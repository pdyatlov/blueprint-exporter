# BP_SimpleLight

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/Dynamics/Props/BP_SimpleLight.BP_SimpleLight` |
| Asset name | `BP_SimpleLight` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces (1):
  - `/Game/Standards/iDamagable.iDamagable_C`

## Variables (2)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Health` | `real<double>` | `10.000000` | `Setup` | — | — | InstanceEditable |
| `Can Be Broken` | `bool` | `True` | `Default` | — | — | InstanceEditable |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`
  - `SM_Light` — `StaticMeshComponent` @ socket `None`
    - `BPC_Damageable` — `BPC_Damageable_C` @ socket `None`

## Class Default Object (2)

- `ActorLabel` (`FString`) = `BP_ChairOffice_A`
- `PrimaryActorTick` (`FActorTickFunction`) = `(bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (5 nodes)
- Construction script: `UserConstructionScript` (4 nodes)
- Additional graphs: _none_

## References

Hard refs out (4):
- `/Game/Art/Discovery/LevelPrototyping/SM_Cube` [asset]
- `/Game/Blueprints/Dynamics/Components/BPC_Damageable` [asset]
- `/Game/Standards/iDamagable` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

