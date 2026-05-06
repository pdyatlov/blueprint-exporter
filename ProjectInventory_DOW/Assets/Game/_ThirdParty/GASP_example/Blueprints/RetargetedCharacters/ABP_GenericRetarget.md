# ABP_GenericRetarget

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/RetargetedCharacters/ABP_GenericRetarget.ABP_GenericRetarget` |
| Asset name | `ABP_GenericRetarget` |
| Subclass | `AnimBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `AnimInstance` (`/Script/Engine.AnimInstance`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (3)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `IKRetargeter` | `object<IKRetargeter>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `IKRetargeter_Map` | `TMap<name<IKRetargeter>>, :/Script/IKRig.IKRetargeter>` | `(("RTG_UEFN_to_UE4_Mannequin", "/Script/IKRig.IKRetargeter'/Game/_ThirdParty/GASP_example/Characters/UE4_Mannequin/Rigs/RTG_UEFN_to_UE4_Mannequin.RTG_UEFN_to_UE4_Mannequin'"),("RTG_UEFN_to_UE5_Mannequin", "/Script/IKRig.IKRetargeter'/Game/_ThirdParty/GASP_example/Characters/UE5_Mannequins/Rigs/RTG_UEFN_to_UE5_Mannequin.RTG_UEFN_to_UE5_Mannequin'"),("RTG_UEFN_to_Echo", "/Script/IKRig.IKRetargeter'/Game/_ThirdParty/GASP_example/Characters/Echo/Rigs/RTG_UEFN_to_Echo.RTG_UEFN_to_Echo'"),("RTG_UEFN_to_TwinBlast", "/Script/IKRig.IKRetargeter'/Game/_ThirdParty/GASP_example/Characters/Paragon/Heroes/TwinBlast/Rigs/RTG_UEFN_to_TwinBlast.RTG_UEFN_to_TwinBlast'"),("RTG_UEFN_to_Metahuman_nrw", "/Script/IKRig.IKRetargeter'/Game/_ThirdParty/GASP_example/MetaHumans/Common/Common/Rigs/RTG_UEFN_to_Metahuman_nrw.RTG_UEFN_to_Metahuman_nrw'"),("RTG_UEFN_to_Metahuman_ovw", "/Script/IKRig.IKRetargeter'/Game/_ThirdParty/GASP_example/MetaHumans/Common/Common/Rigs/RTG_UEFN_to_Metahuman_ovw.RTG_UEFN_to_Metahuman_ovw'"))` | `Default` | — | — | InstanceEditable, Private |
| `RetargetProfile` | `struct<RetargetProfile>` | `(RootSettings=(RotationAlpha=1.000000,TranslationAlpha=1.000000,BlendToSourceWeights=(X=1.000000,Y=1.000000,Z=1.000000),ScaleHorizontal=1.000000,ScaleVertical=1.000000,TranslationOffset=(X=0.000000,Y=0.000000,Z=0.000000),RotationOffset=(Pitch=0.000000,Yaw=0.000000,Roll=0.000000),AffectIKHorizontal=1.000000),GlobalSettings=(bEnableRoot=True,bEnableFK=True,bEnableIK=True,bEnablePost=True,SourceScaleFactor=1.000000,ForwardDirection=Y,WarpForwards=1.000000,WarpSplay=1.000000))` | `Default` | — | — | InstanceEditable, Private |

## Functions (2)

### `AnimGraph`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

### `UpdateRetargetProfile`

- Access: `Public`
- Flags: —
- Inputs: `(struct<RetargetProfile>& Input Profile [ref])`
- Outputs: `(struct<RetargetProfile> ReturnValue)`
- Local variables (3): `ChainsToSet`, `IKChainsController`, `ChainCurveMap`
- Nodes: 26
- Category: `Default`

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `bUsingCopyPoseFromMesh` (`uint8`) = `True`

## Graphs

- Event graph: `EventGraph` (13 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## State Machines

_No authored state machines (single-graph anim blueprint)._

## References

Hard refs out (11):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/Echo/Rigs/RTG_UEFN_to_Echo` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/Paragon/Heroes/TwinBlast/Rigs/RTG_UEFN_to_TwinBlast` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UE4_Mannequin/Rigs/RTG_UEFN_to_UE4_Mannequin` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UE5_Mannequins/Rigs/RTG_UEFN_to_UE5_Mannequin` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Common/Rigs/RTG_UEFN_to_Metahuman_nrw` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Common/Rigs/RTG_UEFN_to_Metahuman_ovw` [asset]
- `/Script/AnimGraph` [asset]
- `/Script/Engine.AnimInstance` [native]
- `/Script/IKRig` [asset]
- `/Script/IKRigDeveloper` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `AnimBlueprint`
- Custom metadata: _none_

