# WBP_SteamFriendsList

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/UI/FindLobby/WBP_SteamFriendsList.WBP_SteamFriendsList` |
| Asset name | `WBP_SteamFriendsList` |
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
| `AddedFriendWidgets` | `TArray<object<WBP_SteamFriendView_C>>` | — | `Default` | — | — | InstanceEditable, Private |

## Functions (2)

### `AddFriendView`

- Access: `Public`
- Flags: —
- Inputs: `(struct<BPFriendInfo> Info, int ArrayIndex)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 26

### `Sort Friends`

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

- Event graph: `EventGraph` (11 nodes)
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

Hard refs out (7):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Blueprints/UI/FindLobby/WBP_SteamFriendView` [asset]
- `/Game/Fonts/Quantico-Regular_Font` [asset]
- `/Script/AdvancedSessions` [asset]
- `/Script/UMG` [asset]
- `/Script/UMG.UserWidget` [native]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

