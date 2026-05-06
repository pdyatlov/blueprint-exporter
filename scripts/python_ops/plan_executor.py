"""EditPlan executor (M24.2).

Takes a plan dict that has already passed `validate_plan`, dispatches
each op to its library function in order, collects per-op result dicts,
and aborts on first failure so partial state does not persist beyond
the failing op.

Each shipped op already compiles + saves on success, so this executor
does not do a separate save step. Per-op idempotence (built into every
op) means replays after a mid-plan failure skip the already-applied
entries automatically.

Apply is atomic per op, NOT per plan. If op 5 of 10 fails, ops 1–4 are
committed on disk. M24.3 mechanical-diff will flag any surprising
persisted state; rollback is the caller's responsibility (typically
`git checkout` or `p4 revert`).

The executor calls `validate_plan` internally as a safety net — even
if the caller already validated, the re-check catches drift between
validate and execute (e.g., an asset deleted out-of-band).
"""

import time

import unreal

from .assets import create_blueprint_class, create_child_bp, rename_asset
from .blueprint_cdo import (
    set_bp_variable_default,
    set_component_property,
    set_instanced_subobject_property,
)
from .blueprint_graph import connect_graph_pins, implement_interface_function
from .blueprint_graph_nodes import (
    add_branch_node,
    add_break_struct_node,
    add_call_function_node,
    add_custom_event_input,
    add_custom_event_node,
    add_dynamic_cast_node,
    add_execution_sequence_node,
    add_local_variable,
    add_macro_instance_node,
    add_make_struct_node,
    add_set_fields_in_struct_node,
    add_variable_get_node,
    add_variable_set_node,
    set_graph_pin_default,
)
from .blueprint_structural import (
    add_bp_function,
    add_bp_interface,
    add_bp_variable,
    add_component_to_scs,
    add_function_input,
    add_function_output,
    add_function_override,
)
from .curves import (
    create_curve_float,
    set_curve_float_keys,
)
from .data_assets import (
    create_data_asset_instance,
    set_data_asset_property,
)
from .eqs import (
    add_eqs_option,
    add_eqs_test,
    remove_eqs_test,
    set_eqs_generator_property,
    set_eqs_test_property,
)
from .gameplay_tags import add_gameplay_tag
from .uds import (
    add_uds_member,
    create_user_defined_struct,
    remove_uds_member,
    set_uds_member_default,
)
from .level import set_level_actor_property
from .mechanical_diff import (
    compute_expected_changes,
    mechanical_diff,
    snapshot_md5s,
)
from .plan_validator import validate_plan
from .statetree import (
    add_statetree_enter_condition,
    add_statetree_task_to_state,
    add_statetree_transition,
    remove_statetree_enter_condition,
    remove_statetree_task_from_state,
    remove_statetree_transition,
    verify_state_enter_conditions,
    verify_state_tasks,
    verify_state_transitions,
)

_OP_DISPATCH = {
    "set_bp_variable_default": set_bp_variable_default,
    "set_component_property": set_component_property,
    "set_instanced_subobject_property": set_instanced_subobject_property,
    "create_child_bp": create_child_bp,
    "create_blueprint_class": create_blueprint_class,
    "rename_asset": rename_asset,
    "add_statetree_enter_condition": add_statetree_enter_condition,
    "remove_statetree_enter_condition": remove_statetree_enter_condition,
    "verify_state_enter_conditions": verify_state_enter_conditions,
    "add_statetree_transition": add_statetree_transition,
    "remove_statetree_transition": remove_statetree_transition,
    "verify_state_transitions": verify_state_transitions,
    "add_statetree_task_to_state": add_statetree_task_to_state,
    "remove_statetree_task_from_state": remove_statetree_task_from_state,
    "verify_state_tasks": verify_state_tasks,
    "implement_interface_function": implement_interface_function,
    "connect_graph_pins": connect_graph_pins,
    "set_level_actor_property": set_level_actor_property,
    "add_bp_variable": add_bp_variable,
    "add_bp_function": add_bp_function,
    "add_function_override": add_function_override,
    "add_component_to_scs": add_component_to_scs,
    "add_bp_interface": add_bp_interface,
    "add_branch_node": add_branch_node,
    "set_graph_pin_default": set_graph_pin_default,
    "add_call_function_node": add_call_function_node,
    "add_variable_get_node": add_variable_get_node,
    "add_variable_set_node": add_variable_set_node,
    "add_custom_event_node": add_custom_event_node,
    "add_execution_sequence_node": add_execution_sequence_node,
    "add_dynamic_cast_node": add_dynamic_cast_node,
    "add_macro_instance_node": add_macro_instance_node,
    "add_make_struct_node": add_make_struct_node,
    "add_break_struct_node": add_break_struct_node,
    "add_set_fields_in_struct_node": add_set_fields_in_struct_node,
    "add_local_variable": add_local_variable,
    "add_function_input": add_function_input,
    "add_function_output": add_function_output,
    "add_custom_event_input": add_custom_event_input,
    "add_eqs_option": add_eqs_option,
    "add_eqs_test": add_eqs_test,
    "remove_eqs_test": remove_eqs_test,
    "set_eqs_generator_property": set_eqs_generator_property,
    "set_eqs_test_property": set_eqs_test_property,
    "create_curve_float": create_curve_float,
    "set_curve_float_keys": set_curve_float_keys,
    "create_data_asset_instance": create_data_asset_instance,
    "set_data_asset_property": set_data_asset_property,
    "create_user_defined_struct": create_user_defined_struct,
    "add_uds_member": add_uds_member,
    "remove_uds_member": remove_uds_member,
    "set_uds_member_default": set_uds_member_default,
    "add_gameplay_tag": add_gameplay_tag,
}


# Metadata / plumbing fields on an op dict that the library function
# does not accept as a kwarg; executor strips these before dispatch.
_OP_PLUMBING = {"op", "_comment", "idempotency_key", "expected_type"}


def _convert_value(value, expected_type=None):
    """Convert a JSON-native value to the UE Python type the op expects.

    Preference order:
      1. If `expected_type` is provided, use it to route conversion.
         Known tags: "float", "int", "bool", "str", "Vector2D",
         "Vector", "Rotator", "LinearColor", "Object".
      2. Otherwise, infer from the value's shape:
         - dict with {x,y}            → Vector2D
         - dict with {x,y,z}          → Vector
         - dict with {pitch,yaw,roll} → Rotator
         - dict with {r,g,b,a}        → LinearColor
         - str starting with "/Game/" → load_asset(...)
         - plain primitive / list     → pass-through (UE coerces)
      3. If nothing matches, pass through unchanged and let UE raise.

    Raises ``ValueError`` for ambiguous conversions so the error points
    at the plan entry rather than the op.
    """
    if expected_type is not None:
        t = expected_type
        if t in ("float", "int", "bool", "str"):
            return value
        if t == "Vector2D":
            return unreal.Vector2D(value["x"], value["y"])
        if t == "Vector":
            return unreal.Vector(value["x"], value["y"], value["z"])
        if t == "Rotator":
            return unreal.Rotator(
                value.get("roll", 0.0),
                value.get("pitch", 0.0),
                value.get("yaw", 0.0),
            )
        if t == "LinearColor":
            return unreal.LinearColor(
                value["r"], value["g"], value["b"], value.get("a", 1.0)
            )
        if t.startswith("Object"):
            if not isinstance(value, str) or not value.startswith("/Game/"):
                raise ValueError(
                    f"expected_type={t} requires a /Game/ path string, got {value!r}"
                )
            return unreal.load_asset(value)
        raise ValueError(f"unknown expected_type: {t!r}")

    if isinstance(value, dict):
        keys = set(value.keys())
        if keys == {"x", "y"}:
            return unreal.Vector2D(value["x"], value["y"])
        if keys == {"x", "y", "z"}:
            return unreal.Vector(value["x"], value["y"], value["z"])
        if keys == {"pitch", "yaw", "roll"}:
            return unreal.Rotator(value["roll"], value["pitch"], value["yaw"])
        if keys == {"r", "g", "b", "a"}:
            return unreal.LinearColor(
                value["r"], value["g"], value["b"], value["a"]
            )
        raise ValueError(
            f"dict value {value!r} has no recognized UE-type shape — "
            f"add an `expected_type` field to disambiguate"
        )

    if isinstance(value, str) and value.startswith("/Game/"):
        loaded = unreal.load_asset(value)
        if loaded is None:
            raise ValueError(f"load_asset returned None for {value!r}")
        return loaded

    # Plain scalar / list — pass through. UE coerces most scalars on
    # set; lists become TArray via UE's marshalling.
    return value


def _prepare_kwargs(op: dict) -> dict:
    """Strip plumbing fields from the op dict and convert any `value`
    key to its UE type. All other kwargs (paths, names) pass through
    unchanged because they are consumed directly by the library ops."""
    expected_type = op.get("expected_type")
    kwargs = {
        k: v for k, v in op.items() if k not in _OP_PLUMBING
    }
    if "value" in kwargs:
        kwargs["value"] = _convert_value(kwargs["value"], expected_type)
    return kwargs


def execute_plan(plan: dict) -> dict:
    """Validate + execute a plan. Aborts on first op failure.

    Args:
        plan: JSON plan matching `plans/README.md`.

    Returns:
        ``{
            "passed": bool,                 # all ops succeeded (or skipped)
            "validation_report": dict,      # full output of validate_plan
            "aborted_at": int | None,       # op index of first failure
            "executed": int,                # count of ops dispatched
            "per_op": [
                {"op_idx": int, "op": str,
                 "result": dict | None,     # the op's result dict, if it ran
                 "error": str | None}       # set on value-conversion / pre-dispatch errors
            ],
            "elapsed_seconds": float,
        }``

    On a validation failure, returns immediately with ``passed=False``,
    ``per_op=[]``, ``aborted_at=None``, and the validation report carrying
    the specific errors. No ops dispatched.
    """
    t0 = time.time()
    report = {
        "passed": False,
        "validation_report": None,
        "aborted_at": None,
        "executed": 0,
        "per_op": [],
        "elapsed_seconds": 0.0,
    }

    total = len(plan.get("operations", []))
    unreal.log(f"[run_plan] execute_plan: validating plan ({total} ops)")
    validation = validate_plan(plan)
    report["validation_report"] = validation
    if not validation["passed"]:
        unreal.log("[run_plan] execute_plan: validator blocked execution")
        report["elapsed_seconds"] = time.time() - t0
        return report
    unreal.log("[run_plan] execute_plan: validation passed, dispatching ops")

    for i, op in enumerate(plan["operations"]):
        op_name = op.get("op")
        func = _OP_DISPATCH.get(op_name)
        unreal.log(f"[run_plan] op {i + 1}/{total}: {op_name} starting")
        op_t0 = time.time()

        per_op_entry = {
            "op_idx": i,
            "op": op_name,
            "result": None,
            "error": None,
        }

        if func is None:
            # Should be impossible because validate_plan already rejects
            # unknown ops, but defend against dispatch-table drift.
            per_op_entry["error"] = (
                f"no dispatch target for op {op_name!r} — drift between "
                f"plan_validator.OP_SPECS and plan_executor._OP_DISPATCH"
            )
            unreal.log_error(f"[run_plan] op {i + 1}/{total}: {per_op_entry['error']}")
            report["per_op"].append(per_op_entry)
            report["aborted_at"] = i
            report["elapsed_seconds"] = time.time() - t0
            return report

        try:
            kwargs = _prepare_kwargs(op)
        except ValueError as exc:
            per_op_entry["error"] = f"value conversion failed: {exc}"
            unreal.log_error(f"[run_plan] op {i + 1}/{total}: {per_op_entry['error']}")
            report["per_op"].append(per_op_entry)
            report["aborted_at"] = i
            report["elapsed_seconds"] = time.time() - t0
            return report

        try:
            result = func(**kwargs)
        except TypeError as exc:
            # Kwarg mismatch — library API drift or a plan key the
            # validator does not gate (e.g. a new field that squeaks
            # past the extras check).
            per_op_entry["error"] = f"library call raised TypeError: {exc}"
            unreal.log_error(f"[run_plan] op {i + 1}/{total}: {per_op_entry['error']}")
            report["per_op"].append(per_op_entry)
            report["aborted_at"] = i
            report["elapsed_seconds"] = time.time() - t0
            return report
        except Exception as exc:
            per_op_entry["error"] = (
                f"library call raised {type(exc).__name__}: {exc}"
            )
            unreal.log_error(f"[run_plan] op {i + 1}/{total}: {per_op_entry['error']}")
            report["per_op"].append(per_op_entry)
            report["aborted_at"] = i
            report["elapsed_seconds"] = time.time() - t0
            return report

        per_op_entry["result"] = result
        report["per_op"].append(per_op_entry)
        report["executed"] += 1

        op_dt = time.time() - op_t0
        if not result.get("success", False):
            unreal.log(
                f"[run_plan] op {i + 1}/{total}: {op_name} FAILED in "
                f"{op_dt:.2f}s (aborting)"
            )
            report["aborted_at"] = i
            report["elapsed_seconds"] = time.time() - t0
            return report
        unreal.log(
            f"[run_plan] op {i + 1}/{total}: {op_name} "
            f"{'skipped' if result.get('skipped') else 'ok'} ({op_dt:.2f}s)"
        )

    report["passed"] = True
    report["elapsed_seconds"] = time.time() - t0
    unreal.log(f"[run_plan] execute_plan: all {total} ops ok ({report['elapsed_seconds']:.2f}s)")
    return report


def _collect_interesting_asset_paths(plan: dict) -> set:
    """Gather every /Game/ path the diff oracle needs md5 snapshots for.

    Includes each op's predicted asset changes plus any path-based
    verification entries. Missing from the current set: assets pulled
    in by rename_asset's `new_path` when it does not yet exist — we
    still snapshot (md5 returns None for absent files, which is how
    `created` is detected post-run).
    """
    paths = set(compute_expected_changes(plan).keys())
    for entry in plan.get("verification", []):
        if "asset_exists" in entry:
            paths.add(entry["asset_exists"])
        if "asset_absent" in entry:
            paths.add(entry["asset_absent"])
        if "path" in entry and isinstance(entry["path"], list) and entry["path"]:
            head = entry["path"][0]
            if isinstance(head, str) and head.startswith("/Game/"):
                paths.add(head)
    return paths


def run_plan(plan: dict) -> dict:
    """End-to-end harness: snapshot → validate+execute → snapshot → diff.

    Single entry point for the M24 loop. Returns a combined report with
    a clear `passed` flag so LLM callers do not have to reason about
    three separate reports individually.

    Flow:
      1. Collect every /Game/ asset path the plan touches or verifies.
      2. Snapshot md5 of each.
      3. Run `execute_plan(plan)`. If blocked by validator, `passed=False`
         and `diff` is None (nothing to diff).
      4. Re-snapshot md5s.
      5. Run `mechanical_diff` against the before/after snapshots.
      6. Return combined report.

    `passed` is True iff the executor passed AND the diff passed.

    Shape:
        ``{
            "passed": bool,
            "execution": <execute_plan report>,
            "diff": <mechanical_diff report> | None,
        }``
    """
    unreal.log("[run_plan] phase 1/4: collecting asset paths + snapshotting md5s (before)")
    interesting = _collect_interesting_asset_paths(plan)
    before = snapshot_md5s(interesting)
    unreal.log(f"[run_plan] phase 1/4: snapshotted {len(interesting)} assets")

    unreal.log("[run_plan] phase 2/4: execute_plan")
    execution = execute_plan(plan)
    if not execution["passed"]:
        unreal.log("[run_plan] phase 2/4: execution did not pass — skipping diff")
        return {"passed": False, "execution": execution, "diff": None}

    unreal.log("[run_plan] phase 3/4: snapshotting md5s (after)")
    after = snapshot_md5s(interesting)

    unreal.log("[run_plan] phase 4/4: mechanical_diff")
    diff = mechanical_diff(plan, before, after)
    unreal.log(f"[run_plan] phase 4/4: diff passed={diff['passed']}")

    return {
        "passed": bool(execution["passed"] and diff["passed"]),
        "execution": execution,
        "diff": diff,
    }


def format_execution_report(report: dict) -> str:
    """Compact terminal rendering of an execute_plan report."""
    lines = []
    status = "PASSED" if report["passed"] else "FAILED"
    lines.append(
        f"Plan execution: {status} "
        f"(executed={report['executed']}, "
        f"aborted_at={report['aborted_at']}, "
        f"elapsed={report['elapsed_seconds']:.2f}s)"
    )

    vr = report.get("validation_report") or {}
    if not vr.get("passed", False):
        lines.append("")
        lines.append("Blocked by validator — no ops executed.")
        for err in vr.get("errors", []):
            lines.append(f"  - {err}")
        for entry in vr.get("per_op", []):
            if not entry.get("ok", False):
                lines.append(f"  - [{entry['op_idx']}] {entry['op']}:")
                for err in entry.get("errors", []):
                    lines.append(f"      {err}")
        return "\n".join(lines)

    if report["per_op"]:
        lines.append("")
        lines.append("Per-op:")
        for entry in report["per_op"]:
            idx = entry["op_idx"]
            op_name = entry["op"]
            result = entry.get("result")
            if entry.get("error"):
                lines.append(f"  [{idx}] {op_name}: ERROR — {entry['error']}")
                continue
            if result is None:
                lines.append(f"  [{idx}] {op_name}: (no result)")
                continue
            tag = "ok" if result.get("success") else "FAIL"
            if result.get("skipped"):
                tag = f"skipped ({result['skipped']})"
            lines.append(f"  [{idx}] {op_name}: {tag}")
            for err in result.get("errors", []):
                lines.append(f"      ERROR: {err}")

    return "\n".join(lines)
