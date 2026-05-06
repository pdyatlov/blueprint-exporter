# CR_Metahuman_FootIK

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/AI/MassAI/Rigs/CR_Metahuman_FootIK.CR_Metahuman_FootIK` |
| Asset name | `CR_Metahuman_FootIK` |
| Subclass | `ControlRigBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ControlRig` (`/Script/ControlRig.ControlRig`, native, module `/Script/ControlRig`)
- Interfaces: _none_

## Variables (6)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `ZOffset_L_Target` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `ZOffset_R_Target` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `ZOffset_L` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `ZOffset_R` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `ZOffset_Pelvis` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `ShouldDoIKTrace` | `bool` | `False` | `Default` | — | — | InstanceEditable |

## Functions (1)

### `FootTrace`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (2)

- `DynamicHierarchy` (`TObjectPtr<URigHierarchy>`) = `/Script/ControlRig.RigHierarchy'/Game/Blueprints/AI/MassAI/Rigs/CR_Metahuman_FootIK.Default__CR_Metahuman_FootIK_C:Dy...`
- `ShapeLibraries` (`TArray`) = `("/ControlRig/Controls/DefaultGizmoLibraryNormalized.DefaultGizmoLibraryNormalized")`

## Graphs

- Event graph: `EventGraph` (41 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (10):
- `/ControlRig/Controls/DefaultGizmoLibraryNormalized` [asset]
- `/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/Body/SKM_World_Npc_Male_Asian_BodyMesh` [asset]
- `/Script/ControlRig` [asset]
- `/Script/ControlRig.ControlRig` [native]
- `/Script/ControlRigDeveloper` [asset]
- `/Script/CoreUObject` [asset]
- `/Script/Engine` [asset]
- `/Script/PBIK` [asset]
- `/Script/RigVM` [asset]
- `/Script/RigVMDeveloper` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `ControlRigBlueprint`
- Custom metadata: _none_

