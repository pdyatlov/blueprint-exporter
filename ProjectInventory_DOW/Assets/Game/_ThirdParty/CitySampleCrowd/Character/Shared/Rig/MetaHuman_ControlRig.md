# MetaHuman_ControlRig

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Rig/MetaHuman_ControlRig.MetaHuman_ControlRig` |
| Asset name | `MetaHuman_ControlRig` |
| Subclass | `ControlRigBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ControlRig` (`/Script/ControlRig.ControlRig`, native, module `/Script/ControlRig`)
- Interfaces: _none_

## Variables (4)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `arm_l_ik_mode` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `arm_r_ik_mode` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `leg_l_ik_mode` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `leg_r_ik_mode` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (4)

- `AssetUserData` (`TArray`) [instanced] = `("/Game/_ThirdParty/CitySampleCrowd/AssetGuidelines/CitySampleCrowdAssetGuideline_RigLogic.CitySampleCrowdAssetGuidel...`
- `DynamicHierarchy` (`TObjectPtr<URigHierarchy>`) = `/Script/ControlRig.RigHierarchy'/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Rig/MetaHuman_ControlRig.Default__...`
- `Influences` (`FRigInfluenceMapPerEvent`) = `(Maps=((EventName="Forwards Solve")),EventToIndex=(("Forwards Solve", 0)))`
- `ShapeLibraries` (`TArray`) = `("/ControlRig/Controls/DefaultGizmoLibrary.DefaultGizmoLibrary")`

## Graphs

- Event graph: `EventGraph` (557 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (8):
- `/ControlRig/Controls/DefaultGizmoLibrary` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/AssetGuidelines/CitySampleCrowdAssetGuideline_RigLogic` [asset]
- `/Game/MetaHumans/Common/Common/f_med_nrw_preview` [asset]
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

