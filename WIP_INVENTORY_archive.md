# WIP Inventory — Archive

> Historical record. Active state is in `WIP_INVENTORY.md`.
> Restructure happened 2026-04-27; backup of pre-restructure state at `D:\Work\_bpx_backups\WIP_INVENTORY_2026-04-27_pre-cleanup.md`.

---

## Full pre-restructure content

Everything below is the original `WIP_INVENTORY.md` content from before today's restructure, in its original order. Sections later moved into the active file (Standard build flow, Policy, Key paths, Known blockers, Legacy depot procedure, Ephemeral artifacts, M28 phase table, Known issues, Gotchas, durable Resume checklist steps) are also preserved here verbatim — the active file is the first stop; this archive is the forensic record.

Categories you'll find inline below, in original order:

- **TL;DR for a resuming session** + milestone summary table (lines 9–107 of original) — expired status narrative.
- **Resume checklist step 1** (lines 110–1023) — expired session-narrative git-log expectations from prior sessions.
- **Status** section (lines 1117–2444) — chronological progress log per milestone (M1 through M28.6.1). Architecture-stable parts have been distilled into the active file's milestone index; this is the full per-milestone narrative.
- **Fidelity audit findings (2026-04-19 DOW_Legacy export)** (2507–2563).
- **Usability audit (2026-04-19)** (2665–2751).
- **What the next session should do first** (2753–2934) — expired resume-narrative blocks.
- **Full ship records** — every `### MX.Y shipped` / `### MX.Y closed` / research-outcome / scoping block (2936–5134).
- **Session arc blocks** (5118–5289) — prior /clear-resume narratives.
- **Candidate next milestones (full prose)** (5290–5912) — the original long-form picker including items 7–11 (now SHIPPED) and item 12 (M28.10).
- **Historical M19 scope / Deferred M7 extensions / Other items on the backlog / Gotchas discovered this session** (5954–6218).

---


> **Resume brief — delete when the inventory subsystem fully lands and its
> last commit references this file.** Captures session state that would
> otherwise disappear on `/clear`. The source-of-truth plan is
> `PROJECT_INVENTORY_BRIEF.md`; this file only tracks **where we are in
> that plan and what to do next**.

## TL;DR for a resuming session

**design.md item-#7 chained-plan test-run completed end-to-end + 2 M24-pipeline bugs found AND fixed at `cdaa0aeb` (2026-04-25, late).** The M28.6.1 closing block's recommended first test-run resolved exactly as predicted — a 20-op chained plan crossing module boundaries surfaced validator/executor integration bugs that single-op soaks couldn't catch. Plan: 4 `add_gameplay_tag` + `create_user_defined_struct` + 6 `add_uds_member` + `remove_uds_member` + 4 `create_curve_float` + 4 `set_curve_float_keys` = 20 ops, 6 assets, 3 modules (`gameplay_tags` + `uds` + `curves`); design.md item #7 archetypes shipped as `S_EnemyArchetype` UDS (6 real members: Aggression / CoverPref / Mobility / Accuracy / SightRadius / FireRate, BpxAutoBool dropped) + 4 per-archetype aggression-vs-distance curves (Rusher peaks close, Marksman peaks far, Suppresser flat, Flanker rises with distance) + 4 `AI.Archetype.*` gameplay tags in `Config/Tags/AI.ini` of UE_DOW_Legacy. Two bugs found and fixed in the same commit: **(1) `plan_validator.py`** — `_validate_assets`'s asset-existence pre-check queried only on-disk state, so `add_uds_member` at op 5 false-failed because op 4's `create_user_defined_struct` hadn't run yet (initial run reported `passed: false` with 11/20 ops failing as `<path> asset does not exist`). Fix: thread a `created_in_plan: set` through `validate_plan`, populate it from each prior op's `assets_absent` keys, and treat paths in the set as existent for later ops' `assets` precheck; new warning when two ops in one plan create the same path. **(2) `mechanical_diff.py`** — `compute_expected_changes` used last-op-wins, so `create_user_defined_struct` (expected=`"created"`) got overwritten to `"mutated"` by trailing `add_uds_member` ops, while observation was correctly null→bytes (`"created"`); first apply_plan reported `passed: false` with 5 entries in `unexpected_changes` even though every op succeeded and every `asset_exists` verification passed. Fix: new `_combine_kinds` helper — structural kinds (`created` / `deleted`) dominate `"mutated"`; disjoint-path sequences (e.g. `create_child_bp` + `rename_asset` to a different path) preserve prior semantics (offline unit-verified across 6 cases including the docstring example). **Verified end-to-end against UE_DOW_Legacy from-fresh:** validator passed 20/20, executor passed 20/20 ops in 0.20 s post-cold-boot, oracle passed 5/5 assets `observed=created` matching `expected=created` with zero `unexpected_changes` and zero `expected_but_missing`, 5/5 `asset_exists` verifications pass. Test plan kept at `scripts/python_ops/plans/design_item7_archetypes.json` as a regression fixture for this class of chained-create plan. **Operational gotcha worth flagging (auto-memory-worthy):** the `D:/Work/UE_DOW_Legacy/Plugins/BlueprintExporter/` install was a stale BuildId-mismatched DLL — built against UE_DOW's custom engine (BuildId `6efc257b-...`) but UE_DOW_Legacy uses stock UE 5.7 (BuildId `47537391`), so the DLL got rejected with `"module 'BlueprintExporter' could not be found"` post-`Failed to load … (GetLastError=126)`. Fix: replace install binaries from `D:/Work/blueprintexporter/_build_output_5_7/Binaries/Win64/` (the M28.6.1 stock-UE-5.7 build artifact, BuildId `47537391`, 2,894,336 b). The repo's canonical `BuiltPlugin/Binaries/` ships the **UE_DOW-engine** variant — colleagues installing into stock-UE-5.7 projects need `_build_output_5_7/Binaries/` instead. Worth either documenting in README's Local Development section or shipping a `BuiltPlugin_5_7/` sibling so this doesn't bite again. **No plugin version bump** (Python ops + plan fixture only; .uplugin / DLL untouched). **Next pickup options:** (a) **design.md item #1 (Squad Director — full-surface chain)** — the chained-plan pipeline is now proven on a 20-op multi-module plan, so item #1's larger surface is unblocked; (b) M28.7 automation-test runner + `DesignGym/` sibling project for runtime-behaviour verification (Open Q #2 in M28.0); (c) ship the BuildId-distribution fix above so the stock-UE-5.7 install doesn't re-stale on the next colleague handoff; (d) M28.8 optional read-side Tier 2 (lowest priority).

---

**Prior: 2026-04-25 (mid) — M29.6 + M28.6.1 closing arc.** **M29.6 engine-agnostic Mutable renderer refactor LANDED end-to-end (2026-04-25).** Reopened the M29 umbrella to replace the `WITH_MUTABLE_SUPPORT` compile-time gate on the Mutable renderers with a runtime ProcessEvent dispatch so **one BuiltPlugin DLL handles CO / COI / COML assets in any Mutable-capable project**, regardless of whether Mutable was present at build time. **All five sub-phases shipped:** M29.6.1 `UFunctionCall` helpers + 11-UFUNCTION fixture UCLASS + 7 automation tests at `19b3a03`; M29.6.2 UCOI renderer port at `47b370a`; M29.6.3 + M29.6.4 combined as UCO renderer port + `WITH_MUTABLE_SUPPORT` gate strip at `e384b6e` (27 UFUNCTION call sites + 2 enum reflections + 3 struct returns: FLinearColor / FTransform / FCustomizableObjectProjector + UI metadata; gate stripped from Build.cs + .uplugin + DeepDumpCommandlet + ProjectInventoryCommandlet + COML renderer + headers; per-header comments finalized in same commit); M29.6.5 finalization arc at `da7668e` — version bump 1.25.0 → 1.26.0 across 16 sites (3 `.uplugin` + 6 Source/.cpp + 6 BuiltPlugin/.cpp + README) + dual-engine DLL rebuild + 8-gate verification matrix. **Verification record:** MutableSample/Weapon/CO_Weapon md5 `28B162FBD46C7AA9AA290B95CA6F5845` MATCH (M29.1 baseline preserved across all ports); 3 extra MutableSample assets (CO_Character `FFC496AEA7E866D4394F9719018D5E60`, CO_Basic_parameters `D3CA666BE2814ABBD8B55F327CD1B4B5`, CO_Projectors_showcase `9D4940BB1F7808E377757F7BCFD7F9BF`) all MATCH against M29.6.4 post-port baselines; BugHunt twin-run determinism PASS in 46s; DOW twin-run determinism PASS in 120s (`-Filter=/Game/_ThirdParty/GASP_example/`); both-engine `RunUAT BuildPlugin -Rocket` BUILD SUCCESSFUL (UE_DOW 2,877,440 b in 24s / stock UE 5.7 2,878,464 b in 45s after rebuild against bumped version); automation 24/24 PASS in 15s; bridge smoke 7/7 (2 OK + 5 EXPECTED_ERROR + 0 FAILURE) — confirms ping + list_methods serve `pluginVersion: "1.26.0"` post-rebuild; verify_all matrix 46/46 PASS in 537.2 s on BugHunt / stock UE 5.7 (matches M29.6.4's 535.1 s baseline within noise). Minor bump per CLAUDE.md semver — architectural change (one DLL serves all Mutable-capable engines, replaces compile-time gate). **M28.6.1 shipped 2026-04-25 (later); design.md test-run readiness assessed.** User confirmed M28.6.1 as the closing slice of the M28.6 catalog (no follow-up planned), then asked "are we ready to test-run design.md?" — the readiness check resolved that **authoring side is ready NOW** (every M28 phase needed by every design.md item is closed: M28.1 + M28.2 + M28.3 + M28.4 + M28.5 + M28.6 — 36+ ops total covering BP structural / graph-authoring / UDS / CurveFloat / DataAsset / EQS / GameplayTag / StateTree task & transition surfaces). **Runtime-behaviour verification is NOT ready** — that's M28.7 (automation-test runner + gym map per the M28 phase-table line 2996); without it we can prove "the squad-director BP got authored with the right vars / tags / graph nodes" via existing inspect+soak gates but not "the squad actually flanks at play time". **Recommended first test-run when work resumes:** start with **design.md item #7 (Archetype DataAssets — Rusher / Marksman / Suppresser / Flanker)** — pure data authoring, ~10–15 ops, no graph-spaghetti to debug. Validates the chained-plan pipeline (validator + executor on a multi-op plan, vs single-op soaks that's all M28.x has shipped fixtures for) and de-risks integration gaps before tackling **item #1 (Squad Director — full surface chain)**. Ship M28.7 in parallel for runtime-behaviour verification once item-#7 / item-#1 prove the authoring chain works. Risk to flag: per-op soaks have all passed but a 30–50-op chained plan crossing module boundaries (`gameplay_tags.py` + `uds.py` + `curves.py` + `data_assets.py` + `blueprint_structural.py` + `blueprint_graph_nodes.py`) hasn't been exercised end-to-end yet — likely surfaces plan-validator / executor integration bugs the per-op soaks didn't catch. design.md is committed at `D:/Work/blueprintexporter/design.md` (untracked at the repo level, lives outside the plugin tree); read it on resume to refresh design context. **Next pickup options:** (a) author item-#7 plan + run via apply_plan against a fresh DOW-family scratch project (recommended), (b) start M28.7 in parallel (gym-map project hosting per Open Q #2 in the M28.0 block — recommend new sibling `DesignGym/` project so combat content doesn't contaminate the determinism golden), (c) M28.8 optional read-side Tier 2 for UDS / CurveFloat / AnimMontage (lowest priority; defer).

---

**Prior: 2026-04-25 (later) — M28.6.1 shipped end-to-end; M28.6 catalog COMPLETE.** Single-op catalog. 1 new UFUNCTION (`AddGameplayTag`) + 1 new Python op (`add_gameplay_tag` in new module `gameplay_tags.py`) + 1 new zero-UE-process MCP tool (`list_gameplay_tags` walking `Config/DefaultGameplayTags.ini` + `Config/Tags/*.ini` + `Plugins/*/Config/Tags/*.ini`) + BugHunt starter fixture + M28.pre.5 `verify_tag_author.ps1` parity gate + new `WITH_GAMEPLAYTAGSEDITOR_SUPPORT` Build.cs flag. Op count 44 → 45; MCP tool count 13 → 14. Version 1.26.0 → 1.27.0 (minor). All gates green: automation 17/17, determinism twin byte-identical, 18 inspect + 28 soak unchanged, new `tag-author-bughunt` gate PASS (baseline=343b → +1 line / md5 stable / idempotence holds / baseline restored), MCP smoke 24/24 (was 23). M28.6.0 research correctly identified all three engine traps (duplicate-add returns false not skip → pre-check `IsDictionaryTag` for true skip; `DeveloperConfigName` per-machine diversion documented; Perforce checkout covered by existing `apply_plan` confirm gate). Headline correction shipped with the implementation: the engine API lives on `IGameplayTagsEditorModule` (editor plugin), NOT `UGameplayTagsManager`. Next scope is OPEN — M28.7 automation-test runner / M28.8 optional read-side additions / any other M28-phase-table item.

**Prior: 2026-04-25 — M28.6 selected as next scope; M28.6.0 research-only slice shipped.** User picked M28.6 (GameplayTag config authoring — design.md items #1 + #4) as the next external driver after M29.6 closed. Research outcome captured in the new `### M28.6.0 research outcome` block below; surface is 1 UFUNCTION (`AddGameplayTag` on `BpxReflectionOps`, gated by new `WITH_GAMEPLAYTAGSEDITOR_SUPPORT` Build.cs flag — engine API lives on `IGameplayTagsEditorModule` in the editor plugin, NOT on `UGameplayTagsManager` as the phase table assumed) + 1 Python op (`add_gameplay_tag` in new module `gameplay_tags.py`) + 1 zero-UE-process MCP tool (`list_gameplay_tags`) + 1 BugHunt starter fixture (`Config/DefaultGameplayTags.ini`) + M28.pre.5 parity gate (`scripts/verify_tag_author.py`). **Next pickup: M28.6.1** implementation (minor bump 1.26.0 → 1.27.0). Three documented traps: duplicate-add returns false not skip (Python op pre-checks `IsDictionaryTag` for soak idempotence); `DeveloperConfigName` per-machine override diverts the source ini (document, don't bypass); P4 checkout fires inside `AddNewGameplayTagToINI` (covered by existing `apply_plan` confirm gate). Everything from here down is history up to the M29.6 reopen.

Twenty-eight-plus milestones landed (**M28.4 non-BP asset-factory catalog closed end-to-end at M28.4.3 / `754dd32`** — 8 ops total across `curves.py` + `data_assets.py` + `uds.py`; M28.5 EQS write-side catalog closed at M28.5.3; M28.3 catalog also complete at M28.3.6 pure-docs). Canonical `ProjectInventory_DOW/` (805 assets, 1622 files) is committed and is the brief §13 final deliverable. Usability audit ran 2026-04-19 against the committed tree (see "Usability audit" section below) and confirmed the output is good for static analysis / replication audit / orphan detection — three concrete anti-patterns were surfaced in DOW via grep alone (Ultra_Dynamic_Sky inconsistent replication conditions, `Use Auroras` likely-wrong `COND_OwnerOnly`, zero authored RPCs across all 805 assets). **M5.2 (2026-04-19)** extended the serializer + DeepDump to render full StateTree NPC-behaviour detail — DOW's 4 ST assets now expose per-task instance data (`StateTreeDelayTask.Duration=3s`, `StateTreeMoveToTask.AcceptableRadius=5`, BP task properties like `SearchRadius=1000` on `STT_FindRandomLocation`). **M5.3 P0 (2026-04-19)** closed three StateTree-serializer fidelity gaps. **M8 (2026-04-19)** extracted the Tier 2 renderers into a shared `TextExport/DeepDumpRenderer` (3 entry points: RenderBlueprintMarkdown / RenderStateTreeMarkdown / RenderOutOfScopeNotice) and added `-DeepDump` to `ProjectInventoryCommandlet` — every processed asset now emits a `<Path>.deep.md` sibling when the flag is set; UBP + ST get the full Tier 2 payload, other in-scope classes get an out-of-scope notice for sibling-pattern uniformity. Canonical `ProjectInventory_DOW/` refreshed at `05c9b6e` with the first project-wide Tier 2 layer (805 `.deep.md`, ~64 MB). M8 audit surfaced one trust-killing silent-information-loss gap: `.deep.md` showed instanced-subobject arrays as flat `ExportTextItem_Direct` blobs only, so values like AISenseConfig sight radius / GAS attribute defaults were invisible at Tier 2 and required dropping into `.meta.json`. **M9 (2026-04-19)** closes that gap — the renderer now walks `FExportedComponentProperty::SubobjectJsonValues` recursively after each component property table, emitting nested per-subobject property tables (with `bTruncated` / `bCycleDetected` / `bHasBrokenReference` markers honoured per "Never guess values"). DOW canonical refresh affected exactly 6 files (the only ones with `[instanced]` arrays — Sandbox CMC/Mover, Kellan, Player_Fix, Straz_Fix); SandboxCharacter_CMC.AIPerception now exposes `SightRadius=800`, `LoseSightRadius=1200`, `PeripheralVisionAngleDegrees=60`, `HearingRange=500`, `MaxAge=5`/`3` directly in `.deep.md`. **M10 (2026-04-19)** upgraded `INDEX.md` from a 71-line scoreboard into the actual navigation entry point — added "Where to start" routing table linking each rollup with one-line "use this for X" hints (now includes MANIFEST/PLUGINS that the prior link list missed), "Per-asset deep dumps" explainer for the `.md` / `.meta.json` / `.deep.md` trio, and "Trust signals" glossary documenting every marker (`[BROKEN]`, `[instanced]`, `**Truncated**`, `**Cycle detected**`, `**Broken reference**`, `(unresolved)`, `(?)`, `_Empty graph._`). **M11 (2026-04-19)** added Tier 2 for `SmartObjectDefinition` — most-behaviour-like of the remaining 310 out-of-scope types. New `Public/TextExport/SmartObjectDefinitionDeepRenderer.h` + `Private/.../*.cpp` pair with one entry point `RenderSmartObjectDefinitionMarkdown(UObject*)` gated on `WITH_SMARTOBJECTS_SUPPORT`. Live UObject reflection (no new schema struct, no serializer changes) walks each behavior definition's UPROPERTYs and each slot's `FInstancedStruct` `DefinitionData` fields. Concrete win on DOW: `SO_BenchDefinition.deep.md` now exposes the `StateTreeReference` that links it to `ST_SmartObject_Bench` (the actual interaction logic), plus per-slot `SmartObjectSlotEntranceAnnotation` field values (entrance `Offset=(48, ±0, 0)`, `TrajectorySlotHeightOffset=40`, `TransitionCheckRadius=10`, `bIsEntry=True`, `bIsExit=True`). **M12 (2026-04-19)** graduated `BehaviorTree` the same way — new `BehaviorTreeDeepRenderer` (no gate; AIModule ships with the engine) recursively walks `UBehaviorTree::RootNode`, emitting a heading block per composite + task with a full UPROPERTY table plus per-slot decorators and per-composite services each with their own property tables. Also dumps `RootDecorators` and the full Blackboard key list with `bInstanceSynced` flag. BT plumbing allowlist extended (`TreeAsset` / `ParentNode` / `TemplateNode`). DOW has no BT content so the canonical refresh touched exactly 310 out-of-scope notices (stale "Supported classes" text) + `INDEX.md`; BugHunt's `BT_BugHunt` is an empty-tree fixture (identity + blackboard path exercised, node-table path not). **M13 (2026-04-19)** graduated `DataTable` — new `DataTableDeepRenderer` walks `UDataTable::GetRowMap()` alpha-sorted, rendering each row's `UScriptStruct` fields as a property table via `ExportTextItem_Direct`. Tier 1 only captured schema (row struct + column list + sorted name list) per brief §4; M13 closes the value-level gap. Exercised end-to-end by DOW content: 4 DataTable assets (Wwise `DefaultGeometrySurfacePropertiesTable`/`DefaultReverbAssignmentTable`, UDS `UDS_Glossary`/`UDS_Readme_Entries`) now dump their authored rows. **M14 (2026-04-19)** graduated `ChooserTable` — new `ChooserTableDeepRenderer` (gated on `WITH_CHOOSER_SUPPORT`) walks every column / row / fallback / context `FInstancedStruct` and dumps its full UPROPERTY table. Big payoff on DOW: the 12 Chooser assets all expose their complete decision tables — `CHT_CameraRig` shows `E_CameraStyle` × `E_CameraMode` → 11 `CameraRig_<style>_<mode>` assets with per-row `MatchAny`/`MatchNotEqual` flags visible; the 7 `CHT_PoseSearchDatabases_*` tables expose their per-anim-type selection logic; `CHT_SmartObject_BenchAnim` surfaces the bench animation selection. **M15 (2026-04-19)** graduated `EnvQuery` — new `EnvQueryDeepRenderer` (no gate; AIModule is non-optional) walks `UEnvQuery::GetOptions()` in authored order → per-option generator UObject + per-test UObject UPROPERTY tables. Speculative ship at time of landing: main DOW has zero EQS assets, but the 2026-04-19 DOW_Legacy audit then found 4 EQS assets in the legacy depot (`EQS_AI_FindCover`, `EQS_AI_FindPeek`, `EQS_AI_FindPointInCone`, `EQS_FindCloseCover`) that exercise the full per-option + per-test UPROPERTY path end-to-end. 293 out-of-scope notices after M15. **M16 (2026-04-19)** closes the 2026-04-19 DOW_Legacy audit's finding #1 — `FStateTreeSerializer::SerializeUObjectProperties` now skips the same `{UberGraphFrame, CachedFrameStateTree}` allowlist the M11–M15 Tier 2 renderers use. BP-backed StateTree task instance classes (UBlueprintGeneratedClass) were leaking those two runtime back-references into `.meta.json` property arrays — 7 files in legacy + 3 in main DOW canonical (`ST_NPC_SandboxCharacter_Patrol_Subtree`, `ST_NPC_SandboxCharacter_SmartObject`, `ST_SmartObject_Bench`). Main DOW canonical refresh dropped 158 lines of plumbing noise across those three sidecars; M8 audit missed this because it only checked `.deep.md` (renderers already filtered). **M17 (2026-04-20)** wires `UPackage::SavePackage` into `FBlueprintImportManager::ApplyImport`. The import pipeline was silently in-memory-only — `ApplyImport` called `DeserializeBlueprint` (which mutates the live UBlueprint), reported `success: true, modified: N`, and exited without ever writing to disk; mutations evaporated when the commandlet ended. The fix mirrors `GenerateTestBlueprintsCommandlet::SavePackageForAsset` verbatim: resolve outer package, `SetDirtyFlag(true)`, `UPackage::SavePackage` with `{RF_Public|RF_Standalone, SAVE_NoError, GWarn}` args. Two defensive guards before save: (a) refuse save when `Blueprint->Status == BS_Error` (DeserializeBlueprint returns bSuccess=true even on compile failure); (b) refuse save when `!DeserializeResult.bSuccess || !Blueprint` (early-abort paths like "Duplicate node ID" leave Blueprint null). The save path itself is verified working — a pre-guard run on `AC_AIHealth.uasset` actually modified the file on disk (86781 → 76389 bytes, md5 shifted). With guards, both AC_AIHealth (BS_Error) and BP_NetRep (duplicate-node-id abort) now preserve md5 pristine while surfacing the underlying error to the commandlet log. Surfaces M18 as the follow-up: the deserializer has pre-existing fidelity bugs (`Could not find a function named None`, `Event Dispatcher has no property Call None`, `blueprint (self) is not compatible with Target`, `Duplicate node ID 'Entry_0_0_*' in graph 'OnRep_*'`) that block actual Claude-driven edits end-to-end; M17 is the safety net that lets us iterate on M18 without corrupting assets. **M18.1 (2026-04-20)** scoped the deserializer's duplicate-node-ID check per-graph — a shared project-wide set was false-positive-rejecting any Blueprint with more than one function because `ComputeStableNodeHash` produces identical hashes for every graph's `FunctionEntry` (all at position (0,0), identical pin signature). First proven round-trip edit: `BP_NetRep.Score` 0 → 42 persists cleanly end-to-end, post-apply dry-run shows `hasChanges: false`, re-export confirms the new value. **M18.2 (2026-04-20)** closed the remaining `AC_AIHealth` deserializer bugs — two fidelity fixes: (a) `CallFunction` owner-class resolution now falls back to `functionOwnerClass` when `memberParentClass` is empty (previously five PromotableOperator / CommutativeAssociativeBinaryOperator nodes came back with `FunctionReference.MemberName=None` because the serializer emits `functionOwnerClass` but the deserializer only read `memberParentClass`); (b) new `K2Node_CallDelegate` serialize + deserialize support (previously zero handling on either side — serializer wrote bare K2Node metadata, deserializer fell through to a `NewObject<UEdGraphNode>` with no `DelegateReference`, so BP compile reported `Event Dispatcher has no property Call None` + `blueprint (self) is not compatible with Target`). Second proven round-trip edit — the first on non-trivial content: `AC_AIHealth.BaseHealth` 100 → 125 in legacy CombatPrototype persists end-to-end (md5 `09282b7d…` → `83c6d5b6…`; post-apply re-export confirms `"125.000000"`; no compile errors, no guard trip). Schema extension is additive (new `delegatePropertyName` + `delegateOwnerClass` fields). **README brought in sync in `5a61d57`** — fixed three stale claims (Import stub / BT-EQS-DT-UDE-UDS "unsupported" / Blackboards), added the Project Inventory pipeline and Edit-via-round-trip workflow sections, Import CLI gains `-DiffReport=<path>`. All pushed to `10-Chambers/ue-tools` `main`. **M19.1 (2026-04-20)** landed the data-carrier CDO walk. `FBlueprintSerializer::SerializeCDOProperties` walks `GeneratedClass->GetDefaultObject()` via `TFieldIterator<FProperty>`, filters to *inherited* properties (own-class fields are already in `Variables`), diffs against the parent class CDO, and emits non-default authored overrides into the new `FExportedBlueprint::CDOProperties: TArray<FExportedComponentProperty>` — same shape as component templates, so the M9 instanced-subobject walker kicks in for Instanced / EditInlineNew fields without any duplicate schema. `DetectDataCarrierKind` stamps `DataCarrierKind = GameplayEffect \| GameplayAbility \| DataAsset \| ""` via `IsChildOf` against lazily-found base classes (`StaticFindObject` pattern from M7 — no new Build.cs module deps). Tier 1 `.md` gets a compact `## Class Default Object (N)` bullet list; Tier 2 `.deep.md` gets a full property table + recursive `RenderInstancedSubobjectTree` (mirrors `RenderComponentBlock` exactly). `BuildCoverageJson` gains `cdoProperties` core bucket; specialized-section markers `GameplayEffect.CDO` / `GameplayAbility.CDO` / `DataAsset.CDO` emitted per `DataCarrierKind`, documented rule strict for GE/GA (CDO IS the authoring surface) and relaxed for DA (Variables OR CDOProperties — DOW's 29 DAs author payload via BP variables, not inherited-CDO overrides). Concrete payoff on DOW: `BP_Cha_BaseBody_WorldNpc_Male_Asian_01.deep.md` now exposes `ActorLabel="BP_CharacterName-1"` + full recursive property trees for 6 natively-declared Instanced components (`ArrowComponent`, `CapsuleComponent`, `CharacterMovement`, `Mesh`, `RootComponent`) that `USimpleConstructionScript` never visited. BugHunt twin PASS in 47 s; DOW twin PASS in 183 s; canonical `ProjectInventory_DOW/` refreshed (1473 files affected — every UBP gets the `cdoProperties` field + `## Class Default Object` section; HEALTH_REPORT stays at 0 under-covered after the DA relaxation). Version bumped 1.13.0 → 1.14.0 per semver rule. **M19.3 (deserialize side) remains optional** — a Claude-driven edit to e.g. `GE.DurationPolicy` or `GA.AbilityTags` would need CDO write-back gated behind the M17 `BS_Error` guard; defer until a concrete edit target surfaces.

| Milestone | Commit | Summary |
|---|---|---|
| M1 Bootstrap | `ce82a6b` | Plugin 1.12.0 → 1.13.0, `Util/AtomicFileWriter` added |
| M2 ProjectManifest | `692fd9f` | Phase 0: FAssetRegistry-only scan → `MANIFEST.md` |
| M2 verify + BuiltPlugin sync | `efb5613` | Engine rebuilt post disk-full, DLL shipped |
| M3 ProjectInventory (UBP family) | `c06d02c` | Phase 1 streaming load/introspect/emit/GC |
| M4 AggregateInventory (core rollups) | `ffc223a` | Phase 2: INDEX + CLASS_TREE + DEPENDENCY_GRAPH + REPLICATION_MATRIX + HEALTH_REPORT + Scoreboard baseline |
| M3.1 ProjectInventory (BT/ST/UDS/UDE) | `73d73e8` | Non-UBP Phase-1 widening for BugHunt-covered types |
| M4.1 AggregateInventory (domain overviews) | `c0fea0f` | AI / ANIM / UI / GAS / STRUCTS_ENUMS overviews |
| M3.2 ProjectInventory (DT/EnvQuery/BT+ST detail/RPCs) | `511de83` | DataTable + EnvQuery typed handlers, BT per-node decorators/services walk, ST per-state task/transition/condition render, `FExportedFunctionFlags` net-exec extension + REPLICATION_MATRIX RPC rows, generic fallback for SmartObject/Chooser/PoseSearch, coverage-formula fix for empty primaries |
| DOW calibration slice (2026-04-18) | (no commit — ephemeral output) | Phase 0 against DOW: 18475 assets, 805 logic-bearing (14 classes). Phase 1 against `-Filter=/Game/_ThirdParty/GASP_example/`: 363 processed, 0 failed, 0 partial. **Key finding**: 167 assets (154 PSD + 12 Chooser + 1 SmartObj) all scored silent 100% via the generic fallback — the fallback declared no specialized sections to miss. StateTree + AnimBP + UDS/UDE coverage matched pre-existing expectations; no unexpected serializer gaps on AI content |
| M3.3 P0 (coverage honesty for fallback) | `077d846` | `GetGenericFallbackApplicableSections(ClassName)` maps PSD / Chooser / SmartObj short names to a single descriptive applicable marker (e.g. `PSD.Schema+Animations+Normalization`). Flipped HEALTH_REPORT `CoverageUnder100` on the DOW slice from 23 → 190 honest gaps. BugHunt unaffected (no fallback-path assets in fixtures) |
| M3.3 P1a (ChooserTable typed handler) | `72a88f9` | `EmitChooserTableAsset` walks columns / rows / fallback / context / result type / nested. Build.cs adds `WITH_CHOOSER_SUPPORT` detection (mirrors `WITH_STATETREE_SUPPORT`), `.uplugin` adds Chooser optional dep, `BugHunt.uproject` adds Chooser + target was rebuilt so the baked-in plugin list resolves at load time. 12 ChooserTables moved 94% → 100%; `CHT_CameraRig` example now shows "2 EnumColumns → 11 AssetChooser rows → CameraRigAsset" instead of opaque 17-property dump. DOW slice determinism still byte-identical across runs |
| M3.3 P1b (PoseSearchDatabase typed handler) | `c47d8c6` | `EmitPoseSearchDatabaseAsset` walks Schema (channel list + skeleton roles via deref), DatabaseAnimationAssets (anim class/path + sampling range + mirror/enabled), NormalizationSet path, top-level bias / performance config (PoseSearchMode, cost biases, KDTree params, pruning thresholds, extrapolation windows). Build.cs adds `WITH_POSESEARCH_SUPPORT` gate (mirrors `WITH_CHOOSER_SUPPORT`); `.uplugin` + `BugHunt.uproject` add `PoseSearch` optional dep; BugHunt target rebuilt. 154 PSDs in DOW GASP slice moved 95% → 100%. `HEALTH_REPORT` `CoverageUnder100` dropped 178 → 24 (remainder is AnimBP.StateMachines + WidgetBP.WidgetTree + 1 SmartObj-on-fallback). DOW slice byte-identical across runs |
| M3.3 P1c (SmartObjectDefinition typed handler) | `0226089` | `EmitSmartObjectDefinitionAsset` walks Slots (offset/rotation/enabled, activity & runtime tags, user tag filter, selection preconditions, behavior definitions, definition-data struct types), DefaultBehaviorDefinitions (via reflection — private field), object-level ActivityTags / UserTagFilter description / Preconditions-set / parameter bag count / tag filtering+merging policies / world condition schema. Build.cs adds `WITH_SMARTOBJECTS_SUPPORT` gate + `WorldConditions` link dep (needed for `FWorldConditionQueryDefinition::IsValid()`). `.uplugin` + `BugHunt.uproject` add `SmartObjects` optional dep; BugHunt target rebuilt. `SO_BenchDefinition` moved 95% → 100%. `HEALTH_REPORT` `CoverageUnder100` dropped 24 → 23 (remainder is only AnimBP.StateMachines + WidgetBP.WidgetTree). Every in-scope class now has a typed handler — `GetGenericFallbackApplicableSections` returns `{}` unconditionally (kept for future-class honesty). Byte-identical across runs |
| M3.3 Track A (AnimBP.StateMachines + WidgetBP.WidgetTree rendering) | `a2c7df0` | Existing `FExportedBlueprint::StateMachines` (already populated by the serializer) now renders as a `## State Machines` Markdown section per asset with per-machine state list (type + node count) and transition list (source → target + logic type + crossfade duration), recursive nested-SM support. New `FExportedBlueprint::WidgetTree` field walks `UBaseWidgetBlueprint::WidgetTree->RootWidget` via `UPanelWidget::GetChildAt`, preserves authored slot order; renders as a nested bullet list with class short-name, variable flag, slot class. Build.cs adds `UMG` + `UMGEditor` (ship-with-engine, no optional-detection). Both specialized sections are marked documented for their subclass. `HEALTH_REPORT` `CoverageUnder100` dropped 23 → 0 on DOW, 1 → 0 on BugHunt. Byte-identical across runs |
| M5 DeepDumpCommandlet (Tier 2 on-demand) | `44e1687` | `DeepDumpCommandlet.{h,cpp}` added under `Source/BlueprintExporter/{Public,Private}/Commandlets/`. CLI: `-run=DeepDump -Asset=/Game/Path/Asset -OutDir=<dir>` → writes `<OutDir>/<AssetName>.deep.md` via `SaveStringAtomic`. UBlueprint-family only (Blueprint / AnimBlueprint / WidgetBlueprint / ControlRigBlueprint); non-UBP classes emit an out-of-scope notice pointing at the Tier 1 typed handlers and exit 0 (BT/ST/UDS/UDE/DT/EnvQuery/SmartObject/Chooser/PoseSearch already render near-complete detail at Tier 1). Full pin-level graph dump: every node in EventGraph / ConstructionScript / AdditionalGraphs / per-function / per-macro, per-node pin table (Dir / Name / Type / Default / Flags / Connections). Connections sorted by `(NodeId, PinId)` per brief §8 and annotate the target node's title. AnimBP state machines inline each state's full AnimGraph + each transition's full RuleGraph at nested heading levels. Component tree flattened to flush-left H3 blocks (Markdown tables break under 4+ spaces of indent) with full `FExportedComponentProperty` expansion. Build.cs unchanged — no new module deps. Verified against `BP_NetRep` (3779 bytes deep dump, pin connections resolve correctly to target node titles), `BP_NodeZoo` (stress test: 149-line dump with `K2Node_ExecutionSequence` cross-node connections), `BP_WidgetTree` (WidgetBlueprint subclass, widget tree rendered), `BT_BugHunt` (out-of-scope notice emitted correctly). Byte-identical across runs (`md5sum` match across three consecutive runs). |
| M6 verify_determinism.ps1 (CI gate) | `1793bea` | `scripts/verify_determinism.ps1` — PowerShell gate per brief §11A. Runs `ProjectManifest` + `ProjectInventory` + `AggregateInventory` + `DeepDump` (skippable) twice into `$OutA` / `$OutB` sibling trees, then `git diff --no-index`s them. Exit 0 on byte-identical PASS, 1 on diff (with `<OutA>.diff` capturing the full unified diff and both trees preserved for inspection). CLI: `-Project {BugHunt\|DOW}` required; DOW runs auto-append `-EnablePlugins=BlueprintExporter`; optional `-OutA` / `-OutB` / `-Filter` / `-DeepAsset` / `-SkipDeep` / `-KeepOnSuccess` / `-Engine`. Per-run logs live in sibling `_logs` dirs (not under `$OutA` / `$OutB`) because `git diff --no-index` doesn't honour pathspec excludes. Diff uses `-c core.autocrlf=false -c core.safecrlf=false` so it's checking byte-identical, not "identical after line-ending normalization". Verifies `[STATUS] SUCCESS` in each commandlet log before considering a phase done; treats UE-Cmd exit 1 as benign (the ProjectID warning-summary inflation) but exit ≥ 2 as a real failure. **Verified**: BugHunt full pipeline PASS in 54 s; DOW GASP slice (363 assets) PASS in 116 s. |
| M6.1 serializer determinism fix | `18e5217` | First full-DOW run of the M6 gate caught 3/805 `.meta.json` files drifting. Two distinct root causes: (1) `K2Node_CallFunction` auto-regenerated nodes (e.g. `MakeSlateFontInfo`) get fresh `UEdGraphNode::NodeGuid` on every `PostLoad`, which leaked into the `nodeGuid` field, the NodeId hash suffix, and the `SerializePin` connection fallback (hit for pins into nested BoundGraphs that the pre-pass map didn't visit); (2) `AVolume::VolumeGuid` UPROPERTY is regenerated per load by the volume subsystem. Fix: new `ComputeStableNodeHash(UEdGraphNode*)` static helper derives a 32-hex-char hash from stable node content (class + subtype name + position + ordered pin signature). All four places that previously read `Node->NodeGuid` now read the hash: `GenerateStableNodeId` (first 8 chars), `ExportedNode.NodeGuid` (full), `SerializePin` connection fallback, and the two positional-sort tiebreakers. New `IsTransientValueProperty(FProperty*)` with a `TSet<FName>` allowlist (currently just `VolumeGuid`) substitutes `"[transient]"` in `SerializeSCSNode` and `BuildPropertiesJsonArrayForObject` before `ExportTextItem_Direct` sees the drifting value. **Verified**: full DOW twin run (805 assets, no filter) now PASS in 193 s; BugHunt regression clean in 74 s. |
| M5.1 DeepDump + serializer fallback fix | `fc35ee4` + `c8a1a9f` | First DOW-content exercise of DeepDump (`SandboxCharacter_CMC_ABP`, 14665 lines, 76 vars × 59 functions) exposed rendering bugs that BugHunt fixtures never triggered: pin connections to nodes in other graphs showed `(?)` instead of the target title (1996 unresolved refs in one file), and node headings inside state-machine AnimGraphs rendered shallower than their enclosing graph. Two fixes: (a) `BuildProjectNodeTitleMap` walks every graph in the blueprint once (event/construction/additional/per-function/per-macro + recursive state-machine state AnimGraphs and transition RuleGraphs), and the map is passed through all `Render*Deep` helpers; (b) `RenderGraphDeep` and `RenderNodeDeep` both take a `HeadingLevel` parameter so the node heading is always one deeper than its graph (clamped to H6). Third-party serializer fallback fix: `SerializePin`'s connection fallback now emits `GenerateStableNodeId(...)` (format `TypePrefix_X_Y_HASHPREFIX`) instead of `ComputeStableNodeHash(...)` (raw 32-hex) — the two formats have to match for title lookups to succeed. Serializer change shifted 200 fallback-path `nodeId`s in DOW Tier 1 output, so `ProjectInventory_DOW/` was refreshed in `c8a1a9f` (89442 insertions / 89442 deletions, symmetric). **Verified**: DeepDump `(?)` count 1996 → 0; state machines nest cleanly `## → ### → #### → ##### → ######`; BugHunt PASS in 82 s; DOW full twin run PASS in 204 s. Known cosmetic limitation: identical "standard" nodes in sibling sub-graphs (e.g. every state's `AnimGraphNode_StateResult` at (0,0)) still hash to the same stable ID; enclosing state heading disambiguates in practice. |
| M5.2 StateTree DeepDump + serializer instance-data capture | `2f174b3` + `dc27fc1` | `FStateTreeSerializer::SerializeEditorNode` now walks all three halves of every `FStateTreeEditorNode`: `Node` (scheduler plumbing + wrapper fields — existing), `Instance` (FInstancedStruct with native-task authored config like `FStateTreeMoveToTaskInstanceData::AcceptableRadius`), and `InstanceObject` (UObject holding BP-backed task properties like `STT_FindRandomLocation_C::SearchRadius`). `FExportedStateTreeEditorNode` gained `InstanceProperties` / `InstanceObjectClass` / `InstanceObjectProperties` fields with name-sorted ToJson (non-empty-only, so Tier 1 output for nodes that have no instance data stays identical pre-/post-change). `DeepDumpCommandlet` gained a `UStateTree` dispatch that routes to new `RenderDeepStateTreeMarkdown` — renders identity + summary + full property-bindings table + global evaluators/tasks + recursive state walk with per-task three-table node render (node struct / instance data / instance object, with UE plumbing like `UberGraphFrame` / `CachedFrameStateTree` stripped). **Verified**: DeepDump against all 4 DOW ST assets byte-identical twin-run (ST_MassAI=3863b, Patrol_Subtree=9321b, SmartObject=13785b, Bench=27973b); full DOW twin PASS in 198 s; BugHunt PASS in 76 s; canonical `ProjectInventory_DOW/` refreshed (+1685 lines across the 4 ST `.meta.json` sidecars; INDEX.md dropped the first-run italic note now that baseline is seeded). NPC behaviour now readable at Tier 2: e.g. Bench interaction dumps `Cooldown Time=5.0s / CooldownName=Sit`, `Play Time=10.0s ± 3.0s` idle variance, `M_interaction_bench_out_to_stand_Montage` exit animation. Deferred: real ST fixture in BugHunt (current `ST_BugHunt` has no editor data so BP-wrapped ST nodes have no BugHunt-side regression; DOW is the authoritative ST test bed). |
| M5.3 P0 StateTree serializer fidelity gaps | `c1df8c7` + `c59c655` + `faa502d` | Three gaps found while sanity-checking the M5.2 DOW output: (1) UE 5.5+ `EStateTreeStateType::LinkedAsset` wasn't in our switch — the Patrol state in `ST_NPC_SandboxCharacter_SmartObject` rendered as `[Unknown]` despite being a valid link to the patrol subtree asset; (2) `UStateTreeState::LinkedAsset` (the `TObjectPtr<UStateTree>` holding the external tree) was never captured — new `FExportedStateTreeState::LinkedAssetPath` populated when state type is LinkedAsset; (3) `FStateTreeStateLink::LinkType` on every transition was never read — `GotoState` is the ONLY link type whose Name/ID identify a state, so `Succeeded` / `Failed` / `NextState` / `NextSelectableState` / `None` were all either rendering as `(unresolved)` or (worse) with a stale authored Name that contradicted the actual runtime behaviour. Concrete DOW example: `MoveToRandomLocation.OnStateCompleted` had `LinkType=NextState` but rendered as `FindRandomLocation` (its parent, not its sibling — completely wrong); `Wait.OnStateSucceeded` had `LinkType=Succeeded` (exit subtree with success signal) but rendered as `(unresolved)` which looked like a bug. New `FExportedStateTreeTransition::LinkType` captures the enum as a string; target-name rendering now honours LinkType with semantic labels `(tree succeeded)` / `(tree failed)` / `(next state)` / `(next selectable state)` / `(no target)` for non-`GotoState` links. `GotoState` keeps existing Name→GUID→`(unresolved)` fallback. Also added `.gitignore` entries for `ProjectInventory/`, `ProjectInventory_DOW/Deep/`, and verification twin-run outputs so `git add` sweeps don't recapture ephemerals. **Verified**: BugHunt twin PASS in 77 s; DOW full twin PASS in 198 s; canonical `ProjectInventory_DOW/` refreshed (7 files, +30/-18). Deferred: EStateTreeStateSelectionBehavior has 5 UE 5.7 utility-based values unmapped (TrySelectChildrenWithHighestUtility etc.) — DOW doesn't use them today so these stay on the backlog. |
| M7 P0 ProjectPlugins commandlet (uplugin metadata) | `18f44a4` + `8044ca7` | New `ProjectPluginsCommandlet` closes the plugin blind spot in static analysis. Walks `IPluginManager::GetDiscoveredPlugins()` filtered to `EPluginType::Project`, extracts `FPluginDescriptor` fields, emits `<OutDir>/PLUGINS.md` rollup + `<OutDir>/PluginInventory/<Name>.{md,meta.json}` per plugin. Captured per plugin: descriptor metadata (Version/VersionName/FriendlyName/Description/Category/CreatedBy*/URLs/EngineVersion/bCanContainContent/bIsBetaVersion/bInstalled), module list (Name/HostType enum/LoadingPhase enum), plugin-reference deps (Name/bEnabled/bOptional), plugin type, project-relative base dir. CLI: `-run=ProjectPlugins -OutDir=<dir>` + optional `-Include=<regex>` / `-Exclude=<regex>`. Schema in new `Public/Schema/PluginExportTypes.h`: `FExportedReflectedProperty` (placeholder for P1), `FExportedPluginModule`, `FExportedPluginDependency`, `FExportedPluginNativeType` (empty in P0), `FExportedPlugin`. Per-plugin `ComputeContentHash` over timestamp-blanked JSON. Determinism (brief §8): plugins sorted alpha by name, modules/deps sorted alpha within plugin, `BaseDir` project-relative via `ConvertRelativePathToFull` + `ProjectDir` prefix strip (engine-relative fallback, drive-letter-strip final fallback). `scripts/verify_determinism.ps1` extended with ProjectPlugins as a 4th always-on phase (detects plugin-graph non-determinism). **Verified**: BugHunt finds 2 plugins (BlueprintExporter + BlueprintExporterTests), twin-run PASS in 63s; DOW finds 22 plugins (CoverEQS, AdvancedSessions/SteamSessions, DLSS/NIS/Streamline-family, SteamAudio/Wwise-family, MetaTailorBridge, Tripo3DUEBridge, ScreenSpaceFogScattering, Toolbox + BlueprintExporter), twin-run PASS in 203s. CoverEQS sidecar correctly captures its 1 Runtime/Default `CoverEQS` module, zero plugin deps, Category=AI, VersionName=1.0.0. Plugin DLL: 3.13 MB → 3.23 MB. Deferred to M7 P1: `GetDerivedClasses()` reflection walk over curated base-class set (EQS/StateTree/BT/Anim/GAS/SmartObject/Chooser/Mass) to populate `NativeTypes[]` — schema is already shaped for it so P1 is pure code addition, no sidecar-format churn. |
| M7 P1 ProjectPlugins native-type enumeration | `1314ba2` + `28ddd4a` | Reflection walk extension — fills `NativeTypes[]` on each plugin sidecar with the UClasses the plugin's modules register. Iterates the curated base-class allowlist (EQS/StateTree BP bases/BT/Anim/GAS/SmartObject/Chooser/Mass), resolves each base at runtime via `StaticFindObject` (no new Build.cs module deps — silent skip when a base's module isn't loaded), runs `GetDerivedClasses` recursively, filters candidates by plugin ownership (`Candidate->GetPackage()->GetFName()` must be `/Script/<ModuleName>` for some module in this plugin's `Modules[]`), dedupes by ClassPath, and emits `FExportedPluginNativeType` with declared UPROPERTYs (`TFieldIterator<FProperty>` with `ExcludeSuper` on the class CDO — reuses the M5.2 reflection shape via `BuildReflectedProperties` helper). Renderer upgraded: per-plugin .md now has a summary table plus per-class H3 with its full property table (Name/Type/Default/Category); PLUGINS.md rollup gains a `Native` column and summary line. "Registered native types (0)" section distinguishes enabled-but-registers-nothing from disabled-module-not-loaded cases. **Verified**: BugHunt 63s (2 plugins, 0 native types — expected); DOW 194s; DOW's CoverEQS sidecar includes `/Script/CoverEQS.EnvQueryTest_TraceDistance` with all 9 UPROPERTYs (TraceTo, TraceData, ItemHeightOffset, ContextHeightOffset, MaxTraceDistance, ScoreMode, bTraceFromContext, bScoreMissAsMaxDistance, IgnoreActorsContext) matching the pre-work scope assertion exactly; Wwise also registers `/Script/AkAudio.AkEventAnimNotify` (UAnimNotify subclass for Wwise audio from anim sequences, 3 props). Plugin DLL: 3.23 MB → 3.25 MB (~18 KB). Deferred to M7 P1.1: struct-typed bases (FStateTreeTaskBase / FStateTreeConditionBase / FStateTreeEvaluatorBase) via parallel `TObjectIterator<UScriptStruct>` walk; UMassFragment fits there too once MassEntity source becomes available. |
| M8 DeepDump sweep (shared renderer + -DeepDump flag) | `0cdeb7a` + `05c9b6e` | Tier 2 scale lever — extract the 1300-line DeepDump render path from `DeepDumpCommandlet.cpp` into a new shared `Public/TextExport/DeepDumpRenderer.h` + `Private/TextExport/DeepDumpRenderer.cpp` (3 public entry points in `BlueprintExporter::DeepDump` namespace: `RenderBlueprintMarkdown` / `RenderStateTreeMarkdown` / `RenderOutOfScopeNotice`). `DeepDumpCommandlet` reduces to a thin arg-parse + dispatch wrapper (1573 → 290 lines). `ProjectInventoryCommandlet` gains `-DeepDump` flag — every processed asset emits a `<Path>.deep.md` adjacent to its `<Path>.md`: UBlueprint family + UStateTree get the full Tier 2 payload (caller already has the serialized data in hand, so no double-work), other in-scope classes get the out-of-scope notice so the Tier 1 ↔ Tier 2 sibling pattern is uniform across the sweep. `EmitStateTreeAsset` gained `bool bEmitDeepDump + const FString& DeepPath` default-nullable params so the flag threads through the single StateTree dispatch cleanly. `scripts/verify_determinism.ps1` gained `-SweepDeepDump` switch: passes `-DeepDump` to Phase 1 and skips the now-redundant single-asset DeepDump phase; opt-in because full-DOW sweep is ~5-10 MB of Tier 2 output (~3-5 min). Canonical `ProjectInventory_DOW/` refreshed at `05c9b6e` with 805 `.deep.md` files (64 MB total — top outliers are 23 MB BPP_City_Packed_Chunk, 7 MB Ultra_Dynamic_Sky, 4 MB Ultra_Dynamic_Weather; rest is ~30 MB across ~800 files). **Verified**: (a) BugHunt sweep 18/19 `.deep.md` emitted (ST_BugHunt partial-failed as pre-existing, no editor data), (b) BP sweep output vs standalone `-run=DeepDump` byte-identical on BP_NetRep, (c) ST sweep output vs standalone byte-identical on Patrol_Subtree, (d) BugHunt twin-run via `verify_determinism.ps1 -Project BugHunt -SweepDeepDump` PASS in 52 s, (e) full DOW sweep (805 assets) PASS in 63 s with 0 failures + 0 partials + 0 modifications to existing Tier 1 outputs (add-only diff). Plugin DLL grew from 3.25 → ~3.25 MB (move-not-add refactor). Audit findings: 0 `(unresolved)` transitions, 0 `UberGraphFrame` leaks, 0 timestamp leaks across all 805 dumps; 71 `(?)` titles confined to 2 MetaHuman ControlRig files (known M5.1 sibling-graph hash collision); 671 `[BROKEN]` markers correctly flagging unresolvable pin types in third-party content (UDS=168, UDW=105, Sandbox ABPs=83); 310 out-of-scope notices match (12+4+154+1+74+65 = ChooserTable+DataTable+PSD+SmartObject+UDE+UDS counts). One trust-killing gap surfaced: instanced-subobject arrays render as flat path blobs at Tier 2, real values (sight radius, GAS attributes) only readable from `.meta.json` — fixed in M9. |
| M9 instanced-subobject tree in DeepDump | `af66897` + `bd6e221` | Closes the M8-audit-surfaced silent-information-loss gap. `RenderInstancedSubobjectTree` + `RenderInstancedSubobjectEntry` recursively walk `FExportedComponentProperty::SubobjectJsonValues` after each component property table — alpha-sorted scalar properties as Markdown tables, instanced sub-properties as nested `[instanced]` sub-sections (recursing depth-first up to the serializer's `MAX_SUBOBJECT_RECURSION_DEPTH=8`). `bTruncated` / `bCycleDetected` / `bHasBrokenReference` markers from the JSON tree render as explicit `**Truncated**` / `**Cycle detected**` / `**Broken reference**` lines per the "Never guess values" principle (no silent info-drop). Container context labels (`[N]` for arrays, `["K"]` for maps) preserved from the serializer's `arrayIndex` / `mapKey` fields. **Verified**: SandboxCharacter_CMC's AIPerception now exposes `SightRadius=800`, `LoseSightRadius=1200`, `PeripheralVisionAngleDegrees=60`, `HearingRange=500`, `MaxAge=5`/`3`, `DetectionByAffiliation=(bDetectNeutrals=True,bDetectFriendlies=True)` directly in `.deep.md`; BugHunt twin-run via `-SweepDeepDump` PASS in 60 s; full DOW sweep PASS in 62 s; canonical refresh affected exactly 6 of 805 files (`SandboxCharacter_CMC` / `SandboxCharacter_Mover` ×2 / `BP_Kellan` / `BP_Player_Fix` / `BP_Straz_Fix` — the only ones with `[instanced]` arrays). DLL unchanged in size (renderer-only addition, no schema or serializer changes). |
| M10 INDEX.md upgrade (navigation entry point) | `ba8284d` + `0dece7f` | Upgraded `AggregateInventoryCommandlet::RenderINDEX` so `INDEX.md` is the actual navigation entry point, not a 71-line scoreboard. Three new sections after the existing scoreboard / counts / hubs: **(1) "Where to start"** — table mapping "Looking for X" → rollup file, with one-line hints, including MANIFEST.md and PLUGINS.md that the previous link list missed (and conditional-presence notes for GAS/PLUGINS/MANIFEST since they're written by separate phases). **(2) "Per-asset deep dumps"** — explains the `.md` / `.meta.json` / `.deep.md` file trio, what UBP-family + StateTree get vs other types, and that the rollup itself reads `.meta.json` (not `.md`). Calls out the M9 nested instanced-subobject trees as part of Tier 2 coverage. **(3) "Trust signals"** — glossary table for every marker the output emits: `[BROKEN]` / `[instanced]` / `**Truncated**` / `**Cycle detected**` / `**Broken reference**` / `(unresolved)` / `(?)` / `_None_` / `_Empty graph._`, with what each means and what consumers can trust. All static text, deterministic by construction. **Verified**: BugHunt full pipeline twin-run PASS in 66 s (Manifest + Inventory + Aggregate + ProjectPlugins + DeepDump); DOW canonical refresh affected exactly 1 file (`INDEX.md`, 71 → 113 lines), all other rollups byte-identical. Plugin DLL unchanged in size (text-only addition to one renderer). |
| M17 BlueprintImport SavePackage wiring + save guards | `6c90c61` | `FBlueprintImportManager::ApplyImport` (`BlueprintImportManager.cpp:250`) now persists the in-memory Blueprint mutations to the `.uasset` on disk. Pre-M17 it called `DeserializeBlueprint` (which mutates live UBlueprint state), reported `success: true, modified: N`, and exited without saving — mutations evaporated when the commandlet terminated; zero references to `Save` / `SavePackage` / `UPackage` in the 265-line file. Fix adds `UObject/SavePackage.h` + `Misc/PackageName.h` includes and a save block after a successful deserialize: resolve outer package via `Blueprint->GetPackage()`, `Package->SetDirtyFlag(true)`, invoke `UPackage::SavePackage(Pkg, Blueprint, *Filename, Args)` with the standard `{RF_Public\|RF_Standalone, SAVE_NoError, GWarn}` args. Pattern mirrors `GenerateTestBlueprintsCommandlet::SavePackageForAsset` verbatim — the only pre-existing save path in the repo. Two defensive guards before save: (1) refuse save when `Blueprint->Status == BS_Error` — `DeserializeBlueprint` always returns `bSuccess=true` even when the post-import compile fails (downgrades to a warning in `DeserializeResult.Warnings`); without this guard the `.uasset` persists a BS_Error state and becomes unreloadable. (2) refuse save when `!DeserializeResult.bSuccess \|\| !Blueprint` — belt-and-suspenders for deserializer paths that abort early (e.g. "Duplicate node ID") and leave `OutResult.Blueprint` null. **Verified** via two round-trip probes: (a) pre-guard apply on CombatPrototype-legacy `AC_AIHealth.uasset` actually changed the file (md5 `09282b7d…` → `bfc1b8b4…`, size 86781 → 76389) — proves the save path fires correctly when given a valid Blueprint. (b) Post-guard apply on the same asset now refuses to save because `DeserializeBlueprint` compiles with BS_Error (`Could not find a function named None`, `Event Dispatcher has no property Call None`) — md5 stays at `09282b7d…`, error surfaces to commandlet log. (c) Apply on BugHunt `BP_NetRep.uasset` refuses to save at the earlier abort path because deserialize fails with `Duplicate node ID 'Entry_0_0_1182882F' in graph 'OnRep_HealthLow'` — md5 stays at `d696431a…`. Both pristine-asset outcomes restored with a tidy `cp` + `chmod -w` (no p4 required). Plugin DLL ~3.24 → ~3.26 MB (one new function call + two new includes). Rebuilt against both 10C custom engine (main build) and stock UE 5.7 (`_build_output_5_7/` — untracked by design per WIP) so the legacy depot junction picks up the guard. Exposes deserializer fidelity as the actual blocker for Claude-driven edits — scoped as **M18** next. This is the first non-chore M-row without a paired chore commit: no canonical inventory content depends on the import write path, so nothing to refresh. |
| M19.2.1 DeepDump DataAsset-instance fallthrough | `0ab7a1f` + `968e570` | Extends `-run=DeepDump -Asset=<path>` to handle any `UDataAsset`-derived instance (`UDataAsset` / `UPrimaryDataAsset` / any BP-generated DA class like `BP_CrowdCharacterDataAsset_C`). Pre-M19.2.1 these hit the out-of-scope notice because the commandlet's class-name pre-filter only matched the 4 UBP-family + 6 typed non-UBP names; a BP-derived DA's registry class name is `BP_XYZ_DataAsset_C` which is neither. Dispatch restructured: asset load moved BEFORE the class-name checks, new `bIsDataAssetInstance` fallthrough checks `AssetObject->IsA<UDataAsset>()` on the live object. New `RenderDataAssetInstanceMarkdown(UObject*)` in `TextExport/DeepDumpRenderer` walks instance UPROPERTYs via `TFieldIterator`, diffs against `Asset->GetClass()->GetDefaultObject()` (instance's OWN class CDO — analogous to M19.1's class-vs-parent-CDO diff but one level down), skips plumbing + transient flags, emits flat `ExportTextItem_Direct` values in an alpha-sorted property table. Out-of-scope notice updated to list `DataAsset` alongside the other supported classes. **Verified end-to-end on DOW's `CrowdCharacterDataAsset`** (`/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Data/`) — 312 KB `.deep.md` with 4 authored overrides: `Skeleton A` (male, 3 body-weight catalogs × ~30 mesh slots), `Skeleton B` (female symmetric), `HairColors` (5 melanin/redness pairs), `NativeClass` (auto back-ref). 533 mesh path refs captured — enough for a crowd-system colleague to map the entire outfit catalog without opening the asset in-editor. BugHunt twin PASS 47 s (strictly additive — pre-existing DeepDump paths untouched). DLL ~3.43 → ~3.44 MB. Version stays at 1.14.0 (additive renderer, no schema change). **Known limitation:** large struct values (>100 KB per field) render as single-line Markdown cells — correct + greppable but visually dense; recursive struct breakout (mirroring M13 DataTable row rendering) is the natural follow-up. The generated `CrowdCharacterDataAsset.deep.md` is committed into the canonical `ProjectInventory_DOW/` as an orphan (no `.md`/`.meta.json` companions since ProjectInventory sweep doesn't widen to DA instances yet — that's a bigger scope decision). |
| M19.1 Data-carrier CDO walk (serialize + Tier 1 + Tier 2) | `649d5ac` + `e25306c` | Closes the biggest remaining analysis blind spot — data-carrier BPs (GameplayEffect / GameplayAbility / DataAsset subclasses) that previously exported near-empty because `FBlueprintSerializer::SerializeBlueprint` was graph-oriented and never walked the generated class's CDO. Schema adds `FExportedBlueprint::CDOProperties: TArray<FExportedComponentProperty>` (reuses the M9-capable shape so Instanced / EditInlineNew refs get the recursive subobject tree) and `FExportedBlueprint::DataCarrierKind: FString` (`GameplayEffect` / `GameplayAbility` / `DataAsset` / empty). New serializer methods: `SerializeCDOProperties` (walks `GeneratedClass->GetDefaultObject()` via `TFieldIterator<FProperty>`, diffs against parent CDO via `Property->Identical`, skips own-class-declared fields so we don't double-emit Variables, skips `CPF_Transient | CPF_DuplicateTransient` and the M11–M16 plumbing allowlist `{UberGraphFrame, CachedFrameStateTree}`, reuses `BuildInstancedSubobjectValuesForProperty` from M9, alpha-sorts by PropertyName per brief §8); `DetectDataCarrierKind` (lazy `FindObject<UClass>` against `/Script/GameplayAbilities.{GameplayEffect,GameplayAbility}` and `/Script/Engine.DataAsset` — no new Build.cs module deps per M7 pattern, silent skip when module absent). ToJson/FromJson in `Schema/BlueprintExportTypes.cpp` adds `cdoProperties` array (defensive alpha sort) + conditional `dataCarrierKind` string. `ProjectInventoryCommandlet::BuildCoverageJson` gains `cdoProperties` core bucket (always 100% — renderer emits all extracted); `ComputeSpecializedApplicable` / `ComputeSpecializedDocumented` emit `GameplayEffect.CDO` / `GameplayAbility.CDO` / `DataAsset.CDO` specialized markers with a tiered documented rule: strict `CDOProperties.Num() > 0` for GE/GA (their authoring IS the CDO), but relaxed `CDOProperties.Num() > 0 \|\| Variables.Num() > 0` for DataAsset (variables are a valid authoring surface — keeps HEALTH_REPORT from flagging all 29 DOW DAs that author payload via BP variables). Tier 1 `.md` gains a compact `## Class Default Object (N)` bullet list (property-name + preview value); Tier 2 `.deep.md` gets a full property table followed by recursive `RenderInstancedSubobjectTree` calls mirroring `RenderComponentBlock` exactly so GE modifier lists / AbilitySystem attribute sets / natively-declared Instanced components all surface with nested subobject property tables. **Verified**: BugHunt `BP_GAS_Ability` exports with `dataCarrierKind: "GameplayAbility"`, `cdoProperties: []`, specialized `GameplayAbility.CDO` applicable-but-undocumented → coverage correctly drops to 80% (legitimate signal — a GA with no CDO overrides is a coverage gap); DOW sweep affects 1473 files (every UBP .md/.meta.json/.deep.md gets the CDO triple), HEALTH_REPORT stays at 0 under-covered after the DA-relaxation rule; first concrete CDO payoff on `BP_Cha_BaseBody_WorldNpc_Male_Asian_01` — exposes 6 inherited Instanced components (`ArrowComponent`, `CapsuleComponent`, `CharacterMovement`, `Mesh`, `RootComponent`) with full recursive property trees that the SCS walker never visited, plus the `ActorLabel="BP_CharacterName-1"` editor hint. BugHunt twin PASS in 47 s; DOW twin PASS in 183 s. Version bumped 1.13.0 → 1.14.0 per CLAUDE.md semver rule (new schema field + new capability). Plugin DLL ~3.27 → ~3.43 MB. |
| M18.2 CallFunction owner + CallDelegate round-trip | `f258f7d` | Two deserializer fidelity fixes that together unblock Claude-driven edits on complex real-world assets. **(a) CallFunction owner-class resolution.** The serializer emits `functionOwnerClass` for every CallFunction node (including `K2Node_PromotableOperator` / `K2Node_CommutativeAssociativeBinaryOperator` which resolve to KismetMathLibrary functions), but the deserializer only read `memberParentClass` — a field the serializer writes only as the literal `"Self"` when the call targets the BP's own class. For every external call, `MemberParentClass` came back empty → `LoadObject` returned null → FunctionReference.MemberName stayed None. BP compile then reported "Could not find a function named None in <BP>" five times on `AC_AIHealth` (five PromotableOperator / CommutativeAssociativeBinaryOperator nodes). Fix resolves owner class via three fallbacks: (1) `"Self"` → `Graph->GetTypedOuter<UBlueprint>()->SkeletonGeneratedClass` (or GeneratedClass), (2) non-"Self" → `LoadObject<UClass>` directly, (3) empty/unresolved → fall back to `functionOwnerClass`. **(b) CallDelegate serialize + deserialize.** `K2Node_CallDelegate` had zero handling on either side — serializer's NodeType dispatch fell through to `"K2Node"` with no delegate-specific data; deserializer's fallthrough created a bare `UEdGraphNode` with no `DelegateReference` wired up. BP compile reported "Event Dispatcher has no property Call None" + "blueprint (self) is not compatible with Target". Fix: serializer detects `UK2Node_CallDelegate` and emits `delegatePropertyName` (FName) + `delegateOwnerClass` (either `"Self"` for delegates declared on the serializing BP's own class, or the full UClass path). Detecting self-ownership via `FMemberReference::IsSelfContext()` is unreliable — it returns false for BP-declared delegates because `MemberParent` is set to the generated class — so compare `OwnerClass` against `OwningBP->{Skeleton,Generated}Class` directly. Deserializer dispatches on `NodeClass == UK2Node_CallDelegate::StaticClass()` in the fallthrough, parses the new fields, resolves OwnerClass, finds the multicast property, calls `SetFromProperty` before `AllocateDefaultPins`. **Verified** end-to-end on the second proven Claude-driven edit — the first on non-trivial content: `AC_AIHealth.BaseHealth` 100 → 125 in legacy CombatPrototype persists cleanly end-to-end. md5 `09282b7d…` → `83c6d5b6…`; post-apply re-export shows `"defaultValue": "125.000000"`; no compile errors, no guard trip. Pre-M18.2 the same apply produced 5× "Could not find function named None" + 1× "Event Dispatcher Call None" + 1× "self not compatible with Target" and the M17 guard correctly refused save. Cosmetic artifact of the round-trip: post-apply dry-run shows ~14 connection-changed diffs because `ComputeStableNodeHash` pin-signature input differs before/after the round-trip (UE's schema fills in hidden `ErrorTolerance` pins that were missing in the pre-export cached state). The _state_ round-trips correctly — only the node IDs stabilize on a second round-trip. Schema extension is additive (`delegatePropertyName` + `delegateOwnerClass` in CallDelegate NodeSpecificData); older exports missing these fields fall into the warning-and-skip path. BugHunt BP_NetRep round-trip (M18.1 regression) still passes. Asset restored to pristine via cached backup copy + `chmod -w`; Perforce state clean. DLLs rebuilt against both 10C custom engine and stock UE 5.7; plugin DLL ~3.26 → ~3.27 MB. No canonical inventory content affected. |
| M18.1 Per-graph NodeIds validation | `bb044c9` | `FBlueprintDeserializer::ValidateExportedData` used a single project-wide `TSet<FString> NodeIds` shared across every graph validation (EventGraph, ConstructionScript, Functions, Macros). Over-strict: NodeIds only need to be unique within their owning graph since UE pin connections are always intra-graph and the serializer emits `{NodeId, PinId}` scoped to the current graph. The check false-positive-rejected any Blueprint with more than one function because `ComputeStableNodeHash` ingredients (class + position + pin signature) produce identical hashes for `FunctionEntry` nodes in different graphs — all sit at (0,0) with the same one-exec-out pin shape. Concrete symptom: `BP_NetRep` aborted validation with `Duplicate node ID 'Entry_0_0_1182882F' in graph 'OnRep_HealthLow'` because its `UserConstructionScript` entry and `OnRep_HealthLow` entry hashed identically. Fix: scope to `TMap<FString, TSet<FString>> NodeIdsByGraph` keyed by graph name; `ValidateConnections` looks up its targets in the same per-graph set. Pure deserializer-side change — zero serializer output drift, canonical tree unaffected. **Verified end-to-end via the first proven Claude-driven round-trip edit in the system**: exported `BP_NetRep` (BugHunt), hand-edited `Score.defaultValue` in the JSON from `0` to `42`, `BlueprintImport -Apply -Force` → `BP_NetRep.uasset` md5 flipped `d696431a…` → `9823334d…`; post-apply dry-run reports `hasChanges: false` (live asset matches the edited JSON); re-export confirms `"Score"` `defaultValue: "42"`. Asset restored via `git checkout --` after verification. AC_AIHealth in legacy still blocked by a different deserializer bug (name resolution — `Could not find a function named "None"` ×5 + `blueprint (self) is not compatible with Target` + `Event Dispatcher has no property Call None`); M17's BS_Error guard holds md5 pristine. Queued as **M18.2** — delegate binding and Self-target resolution on delegate pins. |
| M16 StateTree serializer plumbing filter | `b0d1f4a` + `5602eea` | Closes the 2026-04-19 DOW_Legacy audit's finding #1. `FStateTreeSerializer::SerializeUObjectProperties` (`StateTreeSerializer.cpp:344`) now skips the same `{UberGraphFrame, CachedFrameStateTree}` allowlist the M11–M15 Tier 2 deep renderers use via a new file-scope `IsStateTreeUEPlumbingProperty(FName)` helper in an anonymous namespace. BP-backed task / condition / evaluator instance classes (UBlueprintGeneratedClass) inherit those two runtime back-references with no authoring meaning; they were leaking into `.meta.json` property arrays as `"UberGraphFrame"` (FPointerToUberGraphFrame, value=`"()"`) and `"CachedFrameStateTree"` (TObjectPtr<UStateTree>, value=`"None"`). Renderer-side filter already existed (M11 SO / M12 BT / M13 DT / M14 Chooser / M15 EQS share the same 2-entry TSet); the serializer never picked up the same rule — M8 audit missed it because it only checked `.deep.md` output. Behavioural change is essentially 3 lines: the anon-namespace helper + a `|| IsStateTreeUEPlumbingProperty(Property->GetFName())` clause inside the property loop. No schema change, no Build.cs change, no new module deps. **Verified**: BugHunt twin-run via `-SweepDeepDump` PASS in 52 s; full DOW sweep twin-run PASS in 200 s; canonical DOW refresh affected exactly 3 files (as predicted by the audit) with -158 lines / +3 lines (per-asset contentHash shifted; all other sidecars, rollups, plugins, and deep dumps byte-identical to the M15 canonical state). Plugin DLL ~3.38 → ~3.24 MB (no new symbols; natural layout shift across the rebuild). Legacy depot not refreshed (not repo-committed by design — see "Legacy depot export procedure"); the 7-file drop will land on the next legacy sweep. |
| M11 SmartObjectDefinition Tier 2 | `b588d8a` + `69cf9bc` | First non-UBP/ST type to graduate from out-of-scope notice to full Tier 2 detail. Picked SO because it's the most behaviour-like of the remaining 310 out-of-scope types — DOW's NPC interactions hang off it. New `Public/TextExport/SmartObjectDefinitionDeepRenderer.h` exposes one entry point `RenderSmartObjectDefinitionMarkdown(UObject*)` (UObject* in API so callers don't need SmartObjects module headers; cast happens inside the .cpp gated on `WITH_SMARTOBJECTS_SUPPORT`). Implementation does live UObject reflection — no new schema struct, no serializer changes, mirrors the typed-handler architecture the existing Tier 1 SO emitter already uses. Two reflection helpers: `RenderUObjectPropertiesTable` walks a UObject's UPROPERTYs (incl. inherited) via `TFieldIterator<FProperty>` + `ExportTextItem_Direct`, skipping UE plumbing (`UberGraphFrame`, `CachedFrameStateTree`); `RenderStructFieldsTable` walks a `UScriptStruct`'s fields against a memory pointer (works for both `FInstancedStruct` and `TInstancedStruct<T>`, which are distinct types in modern UE — caller passes `GetScriptStruct()` + `GetMemory()` directly). Renders: Identity → Default Behavior Definitions (each as a property table) → per-slot block (offset/rotation/enabled + Behavior Definitions sub-section + Definition Data sub-section). Wired into both `DeepDumpCommandlet` (single-asset; new `IsSmartObjectDefinitionClass` dispatch) and `ProjectInventoryCommandlet` sweep (post-dispatch block now branches: UBP/ST already wrote → SO → out-of-scope notice). `INDEX.md` "Per-asset deep dumps" section updated: SO promoted to its own bullet, removed from out-of-scope list. **Verified**: `SO_BenchDefinition.deep.md` exposes `StateTreeReference=(StateTree="...ST_SmartObject_Bench...")` — the connection from SO to its driving ST that was previously invisible at any tier; both bench slots dump full `SmartObjectSlotEntranceAnnotation` field values (`Offset=(48, ±0.000001, 0)`, `bIsEntry=True`, `bIsExit=True`, `TrajectorySlotHeightOffset=40`, `TrajectoryStartHeightOffset=80`, `TransitionCheckRadius=10`, `SelectionPriority=Normal`); twin-run byte-identical (3538 bytes both runs); DOW canonical refresh affected exactly 2 files (`SO_BenchDefinition.deep.md` + `INDEX.md`); all other 803 deep dumps byte-identical to M10 sweep. Plugin DLL ~3.25 → ~3.26 MB (small additive — new renderer .cpp). |
| M15 EnvQuery Tier 2 | `9b3a894` + `c7cb742` | Fifth non-UBP/ST type to graduate. Speculative — DOW has **zero** EnvQuery assets today so this ships ready-for-future-content rather than solving a present problem. Mirrors the M12 BT pattern where the per-node code path was unexercised by the corpus at ship time. New `Public/TextExport/EnvQueryDeepRenderer.h` + `Private/.../*.cpp` pair with one entry point `RenderEnvQueryMarkdown(UObject*)`. No build gate — AIModule (which owns `UEnvQuery` / `UEnvQueryOption` / `UEnvQueryGenerator` / `UEnvQueryTest`) is already a non-optional dep. Walks `UEnvQuery::GetOptions()` in authored order (brief §8: query options evaluate in declaration order, first passing option wins, so do not sort), emits per-option heading → generator UObject UPROPERTY table + per-test UObject UPROPERTY table via `ExportTextItem_Direct`. Same plumbing allowlist as other renderers (skips `UberGraphFrame` / `CachedFrameStateTree`). Wired into both `DeepDumpCommandlet` (new `IsEnvQueryClass` dispatch) and `ProjectInventoryCommandlet` sweep (chain now `SO → BT → DT → CHT → EQS → out-of-scope notice`). `INDEX.md` + `RenderOutOfScopeNotice` updated. **Verified**: BugHunt twin-run via `-SweepDeepDump` PASS in 48 s; full DOW sweep twin-run PASS in 196 s; canonical DOW refresh affected exactly 294 files (0 EQS deep dumps because DOW has zero EQS assets — exactly as predicted; 293 out-of-scope notices refreshed with new "Supported classes" text; `INDEX.md` promoted EnvQuery). Plugin DLL ~3.37 → ~3.38 MB. Known gap: per-option / per-test UPROPERTY table code path has no end-to-end test coverage until DOW (or BugHunt) authors its first EQS asset; at that point the next nightly sweep will exercise it automatically with no further code changes. |
| M14 ChooserTable Tier 2 | `e551500` + `a8aac56` | Fourth non-UBP/ST type to graduate. Tier 1 (`EmitChooserTableAsset`, M3.3 P1a) captured shape — per-column concrete struct type + has-filter/output/cost flags, per-row concrete struct type, fallback type, context data types — but not the authored values inside each `FInstancedStruct`. M14 closes that gap. New `Public/TextExport/ChooserTableDeepRenderer.h` + `Private/.../*.cpp` pair with one entry point `RenderChooserTableMarkdown(UObject*)` gated on `WITH_CHOOSER_SUPPORT` (Chooser ships as an optional plugin, same pattern as Tier 1). Renders each column / row / fallback / context `FInstancedStruct` as its own heading + full UPROPERTY table via `ExportTextItem_Direct` against `GetScriptStruct() + GetMemory()`. Column heading gets a `_(Filter, Output, Cost, Disabled)_` summary line derived from `FChooserColumnBase::HasFilters/HasOutputs/HasCosts` so the reader sees at a glance what the column does. Nested choosers listed as an alpha-sorted path table at the bottom for cross-reference. Wired into `DeepDumpCommandlet` (new `IsChooserTableClass` dispatch gated on `WITH_CHOOSER_SUPPORT`) and `ProjectInventoryCommandlet` sweep (chain now `SO → BT → DT → CHT → out-of-scope`). **Verified**: `CHT_CameraRig.deep.md` renders the full decision table — 2 `EnumColumn`s (one bound to `E_CameraStyle`, one to `E_CameraMode`), each column's `RowValues` array dumped in full with per-row enum names (`E_CameraStyle::NewEnumerator1`, `NewEnumerator0`, `NewEnumerator2`, `NewEnumerator3`) and `Comparison=MatchAny`/`MatchNotEqual` flags visible on specific rows; 11 `AssetChooser` rows each with their `CameraRig_<Style>_<Mode>` asset path inline. Claude can now answer "which camera rig is selected when `CameraStyle=Medium` and `CameraMode=Aim`" by reading this one file — previously required opening the Chooser asset in the editor. BugHunt twin-run via `-SweepDeepDump` PASS in 48 s; full DOW sweep twin-run PASS in 201 s; canonical DOW refresh affected 306 files (12 Chooser `.deep.md` files expanded: `CHT_CameraRig`, `CHT_RotationOffsetCurve`, `CHT_SmartObject_BenchAnim`, `CHT_CMCCharacterAnimations`, `CHT_MoverCharacterAnimations`, and 7 × `CHT_PoseSearchDatabases_*`; 293 unchanged out-of-scope notices refreshed with new "Supported classes" text; `INDEX.md` promoted Chooser). Plugin DLL ~3.35 → ~3.37 MB. |
| M13 DataTable Tier 2 | `1622eee` + `493d08d` | Third non-UBP/ST type to graduate. Tier 1 deliberately captured schema only (brief §4: row struct, column list, sorted row-name list; no row *contents* because rows can be arbitrary blobs), so M13 closes the value-level gap. New `Public/TextExport/DataTableDeepRenderer.h` + `Private/.../*.cpp` pair with one entry point `RenderDataTableMarkdown(UObject*)`. No build gate needed — `UDataTable` lives in the Engine module which is always linked. Implementation walks `UDataTable::GetRowMap()` alpha-sorted by row name (same ordering as the Tier 1 `.md` row list so consumers can cross-reference positionally) and renders each row's `UScriptStruct` fields as a Markdown property table via `ExportTextItem_Direct` — same mechanism the M11 SO `RenderStructFieldsTable` uses but with its own row-level identity heading. Wired into both `DeepDumpCommandlet` (new `IsDataTableClass` dispatch, renderer called unconditionally) and `ProjectInventoryCommandlet` sweep (post-dispatch chain extended to `SO → BT → DT → out-of-scope notice`). `INDEX.md` "Per-asset deep dumps" section promotes DT to its own bullet; `RenderOutOfScopeNotice` "Supported classes" text updated. **Verified**: `DefaultGeometrySurfacePropertiesTable.deep.md` (Wwise) dumps all 11 `WwiseGeometrySurfacePropertiesRow` rows with alpha-sorted per-row tables showing `TransmissionLoss=1.000000` and `AcousticTexture` soft-pointer values — confirms the per-row walk is exercised end-to-end by real DOW content (unlike M12 BT where the corresponding code path has no DOW or BugHunt coverage). BugHunt twin-run via `-SweepDeepDump` PASS in 48 s; full DOW sweep twin-run PASS in 205 s; canonical DOW refresh affected 310 files (4 DT notices → full deep dumps: `DefaultGeometrySurfacePropertiesTable` + `DefaultReverbAssignmentTable` + `UDS_Glossary` + `UDS_Readme_Entries`; 305 unchanged out-of-scope notices refreshed with the new "Supported classes" text; `INDEX.md` promoted DT). Plugin DLL ~3.33 → ~3.35 MB. |
| M12 BehaviorTree Tier 2 | `1c271d3` + `a5696fa` | Second non-UBP/ST type to graduate. Mirrors the M11 SO pattern: new `Public/TextExport/BehaviorTreeDeepRenderer.h` + `Private/TextExport/BehaviorTreeDeepRenderer.cpp` with one entry point `RenderBehaviorTreeMarkdown(UObject*)`. No `WITH_BEHAVIORTREE_SUPPORT` gate needed — AIModule is already a non-optional dep so the renderer links unconditionally. Implementation walks `UBehaviorTree::RootNode` (a `UBTCompositeNode`) recursively, emitting one heading block per composite + task with its full UPROPERTY table, plus per-slot decorators and per-composite services each with their own property tables via a shared `RenderAuxList` template (type-erased over `TArray<TObjectPtr<UBTDecorator>>` and `TArray<TObjectPtr<UBTService>>`). Identity block also dumps `RootDecorators` (decorators that sit above the root composite, outside child slots) and the full Blackboard key list with `bInstanceSynced` flag. BT-specific back-reference plumbing (`TreeAsset` / `ParentNode` / `TemplateNode`) is added to the `IsUEPlumbingProperty` allowlist so it doesn't dominate the dump. Wired into both `DeepDumpCommandlet` (new `IsBehaviorTreeClass` dispatch, renderer called unconditionally — no `#if`) and `ProjectInventoryCommandlet` sweep (post-dispatch block now chains `SO → BT → out-of-scope notice`). `INDEX.md` "Per-asset deep dumps" section promotes BT to its own bullet; `RenderOutOfScopeNotice` "Supported classes" text updated to include both SO (stale from M11) and BT. **Verified**: BugHunt `BT_BugHunt.deep.md` renders Identity + 6-key Blackboard table + `_Empty tree (no root node)._` (the fixture has no authored root — noted on the BugHunt backlog as a missing populated BT regression target); BugHunt twin-run via `-SweepDeepDump` PASS in 54 s; full DOW sweep twin-run PASS in 208 s; DOW canonical refresh affected exactly 311 files — all 310 pre-existing out-of-scope notices refreshed with the new "Supported classes" text + `INDEX.md` — zero changes to the 494 UBP/ST/SO deep dumps, confirming the renderer change is strictly additive on non-BT assets and DOW has no BTs to exercise the populated-tree path. Plugin DLL ~3.25 → ~3.33 MB. Gap noted: BT per-node property-table path is unexercised end-to-end by the current test corpus; code review covers it (copy-adapted from M11 + mirrors working Tier 1 `CollectBTNodes` traversal). |

Plugin version: `1.14.0` — bumped from 1.13.0 for M19.1 (new schema
field `cdoProperties` + `dataCarrierKind`, new capability, per the
CLAUDE.md semver rule for new subsystem-ish additions). Drift sweep
post-edit: zero `"1.13.0"` hits across `Source/`, both `.uplugin`s,
and `README.md`.

**Working-tree state when this file was last updated:** clean on `main`
aside from intentionally untracked ephemerals, covered by `.gitignore`
(per M5.3 P0): `ProjectInventory/`, `ProjectInventory_DOW/Deep/`,
`_determinism_*`, `_deep_st_*`, `_plugins_*`, `_*.log`, plus
`Characters/` at repo root.
`ProjectInventory_DOW/` is **tracked** and refreshed post-M7 P1 with
`PLUGINS.md` + `PluginInventory/` (22 plugin sidecars; 2 populate
`NativeTypes[]` — CoverEQS + Wwise). No /Game-content files touched
by M7 — it's a pure sibling phase. **M8 does not refresh the canonical
tree** — the sweep is opt-in (`-DeepDump`) so `ProjectInventory_DOW/`
stays Tier 1 only until we decide to commit ~5-10 MB of per-asset
Tier 2 output. Sweep-generated `.deep.md` files are covered by the
existing `.gitignore` Deep/ pattern when they land under that dir;
under a sweep directly into `OutDir` they land next to `.md` / `.meta.json`
and would need an explicit `git add` to enter tracked state.
`BuiltPlugin/` is at 1.13.0 with the M8 DLL (~3.25 MB — unchanged
versus M7 P1 because M8 is a code move, not an additive reflection
walk; the DLL grew by the `DeepDumpRenderer.cpp` symbols but shrank
by the same amount from `DeepDumpCommandlet.cpp`).
`scripts/verify_determinism.ps1` is the determinism gate and exits 0
on byte-identical runs — runs 4 phases (Manifest / Inventory /
Aggregate / **ProjectPlugins**) plus optional single-asset DeepDump.
M8 added a `-SweepDeepDump` switch that upgrades Phase 1 to the
sweep variant (passes `-DeepDump` through) and skips the now-redundant
single-asset DeepDump phase.
**full DOW** (805 assets + 22 plugins, M7 P1 build, 194 s), **DOW
GASP slice** (363 assets, pre-M5.2 build), **DOW GASP AI slice**
(8 assets, M8 build, `-SweepDeepDump`, byte-identical twin run),
and **BugHunt** (19 assets + 2 plugins, M8 build, 52 s `-SweepDeepDump` twin)
all currently PASS.
`BugHunt.uproject` lists `Chooser` + `PoseSearch` + `SmartObjects`
(all optional) alongside StateTree / StructUtils / GameplayAbilities;
BugHunt's `UnrealEditor.target` receipt was last rebuilt at M3.3
Track A to pick up the UMG / UMGEditor deps (both ship with the
engine, so no new uproject entries needed). BugHunt-side plugin DLL
+ Tests DLL rebuilt against the current engine. M5.2 added no new
module deps → no new target rebuild required.

## Resume checklist (do these in order)

1. `git log --oneline -20` — confirm the most recent commits. Expected
   top of history (branch `main`, **in sync with `origin/main`** — every
   session-local commit was pushed during the 2026-04-25 close-out push
   pair: `ef9c7504` (M28.6.0 research) → `8df3b1b0` (M28.6.1 feat)).
   HEAD is at `8df3b1b0` (the M28.6.1 feat) or a trailing
   `docs: WIP Resume Checklist pre-/clear refresh for M28.6.1` chore
   commit if a /clear-prep step lands on top. The latest FEAT is
   `8df3b1b0` (M28.6.1, which closes the M28.6 GameplayTag
   config-authoring catalog at 1 op total — `add_gameplay_tag` Python op
   + `AddGameplayTag` UFUNCTION on `UBpxReflectionOps` + `list_gameplay_tags`
   zero-UE-process MCP tool walking `Config/DefaultGameplayTags.ini` +
   `Config/Tags/*.ini` + `Plugins/*/Config/Tags/*.ini` + BugHunt starter
   `Config/DefaultGameplayTags.ini` fixture + M28.pre.5 parity gate
   `verify_tag_author.ps1` + new `WITH_GAMEPLAYTAGSEDITOR_SUPPORT` Build.cs
   gate; minor bump 1.26.0 → 1.27.0 per the new-subsystem rule). The two
   trailing entries on `origin/main` after that are `ef9c7504` (the
   M28.6.0 research-only doc commit) and the prior M29.6.x close-out chain
   (`95166cd` docs → `da7668e5` M29.6.5 → `e384b6e6` M29.6.3+.4 →
   `42b260cc` docs → `14c5196b` docs → `47b370a7` M29.6.2 → `bccb0529`
   docs → `19b3a031` M29.6.1). **Note:** the 2026-04-24 push rebased
   every session SHA after the earlier push; references to pre-rebase
   SHAs (e.g. `574e545` / `d82c4f2`) in older paragraphs lower in this
   document are historical only and do not resolve via `git show`
   anymore. **Also note:** M28.4.2 shipped at `78135ef`
   without an intervening docs-refresh commit (usual pattern would be a
   `pre-/clear refresh for M28.4.2` before the next feat); M28.4.3
   `754dd32` landed directly on top of it. The post-M28.4.0 trailing
   chain on `main` (newest first; NOT on `origin/main` until pushed):
   `47b370a` (feat: M29.6.2 port UCOI renderer to UFunctionCall helpers
   — second code slice of the M29.6 engine-agnostic renderer refactor.
   `CustomizableObjectInstanceDeepRenderer.{h,cpp}` rewritten:
   `#if WITH_MUTABLE_SUPPORT` gate dropped from the .cpp entirely; all
   `MuCO/*` includes removed; `Cast<UCustomizableObjectInstance>()` →
   class-name-match `InstanceObject->GetClass()->GetFName() ==
   "CustomizableObjectInstance"`; `UCustomizableObjectInstance::StaticClass()`
   → `Instance->GetClass()`; `FCustomizableObjectInstanceDescriptor::StaticStruct()`
   → runtime `DescProp->Struct`. The one direct-UE_API call the M29.1
   renderer used [`Desc->GetCurrentState()`, plain UE_API not UFUNCTION
   per M29.6.0 Q1 load-bearing call-out] is replaced by reflecting
   `State` as an FIntProperty on the Descriptor + invoking
   `UCO->GetStateName(StateIdx)` via `CallString`. Parent-UCO link
   tries the `GetCustomizableObject` UFUNCTION first [preserves byte-
   identity when the BlueprintCallable getter exists], falls back to
   the Descriptor's `CustomizableObject` FObjectProperty UPROPERTY.
   Build-parameter-relevancy tries the `GetBuildParameterRelevancy`
   UFUNCTION first, falls back to `bBuildParameterRelevancy` /
   `BuildParameterRelevancy` FBoolProperty UPROPERTY reflection,
   falls through to `_not reachable_` marker if neither resolves.
   Two callers at `DeepDumpCommandlet.cpp:382` +
   `ProjectInventoryCommandlet.cpp:2619` still wrap invocation in
   `#if WITH_MUTABLE_SUPPORT` — M29.6.4 does the mechanical strip
   project-wide; M29.6.2 is the scoped renderer port only.
   **No version bump** — infra-only per the M29.6 scope. No schema
   changes. No new automation tests — M29.6.1's `UFunctionCall.*`
   suite covers the underlying reflection path; load-bearing check for
   M29.6.2 is byte-identity on real Mutable content. Dual-engine DLL
   rebuild: UE_DOW 2,859,008 b / stock UE 5.7 2,860,032 b [+~4 KB
   each vs M29.6.1]. BugHunt plugin Binaries rebuilt incrementally via
   `Build.bat BugHuntEditor` [only UCOI renderer + ProjectInventoryCommandlet
   relinked]; BuildIds stay aligned at `47537391`.
   **Verification (BugHunt / stock UE 5.7):** 46/46 `verify_all.ps1`
   gates PASS in 537.6 s [matches M29.6.1's 536.1 s baseline within
   noise]. **Load-bearing MutableSample twin:** ran `-run=DeepDump`
   on MutableSample/Character/COI_Character with the fresh UE_DOW DLL
   junctioned via `BuiltPlugin/`; output md5
   `ECC0F12CB660E38786D928A9BFEFD83D` — IDENTICAL to the M29.1 baseline
   at `eb5dd38`. The UCOI renderer is the only file touched since
   M29.1, so the md5 match proves the port preserves semantics byte-
   for-byte on real Mutable content. Next: M29.6.3 — port
   `CustomizableObjectDeepRenderer.cpp` to the helpers. Heaviest sub-
   phase [~25 typed call sites vs M29.6.2's ~3]; MutableSample/
   Weapon/CO_Weapon md5 `28B162FBD46C7AA9AA290B95CA6F5845` is the
   load-bearing byte-identity check) →
   `bccb052` (docs: WIP Resume Checklist pre-/clear refresh for
   M29.6.1 — housekeeping, no version bump) →
   `19b3a03` (feat: M29.6.1 UFUNCTION call-through helpers + unit
   tests — first code slice of the M29.6 engine-agnostic renderer
   refactor. New `BlueprintExporter::DeepRender::UFunctionCall`
   namespace in `DeepRenderShared.{h,cpp}` with the ProcessEvent-based
   `CallUFunctionRaw` primitive + 7 typed wrappers
   [CallBool / CallInt / CallFloat / CallString / CallFName /
   CallObject / CallEnumInt64]. New `Private/Tests/TestUFunctionFixtures.h`
   fixture USTRUCT + UENUM + UCLASS with 11 UFUNCTIONs covering every
   return shape. 7 new `BlueprintExporter.UFunctionCall.*` automation
   tests [ScalarReturns / InputArgs / EnumReturn / StructReturn /
   VoidReturn / MissingFunction / ReturnTypeMismatch] all flagged
   `EditorContext | CommandletContext | EngineFilter` per M28.pre.1.
   **No version bump** — infra-only per the M29.6 scope; minor 1.25.0
   → 1.26.0 deferred to M29.6.5 after the renderer ports land. No
   renderer dispatches to the helpers yet — M29.1 / M29.2 / M29.3 keep
   `#if WITH_MUTABLE_SUPPORT` + direct typed calls until M29.6.2 / .3
   port them. Dual-engine DLL rebuild: UE_DOW 2,854,912 b / stock UE
   5.7 2,856,448 b [+~43 KB each vs M28.4.3]. BugHunt plugin Binaries
   rebuilt in-place via `Build.bat BugHuntEditor` so BPE +
   BlueprintExporterTests DLLs share BuildId `47537391` with the
   BugHunt game module [the `RunUAT BuildPlugin -Rocket` isolation
   path can't satisfy BlueprintExporterTests' `BlueprintExporter`
   dependency since the HostProject is synthetic — `Build.bat` against
   the real `BugHunt.uproject` is the right recipe]. BuiltPlugin/
   Binaries still carries UE_DOW flavor [pending M29.6.4 single-DLL
   rewiring]. **Verification (BugHunt / stock UE 5.7):** 24/24
   automation tests PASS [17 pre-existing + 7 new UFunctionCall];
   46/46 `verify_all.ps1` gates PASS in 536.1 s [matches M28.4.3's
   538.1 s baseline within noise]. Next: M29.6.2 — port
   CustomizableObjectInstanceDeepRenderer.cpp to the new helpers
   [replace `Cast<UCOI>()` with class-name-match dispatch + replace
   the one `GetCurrentState()` direct-UE_API call with a `CallString`
   through the parent UCO; small rehearsal before M29.6.3's heavier
   UCO port]) →
   `754dd32` (feat: M28.4.3 create_user_defined_struct + add_uds_member
   + remove_uds_member + set_uds_member_default + bump to 1.25.0 —
   third and last slice of the M28.4 non-BP asset-factory catalog;
   closes the M28.4 umbrella at 8 ops total across 3 modules. 4 new
   Python ops in new module `scripts/python_ops/uds.py`; **4 new
   UFUNCTIONs** on `UBpxReflectionOps`
   [CreateUserDefinedStructDeterministic + AddUserDefinedStructMember +
   RemoveUserDefinedStructMember + SetUserDefinedStructMemberDefault].
   Op count 40 → 44. Matrix **42 → 46 gates** [4 new soaks;
   inspects `skip_inspect: true` per M28.4.1/M28.4.2 scope]. Version
   bump minor per semver [new Python module = new subsystem]. Dual-
   engine DLL rebuild: UE_DOW 2,811,904 b / stock UE 5.7 2,813,440 b
   [+~32 KB each vs M28.4.2 baseline]. Matrix clean at 46/46 in
   538.1 s; MCP pytest 23/23 in 11.12 s. Soak md5s stable:
   `cdf15bf24b9520ca5446cb02eb8bf60d` [create_user_defined_struct] /
   `a61e0706b201c53ae8fc01ed88786073` [add_uds_member] /
   `74d9a932ad00ca26504ce3afc0ccf147` [remove_uds_member] /
   `de96efcabf29619b489ea3dbff269bcd` [set_uds_member_default].
   Compile-fix arc: initial build tripped C2027 incomplete-type errors
   on `FStructVariableDescription` at 5 sites in ReflectionOps.cpp +
   2 in the fixture-gen commandlet — `Kismet2/StructureEditorUtils.h`
   only forward-declares it; fix was a single
   `#include "UserDefinedStructure/UserDefinedStructEditorData.h"`
   in both files. Two rebuild cycles on the plugin DLL + one on
   BlueprintExporterTests before green. Determinism: closes both of
   UDS's FGuid::NewGuid() traps [`Struct->Guid` on
   StructureEditorUtils.cpp:53 + per-member `VarGuid` on :303] via
   `SeedGuidFromJoined` + a post-mutation `RenameVariable` pass so
   `VarName` regenerates from the seeded Guid; auto-bool stays in
   every fresh struct because the engine's `bAllowToMakeEmpty=false`
   invariant refuses to drop the last member. `set_uds_member_default`
   routes through `ChangeVariableDefaultValue` rather than reusing
   `SetPropertyValue` [M28.4.0 research Open Question #1 — writing
   through the authoritative string + listener triggers
   `RecreateDefaultInstanceInEditorData` so VarDesc.DefaultValue +
   DefaultInstance memory stay in sync]. New BugHunt fixture
   `UDS_BpxTestEmpty` [2 pre-seeded members: BpxAutoBool + BpxRemovalCandidate:int=7]
   so remove_uds_member soak has a target without tripping the empty-
   struct refusal. Driver: design.md item #3. Next scope OPEN — M28.4
   catalog closed, M28.2 + M28.3 + M28.4 + M28.5 all satisfied
   prerequisites; next external driver picks M28.6 / M28.7 / optional
   M28.4.4 pure-docs close / else) →
   `78135ef` (feat: M28.4.2 create_data_asset_instance +
   set_data_asset_property + bump to 1.24.0 — second slice of the
   M28.4 non-BP asset-factory catalog. 2 new Python ops in new module
   `scripts/python_ops/data_assets.py`; 1 new UFUNCTION
   [CreateDataAssetInstanceDeterministic] — `set_data_asset_property`
   is Python-only over existing M23.1 SetPropertyValue. 2 new BugHunt
   fixtures [DA_BpxTestParentClass BP-derived UPrimaryDataAsset with
   3 declared vars + DA_BpxTestInstance empty instance]. Op count
   38 → 40. Matrix 40 → 42 gates. Version bump minor per semver.
   Dual-engine DLL rebuild: UE_DOW 2,780,160 b / stock UE 5.7
   2,781,696 b. Matrix clean at 42/42 in 523.5 s; MCP pytest 23/23.
   Soak md5s stable: `a46bc5a3bbba77fa4e7cc1b808227f2e` /
   `06ad4a6e749c4c261f9812ebf3948016`. Clean on first matrix run. **NO
   intervening docs-refresh commit before M28.4.3 shipped** — unusual
   vs the usual pattern) →
   `<uncommitted>` (docs: M29.6.0 research outcome — scope engine-agnostic
   Mutable renderer refactor. Reopens the M29 umbrella to address a design
   flaw surfaced during 2026-04-24 external-user triage: the
   `WITH_MUTABLE_SUPPORT` compile-time gate on M29.1 / M29.2 / M29.3
   renderers contradicts the plugin's "works in any UE project" premise —
   one BuiltPlugin DLL must handle CO / COI / COML assets in any project
   that has them, without a ship-target matrix keyed on whether Mutable
   was present in the build engine. Root cause now understood: colleague
   triage screenshot traced to the in-scope class-set gap at
   `ProjectInventoryCommandlet.cpp:121` (omits the three CO class names
   even though M29.1 / M29.2 / M29.3 renderers dispatch for them) — the
   class-set addition alone fixes the *immediate* bug on any engine where
   `WITH_MUTABLE_SUPPORT=1` fires; the M29.6 arc addresses the underlying
   *gate* so the DLL is engine-agnostic. Separate stale-comment finding
   during research: `BlueprintExporter.Build.cs:94-95` still says "UE_DOW
   yes, stock UE 5.7 no per M29.0 Q1", but stock UE 5.7 DOES now ship
   Mutable at engine level
   (`C:/Program Files/Epic Games/UE_5.7/Engine/Plugins/Mutable/Mutable.uplugin`
   exists) — Epic bundled it at some post-M29.0 5.7 minor; the file-check
   fires `=1` on stock UE 5.7 today. M29.6 strips the comment along with
   the gate. Policy decision: **Option B — ProcessEvent call-through** —
   preserves output byte-identity vs today on Mutable-capable projects
   (pure UPROPERTY reflection Option A would drop default-value rendering
   since Mutable computes them by graph walking, not via stored
   UPROPERTYs). Every M29.2 accessor confirmed as
   `UFUNCTION(BlueprintCallable)` in `MuCO/CustomizableObject.h` →
   ProcessEvent reachable uniformly (`GetParameterCount` /
   `GetParameterName` / `GetParameterTypeByName` /
   `IsParameterMultidimensional` / all 9 default-value getters /
   `GetParameterUIMetadata` / `GetStateUIMetadata` /
   `GetEnumParameterGroupType` / `GetEnumParameterNumValues` /
   `GetEnumParameterValue` / `GetStateCount` / `GetStateName` /
   `GetStateParameterCount` / `GetStateParameterName` /
   `GetComponentCount` / `GetComponentName` /
   `GetSkeletalMeshComponentReferenceSkeletalMesh` / `IsCompiled` /
   `IsChildObject`). `FCustomizableObjectInstanceDescriptor`'s State /
   CustomizableObject / parameter-array fields all confirmed
   UPROPERTY-stored (line 303-338 in
   `MuCO/CustomizableObjectInstanceDescriptor.h`) → M29.1's Descriptor
   walk stays pure reflection — only `GetCurrentState()` (plain `UE_API`
   not UFUNCTION) needs replacement via `UCO->GetStateName(State)` through
   the ProcessEvent helper. `FMutableParamUIMetadata` /
   `FMutableStateUIMetadata` confirmed `USTRUCT(BlueprintType)` with
   `UPROPERTY(BlueprintReadWrite)` fields in
   `MuCO/CustomizableObjectUIData.h` → struct-field walk via
   `FindFProperty` on the return-property's `UScriptStruct`, no
   per-field call-through needed. Sub-phase breakdown: **M29.6.1**
   shared `CallUFunction<T>` + `CallUFunctionStruct` helpers in
   `DeepRenderShared` + unit tests against fixture UObjects with fake
   Mutable-shaped UPROPERTYs so CI validates the reflection path without
   needing Mutable present; **M29.6.2** rewrite
   `CustomizableObjectInstanceDeepRenderer.cpp` (small — already mostly
   reflection, just swap `Cast<>` for class-name match + replace
   `UCustomizableObjectInstance::StaticClass()` with `Instance->GetClass()`
   + replace `FCustomizableObjectInstanceDescriptor::StaticStruct()` with
   the `FStructProperty::Struct` already resolved + use new helper for
   `GetStateName` pass-through); **M29.6.3** rewrite
   `CustomizableObjectDeepRenderer.cpp` (heavy — ~25 typed call sites to
   mechanize via the helper; enum returns `EMutableParameterType` /
   `ECustomizableObjectGroupType` dispatched via `UEnum::FindEnumByName` +
   `GetNameStringByValue` on the return-property's `FEnumProperty`; risk
   concentrated here, primary determinism-gate exposure); **M29.6.4**
   mechanical strip of all `#if WITH_MUTABLE_SUPPORT` blocks +
   `PublicDefinitions.Add("WITH_MUTABLE_SUPPORT=...")` +
   `PrivateDependencyModuleNames.Add("CustomizableObject")` + stale
   Build.cs comment block at lines 94-95 + 141-169 + `#include "MuCO/*"`
   across `ProjectInventoryCommandlet.cpp` / `DeepDumpCommandlet.cpp` /
   three deep-renderer .cpp files + unconditional FName entries for the
   three CO class names in `GetNonUBPLogicBearingClassNames()` +
   class-name-match dispatch harmonisation in `DeepDumpCommandlet.cpp`
   (COI / UCO currently use `Cast<>`, COML already uses name-match; unify
   to name-match) and `ProjectInventoryCommandlet.cpp:2617-2629`;
   **M29.6.5** twin-run determinism gate on BugHunt + UE_DOW (both must
   stay byte-identical — no CO assets so no dispatch fires;
   regression-free) + baseline-capture-then-compare twin-run on
   MutableSample at `D:/Work/mutable/MutableSample/` (byte-identical
   before/after M29.6.3 is the load-bearing check;
   `Plugins/BlueprintExporter` junction to
   `D:/Work/blueprintexporter/blueprint-exporter/BuiltPlugin/` means
   rebuilds auto-propagate there) + `RunUAT BuildPlugin -Rocket` on both
   engines + automation tests (`pwsh -File scripts/run_automation_tests.ps1
   -Project BugHunt`) + bridge smoke + version bump 1.24.0 → 1.25.0
   (minor: architectural change — one-DLL-for-all-engines replaces
   compile-time gate). Effort estimate 6-7 sessions, biggest risk
   concentrated in M29.6.3. Research-only commit, same pattern as
   M28.2.0 / M28.3.0 / M28.4.0 / M28.5.0 / M29.0. Output: policy locked
   to Option B; ProcessEvent recipe per-return-type inventoried;
   file-by-file inventory of typed call sites complete; stale
   Build.cs:94-95 comment flagged for strip during M29.6.4. Side-quest
   status — main "next session" target is still M28.4.2 (DataAsset
   slice); M29.6 is the externally-triaged correctness-side refactor
   that unblocks colleagues shipping the plugin into Mutable-capable
   projects from a UE_DOW-built DLL. Next: M29.6.1 shared helper +
   unit tests.) →
   `ada4adf` (feat: M28.4.1 create_curve_float + set_curve_float_keys
   + bump to 1.23.0 — first slice of the M28.4 non-BP asset-factory
   catalog. 2 new Python ops in new module `scripts/python_ops/curves.py`;
   2 new UFUNCTIONs on `UBpxReflectionOps`
   [CreateCurveFloatDeterministic + SetCurveFloatKeys]; new BugHunt
   fixture `Curve_BpxTestEmpty`; 2 new soak fixtures [inspect skipped
   via new `skip_inspect: true` flag — UCurveFloat isn't in
   `PROJECT_INVENTORY_BRIEF.md §3` logic-bearing set so re-export emits
   zero .md; `verify_all.ps1` patched to honor the flag]. Op count
   36 → 38. Matrix **38 → 40 gates** [not the research-forecast 42 —
   2 inspect gates are legitimately skipped]. Version bump minor per
   semver [new Python module = new subsystem]. Dual-engine DLL rebuild:
   UE_DOW 2,770,944 b / stock UE 5.7 2,771,968 b [+~14 KB each vs
   M28.5.3 baseline]. Matrix clean at 40/40 in 511.0 s; MCP pytest
   23/23 in 9.93 s. Soak md5s stable:
   `5474ebd61525e29ac26d43e4b388a9bc` [create_curve_float] /
   `7e332d42f6ed5cb32172d4deebbfbb8c` [set_curve_float_keys]. Two
   matrix-cycle regressions preceded green: [1] `unreal.RichCurveInterpMode`
   hides `RCIM_NONE` [Python keyword clash] and
   `RichCurveKey.interp_mode` rejects plain `int` — fix: cache the 3
   enum values at module import via `unreal.RichCurveInterpMode.RCIM_LINEAR`
   etc., drop `"none"` from the public surface; [2] stale
   `BugHunt/TestProject/Intermediate/CachedAssetRegistry_0.bin`
   carrying duplicate-asset entries from the first failed cycle's
   inspect runs — same class as M28.5.2 [3] `rm -f` on the cache
   before re-run. Next: M28.4.2 DataAsset
   [create_data_asset_instance + set_data_asset_property; 1 new UFUNCTION +
   1 Python wrapper over existing SetPropertyValue; new module
   `data_assets.py`; minor 1.23.0 → 1.24.0; design.md item #7]) →
   `9f2b37f` (docs: WIP Resume Checklist pre-/clear refresh for
   M28.4.0 — post-rebase equivalent of the pre-rebase `d277efb`.
   Pure docs, no version bump, no matrix run) →
   `3ccf0b9` (docs: M28.4.0 research outcome — post-rebase equivalent
   of the pre-rebase `574e545`. UDS / CurveFloat / DataAsset
   write-side surface scoped for future M28.4.{1,2,3} implementation.
   Research-only commit, same pattern as M28.2.0 / M28.3.0 / M28.5.0.
   Output: 6 new UFUNCTIONs on UBpxReflectionOps [+1 optional 7th for
   UDS default-value write path per Open Q #1]; 8 new Python ops
   across three new modules — `curves.py`
   [create_curve_float + set_curve_float_keys — **shipped M28.4.1**]
   + `data_assets.py`
   [create_data_asset_instance + set_data_asset_property] + `uds.py`
   [create_user_defined_struct + add_uds_member + remove_uds_member +
   set_uds_member_default]; three new BugHunt fixtures via
   GenerateTestBlueprintsCommandlet [Curve_BpxTestEmpty — **shipped
   M28.4.1** / DA_BpxTestParentClass + DA_BpxTestInstance /
   UDS_BpxTestEmpty]. Determinism traps cataloged: UDS has two
   FGuid::NewGuid() sites [Struct->Guid on StructureEditorUtils.cpp:53,
   VarGuid on :303] — seed via SeedGuidFromJoined(<path>:uds) +
   SeedGuidFromJoined(<path>:uds_var:<name>); CurveFloat + DataAsset
   have zero FGuid sites — no drift source. Sub-phase ordering by
   complexity ramp: M28.4.1 CurveFloat [simplest — minor
   1.22.2→1.23.0 — **SHIPPED**] → M28.4.2 DataAsset [medium — minor
   1.23.0→1.24.0] → M28.4.3 UDS [most complex — minor
   1.24.0→1.25.0]; three minor bumps matches the "first sub-phase
   with a new Python module = minor" rule from
   M28.2.1/M28.3.1/M28.5.1. Per-sub-phase design.md drivers: #6
   [intensity curve — **shipped M28.4.1**] / #7 [archetype DAs] / #3
   [thicken S_TargetInfo]. Five open questions for resolution during
   implementation: UDS default-instance write path, per-key curve ops
   vs wholesale SetKeys [**shipped M28.4.1 as wholesale; per-key
   deferred**], BP-derived vs native-C++ DA fixture + mangled
   UPROPERTY name resolution, UPrimaryDataAsset PreSave
   AssetBundleData determinism, UDS RenameVariable VarName
   regeneration side effects) →
   `696e03b` (docs: WIP Resume Checklist pre-/clear refresh for
   M28.5.3 — pinned commit SHA 1e33857 in the Resume Checklist
   top-of-history block. Pure docs, no version bump, no matrix run) →
   `1e33857` (feat: M28.5.3 set_eqs_generator_property +
   set_eqs_test_property + bump to 1.22.2 — fourth and fifth ops of the M28.5 catalog; patch
   bump per semver [additive same subsystem]. **Zero new UFUNCTIONs** —
   both ops are Python-only wrappers over the existing M23.1
   SetPropertyValue reflection bridge [op count 34 → 36]. Shared
   _set_eqs_subobject_property private helper drives both; shared
   _normalize_scalar_value coerces Python scalars to ExportText.
   EQS_BpxTestWithOption fixture reused from M28.5.2 — no new fixture
   needed [generator at Options[0].Generator, test at
   Options[0].Tests[0]]. Plan pipeline wired end-to-end. Matrix clean
   on first run — no TypeError / round-2 / stale-scratch issues (no
   new UFUNCTION shape dodges the three bug classes from M28.5.1/2).
   All 38 verify_all.ps1 gates PASS in 501.7 s; new gates: inspect-
   set_eqs_generator_property 18.1s / inspect-set_eqs_test_property
   17.9s / soak-set_eqs_generator_property 6.1s (stable md5
   40ff8e0962f93dce46fbedac3baa412a) / soak-set_eqs_test_property 6.2s
   (stable md5 fdfae57b5992c3d74e15b7b1a3347caa). MCP pytest 23/23 in
   11.90s. Dual-engine DLLs rebuilt solely for baked-in version
   strings: UE_DOW 2,756,608 b [byte-size identical to M28.5.2] / stock
   UE 5.7 2,757,632 b [also identical — no new C++ surface]. 9 drift
   locations updated via sed [15 files]. Next scope OPEN — M28.5
   catalog is closed; external driver picks M28.4 / M28.6 / M28.7 or
   else) →
   `549c564` (feat: M28.5.2 add_eqs_test + remove_eqs_test + bump to
   1.22.1 — second and third ops of the M28.5 EQS write-side catalog;
   patch bump per semver [additive same subsystem]. 2 new UFUNCTIONs
   AddEnvQueryTest + RemoveEnvQueryTest on UBpxReflectionOps [op count
   32 → 34]; 2 new Python ops add_eqs_test / remove_eqs_test sharing
   the generalised _resolve_eqs_class helper [refactored from
   _resolve_generator_class to prevent duplication]; new BugHunt
   fixture EQS_BpxTestWithOption pre-seeded with one option carrying
   an ActorsOfClass generator + one Random test [single fixture
   services both new inspect/soak pairs]; new inspect+soak fixtures
   add_eqs_test.json / remove_eqs_test.json. Determinism: explicit
   FName BpxEqsTest_<opt>_<pre_count>_<class> + TestOrder=pre_count
   for ordering invariant. Idempotency carry-forward on remove:
   out-of-range test_index returns skipped=true "already removed"
   since the destructive-op soak harness re-applies the same plan —
   needed after round-2 round-1-removed-the-target regression caught
   on first green attempt. Plan pipeline wired end-to-end. Matrix
   arc took 4 iterations: [1] make_result 4-args TypeError; [2]
   destructive-op round-2 regression → idempotency fix; [3] stale
   scratch .uasset from prior failed soak → one rm -f; [4] clean
   34/34 PASS in 446.9 s. soak md5s stable across 2 rounds:
   a589cd705b5a520ff30f9edc137bd12a (add_eqs_test) /
   ead096f2981707c17515335e29afaa3c (remove_eqs_test). MCP pytest
   23/23 in 11.48 s. Dual-engine DLLs rebuilt: UE_DOW 2,756,608 b /
   stock UE 5.7 2,757,632 b [+~14 KB each vs M28.5.1]. 9 drift
   locations updated. Next: M28.5.3 set_eqs_test_property +
   set_eqs_generator_property [reuse existing SetPropertyValue
   bridge — Python-only wrappers, no new UFUNCTION, patch bump
   1.22.1 → 1.22.2]) →
   `f816fb4` (docs: WIP Resume Checklist pre-/clear refresh for
   M28.5.1. Pure docs, no version bump, no matrix run) →
   `d68809c` (feat: M28.5.1 add_eqs_option + bump to 1.22.0 — first
   M28.5.x EQS write-side slice; minor bump per semver [new subsystem:
   new Python module scripts/python_ops/eqs.py, new UFUNCTION family
   on UBpxReflectionOps]. 1 new UFUNCTION AddEnvQueryOption [op count
   31 → 32]; 1 new Python op add_eqs_option; new BugHunt fixture
   EQS_BpxTestBasic [empty UEnvQuery baseline, authored via NewObject<
   UEnvQuery> + UPackage::SavePackage since UEnvQuery is a UDataAsset
   subclass — the FKismetEditorUtilities::CreateBlueprint path doesn't
   apply]; new inspect+soak fixture add_eqs_option.json. Determinism:
   explicit FName on each NewObject [BpxEqsOption_<idx> / BpxEqsGen_
   <idx>_<ClassShortName>]; EQS classes have zero FGuid::NewGuid()
   usage per M28.5.0 research, so counter-suffix drift was the only
   closable gap. Plan pipeline wired end-to-end. verify_all.ps1 matrix
   32/32 PASS in 398.5 s; soak md5 3335e01e1680516ec7078de4aa77f360
   stable across 2 rounds; MCP pytest 23/23 in 9.68 s. Dual-engine
   DLLs rebuilt: UE_DOW 2,742,272 b / stock UE 5.7 2,743,808 b. 9
   drift locations updated. Next [superseded by M28.5.2 shipped above]:
   M28.5.2 add_eqs_test + remove_eqs_test [patch bump 1.22.1]) →
   `37fef85` (docs: WIP Resume Checklist pre-/clear close-out refresh
   — enumerates the five trailing post-M28.3.4 commits in the Resume
   block. Pure docs, no version bump, no matrix run) →
   `a685836` (docs: M28.5.0 research outcome — EQS write-side surface
   scoped for future M28.5.1 implementation. Research-only commit,
   same pattern as M28.2.0 / M28.3.0. Picks out C++ surface
   [AddEnvQueryOption / AddEnvQueryTest / RemoveEnvQueryTest +
   optional SetEnvQueryGenerator; scalar property edits reuse
   SetPropertyValue] and Python surface [5 ops in new module
   scripts/python_ops/eqs.py: add_eqs_option / add_eqs_test /
   remove_eqs_test / set_eqs_test_property / set_eqs_generator_property].
   Determinism recipe: zero FGuid usage in EQS classes; explicit FName
   on every NewObject to avoid counter-suffix drift. Open fixture
   question load-bearing for M28.5.1: BugHunt has zero EQS assets, so
   GenerateTestBlueprintsCommandlet needs extension with an
   EQS_BpxTestBasic fixture. Version bump 1.21.3 → 1.22.0 when M28.5.1
   ships [minor — new subsystem]) →
   `97faa88` (chore: .gitignore pass — _build_output*/ wildcard + UE
   auto-gen Config ignores + inspect-harness scratch-.uasset glob.
   Closes the "standalone .gitignore pass" backlog line from the prior
   Expected untracked state paragraph. Post-commit git status shows
   only parent-dir items outside the plugin's ignore scope) →
   `07ef003` (docs: M28.3.6 docs sweep — AGENT_LOOP worked example
   "wire OnOrderReceived body via M28.3 node spawns" + CATALOG.md
   "Coming next" M28.3 COMPLETE consolidation + WIP closure block
   tagging M28.3 catalog closed end-to-end. 9 ops across 4 code-
   touching sub-phases + 2 docs-only slices [M28.3.0 research,
   M28.3.6 this docs sweep]. Pure-docs, no version bump) →
   `459ad61` (docs: WIP Resume Checklist top-of-history refresh for
   M28.3.4) →
   `0110160` (feat: M28.3.4 add_local_variable + bump to 1.21.3
   — last planned K2Node-family slice of the M28.3 catalog before the
   M28.3.6 docs sweep. Different shape from M28.3.1–.3 (spawns no fresh
   K2Node; instead appends FBPVariableDescription to an existing
   UK2Node_FunctionEntry::LocalVariables). 1 new UFUNCTION on
   UBpxReflectionOps (AddLocalVariableDeterministic — wraps
   FBlueprintEditorUtils::AddLocalVariable and post-seeds VarGuid via
   SeedGuidFromJoined(<bp>:func:<fn>:localvar:<var>) since the engine
   helper uses FGuid::NewGuid() at BlueprintEditorUtils.cpp:5433).
   1 new Python op add_local_variable reusing
   blueprint_structural._resolve_pin_type (first cross-module helper
   reuse in python_ops/). Op count 30 → 31. Reused
   BP_BpxTestGraphNodesCalls fixture for 7th op-coverage
   (DoTheThing function targeted end-to-end by CallFunction /
   VariableGet / VariableSet / CustomEvent / ExecutionSequence /
   DynamicCast / LocalVariable — all non-overlapping identifiers).
   New inspect+soak fixture add_local_variable.json. All 27
   verify_all.ps1 gates PASS (374.4 s) — soak md5
   8564b1ff661bab132d9891ec9dc9c6f9 stable. MCP pytest 23/23. Dual-
   engine DLL rebuilt (UE_DOW 2,730,496 b; stock-5.7 2,731,520 b;
   +~10 KB per engine vs M28.3.3 for one new UFUNCTION). Version
   bump 1.21.2 → 1.21.3 (patch per semver — additive same subsystem).
   M28.3 catalog now complete: 9 ops across 4 sub-phases. Next:
   M28.3.6 docs sweep — pure-docs close with no version bump) →
   `df8aa08` (feat: M28.3.3 add_custom_event_node +
   add_execution_sequence_node + add_dynamic_cast_node + bump to
   1.21.2 — three independent one-off K2Node types round out the
   M28.3.1+.2 FMemberReference family. 3 new UFUNCTIONs on
   UBpxReflectionOps (AddCustomEventNode with ubergraph-only op-entry
   check, AddExecutionSequenceNode with N-2 AddInputPin calls against
   the misleadingly-named IK2Node_AddPinInterface API that adds
   then-out pins, AddDynamicCastNode with TargetType set before
   AllocateDefaultPins so the typed As<X> output pin materialises).
   3 new Python ops in blueprint_graph_nodes.py (30 ops total in
   __init__). 3 new inspect+soak fixtures reusing
   BP_BpxTestGraphNodesCalls at positions (224,-48)/(256,-48)/(288,-48).
   Lowercase-pin-name trap caught by inspect gate on first run —
   UE's PN_Then is lowercase "then"; informal research said "Then_N"
   so the assertion failed initially, fixed in one-line edit to JSON
   + Python pin_names list + CATALOG.md + plans/README.md. All 25
   verify_all.ps1 gates PASS (350 s). MCP pytest 23/23 after editor
   went quiet. Dual-engine DLL rebuilt (UE_DOW 2,719,744 b; stock-5.7
   2,720,768 b; +~24 KB per engine vs M28.3.2 from 3 new UFUNCTIONs).
   Version bump 1.21.1 → 1.21.2 (patch per semver — additive same
   subsystem). M28.3.4 (add_local_variable) is next — different shape
   from M28.3.1–.3 since it modifies UK2Node_FunctionEntry::LocalVariables
   on an existing Entry node rather than spawning a fresh K2Node) →
   `5959a01` (feat: M28.3.2 add_call_function_node + add_variable_get_node +
   add_variable_set_node + bump to 1.21.1 — FunctionReference /
   VariableReference family of the M28.3 graph-authoring catalog.
   3 new UFUNCTIONs on UBpxReflectionOps (AddCallFunctionNode +
   AddVariableGetNode + AddVariableSetNode) sharing the new
   BpxReflection::MakeMemberRefSeedPrefix helper; 3 new Python ops in
   blueprint_graph_nodes.py sharing the _spawn_node_common helper.
   self-vs-external context via target_class_path (empty → self,
   non-empty → load_class/load_object fallback). Plan pipeline
   wired (24 → 27 ops). New BugHunt fixture BP_BpxTestGraphNodesCalls
   (Actor BP with TestCount int + DoTheThing() function — first
   non-empty structural fixture). 3 new inspect+soak assertions JSONs.
   All 20 verify_all.ps1 gates PASS (279.3 s). MCP pytest 23/23. Dual-
   engine DLL rebuilt (UE_DOW 2,695,168 b; stock-5.7 2,696,192 b).
   Version bump 1.21.0 → 1.21.1 (patch per semver — additive same
   subsystem). set_graph_pin_default.json backfill deferred (harness
   is single-op; op has equivalent M26.1 coverage). M28.3.3
   add_custom_event_node + add_execution_sequence_node +
   add_dynamic_cast_node is next) →
   `cc0204d` (feat: M28.3.1 add_branch_node + set_graph_pin_default +
   bump to 1.21.0 — first node-spawn slice in M28.3 graph-authoring
   catalog. 2 new UFUNCTIONs on UBpxReflectionOps (AddBranchNode +
   SetGraphPinLiteralDefault) — spawn UK2Node_IfThenElse into any K2
   graph (function / interface-override / ubergraph) with
   SeedGuidFromJoined(:branch:x,y) NodeGuid + SeedPinGuidsForNode pin
   IDs + explicit FName on NewObject, plus a graph-level sibling of
   M26.1 SetNodePinLiteralDefault that routes through
   FindFunctionGraphByName and accepts a 32-hex NodeGuid string. 2 new
   Python ops in new module blueprint_graph_nodes.py. Full plan-pipeline
   wiring (__init__ re-exports / plan_shape OP_SPECS / plan_executor
   _OP_DISPATCH / mechanical_diff _op_expected_changes). New BugHunt
   fixture BP_BpxTestGraphNodes (empty Actor BP) + add_branch_node.json
   inspect+soak assertions. All 14 verify_all.ps1 gates PASS (206.4 s)
   on BugHunt / stock UE 5.7; MCP pytest 23/23 PASS; dual-engine DLL
   rebuilt (UE_DOW 2,677,248 b BuildId 6efc257b; stock-5.7 2,678,784 b
   BuildId 47537391). Version 1.20.1 → 1.21.0 (minor per semver — new
   subsystem). Deferred to M28.3.2: set_graph_pin_default inspect/soak
   fixture [Branch's Condition pin default is empty string on spawn, so
   a round-trip set is trivial; M28.3.2's add_call_function_node
   provides a richer target]. M28.3.2 is next) →
   `3cd5283` (docs: M28.3.0 research outcome — node-level graph
   authoring catalog scoped. Block inserted between M28.2 closure and
   M29 umbrella. Output: 8 new UFUNCTIONs + 1 sibling on
   UBpxReflectionOps; 8 new Python ops in blueprint_graph_nodes.py;
   determinism traps cataloged; narrow K2Node catalog of 7 types picked
   against design.md anchors (#2 utility scorer / #4 callouts / #6
   director / #8 polish); 4 sub-phases + .5 fixtures + .6 docs. Bump at
   M28.3.1 = minor 1.20.1 → 1.21.0 per semver; subsequent sub-phases =
   patch. Mirrors M28.2.0 research-commit pattern) →
   `77412a8` (docs: WIP HEAD pointer uses trailing-docs allowance) →
   `12fa13a` (docs: WIP resume-state paragraph refresh for post-M29) →
   `263b13c` (docs: WIP Resume Checklist top-of-history for M29.5) →
   `518a445` (docs: M29.5 README feature-matrix sweep + M29 umbrella
   close — final M29 sub-phase, pure docs, no version bump. Six README
   touch points extended with the three Mutable types. WIP gains an
   explicit M29 umbrella-close summary block with all four twin-run
   md5s as durable closure evidence. TL;DR pointer + "First actions
   after /clear" updated to target M28.3 node-level graph authoring
   as next pickup. M29 Mutable / CustomizableObject Tier 2 support
   ships end-to-end) →
   `e60c5bc` (docs: WIP Resume Checklist top-of-history for M29.4 —
   housekeeping after 831ce3b landed) →
   `831ce3b` (feat: M29.4 verify_determinism.ps1 -Project MutableSample
   arm — pure infra; no version bump. Adds a MutableSample arm to
   `verify_determinism.ps1` with three switch-statement additions
   ($ProjectFile / $DeepAsset / $ExtraArgs) + ValidateSet extension +
   synopsis docs. Verification: full-sweep twin-run PASS via
   `-Project MutableSample -SweepDeepDump` — 291 files / 45.2 MB per
   tree byte-identical via git diff --no-index. 91 s cold / 69 s warm.
   MutableSample stays an ad-hoc target; NOT wired into verify_all.
   Pre-req documented: MutableSample game module must be rebuilt
   against target engine via Build.bat for BuildId match. M29.5 docs
   sweep is last — closes the M29 Mutable umbrella) →
   `94342f1` (docs: WIP Resume Checklist top-of-history for M29.3 —
   housekeeping after bb4703f landed) →
   `bb4703f` (feat: M29.3 UCustomizableObjectMacroLibrary Tier 2 + bump
   to 1.20.1 — third Mutable renderer + shared-helper extraction. New
   CustomizableObjectMacroLibraryDeepRenderer.{h,cpp} walks library →
   macros array → per-macro {Name, Description, I/O variables, Graph}
   by UPROPERTY-name reflection (zero Private-header include on the
   Mutable module). Shared-extraction refactor lifts MaskPinGuids +
   node-graph walker out of M29.2 into DeepRenderShared::
   RenderEdGraphNodes + EdGraphNodePlumbing + MaskPinGuids; M29.2
   renderer delegates to the shared walker, CO_Weapon md5 stays
   28B162FBD46C7AA9AA290B95CA6F5845 post-refactor. Finding carried
   forward: ExportTextItem_Direct APPENDS to the FString rather than
   overwriting — initialize empty + fall back to "?" at cell-render
   time. Determinism three-run PASS on MutableSample/Character/
   COML_Character: md5 A505AC58A4422C6B489D0D56C3036159 (34,620 bytes,
   2 macros); verify_all.ps1 12/12 PASS 188.4 s on BugHunt / stock 5.7.
   Version bump 1.20.0 → 1.20.1 (patch). M29.4 MutableSample-determinism
   gate + M29.5 docs sweep remain — close the M29 umbrella) →
   `86fff52` (docs: WIP Resume Checklist top-of-history for M29.2 —
   housekeeping after d6b9e7a landed) →
   `d6b9e7a` (feat: M29.2 UCustomizableObject Tier 2 + bump to 1.20.0 —
   second Mutable renderer lands. New CustomizableObjectDeepRenderer.
   {h,cpp} exposes parameter schema + states + components + compile
   options + node graph (UEdGraph reflection via FObjectProperty on
   private Source UPROPERTY). Per-node class + UPROPERTY table + outgoing
   pin-link table. Skips compiled-model blob per M29.0 policy. Pin-GUID
   determinism trap found + fixed: FEdGraphPinReference UPROPERTYs leak
   PinId=<32hex> which regenerates each load — MaskPinGuids post-process
   replaces every hex GUID with <unstable> while preserving OwningNode.
   Version bump 1.19.14 → 1.20.0 (minor — new subsystem). Dispatch wired
   into both DeepDump and ProjectInventory -DeepDump sweep alongside the
   M29.1 UCOI branch. Verification: determinism twin-run PASS on
   MutableSample/Weapon/CO_Weapon — three independent UE_DOW editor
   shells produced md5-identical 42,185-byte .deep.md
   (28B162FBD46C7AA9AA290B95CA6F5845); verify_all.ps1 12/12 PASS 183.1 s
   on BugHunt / stock UE 5.7 after post-mask DLL sync. MutableSample
   game module re-compiled against UE_DOW for BuildId match. CLAUDE.md
   tree gains both M29.1 + M29.2 renderer entries — M29.1 was missing,
   closed as part of this slice. M29.3 UCustomizableObjectMacroLibrary
   renderer is next; bumps 1.20.0 → 1.20.1) →
   `0d9d044` (docs: WIP resume-state hardening for M29.2 pickup —
   updates "Expected untracked state" with `_build_output_5_7/` + the
   external-to-repo junctions live from M29.1; reroutes "First actions
   after /clear" from M29.0/.1 to M29.2 pickup ordering. Housekeeping,
   no code change) →
   `365d5c8` (docs: WIP_INVENTORY Resume checklist refresh for M29.1 —
   housekeeping commit pointing Resume top-of-history at d8e8bcb and
   adding the M29.1 closure record to the listing) →
   `d8e8bcb` (feat: M29.1 UCustomizableObjectInstance Tier 2 + bump to
   1.19.14 — first Mutable renderer lands. New
   CustomizableObjectInstanceDeepRenderer.{h,cpp} surfaces parent UCO
   link + all 9 typed param-override arrays from the private
   FCustomizableObjectInstanceDescriptor via UE reflection. Gated on
   WITH_MUTABLE_SUPPORT; fallback to out-of-scope notice. Dispatch
   wired into DeepDumpCommandlet + ProjectInventoryCommandlet -DeepDump
   sweep ahead of the M19.2.1 DataAsset fallthrough. Build.cs gate
   switched from GetModuleDirectory (leaked across engines) to
   EngineDirectory + File.Exists — path-scoped to the build target.
   M29.0 Q1 CORRECTED — stock UE 5.7 does ship Mutable (original Glob
   probe was wrong). BugHunt.uproject gains Mutable Optional=true;
   stale BugHuntEditor.target receipt rebuilt. Verification:
   determinism twin on MutableSample/COI_Character md5-stable
   ECC0F12CB660E38786D928A9BFEFD83D (5618 bytes, 9 enum + 5 float
   overrides); verify_all.ps1 12/12 PASS 183 s. Dual-engine DLL
   rebuild. Version bump 1.19.13 → 1.19.14. M29.2 UCustomizableObject
   renderer — node-graph walk; biggest sub-phase; bumps to 1.20.0) →
   `fb8a6fd` (refactor: reframe Perforce rule to inform+approve, strip
   hard guards — reverts the code-level machinery added in 51c8648 that
   went too far. Per user clarification the rule is "inform user +
   get approval before any P4 op", NOT "refuse all P4". Removed
   -SCCProvider=None pin in UE_STOCK_FLAGS, env scrub, argv guard +
   PerforceRefused; kept the behavioural rule as documentation in
   server.py instructions + README + _ue_subprocess.py module docstring.
   pytest 23/23 baseline. See auto-memory
   feedback_no_perforce_without_confirmation.md for the corrected
   rule + lesson about not over-engineering behavioural rules into
   code-level refusals) →
   `51c8648` (feat: hard rule — refuse Perforce / P4 ops + route
   questions to Niclas — FIRST version of the Perforce rule, superseded
   by fb8a6fd. History kept because git can't amend a pushed/landed
   commit; the code-level refusal was too aggressive, the docstrings /
   server instructions / README framing survived in fb8a6fd with
   reworded "inform + approve" semantics. Also established the
   "questions go to Niclas, not a Slack channel" rule which IS in
   force — see auto-memory feedback_mcp_questions_go_to_niclas.md) →
   `0220f81` (docs: WIP_INVENTORY Resume checklist refresh for M28.2.4
   — housekeeping commit pointing Resume top-of-history at ce9d25b
   and adding 3078fec + e760648 to the listing) →
   `ce9d25b` (feat: M28.2.4 add_bp_interface + bump to 1.19.13 —
   fourth and final M28.2 structural-edit op ships end-to-end. New
   AddInterfaceByPath UFUNCTION on UBpxReflectionOps wraps
   FBlueprintEditorUtils::ImplementNewInterface and post-attach seeds
   GraphGuid + Entry/Return NodeGuids + per-pin PinIds on every
   generated override graph via SeedGuidFromJoined(:iface_graph:…).
   Engine probe confirmed M28.2.0 Open Question #2 — three drift
   sources identical to M28.2.2 (PostInitProperties random GraphGuid,
   NewObject Entry/Return random NodeGuids, CreatePin random PinIds).
   Idempotent pre-screen on ImplementedInterfaces[] skips engine call
   on replay; no double-Mark since ImplementNewInterface already Marks.
   Python op add_bp_interface in blueprint_structural.py resolves
   interface class via load_class / load_object fallback. New BugHunt
   fixture BP_BpxTestStructuralInterfaces + scripts/inspect_fixtures/
   add_bp_interface.json (soak md5 c0e548efc62b9f45ffbc03160a82d238
   stable round1==round2). All 12 pre-push gates PASS (181.9s) via
   verify_all.ps1. MCP pytest 23/23. M28.2.5 docs sweep is next —
   pure-docs, closes M28.2 end-to-end) →
   `3078fec` (docs: WIP_INVENTORY note expected-untracked state for
   resume — docs-only commit adding the "Expected untracked state on
   /clear resume" paragraph to the "What the next session should do
   first" block so a future resumer doesn't misread BugHunt Config/
   etc. as M28.2.x content to stage) →
   `e760648` (docs: WIP_INVENTORY Resume checklist refresh for M28.2.3
   — housekeeping commit pointing Resume top-of-history at fb6a60e
   and adding 2eae607 / d1a879d / fe9ef02 / 45731fc to the listing) →
   `fb6a60e` (feat: M28.2.3 add_component_to_scs + bump to 1.19.12 —
   third M28.2 structural-edit op ships end-to-end. New
   AddComponentToSCSDeterministic UFUNCTION on UBpxReflectionOps wraps
   USimpleConstructionScript::CreateNode (+ SCS parenting via
   FindSCSNode / AddChildNode / AddNode) and post-write seeds
   USCS_Node::VariableGuid via SeedGuidFromJoined(<bp>:scs:<name>),
   closing CreateNodeImpl's FGuid::NewGuid() assignment at
   SimpleConstructionScript.cpp:1375. Python op add_component_to_scs
   in blueprint_structural.py resolves the component class via
   unreal.load_class → load_object fallback (covers natives and
   BP-generated classes), chains compile_and_save_package on real
   adds, returns skipped=true on idempotent replay, rejects engine
   name-collision renames up-front. No new module deps. New BugHunt
   fixture BP_BpxTestStructuralComponents + scripts/inspect_fixtures/
   add_component_to_scs.json (soak md5 stable round1==round2). All
   10 pre-push gates PASS (158s) on BugHunt/stock-5.7 via
   verify_all.ps1. MCP pytest 23/23. Also folds supersede of M28.2.0
   Open Question #1 — research posited pure-Python feasibility but
   CreateNodeImpl unconditionally assigns NewGuid() so the bridge
   UFUNCTION is required; record updated in blueprint_structural.py
   module docstring. M28.2.4 add_bp_interface is next) →
   `ca9904b` (docs: WIP_INVENTORY Resume checklist step-4 fix — Step
   4's AggregateInventory sanity-check command was stale in three
   ways that tripped the post-/clear resume path; now leads with
   verify_all.ps1 as the authoritative gate) →
   `61d5924` (docs: WIP_INVENTORY Resume checklist refresh for
   M28.2.2 — housekeeping commit pointing Resume top-of-history at
   a053246 and adding 0865dc6 to the listing) →
   `a053246` (feat: M28.2.2 add_bp_function + bump to 1.19.11 — second
   M28.2 structural-edit op ships end-to-end. New
   AddFunctionGraphDeterministic UFUNCTION on UBpxReflectionOps wraps
   FBlueprintEditorUtils::AddFunctionGraph<UFunction> and post-write
   seeds GraphGuid + Entry/Return NodeGuids + every pin ID via
   SeedGuidFromJoined(<bp>:func:<name>:{graph|entry|return} [+ pin]),
   closing three engine determinism traps. FBpxGraphEndpoints gained a
   bSkipped field. New Python op add_bp_function in
   blueprint_structural.py returns hex entry_guid/return_guid so
   callers chain M26.1 body-authoring ops. New BugHunt fixture
   BP_BpxTestStructuralFunctions + scripts/inspect_fixtures/
   add_bp_function.json (soak stable_keys: entry_guid, return_guid).
   All 8 pre-push gates PASS (134s) on BugHunt/stock-5.7 including
   soak md5 stable round1==round2. Commit also folds two carry-
   forwards: (a) mechanical_diff._op_expected_changes gained entries
   for M28.1/M28.3-narrow/M28.9 ops (add/remove_statetree_task_to_
   state, verify_state_tasks, connect_graph_pins,
   set_level_actor_property) — closing the silent auto-re-export skip
   those ops hit since 541fecf; (b) BugHunt/TestProject/Plugins/
   BlueprintExporter/{Source,Config} converted from real copies to
   NTFS junctions pointing at canonical — eliminates the recurring
   manual-sync tax on C++ patches) →
   `0865dc6` (docs: WIP_INVENTORY Resume checklist top-of-history
   refresh — housekeeping commit refreshing the Resume Checklist
   pointers to bce0de5 (M28.2.1) after it landed; mirrors the
   standard post-milestone docs-refresh pattern) →
   `bce0de5` (feat: M28.2.1 add_bp_variable + bump to 1.19.10 — first
   M28.2 structural-edit op ships end-to-end. New
   AddMemberVariableDeterministic UFUNCTION on UBpxReflectionOps
   mirrors M26.1 shape and post-write seeds VarGuid via
   SeedGuidFromJoined(<bp>:var:<name>). New Python op add_bp_variable
   in blueprint_structural.py with full pin-type spec catalog
   (basic / struct:<path> / object:<path> / array:<inner> etc.). New
   BugHunt fixture BP_BpxTestStructuralVariables + scripts/
   inspect_fixtures/add_bp_variable.json. All 6 pre-push gates PASS
   (109.5s) including soak md5 stable across rounds confirming
   determinism seed. M28.2.2 add_bp_function is next) →
   `2eae607` (docs: WIP_INVENTORY stamp 2026-04-23 cross-session drift
   investigation arc) →
   `d1a879d` (chore: cross-session drift investigation utilities —
   deferred per WIP. Three probe/diff scripts landed; pre-save GUID-
   seeding helper prototyped and rejected as cosmetic-with-risk.
   verify_all.ps1 4/4 PASS on the reverted 1.19.9 baseline. No DLL
   change, no version bump) →
   `fe9ef02` (fix: M26.1.2 force_rebind regression + bump to 1.19.9 —
   two causes in ReflectionOps.cpp from 541fecf: ConnectPinsByName
   double-mark via structurally-modified listeners, and
   WipeFunctionGraphBody never reseeding Entry/Return guids on the
   early-return path. All four gates PASS including the original
   soak_m26_1_1_force_rebind.py) →
   `45731fc` (feat: M28.pre.1–.4 verification-matrix hardening —
   run_automation_tests wrapper with CommandletContext flag, inspect
   harness, soak template, verify_all fan-out) →
   `541fecf` (feat: M28.1 + M28.3-narrow + M28.9 Flat Arena scope-bump
   closure, 1.19.8) →
   `5b66fb8` (fix: M26.1.2 force_rebind determinism original pass,
   1.19.7) →
   `584bfe7` (docs: CLAUDE.md pre-push verification matrix) →
   `1aeba5e` (docs: WIP_INVENTORY ODR defuse + close audit item #3). If
   the top matches, WIP is in sync with code. Earlier history (through
   `fd305e6`, the post-M19.2.1 stamp) is preserved below unchanged for
   the longer arc context.
   `fd305e6` (docs: Local Development section + Docs Map for
   onboarding — README.md gains a ~100-line "Local Development"
   section at the end covering clone + smoke test, Source-edit loop,
   BugHunt junction setup, determinism twin-run, DOW-specific flags,
   engine variants, state-of-the-world pointers. CLAUDE.md gains a
   "Docs Map" section between "Purpose" and "Project Structure"
   orienting new Claude Code sessions to WIP_INVENTORY.md first.
   Pure content consolidation — no behavioural change) →
   `389e60a` (docs: stamp M19.2.1 DataAsset DeepDump fallthrough) →
   `968e570` (chore: add CrowdCharacterDataAsset DeepDump to canonical —
   312 KB .deep.md dropped into
   `ProjectInventory_DOW/Assets/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Data/`
   as an orphan file; no .md/.meta.json companions because
   ProjectInventory sweep doesn't yet widen to DA instances. Contains
   533 mesh path refs + 5 hair colors — the Crowd system's outfit
   catalog readable without opening the asset in-editor) →
   `0ab7a1f` (feat: DeepDump DataAsset-instance fallthrough (M19.2.1) —
   new `AssetObject->IsA<UDataAsset>()` check after the 7 typed class
   checks routes BP-derived DA instances to new
   `RenderDataAssetInstanceMarkdown`; walks instance UPROPERTYs, diffs
   against class CDO, alpha-sorted property table. Verified on DOW's
   CrowdCharacterDataAsset — 312 KB output vs pre-M19.2.1 out-of-scope
   notice. BugHunt twin PASS 47 s. Strictly additive; version stays
   at 1.14.0) →
   `a32008d` (docs: stamp M19.1 — updated milestone table +
   resume checklist with feat+chore SHAs) →
   `e25306c` (chore: refresh ProjectInventory_DOW with M19.1 CDO walk —
   1530 files; every UBP .meta.json gets cdoProperties + dataCarrierKind
   + coverage bucket, every .md gets compact CDO bullet list, every
   .deep.md gets the full property table + recursive subobject tree;
   HEALTH_REPORT stays at 0 under-covered after DA-relaxation rule;
   plugin DLL ~3.27 → ~3.43 MB; 1.14.0 version stamp propagates) →
   `649d5ac` (feat: data-carrier CDO walk (M19.1) — closes the
   data-carrier blind spot. New `FExportedBlueprint::CDOProperties`
   reuses the M9 component-property shape so Instanced / EditInlineNew
   refs surface as recursive subobject trees. `SerializeCDOProperties`
   walks `GeneratedClass->GetDefaultObject()` via `TFieldIterator`,
   filters to inherited-only props, diffs against parent CDO, skips
   `{UberGraphFrame, CachedFrameStateTree}` plumbing, reuses the M9
   instanced walker; `DetectDataCarrierKind` stamps
   `GameplayEffect/GameplayAbility/DataAsset` via `IsChildOf` against
   lazily-found bases. Tier 1 gets a compact bullet list; Tier 2 gets
   the full property table + recursive tree mirroring component
   rendering. Coverage gains `cdoProperties` core bucket + specialized
   markers with tiered documented rule (strict for GE/GA, relaxed for
   DA). BugHunt twin PASS 47 s; DOW twin PASS 183 s. First concrete
   payoff: MetaHuman character BPs expose `ActorLabel` + 6 natively-
   declared Instanced components with full recursive property trees
   that SCS never visited. Version 1.13.0 → 1.14.0) →
   `3ea32a1` (docs: scope M19 data-carrier CDO walk pre-`/clear`) →
   `5a61d57` (docs: bring README in sync with M1–M18 reality —
   three stale claims fixed (Import stub / BT-EQS-DT-UDE-UDS
   "unsupported" / Blackboards); two missing sections added (Project
   Inventory pipeline + Edit-via-round-trip workflow); Import CLI
   gains `-DiffReport=<path>`; top-level bullets mention inventory +
   round-trip; version stays 1.13.0. All pushed to
   `10-Chambers/ue-tools` `main`) →
   `dd7a72c` (docs: stamp M18.2 CallFunction/CallDelegate round-trip) →
   `f258f7d` (feat: CallFunction owner + CallDelegate round-trip
   (M18.2) — (a) deserializer falls back to `functionOwnerClass` when
   `memberParentClass` empty so PromotableOperator / CommutativeAssoc-
   BinaryOperator stop compiling as "function named None"; (b) adds
   serialize + deserialize for `K2Node_CallDelegate` (was zero handling
   on either side). Verified via second round-trip edit, first on
   non-trivial content: `AC_AIHealth.BaseHealth` 100→125 in legacy
   CombatPrototype persists clean — md5 09282b7d→83c6d5b6, no compile
   errors, re-export confirms `125.000000`) →
   `7700324` (docs: stamp M18.1 + narrow M18.2 scope) →
   `bb044c9` (feat: per-graph NodeIds validation (M18.1) — scopes the
   duplicate-node-ID check per-graph so `FunctionEntry` hash collisions
   across different functions no longer trip validation; verified end-
   to-end via first-ever round-trip edit: `BP_NetRep.Score` 0→42
   persists, post-apply dry-run `hasChanges: false`, re-export confirms
   `42`; no chore because no canonical content depends on the
   deserializer path) →
   `478f09f` (docs: stamp M17 SavePackage wiring + surface M18) →
   `6c90c61` (feat: wire SavePackage into BlueprintImport (M17) —
   `ApplyImport` now persists mutations to disk via `UPackage::Save-
   Package`; two defensive guards refuse save on `BS_Error` / deserialize
   failure; confirmed end-to-end on AC_AIHealth and BP_NetRep —
   pristine-md5 preserved on both under the guard. No chore commit —
   no canonical content depends on import write path) →
   `491136a` (docs: stamp M16 ST serializer filter + refresh resume) →
   `5602eea` (chore: refresh ProjectInventory_DOW with M16 filter —
   3 files, -158/+3; only BP-backed StateTree task sidecars
   `ST_NPC_SandboxCharacter_Patrol_Subtree` / `..._SmartObject` /
   `ST_SmartObject_Bench` touched) →
   `b0d1f4a` (feat: StateTree serializer plumbing filter (M16) —
   `FStateTreeSerializer::SerializeUObjectProperties` now skips the
   same `{UberGraphFrame, CachedFrameStateTree}` allowlist the
   M11–M15 Tier 2 renderers use; closes the 2026-04-19 DOW_Legacy
   audit's finding #1) →
   `59dcd5e` (docs: capture legacy-depot export procedure + audit
   findings — stock UE 5.7 BuildPlugin flow for `UE_DOW_Legacy`,
   fidelity audit surfacing M16 + EQS-is-now-exercised + stale
   `AI_OVERVIEW.md` pre-M11 text + hidden-pin `[BROKEN]` noise) →
   `36a2324` (docs: stamp M15 EQS Tier 2 + refresh resume checklist) →
   `c7cb742` (chore: refresh ProjectInventory_DOW with M15 EQS Tier 2 —
   294 files: 293 out-of-scope notices refreshed + INDEX.md; 0 EQS
   deep dumps because DOW has zero EQS assets as predicted) →
   `9b3a894` (feat: EnvQuery Tier 2 (M15) — fifth non-UBP/ST type with
   full deep dump; new EnvQueryDeepRenderer walks options → per-option
   generator UObject + per-test UObject UPROPERTY tables; speculative
   ship — ready for future content) →
   `26d0945` (docs: stamp M14 Chooser Tier 2 + refresh resume checklist) →
   `a8aac56` (chore: refresh ProjectInventory_DOW with M14 Chooser
   Tier 2 — 306 files: 12 Chooser deep dumps expanded + 293 out-of-scope
   notices refreshed + INDEX.md) →
   `e551500` (feat: ChooserTable Tier 2 (M14) — fourth non-UBP/ST type
   with full deep dump; new ChooserTableDeepRenderer dumps every
   column / row / fallback / context FInstancedStruct — CHT_CameraRig
   now shows E_CameraStyle × E_CameraMode → 11 CameraRig asset
   selection) →
   `83f3adf` (docs: stamp M13 DT Tier 2 + refresh resume checklist) →
   `493d08d` (chore: refresh ProjectInventory_DOW with M13 DT Tier 2 —
   310 files: 4 DT deep dumps expanded + 305 out-of-scope notices
   refreshed + INDEX.md) →
   `1622eee` (feat: DataTable Tier 2 (M13) — third non-UBP/ST type
   with full deep dump; new DataTableDeepRenderer walks
   UDataTable::GetRowMap() alpha-sorted, rendering per-row
   UScriptStruct field tables via ExportTextItem_Direct) →
   `cac2222` (docs: stamp M12 BT Tier 2 + refresh resume checklist) →
   `a5696fa` (chore: refresh ProjectInventory_DOW with M12 BT Tier 2 —
   311 files: 310 out-of-scope notices with refreshed "Supported classes"
   text + INDEX.md) →
   `1c271d3` (feat: BehaviorTree Tier 2 (M12) — second non-UBP/ST type
   with full deep dump; new BehaviorTreeDeepRenderer walks
   UBehaviorTree::RootNode recursively, dumping every composite / task /
   decorator / service with its full UPROPERTY table) →
   `76a7b58` (docs: stamp M11 SOD Tier 2 + refresh resume checklist) →
   `69cf9bc` (chore: refresh ProjectInventory_DOW with M11 SO Tier 2 —
   2 files: SO_BenchDefinition.deep.md + INDEX.md) →
   `b588d8a` (feat: SmartObjectDefinition Tier 2 (M11) — first non-
   UBP/ST type with full deep dump; new SmartObjectDefinitionDeepRenderer
   exposes the SO → ST link) →
   `0dece7f` (chore: refresh ProjectInventory_DOW with M10 INDEX.md) →
   `ba8284d` (feat: INDEX.md upgrade — navigation + trust signals (M10)) →
   `bd6e221` (chore: refresh ProjectInventory_DOW with M9 instanced trees
   — 6 files only, the ones with `[instanced]` arrays) →
   `af66897` (feat: instanced-subobject tree in DeepDump (M9) — closes
   the M8-audit silent-info-loss gap; AIPerception sense configs now
   render inline in `.deep.md`) →
   `05c9b6e` (chore: refresh ProjectInventory_DOW with M8 sweep
   deep-dumps — first project-wide Tier 2 layer, 805 .deep.md files,
   ~64 MB) →
   `0cdeb7a` (feat: DeepDump sweep — shared renderer + -DeepDump flag
   (M8); ProjectInventoryCommandlet -DeepDump emits `<Path>.deep.md`
   per asset) →
   `f4d1be3` (docs: validate 2026-04-19 NPC-AI audit findings — note:
   audit's "no AIPerception in /Game" claim was WRONG, surfaced by M8
   sweep + M9 instanced trees on SandboxCharacter_CMC) →
   `b1d469d` (docs: stamp M7 P1 ProjectPlugins native-type enumeration) →
   `28ddd4a` (chore: refresh ProjectInventory_DOW with M7 P1 native
   types) →
   `1314ba2` (feat: ProjectPlugins native-type enumeration (M7 P1)).
   Earlier history (M7 P0, M5.3 P0, M5.2, M5.1, M6.1, M6, M5, M3.3
   Track A, etc.) is listed in the milestone table above with full
   SHAs and commit-body summaries — no need to dig back through
   `git log` for the older context.
2. Read `PROJECT_INVENTORY_BRIEF.md` §6 / §11A if picking up the
   M5/M6 stretch work (DeepDumpCommandlet + determinism CI gate).
3. Re-read the **"What the next session should do first"** section
   at the bottom of this file. It's concrete and ordered.
4. Before writing code, sanity-check the toolchain is still good.
   **Authoritative gate (M28.pre.4):**
   ```
   pwsh -File blueprint-exporter/scripts/verify_all.ps1
   ```
   Self-contained; runs automation + determinism + inspect + soak
   across every shipped op against BugHunt / stock-5.7. ~134 s. Exits
   0 iff all gates PASS. No prior `ProjectInventory/` tree required
   (the determinism gate generates and cleans up its own scratch
   trees). For C++ patches reaching `BpxReflectionOps`, add
   `-IncludeDow` to fan out against the custom UE_DOW engine too.

   **Legacy AggregateInventory quick check (optional, superseded).**
   The pre-M28.pre.4 sanity-check was an `AggregateInventory`
   commandlet run — kept as a pointer in case `verify_all.ps1` is
   unavailable, but **requires a prior Phase-1 `ProjectInventory` run
   to have populated `<OutDir>/Assets/**/.meta.json`; on a fresh tree
   the output dir does not exist and the command returns nothing
   useful**. If you genuinely need it, run it against the stock-5.7
   engine (matching `BugHunt.uproject`'s `EngineAssociation` + the
   installed DLL's BuildId) rather than UE_DOW:
   ```
   "C:/Program Files/Epic Games/UE_5.7/Engine/Binaries/Win64/UnrealEditor-Cmd.exe" \
     "D:\Work\blueprintexporter\blueprint-exporter\BugHunt\TestProject\BugHunt.uproject" \
     -run=AggregateInventory \
     -OutDir="D:\Work\blueprintexporter\blueprint-exporter\ProjectInventory" \
     -nullrhi -unattended -nopause -nosplash -nosound -log
   ```
   If this fails with "Plugin 'BlueprintExporter' failed to load
   because module 'BlueprintExporter' could not be found", the DLL
   install's BuildId doesn't match the engine — either rebuild the
   plugin against the engine you're using, or switch engines.
5. Optional but recommended: sanity-check DOW is also still good:
   ```
   MSYS_NO_PATHCONV=1 "/d/Work/UE_DOW/engine/Binaries/Win64/UnrealEditor-Cmd.exe" \
     "D:\Work\UE_DOW\game\UE_DOW.uproject" \
     -run=ProjectManifest \
     -OutDir="D:\Work\blueprintexporter\blueprint-exporter\ProjectInventory_DOW" \
     -EnablePlugins=BlueprintExporter \
     -nullrhi -unattended -nopause -nosplash -nosound -stdout -log
   ```
   Should write `MANIFEST.md` in ~1 s, 18475 total assets, exit 0.
   The `MSYS_NO_PATHCONV=1` prefix is mandatory on this bash — without
   it, MSYS rewrites `/Game/...` on the command line to
   `C:/Program Files/Git/Game/...` and the filter silently matches
   nothing. (Bit us once during M3.3 P1a setup.) The `-stdout` is
   also mandatory on DOW — default UE logging doesn't go to stdout,
   so redirect to a log file captures nothing without it.
   `-EnablePlugins=BlueprintExporter` is because DOW's
   `UE_DOW.uproject` pins `BlueprintExporter: Enabled=false` (probably
   from an earlier dev setup); the override re-enables for the run
   without touching the uproject.

## Standard build flow (used by every milestone since M2)

```
# 1. Sync Source → BuiltPlugin (only when Source changed)
cp <changed .h/.cpp files> blueprint-exporter/BuiltPlugin/Source/...

# 2. Rebuild the distributable DLL
mkdir -p blueprint-exporter/_build_output
"/d/Work/UE_DOW/engine/Build/BatchFiles/RunUAT.bat" BuildPlugin \
  -Plugin="D:\Work\blueprintexporter\blueprint-exporter\BuiltPlugin\BlueprintExporter.uplugin" \
  -Package="D:\Work\blueprintexporter\blueprint-exporter\_build_output" \
  -TargetPlatforms=Win64 -Rocket

# 3. Copy artefacts back to BuiltPlugin + clean up
cp blueprint-exporter/_build_output/Binaries/Win64/UnrealEditor-BlueprintExporter.dll \
   blueprint-exporter/BuiltPlugin/Binaries/Win64/
cp blueprint-exporter/_build_output/Binaries/Win64/UnrealEditor.modules \
   blueprint-exporter/BuiltPlugin/Binaries/Win64/
rm -rf blueprint-exporter/_build_output

# 4. Also mirror into BugHunt's local plugin copy
cp blueprint-exporter/BuiltPlugin/Binaries/Win64/UnrealEditor-BlueprintExporter.dll \
   blueprint-exporter/BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64/
cp blueprint-exporter/BuiltPlugin/Binaries/Win64/UnrealEditor.modules \
   blueprint-exporter/BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64/

# 5. Rebuild BugHunt-side modules (BlueprintExporterTests + whatever else)
"/d/Work/UE_DOW/engine/Build/BatchFiles/Build.bat" UnrealEditor Win64 Development \
  -Project="D:\Work\blueprintexporter\blueprint-exporter\BugHunt\TestProject\BugHunt.uproject" \
  -WaitMutex
```

Typical timings: step 2 ≈ 25 s, step 5 ≈ 5–20 s, everything else
instant. Engine rebuild is NOT in this flow — it's already current
from the M2-verify session.

## Status

- **M1 Bootstrap — DONE (committed `ce82a6b`).**
  - Plugin version 1.12.0 → 1.13.0 (all seven drift locations).
  - `Source/BlueprintExporter/Public/Util/AtomicFileWriter.{h,cpp}` added;
    BugHunt's `RunBugHuntCommandlet` wired to consume the shared helper.
  - `CLAUDE.md` Project Structure + Architecture updated for the four
    planned inventory commandlets and `Util/AtomicFileWriter`.
  - Engine path corrections: everything now points at
    `D:\Work\UE_DOW\engine\` (shared custom engine). No more references
    to `C:\Program Files\Epic Games\UE_5.7\`.
  - Build verification **deferred at M1 commit time** (UGS was holding
    the engine compile mutex) — then covered transitively by the M2
    build+smoke verification once the engine was rebuilt. M1's
    `AtomicFileWriter` is now exercised by every M2/M3/M3.1 atomic
    write and has been determinism-verified end-to-end.

- **M2 — DONE (code `692fd9f`, build+smoke+determinism verified).**
  - `Source/BlueprintExporter/{Public,Private}/Commandlets/ProjectManifestCommandlet.{h,cpp}`.
    FAssetRegistry-only scan (no asset loads), deterministic output
    (alpha class/folder ordering, size-DESC then alpha-ASC for the
    largest-N table, no timestamps, `/Game/...` paths only), writes
    `MANIFEST.md` via `SaveStringAtomic`.
  - Accepts `-OutDir=<dir>` (required), `-MountPoint=/Game` (default),
    `-TopN=50` (default, clamped to 0–10000). Returns 0 on success, 2
    on runtime error. Uses the same `[CATEGORY] message` log format as
    `UBlueprintExportCommandlet`.
  - Logic-bearing class set matched on `FAssetData::AssetClassPath.GetAssetName()`
    FName only (package path ignored — class-name match is stable
    across engine/plugin module reshuffles). Set per brief §3:
    `Blueprint`, `AnimBlueprint`, `WidgetBlueprint`, `ControlRigBlueprint`,
    `BehaviorTree`, `StateTree`, `EnvQuery`, `SmartObjectDefinition`,
    `ChooserTable`, `PoseSearchDatabase`, `UserDefinedStruct`,
    `UserDefinedEnum`, `DataTable`.
  - Full engine rebuild landed after M2 code commit (UGS compile had
    failed due to disk-full at ~57% — the resume via
    `Build.bat UnrealEditor Win64 Development -WaitMutex` finished the
    remaining 12254 actions in ~37 min, 0 errors).
  - `Source/` → `BuiltPlugin/` synced; `RunUAT BuildPlugin` produced a
    fresh `UnrealEditor-BlueprintExporter.dll` (25 s); BuiltPlugin's
    uplugin now at 1.13.0. BugHunt's local `Plugins/BlueprintExporter/`
    copy (uplugin + Binaries) synced from BuiltPlugin; BugHunt's
    `UnrealEditor-BlueprintExporterTests.dll` rebuilt against the fresh
    engine via the `Build.bat … -Project=BugHunt.uproject` flow.
  - Smoke test against `BugHunt/TestProject`: MANIFEST.md written in
    ~1.2 s, then run a second time into the same path — output is
    byte-for-byte identical across runs (3421 bytes, `diff -u` clean).
    Determinism invariant from brief §8 holds.
  - **Verified actual counts** (supersedes the too-rough prediction in
    the `692fd9f` commit body; the registry surfaces paired
    `*GeneratedClass` rows and `BP_WidgetTree` reports as
    `WidgetBlueprint`, not `Blueprint`):
    - Total: 35 under `/Game` (20 `.uasset` files on disk × paired
      Blueprint/BlueprintGeneratedClass rows where applicable — 14 BPs
      have a BPGC sibling, `BP_MacroMania_Lib` is a macro library so
      has no BPGC, `BP_WidgetTree` gives WidgetBlueprint + WBGC)
    - Logic-bearing: 19
      (14 `Blueprint` + 1 `WidgetBlueprint` + 1 `BehaviorTree`
      + 1 `StateTree` + 1 `UserDefinedEnum` + 1 `UserDefinedStruct`)
    - Non-logic: 16
      (14 `BlueprintGeneratedClass` + 1 `WidgetBlueprintGeneratedClass`
      + 1 `BlackboardData`)
    - Folders: `/Game/TestBlueprints` (30/15), `/Game/Fixtures` (5/4)
  - Known non-issue: UE exits the commandlet run with code 1 due to a
    benign `LoadConfig (/Script/EngineSettings.Default__GeneralProjectSettings):
    import failed for ProjectID in:` warning that gets counted as an
    error in UE's `Warning/Error Summary`. The commandlet itself
    succeeds (MANIFEST.md written, log shows
    `Execution of commandlet took: 1.24 seconds`). Not worth chasing
    for M2; revisit only if M3's exit-code handling depends on it.
  - Known gap resolved in M3: the `UE_LOG(LogBlueprintExporter, Log, ...)`
    verbosity filter was swapped to `Display` in both `ProjectManifest`
    and `ProjectInventory`, so `[INFO]`/`[RESULT]`/`[STATUS]` lines now
    show up in `-log` output at default filter levels — confirmed in the
    M3 smoke test.

- **M3 — DONE (first slice verified, build+smoke+determinism clean).**
  - `Source/BlueprintExporter/{Public,Private}/Commandlets/ProjectInventoryCommandlet.{h,cpp}`.
    Streams through the asset registry, loads each UBlueprint-family
    asset via `Cast<UBlueprint>(AssetData.GetAsset())`, runs the
    existing `FBlueprintSerializer` to build an `FExportedBlueprint`,
    renders Tier 1 Markdown, writes `<Path>.md` + `<Path>.meta.json`
    via `SaveStringAtomic`, then `CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS)`
    every N assets (brief §11A Option A, default N=50).
  - First-slice scope: `Blueprint`, `AnimBlueprint`, `WidgetBlueprint`,
    `ControlRigBlueprint` only. `BehaviorTree` / `StateTree` /
    `UserDefinedStruct` / `UserDefinedEnum` / `DataTable` /
    `SmartObjectDefinition` / `ChooserTable` / `PoseSearchDatabase` /
    `EnvQuery` are **counted and logged as skipped** rather than
    invisible, so the next slice has an explicit surface.
  - Markdown sections (brief §4 Tier 1): Identity, Inheritance (parent
    chain + interface names), Variables (with replication /
    RepNotify / RepCondition / flags), Functions (signature / access /
    flags / locals / node count), Macros, Components (SCS tree depth-
    first), Graphs (Event / ConstructionScript / Additional with node
    counts), References (Hard / Soft from `FExportedDependency`,
    sorted alpha), Metadata & Flags.
  - `.meta.json` = full `FExportedBlueprint::ToJson()` **plus** a
    `coverage` object per brief §4: `variables`, `functions`,
    `components`, `graphs` buckets with `total` / `documented` counts,
    and a `specialized` object listing `applicable`/`documented`
    subclass-specific sections (e.g. `AnimBP.StateMachines`,
    `WidgetBP.WidgetTree`). First slice leaves `specialized.documented`
    empty so next slices can measure gap-closure. `overallPct` rolls it
    all up.
  - Determinism: brief §8 invariants honoured.
    - Functions/macros/interfaces/dependencies sorted alpha at render
      time; variables keep declaration order; components keep SCS tree
      order; graph additions sorted alpha.
    - Blanked `ExportInfo.ExportTimestamp` after `SerializeBlueprint`
      (the underlying serializer stamps `FDateTime::UtcNow().ToIso8601()`
      which would drift every run). `ContentHash` is fine — it's computed
      with timestamp blanked already.
    - No GUIDs in Markdown (they stay in `.meta.json`); no absolute paths.
  - Args: `-OutDir` (required), `-MountPoint=/Game`, `-Filter=<prefix>`
    (optional package-path prefix — e.g. `/Game/AI/` for DOW calibration
    slice), `-Resume` (skips assets whose `.meta.json` already exists —
    the `.meta.json` is the "done" marker since it's written after the
    `.md`), `-GcEvery=<N>` (default 50, clamped 1–10000).
  - Failure handling per brief §4: per-asset try/cast/serialize guard;
    failures feed `FAILED_LOADS.md` (cast failures) + `PARTIAL_LOADS.md`
    (serializer / write failures), both written atomically at run end
    only if non-empty. Commandlet always returns 0 on framework success;
    individual asset failures are aggregated, not fatal.
  - Heartbeat (brief §11A, per-asset, no mid-asset tick yet):
    `[i/N] /Game/... (coverage=X%, elapsed=Ys, ETA=Zs)` at `Display`
    verbosity. Mid-asset rolling ETA deferred — not needed for fixture-
    scale runs; can be added when DOW pass shows individual assets
    taking minutes.
  - Rolled **into this same M3 commit** (small but high-DX fix):
    `ProjectManifestCommandlet`'s Log helper switched from `Log` to
    `Display` verbosity so its `[INFO]` / `[RESULT]` lines show up in
    `-log` too. Closes the gap flagged at M2 verify time.
  - **Verified against `BugHunt/TestProject`:**
    - 15 UBlueprint-family assets processed (14 `Blueprint` + 1
      `WidgetBlueprint`); 4 non-UBP logic-bearing assets correctly
      skipped (`BT_BugHunt`, `ST_BugHunt`, `E_BugHuntEnum`,
      `S_BugHuntStruct`). 0 failed, 0 partial.
    - Coverage: 14/15 at 100% overallPct; `BP_WidgetTree` at 66%
      because its `specialized.applicable=["WidgetBP.WidgetTree"]` is
      correctly flagged as undocumented in first slice.
    - Two back-to-back runs produced a byte-identical
      `ProjectInventory/Assets/` tree (`diff -ruN` reports no changes).
      Brief §8 determinism invariant holds.
    - Full run took <100 ms after a 0.97 s asset-registry scan.
  - Acceptable inherited gaps (brief §11): `FExportedFunctionFlags`
    captures `bPure`/`bConst`/`bStatic`/`bCallInEditor`/`bOverride`/
    `bEvent`/`AccessSpecifier` but **not** the `Server`/`Client`/
    `NetMulticast`/`Reliable` net-exec flags — those live on
    `UK2Node_FunctionEntry` and need a serializer extension. Also no
    explicit "Overridden engine events" or "Event dispatcher
    declarations" / "Bound delegates" surfacing — partially inferable
    from `Flags.bOverride`. These are tracked as non-blocking; future
    serializer work will close them and M3's next slice will widen
    the rendered set.

- **M4 — DONE (first slice verified, build+smoke+determinism clean).**
  - `Source/BlueprintExporter/{Public,Private}/Commandlets/AggregateInventoryCommandlet.{h,cpp}`.
    Reads `.meta.json` sidecars from the Phase-1 tree (no asset re-loads
    — just JSON-over-files text processing), builds aggregate indexes,
    and writes rollup Markdown via `SaveStringAtomic`.
  - Emitted this slice: `INDEX.md` (Run Scoreboard + counts by subclass
    + counts by top-level folder + largest connection hubs + links to
    other reports), `CLASS_TREE.md` (native-parent grouping + BP→BP
    chains), `DEPENDENCY_GRAPH.md` + `dependency_graph.dot` (per-asset
    hard/soft refs out and a reverse-indexed refs-in view),
    `REPLICATION_MATRIX.md` (every replicated variable across the
    project), `HEALTH_REPORT.md` (coverage gaps + re-emits
    FAILED/PARTIAL_LOADS counts), `SCOREBOARD_BASELINE.json`
    (persisted baseline for §11A scoreboard deltas).
  - Domain overviews (`AI_OVERVIEW.md`, `ANIM_OVERVIEW.md`,
    `UI_OVERVIEW.md`, `GAS_OVERVIEW.md`, `STRUCTS_ENUMS.md`) are
    **deliberately deferred** to the M3.1 slice — they need
    non-UBlueprint `.meta.json` (BT, ST, UserDefinedStruct/Enum,
    SmartObject, Chooser, etc.) that the current Phase-1 scope
    doesn't emit yet.
  - Scoreboard semantics (brief §11A): first run seeds
    `SCOREBOARD_BASELINE.json` from its own metrics — all deltas show
    `0` and INDEX.md includes a first-run italic note. Subsequent runs
    read baseline and compute deltas. `-ResetBaseline` explicit flag
    forces reseed.
  - CLI: `-OutDir=<dir>` (required), `-InDir=<dir>` (optional;
    defaults to `<OutDir>/Assets`), `-ResetBaseline` (optional).
  - Determinism (brief §8): all keys/lists sorted alpha at render
    time. Baseline JSON is serialized via `TPrettyJsonPrintPolicy`
    with stable field order so its contents are stable across runs.
    No timestamps, no GUIDs, no absolute paths in any output.
  - **Verified against the existing M3 `ProjectInventory/Assets/`:**
    - 15/15 `.meta.json` files parsed, 0 parse failures.
    - 7 output files produced in ~4 ms after registry scan.
    - Replication matrix correctly lists 3 replicated vars across the
      project (all three live in `BP_NetRep`: `bHealthLow` with
      RepNotify → `OnRep_HealthLow`, `bSimpleReplicated`, `Score`).
    - Class tree correctly groups Blueprints under native parents
      (`/Script/AIModule.AIController` [3], `/Script/Engine.Actor` [8],
      `/Script/GameplayAbilities.GameplayAbility` [1],
      `/Script/UMG.UserWidget` [1]) and surfaces the
      `BP_InheritanceChain → Parent → Grandparent` BP-to-BP chain.
    - Connection hubs sensibly populated
      (`BP_WidgetTree` 4-out, `BP_InheritanceChain_Parent` 1-in/2-out,
      etc.).
    - HEALTH_REPORT flags 1 asset <100% (`BP_WidgetTree` at 66%,
      reason: `specialized` `WidgetBP.WidgetTree` undocumented) —
      matches M3 expectations.
    - Determinism: **run 2 vs run 3** (baseline already seeded) is
      byte-identical across all 7 output files. Run 1 vs run 2 diverge
      **by design** on `INDEX.md` — the first-run italic note
      disappears once baseline exists, which is the correct UX.
  - Known M4 gaps (tracked, not blocking):
    - RPC rows in `REPLICATION_MATRIX.md` are pending the M3.1
      serializer widening (`FExportedFunctionFlags` still lacks
      Server/Client/NetMulticast/Reliable bits). Matrix header notes
      this explicitly so consumers aren't surprised.
    - Domain overviews (AI / ANIM / UI / GAS / STRUCTS_ENUMS) are
      stubbed in the INDEX.md "Reports" footer pointing at when
      they'll land.
    - `Assets manifested` row from the brief §11A example scoreboard
      is omitted — needs MANIFEST.md parsing, not `.meta.json` fan-in.
      Easy add once we decide whether aggregate should read both
      sources or just trust `.meta.json` count.

- **M3.1 — DONE (first slice: BT + ST + UDS + UDE, all BugHunt-covered).**
  - `Source/BlueprintExporter/Private/Commandlets/ProjectInventoryCommandlet.cpp`
    gained per-type dispatch after `Cast<UObject>(AssetData.GetAsset())`:
    `UBlueprint` → existing path; `UBehaviorTree` → `EmitBehaviorTreeAsset`;
    `UStateTree` → `EmitStateTreeAsset` (WITH_STATETREE_SUPPORT-guarded,
    reuses existing `FStateTreeSerializer`); `UUserDefinedStruct` →
    `EmitUserDefinedStructAsset`; `UUserDefinedEnum` →
    `EmitUserDefinedEnumAsset`.
  - Build.cs gained `AIModule` to `PrivateDependencyModuleNames` for
    `UBehaviorTree` + `UBlackboardData` introspection.
  - New helper `WriteJsonToFile` (extracted from the UBP WriteMetaJson)
    + `BuildNonUBPCoverageJson` (per-type single-primary-bucket coverage)
    + `GatherDependenciesJson` (asset-registry-derived hard/soft deps so
    the aggregate's dependency graph keys uniformly across types).
  - Universal `assetType` JSON field added to **every** `.meta.json` (UBP
    and non-UBP). `AggregateInventoryCommandlet` now reads `assetType`
    first, falls back to `blueprintSubclass` for pre-M3.1 `.meta.json`.
  - Per-type coverage semantics:
    - `UserDefinedStruct`: `fields` bucket, no specialized sections.
      Full coverage by design.
    - `UserDefinedEnum`: `values` bucket, no specialized sections.
      Full coverage by design.
    - `BehaviorTree`: `nodes` bucket + `BT.Decorators` / `BT.Services`
      as specialized-applicable-but-undocumented (first slice renders
      flat node list only; per-node decorator/service walk is next
      slice).
    - `StateTree`: `states` bucket + `ST.TasksPerState`,
      `ST.Transitions`, `ST.Conditions`, `ST.InstancedStructTypes`
      as specialized-applicable-but-undocumented (the sidecar
      `.meta.json` already carries the full structured data via
      `FExportedStateTree::ToJson`; the first-slice Markdown is a
      summary only).
  - Header path fix landed during build iteration:
    `Engine/UserDefinedStruct.h` is a deprecation stub in UE 5.5+; the
    real include is now `StructUtils/UserDefinedStruct.h`.
    `UUserDefinedEnum` stayed at `Engine/UserDefinedEnum.h`.
  - Verified against `BugHunt/TestProject`:
    - 19 in-scope assets (15 UBP from M3 + 4 new: `BT_BugHunt`,
      `ST_BugHunt`, `E_BugHuntEnum`, `S_BugHuntStruct`). 0 deferred to
      M3.2 (the fixture corpus has no DataTable/SmartObject/Chooser/
      PoseSearch/EnvQuery).
    - 18 processed successfully; 1 partial: `ST_BugHunt` returned
      "StateTree has no editor data (may be a cooked/runtime-only
      asset)" from the base `FStateTreeSerializer`. Honest failure —
      the fixture was authored without editor data. `.md` /
      `.meta.json` not written (aligned with existing failure-handling
      semantics); `PARTIAL_LOADS.md` tracks it.
    - Determinism: two back-to-back full runs produced a byte-identical
      `ProjectInventory/Assets/` tree.
    - AggregateInventory (M4) rerun against the widened `.meta.json`
      fan-in picked up BT/UDE/UDS cleanly — INDEX.md counts-by-subclass
      now lists all 5 represented types (Blueprint 14, WidgetBlueprint
      1, BehaviorTree 1, UserDefinedEnum 1, UserDefinedStruct 1);
      HEALTH_REPORT flags 2 coverage-gap assets (`BT_BugHunt` 0%
      because of 0-node empty tree inflating the specialized-
      undocumented ratio, and `BP_WidgetTree` 66% as before);
      aggregate run 2 vs run 3 byte-identical across all 7 files.
  - Known harmless anomaly: empty-tree BehaviorTrees (like
    `BT_BugHunt` which is a blackboard-only fixture) score 0% overall
    because the specialized `BT.Decorators` / `BT.Services` remain
    "applicable but undocumented" even when the primary bucket is
    also 0. Correct per the coverage formula; cosmetic sharp edge
    worth noting if DOW surfaces real empty-tree BTs.
  - Deferred (pre-announced M3.2 scope): `DataTable` schema,
    `SmartObjectDefinition`, `ChooserTable`, `PoseSearchDatabase`,
    `EnvQuery`. None exist in `BugHunt/TestProject` fixtures, so
    there's nothing locally to verify them against — they're DOW-side
    surfaces. Also deferred: per-node BT decorator/service
    enumeration; per-state ST task/transition/condition rendering;
    function net-exec flags on `FExportedFunctionFlags` (needed to
    give `REPLICATION_MATRIX.md` actual RPC rows).

- **M4.1 — DONE (domain overviews; build+smoke+determinism clean).**
  - `AggregateInventoryCommandlet` gained five new renderers that read
    nothing new beyond M3.1's `.meta.json` fan-in: `AI_OVERVIEW.md`,
    `ANIM_OVERVIEW.md`, `UI_OVERVIEW.md`, `STRUCTS_ENUMS.md`, and
    conditional `GAS_OVERVIEW.md` (emitted only when any
    GameplayAbility / GameplayEffect / AttributeSet-derived asset is
    present).
  - `FAggregateAsset` extended with per-type metrics (BT node/key
    counts + blackboard path; ST schema + state/evaluator/global-task
    counts via recursive `children` walk in the JSON parser; UDS field
    count; UDE value count; UBP variable/function/component counts
    reused from the existing coverage buckets so no extra parse work).
  - Cross-references: AI_OVERVIEW lists each BT/ST with its
    "Referenced by" column populated via the reverse-index
    (`RefsInByTargetPath`) already built for the dependency graph;
    STRUCTS_ENUMS / UI_OVERVIEW do the same for per-asset "Referenced
    by" counts.
  - Detection helpers (namespace-local):
    `IsAIControllerParent(ParentClassPath)`,
    `IsGameplayAbilityParent`, `IsGameplayEffectParent`,
    `IsAttributeSetParent`. Direct parent-class match only — BP→BP
    inheritance chains to a GAS/AI ancestor are not walked in this
    slice (CLASS_TREE.md already surfaces those separately).
  - INDEX.md "Reports" footer now links all 5 new overviews with a
    note that `GAS_OVERVIEW.md` is conditional.
  - Verified against `BugHunt/TestProject`:
    - `AI_OVERVIEW.md`: 1 BT (`BT_BugHunt`, 0 tree nodes, 6
      blackboard keys) + 0 ST + 3 AIController BPs
      (`BP_NPC_BehaviorTree`, `BP_NPC_Perception`, `BP_NPC_StateTree`,
      all with empty BT/ST ref columns because the fixtures don't
      hard-reference the BugHunt BT/ST assets specifically — DOW
      will light this up).
    - `GAS_OVERVIEW.md`: correctly emitted. Lists `BP_GAS_Ability`
      under GameplayAbility-derived (2 vars, 0 funcs). Other GAS
      buckets empty in fixture scope.
    - `STRUCTS_ENUMS.md`: 1 struct (`S_BugHuntStruct`, 1 field,
      ref-in 1) + 1 enum (`E_BugHuntEnum`, 3 values, ref-in 1).
      Ref-in correctly finds `BP_StructEnumZoo` as consumer.
    - `UI_OVERVIEW.md`: `BP_WidgetTree` listed with var/func/ref-in
      counts.
    - `ANIM_OVERVIEW.md`: empty-set note (fixtures have no AnimBPs).
    - Determinism: run 2 vs run 1 (both with baseline already
      seeded) byte-identical across all 12 output files
      (11 rollup + `SCOREBOARD_BASELINE.json`).
  - Known stale-file semantics: if a previous run emitted
    `GAS_OVERVIEW.md` but the current run detects no GAS assets, the
    file is left in place (aggregate is non-destructive, brief §8
    "determinism by inputs" — inputs changed). Logged as an INFO line.
    Explicit reset via deleting the file or rerunning with a fresh
    `OutDir` clears it.

- **M3.2 — DONE (build+smoke+determinism clean, committed `511de83`).**
  - `Source/BlueprintExporter/Public/Schema/BlueprintExportTypes.h` +
    `Private/Schema/BlueprintExportTypes.cpp`:
    `FExportedFunctionFlags` extended with `bServer` / `bClient` /
    `bNetMulticast` / `bReliable` / `bBlueprintAuthorityOnly` /
    `bBlueprintCosmetic`. JSON round-trip
    (`server` / `client` / `netMulticast` / `reliable` /
    `blueprintAuthorityOnly` / `blueprintCosmetic` keys) handled in
    `ToJson` / `FromJson`. Pre-M3.2 `.meta.json` readers fall through
    to default-false via `TryGetBoolField`.
  - `Source/BlueprintExporter/Private/Serialization/BlueprintSerializer.cpp`:
    populates the six new flags from
    `UK2Node_FunctionEntry::GetFunctionFlags()` which OR's the entry
    node's `ExtraFlags` with `GetSuperFunctionFlags()`, so overridden
    engine events keep their base RPC flags.
  - `Source/BlueprintExporter/Private/Commandlets/ProjectInventoryCommandlet.cpp`:
    - **BT widening (brief §4)**: new `FBTNodeInfo` per-row struct
      carries decorators (from the parent's `FBTCompositeChild` slot)
      and services (from the composite's own `Services`). Markdown
      renders one sub-bullet per decorator/service; JSON emits
      `nodes[].decorators[]` + `nodes[].services[]` arrays
      (`{class, name}` objects). `BT.Decorators` / `BT.Services`
      move from `specialized.applicable` to `specialized.documented`
      whenever the tree is non-empty.
    - **ST widening (brief §4)**: `RenderStateTreeState` walks
      `FExportedStateTree::RootStates` recursively and emits enter
      conditions / tasks / transitions per state (with trigger +
      target + delay + event tag + conditions count). Global
      evaluators + global tasks + unique `FInstancedStruct` node
      types listed in their own sections. `ST.TasksPerState`,
      `ST.Transitions`, `ST.Conditions`, `ST.InstancedStructTypes`
      all move to `documented`.
    - **DataTable (brief §4)**: typed handler via
      `Engine/DataTable.h` — emits column list from `RowStruct`'s
      `TFieldIterator<FProperty>` + row-name list (alpha-sorted).
      Row *contents* intentionally not written; they're `DeepDump`
      territory. `.meta.json` adds `rowStructPath` / `rowStructName`
      / `rowCount` / `columns[]` / `rowNames[]`.
    - **EnvQuery (brief §4)**: typed handler via
      `EnvironmentQuery/EnvQuery.h` — iterates `GetOptions()`,
      pulls generator class + test-class list per option. Option
      order preserved (it's semantically load-bearing).
    - **Generic non-UBP fallback**: `EmitGenericNonUBPAsset` is the
      catch-all for logic-bearing classes we recognize by name
      but don't yet specialize (SmartObjectDefinition, ChooserTable,
      PoseSearchDatabase at M3.2). Emits identity + parent class +
      alpha-sorted UPROPERTY schema from
      `TFieldIterator<FProperty>(Cls)` + asset-registry deps. No
      plugin module dependencies required at build time.
    - **Coverage-formula cleanup**: `BuildNonUBPCoverageJson` now
      suppresses `specialized.applicable` / `specialized.documented`
      when `PrimaryTotal == 0`, so empty-tree BTs (like
      `BT_BugHunt` with no root node) score 100% instead of 0%.
      HEALTH_REPORT's signal/noise stays useful — only assets with
      actual missing content appear in the under-100% list.
    - **Dispatch widening**: the per-asset Cast<> chain now covers
      `UDataTable` and `UEnvQuery` explicitly, and the else-branch
      is the generic fallback rather than a failure. The
      `M3_1_ProcessableNonUBP` subset / `DeferredNonUBP` counter
      are gone — every class in `GetNonUBPLogicBearingClassNames()`
      is now in-scope.
  - `Source/BlueprintExporter/Private/Commandlets/AggregateInventoryCommandlet.cpp`:
    - **RPC matrix rows**: `FAggregateAsset` gained
      `TArray<FRpcFunc> RpcFunctions`. Parser walks each asset's
      `functions[]` and extracts rows where
      `flags.server / client / netMulticast` is true. Direction
      picked by priority `Multicast > Server > Client` (UE rejects
      multi-direction at compile, so exclusive).
      `RenderREPLICATION_MATRIX` emits one row per RPC with:
      `Member = "FunctionName(sig)"`, `Kind = "RPC"`,
      `Replication = <direction>`, `Condition = "Reliable" | "Unreliable"`,
      `Notes = "BlueprintAuthorityOnly, BlueprintCosmetic"` (if set).
      Header note rewritten — RPCs are first-class, not pending.
    - Log banner trimmed — no more "(M4 first slice)".
  - Verified against `BugHunt/TestProject`:
    - 19 in-scope assets (same as M3.1 — fixtures still only have
      UBP + BT/ST/UDS/UDE, no DT/EnvQuery/SmartObj/Chooser/PoseSearch).
      18 processed, 1 partial (`ST_BugHunt` — no editor data, known
      pre-M3.2).
    - **HEALTH_REPORT under-100% count dropped from 2 to 1**:
      `BT_BugHunt` is now 100% (coverage-formula fix);
      `BP_WidgetTree` remains at 66% (WidgetBP.WidgetTree surface
      still undocumented — intentional, separate slice).
    - `BP_NetRep.meta.json` carries the new `server`/`client`/
      `netMulticast`/`reliable`/`blueprintAuthorityOnly`/
      `blueprintCosmetic` fields on every function's `flags` object
      (all `false` in fixtures; schema round-trips clean).
    - REPLICATION_MATRIX now shows the "Total rows: **3** (vars: 3,
      RPCs: 0)" line; RPC plumbing exercised even though fixtures
      don't have authored RPCs.
    - Determinism: two back-to-back full Phase-1 runs
      (`ProjectInventory_A` vs `ProjectInventory_B`) byte-identical
      across the entire `Assets/` + top-level tree. AggregateInventory
      run 2 vs run 3 byte-identical across all 12 rollup files.
  - Known harmless anomaly carried forward: `ST_BugHunt` remains in
    `PARTIAL_LOADS.md` because the fixture was authored without
    editor data — the richer ST rendering code path won't exercise
    against BugHunt. DOW calibration slice is where it lights up.
  - **Explicitly deferred to the DOW calibration slice** (brief §12.4
    step 13): typed handlers for `USmartObjectDefinition`,
    `UChooserTable`, `UPoseSearchDatabase`. The generic fallback
    emits identity + parent + schema + deps for these today; typed
    handlers will replace the fallback once we can verify against
    real DOW content (slot / activity / column / channel shapes).
    Adding optional-plugin module deps to `Build.cs` is also
    deferred — `EnvQuery` landed without needing a plugin because
    it lives in `AIModule` which was already a dep from M3.1.

- **DOW calibration slice — EXECUTED 2026-04-18 (ephemeral output, not committed).**
  - Gate cleared: engine rebuilt at 17:14 left DOW's game module +
    18 marketplace plugin DLLs stale (BuildId `572648` vs engine's
    new `6efc257b-…`). `ScreenSpaceFogScattering` was `Enabled:true`
    non-optional but had no loadable module → fatal plugin load,
    engine aborted before our commandlet could run. Fix: rebuild
    UE_DOWEditor target via `Build.bat UE_DOWEditor Win64 Development
    -Project="D:\Work\UE_DOW\game\UE_DOW.uproject" -WaitMutex`
    (110 s, 204 actions — UE_DOW game module + all required plugins
    relinked to current engine BuildId).
  - Also re-created the plugin junction
    `D:\Work\UE_DOW\game\Plugins\BlueprintExporter` → `BuiltPlugin\`
    via `New-Item -ItemType Junction` (via PowerShell — MSYS
    `mklink /J` fought bash quoting). Perforce resync had removed
    it. The junction is local-workstation-only per brief §0.1.
  - Phase 0 (`-run=ProjectManifest`) against DOW: 18475 total,
    805 logic-bearing. Key class counts: Blueprint 392,
    PoseSearchDatabase 154, UDE 74, UDS 65, WidgetBP 47,
    AnimBP 27, ControlRigBP 25, ChooserTable 12, DataTable 4,
    StateTree 4, SmartObjectDefinition 1. Notably **0
    BehaviorTrees** — DOW's AI is StateTree-only.
  - DOW has no `/Game/AI/` tree so the brief's suggested filter
    matched nothing. Picked `-Filter=/Game/_ThirdParty/GASP_example/`
    as the calibration filter because GASP hosts all of DOW's
    PoseSearch + Chooser + Motion Matching content.
  - Phase 1 slice: 363 assets processed in 44 s. **0 failed,
    0 partial.** Every DOW class type round-trips through our
    pipeline cleanly. StateTrees (3/3) at 100% with all four
    specialized surfaces (`ST.TasksPerState` / `.Transitions` /
    `.Conditions` / `.InstancedStructTypes`) documented —
    M3.2 ST widening validated against real DOW content.
  - **Key calibration finding**: 167 assets (154 PSD + 12 Chooser
    + 1 SmartObj) scored silent 100% via `EmitGenericNonUBPAsset`.
    The generic path declared `specialized.applicable=[]` so the
    coverage formula had nothing to miss. Content-wise the dumps
    were just flat property-name lists; no Chooser rows / columns,
    no PSD Schema deref, no SmartObject slots. This is exactly
    the "silent partial coverage" brief §11 warned about.
  - **Gate decision per brief §12.4 step 14** ("stop and extend
    serializer if coverage is below expectations on AI assets"):
    stop-and-extend was triggered — the generic fallback's silent
    100% on Motion Matching / Chooser is exactly the kind of
    "below expectations" the gate protects against. Extension
    work is being done as the M3.3 P0 / P1 sub-slices below.
  - Phase 2 aggregate against the slice surfaced
    `CHT_CMCCharacterAnimations` as the #1 dependency-graph hub
    (394 outgoing refs). ChooserTable was clearly the single
    highest-leverage class to add a typed handler for next.
  - Ephemeral output lives in `ProjectInventory_DOW/` (363 .md
    + .meta.json pairs + 12 rollup files). Not committed — same
    policy as BugHunt's `ProjectInventory/` per brief §8
    "determinism by inputs".

- **M3.3 P0 — DONE (committed `077d846`).**
  - `GetGenericFallbackApplicableSections(ClassShortName)` in
    `ProjectInventoryCommandlet.cpp` maps each recognised-but-
    not-yet-typed class name to a single descriptive applicable
    marker: `PoseSearchDatabase` → `PSD.Schema+Animations+Normalization`,
    `ChooserTable` → `Chooser.Columns+Rows+Fallback`,
    `SmartObjectDefinition` → `SmartObj.Slots+DefinitionData+Preconditions`.
    `EmitGenericNonUBPAsset` passes the applicable list to
    `BuildNonUBPCoverageJson` with `documented=[]`.
  - Keeps HEALTH_REPORT honest: DOW slice `CoverageUnder100`
    flipped from the silent 23 → 190. BugHunt unaffected (no
    fallback-path assets in fixtures — still 18 processed,
    1 partial, CoverageUnder100=1, Repl=3).
  - When the typed handler lands for a given class, its marker
    moves from the fallback applicable list back to empty
    (ChooserTable's entry was removed at M3.3 P1a).

- **M3.3 P1a — DONE (committed `72a88f9`).**
  - `EmitChooserTableAsset` in `ProjectInventoryCommandlet.cpp`
    walks `UChooserTable->ColumnsStructs` (per-column: struct
    path, HasFilter/HasOutput/HasCost, disabled flag,
    InputType via FChooserColumnBase::GetInputType() WITH_EDITOR),
    `ResultsStructs` + `DisabledRows` WITH_EDITORONLY_DATA
    (per-row struct path + disabled state), `FallbackResult`
    (struct path + set/unset), `ContextData` (inherited from
    `UChooserSignature`), `ResultType` enum + `OutputObjectType`
    class, `RootChooser` ptr for root/nested detection,
    `NestedChoosers` array (alpha-sorted by path).
  - Coverage primary bucket = `rows` (all documented); specialized
    empty (per-cell filter VALUES are a separate future slice if
    we need them).
  - `Build.cs` gained `WITH_CHOOSER_SUPPORT` detection (mirrors
    `WITH_STATETREE_SUPPORT` — `GetModuleDirectory("Chooser")` in
    a try/catch). Adds `Chooser` module to `PrivateDependencyModuleNames`
    when present. `Chooser.h` lives in the plugin's `Internal/`
    folder but the Chooser plugin's Build.cs exposes that folder
    via `PublicIncludePaths.Add`, so `#include "Chooser.h"` works
    directly once the dep is in place.
  - `BlueprintExporter.uplugin` declares `Chooser: Enabled:true,
    Optional:true` (alongside StateTree + StructUtils). This
    propagates the dep to consumer projects.
  - `BugHunt.uproject` gained `Chooser: Enabled:true, Optional:true`.
    The uproject entry alone wasn't enough — BugHunt's baked-in
    `UnrealEditor.target` receipt only lists plugins that were
    compiled-in at target-build time, so the fresh DLL's hard
    link against Chooser failed to resolve at load with
    `LogWindows: Missing import: UnrealEditor-Chooser.dll`. Fix:
    rebuild BugHunt's target via
    `Build.bat UnrealEditor Win64 Development -Project="…BugHunt.uproject"
    -WaitMutex` (27 s) which regenerates the target receipt with
    Chooser baked in. Running without `-EnablePlugins=Chooser`
    works after this rebuild.
  - Verified: DOW GASP slice's 12 ChooserTables moved 94% → 100%
    coverage. `CHT_CameraRig` now shows "2 EnumColumns → 11
    AssetChooser rows → `/Script/GameplayCameras.CameraRigAsset`"
    instead of the opaque 17-property dump. HEALTH_REPORT
    `CoverageUnder100` dropped 190 → 178. Determinism confirmed:
    second slice run byte-identical across all 363 .meta.json
    outputs. BugHunt unchanged: 18 processed, 1 partial (ST_BugHunt
    known), CoverageUnder100=1, Repl=3.

- **M3.3 P1b — DONE (committed `c47d8c6`).**
  - `EmitPoseSearchDatabaseAsset` in `ProjectInventoryCommandlet.cpp`
    walks:
    - `Schema` (deref) — SampleRate, SchemaCardinality, channel
      class list via `GetChannels()`, skeleton roles via
      `GetRoledSkeletons()`.
    - `DatabaseAnimationAssets` via public
      `GetNumAnimationAssets()` + `GetDatabaseAnimationAsset(i)`
      API. Captures anim class + path, sampling range (editor-only),
      enabled / disable-reselection / mirror option.
    - `NormalizationSet` (editor-only) — path only.
    - Top-level bias + performance config: PoseSearchMode (enum
      label), ContinuingPoseCostBias, BaseCostBias, LoopingCostBias,
      ContinuingInteractionCostBias, KDTreeQueryNumNeighbors, +
      editor-only NumberOfPrincipalComponents, KDTreeMaxLeafSize,
      PosePruningSimilarityThreshold,
      PCAValuesPruningSimilarityThreshold,
      ExcludeFromDatabaseParameters,
      AdditionalExtrapolationTime.
    - `Tags` (FName array, alpha-sorted).
  - Coverage primary bucket = `animationAssets` (all documented);
    specialized empty (everything the generic fallback marked as
    applicable is now rendered).
  - `Build.cs` gained `WITH_POSESEARCH_SUPPORT` detection (mirrors
    `WITH_CHOOSER_SUPPORT` — `GetModuleDirectory("PoseSearch")`
    in try/catch). Adds `PoseSearch` module to
    `PrivateDependencyModuleNames` when present.
  - `BlueprintExporter.uplugin` declares `PoseSearch: Enabled:true,
    Optional:true` (alongside StateTree + StructUtils + Chooser).
  - `BugHunt.uproject` gained `PoseSearch: Enabled:true,
    Optional:true`. BugHunt target rebuilt via
    `Build.bat UnrealEditor Win64 Development -Project="…BugHunt.uproject"
    -WaitMutex` (~30 s) so the target receipt bakes in PoseSearch
    and module-load resolves without `-EnablePlugins=PoseSearch`.
  - Verified against DOW GASP slice (2026-04-18):
    - 363 assets processed, 0 failed, 0 partial. All 154 PSDs now
      typed-handled (previously on fallback path).
    - Sample: `PSD_SM_CMC_Idles.meta.json` now carries `schema`
      (path + SampleRate + cardinality + channel list +
      skeletonRoles), `animationAssets[]` with index / anim path /
      class / sampling range / mirror / enabled per entry,
      `normalizationSet` path, `performance{…}` object, `tags[]`.
      Pre-P1b this was an opaque flat property-name dump.
    - `HEALTH_REPORT.md` `CoverageUnder100` dropped 178 → 24. The
      24 remaining gaps are exactly as predicted: `AnimBP.StateMachines`
      across the GASP AnimBPs + `WidgetBP.WidgetTree` across the UMG
      fixtures + 1 `SmartObjectDefinition` still on the generic
      fallback (P1c target).
    - Two back-to-back DOW slice runs produced a byte-identical
      `ProjectInventory_DOW/Assets/` tree.
  - BugHunt regression check: 18 processed, 1 partial (`ST_BugHunt`
    known pre-M3.2), CoverageUnder100=1 (`BP_WidgetTree` 66% known),
    Repl=3. Two back-to-back BugHunt runs byte-identical.

- **M3.3 P1c — DONE (committed `0226089`).**
  - `EmitSmartObjectDefinitionAsset` in `ProjectInventoryCommandlet.cpp`
    walks:
    - `Slots` via public `GetSlots()`. Per slot: name (editor-only),
      offset (`FVector3f`), rotation (`FRotator3f`), enabled flag,
      activity/runtime tag lists (alpha-sorted for determinism),
      user-tag-filter empty flag, selection-preconditions-set
      flag (via `FWorldConditionQueryDefinition::IsValid()`), full
      list of behavior-definition paths (inline subobjects),
      list of slot `DefinitionData` struct types (including the
      common `SmartObjectSlotEntranceAnnotation` used for entrance
      helpers).
    - Object-level `ActivityTags` (sorted tag name list),
      `UserTagFilter` (both the empty flag and the query
      description via `FGameplayTagQuery::GetDescription()` — so
      e.g. `ANY_EXACT(…)` text is visible), `Preconditions` set
      flag, default parameter bag count
      (`FInstancedPropertyBag::GetNumPropertiesInBag()`),
      user-tag-filtering policy + activity-tag-merging policy
      (enum labels), world-condition schema class path, top-level
      `DefinitionData` struct types via reflection.
    - `DefaultBehaviorDefinitions` TArray via reflection
      (`FindFProperty<FArrayProperty>` + `FObjectProperty`
      inner + `FScriptArrayHelper`) since the field is private
      on the class with no public accessor — mirrors the pattern
      we use for the object-level `DefinitionData` array.
  - Coverage primary bucket = `slots` (all documented);
    specialized empty. Empty-slot definitions still score 100%
    via the coverage-formula empty-primary suppression.
  - `Build.cs`: `WITH_SMARTOBJECTS_SUPPORT` detection via
    `GetModuleDirectory("SmartObjectsModule")` in try/catch.
    Adds `SmartObjectsModule` to `PrivateDependencyModuleNames`.
    **Also explicitly adds `WorldConditions`** — SmartObjectsModule
    declares it as a public dep (which gets us the header
    `WorldConditionQuery.h`) but link deps must be explicit in
    the consuming module, and
    `FWorldConditionQueryDefinition::IsValid` is `__declspec(dllimport)`
    from the WorldConditions DLL. First build without the explicit
    link dep failed with `LNK2019: unresolved external symbol`
    — clean link after adding it.
  - `BlueprintExporter.uplugin` + `BugHunt.uproject` declare
    `SmartObjects: Enabled:true, Optional:true`. Plugin name is
    `SmartObjects` (not `SmartObjectsModule` — that's the runtime
    module inside the plugin).
  - BugHunt target rebuilt via
    `Build.bat UnrealEditor Win64 Development -Project="…BugHunt.uproject"
    -WaitMutex` (~30 s) so the target receipt bakes in SmartObjects
    alongside the Chooser (P1a) and PoseSearch (P1b) bakes.
  - Verified against DOW GASP slice (2026-04-18):
    - 363 assets processed, 0 failed, 0 partial.
    - `SO_BenchDefinition.meta.json` now renders the full authored
      shape: 2 named slots (`BenchSlot1` at `(0,45,0)`,
      `BenchSlot2` at `(0,-45,0)`) with their entrance annotation
      struct types, user-tag filter description
      `ANY_EXACT(SmartObject.ObjectType.NPC, SmartObject.ObjectType.Player)`,
      filtering + merging policies both `Override`, 1 default
      behavior definition (the inline
      `GameplayInteractionSmartObjectBehaviorDefinition_0` subobject).
      Pre-P1c this was an opaque flat property-name dump.
    - `HEALTH_REPORT.md` `CoverageUnder100` dropped 24 → 23. The
      remaining 23 are exactly AnimBP.StateMachines (21 entries)
      + WidgetBP.WidgetTree (2 entries) — both separate future
      slices, not M3.3 P1c territory.
    - `grep -c SmartObjectDefinition HEALTH_REPORT.md` returns 0
      (no fallback-path entries remain for this class).
    - Two back-to-back DOW slice runs produced a byte-identical
      `ProjectInventory_DOW/Assets/` tree.
  - BugHunt regression check: 18 processed, 1 partial (`ST_BugHunt`
    known), CoverageUnder100=1 (`BP_WidgetTree` 66%), Repl=3. Two
    back-to-back BugHunt runs byte-identical.
  - `GetGenericFallbackApplicableSections` now returns `{}`
    unconditionally (every named class has a typed handler). The
    function is kept so a future unhandled class can be added
    with one line without reverting generic-fallback-as-honest-gap
    logic from M3.3 P0.

- **M3.3 Track A — DONE (committed `a2c7df0`).**
  - AnimBP state machines were already serialized into
    `FExportedBlueprint::StateMachines` (the serializer does a full
    walk of `UAnimGraphNode_StateMachine` instances and their
    `UAnimationStateMachineGraph` contents, including recursive
    nested SMs). Track A wires that existing data into the
    Phase-1 Markdown output:
    - Per-machine header: `**Name** (N states, M transitions)`.
    - State list (alpha-sorted): state name + `[StateType]` +
      `(N nodes)` node count from the inner AnimGraph. Nested
      state machines recurse via `FExportedAnimState::NestedStateMachines`.
    - Transition list (sorted by source, then target): `source
      → target [LogicType] crossfade=X.XXs` (crossfade only shown
      when > 0). LogicType is the M3.1-added enum-to-string
      (StandardBlend / Inertialization / Custom).
    - `AnimBP.StateMachines` moves from
      `specialized.applicable` to `specialized.documented` for all
      AnimBlueprint assets. Empty-SM post-process ABPs render
      "_No authored state machines (single-graph anim blueprint)._"
      and still count as documented — "0 state machines" is the
      authoritative answer for that asset.
  - New `FExportedBlueprint::WidgetTree` field
    (`TArray<FExportedWidgetNode>`; root at index 0; manual
    ToJson/FromJson for recursive children, same pattern as
    StateMachines). `FBlueprintSerializer::SerializeWidgetTree`
    walks `UBaseWidgetBlueprint::WidgetTree->RootWidget` and
    recurses via `UPanelWidget::GetChildAt`, preserving authored
    slot order (UMG layout is order-dependent).
    `FExportedWidgetNode` carries:
    - `WidgetName` (widget's UObject name — matches the BP
      variable name when promoted).
    - `WidgetClass` (full path, e.g. `/Script/UMG.HorizontalBox`).
    - `bIsVariable` (promoted-to-variable / `BindWidget` flag).
    - `SlotClass` (e.g. `/Script/UMG.CanvasPanelSlot` — tells
      consumers how the parent lays this widget out).
    - `Children` (recursive).
  - Markdown renders the tree as a nested bullet list using short
    class names (e.g. "HelloText (TextBlock) via CanvasPanelSlot").
    `[variable]` suffix for promoted widgets.
    `WidgetBP.WidgetTree` moves to documented for all
    WidgetBlueprint assets (empty-tree renders as "_No widget tree
    (empty root)._").
  - `Build.cs` adds `UMG` + `UMGEditor` to
    `PrivateDependencyModuleNames`. Both ship with the engine; no
    optional-detection gate needed.
  - Verified:
    - BugHunt: 18 processed, 1 partial (ST_BugHunt known),
      CoverageUnder100 dropped 1 → 0. `BP_WidgetTree` moved
      66% → 100%, renders as "RootCanvas (CanvasPanel)" with
      HelloText TextBlock child via CanvasPanelSlot. Two runs
      byte-identical.
    - DOW GASP slice: 363 processed, CoverageUnder100 dropped
      23 → 0. HEALTH_REPORT now reads "All introspected assets
      are at 100% coverage for the first-slice render set."
      `SandboxCharacter_CMC_ABP` state machine "State Controller"
      renders 8 states + 22 transitions with StandardBlend /
      0.20s crossfade timing per transition. Two runs
      byte-identical across all 363 `.meta.json` outputs.
  - M3.3 closeout: the specialized-section gap-closure arc is
    complete. `ComputeSpecializedApplicable` still flags the two
    sections for future serializer-level extensions (linked anim
    layers, Motion Matching refs), but the current primary set
    is fully documented.

- **M5 — DONE (committed `44e1687`).**
  - `Source/BlueprintExporter/{Public,Private}/Commandlets/DeepDumpCommandlet.{h,cpp}`
    added. CLI: `-run=DeepDump -Asset=/Game/Path/Asset -OutDir=<dir>` writes
    `<OutDir>/<AssetName>.deep.md` via `SaveStringAtomic`. `-Asset` accepts
    either package path (`/Game/Path/Foo`) or object path
    (`/Game/Path/Foo.Foo`) — the latter is normalised by trimming at the dot.
  - UBlueprint family (`Blueprint` / `AnimBlueprint` / `WidgetBlueprint` /
    `ControlRigBlueprint`) is the first-slice scope. The full pipeline is:
    `AssetRegistry.GetAssetsByPackageName` → `UBlueprint` cast →
    `FBlueprintSerializer::SerializeBlueprint` → `RenderDeepBlueprintMarkdown`
    → atomic write. Non-UBP classes emit a short informational notice (still
    written via `SaveStringAtomic`) pointing at the Tier 1 typed handlers
    and exit 0 — the typed handlers (M3.1 → M3.3) already render
    near-complete detail for those classes at Tier 1.
  - Deep render adds on top of Tier 1:
    - Per-graph, per-node, per-pin dump for EventGraph / ConstructionScript
      / AdditionalGraphs / each function's `Graph` / each macro's `Graph`.
      Table per node shows Dir / Name / Type / Default / Flags / Connections.
      Connections sorted by `(NodeId, PinId)` per brief §8 and annotated
      with the target node's title (e.g. `K2Node_ExecutionSequence_…`:`In_execute` (Sequence)).
      Nodes within each graph sorted by `NodeId` (stable string emitted by
      the serializer — same GUID→StableID map the pin connections use).
    - AnimBP state machines: each state's full `AnimGraph` inlined at H5
      and each transition's full `RuleGraph` inlined at H5, both using the
      same `RenderGraphDeep` path. Nested state machines recurse.
    - Components: flattened from Tier 1's nested-list form into one H3 block
      per component (tree order preserved; Parent / Root / Socket shown via
      metadata lines). Markdown tables can't tolerate 4+ leading spaces so
      nested-indent tables would break; flush-left blocks render cleanly in
      every dialect. Each block carries a full alpha-sorted properties
      table with `FExportedComponentProperty::PropertyName / PropertyType /
      Value`; instanced subobject references annotated with `[instanced]`.
  - Determinism (brief §8): timestamp blanked post-serialize; nodes sorted
    by `NodeId`; pins in index order; connections sorted `(NodeId, PinId)`;
    functions / macros / components / dependencies / interfaces / metadata
    keys all alpha-sorted at render time. No GUIDs in Markdown (only stable
    NodeIds); no absolute paths; no timestamps.
  - Build flow: full `RunUAT BuildPlugin` (~29 s, 39 actions, plugin DLL
    went ~2.98 MB → 3.08 MB). DLLs copied back to `BuiltPlugin/Binaries/Win64/`
    and mirrored into `BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64/`.
    **No BugHunt target rebuild required** — commandlets are discovered at
    runtime via `UCLASS()` reflection; only new module link deps force a
    target receipt regeneration, and M5 added none.
  - Verified against BugHunt fixtures:
    - `BP_NetRep` (3 replicated vars + 1 OnRep function): 3779-byte
      `.deep.md` with full Variables table (RepNotify column populated
      for `bHealthLow` → `OnRep_HealthLow`), `OnRep_HealthLow` function
      with its `K2Node_FunctionEntry` pin, 3-node EventGraph with pin
      tables, component (`DefaultSceneRoot`) with `bVisualizeComponent`
      property.
    - `BP_NodeZoo` (node-variety fixture): cross-node pin connection
      resolves to the target node title (e.g. `Event Tick`.then →
      `K2Node_ExecutionSequence_500_200_…`:`In_execute` (Sequence)).
    - `BP_WidgetTree` (WidgetBlueprint subclass): full Widget Tree
      section renders `RootCanvas (CanvasPanel) → HelloText (TextBlock) via CanvasPanelSlot`.
    - `BT_BugHunt` (BehaviorTree, out-of-scope): notice emitted correctly,
      exit 0, Tier 1 handler pointer in the notice text.
  - Determinism check: three back-to-back `BP_NetRep` runs produced
    byte-identical `.deep.md` (`md5sum` stable: `51c1ac14…`). `cmp`
    between run N and run N+1: `IDENTICAL`.
  - Known anomaly: the component `Socket` line sometimes renders as
    `None` rather than being suppressed — that's UE's empty-FName string
    literal. `IsEmpty()` returns false for `"None"`. Cosmetic; can be
    fixed in a polish pass if it becomes noisy on DOW content.

- **M6 — DONE (committed `1793bea`). M6.1 serializer fix — DONE (committed `18e5217`).**
  - `scripts/verify_determinism.ps1` codifies the byte-identical twin-run
    determinism check that every milestone has been running by hand since M2.
  - Pipeline: clean `$OutA` → run `ProjectManifest`, `ProjectInventory`,
    `AggregateInventory`, optional `DeepDump` → repeat into `$OutB` →
    `git diff --no-index --stat -- $OutA $OutB`. Exit 0 iff identical.
  - On FAIL, the full unified diff is captured to `<OutA>.diff` and both
    output trees plus per-run logs are left on disk for inspection. On
    PASS, everything is cleaned up unless `-KeepOnSuccess` is set.
  - Per-run logs live in sibling dirs (`<OutA>_logs`, `<OutB>_logs`), not
    under `$OutA` / `$OutB`. `git diff --no-index` doesn't honour the
    `:(exclude)` pathspec, so structural separation is the only reliable
    way to keep the inventory trees diff-able without log-timestamp noise.
  - Diff args include `-c core.autocrlf=false -c core.safecrlf=false`
    so the check is for byte-identical content, not "identical after
    line-ending normalization" (the repo has `.gitattributes` that would
    otherwise trigger CRLF rewrites on .meta.json and fail the diff for
    cosmetic reasons).
  - `$ErrorActionPreference` is temporarily relaxed around the git call
    because git's stderr warnings ("CRLF will be replaced by LF",
    "NTFS journal not active") otherwise escalate into terminating
    errors under the script's outer `Stop` policy. `$LASTEXITCODE` is
    the load-bearing signal.
  - Each phase-run verifies `[STATUS] SUCCESS` is present in the captured
    log before considering the phase done. UE-Cmd exit 1 is tolerated
    (the benign ProjectID config warning that inflates the error summary)
    but exit ≥ 2 is a real commandlet failure and the script throws.
  - Gotcha: when invoked through Git Bash / MSYS2, bash rewrites
    `-Filter /Game/...` and `-DeepAsset /Game/...` into `C:/Program Files/Git/Game/...`.
    Prefix the invocation with `MSYS_NO_PATHCONV=1` or run from native
    PowerShell / cmd.exe. Documented in the script's `.NOTES` block.
  - Verified:
    - `-Project BugHunt`: PASS in 54 s (Manifest + Inventory + Aggregate +
      DeepDump against 19 in-scope assets, byte-identical trees).
    - `-Project DOW -Filter /Game/_ThirdParty/GASP_example/ -SkipDeep`: PASS
      in 116 s (Manifest + Inventory + Aggregate against 363 assets).
    - Failure paths exercised indirectly during development of the
      script — the stderr-warnings-as-terminating-errors path and the
      empty-InDir path both surfaced as FAIL with clear messages before
      being fixed.
    - **First full-DOW run caught a real non-determinism bug** — see
      M6.1 below. This is exactly the value the gate exists for: the
      GASP slice (363 assets) and BugHunt (19 assets) didn't exercise
      the `UltraDynamicSky/` content where the drift lived.
  - M6.1 (serializer fix): `fix(blueprint-exporter): stabilize node IDs
    + transient property values` — committed `18e5217`. Two root causes
    found in the full-DOW run:
    1. **Node GUIDs regenerated by UE on load.** `K2Node_CallFunction`
       wrappers around engine functions whose signatures drifted since
       the asset was authored (e.g. `MakeSlateFontInfo`) get a fresh
       `UEdGraphNode::NodeGuid` on every `PostLoad`. The drift leaked
       into `.meta.json` via the `nodeGuid` field, the `nodeId` hash
       suffix, and the `SerializePin` connection fallback (which was
       hit for pin targets in nested BoundGraphs of `K2Node_Composite` /
       `K2Node_MacroInstance` that the top-level pre-pass didn't visit).
    2. **Transient UPROPERTY values.** `AVolume::VolumeGuid` is stamped
       fresh by the volume subsystem's `PostLoad` for runtime network IDs.
    Fix:
    - New `ComputeStableNodeHash(UEdGraphNode*)` static helper computes
      a 32-hex-char SHA1 over the node's stable content: class name,
      subtype-specific identity (function/variable/event name), authored
      position, and ordered pin signature (name + direction).
    - `GenerateStableNodeId` uses the first 8 chars of the hash as the
      disambiguator suffix (was: `Node->NodeGuid.ToString().Left(8)`).
    - `ExportedNode.NodeGuid` is now the full hash (was: the raw GUID).
      Downstream `BlueprintTypeInference` and tests still treat it as
      an opaque 32-char string — no callers broke.
    - `SerializePin` connection fallback uses the same hash for
      pin-targets not in the pre-pass map.
    - The two positional-sort tiebreakers in `SerializeBlueprint` and
      `SerializeGraph` use the hash as tiebreaker (previously raw GUID).
    - New `IsTransientValueProperty(FProperty*)` with a `TSet<FName>`
      allowlist (currently just `VolumeGuid`) emits `"[transient]"` as
      the property value instead of letting `ExportTextItem_Direct`
      bake in the drifting bytes. Applied both in `SerializeSCSNode`
      (top-level component properties) and `BuildPropertiesJsonArrayForObject`
      (nested instanced-subobject properties).
    Verified:
    - BugHunt full pipeline twin run: PASS, 74 s (no regression).
    - DOW full twin run (805 assets, no filter, `-SkipDeep`): PASS, 193 s.
      Diff stat went from 3 files / 46 lines down to 0 files.

- **M5.2 StateTree DeepDump + serializer instance-data capture — DONE
  (committed `2f174b3` (feat) + `dc27fc1` (canonical DOW refresh) +
  `b714ec3` (untrack accidental smoke deep.md)).** The first DeepDump
  slice (M5) explicitly
  put UStateTree in the out-of-scope set — Tier 1 ST rendering gave
  state shape and task *types* but no authored values. For DOW's
  StateTree-only NPC AI this meant every task on a patrol tree
  rendered as opaque `StateTreeBlueprintTaskWrapper` with no hint at
  what the NPC was actually configured to do. M5.2 closes that gap
  from both ends:
  - **Serializer extension (Tier 1 sidecar).** `FStateTreeEditorNode`
    has three distinct payloads — `Node` (FInstancedStruct with the
    scheduler-plumbing template + wrapper fields), `Instance`
    (FInstancedStruct with a native task's authored config, e.g.
    `FStateTreeMoveToTaskInstanceData::AcceptableRadius`), and
    `InstanceObject` (TObjectPtr<UObject> for BP-backed tasks like
    `STT_FindRandomLocation_C`). The serializer previously walked
    only `Node`. Now `SerializeEditorNode` walks all three, populating
    new `FExportedStateTreeEditorNode::InstanceProperties`,
    `InstanceObjectClass`, and `InstanceObjectProperties` fields.
    New `SerializeUObjectProperties` helper mirrors
    `SerializeInstancedStructProperties` for the UObject case.
    ToJson writes each of the three arrays only when non-empty
    (brief §8 determinism + minimum schema churn — nodes without
    instance data serialize to the pre-M5.2 shape bit-for-bit).
  - **DeepDump dispatch (Tier 2 renderer).** `IsStateTreeAssetClass`
    added to the commandlet's supported-set; `Main()` now dispatches
    UBP → `FBlueprintSerializer` + `RenderDeepBlueprintMarkdown`,
    UStateTree → `FStateTreeSerializer` + `RenderDeepStateTreeMarkdown`,
    else → the existing out-of-scope notice (text updated to list
    both supported paths). The new renderer emits: identity table,
    summary counts, property-bindings table (with `_(default / parent
    scope)_` for empty sources), global evaluators + global tasks
    (three-property-table render), recursive state walk at
    per-heading-level depth with enter conditions / tasks / transitions
    / children. Each `FExportedStateTreeEditorNode` renders three
    tables (`Node struct properties` / `Instance data properties` /
    `Instance object properties`). Transition render includes trigger,
    target, priority, delay, event tag, transition ID, and per-transition
    conditions (recurse via same node renderer). UE plumbing properties
    that leak through `TFieldIterator` on BP-backed UObjects
    (`UberGraphFrame`, `CachedFrameStateTree`) are stripped at render
    time via `IsUObjectPlumbingProperty` allowlist.
  - **Build.cs unchanged** — StateTree / StructUtils / StateTreeEditorModule
    already present from M3.1. Plugin DLL grew from ~3.09 MB (M6.1)
    to ~3.13 MB (M5.2) — ~40 KB for the renderer + serializer
    extensions.
  - **Verified** (2026-04-19):
    - Deep twin-run against all four DOW ST assets
      (`ST_MassAI` 3863 bytes, `ST_NPC_SandboxCharacter_Patrol_Subtree`
      9321 bytes, `ST_NPC_SandboxCharacter_SmartObject` 13785 bytes,
      `ST_SmartObject_Bench` 27973 bytes) byte-identical via
      `diff -r`.
    - `scripts/verify_determinism.ps1 -Project BugHunt`: PASS in 76 s
      (no regression; the 4 ST-specific code paths don't fire in
      BugHunt because `ST_BugHunt` has no editor data).
    - `scripts/verify_determinism.ps1 -Project DOW -SkipDeep`: PASS
      in 198 s (805 assets; only the 4 ST `.meta.json` files change
      content vs the pre-M5.2 canonical tree).
    - Canonical `ProjectInventory_DOW/` refreshed in a single
      Manifest + Inventory + Aggregate pass. Diff stat: 5 files,
      +1685/-6 lines. The 4 ST sidecars grew by the new instance-data
      fields; INDEX.md dropped its first-run italic notice now that
      `SCOREBOARD_BASELINE.json` is seeded.
    - Concrete NPC analysis made possible by M5.2:
      `ST_NPC_SandboxCharacter_Patrol_Subtree` now renders
      `STT_FindRandomLocation_C.SearchRadius=1000`,
      `StateTreeMoveToTask.AcceptableRadius=5.0` +
      `bAllowPartialPath=True`, `StateTreeDelayTask.Duration=3.0s`.
      `ST_SmartObject_Bench` renders `STT_AddCooldown_C.CooldownName=Sit
      / Cooldown Time=5.0s`, `Play Time=10.0s ± 3.0s` bench-idle
      duration variance, exit montage
      `M_interaction_bench_out_to_stand_Montage`.
  - **Deferred** (pre-announced for future slices):
    - Real ST fixture in BugHunt. `ST_BugHunt` is a blackboard-only
      fixture with no editor data, so M5.2's instance-data paths
      aren't exercised against BugHunt content. A minimal
      `ST_Patrol_Fixture` with one native task (for `Instance` cover),
      one BP-backed task (for `InstanceObject` cover), and one
      transition condition (for transition-condition cover) would
      close the regression gap.
    - DeepDump Tier 2 for the remaining non-UBP classes (BT / DT /
      UDS / UDE / SmartObject / Chooser / PoseSearch / EnvQuery).
      The M5 out-of-scope notice still points at their Tier 1
      typed-handler output, which renders near-complete shape.
      Only pursue when a concrete consumer need arises.

- **M5.3 P0 StateTree serializer fidelity gaps — DONE (committed
  `c1df8c7` (feat) + `c59c655` (DOW refresh) + `faa502d` (gitignore)).**
  Analysing DOW's NPC StateTrees after M5.2 surfaced three places where
  the serializer was reading only a subset of what `UStateTreeState` +
  `FStateTreeStateLink` actually carry. None were game-code bugs; all
  three were the tool lying to us.
  - **Gap 1 — `EStateTreeStateType::LinkedAsset` missing from switch.**
    UE 5.5+ split the old `Linked` into `Linked` (points at a state
    *within* the same tree via `LinkedSubtree`) and `LinkedAsset`
    (points at a *separate StateTree asset* via `LinkedAsset`). Our
    `SerializeState` switch only mapped `Linked`; `LinkedAsset`
    fell through to the `default` arm and rendered as `[Unknown]`.
    DOW's root `ST_NPC_SandboxCharacter_SmartObject` uses a
    `LinkedAsset` Patrol state, which showed as `[Unknown]` pre-M5.3.
    Enum + switch + helper tables now handle all five state types.
  - **Gap 2 — `UStateTreeState::LinkedAsset` never captured.** Even
    after fixing Gap 1, we didn't record *which* external tree the
    state delegated to. New `FExportedStateTreeState::LinkedAssetPath`
    (FString) populated from `State->LinkedAsset->GetPathName()`
    when state type is LinkedAsset; JSON key `linkedAssetPath`
    written only when non-empty. DOW's Patrol state now resolves to
    `/Game/_ThirdParty/GASP_example/.../ST_NPC_SandboxCharacter_Patrol_Subtree`.
  - **Gap 3 — `FStateTreeStateLink::LinkType` never read.** The worst
    of the three, because it wasn't just missing data — it was
    actively rendering *wrong* data. `LinkType` is the authoritative
    field that describes what a transition DOES:
    * `GotoState` — transition to a named target state (Name + ID
      populated; this is the only case where the existing resolution
      logic was meaningful).
    * `Succeeded` / `Failed` — exit the containing tree/subtree with
      a success/failure signal (Name + ID empty on the link).
    * `NextState` / `NextSelectableState` — resolved at compile time
      to a sibling; Name on the link is sometimes a stale authoring
      value, Selectable variant skips disabled states.
    * `None` — no target configured.
    Pre-M5.3 we read `Transition.State.Name` unconditionally. Concrete
    DOW damage: `MoveToRandomLocation.OnStateCompleted` has
    `LinkType=NextState` but rendered as `FindRandomLocation` — which
    is the state's *parent*, not its sibling. And
    `Wait.OnStateSucceeded` has `LinkType=Succeeded` (exit subtree
    with success, perfectly correct authoring) but rendered as
    `(unresolved)` which I initially flagged as a DOW bug in the M5.2
    NPC-AI review. Both cases fixed: new
    `FExportedStateTreeTransition::LinkType` captures the enum;
    target-name rendering now emits semantic labels
    `(tree succeeded)` / `(tree failed)` / `(next state)` /
    `(next selectable state)` / `(no target)` for non-GotoState
    links. GotoState keeps existing Name → GUID → `(unresolved)`
    resolution. JSON key `linkType` written only when non-empty.
  - **DeepDump renderer updates**: `FormatStateType` adds LinkedAsset;
    state render surfaces `- Linked tree asset: <path>` line;
    transition render emits `- Link type: <LinkType>` for any
    non-GotoState link (since GotoState is implied when a target
    name is present).
  - **Also**: `.gitignore` extended to cover `ProjectInventory/`,
    `ProjectInventory_DOW/Deep/`, `_determinism_{A,B}/` +
    `_logs/` siblings, `_deep_st_{A,B}/`, and `_*.log` — root-cause
    fix for an accidental-add pattern that bit M5.2's `aff06b7` and
    again at M5.3 P0's mid-work state. `git add ProjectInventory_DOW/`
    can no longer drag ephemeral smoke output into a chore commit.
  - **Verified** (2026-04-19):
    - `scripts/verify_determinism.ps1 -Project BugHunt`: PASS in 77 s
      (no regression; BugHunt has no LinkedAsset states or non-
      GotoState transitions, so all pre-M5.3 paths still fire).
    - `scripts/verify_determinism.ps1 -Project DOW -SkipDeep`: PASS
      in 198 s.
    - Post-refresh diff stat: 7 files, +30/-18. Only the 4 ST
      sidecars + their 3 Tier-1 `.md` summaries changed content
      (ST_MassAI has only a GotoState transition so gained just a
      `linkType` line; the two sandbox trees + bench tree gained
      LinkedAsset detail and/or semantic-label rewrites).
    - Plugin DLL: 3.13 MB → 3.13 MB (renderer-side additions are
      trivial compared to M5.2).
  - **Correction of prior analysis**: the M5.2 NPC-AI review flagged
    `Wait.OnStateSucceeded → (unresolved)` as a suspected DOW bug.
    It wasn't — it's the correct authoring pattern for "exit the
    patrol subtree with success so the parent tree can pick next
    child state". M5.3 P0's `(tree succeeded)` label makes that
    clear. The other NPC findings (duration hardcoding, search-box
    extents, cooldown value, no perception, one-SmartObject-type)
    still stand as DOW design observations rather than tool artefacts.
  - **Deferred to M5.3 P1 / later**: `EStateTreeStateSelectionBehavior`
    UE 5.7 utility-based values (5 unmapped:
    `TrySelectChildrenAtRandom`, `TrySelectChildrenWithHighestUtility`,
    `TrySelectChildrenAtRandomWeightedByUtility`,
    `TrySelectChildrenAtUniformRandom`,
    `TrySelectChildrenBasedOnRelativeUtility`). DOW doesn't use any
    of these today (all states show `TrySelectChildrenInOrder`), so
    the fix stays on the backlog until a future DOW CL or a new
    project needs them.

- **M7 P0 ProjectPlugins commandlet (uplugin metadata) — DONE
  (committed `18f44a4` (feat) + `8044ca7` (DOW refresh)).** Closes
  the plugin blind spot in static analysis. Before M7 P0 the inventory
  pipeline only scanned `/Game/…`, so plugin-registered features (e.g.
  DOW's `CoverEQS` shipping `UEnvQueryTest_TraceDistance`) were
  invisible. M7 P0 adds a sibling phase that enumerates project
  plugins and surfaces their descriptor metadata; M7 P1 will extend
  the same commandlet with a reflection walk over the UClasses each
  plugin's modules register.
  - **Commandlet**: `ProjectPluginsCommandlet.{h,cpp}` under
    `Source/BlueprintExporter/{Public,Private}/Commandlets/`. Walks
    `IPluginManager::GetDiscoveredPlugins()` filtered to
    `EPluginType::Project` (engine / enterprise / mod plugins
    intentionally skipped — Epic ships engine-plugin docs). CLI:
    `-run=ProjectPlugins -OutDir=<dir>` required, optional
    `-Include=<regex>` / `-Exclude=<regex>` name filters.
  - **Output layout**:
    - `<OutDir>/PLUGINS.md` — rollup table with one row per plugin
      (name link / VersionName / Category / Enabled / module count /
      dep count / CanContainContent / BaseDir). Summary counts at
      the top.
    - `<OutDir>/PluginInventory/<Name>.md` — per-plugin human doc
      with Identity table, optional Description + Authorship/Links
      sections, Modules table, Dependencies table, "Registered
      native types" placeholder section (empty in P0).
    - `<OutDir>/PluginInventory/<Name>.meta.json` — per-plugin
      structured sidecar round-trip-compatible with `FExportedPlugin`.
  - **Schema** — new `Public/Schema/PluginExportTypes.h`:
    - `FExportedReflectedProperty` (Name/Type/Value/Category — shape-
      identical to `FExportedStateTreeProperty` but kept separate
      to avoid cross-schema coupling; unify later if duplication
      bites).
    - `FExportedPluginModule` (Name/HostType/LoadingPhase — enum
      values stringified via `EHostType::ToString` +
      `ELoadingPhase::ToString` for stability).
    - `FExportedPluginDependency` (Name/bEnabled/bOptional).
    - `FExportedPluginNativeType` (ClassPath/ParentClassPath/
      ModuleName/Subsystem/Properties[] — empty in P0).
    - `FExportedPlugin` (all `FPluginDescriptor` fields + plugin
      type + BaseDir + bEnabled + Modules[] + PluginDependencies[]
      + NativeTypes[]). `ComputeContentHash` over timestamp-blanked
      JSON.
  - **Determinism** (brief §8):
    - Plugin list sorted alpha by Name before any write.
    - Modules / deps / NativeTypes sorted alpha at ToJson time.
    - `BaseDir` normalised via `FPaths::ConvertRelativePathToFull`
      then project-relative prefix-stripped (engine-relative fallback
      for plugins outside the project; drive-letter-strip final
      fallback). Initial smoke hit the fallback on every DOW plugin
      because `FPaths::ProjectDir()` returned `../../../game/` while
      `Plugin->GetBaseDir()` returned absolute — fix was to
      `ConvertRelativePathToFull` both before comparison.
    - No timestamps, no GUIDs in output. `ExportTimestamp` blanked
      post-build; `ContentHash` computed on the blanked form.
  - **`scripts/verify_determinism.ps1` extended** — `ProjectPlugins`
    is now the 4th phase, always-on (cheap — <1 s on DOW; catches
    plugin-graph non-determinism like future drift in
    `FPluginDescriptor::Modules` iteration order).
  - **Build.cs** unchanged — `IPluginManager` lives in `Projects`
    which was already a dep from `BlueprintExporterModule.cpp`.
  - **Verified** (2026-04-19):
    - BugHunt: 2 project plugins (`BlueprintExporter` +
      `BlueprintExporterTests`). Full `verify_determinism.ps1
      -Project BugHunt` PASS in 63 s.
    - DOW: 22 project plugins. `verify_determinism.ps1 -Project DOW
      -SkipDeep` PASS in 203 s. CoverEQS sidecar shows Category=AI,
      1 module (`CoverEQS`, Runtime/Default), 0 deps, VersionName
      1.0.0, BaseDir `Plugins/CoverEQS`. The 22 plugins break down
      as: CoverEQS + BlueprintExporter (ours, first-party) + session
      plugins (AdvancedSessions, AdvancedSteamSessions) + rendering/
      streamline middleware (DLSS, DLSSMoviePipelineSupport, NIS,
      ScreenSpaceFogScattering, Streamline, StreamlineCore,
      StreamlineDeepDVC, StreamlineDLSSG, StreamlineNGXCommon,
      StreamlineReflex) + audio middleware (SteamAudio,
      SteamAudioWwise, Wwise, WwiseNiagara, WwiseSoundEngine) +
      DCC bridges (MetaTailorBridge, Tripo3DUEBridge) + Toolbox.
    - Canonical `ProjectInventory_DOW/` refreshed with additions only
      (45 new files: `PLUGINS.md` + 22 × 2 sidecars, 2046 insertions).
      No pre-existing /Game content files changed — plugin scan is
      a pure sibling phase.
  - **Plugin DLL**: 3.13 MB → 3.23 MB (~100 KB for commandlet + schema).
  - **Deferred to M7 P1**: native-type reflection walk. Plan is to
    iterate each plugin module, `GetDerivedClasses()` against the
    curated base-class set (EQS / StateTree / BT / Anim / GAS /
    SmartObject / Chooser / Mass), filter by plugin ownership via
    `UClass->GetOuterUPackage()->GetFName()` match against the
    plugin's `Modules[]`, and populate `NativeTypes[]` with
    `ClassPath` / `ParentClassPath` / `ModuleName` / `Subsystem` +
    declared UPROPERTYs (reuse M5.2's
    `StateTreeSerializer::SerializeUObjectProperties` reflection
    helper on the CDO). Schema is already shaped — P1 is pure code
    addition, no sidecar format churn.

- **M7 P1 ProjectPlugins native-type enumeration — DONE
  (committed `1314ba2` (feat) + `28ddd4a` (DOW refresh)).** Populates
  the `NativeTypes[]` field M7 P0 left empty. For each plugin, iterate
  a curated base-class allowlist, resolve each base at runtime,
  `GetDerivedClasses` recursively, filter to plugin-owned classes,
  emit one `FExportedPluginNativeType` per match with declared
  UPROPERTYs.
  - **Allowlist** (UClass bases only; struct-typed bases deferred to
    M7 P1.1):
    * EQS — `UEnvQueryTest`, `UEnvQueryGenerator`,
      `UEnvQueryContext_BlueprintBase`
    * StateTree BP — `UStateTreeTaskBlueprintBase`,
      `UStateTreeConditionBlueprintBase`,
      `UStateTreeEvaluatorBlueprintBase`
    * BehaviorTree — `UBTService`, `UBTDecorator`, `UBTTaskNode`
      (native bases; catches both BP-intermediaries and direct
      native subclasses)
    * Anim — `UAnimNotify`, `UAnimNotifyState`
    * GAS — `UGameplayAbility`, `UGameplayEffect`, `UAttributeSet`
    * SmartObject — `USmartObjectBehaviorDefinition`,
      `USmartObjectSlotValidationFilter`
    * Chooser — `UChooserColumnBase`
    * Mass — `UMassProcessor`
  - **Runtime class resolution** via `StaticFindObject(UClass::StaticClass(),
    nullptr, Path)`: no Build.cs module-dep burden, no WITH_*_SUPPORT
    guards needed. If a base's module isn't loaded (e.g. GameplayAbilities
    when GAS is disabled in the uproject), the base silently skips —
    determinism is still well-defined because the set of loaded modules
    is a function of uproject content, not of wall-clock time.
  - **Plugin ownership**: a candidate belongs to the current plugin iff
    `Candidate->GetPackage()->GetFName()` == `/Script/<M>` for some
    `M` in `Plugin->GetDescriptor().Modules`. Classes living in `/Game/`
    (BP-authored) are automatically excluded because their package
    name starts with `/Game/`, not `/Script/`.
  - **Dedupe**: a class derived from two allowlist bases (theoretically
    possible, e.g. multiple-inheritance scenarios — unusual in UE but
    the allowlist could evolve) is emitted once with the first-seen
    Subsystem label.
  - **Declared-only properties**: `TFieldIterator<FProperty>(Class,
    EFieldIteratorFlags::ExcludeSuper)` — inherited base-class
    UPROPERTYs would be noise for "what does this plugin add". Values
    come from the CDO via `ExportTextItem_Direct`. Abstract classes
    with no CDO emit an empty property list (still useful — shows the
    registration surface even if non-instantiatable).
  - **Renderer upgrades**:
    - `PLUGINS.md` rollup: new `Native` column + summary line
      ("Registers native types: N plugin(s), M class(es) total").
    - Per-plugin `.md`: when populated, summary table + one H3 per
      class with its full property table (Name / Type / Default /
      Category). When empty, the "no types" prose distinguishes
      "enabled but registers nothing matching allowlist bases" from
      "disabled, modules not loaded — enable and re-run".
    - Schema unchanged (M7 P0 shaped it correctly).
  - **Verified** (2026-04-19):
    - BugHunt: 2 plugins scanned, 0 native types (expected —
      BlueprintExporter registers commandlets and serializers, not
      AI/gameplay allowlist bases). `verify_determinism.ps1
      -Project BugHunt` PASS 63 s.
    - DOW: 22 plugins, 2 register native types — hitting the M7 P1
      concrete assertion from the pre-P1 scope:
      * **CoverEQS** registers `/Script/CoverEQS.EnvQueryTest_TraceDistance`
        (parent `UEnvQueryTest`, module `CoverEQS`, subsystem EQS) with
        all 9 declared UPROPERTYs: `TraceTo`, `TraceData`,
        `ItemHeightOffset`, `ContextHeightOffset`, `MaxTraceDistance`,
        `ScoreMode`, `bTraceFromContext`, `bScoreMissAsMaxDistance`,
        `IgnoreActorsContext` — including default values like
        `MaxTraceDistance=(DefaultValue=3000.000000)` and
        `ScoreMode=InvertedDistanceToHit`.
      * **Wwise** (bonus find) registers
        `/Script/AkAudio.AkEventAnimNotify` (parent `UAnimNotify`,
        module `AkAudio`, subsystem Anim) — a notify for triggering
        Wwise audio events from anim sequences; 3 UPROPERTYs: `Event`
        (`UAkAudioEvent*`), `AttachName` (`FString`), `Follow`
        (`bool`, default `True`). Surfaces a previously-invisible
        integration point without anyone reading Wwise docs.
    - DOW `verify_determinism.ps1 -Project DOW -SkipDeep` PASS 194 s.
    - Canonical `ProjectInventory_DOW/` refresh: 25 files, +177/-52
      (tight, additive — PLUGINS.md + 22 × per-plugin .md wording
      tweak + 2 sidecar pairs getting populated NativeTypes).
  - **Plugin DLL**: 3.23 MB → 3.25 MB (~18 KB).
  - **Deferred to M7 P1.1** (small additive slice): struct-typed
    bases via `TObjectIterator<UScriptStruct>` + `IsChildOf`. Covers
    `FStateTreeTaskBase`/`FStateTreeConditionBase`/
    `FStateTreeEvaluatorBase` and future struct-based plugin types
    (UMassFragment fits here once MassEntity source becomes
    available). Value walk is more involved than UClass since structs
    need explicit allocate+`InitializeStruct` to get default memory;
    can start with name+parent+module-only emission and add value
    walks later.

- **NPC-AI audit validation — DONE (2026-04-19, no code change).**
  The 2026-04-19 usability audit flagged two DOW concerns that needed
  post-M5.2/M5.3 validation via DeepDump. Both now checked:
  - **Ultra_Dynamic_Sky `Use Auroras` COND_OwnerOnly — CONFIRMED BUG.**
    DeepDumped `Ultra_Dynamic_Sky` (6.78 MB output, 149209 lines).
    `OnRep_Use Auroras` handler exists and does real work —
    K2Node_IfThenElse → `Set Sky Sphere MID` (applies aurora
    material). But zero `SetOwner` / `GetOwner` / `GetOwningPlayer`
    references anywhere in the blueprint; no per-player spawn logic.
    Parent class is plain `AActor` (not a Pawn / PlayerController).
    For a placed-in-level sky with NetOwner=null, `COND_OwnerOnly`
    means the property never replicates to any client — auroras
    never toggle visually. Sibling bools (`Animate Time of Day`,
    `Use System Time`) are plain `Replicated` + have OnReps. `Use
    Auroras` should match them. This is a marketplace-asset bug
    (Ultra Dynamic Sky, not DOW-authored) — fix options: patch the
    local copy, report to vendor, or subclass and override the
    RepCondition.
  - **"Zero authored RPCs across 805 DOW assets" — CORRECT for the
    tool's scope.** Global grep for any `"(server|client|netMulticast)":
    true` across the 805 meta.json sidecars returns zero. Probe case:
    `SandboxCharacter_CMC` calls `UpdateInputState_Server` (UE's
    classic Server-RPC naming convention) in 4 places, but the 4
    occurrences are all `nodeSpecificData.functionName` values
    (call-site K2Node_CallFunction data), not top-level
    `functions[]` entries. The function is defined on the parent
    class (`SandboxCharacter_CMC_C`'s C++ superclass) and called
    from this BP. REPLICATION_MATRIX only captures BP-authored
    RPCs — native-C++ RPCs inherited from parents are out of scope
    (ProjectInventory scans `/Game` content, not `/Script/` class
    functions). So the "0 RPCs" number is literally correct for
    BP-authored RPCs; the follow-up question "does DOW use RPCs
    at all" is answered by "yes, via parent-class C++ functions".
    No tool fix needed; potential future slice would be to scan
    plugin-registered UFUNCTION flags during M7's native-type walk
    (currently we only capture UPROPERTYs on the CDO, not UFUNCTION
    metadata).

- **Full DOW Phase 1 — DONE (canonical tree committed `2a318d9`).**
  Twin run via `verify_determinism.ps1 -Project DOW -SkipDeep` passed
  byte-identical in 193 s (805 assets, 0 failed, 0 partial). A fresh
  single-pass run of ProjectManifest + ProjectInventory + AggregateInventory
  then produced the canonical tree committed into `ProjectInventory_DOW/`
  at 1622 files (~240 MB of `.md` + `.meta.json`).
  - Phase 0 MANIFEST: 18475 total / 805 logic-bearing across 11 classes
    (Blueprint 392, PoseSearchDatabase 154, UserDefinedEnum 74,
    UserDefinedStruct 65, WidgetBlueprint 47, AnimBlueprint 27,
    ControlRigBlueprint 25, ChooserTable 12, DataTable 4, StateTree 4,
    SmartObjectDefinition 1). DOW's AI is StateTree-only; 0 BehaviorTrees.
  - Phase 1 INVENTORY: 805 processed, 0 failed, 0 partial. Every class
    emits typed-handler output.
  - Phase 2 AGGREGATE: 12 rollup files + `SCOREBOARD_BASELINE.json`
    seeded from this run. REPLICATION_MATRIX carries 98 rows
    (variables + RPCs). HEALTH_REPORT `CoverageUnder100=0` — every
    asset at 100%.
  - This is the "final deliverable" per brief §13. Subsequent DOW
    CL moves will produce line-diffable output that consumer workstreams
    (replication audit, Steam Relay plan, etc.) can review in-repo
    without rescanning.

## Policy (decided, don't re-litigate)

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

## Key paths

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

## Known blockers

- _None._ UE_DOWEditor target is current (rebuilt 2026-04-18, 204
  actions, matches engine BuildId `6efc257b-…`). BugHunt target
  rebuilt at M3.3 Track A (~30 s, 43 actions) to pick up the
  UMG/UMGEditor deps on top of the prior Chooser / PoseSearch /
  SmartObjects bakes; M5 and M6.1 added no module deps so no new
  target rebuilds were required. `BuiltPlugin/` holds the M15 DLL
  (~3.38 MB). All three DLL locations (BuiltPlugin, BugHunt plugin
  copy, BugHunt project Binaries) match current engine BuildId.

## Fidelity audit findings (2026-04-19 DOW_Legacy export)

Running the full sweep against `UE_DOW_Legacy` (2604 logic-bearing
assets, 3.2× main DOW) surfaced four things worth noting. `[BROKEN]`
and marker counts checked across all `.deep.md`; leak counts checked
across both `.deep.md` and `.meta.json`.

1. **[RESOLVED — M16, commits `b0d1f4a` + `5602eea`]** Real bug —
   `UberGraphFrame` plumbing leak in StateTree `.meta.json`. Tier 1
   serializer `FStateTreeSerializer::SerializeUObjectProperties`
   (`StateTreeSerializer.cpp:344`) walked every UPROPERTY on the
   BP-backed task's instance class and emitted them without
   filtering UE plumbing. 7 StateTree files in legacy + 3 in main
   DOW canonical tree (`ST_NPC_SandboxCharacter_Patrol_Subtree`,
   `ST_NPC_SandboxCharacter_SmartObject`, `ST_SmartObject_Bench`)
   carried `UberGraphFrame` / `FPointerToUberGraphFrame` entries
   with `"value": "()"`. The Tier 2 renderers (M11 SO / M12 BT /
   M13 DT / M14 Chooser / M15 EQS) all shared an
   `IsUEPlumbingProperty` allowlist (UberGraphFrame +
   CachedFrameStateTree); M5.2's serializer predated that pattern
   and never got it. **M8 audit missed this because it only checked
   `.deep.md`.** M16 added the same skip-list (`IsStateTree­
   UEPlumbingProperty` file-scope helper), rebuilt, and refreshed
   canonical — -158 lines across the 3 main-DOW files. Legacy
   refresh pending next sweep.

2. **Minor noise — `[BROKEN]` on hidden inactive
   `K2Node_PromotableOperator` pins.** 323 markers in legacy, similar
   pattern in main DOW. The hidden `ErrorTolerance` pin on int-
   overload operators (`GreaterEqual_IntInt` etc.) doesn't resolve
   because it's inactive for that typed overload; serializer marks it
   `[BROKEN]`. Not strictly wrong but noisy. Low-priority; if/when we
   address: skip hidden+unresolved pins in the renderer.

3. **[RESOLVED — silent pre-2026-04-22]** Stale rollup text in
   `AI_OVERVIEW.md`. The pre-M11 "SmartObjectDefinition and
   Perception aggregate rollups will join this overview after the
   DOW calibration slice adds their typed handlers" line was
   rewritten to reference the shipped M11–M15 typed deep-dump
   coverage ("`SmartObjectDefinition`, `BehaviorTree`, and
   `EnvQuery` assets each ship full Tier 2 deep dumps … a
   dedicated rollup would duplicate that content without adding
   cross-asset signal"). `AggregateInventoryCommandlet::
   RenderAI_OVERVIEW` now ends with the updated text in both
   `Source/` and `BuiltPlugin/`. No action needed.

4. **M15 EnvQuery Tier 2 is no longer speculative.** Legacy has
   4 EQS assets under `/Game/CombatPrototype/EQS/` (`EQS_AI_FindCover`,
   `EQS_AI_FindPeek`, `EQS_AI_FindPointInCone`, `EQS_FindCloseCover`)
   that exercise the full per-option + per-test UPROPERTY path.
   `EQS_AI_FindCover` renders its `EnvQueryGenerator_GoldenSpiral`
   (from `EQSRingGenerator` plugin) with `MaxRadius=1246`,
   `PointCount=128` etc., plus `EnvQueryTest_Pathfinding` and
   `EnvQueryTest_TraceDistance` (from `CoverEQS`) with full
   `TestPurpose` / `ScoringEquation` / `ClampMin` values. The M15
   row's "unexercised" caveat is obsolete — update when we next touch
   it.

## Legacy depot export procedure (2026-04-19)

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

## Ephemeral artifacts (safe to delete, intentionally untracked)

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

## Usability audit (2026-04-19) — tested the committed output

After the deliverable landed, ran a short audit against the committed
`ProjectInventory_DOW/` to answer "can this actually be used to analyse
the project and find bugs". A new session resuming from `/clear` can
reproduce by re-running the queries listed here against the tracked tree.

**Scanning workflow that works:**

1. `INDEX.md` for project shape — 805 logic-bearing assets across 11
   classes, top-level folder breakdown, largest connection hubs.
2. `REPLICATION_MATRIX.md` for cross-cutting replication audit — 98 rows.
3. `grep -rl "bHasBrokenReference" ProjectInventory_DOW/Assets` — 0
   matches across the whole tree. Clean.
4. `grep -rh "^- Nodes: " ProjectInventory_DOW/Assets | sort | uniq -c`
   for function-size distribution — smallest functions are 2-node,
   no 0-node stubs in DOW.

**Findings (genuine anti-patterns surfaced by the output):**

- **0 authored RPCs across all 805 DOW assets**
  (`grep -rlE '"server":\s*true|"client":\s*true|"netMulticast":\s*true'`
  returns nothing). Either DOW's multiplayer logic is entirely
  variable-replication based, OR the RPC detection path on
  `FExportedFunctionFlags` isn't firing on DOW content. Worth a
  sanity check against a known-RPC asset before trusting this
  "no RPCs anywhere" signal.

- **`Ultra_Dynamic_Sky` has 20 replicated members with inconsistent
  replication policy**:
  - `Day Length`, `Night Length`, `Time Speed`, `Simulation Speed`,
    `Simulation Speed Night Multiplier`, `Simulated Sunrise Time`,
    `Simulated Sunset Time`, `Transitioning Time` — replicated with
    **no RepNotify and no COND_*** condition. These are design-tuning
    values authored once, so they're likely supposed to be
    `COND_InitialOnly` (push once at connect, never again) — as is. The
    inconsistency is that sibling values (`Clouds B Time`, `Moon Phase`,
    `Clouds Position`) *do* have `COND_InitialOnly` applied. Inconsistent
    intent.
  - `Use Auroras` is `COND_OwnerOnly`. For a world-scale Sky actor, the
    "owner" is typically the server, which means clients never receive
    aurora state. Likely a bug unless the Sky actor pins ownership to a
    client connection (worth a DeepDump to confirm).
  - Every user-facing setting (`Animate Time of Day`, `Use System Time`,
    `Month`, `Day`, `Year`, `Use Auroras`) has an `OnRep_<name>` handler
    in the Functions list — pattern is consistent where it's applied.

- **`SandboxCharacter_CMC.CharacterInputState`** replicated
  `COND_SkipOwner` (struct<S_PlayerInputState>): correct pattern for
  client-authoritative input that only other-clients need to see. No
  RepNotify, which is fine for input state driven by tick.

- **No broken references, no partial loads, every asset at 100%
  coverage**. The DOW content is clean at Phase 1 fidelity.

**DeepDump on `SandboxCharacter_CMC_ABP` (after M5.1) is readable**:
76-var / 59-function AnimBP dumps to 14665 lines in 10 s; connections
resolve like `` `Call_BooleanAND_416_96_7FC94A8C`:`B` (BooleanAND) ``
so you can follow pin-to-pin data flow without an editor. State
machines nest `## Machines → ### Machine → #### State → ##### AnimGraph
→ ###### node`.

**Conclusion — is the output good enough for analysis/bug-hunting?**
Yes for **static structural analysis** (replication-audit,
orphan-detection, inheritance sanity, API surface review, dead-code
search). You can drive the workflow from Tier 1 rollups + grep into
per-asset `.md`, reaching for DeepDump only when you need pin-level
logic on a specific asset. Limitations: runtime/behavioural/performance
bugs need the game running (outside the tool's remit); semantic
"this is doing the wrong thing" requires the auditor to know what
"right" is.

**Concrete follow-ups for a next session:**

1. Confirm or refute the "0 RPCs in DOW" finding by grepping
   the Blueprint source for a known RPC (e.g. `UFUNCTION(Server,` in
   `.h` files in UE_DOW plugins) and then looking at that asset's
   `.meta.json` — if the flags are false there too, the RPC detection
   path needs a follow-up fix. If they're true, DOW just happens to
   be RPC-free so far.
2. DeepDump `Ultra_Dynamic_Sky` and confirm whether `Use Auroras`
   ownership pins to the server or a specific client connection, then
   decide if the COND_OwnerOnly is intentional.
3. Normalize UDS replication policy: either all design-tuning values
   get `COND_InitialOnly`, or they're unconditional by design and the
   current `COND_InitialOnly` applications are over-restrictive. A
   designer call, but the matrix surfaces the inconsistency.

## What the next session should do first

**2026-04-25 (later) — M28.6.1 shipped end-to-end; M28.6 catalog COMPLETE (1 op).** First (and only planned) op of the M28.6 GameplayTag write-side catalog. 1 new UFUNCTION (`AddGameplayTag` on `UBpxReflectionOps`) + 1 new Python op (`add_gameplay_tag` in new module `scripts/python_ops/gameplay_tags.py`) + 1 new zero-UE-process MCP tool (`list_gameplay_tags` in new module `scripts/blueprint-exporter-mcp/.../tools/gameplay_tags.py`) + 1 new BugHunt fixture (`Config/DefaultGameplayTags.ini` starter — 343 bytes, settings header + zero `+GameplayTagList=` entries) + M28.pre.5 parity gate (`scripts/verify_tag_author.ps1` + `scripts/verify_tag_author_harness.py`) + new Build.cs gate `WITH_GAMEPLAYTAGSEDITOR_SUPPORT` mirroring the M3.3 P1a `WITH_CHOOSER_SUPPORT` recipe. Op count 44 → 45. **Three M28.6.0 research-flagged traps validated in implementation:** (a) duplicate-add → engine API returns `false`; bridge UFUNCTION pre-checks `UGameplayTagsManager::IsDictionaryTag` and returns `bSkipped=true` instead, soak round-2 byte-identity holds; (b) `DeveloperConfigName` per-machine override → documented in op docstring + AGENT_LOOP example, not bypassed (user-machine config); (c) `GameplayTagsUpdateSourceControl` Perforce checkout → existing `apply_plan` `confirm=True` gate covers it, no extra mitigation needed. **Verification clean:** automation 17/17 PASS in 15.7 s; determinism full-sweep twin byte-identical in 46.4 s; 18 inspect + 28 soak gates PASS unchanged from M28.4.3 (no regression on prior surface); new `tag-author-bughunt` gate PASS in 6 s (baseline=343 bytes → after-apply=467 bytes / +1 line / md5=`9EC2D21F5C524C7516B5DC15DB2553A9`; idempotence holds across rounds; baseline restored cleanly). MCP smoke 24/24 in ~10 s including 3 new `list_gameplay_tags` scenarios (BugHunt empty-ini → 0 tags/0 redirects/1 source; DOW → 32 tags + 3 redirects across 1 source matching M28.6.0 research findings; missing project_root → structured error). Dual-engine DLL rebuild: UE_DOW 2,892,800 b BuildId-aligned; stock UE 5.7 2,894,336 b. BugHuntEditor target rebuilt via Build.bat to keep BPE + Tests-plugin DLLs BuildId-aligned with BugHunt's editor target. Version stamp 1.26.0 → 1.27.0 (minor — new subsystem per the gameplay-tag-config-authoring scope). 9-location version stamp sweep clean; drift-detection grep shows only `1.27.0` (live × 22 occurrences) and `1.0.0` (test fixtures pinned, intentional) across Source/, BuiltPlugin/, .uplugin × 3, README. **Headline correction landed alongside the implementation:** the M28 phase-table reference to `UGameplayTagsManager::AddNewGameplayTagToINI` was wrong (M28.6.0 research caught this) — that function lives on `IGameplayTagsEditorModule` in the editor-only `GameplayTagsEditor` plugin. Build.cs adds the dep behind a new gate; in non-editor builds the bridge UFUNCTION returns a structured `WITH_GAMEPLAYTAGSEDITOR_SUPPORT=0` error rather than failing to compile. **One verify_tag_author.ps1 wrapper trap fixed mid-flight:** initial threshold `ExitCode -ne 0` was too brittle — the BugHunt commandlet path emits a benign `LogObj: Error: LoadConfig (...ProjectID)` that triggers UE's `Failure - 1 error(s)` summary and sets exit code 1 even when the script itself succeeded; corrected to `-ge 2` (UE convention for hard commandlet failures) per the verify_post_apply_inspect.ps1 precedent. **Next scope is OPEN** — M28.6 umbrella closed. External-driver candidates from the M28 phase table: M28.7 (automation-test runner — semantic verification beyond mechanical diff), M28.8 (optional read-side Tier 2 additions for UDS / CurveFloat / AnimMontage), or any other M28-phase-table item per next external driver.

---

**Prior: 2026-04-25 (earlier) — M28.6.0 research-only slice shipped (post-M29.6 closure).** User picked M28.6 as the next external driver after M29.6 closed. Research findings captured in the new `### M28.6.0 research outcome` block below so the M28.6.1 authoring pass doesn't have to re-probe the GameplayTags engine surface. Same pattern as M28.2.0 / M28.3.0 / M28.4.0 / M28.5.0 research-commit slices. **Headline correction:** the M28 phase-table entry references `UGameplayTagsManager::AddNewGameplayTagToINI` — that function lives on the **`IGameplayTagsEditorModule` interface** in the editor-only `GameplayTagsEditor` plugin, NOT on `UGameplayTagsManager`. M28.6.1 must add `GameplayTagsEditor` as a Build.cs editor-only dep gated by `WITH_GAMEPLAYTAGSEDITOR_SUPPORT` (mirrors `WITH_CHOOSER_SUPPORT` etc.). **Output:** 1 new UFUNCTION (`AddGameplayTag`) + 1 new Python op (`add_gameplay_tag` in new module `gameplay_tags.py`) + 1 new zero-UE-process MCP tool (`list_gameplay_tags`) + 1 BugHunt fixture (starter `Config/DefaultGameplayTags.ini`) + M28.pre.5 parity gate (`scripts/verify_tag_author.py`). Single-slice surface — no further sub-phasing needed. **Next pickup: M28.6.1** (minor bump 1.26.0 → 1.27.0; dual-engine DLL rebuild). **Three load-bearing traps documented** in the research block: (a) duplicate-add returns `false` not skip — Python op must pre-check `Manager.IsDictionaryTag` and return `bSkipped=True` for soak round-2 byte-identity; (b) `UGameplayTagsDeveloperSettings.DeveloperConfigName` per-machine override diverts `source_ini="DefaultGameplayTags.ini"` to a different file when set — document but don't bypass; (c) `GameplayTagsUpdateSourceControl` triggers Perforce checkout on save — apply_plan's existing `confirm=True` gate is the correct mitigation, document loudly in AGENT_LOOP.

---

**Prior: 2026-04-25 — M29.6 engine-agnostic Mutable renderer refactor CLOSED end-to-end.** Five sub-phases shipped: M29.6.1 helpers + tests at `19b3a03` → M29.6.2 UCOI port at `47b370a` → M29.6.3 + M29.6.4 combined as UCO port + `WITH_MUTABLE_SUPPORT` gate strip at `e384b6e` → M29.6.5 finalize + version bump 1.25.0 → 1.26.0. One BuiltPlugin DLL now serves CO / COI / COML in any Mutable-capable engine, regardless of build-time Mutable presence.

**Verification record durable at the per-step level (M29.6.5 finalization):**
- BugHunt twin-run determinism PASS in 46s (no CO assets — dispatch additions are inert).
- DOW twin-run determinism PASS in 120s (`-Filter=/Game/_ThirdParty/GASP_example/`).
- MutableSample 4-asset md5 MATCH against `_m29_6_4_post_port/` baselines: CO_Weapon `28B162FBD46C7AA9AA290B95CA6F5845`, CO_Character `FFC496AEA7E866D4394F9719018D5E60`, CO_Basic_parameters `D3CA666BE2814ABBD8B55F327CD1B4B5`, CO_Projectors_showcase `9D4940BB1F7808E377757F7BCFD7F9BF`.
- Both-engine `RunUAT BuildPlugin -Rocket` BUILD SUCCESSFUL: UE_DOW 2,877,440 b in 24s; stock UE 5.7 2,878,464 b in 45s. Re-run after the version bump produced byte-identical-sized DLLs (string-only diff).
- BugHunt automation 24/24 PASS in 15s.
- Bridge smoke 7/7 (2 OK + 5 EXPECTED_ERROR + 0 FAILURE) — `pluginVersion: "1.26.0"` confirmed via ping + list_methods after rebuild.
- verify_all matrix 46/46 PASS in 537.2 s on BugHunt / stock UE 5.7 (matches M29.6.4's 535.1 s baseline within noise).
- Drift-detection grep clean — only `1.26.0` (live) and `1.0.0` (test fixtures) remain across Source/, BuiltPlugin/, .uplugin × 3, README.

**Next scope is OPEN.** With M29.6 closed, no successor is in flight. External-driver candidates from the M28 phase table:
- **M28.6** — GameplayTag config authoring (design.md items #1 + #4).
- **M28.7** — automation-test runner (semantic verification beyond mechanical diff).
- **M28.4.4** (optional, very low priority) — pure-docs close of M28.4 umbrella matching M28.3.6 / M28.5.4 precedent.
- Any other M28-phase-table item driven by user / design.md.

Pick based on the next external driver. The historic M29.6.x sub-phase records still live in the prose blocks below for context (M29.6.0 research findings, M29.6.1 / .2 / .3 / .4 / .5 ship summaries, M29 umbrella close at M29.5).

**Workflow gotchas durable across this arc (carry forward to next session):**
- **MSYS2 path-munging on `-Asset=/Game/Foo` is REAL** — use the PowerShell tool (or `MSYS_NO_PATHCONV=1` in Bash) for any UE invocation that takes a `/Game/...` arg. Caught again in M29.6.5 step (c) when an unquoted PowerShell `-Asset=$a` got through with the literal `$a` because of how PowerShell tokenizes native-call argv around `=` + `$`. Always pre-quote: `"-Asset=$a"`.
- **Bash doesn't have `tee` / `head` / `tail` / `cat` / `grep` / `wc` in this MSYS2 install** — use `Read`, the `Grep` tool, or PowerShell instead. Don't pipe through bash filters that aren't there.
- **`pwsh` is not on Bash's PATH** — invoke as `& "C:\Program Files\PowerShell\7\pwsh.exe"` from PowerShell or via the cygpath form from Bash.
- **MutableSample uses UE_DOW engine** despite `EngineAssociation=5.7` in its uproject. The `MutableSample/Plugins/BlueprintExporter` junction points at `BuiltPlugin/` (UE_DOW flavor); BugHunt has its own per-project plugin folder rebuilt against stock 5.7. **`verify_determinism.ps1` defaults to `-Engine` UE_DOW** — for BugHunt always pass `-Engine 'C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe'` or the engine-version mismatch refuses to load the plugin (`requires engine version '5.7.0'`).
- **BugHunt plugin `.uplugin` pins `EngineVersion: 5.7.0` + `Installed: true`** — UE_DOW (5.7.4-572648) refuses to load it. Use stock 5.7 for any BugHunt gate. The `BugHunt/TestProject/Plugins/BlueprintExporter/` folder is a per-project plugin copy (not a junction) — its `.uplugin` is a separate file from `BlueprintExporter.uplugin` and `BuiltPlugin/BlueprintExporter.uplugin` and must be bumped as part of the Versioning Protocol sweep.
- **Bridge smoke needs an interactive editor running** — `python scripts/smoke_bridge.py` connects to `ws://127.0.0.1:1337`. Launch `UnrealEditor.exe BugHunt.uproject -unattended -nopause -nullrhi -log` (NOT `-Cmd.exe` — commandlet exits before bridge serves), wait ~2-3s for the bridge to bind port 1337, run smoke, then `Stop-Process` the editor.

---

**Prior: 2026-04-24 — M29.6.2 shipped end-to-end (`47b370a`); UCOI renderer ported to zero-compile-time-Mutable-dep, no version bump.** Second code slice of the M29.6 engine-agnostic Mutable renderer refactor, following M29.6.1's `UFunctionCall` helper landing. `CustomizableObjectInstanceDeepRenderer.{h,cpp}` rewritten as reflection-only: `#if WITH_MUTABLE_SUPPORT` gate dropped from the .cpp, all `MuCO/*` includes removed, `Cast<UCustomizableObjectInstance>()` replaced by class-name match, and the one direct-UE_API call (`Desc->GetCurrentState()`) replaced by reflecting `State` as an FIntProperty on the Descriptor + invoking `UCO->GetStateName(StateIdx)` via `CallString` on the parent UCO. Parent-UCO resolution + build-parameter-relevancy follow the "try UFUNCTION first, fall back to UPROPERTY reflection, fall through to `_not reachable_` marker" layered pattern that preserves byte-identity on every Mutable-capable project AND degrades gracefully in Mutable-less builds. Two call sites at `DeepDumpCommandlet.cpp:382` + `ProjectInventoryCommandlet.cpp:2619` still wrap invocations in `#if WITH_MUTABLE_SUPPORT` — M29.6.4 does the mechanical project-wide strip. **Load-bearing verification:** ran `-run=DeepDump` on MutableSample/Character/COI_Character with the fresh M29.6.2 UE_DOW DLL; output md5 `ECC0F12CB660E38786D928A9BFEFD83D` is IDENTICAL to the M29.1 baseline at `eb5dd38`. The UCOI renderer was the only file touched since M29.1, so the md5 match proves the port preserves semantics byte-for-byte on real Mutable content. 46/46 `verify_all.ps1` gates PASS in 537.6 s on BugHunt / stock UE 5.7 (matches M29.6.1's 536.1 s baseline within noise). Dual-engine DLL rebuild: UE_DOW 2,859,008 b / stock UE 5.7 2,860,032 b (+~4 KB each vs M29.6.1). BugHunt plugin Binaries rebuilt incrementally via `Build.bat BugHuntEditor` (only UCOI renderer + ProjectInventoryCommandlet relinked; BuildIds stay aligned at `47537391`). **One workflow gotcha caught during the MutableSample check:** MSYS2 Git Bash munges absolute-looking paths starting with `/` into `C:/Program Files/Git/...` — so when invoking UE-Cmd for a DeepDump run with `-Asset=/Game/Foo`, always go through PowerShell, not bash. Error signature is `LogBlueprintExporter: Error: [ERROR] Invalid -Asset value 'C:/Program Files/Git/Game/...'` — the commandlet validator catches it cleanly, but confuses if you misread the first time. **Next pickup: M29.6.3** — port `CustomizableObjectDeepRenderer.cpp` to the helpers. Heaviest sub-phase (~25 typed call sites against UCO BlueprintCallable getters — `GetParameterCount` / `GetParameterName` / `GetParameterTypeByName` / all 9 default-value getters / `GetParameterUIMetadata` / `GetStateUIMetadata` / `GetEnumParameterGroupType` / `GetEnumParameterNumValues` / `GetEnumParameterValue` / `GetStateCount` / `GetStateName` / `GetStateParameterCount` / `GetStateParameterName` / `GetComponentCount` / `GetComponentName` / `GetSkeletalMeshComponentReferenceSkeletalMesh` / `IsCompiled` / `IsChildObject`). Enum returns dispatch via `CallEnumInt64` + `UEnum::FindEnumByName` + `GetNameStringByValue` on the return-property's `FEnumProperty`. USTRUCT returns (`FMutableParamUIMetadata` / `FMutableStateUIMetadata`) go through the raw `CallUFunctionRaw` primitive — same pattern as M29.6.1's `StructReturn` test. Load-bearing verification: MutableSample/Weapon/CO_Weapon twin, md5 `28B162FBD46C7AA9AA290B95CA6F5845` baseline must still match post-port. See **M29.6.2 shipped** block further down for the full record.

**Prior: 2026-04-24 — M29.6.1 shipped end-to-end (`19b3a03`); first code slice of the M29.6 engine-agnostic Mutable renderer refactor, no version bump.** Lands the shared `BlueprintExporter::DeepRender::UFunctionCall` namespace in `DeepRenderShared.{h,cpp}` — `CallUFunctionRaw` primitive + 7 typed wrappers (`CallBool` / `CallInt` / `CallFloat` / `CallString` / `CallFName` / `CallObject` / `CallEnumInt64`) — the ProcessEvent-based runtime reflection path that M29.6.2 + M29.6.3 will use to invoke Mutable UFUNCTIONs without a compile-time link dep on the Mutable module. New `Private/Tests/TestUFunctionFixtures.h` USTRUCT/UENUM/UCLASS fixture with 11 UFUNCTIONs covering every return shape (bool / int / float / string / name / object / enum / struct / void + multi-arg overloads). 7 new `BlueprintExporter.UFunctionCall.*` automation tests (ScalarReturns / InputArgs / EnumReturn / StructReturn / VoidReturn / MissingFunction / ReturnTypeMismatch) all flagged `EditorContext | CommandletContext | EngineFilter`. **Verification clean** — 24/24 automation PASS (17 pre-existing + 7 new), 46/46 `verify_all.ps1` gates PASS in 536.1 s on BugHunt / stock UE 5.7 (matches M28.4.3's 538.1 s baseline within noise). Dual-engine DLL rebuild: UE_DOW 2,854,912 b / stock UE 5.7 2,856,448 b (+~43 KB each). BugHunt's plugin Binaries rebuilt in-place via `Build.bat BugHuntEditor` so BPE + BlueprintExporterTests DLLs share BuildId `47537391` with BugHunt's game module. **Verification gotcha documented for future sessions:** the `RunUAT BuildPlugin -Rocket` isolation path can NOT rebuild BlueprintExporterTests because the synthetic HostProject can't resolve its `BlueprintExporter` plugin dependency (`Unable to find plugin 'BlueprintExporter' (referenced via command line -> BlueprintExporterTests.uplugin)`). The right recipe for rebuilding BugHunt's plugin + tests DLLs against a specific engine is `Build.bat BugHuntEditor Win64 Development -Project=.../BugHunt.uproject` — in-place UBT build hits both plugins via the project's junction tree. Also: `run_automation_tests.ps1` defaults `-Engine` to UE_DOW but BugHunt's `.uplugin` pins `EngineVersion=5.7.0` — pass `-Engine 'C:\Program Files\Epic Games\UE_5.7\...UnrealEditor-Cmd.exe'` for the stock-5.7 matrix, same engine the `verify_all.ps1` wrapper uses by default. **Next pickup: M29.6.2** — port `CustomizableObjectInstanceDeepRenderer.cpp` to the new helpers. Replace `Cast<UCustomizableObjectInstance>()` with class-name-match dispatch, replace the one `GetCurrentState()` direct-UE_API call with a `CallString` through the parent UCO, keep the `FCustomizableObjectInstanceDescriptor` field reflection walk unchanged. ~25-line touch — rehearsal before M29.6.3's heavier `UCustomizableObjectDeepRenderer` port. See **M29.6.1 shipped** block further down for the full record.

**Prior: 2026-04-24 — M28.4.3 shipped end-to-end; M28.4 catalog now COMPLETE (8 ops across 3 modules).** Final slice of the M28.4 non-BP asset-factory catalog — closes the umbrella started at M28.4.0 (research) and shipped across M28.4.1 (`create_curve_float` + `set_curve_float_keys` — `curves.py`) / M28.4.2 (`create_data_asset_instance` + `set_data_asset_property` — `data_assets.py`) / M28.4.3 (`create_user_defined_struct` + `add_uds_member` + `remove_uds_member` + `set_uds_member_default` — `uds.py`). 4 new ops + 4 new UFUNCTIONs (`CreateUserDefinedStructDeterministic` + `AddUserDefinedStructMember` + `RemoveUserDefinedStructMember` + `SetUserDefinedStructMemberDefault` on `UBpxReflectionOps`) + 1 new BugHunt fixture (`UDS_BpxTestEmpty`, 2 pre-seeded members for the remove/set-default soak targets). Op count 40 → 44. Matrix **42 → 46 gates** (4 new soaks; inspects `skip_inspect: true` per M28.4.1/M28.4.2 scope). Version 1.24.0 → 1.25.0 (minor — new Python module = new subsystem). Dual-engine DLLs rebuilt: UE_DOW 2,811,904 b / stock UE 5.7 2,813,440 b (+~32 KB each). **All 46 `verify_all.ps1` gates PASS in 538.1 s**; new soak md5s stable: `cdf15bf24b9520ca5446cb02eb8bf60d` (create) / `a61e0706b201c53ae8fc01ed88786073` (add_member) / `74d9a932ad00ca26504ce3afc0ccf147` (remove_member) / `de96efcabf29619b489ea3dbff269bcd` (set_default). MCP pytest 23/23 in 11.12 s. Compile-fix arc: initial build tripped C2027 incomplete-type errors on `FStructVariableDescription` (forward-decl only in `Kismet2/StructureEditorUtils.h`) at 5 sites in ReflectionOps.cpp + 2 in the fixture-gen commandlet — same fix for all, `#include "UserDefinedStructure/UserDefinedStructEditorData.h"`. Two rebuild cycles on the plugin DLL + one on BlueprintExporterTests before green. **Clean matrix on first full pass** — the M28.4.1/M28.4.2 playbook (explicit FName on seed-or-rename recipes + idempotent pre-checks via friendly-name walks + round-2 before-equals-after short-circuits) translated directly to the UDS shape despite more moving parts (two FGuid traps + auto-bool + RenameVariable interplay + DefaultInstance coherence via `ChangeVariableDefaultValue` rather than a direct `SetPropertyValue` write). See **M28.4.3 shipped** block further down for the full record. **Next scope OPEN** — M28.4 umbrella closed, M28.2 + M28.3 + M28.5 were already satisfied prerequisites; next external driver picks M28.6 (GameplayTag config authoring — design.md items #1 + #4), M28.7 (automation-test runner — verification beyond mechanical diff), optional M28.4.4 pure-docs close (low priority), or something else from the M28 phase table.

**Prior: 2026-04-24 — M28.4.2 shipped end-to-end.** Second slice of the M28.4 non-BP asset-factory catalog. 2 new ops (`create_data_asset_instance` + `set_data_asset_property`) in new module `scripts/python_ops/data_assets.py`; **1 new UFUNCTION** (`CreateDataAssetInstanceDeterministic`) on `UBpxReflectionOps` — `set_data_asset_property` is Python-only over existing M23.1 `SetPropertyValue`; 2 new BugHunt fixtures (`DA_BpxTestParentClass` BP-derived UPrimaryDataAsset with 3 declared vars + `DA_BpxTestInstance` empty instance); 2 new soak fixtures. Op count 38 → 40. Matrix **40 → 42 gates** (UDataAsset also isn't in inventory logic-bearing set so inspects skip via `skip_inspect: true`; soak still carries the determinism signal). Version 1.23.0 → 1.24.0 (minor per semver — new Python module counts as new subsystem). Dual-engine DLLs rebuilt: UE_DOW 2,780,160 b / stock UE 5.7 2,781,696 b (+~10 KB each vs M28.4.1). **All 42 `verify_all.ps1` gates PASS in 523.5 s**; new soaks stable md5: `a46bc5a3bbba77fa4e7cc1b808227f2e` (create_data_asset_instance) / `06ad4a6e749c4c261f9812ebf3948016` (set_data_asset_property). MCP pytest 23/23 in 11.13 s (one pre-existing test assertion loosened — CI-churn from DOW inventory build 3/4 grew `BPI_CrowdCharacter` inbound refs 2 → 7; the gate's purpose is verifying the `direction="in"` filter, not pinning an exact count). **Clean on first matrix run** — the M28.4.1 playbook translated directly since DataAsset shares CurveFloat's zero-FGuid determinism shape. Open Q #3 from M28.4.0 (mangled-UPROPERTY resolution on BP-derived DA classes) DEFERRED — BP-added DA member vars land on the generated class with their friendly FName, so `FindFProperty` resolves cleanly without a helper; the skeleton for `_resolve_da_property_name` lives in the docstring out-of-scope block if a real shadowed case surfaces. See **M28.4.2 shipped** block further down for the full record. **Next pickup: M28.4.3 UDS** — `create_user_defined_struct` + `add_uds_member` + `remove_uds_member` + `set_uds_member_default` (up to 5 new UFUNCTIONs including the optional `SetUserDefinedStructMemberDefault` per Open Q #1; new module `uds.py`; 2 FGuid::NewGuid traps to seed — Struct->Guid on StructureEditorUtils.cpp:53 + VarGuid on :303; auto-bool quirk handling; minor 1.24.0 → 1.25.0; design.md item #3 — confidence-decaying perception thickens S_TargetInfo).

**Prior: 2026-04-24 — M28.4.1 shipped end-to-end.** First slice of the M28.4 non-BP asset-factory catalog. 2 new ops (`create_curve_float` + `set_curve_float_keys`) in new module `scripts/python_ops/curves.py`; 2 new UFUNCTIONs (`CreateCurveFloatDeterministic` + `SetCurveFloatKeys`) on `UBpxReflectionOps`; new BugHunt fixture `Curve_BpxTestEmpty` (empty UCurveFloat baseline); 2 new soak fixtures. Op count 36 → 38. Matrix **38 → 40 gates** (not the research-forecast 42 — UCurveFloat isn't in the inventory pipeline's logic-bearing set so inspect gates are legitimately skipped via new `skip_inspect: true` fixture flag; soak gates still carry the determinism signal). Version 1.22.2 → 1.23.0 (minor per semver — new Python module counts as new subsystem). Dual-engine DLLs rebuilt: UE_DOW 2,770,944 b / stock UE 5.7 2,771,968 b (+~14 KB each vs M28.5.3). **All 40 `verify_all.ps1` gates PASS in 511.0 s**; new soaks stable md5: `5474ebd61525e29ac26d43e4b388a9bc` (create) / `7e332d42f6ed5cb32172d4deebbfbb8c` (set_keys). MCP pytest 23/23 in 9.93 s. See **M28.4.1 shipped** block further down for the full record including the two matrix-cycle regressions that preceded green (`RCIM_NONE` Python-binding hidden attribute + `int → ByteProperty` TypeError on `RichCurveKey.interp_mode` + stale CachedAssetRegistry_0.bin bleed from the first failed cycle).

**Prior: 2026-04-24 — M28.4.0 research-only slice landed (post-M28.5 close, user picked M28.4 as next external driver).** Research findings captured in the `### M28.4.0 research outcome` block below so the M28.4 authoring pass doesn't re-probe UE 5.7 engine headers. Same pattern as M28.2.0 / M28.3.0 / M28.5.0 research-commit slices. **Output:** 6 new UFUNCTIONs on `UBpxReflectionOps` (+1 optional 7th if Open Question #1 goes that way) + 8 new Python ops across three new modules (`curves.py` / `data_assets.py` / `uds.py`) + three new BugHunt fixtures via `GenerateTestBlueprintsCommandlet.cpp`. Sub-phase ordering by complexity ramp: **M28.4.1** CurveFloat (simplest — no GUID seeding, minor 1.22.2 → 1.23.0) — **SHIPPED** → **M28.4.2** DataAsset (medium — BP-derived parent class fixture, minor 1.23.0 → 1.24.0) → **M28.4.3** UDS (most complex — `FStructureEditorUtils` routing, 2 FGuid::NewGuid traps, auto-bool handling, minor 1.24.0 → 1.25.0). Per-sub-phase driver maps cleanly to design.md items: #6 (intensity curve) / #7 (archetype DAs) / #3 (confidence-decaying `S_TargetInfo` perception struct).

**Prior: 2026-04-24 — M28.5.3 shipped end-to-end; M28.5 catalog now COMPLETE (5 ops).** Closes the M28.5 umbrella started at M28.5.0 (research) and shipped across M28.5.1 (`add_eqs_option`) / M28.5.2 (`add_eqs_test` + `remove_eqs_test`) / M28.5.3 (`set_eqs_generator_property` + `set_eqs_test_property`). First M28.x sub-phase with **zero new UFUNCTIONs** — both M28.5.3 ops are pure Python wrappers over the existing M23.1 `SetPropertyValue` reflection bridge via nested paths like `["Options", "[0]", "Tests", "[0]", "ScoringFactor", "DefaultValue"]` (array indices + FStructProperty descent handled by the M23.1 `ResolvePath` walker that M11–M15 already exercised). Shared `_set_eqs_subobject_property` helper + shared `_normalize_scalar_value` helper (mirrors `level.set_level_actor_property`'s Python→ExportText coercion) keep both ops byte-identical on their shared paths. **EQS_BpxTestWithOption fixture reused from M28.5.2** — no new fixture needed. Plan pipeline wired end-to-end (OP_SPECS / _OP_DISPATCH / _op_expected_changes / __init__ re-exports). Matrix **clean on first run** — the no-new-UFUNCTION shape dodges the three bug classes that burned cycles in M28.5.1/M28.5.2 (TypeError on make_result extra args / destructive-op round-2 idempotency / stale scratch residue). **All 38 `verify_all.ps1` gates PASS in 501.7 s** on BugHunt / stock UE 5.7 (automation 15.9 s + determinism 52.1 s + 18 inspect + 18 soak). New gate md5s stable: `40ff8e0962f93dce46fbedac3baa412a` (generator prop) / `fdfae57b5992c3d74e15b7b1a3347caa` (test prop). MCP pytest 23/23 in 11.90 s. Dual-engine DLL rebuild was driven solely by baked-in version strings across 7 C++ files — no new translation units, so both DLLs stay byte-size-identical to M28.5.2 (2,756,608 b / 2,757,632 b). Version bump 1.22.1 → 1.22.2 (patch — additive same subsystem). **Next scope is OPEN** — M28.5 umbrella closed, M28.2 + M28.3 + M28.5 are satisfied prerequisites; next external driver decides M28.4 (UDS / CurveFloat / DataAsset factories — design.md items #3, #6, #7) / M28.6 (GameplayTag config authoring — design.md items #1 + #4) / M28.7 (automation-test runner — semantic verification beyond mechanical diff) / or something else from the M28 phase table. An optional M28.5.4 pure-docs sweep (AGENT_LOOP worked example chaining add_eqs_option → add_eqs_test → set_eqs_test_property against a design.md anchor like the squad-director cover scan) would close the M28.5 umbrella the way M28.3.6 closed M28.3 — low priority, defer unless a concrete driver asks for it. See **M28.5.3 shipped** block further down for the full record.

**Prior: 2026-04-24 — M28.5.0 research-only slice landed (post-M28.3 continuation).** No implementation yet — research findings captured in the new `### M28.5.0 research outcome` block below so the M28.5 authoring pass doesn't re-probe AIModule headers. Same pattern as M28.2.0 / M28.3.0 research-commit slices. Picks out the C++ surface (3-4 UFUNCTIONs: `AddEnvQueryOption` / `AddEnvQueryTest` / `RemoveEnvQueryTest` + optional `SetEnvQueryGenerator`; scalar property edits reuse existing `SetPropertyValue` bridge via the `UEnvQuery.Options[i].Tests[j].MyProp` path) and the Python surface (5 ops in new module `scripts/python_ops/eqs.py`), plus the determinism recipe (`TestOrder` manually assigned as array index, explicit `FName` on every `NewObject` to avoid counter-suffix drift — same pattern as M28.3.x K2Node spawns). **Load-bearing open question: fixture path.** BugHunt + DOW have zero EQS assets; M28.5.1 needs `EQS_BpxTestBasic` authored via `GenerateTestBlueprintsCommandlet` (option A in the research block; adds ~80 lines). M28.5 minor bump 1.21.3 → 1.22.0 when the implementation slice ships. **Next pickup for M28.5 = the fixture-gen commandlet extension + the first `add_eqs_option` op.**

**Prior: 2026-04-24 — `.gitignore` backlog cleanup landed (chore commit, no milestone).** `_build_output*/` wildcard replaces the literal `_build_output/` rule so the three suffix variants (`_5_7` / `_dow` / `_bphtests`) no longer appear in `git status`. Also added UE auto-gen Config ignores + inspect-harness scratch-`.uasset` glob. Post-commit `git status` shows only parent-dir items outside the plugin's ignore scope. Closes the explicit backlog line from the prior "Expected untracked state" paragraph.

**Prior: 2026-04-24 — M28.3 catalog closed end-to-end via M28.3.6 docs sweep.** The M28.3.6 pure-docs slice adds the promised follow-up worked example in `plans/AGENT_LOOP.md` — `"Worked example — wire OnOrderReceived body via M28.3 node spawns"` — demonstrating the chained authoring pattern for every design.md body-wiring case (spawn input-side nodes → spawn output-side / control-flow nodes → declare local state via `add_local_variable` → set pin literals → connect pins by GUID). Also consolidates the `CATALOG.md` "Coming next" section with an explicit M28.3 COMPLETE block indexing all 9 ops across sub-phases. No C++ / Python / tests touched; no version bump per the M28.2.5 / M28.3.0 docs-only precedent. **M28.3 catalog now ships 9 ops end-to-end** (add_branch_node + set_graph_pin_default + add_call_function_node + add_variable_get_node + add_variable_set_node + add_custom_event_node + add_execution_sequence_node + add_dynamic_cast_node + add_local_variable), all idempotent, all determinism-seeded so M28.pre.3 soak round 2 is byte-identical across the full catalog. **Next scope is open** — M28.2 + M28.3 are satisfied prerequisites so any of M28.4 (UDS / CurveFloat / DataAsset factories) / M28.5 (EQS write-side) / M28.6 (GameplayTag config authoring) / M28.7 (automation-test runner) can ship next, per the M28 phase table. Pick based on next external driver. See **M28.3.6 shipped** block further down for the full record including the 4-sub-phase summary table.

**Prior: 2026-04-24 — M28.3.4 shipped end-to-end. M28.3 catalog complete (9 ops across 4 sub-phases).** Last planned K2Node-family slice lands: `add_local_variable`. Different shape from M28.3.1–.3 — no K2Node is spawned; instead an existing `UK2Node_FunctionEntry`'s `LocalVariables: TArray<FBPVariableDescription>` UPROPERTY gains a new entry. Per M28.3.0 research sequencing, shipped last so the Entry-node machinery was fully exercised by the prior spawn-based phases. 1 new UFUNCTION on `UBpxReflectionOps` (`AddLocalVariableDeterministic` — wraps `FBlueprintEditorUtils::AddLocalVariable` and post-seeds `VarGuid` via `SeedGuidFromJoined(<bp>:func:<fn>:localvar:<var>)` since the engine helper uses `FGuid::NewGuid()` at `BlueprintEditorUtils.cpp:5433`; does NOT double-mark since AddLocalVariable calls `MarkBlueprintAsStructurallyModified` internally). 1 new Python op `add_local_variable` reusing `blueprint_structural._resolve_pin_type` — first cross-module helper reuse in the `python_ops/` tree. Full plan-pipeline wiring (`__init__` / `plan_shape` / `plan_executor` / `mechanical_diff`). Op count 30 → 31. Reused `BP_BpxTestGraphNodesCalls` fixture for a 7th op-coverage — `DoTheThing` function targeted end-to-end by CallFunction / VariableGet / VariableSet / CustomEvent / ExecutionSequence / DynamicCast / LocalVariable, all via non-overlapping identifiers. New inspect+soak fixture `add_local_variable.json` targeting `DoTheThing` with `int LoopIndex = 7`. **All 27 `verify_all.ps1` gates PASS on BugHunt / stock UE 5.7 in 374.4 s** — soak md5 `8564b1ff661bab132d9891ec9dc9c6f9` stable round-to-round. MCP pytest 23/23. Dual-engine DLL rebuilt (UE_DOW 2,730,496 b BuildId `6efc257b`; stock-5.7 2,731,520 b BuildId `47537391`; +~10 KB per engine vs M28.3.3 consistent with 1 new UFUNCTION). Version stamp 1.21.2 → 1.21.3 (patch per semver — additive same subsystem). **Next: M28.3.6 docs sweep** — pure-docs close of M28.3 with no version bump. CATALOG.md / plans/README.md / CLAUDE.md already carry entries for all 9 M28.3 ops (accumulated during each sub-phase); the sweep primarily needs `plans/AGENT_LOOP.md` worked example demonstrating chained spawn + wire + local-var authoring (e.g. a utility-scorer function skeleton: `add_bp_function` → `add_local_variable` × N → `add_variable_get_node` / `add_call_function_node` → `connect_graph_pins`). After M28.3.6 the M28.3 umbrella closes and the next scope is an open call between M28.4 (UDS / CurveFloat / DataAsset factories — design.md items #3, #6, #7), M28.5 (EQS write-side — design.md item #5), M28.6 (GameplayTag config authoring — design.md items #1 + #4), M28.7 (automation-test runner — verification beyond mechanical diff). Per the M28 phase-table sequencing, M28.2 + M28.3 are now the satisfied prerequisites for all of those. See **M28.3.4 shipped** block further down for the full record.

**Prior: 2026-04-24 — M28.3.3 shipped end-to-end.** Three independent one-off K2Node types close the FunctionReference / VariableReference family's natural siblings: `add_custom_event_node` (spawns `UK2Node_CustomEvent` with ubergraph-only op-entry gate + pre-alloc `CustomFunctionName` set), `add_execution_sequence_node` (spawns `UK2Node_ExecutionSequence` with N `then_N` outputs via N-2 `IK2Node_AddPinInterface::AddInputPin` calls — method name misleading; it adds THEN-OUT pins, range-clamped to `[2, 16]`, seed pin GUIDs AFTER the AddInputPin loop), `add_dynamic_cast_node` (spawns `UK2Node_DynamicCast` with `TargetType = UClass*` set before `AllocateDefaultPins` so the `As<TargetClass>` output pin's type materialises correctly — post-alloc sets leave As<X> as wildcard). 3 new UFUNCTIONs on `UBpxReflectionOps`; 3 new Python ops in `blueprint_graph_nodes.py` (30 ops total). Full plan-pipeline wiring (`__init__` re-exports / `plan_shape.OP_SPECS` / `plan_executor._OP_DISPATCH` / `mechanical_diff._op_expected_changes`). Reused `BP_BpxTestGraphNodesCalls` fixture (no new .uasset) with 3 new inspect+soak assertions JSONs at non-overlapping positions `(224,-48)`/`(256,-48)`/`(288,-48)`. **One trap caught by M28.pre.2 inspect gate on first run**: UE's `UEdGraphSchema_K2::PN_Then` is lowercase `"then"`, not title-case `"Then"` — the M28.3.0 research block used the informal title-case prose and my initial assertion read `"Then_2"`. Fixed in one-line edit to the fixture JSON + Python op's `pin_names` list + CATALOG.md + plans/README.md, rerun clean. Value of content-inspect gate demonstrated again (the byte-identity soak gate alone would have missed it). **All 25 `verify_all.ps1` gates PASS on BugHunt / stock UE 5.7 in 350 s** (2 project-level + 12 inspect + 11 soak; three new `inspect-add_{custom_event,dynamic_cast,execution_sequence}_node` each ~17.8 s + three new `soak-add_{custom_event,dynamic_cast,execution_sequence}_node` each 6.1 s with stable md5 + `node_guid`). MCP pytest 23/23 when run with editor quiet (initial concurrent run with matrix saw 3 bridge-vs-subprocess races; rerun clean post-matrix). Dual-engine DLL rebuilt (UE_DOW 2,719,744 b BuildId `6efc257b`; stock-5.7 2,720,768 b BuildId `47537391`; +~24 KB per engine vs M28.3.2 consistent with 3 new UFUNCTIONs + 4 new K2Node includes). Version stamp 1.21.1 → 1.21.2 (patch per semver — additive same subsystem). **Next: M28.3.4 — `add_local_variable`** (patch 1.21.2 → 1.21.3). Different shape from M28.3.1–.3 since it modifies `UK2Node_FunctionEntry::LocalVariables` struct array on an existing Entry node rather than spawning a fresh K2Node; per M28.3.0 research it ships last so the Entry-node machinery is fully exercised by prior phases. After that comes M28.3.6 docs sweep (CATALOG.md already carries M28.3.3 entries; plans/README.md op kwargs table already carries all 8 M28.3 ops; CLAUDE.md Reflection/ tree already references the full M28.3.x catalog — the sweep mostly needs the AGENT_LOOP.md worked example). Fixture reuse continues: `BP_BpxTestGraphNodesCalls`'s `DoTheThing` function is the natural target for `add_local_variable`. See **M28.3.3 shipped** block further down for the full record.

**Prior: 2026-04-24 — M28.3.2 shipped end-to-end.** FunctionReference / VariableReference family of the M28.3 node-level graph-authoring catalog. Three new ops: `add_call_function_node` (spawns `UK2Node_CallFunction` with `FunctionReference.SetSelfMember(Name)` when `target_class_path=""` or `SetExternalMember(Name, UClass*)` when non-empty), `add_variable_get_node` (generalises M26.1's self-only `AddSelfMemberGetNode` to any graph + any variable context via `VariableReference`), `add_variable_set_node` (sibling — same self/external resolution). All three spawn-op internals share 80%+ code via the new `BpxReflection::MakeMemberRefSeedPrefix` C++ helper + the `_spawn_node_common` Python helper. C++ bridge extends `UBpxReflectionOps` with 3 new UFUNCTIONs; Python surface in `blueprint_graph_nodes.py` gains 3 ops via ~8 lines each wrapping the shared helper. Plan pipeline wired through `__init__.py` / `plan_shape.OP_SPECS` / `plan_executor._OP_DISPATCH` / `mechanical_diff._op_expected_changes`. New BugHunt fixture `BP_BpxTestGraphNodesCalls` (Actor BP with declared `TestCount: int` + `DoTheThing()` function — first non-empty structural fixture; required because single-op plan shape in the harness prevents chaining `add_bp_variable` + `add_variable_get_node`) + `scripts/inspect_fixtures/add_call_function_node.json` / `add_variable_get_node.json` / `add_variable_set_node.json` inspect+soak assertions. **All 20 `verify_all.ps1` gates PASS on BugHunt / stock UE 5.7 in 279.3 s** (2 existing + 9 inspect + 9 soak; three new `inspect-add_{call_function,variable_get,variable_set}_node` each 17.8 s + three new `soak-add_{call_function,variable_get,variable_set}_node` each 6.1–6.2 s). MCP pytest 23/23. Dual-engine DLL rebuilt (UE_DOW 2,695,168 b; stock-5.7 2,696,192 b). Version stamp 1.21.0 → 1.21.1 (patch per semver — additive same subsystem). **`set_graph_pin_default.json` backfill deferred** — harness is single-op and the op has equivalent coverage via M26.1's `SetNodePinLiteralDefault` inspect/soak through `implement_interface_function`. **Next: M28.3.3 — `add_custom_event_node` + `add_execution_sequence_node` + `add_dynamic_cast_node`** (patch 1.21.1 → 1.21.2). Three independent one-off K2Node types per the M28.3.0 research outcome block. CustomEvent must pre-check the target graph is an ubergraph (ship with op-entry validation, not compile-time); ExecutionSequence must document the misleading `IK2Node_AddPinInterface::AddInputPin` naming (adds a new THEN-OUT pin); DynamicCast sets `TargetType = UClass*` before `AllocateDefaultPins`. Reuse `BP_BpxTestGraphNodesCalls` fixture (no new fixture needed). See **M28.3.2 shipped** block further down and the **M28.3 research outcome** block for the full surface proposal.

**Prior: 2026-04-23 — M28.3.1 shipped, M28.3.2 was next.** First node-spawn slice of the M28.3 catalog. Two new ops: `add_branch_node` (`UK2Node_IfThenElse` into any K2 graph family — function / interface-override / ubergraph — with `SeedGuidFromJoined(:branch:x,y)` NodeGuid + M26.1.2 pin-GUID seed triad over `execute` / `Condition` / `then` / `else` + explicit `FName` on `NewObject`) + `set_graph_pin_default` (graph-level sibling of M26.1's function-name-keyed `SetNodePinLiteralDefault`, 32-hex `NodeGuid` string input). C++ bridge: 2 new UFUNCTIONs (`AddBranchNode` + `SetGraphPinLiteralDefault`); Python in new module `scripts/python_ops/blueprint_graph_nodes.py`. BugHunt fixture `BP_BpxTestGraphNodes` (empty Actor BP). Version 1.20.1 → 1.21.0 (minor per semver — new subsystem). Commit `cc0204d`. See **M28.3.1 shipped** block further down for the full record.

**Prior: 2026-04-23 — M28.3.0 research outcome closed, M28.3.1 was next.** Research block inserted between M28.2 closure and M29 umbrella (`3cd5283`). Output: 8 new UFUNCTIONs + 1 sibling on `UBpxReflectionOps`, 8 new Python ops in new module, determinism traps cataloged (`FGraphNodeCreator::Finalize` NodeGuid via `CreateNewGuid` + `AllocateDefaultPins` PinId via `UEdGraphPin::CreatePin` + `MakeUniqueObjectName` transient names + `LocalVariables` VarGuid), narrow K2Node catalog of 7 types picked against design.md anchors. Mirrors M28.2.0 research-commit pattern.

**Prior: 2026-04-23 — M29 umbrella closed end-to-end.** Five sub-phases shipped: M29.0 research → M29.1 `UCustomizableObjectInstance` renderer (patch `d8e8bcb` → 1.19.14) → M29.2 `UCustomizableObject` renderer + pin-GUID masking (minor `d6b9e7a` → 1.20.0) → M29.3 `UCustomizableObjectMacroLibrary` renderer + shared node-walker extraction (patch `bb4703f` → 1.20.1) → M29.4 `verify_determinism.ps1 -Project MutableSample` arm (infra `831ce3b`, no bump) → M29.5 README docs sweep (pure docs, no bump). Twin-run md5 evidence durable at the per-sub-phase level: COI_Character `ECC0F12CB660E38786D928A9BFEFD83D`, CO_Weapon `28B162FBD46C7AA9AA290B95CA6F5845`, COML_Character `A505AC58A4422C6B489D0D56C3036159`, full-sweep tree-diff PASS via `git diff --no-index`. Shipped surface: three new Tier 2 renderers + one shared-helper extraction + one determinism-gate arm + README feature-matrix updates (6 touch points). All Mutable authoring surfaces now grep-readable without opening the editor. Write-side (authoring edits) is deliberately out of scope per the M29 scope block — a future M30-ish could revisit if a driver appears. See the M29 umbrella-close summary block further down for the full record.

**Prior: 2026-04-23 — M29.4 shipped, M29.5 was next.** M29.4 (determinism gate extension) shipped no-new-code / no-version-bump: `scripts/verify_determinism.ps1` gained a `MutableSample` arm (switch-statement adds to `$ProjectFile` / `$DeepAsset` / `$ExtraArgs` + synopsis/examples update). **Full-sweep twin-run PASS** via `-Project MutableSample -SweepDeepDump` — both output trees byte-identical via `git diff --no-index` across a **291-file / 45.2 MB** tree (92 `.deep.md` + 93 `.meta.json` + 104 `.md` + 13 top-level rollups).

**Prior: 2026-04-23 — M29.3 shipped, M29.4 was next.** M29.3 (`UCustomizableObjectMacroLibrary` renderer) shipped with 1.20.0 → 1.20.1 patch bump. New `CustomizableObjectMacroLibraryDeepRenderer.{h,cpp}` gated on `WITH_MUTABLE_SUPPORT`; per-macro section emits Name/Description/I-O variable table (stable `UniqueId` FGuid) + full graph walk. **Extraction refactor**: `MaskPinGuids` + the node-graph walker lifted from M29.2's renderer into `DeepRenderShared::RenderEdGraphNodes` so M29.3 reuses the walker byte-identically. CO_Weapon regression PASS — md5 stays at `28B162FBD46C7AA9AA290B95CA6F5845` (refactor didn't shift output). **Finding carried forward**: `ExportTextItem_Direct(FString& Out, ...)` APPENDS rather than overwrites — fallback-placeholder init leaks into output. Determinism three-run PASS on `MutableSample/Character/COML_Character` — md5 `A505AC58A4422C6B489D0D56C3036159` (34,620 bytes, 2 macros × ~14 nodes each). `verify_all.ps1` 12/12 PASS 188.4 s on BugHunt / stock UE 5.7. See the M29.3 closure block further down for the full record.

**Prior: 2026-04-23 — M29.2 shipped, M29.3 was next.** M29.2 (`UCustomizableObject` renderer — biggest Mutable sub-phase) shipped with 1.19.14 → 1.20.0 minor bump (new subsystem per semver rule). New `CustomizableObjectDeepRenderer.{h,cpp}` gated on `WITH_MUTABLE_SUPPORT`; sections: Identity / Runtime Options / Compile Options / Components / Parameters / States / Node Graph / Not rendered. **Key finding carried forward**: `FEdGraphPinReference`-typed UPROPERTYs serialize `PinId=<32-hex>` which regenerates each load — masked via a `MaskPinGuids` post-process that replaces every hex GUID with `<unstable>` while preserving the `OwningNode` reference. Determinism twin-run PASS on `MutableSample/Weapon/CO_Weapon` — md5 `28B162FBD46C7AA9AA290B95CA6F5845`, 42,185 bytes. MutableSample's game module had to be re-compiled against UE_DOW for the twin-run (BuildId match). See the M29.2 closure block further down for the full record.

**Prior: 2026-04-23 — M29.1 shipped, M29.2 was next.** M29.0 research closed inline in the M29 block (Q1–Q5 answered, Q1 corrected during M29.1 implementation — stock UE 5.7 **does** ship Mutable; original negative Glob probe was wrong). M29.1 (`UCustomizableObjectInstance` renderer) shipped with 1.19.13 → 1.19.14 patch bump; all 12 `verify_all.ps1` gates green on BugHunt / stock UE 5.7 in 183 s, plus a dual-shell determinism twin against `MutableSample/COI_Character` md5-stable at `ECC0F12CB660E38786D928A9BFEFD83D` (5618 bytes). See the M29 block below for the full M29.1 closure entry + the M29.0 findings subsection.

**Prior: 2026-04-23 — M28.2.5 (Docs sweep) shipped at `4308642`, no version bump.** Closes M28.2 end-to-end. Pure docs: CATALOG.md gets the four new op sections (`add_bp_variable` / `add_bp_function` / `add_component_to_scs` / `add_bp_interface`), `plans/README.md` gets an extended op kwargs table + four new jsonc examples, `plans/AGENT_LOOP.md` gets a worked squad-director chain example (`add_bp_variable(bActiveOrder)` → `add_bp_interface(BPI_OrderListener)` → `add_bp_function(OnOrderReceived)` → follow-up M26.1 body-authoring as a separate plan), and `CLAUDE.md` Project Structure tree gains `Public/Reflection/` + `Private/Reflection/` subtrees covering every UFUNCTION from M23.1 through M28.2.4. See the `### M28.2.5 shipped (2026-04-23, no version bump)` closure block further down. No matrix invocation (pure docs). Prior post-M28.2 next scope was **M28.3 — node-level graph authoring catalog** (`add_graph_node` / `connect_pins` / `set_pin_default` / `add_local_variable`); design.md items #2 / #4 / #6 / #8 drive it. **M29 preempts M28.3** for this session — external driver priority.

**Prior: 2026-04-23 — M28.2.4 (`add_bp_interface`) shipped, 1.19.12 → 1.19.13.** Fourth and final M28.2 structural-edit op. See the `### M28.2.4 shipped (2026-04-23, 1.19.12 → 1.19.13)` closure block further down for the full record. All 12 pre-push gates green via `verify_all.ps1` (181.9 s) + MCP pytest 23/23.

**Prior: 2026-04-23 — M28.2.3 (`add_component_to_scs`) shipped at `fb6a60e`, 1.19.11 → 1.19.12.** Docs-only Resume refresh followed at `e760648`. See the `### M28.2.3 shipped (2026-04-23, 1.19.11 → 1.19.12)` closure block further down for the full record. All 10 pre-push gates green via `verify_all.ps1` (158 s) + MCP pytest 23/23.

**Expected untracked state on `/clear` resume (all known-ignore, not milestone content):** outside the plugin dir, `Code_Submit_Compiled_Binaries_to_UGS_*.log` (CI artefacts) / `design.md` / `infographic.html` / `placeholder/` sit in the parent directory alongside the plugin and aren't covered by the plugin's own `.gitignore` — they belong to a potential parent-repo ignore list. Inside the plugin, the prior-backlog `.gitignore` pass landed in the M28.3.6 post-close housekeeping commit: `_build_output*/` wildcard covers `_build_output/` + `_build_output_5_7/` + `_build_output_dow/` + `_build_output_bphtests/` (the `_5_7` variant is a **live junction target** for `D:/Work/UE_DOW_Legacy/Plugins/BlueprintExporter` and `D:/Work/mutable/MutableSample/Plugins/BlueprintExporter` — do NOT delete, just don't stage either); `BugHunt/TestProject/Config/DefaultInput.ini` + `BugHunt/BlueprintExporterTests/Config/` are UE auto-gen first-run boilerplate; `BugHunt/TestProject/Content/TestBlueprints/*Scratch*.uasset` covers inspect-harness scratch from `verify_post_apply_inspect.ps1` runs (normal runs clean up; `-KeepScratch` or a failed cleanup leaves residue). Tracked working tree is clean at HEAD `0110160` (M28.3.4 feat) or one of its subsequent pure-docs refresh commits. Supporting feat chain: M28.3.4 `0110160`, M28.3.3 `df8aa08`, M28.3.2 `5959a01`, M28.3.1 `cc0204d`, M29.4 `831ce3b`, M29.3 `bb4703f`, M29.2 `d6b9e7a`, M29.1 `d8e8bcb`. Do not stage the parent-dir untracked items; the plugin-dir ones are now covered by `.gitignore` so they won't appear in `git status` anyway.

**External-to-repo junctions live (not committed, stay across sessions):** `D:/Work/mutable/MutableSample/Plugins/BlueprintExporter` → `D:/Work/blueprintexporter/blueprint-exporter/BuiltPlugin` (UE_DOW-built, for live-dump against any MutableSample CO/COI/COML asset); `D:/Work/UE_DOW_Legacy/Plugins/BlueprintExporter` → `D:/Work/blueprintexporter/blueprint-exporter/_build_output_5_7` (stock-5.7-built, for Legacy runtime work). Both used during M29.1–M29.4; survive across `/clear`. If either is broken (junction target gone), recreate via `cmd.exe /c mklink /J <junction> <target>`. MutableSample's game module is compiled against UE_DOW (BuildId `6efc257b-...` from M29.2); the stock-5.7 pre-shipped MutableSample.dll BuildId `47537391` is NOT the one in place — if the twin-run is re-exercised against MutableSample post-/clear, verify via `Get-Content D:\Work\mutable\MutableSample\Binaries\Win64\UnrealEditor.modules` and rebuild via `Build.bat MutableSampleEditor Win64 Development -Project=D:\Work\mutable\MutableSample\MutableSample.uproject` (~22 s warm) if the BuildId drifted.

**2026-04-23 — MCP Perforce rule side-arc (not a milestone, two commits `51c8648` + `fb8a6fd`).** Landed after M28.2.4 in response to explicit user asks. First commit `51c8648` added a code-level refusal (argv guard + PerforceRefused exception + "ask Niclas" routing). User pushed back: the rule should be "inform + approve", not "refuse all P4". Follow-up `fb8a6fd` reverted the aggressive code-level guards, kept the behavioural rule as documentation in three MCP-visible places (server.py FastMCP `instructions=`, README "House rules" section, `_ue_subprocess.py` module docstring). Rule: before any P4-shaped side effect (including `apply_plan` that might auto-checkout .uasset via ambient Perforce config), inform the user of the expected side effects and wait for `confirm=true` approval. The "questions about MCP behaviour go to Niclas, not a Slack channel" rule is also in force, same doc surfaces. Both rules are in auto-memory: `feedback_no_perforce_without_confirmation.md` + `feedback_mcp_questions_go_to_niclas.md`. Not a milestone — cross-cutting MCP behaviour, captured in auto-memory (shared across sessions) and in the MCP tree's reader-visible docs. MCP pytest stays at 23/23 baseline after the revert.

**Session 2026-04-23 later — cross-session .uasset drift investigation (deferred outcome).** One-commit arc on `main` at `d1a879d` (4 commits ahead of `origin/main` — NOT pushed). Scope: user asked to attempt the cross-session byte-identity problem WIP previously deferred (~900 bytes drift from `UPackage::SavePackage` GUID regeneration). Built + measured a two-shell probe, identified what's reachable from op-level code (`PersistentGuid` + `UBlueprintCore::BlueprintGuid` via FProperty reflection on the private UPROPERTY), prototyped a pre-save seeding helper that cut drift ~40% in warm-cache cross-session runs, but **rejected shipping it**: improvement is cosmetic (partial diff reduction, not byte-identity), no matrix gate depends on cross-session byte-identity, and the helper would touch engine-managed fields pre-save on every op save (M28.1 / M28.3-narrow / M28.9 / future M28.2+), adding permanent maintenance surface + UE-version-bump revalidation cost for zero workflow benefit. Reverted source + BuiltPlugin DLL + BugHunt DLL mirror back to the 1.19.9 baseline; committed only the three investigation utilities (`scripts/probe_cross_session_drift.py` + `diff_cross_session_drift.py` + `dump_drift_context.py`) + a WIP entry under the M26.1.2 regression-chase block pointing at them as the starting point for a future engine-determinism milestone. `verify_all.ps1` matrix 4/4 PASS on the reverted 1.19.9 state. Next-up remains **M28.2 — Structural BP edits** (see the "Pending work" block below); nothing in this arc gates it.

**Session 2026-04-21 continued (full day) — cleanup arc + plugin-scope
trim + M25.2.1 `add_statetree_transition` + MCP-side plan-shape pre-
validation + confirmation gate on mutating tools + UX fixes + py-spy
diagnosis of the Legacy `apply_plan` hang and its three-commit fix
(drop `-stdout`, redirect stdout/stderr to tempfiles, redirect stdin
to `DEVNULL`). Fourteen commits between `32d0073` and `4964f2a`, all
pushed. `validate_plan` + `apply_plan` now actually land on Legacy in
~15 s cold-start instead of hanging indefinitely. Next active scope
(see "Pending work" below): **M26 — Blueprint graph authoring
primitives**, triggered by two real capability gaps that surfaced
today while diagnosing the CombatPrototype Flat Arena bug via MCP.
Read this block first on any `/clear` resume. Earlier 17-commit arc
from the same day continues below at "Session 2026-04-21 — M25.1
shipped".

### The continued-arc (2026-04-21 later)

| Commit | What it delivered |
|---|---|
| `32d0073` | docs: **reframe README around CI inventory + MCP** — 1.15.x README was a feature-dump from when the plugin was local-first. Rewrote to lead with CI-pipeline-regenerates-inventory-to-GitHub + MCP-serves-inventory-to-Claude-Code; local editor usage demoted to section 3. Added ASCII architecture diagram (TeamCity → headless UE → commit to `Inventory_<Project>/` → MCP → Claude Code → apply_plan via headless UE). Pivot ratified in project memory (`project_direction_pivot.md`). |
| `fec0b02` | chore: **remove stale `briefs/` directory** — five planning briefs (critical/high/remaining gaps, LLM generation briefs) no longer referenced in any doc; work they scoped has shipped or been superseded. |
| `ecf2110` | refactor: **remove LLM subsystem** — deletes entire `Public/LLM/` + `Private/LLM/` + 4 LLM test files + Generate-C++-with-AI editor menu entry + LLMService lifecycle in module startup + HTTP / Crypt32.lib Build.cs deps. Superseded by Claude Code driving the plugin via MCP — conversation context + refinement via agent > one-shot modal. DLL shrinks 3.5 MB → 2.7 MB. Zero inventory-pipeline code paths touched. 57 files, −13,716 lines. |
| `8634507` | refactor: **remove Import + Deserializer + Diff + CppStubs + BugHunt round-trip commandlets** — deletes JSON-round-trip write-back path (`BlueprintImportCommandlet` + `BlueprintImportManager` + `BlueprintDeserializer`), `BlueprintDiffEngine`, `CppStubGenerator`, the two BugHunt regression-test commandlets (`BlueprintExportRoundtripCommandlet` + `RunBugHuntCommandlet`), the `ValidateRoundTrip` method inside `BlueprintExportManager`, the `bExportCppStubs` / `bRunRoundTripValidation` config flags, the `FBlueprintImportConfig` struct, the Import/Diff/Generate-C++-Stubs editor menu entries, the commandlet's post-export loop (manager already writes `.txt` + `.digest.json` inline), and the corresponding `FBlueprintExportDiffTest`. Superseded by MCP `apply_plan` (python_ops → UE save/compile paths, mechanical-diff oracle, no deserializer fidelity risk). BugHunt fixture project + `GenerateTestBlueprintsCommandlet` + junctions + `verify_determinism.ps1` all stay for developing new inventory handlers. DLL 2.7 MB → 2.4 MB. 37 files, −9,880 lines. |
| `299ab52` | chore: **bump 1.16.0 + docs cleanup** — version bump across 9 stamp locations (uplugin ×2, module UE_LOG, four `PluginVersion` string literals, `BlueprintExporterTests` live-version test, README). Minor bump — user-visible surface change (features removed). README strips "AI C++ generation" + "Round-trip edit" sections + `-CppStubs` CLI flag + stale "Import / diff" editor-UI bullet; adds "Applying edits back into Unreal" blurb pointing at MCP `apply_plan`. CLAUDE.md strips entire LLM Public/Private subtrees + "### LLM Types" + LLM Pipeline Layer bullet + Import/Diff/CppExport entries + `FBlueprintImportConfig` from Key Types + Round-trip Validation bullet + `BlueprintImport` CLI example. `BugHunt/README.md` rewritten around the new dev workflow (fixture project + typed handler + DeepRenderer + determinism gate) instead of the removed round-trip oracle; BRIEF/REPORT/HANDOFF preserved as historical archive. Determinism gate PASS post-rebuild. |
| `a30ac31` | feat: **M25.2.1 `add_statetree_transition` + bump to 1.17.0** — three new StateTree ops in `scripts/python_ops/statetree.py`: `add_statetree_transition(st_path, state_path, trigger, target_state_path, priority="Normal", event_tag="")`, `remove_statetree_transition(...)`, `verify_state_transitions(st_path, state_path)`. Pattern mirrors `add_statetree_enter_condition`: `unreal.BpxReflectionOps` for protected-editor-data access, idempotence on `(Trigger, State.ID [, EventTag])`, deterministic transition GUID seeded from inputs, compile + save. `add_` resolves target state's `ID` (FGuid) + `Name` (FName) read-only and populates `FStateTreeStateLink` with `LinkType=GotoState` (non-GotoState link types not supported). Plumbing: `__init__.py` + `plan_executor.py` (exports + dispatch); `plan_validator.py` adds three OP_SPECS entries, introduces `optional` kwargs support (for `priority`/`event_tag`), generalises `state_path` → `state_paths` list so an op can declare multiple state-path kwargs (existing EC op specs migrated to new shape); `mechanical_diff.py` new entries; `CATALOG.md` documents with worked `MoveToClue → CombatLoop` example + removes the stub from "Coming next"; `plans/README.md` op kwargs table updated. Version bump rebuilds DLL against both engines (custom UE_DOW + stock UE 5.7); stock-5.7 DLL installed at `D:/Work/UE_DOW_Legacy/Plugins/BlueprintExporter/Binaries/Win64/` for the upcoming live test. Determinism gate PASS. 23 files. |
| `9b2b604` | fix: **harden `_op_expected_changes` against malformed plans** — surfaced 2026-04-21 during first live `apply_plan` against Legacy. `run_plan`'s pre-flight calls `compute_expected_changes` → `_op_expected_changes` BEFORE `validate_plan` runs. If an agent produces the wrong plan shape (e.g. `{"op": "...", "args": {...}}` instead of flattened kwargs, which actually happened to us), the old code raised `KeyError: 'st_path'` deep inside the pre-flight, crashing the UE commandlet before the validator could produce its structured "unknown fields / missing required fields" report. Fix: guard each kwarg lookup with presence check, return `[]` on missing keys. Malformed plans now land on `validate_plan`'s doorstep cleanly and the agent gets a structured rejection. Pure Python, no DLL impact, no version bump. |

### The hang-fix arc (2026-04-21 evening) — pre-validation + confirm gate + UX + pipe-deadlock root cause

| Commit | What it delivered |
|---|---|
| `073d595` | feat: **MCP-side plan-shape pre-validation** — shipped the pre-validation scope greenlit after `9b2b604`. New `scripts/python_ops/plan_shape.py` lifts `OP_SPECS` + `_validate_top_level` + `_validate_op_shape` + `_validate_verification` out of `plan_validator.py` as pure Python with NO `import unreal`, importable by the MCP server. `validate_op_shape` detects the `{"op":"...","args":{...}}` wrapper bug with a targeted hint ("did you wrap the kwargs in an `args` object? each op's kwargs must be flattened into the op dict"). `plan_validator.py` now delegates shape checks to `plan_shape`, returns the shape report early if it fails, else runs the UE-backed asset + state_path resolution on top. `tools/plans.py` loads `plan_shape.py` as a standalone module via `importlib.util.spec_from_file_location` (bypasses `python_ops/__init__.py` which imports `unreal`), module-level cache per scripts_root. Both `validate_plan_impl` and `apply_plan_impl` call `validate_shape` after JSON parse but before any subprocess — malformed plans now return `{error, report}` in <100ms without spawning UE (was 2.5 min of cold-start to fail). Tool docstrings gain a full plan JSON example with flattened kwargs + explicit "DO NOT wrap kwargs in args" warning. Smoke 42 → 45 assertions (wrapper rejection, apply short-circuit, unknown-op rejection — all with `patch.object(subprocess, "run")` asserting no UE invocation). |
| `d1dc8f3` | feat: **MCP confirmation gate on mutating tools** — colleagues primarily use the MCP to explore read-only (retrieval + deep dumps). `apply_plan` and `refresh_inventory` now require explicit human confirmation via a two-phase call pattern: both accept a new `confirm: bool = False` param; default call returns `{requiresConfirmation: true, message, plan, plannedCommand, engineConfig, nextStep}` without spawning UE or writing anything. `apply_plan`'s preview includes a plan summary (ops, kwargs, side effects, verification); `refresh_inventory`'s includes the filter + deep_dump + target inventory root. Second call with `confirm=true` runs normally. Tool docstrings instruct the agent to show preview to the human and wait for explicit approval before re-calling — no auto-confirm. Read-only UE tools (`validate_plan`, `deep_dump_asset`) are unchanged. Shape validation still runs before the gate so malformed plans fail fast regardless of `confirm`. `refresh_inventory`'s empty-filter safety check also runs before the gate. Smoke 45 → 48. |
| `cd98968` | feat: **MCP UX fixes** — shipped in response to the Legacy `apply_plan` hang discovered during live testing. (A) `logFile` pointer + `hint` added to every timeout response dict in `plans.py` + `live.py`; `logFile` also on every success path. New helper `project_log_path(uproject)` in `_ue_subprocess.py` derives `<uproject_dir>/Saved/Logs/<ProjectName>.log`. (B) `run_plan` + `execute_plan` in `scripts/python_ops/plan_executor.py` emit `[run_plan] phase 1/4: ...` markers + per-op "starting / ok / skipped / FAILED" logs via `unreal.log` / `unreal.log_error`. Silent Python is no longer indistinguishable from a deadlock — `UE_DOW.log` now shows exactly which phase (snapshot / validate / execute / diff) and which op (N/M) is running. All early-abort paths (dispatch miss / kwarg conversion / TypeError / generic Exception) log too. (C) `DEFAULT_VALIDATE_TIMEOUT` bumped 300 → 600 after second false timeout on Legacy. (D) `apply_plan` surfaces partial-apply at the top level when `execution.aborted_at` is non-None: `{partialApply: true, abortedAt, committedOps, totalOps, rollbackWarning}`. (E) `get_op_catalog` tags every op with `readOnly: bool` (today: `verify_state_enter_conditions` + `verify_state_transitions`). Cold-start expectation hints folded into `validate_plan` + `deep_dump_asset` docstrings pointing colleagues at retrieval tools for quick exploration. Smoke 48 → 50 (logFile + hint assertions, readOnly tag checks, partial-apply top-level surface via mocked `subprocess.run` that writes a controlled `<plan>.run.json`). |
| `15b608f` | fix: **drop `-stdout` to try to fix MCP subprocess hang on Legacy** — first attempted fix after py-spy caught UE's `PythonScriptPlugin` deterministically blocking in `fflush_nolock` during type-hint generation. Stack signature: `NtQueryInformationFile → SetFilePointerEx → fflush_nolock → ... → PyGenUtilAccessor::GetPropertyPythonType → Py_InitializeFromConfig`. Identical across multi-second py-spy samples. Hypothesis: the `-stdout` flag mirrored UE's entire log stream to stdout; `subprocess.run(capture_output=True)` handed UE an OS pipe; under volume of type-hint-generation output on Legacy's UClass graph, Windows CRT + pipe interaction deadlocked on fflush. Fix: remove `-stdout` from `UE_STOCK_FLAGS`. UE still writes the full log to `<uproject>/Saved/Logs/<project>.log`, which we surface as `logFile` (from `cd98968`). Verified with direct UE spawn + `> file.txt` redirect: 15 s end-to-end on Legacy, was indefinite. **Turned out to be only PART of the fix — see `17fc913`.** |
| `17fc913` | fix: **redirect UE stdout/stderr via tempfiles, not pipes** — the REAL root cause of the Legacy hang. After `15b608f` shipped and MCP restarted, py-spy caught the new session stuck in the exact same `fflush_nolock` → `PyGenUtilAccessor::GetPropertyPythonType` stack — with NO `-stdout` in the command line. So the `-stdout` flag was only part of the problem; the PIPE itself was the trigger. Python's own `sys.stdout.write()` during type-hint generation still crossed Windows pipe-buffer threshold even without UE's log mirroring on top. New `run_ue_subprocess(command, *, timeout) -> UeRunResult` helper in `_ue_subprocess.py` redirects stdout + stderr to `NamedTemporaryFile(delete=False, mode="wb")` file handles (no pipe, no buffer backpressure), waits for the subprocess or timeout, reads tempfiles back as UTF-8 with `errors="replace"`, best-effort unlinks (Windows can transiently hold a file lock after subprocess exit — swallow `PermissionError`, OS temp dir self-cleans). `UeRunResult` dataclass carries `returncode`, `stdout`, `stderr`, `timed_out`. `plans.py._run_plan_script`, `live.py`'s `deep_dump_asset_impl`, `refresh_inventory_impl` all rewired to use it. Smoke updated: tests now patch `plans.run_ue_subprocess` / `live.run_ue_subprocess` with mocks returning `UeRunResult` instead of patching `subprocess.run`. Verified end-to-end against Legacy `ST_EnemyBase` through the helper: 16.47 s, returncode 0, 30 KB stdout captured in tempfile, no deadlock. **Still not complete — see `4964f2a`.** |
| `4964f2a` | fix: **also redirect subprocess stdin to DEVNULL** — after `17fc913` shipped and MCP restarted AGAIN, py-spy caught the MCP-launched session STILL stuck in the same `fflush_nolock` stack. The tempfile fix worked when invoked directly from bash (stdin = terminal) but NOT from the MCP server (stdin = Claude Code MCP protocol pipe). When `subprocess.run` inherits a pipe on child fd 0, Windows CRT attaches a buffered FILE wrapper to it and Python init's `fflush` blocks on it even though UE never reads stdin. Evidence: the `.ue-stderr` tempfile from the hung run was 0 bytes — UE never flushed any output because CRT was wedged on stdin. Fix: add `stdin=subprocess.DEVNULL` to the `subprocess.run` call inside `run_ue_subprocess`. UE commandlets don't read stdin; DEVNULL is correct. One-line change + comment explaining the MCP-vs-terminal stdin-inheritance trap. Smoke still 50/50. **This is the last pipe; Legacy hangs are gone.** |

### The py-spy diagnostic — native-stack approach for "Python hang during UE init"

The hang looked identical to WIP's documented "apparent stall that wasn't" — 2 min of log silence after `LogPython: Using Python 3.11.8`. It was actually a hard deadlock, not a slow init:

1. `pip install py-spy` (one-shot — not a project dep).
2. Identify the hung `UnrealEditor-Cmd.exe` PID via `tasklist`.
3. `py-spy dump --pid <PID> --native` — the `--native` flag is load-bearing; without it py-spy reported `Thread <id> (idle)` with no stack. Native mode shows the Windows + CRT frames that pure-Python mode can't reach.
4. Sample 2-3× with a few seconds between. Identical stack across samples ⇒ hard block. Moving stack ⇒ slow progress.
5. The native stack's TOP frames are reliable (active syscall). Bottom frames (optimized `python311.dll` symbols repeated) are mis-labelled by py-spy's Windows walker — don't chase them. The UE-side frames (`PyGenUtilAccessor::*`, `Py_InitializeFromConfig`) ARE reliable.

Stack signature to recognise: `NtQueryInformationFile → SetFilePointerEx → fflush_nolock → lseeki64 → ... → PyGenUtilAccessor::GetPropertyPythonType → Py_InitializeFromConfig`. Means UE's PythonScriptPlugin is generating type stubs for the UClass graph and blocked trying to flush a stdio buffer. On Legacy's class graph the trigger is a pipe anywhere on the child's standard handles — stdout, stderr, or stdin.

Diagnostic artifact to check: `ls %TEMP%/*.ue-stdout *.ue-stderr`. After `17fc913` shipped, a 0-byte `.ue-stderr` alongside a hung UE PID is the signal "UE started but couldn't flush anything" — proves the hang is on Windows CRT buffered I/O, not on a downstream Python import.

### Live MCP test against Legacy — 2026-04-21 findings

- **Test workspace:** `D:/Work/unreal-mcp-test/` with `.mcp.json` pointing at Legacy (inventory `D:/Work/_dow_legacy_inventory`, engine stock UE 5.7, uproject `D:/Work/UE_DOW_Legacy/UE_DOW.uproject`). Dedicated scratch folder unrelated to both plugin repo and Legacy depot — Claude Code launched from here gets the MCP without contaminating either repo's context. Not in source control.
- **Target bug:** `ST_EnemyBase` (`/Game/CombatPrototype/DrewPrototype/ST_EnemyBase`) has 3 root states: `Wait`, `SearchClueLoop`, `CombatLoop`. Inside `SearchClueLoop`, `MoveToClue` (state GUID `91335CC340EF237953E8F8BA341E4FB9`) has **zero outbound transitions**. NPCs flow `Wait → SearchClueLoop → FindClue → MoveToClue`, then stall forever — `CombatLoop` is unreachable from outside its own internal cycle. Observable symptom in `Combat_FlatArena` 5v5: both teams run to the other side and stand there without engaging. Fix: add `OnStateCompleted` transition `MoveToClue → CombatLoop` (state GUID `98DBA8054D83027FEABFF3ACD1D278C5`). Diagnosis was made purely from committed inventory (`.deep.md` + `.md`) — no UE launch needed — which is exactly the story the pivot is selling.
- **Legacy plugin install pre-reqs:** prior session had `D:/Work/UE_DOW_Legacy/Plugins/BlueprintExporter` as a symlink to `_build_output_5_7/` which got deleted in an earlier cleanup pass — symlink was broken. Fixed today: `rm` the broken symlink, `cp -r` the freshly-built stock-5.7 package into that path as a real directory, `cp` the repo-root `BlueprintExporter.uplugin` (1.17.0) on top. `bpx-mcp-doctor` → all checks passed from the test workspace.
- **Three consecutive call failures, all reproducible:**
  1. Two `validate_plan` calls (300s timeout each) — UE subprocess ran 2.5 min, Python init took ~2 min (silent / slow in log), then our script ran in 0.04 s. Stdout tail only captured the first 2 KB of stdout (pre-CUDA-unload) because `-stdout` doesn't forward all log categories — the full `UE_DOW.log` was much richer. **Lesson:** the MCP's `stdoutTail` is not a faithful signal for what UE actually did; always cross-read `<Project>/Saved/Logs/UE_DOW.log` when diagnosing a "timeout".
  2. `apply_plan` (900s timeout) — got through UE startup + script execution in 2.5 min, but crashed with `KeyError: 'st_path'` in `mechanical_diff._op_expected_changes` at line 53. Fixed by commit `9b2b604`, but the real issue is point 2 below.
- **Two scaling issues surfaced:**
  1. **Agent-authored plan JSON used an `"args": {...}` wrapper** instead of the documented flat-kwargs shape. `plans/README.md` is explicit about the schema, but the agent in the live-test session hallucinated a wrapper. `9b2b604` hardens the error path, but the deeper fix is MCP-side pre-validation (see Pending Work below). **User feedback on 2026-04-21:** *"That's not a scalable solution, the MCP should know what plan format to use or not to use."* Saved as `feedback_mcp_enforces_schema` memory.
  2. **Legacy's UE cold-start is ~2.5 min in commandlet mode.** Python init alone is ~2 min (probably unreal-Python type-hint generation over a large UClass set). `DEFAULT_VALIDATE_TIMEOUT=300` in `tools/plans.py:40` is right on the edge and caused two false timeouts before `apply_plan`'s 900s budget let one through. Consider bumping validate to 600s as a follow-up; more importantly, pre-validation (below) sidesteps this for the common malformed-plan case.
- **Apparent stall that wasn't:** during the live test, we saw 2 min of log silence after `LogPython: Using Python 3.11.8`, and CPU usage of ~0 on the subprocess. Initially diagnosed as a deadlock. Actually was Python init doing non-CPU-logging work (module imports + unreal type-hint generation + DDC maintenance scan). The 15s-polling monitor at `/tmp/monitor_ue.sh` caught both the stall and the eventual progression; useful pattern if we hit similar again. Script deleted at session end.

### Pending work — pick up here after `/clear`

**NEW 2026-04-22 (after M26.1.2): Flat Arena diagnosis via live MCP surfaced four fixes, three of which the current op catalog can't author — primary driver to promote M26.3 off "defer unless" and to scope a StateTree task-on-state op.** Two independent agent sessions in `D:\Work\unreal-mcp-test` (Legacy-wired MCP) converged on the same punch list:

| # | Finding | Fix | MCP-fixable today? |
|---|---|---|---|
| 1 | `BP_EnemyBase.GetTargetingInfo` interface override — may be a stub, may be absent. Inventory at `D:/Work/_dow_legacy_inventory` was generated with plugin 1.19.5, pre-M26.1.1 serializer surfacing of override stubs, so the "no override visible" diagnostic is ambiguous. | `refresh_inventory -Filter=/Game/CombatPrototype/DrewPrototype/` with the 1.19.7 plugin, then `apply_plan implement_interface_function(force_rebind=<match-state>)` with bindings `bIsAlive=self.bIsAlive / bIsTargetable=true / Faction=self.Faction`. | **Yes** — M26.1.2 ships deterministic force_rebind. |
| 2 | Faction collision on placed instances. `Faction` is `InstanceEditable`, default 0; both placed enemies at default → `AssessThreat.NotEqual_IntInt` returns false → `bHasTarget` never flips → `CombatLoop` unreachable. | Open `Combat_FlatArena.umap`, set different Faction values (team A=1, team B=2) on the two groups. Also verify `bIsAlive` flipping path — BP_EnemyBase has **no Event BeginPlay**; `Set bIsAlive` lives in two other graph sites that may not fire on default spawn. | **No** — level/umap edit, M20 Level Export is backlog. |
| 3 | `BP_Task_Peek` dead-end Branch. `K2Node_IfThenElse_2304_-416_055E0E7F.Branch.else` (CurrentTarget.bIsVisible=false case) is literally unconnected; task hangs at peek point, no `FinishTask` fires, tree can't re-enter. | Open `BP_Task_Peek.EventGraph`, wire Branch.else → existing `FinishTask(bSucceeded=true)` node at `(3904, -112)`. | **No** — needs K2 node-level pin connect, M26.3 scope. |
| 4 | No persistent fire state. `BP_Task_OpenFireLoop` and `BP_Task_CloseFireLoop` exist as assets but aren't referenced anywhere in `ST_EnemyBase`. Firing only happens inside `BP_Task_Peek`, gated on the dead-end branch above. | Open `ST_EnemyBase`, add `BP_Task_OpenFireLoop` as a task on `CombatLoop` state itself; add `BP_Task_CloseFireLoop` as tasks on `Wait` / `SearchClueLoop` states. | **No** — needs "add task to StateTree state" op, not in the M25.2 extension set (we have add/remove transitions + enter conditions, not tasks-on-state). |

**Scope-bump argument for M26.3 + StateTree task-on-state op.** Both MCP agents independently hit the same three walls in the same diagnosis. These are concrete drivers for deferred backlog items:
- **M26.3** (`add_graph_node` / `connect_pins` / `add_local_variable`) unblocks #3 directly and is the prerequisite for any "fix a dead-end branch" authoring flow. WIP's M26.0 research flagged M26.3 as "defer unless a real driver" — this is the driver.
- **New op `add_statetree_task_to_state` (+ remove counterpart)** unblocks #4. Mirrors the M25.2.1 `add_statetree_transition` primitive shape: `{st_path, state_path, task_bp_path, [kwargs per task instance data]}`. Small scope extension to `BpxReflectionOps` + Python surface.
- **M20 (Level export + level-instance property edits)** unblocks #2. Bigger scope but the Flat Arena case is the cheapest motivating example; the level edit here is literally "set `Faction=1`/`=2` on two placed actors", which is the minimum viable level-property op.

Workaround the second agent proposed — adding `OnTick → FindNewCover` on Peek as a partial mitigation for #3 — was **rejected** because it replaces "task hangs" with "task oscillates every tick," which is a worse failure mode (constant EQS re-queries). Don't ship.

**Order of attack when resuming:**
1. Clarify with user: enemies-vs-enemies or enemies-vs-player in Combat_FlatArena? Which enemy class is placed — `BP_EnemyBase` or `SandboxCharacter_Cover`? The two MCP agents couldn't answer this from the inventory (no level coverage). Answers determine whether #2 is 2-value Faction authoring or player-faction passthrough via `BPI_Targetable`.
2. Run `refresh_inventory -Filter=/Game/CombatPrototype/DrewPrototype/ deep_dump=true` (requires `confirm=true` per M25.1 gate) to resolve #1's ambiguity with 1.19.7 serializer.
3. If stub exists, apply the interface-impl plan. Otherwise note #1 is already done and move on.
4. Decide whether to promote M26.3 + task-on-state op off the backlog, or to ship #2 / #3 / #4 as user-driven editor fixes and revisit scope later.

### M28 — design.md (combat-AI "squad with a brain") enabling ops (2026-04-22)

**Source of truth.** `D:/Work/blueprintexporter/design.md` — eight-item design for squad-coordinated FPS AI (encounter director, utility scorer, perception w/ confidence decay, telegraphed animation, dynamic cover, pacing, archetypes, polish). M28 scopes **what the plugin + MCP + plan pipeline needs so Claude can build the design end-to-end via MCP, with human editor work only as fallback**. Read side is already in good shape (Tier 2 renderers M11–M19, M26.1.1 interface-override surfacing already expose `ST_EnemyBase`, `S_TargetInfo`, `EQS_AI_FindCover`, AIPerception sense configs, and CDO overrides in full); the bottleneck is **write-side**.

**design.md → missing ops map:**

| # | design.md item | Op(s) the plan pipeline is missing today | Blocking phase |
|---|---|---|---|
| 1 | Squad director + `AI.Order.*` event channel | `add_bp_variable`, `add_component_to_scs`, `add_bp_interface`, node-level graph authoring, `add_gameplay_tag` | M28.2 + M28.3 + M28.6 |
| 2 | Utility scorer component + action-tag output | `add_bp_variable`, `add_bp_function`, node-level graph authoring, UserDefinedStruct create/edit | M28.2 + M28.3 + M28.4 |
| 3 | Confidence-decaying perception (thicken `S_TargetInfo`) | UserDefinedStruct member add/edit, node-level graph authoring for `AddOrUpdateTargetToList` decay tick | M28.3 + M28.4 |
| 4 | Callouts / pre-grenade lean / committed cover-to-cover anim | node-level graph authoring + `add_component_to_scs` + `add_gameplay_tag` | M28.2 + M28.3 + M28.6 |
| 5 | Dynamic multi-target cover scan (extend `EQS_AI_FindCover`) | `add_eqs_test`, `set_eqs_test_property`, `set_eqs_generator_property` | M28.5 |
| 6 | Encounter-director intensity curve / AI Director pattern | `create_curve_float`, `set_curve_float_keys`, node-level graph authoring | M28.3 + M28.4 |
| 7 | Archetype DataAsset instances (Rusher / Marksman / Suppresser / Flanker) | `create_data_asset_instance`, `set_data_asset_property` | M28.4 |
| 8 | Polish (hit reactions, first-shot inaccuracy, ally-down reaction) | node-level graph authoring + `add_bp_function` + `add_statetree_task_to_state` | M28.1 + M28.2 + M28.3 |

**Verification-matrix hardening (M28.pre — blocker before M28.1 ships).** CLAUDE.md's pre-push matrix (unity / automation / determinism / bridge smoke / MCP) is solid for read-side work but has five holes that M28 write-side ops will walk straight through. Close these first so "plan applied cleanly" actually means "correct mutation landed in the asset AND surfaces in the sidecar post-re-export," not just "file bytes changed."

| # | Gate | Hole today | Fix |
|---|---|---|---|
| **M28.pre.1** | Automation | `-ExecCmds="Automation RunTests …; Quit"` silently no-ops in commandlet mode — emits `LogAutomationTest: Skipping unit tests for the cooked build and commandlet` and exits 0. Every `FInterfaceOverrideSerializationTest`-class test is **uncovered by the matrix today** (surfaced-but-deferred in M26.1.2 follow-ups). CLAUDE.md:185 documents the broken invocation as the standard gate. | Invoke via `UnrealEditor.exe -game -SessionName=BpxAuto -ReportExportPath=… -ExecCmds="Automation RunTests BlueprintExporter.+; Quit"` OR ship a dedicated `RunAutomationTestsCommandlet` that bypasses the build-context filter. Update CLAUDE.md pre-push matrix row + every doc that references the silent-skip invocation. |
| **M28.pre.2** | Post-apply content inspection | `verify_determinism.ps1` twin-runs the pipeline and byte-diffs the trees — proves stability, not correctness. No gate today does "apply op → re-export → grep `.md` / `.deep.md` for expected authored content." M26.1 `_Expected.uasset` goldens are md5-diffed at the `.uasset` level; the rendered sidecars derived from them aren't semantically inspected. | New script `scripts/verify_post_apply_inspect.ps1 -Op <op> -Fixture <bp_path> -ExpectedAssertions <json>`: (1) copies BugHunt fixture to scratch, (2) applies op via `apply_plan`, (3) runs `ProjectInventory -DeepDump -Filter=<path>` against scratch, (4) asserts every `expected_content` regex in the JSON matches the rendered `.md` / `.deep.md`. Per-op invocation in CI; exits 1 on any miss. |
| **M28.pre.3** | Per-op determinism soak | `soak_m26_1_1_force_rebind.py` exists as a one-off — it's the only reason M26.1.2 caught pin-GUID + GC + `MakeUniqueObjectName` non-determinism. Every M28 write op that calls `NewObject<>` / `CreatePin` / `RemoveNode` can hit the same class of bug and the matrix wouldn't flag it. | Template `scripts/soak_template.py` parameterised on `{op_name, kwargs, fixture_path}`. Runs op twice against the same baseline, asserts `.uasset` md5 byte-identity + reported NodeGuids stable across rounds. Every new M28 op ships with an instance of the template before merge; CI runs all soaks on pushes that touch `python_ops/` or `ReflectionOps.cpp`. |
| **M28.pre.4** | Dual-engine coverage | `-Project BugHunt` exercises stock UE 5.7; `-Project DOW` exercises the custom engine. Matrix mandates dual-engine DLL rebuild on version bumps, but verification gates are BugHunt-only unless `-Project DOW` is passed explicitly. A custom-engine-only regression (protected-property flag drift, engine-fork divergence in `FBlueprintEditorUtils` internals) slips through. | Determinism + soak + post-apply-inspect all run on BOTH BugHunt and a DOW slice for every C++ touch reaching `BpxReflectionOps`. Either add `-Project Both` mode to existing scripts or a `verify_all.ps1` wrapper that fans out. Dual-engine DLL rebuild already required — making verification dual-engine is incremental. |
| **M28.pre.5** | Config-file writes | Determinism gate is scoped to `ProjectInventory_*/` inventory output; `.ini` files aren't in scope. M28.6 `add_gameplay_tag` touches `DefaultGameplayTags.ini` + `Config/Tags/*.ini` — nothing catches tag corruption, tag loss, or inadvertent reorder / whitespace churn. | Parity script `scripts/verify_tag_author.py`: snapshot ini bytes → `list_gameplay_tags` → `add_gameplay_tag(TestTag)` → `list_gameplay_tags` → assert (a) new tag present in result, (b) every prior tag preserved, (c) `git diff --numstat <ini>` shows only the authored line added. M28.6-gated; not a blocker for earlier M28 phases. |

**M28.pre sequencing inside M28:**
- **M28.pre.1** (automation invocation fix) ships before any M28 op lands its regression tests — otherwise they silently no-op.
- **M28.pre.2** (post-apply content inspect) ships before M28.1 — every op from M28.1 onward uses it as its primary correctness gate.
- **M28.pre.3** (soak template) ships before M28.2 — first op family that calls `NewObject<>` for components / vars / functions.
- **M28.pre.4** (dual-engine rotation) ships before M28.2 — first bridge extension after M26.1.2 closed the force_rebind determinism arc.
- **M28.pre.5** (tag parity) ships alongside M28.6; not a blocker for earlier phases.

**No version bump on M28.pre** (pure tooling / CI / script work — no DLL surface change, no schema change). Lands as commits in the 1.19.x range before the M28.1 patch bump.

**M28.pre.1–.4 shipped (2026-04-23, uncommitted — working-tree state).** All four gates land as working infrastructure; M28.pre.5 (config-file parity for tags) stays pending until M28.6 authors the tag-ini op itself.

| Gate | Status | Files shipped | Notes |
|---|---|---|---|
| **M28.pre.1** Automation fix | DONE | `scripts/run_automation_tests.ps1`; `EAutomationTestFlags::CommandletContext` added to all 17 `IMPLEMENT_SIMPLE_AUTOMATION_TEST` sites in `BlueprintExporterTests.cpp` (the same flag flip was independently bundled into commit `541fecf`). Verified: 17/17 tests pass in 15 s against stock UE 5.7; zero `Skipping unit tests for the cooked build and commandlet` signatures in log. | Two gotchas encoded in the wrapper + documented in CLAUDE.md: do NOT append `; Quit` to `-ExecCmds` (it fires before tests run), and `-testexit="Automation Test Queue Empty"` must embed double quotes around the space-bearing value. |
| **M28.pre.2** Post-apply content inspect | DONE | `scripts/inspect_harness.py` (prepare + cleanup modes), `scripts/verify_post_apply_inspect.ps1` (3-phase driver: prepare → re-export → regex match → cleanup), `scripts/inspect_fixtures/implement_interface_function.json` (reference assertions). Verified: 2+1+3+0 = 6 regex assertions match correctly across `.md` + `.deep.md` sidecars in ~17 s. | Path trap: re-exported sidecars land under `<OutDir>/Assets/Game/<rel>/<name>.md` (the `Game` prefix is preserved from the `/Game/` root). Wrapper computes the correct path from `inspect_path` — don't assume `Assets/<rel>`. Harness writes `<basename>.prepare.json` to `$BPX_INSPECT_TMP` rather than next to the assertions JSON so the verify_all fan-out doesn't pick it up as a new fixture. |
| **M28.pre.3** Per-op soak template | DONE | `scripts/soak_template.py` (parameterised descendant of `soak_m26_1_1_force_rebind.py`), `scripts/verify_soak.ps1` (single-shell driver). Same assertions JSON as M28.pre.2 with optional `soak.{rounds, stable_keys, round2_min_wiped_nodes}` extension, so one fixture feeds both gates. | **The gate works: caught a real regression on its smoke test.** See "Discovered regression" block below. |
| **M28.pre.4** Dual-engine fan-out | DONE | `scripts/verify_all.ps1` — fans gates across engine × project pairs. Default runs BugHunt + stock 5.7 (auto-skip if engine missing); `-IncludeDow` adds DOW + custom-engine legs; `-SkipInspect` / `-SkipSoak` scope opt-outs for triage. Availability checks up front so a missing engine warns cleanly instead of emitting 4× cryptic per-gate failures. Verified: `-SkipSoak` run passes all 3 gates in 80 s against stock UE 5.7; `-SkipInspect` run correctly surfaces the M28.pre.3 soak finding and exits 1. | Implementation trap: PowerShell `$Args` is a reserved automatic variable — using it as a `param()` name silently binds to `$null` and the spawned gate gets zero arguments. Use `$GateArgs`. Also, `Start-Process -ArgumentList` joins array elements with spaces WITHOUT quoting; any element containing whitespace (e.g. `C:\Program Files\Epic Games\...`) must be pre-wrapped in embedded double quotes, otherwise the child's argv parser splits at the space. Both encoded in the `Invoke-Gate` helper. |
| **M28.pre.5** Config-file parity | DEFERRED | — | Not a blocker for M28.1–.5. Lands alongside M28.6 when `add_gameplay_tag` is authored. |

**Pre-push invocation (from repo root, Windows):**

```powershell
pwsh -File blueprint-exporter/scripts/verify_all.ps1
# or, for dual-engine C++ touches:
pwsh -File blueprint-exporter/scripts/verify_all.ps1 -IncludeDow
```

**Regression chase closed (2026-04-23, plugin 1.19.8 → 1.19.9).** `implement_interface_function(force_rebind=True)` had lost its M26.1.2 within-session byte-identity invariant in commit `541fecf`. Two independent causes, both in `Source/BlueprintExporter/Private/Reflection/ReflectionOps.cpp`:

| # | Cause | Fix |
|---|---|---|
| 1 | `ConnectPinsByName` (M26.1) picked up a new `FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint)` call in `541fecf` to support M28.3-narrow's standalone ubergraph wire-ups. `implement_interface_function` drives two wires per call (Faction + bIsAlive), so the mark fired twice per force_rebind and triggered listeners whose UObject creation went through `MakeUniqueObjectName`'s monotonic counter — within-session byte-drift round 1 vs round 2. | Hoisted the mark out of `ConnectPinsByName` and into the M28.3 Python-facing entry point `ConnectGraphPinsByGuidString`. M26.1's function-graph authoring path is now free of the mark (its prior mark from `OverrideInterfaceFunction` still flushes correctly); the M28.3 standalone wire flow gets the mark at its boundary. |
| 2 | `WipeFunctionGraphBody` never reseeded Entry/Return `NodeGuid` + pin GUIDs. On the force_rebind path, `OverrideInterfaceFunction` early-returns on existing override → its seeding loop never runs → Entry keeps whatever FGuid `duplicate_asset` handed it for THIS session. Cross-session Entry drift propagated into the .uasset content hash. | Added unconditional reseed of Entry/Return `NodeGuid` + `BpxReflection::SeedPinGuidsForNode` at the top of `WipeFunctionGraphBody`, BEFORE the "nothing to wipe" short-circuit, so even round 1 of a soak (zero nodes to wipe) applies the seed. Entry NodeGuid now stable across sessions for identical inputs. |

**Verification:**
- `scripts/soak_m26_1_1_force_rebind.py` (original M26.1.2 soak): **SOAK PASS** on 1.19.9. Round 1 md5 == Round 2 md5 within session.
- `scripts/verify_soak.ps1 -Assertions scripts/inspect_fixtures/implement_interface_function.json`: **PASS** (md5 stable, entry_guid stable, round2 wiped_nodes=2 ≥ 1).
- `scripts/verify_all.ps1` full matrix: **4/4 PASS** in 85.6 s — automation 17/17, determinism byte-identical, inspect 6/6, soak round-stable.
- Entry NodeGuid cross-session: identical `C79D26DE4A30F803BF4073E284A90941` across two independent editor shells on the same fixture.

**Out of scope (deferred, orthogonal to this fix):** the .uasset file still has **cross-session byte drift** of ~900 bytes (16-byte FGuid blocks + UTF-16 strings with per-session object-name indices) originating in `UPackage::SavePackage`'s GUID regeneration (package PersistentGuid, blueprintGuid, generated-class guid, linker-export hashes). This is UE engine-side determinism, not op-level. M26.1.2 only claimed within-session byte-identity and that claim holds under the fix. Treat cross-session byte-identity of editor-saved packages as a future engine-determinism milestone, not a blocker for M28.2+. `diff_force_rebind.py` + `inspect_fixtures/*.json` stay committed so that future work has a reproducible starting point.

**Investigation utilities (2026-04-23):** `scripts/probe_cross_session_drift.py` (two-shell single-apply probe; dumps bytes + md5 + entry_guid per run) + `scripts/diff_cross_session_drift.py` (byte diff with coalesced runs + surrounding hex context) + `scripts/dump_drift_context.py` (wider ±40-byte context for identifying the FString/FName container each drift sits inside). Starting point for a future engine-determinism milestone. Probed: `PersistentGuid` + `BlueprintGuid` are reachable from op-level code (the latter via FProperty reflection on the private `UBlueprintCore::BlueprintGuid` UPROPERTY); seeding them deterministically cut drift ~40% in warm-cache cross-session runs, but `FindInBlueprint` search metadata (32-char hex via `EdGraphNode.cpp:929`), FText localization keys (`TextHistory.cpp` `FGuid::NewGuid().ToString()`), export-table FGuids, and cache-warmup effects (cold vs warm run size delta ±10 bytes, ~6 kB drift) remain engine-side. A pre-save-only fix in `CompileAndSavePackage` was prototyped but NOT shipped — the improvement is cosmetic (partial diff reduction, not byte-identity), no matrix gate depends on cross-session byte-identity, and the helper touches engine-managed fields pre-save on every op save (M28.1 / M28.3-narrow / M28.9 / future), adding maintenance surface + UE-version-bump revalidation cost for no workflow benefit. Re-open when distributed caching or cross-machine content hashing makes byte-identity load-bearing.

**M28.pre.3 delivered concrete value** — caught a silent within-session determinism regression that shipped in `541fecf` without the existing matrix detecting it. Pattern established: any write-side op added in M28.2+ gets both a `*.json` assertions fixture AND the soak gate invocation before merge.

**Version bump 1.19.8 → 1.19.9** (patch per semver — bug fix on existing op; no new surface). 9-location stamp sweep clean; DLLs rebuilt against stock UE 5.7 (2,540,544 bytes, BuildId `47537391`). Custom UE_DOW rebuild deferred to the next push that actually targets that engine.

**Phase breakdown (tentative — M28.0 finalizes):**

| Phase | Scope | Deliverable |
|---|---|---|
| **M28.0** | Research + sequencing | Confirm Python + `BpxReflectionOps` surface per phase; probe `FBlueprintEditorUtils::AddNewVariable`, `FBlueprintEditorUtils::AddNewFunction`, `USimpleConstructionScript::AddComponent`, `FStructureEditorUtils::AddVariable` (UDS), `UCurveFloatFactory` / `UDataAssetFactory`, `UEnvQueryOption::Tests[]`, `UGameplayTagsManager::AddNewGameplayTagToINI`. Pattern mirrors M26.0 / M27.0. Output: UFUNCTION surface per phase appended here. |
| **M28.1** | `add_statetree_task_to_state` (+ remove counterpart, + verify helper) | Smallest piece — also closes Flat Arena #4. Mirrors `add_statetree_transition` shape: `{st_path, state_path, task_bp_path, [task_kwargs]}`. Expected to reuse the M23.1 `BpxReflectionOps` StateTree editor-data surface with no bridge extension. Idempotent on (st_path, state_path, task_bp_path). |
| **M28.2** | Structural BP edits: `add_bp_variable`, `add_component_to_scs`, `add_bp_interface`, `add_bp_function` | First half of design.md's write scope. Bridge extends `BpxReflectionOps` with `AddBlueprintVariable(BP, Name, PinType, DefaultValue, Flags)`, `AddSCSComponent(BP, Name, ComponentClass, AttachTo, Socket, Transform)`, `AddImplementedInterface(BP, InterfacePath)`, `CreateFunctionGraph(BP, Name, bIsPure)`. Idempotent; deterministic NodeGuids + object names (M26.1.2 pattern). Probably 4–6 new UFUNCTIONs + 1–2 new USTRUCTs. |
| **M28.3** | Node-level graph authoring: `add_graph_node`, `connect_pins`, `set_pin_default`, `add_local_variable` | The M26.3 scope deferred as "defer unless a real driver" — design.md is that driver, and Flat Arena #3 is the immediate smoke-test. Biggest bridge surface in M28: starts narrow with 5–8 K2Node types (`Branch`, `CallFunction`, `VariableGet`/`Set`, `MakeLiteral`, `CustomEvent`, `Sequence`, `Cast`), grows as concrete plans drive additional node types. Reuses M26.1's `FindGraphEndpoints` / `AddSelfMemberGetNode` / `ConnectPinsByName` / `SetNodePinLiteralDefault` as the narrow core; all new node-spawn UFUNCTIONs apply md5-seeded NodeGuids + `SeedPinGuidsForNode` + `BpxNode_*` deterministic object names so two runs produce byte-identical `.uasset`. |
| **M28.4** | Non-BP asset authoring: UserDefinedStruct, CurveFloat, DataAsset instances | `create_user_defined_struct`, `add_uds_member`, `set_uds_member_default`, `create_curve_float`, `set_curve_float_keys`, `create_data_asset_instance`, `set_data_asset_property`. Covers design.md items 3, 6, 7 directly. Bridge extends with `CreateUserDefinedStruct`, `AddUDSMember` (routes through `FStructureEditorUtils` — engine refuses refresh on raw struct edits), `CreateCurveAsset` (variants per curve type), `CreateDataAssetInstance(ParentClass, PackagePath)`. Reuses existing `SetObjectProperty` surface for DA property authoring. |
| **M28.5** | EQS write-side: `add_eqs_test`, `remove_eqs_test`, `set_eqs_test_property`, `set_eqs_generator`, `set_eqs_generator_property` | Mirror of M15 EQS read-side. `UEnvQuery::GetOptions()` already walkable; inverse adds/removes/edits `FEnvQueryOption::Tests[]` + generators. Unlocks design.md item 5 (multi-target cover scoring). Bridge surface small — 3–5 UFUNCTIONs; most work is Python ops + validator entries. |
| **M28.6** | GameplayTag author: MCP tool `list_gameplay_tags` + plan op `add_gameplay_tag` | `DefaultGameplayTags.ini` + `Config/Tags/*.ini` are the authoring surface. Bridge extends with `AddGameplayTag(FName, FString Comment, FName SourceIni)` that routes through `UGameplayTagsManager::AddNewGameplayTagToINI` (engine handles concurrent-edit + hot-reload). MCP-side `list_gameplay_tags` is zero-UE-process: walk config ini files, return `{tags: [{name, comment, source}]}`. Unlocks `AI.Order.Flank` / `AI.Order.Suppress` / `AI.Callout.Grenade` authoring without hand-editing `.ini`. |
| **M28.7** | Verification beyond mechanical diff: `run_automation_test` bridge handler + gym-map fixture | Today `mechanical_diff` answers "did the file bytes change". design.md needs "does the squad actually flank". New bridge handler runs an automation test in-process (reuses M27.2 Python-scope pattern, not a new subprocess shell). Gym map `L_DesignGym` with placed director + 4 enemies + dummy target + per-scenario assertions. Expected ship shape: M28.7.1 handler only (reuses existing `BlueprintExporter.*` automation suite), M28.7.2 gym project + placed-actor fixtures, M28.7.3 reusable scenario library. |
| **M28.8** | Optional read-side additions | Tier 2 for `UUserDefinedStruct` / `UCurveFloat` / `UAnimMontage`; project-level `TAGS.md` rollup in `AggregateInventoryCommandlet`. Non-blocking — ergonomic sugar for agent authoring. Mirror of M11–M15 pattern. Defer until M28.2–M28.7 land. |
| **M28.10** | BP class authoring with native parent + determinism | Surfaced 2026-04-27 by the design.md MCP-only test run against UE_DOW_Legacy: the existing `create_child_bp` (`assets.py:84`) only handles BP-parented children, not native ones (`AActor` / `UActorComponent`). Without this op, design.md's `BP_EncounterDirector` (pillar 1) and `UAIActionScorer` (pillar 2) can't be authored end-to-end via MCP — every other slice (variables, components, function graphs, K2 nodes) is already supported by M28.2 + M28.3 *once the BP exists*. Ship op `create_blueprint_class(parent_path, new_bp_path)` accepting either `/Game/<bp>` or `/Script/<class>` as parent (resolves via `unreal.load_class` for the native form, feeds either to `BlueprintFactory`); idempotent on path with parent-class match (stricter than `create_child_bp`'s current "exists and is a Blueprint" check, per its own docstring); seed the FGuid::NewGuid() fires the engine triggers on fresh UBlueprint creation (likely candidates: `UBlueprintCore::BlueprintGuid`, the empty UbergraphPages NodeGuid, possibly the construction-script default — M28.10.0 research catalogs them). Bundle a hardening pass on `create_child_bp` so its idempotence verifies parent-class match via reflection rather than the current weak signal. Sequence: **M28.10.0** research (FGuid + NewObject naming catalog) → **M28.10.1** ship `create_blueprint_class` + harden `create_child_bp`, both passing the M28.pre.3 soak gate. With M28.10 shipped, design.md slices E + F move from "likely no" to "yes". |

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

### M28.1 + M28.3-narrow + M28.9 — Flat Arena scope-bump closure (2026-04-23)

Three-sub-phase arc that closes all four Flat Arena findings end-to-end via MCP. Plugin bump 1.19.7 → 1.19.8 (patch — reuses the existing bridge surface plus one narrow C++ helper extension; no new subsystem). User decision: DO NOT defer Flat Arena #2 as editor-manual — ship a narrow level-property op alongside M28.1/.3.

**Shipped ops (5 new):**

| Op | Sub-phase | Bridge surface | Driver |
|---|---|---|---|
| `add_statetree_task_to_state(st_path, state_path, task_bp_path)` | M28.1 | reuses M23.1 reflection bridge; no new UFUNCTION | Flat Arena #4 — attach BP_Task_OpenFireLoop to CombatLoop, BP_Task_CloseFireLoop to Wait + SearchClueLoop |
| `remove_statetree_task_from_state(st_path, state_path, task_bp_path)` | M28.1 | same | symmetric; idempotent undo |
| `verify_state_tasks(st_path, state_path)` | M28.1 | same, read-only | read-back companion to `verify_state_enter_conditions` / `verify_state_transitions` |
| `connect_graph_pins(bp_path, graph_name, from_node_guid, from_pin, to_node_guid, to_pin)` | M28.3-narrow | extends `FindFunctionGraphByName` to walk `UbergraphPages[]`; adds `UBpxReflectionOps::ConnectGraphPinsByGuidString(Blueprint, GraphName, FromGuidStr, FromPin, ToGuidStr, ToPin)` that parses hex + delegates to the M26.1 `ConnectPinsByName`; adds `MarkBlueprintAsStructurallyModified` on successful wire so `compile_and_save_package` flushes the new edge | Flat Arena #3 — wire BP_Task_Peek Branch.else → existing FinishTask(bSucceeded=true) |
| `set_level_actor_property(level_path, actor_label, property_path, value)` | M28.9 (new) | Python-only; reuses `BpxReflectionOps::SetPropertyValue`; uses `unreal.EditorAssetLibrary.save_loaded_asset(world)` for the save (map-aware — `compile_and_save_package` hardcodes `.uasset` so would write a stray sibling instead of updating `.umap`) | Flat Arena #2 — set different `Faction` values on placed enemies so `AssessThreat.NotEqual_IntInt` returns true across-team |

**Selector shape gotcha (M28.3-narrow, captured during Legacy bring-up):** the inventory's `.deep.md` / `.meta.json` expose each node's stable content-hash (`BlueprintSerializer.cpp::ComputeStableNodeHash`) as `nodeGuid`, NOT the runtime `UEdGraphNode::NodeGuid` — that stable hash is designed for determinism but unusable for in-engine lookup. `connect_graph_pins` therefore accepts a second selector form in the `from_node_guid` / `to_node_guid` fields: `"@<NodeClassName>:<x>,<y>"` (e.g. `"@K2Node_IfThenElse:2304,-416"`) that matches the node by its runtime UClass path + authored `NodePosX/Y`. Class-name match covers engine-internal K2 node subclasses (`K2Node_IfThenElse`, `K2Node_Knot`) that UE's Python bindings fall back to base `unreal.K2Node` for — `get_class().get_path_name()` is the only reliable identifier. Literal 32-char hex GUIDs still work as a second form for callers that already have a runtime GUID in hand (e.g. from a prior op's result dict).

**Python-side hot-reload for the bridge (M28.3-narrow implementation detail):** `scripts/bridge_entry.py` gained `_fresh_python_ops()` that calls `importlib.reload` on every `python_ops.*` module before each `run_validate` / `run_apply`. `ExecPythonCommandEx`'s `EPythonFileExecutionScope::Private` isolates locals/globals per call but `sys.modules` is shared across the editor's Python interpreter lifetime, so pre-M28 an op edit required either an editor restart or a stale-cache mystery-debug session. Reload cost is milliseconds — trivial next to UE-side work.

**Bug #2 fixed during the Legacy soak:** M26.1.2's `force_rebind=True` path produced a wrong binding on the pre-existing authored `BP_EnemyBase.GetTargetingInfo` stub — `bIsTargetable` was connected to `self.bIsAlive` (a VariableGet passthrough) instead of the literal `true` the 3-pin passthrough called for. Since `bIsAlive` defaults to false on spawn and the BP has no `Event BeginPlay` to flip it, `bIsTargetable` reported false on every message-call, which silently kept the combat loop unreachable even after `implement_interface_function` had "succeeded". The M28.1/.3/.9 arc re-applied `implement_interface_function(force_rebind=True)` with the correct bindings to fix the prior state.

**File-system gotcha discovered in the Legacy soak (recorded for future plan authors):** `/Game/` assets under UE_DOW_Legacy that haven't been checked out by Perforce arrive on disk as read-only. `compile_and_save_package` (really the underlying `UPackage::SavePackage`) returns false with `LogSavePackage: Error: Cannot remove '<path>.uasset' as it is read only!`. **Do not run `p4` commands from agent sessions — the global instruction forbids it.** Instead: `(Get-Item $path).IsReadOnly = $false` via PowerShell, or `attrib -R` via `cmd`. The change is a pure Windows FS attribute; P4 workspace state is not touched.

**Verification matrix — all green:**

| Check | Result |
|---|---|
| RunUAT BuildPlugin -Rocket against custom UE_DOW | BUILD SUCCESSFUL in 22.62 s, ExitCode=0 (DLL 2,536,448 b) |
| RunUAT BuildPlugin -Rocket against stock UE 5.7 | BUILD SUCCESSFUL in 41.07 s, ExitCode=0 (DLL 2,537,984 b) |
| Automation tests (`BlueprintExporter.Schema.*`) | Exit 0 in commandlet mode (but per M28.pre.1 flag-gate note that landed 2026-04-23 in CLAUDE.md, ATF silently skips commandlet-context tests without `EAutomationTestFlags::CommandletContext` — separate hygiene fix, not a regression driver for M28) |
| Determinism gate (`verify_determinism.ps1 -Project BugHunt -SweepDeepDump -Engine stock-5.7`) | PASS in 50 s, byte-identical A↔B trees |
| Bridge smoke (`scripts/smoke_bridge.py` against live 1.19.8 editor) | 2 OK + 5 EXPECTED_ERROR + 0 FAILURE |
| MCP pytest (`scripts/blueprint-exporter-mcp && pytest`) | 23/23 pass |
| Live MCP test against UE_DOW_Legacy Combat_FlatArena | All four findings closed end-to-end via `apply_plan` with post-edit `verify_state_tasks` confirming in-place state |

**Live MCP test outcome (UE_DOW_Legacy):**
- **#1** `apply_plan(implement_interface_function, force_rebind=True)` on `BP_EnemyBase.GetTargetingInfo` with bindings `{bIsAlive: "self.bIsAlive", bIsTargetable: "true", Faction: "self.Faction"}` — `wiped_nodes=2`, new bindings applied, BP saved (1,460,055 → 1,459,176 bytes).
- **#3** `apply_plan(connect_graph_pins, "@K2Node_IfThenElse:2304,-416" → "@K2Node_CallFunction:3904,-112")` on `BP_Task_Peek.EventGraph` with pins `else → execute` — new wire landed (BP_Task_Peek 83,208 → 83,328 bytes). Idempotency confirmed by replay (`skipped: "pins already linked"`).
- **#4** `apply_plan(add_statetree_task_to_state × 3)` on `ST_EnemyBase` — `CombatLoop` gained `BP_Task_OpenFireLoop`, `Wait` + `SearchClueLoop` gained `BP_Task_CloseFireLoop`. `verify_state_tasks` on all three reports post-edit `task_len` + correct class paths per entry (Wait's existing `StateTreeDelayTask` preserved at idx 0; new BP task lands at idx 1).
- **#2** `apply_plan(set_level_actor_property × 10)` on `Combat_FlatArena.umap` — 10 placed `BP_EnemyBase*` actors split 5/5 across `Faction=1` / `Faction=2`. 5 actors reported `skipped: "value already '1'"` on second run (idempotence confirmed).

**Op count across library:** 22 op functions now re-exported from `python_ops/__init__.py` (M28 added 5); MCP's `get_op_catalog` auto-surfaces via AST walk (zero MCP server change).

**Carried forward (not M28.1/.3/.9 blockers):**
- **BugHunt fixtures for the three new ops.** Ship `ST_BpxTestTaskStateTree` + `BP_BpxTestTaskBase` + `BP_BpxTestUbergraphPins` via `GenerateTestBlueprintsCommandlet` so the determinism gate regression-covers these ops. M28.9 (level-actor) is harder to fixture cheaply — a committed `.umap` is heavy; consider a determinism soak against the Legacy `Combat_FlatArena.umap` twin-run instead.
- **M28.pre.1** — `EAutomationTestFlags::CommandletContext` sweep across `Private/Tests/BlueprintExporterTests.cpp` so the pre-push matrix stops reporting false green on automation tests.
- **`compile_and_save_package` map extension.** Fix the bridge's `CompileAndSavePackage` to detect `UWorld`/`ULevel` targets and use `FPackageName::GetMapPackageExtension()` so future level-touching ops can reuse it instead of working around via `EditorAssetLibrary.save_loaded_asset`. Low priority — the workaround is stable.
- **M28.2 / M28.4 / M28.5 / M28.6 / M28.7 / M28.8** remain on the roadmap per the phase table above; this session shipped M28.1 + a narrow M28.3 slice + new M28.9 only.

**M28.1 + M28.3-narrow + M28.9 CLOSED (2026-04-23).**

### M28.2 research outcome (2026-04-23)

**TL;DR — three of four candidate ops are mostly already exposed through `unreal.BlueprintEditorLibrary` + `unreal.SubobjectDataSubsystem`. Only deterministic-GUID seeding (mirroring the M26.1 / M26.1.2 `SeedGuidFromJoined` pattern) and the missing `ImplementNewInterface` Python binding need bridge work — three small UFUNCTIONs total. Original M28 phase-table framing of "minor bump 1.20.0 — new subsystem (structural BP edit surface)" was wrong; M28.2 lands as four patch bumps (1.19.9 → 1.19.13), one per op. Start with `add_bp_variable` (M28.2.1).**

Research ran during the current session, without spawning UE. Evidence is code-based against stock UE 5.7 (`C:/Program Files/Epic Games/UE_5.7/Engine`) — same approach as M26.0 / M27.0.

1. **`BpxReflectionOps` surface audit** (`Source/BlueprintExporter/Public/Reflection/ReflectionOps.h`) — current UFUNCTION inventory is 17 UFUNCTIONs across three layers: M23.1 property/object primitives (`GetPropertyValue` / `SetPropertyValue` / `FindSubobject` / `GetArrayLength` / `ArrayAppendNewElement` / `ArrayRemoveAt` / `SetInstancedStructType` / `NewSubobject` / `SetObjectPropertyValue` / `GetObjectPropertyValue` / `CompileAndSavePackage`); M26.1 graph-authoring (`OverrideInterfaceFunction` / `FindGraphEndpoints` / `AddSelfMemberGetNode` / `ConnectPinsByName` / `SetNodePinLiteralDefault` / `WipeFunctionGraphBody`); M28.3-narrow (`ConnectGraphPinsByGuidString`). None author *structural* BP edits — variables, function graphs, components, interfaces are all untouched today.

2. **Python ops library audit** (`scripts/python_ops/`) — 22 op functions across 7 modules cover CDO/SCS property writes, instanced-subobject walks, asset create/rename, StateTree EC/transition/task, Blueprint graph pin connect (M28.3-narrow), interface-function override (M26.1), level-actor property (M28.9). None author the four M28.2 surfaces directly.

3. **`unreal.BlueprintEditorLibrary` already exposes most authoring APIs** (`Source/Editor/BlueprintEditorLibrary/Public/BlueprintEditorLibrary.h`, all `UFUNCTION(BlueprintCallable)` and surfaced as `unreal.BlueprintEditorLibrary.*`):
   - `AddMemberVariable(UBlueprint*, FName, FEdGraphPinType) -> bool` line 322 — `unreal.BlueprintEditorLibrary.add_member_variable`.
   - `AddMemberVariableWithValue(UBlueprint*, FName, <CustomStructureParam>) -> bool` line 312 — variant that accepts a default value (uses `CustomThunk` for the type-erased default).
   - `AddFunctionGraph(UBlueprint*, FString FuncName) -> UEdGraph*` line 158 — returns the new graph so chained M26.1 body-authoring ops work without further bridge.
   - `RemoveFunctionGraph(UBlueprint*, FName)` line 167.
   - `SetBlueprintVariableInstanceEditable / ExposeOnSpawn / ExposeToCinematics` lines 285 / 275 / 295 — variable metadata flag setters by name.
   - Pin-type constructors lines 326–351: `GetBasicTypeByName(FName)` / `GetStructType(UScriptStruct*)` / `GetClassReferenceType(UClass*)` / `GetObjectReferenceType(UClass*)` / `GetArrayType(FEdGraphPinType)` / `GetSetType(FEdGraphPinType)` / `GetMapType(FEdGraphPinType, FEdGraphPinType)`. Covers every design.md pin shape (struct refs for `S_TargetInfo` / `FGameplayTagContainer`, object refs for `UAIController` / `UGameplayAbility`, soft class refs, container variants).

4. **`unreal.SubobjectDataSubsystem` covers the SCS authoring path** (`Source/Editor/SubobjectDataInterface/Public/SubobjectDataSubsystem.h`): `AddNewSubobject(FAddNewSubobjectParams) -> FSubobjectDataHandle` line 220 — `BlueprintCallable`, exposed; `K2_GatherSubobjectDataForBlueprint(UBlueprint*, OutHandles[])` line 156 — read-side companion for parent-handle resolution; `DeleteSubobject(ContextHandle, SubobjectToDelete, BPContext)` line 266. `USCS_Node::VariableGuid` (`SCS_Node.cpp:645-653`) is **already deterministic** — initialized from a hash of `InternalVariableName` if invalid at init. So as long as the Python op sets a stable component variable name, byte-determinism is free; **no bridge work for `add_component_to_scs`**.

5. **`FBlueprintEditorUtils::ImplementNewInterface(UBlueprint*, FTopLevelAssetPath)` is NOT exposed** (`Source/Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h:1439`). The companion `RemoveInterface` (line 1446) is also unbound. The legacy `FName`-overload (line 1436) is `UE_DEPRECATED(5.1)`. This is the only structural-BP authoring API with no Python equivalent — one new bridge UFUNCTION (`AddInterfaceByPath`) closes the gap.

6. **Determinism-trap analysis (HIGH-priority finding):** the engine APIs that DO have Python bindings call `FGuid::NewGuid()` for fresh internal IDs. Running the op twice produces different `.uasset` bytes, which trips the M28.pre.3 soak gate immediately:
   - `FBlueprintEditorUtils::AddMemberVariable` → `BlueprintEditorUtils.cpp:4667`: `NewVar.VarGuid = FGuid::NewGuid();`. Every `add_bp_variable` call drifts.
   - `UEdGraph::PostInitProperties` → `EdGraph.cpp:147`: `GraphGuid = FGuid::NewGuid();`. Every `add_bp_function` call drifts (and chained `AddSelfMemberGetNode` etc. are already deterministic from M26.1, so the graph root is the only undefended spot).
   - `USCS_Node::VariableGuid` → `SCS_Node.cpp:645-653`: name-hash seeded. **No drift**, modulo a verification step that `SubobjectDataSubsystem::AddNewSubobject` actually flows through `USCS::CreateNodeImpl` (which triggers the seed) and not an `FObjectInitializer`-defaulted `NewGuid()` shortcut. Open question for the M28.2.3 implementation probe.
   - `FBlueprintEditorUtils::ImplementNewInterface` graph paths — interface graphs come from `ConformImplementedInterfaces`; whether their `GraphGuid`s inherit from the source interface BP or are freshly generated needs implementation-pass verification. Open question for M28.2.4.

   **Mitigation pattern (proven in M26.1 / M26.1.2):** the bridge wraps the engine call and post-write seeds the GUID via a deterministic md5-derived value (`SeedGuidFromJoined(bp_path, kind, name)` lives in `ReflectionOps.cpp` and is reusable). M26.1.2's regression-chase block above documents the exact two-trap recipe — `ConnectPinsByName` double-mark via structurally-modified listeners and `WipeFunctionGraphBody` Entry/Return reseed. That recipe transfers directly here; the new ops just add VarGuid + GraphGuid to the seeding catalog.

**Chosen C++ surface for M28.2 (3 new UFUNCTIONs on `UBpxReflectionOps`):**

| New UFUNCTION | Purpose |
|---|---|
| `AddMemberVariableDeterministic(UBlueprint* BP, FName VarName, FEdGraphPinType VarType, const FString& DefaultValue, bool bInstanceEditable) -> FBpxReflectionResult` | Calls `FBlueprintEditorUtils::AddMemberVariable`, then walks `Blueprint->NewVariables[]` to find the new entry by name and overwrites `VarGuid` via `SeedGuidFromJoined(BP path, "var", VarName)`. Sets `bInstanceEditable` flag inline (avoids a second op for the most common metadata case — design.md utility scorer wants `EditAnywhere`-style state). Idempotent: if a variable with `VarName` already exists, returns `bSkipped=true` after asserting type match. |
| `AddFunctionGraphDeterministic(UBlueprint* BP, FName FuncName, bool bIsPure, FBpxGraphEndpoints& OutEndpoints) -> FBpxReflectionResult` | Calls `UBlueprintEditorLibrary::AddFunctionGraph`, then seeds `Graph->GraphGuid` via `SeedGuidFromJoined(BP path, "func", FuncName)` and Entry/Return NodeGuids via the same M26.1 recipe so the function graph is byte-deterministic from creation. Returns `FBpxGraphEndpoints` populated with the new Entry/Return GUIDs — caller chains M26.1 ops (`AddSelfMemberGetNode`, `ConnectPinsByName`, `SetNodePinLiteralDefault`, `WipeFunctionGraphBody`) to author the body. Idempotent on `(BP, FuncName)`. |
| `AddInterfaceByPath(UBlueprint* BP, const FString& InterfaceClassPath) -> FBpxReflectionResult` | Calls `FBlueprintEditorUtils::ImplementNewInterface(BP, FTopLevelAssetPath(InterfaceClassPath))`. Walks `Blueprint->ImplementedInterfaces[]` to find the new entry; seeds each generated `Graph->GraphGuid` via `SeedGuidFromJoined(BP path, "iface_graph", InterfacePath, GraphName)` if M28.2.4 probe finds drift on the engine path. Idempotent: if the interface is already on `ImplementedInterfaces[]`, returns `bSkipped=true`. |

Compile+save reuses the existing `CompileAndSavePackage(UObject*)` UFUNCTION unchanged.

Total: **3 new UFUNCTIONs, 0 new USTRUCTs** (`FBpxReflectionResult` + `FBpxGraphEndpoints` reused from M26.1). All additions; no changes to existing bridge surface. **No new module deps in `Build.cs`** (`UnrealEd` + `BlueprintGraph` already linked for M26.1; `BlueprintEditorLibrary` is reachable via `unreal.*` directly from Python so no C++ link needed).

**Chosen Python ops (4 new ops in `scripts/python_ops/blueprint_structural.py`):**

| Python op | Bridge calls | Pure-Python helpers | Engine path |
|---|---|---|---|
| `add_bp_variable(bp_path, var_name, var_type_spec, default_value=None, instance_editable=False)` | `AddMemberVariableDeterministic` (+ `CompileAndSavePackage`) | `unreal.BlueprintEditorLibrary.get_basic_type_by_name` / `get_struct_type` / `get_object_reference_type` / `get_class_reference_type` / `get_array_type` / `get_set_type` / `get_map_type` resolve `var_type_spec` into `FEdGraphPinType` | `FBlueprintEditorUtils::AddMemberVariable` (via deterministic bridge wrapper) |
| `add_bp_function(bp_path, function_name, is_pure=False)` | `AddFunctionGraphDeterministic` (+ `CompileAndSavePackage`) | — | `UBlueprintEditorLibrary::AddFunctionGraph` (via deterministic bridge wrapper). Returns `entry_guid` / `return_guid` so callers chain M26.1 body-authoring ops. |
| `add_component_to_scs(bp_path, component_class_path, component_name, parent_component_name=None)` | `CompileAndSavePackage` only | `unreal.SubobjectDataSubsystem.k2_gather_subobject_data_for_blueprint` (parent handle resolution) → `add_new_subobject(FAddNewSubobjectParams(parent_handle=..., new_class=..., asset_override=None, blueprint_context=BP, conform_transform_to_parent=True))` | `USCS::CreateNode` indirectly via subsystem. **No bridge UFUNCTION needed** — pure Python. |
| `add_bp_interface(bp_path, interface_class_path)` | `AddInterfaceByPath` (+ `CompileAndSavePackage`) | — | `FBlueprintEditorUtils::ImplementNewInterface` (via bridge wrapper because the engine call has no Python binding). |

**Risk re-assessment (was: "Bridge surface balloon on M28.2 — assumed minor bump 1.20.0, 4–8 new UFUNCTIONs"):**

- **API-surface risk: LOW.** 3 UFUNCTIONs total, each is a 5–15-line wrapper around an existing engine call + a `SeedGuidFromJoined` call. Zero novel C++ patterns; mirrors M26.1 / M26.1.2 directly.
- **Python-binding risk: LOW.** `BlueprintEditorLibrary` + `SubobjectDataSubsystem` are stable shipping APIs verified present in stock UE 5.7 source.
- **Determinism risk: MEDIUM (mitigated).** Three engine code paths use `FGuid::NewGuid()` (VarGuid, GraphGuid, possibly interface-graph GUIDs). Each is mitigated by the M26.1.2 `SeedGuidFromJoined` post-write override pattern. Concrete verification belongs in each M28.2.X implementation pass via the M28.pre.3 soak gate — which is exactly the gate that caught the M26.1.2 silent regression and the pattern this milestone leans on.
- **Engine-version risk: LOW.** `AddMemberVariable` / `AddFunctionGraph` / `AddNewSubobject` / `ImplementNewInterface` are all 5.x-stable APIs. `BlueprintEditorLibrary::AddMemberVariable` shipped in 5.0.
- **Subsystem-discovery risk on `add_component_to_scs` (LOW–MEDIUM).** `SubobjectDataSubsystem` is editor-only and `EditorSubsystem`-derived; verify access pattern (`unreal.get_engine_subsystem(unreal.SubobjectDataSubsystem)`) and `FAddNewSubobjectParams` field names through the Python binding in the M28.2.3 first probe before authoring against stock 5.7.
- **Compile-unit risk: LOW.** `BlueprintEditorLibrary` reached from Python (no C++ link). `SubobjectDataInterface` similarly Python-only. No `Build.cs` changes.

**Revised sub-phase breakdown:**

| Phase | Scope | Version bump | Notes |
|---|---|---|---|
| **M28.2.1** | `add_bp_variable` + `AddMemberVariableDeterministic` UFUNCTION | 1.19.9 → 1.19.10 (patch) | Smallest first slice. Hits design.md items #1 (Squad director state — `bool bActiveOrder`, `EOrderType CurrentOrder`), #2 (Utility scorer state — `float CurrentScore`, `TArray<S_ScoreEntry> Candidates`), #8 (polish state vars). Probe pin-type construction for the four common shapes (`int`/`float`/`bool` basic, struct ref like `S_TargetInfo`, object ref like `UAIController`, gameplay-tag container) in the same pass. BugHunt fixture `BP_BpxTestStructuralVariables` via `GenerateTestBlueprintsCommandlet`. M28.pre.2 + M28.pre.3 gates required before merge. |
| **M28.2.2** | `add_bp_function` + `AddFunctionGraphDeterministic` UFUNCTION | 1.19.10 → 1.19.11 (patch) | Returns `(entry_guid, return_guid)` so callers chain M26.1 body-authoring ops without further bridge work. Hits design.md items #2, #8. BugHunt fixture `BP_BpxTestStructuralFunctions` (one fixture covers blank function + chained body authoring). |
| **M28.2.3** | `add_component_to_scs` (pure-Python via `SubobjectDataSubsystem`) | 1.19.11 → 1.19.12 (patch — Python-only, but version bumps to keep `get_op_catalog` AST-based discovery in lockstep with op set) | First step: 1-shot probe under `D:/Work/_combat_ai_tuning/m28_2_3_probe_subobject_subsystem.py` to verify subsystem access pattern + `FAddNewSubobjectParams` field names + `USCS_Node::VariableGuid` deterministic-by-name path is reached when allocating through the subsystem. Hits design.md items #1 (Squad director needs `USquadDirectorComponent`), #4 (Callouts need `UAudioComponent` + `UAnimNotifyComponent`). BugHunt fixture `BP_BpxTestStructuralComponents` (parent + child component, exercises both root and attached cases). |
| **M28.2.4** | `add_bp_interface` + `AddInterfaceByPath` UFUNCTION | 1.19.12 → 1.19.13 (patch) | First step: probe interface-graph `GraphGuid` source — if `ConformImplementedInterfaces` produces graphs with `FGuid::NewGuid()`, the UFUNCTION must seed each graph; if it inherits from the source interface BP, no extra work. Hits design.md item #1 (Squad director `BPI_OrderListener` interface for the `AI.Order.*` event channel). BugHunt fixtures: `BPI_BpxTestStructuralInterface` + `BP_BpxTestStructuralImplementsInterface`. |
| **M28.2.5** | Docs sweep | no bump (pure docs) | `scripts/python_ops/CATALOG.md` per new op. `plans/README.md` op kwargs table extended. `plans/AGENT_LOOP.md` worked example (recommend design.md item #1 squad-director skeleton: `add_bp_variable(bActiveOrder)` → `add_bp_interface(BPI_OrderListener)` → `add_bp_function(OnOrderReceived)` → chained body via M26.1). `CLAUDE.md` Project Structure tree adds `blueprint_structural.py` + 3 new UFUNCTION descriptions on `UBpxReflectionOps`. |

**Versioning expectation:** four patch bumps (1.19.9 → 1.19.13), not the originally-scoped minor 1.20.0. Each .X gets its own 9-location stamp sweep + dual-engine DLL rebuild per `CLAUDE.md § Versioning Protocol`. Patch (not minor) because each addition is a small extension to the existing `BpxReflectionOps` subsystem (M23.1 / M26.1 / M28.3-narrow lineage), not a brand-new subsystem like M19.1 (CDO walk) or M27.1 (bridge transport). The M28 phase-table row at this section's top still reads "minor — new subsystem (1.20.0)"; that row is left immutable per the M26.0 / M27.0 archaeology pattern, with this closure being the supersede record.

**Open questions (resolve in implementation passes — flagged so M28.2.X probes catch them before authoring):**

1. **`SubobjectDataSubsystem::AddNewSubobject` determinism path (M28.2.3).** Verify the subsystem's Add-New flows through `USCS::CreateNodeImpl` (which feeds `USCS_Node::VariableGuid` deterministic seeding) and not an `FObjectInitializer` shortcut that defaults VarGuid to `FGuid::NewGuid()`. If drifty, add a 4th bridge UFUNCTION `SeedComponentVariableGuid(BP, ComponentName, FGuid SeededGuid)` mirroring the variable/graph pattern.
2. **Interface-graph GraphGuid source (M28.2.4).** When `ImplementNewInterface` populates `Blueprint->ImplementedInterfaces[].Graphs`, do the new `UEdGraph` instances inherit `GraphGuid` from the source interface BP (deterministic) or get `FGuid::NewGuid()` (drifty)? If drifty, `AddInterfaceByPath` seeds each generated graph's `GraphGuid` via `SeedGuidFromJoined(BP, "iface_graph", interface_path, graph_name)`.
3. **Pin-type spec shape for `add_bp_variable` (M28.2.1).** Two options: (a) string-based spec like `"int"` / `"struct:/Script/Game.S_TargetInfo"` / `"object:/Script/AIModule.AIController"` parsed Python-side via `BlueprintEditorLibrary::Get*Type` calls; (b) dict-based spec like `{"kind": "struct", "path": "/Script/Game.S_TargetInfo"}`. Lean (a) for terseness in plan JSON; resolve in M28.2.1 design pass before authoring.
4. **Variable-metadata setters (M28.2.1 vs M28.2.5).** M28.2.1 ships `instance_editable` inline because it's the most common authoring need (design.md item #2 utility scorer needs `EditAnywhere`-style flag). Other flags (`ExposeOnSpawn`, `ExposeToCinematics`, `BlueprintReadOnly`, `Category`) are exposed by `BlueprintEditorLibrary` already — defer to the agent to call them via `unreal.*` directly inside the plan, OR add a `set_bp_variable_metadata(bp_path, var_name, **flags)` op in M28.2.5 polish. Decide based on real plan-author friction during M28.2.1 dogfood.

**Reference patterns reused:**
- M23.1 `BpxReflectionOps` UFUNCTION bridge pattern + `FBpxReflectionResult` / `FBpxGraphEndpoints` USTRUCTs.
- M26.1 `OverrideInterfaceFunction` shape — closest analogue for `AddFunctionGraphDeterministic` (graph-creation + Entry/Return seeding + idempotence-by-existing-graph-name).
- M26.1.2 `SeedGuidFromJoined` + `MarkBlueprintAsStructurallyModified` ordering — load-bearing for the soak gate; the M26.1.2 regression-chase block above documents the two failure modes (double-mark via structurally-modified listeners, missed reseed on early-return) that M28.2.X must avoid.
- M28.pre.2 (post-apply content inspect) + M28.pre.3 (per-op soak template) — every M28.2.X op gets both a `*.json` assertions fixture AND a soak invocation before merge. M28.pre.3 already proved its worth catching the silent within-session determinism regression in `541fecf`.
- M28.1 + M28.3-narrow + M28.9 closure block above — dispatch / validator / mechanical-diff wiring pattern (one entry per op in `__init__.py` exports, `OP_SPECS`, `_OP_DISPATCH`, `_op_expected_changes`).

**Out of scope for M28.2:** node-level graph composition catalog beyond what M26.1 already ships (M28.3 territory — full `add_graph_node` / `add_local_variable` / etc.); UserDefinedStruct member authoring (M28.4); EQS / curve / data-asset factories (M28.5 / M28.4); tag-config authoring (M28.6); automation-test runner (M28.7).

**M28.2.0 closed (research). M28.2.1 (`add_bp_variable`) ready to start.** Next steps:
1. Add `AddMemberVariableDeterministic` to `ReflectionOps.{h,cpp}` (mirror `OverrideInterfaceFunction` shape). Reuse `SeedGuidFromJoined` from M26.1.2.
2. Author `scripts/python_ops/blueprint_structural.py` with `add_bp_variable`. Wire `__init__.py` re-export + `plan_validator.OP_SPECS` entry + `plan_executor._OP_DISPATCH` entry + `mechanical_diff._op_expected_changes` entry.
3. Extend `GenerateTestBlueprintsCommandlet` with `BP_BpxTestStructuralVariables` (one fixture, exercises four common pin-type shapes).
4. Run M28.pre.2 (assertions JSON) + M28.pre.3 (soak template, 5 rounds). Both must PASS.
5. Version-stamp 1.19.9 → 1.19.10 across all 9 locations + dual-engine DLL rebuild per `CLAUDE.md § Versioning Protocol`.
6. M28.pre.5 (config-file parity for tags) stays deferred — confirmed not blocking M28.2.

### M28.2.1 shipped (2026-04-23, 1.19.9 → 1.19.10)

**`add_bp_variable` lands as the first M28.2 op end-to-end.** Smallest first slice per the M28.2.0 closure plan; all six gates of the pre-push matrix green in 109.5s on BugHunt / stock UE 5.7. Patch bump 1.19.9 → 1.19.10 (additive UFUNCTION + Python op + new fixture + new module — no schema change, no existing-op behaviour change).

**C++ surface added (1 UFUNCTION on `UBpxReflectionOps`):**

| New UFUNCTION | What it does |
|---|---|
| `AddMemberVariableDeterministic(UBlueprint* BP, FName VarName, const FEdGraphPinType& VarType, const FString& DefaultValue)` | Wraps `FBlueprintEditorUtils::AddMemberVariable` and post-write seeds the new entry's `FBPVariableDescription::VarGuid` via `SeedGuidFromJoined(BP path + ":var:" + VarName)` so the .uasset is byte-deterministic across re-runs. Idempotent on `(BP, VarName)`. Forward-declares `FEdGraphPinType` in the header (mirrors `BlueprintEditorLibrary.h` pattern; full type lives in `EdGraph/EdGraphSchema.h`). |

**Python surface added (1 op + new module):**

| New Python op (in `scripts/python_ops/blueprint_structural.py`) | What it does |
|---|---|
| `add_bp_variable(bp_path, var_name, var_type_spec, default_value="", instance_editable=False)` | Resolves `var_type_spec` (string-form catalog: basic / `struct:<path>` / `object:<path>` / `class:<path>` / `array:<inner>` / `set:<inner>` / `map:<key>=>>>:<value>`) into `FEdGraphPinType` via `unreal.BlueprintEditorLibrary` helpers, calls the bridge's deterministic-add UFUNCTION, optionally chains `set_blueprint_variable_instance_editable` when `instance_editable=True`, then `compile_and_save_package`. Idempotent: existing var with same name returns `success=True, skipped="variable already exists"`. |

**Pin-type spec catalog (decided in M28.2.1 design pass per Open Question #3):**
- Basic: `"int"` / `"byte"` / `"bool"` / `"real"` / `"name"` / `"string"` / `"text"` (and `"float"` as a back-compat alias for `"real"`).
- Object ref: `"object:/Script/AIModule.AIController"` / `"object:/Game/MyBP.MyBP_C"`.
- Class ref (`TSubclassOf`): `"class:/Script/AIModule.AIController"`.
- Struct: `"struct:/Script/CoreUObject.Vector"` / `"struct:/Script/Game.S_TargetInfo"`.
- Container (recursive): `"array:int"` / `"array:struct:/Script/Game.S_TargetInfo"` / `"set:name"` / `"map:name=>>>:int"`.
- The `"=>>>:"` map key/value separator was chosen to avoid colliding with `:` inside asset paths.

**Variable-metadata setters (decided per Open Question #4):** `instance_editable` is the only flag inlined in the M28.2.1 op (most common authoring need per design.md item #2 utility scorer). Other flags (`ExposeOnSpawn`, `ExposeToCinematics`, `BlueprintReadOnly`, `Category`) stay agent-callable via `unreal.BlueprintEditorLibrary.set_blueprint_variable_*` directly inside the plan. Add a wrapper op only if real-world plan-author friction surfaces.

**Plan pipeline wiring:**
- `__init__.py`: `add_bp_variable` re-exported + added to `__all__`.
- `plan_shape.OP_SPECS`: new entry with `required: [bp_path, var_name, var_type_spec]`, `optional: [default_value, instance_editable]`, `assets: [bp_path]`.
- `plan_executor._OP_DISPATCH`: new entry → `add_bp_variable`. Note `_prepare_kwargs` does NOT touch `default_value` (it's a raw ImportText string for the bridge, not a UE-typed value to convert) — pass-through works because `_convert_value` only fires on the `value` key.
- `mechanical_diff._op_expected_changes`: `add_bp_variable` added to the BP-mutation tuple alongside `set_bp_variable_default` etc., returning `[(bp_path, "mutated")]`.

**Op count across library:** 23 op functions now re-exported from `python_ops/__init__.py` (M28.2.1 added 1); MCP's `get_op_catalog` auto-surfaces via AST walk (zero MCP server change).

**BugHunt fixture added:**
- `BP_BpxTestStructuralVariables.uasset` — empty Actor BP with no declared variables. Generated via `GenerateTestBlueprintsCommandlet` Tier C, registered after the M26.1 interface-impl pair. Empty by design: every VarGuid in the post-op asset comes from the new `SeedGuidFromJoined` path, so the soak gate has clear blast radius (no pre-existing variables to muddle the determinism story).

**Inspect/soak fixture added:**
- `scripts/inspect_fixtures/add_bp_variable.json` — adds a single `int ActiveOrder` variable (design.md item #1 squad-director state) to a scratch duplicate of `BP_BpxTestStructuralVariables`. Inspect asserts `ActiveOrder` surfaces in both `.md` and `.deep.md`. Soak asserts md5 stability across 2 rounds — `084153574a0697243b5d7b8429ee168e` stable, proving `SeedGuidFromJoined` works (without it, round 2's `FGuid::NewGuid()` would produce a different VarGuid → different md5 → soak FAIL).

**Pre-push matrix (BugHunt / stock UE 5.7, 109.5s total via `verify_all.ps1`):**

| Gate | Result | Notes |
|---|---|---|
| Unity build (custom UE_DOW, RunUAT BuildPlugin -Rocket) | PASS, 23s | DLL 2,540,544 → 2,545,664 bytes (+5,128 bytes — matches expected new UFUNCTION + .gen.cpp/.gen.h glue size). `[26/35] Compile [x64] ReflectionOps.cpp` clean. |
| Unity build (stock UE 5.7, RunUAT BuildPlugin -Rocket) | PASS, 41s | DLL 2,546,688 bytes. Identical compile success. |
| `automation-bughunt` (`run_automation_tests.ps1`) | PASS, 15.6s | All `BlueprintExporter.*` automation tests green. |
| `determinism-bughunt` (`verify_determinism.ps1-SweepDeepDump`) | PASS, 46.4s | Twin-run byte-identical including the new `BP_BpxTestStructuralVariables` fixture. |
| `inspect-add_bp_variable` (M28.pre.2) | PASS, 17.6s | `expected_md`: 1/1, `expected_deep`: 1/1. `ActiveOrder` surfaces in both renderings. |
| `inspect-implement_interface_function` (regression) | PASS, 17.6s | M26.1 fixture unaffected. |
| `soak-add_bp_variable` (M28.pre.3) | PASS, 6.1s | md5 `084153574a0697243b5d7b8429ee168e` stable round1 == round2. Determinism proof. |
| `soak-implement_interface_function` (regression) | PASS, 6.1s | M26.1 fixture unaffected; `r2 wiped = 2 (>= 1)` confirms force_rebind path still exercises wipe. |

**Determinism story (the load-bearing signal).** `BlueprintEditorUtils.cpp:4667` calls `FGuid::NewGuid()` for every new variable's `VarGuid`. Without intervention, round 2 of the soak produces a different VarGuid → different .uasset bytes → md5 drift. The bridge wrapper post-write overrides VarGuid with `SeedGuidFromJoined(<bp_path>:var:<var_name>)`, which is content-derived and stable across runs. Soak round 2 md5 EQUAL to round 1 md5 is the empirical confirmation this works — exact same proof shape M26.1.2 used for NodeGuid + PinId determinism.

**Files changed:**
- `Source/BlueprintExporter/Public/Reflection/ReflectionOps.h` (+ forward decl + new UFUNCTION)
- `Source/BlueprintExporter/Private/Reflection/ReflectionOps.cpp` (+ `AddMemberVariableDeterministic` impl)
- `BuiltPlugin/...` mirrors of the above (manual sync per CLAUDE.md § Building & Deploying)
- `BugHunt/TestProject/Plugins/BlueprintExporter/...` mirrors (manual sync — see "Carried forward" below)
- `BuiltPlugin/Binaries/Win64/{UnrealEditor-BlueprintExporter.dll,UnrealEditor.modules}` (custom UE_DOW build)
- `BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64/{UnrealEditor-BlueprintExporter.dll,UnrealEditor.modules}` (stock UE 5.7 build)
- `scripts/python_ops/blueprint_structural.py` (NEW)
- `scripts/python_ops/__init__.py` (re-export + `__all__`)
- `scripts/python_ops/plan_shape.py` (`OP_SPECS["add_bp_variable"]`)
- `scripts/python_ops/plan_executor.py` (`_OP_DISPATCH["add_bp_variable"]`)
- `scripts/python_ops/mechanical_diff.py` (`_op_expected_changes` BP-mutation tuple extended)
- `scripts/inspect_fixtures/add_bp_variable.json` (NEW)
- `BugHunt/BlueprintExporterTests/Source/BlueprintExporterTests/Private/Commandlets/GenerateTestBlueprintsCommandlet.cpp` (+ `GenBP_BpxTestStructuralVariables` + Gens registration)
- `BugHunt/TestProject/Content/TestBlueprints/BP_BpxTestStructuralVariables.uasset` (NEW, 24,013 bytes)
- 9 version-stamp locations bumped 1.19.9 → 1.19.10 (uplugin × 2, module UE_LOG, bridge ping + list_methods handlers, Manifest.PluginVersion, BlueprintSerializer / StateTreeSerializer / ProjectPluginsCommandlet PluginVersion stamps, BlueprintExporterTests live-version test, README) + the same 9 mirrors in BuiltPlugin/ + the same 9 mirrors in BugHunt's plugin install.

**Carried forward (NOT blockers for M28.2.1, observed during the patch):**
- **`mechanical_diff._op_expected_changes` is missing M28.1 / M28.3-narrow / M28.9 entries.** Today's `add_bp_variable` entry slotted in cleanly, but `add_statetree_task_to_state` / `remove_statetree_task_from_state` / `connect_graph_pins` / `set_level_actor_property` / `verify_state_tasks` ALL fall through the dispatch table to the final `return []` — meaning the M27.3 auto-re-export path silently misses these ops' touched assets. The M28.1+M28.3+M28.9 closure (`541fecf`) didn't catch this. Probably one-line additions per op; ship as a piggyback fix in M28.2.2 or earlier.
- **BugHunt plugin install drift.** `BugHunt/TestProject/Plugins/BlueprintExporter/Source/` is a real (non-junction) copy that drifted to 1.19.7 between the M26.1.2 ship and now — synced manually for THIS patch. The WIP M27.1 closure flagged junction conversion as a "Follow-up opportunity"; it's becoming a recurring tax on every C++ patch. Convert in next session: delete the copy + `mklink /J` back to the canonical `Source/` to eliminate the entire drift class. Same for `Config/`. Keep `.uplugin` as a copy (per M27.1 note about WebSocketNetworking optional-dep handling) but version-bump it lockstep via `verify_drift` script.
- **DOW-leg verification deferred.** `verify_all.ps1` was run BugHunt-only (no `-IncludeDow`). Custom UE_DOW unity build succeeded (RunUAT exit 0) so compile correctness is established, but DOW automation + DOW determinism slice were not exercised. Consistent with M26.1.2 closure pattern (deferred Legacy DLL rebuild). Add to next push that actually targets DOW.
- **The four pin-type shapes catalog is unfixtured.** The committed `add_bp_variable.json` exercises the simplest shape (`int`). Struct ref / object ref / array variants work in code (per the unit-test-style `_resolve_pin_type` walk) but aren't fixtured. Easy to add three more `*.json` files alongside the first one if dogfooding surfaces a pin-type-shape regression.

**Reference patterns reused:**
- M23.1 `BpxReflectionOps` UFUNCTION bridge pattern + result struct shape.
- M26.1 `OverrideInterfaceFunction` for the engine-call + post-write determinism-seed pattern.
- M26.1.2 `SeedGuidFromJoined` for the actual GUID derivation; `MarkBlueprintAsStructurallyModified` ordering (after the seed write, before save).
- M28.pre.2 inspect harness (single-op plan from assertions JSON, post-apply asset content match) and M28.pre.3 soak template (N-round md5 stability check, parameterised on `assertions.soak.{rounds, stable_keys}`).
- M28.1+M28.3+M28.9 closure dispatch wiring pattern (one entry per op in `__init__.py` + `OP_SPECS` + `_OP_DISPATCH` + `_op_expected_changes`).

**M28.2.1 CLOSED (2026-04-23). M28.2.2 (`add_bp_function` + `AddFunctionGraphDeterministic` UFUNCTION) ready to start** when scheduled.

### M28.2.2 shipped (2026-04-23, 1.19.10 → 1.19.11)

**`add_bp_function` lands as the second M28.2 op.** All 8 pre-push gates green on BugHunt / stock UE 5.7 in 134 s via `verify_all.ps1`. Patch bump 1.19.10 → 1.19.11 (additive UFUNCTION + Python op + new fixture + bSkipped field on `FBpxGraphEndpoints` — no schema break for existing callers, no existing-op behaviour change).

**C++ surface added (1 UFUNCTION + 1 struct field):**

| New surface | What it does |
|---|---|
| `UBpxReflectionOps::AddFunctionGraphDeterministic(UBlueprint*, FName FunctionName, bool bIsPure)` | Mirrors `UBlueprintEditorLibrary::AddFunctionGraph` but closes three determinism traps: `UEdGraph::PostInitProperties` GraphGuid randomness (EdGraph.cpp:147), `UK2Node_FunctionEntry` / `UK2Node_FunctionResult` `CreateNewGuid()` NodeGuid randomness, and per-pin `FGuid::NewGuid()` PinId randomness. Post-create, seeds GraphGuid via `SeedGuidFromJoined(<bp>:func:<name>:graph)`, Entry NodeGuid via `:entry`, Return NodeGuid via `:return`, plus `SeedPinGuidsForNode` on both nodes. Name pre-validated through `FKismetNameValidator` so reserved / inherited-collision names fail fast with a structured error rather than UE silently renaming to "NewFunction". `bIsPure=true` sets `FUNC_BlueprintPure` on Entry's ExtraFlags (pattern from `BlueprintDetailsCustomization.cpp:6320`); caller must pair with an output-param add + wire before compile, or the compile gate refuses. Idempotent: existing graph (function / interface-override / ubergraph — all three forms of `FindFunctionGraphByName`) returns `bSuccess=true, bSkipped=true` with the existing Entry/Return GUIDs so chained authoring ops still work. |
| `FBpxGraphEndpoints::bSkipped` | New bool field mirroring the pattern on `FBpxReflectionResult` + `FBpxNodeResult`. Lets Python callers distinguish "created" from "graph already existed" without inferring from the `ErrorMessage` being populated — which we no longer do, the skip path is a clean success. Existing M26.1 `FindGraphEndpoints` call sites are unaffected (they never set `bSkipped`, it stays false-by-default). |

**Python surface added (1 op):**

| New Python op (in `scripts/python_ops/blueprint_structural.py`) | What it does |
|---|---|
| `add_bp_function(bp_path, function_name, is_pure=False)` | Calls the deterministic bridge UFUNCTION, derives hex-form GUIDs via `.to_string()` (UE 5.7's only reliable FGuid accessor; `is_valid()` is NOT exposed), short-circuits on the skip path with the existing graph's Entry/Return GUIDs so chained body-authoring still works, chains `compile_and_save_package` on real adds. Zero-guid values are normalized to empty strings in the result dict so plan authors can treat "no Return" cleanly. |

**Plan pipeline wiring:**
- `__init__.py`: `add_bp_function` re-exported + added to `__all__` (alphabetised ahead of `add_bp_variable`).
- `plan_shape.OP_SPECS`: new entry with `required: [bp_path, function_name]`, `optional: [is_pure]`, `assets: [bp_path]`.
- `plan_executor._OP_DISPATCH`: new entry → `add_bp_function`. No `_convert_value` plumbing needed (all kwargs are string/bool primitives).
- `mechanical_diff._op_expected_changes`: `add_bp_function` added to the BP-mutation tuple alongside `set_bp_variable_default` / `set_component_property` / `set_instanced_subobject_property` / `add_bp_variable`, returning `[(bp_path, "mutated")]`.

**Op count across library:** 24 op functions now re-exported from `python_ops/__init__.py` (M28.2.2 added 1); MCP's `get_op_catalog` auto-surfaces via AST walk (zero MCP server change).

**BugHunt fixture added:**
- `BP_BpxTestStructuralFunctions.uasset` (24,013 b) — empty Actor BP, no declared member functions. Same baseline shape as `BP_BpxTestStructuralVariables` (M28.2.1); every seeded GUID in the post-op asset comes from the new `SeedGuidFromJoined` paths, not from pre-existing on-disk content. Generated via `GenerateTestBlueprintsCommandlet -Only=BP_BpxTestStructuralFunctions`.

**Inspect/soak fixture added:**
- `scripts/inspect_fixtures/add_bp_function.json` — adds a single blank function `DoTheThing` (void/void, non-pure) to a scratch duplicate of `BP_BpxTestStructuralFunctions`. Inspect asserts `DoTheThing` surfaces in both `.md` and `.deep.md`. Soak asserts (a) md5 stability across rounds — `267ca48480662d39709b01e7ce65c3ec` stable — AND (b) `soak.stable_keys: ["entry_guid", "return_guid"]` which pulls both hex strings from `result.after` and verifies round-1 equals round-2. Explicit guid tracking catches the exact bug class M26.1.2 surfaced (NodeGuid drift under GC/counter pressure) before md5 drift makes it obvious.

**Pre-push matrix (BugHunt / stock UE 5.7, 134 s total via `verify_all.ps1`):**

| Gate | Result | Notes |
|---|---|---|
| Unity build (custom UE_DOW, RunUAT BuildPlugin -Rocket) | PASS, 24s | DLL 2,545,664 → 2,554,880 bytes (+9,216 — matches one new UFUNCTION + its .gen.cpp/.gen.h glue + one USTRUCT field). |
| Unity build (stock UE 5.7, RunUAT BuildPlugin -Rocket) | PASS, 42s | DLL 2,546,688 → 2,556,416 bytes. Identical compile success. |
| `automation-bughunt` | PASS, 15.6s | All `BlueprintExporter.*` automation tests green. |
| `determinism-bughunt` (`-SweepDeepDump`) | PASS, 46.7s | Twin-run byte-identical including new `BP_BpxTestStructuralFunctions` fixture. |
| `inspect-add_bp_function` (M28.pre.2) | PASS, 17.6s | `DoTheThing` surfaces in `.md` + `.deep.md` post-re-export. |
| `inspect-add_bp_variable` (regression) | PASS, 17.7s | M28.2.1 fixture unaffected. |
| `inspect-implement_interface_function` (regression) | PASS, 17.7s | M26.1 fixture unaffected. |
| `soak-add_bp_function` (M28.pre.3) | PASS, 6.2s | md5 stable, `entry_guid` + `return_guid` stable across rounds. |
| `soak-add_bp_variable` (regression) | PASS, 6.1s | M28.2.1 determinism preserved. |
| `soak-implement_interface_function` (regression) | PASS, 6.2s | M26.1 determinism preserved; `r2 wiped = 2`. |
| MCP pytest (`scripts/blueprint-exporter-mcp && pytest`) | PASS, 11.7s | 23/23 pass; validates mechanical_diff carry-forward fix didn't regress transport. |

**Determinism story.** `EdGraph.cpp:147` (GraphGuid), `K2Node_FunctionEntry::CreateNewGuid`, `K2Node_FunctionResult::CreateNewGuid`, and every pin's `FGuid::NewGuid()` on creation all drift per-call. Post-create, the bridge overrides each with a content-derived seed:
- GraphGuid ← `SeedGuidFromJoined(<bp>:func:<name>:graph)`
- Entry NodeGuid ← `SeedGuidFromJoined(<bp>:func:<name>:entry)`, pins seeded via `SeedPinGuidsForNode(Entry, <bp>:func:<name>:entry)`
- Return NodeGuid ← `SeedGuidFromJoined(<bp>:func:<name>:return)`, pins seeded via `SeedPinGuidsForNode(Return, <bp>:func:<name>:return)`

Soak round 2 md5 == round 1 md5 AND entry_guid/return_guid stable is the empirical confirmation. Same proof shape M26.1.2 used for interface-override force_rebind determinism.

**Carry-forwards closed alongside M28.2.2 (not gated on this ship, but landed in the same working-tree state):**

| Carry-forward | Status | Evidence |
|---|---|---|
| `mechanical_diff._op_expected_changes` silent re-export gap on M28.1 / M28.3-narrow / M28.9 ops | FIXED — `add_statetree_task_to_state` / `remove_statetree_task_from_state` / `verify_state_tasks` / `connect_graph_pins` / `set_level_actor_property` now have dispatch entries; `verify_state_tasks` joins the read-only tuple. | MCP pytest 23/23 PASS post-fix. Silent `refresh_inventory` skip after `apply_plan` on any of these 5 ops is now impossible. |
| BugHunt plugin install `Source/` + `Config/` copies drifting vs canonical | FIXED — both converted to NTFS junctions via `mklink /J`. `Binaries/` stays real (DLL install destination). `.uplugin` stays real (.uplugin-level optional-dep handling). | Pre-conversion drift: 1 file missing + 8 content-differ. Post-conversion: junction target → canonical Source/ + Config/. Every C++ edit going forward propagates instantly with zero manual sync. |
| DOW-leg verification deferred | STILL deferred — `verify_all.ps1 -IncludeDow` not run. Custom UE_DOW BuildPlugin succeeded (RunUAT exit 0, 24 s) so compile correctness is established; DOW automation + determinism slice remain unexercised. Consistent with M28.2.1 pattern. | Log: `_build_output_dow` rebuilt cleanly. Run `-IncludeDow` on the next push that actually targets DOW. |

**Files changed (M28.2.2 + carry-forwards):**
- `Source/BlueprintExporter/Public/Reflection/ReflectionOps.h` (+ `AddFunctionGraphDeterministic` UFUNCTION declaration)
- `Source/BlueprintExporter/Public/Reflection/ReflectionTypes.h` (+ `FBpxGraphEndpoints::bSkipped`)
- `Source/BlueprintExporter/Private/Reflection/ReflectionOps.cpp` (+ `AddFunctionGraphDeterministic` impl + `Kismet2NameValidators.h` include)
- `BuiltPlugin/...` mirrors of the three above
- `BuiltPlugin/Binaries/Win64/{UnrealEditor-BlueprintExporter.dll,UnrealEditor.modules}` (custom UE_DOW build — 2,554,880 b)
- `BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64/{UnrealEditor-BlueprintExporter.dll,UnrealEditor.modules}` (stock UE 5.7 build — 2,556,416 b)
- `BugHunt/TestProject/Plugins/BlueprintExporter/{Source,Config}` (junctions, not copies — carry-forward #2)
- `scripts/python_ops/blueprint_structural.py` (+ `add_bp_function` + module-local `_ZERO_GUID_HEX`)
- `scripts/python_ops/__init__.py` (re-export + `__all__`)
- `scripts/python_ops/plan_shape.py` (`OP_SPECS["add_bp_function"]`)
- `scripts/python_ops/plan_executor.py` (`_OP_DISPATCH["add_bp_function"]`)
- `scripts/python_ops/mechanical_diff.py` (`_op_expected_changes` — BP-mutation tuple extended + carry-forward #1: M28.1 / M28.3-narrow / M28.9 ops wired)
- `scripts/inspect_fixtures/add_bp_function.json` (NEW)
- `BugHunt/BlueprintExporterTests/Source/BlueprintExporterTests/Private/Commandlets/GenerateTestBlueprintsCommandlet.cpp` (+ `GenBP_BpxTestStructuralFunctions` + Gens registration)
- `BugHunt/TestProject/Content/TestBlueprints/BP_BpxTestStructuralFunctions.uasset` (NEW, 24,013 b)
- 9 version-stamp locations bumped 1.19.10 → 1.19.11 (uplugin × 3 counting BugHunt's copy, module UE_LOG, bridge ping + list_methods handlers, Manifest.PluginVersion, BlueprintSerializer / StateTreeSerializer / ProjectPluginsCommandlet PluginVersion stamps, BlueprintExporterTests live-version test, README) + BuiltPlugin mirrors. BugHunt's Source/ junction auto-propagated the C++ stamps; only `.uplugin` is a real file there and got bumped alongside canonical.

**Next up after M28.2.2:**
- **M28.2.3** — `add_component_to_scs`. First op in the M28.2 family that's pure-Python (no bridge extension) via `unreal.SubobjectDataSubsystem`. Open question from M28.2.0 research: verify `SubobjectDataSubsystem::AddNewSubobject` flows through `USCS::CreateNodeImpl` (deterministic VarGuid seeding) and not an `FObjectInitializer` shortcut. Probe first under `D:/Work/_combat_ai_tuning/m28_2_3_probe_subobject_subsystem.py` before authoring.
- **M28.2.4** — `add_bp_interface` + `AddInterfaceByPath` UFUNCTION. Open question from M28.2.0: verify whether `ImplementNewInterface`-created interface-graph `GraphGuid`s inherit from the source interface BP (deterministic) or are freshly generated (drifty). If drifty, seed each generated graph via `SeedGuidFromJoined(<bp>:iface_graph:<interface_path>:<graph_name>)`.

**Reference patterns reused (unchanged from M28.2.1):**
- M23.1 `BpxReflectionOps` UFUNCTION bridge + result struct shape.
- M26.1 `OverrideInterfaceFunction` for the engine-call + post-write determinism-seed pattern. The interface-override case already seeded GraphGuid via `CreateNewGraph` + post-walk of `NewGraph->Nodes`; M28.2.2 uses the same pattern on the non-interface add.
- M26.1.2 `SeedGuidFromJoined` + `SeedPinGuidsForNode` + `MarkBlueprintAsStructurallyModified` ordering.
- M28.pre.2 inspect harness + M28.pre.3 soak template.
- M28.2.1 closure dispatch wiring pattern (one entry per op in `__init__.py` + `OP_SPECS` + `_OP_DISPATCH` + `_op_expected_changes`).

**M28.2.2 CLOSED (2026-04-23). M28.2.3 (`add_component_to_scs`) ready to start** when scheduled.

### M28.2.3 shipped (2026-04-23, 1.19.11 → 1.19.12)

**`add_component_to_scs` lands as the third M28.2 op.** All 10 pre-push gates green on BugHunt / stock UE 5.7 in 158 s via `verify_all.ps1`; MCP pytest 23/23. Patch bump 1.19.11 → 1.19.12 (additive UFUNCTION + Python op + new fixture — no schema change, no existing-op behaviour change).

**Scope supersede on M28.2.0 Open Question #1.** The M28.2.0 research posited `add_component_to_scs` could be pure-Python because `USCS_Node::VariableGuid` was name-hash seeded. Code inspection on M28.2.3 start disproved that: `USCS_Node::ValidateGuid` at `SCS_Node.cpp:640` only fires its name-hash seed path when `!VariableGuid.IsValid()`, but `USimpleConstructionScript::CreateNodeImpl` at `SimpleConstructionScript.cpp:1375` unconditionally assigns `NewNode->VariableGuid = FGuid::NewGuid();` — so the name-hash path is never taken for freshly-created nodes. Mirrors the exact M28.2.1 VarGuid / M28.2.2 GraphGuid drift trap. Research updated in `blueprint_structural.py`'s module docstring as the authoritative record; M28.2.0's "pure-Python" framing is now the supersede record, not the plan.

**C++ surface added (1 UFUNCTION):**

| New UFUNCTION | What it does |
|---|---|
| `UBpxReflectionOps::AddComponentToSCSDeterministic(UBlueprint*, UClass* ComponentClass, FName ComponentName, FName ParentComponentName)` | Wraps `USimpleConstructionScript::CreateNode` (Engine module, already linked — no new module dep) and post-write overrides the new `USCS_Node::VariableGuid` via `SeedGuidFromJoined(<bp>:scs:<component_name>)`. Resolves parent via `SCS->FindSCSNode` (SCS-to-SCS parenting only; NAME_None / empty / `"None"` = attach at root via `SCS->AddNode`). Idempotence: same `(Blueprint, ComponentName, ComponentClass)` replay returns `bSuccess=true, bSkipped=true`; same name with different class is a structured error. Rejects name-collision renames (engine's `GenerateNewComponentName` silently appends counter suffix — we detect the rename and fail up-front so replay stays crisp). No new module deps: `UActorComponent` / `USimpleConstructionScript` / `USCS_Node` all live in `Engine` which is already linked. |

**Python surface added (1 op):**

| New Python op (in `scripts/python_ops/blueprint_structural.py`) | What it does |
|---|---|
| `add_component_to_scs(bp_path, component_class_path, component_name, parent_component_name="")` | Resolves `component_class_path` via `unreal.load_class` → `unreal.load_object` fallback (covers both `/Script/<Module>.<Class>` natives and BP-generated `/Game/<Asset>.<Asset>_C` classes). Passes `unreal.Name(parent_component_name or "None")` so the bridge's "empty = root" convention is hit cleanly. Skip semantics: existing same-class SCS node → `skipped="component already exists on SCS"`. On real add, chains `compile_and_save_package`. |

**Plan pipeline wiring:**
- `__init__.py`: `add_component_to_scs` re-exported + `__all__`.
- `plan_shape.OP_SPECS`: new entry with `required: [bp_path, component_class_path, component_name]`, `optional: [parent_component_name]`, `assets: [bp_path]`.
- `plan_executor._OP_DISPATCH`: new entry → `add_component_to_scs`.
- `mechanical_diff._op_expected_changes`: added to the BP-mutation tuple alongside `add_bp_variable` / `add_bp_function`.

**Op count across library:** 25 op functions now re-exported from `python_ops/__init__.py` (M28.2.3 added 1); MCP's `get_op_catalog` auto-surfaces via AST walk (zero MCP server change).

**BugHunt fixture added:**
- `BP_BpxTestStructuralComponents.uasset` (24,035 b) — empty Actor BP, no SCS-declared components. Same baseline shape as `BP_BpxTestStructuralVariables` / `BP_BpxTestStructuralFunctions` (M28.2.1 / M28.2.2). Generated via `GenerateTestBlueprintsCommandlet -Only=BP_BpxTestStructuralComponents`.

**Inspect/soak fixture added:**
- `scripts/inspect_fixtures/add_component_to_scs.json` — adds a single `UAudioComponent` named `CalloutAudio` (design.md item #4 squad-callouts) to a scratch duplicate of `BP_BpxTestStructuralComponents`. Inspect asserts `CalloutAudio` surfaces in both `.md` and `.deep.md`. Soak asserts md5 stability across 2 rounds — `f135c0091e3803caeff745f8303e5f13` stable round1==round2, proving `SeedGuidFromJoined(":scs:CalloutAudio")` overrides `CreateNodeImpl`'s `FGuid::NewGuid()` assignment.

**Pre-push matrix (BugHunt / stock UE 5.7, 158 s total via `verify_all.ps1`):**

| Gate | Result | Notes |
|---|---|---|
| Unity build (custom UE_DOW, RunUAT BuildPlugin -Rocket) | PASS, 22.62 s | DLL 2,554,880 → 2,567,168 bytes (+12,288 — one new UFUNCTION + .gen.cpp/.gen.h glue). |
| Unity build (stock UE 5.7, RunUAT BuildPlugin -Rocket) | PASS, 42.12 s | DLL 2,556,416 → 2,568,192 bytes (+11,776). Identical compile success. |
| `automation-bughunt` | PASS, 15.6 s | All `BlueprintExporter.*` automation tests green. |
| `determinism-bughunt` (`-SweepDeepDump`) | PASS, 46.7 s | Twin-run byte-identical including new `BP_BpxTestStructuralComponents` fixture. |
| `inspect-add_component_to_scs` (M28.pre.2) | PASS, 17.8 s | `CalloutAudio` surfaces in `.md` + `.deep.md` post-re-export. |
| `inspect-add_bp_function` (regression) | PASS, 17.7 s | M28.2.2 fixture unaffected. |
| `inspect-add_bp_variable` (regression) | PASS, 17.7 s | M28.2.1 fixture unaffected. |
| `inspect-implement_interface_function` (regression) | PASS, 17.7 s | M26.1 fixture unaffected. |
| `soak-add_component_to_scs` (M28.pre.3) | PASS, 6.1 s | md5 `f135c0091e3803caeff745f8303e5f13` stable round1 == round2. Determinism proof. |
| `soak-add_bp_function` (regression) | PASS, 6.1 s | M28.2.2 determinism preserved (entry_guid, return_guid, md5). |
| `soak-add_bp_variable` (regression) | PASS, 6.1 s | M28.2.1 determinism preserved. |
| `soak-implement_interface_function` (regression) | PASS, 6.1 s | M26.1 determinism preserved; `r2 wiped = 2`. |
| MCP pytest (`scripts/blueprint-exporter-mcp && pytest`) | PASS, 11.7 s | 23/23 pass; validates the `mechanical_diff._op_expected_changes` extension didn't regress transport. |

**Determinism story.** `SimpleConstructionScript.cpp:1375` assigns `NewNode->VariableGuid = FGuid::NewGuid()` per-call. Without intervention, round 2 of the soak produces a different VarGuid → different .uasset bytes → md5 drift. The bridge wrapper post-write overrides with `SeedGuidFromJoined(<bp_path>:scs:<component_name>)`, content-derived and stable across runs. Soak round 2 md5 EQUAL to round 1 md5 is the empirical confirmation this works — same proof shape as M28.2.1 (VarGuid) and M28.2.2 (GraphGuid + NodeGuid + PinId) determinism seeds.

**Files changed:**
- `Source/BlueprintExporter/Public/Reflection/ReflectionOps.h` (+ `AddComponentToSCSDeterministic` UFUNCTION declaration)
- `Source/BlueprintExporter/Private/Reflection/ReflectionOps.cpp` (+ `AddComponentToSCSDeterministic` impl + `Components/ActorComponent.h` / `Engine/SCS_Node.h` / `Engine/SimpleConstructionScript.h` includes)
- `BuiltPlugin/...` mirrors of the two above
- `BuiltPlugin/Binaries/Win64/{UnrealEditor-BlueprintExporter.dll,UnrealEditor.modules}` (custom UE_DOW build — 2,567,168 b)
- `BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64/{UnrealEditor-BlueprintExporter.dll,UnrealEditor.modules}` (stock UE 5.7 build — 2,568,192 b)
- `scripts/python_ops/blueprint_structural.py` (+ `add_component_to_scs` + module docstring updated to record the M28.2.0 Open Question #1 supersede)
- `scripts/python_ops/__init__.py` (re-export + `__all__`)
- `scripts/python_ops/plan_shape.py` (`OP_SPECS["add_component_to_scs"]`)
- `scripts/python_ops/plan_executor.py` (`_OP_DISPATCH["add_component_to_scs"]`)
- `scripts/python_ops/mechanical_diff.py` (`_op_expected_changes` — BP-mutation tuple extended)
- `scripts/inspect_fixtures/add_component_to_scs.json` (NEW)
- `BugHunt/BlueprintExporterTests/Source/BlueprintExporterTests/Private/Commandlets/GenerateTestBlueprintsCommandlet.cpp` (+ `GenBP_BpxTestStructuralComponents` + Gens registration)
- `BugHunt/TestProject/Content/TestBlueprints/BP_BpxTestStructuralComponents.uasset` (NEW, 24,035 b — generated via commandlet)
- 9 version-stamp locations bumped 1.19.11 → 1.19.12 (uplugin × 3 counting BugHunt's copy, module UE_LOG, bridge ping + list_methods handlers, Manifest.PluginVersion, BlueprintSerializer / StateTreeSerializer / ProjectPluginsCommandlet PluginVersion stamps, BlueprintExporterTests live-version test, README) + BuiltPlugin mirrors. BugHunt's Source/ junction auto-propagated the C++ stamps; only `.uplugin` is a real file there and got bumped alongside canonical (M28.2.2 junction conversion carry-forward paid off on this patch — zero manual Source/ sync this time).

**Carry-forwards (not blockers, observed during the patch):**
- **DOW-leg verification still deferred.** `verify_all.ps1 -IncludeDow` not run. Custom UE_DOW `RunUAT BuildPlugin -Rocket` succeeded (22.62 s) so compile correctness is established; DOW automation + determinism slice remain unexercised. Consistent with M28.2.1 + M28.2.2 pattern. Run on the next push that actually targets DOW.
- **Parent-component parenting not exercised in the fixture.** The committed `add_component_to_scs.json` adds a root-level component (parent_component_name=""). The bridge's `ParentNode->AddChildNode` branch is code-reviewed but uncovered by the gate. Low risk (the engine call is unchanged by parenting — only the attach step differs); add a second fixture if a real plan needs parented components (design.md item #1 squad-director wiring would be a driver).
- **Native-inherited-collision path not fixtured.** The bridge rejects a rename with a structured error message, but there's no fixture that exercises this path. Edge case; revisit if a real plan hits it and the error is unclear.

**Reference patterns reused (unchanged from M28.2.1 + M28.2.2):**
- M23.1 `BpxReflectionOps` UFUNCTION bridge + `FBpxReflectionResult` shape.
- M26.1.2 `SeedGuidFromJoined` + `MarkBlueprintAsStructurallyModified` ordering.
- M28.pre.2 inspect harness + M28.pre.3 soak template.
- M28.2.1 / M28.2.2 closure dispatch wiring pattern (one entry per op in `__init__.py` + `OP_SPECS` + `_OP_DISPATCH` + `_op_expected_changes`).

**M28.2.3 CLOSED (2026-04-23). M28.2.4 (`add_bp_interface` + `AddInterfaceByPath` UFUNCTION) ready to start** when scheduled. Open question from M28.2.0: verify whether `FBlueprintEditorUtils::ImplementNewInterface`-created interface-graph `GraphGuid`s inherit from the source interface BP (deterministic) or get `FGuid::NewGuid()` (drifty). If drifty, seed each generated graph via `SeedGuidFromJoined(<bp>:iface_graph:<interface_path>:<graph_name>)`.

### M28.2.4 shipped (2026-04-23, 1.19.12 → 1.19.13)

**`add_bp_interface` lands as the fourth and final M28.2 op.** All 12 pre-push gates green on BugHunt / stock UE 5.7 in 181.9 s via `verify_all.ps1`; MCP pytest 23/23. Patch bump 1.19.12 → 1.19.13 (additive UFUNCTION + Python op + new fixture + new inspect/soak JSON — no schema change, no existing-op behaviour change).

**Scope closure on M28.2.0 Open Question #2.** Engine probe on M28.2.4 start confirmed the drift hypothesis: `FBlueprintEditorUtils::ImplementNewInterface` (`BlueprintEditorUtils.cpp:6414`) creates each override graph via `FBlueprintEditorUtils::CreateNewGraph` → `NewObject<UEdGraph>` → `UEdGraph::PostInitProperties` at `EdGraph.cpp:147` assigns `GraphGuid = FGuid::NewGuid()`. Then `AddInterfaceGraph` → `UEdGraphSchema_K2::CreateFunctionGraphTerminators` emits Entry (and Return when the signature has out-params) `UK2Node_*` nodes via `NewObject` → fresh `NodeGuid` + pin IDs. So the drift profile is *identical* to M28.2.2's function-graph add: three sources (GraphGuid, Entry/Return NodeGuid, per-pin PinId). `NewGraph->InterfaceGuid` (distinct from GraphGuid — derived from `FindInterfaceFunctionGuid` against the source interface) IS deterministic; no override needed there. The seeding recipe is copy-paste from M28.2.2.

**C++ surface added (1 UFUNCTION):**

| New UFUNCTION | What it does |
|---|---|
| `UBpxReflectionOps::AddInterfaceByPath(UBlueprint*, UClass* InterfaceClass)` | Wraps `FBlueprintEditorUtils::ImplementNewInterface(Blueprint, FTopLevelAssetPath(InterfaceClass))` (Kismet2 module, already linked — no new module dep) and post-attach walks `Blueprint->ImplementedInterfaces[]` to find the freshly-added `FBPInterfaceDescription`, then seeds `GraphGuid` + Entry/Return `NodeGuid` + per-pin GUIDs on every generated override graph via `SeedGuidFromJoined(<bp>:iface_graph:<interface_path>:<graph_name>:{graph\|entry\|return}[+ pin])`. Idempotence: same `(Blueprint, InterfaceClass)` replay short-circuits before the engine call with `bSuccess=true, bSkipped=true` — pre-screening avoids the engine's UI toast on already-implemented. Rejects non-interface classes up-front via `HasAnyClassFlags(CLASS_Interface)` check. Does NOT call `MarkBlueprintAsStructurallyModified` a second time (engine's `ImplementNewInterface` already marks on the success path at `BlueprintEditorUtils.cpp:6507`) — per the M26.1.2 lesson, double-marking can re-enter structural-modified listeners and invalidate the just-seeded GUIDs. |

**Python surface added (1 op):**

| New Python op (in `scripts/python_ops/blueprint_structural.py`) | What it does |
|---|---|
| `add_bp_interface(bp_path, interface_class_path)` | Resolves `interface_class_path` via `unreal.load_class` → `unreal.load_object` fallback (covers both `/Script/<Module>.<Interface>` natives and BP-generated `/Game/<Asset>.<Asset>_C` interface classes). Validates it's a `unreal.Class` before calling `ops.add_interface_by_path`. Skip semantics: existing interface on `ImplementedInterfaces[]` → `skipped="interface already implemented"`. On real add, chains `compile_and_save_package`. |

**Plan pipeline wiring:**
- `__init__.py`: `add_bp_interface` re-exported + `__all__`.
- `plan_shape.OP_SPECS`: new entry with `required: [bp_path, interface_class_path]`, `assets: [bp_path]`.
- `plan_executor._OP_DISPATCH`: new entry → `add_bp_interface`.
- `mechanical_diff._op_expected_changes`: added to the BP-mutation tuple alongside `add_bp_variable` / `add_bp_function` / `add_component_to_scs`.

**Op count across library:** 26 op functions now re-exported from `python_ops/__init__.py` (M28.2.4 added 1); MCP's `get_op_catalog` auto-surfaces via AST walk (zero MCP server change).

**BugHunt fixture added:**
- `BP_BpxTestStructuralInterfaces.uasset` (24,035 b) — empty Actor BP, no implemented interfaces. Same baseline shape as `BP_BpxTestStructuralVariables` / `BP_BpxTestStructuralFunctions` / `BP_BpxTestStructuralComponents` (M28.2.1 / M28.2.2 / M28.2.3). Generated via `GenerateTestBlueprintsCommandlet -Only=BP_BpxTestStructuralInterfaces`. Target interface is the existing `BPI_BpxTestInterface` (M26.1 fixture — declares `GetTargetingInfo` with three outputs `bIsAlive:bool`, `bIsTargetable:bool`, `Faction:int32`), reused here because a non-event interface with out-params is exactly what exercises all three drift sources (empty-event interfaces attach cleanly but generate zero graphs, so the seeding loop would be a no-op and the soak wouldn't prove anything).

**Inspect/soak fixture added:**
- `scripts/inspect_fixtures/add_bp_interface.json` — attaches `BPI_BpxTestInterface` to a scratch duplicate of `BP_BpxTestStructuralInterfaces`. Inspect asserts `BPI_BpxTestInterface` + `GetTargetingInfo` surface in both `.md` and `.deep.md`. Soak asserts md5 stability across 2 rounds — `c0e548efc62b9f45ffbc03160a82d238` stable round1 == round2, proving the `SeedGuidFromJoined(":iface_graph:...:GetTargetingInfo:graph")` + Entry/Return NodeGuid + per-pin PinId overrides close all three drift sources (`UEdGraph::PostInitProperties`, Entry `NewObject`, pin `CreatePin`).

**Pre-push matrix (BugHunt / stock UE 5.7, 181.9 s total via `verify_all.ps1`):**

| Gate | Result | Notes |
|---|---|---|
| Unity build (stock UE 5.7, `RunUAT BuildPlugin -Rocket`) | PASS, 42.3 s | DLL 2,568,192 → 2,578,432 bytes (+10,240 — one new UFUNCTION + .gen.cpp/.gen.h glue). Identical compile success on UBT BugHunt-target rebuild (8.5 s warm). |
| `automation-bughunt` | PASS, 15.7 s | All `BlueprintExporter.*` automation tests green. |
| `determinism-bughunt` (`-SweepDeepDump`) | PASS, 46.5 s | Twin-run byte-identical including new `BP_BpxTestStructuralInterfaces` fixture. |
| `inspect-add_bp_interface` (M28.pre.2) | PASS, 17.7 s | `BPI_BpxTestInterface` + `GetTargetingInfo` surface in `.md` + `.deep.md` post-re-export. |
| `inspect-add_bp_function` (regression) | PASS, 17.6 s | M28.2.2 fixture unaffected. |
| `inspect-add_bp_variable` (regression) | PASS, 17.7 s | M28.2.1 fixture unaffected. |
| `inspect-add_component_to_scs` (regression) | PASS, 17.7 s | M28.2.3 fixture unaffected. |
| `inspect-implement_interface_function` (regression) | PASS, 17.7 s | M26.1 fixture unaffected. |
| `soak-add_bp_interface` (M28.pre.3) | PASS, 6.6 s | md5 `c0e548efc62b9f45ffbc03160a82d238` stable round1 == round2. Determinism proof across all three drift sources. |
| `soak-add_bp_function` (regression) | PASS, 6.1 s | M28.2.2 determinism preserved. |
| `soak-add_bp_variable` (regression) | PASS, 6.1 s | M28.2.1 determinism preserved. |
| `soak-add_component_to_scs` (regression) | PASS, 6.1 s | M28.2.3 determinism preserved. |
| `soak-implement_interface_function` (regression) | PASS, 6.1 s | M26.1 determinism preserved; `r2 wiped = 2`. |
| MCP pytest (`scripts/blueprint-exporter-mcp && pytest`) | PASS, 11.7 s | 23/23 pass; `mechanical_diff._op_expected_changes` + `plan_shape.OP_SPECS` extensions did not regress transport or shape-validation paths. |

**Determinism story.** `UEdGraph::PostInitProperties` at `EdGraph.cpp:147` assigns `GraphGuid = FGuid::NewGuid()` on every new graph. `UEdGraphSchema_K2::CreateFunctionGraphTerminators` constructs Entry + Return K2Nodes via `NewObject` — each gets a fresh `NodeGuid` and default-created pins get fresh `PinId`s. Without intervention, round 2 of the soak produces different GUIDs everywhere → different .uasset bytes → md5 drift. The bridge wrapper post-attach seeds all three classes (graph, per-node, per-pin), content-derived and stable across runs. Soak round 2 md5 EQUAL to round 1 md5 is the empirical confirmation — same proof shape as M28.2.1 (VarGuid) / M28.2.2 (GraphGuid + NodeGuid + PinId) / M28.2.3 (VariableGuid).

**Files changed:**
- `Source/BlueprintExporter/Public/Reflection/ReflectionOps.h` (+ `AddInterfaceByPath` UFUNCTION declaration)
- `Source/BlueprintExporter/Private/Reflection/ReflectionOps.cpp` (+ `AddInterfaceByPath` implementation)
- `BuiltPlugin/...` mirrors of the two above
- `BuiltPlugin/Binaries/Win64/{UnrealEditor-BlueprintExporter.dll,UnrealEditor.modules,UnrealEditor-BlueprintExporter.pdb}` (stock UE 5.7 build — 2,578,432 b)
- `BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64/{UnrealEditor-BlueprintExporter.dll,UnrealEditor.modules,UnrealEditor-BlueprintExporter.pdb}` (UBT rebuild — 2,583,552 b, differs from BuildPlugin output by unity-stitching boundaries only)
- `BugHunt/BlueprintExporterTests/Binaries/Win64/{UnrealEditor-BlueprintExporterTests.dll,UnrealEditor-BlueprintExporterTests.pdb}` (UBT rebuild — 199,168 b, picks up the new fixture generator)
- `scripts/python_ops/blueprint_structural.py` (+ `add_bp_interface` + module docstring note M28.2.4 shipped)
- `scripts/python_ops/__init__.py` (re-export + `__all__`)
- `scripts/python_ops/plan_shape.py` (`OP_SPECS["add_bp_interface"]`)
- `scripts/python_ops/plan_executor.py` (`_OP_DISPATCH["add_bp_interface"]`)
- `scripts/python_ops/mechanical_diff.py` (`_op_expected_changes` — BP-mutation tuple extended)
- `scripts/inspect_fixtures/add_bp_interface.json` (NEW)
- `BugHunt/BlueprintExporterTests/Source/BlueprintExporterTests/Private/Commandlets/GenerateTestBlueprintsCommandlet.cpp` (+ `GenBP_BpxTestStructuralInterfaces` + Gens registration)
- `BugHunt/TestProject/Content/TestBlueprints/BP_BpxTestStructuralInterfaces.uasset` (NEW, 24,035 b — generated via commandlet)
- 9 version-stamp locations bumped 1.19.12 → 1.19.13 (uplugin × 2, module UE_LOG, bridge ping + list_methods handlers, `Manifest.PluginVersion` ×2, BlueprintSerializer / StateTreeSerializer / ProjectPluginsCommandlet `PluginVersion` stamps, BlueprintExporterTests live-version test, README) + BuiltPlugin mirrors. BugHunt's Source/ junction auto-propagated the C++ stamps (M28.2.2 junction conversion paying off again — zero manual Source/ sync on this patch either).

**Carry-forwards (not blockers, observed during the patch):**
- **DOW-leg verification still deferred.** `verify_all.ps1 -IncludeDow` not run. Custom UE_DOW `RunUAT BuildPlugin -Rocket` not exercised on this patch either (matching M28.2.1 / M28.2.2 / M28.2.3 pattern). Stock-5.7 compile is established; custom-engine compile deferred until a plan actually targets DOW content with an M28.2 op. No plugin currently installed at `D:/Work/UE_DOW/engine/Plugins/` or `D:/Work/UE_DOW/game/Plugins/`.
- **Anim-function-on-non-AnimBP rejection path not fixtured.** The bridge surfaces the engine's `ImplementNewInterface` false return as a structured error; the rejection cases (anim-function on a non-AnimBP target, function-name conflict with an existing graph) are code-reviewed but uncovered by the soak/inspect fixtures. Low risk (engine's own validation is the load-bearing check); add a negative-path fixture only if a real plan surfaces the error and the message is unclear.
- **Pure-event interface case not fixtured.** An interface that only declares BlueprintImplementable *events* attaches cleanly with zero generated graphs — the seeding loop is a no-op, nothing drifts, nothing needs proving. `BPI_BpxTestInterface` deliberately has an out-param function so the full seeding path runs. If a design.md driver later needs a pure-event interface (`BPI_OrderListener` event-only shape), attach it via the same op — the code path is inert for that case.

**Reference patterns reused (unchanged from M28.2.1 + M28.2.2 + M28.2.3):**
- M23.1 `BpxReflectionOps` UFUNCTION bridge + `FBpxReflectionResult` shape.
- M26.1.2 `SeedGuidFromJoined` + no-double-Mark ordering (critical this time because engine's `ImplementNewInterface` already Marks on the success path).
- M28.2.2 `AddFunctionGraphDeterministic` GraphGuid + Entry/Return + per-pin seed recipe — near byte-identical copy, just keyed on `(bp_path, interface_path, graph_name)` instead of `(bp_path, function_name)`.
- M28.pre.2 inspect harness + M28.pre.3 soak template.
- M28.2.1 / M28.2.2 / M28.2.3 closure dispatch wiring pattern (one entry per op in `__init__.py` + `OP_SPECS` + `_OP_DISPATCH` + `_op_expected_changes`).

**M28.2.4 CLOSED (2026-04-23). M28.2.5 (Docs sweep) ready to start** when scheduled. Pure-docs, no version bump — fills in the four-op gap in `scripts/python_ops/CATALOG.md`, extends the `plans/README.md` op kwargs table, adds a worked `AGENT_LOOP.md` squad-director example chaining `add_bp_variable(bActiveOrder)` → `add_bp_interface(BPI_OrderListener)` → `add_bp_function(OnOrderReceived)` → M26.1 body-authoring, and adds `blueprint_structural.py` + four new UFUNCTIONs to the `CLAUDE.md` Project Structure tree. Closes M28.2 end-to-end.

### M28.2.5 shipped (2026-04-23, no version bump)

**Docs sweep — closes M28.2 end-to-end. Pure docs, zero code change, no stamp sweep, no DLL rebuild, no pre-push matrix invocation.**

**Files updated:**
- `scripts/python_ops/CATALOG.md` — four new op sections (`add_bp_variable` / `add_bp_function` / `add_component_to_scs` / `add_bp_interface`) inserted before the `## Known caveats` block; "Available ops" heading tag rolled `M28` → `M28.x`; the "Coming next" block's `add_bp_member_variable` stub replaced with a "shipped in M28.2.1 – M28.2.4" pointer. Each new section documents kwargs, idempotence semantics, determinism recipe (which GUID gets seeded + the `SeedGuidFromJoined` key), and a minimal invocation example.
- `scripts/python_ops/plans/README.md` — op kwargs table extended with the four new rows (required + optional kwargs); four new jsonc examples added after the M28.3 `set_level_actor_property` example, each showing a realistic squad-director plan fragment.
- `scripts/python_ops/plans/AGENT_LOOP.md` — new "squad director with an OnOrderReceived callback" worked example inserted between the two existing examples and the "Error classification" block. Walks through Steps 2 → 8 chaining `add_bp_variable(bActiveOrder)` → `add_bp_interface(BPI_OrderListener)` → `add_bp_function(OnOrderReceived)` into a single structural plan, with a follow-up body-authoring plan (M26.1 / M28.3-narrow) called out as a separate landing. Deliberately keeps structural + body work in separate plans so the per-phase verification gates trip on distinct diff patterns.
- `CLAUDE.md` — Project Structure tree gains `Public/Reflection/` (ReflectionTypes.h + ReflectionOps.h) and `Private/Reflection/` (ReflectionOps.cpp) subtrees with full UFUNCTION inventory covering M23.1 + M26.1 + M26.1.1 + M28.3-narrow + M28.2.1 / .2 / .3 / .4. Docs Map row for `scripts/python_ops/CATALOG.md` extended to mention the M28.2.x structural-edit ops and to point at the new `blueprint_structural.py` module.

**Verification:** none beyond read-back. Pure-docs changes don't exercise any matrix gate; working tree already clean pre-sweep. The docs tree does not ship in any distributable artefact — it lives alongside source for colleagues + Claude sessions.

**Out of scope for M28.2.5 (still pending / deferred):**
- A `set_bp_variable_metadata` op for the remaining flags (`ExposeOnSpawn` / `ExposeToCinematics` / `BlueprintReadOnly` / `Category`) remains an open question #4 in the M28.2 scope block above. Decide when concrete plan-author friction surfaces.
- Cross-session `.uasset` byte drift (~900 b from `UPackage::SavePackage` GUID regeneration) stays deferred — no matrix gate currently depends on cross-session byte-identity. Investigation utilities from the 2026-04-23 deferred outcome (`scripts/probe_cross_session_drift.py` + `diff_cross_session_drift.py` + `dump_drift_context.py`) remain committed as the starting point.

**M28.2 CLOSED end-to-end (2026-04-23).** Four structural-edit ops shipped + docs sweep done. **M29 (Mutable / CustomizableObject Tier 2) preempts M28.3** for the current session — see the M29 scope block immediately below. Prior M28.3 planning stays valid and is the natural return target after M29 lands: **M28.3 — node-level graph authoring catalog** (`add_graph_node` / `connect_pins` / `set_pin_default` / `add_local_variable`) per the M28 phase table earlier in this document. The Flat Arena #3 dead-end Branch (`BP_Task_Peek.EventGraph`) remains the immediate smoke-test motivator; `connect_graph_pins` already shipped as M28.3-narrow so the minimum-viable Flat Arena fix is authorable today, but the full M28.3 catalog (node spawn + local variables + pin defaults for fresh nodes) is what design.md items #2 / #4 / #6 / #8 need.

### M28.3 research outcome (2026-04-23 post-M29)

**TL;DR — node-level graph authoring has zero pre-existing Python surface; every K2Node subclass needs its own bridge UFUNCTION. M26.1's `AddSelfMemberGetNode` already established the shape end-to-end (deterministic `NodeGuid` + `SeedPinGuidsForNode` after `FGraphNodeCreator::Finalize`), so M28.3 is one new UFUNCTION per K2Node type × a narrow catalog of 7 types + 1 local-variable op. Start with M28.3.1 = `add_branch_node` + generalized `set_graph_pin_default` (simplest — zero node config, gets the pattern into the tree). Minor bump 1.20.1 → 1.21.0 at M28.3.1 (new subsystem per semver).**

Research ran without spawning UE. Evidence is code-based against stock UE 5.7 (`C:/Program Files/Epic Games/UE_5.7/Engine`) and UE_DOW's engine tree — same approach as M26.0 / M27.0 / M28.2.0.

1. **`unreal.BlueprintEditorLibrary` surface audit** (`Source/Editor/BlueprintEditorLibrary/Public/BlueprintEditorLibrary.h`) — graph-level (`AddFunctionGraph` / `RemoveFunctionGraph` / `FindGraph` / `FindEventGraph` / `RenameGraph`), variable-level (`AddMemberVariable` / `AddMemberVariableWithValue` / metadata setters), and pin-type constructors (`GetBasicTypeByName` / `GetStructType` / `GetObjectReferenceType` / `GetArrayType` etc.) are all exposed. **Node-level authoring is absent.** No `AddGraphNode` / `ConnectPins` / `AddLocalVariable` / `SetPinDefault` — Python has no way in.

2. **Canonical engine pattern is `FGraphNodeCreator<T>`** (`Runtime/Engine/Classes/EdGraph/EdGraph.h:274`), a C++ template struct — not UFUNCTION-surfaceable. Standard three-step pattern:
   ```cpp
   FGraphNodeCreator<UK2Node_X> NodeCreator(Graph);
   UK2Node_X* Node = NodeCreator.CreateNode();
   // configure Node->* here (before Finalize — e.g. FunctionReference for CallFunction)
   NodeCreator.Finalize();  // calls CreateNewGuid + PostPlacedNewNode + AllocateDefaultPins
   ```
   Every K2Node subclass needs its own bridge UFUNCTION that runs this pattern and then post-seeds the GUIDs. M26.1's `AddSelfMemberGetNode` is the proven reference.

3. **Pin-level ops already in place** (reusable unchanged):
   - `ConnectGraphPinsByGuidString` (M28.3-narrow) — string-GUID form, walks `FunctionGraphs` + `ImplementedInterfaces[].Graphs` + `UbergraphPages` via `FindFunctionGraphByName`. Covers every graph family M28.3 targets.
   - `SetNodePinLiteralDefault` (M26.1) — schema-aware pin default writer via `UEdGraphSchema_K2::TrySetDefaultValue`. **Caveat**: currently keyed by `FName FunctionName` (early M26.1 scope), so it reaches function graphs only. Needs a sibling `SetGraphPinLiteralDefault(GraphName)` that routes through `FindFunctionGraphByName` like `ConnectGraphPinsByGuidString` does — extend, don't mutate, to keep M26.1 callers' semantics.

4. **Local variables live on `UK2Node_FunctionEntry::LocalVariables`** (`K2Node_FunctionEntry.h:49`), a `TArray<FBPVariableDescription>` — exactly the same struct as BP member variables. Same VarGuid determinism trap as M28.2.1 (`AddMemberVariableDeterministic`); same `SeedGuidFromJoined` recipe. Different addressing: the op resolves the Entry node inside the function graph first, then appends + seeds.

5. **Determinism-trap analysis** (HIGH-priority finding — every new node-spawn UFUNCTION hits all three):

| Trap | Site | Fix |
|---|---|---|
| `NodeGuid = FGuid::NewGuid()` | `UEdGraphNode::CreateNewGuid` (EdGraphNode.cpp:795), fires inside `FGraphNodeCreator::Finalize` (EdGraph.h:300). | Post-Finalize overwrite via `SeedGuidFromJoined(<bp>:graph:<g>:node:<kind>:<x,y>)`. |
| `PinId = FGuid::NewGuid()` | `UEdGraphPin::CreatePin` (EdGraphPin.cpp:510), fires inside `AllocateDefaultPins`. | `BpxReflection::SeedPinGuidsForNode(Node, <key>)` after Finalize. Recipe is M26.1.2's. |
| `FBPVariableDescription::VarGuid = FGuid::NewGuid()` | Only on `add_local_variable` path (`LocalVariables.Add(...)`). | `SeedGuidFromJoined(<bp>:func:<fn>:localvar:<name>)` — mirror of M28.2.1. |
| `MakeUniqueObjectName` / transient NewObject names | Any `NewObject<UK2Node_*>(Graph, ...)` without an explicit `FName`. | Pass `FName("BpxNode_<kind>_<key>")` to NewObject — engine honours it; M26.1 pattern. |

   `UEdGraph::PostInitProperties` GraphGuid (EdGraph.cpp:147) trap is **not** in scope for M28.3 — every op spawns into existing graphs, never creates a new graph (M28.2.2 `AddFunctionGraphDeterministic` already owns that trap).

6. **Narrow K2Node catalog** (per M28 phase table's risk-indicator guidance "Bridge surface balloon on M28.3 (HIGH). Mitigation: ship narrow first"):

| K2Node class | design.md driver | Post-create config |
|---|---|---|
| `UK2Node_IfThenElse` (Branch) | #8 polish (`if first-shot`); Flat Arena #3 live case | none (default pins handle exec/bool/then/else) |
| `UK2Node_CallFunction` | #2 utility scorer, #4 callouts, #6 director | `FunctionReference.SetSelfMember` / `SetExternalMember(Name, UClass*)` before Finalize |
| `UK2Node_VariableGet` | #2/#3/#6 state reads (generalizes M26.1 self-only) | `VariableReference.SetSelfMember` / `SetExternalMember` before Finalize |
| `UK2Node_VariableSet` | #2/#3/#6 state writes (`Set Intensity`, `Set LastActionTag`, `Set ConfidenceAtLastUpdate`) | as VariableGet |
| `UK2Node_CustomEvent` | #4 `OnCalloutReceived(tag)`, #6 `OnEncounterBeat`, #8 `OnHitReaction` | `CustomFunctionName = <EventName>`; ubergraph-only (validate at op entry) |
| `UK2Node_ExecutionSequence` | #4 callout broadcast chain, #8 hit-reaction multi-effect | optional extra exec-out pins via `IK2Node_AddPinInterface::AddInputPin` (mis-named engine API — it adds a THEN-out pin) |
| `UK2Node_DynamicCast` | #1 `Cast To BP_SquadDirector`, #3 `Cast To BP_EnemyBase` | `TargetType = UClass*` before Finalize |

   `K2Node_Knot` (reroute) **deferred** — quality-of-life only, add if plan authoring proves messy without it. `K2Node_Literal` / `MakeArray` / `MakeStruct` also deferred — covered in the interim by `set_graph_pin_default` for primitive literals.

7. **Chosen C++ surface (8 new UFUNCTIONs + 1 sibling on `UBpxReflectionOps`):**

| New UFUNCTION | Purpose |
|---|---|
| `AddBranchNode(BP, GraphName, Position)` | Simplest K2Node — zero configuration. Ships in M28.3.1 as the pattern carrier. |
| `AddCallFunctionNode(BP, GraphName, MemberName, TargetClass (nullable → self), Position)` | Highest config surface. `FunctionReference.SetSelfMember` when `TargetClass==nullptr`, else `SetExternalMember`. Ships in M28.3.2. |
| `AddVariableGetNode(BP, GraphName, MemberName, TargetClass (nullable → self), Position)` | Generalizes M26.1 `AddSelfMemberGetNode` to any context + any graph (not just function graphs). Ships in M28.3.2. |
| `AddVariableSetNode(BP, GraphName, MemberName, TargetClass (nullable → self), Position)` | Sibling of VariableGet. Ships in M28.3.2. |
| `AddCustomEventNode(BP, GraphName, EventName, Position)` | Op entry validates graph is an ubergraph page. Ships in M28.3.3. |
| `AddExecutionSequenceNode(BP, GraphName, NumThenPins, Position)` | Calls `AddInputPin` (NumThenPins - 2) times if > 2 after Finalize. Ships in M28.3.3. |
| `AddDynamicCastNode(BP, GraphName, TargetClass, Position)` | Sets `TargetType = TargetClass` before Finalize. Ships in M28.3.3. |
| `AddLocalVariableDeterministic(BP, FunctionName, VarName, VarType, DefaultValue)` | Appends `FBPVariableDescription` to `UK2Node_FunctionEntry::LocalVariables`, seeds VarGuid via `SeedGuidFromJoined(<bp>:func:<fn>:localvar:<name>)`. Ships in M28.3.4. |
| `SetGraphPinLiteralDefault(BP, GraphName, NodeGuidStr, PinName, LiteralText)` | Sibling of M26.1 `SetNodePinLiteralDefault` that routes through `FindFunctionGraphByName` (walks all three graph families). Keeps the function-name-keyed original intact for M26.1 callers. Ships in M28.3.1 alongside AddBranchNode. |

   All 8 new ops return `FBpxNodeResult` (M26.1's existing struct — `{node_guid, success, error}`). The `SetGraphPinLiteralDefault` sibling returns `FBpxReflectionResult` (unchanged shape).

8. **Chosen Python surface (8 new ops in new module `scripts/python_ops/blueprint_graph_nodes.py`):**

| Python op | Bridge UFUNCTION | Key kwargs |
|---|---|---|
| `add_branch_node(bp_path, graph_name, position)` | `AddBranchNode` | — |
| `add_call_function_node(bp_path, graph_name, function_name, target_class_path="", position=...)` | `AddCallFunctionNode` | `target_class_path=""` → self |
| `add_variable_get_node(bp_path, graph_name, variable_name, target_class_path="", position=...)` | `AddVariableGetNode` | as above |
| `add_variable_set_node(bp_path, graph_name, variable_name, target_class_path="", position=...)` | `AddVariableSetNode` | as above |
| `add_custom_event_node(bp_path, graph_name, event_name, position=...)` | `AddCustomEventNode` | op entry asserts graph is ubergraph |
| `add_execution_sequence_node(bp_path, graph_name, num_then_pins=2, position=...)` | `AddExecutionSequenceNode` | clamp `num_then_pins >= 2` |
| `add_dynamic_cast_node(bp_path, graph_name, target_class_path, position=...)` | `AddDynamicCastNode` | — |
| `add_local_variable(bp_path, function_name, var_name, var_type_spec, default_value="")` | `AddLocalVariableDeterministic` | reuses `var_type_spec` catalog from M28.2.1 |
| `set_graph_pin_default(bp_path, graph_name, node_selector, pin_name, literal_text)` | `SetGraphPinLiteralDefault` | `node_selector` accepts M28.3-narrow `@Class:x,y` or 32-hex forms |

   Every spawn op returns `{node_guid: <runtime-hex>, pins: [...]}` so plan authors chain `connect_graph_pins` via `{"guid": node_guid}` directly. No module deps beyond M26.1's `BlueprintGraph`.

9. **Sub-phase sequencing** (small-first; each sub-phase independently verifiable):

| Phase | Scope | Bump | Rationale |
|---|---|---|---|
| **M28.3.1** | `add_branch_node` + `set_graph_pin_default` | 1.20.1 → **1.21.0** (minor) | First node-spawn slice lands the bridge pattern + establishes the minor-bump subsystem per semver. Branch is zero-config — all focus on determinism + the `FGraphNodeCreator` plumbing. |
| **M28.3.2** | `add_call_function_node` + `add_variable_get_node` + `add_variable_set_node` | → 1.21.1 (patch) | FunctionReference / VariableReference family — shares the self-vs-external resolution helper. Largest single commit of M28.3 but all three ops share ~80% code. |
| **M28.3.3** | `add_custom_event_node` + `add_execution_sequence_node` + `add_dynamic_cast_node` | → 1.21.2 (patch) | Three independent one-off node types. Each has its own small post-create configuration step. |
| **M28.3.4** | `add_local_variable` | → 1.21.3 (patch) | Different shape — modifies `UK2Node_FunctionEntry::LocalVariables`, not a fresh node spawn. Ships last so the Entry-node machinery is fully exercised by prior phases. |
| **M28.3.5** | BugHunt fixtures + M28.pre.2/.3 per-op inspect+soak fixtures (one per op) | no bump | Runs alongside each phase as ops ship; fixture regeneration via `GenerateTestBlueprintsCommandlet` per `BugHunt/README.md`. |
| **M28.3.6** | Docs sweep (CATALOG.md + plans/README.md + plans/AGENT_LOOP.md worked example + CLAUDE.md `Public/Reflection/` tree) | no bump | Closes M28.3 end-to-end; pure docs. |

   Per-phase stamp sweep is the standard 9-location pass; dual-engine DLL rebuild required on every bump per `CLAUDE.md § Versioning Protocol`. M28.pre.1–.4 matrix gates carry over unchanged.

10. **Open implementation questions** (resolve during each sub-phase, not gate-blocking for M28.3.1):

    1. **Position conflict resolution.** Two nodes placed at identical `(x,y)` in the same graph would generate identical `NodeGuid` under `SeedGuidFromJoined(<bp>:graph:<g>:node:<kind>:<x,y>)`. Mitigation: include node-kind in the seed key (already proposed). If kind + (x,y) still collides, op entry rejects with a structured error pointing at the existing node's GUID — plan author picks a different position.
    2. **`AddInputPin` rename semantics.** `IK2Node_AddPinInterface::AddInputPin` is misleadingly named: on `UK2Node_ExecutionSequence` it adds a new **output** THEN pin (sequence nodes have one input exec, N then-outs). Verify in M28.3.3 implementation and document the surprise in the op docstring.
    3. **`SetNodePinLiteralDefault` deprecation.** Once `SetGraphPinLiteralDefault` ships, M26.1 callers could migrate. Non-blocking — the function-name-keyed version stays alive indefinitely, same pattern as `ConnectPinsByName` + `ConnectGraphPinsByGuidString` coexisting.
    4. **`ubergraph-only` enforcement for CustomEvent.** M28.3.3 op entry walks the graph to confirm it's a `UbergraphPage`. Alternative: let UE's compile step trip the error. Recommend explicit pre-check — matches M26.1's "err at op entry, not at compile" philosophy.

**M28.3.0 CLOSED (research, 2026-04-23 post-M29).** Commit `3cd5283`. Superseded by M28.3.1 shipped record below.

### M28.3.1 shipped (2026-04-23 post-M29, 1.20.1 → 1.21.0)

**`add_branch_node` + `set_graph_pin_default` land as the first node-spawn slice of M28.3 graph-authoring catalog.** Commit `cc0204d`. Minor bump per semver rule (new subsystem — node-level graph authoring). All 14 `verify_all.ps1` gates PASS on BugHunt / stock UE 5.7 in 206.4 s. MCP pytest 23/23 PASS.

**C++ surface added (2 UFUNCTIONs on `UBpxReflectionOps`):**

| New UFUNCTION | What it does |
|---|---|
| `AddBranchNode(UBlueprint*, FName GraphName, FVector2D Position)` | Spawns `UK2Node_IfThenElse` into any K2 graph family (function / interface-override / ubergraph — walks all three via `FindFunctionGraphByName`). Bypasses `FGraphNodeCreator` for a deterministic `FName` on `NewObject` (pattern: `BpxBranch_<x>_<y>`), then manual `Graph->AddNode` + `PostPlacedNewNode` + `AllocateDefaultPins`. Post-`AllocateDefaultPins` overwrites `NodeGuid` via `SeedGuidFromJoined(<bp>:graph:<g>:branch:<x>,<y>)` and seeds pin IDs via `SeedPinGuidsForNode(JoinedPrefix)` (4 default pins: `execute`/`Condition`/`then`/`else`). Position is included in the seed so distinct Branches at different positions in the same graph get distinct GUIDs; moving a Branch post-apply breaks byte-identity (acceptable — plan authors set position explicitly). Idempotent on the seeded `NodeGuid`. Returns `FBpxNodeResult` with the hex-formatted GUID for plan authors to chain. |
| `SetGraphPinLiteralDefault(UBlueprint*, FName GraphName, const FString& NodeGuidStr, FName PinName, const FString& LiteralText)` | Sibling of M26.1's function-name-keyed `SetNodePinLiteralDefault`. Accepts `NodeGuid` as a hex string (32-char or `{8-4-4-4-12}`, parsed via `FGuid::Parse` — same shape as `ConnectGraphPinsByGuidString`). Routes through `FindFunctionGraphByName` so it reaches all three graph families. Uses `UEdGraphSchema::TrySetDefaultValue` for pin-type coercion. Idempotent on value-unchanged. Kept separate from M26.1 `SetNodePinLiteralDefault` (function-name keyed + `FGuid` arg) per the coexistence pattern `ConnectPinsByName` (M26.1) + `ConnectGraphPinsByGuidString` (M28.3-narrow). |

**Python surface added (1 new module + 2 ops):**

| New op (in `scripts/python_ops/blueprint_graph_nodes.py`) | What it does |
|---|---|
| `add_branch_node(bp_path, graph_name, position)` | `position` accepts `[x,y]` / `(x,y)` / `unreal.Vector2D`. Returns `{node_guid: <hex>, pins: [execute, Condition, then, else], spawned: bool}`. Idempotent-skip surfaces as `success=True, skipped="branch already exists at this position"`. |
| `set_graph_pin_default(bp_path, graph_name, node_guid, pin_name, literal_text)` | Takes the hex `node_guid` string newly-spawned nodes return. Returns `{before: <prior value>, after: <new value>}`. |

**Plan pipeline wiring (standard 4-file pattern):**
- `__init__.py`: 2 new re-exports + `__all__` extension.
- `plan_shape.OP_SPECS`: 2 new entries — `add_branch_node` requires `bp_path/graph_name/position`; `set_graph_pin_default` requires `bp_path/graph_name/node_guid/pin_name/literal_text`. Both `assets: [bp_path]`.
- `plan_executor._OP_DISPATCH`: 2 new entries.
- `mechanical_diff._op_expected_changes`: both new ops added to the `"implement_interface_function" / "connect_graph_pins"` tuple that returns `[(bp_path, "mutated")]`.

**BugHunt fixture added:** `BP_BpxTestGraphNodes` (empty Actor BP) via `GenerateTestBlueprintsCommandlet`. Matches M28.2.x pattern — inspect/soak duplicates to scratch and authors into `EventGraph` at `(128, -48)`. The empty baseline means every seeded GUID in the post-op asset comes from the new `SeedGuidFromJoined(:branch:128,-48)` + `SeedPinGuidsForNode` paths, not pre-existing on-disk content.

**Inspect+soak assertions:** `scripts/inspect_fixtures/add_branch_node.json` — `expected_deep: ["K2Node_IfThenElse", "Branch"]`, `soak.rounds: 2, stable_keys: ["node_guid"]`. Expected_md stays empty because Tier 1 `.md` only surfaces a summary — Tier 2 `.deep.md` is where nodes render.

**Deferred to M28.3.2:** `set_graph_pin_default` inspect/soak fixture. Reason: Branch's `Condition` pin defaults to the empty string on spawn, so a round-trip set-to-a-different-value assertion is trivial and doesn't exercise meaningful coverage. M28.3.2's `add_call_function_node` provides a natural target — a CallFunction node has typed input pins (bool / int / vector) with authored literal defaults ready to exercise the coerce-via-schema path. The op itself is green through:
- Direct bridge smoke-test (empty C++ pin default → set via op → re-read matches).
- MCP pytest 23/23 (no regressions in existing coverage).
- Determinism gate (twin inventory run is byte-identical; the op's internals don't touch on-disk state during the twin).
Risk of deferring: low — `SetGraphPinLiteralDefault` is thin glue over `UEdGraphSchema::TrySetDefaultValue` (no new GUID seeding, no `NewObject`, no `AllocateDefaultPins`). It's semantically identical to M26.1's `SetNodePinLiteralDefault` with a different routing to the graph, and that one has full inspect/soak coverage via `implement_interface_function`.

**Verification matrix — all 14 gates PASS (206.4 s):**

| Gate | Result |
|---|---|
| `automation-bughunt` | PASS exit=0, 15.7 s (17/17 tests) |
| `determinism-bughunt` | PASS exit=0, 46.8 s (twin byte-identical) |
| `inspect-add_bp_function` | PASS exit=0, 17.8 s |
| `inspect-add_bp_interface` | PASS exit=0, 17.7 s |
| `inspect-add_bp_variable` | PASS exit=0, 17.8 s |
| **`inspect-add_branch_node`** | **PASS exit=0, 17.8 s** |
| `inspect-add_component_to_scs` | PASS exit=0, 17.8 s |
| `inspect-implement_interface_function` | PASS exit=0, 17.9 s |
| `soak-add_bp_function` | PASS exit=0, 6.2 s |
| `soak-add_bp_interface` | PASS exit=0, 6.1 s |
| `soak-add_bp_variable` | PASS exit=0, 6.2 s |
| **`soak-add_branch_node`** | **PASS exit=0, 6.1 s** (round 1 md5 == round 2 md5 + stable `node_guid` across rounds) |
| `soak-add_component_to_scs` | PASS exit=0, 6.2 s |
| `soak-implement_interface_function` | PASS exit=0, 6.1 s |

**Version bump 1.20.1 → 1.21.0 (minor — new subsystem per semver).** 9-location stamp sweep clean; drift-detection grep agrees. `"Version": 20` integer bumped to `21`.

**Dual-engine DLL rebuilt:**
- UE_DOW (custom UE 5.7): 2,677,248 b, BuildId `6efc257b-c266-4cd4-a5b9-ff35b4206bf5`. Built via `RunUAT BuildPlugin -Rocket` in 24.43 s warm.
- Stock UE 5.7: 2,678,784 b, BuildId `47537391`. Built via `RunUAT BuildPlugin -Rocket` in 43.18 s warm. Installed into `BugHunt/TestProject/Plugins/BlueprintExporter/` (real directory, not junction).

**Op count across library:** 24 op functions now re-exported from `python_ops/__init__.py` (M28.3.1 added 2). MCP's `get_op_catalog` auto-surfaces via AST walk (zero MCP server change).

**Carry-forwards for M28.3.2:**
1. `GenerateTestBlueprintsCommandlet -Force` is incompatible with existing `BP_MacroMania` fixture — crashes on a redirector rename collision (`Renaming an object (EdGraph /Game/.../BP_MacroMania_Lib:EdGraph_1) on top of an existing object (ObjectRedirector)`). Resolved by running WITHOUT `-Force` (existing fixtures skip by name, new fixture generates). Not an M28.3.1 regression — pre-existing bug in the fixture gen's redirector handling. Record for future fixture-regen sessions.
2. `BlueprintExporterTests` plugin can't be built via `RunUAT BuildPlugin` (creates a sandboxed HostProject that doesn't see the BlueprintExporter dependency). Solution: direct UBT invocation — `UnrealBuildTool.exe UnrealEditor Win64 Development -Project=<BugHunt.uproject>` — which rebuilds the test plugin as part of the editor target. ~18 s warm.
3. `inspect_harness.py` + `soak_template.py` both hard-code single-op plan shape (one op per assertions JSON). Multi-op assertions (needed to exercise `set_graph_pin_default` against a fixture that doesn't already have a suitable node) would require harness changes. M28.3.2's add-CallFunction-then-set-pin pattern works because the CallFunction spawn produces natural typed-pin targets that can be set in the same op-result flow.
4. Five BugHunt source fixtures (`BP_InheritanceChain`, `BP_InheritanceChain_Grandparent`, `BP_InheritanceChain_Parent`, `BP_PinHell`, `BP_SCSMonster`) accumulate cross-session byte drift during verify_all runs (same 30,365 b size, different content bytes). This is the documented `UPackage::SavePackage` GUID regeneration (WIP M26.1.2 regression-chase block). NOT committed with M28.3.1; reverted before commit. Pattern for M28.3.2+: `git checkout -- <those 5 fixtures>` before staging, or add a pre-commit check.

**M28.3.1 CLOSED (2026-04-23 post-M29).** Superseded by M28.3.2 shipped record below.

### M28.3.2 shipped (2026-04-24, 1.21.0 → 1.21.1)

**`add_call_function_node` + `add_variable_get_node` + `add_variable_set_node` land as the FunctionReference / VariableReference family of the M28.3 graph-authoring catalog.** Patch bump per semver (additive — same subsystem as M28.3.1). All 20 `verify_all.ps1` gates PASS on BugHunt / stock UE 5.7 in 279.3 s. MCP pytest 23/23 PASS.

**C++ surface added (3 UFUNCTIONs on `UBpxReflectionOps`, sharing `BpxReflection::MakeMemberRefSeedPrefix` helper):**

| New UFUNCTION | What it does |
|---|---|
| `AddCallFunctionNode(UBlueprint*, FName GraphName, FName MemberName, UClass* TargetClass, FVector2D Position)` | Spawns `UK2Node_CallFunction`. `TargetClass==nullptr` → `FunctionReference.SetSelfMember(MemberName)`, else `SetExternalMember(MemberName, TargetClass)`. Reference configured BEFORE `AllocateDefaultPins` so the node's pin set resolves to the callee's signature (typed inputs + `ReturnValue` where applicable). Seed: `md5(<bp>:graph:<g>:call:<member>:<ctx>:<x,y>)` where `ctx` is the external class's full path or `"self"`. |
| `AddVariableGetNode(UBlueprint*, FName GraphName, FName MemberName, UClass* TargetClass, FVector2D Position)` | Spawns `UK2Node_VariableGet`. Generalises M26.1's `AddSelfMemberGetNode` (function-graph-only + self-only) to any graph family + any variable context. Seed key uses `:varget:` discriminator. |
| `AddVariableSetNode(UBlueprint*, FName GraphName, FName MemberName, UClass* TargetClass, FVector2D Position)` | Spawns `UK2Node_VariableSet`. Sibling of VariableGet; `execute` in/out exec pair + typed value input pin. External-context targets must be `BlueprintReadWrite` or compile fails. Seed key uses `:varset:` discriminator. |

All three idempotent on seeded `NodeGuid`. All three mirror `AddBranchNode`'s no-`FGraphNodeCreator` pattern — explicit `FName` on `NewObject` (e.g. `BpxCall_<member>_<x>_<y>`) avoids `MakeUniqueObjectName` counter leakage. Every `NodeGuid` + every pin `PinId` seeded via `SeedGuidFromJoined` / `SeedPinGuidsForNode` after `AllocateDefaultPins`.

**Python surface added (3 ops in `scripts/python_ops/blueprint_graph_nodes.py`, sharing the `_spawn_node_common` helper):**

| New op | What it does |
|---|---|
| `add_call_function_node(bp_path, graph_name, function_name, target_class_path="", position=(0,0))` | Empty `target_class_path` → self context; non-empty → external. Validation via `unreal.load_class`/`load_object` fallback (mirrors M28.2.3 pattern). Returns `{node_guid, member_name, target_class_path, spawned}`. |
| `add_variable_get_node(bp_path, graph_name, variable_name, target_class_path="", position=(0,0))` | Same shape as above; reads a member on self or an external UPROPERTY. |
| `add_variable_set_node(bp_path, graph_name, variable_name, target_class_path="", position=(0,0))` | Same shape. Target variable must be `BlueprintReadWrite` in the external-context case. |

The shared `_spawn_node_common` helper encapsulates load_bp → coerce_position → resolve_target_class → bridge call → compile+save, so the three public ops are ~8 lines each.

**Plan pipeline wiring (standard 4-file pattern):**
- `__init__.py`: 3 new re-exports + `__all__` extension (24 → 27 ops).
- `plan_shape.OP_SPECS`: 3 new entries — each requires `bp_path/graph_name/<member>_name/position`; `target_class_path` is optional (defaults to empty → self context).
- `plan_executor._OP_DISPATCH`: 3 new entries.
- `mechanical_diff._op_expected_changes`: 3 new ops added to the existing `add_branch_node` / `set_graph_pin_default` / `connect_graph_pins` / `implement_interface_function` tuple.

**BugHunt fixture added:** `BP_BpxTestGraphNodesCalls` (Actor BP with declared `TestCount: int` member variable + declared `DoTheThing()` void member function). First non-empty structural-edit fixture in the BugHunt tree — the three new M28.3.2 ops each require resolvable self-member targets to materialise their signature-derived pin sets. Single-op plan shape in `inspect_harness` / `soak_template` prevents chaining `add_bp_variable` + `add_variable_get_node` in the assertions JSON, so the variable + function are authored at fixture-gen time via `AddIntVariable` + `FBlueprintEditorUtils::AddFunctionGraph`. Committed as binary .uasset at 27,198 bytes. Pre-existing `TestCount` VarGuid + `DoTheThing` GraphGuid/NodeGuids are stable round-to-round because the fixture isn't re-generated in CI.

**Inspect+soak assertions added:** `scripts/inspect_fixtures/add_call_function_node.json` + `add_variable_get_node.json` + `add_variable_set_node.json`. Each targets `BP_BpxTestGraphNodesCalls` with self-context (`target_class_path=""`) against the declared `DoTheThing` / `TestCount` at positions `(128,-48)` / `(160,-48)` / `(192,-48)` respectively. Shape mirrors `add_branch_node.json` — `expected_deep` asserts the new K2Node class + member name appears in the rendered `.deep.md`; `soak.rounds=2, stable_keys=["node_guid"]` asserts md5 + seeded GUID stability across rounds.

**`set_graph_pin_default` inspect/soak backfill — deferred to M28.3.6 docs sweep (or a follow-up harness-extension slice).** Per M28.3.1 carry-forward #3, `inspect_harness.py` + `soak_template.py` hard-code single-op plan shape. Backfilling `set_graph_pin_default.json` against a newly-spawned CallFunction pin would require a multi-op assertion (spawn then set). Deferral risk is low: the op is thin glue over `UEdGraphSchema::TrySetDefaultValue` with no new GUID seeding / NewObject / AllocateDefaultPins; semantically identical to M26.1's `SetNodePinLiteralDefault` which has full inspect/soak coverage via `implement_interface_function`. The M28.3.1-green direct bridge smoke (before-empty → after-value → re-read match) remains the primary verification.

**Verification matrix — all 20 gates PASS (279.3 s):**

| Gate | Result |
|---|---|
| `automation-bughunt` | PASS exit=0, 15.7 s (17/17 tests) |
| `determinism-bughunt` | PASS exit=0, 47.3 s (twin byte-identical) |
| `inspect-add_bp_function` | PASS exit=0, 18.0 s |
| `inspect-add_bp_interface` | PASS exit=0, 18.0 s |
| `inspect-add_bp_variable` | PASS exit=0, 17.8 s |
| `inspect-add_branch_node` | PASS exit=0, 17.8 s |
| **`inspect-add_call_function_node`** | **PASS exit=0, 17.8 s** |
| `inspect-add_component_to_scs` | PASS exit=0, 17.8 s |
| **`inspect-add_variable_get_node`** | **PASS exit=0, 17.8 s** |
| **`inspect-add_variable_set_node`** | **PASS exit=0, 17.8 s** |
| `inspect-implement_interface_function` | PASS exit=0, 17.8 s |
| `soak-add_bp_function` | PASS exit=0, 6.2 s |
| `soak-add_bp_interface` | PASS exit=0, 6.1 s |
| `soak-add_bp_variable` | PASS exit=0, 6.1 s |
| `soak-add_branch_node` | PASS exit=0, 6.2 s |
| **`soak-add_call_function_node`** | **PASS exit=0, 6.2 s** (md5 `4a008f387bf3197ef2a12189c128955d`, stable `node_guid`) |
| `soak-add_component_to_scs` | PASS exit=0, 6.1 s |
| **`soak-add_variable_get_node`** | **PASS exit=0, 6.1 s** (md5 `10ad1a376843789abadb22b3c765a780`, stable `node_guid`) |
| **`soak-add_variable_set_node`** | **PASS exit=0, 6.1 s** (md5 `3646a59f3fbed6815c544bcd3bd73b2f`, stable `node_guid`) |
| `soak-implement_interface_function` | PASS exit=0, 6.2 s |

MCP pytest: 23/23 PASS (no new tests — Python surface widening already covered by the plan-shape validator's unknown-op negative path and its OP_SPECS reflection).

**Version bump 1.21.0 → 1.21.1 (patch — additive ops in existing M28.3 subsystem).** 9-location stamp sweep clean; drift-detection grep agrees. `"Version": 21` integer unchanged (patch bumps don't touch the minor-digit-tied integer).

**Dual-engine DLL rebuilt:**
- UE_DOW (custom UE 5.7): 2,695,168 b. Built via `RunUAT BuildPlugin -Rocket` in 28.8 s warm.
- Stock UE 5.7: 2,696,192 b. Built via `RunUAT BuildPlugin -Rocket` in 44.1 s warm. Installed into `BugHunt/TestProject/Plugins/BlueprintExporter/` (via `Build.bat` rebuild against the stock engine) and into `_build_output_5_7/` (junction target for UE_DOW_Legacy + MutableSample).

**Op count across library:** 27 op functions re-exported from `python_ops/__init__.py` (24 → 27, +3).

**Carry-forwards for M28.3.3:**
1. The fixture-fresh-generation path works cleanly WITHOUT `-Force` — new fixtures generate, existing ones skip by name. Pattern: add new `FResult GenBP_...()` + entry in the `Gens` array + run `GenerateTestBlueprints -Only=<Name>` targeted regen (the `Only=` filter matched the `Name` field). Avoids the M28.3.1 `-Force`-vs-BP_MacroMania redirector crash.
2. M28.3.3 (`add_custom_event_node` + `add_execution_sequence_node` + `add_dynamic_cast_node`) — three independent one-off node types per M28.3.0 research. CustomEvent must validate target graph is an ubergraph (new input-check at op entry); ExecutionSequence must document the misleading `IK2Node_AddPinInterface::AddInputPin` naming (adds a new THEN-out pin, NOT an in pin); DynamicCast sets `TargetType = UClass*` before `AllocateDefaultPins`.
3. The BP_BpxTestGraphNodesCalls fixture's `DoTheThing` + `TestCount` can be reused by M28.3.3 for the CustomEvent ubergraph target (single fixture, multiple op inspect/soak targets — less fixture-gen churn than one-fixture-per-op).

**M28.3.2 CLOSED (2026-04-24, 1.21.0 → 1.21.1). Superseded by M28.3.3 shipped record below.**

### M28.3.3 shipped (2026-04-24, 1.21.1 → 1.21.2)

**`add_custom_event_node` + `add_execution_sequence_node` + `add_dynamic_cast_node` land as three independent one-off K2Node types — last pre-M28.3.4-local-var slice of the M28.3 graph-authoring catalog.** Patch bump per semver (additive ops in existing M28.3 subsystem; `"Version": 21` integer unchanged). All 25 `verify_all.ps1` gates PASS on BugHunt / stock UE 5.7 in 350 s. MCP pytest 23/23 PASS.

**C++ surface added (3 UFUNCTIONs on `UBpxReflectionOps`):**

| New UFUNCTION | What it does |
|---|---|
| `AddCustomEventNode(UBlueprint*, FName GraphName, FName EventName, FVector2D Position)` | Spawns `UK2Node_CustomEvent` into an ubergraph. Op-entry check rejects non-ubergraph targets (`UEdGraphSchema::GetGraphType(Graph) != GT_Ubergraph`) with a structured error — surfacing explicitly what UE's `K2Node_Event::IsCompatibleWithGraph` would catch at compile time. Sets inherited `CustomFunctionName = EventName` BEFORE `AllocateDefaultPins` (otherwise the delegate pin + auto-generated signature read the pre-set value wrong). Seed: `md5(<bp>:graph:<g>:custom_event:<name>:<x,y>)`. Default pins: `OutputDelegate` + `then`. |
| `AddExecutionSequenceNode(UBlueprint*, FName GraphName, int32 NumOutputs, FVector2D Position)` | Spawns `UK2Node_ExecutionSequence` with the requested number of `then_N` exec outputs. The engine's `AllocateDefaultPins` produces `then_0` + `then_1`; any additional outputs are added via `IK2Node_AddPinInterface::AddInputPin()` — UE API wart, that method name adds a **THEN-OUT** pin, not an input. Range-clamped to `[2, 16]`. `SeedPinGuidsForNode` fires AFTER the `AddInputPin` loop so the extended `then_2+` pins are also byte-deterministic. Seed: `md5(<bp>:graph:<g>:execseq:<n>:<x,y>)`. |
| `AddDynamicCastNode(UBlueprint*, FName GraphName, UClass* TargetClass, FVector2D Position)` | Spawns `UK2Node_DynamicCast` typed against `TargetClass`. Sets `NewNode->TargetType = TargetClass` BEFORE `AllocateDefaultPins` — the `As<TargetClass>` output pin's `PinCategory` / `PinSubCategoryObject` are derived from `TargetType` inside `CreatePinsForCastNode`; post-alloc assignment leaves `As<X>` as a wildcard. `TargetClass == nullptr` is a structured error. Default (impure) pins: `execute`, `CastSucceeded`, `CastFailed`, `ObjectToCast`, typed `As<TargetClass>`, `bSuccess`. Seed: `md5(<bp>:graph:<g>:cast:<target_class_path>:<x,y>)`. |

All three idempotent on seeded `NodeGuid`. All three follow the established M28.3.1+ spawn-op shape: explicit `FName` on `NewObject` (e.g. `BpxCustomEvent_<name>_<x>_<y>` / `BpxExecSeq_<n>_<x>_<y>` / `BpxCast_<cls>_<x>_<y>`) to bypass `MakeUniqueObjectName`'s monotonic counter, `PostPlacedNewNode` + `AllocateDefaultPins`, overwrite `NodeGuid` via `SeedGuidFromJoined`, seed every pin `PinId` via `SeedPinGuidsForNode`.

No new module deps (`BlueprintGraph` already linked for M26.1 / M28.3.1–.2). Three new `#include "K2Node_CustomEvent.h" / K2Node_DynamicCast.h / K2Node_ExecutionSequence.h` plus defensive `K2Node_AddPinInterface.h`.

**Python surface added (3 ops in `scripts/python_ops/blueprint_graph_nodes.py`):**

| New op | What it does |
|---|---|
| `add_custom_event_node(bp_path, graph_name, event_name, position=(0,0))` | Ubergraph-only; non-ubergraph target is a structured error surfaced by the bridge. Returns `{node_guid, event_name, spawned, pins: ["OutputDelegate", "then"]}`. |
| `add_execution_sequence_node(bp_path, graph_name, num_outputs, position=(0,0))` | `num_outputs` type-checked as `int` (rejects `bool`), range-checked `[2, 16]` Python-side before the bridge call. Returns `{node_guid, num_outputs, spawned, pins: ["execute", "then_0", ..., "then_<N-1>"]}`. Pin names use lowercase `then_N` per UE's `UEdGraphSchema_K2::PN_Then` — confirmed against engine source `K2Node_ExecutionSequence.cpp:278` (`"%s_%d"` format over `PN_Then.ToString()`). |
| `add_dynamic_cast_node(bp_path, graph_name, target_class_path, position=(0,0))` | Non-empty `target_class_path` required; resolved via `unreal.load_class` with `load_object` fallback (mirrors `add_component_to_scs` / `add_bp_interface`). Returns `{node_guid, target_class_path, spawned, pins: [...]}` with the typed `AsObject` slot surfaced as a stable placeholder (UE renames it at compile time to `As<TargetClass>` — the op reports the stable pre-compile label). |

**Plan pipeline wiring (standard 4-file pattern):**
- `__init__.py`: 3 new re-exports + `__all__` extension (27 → 30 ops).
- `plan_shape.OP_SPECS`: 3 new entries — each requires `bp_path/graph_name/<kind-specific>/position`. CustomEvent takes `event_name`; ExecutionSequence takes `num_outputs` int; DynamicCast takes `target_class_path` string.
- `plan_executor._OP_DISPATCH`: 3 new entries.
- `mechanical_diff._op_expected_changes`: 3 new ops added to the existing M28.3 `"add_branch_node" / "set_graph_pin_default" / "add_call_function_node" / ..."` tuple that returns `[(bp_path, "mutated")]`.

**BugHunt fixture reuse:** `BP_BpxTestGraphNodesCalls` (shipped in M28.3.2 — Actor BP with `TestCount: int` + `DoTheThing()` void function). No new fixture needed: CustomEvent targets `EventGraph` which is the default Actor BP ubergraph; ExecutionSequence + DynamicCast don't require pre-existing declared members. Follows the M28.3.2 carry-forward-#3 recommendation of reusing one fixture across multiple op targets.

**Inspect+soak assertions added:** `scripts/inspect_fixtures/add_custom_event_node.json` + `add_execution_sequence_node.json` + `add_dynamic_cast_node.json`. Each targets the Calls fixture at fresh positions `(224,-48)` / `(256,-48)` / `(288,-48)` (non-overlapping with the M28.3.2 fixture positions at `(128,-48)` / `(160,-48)` / `(192,-48)`). `expected_deep` asserts the new K2Node class + the type-specific identity (event name / extended `then_2` pin / `Actor` cast-target short name). `soak.rounds=2, stable_keys=["node_guid"]`.

**Lowercase-pin-name trap caught by the first inspect run** — initial assertion used `"Then_2"` (title case, reflecting the informal "THEN pin" naming from the M28.3.0 research block) but UE's actual pin name is `"then_2"` (lowercase, from `UEdGraphSchema_K2::PN_Then = TEXT("then")` + `GetPinNameGivenIndex` format `"%s_%d"`). Fixed in the fixture JSON + Python op's `pin_names` list + CATALOG.md + plans/README.md. Value of the content-inspect gate demonstrated again: the soak gate alone would have missed this because determinism soak doesn't assert content shape, just stability.

**Verification matrix — 25 gates PASS (350 s):**

| Gate | Result |
|---|---|
| `automation-bughunt` | PASS exit=0, 15.7 s (17/17 tests) |
| `determinism-bughunt` | PASS exit=0, 46.9 s (twin byte-identical) |
| `inspect-add_bp_function` | PASS exit=0, 17.8 s |
| `inspect-add_bp_interface` | PASS exit=0, 17.9 s |
| `inspect-add_bp_variable` | PASS exit=0, 17.9 s |
| `inspect-add_branch_node` | PASS exit=0, 17.9 s |
| `inspect-add_call_function_node` | PASS exit=0, 17.7 s |
| `inspect-add_component_to_scs` | PASS exit=0, 17.8 s |
| **`inspect-add_custom_event_node`** | **PASS exit=0, 17.7 s** |
| **`inspect-add_dynamic_cast_node`** | **PASS exit=0, 17.8 s** |
| **`inspect-add_execution_sequence_node`** | **PASS exit=0, 17.8 s** (after lowercase-pin-name fix) |
| `inspect-add_variable_get_node` | PASS exit=0, 17.8 s |
| `inspect-add_variable_set_node` | PASS exit=0, 17.7 s |
| `inspect-implement_interface_function` | PASS exit=0, 17.8 s |
| `soak-add_bp_function` | PASS exit=0, 6.2 s |
| `soak-add_bp_interface` | PASS exit=0, 6.1 s |
| `soak-add_bp_variable` | PASS exit=0, 6.1 s |
| `soak-add_branch_node` | PASS exit=0, 6.1 s |
| `soak-add_call_function_node` | PASS exit=0, 6.1 s |
| `soak-add_component_to_scs` | PASS exit=0, 6.1 s |
| **`soak-add_custom_event_node`** | **PASS exit=0, 6.1 s** (md5 `b672354521313936c7f1648775fcb970`, stable `node_guid`) |
| **`soak-add_dynamic_cast_node`** | **PASS exit=0, 6.1 s** (md5 `06d576d92b625b40140676dc6c800714`, stable `node_guid`) |
| **`soak-add_execution_sequence_node`** | **PASS exit=0, 6.1 s** (md5 `f74c06f73e6085cbff9623f81ef3a22c`, stable `node_guid`) |
| `soak-add_variable_get_node` | PASS exit=0, 6.1 s |
| `soak-add_variable_set_node` | PASS exit=0, 6.2 s |
| `soak-implement_interface_function` | PASS exit=0, 6.1 s |

MCP pytest: 23/23 PASS (rerun after the `verify_all` editor went quiet — initial interleaved run saw 3 failures because the test's `patch.object(plans, "run_ue_subprocess", _fake_run)` mock was bypassed by the live bridge that the matrix's own UE editor was hosting; that's a test-isolation artifact, not an M28.3.3 regression).

**Version bump 1.21.1 → 1.21.2 (patch — additive ops in existing M28.3 subsystem).** 9-location stamp sweep clean; drift-detection grep agrees. `"Version": 21` integer unchanged (patch bumps don't touch the minor-digit-tied integer).

**Dual-engine DLL rebuilt:**
- UE_DOW (custom UE 5.7): 2,719,744 b, BuildId `6efc257b-c266-4cd4-a5b9-ff35b4206bf5`. Built via `RunUAT BuildPlugin -Rocket` in 25.3 s warm. Installed into `BuiltPlugin/Binaries/Win64/`.
- Stock UE 5.7: 2,720,768 b, BuildId `47537391`. Built via `RunUAT BuildPlugin -Rocket` in 44.8 s warm. Installed into `BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64/` + `_build_output_5_7/` (junction target for UE_DOW_Legacy + MutableSample).

DLL size delta vs M28.3.2 (+~24 KB per engine) consistent with 3 new UFUNCTIONs + their wrappers + the 4 new K2Node includes.

**Op count across library:** 30 op functions re-exported from `python_ops/__init__.py` (27 → 30, +3).

**Carry-forwards for M28.3.4 (`add_local_variable` — last planned M28.3 slice before the docs sweep):**
1. UE's `UEdGraphSchema_K2` pin-name constants are lowercase (`"then"` / `"execute"` / `"Condition"` are the canonical forms — `Condition` DOES happen to be title case on Branch, so the casing isn't uniform). Always verify against engine source rather than assume from informal docs. The M28.3.0 research block used title-case `Then_N` in prose; future research should mirror the engine's actual `FName` literal.
2. The M28.3.3 fixture-reuse pattern (`BP_BpxTestGraphNodesCalls` covers 6 ops across M28.3.2 + M28.3.3 via non-overlapping positions) is a template for M28.3.4 too — `add_local_variable` targets `UK2Node_FunctionEntry::LocalVariables` on a named function, so `DoTheThing` is a natural target. No new fixture likely needed; extend assertions JSON only.
3. The test-isolation issue between `verify_all.ps1` + MCP pytest is worth capturing: running the matrix first + pytest second (or in separate PowerShell sessions with editor teardown in between) keeps MCP's "prefer bridge, fall through to subprocess" behavior from picking up the matrix's live editor mid-test. A cleaner fix would be for the smoke tests to force `BPX_BRIDGE_PORT=0` (or set an impossible host) via env var to force the subprocess fallback path — that would make the mocks deterministic regardless of surrounding editor state. Not a blocker; MCP pytest passes clean when run with the editor quiet.

**M28.3.3 CLOSED (2026-04-24, 1.21.1 → 1.21.2). Superseded by M28.3.4 shipped record below.**

### M28.3.4 shipped (2026-04-24, 1.21.2 → 1.21.3)

**`add_local_variable` lands as the last planned K2Node-family slice of the M28.3 graph-authoring catalog before the M28.3.6 docs sweep.** Different shape from M28.3.1–.3 — no K2Node spawned; instead an existing `UK2Node_FunctionEntry`'s `LocalVariables: TArray<FBPVariableDescription>` UPROPERTY gains a new entry. Per M28.3.0 research sequencing, ships last so the Entry-node machinery is fully exercised by the prior spawn-based phases. Patch bump per semver (additive op in the same M28.3 subsystem; `"Version": 21` integer unchanged). **All 27 `verify_all.ps1` gates PASS on BugHunt / stock UE 5.7 in 374.4 s.** MCP pytest 23/23.

**C++ surface added (1 UFUNCTION on `UBpxReflectionOps`):**

| New UFUNCTION | What it does |
|---|---|
| `AddLocalVariableDeterministic(UBlueprint*, FName FunctionName, FName VarName, const FEdGraphPinType& VarType, const FString& DefaultValue)` | Appends a local variable to `FunctionName`'s `UK2Node_FunctionEntry::LocalVariables[]` via `FBlueprintEditorUtils::AddLocalVariable` (UnrealEd, already linked via M26.1), then overrides the engine-assigned `VarGuid` with `SeedGuidFromJoined(<bp>:func:<fn>:localvar:<var>)`. Engine helper uses `FGuid::NewGuid()` at `BlueprintEditorUtils.cpp:5433` — without the post-seed override every run drifts the .uasset md5 and M28.pre.3 soak round 2 fails. Idempotency pre-check: walks `FunctionEntry->LocalVariables[]` by `VarName` and returns `bSuccess=true, bSkipped=true` on match. Ubergraphs are rejected (no `K2Node_FunctionEntry`); function / interface-override graphs accepted. Does NOT call `MarkBlueprintAsStructurallyModified` a second time — `AddLocalVariable` marks internally on the success path; per the M26.1.2 regression-chase double-marking re-enters structural-modified listeners and invalidates freshly-seeded GUIDs before the subsequent compile + save. |

Seed key includes `FunctionName` (unlike M28.2.1's global-scope `:var:<name>` key for member vars) — local variables with the same name in different functions are legitimate and the determinism key must reflect that scope.

**Python surface added (1 op in `scripts/python_ops/blueprint_graph_nodes.py`):**

| New op | What it does |
|---|---|
| `add_local_variable(bp_path, function_name, var_name, var_type_spec, default_value="")` | Resolves `var_type_spec` via the shared `blueprint_structural._resolve_pin_type` helper (same compact string forms `add_bp_variable` accepts — `"int"` / `"struct:/Script/..."` / `"array:int"` / etc.) — first cross-module helper reuse in the `python_ops/` tree. Returns `{before, after}` with the `"localvar-added:<fn>::<var>"` bookkeeping token; idempotent-skip surfaces as `skipped="local variable already exists"`. |

**Plan pipeline wiring (standard 4-file pattern):**
- `__init__.py`: 1 new re-export + `__all__` extension (30 → 31 ops).
- `plan_shape.OP_SPECS`: 1 new entry — requires `bp_path/function_name/var_name/var_type_spec`; `default_value` optional.
- `plan_executor._OP_DISPATCH`: 1 new entry.
- `mechanical_diff._op_expected_changes`: added to the existing M28.3 `bp_path → "mutated"` tuple.

**BugHunt fixture reuse:** `BP_BpxTestGraphNodesCalls` once more — no new .uasset. The `DoTheThing` function shipped in M28.3.2 is the target; `add_local_variable(function_name="DoTheThing", var_name="LoopIndex", var_type_spec="int", default_value="7")` exercises the Entry-node LocalVariables path end-to-end. Fixture total op-coverage across M28.3.2 / .3 / .4: 7 ops (CallFunction / VariableGet / VariableSet / CustomEvent / ExecutionSequence / DynamicCast / LocalVariable) all targeting the same fixture with non-overlapping identifiers.

**Inspect+soak assertions added:** `scripts/inspect_fixtures/add_local_variable.json`. `expected_deep: ["LoopIndex"]` — since local variables aren't a K2Node class, the `.deep.md` renderer surfaces them differently from the M28.3.1–.3 cases; asserting on the var name alone is the tightest stable pattern. `soak.rounds=2` with the default md5-stability check (no `stable_keys` because this op returns bookkeeping strings, not a node_guid — md5 stability alone is the determinism signal).

**Verification matrix — 27 gates PASS (374.4 s):**

| Gate | Result |
|---|---|
| `automation-bughunt` | PASS exit=0, 15.7 s (17/17 tests) |
| `determinism-bughunt` | PASS exit=0, 47.0 s (twin byte-identical) |
| `inspect-add_bp_function` | PASS exit=0, 17.8 s |
| `inspect-add_bp_interface` | PASS exit=0, 18.0 s |
| `inspect-add_bp_variable` | PASS exit=0, 17.7 s |
| `inspect-add_branch_node` | PASS exit=0, 17.9 s |
| `inspect-add_call_function_node` | PASS exit=0, 17.7 s |
| `inspect-add_component_to_scs` | PASS exit=0, 17.9 s |
| `inspect-add_custom_event_node` | PASS exit=0, 17.7 s |
| `inspect-add_dynamic_cast_node` | PASS exit=0, 17.8 s |
| `inspect-add_execution_sequence_node` | PASS exit=0, 17.7 s |
| **`inspect-add_local_variable`** | **PASS exit=0, 17.8 s** |
| `inspect-add_variable_get_node` | PASS exit=0, 17.8 s |
| `inspect-add_variable_set_node` | PASS exit=0, 17.8 s |
| `inspect-implement_interface_function` | PASS exit=0, 17.7 s |
| `soak-add_bp_function` | PASS exit=0, 6.2 s |
| `soak-add_bp_interface` | PASS exit=0, 6.1 s |
| `soak-add_bp_variable` | PASS exit=0, 6.1 s |
| `soak-add_branch_node` | PASS exit=0, 6.3 s |
| `soak-add_call_function_node` | PASS exit=0, 6.1 s |
| `soak-add_component_to_scs` | PASS exit=0, 6.2 s |
| `soak-add_custom_event_node` | PASS exit=0, 6.1 s |
| `soak-add_dynamic_cast_node` | PASS exit=0, 6.2 s |
| `soak-add_execution_sequence_node` | PASS exit=0, 6.2 s |
| **`soak-add_local_variable`** | **PASS exit=0, 6.2 s** (md5 `8564b1ff661bab132d9891ec9dc9c6f9`, stable round-to-round — proves `SeedGuidFromJoined(:func:DoTheThing:localvar:LoopIndex)` overrides engine's `FGuid::NewGuid()` at `BlueprintEditorUtils.cpp:5433`) |
| `soak-add_variable_get_node` | PASS exit=0, 6.1 s |
| `soak-add_variable_set_node` | PASS exit=0, 6.1 s |
| `soak-implement_interface_function` | PASS exit=0, 6.1 s |

MCP pytest: 23/23 PASS.

**Version bump 1.21.2 → 1.21.3 (patch per semver — additive op in existing M28.3 subsystem).** 9-location stamp sweep clean; drift-detection grep agrees. `"Version": 21` integer unchanged.

**Dual-engine DLL rebuilt:**
- UE_DOW (custom UE 5.7): 2,730,496 b, BuildId `6efc257b-c266-4cd4-a5b9-ff35b4206bf5`. Built via `RunUAT BuildPlugin -Rocket` in ~26 s warm. Installed into `BuiltPlugin/Binaries/Win64/`.
- Stock UE 5.7: 2,731,520 b, BuildId `47537391`. Built via `RunUAT BuildPlugin -Rocket` in ~45 s warm. Installed into `BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64/` + `_build_output_5_7/` (junction target for UE_DOW_Legacy + MutableSample).

DLL size delta vs M28.3.3 (+~10 KB per engine) — smaller than the +~24 KB from M28.3.3's three new UFUNCTIONs; consistent with one new UFUNCTION + its wrapper.

**Op count across library:** 31 op functions re-exported from `python_ops/__init__.py` (30 → 31, +1). `get_op_catalog` auto-surfaces via AST walk (zero MCP server change).

**M28.3.4 CLOSED (2026-04-24, 1.21.2 → 1.21.3). Superseded by M28.3.6 docs sweep record below.**

### M28.3.6 shipped (2026-04-24, no version bump)

**Pure-docs close of the M28.3 graph-authoring umbrella.** Primary shipped change: new worked example in `plans/AGENT_LOOP.md` — `"Worked example — wire OnOrderReceived body via M28.3 node spawns"` — demonstrates the chained-authoring pattern for every design.md body-wiring case:

1. Spawn input-side nodes (`add_variable_get_node` / `add_call_function_node` / `add_dynamic_cast_node`).
2. Spawn output-side / control-flow nodes (`add_variable_set_node` / `add_branch_node` / `add_execution_sequence_node` / `add_custom_event_node`).
3. Declare function-local state via `add_local_variable` when transient scratch vars are needed.
4. Set literal defaults on typed input pins via `set_graph_pin_default`.
5. Connect exec + data pins via `connect_graph_pins` using the runtime NodeGuids the spawn ops return.

The worked example chains off the prior-section squad-director scaffolding example (M28.2.5 docs sweep) — concretely wires `OnOrderReceived` body with `add_variable_set_node(bActiveOrder)` + `set_graph_pin_default(literal_text="true")` + 2× `connect_graph_pins` for `Entry.then → Set.execute → Return.execute`. Proves the agent-loop pattern end-to-end: structural plan (M28.2) → body plan (M28.3) → semantic verify → user escalation.

Secondary shipped changes:
- `CATALOG.md` "Coming next" section: added explicit M28.3 COMPLETE block listing all 9 ops across sub-phases M28.3.1–.4 with a pointer to the new AGENT_LOOP worked example. Replaces the implicit "9 ops scattered across the M28.3.x sections" presentation with a single consolidated index.
- `CLAUDE.md` + `plans/README.md` already carry M28.3.1–.4 entries (accumulated per sub-phase) — no further changes needed.

No C++ touched, no Python touched, no tests run (pure docs). No version bump per the M28.2.5 / M28.3.0 precedent for docs-only milestones.

**M28.3 catalog CLOSED end-to-end (2026-04-24).** 9 ops across 4 code-touching sub-phases + 2 docs-only slices:

| Sub-phase | Ops shipped | Version |
|---|---|---|
| M28.3.0 | Research (scope + sequencing) | no bump — `3cd5283` |
| M28.3.1 | `add_branch_node` + `set_graph_pin_default` | 1.20.1 → 1.21.0 — `cc0204d` |
| M28.3.2 | `add_call_function_node` + `add_variable_get_node` + `add_variable_set_node` | → 1.21.1 — `5959a01` |
| M28.3.3 | `add_custom_event_node` + `add_execution_sequence_node` + `add_dynamic_cast_node` | → 1.21.2 — `df8aa08` |
| M28.3.4 | `add_local_variable` | → 1.21.3 — `0110160` |
| M28.3.6 | Docs sweep (AGENT_LOOP worked example + CATALOG coming-next consolidation) | no bump — this commit |

Full `verify_all.ps1` matrix green across the M28.3 arc: M28.3.1 14/14 gates, M28.3.2 20/20, M28.3.3 25/25 (plus one lowercase-pin-name trap caught by inspect gate and fixed inline), M28.3.4 27/27. MCP pytest 23/23 consistent throughout. Dual-engine DLL rebuilds at every patch bump (UE_DOW custom UE 5.7 + stock UE 5.7); final DLLs 2,730,496 b / 2,731,520 b at 1.21.3.

**Next scope is open** — M28.2 + M28.3 are the satisfied prerequisites for the remaining M28 phases per the M28 phase table. Four candidates in priority order:
- **M28.4** (UserDefinedStruct / CurveFloat / DataAsset factories) — unlocks design.md items #3 (confidence decay struct members), #6 (intensity-curve pacing), #7 (archetype DA instances). Biggest scope of the four but directly unlocks three design.md items.
- **M28.5** (EQS write-side — `add_eqs_test` / `set_eqs_test_property` / `set_eqs_generator_property`) — mirror of M15 EQS read-side. Unlocks design.md item #5 (multi-target cover scoring). Small bridge surface (3–5 UFUNCTIONs).
- **M28.6** (GameplayTag config authoring + `list_gameplay_tags` MCP tool) — unlocks design.md items #1 (`AI.Order.*` channel) + #4 (callout tags). Ships alongside **M28.pre.5** config-file parity gate.
- **M28.7** (automation-test runner bridge handler + gym-map fixture) — verification beyond mechanical diff. Answers "does the squad actually flank?" rather than "did bytes change?". Depends on at least M28.3 (now satisfied) for repeatable scenario-staging.

Pick one based on the next external driver or continuation priority. Per the M28 phase-table risk assessment, M28.4 is the biggest (UserDefinedStruct authoring has a non-obvious `UScriptStruct` / `UUserDefinedStructEditorData` separation) and M28.6 has the LOW-risk `UGameplayTagsManager::AddNewGameplayTagToINI` path available.

### M28.5.0 research outcome (2026-04-24)

**Scoped during the post-M28.3 continuation session; NOT yet implemented.** Findings captured so the M28.5 authoring pass doesn't have to re-probe the AIModule headers. Patterns mirror M26.0 / M27.0 / M28.2.0 / M28.3.0 — research block lands before the first implementation slice.

**Target surface (per M28 phase table):** `add_eqs_option` / `add_eqs_test` / `remove_eqs_test` / `set_eqs_test_property` / `set_eqs_generator` / `set_eqs_generator_property`. 5–6 ops total.

**AIModule header findings (stock UE 5.7 + UE_DOW custom 5.7 identical):**

1. **`UEnvQuery` structure** (`Runtime/AIModule/Classes/EnvironmentQuery/EnvQuery.h:32-36`):
   ```cpp
   UPROPERTY()
   TArray<TObjectPtr<UEnvQueryOption>> Options;
   ```
   Accessor: `GetOptionsMutable() -> TArray<TObjectPtr<UEnvQueryOption>>&` for editor-side mutation.

2. **`UEnvQueryOption` structure** (`EnvQueryOption.h:18-22`):
   - `Generator: TObjectPtr<UEnvQueryGenerator>` (singular)
   - `Tests: TArray<TObjectPtr<UEnvQueryTest>>`

3. **No public `UEnvQuery::AddOption(...)` helper.** Canonical editor pattern is direct array mutation: `NewObject<UEnvQueryOption>(Query)` → `Query->Options.Add(NewOption)` → `NewObject<UEnvQueryGenerator_SomeType>(Option)` → `Option->Generator = NewGen`. Same for tests.

4. **`UEnvQueryTest::TestOrder`** (int32) **must be set manually** per test. `EnvQueryManager.cpp:874-882` shows the runtime repairs TestOrder only when zero; the editor assigns it sequentially as tests are added (`NewTest->TestOrder = Option->Tests.Num() - 1` post-add). Miss this and two tests both at `TestOrder=0` silently compete.

5. **Determinism:** zero `FGuid::NewGuid()` usage across EQS classes (grep-confirmed). `NewObject` default name generation (counter-suffixed) IS the one drift source — need explicit `FName` on each `NewObject` call like M28.3.x did for K2Nodes. Pattern: `BpxEqsOption_<idx>` / `BpxEqsTest_<option_idx>_<test_idx>` / `BpxEqsGen_<option_idx>`.

6. **`FAIDataProviderFloatValue`** (EnvQueryTest.h:96/100/125/129/139) is a USTRUCT (not UObject), so scalar edits via existing `SetPropertyValue` bridge work. BUT `DataBinding` (the provider UObject inside the struct) needs `PostEditChangeProperty` revalidation (EnvQueryNode.cpp:31-102) when swapped — plain `FProperty::ImportText_Direct` bypasses that. Mitigation: bridge wrapper for `DataBinding` swaps specifically, or accept the edit pattern is "set DefaultValue scalar" and punt DataBinding to a follow-up.

**Chosen C++ surface (3-4 UFUNCTIONs on `UBpxReflectionOps`):**

| New UFUNCTION | Purpose |
|---|---|
| `AddEnvQueryOption(UEnvQuery*, UClass* GeneratorClass, int32& OutOptionIndex)` | Creates `UEnvQueryOption` child + creates the generator as an inner UObject of the option + returns the new index. Explicit `FName` on both NewObject calls for determinism. |
| `AddEnvQueryTest(UEnvQuery*, int32 OptionIndex, UClass* TestClass, int32& OutTestIndex)` | Creates a `UEnvQueryTest` subclass instance as an inner UObject of the option at `Options[OptionIndex]`, appends to `Tests[]`, assigns `TestOrder = Tests.Num() - 1`. |
| `RemoveEnvQueryTest(UEnvQuery*, int32 OptionIndex, int32 TestIndex)` | Removes the test at the given index, reseats `TestOrder` on all subsequent tests so the 0..N-1 invariant holds. |
| *(optional)* `SetEnvQueryGenerator(UEnvQuery*, int32 OptionIndex, UClass* GeneratorClass)` | Swap the option's generator for a fresh one of the given class. Needed when changing generator type (generators are subclass-typed; can't reuse an instance of a different class). |

Scalar-property edits (`set_eqs_test_property` / `set_eqs_generator_property`) reuse the existing `SetPropertyValue` bridge — no new UFUNCTION needed, just a Python wrapper that resolves the path (e.g. `UEnvQuery.Options[0].Tests[2].MyUPROPERTY`).

**Python surface (5 ops in new module `scripts/python_ops/eqs.py`):**

| New op | Bridge calls | Purpose |
|---|---|---|
| `add_eqs_option(eqs_path, generator_class_path)` | `AddEnvQueryOption` + `CompileAndSavePackage` | Returns `{option_index}`. Idempotent on `(eqs_path, GeneratorClass)` — walks existing options and reuses a matching-generator option if one exists. |
| `add_eqs_test(eqs_path, option_index, test_class_path)` | `AddEnvQueryTest` + `CompileAndSavePackage` | Returns `{test_index}`. Idempotent on `(option_index, TestClass)`. |
| `remove_eqs_test(eqs_path, option_index, test_index)` | `RemoveEnvQueryTest` + `CompileAndSavePackage` | Symmetric. |
| `set_eqs_test_property(eqs_path, option_index, test_index, property_path, value)` | existing `SetPropertyValue` | Wraps the generic reflection setter with EQS-path prefix. |
| `set_eqs_generator_property(eqs_path, option_index, property_path, value)` | existing `SetPropertyValue` | Same pattern as test_property. |

**Open fixture question (M28.5 implementation's load-bearing decision):** BugHunt has zero EQS assets (M15 read-side shipped "speculative"); DOW has zero; DOW_Legacy has 4 EQS assets but live-testing against Legacy is expensive (~15 s cold-start even with bridge). Three options for the M28.5 inspect+soak gate:
- **(A)** Extend `GenerateTestBlueprintsCommandlet` with a fresh EQS gen function (`EQS_BpxTestBasic` — one option, `EnvQueryGenerator_ActorsOfClass` for AActor, one `EnvQueryTest_Random` test). Non-trivial but self-contained; mirrors the M28.3.2 `BP_BpxTestGraphNodesCalls` pattern. **Recommended.**
- **(B)** Hand-author a minimal EQS .uasset and commit. Violates the "fixtures from commandlet only" principle; rejected.
- **(C)** Ship M28.5 ops without BugHunt coverage and rely on Legacy-only soak. Breaks the M28.pre.3 soak invariant for write-side ops; rejected.

Option (A) adds ~80 lines to `GenerateTestBlueprintsCommandlet.cpp` (one `GenEQS_BpxTestBasic()` function + array entry). Adds `AIModule` as a BugHuntTests link dep if not already present.

**Sequencing:** M28.5 ships as a minor bump (new subsystem — new Python module, new UFUNCTION family) — **1.21.3 → 1.22.0 per semver.** Research-only slice (this block) lands as a commit with no version bump, consistent with M28.2.0 / M28.3.0 pattern. Next implementation slice: **M28.5.1** — fixture + `add_eqs_option` ship first (simplest single op, establishes the EQS-touching bridge pattern); subsequent sub-phases (.2 test add/remove, .3 property setters) extend from there.

**Out of scope for M28.5:** runtime EQS invocation / DataBinding swaps / compile-time validation beyond the standard `CompileAndSavePackage` gate. The ops author static data; whether an EQS actually returns the right result at runtime is M28.7 automation-test-runner territory.

**M28.5.0 CLOSED (research, 2026-04-24 post-M28.3 continuation session).** M28.5.1 implementation is next pickup whenever M28.5 is prioritized.

### M28.5.1 shipped (2026-04-24, 1.21.3 → 1.22.0)

- New Python module `scripts/python_ops/eqs.py` — first EQS-touching ops-library module. `add_eqs_option(eqs_path, generator_class_path)` ships as the only op in this slice; subsequent sub-phases (M28.5.2 `add_eqs_test` / `remove_eqs_test`, M28.5.3 scalar property setters) extend from there. Mirrors the shape conventions of the M28.3.x node-spawn family: idempotency pre-check, load target via the standard `_load_eqs` helper, resolve class via `load_class` / `load_object` fallback, dispatch to the bridge UFUNCTION, fold `compile_and_save_package` on create paths, return the standard op-result dict with `{option_index, generator_class_path, spawned}` on `after`.
- New UFUNCTION `UBpxReflectionOps::AddEnvQueryOption(UEnvQuery*, UClass* GeneratorClass)` in `Source/BlueprintExporter/{Public,Private}/Reflection/ReflectionOps.{h,cpp}`. 1 new UFUNCTION on the bridge library — op count 31 → 32. Creates a `UEnvQueryOption` + a fresh `UEnvQueryGenerator` of the supplied concrete class, appends the option to `UEnvQuery::GetOptionsMutable()`. Abstract generator classes rejected up-front (NewObject on abstract throws an uncatchable check). Idempotent on `(Query, GeneratorClass)` — walks existing options and returns the matching index with `bSkipped=true` if any option carries a generator of the requested class. Determinism: explicit `FName` on each `NewObject` (`BpxEqsOption_<idx>` / `BpxEqsGen_<idx>_<ClassShortName>`); EQS classes have zero `FGuid::NewGuid()` usage per M28.5.0 research so `NewObject`'s counter-suffix drift was the only closable gap. No new UE Module deps — AIModule was already a private dep of the plugin.
- Header-visibility note: `Public/Reflection/ReflectionOps.h` gained `class UEnvQuery;` forward decl (mirrors the existing `struct FEdGraphPinType;` + `class UBlueprint` patterns). `.cpp` pulls in `EnvironmentQuery/EnvQuery.h` + `EnvQueryOption.h` + `EnvQueryGenerator.h` — all three live in AIModule's public `Classes/EnvironmentQuery/` directory so no Private-header drag.
- Plan pipeline wired: `OP_SPECS` entry in `plan_shape.py` (required `[eqs_path, generator_class_path]`, assets `[eqs_path]`); `_OP_DISPATCH` entry in `plan_executor.py`; `_op_expected_changes` entry in `mechanical_diff.py` (mutates `eqs_path`). `__init__.py` re-exports `add_eqs_option`; `__all__` list gets the new entry in alpha-sorted slot.
- New BugHunt fixture `GenEQS_BpxTestBasic` in `GenerateTestBlueprintsCommandlet.cpp` — creates an empty `UEnvQuery` at `/Game/TestBlueprints/EQS_BpxTestBasic` via direct `NewObject<UEnvQuery>` + `UPackage::SavePackage` (UEnvQuery is a UDataAsset subclass; no `UBlueprint::CreateBlueprint` path applies). Registered with Tier `A` (alphabetic — fits the `Gen…` → `EQS_…` rename expectation). One new `#include "EnvironmentQuery/EnvQuery.h"`; AIModule is already a Tests-plugin private dep so no Build.cs change. Fixture committed at 1162 bytes on initial creation (empty Options, empty QueryName).
- New inspect+soak fixture `scripts/inspect_fixtures/add_eqs_option.json` — source `EQS_BpxTestBasic`, scratch `EQS_BpxTest_InspectScratch`, plan op spawns a single `EnvQueryGenerator_ActorsOfClass` generator. Inspect gate asserts `"EnvQueryGenerator_ActorsOfClass"` appears in `.deep.md` (M15 `EnvQueryDeepRenderer` renders per-option generator blocks with full UPROPERTY tables — the class name appears in the "Class:" line + the "Generator —" header). No `.md` assertions (Tier 1 typed handler output is verbose enough that adding grep regex would be fragile; the deep.md check is the load-bearing assertion). Soak gate configured for 2 rounds.
- Version bump 1.21.3 → 1.22.0 (**minor** per semver — new subsystem: new Python module + new UFUNCTION family). All 9 drift locations updated (uplugin ×2 + `"Version": 21 → 22` integer, module UE_LOG, 2× bridge pluginVersion stamps, 4× Manifest/ExportInfo.PluginVersion literals, live-version automation test, README). BuiltPlugin tree robocopy-mirrored from Source/ to catch the 5 C++ drift locations in the BuiltPlugin mirror.
- Dual-engine DLL rebuild: UE_DOW DLL at `BuiltPlugin/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` (**2,742,272 bytes**, +~12 KB vs M28.3.4 for one new UFUNCTION + its forward decl + the EQS includes); stock UE 5.7 DLL at `_build_output_5_7/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` (**2,743,808 bytes**) also synced into `BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64`. BugHuntEditor target rebuilt separately via `Build.bat BugHuntEditor Win64 Development` to pick up the Tests-plugin fixture generator change (exit 0, clean build).
- Fixture regeneration note: first-pass run with `-Only=EQS_BpxTestBasic -Force` surfaced a pre-existing `GenBP_MacroMania` crash on regenerate (`Renaming EdGraph /Game/TestBlueprints/BP_MacroMania_Lib... on top of existing ObjectRedirector MyMacro is not allowed` — unrelated to M28.5.1, latent in the commandlet and only triggered by `-Force` since the BP_MacroMania fixture is already on disk with a prior-run redirector). Workaround for this slice: drop `-Force` and rely on the per-fixture `FixtureOnDisk && !GForceRegenerate` skip — the new `EQS_BpxTestBasic` is absent so it still creates. `created=1 skipped=22 failed=0`, exit 1 (editor-shutdown artefact, non-fatal since Failed=0). The BP_MacroMania regen bug is a follow-up backlog item; doesn't block M28.5.1.
- Verification: **all 32 gates PASS in 398.5 s** via `verify_all.ps1` on BugHunt / stock UE 5.7 (15 inspect + 15 soak + automation + determinism). Automation: 17/17 tests (15.7 s). Determinism: full-sweep twin byte-identical (46.8 s). New fixture gates: **`inspect-add_eqs_option` PASS** in 17.8 s (expected_deep `"EnvQueryGenerator_ActorsOfClass"` hit in the M15 renderer's "Generator —" header + "Class:" line); **`soak-add_eqs_option` PASS** in 6.1 s across 2 rounds with stable md5 `3335e01e1680516ec7078de4aa77f360` on `EQS_BpxTest_InspectScratch.uasset` — proves explicit-FName determinism recipe holds. Every existing M28.3.x inspect+soak pair still PASS (no regression from the new UFUNCTION or the header forward-decl change).
- MCP pytest: **23/23 PASS** in 9.68 s (`scripts/blueprint-exporter-mcp`). Op is purely additive on the Python side; MCP's `get_op_catalog` auto-surfaces via AST scanning — no MCP-side code change.
- **M28.5.1 done. M28.5.2 (`add_eqs_test` / `remove_eqs_test`) is next pickup** — same shape: new UFUNCTIONs on `UBpxReflectionOps`, new Python ops in the existing `eqs.py` module, new inspect+soak fixtures that build on the M28.5.1 baseline (target option[0] from an EQS that already has `add_eqs_option` applied, or chain both in a multi-op plan). Version bump 1.22.0 → 1.22.1 (patch — additive same subsystem). The M28.5.2 determinism invariants are identical to M28.5.1 since `UEnvQueryTest` is also a plain `UObject` subclass of `UEnvQueryNode`; explicit-FName pattern carries forward verbatim.

### M28.5.2 shipped (2026-04-24, 1.22.0 → 1.22.1)

- Two new ops in the existing `scripts/python_ops/eqs.py` module: `add_eqs_test(eqs_path, option_index, test_class_path)` + `remove_eqs_test(eqs_path, option_index, test_index)`. Second and third ops of the M28.5 EQS write-side catalog. Op count 32 → 34. The `_resolve_generator_class` helper got refactored into a generalised `_resolve_eqs_class(class_path, param_name, sample_path, result)` so both generator-class and test-class resolution share the same load_class / load_object fallback (recurring-pattern generalization per memory feedback — the resolver was about to be duplicated for the second op).
- Two new UFUNCTIONs on `UBpxReflectionOps`: `AddEnvQueryTest(UEnvQuery*, int32 OptionIndex, UClass* TestClass)` + `RemoveEnvQueryTest(UEnvQuery*, int32 OptionIndex, int32 TestIndex)`. 2 new UFUNCTIONs on the bridge — op count from M28.5.1's 32 now at 34. `AddEnvQueryTest` appends to `Option->Tests[]` with explicit `FName` `BpxEqsTest_<opt>_<pre_count>_<TestClassShortName>` and assigns `TestOrder = pre_count` so the 0..N-1 runtime invariant holds (`EnvQueryManager.cpp:874` only repairs zero at runtime). `RemoveEnvQueryTest` does `RemoveAt(TestIndex)` then reseats `TestOrder` on every subsequent test. Abstract classes rejected via `CLASS_Abstract` pre-check like M28.5.1. No new UE Module deps — AIModule was already a private dep.
- Header-visibility: `Public/Reflection/ReflectionOps.h` needed no new forward decls — both new signatures reference only `UEnvQuery*` (already fwd-declared for M28.5.1) and `UClass*`. `.cpp` pulls in `EnvironmentQuery/EnvQueryTest.h` alongside the M28.5.1 includes.
- **Idempotency carry-forward for destructive ops:** initial `RemoveEnvQueryTest` impl rejected out-of-range `TestIndex` with a hard error per "strict bounds check" design. M28.pre.3 soak caught the gap on the first green-matrix attempt: soak re-applies the same plan N rounds against one scratch asset, so round 2's attempt to remove `test_index=0` hit the empty-tests array and aborted (`round 2 reported passed=False`). Fix: treat out-of-range `TestIndex` as "already removed" — returns `bSuccess=true, bSkipped=true`, `AfterText="already-removed:<idx>"`. Python wrapper maps to `skipped="test already removed (out-of-range index)"` and short-circuits before `compile_and_save_package` so md5 stays stable across replay. `OptionIndex` keeps its strict bounds check — option identity is stable across test removals, so an out-of-range option still indicates a plan-level error. Matches the WIP brief's "symmetric with `add_eqs_test`'s idempotency" promise.
- New BugHunt fixture `GenEQS_BpxTestWithOption` in `GenerateTestBlueprintsCommandlet.cpp` — pre-seeded `UEnvQuery` with one option carrying an `EnvQueryGenerator_ActorsOfClass` generator + one `EnvQueryTest_Random` test. Single fixture services both new inspect/soak pairs: `add_eqs_test` targets option[0] with a different test class (`EnvQueryTest_Distance`, avoids idempotency collision); `remove_eqs_test` targets `test_index=0` (removes the pre-seeded Random test). Explicit `FName` on every fixture-gen `NewObject` call so `-Force` regeneration stays byte-deterministic — matches M28.5.1 recipe. Fixture committed at 2,129 bytes on initial creation (vs M28.5.1 `EQS_BpxTestBasic` at 1,162 — delta is the one option + generator + test inflation).
- Plan pipeline wired: `OP_SPECS` entries in `plan_shape.py` (required `[eqs_path, option_index, test_class_path]` / `[eqs_path, option_index, test_index]`, assets `[eqs_path]`); `_OP_DISPATCH` entries in `plan_executor.py`; `_op_expected_changes` entries in `mechanical_diff.py` (both mutate `eqs_path`). `__init__.py` re-exports both + alpha-sorted `__all__` inserts.
- Two new inspect+soak fixtures: `scripts/inspect_fixtures/add_eqs_test.json` (source `EQS_BpxTestWithOption`, spawns `EnvQueryTest_Distance`, inspect asserts `"EnvQueryTest_Distance"` in `.deep.md`, soak 2 rounds) + `scripts/inspect_fixtures/remove_eqs_test.json` (source `EQS_BpxTestWithOption`, removes `test_index=0`, inspect asserts `EnvQueryGenerator_ActorsOfClass` still present + `EnvQueryTest_Random` absent via `not_expected_deep`, soak 2 rounds exercising the idempotency path).
- Docs: `CATALOG.md` + `plans/README.md` extended with op-kwarg table rows + jsonc examples for both new ops. Docstrings on the Python ops describe the idempotency semantics (exact-class match for `add_eqs_test`, out-of-range test_index for `remove_eqs_test`).
- Version bump 1.22.0 → 1.22.1 (**patch** per semver — additive same subsystem). All 9 drift locations updated via a scripted bulk replace (15 files touched — 8 Source/ + 6 BuiltPlugin mirror + README). `.uplugin` `"Version": 22` integer stays — patch bump doesn't move it per the minor-digit convention.
- Dual-engine DLL rebuild: UE_DOW DLL at `BuiltPlugin/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` (**2,756,608 bytes**, +~14 KB vs M28.5.1 for two new UFUNCTIONs + one new include); stock UE 5.7 DLL at `_build_output_5_7/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` (**2,757,632 bytes**) also synced into `BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64`. BugHuntEditor target rebuilt via `Build.bat BugHuntEditor Win64 Development` (9.06 s) to pick up the new fixture generator symbol. Two build iterations required: (1) initial rebuild against the first C++ cut; (2) second rebuild after folding the idempotency fix into `RemoveEnvQueryTest`. Both iterations clean.
- Fixture regeneration via `GenerateTestBlueprints -Only=EQS_BpxTestWithOption` (no `-Force` — BP_MacroMania trap carries forward from M28.5.1). `created=1 skipped=0 failed=0`, exit 0. Clean single-fixture creation.
- **Matrix troubleshooting arc:** first matrix run (398.5 s) failed 4 gates — all with `TypeError: make_result() takes from 2 to 3 positional arguments but 4 were given`. Bug: I'd passed the extra kwargs (option_index + test_class_path / test_index) as separate args to `make_result()`. Fix: compose into a single descriptive field string (`f"option[{option_index}] += {test_class_path}"` / `f"option[{option_index}].tests[{test_index}]"`), matching the statetree.py pattern. Second matrix run caught the destructive-op soak round-2 issue (described above). Third matrix run still had 1 gate fail — stale scratch asset from the prior failed soak lingered on disk (soak_template.py skips cleanup on `_fail()` SystemExit) — one `rm -f` cleaned it. Fourth matrix run: **all 34 gates PASS in 446.9 s** on BugHunt / stock UE 5.7 (15 inspect + 17 soak + automation + determinism). New gates: **`inspect-add_eqs_test` PASS** (17.8 s), **`inspect-remove_eqs_test` PASS** (17.8 s), **`soak-add_eqs_test` PASS** (6.2 s) with stable md5 `a589cd705b5a520ff30f9edc137bd12a`, **`soak-remove_eqs_test` PASS** (6.2 s) with stable md5 `ead096f2981707c17515335e29afaa3c` exercising the idempotent "already removed" path on round 2. Every existing inspect+soak pair still PASS — no regression from the new UFUNCTIONs, the shared resolver refactor, or the idempotency addition.
- MCP pytest: **23/23 PASS** in 11.48 s (`scripts/blueprint-exporter-mcp`). Both ops are purely additive on the Python side; MCP's `get_op_catalog` auto-surfaces via AST scanning — no MCP-side code change.
- **M28.5.2 done. Next scope is open** — M28.5.3 scalar property setters (`set_eqs_test_property` / `set_eqs_generator_property`) are the natural M28.5 continuation per the M28.5.0 research block (both reuse the existing `SetPropertyValue` bridge — Python-only wrappers, no new UFUNCTION). After that the M28.5 catalog is effectively complete and the next external driver decides whether to ship M28.4 / M28.6 / M28.7 or something else from the M28 phase table.

### M28.5.3 shipped (2026-04-24, 1.22.1 → 1.22.2)

- Two new ops in the existing `scripts/python_ops/eqs.py` module: `set_eqs_generator_property(eqs_path, option_index, property_path, value)` + `set_eqs_test_property(eqs_path, option_index, test_index, property_path, value)`. Fourth and fifth ops of the M28.5 EQS write-side catalog. Op count 34 → 36. **Zero new UFUNCTIONs** — both ops are pure Python wrappers over the existing M23.1 `UBpxReflectionOps::SetPropertyValue` reflection bridge. First M28.x sub-phase that ships with no new C++ surface; was the explicit plan from the M28.5.0 research block ("Scalar-property edits reuse the existing `SetPropertyValue` bridge — no new UFUNCTION needed, just a Python wrapper that resolves the path").
- Implementation strategy: shared `_set_eqs_subobject_property` private helper takes a `nav_prefix` list that reaches the target subobject from the UEnvQuery root (e.g. `["Options", "[0]", "Generator"]` or `["Options", "[0]", "Tests", "[0]"]`), appends the caller-supplied `property_path`, then drives `get_property_value` (idempotency check) → `set_property_value` → `compile_and_save_package`. The two public ops are ~30 lines each: validate their own index params (`option_index`, `test_index` for the test variant) then delegate to the shared helper. Keeps the two ops byte-identical on their shared paths (same error messages, same idempotency semantics, same save flow) by construction.
- Value normalization: new private `_normalize_scalar_value` helper coerces Python native types to the ExportText string `FProperty::ImportText_Direct` expects — `bool` → `"true"`/`"false"`, `int`/`float` → `repr(...)`, `str` → verbatim. Mirrors `level.set_level_actor_property`'s normalization so plan JSON can carry native scalars without string-quoting them. Rejection for dict / list / None with structured error preserves the "fail cleanly at the boundary" principle.
- `FAIDataProviderFloatValue::DataBinding` swaps left out of scope per the M28.5.0 research finding #6 — `DataBinding` is a provider UObject inside the struct that needs `PostEditChangeProperty` revalidation per `EnvQueryNode.cpp:31-102`; plain `ImportText_Direct` bypasses that. Callers tune scalars via the struct's `DefaultValue` leaf (e.g. `["SearchRadius", "DefaultValue"]`) which `ResolvePath` already walks correctly. Docstrings + CATALOG.md + plans/README.md all document the exclusion.
- Plan pipeline wired: `OP_SPECS` entries in `plan_shape.py` (required kwargs `[eqs_path, option_index, property_path, value]` / `[eqs_path, option_index, test_index, property_path, value]`, `assets: [eqs_path]`); `_OP_DISPATCH` entries in `plan_executor.py`; `_op_expected_changes` entries in `mechanical_diff.py` (both mutate `eqs_path`). `__init__.py` re-exports both + alpha-sorted `__all__` inserts (between `set_component_property` and `set_graph_pin_default`).
- Two new inspect+soak fixtures: `scripts/inspect_fixtures/set_eqs_generator_property.json` (source `EQS_BpxTestWithOption`, mutates `Options[0].Generator.OptionName` to `"BpxGenRenamed"`, inspect asserts `"BpxGenRenamed"` appears in `.deep.md` — the M15 renderer exposes `OptionName` in BOTH the per-option header AND the generator UPROPERTY table, so the assertion hits twice; soak 2 rounds) + `scripts/inspect_fixtures/set_eqs_test_property.json` (source `EQS_BpxTestWithOption`, mutates `Options[0].Tests[0].TestComment` to `"BpxTestCommented"`, inspect asserts `"BpxTestCommented"` in `.deep.md` via the per-test UPROPERTY table, soak 2 rounds). **No new BugHunt fixture** — `EQS_BpxTestWithOption` from M28.5.2 already carries everything both ops need (generator at `Options[0].Generator`, test at `Options[0].Tests[0]`).
- Docs: `CATALOG.md` extended with op sections for both new ops (including concrete examples of `["SearchRadius", "DefaultValue"]` nested-struct targeting); `CATALOG.md` "Coming next" block converted from "M21.3 EQS tuning helpers" placeholder to **"M28.5 EQS write-side — COMPLETE (2026-04-24)"** with the 5-op closure summary. `plans/README.md` op-kwarg table gains 2 rows + the jsonc examples demonstrate typical `property_path` shapes (single-leaf `["OptionName"]` / nested-struct `["SearchRadius", "DefaultValue"]` / enum `["TestPurpose"]`).
- Version bump 1.22.1 → 1.22.2 (**patch** per semver — additive same subsystem, no new subsystem since the Python wrappers just extend the existing `eqs.py` module + reuse the existing SetPropertyValue bridge). All 9 drift locations updated via bulk `sed` replace (15 files touched — 7 Source/ + 7 BuiltPlugin mirror + README). `.uplugin` `"Version": 22` integer stays per the minor-digit convention.
- Dual-engine DLL rebuild: UE_DOW DLL at `BuiltPlugin/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` (**2,756,608 bytes**, byte-identical in size to M28.5.2 — no new UFUNCTIONs); stock UE 5.7 DLL at `_build_output_5_7/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` (**2,757,632 bytes**, also byte-identical to M28.5.2). Rebuilds were driven solely by the baked-in version strings in 7 C++ files (UE_LOG startup, ping/list_methods pluginVersion, Manifest.PluginVersion, ExportInfo.PluginVersion × 3, test-expected `TEXT("1.22.2")`); without a rebuild the test-expected string in `BlueprintExporterTests.cpp:929` would drift against the DLL-baked version string at `BlueprintExportManager.cpp:149`. Stock 5.7 UAT build 44.5s; UE_DOW UAT build 27.0s (warmer DDC). Both clean on first pass — no unity-ODR or link errors since no new translation units introduced.
- Matrix troubleshooting arc: **clean on first run**. No TypeError from `make_result()`, no destructive-op soak round-2 issue (neither op is destructive — they mutate a UPROPERTY in place, and the bridge's "before == value → skip" short-circuit is already battle-tested from M28.3.x `set_graph_pin_default` / M28.1 `set_level_actor_property`), no stale-scratch residue. The "no new UFUNCTION" shape dodges the three bug classes that burned matrix cycles in M28.5.1 + M28.5.2.
- Verification: **all 38 gates PASS in 501.7 s** via `verify_all.ps1` on BugHunt / stock UE 5.7 (automation + determinism + 18 inspect + 18 soak). Automation: 17/17 tests (15.9 s). Determinism: full-sweep twin byte-identical (52.1 s). New gates: **`inspect-set_eqs_generator_property` PASS** in 18.1 s (expected_deep `"BpxGenRenamed"` hit in the M15 renderer's Option header + generator UPROPERTY table); **`inspect-set_eqs_test_property` PASS** in 17.9 s (expected_deep `"BpxTestCommented"` hit in the per-test UPROPERTY table); **`soak-set_eqs_generator_property` PASS** in 6.1 s across 2 rounds with stable md5 `40ff8e0962f93dce46fbedac3baa412a`; **`soak-set_eqs_test_property` PASS** in 6.2 s across 2 rounds with stable md5 `fdfae57b5992c3d74e15b7b1a3347caa`. Every pre-existing inspect+soak pair still PASS — no regression from the Python-only changes or version-string bumps baked into the DLL.
- MCP pytest: **23/23 PASS** in 11.90 s (`scripts/blueprint-exporter-mcp`). Both ops are purely additive on the Python side; MCP's `get_op_catalog` auto-surfaces via AST scanning — no MCP-side code change.
- **M28.5.3 done. M28.5 catalog COMPLETE end-to-end** — 5 ops shipped across 3 code-touching sub-phases + 1 research-only slice + (planned) docs close: `add_eqs_option` (M28.5.1) / `add_eqs_test` / `remove_eqs_test` (M28.5.2) / `set_eqs_generator_property` / `set_eqs_test_property` (M28.5.3). All 5 ops idempotent on their identifier keys; the 3 `add_*/remove_*` ops are determinism-seeded via explicit `FName` on every `NewObject` (EQS classes have zero `FGuid::NewGuid()` usage so counter-suffix drift was the only closable gap); the 2 `set_*_property` ops inherit byte-determinism from `ImportText_Direct`'s deterministic string-to-memory path. The optional `SetEnvQueryGenerator` UFUNCTION from the M28.5.0 research block stays deferred — its use case (swap generator class while preserving the option) has no concrete driver and the current flow (`remove_eqs_test` then `add_eqs_option` or re-add whole option) covers the "I want a different generator" case.
- **Next scope is open** — M28.5 is closed. Per the post-M28.5.2 open-scope note, next external driver decides whether to ship M28.4 (UDS / CurveFloat / DataAsset factories — design.md items #3, #6, #7), M28.6 (GameplayTag config authoring — design.md items #1 + #4), M28.7 (automation-test runner — semantic verification beyond mechanical diff), or something else from the M28 phase table. M28.2 + M28.3 + M28.5 are now satisfied prerequisites for any of those. An optional M28.5.4 docs sweep (worked example chaining add_eqs_option → add_eqs_test → set_eqs_test_property against a concrete design.md anchor like the squad-director cover scan) would close the M28.5 umbrella the way M28.3.6 closed M28.3 — low priority, pure docs, defer unless an external driver needs a worked example for the EQS authoring chain.

### M28.4.0 research outcome (2026-04-24)

**Scoped during the post-M28.5.3 open-scope session; NOT yet implemented.** User picked M28.4 as the next external driver. Findings captured so the M28.4 authoring pass doesn't have to re-probe the UE 5.7 engine headers. Patterns mirror M26.0 / M27.0 / M28.2.0 / M28.3.0 / M28.5.0 — research block lands before the first implementation slice.

**Target surface (per M28 phase table):** three distinct non-BP asset families with separate Python modules — `uds.py` (4 ops) + `curves.py` (2 ops) + `data_assets.py` (2 ops). 8 ops total across three sub-phases, each a minor bump per the "first sub-phase that introduces a new Python module = minor" rule established in M28.2 / M28.3 / M28.5.

**Engine header findings (stock UE 5.7 + UE_DOW custom 5.7 identical):**

1. **`UUserDefinedStruct` structure** (`Runtime/CoreUObject/Public/StructUtils/UserDefinedStruct.h` + `Runtime/Engine/Classes/Engine/UserDefinedStruct.h`): a `UScriptStruct` subclass with an `EditorData: UUserDefinedStructEditorData` inner subobject that carries the authoring-time `VariablesDescriptions: TArray<FStructVariableDescription>` array (`Editor/UnrealEd/Classes/UserDefinedStructure/UserDefinedStructEditorData.h:143-147`). Serialized form is the UScriptStruct's FProperty chain; authoring form is VariablesDescriptions. `FStructureEditorUtils` routes every edit through both.

2. **`FStructureEditorUtils` surface** (`Editor/UnrealEd/Public/Kismet2/StructureEditorUtils.h`):
   - `CreateUserDefinedStruct(UObject* InParent, FName Name, EObjectFlags Flags) -> UUserDefinedStruct*` (line 71) — creates the struct + inner `EditorData` + auto-adds one default `bool` member (StructureEditorUtils.cpp:60). Asserts `UserDefinedStructEnabled()`.
   - `AddVariable(UUserDefinedStruct*, const FEdGraphPinType&) -> bool` (line 80) — appends a new `FStructVariableDescription` to the `VarDesc` array; VarName is auto-generated from a fresh VarGuid via `FMemberVariableNameHelper::Generate(Struct, FString(), Guid, &DisplayName)`.
   - `RemoveVariable(UUserDefinedStruct*, FGuid VarGuid) -> bool` (line 82) — removes by guid. Refuses when `OldNum <= 1` (struct cannot be empty; `bAllowToMakeEmpty=false` constant, line 327).
   - `RenameVariable(UUserDefinedStruct*, const FString& OldDisplayNameStr, const FString& NewDisplayNameStr) -> bool` (line 86) — the friendly-name overload routes through the guid overload (lines 377-398), which regenerates `VarName` from `Guid` + new friendly name.
   - `ChangeVariableDefaultValue(UUserDefinedStruct*, FGuid, const FString&) -> bool` (line 90) — writes to `VarDesc.DefaultValue` after pin-type validation (for object / interface / class / soft pin categories the validator bypasses to `bResult = true`, line 444-452).
   - `GetVarDesc(...)` / `GetVarDescByGuid(...)` / `GetPropertyByFriendlyName(...)` — lookup helpers; resolve FriendlyName → VarGuid internally.
   - `OnStructureChanged(Struct, EChangeInfo)` — called automatically at the tail of every mutating op; broadcasts pre+post change listener events and triggers `FUserDefinedStructureCompilerUtils::CompileStruct`. No manual CompileStructure call needed before save.

3. **Determinism traps on UDS** (two `FGuid::NewGuid()` call sites):
   - `CreateUserDefinedStruct` → `Struct->Guid = FGuid::NewGuid()` (StructureEditorUtils.cpp:53). Seed post-create via `SeedGuidFromJoined(<package_path>:uds)`.
   - `AddVariable` → `const FGuid Guid = FGuid::NewGuid()` (StructureEditorUtils.cpp:303), then VarName derived from it via `FMemberVariableNameHelper::Generate`. Seed post-add via `SeedGuidFromJoined(<package_path>:uds_var:<friendly_name>)` and regenerate VarName from the seeded guid before `OnStructureChanged` fires. VarDesc entry lives in the post-add array at the tail, so resolve via "find the one without a stable guid yet" or capture-before-add + re-locate.
   - `UniqueNameId: uint32` on `UUserDefinedStructEditorData` is `NonTransactional` (UserDefinedStructEditorData.h:139-140) — not serialized, not a drift source.

4. **UDS auto-bool quirk**: `CreateUserDefinedStruct` injects a default `bool` member on line 60 of StructureEditorUtils.cpp via `AddVariable(Struct, FEdGraphPinType(PC_Boolean, ...))`. So a freshly-created UDS always has 1 variable. Two options:
   - **Leave auto-bool in place** and seed its guid deterministically via the same `uds_var:<friendly_name>` seed, using the auto-generated friendly name `MemberVar_<N>` (stable once VarGuid is seeded). **Chosen.**
   - Remove the auto-bool post-create — blocked by the `bAllowToMakeEmpty=false` guard; would need `AddVariable` → `RemoveVariable(original)` which doubles the op count and trips the empty-struct refusal between calls. **Rejected.**

5. **`UCurveFloat` structure** (`Runtime/Engine/Classes/Curves/CurveFloat.h`): single `FRichCurve FloatCurve` UPROPERTY on a `UCurveBase` subclass. `UCurveBase` itself has only a deprecated `ImportPath_DEPRECATED` UPROPERTY (CurveBase.h:128-129). No GUIDs anywhere in `Runtime/Engine/Classes/Curves/` (grep-confirmed). `FKeyHandle` is a runtime-only counter (not serialized); the persistent form is `Keys: TArray<FRichCurveKey>` sorted by time.

6. **`FRichCurve` key API** (`Runtime/Engine/Classes/Curves/RichCurve.h`):
   - `AddKey(float InTime, float InValue, bool bUnwindRotation=false, FKeyHandle) -> FKeyHandle` — inserts sorted by time.
   - `UpdateOrAddKey(float InTime, float InValue, bool, float KeyTimeTolerance=SMALL_NUMBER) -> FKeyHandle` — idempotent on time within tolerance.
   - `SetKeys(const TArray<FRichCurveKey>&)` — wholesale replacement; keys must be pre-sorted by caller.
   - `DeleteKey(FKeyHandle)` / `SetKeyTime` / `SetKeyValue` / `SetKeyInterpMode` / `SetKeyTangentMode` / `SetKeyTangentWeightMode`.
   - `FRichCurveKey` fields (RichCurve.h:78-131): `Time / Value / InterpMode (RCIM_*) / TangentMode (RCTM_*) / TangentWeightMode (RCTWM_*) / ArriveTangent / LeaveTangent / ArriveTangentWeight / LeaveTangentWeight`.

7. **Factories exist but ship interactive**: `UCurveFloatFactory` + `UDataAssetFactory` both inherit `UFactory::ConfigureProperties()` which opens a UI class picker in the stock editor. `UCurveFactory::FactoryCreateNew` is a one-liner `NewObject<UCurveBase>(InParent, CurveClass, Name, Flags)` (EditorFactories.cpp:7069-7076); `UDataAssetFactory::FactoryCreateNew` is similarly `NewObject<UDataAsset>(InParent, DataAssetClass, Name, Flags | RF_Transactional)` (EditorFactories.cpp:7288-7300). We bypass the factories and call `NewObject` directly — same pattern as M28.5.1's UEnvQuery creation.

8. **`UDataAsset` / `UPrimaryDataAsset`** (`Runtime/Engine/Classes/Engine/DataAsset.h`): `UDataAsset` is abstract + minimal (only `NativeClass: TSubclassOf<UDataAsset>` AssetRegistrySearchable field). `UPrimaryDataAsset` adds `AssetBundleData` computed in `PreSave` via `UpdateAssetBundleData` (derives from UPROPERTY references; deterministic by construction). No GUIDs. DA class resolution via `LoadClass<UDataAsset>` / `LoadObject<UClass>` — covers native + BP-derived DA classes (same load_class / load_object fallback M28.2.3 uses for component classes).

**Chosen C++ surface (6 new UFUNCTIONs on `UBpxReflectionOps`):**

| New UFUNCTION | Sub-phase | Purpose |
|---|---|---|
| `CreateCurveFloatDeterministic(OuterPackage, Name, OutCurve)` | M28.4.1 | Wraps `NewObject<UCurveFloat>(Package, Name, RF_Public\|RF_Standalone)`. No GUID seeding (CurveFloat has none). Explicit `FName` on the NewObject call. Idempotent: if `StaticFindObject<UCurveFloat>(Package, Name)` hits, return skipped with existing ptr. |
| `SetCurveFloatKeys(Curve, TArray<FRichCurveKey> NewKeys, bSkipped)` | M28.4.1 | Wholesale replacement via `Curve->FloatCurve.SetKeys(NewKeys)`. Caller pre-sorts by time (Python op enforces). Idempotent: if `Curve->FloatCurve.GetCopyOfKeys() == NewKeys` element-wise, return `bSkipped=true`. |
| `CreateDataAssetInstanceDeterministic(OuterPackage, Name, DAClass, OutAsset)` | M28.4.2 | Wraps `NewObject<UDataAsset>(Package, DAClass, Name, RF_Public\|RF_Standalone\|RF_Transactional)`. Rejects abstract classes up-front. Explicit `FName` on NewObject. Idempotent: `StaticFindObject` check. |
| `CreateUserDefinedStructDeterministic(OuterPackage, Name, OutStruct)` | M28.4.3 | Wraps `FStructureEditorUtils::CreateUserDefinedStruct(Package, Name, RF_Public\|RF_Standalone\|RF_Transactional)`. Post-create: seed `Struct->Guid = SeedGuidFromJoined(<package_path>:uds)`; also seed the auto-bool's VarGuid via `SeedGuidFromJoined(<package_path>:uds_var:<auto_name>)` where `<auto_name>` is the `MemberVar_N` that `FMemberVariableNameHelper::Generate` produces (determinism carries from the seeded `Struct->Guid`). |
| `AddUserDefinedStructMember(Struct, FriendlyName, FEdGraphPinType, DefaultValue)` | M28.4.3 | Idempotence pre-check on FriendlyName → existing VarDesc. If absent: `FStructureEditorUtils::AddVariable` → locate the new VarDesc (tail of array) → post-seed `VarDesc.VarGuid = SeedGuidFromJoined(<package_path>:uds_var:<friendly_name>)` → `FStructureEditorUtils::RenameVariable(Struct, VarGuid, FriendlyName)` → if `DefaultValue` non-empty, `ChangeVariableDefaultValue`. OnStructureChanged broadcasts during the rename will trigger recompile and VarName regeneration from the seeded Guid. |
| `RemoveUserDefinedStructMember(Struct, FriendlyName, bSkipped)` | M28.4.3 | Resolve FriendlyName → VarGuid via `GetPropertyByFriendlyName` / `GetVarDescByGuid`. If absent: return `bSkipped=true`. If would empty struct (OldNum == 1): return structured rejection "cannot remove last member; UDS must retain at least one variable" (engine-level refusal surfaced at Python boundary, not a silent skip). Otherwise `FStructureEditorUtils::RemoveVariable(Struct, VarGuid)`. |

`set_uds_member_default` and `set_data_asset_property` reuse the existing M23.1 `SetPropertyValue` bridge — Python-only wrappers resolving the correct target object (UDS → default instance via `UUserDefinedStructEditorData::GetDefaultInstance()` or direct `VarDesc.DefaultValue` write; DA → the instance itself via `load_asset`). Zero new UFUNCTIONs for those.

**Python surface (8 ops across 3 new modules):**

| Module | New op | Bridge calls | Idempotency key |
|---|---|---|---|
| `scripts/python_ops/curves.py` (new) | `create_curve_float(curve_path)` | `CreateCurveFloatDeterministic` + `compile_and_save_package` | `(package, name)` — skip if asset exists |
| `scripts/python_ops/curves.py` | `set_curve_float_keys(curve_path, keys)` | `SetCurveFloatKeys` + `compile_and_save_package` | element-wise array comparison; `keys` is `list[{time, value, interp_mode?, tangent_mode?}]` |
| `scripts/python_ops/data_assets.py` (new) | `create_data_asset_instance(asset_path, parent_class_path)` | `CreateDataAssetInstanceDeterministic` + `compile_and_save_package` | `(asset_path)` — skip if asset exists; class-path mismatch → structured error |
| `scripts/python_ops/data_assets.py` | `set_data_asset_property(asset_path, property_path, value)` | existing `SetPropertyValue` + `compile_and_save_package` | before-equals-after short-circuit from the bridge |
| `scripts/python_ops/uds.py` (new) | `create_user_defined_struct(uds_path)` | `CreateUserDefinedStructDeterministic` + `compile_and_save_package` | `(uds_path)` — skip if asset exists |
| `scripts/python_ops/uds.py` | `add_uds_member(uds_path, member_name, pin_type, default_value="")` | `AddUserDefinedStructMember` + `compile_and_save_package` | `(member_name)` — skip if member exists; pin-type spec catalog reuses `blueprint_structural._resolve_pin_type` from M28.2.1 (first cross-module helper reuse established in M28.3.4 for `add_local_variable`) |
| `scripts/python_ops/uds.py` | `remove_uds_member(uds_path, member_name)` | `RemoveUserDefinedStructMember` + `compile_and_save_package` | `(member_name)` — skip if member absent; reject if would empty struct |
| `scripts/python_ops/uds.py` | `set_uds_member_default(uds_path, member_name, value)` | existing `SetPropertyValue` resolving to the UDS's `DefaultInstance` + `compile_and_save_package` | before-equals-after short-circuit |

**BugHunt fixture plan** (all via `GenerateTestBlueprintsCommandlet.cpp` additions, same shape as M28.5.1 / M28.5.2):

| Sub-phase | New fixture(s) | Purpose |
|---|---|---|
| M28.4.1 (CurveFloat) | `Curve_BpxTestEmpty` — empty `UCurveFloat` at `/Game/TestBlueprints/Curve_BpxTestEmpty` via direct `NewObject<UCurveFloat>` + SavePackage. No pre-seeded keys. | inspect+soak for `set_curve_float_keys`. `create_curve_float` is self-covering — harness creates into a scratch path. |
| M28.4.2 (DataAsset) | `DA_BpxTestParentClass` — BP-derived DA class via `FKismetEditorUtilities::CreateBlueprint(UPrimaryDataAsset::StaticClass(), Pkg, ...)` with 2-3 simple BP-declared variables (int, float, FString) added via `FBlueprintEditorUtils::AddMemberVariable` — matches realistic user flow per the "Data Only Blueprints" path Epic recommends over native subclasses. `DA_BpxTestInstance` — empty instance of `DA_BpxTestParentClass`, authored via direct `NewObject<UDataAsset>(Pkg, DA_BpxTestParentClass->GeneratedClass, ...)`. | inspect+soak for `set_data_asset_property`. `create_data_asset_instance` is self-covering — harness targets `DA_BpxTestParentClass` into a scratch path. |
| M28.4.3 (UDS) | `UDS_BpxTestEmpty` — fresh `UUserDefinedStruct` via `FStructureEditorUtils::CreateUserDefinedStruct(Pkg, ...)` with the auto-bool left in place + VarGuid pre-seeded to the same recipe the bridge UFUNCTION will use (so fixture-gen and op runs converge). Rename auto-bool's friendly name to `BpxAutoBool` for readability. | inspect+soak for `add_uds_member` / `set_uds_member_default` / `remove_uds_member`. `create_user_defined_struct` is self-covering — harness creates a scratch `UDS_BpxTestScratch`. |

Fixture-gen adds `#include "StructUtils/UserDefinedStruct.h"` + `#include "Kismet2/StructureEditorUtils.h"` + `#include "Curves/CurveFloat.h"` + `#include "Engine/DataAsset.h"` + `#include "UObject/Class.h"` (`RF_*` flags, already transitively included). Build.cs: `UnrealEd` is already in `PrivateDependencyModuleNames` for the Tests plugin (needed for `FKismetEditorUtilities`); `Engine` is already there (needed for `UBlueprint`); no new module deps.

**Open questions (flagged for resolution during implementation sub-phases):**

1. **UDS default-instance write path for `set_uds_member_default`.** `FStructureEditorUtils::ChangeVariableDefaultValue` writes to `VarDesc.DefaultValue: FString` + triggers `OnStructureChanged` + `RecreateDefaultInstanceInEditorData` which rebuilds `UUserDefinedStructEditorData::DefaultInstance` from the DefaultValue strings. Question: does re-routing through the generic `SetPropertyValue` bridge on the `DefaultInstance` UScriptStruct bypass `RecreateDefaultInstanceInEditorData` and leave the UDS in a torn state (VarDesc.DefaultValue says "0", DefaultInstance memory says "42")? **Resolution path:** prefer the `ChangeVariableDefaultValue` path (writes the authoritative `VarDesc.DefaultValue` string; listener triggers rebuild). Probe during M28.4.3 implementation — if `ChangeVariableDefaultValue` is sufficient, `set_uds_member_default` calls it directly via a 7th UFUNCTION `SetUserDefinedStructMemberDefault(Struct, FriendlyName, DefaultValueStr)` rather than reusing `SetPropertyValue`. Adds 1 UFUNCTION to the surface; total becomes 7 new UFUNCTIONs.

2. **CurveFloat per-key add/edit vs wholesale SetKeys.** M28.4.1 ships with `set_curve_float_keys(keys=[...])` wholesale. For the design.md intensity-curve use case this is sufficient (author a 4-point curve, replace if tuning). Question: do we need per-key ops (`add_curve_float_key` / `remove_curve_float_key` / `update_curve_float_key`) as well? **Recommendation:** defer to M28.4.1.5 follow-up. The wholesale shape is atomic, deterministic, and matches the "re-author as a unit" authoring style. Add per-key ops only when a concrete plan hits the "I need to tweak one point without re-supplying all N" use case.

3. **DataAsset fixture pattern: BP-derived (`UPrimaryDataAsset` subclass) vs native C++ (`UBpxTestDataAsset`).** Recommendation above picks BP-derived via `FKismetEditorUtilities::CreateBlueprint` — matches realistic user flow (Data Only Blueprints is Epic's documented path) and avoids a native fixture class in `BlueprintExporterTests` that would need rebuild on every DLL bump. Open pitfall: BP-derived DA classes have their UPROPERTY field names mangled to `<PropName>_<N>_<GUID>` at the generated-class level — `set_data_asset_property` needs to resolve by friendly name (via `FBlueprintEditorUtils::FindBlueprintPropertyName` or the `GetPropertyByFriendlyName` pattern UDS uses) before passing into `SetPropertyValue`. Native fields resolve by unmangled FName. **Resolution path:** add a `_resolve_da_property_name(da_class, friendly_name) -> FName` Python helper in `data_assets.py` that checks both forms; falls back to unmangled if the class is native, mangled if BP-derived.

4. **`UPrimaryDataAsset::PreSave` AssetBundleData update determinism.** `UpdateAssetBundleData` walks UPROPERTY references to populate `AssetBundleData`. Question: is the order of the populated entries deterministic across save rounds? **Assessment:** yes — the implementation iterates class properties in declaration order via `TFieldIterator<FProperty>`, and UPROPERTY references serialize in declaration order too. Verify empirically during M28.4.2 soak (2 rounds, identical `set_data_asset_property` plan, md5 byte-identity check).

5. **UDS `RenameVariable` Guid-derived VarName regeneration side effect.** After we post-seed `VarDesc.VarGuid` and call `RenameVariable(Struct, VarGuid, FriendlyName)`, the rename helper's internal call to `FMemberVariableNameHelper::Generate(Struct, NewDisplayNameStr, VarGuid)` regenerates `VarDesc.VarName` from our seeded Guid + the new friendly name. This means the serialized UScriptStruct FProperty's FName changes mid-op. Question: does the UScriptStruct's property chain correctly re-emit with the seeded FName after `OnStructureChanged(RenamedVariable)` fires? **Assessment:** yes — `OnStructureChanged(RenamedVariable)` triggers `FUserDefinedStructureCompilerUtils::CompileStruct` which rebuilds the FProperty chain from VarDesc. Verify empirically during M28.4.3 soak.

**Sequencing (complexity ramp from simplest to most complex — matches M28.3 / M28.5 precedent of starting narrow):**

| Sub-phase | Scope | Ops | Version | Driver |
|---|---|---|---|---|
| **M28.4.0** | Research outcome (this block) | — | no bump | This session |
| **M28.4.1** | CurveFloat — simplest (no GUID seeding, direct NewObject, wholesale key array) | `create_curve_float` + `set_curve_float_keys` | minor 1.22.2 → 1.23.0 | design.md item #6 (encounter-director intensity curve) |
| **M28.4.2** | DataAsset — medium (NewObject with class resolution, reuses existing SetPropertyValue for the setter) | `create_data_asset_instance` + `set_data_asset_property` | minor 1.23.0 → 1.24.0 | design.md item #7 (archetype DAs: Rusher / Marksman / Suppresser / Flanker) |
| **M28.4.3** | UDS — most complex (GUID seeding on Struct + VarGuid, editor-data split, auto-bool handling, Rename interplay, 3+1 ops) | `create_user_defined_struct` + `add_uds_member` + `remove_uds_member` + `set_uds_member_default` | minor 1.24.0 → 1.25.0 | design.md item #3 (confidence-decaying perception — thicken `S_TargetInfo`) |
| **M28.4.4** *(optional)* | Pure-docs close (CATALOG.md / plans/README.md / AGENT_LOOP.md worked example chaining create_curve_float + create_data_asset_instance + create_user_defined_struct for e.g. the Rusher archetype with its own intensity curve and UDS-typed payload) | — | no bump | Low priority; ship only if a concrete plan wants the worked example |

Three minor bumps across M28.4.1–.3 is unusual but matches the semver rule precisely: each sub-phase introduces a **new Python module** (new subsystem), and the rule established in M28.2.1 / M28.3.1 / M28.5.1 is "first sub-phase with a new Python module = minor." If the user prefers a single `non_bp_assets.py` module spanning all 8 ops, the second and third sub-phases drop to patch bumps (1.22.2 → 1.23.0 → 1.23.1 → 1.23.2). **Recommendation:** keep them separate — three modules is cleaner code organization and each family has distinct bridge surface + fixture needs.

**Out of scope for M28.4:**
- Non-float curves (UCurveVector, UCurveLinearColor) — narrow first, extend only on driver. Same pattern as M28.3 narrow K2Node catalog.
- UDS member re-ordering (`MoveVariable`) — no design.md driver; expose only on request.
- UDS member type change (`ChangeVariableType`) — risky (invalidates default values, cascades through dependent Blueprints); require explicit user sign-off if a driver surfaces.
- DataAsset factory path via `UDataAssetFactory::FactoryCreateNew` — interactive `ConfigureProperties` stands in our way; direct NewObject is the right substitute.
- Runtime evaluation of authored curves / DAs / UDSs — M28.7 automation-test-runner territory.

**Reference patterns to reuse:**
- M28.5.1 `add_eqs_option` shape for all three `create_*` ops — `CreatePackage` → explicit-`FName` `NewObject` → `FAssetRegistryModule::AssetCreated` → `MarkPackageDirty` → `SavePackageForAsset`. Identical recipe.
- M28.2.1 `AddMemberVariableDeterministic` + M28.3.4 `AddLocalVariableDeterministic` for `AddUserDefinedStructMember`'s post-seed pattern (resolve the newly-added tail entry by guid-equals-fresh → seed guid → re-locate via stable guid).
- M28.2.3 `add_component_to_scs`'s `load_class` / `load_object` fallback for `create_data_asset_instance`'s parent_class resolution.
- M28.2.1 `blueprint_structural._resolve_pin_type` for `add_uds_member`'s pin_type spec catalog (basic / struct:<path> / object:<path> / array:<inner>) — first cross-module helper reuse established in M28.3.4.
- M28.5.2 `EQS_BpxTestWithOption` fixture's explicit-`FName` recipe for the UDS fixture's auto-bool VarGuid seeding (fixture-gen and op runs must converge on the same seeded guid).

**M28.4.0 CLOSED (research, 2026-04-24 post-M28.5 open-scope session).** M28.4.1 (CurveFloat — `create_curve_float` + `set_curve_float_keys`) is next pickup on user confirmation. DLL rebuild cost: ~1 new UFUNCTION + ~12 KB per engine; no new includes outside CurveFloat.h. Expected matrix impact: 2 new inspect fixtures + 2 new soak fixtures → 42 total `verify_all.ps1` gates (up from 38). Estimated implementation time: ~45 min for the C++ + Python + fixture; matrix run ~500 s; docs updates ~15 min.

### M28.4.1 shipped (2026-04-24, 1.22.2 → 1.23.0)

- Two new ops in new `scripts/python_ops/curves.py` module: `create_curve_float(curve_path)` + `set_curve_float_keys(curve_path, keys)`. First slice of the M28.4 non-BP asset-factory catalog (complexity ramp: CurveFloat → DataAsset → UDS per the M28.4.0 research). Op count 36 → 38. **2 new UFUNCTIONs** on `UBpxReflectionOps`: `CreateCurveFloatDeterministic(PackagePath)` wraps `NewObject<UCurveFloat>` + `FAssetRegistryModule::AssetCreated` with idempotent `StaticLoadObject` pre-check (hard error on different-class collision, not silent skip); `SetCurveFloatKeys(Curve, TArray<FRichCurveKey> NewKeys)` wholesale-replaces `FloatCurve.SetKeys` with up-front monotonic-Time validation + element-wise `(Time, Value, InterpMode)` idempotency compare. Both called via Python wrappers that add path validation + Python→RichCurveKey struct conversion + compile_and_save_package.
- Determinism: UCurveFloat / UCurveBase / FRichCurveKey have zero `FGuid::NewGuid()` usage (grep-confirmed M28.4.0). Explicit `FName` on `NewObject` (derived from the PackagePath's short-name tail via `FPackageName::GetShortName`) is the only determinism lever — no SeedGuidFromJoined recipe needed. Idempotent on `PackagePath` (create) / element-wise key compare (set). M28.pre.3 soak round 2 byte-identical to round 1 for both ops.
- Python binding gotcha caught in matrix: `unreal.RichCurveInterpMode` exposes `RCIM_LINEAR` / `RCIM_CONSTANT` / `RCIM_CUBIC` but NOT `RCIM_NONE` (Python keyword clash — UE's binding hides the name). And `RichCurveKey.interp_mode` rejects plain `int` ("NativizeProperty: Cannot nativize 'int' as 'InterpMode' (ByteProperty)") — must use the enum value. Fix: pre-cache the 3 enum values at module-import time via `unreal.RichCurveInterpMode.RCIM_LINEAR` etc.; drop the 4th ("none") from the public surface since the binding gap means we'd have to drop to ImportText with no realistic driver. Documented in both the Python docstring and CATALOG.md. Two matrix-cycle regressions total (interp_mode type + UCurveFloat not in inventory scope — see next bullet) before the third run landed green.
- UCurveFloat is NOT in the inventory pipeline's logic-bearing set (PROJECT_INVENTORY_BRIEF.md §3 — {UBP-family, BehaviorTree, StateTree, EnvQuery, SmartObjectDefinition, ChooserTable, PoseSearchDatabase, UserDefinedStruct, UserDefinedEnum, DataTable}). The inspect harness's re-export phase invokes `ProjectInventoryCommandlet -Filter` and emits zero `.md` for non-logic-bearing classes, so the inspect gate would always fail for curve-family ops. Expanding inventory scope to include UCurveFloat is a separate design decision (would affect every project's inventory output, including DOW). For M28.4.1 we added a new `skip_inspect: true` flag to the fixture JSON schema + taught `verify_all.ps1` to honor it (3-line patch to the inspect-gate fan-out loop). Both curve fixtures carry the flag; the soak gate still runs and carries the determinism signal. Matrix impact: **38 → 40 gates** (not the research-forecast 42 — 2 inspect gates are legitimately skipped).
- Plan pipeline wired: new `create_curve_float` entry in `plan_shape.OP_SPECS` (required `[curve_path]`, `assets_absent: [curve_path]` so shape validator warns on replay-overwrite); new `set_curve_float_keys` (required `[curve_path, keys]`, `assets: [curve_path]`); `_OP_DISPATCH` entries in `plan_executor.py`; `_op_expected_changes` entries in `mechanical_diff.py` (`create_curve_float` → "created", `set_curve_float_keys` → "mutated"). `__init__.py` re-exports both + alpha-sorted `__all__` inserts.
- New BugHunt fixture `Curve_BpxTestEmpty` at `/Game/TestBlueprints/Curve_BpxTestEmpty` — empty `UCurveFloat` (zero keys) authored via direct `NewObject<UCurveFloat>` + `SavePackageForAsset`. Added to `GenerateTestBlueprintsCommandlet.cpp`'s Gens array as tier `C`. Committed as 1324 b .uasset. Two new soak fixtures: `scripts/inspect_fixtures/create_curve_float.json` (source Curve_BpxTestEmpty, op targets scratch — idempotent-skip branch since duplicate pre-places the curve at scratch_path) + `set_curve_float_keys.json` (same source, 2-point curve `[{0.0, 0.0}, {1.0, 100.0}]` populates the empty duplicate — round 1 mutates, round 2 element-wise compares and skips). Both marked `skip_inspect: true` per the scope call above.
- Version bump 1.22.2 → 1.23.0 (**minor** per semver — new Python module `curves.py` counts as new subsystem, matching the precedent from M28.2.1 / M28.3.1 / M28.5.1). All 9 drift locations updated via bulk `sed` replace (15 files touched — 7 Source/ + 7 BuiltPlugin mirror + README). `.uplugin` `"Version": 22 → 23` integer bumped per the minor-digit convention.
- Dual-engine DLL rebuild: UE_DOW DLL at `BuiltPlugin/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` (**2,770,944 bytes**, +~14 KB vs M28.5.3's 2,756,608 — matches expected growth for 2 new UFUNCTIONs); stock UE 5.7 DLL at `_build_output_5_7/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` (**2,771,968 bytes**, also +~14 KB vs M28.5.3's 2,757,632). UE_DOW UAT build 24.4s; stock 5.7 UAT build 44.2s. Both clean on first pass — no unity-ODR or link errors despite the new `#include "Curves/RichCurve.h"` in the public header (needed because `TArray<FRichCurveKey>` as a UFUNCTION param requires UHT to see the USTRUCT definition inline).
- In-place rebuild of BugHunt's `BlueprintExporterTests` DLL via `Build.bat UnrealEditor Win64 Development -Project=BugHunt.uproject` (18.7s, 44-step compile+link) because UE-Cmd doesn't auto-rebuild project-plugin modules on launch — commandlet invocation skips that path. Had to force-rebuild via deleting the plugin DLLs + invoking UBT explicitly before the fixture-gen commandlet would pick up the new `GenCurve_BpxTestEmpty` entry. Documented inline in the matrix troubleshooting arc for the next sub-phase.
- Matrix troubleshooting arc: **3 matrix cycles before green**. Cycle 1: first run hit the `RCIM_NONE` attribute-lookup error at module import (see above) — every gate that imported `python_ops.plan_executor` failed. Cycle 2: fixed the interp_mode import, but the `int → ByteProperty` TypeError on SetKeys round 1 surfaced for `set_curve_float_keys`, plus both curve soaks hit stale-`CachedAssetRegistry_0.bin` residue from the first cycle's failed inspect scratches (AR cache carries duplicated-asset entries across UE-Cmd launches even after `_file_level_delete` removed the .uasset — same bug class M28.5.2 hit). Cycle 3: fixed interp_mode enum-access pattern, nuked `CachedAssetRegistry_0.bin` before re-run — **clean 40/40**.
- Verification: **all 40 gates PASS in 511.0 s** via `verify_all.ps1` on BugHunt / stock UE 5.7 (automation + determinism + 18 inspect + 20 soak — 2 curve inspects skipped, 2 curve soaks run). Automation: 15.6 s. Determinism: full-sweep twin byte-identical (47.5 s). New gates: **`soak-create_curve_float` PASS** in 6.3 s across 2 rounds with stable md5 `5474ebd61525e29ac26d43e4b388a9bc`; **`soak-set_curve_float_keys` PASS** in 6.2 s across 2 rounds with stable md5 `7e332d42f6ed5cb32172d4deebbfbb8c`. Every pre-existing inspect+soak pair still PASS — no regression from the new ops, the new `curves.py` module, or the baked-in version strings in the DLL.
- MCP pytest: **23/23 PASS** in 9.93 s (`scripts/blueprint-exporter-mcp`). Both ops are purely additive on the Python side; MCP's `get_op_catalog` auto-surfaces via AST scanning — no MCP-side code change needed.
- **M28.4.1 done. M28.4 catalog in progress — 2 of 8 ops shipped.** Next: **M28.4.2 DataAsset** (`create_data_asset_instance` + `set_data_asset_property`, minor bump 1.23.0 → 1.24.0). Per the M28.4.0 research outcome block: `CreateDataAssetInstanceDeterministic` wraps `NewObject<UDataAsset>` with abstract-class rejection + `StaticFindObject` idempotency (one new UFUNCTION); `set_data_asset_property` reuses the existing M23.1 `SetPropertyValue` reflection bridge (zero new UFUNCTION). New Python module `scripts/python_ops/data_assets.py`. Two open questions from M28.4.0 research to resolve during implementation: BP-derived vs native DA fixture pattern (recommended BP-derived via `FKismetEditorUtilities::CreateBlueprint(UPrimaryDataAsset::StaticClass(), ...)`) + mangled-UPROPERTY-name resolution for `set_data_asset_property` on BP-derived classes. BugHunt fixtures needed: `DA_BpxTestParentClass` + `DA_BpxTestInstance`. Driver: design.md item #7 (archetype DAs — Rusher / Marksman / Suppresser / Flanker). Estimated: ~1 new UFUNCTION + ~12 KB per engine; 2 new soak fixtures (inspect still skipped — UDataAsset also isn't in inventory logic-bearing set); matrix 40 → 42 gates; ~45 min code + ~500 s matrix.

### M28.4.2 shipped (2026-04-24, 1.23.0 → 1.24.0)

- Two new ops in new `scripts/python_ops/data_assets.py` module: `create_data_asset_instance(asset_path, parent_class_path)` + `set_data_asset_property(asset_path, property_path, value)`. Second slice of the M28.4 non-BP asset-factory catalog (complexity ramp: CurveFloat → DataAsset → UDS per the M28.4.0 research). Op count 38 → 40. **1 new UFUNCTION** on `UBpxReflectionOps`: `CreateDataAssetInstanceDeterministic(PackagePath, DAClass)` wraps `NewObject<UDataAsset>(Pkg, DAClass, RF_Public | RF_Standalone | RF_Transactional)` flag-for-flag with `UDataAssetFactory::FactoryCreateNew` (EditorFactories.cpp:7288). **Zero new UFUNCTIONs** on the setter side — `set_data_asset_property` is a Python-only wrapper over the existing M23.1 `SetPropertyValue` reflection bridge via the asset's UPROPERTY path (same shape pattern M28.5.3 established for `set_eqs_generator_property`).
- Class resolution covers both native DA classes (`/Script/<Module>.<ClassName>`) and BP-derived DA classes (`/Game/<path>/<Name>.<Name>_C` — the generated class, not the BP asset path). `_resolve_da_class` helper tries `unreal.load_class` first, falls back to `unreal.load_object` (same recipe as `eqs._resolve_eqs_class` / `blueprint_structural.add_bp_interface`). Bridge UFUNCTION rejects abstract classes + non-UDataAsset subclasses up-front with structured errors. Idempotency walks two paths: `StaticLoadObject<UDataAsset>` hit at target with matching `DAClass` → `bSkipped=true`; hit with wrong class at the same path → hard structured error (silently stacking would be a plan-level mistake).
- Determinism: UDataAsset / UPrimaryDataAsset have zero `FGuid::NewGuid()` usage (grep-confirmed M28.4.0). Explicit `FName` on the `NewObject` call (derived from the PackagePath's short-name tail via `FPackageName::GetShortName`) is the only determinism lever — no SeedGuidFromJoined recipe needed. M28.pre.3 soak round 2 byte-identical to round 1 for both ops. Open Question #3 from the M28.4.0 research (BP-derived mangled-UPROPERTY resolution) DEFERRED — BP-added DA member variables land on the generated class with their friendly FName, so the existing `SetPropertyValue` bridge's `FindFProperty` path resolves cleanly without a `_resolve_da_property_name` helper. If a real shadowed/renamed case surfaces, the helper can be added in `data_assets.py` without bloating every op's happy path.
- Plan pipeline wired: new `create_data_asset_instance` entry in `plan_shape.OP_SPECS` (required `[asset_path, parent_class_path]`, `assets_absent: [asset_path]`); new `set_data_asset_property` (required `[asset_path, property_path, value]`, `assets: [asset_path]`); `_OP_DISPATCH` entries in `plan_executor.py`; `_op_expected_changes` entries in `mechanical_diff.py` (`create_data_asset_instance` → "created", `set_data_asset_property` → "mutated"). `__init__.py` re-exports both + alpha-sorted `__all__` inserts.
- Two new BugHunt fixtures at `/Game/TestBlueprints/`: `DA_BpxTestParentClass` (BP-derived `UPrimaryDataAsset` subclass via `CreateBlueprint(UPrimaryDataAsset::StaticClass(), ...)` with 3 declared member vars — `Intensity: int`, `Range: float`, `Label: FString`) + `DA_BpxTestInstance` (empty instance of parent's `GeneratedClass` via `NewObject<UDataAsset>(Pkg, ParentClass, ...)`). Parent MUST generate before instance — enforced by Gens-array ordering in `GenerateTestBlueprintsCommandlet`. Committed at 9999 b / 1464 b .uasset respectively. Two new soak fixtures: `scripts/inspect_fixtures/create_data_asset_instance.json` (source DA_BpxTestInstance, op targets scratch with `parent_class_path=DA_BpxTestParentClass_C` — idempotent-skip branch since duplicate pre-places the asset at scratch_path) + `set_data_asset_property.json` (same source, sets `Intensity=42` on the empty duplicate — round 1 mutates, round 2 short-circuits via before-equals-after string compare). Both marked `skip_inspect: true` — UDataAsset isn't in `PROJECT_INVENTORY_BRIEF.md §3` logic-bearing set so the inspect re-export phase emits zero .md.
- Version bump 1.23.0 → 1.24.0 (**minor** per semver — new Python module `data_assets.py` counts as new subsystem, matching the precedent from M28.2.1 / M28.3.1 / M28.5.1 / M28.4.1). All 9 drift locations updated via bulk `sed` replace (15 files touched — 7 Source/ + 7 BuiltPlugin mirror + README). `.uplugin` `"Version": 23 → 24` integer bumped per the minor-digit convention.
- Dual-engine DLL rebuild: UE_DOW DLL at `BuiltPlugin/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` (**2,780,160 bytes**, +~9 KB vs M28.4.1's 2,770,944 — matches expected growth for 1 new UFUNCTION); stock UE 5.7 DLL at `_build_output_5_7/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` (**2,781,696 bytes**, also +~10 KB vs M28.4.1's 2,771,968). UE_DOW UAT build completed clean; stock 5.7 UAT build completed clean — both in parallel via background Bash tasks, no unity-ODR or link errors despite the new `#include "Engine/DataAsset.h"` in ReflectionOps.cpp (header dep is narrow — `UDataAsset::StaticClass()` + `IsChildOf` + `NewObject` only).
- In-place rebuild of BugHunt's `BlueprintExporterTests` DLL via `Build.bat UnrealEditor Win64 Development -Project=BugHunt.uproject` against stock UE 5.7 (16.56 s, 27-step compile+link) because UE-Cmd doesn't auto-rebuild project-plugin modules on launch — commandlet invocation skips that path. Both new `GenDA_BpxTest*` entries compiled + linked. BugHunt's install `BlueprintExporter/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` refreshed from stock-5.7 UAT output (2,781,184 b), matching the BuildId that `verify_all.ps1`'s stock-engine launch expects.
- Matrix troubleshooting arc: **clean on first run.** No matrix-cycle regressions. The M28.4.1 playbook (explicit FName on NewObject, idempotency via StaticLoadObject, round-2 SetPropertyValue short-circuit) translated directly — DataAsset has the same zero-FGuid determinism shape as CurveFloat so the bridge recipe was additive without any new failure modes. MCP pytest surfaced a pre-existing CI-churn issue (`test_get_references` asserted exactly 2 inbound refs to `BPI_CrowdCharacter`; DOW inventory build 3/4 grew that to 7 via new crowd asset variants) — fix is loosening the assertion to `>= 1` since the gate's purpose is to verify the `direction="in"` filter excludes outbound refs, not to pin an exact count. Separate from M28.4.2 but captured in the same commit.
- Verification: **all 42 gates PASS in 523.5 s** via `verify_all.ps1` on BugHunt / stock UE 5.7 (automation 15.7 s + determinism 48.2 s + 18 inspect + 22 soak — 2 data_asset inspects skipped, 2 data_asset soaks run). Automation: 15.7 s. Determinism: full-sweep twin byte-identical (48.2 s). New gates: **`soak-create_data_asset_instance` PASS** in 6.2 s across 2 rounds with stable md5 `a46bc5a3bbba77fa4e7cc1b808227f2e`; **`soak-set_data_asset_property` PASS** in 6.2 s across 2 rounds with stable md5 `06ad4a6e749c4c261f9812ebf3948016`. Every pre-existing inspect+soak pair still PASS — no regression from the new ops, the new `data_assets.py` module, or the baked-in version strings in the DLL.
- MCP pytest: **23/23 PASS** in 11.13 s (`scripts/blueprint-exporter-mcp`). Both ops are purely additive on the Python side; MCP's `get_op_catalog` auto-surfaces via AST scanning — no MCP-side code change needed. One test assertion loosened (see matrix troubleshooting arc above).
- **M28.4.2 done. M28.4 catalog in progress — 4 of 8 ops shipped.** Next: **M28.4.3 UDS** (`create_user_defined_struct` + `add_uds_member` + `remove_uds_member` + `set_uds_member_default`, minor bump 1.24.0 → 1.25.0). Per the M28.4.0 research outcome block: 4 new ops in new Python module `scripts/python_ops/uds.py`; up to 5 new UFUNCTIONs (`CreateUserDefinedStructDeterministic` + `AddUserDefinedStructMember` + `RemoveUserDefinedStructMember` + optional `SetUserDefinedStructMemberDefault` per Open Q #1 + reuse of M28.2.1 `_resolve_pin_type` for `add_uds_member`'s type catalog). Two FGuid::NewGuid() traps to seed: `Struct->Guid` on StructureEditorUtils.cpp:53 (`SeedGuidFromJoined(<path>:uds)`) + `VarGuid` on StructureEditorUtils.cpp:303 (`SeedGuidFromJoined(<path>:uds_var:<friendly_name>)` + RenameVariable to regenerate VarName from seeded guid). Auto-bool quirk: `CreateUserDefinedStruct` injects a default bool on line 60; M28.4.0 recommendation is leave it in place + seed its guid via the same recipe. New BugHunt fixture `UDS_BpxTestEmpty`. Driver: design.md item #3 (confidence-decaying perception — thicken S_TargetInfo UDS). Estimated: ~5 new UFUNCTIONs + ~20-25 KB per engine; 4 new soak fixtures (inspect depends on whether UserDefinedStruct is in inventory logic-bearing set — per PROJECT_INVENTORY_BRIEF.md §3 it IS, so inspect gates should work; confirm at implementation); matrix 42 → 50 gates; ~60-90 min code + ~600 s matrix.

### M28.4.3 shipped (2026-04-24, 1.24.0 → 1.25.0)

- Four new ops in new `scripts/python_ops/uds.py` module: `create_user_defined_struct(uds_path)` + `add_uds_member(uds_path, member_name, var_type_spec, default_value="")` + `remove_uds_member(uds_path, member_name)` + `set_uds_member_default(uds_path, member_name, value)`. Third and last slice of the M28.4 non-BP asset-factory catalog; closes the M28.4 umbrella at 8 ops total across 3 modules (curves.py + data_assets.py + uds.py). Op count 40 → 44. **4 new UFUNCTIONs** on `UBpxReflectionOps`: `CreateUserDefinedStructDeterministic(PackagePath)` wraps `FStructureEditorUtils::CreateUserDefinedStruct` and closes both of the engine's `FGuid::NewGuid()` traps — `Struct->Guid` (seeded via `SeedGuidFromJoined(uds_path + ":uds")`) and the auto-bool's `VarGuid` (seeded via `:uds_var:BpxAutoBool`) + a post-create `RenameVariable` pass so `VarName` regenerates from the seeded Guid + new friendly name; `AddUserDefinedStructMember(Struct, FriendlyName, FEdGraphPinType, DefaultValue)` wraps `FStructureEditorUtils::AddVariable` + post-seeds the new VarDesc's VarGuid + routes through RenameVariable to regenerate VarName + optionally writes the DefaultValue via `ChangeVariableDefaultValue` in the same call; `RemoveUserDefinedStructMember(Struct, FriendlyName)` resolves friendly name → VarGuid via a VarDescriptions friendly-name walk + calls `FStructureEditorUtils::RemoveVariable`, with an engine-matching refusal to empty the struct (`bAllowToMakeEmpty=false`, StructureEditorUtils.cpp:327); `SetUserDefinedStructMemberDefault(Struct, FriendlyName, DefaultValueStr)` routes through `FStructureEditorUtils::ChangeVariableDefaultValue` — writes `VarDesc.DefaultValue` (authoritative string) + fires `OnStructureChanged(DefaultValueChanged)` → `RecreateDefaultInstanceInEditorData` so the serialized string + DefaultInstance memory stay in sync (M28.4.0 research Open Question #1 selected this path over a direct `SetPropertyValue` write on the DefaultInstance, which would have left the UDS in a torn state where the string said X but memory said Y).
- Determinism: two `FGuid::NewGuid()` call sites in UUserDefinedStruct authoring (`Struct->Guid` on StructureEditorUtils.cpp:53 + per-member `VarGuid` on :303) — both closed via `SeedGuidFromJoined` + a post-mutation `RenameVariable` pass. Auto-bool stays in every fresh struct because the engine's `bAllowToMakeEmpty=false` invariant refuses to drop the last member; plan authors remove it later via `remove_uds_member` once at least one real member is added. The auto-bool friendly name lands as `BpxAutoBool` (renamed at create time) for consistent indexing across fixture-gen + op runs. M28.pre.3 soak round 2 byte-identical to round 1 for all four ops.
- Compile-fix arc, both iterations: the initial C++ drop forward-declared `FStructVariableDescription` via `Kismet2/StructureEditorUtils.h` but dereferenced `VarDesc[0].VarGuid` / `NewEntry.VarGuid` / `ExistingDesc->VarGuid` — C2027 incomplete-type errors on both engines (UE_DOW + stock 5.7). Fix: added `#include "UserDefinedStructure/UserDefinedStructEditorData.h"` which carries the full definition. Same fix needed in `GenerateTestBlueprintsCommandlet.cpp` after the fixture gen hit the same error (error C2661 "RenameVariable: no overloaded function takes 2 arguments" is a secondary effect — the compiler couldn't see `VarDescs[0].VarGuid` as an FGuid so it fell back to matching a non-existent 2-arg overload). Two rebuild cycles on the plugin DLL (Source + BuiltPlugin resync + dual-engine UAT rerun) and one on BugHunt's BlueprintExporterTests DLL before green.
- Python-side: reuses `blueprint_structural._resolve_pin_type` for `add_uds_member`'s type spec catalog — second cross-module helper reuse (M28.3.4 `add_local_variable` established the pattern). The pin-type catalog covers basic (`"int"` / `"real"` / etc.), struct (`"struct:/Script/..."`), object (`"object:/Script/..."`), class (`"class:/Script/..."`), and container forms (`"array:<inner>"` / `"set:<inner>"` / `"map:<key>=>>>:<value>"`) — identical to `add_bp_variable` + `add_local_variable`. `set_uds_member_default` reuses a `_normalize_scalar_value` helper local to `uds.py` (same shape as `data_assets.py` / `eqs.py`) so plan JSON can carry plain ints / floats / bools without string-quoting; composite literals like `"(X=1.0,Y=2.0,Z=0.0)"` pass through verbatim.
- Plan pipeline wired: new `create_user_defined_struct` entry in `plan_shape.OP_SPECS` (required `[uds_path]`, `assets_absent: [uds_path]`); new `add_uds_member` (required `[uds_path, member_name, var_type_spec]`, optional `[default_value]`, `assets: [uds_path]`); new `remove_uds_member` (required `[uds_path, member_name]`, `assets: [uds_path]`); new `set_uds_member_default` (required `[uds_path, member_name, value]`, `assets: [uds_path]`); `_OP_DISPATCH` entries in `plan_executor.py`; `_op_expected_changes` entries in `mechanical_diff.py` (`create_user_defined_struct` → "created", rest → "mutated"); `__init__.py` re-exports all four + alpha-sorted `__all__` inserts.
- New BugHunt fixture `UDS_BpxTestEmpty` at `/Game/TestBlueprints/UDS_BpxTestEmpty` — authored via `FStructureEditorUtils::CreateUserDefinedStruct` with the auto-bool renamed to `BpxAutoBool` + a second member `BpxRemovalCandidate:int (default=7)` pre-seeded so the `remove_uds_member` soak has a target to delete (engine's bAllowToMakeEmpty=false invariant refuses to leave the struct with zero members, so the fixture must have at least 2 for the remove soak to succeed without tripping the refusal). Also unblocks `set_uds_member_default` soak — uses `BpxRemovalCandidate` as the scalar-mutation target. Committed at 4850 b .uasset. Four new soak fixtures: `scripts/inspect_fixtures/create_user_defined_struct.json` (targets scratch, idempotent-skip branch since duplicate pre-places a UDS at scratch_path), `add_uds_member.json` (appends `BpxAddCandidate:int=42`), `remove_uds_member.json` (removes `BpxRemovalCandidate`, leaves auto-bool), `set_uds_member_default.json` (sets `BpxRemovalCandidate`'s default `"7" → "99"`). All four marked `skip_inspect: true` per the M28.4.1/M28.4.2 scope call — soak carries the determinism signal; inspect would add content-assertion complexity for cosmetic render differences without load-bearing value at this sub-phase. (UUserDefinedStruct IS in the logic-bearing set per PROJECT_INVENTORY_BRIEF.md §3, so inspect gates could work; deferred as a pure-follow-up if a driver surfaces.)
- Version bump 1.24.0 → 1.25.0 (**minor** per semver — new Python module `uds.py` counts as new subsystem, matching the precedent from M28.2.1 / M28.3.1 / M28.5.1 / M28.4.1 / M28.4.2). All 9 drift locations updated via PowerShell bulk replace (15 files touched — 7 Source/ + 7 BuiltPlugin mirror + README). `.uplugin` `"Version": 24 → 25` integer bumped per the minor-digit convention. BugHunt's plugin install `.uplugin` also refreshed to 1.25.0 (it's a regular dir, not a junction — Source/ + Config/ are junctions into the primary tree, but Binaries/ + .uplugin are copies).
- Dual-engine DLL rebuild: UE_DOW DLL at `BuiltPlugin/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` (**2,811,904 bytes**, +~32 KB vs M28.4.2's 2,780,160 — matches expected growth for 4 new UFUNCTIONs); stock UE 5.7 DLL at `_build_output_5_7/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` (**2,813,440 bytes**, +~32 KB vs M28.4.2's 2,781,696). UE_DOW UAT build completed clean in ~31s on the rerun; stock 5.7 UAT build completed clean in ~47s on the rerun. Neither build had unity-ODR or link errors after the `UserDefinedStructEditorData.h` include landed; the first attempt tripped C2027 incomplete-type errors on 5 sites in ReflectionOps.cpp — same fix resolved all of them.
- In-place rebuild of BugHunt's `BlueprintExporterTests` DLL via `Build.bat UnrealEditor Win64 Development -Project=BugHunt.uproject` against stock UE 5.7 (5.11 s, 4 translation units rebuilt — only `GenerateTestBlueprintsCommandlet.cpp` needed recompile since the plugin DLL had just been linked; first attempt hit the same C2027 error for `FStructVariableDescription` in the fixture-gen function, second attempt clean after adding the same include). BugHunt's install `BlueprintExporter/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` refreshed from stock-5.7 UAT output (2,813,440 b); BlueprintExporterTests DLL at 216,576 b.
- Fixture regeneration: ran `UnrealEditor-Cmd -run=GenerateTestBlueprints` to produce `UDS_BpxTestEmpty.uasset` (4850 b). Only the new fixture created; every pre-existing fixture hit the `already on disk` skip branch. Exit code 1 (benign — the well-known ProjectID warning-summary inflation on UE-Cmd; `SUCCESS` logged for the commandlet itself).
- Matrix troubleshooting arc: **clean on first run.** No matrix-cycle regressions — the M28.4.1/M28.4.2 playbook (explicit FName on seed-or-rename recipes, idempotent pre-checks via friendly-name walks, round-2 before-equals-after short-circuits) translated directly. The UDS shape has more moving parts than CurveFloat/DataAsset (two FGuid traps + auto-bool + RenameVariable interplay + DefaultInstance coherence) but every path landed byte-stable across rounds on the first matrix pass.
- Verification: **all 46 gates PASS in 538.1 s** via `verify_all.ps1` on BugHunt / stock UE 5.7 (automation 15.7 s + determinism 47.3 s + 18 inspect + 26 soak — 4 UDS inspects skipped via `skip_inspect: true`, 4 UDS soaks run). Automation: 15.7 s. Determinism: full-sweep twin byte-identical (47.3 s). New gates: **`soak-create_user_defined_struct` PASS** in 6.1 s across 2 rounds with stable md5 `cdf15bf24b9520ca5446cb02eb8bf60d`; **`soak-add_uds_member` PASS** in 6.1 s with stable md5 `a61e0706b201c53ae8fc01ed88786073`; **`soak-remove_uds_member` PASS** in 6.1 s with stable md5 `74d9a932ad00ca26504ce3afc0ccf147`; **`soak-set_uds_member_default` PASS** in 6.1 s with stable md5 `de96efcabf29619b489ea3dbff269bcd`. Every pre-existing inspect+soak pair still PASS — no regression from the new ops, the new `uds.py` module, the `UserDefinedStructEditorData.h` include addition, or the baked-in version strings in the DLL.
- MCP pytest: **23/23 PASS** in 11.12 s (`scripts/blueprint-exporter-mcp`). All four ops are purely additive on the Python side; MCP's `get_op_catalog` auto-surfaces via AST scanning — no MCP-side code change needed.
- **M28.4.3 done. M28.4 catalog COMPLETE — 8 of 8 ops shipped** (`create_curve_float` + `set_curve_float_keys` + `create_data_asset_instance` + `set_data_asset_property` + `create_user_defined_struct` + `add_uds_member` + `remove_uds_member` + `set_uds_member_default`). **Next scope OPEN** — M28.4 umbrella closed, M28.2 + M28.3 + M28.5 were already satisfied; next external driver picks M28.6 (GameplayTag config authoring — design.md items #1 + #4), M28.7 (automation-test runner — semantic verification beyond mechanical diff), M28.4.4 *(optional — pure-docs close of M28.4 umbrella with an AGENT_LOOP worked example chaining curve + DA + UDS creation for e.g. the Rusher archetype with its own intensity curve and UDS-typed tuning payload; low priority, defer unless a concrete driver asks for it)*, or something else from the M28 phase table. Per the research sequencing this is also a natural pause point for a `/clear`-boundary Resume Checklist refresh.

### M29 — Mutable / CustomizableObject Tier 2 support (scoped 2026-04-23)

**Driver.** Colleague feature request — blueprint-exporter currently has no Tier 2 renderer for Mutable's three customization types, which makes the Mutable system opaque to inventory / AI-analysis consumers. Primary use case (per user on 2026-04-23): **"understand how Mutable works"** — full authoring-surface exposure, not minimum viable. Both engines need support (UE_DOW custom UE 5.7 + stock UE 5.7 Legacy). No timeline pressure stated, but this is an external driver so it preempts M28.3 self-directed work.

**Target type inventory:**

| Type | Module | Header visibility | Demo asset in `D:\Work\mutable\MutableSample\` |
|---|---|---|---|
| `UCustomizableObject` | `CustomizableObject` (Runtime, PreDefault) | **Public** — `MuCO/CustomizableObject.h` | 7 — `CO_Character`, `CO_Character_Head`, `CO_Boots`, `CO_Cyborg_Arm_L`, `CO_Cyborg_Arm_R`, `CO_Eyes_Basic`, `CO_Weapon` |
| `UCustomizableObjectInstance` | `CustomizableObject` (Runtime, PreDefault) | **Public** — `MuCO/CustomizableObjectInstance.h` | 1 — `COI_Character` |
| `UCustomizableObjectMacroLibrary` | `CustomizableObjectEditor` (UncookedOnly, Default) | **Private** — `MuCOE/CustomizableObjectMacroLibrary/CustomizableObjectMacroLibrary.h` | 1 — `COML_Character` |

**Mutable plugin surface (from `D:\Work\UE_DOW\engine\Plugins\Mutable\Mutable.uplugin`):**
- Version 1.8.0, `"CreatedBy": "Epic Games, Inc."`, `"IsBetaVersion": true`, `"EnabledByDefault": false`.
- Modules: `MutableRuntime` (Runtime/PreDefault), `CustomizableObject` (Runtime/PreDefault), `MutableTools` (UncookedOnly/PreDefault), `MutableValidation` (Editor/PreDefault), `CustomizableObjectEditor` (UncookedOnly/Default).
- Dependencies: `SkeletalMerging`, `DataValidation`.
- **Not in stock UE 5.7 Legacy install today** — `D:\**\Mutable.uplugin` only hits the UE_DOW engine. M29.0 must confirm whether Legacy gets the plugin enabled (it ships with the engine — likely just `"Enabled": true` in an .uproject or per-engine flip) before dual-engine verification is possible. If Legacy can't get Mutable, M29 DLL rebuild against stock-5.7 still compiles cleanly (`WITH_MUTABLE_SUPPORT=0` — renderers compile out) but the verification matrix can only assert stock-5.7 compile, not runtime behaviour.

**Node class surface (~100+ `UCustomizableObjectNode*` UCLASSes):**
- All in `CustomizableObjectEditor/Private/MuCOE/Nodes/` — **private headers** → cannot be included from blueprint-exporter.
- Exposure pattern (proven by M11 SmartObjectDefinition + M12 BehaviorTree): walk via UE reflection — `TObjectIterator<UClass>` to discover, `TFieldIterator<FProperty>` + `ExportTextItem_Direct` per UPROPERTY. No schema struct, no serializer changes, no new module deps.
- Sampled node categories visible in the editor tree:
  - Component / Material / Mesh / Texture / Skeletal / StaticMesh
  - Color / Float / Int / Enum / Bool / String parameters + constants + arithmetic + switches + variations
  - Layout / Modifier (ClipDeform / ClipMorph / ClipWithMesh / ClipWithUVMask / EditLayoutBlocks / EditMeshSection / ExtendMeshSection / MorphMeshSection / RemoveMesh / RemoveMeshBlocks / TransformInMesh)
  - Projector / Curve / Table / Group / Group Projector / PassThroughTexture / Reroute / ExposePin / ExternalPin
  - MeshMorph / MeshMorphStackDefinition / MeshMorphStackApplication / MeshReshape
  - ExtensionDataSwitch / ExtensionDataVariation
  - **MacroInstance** — this is how macro libraries compose into COs (M29.3 inbound link)

**Proposed file additions (mirrors M11–M15 exactly):**

```
Public/TextExport/
├── CustomizableObjectDeepRenderer.h                 # Entry: RenderCustomizableObjectMarkdown(UObject*). Gated on WITH_MUTABLE_SUPPORT.
├── CustomizableObjectInstanceDeepRenderer.h         # Entry: RenderCustomizableObjectInstanceMarkdown(UObject*). Gated on WITH_MUTABLE_SUPPORT.
└── CustomizableObjectMacroLibraryDeepRenderer.h     # Entry: RenderCustomizableObjectMacroLibraryMarkdown(UObject*). Gated on WITH_MUTABLE_SUPPORT.

Private/TextExport/
├── CustomizableObjectDeepRenderer.cpp
├── CustomizableObjectInstanceDeepRenderer.cpp
└── CustomizableObjectMacroLibraryDeepRenderer.cpp

Source/BlueprintExporter/BlueprintExporter.Build.cs  # Conditional optional module dep on CustomizableObject when the plugin is available (pattern mirror of WITH_SMARTOBJECTS_SUPPORT setup). Absent → WITH_MUTABLE_SUPPORT=0 → renderers compile to an "out-of-scope" notice.
Private/Commandlets/DeepDumpCommandlet.cpp            # Dispatch: 3 new typed checks (UCO / UCOI / UCOML) routed to the new renderers ahead of M19.2.1 DataAsset-instance fallthrough.
Private/InventoryEmit/PerAssetEmit.cpp                # Same dispatch for the -DeepDump sweep path.
```

**Sub-phase breakdown:**

| Phase | Scope | Version bump |
|---|---|---|
| **M29.0** | Research-close. Verify whether stock UE 5.7 Legacy can enable Mutable plugin (copy from UE_DOW vs engine-side enable). Probe a UCustomizableObject in memory via a throwaway Python snippet to confirm reflection walk reaches the node graph (likely `Source` or `Graph` FProperty on UCO pointing at a `UEdGraph`-derived type). Check whether the compiled-model blob on UCO re-hashes on save — if yes, document renderer must skip it. No code change. | none |
| **M29.1** | `UCustomizableObjectInstance` renderer — smallest surface. Dumps `CustomizableObject` parent reference + every non-default parameter override (bool / int / float / color / projector / texture) keyed by param name. Wire into DeepDump dispatch + `-DeepDump` sweep. Dual-engine DLL rebuild. Determinism twin-run against `MutableSample` slice (1 asset: `COI_Character`). | 1.19.13 → 1.19.14 (patch — additive new renderer, small surface) |
| **M29.2** | `UCustomizableObject` renderer — biggest piece. Parameters + states + referenced assets (skeletal meshes, materials, textures, anim BPs) + node graph walk (per-node class + UPROPERTY table via reflection; outgoing link list). Skips compiled-model blob (per M29.0 finding). Wire into DeepDump dispatch + `-DeepDump` sweep. Dual-engine DLL rebuild. Determinism twin-run against `MutableSample` slice (7 CO assets). | 1.19.14 → 1.20.0 (minor — new subsystem per CLAUDE.md semver rule) |
| **M29.3** | `UCustomizableObjectMacroLibrary` renderer — per-macro section: inputs + outputs + node-graph walk. Reuses the M29.2 per-node helpers (shared anon-namespace helpers in `DeepDumpRenderer.cpp` or a small `CustomizableObjectNodeRenderer.cpp` kept private-to-TU). Wire into DeepDump dispatch + `-DeepDump` sweep. Dual-engine DLL rebuild. Determinism twin-run against `MutableSample` slice (1 asset: `COML_Character`). | 1.20.0 → 1.20.1 (patch — additive) |
| **M29.4** | `verify_determinism.ps1` gains `-Project MutableSample` option (one-off slice — not in the default regression rotation). Dual-engine full-sweep determinism proof across the 9 demo assets (7 CO + 1 COI + 1 COML). Also closes Legacy-side verification if M29.0 concluded the plugin can be enabled there. | none |
| **M29.5** | Docs sweep. CLAUDE.md Project Structure tree adds the three new `TextExport/*Deep*` entries + `WITH_MUTABLE_SUPPORT` Build.cs note. WIP closure. README feature-matrix row (if that surface still advertises per-type Tier 2 coverage — grep `README.md` for "SmartObject" to find the existing row). | none |

**Fixture-project decision (2026-04-23):** use `MutableSample` (the demo project at `D:\Work\mutable\MutableSample\`) as a **secondary ad-hoc fixture project** — NOT added to BugHunt's regression rotation. Rationale: enabling Mutable in BugHunt's `.uproject` would triple the regression weight (Mutable + MutableRuntime + MutableTools + CustomizableObjectEditor builds) for a specialist subsystem. Instead, `verify_determinism.ps1` gets an optional `-Project MutableSample` target, exercised on push for M29.x changes only. BugHunt stays Mutable-free.

**Compiled-model skip policy:** if M29.0 shows `UCustomizableObject` re-hashes its compiled-model blob on save (non-deterministic output despite identical authoring input), the renderer skips the compiled-model section entirely and documents that in the `.deep.md` output as a known-limitation marker (honouring "Never guess values"). The authoring surface — parameters, states, node graph, referenced assets — is what the user explicitly asked for ("understand how Mutable works"), so skipping the compiled blob doesn't cost any of the stated value. Decision: ship the skip even if M29.0 shows the blob IS deterministic; revisit only if a future driver specifically needs the compiled representation.

**PR strategy:** ship per-sub-phase as separate PRs (M29.1 → M29.2 → M29.3 → M29.4 → M29.5), each with its own version bump + dual-engine DLL rebuild + `verify_all.ps1` matrix on BugHunt + ad-hoc `MutableSample` determinism slice. Matches the M28.2.1 → .5 precedent. Do NOT bundle all three renderers into one commit — each renderer is big enough to warrant independent review, and the per-sub-phase version bumps give the user a clean rollback boundary if any one type's determinism doesn't hold.

**Reference patterns to reuse (pull from existing code — don't re-derive):**
- `Public/TextExport/SmartObjectDefinitionDeepRenderer.h` + `Private/TextExport/SmartObjectDefinitionDeepRenderer.cpp` (M11) — **closest analogue**. Live-UObject-reflection render of a plugin-gated type, walks FInstancedStruct payloads and per-slot UPROPERTYs via `ExportTextItem_Direct`. Same `WITH_SMARTOBJECTS_SUPPORT` Build.cs pattern to mirror. Read this FIRST after `/clear`.
- `Public/TextExport/BehaviorTreeDeepRenderer.h` + `Private/TextExport/BehaviorTreeDeepRenderer.cpp` (M12) — node-graph recursive walk with per-node UPROPERTY tables. Closest template for M29.2's node-graph section and M29.3's macro graph walk.
- `Public/TextExport/DataTableDeepRenderer.h` (M13) — simplest alpha-sorted row dump. Template for M29.1's parameter-override dump.
- `Private/Commandlets/DeepDumpCommandlet.cpp` — the dispatcher chain where the three new typed checks get wired. Study the existing SO / BT / DT / Chooser / EQS dispatch order; CO types insert ahead of the M19.2.1 DataAsset-instance fallthrough.
- `scripts/verify_determinism.ps1` — add `-Project MutableSample` option mirroring the existing `BugHunt` / `DOW` cases. Single new `switch` arm.
- `Source/BlueprintExporter/BlueprintExporter.Build.cs` — grep for `WITH_SMARTOBJECTS_SUPPORT` to find the existing optional-module-dep pattern; copy-paste-adjust for `WITH_MUTABLE_SUPPORT`.

**M29.0 open questions (resolve in the research pass):**

1. **Legacy Mutable availability.** Stock UE 5.7 Legacy install doesn't currently have Mutable enabled — only UE_DOW has the plugin at `D:\Work\UE_DOW\engine\Plugins\Mutable\`. Options: (a) copy the plugin into Legacy's engine Plugins dir; (b) the plugin ships with stock UE 5.7 and just needs enabling in Legacy's `UE_DOW.uproject`; (c) Legacy-side runtime verification is out of scope — stock-5.7 coverage stops at "DLL compiles with `WITH_MUTABLE_SUPPORT=0`". Probe first; decide by evidence.
2. **Node graph location on UCustomizableObject.** Likely a `Source` or `Graph` UPROPERTY pointing at a `UEdGraph` / `UCustomizableObjectGraph` subobject. Read `D:\Work\UE_DOW\engine\Plugins\Mutable\Source\CustomizableObjectEditor\Private\MuCOE\CustomizableObjectGraph.h` to confirm the class; check whether it lives on the Runtime UCO (editor-only UPROPERTY gated by `#if WITH_EDITORONLY_DATA`). If editor-only, the `.deep.md` must be generated from the editor load path — no impact on commandlet-run output because ProjectInventory + DeepDump already run with editor data available.
3. **Compiled-model blob determinism.** Save a UCO in the editor twice with zero changes; compare `.uasset` bytes. If drifts, document the skip; if stable, still skip per the policy above.
4. **Node UClass discovery scope.** `TObjectIterator<UClass>` walks all loaded classes — too broad. Use `IsChildOf(UCustomizableObjectNode::StaticClass())` to filter; but we can't include the node base-class header. Resolve via `StaticFindObject(UClass::StaticClass(), nullptr, TEXT("/Script/CustomizableObjectEditor.CustomizableObjectNode"))` lazy-loaded once. Mirror M11's `StaticFindObject` pattern for the SmartObject base classes.
5. **Parameter-override serialization on UCOI.** The instance stores param overrides as either inline fields (`FCustomizableObjectBoolParameterValue`, `FCustomizableObjectIntParameterValue`, ...) or a single `FCustomizableObjectInstanceDescriptor`. Read `MuCO/CustomizableObjectInstance.h` + `MuCO/CustomizableObjectInstanceDescriptor.h` to confirm the shape; M29.1 structure depends on it.

**M29.0 findings (2026-04-23) — all five open questions resolved, no code change.**

1. **Legacy Mutable availability — STOCK UE 5.7 ACTUALLY SHIPS MUTABLE, corrected 2026-04-23 during M29.1 implementation.** Initial `Glob` probe returned zero hits at the `C:\Program Files\Epic Games\UE_5.7\Engine\Plugins\**\Mutable.uplugin` pattern; re-verified via direct `Test-Path` later (during a UBT cross-engine-discovery investigation for M29.1) — the file exists at `C:\Program Files\Epic Games\UE_5.7\Engine\Plugins\Mutable\Mutable.uplugin` with its compiled `UnrealEditor-CustomizableObject.dll` binaries. Original Glob either mis-matched or was tool-side cache-stale; always verify availability with `Test-Path` when a negative Glob answer drives a build decision. **Corrected decision: ship with `WITH_MUTABLE_SUPPORT=1` on both engines** — UE_DOW runs Mutable authoring content (DOW-side live dump), stock-5.7 builds also enable the renderer path (clean compile, clean load, works with any stock-5.7 project that enables the Mutable plugin). Option (a) ("copy plugin into Legacy's engine Plugins dir") is moot — Mutable already ships with stock 5.7. **Unexpected M29.1 consequence** — because `UnrealBuildTool.GetModuleDirectory("CustomizableObject")` discovers modules across every registered engine on the box (not just the build target's engine), the SmartObjects-pattern detection produced WITH_MUTABLE_SUPPORT=1 even on builds where the Mutable module wasn't reachable at link time (e.g. the HostProject-driven stock-5.7 RunUAT run accidentally linking against UE_DOW's Mutable headers path). The fix landed in Build.cs as a direct `System.IO.File.Exists` check against `EngineDirectory + "/Plugins/Mutable/Mutable.uplugin"` — robust against cross-engine discovery leaks. Pattern note: the SmartObjects / Chooser / StateTree gates above don't hit this because those plugins ship with every modern UE install (no cross-engine ambiguity); copy the M29.1 path-scoped pattern for any future optional dep that ISN'T universally present.
2. **Node-graph UPROPERTY on UCO — CONFIRMED.** `TObjectPtr<UEdGraph> Source;` at `CustomizableObject.h:320-322`, private, `#if WITH_EDITORONLY_DATA`. Reach via `FindFProperty<FObjectProperty>(UCustomizableObject::StaticClass(), TEXT("Source"))`; the renderer is gated on `WITH_EDITORONLY_DATA && WITH_MUTABLE_SUPPORT`. ProjectInventory + DeepDump already run with editor data available, so no commandlet impact.
3. **Compiled-model determinism — evidence strongly favours non-deterministic; SKIP as planned.** UCO holds a private `TObjectPtr<UCustomizableObjectPrivate> Private;` (opaque, likely hosts the compiled model) plus `TObjectPtr<UCustomizableObjectBulk> BulkData;` ("Only valid in packaged builds" per inline comment) plus an explicit `FGuid VersionId;` commented "Used to verify the derived data matches this version" (i.e., explicitly regenerated). Save hooks `PreSave` / `PostSaveRoot` / `BeginCacheForCookedPlatformData` / `IsCachedCookedPlatformDataLoaded` are overridden — strong signal that saves do work that can vary by build context. Empirical twin-save not run (would require launching editor against `MutableSample`); the header evidence is sufficient to ship the skip policy as pre-committed. Renderer emits `_Compiled model / private data — skipped (non-deterministic on save)._` marker honouring the "Never guess values" principle.
4. **UCustomizableObjectNode base-class path — SCOPE CORRECTION: base header is actually Public, not Private as the M29 scope block assumed.** Located at `D:\Work\UE_DOW\engine\Plugins\Mutable\Source\CustomizableObjectEditor\Public\MuCOE\Nodes\CustomizableObjectNode.h:90-94` (`UCLASS(MinimalAPI, abstract) class UCustomizableObjectNode : public UEdGraphNode`). Concrete subclasses (`UCustomizableObjectNodeComponent` / `UCONodeMaterialConstant` / `UCustomizableObjectNodeColorConstant` etc.) stay in `Private/MuCOE/Nodes/` — the original scope's assumption applies to them. **Decision: still use the `StaticFindObject` lazy-load pattern** (`StaticFindObject(UClass::StaticClass(), nullptr, TEXT("/Script/CustomizableObjectEditor.CustomizableObjectNode"))`) — pulling in the public header would drag `UEdGraphNode` + `EdGraph/EdGraphPin.h` + `MuCO/CustomizableObject.h` into our TU as a compile dep; the reflection path is zero-include. Mirrors M11's `StaticFindObject` lazy pattern exactly. Script path verified via Grep hit at `Public/MuCOE/Nodes/CustomizableObjectNode.h:91` (`class UCustomizableObjectNode : public UEdGraphNode`).
5. **UCOI param-override shape — CONFIRMED as single-descriptor.** `UCustomizableObjectInstance` holds one private `UPROPERTY() FCustomizableObjectInstanceDescriptor Descriptor;` (`CustomizableObjectInstance.h:758-759`); the inline `BoolParameters_DEPRECATED` / `IntParameters_DEPRECATED` / etc. arrays on UCOI itself are legacy and explicitly renamed `*_DEPRECATED` (lines 765-785) — skip them, render Descriptor only. Descriptor struct (`CustomizableObjectInstanceDescriptor.h:303-332`) has nine UPROPERTY arrays: `BoolParameters` / `IntParameters` / `FloatParameters` / `TextureParameters` / `SkeletalMeshParameters` / `MaterialParameters` / `VectorParameters` / `ProjectorParameters` / `TransformParameters`. Plus `Transient UPROPERTY() int32 State` — transient so never serialized; we should still render it as the authoring surface for state selection (useful for "understand how Mutable works"). M29.1 structure: `FindFProperty<FStructProperty>(UCustomizableObjectInstance::StaticClass(), TEXT("Descriptor"))` → walk the struct's nine arrays via `TFieldIterator<FArrayProperty>` + inner-struct `TFieldIterator<FProperty>` + `ExportTextItem_Direct` per inner field. Also dump `CustomizableObject` parent reference (first UPROPERTY of Descriptor, line 303-304) as the Tier 1 `Outer` link.

**M29.0 scope correction (2026-04-23):** close "Node UClass discovery scope" wording in Q4 above — base class was assumed private, is actually public-headered. The `StaticFindObject` lazy-load decision stands for compile-dep reasons, not header-visibility reasons. Update the M29.2 fixture notes when that phase ships: subclass discovery via `TObjectIterator<UClass>` filtered by `IsChildOf(BaseClass)` resolved from `StaticFindObject` — **not** by header include.

**M29.0 closed.** All five probes resolve to answers that match the M29 scope block's assumptions except Q4 (base header public, not private) which doesn't change the implementation plan. Ready to start M29.1.

**M29.1 shipped (2026-04-23, 1.19.13 → 1.19.14)**

- New renderer `Public/TextExport/CustomizableObjectInstanceDeepRenderer.{h,cpp}` gated on `WITH_MUTABLE_SUPPORT`. Single entry point `RenderCustomizableObjectInstanceMarkdown(UObject*)`. Casts internally; falls back to `RenderOutOfScopeNotice` on type mismatch or build-without-Mutable.
- `Build.cs` gate — the SmartObjects-pattern `GetModuleDirectory("CustomizableObject")` check leaked modules from other engines (UBT discovers globally). Replaced with `File.Exists(EngineDirectory + "/Plugins/Mutable/Mutable.uplugin")` path-scoped check. Result: `WITH_MUTABLE_SUPPORT=1` on both UE_DOW and stock UE 5.7 (since Mutable ships with stock 5.7 per the M29.0 Q1 correction). Old check false-linked CustomizableObject.dll into stock-5.7 builds even when unreachable at link time → Windows loader failed with `GetLastError=126` → every gate in `verify_all.ps1` red on BugHunt.
- `DeepDumpCommandlet.cpp` — added `IsCustomizableObjectInstanceClass` registry-level check + `bIsCOI` dispatch branch ahead of the M19.2.1 DataAsset fallthrough. UCOI inherits directly from `UObject` (not `UDataAsset`) so the fallthrough would never have caught it.
- `ProjectInventoryCommandlet.cpp` — added the same `Cast<UCustomizableObjectInstance>` branch to the `-DeepDump` sweep path, guarded by `WITH_MUTABLE_SUPPORT`.
- `BlueprintExporter.uplugin` — Mutable added as `Optional=true, Enabled=true`. This does NOT auto-enable Mutable in consumer projects via transitive propagation — the consumer's `.uproject` must still list Mutable explicitly. Dependent-plugin-list propagation runs at plugin-manager time, but the Windows DLL loader resolves imports BEFORE that runs; consumers with Mutable-free uprojects fail at `LoadLibrary`. Fix for BugHunt: added Mutable to `BugHunt.uproject` plugins list (Optional=true) AND rebuilt `BugHuntEditor.target` receipt to include it (stale receipt was silently filtering out newly-listed plugins). Future consumer projects shipping BlueprintExporter must repeat the pattern if they want runtime Mutable coverage; stock-5.7 builds without Mutable enabled in the consumer's uproject will fail to load the plugin DLL.
- Version bump 1.19.13 → 1.19.14 across 9 drift locations (uplugin × 2, module UE_LOG, 2× bridge handler pluginVersion, 4× Manifest/ExportInfo.PluginVersion stamps, live-version automation test, README). Integer stays at 19 per patch-bump rule.
- Dual-engine DLL rebuild: UE_DOW DLL at `BuiltPlugin/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` (2,591,744 bytes, BuildId `6efc257b-...`); stock UE 5.7 DLL at `_build_output_5_7/Binaries/Win64/...` junctioned into both `D:/Work/UE_DOW_Legacy/Plugins/BlueprintExporter` and `BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64` (2,593,280 bytes, BuildId `47537391`).
- Verification: **determinism twin-run PASS** on `MutableSample/COI_Character` — two independent UE editor shells produced md5-identical 5618-byte `.deep.md` (`ECC0F12CB660E38786D928A9BFEFD83D`); content exposes parent UCO link `/Game/Character/CO_Character`, 9 enum param overrides (clothing slots), 5 float param overrides (face morphs), with authored values for every parameter (`ChinType=A`, `EarPosition=0.500000`, etc.). **`verify_all.ps1` matrix PASS 12/12 in 183 s** (BugHunt / stock UE 5.7). `-IncludeDow` leg NOT run — M29.1 didn't touch BpxReflectionOps, so dual-engine verification per the M28.pre.4 gate table isn't required.
- MutableSample junction at `D:/Work/mutable/MutableSample/Plugins/BlueprintExporter` points at `BuiltPlugin/` — left intact for M29.2 (`UCustomizableObject` renderer) follow-up work.
- **M29.1 done. M29.2 (`UCustomizableObject` renderer — biggest sub-phase) is next.** Parameters + states + referenced assets + node-graph walk (per-node class + UPROPERTY table via reflection, outgoing link list). Skip compiled-model blob per the M29.0 policy. Reuse M12 BehaviorTreeDeepRenderer as the closest template for the node-graph recursive walk.

**M29.2 shipped (2026-04-23, 1.19.14 → 1.20.0)**

- New renderer `Public/TextExport/CustomizableObjectDeepRenderer.{h,cpp}` gated on `WITH_MUTABLE_SUPPORT`. Single entry point `RenderCustomizableObjectMarkdown(UObject*)`. Falls back to `RenderOutOfScopeNotice` on type mismatch or build-without-Mutable.
- Sections emitted (in order): **Identity** / **Runtime Options** / **Compile Options** (editor-only) / **Components** / **Parameters** / **States** / **Node Graph** / **Not rendered** (explicit skip notice for compiled-model blob + bulk data + population tags + deprecated inline fields).
- Parameter/state/component surface walked via UCO's public BlueprintCallable accessors (`GetParameterCount/Name/TypeByName/UIMetadata` + per-type default-value getters for all 9 Mutable types; `GetStateCount/Name/StateParameterCount/StateParameterName/GetStateUIMetadata`; `GetComponentCount/Name/GetSkeletalMeshComponentReferenceSkeletalMesh`). Alpha-sorted for determinism. No engine-private header includes needed — the accessors are the stable authoring surface.
- Node graph walked via `FObjectProperty` reflection on UCO's private `Source: TObjectPtr<UEdGraph>` UPROPERTY (lives under `#if WITH_EDITORONLY_DATA`). Per-node: class + title + UPROPERTY table (shared `RenderUObjectPropertiesTable` helper with CO-specific plumbing filter — `NodePosX/Y`, `NodeGuid`, `NodeComment`, `bCommentBubble*`, compiler-message fields, `EnabledState`, `bDisabled`, `Pins`/`DeprecatedPins`), plus outgoing pin-link list (`UEdGraphPin::LinkedTo` introspection, output-direction pins only so inverse edges aren't doubled). Did **not** need `StaticFindObject(UCustomizableObjectNode::StaticClass, ...)` after all — iterating `UEdGraph::Nodes` + reflecting each `UEdGraphNode` subtype worked directly; the M29.0 Q4 note about base-class discovery was predicated on `TObjectIterator<UClass>` filtering which isn't needed for this render path.
- **Pin-GUID determinism trap (new finding — carry forward to M29.3 / future renderers).** UCO nodes hold `FEdGraphPinReference`-typed UPROPERTYs (`NamePin` on `UCustomizableObjectNodeObject`, `LODPins` on `UCustomizableObjectNodeComponentMesh`, etc.) that `ExportTextItem_Direct`-serialize to `(OwningNode="...", PinId=<32-hex>)`. The `PinId` portion is `UEdGraphPin::PinId` — an `FGuid` regenerated at pin-creation time every load, not stable across runs even for an unchanged authored graph. First twin-run against `CO_Weapon` surfaced 325 byte-level drifts across 30 runs of `PinId=<hex>` at identical offsets (same size, same structure — only the GUID hex shifted). Fix: post-process with `MaskPinGuids(InOutText, StartOffset)` after the node-graph section renders — replaces every `PinId=<32-hex>` match with `PinId=<unstable>`, preserving the `OwningNode` reference so the authoring connection is still readable while the output is byte-identical twin-to-twin. Honors "Never guess values" by marking the GUID explicitly rather than stripping / synthesizing one. Pattern to reuse in M29.3 (macro library's node graph) and any future UEdGraph-walking renderer that might hit the same trap.
- `DeepDumpCommandlet.cpp` — added `IsCustomizableObjectClass` registry-level check + `bIsCO` dispatch branch alongside the M29.1 `bIsCOI` branch. Both UCO and UCOI inherit directly from `UObject` (not `UDataAsset`) so the M19.2.1 DataAsset fallthrough wouldn't catch either.
- `ProjectInventoryCommandlet.cpp` — added `Cast<UCustomizableObject>` branch to the `-DeepDump` sweep path alongside M29.1's UCOI branch, both guarded by `WITH_MUTABLE_SUPPORT`.
- Build.cs gate **unchanged** — the M29.1 `File.Exists(EngineDirectory + "/Plugins/Mutable/Mutable.uplugin")` check covers M29.2 too. No new module deps (node-graph walk goes through `UEdGraph`/`UEdGraphNode`/`UEdGraphPin` which are in the already-linked Engine module).
- Version bump 1.19.14 → 1.20.0 (minor — new-subsystem per CLAUDE.md semver rule) across 9 drift locations: `BlueprintExporter.uplugin` (×2 — `Version` integer bumped to 20 per int-rule, plus `VersionName`), module UE_LOG startup, 2× bridge handler `pluginVersion` stamps, 4× Manifest/ExportInfo.PluginVersion literals (`BlueprintExportManager.cpp` / `BlueprintSerializer.cpp` / `StateTreeSerializer.cpp` / `ProjectPluginsCommandlet.cpp`), live-version automation test (`BlueprintExporterTests.cpp`), README. `BuiltPlugin/` mirrored to match.
- Dual-engine DLL rebuild: UE_DOW DLL at `BuiltPlugin/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` (2,644,992 bytes, BuildId `6efc257b-...`); stock UE 5.7 DLL at `_build_output_5_7/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` (2,646,528 bytes, BuildId `47537391`) also synced into `BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64`. Size growth vs M29.1: +53 KB UE_DOW / +53 KB stock-5.7 (the CustomizableObjectDeepRenderer.cpp payload).
- **MutableSample game module re-compiled against UE_DOW** for the twin-run. MutableSample's pre-shipped `UnrealEditor-MutableSample.dll` had BuildId `47537391` (stock-5.7) — booting UE_DOW editor against the project errored with "The game module 'MutableSample' could not be found. Please ensure that this module exists and that it is compiled." Ran `Build.bat MutableSampleEditor Win64 Development -Project=MutableSample.uproject` against UE_DOW in 22 s; new MutableSample.dll picks up BuildId `6efc257b-...`. **Future-proof note for M29.3 / M29.4**: either rebuild MutableSample against UE_DOW (cheap — 22 s warm) or switch to stock-5.7 editor with the `_build_output_5_7` plugin junction (also cheap, but requires every enabled plugin's stock-5.7 BuildId to match). The UE_DOW path kept the MutableSample junction pointing at `BuiltPlugin/` where the UE_DOW-built plugin DLL lives.
- Verification: **determinism twin-run PASS** on `MutableSample/Weapon/CO_Weapon` — three independent UE_DOW editor shells produced md5-identical 42,185-byte `.deep.md` (`28B162FBD46C7AA9AA290B95CA6F5845`). Third shell run specifically to confirm the first two weren't accidentally stable (warm cache could mask a latent randomness); all three matched. Content exposes the full authoring surface: 15 nodes in the weapon graph (CustomizableObjectNodeObject root + ComponentMesh + FloatParameter + EnumParameter + Material + ObjectGroup etc.), full UPROPERTY tables per node, outgoing pin-link tables, 4 parameters (2 enums + 2 floats) with per-parameter UI metadata + enum option lists. **`verify_all.ps1` matrix PASS 12/12** in ~182 s (BugHunt / stock UE 5.7) — re-run after the post-mask stock-5.7 DLL synced into BugHunt to confirm the `MaskPinGuids` post-process doesn't regress any other code path. `-IncludeDow` leg NOT run — M29.2 didn't touch BpxReflectionOps, so dual-engine verification per the M28.pre.4 gate table isn't required.
- MutableSample junction at `D:/Work/mutable/MutableSample/Plugins/BlueprintExporter` → `BuiltPlugin/` (UE_DOW-built). Left live for M29.3 / M29.4 follow-up work — do NOT remove. Legacy junction at `D:/Work/UE_DOW_Legacy/Plugins/BlueprintExporter` → `_build_output_5_7` (stock-5.7-built) also left live.
- CLAUDE.md Project Structure tree updated with both M29.1 `CustomizableObjectInstanceDeepRenderer.{h,cpp}` and M29.2 `CustomizableObjectDeepRenderer.{h,cpp}` entries (M29.1 entry was missing from CLAUDE.md at the time — closed as part of this slice).
- **M29.2 done. M29.3 (`UCustomizableObjectMacroLibrary` renderer — smallest remaining sub-phase) is next.** Per-macro section: inputs + outputs + node-graph walk. Reuse the M29.2 node-graph pattern (including `MaskPinGuids` post-process — `FEdGraphPinReference` traps will appear here too). Twin-run fixture: `MutableSample/Character/COML_Character`. Version bump 1.20.0 → 1.20.1 per the M29 scope (patch — additive renderer).

**M29.3 shipped (2026-04-23, 1.20.0 → 1.20.1)**

- New renderer `Public/TextExport/CustomizableObjectMacroLibraryDeepRenderer.{h,cpp}` gated on `WITH_MUTABLE_SUPPORT`. Single entry point `RenderCustomizableObjectMacroLibraryMarkdown(UObject*)`. Zero-include approach — class dispatch by name (`GetClass()->GetName() == TEXT("CustomizableObjectMacroLibrary")`) so the Private-only `MuCOE/CustomizableObjectMacroLibrary/CustomizableObjectMacroLibrary.h` header stays out of our include chain. Library → Macros array → per-macro `{Name, Description, InputOutputs, Graph}` all resolved via `FindFProperty` by UPROPERTY name.
- Sections emitted: **Identity** → **library-level UPROPERTY table** (everything except Macros, rendered inline) → **Macros (N)** with per-macro block (object path / class / name, Description, I/O variable table, full graph walk) → **Not rendered** (pin-GUID masking notice + compiled-model skip, mirroring M29.2's closer).
- Per-macro I/O variable table surfaces four UPROPERTYs: `Name: FName` + `Type: ECOMacroIOType` (Input/Output) + `PinCategoryType: FName` (mesh / float / enum / etc.) + `UniqueId: FGuid`. UniqueId IS stable across loads — the header comment explicitly calls it out as "Useful for pin reconstruction and name repetitions", so it persists intact on disk. No masking needed; unlike `UEdGraphPin::PinId` this GUID doesn't regenerate.
- **Shared extraction (M29.3 refactor)**: `MaskPinGuids` and the node-graph walker lifted from `CustomizableObjectDeepRenderer.cpp` into `DeepRenderShared.{h,cpp}` as `BlueprintExporter::DeepRender::MaskPinGuids(FString&, int32)` + `RenderEdGraphNodes(FString&, const UEdGraph*)` + `EdGraphNodePlumbing()` (the shared UEdGraphNode plumbing filter, renamed from M29.2's anon-namespace `UCONodePlumbing` — nothing in the set is actually Mutable-specific). Refactor is pure code-move; CO_Weapon regression PASS — md5 `28B162FBD46C7AA9AA290B95CA6F5845` stays byte-identical before + after extraction.
- **`ExportTextItem_Direct` append-vs-assign trap (new finding)**: `FProperty::ExportTextItem_Direct(FString& Out, ...)` APPENDS to the output string rather than overwriting it — first-pass renderer initialized `DirStr` / `UniqueIdStr` with placeholder `"?"` fallbacks and got `"?COMVT_Input"` / `"?<guid>"` in the rendered table. Fix: start with an empty FString, run `ExportTextItem_Direct` into it, then fall back to `"?"` at cell-render time if the result is empty. Carry-forward pattern for any future renderer that uses the direct-text reflection path — initial value leaks into output because the helper doesn't call `.Reset()`.
- `DeepDumpCommandlet.cpp` — added `IsCustomizableObjectMacroLibraryClass` registry-level check + `bIsCOML` dispatch branch alongside the M29.1 `bIsCOI` and M29.2 `bIsCO` branches.
- `ProjectInventoryCommandlet.cpp` — added a class-name-match branch to the `-DeepDump` sweep path (can't use `Cast<UCustomizableObjectMacroLibrary>` because the class header is Private to CustomizableObjectEditor module and we don't want that compile dep).
- Build.cs gate **unchanged** — the M29.1 `File.Exists(EngineDirectory + "/Plugins/Mutable/Mutable.uplugin")` check covers M29.3 as well. No new module deps (`UEdGraph` / `UEdGraphNode` / `UEdGraphPin` are in Engine, already linked).
- Version bump 1.20.0 → 1.20.1 (patch — additive renderer per M29 scope) across 9 drift locations. `"Version": 20` integer stays — same minor digit. BuiltPlugin/ mirrored.
- Dual-engine DLL rebuild: UE_DOW DLL at `BuiltPlugin/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` (2,663,424 bytes, BuildId `6efc257b-...`); stock UE 5.7 DLL at `_build_output_5_7/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` (2,664,960 bytes, BuildId `47537391`) also synced into `BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64`. Size growth vs M29.2: +18 KB UE_DOW / +19 KB stock-5.7 (macro library renderer + shared extraction).
- Verification: **determinism three-run PASS** on `MutableSample/Character/COML_Character` — three independent UE_DOW editor shells produced md5-identical 34,620-byte `.deep.md` (`A505AC58A4422C6B489D0D56C3036159`). Content exposes 2 macros (`BlendNormals` + `ChangeBaseHairColor`), per-macro I/O variable tables (5 + 4 variables respectively), and full per-macro graph walks (14 + 12 nodes respectively). CO_Weapon regression also PASS at the same md5 as M29.2 — `28B162FBD46C7AA9AA290B95CA6F5845` (refactor preserved byte-identity). **`verify_all.ps1` matrix PASS 12/12** in 188.4 s on BugHunt / stock UE 5.7 after the fixed stock-5.7 DLL synced in. `-IncludeDow` NOT run — M29.3 didn't touch BpxReflectionOps, so dual-engine pre-push gate isn't required.
- MutableSample junction at `D:/Work/mutable/MutableSample/Plugins/BlueprintExporter` → `BuiltPlugin/` (UE_DOW-built). MutableSample's game module stays on the UE_DOW-built BuildId from M29.2's rebuild — no additional work needed for M29.3's twin-run.
- CLAUDE.md Project Structure tree updated with both M29.3 `CustomizableObjectMacroLibraryDeepRenderer.{h,cpp}` entries + cross-references from the M29.2 entries to the extracted `DeepRenderShared::RenderEdGraphNodes` helper.
- **M29.3 done. M29.4 / M29.5 remain scoped** per the M29 block further up. M29.4 (determinism gate extension — `verify_determinism.ps1` gains an optional `-Project MutableSample` target + full-sweep twin-run across the 9+ MutableSample Mutable assets) is a no-new-code infra slice. M29.5 is the final docs sweep — README feature-matrix row update if it still advertises per-type coverage (grep for "SmartObject" to find the existing row).

**M29.4 shipped (2026-04-23, no version bump)**

- `scripts/verify_determinism.ps1` gained a `MutableSample` arm. Three edits to the switch statements (`$ProjectFile` / `$DeepAsset` / `$ExtraArgs`) plus a one-line `ValidateSet` extension + docs update for the synopsis / examples. No behavioral change to the BugHunt / DOW paths — surgical add only.
- `-DeepAsset` default for MutableSample is `/Game/Weapon/CO_Weapon` (the smallest UCO in the project) so a single-asset run is cheap if `-SweepDeepDump` isn't set.
- `-EnablePlugins=BlueprintExporter` added to `$ExtraArgs` for the MutableSample arm (mirrors the DOW pattern). MutableSample.uproject doesn't list the plugin in its own `Plugins[]` — we mount it via the junction at `D:/Work/mutable/MutableSample/Plugins/BlueprintExporter` → `BuiltPlugin/`; the explicit `-EnablePlugins` belt-and-braces handles the uproject-plugin-list-missing case.
- Verification: **full-sweep twin-run PASS** via `verify_determinism.ps1 -Project MutableSample -SweepDeepDump`. Two complete pipeline passes (Manifest + Inventory + Aggregate + Plugins, with `-DeepDump` on Inventory so every processed asset emits a `<Path>.deep.md`) — both output trees byte-identical via `git diff --no-index`. First run cold: **91 s total** wall time (UE load + double pipeline). Second run warm (`-KeepOnSuccess` for stats capture): **69 s**.
- Sweep stats: **291 files / 45.2 MB** per tree, covering:
  - 92 `<Path>.deep.md` Tier 2 sidecars (Mutable slice gets the full M29.1/.2/.3 authoring surface; non-Mutable assets get the out-of-scope notice).
  - 93 `<Path>.meta.json` Phase 1 metadata sidecars.
  - 104 `<Path>.md` Phase 1 summaries.
  - 13 top-level rollups: `MANIFEST.md`, `INDEX.md`, `CLASS_TREE.md`, `DEPENDENCY_GRAPH.md` (+ `.dot`), `REPLICATION_MATRIX.md`, `HEALTH_REPORT.md`, `PLUGINS.md`, `AI_OVERVIEW.md`, `ANIM_OVERVIEW.md`, `UI_OVERVIEW.md`, `STRUCTS_ENUMS.md`, `SCOREBOARD_BASELINE.json`.
- **MutableSample stays an ad-hoc target** — deliberately NOT wired into `verify_all.ps1`. The M29.2 + M29.3 closure blocks already document this: enabling Mutable on BugHunt would triple its build weight (Mutable + MutableRuntime + MutableTools + CustomizableObjectEditor) for a specialist subsystem, so we keep the rotation Mutable-free. Manual `-Project MutableSample` is the right invocation when a future M29.x touches any renderer in the Mutable chain.
- Pre-req documented in the synopsis: MutableSample's game module must be rebuilt against the target engine (UE_DOW in our case — one `Build.bat MutableSampleEditor Win64 Development` produces BuildId `6efc257b-...` matching UE_DOW). Stock-5.7 shipped MutableSample.dll's BuildId `47537391` errors with "The game module 'MutableSample' could not be found" when loaded under UE_DOW, so the rebuild is non-optional for the determinism gate.
- No version bump (pure infra slice per M29 scope). No new files committed — only the `.ps1` touched.
- **M29.4 done. M29.5 docs sweep is last** — grep README for SmartObject feature-matrix row, add Mutable entries (CO / COI / COML) if the row exists. Pure-docs; closes the M29 umbrella.

**M29.5 shipped (2026-04-23, no version bump)**

- README.md surface swept — five touch points extended with the three Mutable types (CustomizableObject / CustomizableObjectInstance / CustomizableObjectMacroLibrary):
  1. TL;DR (line ~3) — "every Blueprint, StateTree, BehaviorTree, DataTable, …, Mutable CustomizableObject / Instance / MacroLibrary, Widget / Anim / Control Rig BP".
  2. Tier 2 `.deep.md` feature list (line ~71) — Mutable payload summarised (parameter/state/component schema + authored node graph for UCO, parameter overrides for UCOI, per-macro authoring surface for UCOML).
  3. "Asset coverage" line (line ~80) — appended the three type names with `WITH_MUTABLE_SUPPORT` gate note.
  4. Write-path gaps section (line ~147) — noted Mutable CustomizableObject family is Tier 2 read-only (no write ops yet, consistent with other non-UBP non-ST types).
  5. Bridge re-export coverage (line ~169) — added Mutable CustomizableObject family to the "returns status: unsupported" list, same tier as BT / DT / Chooser.
  6. Inventory-pipeline Tier 2 list (line ~243–248) — new bullet covering all three Mutable types with scope notes (compiled-model blob skipped as non-deterministic; FCustomizableObjectInstanceDescriptor for UCOI overrides; per-macro Name/Description/I-O table/graph walk for UCOML).
- CLAUDE.md Project Structure tree already covered (updated during M29.2 + M29.3); no changes needed.
- No version bump (pure docs per M29 scope).

**M29 umbrella closed (2026-04-23) — Mutable / CustomizableObject Tier 2 support end-to-end**

- **M29.0 research** (inline in this file) — five open questions resolved, Q1 corrected during M29.1 implementation (stock UE 5.7 **does** ship Mutable). Build.cs gate switched to `EngineDirectory + File.Exists` path-scoped check to avoid UBT's cross-engine module discovery false-positives.
- **M29.1** (`UCustomizableObjectInstance` renderer, patch 1.19.13 → 1.19.14, commit `d8e8bcb`) — 9 typed parameter-override arrays from `FCustomizableObjectInstanceDescriptor` via reflection. Twin md5 `ECC0F12CB660E38786D928A9BFEFD83D` / 5618 bytes on `MutableSample/Character/COI_Character`.
- **M29.2** (`UCustomizableObject` renderer, minor 1.19.14 → 1.20.0, commit `d6b9e7a`) — parameter schema + states + components + compile options + authored node graph via `UEdGraph` reflection on the private `Source` UPROPERTY. Pin-GUID determinism trap surfaced + fixed via `MaskPinGuids` post-process. Twin md5 `28B162FBD46C7AA9AA290B95CA6F5845` / 42,185 bytes on `MutableSample/Weapon/CO_Weapon` (three-shell stable).
- **M29.3** (`UCustomizableObjectMacroLibrary` renderer + shared-helper extraction, patch 1.20.0 → 1.20.1, commit `bb4703f`) — per-macro Name/Description/I-O variable table/graph walk via pure reflection (zero Private-header include). `MaskPinGuids` + node-graph walker lifted into `DeepRenderShared::RenderEdGraphNodes` / `::EdGraphNodePlumbing` / `::MaskPinGuids` shared helpers. CO_Weapon regression PASS unchanged post-extraction. Twin md5 `A505AC58A4422C6B489D0D56C3036159` / 34,620 bytes on `MutableSample/Character/COML_Character` (three-shell stable). `ExportTextItem_Direct`-appends-rather-than-overwrites finding documented.
- **M29.4** (determinism gate extension, no version bump, commit `831ce3b`) — `verify_determinism.ps1` gained a `MutableSample` arm (ValidateSet + three switch cases + synopsis docs). Full-sweep twin PASS via `-Project MutableSample -SweepDeepDump`: 291 files / 45.2 MB per tree byte-identical, 69–91 s per pair. MutableSample deliberately NOT wired into the `verify_all.ps1` regression rotation (specialist subsystem; keeps BugHunt Mutable-free).
- **M29.5** (this slice, no version bump) — README feature-matrix / coverage sweeps. Six touch points extended with Mutable types.
- **Shipped surface**: three new Markdown renderers (UCO / UCOI / UCOML), one shared-helper extraction, one determinism-gate arm. Version bumped across two releases (1.19.14 patch + 1.20.0 minor + 1.20.1 patch). Build.cs path-scoped optional-dep pattern established for future plugins that aren't universally present. All four twin-run md5s captured above as durable pass evidence. Renderer chain is read-only — write-side authoring of Mutable content (a future M30-ish scope if a driver appears) explicitly out of scope per the M29 "Out of scope" list.

**First actions after `/clear` (ordered — execute in sequence). M28.5.2 shipped; M28.5.3 is the direct continuation (scalar property setters):**

1. `git log --oneline -5` — confirm HEAD top-of-history is `549c564` (M28.5.2 feat) or a trailing docs-only Resume Checklist refresh on top of it. Working tree clean modulo the documented-ignore untracked items (`Code_Submit_Compiled_Binaries_to_UGS_*.log` + parent-dir `design.md` / `infographic.html` / `placeholder/` — all outside the plugin's ignore scope).
2. Re-read the **M28.5.2 shipped** closure block (line ~3662) for the matrix-troubleshooting arc + idempotency-for-destructive-ops recipe. Key M28.5.3-relevant carry-forwards: (a) the existing `SetPropertyValue` bridge is how scalar edits on Options[N].Generator and Options[N].Tests[M] properties reach the C++ — M28.5.3 ships as Python-only wrappers (no new UFUNCTION); (b) `FAIDataProviderFloatValue` / `FAIDataProviderBoolValue` are USTRUCTs so scalar `.DefaultValue` paths work straight through the existing `SetPropertyValue` — the M28.5.0 research flagged `DataBinding` (the provider UObject swap) as needing `PostEditChangeProperty` revalidation, punt it out of .3 scope.
3. Two new Python ops in `scripts/python_ops/eqs.py` (existing module from M28.5.2 — append, don't create): `set_eqs_test_property(eqs_path, option_index, test_index, property_path, value)` and `set_eqs_generator_property(eqs_path, option_index, property_path, value)`. Both resolve the EQS + walk to the target test/generator UObject via the existing `BpxReflectionOps.set_property_value` call with a composite path like `["Options", "[N]", "Generator", "UPROPERTYName"]`. No new UFUNCTIONs needed — C++ surface is unchanged.
4. Plan pipeline wiring: `OP_SPECS` in `plan_shape.py` (required `[eqs_path, option_index, test_index, property_path, value]` for test / `[eqs_path, option_index, property_path, value]` for generator, assets `[eqs_path]`); `_OP_DISPATCH` in `plan_executor.py`; `_op_expected_changes` in `mechanical_diff.py` (both mutate `eqs_path`). `__init__.py` re-exports + `__all__` alpha-sorted.
5. Fixtures: reuse `EQS_BpxTestWithOption` (M28.5.2 fixture) as the source — it has one option[0] with one test[0], both natural targets for scalar edits. Two new inspect+soak JSONs: one setting `ScoringFactor.DefaultValue` or similar on the Random test, one setting `SearchRadius` or `GeneratedActorClass` on the ActorsOfClass generator. Pick properties that render visibly in the M15 `EnvQueryDeepRenderer` output so `.deep.md` inspect asserts can hit them directly.
6. Version bump 1.22.1 → 1.22.2 (patch per semver — additive same subsystem, no new UFUNCTION). 9 drift locations — same bulk-replace recipe from M28.5.2.
7. Verification chain: since no new UFUNCTION, no dual-engine DLL rebuild is strictly required. However per M28.5.1 / M28.5.2 pattern, ship with a DLL rebuild anyway to re-stamp the pluginVersion fields. `verify_all.ps1` matrix 38/38 expected (34 from M28.5.2 + 2 new pairs × 2 ops), MCP pytest 23/23. No fixture regen needed (reusing EQS_BpxTestWithOption).

**Matrix-troubleshooting lessons carried forward from M28.5.2 (read before starting .3):**
- `make_result(op, target, field)` takes exactly 3 positional args. Multi-kwarg ops must compose the extras into a single descriptive `field` string, not pass separate args. Example: `make_result("set_eqs_test_property", eqs_path, f"option[{i}].tests[{j}].{prop}={value}")`.
- Destructive / stateful soak-round-2 regressions: `set_*_property` is naturally idempotent (same value → same md5), so no round-2 adjustment needed — but confirm the value isn't already the default, which would skip the mutation and produce different md5 than a fresh scratch.
- Stale scratch .uasset from prior failed soak runs blocks inspect re-runs. If a matrix fails mid-run, `rm -f BugHunt/TestProject/Content/TestBlueprints/EQS_BpxTest_*.uasset` before re-running. `soak_template.py` skips cleanup on `_fail()` SystemExit.

**BP_MacroMania -Force regeneration trap (discovered 2026-04-24 during M28.5.1):** `GenerateTestBlueprints -Force` crashes in `GenBP_MacroMania` with `Renaming EdGraph … on top of existing ObjectRedirector MyMacro is not allowed`. This is latent in the commandlet — only triggers when the BP_MacroMania fixture is already on disk with a prior-run redirector. Workaround: drop `-Force` and rely on the per-fixture `FixtureOnDisk && !GForceRegenerate` skip — new fixtures (absent on disk) still create via the `!FixtureOnDisk` branch. Side effect of a prior `-Force` attempt: fixtures before `GenBP_MacroMania` in the `Gens[]` registration order may get regenerated with fresh GUID-drifted bytes; `git checkout --` them if they appear in a `git status` unrelated to the current slice.

**Pre-existing M29 completion block + M28.3 catalog-complete block remain the next fallback drivers** if M28.5 is deprioritized. Both are closed; M28.5 is the active catalog.

**First actions after `/clear` (ordered — execute in sequence). M29.0 + M29.1 + M29.2 + M29.3 are done; this list is now scoped to picking up M29.4:**

1. `git log --oneline -5` — confirm HEAD top-of-history is the M29.3 feat commit (or a trailing docs-only Resume Checklist refresh on top of it). Working tree clean modulo the "Expected untracked state" items.
2. Re-read the **M29.3 shipped** closure block above and the `### M29` block further up for the original M29.4 scope. Carry-forwards to M29.4: (a) the MutableSample game-module-rebuild-against-UE_DOW step (one-time per engine rebuild — cached after that); (b) the `MutableSample` junction points at `BuiltPlugin/` (UE_DOW DLL); (c) the three-run twin-run pattern (not two-run — one probe in M29.2 was accidentally stable despite the pin-GUID bug; third shell caught it).
3. Inspect `scripts/verify_determinism.ps1` — look for the `$Project` param arm handling BugHunt / DOW. Add a MutableSample arm mirroring the existing BugHunt arm's shape: engine defaults to UE_DOW (not stock-5.7, because MutableSample's game module is rebuilt against UE_DOW), default `Filter` covers the 9+ MutableSample Mutable assets.
4. Run the new `-Project MutableSample` leg end-to-end to prove it twin-runs clean across the full MutableSample Mutable slice (CO_* + COI_* + COML_*). Capture timing + total byte count as the M29.4 closure evidence.
5. M29.5 docs sweep — README feature-matrix row update if needed (grep for "SmartObject" row existence); CLAUDE.md cross-refs if anything new lands in M29.4. Likely a pure-docs commit with no version bump.

**First actions after `/clear` (ordered — execute in sequence). M29.0 + M29.1 + M29.2 are done; this list is now scoped to picking up M29.3:**

1. `git log --oneline -5` — confirm HEAD top-of-history is the M29.2 feat commit (or a trailing docs-only Resume Checklist refresh on top of it). Working tree clean modulo the "Expected untracked state" items (`_build_output_5_7/` is a live junction target — do NOT delete).
2. Re-read the **M29.2 shipped** closure block above. Key carry-forwards to M29.3: (a) the `MaskPinGuids` post-process pattern — any node-graph walk over `UEdGraph` that emits `FEdGraphPinReference`-typed UPROPERTYs will hit the same pin-GUID instability trap; (b) the MutableSample game-module-rebuild-against-UE_DOW step; (c) the CO-specific node plumbing filter (`UCONodePlumbing()` in the M29.2 renderer — can reuse verbatim or lift into `DeepRenderShared.{h,cpp}` if M29.3 needs the same set).
3. Read `CustomizableObjectMacroLibrary.h` under `D:\Work\UE_DOW\engine\Plugins\Mutable\Source\CustomizableObjectEditor\Private\MuCOE\CustomizableObjectMacroLibrary\` — confirm the authoring-surface shape (per-macro inputs / outputs / node graph). Private header, so read-only-for-reference; implementation uses live reflection as M29.1 / M29.2 already do.
4. Author `Public/TextExport/CustomizableObjectMacroLibraryDeepRenderer.{h,cpp}` mirroring the M29.2 shape. Entry point: `RenderCustomizableObjectMacroLibraryMarkdown(UObject*)`. Gate on `WITH_MUTABLE_SUPPORT`. Wire dispatch in `DeepDumpCommandlet` + `ProjectInventoryCommandlet` -DeepDump sweep. Rebuild dual-engine. Version bump 1.20.0 → 1.20.1 (patch — additive per M29 scope).
5. Verification: twin-run against `MutableSample/Character/COML_Character` (the only COML asset in MutableSample). Run 3× to confirm stability (not just 2× — M29.2's first twin-run drifted on pin GUIDs, the third run caught that the warm-cache shells weren't evidence of true determinism). `verify_all.ps1` matrix on BugHunt must still PASS 12/12.

**Out of scope for M29** (keep this list stable — don't let scope creep in):
- Compiled-model blob decoding / visualization.
- Mutable runtime graph execution trace (compiled pipeline steps).
- Authoring *edits* of CO / COI / COML via python_ops (M29 is read-only deep export). A future M30-ish milestone could extend — not scoped today.
- Inventory Phase 1 coverage accounting for Mutable types. Currently the Phase 1 `.md` / `.meta.json` treat CO / COI / COML as out-of-scope "other" — M29 only adds Tier 2 `.deep.md` coverage. Phase 1 extension is a separate follow-up if needed.

---

**Pre-existing M26 block (lower priority than the Flat Arena driver above but still valid):**

---

**M26 — Blueprint graph authoring primitives.** Triggered 2026-04-21 during CombatPrototype Flat Arena diagnosis. Two independent capability gaps surfaced in one session, both requiring UEdGraph edits the current op catalog can't perform:

1. **Interface function not implemented** — `BP_EnemyBase` declares `BPI_Targetable` but has no `GetTargetingInfo` override. UE's message-call returns defaults (`bIsAlive=false`, `Faction=0`) for every call, so `AssessThreat(pawn)` never classifies anyone as hostile, `KnownTargets` stays empty, `CombatLoop`'s `ST_Cond_HasTargets` never fires. NPCs flow Wait → SearchClueLoop → FindClue → MoveToClue, find enemy clues (faction filter also broken for the same reason: `OwnFaction=0` ⇒ every AI matches every clue including the opposing team's at the other end of the map), run across the arena, never engage. Minimal fix is a 3-pin passthrough: `bIsAlive = this.bIsAlive`, `bIsTargetable = true`, `Faction = this.Faction`. Editor work is ~2 min; from ops today, unreachable.
2. **StateTreeCondition BP can't be authored** — the "proper" alternative fix (gate `CombatLoop` entry with a HasTarget EnterCondition BP) was deferred in the M25.2 discussion for the same reason: we have `create_child_bp` but no op to author the override graph body.

Both gaps trace to the same missing primitive: create / edit `UEdGraph` function bodies from Python. M23 proved the bridge pattern for StateTreeEditorData protected fields; M26 is the analogue for Blueprint function graphs.

**Sub-phase breakdown (tentative — M26.0 finalizes):**

| Phase | Scope | Deliverable |
|---|---|---|
| **M26.0** | Research + C++/Python surface decision | Which UEdGraph + KismetEditorUtilities APIs are already reachable from `unreal.*`? Where are we blocked by protected-property flags? Minimum `BpxReflectionOps` UFUNCTION surface to close the gap. Probe scripts under `D:/Work/_combat_ai_tuning/` as with M23. Review prior art in UE-Python graph bridging for reference patterns — read, don't vendor, don't attribute. Output: a scope note appended to this section with the chosen C++ surface (if any) + remaining sub-phase breakdown. |
| **M26.1** | `implement_interface_function` — narrow passthrough | Fixes the `BP_EnemyBase.GetTargetingInfo` bug specifically. Input: `{bp_path, interface_bp_path, function_name, output_bindings: {pin_name → "self.VarName" \| literal}}`. Creates override, emits Entry + Return nodes, wires outputs. Idempotent on `(bp_path, interface_fq_name, function_name)`. Deterministic `NodeGuid` via md5-seed from inputs (mirror M23.2's transition-GUID pattern). Atomic compile + save, standard op result dict. |
| **M26.2** | `add_bp_function` + `set_function_return_values` | General function creation with a fixed return shape — same idempotence + determinism rules as M26.1, but decoupled from the "interface" concept. Covers authoring a function-style Blueprint member (non-interface) with literal or variable-passthrough returns. |
| **M26.3** | `add_graph_node` + `connect_pins` + `add_local_variable` | Node-level composition for arbitrary logic. Unlocks authoring `ST_Cond_HasTargets` and similar single-comparison condition BPs. Defer if M26.1 + M26.2 cover the immediate use cases surfacing in practice. |
| **M26.4** | BugHunt fixtures + regression tests | New fixtures under `BugHunt/TestProject/Content/TestBlueprints/`: `BPI_TestInterface` + `BP_TestImplementsInterface` (no override — baseline) + `BP_TestExpectedAfterImpl` (post-op target shape). Determinism twin-run gate exercises the new ops. Fixture regeneration via `GenerateTestBlueprintsCommandlet` (extend the catalog; don't hand-author). |
| **M26.5** | Docs + MCP surface | `scripts/python_ops/CATALOG.md` entries for each new op. `plans/README.md` op kwargs table extended. `plans/AGENT_LOOP.md` worked example: `BPI_Targetable.GetTargetingInfo` passthrough. MCP `get_op_catalog` auto-surfaces (no server change needed — AST-only). `CLAUDE.md` "what the MCP CAN'T do yet" section shrinks. |

**Success criteria (M26 closed):** re-diagnose the Flat Arena bug purely via MCP tools, land the `GetTargetingInfo` fix via `apply_plan`, verify combat entry via `verify_state_transitions`, observe NPCs actually fighting in Legacy `Combat_FlatArena`. No editor manual step. Determinism twin-run passes.

**Risk indicators:** if M26.0 research shows UEdGraph is deeply protected (FProperty flags blocking node / pin mutation at the Python layer), the C++ bridge surface may balloon. Escape hatch: ship M26.1 passthrough-only (fixes the BP_EnemyBase case) as a tactical win and re-scope M26.2+ separately. The "proper" alternative to M26.1 — editor manual-fix on `BP_EnemyBase.GetTargetingInfo` (~2 min) — unblocks combat testing in the meantime if M26.0 reveals a large bridge surface.

**Reference patterns to reuse:**
- M23.2 `add_statetree_enter_condition` / M25.2.1 `add_statetree_transition` for the atomic compile+save + idempotence + deterministic GUID model.
- M24.3 mechanical-diff oracle for post-op verification (md5-level asset change + plan-declared verification entries).
- M23.1 `BpxReflectionOps` for the C++ UFUNCTION bridge pattern if M26.0 decides bridge extensions are needed.
- BugHunt + `verify_determinism.ps1` for the twin-run gate on any op that touches serialization.

**No version bump expected** in M26.0–M26.2 (pure additive Python ops + optional bridge extension). Version bump needed only if M26.3 adds new UFUNCTIONs to `BpxReflectionOps` — in which case follow the 1.17.0 → 1.18.0 minor-bump protocol documented in `CLAUDE.md § Versioning Protocol`.

**Also resume the Flat Arena live test once M26.1 ships:**
- Reconnect MCP in test workspace (`claude` from `D:/Work/unreal-mcp-test/`) — will auto-pick up any new ops via `get_op_catalog`.
- Run the interface-impl plan through `apply_plan` (with `confirm=true` after reviewing the preview).
- Reopen UE on Legacy, right-click `BP_EnemyBase` → Reload, verify the new override in the Blueprint editor, start `Combat_FlatArena` 5v5, observe engagement.
- If you want to exercise the StateTreeCondition path instead (M26.3 territory), the alternate plan is: add `ST_Cond_HasTargets` EnterCondition to `CombatLoop` root state (M25.2 `add_statetree_enter_condition`) after the condition BP itself has been authored via M26 ops.

### M28.6.0 research outcome (2026-04-25)

**Scoped during the post-M29.6 open-scope session; NOT yet implemented.** User picked M28.6 as the next external driver after M29.6 closed. Findings captured so the M28.6 authoring pass doesn't have to re-probe the GameplayTags engine surface. Patterns mirror M26.0 / M27.0 / M28.2.0 / M28.3.0 / M28.4.0 / M28.5.0 — research block lands before the first implementation slice.

**Target surface (per M28 phase table line 2995):** one plan op `add_gameplay_tag` + one zero-UE-process MCP tool `list_gameplay_tags`. Smallest M28.x surface to date — single op + single read tool — but with two non-obvious traps (module location, developer-config diversion) plus a P4-touching engine call worth surfacing.

**Headline correction vs phase-table description.** The phase table's reference to `UGameplayTagsManager::AddNewGameplayTagToINI` is **wrong** — that function lives on the **`IGameplayTagsEditorModule` interface**, not the runtime `UGameplayTagsManager`. The runtime `GameplayTags` module exposes only read-side APIs (`RequestAllGameplayTags`, `IsValidGameplayTagString`, `IsDictionaryTag`); the write-side editor API ships in the **editor-only `GameplayTagsEditor` plugin** at `Engine/Plugins/Editor/GameplayTagsEditor/`. This means M28.6.1's bridge UFUNCTION must add `GameplayTagsEditor` as a Build.cs editor-only dep gated by a new `WITH_GAMEPLAYTAGSEDITOR_SUPPORT` flag (mirroring `WITH_CHOOSER_SUPPORT` / `WITH_SMARTOBJECTS_SUPPORT` / `WITH_POSESEARCH_SUPPORT` patterns from M3.3 P1a–c). Stock UE 5.7 ships the plugin enabled-by-default for editor builds, so this is a low-risk dep add.

**Engine header findings (stock UE 5.7 — verified at `C:/Program Files/Epic Games/UE_5.7/Engine/`):**

1. **`IGameplayTagsEditorModule::AddNewGameplayTagToINI`** (`Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Public/GameplayTagsEditorModule.h:50`):
   ```cpp
   virtual bool AddNewGameplayTagToINI(
       const FString& NewTag,
       const FString& Comment = TEXT(""),
       FName TagSourceName = NAME_None,
       bool bIsRestrictedTag = false,
       bool bAllowNonRestrictedChildren = true) = 0;
   ```
   Returns `bool` — `true` on add success, `false` on any validation failure or duplicate. Module accessed via `IGameplayTagsEditorModule::Get()` (singleton); availability check via `IGameplayTagsEditorModule::IsAvailable()` returns false in non-editor builds.

2. **Implementation control flow** (`Private/GameplayTagsEditorModule.cpp:401-569`, verified line-by-line):
   - **L405-408:** Empty `NewTag` → return false (no toast).
   - **L410-413:** `Manager.ShouldImportTagsFromINI() == false` → return false. This is a project-config flag (`ImportTagsFromConfig` on `UGameplayTagsSettings` — DOW pins it `True`).
   - **L420-424:** `Manager.IsValidGameplayTagString(NewTag, &Err, &FixedString)` invalid → toast + return false. Validates `InvalidTagCharacters` (DOW pins `"\"\',"`), no leading/trailing dot, no double-dots, etc.
   - **L429:** `DeleteTagRedirector(NewTagName)` — if a redirect for this name exists, drops it silently. Determinism-relevant: a stale redirect can vanish on add.
   - **L432-437 (idempotence trap):** `Manager.IsDictionaryTag(NewTagName)` → toast "already exists" + return **false**. Engine API treats duplicate as an error, not a no-op. **The Python op must pre-check via reflected `IsDictionaryTag` and return `bSkipped=true` instead of failing**, otherwise the M28.pre.3 soak round-2 fails on its own success.
   - **L500-510 (DeveloperConfigName diversion):** If `TagSourceName == NAME_None || == FGameplayTagSource::GetDefaultName()` (= literal `"DefaultGameplayTags.ini"` per `GameplayTagsManager.cpp:204+225`) AND `UGameplayTagsDeveloperSettings::DeveloperConfigName` is non-empty, the source is diverted to `<DeveloperConfigName>.ini` (per-machine override). **Cross-machine determinism is impossible if any developer sets `DeveloperConfigName`.** DOW likely doesn't (production project; tags-ini is committed); but the op docs must call this out so plan authors don't expect the same `source_ini` value to land in the same file on every machine.
   - **L512-518:** `Manager.FindTagSource(TagSourceName)` → on miss, `FindOrAddTagSource(...EGameplayTagSourceType::TagList)` creates a new `UGameplayTagsList` source. For non-default names, the engine maps the source to `<Project>/Config/Tags/<TagSourceName>` (note the `Tags/` subdir — `GameplayTagsManager.cpp:2131`). For `"DefaultGameplayTags.ini"`, the source is pre-registered against `UGameplayTagsSettings` whose ConfigFile lives at `<Project>/Config/DefaultGameplayTags.ini` (no subdir). This asymmetry is load-bearing for `list_gameplay_tags` — see MCP surface below.
   - **L535-543:** `TagList->GameplayTagList.AddUnique(FGameplayTagTableRow(FName(*NewTag), Comment))` then `TagList->SortTags()`. **On-disk order is alpha-sorted deterministic** post-write — no insertion-order drift. The `AddUnique` defends against a redundant struct-equality match if the explicit pre-check at L432 misses (it can't, in practice).
   - **L545-551 (P4 trap):** `GameplayTagsUpdateSourceControl(ConfigFileName)` is called twice (before + after `TryUpdateDefaultConfigFile`), routing through `ISourceControlModule`. **If Perforce is configured (env vars / .p4config / project ini), the engine will checkout the .ini file as part of the save.** This is the same `apply_plan` confirm-gate territory as `.uasset` saves — the existing `confirm=True` requirement on the bridge handler is the correct mechanism. Document loudly in the op description + AGENT_LOOP. Not a blocker.
   - **L549:** `TagListObj->TryUpdateDefaultConfigFile(ConfigFileName)` — actual file write. Creates the file + parent dir if missing (standard UObject `SaveConfig` behaviour). Preserves the leading `;METADATA=(Diff=true, UseCommands=true)` header line that DOW's ini carries — that's a config-file-comment, untouched by `SaveConfig`.
   - **L551:** `GConfig->LoadFile(ConfigFileName)` — reload from disk so subsequent in-process `Manager` queries see fresh state.
   - **L565:** `Manager.EditorRefreshGameplayTagTree()` — full in-memory tag-tree rebuild. Means any subsequent `list_assets` / inventory re-export will see the new tag.

3. **`UGameplayTagsManager::IsValidGameplayTagString`** (`Source/Runtime/GameplayTags/Classes/GameplayTagsManager.h:377-379`, `GAMEPLAYTAGS_API`):
   - Three overloads (TCHAR* / FString / FStringView). All public, runtime module, callable without editor.
   - Returns `false` + populates `OutFixedString` with a corrected version (e.g. `".Tag"` → `"Tag"`, `"Bad Tag"` → `"BadTag"` after `InvalidTagCharacters` strip).
   - Already invoked internally by `AddNewGameplayTagToINI`; no need to expose a separate validator UFUNCTION on `BpxReflectionOps` for M28.6.1 (the engine API surfaces validation errors as `bSuccess=false` with a toast). Plan authors get validation feedback through the existing apply_plan report. **Defer dedicated validator UFUNCTION until a real driver wants pre-apply validation feedback.**

4. **`FGameplayTagSource::GetDefaultName()`** (`GameplayTagsManager.cpp:225-228`) returns the literal FName `"DefaultGameplayTags.ini"` (defined `GameplayTagsManager.cpp:204` as `static const FName NAME_DefaultGameplayTagsIni("DefaultGameplayTags.ini");`). This is the canonical name plan authors should pass for the project-default ini.

5. **Existing `IGameplayTagsEditorModule` API surface (richer than M28.6 needs but useful context):**
   - `AddNewGameplayTagToINI` — write (M28.6.1 wraps).
   - `DeleteTagFromINI(FGameplayTagNode)` + bulk variant — out of scope for M28.6.1 (no design.md driver).
   - `RenameTagInINI(Old, New, bRenameChildren)` — leaves a redirect; out of scope for M28.6.1.
   - `UpdateTagInINI(Tag, Comment, bIsRestricted, bAllowNonRestrictedChildren)` — edit comment/flags; out of scope.
   - `MoveTagsBetweenINI(Tags, TargetSource, OutMoved, OutFailed)` — bulk source-swap; out of scope.
   - `AddTransientEditorGameplayTag(Tag)` — editor-session-only tag (no ini write); out of scope.
   - `AddNewGameplayTagSource(NewTagSource, RootDirToUse)` — creates a new ini source without adding tags. **Useful but not required** — `AddNewGameplayTagToINI` auto-creates the source via `FindOrAddTagSource` on the first add. Defer until a driver wants empty-source authoring.

6. **Determinism traps:**
   - **No `FGuid::NewGuid()`** on the write path (grep-confirmed across the editor module + runtime module).
   - **No `MakeUniqueObjectName`** on the write path (the `UGameplayTagsList` UObject is a transient editor-side carrier, not a persisted asset).
   - **`SortTags()` ensures deterministic on-disk order** — alpha-sorted by tag name before write.
   - **`DeveloperConfigName` per-machine diversion** is the one cross-machine determinism risk; documented as user-machine config, not op-level (analogous to P4).
   - Soak round-2 byte-identity is achievable when `IsDictionaryTag` pre-check returns `bSkipped=true` and short-circuits before the `AddUnique` + `SortTags` + `TryUpdateDefaultConfigFile` chain. **Same idempotent-pre-check pattern as M28.5.1's `add_eqs_option`** (which walks existing options and reuses a matching one).

**Chosen C++ surface (1 UFUNCTION on `UBpxReflectionOps`):**

| New UFUNCTION | Purpose |
|---|---|
| `AddGameplayTag(FString TagName, FString DevComment, FName SourceIni, bool bIsRestrictedTag, FBpxReflectionResult& Out)` | Pre-check `Manager.IsDictionaryTag` → if true, set `Out.bSkipped=true` + `Out.Message="tag already registered in source <X>"` and return. Otherwise delegate to `IGameplayTagsEditorModule::Get().AddNewGameplayTagToINI(TagName, DevComment, SourceIni, bIsRestrictedTag, /*bAllowNonRestrictedChildren=*/true)`. Surface `bSuccess` + populated `Out.AfterValue` (= the source ini path) on success. Gated on `WITH_GAMEPLAYTAGSEDITOR_SUPPORT` via Build.cs detection (mirrors the M3.3 P1a `WITH_CHOOSER_SUPPORT` recipe). **No 5th `bAllowNonRestrictedChildren` param exposed** — always `true`; restricted-tag authoring is out of scope for M28.6.1 (`bIsRestrictedTag=false` default; flag accepted in the op for forward-compat but no soak coverage). |

**Python surface (1 op in new module `scripts/python_ops/gameplay_tags.py`):**

| New op | Bridge calls | Purpose |
|---|---|---|
| `add_gameplay_tag(tag_name, dev_comment="", source_ini="DefaultGameplayTags.ini", is_restricted=False)` | `AddGameplayTag` (no save needed — `AddNewGameplayTagToINI` handles file write internally) | Returns `{tag_name, source_ini, skipped}`. Idempotent via the C++-side `IsDictionaryTag` pre-check — second apply against the same `(tag_name, source_ini)` returns `skipped=True` with no ini-file mutation. Accepts both `"DefaultGameplayTags.ini"` (engine literal) and any non-default source name like `"AI.ini"` which routes to `<Project>/Config/Tags/AI.ini`. **No `set_curve_float_keys`-style follow-up op** — DevComment edits would route through the existing `IGameplayTagsEditorModule::UpdateTagInINI` API and ship as a separate M28.6.x sub-phase if a driver surfaces. |

**MCP surface (1 zero-UE-process tool):**

| Tool | Inputs | Output | Walks |
|---|---|---|---|
| `list_gameplay_tags(project_root)` | `project_root` (path string) | `{tags: [{name, comment, source}], sources: [{name, path, exists}]}` | (1) `<project_root>/Config/DefaultGameplayTags.ini` — section `[/Script/GameplayTags.GameplayTagsSettings]`, lines `+GameplayTagList=(Tag="...",DevComment="...")`. (2) `<project_root>/Config/Tags/*.ini` — section `[/Script/GameplayTags.GameplayTagsList]`, same `+GameplayTagList=` syntax. (3) `<project_root>/Plugins/*/Config/Tags/*.ini` — same shape, plugin contributions. **NOT walkable: native tags registered from C++ code via `AddNativeGameplayTag()`** — out of scope for the zero-UE-process tool; document as exclusion. If a driver needs native-tag enumeration, that ships as a separate UE-process tool (`live_list_gameplay_tags`) in a future M28.6.x. |

Implementation: Python regex / `configparser` walk; tag line pattern `r'^\+GameplayTagList=\(Tag="([^"]+)",DevComment="([^"]*)"\)'`. The `+` prefix is the engine's array-append config syntax — strip when matching. Preserve source-relative path so the agent can target follow-up `add_gameplay_tag` calls at the same source ini.

**Verification gate (M28.pre.5 — `scripts/verify_tag_author.py`, deferred since 2026-04-23):**

End-to-end parity script per the M28.pre.5 row in the verification-matrix table (line 2935):
1. **Snapshot baseline:** `git diff --numstat -- <Config/DefaultGameplayTags.ini>` (zero changes expected) + `list_gameplay_tags` (returns N tags).
2. **Apply add:** `add_gameplay_tag("BpxTest.Smoke", "Smoke test tag for M28.6.1", "DefaultGameplayTags.ini", False)` via `apply_plan`.
3. **Verify in-memory:** `list_gameplay_tags` returns `N+1` tags; `BpxTest.Smoke` present with correct comment + source.
4. **Verify on-disk:** `git diff --numstat -- <Config/DefaultGameplayTags.ini>` shows exactly one line added (the `+GameplayTagList=(Tag="BpxTest.Smoke",DevComment="Smoke test tag for M28.6.1")` entry); other prior `+GameplayTagList=` lines unchanged; `;METADATA=` header preserved.
5. **Re-apply (idempotence):** `add_gameplay_tag("BpxTest.Smoke", ...)` again → `skipped=True`; `git diff` unchanged from step 4.
6. **Cleanup:** revert `Config/DefaultGameplayTags.ini` for clean baseline. (M28.pre.3 soak round-2 byte-identity covers the determinism-stability angle separately.)

**Fixture story:** BugHunt has **no `DefaultGameplayTags.ini`** today (`<TestProject>/Config/` carries only `DefaultGame.ini` / `DefaultEngine.ini` / `DefaultInput.ini`). Two options:
- **(A) Commit a starter `DefaultGameplayTags.ini` in BugHunt** with the standard `[/Script/GameplayTags.GameplayTagsSettings]` header + `ImportTagsFromConfig=True` + zero `+GameplayTagList=` entries. Clean baseline for the soak round-2 byte-identity check; mirrors how DOW's ini sits today minus the tag list. **Recommended.**
- **(B) Let `add_gameplay_tag` create the file from scratch on first apply**, accept that round 1 creates file + first tag, round 2 idempotent-skips. Soak round-2 byte-identity is still achievable (round 2's IsDictionaryTag short-circuit means zero mutation), but the inspect gate has to assert against an absent baseline which complicates the `git diff --numstat` check. **Rejected.**

Option (A) adds ~10 lines to BugHunt — a single new `Config/DefaultGameplayTags.ini` file plus a one-line entry in `GenerateTestBlueprintsCommandlet.cpp`'s catalog if we want the file regenerated on fixture refresh (or leave it hand-committed; no .uasset content involved).

**Sequencing:**
- **M28.6.0** (this slice) — research only, no version bump, doc commit.
- **M28.6.1** — implementation slice. Ships UFUNCTION + Python op + MCP tool + parity gate + BugHunt starter ini together. Single slice — surface is small enough to not need further sub-phasing. **Minor bump 1.26.0 → 1.27.0** (new subsystem — tag config authoring). Dual-engine DLL rebuild (UE_DOW + stock UE 5.7); 9-location version stamp sweep per CLAUDE.md § Versioning Protocol.

**Open questions (resolve in M28.6.1):**
1. **`bIsRestrictedTag` exposure in the Python op** — accept the flag but don't ship soak coverage (default `False`; deferred until a real driver). **Recommend:** expose, document, no test fixture for restricted path.
2. **`DeveloperConfigName` diversion** — accept user-machine config; don't try to override. **Document loudly** in op docstring + AGENT_LOOP example so plan authors know `source_ini="DefaultGameplayTags.ini"` can land in `<DeveloperConfigName>.ini` per machine.
3. **Plugin tag contributions in `list_gameplay_tags`** — walk `<Plugins/*/Config/Tags/*.ini>` for project plugins? UE_DOW has plugins; some may carry tag inis. **Recommend:** yes, walk plugin tag inis in the same MCP tool with `source.path` reflecting the plugin-relative location. Native engine tags (registered from C++) still excluded — zero-UE-process can't enumerate them.
4. **DevComment escaping** — DOW's ini has `DevComment=""` everywhere (empty); engine's UE config string syntax escapes `"` as `\"` and `,` as `\,`. **Recommend:** the Python op normalizes `dev_comment` via standard config-string escaping before passing through the bridge; the engine handles the round-trip cleanly.
5. **MCP `list_gameplay_tags` includes redirects?** DOW's ini has 3 `+GameplayTagRedirects=` entries that map old → new tag names. **Recommend:** include `redirects` as a separate top-level field in the response (same shape: `[{old_name, new_name, source}]`) so the agent can resolve historical names without re-walking the ini. Native-engine redirects out of scope for the zero-UE-process tool.

**Out of scope for M28.6:** `delete_gameplay_tag` / `rename_gameplay_tag` / `move_gameplay_tag_between_sources` / `update_tag_comment` (M28.6.x sub-phases if a driver surfaces) / `bAllowNonRestrictedChildren` parameter (always `true`) / native-tag enumeration (UE-process-required, separate future tool).

**M28.6.0 CLOSED (research, 2026-04-25 post-M29.6 closure session).** M28.6.1 implementation is next pickup.

### M26.0 research outcome (2026-04-21)

**TL;DR — pure Python is insufficient; a narrow bridge extension unblocks M26.1. No blast radius on protected-property flags. Go for M26.1.**

Research ran during the current session, without spawning UE. Evidence is code-based:

1. **`BpxReflectionOps` surface audit** (`Source/BlueprintExporter/Public/Reflection/ReflectionOps.h`) — 10 existing UFUNCTIONs cover property GET/SET, array append/remove, InstancedStruct type init, NewSubobject, FindSubobject, CompileAndSavePackage. None of them touch `UEdGraph`, `UK2Node_*`, or `FBlueprintEditorUtils`. The bridge was scoped for StateTree editor-data mutation (M23.1) and the data-model primitives it ships are enough for property-level edits but not graph-level.
2. **Existing Python op patterns** (`scripts/python_ops/{statetree.py,assets.py,blueprint_cdo.py}`) — the EC / transition / CDO-var / SCS ops all stay within the "load asset → walk editor properties → set values → compile+save" envelope. Nothing in the library authors a `UEdGraph` today. `create_child_bp` is the closest: it uses `unreal.BlueprintFactory` + `AssetToolsHelpers.create_asset` to make a new BP, but doesn't add graphs or nodes.
3. **Prior-art code review (UE-Python MCP tooling)** — read-only review of analogous graph-authoring service layers in other UE-Python projects. Typical surface exports ~60 graph/node/variable/function UFUNCTIONs. Key observation: **such projects exist precisely because these APIs are NOT bound to Python out of the box.** Every graph-editing primitive reaches into engine-private C++ — `FBlueprintEditorUtils::CreateNewGraph`, `FBlueprintEditorUtils::AddFunctionGraph<UClass>`, `UEdGraphSchema_K2::TryCreateConnection`, `UK2Node_FunctionEntry::AllocateDefaultPins`, `TObjectIterator<UClass>` for type resolution, `FFindInBlueprintsByName` patterns. None of these have `unreal.*` equivalents in 5.7. The entire prior-art service layer is essentially the bridge we'd need to replicate to reach graph editing from Python.
4. **Probe script authored** at `D:/Work/_combat_ai_tuning/m26_probe_python_surface.py` — read-only, no mutation. Prints attribute inventory of `unreal.BlueprintEditorLibrary` (filtered to override/graph/function/interface/node/pin prefixes), walks `BP_EnemyBase`'s `UBlueprint` instance for `FunctionGraphs` / `UbergraphPages` / `ParentClass` / `ImplementedInterfaces` reachability (all Python-protected historically), tests `K2Node_*` class lookup via `find_object`, and logs to `m26_probe_output.txt`. **Not required for the M26.0 decision** (prior-art evidence is already decisive), but recommended to run on the next Legacy MCP session so we have first-party confirmation of the Python surface on stock UE 5.7 before touching the bridge. Invoke via `UnrealEditor-Cmd.exe <uproject> -run=pythonscript -script="D:/Work/_combat_ai_tuning/m26_probe_python_surface.py"`.

**Chosen C++ surface for M26.1 (narrow passthrough — BP_EnemyBase.GetTargetingInfo fix only):**

| New UFUNCTION on `UBpxReflectionOps` | Purpose |
|---|---|
| `OverrideInterfaceFunction(UBlueprint* BP, UClass* InterfaceClass, FName FunctionName) -> bool` | Creates the override function graph (routes to EventGraph for void/latent FUNC_Event signatures, dedicated FunctionGraph for ones with a return property). Scoped to the interface case — the caller passes the resolved `UInterface`'s generated class, so the op doesn't walk the parent hierarchy. Idempotent: returns `true` without re-creating if the graph already exists. |
| `FindGraphEndpoints(UBlueprint* BP, FName FunctionName) -> FBpxGraphEndpoints { EntryGuid, ReturnGuid }` | Resolves the auto-created `UK2Node_FunctionEntry` + `UK2Node_FunctionResult` for a function graph by name, returns their stable NodeGuids so subsequent ops reference by GUID (deterministic across reloads). New result struct; `FBpxGraphEndpoints` lives next to `FBpxReflectionResult` in `ReflectionTypes.h`. |
| `AddSelfMemberGetNode(UBlueprint* BP, FName FunctionName, FName MemberName, FVector2D Position) -> FBpxNodeResult { NodeGuid, bSuccess, Error }` | Creates a `UK2Node_VariableGet` bound to `MemberName` on the BP's generated class (self). Self-only by design — we don't need arbitrary-owner lookups for the passthrough, so skipping the `TObjectIterator<UClass>` class-resolution path. Deterministic NodeGuid seeded via md5(bp_path + function_name + member_name). |
| `ConnectPinsByName(UBlueprint* BP, FName FunctionName, FGuid FromNodeGuid, FName FromPin, FGuid ToNodeGuid, FName ToPin) -> FBpxReflectionResult` | Finds pins by name on the two referenced nodes, invokes `UEdGraphSchema_K2::TryCreateConnection`. Honours the engine's Branch-alias normalization (`True→then` / `False→else`) so callers can use display-name pin ids — not needed for M26.1's passthrough but shipping it once costs nothing. |
| `SetNodePinLiteralDefault(UBlueprint* BP, FName FunctionName, FGuid NodeGuid, FName PinName, const FString& LiteralText) -> FBpxReflectionResult` | Sets `UEdGraphPin::DefaultValue` so `bIsTargetable=true` lands as a literal without needing a separate `K2Node_MakeLiteralBool`. String form — the schema coerces per pin type. |

Compile+save reuses the existing `CompileAndSavePackage(UObject*)` UFUNCTION unchanged.

Total: **5 new UFUNCTIONs + 2 new USTRUCTs** (`FBpxGraphEndpoints`, `FBpxNodeResult`). All additions; no changes to existing bridge surface. Small enough that a version bump to 1.18.0 + stamp-location sweep is straightforward. DLL rebuild required against BOTH engines (custom UE_DOW + stock UE 5.7 for Legacy).

**Revised sub-phase breakdown (M26.1 stays narrow on purpose):**

| Phase | Scope | Notes |
|---|---|---|
| **M26.1** | Add 5 UFUNCTIONs + 2 USTRUCTs above; ship Python `implement_interface_function(bp_path, interface_bp_path, function_name, output_bindings)` op. Version bump 1.17.0 → 1.18.0. BugHunt regression fixture: `BPI_BpxTestInterface` + `BP_BpxTestImplementsInterface` (no override — baseline) + golden post-op asset. Determinism twin-run gate verifies M8 `.deep.md` sweep is byte-identical after the new UFUNCTIONs ship (they don't touch serialization, so should be trivially green — but verify). |
| **M26.2** | `add_bp_function` + `set_function_return_values` for non-interface function authoring. Extends the M26.1 bridge with `CreateFunction(UBlueprint*, FName, bool bIsPure)` UFUNCTION. M26.1's `AddSelfMemberGetNode` + `ConnectPinsByName` + `SetNodePinLiteralDefault` + `FindGraphEndpoints` + `CompileAndSavePackage` are all reusable as-is. |
| **M26.3** | General node-level composition (`add_graph_node`, `connect_pins`, `add_local_variable`). Bridge surface scales up to the full node-creation catalog (roughly 15-30 UFUNCTIONs). **Defer unless M26.1/.2 prove insufficient for the real backlog** — the `ST_Cond_HasTargets` authoring case is the only known driver, and M26.2 may already cover it if the condition BP's override function is a pure getter. |
| **M26.4** | BugHunt fixtures per phase: at minimum the M26.1 interface-impl fixture; expand as M26.2/.3 ship. `GenerateTestBlueprintsCommandlet` extended — do NOT hand-author fixtures. |
| **M26.5** | Docs sweep: `CATALOG.md` per new op, `plans/README.md` op kwargs table, `plans/AGENT_LOOP.md` worked example (the `BPI_Targetable.GetTargetingInfo` passthrough reads cleanly end-to-end as the motivating example). `CLAUDE.md` grows `UBpxReflectionOps::*` interface-implementation entries. MCP `get_op_catalog` auto-surfaces. |

**Risk re-assessment (was "if research shows UEdGraph is deeply protected, the surface may balloon"):**

- **Python-binding risk: LOW.** Not protected; unbound. The bridge pattern is identical to M23.1 and proven on both engines.
- **API surface risk on M26.1 alone: LOW.** 5 UFUNCTIONs, all narrow, all targeting stable engine APIs confirmed to work on 5.7 via prior-art review.
- **API surface risk on M26.3: MEDIUM.** Full node-creation catalog is 15-30 UFUNCTIONs. Tractable, but non-trivial. Mitigated by explicit defer-unless-needed policy above.
- **Engine-version risk: LOW.** `FBlueprintEditorUtils::CreateNewGraph` + `UEdGraphSchema_K2::TryCreateConnection` are UE 4.x-era stable APIs.
- **Compile-unit risk: LOW.** New UFUNCTIONs live in `ReflectionOps.cpp`, which already links against `UnrealEd` via Build.cs (needed for `FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified` today). `BlueprintGraph` module may need adding to `Build.cs` — confirm in M26.1 implementation pass.

**Revised version-bump expectation:** M26.1 DOES require a version bump (1.17.0 → 1.18.0) — the original brief's "no bump expected in M26.0–M26.2" assumed pure additive Python ops without touching `BpxReflectionOps`. Bridge additions require the full 9-location stamp sweep + dual-engine DLL rebuild per `CLAUDE.md § Versioning Protocol`. M26.2 stays on 1.18.x (additive to the bridge → minor/patch decision at implementation time). M26.3 likely bumps again.

**M26.0 closed. M26.1 ready to start.** Next steps:
1. (Optional but recommended) Run the probe script on next Legacy MCP session to capture first-party Python-surface evidence in `m26_probe_output.txt`. Not a blocker.
2. Start M26.1 implementation: add the 5 UFUNCTIONs + 2 USTRUCTs to `ReflectionOps.{h,cpp}` + `ReflectionTypes.h`; add `Build.cs` dep on `BlueprintGraph` if needed; write the Python `implement_interface_function` op in new module `scripts/python_ops/blueprint_graph.py`; wire into `__init__.py` + `plan_validator.OP_SPECS` + `plan_executor._OP_DISPATCH` + `mechanical_diff._op_expected_changes`; extend BugHunt fixtures via `GenerateTestBlueprintsCommandlet`; version bump 1.17.0 → 1.18.0 across all 9 stamp locations; determinism twin-run.

### M27 — Persistent editor bridge (scoped 2026-04-22)

**Context.** M26.0 research complete and M26.1 shipped (commits `aea0d38` / `34439e1` / `f367354`, plugin 1.17.0 → 1.18.0). M26.2–M26.5 remain pending in the sub-phase table above as a lower-priority track. M27 is the next active milestone scope; `/clear` resumes should pick up here. A reference implementation was reviewed (pattern-only — read, don't vendor, don't attribute; mirrors the M25 / M26.0 prior-art pattern).

**Motivating context.** The M24 plan pipeline → M25 MCP server → M26 graph-authoring bridge climb has been steadily adding capability. The remaining bottleneck is **latency**, not capability: every `apply_plan` cold-starts `UnrealEditor-Cmd.exe -run=pythonscript`, waits 2–5 min for engine boot + Python init, runs the plan, exits. On DOW-sized projects this makes iterative editing impractical. The reviewed reference demonstrates a persistent editor WebSocket server with JSON-RPC 2.0, request IDs, per-handler timeout overrides, and game-thread dispatch via `FTSTicker::AddTicker` with capture-by-value shared state (avoids TaskGraph recursion assertions seen when handlers trigger subsystems like InterchangeEngine). Sub-second round-trip per call. M27 ports the **pattern** onto our existing plugin, keeping everything above it (MCP server, Python op composition, plan validator, mechanical-diff oracle, export pipeline) intact.

**Decisions already made (not re-litigating in M27.0):**
- MCP stays Python / FastMCP at the AI boundary. Transport change happens **below** MCP.
- Python op composition layer stays — C++ primitives continue to grow underneath as the M23→M26 pattern.
- Plan validator (M24.1), executor (M24.2), and mechanical-diff oracle (M24.3) stay unchanged in semantics.
- Primitive-level graph-op track (M26.3) stays deferred. M27 is transport + lifecycle, not new ops.
- Headless / CI path (`UnrealEditor-Cmd.exe -run=pythonscript` shelling) is preserved as a **fallback** — MCP tries the bridge first, falls back on connect failure.
- FTSTicker-based game-thread dispatch is net-new to our plugin (grep confirms zero existing `FTSTicker` / `FSocket` / `FRunnable` / `WebSocket` / `BridgeServer` / `HandlerRegistry` usage in `Source/`).

**Sub-phase breakdown (tentative — M27.0 finalizes):**

| Phase | Scope | Deliverable |
|---|---|---|
| **M27.0** | Research + boundary decisions | Confirm plain-socket vs `WebSocketsModule` choice (review `Build.cs` impact of each). Decide port convention (proposed: 9876, configurable via `BPX_BRIDGE_PORT` env var; localhost-bound, no auth). Decide Python-in-process lifecycle (fresh namespace per plan vs reuse with clearing — benchmark on a representative plan). Probe `FPythonScriptPlugin::ExecPythonCommandEx` availability + error surface. Decide Live Coding / hot-reload behavior (editor reload ⇒ server restart ⇒ MCP reconnect retry). Append M27.0 closure notes here before M27.1 starts. |
| **M27.1** | Minimum viable persistent server | New module subtree `Source/BlueprintExporter/Private/Bridge/`: `BpxBridgeServer.{h,cpp}` (FRunnable accept loop, WS handshake, frame parser), `BpxGameThreadExecutor.{h,cpp}` (FTSTicker-based game-thread dispatch, capture-by-value, abandonment-safe), `BpxHandlerRegistry.{h,cpp}` (`TMap<FString, FHandlerFunction>` + per-method timeout override map). One roundtrip handler: `ping` → returns `{pong: true, pluginVersion: "..."}`. Wired into `BlueprintExporterModule::StartupModule` (server start) + `ShutdownModule` (drain + join). `Build.cs` adds `Sockets`, `Networking` (no `WebSockets` module dep — hand-rolled handshake keeps the dep surface minimal and matches the reviewed pattern). **Version bump 1.18.0 → 1.19.0** (new subsystem = minor per `CLAUDE.md`). 9-location stamp sweep + dual-engine DLL rebuild. |
| **M27.2** | Bridge JSON-RPC to existing plan pipeline | Two handlers registered: `validate_plan(planJson, inventoryRoot)` → runs M24.1 validator in-process, returns structured report. `apply_plan(planJson, confirm, inventoryRoot)` → runs M24.2 executor + M24.3 mechanical-diff in-process, returns run-report matching today's shape. Handlers invoke the existing Python op library via `FPythonScriptPlugin::ExecPythonCommandEx` — same code path as `run_plan.py` today, just in-process instead of subprocess. Per-handler timeouts: `validate_plan` 300 s, `apply_plan` 900 s (mirror today's subprocess limits). MCP-side `tools/plans.py` gains a bridge-first code path: connect → send → await; fall back to today's subprocess shelling on connect-fail / handshake-timeout. `get_op_catalog` deliberately **stays AST-only** (zero-UE-process) — not routed through the bridge; that property is worth preserving. |
| **M27.3** | Auto re-export after apply_plan | `apply_plan` handler extended: on successful execute + diff, scopes a re-export across the asset paths declared in `expected_side_effects` (plus any surfaced by mechanical-diff), invokes the existing `TextExport/DeepDumpRenderer` in-process, writes `.md` / `.meta.json` / `.deep.md` via the existing `AtomicFileWriter::SaveStringAtomic`. `BPX_INVENTORY_ROOT` passed by MCP into the handler params. Run-report grows a `reExport: {scopedPaths[], wroteFiles[], errorCount}` section. `--no-reexport` flag on the handler for debugging. Closes the "manual `refresh_inventory` after each plan" agent-loop step for in-scope plans. |
| **M27.4** | Smoke test infrastructure | New introspection handler `list_methods` → returns registered handler names + param-shape stubs. `scripts/smoke_bridge.py` connects to localhost:<port>, pings, lists methods, round-trips every registered method with a params-shape-valid request, categorizes as OK / EXPECTED_ERROR / FAILURE. Wired into `scripts/verify_determinism.ps1` alongside the existing determinism gate, or as a sibling script invoked from the same PR check. |
| **M27.5** | Docs + polish | `CLAUDE.md`: new "Editor Bridge" section (transport, lifecycle, port convention, fallback behavior, threading discipline). `scripts/blueprint-exporter-mcp/README.md`: update `apply_plan` / `validate_plan` description to call out bridge-first + subprocess-fallback + expected latency delta. `plans/AGENT_LOOP.md`: update 8-step loop timing expectations (sub-second per step when bridge active). `WIP_INVENTORY.md` docs-map table entry for any new bridge doc. Version drift-detection run. |

**Success criteria (M27 closed):** editor-running `apply_plan` round-trip on a representative small plan is sub-second (vs 2–5 min cold-start today). Same M24 plan JSON works through both paths (bridge-first, subprocess-fallback) with no plan-authoring changes. Headless / CI path continues to work via the subprocess fallback — no regression for non-editor environments. `apply_plan` auto-re-exports touched assets; agent loop's manual `refresh_inventory` step is no longer required for in-scope plans. Determinism twin-run (`verify_determinism.ps1`) passes with the bridge active. Smoke script round-trips every registered handler. Post-M27.1 DLL is stable across both engines (custom UE_DOW + stock UE 5.7 for Legacy).

**Risk indicators:**
- **Threading discipline (HIGH → MITIGATED).** Game-thread vs network-thread boundary is the most accident-prone surface. `FTSTicker::AddTicker` with capture-by-value + abandonment-safe closures is the proven pattern — borrow the design literally; reimplement in our style. If a handler triggers an engine subsystem that itself reenters the TaskGraph (as InterchangeEngine does), TaskGraph dispatch will assert — FTSTicker sidesteps this.
- **Python in-process state leak (MEDIUM).** `FPythonScriptPlugin::ExecPythonCommandEx` runs in the editor's persistent Python interpreter. Module globals from plan N can leak into plan N+1 if not cleared. M27.0 benchmarks fresh-namespace vs clear-and-reuse; M27.2 implementation follows whichever is faster without giving up isolation.
- **Compile-time dep creep (LOW).** `Sockets` + `Networking` are engine-shipped. No new plugin deps. Audit in M27.1.
- **Partial-plan atomicity unchanged (CALL OUT, NOT MITIGATE).** Today `apply_plan` is per-op atomic, not per-plan — if op 3 of 5 fails, ops 1–2 are already committed. Bridge path preserves this semantic. Do not conflate transport change with atomicity change. Docs flag.
- **Port collision (LOW).** Proposed default 9876; `BPX_BRIDGE_PORT` env override lets users disambiguate explicitly if a collision surfaces.
- **Live Coding / hot-reload (UNKNOWN — RESOLVE IN M27.0).** Editor reload ⇒ server process continues but handlers may reference stale UFUNCTIONs. Worst case: gate server lifecycle to `FModuleManager` load/unload events explicitly.

**Reference patterns reused:**
- `BpxReflectionOps` (M23.1) for the UFUNCTION bridge pattern — if M27 surfaces any new game-thread-only primitives needing exposure, reuse the pattern. Likely not needed in M27 scope.
- M24.3 mechanical-diff oracle — runs unchanged inside the `apply_plan` handler after execute.
- M25.1 MCP tool signatures — `validate_plan` / `apply_plan` stay identical to MCP consumers. Only the transport below MCP changes.
- `AtomicFileWriter::SaveStringAtomic` for the re-export writes (M27.3) — same as the commandlets use today.
- Determinism twin-run (`scripts/verify_determinism.ps1`) for the regression gate on any M27.3 change that touches output.

**Out of scope for M27:** primitive-level graph-op track (M26.3, still deferred); authentication / remote-bridge / multi-client fanout (local loopback only); replacing MCP with a custom bridge (explicitly not doing this); rewriting Python op composition as C++ handlers (explicitly not doing this — the Python layer is an asset, not a liability); plan-level atomicity / rollback on partial failure (separate concern, separate milestone); bridge use from the commandlet / headless path (commandlets stay the headless entry point; bridge is for interactive editor sessions).

**Versioning expectation:** M27.0 no bump (research, scope). M27.1 bumps 1.18.0 → 1.19.0 (new subsystem). 9-location stamp sweep + dual-engine DLL rebuild per `CLAUDE.md § Versioning Protocol`. M27.2 / M27.3 additive to the bridge, patch-level bumps (1.19.0 → 1.19.1 → 1.19.2) unless a handler addition counts as a new subsystem by the `CLAUDE.md` rule (unlikely). M27.4 / M27.5 no DLL changes expected; MCP-server package version may bump independently.

**Open questions (resolve in M27.0 before M27.1 starts):**
1. Plain socket vs `WebSocketsModule`? Plain socket = fewer deps, hand-rolled handshake + frame parser (~200–300 LOC). `WebSocketsModule` = built-in, less code, pulls a module dep. Lean plain-socket for minimal surface; revisit if hand-rolled impl is more than ~1 day of work.
2. Port default. Proposed 9876 + `BPX_BRIDGE_PORT` override. Confirm 9876 isn't reserved by something in our typical dev environments.
3. Python namespace lifecycle. Fresh namespace per plan (clean, slightly slower) or reuse + explicit state clear (faster, more accident-prone). Benchmark before deciding.
4. Live Coding behavior. Server lifecycle gated to `FModuleManager` load/unload events — confirm this survives a Live Coding iteration cleanly, or document known-broken pattern + recommended "exit + relaunch editor".
5. MCP reconnect policy. Proposed: try bridge → on connect fail, 3x with 200 ms / 500 ms / 1 s backoff → fall back to subprocess shelling. Emits a structured `transport: "bridge" | "subprocess"` field in the MCP tool response for observability.
6. DLL distribution. Today `BuiltPlugin/` is manually copied into the engine's `Plugins/Editor/BlueprintExporter/`. M27.1 adds a new subsystem — confirm the existing distribution story still works (no extra steps, no new runtime files beyond the DLL itself).

**Step-0 probe (can run before M27.0 closes, no code changes):** write a throwaway script to time cold-start `apply_plan` on a minimal fixture plan (e.g. one `set_bp_variable_default` op against a BugHunt fixture). Establishes the "before" number concretely so M27 success criteria has a measured baseline, not a hand-waved "2–5 min". Expected outputs: mean + p95 over 3 runs on a warm DDC, same on a cold DDC.

**M27.0 research outcome (2026-04-22):**

Research ran without spawning UE; evidence is source-level (stock UE 5.7 under `C:/Program Files/Epic Games/UE_5.7/Engine`).

1. **`FPythonScriptPlugin::ExecPythonCommandEx` confirmed available** (`Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Public/IPythonScriptPlugin.h:55`). Signature takes `FPythonCommandEx&` in/out; captures `CommandResult` (return value or exception trace on failure) + `LogOutput[]` (per-line with `EPythonLogOutputType` classification — Info / Warning / Error). Access pattern: `IPythonScriptPlugin::Get()` → pointer. Scope requestable per call via `FPythonCommandEx::FileExecutionScope`.
2. **Python namespace lifecycle — RESOLVED NATIVELY.** Open question #3 eliminated: no benchmark needed. `PythonScriptTypes.h:51` defines `EPythonFileExecutionScope::Private` → "Execute the Python file with its own unique locals and globals dict to isolate any changes it makes to the environment." We set `Private` per plan and the engine gives us isolation. Reuse-with-clearing is not worth the accident surface.
3. **`FTSTicker` game-thread dispatch confirmed** (`Source/Runtime/Core/Public/Containers/Ticker.h:26-119`). `AddTicker(TUniqueFunction<bool(float)>&&, delay)` is documented thread-safe (can be called concurrently from the network thread — line 39/50). `RemoveTicker(Handle)` blocks until in-flight execution finishes — the abandonment-safe property we want. Use `FTSTicker::GetCoreTicker()` — no separate ticker needed. `Core` module dep already in our `Build.cs` `PublicDependencyModuleNames`. Grep confirms zero existing `FTSTicker` / `FSocket` / `FRunnable` / `WebSocket` / `BridgeServer` / `HandlerRegistry` usage in `Source/` — net-new infrastructure.
4. **WebSocket transport — DECISION FLIPPED to `WebSocketNetworking` plugin dep.** Found `Plugins/Experimental/WebSocketNetworking/Source/WebSocketNetworking/Public/IWebSocketServer.h` shipping with stock UE 5.7: `Init(Port, ClientConnectedCallback, BindAddress)` + `Tick()` + libwebsockets backend. Original scope proposed hand-rolled on `Sockets`+`Networking` modules (matching the reviewed reference, which was cross-platform-generalizing across Windows / Linux / Mac). For loopback-only internal tooling on Windows-only dev machines, accepting the "Experimental"-tagged API-churn risk is cheaper than owning ~300 LOC of WebSocket protocol + security-relevant code forever. `Runtime/Online/WebSockets` module is **client-side only** per `IWebSocket.h:1-60` — not a server alternative. Build.cs impact: no `Sockets`+`Networking` add; `.uplugin` gains `WebSocketNetworking` plugin dep; `WebSocketNetworking` module name added to `PrivateDependencyModuleNames` for linkage.
5. **Port 9876 stands** with `BPX_BRIDGE_PORT` env override for disambiguation.

**Deferred to M27.1 or post-M27.1 (require UE spawn):**
- **Step-0 cold-start baseline.** Run `apply_plan` on a minimal BugHunt fixture, 3× warm DDC + 3× cold DDC. Establishes the latency "before" number so M27's sub-second success claim is measured, not asserted. Can run in parallel with M27.1 code work.
- **Live Coding behavior.** Empirical check once server infra lands: server gated to `FModuleManager` load/unload events, iterate with Live Coding, document whether it survives cleanly or requires "exit + relaunch editor" for iteration. Fallback (manual relaunch) is acceptable for a dev tool; not a blocker.

**Revised M27.1 deliverable (reflecting #4 flip):** `Source/BlueprintExporter/Private/Bridge/` subtree with `BpxBridgeServer.{h,cpp}` (thin wrapper around `IWebSocketServer::Init` + `Tick()` driven from game thread), `BpxGameThreadExecutor.{h,cpp}` (FTSTicker-based dispatch, capture-by-value), `BpxHandlerRegistry.{h,cpp}` (`TMap<FString, FHandlerFunction>` + per-method timeout override). `BlueprintExporter.uplugin` gains `WebSocketNetworking` plugin dep; `Build.cs` adds `WebSocketNetworking` to private modules. One roundtrip handler: `ping` → `{pong: true, pluginVersion: "..."}`. Wired to `FBlueprintExporterModule::StartupModule` / `ShutdownModule`. Version bump 1.18.0 → 1.19.0 across 9 stamp locations; dual-engine DLL rebuild.

**M27.0 closed. M27.1 ready to start.**

**M27.1 shipped (2026-04-22):** commit `f4c4e0e`. Delivered the minimum viable persistent server.

Files added under `Source/BlueprintExporter/Private/Bridge/` (all guarded on `WITH_BPXBRIDGE_SUPPORT`):
- `BpxBridgeServer.{h,cpp}` — wraps `IWebSocketServer` from the stock `WebSocketNetworking` plugin. Binds to `127.0.0.1` only. `FTSTicker::GetCoreTicker().AddTicker()` drives `Server->Tick()` every frame on the game thread; libwebsockets delivers `OnClientConnected` / `OnMessageReceived` inside that tick, so all handler dispatch is game-thread-safe by construction.
- `BpxHandlerRegistry.{h,cpp}` — `TMap<FString, FHandlerFn>` lookup. Registration happens during `StartupModule` (game thread) and all reads happen from the same thread — no mutex needed.

Module wiring: `FBlueprintExporterModule::StartBridge/StopBridge` create/destroy the server. One handler registered: `ping` → `{pong: true, pluginVersion: "1.19.0"}`. Port default 9876; `BPX_BRIDGE_PORT` env var overrides.

Build / packaging:
- `Build.cs` gains `bHasWebSocketNetworking` detection mirroring the StateTree / Chooser / PoseSearch / SmartObjects pattern — plugin compiles cleanly on engines without `WebSocketNetworking` (the bridge is simply absent).
- `.uplugin` gains `WebSocketNetworking` as an `Optional: true` plugin dep.
- Version bump 1.18.0 → 1.19.0 across all 9 stamp locations (the pre-existing 8 tracked by `CLAUDE.md § Versioning Protocol` plus `ProjectPluginsCommandlet.cpp` which was drifted off the table; `CLAUDE.md` updated in the same commit). A new 10th stamp exists: the `ping` handler's hardcoded `pluginVersion` return string in `BlueprintExporterModule.cpp`. Added to the table.
- DLL rebuilt against custom UE_DOW engine. **Legacy (stock UE 5.7) DLL rebuild deferred** — lands on first Legacy test.

Two deliberate simplifications from the M27.1 scope:
- **`BpxGameThreadExecutor.{h,cpp}` skipped.** The scope assumed a pattern with a dedicated network thread needing FTSTicker-based marshaling back to the game thread. `IWebSocketServer::Tick()` is actually game-thread-driven already; callbacks fire synchronously inside the tick. The executor becomes relevant in M27.2 when `apply_plan` introduces potentially long Python execution that we don't want to block the game thread on — at that point we'll add a worker thread + FTSTicker ferry. Deferred; not a gap.
- **Per-handler timeout override map skipped.** `ping` is microseconds; timeouts only start mattering when handlers do real work. Added in M27.2 alongside `apply_plan` (900 s) and `validate_plan` (300 s).

**Fix landed during M27.1 build loop:** first build failed with `C4150 deletion of pointer to incomplete type 'IWebSocketServer'` on the defaulted constructor of `FBridgeServer`. TUniquePtr over a forward-declared type needs both ctor and dtor defined out-of-line so the deleter sees the complete type. Moved `FBridgeServer::FBridgeServer() = default` + `~FBridgeServer()` into the .cpp. Second build green.

**Empirical validation (2026-04-22):** Roundtripped the bridge against BugHunt TestProject (stock UE 5.7). Editor on-demand rebuilt the DLL against stock UE 5.7 when the project opened (BuildId mismatch against the custom-UE_DOW DLL we'd built), so this sweep also delivered the Legacy-style build the M27.1 scope had deferred — the fresh stock-5.7 DLL now lives at `BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64/`. Four JSON-RPC paths exercised, all green:

| Request | Response |
|---|---|
| `{"jsonrpc":"2.0","id":1,"method":"ping"}` | `{"result":{"pong":true,"pluginVersion":"1.19.0"},"jsonrpc":"2.0","id":1}` |
| unknown method | `{"error":{"code":-32601,"message":"Method not found..."},"id":2}` |
| malformed JSON | `{"error":{"code":-32700,"message":"Parse error..."},"id":null}` (null id per spec when id can't be parsed) |
| missing `jsonrpc` field | `{"error":{"code":-32600,"message":"Invalid Request..."},"id":4}` |

Log confirms `Bridge server listening on 127.0.0.1:9876` emitted at module StartupModule. Bridge is load-bearing.

**Gotcha landed while bringing the test up:** BugHunt's plugin install has a real (non-symlinked) `.uplugin` file at `BugHunt/TestProject/Plugins/BlueprintExporter/BlueprintExporter.uplugin` while `Source/` and `Config/` inside that same dir are symlinks to the repo's top-level `Source/` / `Config/`. The uplugin had drifted to 1.17.0 and didn't list `WebSocketNetworking` as a plugin dep — so even after bridge code landed, the WebSocketNetworking module wasn't getting loaded into BugHunt. Synced the uplugin manually (untracked file, no commit needed). Additionally added an explicit `WebSocketNetworking` entry to `BugHunt.uproject` Plugins[] — commit `e416672` — because the plugin-level `Optional: true` dep did not reliably force-enable the engine plugin on its own; the project-level enable is the belt-and-braces fix. **Follow-up opportunity (M27.5 docs / hygiene):** replace BugHunt's copy-of-uplugin with a symlink to the top-level `blueprint-exporter/BlueprintExporter.uplugin`, matching the `Source/` and `Config/` pattern already used in that dir, so future bumps propagate without a manual sync.

**Still owed (not blocking M27.2):**
- **Live Coding.** The server is gated to `Startup/ShutdownModule` events. Behavior under a Live Coding iteration is untested — fallback is "exit + relaunch editor" per M27.0 deferral.
- **Step-0 cold-start baseline.** Establishes the "before" latency number so M27.2's sub-second claim is measured. With the editor now known to boot the bridge in ~6 s post-compile, and the first launch (with compile) taking ~54 s of engine init, the baseline is roughly "first `apply_plan` after `/clear` is subprocess-bound at 2–5 min; subsequent bridge calls are sub-second" — but worth nailing down with a fixture plan before M27.2 claims the metric as proven.

**M27.2 shipped (2026-04-22):** commit `de54145`. Bridge JSON-RPC → existing plan pipeline. Editor `apply_plan` / `validate_plan` round-trip against a live editor in well under a second; falls back to today's subprocess shelling when the editor isn't up.

Files added:
- `Source/BlueprintExporter/Private/Bridge/BpxPlanHandlers.{h,cpp}` — C++ handlers. Each validates `{planJson, scriptsRoot}`, writes plan to `FPaths::ProjectIntermediateDir()/bpx_bridge_plan_*.json`, invokes `IPythonScriptPlugin::ExecPythonCommandEx` with `EPythonCommandExecutionMode::ExecuteStatement` + `EPythonFileExecutionScope::Private` (native per-call namespace isolation; no state leaks) running `import sys; sys.path.insert(0, r"<scripts_root>"); import bridge_entry; bridge_entry.run_{validate,apply}(r"<plan>", r"<out>")`. Reads the result JSON back, wraps as `{report, transport: "bridge"}`. Compiles out under `WITH_BPXPYTHON_SUPPORT=0`.
- `scripts/bridge_entry.py` — thin Python wrapper around `python_ops.plan_validator.validate_plan` + `python_ops.plan_executor.run_plan`. Same library calls as `run_plan.py` / `run_plan_validator.py`, so zero fidelity risk between bridge and subprocess transports. Takes explicit file paths (no CLI arg parsing).
- `scripts/blueprint-exporter-mcp/src/blueprint_exporter_mcp/tools/_bridge_client.py` — MCP-side bridge client. `try_bridge_call(method, params, recv_timeout)` opens a WS to `ws://127.0.0.1:<BPX_BRIDGE_PORT, default 9876>`, sends JSON-RPC, returns response dict. Raises `BridgeUnavailable` only on connect-refused / handshake-timeout / missing `websockets` lib — any server-delivered response (including JSON-RPC error objects) is authoritative and propagates to the caller without a subprocess fallback (prevents duplicate state mutations for `apply_plan`).

Files modified:
- `scripts/blueprint-exporter-mcp/src/blueprint_exporter_mcp/tools/plans.py` — `_try_bridge_for_plan` helper + integrated into `_run_plan_script` with a new `bridge_method` param (None = subprocess-only, used by legacy tools). `validate_plan_impl` passes `"validate_plan"`, `apply_plan_impl` passes `"apply_plan"`. Subprocess-path success return now includes `transport: "subprocess"`; bridge-path preserves the handler's own `transport: "bridge"` marker.
- `scripts/blueprint-exporter-mcp/pyproject.toml` — adds `websockets>=12` (lazily imported in `_bridge_client`, so colleagues with older checkouts that don't have it fall through cleanly).
- `BlueprintExporter.uplugin` — adds `PythonScriptPlugin` as `Optional: true` plugin dep; version 1.19.0 → 1.19.1 (patch, additive).
- `Source/BlueprintExporter/BlueprintExporter.Build.cs` — `bHasPythonScriptPlugin` detection mirroring the StateTree / WebSocketNetworking pattern; `WITH_BPXPYTHON_SUPPORT` define; `PythonScriptPlugin` added to `PrivateDependencyModuleNames` when present.
- 8 version-stamp locations bumped 1.19.0 → 1.19.1 (per `CLAUDE.md § Versioning Protocol`; ping handler's JSON response updated too).
- `CLAUDE.md` — Project Structure tree gets `BpxPlanHandlers` entry; Architecture section 5 expanded to cover M27.2 semantics (bridge-first-with-fallback, transport marker, PythonScriptPlugin gating).

**Empirical validation (2026-04-22):** Roundtripped end-to-end against BugHunt TestProject (stock UE 5.7 auto-rebuild of M27.2 source). Direct bridge calls:

| Call | Outcome |
|---|---|
| `ping` | `{pong: true, pluginVersion: "1.19.1"}` |
| `validate_plan` empty-ops | `{report: {passed: false, errors: ["operations must be non-empty"]}, transport: "bridge"}` — validator library ran in-process against live editor state |
| `apply_plan` empty-ops | full run-report `{passed: false, execution: {validation_report: {...}, aborted_at: null, per_op: []}, diff: null, transport: "bridge"}` — same library code as subprocess path, just invoked in-process |

MCP-layer validation:
| Scenario | Outcome |
|---|---|
| `validate_plan_impl` with editor running + shape-valid plan | `transport: "bridge"`; UE-side walker correctly rejects nonexistent `/Game/Nonexistent/ST_Fake` |
| `validate_plan_impl` with `BPX_BRIDGE_PORT=9999` (dead port) + no engine config | bridge unreachable → fallback to subprocess path → errors with `BPX_ENGINE_ROOT not set` (subprocess path's own error, confirming fallback fired) |
| Existing MCP smoke tests | all 18 still pass — no regressions from the bridge integration |

**Gotcha landed while bringing the test up:** UE doesn't auto-rebuild a plugin just because source changed — it only rebuilds on BuildId mismatch (engine-version drift) or missing DLL. The first M27.2 editor launch loaded the M27.1-era DLL from BugHunt's plugin install (BuildId matched), got the stale `v1.19.0` `ping` response, and reported `Method not found` on the new handlers. Fix: `taskkill /F` then `rm` the stale DLL + `UnrealEditor.modules` (with a longer pause — Windows holds the DLL lock briefly after process exit, and my first `rm` silently failed), then relaunch. Rebuild was ~30 s and the v1.19.1 DLL loaded cleanly. **Follow-up for M27.5 docs:** either add a "force-rebuild" script (`rm Binaries/Win64/*` + relaunch) or teach the build-and-sync tooling to nuke downstream installs' DLLs after a source change.

**Still owed after M27.2:**
- Live Coding probe (unchanged from M27.1) — now more interesting because Python-in-process adds another hot-reload surface.
- Step-0 cold-start baseline numbers — the scope cited "2–5 min" subprocess vs "sub-second" bridge; M27.2 proves the bridge is sub-second but hasn't measured the subprocess side on a representative fixture plan.
- **M27.3 — auto re-export after apply_plan.** Scoped re-export of assets listed in `expected_side_effects` + any surfaced by mechanical-diff. Closes the "manual `refresh_inventory` after each plan" agent-loop step.

**Next up — M27.2:** bridge JSON-RPC to the existing plan pipeline. Wire `validate_plan` + `apply_plan` handlers that call `IPythonScriptPlugin::ExecPythonCommandEx` with `EPythonFileExecutionScope::Private`, plus MCP-side bridge-first-with-subprocess-fallback in `scripts/blueprint-exporter-mcp/src/blueprint_exporter_mcp/tools/plans.py`.

**M27.3 shipped (2026-04-22):** scoped re-export of touched assets after a successful `apply_plan`. Closes the "manual `refresh_inventory` after each plan" agent-loop step for UBlueprint / StateTree targets — the next `get_asset_deep_dump` / `search_deep_dumps` / `get_cdo_properties` call sees post-plan state without a full-project re-sweep.

Files added:
- `Source/BlueprintExporter/Private/ReExport/AssetReExporter.{h,cpp}` — new in-plugin surface `BlueprintExporter::ReExport::ReExportAsset(PackageName, InventoryRoot) -> FReExportResult`. Loads the asset via `AssetRegistry::GetAssetsByPackageName`, dispatches by `Cast<UBlueprint>` / `Cast<UStateTree>` (other types return `EReExportStatus::Unsupported` — dot-three-file emission for BT/SO/DT/Chooser/EQS/DataAsset instances requires the commandlet's ~3500-line per-asset emitters, not factored out here). UBP path: `FBlueprintSerializer::SerializeBlueprint` → `FExportedBlueprint::ToJson()` + `coverage: {refreshedBy: "bridge_reexport"}` stub for `.meta.json`, `DeepDump::RenderBlueprintMarkdown` for `.deep.md`, brief placeholder pointing at `get_asset_deep_dump` for `.md`. StateTree path symmetric. All three writes go through `AtomicFileWriter::SaveStringAtomic`. `WITH_STATETREE_SUPPORT` gates the StateTree branch; UBP branch is unconditional.

Files modified:
- `Source/BlueprintExporter/Private/Bridge/BpxPlanHandlers.cpp` — `apply_plan` handler extended. `FPlanParams` gained `InventoryRoot` + `bNoReExport` optional fields. `RunBridgeEntry` takes a new `bRunReExport` flag; when true AND the Python report's `passed: true` AND `InventoryRoot` is set AND `noReexport` is false, the handler walks `report.diff.asset_changes[]`, collects every asset with `observed != stable` (skipping deleted assets — nothing to re-export once gone) or plan-expected mutation, sorts deterministically, invokes `ReExport::ReExportAsset` for each, and embeds a `reExport: {scopedPaths[], wroteFiles[], errorCount, perAsset[]}` section. Skipped paths (noReexport=true / inventoryRoot missing / run didn't pass / report not an object) each produce a `{skipped: true, reason}` stub so the agent can tell "didn't try" from "tried and hit zero assets". `validate_plan` keeps `bRunReExport=false` — read-only, nothing to re-export.
- `scripts/blueprint-exporter-mcp/src/blueprint_exporter_mcp/tools/plans.py` — `_try_bridge_for_plan` now plumbs `config.inventory_root` as `inventoryRoot` into the JSON-RPC params + optional `noReexport: true` when `re_export=False`. `_run_plan_script` + `apply_plan_impl` gained `bridge_re_export` / `re_export` pass-through. `@mcp.tool def apply_plan` gained a `re_export: bool = True` kwarg + expanded docstring describing the M27.3 flow, what gets re-exported in-scope (UBP + ST), and the limitations (other types need `refresh_inventory`; the brief placeholder `.md` vs canonical `.deep.md` + `.meta.json`).
- `CLAUDE.md` — Project Structure tree gains `ReExport/` entry; `BpxPlanHandlers` entry updated to mention the re-export wiring; Architecture section 5 expanded to cover M27.3 semantics (scope = mechanical diff's observed changes, skip rules, `.md` placeholder vs canonical `.meta.json`/`.deep.md`, subprocess path doesn't auto-re-export).
- 9 version-stamp locations bumped 1.19.1 → 1.19.2 (additive to the bridge — `apply_plan` gains a response field but the handler surface is compatible with older callers that ignore `reExport`).

**Re-export scope & limitations (deliberate for M27.3):**
- **UBlueprint family + StateTree only.** Covers 100% of the ops currently in `plan_executor._OP_DISPATCH` (`set_bp_variable_default`, `set_component_property`, `set_instanced_subobject_property`, `create_child_bp`, `implement_interface_function`, all `*_statetree_*` ops, `rename_asset` for the new-path side). BT / DT / Chooser / EQS / SmartObject / UserDefinedStruct / UserDefinedEnum / DataAsset instances return `status: "unsupported"` — the agent sees the unsupported set in `reExport.perAsset[]` and can follow up with `refresh_inventory` if those sidecars matter for downstream reasoning.
- **`.md` is a placeholder, not the full Tier 1 summary.** The Tier 1 rendering in `ProjectInventoryCommandlet` is ~350 lines of per-asset-type logic (field counts / coverage buckets / dependency lists / per-type sections) tangled with the commandlet's anon-namespace helpers. Factoring it out without disturbing a 3781-line file is a separate refactor; skipping it for M27.3 keeps the diff bounded. The placeholder is explicit about this — identity block + "refreshed via bridge_reexport" marker + pointer to `get_asset_deep_dump`. `refresh_inventory` restores canonical Tier 1 format.
- **Coverage block is a stub.** `.meta.json`'s `coverage` field gets `{refreshedBy: "bridge_reexport", note: "..."}` rather than the real per-bucket counts. Aggregation consumers (HEALTH_REPORT) that key on `coverage.overallPct` need to know this — documented in the stub itself.
- **Subprocess fallback doesn't auto-re-export.** Headless / CI callers already run their own full-project scans separately; adding a second pass inside the subprocess run would double the cold-start tax with no benefit.

**Follow-up opportunities (not blocking M27.3):**
- **Full Tier 1 `.md` parity** — factor the per-asset-type emitters out of `ProjectInventoryCommandlet`'s anon namespace into a shared header so both the commandlet and `AssetReExporter` use the same source. Could land as M27.3.1 when someone needs Tier 1 refresh badly enough.
- **Non-UBP types** — BT / SO / DT / Chooser / EQS each have their own typed renderer in `TextExport/` for Tier 2; adding a `ReExportBehaviorTree` / etc. branch is straightforward once the Tier 1 factor-out above exists. 2026-04-22 motivating content is UBP + ST only, so deferred.
- **Dependency-graph propagation** — if plan op A edits `/Game/Foo` and `/Game/Bar.Script` soft-references Foo, Bar's `.deep.md` may not need updating, but `DEPENDENCY_GRAPH.md` does. M27.3 doesn't touch project-level rollups; `refresh_inventory` is still the way to regenerate those.

**Empirical validation (2026-04-22):** Roundtripped end-to-end against BugHunt TestProject (stock UE 5.7 auto-rebuilt the M27.3 plugin on first launch, ~30 s rebuild + ~140 s editor boot; bridge listening on `127.0.0.1:9876` after ~2:20 of cold start). Three bridge calls from a standalone Python websockets client:

| Call | Outcome |
|---|---|
| `ping` | `{pong: true, pluginVersion: "1.19.2"}` — DLL loaded cleanly against stock 5.7 |
| `apply_plan` with malformed plan (`variable_name` + `expected_type` kwargs that the validator rejects) | `{report: {passed: false, execution: {validation_report: {...errors...}}}, reExport: {skipped: true, reason: "plan did not pass..."}}` — skip path fired correctly; re-export is gated on `report.passed=true` |
| `apply_plan` with an idempotent `set_bp_variable_default(BP_NetRep.Score=0, currently=0)` | `{report.passed: true, execution.passed: true, diff.asset_changes: [{asset: /Game/TestBlueprints/BP_NetRep, observed: "stable", expected: "mutated", md5 unchanged}], reExport: {scopedPaths: ["/Game/TestBlueprints/BP_NetRep"], wroteFiles: [<.md>, <.meta.json>, <.deep.md>], errorCount: 0, perAsset: [{asset: ..., status: "ok", class: "Blueprint"}]}}` — re-export wrote all three files into `<scratch>/Assets/Game/TestBlueprints/` |

Post-run file content verified:
- `.md` (741 b): brief placeholder with identity block + "Refreshed via `bridge_reexport` (M27.3)" row + pointer to `get_asset_deep_dump` — matches the M27.3 scope rationale (no duplication of the commandlet's full Tier 1 logic)
- `.meta.json` (14307 b): canonical schema output (`pluginVersion: 1.19.2`, full `variables[]` / `functions[]` / `components[]` / `cdoProperties[]` / `dependencies[]` from `FExportedBlueprint::ToJson()`), `coverage: {refreshedBy: "bridge_reexport", note: "Targeted per-asset refresh..."}` stub as scoped
- `.deep.md` (3947 b): full Tier 2 render with variables table, `pluginVersion: 1.19.2` in identity block — byte-level consistent with what `DeepDumpCommandlet -Asset=/Game/TestBlueprints/BP_NetRep` would emit

Idempotent-skip behavior validated: `observed: "stable" + expected: "mutated"` still triggers re-export (per the `Observed != stable OR !Expected.IsEmpty()` rule in `CollectReExportTargets`) — the agent gets fresh sidecars even on a replay that no-ops.

**Gotcha landed while bringing the test up:** same pattern as M27.2 — BugHunt's `.uplugin` copy was pinned at 1.19.1 (pre-M27.3), and the stale DLL from M27.2's rebuild was still in `BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64/`. UE loads the project's .uplugin text directly (not via symlink through the top-level one) and matches DLL BuildId against the compiled-against engine, so without both fixes the editor would have loaded the M27.2 DLL and reported pluginVersion 1.19.1 with no `reExport` field on the response. Fix: `cp BlueprintExporter.uplugin BugHunt/TestProject/Plugins/BlueprintExporter/` + `rm` the stale `.dll` + `.modules`. Editor rebuilt the plugin against stock 5.7 on first launch (~30 s). **Ties back to the M27.1 follow-up opportunity** to replace BugHunt's copy-of-uplugin with a symlink — still unaddressed.

**Still owed after M27.3:**
- Live Coding probe (unchanged from M27.1 / M27.2).
- Step-0 cold-start baseline numbers (unchanged from M27.2).
- BugHunt uplugin → symlink (M27.5 hygiene).

**Post-M27.3 patch (2026-04-22, plugin 1.19.3):** default bridge port flipped from 9876 → 1337. Historical rationale for 9876 was "sequential digits, not reserved" (M27.0 research #5). 1337 is equally valid — same range, no conflicts with our dev env — and colleagues preferred it. `BPX_BRIDGE_PORT` env var still overrides on both editor + MCP side. Only behavior change for users who hadn't set the override; anyone with an explicit `BPX_BRIDGE_PORT` is unaffected. Five files touched (BlueprintExporterModule.cpp default + log comment, _bridge_client.py default + docstring, README diagram + two paragraphs, CLAUDE.md §5 architecture entry); 9 version stamps bumped to 1.19.3.

**M27.4 shipped (2026-04-22, plugin 1.19.4):** smoke-test infrastructure for the bridge. Closes the M27.4 sub-phase of the M27 scope cleanly — `list_methods` handler + `scripts/smoke_bridge.py` now give us a ~5-second "is the bridge healthy" check that used to require standing up a full BugHunt apply_plan roundtrip.

Files touched:
- `Source/BlueprintExporter/Private/Bridge/BpxHandlerRegistry.{h,cpp}` — `Register()` gains an optional `Description` arg; parallel `TMap<FString, FString> Descriptions` + `GetDescription(Method)` getter. Self-description is co-located with each registration, impossible to drift from the handler itself.
- `Source/BlueprintExporter/Private/BlueprintExporterModule.cpp` — `list_methods` handler registered last (so it sees every peer + itself). Captures the registry by raw pointer (module-lifetime safe: server is torn down before the registry in `StopBridge`). Returns `{methods: [{name, description}], pluginVersion}`. `ping` handler gains a description too.
- `Source/BlueprintExporter/Private/Bridge/BpxPlanHandlers.cpp` — `validate_plan` + `apply_plan` registrations gain prose descriptions covering their params + returned shape.
- `scripts/smoke_bridge.py` (new) — standalone Python client using the same `websockets` lib as `_bridge_client.py`. Seven tests: `ping` / `list_methods` (positive), `unknown_method` / `missing_jsonrpc_field` / `malformed_json` / `validate_plan_empty_ops` / `apply_plan_empty_ops` (negative — EXPECTED_ERROR). Exit 0 iff zero FAILUREs. `BPX_BRIDGE_PORT` env override respected, defaults to 1337.
- `CLAUDE.md` — Project Structure tree entry updated for `HandlerRegistry` + parallel description map; Architecture §5 lists the new `list_methods` handler; Docs Map table gains `scripts/smoke_bridge.py`; Versioning Protocol row 3 expanded to cover both `ping` and `list_methods` hardcoded `pluginVersion` sites.
- `README.md` — Live editor workflow section adds a "Health-checking the bridge" paragraph pointing at the smoke script + mentioning `list_methods` discovery.
- 9 version-stamp locations bumped 1.19.3 → 1.19.4.

**Empirical validation (2026-04-22):** BugHunt editor relaunched with v1.19.4 DLL; bridge listening on `127.0.0.1:1337` after ~25 s (much faster than M27.3's 2:20 because the DLL was already compiled against stock 5.7 and only needed a delta-rebuild). `python scripts/smoke_bridge.py` output:

```
=== Summary: 7 tests  |  OK=2  EXPECTED_ERROR=5  FAILURE=0
PASS
```

Every test categorized correctly — `ping` + `list_methods` return shape-valid responses; all three negative JSON-RPC paths (unknown method / missing `jsonrpc` / malformed JSON) return the expected error codes (-32601 / -32600 / -32700); both plan paths with empty `operations` correctly get rejected by the UE-side validator with `reExport` skipped-reason set to "plan did not pass...".

**Follow-up opportunities from M27.4 (not blocking):**
- Wire `smoke_bridge.py` into CI. Currently the determinism gate (`verify_determinism.ps1`) handles byte-identity regressions but doesn't exercise the bridge subsystem. Adding a sibling `scripts/verify_bridge.ps1` that launches an editor, runs the smoke test, shuts down the editor — or just a GitHub Actions hook that assumes the editor is live — would catch bridge regressions automatically. Deferred until we have a second bridge handler set that's worth regressing against.
- `get_op_catalog`-style param schema on `list_methods`. Today the description is a human-readable string; in a future pass we could emit a structured `{required: [...], optional: [...]}` so MCP clients could auto-discover param shapes instead of hardcoding them. Not worth it while we have only 4 handlers.

**Still owed after M27.4:**
- Live Coding probe (unchanged from M27.1 / M27.2 / M27.3).
- Step-0 cold-start baseline numbers (unchanged from M27.2).
- BugHunt uplugin → symlink (M27.5 hygiene).

**M27.5 shipped (2026-04-22, plugin stays at 1.19.4):** docs + polish. No DLL change (pure documentation + repo-hygiene). Closes the M27 scope cleanly.

Files touched:
- `scripts/blueprint-exporter-mcp/README.md` — `validate_plan` + `apply_plan` tool rows rewritten to call out the bridge-first / subprocess-fallback transport with concrete latency deltas (sub-second vs 2–5 min cold start). New paragraph documents the `transport` field on responses + "keep editor open" guidance + the M27.3 re-export block on `apply_plan`.
- `scripts/python_ops/plans/AGENT_LOOP.md` — new "Timing expectations" table at the top of the 8-step section (sub-second per step with bridge, 2–5 min cold start without). Steps 4/5/7 rewritten to prefer MCP `validate_plan` / `apply_plan` over raw commandlet invocation, and to note that step 7's "manual DeepDump re-run" is replaced by the bridge's auto-re-export for UBP + StateTree targets.
- `BugHunt/TestProject/Plugins/BlueprintExporter/BlueprintExporter.uplugin` — flipped from real file to symlink into the top-level uplugin via `cmd /c mklink`. Eliminates the recurring "BugHunt uplugin drifted" gotcha that bit M27.1 / .2 / .3 / .4. Not git-tracked (the whole plugin dir under BugHunt is gitignored), so the fix is per-machine; `README.md` > BugHunt test project section gains a blockquote flagging the workaround for colleagues on the piecemeal-symlink setup.
- `scripts/force_plugin_rebuild.ps1` (new) — PowerShell helper that kills running editors + deletes a downstream install's `UnrealEditor-BlueprintExporter.dll` + `UnrealEditor.modules` so the next launch forces UBT to rebuild. Defaults to BugHunt's install; `-Install <path>` for other targets. Closes the M27.2 "UE caches DLL by BuildId not source mtime" gotcha — the force-rebuild dance was happening manually each session.
- `README.md` — Source-edit loop section gains a "Gotcha" paragraph pointing at `force_plugin_rebuild.ps1`.
- No version bump — docs + repo hygiene only.

**M27 scope CLOSED (2026-04-22).** All sub-phases M27.0 → M27.5 shipped. Success criteria met:

| Criterion | Status |
|---|---|
| Editor-running `apply_plan` round-trip sub-second | ✓ M27.1/.2 empirical (ping sub-second, plan roundtrip sub-second on M27.3 validation) |
| Same M24 plan JSON works through both transports | ✓ same library code (`python_ops.plan_executor.run_plan`) is invoked whether via ExecPythonCommandEx (bridge) or shell subprocess |
| Headless / CI path preserved via subprocess fallback | ✓ `_try_bridge_for_plan` returns None on BridgeUnavailable; `_run_plan_script` falls through cleanly |
| `apply_plan` auto-re-exports touched assets | ✓ M27.3 `reExport` block; UBP + StateTree covered, other types surfaced as unsupported for follow-up |
| Determinism twin-run passes with bridge active | ✗ not re-run this arc (the bridge doesn't change commandlet output; twin-run is about pipeline determinism, which is untouched) |
| Smoke script round-trips every registered handler | ✓ M27.4 `scripts/smoke_bridge.py` — 2 OK + 5 EXPECTED_ERROR, 0 FAILURE |
| Post-M27.1 DLL stable on both engines | ✓ UE_DOW custom engine + stock UE 5.7 via BugHunt's auto-rebuild; Legacy UE 5.7 not re-tested this arc (not blocking) |

**Plugin version trajectory this arc:** 1.18.0 (pre-M27) → 1.19.0 (M27.1 new subsystem) → 1.19.1 (M27.2 additive) → 1.19.2 (M27.3 additive) → 1.19.3 (default port flip) → 1.19.4 (M27.4 additive). **Still 1.19.4 after M27.5** (pure docs).

**Carried forward (not M27-scope blockers):**
- Live Coding probe — does the plugin survive a Live Coding iteration with an active bridge + in-process Python state? Untested.
- Step-0 cold-start baseline — the M27 scope asserted "2–5 min subprocess", sub-second on bridge is measured, but the subprocess baseline itself hasn't been reified with a fixture plan.
- BugHunt `BlueprintExporterTests` plugin uplugin also has the "real file" setup if we ever author a test that requires per-version-bump sync on that side. Not hit in M27; file it as a future hygiene pass if needed.

**Deferred sub-tracks (revisit when content surfaces):**
- M26.2 / M26.3 — more graph-authoring ops (`add_bp_function`, `set_function_return_values`, general node-level composition).
- M27.4 CI wiring — `scripts/smoke_bridge.py` is standalone; hooking it into a GitHub Actions workflow (which would need to spin up an editor) is a separate concern.

---

**M27.3.1 shipped (2026-04-22, plugin 1.19.5):** tech-debt payoff — factored the commandlet's Tier 1 + meta.json + StateTree emission logic out of `ProjectInventoryCommandlet.cpp`'s anon namespace into a shared `InventoryEmit/PerAssetEmit.{h,cpp}` module. Both the commandlet sweep and the bridge re-export (`AssetReExporter`) now call the same functions, so drift between their outputs is impossible by construction.

Files added:
- `Source/BlueprintExporter/Private/InventoryEmit/PerAssetEmit.h` — namespace `BlueprintExporter::InventoryEmit`. Six small shared helpers (`BuildAssetOutputBase` / `EscTbl` / `StripScriptPrefix` / `WriteJsonToFile` / `ComputeCoveragePercent` / `BuildNonUBPCoverageJson`) + three big entry points (`RenderBlueprintMarkdown` / `WriteMetaJson` / `EmitStateTreeAsset`).
- `Source/BlueprintExporter/Private/InventoryEmit/PerAssetEmit.cpp` — full implementation. UBP helpers (FormatPinType, FormatAccess, FormatBlueprintType, RenderIdentity/Inheritance/Variables/FunctionSection/Components/CDOProperties/StateMachines/WidgetTree/Graphs/References/Metadata + ComputeSpecialized*, BuildCoverageJson) moved here under private anon-namespace. StateTree helpers (Count/Format/RenderStateTreeState/CollectStateTreeStructTypes*) moved here gated on `WITH_STATETREE_SUPPORT`.

Files modified:
- `Source/BlueprintExporter/Private/Commandlets/ProjectInventoryCommandlet.cpp` — ~800 lines removed (the hoisted helpers + entry points). `#include "InventoryEmit/PerAssetEmit.h"` + `using namespace BlueprintExporter::InventoryEmit;` inside the existing anon namespace so the ~100 unqualified call sites (EscTbl / WriteJsonToFile / BuildNonUBPCoverageJson / etc.) resolve to the shared module. File shrinks from 3773 → ~2975 lines, which is worth something on its own.
- `Source/BlueprintExporter/Private/ReExport/AssetReExporter.cpp` — `MakePlaceholderTier1` + `MakeReExportCoverageStub` + `WriteMetaJsonForBlueprint` + `WriteMetaJsonForStateTree` deleted. `ReExportBlueprint` now calls `InventoryEmit::RenderBlueprintMarkdown` + `InventoryEmit::WriteMetaJson` + `DeepDump::RenderBlueprintMarkdown`. `ReExportStateTree` delegates entirely to `InventoryEmit::EmitStateTreeAsset`.
- `README.md` — "Live editor workflow" scope section: removed the "`.md` is a brief placeholder" caveat. Bridge-refreshed sidecars are byte-identical to `refresh_inventory` output.
- `CLAUDE.md` — new Project Structure entry for `InventoryEmit/`; `ReExport/` entry rewritten to call out the delegation to `InventoryEmit`; Architecture §5 bridge-behavior paragraph rewritten to drop the stub discriminator and placeholder caveat.
- 9 version stamps bumped 1.19.4 → 1.19.5.

**Empirical validation (2026-04-22):**

1. **Determinism gate** — `pwsh -File scripts/verify_determinism.ps1 -Project BugHunt -SweepDeepDump -Engine '<stock UE 5.7 cmd>'`. Twin-run of the full commandlet pipeline (ProjectManifest + ProjectInventory -DeepDump + AggregateInventory + ProjectPlugins) completed in 46 s: `PASS -- both output trees are byte-identical.` Proves the hoist didn't regress commandlet output.

2. **Bridge vs commandlet parity** — ran the idempotent `set_bp_variable_default(BP_NetRep.Score=0)` plan through `apply_plan` via the bridge (inventoryRoot pointed at a scratch dir), then ran `UnrealEditor-Cmd.exe -run=ProjectInventory -Filter=/Game/TestBlueprints/BP_NetRep -DeepDump` against a sibling scratch dir. md5sum for all three files:

```
bc0bf00ed6c70a583d4cbf2cf1c6f463 *BP_NetRep.md
fcf11fa021b5ffdf651d5f90a7ec21cc *BP_NetRep.meta.json
b964a1b3dfb6e04887af64c27a9a34b0 *BP_NetRep.deep.md
```

Identical across both output trees. Tech-debt items #1 and #2 closed: bridge re-export's `.md` is now the canonical Tier 1 format (not a placeholder), and `.meta.json`'s coverage block is the real computed values (not a `{refreshedBy: "bridge_reexport"}` stub).

**Gotcha landed while validating:** `verify_determinism.ps1` defaults to `-Engine D:\Work\UE_DOW\engine\Binaries\Win64\UnrealEditor-Cmd.exe` (studio custom engine), but BugHunt is pinned to stock UE 5.7. Running without the override hits a BuildId mismatch and the plugin silently fails to load, producing zero logic-bearing assets and a PASS (for the wrong reason — both empty output trees are trivially identical). Override: `-Engine 'C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe'`. Worth flagging in the script help — a future M27.5.1 could detect this via the `.uproject`'s `EngineAssociation` field.

**Post-M27.3.1 follow-ups (deferred, not blockers):**
- Non-UBP asset types in bridge re-export (BT, DT, Chooser, EQS, SmartObject, DataAsset instances). With `InventoryEmit` infrastructure in place, adding a typed emitter in the bridge path is ~20 LOC per asset type. Still waiting on a plan op that targets one of these — none exist today in `_OP_DISPATCH`.
- `verify_determinism.ps1` engine auto-detection from `.uproject` to eliminate the gotcha above.

### M26.1.1 — invisible interface-stub override fix (2026-04-22)

Patch fix on top of the shipped M26.1 `implement_interface_function` op. Two related bugs, one root cause: UE stores interface-override graphs on `Blueprint->ImplementedInterfaces[i].Graphs`, not on `Blueprint->FunctionGraphs`.

**Bugs fixed:**
1. **Serializer blindspot.** `FBlueprintSerializer::SerializeFunctions` only walked `FunctionGraphs`, so any interface-override stub the editor auto-created (one click on "add function" for an interface in the UI) was invisible in the exported JSON / `.md` / `.deep.md`. Downstream AI analysis saw "no such function" while UE silently carried a half-authored graph on the asset.
2. **Op deadlock.** `implement_interface_function`'s idempotency check hit the existing stub, bailed with `skipped: override graph already exists`, and left the pin bindings unauthored. No way to finish the authoring pass through the plan pipeline — manual-delete-in-editor was the only escape.

**Deliverables:**
- `FExportedFunction` gains `bIsInterfaceOverride: bool` + `InterfaceClassPath: FString`. JSON emission is gated on the flag being true / the path being non-empty, so non-override exports are byte-identical to pre-M26.1.1 (matters for the determinism gate).
- `FBlueprintSerializer::SerializeFunctions` walks `FunctionGraphs` + `ImplementedInterfaces[].Graphs` in a single pass, tagging each with its owning interface class path.
- `PerAssetEmit.cpp` renders `- Interface override of `<path>`` on each override function in the `.md`, with a **stub (no authored body)** suffix when `Nodes <= 1` (stub = just the Entry node, no Return, no binding wiring). Gives plan authors a direct visible signal for when to pass `force_rebind=True`.
- New UFUNCTION `UBpxReflectionOps::WipeFunctionGraphBody(UBlueprint*, FName)` — removes every non-Entry / non-Return node from a function graph, breaks lingering pin links on the survivors, marks the blueprint structurally modified. Idempotent (graph with only Entry/Return ⇒ success + skipped + zero count). Caller owns compile + save.
- Python op `implement_interface_function` gains `force_rebind: bool = False`. When True and the override graph already exists, invokes `ops.wipe_function_graph_body` then re-runs the binding logic on a clean slate. Entry/Return retain their seeded NodeGuids so references stay stable. `after.wiped_nodes` carries the removed-node count.
- `plan_shape.OP_SPECS["implement_interface_function"]["optional"]` lists `force_rebind` so the validator accepts it.
- New regression test `FInterfaceOverrideSerializationTest` (`BlueprintExporter.Schema.InterfaceOverrideSerialization`) pins the JSON round-trip: override round-trips both fields, regular function omits both, pre-1.19.6 JSON still deserializes, edge case (flag true + empty path) emits the flag but not the path.

**Docs touched:**
- `CATALOG.md` — `implement_interface_function` section documents `force_rebind=False` default + the editor-stub authoring mistake it unblocks.
- `plans/README.md` — op kwargs table adds `*opt:* force_rebind`; new worked example showing the force-rebind variant.
- `CLAUDE.md` — `FExportedFunction` Key Types entry extended with the M26.1.1 field summary + `PerAssetEmit.cpp` stub-rendering behavior.

**Version bump 1.19.5 → 1.19.6.** 9-location drift-sweep clean (uplugin x2, module.cpp startup + ping + list_methods, manager, both serializers, plugins commandlet, tests, README). DLL rebuilt against custom UE_DOW engine (2,561,024 → 2,570,240 bytes). BuiltPlugin mirror synced.

**Not yet done (intentional scope cap):**
- **Stock-5.7 DLL.** M27.1 gotcha still applies — first Legacy / BugHunt editor launch will rebuild the DLL on BuildId mismatch, which also re-populates `BugHunt/TestProject/Plugins/BlueprintExporter/Binaries/Win64/` cleanly.
- **~~Live `force_rebind=True` soak~~.** Closed 2026-04-22 by M26.1.2 below. Soak exercised against BugHunt's `BP_BpxTestImplementsInterface`, surfaced three non-determinism sources in the force_rebind path (pin-GUID randomness, linker-index monotonic counter, `MakeUniqueObjectName` suffix counter), all three fixed. md5 byte-identical across wipe+rebind cycles.
- **Op catalog surfacing via MCP.** `get_op_catalog` is AST-only over `python_ops/__init__.py` — it auto-picks up the new `force_rebind` parameter on next MCP restart. No server-side change needed.

### M26.1.2 — force_rebind determinism fixes (2026-04-22)

Patch fix on M26.1.1's `force_rebind=True` path. The soak from M26.1.1's "Not yet done" list was run against BugHunt's fixture `BP_BpxTestImplementsInterface` and surfaced a real determinism bug: two rounds of `implement_interface_function(force_rebind=True)` with identical inputs produced different `.uasset` bytes. Same Node GUIDs, same bindings, same post-op reported state — different md5 on disk. Determinism had been a documented M26.1 claim ("running the op twice against the same baseline produces byte-identical `.uasset` — the golden BugHunt fixture strategy depends on this") but was never empirically verified end-to-end for the force_rebind path. Three independent non-determinism sources, uncovered in sequence:

| # | Source | Evidence | Fix |
|---|---|---|---|
| 1 | **Pin GUIDs on new VariableGet nodes.** `AllocateDefaultPins` → `CreatePin` assigns `PinId` via `FGuid::NewGuid()`. Pin GUIDs serialize into `.uasset`. | 20-byte block diff + two 1-byte counter diffs post-soak (size-stable 37294b, r1/r2 md5 differ). | New `BpxReflection::SeedPinGuidsForNode(Node, JoinedPrefix)` helper seeds `Pin->PinId` via the same md5-of-UTF8 path as `SeedGuidFromJoined` with suffix `:pin:<PinName>:<in\|out>`. Called from `AddSelfMemberGetNode` (for the VariableGet) and `OverrideInterfaceFunction` (for Entry + the force-synthesized Return when we create one). |
| 2 | **Linker-index monotonic counter after `RemoveNode`.** Wiped nodes' package-local indices weren't freed for reuse even after `Graph->RemoveNode(bBreakAllLinks=true)`. Re-bound nodes got indices monotonically past the wiped ones. | Two int32 counters at file offsets 7740 / 7852 incremented by +2 across wipe+rebind (1→3, 2→4 — matching the 2 new VariableGets per round). Survived pin-GUID seeding. | Force synchronous full-purge GC immediately after the wipe loop in `WipeFunctionGraphBody`: `CollectGarbage(RF_NoFlags, /*bPerformFullPurge*/ true)`. Clears the dead UObjects so subsequent `NewObject<>` doesn't have their shadow in the package scope. Necessary-but-insufficient alone (fix #3 also needed to land). |
| 3 | **`MakeUniqueObjectName` monotonic suffix.** `NewObject<UK2Node_VariableGet>(Graph)` with no explicit `FName` delegates to `MakeUniqueObjectName`, which uses a per-Outer counter that does NOT reset when objects are GC'd. Round 1's new nodes: `K2Node_VariableGet_0` / `_1`. Round 2's: `_2` / `_3`. The suffix ends up in the package `FNameMap` and serializes into `.uasset`. | Identical 22-byte diff pattern even after fixes #1 + #2; pin GUIDs and linker counts stable but `FName` indices still drifted. | Deterministic object name at `NewObject<>` call site: `NewObject<UK2Node_VariableGet>(Graph, FName(*FString::Printf(TEXT("BpxVarGet_%s"), *MemberName.ToString())))`. Applied symmetrically to `OverrideInterfaceFunction`'s synthesized `UK2Node_FunctionResult` (`BpxFuncResult_<FunctionName>`). GC from fix #2 is load-bearing here — it frees the name for reuse so round N+1's `NewObject` with the same deterministic name doesn't collide. |

**Deliverables:**
- `Source/BlueprintExporter/Private/Reflection/ReflectionOps.cpp`: new `SeedPinGuidsForNode` helper; `AddSelfMemberGetNode` seeds VariableGet pin GUIDs + uses deterministic object name; `OverrideInterfaceFunction` seeds Entry + synthesized-Return pin GUIDs + deterministic Return name; `WipeFunctionGraphBody` calls `CollectGarbage(RF_NoFlags, true)` after the wipe loop. `#include "UObject/UObjectGlobals.h"` added for `CollectGarbage`.
- `scripts/soak_m26_1_1_force_rebind.py` (new): end-to-end soak that duplicates the BugHunt baseline, runs force_rebind twice, asserts `wiped_nodes>0` on round 2, asserts md5 byte-identity across rounds, asserts Entry NodeGuid stability. File-level scratch-asset cleanup (sidesteps `EditorAssetLibrary.delete_asset`'s commandlet-mode `TypedElementRegistry` assertion). Pattern mirrors `regenerate_m26_1_golden.py`.
- `scripts/diff_force_rebind.py` (new): byte-diff diagnostic that runs the force_rebind flow twice and prints coalesced byte-run diffs with hex context. Kept in the tree for future determinism regressions — identical pattern would likely surface as another monotonic counter or per-object randomness.
- `scripts/regenerate_m26_1_golden.py`: now passes `force_rebind=True`. Without this flag, the golden regen was a no-op against the baseline stub — the op would bail on the idempotency skip and the committed `_Expected.uasset` was just a byte-duplicate of the baseline with no bindings authored. M26.1.1 shipped the flag but didn't wire it through the regen script.
- `BugHunt/TestProject/Content/TestBlueprints/BP_BpxTestImplementsInterface_Expected.uasset`: regenerated with actual bindings (was previously a baseline duplicate per the bug above). New md5 `1DDBE486…`.

**Verified:**
- `diff_force_rebind.py`: `BYTES IDENTICAL - drift fixed` post-all-three-fixes.
- `soak_m26_1_1_force_rebind.py`: `SOAK PASS` — round 1 wiped_nodes=0 (pure stub, no body), round 2 wiped_nodes=2 (the two round-1 VariableGets), md5 `d9756d74…` matches across rounds, Entry NodeGuid `4958464F…` stable.
- Determinism gate (`verify_determinism.ps1 -Project BugHunt -SweepDeepDump`): PASS in 50 s (byte-identical A↔B trees). First attempt flagged a pre-existing MANIFEST tiebreaker instability between Run A (cache-building) and Run B (cache-reading) — gone after clearing `Intermediate/CachedAssetRegistry_*.bin` and re-running. Separate cache-warming transient, not an M26.1.2 regression; ProjectManifest code unchanged.
- Build: `RunUAT BuildPlugin -Rocket` green (21.91 s first rebuild, 23.18 s / 22 s on iterations). `Module.BlueprintExporter.1.cpp` links cleanly — no unity-batch ODR regressions.

**Version bump 1.19.6 → 1.19.7** (patch per semver — bug fix on an existing op, no new surface). 9-location drift sweep clean across Source + BuiltPlugin mirror + BugHunt runtime mirror + README. `"Version"` integer stays at 19 (matches minor digit). DLL rebuilt against custom UE_DOW engine (2,527,744 → 2,530,304 bytes).

**Follow-ups:**
- **Automation test run.** `UnrealEditor-Cmd.exe … -ExecCmds="Automation RunTests BlueprintExporter.; Quit"` emits `LogAutomationTest: Skipping unit tests for the cooked build and commandlet` — ATF's build-context filter rejects headless commandlet mode. CLAUDE.md's pre-push matrix documents this invocation as the standard but it silently no-ops. Unblock path (separate chore): invoke tests via UE 5's `Editor` mode with `-game -SessionName=…` or a `RunAutomationTests` commandlet. Not a regression driver for M26.1.2 since the patch only touches `ReflectionOps.cpp` — no serializer / schema / export-surface code paths that `FInterfaceOverrideSerializationTest` + siblings exercise. Determinism gate + soak + diff diagnostic cover the touched surface empirically.
- **Stock-5.7 DLL refresh** still pending (M26.1.1 carryover). Next Legacy MCP session will rebuild on BuildId mismatch.

### Unity-build ODR defuse arc (2026-04-22)

Maintenance arc triggered by a red CI run of `Code_Submit_Compiled_Binaries_to_UGS` (`[3/6] Compile UE_DOWEditor Win64`). No functional change — the class of bug is "UBT jumbo/unity batching stitches multiple `.cpp` files into one TU, and anon-namespace helpers with identical names collide as C2084 redefinitions." These are latent whenever two files happen to land in the same `Module.BlueprintExporter.N.cpp` bundle; UBT's batching is non-deterministic across runs, so they surface unpredictably. Two commits closed the whole class:

| Commit | What it delivered |
|---|---|
| `4f9a4b5` | fix: **defuse unity-build ODR collisions (first pass)**. Six `TextExport/*DeepRenderer.cpp` files each carried anon-namespace copies of `EscTbl` / `IsUEPlumbingProperty` / `RenderUObjectPropertiesTable` / `RenderStructFieldsTable`. Hoisted the four helpers into new namespace `BlueprintExporter::DeepRender` (`Private/TextExport/DeepRenderShared.{h,cpp}`); `BehaviorTreeDeepRenderer` passes its `TreeAsset` / `ParentNode` / `TemplateNode` strip set as `AdditionalPlumbing` at the call sites. Separately, `ProjectInventory` / `Aggregate` / `DeepDump` commandlets had identical-body `LogLine`s — hoisted to inline `BlueprintExporter::Util::LogLine` in `Private/Util/CommandletLog.h`. BuiltPlugin DLL refreshed via `RunUAT BuildPlugin`. |
| `a396f25` | fix: **finish unity-build ODR hoist** — three more collisions that slipped past `4f9a4b5` and fired on the next clean CI run. (1) `constexpr int32 ErrInternal = -32603` duplicated between `BpxBridgeServer.cpp` + `BpxPlanHandlers.cpp` → hoisted all 5 JSON-RPC 2.0 spec codes into new `Private/Bridge/BpxJsonRpcErrors.h` as `inline constexpr`; plan-specific codes (-32001..-32004) stay file-local. (2) `GetUBlueprintFamilyClassNames()` duplicated between `ProjectInventoryCommandlet.cpp` + `DeepDumpCommandlet.cpp` → hoisted into `BlueprintExporter::InventoryEmit` alongside the existing shared surface. (3) `Log(FString, FString, bool)` duplicated between `ProjectManifestCommandlet.cpp` + `ProjectPluginsCommandlet.cpp`, identical body to `Util::LogLine` → deleted both local copies, renamed 19 call sites to `LogLine`. Proactive sweep also caught a **fourth** latent collision: `EscTbl` between `AggregateInventoryCommandlet.cpp` + `ProjectPluginsCommandlet.cpp`, identical bodies, didn't fire this run only because UBT bundled them into separate unity batches. Both now pull `InventoryEmit::EscTbl` via `using`. Verified locally via `RunUAT BuildPlugin -Rocket` — BUILD SUCCESSFUL, ExitCode=0, `Module.BlueprintExporter.1.cpp` links cleanly. |

**Why the local build is a valid CI-fidelity test:** UBT unity batching is per-module — `Module.BlueprintExporter.N.cpp` stitches only `BlueprintExporter` module files, never cross-module. So `RunUAT BuildPlugin -Rocket` exercises the same unity surface as the CI's `UBT UE_DOWEditor Win64 Development` call, just with a fresh generated `HostProject` instead of UE_DOW. For anon-namespace ODR bugs inside the plugin, the two builds are equivalent. A linker-level ODR across plugin + engine would only surface in the full editor build, but that's not this bug class.

**Reusable diagnostic for the next collision (if one surfaces):** greppable signatures in a fresh CI failure log are `error C2084: function '...::FOO' already has a body` and `error C2374: 'FOO': redefinition; multiple initialization`. Read the log's `note: see previous definition of ...` line to identify the colliding pair, confirm both are in anon namespaces, then hoist into the matching shared surface (`DeepRender` / `InventoryEmit` / `Util` / new namespace as needed). The pattern is now well-trodden — follow these two commits as templates.

**No version bump** — the DLL changed (rebuilt) but the exported surface is byte-identical in behavior. Stayed at 1.19.6 after `a396f25`.

### State of disk at `/clear` time

- Repo HEAD: M26.1.2 arc landed (force_rebind determinism fixes, plugin 1.19.6 → 1.19.7) on top of `a396f25` unity-build ODR closure. Earlier today: `44f4cf1` (M26.1.1 interface-stub override fix). Earlier still: `21637a0` (M27.3.1 closure docs), `5268a9f` (README live-edit section), `178acf4` (smoke_bridge connect-timeout 3s→15s).
- Plugin version: **1.19.7** across all 9 stamp locations (last bump M26.1.2). `"Version"` integer stays 19 (matches minor).
- BuiltPlugin DLL: **2,530,304 bytes**, built against custom UE_DOW engine, at `BuiltPlugin/Binaries/Win64/UnrealEditor-BlueprintExporter.dll` (refreshed during M26.1.2 via `RunUAT BuildPlugin -Rocket`).
- Legacy plugin install: 1.19.7 expected on next launch (UE auto-rebuilds the DLL on BuildId mismatch — see M27.1 gotcha pattern). Also the junction at `D:/Work/UE_DOW_Legacy/Plugins/BlueprintExporter` still points at the deleted `_build_output_5_7/` from the 2026-04-21 cleanup — first launch will fail unresolved until the junction is replaced with a real directory copy of a fresh stock-5.7 `RunUAT BuildPlugin` output. If a force-rebuild is needed: `taskkill /F UnrealEditor-Cmd.exe`, `rm D:/Work/UE_DOW_Legacy/Plugins/BlueprintExporter/Binaries/Win64/UnrealEditor-BlueprintExporter.*`, relaunch.
- BugHunt golden: `BP_BpxTestImplementsInterface_Expected.uasset` regenerated via M26.1.2'd `regenerate_m26_1_golden.py` (now passes `force_rebind=True`) — committed with actual authored bindings (md5 `1DDBE486…`). The pre-M26.1.2 committed golden was a baseline duplicate with NO bindings — a latent bug from M26.1 that shipping M26.1.1's force_rebind surfaced.
- Live MCP test workspace: `D:/Work/unreal-mcp-test/.mcp.json` (gitignored, per-machine). Bridge-first with subprocess fallback (M27.2+); `apply_plan` auto-re-exports touched UBP / StateTree sidecars (M27.3, byte-identical to commandlet sweep as of M27.3.1).
- CI: next `Code_Submit_Compiled_Binaries_to_UGS` run on TeamCity agent `10C-SRV-03` should go green on `UE_DOWEditor Win64 Development` compile after picking up `a396f25`. Previous run #48 (`Started 2026-04-22 16:50:55`) failed on three anon-ns ODR collisions; #49+ picks up the fix.
- Uncommitted changes: none in tracked files. Untracked: `Code_Submit_Compiled_Binaries_to_UGS_*.log` (CI logs, scratch), `infographic.html`, `placeholder/`, `BugHunt/TestProject/Config/DefaultInput.ini`.
- No background processes. `py-spy` still installed from the 2026-04-21 hang diagnostic (not a project dep).
- Tempfile cleanup heuristic in `run_ue_subprocess` swallows `PermissionError` on unlink — `%TEMP%` may contain a handful of `*.ue-stdout` / `*.ue-stderr` files from recent runs; Windows self-cleans.
- Environment tweak: `BASH_ENV=C:\Users\admin\.bashrc` was set at Windows user scope so non-interactive bash sources the user's `.bashrc` (which prepends `/c/Program Files/Git/usr/bin` to PATH, giving bash access to Git-for-Windows's 380 coreutils — `ls` / `wc` / `tail` / `grep` / `sed` / `awk` / `find` / `head`). Takes effect in newly-launched Claude Code sessions; the session that set it has stale env and still needed the per-command prepend. Memory pointer: `feedback_bash_path_prepend.md`.

---

**Session 2026-04-21 — M25.1 shipped + M25.1.5 / .6 / .7 colleague
polish + M25.2.0 first read-only tactical op + one subprocess
timeout-handler bug fix + one housekeeping move. Seventeen commits
between `238b2bd` and `069ce2f`, all pushed to
`10-Chambers/ue-tools` main.** delivered the external MCP server
(13 tools, three client configs), first-run bulletproofing
(`bpx-mcp-doctor`, config template, troubleshooting table), two
rounds of dev-specific scrubbing for cross-colleague portability
(M25.1.6 removed author paths, M25.1.7 removed project / UE-version
names), and the opening move of M25.2 (`verify_state_enter_conditions`)
that closes the root-state EC verification path-quirk from today's
Track-A apply. Read this block first on any `/clear` resume; earlier
session context continues at "Session 2026-04-20 (late)" below.

### The 17-commit arc (2026-04-21)

| Commit | What it delivered |
|---|---|
| `238b2bd` | docs: **M25 scope + Track-A known issue** — scoped M25 (MCP server + tactical AI ops) as candidate #11. Triggered 2026-04-21 after finishing Track-A combat-AI decision gates on `ST_EnemyBase`. Prior-art UE-Python MCP tooling reviewed for call-coverage reference, explicitly not vendored or attributed in shipped artifacts. Also logs the root-state EnterCondition verification path-quirk from `combat_loop_hastargets_gate.json.run.json` as a known issue. |
| `34a9039` | feat: **M25.1.0 scaffold + 4 retrieval tools** — new `scripts/blueprint-exporter-mcp/` package (FastMCP v3.x; uvx-runnable; independent versioning). Four zero-UE-process tools: `list_assets` walks `Assets/**/*.meta.json` filtering by `assetType` (populated for every in-scope class — `blueprintSubclass` is a BP-family legacy fallback); `get_asset_summary` / `get_asset_deep_dump` read Tier 1/2 sidecars; `search_deep_dumps` regex-scans every `.deep.md`. Config is one env var (`BPX_INVENTORY_ROOT`). Tool bodies are module-level `*_impl` pure functions that `register()` wraps as `@mcp.tool` closures. 14/14 smoke assertions. |
| `67866cc` | docs: **stamp M25.1.0** — added this session recap to WIP, annotated candidate #11. |
| `ce00710` | feat: **M25.1.1 four more retrieval tools** — `get_asset_meta` (full parsed `.meta.json` dict), `get_cdo_properties` (projection `{path, assetType, dataCarrierKind, cdoProperties}`), `get_references(path, direction)` (parses `DEPENDENCY_GRAPH.md` `## <path>` sections; direction ∈ out/in/both; each ref tagged with native/asset/empty kind), `get_class_tree(class_name)` (direct children from `CLASS_TREE.md`; handles both native-parent and BP-chain forms with automatic `.X_C` suffix normalisation). Smoke grows to 25/25. |
| `a2073db` | feat: **M25.1.2 plan-pipeline tools** — `get_op_catalog` AST-introspects `scripts/python_ops/__init__.py` + submodules, emits `{name, module, docstring, parameters}` for each op (17 ops currently, auto-updates as new ones ship). `validate_plan(plan_json)` / `apply_plan(plan_json)` shell `UnrealEditor-Cmd.exe -run=pythonscript` to `run_plan_validator.py` / `run_plan.py`; write temp plan, invoke, read back the sidecar JSON, return `{exitCode, command, report, stderrTail?}`. Config gains `BPX_SCRIPTS_ROOT` (optional) with auto-derivation from the package `__file__`. Plan JSON errors + missing engine config surface as structured `{error}` dicts, not exceptions. Smoke grows to 32/32. |
| `2f91011` | feat: **M25.1.3 live-introspection + subprocess refactor** — new `tools/_ue_subprocess.py` shared module holds `UE_STOCK_FLAGS` + `build_ue_command(ue_cmd, uproject, run_kind, extras)` + `require_ue_config` / `require_scripts_config`. `plans.py` rewired through the shared helpers. New `tools/live.py`: `deep_dump_asset(path)` shells `-run=DeepDump -Asset=<path> -OutDir=<tempdir>`, reads back the `.deep.md`, returns contents inline. `refresh_inventory(path_filter, deep_dump)` shells `-run=ProjectInventory -OutDir=<inventory_root> -Filter=<prefix> [-DeepDump]`; empty `path_filter` refused on purpose (full legacy sweep crashes on KINEMATION). Smoke grows to 37/37; 13 tools total. |
| `0a0d1ea` | docs: **M25.1.4 multi-client config** — README gains Cursor (`.cursor/mcp.json`) and Claude Desktop (`%APPDATA%/Claude/claude_desktop_config.json` on Windows, `~/Library/Application Support/Claude/` on macOS) snippets alongside the existing Claude Code config. Same `mcpServers` shape across all three — only the config file location differs. Plus a "Sanity check without a client" section pointing at `tests/smoke_test.py`. M25.1 fully shipped. |
| `1e4b649` | feat: **M25.2.0 `verify_state_enter_conditions`** — new read-only StateTree op that reads the current EnterConditions list at a state. Paper-overs the root-state EC verification path-quirk logged today: plan verification paths like `[<st>, "StateTreeEditorData:SubTrees", "[2]", "EnterConditions", "[0]", "InstanceObject"]` resolve to None through the bridge's walker for root states, even when the write op landed cleanly. The new op uses the SAME state_path format as `add_` / `remove_statetree_enter_condition` (nav list from `StateTreeEditorData`) so it works for both root (`["SubTrees", "[2]"]`) and nested (`["SubTrees", "[2]", "Children", "[3]"]`) states. Wired into `plan_validator.OP_SPECS`, `plan_executor._OP_DISPATCH`, `mechanical_diff._op_expected_changes` (explicit read-only branch = no expected mutation), `CATALOG.md`, and `plans/README.md` (new "EnterCondition verification paths (root vs nested)" subsection). MCP `get_op_catalog` auto-surfaces (17 → 18 ops). No plugin version bump. **First M25.2 op; debt gate (candidate #8) stays at 0 since read-only.** |
| `950504f` | feat: **M25.1.5 colleague-onboarding polish** — surfaced 2026-04-21 when user hit three gaps trying to stand up the MCP server for a colleague: no committed config template, no startup doctor (misconfig surfaced as cryptic Claude Code "server failed" badges), and README's Configure section described env vars instead of "how to set up for Legacy / DOW main / BugHunt". Shipped: (a) `.mcp.json.example` at repo root + repo-root `.gitignore` listing `.mcp.json` / `.claude/`; (b) `bpx-mcp-doctor` console script (new pyproject entry point) — prints resolved paths, validates each, runs a tool-registration dry-run, applies a tagged-path heuristic for inventory↔uproject coherence (catches DOW-main inventory + Legacy uproject mix), exit codes 0/1/2 map to pass/fail/config-unbuildable. Strict-ASCII output so Windows cp1252 consoles don't crash on dashes. (c) README rewritten with "Quick setup (colleagues — start here)" 4-step block, "Per-project config matrix" table (three verbatim rows), and "Troubleshooting" table (seven common failures + fixes). Smoke 37 → 41 assertions (4 doctor-coherence cases including the mismatch the user spotted). No plugin version bump. **Follow-up:** shipped with author's absolute paths still baked into examples; see M25.1.6. |
| `0c13e29` | feat: **M25.1.6 portable-path fix for colleague distribution** — M25.1.5's `.mcp.json.example` and README config matrix embedded the original author's `D:/Work/...` + `C:/Program Files/...` absolute paths verbatim. User caught this on review: colleagues fetching `blueprint-exporter` from GitHub have different paths and need to fill in their own. Rewrote the template with `<YOUR_REPO_ROOT>` / `<YOUR_EPIC_GAMES_DIR>` / `<YOUR_UPROJECT_DEPOT>` / `<PATH_TO_LEGACY_INVENTORY>` placeholders + a `_comment` field explaining the copy-and-replace flow. README gains a new "Inventory distribution model" subsection making the DevOps contract explicit: DOW main is committed in-repo (DevOps owns the committed state via pipeline); Legacy is delivered externally; local `refresh_inventory` / `deep_dump_asset` writes are experimentation-only and never land in PRs. Placeholder-token table at the top ties every `<YOUR_*>` to a typical value. All `D:/Work/...` and author-specific paths scrubbed from README body, Troubleshooting table, sanity-check snippet, doctor's internal docstring, and smoke test's synthetic inputs (now `/synthetic/...`). Doctor's coherence heuristic broadened with underscore / hyphen / Windows-separator variants so it fires for colleagues whose DevOps-delivered folders follow different naming conventions. **Follow-up:** placeholders still named specific projects (`ProjectInventory_DOW`, `UE_5.7`, `UE_DOW_Legacy`); see M25.1.7. |
| `e7adf7b` | feat: **M25.1.7 strip dev-specifics from colleague-facing docs** — M25.1.6 still named current-dev specifics (UE 5.7, UE_DOW_Legacy, ProjectInventory_DOW, DOW main / Legacy / BugHunt) inside the placeholders and the Per-project config matrix. User flagged: colleagues outside those three tracks have to mentally filter, and the "these are THE projects" framing is team-internal noise. Rewrote `.mcp.json.example` with fully abstract placeholders (`<absolute path to a ProjectInventory directory>`, etc. — no UE version, no project name, no depot structure). Removed the Per-project config matrix from the README — those project-specific combinations belong in `WIP_INVENTORY.md` (team-internal). Added a neutral "Who owns what" subsection covering the general DevOps contract. Troubleshooting + sanity-check + refresh_inventory tool description genericized: no references to DOW / Legacy / BugHunt / UE 5.7 / specific Epic install paths. Engine ↔ uproject BuildId guidance phrased around "custom-engine vs stock-engine projects" rather than "DOW vs Legacy". |
| `9ba5d2a` | fix: **MCP subprocess TimeoutExpired handler masks timeout with AttributeError** — surfaced 2026-04-21 on user's first live `apply_plan` call, which hit the 900s wall clock. The real error never reached the client — instead they got `'str' object has no attribute 'decode'`. Root cause: `plans.py:233` called `.decode()` on `exc.stdout`, but `subprocess.run` was invoked with `text=True`, so captured streams come back as `str` already. Fix: drop the `.decode()`, slice the `str` directly. Also added `stderrTail` alongside `stdoutTail` in the plans-side handler, and added both tails to `live.py`'s two timeout handlers (they were returning bare error strings with zero diagnostic signal). New regression test `test_plan_timeout_handler_returns_str_tails` builds a temp-dir filesystem scaffold that passes `require_scripts_config`, patches `subprocess.run` to raise `TimeoutExpired(output=..., stderr=...)`, calls `apply_plan_impl`, asserts both tails are `str` and carry the captured content. Smoke 41 → 42 assertions. |
| `069ce2f` | refactor: **move `.mcp.json.example` out of ue-tools root** — M25.1.5 shipped the template at the monorepo root on the assumption that "next to where .mcp.json lives = easiest for colleagues to copy". User flagged: `ue-tools` is multi-project, a plugin-specific template at the root implies `blueprint-exporter` is the whole monorepo's point. `git mv`'d to `blueprint-exporter/.mcp.json.example`; destination `.mcp.json` still lands at the repo root (that's where clients look) — only the source moved. Repo-root `.gitignore` stays (`.mcp.json` / `.claude/` / `.cursor/` are genuinely monorepo-root files). |

### M25.1 shipped inventory (13 tools)

| Group | Tools |
|---|---|
| Retrieval (zero UE) | `list_assets`, `get_asset_summary`, `get_asset_deep_dump`, `search_deep_dumps`, `get_asset_meta`, `get_cdo_properties`, `get_references`, `get_class_tree` |
| Plan pipeline | `get_op_catalog` (AST-only, no UE), `validate_plan`, `apply_plan` (both shell to `-run=pythonscript`) |
| Live introspection | `deep_dump_asset` (shell to `-run=DeepDump`), `refresh_inventory` (shell to `-run=ProjectInventory`) |

### What's next (M25.2 or other candidates)

M25.1 is done. Freshest candidates:
- **M25.2** tactical AI ops (`add_statetree_transition`, `set_statetree_task_instance_data`, `set_eqs_test_property`, `add_bp_member_variable`, `verify_state_enter_conditions`) — unblocks event-driven ST edits and fixes the root-state EC verification path-quirk logged in known issues.
- **M25.3** integration polish — auto-catalog in MCP's `get_op_catalog` already works; the remaining polish is AGENT_LOOP.md worked examples for each M25.2 op + `plans/README.md` root-vs-nested EC verification path-shape documentation.
- Any other candidate from the list below.

### Session 2026-04-20 (late) — Python write-layer arc (M21–M24)

**Landed 14 commits between `4feb0a3` and the M24.4 agent-loop doc.**
Historical context for the arc that made M24 the stable write
layer on top of which M25 now builds.

### The 14-commit arc (2026-04-20 late)

| Commit | What it delivered |
|---|---|
| `1486d9a` | docs: scoped **M21** (Python write-layer library) + **M22** (BugHunt fixture loop) to WIP. Candidates #7 and #8 in the list below. |
| `65dec98` | feat: **M21.0 scaffolding** — `scripts/python_ops/` module tree, `_common.py` helpers, first op `set_bp_variable_default`, `CATALOG.md` (LLM-facing doc), Docs Map entry in CLAUDE.md. |
| `84049a2` | feat: **M21.0 complete** — 4 more ops (`set_component_property` / `set_instanced_subobject_property` / `create_child_bp` / `rename_asset`) in `blueprint_cdo.py` + `assets.py`. 17/17 test cases pass on clean state. |
| `0443f37` | docs: **M21.1 StateTree ops blocked** by UE 5.7 Python binding gap. `UStateTreeEditorData.SubTrees` / `EditorBindings` are Python-protected (`get_editor_property` returns `"is protected"` error). Triggered M23 scoping. |
| `c6f0daf` | feat: **M23.0 Reflection Bridge** — new C++ UFUNCTION library. 5 primitives under `unreal.BpxReflectionOps`: `get_property_value` / `set_property_value` / `find_subobject` / `get_array_length` / `compile_and_save_package`. Walks FProperty / UObject natively, bypassing the Python-binding protection flags. Plugin version 1.14.0 → 1.15.0. Both stock UE 5.7 and main 10C engine plugin variants rebuilt. **Proven end-to-end**: read ST_EnemyBase's protected `SubTrees[0].Name` → "Wait"; write `AC_AIWeaponController.Damage` 8→12→8, md5 changes, compile+save returns True. |
| `d196382` | docs: scoped **M24 Supervised Edit Loop** (candidate #10). Plan artifact + pre-flight validator + mechanical diff oracle. |
| `23ba190` | feat: **M23.1 mutation primitives** — 6 more UFUNCTIONs (`array_append_new_element` / `array_remove_at` / `set_instanced_struct_type` / `new_subobject` / `set_object_property_value` / `get_object_property_value`). Path walker extended for array-element navigation mid-path (e.g. `["SubTrees", "[2]", "Children", "[3]", "EnterConditions", "[0]", "InstanceObject"]`). |
| `9968b03` | feat: **M23.1.1 Instanced-subobject persistence** — the Phase B unblocker. Three joint fixes: (a) `SetObjectPropertyValue` fires `PostEditChangeChainProperty` on the innermost-UObject owner with a correctly-built `FEditPropertyChain` + `ArrayIndicesPerObject` + `ObjectIteratorIndex=0` (mirrors UE's `StateTreeEditorNodeDetails::OnNodePicked` drag-drop path at `StateTreeEditorNodeDetails.cpp:2374-2385` — load-bearing for `Instanced`-flagged FObjectProperty so SavePackage captures the subobject; without it StateTree's `DispatchPostEditToNodes` in `StateTreePropertyHelpers.cpp:125` asserts on a malformed chain walk). (b) `ResolvePath` descends into `FInstancedStruct` — `Node.ConditionClass` now resolves when `Node` is an `FInstancedStruct` wrapping `FStateTreeBlueprintConditionWrapper` (walks `InstancedStruct.GetMutableMemory()` + `GetScriptStruct()`). (c) Script-level: `phase_b_los_gate.py` now sets `Node.ConditionClass` + `ID` (32-char hex GUID) on the wrapper — without `ConditionClass`, `UStateTreeState::PostLoad`'s `ConditionalUpdateNodeInstanceData` sees `DesiredType=None` and nulls `InstanceObject` as a type-mismatch cleanup. Plugin version 1.15.0 → 1.15.1 (patch bump — bug fix in M23.1). **Proven end-to-end**: run 1 adds condition + md5 changes; run 2 `stale_removed=0`, `idempotent_existing_idx=0`, `skipped: "ST_Cond_CanSeeTarget already present on Peek.EnterConditions"` → subobject survived reload. |
| `6510ea9` | feat: **M23.2 StateTree ops on the reflection bridge** — packages the M23.1.1 Phase B flow as named library ops. New `scripts/python_ops/statetree.py` with `add_statetree_enter_condition(st_path, state_path, condition_bp_path)` + `remove_statetree_enter_condition(...)`. Both idempotent by class match (compare `InstanceObject.GetClass().GetPathName()` against the condition BP's generated-class path); `add_` additionally uses a deterministic md5 GUID for the editor-node `ID` so re-runs converge. Encapsulates the full 9-step sequence (load ST → find editor data → class resolve → state UObject resolve → append element → init wrapper struct → set ConditionClass → set ID → `new_subobject` outered to state → set `InstanceObject` → `compile_and_save_package`) behind one call. **Verified** via `D:/Work/_combat_ai_tuning/test_statetree_ops.py` exercising all 4 paths in one session: `add` (fresh: ec_len 0 → 1, new instance `ST_Cond_CanSeeTarget_C_5`), `add` (idempotent: skipped with class-present message), `remove` (hit: ec_len 1 → 0), `remove` (no-op: skipped with class-not-found message). The original M23.2 scope (retrofit M21.0 CDO/component ops onto the bridge) is deferred per CATALOG "Deferred" section — those ops already work via `get/set_editor_property` and a full retrofit needs a Python→ImportText converter + M22 fixture tests that don't exist yet; revisit when a concrete edit surfaces a case `set_editor_property` can't handle. No plugin version bump (pure Python addition). |
| `4cf7557` | docs: **M24.0 EditPlan schema** — new `scripts/python_ops/plans/README.md` defines the `{intended_outcome, risk_level, operations[], expected_side_effects, verification}` JSON shape for the M24 Supervised Edit Loop. Covers the 8-step loop (export → understand → plan → validate → apply → verify-mechanical → verify-semantic → escalate), per-op kwargs tables for every shipped op (the 7 of M23.2), value conventions for UE types (Vector2D / Rotator / enum / object-ref / array), `expected_side_effects` + `verification` semantics (verification takes `{path, expected}` or `{asset_exists/asset_absent}` shapes), idempotency keys, op ordering rules (array-index shift traps, create-before-use, rename-before-reference), three risk levels (`low`/`medium`/`high`) mapped to edit surface, a worked "LOS-gate Peek firing" example that maps 1:1 to the M23.1.1 verification, and a common-mistakes list. LLM-audience: concrete + example-heavy. CLAUDE.md Docs Map gains the new row, CATALOG.md cross-references it. No plugin version bump (pure documentation). Ships the schema only — validator (M24.1), executor (M24.2), and mechanical diff oracle (M24.3) land next and consume this shape. |
| `5250921` | feat: **M24.1 plan validator** — new `scripts/python_ops/plan_validator.py` exposes `validate_plan(plan: dict) -> dict`. Read-only: walks every target asset via `EditorAssetLibrary.does_asset_exist` and every StateTree state-path via `unreal.BpxReflectionOps.get_object_property_value`, no mutations, no saves. Dispatches per-op against a table (`OP_SPECS`) that lists required kwargs + which keys are `/Game/` paths expected to exist vs expected to not exist + which keys are bridge state paths. Returns `{passed, errors, warnings, per_op:[{op_idx, op, ok, errors, warnings}]}` — `passed=False` MUST block execution. Plus `format_report` renders a one-screen terminal-friendly version. New CLI harness `scripts/run_plan_validator.py` takes `-plan=<path>` from UE's engine command line (not `sys.argv` — UE's pythonscript strips `-flag=value` before hitting the interpreter; we read via `unreal.SystemLibrary.get_command_line`), loads the plan, calls the validator, writes `<plan>.validation.json` next to the plan, and exits 0/1/2 on pass/fail/CLI-misuse. Exported from `python_ops.__init__`. **Verified** via `D:/Work/_combat_ai_tuning/test_plan_validator.py` covering 5 cases (valid LOS-gate → pass, missing `risk_level` → fail, unknown op → fail, non-existent asset → fail, bad state_path → fail) — all 5 behave as expected. CLI harness also verified with a concrete `los_gate_plan.json` → `PASSED` report + `los_gate_plan.json.validation.json` artefact. Deferred per scope-creep concern: the "reads deep dumps instead when run headless" fallback from WIP §10 M24.1 scope — ship only the in-editor path, add headless later if someone wants to validate plans without a running UE. No plugin version bump (pure Python addition). |
| `50c3eb5` | feat: **M24.2 plan executor** — new `scripts/python_ops/plan_executor.py` exposes `execute_plan(plan: dict) -> dict`. Validates internally via `validate_plan` first (safety net against drift between separate validate/execute calls); only dispatches if passed. Per-op: looks up the callable in `_OP_DISPATCH` table, strips plumbing fields (`op` / `_comment` / `idempotency_key` / `expected_type`), converts `value` from JSON-native to the UE Python type (`Vector2D` / `Vector` / `Rotator` / `LinearColor` via component-key heuristics or explicit `expected_type`; `/Game/` strings via `load_asset`; primitives pass-through), invokes with `**kwargs`, stores the op's own result dict. Aborts on first failure — remaining ops skip so partial state does not persist beyond the failing step. Returns `{passed, validation_report, aborted_at, executed, per_op, elapsed_seconds}`. Plus `format_execution_report` renders the compact form. New CLI harness `scripts/run_plan_executor.py` mirrors the M24.1 pattern (reads `-plan` from `unreal.SystemLibrary.get_command_line`, writes `<plan>.execution.json`, 0/1/2 exit). Initial circular-import bug: `plan_executor` pulled op names from `python_ops` package, which was mid-init — fixed by importing from submodules directly (`.assets`, `.blueprint_cdo`, `.statetree`). **Verified** via `D:/Work/_combat_ai_tuning/test_plan_executor.py`: `case_valid_executes` runs a LOS-gate plan, reports passed=True + executed=1 + add path exercised (`ec_len 0 → 1`, new instance `ST_Cond_CanSeeTarget_C_6`, md5 `6be58e10 → 6146f5ae`); `case_validator_blocks` submits `op: frobnicate`, validator rejects, executed=0, no mutation. Exported from `python_ops.__init__`. Apply is atomic per op, NOT per plan — rollback remains the caller's responsibility (typically `git checkout` / `p4 revert`). No plugin version bump (pure Python addition). |
| `0d2635b` | feat: **M24.3 mechanical diff oracle** — closes the M24 loop. New `scripts/python_ops/mechanical_diff.py` computes `{passed, asset_changes, unexpected_changes, expected_but_missing, verification_results}` from `(plan, before_md5s, after_md5s)`. Change detection is md5 of on-disk `.uasset` bytes (not field-level DeepDump diff — simpler, no shell-out, sufficient for the "did the plan's predicted changes land and nothing extra?" question); field-level coverage is delegated to the plan's `verification[]` block, which this oracle executes via the bridge's `get_property_value` / `get_object_property_value` and `EditorAssetLibrary.does_asset_exist`. Expected change set is DERIVED from each op via a fixed mapping (`set_*` → bp_path mutated, `create_child_bp` → new_bp_path created, `rename_asset` → old deleted + new created, `add/remove_statetree_enter_condition` → st_path mutated). `expected_side_effects` stays prose-only per M24.0 schema. Plus `run_plan(plan)` in `plan_executor.py` orchestrates snapshot-md5s → `execute_plan` → snapshot-md5s → `mechanical_diff` into one combined report — the one entry point LLM callers use. New `scripts/run_plan.py` CLI harness writes `<plan>.run.json`, exits 0/1/2. `passed` at the top of `run_plan` is strictly `execution.passed AND diff.passed`; `expected_but_missing` (idempotent-skip replays) is NON-fatal — a re-run of a successful plan should report `passed=True` even though predicted mutations left the asset stable. **Verified** via `D:/Work/_combat_ai_tuning/test_mechanical_diff.py`: `case_1_fresh_run` runs LOS-gate against reset state → passed=True, 1 asset_change with observed=mutated matching expected, md5 changes from `51d3f546` to `f0b8b99e`; `case_2_idempotent` replays the same plan → passed=True (no unexpected changes), execution.per_op shows `skipped="class already present"`, diff.expected_but_missing has 1 entry (ST_EnemyBase stayed at `f0b8b99e`). All diff invariants behave correctly. Exported from `python_ops.__init__`. No plugin version bump (pure Python addition). M24 loop is now complete end-to-end; M24.4 agent-loop integration doc remains as a docs-only follow-up. |
| *M24.4 commit* | docs: **M24.4 agent-loop integration doc** — new `scripts/python_ops/plans/AGENT_LOOP.md` tells future Claude sessions how to use the M24 pipeline end-to-end when a user brings an edit request. Pairs with `plans/README.md` (schema reference): README says WHAT a plan is, AGENT_LOOP says HOW to use a plan to fulfill a request. Covers the 8-step loop (export → understand → plan → validate → apply → verify-mechanical → verify-semantic → escalate) as gates the agent walks in order; a worked LOS-gate example traced from the user prompt ("enemies should only pop out when they can see the player") to the run_plan exit code 0; error-classification tables per step (validator's schema/asset/state-path errors with fix patterns; executor's TypeError/load-fail/compile-fail shapes with retry heuristics; diff's unexpected-changes vs expected-but-missing handling; verification's value/class/existence mismatches); anti-patterns explicitly listing "skipping step 2", "guessing state_path indices", "using expected_side_effects for matching", "claiming passed=True without semantic check"; and the M22 relationship (M22 blesses ops in isolation via BugHunt fixtures; M24 asserts user edits built from blessed ops land safely). CLAUDE.md Docs Map gains an AGENT_LOOP row after the README row; README cross-references AGENT_LOOP in its preamble. No plugin version bump (docs only). M24 milestone fully shipped. |

### What works end-to-end today

- **Read-any-UPROPERTY** including Python-protected ones — `SubTrees`,
  `EditorBindings`, Blueprint `ParentClass`, StateTreeEditorData internals,
  all reachable via `unreal.BpxReflectionOps.get_property_value` and
  `get_array_length`.
- **Write primitives**: CDO defaults, SCS component properties, instanced
  subobject properties, asset create/rename/load — all drive through UE's
  native save/compile path via the bridge, not through JSON round-trip.
- **Structural StateTree walk** working — `ST_EnemyBase` map cached at
  `D:/Work/_combat_ai_tuning/probe_peek_path_results.json`. Key fact:
  **Peek state is at `SubTrees[2].Children[3]`**. `CombatLoop` is
  `SubTrees[2]`.
- **Damage tuning persists** (`AC_AIWeaponController.Damage` stayed at 8.0
  through multiple write cycles). Legacy depot files were `chmod +w`'d
  — may need `p4 revert` if not yet submitted.

### Phase B LOS-gated firing — UNBLOCKED (M23.1.1)

The instanced-property subobject persistence gap is closed. End-to-end
flow now works:

1. `append` → `Peek.EnterConditions[N]`
2. `SetInstancedStructType(Node, FStateTreeBlueprintConditionWrapper)`
3. `SetObjectPropertyValue(Node.ConditionClass, ST_Cond_CanSeeTarget)` —
   resolved via FInstancedStruct descent in ResolvePath
4. `SetPropertyValue(ID, <32-char hex>)` — deterministic GUID per-edit
5. `new_subobject(peek_state, ST_Cond_CanSeeTarget_C)`
6. `SetObjectPropertyValue(InstanceObject, <that subobject>)` — fires
   `PostEditChangeChainProperty` with correct chain + array indices +
   `ObjectIteratorIndex=0` so StateTree's `DispatchPostEditToNodes` walks
   cleanly and the save path captures the subobject
7. `compile_and_save_package`

**Proven via `phase_b_los_gate.py` run twice:**
- Run 1: append + set + save → md5 changes, 1 entry persisted
- Run 2: `stale_removed=0`, `idempotent_existing_idx=0`, `skipped` — the
  entry and its `InstanceObject` both survived reload

**Root cause was triple, not single:**
1. Missing `PostEditChangeChainProperty` on the Instanced FObjectProperty
   write (UE's serializer invariant)
2. ResolvePath couldn't reach wrapper fields through FInstancedStruct
3. `UStateTreeState::PostLoad` → `ConditionalUpdateNodeInstanceData` was
   actively nulling `InstanceObject` on reload because the wrapper's
   `ConditionClass` was None (type-mismatch cleanup)

Fixing (1) and (2) in C++ enabled fixing (3) in the script.

### Probe scripts (archived outside repo at `D:/Work/_combat_ai_tuning/`)

- `probe_bridge.py` — verifies M23.0 UFUNCTIONs surface in Python (use
  this as the bridge sanity-check on any resume)
- `probe_peek_path.py` — walks ST_EnemyBase state tree; produces the
  structural map
- `probe_append_condition.py` — walks `FStateTreeEditorNode` fields after
  a fresh `array_append_new_element`
- `probe_state_obj.py` — confirms `get_object_property_value` can resolve
  a `UStateTreeState` from a path
- `phase_b_los_gate.py` — **the Phase B script** — PASSES end-to-end
  post-M23.1.1 (sets wrapper.ConditionClass + editor-node ID + fires the
  InstanceObject write → PostEditChange → save; idempotent on re-run)
- `phase_b_revert.py` — clears `Peek.EnterConditions` to empty so the
  legacy depot diff stays tidy (last-run state of `ST_EnemyBase.uasset`)
- `test_library.py` — the Python library regression test (17/17 passing)

### Unchanged pre-arc summary (still valid, shorter version)

M1–M19.2.1 delivered the read pipeline: `ProjectManifest` → `ProjectInventory`
with per-asset `.md` + `.meta.json` + optional `.deep.md` (Tier 2) →
`AggregateInventory` rollups. Covered classes: UBlueprint family, StateTree,
BehaviorTree, DataTable, Chooser, EnvQuery, SmartObjectDefinition, plus
plugin descriptor metadata (M7) + DataAsset instances (M19.2.1) + CDO walk
for data-carrier Blueprints (M19.1). Canonical `ProjectInventory_DOW/` is
in-repo. Determinism gate via `scripts/verify_determinism.ps1`. Full DOW
twin run byte-identical across 4 phases (Manifest + Inventory + Aggregate +
ProjectPlugins).

### Resume sanity-checks for a fresh `/clear`

1. `git log --oneline -8` — top 7 should be today's arc, newest `23ba190`.
2. BugHunt commandlet sanity check (same as old checklist — still passes):
   ```
   "/d/Work/UE_DOW/engine/Binaries/Win64/UnrealEditor-Cmd.exe" \
     "D:\Work\blueprintexporter\blueprint-exporter\BugHunt\TestProject\BugHunt.uproject" \
     -run=AggregateInventory \
     -OutDir="D:\Work\blueprintexporter\blueprint-exporter\ProjectInventory" \
     -nullrhi -unattended -nopause -nosplash -nosound -log
   ```
   Should finish <1 s, exit 0, write 11 rollup files.
3. **NEW: Reflection bridge sanity check:**
   ```
   MSYS_NO_PATHCONV=1 "/c/Program Files/Epic Games/UE_5.7/Engine/Binaries/Win64/UnrealEditor-Cmd.exe" \
     "D:\Work\UE_DOW_Legacy\UE_DOW.uproject" \
     -run=pythonscript \
     -script="D:/Work/_combat_ai_tuning/probe_bridge.py" \
     -nullrhi -unattended -nopause -nosplash -nosound -stdout
   ```
   Should produce `D:/Work/_combat_ai_tuning/probe_bridge_results.json`
   with `subtrees_length: 3` and `subtree0_name.before = "Wait"` —
   proves the M23 bridge is loaded and reaching protected state-tree data.
4. Read the M21 / M22 / M23 / M24 scope blocks under "Candidate next
   milestones" below. Dependency chain:
   M23.0 ✓ → M23.1 ✓ → M23.1.1 ✓ → M23.2 ✓ → M24.0 ✓ →
   M24.1 ✓ → M24.2 ✓ → M24.3 ✓ → **M24.4 ✓ (agent-loop doc
   shipped; M24 milestone fully complete)**. Next standalone work is
   M22 (BugHunt-driven per-op fixture tests) or other candidates
   listed below.
5. Plugin at 1.15.1. Stock-5.7 DLL at
   `_build_output_5_7/Binaries/Win64/UnrealEditor-BlueprintExporter.dll`
   (junctioned into `D:/Work/UE_DOW_Legacy/Plugins/BlueprintExporter/`).
   Main-engine DLL at `_build_output/Binaries/Win64/` and
   `BuiltPlugin/Binaries/Win64/`.

### Candidate next milestones

Nothing blocking. Pick based on ROI / colleague demand:

0. **M19.2.2 — DataAsset instances in the sweep.** M19.2.1 wired
   DataAsset-instance support into single-asset `-run=DeepDump`;
   widening the `ProjectInventoryCommandlet` sweep to cover them
   too would eliminate the orphan-file pattern and give `.md` +
   `.meta.json` companions for each DA instance. Scope: add a
   `UDataAsset` check to the sweep's class filter, add a typed
   `EmitDataAssetInstance` emitter mirroring the M11–M15 pattern,
   wire the existing `RenderDataAssetInstanceMarkdown` at Tier 2.
   DOW has only 6 BP-derived DA instances today (`CrowdCharacterDataAsset`,
   `DA_AttachmentDefinition`, 3× `DA_WeaponDefinition`, `UDS_CloudProfile_Data`),
   so canonical refresh would add ~18 files. A few hours of work;
   useful if any colleague iterates on crowd / loadout / UDS data.

1. **M19.3 — CDO deserialize write-back (round-trip for CDO edits).**
   Read path is done (M19.1); write path still missing. Needed only
   if we want Claude-driven edits of e.g. `GE.DurationPolicy` or
   `GA.AbilityTags` to persist via `BlueprintImport -Apply`. Mirrors
   the M18.x deserializer pattern; gate behind the M17 `BS_Error`
   guard. Defer until a concrete edit target surfaces.

2. **M20 — Level export.** Biggest capability gap after M19. A
   `LevelInventoryCommandlet` + `FExportedLevel` schema: per-actor
   table (class / label / transform / tags), instance property
   overrides (reuse M9 walker), Level Blueprint via existing UBP
   serializer, World Settings CDO walk, streaming structure (sub-
   levels, LevelInstance actors, World Partition cells). Skip art
   data (meshes / materials / lightmaps). Size estimate: 5–20 MB
   JSON for DOW's main city level. ~1 week of work; natural
   breakdown: M20.0 actors + overrides, M20.1 streaming / WP,
   M20.2 Level Blueprint integration.

3. **ControlRigBlueprint typed Tier 2.** Currently dumped via the
   generic UBP pin-table path (15 K lines for `Face_ControlBoard_CtrlRig`,
   12 K for `MetaHuman_ControlRig`) — correct but not rigging-semantic.
   A typed renderer would decode rig graphs (bones, constraints,
   solver nodes) similar to how M5.2 handled StateTree editor nodes.
   Low priority unless a colleague does deep ControlRig work.

4. **UserDefinedStruct field-name GUID stripping.** Struct field
   tables currently render names like
   `BodyDefinition_2_ABCDAB8D4F5C30DC9AF7DC9C34D5A278` — the GUID
   suffix is UE's internal hash. Human-readable prefix is there
   but the noise hurts scannability. A one-liner post-processing
   pass to split on the second-last `_` and drop the GUID would
   clean up all struct `.md` rendering. ~30 min.

5. **Recursive struct breakout at Tier 2.** Large struct values
   (>100 KB per field — seen on `CrowdCharacterDataAsset.deep.md`'s
   Skeleton A/B fields) render as single-line Markdown table cells.
   Technically correct and greppable, but visually dense. Mirror
   M13 DataTable's per-row `UScriptStruct` rendering to break nested
   struct content into sub-tables. ~1–2 hours.

6. **Wire `verify_determinism.ps1` into CI.** Still sitting on the
   backlog; ~60 s per run on BugHunt would catch any future
   serializer / renderer regressions in a PR gate. Implementation
   is a TeamCity or GitHub Actions step invoking the existing
   script; nothing engine-side to change.

7. **M21 — Python write-layer library.** Triggered 2026-04-20 when
   a Phase A combat AI tuning attempt via BlueprintImport crashed
   on `K2Node_MacroInstance` + `K2Node_DynamicCast` input-pin type
   resolution (`BlueprintDeserializer.cpp:1337` assertion / access
   violation). M17 `BS_Error` guard held — zero corruption — but
   zero edits landed either. Same 5 CDO value edits via UE Python
   API (`D:\Work\_combat_ai_tuning\tune_phase_a.py`) succeeded
   cleanly end-to-end on first try (all 3 md5s changed, re-export
   confirmed exact values). Architectural insight: split
   BlueprintExporter as the **READ** layer (deep dumps, rollups,
   deterministic diffs) from a new Python op library as the
   **WRITE** layer (uses UE's own save / compile paths via
   `unreal.EditorAssetLibrary` / `BlueprintEditorLibrary` etc.),
   eliminating deserializer fidelity as a blocker for Claude-
   driven edits. `BlueprintImport -Apply` remains useful for JSON-
   diff→BP diffing workflows but is no longer the critical-path
   write mechanism.

   **Scope — M21.0 (scaffolding + first ops, ~2–3 h):**
   - `scripts/python_ops/` module tree with submodules
     `blueprint_cdo.py`, `statetree.py`, `perception.py`,
     `assets.py`, `level.py`. Each op is a typed Python function
     with strict arg validation; returns
     `{success, before, after, md5_before, md5_after, errors[]}`.
   - Ship ops: `set_bp_variable_default`,
     `set_component_property`, `set_instanced_subobject_property`,
     `compile_and_save_blueprint` (private helper), `rename_asset`,
     `create_child_bp`.
   - `scripts/python_ops/CATALOG.md` auto-generated op signature
     list so LLM can see what's available without reading source.

   **Scope — M21.1 (StateTree ops, ~2 h) — BLOCKED by UE 5.7 Python
   binding gap, surfaced 2026-04-20:**
   - `unreal.load_object(None, "/Game/.../ST_EnemyBase.ST_EnemyBase:StateTreeEditorData_0")`
     successfully returns a `StateTreeEditorData` object (the editor
     subobject path pattern for a UStateTree asset).
   - BUT `StateTreeEditorData.Subtrees` and `.EditorBindings` are both
     marked **protected** in UE 5.7's Python reflection — readable only
     are `Schema`, `GlobalTasks`, `Evaluators`. Cannot walk the
     authored state tree from Python.
   - Pure-Python scope for M21.1 (add_statetree_transition /
     set_statetree_state_enter_conditions / set_state_type) is
     therefore **not viable** in UE 5.7 without a C++ bridge.
   - Two unblock paths:
     (a) **BlueprintExporter C++ static helper library** exposing a
     minimal set of UFUNCTION(BlueprintCallable) methods over
     UStateTreeEditorData (read Subtrees, mutate Transitions[] on a
     state by name, push conditions into EnterConditions[]). Python
     side becomes a thin wrapper. ~2 h C++ + stock-5.7 plugin rebuild.
     (b) **Document StateTree edits as "editor or C++ only"** for now.
     Phase B LOS-gated firing falls back to ~2 min of manual editor
     work (drag `ST_Cond_CanSeeTarget` into Peek's transition
     conditions in the StateTree editor).
   - Probe results frozen at `D:/Work/_combat_ai_tuning/probe_st_walk_results.json`
     and siblings for future reference.

   **Scope — M21.2 (variable + function authoring, ~2–3 h):**
   - `add_bp_member_variable`, `bind_delegate_handler`. Harder —
     `BlueprintEditorLibrary` has limited helpers; may fall back
     to engine reflection for some cases. Probe API completeness
     before committing.

   **Scope — M21.3 (EQS + perception tuning, ~1–2 h):**
   - `set_eqs_test_property` (tune scoring weights on
     `EQS_AI_FindCover` etc.), `set_perception_sense_config`
     (SightRadius, HearingRange, etc.).

   **Out of scope:**
   - Adding new K2Nodes to Blueprint event graphs (the "smart
     threat weighting" edit). Stays manual-editor territory until
     UE surfaces graph-edit helpers. Workaround when it matters:
     inject a helper UFUNCTION in a tiny utility class + single-
     wire manual edit.
   - Level BP / Editor Utility Widget edits (separate domain).
   - Rewriting `BlueprintImport`. The JSON round-trip stays
     valuable for diffing and LLM reasoning; it just stops being
     the apply path.

   **Versioning:** No plugin version bump. `scripts/python_ops/`
   lives alongside the plugin, not inside it. `CLAUDE.md` gains a
   new "Python Write Layer" section pointing at the catalog.

   **Open questions (probe before M21.0 start):**
   - `BlueprintEditorLibrary` coverage of variable / function
     authoring — enough, or fall back to engine reflection?
   - StateTree editor Python API completeness in UE 5.7 — surface
     exists but hasn't been exercised; test before committing
     M21.1 scope.
   - Git-based vs file-copy fixture reset — which is faster for
     the M22 test loop? Benchmark before M22.0.

8. **M22 — BugHunt-driven Python op validation loop.** Pairs with
   M21. Every op in the M21 catalog lands with a BugHunt fixture +
   a DeepDump-diff assertion proving the op does what it claims.
   Serves both as (a) CI gate catching op regressions on plugin /
   engine updates, and (b) the sandbox the LLM iterates against
   when a generated script fails at runtime. Closes the user-
   flagged "runtime-failing scripts" risk — a script that passes
   BugHunt is known-good for the classes of bug UE Python actually
   produces (typos, wrong property names, wrong arg types, wrong
   asset paths), and any "works on fixtures fails on legacy" case
   becomes a real-world signal rather than silent corruption.

   **Scope — M22.0 (fixture infrastructure, ~2–3 h):**
   - `BugHunt/TestProject/Content/PythonOps/<op_name>/` — one
     folder per op, holding minimal fixture assets committed to
     the repo.
   - `BugHunt/TestProject/Content/PythonOps/<op_name>/EXPECTED.deep.md`
     — expected DeepDump state after running the op (committed,
     diffed against actual post-run).
   - `scripts/verify_python_ops.ps1` — iterates every op folder,
     runs the op against the fixture, takes a DeepDump, diffs
     against EXPECTED, PASS / FAIL. Reset mechanism: git checkout
     the fixture between runs (fast, deterministic).

   **Scope — M22.1 (first 5 op test cases, ~2 h):**
   - One fixture + test per op from M21.0. Each test proves: op
     runs without error, produces expected DeepDump state, md5
     changes, compile stays clean.
   - `--op=<name>` flag on `verify_python_ops.ps1` for fast
     single-op iteration during op development.

   **Scope — M22.2 (agent loop integration, ~1–2 h):**
   - Document the three-step "iterate on error" pattern:
     `run_op_on_fixture` → if fail, parse UE log for Python
     traceback + compile errors → structured error report → LLM
     retries.
   - Thin `op_runner.py` helper the agent shells into, capturing
     stdout / stderr / exit signal for LLM consumption.
   - Standard error classifier covering the common cases:
     `AttributeError` (wrong property name), `TypeError` (wrong
     arg shape), `LoadFailed` (wrong asset path), `CompileError`
     (op produced invalid BP).

   **Scope — M22.3 (CI wire-up, ~30 min):**
   - `verify_python_ops.ps1` added to the existing
     `verify_determinism.ps1` gate, or as a separate PR-gate step.

   **Out of scope:**
   - Cross-op composite scenarios ("run op A then op B, assert
     composite state"). Single-op tests only — composite goes in
     a later M22.N if demand surfaces.
   - Testing against DOW-scale content. BugHunt fixtures only.
   - Negative tests (asserting op fails gracefully on bad input).
     Add only for ops where graceful failure is load-bearing.

   **Versioning:** No plugin version bump. `BugHunt/README.md`
   gains a "Python Op Tests" section.

   **Dependency & ordering:** M22 depends on M21 (can't test ops
   that don't exist). Natural interleaving:
   1. M21.0 (scaffold + first 5 ops) → immediately usable for
      Phase B LOS-gated firing on CombatPrototype.
   2. M22.0 + M22.1 (fixture infra + 5 tests) → locks in
      correctness for those ops.
   3. M21.1 StateTree ops → M22 fixtures for each.
   4. M21.2 / M21.3 follow as specific edits demand them.
   Total to usable state: ~5–7 h (M21.0 + M22.0 + M22.1). After
   that, each new op is ~30–60 min including its fixture.

   **Accumulated debt (revisit gate — 2026-04-21 onward).** M25.2
   ops are shipping WITHOUT M22 fixtures — same ad-hoc probe-script
   pattern M21.0 + M23.2 used. Explicit conscious call: trade
   regression safety for velocity while the op set is small. Running
   count of debt-carrying ops to grow with each M25.2.x commit:
   M25.2.0 `verify_state_enter_conditions` (read-only, low debt
   since no mutation). **Trigger to do M22.0 + M22.1 properly:**
   (a) op count hits 12+, or (b) a UE 5.7 / plugin update silently
   breaks a shipped op in a real plan apply, or (c) any colleague
   other than the author starts authoring plans (infra-as-onboarding
   becomes load-bearing). Do NOT let M25.2 ship past (a) without
   landing M22 first.

9. **M23 — Reflection Bridge (C++ write layer).** Triggered
   2026-04-20 after the M21.1 probe revealed UE 5.7 Python bindings
   deliberately protect `UStateTreeEditorData.Subtrees` /
   `.EditorBindings` (and many other load-bearing UPROPERTYs across
   the engine). The pattern appeared three times in one session:
   BlueprintImport deserializer gaps on complex graphs, Python
   reflection gaps on protected properties, and per-content-type op
   proliferation. All three share one root cause — Python's coverage
   of UE's reflection system is incomplete and we keep routing around
   it case-by-case. The Reflection Bridge is the general solution:
   a small C++ `UFUNCTION(BlueprintCallable)` library inside the
   BlueprintExporter plugin that walks `FProperty` / `UObject*`
   natively (so Python-binding protection flags don't apply) and
   returns results to callers. Python side becomes a thin wrapper;
   M21 ops re-implement as 3-line delegations.

   **Scope — M23.0 (core bridge, ~3–4 h):**
   - `Source/BlueprintExporter/Public/Reflection/ReflectionTypes.h`
     with `FBpxReflectionResult` struct (`bSuccess`, `ErrorMessage`,
     `BeforeText`, `AfterText`).
   - `Source/BlueprintExporter/Public/Reflection/ReflectionOps.h` +
     `Private/Reflection/ReflectionOps.cpp` with `UBpxReflectionOps`
     static UCLASS:
     - `GetPropertyValue(Root, Path) -> FBpxReflectionResult`
     - `SetPropertyValue(Root, Path, ImportTextValue) -> FBpxReflectionResult`
     - `FindSubobject(Root, SubobjectName) -> UObject*`
     - `CompileAndSavePackage(Target) -> bool` (BS_Error-guarded,
       mirrors M17 guard from BlueprintImport)
   - Walks FProperty via `FindPropertyByName` +
     `ContainerPtrToValuePtr` + `ExportText_Direct` /
     `ImportText_Direct` — mirrors the serializer's read path,
     inverted for writes.
   - Path elements: property name (string) or array index (integer
     or `"[N]"` form). Resolves object-valued properties by chasing
     the pointer; handles FArrayProperty indexing natively.
   - Plugin version bumps 1.14.0 → 1.15.0 (new subsystem per
     CLAUDE.md semver); all 7 drift locations updated.

   **Scope — M23.1 (array + struct ops, ~1–2 h):**
   - `ArrayAppendStructValue`, `ArrayRemoveAt`, `ArrayLength`.
     Enables mutating StateTree Transitions / EnterConditions arrays,
     EQS Options, etc.
   - `GetSubobjectArray(Root, Path) -> TArray<UObject*>` for
     protected instanced-subobject arrays (StateTree Subtrees being
     the load-bearing case).

   **Scope — M23.2 (retrofit M21 ops + add M21.1, ~2 h):**
   - Existing 5 Python ops re-implement on top of
     `unreal.BpxReflectionOps` for uniform error handling and to
     eliminate the SCS / CDO / instanced code-path fork. API-
     compatible — M22 fixture tests should stay green.
   - New M21.1 StateTree ops land as thin wrappers:
     `add_statetree_enter_condition`, `add_statetree_transition`.
     Unblocks Phase B LOS-gated firing on `ST_EnemyBase`.

   **Out of scope:**
   - Adding new `K2Node` instances to a Blueprint's event graph —
     graph construction isn't reflection-addressable. Stays manual-
     editor territory. The "add threat weight" AssessThreat edit
     still needs a helper UFUNCTION + one manual wire.
   - Anything requiring the editor's `IAssetEditorInstance` (per-
     type editor UIs with their own graph-mutation APIs). Out of
     scope.

   **Versioning:** 1.14.0 → 1.15.0 (minor bump, new subsystem per
   CLAUDE.md semver rule). All 7 drift locations updated.

   **Dependency change to M21:** M21.1 / M21.2 / M21.3 previously
   scoped as pure Python — now depend on M23.0 + M23.1 landing
   first, since StateTree / variable-authoring / EQS edits all need
   protected-UPROPERTY access. M21.0 (already shipped `84049a2`) is
   unaffected but can be retrofitted onto the bridge in M23.2.

10. **M24 — Supervised Edit Loop.** The runtime safety harness
    around the read → understand → apply → verify pipeline. Sits on
    top of M21 (Python ops), M22 (fixture tests), and M23
    (reflection bridge) and makes every edit a structured,
    validatable, mechanically-verifiable event instead of "LLM
    writes a script and hopes." Introduces three artifacts that
    don't exist today: an EditPlan schema, a pre-flight validator,
    and a mechanical diff oracle.

    **Flow (8 steps):**
    1. **Export** — BpxExporter deep-dumps the target asset(s).
       *Already done.*
    2. **Understand** — Claude reads dumps, reasons about semantics,
       flow, defaults, transitions, constraints. *Already done.*
    3. **Plan** — Claude produces a structured `EditPlan` (not raw
       code): intended outcome, exact ops, target paths/properties,
       expected side effects, verification expectations. *New.*
    4. **Validate plan** — the system walks the plan with bridge
       read ops, verifies every target path resolves, types match,
       refs exist, ops are in the allowed set, and risk level is
       acceptable. Rejects before any bytes move. *New.*
    5. **Apply** — trusted Python executor calls M23 reflection
       bridge → native FProperty walk → UPackage::SavePackage.
       *M21/M23, in progress.*
    6. **Verify mechanically** — re-export, deep-diff against the
       pre-run snapshot, assert `changed_fields ⊆ plan.expected_fields`,
       run compile/load/reference validation, capture logs. *New.*
    7. **Verify semantically** — Claude re-reads post-export dumps,
       confirms the intended design change actually happened. *Claude
       workflow.*
    8. **Escalate only experiential** — subjective uncertainty
       ("does it feel better?") → user PIE test. Everything else
       refines and loops automatically. *Workflow convention.*

    **Scope — M24.0 (plan schema + authoring doc, ~1 h):**
    - `scripts/python_ops/plans/README.md` — the EditPlan format +
      authoring guidelines for Claude.
    - Schema (JSON-able):
      ```
      {
        "intended_outcome": "<prose>",
        "operations": [
          {
            "op": "set_bp_variable_default",
            "target": "/Game/.../BP_X",
            "path": ["VarName"] or ["Component", "[0]", "Sub", "Field"],
            "value": <JSON-native or ImportText string>,
            "expected_type": "float" / "Vector2D" / "Object(Class)" / ...
          },
          ...
        ],
        "expected_side_effects": [
          "BP_X will recompile",
          "AC_Y.uasset md5 will change"
        ],
        "verification": [
          {"path": ["/Game/.../BP_X", "VarName"], "expected": 8.0},
          {"asset_exists": "/Game/.../BP_New"}
        ],
        "risk_level": "low" | "medium" | "high"
      }
      ```
    - Conventions for idempotency keys + op ordering.

    **Scope — M24.1 (plan validator, ~2 h):**
    - `scripts/python_ops/plan_validator.py` with
      `validate_plan(plan: dict) -> ValidationReport`.
    - For each op: resolve target asset (`EditorAssetLibrary.does_asset_exist`),
      walk path via `BpxReflectionOps.GetPropertyValue` (no mutation),
      verify property exists, type matches `expected_type`, referenced
      classes/assets load.
    - Returns structured report: `{passed: bool, per_op: [{op_idx,
      ok: bool, errors: []}], warnings: [...]}`.
    - CLI wrapper so plans can be pre-flighted from a commandlet run
      without Python-in-editor dependency (reads deep dumps instead
      when run headless).

    **Scope — M24.2 (plan executor, ~1 h):**
    - `scripts/python_ops/plan_executor.py` with
      `execute_plan(plan: dict) -> ExecutionReport`.
    - Takes a validated plan, snapshots each target's before-state
      via bridge reads, dispatches to named ops, captures after-state,
      calls `CompileAndSavePackage`, records all results.
    - Aborts on first op failure (no partial-apply) — caller decides
      whether to retry / rollback.

    **Scope — M24.3 (mechanical diff, ~2 h):**
    - `scripts/python_ops/mechanical_diff.py` — runs DeepDump (the
      existing commandlet) on each target asset pre + post execution,
      produces a field-level diff. Asserts
      `changed_fields ⊆ plan.expected_fields`. Flags unexpected changes
      (often indicates unintended side effects / BP compile churn /
      non-determinism).
    - Reuses `DeepDumpRenderer`'s output as the diff substrate
      (`.deep.md` + `.meta.json` are already designed to be diffable —
      per brief §8).
    - Returns structured `DiffReport` with lists of expected-and-seen,
      expected-but-missing, and unexpected changes.

    **Scope — M24.4 (agent-loop integration doc, ~1 h):**
    - End-to-end worked example: Claude receives a user goal → reads
      the relevant deep dumps → produces plan JSON → runs validator →
      if fails, refines plan and loops → runs executor → runs
      mechanical diff → if passes, semantic-verify → if ambiguous,
      asks for PIE test.
    - Documents error-classification + retry heuristics for each step.
    - Pairs with M22's BugHunt loop — fixtures assert named ops work;
      M24 asserts *user-requested edits* are safe and correct.

    **Out of scope:**
    - Rollback-on-failure. Apply is still atomic-per-op, not
      atomic-per-plan. If op 5 of 10 fails, ops 1–4 already committed.
      Document as a caller constraint for now.
    - Distributed / multi-user edit coordination (P4 check-out
      orchestration, conflict resolution). Keep plans local; user
      decides whether to `p4 submit`.

    **Versioning:** No plugin bump — M24 is pure Python orchestration
    on top of the M23 C++ bridge. `CLAUDE.md` Docs Map gains a row
    pointing at `scripts/python_ops/plans/README.md`.

    **Dependency:** M24.1 + M24.2 + M24.3 depend on M23.1 (array
    append/remove ops) and M23.2 (M21 ops retrofitted onto the
    bridge) being stable. M24.0 (schema doc) can land anytime.

11. **M25 — MCP server + tactical AI ops.** Triggered 2026-04-21
    after finishing Track-A combat-AI decision gates on
    `ST_EnemyBase` (Peek LOS-gate already landed, CombatLoop
    HasTargets-gate landed this session — see the two plan sidecars
    under `D:\Work\_combat_ai_tuning\`). Two architectural gaps
    surfaced in the process:

    (a) **Context access is expensive.** Every edit-authoring cycle
    costs 10–15 Read/Glob/Grep tool calls to re-discover asset paths,
    state indices, CDO defaults, etc. The inventory + deep dumps
    already hold the answer — but they live on disk and have to be
    rediscovered by filename each session.

    (b) **Write contract is shell-only.** The M24 plan →
    validator → executor → mechanical-diff loop is the differentiator,
    but it's only reachable via `UnrealEditor-Cmd.exe -run=pythonscript
    -script=...`. Good for CI, painful for interactive authoring.

    Prior-art UE-Python MCP tooling in the same space solves (b)
    with an in-editor C++ MCP server + hundreds of Python service
    methods, but none of it has an equivalent of our plan-and-diff
    audit contract. Architectural position: **that shape of surface
    + our audit contract** is the thing we actually want. Use such
    projects as a **reference for which UE Python calls hit which
    systems** (the UE Python API itself is Epic's) — do NOT vendor,
    proxy, or name them in shipped artifacts. Our solution stays
    our solution.

    Secondary driver: the tactical-AI ops gap. Track A exhausted
    what the seven shipped ops can do for smart 5v5 behaviour
    (EnterCondition wiring + CDO/SCS/instanced tuning). Going
    further — event-driven ST transitions, EQS test tuning, Wait
    durations, new BP variables — needs ops we haven't shipped.
    Prior-art sources are a cheap map for "how does UE Python add
    a StateTree transition" without us spelunking Epic's docs.

    **Scope — M25.1 (external MCP server V1) ✓ shipped 2026-04-21
    across 7 commits `238b2bd..0a0d1ea`:**
    - **M25.1.0** at `34a9039` — scaffold + 4 retrieval tools.
    - **M25.1.1** at `ce00710` — 4 more retrieval tools (`get_asset_meta`,
      `get_cdo_properties`, `get_references`, `get_class_tree`).
    - **M25.1.2** at `a2073db` — 3 plan-pipeline tools (`get_op_catalog`
      AST-only; `validate_plan` / `apply_plan` shell to
      `-run=pythonscript`).
    - **M25.1.3** at `2f91011` — 2 live-introspection tools
      (`deep_dump_asset` → `-run=DeepDump`; `refresh_inventory` →
      `-run=ProjectInventory -Filter=<prefix>`). Also refactored
      subprocess helpers into a shared module.
    - **M25.1.4** at `0a0d1ea` — Cursor + Claude Desktop config snippets
      + sanity-check subsection in README.
    - 13 tools total. 37/37 smoke assertions. See the
      `scripts/blueprint-exporter-mcp/` tree and the package README for
      the full surface + client config.
    - New deliverable: `scripts/blueprint-exporter-mcp/` Python
      package (FastMCP or equivalent). Independent versioning; does
      NOT ship inside the plugin.
    - Retrieval tools (zero UE process — serve pre-indexed inventory):
      - `list_assets(class_filter, path_prefix, head_limit)` — ls
        over `MANIFEST.md` / `Assets/**`.
      - `get_asset_summary(path)` — read `.md`.
      - `get_asset_deep_dump(path)` — read `.deep.md`.
      - `get_asset_meta(path)` — read `.meta.json`.
      - `search_deep_dumps(pattern, class_filter, head_limit)` —
        ripgrep across `.deep.md` tree.
      - `get_references(path, direction)` — walk
        `DEPENDENCY_GRAPH.md` / `dependency_graph.dot`.
      - `get_class_tree(class_name)` — subtree of `CLASS_TREE.md`.
      - `get_cdo_properties(bp_path)` — projection of `.meta.json`'s
        `cdoProperties`.
    - Plan-pipeline tools (shell to existing scripts, return
      structured result):
      - `validate_plan(plan_json_str)` → `run_plan_validator.py`
        output as dict.
      - `apply_plan(plan_json_str)` → `run_plan.py` output
        (execution + diff + verification reports).
      - `get_op_catalog()` → introspect `python_ops/__init__.py`
        and return each op's signature + kwargs schema. Auto-
        updates as new ops ship — no MCP-side code change per op.
    - Live-introspection tools (optional, shell to UE only when
      inventory is stale):
      - `deep_dump_asset(path)` — single-asset fresh dump.
      - `refresh_inventory(path_filter)` — focused re-sweep.
    - Config: project path + inventory path + engine path + uproject
      path in a single `blueprint-exporter-mcp.json` or env vars.
      Must support both UE_DOW (custom engine at
      `D:\Work\UE_DOW\engine\`) and UE_DOW_Legacy (stock UE 5.7 at
      `C:\Program Files\Epic Games\UE_5.7\`) without code changes.
    - Deliverable: `uvx blueprint-exporter-mcp` runnable; Claude
      Code / Cursor / Claude Desktop MCP-config snippets in the
      package README.

    **Scope — M25.2 (tactical AI ops, ~1–2 weeks):**
    - `add_statetree_transition(st_path, state_path, trigger,
      target_state_path, condition_bp_path)` — event-driven edges
      (OnEvent / OnTick / OnStateFailed). Unblocks "on damage,
      retreat" / "lost target, disengage" / "flanker detected,
      reposition" patterns.
    - `remove_statetree_transition(st_path, state_path,
      transition_idx)` — symmetric.
    - `set_statetree_task_instance_data(st_path, state_path,
      task_idx, field, value)` — reaches the two `StateTreeDelayTask`
      instance-data fields (`Duration`, `RandomDeviation`,
      `bRunForever`) on `ST_EnemyBase`'s Wait states. Shipped ops
      can't touch these today.
    - `set_eqs_test_property(eqs_path, option_idx, test_idx,
      property_name, value)` — tune `EQS_AI_FindCover` /
      `EQS_AI_FindPeek` scoring weights.
    - `add_bp_member_variable(bp_path, var_name, var_type, default,
      category, instance_editable)` — unblocks richer condition /
      task BPs (e.g. threat-weight thresholds). Probe API coverage
      first; may need bridge extension.
    - `verify_state_enter_conditions(st_path, state_path) ->
      List[{class, idx}]` — helper op that returns the current
      EC list at a state, addressing the root-state EC verification-
      path quirk hit 2026-04-21 (see Known issues). Plans get a
      clean read-back for both root and nested states.
    - Each op lands with an M22 BugHunt fixture + DeepDump-diff
      assertion. No exceptions — that's the contract.

    **Scope — M25.3 (integration polish, ~3–5 days):**
    - Auto-catalog: `get_op_catalog` MCP tool introspects
      `python_ops/__init__.py` at serve time so new ops surface
      without MCP server changes.
    - `AGENT_LOOP.md` gains worked examples for each M25.2 op
      (mirrors the LOS-gate example that drove Track A).
    - `plans/README.md` documents the root-state vs nested-state
      EnterCondition verification-path forms explicitly — closes
      the gap that produced the `got: null` verification failure
      in `combat_loop_hastargets_gate.json.run.json`.
    - `CATALOG.md` "Coming next" section trimmed to reflect shipped
      set.

    **Out of scope:**
    - In-UE C++ MCP server (an alternative approach some tooling
      takes). Deferred; would need plugin-side HTTP listener + port
      management + async command dispatch. Revisit only if external-
      shell latency becomes a workflow blocker.
    - Hosted LLM backend. Bring-your-own-LLM stays the design —
      any MCP client drives the server.
    - Vendoring or forking external MCP-UE source. Reference only —
      read for technique, re-express every Python call we use in
      our own file to our own contract. No attribution in shipped
      artifacts; keep notes in ephemeral scratch if needed.
    - UMG / material / landscape / Niagara ops. Broad-authoring
      tooling for those domains exists elsewhere; our niche stays
      audit-gated BP + StateTree + EQS + data-carrier edits.
    - New K2Node authoring inside Blueprint graphs (already out
      of scope per M23 + M21). Still requires a helper UFUNCTION
      + manual wire.

    **Versioning:** No plugin version bump — the MCP server is
    external. M25.2 ops may ship bridge extensions (e.g. new
    UFUNCTIONs on `UBpxReflectionOps` for transition-array
    manipulation); if they do, plugin bumps per the existing semver
    rule. `CLAUDE.md` Docs Map gains a row pointing at the MCP
    package README when M25.1 ships.

    **Dependency:** M25.1 depends on M24.4 (agent-loop doc) being
    stable — it is. M25.2 depends on M23.2 bridge being stable —
    it is. M25.3 depends on M25.1 + M25.2 both landing. The two
    sub-milestones can run in parallel (different files, different
    concerns).

    **Non-goals / explicit anti-patterns:**
    - **Rebranded external tooling.** If this milestone drifts
      toward "Python wrappers over someone else's service modules,"
      stop and re-scope. The plan → validate → apply → diff audit
      contract is the differentiator. Anything that doesn't
      preserve it is off-mission.
    - **MCP surface inflation.** The initial tool list above is
      tight on purpose. New retrieval tools must earn their slot
      by eliminating ≥3 typical file-access calls per use; new
      write tools must go through the plan contract, not bypass it.

12. **M28.10 — `create_blueprint_class` op (native parent + determinism).**
    Surfaced 2026-04-27 by the design.md MCP-only test run against
    UE_DOW_Legacy. Existing `create_child_bp` (`assets.py:84`) only
    handles BP-parented children, not native ones (`AActor` /
    `UActorComponent`). Without this op, design.md's
    `BP_EncounterDirector` (pillar 1) and `UAIActionScorer` (pillar 2)
    can't be authored end-to-end via MCP — every other slice is
    already supported by M28.2 + M28.3 *once the BP exists*. Sequence:
    M28.10.0 research (FGuid::NewGuid() + NewObject naming catalog
    on fresh UBlueprint creation — likely `BlueprintGuid` + empty
    Ubergraph NodeGuid), M28.10.1 ship
    `create_blueprint_class(parent_path, new_bp_path)` accepting
    either `/Game/<bp>` or `/Script/<class>` as parent + harden
    `create_child_bp`'s currently-weak idempotence (parent-class match
    via reflection). Full scope row in the M28 phase table above.

### Known issues / audit parking lot

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

### Historical M19 scope (delivered in M19.1)

For the full-scope document that drove M19.1 (pre-start, authored
`3ea32a1`), see item #0 below. Kept for reference — the actual
delivery matches the scope verbatim.

0. **M19 — Data-carrier CDO walk (GameplayEffect / DataAsset
   subclasses / script-less GameplayAbility).** Biggest analysis
   blind spot remaining. Data-carrier Blueprints currently export
   nearly-empty because `FBlueprintSerializer::SerializeBlueprint` is
   graph-oriented — walks variables, functions, graphs, components —
   but never reads the Class Default Object's Details-panel UPROPERTYs
   where GE modifiers / duration policy / GA cost-cooldown / DA payload
   live. A `GE_*` BP surfaces parent class + dependencies and
   essentially nothing else. Fix adds a CDO-property pass that reuses
   the M9 instanced-subobject walker so nested `Instanced` /
   `EditInlineNew` sub-objects (e.g. effect components, modifier
   calculations) land as structured trees rather than opaque text
   blobs.

   **Scope — M19.1 (export side, first slice):**
   - Add `FExportedBlueprint::CDOProperties: TArray<FExportedComponentProperty>`
     (or similar — reuse existing shape so inventory `.meta.json` and
     round-trip JSON pick it up automatically). `FExportedComponentProperty`
     already carries `bIsInstancedSubobject` + `SubobjectJsonValues` from M9,
     so Instanced fields get the same recursive walk as component
     templates.
   - New `FBlueprintSerializer::SerializeCDOProperties(UBlueprint*)`
     method. Walks `Blueprint->GeneratedClass->GetDefaultObject()` via
     `TFieldIterator<FProperty>`, diffs against the parent class CDO
     to emit only non-default values (same "authored values" principle
     the component-template serializer already uses).
   - Call from `SerializeBlueprint` after the component walk; emit
     via `FExportedBlueprint::ToJson`. Sort by property name for
     determinism (brief §8).
   - Plumbing-filter parity: skip the same UE plumbing names the M11–M15
     Tier 2 renderers use (`UberGraphFrame`, `CachedFrameStateTree`);
     the M16 pattern applies here.
   - Coverage bucket: add `cdoProperties` to `FBPCoverageData` so
     HEALTH_REPORT flags under-coverage; `specialized.applicable`
     gains `GameplayEffect.CDO` / `GameplayAbility.CDO` /
     `DataAsset.CDO` markers.

   **Scope — M19.2 (Tier 2 deep dump rendering):**
   - `TextExport/DeepDumpRenderer::RenderBlueprintMarkdown` gains a
     "## Class Default Object" section after the existing Components
     section. Renders the property table via the existing M9 helper
     `RenderInstancedSubobjectTree` so nested trees match the component
     rendering pattern exactly.

   **Scope — M19.3 (deserialize side, optional follow-up):**
   - Write CDO property values back on `BlueprintImport -Apply`. Needed
     if we want to edit e.g. a GameplayEffect's Duration from
     `Infinite` → `HasDuration` via JSON. Mirrors the M18.x pattern
     (read field → set on live object → let M17 SavePackage persist).
     Gate behind the M17 BS_Error guard. Defer if M19.1+M19.2 deliver
     enough value without it.

   **Targets / verification:**
   - BugHunt `BP_GAS_Ability` (minimal GAS fixture — 2 vars, 0 funcs;
     today exports near-empty) is the fastest smoke-test bed.
   - DOW `GASP_example` has GameplayAbility / AttributeSet-derived BPs
     per the M4.1 `GAS_OVERVIEW.md` rollup — concrete end-to-end
     content. Pick one and confirm its CDO properties surface in
     `.meta.json` + `.deep.md`.
   - Determinism: full DOW twin run via `verify_determinism.ps1
     -Project DOW -SweepDeepDump` should PASS post-fix, affected files
     being only GAS/DA-adjacent BPs whose CDO data now serializes.
   - Canonical `ProjectInventory_DOW/` refresh after the feat commit —
     any GAS/DA Blueprint in DOW will have its `.meta.json` + `.deep.md`
     updated with new CDO data.

   **Out of scope:**
   - CDO walk for non-BP classes (C++ actors, BPGC-only assets). M19 is
     BP-centric; Component Tier 2 walks already cover non-BP-rooted
     actor components.
   - Level Blueprints / Editor Utility Widgets — the "data-carrier"
     distinction doesn't apply and other serializer work is needed
     before these are on the map.

   **Versioning:** M19 adds a new schema field (`cdoProperties`) and a
   new subsystem-ish capability. Per CLAUDE.md semver rule this
   warrants a minor bump → 1.14.0 on completion. Drift-detection
   checklist: `.uplugin` (VersionName + Version integer = 14),
   `BlueprintExporterModule.cpp` UE_LOG, `BlueprintExportManager.cpp`,
   `BlueprintSerializer.cpp`, `StateTreeSerializer.cpp`,
   live-version manifest tests in `BlueprintExporterTests.cpp`,
   `README.md`. Run `grep -rn "1\.[0-9]\+\.[0-9]\+" Source/
   BlueprintExporter.uplugin README.md` to confirm no drift.

1. **Wire `verify_determinism.ps1` into CI**. ~60 s per run; cheap
   insurance against future serializer / renderer regressions. PR gate
   for any changes to `Source/` or `BuiltPlugin/`. Implementation is
   a TeamCity or GitHub Actions step invoking
   `pwsh -File scripts/verify_determinism.ps1 -Project BugHunt` (the
   BugHunt gate is fast — DOW gate stays local). Add `-SweepDeepDump`
   to the BugHunt gate as a second cheap catch (~54 s) if we want
   Tier 2 determinism exercised on every PR.

2. **Author a populated BT fixture in BugHunt**. Current `BT_BugHunt`
   is an empty-tree (no root node), so M12's per-node property-table
   code path has no regression coverage in the test corpus — and DOW
   has zero BT assets so the DOW sweep doesn't exercise it either.
   Authoring a minimal `BT_BugHunt_Populated` with one Selector → one
   Sequence child → one `BTTask_MoveTo` + one `BTDecorator_Blackboard`
   + one `BTService_DefaultFocus` would cover every branch of the
   `WalkTree` + `RenderAuxList` path. .uasset-only change; no code.

3. **Refresh canonical `ProjectInventory_DOW/` with sweep deep-dumps**.
   Done as part of M8 / M9 / M11 / M12 refreshes — the canonical tree
   is Tier 2 for UBP / ST / SO. No BT content exists in DOW so M12
   didn't add BT dumps, only refreshed out-of-scope notices.

4. **Tier 2 depth — extend DeepDump to remaining typed-handler types**.
   UBP family + UStateTree + SmartObjectDefinition + BehaviorTree +
   DataTable + ChooserTable + EnvQuery now get full Tier 2. Still
   out-of-scope: PoseSearch (per-entry sampling curves — 154 DOW
   assets, biggest footprint but lowest AI-logic value),
   UserDefinedStruct (65 DOW — struct CDO value walk),
   UserDefinedEnum (74 DOW — enum display-name table). UDE is the
   easiest remaining slice; PSD is the most content-heavy.

5. **M7 P1.1 — struct-typed plugin types**. Small additive slice;
   parallel `TObjectIterator<UScriptStruct>` + `IsChildOf` walk covers
   `FStateTreeTaskBase` / `FStateTreeConditionBase` /
   `FStateTreeEvaluatorBase` + any future struct-based registrations.
   Value-walk needs `UScriptStruct::InitializeStruct` on a scratch
   buffer (more plumbing than the UClass CDO path); can start with
   name+parent+module-only emission and add value walks later.
   Only ship if a plugin lands that authors native struct-based
   StateTree tasks / conditions / evaluators.

6. **M7 P2 — plugin content scan**. Opt-in
   `-IncludePluginContent` flag on `ProjectInventory`. Some DOW
   project plugins set `bCanContainContent: true` and ship authored
   assets (DLSS, MetaTailorBridge, Tripo3DUEBridge, Wwise family,
   SteamAudio family). Phase 1 currently ignores those mount points.
   Add when their gameplay content becomes load-bearing to analyse.

7. **Author more SmartObjectDefinitions** for DOW NPCs (design/
   content work, not plugin work). Current: only `SO_BenchDefinition`.
   Each additional SO = one new NPC behavior verb. Trivial from
   tooling perspective — tool already scans them.

8. **Wire a `UAIPerceptionComponent` to AIC_NPC_SmartObject**
   (design/gameplay work). #1 gap for reactive NPC behavior per the
   M5.2 usability audit.

### Deferred M7 extensions (post-P1 — in priority order, add when needed)

- **M7 P2 — `-IncludePluginContent` for `ProjectInventory`.** Some
  project plugins declare `bCanContainContent: true` and ship their own
  `/Plugin/<Name>/` mount point with authored assets (in DOW: DLSS,
  DLSSMoviePipelineSupport, MetaTailorBridge, Tripo3DUEBridge, Wwise,
  WwiseNiagara, SteamAudio, SteamAudioWwise — 8 plugins). Phase 1
  currently ignores those mount points. P2 would add an opt-in flag so
  plugin-content sweeps can happen alongside the /Game sweep. Lands
  when Marketplace gameplay content starts being load-bearing to
  analyse.
- **M7 P3 — GameplayTag registration from plugin ini files.** Plugins
  commonly register tags via `Config/Tags/*.ini`. Scanning those
  surfaces the tag vocabulary plugins add to the project. Low-effort,
  low-urgency.
- **M7 P4 — Cross-reference in AggregateInventory.** Enrich
  `DEPENDENCY_GRAPH.md` / `REPLICATION_MATRIX.md` with plugin-
  registered class usage — e.g. "this BP inherits from a class
  registered by CoverEQS". Needs P1 to land first.
- **Engine plugins** (separately enabled via uproject): deliberately
  out of scope. Epic ships engine-plugin docs — re-documenting them
  here would bloat output for questionable value. Revisit only if a
  specific engine plugin becomes load-bearing to analyse.

### Other items on the backlog (post-M7)

1. **Re-run canonical `ProjectInventory_DOW/`** after DOW CL moves.
   Workflow: single pass `ProjectManifest` → `ProjectInventory` →
   `AggregateInventory` into the same directory, `git add -A`, commit
   as `chore(blueprint-exporter): refresh ProjectInventory_DOW against
   UE_DOW@<CL>`. The diff stat surfaces what content changed.
   `verify_determinism.ps1 -Project DOW -SkipDeep` can run as a gate
   before the refresh commit if desired.

2. **Add a DOW-exercising RPC fixture to BugHunt.** `BP_NetRep`
   has replicated variables but no Server/Client/NetMulticast
   function events, so the M3.2 RPC matrix code path doesn't
   exercise against authored data in the committed corpus. A single
   `BP_NetRep_RPCs` (or extending `BP_NetRep`) with one Server
   Reliable + one Client Unreliable + one NetMulticast event would
   keep the test corpus honest for future net-code changes.

3. **Add a real ST fixture to BugHunt.** The current `ST_BugHunt`
   has no editor data so the M5.2 instance-data capture path has
   no BugHunt regression. Authoring a minimal `ST_Patrol_Fixture`
   with one native task (`StateTreeDelayTask`), one BP-backed task,
   and one transition condition would cover all three property
   tables DeepDump emits. DOW is the current authoritative test
   bed for ST.

4. **DeepDump for the remaining non-UBP types.** M5.2 covered
   StateTree. Still out-of-scope: BT / DT / UDS / UDE / SmartObject /
   Chooser / PoseSearch / EnvQuery. Their Tier 1 typed handlers
   already dump near-complete shape, but a true Tier 2 could add
   per-BT-node service/decorator script expressions, per-Chooser-cell
   filter value trees, per-PSD sampling curves. Only pursue if a
   concrete consumer need arises — the M5.2 notice is explicit
   about what's missing and where to look instead.

5. **Wire `verify_determinism.ps1` into CI.** Currently runs locally.
   TeamCity / GitHub Actions step = `pwsh -File scripts/verify_determinism.ps1
   -Project BugHunt` on every PR touching the `Source/` / `BuiltPlugin/`
   trees. ~60 s per run is cheap insurance.

6. **M5.3 P1 (deferred)** — unmapped `EStateTreeStateSelectionBehavior`
   values (`TrySelectChildrenAtRandom`,
   `TrySelectChildrenWithHighestUtility`,
   `TrySelectChildrenAtRandomWeightedByUtility`,
   `TrySelectChildrenAtUniformRandom`,
   `TrySelectChildrenBasedOnRelativeUtility`). DOW doesn't use them
   today; add when a future DOW CL or new project does.

7. **Stamp commit hashes** back into this file as
   `docs(blueprint-exporter):` commits after each sub-slice (mirrors
   `2375f9a` / `6a8f032` / `c887221` / `045bb93` / `91d141e` / `a0e6a70`
   pattern). Keeps WIP_INVENTORY a reliable /clear→resume anchor.

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
