# WBP_GameFlow

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/UI/GameFlow/WBP_GameFlow.WBP_GameFlow` |
| Asset name | `WBP_GameFlow` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (3)

### `SetNavigationPanelVisible`

- Access: `Public`
- Flags: —
- Inputs: `(byte Visibility = Visible)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `ShowLoadingScreen`

- Access: `Public`
- Flags: —
- Inputs: `(text MissionName)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9

### `SwitchToPage`

- Access: `Public`
- Flags: —
- Inputs: `(int Index)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (2)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`

## Graphs

- Event graph: `EventGraph` (24 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_229` (`CanvasPanel`)
  - `WidgetSwitcher` (`WidgetSwitcher`) [variable] via CanvasPanelSlot
    - `WBP_PlayerHub` (`WBP_PlayerHub_C`) [variable] via WidgetSwitcherSlot
    - `WBP_FindLobby` (`WBP_FindLobby_C`) [variable] via WidgetSwitcherSlot
    - `WBP_LoadingScreen` (`WBP_LoadingScreen_C`) [variable] via WidgetSwitcherSlot
    - `WBP_CityMap` (`WBP_CityMap_C`) [variable] via WidgetSwitcherSlot
    - `WBP_MissionPlanner` (`WBP_MissionPlanner_C`) [variable] via WidgetSwitcherSlot
    - `WBP_Loadout` (`WBP_Loadout_C`) [variable] via WidgetSwitcherSlot
    - `WBP_Hideout` (`WBP_Hideout_C`) [variable] via WidgetSwitcherSlot
  - `WBP_NavigationPanel` (`WBP_NavigationPanel_C`) [variable] via CanvasPanelSlot

## References

Hard refs out (12):
- `/Game/Blueprints/UI/CityMap/WBP_CityMap` [asset]
- `/Game/Blueprints/UI/FindLobby/WBP_FindLobby` [asset]
- `/Game/Blueprints/UI/GameFlow/WBP_PlayerHub` [asset]
- `/Game/Blueprints/UI/Hideout/WBP_Hideout` [asset]
- `/Game/Blueprints/UI/LoadingScreen/WBP_LoadingScreen` [asset]
- `/Game/Blueprints/UI/Loadout/WBP_Loadout` [asset]
- `/Game/Blueprints/UI/MissionPlanner/WBP_MissionPlanner` [asset]
- `/Game/Blueprints/UI/NavigationPanel/WBP_NavigationPanel` [asset]
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

