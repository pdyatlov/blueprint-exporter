# Weather_Override_Volume

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Override_Volume.Weather_Override_Volume` |
| Asset name | `Weather_Override_Volume` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces (4):
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArray_ManagedActor.UDS_InterfaceActorArray_ManagedActor_C`
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_and_Weather_Override_Volume_Interface.UDW_and_Weather_Override_Volume_Interface_C`
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Local_Weather_Actor_Interface.UDW_Local_Weather_Actor_Interface_C`
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WOVTarget_Draw_Actor_Interface.UDW_WOVTarget_Draw_Actor_Interface_C`

## Variables (45)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Weather` | `object<UDS_Weather_Settings_C>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain.Rain'` | `Basic Controls` | Replicated | `OnRep_Weather` | InstanceEditable |
| `Transition Width` | `real<double>` | `20000.000000` | `Basic Controls` | — | — | InstanceEditable |
| `Priority` | `int` | `0` | `Basic Controls` | — | — | InstanceEditable |
| `Volume Alpha` | `real<double>` | `1.000000` | `Basic Controls` | Replicated | `OnRep_Volume Alpha` | InstanceEditable |
| `Scaled Transition Width` | `real<double>` | `0.000000` | `System` | — | — | InstanceEditable, Private |
| `UDW` | `object<Ultra_Dynamic_Weather_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Random Weather Variation` | `byte<UDS_RandomWeatherTiming>` | `NewEnumerator3` | `Random Weather Variation` | Replicated | `OnRep_Random Weather Variation` | InstanceEditable |
| `Apply Climate Preset` | `object<UDS_Climate_Preset_C>` | `None` | `Random Weather Variation` | — | — | InstanceEditable |
| `Weather Type Probabilities (Spring)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `(("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Blizzard.Snow_Blizzard'", 0.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Clear_Skies.Clear_Skies'", 0.700000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Cloudy.Cloudy'", 1.300000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Foggy.Foggy'", 0.350000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Light.Rain_Light'", 1.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Light.Snow_Light'", 0.350000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Overcast.Overcast'", 0.800000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Partly_Cloudy.Partly_Cloudy'", 1.400000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain.Rain'", 1.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow.Snow'", 0.200000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Thunderstorm.Rain_Thunderstorm'", 0.800000))` | `Random Weather Variation` | — | — | InstanceEditable |
| `Weather Type Probabilities (Summer)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `(("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Blizzard.Snow_Blizzard'", 0.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Clear_Skies.Clear_Skies'", 0.700000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Cloudy.Cloudy'", 1.200000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Foggy.Foggy'", 0.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Light.Rain_Light'", 1.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Light.Snow_Light'", 0.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Overcast.Overcast'", 0.700000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Partly_Cloudy.Partly_Cloudy'", 1.400000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain.Rain'", 1.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow.Snow'", 0.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Thunderstorm.Rain_Thunderstorm'", 0.800000))` | `Random Weather Variation` | — | — | InstanceEditable |
| `Weather Type Probabilities (Autumn)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `(("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Blizzard.Snow_Blizzard'", 0.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Clear_Skies.Clear_Skies'", 0.300000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Cloudy.Cloudy'", 1.200000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Foggy.Foggy'", 0.500000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Light.Rain_Light'", 1.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Light.Snow_Light'", 0.250000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Overcast.Overcast'", 1.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Partly_Cloudy.Partly_Cloudy'", 1.400000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain.Rain'", 1.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow.Snow'", 0.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Thunderstorm.Rain_Thunderstorm'", 0.800000))` | `Random Weather Variation` | — | — | InstanceEditable |
| `Weather Type Probabilities (Winter)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `(("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Blizzard.Snow_Blizzard'", 0.800000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Clear_Skies.Clear_Skies'", 0.100000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Cloudy.Cloudy'", 1.300000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Foggy.Foggy'", 0.350000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Light.Rain_Light'", 0.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Light.Snow_Light'", 1.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Overcast.Overcast'", 1.200000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Partly_Cloudy.Partly_Cloudy'", 1.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain.Rain'", 0.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow.Snow'", 1.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Thunderstorm.Rain_Thunderstorm'", 0.000000))` | `Random Weather Variation` | — | — | InstanceEditable |
| `Total Sphere Bounds` | `real<double>` | `0.000000` | `System` | — | — | InstanceEditable, Private |
| `Spline Bounds Center` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `System` | — | — | InstanceEditable, Private |
| `Show Weather Label in Editor` | `bool` | `True` | `Basic Controls` | — | — | InstanceEditable |
| `Weather State` | `object<UDS_Weather_Settings_C>` | `None` | `Hidden Exposed` | — | — | InstanceEditable |
| `World Space Triangles` | `TArray<struct<Vector>>` | — | `Volume Drawing` | — | — | InstanceEditable, Private |
| `Canvas Scale Factor` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Volume Drawing` | — | — | InstanceEditable, Private |
| `Canvas Offset` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Volume Drawing` | — | — | InstanceEditable, Private |
| `Volume Color` | `struct<LinearColor>` | `(R=0.325483,G=1.000000,B=0.031642,A=1.000000)` | `System` | — | — | InstanceEditable, Private |
| `Canvas Space Triangles` | `TArray<struct<CanvasUVTri>>` | — | `Volume Drawing` | — | — | InstanceEditable, Private |
| `Started` | `bool` | `False` | `System` | — | — | InstanceEditable, Private |
| `Material State Buffer` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Volume Drawing` | — | — | InstanceEditable, Private |
| `Transitioning Weather` | `bool` | `False` | `Transition` | — | — | InstanceEditable, Private |
| `Transition Weather A` | `object<UDS_Weather_Settings_C>` | `None` | `Transition` | — | — | InstanceEditable, Private |
| `Transition Weather B` | `object<UDS_Weather_Settings_C>` | `None` | `Transition` | — | — | InstanceEditable, Private |
| `Transition Time Elapsed` | `real<double>` | `0.000000` | `Transition` | Replicated (COND_InitialOnly) | — | InstanceEditable, Private |
| `Transition Timer Length` | `real<double>` | `0.000000` | `Transition` | Replicated | `OnRep_Transition Timer Length` | InstanceEditable, Private |
| `Random Weather Label Text` | `string` | `Random` | `Random Weather Variation` | — | — | InstanceEditable |
| `Runtime Spline Points` | `TArray<struct<Vector>>` | — | `System` | Replicated | — | InstanceEditable |
| `Apply Wind Direction` | `bool` | `False` | `Basic Controls` | — | — | InstanceEditable |
| `Wind Direction` | `real<double>` | `180.000000` | `Basic Controls` | — | — | InstanceEditable |
| `Erase Other WOVs` | `bool` | `False` | `Basic Controls` | — | — | InstanceEditable |
| `Apply Temperature Ranges` | `bool` | `True` | `Temperature` | — | — | InstanceEditable |
| `Summer Temperature Min and Max` | `struct<Vector2D>` | `(X=55.000000,Y=80.000000)` | `Temperature` | — | — | InstanceEditable |
| `Autumn Temperature Min and Max` | `struct<Vector2D>` | `(X=40.000000,Y=70.000000)` | `Temperature` | — | — | InstanceEditable |
| `Winter Temperature Min and Max` | `struct<Vector2D>` | `(X=20.000000,Y=55.000000)` | `Temperature` | — | — | InstanceEditable |
| `Spring Temperature Min and Max` | `struct<Vector2D>` | `(X=30.000000,Y=65.000000)` | `Temperature` | — | — | InstanceEditable |
| `Temperature Scale` | `byte<UDS_TemperatureType>` | `NewEnumerator0` | `System` | — | — | InstanceEditable |
| `Material State Needs Check` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Apply Material State` | `bool` | `True` | `Basic Controls` | — | — | InstanceEditable |
| `Apply Height Falloff` | `bool` | `False` | `Basic Controls` | — | — | InstanceEditable |
| `Height Falloff` | `real<double>` | `10000.000000` | `Basic Controls` | — | — | InstanceEditable |
| `Player is In Volume` | `bool` | `False` | `System` | — | — | InstanceEditable, Private |
| `Tick Delta Seconds` | `real<float>` | `0.000000` | `System` | — | — | InstanceEditable, Private |

## Functions (48)

### `Add Quad`

- Access: `Protected`
- Flags: —
- Inputs: `(struct<Vector> Vert 1, struct<Vector> Vert 2, struct<Vector> Vert 3, struct<Vector> Vert 4)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 19
- Category: `Volume Drawing`

### `Add Triangle`

- Access: `Protected`
- Flags: —
- Inputs: `(struct<Vector> Vert 1, struct<Vector> Vert 2, struct<Vector> Vert 3)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10
- Category: `Volume Drawing`

### `Apply Climate Preset Object`

- Access: `Protected`
- Flags: —
- Inputs: `(object<UDS_Climate_Preset_C> Climate Preset)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 32
- Category: `Editor`

### `Apply Transition State B`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9
- Category: `Update`

### `Apply WOV State`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Local_Weather_Actor_Interface.UDW_Local_Weather_Actor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `(struct<UDW_WOV_State> State)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 51

### `Bind Local Weather Update Function to UDW`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Local_Weather_Actor_Interface.UDW_Local_Weather_Actor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `(object<Ultra_Dynamic_Weather_C> UDW)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 4

### `Calculate Spline Bounds`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Bounds`
- Nodes: 25
- Category: `Spline`

### `Canvas Space Update`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WOVTarget_Draw_Actor_Interface.UDW_WOVTarget_Draw_Actor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector2D> Corner Position, real<double> Width = 0.0, int Resolution = 0)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 32

### `Check for Changing Material State to Request Target Redraw`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 20
- Category: `Volume Drawing`

### `Check to Change Temperature Scale`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Local_Weather_Actor_Interface.UDW_Local_Weather_Actor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 52

### `Construct Editor Only Weather Labels`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `Label`, `Text Component`
- Nodes: 53
- Category: `Editor`

### `Construct Weather State Objects`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9
- Category: `Construct`

### `Create Canvas Space Triangles`

- Access: `Protected`
- Flags: —
- Inputs: `(struct<Vector2D> Corner Position, real<double> Width, int Resolution)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 29
- Category: `Volume Drawing`

### `Create World Space Drawing Geometry`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (12): `Loop Vertices`, `Middle Loop Verts`, `Outer Loop Verts`, `Inner Loop Verts`, `Point A Distance`, `Point B Distance`, `Current Vert`, `Next Vert`, `Vertex IDs`, `Vertex Instance IDs`, `Edge IDs`, `2D Inner Loop`
- Nodes: 86
- Category: `Volume Drawing`

### `Custom Volume Behavior`

- Access: `Protected`
- Flags: —
- Inputs: `(real<double> Alpha, object<Ultra_Dynamic_Sky_C> UDS, object<Ultra_Dynamic_Weather_C> UDW)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1
- Category: `Weather Effect`
- Description: An empty function which is run by UDW when generating local weather using WOV actors in the level. You could override this function in a child class of the Weather Override Volume, to give the actor additional behavior besides adjusting weather. The input "Alpha" represents how far into the WOV the player is. 0 is completely outside, 1 is completely inside.

### `Disable Volume`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `Utilities`
- Description: Disable this WOV's effect on weather and material effects. Use the Enable Volume function to turn it back on.

### `Draw to WOV Target`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WOVTarget_Draw_Actor_Interface.UDW_WOVTarget_Draw_Actor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_RenderTarget_State_C> WOV Render Target State, object<Canvas> Canvas, object<MaterialInstanceDynamic> WOV Target Brush MID, object<MaterialInstanceDynamic> Radial Storm Brush MID)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 25

### `Edge to Point Sign F`

- Access: `Protected`
- Flags: —
- Inputs: `(struct<Vector2D> Point, struct<Vector2D> E1, struct<Vector2D> E2)`
- Outputs: `(bool Positive)`
- Local variables: _none_
- Nodes: 13
- Category: `Volume Drawing`

### `Enable Volume`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `Utilities`
- Description: Enable this WOV's effect, if previously disabled

### `Full Reconstruction`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Local_Weather_Actor_Interface.UDW_Local_Weather_Actor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 3

### `Get Next Random Weather and Timer Length`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_and_Weather_Override_Volume_Interface.UDW_and_Weather_Override_Volume_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `(object<Random_Weather_Variation_C> Random Weather Component)`
- Outputs: `(object<UDS_Weather_Settings_C> Next Preset, real<double> Timer Length)`
- Local variables: _none_
- Nodes: 2

### `Get Priority`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArray_ManagedActor.UDS_InterfaceActorArray_ManagedActor_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(int Priority)`
- Local variables: _none_
- Nodes: 5

### `Get Random Weather Mode`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_and_Weather_Override_Volume_Interface.UDW_and_Weather_Override_Volume_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte Mode)`
- Local variables: _none_
- Nodes: 3

### `Get Random Weather Probability Maps`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_and_Weather_Override_Volume_Interface.UDW_and_Weather_Override_Volume_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(TMap<object<UDS_Weather_Settings_C,>>, real> Spring, TMap<object<UDS_Weather_Settings_C,>>, real> Summer, TMap<object<UDS_Weather_Settings_C,>>, real> Autumn, TMap<object<UDS_Weather_Settings_C,>>, real> Winter)`
- Local variables: _none_
- Nodes: 6

### `Get Saved WOV State`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Local_Weather_Actor_Interface.UDW_Local_Weather_Actor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Has Valid State, struct<UDW_WOV_State> State)`
- Local variables: _none_
- Nodes: 14

### `Get Scaled Transition Width`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 6
- Category: `Spline`

### `Get Season Temperature Ranges`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_and_Weather_Override_Volume_Interface.UDW_and_Weather_Override_Volume_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector2D> Spring, struct<Vector2D> Summer, struct<Vector2D> Autumn, struct<Vector2D> Winter)`
- Local variables: _none_
- Nodes: 6

### `Get WOV Random Weather Forecast`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Local_Weather_Actor_Interface.UDW_Local_Weather_Actor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Player is Inside, TArray<object<UDS_Weather_Settings_C>> Array)`
- Local variables: _none_
- Nodes: 5

### `Include in Filtered Array`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArray_ManagedActor.UDS_InterfaceActorArray_ManagedActor_C`
- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Filtering Location = 0, 0, 0)`
- Outputs: `(bool Include)`
- Local variables: _none_
- Nodes: 9

### `Increment Material State`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8
- Category: `Weather Effect`

### `Initialize Random Weather Component`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13
- Category: `Random Weather`

### `Initialize Spline Data`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Spline Points`
- Nodes: 47
- Category: `Spline`

### `Is Point In Triangle`

- Access: `Protected`
- Flags: —
- Inputs: `(struct<Vector2D> Point, struct<Vector2D> V1, struct<Vector2D> V2, struct<Vector2D> V3)`
- Outputs: `(bool Yes)`
- Local variables: _none_
- Nodes: 19
- Category: `Volume Drawing`

### `Local State Update - Apply WOV to State`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(object<UDS_Weather_Settings_C> Target State Object, struct<Vector> Local Weather Location)`
- Outputs: `()`
- Local variables (1): `WOV Alpha`
- Nodes: 59
- Category: `Weather Effect`

### `Sample Point for Current Alpha`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Location)`
- Outputs: `(real<double> Alpha, real<double> Material Alpha, real<double> Alpha, real<double> Material Alpha)`
- Local variables (1): `Alpha without Height Falloff`
- Nodes: 45
- Category: `Weather Effect`
- Description: Takes in a location in world space and sees how much this volume will affect it, from 0 to 1.

### `Scale And Place Vertex in Canvas Space`

- Access: `Protected`
- Flags: —
- Inputs: `(struct<Vector> In)`
- Outputs: `(struct<Vector2D> Pos, struct<LinearColor> Color)`
- Local variables: _none_
- Nodes: 9
- Category: `Volume Drawing`

### `Shut Down WOV`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `End Play`

### `Start Up WOV`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 44
- Category: `Startup`

### `Tick Function`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15
- Category: `Update`

### `Triangulate Polygon`

- Access: `Protected`
- Flags: —
- Inputs: `(TArray<struct<Vector2D>> Vertices (Clockwise))`
- Outputs: `()`
- Local variables (9): `Remaining Verts`, `Current Index`, `Current Vertex`, `Last Vertex`, `Next Vertex`, `Triangle Indexes`, `Triangle Contains Vertex`, `Max Iterations`, `Iterations`
- Nodes: 106
- Category: `Volume Drawing`

### `UDW End Play`

- Access: `Protected`
- Flags: —
- Inputs: `(object<Actor> Actor, byte EndPlayReason = Destroyed)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `End Play`

### `Update Material State Buffer`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Volume Drawing`

### `Update Random Weather`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 18
- Category: `Update`

### `Update Tick Enabled`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8
- Category: `Update`

### `Update Tick Interval`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Update`

### `Update Volume Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13
- Category: `Volume Drawing`

### `Update Weather Transition`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Eased Alpha`
- Nodes: 34
- Category: `Update`

### `📘 Weather Override Volumes`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Basic Controls`

## Macros (2)

### `Edge to Point Sign`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13

### `Label Color`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14

## Components (6)

- `Billboard` — `BillboardComponent` @ socket `None`
  - `Spline` — `SplineComponent` @ socket `None`
- `Random Weather Manager` — `Random_Weather_Variation_C` @ socket `None`
- `Temperature Manager` — `UDW_Temperature_Manager_C` @ socket `None`
- `Material State Manager` — `UDW_Material_State_Manager_C` @ socket `None`
- `UDS_InterfaceActorArray_Reporter` — `UDS_InterfaceActorArray_Reporter_C` @ socket `None`
- `UDS_Utility_Opener` — `UDS_Utility_Opener_C` @ socket `None`

## Class Default Object (7)

- `ActorLabel` (`FString`) = `Weather_Settings_Override_Volume-1`
- `bAlwaysRelevant` (`uint8`) = `True`
- `bEnableAutoLODGeneration` (`uint8`) = `False`
- `bIsSpatiallyLoaded` (`uint8`) = `False`
- `bReplicates` (`uint8`) = `True`
- `NetUpdateFrequency` (`float`) = `10.000000`
- `PrimaryActorTick` (`FActorTickFunction`) = `(bCanEverTick=True,bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (103 nodes)
- Construction script: `UserConstructionScript` (13 nodes)
- Additional graphs: _none_

## References

Hard refs out (37):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_RandomWeatherTiming` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_TemperatureType` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Functions/UltraDynamicSky_Functions` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/RandomWeatherVariation_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArray_ManagedActor` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArray_Reporter` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_RenderTarget_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Random_Weather_Variation` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Climate_Preset` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_and_Weather_Override_Volume_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Local_Weather_Actor_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Material_State_Manager` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Temperature_Manager` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Temperature_Manager_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WeatherState_Structure` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WOV_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WOVTarget_Draw_Actor_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Clear_Skies` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Cloudy` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Foggy` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Overcast` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Partly_Cloudy` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Light` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Thunderstorm` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Blizzard` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Light` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather_Override_Volume` [asset]
- `/Script/Engine.Actor` [native]
- `/Script/MeshDescription` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

