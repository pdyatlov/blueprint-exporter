"""Retrieval tools — read from the pre-indexed inventory, zero UE process.

Shipped tools:
    M25.1.0:
        list_assets(class_filter, path_prefix, head_limit)
        get_asset_summary(path)
        get_asset_deep_dump(path)
        search_deep_dumps(pattern, class_filter, head_limit)
    M25.1.1:
        get_asset_meta(path)
        get_cdo_properties(path)
        get_references(path, direction)
        get_class_tree(class_name)

Tool bodies are implemented as pure module-level `*_impl` functions so they
stay unit-testable without the MCP round-trip. `register()` wires them to a
FastMCP instance as `@mcp.tool`-decorated closures that bind the Config.
"""
from __future__ import annotations

import json
import re
from pathlib import Path
from typing import Any, Iterable

from fastmcp import FastMCP

from ..config import Config
from ..paths import asset_path_from_sidecar, sidecar_path, normalize_asset_path


MAX_LIST_HEAD = 1000
DEFAULT_LIST_HEAD = 100
MAX_SEARCH_HEAD = 500
DEFAULT_SEARCH_HEAD = 50
META_SUFFIX = ".meta.json"
DEEP_SUFFIX = ".deep.md"


def _iter_meta_files(
    assets_root: Path, path_prefix: str | None
) -> Iterable[Path]:
    """Walk Assets/**/*.meta.json, optionally scoped to a path prefix."""
    if path_prefix:
        norm = normalize_asset_path(path_prefix)
        scoped = assets_root / norm
        candidate_meta = scoped.parent / f"{scoped.name}{META_SUFFIX}"
        if candidate_meta.is_file():
            yield candidate_meta
            return
        if scoped.is_dir():
            yield from scoped.rglob(f"*{META_SUFFIX}")
            return
        return
    yield from assets_root.rglob(f"*{META_SUFFIX}")


def _classify(meta_path: Path) -> tuple[str | None, str | None]:
    """Return (assetPath, className) from a .meta.json sidecar, or (None, None) on error.

    `assetType` is the primary key — it's populated for every class the
    Phase-1 serializer emits (UBlueprint family, StateTree, BehaviorTree,
    DataTable, ChooserTable, UserDefinedStruct, UserDefinedEnum, etc.).
    `blueprintSubclass` duplicates `assetType` for BP-family assets only
    and is read as a legacy fallback.
    """
    try:
        with meta_path.open("r", encoding="utf-8") as f:
            data = json.load(f)
    except (OSError, json.JSONDecodeError):
        return (None, None)
    return (
        data.get("assetPath"),
        data.get("assetType") or data.get("blueprintSubclass"),
    )


def list_assets_impl(
    assets_root: Path,
    class_filter: str | None,
    path_prefix: str | None,
    head_limit: int,
) -> list[dict[str, Any]]:
    head = max(1, min(int(head_limit), MAX_LIST_HEAD))
    results: list[dict[str, Any]] = []
    for meta in _iter_meta_files(assets_root, path_prefix):
        asset_path, class_name = _classify(meta)
        if asset_path is None:
            continue
        if class_filter and class_name != class_filter:
            continue
        stem = meta.name[: -len(META_SUFFIX)]
        deep_md = meta.parent / f"{stem}{DEEP_SUFFIX}"
        results.append(
            {
                "path": asset_path,
                "className": class_name,
                "hasDeepDump": deep_md.is_file(),
            }
        )
        if len(results) >= head:
            break
    return results


def get_asset_summary_impl(inventory_root: Path, path: str) -> str:
    md = sidecar_path(inventory_root, path, ".md")
    if not md.is_file():
        return f"[not found] {md}"
    return md.read_text(encoding="utf-8")


def get_asset_deep_dump_impl(inventory_root: Path, path: str) -> str:
    deep = sidecar_path(inventory_root, path, DEEP_SUFFIX)
    if not deep.is_file():
        return f"[not found] {deep}"
    return deep.read_text(encoding="utf-8")


def search_deep_dumps_impl(
    assets_root: Path,
    pattern: str,
    class_filter: str | None,
    head_limit: int,
) -> list[dict[str, Any]]:
    try:
        rx = re.compile(pattern)
    except re.error as exc:
        return [{"error": f"invalid regex: {exc}"}]
    head = max(1, min(int(head_limit), MAX_SEARCH_HEAD))
    results: list[dict[str, Any]] = []
    for deep_md in assets_root.rglob(f"*{DEEP_SUFFIX}"):
        if class_filter is not None:
            stem = deep_md.name[: -len(DEEP_SUFFIX)]
            meta = deep_md.parent / f"{stem}{META_SUFFIX}"
            _, class_name = _classify(meta) if meta.is_file() else (None, None)
            if class_name != class_filter:
                continue
        try:
            with deep_md.open("r", encoding="utf-8", errors="replace") as f:
                for line_no, line in enumerate(f, start=1):
                    if rx.search(line):
                        results.append(
                            {
                                "path": asset_path_from_sidecar(
                                    assets_root, deep_md, DEEP_SUFFIX
                                ),
                                "lineNo": line_no,
                                "match": line.rstrip("\n"),
                            }
                        )
                        if len(results) >= head:
                            return results
        except OSError:
            continue
    return results


def _strip_generated_class_suffix(p: str) -> str:
    """`/Game/X/Foo.Foo_C` -> `/Game/X/Foo`. Leaves other paths untouched."""
    last_slash = p.rfind("/")
    stem = p[last_slash + 1 :] if last_slash >= 0 else p
    if "." in stem:
        base, _, after = stem.partition(".")
        # BP generated-class suffix looks like `Foo.Foo_C`; drop it.
        if after.endswith("_C") and after[: -len("_C")] == base:
            prefix = p[: last_slash + 1] if last_slash >= 0 else ""
            return prefix + base
    return p


def get_asset_meta_impl(inventory_root: Path, path: str) -> dict[str, Any]:
    meta = sidecar_path(inventory_root, path, META_SUFFIX)
    if not meta.is_file():
        return {"error": "not found", "path": str(meta)}
    try:
        with meta.open("r", encoding="utf-8") as f:
            return json.load(f)
    except (OSError, json.JSONDecodeError) as exc:
        return {"error": f"parse failure: {exc}", "path": str(meta)}


def get_cdo_properties_impl(inventory_root: Path, path: str) -> dict[str, Any]:
    meta = sidecar_path(inventory_root, path, META_SUFFIX)
    if not meta.is_file():
        return {"error": "not found", "path": str(meta)}
    try:
        with meta.open("r", encoding="utf-8") as f:
            data = json.load(f)
    except (OSError, json.JSONDecodeError) as exc:
        return {"error": f"parse failure: {exc}", "path": str(meta)}
    return {
        "path": data.get("assetPath", path),
        "assetType": data.get("assetType"),
        "dataCarrierKind": data.get("dataCarrierKind"),
        "cdoProperties": data.get("cdoProperties", []),
    }


_REF_SECTION_RE = re.compile(r"^##\s+`([^`]+)`\s*$")
_REF_HEADER_RE = re.compile(r"^-\s+(Hard refs out|Soft refs out|Hard refs in)\s+\((\d+)\):\s*$")
_REF_BULLET_RE = re.compile(r"^\s{2,}-\s+`([^`]+)`(?:\s+\[(\w+)\])?\s*$")
_REF_NONE_RE = re.compile(r"^\s{2,}-\s+_none_\s*$")


def _strip_asset_suffix(asset_path: str) -> str:
    """Drop a trailing `.AssetName` subpath on a UE asset path.

    `/Game/X/Foo.Foo` -> `/Game/X/Foo`. Keeps the leading slash intact.
    """
    last_slash = asset_path.rfind("/")
    stem = asset_path[last_slash + 1 :] if last_slash >= 0 else asset_path
    if "." in stem:
        stem = stem.split(".", 1)[0]
        prefix = asset_path[: last_slash + 1] if last_slash >= 0 else ""
        return prefix + stem
    return asset_path


def get_references_impl(
    inventory_root: Path, path: str, direction: str
) -> dict[str, Any]:
    direction = (direction or "both").lower()
    if direction not in {"out", "in", "both"}:
        return {
            "error": f"invalid direction {direction!r}; expected 'out', 'in', or 'both'"
        }
    graph_path = inventory_root / "DEPENDENCY_GRAPH.md"
    if not graph_path.is_file():
        return {"error": "DEPENDENCY_GRAPH.md not found", "path": str(graph_path)}

    target = _strip_asset_suffix(path if path.startswith("/") else "/" + path)
    result: dict[str, Any] = {
        "path": target,
        "hardRefsOut": [],
        "softRefsOut": [],
        "hardRefsIn": [],
    }
    found = False
    current_bucket: list[dict[str, str]] | None = None

    with graph_path.open("r", encoding="utf-8", errors="replace") as f:
        in_section = False
        for line in f:
            m_section = _REF_SECTION_RE.match(line)
            if m_section:
                if in_section:
                    # We just exited the target section.
                    break
                if _strip_asset_suffix(m_section.group(1)) == target:
                    in_section = True
                    found = True
                continue
            if not in_section:
                continue

            m_header = _REF_HEADER_RE.match(line)
            if m_header:
                bucket_name = m_header.group(1)
                if bucket_name == "Hard refs out":
                    current_bucket = result["hardRefsOut"]
                elif bucket_name == "Soft refs out":
                    current_bucket = result["softRefsOut"]
                elif bucket_name == "Hard refs in":
                    current_bucket = result["hardRefsIn"]
                continue

            if current_bucket is None:
                continue
            m_bullet = _REF_BULLET_RE.match(line)
            if m_bullet:
                current_bucket.append(
                    {"target": m_bullet.group(1), "kind": m_bullet.group(2) or ""}
                )
                continue
            if _REF_NONE_RE.match(line):
                continue

    if not found:
        return {"error": "not indexed", "path": target}

    if direction == "out":
        result.pop("hardRefsIn", None)
    elif direction == "in":
        result.pop("hardRefsOut", None)
        result.pop("softRefsOut", None)
    return result


_CLASS_TREE_NATIVE_HEADER_RE = re.compile(r"^##\s+By native parent\s*$")
_CLASS_TREE_BP_HEADER_RE = re.compile(r"^##\s+Blueprint .* Blueprint chains\s*$")
_CLASS_TREE_NATIVE_GROUP_RE = re.compile(r"^-\s+`([^`]+)`\s+\[(\d+)\]\s*$")
_CLASS_TREE_NATIVE_CHILD_RE = re.compile(r"^\s{2,}-\s+`([^`]+)`\s*$")
_CLASS_TREE_BP_ROW_RE = re.compile(r"^-\s+`([^`]+)`\s+<\s+`([^`]*)`\s*$")


def get_class_tree_impl(inventory_root: Path, class_name: str) -> dict[str, Any]:
    tree_path = inventory_root / "CLASS_TREE.md"
    if not tree_path.is_file():
        return {"error": "CLASS_TREE.md not found", "path": str(tree_path)}

    target = class_name if class_name.startswith("/") else "/" + class_name
    target_base = _strip_generated_class_suffix(_strip_asset_suffix(target))

    native_children: list[str] = []
    bp_children: list[str] = []
    kind: str | None = None

    section = None  # "native" | "bp"
    in_matching_native_group = False

    with tree_path.open("r", encoding="utf-8", errors="replace") as f:
        for line in f:
            if _CLASS_TREE_NATIVE_HEADER_RE.match(line):
                section = "native"
                in_matching_native_group = False
                continue
            if _CLASS_TREE_BP_HEADER_RE.match(line):
                section = "bp"
                in_matching_native_group = False
                continue
            if section == "native":
                m_group = _CLASS_TREE_NATIVE_GROUP_RE.match(line)
                if m_group:
                    in_matching_native_group = m_group.group(1) == target
                    if in_matching_native_group and kind is None:
                        kind = "native"
                    continue
                if in_matching_native_group:
                    m_child = _CLASS_TREE_NATIVE_CHILD_RE.match(line)
                    if m_child:
                        native_children.append(m_child.group(1))
            elif section == "bp":
                m_row = _CLASS_TREE_BP_ROW_RE.match(line)
                if m_row:
                    child, parent = m_row.group(1), m_row.group(2)
                    parent_base = _strip_generated_class_suffix(
                        _strip_asset_suffix(parent)
                    ) if parent else ""
                    if parent_base and parent_base == target_base:
                        bp_children.append(child)
                        if kind is None:
                            kind = "blueprint"

    if not native_children and not bp_children:
        return {"error": "not indexed", "className": class_name}
    return {
        "className": target,
        "kind": kind or "blueprint",
        "directChildren": sorted(native_children + bp_children),
        "count": len(native_children) + len(bp_children),
    }


def register(mcp: FastMCP, config: Config) -> None:
    inventory_root = config.inventory_root
    assets_root = inventory_root / "Assets"

    @mcp.tool
    def list_assets(
        class_filter: str | None = None,
        path_prefix: str | None = None,
        head_limit: int = DEFAULT_LIST_HEAD,
    ) -> list[dict[str, Any]]:
        """List assets in the pre-indexed inventory.

        Walks Assets/**/*.meta.json and returns a flat list. Cheap: each
        sidecar is a small JSON file and no UE process is involved.

        Args:
            class_filter: Optional class name, e.g. "Blueprint", "StateTree",
                "BehaviorTree", "ChooserTable", "DataTable", "AnimBlueprint",
                "WidgetBlueprint", "SmartObjectDefinition", "UserDefinedStruct",
                "UserDefinedEnum". Case-sensitive; matches the meta sidecar's
                `assetType` field (the same label used in INDEX.md's
                "Counts by Blueprint subclass" table).
            path_prefix: Optional UE path prefix (leading slash optional).
                E.g. "/Game/CombatPrototype", "Game/Blueprints/AI".
            head_limit: Max rows returned. Clamped to [1, 1000]; default 100.

        Returns:
            List of {"path", "className", "hasDeepDump"} records.
        """
        return list_assets_impl(assets_root, class_filter, path_prefix, head_limit)

    @mcp.tool
    def get_asset_summary(path: str) -> str:
        """Read the Tier 1 `.md` summary for an asset.

        The `.md` contains the single-page overview: class, parent, variables,
        functions, components, interfaces, brief coverage. Typically a few KB.

        Args:
            path: UE asset path. Any of these forms work:
                "/Game/Blueprints/BP_GameInstance"
                "/Game/Blueprints/BP_GameInstance.BP_GameInstance"
                "Game/Blueprints/BP_GameInstance"

        Returns:
            File contents, or `[not found] <path>` if the sidecar is missing.
        """
        return get_asset_summary_impl(inventory_root, path)

    @mcp.tool
    def get_asset_deep_dump(path: str) -> str:
        """Read the Tier 2 `.deep.md` for an asset.

        Contains full per-node / per-component detail: graph node pin tables,
        component property trees (including recursive instanced-subobject
        walks from M9), StateTree per-task instance data, BehaviorTree node
        tables, DataTable rows, Chooser decision tables, etc. For classes
        the deep-dump renderer does not cover, the file may still exist with
        a short "out of scope" notice.

        Args:
            path: UE asset path (same forms as `get_asset_summary`).

        Returns:
            File contents, or `[not found] <path>` if absent.
        """
        return get_asset_deep_dump_impl(inventory_root, path)

    @mcp.tool
    def search_deep_dumps(
        pattern: str,
        class_filter: str | None = None,
        head_limit: int = DEFAULT_SEARCH_HEAD,
    ) -> list[dict[str, Any]]:
        """Regex search across every `.deep.md` in the inventory.

        Analogous to `rg <pattern> <inventory>/Assets/**/*.deep.md`. Iterates
        line-by-line; returns the first N matches across the tree.

        Args:
            pattern: Python regular expression (re.search semantics).
            class_filter: Optional class name. When set, skips deep dumps
                whose companion `.meta.json` doesn't match.
            head_limit: Max results. Clamped to [1, 500]; default 50.

        Returns:
            List of {"path", "lineNo", "match"} records, where `path` is the
            UE asset path and `match` is the literal line (newline stripped).
            On invalid regex, returns a single {"error": ...} record.
        """
        return search_deep_dumps_impl(assets_root, pattern, class_filter, head_limit)

    @mcp.tool
    def get_asset_meta(path: str) -> dict[str, Any]:
        """Read the structured `.meta.json` sidecar for an asset.

        Returns the full JSON as a dict — every field the ProjectInventory
        commandlet emitted: `assetPath`, `assetType`, `blueprintSubclass`,
        `parentClass`, `variables`, `functions`, `components`,
        `cdoProperties`, `dataCarrierKind`, `dependencies`, `coverage`, etc.

        Args:
            path: UE asset path (any of the three forms accepted elsewhere).

        Returns:
            The parsed dict, or `{"error": ..., "path": <resolved path>}` on
            missing / unparseable sidecar.
        """
        return get_asset_meta_impl(inventory_root, path)

    @mcp.tool
    def get_cdo_properties(path: str) -> dict[str, Any]:
        """Projection of `.meta.json`'s `cdoProperties` array plus data-carrier kind.

        Faster than `get_asset_meta` when you only want the authored CDO
        overrides of a data-carrier Blueprint (GameplayEffect modifiers,
        GameplayAbility cost / cooldown / tags, DataAsset payload fields,
        ACharacter's natively-declared Instanced components, etc.). Empty
        `cdoProperties` is load-bearing — for GameplayEffect / GameplayAbility
        it signals an under-covered data-carrier per HEALTH_REPORT.

        Args:
            path: UE asset path of a Blueprint (or anything with a
                `.meta.json` sidecar).

        Returns:
            `{path, assetType, dataCarrierKind, cdoProperties: [...]}`, or
            `{"error": ..., "path": ...}` on missing sidecar. Each
            `cdoProperties` entry has `{propertyName, propertyType, value}`
            at minimum and may carry instanced-subobject sub-trees on
            EditInlineNew fields.
        """
        return get_cdo_properties_impl(inventory_root, path)

    @mcp.tool
    def get_references(path: str, direction: str = "both") -> dict[str, Any]:
        """Hard/soft refs in and out of an asset, parsed from `DEPENDENCY_GRAPH.md`.

        Mirrors the rollup: the asset appears once as a `## <path>` section
        with three sub-lists (`Hard refs out`, `Soft refs out`, `Hard refs in`).
        Each reference is tagged with its kind — `native` (Script module),
        `asset` (in-tree UE asset), or empty (unresolved / in-tree by default).

        Args:
            path: UE asset path (any of the three forms).
            direction: "out" (outbound refs only), "in" (inbound refs only),
                or "both" (default).

        Returns:
            Depending on direction, a dict with some or all of:
              `{path, hardRefsOut, softRefsOut, hardRefsIn}`
            where each list holds `{target, kind}` records. On miss:
            `{"error": "not indexed", "path": <normalised>}`.
        """
        return get_references_impl(inventory_root, path, direction)

    @mcp.tool
    def get_class_tree(class_name: str) -> dict[str, Any]:
        """Subtree of `CLASS_TREE.md` for a class — direct children only.

        Accepts either a native class path (`/Script/AIModule.AIController`)
        or a Blueprint path (`/Game/.../BP_AnimNotify_FoleyEvent`). Matches
        in both the "By native parent" section and the
        "Blueprint → Blueprint chains" section; the `.Xxx_C` generated-class
        suffix used in BP chains is normalised away automatically.

        Only direct children are returned. For a full transitive walk,
        call `get_class_tree` again on each child path.

        Args:
            class_name: Native path or Blueprint path of the parent class.

        Returns:
            `{className, kind, directChildren: [...], count}` with
            `kind ∈ {"native", "blueprint"}`. On miss:
            `{"error": "not indexed", "className": <input>}`.
        """
        return get_class_tree_impl(inventory_root, class_name)
