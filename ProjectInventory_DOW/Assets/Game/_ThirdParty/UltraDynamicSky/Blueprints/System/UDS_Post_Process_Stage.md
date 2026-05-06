# UDS_Post_Process_Stage

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Post_Process_Stage.UDS_Post_Process_Stage` |
| Asset name | `UDS_Post_Process_Stage` |
| Asset type | `UserDefinedStruct` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |

## Fields (19)

| Name | Type | Category | ToolTip |
|---|---|---|---|
| `Label_24_760DA3B649F655929138B7846A0B840F` | `FString` | — | Used to label this post process component in the array. Purely for organization to help you keep track of which entry is which. |
| `PostProcessSettings_25_E746F2674432B2790E7147B9B9D48686` | `FPostProcessSettings` | — | The post process settings this component will use. |
| `Priority_47_5B0BDA844B69DB2E7768168865CD16E0` | `double` | — | The priority of the post process component. Will determine the order they're applied relative to other components/post process volumes. |
| `DisableDuringDay_60_6A0C0A844D25727B201270B8E6794534` | `bool` | — | If checked, Blend Weight will be turned down when its daytime. |
| `DisableatDawnDusk_61_D0DA84F840D05C7DA0D7B49A2E6743C4` | `bool` | — | If checked, Blend Weight will be turned down when it's dawn/dusk. |
| `DisableatNight_62_1D5FD8DD4142C2B92FFCEFBE2A0E581F` | `bool` | — | If checked, Blend Weight will be turned down when it's night time. |
| `DisableifOvercast_52_989272994F5025F12C728292C335B969` | `bool` | — | If checked, Blend Weight will be turned down when the sky is overcast. |
| `DisableifNotOvercast_53_D95A77BB4DB1672F50FDC6B817C28515` | `bool` | — | If checked, Blend Weight will be turned down when the sky is mostly clear of clouds. |
| `DisableifFoggy_54_539D2C7E4D2FD2EB58A526993DBB4A10` | `bool` | — | If checked, Blend Weight will be turned down when Fog is high. |
| `DisableifNotFoggy_55_34F8C6474E89F3CB3996E78C6CEF2907` | `bool` | — | If checked, Blend Weight will be turned down when Fog is low. |
| `DisableifDusty_56_0044404B424580AF8096A6B8CD97F80F` | `bool` | — | If checked, Blend Weight will be turned down when Dust Amount is high. |
| `DisableifNotDusty_57_B002D3174D9C870BA261FCA71ADF2E02` | `bool` | — | If checked, Blend Weight will be turned down when Dust Amount is low. |
| `DisableifInsideInterior_58_8D9B008146005C1946D6B4B9F02F9C83` | `bool` | — | If Interior Adjustments are active, Blend Weight will be turned down when the player camera is inside an interior. |
| `DisableifOutsideInterior_59_BF184CAA469ECC2CC17795A644DA512E` | `bool` | — | If Interior Adjustments are active, Blend Weight will be turned down when the player camera is outside/unoccluded. |
| `DisableifRaining_66_6BC8BF074301B1FEAD90188DAE684C20` | `bool` | — | If checked, Blend Weight will be turned down when rain is active on UDW (ignored if UDW is not used) |
| `DisableifNotRaining_68_AE74EF0B44F68955FD9AA38EB1A1ECC4` | `bool` | — | If checked, Blend Weight will be turned down when rain is inactive on UDW (ignored if UDW is not used) |
| `DisableifSnowing_70_63462F7A45D418DF0033E496E5F1C2A3` | `bool` | — | If checked, Blend Weight will be turned down when snow is active on UDW (ignored if UDW is not used) |
| `DisableifNotSnowing_72_5FBF6A2940E5085175DF21A4FB1E2444` | `bool` | — | If checked, Blend Weight will be turned down when snow is inactive on UDW (ignored if UDW is not used) |
| `Static_75_5FD5F55D4D2FBBFA8934419CA91D88DD` | `bool` | — | — |

