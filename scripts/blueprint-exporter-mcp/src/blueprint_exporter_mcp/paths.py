"""Map UE asset paths to on-disk inventory sidecar paths.

Asset-path conventions we accept:
    /Game/Blueprints/BP_X.BP_X  (UE's fully-qualified form)
    /Game/Blueprints/BP_X       (leading-slash, no subpath)
    Game/Blueprints/BP_X        (no leading slash)

Sidecar suffixes:
    .md          — Tier 1 summary
    .meta.json   — structured sidecar (coverage, properties, cdoProperties, ...)
    .deep.md     — Tier 2 deep dump (present for in-scope classes only)
"""
from __future__ import annotations

from pathlib import Path


def normalize_asset_path(asset_path: str) -> str:
    """Normalise a UE asset path to its relative directory + asset stem.

    '/Game/Blueprints/BP_X.BP_X' -> 'Game/Blueprints/BP_X'
    """
    p = asset_path.strip()
    if p.startswith("/"):
        p = p[1:]
    last_slash = p.rfind("/")
    stem = p[last_slash + 1 :] if last_slash >= 0 else p
    if "." in stem:
        stem = stem.split(".", 1)[0]
    prefix = p[: last_slash + 1] if last_slash >= 0 else ""
    return prefix + stem


def sidecar_path(inventory_root: Path, asset_path: str, suffix: str) -> Path:
    """Resolve a UE asset path to its on-disk sidecar."""
    rel = normalize_asset_path(asset_path)
    return inventory_root / "Assets" / f"{rel}{suffix}"


def asset_path_from_sidecar(
    assets_root: Path, sidecar: Path, suffix: str
) -> str:
    """Derive a UE asset path from a sidecar file under Assets/.

    E.g. Assets/Game/Blueprints/BP_X.deep.md (suffix='.deep.md')
         -> '/Game/Blueprints/BP_X'.
    """
    stem = sidecar.name[: -len(suffix)] if sidecar.name.endswith(suffix) else sidecar.stem
    rel = (sidecar.parent / stem).relative_to(assets_root).as_posix()
    return "/" + rel
