# Face_PostProcess_AnimBP

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Face/Face_PostProcess_AnimBP.Face_PostProcess_AnimBP` |
| Asset name | `Face_PostProcess_AnimBP` |
| Subclass | `AnimBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `AnimInstance` (`/Script/Engine.AnimInstance`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (6)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Rig Logic LOD Threshold` | `int` | `-1` | `Default` | — | — | InstanceEditable |
| `Enable Neck Correctives` | `bool` | `True` | `Default` | — | — | InstanceEditable |
| `Neck Correctives LOD Threshold` | `int` | `4` | `Default` | — | — | InstanceEditable |
| `Enable Neck Procedural Control Rig` | `bool` | `True` | `Default` | — | — | InstanceEditable |
| `Neck Procedural Control Rig LOD Threshold` | `int` | `4` | `Default` | — | — | InstanceEditable |
| `Neck Corrective Pose Asset` | `object<PoseAsset>` | `None` | `Default` | — | — | InstanceEditable |

## Functions (1)

### `AnimGraph`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 31

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## State Machines

_No authored state machines (single-graph anim blueprint)._

## References

Hard refs out (10):
- `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Face/Face_Archetype_Skeleton` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Face/HeadMovementIK_Proc_CtrlRig` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Face/Neck_CtrlRig` [asset]
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

