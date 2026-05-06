"""Asset-level ops: rename, create-from-parent, delete.

These are thin wrappers over `unreal.EditorAssetLibrary` + `AssetToolsHelpers`
that add the standard result-dict shape and idempotence semantics used by the
rest of the op library.
"""

import unreal

from ._common import load_bp, make_result


def rename_asset(old_path: str, new_path: str):
    """Rename (move) an asset by /Game/ path.

    Idempotent in the sense that if `new_path` already exists and `old_path`
    doesn't, the op reports success with `skipped="already renamed"`.

    Args:
        old_path: current /Game/... path (no .uasset extension).
        new_path: target /Game/... path.

    Returns:
        Standard op result dict.
    """
    result = make_result("rename_asset", old_path, new_path)

    if not old_path.startswith("/Game/"):
        result["errors"].append(f"old_path must start with /Game/: {old_path!r}")
        return result
    if not new_path.startswith("/Game/"):
        result["errors"].append(f"new_path must start with /Game/: {new_path!r}")
        return result
    if old_path == new_path:
        result["errors"].append("old_path and new_path are identical")
        return result

    asset_lib = unreal.EditorAssetLibrary

    old_exists = asset_lib.does_asset_exist(old_path)
    new_exists = asset_lib.does_asset_exist(new_path)

    result["before"] = {"old_exists": old_exists, "new_exists": new_exists}

    if not old_exists and new_exists:
        result["after"] = {"old_exists": False, "new_exists": True}
        result["success"] = True
        result["skipped"] = "already renamed"
        return result

    if not old_exists:
        result["errors"].append(f"source asset does not exist: {old_path!r}")
        return result

    if new_exists:
        result["errors"].append(
            f"destination {new_path!r} already exists; refusing to overwrite"
        )
        return result

    try:
        ok = asset_lib.rename_asset(old_path, new_path)
    except Exception as exc:
        result["errors"].append(f"rename_asset raised: {exc}")
        return result

    if not ok:
        result["errors"].append("rename_asset returned False")
        return result

    # Confirm
    result["after"] = {
        "old_exists": asset_lib.does_asset_exist(old_path),
        "new_exists": asset_lib.does_asset_exist(new_path),
    }
    if not result["after"]["new_exists"]:
        result["errors"].append("post-rename: destination does not exist")
        return result

    result["success"] = True
    return result


def _ops():
    return unreal.BpxReflectionOps


def _resolve_parent_class(parent_path: str, result: dict):
    """Resolve a UClass from `/Script/Module.Class`, `/Game/.../BP.BP_C`, or
    the BP-asset shorthand `/Game/.../BP`.

    Mirrors `data_assets._resolve_da_class` / `eqs._resolve_eqs_class` /
    `blueprint_structural._resolve_class`'s `load_class || load_object`
    fallback, with one extra accommodation: if `parent_path` is a `/Game/`
    path missing the `.<Tail>_C` suffix, we synthesize the generated-class
    form (`/Game/<dir>/<Name>.<Name>_C`) so plan authors can use either
    "the BP asset" or "the BP's generated class" interchangeably. Native
    `/Script/...` paths route directly to `load_class`.
    """
    if not isinstance(parent_path, str) or not parent_path:
        result["errors"].append("parent_path must be a non-empty string")
        return None

    candidates = [parent_path]
    # If the caller passed `/Game/<dir>/<Name>` (BP asset) without the `.Name_C`
    # generated-class suffix, synthesize it. The BP-asset path itself resolves
    # to the UBlueprint object, NOT a UClass — load_class would fail.
    if parent_path.startswith("/Game/") and "." not in parent_path.rsplit("/", 1)[-1]:
        tail = parent_path.rsplit("/", 1)[-1]
        candidates.append(f"{parent_path}.{tail}_C")

    for path in candidates:
        cls = (
            unreal.load_class(None, path)
            or unreal.load_object(None, path)
        )
        if cls is not None and isinstance(cls, unreal.Class):
            return cls

    result["errors"].append(
        f"parent_path did not resolve to a UClass: {parent_path!r}. "
        f"Accepted forms: native '/Script/<Module>.<Class>' (e.g. '/Script/Engine.Actor'), "
        f"BP generated class '/Game/<path>/<Name>.<Name>_C', or BP asset '/Game/<path>/<Name>'."
    )
    return None


def create_blueprint_class(parent_path: str, new_bp_path: str):
    """Create a new Blueprint with either a native or BP parent class.

    M28.10.1 op. Closes the design.md gap that surfaced via the M28.10.0
    research outcome: existing `create_child_bp` only handled BP-parented
    children, so design.md's `BP_EncounterDirector` (parent `AActor`) and
    `UAIActionScorer` (parent `UActorComponent`) couldn't be authored
    end-to-end via MCP. This op accepts:

      - Native classes: ``/Script/<Module>.<ClassName>``
        (e.g. ``/Script/Engine.Actor``, ``/Script/Engine.ActorComponent``).
      - BP generated classes: ``/Game/<path>/<Name>.<Name>_C``.
      - BP asset shorthand: ``/Game/<path>/<Name>`` — the helper synthesizes
        the ``.{Name}_C`` form so plan authors can use either.

    Determinism is guaranteed by the C++ bridge, which post-create reseeds:

      - ``UBlueprint::BlueprintGuid``    — md5 of ``<path>:bp``.
      - UCS ``K2Node_FunctionEntry`` NodeGuid + pin ids — md5 of ``<path>:ucs:entry``.
      - Each default-spawned event node (BeginPlay / Tick / EndPlay /
        TickComponent / etc., depending on parent class) NodeGuid + pin ids,
        sorted by event member name to defeat ``TMultiMap`` hash-bucket
        ordering instability.

    See M28.10.0 research outcome in WIP_INVENTORY.md for the FGuid-trapdoor
    catalog and seeding recipe.

    Args:
        parent_path: UClass path of the parent. Must be blueprintable (the
            engine's ``FKismetEditorUtilities::CanCreateBlueprintOfClass``
            gate rejects e.g. ``UInterface`` and classes marked
            ``BlueprintType=NotBlueprintable``).
        new_bp_path: ``/Game/...`` path where the new BP should land. Short
            name is derived from the last segment.

    Returns:
        Standard op-result dict. ``after`` carries
        ``{new_bp_path, parent_path, spawned: bool}``.

    Idempotent on ``(new_bp_path, parent_path)``: if a UBlueprint already
    exists at the path AND its ``ParentClass`` pointer matches the resolved
    ``parent_path``, returns ``success=True`` with
    ``skipped="asset already exists with matching parent"``. Class mismatch
    at the same path returns a structured error — silent stacking would be
    a plan-level mistake. This is **stricter than the pre-M28.10.1
    `create_child_bp`**, which only verified existence (the
    ``BlueprintGeneratedClass.get_super_class`` Python binding gap noted in
    ``CATALOG.md:1431`` — closed here by routing the check through C++
    pointer equality on ``Existing->ParentClass``).
    """
    result = make_result("create_blueprint_class", new_bp_path, parent_path)

    if not isinstance(new_bp_path, str) or not new_bp_path.startswith("/Game/"):
        result["errors"].append(
            f"new_bp_path must start with /Game/: {new_bp_path!r}"
        )
        return result

    parent_class = _resolve_parent_class(parent_path, result)
    if parent_class is None:
        return result

    ops = _ops()
    r = ops.create_blueprint_class_deterministic(new_bp_path, parent_class)
    if not r.success:
        result["errors"].append(
            f"create_blueprint_class_deterministic bridge call failed: "
            f"{r.error_message}"
        )
        return result

    result["before"] = r.before_text

    if r.skipped:
        result["success"] = True
        result["skipped"] = "asset already exists with matching parent"
        result["after"] = {
            "new_bp_path": new_bp_path,
            "parent_path": parent_path,
            "spawned": False,
        }
        return result

    # The bridge UFUNCTION saves the .uasset directly (no compile_and_save_package
    # call here) — a second recompile after the seed pass would clobber
    # NodeGuids via ReconstructNode and re-randomize them, breaking
    # determinism. Verified via M28.10.1 soak: byte-identity holds across
    # rounds with bridge-side save, drifts when Python re-saves through
    # CompileBlueprint.
    if unreal.load_asset(new_bp_path) is None:
        result["errors"].append(
            f"load_asset returned None for {new_bp_path!r} after create "
            "(unexpected — bridge reported success)"
        )
        return result

    result["success"] = True
    result["after"] = {
        "new_bp_path": new_bp_path,
        "parent_path": parent_path,
        "spawned": True,
    }
    return result


def create_child_bp(parent_bp_path: str, new_bp_path: str):
    """Create a new Blueprint whose parent is the Blueprint at `parent_bp_path`.

    **M28.10.1 back-compat alias** — delegates to ``create_blueprint_class``
    after normalizing ``parent_bp_path`` (a BP asset path) to its generated
    class form. Existing plans authored against this op continue to work
    unchanged. New plans should prefer ``create_blueprint_class`` directly,
    which also accepts native ``/Script/<Module>.<Class>`` parents.

    Idempotence is now stricter: the bridge verifies ParentClass match via
    pointer equality, so an existing BP at ``new_bp_path`` with a different
    parent surfaces as a structured error rather than a silent skip (closes
    the pre-M28.10.1 caveat in ``CATALOG.md:1431``).

    Args:
        parent_bp_path: ``/Game/...`` path to the parent Blueprint asset.
        new_bp_path: ``/Game/...`` path where the new BP should land.

    Returns:
        Standard op result dict. ``op`` field is ``"create_child_bp"`` (not
        ``"create_blueprint_class"``) so mechanical_diff oracle entries and
        plan-validator shape lookups remain stable.
    """
    result = make_result("create_child_bp", new_bp_path, parent_bp_path)

    if not isinstance(parent_bp_path, str) or not parent_bp_path.startswith("/Game/"):
        result["errors"].append(
            f"parent_bp_path must start with /Game/: {parent_bp_path!r}"
        )
        return result

    delegated = create_blueprint_class(parent_bp_path, new_bp_path)
    # Preserve op name + target shape, propagate everything else.
    result["before"] = delegated.get("before")
    result["after"] = delegated.get("after")
    result["errors"].extend(delegated.get("errors", []))
    if "skipped" in delegated:
        result["skipped"] = delegated["skipped"]
    result["success"] = delegated.get("success", False)
    return result
