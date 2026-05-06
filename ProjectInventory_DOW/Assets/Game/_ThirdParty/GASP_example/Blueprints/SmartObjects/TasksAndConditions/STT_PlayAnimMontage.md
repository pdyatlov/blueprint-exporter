# STT_PlayAnimMontage

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/TasksAndConditions/STT_PlayAnimMontage.STT_PlayAnimMontage` |
| Asset name | `STT_PlayAnimMontage` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `StateTreeTaskBlueprintBase` (`/Script/StateTreeModule.StateTreeTaskBlueprintBase`, native, module `/Script/StateTreeModule`)
- Interfaces: _none_

## Variables (12)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Actor` | `object<Actor>` | `None` | `Context` | — | — | InstanceEditable, Private |
| `Montage to Play` | `object<AnimMontage>` | `None` | `Default` | — | — | InstanceEditable |
| `Start Time` | `real<float>` | `0.000000` | `Default` | — | — | InstanceEditable |
| `Play Time` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable |
| `Play Time Variance` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable |
| `Play Rate` | `real<float>` | `1.000000` | `Default` | — | — | InstanceEditable |
| `Number Of Loops` | `int` | `0` | `Default` | — | — | InstanceEditable |
| `Ignore Collision` | `bool` | `False` | `Default` | — | — | InstanceEditable |
| `Mover Component` | `object<CharacterMoverComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Slot Handle` | `struct<SmartObjectClaimHandle>` | `()` | `Input` | — | — | InstanceEditable, Private |
| `Smart Object Anim Component` | `object<AC_SmartObjectAnimation_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Smart Object Actor` | `object<Actor>` | `None` | `Input` | — | — | InstanceEditable, Private |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (21 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (6):
- `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/AC_SmartObjectAnimation` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/SmartObjectAnimationPayload` [asset]
- `/Script/Mover` [asset]
- `/Script/SmartObjectsModule` [asset]
- `/Script/StateTreeModule` [asset]
- `/Script/StateTreeModule.StateTreeTaskBlueprintBase` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

