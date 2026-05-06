# BPW_DevStats_DLSSFG

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/NVIDIA_DEV/DevStats/BPW_DevStats_DLSSFG.BPW_DevStats_DLSSFG` |
| Asset name | `BPW_DevStats_DLSSFG` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (1)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `isStatVisible` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (3)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Custom`
- `DesignTimeSize` (`FVector2D`) = `(X=434.000000,Y=560.000000)`

## Graphs

- Event graph: `EventGraph` (56 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `brd_dlssfg_dev_stats` (`Border`) [variable]
  - `VerticalBox_154` (`VerticalBox`) via BorderSlot
    - `t_dlssfg_stats` (`BPWC_Title_C`) via VerticalBoxSlot
    - `t_dlssfg_mindriver` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `t_dlssfg_driver` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `t_dlssfgminos` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `t_dlssfg_os` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `t_dlssfg_api` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `t_dlssfg_hw` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `t_dlssfg_vsync` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `t_frame_stats` (`BPWC_Title_C`) via VerticalBoxSlot
    - `t_framerate` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `t_framepresented` (`BPW_Stat_C`) [variable] via VerticalBoxSlot

## References

Hard refs out (8):
- `/Game/Blueprints/NVIDIA_DEV/Core/BPWC_Title` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_Stat` [asset]
- `/Script/SlateCore` [asset]
- `/Script/StreamlineBlueprint` [asset]
- `/Script/StreamlineDLSSGBlueprint` [asset]
- `/Script/UMG` [asset]
- `/Script/UMG.UserWidget` [native]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

