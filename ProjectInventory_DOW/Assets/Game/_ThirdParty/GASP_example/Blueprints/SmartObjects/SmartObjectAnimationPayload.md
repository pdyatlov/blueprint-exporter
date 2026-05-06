# SmartObjectAnimationPayload

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/SmartObjectAnimationPayload.SmartObjectAnimationPayload` |
| Asset name | `SmartObjectAnimationPayload` |
| Asset type | `UserDefinedStruct` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |

## Fields (8)

| Name | Type | Category | ToolTip |
|---|---|---|---|
| `MontageToPlay_7_F6A0D42044C562C11411D2932E3924B9` | `UAnimMontage*` | — | What montage will play |
| `PlayTime_29_A17B3F0E4D0F623A9AD83EA5C6B62190` | `double` | — | If greater than 0, this defines how long the requested montage will play. |
| `RandomPlaytimeVariance_36_0E021DE54C1C093AE9BEC18D4C1CA775` | `double` | — | If Playtime is used, allows +- variance of this value to be added to the playtime. |
| `StartTime_4_27D4D0A8480A6DB032374CAAEA40B79B` | `double` | — | The start time for the animation, in the entry this is from motion matching. |
| `Playrate_13_FBFEE455436381981547FBA0406371DC` | `double` | — | — |
| `NumLoops_10_6272555744E0B949998D99A2A251E547` | `int32` | — | — |
| `WarpTargetTransform_17_A6656D8446DF7313C287309408AD4BFE` | `FTransform` | — | — |
| `UseWarpTarget_20_605A49854206BB310DF1108FA55D9108` | `bool` | — | Signifies that we have a warp target for this animation, the target position being above. |

