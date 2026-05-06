# BP_Door

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Developers/andersjansson/Mission/BP_Door.BP_Door` |
| Asset name | `BP_Door` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (11)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `TimelinePreview` | `real<float>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Unlocked` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Overlaps` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `e_DoorUnlocked` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `e_MissionCompleted` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `e_RoomTypes` | `TArray<byte<e_RoomType>>` | `(NewEnumerator0,NewEnumerator1)` | `Default` | — | — | InstanceEditable |
| `PossibleRoomTypes` | `TArray<softobject<World>>` | — | `Default` | — | — | InstanceEditable, Private |
| `RoomSizes` | `TArray<struct<Vector>>` | — | `Default` | — | — | InstanceEditable, Private |
| `ForcePreview` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `SelectedRoomType` | `softobject<World>` | `None` | `Default` | — | — | InstanceEditable |
| `Lab Small` | `softobject<World>` | `/Game/Levels/Protein/LevelInstances/Rooms/LI_SmallOffice_01.LI_SmallOffice_01` | `Default` | — | — | InstanceEditable, Private |

## Functions (4)

### `CloseDoor`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4

### `CycleSizes`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> LargestSize)`
- Local variables (3): `X`, `Y`, `Z`
- Nodes: 26

### `InjectRoom`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

### `OpenDoor`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4

## Macros (0)

_None._

## Components (1)

- `Scene` — `SceneComponent` @ socket `None`
  - `Frame` — `StaticMeshComponent` @ socket `None`
    - `SpotLight` — `SpotLightComponent` @ socket `None`
  - `Door` — `StaticMeshComponent` @ socket `None`
  - `Box` — `BoxComponent` @ socket `None`
  - `SM_Cube` — `StaticMeshComponent` @ socket `None`
  - `SM_Cube1` — `StaticMeshComponent` @ socket `None`
  - `SM_Cube2` — `StaticMeshComponent` @ socket `None`
  - `SM_Cube3` — `StaticMeshComponent` @ socket `None`
  - `SM_Cube4` — `StaticMeshComponent` @ socket `None`
  - `Scene1` — `SceneComponent` @ socket `None`
    - `Cube` — `StaticMeshComponent` @ socket `None`
  - `StaticMesh` — `StaticMeshComponent` @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (27 nodes)
- Construction script: `UserConstructionScript` (27 nodes)
- Additional graphs: _none_

## References

Hard refs out (15):
- `/Engine/BasicShapes/Cube` [asset]
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Engine/EditorResources/LightIcons/S_LightError` [asset]
- `/Game/Art/Discovery/_Materials/MI_PrototypeGrid_Black` [asset]
- `/Game/Art/Discovery/LevelPrototyping/SM_Cube` [asset]
- `/Game/Art/Discovery/Noodles/SM_Door_A_Door_01` [asset]
- `/Game/Art/Discovery/Noodles/SM_Door_A_Frame_01` [asset]
- `/Game/Developers/andersjansson/Mission/e_RoomType` [asset]
- `/Game/Developers/andersjansson/Mission/M_RoomPreview` [asset]
- `/Game/Levels/Noodles/LevelInstances/Apartment_Instance` [asset]
- `/Game/Levels/Noodles/LevelInstances/ApartmentSmall_Instance` [asset]
- `/Game/Levels/Noodles/LevelInstances/BackAlley_Instance` [asset]
- `/Game/Levels/Protein/LevelInstances/Rooms/LI_SmallOffice_01` [asset]
- `/Script/Engine.Actor` [native]
- `/Script/NavigationSystem` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

