# BPW_DeepDVC

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/NVIDIA_DEV/BPW_DeepDVC.BPW_DeepDVC` |
| Asset name | `BPW_DeepDVC` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (3)

### `InitBPW_DeepDVC`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 31

### `Set Intensity Visibility Rules`

- Access: `Public`
- Flags: —
- Inputs: `(bool Visibility, object<BPW_Slider_C> Target Slider)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

### `Set Mode Visibility Rules`

- Access: `Public`
- Flags: —
- Inputs: `(bool Visibility)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 36

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (4)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Custom`
- `DesignTimeSize` (`FVector2D`) = `(X=422.000000,Y=472.000000)`

## Graphs

- Event graph: `EventGraph` (34 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `brd_DeepDVC` (`Border`) [variable]
  - `vbdvc` (`VerticalBox`) via BorderSlot
    - `t_deepdvc` (`BPWC_Title_C`) via VerticalBoxSlot
    - `t_dvc_support` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `l_dvc_mode` (`BPW_List_C`) [variable] via VerticalBoxSlot
    - `s_dvc_intensity` (`BPW_Slider_C`) [variable] via VerticalBoxSlot
    - `s_dvc_saturation` (`BPW_Slider_C`) [variable] via VerticalBoxSlot
    - `b_dv_showstats` (`BPW_Checkbox_C`) [variable] via VerticalBoxSlot
    - `BPW_DevStats_DynamicVibrance` (`BPW_DevStats_DynamicVibrance_C`) [variable] via VerticalBoxSlot

## References

Hard refs out (13):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Blueprints/NVIDIA_DEV/Core/BPWC_Title` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_Checkbox` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_List` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_Slider` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_Stat` [asset]
- `/Game/Blueprints/NVIDIA_DEV/DevStats/BPW_DevStats_DynamicVibrance` [asset]
- `/Script/SlateCore` [asset]
- `/Script/StreamlineBlueprint` [asset]
- `/Script/StreamlineDeepDVCBlueprint` [asset]
- `/Script/UMG` [asset]
- `/Script/UMG.UserWidget` [native]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

