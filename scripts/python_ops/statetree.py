"""StateTree condition / transition ops via the M23 reflection bridge.

These mutate editor-time StateTree state that UE 5.7's Python reflection
marks as protected (SubTrees, Children, EnterConditions, Transitions) —
so they go through `unreal.BpxReflectionOps` rather than the default
`get_editor_property` / `set_editor_property` path.

Canonical workflow — `add_statetree_enter_condition`:
    1. Resolve StateTreeEditorData subobject of the asset
    2. Walk to the target state UObject via `state_path`
    3. Idempotence check: any existing EnterCondition whose `InstanceObject`
       is of the requested BP's generated class → skipped
    4. Append a default `FStateTreeEditorNode` to `EnterConditions`
    5. Init `Node` FInstancedStruct as `FStateTreeBlueprintConditionWrapper`
    6. Set `Node.ConditionClass` to the BP's generated class (via bridge's
       FInstancedStruct descent — M23.1.1)
    7. Set editor-node `ID` to a deterministic 32-char md5 so re-runs stay
       identical on disk modulo UE's own compile cosmetics
    8. `NewObject` the BP instance outered to the state (Instanced-property
       invariant — InstanceObject would null on reload otherwise)
    9. Set `InstanceObject` → new instance (fires `PostEditChangeChainProperty`
       on the innermost owner — M23.1.1 load-bearing for persistence)
    10. Compile + save package

This is the first library op that exercises the full M23.1.1 chain; proves
the reflection bridge can stand in for UE's editor drag-drop for a
non-trivial editor-data mutation.
"""

import hashlib

import unreal

from ._common import make_result


WRAPPER_STRUCT_PATH = "/Script/StateTreeModule.StateTreeBlueprintConditionWrapper"

# M28.1 — task-on-state ops. UStateTreeState::Tasks is an array of
# FStateTreeEditorNode whose Node struct holds a FStateTreeBlueprintTaskWrapper
# when the task is BP-backed; the wrapper carries a TaskClass field (mirror of
# FStateTreeBlueprintConditionWrapper::ConditionClass).
TASK_WRAPPER_STRUCT_PATH = "/Script/StateTreeModule.StateTreeBlueprintTaskWrapper"


VALID_TRANSITION_TRIGGERS = (
    "OnStateCompleted",
    "OnStateSucceeded",
    "OnStateFailed",
    "OnTick",
    "OnEvent",
)

VALID_TRANSITION_PRIORITIES = (
    "Critical",
    "High",
    "Normal",
    "Low",
)


def _ops():
    return unreal.BpxReflectionOps


def _format_state_path(state_path) -> str:
    """Render a path list like ``["SubTrees", "[2]", "Children", "[3]"]`` as the
    compact human form ``SubTrees[2].Children[3]`` for result messages.
    Arrays ("[N]") fuse onto the preceding property; normal steps dot-join.
    """
    out = []
    for step in state_path:
        s = str(step)
        if s.startswith("[") and s.endswith("]") and out:
            out[-1] = out[-1] + s
        else:
            out.append(s)
    return ".".join(out)


def _deterministic_guid(*parts) -> str:
    """32-char uppercase hex md5 over ':'-joined parts. This is the format
    UE's FGuid::Parse accepts without braces or dashes."""
    joined = ":".join(str(p) for p in parts)
    return hashlib.md5(joined.encode("utf-8")).hexdigest().upper()


def _load_st_and_editor_data(st_path: str, result: dict):
    """Load a UStateTree + resolve its StateTreeEditorData subobject.

    Returns ``(st, ed)`` on success, ``(None, None)`` with errors appended
    otherwise. Uses the bridge's `find_subobject` which does a
    starts-with name match so "StateTreeEditorData_0" / "_1" / etc all hit.
    """
    if not st_path.startswith("/Game/"):
        result["errors"].append(f"st_path must start with /Game/: {st_path!r}")
        return None, None
    st = unreal.load_asset(st_path)
    if st is None:
        result["errors"].append(f"load_asset returned None for {st_path!r}")
        return None, None
    ed = _ops().find_subobject(st, unreal.Name("StateTreeEditorData"))
    if ed is None:
        result["errors"].append(
            f"no StateTreeEditorData subobject reachable from {st_path!r}"
        )
        return None, None
    return st, ed


def _resolve_condition_class(condition_bp_path: str, result: dict):
    """Load a BP and return its generated class. Validates /Game/ prefix and
    UBlueprint type. Returns None with errors on failure."""
    if not condition_bp_path.startswith("/Game/"):
        result["errors"].append(
            f"condition_bp_path must start with /Game/: {condition_bp_path!r}"
        )
        return None
    cond_bp = unreal.load_asset(condition_bp_path)
    if cond_bp is None or not isinstance(cond_bp, unreal.Blueprint):
        result["errors"].append(f"not a Blueprint at {condition_bp_path!r}")
        return None
    cond_class = cond_bp.generated_class()
    if cond_class is None:
        result["errors"].append(
            f"condition BP has no generated_class: {condition_bp_path!r}"
        )
        return None
    return cond_class


def add_statetree_enter_condition(
    st_path: str,
    state_path: list,
    condition_bp_path: str,
):
    """Append a Blueprint-backed condition to a state's EnterConditions array.

    Args:
        st_path: ``/Game/...`` path to the UStateTree asset.
        state_path: nav list from StateTreeEditorData to the target
            UStateTreeState. Example for ``ST_EnemyBase.Peek``:
            ``["SubTrees", "[2]", "Children", "[3]"]``.
        condition_bp_path: ``/Game/...`` path to a Blueprint whose parent is
            ``UStateTreeConditionBlueprintBase``.

    Returns:
        Standard op result dict. ``before`` / ``after`` carry
        ``{ec_len, idx}`` snapshots; ``skipped`` is present when an
        existing entry already matches the condition class.

    Idempotent: if the state's ``EnterConditions`` already contains an
    entry whose ``InstanceObject`` is of the requested BP's generated class,
    returns success with a ``skipped`` reason and does not save.
    """
    result = make_result(
        "add_statetree_enter_condition",
        st_path,
        f"{_format_state_path(state_path)} += {condition_bp_path}",
    )

    st, ed = _load_st_and_editor_data(st_path, result)
    if st is None:
        return result

    wrapper = unreal.find_object(None, WRAPPER_STRUCT_PATH)
    if wrapper is None:
        result["errors"].append(
            f"{WRAPPER_STRUCT_PATH} not found — is StateTreeModule loaded?"
        )
        return result

    cond_class = _resolve_condition_class(condition_bp_path, result)
    if cond_class is None:
        return result
    cond_class_path = cond_class.get_path_name()

    ops = _ops()

    state_obj = ops.get_object_property_value(ed, state_path)
    if state_obj is None:
        result["errors"].append(
            f"state_path {state_path!r} did not resolve to a UObject"
        )
        return result

    ec_path = list(state_path) + ["EnterConditions"]
    ec_len = ops.get_array_length(ed, ec_path)
    if ec_len < 0:
        result["errors"].append(
            f"can't read EnterConditions length at {_format_state_path(state_path)!r}"
        )
        return result
    result["before"] = {"ec_len": ec_len}

    for i in range(ec_len):
        io = ops.get_object_property_value(
            ed, ec_path + [f"[{i}]", "InstanceObject"]
        )
        if io is not None and io.get_class().get_path_name() == cond_class_path:
            result["after"] = {"ec_len": ec_len, "idx": i}
            result["success"] = True
            result["skipped"] = (
                f"{cond_class_path} already present at index {i}"
            )
            return result

    new_idx = ops.array_append_new_element(ed, ec_path)
    if new_idx < 0:
        result["errors"].append("array_append_new_element returned -1")
        return result
    elem_path = ec_path + [f"[{new_idx}]"]

    r = ops.set_instanced_struct_type(ed, elem_path + ["Node"], wrapper)
    if not r.success:
        result["errors"].append(
            f"set_instanced_struct_type failed: {r.error_message}"
        )
        return result

    r = ops.set_object_property_value(
        ed, elem_path + ["Node", "ConditionClass"], cond_class
    )
    if not r.success:
        result["errors"].append(f"set ConditionClass failed: {r.error_message}")
        return result

    guid = _deterministic_guid(
        st_path, _format_state_path(state_path), cond_class_path
    )
    r = ops.set_property_value(ed, elem_path + ["ID"], guid)
    if not r.success:
        result["errors"].append(f"set ID failed: {r.error_message}")
        return result

    cond_instance = ops.new_subobject(state_obj, cond_class, unreal.Name(""))
    if cond_instance is None:
        result["errors"].append("new_subobject returned None")
        return result

    r = ops.set_object_property_value(
        ed, elem_path + ["InstanceObject"], cond_instance
    )
    if not r.success:
        result["errors"].append(f"set InstanceObject failed: {r.error_message}")
        return result

    if not ops.compile_and_save_package(st):
        result["errors"].append("compile_and_save_package returned False")
        return result

    result["after"] = {
        "ec_len": ec_len + 1,
        "idx": new_idx,
        "instance": cond_instance.get_path_name(),
    }
    result["success"] = True
    return result


def verify_state_enter_conditions(
    st_path: str,
    state_path: list,
):
    """Read the current EnterConditions list at a state. Read-only.

    Args:
        st_path: ``/Game/...`` path to the UStateTree asset.
        state_path: nav list from StateTreeEditorData to the target
            UStateTreeState — same format as
            ``add_statetree_enter_condition``. Works for both root
            states (``["SubTrees", "[2]"]``) and nested states
            (``["SubTrees", "[2]", "Children", "[3]"]``).

    Returns:
        Standard op result dict. ``after`` carries the structured
        EnterConditions read-back:
        ``{ec_len, entries: [{idx, class_path, instance_path}]}``.
        Entries with ``InstanceObject == None`` still appear with
        ``class_path`` / ``instance_path`` set to ``None`` so plan
        authors see exactly what's on disk.

    Canonical read-back for a state's EnterConditions. Raw
    ``verification[]`` entries of the form
    ``[<st>, 'StateTreeEditorData:SubTrees', ..., 'InstanceObject']``
    do not resolve through the bridge's path-walker: the colon
    notation was only ever a doc convention and
    ``BpxReflectionOps::ResolvePath`` walks one UPROPERTY per step.
    Call this op in ``operations[]`` instead — it uses the op-side
    ``state_path`` nav format (same as ``add_`` / ``remove_``) and
    records the live EC list in the execution report for both root
    and nested states.

    Plans can either:
      - include this op after a mutating op to capture the post-edit
        state in their own run report, OR
      - invoke it directly as a one-op plan to diagnose EC state.
    Read-only — no compile, no save, no mutation.
    """
    result = make_result(
        "verify_state_enter_conditions",
        st_path,
        _format_state_path(state_path),
    )

    st, ed = _load_st_and_editor_data(st_path, result)
    if st is None:
        return result

    ops = _ops()

    state_obj = ops.get_object_property_value(ed, state_path)
    if state_obj is None:
        result["errors"].append(
            f"state_path {state_path!r} did not resolve to a UObject"
        )
        return result

    ec_path = list(state_path) + ["EnterConditions"]
    ec_len = ops.get_array_length(ed, ec_path)
    if ec_len < 0:
        result["errors"].append(
            f"can't read EnterConditions length at {_format_state_path(state_path)!r}"
        )
        return result

    entries = []
    for i in range(ec_len):
        io = ops.get_object_property_value(
            ed, ec_path + [f"[{i}]", "InstanceObject"]
        )
        if io is None:
            entries.append({"idx": i, "class_path": None, "instance_path": None})
            continue
        entries.append(
            {
                "idx": i,
                "class_path": io.get_class().get_path_name(),
                "instance_path": io.get_path_name(),
            }
        )

    result["before"] = {"ec_len": ec_len}
    result["after"] = {"ec_len": ec_len, "entries": entries}
    result["success"] = True
    return result


def remove_statetree_enter_condition(
    st_path: str,
    state_path: list,
    condition_bp_path: str,
):
    """Remove the first EnterCondition entry whose InstanceObject is of
    ``condition_bp_path``'s generated class.

    No-op when no matching entry exists (returns success with ``skipped``
    describing the class that was searched for).
    """
    result = make_result(
        "remove_statetree_enter_condition",
        st_path,
        f"{_format_state_path(state_path)} -= {condition_bp_path}",
    )

    st, ed = _load_st_and_editor_data(st_path, result)
    if st is None:
        return result

    cond_class = _resolve_condition_class(condition_bp_path, result)
    if cond_class is None:
        return result
    cond_class_path = cond_class.get_path_name()

    ops = _ops()
    ec_path = list(state_path) + ["EnterConditions"]
    ec_len = ops.get_array_length(ed, ec_path)
    if ec_len < 0:
        result["errors"].append(
            f"can't read EnterConditions length at {_format_state_path(state_path)!r}"
        )
        return result
    result["before"] = {"ec_len": ec_len}

    for i in range(ec_len):
        io = ops.get_object_property_value(
            ed, ec_path + [f"[{i}]", "InstanceObject"]
        )
        if io is not None and io.get_class().get_path_name() == cond_class_path:
            r = ops.array_remove_at(ed, ec_path, i)
            if not r.success:
                result["errors"].append(
                    f"array_remove_at({i}) failed: {r.error_message}"
                )
                return result
            if not ops.compile_and_save_package(st):
                result["errors"].append(
                    "compile_and_save_package returned False"
                )
                return result
            result["after"] = {"ec_len": ec_len - 1, "removed_idx": i}
            result["success"] = True
            return result

    result["after"] = {"ec_len": ec_len}
    result["success"] = True
    result["skipped"] = f"no entry with class {cond_class_path} found"
    return result


def _resolve_target_state(ed, target_state_path: list, result: dict):
    """Walk ``target_state_path`` from StateTreeEditorData and return
    ``(target_obj, target_guid, target_name)``.

    The GUID is the target state's ``ID`` field read as ExportText (32-char
    uppercase hex, matches the format ImportText accepts for FGuid writes).
    The name is the state's ``Name`` field for display-only use on the
    resulting ``FStateTreeStateLink.Name``.

    Returns ``(None, None, None)`` with errors appended on failure.
    """
    ops = _ops()
    target = ops.get_object_property_value(ed, target_state_path)
    if target is None:
        result["errors"].append(
            f"target_state_path {target_state_path!r} did not resolve to a UObject"
        )
        return None, None, None
    id_res = ops.get_property_value(target, ["ID"])
    if not id_res.success:
        result["errors"].append(
            f"reading ID on target state failed: {id_res.error_message}"
        )
        return None, None, None
    name_res = ops.get_property_value(target, ["Name"])
    target_name = name_res.after_text if name_res.success else ""
    return target, id_res.after_text, target_name


def add_statetree_transition(
    st_path: str,
    state_path: list,
    trigger: str,
    target_state_path: list,
    priority: str = "Normal",
    event_tag: str = "",
):
    """Append a new ``FStateTreeTransition`` to a state's ``Transitions`` array.

    Args:
        st_path: ``/Game/...`` path to the UStateTree asset.
        state_path: nav list from StateTreeEditorData to the SOURCE state
            UObject — same format as :func:`add_statetree_enter_condition`.
        trigger: one of ``OnStateCompleted`` / ``OnStateSucceeded`` /
            ``OnStateFailed`` / ``OnTick`` / ``OnEvent``.
        target_state_path: nav list to the TARGET state UObject (same format
            as ``state_path``). Read-only: the op reads the target's ``ID``
            (FGuid) + ``Name`` (FName) to populate the new transition's
            ``FStateTreeStateLink`` with ``LinkType=GotoState``.
            Non-``GotoState`` link types (``Succeeded`` / ``Failed`` /
            ``NextState`` / etc.) are not currently supported by this op.
        priority: ``Critical`` / ``High`` / ``Normal`` / ``Low``. Default ``Normal``.
        event_tag: gameplay tag name (e.g. ``"AI.TargetSpotted"``) — required
            when ``trigger=OnEvent``, must be empty otherwise.

    Returns:
        Standard op result dict. ``before``/``after`` carry
        ``{t_len, idx}`` snapshots. ``skipped`` is present when an identical
        transition already exists on the source state.

    Idempotent: if the state's ``Transitions`` array already contains a
    transition with matching ``(Trigger, State.ID)`` — plus matching
    ``RequiredEvent.Tag`` when ``trigger=OnEvent`` — returns success with a
    ``skipped`` reason and does not save.
    """
    result = make_result(
        "add_statetree_transition",
        st_path,
        f"{_format_state_path(state_path)} -[{trigger}]-> {_format_state_path(target_state_path)}",
    )

    if trigger not in VALID_TRANSITION_TRIGGERS:
        result["errors"].append(
            f"invalid trigger {trigger!r}; must be one of {list(VALID_TRANSITION_TRIGGERS)}"
        )
        return result
    if priority not in VALID_TRANSITION_PRIORITIES:
        result["errors"].append(
            f"invalid priority {priority!r}; must be one of {list(VALID_TRANSITION_PRIORITIES)}"
        )
        return result
    if trigger == "OnEvent" and not event_tag:
        result["errors"].append(
            "trigger=OnEvent requires a non-empty event_tag"
        )
        return result
    if trigger != "OnEvent" and event_tag:
        result["errors"].append(
            f"event_tag is only meaningful for trigger=OnEvent, got trigger={trigger!r}"
        )
        return result

    st, ed = _load_st_and_editor_data(st_path, result)
    if st is None:
        return result

    ops = _ops()

    source_state = ops.get_object_property_value(ed, state_path)
    if source_state is None:
        result["errors"].append(
            f"state_path {state_path!r} did not resolve to a UObject"
        )
        return result

    target_obj, target_guid, target_name = _resolve_target_state(
        ed, target_state_path, result
    )
    if target_obj is None:
        return result

    t_path = list(state_path) + ["Transitions"]
    t_len = ops.get_array_length(ed, t_path)
    if t_len < 0:
        result["errors"].append(
            f"can't read Transitions length at {_format_state_path(state_path)!r}"
        )
        return result
    result["before"] = {"t_len": t_len}

    # Idempotence: scan for (Trigger, State.ID) [+ RequiredEvent.Tag for OnEvent] match
    for i in range(t_len):
        elem_path = t_path + [f"[{i}]"]
        trig_res = ops.get_property_value(ed, elem_path + ["Trigger"])
        tid_res = ops.get_property_value(ed, elem_path + ["State", "ID"])
        if not trig_res.success or not tid_res.success:
            continue
        if trig_res.after_text != trigger or tid_res.after_text != target_guid:
            continue
        if trigger == "OnEvent":
            tag_res = ops.get_property_value(
                ed, elem_path + ["RequiredEvent", "Tag"]
            )
            existing_tag = tag_res.after_text if tag_res.success else ""
            if existing_tag != event_tag:
                continue
        result["after"] = {"t_len": t_len, "idx": i}
        result["success"] = True
        result["skipped"] = (
            f"transition {trigger} -> {target_guid} already present at index {i}"
        )
        return result

    new_idx = ops.array_append_new_element(ed, t_path)
    if new_idx < 0:
        result["errors"].append("array_append_new_element returned -1")
        return result
    elem_path = t_path + [f"[{new_idx}]"]

    r = ops.set_property_value(ed, elem_path + ["Trigger"], trigger)
    if not r.success:
        result["errors"].append(f"set Trigger failed: {r.error_message}")
        return result

    r = ops.set_property_value(ed, elem_path + ["State", "LinkType"], "GotoState")
    if not r.success:
        result["errors"].append(f"set State.LinkType failed: {r.error_message}")
        return result

    r = ops.set_property_value(ed, elem_path + ["State", "ID"], target_guid)
    if not r.success:
        result["errors"].append(f"set State.ID failed: {r.error_message}")
        return result

    # State.Name is display-only — keep the link tidy but don't fail the op if
    # it doesn't round-trip (e.g., empty name on an unnamed state).
    if target_name:
        ops.set_property_value(ed, elem_path + ["State", "Name"], target_name)

    r = ops.set_property_value(ed, elem_path + ["Priority"], priority)
    if not r.success:
        result["errors"].append(f"set Priority failed: {r.error_message}")
        return result

    if trigger == "OnEvent" and event_tag:
        r = ops.set_property_value(
            ed, elem_path + ["RequiredEvent", "Tag"], event_tag
        )
        if not r.success:
            result["errors"].append(
                f"set RequiredEvent.Tag failed: {r.error_message}"
            )
            return result

    # Deterministic transition GUID so repeat runs produce identical on-disk
    # bytes. Seeded from (st_path, source_state_path, trigger, target_guid,
    # event_tag) so a trigger-change or retarget would land a different ID.
    guid = _deterministic_guid(
        st_path,
        _format_state_path(state_path),
        trigger,
        target_guid,
        event_tag,
    )
    r = ops.set_property_value(ed, elem_path + ["ID"], guid)
    if not r.success:
        result["errors"].append(f"set ID failed: {r.error_message}")
        return result

    if not ops.compile_and_save_package(st):
        result["errors"].append("compile_and_save_package returned False")
        return result

    result["after"] = {
        "t_len": t_len + 1,
        "idx": new_idx,
        "target_guid": target_guid,
    }
    result["success"] = True
    return result


def remove_statetree_transition(
    st_path: str,
    state_path: list,
    trigger: str,
    target_state_path: list,
):
    """Remove the first ``Transitions[]`` entry on ``state_path`` whose
    ``Trigger`` + ``State.ID`` match ``(trigger, target_state_path)``.

    No-op (success with ``skipped``) when no matching entry exists.
    """
    result = make_result(
        "remove_statetree_transition",
        st_path,
        f"{_format_state_path(state_path)} -[{trigger}]-> {_format_state_path(target_state_path)}",
    )

    if trigger not in VALID_TRANSITION_TRIGGERS:
        result["errors"].append(
            f"invalid trigger {trigger!r}; must be one of {list(VALID_TRANSITION_TRIGGERS)}"
        )
        return result

    st, ed = _load_st_and_editor_data(st_path, result)
    if st is None:
        return result

    ops = _ops()

    target_obj, target_guid, _target_name = _resolve_target_state(
        ed, target_state_path, result
    )
    if target_obj is None:
        return result

    t_path = list(state_path) + ["Transitions"]
    t_len = ops.get_array_length(ed, t_path)
    if t_len < 0:
        result["errors"].append(
            f"can't read Transitions length at {_format_state_path(state_path)!r}"
        )
        return result
    result["before"] = {"t_len": t_len}

    for i in range(t_len):
        elem_path = t_path + [f"[{i}]"]
        trig_res = ops.get_property_value(ed, elem_path + ["Trigger"])
        tid_res = ops.get_property_value(ed, elem_path + ["State", "ID"])
        if not trig_res.success or not tid_res.success:
            continue
        if trig_res.after_text == trigger and tid_res.after_text == target_guid:
            r = ops.array_remove_at(ed, t_path, i)
            if not r.success:
                result["errors"].append(
                    f"array_remove_at({i}) failed: {r.error_message}"
                )
                return result
            if not ops.compile_and_save_package(st):
                result["errors"].append(
                    "compile_and_save_package returned False"
                )
                return result
            result["after"] = {"t_len": t_len - 1, "removed_idx": i}
            result["success"] = True
            return result

    result["after"] = {"t_len": t_len}
    result["success"] = True
    result["skipped"] = (
        f"no transition with trigger={trigger!r} target_guid={target_guid!r} found"
    )
    return result


def verify_state_transitions(
    st_path: str,
    state_path: list,
):
    """Read the ``Transitions`` list at a state. Read-only.

    Returns in ``after``: ``{t_len, entries: [{idx, trigger, target_guid,
    target_name, link_type, priority}]}``. Entries where individual fields
    fail to read still appear with those fields set to ``None`` so plan
    authors see exactly what's on disk.
    """
    result = make_result(
        "verify_state_transitions",
        st_path,
        _format_state_path(state_path),
    )

    st, ed = _load_st_and_editor_data(st_path, result)
    if st is None:
        return result

    ops = _ops()

    source_state = ops.get_object_property_value(ed, state_path)
    if source_state is None:
        result["errors"].append(
            f"state_path {state_path!r} did not resolve to a UObject"
        )
        return result

    t_path = list(state_path) + ["Transitions"]
    t_len = ops.get_array_length(ed, t_path)
    if t_len < 0:
        result["errors"].append(
            f"can't read Transitions length at {_format_state_path(state_path)!r}"
        )
        return result

    def _read(elem_path, *sub):
        r = ops.get_property_value(ed, elem_path + list(sub))
        return r.after_text if r.success else None

    entries = []
    for i in range(t_len):
        elem_path = t_path + [f"[{i}]"]
        entries.append(
            {
                "idx": i,
                "trigger": _read(elem_path, "Trigger"),
                "target_guid": _read(elem_path, "State", "ID"),
                "target_name": _read(elem_path, "State", "Name"),
                "link_type": _read(elem_path, "State", "LinkType"),
                "priority": _read(elem_path, "Priority"),
            }
        )

    result["before"] = {"t_len": t_len}
    result["after"] = {"t_len": t_len, "entries": entries}
    result["success"] = True
    return result


# ---------------------------------------------------------------------------
# M28.1 — task-on-state ops
#
# These mirror the add_/remove_/verify_statetree_enter_condition shape but
# operate on ``UStateTreeState::Tasks`` (a ``TArray<FStateTreeEditorNode>``)
# instead of ``EnterConditions``. The wrapper struct is
# FStateTreeBlueprintTaskWrapper (``TaskClass`` field) rather than
# FStateTreeBlueprintConditionWrapper (``ConditionClass`` field); otherwise
# the plumbing is identical — InstancedStruct type init, owner Outer for
# the BP instance, deterministic ID GUID, compile + save via the bridge.
# ---------------------------------------------------------------------------


def _resolve_task_class(task_bp_path: str, result: dict):
    """Load a BP and return its generated class. Kwarg-name variant of
    :func:`_resolve_condition_class` so error messages point at the right
    plan field when a task path fails to resolve.
    """
    if not task_bp_path.startswith("/Game/"):
        result["errors"].append(
            f"task_bp_path must start with /Game/: {task_bp_path!r}"
        )
        return None
    task_bp = unreal.load_asset(task_bp_path)
    if task_bp is None or not isinstance(task_bp, unreal.Blueprint):
        result["errors"].append(f"not a Blueprint at {task_bp_path!r}")
        return None
    task_class = task_bp.generated_class()
    if task_class is None:
        result["errors"].append(
            f"task BP has no generated_class: {task_bp_path!r}"
        )
        return None
    return task_class


def add_statetree_task_to_state(
    st_path: str,
    state_path: list,
    task_bp_path: str,
):
    """Append a Blueprint-backed task to a state's ``Tasks`` array.

    Args:
        st_path: ``/Game/...`` path to the UStateTree asset.
        state_path: nav list from StateTreeEditorData to the target
            UStateTreeState. Example for ``ST_EnemyBase.CombatLoop``:
            ``["SubTrees", "[2]", "Children", "[1]"]``.
        task_bp_path: ``/Game/...`` path to a Blueprint whose parent is
            ``UStateTreeTaskBlueprintBase``.

    Returns:
        Standard op result dict. ``before`` / ``after`` carry
        ``{task_len, idx}`` snapshots; ``skipped`` is present when an
        existing entry already matches the task class.

    Idempotent: if the state's ``Tasks`` already contains an entry whose
    ``InstanceObject`` is of the requested BP's generated class, returns
    success with a ``skipped`` reason and does not save.
    """
    result = make_result(
        "add_statetree_task_to_state",
        st_path,
        f"{_format_state_path(state_path)} += {task_bp_path}",
    )

    st, ed = _load_st_and_editor_data(st_path, result)
    if st is None:
        return result

    wrapper = unreal.find_object(None, TASK_WRAPPER_STRUCT_PATH)
    if wrapper is None:
        result["errors"].append(
            f"{TASK_WRAPPER_STRUCT_PATH} not found — is StateTreeModule loaded?"
        )
        return result

    task_class = _resolve_task_class(task_bp_path, result)
    if task_class is None:
        return result
    task_class_path = task_class.get_path_name()

    ops = _ops()

    state_obj = ops.get_object_property_value(ed, state_path)
    if state_obj is None:
        result["errors"].append(
            f"state_path {state_path!r} did not resolve to a UObject"
        )
        return result

    tasks_path = list(state_path) + ["Tasks"]
    task_len = ops.get_array_length(ed, tasks_path)
    if task_len < 0:
        result["errors"].append(
            f"can't read Tasks length at {_format_state_path(state_path)!r}"
        )
        return result
    result["before"] = {"task_len": task_len}

    for i in range(task_len):
        io = ops.get_object_property_value(
            ed, tasks_path + [f"[{i}]", "InstanceObject"]
        )
        if io is not None and io.get_class().get_path_name() == task_class_path:
            result["after"] = {"task_len": task_len, "idx": i}
            result["success"] = True
            result["skipped"] = (
                f"{task_class_path} already present at index {i}"
            )
            return result

    new_idx = ops.array_append_new_element(ed, tasks_path)
    if new_idx < 0:
        result["errors"].append("array_append_new_element returned -1")
        return result
    elem_path = tasks_path + [f"[{new_idx}]"]

    r = ops.set_instanced_struct_type(ed, elem_path + ["Node"], wrapper)
    if not r.success:
        result["errors"].append(
            f"set_instanced_struct_type failed: {r.error_message}"
        )
        return result

    r = ops.set_object_property_value(
        ed, elem_path + ["Node", "TaskClass"], task_class
    )
    if not r.success:
        result["errors"].append(f"set TaskClass failed: {r.error_message}")
        return result

    guid = _deterministic_guid(
        st_path, _format_state_path(state_path), "task", task_class_path
    )
    r = ops.set_property_value(ed, elem_path + ["ID"], guid)
    if not r.success:
        result["errors"].append(f"set ID failed: {r.error_message}")
        return result

    task_instance = ops.new_subobject(state_obj, task_class, unreal.Name(""))
    if task_instance is None:
        result["errors"].append("new_subobject returned None")
        return result

    r = ops.set_object_property_value(
        ed, elem_path + ["InstanceObject"], task_instance
    )
    if not r.success:
        result["errors"].append(f"set InstanceObject failed: {r.error_message}")
        return result

    if not ops.compile_and_save_package(st):
        result["errors"].append("compile_and_save_package returned False")
        return result

    result["after"] = {
        "task_len": task_len + 1,
        "idx": new_idx,
        "instance": task_instance.get_path_name(),
    }
    result["success"] = True
    return result


def remove_statetree_task_from_state(
    st_path: str,
    state_path: list,
    task_bp_path: str,
):
    """Remove the first ``Tasks[]`` entry on ``state_path`` whose
    ``InstanceObject`` is of ``task_bp_path``'s generated class.

    No-op (success with ``skipped``) when no matching entry exists.
    """
    result = make_result(
        "remove_statetree_task_from_state",
        st_path,
        f"{_format_state_path(state_path)} -= {task_bp_path}",
    )

    st, ed = _load_st_and_editor_data(st_path, result)
    if st is None:
        return result

    task_class = _resolve_task_class(task_bp_path, result)
    if task_class is None:
        return result
    task_class_path = task_class.get_path_name()

    ops = _ops()
    tasks_path = list(state_path) + ["Tasks"]
    task_len = ops.get_array_length(ed, tasks_path)
    if task_len < 0:
        result["errors"].append(
            f"can't read Tasks length at {_format_state_path(state_path)!r}"
        )
        return result
    result["before"] = {"task_len": task_len}

    for i in range(task_len):
        io = ops.get_object_property_value(
            ed, tasks_path + [f"[{i}]", "InstanceObject"]
        )
        if io is not None and io.get_class().get_path_name() == task_class_path:
            r = ops.array_remove_at(ed, tasks_path, i)
            if not r.success:
                result["errors"].append(
                    f"array_remove_at({i}) failed: {r.error_message}"
                )
                return result
            if not ops.compile_and_save_package(st):
                result["errors"].append(
                    "compile_and_save_package returned False"
                )
                return result
            result["after"] = {"task_len": task_len - 1, "removed_idx": i}
            result["success"] = True
            return result

    result["after"] = {"task_len": task_len}
    result["success"] = True
    result["skipped"] = f"no task with class {task_class_path} found"
    return result


def verify_state_tasks(
    st_path: str,
    state_path: list,
):
    """Read the current ``Tasks`` list at a state. Read-only.

    Returns in ``after``: ``{task_len, entries: [{idx, class_path,
    instance_path}]}``. Entries with ``InstanceObject == None`` still
    appear with ``class_path`` / ``instance_path`` set to ``None`` so plan
    authors see exactly what's on disk.
    """
    result = make_result(
        "verify_state_tasks",
        st_path,
        _format_state_path(state_path),
    )

    st, ed = _load_st_and_editor_data(st_path, result)
    if st is None:
        return result

    ops = _ops()

    state_obj = ops.get_object_property_value(ed, state_path)
    if state_obj is None:
        result["errors"].append(
            f"state_path {state_path!r} did not resolve to a UObject"
        )
        return result

    tasks_path = list(state_path) + ["Tasks"]
    task_len = ops.get_array_length(ed, tasks_path)
    if task_len < 0:
        result["errors"].append(
            f"can't read Tasks length at {_format_state_path(state_path)!r}"
        )
        return result

    entries = []
    for i in range(task_len):
        io = ops.get_object_property_value(
            ed, tasks_path + [f"[{i}]", "InstanceObject"]
        )
        if io is None:
            entries.append({"idx": i, "class_path": None, "instance_path": None})
            continue
        entries.append(
            {
                "idx": i,
                "class_path": io.get_class().get_path_name(),
                "instance_path": io.get_path_name(),
            }
        )

    result["before"] = {"task_len": task_len}
    result["after"] = {"task_len": task_len, "entries": entries}
    result["success"] = True
    return result
