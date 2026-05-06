# STT_AddCooldown

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/TasksAndConditions/STT_AddCooldown.STT_AddCooldown` |
| Asset name | `STT_AddCooldown` |
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
| `CooldownName` | `string` | — | `Default` | — | — | InstanceEditable |
| `Cooldown Tag` | `struct<GameplayTag>` | `()` | `Default` | — | — | InstanceEditable |
| `Cooldown Time` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable |
| `AIController` | `object<AIController>` | `None` | `Context` | — | — | InstanceEditable, Private |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (12 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (5):
- `/Game/_ThirdParty/GASP_example/Blueprints/AI/AIC_NPC_SmartObject` [asset]
- `/Script/AIModule` [asset]
- `/Script/GameplayTags` [asset]
- `/Script/StateTreeModule` [asset]
- `/Script/StateTreeModule.StateTreeTaskBlueprintBase` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

