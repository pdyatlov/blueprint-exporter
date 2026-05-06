"""Blueprint CDO + SCS component value edits.

Covers three overlapping write targets:
- `set_bp_variable_default`: the default of a BP-declared My-Blueprint variable
  (on the generated class's CDO).
- `set_component_property`: a flat property on an SCS-added component template.
- `set_instanced_subobject_property`: a property on a subobject reached by
  walking a path of components / properties / array indices (e.g.
  AIPerception → SensesConfig → [0] → SightRadius).

All three go through UE's own save / compile paths — no JSON round-trip.
"""

import unreal

from ._common import (
    compile_and_save_blueprint,
    find_component_template,
    get_bp_cdo,
    load_bp,
    make_result,
    resolve_subobject_path,
    values_equal,
)


def set_bp_variable_default(bp_path: str, var_name: str, value):
    """Set a BP-declared variable's default value on the Blueprint's CDO.

    Args:
        bp_path: /Game/... path to the Blueprint asset.
        var_name: the BP variable name (case-sensitive, as declared in the BP).
        value: the new default value. Type must match the variable's declared
            type (e.g. unreal.Vector2D for Vector2D vars, float for real,
            int for int, str for str/FName/FText, etc.).

    Returns:
        Result dict — see python_ops docstring for shape.

    Behavior:
        - Idempotent: if current value equals `value`, returns success with
          no save (md5 unchanged).
        - Atomic: either the BP compiles + saves cleanly, or nothing changes
          on disk. Compile failures abort before save.
    """
    result = make_result("set_bp_variable_default", bp_path, var_name)

    bp = load_bp(bp_path, result)
    if bp is None:
        return result

    cdo = get_bp_cdo(bp, result)
    if cdo is None:
        return result

    # Read before-value; this also validates the property exists on the CDO.
    try:
        before = cdo.get_editor_property(var_name)
    except Exception as exc:
        result["errors"].append(
            f"get_editor_property({var_name!r}) raised: {exc} — "
            f"typo or not a CDO-visible property?"
        )
        return result
    result["before"] = before

    # Idempotence: skip save if value is already the target.
    if values_equal(before, value):
        result["after"] = before
        result["success"] = True
        result["skipped"] = "value already matches"
        return result

    try:
        cdo.set_editor_property(var_name, value)
    except Exception as exc:
        result["errors"].append(
            f"set_editor_property({var_name!r}, {value!r}) raised: {exc} — "
            f"type mismatch or read-only property?"
        )
        return result

    # Read-back to confirm the set took.
    try:
        after = cdo.get_editor_property(var_name)
    except Exception as exc:
        result["errors"].append(f"post-set get_editor_property raised: {exc}")
        return result
    result["after"] = after

    if not values_equal(after, value):
        result["errors"].append(
            f"post-set value {after!r} does not match requested {value!r} — "
            f"silent coercion by UE?"
        )
        return result

    if not compile_and_save_blueprint(bp, result):
        return result

    result["success"] = True
    return result


def set_component_property(bp_path: str, component_name: str, property_name: str, value):
    """Set a property on an SCS component template.

    Example:
        set_component_property(
            "/Game/CombatPrototype/DrewPrototype/BP_EnemyBase_AIController",
            "AIPerception",
            "MaxDegreesToSenseDesync",
            5.0,
        )

    Args:
        bp_path: /Game/... path to the Blueprint.
        component_name: SCS component variable name (as in the Components panel).
        property_name: UPROPERTY name on the component (case-sensitive).
        value: new value (same type-matching rules as set_bp_variable_default).

    Idempotent: short-circuits without save if value unchanged.

    Note: works for BP-added SCS components (AIPerception, Mesh, CharacterMovement
    in BP-derived character classes, etc.). For components declared as UPROPERTYs
    on the native parent class (e.g. ACharacter's `Mesh` on a BP that doesn't
    override it), fall back to CDO-property access — a separate op will come in
    M21.0+ if that case appears in practice.
    """
    result = make_result("set_component_property", bp_path, f"{component_name}.{property_name}")

    bp = load_bp(bp_path, result)
    if bp is None:
        return result

    comp = find_component_template(bp, component_name, result)
    if comp is None:
        return result

    try:
        before = comp.get_editor_property(property_name)
    except Exception as exc:
        result["errors"].append(
            f"get_editor_property({property_name!r}) on {component_name!r} raised: {exc}"
        )
        return result
    result["before"] = before

    if values_equal(before, value):
        result["after"] = before
        result["success"] = True
        result["skipped"] = "value already matches"
        return result

    try:
        comp.set_editor_property(property_name, value)
    except Exception as exc:
        result["errors"].append(
            f"set_editor_property({property_name!r}, {value!r}) raised: {exc}"
        )
        return result

    try:
        after = comp.get_editor_property(property_name)
    except Exception as exc:
        result["errors"].append(f"post-set get_editor_property raised: {exc}")
        return result
    result["after"] = after

    if not values_equal(after, value):
        result["errors"].append(
            f"post-set value {after!r} does not match requested {value!r}"
        )
        return result

    if not compile_and_save_blueprint(bp, result):
        return result

    result["success"] = True
    return result


def set_instanced_subobject_property(bp_path: str, path: list, property_name: str, value):
    """Set a property on a nested instanced subobject reached by walking `path`.

    `path` is a list where the first element is the SCS component name, followed
    by any number of string property names and integer array indices. The walker
    stops on the object one step before the leaf property — that leaf property
    is set via `property_name`.

    Example — AIPerception.SensesConfig[0].SightRadius = 1500:

        set_instanced_subobject_property(
            "/Game/CombatPrototype/DrewPrototype/BP_EnemyBase_AIController",
            path=["AIPerception", "SensesConfig", 0],
            property_name="SightRadius",
            value=1500.0,
        )

    Idempotent: short-circuits without save if value unchanged.

    The BP's recompile + save captures the edit because instanced subobjects are
    held by-reference (UObject ptrs) — editing via the Python handle mutates the
    underlying UObject that the BP's component template owns.
    """
    result = make_result(
        "set_instanced_subobject_property",
        bp_path,
        " -> ".join(str(p) for p in list(path) + [property_name]),
    )

    if not path:
        result["errors"].append("path must be non-empty (first element is component name)")
        return result
    if not isinstance(path[0], str):
        result["errors"].append(
            f"path[0] must be a component name string, got {type(path[0]).__name__}"
        )
        return result

    bp = load_bp(bp_path, result)
    if bp is None:
        return result

    component_name = path[0]
    comp = find_component_template(bp, component_name, result)
    if comp is None:
        return result

    leaf = resolve_subobject_path(comp, path[1:], result)
    if leaf is None:
        return result

    try:
        before = leaf.get_editor_property(property_name)
    except Exception as exc:
        result["errors"].append(
            f"get_editor_property({property_name!r}) on leaf raised: {exc}"
        )
        return result
    result["before"] = before

    if values_equal(before, value):
        result["after"] = before
        result["success"] = True
        result["skipped"] = "value already matches"
        return result

    try:
        leaf.set_editor_property(property_name, value)
    except Exception as exc:
        result["errors"].append(
            f"set_editor_property({property_name!r}, {value!r}) raised: {exc}"
        )
        return result

    try:
        after = leaf.get_editor_property(property_name)
    except Exception as exc:
        result["errors"].append(f"post-set get_editor_property raised: {exc}")
        return result
    result["after"] = after

    if not values_equal(after, value):
        result["errors"].append(
            f"post-set value {after!r} does not match requested {value!r}"
        )
        return result

    if not compile_and_save_blueprint(bp, result):
        return result

    result["success"] = True
    return result
