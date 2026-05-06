# WBP_NavigationPanel

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/UI/NavigationPanel/WBP_NavigationPanel.WBP_NavigationPanel` |
| Asset name | `WBP_NavigationPanel` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (3)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `GameFlowRef` | `object<WBP_GameFlow_C>` | `None` | `Default` | — | — | InstanceEditable |
| `PlayerIndicators` | `TMap<string<WBP_PlayerIndicator_C>>, :/Game/Blueprints/UI/NavigationPanel/WBP_PlayerIndicator.WBP_PlayerIndicator_C>` | `()` | `Default` | — | — | InstanceEditable, Private |
| `PlayerColors` | `TArray<struct<LinearColor>>` | — | `Default` | — | — | InstanceEditable, Private |

## Functions (4)

### `HandleMemberDataChanged`

- Access: `Public`
- Flags: —
- Inputs: `(string MemberId, string Key, string Value)`
- Outputs: `()`
- Local variables (3): `CurrentMemberId`, `Indicator`, `TargetTabIndex`
- Nodes: 36

### `InitialSync`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14

### `SelectIcon`

- Access: `Public`
- Flags: —
- Inputs: `(object<WBP_NavigationView_C> View)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 17

### `TryCreateIndicatorForMember`

- Access: `Public`
- Flags: —
- Inputs: `(string MemberId)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 16

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (2)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`

## Graphs

- Event graph: `EventGraph` (29 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_19` (`CanvasPanel`)
  - `HorizontalBox` (`HorizontalBox`) [variable] via CanvasPanelSlot
    - `WBP_NavigationView_CityMap` (`WBP_NavigationView_C`) [variable] via HorizontalBoxSlot
    - `WBP_NavigationView_MissionPlanning` (`WBP_NavigationView_C`) [variable] via HorizontalBoxSlot
    - `WBP_NavigationView_Loadout` (`WBP_NavigationView_C`) [variable] via HorizontalBoxSlot
    - `WBP_NavigationView_Hideout` (`WBP_NavigationView_C`) [variable] via HorizontalBoxSlot

## References

Hard refs out (17):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Art/UI/NavigationPanel/Icons/icon_citymap_default` [asset]
- `/Game/Art/UI/NavigationPanel/Icons/icon_citymap_selected` [asset]
- `/Game/Art/UI/NavigationPanel/Icons/icon_hideout_default` [asset]
- `/Game/Art/UI/NavigationPanel/Icons/icon_hideout_selected` [asset]
- `/Game/Art/UI/NavigationPanel/Icons/icon_loadout_default` [asset]
- `/Game/Art/UI/NavigationPanel/Icons/icon_loadout_selected` [asset]
- `/Game/Art/UI/NavigationPanel/Icons/icon_mission_planning_default` [asset]
- `/Game/Art/UI/NavigationPanel/Icons/icon_mission_planning_selected` [asset]
- `/Game/Blueprints/EditorUtilities/EU_MacroLib` [asset]
- `/Game/Blueprints/UI/GameFlow/WBP_GameFlow` [asset]
- `/Game/Blueprints/UI/NavigationPanel/WBP_NavigationView` [asset]
- `/Game/Blueprints/UI/NavigationPanel/WBP_PlayerIndicator` [asset]
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

