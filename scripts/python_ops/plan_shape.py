"""Pure-Python shape validation for EditPlan JSON documents.

Separated from `plan_validator.py` so the MCP server (which does not
run inside UnrealEditor-Cmd.exe) can pre-validate plan JSON before
shelling out to UE. Catches the common malformed-plan classes in
<100ms:

- wrong top-level keys (missing intended_outcome / risk_level /
  operations; bad types)
- `{"op": "...", "args": {...}}` wrapper instead of flattened kwargs
- unknown op names
- missing required kwargs
- verification entries with the wrong shape

Design constraint: NO `import unreal`. Imports that need UE (live asset
existence + state-path walks) stay in `plan_validator.py` and run only
after shape passes.
"""
from __future__ import annotations


ALLOWED_RISK_LEVELS = {"low", "medium", "high"}

# Metadata fields permitted on any op (stripped by the executor before
# kwargs dispatch; informational only).
OP_META_KEYS = {"op", "_comment", "idempotency_key"}

# Per-op contract:
#   required       - kwargs that must be present
#   optional       - kwargs that may be present with a default applied by
#                    the library op (validator won't reject them as extras)
#   assets         - kwargs whose value is a /Game/ path expected to EXIST
#   assets_absent  - kwargs whose value is a /Game/ path expected to NOT exist
#   state_paths    - list of {asset_key, path_key} entries - each kwarg
#                    named by path_key is a ResolvePath list into StateTree
#                    editor data of the asset named by asset_key (the
#                    UE-backed validator walks each read-only via
#                    unreal.BpxReflectionOps)
OP_SPECS = {
    "set_bp_variable_default": {
        "required": ["bp_path", "var_name", "value"],
        "assets": ["bp_path"],
    },
    "set_component_property": {
        "required": ["bp_path", "component_name", "property_name", "value"],
        "assets": ["bp_path"],
    },
    "set_instanced_subobject_property": {
        "required": ["bp_path", "path", "property_name", "value"],
        "assets": ["bp_path"],
    },
    "create_child_bp": {
        "required": ["parent_bp_path", "new_bp_path"],
        "assets": ["parent_bp_path"],
        "assets_absent": ["new_bp_path"],
    },
    # M28.10.1 — superset of create_child_bp; accepts native /Script/<Module>.<Class>
    # parents in addition to BP /Game/.../BP[._C] forms. parent_path is NOT in
    # `assets` because native paths don't exist as /Game/ assets; the bridge
    # validates the resolved UClass via FKismetEditorUtilities::CanCreateBlueprintOfClass.
    "create_blueprint_class": {
        "required": ["parent_path", "new_bp_path"],
        "assets_absent": ["new_bp_path"],
    },
    "rename_asset": {
        "required": ["old_path", "new_path"],
        "assets": ["old_path"],
        "assets_absent": ["new_path"],
    },
    "add_statetree_enter_condition": {
        "required": ["st_path", "state_path", "condition_bp_path"],
        "assets": ["st_path", "condition_bp_path"],
        "state_paths": [{"asset_key": "st_path", "path_key": "state_path"}],
    },
    "remove_statetree_enter_condition": {
        "required": ["st_path", "state_path", "condition_bp_path"],
        "assets": ["st_path", "condition_bp_path"],
        "state_paths": [{"asset_key": "st_path", "path_key": "state_path"}],
    },
    "verify_state_enter_conditions": {
        "required": ["st_path", "state_path"],
        "assets": ["st_path"],
        "state_paths": [{"asset_key": "st_path", "path_key": "state_path"}],
    },
    "add_statetree_transition": {
        "required": ["st_path", "state_path", "trigger", "target_state_path"],
        "optional": ["priority", "event_tag"],
        "assets": ["st_path"],
        "state_paths": [
            {"asset_key": "st_path", "path_key": "state_path"},
            {"asset_key": "st_path", "path_key": "target_state_path"},
        ],
    },
    "remove_statetree_transition": {
        "required": ["st_path", "state_path", "trigger", "target_state_path"],
        "assets": ["st_path"],
        "state_paths": [
            {"asset_key": "st_path", "path_key": "state_path"},
            {"asset_key": "st_path", "path_key": "target_state_path"},
        ],
    },
    "verify_state_transitions": {
        "required": ["st_path", "state_path"],
        "assets": ["st_path"],
        "state_paths": [{"asset_key": "st_path", "path_key": "state_path"}],
    },
    "add_statetree_task_to_state": {
        "required": ["st_path", "state_path", "task_bp_path"],
        "assets": ["st_path", "task_bp_path"],
        "state_paths": [{"asset_key": "st_path", "path_key": "state_path"}],
    },
    "remove_statetree_task_from_state": {
        "required": ["st_path", "state_path", "task_bp_path"],
        "assets": ["st_path", "task_bp_path"],
        "state_paths": [{"asset_key": "st_path", "path_key": "state_path"}],
    },
    "verify_state_tasks": {
        "required": ["st_path", "state_path"],
        "assets": ["st_path"],
        "state_paths": [{"asset_key": "st_path", "path_key": "state_path"}],
    },
    "implement_interface_function": {
        "required": ["bp_path", "interface_bp_path", "function_name", "output_bindings"],
        "optional": ["force_rebind"],
        "assets": ["bp_path", "interface_bp_path"],
    },
    "connect_graph_pins": {
        "required": [
            "bp_path",
            "graph_name",
            "from_node_guid",
            "from_pin",
            "to_node_guid",
            "to_pin",
        ],
        "assets": ["bp_path"],
    },
    "set_level_actor_property": {
        "required": ["level_path", "actor_label", "property_path", "value"],
        "assets": ["level_path"],
    },
    "add_bp_variable": {
        "required": ["bp_path", "var_name", "var_type_spec"],
        "optional": ["default_value", "instance_editable"],
        "assets": ["bp_path"],
    },
    "add_bp_function": {
        "required": ["bp_path", "function_name"],
        "optional": ["is_pure"],
        "assets": ["bp_path"],
    },
    # M28.12 — native virtual override authoring. function_name resolves
    # against the BP's parent class hierarchy (FindFunctionByName walks
    # ancestors); bridge rejects non-FUNC_BlueprintEvent UFUNCTIONs.
    "add_function_override": {
        "required": ["bp_path", "function_name"],
        "assets": ["bp_path"],
    },
    "add_component_to_scs": {
        "required": ["bp_path", "component_class_path", "component_name"],
        "optional": ["parent_component_name"],
        "assets": ["bp_path"],
    },
    "add_bp_interface": {
        "required": ["bp_path", "interface_class_path"],
        "assets": ["bp_path"],
    },
    "add_branch_node": {
        "required": ["bp_path", "graph_name", "position"],
        "assets": ["bp_path"],
    },
    "set_graph_pin_default": {
        "required": [
            "bp_path",
            "graph_name",
            "node_guid",
            "pin_name",
            "literal_text",
        ],
        "assets": ["bp_path"],
    },
    "add_call_function_node": {
        "required": ["bp_path", "graph_name", "function_name", "position"],
        "optional": ["target_class_path"],
        "assets": ["bp_path"],
    },
    "add_variable_get_node": {
        "required": ["bp_path", "graph_name", "variable_name", "position"],
        "optional": ["target_class_path"],
        "assets": ["bp_path"],
    },
    "add_variable_set_node": {
        "required": ["bp_path", "graph_name", "variable_name", "position"],
        "optional": ["target_class_path"],
        "assets": ["bp_path"],
    },
    "add_custom_event_node": {
        "required": ["bp_path", "graph_name", "event_name", "position"],
        "assets": ["bp_path"],
    },
    "add_execution_sequence_node": {
        "required": ["bp_path", "graph_name", "num_outputs", "position"],
        "assets": ["bp_path"],
    },
    "add_dynamic_cast_node": {
        "required": ["bp_path", "graph_name", "target_class_path", "position"],
        "assets": ["bp_path"],
    },
    # M28.13 — UK2Node_MacroInstance authoring (loop unblocker).
    "add_macro_instance_node": {
        "required": ["bp_path", "graph_name", "macro_path", "position"],
        "assets": ["bp_path"],
    },
    # M28.14 — struct-mutation node catalog (Make / Break / SetFields).
    "add_make_struct_node": {
        "required": ["bp_path", "graph_name", "struct_type_path", "position"],
        "assets": ["bp_path"],
    },
    "add_break_struct_node": {
        "required": ["bp_path", "graph_name", "struct_type_path", "position"],
        "assets": ["bp_path"],
    },
    "add_set_fields_in_struct_node": {
        "required": [
            "bp_path", "graph_name", "struct_type_path", "fields_to_show",
            "position",
        ],
        "assets": ["bp_path"],
    },
    "add_local_variable": {
        "required": ["bp_path", "function_name", "var_name", "var_type_spec"],
        "optional": ["default_value"],
        "assets": ["bp_path"],
    },
    # M28.11 — typed function / custom-event parameter authoring.
    "add_function_input": {
        "required": ["bp_path", "function_name", "pin_name", "var_type_spec"],
        "optional": ["default_value"],
        "assets": ["bp_path"],
    },
    "add_function_output": {
        # No `default_value` — Result-node output pins don't carry a runtime
        # default (BP editor suppresses the field on Result pins).
        "required": ["bp_path", "function_name", "pin_name", "var_type_spec"],
        "assets": ["bp_path"],
    },
    "add_custom_event_input": {
        "required": ["bp_path", "graph_name", "event_name", "pin_name", "var_type_spec"],
        "optional": ["default_value"],
        "assets": ["bp_path"],
    },
    "add_eqs_option": {
        "required": ["eqs_path", "generator_class_path"],
        "assets": ["eqs_path"],
    },
    "add_eqs_test": {
        "required": ["eqs_path", "option_index", "test_class_path"],
        "assets": ["eqs_path"],
    },
    "remove_eqs_test": {
        "required": ["eqs_path", "option_index", "test_index"],
        "assets": ["eqs_path"],
    },
    "set_eqs_generator_property": {
        "required": ["eqs_path", "option_index", "property_path", "value"],
        "assets": ["eqs_path"],
    },
    "set_eqs_test_property": {
        "required": [
            "eqs_path",
            "option_index",
            "test_index",
            "property_path",
            "value",
        ],
        "assets": ["eqs_path"],
    },
    "create_curve_float": {
        "required": ["curve_path"],
        "assets_absent": ["curve_path"],
    },
    "set_curve_float_keys": {
        "required": ["curve_path", "keys"],
        "assets": ["curve_path"],
    },
    "create_data_asset_instance": {
        "required": ["asset_path", "parent_class_path"],
        "assets_absent": ["asset_path"],
    },
    "set_data_asset_property": {
        "required": ["asset_path", "property_path", "value"],
        "assets": ["asset_path"],
    },
    "create_user_defined_struct": {
        "required": ["uds_path"],
        "assets_absent": ["uds_path"],
    },
    "add_uds_member": {
        "required": ["uds_path", "member_name", "var_type_spec"],
        "optional": ["default_value"],
        "assets": ["uds_path"],
    },
    "remove_uds_member": {
        "required": ["uds_path", "member_name"],
        "assets": ["uds_path"],
    },
    "set_uds_member_default": {
        "required": ["uds_path", "member_name", "value"],
        "assets": ["uds_path"],
    },
    "add_gameplay_tag": {
        # M28.6.1 — only required input is the tag itself. dev_comment
        # defaults to empty (matches DOW pattern), source_ini defaults to
        # "DefaultGameplayTags.ini" (engine-canonical project default),
        # is_restricted defaults to False (no design.md driver for the
        # restricted-tag path).
        "required": ["tag_name"],
        "optional": ["dev_comment", "source_ini", "is_restricted"],
        # No `assets` / `assets_absent` — the op writes to a Config/<X>.ini
        # file via the engine's editor module, not to a /Game/... uasset.
        # The mechanical_diff oracle correctly returns no expected
        # asset-level changes for this op (sidecars are never re-exported
        # because nothing in /Game/ moved); the M28.pre.5 verify_tag_author
        # parity gate covers the .ini-level correctness invariant.
    },
}


def _validate_top_level(plan, errors):
    """Validate the plan's outer shape. Returns True iff all required
    top-level fields are present and well-typed. On failure, appends
    messages to `errors` and returns False."""
    if not isinstance(plan, dict):
        errors.append(f"plan must be a dict, got {type(plan).__name__}")
        return False

    ok = True
    outcome = plan.get("intended_outcome")
    if not isinstance(outcome, str) or not outcome.strip():
        errors.append("`intended_outcome` must be a non-empty string")
        ok = False

    risk = plan.get("risk_level")
    if risk not in ALLOWED_RISK_LEVELS:
        errors.append(
            f"`risk_level` must be one of {sorted(ALLOWED_RISK_LEVELS)}, "
            f"got {risk!r}"
        )
        ok = False

    operations = plan.get("operations")
    if not isinstance(operations, list) or not operations:
        errors.append("`operations` must be a non-empty list")
        ok = False

    if "expected_side_effects" in plan and not isinstance(
        plan["expected_side_effects"], list
    ):
        errors.append("`expected_side_effects` must be a list when present")
        ok = False

    if "verification" in plan and not isinstance(plan["verification"], list):
        errors.append("`verification` must be a list when present")
        ok = False

    return ok


def _validate_op_shape(op, spec, errors):
    """Check the op dict has the required kwargs + only recognised extras.

    Catches the `{"op": "...", "args": {...}}` wrapper bug: if `args`
    appears as a top-level key on an op that doesn't declare it, it
    surfaces in `unknown fields` with a targeted fix hint.
    """
    allowed = (
        set(spec["required"])
        | set(spec.get("optional", ()))
        | OP_META_KEYS
    )
    actual = set(op.keys())

    missing = sorted(set(spec["required"]) - actual)
    extras = sorted(actual - allowed)

    if missing:
        errors.append(f"missing required fields: {missing}")
    if extras:
        hint = ""
        if "args" in extras:
            hint = (
                " (did you wrap the kwargs in an `args` object? each op's "
                "kwargs must be flattened into the op dict - see "
                "`plans/README.md`)"
            )
        errors.append(f"unknown fields: {extras}{hint}")

    return not missing and not extras


def _validate_verification(plan, errors):
    """Shape-check verification entries; semantic matching is the diff
    oracle's job (M24.3)."""
    for i, entry in enumerate(plan.get("verification", [])):
        prefix = f"verification[{i}]"
        if not isinstance(entry, dict):
            errors.append(f"{prefix} must be a dict")
            continue

        if "path" in entry:
            if not isinstance(entry["path"], list) or len(entry["path"]) < 2:
                errors.append(
                    f"{prefix}.path must be a list with >= 2 elements "
                    f"(asset + at least one navigation step)"
                )
            if "expected" not in entry and "expected_class" not in entry:
                errors.append(
                    f"{prefix} requires `expected` or `expected_class`"
                )
        elif "asset_exists" in entry or "asset_absent" in entry:
            key = "asset_exists" if "asset_exists" in entry else "asset_absent"
            path = entry[key]
            if not isinstance(path, str) or not path.startswith("/Game/"):
                errors.append(f"{prefix}.{key} must be a /Game/ path")
        else:
            errors.append(
                f"{prefix} has no recognized shape "
                f"(need `path+expected`, `asset_exists`, or `asset_absent`)"
            )


def validate_shape(plan) -> dict:
    """Run all non-UE-dependent checks on `plan` and return a report.

    Args:
        plan: parsed JSON plan matching the schema in `plans/README.md`.

    Returns:
        ``{
            "passed": bool,   # True iff top-level + every op shape-validates
            "errors": list,   # top-level schema / verification errors
            "warnings": list, # non-fatal concerns (reserved; currently empty)
            "per_op": [
                {"op_idx": int, "op": str, "ok": bool,
                 "errors": list, "warnings": list}
            ]
        }``

    `passed=False` means the MCP server can reject the plan without
    shelling to UE. `passed=True` does NOT mean the plan is executable -
    the UE-backed validator still needs to check asset existence and
    state-path resolvability.
    """
    top_errors: list = []
    top_warnings: list = []
    per_op: list = []

    if not _validate_top_level(plan, top_errors):
        return {
            "passed": False,
            "errors": top_errors,
            "warnings": top_warnings,
            "per_op": [],
        }

    for i, op in enumerate(plan.get("operations", [])):
        errs: list = []
        warns: list = []

        op_name = op.get("op") if isinstance(op, dict) else None

        if not isinstance(op, dict):
            errs.append(f"operations[{i}] must be a dict, got {type(op).__name__}")
        elif op_name not in OP_SPECS:
            errs.append(
                f"unknown op: {op_name!r} - known ops: {sorted(OP_SPECS)}"
            )
        else:
            spec = OP_SPECS[op_name]
            _validate_op_shape(op, spec, errs)

        per_op.append(
            {
                "op_idx": i,
                "op": op_name or "<unknown>",
                "ok": not errs,
                "errors": errs,
                "warnings": warns,
            }
        )

    _validate_verification(plan, top_errors)

    passed = not top_errors and all(entry["ok"] for entry in per_op)
    return {
        "passed": passed,
        "errors": top_errors,
        "warnings": top_warnings,
        "per_op": per_op,
    }


def format_shape_report(report: dict) -> str:
    """Human-readable rendering of a validate_shape report."""
    lines = []
    status = "PASSED" if report["passed"] else "FAILED"
    lines.append(f"Plan shape validation: {status}")

    if report["errors"]:
        lines.append("")
        lines.append("Top-level errors:")
        for err in report["errors"]:
            lines.append(f"  - {err}")

    if report["warnings"]:
        lines.append("")
        lines.append("Top-level warnings:")
        for warn in report["warnings"]:
            lines.append(f"  - {warn}")

    if report["per_op"]:
        lines.append("")
        lines.append("Per-op:")
        for entry in report["per_op"]:
            tag = "ok" if entry["ok"] else "FAIL"
            lines.append(f"  [{entry['op_idx']}] {entry['op']}: {tag}")
            for err in entry["errors"]:
                lines.append(f"      ERROR: {err}")
            for warn in entry["warnings"]:
                lines.append(f"      warn:  {warn}")

    return "\n".join(lines)
