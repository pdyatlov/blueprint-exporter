# UDW_Thermometer

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Widgets/UDW_Thermometer.UDW_Thermometer` |
| Asset name | `UDW_Thermometer` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (24)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Temperature Scale` | `byte<UDS_TemperatureType>` | `NewEnumerator0` | `Customize` | — | — | InstanceEditable |
| `Temperature Sampling Location` | `byte<UDS_Temperature_Sample_Location>` | `NewEnumerator0` | `Customize` | — | — | InstanceEditable |
| `Custom Temperature Sample Location` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Customize` | — | — | InstanceEditable |
| `Temperature Decimals` | `int` | `0` | `Customize` | — | — | InstanceEditable |
| `Display Scale` | `bool` | `True` | `Customize` | — | — | InstanceEditable |
| `Slate Font Info` | `struct<SlateFontInfo>` | `(FontObject="/Script/Engine.Font'/Engine/EngineFonts/Roboto.Roboto'",OutlineSettings=(OutlineColor=(R=0.000000,G=0.000000,B=0.000000,A=1.000000)),TypefaceFontName="Regular",Size=24.000000,MonospacedWidth=1.000000)` | `Customize` | — | — | InstanceEditable |
| `Neutral Text Color` | `struct<LinearColor>` | `(R=0.635417,G=0.635417,B=0.635417,A=1.000000)` | `Customize` | — | — | InstanceEditable |
| `Apply Hot/Cold Text Colors` | `bool` | `False` | `Customize` | — | — | InstanceEditable |
| `Hot Text Color` | `struct<LinearColor>` | `(R=0.635417,G=0.148180,B=0.103880,A=1.000000)` | `Customize` | — | — | InstanceEditable |
| `Hot Threshold` | `real<double>` | `0.000000` | `Customize` | — | — | InstanceEditable |
| `Cold Text Color` | `struct<LinearColor>` | `(R=0.175223,G=0.326066,B=0.635417,A=1.000000)` | `Customize` | — | — | InstanceEditable |
| `Cold Threshold` | `real<double>` | `0.000000` | `Customize` | — | — | InstanceEditable |
| `Show Background` | `bool` | `True` | `Customize` | — | — | InstanceEditable |
| `Background Color` | `struct<LinearColor>` | `(R=0.027321,G=0.027321,B=0.027321,A=1.000000)` | `Customize` | — | — | InstanceEditable |
| `Text Padding` | `struct<Margin>` | `(Left=10.000000,Top=6.000000,Right=10.000000,Bottom=4.000000)` | `Customize` | — | — | InstanceEditable |
| `Text Min Desired Width` | `real<float>` | `0.000000` | `Customize` | — | — | InstanceEditable |
| `Temperature Sample Period` | `real<double>` | `0.500000` | `Customize` | — | — | InstanceEditable |
| `UDW` | `object<Ultra_Dynamic_Weather_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Last Temperature Value` | `real<double>` | `0.000000` | `System` | — | — | InstanceEditable, Private |
| `New Temperature Value` | `real<double>` | `0.000000` | `System` | — | — | InstanceEditable, Private |
| `Last Text Color` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=0.000000)` | `System` | — | — | InstanceEditable, Private |
| `New Text Color` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=0.000000)` | `System` | — | — | InstanceEditable, Private |
| `Actor Weather Status` | `object<Actor_Weather_Status_C>` | `None` | `Customize` | — | — | InstanceEditable |
| `Update Timer` | `struct<TimerHandle>` | `()` | `System` | — | — | InstanceEditable, Private |

## Functions (2)

### `Get Temperature`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 41

### `Update Temp Display`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Alpha`
- Nodes: 30

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (4)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Desired`
- `PaletteCategory` (`FText`) = `NSLOCTEXT("", "E02F13544C77A2C9E43A4CB36AE3D902", "Ultra Dynamic Sky Widgets")`
- `Visibility` (`ESlateVisibility`) = `HitTestInvisible`

## Graphs

- Event graph: `EventGraph` (47 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_0` (`CanvasPanel`)
  - `CanvasPanel_50` (`CanvasPanel`) via CanvasPanelSlot
    - `Background` (`Image`) [variable] via CanvasPanelSlot
    - `HorizontalBox_57` (`HorizontalBox`) via CanvasPanelSlot
      - `TempText` (`TextBlock`) [variable] via HorizontalBoxSlot

## References

Hard refs out (11):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Engine/EngineFonts/DroidSansMono` [asset]
- `/Engine/EngineFonts/Roboto` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Temperature_Sample_Location` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_TemperatureType` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Actor_Weather_Status` [asset]
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

