# CR_Walker

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Locomotor/CR_Walker.CR_Walker` |
| Asset name | `CR_Walker` |
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
| `Physics Solver` | `struct<RigComponentKey>` | `(ElementKey=())` | `Default` | — | — | InstanceEditable, Private |
| `Alpha` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `StartingRotation` | `struct<Quat>` | `(X=0.000000,Y=0.000000,Z=0.000000,W=1.000000)` | `Default` | — | — | InstanceEditable, Private |

## Functions (1)

### `CalculateQuaternionAim`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (2)

- `DynamicHierarchy` (`TObjectPtr<URigHierarchy>`) = `/Script/ControlRig.RigHierarchy'/Game/_ThirdParty/GASP_example/Locomotor/CR_Walker.Default__CR_Walker_C:DynamicHierar...`
- `ShapeLibraries` (`TArray`) = `("/ControlRig/Controls/DefaultGizmoLibraryNormalized.DefaultGizmoLibraryNormalized")`

## Graphs

- Event graph: `EventGraph` (24 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (10):
- `/ControlRig/Controls/DefaultGizmoLibraryNormalized` [asset]
- `/Game/_ThirdParty/GASP_example/Locomotor/Mech/Meshes/SK_Mech` [asset]
- `/Game/_ThirdParty/GASP_example/Locomotor/Mech/Meshes/SKM_Mech` [asset]
- `/Script/ControlRig` [asset]
- `/Script/ControlRig.ControlRig` [native]
- `/Script/ControlRigDeveloper` [asset]
- `/Script/Locomotor` [asset]
- `/Script/PBIK` [asset]
- `/Script/RigVM` [asset]
- `/Script/RigVMDeveloper` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `ControlRigBlueprint`
- Custom metadata: _none_

