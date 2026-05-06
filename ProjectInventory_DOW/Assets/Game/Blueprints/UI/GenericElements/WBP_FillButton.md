# WBP_FillButton

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/UI/GenericElements/WBP_FillButton.WBP_FillButton` |
| Asset name | `WBP_FillButton` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (6)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `IsHolding` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `HoldProgress` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `HoldDuration` | `real<double>` | `0.500000` | `Default` | — | — | InstanceEditable, Private |
| `UnrollSpeed` | `real<double>` | `1.000000` | `Default` | — | — | InstanceEditable, Private |
| `OnFillCompleted` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Text` | `text` | — | `Default` | — | — | InstanceEditable |

## Functions (4)

### `SetButtonInteractible`

- Access: `Public`
- Flags: —
- Inputs: `(bool Value)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `SetButtonText`

- Access: `Public`
- Flags: —
- Inputs: `(text Text)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `SetButtonVisible`

- Access: `Public`
- Flags: —
- Inputs: `(byte Value = Visible)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

### `SetFillProgress`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> HoldProgress)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `bHasScriptImplementedPaint` (`uint8`) = `False`

## Graphs

- Event graph: `EventGraph` (28 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `FillButton` (`Button`) [variable]
  - `Overlay_626` (`Overlay`) via ButtonSlot
    - `FillProgressBar` (`ProgressBar`) [variable] via OverlaySlot
    - `Detail` (`Image`) via OverlaySlot
    - `Border` (`Image`) via OverlaySlot
    - `Label` (`TextBlock`) [variable] via OverlaySlot

## References

Hard refs out (7):
- `/Game/Art/UI/Button/generic_button_border` [asset]
- `/Game/Art/UI/Button/generic_button_detail` [asset]
- `/Game/Fonts/Quantico-Regular_Font` [asset]
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

