# WeatherMaskComponentInterface

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/WeatherMaskComponentInterface.WeatherMaskComponentInterface` |
| Asset name | `WeatherMaskComponentInterface` |
| Subclass | `Blueprint` |
| Blueprint type | `Interface` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Interface` (`/Script/CoreUObject.Interface`, native, module `/Script/CoreUObject`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (3)

### `Draw to Height Canvas`

- Access: `Public`
- Flags: —
- Inputs: `(object<Canvas> Height Canvas, object<UDS_RenderTarget_State_C> Target State, object<MaterialInstanceDynamic> Draw MID)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2

### `Draw to Mask Canvas`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_RenderTarget_State_C> Target State, object<Canvas> Mask Canvas, object<Ultra_Dynamic_Weather_C> UDW)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2

### `Mask Outside of Target`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1

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

Hard refs out (3):
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_RenderTarget_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` [asset]
- `/Script/CoreUObject.Interface` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Interface`
- Subclass: `Blueprint`
- Custom metadata: _none_

