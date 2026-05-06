"""GameplayTag config-walking tool — zero UE process, M28.6.1.

Sibling of the M25.1 retrieval tools but reads from the project's
`Config/` directory rather than the pre-indexed inventory tree. UE's
gameplay-tag system stores authored tags in `*.ini` files using the
`+GameplayTagList=(Tag="...",DevComment="...")` array-syntax inside a
`[/Script/GameplayTags.GameplayTagsSettings]` (or
`[/Script/GameplayTags.GameplayTagsList]`) section.

M28.6.1 ships one tool:

    list_gameplay_tags(project_root=None)
        Walks the configured project root for tag-bearing inis and
        returns a structured listing of every tag the project authors
        from config — across the main DefaultGameplayTags.ini, any
        per-source files under Config/Tags/, and any plugin-contributed
        Config/Tags/ files under Plugins/*/Config/Tags/.

Out of scope (deliberate, per M28.6.0 research):
    - Native gameplay tags registered from C++ via `AddNativeGameplayTag`.
      These live in compiled binaries, not on disk; enumerating them
      requires a UE process. Consider a future `live_list_gameplay_tags`
      tool when a driver surfaces.
    - Engine-side tags (e.g. `Engine/Plugins/.../Config/Tags/*.ini`).
      Project-rooted walk only — the editor tag tree includes engine
      tags too but the MCP tool stays project-scoped to keep latency
      low and the result list focused on author-controlled state.
"""
from __future__ import annotations

import re
from pathlib import Path
from typing import Any

from fastmcp import FastMCP

from ..config import Config


# [+]GameplayTagList=(Tag="...",DevComment="...")
# [+]RestrictedGameplayTagList=(Tag="...",DevComment="...",AllowNonRestrictedChildren=...)
# DevComment is optional in the engine's parser but written by the editor
# always. The leading `+` is UE's array-append prefix — required for
# DefaultGameplayTags.ini (UGameplayTagsSettings array-accumulation across
# config layers) but omitted by the editor for per-domain Config/Tags/<X>.ini
# (each file is its own UGameplayTagsList instance, no accumulation).
_TAG_LINE_RE = re.compile(
    r'^\+?(?P<list>(?:Restricted)?GameplayTagList)='
    r'\((?:.*?)Tag\s*=\s*"(?P<tag>[^"]+)"'
    r'(?:.*?DevComment\s*=\s*"(?P<comment>[^"]*)")?',
    re.IGNORECASE,
)

# [+]GameplayTagRedirects=(OldTagName="...",NewTagName="...")
_REDIRECT_LINE_RE = re.compile(
    r'^\+?GameplayTagRedirects='
    r'\(\s*OldTagName\s*=\s*"(?P<old>[^"]+)"\s*,'
    r'\s*NewTagName\s*=\s*"(?P<new>[^"]+)"',
    re.IGNORECASE,
)


def _resolve_project_root(config: Config, project_root: str | None) -> Path | None:
    """Pick the project root: explicit arg → config.project_root → uproject parent.

    Returns None when nothing resolves — caller surfaces a structured
    error rather than crashing.
    """
    if project_root:
        return Path(project_root).expanduser().resolve()
    if config.project_root is not None:
        return config.project_root
    if config.uproject is not None:
        return config.uproject.parent
    return None


def _parse_ini_for_tags(
    ini_path: Path, source_label: str
) -> tuple[list[dict[str, Any]], list[dict[str, Any]]]:
    """Walk an ini file's lines, extract +GameplayTagList= + +GameplayTagRedirects=.

    Returns ``(tags, redirects)``. Each tag is
    ``{name, comment, source, restricted}``; each redirect is
    ``{old_name, new_name, source}``. Engine config syntax allows either
    case for the section header and forward-slash escaping for embedded
    quotes — this parser handles the common cases (the engine's parser is
    significantly more permissive but the dominant convention is the
    quoted form we match here).
    """
    tags: list[dict[str, Any]] = []
    redirects: list[dict[str, Any]] = []
    try:
        text = ini_path.read_text(encoding="utf-8")
    except (OSError, UnicodeDecodeError):
        return tags, redirects

    for raw_line in text.splitlines():
        line = raw_line.strip()
        # Comment lines (`;METADATA=...` is one) and blanks short-circuit.
        if not line or line.startswith(";") or line.startswith("#"):
            continue
        m = _TAG_LINE_RE.match(line)
        if m is not None:
            tags.append(
                {
                    "name": m.group("tag"),
                    "comment": m.group("comment") or "",
                    "source": source_label,
                    "restricted": m.group("list").lower().startswith("restricted"),
                }
            )
            continue
        rm = _REDIRECT_LINE_RE.match(line)
        if rm is not None:
            redirects.append(
                {
                    "old_name": rm.group("old"),
                    "new_name": rm.group("new"),
                    "source": source_label,
                }
            )
    return tags, redirects


def _iter_source_inis(project_root: Path) -> list[tuple[Path, str]]:
    """Enumerate every tag-config ini reachable under the project root.

    Returns a list of ``(path, source_label)`` tuples. ``source_label`` is
    the short identifier the engine's `IGameplayTagsEditorModule` would
    use for that source — useful when a downstream caller wants to feed
    the result into a follow-up `add_gameplay_tag(source_ini=...)` call.

    Walked locations (per M28.6.0 research, validated against DOW's
    `D:/Work/UE_DOW/game/Config/`):

      1. ``<project>/Config/DefaultGameplayTags.ini`` — engine maps this
         to the `DefaultGameplayTags.ini` source (`UGameplayTagsSettings`
         pre-registered). The single most-common authoring surface.
      2. ``<project>/Config/Tags/*.ini`` — per-source inis. Engine maps
         each to a `UGameplayTagsList` source registered under the file's
         basename. Created by the editor on first add when the caller
         passes a non-default ``source_ini`` to ``add_gameplay_tag``.
      3. ``<project>/Plugins/<Plugin>/Config/Tags/*.ini`` — plugin-
         contributed sources. Same `UGameplayTagsList` pattern, scoped
         to the plugin's directory. UE_DOW has plugins; some may
         contribute tag inis. Walked once per project-rooted plugin.

    Engine native tags (registered from C++ via `AddNativeGameplayTag`)
    are NOT walkable — they live in compiled binaries. Engine-bundled
    inis under ``<UE>/Engine/Config/`` are also out of scope; the MCP
    tool stays project-rooted.
    """
    sources: list[tuple[Path, str]] = []

    # 1. Default project ini.
    default_ini = project_root / "Config" / "DefaultGameplayTags.ini"
    if default_ini.is_file():
        sources.append((default_ini, "DefaultGameplayTags.ini"))

    # 2. Project per-source files.
    project_tags_dir = project_root / "Config" / "Tags"
    if project_tags_dir.is_dir():
        for ini in sorted(project_tags_dir.glob("*.ini")):
            sources.append((ini, ini.name))

    # 3. Plugin-contributed files.
    plugins_root = project_root / "Plugins"
    if plugins_root.is_dir():
        for plugin_dir in sorted(plugins_root.iterdir()):
            if not plugin_dir.is_dir():
                continue
            plugin_tags_dir = plugin_dir / "Config" / "Tags"
            if not plugin_tags_dir.is_dir():
                continue
            for ini in sorted(plugin_tags_dir.glob("*.ini")):
                # Source label includes the plugin name so callers can
                # distinguish project-rooted Config/Tags/Foo.ini from
                # Plugins/Bar/Config/Tags/Foo.ini even when the basename
                # collides.
                sources.append((ini, f"{plugin_dir.name}/{ini.name}"))

    return sources


def list_gameplay_tags_impl(
    config: Config, project_root: str | None
) -> dict[str, Any]:
    """Pure implementation — used by both the MCP tool wrapper and tests."""
    root = _resolve_project_root(config, project_root)
    if root is None:
        return {
            "error": (
                "project_root could not be resolved. Pass an explicit "
                "project_root, or set BPX_PROJECT_ROOT or BPX_UPROJECT in the "
                "environment."
            ),
            "tags": [],
            "redirects": [],
            "sources": [],
        }
    if not root.is_dir():
        return {
            "error": f"project_root is not a directory: {root}",
            "tags": [],
            "redirects": [],
            "sources": [],
        }

    sources_summary: list[dict[str, Any]] = []
    all_tags: list[dict[str, Any]] = []
    all_redirects: list[dict[str, Any]] = []
    seen_tag_names: set[tuple[str, str]] = set()

    for ini_path, source_label in _iter_source_inis(root):
        tags, redirects = _parse_ini_for_tags(ini_path, source_label)
        sources_summary.append(
            {
                "name": source_label,
                "path": str(ini_path),
                "exists": True,
                "tag_count": len(tags),
                "redirect_count": len(redirects),
            }
        )
        for t in tags:
            key = (t["name"], t["source"])
            if key in seen_tag_names:
                continue
            seen_tag_names.add(key)
            all_tags.append(t)
        all_redirects.extend(redirects)

    # Alpha-sort tags by (source, name) for deterministic output — matches
    # the engine's on-disk SortTags() guarantee within a source, and groups
    # by source for human readability.
    all_tags.sort(key=lambda t: (t["source"], t["name"]))
    all_redirects.sort(key=lambda r: (r["source"], r["old_name"]))

    return {
        "project_root": str(root),
        "tags": all_tags,
        "redirects": all_redirects,
        "sources": sources_summary,
    }


def register(mcp: FastMCP, config: Config) -> None:
    @mcp.tool
    def list_gameplay_tags(project_root: str | None = None) -> dict[str, Any]:
        """List every gameplay tag authored in project ini config files.

        Walks the project's ``Config/DefaultGameplayTags.ini`` plus any
        ``Config/Tags/*.ini`` (project-rooted) and
        ``Plugins/*/Config/Tags/*.ini`` (plugin-contributed) files.
        Zero UE process — pure ini-text parsing. M28.6.1 sibling of
        ``add_gameplay_tag`` (write side, plan op).

        Args:
            project_root: Optional explicit project directory. When omitted,
                resolves from ``BPX_PROJECT_ROOT`` env var, falling back
                to the parent directory of ``BPX_UPROJECT``.

        Returns:
            A dict shaped:

                {
                    "project_root": "<resolved path>",
                    "tags": [
                        {"name", "comment", "source", "restricted"},
                        ...
                    ],
                    "redirects": [
                        {"old_name", "new_name", "source"},
                        ...
                    ],
                    "sources": [
                        {"name", "path", "exists", "tag_count", "redirect_count"},
                        ...
                    ],
                }

            On unresolvable project root, returns the same shape with an
            ``"error"`` key and empty lists.

        Out of scope (M28.6.0 research):
            - **Native tags** registered from C++ via
              ``AddNativeGameplayTag``. They live in compiled binaries
              and require a UE process to enumerate; this MCP tool is
              zero-process by design. A future ``live_list_gameplay_tags``
              would cover them when a driver surfaces.
            - **Engine-bundled** tag inis under ``<UE>/Engine/Config/``.
              Project-rooted walk only.
        """
        return list_gameplay_tags_impl(config, project_root)
