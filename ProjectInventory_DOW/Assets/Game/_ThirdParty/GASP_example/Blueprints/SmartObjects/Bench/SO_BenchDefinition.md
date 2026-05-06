# SO_BenchDefinition

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/Bench/SO_BenchDefinition.SO_BenchDefinition` |
| Asset name | `SO_BenchDefinition` |
| Asset type | `SmartObjectDefinition` |
| Parent class | `/Script/Engine.DataAsset` |
| Slots | **2** |
| Default behaviors | 1 |
| Activity tags | 0 |
| Preconditions set | no |
| Parameters (bag) | 0 |
| Tag filtering policy | `Override` |
| Tag merging policy | `Override` |
| World condition schema | `/Script/SmartObjectsModule.SmartObjectWorldConditionSchema` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |

## Object-level Tags & Data

- User tag filter: ` ANY_EXACT( SmartObject.ObjectType.NPC, SmartObject.ObjectType.Player )`

## Default Behavior Definitions (1)

| # | Path |
|---:|---|
| 0 | `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/Bench/SO_BenchDefinition.SO_BenchDefinition:GameplayInteractionSmartObjectBehaviorDefinition_0` |

## Slots (2)

### Slot 0 — `BenchSlot1`

| Field | Value |
|---|---|
| Offset | (0.00, 45.00, 0.00) |
| Rotation | (P=0.00, Y=0.00, R=0.00) |
| Enabled | yes |
| Activity tags | 0 |
| Runtime tags | 0 |
| User tag filter | _empty_ |
| Selection preconditions | _unset_ |
| Behavior definitions | 0 |
| DefinitionData entries | 1 |

DefinitionData (1):
- `/Script/SmartObjectsModule.SmartObjectSlotEntranceAnnotation`

### Slot 1 — `BenchSlot2`

| Field | Value |
|---|---|
| Offset | (0.00, -45.00, 0.00) |
| Rotation | (P=0.00, Y=0.00, R=0.00) |
| Enabled | yes |
| Activity tags | 0 |
| Runtime tags | 0 |
| User tag filter | _empty_ |
| Selection preconditions | _unset_ |
| Behavior definitions | 0 |
| DefinitionData entries | 1 |

DefinitionData (1):
- `/Script/SmartObjectsModule.SmartObjectSlotEntranceAnnotation`

