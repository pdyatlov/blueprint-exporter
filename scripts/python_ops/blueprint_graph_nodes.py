"""Blueprint graph-node spawn ops via the M28.3.1+ reflection bridge.

Writes new K2Node subclasses into existing K2 graphs (function / interface
override / ubergraph) with deterministic NodeGuids + pin IDs + object names.
Every op here is idempotent on its seed key so plan replay is safe.

M28.3.1 shipped two ops:
  - add_branch_node          — spawn UK2Node_IfThenElse with zero config
  - set_graph_pin_default    — graph-level sibling of M26.1's function-name
                                keyed SetNodePinLiteralDefault, accepts any
                                graph and a runtime NodeGuid hex string

M28.3.2 extends with the FunctionReference / VariableReference family. Each
shares ~80% of the spawn-op machinery (FindFunctionGraphByName routing,
SeedGuidFromJoined NodeGuid, SeedPinGuidsForNode per-pin, idempotence on
seeded GUID); the delta is a single FMemberReference.SetSelfMember /
SetExternalMember call before AllocateDefaultPins so the node's pin set
resolves to the correct signature:

  - add_call_function_node   — spawn UK2Node_CallFunction (self or external)
  - add_variable_get_node    — spawn UK2Node_VariableGet  (self or external)
  - add_variable_set_node    — spawn UK2Node_VariableSet  (self or external)

M28.3.3 adds three independent one-off K2Node types — each needs its own
pre-AllocateDefaultPins configuration but otherwise shares the spawn-op
scaffold above:

  - add_custom_event_node      — spawn UK2Node_CustomEvent into an ubergraph
                                  (ubergraph-only op entry check; sets
                                  CustomFunctionName before pin alloc)
  - add_execution_sequence_node — spawn UK2Node_ExecutionSequence with N
                                  `then_N` outputs (uses misleadingly named
                                  IK2Node_AddPinInterface::AddInputPin which
                                  actually adds output pins)
  - add_dynamic_cast_node      — spawn UK2Node_DynamicCast targeting a
                                  specific UClass (sets TargetType before
                                  pin alloc so As<X> output pin is typed)

M28.3.4 adds the last planned M28.3 op — different shape from the K2Node
spawn family (modifies an existing UK2Node_FunctionEntry's LocalVariables
array rather than creating a new K2Node):

  - add_local_variable         — append FBPVariableDescription to a function
                                  graph's Entry node. Reuses the
                                  `_resolve_pin_type` spec parser from
                                  M28.2.1's `add_bp_variable`.

After M28.3.4 the M28.3 catalog is closed; M28.3.6 docs sweep follows as
pure-docs with no version bump.
"""

import unreal

from ._common import make_result
from .blueprint_structural import _resolve_pin_type


def _ops():
    return unreal.BpxReflectionOps


def _load_bp(bp_path: str, result: dict):
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


def _guid_str(guid) -> str:
    """Hex form of an FGuid (Digits format: 32 lowercase hex chars, no
    separators). UE Python's default ``str(fguid)`` returns the generic
    struct repr ``"<Struct 'Guid' (0x...) {}>"`` — don't rely on that;
    ``.to_string()`` is the correct accessor."""
    try:
        return guid.to_string()
    except Exception:
        return str(guid)


def _coerce_position(position, result: dict):
    """Accept ``[x, y]`` / ``(x, y)`` / ``unreal.Vector2D``.

    Returns an ``unreal.Vector2D`` or None (errors appended).
    """
    if isinstance(position, unreal.Vector2D):
        return position
    if isinstance(position, (list, tuple)) and len(position) == 2:
        try:
            return unreal.Vector2D(float(position[0]), float(position[1]))
        except (TypeError, ValueError) as exc:
            result["errors"].append(
                f"position {position!r} x/y must be numeric: {exc}"
            )
            return None
    result["errors"].append(
        f"position must be [x, y] / (x, y) / Vector2D; got {position!r}"
    )
    return None


# ---------------------------------------------------------------------------
# M28.3.1 — Branch (UK2Node_IfThenElse) spawn
# ---------------------------------------------------------------------------


def add_branch_node(
    bp_path: str,
    graph_name: str,
    position,
):
    """Spawn a Branch (``UK2Node_IfThenElse``) into a K2 graph.

    Args:
        bp_path: ``/Game/...`` path to the target Blueprint.
        graph_name: name of the target graph. Accepts:
            - a function graph name (``"MyFunc"``)
            - an interface-override graph name (same string — lives on
              ``ImplementedInterfaces[].Graphs`` but resolves by FName)
            - an ubergraph page (``"EventGraph"`` — default)
        position: ``[x, y]`` / ``(x, y)`` / ``unreal.Vector2D``. Included in
            the determinism seed so two Branches at different positions in
            the same graph get distinct NodeGuids.

    Returns:
        Standard op-result dict. ``after`` carries ``{node_guid: <hex>,
        pins: [<pin names>]}`` so callers chain ``connect_graph_pins`` /
        ``set_graph_pin_default`` using the returned GUID verbatim.

        Idempotent: if a Branch with the same seed already exists in the
        graph, returns ``success=True`` with ``skipped="branch already
        exists at this position"``.

    Determinism: NodeGuid is seeded as
    ``md5(<bp>:graph:<g>:branch:<x>,<y>)``; pin IDs via
    ``SeedPinGuidsForNode``. Running the op twice against the same baseline
    produces byte-identical ``.uasset`` — M28.pre.3 soak depends on this.

    Default Branch pins (from ``UK2Node_IfThenElse::AllocateDefaultPins``):
    ``execute`` (exec in), ``Condition`` (bool in), ``then`` (exec out for
    true branch), ``else`` (exec out for false branch).
    """
    result = make_result("add_branch_node", bp_path, graph_name)

    if not graph_name:
        result["errors"].append("graph_name must be non-empty")
        return result

    bp = _load_bp(bp_path, result)
    if bp is None:
        return result

    pos = _coerce_position(position, result)
    if pos is None:
        return result

    ops = _ops()
    node_r = ops.add_branch_node(bp, unreal.Name(graph_name), pos)
    if not node_r.success:
        result["errors"].append(
            f"add_branch_node bridge call failed: {node_r.error_message}"
        )
        return result

    node_guid = _guid_str(node_r.node_guid)

    if node_r.skipped:
        result["success"] = True
        result["skipped"] = "branch already exists at this position"
        result["after"] = {
            "node_guid": node_guid,
            "spawned": False,
            "pins": ["execute", "Condition", "then", "else"],
        }
        return result

    if not ops.compile_and_save_package(bp):
        result["errors"].append(
            "compile_and_save_package returned False — BP compile failed "
            "or save refused (check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = {
        "node_guid": node_guid,
        "spawned": True,
        "pins": ["execute", "Condition", "then", "else"],
    }
    return result


# ---------------------------------------------------------------------------
# M28.3.1 — graph-level pin default
# ---------------------------------------------------------------------------


def set_graph_pin_default(
    bp_path: str,
    graph_name: str,
    node_guid: str,
    pin_name: str,
    literal_text: str,
):
    """Set a pin's literal ``DefaultValue`` on any node in any K2 graph.

    Sibling of M26.1's ``set_node_pin_literal_default`` that reaches any
    graph family (function / interface override / ubergraph) and accepts
    the runtime ``NodeGuid`` as a hex string — the exact shape newly-spawned
    M28.3.1+ nodes return.

    Args:
        bp_path: ``/Game/...`` path to the Blueprint.
        graph_name: graph name, resolved via the bridge's
            ``FindFunctionGraphByName`` (walks all three families).
        node_guid: 32-char hex ``NodeGuid`` (optionally dash-grouped). Plan
            authors get this from the op result of ``add_branch_node`` /
            ``add_call_function_node`` / etc.
        pin_name: display name of the target pin (e.g. ``"Condition"`` on
            a Branch, ``"ReturnValue"`` on a CallFunction).
        literal_text: the new literal default — same format
            ``FProperty::ImportText_Direct`` accepts (``"true"`` for bool,
            ``"42"`` for int, ``"(X=1.0,Y=2.0)"`` for vectors).

    Returns:
        Standard op-result dict. ``before`` is the prior DefaultValue
        string, ``after`` is the post-set value. Idempotent: setting to
        the current value returns ``success=True`` with
        ``skipped="value unchanged"``.
    """
    result = make_result(
        "set_graph_pin_default",
        bp_path,
        f"{graph_name}:{pin_name}",
    )

    if not graph_name:
        result["errors"].append("graph_name must be non-empty")
        return result
    if not node_guid:
        result["errors"].append("node_guid must be non-empty")
        return result
    if not pin_name:
        result["errors"].append("pin_name must be non-empty")
        return result
    # literal_text may legitimately be "" — don't guard it.

    bp = _load_bp(bp_path, result)
    if bp is None:
        return result

    ops = _ops()
    r = ops.set_graph_pin_literal_default(
        bp,
        unreal.Name(graph_name),
        node_guid,
        unreal.Name(pin_name),
        literal_text,
    )
    if not r.success:
        result["errors"].append(
            f"set_graph_pin_literal_default failed: {r.error_message}"
        )
        return result

    result["before"] = r.before_text
    if r.skipped:
        result["success"] = True
        result["skipped"] = "value unchanged"
        result["after"] = r.after_text
        return result

    if not ops.compile_and_save_package(bp):
        result["errors"].append(
            "compile_and_save_package returned False — BP compile failed "
            "or save refused (check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = r.after_text
    return result


# ---------------------------------------------------------------------------
# M28.3.2 — shared resolution helpers + three FMemberReference spawn ops
# ---------------------------------------------------------------------------


def _resolve_target_class(target_class_path: str, result: dict):
    """Resolve a target UClass for the external-context path, or return
    None (self context). Mirrors the ``add_component_to_scs`` /
    ``add_bp_interface`` fallback: ``load_class`` for native ``/Script/...``
    paths, ``load_object`` for BP-generated ``/Game/...._C`` classes.

    Empty string / ``None`` → self context, returns ``(None, True)``.
    Unresolvable non-empty path → appends error, returns ``(None, False)``.
    Successful resolve → ``(UClass, True)``.
    """
    if not target_class_path:
        return None, True
    cls = (
        unreal.load_class(None, target_class_path)
        or unreal.load_object(None, target_class_path)
    )
    if cls is None or not isinstance(cls, unreal.Class):
        result["errors"].append(
            f"target_class_path did not resolve to a UClass: {target_class_path!r} "
            f"(must be /Script/<Module>.<Class> or /Game/<Asset>.<Asset>_C; "
            f"empty string selects self context)"
        )
        return None, False
    return cls, True


def _spawn_node_common(
    op_name: str,
    bridge_callable,
    bp_path: str,
    graph_name: str,
    member_name: str,
    target_class_path: str,
    position,
    skipped_message: str,
):
    """Shared scaffold for the three M28.3.2 FMemberReference spawn ops —
    they only differ in (a) the bridge UFUNCTION invoked and (b) the op name
    surfaced in the result dict. All validation, idempotence-skip, and
    compile+save handling is identical.
    """
    result = make_result(op_name, bp_path, f"{graph_name}:{member_name}")

    if not graph_name:
        result["errors"].append("graph_name must be non-empty")
        return result
    if not member_name:
        result["errors"].append("member_name must be non-empty")
        return result

    bp = _load_bp(bp_path, result)
    if bp is None:
        return result

    pos = _coerce_position(position, result)
    if pos is None:
        return result

    target_class, target_ok = _resolve_target_class(target_class_path, result)
    if not target_ok:
        return result

    node_r = bridge_callable(
        bp,
        unreal.Name(graph_name),
        unreal.Name(member_name),
        target_class,
        pos,
    )
    if not node_r.success:
        result["errors"].append(
            f"{op_name} bridge call failed: {node_r.error_message}"
        )
        return result

    node_guid = _guid_str(node_r.node_guid)
    target_class_record = target_class_path or ""

    if node_r.skipped:
        result["success"] = True
        result["skipped"] = skipped_message
        result["after"] = {
            "node_guid": node_guid,
            "member_name": member_name,
            "target_class_path": target_class_record,
            "spawned": False,
        }
        return result

    ops = _ops()
    if not ops.compile_and_save_package(bp):
        result["errors"].append(
            "compile_and_save_package returned False — BP compile failed "
            "or save refused (check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = {
        "node_guid": node_guid,
        "member_name": member_name,
        "target_class_path": target_class_record,
        "spawned": True,
    }
    return result


def add_call_function_node(
    bp_path: str,
    graph_name: str,
    function_name: str,
    target_class_path: str = "",
    position=(0, 0),
):
    """Spawn a ``UK2Node_CallFunction`` node into a K2 graph.

    Sibling of ``add_branch_node`` with one config step: the ``FunctionReference``
    is set before ``AllocateDefaultPins`` so the node's pins materialise with
    the callee's signature (typed inputs + ``ReturnValue`` where applicable).

    Args:
        bp_path: ``/Game/...`` path to the Blueprint.
        graph_name: target graph (function / interface-override / ubergraph).
        function_name: name of the UFUNCTION to call. For self-context calls
            this is the BP's own declared function or any inherited UFUNCTION
            from the generated class's ancestors; for external-context calls
            this is a member of ``target_class_path``.
        target_class_path: Empty (default) → ``FunctionReference.SetSelfMember``.
            Non-empty → ``SetExternalMember(function_name, load_class(path))``.
            Accepts ``/Script/<Module>.<Class>`` (native) or
            ``/Game/<Asset>.<Asset>_C`` (BP-generated).
        position: ``[x, y]`` / ``(x, y)`` / ``unreal.Vector2D``. Included in
            the determinism seed so two calls at different positions get
            distinct GUIDs.

    Returns:
        Standard op-result dict. ``after`` carries ``{node_guid, member_name,
        target_class_path, spawned}``. Idempotent: if a CallFunction with the
        same seed already exists, returns ``skipped`` with ``spawned=False``.

    Determinism: NodeGuid is seeded as
    ``md5(<bp>:graph:<g>:call:<member>:<target|self>:<x,y>)``; pin IDs via
    ``SeedPinGuidsForNode``. Running twice against the same baseline is a
    byte-identical no-op on round 2.
    """
    return _spawn_node_common(
        "add_call_function_node",
        _ops().add_call_function_node,
        bp_path,
        graph_name,
        function_name,
        target_class_path,
        position,
        "CallFunction node already exists at this position",
    )


def add_variable_get_node(
    bp_path: str,
    graph_name: str,
    variable_name: str,
    target_class_path: str = "",
    position=(0, 0),
):
    """Spawn a ``UK2Node_VariableGet`` node into a K2 graph.

    Generalises M26.1's ``add_self_member_get_node`` (which only reaches
    function graphs and only supports self context) to any graph family and
    to external-class targets.

    Args:
        bp_path: ``/Game/...`` path to the Blueprint.
        graph_name: target graph (function / interface-override / ubergraph).
        variable_name: name of the variable to read. Self context → a variable
            declared on the BP or inherited from its generated class's
            ancestors; external context → a ``BlueprintReadOnly`` /
            ``BlueprintReadWrite`` UPROPERTY on ``target_class_path``.
        target_class_path: Empty → ``VariableReference.SetSelfMember``.
            Non-empty → ``SetExternalMember(variable_name, load_class(path))``.
        position: as ``add_call_function_node``.

    Returns:
        Standard op-result dict. Idempotent behaviour mirrors
        ``add_call_function_node``.

    Determinism: seed key is
    ``md5(<bp>:graph:<g>:varget:<member>:<target|self>:<x,y>)``.
    """
    return _spawn_node_common(
        "add_variable_get_node",
        _ops().add_variable_get_node,
        bp_path,
        graph_name,
        variable_name,
        target_class_path,
        position,
        "VariableGet node already exists at this position",
    )


def add_variable_set_node(
    bp_path: str,
    graph_name: str,
    variable_name: str,
    target_class_path: str = "",
    position=(0, 0),
):
    """Spawn a ``UK2Node_VariableSet`` node into a K2 graph.

    Sibling of ``add_variable_get_node``; default pin set is an ``execute``
    input/output exec pair plus a typed value input pin. Target variable must
    be ``BlueprintReadWrite`` (or the pin won't authorise a write at compile
    time) in the external-context case.

    Args / Returns: see ``add_variable_get_node``.

    Determinism: seed key is
    ``md5(<bp>:graph:<g>:varset:<member>:<target|self>:<x,y>)``.
    """
    return _spawn_node_common(
        "add_variable_set_node",
        _ops().add_variable_set_node,
        bp_path,
        graph_name,
        variable_name,
        target_class_path,
        position,
        "VariableSet node already exists at this position",
    )


# ---------------------------------------------------------------------------
# M28.3.3 — CustomEvent / ExecutionSequence / DynamicCast
# ---------------------------------------------------------------------------


def add_custom_event_node(
    bp_path: str,
    graph_name: str,
    event_name: str,
    position=(0, 0),
):
    """Spawn a ``UK2Node_CustomEvent`` node into an ubergraph.

    Primary driver from design.md: the squad director's ``AI.Order.*`` event
    channel (item #1) — each order subclass fires through a custom event that
    listeners bind to. Also used by the callout system (item #4).

    Args:
        bp_path: ``/Game/...`` path to the Blueprint.
        graph_name: target ubergraph (usually ``"EventGraph"``). Non-ubergraph
            targets are rejected at op entry with a structured error — UE's
            ``K2Node_Event::IsCompatibleWithGraph`` would reject them at
            compile time, surfacing it early keeps the plan author's feedback
            loop tight.
        event_name: the custom event's ``CustomFunctionName``. Must be unique
            within the Blueprint's ubergraph scope; compile time catches
            conflicts with inherited functions. Included in the determinism
            seed so two events at different positions with different names
            get distinct GUIDs.
        position: ``[x, y]`` / ``(x, y)`` / ``unreal.Vector2D``.

    Returns:
        Standard op-result dict. ``after`` carries ``{node_guid, event_name,
        spawned, pins}``. Idempotent: if an event at the same seed already
        exists, returns ``skipped`` with ``spawned=False``.

    Determinism: NodeGuid is seeded as
    ``md5(<bp>:graph:<g>:custom_event:<name>:<x>,<y>)``; pin IDs via
    ``SeedPinGuidsForNode``.

    Default pins (from ``UK2Node_Event::AllocateDefaultPins``):
    ``OutputDelegate`` (delegate out, used by ``Bind Event``) and ``then``
    (exec out). Events with parameters need subsequent user-defined-pin ops
    (deferred to a later M28.3 sub-phase).
    """
    result = make_result("add_custom_event_node", bp_path, f"{graph_name}:{event_name}")

    if not graph_name:
        result["errors"].append("graph_name must be non-empty")
        return result
    if not event_name:
        result["errors"].append("event_name must be non-empty")
        return result

    bp = _load_bp(bp_path, result)
    if bp is None:
        return result

    pos = _coerce_position(position, result)
    if pos is None:
        return result

    ops = _ops()
    node_r = ops.add_custom_event_node(
        bp, unreal.Name(graph_name), unreal.Name(event_name), pos
    )
    if not node_r.success:
        result["errors"].append(
            f"add_custom_event_node bridge call failed: {node_r.error_message}"
        )
        return result

    node_guid = _guid_str(node_r.node_guid)

    if node_r.skipped:
        result["success"] = True
        result["skipped"] = "CustomEvent already exists at this position"
        result["after"] = {
            "node_guid": node_guid,
            "event_name": event_name,
            "spawned": False,
            "pins": ["OutputDelegate", "then"],
        }
        return result

    if not ops.compile_and_save_package(bp):
        result["errors"].append(
            "compile_and_save_package returned False — BP compile failed "
            "or save refused (check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = {
        "node_guid": node_guid,
        "event_name": event_name,
        "spawned": True,
        "pins": ["OutputDelegate", "then"],
    }
    return result


def add_execution_sequence_node(
    bp_path: str,
    graph_name: str,
    num_outputs: int,
    position=(0, 0),
):
    """Spawn a ``UK2Node_ExecutionSequence`` node with N ``Then_N`` outputs.

    Design.md drivers: polish-pass sequencing (item #8 — hit reactions → ally
    reactions → animation triggers) and callout broadcasts fanning out to
    multiple listeners (item #4).

    Args:
        bp_path: ``/Game/...`` path to the Blueprint.
        graph_name: target graph (function / interface-override / ubergraph).
        num_outputs: final output-pin count. Must be in ``[2, 16]``. The
            engine's default ``AllocateDefaultPins`` produces ``Then_0`` +
            ``Then_1``; additional outputs are added via
            ``IK2Node_AddPinInterface::AddInputPin`` — misleading UE API
            name, it actually adds THEN-OUT pins, not inputs. Included in
            the determinism seed so two sequences with different fan-outs at
            the same position get distinct GUIDs.
        position: ``[x, y]`` / ``(x, y)`` / ``unreal.Vector2D``.

    Returns:
        Standard op-result dict. ``after`` carries ``{node_guid, num_outputs,
        spawned, pins}``. Idempotent on seeded GUID.

    Determinism: NodeGuid seeded as
    ``md5(<bp>:graph:<g>:execseq:<n>:<x>,<y>)``; ``SeedPinGuidsForNode`` runs
    AFTER the ``AddInputPin`` loop so extended ``Then_2``+ pins are also
    deterministic.

    Default + extended pins: ``execute`` (exec in), ``then_0`` ... ``then_N-1``
    (exec out; lowercase ``then`` per UE's ``UEdGraphSchema_K2::PN_Then``).
    """
    result = make_result(
        "add_execution_sequence_node", bp_path, f"{graph_name}:n{num_outputs}"
    )

    if not graph_name:
        result["errors"].append("graph_name must be non-empty")
        return result
    if not isinstance(num_outputs, int) or isinstance(num_outputs, bool):
        result["errors"].append(
            f"num_outputs must be an int; got {type(num_outputs).__name__}"
        )
        return result
    if num_outputs < 2 or num_outputs > 16:
        result["errors"].append(
            f"num_outputs={num_outputs} out of range [2, 16]"
        )
        return result

    bp = _load_bp(bp_path, result)
    if bp is None:
        return result

    pos = _coerce_position(position, result)
    if pos is None:
        return result

    ops = _ops()
    node_r = ops.add_execution_sequence_node(
        bp, unreal.Name(graph_name), num_outputs, pos
    )
    if not node_r.success:
        result["errors"].append(
            f"add_execution_sequence_node bridge call failed: {node_r.error_message}"
        )
        return result

    node_guid = _guid_str(node_r.node_guid)
    # Pin names follow UE's UEdGraphSchema_K2::PN_Then (lowercase) — the
    # engine's GetPinNameGivenIndex composes `<PN_Then>_<i>` = "then_<i>".
    pin_names = ["execute"] + [f"then_{i}" for i in range(num_outputs)]

    if node_r.skipped:
        result["success"] = True
        result["skipped"] = "ExecutionSequence already exists at this position"
        result["after"] = {
            "node_guid": node_guid,
            "num_outputs": num_outputs,
            "spawned": False,
            "pins": pin_names,
        }
        return result

    if not ops.compile_and_save_package(bp):
        result["errors"].append(
            "compile_and_save_package returned False — BP compile failed "
            "or save refused (check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = {
        "node_guid": node_guid,
        "num_outputs": num_outputs,
        "spawned": True,
        "pins": pin_names,
    }
    return result


def add_dynamic_cast_node(
    bp_path: str,
    graph_name: str,
    target_class_path: str,
    position=(0, 0),
):
    """Spawn a ``UK2Node_DynamicCast`` node typed against a specific UClass.

    Design.md drivers: utility scorer action resolution (item #2 — cast
    generic ``AActor*`` to archetype-specific classes for per-archetype
    scoring hooks) and callouts (item #4 — cast ally ref to ``BP_EnemyBase``
    to test faction before broadcasting).

    Args:
        bp_path: ``/Game/...`` path to the Blueprint.
        graph_name: target graph (function / interface-override / ubergraph).
        target_class_path: UClass path to cast TO. Required (non-empty).
            Accepts ``/Script/<Module>.<Class>`` (native) or
            ``/Game/<Asset>.<Asset>_C`` (BP-generated). Resolved via
            ``unreal.load_class`` with ``load_object`` fallback, mirroring
            ``add_component_to_scs`` / ``add_bp_interface``.
        position: ``[x, y]`` / ``(x, y)`` / ``unreal.Vector2D``.

    Returns:
        Standard op-result dict. ``after`` carries ``{node_guid,
        target_class_path, spawned, pins}``. Idempotent on seeded GUID
        (seed includes target class + position).

    Determinism: NodeGuid seeded as
    ``md5(<bp>:graph:<g>:cast:<target>:<x>,<y>)``; pin IDs via
    ``SeedPinGuidsForNode``.

    Default pins (impure cast — the ship shape for M28.3.3): ``execute``
    (exec in), ``CastSucceeded`` (exec out), ``CastFailed`` (exec out),
    ``ObjectToCast`` (object in), ``As<TargetClass>`` (object out, typed by
    ``TargetType``), ``bSuccess`` (bool out).
    """
    result = make_result(
        "add_dynamic_cast_node", bp_path, f"{graph_name}:{target_class_path}"
    )

    if not graph_name:
        result["errors"].append("graph_name must be non-empty")
        return result
    if not target_class_path:
        result["errors"].append(
            "target_class_path must be non-empty (DynamicCast requires a concrete UClass)"
        )
        return result

    bp = _load_bp(bp_path, result)
    if bp is None:
        return result

    pos = _coerce_position(position, result)
    if pos is None:
        return result

    target_class = (
        unreal.load_class(None, target_class_path)
        or unreal.load_object(None, target_class_path)
    )
    if target_class is None or not isinstance(target_class, unreal.Class):
        result["errors"].append(
            f"target_class_path did not resolve to a UClass: {target_class_path!r} "
            f"(must be /Script/<Module>.<Class> or /Game/<Asset>.<Asset>_C)"
        )
        return result

    ops = _ops()
    node_r = ops.add_dynamic_cast_node(
        bp, unreal.Name(graph_name), target_class, pos
    )
    if not node_r.success:
        result["errors"].append(
            f"add_dynamic_cast_node bridge call failed: {node_r.error_message}"
        )
        return result

    node_guid = _guid_str(node_r.node_guid)
    # As<X> pin name is computed by UE as e.g. "AsActor" — we surface the
    # stable pattern without trying to reconstruct UE's exact slugged name.
    pin_names = [
        "execute",
        "CastSucceeded",
        "CastFailed",
        "ObjectToCast",
        "AsObject",
        "bSuccess",
    ]

    if node_r.skipped:
        result["success"] = True
        result["skipped"] = "DynamicCast already exists at this position"
        result["after"] = {
            "node_guid": node_guid,
            "target_class_path": target_class_path,
            "spawned": False,
            "pins": pin_names,
        }
        return result

    if not ops.compile_and_save_package(bp):
        result["errors"].append(
            "compile_and_save_package returned False — BP compile failed "
            "or save refused (check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = {
        "node_guid": node_guid,
        "target_class_path": target_class_path,
        "spawned": True,
        "pins": pin_names,
    }
    return result


# ---------------------------------------------------------------------------
# M28.3.4 — LocalVariable add
# ---------------------------------------------------------------------------


def add_local_variable(
    bp_path: str,
    function_name: str,
    var_name: str,
    var_type_spec: str,
    default_value: str = "",
):
    """Append a local variable to a Blueprint function's ``K2Node_FunctionEntry``.

    Final planned op of the M28.3 catalog. Different shape from the K2Node-
    spawn ops (``add_branch_node`` / ``add_call_function_node`` / etc.) — this
    op extends the ``LocalVariables: TArray<FBPVariableDescription>`` UPROPERTY
    on the function graph's existing Entry node rather than creating a fresh
    K2Node. Per the M28.3.0 research sequencing, ships last so the Entry-node
    machinery is fully exercised by the prior phases.

    Args:
        bp_path: ``/Game/...`` path to the Blueprint.
        function_name: name of the target function graph. Accepts function
            graphs and interface-override graphs. Ubergraphs are rejected —
            they have no ``K2Node_FunctionEntry``.
        var_name: name of the new local variable. Must be unique within the
            target function's ``LocalVariables[]``. Local vars with the same
            name in DIFFERENT functions are allowed (determinism seed keys on
            ``function_name`` + ``var_name``).
        var_type_spec: pin-type spec in the same compact string form
            ``add_bp_variable`` (M28.2.1) accepts — ``"int"`` / ``"bool"`` /
            ``"struct:/Script/CoreUObject.Vector"`` /
            ``"object:/Script/AIModule.AIController"`` /
            ``"array:int"`` / ``"map:name=>>>:int"`` / etc. Routed through
            ``blueprint_structural._resolve_pin_type``.
        default_value: literal default value as a string (same format
            ``FBPVariableDescription::DefaultValue`` accepts — ``"true"`` for
            bool, ``"42"`` for int, ``"(X=1.0,Y=2.0)"`` for vectors). Empty
            string = type default.

    Returns:
        Standard op-result dict. ``before``/``after`` are bookkeeping tokens
        (``"no-localvar"`` → ``"localvar-added:<fn>::<var>"``). Idempotent: if
        a local var with ``var_name`` already exists on ``function_name``,
        returns ``success=True`` with ``skipped="local variable already
        exists"``.

    Determinism: ``VarGuid`` is seeded as
    ``md5(<bp>:func:<fn>:localvar:<varname>)``. Running the op twice against
    the same baseline produces byte-identical ``.uasset`` — M28.pre.3 soak
    depends on this.

    Design.md drivers: utility-scorer action resolution (item #2 — per-score
    temporary state), squad-director order processing (item #1 — per-call
    scratch vars like ``CurrentOrderPriority``), polish-pass state (item #8).
    Any function body that needs transient state without polluting the BP's
    member-variable surface.
    """
    result = make_result(
        "add_local_variable", bp_path, f"{function_name}::{var_name}"
    )

    if not function_name:
        result["errors"].append("function_name must be non-empty")
        return result
    if not var_name:
        result["errors"].append("var_name must be non-empty")
        return result

    bp = _load_bp(bp_path, result)
    if bp is None:
        return result

    pin_type = _resolve_pin_type(var_type_spec, result)
    if pin_type is None:
        return result

    ops = _ops()
    r = ops.add_local_variable_deterministic(
        bp,
        unreal.Name(function_name),
        unreal.Name(var_name),
        pin_type,
        default_value,
    )
    if not r.success:
        result["errors"].append(
            f"add_local_variable_deterministic bridge call failed: {r.error_message}"
        )
        return result

    result["before"] = r.before_text

    if r.skipped:
        result["success"] = True
        result["skipped"] = "local variable already exists"
        result["after"] = r.after_text
        return result

    if not ops.compile_and_save_package(bp):
        result["errors"].append(
            "compile_and_save_package returned False — BP compile failed "
            "or save refused (check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = r.after_text
    return result


# ---------------------------------------------------------------------------
# M28.13 — UK2Node_MacroInstance authoring (loop unblocker)
# ---------------------------------------------------------------------------


def _resolve_macro_graph(macro_path: str, result: dict):
    """Resolve a macro path of shape ``"<lib_uobject_path>:<macro_name>"`` to
    the underlying ``UEdGraph``.

    ``lib_uobject_path`` is loaded via ``unreal.load_object`` and must resolve
    to a ``UBlueprint`` (the macro library). The library's ``MacroGraphs``
    array is then walked for a ``UEdGraph`` whose name matches the suffix
    after the ``:``.

    Examples::

        "/Engine/EditorBlueprintResources/StandardMacros.StandardMacros:ForEachLoop"
        "/Engine/EditorBlueprintResources/StandardMacros.StandardMacros:WhileLoop"
        "/Game/Macros/MyLib.MyLib:DoNTimes"

    Returns the resolved ``unreal.EdGraph`` or ``None`` (errors appended).
    """
    if not macro_path:
        result["errors"].append("macro_path must be non-empty")
        return None
    if ":" not in macro_path:
        result["errors"].append(
            f"macro_path must be of shape '<lib_uobject_path>:<macro_name>'; "
            f"got {macro_path!r}"
        )
        return None
    # Split on the LAST ':' so package paths with a Windows drive letter or
    # an embedded ':' don't break the parse — UE asset paths use the form
    # `/Path/To/Lib.LibName` (package.objectName), so the split point we want
    # is the trailing ':' separating the lib path from the macro name.
    lib_path, macro_name = macro_path.rsplit(":", 1)
    if not lib_path or not macro_name:
        result["errors"].append(
            f"macro_path must have non-empty lib_path and macro_name; got {macro_path!r}"
        )
        return None

    lib = unreal.load_object(None, lib_path)
    if lib is None:
        result["errors"].append(
            f"load_object returned None for macro library {lib_path!r}"
        )
        return None
    if not isinstance(lib, unreal.Blueprint):
        result["errors"].append(
            f"macro library at {lib_path!r} is {type(lib).__name__}, expected Blueprint"
        )
        return None

    # MacroGraphs is a CPF_Protected UPROPERTY on UBlueprint, so the Python
    # binding does NOT expose it as `lib.macro_graphs`. Walk it through the
    # reflection bridge (same pattern as `blueprint_graph._resolve_graph`
    # uses for FunctionGraphs / UbergraphPages / ImplementedInterfaces).
    ops_obj = _ops()
    n = ops_obj.get_array_length(lib, ["MacroGraphs"])
    available = []
    for i in range(max(0, n)):
        g = ops_obj.get_object_property_value(lib, ["MacroGraphs", f"[{i}]"])
        if g is None:
            continue
        gname = g.get_name()
        available.append(gname)
        if gname == macro_name:
            return g

    result["errors"].append(
        f"macro {macro_name!r} not found on library {lib_path!r}; "
        f"available: {sorted(available)}"
    )
    return None


def add_macro_instance_node(
    bp_path: str,
    graph_name: str,
    macro_path: str,
    position=(0, 0),
):
    """Spawn a ``UK2Node_MacroInstance`` into a K2 graph, pointed at an
    external macro graph (e.g. ``ForEachLoop`` / ``WhileLoop`` /
    ``ForEachLoopWithBreak``).

    Single highest-ROI op of the M28 catalog: one new bridge UFUNCTION
    unblocks five design.md sections that were stuck on "iterates X →
    blocked" because ForEachLoop is a macro instance, not an atomic
    K2Node, so the M28.3.x catalog couldn't author it.

    Args:
        bp_path: ``/Game/...`` path to the target Blueprint.
        graph_name: target graph (function / interface-override / ubergraph).
        macro_path: full path to a macro graph in the form
            ``"<lib_uobject_path>:<macro_name>"``. The lib path resolves
            to a ``UBlueprint`` (the macro library) via
            ``unreal.load_object``; the suffix after ``:`` matches a
            graph in the library's ``MacroGraphs`` array. Examples:

            - ``"/Engine/EditorBlueprintResources/StandardMacros.StandardMacros:ForEachLoop"``
            - ``"/Engine/EditorBlueprintResources/StandardMacros.StandardMacros:ForEachLoopWithBreak"``
            - ``"/Engine/EditorBlueprintResources/StandardMacros.StandardMacros:WhileLoop"``
            - ``"/Engine/EditorBlueprintResources/StandardMacros.StandardMacros:Reverse for Each Loop"``
        position: ``[x, y]`` / ``(x, y)`` / ``unreal.Vector2D``. Included in
            the determinism seed so two instances of the same macro at
            different positions in the same graph get distinct GUIDs.

    Returns:
        Standard op-result dict. ``after`` carries ``{node_guid, macro_path,
        spawned}``. Idempotent: if a macro instance with the same seed
        already exists, returns ``skipped`` with ``spawned=False``.

    Determinism: NodeGuid seeded as
    ``md5(<bp>:graph:<g>:macro:<lib_path.lib_name:macro_name>:<x>,<y>)``;
    pin IDs via ``SeedPinGuidsForNode`` AFTER ``AllocateDefaultPins`` so
    the mirrored Tunnel/Result pins (whose count + names depend on the
    macro's signature) get deterministic PinIds. Library path is in the
    seed so two different ForEachLoop variants from different libraries
    don't collide.

    Default pins: K2Node_MacroInstance mirrors the macro's own Tunnel
    (entry) and Result (exit) pins onto the instance. For the
    StandardMacros ForEachLoop these are: ``execute`` (exec in), ``Array``
    (array in, wildcard), ``Array Element`` (typed out), ``Array Index``
    (int out), ``LoopBody`` (exec out), ``Completed`` (exec out).
    """
    result = make_result(
        "add_macro_instance_node", bp_path, f"{graph_name}:{macro_path}"
    )

    if not graph_name:
        result["errors"].append("graph_name must be non-empty")
        return result

    bp = _load_bp(bp_path, result)
    if bp is None:
        return result

    pos = _coerce_position(position, result)
    if pos is None:
        return result

    macro_graph = _resolve_macro_graph(macro_path, result)
    if macro_graph is None:
        return result

    ops = _ops()
    node_r = ops.add_macro_instance_node(
        bp, unreal.Name(graph_name), macro_graph, pos
    )
    if not node_r.success:
        result["errors"].append(
            f"add_macro_instance_node bridge call failed: {node_r.error_message}"
        )
        return result

    node_guid = _guid_str(node_r.node_guid)

    if node_r.skipped:
        result["success"] = True
        result["skipped"] = "macro instance already exists at this position"
        result["after"] = {
            "node_guid": node_guid,
            "macro_path": macro_path,
            "spawned": False,
        }
        return result

    if not ops.compile_and_save_package(bp):
        result["errors"].append(
            "compile_and_save_package returned False — BP compile failed "
            "or save refused (check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = {
        "node_guid": node_guid,
        "macro_path": macro_path,
        "spawned": True,
    }
    return result


# ---------------------------------------------------------------------------
# M28.14 — struct-mutation node catalog (Make / Break / SetFields)
# ---------------------------------------------------------------------------


def _resolve_script_struct(struct_type_path: str, result: dict):
    """Resolve a UScriptStruct path to an ``unreal.ScriptStruct``.

    Mirrors ``add_dynamic_cast_node``'s class-resolution recipe: try
    ``unreal.load_object`` first (script structs are UObjects, not UClasses,
    so ``load_class`` doesn't apply). Returns the resolved struct or
    ``None`` (errors appended).

    Accepts engine structs (``/Script/CoreUObject.Vector``,
    ``/Script/Engine.HitResult``) and user-defined structs at
    ``/Game/...`` paths.
    """
    if not struct_type_path:
        result["errors"].append(
            "struct_type_path must be non-empty (Make/Break/SetFields requires a UScriptStruct)"
        )
        return None
    obj = unreal.load_object(None, struct_type_path)
    if obj is None:
        result["errors"].append(
            f"load_object returned None for struct_type_path {struct_type_path!r}"
        )
        return None
    if not isinstance(obj, unreal.ScriptStruct):
        result["errors"].append(
            f"struct_type_path did not resolve to a UScriptStruct: {struct_type_path!r} "
            f"is {type(obj).__name__}"
        )
        return None
    return obj


def add_make_struct_node(
    bp_path: str,
    graph_name: str,
    struct_type_path: str,
    position=(0, 0),
):
    """Spawn a ``UK2Node_MakeStruct`` — pure node that constructs a struct
    value from per-field input pins.

    First op of the M28.14 struct-mutation catalog. Driver: read-modify-write
    inside the M28.13 ForEachLoop body for design.md's UAIActionScorer
    per-element score updates and confidence-decay over ``S_TargetInfo``
    arrays — without struct authoring the loops can iterate but cannot
    author the body.

    Args:
        bp_path: ``/Game/...`` path to the target Blueprint.
        graph_name: target graph (function / interface-override / ubergraph).
        struct_type_path: UScriptStruct path. Engine structs use
            ``/Script/<Module>.<StructName>`` (e.g.
            ``/Script/CoreUObject.Vector``,
            ``/Script/Engine.HitResult``); user-defined structs use
            ``/Game/...``. Resolved via ``unreal.load_object``.
        position: ``[x, y]`` / ``(x, y)`` / ``unreal.Vector2D``.

    Returns:
        Standard op-result dict. ``after`` carries
        ``{node_guid, struct_type_path, spawned}``. Idempotent on seeded
        GUID (seed includes struct path + position).

    Determinism: NodeGuid seeded as
    ``md5(<bp>:graph:<g>:make_struct:<struct_path>:<x>,<y>)``;
    pin IDs via ``SeedPinGuidsForNode``.

    Default pins: one input pin per ``BlueprintVisible`` non-``BlueprintReadOnly``
    UPROPERTY on the struct, plus a single output pin carrying the
    constructed struct value. The exact pin set depends on the struct's
    UPROPERTY layout.
    """
    result = make_result(
        "add_make_struct_node", bp_path, f"{graph_name}:{struct_type_path}"
    )

    if not graph_name:
        result["errors"].append("graph_name must be non-empty")
        return result

    bp = _load_bp(bp_path, result)
    if bp is None:
        return result

    pos = _coerce_position(position, result)
    if pos is None:
        return result

    struct_type = _resolve_script_struct(struct_type_path, result)
    if struct_type is None:
        return result

    ops = _ops()
    node_r = ops.add_make_struct_node(
        bp, unreal.Name(graph_name), struct_type, pos
    )
    if not node_r.success:
        result["errors"].append(
            f"add_make_struct_node bridge call failed: {node_r.error_message}"
        )
        return result

    node_guid = _guid_str(node_r.node_guid)

    if node_r.skipped:
        result["success"] = True
        result["skipped"] = "MakeStruct already exists at this position"
        result["after"] = {
            "node_guid": node_guid,
            "struct_type_path": struct_type_path,
            "spawned": False,
        }
        return result

    if not ops.compile_and_save_package(bp):
        result["errors"].append(
            "compile_and_save_package returned False — BP compile failed "
            "or save refused (check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = {
        "node_guid": node_guid,
        "struct_type_path": struct_type_path,
        "spawned": True,
    }
    return result


def add_break_struct_node(
    bp_path: str,
    graph_name: str,
    struct_type_path: str,
    position=(0, 0),
):
    """Spawn a ``UK2Node_BreakStruct`` — pure node that splits a struct
    input into per-field output pins.

    Sibling of ``add_make_struct_node``; the read half of read-modify-write
    inside loop bodies.

    Args:
        bp_path: ``/Game/...`` path to the target Blueprint.
        graph_name: target graph (function / interface-override / ubergraph).
        struct_type_path: UScriptStruct path — same resolution as
            ``add_make_struct_node``.
        position: ``[x, y]`` / ``(x, y)`` / ``unreal.Vector2D``.

    Returns:
        Standard op-result dict. ``after`` carries
        ``{node_guid, struct_type_path, spawned}``. Idempotent on seeded
        GUID.

    Determinism: NodeGuid seeded as
    ``md5(<bp>:graph:<g>:break_struct:<struct_path>:<x>,<y>)``.

    Default pins: one input pin (struct value) + one output pin per
    ``BlueprintVisible`` UPROPERTY on the struct.
    """
    result = make_result(
        "add_break_struct_node", bp_path, f"{graph_name}:{struct_type_path}"
    )

    if not graph_name:
        result["errors"].append("graph_name must be non-empty")
        return result

    bp = _load_bp(bp_path, result)
    if bp is None:
        return result

    pos = _coerce_position(position, result)
    if pos is None:
        return result

    struct_type = _resolve_script_struct(struct_type_path, result)
    if struct_type is None:
        return result

    ops = _ops()
    node_r = ops.add_break_struct_node(
        bp, unreal.Name(graph_name), struct_type, pos
    )
    if not node_r.success:
        result["errors"].append(
            f"add_break_struct_node bridge call failed: {node_r.error_message}"
        )
        return result

    node_guid = _guid_str(node_r.node_guid)

    if node_r.skipped:
        result["success"] = True
        result["skipped"] = "BreakStruct already exists at this position"
        result["after"] = {
            "node_guid": node_guid,
            "struct_type_path": struct_type_path,
            "spawned": False,
        }
        return result

    if not ops.compile_and_save_package(bp):
        result["errors"].append(
            "compile_and_save_package returned False — BP compile failed "
            "or save refused (check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = {
        "node_guid": node_guid,
        "struct_type_path": struct_type_path,
        "spawned": True,
    }
    return result


def add_set_fields_in_struct_node(
    bp_path: str,
    graph_name: str,
    struct_type_path: str,
    fields_to_show,
    position=(0, 0),
):
    """Spawn a ``UK2Node_SetFieldsInStruct`` — imperative node that takes a
    struct input, sets a configurable subset of its fields from input pins,
    and emits the modified struct as output.

    The "modify" half of read-modify-write inside loop bodies (Make =
    construct, Break = read, SetFields = modify-in-place). UE editor surfaces
    this as a node titled "Set members in <StructName>".

    Args:
        bp_path: ``/Game/...`` path to the target Blueprint.
        graph_name: target graph.
        struct_type_path: UScriptStruct path — same resolution as
            ``add_make_struct_node``.
        fields_to_show: ``list[str]`` of UPROPERTY names to expose as input
            pins. Required (non-empty). Field names must match struct
            UPROPERTYs case-sensitively — the bridge errors out on any
            unknown name to avoid silent typo no-ops. Sorted in the
            determinism seed so caller-side ordering doesn't drift the
            NodeGuid.
        position: ``[x, y]`` / ``(x, y)`` / ``unreal.Vector2D``.

    Returns:
        Standard op-result dict. ``after`` carries
        ``{node_guid, struct_type_path, fields_to_show, spawned}``.
        Idempotent on seeded GUID.

    Determinism: NodeGuid seeded as
    ``md5(<bp>:graph:<g>:set_fields_in_struct:<struct_path>:fields:<sorted_fields>:<x>,<y>)``.

    Default pins: exec in/out + struct in + struct out, plus one input pin
    per name in ``fields_to_show``. Note that
    ``UK2Node_SetFieldsInStruct::FSetFieldsInStructPinManager::GetRecordDefaults``
    initializes ``bShowPin = false`` for every property (vs Make/Break which
    default to true), so an empty ``fields_to_show`` would produce a node
    with no settable pins — the bridge rejects this up front.
    """
    result = make_result(
        "add_set_fields_in_struct_node",
        bp_path,
        f"{graph_name}:{struct_type_path}",
    )

    if not graph_name:
        result["errors"].append("graph_name must be non-empty")
        return result

    if not isinstance(fields_to_show, (list, tuple)):
        result["errors"].append(
            f"fields_to_show must be a list of strings; got {type(fields_to_show).__name__}"
        )
        return result
    if len(fields_to_show) == 0:
        result["errors"].append(
            "fields_to_show is empty — UK2Node_SetFieldsInStruct defaults bShowPin=false "
            "for every field, so an empty list produces a node with no usable input pins. "
            "Pass at least one field name."
        )
        return result
    for field in fields_to_show:
        if not isinstance(field, str) or not field:
            result["errors"].append(
                f"fields_to_show entries must be non-empty strings; got {field!r}"
            )
            return result

    bp = _load_bp(bp_path, result)
    if bp is None:
        return result

    pos = _coerce_position(position, result)
    if pos is None:
        return result

    struct_type = _resolve_script_struct(struct_type_path, result)
    if struct_type is None:
        return result

    fields_arr = unreal.Array(unreal.Name)
    for field in fields_to_show:
        fields_arr.append(unreal.Name(field))

    ops = _ops()
    node_r = ops.add_set_fields_in_struct_node(
        bp, unreal.Name(graph_name), struct_type, fields_arr, pos
    )
    if not node_r.success:
        result["errors"].append(
            f"add_set_fields_in_struct_node bridge call failed: {node_r.error_message}"
        )
        return result

    node_guid = _guid_str(node_r.node_guid)
    fields_list = list(fields_to_show)

    if node_r.skipped:
        result["success"] = True
        result["skipped"] = "SetFieldsInStruct already exists at this position"
        result["after"] = {
            "node_guid": node_guid,
            "struct_type_path": struct_type_path,
            "fields_to_show": fields_list,
            "spawned": False,
        }
        return result

    if not ops.compile_and_save_package(bp):
        result["errors"].append(
            "compile_and_save_package returned False — BP compile failed "
            "or save refused (check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = {
        "node_guid": node_guid,
        "struct_type_path": struct_type_path,
        "fields_to_show": fields_list,
        "spawned": True,
    }
    return result


# ---------------------------------------------------------------------------
# M28.11 — custom-event typed-parameter authoring
# ---------------------------------------------------------------------------


def add_custom_event_input(
    bp_path: str,
    graph_name: str,
    event_name: str,
    pin_name: str,
    var_type_spec: str,
    default_value: str = "",
):
    """Append an input parameter to a UK2Node_CustomEvent in an ubergraph.

    Sibling of M28.3.3's ``add_custom_event_node`` for typed parameter
    authoring. The pin lives on the CustomEvent node (UE pin direction
    EGPD_Output — the event's outputs flow INTO the event-handler body,
    hence they appear as the event's inputs in the editor's Details
    panel).

    Args:
        bp_path: ``/Game/...`` path to the target Blueprint.
        graph_name: name of the ubergraph holding the event (usually
            ``"EventGraph"``). The bridge walks every ``Blueprint->UbergraphPages``
            for a ``UK2Node_CustomEvent`` whose ``CustomFunctionName`` matches
            ``event_name``, so this kwarg is informational at the bridge level
            (kept in the Python signature for symmetry with
            ``add_custom_event_node`` and for future scoping if multiple
            ubergraphs ever carry same-named events). The Python op surfaces
            ``graph_name`` in the result dict so plan authors can confirm the
            event was found in the expected graph.
        event_name: ``CustomFunctionName`` of the target event — same name
            passed to ``add_custom_event_node``. Bridge errors out clearly if
            no matching event exists.
        pin_name: name of the new input parameter. Must be unique within the
            event's ``UserDefinedPins`` array.
        var_type_spec: pin-type spec — see ``add_function_input`` /
            ``add_bp_variable`` for the catalog.
        default_value: literal default value as a string in
            ``FProperty::ImportText_Direct`` format. Empty = no default.

    Returns:
        Standard op-result dict. Idempotent on the pin name.

    Determinism: ``PinId`` is seeded as
    ``md5(<bp>:custom_event:<event>:userpin:<pin>:out)``.

    Design.md driver: encounter-director ↔ AI.Order custom-event channel
    (item #1) — typed event parameters carry the order payload (target ref,
    priority, callout-tag) to listeners without the member-variable
    handshake workaround.
    """
    result = make_result(
        "add_custom_event_input", bp_path, f"{graph_name}:{event_name}:{pin_name}"
    )

    if not graph_name:
        result["errors"].append("graph_name must be non-empty")
        return result
    if not event_name:
        result["errors"].append("event_name must be non-empty")
        return result
    if not pin_name:
        result["errors"].append("pin_name must be non-empty")
        return result
    if not isinstance(default_value, str):
        result["errors"].append(
            f"default_value must be a string (UE ImportText format); "
            f"got {type(default_value).__name__}"
        )
        return result

    bp = _load_bp(bp_path, result)
    if bp is None:
        return result

    pin_type = _resolve_pin_type(var_type_spec, result)
    if pin_type is None:
        return result

    ops = _ops()
    r = ops.add_function_user_defined_pin(
        bp,
        unreal.Name(event_name),
        unreal.Name(pin_name),
        pin_type,
        True,  # bDirectionIsOutput — CustomEvent's outputs are event inputs
        default_value,
    )
    if not r.success:
        result["errors"].append(
            f"add_function_user_defined_pin bridge call failed: {r.error_message}"
        )
        return result

    result["before"] = r.before_text

    if r.skipped:
        result["success"] = True
        result["skipped"] = "user-defined pin already exists"
        result["after"] = r.after_text
        return result

    if not ops.compile_and_save_package(bp):
        result["errors"].append(
            "compile_and_save_package returned False — BP compile failed "
            "or save refused (check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = r.after_text
    return result
