# LevelBlock

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/LevelBlock.LevelBlock` |
| Asset name | `LevelBlock` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (11)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Randomize Button` | `object<LevelButton_C>` | `None` | `Default` | — | — | InstanceEditable |
| `InitialTransform` | `struct<Transform>` | `(Rotation=(X=0.000000,Y=-0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000))` | `Default` | — | — | InstanceEditable, Private |
| `MinTransformOffset` | `struct<Transform>` | `(Rotation=(X=0.000000,Y=-0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=0.000000,Y=0.000000,Z=0.000000))` | `Default` | — | — | InstanceEditable |
| `MaxTransformOffset` | `struct<Transform>` | `(Rotation=(X=0.000000,Y=-0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=0.000000,Y=0.000000,Z=0.000000))` | `Default` | — | — | InstanceEditable |
| `Name` | `text` | — | `Default` | — | — | InstanceEditable |
| `AutoNameFromHeight` | `bool` | `False` | `Default` | — | — | InstanceEditable |
| `UseLevelVisualsColor` | `bool` | `True` | `Default` | — | — | InstanceEditable |
| `ColorGroup` | `name` | `Blocks` | `Default` | — | — | InstanceEditable |
| `MaterialParams` | `struct<S_GridMaterialParams>` | `(GridColor_2_93C9D1544CE9BC2796D83F9E713DAB23=(R=1.000000,G=1.000000,B=1.000000,A=0.500000),SurfaceColor_4_9B668B134E34B8A2B41BB98E51273395=(R=0.121569,G=0.121569,B=0.121569,A=1.000000),GridSizes_16_782DDA9B42440FAB466A829B7C2E5482=(X=100.000000,Y=200.000000,Z=200.000000),Specularity_21_1B077FB34A0BA551F2D806BF119B8EA8=0.050000)` | `Default` | — | — | InstanceEditable |
| `BaseMaterial` | `object<MaterialInterface>` | `/Script/Engine.Material'/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Materials/M_Grid.M_Grid'` | `Default` | — | — | InstanceEditable |
| `DynamicMaterial` | `object<MaterialInstanceDynamic>` | `None` | `Default` | — | — | InstanceEditable, Private |

## Functions (2)

### `UpdateMaterials`

- Access: `Public`
- Flags: —
- Inputs: `(struct<S_GridMaterialParams>& Params [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12

### `UpdateText`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`
  - `StaticMesh` — `StaticMeshComponent` @ socket `None`
    - `TextRender` — `TextRenderComponent` @ socket `None`

## Class Default Object (1)

- `SpriteScale` (`float`) = `0.000000`

## Graphs

- Event graph: `EventGraph` (25 nodes)
- Construction script: `UserConstructionScript` (28 nodes)
- Additional graphs: _none_

## References

Hard refs out (8):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Data/S_GridMaterialParams` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Data/S_LevelStyle` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/LevelButton` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/LevelVisuals` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Materials/M_Grid` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Meshes/SM_Cube` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

