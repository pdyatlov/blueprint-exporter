# AM_FootSteps_Modulation

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/AnimModifiers/AM_FootSteps_Modulation.AM_FootSteps_Modulation` |
| Asset name | `AM_FootSteps_Modulation` |
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
| `TargetAnim` | `object<AnimSequence>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `NotifyTracks` | `TArray<name>` | `("Footstep Left","Footstep Right")` | `Default` | — | — | InstanceEditable, Private |
| `CurveNames` | `TMap<name, ?>` | `(("Footstep Left", "FootSpeed_L"),("Footstep Right", "FootSpeed_R"))` | `Default` | — | — | InstanceEditable, Private |
| `SpeedMax` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `SpeedMin` | `real<double>` | `999999999999999.000000` | `Default` | — | — | InstanceEditable, Private |
| `PrevNotifyTime` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `CurrNotifyTime` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `CurrCurveName` | `name` | `None` | `Default` | — | — | InstanceEditable, Private |
| `CurrAnimNotifyEvents` | `TArray<struct<AnimNotifyEvent>>` | — | `Default` | — | — | InstanceEditable, Private |
| `CurrTrackName` | `name` | `None` | `Default` | — | — | InstanceEditable, Private |
| `MinVolume` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable |
| `TotalMaxSpeedDelta` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Usage` | `text` | `NSLOCTEXT("[79557BE104448C2F512D76CD1B338E43]", "DC4120D44D450E31F6B5CF94DE58EEFE", "Needs to have ")` | `Default` | — | — | InstanceEditable, Private |

## Functions (4)

### `GetMaxSpeedDeltaInCurveRange`

- Access: `Public`
- Flags: —
- Inputs: `(name TargetCurveName, real<double> RangeStart, real<double> RangeEnd)`
- Outputs: `(real<double> OutMaxSpeedDelta)`
- Local variables (2): `PrevSpeed`, `MaxSpeedDelta`
- Nodes: 28

### `GetMaxSpeedInCurveRange`

- Access: `Public`
- Flags: —
- Inputs: `(name TargetCurveName, real<double> RangeStart, real<double> RangeEnd)`
- Outputs: `(real<double> OutMax, real<double> OutMin)`
- Local variables (4): `InRangeStart`, `InRangeEnd`, `RunningMax`, `RunningMin`
- Nodes: 31

### `GetModulationValue`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> InValue)`
- Outputs: `(real<double> OutModulation)`
- Local variables (1): `Inverted Normalized Speed`
- Nodes: 6

### `Validation`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool IsValid, bool IsValid, bool IsValid)`
- Local variables: _none_
- Nodes: 19

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `RevisionGuid` (`FGuid`) = `892DD4E4487B38874DC464B707D74E98`

## Graphs

- Event graph: `EventGraph` (80 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (6):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/AnimNotifies/BP_AnimNotify_FoleyEvent` [asset]
- `/Script/AnimationBlueprintLibrary` [asset]
- `/Script/AnimationModifiers` [asset]
- `/Script/AnimationModifiers.AnimationModifier` [native]
- `/Script/EditorScriptingUtilities` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

