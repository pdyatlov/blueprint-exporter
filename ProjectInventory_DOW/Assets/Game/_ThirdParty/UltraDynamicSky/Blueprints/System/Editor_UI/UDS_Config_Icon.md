# UDS_Config_Icon

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Config_Icon.UDS_Config_Icon` |
| Asset name | `UDS_Config_Icon` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `EditorUtilityWidget` (`/Script/Blutility.EditorUtilityWidget`, native, module `/Script/Blutility`)
- Interfaces: _none_

## Variables (8)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Config` | `object<UDS_SharedConfig_C>` | `None` | `Default` | — | — | InstanceEditable |
| `Config Manager` | `object<Configuration_Manager_C>` | `None` | `Default` | — | — | InstanceEditable |
| `Icon MID` | `object<MaterialInstanceDynamic>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Pan Position` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Hovered` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Time` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Double Click Ready` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Outdated` | `bool` | `False` | `Default` | — | — | InstanceEditable |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (4)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Custom`
- `DesignTimeSize` (`FVector2D`) = `(X=201.000000,Y=201.000000)`
- `PaletteCategory` (`FText`) = `NSLOCTEXT("", "C9EFB5E044ADD0DAEAFF28807C598BDA", "UDS_Tools")`

## Graphs

- Event graph: `EventGraph` (82 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_0` (`CanvasPanel`)
  - `CanvasPanel_50` (`CanvasPanel`) via CanvasPanelSlot
    - `Selection_Highlight` (`Image`) [variable] via CanvasPanelSlot
    - `Border_0` (`Border`) via CanvasPanelSlot
      - `CanvasPanel_1` (`CanvasPanel`) via BorderSlot
        - `Image_41` (`Image`) [variable] via CanvasPanelSlot
        - `VersionNumberText` (`TextBlock`) [variable] via CanvasPanelSlot
    - `NameText` (`TextBlock`) [variable] via CanvasPanelSlot
    - `Button_88` (`Button`) [variable] via CanvasPanelSlot

## References

Hard refs out (9):
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Configuration_Manager` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/config_icon_pan` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_SharedConfig` [asset]
- `/Script/Blutility` [asset]
- `/Script/Blutility.EditorUtilityWidget` [native]
- `/Script/MovieScene` [asset]
- `/Script/SlateCore` [asset]
- `/Script/UMG` [asset]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

