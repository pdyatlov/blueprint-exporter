# BPW_DevStats_DLSSSR

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/NVIDIA_DEV/DevStats/BPW_DevStats_DLSSSR.BPW_DevStats_DLSSSR` |
| Asset name | `BPW_DevStats_DLSSSR` |
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
- `DesignTimeSize` (`FVector2D`) = `(X=347.000000,Y=397.000000)`

## Graphs

- Event graph: `EventGraph` (35 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `brd_dlss_dev_stats` (`Border`) [variable]
  - `VerticalBox_113` (`VerticalBox`) via BorderSlot
    - `t_dlss_stats` (`BPWC_Title_C`) via VerticalBoxSlot
    - `t_dlss_mindriver` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `t_dlss_driverdate` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `t_dlss_screenper` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `t_dlss_mode_stats` (`BPWC_Title_C`) via VerticalBoxSlot
    - `t_dlss_fixedscreen` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `t_dlss_modescreenper` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `t_optimal_screenper` (`BPW_Stat_C`) [variable] via VerticalBoxSlot

## References

Hard refs out (7):
- `/Game/Blueprints/NVIDIA_DEV/Core/BPWC_Title` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_Stat` [asset]
- `/Script/DLSSBlueprint` [asset]
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

