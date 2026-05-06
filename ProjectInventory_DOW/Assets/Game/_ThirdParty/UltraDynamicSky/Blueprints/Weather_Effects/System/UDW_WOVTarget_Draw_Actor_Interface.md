# UDW_WOVTarget_Draw_Actor_Interface

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WOVTarget_Draw_Actor_Interface.UDW_WOVTarget_Draw_Actor_Interface` |
| Asset name | `UDW_WOVTarget_Draw_Actor_Interface` |
| Subclass | `Blueprint` |
| Blueprint type | `Interface` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Interface` (`/Script/CoreUObject.Interface`, native, module `/Script/CoreUObject`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (2)

### `Canvas Space Update`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector2D> Corner Position, real<double> Width, int Resolution)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2
- Category: `WOV Target Draw Actor`

### `Draw to WOV Target`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_RenderTarget_State_C> WOV Render Target State, object<Canvas> Canvas, object<MaterialInstanceDynamic> WOV Target Brush MID, object<MaterialInstanceDynamic> Radial Storm Brush MID)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2
- Category: `WOV Target Draw Actor`

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

Hard refs out (2):
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_RenderTarget_State` [asset]
- `/Script/CoreUObject.Interface` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Interface`
- Subclass: `Blueprint`
- Custom metadata: _none_

