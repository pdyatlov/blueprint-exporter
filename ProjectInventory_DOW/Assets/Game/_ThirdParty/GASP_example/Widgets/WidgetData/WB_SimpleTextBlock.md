# WB_SimpleTextBlock

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Widgets/WidgetData/WB_SimpleTextBlock.WB_SimpleTextBlock` |
| Asset name | `WB_SimpleTextBlock` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (7)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `BoxSize` | `struct<Vector2D>` | `(X=100.000000,Y=25.000000)` | `Default` | — | — | InstanceEditable |
| `BoxColor` | `struct<LinearColor>` | `(R=0.015686,G=0.015686,B=0.015686,A=1.000000)` | `Default` | — | — | InstanceEditable |
| `Text` | `Text` | `NSLOCTEXT("[7ABCEEA56AF779750B3F6CFDA382164F]", "AEA791C94093F43A76D664866EA9F3FE", "Text")` | `Default` | — | — | InstanceEditable |
| `TextAlignment` | `byte<EHorizontalAlignment>` | `HAlign_Left` | `Default` | — | — | InstanceEditable |
| `TextPadding` | `struct<Margin>` | `()` | `Default` | — | — | InstanceEditable |
| `TextColor` | `struct<LinearColor>` | `(R=0.500000,G=0.500000,B=0.500000,A=1.000000)` | `Default` | — | — | InstanceEditable |
| `IsBold` | `bool` | `False` | `Default` | — | — | InstanceEditable |

## Functions (2)

### `SetUpBox`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 22
- Category: `Default`

### `UpdateText`

- Access: `Public`
- Flags: —
- Inputs: `(text Text, struct<LinearColor> Color = (R=0.500000,G=0.500000,B=0.500000,A=1.000000), bool IsBold)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (4)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Custom`
- `DesignTimeSize` (`FVector2D`) = `(X=100.000000,Y=25.000000)`

## Graphs

- Event graph: `EventGraph` (2 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `SizeBox` (`SizeBox`) [variable]
  - `Border` (`Border`) [variable] via SizeBoxSlot
    - `TextBox` (`TextBlock`) [variable] via BorderSlot

## References

Hard refs out (5):
- `/Script/SlateCore` [asset]
- `/Script/SlateRHIRenderer` [asset]
- `/Script/UMG` [asset]
- `/Script/UMG.UserWidget` [native]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

