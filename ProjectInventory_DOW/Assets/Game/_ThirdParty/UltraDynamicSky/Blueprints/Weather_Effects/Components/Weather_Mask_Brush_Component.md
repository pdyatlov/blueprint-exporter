# Weather_Mask_Brush_Component

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Components/Weather_Mask_Brush_Component.Weather_Mask_Brush_Component` |
| Asset name | `Weather_Mask_Brush_Component` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `WeatherMask_C` (`/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/WeatherMask.WeatherMask_C`, blueprint)
- Interfaces: _none_

## Variables (12)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Brush` | `byte<UDS_Weather_Mask_Brush>` | `NewEnumerator0` | `Settings` | — | — | InstanceEditable |
| `Cancel Masks Above` | `bool` | `False` | `Settings` | — | — | InstanceEditable |
| `Brush Texture` | `object<Texture>` | `None` | `Weather Mask Brush` | — | — | InstanceEditable, Private |
| `Brush Color` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=0.000000)` | `Weather Mask Brush` | — | — | InstanceEditable, Private |
| `Painted Brush Texture` | `object<Texture2D>` | `/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/Black.Black'` | `Settings` | — | — | InstanceEditable |
| `Painted Masked Coordinates` | `TArray<struct<IntPoint>>` | — | `Painted Brush` | — | — | InstanceEditable, Private |
| `Mask Buffer Resolution` | `struct<IntPoint>` | `(X=1,Y=1)` | `Painted Brush` | — | — | InstanceEditable, Private |
| `Painted Brush Resolution` | `struct<IntPoint>` | `(X=0,Y=0)` | `Painted Brush` | — | — | InstanceEditable, Private |
| `Brush Painting RT` | `object<TextureRenderTarget2D>` | `None` | `Painted Brush` | — | — | InstanceEditable, Private |
| `Brush Painting Active` | `bool` | `False` | `Painted Brush` | — | — | InstanceEditable, Private |
| `Draw Position` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Weather Mask Brush` | — | — | InstanceEditable, Private |
| `Draw Size` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Weather Mask Brush` | — | — | InstanceEditable, Private |

## Functions (5)

### `Calculate Masking At Location`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Location = 0, 0, 0)`
- Outputs: `(struct<Vector2D> Mask, bool Cancel All Masks, struct<Vector2D> Mask, bool Cancel All Masks, struct<Vector2D> Mask, bool Cancel All Masks)`
- Local variables (2): `Centered UV`, `Mask Value`
- Nodes: 78

### `Draw to Height Canvas`

- Access: `Public`
- Flags: —
- Inputs: `(object<Canvas> Height Canvas, object<UDS_RenderTarget_State_C> Target State, object<MaterialInstanceDynamic> Draw MID)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 19

### `Draw to Mask Canvas`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_RenderTarget_State_C> Target State, object<Canvas> Mask Canvas, object<Ultra_Dynamic_Weather_C> UDW)`
- Outputs: `(bool Success)`
- Local variables (3): `Screen Position`, `Screen Size`, `NewLocalVar`
- Nodes: 23

### `Prepare for Drawing`

- Access: `Public`
- Flags: —
- Inputs: `(object<Ultra_Dynamic_Weather_C> UDW)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14

### `Update Mask Values`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `StaticMesh` (`TObjectPtr<UStaticMesh>`) = `/Script/Engine.StaticMesh'/Game/_ThirdParty/UltraDynamicSky/Meshes/Brush_Square.Brush_Square'`

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (13):
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Weather_Mask_Brush` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_RenderTarget_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/WeatherMask` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/WeatherMask.WeatherMask_C` [Blueprint]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/WeatherMaskComponentInterface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/Brush_Square` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/Black` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Weather/Mask_Brushes/Brush_Circle` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Weather/Mask_Brushes/Brush_Falloff` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Weather/Mask_Brushes/Brush_Pyramid` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Weather/Mask_Brushes/Brush_Radial` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Weather/Mask_Brushes/Brush_Square` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

