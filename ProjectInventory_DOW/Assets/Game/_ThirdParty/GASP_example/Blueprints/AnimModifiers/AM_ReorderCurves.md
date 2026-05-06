# AM_ReorderCurves

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/AnimModifiers/AM_ReorderCurves.AM_ReorderCurves` |
| Asset name | `AM_ReorderCurves` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `AnimationModifier` (`/Script/AnimationModifiers.AnimationModifier`, native, module `/Script/AnimationModifiers`)
- Interfaces: _none_

## Variables (9)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Animation Sequence` | `object<AnimSequence>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `CurvesToOrder` | `TArray<name>` | `("contact_l","contact_r","movedata_speed","enable_warping","Phase","steeringtargettime")` | `Default` | — | — | InstanceEditable |
| `SetColors` | `bool` | `True` | `Default` | — | — | InstanceEditable |
| `Colors` | `TArray<struct<LinearColor>>` | `((R=1.000000,G=0.000000,B=0.029557,A=1.000000),(R=0.000000,G=0.916667,B=1.000000,A=1.000000),(R=0.000000,G=1.000000,B=0.000000,A=1.000000),(R=1.000000,G=1.000000,B=0.000000,A=1.000000),(R=1.000000,G=1.000000,B=1.000000,A=1.000000),(R=1.000000,G=0.124820,B=0.673884,A=1.000000))` | `Default` | — | — | InstanceEditable |
| `Curve Id` | `struct<AnimationCurveIdentifier>` | `(CurveType=(INVALID),Channel=Invalid,Axis=Invalid)` | `Default` | — | — | InstanceEditable, Private |
| `Key` | `struct<RichCurveKey>` | `()` | `Default` | — | — | InstanceEditable, Private |
| `New Curve Id` | `struct<AnimationCurveIdentifier>` | `(CurveType=(INVALID),Channel=Invalid,Axis=Invalid)` | `Default` | — | — | InstanceEditable, Private |
| `CurveName` | `name` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Color` | `struct<LinearColor>` | `(R=0.430792,G=1.000000,B=0.456397,A=0.750000)` | `Default` | — | — | InstanceEditable, Private |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `RevisionGuid` (`FGuid`) = `C52374804FACB86D670AC5ABCCA8EC31`

## Graphs

- Event graph: `EventGraph` (40 nodes)
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

