# DABP_FoleyAudioBank

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Audio/Foley/DABP_FoleyAudioBank.DABP_FoleyAudioBank` |
| Asset name | `DABP_FoleyAudioBank` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `PrimaryDataAsset` (`/Script/Engine.PrimaryDataAsset`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (1)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Assets` | `TMap<struct<SoundBase>>, object:/Script/Engine.SoundBase>` | `()` | `Default` | — | — | InstanceEditable, Private |

## Functions (1)

### `GetSoundFromFoleyEvent`

- Access: `Public`
- Flags: —
- Inputs: `(struct<GameplayTag>& Event [ref])`
- Outputs: `(object<SoundBase> Sound, bool Success)`
- Local variables: _none_
- Nodes: 8

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0) — DataAsset

_No authored overrides found on the CDO. `DataAsset` Blueprints typically author their payload here — if this BP is meant to differ from its parent class, this is a coverage gap._

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (4):
- `/Script/AudioExtensions` [asset]
- `/Script/Engine.PrimaryDataAsset` [native]
- `/Script/GameplayTags` [asset]
- `/Script/MetasoundEngine` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

