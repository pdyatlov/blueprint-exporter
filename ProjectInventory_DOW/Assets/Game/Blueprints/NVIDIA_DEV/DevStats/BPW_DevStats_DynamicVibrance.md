# BPW_DevStats_DynamicVibrance

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/NVIDIA_DEV/DevStats/BPW_DevStats_DynamicVibrance.BPW_DevStats_DynamicVibrance` |
| Asset name | `BPW_DevStats_DynamicVibrance` |
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

## Class Default Object (4)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Custom`
- `DesignTimeSize` (`FVector2D`) = `(X=370.000000,Y=247.000000)`

## Graphs

- Event graph: `EventGraph` (40 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `brd_dvc_dev_stats` (`Border`) [variable]
  - `VerticalBox_154` (`VerticalBox`) via BorderSlot
    - `t_dv_stats` (`BPWC_Title_C`) via VerticalBoxSlot
    - `t_dv_mindriver` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `t_dv_driver` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `t_dvminos` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `t_dv_os` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `t_dv_api` (`BPW_Stat_C`) [variable] via VerticalBoxSlot

## References

Hard refs out (6):
- `/Game/Blueprints/NVIDIA_DEV/Core/BPWC_Title` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_Stat` [asset]
- `/Script/StreamlineBlueprint` [asset]
- `/Script/UMG` [asset]
- `/Script/UMG.UserWidget` [native]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

