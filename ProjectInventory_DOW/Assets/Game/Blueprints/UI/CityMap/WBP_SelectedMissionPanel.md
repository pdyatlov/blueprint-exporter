# WBP_SelectedMissionPanel

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/UI/CityMap/WBP_SelectedMissionPanel.WBP_SelectedMissionPanel` |
| Asset name | `WBP_SelectedMissionPanel` |
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
| `OnStartMissionButtonPressedED` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable |

## Functions (1)

### `Show`

- Access: `Public`
- Flags: —
- Inputs: `(text MissionName)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (2)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`

## Graphs

- Event graph: `EventGraph` (5 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `SizeBox_67` (`SizeBox`)
  - `CanvasPanel_89` (`CanvasPanel`) via SizeBoxSlot
    - `SelectedMissionPanelBackground` (`Image`) [variable] via CanvasPanelSlot
    - `Header` (`TextBlock`) [variable] via CanvasPanelSlot
    - `TextBlock_300` (`TextBlock`) via CanvasPanelSlot
    - `StartMissionButton` (`WBP_Button_C`) [variable] via CanvasPanelSlot

## References

Hard refs out (6):
- `/Game/Art/UI/CityMap/popup` [asset]
- `/Game/Blueprints/UI/GenericElements/WBP_Button` [asset]
- `/Game/Fonts/Quantico-Regular_Font` [asset]
- `/Script/UMG` [asset]
- `/Script/UMG.UserWidget` [native]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

