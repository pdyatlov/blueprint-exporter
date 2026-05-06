# CR_Mech

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Locomotor/Mech/Rigs/CR_Mech.CR_Mech` |
| Asset name | `CR_Mech` |
| Subclass | `ControlRigBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ControlRig` (`/Script/ControlRig.ControlRig`, native, module `/Script/ControlRig`)
- Interfaces: _none_

## Variables (12)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `isRotating` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `FindClosestBone_Value` | `struct<RigElementKey>` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Space` | `byte<ERigVMTransformSpace>` | `GlobalSpace` | `Default` | — | — | InstanceEditable, Private |
| `turret_aim_null` | `struct<RigElementKey>` | `(Type=Bone)` | `Default` | — | — | InstanceEditable, Private |
| `Root_Ctrl` | `struct<RigElementKey>` | `()` | `Default` | — | — | InstanceEditable, Private |
| `base_ctrl` | `struct<RigElementKey>` | `()` | `Default` | — | — | InstanceEditable, Private |
| `turret_ctrl` | `struct<RigElementKey>` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Divide_Result` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `ArrayGetNum_Num` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `closestBones_bones` | `TArray<struct<RigElementKey>>` | — | `Default` | — | — | InstanceEditable, Private |
| `closestBones_controls` | `TArray<struct<RigElementKey>>` | — | `Default` | — | — | InstanceEditable, Private |
| `Is Right Side_Right Side` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |

## Functions (24)

### `Add Null Above`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9

### `Control Stack at Item`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

### `Control Stack at Position`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 45

### `Create FK Rig`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

### `Create IKThreeBone Controls`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12

### `Create Jiggle Rig`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 18

### `Create Leg Rig`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 99

### `Create Piston Rig`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 33

### `Create Root`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9

### `Create Turret Rig`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 23

### `delay`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4

### `FindClosestControl`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 23

### `Flip Control Axis`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12

### `FWD FK Rig`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 16

### `FWD Jiggle Rig`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 17

### `FWD Leg Rig`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 67

### `FWD Piston Rig`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 22

### `FWD Root`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4

### `FWD Turret Rig`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13

### `Get Metadata from Items`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4

### `Is Right Side`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 27

### `Map Controls to Bones`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 26

### `Name Search in Array`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9

### `Print Array`

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

## Class Default Object (3)

- `DynamicHierarchy` (`TObjectPtr<URigHierarchy>`) = `/Script/ControlRig.RigHierarchy'/Game/_ThirdParty/GASP_example/Locomotor/Mech/Rigs/CR_Mech.Default__CR_Mech_C:Dynamic...`
- `HierarchySettings` (`FRigHierarchySettings`) = `(ProceduralElementLimit=1000)`
- `ShapeLibraries` (`TArray`) = `("/ControlRig/Controls/DefaultGizmoLibraryNormalized.DefaultGizmoLibraryNormalized")`

## Graphs

- Event graph: `EventGraph` (52 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (12):
- `/ControlRig/Controls/DefaultGizmoLibraryNormalized` [asset]
- `/ControlRig/StandardFunctionLibrary/StandardFunctionLibrary` [asset]
- `/Game/_ThirdParty/GASP_example/Locomotor/Mech/Meshes/SK_Mech` [asset]
- `/Game/_ThirdParty/GASP_example/Locomotor/Mech/Meshes/SKM_Mech` [asset]
- `/Script/AnimationCore` [asset]
- `/Script/ControlRig` [asset]
- `/Script/ControlRig.ControlRig` [native]
- `/Script/ControlRigDeveloper` [asset]
- `/Script/CoreUObject` [asset]
- `/Script/Engine` [asset]
- `/Script/RigVM` [asset]
- `/Script/RigVMDeveloper` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `ControlRigBlueprint`
- Custom metadata: _none_

