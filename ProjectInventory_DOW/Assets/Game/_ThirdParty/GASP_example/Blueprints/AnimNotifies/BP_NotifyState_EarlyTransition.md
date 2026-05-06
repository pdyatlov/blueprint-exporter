# BP_NotifyState_EarlyTransition

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/AnimNotifies/BP_NotifyState_EarlyTransition.BP_NotifyState_EarlyTransition` |
| Asset name | `BP_NotifyState_EarlyTransition` |
| Subclass | `Blueprint` |
| Blueprint type | `Const` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `AnimNotifyState` (`/Script/Engine.AnimNotifyState`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (3)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `TransitionDestination` | `byte<E_EarlyTransition_Destination>` | `NewEnumerator0` | `Default` | — | — | InstanceEditable |
| `TransitionCondition` | `byte<E_EarlyTransition_Condition>` | `NewEnumerator1` | `Default` | — | — | InstanceEditable |
| `GaitNotEqual` | `byte<E_Gait>` | `NewEnumerator0` | `Default` | — | — | InstanceEditable |

## Functions (2)

### `GetNotifyName`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(string ReturnValue)`
- Local variables: _none_
- Nodes: 15

### `Received_NotifyTick`

- Access: `Public`
- Flags: —
- Inputs: `(object<SkeletalMeshComponent> MeshComp, object<AnimSequenceBase> Animation, real<float> FrameDeltaTime = 0.0, struct<AnimNotifyEventReference>& EventReference [ref])`
- Outputs: `(bool ReturnValue)`
- Local variables (3): `ABPSanboxCharacter`, `Transition`, `ABP`
- Nodes: 26

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (6):
- `/Game/_ThirdParty/GASP_example/Blueprints/AnimNotifies/E_EarlyTransition_Condition` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/AnimNotifies/E_EarlyTransition_Destination` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_ABP` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_Gait` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/SandboxCharacter_CMC_ABP` [asset]
- `/Script/Engine.AnimNotifyState` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Const`
- Subclass: `Blueprint`
- Custom metadata: _none_

