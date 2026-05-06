# BPW_Stat

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_Stat.BPW_Stat` |
| Asset name | `BPW_Stat` |
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
| `caption` | `text` | `NSLOCTEXT("[8FBD1D414BB9422BD7104E8EA1C1B64F]", "1A6FF32E4C4A3293856D03A50E96186E", "Label")` | `Default` | — | — | InstanceEditable |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (4)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `CustomOnScreen`
- `DesignTimeSize` (`FVector2D`) = `(X=250.000000,Y=50.000000)`

## Graphs

- Event graph: `EventGraph` (13 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `HorizontalBox_24` (`HorizontalBox`)
  - `txt_caption` (`TextBlock`) [variable] via HorizontalBoxSlot
  - `txt_value` (`TextBlock`) [variable] via HorizontalBoxSlot

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

