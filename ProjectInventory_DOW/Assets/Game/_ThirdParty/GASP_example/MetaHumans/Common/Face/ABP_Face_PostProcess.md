# ABP_Face_PostProcess

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Face/ABP_Face_PostProcess.ABP_Face_PostProcess` |
| Asset name | `ABP_Face_PostProcess` |
| Subclass | `AnimBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `AnimInstance` (`/Script/Engine.AnimInstance`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (3)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `RigLogic LOD Threshold` | `int` | `-1` | `Default` | — | — | InstanceEditable |
| `EnableHeadMovementIK` | `bool` | `True` | `Default` | — | — | InstanceEditable |
| `Eable Facial Animation` | `bool` | `True` | `Default` | — | — | InstanceEditable |

## Functions (1)

### `AnimGraph`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 23

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `bUsingCopyPoseFromMesh` (`uint8`) = `True`

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## State Machines

_No authored state machines (single-graph anim blueprint)._

## References

Hard refs out (9):
- `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Face/CR_MetaHuman_HeadMovement_IK_Proc` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Face/Face_Archetype_Skeleton` [asset]
- `/Script/AnimGraph` [asset]
- `/Script/AnimGraphRuntime` [asset]
- `/Script/ControlRig` [asset]
- `/Script/ControlRigDeveloper` [asset]
- `/Script/Engine.AnimInstance` [native]
- `/Script/RigLogicDeveloper` [asset]
- `/Script/RigLogicModule` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `AnimBlueprint`
- Custom metadata: _none_

