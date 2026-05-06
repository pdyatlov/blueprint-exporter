# UDS_Cloud_Paint_Container

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Cloud_Paint_Container.UDS_Cloud_Paint_Container` |
| Asset name | `UDS_Cloud_Paint_Container` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces (2):
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_CloudPaintActor_Interface.UDS_CloudPaintActor_Interface_C`
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArray_ManagedActor.UDS_InterfaceActorArray_ManagedActor_C`

## Variables (7)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Cloud Painting Cell Data` | `TMap<struct<UDS_Cloud_Paint_Cell_C>>, object:/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Cloud_Paint_Cell.UDS_Cloud_Paint_Cell_C>` | `()` | `Cloud Painting` | — | — | InstanceEditable |
| `Cloud Painting Cell Size` | `int` | `10000000` | `Cloud Painting` | — | — | InstanceEditable |
| `Cloud Painting Cell Resolution` | `int` | `0` | `Hidden Exposed` | — | — | InstanceEditable |
| `Cell Render Targets` | `TMap<struct<TextureRenderTarget2D>>, object:/Script/Engine.TextureRenderTarget2D>` | `()` | `Hidden Exposed` | — | — | InstanceEditable |
| `Active` | `bool` | `True` | `Cloud Painting` | — | — | InstanceEditable |
| `Asset Code` | `string` | — | `Default` | — | — | InstanceEditable, Private |
| `Loaded Cell Textures` | `TMap<struct<Texture>>, object:/Script/Engine.Texture>` | `()` | `Default` | — | — | InstanceEditable, Private |

## Functions (7)

### `Activate`

- Access: `Public`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10
- Category: `Cloud Painting`
- Description: Call to turn on a container which is inactive. This will turn it on and also turn off all other containers present to avoid conflicts, then call the update function on UDS to redraw the painted coverage target.

### `Apply Effect to Cloud Coverage Value`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_CloudPaintActor_Interface.UDS_CloudPaintActor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Sample Location = 0, 0, 0, real<double>& Cloud Coverage = 0.0 [ref], real<double> Painted Opacity = 0.0)`
- Outputs: `(bool Success)`
- Local variables (5): `Location in Cell Space`, `Cell Coordinates Sampled`, `Current Cell Data`, `Location in Texture Space`, `Filtered Color`
- Nodes: 61

### `Deactivate`

- Access: `Public`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Cloud Painting`
- Description: Call to turn off a container which is active. This will turn it off and then call the update function on UDS to redraw the painted coverage target.

### `Draw to Cloud Paint Target`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_CloudPaintActor_Interface.UDS_CloudPaintActor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `(object<Canvas> Canvas, object<MaterialInstanceDynamic> Radial Storm Draw MID, struct<Vector> Target Mapping = 0, 0, 0, int Target Res = 0, bool& Can Add Coverage = false [ref], bool& Can Subtract Coverage = false [ref], bool Cloud Painting Active = false)`
- Outputs: `(bool Success)`
- Local variables (8): `Target Location`, `Lower Right Corner`, `X Cell Min`, `Y Cell Min`, `X Cell Max`, `Y Cell Max`, `Cells Used`, `Current Cell`
- Nodes: 131

### `Get Priority`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArray_ManagedActor.UDS_InterfaceActorArray_ManagedActor_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(int Priority)`
- Local variables: _none_
- Nodes: 2

### `Include in Filtered Array`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArray_ManagedActor.UDS_InterfaceActorArray_ManagedActor_C`
- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Filtering Location = 0, 0, 0)`
- Outputs: `(bool Include)`
- Local variables: _none_
- Nodes: 3

### `🖌️ Open Painter`

- Access: `Public`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Cloud Painting`
- Description: Opens the Volumetric Cloud Painter utility, to paint cloud coverage into this container.

## Macros (0)

_None._

## Components (3)

- `Billboard` — `BillboardComponent` @ socket `None`
  - `SceneCaptureComponent2D` — `SceneCaptureComponent2D` @ socket `None`
- `UDS_Utility_Opener_Component` — `UDS_Utility_Opener_C` @ socket `None`
- `UDS_InterfaceActorArray_Reporter` — `UDS_InterfaceActorArray_Reporter_C` @ socket `None`

## Class Default Object (2)

- `bEnableAutoLODGeneration` (`uint8`) = `False`
- `bIsSpatiallyLoaded` (`uint8`) = `False`

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `UserConstructionScript` (9 nodes)
- Additional graphs: _none_

## References

Hard refs out (14):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_RunContext` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Cloud_Paint_Cell` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_CloudPaintActor_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArray_ManagedActor` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArray_Reporter` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArrayManager` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Volumetric_Cloud_Painter` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/CloudPainter_Icon` [asset]
- `/Script/Blutility` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

