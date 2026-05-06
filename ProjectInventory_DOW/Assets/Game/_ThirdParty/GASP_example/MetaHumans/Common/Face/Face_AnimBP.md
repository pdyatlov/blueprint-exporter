# Face_AnimBP

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Face/Face_AnimBP.Face_AnimBP` |
| Asset name | `Face_AnimBP` |
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
| `LLink_Face_Subj` | `struct<LiveLinkSubjectName>` | `(Name="iPhoneBlack")` | `Default` | — | — | InstanceEditable |
| `ARKit_HeadRotation` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `JawOpenAlpha` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `TeethShowAlpha` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `LLink_Face_Head` | `bool` | `False` | `Default` | — | — | InstanceEditable |
| `CustomControlValues` | `TMap<name, ?>` | `()` | `Default` | — | — | InstanceEditable, Private |

## Functions (4)

### `AnimGraph`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 29

### `GetCustomControls`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(TMap<name, ?> Curves)`
- Local variables: _none_
- Nodes: 3

### `ResetControls`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `Set Control`

- Access: `Public`
- Flags: —
- Inputs: `(name ControlName, real<double> Value)`
- Outputs: `(bool bControlAdded)`
- Local variables (1): `Result`
- Nodes: 19

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `bUsingCopyPoseFromMesh` (`uint8`) = `True`

## Graphs

- Event graph: `EventGraph` (16 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## State Machines

_No authored state machines (single-graph anim blueprint)._

## References

Hard refs out (10):
- `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Common/Mocap/mh_arkit_mapping_pose` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Face/Face_Archetype_Skeleton` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Face/SKM_Face_Preview` [asset]
- `/Script/AnimGraph` [asset]
- `/Script/AnimGraphRuntime` [asset]
- `/Script/Engine.AnimInstance` [native]
- `/Script/LiveLink` [asset]
- `/Script/LiveLinkAnimationCore` [asset]
- `/Script/LiveLinkGraphNode` [asset]
- `/Script/LiveLinkInterface` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `AnimBlueprint`
- Custom metadata: _none_

