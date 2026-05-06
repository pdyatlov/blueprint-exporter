# blueprint-exporter-mcp

MCP server that exposes BlueprintExporter's pre-indexed `ProjectInventory` output to MCP clients (Claude Code, Cursor, Claude Desktop).

Zero UE process — serves the `.md` / `.deep.md` / `.meta.json` sidecars written by the `-run=ProjectInventory` + `-run=AggregateInventory` commandlets. Later sub-slices add plan-pipeline tools that shell out to the M24 validator / executor scripts.

Scoped in `blueprint-exporter/WIP_INVENTORY.md` §11 (candidate #11 "M25 — MCP server + tactical AI ops").

## Status

**M25.1 complete** — 13 tools total (8 retrieval + 3 plan-pipeline + 2 live-introspection) with Claude Code / Cursor / Claude Desktop configuration documented.

### Retrieval (zero UE process)

| Tool | Purpose |
|---|---|
| `list_assets(class_filter, path_prefix, head_limit)` | Walk the inventory; returns `{path, className, hasDeepDump}` rows. |
| `get_asset_summary(path)` | Read the Tier 1 `.md`. |
| `get_asset_deep_dump(path)` | Read the Tier 2 `.deep.md` (or `[not found]` if absent). |
| `search_deep_dumps(pattern, class_filter, head_limit)` | Regex search across every `.deep.md`. |
| `get_asset_meta(path)` | Full parsed `.meta.json` dict (all fields). |
| `get_cdo_properties(path)` | Projection: `{path, assetType, dataCarrierKind, cdoProperties[]}`. |
| `get_references(path, direction)` | Hard/soft refs in+out from `DEPENDENCY_GRAPH.md`; direction ∈ `out` / `in` / `both`. |
| `get_class_tree(class_name)` | Direct children of a class from `CLASS_TREE.md`; accepts both native (`/Script/...`) and BP (`/Game/...`) forms. |

### Plan pipeline

| Tool | UE process? | Purpose |
|---|---|---|
| `get_op_catalog()` | no | AST-introspect `scripts/python_ops/` and return every op's name, module, docstring, and parameter schema. Auto-updates as new ops ship. |
| `validate_plan(plan_json)` | **bridge (sub-second) OR subprocess (2–5 min)** — read-only | M27.1+: if the UE editor is running with the plugin loaded, routes through the local WebSocket bridge and returns in sub-second. If the editor isn't up, falls back to shelling `UnrealEditor-Cmd.exe -run=pythonscript` (cold start). Returns `{report, transport: "bridge" \| "subprocess"}`. No mutations either way. |
| `apply_plan(plan_json, confirm, re_export)` | **bridge (sub-second) OR subprocess (2–5 min)** — MUTATES | Same transport story as `validate_plan` — bridge-first, subprocess-fallback. Runs `validate → execute → mechanical-diff → verification`. Atomic per op, not per plan. M27.3: when routed through the bridge AND `report.passed=true`, scopes a re-export of touched UBlueprint / StateTree assets and embeds a `reExport: {scopedPaths[], wroteFiles[], errorCount, perAsset[]}` block — agent loop no longer needs a manual `refresh_inventory` after in-scope edits. Set `re_export=False` to opt out. |

**Transport choice and latency:** These three tools (`validate_plan`, `apply_plan`, plus any future bridge-routed tool) prefer the editor bridge when it's reachable at `ws://127.0.0.1:<BPX_BRIDGE_PORT>` (default `1337`), falling back to subprocess shelling on connect-refused / handshake-timeout. The difference is material — a single `apply_plan` that takes 2–5 min cold-start takes well under a second when the editor is already running, and a plan-of-plans iteration (5 sequential ops) drops from 10–25 min to ~5 s total. The `transport` field on the response tells you which path ran. **Keep the editor open** whenever you're iterating; close it only for one-off CI / headless runs.

### Live introspection

| Tool | UE process? | Purpose |
|---|---|---|
| `deep_dump_asset(path)` | yes (read-only) | Shell to `-run=DeepDump -Asset=<path> -OutDir=<tempdir>` and return the generated Tier 2 Markdown. Use when the inventory is stale or missing. |
| `refresh_inventory(path_filter, deep_dump)` | yes (MUTATES inventory) | Shell to `-run=ProjectInventory -Filter=<prefix> [-DeepDump]`, writing into `BPX_INVENTORY_ROOT`. Filter is required on purpose — a full-project sweep can crash on third-party content that triggers engine assertions at load time. |

## Quick setup (first-time colleagues: start here)

Four steps, ~5 minutes. Assumes you already have a UE engine install, a `.uproject`, and a `ProjectInventory` tree produced by the `-run=ProjectInventory` + `-run=AggregateInventory` commandlets.

**1. Install the package into your Python (3.10+).** Editable install picks up future updates via `git pull`:

```bash
pip install -e <path-to-cloned-repo>/blueprint-exporter/scripts/blueprint-exporter-mcp
```

**2. Copy the config template and edit it:**

```bash
cp <path-to-cloned-repo>/blueprint-exporter/.mcp.json.example <path-to-cloned-repo>/.mcp.json
```

Open `.mcp.json` and replace each `<...>` placeholder with an absolute path on your machine. The three env vars you'll set are:

| Variable | What it points at |
|---|---|
| `BPX_INVENTORY_ROOT` | An inventory tree (contains `Assets/` + `INDEX.md`). Most of the 13 tools only need this. |
| `BPX_ENGINE_ROOT` | Your UE engine's `Engine/` directory. The server appends `Binaries/Win64/UnrealEditor-Cmd.exe` to find the headless binary. Needed for the 4 UE-spawning tools. |
| `BPX_UPROJECT` | The `.uproject` the plan pipeline should run against. Needed for the 4 UE-spawning tools. |

**Engine and uproject must match the same engine build** — a mismatch triggers a UE "BuildId mismatch" modal on first launch. If a project ships with a custom engine, point `BPX_ENGINE_ROOT` at that engine's checkout; if it uses a stock Epic Games build, point at the Epic install.

The `_comment` field at the top of `.mcp.json.example` is ignored by MCP clients; leave it or remove it.

**3. Run the doctor to validate:**

```bash
BPX_INVENTORY_ROOT=... BPX_ENGINE_ROOT=... BPX_UPROJECT=... bpx-mcp-doctor
```

Expect a green `all checks passed`. Any `[FAIL]` line names the exact env var / path to fix.

**4. Restart Claude Code:**

`.mcp.json` is read at session start — `/exit`, then `claude` again in the same repo root. Inside the new session, `/mcp` lists the server + 13 tools.

### Who owns what

- **Committed inventory trees in this repo are DevOps-owned.** The pipeline keeps them current on `main`; a fresh `git pull` gets you the blessed state. Don't `refresh_inventory` over a committed tree and then commit — DevOps controls the committed state.
- **Externally-delivered inventory trees** (i.e. anything not shipped in this repo) come from a separate DevOps-controlled channel. Ask your DevOps team where they land on your machine.
- **Local `refresh_inventory` / `deep_dump_asset` writes** are for your own experimentation; they mutate `BPX_INVENTORY_ROOT` on disk but those writes never go into a PR.

If multiple projects are in flight on your team, register multiple MCP server entries under different names (e.g. `blueprint-exporter-<projectA>` + `blueprint-exporter-<projectB>`), each with its own env bundle.

**Never mix** — pointing `BPX_INVENTORY_ROOT` at one project while `BPX_UPROJECT` points at another silently produces retrieval tools that see one asset set and plan-pipeline tools that run against another. The doctor's coherence heuristic catches common cases by looking for shared project identifiers in both paths; rely on that check plus deliberate naming of your server entries.

## Environment variables (reference)

Required for any tool:

| Variable | Purpose |
|---|---|
| `BPX_INVENTORY_ROOT` | Absolute path to a `ProjectInventory` directory (must contain `Assets/` + `INDEX.md`). |

Required only for `validate_plan` / `apply_plan` / `deep_dump_asset` / `refresh_inventory` (the four UE-spawning tools):

| Variable | Purpose |
|---|---|
| `BPX_ENGINE_ROOT` | Absolute path to a UE `Engine/` directory. Server derives `Binaries/Win64/UnrealEditor-Cmd.exe` from this. **Engine and uproject must target the same engine build** — mismatched builds trigger a UE "BuildId mismatch" modal on launch. |
| `BPX_UPROJECT` | Absolute path to the `.uproject` the plan pipeline should run against. |
| `BPX_SCRIPTS_ROOT` | Directory containing `run_plan.py`, `run_plan_validator.py`, and `python_ops/`. Auto-derived when unset, as long as the MCP package lives under `<scripts_root>/blueprint-exporter-mcp/`. |

Reserved (unused today):

| Variable | Purpose |
|---|---|
| `BPX_PROJECT_ROOT` | Project directory containing the `.uproject`. |

Retrieval-only setups (no plan authoring) can omit `BPX_ENGINE_ROOT` + `BPX_UPROJECT`; those are only touched when `validate_plan` / `apply_plan` / `deep_dump_asset` / `refresh_inventory` fire.

## MCP client config files

All three clients use the same `mcpServers.<name>.{command, args, env}` shape — only the file location differs. The template at `<repo>/blueprint-exporter/.mcp.json.example` is authored for Claude Code; the destination `.mcp.json` always lives at the **repo root** (that's where clients look) regardless of where the template ships from. Drop the same block into the other clients' files:

- **Claude Code:** `<repo>/.mcp.json` (per-repo) or `~/.claude.json` (global). Read at session start.
- **Cursor:** `<repo>/.cursor/mcp.json` (per-repo) or `~/.cursor/mcp.json` (global).
- **Claude Desktop:** `%APPDATA%\Claude\claude_desktop_config.json` (Windows) or `~/Library/Application Support/Claude/claude_desktop_config.json` (macOS). **Full app restart** required after editing — "reload" is not enough.

## House rules

**Inform and approve before any Perforce / P4 operation.** P4 checkouts, submits, reverts, etc. are fine when the user has explicitly approved them — but never silently. The concrete risk is `apply_plan` mutating a `.uasset`: `UPackage::SavePackage` routes through `ISourceControlModule` when the module is active, and an ambient Perforce configuration (`P4USER` / `P4CLIENT` / `P4PORT` env vars, `.p4config` in the project tree, or the editor's `SourceControlSettings.ini` `Provider=Perforce`) can trigger an auto-checkout on save without any explicit P4 flag being passed. Before calling `apply_plan` or `refresh_inventory`, tell the user what you're about to do, mention that saves may trigger source-control checkouts, and wait for their approval — the existing `confirm=True` gate on mutating tools is the mechanism. If the user wants to skip P4 on a specific run, they can configure `-SCCProvider=None` in their project's SourceControlSettings; the MCP does not force that setting either way.

**Questions about MCP behaviour go to Niclas.** Not a Slack channel, not a ticket queue — ask Niclas.

## Troubleshooting

| Symptom | Likely cause | Fix |
|---|---|---|
| `/mcp` shows the server as `failed` or missing tools | `python -m blueprint_exporter_mcp` crashed at startup (usually a bad env var) | Run `bpx-mcp-doctor` with the same env vars as `.mcp.json` — it prints the exact validation that failed. |
| Retrieval tools return `[not found]` for an asset you know exists | `BPX_INVENTORY_ROOT` and `BPX_UPROJECT` point at different projects | Realign both env vars to the same project, or run two server entries under different names (one per project). The doctor's coherence heuristic fires on common mismatch shapes. |
| `apply_plan` returns `{"error": "UnrealEditor-Cmd.exe not found under BPX_ENGINE_ROOT at ..."}` | `BPX_ENGINE_ROOT` points at a sibling directory (e.g. `Engine/Binaries/Win64`) instead of the `Engine/` root | Point at `<engine>/Engine/`, not a subfolder. The doctor flags this. |
| `apply_plan` opens a UE modal "BuildId mismatch" | Engine build doesn't match the uproject's expected build | Make sure `BPX_ENGINE_ROOT` points at the engine the uproject was authored against (custom-engine projects need the team's custom-engine checkout; stock-engine projects need the matching Epic Games install). |
| `apply_plan` succeeds but `report.exitCode == 2` | CLI misuse inside the plan harness (bad `-plan`, malformed JSON) | Rare — usually means the plan file didn't reach disk. Capture `stderrTail` + file a bug. |
| Tool call takes 30+ s then times out | UE editor cold-start on a slow disk or a locked uproject | Close any interactive UE editor that has the uproject open, then retry. Bump the op's timeout only as a last resort. |
| `bpx-mcp-doctor: command not found` | Package not installed into the Python on PATH | Re-run `pip install -e <path-to-cloned-repo>/blueprint-exporter/scripts/blueprint-exporter-mcp`. |

## Sanity-check the library code

Beyond the doctor (which checks config), run the unit smoke against any valid inventory to confirm tool bodies behave:

```bash
BPX_INVENTORY_ROOT=<path-to-a-ProjectInventory-tree> \
  python <path-to-cloned-repo>/blueprint-exporter/scripts/blueprint-exporter-mcp/tests/smoke_test.py
```

Expect `All smoke tests passed.` with 41+ green assertions. Every tool body is covered; `validate_plan` / `apply_plan` / `deep_dump_asset` / `refresh_inventory` test their argv assembly + config-error paths with synthetic inputs (no UE spawn). The doctor's inventory ↔ uproject coherence heuristic is exercised across four cases (aligned / aligned / mismatch / unset).

## Design notes

- **Asset-path normalisation** handles all three UE forms: `/Game/X/Y.Y`, `/Game/X/Y`, `Game/X/Y`. See `paths.normalize_asset_path`.
- **`class_filter`** matches the sidecar's `assetType` field verbatim — i.e. the same values `INDEX.md`'s "Counts by Blueprint subclass" table uses. `assetType` is populated for every in-scope class; `blueprintSubclass` is a BP-family-only legacy fallback.
- **`search_deep_dumps`** iterates line-by-line and bails at `head_limit`. For a 1522-file inventory this is still fast enough for interactive use; a later polish slice can add an on-disk index if needed.
- **Errors surface as data, not exceptions** — invalid regex returns `[{"error": "..."}]`; missing sidecars return `[not found] <resolved path>`. MCP clients get a human-readable reason instead of a protocol error.
