# BPW_NGX

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/NVIDIA_DEV/BPW_NGX.BPW_NGX` |
| Asset name | `BPW_NGX` |
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
| `DLSSMode` | `byte<UDLSSMode>` | `Off` | `Default` | — | — | InstanceEditable, Private |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (3)

- `bAutomaticallyRegisterInputOnConstruction` (`uint8`) = `True`
- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`

## Graphs

- Event graph: `EventGraph` (27 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_0` (`CanvasPanel`)
  - `bd_UI` (`Border`) [variable] via CanvasPanelSlot
    - `wb_menu` (`WrapBox`) via BorderSlot
      - `vb_upscallingaa` (`VerticalBox`) via WrapBoxSlot
        - `BPW_UpscalingAA` (`BPW_DLSSSR_UpscalingAA_C`) [variable] via VerticalBoxSlot
      - `vbDLSSFG` (`VerticalBox`) via WrapBoxSlot
        - `BPW_DLSSFG` (`BPW_DLSSFG_C`) [variable] via VerticalBoxSlot
      - `vbdvc` (`VerticalBox`) via WrapBoxSlot
        - `BPW_DeepDVC` (`BPW_DeepDVC_C`) [variable] via VerticalBoxSlot
  - `BPW_QA` (`BPW_QA_C`) [variable] via CanvasPanelSlot

## References

Hard refs out (11):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Blueprints/NVIDIA_DEV/BPW_DeepDVC` [asset]
- `/Game/Blueprints/NVIDIA_DEV/BPW_DLSSFG` [asset]
- `/Game/Blueprints/NVIDIA_DEV/BPW_DLSSSR_UpscalingAA` [asset]
- `/Game/Blueprints/NVIDIA_DEV/BPW_QA` [asset]
- `/Script/DLSSBlueprint` [asset]
- `/Script/InputCore` [asset]
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

