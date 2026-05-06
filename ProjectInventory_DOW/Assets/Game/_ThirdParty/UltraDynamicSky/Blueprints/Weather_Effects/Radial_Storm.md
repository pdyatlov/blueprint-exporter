# Radial_Storm

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Radial_Storm.Radial_Storm` |
| Asset name | `Radial_Storm` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces (5):
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_CloudPaintActor_Interface.UDS_CloudPaintActor_Interface_C`
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArray_ManagedActor.UDS_InterfaceActorArray_ManagedActor_C`
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Radial_Storm_Weather_Interface.Radial_Storm_Weather_Interface_C`
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Local_Weather_Actor_Interface.UDW_Local_Weather_Actor_Interface_C`
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WOVTarget_Draw_Actor_Interface.UDW_WOVTarget_Draw_Actor_Interface_C`

## Variables (47)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Storm Weather` | `object<UDS_Weather_Settings_C>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Thunderstorm.Rain_Thunderstorm'` | `Basic Controls` | Replicated | — | InstanceEditable |
| `Outer Radius` | `real<double>` | `400000.000000` | `Basic Controls` | Replicated | — | InstanceEditable |
| `Inner Radius Fraction` | `real<double>` | `0.400000` | `Basic Controls` | Replicated | — | InstanceEditable |
| `Cloud Altitude Offset` | `real<double>` | `0.000000` | `Basic Controls` | — | — | InstanceEditable |
| `UDS` | `object<Ultra_Dynamic_Sky_C>` | `None` | `System` | — | — | InstanceEditable, Private |
| `UDW` | `object<Ultra_Dynamic_Weather_C>` | `None` | `System` | — | — | InstanceEditable, Private |
| `Cloud Bottom Altitude` | `real<float>` | `0.000000` | `Hidden Exposed` | — | — | InstanceEditable |
| `Ground Level Offset` | `real<double>` | `0.000000` | `Basic Controls` | — | — | InstanceEditable |
| `Cloud Coverage RGB Curve` | `object<CurveVector>` | `/Script/Engine.CurveVector'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/CloudCoverage_RGB.CloudCoverage_RGB'` | `System` | — | — | InstanceEditable, Private |
| `Ambient Light Shadow Intensity` | `real<double>` | `0.500000` | `Visuals` | — | — | InstanceEditable |
| `Fog Sprites Opacity` | `real<double>` | `1.000000` | `Visuals` | — | — | InstanceEditable |
| `Storm Alpha` | `real<double>` | `1.000000` | `System` | — | — | InstanceEditable, Private |
| `UDS Ground Level` | `real<double>` | `0.000000` | `Hidden Exposed` | — | — | InstanceEditable |
| `Cylinder Height` | `real<double>` | `0.000000` | `System` | — | — | InstanceEditable, Private |
| `Enable Thunder Sound` | `bool` | `True` | `Sound Effects` | — | — | InstanceEditable |
| `Thunder Sounds Range (km)` | `real<double>` | `25.000000` | `Sound Effects` | — | — | InstanceEditable |
| `Thunder Sounds Volume Multiplier` | `real<double>` | `0.400000` | `Sound Effects` | — | — | InstanceEditable |
| `Fog Sprites Color Intensity` | `real<double>` | `1.000000` | `Visuals` | — | — | InstanceEditable |
| `Fog Sprites Color Saturation` | `real<double>` | `0.800000` | `Visuals` | — | — | InstanceEditable |
| `Effects Fade Distance (km)` | `real<double>` | `20.000000` | `Visuals` | — | — | InstanceEditable |
| `Fog Sprite Scale` | `real<double>` | `1.000000` | `Visuals` | — | — | InstanceEditable |
| `Fog Sprite Count` | `int` | `75` | `Visuals` | — | — | InstanceEditable |
| `Fog Sprites Render Behind Clouds` | `bool` | `False` | `Visuals` | — | — | InstanceEditable |
| `Fog Sprite Movement Speed` | `real<double>` | `1.000000` | `Visuals` | — | — | InstanceEditable |
| `Dust Fog Color Multiplier` | `struct<LinearColor>` | `(R=1.300000,G=0.698967,B=0.351000,A=1.000000)` | `Visuals` | — | — | InstanceEditable |
| `Lightning Spawn Rate` | `real<double>` | `0.700000` | `Visuals` | — | — | InstanceEditable |
| `Lightning Intensity` | `real<double>` | `1.000000` | `Visuals` | — | — | InstanceEditable |
| `Tick Interval` | `real<double>` | `0.100000` | `Animation` | — | — | InstanceEditable |
| `Alpha Update Threshold` | `real<double>` | `0.001500` | `Animation` | — | — | InstanceEditable |
| `Movement Update Fraction` | `real<double>` | `0.002500` | `Animation` | — | — | InstanceEditable |
| `Starting Location` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Animation` | — | — | InstanceEditable, Private |
| `Movement Target` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Animation` | — | — | InstanceEditable, Private |
| `Fade Speed` | `real<double>` | `0.000000` | `Animation` | — | — | InstanceEditable, Private |
| `Fading In` | `bool` | `False` | `Animation` | — | — | InstanceEditable, Private |
| `Fading Out` | `bool` | `False` | `Animation` | — | — | InstanceEditable, Private |
| `Moving` | `bool` | `False` | `Animation` | — | — | InstanceEditable, Private |
| `Movement Timer` | `struct<TimerHandle>` | `()` | `Animation` | — | — | InstanceEditable, Private |
| `Latent Fade Duration` | `real<double>` | `0.000000` | `Animation` | — | — | InstanceEditable, Private |
| `Move Duration` | `real<double>` | `0.000000` | `Animation` | — | — | InstanceEditable, Private |
| `Last Updated Alpha` | `real<double>` | `0.000000` | `Animation` | — | — | InstanceEditable, Private |
| `Last Updated Location` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Animation` | — | — | InstanceEditable, Private |
| `Last Tick Time` | `real<double>` | `0.000000` | `Animation` | — | — | InstanceEditable, Private |
| `Material Target Color` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=0.000000)` | `System` | — | — | InstanceEditable, Private |
| `Effects Visible` | `bool` | `False` | `System` | — | — | InstanceEditable, Private |
| `Apply Material State` | `bool` | `True` | `Basic Controls` | — | — | InstanceEditable |
| `Lightning Card Scale` | `real<double>` | `1.000000` | `Visuals` | — | — | InstanceEditable |
| `Priority` | `int` | `1` | `Basic Controls` | — | — | InstanceEditable |

## Functions (32)

### `Apply Effect to Cloud Coverage Value`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_CloudPaintActor_Interface.UDS_CloudPaintActor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Sample Location = 0, 0, 0, real<double>& Cloud Coverage = 0.0 [ref], real<double> Painted Opacity = 0.0)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 9

### `Apply Niagara Properties`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Rain/Snow Amount`
- Nodes: 102
- Category: `Startup`
- Description: Applies parameters for the niagara system, based on exposed settings and weather

### `Apply WOV State`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Local_Weather_Actor_Interface.UDW_Local_Weather_Actor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `(struct<UDW_WOV_State> State)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2

### `Bind Local Weather Update Function to UDW`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Local_Weather_Actor_Interface.UDW_Local_Weather_Actor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `(object<Ultra_Dynamic_Weather_C> UDW)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 4

### `Canvas Space Update`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WOVTarget_Draw_Actor_Interface.UDW_WOVTarget_Draw_Actor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector2D> Corner Position, real<double> Width = 0.0, int Resolution = 0)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2

### `Check Sky Mode for Visibility`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Update`

### `Check to Apply Animation Changes`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 24
- Category: `Animation`
- Description: Updates the alpha of the storm itself, and if past thresholds for movement/alpha changes, also updates the render targets affected by the storm on UDS and UDW

### `Check to Change Temperature Scale`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Local_Weather_Actor_Interface.UDW_Local_Weather_Actor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2

### `Configure Thunder Sound`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `Startup`
- Description: Configures the attenuation of the thunder sound component

### `Destroy`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `Fading`
- Description: Destroys the actor

### `Draw to Cloud Paint Target`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_CloudPaintActor_Interface.UDS_CloudPaintActor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `(object<Canvas> Canvas, object<MaterialInstanceDynamic> Radial Storm Draw MID, struct<Vector> Target Mapping = 0, 0, 0, int Target Res = 0, bool& Can Add Coverage = false [ref], bool& Can Subtract Coverage = false [ref], bool Cloud Painting Active = false)`
- Outputs: `(bool Success)`
- Local variables (1): `UDS Cloud Coverage Level`
- Nodes: 52

### `Draw to WOV Target`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WOVTarget_Draw_Actor_Interface.UDW_WOVTarget_Draw_Actor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_RenderTarget_State_C> WOV Render Target State, object<Canvas> Canvas, object<MaterialInstanceDynamic> WOV Target Brush MID, object<MaterialInstanceDynamic> Radial Storm Brush MID)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 26

### `End Movement`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9
- Category: `Animation`
- Description: Called when the timer for the "Move Storm Over Time" function completes

### `Fade in Storm`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Fade Duration = 100.000000)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 19
- Category: `Fading`
- Description: Fade the effects of the radial storm in over time

### `Fade Out Storm`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Fade Duration = 100.000000)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 17
- Category: `Fading`
- Description: Fade the effects of the radial storm out over time, and destroy the actor when complete

### `Full Reconstruction`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Local_Weather_Actor_Interface.UDW_Local_Weather_Actor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2

### `Get Alpha with Location`

- Access: `Protected`
- Flags: —
- Inputs: `(struct<Vector> Test Location)`
- Outputs: `(real<double> Alpha, real<double> Alpha)`
- Local variables (1): `Radial Storm Distance`
- Nodes: 20
- Category: `Weather Effect`

### `Get Priority`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArray_ManagedActor.UDS_InterfaceActorArray_ManagedActor_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(int Priority)`
- Local variables: _none_
- Nodes: 3

### `Get Saved WOV State`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Local_Weather_Actor_Interface.UDW_Local_Weather_Actor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Has Valid State, struct<UDW_WOV_State> State)`
- Local variables: _none_
- Nodes: 2

### `Get UDS and UDW`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Startup`
- Description: Gets reference to UDS and UDW actors, if present

### `Get WOV Random Weather Forecast`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Local_Weather_Actor_Interface.UDW_Local_Weather_Actor_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Player is Inside, TArray<object<UDS_Weather_Settings_C>> Array)`
- Local variables: _none_
- Nodes: 2

### `Include in Filtered Array`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArray_ManagedActor.UDS_InterfaceActorArray_ManagedActor_C`
- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Filtering Location = 0, 0, 0)`
- Outputs: `(bool Include)`
- Local variables: _none_
- Nodes: 2

### `Latent Fade Out`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Fading`
- Description: Used to start the Fade Out function at the end of a timer, for fading at the end of a movement.

### `Local State Update - Apply Radial Storm to Weather`

- Access: `Public`
- Flags: CallInEditor
- Inputs: `(object<UDS_Weather_Settings_C> Target State Object, struct<Vector> Local Weather Location)`
- Outputs: `()`
- Local variables (3): `Radial Storm Distance`, `Radial Storm Alpha`, `Unchanged Cloud Coverage`
- Nodes: 24
- Category: `Weather Effect`

### `Move Storm Over Time`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Target Location, real<double> Movement Duration = 300.000000, bool Fade Out by End of Movement, real<double> Fade Out Duration = 100.000000)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 27
- Category: `Animation`
- Description: Moves the storm to a new location, over time. Optionally can also fade the storm out and destroy it when it reaches the end of the movement path.

### `Refresh Targets`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Update`
- Description: Updates the cloud painting render target on UDS and the material effect render target on UDW

### `Second Frame Startup`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 24
- Category: `Startup`
- Description: Runs on the second frame after the storm is spawned

### `Set Storm Location`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Location)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Animation`
- Description: Sets the storm's location and if needed updates its effect on the clouds/weather

### `Start Ticking`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6
- Category: `Update`
- Description: Sets the actor tick to be enabled, and sets its interval to the exposed setting

### `Update Alpha`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 20
- Category: `Update`
- Description: Applies the storm alpha to the niagara effect and the thunder sound volume

### `Update Radius and Positions`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 47
- Category: `Update`
- Description: Sets locations and scales for the actor and meshes, with respect to the cloud layer altitude and the storm radius

### `📘 Radial Storm`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Basic Controls`

## Macros (0)

_None._

## Components (3)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`
  - `Inner Radius Wire` — `StaticMeshComponent` @ socket `None`
  - `Outer Radius Wire` — `StaticMeshComponent` @ socket `None`
  - `Niagara System` — `NiagaraComponent` @ socket `None`
  - `Thunder Sound` — `AudioComponent` @ socket `None`
- `UDS_InterfaceActorArray_Reporter` — `UDS_InterfaceActorArray_Reporter_C` @ socket `None`
- `UDS_Utility_Opener` — `UDS_Utility_Opener_C` @ socket `None`

## Class Default Object (8)

- `ActorLabel` (`FString`) = `Radial_Storm`
- `bAlwaysRelevant` (`uint8`) = `True`
- `bEnableAutoLODGeneration` (`uint8`) = `False`
- `bIsSpatiallyLoaded` (`uint8`) = `False`
- `bReplicateMovement` (`uint8`) = `True`
- `bReplicates` (`uint8`) = `True`
- `NetUpdateFrequency` (`float`) = `10.000000`
- `PrimaryActorTick` (`FActorTickFunction`) = `(bCanEverTick=True,bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (72 nodes)
- Construction script: `UserConstructionScript` (33 nodes)
- Additional graphs: _none_

## References

Hard refs out (30):
- `/Engine/EditorBlueprintResources/ActorMacros` [asset]
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Engine/EditorResources/AudioIcons/S_AudioComponent` [asset]
- `/Engine/EditorResources/AudioIcons/S_AudioComponent_AutoActivate` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_RunContext` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_SkyMode` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/RandomWeatherVariation_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_CloudPaintActor_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArray_ManagedActor` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArray_Reporter` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_RenderTarget_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/CloudCoverage_RGB` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Radial_Storm_Weather_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Local_Weather_Actor_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WeatherState_Structure` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WOV_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WOVTarget_Draw_Actor_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Thunderstorm` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Radial_Storm_Fog_Particle` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Radial_Storm_Fog_Particle_AboveClouds` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/Brush_Cylinder` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Particles/Radial_Storm` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Sound/MetaSounds/UDS_RadialStorm_Thunder` [asset]
- `/Script/Engine.Actor` [native]
- `/Script/Niagara` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

