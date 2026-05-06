# BP_Mission

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Developers/andersjansson/Mission/BP_Mission.BP_Mission` |
| Asset name | `BP_Mission` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (16)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Targets` | `TArray<object<BP_Target_C>>` | — | `Default` | — | — | InstanceEditable, Private |
| `Exits` | `TArray<object<BP_Exit_C>>` | — | `Default` | — | — | InstanceEditable, Private |
| `CurrentTarget` | `object<BP_Target_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `RandomStream` | `struct<RandomStream>` | `()` | `Default` | — | — | InstanceEditable |
| `SelectedEntryPoint` | `object<BP_Exit_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `e_SetEnterable` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Widget` | `object<WBP_WP_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `SelectedExitPoint` | `object<BP_Exit_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Active` | `bool` | `True` | `Default` | — | — | InstanceEditable |
| `EnterableApartmentDoor` | `object<BP_Door_C>` | `None` | `Default` | — | — | InstanceEditable |
| `WaypointLocation` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `Doors` | `TArray<object<BP_Door_C>>` | — | `Default` | — | — | InstanceEditable, Private |
| `Countdown` | `object<WBP_Countdown_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Time Remaining` | `int` | `120` | `Default` | — | — | InstanceEditable, Private |
| `DiveLevel` | `object<LevelStreamingDynamic>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `EnterDiveTransform` | `struct<Transform>` | `(Rotation=(X=0.000000,Y=0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000))` | `Default` | — | — | InstanceEditable, Private |

## Functions (5)

### `GetClosestExitPoints`

- Access: `Public`
- Flags: —
- Inputs: `(int Max = 2)`
- Outputs: `(object<BP_Exit_C> SelectedEntryPoint)`
- Local variables (3): `Distances`, `Closest`, `LocalExitMap`
- Nodes: 21

### `RandomizeTarget`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13

### `SelectRoomAndDoorType`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(object<BP_Door_C> Door)`
- Local variables (1): `SelectedDoor`
- Nodes: 15

### `StartMission`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 22

### `UpdateTimer`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`

## Class Default Object (1)

- `PrimaryActorTick` (`FActorTickFunction`) = `(bCanEverTick=True)`

## Graphs

- Event graph: `EventGraph` (113 nodes)
- Construction script: `UserConstructionScript` (1 nodes)
- Additional graphs: _none_

## References

Hard refs out (12):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Developers/andersjansson/Mission/BP_Door` [asset]
- `/Game/Developers/andersjansson/Mission/BP_Door_Child` [asset]
- `/Game/Developers/andersjansson/Mission/BP_Exit` [asset]
- `/Game/Developers/andersjansson/Mission/BP_MissionObjective` [asset]
- `/Game/Developers/andersjansson/Mission/BP_Target` [asset]
- `/Game/Developers/andersjansson/Mission/WBP_Countdown` [asset]
- `/Game/Developers/andersjansson/Mission/WBP_WP` [asset]
- `/Game/Prototype/UI/WBP_Dive_Enter_Prototype` [asset]
- `/Script/Engine.Actor` [native]
- `/Script/UMG` [asset]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

