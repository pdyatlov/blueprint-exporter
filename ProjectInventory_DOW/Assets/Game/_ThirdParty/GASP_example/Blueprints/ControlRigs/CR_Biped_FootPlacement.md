# CR_Biped_FootPlacement

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/ControlRigs/CR_Biped_FootPlacement.CR_Biped_FootPlacement` |
| Asset name | `CR_Biped_FootPlacement` |
| Subclass | `ControlRigBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ControlRig` (`/Script/ControlRig.ControlRig`, native, module `/Script/ControlRig`)
- Interfaces: _none_

## Variables (47)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `LeftLegLength` | `real<double>` | `0.000000` | `Initialization` | — | — | InstanceEditable, Private |
| `RightLegLength` | `real<double>` | `0.000000` | `Initialization` | — | — | InstanceEditable, Private |
| `Pelvis Height Offset` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Ground Normal` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Graph Inputs` | — | — | InstanceEditable |
| `Roll Limit Degrees` | `real<double>` | `0.000000` | `Config` | — | — | InstanceEditable |
| `DebugDraw` | `bool` | `True` | `Config` | — | — | InstanceEditable |
| `DoRaycast` | `bool` | `False` | `Config` | — | — | InstanceEditable |
| `LeftFootPinned` | `bool` | `False` | `Pinning` | — | — | InstanceEditable, Private |
| `LeftPinWeight` | `real<double>` | `0.000000` | `Pinning` | — | — | InstanceEditable, Private |
| `LeftFootPinTransformWorldSpace` | `struct<Transform>` | `(Rotation=(X=-0.286778,Y=-0.743633,Z=0.264320,W=0.543050),Translation=(X=19.050000,Y=35.789999,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000))` | `Pinning` | — | — | InstanceEditable, Private |
| `RightFootPinned` | `bool` | `False` | `Pinning` | — | — | InstanceEditable, Private |
| `RightPinWeight` | `real<double>` | `0.000000` | `Pinning` | — | — | InstanceEditable, Private |
| `RightFootPinTransformWorldSpace` | `struct<Transform>` | `(Rotation=(X=0.000000,Y=0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000))` | `Pinning` | — | — | InstanceEditable, Private |
| `LeftFootPinAnimTransformWorldSpace` | `struct<Transform>` | `(Rotation=(X=0.000000,Y=-0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000))` | `Pinning` | — | — | InstanceEditable, Private |
| `RightFootPinAnimTransformWorldSpace` | `struct<Transform>` | `(Rotation=(X=0.000000,Y=-0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000))` | `Pinning` | — | — | InstanceEditable, Private |
| `Enable Foot Pinning` | `bool` | `False` | `Config` | — | — | InstanceEditable |
| `Enable Slope Warping` | `bool` | `True` | `Config` | — | — | InstanceEditable |
| `MaxFootPinRadius` | `real<double>` | `40.000000` | `Config` | — | — | InstanceEditable |
| `ClampFootMinHeightToReferencePose` | `bool` | `False` | `Config` | — | — | InstanceEditable |
| `FootContactLockThreshold` | `real<double>` | `0.970000` | `Config` | — | — | InstanceEditable |
| `PinYawLimitDegrees` | `real<double>` | `20.000000` | `Config` | — | — | InstanceEditable |
| `Pelvis Offset` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `FootToToeAxis_Left` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Initialization` | — | — | InstanceEditable, Private |
| `FootToToeAxis_Right` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Initialization` | — | — | InstanceEditable, Private |
| `AllowHeelLift` | `bool` | `True` | `Config` | — | — | InstanceEditable |
| `Toe Length` | `real<double>` | `5.000000` | `Config` | — | — | InstanceEditable |
| `Hyper Extension Limit Factor` | `real<double>` | `0.980000` | `Config` | — | — | InstanceEditable |
| `Pelvis Smoothing Time` | `real<double>` | `0.200000` | `Config` | — | — | InstanceEditable |
| `PinBlendOutSmoothingTime` | `real<double>` | `0.200000` | `Config` | — | — | InstanceEditable |
| `HeelUpAngleDegrees_Start` | `real<double>` | `15.000000` | `Config` | — | — | InstanceEditable |
| `HeelUpAngleDegrees_End` | `real<double>` | `25.000000` | `Config` | — | — | InstanceEditable |
| `Floor Smoothing Time` | `real<double>` | `0.050000` | `Config` | — | — | InstanceEditable |
| `UseIKBoneTargets` | `bool` | `True` | `Config` | — | — | InstanceEditable |
| `Has Teleported` | `bool` | `False` | `Graph Inputs` | — | — | InstanceEditable |
| `WorldZDamper` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `WorldZDamperVelocity` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `RootDamperSmoothingTime` | `real<double>` | `0.150000` | `Config` | — | — | InstanceEditable |
| `WorldZPrev` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `WorldZDamperAlpha` | `real<double>` | `0.000000` | `Alphas` | — | — | InstanceEditable, Private |
| `WorldZDamperEnabled` | `bool` | `True` | `Config` | — | — | InstanceEditable |
| `LeftSmoothGroundWorldTransform` | `struct<Transform>` | `(Rotation=(X=0.000000,Y=0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000))` | `Default` | — | — | InstanceEditable, Private |
| `RightSmoothGroundWorldTransform` | `struct<Transform>` | `(Rotation=(X=0.000000,Y=0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000))` | `Default` | — | — | InstanceEditable, Private |
| `SlopeWarpingAlpha` | `real<double>` | `0.000000` | `Alphas` | — | — | InstanceEditable, Private |
| `PendingReset` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `ForceReset` | `bool` | `False` | `Config` | — | — | InstanceEditable |
| `Debug Draw Scene Query` | `bool` | `False` | `Config` | — | — | InstanceEditable, Private |
| `Adjust Feet Targets For Collision` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |

## Functions (26)

### `AdjustPositionToPlane`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

### `AlphaLinearInterp`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 19

### `Calculate Limb Length`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7

### `CalculatePinnedToeTargetTransformGlobal`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 32

### `CalculateSlopeAngle`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14

### `CalculateTargetAnimatedToeTransformGlobal`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11

### `CheckEarlyOut`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 28

### `Clamp Pelvis Offset`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 29

### `ClampTransformMinHeightFromReference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4

### `CollidePositionWithPlane`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7

### `ComputePinnedToeTransform`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9

### `DebugDrawExternalIKTargets`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13

### `DebugDrawFootPins`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 34

### `DebugDrawGroundCollision`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14

### `DebugDrawLegs`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 20

### `Do Scene Query`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 60

### `Init Leg`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15

### `Reset`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 25

### `Solve Leg IK`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 95

### `Update Floor Control`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 54

### `Update Foot Pinning`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 111

### `Update Foot Post Solve`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 125

### `Update Leg Controls`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 100

### `Update Pelvis Control`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 40

### `UpdateRootDamper`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 70

### `Wants To Lock`

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

## Class Default Object (2)

- `DynamicHierarchy` (`TObjectPtr<URigHierarchy>`) = `/Script/ControlRig.RigHierarchy'/Game/_ThirdParty/GASP_example/Blueprints/ControlRigs/CR_Biped_FootPlacement.Default_...`
- `ShapeLibraries` (`TArray`) = `("/ControlRig/Controls/DefaultGizmoLibraryNormalized.DefaultGizmoLibraryNormalized")`

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (9):
- `/ControlRig/Controls/DefaultGizmoLibraryNormalized` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Meshes/SKM_UEFN_Mannequin` [asset]
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

