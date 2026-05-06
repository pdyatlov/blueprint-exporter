# Ultra_Dynamic_Weather

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather.Ultra_Dynamic_Weather` |
| Asset name | `Ultra_Dynamic_Weather` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces (3):
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArrayOwner_Interface.UDS_InterfaceActorArrayOwner_Interface_C`
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_and_Weather_Override_Volume_Interface.UDW_and_Weather_Override_Volume_Interface_C`
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface_C`

## Variables (557)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `UltraDynamicSky` | `object<Ultra_Dynamic_Sky_C>` | `None` | `Hidden Exposed` | — | — | InstanceEditable |
| `Refresh Settings` | `bool` | `False` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Weather` | `object<UDS_Weather_Settings_C>` | `None` | `𝙰𝟷  ·  Basic Controls` | Replicated | `OnRep_Weather` | InstanceEditable, ExposeToCinematics |
| `Cloud Coverage` | `real<double>` | `7.500000` | `𝙱𝟷  ·  Manual Weather State` | Replicated | — | InstanceEditable, ExposeToCinematics |
| `Cloud Coverage - Manual Override` | `bool` | `False` | `𝙱𝟷  ·  Manual Weather State` | Replicated | `OnRep_Cloud Coverage - Manual Override` | InstanceEditable |
| `Rain` | `real<double>` | `0.000000` | `𝙱𝟷  ·  Manual Weather State` | Replicated | — | InstanceEditable, ExposeToCinematics |
| `Rain - Manual Override` | `bool` | `False` | `𝙱𝟷  ·  Manual Weather State` | Replicated | `OnRep_Rain - Manual Override` | InstanceEditable |
| `Snow` | `real<double>` | `0.000000` | `𝙱𝟷  ·  Manual Weather State` | Replicated | — | InstanceEditable, ExposeToCinematics |
| `Snow - Manual Override` | `bool` | `False` | `𝙱𝟷  ·  Manual Weather State` | Replicated | `OnRep_Snow - Manual Override` | InstanceEditable |
| `Thunder/Lightning` | `real<double>` | `0.000000` | `𝙱𝟷  ·  Manual Weather State` | Replicated | `OnRep_Thunder/Lightning` | InstanceEditable, ExposeToCinematics |
| `Thunder/Lightning - Manual Override` | `bool` | `False` | `𝙱𝟷  ·  Manual Weather State` | Replicated | `OnRep_Thunder/Lightning - Manual Override` | InstanceEditable |
| `Wind Intensity` | `real<double>` | `2.000000` | `𝙱𝟷  ·  Manual Weather State` | Replicated | `OnRep_Wind Intensity` | InstanceEditable, ExposeToCinematics |
| `Wind Intensity - Manual Override` | `bool` | `False` | `𝙱𝟷  ·  Manual Weather State` | Replicated | `OnRep_Wind Intensity - Manual Override` | InstanceEditable |
| `Fog` | `real<double>` | `3.000000` | `𝙱𝟷  ·  Manual Weather State` | Replicated | `OnRep_Fog` | InstanceEditable, ExposeToCinematics |
| `Fog - Manual Override` | `bool` | `False` | `𝙱𝟷  ·  Manual Weather State` | Replicated | `OnRep_Fog - Manual Override` | InstanceEditable |
| `Dust` | `real<double>` | `0.000000` | `𝙱𝟷  ·  Manual Weather State` | Replicated | `OnRep_Dust` | InstanceEditable, ExposeToCinematics |
| `Dust - Manual Override` | `bool` | `False` | `𝙱𝟷  ·  Manual Weather State` | Replicated | `OnRep_Dust - Manual Override` | InstanceEditable |
| `Material Wetness` | `real<double>` | `0.000000` | `𝙱𝟷  ·  Manual Weather State` | Replicated | `OnRep_Material Wetness` | InstanceEditable, ExposeToCinematics |
| `Material Wetness - Manual Override` | `bool` | `False` | `𝙱𝟷  ·  Manual Weather State` | Replicated | `OnRep_Material Wetness - Manual Override` | InstanceEditable |
| `Material Snow Coverage` | `real<double>` | `0.000000` | `𝙱𝟷  ·  Manual Weather State` | Replicated | `OnRep_Material Snow Coverage` | InstanceEditable, ExposeToCinematics |
| `Material Snow Coverage - Manual Override` | `bool` | `False` | `𝙱𝟷  ·  Manual Weather State` | Replicated | `OnRep_Material Snow Coverage - Manual Override` | InstanceEditable |
| `Material Dust Coverage` | `real<double>` | `0.000000` | `𝙱𝟷  ·  Manual Weather State` | Replicated | `OnRep_Material Dust Coverage` | InstanceEditable, ExposeToCinematics |
| `Material Dust Coverage - Manual Override` | `bool` | `False` | `𝙱𝟷  ·  Manual Weather State` | Replicated | `OnRep_Material Dust Coverage - Manual Override` | InstanceEditable |
| `Wind Direction` | `real<double>` | `180.000000` | `𝙰𝟷  ·  Basic Controls` | Replicated | — | InstanceEditable, ExposeToCinematics |
| `Transition Duration` | `real<double>` | `-1.000000` | `Transition System` | Replicated | — | InstanceEditable, Private |
| `Transition Timer` | `real<double>` | `0.000000` | `Transition System` | Replicated (COND_InitialOnly) | — | InstanceEditable, Private |
| `Particle Collision Mode` | `byte<UDS_Particle_Collision_Mode>` | `NewEnumerator0` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `Ceiling Check Height` | `real<double>` | `8000.000000` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `Spawn Direction Forward Bias` | `real<double>` | `0.900000` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `Spawn Box Height` | `real<double>` | `600.000000` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `Max Spawn Distance` | `real<double>` | `2000.000000` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `Spawn Distance Distribution` | `real<double>` | `1.000000` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `Minimum Particle Distance` | `real<double>` | `45.000000` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `World Spawn Offset` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `Camera Forward Spawn Offset` | `real<double>` | `50.000000` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `Use UDS Water Level` | `bool` | `False` | `𝙹𝟷  ·  Water Level` | — | — | InstanceEditable, ReadOnly |
| `Weather Particle Collision Channel` | `byte<ECollisionChannel>` | `ECC_Visibility` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `Enable Rain Particles` | `bool` | `True` | `𝙲𝟷  ·  Rain Particles` | Replicated (COND_OwnerOnly) | `OnRep_Enable Rain Particles` | InstanceEditable |
| `Rain Particle Spawn Count` | `real<double>` | `20000.000000` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Rain Drops Scale` | `real<double>` | `1.000000` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Rain Wind Velocity` | `real<double>` | `1800.000000` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Rain Velocity Randomization` | `real<double>` | `1.000000` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Rain Particle Color Multiplier` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Rain Drops Alpha` | `real<double>` | `1.000000` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Rain Refraction Intensity` | `real<double>` | `1.000000` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Rain Extra Ambient Light` | `real<double>` | `0.000000` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Rain Light Sparkle` | `real<double>` | `3.000000` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Rain Particles Time Dilation` | `real<double>` | `1.000000` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Splash Particles Rendering Mode` | `byte<UDS_Rain_Splash_RenderMode>` | `NewEnumerator0` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Splash Frequency` | `real<double>` | `1.000000` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Splash Particles Scale` | `real<double>` | `1.000000` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Splash Droplets Scale` | `real<double>` | `1.000000` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Splash Particles Alpha` | `real<double>` | `1.000000` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Splash Minimum Facing Normal` | `real<double>` | `0.020000` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Max Duplicate Splash Range` | `real<double>` | `22.000000` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Rain Ripple Normal Decals` | `bool` | `True` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Render Raindrop Decals` | `bool` | `True` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Raindrop Decal Scale` | `real<double>` | `1.000000` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable |
| `Enable Snow Particles` | `bool` | `True` | `𝙲𝟸  ·  Snow Particles` | Replicated (COND_OwnerOnly) | `OnRep_Enable Snow Particles` | InstanceEditable |
| `Snow Particle Spawn Count` | `real<double>` | `20000.000000` | `𝙲𝟸  ·  Snow Particles` | — | — | InstanceEditable |
| `Snow Flakes Scale` | `real<double>` | `1.000000` | `𝙲𝟸  ·  Snow Particles` | — | — | InstanceEditable |
| `Snow Wind Velocity` | `real<double>` | `1500.000000` | `𝙲𝟸  ·  Snow Particles` | — | — | InstanceEditable |
| `Snow Velocity Randomization` | `real<double>` | `1.000000` | `𝙲𝟸  ·  Snow Particles` | — | — | InstanceEditable |
| `Snow Flakes Alpha` | `real<double>` | `1.000000` | `𝙲𝟸  ·  Snow Particles` | — | — | InstanceEditable |
| `Snow Extra Ambient Light` | `real<double>` | `0.000000` | `𝙲𝟸  ·  Snow Particles` | — | — | InstanceEditable |
| `Snow Flakes Surface Stick Duration` | `real<double>` | `1.500000` | `𝙲𝟸  ·  Snow Particles` | — | — | InstanceEditable |
| `Snow Particles Time Dilation` | `real<double>` | `1.000000` | `𝙲𝟸  ·  Snow Particles` | — | — | InstanceEditable |
| `Snow Particle Color Multiplier` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `𝙲𝟸  ·  Snow Particles` | — | — | InstanceEditable |
| `Spawn Lightning Flashes` | `bool` | `True` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable |
| `Lightning Flash Frequency` | `real<double>` | `14.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable |
| `Lightning Flash Timing Randomization` | `real<double>` | `1.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, ExposeToCinematics |
| `Lightning Effect Tint Color` | `struct<LinearColor>` | `(R=0.311279,G=0.439230,B=0.703125,A=1.000000)` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable |
| `Lightning Intensity Ambient Light Scale` | `real<double>` | `35.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable |
| `Daytime Lightning Flash Intensity` | `real<double>` | `1.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable |
| `Nighttime Lightning Flash Intensity` | `real<double>` | `1.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable |
| `Lightning Flash Light Source` | `bool` | `True` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, ExposeToCinematics |
| `Lightning Flash Light Source Color` | `struct<LinearColor>` | `(R=0.495000,G=0.612833,B=1.000000,A=1.000000)` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable |
| `Lightning Flash Light Intensity` | `real<double>` | `5.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, ExposeToCinematics |
| `Lightning Flashes Cast Shadows` | `bool` | `True` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable |
| `Stationary Lightning Light` | `bool` | `False` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable |
| `Stationary Lightning Light Yaw` | `real<double>` | `0.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable |
| `Stationary Lightning Light Height` | `real<double>` | `20.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable |
| `Lightning Flash Light Bloom` | `byte<UDS_LightningBloomMode>` | `NewEnumerator1` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable |
| `Lightning Flash Light Bloom Intensity` | `real<double>` | `2.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, ExposeToCinematics |
| `Lightning Flash Distance Range` | `struct<FloatRange>` | `(LowerBound=(Value=155000.000000),UpperBound=(Value=650000.000000))` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable |
| `Lightning Flash Duration` | `struct<FloatRange>` | `(LowerBound=(Value=1.750000),UpperBound=(Value=2.200000))` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable |
| `Lightning Height Offset` | `real<double>` | `0.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, ExposeToCinematics |
| `Lightning Bolt Length` | `real<double>` | `75000.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, ExposeToCinematics |
| `Lightning Bolt Thickness Scale` | `real<double>` | `1.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable |
| `Replicate Lightning Direction` | `bool` | `False` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, ExposeToCinematics |
| `Enable Lightning Flashes Striking Actors` | `bool` | `False` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable |
| `Fraction of Lightning Flashes Which Can Strike Actors` | `real<double>` | `0.250000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable |
| `Enable Obscured Lightning` | `bool` | `True` | `𝙴𝟷  ·  Lightning` | Replicated (COND_OwnerOnly) | `OnRep_Enable Obscured Lightning` | InstanceEditable |
| `Obscured Lightning Spawn Rate` | `real<double>` | `2.500000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, ExposeToCinematics |
| `Enable Wind Directional Source` | `bool` | `True` | `𝙷𝟺  ·  Wind Directional Source` | — | — | InstanceEditable |
| `Max Material Wetness` | `real<double>` | `1.000000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Max Material Snow Coverage` | `real<double>` | `1.000000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Max Dust Coverage` | `real<double>` | `0.500000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Material Snow Color` | `struct<LinearColor>` | `(R=0.900000,G=0.900000,B=0.900000,A=8.000000)` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable |
| `Material Dust Color` | `struct<LinearColor>` | `(R=0.260417,G=0.235053,B=0.191244,A=3.600000)` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable |
| `Snow/Dust Wind Direction Shift` | `real<double>` | `0.300000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable |
| `Material Water Roughness` | `real<double>` | `0.040000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable |
| `Tiling Water Ripples Scale` | `real<double>` | `250.000000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Tiling Water Ripples Framerate` | `real<double>` | `30.000000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable |
| `Simulate Changing Material State Over Time` | `bool` | `True` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Wetness Coverage Duration` | `real<double>` | `20.000000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Wetness Dry Duration` | `real<double>` | `90.000000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Wetness Dry Speed in Sunlight` | `real<double>` | `1.000000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Wetness Dry Speed without Sunlight` | `real<double>` | `0.300000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Snow Coverage Duration` | `real<double>` | `60.000000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Snow Melt Duration` | `real<double>` | `90.000000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Snow Melt Speed Above Freezing` | `real<double>` | `1.000000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable |
| `Snow Melt Speed Below Freezing` | `real<double>` | `1.000000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable |
| `Dust Coverage Duration` | `real<double>` | `30.000000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Dust Clear Duration` | `real<double>` | `90.000000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Dust Clear Speed when Windy` | `real<double>` | `1.500000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Dust Clear Speed when Calm` | `real<double>` | `0.500000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Melted Snow Coverage Contributes to Wetness` | `real<double>` | `0.750000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Snow Coverage Lights Up Height Fog` | `real<double>` | `1.000000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Wind Force Scale` | `real<double>` | `2000.000000` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Random Weather Variation` | `byte<UDS_RandomWeatherTiming>` | `NewEnumerator3` | `𝙳𝟸  ·  Random Weather Variation` | — | — | InstanceEditable |
| `Random Weather Change Interval` | `struct<FloatRange>` | `(LowerBound=(Value=200.000000),UpperBound=(Value=300.000000))` | `𝙳𝟸  ·  Random Weather Variation` | — | — | InstanceEditable |
| `Random Weather Change Hour` | `int` | `8` | `𝙳𝟸  ·  Random Weather Variation` | — | — | InstanceEditable |
| `Transition Length` | `real<double>` | `0.350000` | `𝙳𝟸  ·  Random Weather Variation` | — | — | InstanceEditable, ExposeToCinematics |
| `Begin Play Weather is Random` | `bool` | `False` | `𝙳𝟸  ·  Random Weather Variation` | — | — | InstanceEditable |
| `Apply Climate Preset` | `object<UDS_Climate_Preset_C>` | `None` | `𝙳𝟸  ·  Random Weather Variation` | — | — | InstanceEditable |
| `Weather Type Probabilities (Spring)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `(("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Clear_Skies.Clear_Skies'", 0.700000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Cloudy.Cloudy'", 1.300000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Foggy.Foggy'", 0.350000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Light.Rain_Light'", 1.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Light.Snow_Light'", 0.350000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Overcast.Overcast'", 0.800000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Partly_Cloudy.Partly_Cloudy'", 1.400000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain.Rain'", 1.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow.Snow'", 0.200000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Thunderstorm.Rain_Thunderstorm'", 0.800000))` | `𝙳𝟸  ·  Random Weather Variation` | — | — | InstanceEditable |
| `Weather Type Probabilities (Summer)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `(("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Clear_Skies.Clear_Skies'", 0.700000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Cloudy.Cloudy'", 1.200000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Foggy.Foggy'", 0.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Light.Rain_Light'", 1.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Light.Snow_Light'", 0.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Overcast.Overcast'", 0.700000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Partly_Cloudy.Partly_Cloudy'", 1.400000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain.Rain'", 1.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Thunderstorm.Rain_Thunderstorm'", 0.800000))` | `𝙳𝟸  ·  Random Weather Variation` | — | — | InstanceEditable |
| `Weather Type Probabilities (Autumn)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `(("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Clear_Skies.Clear_Skies'", 0.300000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Cloudy.Cloudy'", 1.200000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Foggy.Foggy'", 0.500000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Light.Rain_Light'", 1.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Light.Snow_Light'", 0.250000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Overcast.Overcast'", 1.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Partly_Cloudy.Partly_Cloudy'", 1.400000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain.Rain'", 1.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Thunderstorm.Rain_Thunderstorm'", 0.800000))` | `𝙳𝟸  ·  Random Weather Variation` | — | — | InstanceEditable |
| `Weather Type Probabilities (Winter)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `(("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Blizzard.Snow_Blizzard'", 0.800000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Clear_Skies.Clear_Skies'", 0.100000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Cloudy.Cloudy'", 1.300000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Foggy.Foggy'", 0.350000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Light.Snow_Light'", 1.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Overcast.Overcast'", 1.200000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Partly_Cloudy.Partly_Cloudy'", 1.000000),("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow.Snow'", 1.000000))` | `𝙳𝟸  ·  Random Weather Variation` | — | — | InstanceEditable |
| `Random Weather Forecast Steps` | `int` | `0` | `𝙳𝟸  ·  Random Weather Variation` | — | — | InstanceEditable |
| `Blend Season Probabilities` | `bool` | `True` | `𝙳𝟸  ·  Random Weather Variation` | — | — | InstanceEditable, ExposeToCinematics |
| `Avoid Extreme Cloud Coverage Shifts` | `bool` | `True` | `𝙳𝟸  ·  Random Weather Variation` | — | — | InstanceEditable, ExposeToCinematics |
| `Avoid Repeating Weather Types` | `bool` | `False` | `𝙳𝟸  ·  Random Weather Variation` | — | — | InstanceEditable, ExposeToCinematics |
| `Avoid Changing Directly from Snow to Rain (Or Vice Versa)` | `bool` | `True` | `𝙳𝟸  ·  Random Weather Variation` | — | — | InstanceEditable, ExposeToCinematics |
| `Weather Specific Interval Multipliers` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `()` | `𝙳𝟸  ·  Random Weather Variation` | — | — | InstanceEditable |
| `Extreme Cloud Coverage Shift Theshold` | `real<double>` | `6.000000` | `𝙳𝟸  ·  Random Weather Variation` | — | — | InstanceEditable, ExposeToCinematics |
| `Enable Weather Sound Effects` | `bool` | `True` | `𝙶𝟷  ·  Sound Effects` | Replicated (COND_OwnerOnly) | `OnRep_Enable Weather Sound Effects` | InstanceEditable |
| `Weather Sounds Master Volume` | `real<double>` | `1.000000` | `𝙶𝟷  ·  Sound Effects` | Replicated (COND_OwnerOnly) | `OnRep_Weather Sounds Master Volume` | InstanceEditable |
| `Rain Volume` | `real<double>` | `1.000000` | `𝙶𝟷  ·  Sound Effects` | Replicated (COND_OwnerOnly) | `OnRep_Rain Volume` | InstanceEditable, ExposeToCinematics |
| `Distant Thunder Volume` | `real<double>` | `1.000000` | `𝙶𝟷  ·  Sound Effects` | Replicated (COND_OwnerOnly) | `OnRep_Distant Thunder Volume` | InstanceEditable, ExposeToCinematics |
| `Close Thunder Volume` | `real<double>` | `1.000000` | `𝙶𝟷  ·  Sound Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Close Thunder Delay Per KM` | `real<double>` | `0.150000` | `𝙶𝟷  ·  Sound Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Wind Volume` | `real<double>` | `1.000000` | `𝙶𝟷  ·  Sound Effects` | Replicated (COND_OwnerOnly) | `OnRep_Wind Volume` | InstanceEditable, ExposeToCinematics |
| `Wind Whistling Volume` | `real<double>` | `1.000000` | `𝙶𝟷  ·  Sound Effects` | Replicated (COND_OwnerOnly) | `OnRep_Wind Whistling Volume` | InstanceEditable, ExposeToCinematics |
| `Wind Directional Source Speed Scale` | `real<double>` | `9.000000` | `𝙷𝟺  ·  Wind Directional Source` | — | — | InstanceEditable, ExposeToCinematics |
| `Obscured Lightning Scale` | `real<double>` | `1.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable |
| `Lightning Flash Max Angle from Forward` | `real<double>` | `100.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, ExposeToCinematics |
| `Show Lightning Flashes in Level Editor` | `bool` | `True` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable |
| `Lightning Flash Active` | `bool` | `False` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `Lightning Flash Time Elapsed` | `real<double>` | `0.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `Lightning Flash Length` | `real<double>` | `1.500000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `Temperature Scale` | `byte<UDS_TemperatureType>` | `NewEnumerator0` | `𝙺𝟷  ·  Temperature` | — | — | InstanceEditable |
| `Summer Temperature Min and Max` | `struct<Vector2D>` | `(X=55.000000,Y=80.000000)` | `𝙺𝟷  ·  Temperature` | — | — | InstanceEditable |
| `Autumn Temperature Min and Max` | `struct<Vector2D>` | `(X=40.000000,Y=70.000000)` | `𝙺𝟷  ·  Temperature` | — | — | InstanceEditable |
| `Winter Temperature Min and Max` | `struct<Vector2D>` | `(X=20.000000,Y=55.000000)` | `𝙺𝟷  ·  Temperature` | — | — | InstanceEditable |
| `Spring Temperature Min and Max` | `struct<Vector2D>` | `(X=30.000000,Y=65.000000)` | `𝙺𝟷  ·  Temperature` | — | — | InstanceEditable |
| `Daytime Temperature Bias` | `real<double>` | `0.600000` | `𝙺𝟷  ·  Temperature` | — | — | InstanceEditable |
| `Nighttime Temperature Bias` | `real<double>` | `-0.600000` | `𝙺𝟷  ·  Temperature` | — | — | InstanceEditable |
| `Morning/Evening Temperature Bias` | `real<double>` | `0.300000` | `𝙺𝟷  ·  Temperature` | — | — | InstanceEditable |
| `Overcast Temperature Bias` | `real<double>` | `-0.300000` | `𝙺𝟷  ·  Temperature` | — | — | InstanceEditable |
| `Raining Temperature Bias` | `real<double>` | `-0.300000` | `𝙺𝟷  ·  Temperature` | — | — | InstanceEditable |
| `Snowing Temperature Bias` | `real<double>` | `-1.500000` | `𝙺𝟷  ·  Temperature` | — | — | InstanceEditable |
| `Foggy Temperature Bias` | `real<double>` | `-0.200000` | `𝙺𝟷  ·  Temperature` | — | — | InstanceEditable |
| `Dusty Temperature Bias` | `real<double>` | `-0.300000` | `𝙺𝟷  ·  Temperature` | — | — | InstanceEditable |
| `Randomize Temperature` | `real<double>` | `5.000000` | `𝙺𝟷  ·  Temperature` | — | — | InstanceEditable, ExposeToCinematics |
| `Interior Temperature` | `real<double>` | `72.000000` | `𝙺𝟷  ·  Temperature` | — | — | InstanceEditable, ExposeToCinematics |
| `Interior Insulation` | `real<double>` | `0.850000` | `𝙺𝟷  ·  Temperature` | — | — | InstanceEditable, ExposeToCinematics |
| `Control Point Location Source` | `byte<UDS_ControlPointMode>` | `NewEnumerator3` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Weather Configuration Override` | `object<UDS_Weather_Configuration_C>` | `None` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Custom Control Point Location` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable, ExposeToCinematics |
| `Weather Speed` | `real<double>` | `1.000000` | `𝙰𝟷  ·  Basic Controls` | Replicated | — | InstanceEditable, ExposeToCinematics |
| `Random Seed` | `int` | `-1` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Snow Depth` | `real<double>` | `14.000000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Dust Depth` | `real<double>` | `7.000000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Snow/Dust Z Normal Cutoff` | `real<double>` | `0.660000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable |
| `Snow/Dust Z Normal Falloff` | `real<double>` | `1.500000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable |
| `Snow/Dust Texture Scale` | `real<double>` | `500.000000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable |
| `Snow/Dust Interaction Render Target Area` | `real<double>` | `10000.000000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable |
| `Snow/Dust Interaction Render Target Resolution` | `int` | `2000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable |
| `Snow/Dust Interaction Fade Speed Idle` | `real<double>` | `1.000000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Snow/Dust Interaction Fade Speed Active` | `real<double>` | `5.000000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Control Point Location` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable, Private |
| `Puddle Coverage` | `real<double>` | `0.260000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable |
| `Puddles Z Normal Cutoff` | `real<double>` | `0.950000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable |
| `Puddles Z Normal Falloff` | `real<double>` | `1.000000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable |
| `Base Wetness when Raining` | `real<double>` | `0.700000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Base Wetness when Clear` | `real<double>` | `0.500000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Puddle Sharpness` | `real<double>` | `40.000000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Variation Clouds Scale` | `real<double>` | `20000.000000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable |
| `Snow/Dust Interaction Edge Piling` | `real<double>` | `1.000000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable |
| `Snow/Dust Interaction Depth` | `real<double>` | `0.750000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable |
| `Snow/Dust Interaction Parallax Sample Scale` | `real<double>` | `1.000000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Snow/Dust Interaction Scale` | `real<double>` | `1.300000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Snow/Dust Interaction Size Scatter` | `real<double>` | `0.450000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, ExposeToCinematics |
| `Physical Materials which disable Snow/Dust Sounds and Particles` | `TArray<object<PhysicalMaterial>>` | — | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable |
| `Physical Materials which disable Puddle Sounds and Particles` | `TArray<object<PhysicalMaterial>>` | — | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable |
| `Enable WOV Material Effect Target` | `bool` | `True` | `𝙻𝟸  ·  Weather Override Volumes` | — | — | InstanceEditable |
| `WOV Target Size` | `real<double>` | `5000000.000000` | `𝙻𝟸  ·  Weather Override Volumes` | — | — | InstanceEditable |
| `WOV Target Resolution` | `int` | `1000` | `𝙻𝟸  ·  Weather Override Volumes` | — | — | InstanceEditable |
| `WOV Target Update Threshold (Inside Volume)` | `real<double>` | `0.005000` | `𝙻𝟸  ·  Weather Override Volumes` | — | — | InstanceEditable, ExposeToCinematics |
| `WOV Target Update Threshold (Outside Volume)` | `real<double>` | `0.020000` | `𝙻𝟸  ·  Weather Override Volumes` | — | — | InstanceEditable, ExposeToCinematics |
| `Use Custom Lightning Location` | `bool` | `False` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `Custom Lightning Location` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `Custom Lightning Target` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `Current Lightning Intensity` | `real<double>` | `0.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `Current Lightning Intensity Scale` | `real<double>` | `0.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `Current Lightning Location` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `Current Lightning Angle` | `real<double>` | `0.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `DLWE Mask Target` | `object<TextureRenderTarget2D>` | `/Script/Engine.TextureRenderTarget2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Weather/DLWE_MaskTarget.DLWE_MaskTarget'` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, Private |
| `DLWE Recenter Offset` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, Private |
| `Cloud Reference Array` | `TArray<struct<Vector2D>>` | `((X=124.000000,Y=119.000000),(X=156.000000,Y=127.000000),(X=191.000000,Y=134.000000),(X=193.000000,Y=146.000000),(X=183.000000,Y=143.000000),(X=151.000000,Y=180.000000),(X=87.000000,Y=184.000000),(X=88.000000,Y=169.000000),(X=84.000000,Y=141.000000),(X=112.000000,Y=137.000000),(X=144.000000,Y=131.000000),(X=139.000000,Y=126.000000),(X=126.000000,Y=153.000000),(X=120.000000,Y=150.000000),(X=103.000000,Y=137.000000),(X=136.000000,Y=165.000000),(X=170.000000,Y=186.000000),(X=197.000000,Y=202.000000),(X=175.000000,Y=224.000000),(X=164.000000,Y=199.000000),(X=122.000000,Y=167.000000),(X=129.000000,Y=142.000000),(X=116.000000,Y=136.000000),(X=64.000000,Y=148.000000),(X=69.000000,Y=145.000000),(X=95.000000,Y=133.000000),(X=125.000000,Y=139.000000),(X=144.000000,Y=132.000000),(X=140.000000,Y=119.000000),(X=137.000000,Y=72.000000),(X=107.000000,Y=100.000000),(X=111.000000,Y=114.000000),(X=137.000000,Y=66.000000),(X=136.000000,Y=96.000000),(X=150.000000,Y=155.000000),(X=171.000000,Y=167.000000),(X=142.000000,Y=114.000000),(X=139.000000,Y=135.000000),(X=110.000000,Y=161.000000),(X=103.000000,Y=151.000000),(X=114.000000,Y=150.000000),(X=139.000000,Y=158.000000),(X=163.000000,Y=160.000000),(X=134.000000,Y=135.000000),(X=122.000000,Y=151.000000),(X=138.000000,Y=146.000000),(X=143.000000,Y=138.000000),(X=165.000000,Y=169.000000),(X=186.000000,Y=206.000000),(X=183.000000,Y=208.000000),(X=153.000000,Y=194.000000),(X=142.000000,Y=170.000000),(X=106.000000,Y=149.000000),(X=95.000000,Y=137.000000),(X=91.000000,Y=127.000000),(X=54.000000,Y=121.000000),(X=51.000000,Y=121.000000),(X=94.000000,Y=99.000000),(X=139.000000,Y=90.000000),(X=154.000000,Y=114.000000),(X=162.000000,Y=120.000000),(X=155.000000,Y=100.000000),(X=80.000000,Y=94.000000),(X=100.000000,Y=87.000000),(X=136.000000,Y=122.000000),(X=112.000000,Y=136.000000),(X=119.000000,Y=168.000000),(X=134.000000,Y=183.000000),(X=131.000000,Y=126.000000),(X=102.000000,Y=101.000000),(X=120.000000,Y=141.000000),(X=122.000000,Y=120.000000),(X=110.000000,Y=120.000000),(X=111.000000,Y=122.000000),(X=146.000000,Y=117.000000),(X=106.000000,Y=141.000000),(X=99.000000,Y=144.000000),(X=115.000000,Y=168.000000),(X=130.000000,Y=134.000000),(X=155.000000,Y=143.000000),(X=156.000000,Y=177.000000),(X=156.000000,Y=183.000000),(X=147.000000,Y=183.000000),(X=153.000000,Y=174.000000),(X=127.000000,Y=103.000000),(X=130.000000,Y=66.000000),(X=108.000000,Y=86.000000),(X=95.000000,Y=113.000000),(X=94.000000,Y=133.000000),(X=110.000000,Y=119.000000),(X=141.000000,Y=76.000000),(X=140.000000,Y=56.000000),(X=166.000000,Y=88.000000),(X=191.000000,Y=110.000000),(X=148.000000,Y=115.000000),(X=135.000000,Y=101.000000),(X=149.000000,Y=162.000000),(X=165.000000,Y=179.000000),(X=175.000000,Y=177.000000),(X=156.000000,Y=181.000000),(X=126.000000,Y=116.000000),(X=91.000000,Y=72.000000),(X=109.000000,Y=121.000000),(X=172.000000,Y=94.000000),(X=162.000000,Y=111.000000),(X=125.000000,Y=91.000000),(X=123.000000,Y=80.000000),(X=108.000000,Y=128.000000),(X=91.000000,Y=148.000000),(X=79.000000,Y=151.000000),(X=102.000000,Y=118.000000),(X=104.000000,Y=132.000000),(X=94.000000,Y=137.000000),(X=143.000000,Y=152.000000),(X=145.000000,Y=159.000000),(X=189.000000,Y=145.000000),(X=183.000000,Y=88.000000),(X=136.000000,Y=54.000000),(X=100.000000,Y=82.000000),(X=97.000000,Y=117.000000),(X=95.000000,Y=120.000000),(X=101.000000,Y=131.000000),(X=126.000000,Y=84.000000),(X=152.000000,Y=44.000000),(X=143.000000,Y=79.000000),(X=155.000000,Y=116.000000),(X=148.000000,Y=111.000000),(X=151.000000,Y=101.000000),(X=171.000000,Y=174.000000),(X=172.000000,Y=146.000000),(X=180.000000,Y=131.000000),(X=124.000000,Y=136.000000),(X=117.000000,Y=133.000000),(X=105.000000,Y=96.000000),(X=97.000000,Y=91.000000),(X=145.000000,Y=104.000000),(X=155.000000,Y=121.000000),(X=123.000000,Y=127.000000),(X=114.000000,Y=123.000000),(X=133.000000,Y=136.000000),(X=127.000000,Y=147.000000),(X=88.000000,Y=134.000000),(X=85.000000,Y=104.000000),(X=85.000000,Y=119.000000),(X=95.000000,Y=134.000000),(X=140.000000,Y=119.000000),(X=130.000000,Y=88.000000),(X=203.000000,Y=115.000000),(X=177.000000,Y=125.000000),(X=128.000000,Y=104.000000),(X=94.000000,Y=104.000000),(X=82.000000,Y=122.000000),(X=110.000000,Y=126.000000),(X=137.000000,Y=135.000000),(X=152.000000,Y=128.000000),(X=170.000000,Y=93.000000),(X=144.000000,Y=101.000000),(X=117.000000,Y=99.000000),(X=136.000000,Y=99.000000),(X=140.000000,Y=139.000000),(X=132.000000,Y=156.000000),(X=143.000000,Y=112.000000),(X=165.000000,Y=110.000000),(X=139.000000,Y=119.000000),(X=96.000000,Y=131.000000),(X=78.000000,Y=114.000000),(X=110.000000,Y=129.000000),(X=154.000000,Y=161.000000),(X=130.000000,Y=152.000000),(X=119.000000,Y=145.000000),(X=124.000000,Y=145.000000),(X=156.000000,Y=159.000000),(X=113.000000,Y=170.000000),(X=100.000000,Y=166.000000),(X=75.000000,Y=136.000000),(X=93.000000,Y=127.000000),(X=121.000000,Y=116.000000),(X=137.000000,Y=90.000000),(X=151.000000,Y=105.000000),(X=193.000000,Y=115.000000),(X=149.000000,Y=105.000000),(X=119.000000,Y=116.000000),(X=118.000000,Y=112.000000),(X=125.000000,Y=161.000000),(X=130.000000,Y=165.000000),(X=154.000000,Y=147.000000),(X=177.000000,Y=131.000000),(X=161.000000,Y=113.000000),(X=119.000000,Y=101.000000),(X=100.000000,Y=88.000000),(X=122.000000,Y=129.000000),(X=107.000000,Y=153.000000),(X=106.000000,Y=129.000000),(X=120.000000,Y=116.000000),(X=128.000000,Y=138.000000),(X=135.000000,Y=142.000000),(X=126.000000,Y=138.000000),(X=106.000000,Y=148.000000),(X=120.000000,Y=177.000000),(X=154.000000,Y=173.000000),(X=137.000000,Y=139.000000),(X=158.000000,Y=136.000000),(X=147.000000,Y=132.000000),(X=131.000000,Y=123.000000),(X=95.000000,Y=120.000000),(X=88.000000,Y=161.000000),(X=71.000000,Y=159.000000),(X=106.000000,Y=150.000000),(X=143.000000,Y=150.000000),(X=172.000000,Y=157.000000),(X=197.000000,Y=148.000000),(X=187.000000,Y=108.000000),(X=158.000000,Y=89.000000),(X=126.000000,Y=111.000000),(X=137.000000,Y=103.000000),(X=144.000000,Y=125.000000),(X=157.000000,Y=151.000000),(X=154.000000,Y=153.000000),(X=153.000000,Y=129.000000),(X=128.000000,Y=123.000000),(X=89.000000,Y=100.000000),(X=79.000000,Y=83.000000),(X=106.000000,Y=130.000000),(X=97.000000,Y=147.000000),(X=91.000000,Y=74.000000),(X=92.000000,Y=118.000000),(X=125.000000,Y=152.000000),(X=163.000000,Y=141.000000),(X=146.000000,Y=141.000000),(X=116.000000,Y=149.000000),(X=128.000000,Y=153.000000),(X=142.000000,Y=174.000000),(X=160.000000,Y=123.000000),(X=160.000000,Y=115.000000),(X=133.000000,Y=137.000000),(X=103.000000,Y=136.000000),(X=68.000000,Y=110.000000),(X=95.000000,Y=110.000000),(X=124.000000,Y=107.000000),(X=138.000000,Y=120.000000),(X=156.000000,Y=156.000000),(X=172.000000,Y=167.000000),(X=189.000000,Y=164.000000),(X=179.000000,Y=145.000000),(X=147.000000,Y=124.000000),(X=103.000000,Y=107.000000),(X=112.000000,Y=103.000000),(X=133.000000,Y=123.000000),(X=155.000000,Y=132.000000),(X=126.000000,Y=136.000000),(X=137.000000,Y=140.000000),(X=116.000000,Y=134.000000),(X=109.000000,Y=118.000000),(X=116.000000,Y=85.000000),(X=106.000000,Y=76.000000),(X=91.000000,Y=81.000000),(X=72.000000,Y=97.000000),(X=91.000000,Y=114.000000),(X=129.000000,Y=123.000000),(X=156.000000,Y=111.000000),(X=185.000000,Y=144.000000),(X=160.000000,Y=148.000000),(X=156.000000,Y=134.000000),(X=140.000000,Y=150.000000),(X=122.000000,Y=154.000000),(X=157.000000,Y=151.000000),(X=134.000000,Y=183.000000),(X=96.000000,Y=151.000000),(X=67.000000,Y=109.000000),(X=111.000000,Y=111.000000),(X=157.000000,Y=90.000000),(X=135.000000,Y=99.000000),(X=126.000000,Y=157.000000),(X=155.000000,Y=165.000000),(X=135.000000,Y=154.000000),(X=148.000000,Y=152.000000),(X=104.000000,Y=125.000000),(X=97.000000,Y=99.000000),(X=120.000000,Y=90.000000),(X=146.000000,Y=98.000000),(X=167.000000,Y=113.000000),(X=129.000000,Y=116.000000),(X=121.000000,Y=101.000000),(X=139.000000,Y=95.000000),(X=148.000000,Y=107.000000),(X=145.000000,Y=98.000000),(X=138.000000,Y=79.000000),(X=97.000000,Y=83.000000),(X=78.000000,Y=91.000000),(X=124.000000,Y=105.000000),(X=121.000000,Y=98.000000),(X=138.000000,Y=94.000000),(X=136.000000,Y=113.000000),(X=119.000000,Y=103.000000),(X=143.000000,Y=90.000000),(X=141.000000,Y=95.000000),(X=124.000000,Y=144.000000),(X=130.000000,Y=177.000000),(X=122.000000,Y=183.000000),(X=85.000000,Y=167.000000),(X=77.000000,Y=152.000000),(X=101.000000,Y=157.000000),(X=118.000000,Y=126.000000),(X=125.000000,Y=141.000000),(X=129.000000,Y=158.000000),(X=147.000000,Y=183.000000),(X=140.000000,Y=173.000000),(X=144.000000,Y=143.000000),(X=126.000000,Y=136.000000),(X=110.000000,Y=109.000000),(X=106.000000,Y=75.000000),(X=134.000000,Y=59.000000),(X=179.000000,Y=76.000000),(X=160.000000,Y=102.000000),(X=149.000000,Y=70.000000),(X=124.000000,Y=69.000000),(X=120.000000,Y=98.000000),(X=160.000000,Y=104.000000),(X=180.000000,Y=118.000000),(X=121.000000,Y=107.000000),(X=111.000000,Y=78.000000),(X=116.000000,Y=88.000000),(X=112.000000,Y=104.000000),(X=136.000000,Y=119.000000),(X=96.000000,Y=145.000000),(X=75.000000,Y=119.000000),(X=113.000000,Y=107.000000),(X=121.000000,Y=87.000000),(X=102.000000,Y=118.000000),(X=87.000000,Y=140.000000),(X=96.000000,Y=158.000000),(X=113.000000,Y=165.000000),(X=115.000000,Y=159.000000),(X=149.000000,Y=174.000000),(X=135.000000,Y=141.000000),(X=155.000000,Y=125.000000),(X=166.000000,Y=138.000000),(X=144.000000,Y=164.000000),(X=131.000000,Y=174.000000),(X=143.000000,Y=144.000000),(X=117.000000,Y=94.000000),(X=85.000000,Y=93.000000),(X=72.000000,Y=117.000000),(X=109.000000,Y=109.000000),(X=152.000000,Y=99.000000),(X=161.000000,Y=127.000000),(X=152.000000,Y=103.000000),(X=118.000000,Y=105.000000),(X=121.000000,Y=128.000000),(X=108.000000,Y=132.000000),(X=124.000000,Y=121.000000),(X=119.000000,Y=95.000000),(X=122.000000,Y=94.000000),(X=114.000000,Y=80.000000),(X=148.000000,Y=95.000000),(X=121.000000,Y=129.000000),(X=94.000000,Y=148.000000),(X=90.000000,Y=131.000000),(X=131.000000,Y=115.000000),(X=122.000000,Y=106.000000),(X=65.000000,Y=128.000000),(X=55.000000,Y=110.000000),(X=102.000000,Y=114.000000),(X=93.000000,Y=125.000000),(X=89.000000,Y=104.000000),(X=137.000000,Y=111.000000),(X=150.000000,Y=128.000000),(X=157.000000,Y=131.000000),(X=214.000000,Y=140.000000),(X=210.000000,Y=144.000000),(X=206.000000,Y=162.000000),(X=152.000000,Y=106.000000),(X=118.000000,Y=91.000000),(X=78.000000,Y=105.000000),(X=86.000000,Y=129.000000),(X=120.000000,Y=156.000000),(X=170.000000,Y=157.000000),(X=160.000000,Y=159.000000),(X=150.000000,Y=98.000000),(X=139.000000,Y=112.000000),(X=129.000000,Y=127.000000),(X=107.000000,Y=139.000000),(X=119.000000,Y=145.000000),(X=96.000000,Y=129.000000),(X=118.000000,Y=141.000000),(X=115.000000,Y=109.000000),(X=120.000000,Y=114.000000),(X=102.000000,Y=128.000000),(X=110.000000,Y=125.000000),(X=124.000000,Y=116.000000),(X=139.000000,Y=104.000000),(X=124.000000,Y=108.000000),(X=105.000000,Y=122.000000),(X=86.000000,Y=113.000000),(X=137.000000,Y=114.000000),(X=120.000000,Y=122.000000),(X=87.000000,Y=89.000000),(X=106.000000,Y=82.000000),(X=158.000000,Y=105.000000),(X=157.000000,Y=150.000000),(X=192.000000,Y=161.000000),(X=235.000000,Y=159.000000),(X=235.000000,Y=173.000000),(X=187.000000,Y=131.000000),(X=159.000000,Y=122.000000),(X=128.000000,Y=139.000000),(X=94.000000,Y=164.000000),(X=95.000000,Y=154.000000),(X=156.000000,Y=149.000000),(X=139.000000,Y=118.000000),(X=140.000000,Y=126.000000),(X=137.000000,Y=151.000000),(X=127.000000,Y=163.000000),(X=117.000000,Y=146.000000),(X=118.000000,Y=148.000000),(X=116.000000,Y=146.000000),(X=125.000000,Y=120.000000),(X=127.000000,Y=82.000000),(X=139.000000,Y=93.000000),(X=150.000000,Y=85.000000),(X=126.000000,Y=99.000000),(X=130.000000,Y=124.000000),(X=150.000000,Y=125.000000),(X=170.000000,Y=117.000000),(X=155.000000,Y=104.000000),(X=146.000000,Y=81.000000),(X=167.000000,Y=123.000000),(X=174.000000,Y=133.000000),(X=129.000000,Y=87.000000),(X=137.000000,Y=88.000000),(X=155.000000,Y=121.000000),(X=152.000000,Y=128.000000),(X=173.000000,Y=144.000000),(X=190.000000,Y=143.000000),(X=175.000000,Y=182.000000),(X=160.000000,Y=152.000000),(X=146.000000,Y=153.000000),(X=128.000000,Y=156.000000),(X=121.000000,Y=168.000000),(X=136.000000,Y=165.000000),(X=143.000000,Y=121.000000),(X=107.000000,Y=93.000000),(X=115.000000,Y=105.000000),(X=143.000000,Y=124.000000),(X=140.000000,Y=117.000000),(X=125.000000,Y=115.000000),(X=94.000000,Y=130.000000),(X=113.000000,Y=132.000000),(X=107.000000,Y=107.000000),(X=126.000000,Y=109.000000),(X=167.000000,Y=124.000000),(X=193.000000,Y=131.000000),(X=153.000000,Y=127.000000),(X=125.000000,Y=130.000000),(X=141.000000,Y=135.000000),(X=201.000000,Y=121.000000),(X=165.000000,Y=94.000000),(X=145.000000,Y=97.000000),(X=156.000000,Y=163.000000),(X=151.000000,Y=166.000000),(X=114.000000,Y=98.000000),(X=114.000000,Y=101.000000),(X=126.000000,Y=111.000000),(X=129.000000,Y=79.000000),(X=149.000000,Y=106.000000),(X=168.000000,Y=142.000000),(X=194.000000,Y=140.000000),(X=176.000000,Y=92.000000),(X=146.000000,Y=116.000000),(X=103.000000,Y=138.000000),(X=111.000000,Y=129.000000),(X=159.000000,Y=118.000000),(X=118.000000,Y=119.000000),(X=70.000000,Y=112.000000),(X=104.000000,Y=124.000000),(X=163.000000,Y=110.000000),(X=164.000000,Y=92.000000),(X=170.000000,Y=74.000000),(X=137.000000,Y=60.000000),(X=98.000000,Y=93.000000),(X=136.000000,Y=114.000000),(X=139.000000,Y=148.000000),(X=158.000000,Y=164.000000),(X=222.000000,Y=156.000000),(X=180.000000,Y=157.000000),(X=155.000000,Y=119.000000),(X=149.000000,Y=106.000000),(X=164.000000,Y=77.000000),(X=155.000000,Y=97.000000),(X=158.000000,Y=138.000000),(X=152.000000,Y=186.000000),(X=134.000000,Y=173.000000),(X=104.000000,Y=128.000000),(X=119.000000,Y=129.000000),(X=126.000000,Y=130.000000),(X=141.000000,Y=103.000000),(X=122.000000,Y=95.000000),(X=143.000000,Y=127.000000),(X=169.000000,Y=112.000000),(X=152.000000,Y=86.000000),(X=126.000000,Y=112.000000),(X=131.000000,Y=142.000000),(X=127.000000,Y=168.000000),(X=124.000000,Y=153.000000),(X=91.000000,Y=149.000000),(X=65.000000,Y=157.000000),(X=99.000000,Y=161.000000),(X=151.000000,Y=121.000000),(X=147.000000,Y=107.000000),(X=154.000000,Y=89.000000),(X=144.000000,Y=110.000000),(X=136.000000,Y=136.000000),(X=141.000000,Y=121.000000),(X=140.000000,Y=159.000000),(X=153.000000,Y=147.000000),(X=173.000000,Y=128.000000),(X=154.000000,Y=114.000000),(X=140.000000,Y=115.000000),(X=132.000000,Y=105.000000),(X=138.000000,Y=62.000000),(X=163.000000,Y=97.000000),(X=169.000000,Y=158.000000),(X=134.000000,Y=148.000000),(X=133.000000,Y=163.000000),(X=106.000000,Y=140.000000),(X=125.000000,Y=108.000000),(X=144.000000,Y=126.000000),(X=137.000000,Y=118.000000),(X=143.000000,Y=123.000000),(X=138.000000,Y=136.000000),(X=142.000000,Y=145.000000),(X=141.000000,Y=152.000000),(X=136.000000,Y=137.000000),(X=133.000000,Y=142.000000),(X=158.000000,Y=183.000000),(X=148.000000,Y=202.000000),(X=130.000000,Y=170.000000),(X=136.000000,Y=189.000000),(X=127.000000,Y=147.000000),(X=147.000000,Y=113.000000),(X=128.000000,Y=132.000000),(X=160.000000,Y=130.000000),(X=143.000000,Y=151.000000),(X=150.000000,Y=138.000000),(X=126.000000,Y=127.000000),(X=107.000000,Y=113.000000),(X=145.000000,Y=118.000000),(X=150.000000,Y=104.000000),(X=153.000000,Y=85.000000),(X=124.000000,Y=104.000000),(X=90.000000,Y=92.000000),(X=79.000000,Y=83.000000),(X=106.000000,Y=99.000000),(X=124.000000,Y=166.000000),(X=138.000000,Y=176.000000),(X=122.000000,Y=169.000000),(X=103.000000,Y=168.000000),(X=111.000000,Y=129.000000),(X=107.000000,Y=117.000000),(X=115.000000,Y=96.000000),(X=100.000000,Y=140.000000),(X=88.000000,Y=154.000000),(X=84.000000,Y=150.000000),(X=113.000000,Y=173.000000),(X=152.000000,Y=174.000000),(X=164.000000,Y=146.000000),(X=192.000000,Y=155.000000),(X=170.000000,Y=150.000000),(X=145.000000,Y=150.000000),(X=158.000000,Y=173.000000),(X=142.000000,Y=139.000000),(X=158.000000,Y=117.000000),(X=143.000000,Y=129.000000),(X=143.000000,Y=122.000000),(X=148.000000,Y=136.000000),(X=141.000000,Y=123.000000),(X=113.000000,Y=126.000000),(X=108.000000,Y=108.000000),(X=137.000000,Y=144.000000),(X=124.000000,Y=120.000000),(X=125.000000,Y=86.000000),(X=142.000000,Y=90.000000),(X=116.000000,Y=123.000000),(X=70.000000,Y=118.000000),(X=80.000000,Y=104.000000),(X=92.000000,Y=166.000000),(X=127.000000,Y=191.000000),(X=145.000000,Y=165.000000),(X=143.000000,Y=134.000000),(X=143.000000,Y=86.000000),(X=140.000000,Y=115.000000),(X=112.000000,Y=118.000000),(X=101.000000,Y=122.000000),(X=104.000000,Y=129.000000),(X=88.000000,Y=127.000000),(X=93.000000,Y=159.000000),(X=126.000000,Y=163.000000),(X=149.000000,Y=149.000000),(X=159.000000,Y=143.000000),(X=155.000000,Y=100.000000),(X=134.000000,Y=141.000000),(X=115.000000,Y=174.000000),(X=123.000000,Y=145.000000),(X=148.000000,Y=94.000000),(X=111.000000,Y=131.000000),(X=88.000000,Y=118.000000),(X=128.000000,Y=114.000000),(X=134.000000,Y=142.000000),(X=161.000000,Y=114.000000),(X=121.000000,Y=125.000000),(X=125.000000,Y=153.000000),(X=144.000000,Y=140.000000),(X=131.000000,Y=102.000000),(X=156.000000,Y=79.000000),(X=134.000000,Y=107.000000),(X=86.000000,Y=132.000000),(X=120.000000,Y=102.000000),(X=134.000000,Y=127.000000),(X=132.000000,Y=184.000000),(X=192.000000,Y=184.000000),(X=182.000000,Y=124.000000),(X=150.000000,Y=62.000000),(X=135.000000,Y=104.000000),(X=109.000000,Y=126.000000),(X=130.000000,Y=94.000000),(X=150.000000,Y=95.000000),(X=109.000000,Y=122.000000),(X=94.000000,Y=152.000000),(X=106.000000,Y=135.000000),(X=130.000000,Y=121.000000),(X=126.000000,Y=123.000000),(X=90.000000,Y=93.000000),(X=77.000000,Y=134.000000),(X=110.000000,Y=146.000000),(X=120.000000,Y=131.000000),(X=104.000000,Y=91.000000),(X=88.000000,Y=113.000000),(X=84.000000,Y=102.000000),(X=109.000000,Y=134.000000),(X=113.000000,Y=121.000000),(X=155.000000,Y=109.000000),(X=121.000000,Y=135.000000),(X=107.000000,Y=163.000000),(X=160.000000,Y=175.000000),(X=142.000000,Y=184.000000),(X=150.000000,Y=163.000000),(X=131.000000,Y=120.000000),(X=124.000000,Y=111.000000),(X=125.000000,Y=106.000000),(X=140.000000,Y=122.000000),(X=176.000000,Y=164.000000),(X=207.000000,Y=158.000000),(X=189.000000,Y=148.000000),(X=150.000000,Y=108.000000),(X=136.000000,Y=119.000000),(X=121.000000,Y=86.000000),(X=124.000000,Y=89.000000),(X=137.000000,Y=75.000000),(X=143.000000,Y=120.000000),(X=131.000000,Y=144.000000),(X=131.000000,Y=139.000000),(X=107.000000,Y=109.000000),(X=105.000000,Y=99.000000),(X=61.000000,Y=94.000000),(X=119.000000,Y=117.000000),(X=145.000000,Y=118.000000),(X=122.000000,Y=101.000000),(X=67.000000,Y=120.000000),(X=64.000000,Y=141.000000),(X=78.000000,Y=150.000000),(X=102.000000,Y=149.000000),(X=118.000000,Y=97.000000),(X=135.000000,Y=112.000000),(X=124.000000,Y=119.000000),(X=112.000000,Y=151.000000),(X=145.000000,Y=204.000000),(X=150.000000,Y=211.000000),(X=156.000000,Y=189.000000),(X=115.000000,Y=149.000000),(X=119.000000,Y=133.000000),(X=146.000000,Y=114.000000),(X=165.000000,Y=136.000000),(X=178.000000,Y=135.000000),(X=192.000000,Y=116.000000),(X=168.000000,Y=128.000000),(X=162.000000,Y=138.000000),(X=156.000000,Y=104.000000),(X=148.000000,Y=70.000000),(X=149.000000,Y=65.000000),(X=136.000000,Y=58.000000),(X=117.000000,Y=85.000000),(X=118.000000,Y=106.000000),(X=117.000000,Y=107.000000),(X=95.000000,Y=107.000000),(X=87.000000,Y=127.000000),(X=108.000000,Y=77.000000),(X=164.000000,Y=52.000000),(X=133.000000,Y=83.000000),(X=118.000000,Y=106.000000),(X=91.000000,Y=139.000000),(X=109.000000,Y=174.000000),(X=107.000000,Y=159.000000),(X=141.000000,Y=119.000000),(X=127.000000,Y=101.000000),(X=108.000000,Y=99.000000),(X=120.000000,Y=90.000000),(X=123.000000,Y=132.000000),(X=128.000000,Y=190.000000),(X=151.000000,Y=215.000000),(X=144.000000,Y=186.000000),(X=126.000000,Y=108.000000),(X=121.000000,Y=118.000000),(X=142.000000,Y=97.000000),(X=139.000000,Y=129.000000),(X=129.000000,Y=127.000000),(X=149.000000,Y=104.000000),(X=148.000000,Y=103.000000),(X=163.000000,Y=144.000000),(X=169.000000,Y=152.000000),(X=168.000000,Y=113.000000),(X=152.000000,Y=70.000000),(X=108.000000,Y=54.000000),(X=91.000000,Y=81.000000),(X=110.000000,Y=151.000000),(X=114.000000,Y=128.000000),(X=99.000000,Y=106.000000),(X=119.000000,Y=143.000000),(X=142.000000,Y=110.000000),(X=146.000000,Y=72.000000),(X=145.000000,Y=109.000000),(X=125.000000,Y=146.000000),(X=126.000000,Y=166.000000),(X=126.000000,Y=209.000000),(X=125.000000,Y=168.000000),(X=147.000000,Y=153.000000),(X=131.000000,Y=127.000000),(X=118.000000,Y=88.000000),(X=113.000000,Y=87.000000),(X=119.000000,Y=100.000000),(X=123.000000,Y=153.000000),(X=148.000000,Y=145.000000),(X=144.000000,Y=121.000000),(X=162.000000,Y=117.000000),(X=152.000000,Y=136.000000),(X=119.000000,Y=109.000000),(X=123.000000,Y=99.000000),(X=113.000000,Y=122.000000),(X=125.000000,Y=119.000000),(X=137.000000,Y=130.000000),(X=161.000000,Y=133.000000),(X=170.000000,Y=128.000000),(X=165.000000,Y=146.000000),(X=138.000000,Y=157.000000),(X=131.000000,Y=112.000000),(X=121.000000,Y=134.000000),(X=133.000000,Y=170.000000),(X=158.000000,Y=130.000000),(X=152.000000,Y=107.000000),(X=132.000000,Y=118.000000),(X=117.000000,Y=115.000000),(X=120.000000,Y=82.000000),(X=125.000000,Y=117.000000),(X=119.000000,Y=166.000000),(X=124.000000,Y=187.000000),(X=149.000000,Y=199.000000),(X=160.000000,Y=152.000000),(X=145.000000,Y=111.000000),(X=134.000000,Y=106.000000),(X=98.000000,Y=106.000000),(X=105.000000,Y=128.000000),(X=116.000000,Y=97.000000),(X=105.000000,Y=126.000000),(X=136.000000,Y=147.000000),(X=111.000000,Y=105.000000),(X=135.000000,Y=119.000000),(X=150.000000,Y=143.000000),(X=152.000000,Y=133.000000),(X=124.000000,Y=119.000000),(X=97.000000,Y=121.000000),(X=99.000000,Y=161.000000),(X=138.000000,Y=157.000000),(X=167.000000,Y=167.000000),(X=181.000000,Y=163.000000),(X=137.000000,Y=177.000000),(X=147.000000,Y=172.000000),(X=142.000000,Y=126.000000),(X=148.000000,Y=154.000000),(X=152.000000,Y=149.000000),(X=181.000000,Y=131.000000),(X=159.000000,Y=130.000000),(X=153.000000,Y=135.000000),(X=121.000000,Y=139.000000),(X=97.000000,Y=112.000000),(X=119.000000,Y=113.000000),(X=119.000000,Y=158.000000),(X=101.000000,Y=163.000000),(X=157.000000,Y=132.000000),(X=157.000000,Y=96.000000),(X=129.000000,Y=107.000000),(X=102.000000,Y=135.000000),(X=124.000000,Y=127.000000),(X=125.000000,Y=112.000000),(X=144.000000,Y=115.000000),(X=111.000000,Y=142.000000),(X=112.000000,Y=137.000000),(X=119.000000,Y=99.000000),(X=143.000000,Y=112.000000),(X=139.000000,Y=117.000000),(X=164.000000,Y=108.000000),(X=153.000000,Y=124.000000),(X=142.000000,Y=138.000000),(X=120.000000,Y=172.000000),(X=131.000000,Y=184.000000),(X=152.000000,Y=168.000000),(X=177.000000,Y=160.000000),(X=163.000000,Y=145.000000),(X=140.000000,Y=164.000000),(X=166.000000,Y=169.000000),(X=163.000000,Y=176.000000),(X=158.000000,Y=149.000000),(X=136.000000,Y=144.000000),(X=106.000000,Y=156.000000),(X=142.000000,Y=129.000000),(X=140.000000,Y=142.000000),(X=99.000000,Y=156.000000),(X=91.000000,Y=148.000000),(X=83.000000,Y=163.000000),(X=98.000000,Y=147.000000),(X=128.000000,Y=108.000000),(X=123.000000,Y=95.000000),(X=116.000000,Y=88.000000),(X=120.000000,Y=100.000000),(X=144.000000,Y=107.000000),(X=166.000000,Y=138.000000),(X=176.000000,Y=156.000000),(X=127.000000,Y=176.000000),(X=151.000000,Y=144.000000),(X=194.000000,Y=135.000000),(X=174.000000,Y=147.000000),(X=150.000000,Y=152.000000),(X=152.000000,Y=126.000000),(X=133.000000,Y=122.000000),(X=165.000000,Y=145.000000),(X=165.000000,Y=181.000000),(X=150.000000,Y=209.000000),(X=102.000000,Y=144.000000),(X=152.000000,Y=141.000000),(X=154.000000,Y=148.000000),(X=127.000000,Y=159.000000),(X=141.000000,Y=165.000000),(X=148.000000,Y=164.000000),(X=152.000000,Y=137.000000),(X=106.000000,Y=132.000000),(X=105.000000,Y=139.000000),(X=136.000000,Y=118.000000),(X=157.000000,Y=146.000000),(X=140.000000,Y=158.000000),(X=116.000000,Y=156.000000),(X=96.000000,Y=147.000000),(X=88.000000,Y=99.000000),(X=119.000000,Y=105.000000),(X=131.000000,Y=120.000000),(X=122.000000,Y=88.000000),(X=128.000000,Y=56.000000),(X=126.000000,Y=123.000000),(X=152.000000,Y=151.000000),(X=151.000000,Y=164.000000),(X=146.000000,Y=143.000000),(X=165.000000,Y=141.000000),(X=188.000000,Y=140.000000),(X=173.000000,Y=141.000000),(X=169.000000,Y=158.000000),(X=188.000000,Y=134.000000),(X=169.000000,Y=147.000000),(X=176.000000,Y=158.000000),(X=183.000000,Y=166.000000),(X=165.000000,Y=183.000000),(X=114.000000,Y=167.000000),(X=126.000000,Y=143.000000),(X=170.000000,Y=108.000000),(X=161.000000,Y=140.000000),(X=119.000000,Y=160.000000),(X=113.000000,Y=136.000000),(X=108.000000,Y=142.000000),(X=100.000000,Y=141.000000),(X=114.000000,Y=157.000000),(X=150.000000,Y=152.000000),(X=155.000000,Y=139.000000),(X=173.000000,Y=144.000000),(X=146.000000,Y=124.000000),(X=114.000000,Y=101.000000),(X=109.000000,Y=93.000000),(X=132.000000,Y=110.000000),(X=161.000000,Y=142.000000),(X=158.000000,Y=115.000000),(X=121.000000,Y=81.000000),(X=108.000000,Y=158.000000),(X=143.000000,Y=159.000000),(X=143.000000,Y=178.000000),(X=143.000000,Y=145.000000),(X=150.000000,Y=153.000000),(X=160.000000,Y=169.000000),(X=170.000000,Y=137.000000),(X=174.000000,Y=117.000000),(X=178.000000,Y=134.000000),(X=161.000000,Y=161.000000),(X=142.000000,Y=153.000000),(X=129.000000,Y=152.000000),(X=128.000000,Y=183.000000),(X=132.000000,Y=170.000000),(X=144.000000,Y=132.000000),(X=167.000000,Y=109.000000),(X=180.000000,Y=103.000000),(X=117.000000,Y=121.000000),(X=82.000000,Y=136.000000),(X=78.000000,Y=152.000000),(X=93.000000,Y=159.000000),(X=110.000000,Y=161.000000),(X=122.000000,Y=164.000000),(X=142.000000,Y=145.000000),(X=148.000000,Y=113.000000),(X=141.000000,Y=88.000000),(X=111.000000,Y=90.000000),(X=112.000000,Y=88.000000),(X=124.000000,Y=97.000000),(X=160.000000,Y=119.000000),(X=153.000000,Y=117.000000),(X=115.000000,Y=131.000000),(X=138.000000,Y=157.000000),(X=133.000000,Y=149.000000),(X=113.000000,Y=165.000000),(X=111.000000,Y=157.000000),(X=145.000000,Y=178.000000),(X=170.000000,Y=168.000000),(X=142.000000,Y=148.000000),(X=158.000000,Y=126.000000),(X=161.000000,Y=149.000000),(X=124.000000,Y=181.000000),(X=104.000000,Y=172.000000),(X=54.000000,Y=161.000000),(X=81.000000,Y=158.000000),(X=113.000000,Y=174.000000),(X=140.000000,Y=165.000000),(X=143.000000,Y=120.000000),(X=136.000000,Y=108.000000),(X=126.000000,Y=140.000000),(X=114.000000,Y=151.000000),(X=99.000000,Y=154.000000),(X=101.000000,Y=145.000000),(X=140.000000,Y=161.000000),(X=158.000000,Y=159.000000),(X=147.000000,Y=156.000000),(X=148.000000,Y=115.000000),(X=153.000000,Y=114.000000),(X=157.000000,Y=135.000000),(X=138.000000,Y=107.000000),(X=145.000000,Y=100.000000),(X=147.000000,Y=121.000000),(X=139.000000,Y=140.000000),(X=136.000000,Y=153.000000),(X=111.000000,Y=156.000000),(X=91.000000,Y=159.000000),(X=95.000000,Y=137.000000),(X=93.000000,Y=156.000000),(X=110.000000,Y=173.000000),(X=151.000000,Y=156.000000),(X=143.000000,Y=155.000000),(X=125.000000,Y=122.000000),(X=125.000000,Y=158.000000),(X=83.000000,Y=191.000000),(X=95.000000,Y=165.000000),(X=66.000000,Y=152.000000),(X=74.000000,Y=178.000000),(X=120.000000,Y=196.000000),(X=110.000000,Y=142.000000),(X=108.000000,Y=122.000000),(X=115.000000,Y=112.000000),(X=110.000000,Y=155.000000),(X=107.000000,Y=167.000000),(X=83.000000,Y=142.000000),(X=100.000000,Y=138.000000),(X=143.000000,Y=159.000000),(X=165.000000,Y=160.000000),(X=115.000000,Y=158.000000),(X=132.000000,Y=124.000000),(X=143.000000,Y=165.000000),(X=115.000000,Y=164.000000),(X=122.000000,Y=105.000000),(X=141.000000,Y=121.000000),(X=156.000000,Y=112.000000),(X=160.000000,Y=112.000000),(X=139.000000,Y=138.000000),(X=122.000000,Y=164.000000),(X=115.000000,Y=158.000000),(X=124.000000,Y=140.000000),(X=115.000000,Y=158.000000),(X=132.000000,Y=174.000000),(X=110.000000,Y=159.000000),(X=123.000000,Y=159.000000),(X=124.000000,Y=118.000000),(X=76.000000,Y=128.000000),(X=70.000000,Y=139.000000),(X=113.000000,Y=120.000000),(X=116.000000,Y=131.000000),(X=105.000000,Y=177.000000),(X=114.000000,Y=175.000000),(X=98.000000,Y=144.000000),(X=97.000000,Y=153.000000),(X=118.000000,Y=137.000000),(X=146.000000,Y=182.000000),(X=171.000000,Y=194.000000),(X=133.000000,Y=185.000000),(X=136.000000,Y=129.000000),(X=150.000000,Y=127.000000),(X=129.000000,Y=152.000000),(X=94.000000,Y=168.000000),(X=86.000000,Y=173.000000),(X=115.000000,Y=176.000000),(X=126.000000,Y=155.000000),(X=133.000000,Y=124.000000),(X=133.000000,Y=142.000000),(X=130.000000,Y=113.000000),(X=146.000000,Y=129.000000),(X=140.000000,Y=169.000000))` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, Private |
| `Current Snow/Dust Depth` | `real<double>` | `0.000000` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, Private |
| `Use Occlusion to Attenuate Sounds in Interiors` | `bool` | `True` | `𝙶𝟸  ·  Sound Occlusion` | — | — | InstanceEditable, ExposeToCinematics |
| `Max Attenuation` | `real<double>` | `0.200000` | `𝙶𝟸  ·  Sound Occlusion` | Replicated (COND_OwnerOnly) | `OnRep_Max Attenuation` | InstanceEditable, ExposeToCinematics |
| `Min LPF Frequency` | `real<double>` | `600.000000` | `𝙶𝟸  ·  Sound Occlusion` | Replicated (COND_OwnerOnly) | `OnRep_Min LPF Frequency` | InstanceEditable, ExposeToCinematics |
| `Enable Post Process Wind Fog` | `bool` | `True` | `𝙷𝟻  ·  Post Process Wind Fog` | Replicated (COND_OwnerOnly) | `OnRep_Enable Post Process Wind Fog` | InstanceEditable |
| `PPWF Intensity from Fog` | `real<double>` | `1.400000` | `𝙷𝟻  ·  Post Process Wind Fog` | — | — | InstanceEditable, ExposeToCinematics |
| `PPWF Intensity from Rain` | `real<double>` | `1.400000` | `𝙷𝟻  ·  Post Process Wind Fog` | — | — | InstanceEditable, ExposeToCinematics |
| `PPWF Intensity from Snow` | `real<double>` | `1.400000` | `𝙷𝟻  ·  Post Process Wind Fog` | — | — | InstanceEditable, ExposeToCinematics |
| `PPWF Intensity from Dust` | `real<double>` | `1.400000` | `𝙷𝟻  ·  Post Process Wind Fog` | — | — | InstanceEditable, ExposeToCinematics |
| `PPWF Intensity from Wind` | `real<double>` | `0.700000` | `𝙷𝟻  ·  Post Process Wind Fog` | — | — | InstanceEditable |
| `PPWF Intensity Scale` | `real<double>` | `1.000000` | `𝙷𝟻  ·  Post Process Wind Fog` | — | — | InstanceEditable |
| `PPWF Max Sample Distance` | `real<double>` | `1800.000000` | `𝙷𝟻  ·  Post Process Wind Fog` | — | — | InstanceEditable |
| `PPWF Sample Step Distance` | `real<double>` | `120.000000` | `𝙷𝟻  ·  Post Process Wind Fog` | — | — | InstanceEditable |
| `PPWF 3D Noise Scale` | `real<double>` | `2000.000000` | `𝙷𝟻  ·  Post Process Wind Fog` | — | — | InstanceEditable |
| `PPWF Interior Mask Method` | `byte<UDS_PPWF_MaskMode>` | `NewEnumerator0` | `𝙷𝟻  ·  Post Process Wind Fog` | — | — | InstanceEditable |
| `Post Process Wind Fog MID` | `object<MaterialInstanceDynamic>` | `None` | `𝙷𝟻  ·  Post Process Wind Fog` | — | — | InstanceEditable, Private |
| `Temperature Update Period` | `real<double>` | `2.000000` | `𝙺𝟷  ·  Temperature` | — | — | InstanceEditable |
| `Time Random Offset` | `real<double>` | `-1.000000` | `𝙺𝟷  ·  Temperature` | Replicated | — | InstanceEditable, Private |
| `Enable Wind Direction Variation` | `bool` | `False` | `𝙷𝟷  ·  Wind Direction` | — | — | InstanceEditable, ExposeToCinematics |
| `Maximum Wind Direction Variation` | `real<double>` | `60.000000` | `𝙷𝟷  ·  Wind Direction` | — | — | InstanceEditable, ExposeToCinematics |
| `Variation Speed` | `real<double>` | `1.000000` | `𝙷𝟷  ·  Wind Direction` | — | — | InstanceEditable |
| `Started Raining` | `mcdelegate` | `()` | `Basic Weather Events` | — | — | InstanceEditable, Private |
| `Started Snowing` | `mcdelegate` | `()` | `Basic Weather Events` | — | — | InstanceEditable, Private |
| `Finished Raining` | `mcdelegate` | `()` | `Basic Weather Events` | — | — | InstanceEditable, Private |
| `Finished Snowing` | `mcdelegate` | `()` | `Basic Weather Events` | — | — | InstanceEditable, Private |
| `Getting Cloudy` | `mcdelegate` | `()` | `Basic Weather Events` | — | — | InstanceEditable, Private |
| `Clouds Clearing` | `mcdelegate` | `()` | `Basic Weather Events` | — | — | InstanceEditable, Private |
| `Enable Screen Droplets` | `bool` | `False` | `𝙸𝟷  ·  Screen Droplets` | Replicated (COND_OwnerOnly) | `OnRep_Enable Screen Droplets` | InstanceEditable |
| `Screen Center Strength` | `real<double>` | `0.000000` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable |
| `Screen Edge Strength` | `real<double>` | `2.000000` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable |
| `Camera Facing Rain Bias` | `real<double>` | `4.000000` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable, ExposeToCinematics |
| `Droplet Tiling` | `real<double>` | `1.000000` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable |
| `Blur Radius` | `real<double>` | `0.002000` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable |
| `Wet Screen When Emerging from Water` | `bool` | `True` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable |
| `Screen Droplets Clear Speed` | `real<double>` | `1.000000` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable |
| `Show Screen Droplets in Editor` | `bool` | `True` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable |
| `Screen Droplets MID` | `object<MaterialInstanceDynamic>` | `None` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable, Private |
| `Drops Time` | `real<double>` | `0.000000` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable, Private |
| `Screen Droplets Parent Material` | `softobject<MaterialInterface>` | `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Screen_Droplets.Screen_Droplets` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable, Private |
| `Enable Dust Particles` | `bool` | `True` | `𝙲𝟹  ·  Dust Particles` | Replicated (COND_OwnerOnly) | `OnRep_Enable Dust Particles` | InstanceEditable |
| `Dust Particle Spawn Count` | `real<double>` | `1000.000000` | `𝙲𝟹  ·  Dust Particles` | — | — | InstanceEditable |
| `Dust Particle Scale` | `real<double>` | `1.000000` | `𝙲𝟹  ·  Dust Particles` | — | — | InstanceEditable |
| `Dust Wind Velocity` | `real<double>` | `1400.000000` | `𝙲𝟹  ·  Dust Particles` | — | — | InstanceEditable |
| `Dust Velocity Randomization` | `real<double>` | `1.000000` | `𝙲𝟹  ·  Dust Particles` | — | — | InstanceEditable |
| `Dust Particle Color` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `𝙲𝟹  ·  Dust Particles` | — | — | InstanceEditable |
| `Dust Particle Alpha` | `real<double>` | `0.600000` | `𝙲𝟹  ·  Dust Particles` | — | — | InstanceEditable |
| `Enable Wind Debris` | `bool` | `False` | `𝙷𝟹  ·  Wind Debris` | Replicated (COND_OwnerOnly) | `OnRep_Enable Wind Debris` | InstanceEditable |
| `Wind Debris Particle Spawn Count` | `real<double>` | `5000.000000` | `𝙷𝟹  ·  Wind Debris` | Replicated (COND_OwnerOnly) | `OnRep_Wind Debris Particle Spawn Count` | InstanceEditable |
| `Debris Scale` | `real<double>` | `1.000000` | `𝙷𝟹  ·  Wind Debris` | — | — | InstanceEditable |
| `Debris Particle Alpha` | `real<double>` | `0.500000` | `𝙷𝟹  ·  Wind Debris` | — | — | InstanceEditable |
| `Wind Debris Wind Velocity` | `real<double>` | `2200.000000` | `𝙷𝟹  ·  Wind Debris` | — | — | InstanceEditable |
| `Wind Debris Atlas` | `softobject<Texture2D>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/Weather/Debris_Twigs_and_Leaves.Debris_Twigs_and_Leaves` | `𝙷𝟹  ·  Wind Debris` | — | — | InstanceEditable |
| `Weather Mask Brush Target` | `object<TextureRenderTarget2D>` | `/Script/Engine.TextureRenderTarget2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Weather/Weather_Mask_Brush_Target.Weather_Mask_Brush_Target'` | `𝙼𝟷  ·  Weather Mask Target` | — | — | InstanceEditable, Private |
| `Weather Mask Height Target` | `object<TextureRenderTarget2D>` | `/Script/Engine.TextureRenderTarget2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Weather/Weather_Mask_Height_Target.Weather_Mask_Height_Target'` | `𝙼𝟷  ·  Weather Mask Target` | — | — | InstanceEditable, Private |
| `Weather Mask Target Size` | `int` | `50000` | `𝙼𝟷  ·  Weather Mask Target` | — | — | InstanceEditable |
| `Old Weather State` | `object<UDS_Weather_Settings_C>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Light.Snow_Light'` | `Weather Settings Objects` | — | — | InstanceEditable |
| `Global Weather State` | `object<UDS_Weather_Settings_C>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Clear_Skies.Clear_Skies'` | `Weather Settings Objects` | — | — | InstanceEditable |
| `Local Weather State` | `object<UDS_Weather_Settings_C>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Clear_Skies.Clear_Skies'` | `Weather Settings Objects` | — | — | InstanceEditable |
| `Dust Particles Time Dilation` | `real<double>` | `1.000000` | `𝙲𝟹  ·  Dust Particles` | — | — | InstanceEditable |
| `Season Mode` | `byte<UDS_SeasonMode>` | `NewEnumerator0` | `𝙳𝟷  ·  Season` | — | — | InstanceEditable, ExposeToCinematics |
| `Season` | `real<double>` | `0.000000` | `𝙳𝟷  ·  Season` | Replicated | — | InstanceEditable, ExposeToCinematics |
| `Individual Seasons` | `TArray<real<double>>` | `(1.000000,0.000000,0.000000,0.000000)` | `Hidden Exposed` | — | — | InstanceEditable |
| `Manual Weather State` | `object<UDS_Weather_Settings_C>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Clear_Skies.Clear_Skies'` | `Weather Settings Objects` | — | — | InstanceEditable |
| `DLWE Trail Locations` | `TArray<struct<Vector>>` | — | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, Private |
| `DLWE Trail Size and Angle` | `TArray<struct<Vector>>` | — | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, Private |
| `DLWE Depth Fraction Buffer` | `TArray<real<double>>` | — | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, Private |
| `Lightning Light Ambient Scale` | `real<double>` | `0.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `Obscured Lightning Niagara System` | `softobject<NiagaraSystem>` | `/Game/_ThirdParty/UltraDynamicSky/Particles/Obscured_Lightning.Obscured_Lightning` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `Post Process Wind Fog w Downsampling` | `softobject<MaterialInterface>` | `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Post_Process_Wind_Fog.Post_Process_Wind_Fog` | `𝙷𝟻  ·  Post Process Wind Fog` | — | — | InstanceEditable, Private |
| `Dust/Sand Clearing` | `mcdelegate` | `()` | `Basic Weather Events` | — | — | InstanceEditable, Private |
| `Dust/Sand Forming` | `mcdelegate` | `()` | `Basic Weather Events` | — | — | InstanceEditable, Private |
| `Enable Rainbow` | `bool` | `False` | `𝙸𝟹  ·  Rainbow` | Replicated (COND_OwnerOnly) | `OnRep_Enable Rainbow` | InstanceEditable |
| `Max Rainbow Strength` | `real<double>` | `0.200000` | `𝙸𝟹  ·  Rainbow` | — | — | InstanceEditable, ExposeToCinematics |
| `Strength from Rain` | `real<double>` | `0.500000` | `𝙸𝟹  ·  Rainbow` | — | — | InstanceEditable, ExposeToCinematics |
| `Strength from Fog` | `real<double>` | `0.500000` | `𝙸𝟹  ·  Rainbow` | — | — | InstanceEditable, ExposeToCinematics |
| `Strength in any Weather` | `real<double>` | `0.000000` | `𝙸𝟹  ·  Rainbow` | — | — | InstanceEditable, ExposeToCinematics |
| `Time to Last After Rain/Fog` | `real<double>` | `100.000000` | `𝙸𝟹  ·  Rainbow` | — | — | InstanceEditable, ExposeToCinematics |
| `Mask Rainbow Above Clouds` | `real<double>` | `1.000000` | `𝙸𝟹  ·  Rainbow` | — | — | InstanceEditable |
| `Mask Rainbow Below Water` | `real<double>` | `1.000000` | `𝙸𝟹  ·  Rainbow` | — | — | InstanceEditable |
| `Getting Foggy` | `mcdelegate` | `()` | `Basic Weather Events` | — | — | InstanceEditable, Private |
| `Fog Clearing` | `mcdelegate` | `()` | `Basic Weather Events` | — | — | InstanceEditable, Private |
| `Weather Display Name Changed` | `mcdelegate` | `()` | `Basic Weather Events` | — | — | InstanceEditable, Private |
| `Last Sparse Movement Update Location` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Weather Volume Target` | `softobject<TextureRenderTarget2D>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/Weather/WOV_Material_State_Target.WOV_Material_State_Target` | `𝙻𝟸  ·  Weather Override Volumes` | — | — | InstanceEditable, Private |
| `WOV Target Brush MID` | `object<MaterialInstanceDynamic>` | `None` | `𝙻𝟸  ·  Weather Override Volumes` | — | — | InstanceEditable, Private |
| `Radial Storm Target Draw MID` | `object<MaterialInstanceDynamic>` | `None` | `𝙻𝟸  ·  Weather Override Volumes` | — | — | InstanceEditable, Private |
| `WOV Material Effect Target Active` | `bool` | `False` | `𝙻𝟸  ·  Weather Override Volumes` | — | — | InstanceEditable, Private |
| `UDS Version` | `string` | — | `Hidden Exposed` | — | — | InstanceEditable |
| `UDS Version Info` | `object<UDS_VersionInfo_C>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_VersionInfo.UDS_VersionInfo_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_CurrentVersion.UDS_CurrentVersion'` | `System` | — | — | InstanceEditable, Private |
| `Anti Aliasing Method` | `int` | `0` | `Renderer` | — | — | InstanceEditable, Private |
| `Season Debug` | `string` | — | `𝙳𝟷  ·  Season` | — | — | InstanceEditable |
| `Meteorological Seasons` | `bool` | `True` | `𝙳𝟷  ·  Season` | — | — | InstanceEditable |
| `Season Day Offset` | `int` | `0` | `𝙳𝟷  ·  Season` | — | — | InstanceEditable, ExposeToCinematics |
| `WOV Wind Direction` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `𝙷𝟷  ·  Wind Direction` | — | — | InstanceEditable, Private |
| `Current Lightning Target Offset` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `Splash Material Decal` | `softobject<Material>` | `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Splash_ParticleMat.Splash_ParticleMat` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable, Private |
| `Splash Material Translucent` | `softobject<Material>` | `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Splash_ParticleMat_Translucent.Splash_ParticleMat_Translucent` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable, Private |
| `Rainbow MID` | `object<MaterialInstanceDynamic>` | `None` | `𝙸𝟹  ·  Rainbow` | — | — | InstanceEditable, Private |
| `Current Rainbow Strength` | `real<double>` | `-1.000000` | `𝙸𝟹  ·  Rainbow` | — | — | InstanceEditable, Private |
| `Target Rainbow Strength` | `real<double>` | `0.000000` | `𝙸𝟹  ·  Rainbow` | — | — | InstanceEditable, Private |
| `Rainbow Material` | `softobject<MaterialInterface>` | `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Rainbow_Mat.Rainbow_Mat` | `𝙸𝟹  ·  Rainbow` | — | — | InstanceEditable, Private |
| `Weather Particle Motion Stretch` | `real<double>` | `1.000000` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `Particle Sprite Motion Blur with Camera Movement` | `real<double>` | `0.500000` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `Previous Temperature Scale` | `byte` | `2` | `Hidden Exposed` | — | — | InstanceEditable |
| `Apply Changes Above Volumetric Cloud Layer` | `bool` | `True` | `𝙻𝟷  ·  Weather Above Volumetric Clouds` | — | — | InstanceEditable |
| `Rain Multiplier Above Clouds` | `real<double>` | `0.000000` | `𝙻𝟷  ·  Weather Above Volumetric Clouds` | — | — | InstanceEditable |
| `Snow Multiplier Above Clouds` | `real<double>` | `0.000000` | `𝙻𝟷  ·  Weather Above Volumetric Clouds` | — | — | InstanceEditable |
| `Dust Multiplier Above Clouds` | `real<double>` | `0.000000` | `𝙻𝟷  ·  Weather Above Volumetric Clouds` | — | — | InstanceEditable |
| `Fog Multiplier Above Clouds` | `real<double>` | `0.000000` | `𝙻𝟷  ·  Weather Above Volumetric Clouds` | — | — | InstanceEditable |
| `Thunder/Lightning Multiplier Above Clouds` | `real<double>` | `0.000000` | `𝙻𝟷  ·  Weather Above Volumetric Clouds` | — | — | InstanceEditable |
| `Wind Multiplier Above Clouds` | `real<double>` | `0.500000` | `𝙻𝟷  ·  Weather Above Volumetric Clouds` | — | — | InstanceEditable |
| `Season Changed` | `mcdelegate` | `()` | `Season` | — | — | InstanceEditable, Private |
| `ED_Season` | `int` | `-1` | `Event Dispatching` | — | — | InstanceEditable |
| `Transition Active` | `bool` | `False` | `Transition System` | Replicated | `OnRep_Transition Active` | InstanceEditable, Private |
| `Transition Alpha` | `real<double>` | `0.000000` | `Transition System` | — | — | InstanceEditable, Private |
| `Post Process Wind Fog Legacy` | `softobject<MaterialInterface>` | `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Post_Process_Wind_Fog_Legacy.Post_Process_Wind_Fog_Legacy` | `𝙷𝟻  ·  Post Process Wind Fog` | — | — | InstanceEditable, Private |
| `Current PPWF Intensity` | `real<double>` | `0.000000` | `𝙷𝟻  ·  Post Process Wind Fog` | — | — | InstanceEditable, Private |
| `Target PPWF Intensity` | `real<double>` | `0.000000` | `𝙷𝟻  ·  Post Process Wind Fog` | — | — | InstanceEditable, Private |
| `Screen Droplets Active` | `bool` | `False` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable, Private |
| `Target Screen Droplets Drips Intensity` | `real<double>` | `0.000000` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable, Private |
| `Current Screen Droplets Drips Intensity` | `real<double>` | `0.000000` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable, Private |
| `Target Screen Droplets Camera Exposure` | `real<double>` | `0.000000` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable, Private |
| `Player Occlusion Below Water Level` | `byte<UDS_Occlusion_Water_Behavior>` | `NewEnumerator0` | `𝙹𝟷  ·  Water Level` | — | — | InstanceEditable |
| `Water Level Material Falloff` | `real<double>` | `100.000000` | `𝙹𝟷  ·  Water Level` | — | — | InstanceEditable |
| `Player Camera Underwater` | `bool` | `False` | `𝙹𝟷  ·  Water Level` | — | — | InstanceEditable, Private |
| `Splash Droplet Material Decal` | `softobject<Material>` | `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Splash_Droplet_Particle.Splash_Droplet_Particle` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable, Private |
| `Splash Droplet Material Translucent` | `softobject<Material>` | `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Splash_Droplet_Particle_Translucent.Splash_Droplet_Particle_Translucent` | `𝙲𝟷  ·  Rain Particles` | — | — | InstanceEditable, Private |
| `Weather Mask Target Resolution` | `int` | `1000` | `𝙼𝟷  ·  Weather Mask Target` | — | — | InstanceEditable |
| `Weather Mask Update Period` | `real<double>` | `0.050000` | `𝙼𝟷  ·  Weather Mask Target` | — | — | InstanceEditable |
| `Last Update Mask Components` | `TArray<object<PrimitiveComponent>>` | — | `𝙼𝟷  ·  Weather Mask Target` | — | — | InstanceEditable, Private |
| `Random Stream` | `struct<RandomStream>` | `()` | `System` | — | — | InstanceEditable, Private |
| `Weather Particle DOF Scale` | `real<double>` | `1.000000` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `Collision Path Buffer Length` | `int` | `2000` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `Collision Path Buffer Period` | `real<double>` | `1.000000` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `Scale Distant Particle Alpha` | `real<double>` | `3.000000` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `Distant Particle Range` | `real<double>` | `2500.000000` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `Weather Particles Raytracing Visibility` | `bool` | `False` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `Warm Up Weather Particles on Begin Play` | `bool` | `True` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `Apply Custom Weather Particle Camera Transform` | `bool` | `False` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable |
| `Custom Weather Particle Camera Location` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable, ExposeToCinematics |
| `Custom Weather Particle Camera Forward Vector` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=1.000000)` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable, ExposeToCinematics |
| `Old State Source Map` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `()` | `State Sources` | — | — | InstanceEditable, Private |
| `Last Update Sources` | `TArray<object<UDS_Weather_Settings_C>>` | — | `Hidden Exposed` | — | — | InstanceEditable |
| `Enable Heat Distortion` | `bool` | `False` | `𝙸𝟸  ·  Heat Distortion` | Replicated (COND_OwnerOnly) | `OnRep_Enable Heat Distortion` | InstanceEditable |
| `Heat Distortion Max Intensity` | `real<double>` | `0.080000` | `𝙸𝟸  ·  Heat Distortion` | — | — | InstanceEditable |
| `Heat Distortion from Temperature` | `real<double>` | `1.000000` | `𝙸𝟸  ·  Heat Distortion` | — | — | InstanceEditable, ExposeToCinematics |
| `Heat Distortion Temperature Range` | `struct<FloatRange>` | `(LowerBound=(Value=85.000000),UpperBound=(Value=100.000000))` | `𝙸𝟸  ·  Heat Distortion` | — | — | InstanceEditable |
| `Heat Distortion Uses Player Localized Temperature` | `bool` | `False` | `𝙸𝟸  ·  Heat Distortion` | — | — | InstanceEditable |
| `Manual Heat Distortion` | `real<double>` | `0.000000` | `𝙸𝟸  ·  Heat Distortion` | Replicated (COND_OwnerOnly) | `OnRep_Manual Heat Distortion` | InstanceEditable, ExposeToCinematics |
| `Heat DIstortion Start Distance` | `real<double>` | `7000.000000` | `𝙸𝟸  ·  Heat Distortion` | — | — | InstanceEditable |
| `Heat DIstortion Falloff` | `real<double>` | `20000.000000` | `𝙸𝟸  ·  Heat Distortion` | — | — | InstanceEditable |
| `Heat Distortion Tiling` | `real<double>` | `1.700000` | `𝙸𝟸  ·  Heat Distortion` | — | — | InstanceEditable |
| `Heat Distortion Speed` | `real<double>` | `0.180000` | `𝙸𝟸  ·  Heat Distortion` | — | — | InstanceEditable |
| `Heat Distortion Chromatic Separation` | `real<double>` | `0.200000` | `𝙸𝟸  ·  Heat Distortion` | — | — | InstanceEditable |
| `Heat Distortion Zenith Mask` | `real<double>` | `0.000000` | `𝙸𝟸  ·  Heat Distortion` | — | — | InstanceEditable |
| `Heat Distortion Horizon Mask` | `real<double>` | `1.000000` | `𝙸𝟸  ·  Heat Distortion` | — | — | InstanceEditable |
| `Heat Distortion Horizon Exponent` | `real<double>` | `2.500000` | `𝙸𝟸  ·  Heat Distortion` | — | — | InstanceEditable |
| `Heat Distortion Temporal Dither` | `real<double>` | `1.000000` | `𝙸𝟸  ·  Heat Distortion` | — | — | InstanceEditable |
| `Show Heat Distortion in Editor` | `bool` | `True` | `𝙸𝟸  ·  Heat Distortion` | — | — | InstanceEditable |
| `Target Heat Distortion Value` | `real<double>` | `0.000000` | `𝙸𝟸  ·  Heat Distortion` | — | — | InstanceEditable, Private |
| `Current Heat Distortion Value` | `real<double>` | `0.000000` | `𝙸𝟸  ·  Heat Distortion` | — | — | InstanceEditable, Private |
| `Heat Distortion Parent Material` | `softobject<MaterialInterface>` | `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Heat_Distortion.Heat_Distortion` | `𝙸𝟸  ·  Heat Distortion` | — | — | InstanceEditable, Private |
| `Heat Distortion MID` | `object<MaterialInstanceDynamic>` | `None` | `𝙸𝟸  ·  Heat Distortion` | — | — | InstanceEditable, Private |
| `State Change - Rain` | `mcdelegate` | `()` | `Weather State Changes` | — | — | InstanceEditable, Private |
| `State Change - Snow` | `mcdelegate` | `()` | `Weather State Changes` | — | — | InstanceEditable, Private |
| `State Change - Wind Intensity` | `mcdelegate` | `()` | `Weather State Changes` | — | — | InstanceEditable, Private |
| `State Change - Dust` | `mcdelegate` | `()` | `Weather State Changes` | — | — | InstanceEditable, Private |
| `State Change - Fog` | `mcdelegate` | `()` | `Weather State Changes` | — | — | InstanceEditable, Private |
| `State Change - Thunder/Lightning` | `mcdelegate` | `()` | `Weather State Changes` | — | — | InstanceEditable, Private |
| `State Change - Wind Direction` | `mcdelegate` | `()` | `Weather State Changes` | — | — | InstanceEditable, Private |
| `State Change - Cloud Coverage` | `mcdelegate` | `()` | `Weather State Changes` | — | — | InstanceEditable, Private |
| `State Change - Material Wetness` | `mcdelegate` | `()` | `Weather State Changes` | — | — | InstanceEditable, Private |
| `State Change - Material Snow` | `mcdelegate` | `()` | `Weather State Changes` | — | — | InstanceEditable, Private |
| `State Change - Material Dust` | `mcdelegate` | `()` | `Weather State Changes` | — | — | InstanceEditable, Private |
| `Tick Behavior Active` | `bool` | `False` | `Hidden Exposed` | — | — | InstanceEditable |
| `Run Context` | `byte<UDS_RunContext>` | `NewEnumerator0` | `System` | — | — | InstanceEditable, Private |
| `Max Attenuation for UDS Outdoor Sound` | `real<double>` | `0.100000` | `𝙶𝟸  ·  Sound Occlusion` | — | — | InstanceEditable |
| `Tick Delta Seconds` | `real<float>` | `0.100000` | `System` | — | — | InstanceEditable, Private |
| `Raining Dispatcher Threshold` | `real<double>` | `1.000000` | `𝙽𝟷  ·  Event Dispatchers` | — | — | InstanceEditable |
| `Snowing Dispatcher Threshold` | `real<double>` | `1.000000` | `𝙽𝟷  ·  Event Dispatchers` | — | — | InstanceEditable |
| `Dust/Sand Dispatcher Threshold` | `real<double>` | `3.000000` | `𝙽𝟷  ·  Event Dispatchers` | — | — | InstanceEditable |
| `Cloudy Dispatcher Threshold` | `real<double>` | `4.500000` | `𝙽𝟷  ·  Event Dispatchers` | — | — | InstanceEditable |
| `WOV Render Target State` | `object<UDS_RenderTarget_State_C>` | `None` | `Render Target` | — | — | InstanceEditable, Private |
| `Weather Mask Render Target State` | `object<UDS_RenderTarget_State_C>` | `None` | `Render Target` | — | — | InstanceEditable, Private |
| `DLWE Render Target State` | `object<UDS_RenderTarget_State_C>` | `None` | `Render Target` | — | — | InstanceEditable, Private |
| `Environment Sound` | `object<UDS_Environment_Sound_C>` | `None` | `𝙶𝟷  ·  Sound Effects\|Environment Sound` | — | — | InstanceEditable |
| `Environment Sound Weather Transition` | `real<double>` | `2.000000` | `𝙶𝟷  ·  Sound Effects\|Environment Sound` | — | — | InstanceEditable |
| `Environment Sound Time Transition` | `real<double>` | `10.000000` | `𝙶𝟷  ·  Sound Effects\|Environment Sound` | — | — | InstanceEditable |
| `Weather Sound Update Period` | `real<double>` | `0.500000` | `𝙶𝟷  ·  Sound Effects` | — | — | InstanceEditable |
| `Environment Sound Update Period` | `real<double>` | `1.000000` | `𝙶𝟷  ·  Sound Effects\|Environment Sound` | — | — | InstanceEditable |
| `Environment Sound Components` | `TMap<object<AudioComponent>>, object:/Script/Engine.AudioComponent>` | `()` | `𝙶𝟷  ·  Sound Effects\|Environment Sound` | — | — | InstanceEditable, Private |
| `Directional Sound Asset` | `softobject<SoundBase>` | `/Game/_ThirdParty/UltraDynamicSky/Sound/MetaSounds/UDS_Directional_WeatherSounds.UDS_Directional_WeatherSounds` | `𝙶𝟷  ·  Sound Effects` | — | — | InstanceEditable |
| `Global Sound Asset` | `softobject<SoundBase>` | `/Game/_ThirdParty/UltraDynamicSky/Sound/MetaSounds/UDS_Global_WeatherSounds.UDS_Global_WeatherSounds` | `𝙶𝟷  ·  Sound Effects` | — | — | InstanceEditable |
| `Custom Lightning Seed` | `int` | `-1` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `Temperature Range Update` | `mcdelegate` | `()` | `System` | — | — | InstanceEditable, Private |
| `Last Season Value` | `real<double>` | `-1.000000` | `𝙳𝟷  ·  Season` | — | — | InstanceEditable, Private |
| `Season Change Weather Refresh Threshold` | `real<double>` | `0.500000` | `𝙳𝟸  ·  Random Weather Variation` | — | — | InstanceEditable |
| `Random Weather Season Refresh` | `mcdelegate` | `()` | `System` | — | — | InstanceEditable, Private |
| `Old Weather State Struct` | `struct<UDW_WeatherState_Structure>` | `(CloudCoverage_27_31BA899D45A8A1B84FBCC7AEA870954F=-1.000000,Rain_4_4019C4FF4CE970F8CF06F99779966140=-1.000000,Snow_6_4DF1B106404D7B2DA02FBBB54BEB004A=-1.000000,ThunderLightning_8_6C3109794B58BE8BE4D0D39E9247D947=-1.000000,WindIntensity_28_7D0941E340035FB4BC9CD196CE7AA58B=-1.000000,Fog_22_4B6E454642665C025DADA1BD443B667A=-1.000000,Dust_23_4639102D44077B805735A6BC027AF7ED=-1.000000,MaterialWetness_29_2CE413784192D57B1FA486B8BF605372=-1.000000,MaterialSnowCoverage_30_10F93D3F42158AD6D1D5B7A58EB30E28=-1.000000,MaterialDustCoverage_31_4C9DA3A1430CCB4B92BCAB95AB03CAA9=-1.000000)` | `Transition System` | Replicated (COND_InitialOnly) | `OnRep_Old Weather State Struct` | InstanceEditable, Private |
| `DLWE Snow Trails Activated` | `bool` | `False` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, Private |
| `Dynamic Puddles Active` | `bool` | `False` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, Private |
| `Dynamic Snow/Dust` | `int` | `0` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, Private |
| `Weather Mask Target Active` | `bool` | `False` | `𝙼𝟷  ·  Weather Mask Target` | — | — | InstanceEditable, Private |
| `Mobile` | `bool` | `False` | `Renderer` | — | — | InstanceEditable, Private |
| `Lightning System Toggle` | `bool` | `False` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `Lightning Flash Started` | `mcdelegate` | `()` | `Lightning` | — | — | InstanceEditable, Private |
| `WOV Material Effect Target Allowed` | `bool` | `False` | `𝙻𝟸  ·  Weather Override Volumes` | — | — | InstanceEditable, Private |
| `Rainbow Mesh` | `object<StaticMeshComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Wind Debris Particles` | `object<NiagaraComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Wind Direction Target` | `real<double>` | `0.000000` | `𝙷𝟷  ·  Wind Direction` | — | — | InstanceEditable, Private |
| `Wind Direction Change Speed` | `real<double>` | `0.000000` | `𝙷𝟷  ·  Wind Direction` | — | — | InstanceEditable, Private |
| `Enable Screen Frost` | `bool` | `False` | `𝙸𝟺  ·  Screen Frost` | Replicated (COND_OwnerOnly) | `OnRep_Enable Screen Frost` | InstanceEditable |
| `Screen Frost from Snow` | `real<double>` | `1.000000` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable, ExposeToCinematics |
| `Screen Frost from Material Snow` | `real<double>` | `0.000000` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable, ExposeToCinematics |
| `Manual Screen Frost` | `real<double>` | `0.000000` | `𝙸𝟺  ·  Screen Frost` | Replicated (COND_OwnerOnly) | `OnRep_Manual Screen Frost` | InstanceEditable, ExposeToCinematics |
| `Screen Frost Multiplier in Interior` | `real<double>` | `0.000000` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable |
| `Screen Frost Form Duration` | `real<double>` | `8.000000` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable |
| `Screen Frost Clear Duration` | `real<double>` | `12.000000` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable |
| `Screen Frost Color` | `struct<LinearColor>` | `(R=0.525360,G=0.568881,B=0.593750,A=0.175000)` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable |
| `Screen Frost Falloff Shape` | `real<double>` | `0.500000` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable |
| `Screen Frost Falloff Exponent` | `real<double>` | `1.350000` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable |
| `Screen Frost Center Mask` | `real<double>` | `0.000000` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable |
| `Screen Frost Edge Mask` | `real<double>` | `1.000000` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable |
| `Screen Frost Distortion Strength` | `real<double>` | `0.200000` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable |
| `Screen Frost Distortion Alpha` | `real<double>` | `0.850000` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable |
| `Screen Frost Texture Scale` | `real<double>` | `3.000000` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable |
| `Screen Frost Scatter` | `real<double>` | `2.000000` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable |
| `Screen Frost Sharpness` | `real<double>` | `12.000000` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable |
| `Randomize Screen Frost Texture at Runtime` | `bool` | `True` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable |
| `Screen Frost Scatter Texture` | `softobject<Texture2D>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/Weather/Frost_Scatter.Frost_Scatter` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable |
| `Screen Frost Normal Texture` | `softobject<Texture2D>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/Weather/Snow_Normal.Snow_Normal` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable |
| `Show Screen Frost In Editor` | `bool` | `True` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable |
| `Screen Frost Active` | `bool` | `False` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable, Private |
| `Target Screen Frost Intensity` | `real<double>` | `0.000000` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable, Private |
| `Current Screen Frost Intensity` | `real<double>` | `0.000000` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable, Private |
| `Screen Frost MID` | `object<MaterialInstanceDynamic>` | `None` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable, Private |
| `Screen Frost Parent Material` | `softobject<MaterialInterface>` | `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Screen_Frost.Screen_Frost` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable, Private |
| `Loaded Objects` | `TArray<object<Object>>` | — | `System` | — | — | InstanceEditable, Private |
| `Rain Particles` | `object<NiagaraComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Snow Particles` | `object<NiagaraComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Dust Particles` | `object<NiagaraComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Obscured Lightning Particles` | `object<NiagaraComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Lightning Flash 1` | `object<NiagaraComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Lightning Flash 2` | `object<NiagaraComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Sparse Weather Occlusion` | `object<NiagaraComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Projection Box Scene Capture Component` | `object<SceneCaptureComponent2D>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Temperature Weather State` | `object<UDS_Weather_Settings_C>` | `None` | `Weather Settings Objects` | — | — | InstanceEditable, Private |
| `DLWE Trail Brush MID` | `object<MaterialInstanceDynamic>` | `None` | `𝙵𝟸  ·  Dynamic Landscape Weather Effects` | — | — | InstanceEditable, Private |
| `Last Update State Source Values` | `TArray<real<double>>` | — | `State Sources` | — | — | InstanceEditable, Private |
| `Last Update State Source Keys` | `TArray<object<UDS_Weather_Settings_C>>` | — | `State Sources` | — | — | InstanceEditable, Private |
| `Lightning Strike Niagara System` | `softobject<NiagaraSystem>` | `/Game/_ThirdParty/UltraDynamicSky/Particles/Lightning_Strike.Lightning_Strike` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `Wind Gust Intensity` | `real<double>` | `0.450000` | `𝙷𝟸  ·  Wind Gusts` | — | — | InstanceEditable |
| `Wind Gust Speed` | `real<double>` | `0.500000` | `𝙷𝟸  ·  Wind Gusts` | — | — | InstanceEditable |
| `Active Weather Particle Systems` | `TArray<object<NiagaraComponent>>` | — | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable, Private |
| `Target Wind Gust Multiplier` | `real<double>` | `0.000000` | `𝙷𝟸  ·  Wind Gusts` | — | — | InstanceEditable, Private |
| `Wind Directional Source Component` | `object<WindDirectionalSourceComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Disable Directional Source Speed in Interior` | `bool` | `False` | `𝙷𝟺  ·  Wind Directional Source` | — | — | InstanceEditable |
| `Wind Directional Source Update Period` | `real<double>` | `0.600000` | `𝙷𝟺  ·  Wind Directional Source` | — | — | InstanceEditable |
| `Enable Wind Camera Shake` | `bool` | `False` | `𝙷𝟼  ·  Wind Camera Shake` | Replicated (COND_OwnerOnly) | `OnRep_Enable Wind Camera Shake` | InstanceEditable |
| `Wind Camera Shake Scale` | `real<double>` | `0.500000` | `𝙷𝟼  ·  Wind Camera Shake` | — | — | InstanceEditable |
| `Wind Camera Shake Intensity Range` | `struct<FloatRange>` | `(LowerBound=(Value=8.000000),UpperBound=(Value=10.000000))` | `𝙷𝟼  ·  Wind Camera Shake` | — | — | InstanceEditable |
| `Enable Radial Storm Spawning` | `bool` | `False` | `𝙳𝟹  ·  Radial Storm Spawning` | Replicated (COND_OwnerOnly) | `OnRep_Enable Radial Storm Spawning` | InstanceEditable |
| `Radial Storm Spawning Direction Variation` | `real<double>` | `60.000000` | `𝙳𝟹  ·  Radial Storm Spawning` | — | — | InstanceEditable |
| `Radial Storm Probabilities (Spring)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `(("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Thunderstorm.Rain_Thunderstorm'", 1.000000))` | `𝙳𝟹  ·  Radial Storm Spawning` | — | — | InstanceEditable |
| `Radial Storm Probabilities (Summer)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `(("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Thunderstorm.Rain_Thunderstorm'", 1.000000))` | `𝙳𝟹  ·  Radial Storm Spawning` | — | — | InstanceEditable |
| `Radial Storm Probabilities (Autumn)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `(("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Rain_Thunderstorm.Rain_Thunderstorm'", 1.000000))` | `𝙳𝟹  ·  Radial Storm Spawning` | — | — | InstanceEditable |
| `Radial Storm Probabilities (Winter)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `(("/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Snow_Blizzard.Snow_Blizzard'", 1.000000))` | `𝙳𝟹  ·  Radial Storm Spawning` | — | — | InstanceEditable |
| `Radial Storm Start Distance` | `real<double>` | `25.000000` | `𝙳𝟹  ·  Radial Storm Spawning` | — | — | InstanceEditable |
| `Radial Storm End Distance` | `real<double>` | `25.000000` | `𝙳𝟹  ·  Radial Storm Spawning` | — | — | InstanceEditable |
| `Radial Storm Spawn Random Offset` | `real<double>` | `0.000000` | `𝙳𝟹  ·  Radial Storm Spawning` | — | — | InstanceEditable |
| `Radial Storm Outer Radius` | `real<double>` | `13.000000` | `𝙳𝟹  ·  Radial Storm Spawning` | — | — | InstanceEditable |
| `Radial Storm Inner Radius Fraction` | `real<double>` | `0.300000` | `𝙳𝟹  ·  Radial Storm Spawning` | — | — | InstanceEditable |
| `Radial Storm Lifetime Range` | `struct<FloatRange>` | `(LowerBound=(Value=500.000000),UpperBound=(Value=700.000000))` | `𝙳𝟹  ·  Radial Storm Spawning` | — | — | InstanceEditable |
| `Radial Storm Fade Duration Fraction` | `real<double>` | `0.200000` | `𝙳𝟹  ·  Radial Storm Spawning` | — | — | InstanceEditable |
| `Radial Storm Wait Interval Range` | `struct<FloatRange>` | `(LowerBound=(Value=1000.000000),UpperBound=(Value=2000.000000))` | `𝙳𝟹  ·  Radial Storm Spawning` | — | — | InstanceEditable |
| `Radial Storm First Wait Multiplier` | `real<double>` | `0.500000` | `𝙳𝟹  ·  Radial Storm Spawning` | — | — | InstanceEditable |
| `Radial Storm Class` | `softclass<Class>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Radial_Storm.Radial_Storm_C` | `𝙳𝟹  ·  Radial Storm Spawning` | — | — | InstanceEditable |
| `Radial Storm Class Hard` | `class<Class>` | `None` | `𝙳𝟹  ·  Radial Storm Spawning` | — | — | InstanceEditable, Private |
| `Wind Camera Shake Class` | `softclass<Class>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Wind_Camera_Shake.UDW_Wind_Camera_Shake_C` | `𝙷𝟼  ·  Wind Camera Shake` | — | — | InstanceEditable |
| `Foggy Dispatcher Threshold` | `real<double>` | `6.000000` | `𝙽𝟷  ·  Event Dispatchers` | — | — | InstanceEditable |
| `Outdoor Sound Mix Modifier` | `object<SoundMix>` | `None` | `𝙶𝟸  ·  Sound Occlusion` | — | — | InstanceEditable, Private |
| `DBuffer Supported` | `bool` | `False` | `Renderer` | — | — | InstanceEditable, Private |
| `Weather Particles Hidden` | `bool` | `False` | `𝙲𝟺  ·  Shared Particle Settings` | — | — | InstanceEditable, Private |
| `Force Weather Mask Target Active` | `bool` | `False` | `𝙼𝟷  ·  Weather Mask Target` | — | — | InstanceEditable, Private |
| `Force WOV Material Target Active` | `bool` | `False` | `𝙻𝟸  ·  Weather Override Volumes` | — | — | InstanceEditable, Private |
| `Instant State Change` | `mcdelegate` | `()` | `Weather State Changes` | — | — | InstanceEditable, Private |
| `Lightning Flash Bloom PP Material` | `softobject<MaterialInterface>` | `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/LightningFlashBloom_PP.LightningFlashBloom_PP` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `Lightning Flash Bloom MID` | `object<MaterialInstanceDynamic>` | `None` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `Random Weather Variation State` | `byte` | `10` | `𝙳𝟸  ·  Random Weather Variation` | Replicated | `OnRep_Random Weather Variation State` | InstanceEditable, Private |
| `Runtime Tick` | `mcdelegate` | `()` | `Active Binding` | — | — | InstanceEditable, Private |
| `Construct Global Weather` | `mcdelegate` | `()` | `State Update` | — | — | InstanceEditable, Private |
| `Construct Local Weather` | `mcdelegate` | `()` | `State Update` | — | — | InstanceEditable, Private |
| `Update Binding Changed` | `bool` | `False` | `System` | — | — | InstanceEditable, Private |
| `Material State Sim Active` | `bool` | `False` | `𝙵𝟷  ·  Material Effects` | — | — | InstanceEditable, Private |
| `Last Weather State Hash` | `TArray<int>` | `(-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1)` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Apply Active Updates` | `mcdelegate` | `()` | `Active Binding` | — | — | InstanceEditable, Private |
| `Material Parameters Weather State` | `object<UDS_Weather_Settings_C>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Clear_Skies.Clear_Skies'` | `Weather Settings Objects` | — | — | InstanceEditable |
| `Extra Feature Updates` | `mcdelegate` | `()` | `Active Binding` | — | — | InstanceEditable, Private |
| `Rainbow Active` | `bool` | `False` | `𝙸𝟹  ·  Rainbow` | — | — | InstanceEditable, Private |
| `Post Process Wind Fog Active` | `bool` | `False` | `𝙷𝟻  ·  Post Process Wind Fog` | — | — | InstanceEditable, Private |
| `Instant Weather Updating` | `bool` | `False` | `System` | — | — | InstanceEditable, Private |
| `Current Screen Droplets Camera Exposure` | `real<double>` | `0.000000` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable, Private |
| `Target Screen Droplets Intensity` | `real<double>` | `0.000000` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable, Private |
| `Current Screen Droplets Intensity` | `real<double>` | `0.000000` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable, Private |
| `Screen Droplets Manual Intensity` | `real<double>` | `0.000000` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable, Private |
| `Last Screen Droplets Periodic Update Time` | `real<double>` | `0.000000` | `𝙸𝟷  ·  Screen Droplets` | — | — | InstanceEditable, Private |
| `Current Screen Frost Occlusion Mask` | `real<double>` | `0.000000` | `𝙸𝟺  ·  Screen Frost` | — | — | InstanceEditable, Private |
| `Heat Distortion Active` | `bool` | `False` | `𝙸𝟸  ·  Heat Distortion` | — | — | InstanceEditable, Private |
| `Raining Dispatcher State` | `int` | `-1` | `Event Dispatching` | — | — | InstanceEditable, Private |
| `Snowing Dispatcher State` | `int` | `-1` | `Event Dispatching` | — | — | InstanceEditable, Private |
| `Foggy Dispatcher State` | `int` | `-1` | `Event Dispatching` | — | — | InstanceEditable, Private |
| `Cloudy Dispatcher State` | `int` | `-1` | `Event Dispatching` | — | — | InstanceEditable, Private |
| `Dust Dispatcher State` | `int` | `-1` | `Event Dispatching` | — | — | InstanceEditable, Private |
| `Display Name Dispatcher State` | `int` | `-1` | `Event Dispatching` | — | — | InstanceEditable, Private |
| `Wind Gust Multiplier Timer` | `real<double>` | `0.000000` | `𝙷𝟸  ·  Wind Gusts` | — | — | InstanceEditable, Private |
| `Current Wind Gust Multiplier` | `real<double>` | `0.000000` | `𝙷𝟸  ·  Wind Gusts` | — | — | InstanceEditable, Private |
| `Last Wind Gust Multiplier` | `real<double>` | `0.000000` | `𝙷𝟸  ·  Wind Gusts` | — | — | InstanceEditable, Private |
| `Lightning Flash Spawn Timer` | `real<double>` | `0.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `Lightning Flash Spawn Period` | `real<double>` | `2.000000` | `𝙴𝟷  ·  Lightning` | — | — | InstanceEditable, Private |
| `Environment Sound Time Integer` | `int` | `-1` | `𝙶𝟷  ·  Sound Effects` | — | — | InstanceEditable, Private |
| `Environment Sound Weather Integer` | `int` | `-1` | `𝙶𝟷  ·  Sound Effects` | — | — | InstanceEditable, Private |
| `Environment Sound Wind Integer` | `int` | `-1` | `𝙶𝟷  ·  Sound Effects` | — | — | InstanceEditable, Private |
| `Radial Storm Spawn Timer` | `struct<TimerHandle>` | `()` | `𝙳𝟹  ·  Radial Storm Spawning` | — | — | InstanceEditable, Private |
| `Screen Droplets Post Process` | `object<PostProcessComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Heat Distortion Post Process` | `object<PostProcessComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `PPWF Post Process` | `object<PostProcessComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Screen Frost Post Process` | `object<PostProcessComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Wind Camera Shake Timer` | `struct<TimerHandle>` | `()` | `𝙷𝟼  ·  Wind Camera Shake` | — | — | InstanceEditable, Private |
| `Weather Occlusion Volume System Asset` | `softobject<NiagaraSystem>` | `/Game/_ThirdParty/UltraDynamicSky/Particles/WeatherOcclusionVolumeSystem.WeatherOcclusionVolumeSystem` | `𝙼𝟸  ·  Weather Occlusion Volume` | — | — | InstanceEditable, Private |
| `Weather Occlusion Volume Area` | `real<double>` | `6000.000000` | `𝙼𝟸  ·  Weather Occlusion Volume` | — | — | InstanceEditable |
| `Weather Occlusion Volume Sample Period` | `real<double>` | `2.000000` | `𝙼𝟸  ·  Weather Occlusion Volume` | — | — | InstanceEditable |
| `Weather Occlusion Volume Max Trace DIstance` | `real<double>` | `4000.000000` | `𝙼𝟸  ·  Weather Occlusion Volume` | — | — | InstanceEditable |
| `Weather Occlusion Volume Center` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `𝙼𝟸  ·  Weather Occlusion Volume` | — | — | InstanceEditable, Private |
| `Distance Fields Supported` | `bool` | `False` | `Renderer` | — | — | InstanceEditable, Private |
| `Using Legacy PPWF` | `bool` | `False` | `𝙷𝟻  ·  Post Process Wind Fog` | — | — | InstanceEditable, Private |
| `Player Pawn` | `object<Pawn>` | `None` | `System` | — | — | InstanceEditable, Private |
| `Global State Binding Active` | `bool` | `False` | `Global State Update` | — | — | InstanceEditable, Private |
| `Active PPWF Interior Mask Method` | `byte<UDS_PPWF_MaskMode>` | `NewEnumerator0` | `𝙷𝟻  ·  Post Process Wind Fog` | — | — | InstanceEditable, Private |
| `Weather Occlusion Volume Dirty` | `bool` | `False` | `Hidden Exposed` | — | — | InstanceEditable |
| `Dispatch Tunnel` | `object<UDW_Dispatcher_Tunnel_C>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Dispatcher_Tunnel.UDW_Dispatcher_Tunnel_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_DispatcherTunnelAsset.UDW_DispatcherTunnelAsset'` | `System` | — | — | InstanceEditable, Private |
| `Weather Mask Height Draw MID` | `object<MaterialInstanceDynamic>` | `None` | `𝙼𝟷  ·  Weather Mask Target` | — | — | InstanceEditable, Private |
| `Global Update Rebind Count` | `int` | `0` | `Global State Update` | — | — | InstanceEditable, Private |
| `Local Update Rebind Count` | `int` | `0` | `Local State Update` | — | — | InstanceEditable, Private |
| `Last Weather Occlusion Trace Direction` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `𝙼𝟸  ·  Weather Occlusion Volume` | — | — | InstanceEditable, Private |
| `First Editor Tick` | `bool` | `True` | `System` | — | — | InstanceEditable, Private |

## Functions (333)

### `Any Manual Overrides Applied`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 13
- Category: `𝙱𝟷  ·  Manual Weather State`

### `Apply Climate Preset Object`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Climate_Preset_C> Climate)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 28
- Category: `𝙳𝟸  ·  Random Weather Variation`
- Description: If a climate object is supplied, it will use it to set the temperature ranges and the probability maps for random weather variation.

### `Apply Configuration Override`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8
- Category: `Startup`

### `Apply Environment Sound Interp Time`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `𝙶𝟷  ·  Sound Effects`

### `Apply Local Temperature Effects`

- Access: `Protected`
- Flags: —
- Inputs: `(real<double> Temp, real<double> Occlusion, struct<Vector> Location)`
- Outputs: `(real<double> Temp Out)`
- Local variables (4): `Local Interior Temp`, `Unconverted Temperature`, `Total Offset`, `Manual Alpha`
- Nodes: 45
- Category: `𝙺𝟷  ·  Temperature`

### `Apply Sound Effects Volume Levels`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 28
- Category: `𝙶𝟷  ·  Sound Effects`

### `Apply Sound Update Periods`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9
- Category: `𝙶𝟷  ·  Sound Effects`

### `Apply Weather Configuration`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Weather_Configuration_C> Configuration)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 104
- Category: `Utility Functions`
- Description: Call to apply a full configuration of all the exposed settings on UDW at runtime. Created using the Configuration Manager utility. Understand this necessarily restarts the entire system as if it is returning to begin play.

### `Apply Wind Camera Shake`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Shake Mask`
- Nodes: 27
- Category: `𝙷𝟼  ·  Wind Camera Shake`

### `AU - Check for Dispatcher - Weather Display Name`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables (1): `Current State`
- Nodes: 14
- Category: `Event Dispatching`

### `AU - Cloud Coverage Material Parameter`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `𝙵𝟷  ·  Material Effects`

### `AU - DLWE Interaction Mode`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables (1): `New Snow/Dust`
- Nodes: 38
- Category: `𝙵𝟸  ·  Dynamic Landscape Weather Effects`

### `AU - DLWE Snow/Dust Parameters`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 30
- Category: `𝙵𝟸  ·  Dynamic Landscape Weather Effects`

### `AU - Dust Spawn Rate`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables (1): `Spawn Rate Scale`
- Nodes: 23
- Category: `𝙲𝟹  ·  Dust Particles`

### `AU - Dynamic Puddles Active`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `𝙵𝟸  ·  Dynamic Landscape Weather Effects`

### `AU - Fog Material Parameter`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `𝙵𝟷  ·  Material Effects`

### `AU - Heat Distortion Intensity`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 23
- Category: `𝙸𝟸  ·  Heat Distortion`
- Description: Runs periodically at runtime to check how strong heat distortion should currently be based on temperature

### `AU - Obscured Lightning Spawn Rate`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables (1): `Spawn Rate`
- Nodes: 21
- Category: `𝙴𝟷  ·  Lightning`

### `AU - Post Process Wind Fog Intensity`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 43
- Category: `𝙷𝟻  ·  Post Process Wind Fog`

### `AU - Rain Spawn Rate`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables (1): `Spawn Rate`
- Nodes: 17
- Category: `𝙲𝟷  ·  Rain Particles`

### `AU - Rainbow Strength`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 24
- Category: `𝙸𝟹  ·  Rainbow`

### `AU - Raining Material Parameter`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `𝙵𝟷  ·  Material Effects`

### `AU - Sand/Dust Material Parameter`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `𝙵𝟷  ·  Material Effects`

### `AU - Screen Droplets Intensity`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 19
- Category: `𝙸𝟷  ·  Screen Droplets`
- Description: Checks weather and the camera's exposure to rain, and uses that to control intensity of drips/drops for the Screen Droplets effect.

### `AU - Screen Frost Intensity`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 30
- Category: `𝙸𝟺  ·  Screen Frost`

### `AU - Snow Spawn Rate`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables (1): `Spawn Rate`
- Nodes: 16
- Category: `𝙲𝟸  ·  Snow Particles`

### `AU - Snowing Material Parameter`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `𝙵𝟷  ·  Material Effects`

### `AU - Update Rain Sound Parameter`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6
- Category: `𝙶𝟷  ·  Sound Effects`

### `AU - Update Thunder/Lightning Sound Parameter`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `𝙶𝟷  ·  Sound Effects`

### `AU - Update Wind Directional Source Direction`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6
- Category: `𝙷𝟺  ·  Wind Directional Source`
- Description: Updates the speed and direction of the wind directional source component

### `AU - Update Wind Directional Source Speed`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 22
- Category: `𝙷𝟺  ·  Wind Directional Source`
- Description: Updates the speed and direction of the wind directional source component

### `AU - Update Wind Intensity Sound Parameter`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6
- Category: `𝙶𝟷  ·  Sound Effects`

### `AU - Update Wind Lean Sound Parameters`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 18
- Category: `𝙶𝟷  ·  Sound Effects`

### `AU - Wind Angle Parameter`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `𝙵𝟷  ·  Material Effects`

### `AU - Wind Debris Spawn Rate`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables (1): `Spawn Rate`
- Nodes: 16
- Category: `𝙷𝟹  ·  Wind Debris`

### `AU - Wind Force Parameter`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `𝙵𝟷  ·  Material Effects`

### `Bind Active Updates - Cloud Coverage`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6
- Category: `Active Update Bindings`

### `Bind Active Updates - Dust`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10
- Category: `Active Update Bindings`

### `Bind Active Updates - Fog`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10
- Category: `Active Update Bindings`

### `Bind Active Updates - Material Dust`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8
- Category: `Active Update Bindings`

### `Bind Active Updates - Material Snow`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11
- Category: `Active Update Bindings`

### `Bind Active Updates - Material Wetness`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Active Update Bindings`

### `Bind Active Updates - Rain`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 16
- Category: `Active Update Bindings`

### `Bind Active Updates - Snow`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12
- Category: `Active Update Bindings`

### `Bind Active Updates - Thunder/Lightning`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Active Update Bindings`

### `Bind Active Updates - Wind Direction`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9
- Category: `Active Update Bindings`

### `Bind Active Updates - Wind Intensity`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 16
- Category: `Active Update Bindings`

### `Bind Events to Tick`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 63
- Category: `Startup`

### `Bind Extra Feature Updates`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 54
- Category: `Extra Features`

### `Bind Global State Update Functions`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Anything Changing Global Weather`
- Nodes: 62
- Category: `Global State Update`

### `Bind Local State Update Functions`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 36
- Category: `Local State Update`
- Description: Binds the functions which are called to construct the local weather state

### `Bind to Array Managers`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Startup`

### `Bind to Game User Settings`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Startup`

### `Bind to UDS Dispatchers`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8
- Category: `Startup`

### `Bind to UDS Events`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `UDS Connection`

### `Calculate Display Name for Weather State Object`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Weather_Settings_C> State)`
- Outputs: `(byte Display Name)`
- Local variables (1): `Chosen Enum`
- Nodes: 61
- Category: `Weather State`
- Description: Finds a descriptor for the state values of a weather settings object.

### `Call Custom Weather Behavior`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (6): `Keys Buffer`, `Source Map Buffer`, `Updating Global Sources`, `Active Sources`, `Values Buffer`, `Sources Changed`
- Nodes: 54
- Category: `Weather State`
- Description: If needed by enabled features, keeps track of the specific weather settings objects which are contributing to the global and local weather states, and how much for each.

### `Change Environment Sound`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Environment_Sound_C> New Sound, real<double> Fade Duration = 10.000000, bool Async Load Source = true)`
- Outputs: `()`
- Local variables (3): `Current Audio Component`, `Source Loaded`, `Toggling Component`
- Nodes: 101
- Category: `𝙶𝟷  ·  Sound Effects`
- Description: Call to enable an environment sound asset, change from the current one to another, or disable them (by calling with no asset selected) If Async Load Source is true, the metasound source will be async loaded if it is not ready, meaning the actual start of the sound will be delayed by the amount of time it takes to load.

### `Change Wind Direction`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> New Wind Direction = 180.000000, real<double> Change Duration)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 20
- Category: `𝙷𝟷  ·  Wind Direction`
- Description: Once called, the wind direction on UDW will start transitioning to a new value over a transition duration. Note this is the global wind direction defined in Basic Controls on UDW. This won't take priority over Weather Override Volumes which control wind direction.

### `Check Camera Relative to Water Level`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 19
- Category: `𝙹𝟷  ·  Water Level`

### `Check for Actors to be Struck by Lightning`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Striking Actor, struct<Vector> Target Location, bool Striking Actor, struct<Vector> Target Location, bool Striking Actor, struct<Vector> Target Location, bool Striking Actor, struct<Vector> Target Location)`
- Local variables (4): `All Strikable Actors`, `Potential Strikable Locations`, `Potential Strikable Actors`, `Selected Index`
- Nodes: 46
- Category: `𝙴𝟷  ·  Lightning`

### `Check for Dispatcher - Cloudy`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Current State`
- Nodes: 15
- Category: `Event Dispatching`

### `Check for Dispatcher - Dust/Sand`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Current State`
- Nodes: 16
- Category: `Event Dispatching`

### `Check for Dispatcher - Foggy`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Current State`
- Nodes: 16
- Category: `Event Dispatching`

### `Check for Dispatcher - Raining`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Current State`
- Nodes: 16
- Category: `Event Dispatching`

### `Check for Dispatcher - Snowing`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Current State`
- Nodes: 16
- Category: `Event Dispatching`

### `Check for Render Target Recentering`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 41
- Category: `Render Target`

### `Check Point for Puddles Snow Or Dust`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Location, struct<Vector> Ground Normal, object<PhysicalMaterial> Physical Material)`
- Outputs: `(real<double> Puddle Depth, real<double> Snow Depth, real<double> Dust Depth, real<double> Puddle Depth, real<double> Snow Depth, real<double> Dust Depth, real<double> Puddle Depth, real<double> Snow Depth, real<double> Dust Depth)`
- Local variables (8): `Large Cloud Sample`, `Small Cloud Sample`, `Snow Mask`, `Puddle Mask`, `Weather Mask`, `Weather Mask Rain`, `Mask_Cancel`, `Dust Mask`
- Nodes: 168
- Category: `𝙵𝟸  ·  Dynamic Landscape Weather Effects`
- Description: Approximates the material logic for snow coverage, dust coverage, and puddles, from Dynamic Landscape Weather Effects

### `Check to Activate Extra Feature`

- Access: `Protected`
- Flags: —
- Inputs: `(real<double>& Target Intensity [ref], real<double>& Current Intensity [ref], bool& Effect Active [ref])`
- Outputs: `(bool Activated, bool Activated)`
- Local variables: _none_
- Nodes: 21
- Category: `Extra Features`

### `Check to Change Temperature Scale`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 86
- Category: `𝙺𝟷  ·  Temperature`

### `Check UDS Version`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 19
- Category: `Startup`

### `Clear All Material Parameters to Zero Coverage`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 18
- Category: `𝙵𝟷  ·  Material Effects`
- Description: Sets shared material parameters for weather state to values which represent no active material coverage

### `Clear All Render Targets`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 17
- Category: `Render Target`

### `Close Thunder Sound Delay`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Delay)`
- Local variables: _none_
- Nodes: 10
- Category: `𝙶𝟷  ·  Sound Effects`
- Description: Amount the close thunder sound should be delayed, based on its distance.

### `Compress DLWE Snow/Dust`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Location, real<double> Depth Fraction, struct<Vector> Size and Angle)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 28
- Category: `𝙵𝟸  ·  Dynamic Landscape Weather Effects`
- Description: Called by the DLWE Interaction component. Requests a single compression to be drawn into the render target.

### `Configure Editor Actor Appearance`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Status MID`
- Nodes: 29
- Category: `Editor`

### `Construct All Weather State Objects`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 22
- Category: `Startup`
- Description: Creates the required weather state objects for the local weather state, old weather state, etc.

### `Construct Weather Mask Target State`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 30
- Category: `𝙼𝟷  ·  Weather Mask Target`

### `Construct Weather State Object if Invalid`

- Access: `Protected`
- Flags: —
- Inputs: `(object<UDS_Weather_Settings_C>& State [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10
- Category: `Startup`
- Description: Checks if a weather state object is invalid and constructs it if it is.

### `Construct WOV Render Target State`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 34
- Category: `𝙻𝟸  ·  Weather Override Volumes`

### `Convert Temperature Scale`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Input, byte In Scale = NewEnumerator0, byte Out Scale = NewEnumerator0, bool Relative Degrees, bool Snap)`
- Outputs: `(real<double> Output)`
- Local variables: _none_
- Nodes: 19
- Category: `𝙺𝟷  ·  Temperature`
- Description: Converts from celsius to fahrenheit

### `Copy Manual State Object to Variables`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 31
- Category: `𝙱𝟷  ·  Manual Weather State`

### `Copy Old Weather State Struct to Object`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6
- Category: `Weather State`

### `Create Cloud Reference Array`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (3): `Source Render Target`, `Pixel X`, `Pixel Y`
- Nodes: 22
- Category: `𝙵𝟸  ·  Dynamic Landscape Weather Effects`

### `Create Composite Probability Map`

- Access: `Protected`
- Flags: —
- Inputs: `(object<Random_Weather_Variation_C> Random Weather Variation Component)`
- Outputs: `(TMap<object<UDS_Weather_Settings_C,>>, real> Out, TMap<object<UDS_Weather_Settings_C,>>, real> Out)`
- Local variables (3): `Composite Map`, `Season Probability Totals`, `Individual Seasons2`
- Nodes: 60
- Category: `𝙳𝟸  ·  Random Weather Variation`
- Description: Blends seasonal probability maps together based on the progress between seasons

### `Currently Cloudy`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Yes)`
- Local variables: _none_
- Nodes: 6
- Category: `Event Dispatching`
- Description: Used for the event dispatchers for cloudiness

### `Currently Dusty`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Yes)`
- Local variables: _none_
- Nodes: 6
- Category: `Event Dispatching`
- Description: Used for the event dispatchers for dust

### `Currently Foggy`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Yes)`
- Local variables: _none_
- Nodes: 6
- Category: `Event Dispatching`
- Description: Used for the event dispatchers for fog

### `Currently Raining`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Yes)`
- Local variables: _none_
- Nodes: 6
- Category: `Event Dispatching`
- Description: Used for the event dispatchers for rain

### `Currently Snowing`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Yes)`
- Local variables: _none_
- Nodes: 6
- Category: `Event Dispatching`
- Description: Used for the event dispatchers for snow

### `Custom Weather Mask Target Drawing Logic`

- Access: `Protected`
- Flags: —
- Inputs: `(object<Canvas> Canvas)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1
- Category: `𝙼𝟷  ·  Weather Mask Target`
- Description: An empty function called in the function which updates the weather mask target, during the draw to the canvas. Can be overriden to add extra drawing logic for the weather mask.

### `Custom WOV Render Target Drawing Logic`

- Access: `Protected`
- Flags: —
- Inputs: `(object<Canvas> Canvas)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1
- Category: `𝙻𝟸  ·  Weather Override Volumes`
- Description: Empty function which is called in the process of drawing to the WOV render target. Can be overridden to add extra logic for drawing to that target before the WOVs and Radial Storms do.

### `Daily Season Update`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `𝙳𝟷  ·  Season`

### `Delete/Clear Runtime Data`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 77
- Category: `System`

### `Dust Niagara System Asset`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(softobject<NiagaraSystem> Out)`
- Local variables: _none_
- Nodes: 3
- Category: `𝙲𝟹  ·  Dust Particles`

### `Dust Spawn Rate Scale`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 7
- Category: `𝙲𝟹  ·  Dust Particles`

### `Dust System Finished`

- Access: `Protected`
- Flags: —
- Inputs: `(object<NiagaraComponent> PSystem)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `𝙲𝟹  ·  Dust Particles`

### `Editor Return from PIE`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 3

### `Editor Tick`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `(real<double> Delta Time = 0.0)`
- Outputs: `(bool Completed)`
- Local variables: _none_
- Nodes: 33

### `Editor Update Season`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 7

### `EF - Update Custom Weather Particle Camera`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6
- Category: `𝙲𝟺  ·  Shared Particle Settings`

### `EF - Update Heat Distortion`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14
- Category: `𝙸𝟸  ·  Heat Distortion`
- Description: Updates the post process material for heat distortion when it is active

### `EF - Update Post Process Wind Fog`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables (1): `Force Update`
- Nodes: 40
- Category: `𝙷𝟻  ·  Post Process Wind Fog`
- Description: Moves the post process wind fog 3D noise samples with wind/particles, and updates its strength based on fog/weather. Also updates its directional occlusion values using current player occlusion.

### `EF - Update Rainbow`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 21
- Category: `𝙸𝟹  ·  Rainbow`
- Description: Changes Rainbow visibility with weather, and sets the visibility of the mesh.

### `EF - Update Screen Droplets`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 49
- Category: `𝙸𝟷  ·  Screen Droplets`
- Description: Checks weather and the camera's exposure to rain, and uses that to control intensity of drips/drops for the Screen Droplets effect.

### `EF - Update Screen Frost`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 32
- Category: `𝙸𝟺  ·  Screen Frost`

### `EF - Weather Occlusion Volume Update`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(bool Active)`
- Outputs: `()`
- Local variables (2): `Volume Corner`, `Trace Direction`
- Nodes: 38
- Category: `𝙼𝟸  ·  Weather Occlusion Volume`

### `Environment Sound Full Update`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `𝙶𝟷  ·  Sound Effects`

### `Environment Sound Hourly Update`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(int Hour)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙶𝟷  ·  Sound Effects`

### `Fade DLWE Target Over Time`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 27
- Category: `𝙵𝟸  ·  Dynamic Landscape Weather Effects`
- Description: Periodically called to either slowly fade snow compressions, or quickly fade puddle ripples.

### `Filter Probability Map`

- Access: `Protected`
- Flags: —
- Inputs: `(TMap<object<UDS_Weather_Settings_C,>>, real> Probability Map, object<UDS_Weather_Settings_C> Current Random Type)`
- Outputs: `(TMap<object<UDS_Weather_Settings_C,>>, real> Filtered Probability Map, TMap<object<UDS_Weather_Settings_C,>>, real> Filtered Probability Map, TMap<object<UDS_Weather_Settings_C,>>, real> Filtered Probability Map)`
- Local variables (2): `Weather Types to Filter`, `Map`
- Nodes: 68
- Category: `𝙳𝟸  ·  Random Weather Variation`
- Description: Filters a list of probabilities for weather presets, using the current rules limiting repeating or extreme changes.

### `Force Custom Weather Behavior Update`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 7

### `Full Reconstruction at Runtime`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10
- Category: `System`

### `Game User Settings Update`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `System`

### `General Weather Particle Direction`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> ReturnValue)`
- Local variables: _none_
- Nodes: 11
- Category: `𝙲𝟺  ·  Shared Particle Settings`

### `Generate Weather State At Location`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Location, object<UDS_Weather_Settings_C> Settings Object)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Get Weather Info`
- Description: Goes through all the logic for creating a local weather state for a specific location, as effected by Weather Override Volumes, Radial Storms, and Weather Over Volumetric Clouds. Can be used to query what the weather is like at a specific spot, regardless of what the local weather is around the player. It can also be used from a dedicated server to test what weather is like for a client at their location in the level. This needs a UDS Weather Settings object input into it, for the state to be set in. This should be an object which is constructed, not an asset on disk.

### `Get Control Point - Custom`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Player Movement`

### `Get Control Point - Player Camera`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Player Movement`

### `Get Control Point - Player Pawn`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6
- Category: `Player Movement`

### `Get Current Season`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Season)`
- Local variables: _none_
- Nodes: 3

### `Get Current Sound Occlusion Values`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Non-Directional Occlusion, real<double> X+ Occlusion, real<double> Y+ Occlusion, real<double> X- Occlusion, real<double> Y- Occlusion, real<double> Upward Occlusion)`
- Local variables: _none_
- Nodes: 7
- Category: `𝙶𝟸  ·  Sound Occlusion`
- Description: Can be used to sample UDW's current sound occlusion values

### `Get Current Temperature`

- Access: `Public`
- Flags: —
- Inputs: `(byte Sample Location = NewEnumerator0, struct<Vector> Custom Sample Location, byte Scale = NewEnumerator0)`
- Outputs: `(real<double> Output)`
- Local variables (3): `Unconverted Temperature`, `Occlusion Value`, `Sample Location Vector`
- Nodes: 73
- Category: `𝙺𝟷  ·  Temperature`
- Description: Uses the values in the Temperature category on UDW to determine a temperature using the current time and weather. Sample Location determines if localized effects are applied, like the Interior Temperature and Temperature Volumes. Read the tooltip for each option for more info.

### `Get Display Name for Current Weather`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(string As String, byte As Enumerator)`
- Local variables (1): `Chosen Enum`
- Nodes: 7
- Category: `Get Weather Info`
- Description: Finds a descriptor for the current weather state on Ultra Dynamic Weather. Note, this is not directly related to the weather settings objects informing the current state. For example, if the weather is transitioning from Clear Skies to Overcast, this function will not output either of those states in the middle of that transition. Instead, it would output something reasonable for the in between state like Partly Cloudy.

### `Get Dust Material Change Timing`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Coverage Duration, real<double> Clear Duration, real<double> Clear Speed (Windy), real<double> Clear Speed (No Wind))`
- Local variables: _none_
- Nodes: 6

### `Get Editor Control Point`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Editor`

### `Get Filtering Location`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArrayOwner_Interface.UDS_InterfaceActorArrayOwner_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> Filtering Location)`
- Local variables: _none_
- Nodes: 3

### `Get Global Temp Above Freezing`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Above Freezing)`
- Local variables: _none_
- Nodes: 7

### `Get Individual Seasons`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(TArray<real<double>> Seasons)`
- Local variables: _none_
- Nodes: 3

### `Get Next Random Weather and Timer Length`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_and_Weather_Override_Volume_Interface.UDW_and_Weather_Override_Volume_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `(object<Random_Weather_Variation_C> Random Weather Component)`
- Outputs: `(object<UDS_Weather_Settings_C> Next Preset, real<double> Timer Length)`
- Local variables (2): `Selected Next Preset`, `Current Timer Length`
- Nodes: 24

### `Get Normalized Wind Direction`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> Wind Vector)`
- Local variables: _none_
- Nodes: 4
- Category: `𝙷𝟷  ·  Wind Direction`
- Description: Outputs a unit vector pointing the current direction of the wind.

### `Get Projection Box Scene Capture 2D`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(object<SceneCaptureComponent2D> Out)`
- Local variables: _none_
- Nodes: 8
- Category: `𝙼𝟷  ·  Weather Mask Target`

### `Get Random Weather Forecast`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(TArray<object<UDS_Weather_Settings_C>> Upcoming Weather Objects, TArray<object<UDS_Weather_Settings_C>> Upcoming Weather Objects, TArray<object<UDS_Weather_Settings_C>> Upcoming Weather Objects, TArray<object<UDS_Weather_Settings_C>> Upcoming Weather Objects)`
- Local variables: _none_
- Nodes: 19
- Category: `𝙳𝟸  ·  Random Weather Variation`
- Description: Outputs the planned weather changes upcoming from random weather variation, if enabled. The size of the array will be set by Random Weather Forecast Steps. The array is in order with the first index being the next upcoming weather.

### `Get Random Weather Mode`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_and_Weather_Override_Volume_Interface.UDW_and_Weather_Override_Volume_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte Mode)`
- Local variables: _none_
- Nodes: 4

### `Get Random Weather Probability Maps`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_and_Weather_Override_Volume_Interface.UDW_and_Weather_Override_Volume_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(TMap<object<UDS_Weather_Settings_C,>>, real> Spring, TMap<object<UDS_Weather_Settings_C,>>, real> Summer, TMap<object<UDS_Weather_Settings_C,>>, real> Autumn, TMap<object<UDS_Weather_Settings_C,>>, real> Winter)`
- Local variables: _none_
- Nodes: 6

### `Get Season`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Season, byte Season Enum)`
- Local variables: _none_
- Nodes: 5
- Category: `𝙳𝟷  ·  Season`
- Description: Gets the Season float value and the current season (from the floored value) as an enum

### `Get Season Temperature Ranges`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_and_Weather_Override_Volume_Interface.UDW_and_Weather_Override_Volume_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector2D> Spring, struct<Vector2D> Summer, struct<Vector2D> Autumn, struct<Vector2D> Winter)`
- Local variables: _none_
- Nodes: 6

### `Get Snow Material Change Timing`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Coverage Duration, real<double> Melt Duration, real<double> Melt Speed (Above Freezing), real<double> Melt Speed (Below Freezing))`
- Local variables: _none_
- Nodes: 6

### `Get Sound Directional Occlusion`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(TArray<real<double>> Out)`
- Local variables: _none_
- Nodes: 11
- Category: `𝙶𝟸  ·  Sound Occlusion`

### `Get Sound Global Occlusion`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 9
- Category: `𝙶𝟸  ·  Sound Occlusion`

### `Get Sound Upward Occlusion`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 9
- Category: `𝙶𝟸  ·  Sound Occlusion`

### `Get Temperature Bias Settings`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Nighttime Bias, real<double> Daytime  Bias, real<double> Overcast Bias, real<double> Rain Bias, real<double> Snow Bias, real<double> Fog Bias, real<double> Dust Bias, real<double> Morning/Evening Bias)`
- Local variables: _none_
- Nodes: 10

### `Get UDS Values Controlled by UDW`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Cloud Coverage, real<double> Fog, real<double> Dust Amount, real<double> Cloud Direction, real<double> Wind Intensity, real<double> Rain, real<double> Snow, real<double> Fog Snow Contribution)`
- Local variables: _none_
- Nodes: 14

### `Get UDS Weather Override Bool`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Cloud Coverage, bool Fog, bool Dust)`
- Local variables: _none_
- Nodes: 5

### `Get UDW Current UDS Reference`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(object<Ultra_Dynamic_Sky_C> UDS)`
- Local variables: _none_
- Nodes: 6

### `Get UDW State for Saving`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<UDS_and_UDW_State> UDW State)`
- Local variables (1): `State`
- Nodes: 33

### `Get Weather Presets Used By Local Weather`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(TMap<object<UDS_Weather_Settings_C,>>, real> Sources)`
- Local variables: _none_
- Nodes: 4
- Category: `Get Weather Info`
- Description: Outputs a map of the weather presets contributing to the current local weather state. Each entry in the map has a float from 0 to 1 representing how much that weather object is affecting the weather. The total values should always add up to 1.

### `Get Weather Speed`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 3

### `Get Wetness Material Change Timing`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Coverage Duration, real<double> Dry Duration, real<double> Dry Speed (Sunny), real<double> Dry Speed (Cloudy), real<double> Snow Melt Contributes to Wetness)`
- Local variables: _none_
- Nodes: 7

### `Get Wind Speed in Real Units`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Knots at Wind Intensity 10 = 38.000000, bool Factor Wind Gusts = false)`
- Outputs: `(real<double> Knots, real<double> MPH, real<double> KPH)`
- Local variables (1): `Speed Knots`
- Nodes: 21
- Category: `Get Weather Info`
- Description: Gets the wind speed approximated as real world units (knots, MPH, KPH) The input Knots at Wind Intensity 10 can be used to recalibrate this calculation higher or lower, if you've configured wind forces and effects to represent a different level of wind at a Wind Intensity value of 10. The input Factor Wind Gusts applies the wind gust multiplier. See the documentation on Wind Gusts for information on that.

### `Global State Update - Apply Manual Weather`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(object<UDS_Weather_Settings_C> Target State Object)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13
- Category: `Global State Update`

### `Global State Update - Apply Random Weather`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(object<UDS_Weather_Settings_C> Target State Object)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15
- Category: `Global State Update`

### `Global State Update - Apply Static Preset`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(object<UDS_Weather_Settings_C> Target State Object)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12
- Category: `Global State Update`

### `Global State Update - Apply Transition`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(object<UDS_Weather_Settings_C> Target State Object)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 30
- Category: `Global State Update`

### `Global State Update - Increment Material State`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(object<UDS_Weather_Settings_C> Target State Object)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Global State Update`

### `Ground UDW Actor`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9
- Category: `Startup`

### `Hide Weather`

- Access: `Public`
- Flags: —
- Inputs: `(bool Hide Entire Actor, bool Hide Weather Particles, bool Hide Post Process Effects)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 34
- Category: `Utility Functions`
- Description: At runtime, use to hide/show the entire weather actor, or specific elements like weather particles/post process effects/etc Note the visible components being hidden won't affect sound effects. To toggle those at runtime, call "Set Enable Weather Sound Effects"

### `Hourly Season Update`

- Access: `Protected`
- Flags: —
- Inputs: `(int Hour)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `𝙳𝟷  ·  Season`

### `Impact Snow/ Puddle/ Dust at Location`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Location, real<double> Radius = 24.000000)`
- Outputs: `()`
- Local variables (6): `Puddle Actor`, `Hit Puddle Fluid Volume`, `Landscape Hit`, `Puddle Hit`, `Snow/Dust Hit`, `DLWE One Shot Class`
- Nodes: 7
- Category: `𝙵𝟸  ·  Dynamic Landscape Weather Effects`
- Description: Can be used to make something like a projectile do a one time interaction effect against DLWE snow/dust/puddles, and Puddle Fluid Volumes as well.

### `Increment Extra Feature Intensity`

- Access: `Protected`
- Flags: —
- Inputs: `(real<double>& Target Intensity [ref], real<double>& Current Intensity [ref], real<double> Interp Speed Up, real<double> Interp Speed Down)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 22
- Category: `Extra Features`

### `Increment Wind Direction Transition`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 23
- Category: `𝙷𝟷  ·  Wind Direction`
- Description: Called every frame during a transition of wind direction, after "Change Wind Direction" is called by the user

### `Initialize Random Weather Variation`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 27
- Category: `𝙳𝟸  ·  Random Weather Variation`
- Description: If enabled, starts up the random weather variation component and sets variable for weather state based on its starting state

### `Instant Environment Sound Update`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11
- Category: `𝙶𝟷  ·  Sound Effects`

### `Instant Sound Update`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14
- Category: `𝙶𝟷  ·  Sound Effects`

### `Level Editor WOV Update`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13
- Category: `𝙻𝟸  ·  Weather Override Volumes`

### `Lightning Bolt Target Offset`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> Out)`
- Local variables: _none_
- Nodes: 13
- Category: `𝙴𝟷  ·  Lightning`
- Description: Determines the current target offset for the lightning niagara effect. The target offset is where the lightning bolt will strike, relative to where it starts.

### `Lightning Distance Range`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Range)`
- Local variables: _none_
- Nodes: 12
- Category: `𝙴𝟷  ·  Lightning`
- Description: Turns the distance from the current lightning flash to the camera into a normalized 0 to 1 range, from min to max lightning distance.

### `Lightning Flash Location`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Found Valid Location, struct<Vector> Loc, bool Found Valid Location, struct<Vector> Loc, bool Found Valid Location, struct<Vector> Loc, bool Found Valid Location, struct<Vector> Loc, bool Found Valid Location, struct<Vector> Loc)`
- Local variables (2): `Valid Location`, `Current Tested Location`
- Nodes: 55
- Category: `𝙴𝟷  ·  Lightning`
- Description: Generates a location for the current lightning flash to spawn at

### `Lightning Flash Spawning`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 27
- Category: `𝙴𝟷  ·  Lightning`

### `Lightning Intensity Day/Night Scale`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 7
- Category: `𝙴𝟷  ·  Lightning`

### `Lightning World Height`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Height)`
- Local variables: _none_
- Nodes: 6
- Category: `𝙴𝟷  ·  Lightning`
- Description: The height at which lightning should spawn

### `Load Soft Object Array`

- Access: `Protected`
- Flags: —
- Inputs: `(TArray<softobject<Object>> In)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `Startup`

### `Local State Update - Apply Manual Overrides`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(object<UDS_Weather_Settings_C> Target State Object, struct<Vector> Local Weather Location)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 17
- Category: `Local State Update`

### `Local State Update - Changes Above Cloud Layer`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(object<UDS_Weather_Settings_C> Target State Object, struct<Vector> Local Weather Location)`
- Outputs: `()`
- Local variables (2): `Above Clouds`, `State Object`
- Nodes: 60
- Category: `Local State Update`
- Description: Applies the selected changes to Local Weather State when the camera is above the volumetric cloud layer.

### `Local State Update - Copy Global to Local`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(object<UDS_Weather_Settings_C> Target State Object, struct<Vector> Local Weather Location)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Local State Update`

### `Local State Update - Wind Direction Variation`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `(object<UDS_Weather_Settings_C> Target State Object, struct<Vector> Local Weather Location)`
- Outputs: `()`
- Local variables (1): `Variation Time`
- Nodes: 27
- Category: `Local State Update`

### `Make Dust Component`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 18
- Category: `𝙲𝟹  ·  Dust Particles`

### `Make Lightning Flash Systems`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14
- Category: `𝙴𝟷  ·  Lightning`

### `Make Manual State`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13
- Category: `Weather State`
- Description: Sets the contents of the Manual Weather State object using the manual weather state variables.

### `Make Obscured Lightning Component`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13
- Category: `𝙴𝟷  ·  Lightning`

### `Make Outdoor Sound Mix`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15
- Category: `𝙶𝟷  ·  Sound Effects`
- Description: Creates the sound mix modifier to adjust volume with occlusion for the UDS Outdoor Sound class.

### `Make Post Process Component for Extra Feature`

- Access: `Protected`
- Flags: —
- Inputs: `(object<PostProcessComponent>& Component [ref], object<MaterialInterface> Parent Material, object<MaterialInstanceDynamic>& MID [ref], bool Show in Editor)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 23
- Category: `Extra Features`

### `Make Rain Component`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 18
- Category: `𝙲𝟷  ·  Rain Particles`

### `Make Random Stream`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Startup`

### `Make Snow Component`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 18
- Category: `𝙲𝟸  ·  Snow Particles`

### `Make Weather State Hash`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(TArray<int> Hash Array)`
- Local variables: _none_
- Nodes: 36
- Category: `Change Monitoring`

### `Make Wind Debris Component`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 18
- Category: `𝙷𝟹  ·  Wind Debris`

### `Manual Override to State Value`

- Access: `Protected`
- Flags: —
- Inputs: `(object<UDS_Weather_Settings_C> Target, int Index)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 33
- Category: `Weather State`

### `Material Effect Draw Color from State`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Weather_Settings_C> State, real<double> Alpha)`
- Outputs: `(struct<LinearColor> Color)`
- Local variables: _none_
- Nodes: 13
- Category: `𝙻𝟸  ·  Weather Override Volumes`

### `Monitor Local Weather Changes`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (4): `New Hash Array`, `Value Change`, `Current Value Index`, `Called Instant Change`
- Nodes: 56
- Category: `Change Monitoring`
- Description: Look at this tick's local weather state compared to last tick, to determine which aspects of the weather require updates

### `Obscured Lightning Current Spawn Rate`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 8
- Category: `𝙴𝟷  ·  Lightning`

### `Obscured Lightning System Finished`

- Access: `Protected`
- Flags: —
- Inputs: `(object<NiagaraComponent> PSystem)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙴𝟷  ·  Lightning`

### `OnRep_Enable Dust Particles`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

### `OnRep_Enable Heat Distortion`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

### `OnRep_Enable Obscured Lightning`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

### `OnRep_Enable Post Process Wind Fog`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

### `OnRep_Enable Radial Storm Spawning`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

### `OnRep_Enable Rain Particles`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

### `OnRep_Enable Rainbow`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12

### `OnRep_Enable Screen Droplets`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

### `OnRep_Enable Screen Frost`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

### `OnRep_Enable Snow Particles`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

### `OnRep_Enable Weather Sound Effects`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

### `OnRep_Enable Wind Camera Shake`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

### `OnRep_Enable Wind Debris`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

### `OnRep_Manual Heat Distortion`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

### `OnRep_Manual Screen Frost`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

### `OnRep_Wind Debris Particle Spawn Count`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

### `Open Editor Readme Entry`

- Access: `Protected`
- Flags: —
- Inputs: `(string Entry Row)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `Editor`

### `Open Editor Readme Entry Set`

- Access: `Protected`
- Flags: —
- Inputs: `(TArray<name>& Entries [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `Editor`

### `Populate Runtime Config Properties`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Weather_Configuration_C> Configuration)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 78
- Category: `Configuration`

### `Query Project Settings`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 16
- Category: `Startup`

### `Rain Niagara System Asset`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(softobject<NiagaraSystem> Out)`
- Local variables: _none_
- Nodes: 3
- Category: `𝙲𝟷  ·  Rain Particles`

### `Rain Spawn Rate`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 10
- Category: `𝙲𝟷  ·  Rain Particles`

### `Rain System Finished`

- Access: `Protected`
- Flags: —
- Inputs: `(object<NiagaraComponent> PSystem)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `𝙲𝟷  ·  Rain Particles`

### `Recenter DLWE Render Target`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `Canvas`, `Target Size`
- Nodes: 40
- Category: `𝙵𝟸  ·  Dynamic Landscape Weather Effects`
- Description: Draws the render target to itself at an offset from the center so that the render target area can be moved proportionally.

### `Report Removal Of Mask Component`

- Access: `Public`
- Flags: —
- Inputs: `(object<WeatherMask_C> Component)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙼𝟷  ·  Weather Mask Target`
- Description: Run by the mask actors and weather override volumes, to report to UDW that they are being removed from the level.

### `Reset Last Weather Hash Values`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Change Monitoring`

### `Runtime or Initializing`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 4
- Category: `System`

### `Screen Droplets Periodic Updates`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `Pawn in Array`, `Trace Direction`
- Nodes: 50
- Category: `𝙸𝟷  ·  Screen Droplets`
- Description: Runs periodically when screen droplets are active, to do the line trace from the camera in the direction of the rain and check exposure of the camera to the rain.

### `Second Frame Startup Functions`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9
- Category: `Startup`
- Description: Functions which require a frame of latency after startup before they should be run.

### `Select Random Weather Type`

- Access: `Protected`
- Flags: —
- Inputs: `(TMap<object<UDS_Weather_Settings_C,>>, real> Probability Map)`
- Outputs: `(object<UDS_Weather_Settings_C> Selected Preset)`
- Local variables (5): `Current Probabilities`, `Random Max Range`, `Random Float`, `Threshold`, `Selected Weather`
- Nodes: 36
- Category: `𝙳𝟸  ·  Random Weather Variation`
- Description: Finds a new weather state from the probability map

### `Set Enable Dust Particles`

- Access: `Public`
- Flags: —
- Inputs: `(bool Enabled)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙲𝟹  ·  Dust Particles`
- Description: For turning the dust particles on/off at runtime if needed

### `Set Enable Heat Distortion`

- Access: `Public`
- Flags: —
- Inputs: `(bool Enabled)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙸𝟸  ·  Heat Distortion`
- Description: For turning Heat Distortion on/off at runtime

### `Set Enable Obscured Lightning`

- Access: `Public`
- Flags: —
- Inputs: `(bool Enabled)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙴𝟷  ·  Lightning`
- Description: For turning the obscured lightning particles on/off at runtime if needed

### `Set Enable Post Process Wind Fog`

- Access: `Public`
- Flags: —
- Inputs: `(bool Enabled)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙷𝟻  ·  Post Process Wind Fog`
- Description: For turning the Post Process Wind Fog on/off at runtime

### `Set Enable Radial Storm Spawning`

- Access: `Public`
- Flags: —
- Inputs: `(bool Enabled)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙳𝟹  ·  Radial Storm Spawning`
- Description: For turning the Radial Storm Spawning on/off at runtime

### `Set Enable Rain Particles`

- Access: `Public`
- Flags: —
- Inputs: `(bool Enabled)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙲𝟷  ·  Rain Particles`
- Description: For turning the rain particles on/off at runtime if needed

### `Set Enable Rainbow`

- Access: `Public`
- Flags: —
- Inputs: `(bool Enabled)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙸𝟹  ·  Rainbow`
- Description: For turning the Rainbow on/off at runtime

### `Set Enable Screen Droplets`

- Access: `Public`
- Flags: —
- Inputs: `(bool Enabled)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙸𝟷  ·  Screen Droplets`
- Description: For turning the Screen Droplets on/off at runtime

### `Set Enable Screen Frost`

- Access: `Public`
- Flags: —
- Inputs: `(bool Enabled)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙸𝟺  ·  Screen Frost`
- Description: For turning the Screen Frost on/off at runtime

### `Set Enable Snow Particles`

- Access: `Public`
- Flags: —
- Inputs: `(bool Enabled)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙲𝟸  ·  Snow Particles`
- Description: For turning the snow particles on/off at runtime if needed

### `Set Enable Weather Sound Effects`

- Access: `Public`
- Flags: —
- Inputs: `(bool Enabled)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙶𝟷  ·  Sound Effects`
- Description: For turning the Weather Sound Effects on/off at runtime

### `Set Enable Wind Camera Shake`

- Access: `Public`
- Flags: —
- Inputs: `(bool Enabled)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙷𝟼  ·  Wind Camera Shake`
- Description: For turning the Wind Camera Shake on/off at runtime

### `Set Enable Wind Debris`

- Access: `Public`
- Flags: —
- Inputs: `(bool Enabled)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙷𝟹  ·  Wind Debris`
- Description: For turning the wind debris particles on/off at runtime if needed

### `Set Enabled Niagara System`

- Access: `Protected`
- Flags: —
- Inputs: `(bool Enabled, object<NiagaraComponent> System)`
- Outputs: `(bool Turned On, bool Turned On)`
- Local variables: _none_
- Nodes: 11
- Category: `𝙲𝟺  ·  Shared Particle Settings`

### `Set Random Time Offset`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6
- Category: `Startup`

### `Set Replicated Old Weather State`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6
- Category: `Weather State`
- Description: Sets the "Old" replicated weather state. This is the state the transition system uses as the A when interpolating to the B state.

### `Set Season`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Season)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `𝙳𝟷  ·  Season`
- Description: Sets the Season value (changing Season Mode to Manual Setting if necessary) and updating the season effects on materials and weather

### `Set Shared Weather Particle Parameters`

- Access: `Protected`
- Flags: —
- Inputs: `(object<NiagaraComponent> System)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 80
- Category: `𝙲𝟺  ·  Shared Particle Settings`
- Description: Sets parameters which are used by all of the weather particle niagara systems in the same way.

### `Set UDS Reference`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `UDS Connection`
- Description: If the UDS reference is not valid, gets a reference if one can be found

### `Set WOV Render Target Mapping`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15
- Category: `𝙻𝟸  ·  Weather Override Volumes`
- Description: Updates the vector parameter which controls where the WOV target is being mapped, and also has the volumes themselves update their canvas space geometry, for drawing to the target.

### `Sky Cloud Speed`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 8
- Category: `UDS Connection`

### `Snow Niagara System Asset`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(softobject<NiagaraSystem> Out)`
- Local variables: _none_
- Nodes: 3
- Category: `𝙲𝟸  ·  Snow Particles`

### `Snow Spawn Rate`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 11
- Category: `𝙲𝟸  ·  Snow Particles`

### `Snow System Finished`

- Access: `Protected`
- Flags: —
- Inputs: `(object<NiagaraComponent> PSystem)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `𝙲𝟸  ·  Snow Particles`

### `Sparse Movement Updates`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Distance Moved`
- Nodes: 18
- Category: `Player Movement`
- Description: Runs updates which only need to be run when the control point location has moved a significant amount. Used for things like render target recentering.

### `Spawn Radial Storm`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (10): `Spawn Direction`, `Start Location`, `End Location`, `Weather Preset Map`, `Spawn Origin`, `Lifetime`, `Selected Weather`, `Random Range Size`, `Random Value`, `Threshold`
- Nodes: 104
- Category: `𝙳𝟹  ·  Radial Storm Spawning`
- Description: Spawns a single radial storm and sets a timer to spawn the next one

### `Start Lightning Flash`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Lightning Niagara System`
- Nodes: 173
- Category: `𝙴𝟷  ·  Lightning`
- Description: Called in the Lightning Flash graph. Starts the niagara system, sound, and light effects for the lightning flash

### `Start Monitoring Player Controller for Pawn`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10
- Category: `Startup`

### `Start Up DLWE Interaction System`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 38
- Category: `𝙵𝟸  ·  Dynamic Landscape Weather Effects`

### `Start Up Environment Sound`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `𝙶𝟷  ·  Sound Effects`

### `Start Up Radial Storm Spawning`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 18
- Category: `𝙳𝟹  ·  Radial Storm Spawning`

### `Start Up Render Targets`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8
- Category: `Startup`

### `Start Up Wind Camera Shake`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6
- Category: `𝙷𝟼  ·  Wind Camera Shake`

### `Start Weather System`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 77
- Category: `Startup`
- Description: Starts the weather system up. Used both from construction script and begin play.

### `Static Properties - DLWE`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 22
- Category: `𝙵𝟸  ·  Dynamic Landscape Weather Effects`
- Description: Applies shared material parameters for the DLWE effects which don't change with weather

### `Static Properties - Dust`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 36
- Category: `𝙲𝟹  ·  Dust Particles`
- Description: Sets up dust niagara system and applies settings which don't change with weather.

### `Static Properties - Heat Distortion`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 50
- Category: `𝙸𝟸  ·  Heat Distortion`
- Description: Creates post process settings and a dynamic material instance for the heat distortion effect

### `Static Properties - Lightning`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 102
- Category: `𝙴𝟷  ·  Lightning`
- Description: Applies settings to lightning flashes and obscured lightning which don't change with weather.

### `Static Properties - Material Effects`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15
- Category: `𝙵𝟷  ·  Material Effects`

### `Static Properties - Post Process Wind Fog`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Parent Mat`
- Nodes: 60
- Category: `𝙷𝟻  ·  Post Process Wind Fog`
- Description: Sets up the Post Process Wind Fog effect

### `Static Properties - Rain`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 105
- Category: `𝙲𝟷  ·  Rain Particles`
- Description: Sets up rain niagara system and applies settings which don't change with weather.

### `Static Properties - Rainbow`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 43
- Category: `𝙸𝟹  ·  Rainbow`
- Description: Sets up the rainbow mesh and material

### `Static Properties - Rendering Cvars`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 39
- Category: `Renderer`

### `Static Properties - Screen Droplets`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 33
- Category: `𝙸𝟷  ·  Screen Droplets`
- Description: Creates the dynamic material instance and assigns it to the post component for the screen droplets.

### `Static Properties - Screen Frost`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 56
- Category: `𝙸𝟺  ·  Screen Frost`

### `Static Properties - Shared Particles`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12
- Category: `𝙲𝟺  ·  Shared Particle Settings`
- Description: Applies shared particle settings which don't change with weather

### `Static Properties - Snow`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 44
- Category: `𝙲𝟸  ·  Snow Particles`
- Description: Sets up snow niagara system and applies settings which don't change with weather.

### `Static Properties - Sound Effects`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Spatialization`
- Nodes: 39
- Category: `𝙶𝟷  ·  Sound Effects`
- Description: Sets up the sound effect components and the sounds they play

### `Static Properties - Weather Occlusion Volume`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Clear System`
- Nodes: 46
- Category: `𝙼𝟸  ·  Weather Occlusion Volume`

### `Static Properties - Wind Debris`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 31
- Category: `𝙷𝟹  ·  Wind Debris`
- Description: Sets up wind debris niagara system and applies settings which don't change with weather.

### `Static Properties - Wind Directional Source`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15
- Category: `𝙷𝟺  ·  Wind Directional Source`

### `Test Actor for Weather Exposure`

- Access: `Public`
- Flags: —
- Inputs: `(object<Actor> Actor, bool Test Colliding Components Only = true, object<SceneComponent> Custom Component for Bounds, byte Trace Channel = TraceTypeQuery1)`
- Outputs: `(real<double> Rain Exposure, real<double> Snow Exposure, real<double> Wind Exposure, real<double> Dust Exposure)`
- Local variables (4): `Actor Origin`, `Actor Extent`, `Weather Exposure`, `Wind Direction Exposure`
- Nodes: 48
- Category: `Test Actors`
- Description: Takes in an Actor reference and performs traces based on the actor's bounds, to roughly approximate, based on the current weather, how exposed the actor is to rain, snow, and wind. The outputs are all on a range from 0 to 1.

### `Test Component for Wind Exposure`

- Access: `Public`
- Flags: —
- Inputs: `(object<PrimitiveComponent> Component)`
- Outputs: `(real<double> Wind Exposure)`
- Local variables: _none_
- Nodes: 10
- Category: `Test Actors`
- Description: Tests a single primitive component's bounds using line traces, to see how much wind is hitting it.

### `Tick Random Weather System`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `𝙳𝟸  ·  Random Weather Variation`

### `Trace Bounds for Exposure Values`

- Access: `Protected`
- Flags: —
- Inputs: `(struct<Vector> Bounds Origin, struct<Vector> Bounds Extent, TArray<object<Actor>> Actors to Ignore, byte Trace Channel = TraceTypeQuery1)`
- Outputs: `(real<double> Exposure Value)`
- Local variables (3): `Exposure`, `Current Trace Origin`, `Current Vector`
- Nodes: 31
- Category: `Test Actors`
- Description: Used by utility functions to test how exposed a set of bounds is to weather or wind

### `UDS Weather Variable Overrides`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `(bool Override Clouds = false, real<double> Cloud Coverage = 0.0, bool Override Fog = false, real<double> Fog = 0.0, bool Override Dust = false, real<double> Dust = 0.0)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 23

### `UDW State Apply`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `(struct<UDS_and_UDW_State> State)`
- Outputs: `(bool Completed)`
- Local variables: _none_
- Nodes: 59

### `Update Active Variables`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Update`
- Description: Updates the parameters for weather and niagara systems which change at runtime.

### `Update Current Global And Local Weather State`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 33
- Category: `Weather State`
- Description: Sets the global and local weather state based on all possible sources of weather

### `Update DLWE Snow Compressions`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (9): `RenderCanvas`, `Render Context`, `Int Location`, `Int Size`, `Absolute Interaction Depth`, `Deep Snow Alpha`, `Depth Fraction`, `BrushSize`, `Heading Angle`
- Nodes: 84
- Category: `𝙵𝟸  ·  Dynamic Landscape Weather Effects`
- Description: Takes the buffer of compressions since last update and uses them to draw into the render target.

### `Update Environment Sound Time Integer`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (3): `Sunrise Time`, `Sunset Time`, `Wrapped Time`
- Nodes: 44
- Category: `𝙶𝟷  ·  Sound Effects`

### `Update Environment Sound Weather Integer`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 18
- Category: `𝙶𝟷  ·  Sound Effects`

### `Update Environment Sound Wind Integer`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11
- Category: `𝙶𝟷  ·  Sound Effects`

### `Update Lightning Flash Light`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Overall Intensity`
- Nodes: 72
- Category: `𝙴𝟷  ·  Lightning`

### `Update Material Effect Parameters`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 28
- Category: `𝙵𝟷  ·  Material Effects`
- Description: Sets the shared material parameters for things like wetness and snow coverage, to be used on the material functions.

### `Update Player Pawn Reference`

- Access: `Protected`
- Flags: —
- Inputs: `(object<Pawn> OldPawn, object<Pawn> NewPawn)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `Player Movement`

### `Update Season`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 97
- Category: `𝙳𝟷  ·  Season`
- Description: Gets the season value from UDS if that option is enabled. Also turns the season value into the color parameter for UDW Seasons, to be sampled in materials.

### `Update Sound Occlusion Parameters`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `Directional Occlusion`, `Upward Occlusion`
- Nodes: 34
- Category: `Active Binding`
- Description: Applies the current sound occlusion values to the audio components

### `Update Static Variables`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 24
- Category: `Update`
- Description: Sets properties and prepares components with values that don't change with the weather.

### `Update Underwater State`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 38
- Category: `𝙹𝟷  ·  Water Level`
- Description: Runs when the camera goes under the water level or emerges from it

### `Update Weather Mask Target`

- Access: `Public`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables (13): `Mask Canvas`, `Mask Context`, `Brush Components`, `Projection Box Components`, `Current Projection Box`, `Brush Heights`, `Mask Components`, `Current Index`, `Lowest Brush Height`, `New Location`, `Brush`, `Height Canvas`, `Height Context`
- Nodes: 92
- Category: `Active Binding`
- Description: Draws the render target used for the Weather Mask Brushes, and sampled in the weather effect material functions.

### `Update Weather Occlusion Trace Direction`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `New Direction`, `Constant Updates`
- Nodes: 24
- Category: `𝙼𝟸  ·  Weather Occlusion Volume`

### `Update Weather Particles Parent Location`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Update`

### `Update Wind Gust Multiplier`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 38
- Category: `𝙷𝟸  ·  Wind Gusts`

### `Update WOV Render Target`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (4): `Render Canvas`, `New Mapping`, `Draw Context`, `Draw Actors Present`
- Nodes: 46
- Category: `𝙻𝟸  ·  Weather Override Volumes`
- Description: Redraws the target used by the weather override volumes, to have local control of material effects

### `Warm Up Niagara Systems`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Should Warm Up`
- Nodes: 76
- Category: `𝙲𝟺  ·  Shared Particle Settings`
- Description: Advance the niagara systems to update them instantly with particles. An expensive operation.

### `Wind Debris Niagara System Asset`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(softobject<NiagaraSystem> Out)`
- Local variables: _none_
- Nodes: 3
- Category: `𝙷𝟹  ·  Wind Debris`

### `Wind Debris Spawn Rate`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 10
- Category: `𝙷𝟹  ·  Wind Debris`

### `Wind Debris System Finished`

- Access: `Protected`
- Flags: —
- Inputs: `(object<NiagaraComponent> PSystem)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `𝙷𝟹  ·  Wind Debris`

### `Wind Force Vector`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> ReturnValue)`
- Local variables: _none_
- Nodes: 14
- Category: `𝙷𝟷  ·  Wind Direction`

### `Wind Rotation`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Rotator> Rot)`
- Local variables: _none_
- Nodes: 5
- Category: `𝙷𝟷  ·  Wind Direction`
- Description: Derives a rotator from the current wind direction

### `📘 Dust Particles`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `𝙲𝟹  ·  Dust Particles`

### `📘 Dynamic Landscape Weather Effects`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙵𝟸  ·  Dynamic Landscape Weather Effects`

### `📘 Event Dispatchers`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙽𝟷  ·  Event Dispatchers`

### `📘 Heat Distortion`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙸𝟸  ·  Heat Distortion`

### `📘 Lightning`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙴𝟷  ·  Lightning`

### `📘 Manual Weather State`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙱𝟷  ·  Manual Weather State`

### `📘 Material Effects`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `𝙵𝟷  ·  Material Effects`

### `📘 Post Process Wind Fog`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙷𝟻  ·  Post Process Wind Fog`

### `📘 Radial Storms`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙳𝟹  ·  Radial Storm Spawning`

### `📘 Rain Particles`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `𝙲𝟷  ·  Rain Particles`

### `📘 Rainbow`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙸𝟹  ·  Rainbow`

### `📘 Random Weather Variation`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙳𝟸  ·  Random Weather Variation`

### `📘 Screen Droplets`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙸𝟷  ·  Screen Droplets`

### `📘 Screen Frost`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙸𝟺  ·  Screen Frost`

### `📘 Season`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙳𝟷  ·  Season`

### `📘 Snow Particles`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `𝙲𝟸  ·  Snow Particles`

### `📘 Sound Effects`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `𝙶𝟷  ·  Sound Effects`

### `📘 Sound Occlusion`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙶𝟸  ·  Sound Occlusion`

### `📘 Temperature`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙺𝟷  ·  Temperature`

### `📘 Water Level`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙹𝟷  ·  Water Level`

### `📘 Weather Above Volumetric Clouds`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙻𝟷  ·  Weather Above Volumetric Clouds`

### `📘 Weather Documentation`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `𝙰𝟷  ·  Basic Controls`

### `📘 Weather Mask Tools`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙼𝟷  ·  Weather Mask Target`

### `📘 Weather Occlusion Volume`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙼𝟸  ·  Weather Occlusion Volume`

### `📘 Weather Override Volumes`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙻𝟸  ·  Weather Override Volumes`

### `📘 Weather Particles`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `𝙲𝟺  ·  Shared Particle Settings`

### `📘 Wind Camera Shake`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙷𝟼  ·  Wind Camera Shake`

### `📘 Wind Debris`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙷𝟹  ·  Wind Debris`

### `📘 Wind Direction`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙷𝟷  ·  Wind Direction`

### `📘 Wind Directional Source`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙷𝟺  ·  Wind Directional Source`

### `📘 Wind Gusts`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙷𝟸  ·  Wind Gusts`

## Macros (11)

### `Runtime Config Bool Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 57

### `Runtime Config Byte Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13

### `Runtime Config Color Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11

### `Runtime Config Float Range Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

### `Runtime Config Float Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 231

### `Runtime Config Hard Object Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

### `Runtime Config Integer Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12

### `Runtime Config Soft Class Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4

### `Runtime Config Soft Object Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

### `Runtime Config Vector Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

### `Runtime Config Vector2D Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7

## Components (7)

- `Random Weather Manager` — `Random_Weather_Variation_C` @ socket `None`
- `Material State Manager` — `UDW_Material_State_Manager_C` @ socket `None`
- `Temperature Manager` — `UDW_Temperature_Manager_C` @ socket `None`
- `WeatherRoot` — `SceneComponent` @ socket `None`
  - `Sound_Global` — `AudioComponent` @ socket `None`
  - `Lightning Light` — `DirectionalLightComponent` @ socket `None`
    - `LightningFlashBloom` — `PostProcessComponent` @ socket `None`
  - `Sound_Directional` — `AudioComponent` @ socket `None`
  - `UDW Label` — `StaticMeshComponent` @ socket `None`
  - `Sound_Mixer` — `AudioComponent` @ socket `None`
  - `WeatherParticles_Parent` — `SceneComponent` @ socket `None`
    - `SelectionHide` — `StaticMeshComponent` @ socket `None`
  - `StatusDisk` — `StaticMeshComponent` @ socket `None`
  - `Wind_Arrow` — `StaticMeshComponent` @ socket `None`
- `Local Weather Actors Manager` — `UDS_InterfaceActorArrayManager_C` @ socket `None`
- `WOV Target Draw Actors Manager` — `UDS_InterfaceActorArrayManager_C` @ socket `None`
- `UDS_Utility_Opener` — `UDS_Utility_Opener_C` @ socket `None`

## Class Default Object (7)

- `ActorLabel` (`FString`) = `Ultra_Dynamic_Sky_Weather-1`
- `bAlwaysRelevant` (`uint8`) = `True`
- `bEnableAutoLODGeneration` (`uint8`) = `False`
- `bIsSpatiallyLoaded` (`uint8`) = `False`
- `bRelevantForLevelBounds` (`uint8`) = `False`
- `bReplicates` (`uint8`) = `True`
- `PrimaryActorTick` (`FActorTickFunction`) = `(TickGroup=TG_PostPhysics,bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (217 nodes)
- Construction script: `UserConstructionScript` (17 nodes)
- Additional graphs: _none_

## References

Hard refs out (125):
- `/Engine/EditorBlueprintResources/ActorMacros` [asset]
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Engine/EditorResources/AudioIcons/S_AudioComponent` [asset]
- `/Engine/EditorResources/AudioIcons/S_AudioComponent_AutoActivate` [asset]
- `/Engine/EditorResources/LightIcons/S_LightError` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_ComparisonType` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_ControlPointMode` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_LightningBloomMode` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Occlusion_Water_Behavior` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Particle_Collision_Mode` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_PPWF_MaskMode` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Project_Mode` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Rain_Splash_RenderMode` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_RandomWeatherTiming` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_RenderingFeatureLevel` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_RunContext` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Season` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_SeasonMode` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_SkyMode` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Temperature_Sample_Location` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_TemperatureType` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Weather_Display_Names` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Functions/UltraDynamicSky_Functions` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/Editor_Materials/UDS_Compass_Material` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/Editor_Materials/UDS_EditorLabel` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/Editor_Materials/UDW_StatusDisk_Material` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_CurrentVersion` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_VersionInfo` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/RandomWeatherVariation_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_and_UDW_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Calendar` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Environment_Sound` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArrayManager` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArrayOwner_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Modifier` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_RenderTarget_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_SharedConfig` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Weather_Configuration` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Components/Weather_Mask_Brush_Component` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Components/Weather_Mask_Projection_Box_Component` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Radial_Storm` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/DLWE_OneShot_Interaction` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Radial_Storm_Weather_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Random_Weather_Variation` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Temperature_Volume_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Climate_Preset` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_and_Weather_Override_Volume_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Dispatcher_Tunnel` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_DispatcherTunnelAsset` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_LightningStrikableActorInterface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Local_Weather_Actor_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Material_State_Manager` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Temperature_Manager` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Temperature_Manager_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WeatherState_Structure` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Wind_Camera_Shake` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WOV_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WOVTarget_Draw_Actor_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/WeatherMask` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/WeatherMaskComponentInterface` [asset]
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
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/DLWE_Trail_Brush` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Heat_Distortion` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/LightningFlashBloom_PP` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Post_Process_Wind_Fog` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Post_Process_Wind_Fog_Composite` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Post_Process_Wind_Fog_Legacy` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Radial_Storm_Weather_Draw` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Rainbow_Mat` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Screen_Droplets` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Screen_Frost` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Snow_Fade_Target_Mat` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Splash_Droplet_Particle` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Splash_Droplet_Particle_Translucent` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Splash_ParticleMat` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Splash_ParticleMat_Translucent` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/UltraDynamicWeather_Parameters` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/WeatherMaskHeightDraw` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/WOV_Target_Brush` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/EditorLabels/ClockDisk` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/EditorLabels/UDW_Text` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/EditorLabels/Wind_Arrow` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/Nebula_Sphere` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/Rainbow` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Particles/Clear_WeatherOcclusionVolume` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Particles/Dust` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Particles/Lightning_Strike` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Particles/Obscured_Lightning` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Particles/Rain` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Particles/Snow` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Particles/UDW_WeatherParticle_Parameters` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Particles/WeatherOcclusionVolumeSystem` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Particles/Wind_Debris` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Sound/MetaSounds/UDS_Directional_WeatherSounds` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Sound/MetaSounds/UDS_Global_WeatherSounds` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Sound/MetaSounds/UDS_WeatherSoundMixer` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Sound/UDS_Outdoor_Sound` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Weather/Debris_Twigs_and_Leaves` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Weather/DLWE_MaskTarget` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Weather/Frost_Scatter` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Weather/Snow_Normal` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Weather/Weather_Mask_Brush_Target` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Weather/Weather_Mask_Height_Target` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Weather/WOV_Material_State_Target` [asset]
- `/Script/AudioExtensions` [asset]
- `/Script/Engine.Actor` [native]
- `/Script/MetasoundEngine` [asset]
- `/Script/Niagara` [asset]
- `/Script/PhysicsCore` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

