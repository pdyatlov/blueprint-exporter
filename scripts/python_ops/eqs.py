"""EnvQuery (EQS) authoring ops via the M28.5.1+ reflection bridge.

Writes EQS content into existing `UEnvQuery` assets with deterministic
`NewObject` names. Every op here is idempotent on its identifier key so plan
replay is safe.

M28.5.1 + M28.5.2 + M28.5.3 ship five ops of the planned M28.5 catalog:

  - add_eqs_option             — append a UEnvQueryOption with a fresh
                                   generator of the supplied concrete class.
  - add_eqs_test               — append a UEnvQueryTest subclass to an
                                   existing option's Tests[] array with
                                   TestOrder assigned.
  - remove_eqs_test            — remove a test by index and reseat
                                   TestOrder on the tail so the 0..N-1
                                   invariant holds.
  - set_eqs_generator_property — scalar UPROPERTY setter on
                                   Options[i].Generator, reusing the
                                   existing SetPropertyValue reflection
                                   bridge via a nested path.
  - set_eqs_test_property      — scalar UPROPERTY setter on
                                   Options[i].Tests[j], same pattern.

Design.md drivers: the utility-scorer target picker (item #2) and squad
director cover scans (item #6) both rely on EQS to resolve candidate
positions / actors. M15 landed the Tier 2 read-side so authored content is
inspectable; M28.5 closes the loop with a write-side so authoring stays in
the plan layer rather than requiring manual editor clicks.

Determinism: EQS classes have zero `FGuid::NewGuid()` usage (grep-confirmed
M28.5.0); the only drift source is `NewObject`'s counter-suffixed default
name generation. The add_* ops pass an explicit `FName` on each `NewObject`
the bridge UFUNCTION makes. The set_*_property ops do not allocate new
UObjects — they only mutate existing FProperty memory via
`FProperty::ImportText_Direct`, which is deterministic by construction.
"""

import unreal

from ._common import make_result


def _ops():
    return unreal.BpxReflectionOps


def _load_eqs(eqs_path: str, result: dict):
    """Load a UEnvQuery asset. On failure appends error + returns None.

    Mirrors `blueprint_graph_nodes._load_bp` but for EnvQuery. Canonical
    rejection path for ``/Script/`` targets (EQS must live under ``/Game/``
    because only project content is editable) and wrong-type assets.
    """
    if not eqs_path.startswith("/Game/"):
        result["errors"].append(f"eqs_path must start with /Game/: {eqs_path!r}")
        return None
    asset = unreal.load_asset(eqs_path)
    if asset is None:
        result["errors"].append(f"load_asset returned None for {eqs_path!r}")
        return None
    if not isinstance(asset, unreal.EnvQuery):
        result["errors"].append(
            f"asset at {eqs_path!r} is {type(asset).__name__}, expected EnvQuery"
        )
        return None
    return asset


def _resolve_eqs_class(
    class_path: str,
    param_name: str,
    sample_path: str,
    result: dict,
):
    """Resolve a UClass by ``/Script/<Module>.<Class>`` path.

    Generic resolver for M28.5.x ops — used by `add_eqs_option` (generator
    class) and `add_eqs_test` (test class). Mirrors `blueprint_graph_nodes.
    _resolve_target_class` / `blueprint_structural.add_bp_interface`:
    `load_class` for native paths, `load_object` fallback for edge cases.
    Abstract-class and wrong-subclass rejection happens on the C++ side —
    the bridge UFUNCTION already produces a structured error for both, so
    this helper only validates the "does this path resolve to a UClass"
    question. ``param_name`` / ``sample_path`` flow into the error text.
    """
    if not class_path:
        result["errors"].append(f"{param_name} must be non-empty")
        return None
    cls = (
        unreal.load_class(None, class_path)
        or unreal.load_object(None, class_path)
    )
    if cls is None or not isinstance(cls, unreal.Class):
        result["errors"].append(
            f"{param_name} did not resolve to a UClass: {class_path!r} "
            f"(must be /Script/<Module>.<Class>; try {sample_path})"
        )
        return None
    return cls


# ---------------------------------------------------------------------------
# M28.5.1 — add_eqs_option
# ---------------------------------------------------------------------------


def add_eqs_option(
    eqs_path: str,
    generator_class_path: str,
):
    """Append a new option to a UEnvQuery with a fresh generator.

    First op of the M28.5 EQS write-side catalog. Creates a `UEnvQueryOption`
    owned by the target query and a fresh `UEnvQueryGenerator` of the
    supplied concrete class owned by the option, then appends the option to
    ``UEnvQuery::Options``. Atomic: option + generator land together or not
    at all.

    Args:
        eqs_path: ``/Game/...`` path to the target `UEnvQuery`.
        generator_class_path: UClass path of the concrete generator subclass
            to instantiate. Must be a non-abstract subclass of
            ``/Script/AIModule.EnvQueryGenerator``. Typical values:

              - ``/Script/AIModule.EnvQueryGenerator_ActorsOfClass``
              - ``/Script/AIModule.EnvQueryGenerator_SimpleGrid``
              - ``/Script/AIModule.EnvQueryGenerator_Donut``
              - ``/Script/AIModule.EnvQueryGenerator_OnCircle``
              - ``/Script/AIModule.EnvQueryGenerator_PathingGrid``

    Returns:
        Standard op-result dict. ``after`` carries
        ``{option_index: int, generator_class_path: str, spawned: bool}``.

        Idempotent on ``(eqs_path, generator_class_path)``: if any existing
        option already carries a generator of the requested class, returns
        ``success=True`` with ``skipped="option with this generator already
        exists"`` and ``option_index`` pointing at the matching slot.

    Determinism: the bridge UFUNCTION passes explicit `FName`s
    (``BpxEqsOption_<idx>`` / ``BpxEqsGen_<idx>_<ClassShortName>``) on each
    `NewObject` so two replays against the same baseline produce
    byte-identical ``.uasset``. M28.pre.3 soak exercises this invariant.
    """
    result = make_result("add_eqs_option", eqs_path, generator_class_path)

    eqs = _load_eqs(eqs_path, result)
    if eqs is None:
        return result

    gen_class = _resolve_eqs_class(
        generator_class_path,
        "generator_class_path",
        "/Script/AIModule.EnvQueryGenerator_ActorsOfClass",
        result,
    )
    if gen_class is None:
        return result

    ops = _ops()
    r = ops.add_env_query_option(eqs, gen_class)
    if not r.success:
        result["errors"].append(
            f"add_env_query_option bridge call failed: {r.error_message}"
        )
        return result

    # AfterText is the new (or existing-matched) option index as a decimal
    # string — r.after_text is already safely bounded and numeric.
    try:
        option_index = int(r.after_text)
    except (TypeError, ValueError):
        result["errors"].append(
            f"add_env_query_option returned non-numeric after_text: {r.after_text!r}"
        )
        return result

    result["before"] = r.before_text

    if r.skipped:
        result["success"] = True
        result["skipped"] = "option with this generator already exists"
        result["after"] = {
            "option_index": option_index,
            "generator_class_path": generator_class_path,
            "spawned": False,
        }
        return result

    # UEnvQuery is not a Blueprint; compile_and_save_package skips the BP
    # compile step and goes straight to UPackage::SavePackage.
    if not ops.compile_and_save_package(eqs):
        result["errors"].append(
            "compile_and_save_package returned False — save refused "
            "(check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = {
        "option_index": option_index,
        "generator_class_path": generator_class_path,
        "spawned": True,
    }
    return result


# ---------------------------------------------------------------------------
# M28.5.2 — add_eqs_test / remove_eqs_test
# ---------------------------------------------------------------------------


def add_eqs_test(
    eqs_path: str,
    option_index: int,
    test_class_path: str,
):
    """Append a UEnvQueryTest subclass to an option's Tests[] array.

    Second op of the M28.5 EQS write-side catalog; builds on M28.5.1's
    option-level shape by targeting ``UEnvQuery::Options[option_index].Tests``.

    Args:
        eqs_path: ``/Game/...`` path to the target `UEnvQuery`.
        option_index: Zero-based index into ``UEnvQuery::Options``. Fails
            fast with a structured error if out of range.
        test_class_path: UClass path of the concrete test subclass.
            Must be a non-abstract subclass of
            ``/Script/AIModule.EnvQueryTest``. Typical values:

              - ``/Script/AIModule.EnvQueryTest_Random``
              - ``/Script/AIModule.EnvQueryTest_Distance``
              - ``/Script/AIModule.EnvQueryTest_Trace``
              - ``/Script/AIModule.EnvQueryTest_Dot``
              - ``/Script/AIModule.EnvQueryTest_Pathfinding``

    Returns:
        Standard op-result dict. ``after`` carries
        ``{option_index, test_index, test_class_path, spawned}``.

        Idempotent on ``(eqs_path, option_index, test_class_path)``: if any
        existing test on the target option is an exact-class match,
        returns ``success=True`` with ``skipped="test with this class
        already exists on option"`` and ``test_index`` pointing at the
        matching slot.

    Determinism: the bridge UFUNCTION passes an explicit `FName`
    (``BpxEqsTest_<option_index>_<pre_count>_<TestClassShortName>``) on the
    `NewObject` call. ``TestOrder`` is assigned to the post-append index
    so the ``0..N-1`` runtime invariant holds — `EnvQueryManager.cpp:874`
    only repairs zero at runtime.
    """
    result = make_result(
        "add_eqs_test",
        eqs_path,
        f"option[{option_index}] += {test_class_path}",
    )

    eqs = _load_eqs(eqs_path, result)
    if eqs is None:
        return result

    if not isinstance(option_index, int) or option_index < 0:
        result["errors"].append(
            f"option_index must be a non-negative int, got {option_index!r}"
        )
        return result

    test_class = _resolve_eqs_class(
        test_class_path,
        "test_class_path",
        "/Script/AIModule.EnvQueryTest_Random",
        result,
    )
    if test_class is None:
        return result

    ops = _ops()
    r = ops.add_env_query_test(eqs, option_index, test_class)
    if not r.success:
        result["errors"].append(
            f"add_env_query_test bridge call failed: {r.error_message}"
        )
        return result

    try:
        test_index = int(r.after_text)
    except (TypeError, ValueError):
        result["errors"].append(
            f"add_env_query_test returned non-numeric after_text: {r.after_text!r}"
        )
        return result

    result["before"] = r.before_text

    if r.skipped:
        result["success"] = True
        result["skipped"] = "test with this class already exists on option"
        result["after"] = {
            "option_index": option_index,
            "test_index": test_index,
            "test_class_path": test_class_path,
            "spawned": False,
        }
        return result

    if not ops.compile_and_save_package(eqs):
        result["errors"].append(
            "compile_and_save_package returned False — save refused "
            "(check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = {
        "option_index": option_index,
        "test_index": test_index,
        "test_class_path": test_class_path,
        "spawned": True,
    }
    return result


def remove_eqs_test(
    eqs_path: str,
    option_index: int,
    test_index: int,
):
    """Remove a test from an option's Tests[] array by index.

    Symmetric counterpart of `add_eqs_test`. Removes
    ``UEnvQuery::Options[option_index].Tests[test_index]`` and reseats
    ``TestOrder`` on every subsequent test so the ``0..N-1`` invariant
    holds — `EnvQueryManager.cpp:874` only repairs zero at runtime, so
    non-zero stale values would silently break evaluation order.

    Args:
        eqs_path: ``/Game/...`` path to the target `UEnvQuery`.
        option_index: Zero-based index into ``UEnvQuery::Options``.
        test_index: Zero-based index into the target option's ``Tests``
            array.

    Returns:
        Standard op-result dict. ``after`` carries
        ``{option_index, removed_test_index}``.

        Idempotent on ``(eqs_path, option_index, test_index)``: an
        out-of-range ``test_index`` (e.g. a re-apply after a prior run
        already removed this slot) returns ``success=True`` with
        ``skipped="test already removed (out-of-range index)"``. This
        supports soak-style replay where round 1 mutates and round 2
        would otherwise hit the now-empty slot. ``option_index`` still
        has a strict bounds check — option identity is stable across
        test removals.
    """
    result = make_result(
        "remove_eqs_test",
        eqs_path,
        f"option[{option_index}].tests[{test_index}]",
    )

    eqs = _load_eqs(eqs_path, result)
    if eqs is None:
        return result

    if not isinstance(option_index, int) or option_index < 0:
        result["errors"].append(
            f"option_index must be a non-negative int, got {option_index!r}"
        )
        return result
    if not isinstance(test_index, int) or test_index < 0:
        result["errors"].append(
            f"test_index must be a non-negative int, got {test_index!r}"
        )
        return result

    ops = _ops()
    r = ops.remove_env_query_test(eqs, option_index, test_index)
    if not r.success:
        result["errors"].append(
            f"remove_env_query_test bridge call failed: {r.error_message}"
        )
        return result

    result["before"] = r.before_text

    if r.skipped:
        # Idempotent replay path — bridge already checked the option
        # exists; out-of-range test_index means a prior apply removed
        # this target. Don't re-save — nothing changed.
        result["success"] = True
        result["skipped"] = "test already removed (out-of-range index)"
        result["after"] = {
            "option_index": option_index,
            "removed_test_index": test_index,
        }
        return result

    if not ops.compile_and_save_package(eqs):
        result["errors"].append(
            "compile_and_save_package returned False — save refused "
            "(check UE log)"
        )
        return result

    result["success"] = True
    result["after"] = {
        "option_index": option_index,
        "removed_test_index": test_index,
    }
    return result


# ---------------------------------------------------------------------------
# M28.5.3 — set_eqs_generator_property / set_eqs_test_property
# ---------------------------------------------------------------------------


def _normalize_scalar_value(value, result: dict):
    """Coerce a Python scalar to the ExportText string SetPropertyValue expects.

    Mirrors ``level.set_level_actor_property``'s normalization so plan JSON
    can carry plain ints / floats / bools without string-quoting them. On
    unsupported types appends a structured error and returns ``(None, False)``.
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


def _set_eqs_subobject_property(
    *,
    op_name: str,
    eqs_path: str,
    nav_prefix: list,
    field_descriptor: str,
    property_path,
    value,
):
    """Shared driver for set_eqs_generator_property / set_eqs_test_property.

    Takes ``nav_prefix`` — the pre-validated navigation steps that reach the
    target subobject from the UEnvQuery root (e.g. ``["Options", "[0]",
    "Generator"]`` or ``["Options", "[0]", "Tests", "[0]"]``) — and appends
    the caller-supplied ``property_path`` (the leaf property + any nested
    struct fields like ``["SearchRadius", "DefaultValue"]``). Reuses the
    existing ``SetPropertyValue`` reflection bridge; idempotent via a
    ``GetPropertyValue`` pre-check that short-circuits when before == value.

    Save path: ``compile_and_save_package(eqs)``. UEnvQuery is a UDataAsset
    subclass (not a Blueprint) so the compile step is a no-op; the real
    work is ``UPackage::SavePackage``.
    """
    result = make_result(
        op_name,
        eqs_path,
        f"{'/'.join(nav_prefix)}.{field_descriptor}={value!r}",
    )

    if not isinstance(property_path, list) or not property_path:
        result["errors"].append(
            "property_path must be a non-empty list of path steps"
        )
        return result
    for step in property_path:
        if not isinstance(step, str) or not step:
            result["errors"].append(
                f"property_path steps must be non-empty strings; got {step!r}"
            )
            return result

    norm_value, ok = _normalize_scalar_value(value, result)
    if not ok:
        return result

    eqs = _load_eqs(eqs_path, result)
    if eqs is None:
        return result

    full_path = list(nav_prefix) + list(property_path)

    ops = _ops()

    before = ops.get_property_value(eqs, full_path)
    if not before.success:
        result["errors"].append(
            f"get_property_value failed at {full_path!r}: {before.error_message}"
        )
        return result
    result["before"] = before.after_text

    if before.after_text == norm_value:
        result["success"] = True
        result["skipped"] = f"value already {norm_value!r}"
        result["after"] = before.after_text
        return result

    r = ops.set_property_value(eqs, full_path, norm_value)
    if not r.success:
        result["errors"].append(
            f"set_property_value failed at {full_path!r}: {r.error_message}"
        )
        return result

    if not ops.compile_and_save_package(eqs):
        result["errors"].append(
            "compile_and_save_package returned False — save refused "
            "(check UE log)"
        )
        return result

    after = ops.get_property_value(eqs, full_path)
    result["after"] = after.after_text if after.success else norm_value
    result["success"] = True
    return result


def set_eqs_generator_property(
    eqs_path: str,
    option_index: int,
    property_path: list,
    value,
):
    """Mutate a UPROPERTY on ``UEnvQuery::Options[option_index].Generator``.

    Fourth op of the M28.5 EQS write-side catalog. Wraps the existing
    ``UBpxReflectionOps::SetPropertyValue`` reflection bridge (shipped in
    M23.1) with an EQS-specific path prefix — no new UFUNCTION. Covers any
    editable UPROPERTY the generator exposes, from concrete-class fields
    like ``EnvQueryGenerator_ActorsOfClass::SearchRadius`` (via
    ``["SearchRadius", "DefaultValue"]`` to reach the
    ``FAIDataProviderFloatValue::DefaultValue`` leaf) down to base-class
    fields like ``UEnvQueryGenerator::OptionName``
    (via ``["OptionName"]``).

    Args:
        eqs_path: ``/Game/...`` path to the target `UEnvQuery`.
        option_index: Zero-based index into ``UEnvQuery::Options``. Fails
            fast with a structured error if out of range.
        property_path: Leaf-relative navigation steps the reflection bridge
            understands. A single leaf name
            (``["OptionName"]``) addresses a plain UPROPERTY on the
            generator; nested paths (``["SearchRadius", "DefaultValue"]``)
            descend into FStructProperty fields such as
            ``FAIDataProviderFloatValue``. Array elements use ``"[N]"``
            notation — see ``BpxReflectionOps::ResolvePath``.
        value: The property's new value. Strings are forwarded verbatim;
            ints / floats / bools are coerced to their ExportText form
            (``"true"`` / ``"false"`` / decimal repr) so plan JSON can
            carry native scalars. See
            ``FProperty::ExportTextItem_Direct`` for the canonical string
            format per type.

    Returns:
        Standard op-result dict. ``before`` / ``after`` carry the
        ExportText form of the old and new values. ``skipped`` is set
        when the property already equals ``value`` (no save).

    Idempotent: ``SetPropertyValue`` short-circuits when ``before == value``
    as a string, so replaying the same plan is a no-op on rounds 2+.

    Out of scope (deliberate):
      - ``FAIDataProviderFloatValue::DataBinding`` swaps. The provider is
        a UObject inside the struct that needs
        ``PostEditChangeProperty`` revalidation per ``EnvQueryNode.cpp``.
        Use the default-value path (``["<Prop>", "DefaultValue"]``) for
        scalar tuning; swap DataBinding from the editor when needed.
        Revisit in a follow-up if a concrete driver materialises.
    """
    if not isinstance(option_index, int) or option_index < 0:
        r = make_result(
            "set_eqs_generator_property",
            eqs_path,
            f"option[{option_index}].Generator",
        )
        r["errors"].append(
            f"option_index must be a non-negative int, got {option_index!r}"
        )
        return r

    return _set_eqs_subobject_property(
        op_name="set_eqs_generator_property",
        eqs_path=eqs_path,
        nav_prefix=["Options", f"[{option_index}]", "Generator"],
        field_descriptor=".".join(str(p) for p in (property_path or [])),
        property_path=property_path,
        value=value,
    )


def set_eqs_test_property(
    eqs_path: str,
    option_index: int,
    test_index: int,
    property_path: list,
    value,
):
    """Mutate a UPROPERTY on ``UEnvQuery::Options[i].Tests[j]``.

    Fifth op of the M28.5 EQS write-side catalog; sibling of
    `set_eqs_generator_property` targeting an option's Tests[] array
    instead of its Generator slot. Reuses the same ``SetPropertyValue``
    reflection bridge — no new UFUNCTION.

    Args:
        eqs_path: ``/Game/...`` path to the target `UEnvQuery`.
        option_index: Zero-based index into ``UEnvQuery::Options``.
        test_index: Zero-based index into the target option's ``Tests``
            array.
        property_path: Leaf-relative navigation steps. Typical entries:

              - ``["TestComment"]`` — FString, base
                ``UEnvQueryTest::TestComment``.
              - ``["TestPurpose"]`` — enum; ExportText form
                (``"Filter"`` / ``"Score"`` / ``"FilterAndScore"``).
              - ``["ScoringFactor", "DefaultValue"]`` — nested struct
                into ``FAIDataProviderFloatValue``.

        value: See `set_eqs_generator_property`. Strings forwarded
            verbatim; ints / floats / bools coerced to ExportText.

    Returns:
        Standard op-result dict. ``before`` / ``after`` + idempotent
        skip semantics match `set_eqs_generator_property`.

    Deliberate non-features mirror `set_eqs_generator_property`:
    DataBinding swaps are out of scope; set the struct's
    ``DefaultValue`` leaf instead.
    """
    if not isinstance(option_index, int) or option_index < 0:
        r = make_result(
            "set_eqs_test_property",
            eqs_path,
            f"option[{option_index}].tests[{test_index}]",
        )
        r["errors"].append(
            f"option_index must be a non-negative int, got {option_index!r}"
        )
        return r
    if not isinstance(test_index, int) or test_index < 0:
        r = make_result(
            "set_eqs_test_property",
            eqs_path,
            f"option[{option_index}].tests[{test_index}]",
        )
        r["errors"].append(
            f"test_index must be a non-negative int, got {test_index!r}"
        )
        return r

    return _set_eqs_subobject_property(
        op_name="set_eqs_test_property",
        eqs_path=eqs_path,
        nav_prefix=["Options", f"[{option_index}]", "Tests", f"[{test_index}]"],
        field_descriptor=".".join(str(p) for p in (property_path or [])),
        property_path=property_path,
        value=value,
    )
