# Sky_Modifier_Editor_Row

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/SkyModifier_Tool/Sky_Modifier_Editor_Row.Sky_Modifier_Editor_Row` |
| Asset name | `Sky_Modifier_Editor_Row` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `EditorUtilityWidget` (`/Script/Blutility.EditorUtilityWidget`, native, module `/Script/Blutility`)
- Interfaces: _none_

## Variables (7)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Property is Color` | `bool` | `False` | `Default` | — | — | InstanceEditable |
| `Color Enum` | `byte<UDS_Modifier_Color_Property>` | `NewEnumerator0` | `Default` | — | — | InstanceEditable |
| `Float Enum` | `byte<UDS_Modifier_Float_Property>` | `NewEnumerator0` | `Default` | — | — | InstanceEditable |
| `Color Property` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `Float Property` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Sky Modifier Authoring Tool` | `object<Sky_Modifier_Editor_C>` | `None` | `Default` | — | — | InstanceEditable |
| `Override Active` | `bool` | `False` | `Default` | — | — | InstanceEditable |

## Functions (4)

### `Set Override`

- Access: `Public`
- Flags: —
- Inputs: `(bool Override Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7

### `Set Value`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Float Value, struct<LinearColor> Color Value)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `Set Value to Default`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13

### `Update Modifier Asset`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 22

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (5)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Custom`
- `DesignTimeSize` (`FVector2D`) = `(X=700.000000,Y=100.000000)`
- `PaletteCategory` (`FText`) = `NSLOCTEXT("", "6DD1F9C445A69BF40BB76298E03DF358", "UDS_Tools")`

## Graphs

- Event graph: `EventGraph` (33 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `VerticalBox_0` (`VerticalBox`)
  - `HorizontalBox_29` (`HorizontalBox`) via VerticalBoxSlot
    - `CanvasPanel_160` (`CanvasPanel`) via HorizontalBoxSlot
      - `PropertyName` (`TextBlock`) [variable] via CanvasPanelSlot
    - `HorizontalBox_122` (`HorizontalBox`) via HorizontalBoxSlot
      - `CanvasPanel_0` (`CanvasPanel`) via HorizontalBoxSlot
        - `SinglePropertyView_57` (`SinglePropertyView`) [variable] via CanvasPanelSlot
      - `CheckBox_82` (`CheckBox`) [variable] via HorizontalBoxSlot
  - `Spacer_182` (`Spacer`) via VerticalBoxSlot
  - `Image_98` (`Image`) [variable] via VerticalBoxSlot
  - `Spacer_61` (`Spacer`) via VerticalBoxSlot

## References

Hard refs out (9):
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Modifier_Color_Property` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Modifier_Float_Property` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Modifier` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Tools/Sky_Modifier_Editor` [asset]
- `/Script/Blutility` [asset]
- `/Script/Blutility.EditorUtilityWidget` [native]
- `/Script/ScriptableEditorWidgets` [asset]
- `/Script/UMG` [asset]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

