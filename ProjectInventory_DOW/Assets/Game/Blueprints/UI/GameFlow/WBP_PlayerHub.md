# WBP_PlayerHub

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/UI/GameFlow/WBP_PlayerHub.WBP_PlayerHub` |
| Asset name | `WBP_PlayerHub` |
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
| `GameFlowRef` | `object<WBP_GameFlow_C>` | `None` | `Default` | — | — | InstanceEditable |

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

- Event graph: `EventGraph` (11 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_18` (`CanvasPanel`)
  - `Background` (`Image`) [variable] via CanvasPanelSlot
  - `StartLevelButton` (`WBP_Button_C`) [variable] via CanvasPanelSlot
  - `SearchTeamsButton` (`WBP_Button_C`) [variable] via CanvasPanelSlot
  - `EditMercProfileButton` (`WBP_Button_C`) [variable] via CanvasPanelSlot
  - `WBP_ConnectionList` (`WBP_ConnectionList_C`) [variable] via CanvasPanelSlot

## References

Hard refs out (7):
- `/Game/Art/UI/player_hub` [asset]
- `/Game/Blueprints/UI/ConnectionList/WBP_ConnectionList` [asset]
- `/Game/Blueprints/UI/GameFlow/WBP_GameFlow` [asset]
- `/Game/Blueprints/UI/GenericElements/WBP_Button` [asset]
- `/Script/UMG` [asset]
- `/Script/UMG.UserWidget` [native]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

