# AM_BakePhaseCurveFromFootstepNotifies

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/AnimModifiers/AM_BakePhaseCurveFromFootstepNotifies.AM_BakePhaseCurveFromFootstepNotifies` |
| Asset name | `AM_BakePhaseCurveFromFootstepNotifies` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `AnimationModifier` (`/Script/AnimationModifiers.AnimationModifier`, native, module `/Script/AnimationModifiers`)
- Interfaces: _none_

## Variables (13)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Animation Sequence` | `object<AnimSequence>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Oscillate` | `bool` | `True` | `Default` | — | — | InstanceEditable |
| `Looping` | `bool` | `False` | `Default` | — | — | InstanceEditable |
| `StartAt0` | `bool` | `False` | `Default` | — | — | InstanceEditable |
| `CurveName` | `name` | `phase` | `Default` | — | — | InstanceEditable |
| `Left Foot Value` | `real<double>` | `1.000000` | `Default` | — | — | InstanceEditable |
| `Right Foot Value` | `real<double>` | `-1.000000` | `Default` | — | — | InstanceEditable |
| `LeftFootTrack` | `name` | `Footstep Left` | `Default` | — | — | InstanceEditable |
| `RightFootTrack` | `name` | `Footstep Right` | `Default` | — | — | InstanceEditable |
| `LeftFootEvents` | `TArray<struct<AnimNotifyEvent>>` | — | `Default` | — | — | InstanceEditable, Private |
| `RightFootEvents` | `TArray<struct<AnimNotifyEvent>>` | — | `Default` | — | — | InstanceEditable, Private |
| `LeftFirst` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `LeftLast` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |

## Functions (2)

### `AddKey`

- Access: `Public`
- Flags: —
- Inputs: `(object<AnimSequenceBase> AnimationSequenceBase, real<float> Time, name CurveName, bool IsLeft)`
- Outputs: `()`
- Local variables (1): `Curve`
- Nodes: 22

### `ClearCurve`

- Access: `Public`
- Flags: —
- Inputs: `(object<AnimSequenceBase> AnimationSequenceBase, name CurveName)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `RevisionGuid` (`FGuid`) = `3951A74048C5C3FE7683BC988982159C`

## Graphs

- Event graph: `EventGraph` (124 nodes)
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

