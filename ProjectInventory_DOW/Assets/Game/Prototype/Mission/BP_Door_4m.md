# BP_Door_4m

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Prototype/Mission/BP_Door_4m.BP_Door_4m` |
| Asset name | `BP_Door_4m` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `BP_MissionScriptable_C` (`/Game/Prototype/Mission/Core/BP_MissionScriptable.BP_MissionScriptable_C`, blueprint)
- Interfaces: _none_

## Variables (2)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `DMI` | `object<MaterialInstanceDynamic>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `WeldTimer` | `struct<TimerHandle>` | `()` | `Default` | — | — | InstanceEditable, Private |

## Functions (1)

### `UpdateProgress`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

## Macros (0)

_None._

## Components (6)

- `SM_Cube` — `StaticMeshComponent` @ socket `None`
- `SM_Cube1` — `StaticMeshComponent` @ socket `None`
- `SM_Cube2` — `StaticMeshComponent` @ socket `None`
- `SM_Cube3` — `StaticMeshComponent` @ socket `None`
- `SM_Cube4` — `StaticMeshComponent` @ socket `None`
- `Plane` — `StaticMeshComponent` @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (18 nodes)
- Construction script: `UserConstructionScript` (6 nodes)
- Additional graphs: _none_

## References

Hard refs out (7):
- `/Engine/BasicShapes/Plane` [asset]
- `/Game/Art/Discovery/_Materials/MI_PrototypeGrid_Black` [asset]
- `/Game/Art/Discovery/LevelPrototyping/SM_Cube` [asset]
- `/Game/Prototype/Mission/Assets/M_Temp_DrillGlow` [asset]
- `/Game/Prototype/Mission/BlueprintInterface/BPI_MissionScripting` [asset]
- `/Game/Prototype/Mission/Core/BP_MissionScriptable` [asset]
- `/Game/Prototype/Mission/Core/BP_MissionScriptable.BP_MissionScriptable_C` [Blueprint]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

