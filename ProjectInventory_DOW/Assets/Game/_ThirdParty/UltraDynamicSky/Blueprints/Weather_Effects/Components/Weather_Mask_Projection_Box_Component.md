# Weather_Mask_Projection_Box_Component

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Components/Weather_Mask_Projection_Box_Component.Weather_Mask_Projection_Box_Component` |
| Asset name | `Weather_Mask_Projection_Box_Component` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `WeatherMask_C` (`/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/WeatherMask.WeatherMask_C`, blueprint)
- Interfaces: _none_

## Variables (17)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `SceneCaptureComponent2D` | `object<SceneCaptureComponent2D>` | `None` | `Weather Mask` | — | — | InstanceEditable, Private |
| `Blur Radius` | `real<double>` | `100.000000` | `Projection Box Settings` | — | — | InstanceEditable |
| `Blur Slope (Wetness)` | `real<double>` | `1.000000` | `Projection Box Settings` | — | — | InstanceEditable |
| `Blur Slope (Snow/Dust)` | `real<double>` | `1.000000` | `Projection Box Settings` | — | — | InstanceEditable |
| `Capture Pixel Size` | `int` | `5` | `Projection Box Settings` | — | — | InstanceEditable |
| `Exclude Actors from Occlusion` | `TArray<object<Actor>>` | — | `Projection Box Settings` | — | — | InstanceEditable |
| `Mask_MID` | `object<MaterialInstanceDynamic>` | `None` | `Weather Mask` | — | — | InstanceEditable, Private |
| `Height_MID` | `object<MaterialInstanceDynamic>` | `None` | `Weather Mask` | — | — | InstanceEditable, Private |
| `Top Height` | `real<double>` | `0.000000` | `Weather Mask` | — | — | InstanceEditable, Private |
| `Capture Box Size` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Weather Mask` | — | — | InstanceEditable, Private |
| `Depth Render Target` | `object<TextureRenderTarget2D>` | `None` | `Weather Mask` | — | — | InstanceEditable, Private |
| `Capture X Resolution` | `int` | `0` | `Weather Mask` | — | — | InstanceEditable, Private |
| `Height Dilation` | `real<double>` | `10.000000` | `Projection Box Settings` | — | — | InstanceEditable |
| `Recycle Scene Capture for Repeated Mask Draws` | `bool` | `True` | `Projection Box Settings` | — | — | InstanceEditable |
| `UDW Runtime` | `bool` | `False` | `Weather Mask` | — | — | InstanceEditable, Private |
| `Draw Position` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Weather Mask` | — | — | InstanceEditable, Private |
| `Draw Size` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Weather Mask` | — | — | InstanceEditable, Private |

## Functions (9)

### `Calculate Masking At Location`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Location = 0, 0, 0)`
- Outputs: `(struct<Vector2D> Mask, bool Cancel All Masks, struct<Vector2D> Mask, bool Cancel All Masks)`
- Local variables (5): `Number of Traces`, `1 Trace Vector`, `5 Trace Vectors`, `9 Trace Vectors`, `Total Occlusion`
- Nodes: 58

### `Draw to Height Canvas`

- Access: `Public`
- Flags: —
- Inputs: `(object<Canvas> Height Canvas, object<UDS_RenderTarget_State_C> Target State, object<MaterialInstanceDynamic> Draw MID)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 9

### `Draw to Mask Canvas`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_RenderTarget_State_C> Target State, object<Canvas> Mask Canvas, object<Ultra_Dynamic_Weather_C> UDW)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 22

### `Get Brush Scale`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector2D> Out)`
- Local variables: _none_
- Nodes: 4

### `Prepare for Drawing`

- Access: `Public`
- Flags: —
- Inputs: `(object<Ultra_Dynamic_Weather_C> UDW)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 80

### `Recycle Render Target`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

### `Unready`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `Update Capture`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Y Resolution`
- Nodes: 60

### `Update Mask Values`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (5 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (8):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_RenderTarget_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/WeatherMask` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/WeatherMask.WeatherMask_C` [Blueprint]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/WeatherMaskComponentInterface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Projection_Box_Height` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Projection_Box_Mask` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

