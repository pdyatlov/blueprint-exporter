# BlueprintExporter Bug Hunt Brief

> **Reading note:** Paths below (`TestProject/`, `Source/BlueprintExporterTests/`)
> describe the *original* plan. The current repo layout relocates the bug-hunt
> tooling under `BugHunt/` — see `BugHunt/README.md` for the actual paths and
> current run commands. Sections 0–10 are preserved as-written; §11 "Notes
> from first execution" is the delta.

**Target:** BlueprintExporter plugin for UE 5.7
**Project context:** Den of Wolves — first-person co-op heist, GASP-based animation, ambitious NPC AI (State Tree, BT, Perception, Smart Objects, potentially Mass/GAS)
**Mission:** Spawn parallel Claude Code subagents to hunt and fix bugs in the Blueprint export/import pipeline. Blueprints are structurally messy — nested graphs, polymorphic pins, hidden metadata, domain-specific node types — so each agent owns one facet of that complexity.

---

## 0. Working Directory Constraint (NON-NEGOTIABLE)

**All work happens inside `D:\Work\blueprintexporter\blueprint-exporter`.** One exception: **read-only** access to the engine install at `C:\Program Files\Epic Games\UE_5.7`.

**Allowed:**
- Read, write, modify, commit anything inside `D:\Work\blueprintexporter\blueprint-exporter`
- Execute `C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe` against the test project
- Read engine source, headers, and samples under `C:\Program Files\Epic Games\UE_5.7\` for reference (how UE serializes Blueprints, K2Node APIs, State Tree internals, GASP samples, etc.)

**Forbidden:**
- Writing, modifying, or deleting anything under `C:\Program Files\Epic Games\UE_5.7\`
- Touching the UE_DOW depot or any other project on the machine
- Reaching into any other path for assets, configs, or tools
- **No assets are fetched from UE_DOW or any other project this run.** Every fixture is generated programmatically by the agents.

If an agent determines it needs something outside these two paths, it stops and reports to `HANDOFF.md` rather than reaching out.

All relative paths in this brief resolve against `D:\Work\blueprintexporter\blueprint-exporter\`.

---

## 1. Pipeline Prerequisite (bootstrap before agents spawn)

The bug hunt runs against a **programmatic, headless pipeline**. No manual editor use, ever. Bootstrap must exist before any agent is spawned.

### Test project

Minimal `.uproject` that hosts the plugin and fixtures. Lives in the plugin repo under `TestProject/`.

```
BlueprintExporter/
├── Source/
│   └── BlueprintExporter/                  # the plugin itself
├── Source/BlueprintExporterTests/          # editor-only test module
│   ├── Commandlets/
│   │   ├── GenerateTestBlueprintsCommandlet.cpp
│   │   ├── BlueprintExportRoundtripCommandlet.cpp
│   │   └── RunBugHuntCommandlet.cpp
│   └── Tests/                              # one file per area
├── BlueprintExporter.uplugin
└── TestProject/
    ├── BlueprintExporterTests.uproject
    ├── .gitignore                          # Saved/, Intermediate/, DDC/, Binaries/
    ├── Content/
    │   ├── TestBlueprints/                 # generated .uasset fixtures (committed)
    │   └── Fixtures/                       # generated placeholder meshes/anims/skeletons
    └── Config/
        └── DefaultEngine.ini
```

Generate the `.uproject` JSON directly — no GUI:

```json
{
  "FileVersion": 3,
  "EngineAssociation": "5.7",
  "Description": "BlueprintExporter plugin test bed",
  "Modules": [],
  "Plugins": [
    { "Name": "BlueprintExporter", "Enabled": true }
  ]
}
```

### Core commandlets

**1. `GenerateTestBlueprintsCommandlet`** — builds all fixture Blueprints programmatically via `FKismetEditorUtilities::CreateBlueprint`, `FBlueprintEditorUtils`, K2 node APIs. One generator function per area. Output lands in `Content/TestBlueprints/`. Run once, commit the generated `.uasset` files. Regenerate only on engine upgrade or when extending the fixture set.

**2. `BlueprintExportRoundtripCommandlet`** — the oracle. Takes a BP path, runs export → re-import → diff. Exit 0 = identical, non-zero = bug with structured diff on stdout. Supports byte, semantic, and compile-equivalence diff modes.

```
UnrealEditor-Cmd.exe TestProject/BlueprintExporterTests.uproject ^
  -run=BlueprintExportRoundtrip ^
  -TargetBP=/Game/TestBlueprints/BP_GASP_AnimBP ^
  -OutDir=<tmp> -DiffMode=semantic ^
  -nullrhi -unattended -nopause
```

**3. `RunBugHuntCommandlet`** — orchestrator. Single entry point per area. Returns one JSON report on stdout and one exit code.

```
UnrealEditor-Cmd.exe <uproject> -run=RunBugHunt -Area=<name>
```

Steps:
1. Regenerate fixtures if stale
2. Run automation tests matching `BlueprintExporter.<Area>.*`
3. Run roundtrip on every fixture in that area
4. Emit JSON report, exit 0 only if everything passes

---

## 2. Fixture Priorities (UE 5.7 + GASP + ambitious AI)

Build fixtures in this order. Tier A is highest-risk, most likely to surface real exporter bugs.

### Tier A — build first

1. **`BP_GASP_AnimBP`** — GASP-style layered AnimBP: Motion Matching node, Chooser Table reference, linked anim layers, state machines, blend spaces, Control Rig node, orientation/stride warping
2. **`BP_NPC_StateTree`** — State Tree asset with nested tasks, conditions, transitions, referenced from an AIController BP
3. **`BP_NPC_BehaviorTree`** — BT with custom BP-authored tasks/services/decorators, Blackboard with every key type
4. **`BP_NPC_Perception`** — AIController + AIPerceptionComponent with sight/hearing/damage/team configs, stimuli source, perception event bindings to BT/StateTree
5. **`BP_NPC_SmartObject`** — SmartObjectDefinition + a BP that claims and uses it

### Tier B

6. **`BP_NPC_Full`** — realistic NPC tying Tier A together: GASP AnimBP + AIController + perception + BT/StateTree + Smart Object usage
7. **`BP_ChooserTable_Driver`** — BP driving a Chooser Table with struct inputs (exercises `FInstancedStruct`)
8. **`BP_PoseSearch_Config`** — BP referencing a PoseSearchDatabase with schema/channels
9. **`BP_EQS_Query`** — EQS query with generators and tests
10. **`BP_GAS_Ability`** — GameplayAbility BP with tasks and tags (if NPCs use GAS)

### Tier C — structural baseline

11. `BP_NodeZoo` — every K2Node subclass
12. `BP_PinHell` — wildcards, split structs, arrays/sets/maps, delegate pins
13. `BP_InheritanceChain` — 5-deep parent chain with overrides at each level
14. `BP_SCSMonster` — deep component attachment hierarchy with per-instance overrides
15. `BP_MacroMania` — macro instances, macro libraries, tunnels
16. `BP_WidgetTree` — nested user widgets, named slots, bindings, animations
17. `BP_NetRep` — RepNotify, RPCs (Server/Client/Multicast, Reliable), replication conditions, push model
18. `BP_StructEnumZoo` — user-defined structs/enums with every property type

Placeholder assets (skeleton, a few anim sequences, a basic mesh) needed by GASP/PoseSearch fixtures must also be generated programmatically into `Content/Fixtures/` and committed. No assets are imported from outside the working directory.

---

## 3. Agent Areas (one agent each)

Drop any area that doesn't apply to Den of Wolves. Don't spawn dead agents.

1. **Node serialization** — every K2Node subclass, custom nodes, collapsed graphs, tunnels
2. **Pin types & connections** — wildcard pins, split structs, arrays/sets/maps, delegate pins, default values, orphaned pins
3. **Variables & properties** — instance vs local, replication flags, metadata, inherited overrides, sparse class data
4. **Functions, macros & interfaces** — inputs/outputs, pure/const, latent, interface implementations, macro instances
5. **Components & SCS** — inherited components, attachment hierarchy, per-instance overrides, child actor components
6. **Event graphs & construction script** — event dispatchers, bound events, input events, timeline nodes
7. **Inheritance & references** — parent class changes, soft/hard object refs, circular refs, redirectors
8. **AI & Behavior Trees** — BT tasks/services/decorators as BPs, Blackboard key refs, EQS generators/tests, AIController BPs
9. **State Tree** — `UStateTree` assets, tasks, conditions, transitions, `FInstancedStruct` serialization
10. **Perception & sensing** — AIPerceptionComponent, sense configs (sight/hearing/damage/team), stimuli source, perception bindings
11. **Smart Objects & Mass** — `USmartObjectDefinition`, slots, claim handles, Mass traits/processors if used
12. **Animation Blueprints (GASP)** — AnimGraph nodes, state machines, transition rules, blend spaces, anim notifies, sync groups, linked anim graphs, anim layer interfaces, Motion Matching, Chooser Tables, Control Rig nodes
13. **Gameplay Ability System** (if used) — GameplayAbility BPs, GameplayEffect BPs, ability tasks, attribute sets, gameplay cues, tag containers
14. **Widget Blueprints (UMG)** — widget trees, named slots, bindings, animations, designer vs graph data
15. **Niagara/FX & Materials** — Niagara emitter/system BPs, material function BPs, parameter collections
16. **Networking & replication** — RepNotify, replicated variables, RPC specifiers, replication conditions, push model
17. **Enums, structs & data assets** — user-defined enums/structs, Primary Data Assets, Data Tables as BP references
18. **Roundtrip integrity** — export then re-import must produce an identical Blueprint (byte/semantic/compile-equivalence)

---

## 4. Headless Test Harness

Every agent verifies fixes via `UnrealEditor-Cmd.exe`. Zero manual editor runs.

**Base automation command:**
```
UnrealEditor-Cmd.exe TestProject/BlueprintExporterTests.uproject ^
  -run=Automation ^
  -ExecCmds="Automation RunTests <TestFilter>; Quit" ^
  -nullrhi -unattended -nopause -nosplash -nosound ^
  -log -LogCmds="LogAutomationController Verbose"
```

**Per-area test filter:** agents run a scoped filter matching their area, e.g. `BlueprintExporter.GASP_AnimBP.*`, `BlueprintExporter.StateTree.*`, `BlueprintExporter.Perception.*`. If no tests exist for an area, first job is to write them.

**Roundtrip is the oracle.** When in doubt: export → import → diff. Silent data loss is the worst bug class here. Agents must not close a bug without a green roundtrip on every fixture in their area.

**Log parsing contract:**
- `LogAutomationController: .* Result=\{Success\}` → pass
- `LogAutomationController: .* Result=\{Fail\}` → fail, capture preceding `Error:` lines
- `LogBlueprint: Error` / `LogBlueprint: Warning` during compile → treat as failures for compile-gate tests

**Performance discipline:**
- One editor invocation per test batch, not per test (cold start is 30s–2min)
- Agents run in parallel, each spawning its own editor process
- Cache DDC between runs so warmup only hits once

**Area-specific notes:**
- **GASP AnimBP, Niagara, Widget BPs:** `-nullrhi` may give false passes. For these areas, agents must also run once with a real RHI (`-windowed -resx=256 -resy=256`) before closing the bug.
- **AI/Perception/BT/StateTree:** Functional Tests in a dedicated test map, PIE headless with `-nullrhi`
- **Networking/replication:** dedicated server + client in the same test via Functional Test multiplayer support, still headless

---

## 5. Validation (single tier, programmatic only)

All validation runs against **generated fixtures only**. No harvested Blueprints, no imports from UE_DOW this run.

- Agents loop against `Content/TestBlueprints/` fixtures produced by `GenerateTestBlueprintsCommandlet`.
- Coverage gaps are closed by **extending the generator**, not by importing real assets. If an agent finds its area under-covered, it adds a new generator function, regenerates, commits the fixture, then continues the hunt.
- The roundtrip commandlet is the oracle for every fixture. No bug closes without a green roundtrip.

Acknowledged limitation: generated fixtures won't cover every real-world idiom or scale pattern from DOW. That's an accepted trade-off for this run — a follow-up hunt with harvested assets can happen later if needed.

---

## 6. Per-Agent Rules

- **Scope lock:** only fix bugs in your assigned area. Issues elsewhere → `HANDOFF.md`, never touched directly.
- **Global read:** read any file to understand context — especially engine headers and how UE itself serializes the thing you're exporting.
- **Loop until fixed:** reproduce → fix → verify → iterate. Don't exit until the bug is fixed or disproven.
- **Test against nasty Blueprints:** Tier A fixtures first, then Tier B, then Tier C. If your area has no fixture or existing fixtures don't stress your area hard enough, extend `GenerateTestBlueprintsCommandlet`, regenerate, commit the new fixtures, then proceed.
- **Roundtrip is the oracle.** No bug closes without a green roundtrip.
- **No drive-by changes.** Bugs only. No refactors, style changes, or unrelated cleanups.

### Agent loop

```
while not fixed:
    run: UnrealEditor-Cmd.exe -run=RunBugHunt -Area=<mine>
    parse JSON report
    if pass: exit loop
    identify failing fixture + assertion
    read relevant plugin source
    apply fix
    rerun RunBugHunt — must pass
    git add -p && git commit -m "fix(<area>): ..."
```

Zero human touch between bugs.

---

## 7. Git Discipline

- **One bug = one local commit.** After each bug is fixed and verified, commit immediately.
- **Commit message format:**
  ```
  fix(<area>): <short description>

  Root cause: <one or two lines>
  Fix: <what changed>
  Verification: <which fixture/test now passes, roundtrip exit code>
  ```
- Keep commits atomic — no bundling multiple bugs into one commit.
- **Do not push.** Pushing happens at the end with Niclas.
- If a fix needs to be reverted mid-hunt, use `git revert` rather than amending history.

---

## 8. Output Per Agent

- Area name
- Bugs found (one line each)
- Per bug: root cause, fix, verification result, commit SHA
- Out-of-scope findings → `HANDOFF.md`

---

## 9. Final Step

Consolidate all agents into `BUGHUNT_REPORT.md`:
- Summary table of bugs by area
- Roundtrip pass/fail matrix across all generated fixtures
- List of all commit SHAs in order
- Any `HANDOFF.md` items that need follow-up hunts
- Note any coverage gaps where a follow-up harvested-asset hunt might be warranted
- Hand off to Niclas for review and push.

---

## 10. Bootstrap Order (before agents spawn)

1. Generate `TestProject/BlueprintExporterTests.uproject`
2. Create `BlueprintExporterTests` editor-only module skeleton
3. Implement `GenerateTestBlueprintsCommandlet` with one generator per area (Tier A first), including programmatic generation of any placeholder meshes/anims/skeletons required
4. Implement `BlueprintExportRoundtripCommandlet` with byte + semantic + compile-equivalence diff modes
5. Implement `RunBugHuntCommandlet` orchestrator with JSON output
6. Commit bootstrap
7. Run `GenerateTestBlueprints`, commit generated fixtures
8. Spawn agents

---

## 11. Notes from first execution (2026-04-18)

First pass landed 8/14 round-trip passing, two real bugs fixed, four diagnosed.
Full findings in `BUGHUNT_REPORT.md`, open items in `HANDOFF.md`. This section
is the *delta to the plan itself* — things the next clean run should do
differently so it doesn't re-trip the same empirical landmines.

### 11.1 Scope calibration

**"Spawn parallel Claude Code subagents … one per area" is impractical at 18.**
18 concurrent UE headless instances each cold-starting (30s–2min) and
rebuilding plugin DLLs is too much machine and too much coordination for a
single session. Compress the 18 areas into one invocable catalog — see
`RunBugHuntCommandlet::GetAreaCatalog` — and drive it serially from one
shell. If parallelism is wanted, batch 2–3 distinct areas with separate
DDC locations, no more.

**Tier A is highest-value for the exporter but *hardest to generate*.** The
brief is right that Tier A surfaces the scariest bugs. But programmatic
generation of Tier A is the cliff: `BP_GASP_AnimBP` needs a real
`USkeleton`, `BP_NPC_SmartObject` needs `SmartObjectsModule` wired into
the plugin `Build.cs`. Tier C is trivial to generate and still surfaced
cross-cutting bugs this pass (override events, RepNotify duplication,
component silent-drop). **Revised order: Tier C first to validate the
oracle, then Tier A once the oracle is proven trustworthy.**

**Consider a narrow harvest-asset carve-out.** The "every fixture generated
programmatically" rule is what caused the `BP_GASP_AnimBP` skip. A single
hand-authored minimal `USkeleton.uasset` + two `UAnimSequence.uasset`s
committed to `TestProject/Content/Fixtures/` (not sourced from UE_DOW —
authored from scratch once) would unlock the entire animation surface for
round-trip coverage without violating the no-harvest spirit of the run.

### 11.2 Bootstrap landmines (Section 10 addendum)

Section 10's steps are directionally correct but silent on the traps that
cost the first pass ~20 minutes apiece to diagnose:

1. **The uproject name must not match any plugin module name.** When
   optional plugins mark the project "code-based", UBT auto-generates a
   project module stub in `TestProject/Intermediate/Source/` named after
   the uproject. Naming it `BlueprintExporterTests.uproject` alongside a
   plugin module `BlueprintExporterTests` produces duplicate C# class
   errors in the rules assembly with file-paths that falsely blame the
   plugin source. Use a neutral name — `BugHunt.uproject` worked.

2. **Plugin discovery via junction must be *scoped*, not whole-repo.** The
   instinct — junction `TestProject/Plugins/BlueprintExporter` at the
   repo root — fails: UBT then discovers `BuiltPlugin/BlueprintExporter.uplugin`
   as a second plugin with the same name, and the rules assembly gets
   two `class BlueprintExporter : ModuleRules` definitions. Correct
   shape:
   ```
   TestProject/Plugins/BlueprintExporter/
     ├── BlueprintExporter.uplugin   (copy of the root uplugin)
     ├── Source/                     (junction → ../../../Source)
     └── Config/                     (junction → ../../../Config)
   ```
   Gitignore the plugin folder. `BuiltPlugin/` and `_compile_check/` stay
   out of UBT's sight this way. `_compile_check/Plugins/BlueprintExporter/`
   exists on Niclas's machine as a separate ad-hoc compile-test copy — it
   must not be discovered during the hunt.

3. **Programmatic Blueprint creation footguns (UE 5.7):**
   - `FKismetEditorUtilities::CreateBlueprint` arg order is
     `(ParentClass, Outer, Name, Type, UBlueprint::StaticClass(),
     UBlueprintGeneratedClass::StaticClass(), Context)`. Swap the last
     two and the returned object is malformed — for `UWidgetBlueprint`
     this produces a null `WidgetTree` that crashes 20 lines later with
     a stack trace that does not point at the mistake.
   - For `UWidgetBlueprint` specifically, the `CreateBlueprint` path does
     **not** auto-create the `WidgetTree`. Construct it manually:
     `NewObject<UWidgetTree>(BP, TEXT("WidgetTree"), RF_Transactional)`.
   - `FBlueprintEditorUtils::SetVariableReplication` / `EVariableReplication`
     don't exist in 5.7. Use `GetBlueprintVariablePropertyFlags` +
     bitwise-or `CPF_Net` / `CPF_RepNotify`, and
     `SetBlueprintVariableRepNotifyFunc` for the notify-func name.
   - `FEnumEditorUtils::CreateUserDefinedEnum` returns `UEnum*`; cast to
     `UUserDefinedEnum*` before use.

4. **Generators must be idempotent-or-destructive, never in-between.** A
   generator that crashes halfway leaves half-saved fixtures on disk;
   a re-run that overlays on top produces duplicate custom events,
   `EdGraph`-on-`ObjectRedirector` rename assertions, and other artefacts
   that masquerade as plugin bugs. Guard every generator with "skip if
   asset exists on disk unless `-Force`". Decide this up front, not
   after the first crash.

### 11.3 Oracle design (Section 5 addendum)

**The diff engine matches nodes by `nodeId`, which embeds the node GUID.**
UE assigns fresh GUIDs to every newly-imported node, so without a scrub
pass every round-trip reports catastrophic drift (`N added, N removed`
where N is every node) regardless of actual correctness. The orchestrator
must recursively zero these fields on both source and target JSON before
calling `FBlueprintDiffEngine::Compare`:

  `blueprintGuid`, `variableGuid`, `graphGuid`, `nodeGuid`, `pinGuid`,
  `nodeId`, `pinId`, `contentHash`, `exportTimestamp`, `assetPath`,
  `sourcePackage`.

**This is the single most important oracle change.** Without it, the
first pass of any hunt burns hours chasing phantom bugs.

**`FBlueprintDiffResult` has no counter for components or widgets.**
`BP_SCSMonster` round-tripped as pass=true in the first pass even though
`ApplyComponents` silently dropped everything, because the numeric
counters (`NodesAdded` etc.) stayed zero. The orchestrator must fail on
any non-empty `Changes` array, not only on non-zero counters. Logged as
BUG-6 / HANDOFF item 7 — fix before trusting oracle greens.

### 11.4 Where to aim the hunt

The first pass proved the exporter is much more mature than the importer.
`ApplyComponents` is a one-line stub; `WidgetBlueprint` import doesn't
exist; `CPF_RepNotify` isn't reapplied; `FMemberReference`s don't re-base
across the source→sandbox package move. **Front-load
`Source/BlueprintExporter/Private/Serialization/BlueprintDeserializer.cpp`
audit next run.** Adding more fixtures without exercising the importer is
diminishing returns.

### 11.5 Distribution-pipeline hazard to resolve before next production build

The first pass added `BlueprintExporterTests` to the root
`BlueprintExporter.uplugin`'s `Modules` array. `CLAUDE.md`'s RunUAT
BuildPlugin pipeline syncs `Source/` into `BuiltPlugin/` and packages
the result as the shippable plugin — which would now drag in the test
module. Before the next production build:

- Either exclude `Source/BlueprintExporterTests/` from the sync step and
  leave `BuiltPlugin/BlueprintExporter.uplugin`'s `Modules` array with
  only `BlueprintExporter`, **or**
- Factor the test module out into its own sibling `.uplugin` (e.g.
  `BlueprintExporterTests.uplugin` in a sibling folder) so the main
  plugin's distribution uplugin stays untouched.

### 11.6 First-pass scoreboard (baseline for regression detection)

| | Before first pass | After first pass |
|---|---|---|
| Re-runnable round-trip oracle | no | yes (`-run=RunBugHunt -Area=<name>`) |
| Committed programmatic fixtures | 0 | 14 created + 2 explicitly skipped |
| Round-trip green fixtures | — | 8/14 |
| Bugs fixed | — | 2 (override events, oracle GUID scrub) |
| Bugs partially fixed | — | 1 (RepNotify defensive guard) |
| Open diagnosed bugs | — | 4 (see `BUGHUNT_REPORT.md` §2) |

A future run that scores below 8/14 on the same fixture set is a regression.
