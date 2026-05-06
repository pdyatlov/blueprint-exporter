# Ultra_Dynamic_Sky

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky.Ultra_Dynamic_Sky` |
| Asset name | `Ultra_Dynamic_Sky` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces (3):
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArrayOwner_Interface.UDS_InterfaceActorArrayOwner_Interface_C`
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Modifier_Interface.UDS_Modifier_Interface_C`
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion_Interface.UDS_PlayerOcclusion_Interface_C`

## Variables (858)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Sky Sphere MID` | `object<MaterialInstanceDynamic>` | `None` | `Dynamic Material Instances` | — | — | InstanceEditable, Private |
| `Cloud Speed` | `real<double>` | `0.350000` | `𝙲𝟺  ·  Cloud Movement` | — | — | InstanceEditable, ExposeToCinematics |
| `Cloud Wisps Opacity (Clear)` | `real<double>` | `0.200000` | `𝙲𝟻  ·  Cloud Wisps` | — | — | InstanceEditable, ExposeToCinematics |
| `Refresh Settings` | `bool` | `False` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Time of Day` | `real<double>` | `960.000000` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable, ExposeToCinematics |
| `Sky Mode` | `byte<UDS_SkyMode>` | `NewEnumerator0` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Color Mode` | `byte<UDS_ColorMode>` | `NewEnumerator0` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Project Mode` | `byte<UDS_Project_Mode>` | `NewEnumerator0` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Feature Level` | `byte<UDS_RenderingFeatureLevel>` | `NewEnumerator0` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Cloud Coverage` | `real<double>` | `3.800000` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable, ExposeToCinematics |
| `Fog` | `real<double>` | `1.000000` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable, ExposeToCinematics |
| `Overall Intensity` | `real<double>` | `1.000000` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable, ExposeToCinematics |
| `Cloud Direction` | `real<double>` | `180.000000` | `𝙲𝟺  ·  Cloud Movement` | — | — | InstanceEditable, ExposeToCinematics |
| `Cloud Phase` | `real<double>` | `0.000000` | `𝙲𝟺  ·  Cloud Movement` | — | — | InstanceEditable, ExposeToCinematics |
| `Manually Position Moon Target` | `bool` | `False` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Render Moon` | `bool` | `True` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable |
| `Moon Light Intensity` | `real<double>` | `0.150000` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Moon Mobility` | `byte<EComponentMobility>` | `Movable` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable |
| `Moon Scale` | `real<double>` | `0.950000` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Moon Phase` | `real<double>` | `0.000000` | `𝙴𝟸  ·  Moon` | Replicated (COND_InitialOnly) | — | InstanceEditable, ExposeToCinematics |
| `Moon Yaw` | `real<double>` | `15.000000` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Moon Pitch` | `real<double>` | `35.000000` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Moon Vertical Offset` | `real<double>` | `0.040000` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Moon Orbit Offset` | `real<double>` | `0.000000` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Moon Casts Shadows` | `bool` | `True` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Moon Transmission` | `bool` | `False` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable |
| `Moon Light Color` | `struct<LinearColor>` | `(R=0.445801,G=0.557475,B=0.864583,A=1.000000)` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Moon Texture` | `softobject<Texture2D>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/Moon_Color.Moon_Color` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable |
| `Moon Material Color` | `struct<LinearColor>` | `(R=0.486328,G=0.574971,B=0.864583,A=1.000000)` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Moon Texture Intensity (Night)` | `real<double>` | `0.300000` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Moon Texture Intensity (Day)` | `real<double>` | `0.600000` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Moon Glow Intensity` | `real<double>` | `0.070000` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable |
| `Moon Glow Scale` | `real<double>` | `1.000000` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable |
| `Render Moon Phases` | `bool` | `True` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable |
| `Moon Phase Contrast` | `real<double>` | `1.600000` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable |
| `Moon Phase Changes Over Time` | `bool` | `False` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable |
| `Dark Side Brightness` | `real<double>` | `0.005000` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable |
| `Moon Phase Normal` | `softobject<Texture2D>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/Moon_PhaseNormal.Moon_PhaseNormal` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable |
| `Manually Position Sun Target` | `bool` | `False` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, ExposeToCinematics |
| `Sun Light Intensity` | `real<double>` | `5.000000` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, ExposeToCinematics |
| `Sun Mobility` | `byte<EComponentMobility>` | `Movable` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable |
| `Sun Yaw` | `real<double>` | `0.000000` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, ExposeToCinematics |
| `Contrast` | `real<double>` | `0.100000` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Saturation` | `real<double>` | `1.000000` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable, ExposeToCinematics |
| `Dawn Time` | `real<double>` | `600.000000` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Dusk Time` | `real<double>` | `1800.000000` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Lighting Brightness (Day)` | `real<double>` | `1.000000` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable, ExposeToCinematics |
| `Lighting Brightness (Dawn/Dusk)` | `real<double>` | `1.000000` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable, ExposeToCinematics |
| `Lighting Brightness (Night)` | `real<double>` | `1.000000` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable, ExposeToCinematics |
| `Sun Pitch` | `real<double>` | `30.000000` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, ExposeToCinematics |
| `Sun Vertical Offset` | `real<double>` | `0.000000` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, ExposeToCinematics |
| `Sun Casts Shadows` | `bool` | `True` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, ExposeToCinematics |
| `Sun Transmission` | `bool` | `False` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable |
| `Sun Light Color` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, ExposeToCinematics |
| `Soften 2D Dynamic Cloud Layer 1` | `real<double>` | `0.000000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `Soften 2D Dynamic Cloud Layer 2` | `real<double>` | `0.000000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `Sharpen 2D Dynamic Cloud Outer Edge` | `real<double>` | `0.000000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `Stars Intensity` | `real<double>` | `0.750000` | `𝙷𝟷  ·  Stars` | — | — | InstanceEditable, ExposeToCinematics |
| `Stars Color` | `struct<LinearColor>` | `(R=0.484375,G=0.639062,B=1.000000,A=1.000000)` | `𝙷𝟷  ·  Stars` | — | — | InstanceEditable, ExposeToCinematics |
| `Sun Scale` | `real<double>` | `1.200000` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, ExposeToCinematics |
| `Cloud Shadows MID` | `object<MaterialInstanceDynamic>` | `None` | `Dynamic Material Instances` | — | — | InstanceEditable, Private |
| `Use Cloud Shadows` | `bool` | `True` | `𝙴𝟻  ·  Cloud Shadows` | — | — | InstanceEditable |
| `Cloud Shadows Intensity When Sunny` | `real<double>` | `0.700000` | `𝙴𝟻  ·  Cloud Shadows` | — | — | InstanceEditable |
| `Stars Speed` | `real<double>` | `0.030000` | `𝙷𝟷  ·  Stars` | — | — | InstanceEditable |
| `New Moon Light Brightness` | `real<double>` | `0.015000` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Moon Source Angle Scale` | `real<double>` | `1.000000` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Moon Texture Rotation` | `real<double>` | `0.000000` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Sky Light Mode` | `byte<UDS_SkyLightMode>` | `NewEnumerator0` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable |
| `Use Auroras` | `bool` | `False` | `𝙷𝟺  ·  Aurora` | Replicated (COND_OwnerOnly) | `OnRep_Use Auroras` | InstanceEditable |
| `Aurora Intensity` | `real<double>` | `0.120000` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable, ExposeToCinematics |
| `Aurora Speed` | `real<double>` | `0.150000` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable |
| `Cloud Shadows Intensity When Overcast` | `real<double>` | `1.000000` | `𝙴𝟻  ·  Cloud Shadows` | — | — | InstanceEditable |
| `Cloud Shadows Softness` | `real<double>` | `0.100000` | `𝙴𝟻  ·  Cloud Shadows` | — | — | InstanceEditable |
| `2D Dynamic Cloud Tiling` | `real<double>` | `3.500000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `Soften 2D Dynamic Cloud Horizon` | `real<double>` | `2.000000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `2D Dynamic Clouds - Use Single Layer` | `bool` | `False` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `2D Dynamic Cloud Height` | `real<double>` | `0.500000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `2D Dynamic Clouds Overcast Texture` | `real<double>` | `2.000000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `Directional Balance` | `real<double>` | `1.000000` | `𝙴𝟺  ·  Directional Light` | — | — | InstanceEditable, ExposeToCinematics |
| `Night Brightness` | `real<double>` | `1.000000` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable, ExposeToCinematics |
| `Sun Softness` | `real<double>` | `3.800000` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable |
| `Aurora Phase` | `real<double>` | `1.000000` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable, ExposeToCinematics |
| `Sun_LightComponent` | `object<DirectionalLightComponent>` | `None` | `Components` | — | — | InstanceEditable, Private |
| `Moon_LightComponent` | `object<DirectionalLightComponent>` | `None` | `Components` | — | — | InstanceEditable, Private |
| `SkyLightComponent` | `object<SkyLightComponent>` | `None` | `Components` | — | — | InstanceEditable, Private |
| `Height Fog Component` | `object<ExponentialHeightFogComponent>` | `None` | `Components` | — | — | InstanceEditable, Private |
| `Apply Exposure Settings` | `bool` | `True` | `𝙴𝟼  ·  Exposure` | — | — | InstanceEditable |
| `Exposure Metering Mode` | `byte<EAutoExposureMethod>` | `AEM_Histogram` | `𝙴𝟼  ·  Exposure` | — | — | InstanceEditable |
| `Exposure Compensation Curve` | `object<CurveFloat>` | `/Script/Engine.CurveFloat'/Game/_ThirdParty/UltraDynamicSky/Materials/Float_Curves/Exposure_Compensation_Curve.Exposure_Compensation_Curve'` | `𝙴𝟼  ·  Exposure` | — | — | InstanceEditable |
| `Animate Time of Day` | `bool` | `False` | `𝙱𝟷  ·  Animate Time Of Day` | Replicated | `OnRep_Animate Time of Day` | InstanceEditable |
| `Day Length` | `real<double>` | `30.000000` | `𝙱𝟷  ·  Animate Time Of Day` | Replicated | — | InstanceEditable, ExposeToCinematics |
| `Night Length` | `real<double>` | `15.000000` | `𝙱𝟷  ·  Animate Time Of Day` | Replicated | — | InstanceEditable, ExposeToCinematics |
| `Sun Disk Tint` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, ExposeToCinematics |
| `Extend Dawn and Dusk` | `real<double>` | `0.000000` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, ExposeToCinematics |
| `Base Fog Density` | `real<double>` | `0.005500` | `𝙵𝟸  ·  Fog Density` | — | — | InstanceEditable, ExposeToCinematics |
| `Foggy Density Contribution` | `real<double>` | `0.100000` | `𝙵𝟸  ·  Fog Density` | — | — | InstanceEditable, ExposeToCinematics |
| `Cloudy Density Contribution` | `real<double>` | `0.002000` | `𝙵𝟸  ·  Fog Density` | — | — | InstanceEditable, ExposeToCinematics |
| `Dust Density Contribution` | `real<double>` | `0.500000` | `𝙵𝟸  ·  Fog Density` | — | — | InstanceEditable, ExposeToCinematics |
| `Stars Tiling` | `real<double>` | `2.500000` | `𝙷𝟷  ·  Stars` | — | — | InstanceEditable |
| `Stars Daytime Intensity` | `real<double>` | `0.000000` | `𝙷𝟷  ·  Stars` | — | — | InstanceEditable, ExposeToCinematics |
| `Twinkle Amount` | `real<double>` | `0.300000` | `𝙷𝟷  ·  Stars` | — | — | InstanceEditable |
| `Twinkle Speed` | `real<double>` | `1.000000` | `𝙷𝟷  ·  Stars` | — | — | InstanceEditable |
| `Tiling Stars Texture` | `softobject<Texture2D>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/Tiling_Stars.Tiling_Stars` | `𝙷𝟷  ·  Stars` | — | — | InstanceEditable |
| `Real Stars Texture` | `softobject<Texture2D>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/Real_Stars.Real_Stars` | `𝙷𝟷  ·  Stars` | — | — | InstanceEditable |
| `Stars Phase` | `real<double>` | `0.000000` | `𝙷𝟷  ·  Stars` | — | — | InstanceEditable, ExposeToCinematics |
| `Sky Light Intensity` | `real<double>` | `1.000000` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable, ExposeToCinematics |
| `Sky Light Mobility` | `byte<EComponentMobility>` | `Movable` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable |
| `Sky Light Temperature` | `real<double>` | `0.000000` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable, ExposeToCinematics |
| `Sky Light Color Multiplier (Day)` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable, ExposeToCinematics |
| `Sky Light Color Multiplier (Dawn/Dusk)` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable, ExposeToCinematics |
| `Sky Light Color Multiplier (Night)` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable, ExposeToCinematics |
| `Real Time Capture` | `bool` | `True` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable |
| `Render Sky Light` | `bool` | `True` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable |
| `Move Sky Light Capture with Camera Location` | `bool` | `True` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable |
| `Sky Light Movement uses Z Axis` | `bool` | `False` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable |
| `Sky Light Lower Hemisphere Tint (Capture Based)` | `struct<LinearColor>` | `(R=0.260417,G=0.229905,B=0.202094,A=1.000000)` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable, ExposeToCinematics |
| `Sky Light Lower Hemisphere Tint (Cubemap)` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=0.750000)` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable, ExposeToCinematics |
| `Sky Light Cubemap` | `softobject<TextureCube>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/FlatCubemap.FlatCubemap` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable |
| `Sky Light Cubemap Angle` | `real<double>` | `0.000000` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable |
| `Custom Sky Light Actor` | `object<SkyLight>` | `None` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable |
| `Real Time Capture Uses Time Slicing` | `bool` | `True` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable |
| `Real Time Capture Time Slicing Cloud Faces Per Frame` | `int` | `1` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable |
| `Static/Stationary Sky Light Casts Shadows` | `bool` | `True` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable |
| `Movable Sky Light Casts Shadows (Enable DFAO)` | `bool` | `False` | `𝙴𝟹  ·  Sky Light` | — | — | InstanceEditable |
| `Random Starting Time` | `bool` | `False` | `𝙱𝟷  ·  Animate Time Of Day` | — | — | InstanceEditable |
| `Sunrise Event Offset` | `real<double>` | `0.000000` | `𝙱𝟷  ·  Animate Time Of Day` | — | — | InstanceEditable |
| `Sunset Event Offset` | `real<double>` | `0.000000` | `𝙱𝟷  ·  Animate Time Of Day` | — | — | InstanceEditable |
| `Sunset` | `mcdelegate` | `()` | `Time Dispatchers` | — | — | InstanceEditable, Private |
| `Sunrise` | `mcdelegate` | `()` | `Time Dispatchers` | — | — | InstanceEditable, Private |
| `Cloud Wisps Opacity (Cloudy)` | `real<double>` | `0.500000` | `𝙲𝟻  ·  Cloud Wisps` | — | — | InstanceEditable, ExposeToCinematics |
| `Cloud Wisps Texture` | `object<Texture2D>` | `/Script/Engine.Texture2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/Cloud_Wisps.Cloud_Wisps'` | `𝙲𝟻  ·  Cloud Wisps` | — | — | InstanceEditable |
| `2D Dynamic Cloud Formation Texture` | `softobject<Texture2D>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/Clouds/clouds_diverse.clouds_diverse` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `2D Dynamic Clouds Sun Shader Intensity` | `real<double>` | `0.350000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `2D Dynamic Clouds Directional Lighting Intensity` | `real<double>` | `3.000000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `2D Dynamic Clouds Sun Highlight Radius Scale` | `real<double>` | `1.000000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `2D Dynamic Cloud Opacity` | `real<double>` | `1.000000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `2D Clouds Horizon Density Multiplier` | `real<double>` | `1.100000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `2D Clouds Zenith Density Multiplier` | `real<double>` | `0.900000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `2D Clouds Latitude Gradient Position` | `real<double>` | `0.250000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `2D Clouds Latitude Gradient Width` | `real<double>` | `50.000000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `2D Clouds Around Sun Density Multiplier` | `real<double>` | `1.000000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `2D Clouds Around Sun Density Exponent` | `real<double>` | `25.000000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `2D Clouds Around Moon Density Multiplier` | `real<double>` | `1.000000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `2D Clouds Around Moon Density Exponent` | `real<double>` | `45.000000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `2D Clouds Shading Offset` | `real<double>` | `1.000000` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `2D Dynamic Clouds Shine Intensity Curve` | `object<CurveFloat>` | `/Script/Engine.CurveFloat'/Game/_ThirdParty/UltraDynamicSky/Materials/Float_Curves/Shine_Intensity.Shine_Intensity'` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `2D Dynamic Clouds Sun Highlight Intensity Curve` | `object<CurveFloat>` | `/Script/Engine.CurveFloat'/Game/_ThirdParty/UltraDynamicSky/Materials/Float_Curves/Sun_Highlight_Intensity.Sun_Highlight_Intensity'` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `2D Dynamic Clouds Sun Highlight Radius Curve` | `object<CurveFloat>` | `/Script/Engine.CurveFloat'/Game/_ThirdParty/UltraDynamicSky/Materials/Float_Curves/Sun_Highlight_Radius.Sun_Highlight_Radius'` | `𝙲𝟸  ·  2D Dynamic Clouds` | — | — | InstanceEditable |
| `Adjust for Path Tracer` | `bool` | `False` | `𝙼𝟷  ·  Cinematics / Offline Rendering` | — | — | InstanceEditable |
| `Lights Update Period` | `real<double>` | `0.000000` | `𝙴𝟺  ·  Directional Light` | — | — | InstanceEditable |
| `Lights Update Degree Threshold` | `real<double>` | `0.030000` | `𝙴𝟺  ·  Directional Light` | — | — | InstanceEditable |
| `Dim Directional Lights with Cloud Coverage` | `bool` | `False` | `𝙴𝟺  ·  Directional Light` | — | — | InstanceEditable |
| `Directional Lights Absent Brightness` | `real<double>` | `2.000000` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable, ExposeToCinematics |
| `Sky Configuration Override` | `object<UDS_Sky_Configuration_C>` | `None` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Extra Night Brightness when Cloudy` | `real<double>` | `0.000000` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Vol Clouds MID Complex` | `object<MaterialInstanceDynamic>` | `None` | `Dynamic Material Instances` | — | — | InstanceEditable, Private |
| `Volumetric Cloud Rendering Mode` | `byte<UDS_VolRT_Mode>` | `NewEnumerator0` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Bottom Altitude` | `real<double>` | `0.600000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Volumetric Clouds Scale` | `real<double>` | `1.000000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Layer Height Scale` | `real<double>` | `1.000000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Cloud Formation Texture Scale` | `real<double>` | `1.000000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Cloud Formation Z Shift` | `real<double>` | `0.000000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `3D Noise Scale` | `real<double>` | `0.900000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `3D Erosion Intensity` | `real<double>` | `1.200000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `High Frequency Noise Amount` | `real<double>` | `0.240000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `High Frequency Noise Distance Scale` | `real<double>` | `130000.000000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Max High Frequency Noise Levels` | `int` | `2` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Distort High Frequency Noise` | `real<double>` | `0.210000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Extinction Scale` | `real<double>` | `10.000000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Base Floor Variation` | `real<double>` | `0.100000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Overcast Floor Variation` | `real<double>` | `0.800000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Floor Luminance Scale` | `real<double>` | `1.200000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `View Sample Scale (Day)` | `real<double>` | `2.200000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `View Sample Scale (Night)` | `real<double>` | `1.700000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Shadow Sample Scale` | `real<double>` | `0.400000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Shadow Tracing Distance` | `real<double>` | `0.500000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Tracing Max Distance (Inside Cloud Layer)` | `real<double>` | `6.000000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Tracing Max Distance (Outside Cloud Layer)` | `real<double>` | `20.000000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Volumetric Cloud Color` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Cloud Profile LUT` | `softobject<Texture>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/Volumetric_Clouds/Cloud_Profile.Cloud_Profile` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Volumetric Cloud Formation Volume Texture` | `softobject<VolumeTexture>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/3D_Clouds/FormationVolume.FormationVolume` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Minimum Erosion` | `real<double>` | `0.000000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Close View Sample Ratio` | `real<double>` | `2.000000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Cloud Formation Mip Level` | `real<double>` | `0.000000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Reflection Sample Count Scale` | `real<double>` | `2.000000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Reflection Shadow Sample Count Scale` | `real<double>` | `0.300000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Volumetric Cloud Ambient Light Intensity` | `real<double>` | `1.000000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Volumetric Cloud Ambient Light (Day)` | `struct<LinearColor>` | `(R=0.354899,G=0.463542,B=0.443624,A=1.000000)` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Volumetric Cloud Ambient Light (Dawn/Dusk)` | `struct<LinearColor>` | `(R=0.531250,G=0.313991,B=0.296061,A=1.000000)` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Volumetric Cloud Ambient Light (Night)` | `struct<LinearColor>` | `(R=0.368548,G=0.376632,B=0.500000,A=1.000000)` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Volumetric Cloud Ambient Light Saturation` | `real<double>` | `0.450000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Multiscattering Light Intensity` | `real<double>` | `0.850000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Multiscattering Light Occlusion` | `real<double>` | `0.500000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Vol Clouds MID Simple` | `object<MaterialInstanceDynamic>` | `None` | `Dynamic Material Instances` | — | — | InstanceEditable, Private |
| `Scale Fog Density` | `real<double>` | `1.000000` | `𝙵𝟸  ·  Fog Density` | — | — | InstanceEditable, ExposeToCinematics |
| `Min Fog Start Distance` | `real<double>` | `0.000000` | `𝙵𝟸  ·  Fog Density` | — | — | InstanceEditable, ExposeToCinematics |
| `Max Fog Start Distance` | `real<double>` | `15000.000000` | `𝙵𝟸  ·  Fog Density` | — | — | InstanceEditable, ExposeToCinematics |
| `Min Fog Start Distance Density` | `real<double>` | `0.080000` | `𝙵𝟸  ·  Fog Density` | — | — | InstanceEditable, ExposeToCinematics |
| `Formation Change Speed` | `real<double>` | `0.700000` | `𝙲𝟺  ·  Cloud Movement` | — | — | InstanceEditable |
| `Randomize Cloud Formation on Run` | `bool` | `True` | `𝙲𝟺  ·  Cloud Movement` | — | — | InstanceEditable |
| `3D Noise Vertical Movement` | `real<double>` | `0.250000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Macro Variation` | `real<double>` | `0.160000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Macro Scale` | `real<double>` | `1.300000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Multiscattering Phase 1` | `real<double>` | `0.850000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Multiscattering Phase 2` | `real<double>` | `0.400000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Multiscattering Eccentricity` | `real<double>` | `0.400000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Custom Time Dispatchers` | `TArray<real<double>>` | — | `𝙱𝟷  ·  Animate Time Of Day` | — | — | InstanceEditable |
| `Time Event Dispatcher Check Period` | `real<double>` | `1.000000` | `𝙱𝟷  ·  Animate Time Of Day` | — | — | InstanceEditable |
| `Time Speed` | `real<double>` | `1.000000` | `𝙱𝟷  ·  Animate Time Of Day` | Replicated | — | InstanceEditable, ExposeToCinematics |
| `Time Cycle Degrees` | `real<double>` | `0.000000` | `System - Time` | — | — | InstanceEditable, Private |
| `Ultra Dynamic Weather` | `object<Actor>` | `None` | `Hidden Exposed` | — | — | InstanceEditable |
| `Tracing Max Start Distance` | `real<double>` | `100.000000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Aurora Shape Change Speed` | `real<double>` | `2.000000` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable |
| `Aurora Texture Scale` | `real<double>` | `1.000000` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable |
| `Daytime Aurora Intensity` | `real<double>` | `0.000000` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable |
| `Aurora Color 1` | `struct<LinearColor>` | `(R=0.619792,G=0.091135,B=0.341744,A=1.000000)` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable |
| `Aurora Color 2` | `struct<LinearColor>` | `(R=0.189217,G=1.000000,B=0.050196,A=1.000000)` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable |
| `Aurora Color 3` | `struct<LinearColor>` | `(R=0.070031,G=0.347007,B=0.656250,A=1.000000)` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable |
| `Volumetric Aurora MID` | `object<MaterialInstanceDynamic>` | `None` | `Dynamic Material Instances` | — | — | InstanceEditable, Private |
| `Half Rate Tick` | `bool` | `True` | `𝙼𝟸  ·  Scalability / Performance` | — | — | InstanceEditable, ExposeToCinematics |
| `Half Rate Tick Framerate Threshold` | `int` | `45` | `𝙼𝟸  ·  Scalability / Performance` | — | — | InstanceEditable |
| `Disable All Runtime Updating` | `bool` | `False` | `𝙼𝟸  ·  Scalability / Performance` | — | — | InstanceEditable |
| `Use Sky Mode Scalability Map` | `bool` | `False` | `𝙼𝟸  ·  Scalability / Performance` | — | — | InstanceEditable |
| `Sky Mode Scalability Map` | `TMap<int<UDS_SkyMode>>, :/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_SkyMode.UDS_SkyMode>` | `((0, NewEnumerator6),(1, NewEnumerator6),(2, NewEnumerator0),(3, NewEnumerator0),(4, NewEnumerator0))` | `𝙼𝟸  ·  Scalability / Performance` | — | — | InstanceEditable |
| `Sun Disk Intensity` | `real<double>` | `4.000000` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, ExposeToCinematics |
| `Inside Clouds Fog MID` | `object<MaterialInstanceDynamic>` | `None` | `Dynamic Material Instances` | — | — | InstanceEditable, Private |
| `Enable Fog Inside Clouds` | `bool` | `True` | `𝙲𝟷  ·  Volumetric Clouds\|Fog Inside Clouds` | — | — | InstanceEditable |
| `Aurora Sky Light/Reflection Brightness` | `real<double>` | `1.000000` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable |
| `Aurora Texture` | `softobject<Texture2D>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/Clouds/Aurora_Clouds.Aurora_Clouds` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable |
| `2D Aurora Max Samples` | `real<double>` | `14.000000` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable, ExposeToCinematics |
| `2D Aurora Sample Step Size` | `real<double>` | `0.025000` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable |
| `2D Aurora Line Exponent` | `real<double>` | `15.000000` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable |
| `2D Aurora Mask Exponent` | `real<double>` | `3.500000` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable |
| `Volumetric Aurora Rendering Mode` | `byte<UDS_VolRT_Mode>` | `NewEnumerator1` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable |
| `Volumetric Aurora Sample Count Scale` | `real<double>` | `1.000000` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable |
| `Volumetric Aurora Layer Height` | `real<double>` | `1.200000` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable |
| `Volumetric Aurora Bottom Altitude` | `real<double>` | `0.500000` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable |
| `Fog Density Daytime Mutliplier` | `real<double>` | `1.000000` | `𝙵𝟸  ·  Fog Density` | — | — | InstanceEditable, ExposeToCinematics |
| `Fog Density Nighttime Multiplier` | `real<double>` | `1.000000` | `𝙵𝟸  ·  Fog Density` | — | — | InstanceEditable, ExposeToCinematics |
| `Base Height Fog Falloff` | `real<double>` | `0.065000` | `𝙵𝟸  ·  Fog Density` | — | — | InstanceEditable, ExposeToCinematics |
| `Cloudy Height Fog Falloff` | `real<double>` | `0.050000` | `𝙵𝟸  ·  Fog Density` | — | — | InstanceEditable, ExposeToCinematics |
| `Foggy Height Fog Falloff` | `real<double>` | `0.015000` | `𝙵𝟸  ·  Fog Density` | — | — | InstanceEditable, ExposeToCinematics |
| `Inside Cloud Fog Strength` | `real<double>` | `1.000000` | `𝙲𝟷  ·  Volumetric Clouds\|Fog Inside Clouds` | — | — | InstanceEditable |
| `Inside Cloud Fog Color` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `𝙲𝟷  ·  Volumetric Clouds\|Fog Inside Clouds` | — | — | InstanceEditable |
| `2D Overcast Turbulence` | `real<double>` | `0.800000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Close Fade Distance` | `real<double>` | `100000.000000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Close Fade Offset` | `real<double>` | `5000.000000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Two Layers` | `bool` | `False` | `𝙲𝟷  ·  Volumetric Clouds\|Second Cloud Layer` | — | — | InstanceEditable |
| `Layer 2 Coverage Scale` | `real<double>` | `1.000000` | `𝙲𝟷  ·  Volumetric Clouds\|Second Cloud Layer` | — | — | InstanceEditable, ExposeToCinematics |
| `Layer 2 Extinction Scale` | `real<double>` | `0.050000` | `𝙲𝟷  ·  Volumetric Clouds\|Second Cloud Layer` | — | — | InstanceEditable |
| `Layer 2 Cloud Scale` | `struct<Vector2D>` | `(X=0.600000,Y=1.400000)` | `𝙲𝟷  ·  Volumetric Clouds\|Second Cloud Layer` | — | — | InstanceEditable |
| `Layer 2 Mip Offset` | `real<double>` | `1.000000` | `𝙲𝟷  ·  Volumetric Clouds\|Second Cloud Layer` | — | — | InstanceEditable |
| `Distance Between Layers` | `real<double>` | `0.000000` | `𝙲𝟷  ·  Volumetric Clouds\|Second Cloud Layer` | — | — | InstanceEditable |
| `Enable Sun Light Shaft Bloom` | `bool` | `False` | `𝙸𝟷  ·  Screen Space Light Shafts` | — | — | InstanceEditable |
| `Sun Light Shaft Bloom - Scale` | `real<double>` | `0.300000` | `𝙸𝟷  ·  Screen Space Light Shafts` | — | — | InstanceEditable |
| `Sun Light Shaft Bloom - Max Brightness` | `real<double>` | `0.350000` | `𝙸𝟷  ·  Screen Space Light Shafts` | — | — | InstanceEditable |
| `Sun Light Shaft Bloom - Threshold` | `real<double>` | `0.750000` | `𝙸𝟷  ·  Screen Space Light Shafts` | — | — | InstanceEditable |
| `Sun Light Shaft Bloom - Tint Color` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `𝙸𝟷  ·  Screen Space Light Shafts` | — | — | InstanceEditable |
| `Enable Moon Light Shaft Bloom` | `bool` | `False` | `𝙸𝟷  ·  Screen Space Light Shafts` | — | — | InstanceEditable |
| `Moon Light Shaft Bloom - Scale` | `real<double>` | `0.400000` | `𝙸𝟷  ·  Screen Space Light Shafts` | — | — | InstanceEditable |
| `Moon Light Shaft Bloom - Max Brightness` | `real<double>` | `0.150000` | `𝙸𝟷  ·  Screen Space Light Shafts` | — | — | InstanceEditable |
| `Moon Light Shaft Bloom - Threshold` | `real<double>` | `0.150000` | `𝙸𝟷  ·  Screen Space Light Shafts` | — | — | InstanceEditable |
| `Moon Light Shaft Bloom - Tint Color` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `𝙸𝟷  ·  Screen Space Light Shafts` | — | — | InstanceEditable |
| `Volumetric Clouds Replacement` | `byte<UDS_SkyMode>` | `NewEnumerator6` | `𝙾𝟷  ·  Mobile` | — | — | InstanceEditable |
| `Real Time Capture Sky Light Replacement` | `byte<UDS_SkyLightMode>` | `NewEnumerator2` | `𝙾𝟷  ·  Mobile` | — | — | InstanceEditable |
| `Volumetric Aurora Replacement` | `byte<UDS_SkyMode>` | `NewEnumerator4` | `𝙾𝟷  ·  Mobile` | — | — | InstanceEditable |
| `Platform Feature Levels` | `TMap<string<UDS_RenderingFeatureLevel>>, :/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_RenderingFeatureLevel.UDS_RenderingFeatureLevel>` | `()` | `𝙾𝟷  ·  Mobile` | — | — | InstanceEditable |
| `Simulate Real Sun` | `bool` | `False` | `𝙳𝟷  ·  Simulation` | — | — | InstanceEditable |
| `Simulate Real Moon` | `bool` | `False` | `𝙳𝟷  ·  Simulation` | — | — | InstanceEditable |
| `Simulate Real Stars` | `bool` | `False` | `𝙳𝟷  ·  Simulation` | — | — | InstanceEditable |
| `Location Preset` | `byte<UDS_CityPresets>` | `NewEnumerator0` | `𝙳𝟷  ·  Simulation` | — | — | InstanceEditable |
| `Latitude` | `real<double>` | `51.178856` | `𝙳𝟷  ·  Simulation` | — | — | InstanceEditable, ExposeToCinematics |
| `Longitude` | `real<double>` | `-1.826185` | `𝙳𝟷  ·  Simulation` | — | — | InstanceEditable, ExposeToCinematics |
| `Time Zone` | `real<double>` | `0.000000` | `𝙳𝟷  ·  Simulation` | — | — | InstanceEditable, ExposeToCinematics |
| `Month` | `int` | `3` | `𝙳𝟷  ·  Simulation` | Replicated | `OnRep_Month` | InstanceEditable, ExposeToCinematics |
| `Day` | `int` | `26` | `𝙳𝟷  ·  Simulation` | Replicated | `OnRep_Day` | InstanceEditable, ExposeToCinematics |
| `Year` | `int` | `2021` | `𝙳𝟷  ·  Simulation` | Replicated | `OnRep_Year` | InstanceEditable, ExposeToCinematics |
| `North Yaw` | `real<double>` | `0.000000` | `𝙳𝟷  ·  Simulation` | — | — | InstanceEditable, ExposeToCinematics |
| `Simulation Speed` | `real<double>` | `1.000000` | `𝙳𝟷  ·  Simulation` | Replicated | — | InstanceEditable, ExposeToCinematics |
| `Use System Time` | `bool` | `False` | `𝙳𝟷  ·  Simulation` | Replicated | `OnRep_Use System Time` | InstanceEditable |
| `Apply Daylight Savings Time` | `bool` | `True` | `𝙳𝟷  ·  Simulation` | — | — | InstanceEditable |
| `Calendar` | `object<UDS_Calendar_C>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Calendar.UDS_Calendar_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Calendars/Gregorian_Calendar.Gregorian_Calendar'` | `𝙳𝟷  ·  Simulation` | — | — | InstanceEditable |
| `Simulation Speed Night Multiplier` | `real<double>` | `1.000000` | `𝙳𝟷  ·  Simulation` | Replicated | — | InstanceEditable, ExposeToCinematics |
| `DST Start Month` | `int` | `3` | `𝙳𝟷  ·  Simulation` | — | — | InstanceEditable |
| `DST Start Day of the Week` | `int` | `6` | `𝙳𝟷  ·  Simulation` | — | — | InstanceEditable |
| `DST Start Day Count` | `int` | `0` | `𝙳𝟷  ·  Simulation` | — | — | InstanceEditable |
| `Allow DST` | `bool` | `False` | `System - Time` | — | — | InstanceEditable, Private |
| `DST Start Day` | `int` | `14` | `System - Time` | — | — | InstanceEditable, Private |
| `DST Start Hour` | `int` | `1` | `𝙳𝟷  ·  Simulation` | — | — | InstanceEditable |
| `DST End Month` | `int` | `10` | `𝙳𝟷  ·  Simulation` | — | — | InstanceEditable |
| `DST End Day of the Week` | `int` | `6` | `𝙳𝟷  ·  Simulation` | — | — | InstanceEditable |
| `DST End Day Count` | `int` | `0` | `𝙳𝟷  ·  Simulation` | — | — | InstanceEditable |
| `Stellar Calibration` | `real<double>` | `0.000000` | `System - Simulation` | — | — | InstanceEditable, Private |
| `Lunar Orbit Calibration` | `real<double>` | `0.358600` | `System - Simulation` | — | — | InstanceEditable, Private |
| `Lunar Inclination Calibration` | `real<double>` | `0.642000` | `System - Simulation` | — | — | InstanceEditable, Private |
| `Daylight Savings Time` | `bool` | `False` | `System - Simulation` | — | — | InstanceEditable, Private |
| `DST Start Year Progress` | `real<double>` | `0.000000` | `System - Time` | — | — | InstanceEditable, Private |
| `DST End Day` | `int` | `7` | `System - Time` | — | — | InstanceEditable, Private |
| `DST End Year Progress` | `real<double>` | `0.000000` | `System - Time` | — | — | InstanceEditable, Private |
| `Total Days Elapsed` | `int` | `0` | `System - Time` | — | — | InstanceEditable, Private |
| `Preview Cloud Movement in Editor` | `bool` | `True` | `𝙲𝟺  ·  Cloud Movement` | — | — | InstanceEditable |
| `Clouds Move with Time of Day` | `bool` | `False` | `𝙲𝟺  ·  Cloud Movement` | — | — | InstanceEditable |
| `Time of Day Movement Multiplier` | `real<double>` | `1.000000` | `𝙲𝟺  ·  Cloud Movement` | — | — | InstanceEditable, ExposeToCinematics |
| `Sky MID Parent Instances` | `TMap<string<MaterialInstance>>, :/Script/Engine.MaterialInstance>` | `(("", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_B.UDS_B"),("A", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_A.UDS_A"),("AD", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_AD.UDS_AD"),("ADO", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_ADO.UDS_ADO"),("CA", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_CA.UDS_CA"),("CAD", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_CAD.UDS_CAD"),("CADO", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_CADO.UDS_CADO"),("CD", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_CD.UDS_CD"),("CDO", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_CDO.UDS_CDO"),("CS", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_CS.UDS_CS"),("D", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_D.UDS_D"),("DO", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_DO.UDS_DO"),("K", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_K.UDS_K"),("KA", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KA.UDS_KA"),("KAD", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KAD.UDS_KAD"),("KADO", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KADO.UDS_KADO"),("KCA", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KCA.UDS_KCA"),("KCAD", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KCAD.UDS_KCAD"),("KCADO", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KCADO.UDS_KCADO"),("KCD", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KCD.UDS_KCD"),("KCDO", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KCDO.UDS_KCDO"),("KCS", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KCS.UDS_KCS"),("KD", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KD.UDS_KD"),("KDO", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KDO.UDS_KDO"),("KS", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KS.UDS_KS"),("P", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_P.UDS_P"),("PC", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_PC.UDS_PC"),("S", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_S.UDS_S"),("C", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_C.UDS_C"),("KC", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KC.UDS_KC"),("KAS", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KAS.UDS_KAS"),("KCAS", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KCAS.UDS_KCAS"),("AS", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_AS.UDS_AS"),("CAS", "/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_CAS.UDS_CAS"))` | `System - Sky Material` | — | — | InstanceEditable, Private |
| `Fog Shadows` | `real<double>` | `0.800000` | `𝙴𝟻  ·  Cloud Shadows` | — | — | InstanceEditable, ExposeToCinematics |
| `Dust Shadows` | `real<double>` | `1.000000` | `𝙴𝟻  ·  Cloud Shadows` | — | — | InstanceEditable, ExposeToCinematics |
| `2D Cloud Shadows Speed` | `real<double>` | `1.000000` | `𝙴𝟻  ·  Cloud Shadows` | — | — | InstanceEditable |
| `2D Cloud Shadows Scale` | `real<double>` | `450000.000000` | `𝙴𝟻  ·  Cloud Shadows` | — | — | InstanceEditable |
| `2D Cloud Shadows Light Angle Offset Scale` | `real<double>` | `1.000000` | `𝙴𝟻  ·  Cloud Shadows` | — | — | InstanceEditable |
| `Correct Specular Scale for Low Angle Cloud Shadows` | `bool` | `False` | `𝙴𝟻  ·  Cloud Shadows` | — | — | InstanceEditable |
| `Disable Directional Light Shadows when Fully Shadowed by Clouds` | `bool` | `True` | `𝙴𝟻  ·  Cloud Shadows` | — | — | InstanceEditable |
| `Custom Light Function Material` | `object<MaterialInterface>` | `None` | `𝙴𝟻  ·  Cloud Shadows` | — | — | InstanceEditable |
| `Force Light Functions On` | `bool` | `True` | `𝙴𝟻  ·  Cloud Shadows` | — | — | InstanceEditable |
| `Time of Day Replication Period` | `real<double>` | `1.000000` | `𝙱𝟷  ·  Animate Time Of Day` | — | — | InstanceEditable |
| `Replicated Time of Day` | `real<double>` | `-1.000000` | `System - Replication` | Replicated (COND_SkipOwner) | `OnRep_Replicated Time of Day` | InstanceEditable, Private |
| `Render Moon Directional Light` | `bool` | `True` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable |
| `Custom Moon Light Actor` | `object<DirectionalLight>` | `None` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable |
| `Scale Moon Radius as it Nears Horizon` | `real<double>` | `1.000000` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Fog Colors from Sky Atmosphere` | `bool` | `False` | `Mode Derivatives` | — | — | InstanceEditable, Private |
| `Dusty Height Fog Falloff` | `real<double>` | `0.030000` | `𝙵𝟸  ·  Fog Density` | — | — | InstanceEditable, ExposeToCinematics |
| `Moon Specular Scale` | `real<double>` | `0.100000` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Ambient Light from Sky Atmosphere` | `real<double>` | `0.000000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Volumetric Cloud Ambient Light Bottom Scale` | `real<double>` | `0.850000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Volumetric Cloud Ambient Light Top Scale` | `real<double>` | `1.000000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Change to Simplified Material when Overcast` | `bool` | `True` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Simplified Material Cloud Coverage Threshold` | `real<double>` | `2.100000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Simplified Material Fade Length` | `real<double>` | `0.200000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Scale View Samples when Overcast` | `real<double>` | `0.700000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Clouds Position` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Hidden Cloud Movement` | Replicated (COND_InitialOnly) | — | InstanceEditable |
| `Cloud Phase Vector Multiplier` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `System - Cloud Movement` | — | — | InstanceEditable, Private |
| `Rayleigh Scattering Color (Day)` | `struct<LinearColor>` | `(R=0.168627,G=0.407843,B=1.000000,A=1.000000)` | `𝙶𝟷  ·  Sky Atmosphere` | — | — | InstanceEditable, ExposeToCinematics |
| `Rayleigh Scattering Color (Dawn/Dusk)` | `struct<LinearColor>` | `(R=0.170000,G=0.409234,B=1.000000,A=1.000000)` | `𝙶𝟷  ·  Sky Atmosphere` | — | — | InstanceEditable, ExposeToCinematics |
| `Rayleigh Scattering Color (Night)` | `struct<LinearColor>` | `(R=0.241211,G=0.347328,B=0.609375,A=1.000000)` | `𝙶𝟷  ·  Sky Atmosphere` | — | — | InstanceEditable, ExposeToCinematics |
| `Desaturate Rayleigh Scattering when Cloudy` | `real<double>` | `0.400000` | `𝙶𝟷  ·  Sky Atmosphere` | — | — | InstanceEditable, ExposeToCinematics |
| `Current Time of Day Offset` | `real<double>` | `0.000000` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Last Frame Time of Day` | `real<double>` | `-5.000000` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Time of Day Change Speed` | `real<double>` | `0.000000` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Night Sky Glow` | `real<double>` | `0.600000` | `𝙷𝟹  ·  Sky Glow` | — | — | InstanceEditable, ExposeToCinematics |
| `Night Sky Glow Color` | `struct<LinearColor>` | `(R=0.093045,G=0.141694,B=0.255208,A=1.000000)` | `𝙷𝟹  ·  Sky Glow` | — | — | InstanceEditable, ExposeToCinematics |
| `Light Pollution Intensity` | `real<double>` | `0.000000` | `𝙷𝟹  ·  Sky Glow` | — | — | InstanceEditable, ExposeToCinematics |
| `Light Pollution Color` | `struct<LinearColor>` | `(R=0.630208,G=0.481016,B=0.377575,A=1.000000)` | `𝙷𝟹  ·  Sky Glow` | — | — | InstanceEditable, ExposeToCinematics |
| `Cloud Fog Post Process MID` | `object<MaterialInstanceDynamic>` | `None` | `Dynamic Material Instances` | — | — | InstanceEditable, Private |
| `Dimming Range` | `struct<FloatRange>` | `(LowerBound=(Value=1.400000),UpperBound=(Value=2.000000))` | `𝙴𝟺  ·  Directional Light` | — | — | InstanceEditable |
| `Dimming Range Exponent` | `real<double>` | `2.000000` | `𝙴𝟺  ·  Directional Light` | — | — | InstanceEditable, ExposeToCinematics |
| `Custom Sky Sphere Material` | `object<MaterialInterface>` | `None` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Fog Snow Contribution` | `real<double>` | `0.000000` | `Hidden Exposed` | — | — | InstanceEditable |
| `Midnight` | `mcdelegate` | `()` | `Time Dispatchers` | — | — | InstanceEditable, Private |
| `Sunset/Sunrise Color (Absorption)` | `struct<LinearColor>` | `(R=0.198069,G=0.095307,B=1.000000,A=1.000000)` | `𝙶𝟷  ·  Sky Atmosphere` | — | — | InstanceEditable, ExposeToCinematics |
| `Sunset/Sunrise Color Intensity (Absorption Scale)` | `real<double>` | `0.002000` | `𝙶𝟷  ·  Sky Atmosphere` | — | — | InstanceEditable, ExposeToCinematics |
| `Simulated Sunrise Time` | `real<double>` | `0.000000` | `System - Simulation` | Replicated | — | InstanceEditable, Private |
| `Simulated Sunset Time` | `real<double>` | `0.000000` | `System - Simulation` | Replicated | — | InstanceEditable, Private |
| `Base Cloud Height` | `real<double>` | `15.000000` | `System - Volumetric Clouds` | — | — | InstanceEditable, Private |
| `Enable Sun Lens Flare` | `bool` | `False` | `𝙸𝟸  ·  Lens Flare` | — | — | InstanceEditable |
| `Lens Flare Type` | `byte<UDS_LensFlareType>` | `NewEnumerator0` | `𝙸𝟸  ·  Lens Flare` | — | — | InstanceEditable |
| `Lens Flare Strength` | `real<double>` | `0.300000` | `𝙸𝟸  ·  Lens Flare` | — | — | InstanceEditable |
| `Lens Flare Tint` | `struct<LinearColor>` | `(R=1.000000,G=0.710467,B=0.440498,A=1.000000)` | `𝙸𝟸  ·  Lens Flare` | — | — | InstanceEditable |
| `Lens Flare MID` | `object<MaterialInstanceDynamic>` | `None` | `Dynamic Material Instances` | — | — | InstanceEditable, Private |
| `Lens Flare Brightness Threshold` | `real<double>` | `0.950000` | `𝙸𝟸  ·  Lens Flare` | — | — | InstanceEditable |
| `Custom Lens Flare Parent Instance` | `object<MaterialInterface>` | `None` | `𝙸𝟸  ·  Lens Flare` | — | — | InstanceEditable |
| `Scale Flare Elements` | `real<double>` | `1.000000` | `𝙸𝟸  ·  Lens Flare` | — | — | InstanceEditable |
| `Dynamic Sky Light Transition Time` | `real<double>` | `0.000000` | `System - Sky Light` | — | — | InstanceEditable, Private |
| `Target Sky Light Multiplier` | `real<double>` | `1.000000` | `System - Sky Light` | — | — | InstanceEditable, Private |
| `Dynamic Sky Light Multiplier` | `real<double>` | `1.000000` | `System - Sky Light` | — | — | InstanceEditable, Private |
| `Cloud Coverage 0-3` | `real<double>` | `0.000000` | `Common Derivatives` | — | — | InstanceEditable, Private |
| `Global Overcast 0-1` | `real<double>` | `0.000000` | `Common Derivatives` | — | — | InstanceEditable, Private |
| `Local Overcast 0-1` | `real<double>` | `0.000000` | `Common Derivatives` | — | — | InstanceEditable, Private |
| `Override with New Changes` | `bool` | `True` | `System - State` | — | — | InstanceEditable, Private |
| `Scale View Samples when Camera is In Cloud Layer` | `real<double>` | `2.000000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Low Material Quality Sample Count Scale` | `real<double>` | `0.800000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Medium Material Quality Sample Count Scale` | `real<double>` | `0.900000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Epic Material Quality Sample Count Scale` | `real<double>` | `1.150000` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `2D Overcast Turbulence Texture` | `softobject<Texture2D>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/Clouds/CloudsTurbulence.CloudsTurbulence` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Epic Quality Volume Texture` | `softobject<VolumeTexture>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/3D_Clouds/3DCells_128.3DCells_128` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `High Quality Volume Texture` | `softobject<VolumeTexture>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/3D_Clouds/3D_Cells_64.3D_Cells_64` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Low Quality Volume Texture` | `softobject<VolumeTexture>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/3D_Clouds/3D_Cells_32.3D_Cells_32` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Inside Cloud Fog Parent Material` | `softobject<MaterialInterface>` | `/Game/_ThirdParty/UltraDynamicSky/Materials/Inside_Clouds_Fog_Particle.Inside_Clouds_Fog_Particle` | `System - Volumetric Clouds` | — | — | InstanceEditable, Private |
| `Post Process Cloud Fog Parent Material` | `softobject<MaterialInterface>` | `/Game/_ThirdParty/UltraDynamicSky/Materials/Cloud_Fog_PostProcess.Cloud_Fog_PostProcess` | `System - Volumetric Clouds` | — | — | InstanceEditable, Private |
| `Moon Light Current Intensity Value` | `real<double>` | `0.000000` | `System - Moon` | — | — | InstanceEditable, Private |
| `Twilight Color (Absorption)` | `struct<LinearColor>` | `(R=0.030354,G=0.181178,B=1.000000,A=1.000000)` | `𝙶𝟷  ·  Sky Atmosphere` | — | — | InstanceEditable, ExposeToCinematics |
| `Twilight Color Intensity (Absorption Scale)` | `real<double>` | `0.004000` | `𝙶𝟷  ·  Sky Atmosphere` | — | — | InstanceEditable, ExposeToCinematics |
| `Base Sky Color (Day)` | `struct<LinearColor>` | `(R=0.050313,G=0.100844,B=0.218750,A=1.000000)` | `𝙶𝟸  ·  Simplified Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Base Sky Color (Dawn/Dusk)` | `struct<LinearColor>` | `(R=0.094145,G=0.167055,B=0.260417,A=1.000000)` | `𝙶𝟸  ·  Simplified Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Base Sky Color (Night)` | `struct<LinearColor>` | `(R=0.065593,G=0.102341,B=0.161458,A=1.000000)` | `𝙶𝟸  ·  Simplified Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Cloud Light Color (Day)` | `struct<LinearColor>` | `(R=0.708631,G=0.785507,B=0.901042,A=1.000000)` | `𝙶𝟸  ·  Simplified Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Cloud Light Color (Dawn/Dusk)` | `struct<LinearColor>` | `(R=1.000000,G=0.477468,B=0.054318,A=1.000000)` | `𝙶𝟸  ·  Simplified Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Cloud Light Color (Night)` | `struct<LinearColor>` | `(R=1.177604,G=1.321682,B=1.700000,A=1.000000)` | `𝙶𝟸  ·  Simplified Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Cloud Dark Color (Day)` | `struct<LinearColor>` | `(R=0.034505,G=0.119041,B=0.276042,A=1.000000)` | `𝙶𝟸  ·  Simplified Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Cloud Dark Color (Dawn/Dusk)` | `struct<LinearColor>` | `(R=0.043050,G=0.069910,B=0.119792,A=1.000000)` | `𝙶𝟸  ·  Simplified Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Cloud Dark Color (Night)` | `struct<LinearColor>` | `(R=0.070258,G=0.109470,B=0.182292,A=1.000000)` | `𝙶𝟸  ·  Simplified Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Directional Intensity Curve` | `object<CurveFloat>` | `/Script/Engine.CurveFloat'/Game/_ThirdParty/UltraDynamicSky/Materials/Float_Curves/Directional_Light_Intensity.Directional_Light_Intensity'` | `𝙶𝟸  ·  Simplified Color` | — | — | InstanceEditable |
| `Directional Light Scattering Curve` | `object<CurveLinearColor>` | `/Script/Engine.CurveLinearColor'/Game/_ThirdParty/UltraDynamicSky/Materials/Color_Curves/Sun_Light_Color.Sun_Light_Color'` | `𝙶𝟸  ·  Simplified Color` | — | — | InstanceEditable |
| `Render Exponential Height Fog` | `bool` | `True` | `𝙵𝟷  ·  Fog Color` | — | — | InstanceEditable |
| `Custom Height Fog Actor` | `object<ExponentialHeightFog>` | `None` | `𝙵𝟷  ·  Fog Color` | — | — | InstanceEditable |
| `Fog Color Mode` | `byte<UDS_FogColorMode>` | `NewEnumerator2` | `𝙵𝟷  ·  Fog Color` | — | — | InstanceEditable |
| `Fog Color Intensity Scale` | `real<double>` | `1.000000` | `𝙵𝟷  ·  Fog Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Overcast Brightness Day` | `real<double>` | `0.200000` | `𝙵𝟷  ·  Fog Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Overcast Brightness Night` | `real<double>` | `0.200000` | `𝙵𝟷  ·  Fog Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Sky Atmosphere Fog Influence Sun` | `real<double>` | `2.300000` | `𝙵𝟷  ·  Fog Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Sky Atmosphere Fog Influence Moon` | `real<double>` | `1.650000` | `𝙵𝟷  ·  Fog Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Sky Atmosphere Fog Influence None` | `real<double>` | `0.800000` | `𝙵𝟷  ·  Fog Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Fog Inscattering Color Curve` | `object<CurveLinearColor>` | `/Script/Engine.CurveLinearColor'/Game/_ThirdParty/UltraDynamicSky/Materials/Color_Curves/Fog_Scattering_Color.Fog_Scattering_Color'` | `𝙵𝟷  ·  Fog Color` | — | — | InstanceEditable |
| `Fog Inscattering Sun` | `struct<LinearColor>` | `(R=0.083620,G=0.156441,B=0.302083,A=1.000000)` | `𝙵𝟷  ·  Fog Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Fog Inscattering Moon` | `struct<LinearColor>` | `(R=0.076091,G=0.108017,B=0.171875,A=1.000000)` | `𝙵𝟷  ·  Fog Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Fog Directional Inscattering Color Curve` | `object<CurveLinearColor>` | `/Script/Engine.CurveLinearColor'/Game/_ThirdParty/UltraDynamicSky/Materials/Color_Curves/Fog_Directional_Scattering_Color.Fog_Directional_Scattering_Color'` | `𝙵𝟷  ·  Fog Color` | — | — | InstanceEditable |
| `Fog Directional Inscattering` | `struct<LinearColor>` | `(R=0.146484,G=0.147386,B=0.156250,A=1.000000)` | `𝙵𝟷  ·  Fog Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Foggy Desaturation` | `real<double>` | `0.400000` | `𝙵𝟷  ·  Fog Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Overcast Desaturation` | `real<double>` | `0.450000` | `𝙵𝟷  ·  Fog Color` | — | — | InstanceEditable, ExposeToCinematics |
| `All Fog Colors Multiplier` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `𝙵𝟷  ·  Fog Color` | — | — | InstanceEditable, ExposeToCinematics |
| `Dust Amount` | `real<double>` | `0.000000` | `𝙵𝟺  ·  Dust` | — | — | InstanceEditable, ExposeToCinematics |
| `Dust Color` | `struct<LinearColor>` | `(R=0.260417,G=0.216760,B=0.184462,A=1.000000)` | `𝙵𝟺  ·  Dust` | — | — | InstanceEditable, ExposeToCinematics |
| `Use Volumetric Fog` | `bool` | `False` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Volumetric Fog Distance` | `real<double>` | `8000.000000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Volumetric Fog Extinction` | `real<double>` | `2.500000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Sun Volumetric Scattering Intensity` | `real<double>` | `1.000000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable, ExposeToCinematics |
| `Moon Volumetric Scattering Intensity` | `real<double>` | `1.000000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable, ExposeToCinematics |
| `Volumetric Fog Albedo (Day)` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Volumetric Fog Albedo (Dawn/Dusk)` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Volumetric Fog Albedo (Night)` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Disable Height Fog Above Volumetric Cloud Layer` | `bool` | `False` | `𝙵𝟸  ·  Fog Density` | — | — | InstanceEditable |
| `Cached Height Fog Density` | `real<float>` | `0.000000` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Using Post Process Cloud Fog` | `bool` | `False` | `System - Volumetric Clouds` | — | — | InstanceEditable, Private |
| `Ambient Fog Color` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=0.000000)` | `System - Fog` | — | — | InstanceEditable, Private |
| `Directional Base Fog Color` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=0.000000)` | `System - Fog` | — | — | InstanceEditable, Private |
| `Scaled Directional Base Fog Color` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=0.000000)` | `System - Fog` | — | — | InstanceEditable, Private |
| `Volumetric Aurora Parent Material` | `softobject<MaterialInterface>` | `/Game/_ThirdParty/UltraDynamicSky/Materials/Volumetric_Aurora.Volumetric_Aurora` | `System - Aurora` | — | — | InstanceEditable, Private |
| `Using Volumetric Cloud Fog` | `bool` | `False` | `System - Volumetric Clouds` | — | — | InstanceEditable, Private |
| `Forward Shading` | `bool` | `False` | `System - Project Settings` | — | — | InstanceEditable, Private |
| `Hourly` | `mcdelegate` | `()` | `Time Dispatchers` | — | — | InstanceEditable, Private |
| `Event Hour` | `int` | `0` | `System - Time` | — | — | InstanceEditable, Private |
| `Cloud Wisps Color Intensity` | `real<double>` | `1.000000` | `𝙲𝟻  ·  Cloud Wisps` | — | — | InstanceEditable, ExposeToCinematics |
| `Max Moon Source Angle Scale` | `real<double>` | `20.000000` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Transition Time A` | `real<double>` | `0.000000` | `System - Time Transition` | — | — | InstanceEditable, Private |
| `Transition Time B` | `real<double>` | `0.000000` | `System - Time Transition` | — | — | InstanceEditable, Private |
| `Transitioning Time` | `bool` | `False` | `System - Time Transition` | Replicated | — | InstanceEditable, Private |
| `Transition Easing Function` | `byte<EEasingFunc>` | `EaseInOut` | `System - Time Transition` | — | — | InstanceEditable, Private |
| `Transition Easing Exponent` | `real<double>` | `2.000000` | `System - Time Transition` | — | — | InstanceEditable, Private |
| `Transition Timer` | `struct<TimerHandle>` | `()` | `System - Time Transition` | — | — | InstanceEditable, Private |
| `Transition Duration` | `real<double>` | `0.000000` | `System - Time Transition` | — | — | InstanceEditable, Private |
| `Transition Days Counted` | `int` | `0` | `System - Time Transition` | — | — | InstanceEditable, Private |
| `Transition Can Go Backwards` | `bool` | `False` | `System - Time Transition` | — | — | InstanceEditable, Private |
| `Moon Source Angle Softness` | `real<double>` | `0.300000` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Exposure Bias Day` | `real<double>` | `0.000000` | `𝙴𝟼  ·  Exposure` | — | — | InstanceEditable, ExposeToCinematics |
| `Exposure Bias Dawn/Dusk` | `real<double>` | `0.000000` | `𝙴𝟼  ·  Exposure` | — | — | InstanceEditable, ExposeToCinematics |
| `Exposure Bias Night` | `real<double>` | `0.000000` | `𝙴𝟼  ·  Exposure` | — | — | InstanceEditable, ExposeToCinematics |
| `Exposure Bias Cloudy` | `real<double>` | `0.000000` | `𝙴𝟼  ·  Exposure` | — | — | InstanceEditable, ExposeToCinematics |
| `Exposure Bias Foggy` | `real<double>` | `0.000000` | `𝙴𝟼  ·  Exposure` | — | — | InstanceEditable, ExposeToCinematics |
| `Exposure Bias Dusty` | `real<double>` | `0.000000` | `𝙴𝟼  ·  Exposure` | — | — | InstanceEditable, ExposeToCinematics |
| `Exposure Brightness Range` | `struct<FloatRange>` | `(LowerBound=(Value=-10.000000),UpperBound=(Value=20.000000))` | `𝙴𝟼  ·  Exposure` | — | — | InstanceEditable |
| `Apply Interior Adjustments` | `bool` | `False` | `𝙽𝟷  ·  Interior Adjustments` | — | — | InstanceEditable, ExposeToCinematics |
| `Extra Fog Start Distance in Interior` | `real<double>` | `0.000000` | `𝙽𝟷  ·  Interior Adjustments` | — | — | InstanceEditable, ExposeToCinematics |
| `Fog Density Multiplier in Interior` | `real<double>` | `1.000000` | `𝙽𝟷  ·  Interior Adjustments` | — | — | InstanceEditable, ExposeToCinematics |
| `Exposure Bias in Interior` | `real<double>` | `0.000000` | `𝙽𝟷  ·  Interior Adjustments` | — | — | InstanceEditable, ExposeToCinematics |
| `Sky Light Intensity Multiplier in Interiors` | `real<double>` | `1.000000` | `𝙽𝟷  ·  Interior Adjustments` | — | — | InstanceEditable, ExposeToCinematics |
| `Sun Light Intensity Multiplier in Interiors` | `real<double>` | `1.000000` | `𝙽𝟷  ·  Interior Adjustments` | — | — | InstanceEditable, ExposeToCinematics |
| `Moon Light Intensity Multiplier in Interiors` | `real<double>` | `1.000000` | `𝙽𝟷  ·  Interior Adjustments` | — | — | InstanceEditable, ExposeToCinematics |
| `Extra Sun Volumetric Scattering in Interiors` | `real<double>` | `0.000000` | `𝙽𝟷  ·  Interior Adjustments` | — | — | InstanceEditable, ExposeToCinematics |
| `Extra Moon Volumetric Scattering in Interiors` | `real<double>` | `0.000000` | `𝙽𝟷  ·  Interior Adjustments` | — | — | InstanceEditable, ExposeToCinematics |
| `Cached Inverted Global Occlusion` | `real<double>` | `0.000000` | `𝙽𝟷  ·  Interior Adjustments` | — | — | InstanceEditable, Private |
| `Cloud Shadow Disable Threshold` | `real<double>` | `3.000000` | `System - Cloud Shadows` | — | — | InstanceEditable, Private |
| `Cloud Bottom World Height` | `real<double>` | `0.000000` | `System - Volumetric Clouds` | — | — | InstanceEditable, Private |
| `Cached Night Filter` | `real<double>` | `0.000000` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Cached Floats Old` | `TArray<real<double>>` | — | `System - Cache` | — | — | InstanceEditable, Private |
| `Cached Floats New` | `TArray<real<double>>` | — | `System - Cache` | — | — | InstanceEditable, Private |
| `Cached Floats Last Accessed` | `TArray<real<double>>` | — | `System - Cache` | — | — | InstanceEditable, Private |
| `Cache Alpha` | `real<double>` | `1.000000` | `System - Cache` | — | — | InstanceEditable, Private |
| `Filling Starting Cache` | `bool` | `True` | `System - Cache` | — | — | InstanceEditable, Private |
| `Cached Colors Old` | `TArray<struct<LinearColor>>` | — | `System - Cache` | — | — | InstanceEditable, Private |
| `Cached Colors New` | `TArray<struct<LinearColor>>` | — | `System - Cache` | — | — | InstanceEditable, Private |
| `Cached Sun Vector` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Cached Sun Z Vector` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Cached Moon Vector` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Max Property Cache Period` | `real<double>` | `1.500000` | `𝙼𝟸  ·  Scalability / Performance` | — | — | InstanceEditable |
| `Preset Location Coordinates` | `TMap<byte<Vector>>, :/Script/CoreUObject.Vector>` | `((NewEnumerator1, (X=5.550000,Y=-0.200000,Z=0.000000)),(NewEnumerator2, (X=9.030000,Y=38.740000,Z=3.000000)),(NewEnumerator3, (X=-34.920000,Y=138.600000,Z=9.500000)),(NewEnumerator4, (X=36.750000,Y=3.050000,Z=1.000000)),(NewEnumerator5, (X=43.270000,Y=76.890000,Z=6.000000)),(NewEnumerator6, (X=31.940000,Y=35.930000,Z=2.000000)),(NewEnumerator7, (X=52.360000,Y=4.900000,Z=1.000000)),(NewEnumerator8, (X=64.730000,Y=177.510000,Z=12.000000)),(NewEnumerator9, (X=61.210000,Y=-149.890000,Z=-9.000000)),(NewEnumerator10, (X=39.930000,Y=32.850000,Z=3.000000)),(NewEnumerator11, (X=-18.930000,Y=47.510000,Z=3.000000)),(NewEnumerator12, (X=-25.300000,Y=-57.630000,Z=-4.000000)),(NewEnumerator13, (X=37.980000,Y=23.720000,Z=2.000000)),(NewEnumerator14, (X=33.740000,Y=-84.390000,Z=-5.000000)),(NewEnumerator15, (X=-36.840000,Y=174.740000,Z=12.000000)),(NewEnumerator16, (X=33.330000,Y=44.380000,Z=3.000000)),(NewEnumerator17, (X=13.750000,Y=100.490000,Z=7.000000)),(NewEnumerator18, (X=41.380000,Y=2.180000,Z=1.000000)),(NewEnumerator19, (X=39.900000,Y=116.390000,Z=8.000000)),(NewEnumerator20, (X=33.880000,Y=35.510000,Z=2.000000)),(NewEnumerator21, (X=44.810000,Y=20.450000,Z=1.000000)),(NewEnumerator22, (X=12.970000,Y=77.590000,Z=5.500000)),(NewEnumerator23, (X=52.520000,Y=13.400000,Z=1.000000)),(NewEnumerator24, (X=4.710000,Y=-74.070000,Z=-5.000000)),(NewEnumerator25, (X=42.360000,Y=-71.050000,Z=-5.000000)),(NewEnumerator26, (X=-15.790000,Y=-47.880000,Z=-3.000000)),(NewEnumerator27, (X=-27.460000,Y=153.020000,Z=10.000000)),(NewEnumerator28, (X=50.840000,Y=4.350000,Z=1.000000)),(NewEnumerator29, (X=44.430000,Y=26.100000,Z=2.000000)),(NewEnumerator30, (X=47.490000,Y=19.050000,Z=1.000000)),(NewEnumerator31, (X=-34.600000,Y=-58.380000,Z=-3.000000)),(NewEnumerator32, (X=30.040000,Y=31.230000,Z=2.000000)),(NewEnumerator33, (X=51.040000,Y=-114.050000,Z=-7.000000)),(NewEnumerator34, (X=-35.290000,Y=149.120000,Z=10.000000)),(NewEnumerator35, (X=-33.920000,Y=18.420000,Z=2.000000)),(NewEnumerator36, (X=10.480000,Y=-66.900000,Z=-4.000000)),(NewEnumerator37, (X=33.530000,Y=-7.580000,Z=1.000000)),(NewEnumerator38, (X=41.880000,Y=-87.620000,Z=-6.000000)),(NewEnumerator39, (X=55.670000,Y=12.560000,Z=1.000000)),(NewEnumerator40, (X=32.770000,Y=-96.800000,Z=-6.000000)),(NewEnumerator41, (X=-6.800000,Y=39.280000,Z=3.000000)),(NewEnumerator42, (X=-12.430000,Y=130.840000,Z=9.500000)),(NewEnumerator43, (X=39.730000,Y=-104.980000,Z=-7.000000)),(NewEnumerator44, (X=42.330000,Y=-83.040000,Z=-5.000000)),(NewEnumerator45, (X=23.760000,Y=90.380000,Z=6.000000)),(NewEnumerator46, (X=25.380000,Y=51.530000,Z=3.000000)),(NewEnumerator47, (X=25.260000,Y=55.390000,Z=4.000000)),(NewEnumerator48, (X=53.350000,Y=-6.260000,Z=0.000000)),(NewEnumerator49, (X=53.530000,Y=-113.490000,Z=-7.000000)),(NewEnumerator50, (X=50.110000,Y=8.680000,Z=1.000000)),(NewEnumerator51, (X=14.610000,Y=-90.530000,Z=-6.000000)),(NewEnumerator52, (X=44.860000,Y=-63.710000,Z=-4.000000)),(NewEnumerator53, (X=21.020000,Y=105.850000,Z=7.000000)),(NewEnumerator54, (X=-17.820000,Y=31.050000,Z=2.000000)),(NewEnumerator55, (X=23.130000,Y=-82.350000,Z=-5.000000)),(NewEnumerator56, (X=60.170000,Y=24.930000,Z=2.000000)),(NewEnumerator57, (X=22.300000,Y=114.200000,Z=8.000000)),(NewEnumerator58, (X=21.300000,Y=-157.850000,Z=-10.000000)),(NewEnumerator59, (X=29.760000,Y=-95.380000,Z=-6.000000)),(NewEnumerator60, (X=39.760000,Y=-86.150000,Z=-5.000000)),(NewEnumerator61, (X=33.690000,Y=73.060000,Z=5.000000)),(NewEnumerator62, (X=41.010000,Y=28.950000,Z=3.000000)),(NewEnumerator63, (X=-6.200000,Y=106.810000,Z=7.000000)),(NewEnumerator64, (X=31.780000,Y=35.210000,Z=2.000000)),(NewEnumerator65, (X=-26.200000,Y=28.040000,Z=2.000000)),(NewEnumerator66, (X=34.520000,Y=69.170000,Z=4.500000)),(NewEnumerator67, (X=24.860000,Y=67.010000,Z=5.000000)),(NewEnumerator68, (X=27.710000,Y=85.320000,Z=5.750000)),(NewEnumerator69, (X=15.500000,Y=32.560000,Z=2.000000)),(NewEnumerator70, (X=17.970000,Y=-76.790000,Z=-5.000000)),(NewEnumerator71, (X=-4.320000,Y=15.320000,Z=1.000000)),(NewEnumerator72, (X=1.850000,Y=-157.400000,Z=14.000000)),(NewEnumerator73, (X=22.560000,Y=88.730000,Z=5.500000)),(NewEnumerator74, (X=3.140000,Y=101.690000,Z=8.000000)),(NewEnumerator75, (X=29.360000,Y=47.970000,Z=3.000000)),(NewEnumerator76, (X=50.450000,Y=30.520000,Z=2.000000)),(NewEnumerator77, (X=-16.500000,Y=-68.150000,Z=-4.000000)),(NewEnumerator78, (X=6.450000,Y=3.380000,Z=1.000000)),(NewEnumerator79, (X=31.540000,Y=74.340000,Z=5.000000)),(NewEnumerator80, (X=36.175000,Y=-115.130000,Z=-8.000000)),(NewEnumerator81, (X=-12.060000,Y=-77.030000,Z=-5.000000)),(NewEnumerator82, (X=38.720000,Y=-9.150000,Z=0.000000)),(NewEnumerator83, (X=51.500000,Y=-0.120000,Z=0.000000)),(NewEnumerator84, (X=34.050000,Y=-118.250000,Z=-8.000000)),(NewEnumerator85, (X=40.410000,Y=-3.700000,Z=1.000000)),(NewEnumerator86, (X=12.130000,Y=-86.250000,Z=-6.000000)),(NewEnumerator87, (X=14.590000,Y=120.970000,Z=8.000000)),(NewEnumerator104, (X=-77.840000,Y=166.660000,Z=12.000000)),(NewEnumerator88, (X=-37.810000,Y=144.960000,Z=10.000000)),(NewEnumerator89, (X=19.430000,Y=-99.130000,Z=-6.000000)),(NewEnumerator90, (X=25.770000,Y=-80.200000,Z=-5.000000)),(NewEnumerator91, (X=44.980000,Y=-93.260000,Z=-6.000000)),(NewEnumerator92, (X=53.900000,Y=27.560000,Z=3.000000)),(NewEnumerator93, (X=-34.880000,Y=-56.180000,Z=-3.000000)),(NewEnumerator94, (X=45.500000,Y=-73.550000,Z=-5.000000)),(NewEnumerator95, (X=55.750000,Y=37.610000,Z=3.000000)),(NewEnumerator96, (X=19.060000,Y=72.800000,Z=5.500000)),(NewEnumerator97, (X=-1.280000,Y=36.810000,Z=3.000000)),(NewEnumerator98, (X=25.070000,Y=-77.330000,Z=-5.000000)),(NewEnumerator99, (X=28.610000,Y=77.200000,Z=5.500000)),(NewEnumerator100, (X=29.950000,Y=-90.080000,Z=-6.000000)),(NewEnumerator101, (X=40.710000,Y=-74.000000,Z=-5.000000)),(NewEnumerator102, (X=59.910000,Y=10.730000,Z=1.000000)),(NewEnumerator103, (X=45.420000,Y=-75.690000,Z=-5.000000)),(NewEnumerator105, (X=48.850000,Y=2.350000,Z=1.000000)),(NewEnumerator106, (X=-31.950000,Y=115.860000,Z=8.000000)),(NewEnumerator107, (X=39.950000,Y=-75.160000,Z=-5.000000)),(NewEnumerator108, (X=33.440000,Y=-112.070000,Z=-7.000000)),(NewEnumerator109, (X=50.080000,Y=14.420000,Z=1.000000)),(NewEnumerator110, (X=64.140000,Y=-21.940000,Z=0.000000)),(NewEnumerator111, (X=-22.910000,Y=-43.200000,Z=-3.000000)),(NewEnumerator112, (X=24.630000,Y=46.710000,Z=3.000000)),(NewEnumerator113, (X=41.890000,Y=12.480000,Z=1.000000)),(NewEnumerator114, (X=40.760000,Y=-111.890000,Z=-7.000000)),(NewEnumerator115, (X=37.770000,Y=-122.410000,Z=-8.000000)),(NewEnumerator116, (X=18.400000,Y=-66.060000,Z=-4.000000)),(NewEnumerator117, (X=13.690000,Y=-89.190000,Z=-6.000000)),(NewEnumerator118, (X=-33.450000,Y=-70.660000,Z=-4.000000)),(NewEnumerator119, (X=18.460000,Y=-69.950000,Z=-4.000000)),(NewEnumerator120, (X=-23.550000,Y=-46.630000,Z=-3.000000)),(NewEnumerator121, (X=47.600000,Y=-122.330000,Z=-8.000000)),(NewEnumerator122, (X=37.560000,Y=126.990000,Z=9.000000)),(NewEnumerator123, (X=31.220000,Y=121.470000,Z=8.000000)),(NewEnumerator124, (X=1.390000,Y=103.820000,Z=8.000000)),(NewEnumerator125, (X=42.700000,Y=23.330000,Z=2.000000)),(NewEnumerator126, (X=47.480000,Y=-52.790000,Z=-3.500000)),(NewEnumerator127, (X=59.320000,Y=18.060000,Z=1.000000)),(NewEnumerator128, (X=-18.140000,Y=178.440000,Z=12.000000)),(NewEnumerator129, (X=-33.860000,Y=151.210000,Z=10.000000)),(NewEnumerator130, (X=25.060000,Y=121.510000,Z=8.000000)),(NewEnumerator131, (X=59.430000,Y=24.740000,Z=2.000000)),(NewEnumerator132, (X=41.300000,Y=69.260000,Z=5.000000)),(NewEnumerator133, (X=14.100000,Y=-87.210000,Z=-6.000000)),(NewEnumerator134, (X=35.680000,Y=51.380000,Z=3.500000)),(NewEnumerator135, (X=35.680000,Y=139.690000,Z=9.000000)),(NewEnumerator136, (X=43.740000,Y=-79.370000,Z=-5.000000)),(NewEnumerator137, (X=49.260000,Y=-123.110000,Z=-8.000000)),(NewEnumerator138, (X=48.200000,Y=16.360000,Z=1.000000)),(NewEnumerator139, (X=52.230000,Y=21.010000,Z=1.000000)),(NewEnumerator140, (X=38.900000,Y=-77.010000,Z=-5.000000)),(NewEnumerator141, (X=49.880000,Y=-97.140000,Z=-6.000000)),(NewEnumerator142, (X=16.790000,Y=96.160000,Z=6.500000)),(NewEnumerator143, (X=45.810000,Y=15.980000,Z=1.000000)),(NewEnumerator144, (X=47.370000,Y=8.540000,Z=1.000000)))` | `System - Simulation` | — | — | InstanceEditable, Private |
| `Disable Image Based Lens Flares when Enabled` | `bool` | `True` | `𝙸𝟸  ·  Lens Flare` | — | — | InstanceEditable |
| `Starting Sky Atmosphere Height` | `real<double>` | `0.000000` | `System - Sky Atmosphere` | — | — | InstanceEditable, Private |
| `Post Process Components` | `TArray<struct<UDS_Post_Process_Stage>>` | — | `𝙸𝟹  ·  Post Processing` | — | — | InstanceEditable |
| `User Post Process Components` | `TArray<object<PostProcessComponent>>` | — | `𝙸𝟹  ·  Post Processing` | — | — | InstanceEditable, Private |
| `Using Post Process Components` | `bool` | `False` | `System - Post Process` | — | — | InstanceEditable, Private |
| `Cloud Wisps Tint (Day)` | `struct<LinearColor>` | `(R=0.416713,G=0.436257,B=0.478431,A=1.000000)` | `𝙲𝟻  ·  Cloud Wisps` | — | — | InstanceEditable |
| `Cloud Wisps Tint (Dawn/Dusk)` | `struct<LinearColor>` | `(R=1.000000,G=0.587119,B=0.395833,A=1.000000)` | `𝙲𝟻  ·  Cloud Wisps` | — | — | InstanceEditable |
| `Cloud Wisps Tint (Night)` | `struct<LinearColor>` | `(R=0.367187,G=0.428386,B=0.489583,A=1.000000)` | `𝙲𝟻  ·  Cloud Wisps` | — | — | InstanceEditable |
| `Increase Wisps Brightness Around Sun` | `real<double>` | `5.000000` | `𝙲𝟻  ·  Cloud Wisps` | — | — | InstanceEditable, ExposeToCinematics |
| `Increase Wisps Brightness Around Moon` | `real<double>` | `3.000000` | `𝙲𝟻  ·  Cloud Wisps` | — | — | InstanceEditable, ExposeToCinematics |
| `Sun Source Angle Scale` | `real<double>` | `1.000000` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, ExposeToCinematics |
| `Solar Eclipse` | `bool` | `True` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable |
| `Solar Eclipse Tint Color` | `struct<LinearColor>` | `(R=0.994792,G=0.754438,B=0.784207,A=1.000000)` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable |
| `Solar Eclipse Intensity Multiplier` | `real<double>` | `0.000000` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, ExposeToCinematics |
| `Sun Specular Scale` | `real<double>` | `1.000000` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, ExposeToCinematics |
| `Render Sun Directional Light` | `bool` | `True` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable |
| `Custom Sun Light Actor` | `object<DirectionalLight>` | `None` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable |
| `Max Sun Source Angle Scale` | `real<double>` | `5.000000` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, ExposeToCinematics |
| `Sun Source Angle Softness` | `real<double>` | `0.500000` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, ExposeToCinematics |
| `Scale Sun Radius as it Nears Horizon` | `real<double>` | `1.000000` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, ExposeToCinematics |
| `Fade Down High Sun Light Intensity Below Horizon` | `bool` | `True` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable |
| `Support Sky Atmo Affecting Height Fog` | `bool` | `False` | `System - Project Settings` | — | — | InstanceEditable, Private |
| `UDS Version` | `string` | — | `Hidden Exposed` | — | — | InstanceEditable |
| `UDS Version Info` | `object<UDS_VersionInfo_C>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_VersionInfo.UDS_VersionInfo_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_CurrentVersion.UDS_CurrentVersion'` | `Project` | — | — | InstanceEditable, Private |
| `Clouds B Time` | `real<double>` | `0.000000` | `Hidden Cloud Movement` | Replicated (COND_InitialOnly) | — | InstanceEditable |
| `Mie Scattering Scale Multiplier` | `real<double>` | `1.000000` | `𝙶𝟷  ·  Sky Atmosphere` | — | — | InstanceEditable, ExposeToCinematics |
| `Sky Atmosphere Overcast Luminance` | `real<double>` | `1.000000` | `𝙶𝟷  ·  Sky Atmosphere` | — | — | InstanceEditable, ExposeToCinematics |
| `Keep Planet Top at Camera XY Location` | `bool` | `True` | `𝙶𝟷  ·  Sky Atmosphere` | — | — | InstanceEditable |
| `Control Sky Atmosphere Settings` | `bool` | `True` | `𝙶𝟷  ·  Sky Atmosphere` | — | — | InstanceEditable |
| `Old Composite Weather` | `struct<Vector>` | `(X=-1.000000,Y=-1.000000,Z=-1.000000)` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Old Composite Context` | `struct<Vector>` | `(X=-1.000000,Y=-1.000000,Z=-1.000000)` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Composite Weather Change Speed` | `real<double>` | `0.000000` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Composite Context Change Speed` | `real<double>` | `0.000000` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Old Moon Target` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Old Sun Target` | `struct<Vector>` | `(X=1.000000,Y=0.000000,Z=0.000000)` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Cached Colors Last Accessed` | `TArray<struct<LinearColor>>` | — | `System - Cache` | — | — | InstanceEditable, Private |
| `Last Low Frequency Update Location` | `struct<Vector>` | `(X=50000000000.000000,Y=50000000000.000000,Z=50000000000.000000)` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Add Planet/Moon Preset` | `object<UDS_Planet_Preset_C>` | `None` | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable |
| `Planets/Moons` | `TArray<struct<UDS_Space_Planet>>` | — | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable |
| `Space Layer Brightness (Night)` | `real<double>` | `1.000000` | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable, ExposeToCinematics |
| `Space Layer Brightness (Day)` | `real<double>` | `5.000000` | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable, ExposeToCinematics |
| `Space Glow Brightness` | `real<double>` | `0.080000` | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable |
| `Space Planet MIDs` | `TArray<object<MaterialInstanceDynamic>>` | — | `Dynamic Material Instances` | — | — | InstanceEditable, Private |
| `Render Nebula` | `bool` | `False` | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable |
| `Nebula Intensity` | `real<double>` | `0.700000` | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable |
| `Nebula Color 1` | `struct<LinearColor>` | `(R=0.019449,G=1.000000,B=0.950241,A=1.000000)` | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable |
| `Nebula Color 2` | `struct<LinearColor>` | `(R=1.000000,G=0.082829,B=0.000000,A=1.000000)` | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable |
| `Nebula Color 3` | `struct<LinearColor>` | `(R=0.000000,G=0.355670,B=1.000000,A=1.000000)` | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable |
| `Nebula Core Highlight` | `real<double>` | `0.500000` | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable |
| `Nebula Noise Scale` | `real<double>` | `5.000000` | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable |
| `Nebula Exponent` | `real<double>` | `4.500000` | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable |
| `Nebula Large Distortion` | `real<double>` | `0.110000` | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable |
| `Nebula Small Distortion` | `real<double>` | `0.030000` | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable |
| `Nebula Noise Offset` | `real<double>` | `0.500000` | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable |
| `Nebula Sort Index` | `int` | `0` | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable |
| `Moon Renders Behind Space Layer` | `bool` | `False` | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable |
| `Force Enable Space Layer` | `bool` | `False` | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable |
| `Space Scene Components` | `TArray<object<SceneComponent>>` | — | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable, Private |
| `Space Ring MIDs` | `TArray<object<MaterialInstanceDynamic>>` | — | `Dynamic Material Instances` | — | — | InstanceEditable, Private |
| `Space Glow MIDs` | `TArray<object<MaterialInstanceDynamic>>` | — | `Dynamic Material Instances` | — | — | InstanceEditable, Private |
| `Space Planet Components` | `TArray<object<StaticMeshComponent>>` | — | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable, Private |
| `Space Layer Active` | `bool` | `False` | `System - State` | — | — | InstanceEditable, Private |
| `Cached Moon Z Vector` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Cached Solar Eclipse Tint` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Cached Sun Scale` | `real<double>` | `0.000000` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Cached Moon Scale` | `real<double>` | `0.000000` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Sun - Lighting Channel 0` | `bool` | `True` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable |
| `Sun - Lighting Channel 1` | `bool` | `False` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable |
| `Sun - Lighting Channel 2` | `bool` | `False` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable |
| `Moon - Lighting Channel 0` | `bool` | `True` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable |
| `Moon - Lighting Channel 1` | `bool` | `False` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable |
| `Moon - Lighting Channel 2` | `bool` | `False` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable |
| `Space Roots` | `TArray<object<SceneComponent>>` | — | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable, Private |
| `Water Level` | `real<double>` | `0.000000` | `𝙹𝟷  ·  Water` | — | — | InstanceEditable, ExposeToCinematics |
| `Render Water Caustics` | `bool` | `False` | `𝙹𝟷  ·  Water` | — | — | InstanceEditable |
| `Caustics Intensity` | `real<double>` | `0.800000` | `𝙹𝟷  ·  Water` | — | — | InstanceEditable |
| `Caustics Falloff` | `real<double>` | `100.000000` | `𝙹𝟷  ·  Water` | — | — | InstanceEditable |
| `Deep Water Falloff` | `real<double>` | `20000.000000` | `𝙹𝟷  ·  Water` | — | — | InstanceEditable |
| `Caustics Texture Scale` | `real<double>` | `700.000000` | `𝙹𝟷  ·  Water` | — | — | InstanceEditable |
| `Moons Cloud Mask` | `real<double>` | `1.000000` | `System - Moon` | — | — | InstanceEditable, Private |
| `Caustics Falloff Offset` | `real<double>` | `0.000000` | `𝙹𝟷  ·  Water` | — | — | InstanceEditable |
| `Blur Caustics with Depth` | `real<double>` | `5.000000` | `𝙹𝟷  ·  Water` | — | — | InstanceEditable |
| `Blur Caustics in Cloud Shadow` | `real<double>` | `7.000000` | `𝙹𝟷  ·  Water` | — | — | InstanceEditable |
| `Blur Caustics with Camera Distance` | `real<double>` | `1.000000` | `𝙹𝟷  ·  Water` | — | — | InstanceEditable |
| `Event Minute` | `int` | `-1` | `System - Time` | — | — | InstanceEditable, Private |
| `Sunset Event State` | `int` | `-1` | `System - Time` | — | — | InstanceEditable, Private |
| `Disable Sky/Fog Cloudiness Above Cloud Layer` | `bool` | `True` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Custom Volumetric Cloud Material` | `softobject<MaterialInterface>` | `None` | `𝙲𝟷  ·  Volumetric Clouds` | — | — | InstanceEditable |
| `Camera Cloud Layer Normalized Height` | `real<double>` | `0.000000` | `System - Volumetric Clouds` | — | — | InstanceEditable, Private |
| `Camera Sky Atmosphere Normalized Density` | `real<double>` | `1.000000` | `System - Sky Atmosphere` | — | — | InstanceEditable, Private |
| `Moon Fog Base Color` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=0.000000)` | `System - Fog` | — | — | InstanceEditable, Private |
| `Sun Fog Base Color` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=0.000000)` | `System - Fog` | — | — | InstanceEditable, Private |
| `Last High Frequency Update Location` | `struct<Vector>` | `(X=50000000000.000000,Y=50000000000.000000,Z=50000000000.000000)` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Old Cloud Layer Camera Level` | `real<double>` | `0.000000` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Cloud Camera Relative Change Speed` | `real<double>` | `0.000000` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Cached Sky Atmosphere Absorption Color` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=0.000000)` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Cloud Coverage Target Resolution` | `int` | `256` | `𝙺𝟸  ·  Volumetric Cloud Painting` | — | — | InstanceEditable |
| `Cloud Coverage Target Size` | `int` | `20000000` | `𝙺𝟸  ·  Volumetric Cloud Painting` | — | — | InstanceEditable |
| `Painted Cloud Coverage Opacity` | `real<double>` | `1.000000` | `𝙺𝟸  ·  Volumetric Cloud Painting` | — | — | InstanceEditable, ExposeToCinematics |
| `Layer 2 Painted Cloud Coverage Opacity` | `real<double>` | `0.000000` | `𝙺𝟸  ·  Volumetric Cloud Painting` | — | — | InstanceEditable, ExposeToCinematics |
| `Painted Coverage Affects Global Values` | `real<double>` | `0.850000` | `𝙺𝟸  ·  Volumetric Cloud Painting` | — | — | InstanceEditable |
| `Cloud Painting Active` | `bool` | `False` | `Hidden Exposed` | — | — | InstanceEditable |
| `Cloud Coverage Target Location` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `𝙺𝟸  ·  Volumetric Cloud Painting` | — | — | InstanceEditable, Private |
| `Current Cloud Coverage Render Target Mapping` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=0.000000)` | `System - VC Painting` | — | — | InstanceEditable, Private |
| `Cloud Coverage Render Target` | `object<TextureRenderTarget2D>` | `/Script/Engine.TextureRenderTarget2D'/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/CloudPaintTarget.CloudPaintTarget'` | `𝙺𝟸  ·  Volumetric Cloud Painting` | — | — | InstanceEditable, Private |
| `Cloud Coverage Target in Use` | `bool` | `False` | `𝙺𝟸  ·  Volumetric Cloud Painting` | — | — | InstanceEditable, Private |
| `Async Loading Queue` | `TArray<softobject<Object>>` | — | `System - Loading` | — | — | InstanceEditable, Private |
| `Async Loaded Objects` | `TArray<object<Object>>` | — | `System - Loading` | — | — | InstanceEditable, Private |
| `Async Loading Active` | `bool` | `False` | `System - Loading` | — | — | InstanceEditable, Private |
| `Cloud Coverage After Painting` | `real<double>` | `0.000000` | `Common Derivatives` | — | — | InstanceEditable, Private |
| `Cloud Paint Can Add Coverage` | `bool` | `False` | `𝙺𝟸  ·  Volumetric Cloud Painting` | — | — | InstanceEditable, Private |
| `Cloud Paint Can Subtract Coverage` | `bool` | `False` | `𝙺𝟸  ·  Volumetric Cloud Painting` | — | — | InstanceEditable, Private |
| `Enable Volumetric Cloud Light Rays` | `bool` | `True` | `𝙺𝟷  ·  Volumetric Cloud Light Rays` | — | — | InstanceEditable |
| `Light Ray Intensity` | `real<double>` | `1.000000` | `𝙺𝟷  ·  Volumetric Cloud Light Rays` | — | — | InstanceEditable, ExposeToCinematics |
| `Light Ray Tint Color` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `𝙺𝟷  ·  Volumetric Cloud Light Rays` | — | — | InstanceEditable, ExposeToCinematics |
| `Light Rays Point Spacing` | `real<double>` | `50000.000000` | `𝙺𝟷  ·  Volumetric Cloud Light Rays` | — | — | InstanceEditable |
| `Light Ray Length` | `real<double>` | `1.000000` | `𝙺𝟷  ·  Volumetric Cloud Light Rays` | — | — | InstanceEditable |
| `Individual Clouds Light Rays` | `real<double>` | `0.000000` | `𝙺𝟷  ·  Volumetric Cloud Light Rays` | — | — | InstanceEditable |
| `Scale Light Ray Width` | `real<double>` | `1.000000` | `𝙺𝟷  ·  Volumetric Cloud Light Rays` | — | — | InstanceEditable, ExposeToCinematics |
| `Light Rays Max Distance (Km)` | `real<double>` | `12.000000` | `𝙺𝟷  ·  Volumetric Cloud Light Rays` | — | — | InstanceEditable |
| `Light Rays Depth Fade Distance` | `real<double>` | `100000.000000` | `𝙺𝟷  ·  Volumetric Cloud Light Rays` | — | — | InstanceEditable |
| `Light Rays 3D Noise Scale` | `real<double>` | `700000.000000` | `𝙺𝟷  ·  Volumetric Cloud Light Rays` | — | — | InstanceEditable |
| `Volumetric Cloud Light Rays Niagara System` | `softobject<NiagaraSystem>` | `/Game/_ThirdParty/UltraDynamicSky/Particles/VolumetricCloud_LightRays.VolumetricCloud_LightRays` | `System - VC Light Rays` | — | — | InstanceEditable, Private |
| `Max Light Ray Length` | `real<double>` | `0.000000` | `System - VC Light Rays` | — | — | InstanceEditable, Private |
| `Cloud Top World Height` | `real<double>` | `0.000000` | `System - Volumetric Clouds` | — | — | InstanceEditable, Private |
| `Cached Light Ray Vector` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `System - VC Light Rays` | — | — | InstanceEditable, Private |
| `Light Rays Using Sun` | `bool` | `False` | `System - VC Light Rays` | — | — | InstanceEditable, Private |
| `Cached Light Ray Strength` | `real<double>` | `0.000000` | `System - VC Light Rays` | — | — | InstanceEditable, Private |
| `Space Nebula MID` | `object<MaterialInstanceDynamic>` | `None` | `Dynamic Material Instances` | — | — | InstanceEditable, Private |
| `Cloud Paint Draw MID` | `object<MaterialInstanceDynamic>` | `None` | `Dynamic Material Instances` | — | — | InstanceEditable, Private |
| `Render Global Volumetric Material` | `bool` | `False` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Fog Noise Scale` | `real<double>` | `2000.000000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Fog Noise Intensity` | `real<double>` | `1.500000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Fog Noise Max Samples` | `real<double>` | `4.000000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Fog Noise Speed Scale` | `real<double>` | `1.000000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Fog Noise Offset` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable, ExposeToCinematics |
| `Mask Fog with Weather Masks` | `real<double>` | `1.000000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Fog Masked Extinction` | `real<double>` | `0.000000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Extra Fog Extinction (Rainy)` | `real<double>` | `0.200000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Extra Fog Extinction (Snowy)` | `real<double>` | `0.200000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Extra Fog Extinction (Dusty)` | `real<double>` | `0.200000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Render Ground Fog (Fog Above Distance Fields)` | `bool` | `False` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Ground Fog Extinction (Foggy)` | `real<double>` | `0.200000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable, ExposeToCinematics |
| `Ground Fog Extinction (Dusty)` | `real<double>` | `0.300000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable, ExposeToCinematics |
| `Ground Fog Extinction (Rainy)` | `real<double>` | `0.100000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable, ExposeToCinematics |
| `Ground Fog Extinction (Snowy)` | `real<double>` | `0.100000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable, ExposeToCinematics |
| `Ground Fog Extinction (Manual)` | `real<double>` | `0.000000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable, ExposeToCinematics |
| `Ground Fog Height` | `real<double>` | `70.000000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Ground Fog Height Noise` | `real<double>` | `2.000000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Ground Fog Angle Threshold` | `real<double>` | `0.200000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Ground Fog Hardness` | `real<double>` | `4.000000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Apply Water Fog Values` | `bool` | `False` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Water Extinction` | `real<double>` | `0.100000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Water Albedo` | `struct<LinearColor>` | `(R=0.225152,G=0.311797,B=0.432292,A=1.000000)` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Water Fog Falloff` | `real<double>` | `20.000000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Water Fog Falloff Offset` | `real<double>` | `0.000000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Water Caustic Fog Ray Intensity` | `real<double>` | `2.000000` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Volumetric Clouds Apply Fog Late` | `bool` | `True` | `𝙵𝟹  ·  Volumetric Fog` | — | — | InstanceEditable |
| `Global Volumetric Fog MID` | `object<MaterialInstanceDynamic>` | `None` | `Dynamic Material Instances` | — | — | InstanceEditable, Private |
| `Fog Position` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Hidden Cloud Movement` | — | — | InstanceEditable |
| `Sun Disk Color Curve` | `object<CurveLinearColor>` | `/Script/Engine.CurveLinearColor'/Game/_ThirdParty/UltraDynamicSky/Materials/Color_Curves/Sun_Disk_Color.Sun_Disk_Color'` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable |
| `Sun Target` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, ExposeToCinematics |
| `Moon Target` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `𝙴𝟸  ·  Moon` | — | — | InstanceEditable, ExposeToCinematics |
| `Static Clouds Texture` | `softobject<Texture2D>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/StaticClouds/StaticClouds_A.StaticClouds_A` | `𝙲𝟹  ·  Static Clouds` | — | — | InstanceEditable |
| `Static Clouds Rotation` | `real<double>` | `0.000000` | `𝙲𝟹  ·  Static Clouds` | — | — | InstanceEditable |
| `Static Clouds Rotation Speed` | `real<double>` | `0.000000` | `𝙲𝟹  ·  Static Clouds` | — | — | InstanceEditable |
| `Static Clouds Color Intensity` | `real<double>` | `1.000000` | `𝙲𝟹  ·  Static Clouds` | — | — | InstanceEditable, ExposeToCinematics |
| `Cloud Movement Update Period` | `real<double>` | `0.550000` | `𝙲𝟺  ·  Cloud Movement` | — | — | InstanceEditable |
| `Clouds B Time Old` | `real<double>` | `0.000000` | `Hidden Cloud Movement` | — | — | InstanceEditable |
| `Clouds Position Color A` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=1.000000)` | `Hidden Cloud Movement` | — | — | InstanceEditable |
| `Clouds Position Color B` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=1.000000)` | `Hidden Cloud Movement` | — | — | InstanceEditable |
| `Fog Position Color A` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=1.000000)` | `Hidden Cloud Movement` | — | — | InstanceEditable |
| `Fog Position Color B` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=1.000000)` | `Hidden Cloud Movement` | — | — | InstanceEditable |
| `Current Cache Timer Speed` | `real<double>` | `10.000000` | `System - Cache` | — | — | InstanceEditable, Private |
| `Low Priority Update Step` | `int` | `-1` | `System - Update` | — | — | InstanceEditable, Private |
| `Active Update Speed` | `int` | `4` | `System - Update` | — | — | InstanceEditable, Private |
| `High Priority Update Step` | `int` | `0` | `System - Update` | — | — | InstanceEditable, Private |
| `Non Cached Update Step` | `int` | `0` | `System - Update` | — | — | InstanceEditable, Private |
| `Min Property Cache Period` | `real<double>` | `0.100000` | `𝙼𝟸  ·  Scalability / Performance` | — | — | InstanceEditable |
| `Fast Cache Toggle` | `bool` | `False` | `𝙼𝟸  ·  Scalability / Performance` | — | — | InstanceEditable, ExposeToCinematics |
| `Minimum Active Update Speed` | `int` | `0` | `𝙼𝟸  ·  Scalability / Performance` | — | — | InstanceEditable |
| `Fast Cache Toggle Speed` | `real<double>` | `1.300000` | `𝙼𝟸  ·  Scalability / Performance` | — | — | InstanceEditable |
| `UDW Wind Value` | `real<double>` | `2.000000` | `Hidden Cloud Movement` | — | — | InstanceEditable |
| `Volumetric Aurora Fade Distance (km)` | `real<double>` | `30.000000` | `𝙷𝟺  ·  Aurora` | — | — | InstanceEditable |
| `Cinematic Clouds View Sample Scale` | `real<double>` | `25.000000` | `𝙼𝟷  ·  Cinematics / Offline Rendering` | — | — | InstanceEditable |
| `Cinematic Clouds Shadow Sample Scale` | `real<double>` | `0.600000` | `𝙼𝟷  ·  Cinematics / Offline Rendering` | — | — | InstanceEditable |
| `Cinematic Clouds Tracing Max Distance` | `real<double>` | `20.000000` | `𝙼𝟷  ·  Cinematics / Offline Rendering` | — | — | InstanceEditable |
| `Cinematic Clouds View Ray Sample Max Count` | `int` | `10000` | `𝙼𝟷  ·  Cinematics / Offline Rendering` | — | — | InstanceEditable |
| `Current Modifiers` | `TArray<object<UDS_Modifier_C>>` | — | `System - Modifiers` | — | — | InstanceEditable, Private |
| `Modifier Alphas` | `TArray<real<double>>` | — | `System - Modifiers` | — | — | InstanceEditable, Private |
| `Modifier Targets` | `TArray<real<double>>` | — | `System - Modifiers` | — | — | InstanceEditable, Private |
| `Modifier Speeds` | `TArray<real<double>>` | — | `System - Modifiers` | — | — | InstanceEditable, Private |
| `Starting Modifiers` | `TArray<object<UDS_Modifier_C>>` | — | `𝙻𝟷  ·  Sky Modifiers` | — | — | InstanceEditable |
| `Time of Day Specific Modifiers` | `TMap<object<UDS_TimeOfDay_FadeRange>>, struct:/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_TimeOfDay_FadeRange.UDS_TimeOfDay_FadeRange>` | `()` | `𝙻𝟷  ·  Sky Modifiers` | — | — | InstanceEditable |
| `Preview Modifiers in Editor` | `bool` | `True` | `𝙻𝟷  ·  Sky Modifiers` | — | — | InstanceEditable |
| `Replicate Modifiers to Clients` | `bool` | `False` | `𝙻𝟷  ·  Sky Modifiers` | — | — | InstanceEditable |
| `Using Volumetric Light Rays` | `bool` | `False` | `𝙺𝟷  ·  Volumetric Cloud Light Rays` | — | — | InstanceEditable, Private |
| `Last Material Quality Level` | `int` | `0` | `System - Scalability` | — | — | InstanceEditable, Private |
| `Last Effects Quality Level` | `int` | `0` | `System - Scalability` | — | — | InstanceEditable, Private |
| `Instant Exposure Adjustment on Begin Play` | `bool` | `False` | `𝙴𝟼  ·  Exposure` | — | — | InstanceEditable |
| `Exposure Compensation Curve for Physical Light Intensity` | `object<CurveFloat>` | `/Script/Engine.CurveFloat'/Game/_ThirdParty/UltraDynamicSky/Materials/Float_Curves/Exposure_Compensation_Curve_Physical.Exposure_Compensation_Curve_Physical'` | `𝙴𝟼  ·  Exposure` | — | — | InstanceEditable |
| `Instant Exposure Post Process` | `object<PostProcessComponent>` | `None` | `𝙴𝟼  ·  Exposure` | — | — | InstanceEditable, Private |
| `Tick Delta Seconds` | `real<double>` | `1.000000` | `System - Time` | — | — | InstanceEditable, Private |
| `Editor Camera Position` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Hidden Exposed` | — | — | InstanceEditable |
| `Editor Camera Position Offset` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Hidden Exposed` | — | — | InstanceEditable, Private |
| `Current Camera Location` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=-10000000.000000)` | `Hidden Exposed` | — | — | InstanceEditable |
| `Current Camera Rotation` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=-10000000.000000)` | `Hidden Exposed` | — | — | InstanceEditable |
| `Run Context` | `byte<UDS_RunContext>` | `NewEnumerator0` | `System - State` | — | — | InstanceEditable, Private |
| `Slow Falling Combined Change Speed` | `real<double>` | `10.000000` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Custom Sky Sphere Static Mesh` | `object<StaticMesh>` | `None` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Fallback Cloud Layer Altitude` | `real<double>` | `70000.000000` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Level Editor Tick` | `bool` | `True` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Time of Last Cloud Cache` | `real<double>` | `0.000000` | `Hidden Cloud Movement` | — | — | InstanceEditable |
| `Last Static Clouds Update Time` | `real<double>` | `0.000000` | `Hidden Cloud Movement` | — | — | InstanceEditable |
| `Static Clouds Dynamic Rotation` | `real<double>` | `0.000000` | `Hidden Cloud Movement` | — | — | InstanceEditable |
| `Editor Camera Rotation` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `System - State` | — | — | InstanceEditable, Private |
| `Cached Cloud Shadows Cancel Value` | `real<double>` | `1.000000` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Interior Occlusion Change Speed` | `real<double>` | `0.000000` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Time of Last Cache Timing Update` | `real<double>` | `-1.000000` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Old Interior Occlusion` | `real<double>` | `-1.000000` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Transitioning Sky Light Intensity` | `bool` | `False` | `System - Sky Light` | — | — | InstanceEditable, Private |
| `Cached Sun Cast Shadows` | `bool` | `False` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Eclipse Percent` | `real<double>` | `1.000000` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, Private |
| `Sun Shadows Cutoff Z` | `real<double>` | `0.002000` | `𝙴𝟷  ·  Sun` | — | — | InstanceEditable, Private |
| `Current Hour Changed` | `mcdelegate` | `()` | `Time Dispatchers` | — | — | InstanceEditable, Private |
| `Every Minute` | `mcdelegate` | `()` | `Time Dispatchers` | — | — | InstanceEditable, Private |
| `Called Starting Event Dispatchers` | `bool` | `False` | `System - Time` | — | — | InstanceEditable, Private |
| `World Origin Location` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `System - State` | — | — | InstanceEditable, Private |
| `Event Date` | `struct<UDS_DateAndTime>` | `()` | `System - Time` | — | — | InstanceEditable, Private |
| `Date Changed` | `mcdelegate` | `()` | `Time Dispatchers` | — | — | InstanceEditable, Private |
| `Initial Replication` | `bool` | `False` | `System - Replication` | Replicated (COND_InitialOnly) | — | InstanceEditable, Private |
| `Starting Date` | `struct<UDS_DateAndTime>` | `()` | `System - Time` | — | — | InstanceEditable, Private |
| `Unmodified Floats` | `TArray<real<double>>` | — | `System - Modifiers` | — | — | InstanceEditable, Private |
| `Unmodified Colors` | `TArray<struct<LinearColor>>` | — | `System - Modifiers` | — | — | InstanceEditable, Private |
| `Modifiers Ticking` | `bool` | `False` | `System - Modifiers` | — | — | InstanceEditable, Private |
| `Modified Float Properties` | `TArray<byte<UDS_Modifier_Float_Property>>` | — | `System - Modifiers` | — | — | InstanceEditable, Private |
| `Modified Color Properties` | `TArray<byte<UDS_Modifier_Color_Property>>` | — | `System - Modifiers` | — | — | InstanceEditable, Private |
| `Move Sky Light Location` | `bool` | `False` | `System - Sky Light` | — | — | InstanceEditable, Private |
| `Weather Cloud Coverage` | `real<double>` | `-1.000000` | `Hidden Exposed` | — | — | InstanceEditable |
| `Weather Fog` | `real<double>` | `-1.000000` | `Hidden Exposed` | — | — | InstanceEditable |
| `Weather Dust Amount` | `real<double>` | `-1.000000` | `Hidden Exposed` | — | — | InstanceEditable |
| `Sky Glow Fog Color` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=0.000000)` | `System - Fog` | — | — | InstanceEditable, Private |
| `Cached Night Sky Glow` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=1.000000)` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Cached Light Pollution` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=1.000000)` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Local Cloud Coverage` | `real<double>` | `0.000000` | `Common Derivatives` | — | — | InstanceEditable, Private |
| `Storm Clouds Draw MID` | `object<MaterialInstanceDynamic>` | `None` | `Dynamic Material Instances` | — | — | InstanceEditable, Private |
| `Cvar Cache` | `TMap<string, ?>` | `()` | `Project` | — | — | InstanceEditable, Private |
| `Sun World Rotation` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `𝙴𝟺  ·  Directional Light` | — | — | InstanceEditable, Private |
| `Moon World Rotation` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `𝙴𝟺  ·  Directional Light` | — | — | InstanceEditable, Private |
| `Path Tracer Sky Light` | `object<SkyLightComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Global Volumetric Fog Mesh` | `object<StaticMeshComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Volumetric Cloud Light Rays` | `object<NiagaraComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Inside Cloud Fog Mesh` | `object<StaticMeshComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Volumetric Cloud Shadow Altitude` | `real<double>` | `0.000000` | `System - Volumetric Clouds` | — | — | InstanceEditable, Private |
| `Path Tracer Fog Parent Mat` | `softobject<MaterialInterface>` | `/Game/_ThirdParty/UltraDynamicSky/Materials/PathTracer_ExpHeightFog.PathTracer_ExpHeightFog` | `Path Tracer` | — | — | InstanceEditable, Private |
| `Path Tracer Fog MID` | `object<MaterialInstanceDynamic>` | `None` | `Path Tracer` | — | — | InstanceEditable, Private |
| `Render Height Fog in Path Tracer using Post Process` | `bool` | `True` | `𝙵𝟷  ·  Fog Color` | — | — | InstanceEditable |
| `Cloud Profile LUT Preview` | `object<Texture>` | `None` | `Hidden Exposed` | — | — | InstanceEditable |
| `Previewing Cloud Profile Editor` | `bool` | `False` | `Hidden Exposed` | — | — | InstanceEditable |
| `Mie Anisotropy Multiplier` | `real<double>` | `1.000000` | `𝙶𝟷  ·  Sky Atmosphere` | — | — | InstanceEditable, ExposeToCinematics |
| `Sky Atmosphere Density Curve` | `object<CurveFloat>` | `/Script/Engine.CurveFloat'/Game/_ThirdParty/UltraDynamicSky/Materials/Float_Curves/Skyatmosphere_Density.Skyatmosphere_Density'` | `𝙶𝟷  ·  Sky Atmosphere` | — | — | InstanceEditable, Private |
| `Allow Disabling Directional Shadows with Coverage` | `bool` | `False` | `System - Cloud Shadows` | — | — | InstanceEditable, Private |
| `Apply Flat Cloudiness` | `bool` | `False` | `System - Sky Material` | — | — | InstanceEditable, Private |
| `Using Sky Atmosphere` | `bool` | `False` | `Mode Derivatives` | — | — | InstanceEditable, Private |
| `Cached Moon Effective Illumination 0-1` | `real<double>` | `0.000000` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Cached Absent Directional Lights Brightness` | `real<double>` | `0.000000` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Cached Current Moon Lit Percent` | `real<double>` | `0.000000` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Using Space Mode` | `bool` | `False` | `Mode Derivatives` | — | — | InstanceEditable, Private |
| `Using Volumetric Clouds` | `bool` | `False` | `Mode Derivatives` | — | — | InstanceEditable, Private |
| `Using Static Clouds` | `bool` | `False` | `Mode Derivatives` | — | — | InstanceEditable, Private |
| `Using 2D Dynamic Clouds` | `bool` | `False` | `Mode Derivatives` | — | — | InstanceEditable, Private |
| `Using Volumetric Aurora` | `bool` | `False` | `Mode Derivatives` | — | — | InstanceEditable, Private |
| `Cached Lit Intensity` | `real<double>` | `0.000000` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Cached Directional Light Dimming` | `real<double>` | `0.000000` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Modifiers Animating` | `bool` | `False` | `𝙻𝟷  ·  Sky Modifiers` | — | — | InstanceEditable, Private |
| `Cached Directional Inscattering Multiplier` | `real<double>` | `0.000000` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Space Nebula Parent Material` | `softobject<MaterialInterface>` | `/Game/_ThirdParty/UltraDynamicSky/Materials/Space/Nebula_Layer.Nebula_Layer` | `𝙷𝟸  ·  Space Layer` | — | — | InstanceEditable, Private |
| `Cached Fog Directional Inscattering` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=0.000000)` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Sun Moon Delta` | `real<double>` | `0.000000` | `Change Monitoring` | — | — | InstanceEditable, Private |
| `Use Legacy Cloud Coverage Range` | `bool` | `False` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Space Nebula Sphere` | `object<StaticMeshComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Preview Weather Modifiers` | `TMap<object<UDS_Modifier_C,>>, real>` | `()` | `Hidden Exposed` | — | — | InstanceEditable |
| `Movement Update Threshold` | `real<double>` | `100.000000` | `System - Update` | — | — | InstanceEditable, Private |
| `Show UDS Level Editor Toolbar` | `bool` | `True` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Custom Time` | `mcdelegate` | `()` | `Time Dispatchers` | — | — | InstanceEditable, Private |
| `Dedicated Server Tick Interval` | `real<double>` | `0.250000` | `𝙱𝟷  ·  Animate Time Of Day` | — | — | InstanceEditable |
| `Custom Time Dispatcher Flags` | `TArray<int>` | — | `𝙱𝟷  ·  Animate Time Of Day` | — | — | InstanceEditable, Private |
| `Compensate Directional Inscattering` | `bool` | `False` | `System - Fog` | — | — | InstanceEditable, Private |
| `Show Editor Warnings for Incompatible Project Settings` | `bool` | `True` | `𝙰𝟷  ·  Basic Controls` | — | — | InstanceEditable |
| `Instant Time of Day Change` | `mcdelegate` | `()` | `System Dispatchers` | — | — | InstanceEditable, Private |
| `Light Functions Supported` | `bool` | `False` | `System - Project Settings` | — | — | InstanceEditable, Private |
| `DBuffer Supported` | `bool` | `False` | `System - Project Settings` | — | — | InstanceEditable, Private |
| `Static Overcast Texture` | `softobject<Texture2D>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/Static_Overcast.Static_Overcast` | `𝙲𝟹  ·  Static Clouds` | — | — | InstanceEditable |
| `Static Overcast Strength` | `real<double>` | `1.000000` | `𝙲𝟹  ·  Static Clouds` | — | — | InstanceEditable |
| `Caching Incoming Modifiers` | `bool` | `False` | `𝙻𝟷  ·  Sky Modifiers` | — | — | InstanceEditable, Private |
| `Incoming Modifier Cache` | `TMap<object<UDS_Modifier_C,>>, real>` | `()` | `𝙻𝟷  ·  Sky Modifiers` | — | — | InstanceEditable, Private |
| `Simplified Color Sun Atmosphere LUT` | `softobject<VolumeTexture>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/Sun_Atmosphere_LUT_Volume.Sun_Atmosphere_LUT_Volume` | `𝙶𝟸  ·  Simplified Color` | — | — | InstanceEditable |
| `Simplified Color Moon Atmosphere LUT` | `softobject<VolumeTexture>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/Moon_Atmosphere_LUT_Volume.Moon_Atmosphere_LUT_Volume` | `𝙶𝟸  ·  Simplified Color` | — | — | InstanceEditable |
| `Static Clouds Fade in Clear Skies` | `bool` | `True` | `𝙲𝟹  ·  Static Clouds` | — | — | InstanceEditable |
| `Force Cloud Coverage Target Active` | `bool` | `False` | `𝙺𝟸  ·  Volumetric Cloud Painting` | — | — | InstanceEditable, Private |
| `Connect with UDW` | `bool` | `True` | `Hidden Exposed` | — | — | InstanceEditable |
| `Current Scene Lighting Brightness Scale` | `real<double>` | `0.000000` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Time Transition Complete` | `mcdelegate` | `()` | `System Dispatchers` | — | — | InstanceEditable, Private |
| `Sky Modifier Post Process Components` | `TMap<object<PostProcessComponent>>, object:/Script/Engine.PostProcessComponent>` | `()` | `𝙻𝟷  ·  Sky Modifiers` | — | — | InstanceEditable, Private |
| `Light Function Atlas Scale` | `real<double>` | `8.000000` | `𝙴𝟻  ·  Cloud Shadows` | — | — | InstanceEditable |
| `Apply Light Function Atlas Resolution` | `bool` | `True` | `𝙴𝟻  ·  Cloud Shadows` | — | — | InstanceEditable |
| `Light Function Atlas Resolution` | `int` | `512` | `𝙴𝟻  ·  Cloud Shadows` | — | — | InstanceEditable |
| `Disable Cvar Control` | `TArray<string>` | — | `𝙼𝟸  ·  Scalability / Performance` | — | — | InstanceEditable |
| `Cached VolCloud Top Emissive` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=0.000000)` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Cached VolCloud Bottom Emissive` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=0.000000)` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `DST End Hour` | `int` | `1` | `𝙳𝟷  ·  Simulation` | — | — | InstanceEditable |
| `Preset Location DST Settings` | `TMap<byte<UDS_DST_Preset>>, :/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_DST_Preset.UDS_DST_Preset>` | `((NewEnumerator1, ()),(NewEnumerator2, ()),(NewEnumerator3, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=10,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=1,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=4,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=3)),(NewEnumerator4, ()),(NewEnumerator5, ()),(NewEnumerator6, ()),(NewEnumerator7, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator8, ()),(NewEnumerator9, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator10, ()),(NewEnumerator11, ()),(NewEnumerator12, ()),(NewEnumerator13, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=3,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=3)),(NewEnumerator14, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator15, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=9,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=4,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=3)),(NewEnumerator16, ()),(NewEnumerator17, ()),(NewEnumerator18, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator19, ()),(NewEnumerator20, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6)),(NewEnumerator21, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=3,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=3)),(NewEnumerator22, ()),(NewEnumerator23, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=3,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=3)),(NewEnumerator24, ()),(NewEnumerator25, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator26, ()),(NewEnumerator27, ()),(NewEnumerator28, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator29, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=3,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=3)),(NewEnumerator30, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator31, ()),(NewEnumerator32, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=4,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=4,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=3,DSTEndHour_22_356947C540229AABB2901B93C9E77190=24)),(NewEnumerator33, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator34, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=10,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=1,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=4,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=3)),(NewEnumerator35, ()),(NewEnumerator36, ()),(NewEnumerator37, ()),(NewEnumerator38, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator39, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator40, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator41, ()),(NewEnumerator42, ()),(NewEnumerator43, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator44, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator45, ()),(NewEnumerator46, ()),(NewEnumerator47, ()),(NewEnumerator48, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=1,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=1)),(NewEnumerator49, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator50, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator51, ()),(NewEnumerator52, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator53, ()),(NewEnumerator54, ()),(NewEnumerator55, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=1)),(NewEnumerator56, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=3,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=3)),(NewEnumerator57, ()),(NewEnumerator58, ()),(NewEnumerator59, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator60, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator61, ()),(NewEnumerator62, ()),(NewEnumerator63, ()),(NewEnumerator64, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator65, ()),(NewEnumerator66, ()),(NewEnumerator67, ()),(NewEnumerator68, ()),(NewEnumerator69, ()),(NewEnumerator70, ()),(NewEnumerator71, ()),(NewEnumerator72, ()),(NewEnumerator73, ()),(NewEnumerator74, ()),(NewEnumerator75, ()),(NewEnumerator76, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=3,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=3)),(NewEnumerator77, ()),(NewEnumerator78, ()),(NewEnumerator79, ()),(NewEnumerator80, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator81, ()),(NewEnumerator82, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=1,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=1)),(NewEnumerator83, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=1,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=1)),(NewEnumerator84, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator85, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator86, ()),(NewEnumerator87, ()),(NewEnumerator104, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=9,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=4,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=3)),(NewEnumerator88, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=10,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=1,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=4,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=3)),(NewEnumerator89, ()),(NewEnumerator90, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator91, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator92, ()),(NewEnumerator93, ()),(NewEnumerator94, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator95, ()),(NewEnumerator96, ()),(NewEnumerator97, ()),(NewEnumerator98, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator99, ()),(NewEnumerator100, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator101, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator102, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator103, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator105, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator106, ()),(NewEnumerator107, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator108, ()),(NewEnumerator109, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator110, ()),(NewEnumerator111, ()),(NewEnumerator112, ()),(NewEnumerator113, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator114, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator115, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator116, ()),(NewEnumerator117, ()),(NewEnumerator118, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=9,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=5,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=1,DSTStartHour_14_790920F8469C47CDAF342B844018210E=24,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=4,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=5,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=24)),(NewEnumerator119, ()),(NewEnumerator120, ()),(NewEnumerator121, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator122, ()),(NewEnumerator123, ()),(NewEnumerator124, ()),(NewEnumerator125, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=3,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=3)),(NewEnumerator126, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator127, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator128, ()),(NewEnumerator129, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=10,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=1,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=4,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=3)),(NewEnumerator130, ()),(NewEnumerator131, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=3,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=3)),(NewEnumerator132, ()),(NewEnumerator133, ()),(NewEnumerator134, ()),(NewEnumerator135, ()),(NewEnumerator136, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator137, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator138, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator139, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator140, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator141, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartDayCount_12_5ACA19024B4C50AF91927A86C9DC9C5F=2,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=11,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndDayCount_20_9ECD2F464E5746FA3686A99989498D27=1,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator142, ()),(NewEnumerator143, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)),(NewEnumerator144, (ApplyDST_5_8F6945EF4138B744A49B39B6FD16404B=True,DSTStartMonth_8_21BF09114B395EA3FD807F99F363A6C0=3,DSTStartDayoftheWeek_10_B383F1E041B47DCC9A8285AC1D129C0F=6,DSTStartHour_14_790920F8469C47CDAF342B844018210E=2,DSTEndMonth_16_C3CEE1D74AD66CF5DE9FFBBCBA33E107=10,DSTEndDayoftheWeek_18_B120DBCA4DBA0A86BEDEFBA758B93036=6,DSTEndHour_22_356947C540229AABB2901B93C9E77190=2)))` | `System - Simulation` | — | — | InstanceEditable, Private |
| `Directional Specular Cancel Value` | `real<double>` | `1.000000` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Runtime Tick` | `mcdelegate` | `()` | `System Dispatchers` | — | — | InstanceEditable, Private |
| `Cached PP Blend Weights Old` | `TArray<real<double>>` | — | `System - Cache` | — | — | InstanceEditable, Private |
| `Cached PP Blend Weights New` | `TArray<real<double>>` | — | `System - Cache` | — | — | InstanceEditable, Private |
| `High Priority Updates 1` | `mcdelegate` | `()` | `Apply Properties` | — | — | InstanceEditable, Private |
| `High Priority Updates 2` | `mcdelegate` | `()` | `Apply Properties` | — | — | InstanceEditable, Private |
| `High Priority Updates 3` | `mcdelegate` | `()` | `Apply Properties` | — | — | InstanceEditable, Private |
| `High Priority Updates 4` | `mcdelegate` | `()` | `Apply Properties` | — | — | InstanceEditable, Private |
| `Low Priority Updates 1` | `mcdelegate` | `()` | `Apply Properties` | — | — | InstanceEditable, Private |
| `Low Priority Updates 2` | `mcdelegate` | `()` | `Apply Properties` | — | — | InstanceEditable, Private |
| `Low Priority Updates 3` | `mcdelegate` | `()` | `Apply Properties` | — | — | InstanceEditable, Private |
| `Low Priority Updates 4` | `mcdelegate` | `()` | `Apply Properties` | — | — | InstanceEditable, Private |
| `Low Priority Updates 5` | `mcdelegate` | `()` | `Apply Properties` | — | — | InstanceEditable, Private |
| `Low Priority Updates 6` | `mcdelegate` | `()` | `Apply Properties` | — | — | InstanceEditable, Private |
| `Low Priority Updates 7` | `mcdelegate` | `()` | `Apply Properties` | — | — | InstanceEditable, Private |
| `Low Priority Updates 8` | `mcdelegate` | `()` | `Apply Properties` | — | — | InstanceEditable, Private |
| `Max Priority Updates` | `mcdelegate` | `()` | `Apply Properties` | — | — | InstanceEditable, Private |
| `Immediate and Unrepeated Updates` | `mcdelegate` | `()` | `Apply Properties` | — | — | InstanceEditable, Private |
| `Cached PP Blend Weights Last Accessed` | `TArray<real<double>>` | — | `System - Cache` | — | — | InstanceEditable, Private |
| `Cache Group Timers` | `TArray<real<double>>` | `(0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000)` | `System - Cache` | — | — | InstanceEditable, Private |
| `Cache Group Timer Indexes` | `TArray<int>` | — | `System - Cache` | — | — | InstanceEditable, Private |
| `Cache Properties Step` | `int` | `0` | `System - Cache` | — | — | InstanceEditable, Private |
| `Active Cache Group` | `int` | `0` | `System - Cache` | — | — | InstanceEditable, Private |
| `Cache Group Timers Clear` | `TArray<real<double>>` | `(0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000)` | `System - Cache` | — | — | InstanceEditable, Private |
| `Cache Steps Multiplier` | `int` | `1` | `System - Cache` | — | — | InstanceEditable, Private |
| `Hard Cache Reset Change Speed Threshold` | `real<double>` | `0.350000` | `System - Cache` | — | — | InstanceEditable, Private |
| `Change Speed Rolling Buffer` | `TArray<real<float>>` | — | `System - Cache` | — | — | InstanceEditable, Private |
| `Last Delayed Change Speed` | `real<double>` | `-1.000000` | `System - Cache` | — | — | InstanceEditable, Private |
| `Low Priority Set Toggle` | `bool` | `False` | `System - Update` | — | — | InstanceEditable, Private |
| `High Priority Toggle One` | `bool` | `True` | `System - Update` | — | — | InstanceEditable, Private |
| `High Priority Toggle Two` | `bool` | `True` | `System - Update` | — | — | InstanceEditable, Private |
| `Use Angle Threshold Light Update` | `bool` | `False` | `Mode Derivatives` | — | — | InstanceEditable, Private |
| `Use Forced Light Update` | `bool` | `True` | `Mode Derivatives` | — | — | InstanceEditable, Private |
| `Use Periodic Light Update` | `bool` | `False` | `Mode Derivatives` | — | — | InstanceEditable, Private |
| `Last Sun Light Periodic Update Time` | `real<double>` | `0.000000` | `System - Update` | — | — | InstanceEditable, Private |
| `Last Moon Light Periodic Update Time` | `real<double>` | `0.000000` | `System - Update` | — | — | InstanceEditable, Private |
| `Using Either Aurora` | `bool` | `False` | `Mode Derivatives` | — | — | InstanceEditable, Private |
| `Cached Night Filtered Night Brightness` | `real<double>` | `0.000000` | `System - Cached Common Values` | — | — | InstanceEditable, Private |
| `Occlusion Mode` | `byte<UDS_Occlusion_Mode>` | `NewEnumerator2` | `𝙽𝟸  ·  Player Occlusion` | — | — | InstanceEditable |
| `Occlusion Sampling Location` | `byte<UDS_OcclusionSamplingLocation>` | `NewEnumerator0` | `𝙽𝟸  ·  Player Occlusion` | — | — | InstanceEditable |
| `Occlusion Uses GPU Distance Field Collision` | `bool` | `False` | `𝙽𝟸  ·  Player Occlusion` | — | — | InstanceEditable |
| `Occlusion Max Trace Distance` | `real<double>` | `4500.000000` | `𝙽𝟸  ·  Player Occlusion` | — | — | InstanceEditable |
| `Occlusion Horizontal Trace Steps` | `int` | `12` | `𝙽𝟸  ·  Player Occlusion` | — | — | InstanceEditable |
| `Occlusion Vertical Trace Steps` | `int` | `4` | `𝙽𝟸  ·  Player Occlusion` | — | — | InstanceEditable |
| `Occlusion Trace Channel` | `byte<ETraceTypeQuery>` | `TraceTypeQuery1` | `𝙽𝟸  ·  Player Occlusion` | — | — | InstanceEditable |
| `Occlusion Update Period` | `real<double>` | `0.550000` | `𝙽𝟸  ·  Player Occlusion` | — | — | InstanceEditable |
| `Global Occlusion Min Fraction` | `real<double>` | `0.200000` | `𝙽𝟸  ·  Player Occlusion` | — | — | InstanceEditable |
| `Global Occlusion Max Fraction` | `real<double>` | `0.900000` | `𝙽𝟸  ·  Player Occlusion` | — | — | InstanceEditable |
| `Query Occlusion Portals` | `bool` | `True` | `𝙽𝟸  ·  Player Occlusion` | — | — | InstanceEditable |
| `Occlusion GPU Distance Field Sample Count` | `int` | `100` | `𝙽𝟸  ·  Player Occlusion` | — | — | InstanceEditable |
| `Show Player Occlusion Trace Debugs` | `bool` | `False` | `𝙽𝟸  ·  Player Occlusion` | — | — | InstanceEditable |
| `Using Player Occlusion` | `bool` | `False` | `Mode Derivatives` | — | — | InstanceEditable, Private |
| `UDW Snow Value` | `real<double>` | `0.000000` | `Hidden Exposed` | — | — | InstanceEditable |
| `UDW Rain Value` | `real<double>` | `0.000000` | `Hidden Exposed` | — | — | InstanceEditable |
| `Started Editor Tick Handler` | `bool` | `False` | `Hidden Exposed` | — | — | InstanceEditable |
| `Lens Flare Post Process` | `object<PostProcessComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Cloud Fog Post Process` | `object<PostProcessComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Path Tracer Fog Post Process` | `object<PostProcessComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Cloud Movement Increment Timer` | `real<double>` | `0.000000` | `System - Cloud Movement` | — | — | InstanceEditable, Private |
| `Event Dispatcher Check Timer` | `struct<TimerHandle>` | `()` | `System - Time` | — | — | InstanceEditable, Private |
| `Editor Sequence Cache Speedup` | `bool` | `False` | `System - Cache` | — | — | InstanceEditable, Private |
| `Finished Player Occlusion Cycle` | `mcdelegate` | `()` | `System Dispatchers` | — | — | InstanceEditable, Private |
| `Player Occlusion Hard Update` | `mcdelegate` | `()` | `System Dispatchers` | — | — | InstanceEditable, Private |
| `Force Calculate Player Occlusion` | `bool` | `False` | `𝙽𝟸  ·  Player Occlusion` | — | — | InstanceEditable |
| `Hard Occlusion Update Last Tick` | `bool` | `False` | `𝙽𝟸  ·  Player Occlusion` | — | — | InstanceEditable, Private |
| `General Post Process` | `object<PostProcessComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Generate Mesh Distance Fields` | `bool` | `False` | `System - Project Settings` | — | — | InstanceEditable, Private |
| `UDS Dispatch Tunnel` | `object<UDS_DispatcherTunnel_C>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_DispatcherTunnel.UDS_DispatcherTunnel_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_DispatcherTunnelObject.UDS_DispatcherTunnelObject'` | `System - State` | — | — | InstanceEditable, Private |
| `Path Tracer Sky Resolution` | `byte<UDS_PathTracerSkyRes>` | `NewEnumerator0` | `𝙼𝟷  ·  Cinematics / Offline Rendering` | — | — | InstanceEditable |
| `Replicated Modifier State` | `struct<UDS_ModifierState>` | `(ModifierSpeeds_10_136D646E4A33FE4EE9D61FAF08E7FA34=(0.000000))` | `𝙻𝟷  ·  Sky Modifiers` | Replicated | `OnRep_Replicated Modifier State` | InstanceEditable, Private |
| `Time of Day Specific Modifiers Keys` | `TArray<object<UDS_Modifier_C>>` | — | `𝙻𝟷  ·  Sky Modifiers` | — | — | InstanceEditable, Private |
| `Time of Day Specific Modifiers Values` | `TArray<struct<UDS_TimeOfDay_FadeRange>>` | — | `𝙻𝟷  ·  Sky Modifiers` | — | — | InstanceEditable, Private |
| `Cloud Top World Height Bottom Layer` | `real<double>` | `0.000000` | `System - Volumetric Clouds` | — | — | InstanceEditable, Private |

## Functions (486)

### `2D Clouds Shading Offset Vector`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> LinearColor)`
- Local variables: _none_
- Nodes: 16
- Category: `𝙲𝟸  ·  2D Dynamic Clouds`

### `3 Color Time Blend`

- Access: `Protected`
- Flags: —
- Inputs: `(struct<LinearColor> Day Color, struct<LinearColor> Dawn/Dusk Color, struct<LinearColor> Night Color)`
- Outputs: `(struct<LinearColor> Out)`
- Local variables: _none_
- Nodes: 8
- Category: `𝙶𝟸  ·  Simplified Color`
- Description: Blends between a Day, Dawn/Dusk, and Night color,

### `Absent Directional Lights Brightness`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 13
- Category: `𝙴𝟺  ·  Directional Light`
- Description: Used to increase brightness of sky/sky lighting when the moon and sun are both absent.

### `Add Modifier`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Modifier_C> Modifier, real<double> Fade In Time = 20.000000)`
- Outputs: `()`
- Local variables (1): `Modifier Index`
- Nodes: 47
- Category: `𝙻𝟷  ·  Sky Modifiers`
- Description: Add a UDS Modifier to the sky, with an optional fade in time (in seconds)

### `Adjust Base Sun Light Intensity`

- Access: `Protected`
- Flags: —
- Inputs: `(struct<Vector> Sun Vector)`
- Outputs: `(real<double> Intensity, real<double> Multiplier)`
- Local variables: _none_
- Nodes: 14
- Category: `𝙴𝟷  ·  Sun`

### `Adjust for World Origin Rebasing`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14
- Category: `Update Sky`
- Description: Detects if the world origin has been moved and runs updates to correct the system for this

### `All Volumetric Cloud MIDs`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(TArray<object<MaterialInstanceDynamic>> MIDs)`
- Local variables (1): `All MIDs`
- Nodes: 21
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: Creates an array which includes all the dynamic material instances which need to be controlled with the volumetric cloud's parameters.

### `AP - 2D Cloud Tint`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Ambient Fog Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Aurora Intensity`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 19
- Category: `Apply Properties`

### `AP - Aurora Phase`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9
- Category: `Apply Properties`

### `AP - Cloud Dark Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Cloud Fog Post Process Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Cloud Fog Post Process Directional Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Cloud Fog Post Process Enabled`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `Apply Properties`

### `AP - Cloud Light Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Cloud Shadow Trace Distance`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Cloud Shadows Cancel`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Cloud Shadows Light Vector`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Cloud Wisps Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Cloud Wisps Gradient Vector`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Cloud Wisps Opacity`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Directional Inscattering Exponent`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Enable Lens Flare Post Process`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `Apply Properties`

### `AP - Exposure Bias`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9
- Category: `Apply Properties`

### `AP - Filtered Moon Light Intensity`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Fog Density`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Apply Properties`

### `AP - Fog Directional Inscattering Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Fog Height Falloff`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Fog Inscattering Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Fog Max Opacity`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Fog Sky Atmosphere Contribution`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Fog Start Distance`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - High Frequency Noise Amount`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Macro Variation`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Mie Anisotropy`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Mie Scattering Scale`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Moon Casting Shadows`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 22
- Category: `Apply Properties`

### `AP - Moon Light Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Moon Light Source Angle`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9
- Category: `Apply Properties`

### `AP - Moon Light Specular Scale`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Moon Lit Percent`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8
- Category: `Apply Properties`

### `AP - Moon Material Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Moon Material Intensity`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Moon Phase Angle`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Moon Root Vector`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Forward Vector`
- Nodes: 53
- Category: `Apply Properties`

### `AP - Moon Scale`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Moon Scattering Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Moon Volumetric Scattering Intensity`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Moon X Axis Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Multiscattering Intensity`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Multiscattering Occlusion`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Night Sky Glow Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Overcast Turbulence Strength`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Turbulence Strength`
- Nodes: 3
- Category: `Apply Properties`

### `AP - Painted Cloud Coverage Opacity Layer 1`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Painted Cloud Coverage Opacity Layer 2`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Phase Blend`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Post Process Blend Weights`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 20
- Category: `Apply Properties`

### `AP - Rayleigh Scattering Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Shading Offset Vector`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Shine Intensity`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sky Ambient Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sky Atmo Absorption Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Apply Properties`

### `AP - Sky Atmosphere Luminance`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sky Base Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sky Light Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sky Light Intensity`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sky Light Lower Hemisphere Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sky Lit Intensity`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sky Material Contrast Midpoint`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sky Overall Intensity`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sky Saturation`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Space Layer Brightness`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Stars Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Stars Orbit`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Stars Orientation`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Stars Phase`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Static Clouds Dynamic Rotation`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8
- Category: `Apply Properties`

### `AP - Static Clouds Lighting Mask`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Static Clouds Shadow Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Static Clouds Tint Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sun Disabled Brightness`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sun Disk Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sun Disk Reflection Intensity`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sun Glow Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sun Highlight Intensity`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sun Highlight Radius`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sun Light Casts Shadows`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 23
- Category: `Apply Properties`

### `AP - Sun Light Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sun Light Intensity`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sun Light Source Angle`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9
- Category: `Apply Properties`

### `AP - Sun Radius`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sun Root Vector`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Forward Vector`
- Nodes: 52
- Category: `Apply Properties`

### `AP - Sun Scattering Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sun Specular Scale`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Sun Volumetric Scattering Intensity`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Vol Cloud Inner Emit Limit`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Volumetric Cloud Albedo`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Volumetric Cloud Emissive Bottom`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Volumetric Cloud Emissive Top`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Volumetric Cloud Floor Variation Clear`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Volumetric Cloud Floor Variation Cloudy`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Volumetric Cloud Floor Variation Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Volumetric Cloud Lerp to Simplified`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Volumetric Cloud Light Rays Color`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `New Color`, `Current Strength`
- Nodes: 18
- Category: `Apply Properties`

### `AP - Volumetric Cloud Material Switch`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8
- Category: `Apply Properties`

### `AP - Volumetric Cloud Max Trace Distance`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Volumetric Cloud Multiscattering Phase 1`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Volumetric Cloud Sky Atmo Contribution`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `AP - Volumetric Cloud View Sample Scale`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Volumetric Fog Albedo`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10
- Category: `Apply Properties`

### `AP - Volumetric Fog Global Mat Extinction`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Volumetric Fog Ground Fog Extinction`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Apply Properties`

### `AP - Water Level`

- Access: `Protected`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Apply Properties`

### `Apply Cached Incoming Modifiers`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13
- Category: `𝙻𝟷  ·  Sky Modifiers`

### `Apply Configuration Override`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10
- Category: `Construct`

### `Apply Console Variable with Check`

- Access: `Public`
- Flags: —
- Inputs: `(string Cvar, real<double> setting, int Type)`
- Outputs: `()`
- Local variables (3): `Existing Bool`, `Existing Float`, `Existing Int`
- Nodes: 77
- Category: `Static Properties`
- Description: A function to apply a consolve variable only when necessary, to avoid setting cvars that are already set as desired.

### `Apply Editor Weather Override`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (3): `Override Cloud Coverage`, `Override Fog`, `Override Dust`
- Nodes: 65
- Category: `Weather Connection`

### `Apply Feature Level Mode Changes`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Made Changes)`
- Local variables (1): `Changes Applied`
- Nodes: 45
- Category: `Construct`

### `Apply Location Preset`

- Access: `Public`
- Flags: —
- Inputs: `(byte Location = NewEnumerator0)`
- Outputs: `()`
- Local variables (1): `DST Struct`
- Nodes: 34
- Category: `𝙳𝟷  ·  Simulation`
- Description: Takes in one of UDS' simulation location presets and applies it to the latitude/longitude and time zone.

### `Apply Modifier Property Overrides`

- Access: `Protected`
- Flags: —
- Inputs: `(object<UDS_Modifier_C> Modifier, real<double> Alpha)`
- Outputs: `()`
- Local variables (4): `Eased Alpha`, `Current Float Property`, `Current Color Property`, `Property Index`
- Nodes: 76
- Category: `𝙻𝟷  ·  Sky Modifiers`
- Description: Applies the overrides in a modifier object

### `Apply Modifiers`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (5): `Current Modifier Index`, `New Alpha`, `Next Frame Needs Update`, `Modifier Tick Timer`, `Modifier to Remove`
- Nodes: 75
- Category: `𝙻𝟷  ·  Sky Modifiers`
- Description: Uses the array of current modifiers to apply changes to the UDS float and color properties

### `Apply Saved UDS and UDW State`

- Access: `Public`
- Flags: —
- Inputs: `(struct<UDS_and_UDW_State> State)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 67
- Category: `Saving And Loading`
- Description: Takes a packaged state (created using "Create UDS and UDW State for Saving" and applies its contents to UDS, and UDW if one is in the scene.

### `Apply Sky Configuration`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Sky_Configuration_C> Configuration)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 88
- Category: `Utility Functions`
- Description: Call to apply a full configuration of all the exposed settings on UDS. Created using the Configuration Manager utility. Understand this necessarily restarts the entire system as if it is returning to begin play.

### `Apply Starting Modifiers`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `Insert Index`, `Current Modifier`
- Nodes: 93
- Category: `𝙻𝟷  ·  Sky Modifiers`

### `Apply System Time`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `Out of Range Time of Day`, `Time Zone Date Offset`
- Nodes: 52
- Category: `𝙳𝟷  ·  Simulation`
- Description: If enabled, sets the time and date to the system time

### `Apply Time of Day Specific Modifiers`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (7): `Modifier Array`, `Fade Range Array`, `Current Modifier`, `Current Fade Range`, `Fade In`, `Fade Out`, `Current Modifier Alpha`
- Nodes: 64
- Category: `𝙻𝟷  ·  Sky Modifiers`

### `Apply Volumetric Mode`

- Access: `Public`
- Flags: —
- Inputs: `(byte Mode = NewEnumerator0)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: Used to set the cvars controlled by Volumetric Cloud Rendering Mode

### `Approximate Real Sun Moon and Stars`

- Access: `Protected`
- Flags: —
- Inputs: `(real<double> Time of Day, bool Only Calculate Sun)`
- Outputs: `(struct<Vector> Sun Vector, struct<Vector> Moon Vector, real<double> Real Phase, struct<Vector> Phase Alignment, struct<LinearColor> Celestial Yaw, real<double> Celestial Orbit, struct<Vector> Sun Vector, struct<Vector> Moon Vector, real<double> Real Phase, struct<Vector> Phase Alignment, struct<LinearColor> Celestial Yaw, real<double> Celestial Orbit)`
- Local variables (26): `UTC Time of Day`, `UTC Time of Year`, `UTC Month`, `UTC Day`, `Day of Year Index`, `Seasonal Time`, `Local Geocoordinate`, `Viewer Position on Earth`, `Axial Tilt`, `Zenith Direction`, `UTC Year`, `Sun Direction`, `Stars Yaw`, `Stars Orbit`, `Celestial North Pole`, `Moon Direction`, `Moon Alignment`, `Moon Real Phase`, `Earth Center`, `Lunar Time`, `Moon Center`, `Lunar Inclination Cycle`, `Equation of Time Curve`, `Equation of Time Offset`, `Time Offset by DST and Time Zone`, `Days in This Year`
- Nodes: 281
- Category: `𝙳𝟷  ·  Simulation`
- Description: Uses the date, time, latitude and longitude, from the Simulation category, to determine Sun Moon and Stars orientations.

### `Bind Events to Tick`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 76
- Category: `Startup`

### `Cache Color`

- Access: `Protected`
- Flags: —
- Inputs: `(byte Property = NewEnumerator0, struct<LinearColor> Set Value, real<double> Change Tolerance = 0.000100, byte Update Group = NewEnumerator0, delegate& Event [ref])`
- Outputs: `()`
- Local variables (2): `Index`, `Need Update`
- Nodes: 57
- Category: `Cache`
- Description: Caches a color property, to be recalled later with Get Cached Color.

### `Cache Float`

- Access: `Protected`
- Flags: —
- Inputs: `(byte Property = NewEnumerator0, real<double> Set Value, real<double> Change Tolerance = 0.000001, byte Update Group = NewEnumerator0, delegate& Event [ref])`
- Outputs: `()`
- Local variables (2): `Index`, `Needs Update`
- Nodes: 56
- Category: `Cache`
- Description: Cache a float property, to be recalled using Get Cached Float.

### `Cache Global Fog Material Properties`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Weather Contribution`
- Nodes: 51
- Category: `𝙵𝟹  ·  Volumetric Fog`
- Description: Cached global extinction and ground fog extinction for the global volumetric material

### `Cache Post Process Blend Weights`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (9): `Current Component Settings`, `Post Component`, `Time Multiplier`, `Cloudy Multiplier`, `Fog Multiplier`, `Dust Multiplier`, `Interior Multiplier`, `Weather Multiplier`, `Post Process Index`
- Nodes: 143
- Category: `Cache`
- Description: Updates the Blend Weight of any of the Post Process components created by the Post Process Components array.

### `Cache Properties`

- Access: `Public`
- Flags: —
- Inputs: `(int Cache Group = -1, bool Starting Cache Fill)`
- Outputs: `()`
- Local variables (1): `Current Cache Group`
- Nodes: 458
- Category: `Cache`
- Description: Caches dynamic properties, including component settings, material parameters, light settings, etc. This function is run periodically to cache properties, then the rest of the frames, the cached values are used, lerping from the last set to the new set.

### `Cache Sun and Moon Orientation`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (5): `Real Sun Position`, `Real Moon Position`, `Real Moon Phase`, `Moon Alignment`, `Extend Dawn Dusk Multiplier`
- Nodes: 183
- Category: `Cache`
- Description: Caches the Sun and Moon's rotation, to be recalled later in Set Sun and Moon Root Rotation.

### `Camera Location Dependent Updates`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Distance Since Last HF Update`
- Nodes: 107
- Category: `Update Sky`

### `Change Sky Mode at Runtime`

- Access: `Public`
- Flags: —
- Inputs: `(byte New Sky Mode = NewEnumerator0)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `𝙰𝟷  ·  Basic Controls`
- Description: If you need to change the sky mode when the game is already running, use this function to do so.

### `Check DST on Date Change`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `𝙳𝟷  ·  Simulation`

### `Check for Cloud Coverage Target Recenter`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13
- Category: `𝙺𝟸  ·  Volumetric Cloud Painting`
- Description: Runs periodically to check if the render target for the painted volumetric cloud coverage needs to be recentered.

### `Check for Daylight Savings Time`

- Access: `Protected`
- Flags: —
- Inputs: `(int Hour)`
- Outputs: `()`
- Local variables (2): `DST Active`, `New Time of Day Out of Range`
- Nodes: 35
- Category: `𝙳𝟷  ·  Simulation`
- Description: Checks based on current date and time if DST should be active.

### `Check for Time Event Dispatchers`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (5): `Current Hour`, `Current Minute`, `Minute Changed`, `Hour Changed`, `Current Custom Dispatcher`
- Nodes: 95
- Category: `Event Dispatching`
- Description: Checks if the Sunset, Sunrise, or Hourly dispatchers should be fired

### `Check if DST is Allowed`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10
- Category: `𝙳𝟷  ·  Simulation`

### `Check if Point is Exposed to Sun or Moon Light`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Location, real<double> Distance to Trace = 20000.000000, TArray<object<Actor>> Actors to Ignore in Trace, byte Trace Channel = TraceTypeQuery1)`
- Outputs: `(bool Exposed to Sun, bool Exposed to Moon, bool Exposed to Either, real<double> Light Intensity (Lux))`
- Local variables (4): `Trace Hits`, `Hit By Sun`, `Not Blocked by Clouds`, `Hit By Moon`
- Nodes: 89
- Category: `𝙴𝟺  ·  Directional Light`
- Description: Takes in a world space location, and outputs values showing if that point is exposed directly to sun or moon light, as affected by shadows. Also outputs a value representing the actual brightness of light hitting the surface, in Lux. The effect of cloud shadows is approximated based on overall cloud density.

### `Check If Year is Leap Year`

- Access: `Protected`
- Flags: —
- Inputs: `(int Year)`
- Outputs: `(bool Leap Year)`
- Local variables: _none_
- Nodes: 6
- Category: `Date And Time`

### `Check to Start Volumetric Cloud Light Rays`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 31
- Category: `𝙺𝟷  ·  Volumetric Cloud Light Rays`
- Description: Checks if context calls for the volumetric cloud light rays effect, and creates the component if so

### `Cinematic Mode Startup`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8
- Category: `𝙼𝟷  ·  Cinematics / Offline Rendering`
- Description: Additional logic run on startup when in cinematic mode

### `Cinematic Runtime Update`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Update Sky`

### `Clear Modifiers`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14
- Category: `𝙻𝟷  ·  Sky Modifiers`
- Description: Instantly clear all applied modifiers

### `Clear Sky Modifier Post Processing`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11
- Category: `𝙻𝟷  ·  Sky Modifiers`

### `Clear/Delete Runtime Data`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 68
- Category: `Startup`

### `Client Check Initial Replication`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9
- Category: `Replication`

### `Cloud Coverage Target Mapping`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> Mapping)`
- Local variables: _none_
- Nodes: 10
- Category: `𝙺𝟸  ·  Volumetric Cloud Painting`
- Description: The current mapping for the render target used by painted volumetric cloud coverage.

### `Cloud Fog Post Process Enabled`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 4
- Category: `𝙲𝟷  ·  Volumetric Clouds`

### `Cloud Layer Top and Bottom World Height`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Bottom World Height, real<double> Top World Height)`
- Local variables: _none_
- Nodes: 16
- Category: `𝙲𝟷  ·  Volumetric Clouds`

### `Cloud Shadows Cloud Density`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue, real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 13
- Category: `𝙴𝟻  ·  Cloud Shadows`
- Description: Determines the cloud density parameter for the cloud shadows, based on Cloud Coverage.

### `Cloud Shadows Light Vector And Cancel Value`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> Vector, real<double> Cancel Value)`
- Local variables (2): `Shadows Vector`, `Transition Multiplier`
- Nodes: 54
- Category: `𝙴𝟻  ·  Cloud Shadows`
- Description: Generates the light vector parameter and cancel value for the cloud shadows light function

### `Cloud Shadows Parent Material`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(softobject<MaterialInterface> Mat, softobject<MaterialInterface> Mat, softobject<MaterialInterface> Mat, softobject<MaterialInterface> Mat, softobject<MaterialInterface> Mat, softobject<MaterialInterface> Mat, softobject<MaterialInterface> Mat)`
- Local variables: _none_
- Nodes: 25
- Category: `𝙴𝟻  ·  Cloud Shadows`
- Description: Finds the soft reference to the parent material, to be used for the cloud shadows light function dynamic material instance.

### `Cloud Texture Pan Scale`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Scale)`
- Local variables: _none_
- Nodes: 5
- Category: `𝙲𝟺  ·  Cloud Movement`

### `Cloud Texture Velocity`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> ReturnValue)`
- Local variables: _none_
- Nodes: 13
- Category: `𝙲𝟺  ·  Cloud Movement`
- Description: Represents the current speed the clouds are moving, either volumetric or 2D. Used to increment Cloud Position over time.

### `Cloud Wisp Gradient Vector`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> Out, struct<LinearColor> Out)`
- Local variables (2): `Using Sun Vector`, `Sun Threshold`
- Nodes: 29
- Category: `𝙲𝟻  ·  Cloud Wisps`
- Description: The vector parameter for the sky material, used to position and scale the gradient used to intensify the cloud wisps around the sun or moon.

### `Combined Night Brightness`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> out, real<double> out)`
- Local variables: _none_
- Nodes: 10
- Category: `Sky Material`
- Description: The Night Brightness variable plus the Extra Night Brightness When Cloudy effect.

### `Compare Version Strings`

- Access: `Public`
- Flags: —
- Inputs: `(string Version String A, string Version String B)`
- Outputs: `(byte Comparison, byte Comparison, byte Comparison, byte Comparison, byte Comparison)`
- Local variables (4): `Major A`, `Minor A`, `Major B`, `Minor B`
- Nodes: 27
- Category: `Construct`
- Description: Compare version strings formatted with a major version number, a period, then a minor version number.

### `Composite Context Vector`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> Out)`
- Local variables: _none_
- Nodes: 7
- Category: `Change Monitoring`

### `Composite Weather Vector`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> Out)`
- Local variables: _none_
- Nodes: 9
- Category: `Change Monitoring`

### `Configure Directional Light with Feature Toggle`

- Access: `Protected`
- Flags: —
- Inputs: `(bool Toggle, object<DirectionalLightComponent>& Selected Component Variable [ref], object<DirectionalLightComponent> Built in Light Component, object<DirectionalLight> Custom Light Actor, int Atmospheric Index, byte Mobility = Static, bool Light Visibility, object<SceneComponent> Parent)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 46
- Category: `𝙴𝟺  ·  Directional Light`
- Description: Sets visibility and determines what light component will be used by the system for sun or moon.

### `Configure Height Fog with Feature Toggle`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 20
- Category: `𝙵𝟷  ·  Fog Color`
- Description: Sets the selected height fog component, and its visibility

### `Configure Sky Light with Feature Toggle`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 64
- Category: `𝙴𝟹  ·  Sky Light`
- Description: Sets the active sky light component, its visibility, and mobility.

### `Create UDS and UDW State for Saving`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<UDS_and_UDW_State> Packaged State)`
- Local variables (1): `State`
- Nodes: 27
- Category: `Saving and Loading`
- Description: Outputs the state of dynamics like time and weather, to be saved with a save file or between levels. To load the data, use the function "Apply Saved UDS and UDW State". Note, this function doesn't pack together every single variable on the blueprints, only the typical dynamic ones which would make sense to include in save data.

### `Current 2D Cloud Tint`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> ReturnValue)`
- Local variables: _none_
- Nodes: 7
- Category: `𝙲𝟸  ·  2D Dynamic Clouds`
- Description: Tints the cloud colors on the sky material with Cloud Coverage.

### `Current Aurora Intensity`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 11
- Category: `𝙷𝟺  ·  Aurora`
- Description: The current intensity of the aurora, either the 2D aurora or volumetric aurora

### `Current Base Clouds Scale`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 5
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: Scales the "Base Clouds Scale" setting with the standard world scale of the texture and Volumetric Clouds Scale, for the final world space size of the base clouds texture for the volumetric clouds.

### `Current Cloud Fog Post Process Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> Color, struct<LinearColor> Directional Color)`
- Local variables: _none_
- Nodes: 12
- Category: `𝙲𝟷  ·  Volumetric Clouds`

### `Current Cloud Wisps Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> Out)`
- Local variables: _none_
- Nodes: 17
- Category: `Sky Material`

### `Current Directional Inscattering Exponent`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue, real<double> ReturnValue)`
- Local variables (1): `Exponent`
- Nodes: 20
- Category: `𝙵𝟷  ·  Fog Color`

### `Current Event Date`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<UDS_DateAndTime> ReturnValue)`
- Local variables: _none_
- Nodes: 6
- Category: `𝙳𝟷  ·  Simulation`

### `Current Exposure Bias`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Bias)`
- Local variables: _none_
- Nodes: 20
- Category: `𝙴𝟼  ·  Exposure`
- Description: Based on all the settings in the Exposure category for bias, finds what the current bias value should be, based on time, cloud coverage, fog and dust.

### `Current Fog Density`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 27
- Category: `𝙵𝟸  ·  Fog Density`
- Description: Determines the current density for the height fog component, based on weather, time and exposed settings.

### `Current Fog Directional Inscattering Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> Directional Inscattering Color)`
- Local variables (1): `Base Intensity`
- Nodes: 35
- Category: `𝙵𝟷  ·  Fog Color`
- Description: Finds the current directional inscattering color for the height fog component.

### `Current Fog Inscattering Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> Inscattering Color)`
- Local variables (1): `Base Color`
- Nodes: 28
- Category: `𝙵𝟷  ·  Fog Color`
- Description: Finds the current fog inscattering color for the height fog component.

### `Current Hour as Integer`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(int Hour)`
- Local variables: _none_
- Nodes: 8
- Category: `Time`
- Description: Outputs the current hour on UDS, from the Time of Day value

### `Current Lerp to Simplified Clouds`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Alpha)`
- Local variables: _none_
- Nodes: 19
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: Used to scale the 3D noise contribution down when the material is about to change over to the simplified version, which doesn't use the 3D noise.

### `Current Light Pollution`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> ReturnValue)`
- Local variables: _none_
- Nodes: 8
- Category: `𝙷𝟹  ·  Sky Glow`
- Description: The current color applied based on the Light Pollution settings and time of day.

### `Current Lit Intensity`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 4
- Category: `Sky Material`
- Description: Determines the Lit Intensity parameter, which scales the brightness of the base sky color, cloud wisps and 2D dynamic clouds. Basically everything except the nighttime elements like moon, stars and aurora.

### `Current Max Trace Distance`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 12
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: Determines the current Max Trace Distance for the volumetric clouds, depending on the camera's position within the cloud layer.

### `Current Mie Anisotropy`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 7
- Category: `𝙶𝟷  ·  Sky Atmosphere`
- Description: Scales Mie Anisotropy for the Sky Atmosphere component, based on Cloud Coverage.

### `Current Mie Scattering Scale`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables (3): `Max Cloud Coverage Level`, `Max Unscaled Scattering`, `Final Scale`
- Nodes: 19
- Category: `𝙶𝟷  ·  Sky Atmosphere`
- Description: Determines Mie Scattering Scale for the Sky Atmosphere component, based on Cloud Coverage and Fog.

### `Current Minute as Integer`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(int Minute)`
- Local variables: _none_
- Nodes: 6
- Category: `Time`
- Description: Outputs the current minute (0-59) on UDS, from the Time of Day value

### `Current Month Lengths`

- Access: `Public`
- Flags: —
- Inputs: `(int Year)`
- Outputs: `(TArray<int> Lengths)`
- Local variables: _none_
- Nodes: 7
- Category: `Date And Time`

### `Current Moon Light Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> Color)`
- Local variables (2): `Base Color`, `Tinted Color`
- Nodes: 21
- Category: `𝙴𝟸  ·  Moon`

### `Current Moon Lit Percent`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue, real<double> ReturnValue, real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 14
- Category: `𝙴𝟸  ·  Moon`
- Description: Turns Moon Phase into a 0 to 1 value representing how much of the visible face of the moon is lit. This is used to do things like affect the brightness of the moon directional light with the moon phase.

### `Current Moon Material Intensity`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue, real<double> ReturnValue, real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 23
- Category: `𝙴𝟸  ·  Moon`
- Description: The current level of intensity to render the visible moon texutre and glow, in the sky material.

### `Current Moon Phase Angle`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> ReturnValue)`
- Local variables: _none_
- Nodes: 7
- Category: `𝙴𝟸  ·  Moon`
- Description: A color parameter which stores a vector, used to create the moon phase in the sky material. This is essentially the direction of the sun light, relative to the moon's texture space.

### `Current Moon Scale`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Scale, real<double> Scale, real<double> Scale)`
- Local variables: _none_
- Nodes: 17
- Category: `𝙴𝟸  ·  Moon`
- Description: The current scale of the visible moon, scaled by "Scale Moon Radius As It Nears Horizon". The Cutout value is used to  create a circular mask for the moon, in the Moon material function.

### `Current Moons Cloud Mask`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue, real<double> ReturnValue, real<double> ReturnValue, real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 18
- Category: `𝙷𝟸  ·  Space Layer`

### `Current Night Sky Glow`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> ReturnValue)`
- Local variables: _none_
- Nodes: 21
- Category: `𝙷𝟹  ·  Sky Glow`
- Description: The color contributed by Night Sky Glow. Used for the sky material and clouds.

### `Current Overall Intensity`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 7
- Category: `Sky Material`
- Description: Gets the overall intensity, specifically for use as a parameter on the sky material.

### `Current Overcast Turbulence Strength`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 8
- Category: `𝙲𝟷  ·  Volumetric Clouds`

### `Current Rayleigh Scattering Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> ReturnValue, struct<LinearColor> ReturnValue)`
- Local variables (1): `Base Color`
- Nodes: 29
- Category: `𝙶𝟷  ·  Sky Atmosphere`
- Description: Desaturates and brightens the Rayleigh Scattering Color for the Sky Atmosphere component, with Cloud Coverage and the exposed settings.

### `Current Sky Ambient Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> Sky Ambient Color)`
- Local variables: _none_
- Nodes: 28
- Category: `Sky Material`
- Description: Gets the current sky ambient color for the sky material, to be used for the cloud wisps.

### `Current Sky Atmosphere Absorption Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> out)`
- Local variables (1): `Twilight Alpha`
- Nodes: 25
- Category: `𝙶𝟷  ·  Sky Atmosphere`

### `Current Sky Atmosphere Luminance`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> ReturnValue)`
- Local variables: _none_
- Nodes: 13
- Category: `𝙶𝟷  ·  Sky Atmosphere`
- Description: Scales the colors generated for atmospheric scattering by the sky atmosphere component.

### `Current Sky Light Lower Hemisphere Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> ReturnValue, struct<LinearColor> ReturnValue, struct<LinearColor> ReturnValue)`
- Local variables: _none_
- Nodes: 15
- Category: `𝙴𝟹  ·  Sky Light`
- Description: Based on the current sky light mode, determines the color of the lower hemisphere of the sky light.

### `Current Solar Eclipse Values`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Eclipse Percent, struct<LinearColor> Tint Color, real<double> Eclipse Percent, struct<LinearColor> Tint Color)`
- Local variables (6): `Sun Fraction Showing`, `Sun Angular Diameter`, `Space Planet`, `Sun Root Rotation`, `Moon Root Rotation`, `Planet Location`
- Nodes: 71
- Category: `𝙴𝟷  ·  Sun`
- Description: Calculates how covered the sun is by the moon or space planets, for solar eclipses

### `Current Space Layer Brightness`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables (1): `Result Value`
- Nodes: 32
- Category: `𝙷𝟸  ·  Space Layer`

### `Current Stars Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> ReturnValue)`
- Local variables (1): `Applied Intensity`
- Nodes: 27
- Category: `𝙷𝟷  ·  Stars`
- Description: Determines the stars color parameter used by the sky material. Scales with stars intensity.

### `Current Sun Disk Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> ReturnValue)`
- Local variables (1): `Unscaled Color`
- Nodes: 30
- Category: `𝙴𝟷  ·  Sun`
- Description: The color of the sun disk as used in the sky material, multiplied by the sun disk color curve and the current sun disk intensity.

### `Current Sun Disk Intensity`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 17
- Category: `𝙴𝟷  ·  Sun`
- Description: Determines the sun disk intensity, as used in the sky material to scale the sun color.

### `Current Sun Light Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> ReturnValue, struct<LinearColor> ReturnValue)`
- Local variables (1): `Out Color`
- Nodes: 26
- Category: `𝙴𝟷  ·  Sun`
- Description: The current color applied to the sun directional light.

### `Current Sun Light Intensity`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue, real<double> ReturnValue)`
- Local variables (1): `Unscaled Intensity`
- Nodes: 37
- Category: `𝙴𝟷  ·  Sun`
- Description: The current intensity value set on the sun directional light. Scaled by directional balance, dimming, and the Directional Intensity curve if using SImplified Color

### `Current Sun Radius`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue, real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 13
- Category: `𝙴𝟷  ·  Sun`
- Description: Radius of the sun disk, scaled by the "Scale Sun Radius As It Nears Horizon" setting.

### `Current Sun Specular Scale`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 17
- Category: `𝙴𝟷  ·  Sun`

### `Current Sunrise Event Time`

- Access: `Public`
- Flags: —
- Inputs: `(bool Add Event Offset = true)`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 11
- Category: `Time`
- Description: Outputs the Time of Day that the Sunrise event dispatcher should be fired today.

### `Current Sunset Event Time`

- Access: `Public`
- Flags: —
- Inputs: `(bool Add Event Offset = true)`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 11
- Category: `Time`
- Description: Outputs the Time of Day that the Sunset event dispatcher should be fired today.

### `Current Sunset/Sunrise Event State`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Sun Up)`
- Local variables: _none_
- Nodes: 16
- Category: `Event Dispatching`

### `Current View Sample Scale`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> out, real<double> out)`
- Local variables (1): `Count`
- Nodes: 29
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: Determines view sample scale with day and night values and scaled by material quality.

### `Current Volumetric Cloud Albedo`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> ReturnValue)`
- Local variables: _none_
- Nodes: 40
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: Determines the albedo/color of the volumetric clouds, using the setting for volumetric cloud color, and scaling with Overall Intensity and Directional Balance.

### `Current Volumetric Cloud Inner Emit Limit`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 7
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: The limit on the amount emissive color can be increased by extinction in the volumetric cloud material. This value is used for clouds close to the viewer.

### `Current Volumetric Cloud Macro Variation`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 7
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: The amount that the Macro Variation is applied, scaled by the setting for it and scaled up and down with cloud coverage.

### `Current Volumetric Cloud Multiscattering Intensity`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 6
- Category: `𝙲𝟷  ·  Volumetric Clouds`

### `Current Volumetric Cloud Multiscattering Occlusion`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Occlusion)`
- Local variables: _none_
- Nodes: 10
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: Determines the multiscattering occlusion for the volumetric clouds. How much light is occluded as it passes through the layer.

### `Current Volumetric Cloud Shadow Tracing Distance`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 21
- Category: `𝙲𝟷  ·  Volumetric Clouds`

### `Current Volumetric Cloud Sky Atmo Contribution`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 12
- Category: `𝙲𝟷  ·  Volumetric Clouds`

### `Current Volumetric Clouds Density`

- Access: `Protected`
- Flags: —
- Inputs: `(bool Layer 1 = true)`
- Outputs: `(real<double> Out, real<double> Out)`
- Local variables: _none_
- Nodes: 20
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: Determines the density value used for the volumetric cloud material, based on Cloud Coverage

### `Current Volumetric Multiscattering Phase 1`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 8
- Category: `𝙲𝟷  ·  Volumetric Clouds`

### `Current Wisps Opacity`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables (1): `Base`
- Nodes: 25
- Category: `Sky Material`
- Description: The current opacity of the cloud wisps in the sky material

### `Custom Painted Cloud Coverage Target Drawing Logic`

- Access: `Protected`
- Flags: —
- Inputs: `(object<Canvas> Canvas)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1
- Category: `𝙺𝟸  ·  Volumetric Cloud Painting`
- Description: An empty function which is called as part of the logic for drawing the painted cloud coverage render target. Can be overriden to add extra logic which is applied before the normal painted coverage and radial storms.

### `Date and Time to Year Progress`

- Access: `Protected`
- Flags: —
- Inputs: `(int Month, int Day, real<double> Time)`
- Outputs: `(real<double> Days from Start of Year)`
- Local variables: _none_
- Nodes: 12
- Category: `Date And Time`
- Description: Takes a date and time and finds the exact amount of time in days since the start of the year

### `Day Count at the Start of a Month`

- Access: `Protected`
- Flags: —
- Inputs: `(int Year, int Month)`
- Outputs: `(int Count)`
- Local variables: _none_
- Nodes: 10
- Category: `Date And Time`

### `Day Ended`

- Access: `Protected`
- Flags: —
- Inputs: `(bool Forward = true)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Time`
- Description: Calls the midnight dispatcher and offsets the current date forward

### `Days Since J2000`

- Access: `Protected`
- Flags: —
- Inputs: `(int Input Day, int Input Month, int Input Year)`
- Outputs: `(int Days)`
- Local variables (1): `Positive`
- Nodes: 4
- Category: `𝙳𝟷  ·  Simulation`
- Description: Finds the number of days (positive or negative) since January 1st 2000.

### `Days Since Y1D1M1`

- Access: `Protected`
- Flags: —
- Inputs: `(int Input Day, int Input Month, int Input Year)`
- Outputs: `(int Days)`
- Local variables (5): `Year Delta`, `Day Count`, `Number of Leap Years`, `Number of Non Leap Years`, `Day Count in a Non Leap Year`
- Nodes: 86
- Category: `Date And Time`
- Description: The number of days since year 1, day 1, month 1 on the selected calendar.

### `Dedicated Server Startup`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `Startup`

### `Dimming Directional Lights`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 10
- Category: `𝙴𝟺  ·  Directional Light`
- Description: Outputs true if the directional lights should be dimmed down to 0 when cloud coverage is high.

### `Directional Inscattering Multiplier`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Multiplier)`
- Local variables: _none_
- Nodes: 16
- Category: `𝙴𝟺  ·  Directional Light`
- Description: Used to scale directional light intensity based on cloud coverage and fog.

### `Directional Light Dimming`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out, real<double> Out)`
- Local variables: _none_
- Nodes: 15
- Category: `𝙴𝟺  ·  Directional Light`
- Description: Dims directional light intensity down to 0 using Cloud Coverage, if the setting for it is enabled.

### `Directional Source Angle`

- Access: `Protected`
- Flags: —
- Inputs: `(real<double> Disk Scale, real<double> Max Scale Factor, real<double> Scale Setting)`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 19
- Category: `𝙴𝟷  ·  Sun`
- Description: Determines the light source angle of the sun or moon directional light.

### `Disable Instant Exposure`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `𝙴𝟼  ·  Exposure`

### `Editor Freeze Cloud Movement`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11
- Category: `Editor`

### `Editor Return from PIE`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12
- Category: `Editor`

### `Editor Tick`

- Access: `Public`
- Flags: —
- Inputs: `(bool Sequencer Open)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 51
- Category: `Editor`

### `Editor Update from UDW`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15
- Category: `Editor`

### `Editor Update Sun and Moon Target Handles`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 51
- Category: `Editor`

### `Filtered Moon Light Intensity`

- Access: `Protected`
- Flags: —
- Inputs: `(real<double> Unfiltered)`
- Outputs: `(real<double> Intensity)`
- Local variables: _none_
- Nodes: 11
- Category: `𝙴𝟸  ·  Moon`
- Description: Filters the moon light intensity with the Directional Balance and the scattering multiplier.

### `Find DST Start and End Times`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (12): `Months`, `Day Counts`, `Days of the Week`, `Tested Month`, `Tested Day Count`, `Tested Day of the Week`, `First Day of the Month`, `Days in Tested Month`, `First Instance of Tested Day This Month`, `Days in a Week`, `Number of this Day of the Week This Month`, `Final Values`
- Nodes: 87
- Category: `𝙳𝟷  ·  Simulation`
- Description: Finds the days which DST starts and ends

### `Find Real Sunset/Sunrise Times`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (3): `Sunrise Time`, `Current Factor`, `Sunset Time`
- Nodes: 59
- Category: `𝙳𝟷  ·  Simulation`
- Description: Calculates the accurate simulated sunset and sunrise times of the simulation. Used if Simulate Real Sun is true. This is run at midnight every day to find the values for the next 24 hours.

### `Finish Time Transition`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Time Transition`
- Description: Sets Transitioning Time to false. Only to be used with a Timer for the transition system.

### `Finished Occlusion Cycle`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion_Interface.UDS_PlayerOcclusion_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 3

### `Fire Editor Dispatchers`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 17
- Category: `Event Dispatching`
- Description: Calls Sunset and Sunrise as part of construction script, so that actors which bind to these events as part of their construction script can be affected in editor.

### `Fog and Dust Shadow Value`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 12
- Category: `𝙴𝟻  ·  Cloud Shadows`

### `Fog Height Falloff`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 13
- Category: `𝙵𝟸  ·  Fog Density`
- Description: Determines the current height falloff for the height fog component, based on fog, cloud coverage and dust.

### `Fog Max Opacity`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 6
- Category: `𝙵𝟷  ·  Fog Color`

### `Fog Start Distance`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 15
- Category: `𝙵𝟸  ·  Fog Density`
- Description: Uses the current fog density to determine the start distance of the fog

### `Force Valid Day`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 25
- Category: `Date And Time`
- Description: Makes sure the calendar and date variables is valid. If the date was set to December 50th, this function would bring the day down to 31. Factors in Leap Years.

### `Full Reconstruction at Runtime`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14
- Category: `Utility Functions`
- Description: Restarts the blueprint and reruns the entire construction script.

### `Game User Settings Bound Updates`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙼𝟸  ·  Scalability / Performance`

### `Get All Modifier Property Values`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(TMap<byte, ?> Floats, TMap<byte, ?> Colors)`
- Local variables (2): `Color Map`, `Float Map`
- Nodes: 12
- Category: `𝙻𝟷  ·  Sky Modifiers`
- Description: Outputs all the values for every property on UDS which can be affected by the sky modifier system

### `Get Cached Color`

- Access: `Protected`
- Flags: —
- Inputs: `(byte Property = NewEnumerator0)`
- Outputs: `(struct<LinearColor> Value)`
- Local variables (2): `Prop Index`, `New Value`
- Nodes: 22
- Category: `Cache`

### `Get Cached Float`

- Access: `Protected`
- Flags: —
- Inputs: `(byte Property = NewEnumerator0)`
- Outputs: `(real<double> Value)`
- Local variables (2): `Property Index`, `New Value`
- Nodes: 22
- Category: `Cache`
- Description: Gets a float property which has been cached by Cache Properties

### `Get Cloud Coverage 0-10`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Cloud Coverage)`
- Local variables: _none_
- Nodes: 7
- Category: `Cloud Coverage`

### `Get Cloud Coverage 0-3`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Cloud Coverage, real<double> Cloud Coverage)`
- Local variables: _none_
- Nodes: 9
- Category: `Cloud Coverage`

### `Get Cloud Coverage Local`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Local Height, real<double> Local Height)`
- Local variables (1): `Height Multiplier`
- Nodes: 17
- Category: `Cloud Coverage`

### `Get Current Camera Location`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion_Interface.UDS_PlayerOcclusion_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> Out)`
- Local variables: _none_
- Nodes: 3

### `Get Current Month as String`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(string Month)`
- Local variables: _none_
- Nodes: 8
- Category: `Date And Time`
- Description: Outputs the name of the current Month, as a string

### `Get Current Sky Light Color and Intensity`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out Intensity, struct<LinearColor> Out Color)`
- Local variables (7): `Intensity Output`, `Color Output`, `Current Multiplier Color`, `Luminance Intensity Balance`, `Base Color`, `Temperature Tint`, `Base Intensity`
- Nodes: 94
- Category: `𝙴𝟹  ·  Sky Light`
- Description: Based on the current sky light mode, determines the color and intensity of the sky light.

### `Get Current UDS Date and Time`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<UDS_DateAndTime> UDS Date and Time)`
- Local variables: _none_
- Nodes: 7
- Category: `Date And Time`
- Description: Outputs a UDS specific structure containing Year Month Day and Time of Day

### `Get Current Volumetric Cloud Extinction Scale`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Top)`
- Local variables: _none_
- Nodes: 6
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: Determines the extinction scale (volumetric density) of the top and bottom of the cloud layer.

### `Get DateTime`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<DateTime> Current Date and Time)`
- Local variables: _none_
- Nodes: 10
- Category: `Date and Time`
- Description: Constructs a Date Time struct using the current Time of Day and Year Month and Day on UDS.

### `Get Day of the Week`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(int Index, string Name)`
- Local variables: _none_
- Nodes: 6
- Category: `Date And Time`
- Description: Uses the date values and the selected calendar asset to find the current day of the week. Outputs the index of the day and the name as a string.

### `Get Day of the Week On Date`

- Access: `Protected`
- Flags: —
- Inputs: `(int Input Day, int Input Month, int Input Year)`
- Outputs: `(int Index, string Name)`
- Local variables: _none_
- Nodes: 14
- Category: `Date and Time`

### `Get Editor Camera Transform`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10
- Category: `Editor`

### `Get Filtering Location`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArrayOwner_Interface.UDS_InterfaceActorArrayOwner_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> Filtering Location)`
- Local variables: _none_
- Nodes: 3

### `Get GPU DF Sample Count`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion_Interface.UDS_PlayerOcclusion_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(int Out)`
- Local variables: _none_
- Nodes: 3

### `Get GPU Distance Field Toggle`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion_Interface.UDS_PlayerOcclusion_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Out)`
- Local variables: _none_
- Nodes: 3

### `Get Inverted Global Occlusion`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Current, real<double> Current)`
- Local variables: _none_
- Nodes: 12
- Category: `𝙽𝟸  ·  Player Occlusion`

### `Get Manual Target Change Speed`

- Access: `Protected`
- Flags: —
- Inputs: `(struct<Vector>& Old Vector [ref], struct<Vector> New Vector)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15
- Category: `Change Monitoring`

### `Get Occlusion Min and Max Fraction`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion_Interface.UDS_PlayerOcclusion_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Min, real<double> Max)`
- Local variables: _none_
- Nodes: 4

### `Get Occlusion Mode`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion_Interface.UDS_PlayerOcclusion_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte Out)`
- Local variables: _none_
- Nodes: 3

### `Get Occlusion Sampling Location`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion_Interface.UDS_PlayerOcclusion_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte Out)`
- Local variables: _none_
- Nodes: 3

### `Get Occlusion Trace Channel`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion_Interface.UDS_PlayerOcclusion_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte Out)`
- Local variables: _none_
- Nodes: 3

### `Get Occlusion Trace Max Distance`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion_Interface.UDS_PlayerOcclusion_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 3

### `Get Occlusion Trace Steps`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion_Interface.UDS_PlayerOcclusion_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(int Vertical, int Horizontal)`
- Local variables: _none_
- Nodes: 4

### `Get Occlusion Update Period`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion_Interface.UDS_PlayerOcclusion_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 3

### `Get Query Occlusion Portals`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion_Interface.UDS_PlayerOcclusion_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Out)`
- Local variables: _none_
- Nodes: 3

### `Get Runtime Camera Transform`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Update Sky`

### `Get Show Trace Debugs`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion_Interface.UDS_PlayerOcclusion_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Out)`
- Local variables: _none_
- Nodes: 3

### `Get Sky MID Parent Material Instance`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(softobject<MaterialInterface> ReturnValue)`
- Local variables: _none_
- Nodes: 35
- Category: `Sky Material`
- Description: Finds the soft reference to the appropriate material instance to use as the parent when making the dynamic material instance for the sky material.

### `Get TimeCode`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Timecode> Time)`
- Local variables: _none_
- Nodes: 7
- Category: `Time`
- Description: Converts Time of Day into a standard Timecode format, with hours/minutes/seconds

### `Get UDW Reference`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 17
- Category: `Weather Connection`

### `Get Volumetric Cloud Emissive Colors`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> Bottom, struct<LinearColor> Top)`
- Local variables (2): `Light from Aurora`, `Light Intensity Multiplier`
- Nodes: 44
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: Calculates the emissive colors for the volumetric cloud layers, including things like the night sky glow and the aurora's light contribution.

### `Global Volumetric Fog Parent Mat`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(softobject<MaterialInterface> ReturnValue)`
- Local variables: _none_
- Nodes: 11
- Category: `𝙵𝟹  ·  Volumetric Fog`

### `Ground UDS Actor`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9
- Category: `Editor`

### `H/M/S/MS to Time of Day`

- Access: `Public`
- Flags: —
- Inputs: `(int Hours, int Minutes, int Seconds, int Miliseconds)`
- Outputs: `(real<double> Time)`
- Local variables: _none_
- Nodes: 14
- Category: `Time`
- Description: Converts a value of Hours, Minutes, Seconds and Miliseconds over to a float formatted for Time of Day.

### `Hard Reset Cache`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8
- Category: `Cache`
- Description: Forced a complete update of the property cache

### `Hide Sky`

- Access: `Public`
- Flags: —
- Inputs: `(bool Hide Entire Actor, bool Hide Lights, bool Hide Fog/Atmosphere, bool Hide Sky Sphere/Clouds, bool Hide Post Processing)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 34
- Category: `Utility Functions`
- Description: At runtime, use to hide/show the entire sky, or specific elements like lights/fog/sky sphere. If you want to hide weather effects as well, UDW has its own similar Hide Weather function.

### `If DBuffer Supported`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables (3): `Desktop Dbuffer Toggle`, `Mobile Dbuffer Toggle`, `Mobile Shading Path`
- Nodes: 14
- Category: `Static Properties`
- Description: Queries rendering cvars and UDS Feature Level setting to see if the DBuffer is supported by the rendering context

### `Increment Cache Timer`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (6): `Last Cache Step`, `New Timer 9`, `Max Recent Cache Timer Speed`, `Change Speed This Frame`, `Delayed Change Speed`, `New Target Timer Length`
- Nodes: 104
- Category: `Cache`

### `Increment Cloud Movement Cache`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (7): `Clouds Time Offset`, `Cloud Movement Vector`, `Time Delta`, `Shared Time Offset`, `Texture Velocity`, `Fog Movement Vector`, `UDW Wind Multiplier`
- Nodes: 86
- Category: `𝙲𝟺  ·  Cloud Movement`
- Description: Offsets the position of the clouds with their current velocity and caches the new values.

### `Increment Time of Day Forward`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Amount)`
- Outputs: `()`
- Local variables (2): `Offset Time Out of Range`, `Offset Time In Range`
- Nodes: 37
- Category: `Time`
- Description: Offsets Time of Day forward, starting a new day and incrementing the date if needed.

### `Initialize Occlusion`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11
- Category: `𝙽𝟸  ·  Player Occlusion`
- Description: Starts the player occlusion component, if Apply interior Adjustments is enabled.

### `Inside Outside Cloud Layer`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables (1): `Local Normalized Height`
- Nodes: 23
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: 0-1 Value representing how "deep" in the cloud layer the camera is. 1 when outside the cloud layer. Goes to 0 at midway through the layer.

### `Is Date and Time in Daylight Savings Time`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue, bool ReturnValue)`
- Local variables (1): `Current Year Progress`
- Nodes: 22
- Category: `Date And Time`

### `Is Directional Light Casting Shadows`

- Access: `Protected`
- Flags: —
- Inputs: `(bool Force Disabled, struct<Vector> Light Vector)`
- Outputs: `(bool Yes, bool Yes, bool Yes, bool Yes)`
- Local variables (3): `Disable Shadows`, `Sun High Enough for Shadows`, `Coverage High Enough for Disable`
- Nodes: 31
- Category: `𝙴𝟺  ·  Directional Light`
- Description: Determines based on its height if the sun should currently be casting shadows. Also disables shadows if cloud shadows have completely occluded the light, if the option for that is enabled.

### `Is it Daytime?`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Yes)`
- Local variables: _none_
- Nodes: 9
- Category: `Time`
- Description: Returns true if the sun is above the horizon

### `Lens Flare Parent Material`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(softobject<MaterialInterface> Mat)`
- Local variables: _none_
- Nodes: 8
- Category: `𝙸𝟸  ·  Lens Flare`
- Description: Finds the soft reference to the material for the selected Lens Flare Type.

### `Lens Flare Post Process Enabled`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Out, bool Out, bool Out)`
- Local variables (1): `Allow Lens Flare`
- Nodes: 30
- Category: `𝙸𝟸  ·  Lens Flare`

### `Lights Update Degree Threshold Test`

- Access: `Protected`
- Flags: —
- Inputs: `(struct<Vector> Forward Vector, object<SceneComponent> Light)`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 7
- Category: `𝙴𝟺  ·  Directional Light`
- Description: Tests if the root is far enough from the directional light component for the sun or moon to trigger a light rotation update

### `Log UDS Version Number`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Startup`
- Description: Prints the UDS version number to the log. Runs on startup, so that log files contain the information, to help with debugging user issues with UDS

### `Make Post Process Material and Component`

- Access: `Protected`
- Flags: —
- Inputs: `(object<PostProcessComponent>& Component [ref], object<MaterialInterface> Parent Material, object<MaterialInstanceDynamic>& MID [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 16
- Category: `𝙸𝟹  ·  Post Processing`

### `Monitor for Changes`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (3): `Time Since Last Check`, `New Composite Weather`, `New Composite Context`
- Nodes: 88
- Category: `Change Monitoring`
- Description: Keep track of changes in key dynamics like Time of Day, Fog, Cloud Coverage, and Dust. These resultant change speeds are used to determine how often the system caches properties, and if ticks can be skipped.

### `Moon Effective Illumination 0-1`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 11
- Category: `𝙴𝟸  ·  Moon`

### `Moon Light Specular Scale`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 22
- Category: `𝙴𝟸  ·  Moon`
- Description: Specular scale of the moon directional light, filtered by fog and cloud coverage.

### `Moon Light Volumetric Scattering Intensity`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 7
- Category: `𝙴𝟸  ·  Moon`
- Description: The current volumetric scattering intensity applied to the Moon directional light.

### `Moon Phase Light Multiplier`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue, real<double> Without Light Brightness)`
- Local variables: _none_
- Nodes: 10
- Category: `𝙴𝟸  ·  Moon`

### `Moon Z Vector`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> out)`
- Local variables: _none_
- Nodes: 16
- Category: `𝙴𝟸  ·  Moon`
- Description: Finds a good Z vector, for turning the X vector into a rotator

### `Night Filter`

- Access: `Public`
- Flags: —
- Inputs: `(bool Cached = true)`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 11
- Category: `Time`
- Description: Outputs 1 at night and 0 during the day, and fades during dawn and dusk.

### `Night Filtered Night Brightness`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Multiplier)`
- Local variables: _none_
- Nodes: 5
- Category: `Sky Material`

### `Number of Days in a Year`

- Access: `Protected`
- Flags: —
- Inputs: `(int Year)`
- Outputs: `(int Count)`
- Local variables: _none_
- Nodes: 7
- Category: `Date And Time`

### `Occlusion Hard Update`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion_Interface.UDS_PlayerOcclusion_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 3

### `Offset Date`

- Access: `Public`
- Flags: —
- Inputs: `(int Offset = 1)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15
- Category: `Date And Time`
- Description: Offsets the current date by a number of days. Used at midnight to offset the date forward one day.

### `Offset Date by a Number of Days`

- Access: `Protected`
- Flags: —
- Inputs: `(int Input Month = 1, int Input Day = 1, int Input Year = 1, int Offset = 1)`
- Outputs: `(int Output Month, int Output Day, int Output Year)`
- Local variables (4): `Current Month`, `Current Day`, `Current Year`, `Forward`
- Nodes: 72
- Category: `Date And Time`
- Description: Takes in a date and an offset in days and outputs the date with the offset added to it.

### `Offset Time by Time Span`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Timespan> Timespan)`
- Outputs: `()`
- Local variables (2): `Time of Day Offset Value`, `Date Offset`
- Nodes: 30
- Category: `Time`
- Description: Moves Time of Day and date values forward or backward using a Time Span struct.

### `Offset Time of Day by Hours`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Hours)`
- Outputs: `()`
- Local variables (2): `Time of Day Offset Value`, `Date Offset`
- Nodes: 21
- Category: `Time`
- Description: Moves Time of Day forward or backward by a number of hours. Positive values are forward, negative values are backward. Date values will be affected if moving to a different day.

### `Open Editor Readme Entry`

- Access: `Protected`
- Flags: —
- Inputs: `(string Entry)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6
- Category: `Editor`

### `Open Editor Readme Entry Set`

- Access: `Protected`
- Flags: —
- Inputs: `(TArray<name> Entry)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6
- Category: `Editor`

### `Overcast Brightness`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 12
- Category: `Sky Material`

### `Overcast Luminance Boost`

- Access: `Protected`
- Flags: —
- Inputs: `(real<double> Multiplier = 1.650000)`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 7
- Category: `Cloud Coverage`

### `Populate Runtime Config Properties`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Sky_Configuration_C> Configuration)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 71
- Category: `System - Configuration`

### `Query Project Settings And UDS Version`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Mobile Shading Path`
- Nodes: 49
- Category: `Construct`
- Description: Gets some project level cvars, so that the system can use them to affect behavior.

### `Randomize Time Of Day`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8
- Category: `Time`
- Description: Randomizes the Time of Day, to be run on startup, if the option for it is enabled.

### `Remove Modifier`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Modifier_C> Modifier, real<double> Fade Out Time = 20.000000)`
- Outputs: `()`
- Local variables (1): `Modifier Index`
- Nodes: 30
- Category: `𝙻𝟷  ·  Sky Modifiers`
- Description: Remove a UDS Modifier which is currently active on the sky, with an optional fade out time (in seconds)

### `Remove Modifier from Arrays and Maps`

- Access: `Protected`
- Flags: —
- Inputs: `(int Modifier Index)`
- Outputs: `()`
- Local variables (1): `Modifier to Remove`
- Nodes: 31
- Category: `𝙻𝟷  ·  Sky Modifiers`

### `Restart Real Time Sky Light Capture`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15
- Category: `𝙴𝟹  ·  Sky Light`
- Description: Corrects for an engine bug with real time reflection capture, resulting from a conflict between UDS' applied cvars and the Effects Quality scalability group

### `Revert Changed Console Variables`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15
- Category: `Static Properties`

### `Revert Modified Properties`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 22
- Category: `𝙻𝟷  ·  Sky Modifiers`

### `Runtime Or Initializing`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 4
- Category: `Update Sky`

### `Scale Sample Count`

- Access: `Protected`
- Flags: —
- Inputs: `(real<double> in)`
- Outputs: `(real<double> out)`
- Local variables: _none_
- Nodes: 8
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: Scales a sample count for the volumetric cloud rendering, using the current global material quality level.

### `Scaled Directional Balance`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Balance)`
- Local variables: _none_
- Nodes: 5
- Category: `𝙴𝟺  ·  Directional Light`

### `Season Value for Weather from Date and Time`

- Access: `Public`
- Flags: —
- Inputs: `(int Day Offset, bool Meteorological Seasons)`
- Outputs: `(real<double> Season)`
- Local variables: _none_
- Nodes: 28
- Category: `Date And Time`
- Description: Finds the Season value for UDW, based on the current date and time

### `Second Frame Startup Functions`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Startup`

### `Set Apply Daylight Savings Time`

- Access: `Public`
- Flags: —
- Inputs: `(bool On)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `𝙳𝟷  ·  Simulation`
- Description: Call this if you need to toggle Apply Daylight Savings Time at runtime

### `Set Apply Exposure Settings`

- Access: `Public`
- Flags: —
- Inputs: `(bool Enabled)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15
- Category: `𝙴𝟼  ·  Exposure`
- Description: For turning the exposure settings on/off at runtime

### `Set Apply Property Event Binding`

- Access: `Public`
- Flags: —
- Inputs: `(bool Is Bound, byte Group = NewEnumerator0, delegate& Event [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 34
- Category: `Cache`

### `Set Cloud Coverage`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Cloud Coverage)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8
- Category: `𝙰𝟷  ·  Basic Controls`
- Description: Sets the current cloud coverage level on UDS. If UDW is in use, this applies a manual override to the weather state's cloud coverage level.

### `Set Current Fog Base Colors`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (6): `Desaturation Amount`, `Local Dust Fog Color`, `Local Fog Brightness Multiplier`, `Local Base Directional Scattering Fog Color`, `Sun Twilight Brightness Falloff`, `Moon Twilight Brightness Falloff`
- Nodes: 213
- Category: `𝙵𝟷  ·  Fog Color`
- Description: Generates a color for fog inscattering, directional inscattering, and cloud wisps/ambient sky color.

### `Set Date and Time`

- Access: `Public`
- Flags: —
- Inputs: `(struct<DateTime> Date Time)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Date And Time`
- Description: Takes a Date Time struct and uses it to set both the Time of Day and Year, Month and Day variables.

### `Set Directional Light Update Mode`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 31
- Category: `𝙴𝟺  ·  Directional Light`

### `Set Dust Amount`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Dust Amount)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `𝙵𝟺  ·  Dust`
- Description: Sets the current Dust Amount on UDS. If UDW is in use, this applies a manual override to the weather state's dust value.

### `Set Fog`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Fog)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `𝙰𝟷  ·  Basic Controls`
- Description: Sets the current Fog value on UDS. If UDW is in use, this applies a manual override to the weather state's fog value.

### `Set Modifier State`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Modifier_C> Modifier, real<double> Alpha)`
- Outputs: `()`
- Local variables (2): `Index`, `Existing Index`
- Nodes: 91
- Category: `𝙻𝟷  ·  Sky Modifiers`
- Description: Directly set the applied alpha of a UDS Modifier on the sky. This can be used to add a new modifier or remove one, with an alpha value that does not change after this function is called.

### `Set Previous Weather Variables`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10
- Category: `Weather Connection`

### `Set Time Cycle Degrees`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (3): `Internal Time`, `Time in Range`, `Daytime`
- Nodes: 47
- Category: `Time`
- Description: Converts the time of day to a value in degrees, to be used by the non-simulation sun and moon logic

### `Set Time with Time Code`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Timecode> Time Code)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Time`
- Description: Takes a Time Code struct and uses it to set the Time of Day on UDS.

### `Set Unmodified Property Values`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 21
- Category: `𝙻𝟷  ·  Sky Modifiers`
- Description: Saves the values for properties on UDS which have not been affected by modifiers. These are then used to lerp to and from the values in modifier assets.

### `Set Up Internal Bindings`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 28
- Category: `Startup`
- Description: Bind functions to event dispatchers. For things which need to update as time changes.

### `Set Variables Controlled by Weather`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 22
- Category: `Weather Connection`
- Description: Updates variables which UDW controls using the weather

### `Show Editor Warning`

- Access: `Protected`
- Flags: —
- Inputs: `(string Title, string Message)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10
- Category: `Editor`

### `Simplfied Color Sun Scattering`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> ReturnValue)`
- Local variables: _none_
- Nodes: 17
- Category: `𝙶𝟸  ·  Simplified Color`

### `Simplified Base Sky Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> Out)`
- Local variables: _none_
- Nodes: 9
- Category: `𝙶𝟸  ·  Simplified Color`

### `Simplified Cloud Dark Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> Out)`
- Local variables: _none_
- Nodes: 9
- Category: `𝙶𝟸  ·  Simplified Color`

### `Simplified Cloud Light Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> Out)`
- Local variables: _none_
- Nodes: 12
- Category: `𝙶𝟸  ·  Simplified Color`

### `Simplified Moon Scattering Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> ReturnValue, struct<LinearColor> ReturnValue)`
- Local variables: _none_
- Nodes: 17
- Category: `𝙶𝟸  ·  Simplified Color`

### `Size Cache Arrays`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Size`
- Nodes: 26
- Category: `Cache`
- Description: Zero fills the cached property arrays out to the number of entries in the property enum.

### `Sky Atmosphere Fog Contribution`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Output, real<double> Output)`
- Local variables (1): `Overcast Brightness Multiplier`
- Nodes: 45
- Category: `𝙵𝟷  ·  Fog Color`
- Description: Determines the value used for the sky atmosphere component's Height Fog Contribution.

### `Solar Eclipse Circle Mask`

- Access: `Protected`
- Flags: —
- Inputs: `(real<double> Sun Angular Diameter, real<double> Moon Angular Diameter, struct<Vector> Moon Vector)`
- Outputs: `(real<double> Fraction Showing)`
- Local variables: _none_
- Nodes: 25
- Category: `𝙴𝟷  ·  Sun`
- Description: Calculates how much of the sun disk is covered by another circular object

### `Space Planet Parent MID`

- Access: `Protected`
- Flags: —
- Inputs: `(struct<UDS_Space_Planet> Planet)`
- Outputs: `(softobject<MaterialInterface> Out)`
- Local variables: _none_
- Nodes: 10
- Category: `𝙷𝟸  ·  Space Layer`
- Description: Selects the correct parent material for creating the dynamic material instance for a space layer planet/moon

### `Start Editor Tick Handler`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 21
- Category: `Editor`

### `Start Instant Exposure`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9
- Category: `𝙴𝟼  ·  Exposure`

### `Start Time Replication`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8
- Category: `Replication`

### `Start Up UDW If it Exists`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 17
- Category: `Weather Connection`
- Description: Runs on startup, to find a UDW actor and initialize it.

### `Starting Cloud Formation`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12
- Category: `𝙲𝟺  ·  Cloud Movement`
- Description: Sets the starting cloud formation, either 0 or randomized, depending on the setting Randomize Cloud Formation on Run.

### `Startup Sky`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 100
- Category: `Startup`
- Description: Starts the sky system. Runs both in construction script and begin play.

### `Static Clouds Current Dynamic Rotation`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 19
- Category: `𝙲𝟹  ·  Static Clouds`

### `Static Clouds Lighting Mask`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> XY Mask)`
- Local variables (2): `Local Lighting Vector`, `Light Blend Alpha`
- Nodes: 58
- Category: `𝙲𝟹  ·  Static Clouds`
- Description: The vector parameter used in the sky material for determining how much of each channel of the static clouds texture to use for shading.

### `Static Clouds Tint Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> Light, struct<LinearColor> Shadow)`
- Local variables (1): `Clouds Alpha`
- Nodes: 21
- Category: `𝙲𝟹  ·  Static Clouds`
- Description: Multiplied over the static cloud colors in the sky material.

### `Static Properties - 2D Dynamic Clouds`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 70
- Category: `𝙲𝟸  ·  2D Dynamic Clouds`
- Description: Applies properties for the 2d clouds which do not change with dynamics.

### `Static Properties - Aurora`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 109
- Category: `𝙷𝟺  ·  Aurora`
- Description: Applies properties for the aurora which do not change with dynamics.

### `Static Properties - Calendar`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Day Count`
- Nodes: 64
- Category: `Date And Time`

### `Static Properties - Cloud Movement`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `𝙲𝟺  ·  Cloud Movement`

### `Static Properties - Cloud Shadows`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 91
- Category: `𝙴𝟻  ·  Cloud Shadows`
- Description: Applies properties for the cloud shadows which do not change with dynamics.

### `Static Properties - Exposure`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 24
- Category: `𝙴𝟼  ·  Exposure`

### `Static Properties - General Cvars`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 16
- Category: `Static Properties`

### `Static Properties - Global Volumetric Fog`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 76
- Category: `𝙵𝟹  ·  Volumetric Fog`
- Description: Creates the material instance and sets its parameters, for the Global Volumetric Fog Material

### `Static Properties - Height Fog`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 20
- Category: `𝙵𝟷  ·  Fog Color`
- Description: Applies properties for the fog which do not change with dynamics.

### `Static Properties - Inside Cloud Fog`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Inside Cloud Fog Active`
- Nodes: 40
- Category: `𝙵𝟹  ·  Volumetric Fog`

### `Static Properties - Lens Flare`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 27
- Category: `𝙸𝟸  ·  Lens Flare`
- Description: Applies properties for the lens flare which do not change with dynamics.

### `Static Properties - Mode Derivatives`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 51
- Category: `Static Properties`

### `Static Properties - Moon`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 58
- Category: `𝙴𝟸  ·  Moon`
- Description: Applies properties for the moon which do not change with dynamics.

### `Static Properties - Occlusion`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `𝙽𝟸  ·  Player Occlusion`

### `Static Properties - Path Tracer`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 44
- Category: `Path Tracer`

### `Static Properties - Post Process Components`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (3): `Post Component`, `Array Element`, `Array Index`
- Nodes: 48
- Category: `𝙸𝟹  ·  Post Processing`
- Description: Creates the components based on the exposed Post Processing Components array.

### `Static Properties - Simplified Color`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 16
- Category: `𝙶𝟸  ·  Simplified Color`
- Description: Applies properties for simplified color which do not change with dynamics.

### `Static Properties - Sky Atmosphere`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11
- Category: `𝙶𝟷  ·  Sky Atmosphere`
- Description: Applies properties for the sky atmosphere which do not change with dynamics.

### `Static Properties - Sky Light`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 66
- Category: `𝙴𝟹  ·  Sky Light`
- Description: Applies properties for the sky light which do not change with dynamics.

### `Static Properties - Sky Sphere and Material`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 24
- Category: `Sky Material`
- Description: Makes the dynamic material instance for the sky material and sets visibillity of the sky sphere mesh

### `Static Properties - Space Layer`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (15): `Current Planet`, `Current Sphere`, `Current Root`, `Current MID`, `Current Index`, `Ring Front`, `Ring Back`, `Planet Distance`, `Current Glow Mesh`, `Current Glow MID`, `Ring MID`, `Ring Front Mesh`, `Ring Back Mesh`, `Ring Rotation`, `Ring Scale`
- Nodes: 495
- Category: `𝙷𝟸  ·  Space Layer`
- Description: Creates the objects specified in the arrays in the Space Layer category. This can be called at runtime if you need to refresh the sky with changes to those arrays.

### `Static Properties - Stars`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 47
- Category: `𝙷𝟷  ·  Stars`
- Description: Applies properties for the stars which do not change with dynamics.

### `Static Properties - Static Clouds`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 22
- Category: `𝙲𝟹  ·  Static Clouds`
- Description: Applies properties for the static clouds which do not change with dynamics.

### `Static Properties - Sun`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 37
- Category: `𝙴𝟷  ·  Sun`
- Description: Applies properties for the sun which do not change with dynamics.

### `Static Properties - Volumetric Cloud Light Rays`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 79
- Category: `𝙺𝟷  ·  Volumetric Cloud Light Rays`
- Description: Applies properties for volumetric clouds light rays which do not change with dynamics.

### `Static Properties - Volumetric Clouds`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `All Volumetric Cloud MIDs`
- Nodes: 258
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: Applies properties for volumetric clouds which do not change with dynamics.

### `Static Properties - Water Caustics`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `MIDs to Configure`
- Nodes: 36
- Category: `𝙹𝟷  ·  Water`
- Description: Applies properties for the water caustics which do not change with dynamics.

### `Sun Disk Reflection Intensity`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 6
- Category: `𝙴𝟷  ·  Sun`

### `Sun Height`

- Access: `Protected`
- Flags: —
- Inputs: `(bool Cached = true)`
- Outputs: `(real<double> Z)`
- Local variables: _none_
- Nodes: 9
- Category: `𝙴𝟷  ·  Sun`
- Description: Turns the cached Sun Vector into a float from 0 to 1, where 0 is pointing straight up and 1 is pointing straight down. Most of the curves as formatted this way, so this function is used for their Time input.

### `Sun Light Volumetric Scattering Intensity`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 7
- Category: `𝙴𝟷  ·  Sun`

### `Sun Z Vector`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> out)`
- Local variables: _none_
- Nodes: 16
- Category: `𝙴𝟷  ·  Sun`
- Description: Finds a good Z vector, for turning the X vector into a rotator

### `Swap with Cinematic Runtime Value`

- Access: `Protected`
- Flags: —
- Inputs: `(real<double> In, real<double> Cine, bool Use Higher = true)`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 12
- Category: `𝙼𝟷  ·  Cinematics / Offline Rendering`
- Description: If project mode is Cinematic, changes out a value at runtime. Used to modify things like volumetric cloud quality while rendering.

### `Test Point for Painted Cloud Coverage`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Location)`
- Outputs: `(real<double> Cloud Coverage with Painting, real<double> Cloud Coverage with Painting)`
- Local variables (2): `Resulting Coverage`, `Filtered Color`
- Nodes: 17
- Category: `𝙺𝟸  ·  Volumetric Cloud Painting`
- Description: Given a location, checks the painted cloud coverage cells to see what the cloud coverage is at that point, as affected by the painted target.

### `Three Time Floats`

- Access: `Protected`
- Flags: —
- Inputs: `(real<double> Day, real<double> Dawn/Dusk, real<double> Night, bool Cached)`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 11
- Category: `Time`
- Description: Blends a value for Day, Dawn/Dusk, and Night.

### `Tick Occlusion`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `𝙽𝟸  ·  Player Occlusion`

### `Tick Time Transition`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `New Time of Day`
- Nodes: 51
- Category: `Time Transition`
- Description: Uses the transition timer to set Time of Day and increment the day as needed, when using Transition Time of Day.

### `Time of Day Animation`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10
- Category: `Time`
- Description: Increments time forward with the current speed from Animate Time of Day.

### `Time of Day Offset`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Per Second, real<double> Per Second)`
- Local variables: _none_
- Nodes: 39
- Category: `Time`
- Description: Used to offset Time of Day forward every frame, when Animate Time of Day is true.

### `Time Of Day to H/M/S`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Time)`
- Outputs: `(int Hour, int Minute, int Second, real<double> Second Fraction)`
- Local variables: _none_
- Nodes: 12
- Category: `Time`
- Description: Converts a 0-2400 Time of Day value to hours/minutes/seconds

### `Total Time Elapsed`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 9
- Category: `Time`
- Description: Outputs the total amount of UDS time which has passed since the game started running.

### `Transition Sky Light Intensity`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> New Sky Light Intensity Multiplier = 1.000000, real<double> Transition Time = 5.000000)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6
- Category: `𝙴𝟹  ·  Sky Light`
- Description: Can be used to transition the sky light's intensity, as a simple solution for changing the ambient light level, usually with a movable sky light. For example, you could run this function when walking into a cave, to have the ambient light level smoothly dim down over a few seconds. Then run this function again to bring the ambient light level back to normal upon leaving the cave.

### `Transition Time of Day`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> New Time of Day = 1200.000000, real<double> Transition Duration (Seconds) = 10.000000, byte Easing Function = EaseInOut, real<double> Easing Exponent = 2.000000, bool Allow Time Going Backwards)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 31
- Category: `Time`
- Description: Call this function to transition over to a specific time of day (from the current time of day). The duration and easing of the transition is customizable.

### `Twilight Brightness Falloff`

- Access: `Protected`
- Flags: —
- Inputs: `(real<double> Z)`
- Outputs: `(real<double> Scale)`
- Local variables: _none_
- Nodes: 4
- Category: `𝙵𝟷  ·  Fog Color`
- Description: Calculates how sun and moon fog colors should drop off after going below the horizon.

### `UDS Date Equal`

- Access: `Protected`
- Flags: —
- Inputs: `(struct<UDS_DateAndTime> Date A, struct<UDS_DateAndTime> Date B)`
- Outputs: `(bool Equal)`
- Local variables: _none_
- Nodes: 8
- Category: `Date and Time`

### `UDW Destroyed`

- Access: `Public`
- Flags: —
- Inputs: `(object<Actor> DestroyedActor)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6
- Category: `Weather Connection`

### `Unbind All Active Property Functions`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15
- Category: `Cache`

### `Unfiltered Moon Light Intensity`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables (1): `Base Intensity`
- Nodes: 29
- Category: `𝙴𝟸  ·  Moon`
- Description: Moon Light Intensity without directional balance or scattering 

### `Update Active Variables`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Steps`
- Nodes: 54
- Category: `Update Sky`
- Description: Updates all the parameters which the system expects to need to update at runtime. Things that change with time or cloud coverage or fog, like the position of the sun disk in the sky material, or the current color of the fog.

### `Update Atlas Light Vectors`

- Access: `Protected`
- Flags: —
- Inputs: `(struct<Rotator> Rotation)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 16
- Category: `𝙴𝟻  ·  Cloud Shadows`
- Description: Updates the vectors describing the full rotation of the light being used for cloud shadows, for the light function atlas to use.

### `Update Atlas Position`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `New Position`
- Nodes: 23
- Category: `𝙴𝟻  ·  Cloud Shadows`
- Description: Updates the position of the sun parent and moon parent. This is to control the center location of the light function, for the light function atlas support.

### `Update Cloud Coverage Material Parameters`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 23
- Category: `Update Sky`

### `Update Cloud Movement`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `Cached Movement Alpha`, `Time Based Phase`
- Nodes: 59
- Category: `𝙲𝟺  ·  Cloud Movement`
- Description: Updates the position and phase of the clouds, with their current movement.

### `Update Common Derivatives`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 18
- Category: `Update Sky`
- Description: Updates variables which are derived from dynamic values. To save having to calculate them multiple times later in the update process.

### `Update Dynamic Sky Light Multiplier`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 20
- Category: `𝙴𝟹  ·  Sky Light`
- Description: Updates the multiplier used by Transition Sky Light Intensity

### `Update Lunar Phase`

- Access: `Protected`
- Flags: —
- Inputs: `(int Hour)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6
- Category: `𝙴𝟸  ·  Moon`
- Description: If enabled, increments the Moon Phase value with time that has passed.

### `Update Modifier Post Processing`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (3): `Modifier`, `Post Component`, `Index`
- Nodes: 35
- Category: `𝙻𝟷  ·  Sky Modifiers`

### `Update Painted Cloud Coverage Target`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (4): `Draw Canvas`, `Draw Context`, `Storm Location`, `Current RT Mapping`
- Nodes: 91
- Category: `𝙺𝟸  ·  Volumetric Cloud Painting`
- Description: Draws the render target, if needed, for painted volumetric cloud coverage.

### `Update Path Tracer Fog`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 55
- Category: `Path Tracer`

### `Update Replicated Modifier State`

- Access: `Protected`
- Flags: —
- Inputs: `(bool Hard Reset on Apply)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11
- Category: `𝙻𝟷  ·  Sky Modifiers`

### `Update Replicated Time`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Replication`
- Description: For the server, updates the replicated time values, for the clients to recieve and use to increment time until the next update.

### `Update Settings Based on Scalability`

- Access: `Protected`
- Flags: —
- Inputs: `(bool Reconstruct if Needed)`
- Outputs: `()`
- Local variables (3): `Effects Quality`, `Reconstruct`, `Previous Run Context`
- Nodes: 50
- Category: `𝙼𝟸  ·  Scalability / Performance`
- Description: Runs on startup. Checks scalability settings and changes settings as determined by the exposed settings.

### `Update Sky Atmosphere Location`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Location)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12
- Category: `𝙶𝟷  ·  Sky Atmosphere`

### `Update Static Variables`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 38
- Category: `Update Sky`
- Description: Updates all of the parameters which the system expects to only need to be set once at launch. This function updates ALL static properties. If you need to refresh specific static properties at runtime, the more efficient option is to call one of the specific "Static Properties" functions for the group you need to update.

### `Update Total Days Elapsed`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `Start Day Count`, `Current Day Count`
- Nodes: 14
- Category: `Date And Time`

### `Volumetric Cloud Ambient Light Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> Bottom, struct<LinearColor> Top)`
- Local variables (3): `Color`, `Bottom Intensity`, `Top Intensity`
- Nodes: 103
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: The ambient light color, used as part of the emissive color parameters for the volumetric cloud material

### `Volumetric Cloud Base Cloud Height`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Base Cloud Height)`
- Local variables: _none_
- Nodes: 5
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: Determines the current height of the cloud layer, as scaled by cloud coverage (the layer is thinner with lower cloud coverage)

### `Volumetric Cloud First Layer Top Altitude`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Cloud Top Altitude)`
- Local variables: _none_
- Nodes: 14
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: Determines the world height of the top of the current cloud layer. Used by the cloud fog post process to approximate the cloud layer.

### `Volumetric Cloud Floor Variation`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Height Clear, real<double> Height Cloudy, real<double> Color)`
- Local variables (2): `Height Multiplier`, `Color Luminance Variation`
- Nodes: 34
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: Scales the floor variation values on the volumetric cloud material with cloud coverage.

### `Volumetric Cloud Layer Height`

- Access: `Protected`
- Flags: —
- Inputs: `(real<double> Base Cloud Height)`
- Outputs: `(real<double> Layer Height)`
- Local variables: _none_
- Nodes: 9
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: The actual applied cloud component layer height, factoring both layers if using Two Layers.

### `Volumetric Cloud Layer Scale`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Layer Scale)`
- Local variables: _none_
- Nodes: 13
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: Used in the volumetric cloud material to scale the normalized altitude range, to support Two Layers.

### `Volumetric Cloud Phase Blend`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 4
- Category: `𝙲𝟷  ·  Volumetric Clouds`

### `Volumetric Cloud Simplified Material Switch`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 16
- Category: `𝙲𝟷  ·  Volumetric Clouds`

### `Volumetric Clouds Parent Materials`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(softobject<MaterialInterface> Simplified, softobject<MaterialInterface> Complex)`
- Local variables: _none_
- Nodes: 9
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: The parent materials used to make the Volumetric Cloud dynamic material instances. There's a Simplified and a Complex material, utilized by the feature which shifts to a simplified version when the sky is heavily overcast.

### `Volumetric Clouds SubNoise Scales`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> High, struct<LinearColor> Low)`
- Local variables: _none_
- Nodes: 12
- Category: `𝙲𝟷  ·  Volumetric Clouds`
- Description: Scales the 3D Noise samples in the volumetric cloud material. The scale is different based on global material quality level, because of the difference in the 3D noise resolution.

### `Volumetric Light Ray Strength and Color`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<LinearColor> Ray Color)`
- Local variables (3): `Light Ray Vector`, `Strength`, `Color`
- Nodes: 54
- Category: `𝙺𝟷  ·  Volumetric Cloud Light Rays`

### `📘 Aurora`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙷𝟺  ·  Aurora`

### `📘 Cinematic / Offline Rendering`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `𝙼𝟷  ·  Cinematics / Offline Rendering`

### `📘 Cloud Movement`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙲𝟺  ·  Cloud Movement`

### `📘 Cloud Shadows`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙴𝟻  ·  Cloud Shadows`

### `📘 Cloud Wisps`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙲𝟻  ·  Cloud Wisps`

### `📘 Configuring for Performance`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙼𝟸  ·  Scalability / Performance`

### `📘 Considerations for Mobile`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙾𝟷  ·  Mobile`

### `📘 Directional Light`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `𝙴𝟺  ·  Directional Light`

### `📘 Dust`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙵𝟺  ·  Dust`

### `📘 Exposure`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙴𝟼  ·  Exposure`

### `📘 Fog Color`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙵𝟷  ·  Fog Color`

### `📘 Fog Density`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙵𝟸  ·  Fog Density`

### `📘 Interior Adjustments`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙽𝟷  ·  Interior Adjustments`

### `📘 Moon`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `𝙴𝟸  ·  Moon`

### `📘 Player Occlusion`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙽𝟸  ·  Player Occlusion`

### `📘 Post Processing`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙸𝟹  ·  Post Processing`

### `📘 Screen Space Light Shafts`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙸𝟷  ·  Screen Space Light Shafts`

### `📘 Simplified Color`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙶𝟸  ·  Simplified Color`

### `📘 Simulation`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `𝙳𝟷  ·  Simulation`

### `📘 Sky Atmosphere`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙶𝟷  ·  Sky Atmosphere`

### `📘 Sky Glow`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙷𝟹  ·  Sky Glow`

### `📘 Sky Light`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙴𝟹  ·  Sky Light`

### `📘 Sky Modifiers`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙻𝟷  ·  Sky Modifiers`

### `📘 Space Layer`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙷𝟸  ·  Space Layer`

### `📘 Stars`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙷𝟷  ·  Stars`

### `📘 Sun`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `𝙴𝟷  ·  Sun`

### `📘 Sun Lens Flare`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙸𝟸  ·  Lens Flare`

### `📘 UDS Documentation`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙰𝟷  ·  Basic Controls`

### `📘 Underwater Caustics`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙹𝟷  ·  Water`

### `📘 Volumetric Cloud Light Rays`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙺𝟷  ·  Volumetric Cloud Light Rays`

### `📘 Volumetric Cloud Painting`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙺𝟸  ·  Volumetric Cloud Painting`

### `📘 Volumetric Fog`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙵𝟹  ·  Volumetric Fog`

### `📘2D Dynamic Clouds`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙲𝟸  ·  2D Dynamic Clouds`

### `📘Static Clouds`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙲𝟹  ·  Static Clouds`

### `📘Time of Day`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `𝙱𝟷  ·  Animate Time Of Day`

### `📘Volumetric Clouds`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `𝙲𝟷  ·  Volumetric Clouds`

## Macros (12)

### `Modifier Color Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 46

### `Modifier Float Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 127

### `Runtime Config Bool Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 89

### `Runtime Config Byte Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 20

### `Runtime Config Color Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 57

### `Runtime Config Float Range Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

### `Runtime Config Float Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 312

### `Runtime Config Hard Object Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 19

### `Runtime Config Integer Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 26

### `Runtime Config Soft Object Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 21

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
- Nodes: 4

## Components (5)

- `SkyRoot` — `SceneComponent` @ socket `None`
  - `ClockDisk` — `StaticMeshComponent` @ socket `None`
  - `HeightFog` — `ExponentialHeightFogComponent` @ socket `None`
  - `SkyAtmosphere` — `SkyAtmosphereComponent` @ socket `None`
  - `Sky_Sphere` — `StaticMeshComponent` @ socket `None`
  - `Cubemap Sky Light` — `SkyLightComponent` @ socket `None`
  - `VolumetricCloud` — `VolumetricCloudComponent` @ socket `None`
  - `Captured Scene Sky Light` — `SkyLightComponent` @ socket `None`
  - `UDS Label` — `StaticMeshComponent` @ socket `None`
  - `Compass` — `StaticMeshComponent` @ socket `None`
    - `W` — `StaticMeshComponent` @ socket `None`
    - `N` — `StaticMeshComponent` @ socket `None`
    - `E` — `StaticMeshComponent` @ socket `None`
    - `S` — `StaticMeshComponent` @ socket `None`
  - `Sun Handle` — `StaticMeshComponent` @ socket `None`
  - `Moon Handle` — `StaticMeshComponent` @ socket `None`
  - `Sun Parent` — `SceneComponent` @ socket `None`
    - `Sun` — `DirectionalLightComponent` @ socket `None`
  - `Moon Parent` — `SceneComponent` @ socket `None`
    - `Moon` — `DirectionalLightComponent` @ socket `None`
- `UDS_Utility_Opener` — `UDS_Utility_Opener_C` @ socket `None`
- `UDS_Editor_Tick_Handler` — `UDS_Editor_Tick_Handler_C` @ socket `None`
- `Cloud Paint Actors Manager` — `UDS_InterfaceActorArrayManager_C` @ socket `None`
- `UDS_PlayerOcclusion` — `UDS_PlayerOcclusion_C` @ socket `None`

## Class Default Object (9)

- `ActorLabel` (`FString`) = `Ultra_Dynamic_Sky_BP-1`
- `bAlwaysRelevant` (`uint8`) = `True`
- `bCanBeDamaged` (`uint8`) = `False`
- `bEnableAutoLODGeneration` (`uint8`) = `False`
- `bIsSpatiallyLoaded` (`uint8`) = `False`
- `bRelevantForLevelBounds` (`uint8`) = `False`
- `bReplicates` (`uint8`) = `True`
- `NetUpdateFrequency` (`float`) = `60.000000`
- `PrimaryActorTick` (`FActorTickFunction`) = `(TickGroup=TG_DuringPhysics,bCanEverTick=True)`

## Graphs

- Event graph: `EventGraph` (99 nodes)
- Construction script: `UserConstructionScript` (6 nodes)
- Additional graphs: _none_

## References

Hard refs out (176):
- `/Engine/BasicShapes/Cube` [asset]
- `/Engine/EditorBlueprintResources/ActorMacros` [asset]
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Engine/EditorResources/LightIcons/S_LightError` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_CachedProperties` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_CityPresets` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_ColorMode` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_ComparisonType` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_FogColorMode` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_LensFlareType` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Modifier_Color_Property` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Modifier_Float_Property` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Occlusion_Mode` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_OcclusionSamplingLocation` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_PathTracerSkyRes` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Planet_Lightsource` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Project_Mode` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_PropertyUpdateGroup` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_RenderingFeatureLevel` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_RunContext` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_SkyLightMode` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_SkyMode` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Space_Parent` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_VolRT_Mode` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Calendars/Gregorian_Calendar` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/Editor_Materials/Editor_Moon_Glow` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/Editor_Materials/Editor_MoonHandle_Material` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/Editor_Materials/Editor_Sun_Glow` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/Editor_Materials/Editor_SunHandle_Material` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/Editor_Materials/UDS_Clock_Material` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/Editor_Materials/UDS_Compass_Material` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/Editor_Materials/UDS_Compass_Material_Letters` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/Editor_Materials/UDS_EditorLabel` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_CurrentVersion` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Editor_Tick_Handler` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Editor_Tick_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_VersionInfo` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/RandomWeatherVariation_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_and_UDW_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Calendar` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_CloudPaintActor_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_DateAndTime` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_DispatcherTunnel` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_DispatcherTunnelObject` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_DST_Preset` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArrayManager` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArrayOwner_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Modifier` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Modifier_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_ModifierState` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Planet_Preset` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Post_Process_Stage` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_SharedConfig` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Sky_Configuration` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Space_Planet` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_TimeOfDay_FadeRange` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WeatherState_Structure` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Cloud_Fog_PostProcess` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Color_Curves/Fog_Directional_Scattering_Color` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Color_Curves/Fog_Scattering_Color` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Color_Curves/Sun_Disk_Color` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Color_Curves/Sun_Light_Color` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Float_Curves/Directional_Light_Intensity` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Float_Curves/Equation_of_Time` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Float_Curves/Exposure_Compensation_Curve` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Float_Curves/Exposure_Compensation_Curve_Physical` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Float_Curves/Shine_Intensity` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Float_Curves/Skyatmosphere_Density` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Float_Curves/Sun_Highlight_Intensity` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Float_Curves/Sun_Highlight_Radius` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Global_Volumetric_Fog` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Inside_Clouds_Fog_Particle` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Functions/UDS_VolumetricClouds_MPC` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/Global_Volumetric_Fog_C` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/Global_Volumetric_Fog_GFC` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/Global_Volumetric_Fog_w_Ground_Fog` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/Lens_Flares/35mm_Prime` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/Lens_Flares/Anamorphic` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/Lens_Flares/Zoom_Chromatic` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/Light_Functions/LF_2DCloud_Shadows` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/Light_Functions/LF_2DCloud_Shadows_Caustics` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/Light_Functions/LF_Basic` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/Light_Functions/LF_CausticsOnly` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/Light_Functions/LF_VolCloud_Shadows` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/Light_Functions/LF_VolCloud_Shadows_Caustics` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_A` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_AD` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_ADO` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_AS` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_B` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_C` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_CA` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_CAD` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_CADO` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_CAS` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_CD` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_CDO` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_CS` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_D` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_DO` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_K` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KA` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KAD` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KADO` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KAS` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KC` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KCA` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KCAD` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KCADO` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KCAS` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KCD` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KCDO` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KCS` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KD` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KDO` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_KS` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_P` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_PC` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/UDS_S` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/Volumetric_Clouds_2L` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/Volumetric_Clouds_2L_S` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/Volumetric_Clouds_default` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Material_Instances/Volumetric_Clouds_default_S` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/PathTracer_ExpHeightFog` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Space/Instances/Space_Planet_A` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Space/Instances/Space_Planet_Default` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Space/Instances/Space_Planet_N` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Space/Instances/Space_Planet_NA` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Space/Nebula_Layer` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Space/Space_Planet_Glow_Mat` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Space/Space_Ring_Mat` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Volumetric_Aurora` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Radial_Storm_Cloud_Draw` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/UltraDynamicWeather_Parameters` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/Compass` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/EditorLabels/ClockDisk` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/EditorLabels/Compass_E` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/EditorLabels/Compass_N` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/EditorLabels/Compass_S` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/EditorLabels/Compass_W` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/EditorLabels/Editor_SunMoon_Handle` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/EditorLabels/UDS_Text` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/Nebula_Sphere` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/Space_Glow_Circle` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/Space_Planet` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/Space_Ring_BackHalf` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/Space_Ring_FrontHalf` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/Ultra_Dynamic_Sky_Sphere` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Particles/VolumetricCloud_LightRays` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/3D_Clouds/3D_Cells_32` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/3D_Clouds/3D_Cells_64` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/3D_Clouds/3DCells_128` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/3D_Clouds/FormationVolume` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Clouds/Aurora_Clouds` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Clouds/clouds_diverse` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Clouds/CloudsTurbulence` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/Cloud_Wisps` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/CloudPaintTarget` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/FlatCubemap` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/Moon_Atmosphere_LUT_Volume` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/Moon_Color` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/Moon_PhaseNormal` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/Real_Stars` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/Static_Overcast` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/Sun_Atmosphere_LUT_Volume` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Sky/Tiling_Stars` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/StaticClouds/StaticClouds_A` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Volumetric_Clouds/Cloud_Profile` [asset]
- `/Script/Engine.Actor` [native]
- `/Script/Niagara` [asset]
- `/Script/PhysicsCore` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

