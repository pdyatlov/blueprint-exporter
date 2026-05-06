# BP_NotifyState_MontageBlendOut

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/AnimNotifies/BP_NotifyState_MontageBlendOut.BP_NotifyState_MontageBlendOut` |
| Asset name | `BP_NotifyState_MontageBlendOut` |
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
| `BlendOutCondition` | `byte<E_TraversalBlendOutCondition>` | `NewEnumerator0` | `Default` | — | — | InstanceEditable |
| `BlendOutTime` | `real<double>` | `0.200000` | `Default` | — | — | InstanceEditable |
| `BlendProfile` | `name` | `FastFeet_InstantRoot` | `Default` | — | — | InstanceEditable |

## Functions (2)

### `GetNotifyName`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(string ReturnValue)`
- Local variables: _none_
- Nodes: 5

### `Received_NotifyTick`

- Access: `Public`
- Flags: —
- Inputs: `(object<SkeletalMeshComponent> MeshComp, object<AnimSequenceBase> Animation, real<float> FrameDeltaTime = 0.0, struct<AnimNotifyEventReference>& EventReference [ref])`
- Outputs: `(bool ReturnValue)`
- Local variables (5): `Character`, `AnimInstance`, `AnimMontage`, `ShouldBlendOut`, `CharacterProperties`
- Nodes: 40

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

Hard refs out (5):
- `/Game/_ThirdParty/GASP_example/Blueprints/AnimNotifies/E_TraversalBlendOutCondition` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_Pawn` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_MovementMode` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_CharacterPropertiesForAnimation` [asset]
- `/Script/Engine.AnimNotifyState` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Const`
- Subclass: `Blueprint`
- Custom metadata: _none_

