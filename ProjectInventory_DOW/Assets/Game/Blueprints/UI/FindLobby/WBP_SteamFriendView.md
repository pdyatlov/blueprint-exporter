# WBP_SteamFriendView

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/UI/FindLobby/WBP_SteamFriendView.WBP_SteamFriendView` |
| Asset name | `WBP_SteamFriendView` |
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
| `FriendInfo` | `struct<BPFriendInfo>` | `(OnlineState=Offline,UniqueNetId=(),PresenceInfo=(PresenceState=Offline))` | `Default` | — | — | InstanceEditable, Private |

## Functions (1)

### `SendInvitationToFriend`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (3)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Desired`

## Graphs

- Event graph: `EventGraph` (19 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `SizeBox_Avatar` (`SizeBox`) [variable]
  - `HorizontalBox_139` (`HorizontalBox`) via SizeBoxSlot
    - `SizeBox_147` (`SizeBox`) via HorizontalBoxSlot
      - `AvatarImage` (`Image`) [variable] via SizeBoxSlot
    - `Content` (`RetainerBox`) [variable] via HorizontalBoxSlot
      - `PlayerNameLabel` (`TextBlock`) [variable] via PanelSlot
    - `SizeBox_249` (`SizeBox`) via HorizontalBoxSlot
    - `InviteButton` (`WBP_Button_C`) [variable] via HorizontalBoxSlot

## References

Hard refs out (6):
- `/Game/Blueprints/UI/GenericElements/WBP_Button` [asset]
- `/Script/AdvancedSessions` [asset]
- `/Script/AdvancedSteamSessions` [asset]
- `/Script/UMG` [asset]
- `/Script/UMG.UserWidget` [native]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

