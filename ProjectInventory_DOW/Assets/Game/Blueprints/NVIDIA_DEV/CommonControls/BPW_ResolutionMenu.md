# BPW_ResolutionMenu

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/NVIDIA_DEV/CommonControls/BPW_ResolutionMenu.BPW_ResolutionMenu` |
| Asset name | `BPW_ResolutionMenu` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `BPW_List_C` (`/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_List.BPW_List_C`, blueprint)
- Interfaces: _none_

## Variables (1)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Resolutions` | `object<DataTable>` | `/Script/Engine.DataTable'/Game/Blueprints/NVIDIA_DEV/CommonControls/DT_Resoltions.DT_Resoltions'` | `Default` | — | — | InstanceEditable |

## Functions (1)

### `InitResolution`

- Access: `Public`
- Flags: —
- Inputs: `(object<GameUserSettings> GameUserSettings)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `label` (`FText`) = `NSLOCTEXT("[F81C42653395F7FC839DCC1C808A2674]", "8A7CE54A4832771B41CC0CAAAEB27033", "Resolution")`

## Graphs

- Event graph: `EventGraph` (24 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

_No widget tree (empty root)._

## References

Hard refs out (8):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CommonControls/BPS_Resolutions` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CommonControls/DT_Resoltions` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_List` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_List.BPW_List_C` [Blueprint]
- `/Script/SlateCore` [asset]
- `/Script/UMG` [asset]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

