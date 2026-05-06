# STT_FindSmartObject

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/TasksAndConditions/STT_FindSmartObject.STT_FindSmartObject` |
| Asset name | `STT_FindSmartObject` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `StateTreeTaskBlueprintBase` (`/Script/StateTreeModule.StateTreeTaskBlueprintBase`, native, module `/Script/StateTreeModule`)
- Interfaces: _none_

## Variables (8)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Actor` | `object<Actor>` | `None` | `Context` | — | — | InstanceEditable |
| `SearchType` | `byte<SmartObjectSearchType>` | `NewEnumerator0` | `Default` | — | — | InstanceEditable |
| `Search Box Extents` | `struct<Vector>` | `(X=2000.000000,Y=2000.000000,Z=2000.000000)` | `Default` | — | — | InstanceEditable |
| `Smart Object` | `object<Actor>` | `None` | `Output` | — | — | InstanceEditable |
| `CandidateSlot` | `struct<SmartObjectSlotHandle>` | `()` | `Output` | — | — | InstanceEditable |
| `SearchResults` | `TArray<struct<SmartObjectRequestResult>>` | — | `Default` | — | — | InstanceEditable, Private |
| `Index` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `Search Result` | `struct<SmartObjectRequestResult>` | `()` | `Internal` | — | — | InstanceEditable, Private |

## Functions (1)

### `Find Slot Using Distance`

- Access: `Public`
- Flags: —
- Inputs: `(TArray<struct<SmartObjectRequestResult>> In Results, bool Closest)`
- Outputs: `(struct<SmartObjectRequestResult> Out Result)`
- Local variables (4): `Out Slot`, `Current Best Distance`, `Current Index`, `Current Smart Object Result`
- Nodes: 32

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (61 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (7):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/TasksAndConditions/SmartObjectSearchType` [asset]
- `/Script/GameplayInteractionsModule` [asset]
- `/Script/GameplayTags` [asset]
- `/Script/SmartObjectsModule` [asset]
- `/Script/StateTreeModule` [asset]
- `/Script/StateTreeModule.StateTreeTaskBlueprintBase` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

