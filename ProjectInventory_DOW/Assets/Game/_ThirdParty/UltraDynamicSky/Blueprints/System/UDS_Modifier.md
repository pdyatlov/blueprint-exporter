# UDS_Modifier

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Modifier.UDS_Modifier` |
| Asset name | `UDS_Modifier` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `PrimaryDataAsset` (`/Script/Engine.PrimaryDataAsset`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (12)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Float Property Overrides` | `TMap<byte<UDS_Modifier_Float_Property,>>, ?>` | `()` | `Default` | — | — | InstanceEditable |
| `Color Property Overrides` | `TMap<byte<LinearColor>>, :/Script/CoreUObject.LinearColor>` | `()` | `Default` | — | — | InstanceEditable |
| `Easing Function` | `byte<EEasingFunc>` | `EaseInOut` | `Easing and Alpha` | — | — | InstanceEditable |
| `Easing Blend Exponent` | `real<double>` | `2.000000` | `Easing and Alpha` | — | — | InstanceEditable |
| `Max Alpha` | `real<double>` | `1.000000` | `Easing and Alpha` | — | — | InstanceEditable |
| `Float Property Keys` | `TArray<byte<UDS_Modifier_Float_Property>>` | — | `Arrays` | — | — | InstanceEditable, Private |
| `Float Property Values` | `TArray<real<double>>` | — | `Arrays` | — | — | InstanceEditable, Private |
| `Color Property Keys` | `TArray<byte<UDS_Modifier_Color_Property>>` | — | `Arrays` | — | — | InstanceEditable, Private |
| `Color Property Values` | `TArray<struct<LinearColor>>` | — | `Arrays` | — | — | InstanceEditable, Private |
| `Apply Post Process Settings` | `bool` | `False` | `Post Processing` | — | — | InstanceEditable |
| `Post Process Settings` | `struct<PostProcessSettings>` | `(WhiteTemp=6500.000000,ColorSaturation=(X=1.000000,Y=1.000000,Z=1.000000,W=1.000000),ColorContrast=(X=1.000000,Y=1.000000,Z=1.000000,W=1.000000),ColorGamma=(X=1.000000,Y=1.000000,Z=1.000000,W=1.000000),ColorGain=(X=1.000000,Y=1.000000,Z=1.000000,W=1.000000),ColorOffset=(X=0.000000,Y=0.000000,Z=0.000000,W=0.000000),ColorSaturationShadows=(X=1.000000,Y=1.000000,Z=1.000000,W=1.000000),ColorContrastShadows=(X=1.000000,Y=1.000000,Z=1.000000,W=1.000000),ColorGammaShadows=(X=1.000000,Y=1.000000,Z=1.000000,W=1.000000),ColorGainShadows=(X=1.000000,Y=1.000000,Z=1.000000,W=1.000000),ColorOffsetShadows=(X=0.000000,Y=0.000000,Z=0.000000,W=0.000000),ColorSaturationMidtones=(X=1.000000,Y=1.000000,Z=1.000000,W=1.000000),ColorContrastMidtones=(X=1.000000,Y=1.000000,Z=1.000000,W=1.000000),ColorGammaMidtones=(X=1.000000,Y=1.000000,Z=1.000000,W=1.000000),ColorGainMidtones=(X=1.000000,Y=1.000000,Z=1.000000,W=1.000000),ColorOffsetMidtones=(X=0.000000,Y=0.000000,Z=0.000000,W=0.000000),ColorSaturationHighlights=(X=1.000000,Y=1.000000,Z=1.000000,W=1.000000),ColorContrastHighlights=(X=1.000000,Y=1.000000,Z=1.000000,W=1.000000),ColorGammaHighlights=(X=1.000000,Y=1.000000,Z=1.000000,W=1.000000),ColorGainHighlights=(X=1.000000,Y=1.000000,Z=1.000000,W=1.000000),ColorOffsetHighlights=(X=0.000000,Y=0.000000,Z=0.000000,W=0.000000),ColorCorrectionHighlightsMin=0.500000,ColorCorrectionHighlightsMax=1.000000,ColorCorrectionShadowsMax=0.090000,BlueCorrection=0.600000,ExpandGamut=1.000000,ToneCurveAmount=1.000000,FilmSlope=0.880000,FilmToe=0.550000,FilmShoulder=0.260000,FilmWhiteClip=0.040000,SceneColorTint=(R=1.000000,G=1.000000,B=1.000000,A=1.000000),BloomIntensity=0.675000,BloomGaussianIntensity=1.000000,BloomThreshold=-1.000000,BloomSizeScale=4.000000,Bloom1Size=0.300000,Bloom2Size=1.000000,Bloom3Size=2.000000,Bloom4Size=10.000000,Bloom5Size=30.000000,Bloom6Size=64.000000,Bloom1Tint=(R=0.346500,G=0.346500,B=0.346500,A=1.000000),Bloom2Tint=(R=0.138000,G=0.138000,B=0.138000,A=1.000000),Bloom3Tint=(R=0.117600,G=0.117600,B=0.117600,A=1.000000),Bloom4Tint=(R=0.066000,G=0.066000,B=0.066000,A=1.000000),Bloom5Tint=(R=0.066000,G=0.066000,B=0.066000,A=1.000000),Bloom6Tint=(R=0.061000,G=0.061000,B=0.061000,A=1.000000),BloomConvolutionIntensity=1.000000,BloomConvolutionScatterDispersion=1.000000,BloomConvolutionSize=1.000000,BloomConvolutionCenterUV=(X=0.500000,Y=0.500000),BloomConvolutionPreFilterMin=7.000000,BloomConvolutionPreFilterMax=15000.000000,BloomConvolutionPreFilterMult=15.000000,BloomConvolutionBufferScale=0.133000,BloomDirtMaskTint=(R=0.500000,G=0.500000,B=0.500000,A=1.000000),DynamicGlobalIlluminationMethod=Lumen,IndirectLightingColor=(R=1.000000,G=1.000000,B=1.000000,A=1.000000),IndirectLightingIntensity=1.000000,LumenSceneLightingQuality=1.000000,LumenSceneDetail=1.000000,LumenSceneViewDistance=20000.000000,LumenSceneLightingUpdateSpeed=1.000000,LumenFinalGatherQuality=1.000000,LumenFinalGatherLightingUpdateSpeed=1.000000,LumenFinalGatherScreenTraces=True,LumenMaxTraceDistance=20000.000000,LumenDiffuseColorBoost=1.000000,LumenSkylightLeakingTint=(R=1.000000,G=1.000000,B=1.000000,A=1.000000),LumenFullSkylightLeakingDistance=1000.000000,LumenSurfaceCacheResolution=1.000000,ReflectionMethod=Lumen,LumenReflectionQuality=1.000000,LumenReflectionsScreenTraces=True,LumenMaxRoughnessToTraceReflections=0.400000,LumenMaxReflectionBounces=1,ScreenSpaceReflectionIntensity=100.000000,ScreenSpaceReflectionQuality=50.000000,ScreenSpaceReflectionMaxRoughness=0.600000,bMegaLights=True,AmbientCubemapTint=(R=1.000000,G=1.000000,B=1.000000,A=1.000000),AmbientCubemapIntensity=1.000000,CameraShutterSpeed=60.000000,CameraISO=100.000000,DepthOfFieldFstop=4.000000,DepthOfFieldMinFstop=1.200000,DepthOfFieldBladeCount=5,AutoExposureBias=1.000000,AutoExposureApplyPhysicalCameraExposure=True,AutoExposureLowPercent=10.000000,AutoExposureHighPercent=90.000000,AutoExposureMinBrightness=-10.000000,AutoExposureMaxBrightness=20.000000,AutoExposureSpeedUp=3.000000,AutoExposureSpeedDown=1.000000,HistogramLogMin=-10.000000,HistogramLogMax=20.000000,LocalExposureHighlightContrastScale=1.000000,LocalExposureShadowContrastScale=1.000000,LocalExposureDetailStrength=1.000000,LocalExposureBlurredLuminanceBlend=0.600000,LocalExposureBlurredLuminanceKernelSizePercent=50.000000,LocalExposureHighlightThresholdStrength=1.000000,LocalExposureShadowThresholdStrength=1.000000,LensFlareIntensity=1.000000,LensFlareTint=(R=1.000000,G=1.000000,B=1.000000,A=1.000000),LensFlareBokehSize=3.000000,LensFlareThreshold=8.000000,LensFlareTints[0]=(R=1.000000,G=0.800000,B=0.400000,A=0.600000),LensFlareTints[1]=(R=1.000000,G=1.000000,B=0.600000,A=0.530000),LensFlareTints[2]=(R=0.800000,G=0.800000,B=1.000000,A=0.460000),LensFlareTints[3]=(R=0.500000,G=1.000000,B=0.400000,A=0.390000),LensFlareTints[4]=(R=0.500000,G=0.800000,B=1.000000,A=0.310000),LensFlareTints[5]=(R=0.900000,G=1.000000,B=0.800000,A=0.270000),LensFlareTints[6]=(R=1.000000,G=0.800000,B=0.400000,A=0.220000),LensFlareTints[7]=(R=0.900000,G=0.700000,B=0.700000,A=0.150000),VignetteIntensity=0.400000,FilmGrainIntensityShadows=1.000000,FilmGrainIntensityMidtones=1.000000,FilmGrainIntensityHighlights=1.000000,FilmGrainShadowsMax=0.090000,FilmGrainHighlightsMin=0.500000,FilmGrainHighlightsMax=1.000000,FilmGrainTexelSize=1.000000,AmbientOcclusionIntensity=0.500000,AmbientOcclusionStaticFraction=1.000000,AmbientOcclusionRadius=200.000000,AmbientOcclusionFadeDistance=8000.000000,AmbientOcclusionFadeRadius=5000.000000,AmbientOcclusionPower=2.000000,AmbientOcclusionBias=3.000000,AmbientOcclusionQuality=50.000000,AmbientOcclusionMipBlend=0.600000,AmbientOcclusionMipScale=1.700000,AmbientOcclusionMipThreshold=0.010000,AmbientOcclusionTemporalBlendWeight=0.100000,RayTracingAOSamplesPerPixel=1,RayTracingAOIntensity=1.000000,RayTracingAORadius=200.000000,ColorGradingIntensity=1.000000,DepthOfFieldSensorWidth=24.576000,DepthOfFieldSqueezeFactor=1.000000,DepthOfFieldDepthBlurAmount=1.000000,DepthOfFieldPetzvalBokehFalloff=1.000000,DepthOfFieldPetzvalExclusionBoxExtents=(X=0.000000,Y=0.000000),DepthOfFieldAspectRatioScalar=1.000000,DepthOfFieldBarrelRadius=5.000000,DepthOfFieldMatteBoxFlags[0]=(),DepthOfFieldMatteBoxFlags[1]=(),DepthOfFieldMatteBoxFlags[2]=(),DepthOfFieldNearTransitionRegion=300.000000,DepthOfFieldFarTransitionRegion=500.000000,DepthOfFieldNearBlurSize=15.000000,DepthOfFieldFarBlurSize=15.000000,DepthOfFieldOcclusion=0.400000,DepthOfFieldVignetteSize=200.000000,MotionBlurAmount=0.500000,MotionBlurMax=5.000000,MotionBlurTargetFPS=30,RayTracingTranslucencyMaxRoughness=0.600000,RayTracingTranslucencyRefractionRays=3,RayTracingTranslucencySamplesPerPixel=1,RayTracingTranslucencyMaxPrimaryHitEvents=4,RayTracingTranslucencyMaxSecondaryHitEvents=2,RayTracingTranslucencyShadows=Hard_shadows,RayTracingTranslucencyRefraction=True,PathTracingMaxBounces=32,PathTracingSamplesPerPixel=2048,PathTracingMaxPathIntensity=24.000000,PathTracingEnableEmissiveMaterials=True,PathTracingEnableDenoiser=True,PathTracingIncludeEmissive=True,PathTracingIncludeDiffuse=True,PathTracingIncludeIndirectDiffuse=True,PathTracingIncludeSpecular=True,PathTracingIncludeIndirectSpecular=True,PathTracingIncludeVolume=True,PathTracingIncludeIndirectVolume=True,WeightedBlendables=())` | `Post Processing` | — | — | InstanceEditable |
| `Post Process Priority` | `real<double>` | `2.000000` | `Post Processing` | — | — | InstanceEditable |

## Functions (1)

### `Parse Maps into Arrays`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 24
- Description: Makes arrays out of the property maps

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0) — DataAsset

_No authored overrides found on the CDO. `DataAsset` Blueprints typically author their payload here — if this BP is meant to differ from its parent class, this is a coverage gap._

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (4):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Modifier_Color_Property` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Modifier_Float_Property` [asset]
- `/Script/Engine.PrimaryDataAsset` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

