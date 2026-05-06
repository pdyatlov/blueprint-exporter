# STT_ClaimSlot

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/TasksAndConditions/STT_ClaimSlot.STT_ClaimSlot` |
| Asset name | `STT_ClaimSlot` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `StateTreeTaskBlueprintBase` (`/Script/StateTreeModule.StateTreeTaskBlueprintBase`, native, module `/Script/StateTreeModule`)
- Interfaces: _none_

## Variables (4)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Actor` | `object<Actor>` | `None` | `Context` | — | — | InstanceEditable |
| `ClaimedHandle` | `struct<SmartObjectClaimHandle>` | `()` | `Output` | — | — | InstanceEditable, Private |
| `SlotToBeClaimed` | `struct<SmartObjectSlotHandle>` | `()` | `Input` | — | — | InstanceEditable, Private |
| `SmartObject` | `object<Actor>` | `None` | `Input` | — | — | InstanceEditable, Private |

## Functions (1)

### `IsSlotFreeOrFindNewSlot`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<SmartObjectSlotHandle> Candidate Slot To be Claimed, struct<SmartObjectSlotHandle> Candidate Slot To be Claimed)`
- Local variables: _none_
- Nodes: 17

## Macros (1)

### `IsHandleFree`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (5 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (5):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
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

