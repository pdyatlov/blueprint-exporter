# WBP_MissionIcon

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/UI/CityMap/WBP_MissionIcon.WBP_MissionIcon` |
| Asset name | `WBP_MissionIcon` |
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
| `OnSelected` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |

## Functions (2)

### `OnMouseButtonDown`

- Access: `Public`
- Flags: —
- Net exec: BlueprintCosmetic
- Inputs: `(struct<Geometry> MyGeometry, struct<PointerEvent>& MouseEvent [ref])`
- Outputs: `(struct<EventReply> ReturnValue, struct<EventReply> ReturnValue)`
- Local variables: _none_
- Nodes: 8

### `SetSelectedStatus`

- Access: `Public`
- Flags: —
- Inputs: `(bool IsSelected)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (2)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`

## Graphs

- Event graph: `EventGraph` (2 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `SizeBox_23` (`SizeBox`)
  - `CanvasPanel_197` (`CanvasPanel`) via SizeBoxSlot
    - `SelectedImage` (`Image`) [variable] via CanvasPanelSlot
    - `Background` (`Image`) [variable] via CanvasPanelSlot
    - `Icon` (`Image`) [variable] via CanvasPanelSlot

## References

Hard refs out (8):
- `/Game/Art/UI/CityMap/intel_icon_1` [asset]
- `/Game/Art/UI/CityMap/node_medium` [asset]
- `/Game/Art/UI/CityMap/node_selected` [asset]
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

