# BP_AirlockDoor

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Levels/Protein/LevelInstances/BP_AirlockDoor.BP_AirlockDoor` |
| Asset name | `BP_AirlockDoor` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (3)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `OpenTarget` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `CloseTarget` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `IsOpening` | `bool` | `False` | `Default` | — | — | InstanceEditable |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`
  - `StaticMesh` — `StaticMeshComponent` @ socket `None`
    - `SM_Door_A_DoorRight_01` — `StaticMeshComponent` @ socket `None`
    - `SM_Door_A_DoorLeft_01` — `StaticMeshComponent` @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (25 nodes)
- Construction script: `UserConstructionScript` (1 nodes)
- Additional graphs: _none_

## References

Hard refs out (5):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Prototype/Protein/SM_Door_A_DoorLeft_01` [asset]
- `/Game/Prototype/Protein/SM_Door_A_DoorRight_01` [asset]
- `/Game/Prototype/Protein/SM_Door_A_Frame_01` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

