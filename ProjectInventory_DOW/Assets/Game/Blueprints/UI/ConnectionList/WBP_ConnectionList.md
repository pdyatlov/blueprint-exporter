# WBP_ConnectionList

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/UI/ConnectionList/WBP_ConnectionList.WBP_ConnectionList` |
| Asset name | `WBP_ConnectionList` |
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
| `AddedConnectionWidgets` | `TArray<object<WBP_ConnectionListView_C>>` | — | `Default` | — | — | InstanceEditable, Private |

## Functions (2)

### `AddListView`

- Access: `Public`
- Flags: —
- Inputs: `(struct<SessionPlayerInfo> Info, int ArrayIndex)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 24

### `SortConnectionList`

- Access: `Public`
- Flags: —
- Inputs: `(TArray<struct<BPFriendInfo>> Friends)`
- Outputs: `(TArray<struct<BPFriendInfo>> Sorted friends)`
- Local variables (3): `OfflineFriends`, `OnlineFriends`, `AllFriends`
- Nodes: 19

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (3)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Desired`

## Graphs

- Event graph: `EventGraph` (13 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `SizeBox_28` (`SizeBox`)
  - `Border_34` (`Border`) via SizeBoxSlot
    - `VerticalBox_176` (`VerticalBox`) via BorderSlot
      - `Border_113` (`Border`) via VerticalBoxSlot
        - `HeaderLabel` (`TextBlock`) via BorderSlot
      - `ScrollBox_107` (`ScrollBox`) via VerticalBoxSlot
        - `Container` (`VerticalBox`) [variable] via ScrollBoxSlot

## References

Hard refs out (8):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Blueprints/UI/ConnectionList/WBP_ConnectionListView` [asset]
- `/Game/Fonts/Quantico-Regular_Font` [asset]
- `/Script/AdvancedSessions` [asset]
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

