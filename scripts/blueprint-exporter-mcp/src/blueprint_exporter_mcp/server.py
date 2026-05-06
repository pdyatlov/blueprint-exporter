"""FastMCP server entry point.

Loads config from environment, registers tool modules, runs stdio transport.
"""
from __future__ import annotations

from fastmcp import FastMCP

from .config import Config
from .tools import gameplay_tags, live, plans, retrieval


mcp = FastMCP(
    name="blueprint-exporter",
    instructions=(
        "BlueprintExporter inventory access + M24 plan pipeline + live "
        "introspection. 8 zero-UE-process retrieval tools over the "
        "pre-indexed inventory (list_assets, get_asset_summary, "
        "get_asset_deep_dump, search_deep_dumps, get_asset_meta, "
        "get_cdo_properties, get_references, get_class_tree), 3 plan-"
        "pipeline tools (get_op_catalog zero-UE, validate_plan + "
        "apply_plan shell to UnrealEditor-Cmd.exe), and 2 live-"
        "introspection tools (deep_dump_asset, refresh_inventory) for "
        "on-demand re-scans when the inventory is stale. Use retrieval "
        "first; validate_plan before apply_plan.\n\n"
        "HARD RULE — never initiate a Perforce / P4 operation (checkout, "
        "submit, revert, etc.) without informing the user first and getting "
        "explicit approval. P4 ops are allowed when the user says yes; they "
        "are never allowed silently. Concrete risk worth calling out: "
        "`apply_plan` saves .uasset files via UE, and if the user has P4 "
        "configured (env vars, .p4config, or ini) the save can auto-checkout "
        "through UE's ISourceControlModule. Before calling `apply_plan` or "
        "any mutating tool on a project that may have Perforce active, "
        "tell the user what you're about to do, mention that saves may "
        "trigger source-control checkouts, and wait for their approval "
        "(the existing confirm=True gate on mutating tools is the mechanism). "
        "Questions about MCP behaviour go to Niclas."
    ),
)


def run() -> None:
    """uvx / console-script entry point."""
    config = Config.from_env()
    retrieval.register(mcp, config)
    plans.register(mcp, config)
    live.register(mcp, config)
    gameplay_tags.register(mcp, config)
    mcp.run()


if __name__ == "__main__":
    run()
