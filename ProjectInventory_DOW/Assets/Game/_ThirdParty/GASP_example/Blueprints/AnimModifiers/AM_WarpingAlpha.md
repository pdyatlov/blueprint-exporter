# AM_WarpingAlpha

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/AnimModifiers/AM_WarpingAlpha.AM_WarpingAlpha` |
| Asset name | `AM_WarpingAlpha` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `AnimationModifier` (`/Script/AnimationModifiers.AnimationModifier`, native, module `/Script/AnimationModifiers`)
- Interfaces: _none_

## Variables (20)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `SamplesPerSecond` | `int` | `30` | `Default` | — | — | InstanceEditable |
| `TimePerSample` | `real<double>` | `1.000000` | `Default` | — | — | InstanceEditable, Private |
| `SampleTime` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `TargetAnim` | `object<AnimSequenceBase>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `SampleIndex` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `LastBoneTransform` | `struct<Transform>` | `(Rotation=(X=0.000000,Y=0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000))` | `Default` | — | — | InstanceEditable, Private |
| `BoneTransform` | `struct<Transform>` | `(Rotation=(X=0.000000,Y=0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000))` | `Default` | — | — | InstanceEditable, Private |
| `CurveName` | `name` | `Enable_Warping` | `Default` | — | — | InstanceEditable |
| `bDeleteCurveOnRevert` | `bool` | `True` | `Default` | — | — | InstanceEditable |
| `bGoingStraight` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `bLastGoingStraight` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `BlendInTime` | `real<double>` | `0.250000` | `Default` | — | — | InstanceEditable |
| `BlendOutTime` | `real<double>` | `0.250000` | `Default` | — | — | InstanceEditable |
| `RootMotionTranslationAngle` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `LastRootMotionTranslationAngle` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `RotationAngleThreshold` | `real<float>` | `5.000000` | `Default` | — | — | InstanceEditable |
| `TranslationAngleThreshold` | `real<double>` | `5.000000` | `Default` | — | — | InstanceEditable |
| `bInvert` | `bool` | `False` | `Default` | — | — | InstanceEditable |
| `RotationError` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `TranslationError` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |

## Functions (3)

### `Get Current Sample Time`

- Access: `Private`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Output Sample Time)`
- Local variables: _none_
- Nodes: 8

### `Init Iteration Params`

- Access: `Private`
- Flags: —
- Inputs: `(object<AnimSequenceBase> InTargetAnim)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11

### `SetCurveKey`

- Access: `Public`
- Flags: CallInEditor
- Inputs: `(name Name, real<float> Time, real<float> Value)`
- Outputs: `()`
- Local variables (1): `Curve`
- Nodes: 8

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `RevisionGuid` (`FGuid`) = `1ED1C5AB4DFCE5D399D22D90DDF32628`

## Graphs

- Event graph: `EventGraph` (130 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (4):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Script/AnimationBlueprintLibrary` [asset]
- `/Script/AnimationModifiers` [asset]
- `/Script/AnimationModifiers.AnimationModifier` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

