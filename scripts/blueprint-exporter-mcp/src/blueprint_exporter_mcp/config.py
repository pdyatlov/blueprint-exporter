"""Configuration loaded from environment variables.

Required:
    BPX_INVENTORY_ROOT — path to a ProjectInventory_* tree (contains
        Assets/, INDEX.md, MANIFEST.md, ...).

Optional (required only for plan-pipeline tools M25.1.2+):
    BPX_ENGINE_ROOT  — UE engine `Engine/` directory. The server
        derives the `Binaries/Win64/UnrealEditor-Cmd.exe` path from
        this, so e.g. set to `C:/Program Files/Epic Games/UE_5.7/Engine`.
    BPX_UPROJECT     — full path to the `.uproject` file the plan
        pipeline should run against.
    BPX_SCRIPTS_ROOT — directory containing `run_plan.py`,
        `run_plan_validator.py`, and the `python_ops/` package.
        Auto-derived from this package's location when unset (the
        package ships under `<scripts_root>/blueprint-exporter-mcp/`
        by convention).
    BPX_PROJECT_ROOT — project directory containing the `.uproject`.
        Reserved; unused today.
"""
from __future__ import annotations

import os
from dataclasses import dataclass
from pathlib import Path


class ConfigError(RuntimeError):
    pass


def _default_scripts_root() -> Path | None:
    """Walk up from this file to find a sibling `python_ops/` dir.

    Layout convention:
        <scripts>/python_ops/
        <scripts>/blueprint-exporter-mcp/src/blueprint_exporter_mcp/config.py (this file)
    """
    here = Path(__file__).resolve()
    for parent in here.parents:
        if (parent / "python_ops").is_dir() and (parent / "run_plan.py").is_file():
            return parent
    return None


@dataclass(frozen=True)
class Config:
    inventory_root: Path
    project_root: Path | None
    engine_root: Path | None
    uproject: Path | None
    scripts_root: Path | None

    @property
    def ue_cmd(self) -> Path | None:
        """Resolve `UnrealEditor-Cmd.exe` under the configured engine root."""
        if self.engine_root is None:
            return None
        return self.engine_root / "Binaries" / "Win64" / "UnrealEditor-Cmd.exe"

    @classmethod
    def from_env(cls) -> "Config":
        inv_raw = os.getenv("BPX_INVENTORY_ROOT", "").strip()
        if not inv_raw:
            raise ConfigError(
                "BPX_INVENTORY_ROOT not set. Point this at a ProjectInventory_* "
                "directory (one that contains Assets/, INDEX.md, MANIFEST.md)."
            )
        inv = Path(inv_raw).expanduser().resolve()
        if not inv.is_dir():
            raise ConfigError(f"BPX_INVENTORY_ROOT is not a directory: {inv}")
        if not (inv / "Assets").is_dir():
            raise ConfigError(
                f"BPX_INVENTORY_ROOT does not look like an inventory root "
                f"(missing Assets/): {inv}"
            )

        def _opt(key: str) -> Path | None:
            raw = os.getenv(key, "").strip()
            if not raw:
                return None
            return Path(raw).expanduser().resolve()

        scripts_root = _opt("BPX_SCRIPTS_ROOT") or _default_scripts_root()

        return cls(
            inventory_root=inv,
            project_root=_opt("BPX_PROJECT_ROOT"),
            engine_root=_opt("BPX_ENGINE_ROOT"),
            uproject=_opt("BPX_UPROJECT"),
            scripts_root=scripts_root,
        )
