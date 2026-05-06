# UDS_Space_Planet

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Space_Planet.UDS_Space_Planet` |
| Asset name | `UDS_Space_Planet` |
| Asset type | `UserDefinedStruct` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |

## Fields (40)

| Name | Type | Category | ToolTip |
|---|---|---|---|
| `Parent_2_0E1A37CE4AF01519A9BCE6ACA2CD1137` | `TEnumAsByte<UDS_Space_Parent>` | — | Determines if this space object will move with the sun, moon, or not move. |
| `RelativeRotation_5_6AB46E784AAA14769695A882EB23223E` | `FRotator` | — | The rotation of the object, relative to the actor if it has no parent, or relative to the sun or moon if parented to those. |
| `Scale_9_D8C257DF48AA1AA6FF92B0BADA269EDB` | `double` | — | The visual size of the planet/moon |
| `ColorTexture_30_2BBB70D24D2BDD9AD355609B4FF9B21B` | `TSoftObjectPtr<UTexture2D>` | — | The texture used for the color. Should be flat/unshaded. |
| `ColorTextureTint_123_F088C5B64DFD1D20EEC23CBC27966B9C` | `FLinearColor` | — | Tints the color texture overall |
| `NormalMap_33_A9266AE648B84654F7C9B9849CFA3E7C` | `TSoftObjectPtr<UTexture2D>` | — | Normal map for adding detail to shading from the sun |
| `NormalMapStrength_36_6F822CA84FCDEF589CED9595F668D77A` | `double` | — | The strength of the normal map's effect on the shading. |
| `DarkSideTint_40_83860D2D4EEEF7086AB3AFB09CF1DCCC` | `FLinearColor` | — | The color multiplied over the dark side of the planet. Can be set to white to make an object that doesn't visibly have shading. |
| `LightSideTint_42_0EF08CD645E27CABBE7DBD8E7471F04B` | `FLinearColor` | — | The color multiplied over the light side of the planet. Would typically be white, but can be used to tint the light side as needed. |
| `TerminatorThickness_58_E6DC59F2417BA23BB1BAA5BF464BF621` | `double` | — | Multiplied over the shading gradient, to control how wide/tight the terminator (the border between the light and dark side) is. |
| `TerminatorPower_60_249814CB4B2F0A60E458FEA89132D36E` | `double` | — | An exponent for the shading gradient, to control the curve of falloff from light to dark. |
| `TerminatorOffset_62_E26446874807C179E62DC3A3D511938F` | `double` | — | An offset for the shading gradient, to have more or less of the sphere be lit. |
| `TerminatorTint_44_8A6F729743E618D4CBE093BDCA99CD01` | `FLinearColor` | — | A tint color applied in the middle of the terminator. Useful for planets with atmospheres like Earth, to imitate the way light filters warm along the terminator. |
| `LightVector_105_71AFA5654C1A2915EF2F6F9636985F79` | `TEnumAsByte<UDS_Planet_Lightsource>` | — | Choose the angle that the material will appear lit from. The sun, the moon, or the custom vector (adjustable below) |
| `CustomLightVector_108_A1E02E374DF47067FFF4BB83AD035BC4` | `FVector` | — | If the Light Vector setting is Custom, this vector will be used for the direction light shades this planet. |
| `Glow_116_6BBE205A4CB7B5A1555103A09A90E0F7` | `double` | — | Glow around the planet/moon, like light scattering through the local atmosphere |
| `GlowColor_117_D644808A49C9F262468CD988D1087F09` | `FLinearColor` | — | Tints the color of the glow added by the above setting |
| `GlowScale_120_20ADA5B346CD968A0904D284F1D968B0` | `double` | — | Scales the glow sprite relative to the planet/moon scale |
| `RenderAtmosphere_47_8FA38C394C66F95149E4269D6A13E9DE` | `bool` | — | If true, atmosphere color and a ring of atmosphere "glow" will encircle the planet. |
| `AtmosphereStrength_50_0D33B16248764FF3CEBC98B70F026998` | `double` | — | The opacity of the atmosphere color and glow |
| `AtmosphereThickness_52_0C2D526D4C6E998A929F2D9A2B3FE30B` | `double` | — | The size of the atmosphere's "ring" around the planet's sphere. |
| `AtmosphereColor_55_39F94C30482BE08919CDB1BE025A7DC8` | `FLinearColor` | — | The color of the atmosphere, applied if Render Atmosphere is true. |
| `EmissiveTexture_66_5312AAA94E7A901D5F46D6AC848F943F` | `TSoftObjectPtr<UTexture2D>` | — | An emissive color texture or grayscale mask. One possible use is for city lights visible on the night side of a planet. |
| `EmissiveLightSideTint_73_969799654B9C1754BDE425B229EA063E` | `FLinearColor` | — | Tints the emissive texture on the lit side of the planet |
| `EmissiveDarkSideTint_74_EBFDD1104CC20ADAE943EC913D1977B2` | `FLinearColor` | — | Tints the emissive texture on the dark side of the planet |
| `RenderRing_78_1DDEF5604EC914832AB31CA1327D2947` | `bool` | — | Render planetary rings around the sphere |
| `RingPitch_80_56F5E8E14589B8624F3C7B9951D4C8D1` | `double` | — | The pitch of the ring's rotation |
| `RingRoll_82_091721764596A286D8F56C92EFB17435` | `double` | — | The roll of the ring's rotation |
| `RingDistance_84_8E87B9394476970597D7A8B81A055C39` | `double` | — | The innter distance of the ring, from the planet surface. |
| `RingWidth_86_324627CE43F44BEFA03D019FC1E0FF8F` | `double` | — | The thickness of the ring |
| `RingTexture_92_B962AC934EE0E4617A29BE9F710F32EF` | `TSoftObjectPtr<UTexture2D>` | — | The texture used for the ring. Only sampled on X axis, so should be 1 pixel tall. RGB contains color and A is used for opacity. |
| `RingTintColor_95_4F6B04E54C74C020B0C009971EB24538` | `FLinearColor` | — | Tint the color of the ring. Multiplied over the color from the Ring Texture. |
| `RingOpacity_98_6F398376468F51CF8289D9AA39638D49` | `double` | — | Scales the alpha channel of the ring texture |
| `RingShadowBrightness_100_82A5108141E68184387C0CBDA39F37D6` | `double` | — | Sets how much the planet's shadow darkens the ring. |
| `RingShadowSoftness_102_B53027E540B8F2E6C7744D90958C1B85` | `double` | — | Larger values will make the planet's shadow on the ring softer. |
| `RingAroundLocalPlanet_137_C88F416041C533DC98C9EA8F7D68CBD7` | `bool` | — | This is for if you want to use this planet/moon to render a ring around the local planet (the planet you're on). When this is true, only the ring decal will be rendered, centered around the local planet. |
| `MeshDeformTexture_126_B7DC215A433430E4AD89459B331BC0CE` | `TSoftObjectPtr<UTexture2D>` | — | Alpha texture used to deform the surface along the vertex normal (for irregularly shaped moons, asteroids) |
| `MeshDeformStrength_129_CBDEB487415F39784E41DBB95BE8F4B1` | `double` | — | Amount to deform the mesh along the vertex normal, relative to the size of the object. |
| `MeshDeformCenterLevel_135_D94322934BFA5C635C0D2BA54E37A086` | `double` | — | Defines the level of brightness in the mesh deform texture which is unmoved by the deformation. |
| `MeshDeformTextureOffset_132_F11E46C5458E2C4E5B3ABB8E3C2E6B45` | `FVector` | — | The first two channels offset the mesh deform texture in X and Y space. The third scales the texture. |

