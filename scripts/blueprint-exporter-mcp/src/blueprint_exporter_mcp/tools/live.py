"""Live-introspection tools — on-demand UnrealEditor-Cmd runs.

M25.1.3 ships two tools:
    deep_dump_asset(path)
        Runs `-run=DeepDump -Asset=<path> -OutDir=<tempdir>` and returns
        the generated `.deep.md` content. Use when the inventory is
        stale or missing the asset you care about.
    refresh_inventory(path_filter, deep_dump)
        Runs `-run=ProjectInventory -OutDir=<inventory_root> -Filter=<prefix>
        [-DeepDump]` to re-scan a slice of the project. MUTATES the
        configured `BPX_INVENTORY_ROOT` tree.

Both shell to the same `UnrealEditor-Cmd.exe` as the plan-pipeline
tools. Requires `BPX_ENGINE_ROOT` + `BPX_UPROJECT`; `BPX_SCRIPTS_ROOT`
is NOT required (no pythonscript harness involved).
"""
from __future__ import annotations

import subprocess
import tempfile
import time
from pathlib import Path
from typing import Any

from fastmcp import FastMCP

from ..config import Config
from ..paths import normalize_asset_path
from ._ue_subprocess import (
    SubprocessConfigError,
    build_ue_command,
    project_log_path,
    require_ue_config,
    run_ue_subprocess,
)


_TIMEOUT_HINT = (
    "stdoutTail is empty by design — `-stdout` was dropped to avoid a "
    "pipe-backpressure hang in UE's PythonScriptPlugin type-hint "
    "generator (2026-04-21). Tail `logFile` for the real signal."
)


DEFAULT_DEEP_DUMP_TIMEOUT = 300
DEFAULT_REFRESH_TIMEOUT = 900


def _asset_stem(asset_path: str) -> str:
    """`/Game/X/Foo.Foo` or `/Game/X/Foo` -> `Foo`."""
    rel = normalize_asset_path(asset_path)
    last_slash = rel.rfind("/")
    return rel[last_slash + 1 :] if last_slash >= 0 else rel


def deep_dump_asset_impl(
    config: Config, path: str, timeout: int = DEFAULT_DEEP_DUMP_TIMEOUT
) -> dict[str, Any]:
    try:
        ue_cmd, uproject = require_ue_config(config)
    except SubprocessConfigError as exc:
        return {"error": str(exc)}
    if not path or not path.strip():
        return {"error": "path is required"}

    # Normalise to the `/Game/...` form DeepDumpCommandlet expects.
    asset_path = path.strip()
    if not asset_path.startswith("/"):
        asset_path = "/" + asset_path
    stem = _asset_stem(asset_path)

    out_dir = Path(tempfile.mkdtemp(prefix="bpx-mcp-deep-"))
    command = build_ue_command(
        ue_cmd,
        uproject,
        "DeepDump",
        [f"-Asset={asset_path}", f"-OutDir={out_dir}"],
    )

    started = time.monotonic()
    run = run_ue_subprocess(command, timeout=timeout)
    if run.timed_out:
        _rmtree_silent(out_dir)
        return {
            "error": f"UnrealEditor-Cmd.exe timed out after {timeout}s",
            "command": command,
            "stdoutTail": run.stdout[-2000:],
            "stderrTail": run.stderr[-2000:],
            "logFile": str(project_log_path(uproject)),
            "hint": _TIMEOUT_HINT,
        }
    elapsed = time.monotonic() - started

    deep_md_path = out_dir / f"{stem}.deep.md"
    deep_md = deep_md_path.read_text(encoding="utf-8") if deep_md_path.is_file() else None
    _rmtree_silent(out_dir)

    result: dict[str, Any] = {
        "exitCode": run.returncode,
        "command": command,
        "elapsedSeconds": round(elapsed, 2),
        "asset": asset_path,
        "deepDumpMarkdown": deep_md,
        "logFile": str(project_log_path(uproject)),
    }
    if deep_md is None:
        result["error"] = (
            f"DeepDump produced no {stem}.deep.md under {out_dir}; check "
            "stderrTail + stdoutTail for the commandlet's own error output."
        )
        result["stdoutTail"] = run.stdout[-4000:]
    stderr_tail = run.stderr.strip()
    if stderr_tail:
        result["stderrTail"] = stderr_tail[-4000:]
    return result


def refresh_inventory_impl(
    config: Config,
    path_filter: str,
    deep_dump: bool = False,
    confirm: bool = False,
    timeout: int = DEFAULT_REFRESH_TIMEOUT,
) -> dict[str, Any]:
    if not path_filter or not path_filter.strip():
        return {
            "error": (
                "path_filter is required. Pass a /Game/... prefix to scope "
                "the refresh — a full-project sweep is dangerous (known "
                "KINEMATION crash on full legacy sweeps)."
            )
        }
    filt = path_filter.strip()
    if not filt.startswith("/"):
        filt = "/" + filt

    # Confirmation gate — mutates BPX_INVENTORY_ROOT sidecars under the
    # filter prefix. First call (confirm=False) returns a preview so the
    # agent can show the human what would be overwritten.
    if not confirm:
        preview: dict[str, Any] = {
            "requiresConfirmation": True,
            "message": (
                "refresh_inventory will OVERWRITE sidecar files under "
                "BPX_INVENTORY_ROOT/Assets matching the filter prefix via "
                "UnrealEditor-Cmd.exe. Review the scope below and re-call "
                "with confirm=true if approved. Other paths under "
                "BPX_INVENTORY_ROOT are left untouched."
            ),
            "inventoryRoot": str(config.inventory_root),
            "filter": filt,
            "deepDump": deep_dump,
            "nextStep": (
                "Show this preview to the human. If they approve, "
                "re-call with confirm=true. Nothing has been launched "
                "or written — UE was not invoked."
            ),
        }
        try:
            ue_cmd, uproject = require_ue_config(config)
        except SubprocessConfigError as exc:
            preview["engineConfig"] = {"ready": False, "detail": str(exc)}
        else:
            extras = [f"-OutDir={config.inventory_root}", f"-Filter={filt}"]
            if deep_dump:
                extras.append("-DeepDump")
            preview["engineConfig"] = {"ready": True}
            preview["plannedCommand"] = build_ue_command(
                ue_cmd, uproject, "ProjectInventory", extras
            )
        return preview

    try:
        ue_cmd, uproject = require_ue_config(config)
    except SubprocessConfigError as exc:
        return {"error": str(exc)}

    extras = [f"-OutDir={config.inventory_root}", f"-Filter={filt}"]
    if deep_dump:
        extras.append("-DeepDump")
    command = build_ue_command(ue_cmd, uproject, "ProjectInventory", extras)

    started = time.monotonic()
    run = run_ue_subprocess(command, timeout=timeout)
    if run.timed_out:
        return {
            "error": f"UnrealEditor-Cmd.exe timed out after {timeout}s",
            "command": command,
            "stdoutTail": run.stdout[-2000:],
            "stderrTail": run.stderr[-2000:],
            "logFile": str(project_log_path(uproject)),
            "hint": _TIMEOUT_HINT,
        }
    elapsed = time.monotonic() - started

    result: dict[str, Any] = {
        "exitCode": run.returncode,
        "command": command,
        "elapsedSeconds": round(elapsed, 2),
        "inventoryRoot": str(config.inventory_root),
        "filter": filt,
        "deepDump": deep_dump,
        "logFile": str(project_log_path(uproject)),
    }
    stdout_tail = run.stdout.strip()
    stderr_tail = run.stderr.strip()
    if stdout_tail:
        result["stdoutTail"] = stdout_tail[-4000:]
    if stderr_tail:
        result["stderrTail"] = stderr_tail[-4000:]
    return result


def _rmtree_silent(p: Path) -> None:
    import shutil

    try:
        shutil.rmtree(p)
    except OSError:
        pass


def register(mcp: FastMCP, config: Config) -> None:
    @mcp.tool
    def deep_dump_asset(path: str) -> dict[str, Any]:
        """Run the DeepDump commandlet against a single asset and return its Tier 2 Markdown.

        Spawns `UnrealEditor-Cmd.exe <uproject> -run=DeepDump -Asset=<path>
        -OutDir=<tempdir>`, reads the generated `<stem>.deep.md`, cleans
        up the temp directory, and returns the contents. Use when the
        inventory sidecar is stale (asset was edited since the last sweep)
        or when the asset simply isn't in the committed inventory tree.

        Expect 2-5 min on cold start (engine boot + Python init). For
        quick exploration of existing content, prefer
        `get_asset_deep_dump` which reads the pre-committed inventory
        without spawning UE.

        Requires `BPX_ENGINE_ROOT` + `BPX_UPROJECT`. No asset mutations —
        DeepDump is a read-only commandlet.

        Args:
            path: UE asset path (any of the three forms `list_assets` accepts).

        Returns:
            `{exitCode, command, elapsedSeconds, asset, deepDumpMarkdown,
            stderrTail?, stdoutTail?}`. `deepDumpMarkdown` is null when
            the commandlet produced no file (look at the tails + exit
            code). On config errors, returns `{error: ...}` without
            invoking UE.
        """
        return deep_dump_asset_impl(config, path)

    @mcp.tool
    def refresh_inventory(
        path_filter: str,
        deep_dump: bool = False,
        confirm: bool = False,
    ) -> dict[str, Any]:
        """Re-scan a slice of the project into the configured inventory root.

        MUTATES the configured `BPX_INVENTORY_ROOT` tree — sidecar files
        under `Assets/<prefix>/...` are overwritten. Requires explicit
        human confirmation — the default call returns a preview so the
        agent can show the human what would happen; a second call with
        `confirm=true` actually runs it.

        When approved, spawns `UnrealEditor-Cmd.exe <uproject>
        -run=ProjectInventory -OutDir=<BPX_INVENTORY_ROOT>
        -Filter=<prefix> [-DeepDump]`. Only assets under the filter
        prefix are touched; other paths are left alone.

        A `path_filter` is REQUIRED — a full-project sweep is dangerous
        (known KINEMATION crash on full legacy sweeps), so empty
        filters are refused on purpose.

        Requires `BPX_ENGINE_ROOT` + `BPX_UPROJECT` to actually run; the
        preview step works without them (it just flags
        `engineConfig.ready=false`).

        Agent guidance: call with `confirm=false` first, show the
        preview to the human (inventoryRoot + filter + deepDump), wait
        for their explicit approval, THEN re-call with `confirm=true`.
        Do not auto-confirm.

        Args:
            path_filter: UE path prefix to scope the refresh, e.g.
                "/Game/CombatPrototype".
            deep_dump: If True, passes `-DeepDump` so each processed
                asset also gets its Tier 2 `.deep.md` regenerated.
            confirm: When False (default), returns a preview and does
                not launch UE. Set to True only after a human has
                approved the preview.

        Returns:
            On `confirm=false`: `{requiresConfirmation: true, message,
            inventoryRoot, filter, deepDump, plannedCommand,
            engineConfig, nextStep}`.
            On `confirm=true` run: `{exitCode, command, elapsedSeconds,
            inventoryRoot, filter, deepDump, stdoutTail?, stderrTail?}`.
            No structured result beyond the exit code — the commandlet
            writes directly into the inventory tree, so follow up with
            the retrieval tools to see what landed.
        """
        return refresh_inventory_impl(
            config, path_filter, deep_dump, confirm=confirm
        )
