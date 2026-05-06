# AC_SmartObjectAnimation

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/AC_SmartObjectAnimation.AC_SmartObjectAnimation` |
| Asset name | `AC_SmartObjectAnimation` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ActorComponent` (`/Script/Engine.ActorComponent`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (10)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Owner Skeletal Mesh` | `object<SkeletalMeshComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Incoming Animation Payload` | `struct<SmartObjectAnimationPayload>` | `(Playrate_13_FBFEE455436381981547FBA0406371DC=1.000000,WarpTargetTransform_17_A6656D8446DF7313C287309408AD4BFE=(Rotation=(X=0.000000,Y=-0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000)))` | `Default` | — | — | InstanceEditable, Private |
| `Number Of Loops` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `Warp Target Name` | `name` | `SmartObject` | `Default` | — | — | InstanceEditable, Private |
| `Owner Montage Finished` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Ignore Character Movement Server Corrections` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Character Movement Component` | `object<CharacterMovementComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Smart Object Selection Inputs` | `struct<SmartObjectSelectionInputs>` | `(PoseHistoryNode_9_2F1F46A246A738A457FA419A05F81F8D=())` | `Default` | — | — | InstanceEditable, Private |
| `Smart Object Selection Outputs` | `struct<SmartObjectSelectionOutputs>` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Mover Component` | `object<MoverComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |

## Functions (8)

### `Cache Necessary Data`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14

### `Evaluate Distance and Motion Match`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Transform>& Destination [ref], object<ProxyTable> ProxyTable)`
- Outputs: `(object<AnimMontage> Result, real<double> Cost, real<double> StartTime)`
- Local variables (1): `Anim Instance`
- Nodes: 14

### `Is Mover`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Result, bool Result)`
- Local variables: _none_
- Nodes: 5

### `NPC Approach Angle and Distance`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Transform>& Destination [ref])`
- Outputs: `(real<double> Distance, real<double> Angle)`
- Local variables: _none_
- Nodes: 13

### `Set Ignore Character Movement Correction`

- Access: `Public`
- Flags: —
- Inputs: `(bool Ignore Corrections)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7

### `Set Ignore Collision State`

- Access: `Public`
- Flags: —
- Inputs: `(bool bShouldIgnore, object<Actor> Other Actor)`
- Outputs: `()`
- Local variables (1): `Capsules`
- Nodes: 9

### `Setup Play Timer`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13

### `Try Add Warp Target`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

## Macros (1)

### `Evaluation Montage Loop And Exit`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 16

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `bReplicates` (`uint8`) = `True`

## Graphs

- Event graph: `EventGraph` (46 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (16):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_ABP` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/CHPA_SmartObject` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/SmartObjectAnimationPayload` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/SmartObjectSelectionInputs` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/SmartObjectSelectionOutputs` [asset]
- `/Script/AnimGraph` [asset]
- `/Script/AnimGraphRuntime` [asset]
- `/Script/Chooser` [asset]
- `/Script/Engine.ActorComponent` [native]
- `/Script/MotionWarping` [asset]
- `/Script/Mover` [asset]
- `/Script/MoverEditor` [asset]
- `/Script/PoseSearch` [asset]
- `/Script/ProxyTable` [asset]
- `/Script/ProxyTableUncooked` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

