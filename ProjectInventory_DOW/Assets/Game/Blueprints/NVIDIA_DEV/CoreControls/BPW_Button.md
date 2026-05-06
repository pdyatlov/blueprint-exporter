# BPW_Button

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_Button.BPW_Button` |
| Asset name | `BPW_Button` |
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
| `Caption` | `text` | `NSLOCTEXT("[FD2F79054D1C08B95E6B75B3CD09AC55]", "32A440B746848EAB7D1737904006A043", "Button")` | `Default` | — | — | InstanceEditable |
| `ButtonClicked` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |

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
- `DesignTimeSize` (`FVector2D`) = `(X=100.000000,Y=30.000000)`

## Graphs

- Event graph: `EventGraph` (11 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `btn_w_text` (`Button`) [variable]
  - `txt_caption` (`TextBlock`) [variable] via ButtonSlot

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

