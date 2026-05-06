# UDS_Weather_Preset_Icon

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Preset_Icon.UDS_Weather_Preset_Icon` |
| Asset name | `UDS_Weather_Preset_Icon` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (2)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Weather Settings` | `object<UDS_Weather_Settings_C>` | `None` | `Default` | — | — | InstanceEditable |
| `Size` | `int` | `40` | `Default` | — | — | InstanceEditable |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (5)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Desired`
- `DesignTimeSize` (`FVector2D`) = `(X=100.000000,Y=30.000000)`
- `PaletteCategory` (`FText`) = `NSLOCTEXT("", "FF2C92AB48CA5A4B92C8DB9174BB90E6", "UDS_Tools")`

## Graphs

- Event graph: `EventGraph` (22 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_31` (`CanvasPanel`)
  - `HorizontalBox_144` (`HorizontalBox`) via CanvasPanelSlot
    - `Icon_Image` (`Image`) [variable] via HorizontalBoxSlot
    - `LabelText` (`TextBlock`) [variable] via HorizontalBoxSlot

## References

Hard refs out (7):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Weather_Icon_BG` [asset]
- `/Script/SlateCore` [asset]
- `/Script/UMG` [asset]
- `/Script/UMG.UserWidget` [native]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

