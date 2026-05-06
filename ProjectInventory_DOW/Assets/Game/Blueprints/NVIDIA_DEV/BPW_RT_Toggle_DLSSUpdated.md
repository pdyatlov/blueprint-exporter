# BPW_RT_Toggle_DLSSUpdated

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/NVIDIA_DEV/BPW_RT_Toggle_DLSSUpdated.BPW_RT_Toggle_DLSSUpdated` |
| Asset name | `BPW_RT_Toggle_DLSSUpdated` |
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
| `RTToggled` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `IsRTXEnabled` | `bool` | `True` | `Default` | — | — | InstanceEditable |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (4)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Custom`
- `DesignTimeSize` (`FVector2D`) = `(X=320.000000,Y=48.000000)`

## Graphs

- Event graph: `EventGraph` (22 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `HorizontalBox_36` (`HorizontalBox`)
  - `btn_rtx` (`BPW_Button_C`) [variable] via HorizontalBoxSlot
  - `Overlay_50` (`Overlay`) via HorizontalBoxSlot
    - `brd_green` (`Border`) via OverlaySlot
    - `brd_gray` (`Border`) via OverlaySlot
    - `txt_rtx_stat` (`TextBlock`) [variable] via OverlaySlot

## References

Hard refs out (8):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_Button` [asset]
- `/Script/DLSSBlueprint` [asset]
- `/Script/MovieScene` [asset]
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

