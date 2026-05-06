# BP_CivilianNPC

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/AI/MassAI/BP_CivilianNPC.BP_CivilianNPC` |
| Asset name | `BP_CivilianNPC` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Character` (`/Script/Engine.Character`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (0)

_None._

## Macros (0)

_None._

## Components (5)

- `MetaHuman` — `MetaHumanComponentUE` @ socket `None`
- `MassAgent` — `MassAgentComponent` @ socket `None`
- `Body` — `SkeletalMeshComponent` @ socket `None`
  - `Face` — `SkeletalMeshComponent` @ socket `None`
    - `Eyebrows` — `GroomComponent` @ socket `None`
    - `Eyelashes` — `GroomComponent` @ socket `None`
    - `Mustache` — `GroomComponent` @ socket `None`
    - `Beard` — `GroomComponent` @ socket `None`
- `AIPerception` — `AIPerceptionComponent` @ socket `None`
- `Clothing` — `SkeletalMeshComponent` @ socket `None`

## Class Default Object (6)

- `ActorLabel` (`FString`) = `BP_CivilianNPC`
- `ArrowComponent` (`TObjectPtr<UArrowComponent>`) [instanced] = `/Script/Engine.ArrowComponent'/Game/Blueprints/AI/MassAI/BP_CivilianNPC.Default__BP_CivilianNPC_C:Arrow'`
- `CapsuleComponent` (`TObjectPtr<UCapsuleComponent>`) [instanced] = `/Script/Engine.CapsuleComponent'/Game/Blueprints/AI/MassAI/BP_CivilianNPC.Default__BP_CivilianNPC_C:CollisionCylinder'`
- `CharacterMovement` (`TObjectPtr<UCharacterMovementComponent>`) [instanced] = `/Script/Engine.CharacterMovementComponent'/Game/Blueprints/AI/MassAI/BP_CivilianNPC.Default__BP_CivilianNPC_C:CharMov...`
- `Mesh` (`TObjectPtr<USkeletalMeshComponent>`) [instanced] = `/Script/Engine.SkeletalMeshComponent'/Game/Blueprints/AI/MassAI/BP_CivilianNPC.Default__BP_CivilianNPC_C:CharacterMesh0'`
- `RootComponent` (`TObjectPtr<USceneComponent>`) [instanced] = `/Script/Engine.CapsuleComponent'/Game/Blueprints/AI/MassAI/BP_CivilianNPC.Default__BP_CivilianNPC_C:CollisionCylinder'`

## Graphs

- Event graph: `EventGraph` (3 nodes)
- Construction script: `UserConstructionScript` (5 nodes)
- Additional graphs: _none_

## References

Hard refs out (28):
- `/Engine/Engine_MI_Shaders/Instances/M_Shader_SimpleTranslucent_Invis` [asset]
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
- `/Game/Art/Characters/MetaHumans/Common/Animation/ABP_Clothing_PostProcess` [asset]
- `/Game/Art/Characters/MetaHumans/Common/Face/ARKit/PA_MetaHuman_ARKit_Mapping` [asset]
- `/Game/Art/Characters/MetaTailorImported/Outfits/Cha_Cv_M_Clothing_01/Cha_Cv_M_Clothing_01` [asset]
- `/Game/Blueprints/AI/MassAI/Anims/ABP_Civilian_1` [asset]
- `/Game/Blueprints/AI/MassAI/DA_NPCconfig` [asset]
- `/Script/AIModule` [asset]
- `/Script/Engine.Character` [native]
- `/Script/HairStrandsCore` [asset]
- `/Script/MassActors` [asset]
- `/Script/MetaHumanSDKRuntime` [asset]
- `/Script/NavigationSystem` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

