# BPW_List

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_List.BPW_List` |
| Asset name | `BPW_List` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (5)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `label` | `text` | `NSLOCTEXT("[C4C9C729961945447EE5C3274BCC0267]", "019F143C46BE044BB341DBB6723A3567", "Label")` | `Default` | — | — | InstanceEditable |
| `options` | `TArray<string>` | — | `Default` | — | — | InstanceEditable |
| `selected_id` | `int` | `0` | `Default` | — | — | InstanceEditable |
| `dropdown_padding` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable |
| `SelectionChanged` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |

## Functions (4)

### `AddOption`

- Access: `Public`
- Flags: —
- Inputs: `(string Option)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `Default`

### `GetSelectedOption`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(int OptionID, string OptionLabel)`
- Local variables: _none_
- Nodes: 5
- Category: `Default`

### `SetDisabled`

- Access: `Public`
- Flags: —
- Inputs: `(bool Is Disabled)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `Default`

### `SetSelectedOption`

- Access: `Public`
- Flags: —
- Inputs: `(string OptionName, int OptionID)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12
- Category: `Default`

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (4)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Custom`
- `DesignTimeSize` (`FVector2D`) = `(X=256.000000,Y=32.000000)`

## Graphs

- Event graph: `EventGraph` (25 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `HorizontalBox_34` (`HorizontalBox`)
  - `txt_label` (`TextBlock`) [variable] via HorizontalBoxSlot
  - `l_items` (`ComboBoxString`) [variable] via HorizontalBoxSlot

## References

Hard refs out (5):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
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

