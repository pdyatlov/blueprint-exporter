# DOW Project Inventory Brief

**Target:** Full programmatic inventory of Den of Wolves (UE 5.7) so Claude Code can understand the project end-to-end without opening the editor.
**Host:** Commandlets built inside the existing BlueprintExporter plugin.
**Working directory (full read / write):** `D:\Work\blueprintexporter\blueprint-exporter`
**Engine + DOW project tree (read + execute only):** `D:\Work\UE_DOW`

The engine is a custom build that ships with DOW — both the engine and the project live under `D:\Work\UE_DOW`. There is no separate engine install under `C:\Program Files\Epic Games\`; every commandlet invocation resolves `UnrealEditor-Cmd.exe` from the DOW tree.

Concrete layout (verified):

```
D:\Work\UE_DOW\
├── engine\                                        # custom UE 5.7 fork
│   ├── Binaries\Win64\UnrealEditor-Cmd.exe        # invoked for all commandlets
│   └── Build\BatchFiles\{Build.bat, RunUAT.bat}   # used for plugin builds
└── game\
    ├── UE_DOW.uproject                            # passed as -Project= arg
    ├── Content\                                    # scan target
    └── Plugins\                                    # plugin-junction parent
```

---

## 0. Working Directory Constraint (NON-NEGOTIABLE)

Two trees matter:

- `D:\Work\blueprintexporter\blueprint-exporter` — **full read / write**, where all inventory code, plugin changes, scripts, and inventory output live.
- `D:\Work\UE_DOW` — **read + execute** only. Contains both the custom engine binaries and the game project per the layout above. The invariant is "nothing under `D:\Work\UE_DOW` gets modified" (except the narrow plugin-junction exception in §0.1).

**Allowed:**
- Read, write, modify, commit anything inside `D:\Work\blueprintexporter\blueprint-exporter`
- Execute `D:\Work\UE_DOW\engine\Binaries\Win64\UnrealEditor-Cmd.exe` against `D:\Work\UE_DOW\game\UE_DOW.uproject`
- Read engine source under `D:\Work\UE_DOW\engine\` and project source / asset data under `D:\Work\UE_DOW\game\` for reference and introspection

**Forbidden:**
- Writing, modifying, or deleting anything under `D:\Work\UE_DOW\` (except the narrow plugin-junction exception in §0.1)
- Reaching outside these two trees for tools or assets

All commandlet output goes into `D:\Work\blueprintexporter\blueprint-exporter\ProjectInventory\`. Nothing else is written.

If an agent needs something outside these paths, it stops and reports to `HANDOFF.md`.

### 0.1 Plugin Discovery Exception (GATE ITEM)

UE cannot load the BlueprintExporter plugin unless it resolves under the project's `Plugins/` folder, the engine's `Plugins/Marketplace/`, or an explicit project reference. None of these are writable under the rules above.

**Resolution (decided before first run):** create a **one-time directory junction** from DOW's `Plugins/` folder to the plugin's built output:

```
mklink /J "D:\Work\UE_DOW\game\Plugins\BlueprintExporter" ^
         "D:\Work\blueprintexporter\blueprint-exporter\BuiltPlugin\BlueprintExporter"
```

This is the narrow, explicitly-sanctioned exception to the `D:\Work\UE_DOW` write-restriction:
- Created once by Niclas before first run
- Junction target is the plugin's build output, so the DOW tree gets updated plugin binaries automatically without any agent writing to DOW
- Removed with `rmdir` when the inventory work is done
- Agents do not create, modify, or remove the junction — this is a manual bootstrap step

Engine binaries under `D:\Work\UE_DOW\engine\` remain fully read-only. No engine writes. No direct file copies into DOW outside the single junction above.

**Alternative rejected:** installing into the engine's `Plugins/Marketplace/` directory violates the engine read-only rule.
**Alternative rejected:** copying files directly into DOW's `Plugins/` violates DOW write-restriction and creates drift between the plugin repo and the DOW-local copy.

---

## 1. Mission

Produce a complete, text-based model of DOW that Claude Code can read and reason over. Every logic-bearing asset in the project gets introspected headlessly and documented. The output becomes the ground truth for every subsequent question about DOW (replication audit, Steam Relay integration, AI review, playtest risk assessment, onboarding).

No human opens the editor. No agent opens the editor. Commandlets do the loading, introspection, and documentation.

---

## 2. Architecture

Three commandlets inside the BlueprintExporter plugin. Each produces text output. Each runs independently.

```
Phase 0: ProjectManifestCommandlet
         ↓ fast Asset Registry scan, no asset loading
         → MANIFEST.md (asset counts, class distribution)

Phase 1: ProjectInventoryCommandlet
         ↓ loads every logic-bearing asset, introspects fully
         → Assets/<path>/<AssetName>.md   (one file per asset, Tier 1 detail)
         → FAILED_LOADS.md, PARTIAL_LOADS.md

Phase 2: AggregateInventoryCommandlet
         ↓ reads Phase 1 output, builds rollups
         → INDEX.md, CLASS_TREE.md, DEPENDENCY_GRAPH.md
         → REPLICATION_MATRIX.md, AI_OVERVIEW.md, ANIM_OVERVIEW.md, UI_OVERVIEW.md

On-demand: DeepDumpCommandlet
         ↓ single-asset full graph dump
         → Assets/<path>/<AssetName>.deep.md (Tier 2 detail, generated lazily)
```

All three plus the deep dump live in `Plugins/BlueprintExporter/Source/BlueprintExporter/Private/Commandlets/` alongside the existing exporter code.

---

## 3. Phase 0 — Manifest

**Purpose:** Cheap, fast scan that tells us exactly what DOW contains before committing to a full inventory run.

**Mechanism:** `FAssetRegistry` only. Does not load assets. Reads `.uasset` header metadata: class, parent class, package path, disk size.

**Invocation:**
```
UnrealEditor-Cmd.exe <DOW.uproject> ^
  -run=ProjectManifest ^
  -OutDir=D:\Work\blueprintexporter\blueprint-exporter\ProjectInventory ^
  -nullrhi -unattended -nopause -nosplash -nosound -log
```

**Output — `MANIFEST.md`:**
- Total asset count
- Asset count by class (`UBlueprint`, `UAnimBlueprint`, `UWidgetBlueprint`, `UBehaviorTree`, `UStateTree`, `USmartObjectDefinition`, `UChooserTable`, `UPoseSearchDatabase`, `UNiagaraSystem`, `UDataTable`, `UUserDefinedStruct`, `UUserDefinedEnum`, etc.)
- Asset count by top-level content folder
- Largest 50 assets by disk size
- Flagged asset classes split into **logic-bearing** (inventoried in Phase 1) vs **non-logic** (skipped)

**Logic-bearing classes (Phase 1 scope):**
`UBlueprint`, `UAnimBlueprint`, `UWidgetBlueprint`, `UControlRigBlueprint`, `UBehaviorTree`, `UStateTree`, `UEnvQuery`, `USmartObjectDefinition`, `UChooserTable`, `UPoseSearchDatabase`, `UUserDefinedStruct`, `UUserDefinedEnum`, `UDataTable` (schema only, not rows), `UGameplayAbility`-derived BPs, `UGameplayEffect`-derived BPs

**Explicitly skipped:** textures, meshes, materials (unless flagged for materials-as-BP separately), audio, animation sequences, levels (too large and per-actor detail is elsewhere).

**Runtime estimate:** 5–15 minutes on a 15,000-asset project.

**Success criteria:** `MANIFEST.md` exists and lists every asset in DOW's Content folder by class. No assets loaded into memory. No failures during the run (Asset Registry is robust).

---

## 4. Phase 1 — Full Inventory (Tier 1)

**Purpose:** One Markdown file per logic-bearing asset, containing everything needed to understand that asset without opening it in the editor.

**Mechanism:** Loads each asset, introspects via reflection, writes Markdown, unloads, `CollectGarbage()`, next. Streaming pattern — never holds more than a handful of assets in memory.

**Invocation:**
```
UnrealEditor-Cmd.exe <DOW.uproject> ^
  -run=ProjectInventory ^
  -OutDir=D:\Work\blueprintexporter\blueprint-exporter\ProjectInventory ^
  -Mode=Summary ^                          # or Full; Summary recommended
  -Classes=<comma-separated>  (optional)   # default: all logic-bearing
  -Filter=<glob>  (optional)               # e.g. /Game/Characters/*
  -Since=<P4_CL>  (optional, incremental)  # skip assets unchanged since this CL
  -nullrhi -unattended -nopause -nosplash -nosound -log
```

**Output layout:**
```
ProjectInventory/
└── Assets/
    └── Game/
        ├── Characters/
        │   ├── BP_Heister.md
        │   ├── BP_Heister.md.meta.json    # structured metadata for machine processing
        │   └── ...
        ├── AI/
        │   ├── BT_Enemy.md
        │   ├── ST_Enemy.md
        │   └── ...
        └── ...
```

Folder structure mirrors DOW's `Content/` layout exactly.

**Per-asset Markdown contents (Tier 1 detail for UBlueprint):**

- **Identity**
  - Full asset path, class, generated class name, engine version stamp
- **Inheritance**
  - Full parent chain up to `UObject`
  - Implemented interfaces with function lists
- **Variables**
  - Name, type, default value, category, metadata
  - Replication setting (None / Replicated / RepNotify + notify function name)
  - Rep condition, push model flag
  - Access level, editor-exposed flags
- **Functions**
  - Signature (inputs, outputs), pure/const, access level
  - Net execution flags (Server / Client / NetMulticast, Reliable)
  - Validation function reference
  - Local variable list
  - Node count, connection count (no detail — that's Tier 2)
- **Events & Delegates**
  - Overridden engine events (BeginPlay, Tick, etc.)
  - Custom events with signatures + net flags
  - Event dispatcher declarations
  - Bound delegates
- **Components (SCS)**
  - Full attachment tree as a Markdown list with indentation
  - Per-component: class, name, key properties (replication, visibility, collision, attach socket)
  - Inherited vs added components flagged
- **Graphs present**
  - EventGraph, UbergraphPages list
  - Function graphs with names
  - Macro graphs with names
  - For AnimBPs: AnimGraph, StateMachines list
- **References**
  - Hard refs out (what this asset depends on)
  - Soft refs out
  - Hard refs in (what depends on this asset) — populated in Phase 2 aggregate pass
- **Metadata & Flags**
  - Class flags, blueprint type, compile status at time of scan

**Per-asset specialized sections:**

- **AnimBlueprint:** state machine list with state count per machine, transition count, blend space references, Motion Matching (`FAnimNode_MotionMatching`) detection + pose search DB ref, Chooser Table refs, linked anim layer interfaces, Control Rig node refs
- **WidgetBlueprint:** widget tree as nested Markdown list, named slot list, binding list (property path → function), widget animation list
- **BehaviorTree:** tree structure as nested Markdown (composites → tasks), decorator list per node, service list per node, blackboard asset reference + key list
- **StateTree:** state hierarchy, task list per state, transition list, condition list, `FInstancedStruct` node types used
- **SmartObjectDefinition:** slot list, activity list, precondition tags
- **ChooserTable:** column types, row count, output type, referenced input struct
- **PoseSearchDatabase:** schema ref, channel list, sampling config
- **GameplayAbility BP:** net execution policy, cost/cooldown refs, tag containers (granted, blocked, required)
- **UserDefinedStruct / Enum:** full field list with types and default values

**Per-asset `.meta.json`:**
Same information as the Markdown, emitted as structured JSON so later tools can process it programmatically without re-parsing Markdown. Keep keys stable for diffing across runs.

**Failure handling:**
- Per-asset `try/catch` — one failure does not abort the run
- `FAILED_LOADS.md` — assets that failed to load, with path + error
- `PARTIAL_LOADS.md` — assets that loaded but couldn't fully introspect, with path + section that failed
- Commandlet always exits 0 if the framework ran successfully, even if individual assets failed; failure count is reported in the log
- A `-StrictMode` flag causes non-zero exit if any asset fails — useful for CI later, not for the first run

**Memory discipline:**
- Load → introspect → write → unload → `CollectGarbage()` after every N assets (tunable, default 50)
- Peak memory should stay well under editor baseline
- Long-running process, not a bulk-load

**Runtime estimates (assuming ~1,500 logic-bearing assets):**
- First run cold DDC: 60–120 minutes
- Warm DDC re-run: 30–60 minutes
- Incremental with `-Since=<CL>`: 5–15 minutes

**Success criteria (reflection-derived, not sampled):**

"95% of assets produce a file" is a silent-drop trap — it doesn't catch partial introspection of the assets that *did* produce a file. Replace with coverage accounting:

- At introspection time, walk each loaded `UObject` via `UClass::PropertyLink`, `UBlueprint::NewVariables`, `UBlueprint::FunctionGraphs`, SCS node list, etc., and **count what exists**.
- As each section of the Markdown is written, **count what made it in**.
- Emit `coverage` object per asset into `.meta.json`:
  ```json
  "coverage": {
    "variables": { "total": 42, "documented": 42 },
    "functions": { "total": 17, "documented": 17 },
    "components": { "total": 8, "documented": 8 },
    "graphs":     { "total": 5,  "documented": 5  },
    "specialized": { "applicable": ["AnimBP.StateMachines"], "documented": ["AnimBP.StateMachines"] }
  }
  ```
- `HEALTH_REPORT.md` rolls up per-asset coverage deltas. Any asset below 100% is flagged with the missing section(s).

**Snapshot-regression baseline:**
- First clean run against DOW @ pinned CL is the **baseline snapshot**. No hand-authored expectations.
- Re-running against the same CL must produce byte-identical output (aside from `RUN_LOG.md`). Any diff = regression.
- `scripts/verify_determinism.ps1` runs the commandlets twice against the same CL and diffs the outputs. Gate check before trusting any subsequent run.

---

## 5. Phase 2 — Aggregates

**Purpose:** Rollup documents that summarize the project across all assets. These are what Claude Code reads first to form a project-wide understanding.

**Mechanism:** Reads `.meta.json` files produced by Phase 1. Does not reload assets. Pure text processing.

**Invocation:**
```
UnrealEditor-Cmd.exe <DOW.uproject> ^
  -run=AggregateInventory ^
  -InDir=D:\Work\blueprintexporter\blueprint-exporter\ProjectInventory\Assets ^
  -OutDir=D:\Work\blueprintexporter\blueprint-exporter\ProjectInventory ^
  -nullrhi -unattended -nopause -log
```

Can technically run without loading the editor at all (it's just text processing), but running it as a commandlet keeps the toolchain uniform.

**Output — aggregate files:**

- **`INDEX.md`** — top-level map. Counts by class, counts by folder, links to per-domain overviews, pointers to the biggest/most-connected assets. First thing Claude Code reads.
- **`CLASS_TREE.md`** — full inheritance tree across all BPs in the project. Every class hierarchy visualized as indented Markdown.
- **`DEPENDENCY_GRAPH.md`** — who references whom. Format: one section per asset, listing hard refs out and hard refs in. Also emits a DOT/Graphviz file (`dependency_graph.dot`) for optional visualization.
- **`REPLICATION_MATRIX.md`** — every replicated variable and every RPC across the whole project, one line each. Columns: Asset, Member, Kind (Var/RPC), Replication, Condition, Notes. **This is the single most valuable document for the Steam Relay playtest workstream.**
- **`AI_OVERVIEW.md`** — every BehaviorTree, StateTree, EQS query, AIController, SmartObjectDefinition. For each: structural summary, blackboard refs, interaction points. Cross-references the NPCs that use them.
- **`ANIM_OVERVIEW.md`** — every AnimBP. Motion Matching usage, Chooser Table usage, state machine complexity, linked anim layers. Flags the gnarliest AnimBPs.
- **`UI_OVERVIEW.md`** — every WidgetBP. Widget tree summaries, binding density, nested widget usage.
- **`GAS_OVERVIEW.md`** — GameplayAbility BPs, GameplayEffect BPs, attribute sets, tag containers. Only generated if GAS is detected in the project.
- **`STRUCTS_ENUMS.md`** — all user-defined structs and enums in one place. Fields, default values, usage count.
- **`HEALTH_REPORT.md`** — quality signals: assets with compile warnings at scan time, orphaned nodes, disconnected pins, deprecated node types detected, failed loads, partial loads, **per-asset coverage delta (fields introspected vs fields documented)**. Acts as a backlog of issues the project already has plus a regression signal for the inventory itself.

**Runtime estimate:** 10–30 minutes.

**Success criteria:** All aggregate files exist. `INDEX.md` links everything together. `REPLICATION_MATRIX.md` is complete and readable.

---

## 6. On-Demand — Deep Dumps (Tier 2)

**Purpose:** Full graph-level detail for a specific asset when Tier 1 isn't enough. Generated lazily, one asset at a time.

**Invocation:**
```
UnrealEditor-Cmd.exe <DOW.uproject> ^
  -run=DeepDump ^
  -Asset=/Game/Characters/BP_Heister ^
  -OutDir=D:\Work\blueprintexporter\blueprint-exporter\ProjectInventory\Assets\Game\Characters ^
  -nullrhi -unattended -nopause -log
```

**Output:** `BP_Heister.deep.md` alongside the Tier 1 file.

**Contents:** every node in every graph, with class, title, pin layout, default values per pin, link list. For AnimBPs: full state machine graphs including transition rules. For WidgetBPs: full binding graph.

**Not generated in bulk.** Only invoked when Claude Code or a human explicitly asks for deep detail on a specific asset.

---

## 7. Workflow

### Bootstrap (one-time)

1. Add the three commandlets (`ProjectManifest`, `ProjectInventory`, `AggregateInventory`) plus `DeepDump` to the BlueprintExporter plugin under `Source/BlueprintExporter/Private/Commandlets/`
2. Build the plugin against UE 5.7
3. Commit plugin changes
4. Create `ProjectInventory/` output directory structure
5. Add `ProjectInventory/` to `.gitignore` if the output is large, OR decide it's version-controlled (recommend: committed, so diffs across runs are visible)

### First run

1. **Phase 0 — Manifest:** run first, review `MANIFEST.md`, confirm asset class distribution matches expectations
2. **Phase 1 — Inventory:** run overnight with `-Mode=Summary`, expect 1–2 hours on a 15,000-asset project
3. Review `FAILED_LOADS.md` and `PARTIAL_LOADS.md` — flag any surprising failures
4. **Phase 2 — Aggregates:** run, review `INDEX.md`, `REPLICATION_MATRIX.md`, and per-domain overviews
5. Commit all output to `D:\Work\blueprintexporter\blueprint-exporter\ProjectInventory\`

### Ongoing

- Incremental re-run with `-Since=<last_CL>` whenever DOW moves forward, regenerating only changed assets
- Deep dumps on demand for specific assets under active investigation
- Aggregate re-run after any incremental Phase 1 run
- Commits per run so diffs across runs are reviewable

### Claude Code usage pattern

1. Read `INDEX.md` and `MANIFEST.md` first for project-wide context
2. Read the relevant domain overview (`AI_OVERVIEW.md`, `ANIM_OVERVIEW.md`, `REPLICATION_MATRIX.md`) for the task at hand
3. Drill into specific Tier 1 `.md` files for individual assets
4. Request a `DeepDump` only if Tier 1 lacks the detail needed
5. Never re-scan the project from scratch when the inventory exists

---

## 8. Per-Agent Rules

- **Scope lock:** only write to `D:\Work\blueprintexporter\blueprint-exporter\`. Engine install is read-only. DOW project tree is read-only.
- **No modifications to DOW.** The inventory is non-invasive — it loads assets via commandlet, introspects, writes documentation elsewhere, exits.
- **No editor GUI.** Every run is headless via `UnrealEditor-Cmd.exe` with `-nullrhi -unattended -nopause`.
- **Streaming memory pattern.** Load, dump, unload, GC. Never bulk-load.
- **Failures don't abort.** Per-asset resilience. Aggregate failure counts at the end.
- **Deterministic output.** Same input CL → byte-identical output bytes across runs. Explicit ordering rules:
  - **Variables:** emitted in declaration order (`TArray<FBPVariableDescription>` preserves order — do **not** re-sort)
  - **Functions:** alphabetical by `FName`, stable across runs
  - **Components:** SCS tree traversal order (depth-first, child order as authored), **not** map-key iteration order
  - **Pins & connections:** pin index order within a node; connections sorted by target node GUID then pin index
  - **References:** alphabetical by package path
  - **No GUIDs in Markdown.** GUIDs go only in `.meta.json` where they're needed for machine processing. Markdown uses stable names.
  - **No timestamps in file contents.** Timestamps live only in `RUN_LOG.md`.
  - **No absolute paths** (DOW location varies across machines). Use `/Game/...` package paths only.

---

## 9. Git Discipline

- One commit for the bootstrap (plugin changes adding the commandlets)
- One commit per inventory run, message format:
  ```
  inventory: DOW @ CL <p4_cl> (<date>)

  Phase 0: <summary>
  Phase 1: <count> assets inventoried, <n> failed, <m> partial
  Phase 2: aggregates regenerated
  ```
- Separate commits for code fixes to the commandlets vs. inventory output updates
- **Do not push.** Pushing happens at the end with Niclas.

---

## 10. Output Specification

Every file in `ProjectInventory/` is Markdown or JSON. No binary. No editor-specific formats.

Every file is:
- Human-readable
- Claude-Code-readable
- Diffable line-by-line
- Searchable via ripgrep

**This is the unlock.** Once the inventory exists, every subsequent workstream (replication audit, Steam Relay integration plan, playtest risk assessment, AI review, new-hire onboarding) reads text instead of rescanning the project.

---

## 11. Failure Modes & Mitigations

- **Memory blowout:** streaming pattern + GC cadence. If it still happens, lower batch size or split runs by asset class.
- **Commandlet crash mid-run:** resume support via `-ResumeFrom=<last_completed_asset>`. Manifest from Phase 0 provides the full asset list, so resume is a matter of skipping already-written files. Resume correctness must be verified before the first full run (see Section 12.4 step 16).
- **Asset load failures from plugin dependencies:** DOW requires its own plugins to be enabled. Ensure the commandlet runs against DOW's `.uproject` so plugin resolution is correct. Document any plugins that must be enabled.
- **Output size too large for practical review:** Tier 1 Summary mode keeps per-asset files manageable. Aggregates are the primary read surface. Deep dumps are rare.
- **Engine version drift:** commandlets are pinned to UE 5.7. If UE_DOW upgrades, commandlets need a re-compile and a re-run.
- **Stale plugin DLL in DOW:** junction points at `BuiltPlugin/`, so DOW always loads whatever the last `RunUAT BuildPlugin` produced. Skipping the full build flow and running a bare `Build.bat` will leave DOW loading a stale DLL without warning. Always follow the full build flow in CLAUDE.md.
- **Inherited serializer gaps:** the inventory reuses `FBlueprintSerializer`. Any partial coverage there (Motion Matching internals, Chooser Table columns, `FInstancedStruct` in State Tree) is silently inherited. Calibration slice (Section 12.4) exists to surface these before the full run.

---

## 11A. Operational Requirements

These are first-class requirements, not polish — they determine whether the first run is trustworthy and diagnosable.

**Atomic writes.** Every output file is written as `<name>.md.tmp` and `rename()`'d on close. A crashed run never leaves partial files claiming to be complete. Resume logic treats only fully-renamed files as done.

**Heartbeat logging.** Phase 1 emits one log line per asset:
```
[1247/1893] /Game/AI/BT_Enemy_Heavy  (coverage=100%, elapsed=42m, ETA=31m)
```
Plus a rolling ETA update every 30 seconds even mid-asset (slow AnimBPs can take minutes). A silent 2-hour run is indistinguishable from a hung one; heartbeat makes that distinguishable from the first minute.

**GC cadence decision (explicit, not fragile).** `CollectGarbage()` after every N assets doesn't release packages held by hard-ref cascades. Two options, decide upfront:
- **Option A — Accept higher steady-state memory.** GC every 50 assets, accept that the resident set grows with reference density. Simpler. Needs ~16-32GB RAM comfortable for DOW.
- **Option B — Explicit per-asset `UnloadPackage`.** After introspecting an asset, force-unload its package. Tighter memory but risks breaking reference resolution for the next asset.

Default: **Option A**, because the scan is a one-shot overnight run and Niclas's workstation has the RAM. Revisit only if memory becomes a problem.

**Scoreboard in INDEX.md.** Every run ends by writing a baseline block at the top of `INDEX.md`:
```
## Run Scoreboard

| Metric                    | Baseline | Last Run | Delta |
|---------------------------|----------|----------|-------|
| Assets manifested         | 1893     | 1894     | +1    |
| Assets introspected       | 1847     | 1849     | +2    |
| Failed loads              | 12       | 11       | -1    |
| Partial loads             | 34       | 33       | -1    |
| Coverage <100%            | 47       | 46       | -1    |
| HEALTH warnings           | 128      | 126      | -2    |
```
First run establishes the baseline. Every subsequent run flags deltas automatically — regression detection without hand-authored expectations.

**Determinism verification script.** `scripts/verify_determinism.ps1` runs Phase 1 against a fixed filter twice, diffs outputs with `git diff --no-index`, exits non-zero on any diff. Run before trusting any output.

---

## 12. Bootstrap Order

### 12.1 Pre-code (gate items from CLAUDE.md review)

1. **Plugin discovery junction** (manual, Niclas-only): `mklink /J "D:\Work\UE_DOW\game\Plugins\BlueprintExporter" "D:\Work\blueprintexporter\blueprint-exporter\BuiltPlugin\BlueprintExporter"`. Confirm UE can resolve the plugin before any code is written.
2. **Version bump:** increment the plugin's minor version across all seven drift locations per the plugin's CLAUDE.md rules. Four new commandlets = new subsystem, which meets the minor-bump criteria. Do not proceed until all seven locations are in sync.
3. **Update CLAUDE.md Project Structure** section to include the four new commandlets under `Source/BlueprintExporter/Private/Commandlets/`.

### 12.2 Code

4. Create `Plugins/BlueprintExporter/Source/BlueprintExporter/Private/Commandlets/ProjectManifestCommandlet.{h,cpp}`
5. Create `ProjectInventoryCommandlet.{h,cpp}`
6. Create `AggregateInventoryCommandlet.{h,cpp}`
7. Create `DeepDumpCommandlet.{h,cpp}`
8. Update `BlueprintExporter.Build.cs` to include `AssetRegistry`, `AssetTools`, `BlueprintGraph`, `AnimGraph`, `UMGEditor`, `AIModule`, `GameplayTasksEditor`, `StateTreeModule`, `StateTreeEditorModule`, `SmartObjectsModule`, `Chooser`, `PoseSearch`, `GameplayAbilities` (as applicable to what DOW uses) for introspection
9. Add atomic-write helper and heartbeat logger to shared utility code

### 12.3 Build (not just "compile")

10. Follow CLAUDE.md's full build flow: `Source/` → `BuiltPlugin/` sync → `RunUAT BuildPlugin` → binary copy-back. Do **not** stop at a bare `Build.bat` — DOW would load a stale DLL via the junction.
11. Verify the junction resolves the freshly-built plugin: DOW's editor startup log should show the bumped version number.

### 12.4 Calibration slice (before the full run)

12. Run Phase 0 (Manifest) against DOW. Review `MANIFEST.md`.
13. Run Phase 1 with `-Filter=/Game/AI/*` as a **calibration slice**. AI surfaces are the ambitious ones (State Tree `FInstancedStruct`, BT custom tasks, Perception) and will expose any serializer coverage gaps inherited from the existing `FBlueprintSerializer` before committing to a 1–2 hour full run.
14. Review coverage percentages in the slice's `HEALTH_REPORT.md`. If coverage is below expectations on AI assets, **stop and extend the serializer** before the full run. Silent partial coverage on 1,500 assets is worse than an abort.
15. Run `scripts/verify_determinism.ps1` against the slice: two runs, same CL, byte-identical output. If not identical, fix determinism before proceeding.
16. **Resume-correctness test:** start a Phase 1 slice run, `taskkill /F` at ~50% progress, re-run with `-ResumeFrom`. Confirm final output byte-matches an uninterrupted run of the same slice. This proves resume is safe before trusting it on the overnight full run.

### 12.5 Commit

17. Commit bootstrap (plugin changes, version bumps, CLAUDE.md updates, scripts) as one atomic commit.
18. Commit calibration slice output separately, labeled as calibration.

### 12.6 Full run

19. Run Phase 1 overnight without `-Filter`, with heartbeat logging on.
20. Run Phase 2 (Aggregates).
21. Commit full inventory output.
22. Hand off to downstream workstreams (replication audit, Steam Relay plan).

---

## 13. Final Deliverable

A committed `ProjectInventory/` directory inside `D:\Work\blueprintexporter\blueprint-exporter\` containing:
- `MANIFEST.md`
- `INDEX.md`
- `CLASS_TREE.md`
- `DEPENDENCY_GRAPH.md` (+ `.dot`)
- `REPLICATION_MATRIX.md`
- Domain overviews (`AI_OVERVIEW.md`, `ANIM_OVERVIEW.md`, `UI_OVERVIEW.md`, `GAS_OVERVIEW.md` if applicable, `STRUCTS_ENUMS.md`)
- `HEALTH_REPORT.md`
- `FAILED_LOADS.md`, `PARTIAL_LOADS.md`
- `Assets/` tree mirroring DOW's `Content/` layout, one `.md` + `.meta.json` per logic-bearing asset
- `RUN_LOG.md` with timing and CL stamps for each run

This is the ground truth for every subsequent DOW engineering question. Hand off to Niclas for review, then proceed to the replication audit and Steam Relay plugin work with the inventory as reference.
