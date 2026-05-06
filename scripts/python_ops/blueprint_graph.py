"""Blueprint function-graph authoring ops via the M26.1 reflection bridge.

Motivating case: `BP_EnemyBase` in Legacy's `CombatPrototype` declares
`BPI_Targetable` but has no `GetTargetingInfo` override. UE's message-call
returns defaults (`bIsAlive=false`, `Faction=0`) for every call, so the
combat behaviour tree never classifies anyone as hostile and enemies stand
around in Flat Arena. The minimal fix is a 3-pin passthrough override that
wires `this.bIsAlive` / literal `true` / `this.Faction` into the three
Return pins. This op performs exactly that class of edit in one step,
idempotently.

Bridge surface used (all new UFUNCTIONs in M26.1):
    - OverrideInterfaceFunction (creates the function graph + Entry/Return
      nodes, seeded with deterministic GUIDs)
    - FindGraphEndpoints (reports Entry/Return NodeGuids)
    - AddSelfMemberGetNode (deterministic-GUID VariableGet bound to self)
    - ConnectPinsByName (invokes UEdGraphSchema_K2::TryCreateConnection)
    - SetNodePinLiteralDefault (schema-aware pin DefaultValue writer)
"""

import unreal

from ._common import make_result


SELF_PREFIX = "self."

ZERO_GUID_STR = "00000000-0000-0000-0000-000000000000"


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


_ZERO_GUID_HEX = "00000000000000000000000000000000"


def _guid_str(guid) -> str:
    """Hex form of an FGuid (Digits format: 32 lowercase hex chars, no
    separators). UE Python's default `str(fguid)` returns the generic
    struct repr `"<Struct 'Guid' (0x...) {}>"` — don't rely on that;
    `.to_string()` is the correct accessor."""
    try:
        return guid.to_string()
    except Exception:
        return str(guid)


def _guid_is_zero(guid) -> bool:
    """FGuid::IsValid() is `(A|B|C|D) != 0`; we mirror that via the hex
    string `.to_string()` returns. Note UE Python's FGuid `.to_tuple()`
    returns `()` (not the four uint32 fields) in 5.7, so the tuple
    approach doesn't work — stick with the string form."""
    return _guid_str(guid) == _ZERO_GUID_HEX


def implement_interface_function(
    bp_path: str,
    interface_bp_path: str,
    function_name: str,
    output_bindings: dict,
    force_rebind: bool = False,
):
    """Create an interface-function override on `bp_path` and wire its Return
    pins to BP member variables (self-context) or literal defaults.

    Args:
        bp_path: ``/Game/...`` path to the target Blueprint. The BP MUST
            already declare ``interface_bp_path`` on its
            ``ImplementedInterfaces`` list (adding an interface to a BP is
            out of scope — do that in the BP editor).
        interface_bp_path: ``/Game/...`` path to the interface Blueprint.
            The op reads ``interface_bp.generated_class()`` and asserts the
            function exists on that class.
        function_name: name of the interface function to override. Must
            match a ``UFunction`` on ``interface_bp.generated_class()``.
        output_bindings: dict mapping each Return pin name to a binding
            spec string:

              - ``"self.<VarName>"``  — wire the Return pin to a
                ``K2Node_VariableGet`` bound to the named BP-member
                variable (self context). Get node is placed deterministically
                left of the Return node.
              - any other string    — set the Return pin's
                ``DefaultValue`` literal; UE schema coerces per pin type
                (``"true"`` for bool, ``"42"`` for int, struct importtext
                for FVector etc.).
        force_rebind: when True AND the override graph already exists,
            wipe every non-Entry/non-Return node out of the existing graph
            and re-run the binding logic on a clean slate. Default False
            preserves the idempotent-skip behaviour. Use True to unblock
            the common scenario where the editor auto-created a stub override
            (clicking "add function" on an interface in the UI) that the op
            otherwise mistakes for a completed authoring pass. Entry / Return
            nodes are preserved so their seeded NodeGuids stay stable.

    Returns:
        Standard op-result dict. ``after`` carries the list of bindings
        applied plus Entry / Return / Get-node GUIDs for the run report.
        When ``force_rebind=True`` and the graph was wiped first, ``after``
        includes ``wiped_nodes`` (count of removed body nodes).
        Idempotent on the default path: if an override graph with
        ``function_name`` already exists and ``force_rebind=False``, returns
        success with ``skipped`` and does not touch output bindings.

    Pin-name conventions (documented because the op hides them from
    plan authors):
      - The Entry node's execution output pin is ``"then"``.
      - The Return node's execution input pin is ``"execute"``.
      - A VariableGet node's data output pin is named after the variable
        (e.g. ``self.bIsAlive`` → output pin ``bIsAlive``).
      - The Return node's data input pin is named per the interface
        function signature (must match the ``output_bindings`` key).

    Determinism: node GUIDs (Entry / Return / per-binding Get) are seeded
    via md5 over ``(bp_path, function_name, kind, member_name?)``. Running
    the op twice against the same baseline produces byte-identical
    ``.uasset`` — the golden BugHunt fixture strategy depends on this.
    """
    result = make_result(
        "implement_interface_function",
        bp_path,
        f"{interface_bp_path}:{function_name}",
    )

    if not isinstance(output_bindings, dict):
        result["errors"].append(
            f"output_bindings must be a dict, got {type(output_bindings).__name__}"
        )
        return result
    if not function_name:
        result["errors"].append("function_name is empty")
        return result

    bp = _load_bp(bp_path, result)
    if bp is None:
        return result

    interface_bp = _load_bp(interface_bp_path, result)
    if interface_bp is None:
        return result

    interface_class = interface_bp.generated_class()
    if interface_class is None:
        result["errors"].append(
            f"interface_bp {interface_bp_path!r} has no generated_class"
        )
        return result

    ops = _ops()
    fn_name = unreal.Name(function_name)

    override_r = ops.override_interface_function(bp, interface_class, fn_name)
    if not override_r.success:
        result["errors"].append(
            f"override_interface_function failed: {override_r.error_message}"
        )
        return result

    result["before"] = {"override_exists": bool(override_r.skipped)}
    wiped_nodes = 0

    if override_r.skipped:
        if not force_rebind:
            result["success"] = True
            result["skipped"] = f"override graph {function_name!r} already exists"
            result["after"] = {
                "override_exists": True,
                "bindings_applied": False,
            }
            return result

        # force_rebind: clear every non-Entry / non-Return node out of the
        # existing graph so the binding logic below runs on a clean slate.
        # Entry / Return keep their seeded NodeGuids so downstream references
        # by GUID stay stable.
        wipe_r = ops.wipe_function_graph_body(bp, fn_name)
        if not wipe_r.success:
            result["errors"].append(
                f"wipe_function_graph_body failed: {wipe_r.error_message}"
            )
            return result
        try:
            wiped_nodes = int(wipe_r.after_text or "0")
        except (TypeError, ValueError):
            wiped_nodes = 0

    endpoints = ops.find_graph_endpoints(bp, fn_name)
    if not endpoints.success:
        result["errors"].append(
            f"find_graph_endpoints failed: {endpoints.error_message}"
        )
        return result

    entry_guid = endpoints.entry_guid
    return_guid = endpoints.return_guid
    has_return = not _guid_is_zero(return_guid)

    # Interface-function overrides in UE don't get a UK2Node_FunctionResult
    # node — UE models the function's output parameters as EGPD_Input pins
    # on the Entry node (same convention the interface BP itself uses). The
    # bridge's FindGraphEndpoints reports ReturnGuid=0 in that case.
    # Output bindings wire to Entry instead of Return, and the Entry.then
    # -> Return.execute exec wire is skipped (execution terminates at the
    # end of Entry's sequence, which UE treats as "function returns with
    # whatever values were written to Entry's output pins").
    output_target_guid = return_guid if has_return else entry_guid
    output_target_label = "Return" if has_return else "Entry"

    applied = []

    if has_return:
        wire = ops.connect_pins_by_name(
            bp, fn_name,
            entry_guid, unreal.Name("then"),
            return_guid, unreal.Name("execute"),
        )
        if not wire.success and not wire.skipped:
            result["errors"].append(
                f"Entry.then -> Return.execute wire failed: {wire.error_message}"
            )
            return result

    # Output bindings — sorted by pin name for determinism (node positions
    # depend on enumeration index).
    get_node_guids = {}
    for index, (pin_name, binding) in enumerate(sorted(output_bindings.items())):
        if not isinstance(binding, str):
            result["errors"].append(
                f"binding for {pin_name!r} must be a string (got {type(binding).__name__})"
            )
            return result

        if binding.startswith(SELF_PREFIX):
            var_name = binding[len(SELF_PREFIX):]
            if not var_name:
                result["errors"].append(
                    f"binding {binding!r} has empty variable name after 'self.'"
                )
                return result

            # Layout: vertical column of Get nodes to the left of Return.
            # 400u left + 100u per index puts each Get cleanly separated.
            pos = unreal.Vector2D(-400.0, 100.0 * index)
            get_r = ops.add_self_member_get_node(
                bp, fn_name, unreal.Name(var_name), pos
            )
            if not get_r.success:
                result["errors"].append(
                    f"add_self_member_get_node({var_name!r}) failed: {get_r.error_message}"
                )
                return result

            get_guid = get_r.node_guid
            get_node_guids[var_name] = _guid_str(get_guid)

            conn = ops.connect_pins_by_name(
                bp, fn_name,
                get_guid, unreal.Name(var_name),
                output_target_guid, unreal.Name(pin_name),
            )
            if not conn.success and not conn.skipped:
                result["errors"].append(
                    f"connect Get.{var_name} -> {output_target_label}.{pin_name} failed: {conn.error_message}"
                )
                return result

            applied.append({
                "pin": pin_name,
                "kind": "self_var",
                "source": var_name,
            })

        else:
            set_r = ops.set_node_pin_literal_default(
                bp, fn_name, output_target_guid, unreal.Name(pin_name), binding
            )
            if not set_r.success and not set_r.skipped:
                result["errors"].append(
                    f"set literal {binding!r} on {output_target_label}.{pin_name} failed: {set_r.error_message}"
                )
                return result

            applied.append({
                "pin": pin_name,
                "kind": "literal",
                "value": binding,
            })

    if not ops.compile_and_save_package(bp):
        result["errors"].append(
            "compile_and_save_package returned False — BP compile failed or "
            "save refused (check UE log for compile errors)"
        )
        return result

    result["success"] = True
    result["after"] = {
        "override_exists": True,
        "bindings_applied": True,
        "wiped_nodes": wiped_nodes,
        "bindings": applied,
        "entry_guid": _guid_str(entry_guid),
        "return_guid": _guid_str(return_guid) if has_return else None,
        "get_node_guids": get_node_guids,
    }
    return result


# ---------------------------------------------------------------------------
# M28.2 — connect existing pins in any K2 graph
#
# Driver: BP_Task_Peek.EventGraph Branch.else is unconnected, so the task
# hangs at the peek point and never calls FinishTask. The fix is a single
# wire: Branch.else (FGuid already on disk) → existing FinishTask node
# (FGuid also on disk). Both GUIDs are exposed by the MCP's
# `get_asset_deep_dump` — this op lets a plan author consume them as hex
# strings.
# ---------------------------------------------------------------------------


def _resolve_graph(bp, graph_name: str):
    """Walk FunctionGraphs + ImplementedInterfaces[].Graphs + UbergraphPages
    via the reflection bridge (Python-protected UPROPERTYs so we can't use
    get_editor_property), return the first UEdGraph whose FName matches.

    Returns the graph UObject or None.
    """
    ops = _ops()
    for arr_name in ("FunctionGraphs", "UbergraphPages"):
        n = ops.get_array_length(bp, [arr_name])
        for i in range(max(0, n)):
            g = ops.get_object_property_value(bp, [arr_name, f"[{i}]"])
            if g is not None and str(g.get_fname()) == graph_name:
                return g
    ifaces_len = ops.get_array_length(bp, ["ImplementedInterfaces"])
    for i in range(max(0, ifaces_len)):
        gl = ops.get_array_length(bp, ["ImplementedInterfaces", f"[{i}]", "Graphs"])
        for j in range(max(0, gl)):
            g = ops.get_object_property_value(
                bp, ["ImplementedInterfaces", f"[{i}]", "Graphs", f"[{j}]"]
            )
            if g is not None and str(g.get_fname()) == graph_name:
                return g
    return None


def _find_node_runtime_guid(bp, graph, selector: dict, result: dict):
    """Resolve a runtime ``NodeGuid`` (32-char hex) for a node in ``graph``.

    Accepts two selector forms:
      - ``{"guid": "<32-char-hex>"}`` — trusts the caller's guid. Returned
        as-is; the bridge's ConnectPinsByName does the lookup. Kept for the
        rare case a caller already has the live runtime guid in hand.
      - ``{"class": "<NodeClassName>", "pos": [x, y]}`` — iterates Nodes[]
        via the reflection bridge, matches by (runtime class name,
        NodePosX, NodePosY). Necessary because `DeepDumpRenderer` emits
        a STABLE hash (see BlueprintSerializer.cpp::ComputeStableNodeHash)
        not the runtime FGuid — the hash is deterministic across loads
        but unusable for engine-side lookup.

    Returns the runtime guid string or None. On failure appends to result.
    """
    if "guid" in selector:
        return selector["guid"]

    cls = selector.get("class")
    pos = selector.get("pos")
    if not cls or pos is None:
        result["errors"].append(
            f"node selector must carry 'guid' OR ('class' + 'pos'); got {selector!r}"
        )
        return None
    if not isinstance(pos, (list, tuple)) or len(pos) != 2:
        result["errors"].append(
            f"'pos' must be a [x, y] pair; got {pos!r}"
        )
        return None
    target_x, target_y = int(pos[0]), int(pos[1])

    ops = _ops()
    n = ops.get_array_length(graph, ["Nodes"])
    candidates = []
    for i in range(max(0, n)):
        node = ops.get_object_property_value(graph, ["Nodes", f"[{i}]"])
        if node is None:
            continue
        # UE's Python bindings expose K2Node SUBCLASSES inconsistently: common
        # ones (``K2Node_CallFunction`` / ``K2Node_VariableGet``) are bound,
        # but engine-internal subclasses (``K2Node_IfThenElse`` / ``K2Node_Knot``)
        # fall back to the base ``unreal.K2Node`` wrapper, so
        # ``type(node).__name__`` is lossy. Match via UClass path instead —
        # always surfaces the exact C++ class regardless of binding coverage.
        node_cls_path = node.get_class().get_path_name()
        # Path form: "/Script/BlueprintGraph.K2Node_IfThenElse".
        # Accept unqualified tail (``"K2Node_IfThenElse"``) OR fully qualified.
        node_cls_tail = node_cls_path.rsplit(".", 1)[-1]
        if cls != node_cls_path and cls != node_cls_tail:
            continue
        x_res = ops.get_property_value(node, ["NodePosX"])
        y_res = ops.get_property_value(node, ["NodePosY"])
        if not x_res.success or not y_res.success:
            continue
        try:
            x = int(x_res.after_text)
            y = int(y_res.after_text)
        except ValueError:
            continue
        candidates.append((x, y, node_cls_tail))
        if x == target_x and y == target_y:
            g_res = ops.get_property_value(node, ["NodeGuid"])
            return g_res.after_text if g_res.success else None

    result["errors"].append(
        f"no node of class {cls!r} at position ({target_x}, {target_y}); "
        f"candidates matching class: {candidates[:10]}"
    )
    return None


def _parse_node_selector(raw: str) -> dict:
    """Parse a node selector string into a ``{kind, ...}`` dict.

    Two forms:
      - 32-char hex (optionally dash-grouped) → ``{"kind": "guid",
        "guid": <raw>}``. The op passes this through to
        ``ConnectGraphPinsByGuidString`` verbatim. Only usable when the
        caller already has the runtime ``UEdGraphNode::NodeGuid``.
      - ``"@<ClassName>:<x>,<y>"`` → ``{"kind": "class_pos",
        "class": ClassName, "x": int, "y": int}``. Matches a node by
        its runtime class + authored NodePosX/Y. This is the recommended
        form because the inventory's ``.deep.md`` / ``.meta.json``
        expose a STABLE hash (``BlueprintSerializer::ComputeStableNodeHash``)
        for determinism, not the runtime FGuid — so the deep-dump GUID
        column cannot be fed into a live-engine lookup directly.

    Raises ``ValueError`` on malformed input with a pointer to the two
    accepted shapes.
    """
    if not isinstance(raw, str) or not raw:
        raise ValueError(
            f"node selector must be a non-empty string; got {raw!r}"
        )
    if raw.startswith("@"):
        # "@K2Node_IfThenElse:2304,-416"
        body = raw[1:]
        if ":" not in body or "," not in body:
            raise ValueError(
                f"class+position selector {raw!r} must be @<Class>:<x>,<y>"
            )
        cls, pos = body.split(":", 1)
        xs, ys = pos.split(",", 1)
        try:
            return {"kind": "class_pos", "class": cls, "x": int(xs), "y": int(ys)}
        except ValueError as exc:
            raise ValueError(
                f"class+position selector {raw!r} x/y must be ints: {exc}"
            )
    return {"kind": "guid", "guid": raw}


def connect_graph_pins(
    bp_path: str,
    graph_name: str,
    from_node_guid: str,
    from_pin: str,
    to_node_guid: str,
    to_pin: str,
):
    """Wire two existing pins in a Blueprint graph.

    Args:
        bp_path: ``/Game/...`` path to the Blueprint.
        graph_name: name of the target graph. Accepts:
            - a function graph name (``"GetTargetingInfo"``)
            - an interface-override graph name (same string — they live
              on ``ImplementedInterfaces[].Graphs`` but resolve by FName)
            - an ubergraph page (``"EventGraph"`` — default ubergraph)
        from_node_guid: selector string. **Two accepted forms:**

            1. ``"@<NodeClassName>:<x>,<y>"`` — RECOMMENDED. Matches a
               node by runtime class + authored (NodePosX, NodePosY).
               Class name may be unqualified (``"K2Node_IfThenElse"``)
               or fully qualified
               (``"/Script/BlueprintGraph.K2Node_IfThenElse"``). Pull the
               coords from the deep dump's ``Position: (X, Y)`` line.

            2. 32-char hex (optionally dash-grouped) — a runtime
               ``UEdGraphNode::NodeGuid``. Usable only when the caller
               already has the live runtime GUID (e.g., from a prior
               op's result). **The GUID column in ``.deep.md`` /
               ``.meta.json`` is NOT a runtime GUID** — it's a stable
               content-hash (``BlueprintSerializer::ComputeStableNodeHash``)
               that's unrecognised by ``ConnectPinsByName``. Use form 1
               when sourcing from the inventory.
        from_pin: source pin display name. Branch nodes use engine pin
            names: ``"then"`` for the true branch, ``"else"`` for the
            false branch. Exec-in is ``"execute"``.
        to_node_guid: same two forms as ``from_node_guid``.
        to_pin: destination pin display name.

    Returns:
        Standard op-result dict. ``after`` carries ``{linked: bool}``.
        Idempotent: already-linked pins return success with ``skipped``.

    Idempotence: ``BpxReflectionOps::ConnectPinsByName`` short-circuits
    when the two pins are already in each other's ``LinkedTo`` arrays.
    Running this op twice against the same baseline is safe.
    """
    result = make_result(
        "connect_graph_pins",
        bp_path,
        f"{graph_name}:{from_pin} -> {to_pin}",
    )

    if not graph_name:
        result["errors"].append("graph_name must be non-empty")
        return result
    if not from_pin:
        result["errors"].append("from_pin must be non-empty")
        return result
    if not to_pin:
        result["errors"].append("to_pin must be non-empty")
        return result

    bp = _load_bp(bp_path, result)
    if bp is None:
        return result

    graph = _resolve_graph(bp, graph_name)
    if graph is None:
        result["errors"].append(
            f"no graph named {graph_name!r} on {bp_path!r} — see BP's "
            f"FunctionGraphs / UbergraphPages / ImplementedInterfaces.Graphs"
        )
        return result

    # Resolve both node selectors to runtime NodeGuids.
    try:
        from_selector = _parse_node_selector(from_node_guid)
        to_selector = _parse_node_selector(to_node_guid)
    except ValueError as exc:
        result["errors"].append(str(exc))
        return result
    if from_selector["kind"] == "class_pos":
        from_selector = {
            "class": from_selector["class"],
            "pos": [from_selector["x"], from_selector["y"]],
        }
    if to_selector["kind"] == "class_pos":
        to_selector = {
            "class": to_selector["class"],
            "pos": [to_selector["x"], to_selector["y"]],
        }
    from_guid = _find_node_runtime_guid(bp, graph, from_selector, result)
    if not from_guid:
        return result
    to_guid = _find_node_runtime_guid(bp, graph, to_selector, result)
    if not to_guid:
        return result
    from_node_guid = from_guid
    to_node_guid = to_guid

    ops = _ops()
    r = ops.connect_graph_pins_by_guid_string(
        bp,
        unreal.Name(graph_name),
        from_node_guid,
        unreal.Name(from_pin),
        to_node_guid,
        unreal.Name(to_pin),
    )
    if not r.success:
        result["errors"].append(
            f"connect_graph_pins_by_guid_string failed: {r.error_message}"
        )
        return result

    if r.skipped:
        result["success"] = True
        result["skipped"] = "pins already linked"
        result["after"] = {"linked": True, "already": True}
        return result

    if not ops.compile_and_save_package(bp):
        result["errors"].append(
            "compile_and_save_package returned False — BP compile failed "
            "or save refused (check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = {"linked": True, "already": False}
    return result
