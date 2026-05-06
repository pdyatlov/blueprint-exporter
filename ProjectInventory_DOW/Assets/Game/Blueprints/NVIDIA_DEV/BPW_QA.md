# BPW_QA

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/NVIDIA_DEV/BPW_QA.BPW_QA` |
| Asset name | `BPW_QA` |
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

## Macros (3)

### `Set ConstrainedView`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

### `Set EditorConstrainedView`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

### `Set ViewRectOffset`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (3)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignTimeSize` (`FVector2D`) = `(X=88.000000,Y=1138.000000)`

## Graphs

- Event graph: `EventGraph` (80 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_105` (`CanvasPanel`)
  - `Border_0` (`Border`) via CanvasPanelSlot
    - `VerticalBox_39` (`VerticalBox`) via BorderSlot
      - `TitleDebugPanel` (`BPWC_Title_C`) via VerticalBoxSlot
      - `lstCreatePlayer` (`BPW_List_C`) [variable] via VerticalBoxSlot
      - `sl_viewrectoffset` (`BPW_Slider_C`) [variable] via VerticalBoxSlot
      - `sl_EditorConstrainedView` (`BPW_Slider_C`) [variable] via VerticalBoxSlot
      - `sl_ConstrainedView` (`BPW_Slider_C`) [variable] via VerticalBoxSlot
      - `TextBlock_83` (`TextBlock`) via VerticalBoxSlot

## References

Hard refs out (8):
- `/Game/Blueprints/NVIDIA_DEV/Core/BPWC_Title` [asset]
- `/Game/Blueprints/NVIDIA_DEV/Core/E_MultiView` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_List` [asset]
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

