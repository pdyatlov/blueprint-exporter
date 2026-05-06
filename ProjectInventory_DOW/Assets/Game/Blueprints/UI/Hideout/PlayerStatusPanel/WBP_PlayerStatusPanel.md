# WBP_PlayerStatusPanel

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/UI/Hideout/PlayerStatusPanel/WBP_PlayerStatusPanel.WBP_PlayerStatusPanel` |
| Asset name | `WBP_PlayerStatusPanel` |
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

## Class Default Object (2)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`

## Graphs

- Event graph: `EventGraph` (3 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_30` (`CanvasPanel`)
  - `Icon` (`Image`) [variable] via CanvasPanelSlot
  - `VerticalBox_49` (`VerticalBox`) via CanvasPanelSlot
    - `Border_39` (`Border`) via VerticalBoxSlot
      - `TextBlock_302` (`TextBlock`) via BorderSlot
    - `Border` (`Border`) via VerticalBoxSlot
      - `TextBlock_376` (`TextBlock`) via BorderSlot

## References

Hard refs out (6):
- `/Game/Art/UI/hideout_player_icon` [asset]
- `/Game/Fonts/Quantico-Regular_Font` [asset]
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

