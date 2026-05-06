# UDW_and_Weather_Override_Volume_Interface

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_and_Weather_Override_Volume_Interface.UDW_and_Weather_Override_Volume_Interface` |
| Asset name | `UDW_and_Weather_Override_Volume_Interface` |
| Subclass | `Blueprint` |
| Blueprint type | `Interface` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Interface` (`/Script/CoreUObject.Interface`, native, module `/Script/CoreUObject`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (7)

### `Check for Material Refresh`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1
- Category: `Material Effects`

### `Force WOV Tick`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1
- Category: `Weather Override Volumes`

### `Get Next Random Weather and Timer Length`

- Access: `Public`
- Flags: —
- Inputs: `(object<Random_Weather_Variation_C> Random Weather Component)`
- Outputs: `(object<UDS_Weather_Settings_C> Next Preset, real<double> Timer Length)`
- Local variables: _none_
- Nodes: 2
- Category: `Random Weather`

### `Get Random Weather Mode`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte Mode)`
- Local variables: _none_
- Nodes: 2
- Category: `Random Weather`

### `Get Random Weather Probability Maps`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(TMap<object<UDS_Weather_Settings_C,>>, real> Spring, TMap<object<UDS_Weather_Settings_C,>>, real> Summer, TMap<object<UDS_Weather_Settings_C,>>, real> Autumn, TMap<object<UDS_Weather_Settings_C,>>, real> Winter)`
- Local variables: _none_
- Nodes: 2
- Category: `Random Weather`

### `Get Season Temperature Ranges`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector2D> Spring, struct<Vector2D> Summer, struct<Vector2D> Autumn, struct<Vector2D> Winter)`
- Local variables: _none_
- Nodes: 2
- Category: `Season`

### `Instant Material State Update`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1
- Category: `Material Effects`

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

Hard refs out (4):
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_RandomWeatherTiming` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Random_Weather_Variation` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings` [asset]
- `/Script/CoreUObject.Interface` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Interface`
- Subclass: `Blueprint`
- Custom metadata: _none_

