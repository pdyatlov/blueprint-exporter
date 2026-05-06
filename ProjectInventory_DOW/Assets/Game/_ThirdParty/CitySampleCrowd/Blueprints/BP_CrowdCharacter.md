# BP_CrowdCharacter

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/CitySampleCrowd/Blueprints/BP_CrowdCharacter.BP_CrowdCharacter` |
| Asset name | `BP_CrowdCharacter` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `SkeletalMeshActor` (`/Script/Engine.SkeletalMeshActor`, native, module `/Script/Engine`)
- Interfaces (1):
  - `/Game/_ThirdParty/CitySampleCrowd/Blueprints/BPI_CrowdCharacter.BPI_CrowdCharacter_C`

## Variables (18)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Skeleton` | `byte<CrowdSkeleton>` | `NewEnumerator0` | `CharacterOptions` | — | — | InstanceEditable |
| `Body Shape` | `byte<CrowdBodyType>` | `NewEnumerator0` | `CharacterOptions` | — | — | InstanceEditable |
| `HeadIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `SkinTextureIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `SkinTextureModifierIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `HairIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `EyebrowsIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `MustacheIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `BeardIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `HairColorIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `OutfitIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `OutfitMaterialIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `PatternOptionIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `PatternColorIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `AccessoryIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `ScaleFactorIndex` | `int` | `0` | `CharacterOptions` | — | — | InstanceEditable |
| `CrowdDataAsset` | `object<BP_CrowdCharacterDataAsset_C>` | `/Game/_ThirdParty/CitySampleCrowd/Blueprints/BP_CrowdCharacterDataAsset.BP_CrowdCharacterDataAsset_C'/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Data/CrowdCharacterDataAsset.CrowdCharacterDataAsset'` | `Default` | — | — | InstanceEditable, Private |
| `RandomOptions` | `bool` | `False` | `CharacterOptions` | — | — | InstanceEditable |

## Functions (35)

### `AttachAccessory`

- Access: `Public`
- Flags: —
- Inputs: `(struct<CrowdAccessoryDefinition>& AccessoryDefinition [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 18
- Category: `SetupComponents`

### `CreateDynamicMaterialInstance`

- Access: `Public`
- Flags: —
- Inputs: `(object<MeshComponent> MeshComponent, name MaterialSlotName)`
- Outputs: `(object<MaterialInstanceDynamic> MaterialInstance, object<MaterialInstanceDynamic> MaterialInstance, object<MaterialInstanceDynamic> MaterialInstance)`
- Local variables (1): `ElementIndex`
- Nodes: 14
- Category: `Default`

### `CreateGroomAssetDynamicMaterialInstance`

- Access: `Public`
- Flags: —
- Inputs: `(object<GroomComponent> GroomComponent, name MaterialSlotName)`
- Outputs: `(object<MaterialInstanceDynamic> MaterialInstance, object<MaterialInstanceDynamic> MaterialInstance, object<MaterialInstanceDynamic> MaterialInstance)`
- Local variables: _none_
- Nodes: 17

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
- Inputs: `(struct<CrowdSkeletonDefinition>& GenderDefinition [ref], byte BodyType = NewEnumerator0)`
- Outputs: `(struct<CrowdBodyOutfitDefinition> BodyOutfitDefinition, struct<CrowdBodyOutfitDefinition> BodyOutfitDefinition, struct<CrowdBodyOutfitDefinition> BodyOutfitDefinition)`
- Local variables: _none_
- Nodes: 6
- Category: `Character Definition`

### `GetBodyOutiftDefinitionData`

- Access: `Public`
- Flags: —
- Inputs: `(struct<CrowdBodyOutfitDefinition>& CrowdBodyOutfitDefinition [ref], int HeadIndex, int OutiftIndex, int AccessoryIndex, int ScaleFactorIndex)`
- Outputs: `(struct<CrowdBodyDefinition> BodyDefinition, struct<CrowdOutfitDefinition> OutfitDefinition, softobject<SkeletalMesh> Head, struct<CrowdAccessoryDefinition> AccessoryDefinition, real<float> ScaleFactor)`
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
- Outputs: `(struct<CrowdCharacterDefinition> CharacterDefinition)`
- Local variables: _none_
- Nodes: 28
- Category: `CharacterDefinition`

### `GetHairColorDefinition`

- Access: `Public`
- Flags: —
- Inputs: `(object<BP_CrowdCharacterDataAsset_C> DataAsset, int HairColorIndex)`
- Outputs: `(struct<CrowdHairColorDefinition> HairColorDefinition)`
- Local variables: _none_
- Nodes: 4
- Category: `Character Definition`

### `GetHairDefinitions`

- Access: `Public`
- Flags: —
- Inputs: `(struct<CrowdSkeletonDefinition>& GenderDefinition [ref], int HairIndex, int EyebrowsIndex, int MustacheIndex, int BeardIndex)`
- Outputs: `(struct<CrowdHairDefinition> HairDefinition, struct<CrowdHairDefinition> EyebrowsDefinition, struct<CrowdHairDefinition> MustacheDfinition, struct<CrowdHairDefinition> BeardDefinition)`
- Local variables: _none_
- Nodes: 7
- Category: `Character Definition`

### `GetOutfitMaterialDefinition`

- Access: `Public`
- Flags: —
- Inputs: `(struct<CrowdSkeletonDefinition>& GenderDefinition [ref], int OutfitMaterialIndex)`
- Outputs: `(struct<CrowdOutfitMaterialDefinition> OutfitMaterialDefinition)`
- Local variables: _none_
- Nodes: 6
- Category: `Character Definition`

### `GetPatternInfoForSlot`

- Access: `Public`
- Flags: —
- Inputs: `(TMap<name, ?> MaterialOverrides, name SlotName, int PatternColorIndex, int PatternSelectionIndex)`
- Outputs: `(struct<Color> PatternColor, struct<CrowdPatternInfo> PatternInfo, bool bFound, struct<Color> PatternColor, struct<CrowdPatternInfo> PatternInfo, bool bFound)`
- Local variables (5): `L_DrivenScaleMultiplier`, `L_MaterialOverride`, `L_Condition`, `L_PatternColor`, `L_PatternInfo`
- Nodes: 52
- Category: `SetupComponents`

### `GetSkeletonDefinition`

- Access: `Public`
- Flags: —
- Inputs: `(object<BP_CrowdCharacterDataAsset_C> DataAsset, byte Skeleton = NewEnumerator0)`
- Outputs: `(struct<CrowdSkeletonDefinition> SkeletonDefinition, struct<CrowdSkeletonDefinition> SkeletonDefinition)`
- Local variables: _none_
- Nodes: 6
- Category: `Character Definition`

### `GetSkinTextureDefinition`

- Access: `Public`
- Flags: —
- Inputs: `(struct<CrowdSkeletonDefinition>& GenderDefinition [ref], int SkinTextureIndex, int SkinTextureModifierIndex)`
- Outputs: `(struct<CrowdSkinTextureModifierDefinition> SkinTextureModifierDefinition, struct<CrowdSkinTextureDefinition> SkinTextureDefinition)`
- Local variables: _none_
- Nodes: 11
- Category: `Character Definition`

### `SetBakedGroomMap`

- Access: `Public`
- Flags: —
- Inputs: `(object<MaterialInstanceDynamic> MaterialInstance, name AttributeMapName, softobject<GroomAsset> Groom, softobject<Texture2D> BakedGroomMap, int BakedGroomMinimumLOD, int LODIndex)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 23
- Category: `SetupComponents`

### `SetBodyMaterials`

- Access: `Public`
- Flags: —
- Inputs: `(struct<CrowdSkinTextureDefinition> SkinTextureDefinition, struct<CrowdSkinTextureModifierDefinition> SkinTextureModifierDefinition)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 28
- Category: `SetupComponents`

### `SetCharacterDefinition`

- Access: `Public`
- Flags: —
- Inputs: `(struct<CrowdCharacterDefinition> CharacterDefinition)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 26
- Category: `SetupComponents`

### `SetFaceMaterial`

- Access: `Public`
- Flags: —
- Inputs: `(object<MaterialInstanceDynamic> MaterialInstance, struct<CrowdSkinTextureDefinition>& SkinTextureDefinition [ref], struct<CrowdSkinTextureModifierDefinition>& SkinTextureModifierDefinition [ref])`
- Outputs: `()`
- Local variables (1): `L_MaterialInstance`
- Nodes: 23
- Category: `SetupComponents`

### `SetFaceMaterials`

- Access: `Public`
- Flags: —
- Inputs: `(struct<CrowdSkinTextureDefinition> SkinTextureDefinition, struct<CrowdSkinTextureModifierDefinition> SkinTextureModifierDefinition, struct<CrowdHairColorDefinition> HairColorDefinition, struct<CrowdHairDefinition> HairDefinition, struct<CrowdHairDefinition> EyebrowsDefinition, struct<CrowdHairDefinition> MustacheDefinition, struct<CrowdHairDefinition> BeardDefinition)`
- Outputs: `()`
- Local variables (1): `MaterialInstance`
- Nodes: 24
- Category: `SetupComponents`

### `SetFollicleMask`

- Access: `Public`
- Flags: —
- Inputs: `(object<MaterialInstanceDynamic> MaterialInstance, name FollicleMaskName, softobject<Object>& FollicleMask [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 16
- Category: `SetupComponents`

### `SetGroom`

- Access: `Public`
- Flags: —
- Inputs: `(object<GroomComponent> GroomComponent, struct<CrowdHairDefinition>& HairDefinition [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9
- Category: `SetupComponents`

### `SetGroomBinding`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `L_GroomBindings`
- Nodes: 41
- Category: `SetupComponents`

### `SetGrooms`

- Access: `Public`
- Flags: —
- Inputs: `(struct<CrowdHairDefinition>& HairDefinition [ref], struct<CrowdHairDefinition>& MustacheDefinition [ref], struct<CrowdHairDefinition>& BeardDefinition [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10
- Category: `SetupComponents`

### `SetGroomsMaterials`

- Access: `Public`
- Flags: —
- Inputs: `(struct<CrowdHairColorDefinition> HairColorDefiniion)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `SetupComponents`

### `SetHairMaterials`

- Access: `Public`
- Flags: —
- Inputs: `(object<GroomComponent> HairComponent, struct<CrowdHairColorDefinition> HairColorDefiniion, name MelaninParameterName, name RednessParameterName, name RoughnessParameterName)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 19
- Category: `SetupComponents`

### `SetMelaninAndRedless`

- Access: `Public`
- Flags: —
- Inputs: `(object<MaterialInstanceDynamic> MaterialInstance, name MelaninParameterName, name RednessParameterName, struct<CrowdHairColorDefinition>& CrowdHairColorDefinition [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
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
- Inputs: `(int PatternColorIndex, int PatternOptionIndex, struct<CrowdOutfitMaterialDefinition>& OutfitMaterialDefinition [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 17
- Category: `SetupComponents`

### `SetOutfitParameterOverrides`

- Access: `Public`
- Flags: —
- Inputs: `(TArray<struct<CrowdMaterialColorOverride>> ParameterOverrides, object<MaterialInstanceDynamic> MaterialInstance)`
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
- Nodes: 53
- Category: `CharacterOptions`

### `SetScalpMaterial`

- Access: `Public`
- Flags: —
- Inputs: `(object<MaterialInstanceDynamic> MaterialInstance, struct<CrowdHairColorDefinition> HairColorDefinition, struct<CrowdHairDefinition> HairDefinition, name AttributeMapName, name FollicleMaskName, name MelaninParameterName, name RednessParameterName, int LODIndex)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13
- Category: `SetupComponents`

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
  - `Hair` — `GroomComponent` @ socket `None`
  - `Mustache` — `GroomComponent` @ socket `None`
  - `Beard` — `GroomComponent` @ socket `None`

## Class Default Object (3)

- `ActorLabel` (`FString`) = `BP_Male_Med-1`
- `RootComponent` (`TObjectPtr<USceneComponent>`) [instanced] = `/Script/Engine.SkeletalMeshComponent'/Game/_ThirdParty/CitySampleCrowd/Blueprints/BP_CrowdCharacter.Default__BP_Crowd...`
- `SkeletalMeshComponent` (`TObjectPtr<USkeletalMeshComponent>`) [instanced] = `/Script/Engine.SkeletalMeshComponent'/Game/_ThirdParty/CitySampleCrowd/Blueprints/BP_CrowdCharacter.Default__BP_Crowd...`

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `UserConstructionScript` (20 nodes)
- Additional graphs: _none_

## References

Hard refs out (32):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Blueprints/BP_CrowdCharacterDataAsset` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Blueprints/BPI_CrowdCharacter` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Male/NormalWeight/Meshes/m_tal_nrw_base` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Data/CrowdCharacterDataAsset` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Enums/CrowdBodyType` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Enums/CrowdPatternUsage` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Enums/CrowdSkeleton` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Materials/MetaHuman/MI_Facial_Hair` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Materials/MetaHuman/MI_Hair` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Materials/MetaHuman/MI_Hair_Helmet` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Rig/ABP_CrowdCharacter_Head` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdAccessoryDefinition` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdBodyDefinition` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdBodyOutfitDefinition` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdCharacterDefinition` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdHairColorDefinition` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdHairDefinition` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdMaterialColorOverride` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdMaterialOverride` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdOutfitDefinition` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdOutfitMaterialDefinition` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdPatternInfo` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdSkeletonDefinition` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdSkinMaterialDefinition` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdSkinTextureDefinition` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Structs/CrowdSkinTextureModifierDefinition` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Textures/1x1_BakedGroomTextureBase_VT` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Textures/Default/T_DefaultMaskTexture_VT` [asset]
- `/Script/AssetRegistry` [asset]
- `/Script/Engine.SkeletalMeshActor` [native]
- `/Script/HairStrandsCore` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

