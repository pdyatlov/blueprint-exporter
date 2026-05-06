# WBP_Countdown

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Developers/andersjansson/Mission/WBP_Countdown.WBP_Countdown` |
| Asset name | `WBP_Countdown` |
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

### `UpdateTime`

- Access: `Public`
- Flags: —
- Inputs: `(int TimeRemaining)`
- Outputs: `(bool TimeUp)`
- Local variables: _none_
- Nodes: 9

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (2)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`

## Graphs

- Event graph: `EventGraph` (3 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_21` (`CanvasPanel`)
  - `Overlay_0` (`Overlay`) via CanvasPanelSlot
    - `Image_53` (`Image`) [variable] via OverlaySlot
    - `TimeText` (`TextBlock`) [variable] via OverlaySlot

## References

Hard refs out (4):
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

