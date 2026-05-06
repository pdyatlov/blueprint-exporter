"""Structural Blueprint edits via the M28.2 reflection bridge.

M28.2 covers the four structural-edit ops design.md needs to author the
combat-AI surface end-to-end through MCP:

  - add_bp_variable        (M28.2.1, shipped)
  - add_bp_function        (M28.2.2, shipped)
  - add_component_to_scs   (M28.2.3, shipped)
  - add_bp_interface       (M28.2.4, this op)

Each op stays inside the standard "load asset → call op → compile + save"
envelope. The bridge UFUNCTIONs are minimal — they only exist to seed
deterministic GUIDs over engine APIs that internally call FGuid::NewGuid()
(VarGuid for variables, GraphGuid for functions / interface graphs,
USCS_Node::VariableGuid for SCS components).

M28.2.0 research assumed USCS_Node::VariableGuid was name-hash
deterministic and add_component_to_scs would be pure-Python. Code
inspection during M28.2.3 disproved that: USCS_Node::ValidateGuid only
fires its name-hash seed path when `!VariableGuid.IsValid()`, but
`SimpleConstructionScript::CreateNodeImpl` assigns `FGuid::NewGuid()` to
VariableGuid before that, so the hash path is never taken for freshly-
created nodes. A 3rd bridge UFUNCTION (`AddComponentToSCSDeterministic`)
closes the gap.

Idempotence: every op short-circuits on a name-match in the BP's existing
declarations; second run with the same plan is a no-op (no save).

Determinism: every op's identifier GUIDs are seeded via
SeedGuidFromJoined(bp_path + ":<kind>:" + <name>) so post-op .uasset
bytes are reproducible across re-runs. The M28.pre.3 soak gate enforces
this — without the seeding, round 2 would produce a different md5 than
round 1 every time.
"""

import unreal

from ._common import compile_and_save_blueprint, load_bp, make_result


# Public list of canonical pin-type spec strings for `add_bp_variable`.
# Documented here (not in the docstring alone) so plan authors can grep
# the catalog from the agent loop.
_BASIC_TYPE_NAMES = ("int", "byte", "bool", "real", "name", "string", "text")


def _ops():
    return unreal.BpxReflectionOps


def _resolve_pin_type(spec, result: dict):
    """Resolve a `var_type_spec` into an `unreal.EdGraphPinType`.

    Accepted forms (all strings — keeps plan JSON terse):

      - basic:    ``"int"`` / ``"byte"`` / ``"bool"`` / ``"real"`` /
                  ``"name"`` / ``"string"`` / ``"text"`` — routed via
                  ``unreal.BlueprintEditorLibrary.get_basic_type_by_name``.
                  Note: UE's "real" is the unified float / double pin
                  type (legacy ``"float"`` is also accepted as an alias
                  and mapped to ``"real"``).
      - struct:   ``"struct:/Script/CoreUObject.Vector"`` /
                  ``"struct:/Script/Game.S_TargetInfo"`` — loads the
                  ``UScriptStruct`` and routes via ``get_struct_type``.
      - object:   ``"object:/Script/AIModule.AIController"`` /
                  ``"object:/Game/MyBP.MyBP_C"`` — object reference;
                  loads the ``UClass`` and routes via
                  ``get_object_reference_type``.
      - class:    ``"class:/Script/AIModule.AIController"`` — TSubclassOf
                  reference; routes via ``get_class_reference_type``.
      - array:    ``"array:<inner_spec>"`` — recursive; inner_spec is
                  resolved as one of the above. E.g.
                  ``"array:int"`` / ``"array:struct:/Script/Game.S_TargetInfo"``.
      - set:      ``"set:<inner_spec>"`` — recursive; same inner-spec
                  rules as array.
      - map:      ``"map:<key_spec>=>>>:<value_spec>"`` — recursive on both
                  sides; key/value separated by the literal ``"=>>>"``
                  token (chosen to avoid colliding with ``":"`` inside
                  asset paths). E.g.
                  ``"map:name=>>>:int"`` for ``TMap<FName, int32>``.

    Returns the `unreal.EdGraphPinType` on success, None on failure
    (errors appended to ``result``).
    """
    if not isinstance(spec, str) or not spec:
        result["errors"].append(
            f"var_type_spec must be a non-empty string; got {spec!r}"
        )
        return None

    bel = unreal.BlueprintEditorLibrary

    # Container forms (recursive).
    if spec.startswith("array:"):
        inner = _resolve_pin_type(spec[len("array:"):], result)
        if inner is None:
            return None
        return bel.get_array_type(inner)
    if spec.startswith("set:"):
        inner = _resolve_pin_type(spec[len("set:"):], result)
        if inner is None:
            return None
        return bel.get_set_type(inner)
    if spec.startswith("map:"):
        body = spec[len("map:"):]
        if "=>>>:" not in body:
            result["errors"].append(
                f"map var_type_spec {spec!r} must use '=>>>:' as key/value "
                f"separator (chosen to avoid colliding with ':' inside asset paths)"
            )
            return None
        key_spec, val_spec = body.split("=>>>:", 1)
        key_type = _resolve_pin_type(key_spec, result)
        if key_type is None:
            return None
        val_type = _resolve_pin_type(val_spec, result)
        if val_type is None:
            return None
        return bel.get_map_type(key_type, val_type)

    # Object / class / struct refs.
    if spec.startswith("object:"):
        path = spec[len("object:"):]
        cls = unreal.load_class(None, path) or unreal.load_object(None, path)
        if cls is None:
            result["errors"].append(
                f"object var_type_spec: load failed for {path!r} — must be a "
                f"UClass path like '/Script/AIModule.AIController' or "
                f"'/Game/MyBP.MyBP_C'"
            )
            return None
        return bel.get_object_reference_type(cls)
    if spec.startswith("class:"):
        path = spec[len("class:"):]
        cls = unreal.load_class(None, path) or unreal.load_object(None, path)
        if cls is None:
            result["errors"].append(
                f"class var_type_spec: load failed for {path!r}"
            )
            return None
        return bel.get_class_reference_type(cls)
    if spec.startswith("struct:"):
        path = spec[len("struct:"):]
        struct = unreal.load_object(None, path)
        if struct is None or not isinstance(struct, unreal.ScriptStruct):
            result["errors"].append(
                f"struct var_type_spec: {path!r} did not resolve to a UScriptStruct"
            )
            return None
        return bel.get_struct_type(struct)

    # Basic types — accept "float" as a friendly alias for "real" since
    # that's the historical naming from pre-LWC UE.
    basic = "real" if spec == "float" else spec
    if basic not in _BASIC_TYPE_NAMES:
        result["errors"].append(
            f"unknown var_type_spec {spec!r}. Accepted: basic ({_BASIC_TYPE_NAMES}), "
            f"'object:<UClass-path>', 'class:<UClass-path>', "
            f"'struct:<UScriptStruct-path>', 'array:<inner>', 'set:<inner>', "
            f"'map:<key>=>>>:<value>'"
        )
        return None
    return bel.get_basic_type_by_name(unreal.Name(basic))


def add_bp_variable(
    bp_path: str,
    var_name: str,
    var_type_spec: str,
    default_value: str = "",
    instance_editable: bool = False,
):
    """Add a member variable to a Blueprint.

    Args:
        bp_path: ``/Game/...`` path to the target Blueprint.
        var_name: name of the new variable. Must be unique across the BP's
            inherited + declared variables (the bridge surfaces inherited
            collisions as a clear error rather than a generic engine warning).
        var_type_spec: type spec string. See ``_resolve_pin_type`` for
            the full catalog. Common forms:

              - ``"int"`` / ``"bool"`` / ``"real"`` / ``"string"``
              - ``"struct:/Script/CoreUObject.Vector"``
              - ``"object:/Script/AIModule.AIController"``
              - ``"array:int"`` / ``"array:struct:/Script/Game.S_TargetInfo"``
        default_value: literal default value as a string in the same
            format ``FBPVariableDescription::DefaultValue`` accepts:
            ``"true"`` for bool, ``"42"`` for int, ``"(X=1.0,Y=2.0)"``
            for vectors. Empty string = type default. Note: UE expects a
            *string*; the executor's ``_convert_value`` is bypassed on this
            kwarg because the bridge needs the raw text for ImportText.
        instance_editable: when True, sets the ``CPF_DisableEditOnInstance``
            flag OFF after the add (= "Instance Editable" checkbox in the
            BP editor) by chaining ``unreal.BlueprintEditorLibrary
            .set_blueprint_variable_instance_editable``. Default False
            preserves UE's stricter default (variable hidden on placed
            instances unless explicitly exposed — matches editor UI).

    Returns:
        Standard op-result dict. ``after`` carries
        ``{"var_name": <name>, "var_type": <spec>, "instance_editable": bool}``.
        Idempotent: if a variable with ``var_name`` already exists on the
        BP's declared (non-inherited) list, returns success with
        ``skipped="variable already exists"`` and does NOT touch the
        existing variable's type or metadata flags.

    Determinism: VarGuid is seeded post-add via
    ``SeedGuidFromJoined(bp_path + ":var:" + var_name)`` by the
    ``AddMemberVariableDeterministic`` UFUNCTION. Without this, the engine
    assigns ``FGuid::NewGuid()`` and ``.uasset`` md5 drifts every run —
    M28.pre.3 soak gate would catch it on round 2.
    """
    result = make_result("add_bp_variable", bp_path, var_name)

    if not var_name:
        result["errors"].append("var_name must be non-empty")
        return result
    if not isinstance(default_value, str):
        result["errors"].append(
            f"default_value must be a string (UE ImportText format); "
            f"got {type(default_value).__name__}"
        )
        return result

    bp = load_bp(bp_path, result)
    if bp is None:
        return result

    pin_type = _resolve_pin_type(var_type_spec, result)
    if pin_type is None:
        return result

    ops = _ops()
    fn = unreal.Name(var_name)
    add_r = ops.add_member_variable_deterministic(bp, fn, pin_type, default_value)
    if not add_r.success:
        result["errors"].append(
            f"add_member_variable_deterministic failed: {add_r.error_message}"
        )
        return result

    result["before"] = {"var_exists": bool(add_r.skipped)}

    if add_r.skipped:
        result["success"] = True
        result["skipped"] = "variable already exists"
        result["after"] = {
            "var_name": var_name,
            "var_type": var_type_spec,
            "instance_editable": False,
            "added": False,
        }
        return result

    # Optional metadata. Run as a separate engine call so the bridge
    # UFUNCTION stays minimal (does one thing: deterministic add).
    if instance_editable:
        try:
            unreal.BlueprintEditorLibrary.set_blueprint_variable_instance_editable(
                bp, fn, True
            )
        except Exception as exc:
            result["errors"].append(
                f"set_blueprint_variable_instance_editable raised: {exc}"
            )
            return result

    if not compile_and_save_blueprint(bp, result):
        return result

    result["success"] = True
    result["after"] = {
        "var_name": var_name,
        "var_type": var_type_spec,
        "instance_editable": bool(instance_editable),
        "added": True,
    }
    return result


def add_bp_function(
    bp_path: str,
    function_name: str,
    is_pure: bool = False,
):
    """Add a blank member function graph to a Blueprint.

    Mirrors ``add_bp_variable``'s shape — deterministic bridge wrapper,
    idempotent on the function name, compile+save at the end. The op
    creates a standard void/void function with auto-generated Entry and
    Return nodes; subsequent M26.1 body-authoring ops
    (``AddSelfMemberGetNode``, ``ConnectPinsByName``,
    ``SetNodePinLiteralDefault``) chain off the returned ``entry_guid`` /
    ``return_guid`` to populate the body.

    Args:
        bp_path: ``/Game/...`` path to the target Blueprint.
        function_name: name of the new function. Validated through
            ``FKismetNameValidator`` bridge-side so reserved names or
            inherited-collision names are rejected with a structured
            error instead of being silently renamed.
        is_pure: when True, sets ``FUNC_BlueprintPure`` on the Entry
            node's ExtraFlags. Note: pure functions need at least one
            output param to compile cleanly — call this op with
            ``is_pure=True`` only when you plan to add an output and
            wire the Return pin in the same plan. Default False.

    Returns:
        Standard op-result dict. ``after`` carries
        ``{"function_name": <name>, "is_pure": bool, "entry_guid": <hex>,
        "return_guid": <hex>, "added": bool}``. Idempotent: if a graph
        named ``function_name`` already exists on the BP (function
        graphs, interface overrides, or ubergraphs — all three live in
        ``FindFunctionGraphByName``), returns success with
        ``skipped="function already exists"`` and populates the existing
        graph's Entry / Return GUIDs so chained authoring ops still work.

    Determinism: GraphGuid + Entry NodeGuid + Return NodeGuid + every
    Entry / Return pin's PinId are seeded post-create via
    ``SeedGuidFromJoined(bp_path + ":func:" + function_name + ":<slot>")``
    by the ``AddFunctionGraphDeterministic`` UFUNCTION. Without this, the
    engine would re-randomize all of those per-call and the .uasset md5
    would drift every run — M28.pre.3 soak gate would catch it.
    """
    result = make_result("add_bp_function", bp_path, function_name)

    if not function_name:
        result["errors"].append("function_name must be non-empty")
        return result

    bp = load_bp(bp_path, result)
    if bp is None:
        return result

    ops = _ops()
    fn = unreal.Name(function_name)
    add_r = ops.add_function_graph_deterministic(bp, fn, bool(is_pure))
    if not add_r.success:
        result["errors"].append(
            f"add_function_graph_deterministic failed: {add_r.error_message}"
        )
        return result

    # UE-Python FGuid doesn't expose `is_valid()`; mirror blueprint_graph's
    # pattern and derive emptiness from the hex string. `.to_string()` is
    # the only reliable accessor in 5.7 (the generic `str()` returns a
    # struct-repr, not the 32-char digest).
    _ZERO_GUID_HEX = "00000000000000000000000000000000"
    entry_guid_str = add_r.entry_guid.to_string()
    return_guid_str = add_r.return_guid.to_string()
    if entry_guid_str == _ZERO_GUID_HEX:
        entry_guid_str = ""
    if return_guid_str == _ZERO_GUID_HEX:
        return_guid_str = ""

    result["before"] = {"function_exists": bool(add_r.skipped)}

    if add_r.skipped:
        result["success"] = True
        result["skipped"] = "function already exists"
        result["after"] = {
            "function_name": function_name,
            "is_pure": bool(is_pure),
            "entry_guid": entry_guid_str,
            "return_guid": return_guid_str,
            "added": False,
        }
        return result

    if not compile_and_save_blueprint(bp, result):
        return result

    result["success"] = True
    result["after"] = {
        "function_name": function_name,
        "is_pure": bool(is_pure),
        "entry_guid": entry_guid_str,
        "return_guid": return_guid_str,
        "added": True,
    }
    return result


def add_function_override(
    bp_path: str,
    function_name: str,
):
    """Override a native virtual UFUNCTION inherited from the Blueprint's
    parent class hierarchy.

    Mirrors ``add_bp_function``'s shape — deterministic bridge wrapper,
    idempotent on the function name, compile+save at the end. Different
    code path: ``add_bp_function`` creates a fresh void/void function;
    ``add_function_override`` resolves the parent UFUNCTION via
    ``Blueprint->ParentClass->FindFunctionByName`` (walks the entire
    inheritance chain) and authors a graph that mirrors the parent's
    signature — typed Entry pins from inputs + Result pins from outputs /
    return value, all auto-spawned by UE's ``AddFunctionGraph<UClass>``
    helper plus our deterministic-Result-spawn pass when the parent has
    output / return params.

    Args:
        bp_path: ``/Game/...`` path to the target Blueprint.
        function_name: name of the parent-class UFUNCTION to override.
            Must be ``BlueprintImplementableEvent`` or
            ``BlueprintNativeEvent`` (the bridge checks ``FUNC_BlueprintEvent``
            and rejects non-overridable virtuals with a structured error
            matching the BP editor's "Override Function" menu visibility).
            Common drivers:

              - ``"ReceiveTestCondition"`` on
                ``UEnvQueryTest_BlueprintBase`` (returns bool, the
                M28.12 driver case)
              - ``"IsRelevancyOwnerFor"`` on ``AActor`` (returns bool,
                takes 3 ``AActor*`` params)
              - ``"K2_OnReset"`` / ``"OnInterpToggle"`` on ``AActor``
                (events, no return — these go through the ubergraph
                event-node path on parent overrides instead, so the
                bridge UFUNCTION returns a clean rejection if a non-
                function-graph BIE is targeted)

    Returns:
        Standard op-result dict. ``after`` carries
        ``{"function_name": <name>, "entry_guid": <hex>, "return_guid":
        <hex>, "added": bool}``. Idempotent: if a graph named
        ``function_name`` already exists on the BP, returns
        ``success=True`` with ``skipped="function override already
        exists"`` and populates the existing graph's Entry / Return
        GUIDs so chained authoring ops still work.

    Determinism: ``GraphGuid`` + Entry / Return ``NodeGuid`` + pin IDs
    are seeded post-create via
    ``SeedGuidFromJoined(<bp>:override_func:<fn>:<slot>)`` by the
    ``AddFunctionOverrideDeterministic`` UFUNCTION. Distinct prefix
    (``override_func`` vs fresh-function ``func``) so a name collision
    between a fresh function and an override on the same BP — illegal at
    compile time but possible mid-authoring — produces distinct seeds.

    Design.md driver: ``UEnvQueryTest_BlueprintBase::ReceiveTestCondition``
    override for the squad-director / utility-scorer EQS test set.
    Surfaced 2026-04-27 by the design.md MCP-only test against
    UE_DOW_Legacy — pre-M28.12 the only authoring surface was
    ``add_bp_function`` (fresh void/void), wrong shape for inherited
    virtuals.
    """
    result = make_result("add_function_override", bp_path, function_name)

    if not function_name:
        result["errors"].append("function_name must be non-empty")
        return result

    bp = load_bp(bp_path, result)
    if bp is None:
        return result

    ops = _ops()
    fn = unreal.Name(function_name)
    add_r = ops.add_function_override_deterministic(bp, fn)
    if not add_r.success:
        result["errors"].append(
            f"add_function_override_deterministic failed: {add_r.error_message}"
        )
        return result

    # Mirror add_bp_function's GUID-extraction pattern — UE-Python FGuid
    # doesn't expose `is_valid()`; check the hex string against the zero-GUID
    # sentinel.
    _ZERO_GUID_HEX = "00000000000000000000000000000000"
    entry_guid_str = add_r.entry_guid.to_string()
    return_guid_str = add_r.return_guid.to_string()
    if entry_guid_str == _ZERO_GUID_HEX:
        entry_guid_str = ""
    if return_guid_str == _ZERO_GUID_HEX:
        return_guid_str = ""

    result["before"] = {"override_exists": bool(add_r.skipped)}

    if add_r.skipped:
        result["success"] = True
        result["skipped"] = "function override already exists"
        result["after"] = {
            "function_name": function_name,
            "entry_guid": entry_guid_str,
            "return_guid": return_guid_str,
            "added": False,
        }
        return result

    if not compile_and_save_blueprint(bp, result):
        return result

    result["success"] = True
    result["after"] = {
        "function_name": function_name,
        "entry_guid": entry_guid_str,
        "return_guid": return_guid_str,
        "added": True,
    }
    return result


def add_component_to_scs(
    bp_path: str,
    component_class_path: str,
    component_name: str,
    parent_component_name: str = "",
):
    """Add a component to an Actor Blueprint's SimpleConstructionScript.

    Calls into the M28.2.3 ``AddComponentToSCSDeterministic`` UFUNCTION, which
    wraps ``USimpleConstructionScript::CreateNode`` and post-write overrides
    the new ``USCS_Node::VariableGuid`` via ``SeedGuidFromJoined`` so the
    .uasset bytes are byte-stable across re-runs (the engine assigns
    ``FGuid::NewGuid()`` by default, which the soak gate catches on round 2).

    Args:
        bp_path: ``/Game/...`` path to the target Actor Blueprint.
        component_class_path: ``UClass`` path for the component to add —
            ``"/Script/Engine.AudioComponent"`` /
            ``"/Script/AIModule.AIPerceptionComponent"`` /
            ``"/Game/MySquad/BP_SquadDirector.BP_SquadDirector_C"``.
            Must be a ``UActorComponent`` subclass (the bridge validates).
        component_name: desired component variable name. Used verbatim as
            the USCS_Node's InternalVariableName — the bridge rejects calls
            where the name collides with a native-inherited component
            (engine would silently append a counter suffix, which breaks
            replay idempotence) rather than accepting the rename.
        parent_component_name: SCS-node name of the parent to attach under.
            Empty / ``"None"`` / omitted → attach at SCS root. Parenting
            onto a native (inherited-CDO) component isn't supported; the
            op's scope is SCS-to-SCS parenting only.

    Returns:
        Standard op-result dict. ``after`` carries
        ``{"component_name": <name>, "component_class": <path>,
        "parent_component_name": <name-or-empty>, "added": bool}``.
        Idempotent: if a USCS node named ``component_name`` already exists
        on the BP's SCS with a matching class, returns success with
        ``skipped="component already exists on SCS"`` and does NOT touch the
        existing node. Name-with-different-class collision is an error
        rather than a silent overwrite.

    Determinism: VariableGuid is seeded post-add via
    ``SeedGuidFromJoined(bp_path + ":scs:" + component_name)`` by the
    ``AddComponentToSCSDeterministic`` UFUNCTION. Without this, the engine
    assigns ``FGuid::NewGuid()`` at ``SimpleConstructionScript.cpp:1375``
    and ``.uasset`` md5 drifts every run.
    """
    result = make_result("add_component_to_scs", bp_path, component_name)

    if not component_name:
        result["errors"].append("component_name must be non-empty")
        return result
    if not component_class_path:
        result["errors"].append("component_class_path must be non-empty")
        return result

    bp = load_bp(bp_path, result)
    if bp is None:
        return result

    # Resolve the component UClass. Mirrors _resolve_pin_type's object-ref
    # fallback — load_class covers native /Script/ paths, load_object covers
    # BP-generated /Game/ classes (which arrive as UClass when the suffix is
    # "_C", e.g. "/Game/MySquad/BP_SquadDirector.BP_SquadDirector_C").
    component_class = (
        unreal.load_class(None, component_class_path)
        or unreal.load_object(None, component_class_path)
    )
    if component_class is None or not isinstance(component_class, unreal.Class):
        result["errors"].append(
            f"component_class_path did not resolve to a UClass: {component_class_path!r} "
            f"(must be a /Script/<Module>.<Class> or /Game/<Asset>.<Asset>_C path)"
        )
        return result

    ops = _ops()
    comp_name_fn = unreal.Name(component_name)
    # Bridge treats empty / "None" FName as "attach at root".
    parent_name_fn = unreal.Name(parent_component_name or "None")

    add_r = ops.add_component_to_scs_deterministic(
        bp, component_class, comp_name_fn, parent_name_fn
    )
    if not add_r.success:
        result["errors"].append(
            f"add_component_to_scs_deterministic failed: {add_r.error_message}"
        )
        return result

    result["before"] = {"component_exists": bool(add_r.skipped)}

    if add_r.skipped:
        result["success"] = True
        result["skipped"] = "component already exists on SCS"
        result["after"] = {
            "component_name": component_name,
            "component_class": component_class_path,
            "parent_component_name": parent_component_name or "",
            "added": False,
        }
        return result

    if not compile_and_save_blueprint(bp, result):
        return result

    result["success"] = True
    result["after"] = {
        "component_name": component_name,
        "component_class": component_class_path,
        "parent_component_name": parent_component_name or "",
        "added": True,
    }
    return result


def add_bp_interface(
    bp_path: str,
    interface_class_path: str,
):
    """Attach an interface implementation to a Blueprint.

    Calls into the M28.2.4 ``AddInterfaceByPath`` UFUNCTION, which wraps
    ``FBlueprintEditorUtils::ImplementNewInterface`` and post-write seeds
    ``GraphGuid`` + Entry/Return ``NodeGuid`` + pin IDs on every generated
    override graph so the .uasset bytes are byte-stable across re-runs (the
    engine hands each new graph a ``FGuid::NewGuid()`` via
    ``UEdGraph::PostInitProperties`` and random GUIDs on the Entry/Return
    K2Nodes produced by ``CreateFunctionGraphTerminators``; without the
    seeding, M28.pre.3 soak would trip on round 2).

    Args:
        bp_path: ``/Game/...`` path to the target Blueprint.
        interface_class_path: ``UClass`` path of the interface to add.
            Native: ``"/Script/<Module>.<Interface>"`` (e.g.
            ``"/Script/Engine.Interface_PostProcessVolume"``). BP-generated:
            ``"/Game/.../BPI_OrderListener.BPI_OrderListener_C"``. Must be
            a class with ``CLASS_Interface`` set (the bridge validates).

    Returns:
        Standard op-result dict. ``after`` carries
        ``{"interface_class": <path>, "added": bool}``.
        Idempotent: if the BP already lists ``interface_class_path`` on
        ``ImplementedInterfaces[]``, returns success with
        ``skipped="interface already implemented"`` and does NOT touch the
        existing implementation (graphs, overrides, or Blueprint state).

    Notes:
        ``ImplementNewInterface`` generates an override graph only for
        interface functions that are NOT placeable as events (i.e. functions
        with output parameters — events remain wired up via the ubergraph's
        event-node path). Pure-event interfaces (like ``IInterface_AssetUserData``)
        attach cleanly with zero generated graphs; the seeding loop is a no-op.

    Determinism: each generated graph's ``GraphGuid`` + Entry/Return
    ``NodeGuid`` + pin IDs are seeded via
    ``SeedGuidFromJoined(bp_path + ":iface_graph:" + interface_class_path
    + ":" + graph_name + ":<slot>")`` by the ``AddInterfaceByPath`` UFUNCTION.
    Keyed on both BP and interface paths so two BPs implementing the same
    interface get distinct seeds and replay is byte-stable across re-runs.
    """
    result = make_result("add_bp_interface", bp_path, interface_class_path)

    if not interface_class_path:
        result["errors"].append("interface_class_path must be non-empty")
        return result

    bp = load_bp(bp_path, result)
    if bp is None:
        return result

    # Resolve the interface UClass. Mirror `add_component_to_scs`'s
    # load_class-then-load_object fallback: load_class covers native
    # /Script/ paths, load_object covers BP-generated /Game/ interface
    # classes (which arrive as UClass when the path suffix is `_C`).
    interface_class = (
        unreal.load_class(None, interface_class_path)
        or unreal.load_object(None, interface_class_path)
    )
    if interface_class is None or not isinstance(interface_class, unreal.Class):
        result["errors"].append(
            f"interface_class_path did not resolve to a UClass: {interface_class_path!r} "
            f"(must be a /Script/<Module>.<Interface> or /Game/<Asset>.<Asset>_C path)"
        )
        return result

    ops = _ops()
    add_r = ops.add_interface_by_path(bp, interface_class)
    if not add_r.success:
        result["errors"].append(
            f"add_interface_by_path failed: {add_r.error_message}"
        )
        return result

    result["before"] = {"interface_exists": bool(add_r.skipped)}

    if add_r.skipped:
        result["success"] = True
        result["skipped"] = "interface already implemented"
        result["after"] = {
            "interface_class": interface_class_path,
            "added": False,
        }
        return result

    if not compile_and_save_blueprint(bp, result):
        return result

    result["success"] = True
    result["after"] = {
        "interface_class": interface_class_path,
        "added": True,
    }
    return result


# ---------------------------------------------------------------------------
# M28.11 — function entry/result typed-parameter authoring
# ---------------------------------------------------------------------------


def _add_user_defined_pin(
    op_name: str,
    bp_path: str,
    function_name: str,
    pin_name: str,
    var_type_spec: str,
    direction_is_output: bool,
    default_value: str,
):
    """Shared scaffold for the M28.11 user-defined-pin ops.

    Each op only differs in (a) the surfaced op name in the result dict and
    (b) the bool that picks which K2Node_EditablePinBase the bridge targets.
    Validation, idempotence-skip, type resolution, compile+save are shared.
    """
    result = make_result(op_name, bp_path, f"{function_name}::{pin_name}")

    if not function_name:
        result["errors"].append("function_name must be non-empty")
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

    bp = load_bp(bp_path, result)
    if bp is None:
        return result

    pin_type = _resolve_pin_type(var_type_spec, result)
    if pin_type is None:
        return result

    ops = _ops()
    r = ops.add_function_user_defined_pin(
        bp,
        unreal.Name(function_name),
        unreal.Name(pin_name),
        pin_type,
        bool(direction_is_output),
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

    if not compile_and_save_blueprint(bp, result):
        return result

    result["success"] = True
    result["after"] = r.after_text
    return result


def add_function_input(
    bp_path: str,
    function_name: str,
    pin_name: str,
    var_type_spec: str,
    default_value: str = "",
):
    """Append an input parameter to a Blueprint function's K2Node_FunctionEntry.

    Sibling of `add_local_variable` but the pin lives on the function's Entry
    node (its UE pin direction is EGPD_Output — the entry's outputs flow INTO
    the function body, hence they appear as the function's inputs in the
    editor's Details panel).

    Args:
        bp_path: ``/Game/...`` path to the target Blueprint.
        function_name: name of the target function graph. Accepts function
            graphs and interface-override graphs. Ubergraphs are rejected
            bridge-side — events use ``add_custom_event_input``.
        pin_name: name of the new input parameter. Must be unique within the
            function's ``K2Node_FunctionEntry::UserDefinedPins`` list.
        var_type_spec: pin-type spec in the same compact string form
            ``add_bp_variable`` (M28.2.1) accepts — ``"int"`` / ``"bool"`` /
            ``"struct:/Script/CoreUObject.Vector"`` /
            ``"object:/Script/AIModule.AIController"`` / ``"array:int"`` /
            ``"map:name=>>>:int"`` / etc. Routed through
            ``_resolve_pin_type``.
        default_value: literal default value as a string in
            ``FProperty::ImportText_Direct`` format. Empty = no default.
            Applied via ``ModifyUserDefinedPinDefaultValue`` after pin
            creation.

    Returns:
        Standard op-result dict. ``before``/``after`` are bookkeeping tokens
        (``"no-user-pin"`` → ``"user-pin-added:<fn>::<pin>::out"``).
        Idempotent: if a user pin with ``pin_name`` already exists on the
        Entry node's ``UserDefinedPins`` array, returns ``success=True`` with
        ``skipped="user-defined pin already exists"`` (type compatibility is
        NOT verified on the skip path — same semantics as
        ``add_bp_variable``).

    Determinism: ``PinId`` is seeded as
    ``md5(<bp>:entry:<fn>:userpin:<pin>:out)``. Without this, replay would
    drift (engine assigns ``FGuid::NewGuid()`` in ``UEdGraphPin::CreatePin``);
    M28.pre.3 soak round 2 would catch it.

    Design.md driver: encounter-director ↔ AI.Order custom-event channel
    workaround — typed function inputs replace the member-variable handshake
    when an existing function call is the order's surface (item #1).
    """
    return _add_user_defined_pin(
        "add_function_input",
        bp_path,
        function_name,
        pin_name,
        var_type_spec,
        direction_is_output=True,
        default_value=default_value,
    )


def add_function_output(
    bp_path: str,
    function_name: str,
    pin_name: str,
    var_type_spec: str,
):
    """Append an output parameter to a Blueprint function's K2Node_FunctionResult.

    Sibling of ``add_function_input``; the pin lives on the function's Result
    node (UE pin direction EGPD_Input — the result's inputs receive FROM the
    function body, hence they appear as the function's outputs in the
    editor's Details panel).

    Result-node auto-spawn: if the target function has no ``K2Node_FunctionResult``
    (e.g. pure-flagged via ``add_bp_function(..., is_pure=True)`` — pure
    functions skip the engine's auto-Result on create), the bridge spawns
    one with deterministic ``NodeGuid`` + pin IDs seeded from
    ``<bp>:func:<fn>:result``. Authors don't need a separate "spawn Result"
    step.

    Args:
        bp_path: ``/Game/...`` path to the target Blueprint.
        function_name: name of the target function graph (function graph or
            interface-override graph).
        pin_name: name of the new output parameter. Must be unique within
            the Result node's ``UserDefinedPins`` array.
        var_type_spec: pin-type spec — see ``add_function_input``.

    Returns:
        Standard op-result dict. Idempotent on the pin name (Result-node
        ``UserDefinedPins`` array walked by name).

    Determinism: ``PinId`` is seeded as
    ``md5(<bp>:result:<fn>:userpin:<pin>:in)``.

    Note: function output pins don't carry a default value at runtime — the
    BP editor suppresses the Default Value field on Result-node pins, so
    this op signature has no ``default_value`` kwarg. The bridge would
    accept it harmlessly via ``ModifyUserDefinedPinDefaultValue`` but the
    field is never read by the BP runtime.
    """
    return _add_user_defined_pin(
        "add_function_output",
        bp_path,
        function_name,
        pin_name,
        var_type_spec,
        direction_is_output=False,
        default_value="",
    )
