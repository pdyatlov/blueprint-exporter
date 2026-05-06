# BP_Debris

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/Dynamics/Props/BP_Debris.BP_Debris` |
| Asset name | `BP_Debris` |
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
| `Pieces and Health` | `TMap<object<StaticMesh,>>, real>` | `()` | `Setup` | — | — | InstanceEditable |
| `Removal Delay` | `real<double>` | `15.000000` | `Setup` | — | — | InstanceEditable |
| `Pieces Health` | `real<double>` | `0.000000` | `Setup` | — | — | InstanceEditable |
| `Destructible` | `bool` | `False` | `Setup` | — | — | InstanceEditable |
| `Transform` | `struct<Transform>` | `(Rotation=(X=0.000000,Y=0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000))` | `Setup` | — | — | InstanceEditable |
| `Piece Mesh` | `object<StaticMesh>` | `None` | `Begin Play` | — | — | InstanceEditable, Private |
| `Piece Health` | `real<double>` | `0.000000` | `Begin Play` | — | — | InstanceEditable, Private |
| `Spawned Pieces` | `TArray<object<StaticMeshComponent>>` | — | `Default` | — | — | InstanceEditable, Private |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`

## Class Default Object (1)

- `PrimaryActorTick` (`FActorTickFunction`) = `(bCanEverTick=True,bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (45 nodes)
- Construction script: `UserConstructionScript` (1 nodes)
- Additional graphs: _none_

## References

Hard refs out (5):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Blueprints/Dynamics/Components/BPC_Damageable` [asset]
- `/Game/Blueprints/Dynamics/Props/BP_SimpleProp` [asset]
- `/Game/Standards/iDamagable` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

