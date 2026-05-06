"""UUserDefinedStruct authoring ops via the M28.4.3+ reflection bridge.

Creates and edits `UUserDefinedStruct` assets — the most complex slice
of the M28.4 non-BP asset factories (curves → data assets → user-defined
structs, complexity ramp per the M28.4.0 research outcome).

M28.4.3 ships four ops:

  - create_user_defined_struct   — wraps FStructureEditorUtils::CreateUserDefinedStruct
                                    + seeds the engine-generated Struct->Guid
                                    and the auto-bool's VarGuid for determinism.
                                    Idempotent on (uds_path).
  - add_uds_member               — appends a new member with a deterministic
                                    VarGuid + optional default value.
                                    Idempotent on (uds_path, member_name).
  - remove_uds_member            — removes a member by friendly name. Refuses
                                    to empty the struct (engine invariant
                                    bAllowToMakeEmpty=false). Idempotent on
                                    (uds_path, member_name).
  - set_uds_member_default       — writes VarDesc.DefaultValue via
                                    ChangeVariableDefaultValue so the
                                    DefaultInstance memory + serialized
                                    string stay in sync. Idempotent on
                                    value-equality.

Design.md driver: item #3 (confidence-decaying perception — thicken
`S_TargetInfo` UDS with lifetime / last-seen-time / exposure-score fields
so the perception system can reason about stale contacts without the
per-tick line-trace cost).

Determinism: UUserDefinedStruct has two `FGuid::NewGuid()` call sites —
`Struct->Guid` (StructureEditorUtils.cpp:53) and per-member `VarGuid`
(StructureEditorUtils.cpp:303). Both are closed via the
`SeedGuidFromJoined` recipe on the C++ side — bridge UFUNCTIONs overwrite
the random values post-create and route the rename pass so `VarName`
regenerates from the seeded `VarGuid`. M28.pre.3 soak exercises this
invariant.

Type specs reuse `blueprint_structural._resolve_pin_type` (first
established as a cross-module helper in M28.3.4 `add_local_variable`).
The spec catalog is the same terse string form as `add_bp_variable`:
  - basic:   "int" / "real" / "bool" / "string" / "name" / "text" / "byte"
  - struct:  "struct:/Script/CoreUObject.Vector"
  - object:  "object:/Script/AIModule.AIController"
  - class:   "class:/Script/AIModule.AIController"
  - array:   "array:<inner>"
  - set:     "set:<inner>"
  - map:     "map:<key>=>>>:<value>"

Out of scope for M28.4.3 (deferred per the research outcome):

  - UDS member re-ordering (`MoveVariable`). No design.md driver; expose
    only on request.
  - UDS member type change (`ChangeVariableType`). Risky — invalidates
    default values and cascades through every Blueprint that consumes
    the struct. Require explicit user sign-off if a driver surfaces.
  - Removing the auto-bool member on creation. The engine's
    bAllowToMakeEmpty=false guard blocks `create → remove_auto_bool` as
    a one-shot; the auto-bool stays in the fresh struct with friendly
    name `BpxAutoBool` until plan authors add a real member and then
    remove it in a chained plan.
"""

import unreal

from ._common import make_result
from .blueprint_structural import _resolve_pin_type


def _ops():
    return unreal.BpxReflectionOps


def _load_uds(uds_path: str, result: dict):
    """Load a UUserDefinedStruct. On failure appends error + returns None.

    Mirrors `data_assets._load_data_asset` shape: /Game/ path gate +
    type check + structured rejection for missing / wrong-class paths.
    """
    if not isinstance(uds_path, str) or not uds_path.startswith("/Game/"):
        result["errors"].append(
            f"uds_path must start with /Game/: {uds_path!r}"
        )
        return None
    asset = unreal.load_asset(uds_path)
    if asset is None:
        result["errors"].append(f"load_asset returned None for {uds_path!r}")
        return None
    if not isinstance(asset, unreal.UserDefinedStruct):
        result["errors"].append(
            f"asset at {uds_path!r} is {type(asset).__name__}, expected UserDefinedStruct"
        )
        return None
    return asset


def _normalize_scalar_value(value, result: dict):
    """Coerce a Python scalar to the ExportText string a VarDesc.DefaultValue
    expects. Mirrors `data_assets._normalize_scalar_value` /
    `eqs._normalize_scalar_value` so plan JSON carries plain ints / floats /
    bools without string-quoting them. Strings pass through verbatim for
    composite literals like ``"(X=1.0,Y=2.0,Z=0.0)"``.
    """
    if isinstance(value, bool):
        return ("true" if value else "false"), True
    if isinstance(value, (int, float)):
        return repr(value), True
    if isinstance(value, str):
        return value, True
    result["errors"].append(
        f"value must be a string / int / float / bool; got {type(value).__name__}"
    )
    return None, False


def create_user_defined_struct(uds_path: str):
    """Create a new `UUserDefinedStruct` at a ``/Game/...`` package path.

    First op of M28.4.3, fifth op of the M28.4 non-BP asset-factory
    catalog. Creates the struct plus an auto-bool member (engine-required
    — a UDS must have at least one variable, and `CreateUserDefinedStruct`
    auto-adds a default `bool` on line 60 of
    `Editor/UnrealEd/Private/Kismet2/StructureEditorUtils.cpp`).

    The auto-bool is renamed to ``BpxAutoBool`` with a deterministic
    VarGuid so every run produces a byte-identical struct. Plan authors
    typically chain `add_uds_member` ops to grow the struct, then
    optionally `remove_uds_member` to drop `BpxAutoBool` once at least
    one real member exists (the engine's ``bAllowToMakeEmpty=false``
    invariant refuses to remove the last variable).

    Args:
        uds_path: ``/Game/...`` path where the struct should live. Short
            name is derived from the last segment — the asset's FName
            will match the path tail so re-exports / inventory sidecars
            resolve cleanly.

    Returns:
        Standard op-result dict. ``after`` carries
        ``{uds_path, spawned: bool}``.

        Idempotent on ``uds_path``: if a UUserDefinedStruct already
        exists at the target path, returns ``success=True`` with
        ``skipped="uds already exists"`` and ``spawned=False``. Wrong-
        class collision at the same path returns a structured error —
        silent stacking would be a plan-level mistake.

    Determinism: the bridge UFUNCTION overwrites both
    ``Struct->Guid`` (`SeedGuidFromJoined(uds_path + ":uds")`) and the
    auto-bool's ``VarGuid``
    (`SeedGuidFromJoined(uds_path + ":uds_var:BpxAutoBool")`), then
    reroutes through `RenameVariable` so the auto-bool's ``VarName``
    regenerates from the seeded VarGuid. M28.pre.3 soak exercises this
    invariant.
    """
    result = make_result("create_user_defined_struct", uds_path, "")

    if not isinstance(uds_path, str) or not uds_path.startswith("/Game/"):
        result["errors"].append(
            f"uds_path must start with /Game/: {uds_path!r}"
        )
        return result

    ops = _ops()
    r = ops.create_user_defined_struct_deterministic(uds_path)
    if not r.success:
        result["errors"].append(
            f"create_user_defined_struct_deterministic bridge call failed: "
            f"{r.error_message}"
        )
        return result

    result["before"] = r.before_text

    if r.skipped:
        result["success"] = True
        result["skipped"] = "uds already exists"
        result["after"] = {"uds_path": uds_path, "spawned": False}
        return result

    # Resolve the freshly-created in-memory UObject back via load_asset.
    uds = unreal.load_asset(uds_path)
    if uds is None:
        result["errors"].append(
            f"load_asset returned None for {uds_path!r} after create "
            "(unexpected — bridge reported success)"
        )
        return result

    # UUserDefinedStruct is not a Blueprint; compile_and_save_package skips
    # the BP compile step and goes straight to UPackage::SavePackage. The
    # post-create RenameVariable has already compiled the struct's
    # FProperty chain via OnStructureChanged(RenamedVariable).
    if not ops.compile_and_save_package(uds):
        result["errors"].append(
            "compile_and_save_package returned False — save refused "
            "(check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = {"uds_path": uds_path, "spawned": True}
    return result


def add_uds_member(
    uds_path: str,
    member_name: str,
    var_type_spec: str,
    default_value: str = "",
):
    """Append a new member variable to an existing `UUserDefinedStruct`.

    Sixth op of the M28.4 catalog. Wraps
    ``FStructureEditorUtils::AddVariable`` via the M28.4.3 bridge UFUNCTION
    which closes the engine's ``VarGuid = FGuid::NewGuid()`` determinism
    trap by post-seeding + routing through ``RenameVariable`` so
    ``VarName`` regenerates from the seeded ``VarGuid`` + the requested
    friendly name.

    Args:
        uds_path: ``/Game/...`` path to an existing UUserDefinedStruct.
        member_name: friendly name of the new member (as it appears in
            the struct editor's Details panel). Case-sensitive; plan
            authors should use the canonical casing. Idempotency is
            keyed on this name.
        var_type_spec: type spec string. See
            ``blueprint_structural._resolve_pin_type`` for the full
            catalog. Common forms:

              - ``"int"`` / ``"bool"`` / ``"real"`` / ``"string"``
              - ``"struct:/Script/CoreUObject.Vector"``
              - ``"object:/Script/AIModule.AIController"``
              - ``"array:real"`` /
                ``"array:struct:/Script/Game.S_TargetInfo"``

        default_value: literal default value as a string in the same
            format ``FStructVariableDescription::DefaultValue`` accepts
            — ``"true"`` for bool, ``"42"`` for int,
            ``"(X=1.0,Y=2.0,Z=0.0)"`` for vectors. Empty string = engine
            default (zero-init). On non-empty input, the bridge writes
            the default via ``ChangeVariableDefaultValue`` in the same
            call so VarDesc + DefaultInstance stay in sync.

    Returns:
        Standard op-result dict. ``after`` carries
        ``{uds_path, member_name, var_type_spec, default_value}``.

        Idempotent on ``member_name``: if a member with that friendly
        name already exists, returns ``success=True`` with
        ``skipped="member already exists"``. Type / default-value
        compatibility is NOT verified on the skip path — callers can
        inspect the existing member via the standard
        ``unreal.UserDefinedStruct`` reflection if type drift matters.
    """
    result = make_result("add_uds_member", uds_path, member_name)

    if not isinstance(member_name, str) or not member_name:
        result["errors"].append("member_name must be a non-empty string")
        return result
    if not isinstance(var_type_spec, str) or not var_type_spec:
        result["errors"].append("var_type_spec must be a non-empty string")
        return result
    if not isinstance(default_value, str):
        result["errors"].append(
            f"default_value must be a string; got {type(default_value).__name__}"
        )
        return result

    uds = _load_uds(uds_path, result)
    if uds is None:
        return result

    # Resolve pin type spec → unreal.EdGraphPinType. Reuses the
    # M28.2.1 structural helper (first cross-module helper reuse
    # established by M28.3.4 add_local_variable).
    pin_type = _resolve_pin_type(var_type_spec, result)
    if pin_type is None:
        return result

    ops = _ops()
    r = ops.add_user_defined_struct_member(
        uds, unreal.Name(member_name), pin_type, default_value
    )
    if not r.success:
        result["errors"].append(
            f"add_user_defined_struct_member bridge call failed: "
            f"{r.error_message}"
        )
        return result

    result["before"] = r.before_text

    if r.skipped:
        result["success"] = True
        result["skipped"] = "member already exists"
        result["after"] = {
            "uds_path": uds_path,
            "member_name": member_name,
            "var_type_spec": var_type_spec,
            "default_value": default_value,
        }
        return result

    if not ops.compile_and_save_package(uds):
        result["errors"].append(
            "compile_and_save_package returned False — save refused "
            "(check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = {
        "uds_path": uds_path,
        "member_name": member_name,
        "var_type_spec": var_type_spec,
        "default_value": default_value,
    }
    return result


def remove_uds_member(uds_path: str, member_name: str):
    """Remove a member variable from a `UUserDefinedStruct` by friendly name.

    Seventh op of the M28.4 catalog. Wraps
    ``FStructureEditorUtils::RemoveVariable`` after resolving the friendly
    name → VarGuid on the target struct.

    Args:
        uds_path: ``/Game/...`` path to an existing UUserDefinedStruct.
        member_name: friendly name of the member to remove. Case-
            sensitive, same spelling as in the struct editor Details
            panel.

    Returns:
        Standard op-result dict. ``after`` carries
        ``{uds_path, member_name, removed: bool}``.

        Idempotent on ``member_name``: if no member with that friendly
        name exists, returns ``success=True`` with
        ``skipped="member already absent"`` and ``removed=False``.
        Supports destructive-op soak round 2 replay.

        Refuses to empty the struct: if the target is the last member,
        returns a structured error matching the engine's
        ``bAllowToMakeEmpty=false`` invariant. Plan authors should add
        the replacement member BEFORE removing the last existing one.
    """
    result = make_result("remove_uds_member", uds_path, member_name)

    if not isinstance(member_name, str) or not member_name:
        result["errors"].append("member_name must be a non-empty string")
        return result

    uds = _load_uds(uds_path, result)
    if uds is None:
        return result

    ops = _ops()
    r = ops.remove_user_defined_struct_member(uds, unreal.Name(member_name))
    if not r.success:
        result["errors"].append(
            f"remove_user_defined_struct_member bridge call failed: "
            f"{r.error_message}"
        )
        return result

    result["before"] = r.before_text

    if r.skipped:
        result["success"] = True
        result["skipped"] = "member already absent"
        result["after"] = {
            "uds_path": uds_path,
            "member_name": member_name,
            "removed": False,
        }
        return result

    if not ops.compile_and_save_package(uds):
        result["errors"].append(
            "compile_and_save_package returned False — save refused "
            "(check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = {
        "uds_path": uds_path,
        "member_name": member_name,
        "removed": True,
    }
    return result


def set_uds_member_default(uds_path: str, member_name: str, value):
    """Set a member variable's default value on a `UUserDefinedStruct`.

    Eighth op of the M28.4 catalog. Wraps
    ``FStructureEditorUtils::ChangeVariableDefaultValue`` so
    ``VarDesc.DefaultValue`` (the authoritative string) and
    ``DefaultInstance`` memory stay in sync — a direct write to
    ``DefaultInstance`` via ``SetPropertyValue`` would leave the UDS in
    a torn state where the serialized string says X but memory says Y
    (M28.4.0 research Open Question #1).

    Args:
        uds_path: ``/Game/...`` path to an existing UUserDefinedStruct.
        member_name: friendly name of the target member.
        value: the new default value. Strings pass through verbatim for
            composite literals (``"(X=1.0,Y=2.0,Z=0.0)"`` /
            ``"/Game/DT_Foo.DT_Foo"``); ints / floats / bools are
            coerced to ExportText form (``"true"`` / ``"false"`` /
            decimal repr) so plan JSON can carry native scalars.

    Returns:
        Standard op-result dict. ``before`` / ``after`` carry the
        ExportText form of the old and new default values.

        Idempotent: compares existing VarDesc.DefaultValue against the
        normalized value string up-front; match → ``skipped="value already match"``.
        Supports soak-style round-2 replay without churning the asset.

        Missing member returns a structured error (not a silent no-op) —
        typos in the member name should surface at plan-execution time,
        not get hidden behind an idempotent skip.
    """
    result = make_result(
        "set_uds_member_default", uds_path, f"{member_name}={value!r}"
    )

    if not isinstance(member_name, str) or not member_name:
        result["errors"].append("member_name must be a non-empty string")
        return result

    norm_value, ok = _normalize_scalar_value(value, result)
    if not ok:
        return result

    uds = _load_uds(uds_path, result)
    if uds is None:
        return result

    ops = _ops()
    r = ops.set_user_defined_struct_member_default(
        uds, unreal.Name(member_name), norm_value
    )
    if not r.success:
        result["errors"].append(
            f"set_user_defined_struct_member_default bridge call failed: "
            f"{r.error_message}"
        )
        return result

    result["before"] = r.before_text

    if r.skipped:
        result["success"] = True
        result["skipped"] = "value already match"
        result["after"] = r.after_text
        return result

    if not ops.compile_and_save_package(uds):
        result["errors"].append(
            "compile_and_save_package returned False — save refused "
            "(check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = r.after_text
    return result
