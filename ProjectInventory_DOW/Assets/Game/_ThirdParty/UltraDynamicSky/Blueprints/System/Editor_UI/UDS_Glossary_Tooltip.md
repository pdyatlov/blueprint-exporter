# UDS_Glossary_Tooltip

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Glossary_Tooltip.UDS_Glossary_Tooltip` |
| Asset name | `UDS_Glossary_Tooltip` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `EditorUtilityWidget` (`/Script/Blutility.EditorUtilityWidget`, native, module `/Script/Blutility`)
- Interfaces: _none_

## Variables (2)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Glossary Entry` | `struct<UDS_Glossary_Entry>` | `()` | `Default` | — | — | InstanceEditable |
| `Color` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=0.000000)` | `Default` | — | — | InstanceEditable |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (4)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Desired`
- `PaletteCategory` (`FText`) = `NSLOCTEXT("", "F7CC6D574178E7BB6295229033B0B953", "UDS_Tools")`

## Graphs

- Event graph: `EventGraph` (26 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_40` (`CanvasPanel`)
  - `BG` (`Image`) [variable] via CanvasPanelSlot
  - `SizeBox_106` (`SizeBox`) via CanvasPanelSlot
    - `VerticalBox_0` (`VerticalBox`) via SizeBoxSlot
      - `HorizontalBox_1` (`HorizontalBox`) via VerticalBoxSlot
        - `DisplayName` (`TextBlock`) [variable] via HorizontalBoxSlot
        - `TextBlock_416` (`TextBlock`) via HorizontalBoxSlot
        - `TypeLabel` (`TextBlock`) [variable] via HorizontalBoxSlot
      - `Spacer_133` (`Spacer`) via VerticalBoxSlot
      - `Image_191` (`Image`) [variable] via VerticalBoxSlot
      - `Spacer_369` (`Spacer`) via VerticalBoxSlot
      - `Tooltip_Text` (`TextBlock`) [variable] via VerticalBoxSlot

## References

Hard refs out (10):
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Readme_Glossary_Type` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Glossary_Entry` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/AmbientSound_TimeWeather` [asset]
- `/Script/Blutility` [asset]
- `/Script/Blutility.EditorUtilityWidget` [native]
- `/Script/MovieScene` [asset]
- `/Script/MovieSceneTracks` [asset]
- `/Script/SlateCore` [asset]
- `/Script/UMG` [asset]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

