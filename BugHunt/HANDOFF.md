# Bug-hunt HANDOFF

Out-of-scope findings and follow-up items surfaced during the programmatic
bug hunt but not addressed in this pass. Each item notes *why* it's deferred
and *where* to pick it up.

---

## 1. ApplyComponents is a stub — all component data is silently dropped on import

**Location:** `Source/BlueprintExporter/Private/Serialization/BlueprintDeserializer.cpp` (around `FBlueprintDeserializer::ApplyComponents`)
(function `FBlueprintDeserializer::ApplyComponents`).

**Evidence:** `BP_NPC_Perception` round-trip diff shows the source has a full
`components` array (AIPerceptionComponent with nested `FInstancedSubobject`
`SenseConfig` entries for Sight + Hearing), and the target has none.
`BP_SCSMonster` passes round-trip only because its semantic diff doesn't
currently count missing components as "nodes / variables / functions changed"
— the underlying data is still lost.

**Scope to fix:** Non-trivial. Needs:
- Recreate `USCS_Node`s from `FExportedComponent` entries, matching
  attachment hierarchy.
- Re-apply each `FExportedComponentProperty` via `ImportText_Direct` /
  property iteration, with special handling for
  `bIsInstancedSubobject` (walk `SubobjectJsonValues` and instantiate the
  nested class, recursively applying its properties).
- Remove the one-line "partially supported" warning.
- Extend `FBlueprintDiffEngine` to count component drift so regressions
  show up in the diff counters rather than only in the change list.

**Suggested phasing:** implement bare component recreation first (class +
attach-to-parent + simple scalar properties), validate on `BP_SCSMonster`,
then layer in instanced subobject support for `BP_NPC_Perception` and any
GAS/StateTree fixtures that exercise `FInstancedStruct`.

---

## 2. WidgetBlueprint widget tree not reconstructed on import

**Location:** Same deserializer. The import pipeline doesn't have any
WidgetBlueprint-aware branch — `UWidgetTree`, `RootWidget`, and nested
`UPanelSlot` data are written by the exporter but the importer doesn't
read them back.

**Evidence:** `BP_WidgetTree` round-trip fails with non-zero `bHasChanges`.

**Scope to fix:** Add a `UWidgetBlueprint`-specific post-pass that mirrors
the exporter's widget-tree serialization — construct each widget via
`WidgetTree->ConstructWidget`, re-parent per-slot, apply typed slot data.
Likely 100-200 lines of new code; safest to keep it in a separate file
(`Private/Serialization/WidgetBlueprintDeserializer.cpp`) rather than
bloating `BlueprintDeserializer.cpp` further.

---

## 3. RepNotify metadata round-trips lossy (export half done)

**Status:** Export-side fixed in `a857746` — `FExportedVariableFlags` now
carries `bRepNotify` + `RepNotifyFunc`, `BlueprintSerializer` populates
them, and `ToJson`/`FromJson` read/write the new keys. What remains:

**Location:** `Source/BlueprintExporter/Private/Serialization/BlueprintDeserializer.cpp`
(`FBlueprintDeserializer::ApplyVariables`).

**Evidence:** `BP_NetRep` round-trip still fails with *"Found more than
one function with the same name OnRep_HealthLow"* at compile time.
`ApplyVariables` sets `CPF_Net` when `bReplicated` is true but never
re-applies `CPF_RepNotify` or `RepNotifyFunc` from the JSON, so the
defensive guard committed in `6620aaf` can't fire on a freshly-imported
BP — the flag it looks for isn't there.

**Scope to fix (import half):**
- In `ApplyVariables`, when the exported `Flags.bRepNotify` is true:
  set `Var.PropertyFlags |= CPF_RepNotify` and
  `Var.RepNotifyFunc = FName(*Flags.RepNotifyFunc)`.
- That's it. Schema is already in place. Once the flag round-trips,
  `6620aaf`'s `SkipAsRepNotify` pre-collect starts doing real work and
  the duplicate-function compile error disappears.

---

## 4. Inherited-Blueprint compile errors ("function named 'None'")

**Evidence:** `BP_InheritanceChain` (3-level chain: Grandparent → Parent →
Child, all AActor-derived) fails round-trip because the re-imported child
BP fails compile with four *"Could not find a function named 'None' in
'BP_InheritanceChain'"* errors.

**Likely cause (not confirmed):** Inherited-variable or inherited-event
node references whose `memberParentClass` resolves to the *source's*
parent BP (`/Game/TestBlueprints/BP_InheritanceChain_Parent`) rather than
any path reachable from the sandbox target BP. The member-name lookup
then falls back to `NAME_None`.

**Reproduction:**
```
UnrealEditor-Cmd.exe BugHunt/TestProject/BugHunt.uproject ^
  -run=RunBugHunt -Area=Inheritance -nullrhi -unattended -nopause
```
Then inspect `BugHunt/TestProject/Saved/BugHunt/Inheritance/BP_InheritanceChain.import.json`
for nodes whose `memberParentClass` points at `/Game/TestBlueprints/...`
(which is correct — the parent BPs do live there) yet fail to resolve
at compile time for the target at `/Game/_Roundtrip/...`. The bug is
most likely in how the deserializer re-hydrates `FMemberReference`s
whose `GuidFromParent` or `bSelfContext` needs re-basing.

**Scope to fix:** Medium. Start with `BlueprintDeserializer.cpp:955-995`
(the `CallFunction` branch — member-reference resolution). May also
touch `VariableGet`/`VariableSet` branches for inherited variables.

---

## 5. `BP_GASP_AnimBP` — no programmatic path without a USkeleton asset

The generator currently marks this fixture as *skipped* with reason
`No USkeleton available in TestProject without imports`. Generating a
GASP-style AnimBP (Motion Matching, Chooser Table, linked anim layers,
Control Rig) programmatically is feasible but requires at minimum a
`USkeleton` and a handful of `UAnimSequence`s. Creating those
programmatically from scratch (as the brief requires — "every fixture
is generated programmatically") is realistic only if we accept a
throwaway skeleton with zero bones and placeholder anims that will
fail to compile against GASP itself.

**Recommendation:** out-of-scope for this pass. Defer to a follow-up
harvested-asset hunt where a real GASP skeleton can be dropped into
`BugHunt/TestProject/Content/Fixtures/` and the generator uses it. Captured
in the report's coverage-gaps section.

---

## 6. `BP_NPC_SmartObject` — SmartObjects module not in plugin deps

The generator is structured to handle this (it emits a skipped result
with an explicit reason) but the actual module wasn't added to
`BlueprintExporter.Build.cs` because adding it without verifying
editor availability on this machine risks breaking the existing build.

**Recommendation:** add `SmartObjectsModule` as an optional module in
`BlueprintExporter.Build.cs` (mirror the `WITH_STATETREE_SUPPORT`
pattern), then implement `GenBP_NPC_SmartObject` properly. One-commit
scope; the helper infrastructure is already in place.

---

## 7. Diff engine should count component and widget drift

Currently `FBlueprintDiffResult` has counters for nodes / variables /
functions / connections / layout, but no counter for components or
widget-tree changes. `BP_SCSMonster` passes round-trip today even
though `ApplyComponents` is a stub, because the diff engine doesn't
surface the lost components as a numeric delta — only as change-list
entries (which `RunBugHuntCommandlet` doesn't currently print).

**Recommendation:** extend `FBlueprintDiffResult` with
`ComponentsChanged` / `WidgetChanges` counters, and teach the bug-hunt
orchestrator to fail when any change-list entry exists, not only when
a numeric counter trips.

---

## 8. Areas the roundtrip oracle never ran on this pass

The brief lists 18 agent areas. This pass consolidated many of them
into a single `RunBugHuntCommandlet` catalog, but several areas have
no dedicated fixture coverage yet:

- **Pin types** beyond the basic zoo (no wildcard, no split struct, no
  delegate-pin fixture)
- **Event dispatchers + bound events** (BP_NodeZoo has a custom event
  but no delegate binding)
- **Timeline nodes** (covered by neither fixture)
- **EQS queries**, **Niagara/Material** BPs, **Gameplay Tags**,
  **Soft/hard refs with redirectors** — all zero coverage

These are pure fixture-generator additions (one function each in
`GenerateTestBlueprintsCommandlet.cpp`). Each should be added before
the associated area of the deserializer is audited. Noted in the
report under "coverage gaps".
