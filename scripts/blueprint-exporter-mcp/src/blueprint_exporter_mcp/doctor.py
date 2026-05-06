"""Command-line config doctor.

Prints resolved configuration and validates every env-var-reachable path.
Primary goal: catch colleague setup mistakes before they reach an MCP
client (where the same failures surface as cryptic "server failed" badges).

Runs without importing UE; safe to invoke from any shell with Python 3.10+.

Exit codes:
    0 -- all checks passed
    1 -- one or more checks failed (look for ``[FAIL]`` lines)
    2 -- the config object itself could not be built (missing required env)

Entry point: ``bpx-mcp-doctor`` (see pyproject.toml ``[project.scripts]``).
"""
from __future__ import annotations

import asyncio
import os
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable

from . import __version__
from .config import Config, ConfigError


OK = "[ok]   "
WARN = "[warn] "
FAIL = "[FAIL] "


@dataclass
class _Check:
    ok: bool
    label: str
    detail: str = ""


def _check_path(
    label: str,
    p: Path | None,
    *,
    kind: str,
    required: bool,
) -> _Check:
    """Verify a path exists and is the expected kind ('dir' | 'file')."""
    if p is None:
        if required:
            return _Check(False, label, "not set")
        return _Check(True, label, "unset (optional)")
    if not p.exists():
        return _Check(False, label, f"missing: {p}")
    if kind == "dir" and not p.is_dir():
        return _Check(False, label, f"expected dir, got file: {p}")
    if kind == "file" and not p.is_file():
        return _Check(False, label, f"expected file, got dir: {p}")
    return _Check(True, label, str(p))


def _check_inventory_shape(inventory_root: Path) -> _Check:
    """`BPX_INVENTORY_ROOT` should contain `Assets/` + a top-level `INDEX.md`."""
    if not (inventory_root / "Assets").is_dir():
        return _Check(
            False,
            "inventory shape",
            f"missing Assets/ under {inventory_root}",
        )
    if not (inventory_root / "INDEX.md").is_file():
        return _Check(
            False,
            "inventory shape",
            f"missing INDEX.md under {inventory_root} (expected an "
            "AggregateInventory-produced tree)",
        )
    return _Check(True, "inventory shape", "Assets/ + INDEX.md present")


def _check_ue_cmd(config: Config) -> _Check:
    ue_cmd = config.ue_cmd
    if ue_cmd is None:
        return _Check(
            True,
            "UnrealEditor-Cmd.exe",
            "unset (optional -- only needed for plan-pipeline / live tools)",
        )
    if not ue_cmd.is_file():
        return _Check(
            False,
            "UnrealEditor-Cmd.exe",
            (
                f"not found at {ue_cmd} -- BPX_ENGINE_ROOT should point at the "
                "Engine/ directory (e.g. 'C:/Program Files/Epic Games/UE_5.7/Engine'), "
                "not a subfolder or the top of the engine tree."
            ),
        )
    return _Check(True, "UnrealEditor-Cmd.exe", str(ue_cmd))


def _check_scripts_content(scripts_root: Path | None) -> Iterable[_Check]:
    if scripts_root is None:
        yield _Check(
            True,
            "scripts_root content",
            "unset -- plan-pipeline tools will fail until BPX_SCRIPTS_ROOT "
            "is set or the package is installed alongside python_ops/",
        )
        return
    for name in ("run_plan.py", "run_plan_validator.py", "python_ops/__init__.py"):
        p = scripts_root / name
        expected_file = True
        if p.name == "__init__.py":
            expected_file = True
        ok = p.is_file() if expected_file else p.exists()
        yield _Check(
            ok,
            f"scripts/{name}",
            str(p) if ok else f"missing: {p}",
        )


def _check_project_coherence(config: Config) -> _Check:
    """Heuristic: inventory + uproject should target the same project tree.

    Mechanism: the DOW main committed inventory lives inside the plugin
    repo (`<repo>/blueprint-exporter/ProjectInventory_DOW/`); the Legacy
    inventory is delivered externally by DevOps and typically lands in a
    folder whose name contains `legacy`. A colleague who mixes
    BPX_INVENTORY_ROOT from one project with BPX_UPROJECT from another
    gets retrieval tools that disagree with their plan applies -- silently
    wrong unless flagged here.

    We can't introspect the inventory to extract 'which uproject it was
    produced from' reliably, so this is a tagged-path heuristic that
    warns rather than fails. False positives are fine; silent wrongness
    is not.
    """
    if config.uproject is None:
        return _Check(
            True,
            "inventory <-> uproject coherence",
            "BPX_UPROJECT unset; coherence check skipped",
        )
    inv = str(config.inventory_root).lower().replace("\\", "/")
    up = str(config.uproject).lower().replace("\\", "/")

    # Heuristic: match on substrings most colleagues encounter. Order
    # matters for BOTH lookups -- 'ue_dow' is a substring of 'ue_dow_legacy'
    # so the longer / more specific patterns must be tried first.
    #
    # Colleagues may name their local folders differently. If a path
    # doesn't hit any pattern, this check skips (returns OK with a
    # "heuristic skipped" detail) -- we only fail on an _observed_
    # mismatch, never on absence of signal.
    inv_patterns = [
        ("_dow_legacy_inventory", "ue_dow_legacy"),
        ("dow_legacy_inventory", "ue_dow_legacy"),
        ("dow-legacy-inventory", "ue_dow_legacy"),
        ("projectinventory_dow", "ue_dow"),
        ("projectinventory-dow", "ue_dow"),
        ("bughunt/testproject/projectinventory", "bughunt"),
        ("bughunt\\testproject\\projectinventory", "bughunt"),
        ("blueprint-exporter/projectinventory", "bughunt"),
        ("blueprint-exporter\\projectinventory", "bughunt"),
    ]
    up_patterns = [
        ("ue_dow_legacy", "ue_dow_legacy"),
        ("ue-dow-legacy", "ue_dow_legacy"),
        ("dow_legacy", "ue_dow_legacy"),
        ("dow-legacy", "ue_dow_legacy"),
        ("bughunt", "bughunt"),
        ("ue_dow", "ue_dow"),
        ("ue-dow", "ue_dow"),
    ]
    inv_project = next(
        (tag for needle, tag in inv_patterns if needle in inv), None
    )
    up_project = next(
        (tag for needle, tag in up_patterns if needle in up), None
    )
    if inv_project is None or up_project is None:
        return _Check(
            True,
            "inventory <-> uproject coherence",
            "heuristic skipped (paths don't match known patterns)",
        )
    if inv_project != up_project:
        return _Check(
            False,
            "inventory <-> uproject coherence",
            (
                f"inventory looks like '{inv_project}' but uproject looks "
                f"like '{up_project}' -- retrieval tools will see a different "
                "asset set than plan-pipeline tools. See README 'Per-project "
                "config matrix'. If you intentionally want two views, run "
                "two server entries under different names."
            ),
        )
    return _Check(
        True,
        "inventory <-> uproject coherence",
        f"both look like '{inv_project}'",
    )


def _check_tool_registration() -> _Check:
    """Simulate registering every tool -- catches import errors / decorator bugs."""
    try:
        from fastmcp import FastMCP

        from .tools import live, plans, retrieval
    except Exception as exc:  # pragma: no cover -- tool bugs surface at import
        return _Check(False, "tool imports", f"{type(exc).__name__}: {exc}")

    try:
        config = Config.from_env()
    except ConfigError as exc:
        # The caller's _build_and_collect handles this; shouldn't reach here.
        return _Check(False, "tool registration", str(exc))

    try:
        mcp = FastMCP(name="doctor")
        retrieval.register(mcp, config)
        plans.register(mcp, config)
        live.register(mcp, config)
        tools = asyncio.run(mcp.list_tools())
    except Exception as exc:  # pragma: no cover
        return _Check(False, "tool registration", f"{type(exc).__name__}: {exc}")
    return _Check(True, "tool registration", f"{len(tools)} tools registered")


def _print(check: _Check) -> None:
    prefix = OK if check.ok else FAIL
    tail = f" -- {check.detail}" if check.detail else ""
    print(f"{prefix}{check.label}{tail}")


def _header() -> None:
    # Some Windows consoles default to cp1252; keep output strictly ASCII so
    # `bpx-mcp-doctor` never crashes before printing the real diagnostic.
    try:
        sys.stdout.reconfigure(encoding="utf-8")
    except (AttributeError, OSError):
        pass
    print(f"blueprint-exporter-mcp doctor -- package {__version__}")
    print(f"python {sys.version.split()[0]} at {sys.executable}")
    print()


def run() -> int:
    _header()

    try:
        config = Config.from_env()
    except ConfigError as exc:
        print(f"{FAIL}Config.from_env -- {exc}")
        print()
        print("Config could not be built. Fix BPX_INVENTORY_ROOT first, then re-run.")
        return 2

    checks: list[_Check] = []
    checks.append(_check_path(
        "BPX_INVENTORY_ROOT", config.inventory_root, kind="dir", required=True,
    ))
    checks.append(_check_inventory_shape(config.inventory_root))
    checks.append(_check_path(
        "BPX_ENGINE_ROOT", config.engine_root, kind="dir", required=False,
    ))
    checks.append(_check_ue_cmd(config))
    checks.append(_check_path(
        "BPX_UPROJECT", config.uproject, kind="file", required=False,
    ))
    checks.append(_check_path(
        "BPX_SCRIPTS_ROOT", config.scripts_root, kind="dir", required=False,
    ))
    for c in _check_scripts_content(config.scripts_root):
        checks.append(c)
    checks.append(_check_project_coherence(config))
    checks.append(_check_tool_registration())

    for c in checks:
        _print(c)

    failed = [c for c in checks if not c.ok]
    print()
    if failed:
        print(f"{FAIL}{len(failed)} check(s) failed -- see [FAIL] lines above.")
        return 1
    print(f"{OK}all checks passed")
    return 0


if __name__ == "__main__":
    sys.exit(run())
