# BP_AnimNotify_FoleyEvent

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/AnimNotifies/BP_AnimNotify_FoleyEvent.BP_AnimNotify_FoleyEvent` |
| Asset name | `BP_AnimNotify_FoleyEvent` |
| Subclass | `Blueprint` |
| Blueprint type | `Const` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `AnimNotify` (`/Script/Engine.AnimNotify`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (7)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Event` | `struct<GameplayTag>` | `()` | `Default` | — | — | InstanceEditable |
| `Side` | `byte<E_FoleyEventSide>` | `NewEnumerator4` | `Default` | — | — | InstanceEditable |
| `VolumeMultiplier` | `real<double>` | `1.000000` | `Default` | — | — | InstanceEditable |
| `PitchMultiplier` | `real<double>` | `1.000000` | `Default` | — | — | InstanceEditable |
| `DefaultBank` | `object<DABP_FoleyAudioBank_C>` | `/Game/_ThirdParty/GASP_example/Audio/Foley/DABP_FoleyAudioBank.DABP_FoleyAudioBank_C'/Game/_ThirdParty/GASP_example/Audio/Foley/DefaultFoleyEventAudioBank.DefaultFoleyEventAudioBank'` | `Default` | — | — | InstanceEditable, Private |
| `VisLogDebugColor` | `struct<LinearColor>` | `(R=1.000000,G=0.054146,B=0.897670,A=1.000000)` | `Debug` | — | — | InstanceEditable, Private |
| `VisLogDebugText` | `string` | — | `Debug` | — | — | InstanceEditable, Private |

## Functions (2)

### `GetNotifyName`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(string ReturnValue)`
- Local variables: _none_
- Nodes: 7

### `Received_Notify`

- Access: `Public`
- Flags: —
- Inputs: `(object<SkeletalMeshComponent> MeshComp, object<AnimSequenceBase> Animation, struct<AnimNotifyEventReference>& EventReference [ref])`
- Outputs: `(bool ReturnValue)`
- Local variables (1): `FoleyEventComponent`
- Nodes: 21

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

Hard refs out (8):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Audio/Foley/AC_FoleyEvents` [asset]
- `/Game/_ThirdParty/GASP_example/Audio/Foley/DABP_FoleyAudioBank` [asset]
- `/Game/_ThirdParty/GASP_example/Audio/Foley/DefaultFoleyEventAudioBank` [asset]
- `/Game/_ThirdParty/GASP_example/Audio/Foley/S_FoleyEventParams` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/AnimNotifies/E_FoleyEventSide` [asset]
- `/Script/Engine.AnimNotify` [native]
- `/Script/GameplayTags` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Const`
- Subclass: `Blueprint`
- Custom metadata: _none_

