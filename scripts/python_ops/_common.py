"""Private helpers shared across op modules."""

import unreal


def make_result(op: str, target: str, field: str = "") -> dict:
    """Seed the standard op-result dict."""
    return {
        "success": False,
        "op": op,
        "target": target,
        "field": field,
        "before": None,
        "after": None,
        "errors": [],
    }


def load_bp(bp_path: str, result: dict):
    """Load a Blueprint asset. On failure appends error + returns None."""
    if not bp_path.startswith("/Game/"):
        result["errors"].append(f"bp_path must start with /Game/: {bp_path!r}")
        return None
    asset = unreal.load_asset(bp_path)
    if asset is None:
        result["errors"].append(f"load_asset returned None for {bp_path!r}")
        return None
    if not isinstance(asset, unreal.Blueprint):
        result["errors"].append(
            f"asset at {bp_path!r} is {type(asset).__name__}, expected Blueprint"
        )
        return None
    return asset


def get_bp_cdo(bp, result: dict):
    """Resolve a Blueprint's Class Default Object."""
    gen_class = bp.generated_class()
    if gen_class is None:
        result["errors"].append(f"generated_class is None for {bp.get_path_name()!r}")
        return None
    cdo = unreal.get_default_object(gen_class)
    if cdo is None:
        result["errors"].append(f"get_default_object returned None for {bp.get_path_name()!r}")
        return None
    return cdo


def compile_and_save_blueprint(bp, result: dict) -> bool:
    """Recompile the BP (so it captures new CDO state) and save the package.

    Returns True on success, False on any step failure (errors appended to result).
    """
    try:
        unreal.BlueprintEditorLibrary.compile_blueprint(bp)
    except Exception as exc:
        result["errors"].append(f"compile_blueprint raised: {exc}")
        return False

    try:
        saved = unreal.EditorAssetLibrary.save_loaded_asset(bp)
    except Exception as exc:
        result["errors"].append(f"save_loaded_asset raised: {exc}")
        return False

    if not saved:
        result["errors"].append("save_loaded_asset returned False")
        return False

    return True


def values_equal(a, b) -> bool:
    """Structural equality for UE values — handles Vector2D / Vector / Rotator etc.

    Property getters return UE struct types which don't implement __eq__ uniformly;
    this is a pragmatic comparison that catches no-op edits without requiring
    per-type handling.
    """
    if a is b:
        return True
    if type(a) is not type(b):
        return False
    try:
        return a == b
    except Exception:
        pass
    # Fallback: string representation comparison (unreal types have stable reprs)
    return repr(a) == repr(b)


def find_component_template(bp, component_name: str, result: dict):
    """Resolve the SCS component template UObject for an SCS-added component.

    Uses SubobjectDataSubsystem (the modern API, UE 5.0+). Works for BP-added
    components; for natively-declared components use CDO access via
    `cdo.get_editor_property(component_name)` instead (M21.0 scope — not
    bundled here since natively-declared components are a separate code path).

    Returns the component template UObject or None (with errors appended).
    """
    try:
        sds = unreal.get_engine_subsystem(unreal.SubobjectDataSubsystem)
    except Exception as exc:
        result["errors"].append(f"SubobjectDataSubsystem unavailable: {exc}")
        return None

    if sds is None:
        result["errors"].append("SubobjectDataSubsystem returned None")
        return None

    sbfl = unreal.SubobjectDataBlueprintFunctionLibrary
    try:
        handles = sds.k2_gather_subobject_data_for_blueprint(bp)
    except Exception as exc:
        result["errors"].append(f"gather subobjects failed: {exc}")
        return None

    available_names = []
    for h in handles or []:
        data = sbfl.get_data(h)
        if data is None:
            continue
        var_name = str(sbfl.get_variable_name(data))
        available_names.append(var_name)
        if var_name == component_name:
            obj = sbfl.get_object(data)
            if obj is None:
                result["errors"].append(
                    f"component {component_name!r} found but get_object returned None"
                )
                return None
            return obj

    result["errors"].append(
        f"component {component_name!r} not found on BP; available: {available_names}"
    )
    return None


def resolve_subobject_path(root, path, result: dict):
    """Walk a list of str / int navigation steps starting from `root`.

    Strings resolve via get_editor_property. Integers index into a sequence.
    Returns the final object, or None on failure (errors appended).
    """
    obj = root
    for i, step in enumerate(path):
        trace = f"path[:{i + 1}] = {path[: i + 1]!r}"
        if isinstance(step, int):
            try:
                obj = obj[step]
            except Exception as exc:
                result["errors"].append(f"index {step} failed at {trace}: {exc}")
                return None
        elif isinstance(step, str):
            try:
                obj = obj.get_editor_property(step)
            except Exception as exc:
                result["errors"].append(f"get_editor_property({step!r}) failed at {trace}: {exc}")
                return None
        else:
            result["errors"].append(
                f"path element at index {i} is {type(step).__name__}, expected str or int"
            )
            return None
        if obj is None:
            result["errors"].append(f"navigation returned None at {trace}")
            return None
    return obj
