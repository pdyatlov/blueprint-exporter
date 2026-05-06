"""Plan-pipeline tools — shell out to the M24 validator / executor scripts.

M25.1.2 ships three tools:
    get_op_catalog()                — AST-introspect `python_ops/` and
                                       return each op's signature + kwargs.
                                       Zero UE process.
    validate_plan(plan_json_str)    — runs `run_plan_validator.py` under
                                       UnrealEditor-Cmd.exe and returns
                                       the `<plan>.validation.json` dict.
    apply_plan(plan_json_str)       — runs `run_plan.py` (validate →
                                       execute → mechanical-diff →
                                       verification) and returns the
                                       `<plan>.run.json` dict.

Tool bodies land as module-level `*_impl` pure functions; `register()`
wires them to a FastMCP instance as `@mcp.tool` closures that bind
Config. Subprocess invocation is isolated in `_build_ue_command` and
`_run_plan_script` so smoke can verify the command shape without
launching UE.
"""
from __future__ import annotations

import ast
import json
import subprocess
import tempfile
from pathlib import Path
from types import ModuleType
from typing import Any

from fastmcp import FastMCP

from ..config import Config
from ._bridge_client import BridgeUnavailable, try_bridge_call
from ._ue_subprocess import (
    SubprocessConfigError,
    build_ue_command,
    project_log_path,
    require_scripts_config,
    run_ue_subprocess,
)


# Raised 300 -> 600 after a second false timeout on UE_DOW_Legacy (2026-04-21).
# Legacy's commandlet cold-start + Python init lands right at ~3 min on a
# warm DDC; 300 leaves no headroom for the actual Python work.
DEFAULT_VALIDATE_TIMEOUT = 600
DEFAULT_APPLY_TIMEOUT = 900


# -----------------------------------------------------------------------------
# MCP-side plan-shape pre-validation
# -----------------------------------------------------------------------------
#
# Catches malformed plan JSON (wrong top-level keys, `args` wrapper, unknown
# ops, missing required kwargs) in <100ms so we don't pay 2.5 min of UE
# cold-start to fail. Imports `python_ops.plan_shape` from the configured
# scripts_root dynamically — the module is pure Python with no `import
# unreal`, designed for exactly this use case. See
# `scripts/python_ops/plan_shape.py`.


_PLAN_SHAPE_CACHE: dict[str, ModuleType | None] = {}


def _load_plan_shape(config: Config) -> ModuleType | None:
    """Load `plan_shape.py` from the configured scripts_root as a
    standalone module.

    Bypasses `python_ops/__init__.py` (which imports `unreal` and
    therefore can't load outside UE). Cached per scripts_root path.

    Returns None if scripts_root is unset, the file is missing, or
    execution fails. When None, the MCP layer skips pre-validation and
    falls through to UE-side validation.
    """
    if config.scripts_root is None:
        return None
    sr = str(config.scripts_root)
    if sr in _PLAN_SHAPE_CACHE:
        return _PLAN_SHAPE_CACHE[sr]

    shape_py = config.scripts_root / "python_ops" / "plan_shape.py"
    if not shape_py.is_file():
        _PLAN_SHAPE_CACHE[sr] = None
        return None

    import importlib.util

    spec = importlib.util.spec_from_file_location(
        "blueprint_exporter_mcp._vendored_plan_shape", shape_py
    )
    if spec is None or spec.loader is None:
        _PLAN_SHAPE_CACHE[sr] = None
        return None
    module = importlib.util.module_from_spec(spec)
    try:
        spec.loader.exec_module(module)
    except Exception:
        _PLAN_SHAPE_CACHE[sr] = None
        return None

    _PLAN_SHAPE_CACHE[sr] = module
    return module


# Ops that read state without modifying it. Tagged in `get_op_catalog`
# output so colleagues can tell at a glance whether calling an op via
# apply_plan would mutate assets. Keep in sync with the `verify_*` family
# in `scripts/python_ops/statetree.py`.
READ_ONLY_OPS = frozenset(
    {
        "verify_state_enter_conditions",
        "verify_state_transitions",
    }
)


# -----------------------------------------------------------------------------
# get_op_catalog
# -----------------------------------------------------------------------------


def _param_from_ast(
    arg: ast.arg, default: ast.expr | None
) -> dict[str, Any]:
    entry: dict[str, Any] = {"name": arg.arg}
    if arg.annotation is not None:
        entry["annotation"] = ast.unparse(arg.annotation)
    if default is not None:
        entry["required"] = False
        entry["default"] = ast.unparse(default)
    else:
        entry["required"] = True
    return entry


def _extract_function_signature(
    func: ast.FunctionDef | ast.AsyncFunctionDef,
) -> dict[str, Any]:
    args = func.args
    # Map trailing defaults onto positional args.
    pos_args = args.args
    pos_defaults: list[ast.expr | None] = [None] * (
        len(pos_args) - len(args.defaults)
    ) + list(args.defaults)

    parameters = [
        _param_from_ast(a, d) for a, d in zip(pos_args, pos_defaults)
    ]
    for a, d in zip(args.kwonlyargs, args.kw_defaults):
        parameters.append(_param_from_ast(a, d))

    return {
        "name": func.name,
        "docstring": ast.get_docstring(func),
        "parameters": parameters,
    }


def get_op_catalog_impl(
    scripts_root: Path | None,
    name_filter: str | None = None,
) -> dict[str, Any]:
    """AST-parse `python_ops/__init__.py` + referenced submodules.

    No imports are executed, so the parser does not need the `unreal`
    module available.

    `name_filter`, when truthy, is matched as a case-insensitive
    substring against each op's name; non-matching ops are skipped
    before their submodule is parsed. The unfiltered total is echoed
    back as `total` so callers can tell how many ops are hidden.
    """
    if scripts_root is None:
        return {
            "error": (
                "scripts_root not configured. Set BPX_SCRIPTS_ROOT to the "
                "directory containing python_ops/ (defaults auto-derive from "
                "the package location)."
            )
        }
    ops_pkg = scripts_root / "python_ops"
    init_py = ops_pkg / "__init__.py"
    if not init_py.is_file():
        return {
            "error": f"python_ops/__init__.py not found at {init_py}",
            "scriptsRoot": str(scripts_root),
        }

    try:
        init_tree = ast.parse(init_py.read_text(encoding="utf-8"))
    except (OSError, SyntaxError) as exc:
        return {"error": f"parse failure on __init__.py: {exc}"}

    # Collect op_name -> submodule_name from re-export `ImportFrom`s.
    op_to_module: dict[str, str] = {}
    for node in init_tree.body:
        if not isinstance(node, ast.ImportFrom):
            continue
        if node.level != 1 or node.module is None:
            continue
        for alias in node.names:
            op_to_module[alias.asname or alias.name] = node.module

    needle = (name_filter or "").lower()

    ops: list[dict[str, Any]] = []
    for op_name, module_name in sorted(op_to_module.items()):
        if needle and needle not in op_name.lower():
            continue
        mod_file = ops_pkg / f"{module_name}.py"
        if not mod_file.is_file():
            ops.append(
                {
                    "name": op_name,
                    "module": module_name,
                    "error": "submodule not found",
                }
            )
            continue
        try:
            mod_tree = ast.parse(mod_file.read_text(encoding="utf-8"))
        except (OSError, SyntaxError) as exc:
            ops.append(
                {
                    "name": op_name,
                    "module": module_name,
                    "error": f"parse failure: {exc}",
                }
            )
            continue
        found = None
        for node in mod_tree.body:
            if isinstance(node, (ast.FunctionDef, ast.AsyncFunctionDef)) and node.name == op_name:
                found = node
                break
        if found is None:
            ops.append(
                {
                    "name": op_name,
                    "module": module_name,
                    "error": "function not found in submodule",
                }
            )
            continue
        entry = _extract_function_signature(found)
        entry["module"] = module_name
        entry["readOnly"] = op_name in READ_ONLY_OPS
        ops.append(entry)

    result: dict[str, Any] = {
        "scriptsRoot": str(scripts_root),
        "count": len(ops),
        "ops": ops,
    }
    if needle:
        result["filter"] = name_filter
        result["total"] = len(op_to_module)
    return result


# -----------------------------------------------------------------------------
# Plan-pipeline shell-outs
# -----------------------------------------------------------------------------


def _build_plan_ue_command(
    ue_cmd: Path, uproject: Path, script: Path, plan_file: Path
) -> list[str]:
    """Thin wrapper that fixes run_kind=pythonscript + the two pythonscript args."""
    return build_ue_command(
        ue_cmd,
        uproject,
        "pythonscript",
        [f"-script={script}", f"-plan={plan_file}"],
    )


def _parse_plan_json(plan_json_str: str) -> tuple[dict | None, str | None]:
    try:
        plan = json.loads(plan_json_str)
    except (TypeError, json.JSONDecodeError) as exc:
        return None, f"plan JSON did not parse: {exc}"
    if not isinstance(plan, dict):
        return None, f"plan must be a JSON object, got {type(plan).__name__}"
    return plan, None


def _summarize_plan(plan: dict) -> dict[str, Any]:
    """Compact preview of what the plan will do. Safe even if some
    optional fields are missing — the shape validator already ran."""
    ops = plan.get("operations", [])
    op_rows = []
    for i, op in enumerate(ops):
        if not isinstance(op, dict):
            op_rows.append({"idx": i, "op": f"<invalid: {type(op).__name__}>"})
            continue
        name = op.get("op", "<missing>")
        targets = {
            k: v
            for k, v in op.items()
            if k != "op"
            and k != "_comment"
            and k != "idempotency_key"
            and isinstance(v, (str, int, float, bool, list))
        }
        op_rows.append({"idx": i, "op": name, "kwargs": targets})
    return {
        "intendedOutcome": plan.get("intended_outcome"),
        "riskLevel": plan.get("risk_level"),
        "operationCount": len(ops),
        "operations": op_rows,
        "expectedSideEffects": plan.get("expected_side_effects", []),
        "verification": plan.get("verification", []),
    }


def _try_bridge_for_plan(
    config: Config,
    bridge_method: str,
    plan_json_str: str,
    recv_timeout: int,
    re_export: bool = True,
) -> dict[str, Any] | None:
    """Attempt to route a plan request through the M27 editor bridge.

    Returns the bridge response annotated with `transport: "bridge"` on
    success (including bridge-delivered error objects — those are
    authoritative, not transport failures). Returns None if the bridge is
    unreachable so the caller can fall through to the subprocess path.
    Requires `config.scripts_root` to be set; without it the bridge's
    Python-side can't locate `bridge_entry.py`.

    M27.3 — passes `inventoryRoot` so the bridge's apply_plan handler can
    scope a re-export of touched assets after a successful run. Set
    `re_export=False` to opt out (debugging / benchmarking); validate_plan
    callers pass False since there's nothing to re-export.
    """
    if config.scripts_root is None:
        return None

    params = {
        "planJson": plan_json_str,
        "scriptsRoot": str(config.scripts_root),
        "inventoryRoot": str(config.inventory_root),
    }
    if not re_export:
        params["noReexport"] = True

    try:
        resp = try_bridge_call(
            bridge_method,
            params,
            recv_timeout=float(recv_timeout),
        )
    except BridgeUnavailable:
        return None

    # Unwrap the JSON-RPC envelope. The bridge wraps results as
    # {"result": {"report": <...>, "transport": "bridge"}, ...} on success,
    # or {"error": {"code", "message"}} on a server-side failure the bridge
    # actually handled (e.g. Python unavailable). Both shapes are
    # authoritative — do not fall back to subprocess in either case.
    if "result" in resp and isinstance(resp["result"], dict):
        result = dict(resp["result"])
        # Ensure transport marker is present even if the bridge forgot.
        result.setdefault("transport", "bridge")
        return result
    if "error" in resp and isinstance(resp["error"], dict):
        err = resp["error"]
        return {
            "error": err.get("message", "bridge returned an unspecified error"),
            "bridgeErrorCode": err.get("code"),
            "transport": "bridge",
        }
    return {
        "error": "bridge returned a malformed JSON-RPC response",
        "rawResponse": resp,
        "transport": "bridge",
    }


def _run_plan_script(
    config: Config,
    script_name: str,
    sidecar_suffix: str,
    plan_json_str: str,
    timeout: int,
    confirm: bool,
    confirm_message: str,
    bridge_method: str | None = None,
    bridge_re_export: bool = True,
) -> dict[str, Any]:
    plan, err = _parse_plan_json(plan_json_str)
    if err is not None:
        return {"error": err}

    # MCP-side shape pre-validation — catches malformed plans before we pay
    # 2.5 min of UE cold-start. Skipped only if the shape module cannot be
    # loaded (degraded scripts_root config).
    shape_module = _load_plan_shape(config)
    if shape_module is not None:
        shape_report = shape_module.validate_shape(plan)
        if not shape_report["passed"]:
            return {
                "error": (
                    "plan failed MCP-side shape validation. Fix the errors "
                    "in `report` and resubmit — UE was not invoked. See "
                    "`plans/README.md` for the plan schema and call "
                    "`get_op_catalog` for the authoritative op kwargs."
                ),
                "report": shape_report,
            }

    # Confirmation gate — tools that spawn UE AND mutate files require the
    # caller to explicitly pass confirm=True. The first call returns a
    # preview so the agent can surface "here's what I'd do" to the human
    # before anything runs.
    if not confirm:
        preview: dict[str, Any] = {
            "requiresConfirmation": True,
            "message": confirm_message,
            "plan": _summarize_plan(plan),
            "nextStep": (
                "Show this preview to the human. If they approve, "
                "re-call with confirm=true. Nothing has been launched "
                "or written — UE was not invoked."
            ),
        }
        try:
            ue_cmd, uproject, script = require_scripts_config(
                config, script_name
            )
        except SubprocessConfigError as exc:
            preview["engineConfig"] = {
                "ready": False,
                "detail": str(exc),
            }
        else:
            preview["engineConfig"] = {"ready": True}
            preview["plannedCommand"] = _build_plan_ue_command(
                ue_cmd, uproject, script, Path("<plan-json-tempfile>")
            )
        return preview

    # M27.2 — try the persistent editor bridge first. On connect-refused /
    # handshake-timeout we fall through to the subprocess path below; on any
    # actual bridge response (success or server-side error) we return it
    # directly because the editor already handled the request and retrying
    # via subprocess would duplicate state mutations for apply_plan.
    if bridge_method is not None:
        bridge_result = _try_bridge_for_plan(
            config, bridge_method, plan_json_str, timeout,
            re_export=bridge_re_export,
        )
        if bridge_result is not None:
            return bridge_result

    try:
        ue_cmd, uproject, script = require_scripts_config(config, script_name)
    except SubprocessConfigError as exc:
        return {"error": str(exc)}

    with tempfile.NamedTemporaryFile(
        mode="w", suffix=".json", delete=False, encoding="utf-8"
    ) as plan_fp:
        json.dump(plan, plan_fp, indent=2)
        plan_path = Path(plan_fp.name)

    sidecar = plan_path.with_name(plan_path.name + sidecar_suffix)
    command = _build_plan_ue_command(ue_cmd, uproject, script, plan_path)

    run = run_ue_subprocess(command, timeout=timeout)
    if run.timed_out:
        plan_path.unlink(missing_ok=True)
        sidecar.unlink(missing_ok=True)
        return {
            "error": f"UnrealEditor-Cmd.exe timed out after {timeout}s",
            "command": command,
            "stdoutTail": run.stdout[-2000:],
            "stderrTail": run.stderr[-2000:],
            "logFile": str(project_log_path(uproject)),
            "hint": (
                "stdoutTail captures what UE wrote before the timeout. "
                "For ordered progress including the `[run_plan]` phase "
                "markers, tail `logFile` — that's the project's native "
                "UE log and has the full trail."
            ),
        }

    # Read sidecar produced by the CLI harness.
    report: dict[str, Any] | None = None
    if sidecar.is_file():
        try:
            report = json.loads(sidecar.read_text(encoding="utf-8"))
        except (OSError, json.JSONDecodeError) as exc:
            report = {"error": f"sidecar parse failure: {exc}"}

    # Always clean the temp plan; keep sidecar only on the caller's behalf
    # via the in-memory report, not as a leak on disk.
    plan_path.unlink(missing_ok=True)
    sidecar.unlink(missing_ok=True)

    result: dict[str, Any] = {
        "exitCode": run.returncode,
        "command": command,
        "report": report,
        "logFile": str(project_log_path(uproject)),
        "transport": "subprocess",
    }

    # Surface partial-apply explicitly — the executor is atomic per op,
    # not per plan. If ops 1..N-1 committed and op N failed, ops 1..N-1
    # are already on disk and rollback is the caller's responsibility
    # (git checkout / p4 revert). Hiding this inside `report.execution`
    # is too easy to miss.
    execution = (report or {}).get("execution") if isinstance(report, dict) else None
    if isinstance(execution, dict):
        aborted_at = execution.get("aborted_at")
        per_op = execution.get("per_op") or []
        if aborted_at is not None:
            committed = sum(
                1
                for entry in per_op
                if isinstance(entry, dict) and entry.get("error") is None
            )
            total = len(plan.get("operations", []))
            result["partialApply"] = True
            result["abortedAt"] = aborted_at
            result["committedOps"] = committed
            result["totalOps"] = total
            result["rollbackWarning"] = (
                f"apply_plan is atomic per op, not per plan: "
                f"{committed} of {total} operations committed to disk "
                f"before op #{aborted_at} failed. Rollback is manual "
                f"(git checkout / p4 revert on the touched .uasset files). "
                f"See `report.execution.per_op` for which ops landed."
            )

    stderr_tail = run.stderr.strip()
    if stderr_tail:
        result["stderrTail"] = stderr_tail[-4000:]
    return result


def validate_plan_impl(
    config: Config, plan_json_str: str, timeout: int = DEFAULT_VALIDATE_TIMEOUT
) -> dict[str, Any]:
    # validate_plan is read-only (no asset mutations) — no confirmation
    # gate. Runs the UE-side validator directly after shape passes.
    return _run_plan_script(
        config,
        "run_plan_validator.py",
        ".validation.json",
        plan_json_str,
        timeout,
        confirm=True,
        confirm_message="",
        bridge_method="validate_plan",
        bridge_re_export=False,  # read-only; nothing to re-export
    )


def apply_plan_impl(
    config: Config,
    plan_json_str: str,
    confirm: bool = False,
    re_export: bool = True,
    timeout: int = DEFAULT_APPLY_TIMEOUT,
) -> dict[str, Any]:
    return _run_plan_script(
        config,
        "run_plan.py",
        ".run.json",
        plan_json_str,
        timeout,
        confirm=confirm,
        confirm_message=(
            "apply_plan will MUTATE assets on disk. If an editor is running "
            "with the plugin loaded, this routes through the M27 in-process "
            "bridge (sub-second roundtrip, editor UI briefly frozen during "
            "execution); otherwise it falls back to shelling to "
            "UnrealEditor-Cmd.exe (2-5 min cold start). Each op is atomic "
            "per-op, NOT per-plan: if op 3 of 5 fails, ops 1 and 2 are "
            "already committed. Rollback is the caller's responsibility "
            "(git checkout / p4 revert). Review the `plan` preview below "
            "with the human before re-calling with confirm=true."
        ),
        bridge_method="apply_plan",
        bridge_re_export=re_export,
    )


# -----------------------------------------------------------------------------
# Registration
# -----------------------------------------------------------------------------


def register(mcp: FastMCP, config: Config) -> None:
    @mcp.tool
    def get_op_catalog(name_filter: str | None = None) -> dict[str, Any]:
        """Auto-catalog of every op exported from `scripts/python_ops/`.

        Walks the package's `__init__.py` re-exports, then parses each
        referenced submodule to extract every op's name, docstring,
        parameter schema (name, annotation, required/default), and a
        `readOnly` flag so colleagues can tell at a glance which ops
        mutate assets vs only read state. AST-only, no UE process.

        New ops surface here automatically as they ship — the MCP server
        does not need to change per op.

        Args:
            name_filter: Optional case-insensitive substring matched
                against op `name`. The unfiltered catalog has grown
                past common MCP-client tool-result inlining limits
                (~26K tokens at 60+ ops); pass a substring like
                `"struct"` or `"add_macro"` to scope the response.
                Omit or pass `None`/`""` to get every op.

        Returns:
            `{scriptsRoot, count, ops: [{name, module, docstring,
            readOnly: bool, parameters: [{name, annotation, required,
            default}]}]}`. When `name_filter` is applied the response
            also carries `filter` (echoed) and `total` (unfiltered op
            count) so callers can tell how many ops were hidden.
            `readOnly=true` ops (e.g. `verify_state_transitions`)
            observe the project; all others mutate when run via
            `apply_plan`.
        """
        return get_op_catalog_impl(config.scripts_root, name_filter)

    @mcp.tool
    def validate_plan(plan_json: str) -> dict[str, Any]:
        """Pre-flight an EditPlan with the M24.1 validator.

        Two-phase:

        1. MCP-side shape validation (fast, no UE): checks top-level
           fields, known op names, required/optional kwargs, and
           verification-entry shapes. Fails in <100ms on malformed input.
        2. UE-side validation (slow, launches UnrealEditor-Cmd.exe):
           walks every target asset + StateTree state-path via
           `BpxReflectionOps.get_property_value`. READ-ONLY — no
           mutations, no saves. Expect 2-5 min on cold start (engine
           boot + Python init); subsequent calls in the same session
           are not cached. For quick exploration, prefer the retrieval
           tools (list_assets, get_asset_deep_dump) which read from
           the pre-committed inventory without spawning UE.

        Plan JSON shape — each op flattens its kwargs into the op dict.
        DO NOT wrap kwargs in an `args` object; `get_op_catalog` lists
        the required kwargs per op. Example:

            {
              "intended_outcome": "Add missing MoveToClue -> CombatLoop transition",
              "risk_level": "low",
              "operations": [
                {
                  "op": "add_statetree_transition",
                  "st_path": "/Game/CombatPrototype/ST_EnemyBase",
                  "state_path": ["SubTrees", "[1]", "Children", "[1]"],
                  "trigger": "OnStateCompleted",
                  "target_state_path": ["SubTrees", "[2]"],
                  "priority": "Normal"
                }
              ],
              "expected_side_effects": [],
              "verification": []
            }

        UE-side phase requires `BPX_ENGINE_ROOT`, `BPX_UPROJECT`, and
        (usually auto-derived) `BPX_SCRIPTS_ROOT`. Shape phase only
        needs `BPX_SCRIPTS_ROOT`.

        Args:
            plan_json: An EditPlan as a JSON string (per the schema in
                `scripts/python_ops/plans/README.md`).

        Returns:
            On shape rejection: `{error, report}` where `report` is the
            shape validator's `{passed: false, errors, warnings,
            per_op}` — UE is NOT invoked.
            On UE-side run: `{exitCode, command, report, stderrTail?}`.
            `exitCode == 0` means passed; `== 1` means the validator
            rejected; `== 2` means CLI misuse. On config errors, returns
            `{error: ...}` without invoking UE.
        """
        return validate_plan_impl(config, plan_json)

    @mcp.tool
    def apply_plan(
        plan_json: str, confirm: bool = False, re_export: bool = True
    ) -> dict[str, Any]:
        """Run the full M24 loop on an EditPlan — validate → execute → diff → re-export.

        MUTATES project assets on disk. Requires explicit human
        confirmation — the default call returns a preview so the agent
        can show the human what would happen; a second call with
        `confirm=true` actually runs it.

        Three-phase flow:

        1. MCP-side shape validation (fast, no UE) — rejects malformed
           plans without spawning UE.
        2. Confirmation preview (if `confirm=False`, the default) —
           returns `{requiresConfirmation: true, message, plan,
           plannedCommand, engineConfig, nextStep}` describing what
           would run. Nothing is launched or written.
        3. UE-side full loop (only when `confirm=True`): shells to
           `scripts/run_plan.py`, mutates assets via UE's native save
           path. Atomic per op, NOT per plan — if op 3 of 5 fails, ops
           1 and 2 are already committed. Rollback is the caller's
           responsibility (git checkout / p4 revert).

        M27.3 — when the bridge transport is used AND the plan passes,
        the editor re-exports `.md` / `.meta.json` / `.deep.md` sidecars
        for every touched asset (as surfaced by the mechanical diff) into
        the configured `BPX_INVENTORY_ROOT`. This closes the "manual
        `refresh_inventory` after each plan" agent-loop step for UBP +
        StateTree targets. Scope + limitations:
          - Only UBlueprint family + StateTree are re-exported in-process.
            Other asset types (DataAsset instances, BT, DT, Chooser, etc.)
            appear in the response with `status: "unsupported"` and need
            `refresh_inventory` to update their sidecars.
          - The re-exported `.md` is a brief placeholder (identity +
            pointer to `get_asset_deep_dump`) rather than the full Tier 1
            summary. `.deep.md` and `.meta.json` are regenerated to the
            canonical format. Run `refresh_inventory` if you specifically
            need the Tier 1 `.md` reformatted.
          - Subprocess fallback path does NOT re-export (the headless
            commandlet already does its own full-project scan when
            invoked separately).

        Plan JSON shape — each op flattens its kwargs into the op dict.
        DO NOT wrap kwargs in an `args` object; `get_op_catalog` lists
        the required kwargs per op. Example:

            {
              "intended_outcome": "Fix Peek LOS-gate firing",
              "risk_level": "low",
              "operations": [
                {
                  "op": "add_statetree_enter_condition",
                  "st_path": "/Game/CombatPrototype/ST_EnemyBase",
                  "state_path": ["SubTrees", "[2]", "Children", "[3]"],
                  "condition_bp_path": "/Game/CombatPrototype/ST_Cond_CanSeeTarget"
                }
              ],
              "expected_side_effects": [
                "ST_EnemyBase.Peek gains an EnterCondition referencing ST_Cond_CanSeeTarget"
              ],
              "verification": [
                {"asset_exists": "/Game/CombatPrototype/ST_EnemyBase"}
              ]
            }

        Requires `BPX_ENGINE_ROOT`, `BPX_UPROJECT`, and (usually
        auto-derived) `BPX_SCRIPTS_ROOT`. The plan's target assets must
        live under the configured `.uproject`'s Content tree; cross-
        project applies are not supported.

        Agent guidance: call with `confirm=false` first, show the
        preview to the human, wait for their explicit approval, THEN
        re-call with `confirm=true`. Do not auto-confirm.

        Args:
            plan_json: An EditPlan as a JSON string (per the schema in
                `scripts/python_ops/plans/README.md`).
            confirm: When False (default), returns a preview and does
                not launch UE. Set to True only after a human has
                approved the preview.
            re_export: When True (default), and the bridge transport is
                used, and the plan passes — the editor re-exports
                sidecars for touched UBP / StateTree assets. Set False
                to skip (debugging, benchmarking the raw plan run).

        Returns:
            On shape rejection: `{error, report}` with the shape
            validator's `{passed: false, errors, warnings, per_op}` —
            UE is NOT invoked.
            On `confirm=false`: `{requiresConfirmation: true, message,
            plan, plannedCommand, engineConfig, nextStep}`.
            On bridge-path run: `{report, transport: "bridge",
            reExport: {scopedPaths[], wroteFiles[], errorCount,
            perAsset[]} | {skipped: true, reason}}`.
            On subprocess-path run: `{exitCode, command, report,
            stderrTail?, transport: "subprocess"}` — no `reExport`
            block (subprocess path doesn't auto-re-export).
            On config errors (with confirm=true), returns
            `{error: ...}` without invoking UE.
        """
        return apply_plan_impl(
            config, plan_json, confirm=confirm, re_export=re_export
        )
