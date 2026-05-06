# BP_DynamicCover

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Prototype/Mission/BP_DynamicCover.BP_DynamicCover` |
| Asset name | `BP_DynamicCover` |
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
| `AnimationEndLocation` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=200.000000)` | `Default` | — | — | InstanceEditable, Private |
| `AnimationDuration` | `real<double>` | `2.000000` | `Default` | — | — | InstanceEditable, Private |

## Functions (1)

### `SendActivationMessage`

- Access: `Public`
- Flags: —
- Inputs: `(struct<S_ActivationType> ActivationInfo)`
- Outputs: `(struct<S_ActivationType> PassedActivationType)`
- Local variables: _none_
- Nodes: 3

## Macros (0)

_None._

## Components (1)

- `MoveRoot` — `SceneComponent` @ socket `None`
  - `SM_DisplayCase_A_15x20x20_01_Glass` — `StaticMeshComponent` @ socket `None`
  - `SM_DisplayCase_A_15x20x20_01` — `StaticMeshComponent` @ socket `None`
  - `SM_DisplayCase_A_15x20x20_01_Glass1` — `StaticMeshComponent` @ socket `None`
  - `SM_DisplayCase_A_15x20x20_02` — `StaticMeshComponent` @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (19 nodes)
- Construction script: `UserConstructionScript` (7 nodes)
- Additional graphs: _none_

## References

Hard refs out (6):
- `/Game/Prototype/Mission/BlueprintInterface/BPI_MissionScripting` [asset]
- `/Game/Prototype/Mission/Core/BP_MissionScriptable` [asset]
- `/Game/Prototype/Mission/Core/BP_MissionScriptable.BP_MissionScriptable_C` [Blueprint]
- `/Game/Prototype/Mission/Structs/S_ActivationType` [asset]
- `/Game/Prototype/TheBank/DisplayCase/SM_DisplayCase_A_15x20x20_01` [asset]
- `/Game/Prototype/TheBank/DisplayCase/SM_DisplayCase_A_15x20x20_01_Glass` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

