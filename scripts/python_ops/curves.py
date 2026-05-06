"""UCurveFloat authoring ops via the M28.4.1+ reflection bridge.

Creates and edits `UCurveFloat` assets — the simplest slice of the M28.4
non-BP asset factories (curves → data assets → user-defined structs,
complexity ramp per the M28.4.0 research outcome).

M28.4.1 ships the two bootstrap ops:

  - create_curve_float    — wraps NewObject<UCurveFloat> + AssetRegistry
                            notification at a /Game/ path. Idempotent on
                            (curve_path).
  - set_curve_float_keys  — wholesale-replace the FRichCurveKey array on
                            UCurveFloat::FloatCurve. Idempotent on the
                            (Time, Value, InterpMode) tuple per key.

Design.md driver: item #6 (encounter-director intensity curve) — author
the 4-point intensity curve as a UCurveFloat at plan-compose time,
rather than requiring a manual editor pass.

Determinism: UCurveFloat / UCurveBase / FRichCurveKey have zero
`FGuid::NewGuid()` usage (grep-confirmed M28.4.0 research). No seeding
recipe is needed — the explicit `FName` on each `NewObject` (derived
from the asset's short name) is the only determinism lever, and the
bridge UFUNCTION already handles it.

Out of scope for M28.4.1 (deferred per the research outcome):

  - Per-key ops (add_curve_float_key / remove_curve_float_key /
    update_curve_float_key). Wholesale replacement is atomic and matches
    the "re-author as a unit" authoring style the design.md driver uses.
    Revisit if a plan surfaces the "tweak one point without re-supplying
    all N" use case.
  - Tangent / interp-mode configuration beyond the default (`Linear`).
    The Python surface accepts `interp_mode` as an optional string but
    doesn't expose tangent tuning — `FRichCurveKey`'s default
    zero-initialiser covers the common case; bespoke tangents belong in
    a future per-key op.
  - Non-float curves (UCurveVector, UCurveLinearColor). Narrow scope
    matches the M28.3 narrow K2Node catalog precedent.
"""

import unreal

from ._common import make_result


def _ops():
    return unreal.BpxReflectionOps


# ERichCurveInterpMode enum values resolved via getattr at import time, because
# UE's Python binding rejects plain `int` for the ByteProperty-backed
# `RichCurveKey.interp_mode` field ("NativizeProperty: Cannot nativize 'int' as
# 'InterpMode' (ByteProperty)"). The unreal.RichCurveInterpMode enum exposes
# RCIM_LINEAR / RCIM_CONSTANT / RCIM_CUBIC but NOT RCIM_NONE (the binding hides
# the `None` spelling due to the Python keyword clash). We don't expose
# "none" on the Python surface — it has no realistic driver for the M28.4.1
# intensity-curve use case, and the binding's gap means we'd have to drop to
# ImportText to reach it. If a driver surfaces, revisit with a per-key op.
_E = unreal.RichCurveInterpMode
_INTERP_MODES = {
    "linear":   _E.RCIM_LINEAR,
    "constant": _E.RCIM_CONSTANT,
    "cubic":    _E.RCIM_CUBIC,
}


def _resolve_interp_mode(name, result: dict):
    """Resolve a string interp-mode name to the unreal.RichCurveInterpMode
    enum value. Returns the enum on success, or None (with error appended)
    on bad input. Unknown names return a structured error rather than
    silently falling back to RCIM_Linear.
    """
    if name is None:
        return _INTERP_MODES["linear"]
    key = str(name).strip().lower()
    if key not in _INTERP_MODES:
        result["errors"].append(
            f"unknown interp_mode: {name!r} (valid: {sorted(_INTERP_MODES)})"
        )
        return None
    return _INTERP_MODES[key]


def _build_rich_curve_key(entry, idx: int, result: dict):
    """Convert a plan-JSON dict into an `unreal.RichCurveKey`.

    Accepted shape: ``{"time": float, "value": float[, "interp_mode": str]}``.
    Missing `time` or `value` return structured errors keyed by index
    so plan authors can pinpoint the bad entry.
    """
    if not isinstance(entry, dict):
        result["errors"].append(
            f"keys[{idx}] must be a dict, got {type(entry).__name__}"
        )
        return None
    for required in ("time", "value"):
        if required not in entry:
            result["errors"].append(
                f"keys[{idx}] missing required field {required!r}"
            )
            return None

    try:
        time = float(entry["time"])
    except (TypeError, ValueError) as exc:
        result["errors"].append(f"keys[{idx}].time must be a number: {exc}")
        return None
    try:
        value = float(entry["value"])
    except (TypeError, ValueError) as exc:
        result["errors"].append(f"keys[{idx}].value must be a number: {exc}")
        return None

    interp = _resolve_interp_mode(entry.get("interp_mode"), result)
    if interp is None:
        return None

    key = unreal.RichCurveKey()
    key.time = time
    key.value = value
    key.interp_mode = interp
    return key


def create_curve_float(curve_path: str):
    """Create a new `UCurveFloat` at a ``/Game/...`` package path.

    First op of the M28.4 non-BP asset-factory catalog. Creates an empty
    curve (zero keys); populate with `set_curve_float_keys` in a follow-up
    op or plan step.

    Args:
        curve_path: ``/Game/...`` path where the curve should live. Short
            name is derived from the last segment — the asset's FName will
            match the path tail so re-exports / inventory sidecars resolve
            cleanly.

    Returns:
        Standard op-result dict. ``after`` carries
        ``{curve_path, spawned: bool}``.

        Idempotent on ``curve_path``: if a `UCurveFloat` already exists at
        the target path, returns ``success=True`` with
        ``skipped="curve already exists"`` and ``spawned=False``. If a
        different asset class occupies the path, returns a structured
        error (silently co-existing would be a plan-level mistake).

    Determinism: the bridge UFUNCTION passes an explicit `FName` on the
    `NewObject` call (derived from the short-name tail of
    ``curve_path``). `UCurveFloat` has zero `FGuid::NewGuid()` usage so
    no seed recipe is needed. M28.pre.3 soak exercises this invariant.
    """
    result = make_result("create_curve_float", curve_path, "")

    if not isinstance(curve_path, str) or not curve_path.startswith("/Game/"):
        result["errors"].append(
            f"curve_path must start with /Game/: {curve_path!r}"
        )
        return result

    ops = _ops()
    r = ops.create_curve_float_deterministic(curve_path)
    if not r.success:
        result["errors"].append(
            f"create_curve_float_deterministic bridge call failed: "
            f"{r.error_message}"
        )
        return result

    result["before"] = r.before_text

    if r.skipped:
        result["success"] = True
        result["skipped"] = "curve already exists"
        result["after"] = {"curve_path": curve_path, "spawned": False}
        return result

    # Resolve the freshly-created in-memory UObject back via load_asset.
    # After NewObject + AssetRegistry::AssetCreated the asset is visible
    # to `unreal.load_asset` without requiring a prior save — the Python
    # binding's load_object path finds in-memory UObjects first.
    curve = unreal.load_asset(curve_path)
    if curve is None:
        result["errors"].append(
            f"load_asset returned None for {curve_path!r} after create "
            "(unexpected — bridge reported success)"
        )
        return result

    # UCurveFloat is a UDataAsset subclass (not a Blueprint);
    # CompileAndSavePackage skips the compile step and goes straight to
    # UPackage::SavePackage.
    if not ops.compile_and_save_package(curve):
        result["errors"].append(
            "compile_and_save_package returned False — save refused "
            "(check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = {"curve_path": curve_path, "spawned": True}
    return result


def set_curve_float_keys(curve_path: str, keys: list):
    """Wholesale-replace the key array on a `UCurveFloat`'s `FloatCurve`.

    Second op of the M28.4 catalog. Mirrors `FRichCurve::SetKeys` — the
    entire key array is replaced in one atomic op. Per the M28.4.0
    research outcome, per-key add/edit/remove ops are deferred until a
    concrete driver materialises; the wholesale shape matches the
    design.md intensity-curve authoring style (re-author as a unit).

    Args:
        curve_path: ``/Game/...`` path to an existing `UCurveFloat`.
        keys: ordered list of ``{time, value [, interp_mode]}`` dicts.
            `time` and `value` are required floats. `interp_mode` is an
            optional string — one of ``"linear"``, ``"constant"``,
            ``"cubic"``, ``"none"`` (default ``"linear"``). Entries must
            be pre-sorted by `time` ascending; the bridge rejects unsorted
            input because `FRichCurve::Evaluate` assumes sorted storage.

    Returns:
        Standard op-result dict. ``after`` carries
        ``{curve_path, key_count, keys}``.

        Idempotent on element-wise ``(time, value, interp_mode)``
        equality against the existing key array: a replay with the same
        keys returns ``success=True`` with
        ``skipped="keys already match"``. Supports soak-style round-2
        replay.
    """
    result = make_result(
        "set_curve_float_keys",
        curve_path,
        f"keys[{len(keys) if isinstance(keys, list) else '?'}]",
    )

    if not isinstance(curve_path, str) or not curve_path.startswith("/Game/"):
        result["errors"].append(
            f"curve_path must start with /Game/: {curve_path!r}"
        )
        return result

    if not isinstance(keys, list):
        result["errors"].append(
            f"keys must be a list, got {type(keys).__name__}"
        )
        return result

    # Build RichCurveKey structs BEFORE hitting the bridge so malformed
    # plan entries fail fast with per-index errors rather than surfacing
    # a generic bridge-side failure.
    built_keys = []
    for i, entry in enumerate(keys):
        key = _build_rich_curve_key(entry, i, result)
        if key is None:
            return result
        built_keys.append(key)

    # Time-ascending monotonicity — the bridge enforces it too, but
    # catching Python-side produces a cleaner error for plan authors.
    for i in range(1, len(built_keys)):
        if built_keys[i].time < built_keys[i - 1].time:
            result["errors"].append(
                f"keys must be sorted by time ascending; "
                f"keys[{i}].time={built_keys[i].time} < "
                f"keys[{i - 1}].time={built_keys[i - 1].time}"
            )
            return result

    curve = unreal.load_asset(curve_path)
    if curve is None:
        result["errors"].append(f"load_asset returned None for {curve_path!r}")
        return result
    if not isinstance(curve, unreal.CurveFloat):
        result["errors"].append(
            f"asset at {curve_path!r} is {type(curve).__name__}, expected CurveFloat"
        )
        return result

    ops = _ops()
    r = ops.set_curve_float_keys(curve, built_keys)
    if not r.success:
        result["errors"].append(
            f"set_curve_float_keys bridge call failed: {r.error_message}"
        )
        return result

    result["before"] = r.before_text

    if r.skipped:
        result["success"] = True
        result["skipped"] = "keys already match"
        result["after"] = {
            "curve_path": curve_path,
            "key_count": len(built_keys),
        }
        return result

    if not ops.compile_and_save_package(curve):
        result["errors"].append(
            "compile_and_save_package returned False — save refused "
            "(check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = {
        "curve_path": curve_path,
        "key_count": len(built_keys),
    }
    return result
