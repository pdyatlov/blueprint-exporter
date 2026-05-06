# BPW_Slider

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_Slider.BPW_Slider` |
| Asset name | `BPW_Slider` |
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
| `caption` | `text` | `NSLOCTEXT("[9DEB22D34A1CB85CCE59BB89B9FEA004]", "1D4BFCCF44C3678B162A288BD0038648", "Slider")` | `Default` | — | — | InstanceEditable |
| `SliderChanged` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `range` | `struct<Vector2D>` | `(X=0.000000,Y=1.000000)` | `Default` | — | — | InstanceEditable |
| `increment` | `real<double>` | `0.100000` | `Default` | — | — | InstanceEditable |
| `Value` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable |

## Functions (1)

### `GetSliderValue`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Value)`
- Local variables: _none_
- Nodes: 3

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (5)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Custom`
- `DesignTimeSize` (`FVector2D`) = `(X=200.000000,Y=100.000000)`
- `Padding` (`FMargin`) = `(Bottom=10.000000)`

## Graphs

- Event graph: `EventGraph` (28 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `VerticalBox_76` (`VerticalBox`)
  - `HorizontalBox_0` (`HorizontalBox`) via VerticalBoxSlot
    - `sld_caption` (`TextBlock`) [variable] via HorizontalBoxSlot
    - `sld_text_val` (`TextBlock`) [variable] via HorizontalBoxSlot
  - `sld_value` (`Slider`) [variable] via VerticalBoxSlot

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

