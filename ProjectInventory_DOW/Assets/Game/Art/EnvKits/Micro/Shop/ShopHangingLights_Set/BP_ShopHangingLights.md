# BP_ShopHangingLights

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Art/EnvKits/Micro/Shop/ShopHangingLights_Set/BP_ShopHangingLights.BP_ShopHangingLights` |
| Asset name | `BP_ShopHangingLights` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces (1):
  - `/Game/Standards/iDamagable.iDamagable_C`

## Variables (3)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Detach Health` | `real<double>` | `20.000000` | `Default` | — | — | InstanceEditable |
| `Health` | `real<double>` | `100.000000` | `Default` | — | — | InstanceEditable |
| `Detach When Shot` | `bool` | `True` | `Default` | — | — | InstanceEditable |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`
  - `SM_Lantern` — `StaticMeshComponent` @ socket `None`
    - `BPC_Damageable_Lantern` — `BPC_Damageable_C` @ socket `None`
    - `Wind_Physics_Force_Lantern` — `Wind_Physics_Force_C` @ socket `None`
  - `SM_Tag` — `StaticMeshComponent` @ socket `None`
    - `PC_Tag` — `PhysicsConstraintComponent` @ socket `None`
    - `Wind_Physics_Force_Tag` — `Wind_Physics_Force_C` @ socket `None`
  - `BPC_Damagable_DelayActorDeath` — `BPC_Damageable_C` @ socket `None`

## Class Default Object (1)

- `PrimaryActorTick` (`FActorTickFunction`) = `(bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (28 nodes)
- Construction script: `UserConstructionScript` (4 nodes)
- Additional graphs: _none_

## References

Hard refs out (9):
- `/Engine/EditorResources/S_KBSJoint` [asset]
- `/Engine/EditorResources/S_KHinge` [asset]
- `/Engine/EditorResources/S_KPrismatic` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Wind_Physics_Force` [asset]
- `/Game/Art/EnvKits/Micro/Shop/ShopHangingLights_Set/SM_Lantern_A_01` [asset]
- `/Game/Art/EnvKits/Micro/Shop/ShopHangingLights_Set/SM_Lantern_A_Tag_01` [asset]
- `/Game/Blueprints/Dynamics/Components/BPC_Damageable` [asset]
- `/Game/Standards/iDamagable` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

