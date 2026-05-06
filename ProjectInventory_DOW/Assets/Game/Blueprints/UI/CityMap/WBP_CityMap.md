# WBP_CityMap

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/UI/CityMap/WBP_CityMap.WBP_CityMap` |
| Asset name | `WBP_CityMap` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (2)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `GameFlowRef` | `object<WBP_GameFlow_C>` | `None` | `Default` | — | — | InstanceEditable |
| `LevelPath` | `string` | — | `Default` | — | — | InstanceEditable, Private |

## Functions (2)

### `SelectMission`

- Access: `Public`
- Flags: —
- Inputs: `(object<WBP_MissionIcon_C> MissionIcon, string LevelPath, text MissionName)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

### `SetAllIconsSelected`

- Access: `Public`
- Flags: —
- Inputs: `(bool IsSelected)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (2)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`

## Graphs

- Event graph: `EventGraph` (32 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_23` (`CanvasPanel`)
  - `Background` (`Image`) [variable] via CanvasPanelSlot
  - `SelectedMissionPanel` (`WBP_SelectedMissionPanel_C`) [variable] via CanvasPanelSlot
  - `IconsPanel` (`CanvasPanel`) [variable] via CanvasPanelSlot
    - `MissionIcon_PinkStacks` (`WBP_MissionIcon_C`) [variable] via CanvasPanelSlot
    - `MissionIcon_Noodles` (`WBP_MissionIcon_C`) [variable] via CanvasPanelSlot
    - `MissionIcon_HeistExtraction` (`WBP_MissionIcon_C`) [variable] via CanvasPanelSlot
    - `MissionIcon_Protein` (`WBP_MissionIcon_C`) [variable] via CanvasPanelSlot

## References

Hard refs out (9):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Art/UI/CityMap/citymap_screen` [asset]
- `/Game/Blueprints/UI/CityMap/WBP_MissionIcon` [asset]
- `/Game/Blueprints/UI/CityMap/WBP_SelectedMissionPanel` [asset]
- `/Game/Blueprints/UI/GameFlow/WBP_GameFlow` [asset]
- `/Script/UE_DOW` [asset]
- `/Script/UMG` [asset]
- `/Script/UMG.UserWidget` [native]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

