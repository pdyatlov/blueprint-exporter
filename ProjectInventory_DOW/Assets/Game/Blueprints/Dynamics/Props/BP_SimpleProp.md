# BP_SimpleProp

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/Dynamics/Props/BP_SimpleProp.BP_SimpleProp` |
| Asset name | `BP_SimpleProp` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces (1):
  - `/Game/Standards/iDamagable.iDamagable_C`

## Variables (8)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Health` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Max Health` | `real<double>` | `100.000000` | `Setup` | — | — | InstanceEditable |
| `Destructible` | `bool` | `False` | `Setup` | — | — | InstanceEditable |
| `Destruction Delay` | `real<double>` | `5.000000` | `Setup` | — | — | InstanceEditable |
| `Destroyed At Time` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `WindPhysicsForce` | `object<Wind_Physics_Force_C>` | `None` | `Setup` | — | — | InstanceEditable |
| `Damaged` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Damage` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (1)

- `SM_StaticMesh` — `StaticMeshComponent` @ socket `None`
  - `BPC_Damageable` — `BPC_Damageable_C` @ socket `None`

## Class Default Object (2)

- `ActorLabel` (`FString`) = `BP_ChairOffice_A`
- `PrimaryActorTick` (`FActorTickFunction`) = `(bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `UserConstructionScript` (10 nodes)
- Additional graphs: _none_

## References

Hard refs out (5):
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Meshes/SM_Cube` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Wind_Physics_Force` [asset]
- `/Game/Blueprints/Dynamics/Components/BPC_Damageable` [asset]
- `/Game/Standards/iDamagable` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

