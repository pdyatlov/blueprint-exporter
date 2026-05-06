# UDS_Digital_Clock

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Widgets/UDS_Digital_Clock.UDS_Digital_Clock` |
| Asset name | `UDS_Digital_Clock` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (13)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `24h Time` | `bool` | `True` | `Customize` | — | — | InstanceEditable |
| `Show AM/PM` | `bool` | `False` | `Customize` | — | — | InstanceEditable |
| `Show Seconds` | `bool` | `True` | `Customize` | — | — | InstanceEditable |
| `Pad Hour with Zero` | `bool` | `True` | `Customize` | — | — | InstanceEditable |
| `Font` | `object<Font>` | `/Script/Engine.Font'/Engine/EngineFonts/DroidSansMono.DroidSansMono'` | `Customize` | — | — | InstanceEditable |
| `Font Size` | `int` | `24` | `Customize` | — | — | InstanceEditable |
| `Digit Spacing` | `int` | `0` | `Customize` | — | — | InstanceEditable |
| `Text Color` | `struct<LinearColor>` | `(R=0.635417,G=0.635417,B=0.635417,A=1.000000)` | `Customize` | — | — | InstanceEditable |
| `Show Background` | `bool` | `True` | `Customize` | — | — | InstanceEditable |
| `Background Color` | `struct<LinearColor>` | `(R=0.027321,G=0.027321,B=0.027321,A=1.000000)` | `Customize` | — | — | InstanceEditable |
| `Time Text Padding` | `struct<Margin>` | `(Left=10.000000,Top=6.000000,Right=10.000000,Bottom=4.000000)` | `Customize` | — | — | InstanceEditable |
| `Time Text Min Desired Width` | `real<float>` | `0.000000` | `Customize` | — | — | InstanceEditable |
| `Slate Font Info` | `struct<SlateFontInfo>` | `(OutlineSettings=(OutlineColor=(R=0.000000,G=0.000000,B=0.000000,A=1.000000)),Size=24.000000,MonospacedWidth=1.000000)` | `Customize` | — | — | InstanceEditable |

## Functions (1)

### `Update Time`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `Time`, `Time of Day`
- Nodes: 42

## Macros (1)

### `Pad Digits`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (4)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Desired`
- `PaletteCategory` (`FText`) = `NSLOCTEXT("", "E02F13544C77A2C9E43A4CB36AE3D902", "Ultra Dynamic Sky Widgets")`
- `Visibility` (`ESlateVisibility`) = `HitTestInvisible`

## Graphs

- Event graph: `EventGraph` (41 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_0` (`CanvasPanel`)
  - `CanvasPanel_50` (`CanvasPanel`) via CanvasPanelSlot
    - `Background` (`Image`) [variable] via CanvasPanelSlot
    - `HorizontalBox_57` (`HorizontalBox`) via CanvasPanelSlot
      - `TimeText` (`TextBlock`) [variable] via HorizontalBoxSlot

## References

Hard refs out (8):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Engine/EngineFonts/DroidSansMono` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/UltraDynamicWeather_Parameters` [asset]
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

