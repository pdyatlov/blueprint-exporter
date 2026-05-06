# BP_Robo_01

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Prototype/Protein/BP_Robo_01.BP_Robo_01` |
| Asset name | `BP_Robo_01` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (14)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `01RandomRotation` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `02RandomRotation` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `03RandomRotation` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `04RandomRotation` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `Move01` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Move02` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Move03` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Move04` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `01Rotation` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `02Rotation` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `03Rotation` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `04Rotation` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `PlayAnimation` | `bool` | `True` | `Default` | — | — | InstanceEditable |
| `Relative Rotation` | `TArray<struct<Rotator>>` | — | `Default` | — | — | InstanceEditable, Private |

## Functions (1)

### `RotateFuckers`

- Access: `Public`
- Flags: —
- Inputs: `(object<StaticMeshComponent> Component, struct<Rotator>& StoredRot [ref], real<double> Alpha, bool Animate, struct<Rotator> RandomRot)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12

## Macros (0)

_None._

## Components (1)

- `Scene` — `SceneComponent` @ socket `None`
  - `SM_Robo_Base` — `StaticMeshComponent` @ socket `None`
    - `SM_Robo_01` — `StaticMeshComponent` @ socket `None`
      - `SM_Robo_02` — `StaticMeshComponent` @ socket `None`
        - `SM_Robo_03` — `StaticMeshComponent` @ socket `None`
          - `SM_Robo_04` — `StaticMeshComponent` @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (70 nodes)
- Construction script: `UserConstructionScript` (12 nodes)
- Additional graphs: _none_

## References

Hard refs out (7):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Prototype/Protein/SM_Robo_01` [asset]
- `/Game/Prototype/Protein/SM_Robo_02` [asset]
- `/Game/Prototype/Protein/SM_Robo_03` [asset]
- `/Game/Prototype/Protein/SM_Robo_04` [asset]
- `/Game/Prototype/Protein/SM_Robo_Base` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

