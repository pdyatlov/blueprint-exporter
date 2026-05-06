"""Shared UnrealEditor-Cmd subprocess plumbing.

Used by `tools/plans.py` (pythonscript invocations for M24 plan pipeline)
and `tools/live.py` (commandlet invocations for DeepDump / ProjectInventory
re-runs). Keeps the stock headless flags + config validation in one place.

Perforce / source-control rule
==============================
Don't cause a silent `p4 edit` / `p4 submit` / `p4 revert` behind a user's
back. Concrete risk: `apply_plan` mutates `.uasset` files and
`UPackage::SavePackage` routes through `ISourceControlModule` when active,
so ambient Perforce config (`P4USER` / `.p4config` / `SourceControlSettings
.ini Provider=Perforce`) can auto-checkout on save with no explicit P4 flag.

The rule is **inform the user and get explicit approval before any
Perforce operation** — it is NOT "refuse all P4 forever". P4 is allowed
when the user has said yes in the current request. There is no code-level
guard here on purpose: that's a behavioural contract for the MCP client
(Claude) to honour via the existing `confirm=True` gate on mutating tools
(`apply_plan`, `refresh_inventory`) plus explicit narration of expected
source-control side effects in the preview. See the README "House rules"
section and `server.py`'s instructions block.

Questions about this rule, or about any MCP behaviour in general, go to
Niclas.
"""
from __future__ import annotations

import subprocess
import tempfile
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable

from ..config import Config


UE_STOCK_FLAGS = (
    "-nullrhi",
    "-unattended",
    "-nopause",
    "-nosplash",
    "-nosound",
    # `-stdout` was dropped 2026-04-21 after py-spy caught UE's
    # PythonScriptPlugin deterministically blocking in fflush_nolock
    # during type-hint generation. See run_ue_subprocess below for the
    # companion fix — UE must be launched with file-backed stdout/stderr
    # rather than OS pipes, or the same deadlock recurs WITHOUT
    # `-stdout` because Python itself writes to sys.stdout during
    # PyGenUtil type generation.
)


@dataclass(frozen=True)
class UeRunResult:
    """Normalised result from a UE subprocess launch.

    On timeout: `timed_out=True`, `returncode=None`, stdout/stderr are
    whatever the subprocess had written to the tempfiles up to the kill.
    On normal exit: `timed_out=False`, `returncode` is the subprocess
    exit code, stdout/stderr are the full capture.
    """

    returncode: int | None
    stdout: str
    stderr: str
    timed_out: bool


def run_ue_subprocess(
    command: list[str], *, timeout: int
) -> UeRunResult:
    """Launch UE and capture stdout/stderr via tempfiles, not OS pipes.

    Why not `subprocess.run(capture_output=True)`: `capture_output` wires
    stdout/stderr to OS pipes. Windows CRT + pipe interaction during
    UE's PythonScriptPlugin type-hint generation (`PyGenUtilAccessor::
    GetPropertyPythonType`) deterministically deadlocks in
    `fflush_nolock` once sys.stdout writes cross a Windows pipe buffer
    threshold on large UClass graphs (Legacy). Verified 2026-04-21 via
    py-spy: identical native stack across multi-second samples, Python
    interpreter stuck inside `Py_InitializeFromConfig` -> the plugin's
    type generator -> the CRT's flush syscall.

    Redirecting both streams to regular files (no pipe buffer, no
    backpressure) sidesteps the deadlock. Cold-start validate against
    Legacy: previously indefinite hang, now ~15 s end-to-end.

    The tempfiles are created with `delete=False`, closed after the
    subprocess exits (or times out), read back into memory as UTF-8
    with `errors="replace"`, and unlinked. Callers see only the
    decoded text via the returned `UeRunResult`.
    """
    # NamedTemporaryFile(delete=False, mode="wb") gives us a Path we can
    # hand to subprocess + read back once UE exits. Binary mode so the
    # subprocess can write arbitrary bytes; we decode on read-back.
    stdout_fh = tempfile.NamedTemporaryFile(
        mode="wb", suffix=".ue-stdout", delete=False
    )
    stderr_fh = tempfile.NamedTemporaryFile(
        mode="wb", suffix=".ue-stderr", delete=False
    )
    stdout_path = Path(stdout_fh.name)
    stderr_path = Path(stderr_fh.name)

    try:
        try:
            completed = subprocess.run(
                command,
                # stdin MUST be DEVNULL, not inherited. Under the MCP
                # server, parent stdin is the Claude Code MCP protocol
                # pipe. UE's Python interpreter init apparently
                # touches fd 0 through CRT, which (on a pipe) triggers
                # the same fflush deadlock the tempfile redirect on
                # stdout/stderr was meant to prevent. Confirmed
                # 2026-04-21: direct bash call works (stdin=terminal),
                # MCP-launched call with only stdout/stderr redirected
                # still hangs (stdin=pipe).
                stdin=subprocess.DEVNULL,
                stdout=stdout_fh,
                stderr=stderr_fh,
                timeout=timeout,
                check=False,
            )
            timed_out = False
            returncode: int | None = completed.returncode
        except subprocess.TimeoutExpired:
            timed_out = True
            returncode = None
        finally:
            # Close the file handles so we can read back what the
            # subprocess wrote before it was killed / exited.
            stdout_fh.close()
            stderr_fh.close()

        stdout_text = stdout_path.read_text(
            encoding="utf-8", errors="replace"
        )
        stderr_text = stderr_path.read_text(
            encoding="utf-8", errors="replace"
        )
    finally:
        # Best-effort unlink — on Windows, the OS occasionally keeps a
        # transient lock on the file even after both parent close and
        # child exit. Failing here would poison an otherwise-successful
        # run; the OS temp dir is self-cleaning.
        for p in (stdout_path, stderr_path):
            try:
                p.unlink(missing_ok=True)
            except PermissionError:
                pass

    return UeRunResult(
        returncode=returncode,
        stdout=stdout_text,
        stderr=stderr_text,
        timed_out=timed_out,
    )


class SubprocessConfigError(Exception):
    """Raised when required env vars are missing or paths don't resolve."""


def build_ue_command(
    ue_cmd: Path,
    uproject: Path,
    run_kind: str,
    extra_args: Iterable[str],
) -> list[str]:
    """Assemble a headless UnrealEditor-Cmd.exe argv.

    Example: `build_ue_command(cmd, proj, "DeepDump", ["-Asset=/Game/Foo",
    "-OutDir=C:/tmp/out"])` produces the usual
    `<cmd> <proj> -run=DeepDump -Asset=... -OutDir=... -nullrhi ...` form.
    """
    argv: list[str] = [str(ue_cmd), str(uproject), f"-run={run_kind}"]
    argv.extend(extra_args)
    argv.extend(UE_STOCK_FLAGS)
    return argv


def project_log_path(uproject: Path) -> Path:
    """Derive the canonical UE log location for `<uproject>`.

    UE writes the active session's log to
    `<project_dir>/Saved/Logs/<ProjectName>.log`. Since `-stdout` is no
    longer passed (pipe backpressure hang on Legacy, 2026-04-21), this
    file is the ONLY place subprocess-era signal lives. Surfaced as
    `logFile` on every response + in every timeout error.
    """
    return uproject.parent / "Saved" / "Logs" / f"{uproject.stem}.log"


def require_ue_config(config: Config) -> tuple[Path, Path]:
    """Return (ue_cmd, uproject); raise SubprocessConfigError on missing bits.

    Does NOT check scripts_root — callers that need it should call
    `require_scripts_config` instead.
    """
    if config.ue_cmd is None:
        raise SubprocessConfigError(
            "BPX_ENGINE_ROOT not set. Point this at the UE `Engine/` dir "
            "(e.g. 'C:/Program Files/Epic Games/UE_5.7/Engine')."
        )
    if not config.ue_cmd.is_file():
        raise SubprocessConfigError(
            f"UnrealEditor-Cmd.exe not found under BPX_ENGINE_ROOT at {config.ue_cmd}"
        )
    if config.uproject is None:
        raise SubprocessConfigError(
            "BPX_UPROJECT not set. Point this at the full path to the "
            "`.uproject` the tool should run against."
        )
    if not config.uproject.is_file():
        raise SubprocessConfigError(f"BPX_UPROJECT is not a file: {config.uproject}")
    return config.ue_cmd, config.uproject


def require_scripts_config(
    config: Config, script_name: str
) -> tuple[Path, Path, Path]:
    """Return (ue_cmd, uproject, script_path) for pythonscript invocations."""
    ue_cmd, uproject = require_ue_config(config)
    if config.scripts_root is None:
        raise SubprocessConfigError(
            "scripts_root not resolved. Either set BPX_SCRIPTS_ROOT, or "
            "ensure the MCP package lives next to `python_ops/` + "
            "`run_plan.py` so auto-derivation can find them."
        )
    script = config.scripts_root / script_name
    if not script.is_file():
        raise SubprocessConfigError(
            f"{script_name} not found at {script} (check BPX_SCRIPTS_ROOT)."
        )
    return ue_cmd, uproject, script
