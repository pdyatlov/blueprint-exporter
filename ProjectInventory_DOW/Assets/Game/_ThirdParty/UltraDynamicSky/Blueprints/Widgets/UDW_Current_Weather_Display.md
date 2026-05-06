# UDW_Current_Weather_Display

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Widgets/UDW_Current_Weather_Display.UDW_Current_Weather_Display` |
| Asset name | `UDW_Current_Weather_Display` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (11)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Show Text Instead of Icon` | `bool` | `False` | `Weather Display Settings` | — | — | InstanceEditable |
| `UDW` | `object<Ultra_Dynamic_Weather_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Calculate Displayed Weather Type from State Values` | `bool` | `True` | `Weather Display Settings` | — | — | InstanceEditable |
| `Icon Size` | `real<double>` | `80.000000` | `Weather Display Settings` | — | — | InstanceEditable |
| `Weather Icons by Display Name Enum` | `TMap<byte<Texture2D>>, :/Script/Engine.Texture2D>` | `((NewEnumerator14, "/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Overcast.Overcast'"),(NewEnumerator13, "/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Cloudy.Cloudy'"),(NewEnumerator12, "/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/PartlyCloudy.PartlyCloudy'"),(NewEnumerator11, "/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Clear_Skies.Clear_Skies'"),(NewEnumerator10, "/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Foggy.Foggy'"),(NewEnumerator9, "/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Dust.Dust'"),(NewEnumerator8, "/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/DustStorm.DustStorm'"),(NewEnumerator7, "/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Blizzard.Blizzard'"),(NewEnumerator6, "/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Snow.Snow'"),(NewEnumerator5, "/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Snow.Snow'"),(NewEnumerator4, "/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Light_Snow.Light_Snow'"),(NewEnumerator3, "/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Thunderstorms.Thunderstorms'"),(NewEnumerator2, "/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Rain.Rain'"),(NewEnumerator1, "/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Rain.Rain'"),(NewEnumerator0, "/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/LightRain.LightRain'"))` | `Weather Display Settings` | — | — | InstanceEditable |
| `Text Font` | `struct<SlateFontInfo>` | `(FontObject="/Script/Engine.Font'/Engine/EngineFonts/Roboto.Roboto'",OutlineSettings=(OutlineColor=(R=0.000000,G=0.000000,B=0.000000,A=1.000000)),TypefaceFontName="Regular",Size=13.500000,MonospacedWidth=1.000000)` | `Weather Display Settings` | — | — | InstanceEditable |
| `Text Color` | `struct<LinearColor>` | `(R=0.828125,G=0.828125,B=0.828125,A=1.000000)` | `Weather Display Settings` | — | — | InstanceEditable |
| `Text Min Desired Width` | `real<double>` | `145.000000` | `Weather Display Settings` | — | — | InstanceEditable |
| `Show Background` | `bool` | `True` | `Weather Display Settings` | — | — | InstanceEditable |
| `Background Color` | `struct<LinearColor>` | `(R=0.027321,G=0.027321,B=0.027321,A=1.000000)` | `Weather Display Settings` | — | — | InstanceEditable |
| `Update Display Period` | `real<double>` | `1.000000` | `Weather Display Settings` | — | — | InstanceEditable |

## Functions (1)

### `Update Current Display`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `Display Text`, `Display Icon`
- Nodes: 40

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (4)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Desired`
- `PaletteCategory` (`FText`) = `NSLOCTEXT("", "4A0F92B4494EBAAF02573FB388C9BC40", "Ultra Dynamic Sky Widgets")`

## Graphs

- Event graph: `EventGraph` (55 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_0` (`CanvasPanel`)
  - `Border` (`Border`) [variable] via CanvasPanelSlot
    - `CanvasPanel_147` (`CanvasPanel`) via BorderSlot
      - `IconImage` (`Image`) [variable] via CanvasPanelSlot
      - `LabelText` (`TextBlock`) [variable] via CanvasPanelSlot

## References

Hard refs out (24):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Engine/EngineFonts/Roboto` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_RunContext` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Weather_Display_Names` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Blizzard` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Clear_Skies` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Cloudy` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Dust` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/DustStorm` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Foggy` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Light_Snow` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/LightRain` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Overcast` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/PartlyCloudy` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Rain` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Snow` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Thunderstorms` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Weather_Icon_BG` [asset]
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

