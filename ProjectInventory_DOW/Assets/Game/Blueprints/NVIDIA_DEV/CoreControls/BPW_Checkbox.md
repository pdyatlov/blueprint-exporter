# BPW_Checkbox

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_Checkbox.BPW_Checkbox` |
| Asset name | `BPW_Checkbox` |
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
| `caption` | `text` | `NSLOCTEXT("[58C763664E28770F8DAA208389700619]", "ABF3453A4F96363F4FCE8790DC226BA3", "checkbox")` | `Default` | — | — | InstanceEditable |
| `CheckBoxStateChanged` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `chk_state` | `byte<ECheckBoxState>` | `Unchecked` | `Default` | — | — | InstanceEditable |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (4)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Custom`
- `DesignTimeSize` (`FVector2D`) = `(X=200.000000,Y=100.000000)`

## Graphs

- Event graph: `EventGraph` (11 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `HorizontalBox_117` (`HorizontalBox`)
  - `chk_val` (`CheckBox`) [variable] via HorizontalBoxSlot
  - `chk_caption` (`TextBlock`) [variable] via HorizontalBoxSlot

## References

Hard refs out (4):
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

