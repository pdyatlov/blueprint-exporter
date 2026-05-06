"""UDataAsset authoring ops via the M28.4.2+ reflection bridge.

Creates and edits `UDataAsset`-subclass instances — the middle slice of
the M28.4 non-BP asset factories (curves → data assets → user-defined
structs, complexity ramp per the M28.4.0 research outcome).

M28.4.2 ships the two ops:

  - create_data_asset_instance  — wraps NewObject<UDataAsset>(Pkg, DAClass,
                                    RF_Public|RF_Standalone|RF_Transactional)
                                    at a /Game/ path. Idempotent on
                                    (asset_path, parent_class_path).
  - set_data_asset_property     — scalar UPROPERTY setter on a DA instance,
                                    reusing the existing M23.1 SetPropertyValue
                                    reflection bridge — zero new UFUNCTIONs.

Design.md driver: item #7 (archetype DAs — Rusher / Marksman /
Suppresser / Flanker). Each archetype is a /Game/.../DA_Rusher.uasset
instance of a BP-derived UPrimaryDataAsset subclass carrying the
per-archetype tuning (aggressive melee range, backline scoring bias,
suppression duty cycle, flanking preference weights).

Determinism: UDataAsset / UPrimaryDataAsset have zero
`FGuid::NewGuid()` usage (grep-confirmed M28.4.0 research). No seeding
recipe is needed — the explicit `FName` on each `NewObject` (derived
from the asset's short name) is the only determinism lever, and the
bridge UFUNCTION already handles it.

Out of scope for M28.4.2 (deferred per the research outcome):

  - Full UPrimaryDataAsset PreSave AssetBundleData determinism audit.
    UpdateAssetBundleData walks UPROPERTY references in declaration
    order so the output is deterministic by construction (M28.4.0
    research #4); if a concrete corpus surfaces drift, add a soak fixture
    that exercises a DA with bundle-tagged object references.
  - BP-derived DA parent class resolution via the mangled
    `<PropName>_<N>_<GUID>` UPROPERTY name form. The current
    `SetPropertyValue` bridge walks `FindFProperty` by the friendly
    FName the author declared, which matches how BP-declared member
    variables land on the generated class. If a real mangling case
    surfaces (e.g. a shadowed / renamed field), add a
    `_resolve_da_property_name(da_class, friendly_name)` helper here
    rather than bloating every op's happy path.
  - Non-scalar / Instanced-subobject property edits. The existing
    M26.1 `set_instanced_subobject_property` op covers that shape for
    Blueprints; if a DA carries an EditInline inner object that needs
    mutating, that op already works on any UObject root.
"""

import unreal

from ._common import make_result


def _ops():
    return unreal.BpxReflectionOps


def _load_data_asset(asset_path: str, result: dict):
    """Load a UDataAsset. On failure appends error + returns None.

    Mirrors `eqs._load_eqs` but for DataAsset. Accepts any UDataAsset
    subclass — BP-derived DA classes also pass `isinstance(..., DataAsset)`
    because their GeneratedClass inherits from UDataAsset / UPrimaryDataAsset.
    Canonical rejection path for `/Script/` targets (DAs must live under
    `/Game/` because only project content is editable) and wrong-type assets.
    """
    if not isinstance(asset_path, str) or not asset_path.startswith("/Game/"):
        result["errors"].append(
            f"asset_path must start with /Game/: {asset_path!r}"
        )
        return None
    asset = unreal.load_asset(asset_path)
    if asset is None:
        result["errors"].append(f"load_asset returned None for {asset_path!r}")
        return None
    if not isinstance(asset, unreal.DataAsset):
        result["errors"].append(
            f"asset at {asset_path!r} is {type(asset).__name__}, expected DataAsset"
        )
        return None
    return asset


def _resolve_da_class(class_path: str, result: dict):
    """Resolve a UClass by path — covers native `/Script/<Module>.<Class>` and
    BP-derived `/Game/.../DA_Foo.DA_Foo_C` forms.

    Mirrors `eqs._resolve_eqs_class` / `blueprint_structural.add_bp_interface`'s
    resolution shape: `load_class` for native paths, `load_object` fallback
    for BP-derived generated classes. The bridge UFUNCTION does the abstract /
    wrong-subclass rejection — this helper only validates that the path
    resolves to a UClass at all.
    """
    if not isinstance(class_path, str) or not class_path:
        result["errors"].append("parent_class_path must be a non-empty string")
        return None
    cls = (
        unreal.load_class(None, class_path)
        or unreal.load_object(None, class_path)
    )
    if cls is None or not isinstance(cls, unreal.Class):
        result["errors"].append(
            f"parent_class_path did not resolve to a UClass: {class_path!r} "
            f"(native form /Script/<Module>.<Class> or BP form "
            f"/Game/<path>/<Name>.<Name>_C)"
        )
        return None
    return cls


def _normalize_scalar_value(value, result: dict):
    """Coerce a Python scalar to the ExportText string SetPropertyValue expects.

    Mirrors `eqs._normalize_scalar_value` / `level.set_level_actor_property`
    so plan JSON can carry plain ints / floats / bools without
    string-quoting them. On unsupported types appends a structured error and
    returns ``(None, False)``.
    """
    if isinstance(value, bool):
        return ("true" if value else "false"), True
    if isinstance(value, (int, float)):
        return repr(value), True
    if isinstance(value, str):
        return value, True
    result["errors"].append(
        f"value must be a string / int / float / bool; got {type(value).__name__}"
    )
    return None, False


def create_data_asset_instance(asset_path: str, parent_class_path: str):
    """Create a new `UDataAsset`-subclass instance at a ``/Game/...`` path.

    Third op of the M28.4 non-BP asset-factory catalog. Creates an empty
    instance (no UPROPERTY overrides); populate via `set_data_asset_property`
    in follow-up op(s) or plan step(s).

    Args:
        asset_path: ``/Game/...`` path where the asset should live. Short
            name is derived from the last segment — the asset's FName will
            match the path tail so re-exports / inventory sidecars resolve
            cleanly.
        parent_class_path: UClass path of the concrete DA subclass to
            instantiate. Covers:

              - native DA classes: ``/Script/<Module>.<ClassName>``
              - BP-derived DA classes: ``/Game/<path>/<Name>.<Name>_C``
                (the generated class, not the BP asset path — `_C` suffix
                per Epic's GeneratedClass naming convention).

            Must be a non-abstract subclass of ``UDataAsset`` (which
            `UPrimaryDataAsset` and every BP-derived DA class also
            satisfies transitively).

    Returns:
        Standard op-result dict. ``after`` carries
        ``{asset_path, parent_class_path, spawned: bool}``.

        Idempotent on ``(asset_path, parent_class_path)``: if a DA instance
        already exists at the target path AND its class matches
        ``parent_class_path``, returns ``success=True`` with
        ``skipped="asset already exists"`` and ``spawned=False``. Class
        mismatch at the same path returns a structured error — silent
        co-existence would be a plan-level mistake.

    Determinism: the bridge UFUNCTION passes an explicit `FName` on the
    `NewObject` call (derived from the short-name tail of ``asset_path``).
    `UDataAsset` / `UPrimaryDataAsset` have zero `FGuid::NewGuid()` usage
    so no seed recipe is needed. M28.pre.3 soak exercises this invariant.
    """
    result = make_result(
        "create_data_asset_instance", asset_path, parent_class_path
    )

    if not isinstance(asset_path, str) or not asset_path.startswith("/Game/"):
        result["errors"].append(
            f"asset_path must start with /Game/: {asset_path!r}"
        )
        return result

    da_class = _resolve_da_class(parent_class_path, result)
    if da_class is None:
        return result

    ops = _ops()
    r = ops.create_data_asset_instance_deterministic(asset_path, da_class)
    if not r.success:
        result["errors"].append(
            f"create_data_asset_instance_deterministic bridge call failed: "
            f"{r.error_message}"
        )
        return result

    result["before"] = r.before_text

    if r.skipped:
        result["success"] = True
        result["skipped"] = "asset already exists"
        result["after"] = {
            "asset_path": asset_path,
            "parent_class_path": parent_class_path,
            "spawned": False,
        }
        return result

    # Resolve the freshly-created in-memory UObject back via load_asset.
    # After NewObject + AssetRegistry::AssetCreated the asset is visible to
    # `unreal.load_asset` without requiring a prior save — the Python
    # binding's load_object path finds in-memory UObjects first.
    asset = unreal.load_asset(asset_path)
    if asset is None:
        result["errors"].append(
            f"load_asset returned None for {asset_path!r} after create "
            "(unexpected — bridge reported success)"
        )
        return result

    # UDataAsset is not a Blueprint; compile_and_save_package skips the BP
    # compile step and goes straight to UPackage::SavePackage.
    if not ops.compile_and_save_package(asset):
        result["errors"].append(
            "compile_and_save_package returned False — save refused "
            "(check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = {
        "asset_path": asset_path,
        "parent_class_path": parent_class_path,
        "spawned": True,
    }
    return result


def set_data_asset_property(
    asset_path: str,
    property_path: list,
    value,
):
    """Mutate a UPROPERTY on a `UDataAsset`-subclass instance.

    Fourth op of the M28.4 non-BP asset-factory catalog. Wraps the existing
    ``UBpxReflectionOps::SetPropertyValue`` reflection bridge (shipped in
    M23.1) — no new UFUNCTION. Covers any editable UPROPERTY the DA class
    exposes, whether declared natively on a C++ parent or as a BP-added
    member variable on a BP-derived DA class.

    Args:
        asset_path: ``/Game/...`` path to an existing DA instance.
        property_path: Navigation steps the reflection bridge understands.
            A single leaf name (``["AggroRadius"]``) addresses a plain
            UPROPERTY on the DA; nested paths
            (``["Tuning", "MeleeRange"]``) descend into FStructProperty
            fields such as a declared ``FArchetypeTuning`` struct. Array
            elements use ``"[N]"`` notation — see
            ``BpxReflectionOps::ResolvePath``.
        value: The property's new value. Strings are forwarded verbatim;
            ints / floats / bools are coerced to their ExportText form
            (``"true"`` / ``"false"`` / decimal repr) so plan JSON can
            carry native scalars. See
            ``FProperty::ExportTextItem_Direct`` for the canonical string
            format per type.

    Returns:
        Standard op-result dict. ``before`` / ``after`` carry the
        ExportText form of the old and new values. ``skipped`` is set
        when the property already equals ``value`` (no save).

    Idempotent: ``SetPropertyValue`` short-circuits when ``before == value``
    as a string, so replaying the same plan is a no-op on rounds 2+.

    Out of scope (deliberate):
      - Instanced-subobject / EditInlineNew references. Use
        `set_instanced_subobject_property` (M26.1) for those — it already
        works on any UObject root. The SetPropertyValue bridge only covers
        scalar + struct-scalar mutations.
      - Mangled UPROPERTY name resolution. BP-added DA member variables
        land on the generated class with the friendly FName, so
        `FindFProperty(class, FName(friendly_name))` resolves cleanly.
        If a real mangled case surfaces, add a
        `_resolve_da_property_name` helper here.
    """
    result = make_result(
        "set_data_asset_property",
        asset_path,
        f"{'.'.join(str(p) for p in (property_path or []))}={value!r}",
    )

    if not isinstance(property_path, list) or not property_path:
        result["errors"].append(
            "property_path must be a non-empty list of path steps"
        )
        return result
    for step in property_path:
        if not isinstance(step, str) or not step:
            result["errors"].append(
                f"property_path steps must be non-empty strings; got {step!r}"
            )
            return result

    norm_value, ok = _normalize_scalar_value(value, result)
    if not ok:
        return result

    asset = _load_data_asset(asset_path, result)
    if asset is None:
        return result

    ops = _ops()

    before = ops.get_property_value(asset, property_path)
    if not before.success:
        result["errors"].append(
            f"get_property_value failed at {property_path!r}: {before.error_message}"
        )
        return result
    result["before"] = before.after_text

    if before.after_text == norm_value:
        result["success"] = True
        result["skipped"] = f"value already {norm_value!r}"
        result["after"] = before.after_text
        return result

    r = ops.set_property_value(asset, property_path, norm_value)
    if not r.success:
        result["errors"].append(
            f"set_property_value failed at {property_path!r}: {r.error_message}"
        )
        return result

    if not ops.compile_and_save_package(asset):
        result["errors"].append(
            "compile_and_save_package returned False — save refused "
            "(check UE log)"
        )
        return result

    after = ops.get_property_value(asset, property_path)
    result["after"] = after.after_text if after.success else norm_value
    result["success"] = True
    return result
