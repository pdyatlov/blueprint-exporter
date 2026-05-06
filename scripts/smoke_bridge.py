"""M27.4 editor-bridge smoke test.

Connects to a running UE editor's bridge server, exercises every
registered method with shape-valid params, and prints a categorized
result line per test. Exits 0 if no test is in the FAILURE category;
EXPECTED_ERROR is a valid pass (e.g. empty-ops plans are deliberately
rejected by the validator so we send one to prove the error path works
end-to-end).

Usage:
    python scripts/smoke_bridge.py

Environment:
    BPX_BRIDGE_PORT  overrides the default port (1337). Set this when
                     the editor was launched with the same override.

The script does NOT start a UE editor. Launch one with this plugin
loaded first, wait for the `Bridge server listening on 127.0.0.1:<port>`
line in the log, then run this.

Categorization:
    OK              transport succeeded, response.result present, passes
                    test-specific assertions.
    EXPECTED_ERROR  transport succeeded AND response.error present with
                    the expected code. We WANT this outcome for negative
                    tests (malformed JSON, unknown method, missing
                    jsonrpc, intentionally-rejected plans) — exiting 0
                    if these are the only "failures" keeps the smoke
                    test honest.
    FAILURE         transport failed, response shape unexpected, or
                    assertions missed. Drives exit code != 0.
"""
from __future__ import annotations

import asyncio
import json
import os
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Callable

try:
    import websockets
except ImportError:
    print("ERROR: `pip install websockets` first (>=12).", file=sys.stderr)
    sys.exit(2)


DEFAULT_PORT = 1337
# 15s handles large-project cold connections (DOW-scale editors with
# 10+ GB working set take several seconds on the first handshake).
# BugHunt-sized projects answer in well under a second.
CONNECT_TIMEOUT_S = 15.0
RECV_TIMEOUT_S = 30.0


def resolve_port() -> int:
    raw = os.environ.get("BPX_BRIDGE_PORT", "").strip()
    if not raw:
        return DEFAULT_PORT
    try:
        parsed = int(raw)
    except ValueError:
        return DEFAULT_PORT
    return parsed if 1 <= parsed <= 65535 else DEFAULT_PORT


def resolve_scripts_root() -> str:
    """The bridge's plan handlers need a scripts root where `bridge_entry.py`
    and the `python_ops/` package live. For the smoke script, assume we're
    under `<repo>/scripts/` and point at ourselves."""
    return str(Path(__file__).resolve().parent)


@dataclass
class TestResult:
    name: str
    category: str  # "OK" | "EXPECTED_ERROR" | "FAILURE"
    detail: str = ""
    response: dict[str, Any] | None = None


@dataclass
class TestCase:
    name: str
    # Either a JSON-RPC request dict or a raw string (used for malformed-JSON test).
    request: dict[str, Any] | str
    # Called with the parsed response + returns (category, detail).
    # If the server couldn't parse the raw input, `response` may lack "id".
    check: Callable[[dict[str, Any]], tuple[str, str]]
    # If True, send as raw bytes (for malformed-JSON injection).
    raw: bool = False


def check_ping(resp: dict[str, Any]) -> tuple[str, str]:
    result = resp.get("result") or {}
    if not isinstance(result, dict):
        return "FAILURE", f"result is not an object: {result!r}"
    if result.get("pong") is not True:
        return "FAILURE", f"pong != true: {result.get('pong')!r}"
    pv = result.get("pluginVersion")
    if not isinstance(pv, str) or not pv:
        return "FAILURE", f"pluginVersion missing/empty: {pv!r}"
    return "OK", f"pluginVersion={pv}"


def check_list_methods(resp: dict[str, Any]) -> tuple[str, str]:
    result = resp.get("result") or {}
    methods = result.get("methods")
    if not isinstance(methods, list):
        return "FAILURE", f"methods is not a list: {methods!r}"
    if not methods:
        return "FAILURE", "methods list is empty"
    names = []
    for entry in methods:
        if not isinstance(entry, dict) or "name" not in entry:
            return "FAILURE", f"malformed entry: {entry!r}"
        names.append(entry["name"])
    expected = {"ping", "list_methods", "validate_plan", "apply_plan"}
    missing = expected - set(names)
    if missing:
        return "FAILURE", f"missing expected methods: {sorted(missing)}"
    without_desc = [e["name"] for e in methods if not e.get("description")]
    if without_desc:
        return "FAILURE", f"registered without description: {without_desc}"
    return "OK", f"{len(names)} methods registered"


def check_unknown_method(resp: dict[str, Any]) -> tuple[str, str]:
    err = resp.get("error") or {}
    if not isinstance(err, dict):
        return "FAILURE", f"no error object: {resp!r}"
    if err.get("code") != -32601:
        return "FAILURE", f"expected code -32601, got {err.get('code')!r}"
    return "EXPECTED_ERROR", f"code -32601 method not found"


def check_missing_jsonrpc(resp: dict[str, Any]) -> tuple[str, str]:
    err = resp.get("error") or {}
    if err.get("code") != -32600:
        return "FAILURE", f"expected code -32600, got {err.get('code')!r}"
    return "EXPECTED_ERROR", f"code -32600 invalid request"


def check_malformed_json(resp: dict[str, Any]) -> tuple[str, str]:
    err = resp.get("error") or {}
    if err.get("code") != -32700:
        return "FAILURE", f"expected code -32700, got {err.get('code')!r}"
    return "EXPECTED_ERROR", f"code -32700 parse error"


def check_validate_plan_empty_ops(resp: dict[str, Any]) -> tuple[str, str]:
    """We deliberately send an empty-ops plan. The MCP-side shape validator
    isn't in the loop here (direct websocket); the UE-side validator should
    reject with `operations must be non-empty`. A passing run-report with
    that in errors is the expected outcome."""
    result = resp.get("result") or {}
    if not isinstance(result, dict):
        return "FAILURE", f"result not an object: {result!r}"
    report = result.get("report")
    if not isinstance(report, dict):
        return "FAILURE", f"result.report not an object: {report!r}"
    if report.get("passed") is not False:
        return "FAILURE", f"expected report.passed=false, got {report.get('passed')!r}"
    errors = report.get("errors") or []
    if not any("non-empty" in str(e) or "operations" in str(e) for e in errors):
        return "FAILURE", f"expected 'operations must be non-empty' error, got {errors!r}"
    return "EXPECTED_ERROR", "validator rejected empty operations as designed"


def check_apply_plan_empty_ops(resp: dict[str, Any]) -> tuple[str, str]:
    """Apply path with empty-ops: validator fails via execution.validation_report,
    so report.passed=false and reExport is skipped with a clear reason."""
    result = resp.get("result") or {}
    if not isinstance(result, dict):
        return "FAILURE", f"result not an object: {result!r}"
    report = result.get("report")
    if not isinstance(report, dict):
        return "FAILURE", f"result.report not an object: {report!r}"
    if report.get("passed") is not False:
        return "FAILURE", f"expected report.passed=false, got {report.get('passed')!r}"
    re_export = result.get("reExport")
    if not isinstance(re_export, dict) or not re_export.get("skipped"):
        return "FAILURE", f"expected reExport.skipped=true, got {re_export!r}"
    return "EXPECTED_ERROR", "validator rejected; reExport skipped as designed"


def build_test_cases(scripts_root: str) -> list[TestCase]:
    empty_plan = json.dumps(
        {
            "intended_outcome": "M27.4 smoke — empty-ops plan",
            "risk_level": "low",
            "operations": [],
            "expected_side_effects": [],
            "verification": [],
        }
    )
    return [
        TestCase(
            "ping",
            {"jsonrpc": "2.0", "id": 1, "method": "ping"},
            check_ping,
        ),
        TestCase(
            "list_methods",
            {"jsonrpc": "2.0", "id": 2, "method": "list_methods"},
            check_list_methods,
        ),
        TestCase(
            "unknown_method",
            {"jsonrpc": "2.0", "id": 3, "method": "this_method_does_not_exist"},
            check_unknown_method,
        ),
        TestCase(
            "missing_jsonrpc_field",
            {"id": 4, "method": "ping"},
            check_missing_jsonrpc,
        ),
        TestCase(
            "malformed_json",
            "{not valid json",
            check_malformed_json,
            raw=True,
        ),
        TestCase(
            "validate_plan_empty_ops",
            {
                "jsonrpc": "2.0",
                "id": 6,
                "method": "validate_plan",
                "params": {"planJson": empty_plan, "scriptsRoot": scripts_root},
            },
            check_validate_plan_empty_ops,
        ),
        TestCase(
            "apply_plan_empty_ops",
            {
                "jsonrpc": "2.0",
                "id": 7,
                "method": "apply_plan",
                "params": {"planJson": empty_plan, "scriptsRoot": scripts_root},
            },
            check_apply_plan_empty_ops,
        ),
    ]


async def run_case(ws, case: TestCase) -> TestResult:
    try:
        if case.raw:
            assert isinstance(case.request, str)
            await ws.send(case.request)
        else:
            await ws.send(json.dumps(case.request))
        raw_resp = await asyncio.wait_for(ws.recv(), timeout=RECV_TIMEOUT_S)
    except asyncio.TimeoutError:
        return TestResult(case.name, "FAILURE", f"recv timed out after {RECV_TIMEOUT_S}s")
    except Exception as exc:
        return TestResult(case.name, "FAILURE", f"send/recv error: {type(exc).__name__}: {exc}")

    try:
        resp = json.loads(raw_resp)
    except json.JSONDecodeError as exc:
        return TestResult(case.name, "FAILURE", f"response not JSON: {exc}; raw={raw_resp[:200]!r}")

    try:
        category, detail = case.check(resp)
    except Exception as exc:
        return TestResult(case.name, "FAILURE", f"check raised {type(exc).__name__}: {exc}", response=resp)
    return TestResult(case.name, category, detail, response=resp)


async def main() -> int:
    port = resolve_port()
    scripts_root = resolve_scripts_root()
    uri = f"ws://127.0.0.1:{port}"

    print(f"=== M27.4 bridge smoke test")
    print(f"    uri          : {uri}")
    print(f"    scriptsRoot  : {scripts_root}")
    print()

    try:
        ws = await asyncio.wait_for(websockets.connect(uri, max_size=None), timeout=CONNECT_TIMEOUT_S)
    except asyncio.TimeoutError:
        print(f"FAILURE: connect timed out after {CONNECT_TIMEOUT_S}s — is the editor running with the bridge loaded?")
        return 1
    except (ConnectionRefusedError, OSError) as exc:
        print(f"FAILURE: could not connect to {uri}: {exc} — is the editor running with the bridge loaded?")
        return 1

    counts: dict[str, int] = {"OK": 0, "EXPECTED_ERROR": 0, "FAILURE": 0}
    results: list[TestResult] = []

    try:
        cases = build_test_cases(scripts_root)
        for case in cases:
            result = await run_case(ws, case)
            counts[result.category] = counts.get(result.category, 0) + 1
            results.append(result)
            line = f"  [{result.category:14s}] {result.name:30s} {result.detail}"
            print(line)
    finally:
        await ws.close()

    print()
    total = sum(counts.values())
    print(f"=== Summary: {total} tests  |  "
          f"OK={counts['OK']}  EXPECTED_ERROR={counts['EXPECTED_ERROR']}  FAILURE={counts['FAILURE']}")

    if counts["FAILURE"] == 0:
        print("PASS")
        return 0

    print()
    print("FAILED tests:")
    for r in results:
        if r.category == "FAILURE":
            print(f"  - {r.name}: {r.detail}")
            if r.response is not None:
                print(f"      response: {json.dumps(r.response)[:300]}")
    return 1


if __name__ == "__main__":
    sys.exit(asyncio.run(main()))
