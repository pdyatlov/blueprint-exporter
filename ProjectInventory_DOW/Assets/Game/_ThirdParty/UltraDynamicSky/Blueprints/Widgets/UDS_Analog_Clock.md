# UDS_Analog_Clock

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Widgets/UDS_Analog_Clock.UDS_Analog_Clock` |
| Asset name | `UDS_Analog_Clock` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (16)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Clock Size` | `real<double>` | `200.000000` | `Customize` | — | — | InstanceEditable |
| `Clock Face Texture` | `object<Texture2D>` | `/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Widgets/Clock_Face.Clock_Face'` | `Customize` | — | — | InstanceEditable |
| `Show Hour Hand` | `bool` | `True` | `Customize` | — | — | InstanceEditable |
| `Hour Hand Texture` | `object<Texture2D>` | `/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Widgets/Clock_Hand.Clock_Hand'` | `Customize` | — | — | InstanceEditable |
| `Hour Hand Size` | `struct<Vector2D>` | `(X=8.000000,Y=40.000000)` | `Customize` | — | — | InstanceEditable |
| `Hour Hand Color` | `struct<LinearColor>` | `(R=0.432292,G=0.432292,B=0.432292,A=1.000000)` | `Customize` | — | — | InstanceEditable |
| `Show Minute Hand` | `bool` | `True` | `Customize` | — | — | InstanceEditable |
| `Minute Hand Texture` | `object<Texture2D>` | `/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Widgets/Clock_Hand.Clock_Hand'` | `Customize` | — | — | InstanceEditable |
| `Minute Hand Size` | `struct<Vector2D>` | `(X=6.000000,Y=60.000000)` | `Customize` | — | — | InstanceEditable |
| `Minute Hand Color` | `struct<LinearColor>` | `(R=0.432292,G=0.432292,B=0.432292,A=1.000000)` | `Customize` | — | — | InstanceEditable |
| `Show Second Hand` | `bool` | `False` | `Customize` | — | — | InstanceEditable |
| `Second Hand Texture` | `object<Texture2D>` | `/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Widgets/Clock_Hand.Clock_Hand'` | `Customize` | — | — | InstanceEditable |
| `Second Hand Size` | `struct<Vector2D>` | `(X=3.000000,Y=60.000000)` | `Customize` | — | — | InstanceEditable |
| `Second Hand Color` | `struct<LinearColor>` | `(R=0.473958,G=0.154875,B=0.093292,A=1.000000)` | `Customize` | — | — | InstanceEditable |
| `Show Axis Circle` | `bool` | `True` | `Customize` | — | — | InstanceEditable |
| `Axis Circle Color` | `struct<LinearColor>` | `(R=0.432292,G=0.432292,B=0.432292,A=1.000000)` | `Customize` | — | — | InstanceEditable |

## Functions (1)

### `Update Hands`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Time`
- Nodes: 21

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (5)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Desired`
- `DesignTimeSize` (`FVector2D`) = `(X=200.000000,Y=200.000000)`
- `PaletteCategory` (`FText`) = `NSLOCTEXT("", "F6FDE5904B4DE779F459C5BF70FD0F9A", "Ultra Dynamic Sky Widgets")`
- `Visibility` (`ESlateVisibility`) = `HitTestInvisible`

## Graphs

- Event graph: `EventGraph` (76 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_0` (`CanvasPanel`)
  - `CanvasPanel_60` (`CanvasPanel`) via CanvasPanelSlot
    - `Face_Image` (`Image`) [variable] via CanvasPanelSlot
    - `MinuteHand` (`Image`) [variable] via CanvasPanelSlot
    - `HourHand` (`Image`) [variable] via CanvasPanelSlot
    - `SecondHand` (`Image`) [variable] via CanvasPanelSlot
    - `Axis_Circle` (`Image`) [variable] via CanvasPanelSlot

## References

Hard refs out (9):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/UltraDynamicWeather_Parameters` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Widgets/Clock_Center` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Widgets/Clock_Face` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Widgets/Clock_Hand` [asset]
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

