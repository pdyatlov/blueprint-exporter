# StillCam

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Widgets/WidgetData/StillCam.StillCam` |
| Asset name | `StillCam` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (4)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `TargetActor` | `object<Actor>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `LookAtTarget` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `FollowTarget` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `LastTargetLocation` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (1)

- `Camera` — `CameraComponent` @ socket `None`

## Class Default Object (1)

- `PrimaryActorTick` (`FActorTickFunction`) = `(bCanEverTick=True)`

## Graphs

- Event graph: `EventGraph` (20 nodes)
- Construction script: `UserConstructionScript` (1 nodes)
- Additional graphs: _none_

## References

Hard refs out (1):
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

