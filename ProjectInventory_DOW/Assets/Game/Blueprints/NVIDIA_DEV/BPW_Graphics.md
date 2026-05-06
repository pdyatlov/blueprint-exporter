# BPW_Graphics

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/NVIDIA_DEV/BPW_Graphics.BPW_Graphics` |
| Asset name | `BPW_Graphics` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (0)

_None._

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
- `DesignTimeSize` (`FVector2D`) = `(X=308.000000,Y=168.000000)`

## Graphs

- Event graph: `EventGraph` (3 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `brd_graphics` (`Border`) [variable]
  - `vb_graphics` (`VerticalBox`) via BorderSlot
    - `t_graphics_settings` (`BPWC_Title_C`) via VerticalBoxSlot
    - `s_sharpness` (`BPW_Slider_C`) [variable] via VerticalBoxSlot
    - `BPW_RT_Toggle_DLSSUpdated` (`BPW_RT_Toggle_DLSSUpdated_C`) [variable] via VerticalBoxSlot

## References

Hard refs out (7):
- `/Game/Blueprints/NVIDIA_DEV/BPW_RT_Toggle_DLSSUpdated` [asset]
- `/Game/Blueprints/NVIDIA_DEV/Core/BPWC_Title` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_Slider` [asset]
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

