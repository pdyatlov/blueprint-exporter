# BP_Screen_Test_PS

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Art/Discovery/PinkStacks/BP_Screen_Test_PS.BP_Screen_Test_PS` |
| Asset name | `BP_Screen_Test_PS` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (5)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Scale` | `real<double>` | `1.000000` | `Default` | — | — | InstanceEditable |
| `Opacity` | `real<double>` | `0.250000` | `Default` | — | — | InstanceEditable |
| `Material` | `object<MaterialInterface>` | `/Script/Engine.MaterialInstanceConstant'/Landmass/Landscape/OldPrototype_BP/Mats/PP/CameraOverlay_Inst.CameraOverlay_Inst'` | `Default` | — | — | InstanceEditable |
| `Note` | `string` | `To change the texture, open the material above and change it there. Currently does not seem possible to modify a post process material on a volume.` | `Default` | — | — | InstanceEditable |
| `Enable` | `bool` | `False` | `Default` | — | — | InstanceEditable |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`
  - `PostProcess` — `PostProcessComponent` @ socket `None`
  - `SM_SeedyStreet_Screen` — `StaticMeshComponent` @ socket `None`

## Class Default Object (1)

- `ActorLabel` (`FString`) = `BP_ScreenOverlay-1`

## Graphs

- Event graph: `EventGraph` (3 nodes)
- Construction script: `UserConstructionScript` (8 nodes)
- Additional graphs: _none_

## References

Hard refs out (4):
- `/Game/Art/Discovery/PinkStacks/SM_SeedyStreet_Screen` [asset]
- `/Landmass/Landscape/OldPrototype_BP/Mats/MPC/MPC_Drawing` [asset]
- `/Landmass/Landscape/OldPrototype_BP/Mats/PP/CameraOverlay_Inst` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

