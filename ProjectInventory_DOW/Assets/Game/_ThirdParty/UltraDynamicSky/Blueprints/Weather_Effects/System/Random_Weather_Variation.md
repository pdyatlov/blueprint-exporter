# Random_Weather_Variation

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Random_Weather_Variation.Random_Weather_Variation` |
| Asset name | `Random_Weather_Variation` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ActorComponent` (`/Script/Engine.ActorComponent`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (19)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `UDW` | `object<Actor>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `UDS` | `object<Ultra_Dynamic_Sky_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Target Random Weather Type` | `object<UDS_Weather_Settings_C>` | `None` | `Default` | Replicated | — | InstanceEditable, Private |
| `Last Random Weather Type` | `object<UDS_Weather_Settings_C>` | `None` | `Default` | Replicated | — | InstanceEditable, Private |
| `Current Lerp Alpha` | `real<double>` | `0.000000` | `Default` | Replicated (COND_InitialOnly) | — | InstanceEditable, Private |
| `Current Timer Length` | `real<double>` | `-1.000000` | `Default` | Replicated | — | InstanceEditable, Private |
| `Owner Actor` | `object<Actor>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Current Random Weather State` | `object<UDS_Weather_Settings_C>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Cloudy.Cloudy'` | `Default` | — | — | InstanceEditable, Private |
| `Change Timer` | `real<double>` | `0.000000` | `Default` | Replicated (COND_InitialOnly) | — | InstanceEditable, Private |
| `Started` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Changing Weather` | `bool` | `True` | `Default` | — | — | InstanceEditable, Private |
| `Weather Forecast` | `TArray<object<UDS_Weather_Settings_C>>` | — | `Default` | Replicated | — | InstanceEditable, Private |
| `Random Forecast Steps` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `Transition Length` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Random Weather Change Hour` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `Weather Speed` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Tick Delta Seconds` | `real<float>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Weather Forecast Times` | `TArray<real<double>>` | — | `Default` | Replicated | — | InstanceEditable, Private |
| `Force Changing` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |

## Functions (20)

### `Apply State`

- Access: `Public`
- Flags: —
- Inputs: `(struct<RandomWeatherVariation_State> Random Weather State)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 37
- Category: `Saving/ Loading`

### `Bind to UDS`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Startup`
- Description: Binds to event dispatchers on UDS, for the Daily/Hourly modes

### `Change to Next Random Weather Type`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (3): `Random Max Range`, `Random Float`, `Threshold`
- Nodes: 29
- Category: `Random Changes`
- Description: Selects the next random type and starts transitioning to it.

### `Check For Client Startup`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9
- Category: `System`

### `Check For Season Instant Refresh`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12
- Category: `Time`

### `Clear and Restart`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8
- Category: `System`
- Description: Clears the current random weather and restarts with a new type

### `Current Hour Changed`

- Access: `Protected`
- Flags: —
- Inputs: `(int Hour)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Time`
- Description: Bound to the dispatcher on UDS, for handling the Hourly timing mode

### `Fill Weather Forecast`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (3): `Last Step Weather`, `Current Probabilities`, `Previous Target`
- Nodes: 18
- Category: `Forecast`
- Description: Fills the weather forecast array out to its requested size

### `Get Climate Temperature Ranges`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Climate_Preset_C> Climate Object, byte Scale = NewEnumerator0)`
- Outputs: `(struct<Vector2D> Summer Range, struct<Vector2D> Autumn Range, struct<Vector2D> Winter Range, struct<Vector2D> Spring Range)`
- Local variables: _none_
- Nodes: 10
- Category: `Climate`
- Description: Returns the temperature ranges stored in a climate preset asset

### `Get Current Lerp Alpha`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue, real<double> ReturnValue, real<double> ReturnValue, real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 45
- Category: `Tick`
- Description: Finds the alpha from the last weather to the target weather, depending on the timing mode.

### `Get Season Probability Map`

- Access: `Public`
- Flags: —
- Inputs: `(int Season)`
- Outputs: `(TMap<object<UDS_Weather_Settings_C,>>, real> Map)`
- Local variables: _none_
- Nodes: 6
- Category: `Time`
- Description: Outputs a season's probablility map, either from UDS or the WOV actor this component exists on

### `Get State for Saving`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<RandomWeatherVariation_State> State, struct<RandomWeatherVariation_State> State)`
- Local variables: _none_
- Nodes: 16
- Category: `Saving/Loading`

### `Hourly`

- Access: `Protected`
- Flags: —
- Inputs: `(int Hour)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11
- Category: `Time`
- Description: Bound to the dispatcher on UDS, for handling the Daily mode

### `Increment Change Timer`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 16
- Category: `Tick`
- Description: For Random Interval timing, increments the timer and selects new weather when it reaches the timer length

### `Increment Random Weather`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `Eased Alpha`, `New Changing State`
- Nodes: 38
- Category: `Tick`
- Description: Gets the current random weather state, as a result of the blend of the last and the target states

### `Make Climate Probability Map`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Climate_Preset_C> Climate, int Season)`
- Outputs: `(TMap<object<UDS_Weather_Settings_C,>>, real> Probability Map)`
- Local variables (17): `High Temp (C)`, `Low Temp (C)`, `Rainfall (mm)`, `Snowfall (mm)`, `Cloudy Percentage`, `Sunny Percentage`, `Precipitating Percentage`, `Current Type Probability`, `Weather Probability Map`, `Current Type`, `Raining Percentage`, `Snowing Percentage`, `Allocation Fraction`, `Remaining Allocation Percentage`, `Precipitation Types`, `Current Precipitation Percentage`, `Probability Total`
- Nodes: 229
- Category: `Climate`
- Description: Synthesizes a random weather probability map, by interpreting the climate data from one of the climate preset objects.

### `Recalculate Forecast`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Forecast`
- Description: Clears the forecasted weather array and fills it with newly selected types.

### `Start Up Random Weather Variation`

- Access: `Public`
- Flags: —
- Inputs: `(object<Actor> UDW, object<Actor> Owner Actor, bool Start with a Random Type, object<UDS_Weather_Settings_C> Starting Weather Settings, int Random Forecast Steps, real<double> Transition Length, int Random Weather Change Hour)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 37
- Category: `Startup`
- Description: Called by UDW or Weather Override Volumes, to start the component generating a random weather state

### `Tick`

- Access: `Public`
- Flags: —
- Inputs: `(real<float> Tick Delta Seconds)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Tick`

### `Unbind from UDS`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Startup`
- Description: Binds to event dispatchers on UDS, for the Daily/Hourly modes

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (2)

- `bReplicates` (`uint8`) = `True`
- `PrimaryComponentTick` (`FActorComponentTickFunction`) = `(bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (9 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (24):
- `/Engine/EditorBlueprintResources/ActorComponentMacros` [asset]
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_RandomWeatherTiming` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_TemperatureType` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/RandomWeatherVariation_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Climate_Preset` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_and_Weather_Override_Volume_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface` [asset]
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
- `/Script/Engine.ActorComponent` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

