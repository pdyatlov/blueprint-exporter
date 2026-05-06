# BP_Straz_Fix

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/BP_Straz_Fix.BP_Straz_Fix` |
| Asset name | `BP_Straz_Fix` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (8)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `ARKitFaceSubj` | `struct<LiveLinkSubjectName>` | `()` | `Live Link` | — | — | InstanceEditable |
| `UseARKitFace` | `bool` | `False` | `Live Link` | — | — | InstanceEditable |
| `UseLiveRetargetMode` | `bool` | `False` | `LiveRetarget` | — | — | InstanceEditable |
| `RetargetOrigBodyAnimMode` | `byte<EAnimationMode>` | `AnimationBlueprint` | `Live Retarget` | — | — | InstanceEditable, Private |
| `RetargetOrigAnimClass` | `class<Class>` | `None` | `Live Retarget` | — | — | InstanceEditable, Private |
| `LiveLinkBodySubj` | `struct<LiveLinkSubjectName>` | `()` | `Live Link` | — | — | InstanceEditable |
| `UseLiveLinkBody` | `bool` | `False` | `Live Link` | — | — | InstanceEditable |
| `LiveLinkBodyRetarget` | `class<Class>` | `None` | `Live Link` | — | — | InstanceEditable, Private |

## Functions (6)

### `ARKitFaceSetup`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11

### `EnableMasterPose`

- Access: `Public`
- Flags: —
- Inputs: `(object<SkeletalMeshComponent> SkeletalMeshComponent)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15

### `HairLODSetup`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 20

### `LiveLinkSetup`

- Access: `Public`
- Flags: —
- Inputs: `(object<SkeletalMeshComponent> SkeletalMesh, struct<LiveLinkSubjectName> SubjectName, class<Class> RetargetAsset, bool UseLiveLink)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13

### `LiveRetargetSetup`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 34

### `SetUpdateAnimationInEditor`

- Access: `Public`
- Flags: —
- Inputs: `(bool IsEnabled)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

## Macros (0)

_None._

## Components (2)

- `Root` — `SceneComponent` @ socket `None`
  - `Body` — `SkeletalMeshComponent` @ socket `None`
    - `Face` — `SkeletalMeshComponent` @ socket `None`
      - `Hair` — `GroomComponent` @ socket `None`
      - `Eyebrows` — `GroomComponent` @ socket `None`
      - `Fuzz` — `GroomComponent` @ socket `None`
      - `Eyelashes` — `GroomComponent` @ socket `None`
      - `Mustache` — `GroomComponent` @ socket `None`
      - `Beard` — `GroomComponent` @ socket `None`
    - `Torso` — `SkeletalMeshComponent` @ socket `None`
    - `Legs` — `SkeletalMeshComponent` @ socket `None`
    - `Feet` — `SkeletalMeshComponent` @ socket `None`
- `LODSync` — `LODSyncComponent` @ socket `None`

## Class Default Object (1)

- `ActorLabel` (`FString`) = `BP_CharacterName-1`

## Graphs

- Event graph: `EventGraph` (27 nodes)
- Construction script: `UserConstructionScript` (21 nodes)
- Additional graphs: _none_

## References

Hard refs out (33):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/RetargetedCharacters/ABP_GenericRetarget` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Common/RTG_metahuman_base_skel_AnimBP` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Face/Face_AnimBP` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Male/Medium/NormalWeight/Bottoms/Cargopants/m_med_nrw_btm_cargopants_High` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Male/Medium/NormalWeight/Shoes/RunningShoes/m_med_nrw_shs_runningshoes_High` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Male/Medium/NormalWeight/Tops/Hoodie/Meshes/m_med_nrw_top_hoodie_nrm_High` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/Body/Materials/MI_BodySynthesized_Simplified` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/Face/Kellan_FaceMesh` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/Male/Medium/NormalWeight/Body/m_med_nrw_body` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/MaleHair/GroomBinding/Eyebrows_M_Full_m_head_Archetype_Binding` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/MaleHair/GroomBinding/Eyelashes_S_Sparse_m_med_nrw_head_skmesh_Face_Archetype_Binding` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/MaleHair/GroomBinding/Hair_S_360Waves_m_med_nrw_head_skmesh_Face_Archetype_Binding` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/MaleHair/GroomBinding/Mustache_S_Stubble_m_head_Archetype_Binding` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/MaleHair/Hair/Eyebrows_M_Full` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/MaleHair/Hair/Eyelashes_S_Sparse` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/MaleHair/Hair/Hair_S_360Waves` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/MaleHair/Hair/Mustache_S_Stubble` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/Materials/MI_Facial_Hair` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/Materials/MI_Hair` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/Materials/MI_Hair1` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/Materials/MI_Hair2` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/Materials/MI_Hair3` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/Materials/MI_Hair_Cards` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/Materials/MI_Hair_Helmet` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/Shared/Materials/MI_Fabric_Feet_Simplified` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/Shared/Materials/MI_Fabric_Legs_Simplified` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/Shared/Materials/MI_Fabric_Torso_Simplified` [asset]
- `/Script/ClothingSystemRuntimeNv` [asset]
- `/Script/Engine.Actor` [native]
- `/Script/HairStrandsCore` [asset]
- `/Script/LiveLinkAnimationCore` [asset]
- `/Script/LiveLinkInterface` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

