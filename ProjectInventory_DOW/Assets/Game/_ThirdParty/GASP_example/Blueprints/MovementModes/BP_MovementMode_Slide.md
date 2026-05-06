# BP_MovementMode_Slide

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/MovementModes/BP_MovementMode_Slide.BP_MovementMode_Slide` |
| Asset name | `BP_MovementMode_Slide` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `SmoothWalkingMode` (`/Script/Mover.SmoothWalkingMode`, native, module `/Script/Mover`)
- Interfaces: _none_

## Variables (12)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `InitialBoost` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `InitialBoostTime` | `real<double>` | `0.200000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `InitialBoostSpeed` | `real<double>` | `800.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `InitialBoostAcceleration` | `real<double>` | `2000.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `AfterBoostAcceleration` | `real<double>` | `300.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `SteepSlopeAngle` | `real<double>` | `40.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `ShallowSlopeAngle` | `real<double>` | `10.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `SteepSlopeSpeed` | `real<double>` | `800.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `ShallowSlopeSpeed` | `real<double>` | `500.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `FlatGroundSpeed` | `real<double>` | `100.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `SteepSlopeDeceleration` | `real<double>` | `2000.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `FlatGroundDeceleration` | `real<double>` | `500.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |

## Functions (1)

### `GenerateWalkMove`

- Access: `Public`
- Flags: —
- Inputs: `(struct<MoverTickStartData>& StartState [ref], real<float> DeltaSeconds = 0.0, struct<Vector>& DesiredVelocity = 0, 0, 0 [ref], struct<Quat>& DesiredFacing [ref], struct<Quat>& CurrentFacing [ref], struct<Vector>& InOutAngularVelocityDegrees = 0, 0, 0 [ref], struct<Vector>& InOutVelocity = 0, 0, 0 [ref])`
- Outputs: `()`
- Local variables (6): `SlopeAngle`, `CurrentOffset`, `InputCollection`, `MoverDefaultInputs`, `MoverCustomInputs`, `OverridenDesiredFacing`
- Nodes: 78

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (9)

- `Acceleration` (`float`) = `2000.000000`
- `AccelerationSmoothingTime` (`float`) = `0.000000`
- `bSmoothFacingWithDoubleSpring` (`bool`) = `False`
- `Deceleration` (`float`) = `200.000000`
- `DecelerationSmoothingTime` (`float`) = `0.000000`
- `FacingSmoothingTime` (`float`) = `0.150000`
- `SharedSettingsClasses` (`TArray`) = `("/Script/CoreUObject.Class'/Script/Mover.CommonLegacyMovementSettings'","/Script/CoreUObject.Class'/Script/Mover.Sta...`
- `Transitions` (`TArray`) [instanced] = `("/Game/_ThirdParty/GASP_example/Blueprints/MovementModes/BP_MovementTransition_FromSlide.BP_MovementTransition_FromS...`
- `TurningStrength` (`float`) = `1.000000`

## Graphs

- Event graph: `EventGraph` (5 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (5):
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_MoverCustomInputs` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/MovementModes/BP_MovementTransition_FromSlide` [asset]
- `/Script/Mover` [asset]
- `/Script/Mover.SmoothWalkingMode` [native]
- `/Script/PhysicsCore` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

