# UDS_Onscreen_Controls

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Widgets/UDS_Onscreen_Controls.UDS_Onscreen_Controls` |
| Asset name | `UDS_Onscreen_Controls` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (18)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `UDS` | `object<Ultra_Dynamic_Sky_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Show Time Control` | `bool` | `True` | `Settings` | — | — | InstanceEditable |
| `Show Date Control` | `bool` | `True` | `Settings` | — | — | InstanceEditable |
| `Show Location Control` | `bool` | `True` | `Settings` | — | — | InstanceEditable |
| `Show Weather Control` | `bool` | `True` | `Settings` | — | — | InstanceEditable |
| `UDW` | `object<Ultra_Dynamic_Weather_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `24h Time` | `bool` | `False` | `Settings` | — | — | InstanceEditable |
| `Date Format` | `int` | `0` | `Settings` | — | — | InstanceEditable |
| `Time Zone Change Updates Time of Day` | `bool` | `False` | `Settings` | — | — | InstanceEditable |
| `Weather Change Transition Time` | `real<double>` | `3.000000` | `Settings` | — | — | InstanceEditable |
| `Available Weather Presets` | `TArray<object<UDS_Weather_Settings_C>>` | `("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Clear_Skies.Clear_Skies'","/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Partly_Cloudy.Partly_Cloudy'","/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Cloudy.Cloudy'","/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Overcast.Overcast'","/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Foggy.Foggy'","/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Light.Rain_Light'","/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain.Rain'","/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Thunderstorm.Rain_Thunderstorm'","/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Light.Snow_Light'","/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow.Snow'","/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Blizzard.Snow_Blizzard'","/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Sand_Dust_Calm.Sand_Dust_Calm'","/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Sand_Dust_Storm.Sand_Dust_Storm'")` | `Settings` | — | — | InstanceEditable |
| `Selected Weather Type Icon` | `object<UDS_Weather_Preset_Icon_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Show Custom Weather Dropdown` | `bool` | `True` | `Settings` | — | — | InstanceEditable |
| `Time Zone Time Adjustment` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Client Controller` | `object<UDS_Client_Controller_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Use Client Controller` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Allow Manual Slider Update` | `bool` | `True` | `Default` | — | — | InstanceEditable, Private |
| `Allow Hard Reset` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |

## Functions (14)

### `Apply Custom Weather`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 74

### `Check for Client Controller`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11

### `Generate Calendar Grid`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `X`, `Y`
- Nodes: 8

### `Generate Weather Content Widget`

- Access: `Public`
- Flags: —
- Inputs: `(name Item)`
- Outputs: `(object<Widget> ReturnValue)`
- Local variables: _none_
- Nodes: 4

### `Generate Weather Item Widget`

- Access: `Public`
- Flags: —
- Inputs: `(name Item)`
- Outputs: `(object<Widget> ReturnValue)`
- Local variables: _none_
- Nodes: 7

### `Generate Weather Types Dropdown`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7

### `Offset Time of Day`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Offset)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9

### `On_Map_MouseButtonDown_0`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Geometry> MyGeometry, struct<PointerEvent>& MouseEvent [ref])`
- Outputs: `(struct<EventReply> ReturnValue)`
- Local variables: _none_
- Nodes: 23

### `Order Date Widgets`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 36

### `PreConstruct Logic`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 33

### `Set Up City Dropdown`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13

### `Tick Widgets Controlled by UDS`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 181

### `UDS Hard Reset if Allowed`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

### `Update Map Point`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (4)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Desired`
- `DesignTimeSize` (`FVector2D`) = `(X=701.000000,Y=901.000000)`
- `PaletteCategory` (`FText`) = `NSLOCTEXT("", "292B69DD404CA87A4B29E288F97095D1", "Ultra Dynamic Sky Widgets")`

## Graphs

- Event graph: `EventGraph` (353 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_27` (`CanvasPanel`)
  - `CanvasPanel_371` (`CanvasPanel`) via CanvasPanelSlot
    - `BackgroundBlur_106` (`BackgroundBlur`) via CanvasPanelSlot
    - `Image_1004` (`Image`) [variable] via CanvasPanelSlot
    - `CanvasPanel_165` (`CanvasPanel`) via CanvasPanelSlot
      - `VerticalBox_82` (`VerticalBox`) via CanvasPanelSlot
        - `Spacer_286` (`Spacer`) via VerticalBoxSlot
        - `TimePanel` (`SizeBox`) [variable] via VerticalBoxSlot
          - `VerticalBox_103` (`VerticalBox`) via SizeBoxSlot
            - `HorizontalBox_0` (`HorizontalBox`) via VerticalBoxSlot
              - `Image_260` (`Image`) [variable] via HorizontalBoxSlot
              - `TextBlock_353` (`TextBlock`) via HorizontalBoxSlot
              - `Image` (`Image`) [variable] via HorizontalBoxSlot
            - `HorizontalBox_134` (`HorizontalBox`) via VerticalBoxSlot
              - `Time_SubtraceMinuteButton` (`Button`) [variable] via HorizontalBoxSlot
                - `TextBlock_3` (`TextBlock`) via ButtonSlot
              - `Time_SubtractHourButton` (`Button`) [variable] via HorizontalBoxSlot
                - `TextBlock_2` (`TextBlock`) via ButtonSlot
              - `UDS_Digital_Clock` (`UDS_Digital_Clock_C`) [variable] via HorizontalBoxSlot
              - `Time_AddHourButton` (`Button`) [variable] via HorizontalBoxSlot
                - `TextBlock` (`TextBlock`) via ButtonSlot
              - `Time_AddMinuteButton` (`Button`) [variable] via HorizontalBoxSlot
                - `TextBlock_1` (`TextBlock`) via ButtonSlot
            - `TimeofDaySlider` (`Slider`) [variable] via VerticalBoxSlot
        - `DatePanel` (`SizeBox`) [variable] via VerticalBoxSlot
          - `VerticalBox_0` (`VerticalBox`) via SizeBoxSlot
            - `HorizontalBox_1` (`HorizontalBox`) via VerticalBoxSlot
              - `Image_1` (`Image`) [variable] via HorizontalBoxSlot
              - `TextBlock_6` (`TextBlock`) via HorizontalBoxSlot
              - `Image_2` (`Image`) [variable] via HorizontalBoxSlot
            - `DateFormatBox` (`HorizontalBox`) [variable] via VerticalBoxSlot
              - `Month_Combobox` (`ComboBoxString`) [variable] via HorizontalBoxSlot
              - `DaySpinbox` (`SpinBox`) [variable] via HorizontalBoxSlot
              - `Year_Spinbox` (`SpinBox`) [variable] via HorizontalBoxSlot
        - `Location_Panel` (`SizeBox`) [variable] via VerticalBoxSlot
          - `VerticalBox_136` (`VerticalBox`) via SizeBoxSlot
            - `HorizontalBox_2` (`HorizontalBox`) via VerticalBoxSlot
              - `Image_3` (`Image`) [variable] via HorizontalBoxSlot
              - `TextBlock_7` (`TextBlock`) via HorizontalBoxSlot
              - `Image_4` (`Image`) [variable] via HorizontalBoxSlot
            - `HorizontalBox_192` (`HorizontalBox`) via VerticalBoxSlot
              - `TextBlock_183` (`TextBlock`) via HorizontalBoxSlot
              - `Latitude_Spinbox` (`SpinBox`) [variable] via HorizontalBoxSlot
              - `TextBlock_4` (`TextBlock`) via HorizontalBoxSlot
              - `Longitude_Spinbox` (`SpinBox`) [variable] via HorizontalBoxSlot
            - `Map_Panel` (`SizeBox`) [variable] via VerticalBoxSlot
              - `CanvasPanel_0` (`CanvasPanel`) via SizeBoxSlot
                - `Map` (`Image`) via CanvasPanelSlot
                - `Map_Point` (`Image`) [variable] via CanvasPanelSlot
                - `CanvasPanel_277` (`CanvasPanel`) via CanvasPanelSlot
                - `City_Combobox` (`ComboBoxString`) [variable] via CanvasPanelSlot
            - `ExpandMapButton` (`Button`) [variable] via VerticalBoxSlot
              - `Image_792` (`Image`) [variable] via ButtonSlot
            - `HorizontalBox` (`HorizontalBox`) via VerticalBoxSlot
              - `TextBlock_5` (`TextBlock`) via HorizontalBoxSlot
              - `Timezone_Spinbox` (`SpinBox`) [variable] via HorizontalBoxSlot
        - `UDS_Weather_Panel` (`SizeBox`) [variable] via VerticalBoxSlot
          - `VerticalBox_125` (`VerticalBox`) via SizeBoxSlot
            - `HorizontalBox_3` (`HorizontalBox`) via VerticalBoxSlot
              - `Image_5` (`Image`) [variable] via HorizontalBoxSlot
              - `TextBlock_8` (`TextBlock`) via HorizontalBoxSlot
              - `Image_6` (`Image`) [variable] via HorizontalBoxSlot
            - `HorizontalBox_4` (`HorizontalBox`) via VerticalBoxSlot
              - `Image_7` (`Image`) [variable] via HorizontalBoxSlot
              - `CloudCoverageSlider` (`Slider`) [variable] via HorizontalBoxSlot
              - `Image_531` (`Image`) [variable] via HorizontalBoxSlot
            - `HorizontalBox_5` (`HorizontalBox`) via VerticalBoxSlot
              - `Image_8` (`Image`) [variable] via HorizontalBoxSlot
              - `Fog_Slider` (`Slider`) [variable] via HorizontalBoxSlot
              - `Image_9` (`Image`) [variable] via HorizontalBoxSlot
        - `UDW_Weather_Panel` (`SizeBox`) [variable] via VerticalBoxSlot
          - `VerticalBox` (`VerticalBox`) via SizeBoxSlot
            - `HorizontalBox_6` (`HorizontalBox`) via VerticalBoxSlot
              - `Image_10` (`Image`) [variable] via HorizontalBoxSlot
              - `TextBlock_9` (`TextBlock`) via HorizontalBoxSlot
              - `Image_11` (`Image`) [variable] via HorizontalBoxSlot
            - `CanvasPanel_3` (`CanvasPanel`) via VerticalBoxSlot
              - `WeatherTypeCombobox` (`ComboBoxKey`) [variable] via CanvasPanelSlot
              - `CustomWeatherButton` (`Button`) [variable] via CanvasPanelSlot
                - `TextBlock_377` (`TextBlock`) via ButtonSlot
            - `Spacer_281` (`Spacer`) via VerticalBoxSlot
            - `Custom_Weather_Box` (`SizeBox`) via VerticalBoxSlot
              - `weather_settingsbox` (`VerticalBox`) [variable] via SizeBoxSlot
                - `HorizontalBox_131` (`HorizontalBox`) via VerticalBoxSlot
                  - `TextBlock_10` (`TextBlock`) via HorizontalBoxSlot
                  - `UDW_CloudCoverage_Slider` (`Slider`) [variable] via HorizontalBoxSlot
                - `Spacer_646` (`Spacer`) via VerticalBoxSlot
                - `HorizontalBox_8` (`HorizontalBox`) via VerticalBoxSlot
                  - `TextBlock_11` (`TextBlock`) via HorizontalBoxSlot
                  - `UDW_Fog_Slider` (`Slider`) [variable] via HorizontalBoxSlot
                - `Spacer` (`Spacer`) via VerticalBoxSlot
                - `HorizontalBox_9` (`HorizontalBox`) via VerticalBoxSlot
                  - `TextBlock_12` (`TextBlock`) via HorizontalBoxSlot
                  - `UDW_Rain_Slider` (`Slider`) [variable] via HorizontalBoxSlot
                - `Spacer_1` (`Spacer`) via VerticalBoxSlot
                - `HorizontalBox_10` (`HorizontalBox`) via VerticalBoxSlot
                  - `TextBlock_13` (`TextBlock`) via HorizontalBoxSlot
                  - `UDW_Snow_Slider` (`Slider`) [variable] via HorizontalBoxSlot
                - `Spacer_2` (`Spacer`) via VerticalBoxSlot
                - `HorizontalBox_11` (`HorizontalBox`) via VerticalBoxSlot
                  - `TextBlock_14` (`TextBlock`) via HorizontalBoxSlot
                  - `UDW_Dust_Slider` (`Slider`) [variable] via HorizontalBoxSlot
                - `Spacer_3` (`Spacer`) via VerticalBoxSlot
                - `HorizontalBox_12` (`HorizontalBox`) via VerticalBoxSlot
                  - `TextBlock_15` (`TextBlock`) via HorizontalBoxSlot
                  - `UDW_Wind_Slider` (`Slider`) [variable] via HorizontalBoxSlot
                - `Spacer_4` (`Spacer`) via VerticalBoxSlot
                - `HorizontalBox_13` (`HorizontalBox`) via VerticalBoxSlot
                  - `TextBlock_16` (`TextBlock`) via HorizontalBoxSlot
                  - `UDW_Thunder_Slider` (`Slider`) [variable] via HorizontalBoxSlot

## References

Hard refs out (35):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Engine/EngineFonts/Roboto` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_CityPresets` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Calendar` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Utilities/UDS_Client_Controller` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Preset_Icon` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Clear_Skies` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Cloudy` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Foggy` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Overcast` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Partly_Cloudy` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Light` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Thunderstorm` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Sand_Dust_Calm` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Sand_Dust_Storm` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Blizzard` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Light` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Widgets/UDS_Digital_Clock` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Fog_Icon` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Full_CloudPaint_Icon` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Globe_Icon` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Zero_CloudPaint_Icon` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Widgets/Earth_Map` [asset]
- `/Script/MovieScene` [asset]
- `/Script/MovieSceneTracks` [asset]
- `/Script/Slate` [asset]
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

