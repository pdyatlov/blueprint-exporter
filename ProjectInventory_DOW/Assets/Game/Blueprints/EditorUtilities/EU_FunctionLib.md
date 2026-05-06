# EU_FunctionLib

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/EditorUtilities/EU_FunctionLib.EU_FunctionLib` |
| Asset name | `EU_FunctionLib` |
| Subclass | `Blueprint` |
| Blueprint type | `FunctionLibrary` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `BlueprintFunctionLibrary` (`/Script/Engine.BlueprintFunctionLibrary`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (2)

### `FillUpArtKitArrays`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Struct_ArtKit> ArtKit, string ArtKit_KitPath_2_9EDDF3534D1D4B5A6ECBFA80531C268A, string ArtKit_TexturesPath_4_631595B841F9A12C0D58D6B8FA4708AC, string ArtKit_MaterialsPath_6_86111E364F28123365F5019AC7FB8B4D, TArray<string> ArtKit_MeshPaths_24_4C737EBF4DD854FC9C0D859D4A8D89D5, TArray<string> ArtKit_TexturePaths_25_31C35B7A4AB52D65E33A588753516982, TArray<string> ArtKit_MaterialPaths_26_E261B03E48F1F1C31D3A4C9C3EF6D940, object<Object> __WorldContext)`
- Outputs: `(struct<Struct_ArtKit> FilledArtKit, string FilledArtKit_KitPath_2_9EDDF3534D1D4B5A6ECBFA80531C268A, string FilledArtKit_TexturesPath_4_631595B841F9A12C0D58D6B8FA4708AC, string FilledArtKit_MaterialsPath_6_86111E364F28123365F5019AC7FB8B4D, TArray<string> FilledArtKit_MeshPaths_24_4C737EBF4DD854FC9C0D859D4A8D89D5, TArray<string> FilledArtKit_TexturePaths_25_31C35B7A4AB52D65E33A588753516982, TArray<string> FilledArtKit_MaterialPaths_26_E261B03E48F1F1C31D3A4C9C3EF6D940)`
- Local variables: _none_
- Nodes: 13

### `GetAssetsOfClassFromDir`

- Access: `Public`
- Flags: —
- Inputs: `(string SearchPath, struct<TopLevelAssetPath> ClassPathStruct, object<Object> __WorldContext)`
- Outputs: `(TArray<string>& AssetPaths [ref])`
- Local variables (1): `FoundPaths`
- Nodes: 16

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (5):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Blueprints/EditorUtilities/DataStructs/Struct_ArtKit` [asset]
- `/Game/Blueprints/EditorUtilities/EU_MacroLib` [asset]
- `/Script/AssetRegistry` [asset]
- `/Script/Engine.BlueprintFunctionLibrary` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `FunctionLibrary`
- Subclass: `Blueprint`
- Custom metadata: _none_

