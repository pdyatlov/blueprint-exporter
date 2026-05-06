# UltraDynamicWeather_Functions

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Functions/UltraDynamicWeather_Functions.UltraDynamicWeather_Functions` |
| Asset name | `UltraDynamicWeather_Functions` |
| Subclass | `Blueprint` |
| Blueprint type | `FunctionLibrary` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `BlueprintFunctionLibrary` (`/Script/Engine.BlueprintFunctionLibrary`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (22)

### `Apply Weather Configuration · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Weather_Configuration_C> Configuration, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `Ultra Dynamic Weather`
- Description: Call to apply a full configuration of all the exposed settings on UDW at runtime. Created using the Configuration Manager utility. Understand this necessarily restarts the entire system as if it is returning to begin play.

### `Change to Random Weather Variation · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Time to Transition to Random Weather (Seconds) = 200.000000, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Ultra Dynamic Weather`
- Description: Changes the global weather state on Ultra Dynamic Weather over to the random weather variation system. Can transition to the random state over Time to Transition, or instantly change if Time to Transition is 0.

### `Change Weather · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Weather_Settings_C> New Weather Type, real<double> Time To Transition To New Weather (Seconds) = 200.000000, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Ultra Dynamic Weather`
- Description: Changes the global weather state on Ultra Dynamic Weather to a new weather settings preset. Can transition smoothly to the new state over Time to Transition, or instantly if Time to Transition is 0.

### `Change Wind Direction · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> New Wind Direction, real<double> Change Duration, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Ultra Dynamic Weather`
- Description: Once called, the wind direction on UDW will start transitioning to a new value over a transition duration. Note this is the global wind direction defined in Basic Controls on UDW. This won't take priority over Weather Override Volumes which control wind direction.

### `Flash Lightning · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(bool Use Custom Lightning Location = false, struct<Vector> Custom Lightning Location, struct<Vector> Custom Target Location, int Lightning Bolt Seed = -1, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Ultra Dynamic Weather`
- Description: Manually spawn in a lightning flash on Ultra Dynamic Weather. Replicates to clients if called on the server.

### `Get Cloud Coverage · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(real<double> Cloud Coverage, real<double> Cloud Coverage)`
- Local variables: _none_
- Nodes: 7
- Category: `Ultra Dynamic Weather`
- Description: Outputs the Cloud Coverage value from the local weather state on Ultra Dynamic Weather

### `Get Current Temperature · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(byte Sample Location = NewEnumerator0, struct<Vector> Custom Sample Location, byte Scale = NewEnumerator0, object<Object> __WorldContext)`
- Outputs: `(real<double> Temperature, real<double> Temperature)`
- Local variables: _none_
- Nodes: 7
- Category: `Ultra Dynamic Weather`
- Description: Uses the values in the Temperature category on UDW to determine a temperature using the current time and weather. Sample Location determines if localized effects are applied, like the Interior Temperature and Temperature Volumes. Read the tooltip for each option for more info.

### `Get Display Name for Current Weather · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(string As String, byte As Enumerator, string As String, byte As Enumerator)`
- Local variables: _none_
- Nodes: 6
- Category: `Ultra Dynamic Weather`
- Description: Finds a descriptor for the current weather state on Ultra Dynamic Weather. Note, this is not directly related to the weather settings objects informing the current state. For example, if the weather is transitioning from Clear Skies to Overcast, this function will not output either of those states in the middle of that transition. Instead, it would output something reasonable for the in between state like Partly Cloudy.

### `Get Dust/Sand Amount · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(real<double> Dust, real<double> Dust)`
- Local variables: _none_
- Nodes: 7
- Category: `Ultra Dynamic Weather`
- Description: Outputs the Dust value from the local weather state on Ultra Dynamic Weather

### `Get Fog · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(real<double> Fog, real<double> Fog)`
- Local variables: _none_
- Nodes: 7
- Category: `Ultra Dynamic Weather`
- Description: Outputs the Fog value from the local weather state on Ultra Dynamic Weather

### `Get Local Weather State · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(object<UDS_Weather_Settings_C> Local Weather State, object<UDS_Weather_Settings_C> Local Weather State)`
- Local variables: _none_
- Nodes: 6
- Category: `Ultra Dynamic Weather`
- Description: Outputs the Local Weather State object on Ultra Dynamic Weather. This holds the weather state values for the currently displayed weather

### `Get Material Dust Coverage · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(real<double> Material Dust Coverage, real<double> Material Dust Coverage)`
- Local variables: _none_
- Nodes: 7
- Category: `Ultra Dynamic Weather`
- Description: Outputs the Material Dust Coverage value from the local weather state on Ultra Dynamic Weather

### `Get Material Snow Coverage · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(real<double> Material Snow Coverage, real<double> Material Snow Coverage)`
- Local variables: _none_
- Nodes: 7
- Category: `Ultra Dynamic Weather`
- Description: Outputs the Material Snow Coverage value from the local weather state on Ultra Dynamic Weather

### `Get Material Wetness · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(real<double> Material Wetness, real<double> Material Wetness)`
- Local variables: _none_
- Nodes: 7
- Category: `Ultra Dynamic Weather`
- Description: Outputs the Material Wetness value from the local weather state on Ultra Dynamic Weather

### `Get Rain Amount · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(real<double> Rain, real<double> Rain)`
- Local variables: _none_
- Nodes: 7
- Category: `Ultra Dynamic Weather`
- Description: Outputs the Rain value from the local weather state on Ultra Dynamic Weather

### `Get Season · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(real<double> Season, byte Season Enum, real<double> Season, byte Season Enum)`
- Local variables: _none_
- Nodes: 6
- Category: `Ultra Dynamic Weather`
- Description: Gets the Season float value and the current season (from the floored value) as an enum

### `Get Snow Amount · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(real<double> Snow, real<double> Snow)`
- Local variables: _none_
- Nodes: 7
- Category: `Ultra Dynamic Weather`
- Description: Outputs the Snow value from the local weather state on Ultra Dynamic Weather

### `Get Thunder/Lightning · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(real<double> Thunder/Lightning, real<double> Thunder/Lightning)`
- Local variables: _none_
- Nodes: 7
- Category: `Ultra Dynamic Weather`
- Description: Outputs the Thunder/Lightning value from the local weather state on Ultra Dynamic Weather

### `Get Ultra Dynamic Weather`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(object<Ultra_Dynamic_Weather_C> UDW, bool Valid)`
- Local variables: _none_
- Nodes: 4
- Category: `Ultra Dynamic Weather`
- Description: Outputs a reference to the UDW actor in the level, if one exists.

### `Get Wind Direction Vector · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(struct<Vector> Wind Direction, struct<Vector> Wind Direction)`
- Local variables: _none_
- Nodes: 6
- Category: `Ultra Dynamic Weather`
- Description: Outputs a unit vector pointing in the direction of the current wind on Ultra Dynamic Weather

### `Get Wind Intensity · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(real<double> Wind Intensity, real<double> Wind Intensity)`
- Local variables: _none_
- Nodes: 7
- Category: `Ultra Dynamic Weather`
- Description: Outputs the Wind Intensity value from the local weather state on Ultra Dynamic Weather

### `Get Wind Speed in Real Units · 𝖴𝖣𝖶`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Knots at Wind Intensity 10 = 38.000000, bool Factor Wind Gusts, object<Object> __WorldContext)`
- Outputs: `(real<double> Knots, real<double> MPH, real<double> KPH, real<double> Knots, real<double> MPH, real<double> KPH)`
- Local variables: _none_
- Nodes: 6
- Category: `Ultra Dynamic Weather`
- Description: Gets the wind speed from UDW approximated as real world units (knots, MPH, KPH) The input Knots at Wind Intensity 10 can be used to recalibrate this calculation higher or lower, if you've configured wind forces and effects to represent a different level of wind at a Wind Intensity value of 10. The input Factor Wind Gusts applies the wind gust multiplier. See the documentation on Wind Gusts for information on that.

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (10):
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_RandomWeatherTiming` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Season` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Temperature_Sample_Location` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_TemperatureType` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Weather_Display_Names` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Weather_Configuration` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Clear_Skies` [asset]
- `/Script/Engine.BlueprintFunctionLibrary` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `FunctionLibrary`
- Subclass: `Blueprint`
- Custom metadata: _none_

