# BP_Propulsion

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/Dynamics/Shared/BP_Propulsion.BP_Propulsion` |
| Asset name | `BP_Propulsion` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (6)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Debug Draw Arrow` | `bool` | `False` | `Debug` | — | — | InstanceEditable, Private |
| `Thrust` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Debug Arrow Color` | `real<double>` | `-1.000000` | `Debug` | — | — | InstanceEditable, Private |
| `Parent` | `object<StaticMeshComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Debug Arrow Length` | `real<double>` | `-1.000000` | `Debug` | — | — | InstanceEditable, Private |
| `Target Actor` | `object<StaticMeshComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`

## Class Default Object (2)

- `ActorLabel` (`FString`) = `BP_JetForce`
- `PrimaryActorTick` (`FActorTickFunction`) = `(bCanEverTick=True,bStartWithTickEnabled=False,TickInterval=0.010000)`

## Graphs

- Event graph: `EventGraph` (31 nodes)
- Construction script: `UserConstructionScript` (1 nodes)
- Additional graphs: _none_

## References

Hard refs out (2):
- `/Script/DrawDebugLibrary` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

