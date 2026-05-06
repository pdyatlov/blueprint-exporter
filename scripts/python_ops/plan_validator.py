"""Read-only validator for EditPlan JSON documents (M24.1).

Given a plan dict conforming to `plans/README.md`, runs two passes:

1. **Shape** (delegated to `plan_shape.validate_shape`, no UE) - top-level
   fields, known op names, required/optional kwargs, `args`-wrapper
   detection, verification-entry shapes. Importable outside UE.
2. **UE-dependent** (here) - every `/Game/` asset kwarg resolves via
   `EditorAssetLibrary.does_asset_exist`; every StateTree `state_path`
   kwarg resolves to a `UObject` via the M23 reflection bridge,
   read-only, no mutations, no saves.

If shape fails, UE-dependent checks are skipped - the report returned is
the shape report directly so the caller sees exactly what the MCP-side
pre-validation would have caught.

Pairs with the M24.2 executor (refuses to run if
`validate_plan(...)["passed"]` is False).

The validator is intentionally minimal on semantic checks - it does not
pre-compute the expected post-run state, does not re-resolve the
verification block against live state (that is the M24.3 diff oracle's
job), and does not attempt to predict compile outcomes. It catches the
set of plan mistakes that manifest as "op failed on first call": wrong
op names, missing kwargs, typo'd asset paths, unresolvable StateTree
states.
"""

import unreal

from .plan_shape import (
    OP_SPECS,
    format_shape_report,
    validate_shape,
)


def _validate_assets(op, spec, errors, warnings, created_in_plan):
    """Run `does_asset_exist` checks for all `assets` / `assets_absent` keys.

    `created_in_plan` is the set of /Game/ paths that prior ops in this
    plan will create (accumulated from each prior op's `assets_absent`
    entries). A path absent from disk but present in this set is treated
    as existent for `assets` checks — the prior op's create satisfies the
    dependency by the time the current op runs.
    """
    asset_lib = unreal.EditorAssetLibrary

    for key in spec.get("assets", ()):
        path = op.get(key, "")
        if not isinstance(path, str) or not path.startswith("/Game/"):
            errors.append(f"`{key}` must be a /Game/ path string, got {path!r}")
            continue
        if not asset_lib.does_asset_exist(path) and path not in created_in_plan:
            errors.append(f"`{key}` asset does not exist: {path}")

    for key in spec.get("assets_absent", ()):
        path = op.get(key, "")
        if not isinstance(path, str) or not path.startswith("/Game/"):
            # Missing already caught by shape validation when required,
            # else a type warning.
            continue
        if path in created_in_plan:
            warnings.append(
                f"`{key}` is created by an earlier op in this plan: {path} "
                f"— duplicate create will be a skip or class-mismatch conflict"
            )
        elif asset_lib.does_asset_exist(path):
            warnings.append(
                f"`{key}` already exists: {path} — op may be a no-op or conflict"
            )


def _validate_state_path(op, spec_entry, errors):
    """Walk `state_path` read-only through the M23 bridge on the asset
    referenced by `asset_key`. Appends actionable error if the path does
    not resolve to a UObject."""
    asset_key = spec_entry["asset_key"]
    path_key = spec_entry["path_key"]

    asset_path = op.get(asset_key, "")
    if not isinstance(asset_path, str) or not asset_path.startswith("/Game/"):
        # Asset-shape error already produced; skip.
        return

    state_path = op.get(path_key)
    if not isinstance(state_path, list) or not state_path:
        errors.append(
            f"`{path_key}` must be a non-empty list of path steps"
        )
        return

    for step in state_path:
        if not isinstance(step, (str, int)):
            errors.append(
                f"`{path_key}` element {step!r} must be a string or int"
            )
            return

    asset = unreal.load_asset(asset_path)
    if asset is None:
        errors.append(f"load_asset returned None for `{asset_key}`: {asset_path}")
        return

    ed = unreal.BpxReflectionOps.find_subobject(
        asset, unreal.Name("StateTreeEditorData")
    )
    if ed is None:
        errors.append(
            f"no StateTreeEditorData subobject reachable from `{asset_key}` "
            f"({asset_path}) — is this a StateTree asset?"
        )
        return

    resolved = unreal.BpxReflectionOps.get_object_property_value(ed, state_path)
    if resolved is None:
        errors.append(
            f"`{path_key}` {state_path!r} does not resolve to a UObject on {asset_path}"
        )


def validate_plan(plan: dict) -> dict:
    """Validate an EditPlan dict without mutating anything.

    Two-pass: (1) `plan_shape.validate_shape` for all non-UE checks, (2)
    UE-dependent asset + state_path resolution. If (1) fails, (2) is
    skipped and the shape report is returned as-is.

    Args:
        plan: parsed JSON plan matching the schema in `plans/README.md`.

    Returns:
        ``{
            "passed": bool,   # True iff no per-op errors AND no top-level errors
            "errors": list,   # top-level schema / verification errors
            "warnings": list, # non-fatal concerns
            "per_op": [
                {"op_idx": int, "op": str, "ok": bool,
                 "errors": list, "warnings": list}
            ]
        }``

    `passed=False` MUST block execution downstream (M24.2 executor
    enforces this). Warnings do not block — they indicate "op may be a
    no-op" or similar soft concerns.
    """
    shape_report = validate_shape(plan)
    if not shape_report["passed"]:
        return shape_report

    # Shape passed. Run the UE-dependent checks op by op, layering any
    # additional errors / warnings onto the shape report's per-op dicts.
    per_op = shape_report["per_op"]
    top_errors = list(shape_report["errors"])
    top_warnings = list(shape_report["warnings"])

    # Paths created by ops earlier in this plan. An op whose spec lists
    # a kwarg under `assets_absent` creates that path on success; later
    # ops that need it under `assets` should treat it as existent.
    created_in_plan: set = set()

    for i, op in enumerate(plan.get("operations", [])):
        entry = per_op[i]
        # Shape pass ensures op is a dict with a known name; fetch the spec.
        spec = OP_SPECS[op["op"]]
        errs = entry["errors"]
        warns = entry["warnings"]
        _validate_assets(op, spec, errs, warns, created_in_plan)
        for sp_entry in spec.get("state_paths", ()):
            _validate_state_path(op, sp_entry, errs)
        entry["ok"] = not errs

        # Record any /Game/ paths this op will create so subsequent ops
        # see them as existent. `assets_absent` is the canonical create
        # marker (covers create_user_defined_struct, create_curve_float,
        # create_data_asset_instance, create_child_bp, rename_asset).
        for key in spec.get("assets_absent", ()):
            path = op.get(key, "")
            if isinstance(path, str) and path.startswith("/Game/"):
                created_in_plan.add(path)

    passed = not top_errors and all(entry["ok"] for entry in per_op)
    return {
        "passed": passed,
        "errors": top_errors,
        "warnings": top_warnings,
        "per_op": per_op,
    }


def format_report(report: dict) -> str:
    """Human-readable one-screen rendering of a validate_plan report.
    Useful when the CLI harness pipes stdout to a terminal."""
    # Same structure as the shape report; reuse its renderer.
    return format_shape_report(report).replace(
        "Plan shape validation:", "Plan validation:", 1
    )
