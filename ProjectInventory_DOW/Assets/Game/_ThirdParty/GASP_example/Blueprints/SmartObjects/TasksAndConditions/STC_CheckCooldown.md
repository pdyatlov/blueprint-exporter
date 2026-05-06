# STC_CheckCooldown

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/TasksAndConditions/STC_CheckCooldown.STC_CheckCooldown` |
| Asset name | `STC_CheckCooldown` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `StateTreeConditionBlueprintBase` (`/Script/StateTreeModule.StateTreeConditionBlueprintBase`, native, module `/Script/StateTreeModule`)
- Interfaces: _none_

## Variables (2)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `AIController` | `object<AIController>` | `None` | `Context` | — | — | InstanceEditable |
| `CooldownName` | `string` | — | `Default` | — | — | InstanceEditable |

## Functions (2)

### `ReceiveGetDescription`

- Access: `Protected`
- Flags: —
- Inputs: `(byte Formatting = RichText)`
- Outputs: `(text ReturnValue)`
- Local variables: _none_
- Nodes: 4

### `ReceiveTestCondition`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue, bool ReturnValue, bool ReturnValue)`
- Local variables (1): `AIC Smart Obj`
- Nodes: 22

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (2)

- `IconColor` (`FColor`) = `(B=127,G=239,R=255,A=255)`
- `IconName` (`FName`) = `EditorStyle|EditorViewport.ToggleRealTime`

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (4):
- `/Game/_ThirdParty/GASP_example/Blueprints/AI/AIC_NPC_SmartObject` [asset]
- `/Script/AIModule` [asset]
- `/Script/StateTreeModule` [asset]
- `/Script/StateTreeModule.StateTreeConditionBlueprintBase` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

