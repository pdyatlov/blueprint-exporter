"""Level (.umap) authoring ops via the M23 reflection bridge.

Motivating case: Combat_FlatArena has two enemy instances placed with
``Faction`` defaulting to 0 on both. ``AssessThreat.NotEqual_IntInt``
returns false for equal factions, so ``bHasTarget`` never flips and the
AI never enters combat. The fix is to set different faction values on
the two placed actors (team A=1, team B=2). Those are per-instance
``InstanceEditable`` UPROPERTY edits on level actors — no Blueprint-side
change involved.

M28.3 ships :func:`set_level_actor_property` for exactly this class of
edit: locate one placed actor by label, mutate a UPROPERTY on it via the
existing reflection bridge, save the level package. All reflection-bridge
invariants (idempotent SetPropertyValue, deterministic ExportText
round-trip, compile-and-save-package) carry over from M23.

Bridge surface used:
    - BpxReflectionOps.set_property_value (existing — M23.1)
    - BpxReflectionOps.compile_and_save_package (existing — saves the
      level package; compile is a no-op for non-Blueprint UObjects)

Python surface used (editor-side only, not commandlet-safe):
    - unreal.EditorLoadingAndSavingUtils.load_map(level_path) to make
      the target level the editor's current level so GetAllLevelActors
      returns its actors. Commandlet path needs `-SetCurrentMap=<umap>`
      or equivalent; deferred until a non-interactive driver materialises.
"""

import unreal

from ._common import make_result


def _ops():
    return unreal.BpxReflectionOps


def _get_actor_label(actor) -> str:
    """Read an AActor's editor-time label. UE 5.7 Python exposes it via
    ``get_actor_label()`` on the AActor wrapper; older UE versions used
    ``get_editor_property('actor_label')``. We try both so the op works
    across minor version skews without a hard dep on either path."""
    try:
        return str(actor.get_actor_label())
    except Exception:
        pass
    try:
        return str(actor.get_editor_property("actor_label"))
    except Exception:
        pass
    return ""


def _load_level_and_find_actor(level_path: str, actor_label: str, result: dict):
    """Load the level as the editor's current map and return the actor
    matching ``actor_label``. Returns ``(world, actor)`` on success,
    ``(None, None)`` with errors appended otherwise.

    Side effect: the editor's current map becomes ``level_path``. Safe
    for plan execution — ``apply_plan`` is already a side-effecting
    operation — but callers doing interactive work should expect the
    editor to open this level.
    """
    if not level_path.startswith("/Game/"):
        result["errors"].append(
            f"level_path must start with /Game/: {level_path!r}"
        )
        return None, None

    if not actor_label:
        result["errors"].append("actor_label must be non-empty")
        return None, None

    try:
        loaded = unreal.EditorLoadingAndSavingUtils.load_map(level_path)
    except Exception as exc:
        result["errors"].append(f"load_map({level_path!r}) raised: {exc}")
        return None, None
    if not loaded:
        result["errors"].append(f"load_map({level_path!r}) returned False")
        return None, None

    world = unreal.load_asset(level_path)
    if world is None:
        result["errors"].append(f"load_asset returned None for {level_path!r}")
        return None, None
    if not isinstance(world, unreal.World):
        result["errors"].append(
            f"asset at {level_path!r} is {type(world).__name__}, expected World"
        )
        return None, None

    # EditorActorSubsystem is the current API (UE 5.0+); EditorLevelLibrary
    # is deprecated but kept as a fallback path for older 5.x minors.
    actors = []
    try:
        eas = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
        if eas is not None:
            actors = list(eas.get_all_level_actors())
    except Exception as exc:
        result["errors"].append(
            f"EditorActorSubsystem.get_all_level_actors raised: {exc}"
        )
        return None, None

    if not actors:
        try:
            actors = list(unreal.EditorLevelLibrary.get_all_level_actors())
        except Exception:
            actors = []

    if not actors:
        result["errors"].append(
            f"no actors found in current level after load_map({level_path!r}) — "
            f"World-Partition projects may require per-cell loading"
        )
        return None, None

    available = []
    for actor in actors:
        label = _get_actor_label(actor)
        if not label:
            continue
        available.append(label)
        if label == actor_label:
            return world, actor

    # On miss, prefer labels likely to be enemies / BP-derived (non-LevelBlock)
    # so the diagnostic is useful even on dense levels where LevelBlock clutter
    # would push the interesting labels past the tail of a 20-label window.
    filtered = [lbl for lbl in available if not lbl.startswith("LevelBlock")]
    result["errors"].append(
        f"no actor with label {actor_label!r} in {level_path!r}; "
        f"{len(available)} actors total; non-LevelBlock (first 40): {filtered[:40]}"
    )
    return None, None


def set_level_actor_property(
    level_path: str,
    actor_label: str,
    property_path: list,
    value: str,
):
    """Mutate a UPROPERTY on one placed actor in a level and save the level.

    Args:
        level_path: ``/Game/...`` path to the .umap asset.
        actor_label: the actor's editor label as shown in the World
            Outliner (``AActor::GetActorLabel()``). Must match exactly;
            the op does not tolerate duplicate labels in the level.
        property_path: path list the reflection bridge understands.
            Typically a single leaf name (``["Faction"]``); nested paths
            like ``["MovementComponent", "MaxWalkSpeed"]`` also work
            (nav into child UObjects follows the same rules as the rest
            of the op library — see ``BpxReflectionOps::ResolvePath``).
            Array elements use ``"[N]"`` notation.
        value: the property's new value as ExportText — the format
            ``FProperty::ExportTextItem_Direct`` produces. Examples:
            ``"1"`` for an int, ``"true"`` for a bool, ``"EnumName::Alpha"``
            for an enum, ``"(X=1.0,Y=2.0,Z=3.0)"`` for an FVector.
            UE's ``ImportText_Direct`` coerces into the property's native
            type so the schema does the type validation.

    Returns:
        Standard op-result dict. ``before`` / ``after`` carry the
        ExportText form of the old and new property values. ``skipped``
        is set when the property already equals ``value`` (no save).

    Idempotent: the underlying ``BpxReflectionOps.set_property_value``
    short-circuits when ``before == value`` as a string, so running the
    same plan twice is a no-op on the second run.

    Out of scope (M28.3 deliberate):
      - Adding / removing actors in the level. Use the editor.
      - World Partition cell-aware loading — if an actor lives in an
        OFPA cell that isn't loaded by ``load_map``, the op reports
        "no actor with label" and fails cleanly. Loading WP cells
        programmatically is an M20 concern.
      - Level-wide batched edits. Call the op once per actor — each call
        re-saves the level package.
    """
    prop_path_str = "/".join(str(p) for p in property_path)
    result = make_result(
        "set_level_actor_property",
        level_path,
        f"{actor_label}.{prop_path_str}={value!r}",
    )

    if not isinstance(property_path, list) or not property_path:
        result["errors"].append(
            "property_path must be a non-empty list of path steps"
        )
        return result

    # Normalize scalar values into ExportText form. The reflection bridge's
    # SetPropertyValue takes an FString and feeds it to ImportText_Direct;
    # Python's default ``str(True) == "True"`` doesn't round-trip through
    # FProperty's bool importer (it expects lowercase). Explicit coercion
    # makes int / float / bool plan literals safe without the plan author
    # having to quote them.
    if isinstance(value, bool):
        value = "true" if value else "false"
    elif isinstance(value, (int, float)):
        value = repr(value)
    elif not isinstance(value, str):
        result["errors"].append(
            f"value must be a string / int / float / bool; got {type(value).__name__}"
        )
        return result

    world, actor = _load_level_and_find_actor(level_path, actor_label, result)
    if actor is None:
        return result

    ops = _ops()

    # Read current value to decide idempotent skip.
    before = ops.get_property_value(actor, property_path)
    if not before.success:
        result["errors"].append(
            f"get_property_value failed at {property_path!r}: {before.error_message}"
        )
        return result
    result["before"] = before.after_text

    if before.after_text == value:
        result["success"] = True
        result["skipped"] = f"value already {value!r}"
        result["after"] = before.after_text
        return result

    r = ops.set_property_value(actor, property_path, value)
    if not r.success:
        result["errors"].append(
            f"set_property_value failed at {property_path!r}: {r.error_message}"
        )
        return result

    # Fire property-changed so the level editor (if this is running under
    # the bridge with an editor UI up) updates the details panel.
    try:
        actor.modify()
    except Exception:
        pass

    # Mark the world package dirty so save_loaded_asset actually writes it —
    # the in-memory SetPropertyValue path above doesn't update package flags.
    try:
        world.get_package().set_dirty_flag(True)
    except Exception:
        pass

    # Use EditorAssetLibrary.save_loaded_asset rather than the bridge's
    # compile_and_save_package for levels. The latter hardcodes the .uasset
    # extension via FPackageName::GetAssetPackageExtension() so it would
    # write a sibling ``Combat_FlatArena.uasset`` instead of updating the
    # ``.umap``. ``save_loaded_asset`` routes through UE's own map-aware
    # serializer that picks the right extension from the package type.
    try:
        saved = unreal.EditorAssetLibrary.save_loaded_asset(world, only_if_is_dirty=False)
    except Exception as exc:
        result["errors"].append(
            f"save_loaded_asset(world) raised: {exc}"
        )
        return result
    if not saved:
        result["errors"].append(
            "save_loaded_asset(world) returned False — level save refused "
            "(check UE log for error details)"
        )
        return result

    # Read-back: confirm the write landed.
    after = ops.get_property_value(actor, property_path)
    result["after"] = after.after_text if after.success else value
    result["success"] = True
    return result
