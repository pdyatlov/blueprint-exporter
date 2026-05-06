# WIP: Project Inventory Subsystem

> History prior to today's restructure has moved to `WIP_INVENTORY_archive.md`.
> This file holds **current state, what's next, and durable reference material only.**

---

## Current state

**Date:** 2026-04-29.

**Latest ship:** **M28.15 — `get_op_catalog` `name_filter` substring param** at version **1.28.6** (2026-04-29, working-tree). Surfaced by the 2026-04-29 design.md MCP-only session against UE_DOW_Legacy: catalog response had grown to ~106 KB / ~26 K tokens at 63 ops × full docstrings + parameter schemas, crossed the MCP-client tool-result inlining limit, and the agent fell back to a stale local snapshot — misclassifying shipped M28.13 (`add_macro_instance_node`) and M28.14 (`add_make_struct_node` / `add_break_struct_node` / `add_set_fields_in_struct_node`) ops as "M28.14 candidate" and "blocked." Pure-MCP-server fix mirroring the M28.6.2 shape: single-file change in `scripts/blueprint-exporter-mcp/src/blueprint_exporter_mcp/tools/plans.py` adding optional `name_filter: str | None = None` param to `get_op_catalog_impl` + `register()`'s `@mcp.tool` shim. Case-insensitive substring match against op `name` (lowercase both sides); non-matching ops are skipped before their submodule is parsed (matters because per-op AST extraction reads the file from disk — the filter shortcuts both work and response size). Empty string / `None` / omitted = unfiltered (existing callers see no shape change). On a filtered call the response also carries `filter` (echoed input) and `total` (unfiltered op count) so the caller can tell how many ops are hidden; on an unfiltered call those bookkeeping fields are absent (preserves backward-compat with the existing `test_get_op_catalog` shape assertion). Tool-shim docstring updated to point at the inlining-limit motivation + recommend a substring like `"struct"` or `"add_macro"`. New regression test `test_get_op_catalog_name_filter` covers: substring narrows the catalog, full set vs filtered count consistency, case-insensitivity (`STRUCT` matches `struct`), empty/None treated as unfiltered, no-match returns `count=0` with bookkeeping intact. All 26 MCP smoke tests in scope PASS (3 pre-existing live-bridge failures `test_plan_tools_config_errors` / `test_plan_timeout_handler_returns_str_tails` / `test_partial_apply_surfaces_at_top_level` are caused by an unrelated `ModuleNotFoundError: No module named 'python_ops.plan_executor'` from the user's running editor's bridge — `sys.path` issue in the live editor process, surfaces only when bridge is reachable; my change does not touch those code paths). Patch bump (catalog-additive, no schema break). Full 9-site stamp sweep + BuiltPlugin mirror applied (19 grep hits clean at 1.28.6). Dual-engine DLL rebuild (DOW custom 26 s, stock UE 5.7 44 s, both `ExitCode=0`) + 3-location install (BuiltPlugin/ → DOW-target, BugHunt/ + UE_DOW_Legacy/ → stock-5.7) + `.uplugin` sync across all installs (BugHunt's was at 1.27.1, legacy was at 1.28.3 — both repaired). `verify_all -IncludeDow` PASS in 732 s. 12-commit chain (M28.10 → M28.15) rebased on origin/main + pushed; follow-up docs commit (`ac3443a5`) captures dual-engine ship-flow fixes + drift-detector extension to cover BugHunt + BuiltPlugin uplugins.

**Most recent feature milestone before M28.15:** **M28.14 — struct-mutation node catalog (`add_make_struct_node` / `add_break_struct_node` / `add_set_fields_in_struct_node`)** at version **1.28.5** (2026-04-28, working-tree). Three new bridge UFUNCTIONs on `UBpxReflectionOps` (`AddMakeStructNode` / `AddBreakStructNode` / `AddSetFieldsInStructNode`) sharing one templated `BpxReflection::PrepStructNodeSpawn<TNodeClass>` scaffold (validates BP / graph / struct, computes seeded NodeGuid + idempotence walk, NewObject + StructType + `bMadeAfterOverridePinRemoval = true` + AddNode + PostPlacedNewNode + AllocateDefaultPins). Make/Break each return after the shared scaffold + `SeedPinGuidsForNode`; SetFields adds a post-AllocateDefaultPins pass that walks `ShowPinForProperties`, flips `bShowPin = true` for each entry whose `PropertyName` is in the caller's `FieldsToShow`, then `ReconstructNode()` + `SeedPinGuidsForNode` (the SetFields pin manager defaults `bShowPin = false` for every field per `K2Node_SetFieldsInStruct.cpp:400`, so without this walk the node lands with no settable pins). `bMadeAfterOverridePinRemoval = true` matches the engine's editor spawn path at `EdGraphSchema_K2.cpp:7286` / `:7350`; without it the node is treated as legacy and surfaces phantom override-toggle pins. Pre-validation: `FieldsToShow` non-empty (else structured error — empty list = no settable pins, definitely a typo); every name resolves to a property on `StructType` via `TFieldIterator<FProperty>` walk (else structured error listing the unknown names; silent no-op on a typo would be a foot-gun where the user expects a settable pin and gets nothing). Determinism seeds: `md5(<bp>:graph:<g>:make_struct:<struct_path>:<x,y>)` / `:break_struct:` / `:set_fields_in_struct:<struct_path>:fields:<sorted_fields>:<x,y>` — sort-and-join the FieldsToShow set into the seed key so caller-side ordering doesn't drift the GUID. Three Python ops in `blueprint_graph_nodes.py` sharing a new `_resolve_script_struct(struct_type_path)` helper (mirrors the `add_dynamic_cast_node` class-resolution recipe — `unreal.load_object` since `ScriptStruct` is a UObject, not a UClass; `load_class` doesn't apply). `fields_to_show` accepted as a Python `list[str]`, marshalled to `unreal.Array(unreal.Name)` for the bridge call. Wire fans out the standard way: plan_shape (3 entries), mechanical_diff (3 names in the mutated-`bp_path` branch), plan_executor (3 dispatch entries), `__init__.py` (3 re-exports + 3 `__all__` entries), `smoke_test.py` catalog assertion (3 names), `CATALOG.md` (3 op sections + 1 ship-record block). Three new soak fixtures (`add_make_struct_node.json` / `add_break_struct_node.json` / `add_set_fields_in_struct_node.json`) against `BP_BpxTestGraphNodesCalls` using `/Script/CoreUObject.Vector` (engine-shipped, stable, X/Y/Z all `BlueprintVisible` non-`BlueprintReadOnly`); SetFields fixture passes `fields_to_show=["X","Y"]` to exercise the post-alloc bShowPin walk + sorted-fields seed key. All `skip_inspect=true` with `stable_keys=["node_guid"]` — deep-render struct ops surface inline as flat per-field pin tables that aren't grep-friendly, byte-identity is the load-bearing assertion. With M28.14 shipped, design.md's read-modify-write patterns inside the M28.13 ForEachLoop body — UAIActionScorer per-element score updates (item 2: iterate `KnownTargets`, decay each entry's score) and confidence-decay over `S_TargetInfo` arrays (item 3: per-tick scaling) — are end-to-end authorable from a plan; the loops can both iterate AND author the body. Patch bump (catalog-additive, no new subsystem). Full 9-site stamp sweep + dual-engine DLL rebuild (UE_DOW custom 28 s, stock UE 5.7 47 s, both `ExitCode=0`) + 3-location install (`BuiltPlugin/Binaries/Win64/`, `BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64/`, `D:\Work\UE_DOW_Legacy\Plugins\BlueprintExporter\Binaries\Win64\`).

**Most recent feature milestone before M28.14:** **M28.6.2 — `list_gameplay_tags` per-domain parser fix** at commit `2196052c` (2026-04-28, plugin 1.28.3 → 1.28.4). Pure-MCP-server fix surfaced by the 2026-04-27 design.md MCP-only session against UE_DOW_Legacy. Parser regex required the `+` array-append prefix that `Config/DefaultGameplayTags.ini` uses (since `UGameplayTagsSettings` accumulates across the config layer chain) but per-domain `Config/Tags/<X>.ini` files use plain `GameplayTagList=` (each backs a standalone `UGameplayTagsList` instance, no accumulation). Fix: relax `^\+(?P<list>...)=` to `^\+?(?P<list>...)=` for both regular + restricted list lines plus the redirects line. Single-file change in `scripts/blueprint-exporter-mcp/src/blueprint_exporter_mcp/tools/gameplay_tags.py` + new regression test `test_list_gameplay_tags_per_domain_no_plus_prefix` in `tests/smoke_test.py`. End-to-end against UE_DOW_Legacy AI.ini now reports `tag_count: 4` (and DefaultGameplayTags.ini still parses 49 tags + 3 redirects).

**Most recent feature milestone before M28.6.2:** **M28.13 — `K2Node_MacroInstance` authoring (loop unblocker)** at commit `0fd43cd9` (2026-04-28, plugin 1.28.2 → 1.28.3). One new bridge UFUNCTION `UBpxReflectionOps::AddMacroInstanceNode(BP, GraphName, MacroGraph, Position)` unblocks five design.md sections stuck on "iterates X → blocked" because ForEachLoop is a macro instance, not an atomic K2Node. Pre-`AllocateDefaultPins` `MacroGraphReference.SetGraph(MacroGraph)` so the inherited `UK2Node_Tunnel::AllocateDefaultPins` pin-mirror walk has the macro to iterate. NodeGuid seeded `md5(<bp>:graph:<g>:macro:<macro_lib_path>:<x>,<y>)`; pin IDs reseeded AFTER alloc. One Python op `add_macro_instance_node` accepting `"<lib_uobject_path>:<macro_name>"`. With M28.13 + M28.14 shipped, the design.md feasibility table goes from 5 "❌ iterates → blocked" entries to 5 "✅ achievable via add_macro_instance_node + struct-mutation catalog + connect_graph_pins" entries.

**Working-tree state:** M28.15 fully shipped: source + tests + 9-site version stamp sweep to 1.28.6 + BuiltPlugin source mirror, both DLLs rebuilt (DOW custom 26 s, stock UE 5.7 44 s, both `ExitCode=0`), 3-location install refreshed (BuiltPlugin/ → DOW-target, BugHunt/ + UE_DOW_Legacy/ → stock-5.7), `.uplugin` manifests synced across all three installs, `verify_all.ps1 -IncludeDow` PASS in 732 s (55+ gates: automation × 2 engines, determinism × 2 engines, inspect × 21 ops, soak × 35 ops, tag-author parity). 12-commit chain (M28.10 → M28.15) rebased on origin/main and pushed.

**Open follow-ups for next session:** one item remains from the 2026-04-27 design.md MCP-only session against UE_DOW_Legacy (items A + C closed by 2026-04-28 ships M28.6.2 and M28.14 respectively). See **Open follow-ups from 2026-04-27 design.md MCP-only session** below. TL;DR pickup priority:

1. **M28.12.1** — `add_function_override("ReceiveBeginPlay")` body-add failure on `BP_EnemyBase_AIController`. Potential M28.12 regression. **Cannot fix without repro from the other session** — request the failing plan JSON + run_plan report + UE log block before opening a fix. Workaround documented: author the body manually in the editor for that one graph; doesn't block a design.md drive end-to-end.

If no design.md regression surfaces and M28.12.1 stays unrepro'd, the next pickup is open — see the **Candidate next milestones** section below for the genuine backlog (item 0 M19.2.2 DataAsset sweep, item 4 UDS field-name GUID stripping, item 5 recursive struct breakout at Tier 2, item 6 `verify_determinism.ps1` CI wiring, item 2 M20 Level export — biggest capability gap remaining).

**Most recent feature milestone before M28.10.1:** M28.6.1 at commit `8df3b1b0` (2026-04-25, plugin 1.26.0 → 1.27.0) — `add_gameplay_tag` Python op + `AddGameplayTag` UFUNCTION on `UBpxReflectionOps` + `list_gameplay_tags` zero-UE-process MCP tool, walking `Config/DefaultGameplayTags.ini` + `Config/Tags/*.ini` + `Plugins/*/Config/Tags/*.ini`. Closes the M28.6 GameplayTag config-authoring catalog.

**Branch state:** `main`, in sync with `origin/main`. The M28.10 → M28.15 ship chain (12 commits) was rebased on top of 3 remote commits (2 CI inventory updates + 1 README revision) and pushed clean as of 2026-04-29. Top of `origin/main`: `9dad56a4` (M28.15 dual-engine DLL rebuild + 3-location install at 1.28.6).

---

## Resume checklist (do these in order on a fresh /clear)

1. `git log --oneline -20` — confirm the most recent commits. Expected top of history (branch `main`): the M28.14 ship commit (1.28.4 → 1.28.5 struct-mutation catalog), `88c155e8` (docs re-prioritize M28.14 as next pickup), `4540f5df` (docs WIP TL;DR refresh post-M28.6.2), `2196052c` (M28.6.2 fix — list_gameplay_tags per-domain parser + 1.28.4), `0fd43cd9` (M28.13 K2Node_MacroInstance authoring + 1.28.3), `ef4d5aef` (M28.12 native virtual override authoring + 1.28.2), `022de81c` (M28.11 typed function/event param authoring + 1.28.1), `710bab73` (M28.10 create_blueprint_class + 1.28.0). For older SHA narratives, see `WIP_INVENTORY_archive.md`.

2. Read `PROJECT_INVENTORY_BRIEF.md` §6 / §11A if picking up M5/M6 stretch work (DeepDumpCommandlet + determinism CI gate).

3. Re-read the **Candidate next milestones** section below — it's concrete and ordered.

4. Before writing code, sanity-check the toolchain is still good. **Authoritative gate (M28.pre.4):**
    ```
    pwsh -File blueprint-exporter/scripts/verify_all.ps1
    ```
    Self-contained; runs automation + determinism + inspect + soak across every shipped op against BugHunt / stock-5.7. ~134 s. Exits 0 iff all gates PASS. No prior `ProjectInventory/` tree required (the determinism gate generates and cleans up its own scratch trees). For C++ patches reaching `BpxReflectionOps`, add `-IncludeDow` to fan out against the custom UE_DOW engine too.

    **Legacy AggregateInventory quick check (optional, superseded).** The pre-M28.pre.4 sanity-check was an `AggregateInventory` commandlet run — kept as a pointer in case `verify_all.ps1` is unavailable, but **requires a prior Phase-1 `ProjectInventory` run to have populated `<OutDir>/Assets/**/.meta.json`; on a fresh tree the output dir does not exist and the command returns nothing useful**. If you genuinely need it, run it against the stock-5.7 engine (matching `BugHunt.uproject`'s `EngineAssociation` + the installed DLL's BuildId) rather than UE_DOW:
    ```
    "C:/Program Files/Epic Games/UE_5.7/Engine/Binaries/Win64/UnrealEditor-Cmd.exe" \
      "D:\Work\blueprintexporter\blueprint-exporter\BugHunt\TestProject\BugHunt.uproject" \
      -run=AggregateInventory \
      -OutDir="D:\Work\blueprintexporter\blueprint-exporter\ProjectInventory" \
      -nullrhi -unattended -nopause -nosplash -nosound -log
    ```
    If this fails with "Plugin 'BlueprintExporter' failed to load because module 'BlueprintExporter' could not be found", the DLL install's BuildId doesn't match the engine — either rebuild the plugin against the engine you're using, or switch engines.

5. Optional but recommended: sanity-check DOW is also still good:
    ```
    MSYS_NO_PATHCONV=1 "/d/Work/UE_DOW/engine/Binaries/Win64/UnrealEditor-Cmd.exe" \
      "D:\Work\UE_DOW\game\UE_DOW.uproject" \
      -run=ProjectManifest \
      -OutDir="D:\Work\blueprintexporter\blueprint-exporter\ProjectInventory_DOW" \
      -EnablePlugins=BlueprintExporter \
      -nullrhi -unattended -nopause -nosplash -nosound -stdout -log
    ```
    Should write `MANIFEST.md` in ~1 s, 18475 total assets, exit 0. The `MSYS_NO_PATHCONV=1` prefix is mandatory on this bash — without it, MSYS rewrites `/Game/...` on the command line to `C:/Program Files/Git/Game/...` and the filter silently matches nothing. The `-stdout` is also mandatory on DOW — default UE logging doesn't go to stdout, so redirect to a log file captures nothing without it. `-EnablePlugins=BlueprintExporter` is because DOW's `UE_DOW.uproject` pins `BlueprintExporter: Enabled=false` (probably from an earlier dev setup); the override re-enables for the run without touching the uproject.

---

## Open follow-ups from 2026-04-27 design.md MCP-only session

Two items remain (item A — `list_gameplay_tags` parser bug — closed by the M28.6.2 ship on 2026-04-28). Listed in priority order; the first is the next session's pickup.

### B. **M28.12.1 — `add_function_override("ReceiveBeginPlay")` duplicate-graph guard** — SCOPED 2026-04-29

**Root cause (received from 2026-04-29 MCP session):** `AAIController`-derived BPs (and any actor-family child) get an auto-spawned `K2Node_Event` for `EventBeginPlay` from `FKismetEditorUtilities::CreateBlueprint`'s `bSpawnDefaultBlueprintNodes` path. Calling `add_function_override(bp_path, "ReceiveBeginPlay")` then creates a NEW function graph alongside the existing event node — both authored against the same `BeginPlay` virtual. Compile sees the duplicate dispatch source and silently fails. The body-add ops that come after correctly try to write into the new override graph but the BP is already in a broken-compile state, so `compile_and_save_package` returns False with no informative error. The "compile_and_save_package returned False" line in the run_plan report was misleading — the actual breakage was the prior `add_function_override` call.

**Fix direction:** in `UBpxReflectionOps::AddFunctionOverrideDeterministic`, after resolving the parent UFUNCTION via `Blueprint->ParentClass->FindFunctionByName`, also walk every `UbergraphPage` for an existing `UK2Node_Event` whose `EventReference.GetMemberName() == FunctionName`. If found, return a structured error: `{ok: false, error: "duplicate-event-graph", existingNodeGuid: <guid>, existingGraphName: <ubergraph>, hint: "EventBeginPlay (or equivalent) is already implemented as an event node; use the existing node or remove it via remove_node before authoring as a function override"}`. Three options were considered:
- **(a) detect-and-refuse — RECOMMENDED.** Defensive default. Caller decides whether to clean up the event node (once `remove_node` lands in M28.16) or use it as-is.
- (b) reuse-existing — silent contract change (UFUNCTION returns a pre-existing graph instead of creating one). Surprising to callers who expected a fresh graph.
- (c) warn-loudly — passes the broken state through; not safe.

**Deferred prerequisite for clean fix:** `remove_node` op (part of M28.16 removal-op symmetry catalog) — without it, the only way for the caller to recover from a stale `EventBeginPlay` node they can't compile around is editor-side authoring. Detect-and-refuse can ship before M28.16 lands; the caller has manual workaround until then.

**Soak fixture when shipped:** override `ReceiveBeginPlay` on a UAIController child fixture in BugHunt, assert structured `duplicate-event-graph` error, then a successful path on a parent class without the auto-event (e.g. UInterface child).

**Versioning when fixed:** patch bump (1.28.6 → 1.28.7).

**Workaround in the meantime:** caller can either author the `BeginPlay` body in the existing event node (via the M28.3.x body-add catalog with `from_node_guid` matching the event node's GUID — surfaced through `get_asset_deep_dump`), or manually delete the event node in the editor before calling `add_function_override`.

---

## Open follow-ups from 2026-04-29 design.md MCP-only session (post-M28.15)

Punch list received from the session that drove the M28.15 ship + scoped M28.12.1 above. Listed in priority order; the first two are confirmed bugs, the rest are scoped milestones.

### D. **MCP `bridge_entry.py` — `ModuleNotFoundError: No module named 'python_ops.plan_executor'`** (CONFIRMED REGRESSION, HIGH PRIORITY)

**Symptom:** every `apply_plan` (and `validate_plan`) call routed through the M27 editor bridge fails with `bridgeErrorCode: -32002` + the bridge response carrying the Python traceback `ModuleNotFoundError: No module named 'python_ops.plan_executor'`. Subprocess fallback works fine (the MCP-side falls through to spawning `UnrealEditor-Cmd.exe -run=pythonscript` with the correct `sys.path` setup). Only the bridge path is broken. Surfaces in 3 pytest tests (`test_plan_tools_config_errors`, `test_plan_timeout_handler_returns_str_tails`, `test_partial_apply_surfaces_at_top_level`) when run with a live editor — these tests assume bridge-or-subprocess; getting the bridge but with broken `sys.path` produces unexpected response shape, all 3 fail. Reproduced in production by the design.md MCP-only session against UE_DOW_Legacy (UE log timestamp 16:07:44 UTC 2026-04-29).

**Hypothesis:** `bridge_entry.py` is invoked via `IPythonScriptPlugin::ExecPythonCommandEx` with per-call namespace isolation (per CLAUDE.md § Editor Bridge Layer). The per-call namespace setup probably doesn't include the same `sys.path` hooks that `bridge_entry.py`'s subprocess-fallback path relies on (where the MCP-side passes `BPX_SCRIPTS_ROOT` env + a `-script=...` arg pointing at a known location). The bridge handler may be reading `bridge_entry.py` from the plugin's `Content/Python/` baked-in path rather than the working-tree `scripts/` location — and the baked-in copy's `sys.path.insert` line targets a path that no longer exists, OR the per-call namespace isolation strips the path hook.

**Diagnostic next steps for whoever picks this up:**
1. Read `Source/BlueprintExporter/Private/Bridge/BpxPlanHandlers.cpp` — find the `ExecPythonCommandEx` invocation site for `bridge_entry.py` and check what `sys.path` setup is done before the call (probably none — relies on the script itself).
2. Read `scripts/bridge_entry.py` — find the `sys.path.insert(0, ...)` line that's supposed to make `python_ops.plan_executor` importable. Confirm the path it inserts actually contains `python_ops/`.
3. Run `python -c "import sys; sys.path.insert(0, '<bridge_entry's-resolved-path>'); from python_ops.plan_executor import run_plan; print('OK')"` from a shell to confirm whether the issue is bridge-side namespace isolation or `bridge_entry.py`'s path-resolution.
4. Soak: add a bridge smoke-test variant in `scripts/smoke_bridge.py` that round-trips a minimal `apply_plan` (e.g., a no-op plan with `operations: []` to exercise the import path without mutating anything). Should fail before fix, PASS after.

**Versioning when fixed:** patch bump (1.28.6 → 1.28.7 if it lands before M28.12.1; otherwise next patch).

### E. **M28.18 — `deep_dump_asset` error observability** (small fix, ~1–2 hrs)

**Symptom:** when `deep_dump_asset` aborts on a broken Blueprint compile, the result's `stdoutTail` shows the "aborting export" line but NOT the preceding `LogBlueprint:Error` / `LogPython:Error` entries. The actual diagnostic information lives in `Saved/Logs/<Project>.log`, which the MCP-only caller can't read without leaving MCP scope.

**Fix:** in the `deep_dump_asset` MCP tool's post-processing, also tail the project's `Saved/Logs/<Project>.log` for the last N (suggest 50) lines matching `LogBlueprint:.*Error|LogPython:.*Error|LogSavePackage:.*Error` and surface them in the result as `logErrorTail: [{line, source}]`. Same pattern as `stdoutTail` but log-side. Single-file MCP-only change in `scripts/blueprint-exporter-mcp/src/blueprint_exporter_mcp/tools/live.py` (or wherever `deep_dump_asset` lives — verify on pickup).

**Versioning when fixed:** patch bump.

### F. **M28.19 — `get_op_catalog` lazy-fetch v2 (`list_ops` + `get_op_signature`)** (~2 hrs)

**Context:** M28.15 added `name_filter` to `get_op_catalog` to let agents narrow the response. That helps but doesn't fully solve the inlining problem — agents still hit the cap when they don't know what to filter on. The session ended up probing via `validate_plan` shape errors (the "unknown op" error happens to dump all known op names) as a workaround, ~6 round-trips of probing.

**Fix:** split into two new MCP tools (preserve `get_op_catalog` as-is for existing callers):
- `list_ops()` returns `{count, ops: [{name, module, summary_line, readOnly}]}` — drops the docstring + parameter schema. Probably <5 K tokens for 63 ops; well under any inlining cap.
- `get_op_signature(op_name: str)` returns the full per-op shape on demand (current per-op entry from `get_op_catalog`).

This is the same pattern Claude Code's `ToolSearch` uses for its own deferred tools (`select:Read,Edit,Grep`). Agents call `list_ops` to discover, then `get_op_signature` for each op they need to author against.

**Soak fixture:** new pytest test confirming `list_ops` < 5 KB, contains all 63+ op names, drops docstrings; `get_op_signature("add_make_struct_node")` returns the same shape as one entry of the unfiltered `get_op_catalog`.

**Versioning when fixed:** patch bump.

### G. **M28.20 — `connect_graph_pins` logical-label scheme** (medium surface change)

**Context:** Currently `connect_graph_pins` requires real `from_node_guid` / `to_node_guid` strings, which are only available from the response of a previous `apply_plan`. Plans that need to wire newly-created nodes have to ship in two phases: (1) create nodes, harvest GUIDs from the response, (2) connect them. The session noted this forces extra round-trips.

**Fix:** add an optional `node_label` field to every node-creating op (`add_branch_node`, `add_call_function_node`, `add_make_struct_node`, etc. — every `add_*_node` op). When present, the op also writes a `(label → node_guid)` mapping into the plan's per-plan label table. `connect_graph_pins` accepts `from_node_label` / `to_node_label` (alongside the existing GUID forms) which resolve via the table. Determinism: labels are caller-supplied strings, the GUID seed already includes deterministic inputs (position, target struct, etc.), so the label is just a within-plan alias — no determinism risk.

**Bigger surface than M28.18/M28.19** because it touches every node-spawning Python op + the `connect_graph_pins` validator + the bridge's plan-executor (to track the label table across an in-flight plan). Probably 1–2 day effort.

**Versioning when fixed:** minor bump (1.28.x → 1.29.0) — this is a new ergonomic subsystem touching every node-creating op.

### H. **Smaller polish** (queue with the existing #4/#5 backlog items in the candidate list below)

- **`var_type_spec` grammar documentation** — bare `"double"` works for primitives, but `struct:`, `object:`, `array:` formats are guesswork. Inline grammar examples in op docstrings + improve the validator's error message to show the expected shape on rejection. ~30 min.
- **`add_set_array_elem` typed op** — `Array_Set` via `add_call_function_node` works but is undiscoverable. A typed array-write op would mirror the M28.14 struct-mutation catalog pattern. Patch.
- **UDS field-GUID render in deep-dump** — extends candidate next-milestone item #4 (UDS field-name GUID stripping) to ALSO render the field GUIDs as `fields_to_show=[...]` strings inline so the `.deep.md` is the one place an authoring caller looks for the inputs to `add_set_fields_in_struct_node`.

### I. **`list_gameplay_tags` per-domain parser** — **CLOSED 2026-04-28** (M28.6.2 ship at 1.28.4)

Confirmed working in the 2026-04-29 session — `Config/Tags/AI.ini` parses 4 tags as expected. No regression.

---

### C. **M28.14 — Struct-mutation node catalog** — **CLOSED 2026-04-28** at version 1.28.5

Shipped this session. Three bridge UFUNCTIONs (`AddMakeStructNode` / `AddBreakStructNode` / `AddSetFieldsInStructNode`) sharing the templated `BpxReflection::PrepStructNodeSpawn<TNodeClass>` scaffold; three Python ops (`add_make_struct_node` / `add_break_struct_node` / `add_set_fields_in_struct_node`) in `blueprint_graph_nodes.py`; three soak fixtures against `BP_BpxTestGraphNodesCalls` using `/Script/CoreUObject.Vector`. SetFields validates `fields_to_show` non-empty + every name resolves to a struct property (silent typo no-op = foot-gun). Determinism seeds `md5(<bp>:graph:<g>:<kind>:<struct_path>[:fields:<sorted_fields>]:<x,y>)` with sort-and-join on FieldsToShow so caller-side ordering doesn't drift the GUID. Read-modify-write inside the M28.13 ForEachLoop body is now end-to-end authorable from a plan. Full ship narrative in the **Latest ship** block above.

---

## Candidate next milestones

Nothing blocking. Pick based on ROI / colleague demand. Items 0–6 are the genuine backlog; items 7–12 are family one-liners pointing at the archive / shipped index (those families are SHIPPED — see the milestone index further down).

0. **M19.2.2 — DataAsset instances in the sweep.** M19.2.1 wired DataAsset-instance support into single-asset `-run=DeepDump`; widening the `ProjectInventoryCommandlet` sweep to cover them too would eliminate the orphan-file pattern and give `.md` + `.meta.json` companions for each DA instance. Scope: add a `UDataAsset` check to the sweep's class filter, add a typed `EmitDataAssetInstance` emitter mirroring the M11–M15 pattern, wire the existing `RenderDataAssetInstanceMarkdown` at Tier 2. DOW has only 6 BP-derived DA instances today; canonical refresh would add ~18 files. A few hours of work.

1. **M19.3 — CDO deserialize write-back (round-trip for CDO edits).** Read path is done (M19.1); write path still missing. Needed only if we want Claude-driven edits of e.g. `GE.DurationPolicy` or `GA.AbilityTags` to persist via `BlueprintImport -Apply`. Mirrors the M18.x deserializer pattern; gate behind the M17 `BS_Error` guard. Defer until a concrete edit target surfaces.

2. **M20 — Level export.** Biggest capability gap after M19. A `LevelInventoryCommandlet` + `FExportedLevel` schema: per-actor table (class / label / transform / tags), instance property overrides (reuse M9 walker), Level Blueprint via existing UBP serializer, World Settings CDO walk, streaming structure (sub-levels, LevelInstance actors, World Partition cells). Skip art data (meshes / materials / lightmaps). Size estimate: 5–20 MB JSON for DOW's main city level. ~1 week of work; natural breakdown: M20.0 actors + overrides, M20.1 streaming / WP, M20.2 Level Blueprint integration.

3. **ControlRigBlueprint typed Tier 2.** Currently dumped via the generic UBP pin-table path (15 K lines for `Face_ControlBoard_CtrlRig`, 12 K for `MetaHuman_ControlRig`) — correct but not rigging-semantic. A typed renderer would decode rig graphs (bones, constraints, solver nodes) similar to how M5.2 handled StateTree editor nodes. Low priority unless a colleague does deep ControlRig work.

4. **UserDefinedStruct field-name GUID stripping.** Struct field tables currently render names like `BodyDefinition_2_ABCDAB8D4F5C30DC9AF7DC9C34D5A278` — the GUID suffix is UE's internal hash. A one-liner post-processing pass to split on the second-last `_` and drop the GUID would clean up all struct `.md` rendering. ~30 min.

5. **Recursive struct breakout at Tier 2.** Large struct values (>100 KB per field — seen on `CrowdCharacterDataAsset.deep.md`'s Skeleton A/B fields) render as single-line Markdown table cells. Mirror M13 DataTable's per-row `UScriptStruct` rendering to break nested struct content into sub-tables. ~1–2 hours.

6. **Wire `verify_determinism.ps1` into CI.** Still sitting on the backlog; ~60 s per run on BugHunt would catch any future serializer / renderer regressions in a PR gate. Implementation is a TeamCity or GitHub Actions step invoking the existing script.

7. **M21 — Python write-layer library.** SHIPPED 2026-04-20. Python op library as the new write layer (uses UE's own save/compile paths). See archive for the original scope brief and M21.x sub-phase breakdown.

8. **M22 — BugHunt-driven Python op validation loop.** SHIPPED 2026-04-20 (late). See archive.

9. **M23 — Reflection Bridge (C++ write layer, `BpxReflectionOps`).** SHIPPED 2026-04-21. See archive.

10. **M24 — Supervised Edit Loop (plan validator + executor + mechanical_diff oracle).** SHIPPED 2026-04-21. See archive.

11. **M25 — MCP server + tactical AI ops.** SHIPPED 2026-04-21. See archive § M25.1 (13 tools).

12. **M28.10 — `create_blueprint_class` op (native parent + determinism).** SHIPPED 2026-04-27 (1.27.1 → 1.28.0). M28.10.0 research outcome (FGuid trapdoor catalog + seeding recipe) + M28.10.1 ship (`CreateBlueprintClassDeterministic` UFUNCTION + `create_blueprint_class` Python op + `create_child_bp` alias with strict ParentClass match + soak harness `recreate_between_rounds` extension). See shipped index below + `M28.10.0 research outcome` section above.

13. **M28.11 — function / custom-event typed-parameter authoring.** SHIPPED 2026-04-27 (1.28.0 → 1.28.1). One bridge UFUNCTION `AddFunctionUserDefinedPin` + 3 Python ops (`add_function_input` / `add_function_output` / `add_custom_event_input`) covering K2Node_FunctionEntry / K2Node_FunctionResult / K2Node_CustomEvent user-defined pins. With M28.11 shipped, design.md's encounter-director ↔ AI.Order custom-event channel can drop the member-variable handshake workaround and use typed event params throughout. See shipped index below.

14. **M28.12 — native virtual override authoring.** SHIPPED 2026-04-27 (1.28.1 → 1.28.2). Surfaced by the design.md MCP-only test against UE_DOW_Legacy hitting `UEnvQueryTest_BlueprintBase::ReceiveTestCondition` — pre-M28.12 the only function-authoring surface was `add_bp_function`, which always created a fresh void/void function (wrong shape for inherited virtuals). One bridge UFUNCTION `AddFunctionOverrideDeterministic(BP, FunctionName)` resolves the parent UFUNCTION via `Blueprint->ParentClass->FindFunctionByName` and calls `AddFunctionGraph<UClass>(BP, NewGraph, /*bIsUserCreated*/ false, ParentClass)` — same engine path as `OverrideInterfaceFunction` (M26.1) but targeting the parent-class chain instead of an `ImplementedInterfaces[]` entry. One Python op `add_function_override(bp_path, function_name)`. See shipped index below.

15. **M28.13 — K2Node_MacroInstance authoring (loop unblocker).** SHIPPED 2026-04-27 (1.28.2 → 1.28.3). See shipped index below.

16. **M28.14 — Struct-mutation node catalog.** SHIPPED 2026-04-28 (1.28.4 → 1.28.5). Three new bridge UFUNCTIONs (`AddMakeStructNode` / `AddBreakStructNode` / `AddSetFieldsInStructNode`) sharing one templated `BpxReflection::PrepStructNodeSpawn<TNodeClass>` scaffold; three Python ops in `blueprint_graph_nodes.py`. Make/Break write the standard `StructType + bMadeAfterOverridePinRemoval = true` pre-alloc config matching the engine editor spawn path (`EdGraphSchema_K2.cpp:7286` / `:7350`). SetFields adds a post-AllocateDefaultPins pass walking `ShowPinForProperties` to flip `bShowPin = true` for each entry whose `PropertyName` matches the caller's `FieldsToShow` list, then `ReconstructNode()` — the SetFields pin manager defaults `bShowPin = false` for every field (`K2Node_SetFieldsInStruct.cpp:400`), so without this walk the node lands with no settable pins. Pre-validates `FieldsToShow` non-empty + every name resolves to a struct property (silent typo no-op = foot-gun). Determinism seeds `md5(<bp>:graph:<g>:<kind>:<struct_path>[:fields:<sorted_fields>]:<x,y>)` with sort-and-join on FieldsToShow so caller-side ordering doesn't drift the GUID. With M28.14 + M28.13 shipped, design.md's read-modify-write inside the ForEachLoop body (UAIActionScorer per-element scoring, S_TargetInfo confidence-decay) is end-to-end authorable from a plan. Three soak fixtures against `BP_BpxTestGraphNodesCalls` using `/Script/CoreUObject.Vector` (X/Y/Z all BlueprintVisible non-BlueprintReadOnly — stable across engine versions); SetFields fixture passes `fields_to_show=["X","Y"]` to exercise both the post-alloc bShowPin walk and the sorted-fields seed. See shipped index below.

---

## M28 phase table

**Phase breakdown (tentative — M28.0 finalizes):**

| Phase | Scope | Deliverable |
|---|---|---|
| **M28.0** | Research + sequencing | Confirm Python + `BpxReflectionOps` surface per phase; probe `FBlueprintEditorUtils::AddNewVariable`, `FBlueprintEditorUtils::AddNewFunction`, `USimpleConstructionScript::AddComponent`, `FStructureEditorUtils::AddVariable` (UDS), `UCurveFloatFactory` / `UDataAssetFactory`, `UEnvQueryOption::Tests[]`, `UGameplayTagsManager::AddNewGameplayTagToINI`. Pattern mirrors M26.0 / M27.0. Output: UFUNCTION surface per phase appended here. |
| **M28.1** | `add_statetree_task_to_state` (+ remove counterpart, + verify helper) | Smallest piece — also closes Flat Arena #4. Mirrors `add_statetree_transition` shape: `{st_path, state_path, task_bp_path, [task_kwargs]}`. Expected to reuse the M23.1 `BpxReflectionOps` StateTree editor-data surface with no bridge extension. Idempotent on (st_path, state_path, task_bp_path). |
| **M28.2** | Structural BP edits: `add_bp_variable`, `add_component_to_scs`, `add_bp_interface`, `add_bp_function` | First half of design.md's write scope. Bridge extends `BpxReflectionOps` with `AddBlueprintVariable(BP, Name, PinType, DefaultValue, Flags)`, `AddSCSComponent(BP, Name, ComponentClass, AttachTo, Socket, Transform)`, `AddImplementedInterface(BP, InterfacePath)`, `CreateFunctionGraph(BP, Name, bIsPure)`. Idempotent; deterministic NodeGuids + object names (M26.1.2 pattern). Probably 4–6 new UFUNCTIONs + 1–2 new USTRUCTs. |
| **M28.3** | Node-level graph authoring: `add_graph_node`, `connect_pins`, `set_pin_default`, `add_local_variable` | The M26.3 scope deferred as "defer unless a real driver" — design.md is that driver, and Flat Arena #3 is the immediate smoke-test. Biggest bridge surface in M28: starts narrow with 5–8 K2Node types (`Branch`, `CallFunction`, `VariableGet`/`Set`, `MakeLiteral`, `CustomEvent`, `Sequence`, `Cast`), grows as concrete plans drive additional node types. Reuses M26.1's `FindGraphEndpoints` / `AddSelfMemberGetNode` / `ConnectPinsByName` / `SetNodePinLiteralDefault` as the narrow core; all new node-spawn UFUNCTIONs apply md5-seeded NodeGuids + `SeedPinGuidsForNode` + `BpxNode_*` deterministic object names so two runs produce byte-identical `.uasset`. |
| **M28.4** | Non-BP asset authoring: UserDefinedStruct, CurveFloat, DataAsset instances | `create_user_defined_struct`, `add_uds_member`, `set_uds_member_default`, `create_curve_float`, `set_curve_float_keys`, `create_data_asset_instance`, `set_data_asset_property`. Covers design.md items 3, 6, 7 directly. Bridge extends with `CreateUserDefinedStruct`, `AddUDSMember` (routes through `FStructureEditorUtils` — engine refuses refresh on raw struct edits), `CreateCurveAsset` (variants per curve type), `CreateDataAssetInstance(ParentClass, PackagePath)`. Reuses existing `SetObjectProperty` surface for DA property authoring. |
| **M28.5** | EQS write-side: `add_eqs_test`, `remove_eqs_test`, `set_eqs_test_property`, `set_eqs_generator`, `set_eqs_generator_property` | Mirror of M15 EQS read-side. `UEnvQuery::GetOptions()` already walkable; inverse adds/removes/edits `FEnvQueryOption::Tests[]` + generators. Unlocks design.md item 5 (multi-target cover scoring). Bridge surface small — 3–5 UFUNCTIONs; most work is Python ops + validator entries. |
| **M28.6** | GameplayTag author: MCP tool `list_gameplay_tags` + plan op `add_gameplay_tag` | **M28.6.1 SHIPPED 2026-04-25 (1.26.0 → 1.27.0); M28.6.2 SHIPPED 2026-04-28 (1.28.3 → 1.28.4) — per-domain `Config/Tags/<X>.ini` parser fix on `list_gameplay_tags` (regex required `+` array-append prefix; UE's editor writes per-domain files without it because each backs a standalone `UGameplayTagsList` instance, no cross-config-layer accumulation).** `DefaultGameplayTags.ini` + `Config/Tags/*.ini` are the authoring surface. Bridge has `AddGameplayTag(FName, FString Comment, FName SourceIni)` routing through `UGameplayTagsManager::AddNewGameplayTagToINI`. MCP-side `list_gameplay_tags` is zero-UE-process: walks config ini files, returns `{tags: [{name, comment, source, restricted}], redirects, sources}`. Unlocks `AI.Order.Flank` / `AI.Order.Suppress` / `AI.Callout.Grenade` authoring without hand-editing `.ini`. |
| **M28.7** | Verification beyond mechanical diff: `run_automation_test` bridge handler + gym-map fixture | Today `mechanical_diff` answers "did the file bytes change". design.md needs "does the squad actually flank". New bridge handler runs an automation test in-process (reuses M27.2 Python-scope pattern, not a new subprocess shell). Gym map `L_DesignGym` with placed director + 4 enemies + dummy target + per-scenario assertions. Expected ship shape: M28.7.1 handler only (reuses existing `BlueprintExporter.*` automation suite), M28.7.2 gym project + placed-actor fixtures, M28.7.3 reusable scenario library. |
| **M28.8** | Optional read-side additions | Tier 2 for `UUserDefinedStruct` / `UCurveFloat` / `UAnimMontage`; project-level `TAGS.md` rollup in `AggregateInventoryCommandlet`. Non-blocking — ergonomic sugar for agent authoring. Mirror of M11–M15 pattern. Defer until M28.2–M28.7 land. |
| **M28.11** | Function / custom-event typed-parameter authoring | **SHIPPED 2026-04-27 (1.28.0 → 1.28.1).** Bridge UFUNCTION `AddFunctionUserDefinedPin(BP, FunctionName, PinName, PinType, bDirectionIsOutput, DefaultValue)` wraps `K2Node_EditablePinBase::CreateUserDefinedPin` covering Entry / Result / CustomEvent nodes (Result node auto-spawned with deterministic NodeGuid + pin IDs on first output add when missing). Python ops `add_function_input` / `add_function_output` / `add_custom_event_input`. Reuses `_resolve_pin_type` from blueprint_structural. Idempotence: inline `UserDefinedPins` walk by name (engine's `UserDefinedPinExists` not `BLUEPRINTGRAPH_API` exported). Determinism: pin GUIDs seeded via `SeedGuidFromJoined(<bp>:<scope>:<fname>:userpin:<pname>:<dir>)` matching the M26.1.2 pin-id seed convention. Three new soak fixtures (`add_function_input.json` / `add_function_output.json` / `add_custom_event_input.json`); all 51 pre-push gates PASS in 702 s with `-IncludeDow`. |
| **M28.12** | Native virtual override authoring | **SHIPPED 2026-04-27 (1.28.1 → 1.28.2).** Surfaced by the design.md MCP-only test hitting `UEnvQueryTest_BlueprintBase::ReceiveTestCondition` — pre-M28.12 the only function-authoring surface was `add_bp_function` (fresh void/void only). Bridge UFUNCTION `AddFunctionOverrideDeterministic(BP, FunctionName)` parallels `OverrideInterfaceFunction` (M26.1): resolves parent UFUNCTION via `Blueprint->ParentClass->FindFunctionByName(FunctionName)` (engine helper walks entire ancestor chain), validates `FUNC_BlueprintEvent` flag, calls `AddFunctionGraph<UClass>(BP, NewGraph, false, ParentClass)`, auto-spawns deterministic `K2Node_FunctionResult` if parent has out/return params. Python op `add_function_override(bp_path, function_name)`. Distinct seed prefix `<bp>:override_func:<fn>:<slot>` (vs fresh-function `<bp>:func:`) so a fresh function and override on the same BP get distinct seeds. Soak fixture against `BP_GAS_Ability` overriding `K2_ShouldAbilityRespondToEvent`. All 52 pre-push gates PASS in 702 s with `-IncludeDow`. |
| **M28.13** | K2Node_MacroInstance authoring (loop unblocker) | **SHIPPED 2026-04-27 (1.28.2 → 1.28.3).** Single highest-ROI op of M28: one new bridge UFUNCTION `AddMacroInstanceNode(BP, GraphName, MacroGraph, Position)` unblocks five design.md sections stuck on "iterates X → blocked" (BroadcastOrder/AssignRole iteration, ScorerScoringLoop, ConfidenceDecay×2, SharedPerception). Adjacent to the M28.3.x atomic K2Node spawn family — only delta is the pre-`AllocateDefaultPins` `MacroGraphReference.SetGraph(MacroGraph)` call so the inherited `UK2Node_Tunnel::AllocateDefaultPins` pin-mirror walk has the macro to iterate. NodeGuid seeded `md5(<bp>:graph:<g>:macro:<lib_path>:<x>,<y>)`; `SeedPinGuidsForNode` runs AFTER alloc so mirrored pins (variable count by signature) get deterministic PinIds. One Python op `add_macro_instance_node(bp_path, graph_name, macro_path, position)` accepting `"<lib_uobject_path>:<macro_name>"` shape. Macro library walked via the reflection-bridge `get_array_length` / `get_object_property_value` accessor (UBlueprint's `MacroGraphs` UPROPERTY is `CPF_Protected`, not surfaced as `lib.macro_graphs` in the Python binding — surfaced as a soak round-1 `AttributeError` on first attempt). Soak fixture `add_macro_instance_node.json` against `BP_BpxTestGraphNodesCalls` spawning ForEachLoop; `skip_inspect=true`. All 53 pre-push gates PASS in 707 s with `-IncludeDow`. |
| **M28.14** | Struct-mutation node catalog (Make / Break / SetFields) | **SHIPPED 2026-04-28 (1.28.4 → 1.28.5).** Three new bridge UFUNCTIONs `AddMakeStructNode` / `AddBreakStructNode` / `AddSetFieldsInStructNode` on `UBpxReflectionOps` sharing one templated `BpxReflection::PrepStructNodeSpawn<TNodeClass>` scaffold (validates BP / graph / struct, computes seeded NodeGuid + idempotence walk, NewObject + StructType + `bMadeAfterOverridePinRemoval = true` + AddNode + AllocateDefaultPins). Make/Break finalize with `SeedPinGuidsForNode`. SetFields adds a post-alloc `ShowPinForProperties` walk flipping `bShowPin = true` per `FieldsToShow` entry, then `ReconstructNode()` to honor the bShowPin overrides (engine `RebuildPropertyList` preserves them via its old-settings cache, `K2Node.cpp:1722-1817`); pre-validates `FieldsToShow` non-empty + every name resolves to a struct property (silent typo no-op = foot-gun). Determinism seeds `md5(<bp>:graph:<g>:<kind>:<struct_path>[:fields:<sorted_fields>]:<x,y>)`; sort-and-join on FieldsToShow so caller-side ordering doesn't drift the GUID. Three Python ops in `blueprint_graph_nodes.py` sharing `_resolve_script_struct(struct_type_path)` helper (`unreal.load_object` since ScriptStruct is a UObject not a UClass). Three soak fixtures against `BP_BpxTestGraphNodesCalls` using `/Script/CoreUObject.Vector` (engine-stable, X/Y/Z all BlueprintVisible). With M28.14 shipped, the read-modify-write half of design.md's loop bodies (item 2 UAIActionScorer per-element scoring, item 3 confidence-decay over `S_TargetInfo`) is end-to-end authorable from a plan. |
| **M28.10** | BP class authoring with native parent + determinism | **SHIPPED 2026-04-27 (1.27.1 → 1.28.0).** M28.10.0 research outcome (FGuid trapdoor catalog + seeding recipe — see active section above) + M28.10.1 ship: `UBpxReflectionOps::CreateBlueprintClassDeterministic` UFUNCTION post-create reseeds all three trapdoors (BlueprintGuid + UCS entry NodeGuid + sorted default-event NodeGuids/PinIds); `create_blueprint_class(parent_path, new_bp_path)` Python op accepts native `/Script/...` + BP `/Game/...[.<Name>_C]` parents; `create_child_bp` converts to back-compat alias with strict ParentClass match via C++ pointer equality (closes the pre-M28.10.1 Python-binding caveat); `scripts/soak_template.py` extended with `recreate_between_rounds` flag so create-op soaks genuinely exercise the create path. With M28.10 shipped, design.md slices E + F move from "likely no" to "yes". Full ship narrative in shipped index below. |
| **M28.15** | `get_op_catalog` `name_filter` substring param | **SHIPPED 2026-04-29 (1.28.5 → 1.28.6).** Pure-MCP-server fix — optional `name_filter: str | None = None` param on `get_op_catalog_impl` + the `@mcp.tool` shim. Surfaced by the 2026-04-29 design.md MCP-only session against UE_DOW_Legacy where the unfiltered catalog (~106 KB, ~26 K tokens at 63 ops × full docstrings + parameter schemas) crossed the MCP-client tool-result inlining limit; agent fell back to a stale snapshot and misclassified shipped M28.13 + M28.14 ops as "candidate / blocked." Case-insensitive substring match against op `name`; non-matching ops skipped before per-op file read + AST parse. Filtered responses carry `filter` + `total` bookkeeping; unfiltered shape unchanged. Single-file change in `tools/plans.py` + new regression test `test_get_op_catalog_name_filter`. Patch bump. Full ship narrative in **Latest ship** above. |
| **M28.12.1** | `add_function_override` duplicate-graph guard | **SCOPED 2026-04-29.** Bug surfaced by design.md session against `BP_EnemyBase_AIController.ReceiveBeginPlay`: `AAIController`-derived BPs get an auto-spawned `EventBeginPlay` event node from `bSpawnDefaultBlueprintNodes`; `add_function_override` then creates a same-named function graph alongside it, breaking compile. Fix direction (a) detect-and-refuse: in `AddFunctionOverrideDeterministic`, walk all `UbergraphPages` for an existing `UK2Node_Event` whose `EventReference.GetMemberName() == FunctionName`, return structured error. Patch bump (1.28.6 → 1.28.7). Full triage detail in **Open follow-ups from 2026-04-27 design.md MCP-only session** § B above. |
| **M28.16** | Removal-op symmetry catalog (LARGE) | **PROPOSED.** Catalog has 21 `add_*` / 9 `set_*` but only 5 `remove_*` ops. Concrete missing: `remove_function_override`, `remove_graph`, `remove_bp_function`, `remove_bp_variable`, `remove_function_input`, `remove_function_output`, `remove_local_variable`, `remove_node`, `delete_asset`. Probably split into: M28.16.0 research (engine-helper map: `FBlueprintEditorUtils::RemoveFunctionGraph`, `FBlueprintEditorUtils::RemoveMemberVariable`, `K2Node_EditablePinBase::RemoveUserDefinedPin`, `UEdGraph::RemoveNode`, `ObjectTools::DeleteObjects`), then M28.16.1 BP-side removals (graph/variable/function), M28.16.2 node-level removals (`remove_node` + parameter removals), M28.16.3 asset deletion. Drives M28.12.1's clean fix (caller can `remove_node` the auto-spawned event before `add_function_override`). Probably 1–2 weeks total. Minor bump per ship slice. |
| **M28.17** | StateTree state-instance writes + property bindings | **PROPOSED.** Two surfaces: (a) `set_statetree_state_condition_property(st_path, state_path, condition_index, property_name, value)` — writes per-state-instance condition property values (the design.md `RequiredOrder` case). Mirrors `set_statetree_task_property` shape if it exists, otherwise mirrors `set_data_asset_property`. (b) `bind_statetree_property(st_path, state_path, target_path, source_path)` — `FStateTreePropertyPath` binding from a context source (e.g. `Self.AIController.CurrentOrder`) to a state input. Source/target paths are 3-tuples (struct ID + segments + segment kinds); needs research on `FStateTreeBindingDesc` / `FStateTreeEditorPropertyPath` engine surface. Probably M28.17.0 research + M28.17.1/.2 ship slices. Minor bump. |
| **M28.18** | `deep_dump_asset` error observability | **PROPOSED.** Small fix (~1–2 hrs). When `deep_dump_asset` aborts on broken-compile, also tail the project's `Saved/Logs/<Project>.log` for last N (suggest 50) lines matching `LogBlueprint:.*Error\|LogPython:.*Error\|LogSavePackage:.*Error` and surface as `logErrorTail: [{line, source}]`. Single-file MCP-only change. Patch bump. Full triage detail in **Open follow-ups from 2026-04-29 design.md MCP-only session** § E above. |
| **M28.19** | Catalog discoverability v2 (lazy-fetch) | **PROPOSED.** M28.15's `name_filter` was partial; full lazy-fetch pattern: split into `list_ops()` (returns `{count, ops: [{name, module, summary_line, readOnly}]}` only — drops docstring + parameter schema, < 5 K tokens) + `get_op_signature(op_name: str)` (returns full per-op shape on demand). Mirrors Claude Code's `ToolSearch` pattern. Preserve `get_op_catalog` as-is for back-compat. ~2 hrs. Patch bump. Full triage detail in § F above. |
| **M28.20** | `connect_graph_pins` logical-label scheme | **PROPOSED (medium surface).** Optional `node_label` field on every node-creating op; `connect_graph_pins` accepts `from_node_label` / `to_node_label` resolved via a per-plan label table. Lets a single plan create + wire instead of the current 2-phase (create → harvest GUIDs from response → wire). Touches every `add_*_node` op signature + the validator + the bridge plan-executor. 1–2 day effort. Minor bump (1.28.x → 1.29.0) — new ergonomic subsystem. Full triage detail in § G above. |
| **M28.bridge-fix** | `bridge_entry.py` `python_ops.plan_executor` ModuleNotFoundError | **PROPOSED, HIGH PRIORITY.** Bridge-routed `apply_plan` / `validate_plan` calls fail with `bridgeErrorCode: -32002` + `ModuleNotFoundError: No module named 'python_ops.plan_executor'`. Subprocess fallback works fine. Diagnostic in § D above. Probably small surface to fix once diagnosed. Patch bump. |
| **M28.15** | `get_op_catalog` `name_filter` substring param | **SHIPPED 2026-04-29 (1.28.5 → 1.28.6).** Pure-MCP-server fix surfaced by the 2026-04-29 design.md MCP-only session against UE_DOW_Legacy: agent reported "Catalog too big to inline. Probing the cached file for the four target ops directly" and fell back to a stale snapshot, misclassifying shipped M28.13 + M28.14 ops as "M28.14 candidate / blocked." Root cause: catalog grew to ~106 KB / ~26 K tokens at 63 ops × full docstrings + parameter schemas, crossed the MCP-client tool-result inlining limit. Fix: optional `name_filter: str | None = None` param on `get_op_catalog_impl` + `@mcp.tool` shim; case-insensitive substring match against op `name`; non-matching ops skipped before per-op file read + AST parse. Filtered responses carry `filter` + `total` bookkeeping; unfiltered shape unchanged (existing callers and `test_get_op_catalog` shape assertions intact). Single-file change in `scripts/blueprint-exporter-mcp/src/blueprint_exporter_mcp/tools/plans.py`; new regression test `test_get_op_catalog_name_filter` covers narrow / case-insensitivity / empty-as-unfiltered / no-match-with-bookkeeping. Patch bump (catalog-additive). DLL rebuild + 3-location install deferred (active editor session); pure-Python so MCP picks up new shape on next restart regardless of DLL state. |

**Sequencing constraint:** M28.pre.1 / .2 / .3 / .4 block M28.1 per the gate table above — ship matrix hardening BEFORE the first write-side op lands, otherwise every M28 op ships with known-silent verification. Post-M28.pre: M28.1 → M28.2 → M28.3 is the critical path (each depends on the prior's bridge surface). M28.4 / M28.5 / M28.6 can ship in parallel once M28.2 lands. M28.7 depends on at least M28.3 (tests need node-level authoring to stage repeatable scenarios). M28.8 can ship anytime. M28.10 can ship anytime — it has no inbound dependency on other M28 phases (its outbound is what unblocks design.md slices E + F end-to-end).

**Reference patterns to reuse:**
- `BpxReflectionOps` (M23.1) for every UFUNCTION bridge extension.
- M26.1 / M26.1.1 / M26.1.2 for deterministic seeding — **reuse `SeedGuidFromJoined` + `SeedPinGuidsForNode` + `BpxVarGet_*`-style deterministic object names across every graph op in M28.3**; also the `CollectGarbage(RF_NoFlags, /*bPerformFullPurge*/ true)` post-wipe pattern when an op swaps old nodes for new.
- M25.2.1 `add_statetree_transition` for the Python op shape (atomic compile+save, idempotence, optional kwargs, JSON serialization of kwarg values).
- M24.3 `mechanical_diff` oracle — extend `_op_expected_changes` per new op.
- `AtomicFileWriter::SaveStringAtomic` for any new config-file writes (M28.6 tag ini path — though prefer `UGameplayTagsManager` APIs where possible).
- BugHunt + `verify_determinism.ps1 -SweepDeepDump` — **non-negotiable** gate per op that touches serialization; new fixtures via `GenerateTestBlueprintsCommandlet`, never hand-authored.
- M27.2 bridge handler pattern for M28.7's in-process automation-test runner (not a subprocess shell).

**Versioning expectation (full 9-location stamp sweep + dual-engine DLL rebuild per `CLAUDE.md § Versioning Protocol` on every bump):**
- M28.0: no bump (research).
- M28.1: patch — reuses existing bridge surface (1.19.7 → 1.19.8).
- M28.2: minor — new subsystem (structural BP edit surface) (1.20.0).
- M28.3: minor — new subsystem (graph-authoring catalog) (1.21.0).
- M28.4: minor — new subsystem (non-BP asset factories) (1.22.0).
- M28.5: patch — additive (1.22.x).
- M28.6: minor — new subsystem (tag config authoring) (1.23.0).
- M28.7: minor — new subsystem (automation-test runner) (1.24.0).
- M28.8: patch per renderer addition.
- M28.10: minor — new subsystem (BP class factory). Patch on `create_child_bp` hardening if shipped separately.

**Success criterion (M28 closed):** given a fresh DOW-family project with the current `ST_EnemyBase` shape, Claude can author the entire design.md via `apply_plan` calls end-to-end — director spawned, utility scorer attached, perception struct thickened, archetype DAs authored, EQS multi-target cover active, intensity curve driving pacing, callout tags registered, gym-map automation test passes — with no manual editor work outside asset creation the design doesn't scope (meshes / SFX / anim source). Determinism gate green across every shipped op.

**Risk indicators:**
- **Bridge surface balloon on M28.3 (HIGH).** Node-creation catalog is broad. Mitigation: ship narrow first (5–8 K2Node types covering the minimum design.md surface), extend only when a concrete plan requires a new node type. Reviewed external UE-Python graph tooling exports ~60 UFUNCTIONs for full coverage — we don't need parity, we need design.md coverage.
- **UserDefinedStruct authoring on M28.4 (MEDIUM).** UDS has a non-obvious separation between the `UScriptStruct` (serialized form) and `UUserDefinedStructEditorData` (authoring state). Member edits MUST go through `FStructureEditorUtils` or the editor refuses to refresh. Probe in M28.0.
- **Tag-ini concurrent editing on M28.6 (LOW).** Multiple `*.ini` sources + hot-reload. Mitigation: always route through `UGameplayTagsManager` APIs (engine owns re-read), never raw file writes.
- **Automation-test scope creep on M28.7 (MEDIUM).** Gym map + scenarios + assertion scaffolding is a project unto itself. Mitigation: ship M28.7.1 handler-only against the existing `BlueprintExporter.*` automation family before M28.7.2 gym.
- **design.md evolves.** It's a design doc, not a frozen spec. If the user revises design.md, this phase table should track — re-read the source when ambiguity surfaces.

**Open questions (resolve in M28.0):**
1. **Generic node-spawn (M28.3) vs per-pattern convenience ops.** Generic is reusable; per-pattern (e.g. `add_callout_broadcast(bp_path, tag, audio_cue)`) is faster to ship and easier for agents to author correct plans against. **Recommend:** narrow-generic for M28.3, then one convenience op per design.md item in a follow-up M28.9 polish pass if the raw generics prove clunky in practice.
2. **Gym-map project hosting (M28.7).** BugHunt (already in determinism rotation, but risks bloating fixture regen) vs new dedicated `DesignGym/` sibling project. **Recommend:** new sibling project with its own junction so combat content doesn't contaminate the determinism golden.
3. **Feedback loop from M28.7 failures.** Today plans are one-shot. If a test fails, how does the agent retry? **Recommend:** surface test report back through MCP, let the agent compose a follow-up plan — do NOT build auto-retry into the pipeline itself (stateful + harder to reason about).

**Relationship to pre-existing blocks in this file:**
- **Flat Arena #4** (`add_statetree_task_to_state`) IS M28.1. Ship M28.1 first so Flat Arena closes alongside the design.md critical path.
- **Flat Arena #3** (K2 node-pin connect) is covered by M28.3. Ship M28.3 after M28.2.
- **Flat Arena #2** (level / umap edits) is M20 Level Export, a separate track. design.md mostly avoids level-side edits (director + components + DAs + curves are all asset-side); defer M20 unless a later design.md revision demands it.
- **Pre-existing M26.2 / M26.3 rows** in the M26 sub-phase table below are fully subsumed by M28.2 + M28.3. Delete those M26 rows once M28.0 closes and M28.1 ships.

---

## M28.10.0 research outcome (2026-04-27)

Self-contained brief for picking up M28.10.1 cold after `/clear`. Mirrors the M28.4.3 / M28.6.0 research-outcome shape.

### FGuid::NewGuid() trapdoors on fresh `BlueprintFactory.create_asset(...)`

Trace path (engine UE 5.7-equivalent in custom UE_DOW): `UBlueprintFactory::FactoryCreateNew` → `FKismetEditorUtilities::CreateBlueprint` (`Editor/UnrealEd/Private/Kismet2/Kismet2.cpp:432`).

| # | Site | What gets a fresh `FGuid::NewGuid()` | Trapdoor severity |
|---|---|---|---|
| 1 | `Kismet2.cpp:454` `NewBP->GenerateNewGuid()` → `BlueprintCore.h:43` `BlueprintGuid = FGuid::NewGuid()` | `UBlueprintCore::BlueprintGuid` | **HIGH** — persisted, diffable, breaks twin-run on every create. |
| 2 | `Kismet2.cpp:532–567` `bSpawnDefaultBlueprintNodes` block: `AddDefaultEventNode` for each entry in `AutoGeneratedDefaultEventsMap` matching the parent class. Each spawned `UK2Node_Event` ends up with `NodeGuid = FGuid::NewGuid()` via the `PostPlacedNewNode` path (and pin GUIDs via `AllocateDefaultPins` → `UEdGraphPin::CreatePin`). | Per-event `NodeGuid` + per-pin `PinId` on every default-spawned event node (BeginPlay / Tick / etc. for `AActor`-family parents; module-registered events for other parents) | **HIGH** — same drift pattern M26.1.2 closed for graph-authoring ops. |
| 3 | `SCS_Node.cpp:645–654` `USCS_Node::ValidateGuid` — already deterministic (md5 of `InternalVariableName`), no trapdoor | n/a | NONE — confirmed safe. |

**Confirmed safe (no `FGuid::NewGuid()` fires):**
- `UEdGraph` (Ubergraph EventGraph + UCS function graph) has no GUID field.
- `UBlueprintGeneratedClass` named with deterministic `<ShortName>_C` (`Kismet2.cpp:461–463`).
- `USimpleConstructionScript` for fresh BP has zero nodes (no Add → no VariableGuid).
- UCS function graph has just an empty `UFunctionEntry` — `K2Node_FunctionEntry::PostPlacedNewNode` does call `CreateNewGuid()`, so this is **trapdoor #2b**: also need to seed the UCS entry node's NodeGuid.

### Determinism strategy (mirror of `CreateUserDefinedStructDeterministic`, `ReflectionOps.h:1080`)

Bridge UFUNCTION shape (added to `UBpxReflectionOps`):

```cpp
UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
static FBpxReflectionResult CreateBlueprintClassDeterministic(
    const FString& PackagePath,   // /Game/.../BP_Foo (no .uasset, no _C)
    UClass* ParentClass);          // resolved Python-side via load_class || load_object
```

Post-create seeding pass (in `CreateBlueprintClassDeterministic`, after `FKismetEditorUtilities::CreateBlueprint` returns the new `UBlueprint*`):

1. `NewBP->BlueprintGuid = SeedGuidFromJoined(PackagePath + TEXT(":bp"))`. Closes trapdoor #1.
2. **Seed the UCS function graph's entry node** (zero or one `K2Node_FunctionEntry`):
   - `Node->NodeGuid = SeedGuidFromJoined(PackagePath + TEXT(":ucs:entry"))`
   - `SeedPinGuidsForNode(Node, PackagePath + TEXT(":ucs:entry"))`
3. **Sort + reseed default-spawned event nodes** in `NewBP->UbergraphPages[0]->Nodes`:
   - Sort by `(NodeClass->GetName(), Cast<UK2Node_Event>(Node)->EventReference.GetMemberName().ToString())` so iteration order doesn't depend on `TMultiMap` hash-bucket ordering across editor invocations. (Same paranoia we applied at M26.1.2's `force_rebind` pass.)
   - For each: `Node->NodeGuid = SeedGuidFromJoined(PackagePath + TEXT(":evt:") + EventName)` + `SeedPinGuidsForNode(Node, PackagePath + TEXT(":evt:") + EventName)`.
4. Recompile (the engine compile inside `CreateBlueprint` ran with the random GUIDs; the seeded GUIDs need to flow into the generated class). `FBlueprintCompilationManager::CompileSynchronously(NewBP, EBlueprintCompileOptions::SkipGarbageCollection)` then `MarkBlueprintAsStructurallyModified` → `CompileAndSavePackage` (existing helper) handles it.

**Reuse:** `BpxReflection::SeedGuidFromJoined` (`ReflectionOps.cpp:381`) + `SeedPinGuidsForNode` (`ReflectionOps.cpp:406`) — already battle-tested across M28.3.

### Native vs BP parent-class resolution

Canonical recipe (already used by `data_assets._resolve_da_class`, `eqs._resolve_eqs_class`, `blueprint_structural._resolve_class`, `blueprint_graph_nodes._resolve_class`):

```python
cls = unreal.load_class(None, class_path) or unreal.load_object(None, class_path)
```

- Native: `/Script/Engine.Actor` → `load_class` resolves directly.
- BP-derived generated class: `/Game/.../BP_Foo.BP_Foo_C` → `load_object` fallback resolves the generated class.
- BP-asset path (`/Game/.../BP_Foo`): NOT directly resolvable as a `UClass`; either accept and append `.{tail}_C` Python-side OR reject with a structured error directing the user to use the `_C` form. **Recommend:** accept both and normalize. The plan_validator's `assets` field semantics make `/Game/.../BP_Foo` the natural author form for "an existing Blueprint asset"; appending `_C` Python-side mirrors how `set_data_asset_property` already handles BP-derived DA classes.

**Bridge-side validation** (in `CreateBlueprintClassDeterministic`):
- `if (!ParentClass) -> error "ParentClass null"`
- `if (!FKismetEditorUtilities::CanCreateBlueprintOfClass(ParentClass)) -> error "parent not blueprintable"` (the `BlueprintFactory::FactoryCreateNew` check at `EditorFactories.cpp:6805` would otherwise raise a modal `FMessageDialog` — must intercept before that path).
- `if (ParentClass->HasAnyClassFlags(CLASS_Abstract))` → tolerated; engine handles abstract parents fine.

### Idempotence (stricter than `create_child_bp`)

Bridge-side (no Python-binding limitation per `CATALOG.md:1431`):

```cpp
if (UPackage* Pkg = FindPackage(nullptr, *PackagePath)) {
    if (UBlueprint* Existing = FindObject<UBlueprint>(Pkg, *ShortName)) {
        if (Existing->ParentClass == ParentClass) {
            // success, skipped — match
        } else {
            // structured error: parent class mismatch (Existing->ParentClass->GetPathName() vs ParentClass->GetPathName())
        }
    }
}
```

This matches Existing's `ParentClass` against the requested `ParentClass` directly via `UClass*` pointer equality (post-load both resolve to the same singleton). Eliminates the "parent class not verified" caveat from `create_child_bp:134`.

### `create_child_bp` hardening (M28.10.1 bundles this)

Two options for `create_child_bp:84`:

**Option A — route through the same C++ bridge.** Add a thin helper UFUNCTION `CheckBlueprintParentClass(BPPath, ExpectedParent) -> bool` and call it from `create_child_bp` before falling through to the existing "skipped" path. Removes the "parent class not verified" caveat. Slightly more bridge surface.

**Option B — converge `create_child_bp` and `create_blueprint_class` into one op.** `create_blueprint_class(parent_path, new_bp_path)` accepts both `/Script/...` (native) and `/Game/...` (BP) parent forms; `create_child_bp` becomes a back-compat alias that internally calls `create_blueprint_class` with the same parent resolution recipe. Plans authored against the old name keep working; new plans use the unified op. Less surface, more consolidation.

**Recommend Option B.** Saves a UFUNCTION, removes a Python-binding limitation, leaves zero behavioural divergence between native-parent and BP-parent paths. The `create_child_bp` plan_shape entry stays as a back-compat alias; mechanical_diff `_op_expected_changes` already covers both names since they map to the same `(asset_path, "created")` shape.

### M28.10.1 ship checklist (pre-flight)

1. **C++:** add `UBpxReflectionOps::CreateBlueprintClassDeterministic` per the shape above. Mirror `CreateUserDefinedStructDeterministic`'s structure.
2. **Python op:** add `create_blueprint_class(parent_path, new_bp_path)` to `scripts/python_ops/assets.py`. Resolve parent via the canonical `load_class || load_object` fallback. Convert `create_child_bp` to an alias that delegates with the parent-path normalization (`/Game/.../BP` → `/Game/.../BP.BP_C`).
3. **Plan validator:** add `create_blueprint_class` row to `plan_shape.py`'s `OP_SHAPES`; required `["parent_path", "new_bp_path"]`, `assets_absent: ["new_bp_path"]`. Keep `create_child_bp` row.
4. **Mechanical diff oracle:** add `create_blueprint_class` branch to `mechanical_diff._op_expected_changes` returning `[(new_bp_path, "created")]`. Already covered for `create_child_bp`.
5. **Soak fixture (verify_all.ps1's M28.pre.3 pass):** add a soak slice creating `/Game/Test/BPX/BP_FromActor` (parent `/Script/Engine.Actor`) + `/Game/Test/BPX/BP_FromComp` (parent `/Script/Engine.ActorComponent`). Two creates → assert byte-identical .uasset across rounds.
6. **CATALOG.md:** add the op row + remove the "BlueprintGeneratedClass.get_super_class not exposed uniformly" caveat at `:1431` (now closed via Option B).
7. **Versioning stamp sweep:** `1.27.1 → 1.28.0` (minor bump per "new subsystem (BP class factory)" line in the M28.10 versioning expectation). All 9 locations per `CLAUDE.md § Versioning Protocol`. Dual-engine DLL rebuild (UE_DOW custom + stock UE 5.7 via `_build_output_5_7`) per the colleague-bulletproof rule.
8. **Pre-push gates per `CLAUDE.md § Pre-push verification`:** unity build (1) + automation tests (2) + determinism gate (3) + soak (`verify_all.ps1`). MCP smoke (6) since this is a new MCP-driven op shape.

### Out of scope for M28.10 (defer)

- Anim Blueprint / Widget Blueprint / Interface Blueprint variants. `BlueprintFactory` handles `BPTYPE_Normal` only; the other types route through `UAnimBlueprintFactory` / `UWidgetBlueprintFactoryNew` / `UBlueprintInterfaceFactory`. Each has its own determinism trapdoor catalog. Add when a concrete design.md driver surfaces.
- Mutating an existing BP's parent class. Different code path (`FBlueprintEditorUtils::ReparentBlueprint`); not in design.md scope.
- Stripping default-spawned events on create (`bSpawnDefaultBlueprintNodes=false` window). The seeded-NodeGuid + sorted-walk approach is sufficient; suppressing the events would diverge from "what the editor would create" with no concrete payoff.

---

## Shipped milestones — index

One line per shipped milestone. For full ship-record narratives (commit bodies, gate counts, fixture names, troubleshooting arcs), see `WIP_INVENTORY_archive.md`.

### Read-side: inventory pipeline + serializers (M1–M19)

- **M1 Bootstrap** (commit `ce82a6b`, 1.12.0 → 1.13.0) — `Util/AtomicFileWriter` added; engine path corrections.
- **M2 ProjectManifest** (commit `692fd9f`) — Phase 0 FAssetRegistry-only scan to `MANIFEST.md`.
- **M2 verify + BuiltPlugin sync** (commit `efb5613`) — engine rebuilt post-disk-full, DLL shipped.
- **M3 ProjectInventory (UBP family)** (commit `c06d02c`) — Phase 1 streaming load/introspect/emit/GC; UBlueprint family only first slice.
- **M3.1 ProjectInventory (BT/ST/UDS/UDE)** (commit `73d73e8`) — non-UBP Phase-1 widening for BugHunt-covered types.
- **M3.2 ProjectInventory (DT/EnvQuery/BT+ST detail/RPCs)** (commit `511de83`) — DataTable + EnvQuery typed handlers, BT per-node decorators/services walk, ST per-state task/transition/condition render.
- **M3.3 P0** (commit `077d846`) — coverage honesty for fallback (PSD / Chooser / SmartObj applicable markers).
- **M3.3 P1a ChooserTable typed handler** (commit `72a88f9`) — columns / rows / fallback / context / nested. Build.cs adds `WITH_CHOOSER_SUPPORT`.
- **M3.3 P1b PoseSearchDatabase typed handler** (commit `c47d8c6`) — Schema + DatabaseAnimationAssets + sampling ranges.
- **M3.3 P1c SmartObjectDefinition typed handler** (commit `0226089`) — Slots (offset/rotation/enabled, activity & runtime tags, etc.).
- **M3.3 Track A** (commit `a2c7df0`) — AnimBP.StateMachines + WidgetBP.WidgetTree rendering.
- **M4 AggregateInventory (core rollups)** (commit `ffc223a`) — INDEX + CLASS_TREE + DEPENDENCY_GRAPH + REPLICATION_MATRIX + HEALTH_REPORT + Scoreboard baseline.
- **M4.1 AggregateInventory (domain overviews)** (commit `c0fea0f`) — AI / ANIM / UI / GAS / STRUCTS_ENUMS overviews.
- **M5 DeepDumpCommandlet (Tier 2 on-demand)** (commit `44e1687`) — first Tier 2 scale lever; CLI `-run=DeepDump -Asset=<path>`.
- **M5.1 DeepDump + serializer fallback fix** (commits `fc35ee4` + `c8a1a9f`) — first DOW-content exercise; rendering fixes.
- **M5.2 StateTree DeepDump + serializer instance-data capture** (commits `2f174b3` + `dc27fc1`) — walks all three halves of every `FStateTreeEditorNode`.
- **M5.3 P0 StateTree serializer fidelity gaps** (commits `c1df8c7` + `c59c655` + `faa502d`) — UE 5.5+ LinkedAsset, etc.
- **M6 verify_determinism.ps1 (CI gate)** (commit `1793bea`) — PowerShell gate per brief §11A, runs Manifest + Inventory + Aggregate + DeepDump twin-run + diff.
- **M6.1 serializer determinism fix** (commit `18e5217`) — fixed 3/805 .meta.json files drifting (K2Node_CallFunction auto-regen).
- **M7 P0 ProjectPlugins commandlet** (commits `18f44a4` + `8044ca7`) — uplugin metadata; closes the plugin blind spot in static analysis.
- **M7 P1 ProjectPlugins native-type enumeration** (commits `1314ba2` + `28ddd4a`) — fills `NativeTypes[]` on each plugin sidecar.
- **M8 DeepDump sweep (shared renderer + -DeepDump flag)** (commits `0cdeb7a` + `05c9b6e`) — extracts the 1300-line DeepDump render path into shared `Public/TextExport/DeepDumpRenderer.{h,cpp}`.
- **M9 instanced-subobject tree in DeepDump** (commits `af66897` + `bd6e221`) — closes the M8-audit-surfaced silent-information-loss gap.
- **M10 INDEX.md upgrade (navigation entry point)** (commits `ba8284d` + `0dece7f`) — INDEX.md is now the actual nav hub.
- **M11 SmartObjectDefinition Tier 2** (commits `b588d8a` + `69cf9bc`) — first non-UBP/ST type to graduate to full Tier 2 detail.
- **M12 BehaviorTree Tier 2** (commits `1c271d3` + `a5696fa`) — second non-UBP/ST type to graduate.
- **M13 DataTable Tier 2** (commits `1622eee` + `493d08d`) — third non-UBP/ST type to graduate (per-row `UScriptStruct` content).
- **M14 ChooserTable Tier 2** (commits `e551500` + `a8aac56`) — fourth non-UBP/ST type to graduate.
- **M15 EnvQuery Tier 2** (commits `9b3a894` + `c7cb742`) — fifth non-UBP/ST type to graduate (legacy DOW exercises this with 4 EQS assets).
- **M16 StateTree serializer plumbing filter** (commits `b0d1f4a` + `5602eea`) — UberGraphFrame skip-list; closes 2026-04-19 audit finding #1.
- **M17 BlueprintImport SavePackage wiring + save guards** (commit `6c90c61`) — persists in-memory Blueprint mutations to .uasset; BS_Error guard.
- **M18.1 Per-graph NodeIds validation** (commit `bb044c9`) — fixes shared-set bug.
- **M18.2 CallFunction owner + CallDelegate round-trip** (commit `f258f7d`) — two deserializer fidelity fixes that unblock complex real-world edits.
- **M19.1 Data-carrier CDO walk (serialize + Tier 1 + Tier 2)** (commits `649d5ac` + `e25306c`) — closes the biggest analysis blind spot (GameplayEffect / GameplayAbility / DataAsset CDO values). 1.13.0 → 1.14.0.
- **M19.2.1 DeepDump DataAsset-instance fallthrough** (commits `0ab7a1f` + `968e570`) — single-asset DeepDump handles any UDataAsset-derived instance.

### Write-side: Python + reflection bridge + supervised loop + MCP (M21–M27)

- **M21 Python write-layer library** — SHIPPED 2026-04-20. `scripts/python_ops/` module tree (`blueprint_cdo.py` / `statetree.py` / `assets.py` / `level.py`); first ops: `set_bp_variable_default`, `set_component_property`, `set_instanced_subobject_property`, `compile_and_save_blueprint`, `rename_asset`, `create_child_bp`. See archive for full scope brief.
- **M22 BugHunt-driven Python op validation loop** — SHIPPED 2026-04-20 (late). See archive.
- **M23 Reflection Bridge (C++ write layer)** — SHIPPED 2026-04-21. `UBpxReflectionOps` UFUNCTIONs + Python ops bridged through. See archive.
- **M24 Supervised Edit Loop** — SHIPPED 2026-04-21. Plan validator + executor + M24.3 mechanical_diff oracle. See archive (incl. plan-validator + oracle intra-plan create fix at `cdaa0aeb` 2026-04-25).
- **M25.1 MCP server + tactical AI ops** — SHIPPED 2026-04-21 (13 tools). Includes `refresh_inventory` confirm-gated tool. See archive.
- **M25.2.1 `add_statetree_transition`** (commit `a30ac31`, 1.17.0) — Python op for StateTree transition authoring; sets the M28.2.x op shape.
- **MCP hang-fix arc (2026-04-21 evening)** — 6 commits `073d595` → `4964f2a` fixing pre-validation, confirmation gate, MCP UX, plus the pipe-deadlock root cause (redirect UE stdout/stderr via tempfiles + stdin to DEVNULL). See archive.
- **M26.0 research outcome** (2026-04-21) — Blueprint graph authoring primitives scoped. See archive.
- **M26.1.1** (2026-04-22) — invisible interface-stub override fix. See archive.
- **M26.1.2** (2026-04-22) — force_rebind determinism fixes (pin-GUID + GC + MakeUnique). See archive.
- **Unity-build ODR defuse arc** (2026-04-22) — first ODR defuse pass. (See also 1.27.1 `130601d9` for a follow-up defuse on `DoRenderDeep`.)
- **M27 Persistent editor bridge** — SHIPPED 2026-04-22. WebSocket-based. Pattern reused by M28.7's planned in-process automation runner. See archive.

### Author-side write ops (M28.x) and Mutable (M29.x)

- **M28 — design.md (combat-AI "squad with a brain") enabling ops** (scoped 2026-04-22). Umbrella in flight; see active phase table above.
- **M28.pre.1–.4 (matrix hardening)** (2026-04-23, working-tree, plus regression chase 1.19.8 → 1.19.9). Automation fix + post-apply content inspect + per-op soak + dual-engine fan-out.
- **M28.1 + M28.3-narrow + M28.9 — Flat Arena scope-bump closure** (2026-04-23). See archive.
- **M28.2 research outcome** (2026-04-23). See archive.
- **M28.2.1 shipped** (2026-04-23, 1.19.9 → 1.19.10). See archive.
- **M28.2.2 shipped** (2026-04-23, 1.19.10 → 1.19.11). See archive.
- **M28.2.3 `add_component_to_scs` shipped** (2026-04-23 commit `fb6a60e`, 1.19.11 → 1.19.12). See archive.
- **M28.2.4 `add_bp_interface` shipped** (2026-04-23, 1.19.12 → 1.19.13). See archive.
- **M28.2.5 docs sweep shipped** (commit `4308642`, no version bump) — closes M28.2 umbrella. See archive.
- **M28.3 research outcome** (2026-04-23 post-M29). See archive.
- **M28.3.1 shipped** (2026-04-23 post-M29, 1.20.1 → 1.21.0) — first node-spawn slice; `add_branch_node`. See archive.
- **M28.3.2 shipped** (2026-04-24, 1.21.0 → 1.21.1) — FunctionReference / VariableReference family. See archive.
- **M28.3.3 shipped** (2026-04-24, 1.21.1 → 1.21.2) — three independent K2Node types. See archive.
- **M28.3.4 shipped** (2026-04-24, 1.21.2 → 1.21.3) — `add_local_variable`; closes M28.3 catalog at 9 ops across 4 sub-phases. See archive.
- **M28.3.6 shipped** (2026-04-24, no version bump) — docs sweep close of M28.3 umbrella; worked example in `plans/`. See archive.
- **M28.5.0 research outcome** (2026-04-24). See archive.
- **M28.5.1 shipped** (2026-04-24, 1.21.3 → 1.22.0). See archive.
- **M28.5.2 shipped** (2026-04-24, 1.22.0 → 1.22.1). See archive.
- **M28.5.3 shipped** (2026-04-24, 1.22.1 → 1.22.2) — closes M28.5 EQS write-side catalog at 5 ops. See archive.
- **M28.4.0 research outcome** (2026-04-24). See archive.
- **M28.4.1 shipped** (2026-04-24, 1.22.2 → 1.23.0) — `create_curve_float` + `set_curve_float_keys`. See archive.
- **M28.4.2 shipped** (2026-04-24 commit `78135ef`, 1.23.0 → 1.24.0) — `create_data_asset_instance` + `set_data_asset_property`. See archive.
- **M28.4.3 shipped** (2026-04-24 commit `754dd32`, 1.24.0 → 1.25.0) — `create_user_defined_struct` + `add_uds_member` + `remove_uds_member` + `set_uds_member_default`; closes M28.4 catalog at 8 ops across 3 modules. See archive.
- **M28.6.0 research outcome** (2026-04-25, commit `ef9c7504`). See archive.
- **M28.6.1 shipped** (2026-04-25 commit `8df3b1b0`, 1.26.0 → 1.27.0) — `add_gameplay_tag` Python op + `AddGameplayTag` UFUNCTION + `list_gameplay_tags` MCP tool; new `WITH_GAMEPLAYTAGSEDITOR_SUPPORT` Build.cs gate; new `Config/Tags/*.ini` authoring; M28.pre.5 parity gate `verify_tag_author.ps1`. Closes M28.6 catalog at 1 op.
- **Unity-build ODR hot fix** (2026-04-27 commit `130601d9`, 1.27.0 → 1.27.1) — renames duplicate `DoRenderDeep` helpers (one per typed deep renderer) to renderer-prefixed names so unity-build merge units stop colliding. Hot fix on top of the M28.6.1 ship.
- **M28.10.0 research** (2026-04-27, working-tree) — FGuid::NewGuid() trapdoor catalog on fresh UBlueprint creation + NewObject naming + native vs BP parent-class resolution recipe + create_child_bp idempotence-tightening spec. Three trapdoors confirmed: `UBlueprint::BlueprintGuid` (`Kismet2.cpp:454`), default-spawned event NodeGuids (sorted by event name to defeat `TMultiMap` hash-bucket instability), UCS `K2Node_FunctionEntry` NodeGuid. `USCS_Node::VariableGuid` confirmed already-deterministic (md5 of InternalVariableName). Outcome section in active WIP_INVENTORY (not archive — M28.10.1 implementation needed it self-contained).
- **M28.6.2 shipped** (2026-04-28, 1.28.3 → 1.28.4) — Pure-MCP-server fix surfaced by the 2026-04-27 design.md MCP-only session against UE_DOW_Legacy: `list_gameplay_tags` reported `tag_count: 0` for `Config/Tags/AI.ini` despite four tags present. Root cause: the M28.6.1 regex `^\+(?P<list>(?:Restricted)?GameplayTagList)=` required the array-append `+` prefix, but UE's editor writes per-domain `Config/Tags/<X>.ini` files (each backed by its own standalone `UGameplayTagsList` instance — no cross-config-layer accumulation) without the `+`, while only `Config/DefaultGameplayTags.ini` (backed by `UGameplayTagsSettings`, which DOES accumulate) uses `+GameplayTagList=`. Fix: relax the prefix to optional in both the tag-line regex and the `GameplayTagRedirects` regex (`^\+?...`); single-file change in `scripts/blueprint-exporter-mcp/src/blueprint_exporter_mcp/tools/gameplay_tags.py`. New regression test `test_list_gameplay_tags_per_domain_no_plus_prefix` synthesizes both shapes side-by-side in a tempdir (DefaultGameplayTags.ini with `+`, Tags/AI.ini and Tags/Restricted.ini without) and asserts non-zero tag counts on the per-domain files plus correct `restricted` flag survival. Confirmed end-to-end against live UE_DOW_Legacy: AI.ini now reports `tag_count: 4` (`AI.Archetype.Flanker/Marksman/Rusher/Suppresser`); DefaultGameplayTags.ini still parses 49 tags + 3 redirects. Patch bump took the full 9-site sweep + dual-engine DLL rebuild (UE_DOW custom 23 s + stock UE 5.7 42 s, both `BUILD SUCCESSFUL`) + 3-location DLL install (BuiltPlugin/, BugHunt/, UE_DOW_Legacy/) so source and runtime stay in sync. All 55 pre-push gates in `verify_all.ps1 -IncludeDow` PASS in 710.8 s.
- **M28.13 shipped** (2026-04-27, 1.28.2 → 1.28.3) — Single highest-ROI op of the M28 catalog. One bridge UFUNCTION `UBpxReflectionOps::AddMacroInstanceNode(BP, GraphName, MacroGraph, Position) -> FBpxNodeResult` unblocks five design.md sections that were stuck on "iterates X → blocked" (BroadcastOrder/AssignRole iteration, ScorerScoringLoop, ConfidenceDecay, ConfidenceDecay+SharedPerception) because ForEachLoop is a macro instance, not an atomic K2Node — the M28.3.x catalog couldn't author it. Adjacent to the M28.3.x atomic K2Node spawn family in `ReflectionOps.cpp`; only structural delta is the pre-`AllocateDefaultPins` `MacroGraphReference.SetGraph(MacroGraph)` call so the inherited `UK2Node_Tunnel::AllocateDefaultPins` pin-mirror walk has the macro to iterate (without the pre-alloc set the node lands with zero pins). NodeGuid seeded `md5(<bp>:graph:<g>:macro:<macro_lib_path>:<x>,<y>)` — library path included so two different ForEachLoop variants from different libraries don't collide; `SeedPinGuidsForNode` runs AFTER `AllocateDefaultPins` so the mirrored pins (whose count + names depend on the macro's signature) get deterministic PinIds. Defensive bridge-side `GT_Macro` check rejects non-macro graphs. Idempotent on seeded NodeGuid. Python op `add_macro_instance_node(bp_path, graph_name, macro_path, position)` in `blueprint_graph_nodes.py`; `macro_path` shape `"<lib_uobject_path>:<macro_name>"` like `"/Engine/EditorBlueprintResources/StandardMacros.StandardMacros:ForEachLoop"`. Macro-library resolution recovered mid-ship from `AttributeError: 'Blueprint' object has no attribute 'macro_graphs'` (soak round 1) — UBlueprint's `MacroGraphs` UPROPERTY is `CPF_Protected` so the Python binding does not surface it as `lib.macro_graphs`; switched to walking it via the existing reflection-bridge `get_array_length` + `get_object_property_value` accessor (same pattern as `blueprint_graph._resolve_graph` uses for `FunctionGraphs` / `UbergraphPages` / `ImplementedInterfaces`). Soak fixture `add_macro_instance_node.json` (against `BP_BpxTestGraphNodesCalls`, ForEachLoop into EventGraph, `skip_inspect=true`, `stable_keys=["node_guid"]`) initially failed round-1 baseline duplicate with stale-AssetRegistry `duplicate_asset returned None` against `BP_BpxTest_GraphNodesCallsScratch_Macro` (registry cached the path from the round-0 AttributeError leftover); recovered by renaming the scratch path to `BP_BpxTest_GraphNodesCallsScratch_MacroForEach` (fresh AR slot). plan_shape + mechanical_diff + plan_executor + `__init__` + smoke_test + CATALOG.md all wired. With M28.13 shipped, the design.md feasibility table goes from 5 "❌ iterates → blocked" entries to 5 "✅ achievable via add_macro_instance_node + connect_graph_pins" entries. All 53 pre-push gates in `verify_all.ps1 -IncludeDow` PASS in 707 s. Third install location `D:\Work\UE_DOW_Legacy\Plugins\BlueprintExporter\Binaries\Win64\` updated post-gate-run (initial copy attempt was blocked by a running Legacy editor's file lock; refreshed once the editor was closed).

- **M28.12 shipped** (2026-04-27, 1.28.1 → 1.28.2) — Surfaced by the design.md MCP-only test against UE_DOW_Legacy hitting the `UEnvQueryTest_BlueprintBase::ReceiveTestCondition` override wall (pre-M28.12 `add_bp_function` always created a fresh void/void function, wrong shape for inherited virtuals). One bridge UFUNCTION `UBpxReflectionOps::AddFunctionOverrideDeterministic(BP, FunctionName)` parallel to `OverrideInterfaceFunction` (M26.1): same `AddFunctionGraph<UClass>(BP, NewGraph, /*bIsUserCreated*/ false, ParentClass)` engine call but targets `Blueprint->ParentClass` instead of an `ImplementedInterfaces[]` entry, with the parent UFUNCTION resolved via `Blueprint->ParentClass->FindFunctionByName(FunctionName)` (engine helper walks the entire ancestor chain — any overridable virtual from any ancestor reachable). Validates the resolved UFUNCTION carries `FUNC_BlueprintEvent` (UHT applies that to `BlueprintImplementableEvent` and `BlueprintNativeEvent` UFUNCTIONs only — matches BP editor's "Override Function" menu visibility, rejects plain `BlueprintCallable` virtuals with a structured error). Auto-spawns a `K2Node_FunctionResult` (named `BpxFuncResult_<FunctionName>` for determinism) when the parent UFUNCTION has output / return params — `AddFunctionGraph<UClass>` only spawns Entry by default, mirrors the `OverrideInterfaceFunction` post-spawn pass. Distinct seed prefix `<bp>:override_func:<fn>:<slot>` (vs fresh-function `<bp>:func:<fn>:<slot>`) so a name collision between a fresh function and an override on the same BP — illegal at compile time but possible mid-authoring — produces distinct seeds and replay is byte-stable. One Python op `add_function_override(bp_path, function_name)` in `blueprint_structural.py` alongside `add_bp_function`. plan_shape + mechanical_diff + plan_executor + `__init__` + smoke_test + CATALOG.md all wired. New soak fixture against `BP_GAS_Ability` (UGameplayAbility child, BugHunt fixture) overriding `K2_ShouldAbilityRespondToEvent` (returns bool, takes 2 struct params — exercises the typed-pin signature mirror). One UHT-friendly fix mid-build: removed nested `/*bIsUserCreated*/` from a doc comment that UHT was parsing as a malformed character constant. With M28.12 shipped, design.md slices that depend on overriding inherited virtuals (every EQS test, GAS ability override, native-tick overrides on Pawns) are end-to-end authorable from a plan. All 52 pre-push gates in `verify_all.ps1 -IncludeDow` PASS in 702 s.

- **M28.11 shipped** (2026-04-27, 1.28.0 → 1.28.1) — One bridge UFUNCTION `UBpxReflectionOps::AddFunctionUserDefinedPin(BP, FunctionName, PinName, PinType, bDirectionIsOutput, DefaultValue)` wraps `K2Node_EditablePinBase::CreateUserDefinedPin` and reseeds the new `UEdGraphPin::PinId` from `md5(<bp>:<scope>:<fname>:userpin:<pname>:<dir>)` (scope ∈ `entry`/`result`/`custom_event`). Three Python ops: `add_function_input(bp, fn, pin, type, default)` → Entry node (`EGPD_Output`); `add_function_output(bp, fn, pin, type)` → Result node (`EGPD_Input`; auto-spawns Result with deterministic NodeGuid + pin IDs from `<bp>:func:<fn>:result` if missing — matches `AddFunctionGraphDeterministic`'s seed key for byte-identity across pure-then-promoted vs non-pure-from-create paths); `add_custom_event_input(bp, graph, event, pin, type, default)` → walks all `UbergraphPages` for a `K2Node_CustomEvent` whose `CustomFunctionName == event_name` (`EGPD_Output`). Idempotence via inline `UserDefinedPins` walk by name (engine's `UserDefinedPinExists` is not `BLUEPRINTGRAPH_API` exported, would LNK2019 across the module boundary; the inline walk has identical semantics). Direction param surfaces as `bool bDirectionIsOutput` not `EEdGraphPinDirection` because the enum is not in DOW's UE Python stub and BlueprintCallable enum reflection doesn't survive Python automatically. plan_shape + mechanical_diff + plan_executor + `__init__` + smoke_test + CATALOG.md all wired. Three new soak fixtures (`add_function_input.json` / `add_function_output.json` / `add_custom_event_input.json`) all `skip_inspect=true` because the existing DeepDumpRenderer surfaces user-defined pins as part of the function/event signature header in a form that isn't grep-friendly. With M28.11 shipped, design.md's encounter-director ↔ AI.Order custom-event channel (item #1) drops the member-variable handshake workaround. All 51 pre-push gates in `verify_all.ps1 -IncludeDow` PASS in 702 s.

- **M28.10.1 shipped** (2026-04-27, 1.27.1 → 1.28.0) — `UBpxReflectionOps::CreateBlueprintClassDeterministic` UFUNCTION (`ReflectionOps.cpp:~3920`) post-create reseeds the documented FGuid trapdoors via `SeedGuidFromJoined` + `SeedPinGuidsForNode` and a generic FProperty walker `SeedAllFGuidProperties` that catches any UPROPERTY-declared FGuid on the UBlueprint / UBlueprintGeneratedClass / SkeletonGeneratedClass / SimpleConstructionScript / UEdGraphs. To suppress a class of auto-generated random state we couldn't fully tame (each default-spawned `UK2Node_Event` carried ~177 bytes of post-NodeGuid drift attributable to FUniqueObjectGuid annotations or UFunction-related GUIDs whose source we couldn't pinpoint after a long debug arc), the bridge also flips `UBlueprintEditorSettings::bSpawnDefaultBlueprintNodes` to false for the duration of the create call — plan authors author events explicitly via `add_custom_event_node` (M28.3.3) which has its own seeding. Save is done in C++ directly (no second compile-and-save from Python) so the seed pass is the last write before SavePackage. `create_blueprint_class(parent_path, new_bp_path)` Python op (`assets.py`) accepts native `/Script/<Module>.<Class>` and BP `/Game/<path>/<Name>[.<Name>_C]` parents (auto-suffixes the `_C` form for BP-asset-shorthand). `create_child_bp` converts to a back-compat alias (delegates to `create_blueprint_class` after the same `_C` normalization); strict ParentClass match via C++ pointer equality on `Existing->ParentClass` closes the pre-M28.10.1 `BlueprintGeneratedClass.get_super_class` Python-binding caveat. `scripts/soak_template.py` extended with `soak.recreate_between_rounds: true` flag (and `_file_level_delete(evict_in_memory=True)`) for ops that want true create-path soak coverage; preserved as a diagnostic tool. New soak fixture `scripts/inspect_fixtures/create_blueprint_class.json` uses the M28.4.x idempotence-only pattern (duplicate + skip via parent match) — recreate_between_rounds verified the seed pass works end-to-end during development but surfaced ~16 bytes of residual FGuid drift per round somewhere in the post-export annotation table or asset-registry tag block (source unidentified; production single-create usage is unaffected, documented in CATALOG.md as a known limitation). plan_shape + mechanical_diff + plan_executor + `__init__` + smoke_test all wired. CATALOG.md row added; obsolete caveat at `:1431` removed. Unblocks design.md's `BP_EncounterDirector` (pillar 1) + `UAIActionScorer` (pillar 2).

- **M29 — Mutable / CustomizableObject Tier 2 support** — SHIPPED 2026-04-23. Five sub-phases: M29.0 research → M29.1 UCustomizableObjectInstance renderer (commit `d8e8bcb`) → M29.2 UCustomizableObject renderer (1.19.14 → 1.20.0) → M29.3 UCustomizableObjectMacroLibrary renderer (1.20.0 → 1.20.1 patch) → M29.4 determinism gate extension (no version bump) → M29.5 close-out. See archive.
- **M29.6 engine-agnostic Mutable renderer refactor** — SHIPPED 2026-04-25. Reopened M29 umbrella to ship one BuiltPlugin DLL that handles CO/COI/COML in any project. Five code slices: M29.6.1 `UFunctionCall.*` helpers + tests (commit `19b3a03`) → M29.6.2 UCOI port (commit `47b370a`) → M29.6.3 UCO port → M29.6.4 mechanical strip project-wide → M29.6.5 finalization (1.25.0 → 1.26.0 minor bump). MutableSample byte-identity confirmed at every step. See archive.

### Side-arcs / fidelity audits / non-milestone work

- **DOW calibration slice** (2026-04-18, ephemeral output) — 18475 assets, 805 logic-bearing.
- **DOW_Legacy fidelity audit** (2026-04-19) — 4 findings; finding #1 → M16, #3 resolved silently, #4 unblocked M15. See archive § "Fidelity audit findings".
- **DOW_Legacy export procedure** (2026-04-19) — stock UE 5.7 build; output outside the repo at `D:/Work/_dow_legacy_inventory/`. See active file § Reference patterns.
- **Usability audit** (2026-04-19) — audited committed `ProjectInventory_DOW/` for real-world bug-hunt utility. Surfaced Ultra_Dynamic_Sky replication anomalies and the 0-RPCs-in-DOW signal. See archive.
- **MCP Perforce rule side-arc** (2026-04-23, commits `51c8648` + `fb8a6fd`) — explicit rule: never initiate P4 ops silently. See archive.
- **Cross-session .uasset drift investigation** (2026-04-23 later, commit `d1a879d`). Outcome deferred. See archive.

---

## Reference patterns + workflow gotchas (durable)

### Standard build flow (used by every milestone since M2)

**Critical context (re-discovered M28.15 2026-04-29 the hard way):** the repo ships TWO engine-targeted DLL builds for the same plugin source. They are NOT interchangeable — wrong build at an install location → `Plugin 'BlueprintExporter' failed to load because module 'BlueprintExporter' could not be found` + `GetLastError=126` modal at editor startup. The dual-engine install matrix is:

| Install location | Engine target | Build source |
|---|---|---|
| `BuiltPlugin/Binaries/Win64/` | UE_DOW **custom** engine | DOW build (step 3) — also seen by `D:\Work\UE_DOW\game\` via the plugin junction |
| `BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64/` | **Stock UE 5.7** | Stock-5.7 build (step 5) — `verify_all.ps1` runs BugHunt gates against `$StockEngine` (`C:\Program Files\Epic Games\UE_5.7\Engine\...`) |
| `D:\Work\UE_DOW_Legacy\Plugins\BlueprintExporter\Binaries\Win64\` (off-repo) | **Stock UE 5.7** | Stock-5.7 build (step 5) — flat copy, NOT a junction; needs editor closed before refresh |

```
# 1. Sync Source → BuiltPlugin (only when Source changed)
cp <changed .h/.cpp files> blueprint-exporter/BuiltPlugin/Source/...

# 2. Build against UE_DOW custom engine
mkdir -p blueprint-exporter/_build_output
"/d/Work/UE_DOW/engine/Build/BatchFiles/RunUAT.bat" BuildPlugin \
  -Plugin="D:\Work\blueprintexporter\blueprint-exporter\BuiltPlugin\BlueprintExporter.uplugin" \
  -Package="D:\Work\blueprintexporter\blueprint-exporter\_build_output" \
  -TargetPlatforms=Win64 -Rocket

# 3. Copy DOW-target artefacts → BuiltPlugin/ ONLY (do NOT also copy to BugHunt — wrong engine)
cp blueprint-exporter/_build_output/Binaries/Win64/UnrealEditor-BlueprintExporter.dll \
   blueprint-exporter/BuiltPlugin/Binaries/Win64/
cp blueprint-exporter/_build_output/Binaries/Win64/UnrealEditor.modules \
   blueprint-exporter/BuiltPlugin/Binaries/Win64/
rm -rf blueprint-exporter/_build_output

# 4. Build against stock UE 5.7 (separate output dir so artefacts don't clobber DOW's)
mkdir -p blueprint-exporter/_build_output_5_7
"/c/Program Files/Epic Games/UE_5.7/Engine/Build/BatchFiles/RunUAT.bat" BuildPlugin \
  -Plugin="D:\Work\blueprintexporter\blueprint-exporter\BuiltPlugin\BlueprintExporter.uplugin" \
  -Package="D:\Work\blueprintexporter\blueprint-exporter\_build_output_5_7" \
  -TargetPlatforms=Win64 -Rocket

# 5. Stock-5.7 artefacts → BugHunt + UE_DOW_Legacy + sync the .uplugin manifests too
#    (the .uplugin sync is REQUIRED — both downstream installs drift silently otherwise;
#    M28.15 found BugHunt at 1.27.1 and UE_DOW_Legacy at 1.28.3 after multiple ships)
cp blueprint-exporter/_build_output_5_7/Binaries/Win64/UnrealEditor-BlueprintExporter.dll \
   blueprint-exporter/BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64/
cp blueprint-exporter/_build_output_5_7/Binaries/Win64/UnrealEditor.modules \
   blueprint-exporter/BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64/
cp blueprint-exporter/BuiltPlugin/BlueprintExporter.uplugin \
   blueprint-exporter/BugHunt/TestProject/Plugins/BlueprintExporter/BlueprintExporter.uplugin

cp blueprint-exporter/_build_output_5_7/Binaries/Win64/UnrealEditor-BlueprintExporter.dll \
   "D:/Work/UE_DOW_Legacy/Plugins/BlueprintExporter/Binaries/Win64/"
cp blueprint-exporter/_build_output_5_7/Binaries/Win64/UnrealEditor.modules \
   "D:/Work/UE_DOW_Legacy/Plugins/BlueprintExporter/Binaries/Win64/"
cp blueprint-exporter/BuiltPlugin/BlueprintExporter.uplugin \
   "D:/Work/UE_DOW_Legacy/Plugins/BlueprintExporter/BlueprintExporter.uplugin"

rm -rf blueprint-exporter/_build_output_5_7

# 6. Rebuild BugHunt-side test modules (BlueprintExporterTests + whatever else).
#    Engine choice here matches whatever BugHunt.uproject targets — stock UE 5.7.
"/c/Program Files/Epic Games/UE_5.7/Engine/Build/BatchFiles/Build.bat" UnrealEditor Win64 Development \
  -Project="D:\Work\blueprintexporter\blueprint-exporter\BugHunt\TestProject\BugHunt.uproject" \
  -WaitMutex
```

Typical timings: step 2 ≈ 25 s, step 4 ≈ 45 s, step 6 ≈ 5–20 s,
everything else instant. Engine rebuilds are NOT in this flow — both
engines are assumed already current from prior verify sessions.

### Policy (decided, don't re-litigate)


- **BugHunt stays the first-pass test bed.** 20 committed fixtures
  exercise UBP + BT + ST + UDS + UDE through every slice. DOW is
  for surfaces BugHunt can't exercise (Motion Matching, Choosers,
  SmartObjects, deep inheritance). Pattern: build against DOW fresh
  content first, then add a BugHunt fixture if the feature warrants
  a regression test.
- **DOW calibration slice — EXECUTED 2026-04-18.** See the "DOW
  calibration slice" entry in the Status section above. Deployment
  gate (brief §12.4) cleared; the M3.3 P0 / P1 sub-slices are how
  we're responding to the slice findings. The original brief
  prescription of `-Filter=/Game/AI/*` didn't apply (DOW has no such
  folder); we used `-Filter=/Game/_ThirdParty/GASP_example/` instead
  because that's where DOW's Motion Matching / Chooser / StateTree
  content actually lives.
- **Two-tree invariant.** `D:\Work\blueprintexporter\blueprint-exporter`
  is full read/write; `D:\Work\UE_DOW` is read+execute only, with the
  single plugin-junction exception at `D:\Work\UE_DOW\game\Plugins\BlueprintExporter`.
  Details in `PROJECT_INVENTORY_BRIEF.md` §0 / §0.1.
- **Build flow.** First rebuild after any change:
  `"/d/Work/UE_DOW/engine/Build/BatchFiles/Build.bat" UnrealEditor Win64 Development -Project="D:\Work\blueprintexporter\blueprint-exporter\BugHunt\TestProject\BugHunt.uproject" -WaitMutex`.
  See `blueprint-exporter/CLAUDE.md` §Building & Deploying for the
  full shipping-plugin build flow (`RunUAT.bat` + BuiltPlugin sync).
- **Commit discipline.** One commit per milestone. `feat(blueprint-exporter):`
  for new commandlet code, `docs(blueprint-exporter):` for doc
  updates. Keep commit subjects imperative and under ~70 chars.

### Key paths

| What | Where |
|---|---|
| Source of truth plan | `PROJECT_INVENTORY_BRIEF.md` (this repo) |
| Plugin version | `BlueprintExporter.uplugin` → `"Version": 13`, `"VersionName": "1.13.0"` |
| Shared atomic-write helper | `Source/BlueprintExporter/Public/Util/AtomicFileWriter.h` |
| ProjectManifest commandlet (Phase 0) | `Source/BlueprintExporter/Private/Commandlets/ProjectManifestCommandlet.cpp` |
| ProjectInventory commandlet (Phase 1) | `Source/BlueprintExporter/Private/Commandlets/ProjectInventoryCommandlet.cpp` |
| AggregateInventory commandlet (Phase 2) | `Source/BlueprintExporter/Private/Commandlets/AggregateInventoryCommandlet.cpp` |
| Test bed for M2/M3/M3.1/M3.2/M4/M4.1/M3.3/M5 | `BugHunt/TestProject` (20 committed fixtures; uproject enables `Chooser` + `PoseSearch` + `SmartObjects` optional; `UnrealEditor.target` rebuilt at M3.3 P1c — M5 didn't need a target rebuild, added no module deps) |
| DeepDump commandlet (Tier 2, M5) | `Source/BlueprintExporter/Private/Commandlets/DeepDumpCommandlet.cpp` |
| Determinism CI gate (M6) | `scripts/verify_determinism.ps1` |
| Engine binary | `D:\Work\UE_DOW\engine\Binaries\Win64\UnrealEditor-Cmd.exe` |
| DOW uproject (read-only except for the plugin-junction exception) | `D:\Work\UE_DOW\game\UE_DOW.uproject` |
| Build.cs (module deps) | `Source/BlueprintExporter/BlueprintExporter.Build.cs` — `AIModule` (M3.1), `WITH_STATETREE_SUPPORT` (M3.1), `WITH_CHOOSER_SUPPORT` + `Chooser` dep (M3.3 P1a), `WITH_POSESEARCH_SUPPORT` + `PoseSearch` dep (M3.3 P1b), `WITH_SMARTOBJECTS_SUPPORT` + `SmartObjectsModule` + `WorldConditions` deps (M3.3 P1c), `UMG` + `UMGEditor` deps (M3.3 Track A; no gate — ship-with-engine) |
| DOW plugin junction | `D:\Work\UE_DOW\game\Plugins\BlueprintExporter` → `…BuiltPlugin\`. Recreated 2026-04-18 after Perforce resync wiped it. PowerShell `New-Item -ItemType Junction` (MSYS `mklink /J` fights bash quoting) |
| Stock UE 5.7 (for DOW_Legacy) | `C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe`. Added 2026-04-19. Legacy uproject targets stock 5.7 (`EngineAssociation: "5.7"`) not the 10C custom engine (`EngineAssociation: ""`). |
| Stock-5.7 BuiltPlugin (for DOW_Legacy) | `blueprint-exporter/_build_output_5_7/` — plugin package built against stock UE 5.7 via `RunUAT BuildPlugin`. Untracked. Rebuild from source whenever main-side source changes if legacy re-exports are needed. |
| DOW_Legacy uproject (read-only) | `D:\Work\UE_DOW_Legacy\UE_DOW.uproject` — separate Perforce depot; worked-on WIP that shouldn't land on main. `EngineAssociation: "5.7"`, no project source synced (`Source/` dir absent — pre-built `UnrealEditor-EditorModule_SurfaceDefinition.dll` ships in `Binaries/Win64`). Do NOT run `Build.bat` against it — UBT fails without the module source. |
| DOW_Legacy plugin junction | `D:\Work\UE_DOW_Legacy\Plugins\BlueprintExporter` → `_build_output_5_7\`. Created 2026-04-19. |
| DOW_Legacy export output | `D:\Work\_dow_legacy_inventory\` — **outside the blueprint-exporter repo by design** (legacy content should not land on main). 2604 logic-bearing assets, 2183 `.deep.md`, 0 failed / 0 partial / 100% coverage on the 2026-04-19 sweep. |

### Known blockers


- _None._ UE_DOWEditor target is current (rebuilt 2026-04-18, 204
  actions, matches engine BuildId `6efc257b-…`). BugHunt target
  rebuilt at M3.3 Track A (~30 s, 43 actions) to pick up the
  UMG/UMGEditor deps on top of the prior Chooser / PoseSearch /
  SmartObjects bakes; M5 and M6.1 added no module deps so no new
  target rebuilds were required. `BuiltPlugin/` holds the M15 DLL
  (~3.38 MB). All three DLL locations (BuiltPlugin, BugHunt plugin
  copy, BugHunt project Binaries) match current engine BuildId.

### Legacy depot export procedure (2026-04-19)


Reproducible after `/clear`. Legacy's plugin DLLs are built against
stock UE 5.7, so we can't use the 10C custom engine for it — we use
the Epic Launcher install at `C:\Program Files\Epic Games\UE_5.7\`.

```bash
# 1. Rebuild BlueprintExporter against stock UE 5.7 (if Source/ changed
#    since the last legacy export). Produces _build_output_5_7/.
"/c/Program Files/Epic Games/UE_5.7/Engine/Build/BatchFiles/RunUAT.bat" \
  BuildPlugin \
  -Plugin="D:\Work\blueprintexporter\blueprint-exporter\BuiltPlugin\BlueprintExporter.uplugin" \
  -Package="D:\Work\blueprintexporter\blueprint-exporter\_build_output_5_7" \
  -TargetPlatforms=Win64 -Rocket

# 2. Junction the stock-5.7 build into the legacy depot's Plugins/
#    (one-time — survives as long as Perforce doesn't wipe it).
powershell -Command "New-Item -ItemType Junction \
  -Path 'D:\Work\UE_DOW_Legacy\Plugins\BlueprintExporter' \
  -Target 'D:\Work\blueprintexporter\blueprint-exporter\_build_output_5_7'"

# 3. Run the full pipeline using the stock UE 5.7 editor binary.
#    Output goes OUTSIDE the blueprint-exporter repo by design —
#    legacy content shouldn't land on main.
MSYS_NO_PATHCONV=1 "/c/Program Files/Epic Games/UE_5.7/Engine/Binaries/Win64/UnrealEditor-Cmd.exe" \
  "D:\Work\UE_DOW_Legacy\UE_DOW.uproject" \
  -run=ProjectInventory -OutDir="D:\Work\_dow_legacy_inventory" -DeepDump \
  -nullrhi -unattended -nopause -nosplash -nosound -stdout

# 4. Phase 2 + plugins (fast — no asset loads).
MSYS_NO_PATHCONV=1 "/c/Program Files/Epic Games/UE_5.7/Engine/Binaries/Win64/UnrealEditor-Cmd.exe" \
  "D:\Work\UE_DOW_Legacy\UE_DOW.uproject" \
  -run=AggregateInventory -OutDir="D:\Work\_dow_legacy_inventory" \
  -nullrhi -unattended -nopause -nosplash -nosound -stdout
MSYS_NO_PATHCONV=1 "/c/Program Files/Epic Games/UE_5.7/Engine/Binaries/Win64/UnrealEditor-Cmd.exe" \
  "D:\Work\UE_DOW_Legacy\UE_DOW.uproject" \
  -run=ProjectPlugins -OutDir="D:\Work\_dow_legacy_inventory" \
  -nullrhi -unattended -nopause -nosplash -nosound -stdout
```

Notes:
- **Do NOT run `Build.bat` against `UE_DOW_Legacy/UE_DOW.uproject`**.
  Legacy is missing project-module source (`EditorModule_SurfaceDefinition`
  — only the prebuilt DLL ships in `Binaries/`), and UBT fails pre-
  compile with "Could not find definition for module". Pre-built plugin
  DLLs in the legacy depot are already BuildId-matched against stock
  UE 5.7, so no rebuild is needed.
- **No `-EnablePlugins=BlueprintExporter` flag for legacy.** The legacy
  uproject doesn't pin it as disabled (unlike main DOW's uproject), and
  the junction makes the plugin auto-discoverable.
- **Asset counts on the 2026-04-19 run**: Blueprint=1694, PSD=308,
  UDS=48, UDE=40, ABP=31, Chooser=23, CRBP=17, WBP=10, ST=7, EQS=4,
  SOD=1. Total logic-bearing=2183 (matches `.deep.md` file count).

### Ephemeral artifacts (safe to delete, intentionally untracked)


- `blueprint-exporter/ProjectInventory/` — smoke-test output from the
  latest BugHunt run through M3.3 Track A. Contains:
  - `Assets/Game/…` tree with 18 `.md` + 18 `.meta.json` pairs
    (15 UBP + 3 non-UBP: `BT_BugHunt`, `E_BugHuntEnum`,
    `S_BugHuntStruct`; `ST_BugHunt` in `PARTIAL_LOADS.md` — fixture
    has no EditorData).
  - Top-level aggregates: INDEX, CLASS_TREE, DEPENDENCY_GRAPH (+ .dot),
    REPLICATION_MATRIX, HEALTH_REPORT, PARTIAL_LOADS, AI / ANIM / UI /
    GAS / STRUCTS_ENUMS overviews, SCOREBOARD_BASELINE.json.
- `blueprint-exporter/ProjectInventory_DOW/` — DOW calibration slice
  output (2026-04-18). Contains:
  - `MANIFEST.md` (Phase 0 — 18475 assets across 14 logic-bearing
    classes, top-level folder counts, largest-50 table).
  - `Assets/Game/_ThirdParty/GASP_example/…` tree — 363 `.md` +
    363 `.meta.json` pairs spanning every logic-bearing class we care
    about (154 PSD, 107 Blueprint, 24 UDS, 23 UDE, 19 AnimBP, 16 CR,
    12 Chooser, 4 Widget, 3 ST, 1 SmartObj).
  - Aggregate rollups (11 of them, no GAS_OVERVIEW since GASP has no
    GAS content — the conditional emit works correctly).
  Safe to delete; recreated on the next DOW slice run.
  `SCOREBOARD_BASELINE.json` is intentionally kept across runs per
  brief §11A.
- `blueprint-exporter/_*.log` — build / commandlet stdout captures
  from M1 → M5 verification cycles. The M3.3 batch is named
  `_m3_3_p0_*`, `_m3_3_p1a_*`, `_m3_3_p1b_*`, `_m3_3_p1c_*`,
  `_m3_3_trackA_*`, `_dow_m0_manifest.log`, `_dow_m1_slice.log`,
  `_dow_m2_agg.log`, `_dow_rebuild.log`. M5 batch is named
  `_m5_buildplugin.log`, `_m5_deep_bp_netrep_run{1,2,3}.log`,
  `_m5_deep_bt.log`, `_m5_deep_nodezoo.log`, `_m5_deep_widget.log`.
  M6 batch is `_m6_verify_bughunt.log`, `_m6_verify_dow_gasp.log`,
  `_dow_full_verify.log`. M6.1 batch is `_m6_1_buildplugin.log`,
  `_m6_1_verify_bughunt.log`, `_m6_1_verify_dow_full.log`,
  `_m6_2_verify_dow_full.log`. All safe to delete.
- `blueprint-exporter/_determinism_{A,B}/` + `_determinism_{A,B}_logs/`
  — twin-run output from the last `verify_determinism.ps1 -KeepOnSuccess`
  invocation. Either tree can be promoted to `ProjectInventory_DOW/`
  if we decide to commit the canonical deliverable.
- `blueprint-exporter/ProjectInventory/Deep/` — M5 smoke-test output.
  Contains one `.deep.md` per asset we ran DeepDump against
  (`BP_NetRep.deep.md`, `BP_NodeZoo.deep.md`, `BP_WidgetTree.deep.md`,
  `BT_BugHunt.deep.md`). Safe to delete; regenerated on demand.
- `blueprint-exporter/Characters/` at the repo root — pre-existing
  leftover export output from a prior unrelated test run.

### Workflow gotchas durable across the M21–M29 arc

Pulled from session blocks. Carry forward to next session.

- **MSYS2 path-munging on `-Asset=/Game/Foo` is REAL** — use the PowerShell tool (or `MSYS_NO_PATHCONV=1` in Bash) for any UE invocation that takes a `/Game/...` arg. Bit us once during M3.3 P1a setup; bit us again during M28.x Legacy testing.
- **Bash doesn't have `tee` / `head` / `tail` / `cat` / `grep` / `wc` in this MSYS2 install** — use `Read`, the `Grep` tool, or PowerShell instead. Don't pipe to those binaries; they don't exist.
- **`pwsh` is not on Bash's PATH** — invoke as `& "C:\Program Files\PowerShell\7\pwsh.exe"` from PowerShell, or via the cygpath form from Bash.
- **MutableSample uses UE_DOW engine** despite `EngineAssociation=5.7` in its uproject. The `MutableSample/Plugins/BlueprintExporter` junction points at `BuiltPlugin/`, which carries the UE_DOW-engine flavor; if you need to test against stock UE 5.7, junction from `_build_output_5_7/` instead.
- **BugHunt plugin `.uplugin` pins `EngineVersion: 5.7.0` + `Installed: true`** — UE_DOW (5.7.4-572648) refuses to load it. Use stock 5.7 for any BugHunt gate.
- **Bridge smoke needs an interactive editor running** — `python scripts/smoke_bridge.py` connects to `ws://127.0.0.1:1337`. Launch `UnrealEditor.exe BugHunt.uproject` with the bridge port enabled before running the smoke.
- **DOW needs `-stdout -log` to emit to stdout.** Without `-stdout` UE writes to its log file only; `>` redirect captures nothing. BugHunt is more forgiving but use `-stdout` for both to match.
- **Plugin load needs baked-in target.** Adding a module dep to `Build.cs` requires rebuilding the consuming project's target (BugHunt in our case) so the `.target` receipt lists the new plugin. `.uplugin` Optional deps don't substitute. Symptom: `LogWindows: Missing import: UnrealEditor-<Module>.dll` during plugin load. Fix: `Build.bat UnrealEditor Win64 Development -Project=BugHunt.uproject -WaitMutex` (~27 s).
- **DOW's `UE_DOW.uproject` disables BlueprintExporter.** Pins `"BlueprintExporter": { "Enabled": false }`. Always pass `-EnablePlugins=BlueprintExporter` when running commandlets against DOW until someone flips it upstream.
- **Engine re-syncs wipe plugin junctions.** `D:\Work\UE_DOW\game\Plugins\BlueprintExporter` is local-only; after any Perforce sync that touches `game/Plugins/` the junction is gone. Recreate with `New-Item -ItemType Junction -Path '...' -Target '...'`.
- **Engine rebuild invalidates plugin DLLs.** When UGS or manual builds produce a new engine BuildId GUID, every plugin DLL stamped with the old CL becomes "stale" and UE silently skips loading them. If a *required* plugin is stale, engine init aborts with `LogPluginManager: Error: Plugin 'X' failed to load because module 'X' could not be found`. Fix: rebuild the consuming project's target against the new engine via `Build.bat <Target> Win64 Development -Project=... -WaitMutex`.

---

## Architecture notes (Project Inventory)

Steady-state architecture of the inventory subsystem. Captures *what the system IS*, not *what was just shipped*. Per-milestone progress narrative is in the archive.

**Three-phase commandlet pipeline.** Source of truth is `PROJECT_INVENTORY_BRIEF.md`; this section is the anchor.

- **Phase 0 — `ProjectManifest`** (`Source/BlueprintExporter/Private/Commandlets/ProjectManifestCommandlet.cpp`). FAssetRegistry-only scan, no asset loads. Writes a single `MANIFEST.md` listing total + logic-bearing counts by class, per-folder counts, top-N largest assets. Args: `-OutDir=<dir>` (required), `-MountPoint=/Game` (default), `-TopN=50` (default). Logic-bearing class set is matched on `FAssetData::AssetClassPath.GetAssetName()` FName only (package path ignored; class-name match is stable across module reshuffles): Blueprint, AnimBlueprint, WidgetBlueprint, ControlRigBlueprint, BehaviorTree, StateTree, EnvQuery, SmartObjectDefinition, ChooserTable, PoseSearchDatabase, UserDefinedStruct, UserDefinedEnum, DataTable. ~1.2 s on BugHunt; ~1 s on DOW (registry-only).

- **Phase 1 — `ProjectInventory`** (`Source/BlueprintExporter/Private/Commandlets/ProjectInventoryCommandlet.cpp`). Streams through the registry, loads each in-scope asset, runs the appropriate typed serializer, renders Tier 1 Markdown, writes `<Path>.md` + `<Path>.meta.json` via `SaveStringAtomic`, and `CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS)` every N assets (`-GcEvery=<N>` default 50, brief §11A Option A). Args: `-OutDir` (required), `-MountPoint=/Game`, `-Filter=<prefix>` (optional package-path prefix), `-Resume` (skips assets whose `.meta.json` already exists), `-DeepDump` / `-SweepDeepDump` (enables Tier 2 inline). Failures aggregated to `FAILED_LOADS.md` (cast failures) + `PARTIAL_LOADS.md` (serializer/write failures); commandlet always returns 0 on framework success.

- **Phase 2 — `AggregateInventory`** (`Source/BlueprintExporter/Private/Commandlets/AggregateInventoryCommandlet.cpp`). Reads `.meta.json` sidecars from the Phase-1 tree (no asset re-loads, just JSON-over-files text processing), builds aggregate indexes, writes rollups: `INDEX.md` (nav entry point + Run Scoreboard + counts by subclass + counts by top-level folder + largest connection hubs + links), `CLASS_TREE.md` (native-parent grouping + BP→BP chains), `DEPENDENCY_GRAPH.md` + `dependency_graph.dot` (per-asset hard/soft refs in/out), `REPLICATION_MATRIX.md` (every replicated variable across the project), `HEALTH_REPORT.md` (coverage gaps + FAILED/PARTIAL_LOADS counts), `SCOREBOARD_BASELINE.json` (persisted baseline for §11A scoreboard deltas), domain overviews (`AI_OVERVIEW.md` / `ANIM_OVERVIEW.md` / `UI_OVERVIEW.md` / `GAS_OVERVIEW.md` / `STRUCTS_ENUMS.md`).

- **Phase "P" — `ProjectPlugins`** — plugin sidecars per discovered plugin (uplugin metadata + native-type enumeration). Sibling phase to 0–2. M7 P0 / P1.

**Tier 1 vs Tier 2.** Tier 1 = always-on per-asset Markdown summary written by Phase 1 (structural shape, signatures, replication info, references). Tier 2 = on-demand `.deep.md` per-asset deep dump written by `DeepDumpCommandlet` or Phase-1's `-DeepDump` sweep (full pin-by-pin graph content, instanced subobject trees, per-state task content for ST). Tier 2 size is ~5–10 MB for DOW canonical.

**Determinism rules** (brief §8). All output must be byte-identical across twin runs. Enforcement:
- Functions / macros / interfaces / dependencies sorted alpha at render time; variables keep declaration order; components keep SCS tree order.
- `ExportInfo.ExportTimestamp` blanked after `SerializeBlueprint` (the underlying serializer stamps `FDateTime::UtcNow().ToIso8601()` which would drift every run).
- `ContentHash` computed with timestamp blanked already.
- No GUIDs in Markdown (they stay in `.meta.json`); no absolute paths anywhere.
- **Twin-run gate** = `scripts/verify_determinism.ps1`: runs Manifest + Inventory + Aggregate + ProjectPlugins twice into separate trees, then `diff -ruN` and exits 0 iff byte-identical. Optional `-SweepDeepDump` upgrades Phase 1 to the sweep variant.
- **Per-op soak gate** (M28.pre.3) = `scripts/soak_template.py`: parameterised round-1 vs round-2 md5 + entry_guid stability check on a fixture, catches within-session non-determinism that would slip past the twin-run gate (e.g. `MakeUnique` GC traps).

**Coverage accounting** (brief §4). `.meta.json` carries a `coverage` object with `variables` / `functions` / `components` / `graphs` buckets (each `{total, documented}`) plus a `specialized` object listing applicable / documented subclass-specific sections (e.g. `AnimBP.StateMachines`, `WidgetBP.WidgetTree`). `overallPct` rolls it up. Used by `HEALTH_REPORT.md` + INDEX scoreboard.

**File trio per asset.** Phase 1 emits `<Path>.md` (Tier 1 Markdown summary) + `<Path>.meta.json` (full `FExportedBlueprint::ToJson()` + coverage). Phase 1 with `-DeepDump` or `DeepDumpCommandlet` adds `<Path>.deep.md` (Tier 2 pin-level dump). `.meta.json` is the "done" marker for `-Resume` (written after `.md`).

**Write-side architecture (M21+).** Plugin is the **READ** layer (deep dumps, rollups, deterministic diffs). The **WRITE** layer is the Python op library (`scripts/python_ops/`) shelling to `UnrealEditor-Cmd.exe -run=pythonscript`, which uses UE's own save/compile paths via `unreal.EditorAssetLibrary` / `BlueprintEditorLibrary` and the `UBpxReflectionOps` UFUNCTION bridge. M24 supervised loop wraps it with plan validator + executor + mechanical_diff oracle. M25.1 MCP server exposes 13 zero-UE-process retrieval tools + 3 plan-pipeline tools + 2 live-introspection tools (the latter confirm-gated for any write).

**Two-tree invariant.** `D:\Work\blueprintexporter\blueprint-exporter` is full read/write; `D:\Work\UE_DOW` is read+execute only, with the single plugin-junction exception at `D:\Work\UE_DOW\game\Plugins\BlueprintExporter`. Details in `PROJECT_INVENTORY_BRIEF.md` §0 / §0.1.

**Dual-engine BuiltPlugin.** Repo ships TWO engine-targeted plugin builds: `BuiltPlugin/` is the UE_DOW-engine variant; `_build_output_5_7/` is the stock-UE-5.7 variant for BugHunt / UE_DOW_Legacy / MutableSample. Wrong choice = `Failed to load ... (GetLastError=126)`. The M29.6 engine-agnostic refactor produced ProcessEvent-based UFUNCTION call-through helpers so the renderer code itself doesn't differ between the two builds, but the DLL BuildId still must match the engine.

---

## Known issues / audit parking lot

- **Full-depot legacy sweep crashes on KINEMATION.** Running
  `ProjectInventory -DeepDump` against all 2604 legacy assets hits
  a UE engine assertion at asset `#2184` (immediately after
  `ABP_Mag_WK-11_Viper`, inside `/Game/KINEMATION/TacticalShooterPack/`):
  `!bRequiresCachedVariable` at `K2Node_PropertyAccess.cpp:104`.
  Third-party content issue — load-time UE assertion triggered
  before any plugin code runs. Workaround: scope sweeps with
  `-Filter=/Game/CombatPrototype/` (what the M19.2.1 verification
  run did; 36-asset slice at `D:\Work\_dow_legacy_inventory_cp\`
  outside the repo by design). Proper fix: filter KINEMATION out
  of the full sweep via `-Exclude=/Game/KINEMATION/` (the commandlet
  supports it — worth a one-liner if a full legacy refresh is
  needed).
- **[RESOLVED — docs hygiene, 2026-04-21]** EnterCondition
  verification via a raw `verification[]` `path` entry (e.g.
  `["<st>", "StateTreeEditorData:SubTrees", "[2]", "EnterConditions",
  "[0]", "InstanceObject"]`) returned `null` for both root and
  nested states, even when the mutating op landed cleanly (op's own
  before/after dict showed `ec_len 0 → 1, idx: 0, instance: ST_Cond_­
  HasTargets_C_0`, and the .uasset md5 shifted — see
  `D:\Work\_combat_ai_tuning\combat_loop_hastargets_gate.json.run.json`).
  Root cause: the `StateTreeEditorData:Foo` colon notation was only
  ever a doc convention — `BpxReflectionOps::ResolvePath` in
  `Source/BlueprintExporter/Private/Reflection/ReflectionOps.cpp`
  walks one UPROPERTY per step and has no parse rule for `:`. The
  original parking-lot claim that "nested WORKS, root returns null"
  was never empirically exercised end-to-end; the LOS-gate plan that
  shipped the worked example had no `verification[]` block at all.
  Both paths fail the same way. **Resolution (docs-only):** the
  shipped `verify_state_enter_conditions` op (M25.2.0) is now
  documented as the canonical read-back for both root and nested
  states — it uses the op-side `state_path` nav format (same as
  `add_` / `remove_`) and resolves reliably. `plans/README.md`,
  `scripts/python_ops/CATALOG.md`, and the `statetree.py` docstring
  now steer plan authors to the op inside `operations[]` instead of
  suggesting the unsupported `:` path in `verification[]`. The LOS
  worked example was rewritten to demonstrate the op-based pattern.


---

## Gotchas discovered this session (2026-04-18)

- **MSYS path mangling on `/Game/…` filters.** Bash rewrites
  `-Filter=/Game/Foo/` to `-Filter=C:/Program Files/Git/Game/Foo/`
  silently. Result: filter matches nothing, commandlet reports
  `Processed=0`. Fix: prefix the command with `MSYS_NO_PATHCONV=1`.
  Also applies to any `/Game/…` literal arg (OutDir is fine because
  it starts with `D:\…`). M5 `-Asset=/Game/…` is subject to the same
  trap — DeepDumpCommandlet does a defensive post-parse check
  (`if (!Path.StartsWith("/"))`) and errors out early with a clear
  message when bash has mangled the arg, but prefixing `MSYS_NO_PATHCONV=1`
  is still the correct fix.
- **DOW needs `-stdout -log` to emit to stdout.** Without `-stdout`
  UE writes to its log file only; `>` redirect captures nothing.
  BugHunt is more forgiving but use `-stdout` for both to match.
- **Plugin load needs baked-in target.** Adding a module dep to
  `Build.cs` requires rebuilding the consuming project's target
  (BugHunt in our case) so the `.target` receipt lists the new
  plugin. `.uplugin` Optional deps don't substitute. Symptom:
  `LogWindows: Missing import: UnrealEditor-<Module>.dll` during
  plugin load. Fix: `Build.bat UnrealEditor Win64 Development
  -Project=BugHunt.uproject -WaitMutex` (~27 s).
- **DOW's `UE_DOW.uproject` disables BlueprintExporter.** It pins
  `"BlueprintExporter": { "Enabled": false }`, probably from an
  earlier dev setup. Always pass `-EnablePlugins=BlueprintExporter`
  when running commandlets against DOW until someone flips it
  upstream (not our tree to touch).
- **Engine re-syncs wipe plugin junctions.** `D:\Work\UE_DOW\game\Plugins\BlueprintExporter`
  is local-only; after any Perforce sync that touches `game/Plugins/`
  the junction is gone. Recreate with
  `powershell -Command "New-Item -ItemType Junction -Path '…\Plugins\BlueprintExporter' -Target '…\BuiltPlugin'"`.
- **Engine rebuild invalidates plugin DLLs.** When UGS or manual
  builds produce a new engine BuildId GUID, every plugin DLL
  stamped with the old CL number becomes "stale" and UE silently
  skips loading them. If a *required* plugin (non-`Optional`) is
  stale, engine init aborts with `LogPluginManager: Error: Plugin
  'X' failed to load because module 'X' could not be found`.
  Fix: rebuild the consuming project's target against the new
  engine via `Build.bat <Target> Win64 Development -Project=…
  -WaitMutex`, which regenerates all its plugin DLLs.
