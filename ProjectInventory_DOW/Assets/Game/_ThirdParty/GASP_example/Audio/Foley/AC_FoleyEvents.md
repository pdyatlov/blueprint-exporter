# AC_FoleyEvents

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Audio/Foley/AC_FoleyEvents.AC_FoleyEvents` |
| Asset name | `AC_FoleyEvents` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ActorComponent` (`/Script/Engine.ActorComponent`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (3)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `FoleyEventBank` | `object<DABP_FoleyAudioBank_C>` | `/Game/_ThirdParty/GASP_example/Audio/Foley/DABP_FoleyAudioBank.DABP_FoleyAudioBank_C'/Game/_ThirdParty/GASP_example/Audio/Foley/DefaultFoleyEventAudioBank.DefaultFoleyEventAudioBank'` | `Default` | — | — | InstanceEditable, Private |
| `VisLogDebugText` | `string` | — | `Debug` | — | — | InstanceEditable, Private |
| `VisLogDebugColor` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=1.000000)` | `Debug` | — | — | InstanceEditable, Private |

## Functions (3)

### `CanPlayFoley`

- Access: `Private`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Result)`
- Local variables: _none_
- Nodes: 4
- Category: `Private`

### `PlayFoleyEvent`

- Access: `Public`
- Flags: —
- Inputs: `(struct<GameplayTag> Event, struct<S_FoleyEventParams> Params)`
- Outputs: `(object<AudioComponent> AudioComponent)`
- Local variables: _none_
- Nodes: 15

### `TriggerVisLog`

- Access: `Private`
- Flags: —
- Inputs: `(struct<S_FoleyEventParams>& Params [ref], byte Params_Side_9_D749B6B548D0A4778009A58DC6BD468F, real<double> Params_Volume_4_693373E847A8B941D3BDCEA05B20F090, real<double> Params_Pitch_3_45F5C1C94A5CC32B504F1B8A7D38320C)`
- Outputs: `()`
- Local variables (1): `MeshComponent`
- Nodes: 17
- Category: `Private`

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (8):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Audio/Foley/DABP_FoleyAudioBank` [asset]
- `/Game/_ThirdParty/GASP_example/Audio/Foley/DefaultFoleyEventAudioBank` [asset]
- `/Game/_ThirdParty/GASP_example/Audio/Foley/I_FoleyAudioBankInterface` [asset]
- `/Game/_ThirdParty/GASP_example/Audio/Foley/S_FoleyEventParams` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/AnimNotifies/E_FoleyEventSide` [asset]
- `/Script/Engine.ActorComponent` [native]
- `/Script/GameplayTags` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

