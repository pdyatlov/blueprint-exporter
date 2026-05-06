# BPW_Reflex

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/NVIDIA_DEV/BPW_Reflex.BPW_Reflex` |
| Asset name | `BPW_Reflex` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (2)

### `InitBPW_Reflex`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 29

### `SetReflexVisibility`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9
- Category: `Default`

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (4)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Custom`
- `DesignTimeSize` (`FVector2D`) = `(X=326.000000,Y=584.000000)`

## Graphs

- Event graph: `EventGraph` (16 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `brd_reflex` (`Border`) [variable]
  - `vbReflex` (`VerticalBox`) via BorderSlot
    - `t_reflex` (`BPWC_Title_C`) via VerticalBoxSlot
    - `t_reflex_support` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
    - `l_reflex_mode` (`BPW_List_C`) [variable] via VerticalBoxSlot
    - `cb_reflex_showdevstats` (`BPW_Checkbox_C`) [variable] via VerticalBoxSlot
    - `BPW_DevStats_Reflex` (`BPW_DevStats_Reflex_C`) [variable] via VerticalBoxSlot

## References

Hard refs out (12):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Blueprints/NVIDIA_DEV/Core/BPWC_Title` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_Checkbox` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_List` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_Stat` [asset]
- `/Game/Blueprints/NVIDIA_DEV/DevStats/BPW_DevStats_Reflex` [asset]
- `/Script/StreamlineBlueprint` [asset]
- `/Script/StreamlineDLSSGBlueprint` [asset]
- `/Script/StreamlineReflexBlueprint` [asset]
- `/Script/UMG` [asset]
- `/Script/UMG.UserWidget` [native]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

