# BP_SignParent_01

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Prototype/Art/ShopfrontSigns/BP_SignParent_01.BP_SignParent_01` |
| Asset name | `BP_SignParent_01` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `StaticMeshActor` (`/Script/Engine.StaticMeshActor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (6)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Face` | `bool` | `True` | `Sign` | — | — | InstanceEditable |
| `Interior` | `bool` | `False` | `Sign` | — | — | InstanceEditable |
| `Damageable` | `bool` | `False` | `Sign` | — | — | InstanceEditable, Private |
| `Health` | `real<double>` | `10.000000` | `Default` | — | — | InstanceEditable |
| `Material` | `object<MaterialInterface>` | `None` | `Sign` | — | — | InstanceEditable, Private |
| `FaceMesh` | `object<StaticMesh>` | `None` | `Sign` | — | — | InstanceEditable, Private |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (2)

- `FaceMeshComponent` — `StaticMeshComponent` @ socket `None`
- `InteriorMeshComponent` — `StaticMeshComponent` @ socket `None`

## Class Default Object (3)

- `PrimaryActorTick` (`FActorTickFunction`) = `(bStartWithTickEnabled=False)`
- `RootComponent` (`TObjectPtr<USceneComponent>`) [instanced] = `/Script/Engine.StaticMeshComponent'/Game/Prototype/Art/ShopfrontSigns/BP_SignParent_01.Default__BP_SignParent_01_C:St...`
- `StaticMeshComponent` (`TObjectPtr<UStaticMeshComponent>`) [instanced] = `/Script/Engine.StaticMeshComponent'/Game/Prototype/Art/ShopfrontSigns/BP_SignParent_01.Default__BP_SignParent_01_C:St...`

## Graphs

- Event graph: `EventGraph` (3 nodes)
- Construction script: `UserConstructionScript` (25 nodes)
- Additional graphs: _none_

## References

Hard refs out (1):
- `/Script/Engine.StaticMeshActor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

