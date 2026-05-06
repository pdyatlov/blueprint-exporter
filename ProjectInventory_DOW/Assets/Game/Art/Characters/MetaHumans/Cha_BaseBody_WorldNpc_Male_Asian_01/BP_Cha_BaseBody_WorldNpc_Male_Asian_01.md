# BP_Cha_BaseBody_WorldNpc_Male_Asian_01

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/BP_Cha_BaseBody_WorldNpc_Male_Asian_01.BP_Cha_BaseBody_WorldNpc_Male_Asian_01` |
| Asset name | `BP_Cha_BaseBody_WorldNpc_Male_Asian_01` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Character` (`/Script/Engine.Character`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (1)

### `EnableMasterPose`

- Access: `Private`
- Flags: —
- Inputs: `(object<SkeletalMeshComponent> SkeletalMeshComponent)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15

## Macros (0)

_None._

## Components (4)

- `MetaHuman` — `MetaHumanComponentUE` @ socket `None`
- `LODSync` — `LODSyncComponent` @ socket `None`
- `Body` — `SkeletalMeshComponent` @ socket `None`
  - `Face` — `SkeletalMeshComponent` @ socket `None`
    - `Eyebrows` — `GroomComponent` @ socket `None`
    - `Eyelashes` — `GroomComponent` @ socket `None`
    - `Mustache` — `GroomComponent` @ socket `None`
    - `Beard` — `GroomComponent` @ socket `None`
- `Clothing` — `SkeletalMeshComponent` @ socket `None`

## Class Default Object (6)

- `ActorLabel` (`FString`) = `BP_CharacterName-1`
- `ArrowComponent` (`TObjectPtr<UArrowComponent>`) [instanced] = `/Script/Engine.ArrowComponent'/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/BP_Cha_BaseBody_Wor...`
- `CapsuleComponent` (`TObjectPtr<UCapsuleComponent>`) [instanced] = `/Script/Engine.CapsuleComponent'/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/BP_Cha_BaseBody_W...`
- `CharacterMovement` (`TObjectPtr<UCharacterMovementComponent>`) [instanced] = `/Script/Engine.CharacterMovementComponent'/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/BP_Cha_...`
- `Mesh` (`TObjectPtr<USkeletalMeshComponent>`) [instanced] = `/Script/Engine.SkeletalMeshComponent'/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/BP_Cha_BaseB...`
- `RootComponent` (`TObjectPtr<USceneComponent>`) [instanced] = `/Script/Engine.CapsuleComponent'/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/BP_Cha_BaseBody_W...`

## Graphs

- Event graph: `EventGraph` (3 nodes)
- Construction script: `UserConstructionScript` (14 nodes)
- Additional graphs: _none_

## References

Hard refs out (25):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UE5_Mannequins/Rigs/CR_Mannequin_Body` [asset]
- `/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/Body/SKM_World_Npc_Male_Asian_BodyMesh` [asset]
- `/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/Face/SKM_World_Npc_Male_Asian_FaceMesh` [asset]
- `/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/Grooms/Eyebrows_M_Wide` [asset]
- `/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/Grooms/Eyebrows_M_Wide_Binding` [asset]
- `/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/Grooms/Goatee_S_SoulpatchStrip` [asset]
- `/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/Grooms/Goatee_S_SoulpatchStrip_Binding` [asset]
- `/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/Grooms/MI_WI_Eyebrows_M_Wide_Facial_Hair` [asset]
- `/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/Grooms/MI_WI_Eyebrows_M_Wide_Hair` [asset]
- `/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/Grooms/MI_WI_Goatee_S_SoulpatchStrip_Facial_Hair` [asset]
- `/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/Grooms/MI_WI_Goatee_S_SoulpatchStrip_Hair` [asset]
- `/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/Grooms/MI_WI_Goatee_S_SoulpatchStrip_Hair_Helmet` [asset]
- `/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/Grooms/MI_WI_Mustache_S_Curly_Facial_Hair` [asset]
- `/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/Grooms/MI_WI_Mustache_S_Curly_Hair` [asset]
- `/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/Grooms/MI_WI_Mustache_S_Curly_Hair_Helmet` [asset]
- `/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/Grooms/Mustache_S_Curly` [asset]
- `/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/Grooms/Mustache_S_Curly_Binding` [asset]
- `/Game/Art/Characters/MetaTailorImported/Outfits/Cha_Cv_M_Clothing_01/Cha_Cv_M_Clothing_01` [asset]
- `/Game/Blueprints/AI/MassAI/Anims/ABP_Civilian_1` [asset]
- `/Script/Engine.Character` [native]
- `/Script/HairStrandsCore` [asset]
- `/Script/LiveLinkAnimationCore` [asset]
- `/Script/MetaHumanSDKRuntime` [asset]
- `/Script/NavigationSystem` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

