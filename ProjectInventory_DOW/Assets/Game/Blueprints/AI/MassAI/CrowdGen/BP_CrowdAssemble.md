# BP_CrowdAssemble

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/AI/MassAI/CrowdGen/BP_CrowdAssemble.BP_CrowdAssemble` |
| Asset name | `BP_CrowdAssemble` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `SkeletalMeshActor` (`/Script/Engine.SkeletalMeshActor`, native, module `/Script/Engine`)
- Interfaces (1):
  - `/Game/_ThirdParty/CitySampleCrowd/Blueprints/BPI_CrowdCharacter.BPI_CrowdCharacter_C`

## Variables (13)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Skeleton` | `byte<CrowdSkeleton>` | `NewEnumerator0` | `CharacterOptions` | — | — | InstanceEditable |
| `Body Shape` | `byte<CrowdBodyType>` | `NewEnumerator0` | `CharacterOptions` | — | — | InstanceEditable |
| `HeadIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `SkinTextureIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `SkinTextureModifierIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `OutfitIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `OutfitMaterialIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `PatternOptionIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `PatternColorIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `AccessoryIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `ScaleFactorIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `CrowdDataAsset` | `object<DA_BP_CrowdCharacter_C>` | `/Game/Blueprints/AI/MassAI/CrowdGen/DataAssets/DataAssetsAssemble/DA_BP_CrowdCharacter.DA_BP_CrowdCharacter_C'/Game/Blueprints/AI/MassAI/CrowdGen/DataAssets/DataAssetsAssemble/DA_CrowdAssemble.DA_CrowdAssemble'` | `Default` | — | — | InstanceEditable, Private |
| `RandomOptions` | `bool` | `True` | `CharacterOptions` | — | — | InstanceEditable |

## Functions (23)

### `AttachAccessory`

- Access: `Public`
- Flags: —
- Inputs: `(struct<S_CrowdAccessoryDefinition>& AccessoryDefinition [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 19
- Category: `SetupComponents`

### `CreateDynamicMaterialInstance`

- Access: `Public`
- Flags: —
- Inputs: `(object<MeshComponent> MeshComponent, name MaterialSlotName)`
- Outputs: `(object<MaterialInstanceDynamic> MaterialInstance, object<MaterialInstanceDynamic> MaterialInstance)`
- Local variables (1): `ElementIndex`
- Nodes: 11
- Category: `Default`

### `CreateSkeletalMeshDynamicMaterialInstance`

- Access: `Public`
- Flags: —
- Inputs: `(object<SkeletalMeshComponent> SkeletalMeshComponent, name MaterialSlotName)`
- Outputs: `(object<MaterialInstanceDynamic> MaterialInstance, object<MaterialInstanceDynamic> MaterialInstance)`
- Local variables (1): `L_ElementIndex`
- Nodes: 21

### `CreateStaticMeshDynamicMaterialInstance`

- Access: `Public`
- Flags: —
- Inputs: `(object<StaticMeshComponent> StaticMeshComponent, name MaterialSlotName)`
- Outputs: `(object<MaterialInstanceDynamic> ReturnValue)`
- Local variables: _none_
- Nodes: 9

### `GetBodyOutfitDefinition`

- Access: `Public`
- Flags: —
- Inputs: `(struct<S_CrowdSkeletonDefinition>& GenderDefinition [ref], byte BodyType = NewEnumerator0)`
- Outputs: `(struct<S_CrowdBodyOutfitDefinition> BodyOutfitDefinition, struct<S_CrowdBodyOutfitDefinition> BodyOutfitDefinition, struct<S_CrowdBodyOutfitDefinition> BodyOutfitDefinition)`
- Local variables: _none_
- Nodes: 6
- Category: `Character Definition`

### `GetBodyOutiftDefinitionData`

- Access: `Public`
- Flags: —
- Inputs: `(struct<S_CrowdBodyOutfitDefinition>& CrowdBodyOutfitDefinition [ref], int HeadIndex, int OutiftIndex, int AccessoryIndex, int ScaleFactorIndex)`
- Outputs: `(struct<S_CrowdBodyDefinition> BodyDefinition, struct<S_CrowdOutfitDefinition> OutfitDefinition, softobject<SkeletalMesh> Head, struct<S_CrowdAccessoryDefinition> AccessoryDefinition, real<float> ScaleFactor)`
- Local variables: _none_
- Nodes: 7
- Category: `Character Definition`

### `GetBodyType`

- Interface override of `/Game/_ThirdParty/CitySampleCrowd/Blueprints/BPI_CrowdCharacter.BPI_CrowdCharacter_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte BodyType)`
- Local variables: _none_
- Nodes: 3

### `GetCharacterDefinition`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<S_CrowdCharacterDefinition> CharacterDefinition)`
- Local variables: _none_
- Nodes: 22
- Category: `CharacterDefinition`

### `GetOutfitMaterialDefinition`

- Access: `Public`
- Flags: —
- Inputs: `(struct<S_CrowdSkeletonDefinition>& GenderDefinition [ref], int OutfitMaterialIndex)`
- Outputs: `(struct<S_CrowdOutfitMaterialDefinition> OutfitMaterialDefinition)`
- Local variables: _none_
- Nodes: 4
- Category: `Character Definition`

### `GetPatternInfoForSlot`

- Access: `Public`
- Flags: —
- Inputs: `(TMap<name, ?> MaterialOverrides, name SlotName, int PatternColorIndex, int PatternSelectionIndex)`
- Outputs: `(struct<Color> PatternColor, struct<S_CrowdPatternInfo> PatternInfo, bool bFound, struct<Color> PatternColor, struct<S_CrowdPatternInfo> PatternInfo, bool bFound)`
- Local variables (5): `L_DrivenScaleMultiplier`, `L_MaterialOverride`, `L_Condition`, `L_PatternColor`, `L_PatternInfo`
- Nodes: 54
- Category: `SetupComponents`

### `GetSkeletonDefinition`

- Access: `Public`
- Flags: —
- Inputs: `(object<DA_BP_CrowdCharacter_C> DataAsset, byte Skeleton = NewEnumerator0)`
- Outputs: `(struct<S_CrowdSkeletonDefinition> SkeletonDefinition, struct<S_CrowdSkeletonDefinition> SkeletonDefinition)`
- Local variables: _none_
- Nodes: 6
- Category: `Character Definition`

### `GetSkinTextureDefinition`

- Access: `Public`
- Flags: —
- Inputs: `(struct<S_CrowdSkeletonDefinition>& GenderDefinition [ref], int SkinTextureIndex, int SkinTextureModifierIndex)`
- Outputs: `(struct<S_CrowdSkinTextureModifierDefinition> SkinTextureModifierDefinition, struct<S_CrowdSkinTextureDefinition> SkinTextureDefinition)`
- Local variables: _none_
- Nodes: 6
- Category: `Character Definition`

### `SetBodyMaterials`

- Access: `Public`
- Flags: —
- Inputs: `(struct<S_CrowdSkinTextureDefinition> SkinTextureDefinition, struct<S_CrowdSkinTextureModifierDefinition> SkinTextureModifierDefinition)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 28
- Category: `SetupComponents`

### `SetCharacterDefinition`

- Access: `Public`
- Flags: —
- Inputs: `(struct<S_CrowdCharacterDefinition> CharacterDefinition)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 17
- Category: `SetupComponents`

### `SetFaceMaterial`

- Access: `Public`
- Flags: —
- Inputs: `(object<MaterialInstanceDynamic> MaterialInstance, struct<S_CrowdSkinTextureDefinition>& SkinTextureDefinition [ref], struct<S_CrowdSkinTextureModifierDefinition>& SkinTextureModifierDefinition [ref])`
- Outputs: `()`
- Local variables (1): `L_MaterialInstance`
- Nodes: 25
- Category: `SetupComponents`

### `SetFaceMaterials`

- Access: `Public`
- Flags: —
- Inputs: `(struct<S_CrowdSkinTextureDefinition> SkinTextureDefinition, struct<S_CrowdSkinTextureModifierDefinition> SkinTextureModifierDefinition)`
- Outputs: `()`
- Local variables (1): `MaterialInstance`
- Nodes: 10
- Category: `SetupComponents`

### `SetOutfitMaterial`

- Access: `Public`
- Flags: —
- Inputs: `(object<MeshComponent> MeshComponent, int PatternColorIndex, int PatternOptionIndex, TMap<name, ?> MaterialOverrides)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 32
- Category: `SetupComponents`

### `SetOutfitMaterials`

- Access: `Public`
- Flags: —
- Inputs: `(int PatternColorIndex, int PatternOptionIndex, struct<S_CrowdOutfitMaterialDefinition>& OutfitMaterialDefinition [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 18
- Category: `SetupComponents`

### `SetOutfitParameterOverrides`

- Access: `Public`
- Flags: —
- Inputs: `(TArray<struct<S_CrowdMaterialColorOverride>> ParameterOverrides, object<MaterialInstanceDynamic> MaterialInstance)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `SetupComponents`

### `SetRandomOptions`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 48
- Category: `CharacterOptions`

### `SetSkeletalMesh`

- Access: `Public`
- Flags: —
- Inputs: `(object<SkeletalMeshComponent> SkeletalMeshComponent, softobject<SkeletalMesh> SkeletalMesh)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6
- Category: `Default`

### `SetSkeletalMeshes`

- Access: `Public`
- Flags: —
- Inputs: `(softobject<SkeletalMesh> Base, softobject<SkeletalMesh> Body, softobject<SkeletalMesh> Head, softobject<SkeletalMesh> Top, softobject<SkeletalMesh> Bottom, softobject<SkeletalMesh> Shoes)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13
- Category: `SetupComponents`

### `SetUpdateAnimationInEditor`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Default`

## Macros (2)

### `GetSafeCopy`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11

### `ReinterpretAsLinear`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12

## Components (7)

- `LODSync` — `LODSyncComponent` @ socket `None`
- `Body` — `SkeletalMeshComponent` @ socket `None`
- `Accessory` — `StaticMeshComponent` @ socket `None`
- `Top` — `SkeletalMeshComponent` @ socket `None`
- `Bottom` — `SkeletalMeshComponent` @ socket `None`
- `Shoes` — `SkeletalMeshComponent` @ socket `None`
- `Face` — `SkeletalMeshComponent` @ socket `None`

## Class Default Object (3)

- `ActorLabel` (`FString`) = `BP_Male_Med-1`
- `RootComponent` (`TObjectPtr<USceneComponent>`) [instanced] = `/Script/Engine.SkeletalMeshComponent'/Game/Blueprints/AI/MassAI/CrowdGen/BP_CrowdAssemble.Default__BP_CrowdAssemble_C...`
- `SkeletalMeshComponent` (`TObjectPtr<USkeletalMeshComponent>`) [instanced] = `/Script/Engine.SkeletalMeshComponent'/Game/Blueprints/AI/MassAI/CrowdGen/BP_CrowdAssemble.Default__BP_CrowdAssemble_C...`

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `UserConstructionScript` (20 nodes)
- Additional graphs: _none_

## References

Hard refs out (30):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Blueprints/BPI_CrowdCharacter` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Male/NormalWeight/Meshes/m_tal_nrw_base` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Enums/CrowdBodyType` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Enums/CrowdPatternUsage` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Enums/CrowdSkeleton` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Rig/ABP_CrowdCharacter_Head` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdAccessoryDefinition` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdMaterialOverride` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdOutfitMaterialDefinition` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdPatternInfo` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdSkinTextureDefinition` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdSkinTextureModifierDefinition` [asset]
- `/Game/Blueprints/AI/MassAI/CrowdGen/BP_CrowdMassAI_Original` [asset]
- `/Game/Blueprints/AI/MassAI/CrowdGen/DataAssets/DataAssetsAssemble/DA_BP_CrowdCharacter` [asset]
- `/Game/Blueprints/AI/MassAI/CrowdGen/DataAssets/DataAssetsAssemble/DA_CrowdAssemble` [asset]
- `/Game/Blueprints/AI/MassAI/CrowdGen/Definitions/S_CrowdAccessoryDefinition` [asset]
- `/Game/Blueprints/AI/MassAI/CrowdGen/Definitions/S_CrowdBodyDefinition` [asset]
- `/Game/Blueprints/AI/MassAI/CrowdGen/Definitions/S_CrowdBodyOutfitDefinition` [asset]
- `/Game/Blueprints/AI/MassAI/CrowdGen/Definitions/S_CrowdCharacterDefinition` [asset]
- `/Game/Blueprints/AI/MassAI/CrowdGen/Definitions/S_CrowdMaterialColorOverride` [asset]
- `/Game/Blueprints/AI/MassAI/CrowdGen/Definitions/S_CrowdMaterialOverride` [asset]
- `/Game/Blueprints/AI/MassAI/CrowdGen/Definitions/S_CrowdOutfitDefinition` [asset]
- `/Game/Blueprints/AI/MassAI/CrowdGen/Definitions/S_CrowdOutfitMaterialDefinition` [asset]
- `/Game/Blueprints/AI/MassAI/CrowdGen/Definitions/S_CrowdPatternInfo` [asset]
- `/Game/Blueprints/AI/MassAI/CrowdGen/Definitions/S_CrowdSkeletonDefinition` [asset]
- `/Game/Blueprints/AI/MassAI/CrowdGen/Definitions/S_CrowdSkinMaterialDefinition` [asset]
- `/Game/Blueprints/AI/MassAI/CrowdGen/Definitions/S_CrowdSkinTextureDefinition` [asset]
- `/Game/Blueprints/AI/MassAI/CrowdGen/Definitions/S_CrowdSkinTextureModifierDefinition` [asset]
- `/Script/Engine.SkeletalMeshActor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

