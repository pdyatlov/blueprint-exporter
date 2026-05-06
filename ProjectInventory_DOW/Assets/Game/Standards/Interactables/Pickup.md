# Pickup

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Standards/Interactables/Pickup.Pickup` |
| Asset name | `Pickup` |
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
| `Direction` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `Velocity` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `In Out Vi` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `Zero` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |

## Functions (1)

### `Spring`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector2D>& Velocity [ref], struct<Vector2D>& Position [ref], real<double> Delta, real<double> Frequency, real<double> Dampening)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 34

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (3 nodes)
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

