"""Mechanical diff + verification oracle (M24.3).

Compares observed post-execution state to what a plan's ops predicted,
then runs each `verification[]` entry via the reflection bridge. Called
from `run_plan()` (in plan_executor.py) after `execute_plan()` returns.

Scope trade-offs:

- Change detection uses md5 of on-disk .uasset bytes. Not the field-
  level diff the WIP M24.3 scope mentioned (DeepDump-over-.deep.md-
  outputs). md5 captures the 80%-value signal cheaply without shelling
  out to the DeepDump commandlet for every asset on every plan run;
  field-level coverage lives in the `verification[]` block, which this
  oracle executes via the bridge's `get_property_value` /
  `get_object_property_value`. If a specific fine-grained equality
  matters, put it in `verification[]` — that is what the schema is for.

- The `expected_side_effects` prose field is NOT parsed. Per the M24.0
  schema doc it is for human review only. The expected change set is
  DERIVED from each op's target fields via a fixed table below.
"""

import hashlib
import os

import unreal


def _op_expected_changes(op: dict):
    """Return a list of ``(asset_path, kind)`` tuples for this op.

    Kind is ``"mutated"`` (content change), ``"created"`` (new asset),
    or ``"deleted"`` (asset removed). Unknown ops return an empty list
    — the validator has already rejected those by the time we get here.

    Robust to malformed ops: if the kwarg a given op expects is missing
    (e.g., an agent produced ``{"op": "...", "args": {...}}`` instead of
    the flattened shape), returns ``[]`` rather than raising ``KeyError``.
    The downstream validator will then reject the plan with a clean
    structured error instead of the pre-flight crashing this helper.
    """
    name = op.get("op", "")

    def _pick(*keys):
        """Return (value, True) for the first present key, else (None, False)."""
        for k in keys:
            if k in op:
                return op[k], True
        return None, False

    if name in (
        "set_bp_variable_default",
        "set_component_property",
        "set_instanced_subobject_property",
        "add_bp_variable",
        "add_bp_function",
        "add_function_override",
        "add_component_to_scs",
        "add_bp_interface",
    ):
        v, ok = _pick("bp_path")
        return [(v, "mutated")] if ok else []
    if name == "create_child_bp":
        v, ok = _pick("new_bp_path")
        return [(v, "created")] if ok else []
    if name == "create_blueprint_class":
        v, ok = _pick("new_bp_path")
        return [(v, "created")] if ok else []
    if name == "rename_asset":
        changes = []
        old_v, old_ok = _pick("old_path")
        new_v, new_ok = _pick("new_path")
        if old_ok:
            changes.append((old_v, "deleted"))
        if new_ok:
            changes.append((new_v, "created"))
        return changes
    if name in (
        "add_statetree_enter_condition",
        "remove_statetree_enter_condition",
        "add_statetree_transition",
        "remove_statetree_transition",
        "add_statetree_task_to_state",
        "remove_statetree_task_from_state",
    ):
        v, ok = _pick("st_path")
        return [(v, "mutated")] if ok else []
    if name in (
        "implement_interface_function",
        "connect_graph_pins",
        "add_branch_node",
        "set_graph_pin_default",
        "add_call_function_node",
        "add_variable_get_node",
        "add_variable_set_node",
        "add_custom_event_node",
        "add_execution_sequence_node",
        "add_dynamic_cast_node",
        # M28.13 — UK2Node_MacroInstance authoring (loop unblocker).
        "add_macro_instance_node",
        # M28.14 — struct-mutation node catalog (Make / Break / SetFields).
        "add_make_struct_node",
        "add_break_struct_node",
        "add_set_fields_in_struct_node",
        "add_local_variable",
        # M28.11 typed function / custom-event parameter authoring — all
        # mutate the BP asset (Entry / Result / CustomEvent UserDefinedPins).
        "add_function_input",
        "add_function_output",
        "add_custom_event_input",
    ):
        v, ok = _pick("bp_path")
        return [(v, "mutated")] if ok else []
    if name == "set_level_actor_property":
        v, ok = _pick("level_path")
        return [(v, "mutated")] if ok else []
    if name == "add_eqs_option":
        v, ok = _pick("eqs_path")
        return [(v, "mutated")] if ok else []
    if name == "add_eqs_test":
        v, ok = _pick("eqs_path")
        return [(v, "mutated")] if ok else []
    if name == "remove_eqs_test":
        v, ok = _pick("eqs_path")
        return [(v, "mutated")] if ok else []
    if name == "set_eqs_generator_property":
        v, ok = _pick("eqs_path")
        return [(v, "mutated")] if ok else []
    if name == "set_eqs_test_property":
        v, ok = _pick("eqs_path")
        return [(v, "mutated")] if ok else []
    if name == "create_curve_float":
        v, ok = _pick("curve_path")
        return [(v, "created")] if ok else []
    if name == "set_curve_float_keys":
        v, ok = _pick("curve_path")
        return [(v, "mutated")] if ok else []
    if name == "create_data_asset_instance":
        v, ok = _pick("asset_path")
        return [(v, "created")] if ok else []
    if name == "set_data_asset_property":
        v, ok = _pick("asset_path")
        return [(v, "mutated")] if ok else []
    if name == "create_user_defined_struct":
        v, ok = _pick("uds_path")
        return [(v, "created")] if ok else []
    if name == "add_uds_member":
        v, ok = _pick("uds_path")
        return [(v, "mutated")] if ok else []
    if name == "remove_uds_member":
        v, ok = _pick("uds_path")
        return [(v, "mutated")] if ok else []
    if name == "set_uds_member_default":
        v, ok = _pick("uds_path")
        return [(v, "mutated")] if ok else []
    # Read-only ops — known to the validator, no expected mutation.
    if name in (
        "verify_state_enter_conditions",
        "verify_state_transitions",
        "verify_state_tasks",
    ):
        return []
    # M28.6.1 — add_gameplay_tag writes to a Config/<X>.ini text file, not
    # a /Game/... uasset. mechanical_diff snapshots .uasset md5s only, so
    # there's no expected asset-level change here. Correctness of the .ini
    # write is covered by the M28.pre.5 verify_tag_author.py parity gate
    # (snapshot ini bytes → list_gameplay_tags → add → list → diff
    # --numstat asserts exactly one line added; re-add is a no-op).
    if name == "add_gameplay_tag":
        return []
    return []


_STRUCTURAL_KINDS = {"created", "deleted"}


def _combine_kinds(prior, new):
    """Combine an asset's existing expected kind with a new op's kind.

    Structural kinds (``"created"`` / ``"deleted"``) dominate
    ``"mutated"``. A plan that creates an asset at op N and then mutates
    it at op N+M still leaves a single observed effect — null→bytes —
    that the oracle classifies as ``"created"``. The expected kind must
    mirror that observation, not get overwritten to ``"mutated"`` by
    the later op.

    Same logic mirrored for delete: a plan that mutates and then
    deletes the same asset is observed as ``"deleted"`` (bytes → null),
    so a prior ``"deleted"`` is not downgraded by a subsequent
    ``"mutated"``.

    Sequences without a structural prior fall through to "last wins"
    semantics — e.g. mutated-then-created stays ``"created"`` (rare,
    typically only produced when a plan recreates a previously-mutated
    asset; observed will be ``"created"`` if before-md5 was None at
    the time the snapshot ran, or ``"mutated"`` otherwise; either way
    last-wins is the safer default).
    """
    if prior in _STRUCTURAL_KINDS and new == "mutated":
        return prior
    return new


def compute_expected_changes(plan: dict) -> dict:
    """Collapse every op's expected changes into a single dict.

    Walks ops in order, combining each op's per-asset kind through
    ``_combine_kinds`` so create-then-mutate sequences on the same
    path collapse to ``"created"`` (the observed null→bytes effect)
    and not the last op's ``"mutated"``. Disjoint-path sequences
    are unaffected — e.g. ``create_child_bp /Game/X`` followed by
    ``rename_asset old=X new=Y`` still produces ``X="deleted"`` and
    ``Y="created"`` as before.
    """
    changes = {}
    for op in plan.get("operations", []):
        for asset, kind in _op_expected_changes(op):
            changes[asset] = _combine_kinds(changes.get(asset), kind)
    return changes


def _game_path_to_fs(game_path: str):
    """Convert a ``/Game/...`` asset path to the absolute .uasset file
    path. Returns None if the input is not under ``/Game/``."""
    if not game_path.startswith("/Game/"):
        return None
    content_dir = unreal.Paths.project_content_dir()
    relative = game_path[len("/Game/") :]
    return os.path.normpath(os.path.join(content_dir, relative + ".uasset"))


def md5_asset(game_path: str):
    """Read a ``/Game/`` asset's .uasset file and return its md5 hex
    digest. Returns None if the file does not exist (useful signal for
    created/deleted assets — pass through unchanged)."""
    fs_path = _game_path_to_fs(game_path)
    if fs_path is None or not os.path.isfile(fs_path):
        return None
    h = hashlib.md5()
    with open(fs_path, "rb") as fp:
        for chunk in iter(lambda: fp.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def snapshot_md5s(asset_paths) -> dict:
    """Compute md5 for a collection of ``/Game/`` paths.

    Absent assets map to None. Duplicates are deduped. Order-independent
    — the returned dict lets caller compare before/after dicts directly.
    """
    return {p: md5_asset(p) for p in sorted(set(asset_paths))}


def _format_expected(expected) -> str:
    """Render the `expected` value of a verification entry as the same
    ExportText form `get_property_value` returns, so string equality
    covers the common cases (bool / int / float / str)."""
    if isinstance(expected, bool):
        return "true" if expected else "false"
    if isinstance(expected, (int, float)):
        return str(expected)
    return str(expected)


def _run_verification_entry(entry: dict, entry_idx: int) -> dict:
    """Execute a single verification[] entry, returning a result dict."""
    asset_lib = unreal.EditorAssetLibrary
    ops = unreal.BpxReflectionOps

    result = {
        "entry_idx": entry_idx,
        "entry": entry,
        "passed": False,
        "got": None,
        "error": None,
    }

    if "asset_exists" in entry:
        path = entry["asset_exists"]
        got = asset_lib.does_asset_exist(path)
        result["got"] = got
        result["passed"] = bool(got)
        if not got:
            result["error"] = f"asset does not exist: {path}"
        return result

    if "asset_absent" in entry:
        path = entry["asset_absent"]
        got = asset_lib.does_asset_exist(path)
        result["got"] = got
        result["passed"] = not got
        if got:
            result["error"] = f"asset still exists: {path}"
        return result

    if "path" in entry:
        path = entry["path"]
        if not isinstance(path, list) or len(path) < 2:
            result["error"] = "`path` must be [asset_path, step1, ...]"
            return result

        asset_path, nav = path[0], path[1:]
        asset = unreal.load_asset(asset_path)
        if asset is None:
            result["error"] = f"load_asset returned None for {asset_path}"
            return result

        if "expected_class" in entry:
            obj = ops.get_object_property_value(asset, nav)
            if obj is None:
                result["got"] = None
                result["error"] = f"path resolved to None; expected object of class {entry['expected_class']!r}"
                return result
            got_class = obj.get_class().get_path_name()
            result["got"] = got_class
            result["passed"] = got_class == entry["expected_class"]
            if not result["passed"]:
                result["error"] = (
                    f"class mismatch: got {got_class}, "
                    f"expected {entry['expected_class']}"
                )
            return result

        if "expected" not in entry:
            result["error"] = "`path` entry needs `expected` or `expected_class`"
            return result

        r = ops.get_property_value(asset, nav)
        if not r.success:
            result["error"] = f"get_property_value failed: {r.error_message}"
            return result

        expected_str = _format_expected(entry["expected"])
        result["got"] = r.before_text
        result["passed"] = r.before_text == expected_str
        if not result["passed"]:
            result["error"] = (
                f"value mismatch: got {r.before_text!r}, expected {expected_str!r}"
            )
        return result

    result["error"] = "unrecognized verification shape"
    return result


def _run_verification(plan: dict):
    """Run every verification[] entry. Returns list of result dicts."""
    return [
        _run_verification_entry(entry, i)
        for i, entry in enumerate(plan.get("verification", []))
    ]


def mechanical_diff(plan: dict, before_md5s: dict, after_md5s: dict) -> dict:
    """Compute the mechanical diff + verification report.

    Args:
        plan: the EditPlan dict.
        before_md5s: ``{/Game/ path: md5 or None}`` captured before execution.
        after_md5s: same structure, captured after execution.

    Returns:
        ``{
            "passed": bool,                # True iff no unexpected changes AND verification passes
            "asset_changes": list,         # one per affected asset
            "unexpected_changes": list,    # observed kind != expected kind
            "expected_but_missing": list,  # expected kind but observed stable
            "verification_results": list,
        }``

    `expected_but_missing` is NOT fatal by default — idempotent-skip
    ops (replaying the same plan twice, value already matches target)
    leave the asset stable even though the plan expected a mutation.
    `passed` is driven by `unexpected_changes` (fatal) and
    `verification_results` (each entry must pass).
    """
    expected = compute_expected_changes(plan)
    all_assets = set(expected) | set(before_md5s) | set(after_md5s)

    asset_changes = []
    unexpected = []
    expected_missing = []

    for asset in sorted(all_assets):
        before = before_md5s.get(asset)
        after = after_md5s.get(asset)

        if before is None and after is not None:
            observed = "created"
        elif before is not None and after is None:
            observed = "deleted"
        elif before != after:
            observed = "mutated"
        else:
            observed = "stable"

        expected_kind = expected.get(asset)
        was_expected = (observed == expected_kind) or (
            observed == "stable" and expected_kind is None
        )

        entry = {
            "asset": asset,
            "observed": observed,
            "expected": expected_kind,
            "md5_before": before,
            "md5_after": after,
            "was_expected": was_expected,
        }
        asset_changes.append(entry)

        if observed != "stable" and observed != expected_kind:
            unexpected.append(entry)
        if expected_kind is not None and observed == "stable":
            expected_missing.append(entry)

    verification_results = _run_verification(plan)
    verification_passed = all(r["passed"] for r in verification_results)

    passed = not unexpected and verification_passed

    return {
        "passed": passed,
        "asset_changes": asset_changes,
        "unexpected_changes": unexpected,
        "expected_but_missing": expected_missing,
        "verification_results": verification_results,
    }


def format_diff_report(report: dict) -> str:
    """Compact terminal rendering of a mechanical_diff report."""
    lines = []
    status = "PASSED" if report["passed"] else "FAILED"
    lines.append(f"Mechanical diff: {status}")

    if report["unexpected_changes"]:
        lines.append("")
        lines.append(
            f"Unexpected changes ({len(report['unexpected_changes'])}):"
        )
        for entry in report["unexpected_changes"]:
            lines.append(
                f"  - {entry['asset']}: "
                f"observed={entry['observed']}, expected={entry['expected']}"
            )

    if report["expected_but_missing"]:
        lines.append("")
        lines.append(
            f"Predicted but stable ({len(report['expected_but_missing'])}):"
        )
        for entry in report["expected_but_missing"]:
            lines.append(
                f"  - {entry['asset']}: expected {entry['expected']}, "
                f"observed stable (idempotent skip?)"
            )

    if report["verification_results"]:
        lines.append("")
        lines.append("Verification:")
        for r in report["verification_results"]:
            tag = "ok" if r["passed"] else "FAIL"
            lines.append(f"  [{r['entry_idx']}] {tag}")
            if r["error"]:
                lines.append(f"      {r['error']}")

    return "\n".join(lines)
