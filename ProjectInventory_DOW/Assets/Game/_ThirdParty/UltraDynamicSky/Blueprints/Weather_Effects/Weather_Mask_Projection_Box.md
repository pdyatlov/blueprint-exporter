# Weather_Mask_Projection_Box

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Mask_Projection_Box.Weather_Mask_Projection_Box` |
| Asset name | `Weather_Mask_Projection_Box` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (8)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Box Extent` | `struct<Vector>` | `(X=500.000000,Y=500.000000,Z=300.000000)` | `Settings` | — | — | InstanceEditable |
| `Mask Snow / Dust` | `real<double>` | `1.000000` | `Settings` | — | — | InstanceEditable |
| `Mask Wetness` | `real<double>` | `1.000000` | `Settings` | — | — | InstanceEditable |
| `Blur Radius` | `real<double>` | `100.000000` | `Settings` | — | — | InstanceEditable |
| `Blur Slope (Snow/Dust)` | `real<double>` | `1.000000` | `Settings` | — | — | InstanceEditable |
| `Blur Slope (Wetness)` | `real<double>` | `1.000000` | `Settings` | — | — | InstanceEditable |
| `Capture Pixel Size` | `int` | `5` | `Settings` | — | — | InstanceEditable |
| `Exclude Actors from Occlusion` | `TArray<object<Actor>>` | — | `Settings` | — | — | InstanceEditable |

## Functions (2)

### `Force Update`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `📘 Weather Mask Tools`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Settings`

## Macros (0)

_None._

## Components (2)

- `Billboard` — `BillboardComponent` @ socket `None`
  - `Weather_Mask_Projection_Box_Component` — `Weather_Mask_Projection_Box_Component_C` @ socket `None`
- `UDS_Utility_Opener` — `UDS_Utility_Opener_C` @ socket `None`

## Class Default Object (3)

- `bCanBeDamaged` (`uint8`) = `False`
- `bEnableAutoLODGeneration` (`uint8`) = `False`
- `PrimaryActorTick` (`FActorTickFunction`) = `(bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `UserConstructionScript` (32 nodes)
- Additional graphs: _none_

## References

Hard refs out (7):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Components/Weather_Mask_Projection_Box_Component` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/WeatherMask` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather_Mask_Projection_Box` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

