# UDS_Occlusion_Volume

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Occlusion/UDS_Occlusion_Volume.UDS_Occlusion_Volume` |
| Asset name | `UDS_Occlusion_Volume` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UDS_Volume_Actor_C` (`/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Volume_Actor.UDS_Volume_Actor_C`, blueprint)
- Interfaces: _none_

## Variables (3)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Affects Sound Occlusion / Interior Adjusments` | `bool` | `True` | `Occlusion` | — | — | InstanceEditable |
| `Occlusion Multiplier` | `real<double>` | `0.000000` | `Occlusion` | — | — | InstanceEditable |
| `Block Weather Particles` | `bool` | `False` | `Occlusion` | — | — | InstanceEditable |

## Functions (3)

### `Configure Weather Particle Blocking`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9

### `Query Occlusion Multiplier`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Location)`
- Outputs: `(real<double> Multiplier, real<double> Multiplier)`
- Local variables: _none_
- Nodes: 9

### `📘 Player Occlusion`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Occlusion`

## Macros (0)

_None._

## Components (1)

- `UDS_Utility_Opener` — `UDS_Utility_Opener_C` @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (2 nodes)
- Construction script: `UserConstructionScript` (3 nodes)
- Additional graphs: _none_

## References

Hard refs out (7):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Volume_Actor` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Volume_Actor.UDS_Volume_Actor_C` [Blueprint]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/UltraDynamicWeather_Parameters` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/OcclusionVolume` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

