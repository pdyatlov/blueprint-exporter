# Replication Matrix

Every replicated member across the Phase-1 scope. The single most valuable document for the Steam Relay playtest workstream (brief §5).

Kinds: `Var` (UPROPERTY(Replicated)/RepNotify), `RPC` (functions with Server/Client/NetMulticast + optional Reliable flags). RPC rows are sourced from M3.2's net-exec flag extension on `FExportedFunctionFlags`.

Total rows: **98** (vars: 98, RPCs: 0)

| Asset | Member | Kind | Replication | Condition | Notes |
|---|---|---|---|---|---|
| `/Game/_ThirdParty/GASP_example/Blueprints/AC_VisualOverrideManager` | `VisualOverride` | Var | Replicated (class<Class>) | — | RepNotify: `OnRep_VisualOverride` |
| `/Game/_ThirdParty/GASP_example/Blueprints/SandboxCharacter_CMC` | `CharacterInputState` | Var | Replicated (struct<S_PlayerInputState>) | COND_SkipOwner | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Animate Time of Day` | Var | Replicated (bool) | — | RepNotify: `OnRep_Animate Time of Day` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Clouds B Time` | Var | Replicated (real<double>) | COND_InitialOnly | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Clouds Position` | Var | Replicated (struct<Vector>) | COND_InitialOnly | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Day` | Var | Replicated (int) | — | RepNotify: `OnRep_Day` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Day Length` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Initial Replication` | Var | Replicated (bool) | COND_InitialOnly | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Month` | Var | Replicated (int) | — | RepNotify: `OnRep_Month` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Moon Phase` | Var | Replicated (real<double>) | COND_InitialOnly | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Night Length` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Replicated Modifier State` | Var | Replicated (struct<UDS_ModifierState>) | — | RepNotify: `OnRep_Replicated Modifier State` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Replicated Time of Day` | Var | Replicated (real<double>) | COND_SkipOwner | RepNotify: `OnRep_Replicated Time of Day` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Simulated Sunrise Time` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Simulated Sunset Time` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Simulation Speed` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Simulation Speed Night Multiplier` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Time Speed` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Transitioning Time` | Var | Replicated (bool) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Use Auroras` | Var | Replicated (bool) | COND_OwnerOnly | RepNotify: `OnRep_Use Auroras` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Use System Time` | Var | Replicated (bool) | — | RepNotify: `OnRep_Use System Time` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` | `Year` | Var | Replicated (int) | — | RepNotify: `OnRep_Year` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Cloud Coverage` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Cloud Coverage - Manual Override` | Var | Replicated (bool) | — | RepNotify: `OnRep_Cloud Coverage - Manual Override` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Distant Thunder Volume` | Var | Replicated (real<double>) | COND_OwnerOnly | RepNotify: `OnRep_Distant Thunder Volume` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Dust` | Var | Replicated (real<double>) | — | RepNotify: `OnRep_Dust` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Dust - Manual Override` | Var | Replicated (bool) | — | RepNotify: `OnRep_Dust - Manual Override` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Enable Dust Particles` | Var | Replicated (bool) | COND_OwnerOnly | RepNotify: `OnRep_Enable Dust Particles` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Enable Heat Distortion` | Var | Replicated (bool) | COND_OwnerOnly | RepNotify: `OnRep_Enable Heat Distortion` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Enable Obscured Lightning` | Var | Replicated (bool) | COND_OwnerOnly | RepNotify: `OnRep_Enable Obscured Lightning` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Enable Post Process Wind Fog` | Var | Replicated (bool) | COND_OwnerOnly | RepNotify: `OnRep_Enable Post Process Wind Fog` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Enable Radial Storm Spawning` | Var | Replicated (bool) | COND_OwnerOnly | RepNotify: `OnRep_Enable Radial Storm Spawning` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Enable Rain Particles` | Var | Replicated (bool) | COND_OwnerOnly | RepNotify: `OnRep_Enable Rain Particles` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Enable Rainbow` | Var | Replicated (bool) | COND_OwnerOnly | RepNotify: `OnRep_Enable Rainbow` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Enable Screen Droplets` | Var | Replicated (bool) | COND_OwnerOnly | RepNotify: `OnRep_Enable Screen Droplets` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Enable Screen Frost` | Var | Replicated (bool) | COND_OwnerOnly | RepNotify: `OnRep_Enable Screen Frost` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Enable Snow Particles` | Var | Replicated (bool) | COND_OwnerOnly | RepNotify: `OnRep_Enable Snow Particles` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Enable Weather Sound Effects` | Var | Replicated (bool) | COND_OwnerOnly | RepNotify: `OnRep_Enable Weather Sound Effects` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Enable Wind Camera Shake` | Var | Replicated (bool) | COND_OwnerOnly | RepNotify: `OnRep_Enable Wind Camera Shake` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Enable Wind Debris` | Var | Replicated (bool) | COND_OwnerOnly | RepNotify: `OnRep_Enable Wind Debris` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Fog` | Var | Replicated (real<double>) | — | RepNotify: `OnRep_Fog` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Fog - Manual Override` | Var | Replicated (bool) | — | RepNotify: `OnRep_Fog - Manual Override` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Manual Heat Distortion` | Var | Replicated (real<double>) | COND_OwnerOnly | RepNotify: `OnRep_Manual Heat Distortion` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Manual Screen Frost` | Var | Replicated (real<double>) | COND_OwnerOnly | RepNotify: `OnRep_Manual Screen Frost` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Material Dust Coverage` | Var | Replicated (real<double>) | — | RepNotify: `OnRep_Material Dust Coverage` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Material Dust Coverage - Manual Override` | Var | Replicated (bool) | — | RepNotify: `OnRep_Material Dust Coverage - Manual Override` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Material Snow Coverage` | Var | Replicated (real<double>) | — | RepNotify: `OnRep_Material Snow Coverage` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Material Snow Coverage - Manual Override` | Var | Replicated (bool) | — | RepNotify: `OnRep_Material Snow Coverage - Manual Override` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Material Wetness` | Var | Replicated (real<double>) | — | RepNotify: `OnRep_Material Wetness` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Material Wetness - Manual Override` | Var | Replicated (bool) | — | RepNotify: `OnRep_Material Wetness - Manual Override` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Max Attenuation` | Var | Replicated (real<double>) | COND_OwnerOnly | RepNotify: `OnRep_Max Attenuation` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Min LPF Frequency` | Var | Replicated (real<double>) | COND_OwnerOnly | RepNotify: `OnRep_Min LPF Frequency` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Old Weather State Struct` | Var | Replicated (struct<UDW_WeatherState_Structure>) | COND_InitialOnly | RepNotify: `OnRep_Old Weather State Struct` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Rain` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Rain - Manual Override` | Var | Replicated (bool) | — | RepNotify: `OnRep_Rain - Manual Override` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Rain Volume` | Var | Replicated (real<double>) | COND_OwnerOnly | RepNotify: `OnRep_Rain Volume` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Random Weather Variation State` | Var | Replicated (byte) | — | RepNotify: `OnRep_Random Weather Variation State` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Season` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Snow` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Snow - Manual Override` | Var | Replicated (bool) | — | RepNotify: `OnRep_Snow - Manual Override` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Thunder/Lightning` | Var | Replicated (real<double>) | — | RepNotify: `OnRep_Thunder/Lightning` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Thunder/Lightning - Manual Override` | Var | Replicated (bool) | — | RepNotify: `OnRep_Thunder/Lightning - Manual Override` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Time Random Offset` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Transition Active` | Var | Replicated (bool) | — | RepNotify: `OnRep_Transition Active` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Transition Duration` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Transition Timer` | Var | Replicated (real<double>) | COND_InitialOnly | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Weather` | Var | Replicated (object<UDS_Weather_Settings_C>) | — | RepNotify: `OnRep_Weather` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Weather Sounds Master Volume` | Var | Replicated (real<double>) | COND_OwnerOnly | RepNotify: `OnRep_Weather Sounds Master Volume` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Weather Speed` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Wind Debris Particle Spawn Count` | Var | Replicated (real<double>) | COND_OwnerOnly | RepNotify: `OnRep_Wind Debris Particle Spawn Count` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Wind Direction` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Wind Intensity` | Var | Replicated (real<double>) | — | RepNotify: `OnRep_Wind Intensity` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Wind Intensity - Manual Override` | Var | Replicated (bool) | — | RepNotify: `OnRep_Wind Intensity - Manual Override` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Wind Volume` | Var | Replicated (real<double>) | COND_OwnerOnly | RepNotify: `OnRep_Wind Volume` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` | `Wind Whistling Volume` | Var | Replicated (real<double>) | COND_OwnerOnly | RepNotify: `OnRep_Wind Whistling Volume` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Puddle_Fluid_Volume` | `Fill Manually` | Var | Replicated (bool) | COND_OwnerOnly | RepNotify: `OnRep_Fill Manually` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Puddle_Fluid_Volume` | `Fill with Material Wetness` | Var | Replicated (bool) | COND_OwnerOnly | RepNotify: `OnRep_Fill with Material Wetness` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Puddle_Fluid_Volume` | `Fill with Rain` | Var | Replicated (bool) | COND_OwnerOnly | RepNotify: `OnRep_Fill with Rain` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Radial_Storm` | `Inner Radius Fraction` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Radial_Storm` | `Outer Radius` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Radial_Storm` | `Storm Weather` | Var | Replicated (object<UDS_Weather_Settings_C>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Random_Weather_Variation` | `Change Timer` | Var | Replicated (real<double>) | COND_InitialOnly | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Random_Weather_Variation` | `Current Lerp Alpha` | Var | Replicated (real<double>) | COND_InitialOnly | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Random_Weather_Variation` | `Current Timer Length` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Random_Weather_Variation` | `Last Random Weather Type` | Var | Replicated (object<UDS_Weather_Settings_C>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Random_Weather_Variation` | `Target Random Weather Type` | Var | Replicated (object<UDS_Weather_Settings_C>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Random_Weather_Variation` | `Weather Forecast` | Var | Replicated (TArray<object<UDS_Weather_Settings_C>>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Random_Weather_Variation` | `Weather Forecast Times` | Var | Replicated (TArray<real<double>>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Material_State_Manager` | `Replicated Material Dust` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Material_State_Manager` | `Replicated Material Snow` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Material_State_Manager` | `Replicated Wetness` | Var | Replicated (real<double>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Override_Volume` | `Random Weather Variation` | Var | Replicated (byte<UDS_RandomWeatherTiming>) | — | RepNotify: `OnRep_Random Weather Variation` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Override_Volume` | `Runtime Spline Points` | Var | Replicated (TArray<struct<Vector>>) | — | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Override_Volume` | `Transition Time Elapsed` | Var | Replicated (real<double>) | COND_InitialOnly | — |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Override_Volume` | `Transition Timer Length` | Var | Replicated (real<double>) | — | RepNotify: `OnRep_Transition Timer Length` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Override_Volume` | `Volume Alpha` | Var | Replicated (real<double>) | — | RepNotify: `OnRep_Volume Alpha` |
| `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Override_Volume` | `Weather` | Var | Replicated (object<UDS_Weather_Settings_C>) | — | RepNotify: `OnRep_Weather` |
| `/Game/Standards/GameActor/GameComponent` | `R_Keyframes` | Var | Replicated (struct<sFourBytes>) | — | RepNotify: `OnRep_R_Keyframes` |

