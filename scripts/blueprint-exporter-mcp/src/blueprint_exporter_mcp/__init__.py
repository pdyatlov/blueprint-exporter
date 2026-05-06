"""Blueprint Exporter MCP server.

Exposes the pre-indexed ProjectInventory (produced by
`-run=ProjectInventory` + `-run=AggregateInventory` commandlets) to MCP
clients so authoring loops can query asset summaries, deep dumps, and
cross-refs without spawning a fresh UE process per question.

See README.md and blueprint-exporter/WIP_INVENTORY.md §11 (M25 scope).
"""

__version__ = "0.1.0"
