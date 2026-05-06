# BPW_DLSSFG

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/NVIDIA_DEV/BPW_DLSSFG.BPW_DLSSFG` |
| Asset name | `BPW_DLSSFG` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (1)

### `InitBPW_DLSSFG`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 29

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (4)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Custom`
- `DesignTimeSize` (`FVector2D`) = `(X=428.000000,Y=584.000000)`

## Graphs

- Event graph: `EventGraph` (20 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `brd_DLSS-FG` (`Border`) [variable]
  - `vbDLSSFG` (`VerticalBox`) via BorderSlot
    - `t_dlssfg` (`BPWC_Title_C`) via VerticalBoxSlot
    - `t_dlssfg_support` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `l_dlssfg_modes` (`BPW_List_C`) [variable] via VerticalBoxSlot
    - `b_dlssfg_showstats` (`BPW_Checkbox_C`) [variable] via VerticalBoxSlot
    - `BPW_DevStatDLSSFG` (`BPW_DevStats_DLSSFG_C`) [variable] via VerticalBoxSlot
    - `BPW_Reflex` (`BPW_Reflex_C`) [variable] via VerticalBoxSlot

## References

Hard refs out (13):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Blueprints/NVIDIA_DEV/BPW_Reflex` [asset]
- `/Game/Blueprints/NVIDIA_DEV/Core/BPWC_Title` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_Checkbox` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_List` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_Stat` [asset]
- `/Game/Blueprints/NVIDIA_DEV/DevStats/BPW_DevStats_DLSSFG` [asset]
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

