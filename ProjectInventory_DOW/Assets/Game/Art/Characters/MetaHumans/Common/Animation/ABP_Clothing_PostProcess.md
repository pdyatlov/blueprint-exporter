# ABP_Clothing_PostProcess

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Art/Characters/MetaHumans/Common/Animation/ABP_Clothing_PostProcess.ABP_Clothing_PostProcess` |
| Asset name | `ABP_Clothing_PostProcess` |
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
| `Enable Rigid Body Simulation` | `bool` | `False` | `Default` | — | — | InstanceEditable |
| `Enable Control Rig` | `bool` | `False` | `Default` | — | — | InstanceEditable |
| `Override Physics Asset` | `object<PhysicsAsset>` | `None` | `Default` | — | — | InstanceEditable |
| `Control Rig Class` | `class<Class>` | `None` | `Default` | — | — | InstanceEditable |
| `Rigid Body LOD Threshold` | `int` | `1` | `Default` | — | — | InstanceEditable |
| `Control Rig LOD Threshold` | `int` | `3` | `Default` | — | — | InstanceEditable |

## Functions (3)

### `AnimGraph`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 20

### `On Control Rig Initial Update`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

### `On Rigid Body Update`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `bUsingCopyPoseFromMesh` (`uint8`) = `True`

## Graphs

- Event graph: `EventGraph` (2 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## State Machines

_No authored state machines (single-graph anim blueprint)._

## References

Hard refs out (7):
- `/Game/Art/Characters/MetaHumans/Common/Animation/CR_PlaceHolder` [asset]
- `/Game/Art/Characters/MetaHumans/Common/Female/Medium/NormalWeight/Body/metahuman_base_skel` [asset]
- `/Script/AnimGraph` [asset]
- `/Script/AnimGraphRuntime` [asset]
- `/Script/ControlRig` [asset]
- `/Script/ControlRigDeveloper` [asset]
- `/Script/Engine.AnimInstance` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `AnimBlueprint`
- Custom metadata: _none_

