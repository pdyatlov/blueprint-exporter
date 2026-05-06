# WBP_LoadingScreen

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/UI/LoadingScreen/WBP_LoadingScreen.WBP_LoadingScreen` |
| Asset name | `WBP_LoadingScreen` |
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

## Functions (1)

### `SetMissionInfo`

- Access: `Public`
- Flags: —
- Inputs: `(text InText)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (2)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_22` (`CanvasPanel`)
  - `BackgroundImage` (`Image`) [variable] via CanvasPanelSlot
  - `Label` (`TextBlock`) [variable] via CanvasPanelSlot

## References

Hard refs out (5):
- `/Game/Art/UI/citymap_bg` [asset]
- `/Game/Blueprints/UI/GameFlow/WBP_GameFlow` [asset]
- `/Script/UMG` [asset]
- `/Script/UMG.UserWidget` [native]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

