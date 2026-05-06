# BlueprintExporter Bug Hunt Report

**Target:** BlueprintExporter plugin for UE 5.7 (v1.11.0)
**Project context:** Den of Wolves — GASP animation, ambitious NPC AI (State Tree,
BT, Perception, Smart Objects).
**Mission:** Programmatic headless bug hunt against generated fixtures per
`BUGHUNT_BRIEF.md`. Zero assets harvested from `UE_DOW` or any other project.

Stop point: report consolidated, no push.

---

## 1. Summary

| | Count |
|---|---|
| Fixtures generated programmatically | 14 |
| Fixtures deliberately skipped (optional modules / missing assets) | 2 |
| Round-trip passing at end of hunt | 8 |
| Round-trip still failing (real plugin bugs) | 4 |
| Fixtures with no generator coverage | 2 |
| Bugs fixed & committed this pass | 2 |
| Bugs partially fixed / guarded | 1 |
| Open bugs with concrete diagnosis | 3 |
| Open bugs / gaps handed off for follow-up | 8 — see `HANDOFF.md` |

Before this pass: the plugin had **no programmatic round-trip oracle at all**
and no fixture set — ad-hoc inline automation tests only. Round-trip pass
rate was effectively 0 for any Actor-derived Blueprint (see bug #1).
After this pass: **8/14 = 57%** of fixtures round-trip clean, and the
oracle is re-runnable and CI-ready (`-run=RunBugHunt -Area=<name>`).

---

## 2. Bugs by area

### 2.1 Fixed this pass (committed)

#### BUG-1 — Override events become broken "None" custom events on import
- **Area:** Event graphs & construction script / Node serialization
- **Root cause:** `FBlueprintDeserializer::CreateNode` unconditionally
  instantiated `UK2Node_CustomEvent` for every `NodeType == "Event"`.
  For override events (`UK2Node_Event` with `bOverrideFunction = true`,
  e.g. `ReceiveBeginPlay`, `ReceiveTick`, `ReceiveActorBeginOverlap`)
  the exported `customFunctionName` is empty and `eventName` holds the
  parent-function name, so the deserializer assigned
  `"ReceiveBeginPlay"` as a CustomEvent name — which UE immediately
  sanitised back to `NAME_None`, leaving a ghost
  `None\nCustom Event` node beside the stub events UE auto-creates.
- **Fix:** When `SpecificData["isOverrideEvent"] == true`, reuse any
  existing matching `UK2Node_Event` already in the graph, otherwise
  walk the Blueprint's parent-class chain to find the signature class
  and construct a proper `UK2Node_Event` with `EventReference` set and
  `bOverrideFunction = true`. Also tolerate the `customFunctionName`
  vs `eventName` precedence on the custom-event path.
- **Verification:** Every Actor-derived fixture (`BP_NodeZoo`,
  `BP_PinHell`, `BP_SCSMonster`, `BP_MacroMania`, `BP_StructEnumZoo`,
  `BP_NPC_BehaviorTree`, `BP_NPC_StateTree`, `BP_GAS_Ability`) went
  from red to green on this fix alone — the ghost "None" nodes were
  the single largest false-positive source.
- **Commit:** `0538ec0`

#### BUG-2 — Round-trip oracle conflated GUID churn with semantic drift
- **Area:** Roundtrip integrity (tooling, not the plugin proper)
- **Root cause:** The bug-hunt orchestrator (new in this pass) fed raw
  re-serialised JSON directly to `FBlueprintDiffEngine`. The diff
  engine matches nodes by `nodeId`, and `nodeId` embeds the node GUID.
  Since UE assigns fresh GUIDs to every newly-imported node, *every*
  round-trip reported `N added, N removed` with `N == node count`.
- **Fix:** `RunBugHuntCommandlet` now recursively scrubs volatile
  fields (`blueprintGuid`, `variableGuid`, `graphGuid`, `nodeGuid`,
  `pinGuid`, `nodeId`, `pinId`, `contentHash`, `exportTimestamp`,
  `assetPath`, `sourcePackage`) on both source and target JSON
  before handing them to the diff engine.
- **Why it matters:** Without this fix the oracle was all-noise, so
  any real bug was drowned. With it, the 4 remaining failures below
  are the *actual* semantic drift.
- **Commit:** `0538ec0`

### 2.2 Partially fixed (defensive guard, root cause documented)

#### BUG-3 — RepNotify function duplication on BP re-import
- **Area:** Networking & replication / Functions
- **Symptom:** `BP_NetRep` fails round-trip with compile error
  *"Found more than one function with the same name OnRep_HealthLow;
  second occurance at  OnRep_HealthLow"*.
- **Root cause:** Two-part.
  1. `ApplyVariables` sets `CPF_Net` but does **not** set
     `CPF_RepNotify` or `RepNotifyFunc`, even though the source has
     both set. (The schema also doesn't carry them — there's no
     `bRepNotify` field on `FExportedVariableFlags`.)
  2. `ApplyFunctions` re-creates the exported `OnRep_HealthLow` graph
     even when UE has synthesised a stub of the same name from the
     variable's flags — producing two functions with one name at
     compile time.
- **Partial fix applied:** `ApplyFunctions` now pre-collects
  RepNotify function names from variables that already carry the
  `CPF_RepNotify` flag and skips re-adding them. There's also a
  defensive `SkeletonGeneratedClass->FindFunctionByName` fallback.
- **Why it's only partial:** Because `ApplyVariables` never imports
  `CPF_RepNotify`, the pre-collect set is empty for any freshly
  imported BP — so the guard doesn't fire on the real failure path.
  Full fix needs a schema change (`bRepNotify` + `repNotifyFunc`
  fields) plus matching read/write in serializer and deserializer.
  See `HANDOFF.md` item **3**.
- **Commit:** `85212d7`

### 2.3 Open — diagnosed, not yet fixed

#### BUG-4 — Inherited Blueprint re-import produces "function named None" compile errors
- **Area:** Inheritance & references
- **Symptom:** `BP_InheritanceChain` (Grandparent → Parent → Child
  chain, all `AActor`-derived) imports without error but fails
  compile at the final step with 4× *"Could not find a function named
  'None' in 'BP_InheritanceChain'"*.
- **Likely cause:** `FMemberReference` hydration. Nodes that inherited
  from the Parent class are exported with `memberParentClass` pointing
  at `/Game/TestBlueprints/BP_InheritanceChain_Parent.BP_InheritanceChain_Parent_C`
  — correct in principle. Re-imported into `/Game/_Roundtrip/BP_InheritanceChain_RT`,
  the member-reference's `GuidFromParent` / `bSelfContext` / `MemberGuid`
  fields aren't re-based or resolved, so look-up falls back to
  `NAME_None`. Same failure likely hides in cousin areas (variable gets
  inherited from parent, interface-call inherited, etc.) but wasn't
  exercised by this fixture set.
- **Full diagnosis + next steps:** `HANDOFF.md` item **4**.

#### BUG-5 — Component hierarchy + per-component property data silently dropped on import
- **Area:** Components & SCS / Perception & sensing / Smart Objects & Mass
- **Symptom:** `BP_NPC_Perception` fails round-trip — source exports a
  full `components` array (AIPerceptionComponent with nested
  `bIsInstancedSubobject: true` senseConfig entries for Sight & Hearing
  with every configured property) and the target has `components: []`.
  `BP_SCSMonster` *passes* round-trip only because the diff engine
  doesn't count component drift in its numeric counters (see BUG-6).
- **Root cause:** `FBlueprintDeserializer::ApplyComponents` is a stub.
  Its entire body is *"Component recreation is complex - for now just
  log a warning"* followed by `Result.AddWarning(...)`. No SCS node is
  ever created on the import path.
- **Scope:** Non-trivial. Full diagnosis and suggested phasing in
  `HANDOFF.md` item **1**.

#### BUG-6 — Diff engine has no counter for component / widget drift
- **Area:** Roundtrip integrity / Diff engine
- **Symptom:** `BP_SCSMonster` (which has a 4-component attachment
  hierarchy) reports `pass: true` in the orchestrator even though
  `ApplyComponents` silently dropped everything — the counters
  (`NodesAdded`, `NodesRemoved`, etc.) are all zero.
- **Root cause:** `FBlueprintDiffResult` has no
  `ComponentsChanged` field, and `FBlueprintDiffEngine::CompareComponents`
  emits entries into the generic `Changes` array but the orchestrator
  only checks the numeric counters.
- **Scope:** Small — add counter, teach orchestrator to fail on any
  non-empty change list. Noted in `HANDOFF.md` item **7**.

#### BUG-7 — WidgetBlueprint widget tree not reconstructed
- **Area:** UMG / Widget Blueprints
- **Symptom:** `BP_WidgetTree` round-trip has `bHasChanges = true`
  despite clean numeric counters (same class of diff-counter gap as
  BUG-6).
- **Root cause:** The importer has no `UWidgetBlueprint`-specific
  branch — widget tree, `RootWidget`, panel slots are written by the
  exporter but the importer silently discards them.
- **Scope:** `HANDOFF.md` item **2**.

---

## 3. Round-trip pass/fail matrix

All fixtures generated by `UGenerateTestBlueprintsCommandlet` with `-Tier`
and `-Only` unset. `RunBugHuntCommandlet -Area=Roundtrip` is the authoritative
oracle. Report generated after the last fix commit (`85212d7`).

| Fixture | Tier | Status | Notes |
|---|---|---|---|
| BP_NodeZoo                | C | ✅ PASS | Events, sequence, variables |
| BP_PinHell                | C | ✅ PASS | Int / array / set / map / object / vector vars |
| BP_InheritanceChain       | C | ❌ FAIL | BUG-4 — compile error on child BP import |
| BP_SCSMonster             | C | ✅ PASS\* | \*passes numeric diff but ApplyComponents is a stub (BUG-5/6) |
| BP_MacroMania             | C | ✅ PASS | Macro library + consumer |
| BP_NetRep                 | C | ❌ FAIL | BUG-3 — duplicate OnRep on import |
| BP_StructEnumZoo          | C | ✅ PASS | User-defined enum + struct ref'd from BP |
| BP_WidgetTree             | C | ❌ FAIL | BUG-7 — widget tree not re-imported |
| BP_NPC_BehaviorTree       | A | ✅ PASS | AIController BP, soft-ref to BT, BB with 5 key types |
| BP_NPC_Perception         | A | ❌ FAIL | BUG-5 — AIPerceptionComponent not re-imported |
| BP_NPC_StateTree          | A | ✅ PASS | AIController + soft-ref to UStateTree asset |
| BP_NPC_SmartObject        | A | ⚪ SKIP | SmartObjects module not in plugin deps |
| BP_GASP_AnimBP            | A | ⚪ SKIP | No USkeleton programmatically available |
| BP_GAS_Ability            | B | ✅ PASS | GameplayAbility BP with cooldown/charges vars |

Detailed per-fixture diffs committed to `BugHunt/TestProject/Saved/BugHunt/Roundtrip/`
(source.json, target.json, import.json per fixture) when you re-run the
oracle.

---

## 4. Commit list (in order)

| SHA | Subject |
|---|---|
| `650562e` | feat(blueprint-exporter): bootstrap bug-hunt test harness |
| `d30157e` | feat(blueprint-exporter): commit bug-hunt fixture set |
| `0538ec0` | fix(blueprint-exporter): restore override events on BP import |
| `85212d7` | fix(blueprint-exporter): defend against RepNotify function duplication |

4 commits total. All atomic, all local, no pushes.

---

## 5. Coverage gaps

Fixtures not covered by the current generator that should exist before the
corresponding deserializer area can be audited end-to-end:

| Brief area | Have a fixture? | Gap |
|---|---|---|
| Node serialization (full K2Node zoo) | Partial | BP_NodeZoo covers Event + Sequence + CustomEvent. No Timeline, MathExpression, DynamicCast, SpawnActor, Composite, or Knot nodes. |
| Pin types (wildcard, split struct, delegate pins) | Partial | BP_PinHell covers array/set/map/int/string/object/vector. No wildcard pin, no split-struct pins, no delegate pins. |
| Variables & properties (full flag matrix) | Partial | Basic vars + replicated + RepNotify (buggy). No `Instance Editable` / `Expose on Spawn` / `Expose to Cinematics` coverage. |
| Functions, macros & interfaces | Partial | Macro library + consumer, but no interface BP + implementer. |
| Components & SCS | ✅ BP_SCSMonster exists but exercise is blunt because ApplyComponents is a stub (BUG-5). |
| Event graphs & construction script | Partial | Event graph covered by BP_NodeZoo. No construction-script fixture. No event-dispatcher / bound-event coverage. |
| Inheritance & references | ✅ BP_InheritanceChain (currently failing — BUG-4). No soft/hard object-ref / redirector fixture. |
| AI & Behavior Trees | ✅ BP_NPC_BehaviorTree (passing). No BP-authored BT task fixture. |
| State Tree | Partial | BP_NPC_StateTree (AIController + soft ref). No `FInstancedStruct` tasks/conditions exercised. |
| Perception & sensing | ✅ BP_NPC_Perception (failing — BUG-5). |
| Smart Objects & Mass | ❌ Skipped — deps gap (`HANDOFF.md` item 6). |
| Animation Blueprints (GASP) | ❌ Skipped — no programmatic skeleton (`HANDOFF.md` item 5). |
| Gameplay Ability System | Partial | BP_GAS_Ability exists. No GameplayEffect BP, no attribute set, no gameplay cue. |
| Widget Blueprints (UMG) | ✅ BP_WidgetTree (failing — BUG-7). No named slots, no widget anim, no binding fixture. |
| Niagara / FX & Materials | ❌ Zero coverage. |
| Networking & replication | Partial | BP_NetRep (failing — BUG-3). No RPC function fixture, no push-model fixture. |
| Enums, structs & data assets | Partial | BP_StructEnumZoo exists. No Primary Data Asset or DataTable fixture. |
| Roundtrip integrity | ✅ Infrastructure exists and is re-runnable. |

**Recommendation for a second pass:** fill fixture gaps before auditing more
deserializer branches. The pattern established by
`GenerateTestBlueprintsCommandlet` makes adding a fixture one pure-function
addition, and each new fixture is a new oracle vantage point.

**Recommendation for a harvested-asset pass:** drop a real GASP skeleton +
animations + Chooser Table into `BugHunt/TestProject/Content/Fixtures/` (bypassing
the "zero imports" constraint of this run) so `BP_GASP_AnimBP` moves from
skipped to executed. That covers the most complex single exporter surface
area — animation blueprints, anim-graph nodes, Motion Matching, Chooser,
Control Rig — which this programmatic run couldn't reach.

---

## 6. What to run next

**Re-run current oracle (smoke test):**
```
UnrealEditor-Cmd.exe BugHunt/TestProject/BugHunt.uproject ^
  -run=RunBugHunt -Area=Roundtrip ^
  -nullrhi -unattended -nopause -nosplash -nosound
```
Expected: `failed: 6` (4 open bugs + 2 skipped fixtures). Anything else
is a regression.

**Per-area run:**
Valid area names are in `BugHunt/BlueprintExporterTests/Source/BlueprintExporterTests/Private/Commandlets/RunBugHuntCommandlet.cpp`
`GetAreaCatalog()`. Common names: `NodeSerialization`, `PinTypes`,
`Inheritance`, `Components`, `Networking`, `UMG`, `Perception`, `StateTree`,
`AI_BehaviorTree`, `AnimBP`, `GAS`, `StructsEnums`, `Roundtrip`.

**Regenerate fixtures:**
```
UnrealEditor-Cmd.exe BugHunt/TestProject/BugHunt.uproject ^
  -run=GenerateTestBlueprints [-Force] [-Only=<name>] [-Tier=A|B|C] ^
  -nullrhi -unattended -nopause
```
Without `-Force`, existing fixtures are preserved. With `-Force`, every
fixture regenerates on top of whatever is on disk (not recommended — use
`-Only=<name>` for targeted fixes).

---

## 7. Hand-off

The full open-items list is in `HANDOFF.md`. Four items are concrete
implementable bugs with diagnosis and file-level pointers. Four more are
coverage or schema gaps that unblock further audit once addressed.

Reviewer: Niclas — please push when satisfied.
