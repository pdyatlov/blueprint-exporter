# MetaHuman_ControlRig

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Art/Characters/MetaHumans/Common/Common/MetaHuman_ControlRig.MetaHuman_ControlRig` |
| Asset name | `MetaHuman_ControlRig` |
| Subclass | `ControlRigBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ControlRig` (`/Script/ControlRig.ControlRig`, native, module `/Script/ControlRig`)
- Interfaces: _none_

## Variables (11)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `L Arm IK Mode` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `R Arm IK Mode` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `L Leg IK Mode ` | `bool` | `True` | `Default` | — | — | InstanceEditable, Private |
| `R Leg IK Mode` | `bool` | `True` | `Default` | — | — | InstanceEditable, Private |
| `Spine IK Mode` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Neck IK Mode` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Spine Offsets` | `TArray<struct<Transform>>` | — | `Default` | — | — | InstanceEditable, Private |
| `Spine Length` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Neck Length` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `L Arm IK Align` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `R Arm IK Align` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |

## Functions (40)

### `Backward Arm`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 41

### `Backward Clavicle`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

### `Backward Fingers`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7

### `Backward Foot`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 19

### `Backward Leg`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 26

### `Backward Neck`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 30

### `Backward SNC`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

### `Backward Spine`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 19

### `BSpline IK`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 86

### `BSpline Passing thru 4 Points`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 49

### `Compute Pole Vector Parent`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7

### `Find Finger Controls`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 19

### `FK Point At`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 33

### `Forward Arm`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 108

### `Forward Clavicle`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

### `Forward Fingers`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 30

### `Forward Foot`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 68

### `Forward Leg`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 51

### `Forward Neck`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 69

### `Forward Reverse Foot`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 87

### `Forward SNC`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 103

### `Forward Spine`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 66

### `Get Negative Transform`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

### `IK 2 Bones`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 53

### `Interpolate Interacting Controls`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 53

### `Match 2 Bones IK onto FK`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14

### `Project to New Parents`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

### `Set IKFK Keys`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 20

### `Set IKFK Visibility`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 19

### `Set Neck IK-FK and SNC Visibility`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 54

### `Setup Arm`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 67

### `Setup Clavicle`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9

### `Setup Fingers`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 18

### `Setup Foot`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 35

### `Setup Leg`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 61

### `Setup Neck`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 37

### `Setup Reverse Foot`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 46

### `Setup SNC`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 69

### `Setup Spine`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 46

### `Spine Match IK onto FK`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 22

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (3)

- `DynamicHierarchy` (`TObjectPtr<URigHierarchy>`) = `/Script/ControlRig.RigHierarchy'/Game/Art/Characters/MetaHumans/Common/Common/MetaHuman_ControlRig.Default__MetaHuman...`
- `Influences` (`FRigInfluenceMapPerEvent`) = `(Maps=((EventName="Forwards Solve")),EventToIndex=(("Forwards Solve", 0)))`
- `ShapeLibraries` (`TArray`) = `("/ControlRig/Controls/DefaultGizmoLibraryNormalized.DefaultGizmoLibraryNormalized")`

## Graphs

- Event graph: `EventGraph` (301 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (9):
- `/ControlRig/Controls/DefaultGizmoLibraryNormalized` [asset]
- `/Script/AnimationCore` [asset]
- `/Script/ControlRig` [asset]
- `/Script/ControlRig.ControlRig` [native]
- `/Script/ControlRigDeveloper` [asset]
- `/Script/ControlRigSpline` [asset]
- `/Script/CoreUObject` [asset]
- `/Script/RigVM` [asset]
- `/Script/RigVMDeveloper` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `ControlRigBlueprint`
- Custom metadata: _none_

