# Neck_CtrlRig

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Face/Neck_CtrlRig.Neck_CtrlRig` |
| Asset name | `Neck_CtrlRig` |
| Subclass | `ControlRigBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ControlRig` (`/Script/ControlRig.ControlRig`, native, module `/Script/ControlRig`)
- Interfaces: _none_

## Variables (3)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `neckCorrMultU` | `real<double>` | `1.000000` | `Default` | — | — | InstanceEditable |
| `neckCorrMultM` | `real<double>` | `1.000000` | `Default` | — | — | InstanceEditable |
| `neckCorrMultD` | `real<double>` | `1.000000` | `Default` | — | — | InstanceEditable |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (3)

- `DynamicHierarchy` (`TObjectPtr<URigHierarchy>`) = `/Script/ControlRig.RigHierarchy'/Game/_ThirdParty/GASP_example/MetaHumans/Common/Face/Neck_CtrlRig.Default__Neck_Ctrl...`
- `Influences` (`FRigInfluenceMapPerEvent`) = `(Maps=((EventName="Forwards Solve")),EventToIndex=(("Forwards Solve", 0)))`
- `ShapeLibraries` (`TArray`) = `("/ControlRig/Controls/DefaultGizmoLibrary.DefaultGizmoLibrary")`

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (7):
- `/ControlRig/Controls/DefaultGizmoLibrary` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Face/SKM_Face_Preview` [asset]
- `/Script/ControlRig` [asset]
- `/Script/ControlRig.ControlRig` [native]
- `/Script/ControlRigDeveloper` [asset]
- `/Script/RigVM` [asset]
- `/Script/RigVMDeveloper` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `ControlRigBlueprint`
- Custom metadata: _none_

