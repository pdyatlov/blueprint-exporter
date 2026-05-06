# Project Inventory Index

First file to read. Rollup of `.meta.json` sidecars produced by `-run=ProjectInventory` (Phase 1 / brief §4).

## Run Scoreboard

_First run against this output directory — baseline seeded from this run, so all deltas are `0`. Subsequent runs will diff against this baseline. Pass `-ResetBaseline` to reseed explicitly._

| Metric | Baseline | Last Run | Delta |
|---|---:|---:|---:|
| Assets introspected | 893 | 893 | 0 |
| Failed loads | 0 | 0 | 0 |
| Partial loads | 0 | 0 | 0 |
| Coverage <100% | 0 | 0 | 0 |
| HEALTH warnings | 0 | 0 | 0 |

## Counts by Blueprint subclass

| Subclass | Count |
|---|---:|
| `AnimBlueprint` | 27 |
| `Blueprint` | 432 |
| `ChooserTable` | 12 |
| `ControlRigBlueprint` | 25 |
| `DataTable` | 6 |
| `PoseSearchDatabase` | 154 |
| `SmartObjectDefinition` | 1 |
| `StateTree` | 4 |
| `UserDefinedEnum` | 80 |
| `UserDefinedStruct` | 85 |
| `WidgetBlueprint` | 67 |

## Counts by top-level folder

| Folder | Assets |
|---|---:|
| `/Game/_ThirdParty` | 543 |
| `/Game/Art` | 108 |
| `/Game/Blueprints` | 100 |
| `/Game/Developers` | 46 |
| `/Game/Levels` | 21 |
| `/Game/Movies` | 1 |
| `/Game/Prototype` | 50 |
| `/Game/Standards` | 22 |
| `/Game/WwiseAudio` | 2 |

## Largest connection hubs

| Asset | Refs in | Refs out |
|---|---:|---:|
| `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/ExperimentalStateMachineData/CHT_CMCCharacterAnimations` | 1 | 394 |
| `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/ExperimentalStateMachineData/CHT_MoverCharacterAnimations` | 1 | 373 |
| `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/ExperimentalStateMachineData/PSD_SM_CMC_Transitions` | 0 | 317 |
| `/Game/Levels/City/BPP_City_Packed_Chunk` | 0 | 216 |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | 14 | 176 |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | 16 | 125 |
| `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Dense/PSD_Dense_Stand_Run_Pivots` | 1 | 139 |
| `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/ExperimentalStateMachineData/PSD_SM_Mover_Transitions` | 0 | 136 |
| `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Dense/PSD_Dense_Stand_Walk_Pivots` | 1 | 135 |
| `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Dense/PSD_Dense_Crouch_Walk_Pivots` | 1 | 134 |

## Where to start

Pick a question, jump to the right rollup. All rollups are deterministic text files; everything is link-and-read.

| Looking for... | Read |
|---|---|
| NPC behavior / AIControllers / BehaviorTrees / StateTrees | [AI_OVERVIEW.md](AI_OVERVIEW.md) |
| Animation Blueprints + state machines + transitions | [ANIM_OVERVIEW.md](ANIM_OVERVIEW.md) |
| UI widget trees (UMG) | [UI_OVERVIEW.md](UI_OVERVIEW.md) |
| GameplayAbility / GAS-derived blueprints | [GAS_OVERVIEW.md](GAS_OVERVIEW.md) |
| UserDefinedStruct / UserDefinedEnum schemas | [STRUCTS_ENUMS.md](STRUCTS_ENUMS.md) |
| Replicated variables + Server/Client/NetMulticast RPCs | [REPLICATION_MATRIX.md](REPLICATION_MATRIX.md) |
| Class inheritance chains (native + BP→BP) | [CLASS_TREE.md](CLASS_TREE.md) |
| Refs in / refs out per asset (+ Graphviz `.dot`) | [DEPENDENCY_GRAPH.md](DEPENDENCY_GRAPH.md) |
| Project plugins + their registered native types | [PLUGINS.md](PLUGINS.md) |
| Coverage gaps + failed loads + partial loads | [HEALTH_REPORT.md](HEALTH_REPORT.md) |
| Full registry scan (incl. non-logic-bearing assets) | [MANIFEST.md](MANIFEST.md) |

Some rollups are conditional on the source data:
- `GAS_OVERVIEW.md` is written only when GAS-derived assets are detected.
- `PLUGINS.md` + `PluginInventory/` are written by the separate `-run=ProjectPlugins` step.
- `MANIFEST.md` is written by the separate `-run=ProjectManifest` step (Phase 0).

## Per-asset deep dumps

Each Phase-1 asset writes siblings under `Assets/<package>`:

| File | What |
|---|---|
| `<Asset>.md` | Tier 1 human-readable summary (variables, function signatures, graph node counts, references). |
| `<Asset>.meta.json` | Tier 1 structured form (full export + coverage block). This rollup reads the JSON, not the `.md`. |
| `<Asset>.deep.md` | Tier 2 full per-node / per-pin / per-task dump _(only when `-DeepDump` was passed)_. |

Tier 2 coverage:

- **UBlueprint family** (`Blueprint`, `AnimBlueprint`, `WidgetBlueprint`, `ControlRigBlueprint`) and **StateTree** get the full `.deep.md`: every node with its pin table, every state with per-task instance data + instance object properties, full property bindings, and **nested instanced-subobject trees** for Instanced / EditInlineNew references (`AIPerception` sense configs, GAS attribute sets, anim layer overrides, etc.).
- **SmartObjectDefinition** gets full per-behavior-definition UPROPERTY tables and per-slot `FInstancedStruct` `DefinitionData` field values — exposes the `StateTreeReference` link from the SO definition to the StateTree that runs the interaction (e.g., `SO_BenchDefinition` → `ST_SmartObject_Bench`), plus entrance annotations (`Offset`, `bIsEntry`, `TrajectorySlotHeightOffset`, `TransitionCheckRadius`, etc.).
- **BehaviorTree** gets a per-node property-table dump — every composite / task / decorator / service in the tree renders its full UPROPERTY values, so the authored configuration (`AcceptableRadius` on a `BTTask_MoveTo`, `FlowAbortMode` on a `BTDecorator_Blackboard`, `Interval` on a `BTService_DefaultFocus`, Blackboard key selectors) is readable without opening the asset.
- **DataTable** gets per-row property tables — Tier 1 captures schema only (row struct, column list, row names), Tier 2 walks every row's `UScriptStruct` fields via `ExportTextItem_Direct` so the actual data (`Damage=15`, `Icon=/Game/UI/…`, `Tier=Common` on a row named `Sword_Iron`) is inline. Rows are alpha-sorted to match the Tier 1 name list positionally.
- **ChooserTable** gets full `FInstancedStruct` field tables per column + row + fallback + context entry — the authored values for each column (which enum a `FEnumColumn` reads, the per-row RowValues arrays, the range on each `FFloatRangeColumn`) and the asset paths / sub-choosers each row points at become inline instead of just type names.
- **EnvQuery** gets per-option generator + per-test UPROPERTY tables — Tier 1 records class + option order, Tier 2 adds the authored values (`Radius` on an `EnvQueryGenerator_SimpleGrid`, `TestPurpose` / `ScoringEquation` / `ClampMin` / `Weight` per test, trace config, tag filters, etc.).
- Other types (`PoseSearchDatabase`, `UserDefinedStruct`, `UserDefinedEnum`) get an out-of-scope `.deep.md` notice pointing back at the Tier 1 typed handler — those handlers already render near-complete shape in `.md`.

## Trust signals

Output follows a strict "never guess values" rule. When something can't be determined, it's marked, not substituted. Any value not bracketed by these markers is the actual authored value:

| Marker | Meaning |
|---|---|
| `[BROKEN]` on a pin type | Serializer couldn't resolve the pin's `SubCategoryObject` weak pointer (typically third-party PostLoad failures). The pin existed but its type is degraded; do not infer it. |
| `[instanced]` on a property type | Property points at one or more Instanced / EditInlineNew subobjects. Their full property tree is rendered as nested sub-sections immediately below the property table. |
| `**Truncated**` in an instanced subtree | Recursion-depth cap reached (`MAX_SUBOBJECT_RECURSION_DEPTH=8`); deeper subobjects exist but weren't walked. |
| `**Cycle detected**` in an instanced subtree | Subobject reference cycle; tree truncated to avoid infinite recursion. |
| `**Broken reference**` in an instanced subtree | Instanced slot existed but the referenced object was null at export time. |
| `(unresolved)` on a transition | StateTree transition target couldn't be resolved (rare; should not appear for any standard `Succeeded`/`Failed`/`NextState`/`GotoState` transition). |
| `(?)` in a pin connection | Cross-graph node title couldn't be resolved (cosmetic; observed only on identical sub-graph hash collisions in third-party rigs). |
| `_None_` / `_Empty graph._` | Genuinely empty container — not a serialization failure. |

