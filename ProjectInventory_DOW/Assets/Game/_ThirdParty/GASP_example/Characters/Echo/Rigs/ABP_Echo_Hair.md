# ABP_Echo_Hair

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Characters/Echo/Rigs/ABP_Echo_Hair.ABP_Echo_Hair` |
| Asset name | `ABP_Echo_Hair` |
| Subclass | `AnimBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `AnimInstance` (`/Script/Engine.AnimInstance`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (2)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `WindExternalForce` | `struct<Vector>` | `(X=20000.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `bIsWindy` | `bool` | `False` | `Default` | — | — | InstanceEditable |

## Functions (1)

### `AnimGraph`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `bUsingCopyPoseFromMesh` (`uint8`) = `True`

## Graphs

- Event graph: `EventGraph` (17 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## State Machines

_No authored state machines (single-graph anim blueprint)._

## References

Hard refs out (6):
- `/Game/_ThirdParty/GASP_example/Characters/Echo/Meshes/SK_Echo` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/Echo/Meshes/SKM_Echo_Hair` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/Echo/Rigs/Physics/PA_Echo_Ponytail` [asset]
- `/Script/AnimGraph` [asset]
- `/Script/AnimGraphRuntime` [asset]
- `/Script/Engine.AnimInstance` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `AnimBlueprint`
- Custom metadata: _none_

