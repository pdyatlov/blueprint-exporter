# BlueprintExporter

Unreal Engine 5 editor plugin that exports, imports, and compares Blueprints and State Trees in JSON format for version control and CI/CD integration.

## Purpose

The primary use case is **exporting Blueprints for AI analysis**. The exported JSON must be accurate and complete so AI systems can reason about Blueprint logic without hallucinating.

### Critical Principle: Never Guess Values

- If a value cannot be determined, explicitly mark it as unknown (e.g., `null`, empty string, or dedicated "unknown" field)
- Never substitute default values or placeholder data for missing information
- Include metadata indicating when data may be incomplete or uncertain
- This ensures AI systems analyzing exports won't make false assumptions

## Docs Map

Canonical documentation lives across several files. When picking up work (especially after `/clear`), consult them in this order:

| File | Read it when | What it covers |
|---|---|---|
| `WIP_INVENTORY.md` | **FIRST, on any resume or inventory question** | Current state + what's next + durable reference. Source of truth across `/clear` boundaries. Per-milestone forensic record was extracted to `WIP_INVENTORY_archive.md` on 2026-04-27. |
| `WIP_INVENTORY_archive.md` | Only when a specific historical detail is needed (commit SHA, fixture name, prior-session narrative, troubleshooting arc for a closed milestone) | Forensic record, NOT auto-loaded. Full ship records for every closed milestone, session narratives, expired snapshots. |
| `README.md` | Onboarding / consumer use / local-dev setup | Install, CLI reference, feature matrix, Local Development. |
| `BugHunt/README.md` | Test-project / regression work | Dev-only test plugin + committed-fixture UE 5.7 project; junction setup; hunt commandlets. |
| `PROJECT_INVENTORY_BRIEF.md` | Inventory pipeline design decisions | Phase 0/1/2 architecture, determinism rules (§8), coverage accounting, §11A twin-run gate, §13 final deliverable. |
| `scripts/verify_determinism.ps1` | Before touching pipeline output | Twin-run CI gate: `pwsh -File scripts/verify_determinism.ps1 -Project {BugHunt\|DOW} -SweepDeepDump`. |
| `scripts/smoke_bridge.py` | After bridge handler / registry / transport changes | Editor-running end-to-end smoke. Pings, lists methods, round-trips every handler + negative paths. Exit 0 iff zero FAILUREs. Complements the determinism gate (output byte-identity vs. transport + handler wiring). |
| `scripts/python_ops/CATALOG.md` | Before authoring Claude-driven asset edits | Python write-layer reference. Per-op kwargs for every shipped op (CDO defaults, SCS, instanced fields, asset create/rename, StateTree edits, interface overrides, structural BP edits, graph nodes, EQS, curves, data assets, UDS, gameplay tags). |
| `scripts/python_ops/plans/README.md` | Before generating an EditPlan | EditPlan JSON schema + authoring conventions consumed by the validator + executor + diff oracle. |
| `scripts/python_ops/plans/AGENT_LOOP.md` | When fulfilling a user edit request via the plan pipeline | Agent-facing 8-step loop, error tables, retry heuristics, anti-patterns. Read first when picking up an edit request. |
| `scripts/blueprint-exporter-mcp/README.md` | When wiring an MCP client (Claude Code / Cursor / Claude Desktop) | External MCP server. 14 tools across retrieval / plan-pipeline / live-introspection / config-walking. |
| `CLAUDE.md` (this file) | Architecture / key types / build loop / semver rule | Data flow layers, schema types, Source → BuiltPlugin → rebuild pipeline, version drift-detection. |

Skill / agent reference: the auto-memory system at `~/.claude/projects/<project-hash>/memory/` persists cross-session facts that aren't derivable from these files. Per-user-per-machine; does not transfer between collaborators.

## Project Structure

```
Source/BlueprintExporter/
├── Public/
│   ├── BlueprintExporterModule.h          # Plugin entry point, UI integration
│   ├── Schema/
│   │   ├── BlueprintExportTypes.h         # Blueprint data structures
│   │   ├── StateTreeExportTypes.h         # State Tree data structures
│   │   └── PluginExportTypes.h            # Plugin descriptor + reflected-type structs
│   ├── Export/
│   │   └── BlueprintExportManager.h       # Export orchestration
│   ├── Serialization/
│   │   ├── BlueprintSerializer.h          # Blueprint → FExportedBlueprint
│   │   └── BlueprintTypeInference.h       # Pin type mapping
│   ├── TextExport/
│   │   ├── HumanReadableExporter.h        # .txt format output
│   │   ├── DeepDumpRenderer.h             # Tier 2 Markdown renderers shared by DeepDumpCommandlet (single asset) and ProjectInventoryCommandlet -DeepDump (sweep). Entry points: RenderBlueprintMarkdown / RenderStateTreeMarkdown / RenderDataAssetInstanceMarkdown / RenderOutOfScopeNotice. Walks instanced subobjects recursively so AIPerception sense configs / GAS attribute defaults / anim layer overrides render inline as nested property tables.
│   │   ├── SmartObjectDefinitionDeepRenderer.h    # Tier 2 for USmartObjectDefinition. Gated on WITH_SMARTOBJECTS_SUPPORT.
│   │   ├── BehaviorTreeDeepRenderer.h             # Tier 2 for UBehaviorTree. No gate (AIModule is always linked).
│   │   ├── DataTableDeepRenderer.h                # Tier 2 for UDataTable. No gate.
│   │   ├── ChooserTableDeepRenderer.h             # Tier 2 for UChooserTable. Gated on WITH_CHOOSER_SUPPORT.
│   │   ├── EnvQueryDeepRenderer.h                 # Tier 2 for UEnvQuery. No gate.
│   │   ├── CustomizableObjectInstanceDeepRenderer.h  # Tier 2 for Mutable's UCustomizableObjectInstance. Gated on WITH_MUTABLE_SUPPORT.
│   │   ├── CustomizableObjectDeepRenderer.h          # Tier 2 for Mutable's UCustomizableObject. Gated on WITH_MUTABLE_SUPPORT. Skips compiled-model blob (regenerates on save and would destroy twin-run byte-identity).
│   │   └── CustomizableObjectMacroLibraryDeepRenderer.h # Tier 2 for Mutable's UCustomizableObjectMacroLibrary. Gated on WITH_MUTABLE_SUPPORT. Zero-include — class dispatch by name.
│   ├── Commandlets/
│   │   ├── BlueprintExportCommandlet.h
│   │   ├── ProjectManifestCommandlet.h    # Inventory Phase 0 — AssetRegistry-only scan → MANIFEST.md
│   │   ├── ProjectInventoryCommandlet.h   # Inventory Phase 1 — per-asset .md + .meta.json + resume
│   │   ├── AggregateInventoryCommandlet.h # Inventory Phase 2 — INDEX / CLASS_TREE / DEPENDENCY_GRAPH / REPLICATION_MATRIX / HEALTH_REPORT / domain overviews from .meta.json fan-in
│   │   ├── DeepDumpCommandlet.h           # On-demand single-asset Tier 2 dump (.deep.md). Thin wrapper around DeepDumpRenderer.
│   │   └── ProjectPluginsCommandlet.h     # Project-plugin scan → PLUGINS.md + PluginInventory/<Name>.{md,meta.json}
│   ├── Util/
│   │   └── AtomicFileWriter.h             # SaveStringAtomic — write to <path>.tmp then rename. Used by every emit path.
│   └── Reflection/
│       ├── ReflectionTypes.h              # Result structs returned by the reflection-bridge UFUNCTIONs (FBpxReflectionResult / FBpxGraphEndpoints / FBpxNodeResult).
│       └── ReflectionOps.h                # UBpxReflectionOps static UFUNCTION library. Bypasses Python-layer CPF_Protected filtering by walking FProperty / UObject in native C++. Surface: mutation primitives (Get/SetPropertyValue, FindSubobject, array ops, NewSubobject, CompileAndSavePackage), graph-authoring (OverrideInterfaceFunction, FindGraphEndpoints, ConnectPinsByName, SetNodePinLiteralDefault, ConnectGraphPinsByGuidString, WipeFunctionGraphBody), structural BP authoring (AddMemberVariable / AddFunctionGraph / AddComponentToSCS / AddInterfaceByPath, all Deterministic), node-level graph authoring (AddBranch / AddCallFunction / AddVariableGet / AddVariableSet / AddCustomEvent / AddExecutionSequence / AddDynamicCast / AddLocalVariable / SetGraphPinLiteralDefault), non-BP factories (CreateCurveFloat + SetCurveFloatKeys, CreateDataAssetInstance, CreateUserDefinedStruct + Add/Remove/SetUDSMember), EQS (AddEnvQueryOption), and config edits (AddGameplayTag — first config-file-mutating UFUNCTION; gated on WITH_GAMEPLAYTAGSEDITOR_SUPPORT). Every write op idempotent on its identifier and deterministic via SeedGuidFromJoined or explicit FName. Per-op detail in scripts/python_ops/CATALOG.md; foot-gun history in WIP_INVENTORY_archive.md.
├── Private/
│   ├── Bridge/                            # Editor JSON-RPC 2.0 WebSocket bridge. Compiles out when WebSocketNetworking is unavailable (WITH_BPXBRIDGE_SUPPORT=0).
│   │   ├── BpxBridgeServer.{h,cpp}        # Wraps IWebSocketServer. 127.0.0.1 only. FTSTicker drives Server->Tick() on the game thread; libwebsockets delivers callbacks synchronously inside that tick, so handler dispatch is game-thread-safe. JSON-RPC 2.0 framing; spec-compliant error codes.
│   │   ├── BpxHandlerRegistry.{h,cpp}     # TMap method lookup + parallel descriptions table consumed by the list_methods introspection handler.
│   │   └── BpxPlanHandlers.{h,cpp}        # validate_plan + apply_plan handlers. Invoke scripts/bridge_entry.py via IPythonScriptPlugin::ExecPythonCommandEx (Private namespace scope, Unattended). On a passed apply_plan the handler also calls ReExport::ReExportAsset for each touched asset and embeds a reExport: {scopedPaths, wroteFiles, errorCount, perAsset} section. Compiles out when WITH_BPXPYTHON_SUPPORT=0.
│   ├── InventoryEmit/                     # Shared per-asset inventory-emission surface used by both ProjectInventoryCommandlet and ReExport.
│   │   └── PerAssetEmit.{h,cpp}           # BlueprintExporter::InventoryEmit namespace. Single source of truth for .md + .meta.json shape; commandlet sweep and bridge re-export are byte-identical by construction.
│   ├── ReExport/                          # Scoped per-asset inventory refresh called from the bridge. Not a full commandlet replacement: project-level rollups (coverage / DEPENDENCY_GRAPH / CLASS_TREE) still need refresh_inventory.
│   │   └── AssetReExporter.{h,cpp}        # ReExportAsset(PackageName, InventoryRoot) → loads asset, dispatches to UBlueprint or UStateTree path via InventoryEmit, writes via SaveStringAtomic. UBlueprint branch unconditional; StateTree branch gated on WITH_STATETREE_SUPPORT.
│   ├── Schema/
│   │   ├── BlueprintExportTypes.cpp
│   │   └── StateTreeExportTypes.cpp
│   ├── Serialization/
│   │   ├── BlueprintSerializer.cpp
│   │   └── StateTreeSerializer.cpp        # UStateTree → FExportedStateTree
│   ├── Util/
│   │   └── AtomicFileWriter.cpp
│   ├── Commandlets/
│   │   ├── BlueprintExportCommandlet.cpp
│   │   ├── ProjectManifestCommandlet.cpp
│   │   ├── ProjectInventoryCommandlet.cpp
│   │   ├── AggregateInventoryCommandlet.cpp
│   │   ├── DeepDumpCommandlet.cpp
│   │   └── ProjectPluginsCommandlet.cpp
│   ├── Reflection/
│   │   └── ReflectionOps.cpp              # Implementation. Shared helpers: FindFunctionGraphByName (walks FunctionGraphs → ImplementedInterfaces[].Graphs → UbergraphPages), SeedGuidFromJoined (md5→FGuid), SeedPinGuidsForNode. **Foot-gun**: MarkBlueprintAsStructurallyModified must be called ONCE per op boundary — wrappers that already get a mark from the engine API (ImplementNewInterface, AddMemberVariable, AddLocalVariable) MUST NOT mark a second time, otherwise listeners re-enter and invalidate the just-seeded GUIDs before the follow-up compile + save.
│   ├── TextExport/
│   │   ├── DeepDumpRenderer.cpp           # Tier 2 Markdown render helpers; entry points in BlueprintExporter::DeepDump namespace.
│   │   ├── SmartObjectDefinitionDeepRenderer.cpp
│   │   ├── BehaviorTreeDeepRenderer.cpp
│   │   ├── DataTableDeepRenderer.cpp
│   │   ├── ChooserTableDeepRenderer.cpp
│   │   ├── EnvQueryDeepRenderer.cpp
│   │   ├── CustomizableObjectInstanceDeepRenderer.cpp
│   │   ├── CustomizableObjectDeepRenderer.cpp        # Per-node graph walk delegated to DeepRenderShared::RenderEdGraphNodes (shared with the macro-library renderer).
│   │   └── CustomizableObjectMacroLibraryDeepRenderer.cpp
│   └── [other .cpp files]
```

Per-renderer milestone authorship and per-write-op shipping prose live in `WIP_INVENTORY_archive.md` and `scripts/python_ops/CATALOG.md` — not duplicated here.

## Architecture

Data flows through these layers:

1. **Manager Layer** — orchestrates operations (`FBlueprintExportManager`).
2. **Serialization Layer** — converts UE types to portable structs.
3. **Type Layer** — portable data structures (`BlueprintExportTypes.h` / `StateTreeExportTypes.h` / `PluginExportTypes.h`).
4. **Output Layer** — JSON, text, digest, batch manifest.
5. **Editor Bridge Layer** (`Private/Bridge/` + `Private/ReExport/`) — editor-only JSON-RPC 2.0 WebSocket server on `127.0.0.1:1337` (override via `BPX_BRIDGE_PORT`). Started from `StartupModule`, stopped from `ShutdownModule`. Handlers: `ping`, `list_methods` (zero-param introspection, returns `{methods, pluginVersion}`, drives `smoke_bridge.py`), `validate_plan`, `apply_plan`. The plan handlers invoke `scripts/bridge_entry.py` in-process via `IPythonScriptPlugin::ExecPythonCommandEx` with per-call namespace isolation. On a passed `apply_plan`, the handler walks the report's `diff.asset_changes[]` and invokes `ReExport::ReExportAsset` on each touched UBlueprint / UStateTree — outputs are byte-identical to a `refresh_inventory` sweep for those assets (shared `InventoryEmit` module guarantees this). Project-level rollups (coverage / DEPENDENCY_GRAPH / CLASS_TREE) still require `refresh_inventory`. MCP-side (`tools/plans.py`) is bridge-first with subprocess-fallback on transport failure; responses carry `transport: "bridge"` or `"subprocess"`. Compiles out when `WebSocketNetworking` is absent (`WITH_BPXBRIDGE_SUPPORT=0`); plan handlers additionally compile out when `PythonScriptPlugin` is absent (`WITH_BPXPYTHON_SUPPORT=0`). Purpose: kill the 2–5 min `UnrealEditor-Cmd.exe -run=pythonscript` cold-start tax on every plan invocation when an editor is already running.
6. **Project Inventory Pipeline Layer** (see `PROJECT_INVENTORY_BRIEF.md`) — `ProjectManifestCommandlet` (FAssetRegistry-only scan → `MANIFEST.md`) → `ProjectInventoryCommandlet` (streaming load / introspect / write / GC per asset; per-asset `<Path>.md` + `<Path>.meta.json` with coverage accounting; `-Resume` via sidecar marker) → `AggregateInventoryCommandlet` (reads `.meta.json` fan-in; emits `INDEX.md`, `CLASS_TREE.md`, `DEPENDENCY_GRAPH.md`, `REPLICATION_MATRIX.md`, domain overviews, `HEALTH_REPORT.md`). `DeepDumpCommandlet` is the on-demand Tier 2 dump for a single asset; `ProjectInventoryCommandlet -DeepDump` runs the same `TextExport/DeepDumpRenderer` across every processed asset (sibling `<Path>.deep.md`). Tier 2 covers UBlueprint family, UStateTree, SmartObjectDefinition, BehaviorTree, DataTable, ChooserTable, EnvQuery, UDataAsset instances, and the Mutable class set (UCOI / UCO / COML); other in-scope classes get a short out-of-scope notice so the sibling pattern is uniform. `ProjectPluginsCommandlet` complements the /Game-focused phases by walking `IPluginManager` for project plugins (uplugin descriptor → `PLUGINS.md` + per-plugin sidecars). All writes go through `Util/AtomicFileWriter::SaveStringAtomic` so a mid-run crash never leaves a torn file. Output is deterministic — declaration order for variables, alphabetical for functions, SCS traversal for components, `/Game/...` paths only.

Critical gap closures: instanced subobjects walk recursively (sense configs, GAS attribute sets, anim layer overrides) so AI consumers don't have to parse opaque `ExportTextItem_Direct` blobs. The CDO property pass diffs inherited UPROPERTYs against the parent class CDO so data-carrier Blueprints (`GameplayEffect` modifier lists, `GameplayAbility` cost/cooldown/tags, inherited `DataAsset` payloads) and natively-declared Instanced components (`AActor::ArrowComponent`, `ACharacter::CharacterMovement` / `Mesh`) all surface in the export. Truncation, cycles, and broken references are explicit markers (`bTruncated` / `bCycleDetected` / `bHasBrokenReference`) — never silently dropped.

## Key Types (BlueprintExportTypes.h)

- `FExportedBlueprint` — complete Blueprint representation. Carries `CDOProperties` (inherited UPROPERTY overrides diffed against parent CDO; covers GE / GA / DataAsset payloads + natively-declared Instanced components) and `DataCarrierKind` discriminator (`GameplayEffect` / `GameplayAbility` / `DataAsset`) consumed by HEALTH_REPORT's coverage classification.
- `FExportedGraph` — node graphs (Event, Construction, Custom, Function, Macro, Ubergraph).
- `FExportedNode` — individual nodes; GUIDs mapped to stable string IDs for consistent serialization.
- `FExportedPin` — connections and default values.
- `FExportedVariable` — properties with flags and metadata.
- `FExportedFunction` — functions with parameters and graphs. `bIsInterfaceOverride` + `InterfaceClassPath` distinguish override graphs (which live on `Blueprint->ImplementedInterfaces[].Graphs`) from regular function graphs; emitted only when set so non-override exports stay byte-identical to pre-flag versions.
- `FExportedComponent` — actor component hierarchies.
- `FExportedComponentProperty` — single property on a component template OR an entry in `FExportedBlueprint::CDOProperties` (same shape, reused). `Value` carries the flat `ExportTextItem_Direct` string. For Instanced / EditInlineNew references, `bIsInstancedSubobject=true` and `SubobjectJsonValues` holds a structured tree of each referenced subobject — so AI consumers don't have to parse the opaque blob.
- `FExportedPinType` — pin type info. `bSubCategoryObjectResolved` distinguishes "pin genuinely has no subtype" from "subtype was blanked defensively because the weak pointer wasn't safe to read".
- `FBlueprintExportConfig` — operation settings.

## Building & Deploying

### Full build + deploy pipeline (MUST follow all steps after any code change):

1. **Sync Source → BuiltPlugin** (BuiltPlugin is the distributable copy):
   ```bash
   # Copy changed files from Source/ to BuiltPlugin/Source/
   # Also sync BlueprintExporterModule.h/.cpp, Build.cs if modified
   ```

2. **Rebuild DLL with UE** (REQUIRED — BuiltPlugin DLL must match source):
   ```bash
   cd blueprint-exporter
   mkdir -p _build_output
   "/d/Work/UE_DOW/engine/Build/BatchFiles/RunUAT.bat" \
     BuildPlugin \
     -Plugin="$(cygpath -w "$(pwd)/BuiltPlugin/BlueprintExporter.uplugin")" \
     -Package="$(cygpath -w "$(pwd)/_build_output")" \
     -TargetPlatforms=Win64 -Rocket
   # Copy binaries back:
   cp _build_output/Binaries/Win64/UnrealEditor-BlueprintExporter.dll BuiltPlugin/Binaries/Win64/
   cp _build_output/Binaries/Win64/UnrealEditor.modules BuiltPlugin/Binaries/Win64/
   rm -rf _build_output
   ```

3. **Distribute `BuiltPlugin/` manually** (current approach while testing):
   - **`BuiltPlugin/Binaries/Win64/` is the UE_DOW custom-engine variant only** — its BuildId matches `D:/Work/UE_DOW/engine/`. Do NOT copy it into stock-UE-5.7 projects (`BugHunt`, `UE_DOW_Legacy`, fresh stock scratch projects) — UE rejects the load with `Plugin 'BlueprintExporter' failed to load because module ... could not be found` + `GetLastError=126`. For those, build separately against stock UE 5.7 (`C:\Program Files\Epic Games\UE_5.7\...`'s `RunUAT.bat`) and install from `_build_output_5_7/`.
   - Remove any prior install first (DLL + `.modules` + `.uplugin`) to avoid stale BuildId or version-stamp mismatches.
   - Full dual-engine flow (build both targets + 3-location install + `.uplugin` sync) is documented step-by-step in `WIP_INVENTORY.md § Standard build flow`.

### Important build notes

- **Never skip the UE rebuild** — if you only copy source files without rebuilding the DLL, UE will detect the mismatch and try to rebuild on startup (which fails for engine plugins).
- **Two engines, two builds, three installs.** `BuildPlugin -Rocket` is engine-pinned via the `RunUAT.bat` you invoke. Building once and copying the same DLL into a stock-UE-5.7 project is the most common ship-process foot-gun — it silently corrupts the install. The dual-engine matrix is enumerated in `WIP_INVENTORY.md § Standard build flow`.
- **Sync `.uplugin` to every downstream install.** Each downstream install (`BugHunt/TestProject/Plugins/BlueprintExporter/BlueprintExporter.uplugin`, `D:\Work\UE_DOW_Legacy\Plugins\BlueprintExporter\BlueprintExporter.uplugin`) carries its own `.uplugin` copy. The drift detector below catches BugHunt's; the off-repo legacy install is checked manually.

### Pre-push verification (REQUIRED — see matrix below)

Every push to `origin/main` triggers TeamCity `Code_Submit_Compiled_Binaries_to_UGS`, which compiles the plugin as part of the full editor target with **unity (jumbo) builds enabled** — same stitching mode as `RunUAT BuildPlugin -Rocket`. A red compile blocks the UGS submit step and wastes shared agent time. Determinism / behavior regressions are worse: they land silently and corrupt committed inventory output for every downstream consumer.

Verification scales with what changed:

| Change class | Required pre-push checks |
|---|---|
| Plugin C++ source — `Source/**/*.{cpp,h}`, `Build.cs`, `BuiltPlugin/Source/**`, `BlueprintExporter.uplugin` | (1) Unity build + (2) Automation tests + (3) Determinism gate if serializer / renderer / emit path touched |
| Serializer / renderer / emitter behavior (anything affecting `.md` / `.meta.json` / `.deep.md` / `INDEX.md` / `HEALTH_REPORT.md`) | (3) Determinism gate is load-bearing — output stability invariant per `PROJECT_INVENTORY_BRIEF.md § 8`. (1) + (2) still apply if C++ was touched. |
| New typed handler or DeepRenderer for a class not yet covered | (4) Fixture regeneration via `GenerateTestBlueprintsCommandlet` → commit fixtures → then (1) + (2) + (3) |
| Bridge handler code (`Private/Bridge/**` or `scripts/bridge_entry.py`) | (1) + (2) + (5) Bridge smoke (`scripts/smoke_bridge.py`) |
| Python ops library (`scripts/python_ops/**`) | (6) MCP + op smoke tests (`pytest scripts/blueprint-exporter-mcp/`, plus `smoke_bridge.py` if handlers exercised) |
| Config-mutating ops (`add_gameplay_tag` and any future `Config/<X>.ini` writers) | (7) Tag-author parity gate (`scripts/verify_tag_author.ps1`). Auto-run as part of `verify_all.ps1`. |
| MCP server itself (`scripts/blueprint-exporter-mcp/**`) | (6) + editor-running roundtrip if transport changed |
| Pure docs (`.md` only), config-only (no `Build.cs`), `.claude/` tweaks | Push directly. |

**Commands:**

1. **Unity build** — `RunUAT BuildPlugin -Rocket` (step 2 above). ~30 s warm DDC. Exercises the per-module unity batching CI uses. Expect `BUILD SUCCESSFUL` / `ExitCode=0`.
2. **Automation tests** — `pwsh -File scripts/run_automation_tests.ps1 -Project BugHunt`. The wrapper parses the log for per-test pass/fail and refuses to exit 0 if ATF's `Skipping unit tests for the cooked build and commandlet` signature appears (silent-no-op trip-wire). Per-area filter via `-Filter BlueprintExporter.Schema.` etc. **Foot-gun**: every `IMPLEMENT_*_AUTOMATION_TEST` in this plugin MUST include `EAutomationTestFlags::CommandletContext` in its flag mask, otherwise ATF rejects the test in commandlet mode and it reports a false green. Canonical mask: `EditorContext | CommandletContext | EngineFilter`. **Wrapper gotchas** (encoded so the raw form matters): do NOT append `; Quit` to `-ExecCmds` (fires before async tests run); use `-testexit="Automation Test Queue Empty"` instead, with the embedded space quoted properly.
3. **Determinism gate** — `pwsh -File scripts/verify_determinism.ps1 -Project BugHunt -SweepDeepDump`. Runs the full inventory pipeline twice and `git diff --no-index` the two trees. Exit 0 iff byte-identical. BugHunt is the cheap default; `-Project DOW -Filter=/Game/<slice>/` for risky serializer changes.
4. **Fixture regeneration** — see `BugHunt/README.md`. Add the fixture to `GenerateTestBlueprintsCommandlet`'s catalog, run with `-Force`, commit the regenerated `Content/TestBlueprints/*.uasset`. Never hand-author fixtures.
5. **Bridge smoke** — `python scripts/smoke_bridge.py` with the editor running. Pings, lists methods, round-trips every handler. Exit 0 iff zero FAILUREs (EXPECTED_ERROR is the negative-path coverage).
6. **MCP / op smoke** — `cd scripts/blueprint-exporter-mcp && pytest`. For ops-only changes, run the matching `test_*.py` probe.
7. **Tag-author parity gate** — `pwsh -File scripts/verify_tag_author.ps1`. Snapshots ini bytes, applies via `run_plan`, asserts +1 line + idempotence on re-apply, restores baseline.

**When to skip entirely:** pure-docs (`.md`), `.claude/` config, CI configuration that doesn't touch `Build.cs`, scratch artefacts.

**Diagnosing a red CI run** — `Code_Submit_Compiled_Binaries_to_UGS_<N>.log` artefacts have grep-friendly signatures: `error C2084: function '...' already has a body` / `error C2374: '...': redefinition` (ODR); `error LNK2005` (multi-def link); `Test Failed:` (automation); `Tree diff: N files differ` (determinism). Match the signature to the matrix and reproduce locally before pushing a fix.

## Coding Conventions

- Follow Unreal Engine C++ standards.
- `F` prefix for structs/classes, `U` prefix for UObjects, `E` prefix for enums.
- Use LOCTEXT macros for user-facing strings.
- Result structs should include `bSuccess` flag and error messages.
- Check for orphaned object references before dereferencing weak pointers.

## Important Implementation Details

- **Orphaned References**: Always check `bHasBrokenReference` before using object references. When broken, preserve the `BrokenReferenceInfo` so AI knows the reference existed but couldn't be resolved.
- **Stable IDs**: Node GUIDs are mapped to stable string IDs for consistent serialization.
- **Pin Type Safety**: Use `FBlueprintTypeInference` for type mapping to avoid crashes.
- **No Default Fallbacks**: If a value cannot be read, do not substitute a default. Use null or include an explicit "unknown" marker.
- **Explicit Uncertainty**: If type inference fails or a reference is unresolved, include fields like `bTypeInferred: false` or `bValueUnknown: true`.
- **Instanced Subobject Capture**: Component properties whose `FProperty` flags include `CPF_InstancedReference` / `CPF_PersistentInstance` (directly or on a container's inner element property) must be walked recursively. Depth is capped at `MAX_SUBOBJECT_RECURSION_DEPTH`; cycles detected via visited-set. Null references, truncation, and cycles are marked explicitly (`bHasBrokenReference`, `bTruncated`, `bCycleDetected`) — never silently dropped.

## CLI Usage

```bash
# Export Blueprints
UE5Editor.exe Project.uproject -run=BlueprintExport -Paths="/Game/Blueprints" -Out="./Exports"

# Export Blueprints + State Trees
UE5Editor.exe Project.uproject -run=BlueprintExport -Paths="/Game/AI" -Out="./Exports" -IncludeStateTrees
```

## Output Files

- Blueprint exports: `{Name}.json` (full data), `{Name}.txt` (human-readable summary), `{Name}.digest.json` (metrics).
- State Tree exports: `{Name}.statetree.json`, `{Name}.txt`, `{Name}.digest.json`.
- Batch exports also produce `manifest.json` (with `assetType` field: `"Blueprint"` or `"StateTree"`).

## Versioning Protocol

Every version bump must update all locations in the table below. Missing any one location causes version drift (detectable by the drift-detection command at the bottom).

| # | File | Field / Context |
|---|------|----------------|
| 1 | `BlueprintExporter.uplugin` | `"VersionName"` string AND `"Version"` integer (= minor digit) |
| 2 | `Source/BlueprintExporter/Private/BlueprintExporterModule.cpp` | `UE_LOG` startup message `"vX.Y.Z"` |
| 3 | `Source/BlueprintExporter/Private/BlueprintExporterModule.cpp` | `StartBridge()` — `ping` AND `list_methods` handlers each hardcode `pluginVersion` in their JSON response. Grep `pluginVersion.*TEXT` to catch all sites. |
| 4 | `Source/BlueprintExporter/Private/Export/BlueprintExportManager.cpp` | `Manifest.PluginVersion = TEXT("X.Y.Z")` |
| 5 | `Source/BlueprintExporter/Private/Serialization/BlueprintSerializer.cpp` | `ExportInfo.PluginVersion = TEXT("X.Y.Z")` |
| 6 | `Source/BlueprintExporter/Private/Serialization/StateTreeSerializer.cpp` | `ExportInfo.PluginVersion = TEXT("X.Y.Z")` |
| 7 | `Source/BlueprintExporter/Private/Commandlets/ProjectPluginsCommandlet.cpp` | `Out.ExportInfo.PluginVersion = TEXT("X.Y.Z")` |
| 8 | `Source/BlueprintExporter/Private/Tests/BlueprintExporterTests.cpp` | `Manifest.PluginVersion` in live-version manifest tests only — fixtures pinned to `"1.0.0"` are intentionally excluded and must NOT be changed |
| 9 | `README.md` | `Version: X.Y.Z` block |

### Semver Rule

- New subsystem or feature → minor bump (x.**Y**.0), e.g. 1.8.0 → 1.9.0.
- Bug fix → patch bump (x.y.**Z**), e.g. 1.9.0 → 1.9.1.

### `.uplugin` Version Integer Convention

The `"Version"` integer field equals the **minor digit** of the version string. Example: `"VersionName": "1.9.0"` → `"Version": 9`.

### Drift-Detection Command

```bash
grep -rn "1\.[0-9]\+\.[0-9]\+" \
  Source/ \
  BuiltPlugin/Source/ \
  BlueprintExporter.uplugin \
  BuiltPlugin/BlueprintExporter.uplugin \
  BugHunt/TestProject/Plugins/BlueprintExporter/BlueprintExporter.uplugin \
  README.md
```

All hits must show the same version string. Any mismatch is drift. M28.15 found BugHunt's `.uplugin` had drifted to 1.27.1 across multiple ships because the original drift detector excluded both BuiltPlugin's mirror and the BugHunt-side downstream install — the extended scope above closes that gap. The off-repo `D:\Work\UE_DOW_Legacy\Plugins\BlueprintExporter\BlueprintExporter.uplugin` is not grepped here (machine-specific path); check it manually as part of the dual-engine ship process documented in `WIP_INVENTORY.md § Standard build flow`.

### CLAUDE.md Update Gate

CLAUDE.md must be updated as a completion gate for any **new subsystem** added to the plugin: a new module, a new architecture layer, or a new key type. Per-milestone forensic detail (which engine helper was wrapped, which FGuid trap was closed, which seed-prefix string was chosen) belongs in `WIP_INVENTORY_archive.md` or `scripts/python_ops/CATALOG.md`, not here — keep this file describing current state in one-line-per-file form.
