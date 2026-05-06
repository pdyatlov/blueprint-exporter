# Weather_Mask_Brush

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Mask_Brush.Weather_Mask_Brush` |
| Asset name | `Weather_Mask_Brush` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (4)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Brush` | `byte<UDS_Weather_Mask_Brush>` | `NewEnumerator0` | `Settings` | — | — | InstanceEditable |
| `Mask Wetness` | `real<double>` | `1.000000` | `Settings` | — | — | InstanceEditable |
| `Mask Snow/Dust` | `real<double>` | `1.000000` | `Settings` | — | — | InstanceEditable |
| `Cancel Masks Above` | `bool` | `False` | `Settings` | — | — | InstanceEditable |

## Functions (2)

### `📘 Weather Mask Tools`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Settings`

### `🖌️ Weather Mask Brush Painter`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `Settings`

## Macros (0)

_None._

## Components (2)

- `Billboard` — `BillboardComponent` @ socket `None`
  - `Weather_Mask_Brush_Component` — `Weather_Mask_Brush_Component_C` @ socket `None`
- `UDS_Utility_Opener_Component` — `UDS_Utility_Opener_C` @ socket `None`

## Class Default Object (3)

- `ActorLabel` (`FString`) = `Weather_Decal-1`
- `bEnableAutoLODGeneration` (`uint8`) = `False`
- `PrimaryActorTick` (`FActorTickFunction`) = `(bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `UserConstructionScript` (19 nodes)
- Additional graphs: _none_

## References

Hard refs out (11):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Weather_Mask_Brush` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Tools/Weather_Mask_Brush_Painter` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Components/Weather_Mask_Brush_Component` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/WeatherMask` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather_Mask_Brush` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/Black` [asset]
- `/Script/Blutility` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

