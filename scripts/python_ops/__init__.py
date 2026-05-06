"""
python_ops — UE Editor Python operation library for Claude-driven asset edits.

Goes through UE's own save / compile paths via `unreal` module — no JSON
round-trip, no deserializer fidelity risk. Invoked by the MCP `apply_plan`
tool (see scripts/blueprint-exporter-mcp/).

Public API re-exported here. Import from submodules for namespaced access.

Usage pattern from an LLM-generated tuning script:

    import sys
    sys.path.insert(0, r"D:/Work/blueprintexporter/blueprint-exporter/scripts")
    from python_ops import set_bp_variable_default
    import unreal

    result = set_bp_variable_default(
        bp_path="/Game/CombatPrototype/DrewPrototype/BP_Task_Peek",
        var_name="MinMaxTimePeeking",
        value=unreal.Vector2D(0.7, 3.0),
    )
    if not result["success"]:
        unreal.log_error(f"Op failed: {result['errors']}")

Ops return a dict with the following shape:

    {
        "success": bool,
        "op": str,              # op name, e.g. "set_bp_variable_default"
        "target": str,          # asset path
        "field": str,           # property / var name touched (if applicable)
        "before": Any,          # value before the op
        "after": Any,           # value after the op
        "errors": List[str],    # empty on success
    }

Invariant: ops are idempotent — calling with the same value twice is a no-op
on the second call (detected by comparing `before` to `value`; no save if
unchanged).
"""

from .assets import (
    create_blueprint_class,
    create_child_bp,
    rename_asset,
)
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
    format_diff_report,
    md5_asset,
    mechanical_diff,
    snapshot_md5s,
)
from .plan_executor import execute_plan, format_execution_report, run_plan
from .plan_validator import format_report, validate_plan
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

__all__ = [
    "add_bp_function",
    "add_bp_interface",
    "add_bp_variable",
    "add_branch_node",
    "add_break_struct_node",
    "add_call_function_node",
    "add_component_to_scs",
    "add_custom_event_input",
    "add_custom_event_node",
    "add_dynamic_cast_node",
    "add_eqs_option",
    "add_eqs_test",
    "add_execution_sequence_node",
    "add_function_input",
    "add_function_output",
    "add_function_override",
    "add_gameplay_tag",
    "add_local_variable",
    "add_macro_instance_node",
    "add_make_struct_node",
    "add_set_fields_in_struct_node",
    "add_statetree_enter_condition",
    "add_statetree_task_to_state",
    "add_statetree_transition",
    "add_uds_member",
    "add_variable_get_node",
    "add_variable_set_node",
    "compute_expected_changes",
    "connect_graph_pins",
    "create_blueprint_class",
    "create_child_bp",
    "create_curve_float",
    "create_data_asset_instance",
    "create_user_defined_struct",
    "execute_plan",
    "format_diff_report",
    "format_execution_report",
    "format_report",
    "implement_interface_function",
    "md5_asset",
    "mechanical_diff",
    "remove_eqs_test",
    "remove_statetree_enter_condition",
    "remove_statetree_task_from_state",
    "remove_statetree_transition",
    "remove_uds_member",
    "rename_asset",
    "run_plan",
    "set_bp_variable_default",
    "set_component_property",
    "set_curve_float_keys",
    "set_data_asset_property",
    "set_eqs_generator_property",
    "set_eqs_test_property",
    "set_graph_pin_default",
    "set_instanced_subobject_property",
    "set_level_actor_property",
    "set_uds_member_default",
    "snapshot_md5s",
    "validate_plan",
    "verify_state_enter_conditions",
    "verify_state_tasks",
    "verify_state_transitions",
]
