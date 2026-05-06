# LevelVisuals

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/LevelVisuals.LevelVisuals` |
| Asset name | `LevelVisuals` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (3)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `StyleIndex` | `int` | `0` | `Default` | — | — | InstanceEditable |
| `LevelStyles` | `TArray<struct<S_LevelStyle>>` | `((FogColor_3_DA5FC03848B34AFC1BABBCB1640E14A6=(R=0.791667,G=0.750000,B=1.000000,A=1.000000),BlockColors_19_BD7B5F9248A47F4BA4AEE2BCADEEA20F=(("Floor", (GridColor_2_93C9D1544CE9BC2796D83F9E713DAB23=(R=0.300000,G=0.300000,B=0.300000,A=1.000000),GridSizes_16_782DDA9B42440FAB466A829B7C2E5482=(X=100.000000,Y=200.000000,Z=800.000000))),("Blocks", (GridColor_2_93C9D1544CE9BC2796D83F9E713DAB23=(R=0.121569,G=0.121569,B=0.121569,A=1.000000),SurfaceColor_4_9B668B134E34B8A2B41BB98E51273395=(R=0.300000,G=0.300000,B=0.300000,A=1.000000))),("Blocks_Traversable", (GridColor_2_93C9D1544CE9BC2796D83F9E713DAB23=(R=0.300000,G=0.300000,B=0.300000,A=1.000000))))),(FogColor_3_DA5FC03848B34AFC1BABBCB1640E14A6=(R=0.484375,G=0.655383,B=1.000000,A=1.000000),DecalColor_12_1498C751435B031639098A8BF277CF4D=(R=0.000000,G=0.000000,B=0.000000,A=0.500000),BlockColors_19_BD7B5F9248A47F4BA4AEE2BCADEEA20F=(("Floor", (GridColor_2_93C9D1544CE9BC2796D83F9E713DAB23=(R=0.200000,G=0.200000,B=0.200000,A=1.000000),SurfaceColor_4_9B668B134E34B8A2B41BB98E51273395=(R=0.510417,G=0.510417,B=0.510417,A=1.000000),GridSizes_16_782DDA9B42440FAB466A829B7C2E5482=(X=100.000000,Y=200.000000,Z=800.000000))),("Blocks", (GridColor_2_93C9D1544CE9BC2796D83F9E713DAB23=(R=0.200000,G=0.200000,B=0.200000,A=1.000000),SurfaceColor_4_9B668B134E34B8A2B41BB98E51273395=(R=0.510417,G=0.510417,B=0.510417,A=1.000000))),("Blocks_Traversable", (GridColor_2_93C9D1544CE9BC2796D83F9E713DAB23=(R=0.500000,G=0.500000,B=0.500000,A=1.000000),SurfaceColor_4_9B668B134E34B8A2B41BB98E51273395=(R=0.250000,G=0.250000,B=0.250000,A=1.000000))))),(FogColor_3_DA5FC03848B34AFC1BABBCB1640E14A6=(R=0.539931,G=0.447917,B=1.000000,A=1.000000),DecalColor_12_1498C751435B031639098A8BF277CF4D=(R=1.000000,G=0.500000,B=0.000000,A=0.400000),BlockColors_19_BD7B5F9248A47F4BA4AEE2BCADEEA20F=(("Floor", (GridColor_2_93C9D1544CE9BC2796D83F9E713DAB23=(R=0.500000,G=0.500000,B=0.500000,A=1.000000),SurfaceColor_4_9B668B134E34B8A2B41BB98E51273395=(R=0.258463,G=0.236978,B=0.541667,A=1.000000),GridSizes_16_782DDA9B42440FAB466A829B7C2E5482=(X=100.000000,Y=200.000000,Z=800.000000))),("Blocks", (GridColor_2_93C9D1544CE9BC2796D83F9E713DAB23=(R=0.177083,G=0.177083,B=0.177083,A=1.000000),SurfaceColor_4_9B668B134E34B8A2B41BB98E51273395=(R=0.510417,G=0.510417,B=0.510417,A=1.000000))),("Blocks_Traversable", (GridColor_2_93C9D1544CE9BC2796D83F9E713DAB23=(R=0.700000,G=0.700000,B=0.700000,A=1.000000),SurfaceColor_4_9B668B134E34B8A2B41BB98E51273395=(R=0.850000,G=0.264066,B=0.132812,A=1.000000))))))` | `Default` | — | — | InstanceEditable |
| `Landscape` | `object<Landscape>` | `None` | `Default` | — | — | InstanceEditable |

## Functions (2)

### `GetLevelStyle`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<S_LevelStyle> ReturnValue)`
- Local variables: _none_
- Nodes: 7

### `UpdateLevelVisuals`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `NewStyle`
- Nodes: 36

## Macros (0)

_None._

## Components (1)

- `Scene` — `SceneComponent` @ socket `None`
  - `SkyLight` — `SkyLightComponent` @ socket `None`
  - `DirectionalLight` — `DirectionalLightComponent` @ socket `None`
  - `ExponentialHeightFog` — `ExponentialHeightFogComponent` @ socket `None`
  - `PostProcess` — `PostProcessComponent` @ socket `None`
  - `Decal` — `DecalComponent` @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (5 nodes)
- Construction script: `UserConstructionScript` (2 nodes)
- Additional graphs: _none_

## References

Hard refs out (9):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Engine/EditorResources/LightIcons/S_LightError` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Data/S_GridMaterialParams` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Data/S_LevelStyle` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/LevelBlock` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Materials/Decal_ProjectLogo` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Textures/T_sky_01_8k` [asset]
- `/Script/Engine.Actor` [native]
- `/Script/Landscape` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

