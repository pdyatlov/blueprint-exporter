# BP_Exit

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Developers/andersjansson/Mission/BP_Exit.BP_Exit` |
| Asset name | `BP_Exit` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (2)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `ActiveExit` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `e_Exited` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |

## Functions (2)

### `SetActiveEntryPoint`

- Access: `Public`
- Flags: —
- Inputs: `(bool IsActiveEntryPoint)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

### `SetActiveExitPoint`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`
  - `Arrow` — `ArrowComponent` @ socket `None`
  - `Capsule` — `CapsuleComponent` @ socket `None`
  - `Capsule1` — `CapsuleComponent` @ socket `None`
  - `Capsule2` — `CapsuleComponent` @ socket `None`
  - `Capsule3` — `CapsuleComponent` @ socket `None`
  - `ActiveArrow` — `ArrowComponent` @ socket `None`
  - `Sphere` — `SphereComponent` @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (7 nodes)
- Construction script: `UserConstructionScript` (1 nodes)
- Additional graphs: _none_

## References

Hard refs out (2):
- `/Script/Engine.Actor` [native]
- `/Script/NavigationSystem` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

