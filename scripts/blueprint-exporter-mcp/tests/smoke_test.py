"""Smoke test — hit every tool against the canonical ProjectInventory_DOW.

Runs without the MCP round-trip: exercises the `*_impl` pure functions and
the `register()` wiring (to catch tool-registration surprises), using the
canonical DOW inventory in the repo as test data.

Usage:
    python -m tests.smoke_test

Exits 0 on success, non-zero on any assertion failure.
"""
from __future__ import annotations

import os
import sys
from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[3]
INV_ROOT = REPO_ROOT / "ProjectInventory_DOW"
PKG_SRC = REPO_ROOT / "scripts" / "blueprint-exporter-mcp" / "src"

sys.path.insert(0, str(PKG_SRC))
os.environ["BPX_INVENTORY_ROOT"] = str(INV_ROOT)


def _ok(label: str) -> None:
    print(f"[ok] {label}")


def _fail(label: str, detail: str) -> None:
    print(f"[FAIL] {label}: {detail}")
    sys.exit(1)


def test_paths() -> None:
    from blueprint_exporter_mcp.paths import (
        asset_path_from_sidecar,
        normalize_asset_path,
        sidecar_path,
    )

    assert (
        normalize_asset_path("/Game/Blueprints/BP_X.BP_X") == "Game/Blueprints/BP_X"
    ), "leading slash + .AssetName form"
    assert normalize_asset_path("/Game/Blueprints/BP_X") == "Game/Blueprints/BP_X"
    assert normalize_asset_path("Game/Blueprints/BP_X") == "Game/Blueprints/BP_X"
    _ok("normalize_asset_path accepts all three UE forms")

    md = sidecar_path(INV_ROOT, "/Game/Blueprints/BP_GameInstance", ".md")
    assert md.is_file(), f"expected {md} to exist"
    deep = sidecar_path(INV_ROOT, "/Game/Blueprints/BP_GameInstance", ".deep.md")
    assert deep.is_file(), f"expected {deep} to exist"
    _ok("sidecar_path resolves canonical DOW Blueprint sidecars")

    assets_root = INV_ROOT / "Assets"
    roundtrip = asset_path_from_sidecar(assets_root, deep, ".deep.md")
    assert roundtrip == "/Game/Blueprints/BP_GameInstance", roundtrip
    _ok("asset_path_from_sidecar round-trips to the UE asset path")


def test_config() -> None:
    from blueprint_exporter_mcp.config import Config, ConfigError

    cfg = Config.from_env()
    assert cfg.inventory_root == INV_ROOT.resolve()
    assert cfg.project_root is None
    _ok("Config.from_env loads BPX_INVENTORY_ROOT and leaves optional fields None")

    prev = os.environ.pop("BPX_INVENTORY_ROOT")
    try:
        try:
            Config.from_env()
            _fail("Config rejects missing BPX_INVENTORY_ROOT", "no exception raised")
        except ConfigError:
            pass
    finally:
        os.environ["BPX_INVENTORY_ROOT"] = prev
    _ok("Config.from_env raises ConfigError when inventory root is unset")


def test_list_assets() -> None:
    from blueprint_exporter_mcp.tools.retrieval import list_assets_impl

    assets_root = INV_ROOT / "Assets"

    # Unfiltered: cap at 10 so the walk stops early.
    rows = list_assets_impl(assets_root, None, None, 10)
    assert len(rows) == 10, f"expected 10 rows, got {len(rows)}"
    for row in rows:
        assert set(row.keys()) == {"path", "className", "hasDeepDump"}, row.keys()
        assert row["path"].startswith("/Game/"), row["path"]
    _ok(f"list_assets returns 10 capped rows with expected shape")

    # Class filter: StateTree — DOW has 4.
    st_rows = list_assets_impl(assets_root, "StateTree", None, 100)
    assert len(st_rows) == 4, f"expected 4 StateTree rows, got {len(st_rows)}"
    for row in st_rows:
        assert row["className"] == "StateTree", row
        assert row["hasDeepDump"] is True, f"ST should have deep dump: {row}"
    _ok(f"list_assets class_filter='StateTree' returns 4 ST assets, all with deep dumps")

    # Path prefix scoping.
    bp_rows = list_assets_impl(assets_root, None, "/Game/Blueprints", 100)
    assert len(bp_rows) > 0
    for row in bp_rows:
        assert row["path"].startswith("/Game/Blueprints"), row["path"]
    _ok(f"list_assets path_prefix='/Game/Blueprints' scopes correctly ({len(bp_rows)} rows)")


def test_get_asset_summary() -> None:
    from blueprint_exporter_mcp.tools.retrieval import get_asset_summary_impl

    text = get_asset_summary_impl(INV_ROOT, "/Game/Blueprints/BP_GameInstance")
    assert "BP_GameInstance" in text, "summary should mention asset name"
    assert "AdvancedFriendsGameInstance" in text, "summary should mention parent class"
    _ok("get_asset_summary returns canonical BP_GameInstance.md content")

    missing = get_asset_summary_impl(INV_ROOT, "/Game/Does/Not/Exist")
    assert missing.startswith("[not found]"), missing
    _ok("get_asset_summary returns [not found] for missing asset")


def test_get_asset_deep_dump() -> None:
    from blueprint_exporter_mcp.tools.retrieval import get_asset_deep_dump_impl

    text = get_asset_deep_dump_impl(INV_ROOT, "/Game/Blueprints/BP_GameInstance")
    assert len(text) > 500, f"deep dump suspiciously short: {len(text)} chars"
    _ok(f"get_asset_deep_dump returns BP_GameInstance.deep.md ({len(text)} chars)")


def test_search_deep_dumps() -> None:
    from blueprint_exporter_mcp.tools.retrieval import search_deep_dumps_impl

    assets_root = INV_ROOT / "Assets"

    # Invalid regex.
    bad = search_deep_dumps_impl(assets_root, "[unclosed", None, 5)
    assert len(bad) == 1 and "error" in bad[0], bad
    _ok("search_deep_dumps surfaces invalid-regex as data, not exception")

    # Well-known string that only StateTree .deep.md files carry.
    hits = search_deep_dumps_impl(assets_root, r"## Root Decorators|StateTreeDelayTask", "StateTree", 20)
    assert len(hits) > 0, "expected at least one StateTree match for StateTreeDelayTask"
    assert all(h["path"].startswith("/Game/") for h in hits)
    assert all(isinstance(h["lineNo"], int) and h["lineNo"] > 0 for h in hits)
    _ok(f"search_deep_dumps finds StateTreeDelayTask pattern in ST deep dumps ({len(hits)} hits)")


def test_register_with_fastmcp() -> None:
    import asyncio

    from fastmcp import FastMCP

    from blueprint_exporter_mcp.config import Config
    from blueprint_exporter_mcp.tools import gameplay_tags, live, plans, retrieval

    mcp = FastMCP(name="smoke")
    config = Config.from_env()
    retrieval.register(mcp, config)
    plans.register(mcp, config)
    live.register(mcp, config)
    gameplay_tags.register(mcp, config)
    tools = asyncio.run(mcp.list_tools())
    names = {t.name for t in tools}
    expected = {
        "list_assets",
        "get_asset_summary",
        "get_asset_deep_dump",
        "search_deep_dumps",
        "get_asset_meta",
        "get_cdo_properties",
        "get_references",
        "get_class_tree",
        "get_op_catalog",
        "validate_plan",
        "apply_plan",
        "deep_dump_asset",
        "refresh_inventory",
        "list_gameplay_tags",
    }
    missing = expected - names
    assert not missing, f"missing tools in registration: {missing} (got {names})"
    _ok(f"FastMCP registration exposes all 14 tools: {sorted(expected)}")


def test_get_asset_meta() -> None:
    from blueprint_exporter_mcp.tools.retrieval import get_asset_meta_impl

    meta = get_asset_meta_impl(INV_ROOT, "/Game/Blueprints/BP_GameInstance")
    assert meta.get("assetPath") == "/Game/Blueprints/BP_GameInstance.BP_GameInstance", meta.get("assetPath")
    assert meta.get("assetType") == "Blueprint"
    assert meta.get("blueprintSubclass") == "Blueprint"
    assert isinstance(meta.get("dependencies"), list)
    _ok("get_asset_meta returns parsed BP_GameInstance meta with expected fields")

    missing = get_asset_meta_impl(INV_ROOT, "/Game/Does/Not/Exist")
    assert missing.get("error") == "not found", missing
    _ok("get_asset_meta surfaces missing sidecar as {error: 'not found'}")


def test_get_cdo_properties() -> None:
    from blueprint_exporter_mcp.tools.retrieval import get_cdo_properties_impl

    # BP_Cha_BaseBody_WorldNpc_Male_Asian_01 has 6 CDO overrides per the M19.1 walk.
    cdo = get_cdo_properties_impl(
        INV_ROOT,
        "/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/BP_Cha_BaseBody_WorldNpc_Male_Asian_01",
    )
    assert "cdoProperties" in cdo, cdo
    props = cdo["cdoProperties"]
    assert len(props) >= 1, f"expected populated cdoProperties, got {props}"
    names = {p.get("propertyName") for p in props}
    assert "ActorLabel" in names, f"expected ActorLabel in CDO overrides: {names}"
    _ok(
        f"get_cdo_properties surfaces {len(props)} authored overrides on BP_Cha_BaseBody (names include ActorLabel)"
    )

    # BP with zero CDO overrides still returns the field, not an error.
    cdo_empty = get_cdo_properties_impl(INV_ROOT, "/Game/Blueprints/BP_GameInstance")
    assert cdo_empty.get("cdoProperties") == [], cdo_empty
    assert cdo_empty.get("assetType") == "Blueprint"
    _ok("get_cdo_properties returns empty cdoProperties + assetType for non-carrier BP")


def test_get_references() -> None:
    from blueprint_exporter_mcp.tools.retrieval import get_references_impl

    # BP_CrowdCharacter has 32 hard refs out, 0 in (per DEPENDENCY_GRAPH.md line 28).
    refs = get_references_impl(
        INV_ROOT,
        "/Game/_ThirdParty/CitySampleCrowd/Blueprints/BP_CrowdCharacter",
        "both",
    )
    assert "hardRefsOut" in refs, refs
    assert len(refs["hardRefsOut"]) == 32, f"expected 32 out, got {len(refs['hardRefsOut'])}"
    assert refs["softRefsOut"] == []
    assert refs["hardRefsIn"] == []
    kinds = {r.get("kind") for r in refs["hardRefsOut"]}
    assert {"asset", "native"} <= kinds, f"expected asset + native kinds: {kinds}"
    _ok("get_references finds BP_CrowdCharacter's 32 hard refs out with asset+native kinds")

    # Direction filter.
    out_only = get_references_impl(
        INV_ROOT,
        "/Game/_ThirdParty/CitySampleCrowd/Blueprints/BP_CrowdCharacter",
        "out",
    )
    assert "hardRefsIn" not in out_only, out_only
    assert "hardRefsOut" in out_only
    in_only = get_references_impl(
        INV_ROOT,
        "/Game/_ThirdParty/CitySampleCrowd/Blueprints/BPI_CrowdCharacter",
        "in",
    )
    assert "hardRefsOut" not in in_only, in_only
    # At least one inbound ref — the exact count tracks DOW inventory churn
    # (CI "Update Inventory_DOW from DOW build N" commits add new crowd
    # assets over time). The invariant this gate protects is "direction='in'
    # still surfaces the inbound sub-list", not a pinned count.
    assert len(in_only.get("hardRefsIn", [])) >= 1, in_only
    _ok("get_references direction='out' / 'in' scopes returned sub-lists correctly")

    # Invalid direction.
    bad = get_references_impl(INV_ROOT, "/Game/Blueprints/BP_GameInstance", "sideways")
    assert "error" in bad, bad
    _ok("get_references rejects invalid direction value")

    # Not indexed.
    missing = get_references_impl(INV_ROOT, "/Game/Does/Not/Exist", "both")
    assert missing.get("error") == "not indexed", missing
    _ok("get_references returns 'not indexed' for asset absent from graph")


def test_get_class_tree() -> None:
    from blueprint_exporter_mcp.tools.retrieval import get_class_tree_impl

    # Native parent: AIController has exactly 1 child per CLASS_TREE.md line 9.
    tree = get_class_tree_impl(INV_ROOT, "/Script/AIModule.AIController")
    assert tree.get("kind") == "native", tree
    assert tree.get("count") == 1
    assert tree["directChildren"] == [
        "/Game/_ThirdParty/GASP_example/Blueprints/AI/AIC_NPC_SmartObject"
    ]
    _ok("get_class_tree surfaces AIController's 1 direct child via native-parent section")

    # BP parent: AM_OrientationWarpingAlpha has one BP child (AM_RateWarpingAlpha).
    bp_tree = get_class_tree_impl(
        INV_ROOT,
        "/Game/_ThirdParty/GASP_example/Blueprints/AnimModifiers/AM_OrientationWarpingAlpha",
    )
    assert bp_tree.get("kind") == "blueprint", bp_tree
    assert bp_tree.get("count") >= 1
    assert any("AM_RateWarpingAlpha" in c for c in bp_tree["directChildren"])
    _ok(
        f"get_class_tree finds BP-chain children of AM_OrientationWarpingAlpha (count={bp_tree['count']})"
    )

    # Miss.
    miss = get_class_tree_impl(INV_ROOT, "/Script/DoesNotExist.Class")
    assert miss.get("error") == "not indexed", miss
    _ok("get_class_tree returns 'not indexed' for unknown class")


def test_config_auto_derives_scripts_root() -> None:
    from blueprint_exporter_mcp.config import Config

    cfg = Config.from_env()
    assert cfg.scripts_root is not None, (
        "scripts_root should auto-derive from the package location"
    )
    assert (cfg.scripts_root / "python_ops").is_dir(), cfg.scripts_root
    assert (cfg.scripts_root / "run_plan.py").is_file(), cfg.scripts_root
    _ok(f"Config.scripts_root auto-derives to {cfg.scripts_root}")


def test_get_op_catalog() -> None:
    from blueprint_exporter_mcp.config import Config
    from blueprint_exporter_mcp.tools.plans import get_op_catalog_impl

    cfg = Config.from_env()
    catalog = get_op_catalog_impl(cfg.scripts_root)
    assert "ops" in catalog, catalog
    ops = catalog["ops"]
    # python_ops/__init__.py re-exports 17 symbols; not every one is a primitive
    # op (some are helpers like format_report), but the catalog should see them all.
    assert catalog["count"] >= 15, catalog["count"]
    names = {op["name"] for op in ops}
    # Core ops shipped through M21 / M23 / M25 / M26.
    for expected in (
        "set_bp_variable_default",
        "set_component_property",
        "create_child_bp",
        "create_blueprint_class",
        "rename_asset",
        "add_statetree_enter_condition",
        "remove_statetree_enter_condition",
        "verify_state_enter_conditions",
        "implement_interface_function",
        # M28 — Flat Arena scope-bump ops.
        "add_statetree_task_to_state",
        "remove_statetree_task_from_state",
        "verify_state_tasks",
        "connect_graph_pins",
        "set_level_actor_property",
        # M28.11 typed function / custom-event parameter authoring.
        "add_function_input",
        "add_function_output",
        "add_custom_event_input",
        # M28.12 native virtual override authoring.
        "add_function_override",
        # M28.13 K2Node_MacroInstance authoring (loop unblocker).
        "add_macro_instance_node",
        # M28.14 struct-mutation node catalog (Make / Break / SetFields).
        "add_make_struct_node",
        "add_break_struct_node",
        "add_set_fields_in_struct_node",
    ):
        assert expected in names, f"op '{expected}' missing from catalog ({sorted(names)})"
    _ok(f"get_op_catalog returns {catalog['count']} ops including M28 scope-bump surface")

    # Parameter shape: set_bp_variable_default takes bp_path + var_name + value.
    sbp = next(op for op in ops if op["name"] == "set_bp_variable_default")
    param_names = [p["name"] for p in sbp["parameters"]]
    for req in ("bp_path", "var_name", "value"):
        assert req in param_names, f"set_bp_variable_default missing param {req}: {param_names}"
    assert sbp.get("docstring"), "set_bp_variable_default should have a docstring"
    _ok("get_op_catalog extracts parameter schema for set_bp_variable_default")

    # readOnly tag — colleagues can tell mutating vs observing ops apart.
    assert sbp["readOnly"] is False, sbp
    verify = next(op for op in ops if op["name"] == "verify_state_transitions")
    assert verify["readOnly"] is True, verify
    assert all(isinstance(op.get("readOnly"), bool) for op in ops), (
        "every op must carry a readOnly bool"
    )
    _ok("get_op_catalog tags each op with readOnly:bool (set_bp_variable_default=False, verify_state_transitions=True)")


def test_get_op_catalog_name_filter() -> None:
    from blueprint_exporter_mcp.config import Config
    from blueprint_exporter_mcp.tools.plans import get_op_catalog_impl

    cfg = Config.from_env()
    full = get_op_catalog_impl(cfg.scripts_root)
    assert "filter" not in full and "total" not in full, (
        "unfiltered response must not carry filter/total bookkeeping fields"
    )

    filtered = get_op_catalog_impl(cfg.scripts_root, "struct")
    names = {op["name"] for op in filtered["ops"]}
    assert filtered["filter"] == "struct"
    assert filtered["total"] == full["count"]
    assert filtered["count"] == len(filtered["ops"])
    assert filtered["count"] < full["count"], (
        "filter='struct' must narrow the catalog"
    )
    for expected in (
        "add_make_struct_node",
        "add_break_struct_node",
        "add_set_fields_in_struct_node",
        "create_user_defined_struct",
    ):
        assert expected in names, f"filter='struct' should include {expected}: {sorted(names)}"
    assert "set_bp_variable_default" not in names, (
        f"filter='struct' must exclude unrelated ops: {sorted(names)}"
    )
    _ok(f"get_op_catalog(name_filter='struct') narrows {full['count']} → {filtered['count']} ops")

    # Case insensitivity.
    upper = get_op_catalog_impl(cfg.scripts_root, "STRUCT")
    assert {op["name"] for op in upper["ops"]} == names, "filter must be case-insensitive"
    _ok("get_op_catalog name_filter is case-insensitive")

    # Empty / None / whitespace-only treated as unfiltered.
    for empty in ("", None):
        result = get_op_catalog_impl(cfg.scripts_root, empty)
        assert result["count"] == full["count"]
        assert "filter" not in result and "total" not in result
    _ok("get_op_catalog treats empty/None name_filter as unfiltered")

    # No matches → count==0, ops==[], filter+total still echoed.
    miss = get_op_catalog_impl(cfg.scripts_root, "this_will_never_match_xyz")
    assert miss["count"] == 0 and miss["ops"] == []
    assert miss["filter"] == "this_will_never_match_xyz"
    assert miss["total"] == full["count"]
    _ok("get_op_catalog with non-matching filter returns count=0 with bookkeeping intact")


def test_ue_command_builder() -> None:
    from blueprint_exporter_mcp.tools._ue_subprocess import UE_STOCK_FLAGS, build_ue_command
    from blueprint_exporter_mcp.tools.plans import _build_plan_ue_command

    # Synthetic paths — these are string-valued inputs for argv assembly;
    # they don't need to exist on disk for the test to mean anything.
    ue_cmd = Path("/synthetic/ue/engine/Binaries/Win64/UnrealEditor-Cmd.exe")
    uproject = Path("/synthetic/depot/Project/Project.uproject")

    argv = build_ue_command(
        ue_cmd, uproject, "DeepDump", ["-Asset=/Game/Foo", "-OutDir=/synthetic/tmp"]
    )
    assert argv[0] == str(ue_cmd), argv
    assert argv[1] == str(uproject), argv
    assert argv[2] == "-run=DeepDump", argv
    assert "-Asset=/Game/Foo" in argv
    assert "-OutDir=/synthetic/tmp" in argv
    for flag in UE_STOCK_FLAGS:
        assert flag in argv, f"missing flag {flag} in argv: {argv}"
    _ok("build_ue_command assembles -run=<kind> + extras + stock flags")

    # Plan-script wrapper — specialises to pythonscript + -script + -plan.
    script = Path("/synthetic/scripts/run_plan.py")
    plan = Path("/synthetic/tmp/my_plan.json")
    argv2 = _build_plan_ue_command(ue_cmd, uproject, script, plan)
    assert "-run=pythonscript" in argv2
    assert f"-script={script}" in argv2
    assert f"-plan={plan}" in argv2
    _ok("_build_plan_ue_command specialises correctly for run_plan.py scripts")


def test_plan_tools_config_errors() -> None:
    from blueprint_exporter_mcp.config import Config
    from blueprint_exporter_mcp.tools.plans import apply_plan_impl, validate_plan_impl

    cfg = Config.from_env()
    # Shape-valid plan so we fall through to the engine-missing check.
    # (Empty-operations plans are rejected at the MCP shape layer now.)
    shape_valid_plan = (
        '{"intended_outcome":"x","risk_level":"low",'
        '"operations":[{"op":"verify_state_enter_conditions",'
        '"st_path":"/Game/X","state_path":["SubTrees","[0]"]}],'
        '"expected_side_effects":[],"verification":[]}'
    )
    # No engine_root / uproject in smoke env — config-missing errors should
    # surface cleanly as data, not raise.
    res = validate_plan_impl(cfg, shape_valid_plan)
    assert "error" in res, res
    assert "BPX_ENGINE_ROOT" in res["error"], res["error"]
    _ok("validate_plan surfaces missing BPX_ENGINE_ROOT as structured error")

    # apply_plan gates on confirm — pass confirm=True to exercise the
    # engine-missing path (default confirm=False returns a preview).
    res2 = apply_plan_impl(cfg, shape_valid_plan, confirm=True)
    assert "error" in res2, res2
    assert "BPX_ENGINE_ROOT" in res2["error"], res2["error"]
    _ok("apply_plan (confirm=True) surfaces missing BPX_ENGINE_ROOT as structured error")

    # Malformed plan JSON → error, not crash.
    bad = validate_plan_impl(cfg, "{not json")
    assert "error" in bad and "JSON" in bad["error"], bad
    _ok("validate_plan rejects malformed plan JSON as structured error")


def test_plan_timeout_handler_returns_str_tails() -> None:
    """On timeout, the plan-script handler must surface partial stdout/stderr
    captured to the tempfile-backed streams (not raise, not decode-crash),
    plus the logFile pointer + hint."""
    import tempfile
    from unittest.mock import patch

    from blueprint_exporter_mcp.config import Config
    from blueprint_exporter_mcp.tools import plans
    from blueprint_exporter_mcp.tools._ue_subprocess import UeRunResult

    with tempfile.TemporaryDirectory() as tmp:
        tmp_root = Path(tmp)
        # Build just enough real-on-disk structure for
        # require_scripts_config to pass.
        engine = tmp_root / "engine"
        (engine / "Binaries" / "Win64").mkdir(parents=True)
        ue_cmd = engine / "Binaries" / "Win64" / "UnrealEditor-Cmd.exe"
        ue_cmd.write_text("")
        uproject = tmp_root / "Project.uproject"
        uproject.write_text("{}")
        scripts = tmp_root / "scripts"
        (scripts / "python_ops").mkdir(parents=True)
        (scripts / "run_plan.py").write_text("")
        (scripts / "run_plan_validator.py").write_text("")
        (scripts / "python_ops" / "__init__.py").write_text("")
        inventory = tmp_root / "inv"
        (inventory / "Assets").mkdir(parents=True)
        (inventory / "INDEX.md").write_text("")

        cfg = Config(
            inventory_root=inventory,
            project_root=None,
            engine_root=engine,
            uproject=uproject,
            scripts_root=scripts,
        )

        def _fake_timeout(command, *, timeout):
            return UeRunResult(
                returncode=None,
                stdout="captured stdout before timeout\n" * 3,
                stderr="captured stderr before timeout\n" * 3,
                timed_out=True,
            )

        plan_json = (
            '{"intended_outcome":"smoke","risk_level":"low",'
            '"operations":[{"op":"verify_state_enter_conditions",'
            '"st_path":"/Game/X","state_path":["SubTrees","[0]"]}],'
            '"expected_side_effects":[],"verification":[]}'
        )

        with patch.object(plans, "run_ue_subprocess", _fake_timeout):
            result = plans.apply_plan_impl(cfg, plan_json, confirm=True, timeout=1)

    assert "error" in result and "timed out" in result["error"], result
    assert isinstance(result.get("stdoutTail"), str), result
    assert isinstance(result.get("stderrTail"), str), result
    assert "captured stdout" in result["stdoutTail"], result["stdoutTail"]
    assert "captured stderr" in result["stderrTail"], result["stderrTail"]
    # Timeout response must point at the project's UE log — stdoutTail is
    # rarely useful past engine init, so the real signal is in logFile.
    assert "logFile" in result, result
    assert result["logFile"].endswith("Project.log"), result["logFile"]
    assert "Saved" in result["logFile"] and "Logs" in result["logFile"], result["logFile"]
    assert "hint" in result and "logFile" in result["hint"], result.get("hint")
    _ok("plan timeout handler returns str tails + logFile pointer + hint")


def test_plan_shape_rejection_skips_subprocess() -> None:
    """Regression for 2026-04-21 live-test finding: agents sometimes emit
    `{"op": "...", "args": {...}}` wrappers instead of flattened kwargs.
    Before this fix, that landed in UE after 2.5 min of cold-start and
    crashed in `_op_expected_changes`. Now the MCP server must reject
    on shape WITHOUT shelling out — subprocess.run is never called."""
    from unittest.mock import patch

    from blueprint_exporter_mcp.config import Config
    from blueprint_exporter_mcp.tools import plans

    cfg = Config.from_env()
    # scripts_root auto-derives to the real repo location — plan_shape
    # will import, so the MCP-layer pre-validation is active.
    assert cfg.scripts_root is not None, (
        "test precondition: scripts_root must auto-derive so plan_shape is importable"
    )

    # The wrapper-bug shape: kwargs nested under an "args" object.
    wrapped_plan = (
        '{"intended_outcome":"add transition",'
        '"risk_level":"low",'
        '"operations":[{"op":"add_statetree_transition",'
        '"args":{"st_path":"/Game/X",'
        '"state_path":["SubTrees","[0]"],'
        '"trigger":"OnStateCompleted",'
        '"target_state_path":["SubTrees","[1]"]}}],'
        '"expected_side_effects":[],"verification":[]}'
    )

    def _forbid_subprocess(*args, **kwargs):
        raise AssertionError(
            "subprocess.run must not be invoked when plan fails shape validation"
        )

    with patch.object(plans, "run_ue_subprocess", _forbid_subprocess):
        result = plans.validate_plan_impl(cfg, wrapped_plan)

    assert "error" in result, result
    assert "shape validation" in result["error"], result["error"]
    assert "report" in result, result
    report = result["report"]
    assert report["passed"] is False, report
    # Per-op error should call out the unknown `args` field with a hint.
    op0 = report["per_op"][0]
    assert not op0["ok"], op0
    joined = " ".join(op0["errors"])
    assert "args" in joined, joined
    assert "missing required fields" in joined, joined
    _ok("validate_plan rejects `args`-wrapper bug at the MCP layer (no subprocess.run)")

    # Same check for apply_plan — must reject identically before mutating
    # anything, even when the caller passes confirm=True. Shape rejection
    # beats the confirm gate (malformed input is always rejected).
    with patch.object(plans, "run_ue_subprocess", _forbid_subprocess):
        apply_result = plans.apply_plan_impl(cfg, wrapped_plan, confirm=True)
    assert "error" in apply_result and "shape validation" in apply_result["error"], apply_result
    _ok("apply_plan also short-circuits on shape rejection (no subprocess.run)")

    # Unknown-op plan — should also reject without shelling out.
    unknown_plan = (
        '{"intended_outcome":"bogus",'
        '"risk_level":"low",'
        '"operations":[{"op":"frobnicate","target":"/Game/X"}],'
        '"expected_side_effects":[],"verification":[]}'
    )
    with patch.object(plans, "run_ue_subprocess", _forbid_subprocess):
        unknown_result = plans.validate_plan_impl(cfg, unknown_plan)
    assert "shape validation" in unknown_result["error"], unknown_result
    op0 = unknown_result["report"]["per_op"][0]
    assert "unknown op" in " ".join(op0["errors"]), op0
    _ok("validate_plan rejects unknown op names at the MCP layer (no subprocess.run)")


def test_apply_plan_confirm_gate() -> None:
    """apply_plan requires explicit confirm=True. The default call must
    return a preview WITHOUT spawning UE — colleagues using the MCP for
    read-only exploration shouldn't mutate assets by accident."""
    from unittest.mock import patch

    from blueprint_exporter_mcp.config import Config
    from blueprint_exporter_mcp.tools import plans

    cfg = Config.from_env()
    shape_valid_plan = (
        '{"intended_outcome":"Fix Peek LOS-gate firing",'
        '"risk_level":"low",'
        '"operations":[{"op":"add_statetree_enter_condition",'
        '"st_path":"/Game/X",'
        '"state_path":["SubTrees","[0]"],'
        '"condition_bp_path":"/Game/Y"}],'
        '"expected_side_effects":[],"verification":[]}'
    )

    def _forbid_subprocess(*args, **kwargs):
        raise AssertionError(
            "subprocess.run must not be invoked on a preview call (confirm=False)"
        )

    with patch.object(plans, "run_ue_subprocess", _forbid_subprocess):
        preview = plans.apply_plan_impl(cfg, shape_valid_plan)

    assert preview.get("requiresConfirmation") is True, preview
    assert "MUTATE" in preview.get("message", ""), preview["message"]
    assert preview["plan"]["operationCount"] == 1, preview["plan"]
    assert preview["plan"]["riskLevel"] == "low", preview["plan"]
    assert preview["plan"]["operations"][0]["op"] == "add_statetree_enter_condition", preview
    # Engine-missing in smoke env — preview should surface the status
    # without raising.
    assert preview["engineConfig"]["ready"] is False, preview["engineConfig"]
    _ok("apply_plan (confirm=False) returns a preview without invoking UE")


def test_refresh_inventory_confirm_gate() -> None:
    """refresh_inventory requires explicit confirm=True. The default call
    returns a preview without shelling out."""
    from unittest.mock import patch

    from blueprint_exporter_mcp.config import Config
    from blueprint_exporter_mcp.tools import live

    cfg = Config.from_env()

    def _forbid_subprocess(*args, **kwargs):
        raise AssertionError(
            "subprocess.run must not be invoked on a preview call (confirm=False)"
        )

    with patch.object(live, "run_ue_subprocess", _forbid_subprocess):
        preview = live.refresh_inventory_impl(cfg, "/Game/CombatPrototype", deep_dump=True)

    assert preview.get("requiresConfirmation") is True, preview
    assert "OVERWRITE" in preview.get("message", ""), preview["message"]
    assert preview["filter"] == "/Game/CombatPrototype", preview
    assert preview["deepDump"] is True, preview
    assert preview["inventoryRoot"] == str(cfg.inventory_root), preview
    assert preview["engineConfig"]["ready"] is False, preview["engineConfig"]
    _ok("refresh_inventory (confirm=False) returns a preview without invoking UE")

    # Empty filter is still rejected early (before the confirm gate) — the
    # "full-project sweep is dangerous" safety check must not be bypassed
    # just because confirm is missing.
    with patch.object(live, "run_ue_subprocess", _forbid_subprocess):
        bad = live.refresh_inventory_impl(cfg, "")
    assert "error" in bad and "path_filter" in bad["error"], bad
    _ok("refresh_inventory still rejects empty path_filter before the confirm gate")


def test_partial_apply_surfaces_at_top_level() -> None:
    """When apply_plan's execution.aborted_at is set, the top-level result
    must carry partialApply, abortedAt, committedOps, totalOps, and a
    rollbackWarning. Burying it inside report.execution is too easy to
    miss, and rollback is the caller's responsibility."""
    import json as _json
    import tempfile
    from unittest.mock import patch

    from blueprint_exporter_mcp.config import Config
    from blueprint_exporter_mcp.tools import plans

    with tempfile.TemporaryDirectory() as tmp:
        tmp_root = Path(tmp)
        engine = tmp_root / "engine"
        (engine / "Binaries" / "Win64").mkdir(parents=True)
        ue_cmd = engine / "Binaries" / "Win64" / "UnrealEditor-Cmd.exe"
        ue_cmd.write_text("")
        uproject = tmp_root / "Project.uproject"
        uproject.write_text("{}")
        scripts = tmp_root / "scripts"
        (scripts / "python_ops").mkdir(parents=True)
        (scripts / "run_plan.py").write_text("")
        (scripts / "run_plan_validator.py").write_text("")
        (scripts / "python_ops" / "__init__.py").write_text("")
        inventory = tmp_root / "inv"
        (inventory / "Assets").mkdir(parents=True)
        (inventory / "INDEX.md").write_text("")

        cfg = Config(
            inventory_root=inventory,
            project_root=None,
            engine_root=engine,
            uproject=uproject,
            scripts_root=scripts,
        )

        plan_json = (
            '{"intended_outcome":"smoke","risk_level":"low",'
            '"operations":['
            '{"op":"verify_state_enter_conditions","st_path":"/Game/A","state_path":["SubTrees","[0]"]},'
            '{"op":"verify_state_enter_conditions","st_path":"/Game/B","state_path":["SubTrees","[0]"]},'
            '{"op":"verify_state_enter_conditions","st_path":"/Game/C","state_path":["SubTrees","[0]"]}'
            '],'
            '"expected_side_effects":[],"verification":[]}'
        )

        # Fake run.json: ops 0+1 succeeded, op 2 failed, aborted_at=2.
        fake_run_json = {
            "passed": False,
            "execution": {
                "passed": False,
                "aborted_at": 2,
                "executed": 2,
                "per_op": [
                    {"op_idx": 0, "op": "verify_state_enter_conditions", "error": None},
                    {"op_idx": 1, "op": "verify_state_enter_conditions", "error": None},
                    {"op_idx": 2, "op": "verify_state_enter_conditions",
                     "error": "library call raised RuntimeError: boom"},
                ],
            },
            "diff": None,
        }

        from blueprint_exporter_mcp.tools._ue_subprocess import UeRunResult

        def _fake_run(command, *, timeout):
            # Find -plan=<path> in command and write the sidecar next to it.
            plan_path = None
            for arg in command:
                if isinstance(arg, str) and arg.startswith("-plan="):
                    plan_path = arg.split("=", 1)[1]
                    break
            if plan_path is not None:
                Path(plan_path + ".run.json").write_text(_json.dumps(fake_run_json))
            return UeRunResult(returncode=1, stdout="", stderr="", timed_out=False)

        with patch.object(plans, "run_ue_subprocess", _fake_run):
            result = plans.apply_plan_impl(cfg, plan_json, confirm=True)

    assert result.get("partialApply") is True, result
    assert result.get("abortedAt") == 2, result
    assert result.get("committedOps") == 2, result
    assert result.get("totalOps") == 3, result
    assert "rollbackWarning" in result, result
    assert "2 of 3" in result["rollbackWarning"], result["rollbackWarning"]
    assert "manual" in result["rollbackWarning"], result["rollbackWarning"]
    _ok("apply_plan surfaces partial-apply + rollbackWarning at the top level")


def test_doctor_coherence_heuristic() -> None:
    from blueprint_exporter_mcp.config import Config
    from blueprint_exporter_mcp.doctor import _check_project_coherence

    def _cfg(inv: str, up: str | None) -> Config:
        return Config(
            inventory_root=Path(inv),
            project_root=None,
            engine_root=None,
            uproject=Path(up) if up is not None else None,
            scripts_root=None,
        )

    # Synthetic path fragments that contain the substrings the heuristic
    # looks for — the test is about pattern-matching, not real files.

    # Aligned: Legacy inventory + Legacy uproject.
    check = _check_project_coherence(
        _cfg(
            "/synthetic/devops/_dow_legacy_inventory",
            "/synthetic/depot/UE_DOW_Legacy/UE_DOW.uproject",
        )
    )
    assert check.ok, check.detail
    assert "ue_dow_legacy" in check.detail
    _ok("doctor coherence: aligned Legacy paths pass")

    # Aligned: DOW main inventory + DOW main uproject.
    check = _check_project_coherence(
        _cfg(
            "/synthetic/repo/blueprint-exporter/ProjectInventory_DOW",
            "/synthetic/depot/UE_DOW/DOW.uproject",
        )
    )
    assert check.ok, check.detail
    assert "ue_dow" in check.detail
    _ok("doctor coherence: aligned DOW-main paths pass")

    # Mismatched: DOW main inventory + Legacy uproject — the bug the user spotted.
    check = _check_project_coherence(
        _cfg(
            "/synthetic/repo/blueprint-exporter/ProjectInventory_DOW",
            "/synthetic/depot/UE_DOW_Legacy/UE_DOW.uproject",
        )
    )
    assert not check.ok, check.detail
    assert "ue_dow" in check.detail and "ue_dow_legacy" in check.detail
    _ok("doctor coherence: DOW-main inventory + Legacy uproject FAILS loudly")

    # BPX_UPROJECT unset: coherence skipped (check passes).
    check = _check_project_coherence(
        _cfg("/synthetic/devops/_dow_legacy_inventory", None)
    )
    assert check.ok and "skipped" in check.detail
    _ok("doctor coherence: BPX_UPROJECT unset -> skipped, not failed")


def test_live_tools_config_errors() -> None:
    from blueprint_exporter_mcp.config import Config
    from blueprint_exporter_mcp.tools.live import (
        deep_dump_asset_impl,
        refresh_inventory_impl,
    )

    cfg = Config.from_env()

    # Missing engine config.
    res = deep_dump_asset_impl(cfg, "/Game/Blueprints/BP_GameInstance")
    assert "error" in res and "BPX_ENGINE_ROOT" in res["error"], res
    _ok("deep_dump_asset surfaces missing BPX_ENGINE_ROOT as structured error")

    # refresh_inventory gates on confirm — pass confirm=True to exercise
    # the engine-missing path (default confirm=False returns a preview).
    res2 = refresh_inventory_impl(cfg, "/Game/CombatPrototype", confirm=True)
    assert "error" in res2 and "BPX_ENGINE_ROOT" in res2["error"], res2
    _ok("refresh_inventory (confirm=True) surfaces missing BPX_ENGINE_ROOT as structured error")


def test_live_command_shape() -> None:
    from blueprint_exporter_mcp.tools._ue_subprocess import (
        UE_STOCK_FLAGS,
        build_ue_command,
    )

    ue_cmd = Path("/synthetic/ue/engine/Binaries/Win64/UnrealEditor-Cmd.exe")
    uproject = Path("/synthetic/depot/Project/Project.uproject")

    # DeepDump commandlet.
    argv = build_ue_command(
        ue_cmd,
        uproject,
        "DeepDump",
        [
            "-Asset=/Game/Blueprints/BP_GameInstance",
            "-OutDir=C:/tmp/out",
        ],
    )
    assert "-run=DeepDump" in argv
    assert "-Asset=/Game/Blueprints/BP_GameInstance" in argv
    assert "-OutDir=C:/tmp/out" in argv
    for flag in UE_STOCK_FLAGS:
        assert flag in argv
    _ok("build_ue_command produces correct DeepDump argv")

    # ProjectInventory commandlet.
    argv2 = build_ue_command(
        ue_cmd,
        uproject,
        "ProjectInventory",
        [
            "-OutDir=D:/ProjectInventory_DOW",
            "-Filter=/Game/CombatPrototype",
            "-DeepDump",
        ],
    )
    assert "-run=ProjectInventory" in argv2
    assert "-Filter=/Game/CombatPrototype" in argv2
    assert "-DeepDump" in argv2
    _ok("build_ue_command produces correct ProjectInventory argv (with -DeepDump)")


def test_list_gameplay_tags() -> None:
    """M28.6.1 — exercise the zero-UE-process list_gameplay_tags walker.

    Two scenarios:

      1. Empty starter ini (BugHunt fixture committed alongside this test) —
         confirms the parser sees the source file and reports 0 tags + 0
         redirects. This is the round-1 baseline state for the M28.pre.5
         verify_tag_author parity gate; if the parser counted phantom
         tags from the settings header, the gate would false-fail.

      2. DOW project, when present on disk — confirms the parser handles
         the dominant real-world content shape (32 tags + 3 redirects in
         /D:/Work/UE_DOW/game/Config/DefaultGameplayTags.ini per the
         M28.6.0 research). Skipped gracefully when DOW isn't checked
         out so this test stays portable across machines.
    """
    from blueprint_exporter_mcp.config import Config
    from blueprint_exporter_mcp.tools.gameplay_tags import (
        list_gameplay_tags_impl,
    )

    # Scenario 1 — BugHunt starter fixture (empty Config/DefaultGameplayTags.ini).
    bughunt_root = REPO_ROOT / "BugHunt" / "TestProject"
    cfg = Config.from_env()
    res = list_gameplay_tags_impl(cfg, str(bughunt_root))
    assert "error" not in res, res
    assert res["project_root"] == str(bughunt_root.resolve()), res["project_root"]
    sources = res["sources"]
    assert len(sources) == 1, f"expected 1 source for BugHunt fixture, got {sources}"
    assert sources[0]["name"] == "DefaultGameplayTags.ini"
    assert sources[0]["tag_count"] == 0
    assert sources[0]["redirect_count"] == 0
    assert res["tags"] == []
    assert res["redirects"] == []
    _ok("list_gameplay_tags: BugHunt empty-ini baseline returns 0 tags / 0 redirects, 1 source")

    # Scenario 2 — DOW project, opportunistic.
    dow_root = Path("D:/Work/UE_DOW/game")
    if (dow_root / "Config" / "DefaultGameplayTags.ini").is_file():
        dow_res = list_gameplay_tags_impl(cfg, str(dow_root))
        assert "error" not in dow_res, dow_res
        # Tag count is content-driven and may shift over time as the
        # project evolves; just assert it's reading something non-empty
        # plus the well-known redirects from the M28.6.0 research record.
        assert len(dow_res["tags"]) > 0, "DOW should have authored gameplay tags"
        assert len(dow_res["redirects"]) >= 1, "DOW has ≥3 known redirects"
        # Sanity: at least one tag from the DOW Foley.* / MotionMatching.*
        # family should be present (visible in the M28.6.0 research dump).
        names = {t["name"] for t in dow_res["tags"]}
        assert any(n.startswith(("Foley.", "MotionMatching.")) for n in names), (
            f"expected Foley.* or MotionMatching.* in DOW tags; got first 5: "
            f"{sorted(names)[:5]}"
        )
        _ok(
            f"list_gameplay_tags: DOW project parses {len(dow_res['tags'])} tags + "
            f"{len(dow_res['redirects'])} redirects across {len(dow_res['sources'])} sources"
        )
    else:
        _ok("list_gameplay_tags: DOW project not present, scenario 2 skipped (portable)")

    # Scenario 3 — error path: unresolvable project root.
    err_res = list_gameplay_tags_impl(cfg, "/synthetic/path/does/not/exist")
    assert "error" in err_res
    assert err_res["tags"] == [] and err_res["sources"] == []
    _ok("list_gameplay_tags: surfaces missing project_root as structured error, not exception")


def test_list_gameplay_tags_per_domain_no_plus_prefix() -> None:
    """M28.6.2 regression — parse Config/Tags/<X>.ini with plain `GameplayTagList=`.

    UE's editor writes per-domain tag files (e.g. Config/Tags/AI.ini) without
    the `+` array-append prefix, because each file deserializes to its own
    UGameplayTagsList instance and the array isn't being accumulated across
    config layers. The pre-fix M28.6.1 regex required `^\\+` and silently
    returned `tag_count: 0` for these files even when content was present.

    Synthesizes both shapes side-by-side so the test exercises the mixed
    fleet path the parser sees in practice (DefaultGameplayTags.ini with `+`
    plus per-domain Config/Tags/*.ini without). Restricted variant included
    so the no-prefix support extends across both list types, not just the
    common one.
    """
    import tempfile

    from blueprint_exporter_mcp.config import Config
    from blueprint_exporter_mcp.tools.gameplay_tags import (
        list_gameplay_tags_impl,
    )

    with tempfile.TemporaryDirectory() as tmp:
        proj = Path(tmp)
        (proj / "Config").mkdir()
        (proj / "Config" / "Tags").mkdir()

        # Per-domain file — NO `+` prefix on the array entries (engine-written
        # convention, the M28.6.2 repro shape from UE_DOW_Legacy/Config/Tags/AI.ini).
        (proj / "Config" / "Tags" / "AI.ini").write_text(
            "[/Script/GameplayTags.GameplayTagsList]\n"
            'GameplayTagList=(Tag="AI.Archetype.Flanker",DevComment="Flanker: ignores LoS")\n'
            'GameplayTagList=(Tag="AI.Archetype.Marksman",DevComment="Marksman: holds cover")\n'
            'GameplayTagList=(Tag="AI.Archetype.Rusher",DevComment="Rusher: closes distance")\n'
            'GameplayTagList=(Tag="AI.Archetype.Suppresser",DevComment="Suppresser: high fire rate")\n',
            encoding="utf-8",
        )
        # Sibling per-domain file with the restricted variant — also no `+`.
        (proj / "Config" / "Tags" / "Restricted.ini").write_text(
            "[/Script/GameplayTags.GameplayTagsList]\n"
            'RestrictedGameplayTagList=(Tag="Locked.Root",DevComment="Restricted root")\n',
            encoding="utf-8",
        )
        # Default file — WITH `+` prefix (UGameplayTagsSettings array-accumulation form).
        (proj / "Config" / "DefaultGameplayTags.ini").write_text(
            ";METADATA=(Diff=true, UseCommands=true)\n"
            "[/Script/GameplayTags.GameplayTagsSettings]\n"
            "ImportTagsFromConfig=True\n"
            '+GameplayTagList=(Tag="Default.From.Plus",DevComment="Default-form, with +")\n'
            '+GameplayTagRedirects=(OldTagName="Old.Path",NewTagName="New.Path")\n',
            encoding="utf-8",
        )

        cfg = Config.from_env()
        res = list_gameplay_tags_impl(cfg, str(proj))
        assert "error" not in res, res

        sources_by_name = {s["name"]: s for s in res["sources"]}
        assert "AI.ini" in sources_by_name, f"AI.ini source missing: {sources_by_name}"
        assert sources_by_name["AI.ini"]["tag_count"] == 4, (
            f"per-domain Config/Tags/AI.ini parser regression: expected 4 tags "
            f"in no-`+`-prefix file, got {sources_by_name['AI.ini']['tag_count']}. "
            f"This is the M28.6.2 bug — the regex required `^\\+` but UE writes "
            f"per-domain files without the array-append prefix."
        )
        assert sources_by_name["Restricted.ini"]["tag_count"] == 1, (
            f"restricted variant of per-domain no-`+` shape failed: "
            f"{sources_by_name['Restricted.ini']}"
        )
        assert sources_by_name["DefaultGameplayTags.ini"]["tag_count"] == 1, (
            f"with-`+` form regressed: {sources_by_name['DefaultGameplayTags.ini']}"
        )
        assert sources_by_name["DefaultGameplayTags.ini"]["redirect_count"] == 1

        names = {t["name"] for t in res["tags"]}
        assert "AI.Archetype.Flanker" in names
        assert "AI.Archetype.Suppresser" in names
        assert "Locked.Root" in names
        assert "Default.From.Plus" in names

        # Confirm the restricted flag survives the no-`+` parse path.
        locked = next(t for t in res["tags"] if t["name"] == "Locked.Root")
        assert locked["restricted"] is True, locked
        flanker = next(t for t in res["tags"] if t["name"] == "AI.Archetype.Flanker")
        assert flanker["restricted"] is False, flanker
        assert flanker["comment"] == "Flanker: ignores LoS"

    _ok(
        "list_gameplay_tags: parses per-domain Config/Tags/<X>.ini without "
        "`+` array-append prefix (M28.6.2 regression)"
    )


def main() -> None:
    test_paths()
    test_config()
    test_config_auto_derives_scripts_root()
    test_list_assets()
    test_get_asset_summary()
    test_get_asset_deep_dump()
    test_search_deep_dumps()
    test_get_asset_meta()
    test_get_cdo_properties()
    test_get_references()
    test_get_class_tree()
    test_get_op_catalog()
    test_ue_command_builder()
    test_plan_tools_config_errors()
    test_plan_timeout_handler_returns_str_tails()
    test_plan_shape_rejection_skips_subprocess()
    test_apply_plan_confirm_gate()
    test_refresh_inventory_confirm_gate()
    test_partial_apply_surfaces_at_top_level()
    test_doctor_coherence_heuristic()
    test_live_tools_config_errors()
    test_live_command_shape()
    test_list_gameplay_tags()
    test_list_gameplay_tags_per_domain_no_plus_prefix()
    test_register_with_fastmcp()
    print("\nAll smoke tests passed.")


if __name__ == "__main__":
    main()
