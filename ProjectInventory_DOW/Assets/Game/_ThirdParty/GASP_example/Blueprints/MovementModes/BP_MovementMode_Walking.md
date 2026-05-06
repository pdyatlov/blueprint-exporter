# BP_MovementMode_Walking

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/MovementModes/BP_MovementMode_Walking.BP_MovementMode_Walking` |
| Asset name | `BP_MovementMode_Walking` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `SmoothWalkingMode` (`/Script/Mover.SmoothWalkingMode`, native, module `/Script/Mover`)
- Interfaces: _none_

## Variables (15)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `WalkSpeed` | `real<float>` | `165.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `WalkAcceleration` | `real<float>` | `500.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `RunSpeed` | `real<float>` | `375.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `RunAcceleration` | `real<float>` | `800.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `SprintSpeed` | `real<float>` | `585.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `SprintAcceleration` | `real<float>` | `300.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `CrouchSpeed` | `real<float>` | `200.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `Walk/RunTurnStrength` | `real<double>` | `8.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `SprintTurnStrength` | `real<double>` | `4.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `GaitChangeDeceleration` | `real<float>` | `300.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `StoppingDeceleration` | `real<float>` | `1000.000000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `Walk/RunFacingTime` | `real<double>` | `0.400000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `SprintFacingTime` | `real<double>` | `0.800000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `IdleFacingTime` | `real<double>` | `0.200000` | `Blueprint Overrides (Change These)` | — | — | InstanceEditable, Private |
| `JustLanded` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |

## Functions (1)

### `GenerateWalkMove`

- Access: `Public`
- Flags: —
- Inputs: `(struct<MoverTickStartData>& StartState [ref], real<float> DeltaSeconds = 0.0, struct<Vector>& DesiredVelocity = 0, 0, 0 [ref], struct<Quat>& DesiredFacing [ref], struct<Quat>& CurrentFacing [ref], struct<Vector>& InOutAngularVelocityDegrees = 0, 0, 0 [ref], struct<Vector>& InOutVelocity = 0, 0, 0 [ref])`
- Outputs: `()`
- Local variables (5): `InputCollection`, `MoverDefaultInputs`, `MoverCustomInputs`, `OverridenDesiredFacing`, `CurrentOffset`
- Nodes: 125

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (6)

- `Acceleration` (`float`) = `1000.000000`
- `bSmoothFacingWithDoubleSpring` (`bool`) = `False`
- `FacingSmoothingTime` (`float`) = `0.500000`
- `SharedSettingsClasses` (`TArray`) = `("/Script/CoreUObject.Class'/Script/Mover.CommonLegacyMovementSettings'","/Script/CoreUObject.Class'/Script/Mover.Sta...`
- `Transitions` (`TArray`) [instanced] = `("/Game/_ThirdParty/GASP_example/Blueprints/MovementModes/BP_MovementTransition_ToSlide.BP_MovementTransition_ToSlide...`
- `TurningStrength` (`float`) = `8.000000`

## Graphs

- Event graph: `EventGraph` (8 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (5):
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_Gait` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_MoverCustomInputs` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/MovementModes/BP_MovementTransition_ToSlide` [asset]
- `/Script/Mover` [asset]
- `/Script/Mover.SmoothWalkingMode` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

