# BP_Debug_Lerp

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Developers/erikspellerberg/Blueprints/BP_Debug_Lerp.BP_Debug_Lerp` |
| Asset name | `BP_Debug_Lerp` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (15)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Limited` | `bool` | `True` | `Settings` | — | — | InstanceEditable |
| `Colums` | `int` | `30` | `Settings` | — | — | InstanceEditable |
| `Exp Max` | `real<double>` | `5.000000` | `Settings` | — | — | InstanceEditable |
| `Box Size` | `real<double>` | `10.000000` | `Settings` | — | — | InstanceEditable |
| `Row Index` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `T` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Height` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Color` | `struct<Color>` | `(B=114,G=152,R=255,A=0)` | `Default` | — | — | InstanceEditable, Private |
| `A` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `B` | `real<double>` | `100.000000` | `Default` | — | — | InstanceEditable, Private |
| `Exp Fraction` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Exp` | `real<double>` | `5.000000` | `Default` | — | — | InstanceEditable, Private |
| `Custom Curve` | `object<CurveFloat>` | `/Script/Engine.CurveFloat'/Game/Developers/erikspellerberg/Blueprints/Debug_Curve.Debug_Curve'` | `Default` | — | — | InstanceEditable, Private |
| `Curves To Demo` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `Column Index` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`

## Class Default Object (1)

- `PrimaryActorTick` (`FActorTickFunction`) = `(bCanEverTick=True)`

## Graphs

- Event graph: `EventGraph` (117 nodes)
- Construction script: `UserConstructionScript` (1 nodes)
- Additional graphs: _none_

## References

Hard refs out (4):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Developers/erikspellerberg/Blueprints/Debug_Curve` [asset]
- `/Script/DrawDebugLibrary` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

