# UltraDynamicSky_Functions

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Functions/UltraDynamicSky_Functions.UltraDynamicSky_Functions` |
| Asset name | `UltraDynamicSky_Functions` |
| Subclass | `Blueprint` |
| Blueprint type | `FunctionLibrary` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `BlueprintFunctionLibrary` (`/Script/Engine.BlueprintFunctionLibrary`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (17)

### `Apply Saved UDS and UDW State · 𝖴𝖣𝖲`

- Access: `Public`
- Flags: —
- Inputs: `(struct<UDS_and_UDW_State> State, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Ultra Dynamic Sky`
- Description: Takes a packaged state (created using "Create UDS and UDW State for Saving" and applies its contents to UDS, and UDW if one is in the scene.

### `Apply Sky Configuration · 𝖴𝖣𝖲`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Sky_Configuration_C> Configuration, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `Ultra Dynamic Sky`
- Description: Call to apply a full configuration of all the exposed settings on UDS. Created using the Configuration Manager utility. Understand this necessarily restarts the entire system as if it is returning to begin play.

### `Create UDS and UDW State for Saving · 𝖴𝖣𝖲`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(struct<UDS_and_UDW_State> Packaged State, struct<UDS_and_UDW_State> Packaged State)`
- Local variables: _none_
- Nodes: 7
- Category: `Ultra Dynamic Sky`
- Description: Outputs the state of dynamics like time and weather, to be saved with a save file or between levels. To load the data, use the function "Apply Saved UDS and UDW State". Note, this function doesn't pack together every single variable on the blueprints, only the typical dynamic ones which would make sense to include in save data.

### `Get DateTime · 𝖴𝖣𝖲`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(struct<DateTime> DateTime, struct<DateTime> DateTime)`
- Local variables: _none_
- Nodes: 8
- Category: `Ultra Dynamic Sky`
- Description: Outputs the date and time on Ultra Dynamic Sky, as a DateTime structure

### `Get Day of the Week · 𝖴𝖣𝖲`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(int Index, string Name, int Index, string Name)`
- Local variables: _none_
- Nodes: 7
- Category: `Ultra Dynamic Sky`
- Description: Outputs the day of the week on Ultra Dynamic Sky, using its date and selected Calendar asset.

### `Get Time of Day · 𝖴𝖣𝖲`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(real<double> Time of Day, real<double> Time of Day)`
- Local variables: _none_
- Nodes: 7
- Category: `Ultra Dynamic Sky`
- Description: Outputs the current Time of Day value on Ultra Dynamic Sky (0-2400)

### `Get TimeCode · 𝖴𝖣𝖲`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(struct<Timecode> TimeCode, struct<Timecode> TimeCode)`
- Local variables: _none_
- Nodes: 8
- Category: `Ultra Dynamic Sky`
- Description: Outputs the time on Ultra Dynamic Sky, as a timecode structure

### `Get Ultra Dynamic Sky`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(object<Ultra_Dynamic_Sky_C> UDS, bool Valid)`
- Local variables: _none_
- Nodes: 4
- Category: `Ultra Dynamic Sky`
- Description: Outputs a reference to the UDS actor in the level, if one exists.

### `Is It Daytime? · 𝖴𝖣𝖲`

- Access: `Public`
- Flags: —
- Inputs: `(object<Object> __WorldContext)`
- Outputs: `(bool Daytime, bool Daytime)`
- Local variables: _none_
- Nodes: 8
- Category: `Ultra Dynamic Sky`
- Description: Outputs true if the sun on Ultra Dynamic Sky is above the horizon

### `Lerp Yaw Angles`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Angle A, real<double> Angle B, real<double> Alpha, object<Object> __WorldContext)`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 20
- Category: `Utilities`
- Description: Used to lerp from one angle to another, in degrees,. without errors

### `Offset Time by Time Span · 𝖴𝖣𝖲`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Timespan> Timespan, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Ultra Dynamic Sky`
- Description: Moves Time of Day and date values forward or backward using a Time Span struct.

### `Offset Time of Day by Hours · 𝖴𝖣𝖲`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Hours, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Ultra Dynamic Sky`
- Description: Moves Time of Day forward or backward by a number of hours. Positive values are forward, negative values are backward. Date values will be affected if moving to a different day.

### `Random Value in Float Range Structure`

- Access: `Public`
- Flags: —
- Inputs: `(struct<FloatRange> Range, struct<RandomStream> Stream, object<Object> __WorldContext)`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 6
- Category: `Utilities`
- Description: Finds a random value within the range of a Float Range structure.

### `Set Date and Time · 𝖴𝖣𝖲`

- Access: `Public`
- Flags: —
- Inputs: `(struct<DateTime> DateTime, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `Ultra Dynamic Sky`
- Description: Set the current Date and Time of Day values on Ultra Dynamic Sky, using a DateTime structure

### `Set Time of Day · 𝖴𝖣𝖲`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Time of Day, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `Ultra Dynamic Sky`
- Description: Sets the Time of Day variable on Ultra Dynamic Sky, if one exists in the level

### `Set Time with Time Code · 𝖴𝖣𝖲`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Timecode> TimeCode, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `Ultra Dynamic Sky`
- Description: Sets the current Time of Day on Ultra Dynamic Sky, using a Time Code structure

### `Transition Time of Day · 𝖴𝖣𝖲`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> New Time of Day = 1200.000000, real<double> Transition Duration (Seconds) = 10.000000, byte Easing Function = EaseInOut, real<double> Easing Exponent = 2.000000, bool Allow Time Going Backwards, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Ultra Dynamic Sky`
- Description: Starts Time of Day on Ultra Dynamic Sky animating to a new value, over a supplied transition duration.

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

Hard refs out (7):
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/RandomWeatherVariation_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_and_UDW_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_DateAndTime` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Sky_Configuration` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WeatherState_Structure` [asset]
- `/Script/Engine.BlueprintFunctionLibrary` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `FunctionLibrary`
- Subclass: `Blueprint`
- Custom metadata: _none_

