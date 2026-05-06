# BPC_JetForce

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/Dynamics/Components/BPC_JetForce.BPC_JetForce` |
| Asset name | `BPC_JetForce` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `SceneComponent` (`/Script/Engine.SceneComponent`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (8)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Debug Draw Arrow` | `bool` | `False` | `Debug` | — | — | InstanceEditable |
| `Debug Arrow Color` | `real<double>` | `-1.000000` | `Debug` | — | — | InstanceEditable |
| `Debug Arrow Length` | `real<double>` | `-1.000000` | `Debug` | — | — | InstanceEditable |
| `Thrust` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Parent` | `object<PrimitiveComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Apply Sway` | `bool` | `True` | `Default` | — | — | InstanceEditable, Private |
| `Rotation` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `Sway Multiplier` | `real<double>` | `0.500000` | `Default` | — | — | InstanceEditable, Private |

## Functions (1)

### `Debug Draw`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector>& Location [ref], struct<Rotator>& Rotation [ref])`
- Outputs: `()`
- Local variables (1): `NewLocalVar`
- Nodes: 19

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `PrimaryComponentTick` (`FActorComponentTickFunction`) = `(bCanEverTick=True)`

## Graphs

- Event graph: `EventGraph` (37 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (2):
- `/Script/DrawDebugLibrary` [asset]
- `/Script/Engine.SceneComponent` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

