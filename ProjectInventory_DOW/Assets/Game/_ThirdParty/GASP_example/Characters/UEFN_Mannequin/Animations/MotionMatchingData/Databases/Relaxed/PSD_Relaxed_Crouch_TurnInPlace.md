# PSD_Relaxed_Crouch_TurnInPlace

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Relaxed/PSD_Relaxed_Crouch_TurnInPlace.PSD_Relaxed_Crouch_TurnInPlace` |
| Asset name | `PSD_Relaxed_Crouch_TurnInPlace` |
| Asset type | `PoseSearchDatabase` |
| Parent class | `/Script/Engine.DataAsset` |
| Search mode | `PCAKDTree` |
| Schema | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Schemas/PSS_Default_Mover.PSS_Default_Mover` |
| Animation assets | **8** |
| Channels | **2** |
| Tags | 1 |
| Engine version | `5.7.4-573521+++UE_DOW+main` |

## Schema

| Field | Value |
|---|---|
| Path | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Schemas/PSS_Default_Mover.PSS_Default_Mover` |
| SampleRate | 30 |
| Cardinality | 21 |

### Skeleton roles (1)

| # | Role | Skeleton |
|---:|---|---|
| 0 | `(none)` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Meshes/SK_UEFN_Mannequin.SK_UEFN_Mannequin` |

### Channels (2)

| # | Class |
|---:|---|
| 0 | `/Script/PoseSearch.PoseSearchFeatureChannel_Trajectory` |
| 1 | `/Script/PoseSearch.PoseSearchFeatureChannel_Curve` |

## Animation Assets (8)

| # | Asset class | Asset path | Sampling range | Mirror | Enabled |
|---:|---|---|---|---|:---:|
| 0 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Crouch/M_Neutral_Crouch_Idle_Turn_180_R.M_Neutral_Crouch_Idle_Turn_180_R` | _full_ | `UnmirroredOnly` | yes |
| 1 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Crouch/M_Neutral_Crouch_Idle_Turn_180_L.M_Neutral_Crouch_Idle_Turn_180_L` | _full_ | `UnmirroredOnly` | yes |
| 2 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Crouch/M_Neutral_Crouch_Idle_Turn_135_R.M_Neutral_Crouch_Idle_Turn_135_R` | _full_ | `UnmirroredOnly` | yes |
| 3 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Crouch/M_Neutral_Crouch_Idle_Turn_135_L.M_Neutral_Crouch_Idle_Turn_135_L` | _full_ | `UnmirroredOnly` | yes |
| 4 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Crouch/M_Neutral_Crouch_Idle_Turn_090_R.M_Neutral_Crouch_Idle_Turn_090_R` | _full_ | `UnmirroredOnly` | yes |
| 5 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Crouch/M_Neutral_Crouch_Idle_Turn_090_L.M_Neutral_Crouch_Idle_Turn_090_L` | _full_ | `UnmirroredOnly` | yes |
| 6 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Crouch/M_Neutral_Crouch_Idle_Turn_045_R.M_Neutral_Crouch_Idle_Turn_045_R` | _full_ | `UnmirroredOnly` | yes |
| 7 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Crouch/M_Neutral_Crouch_Idle_Turn_045_L.M_Neutral_Crouch_Idle_Turn_045_L` | _full_ | `UnmirroredOnly` | yes |

## Normalization

- NormalizationSet: `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Normalization_Sets/PSN_Relaxed_All.PSN_Relaxed_All`

## Performance & Bias

| Field | Value |
|---|---|
| PoseSearchMode | `PCAKDTree` |
| ContinuingPoseCostBias | -0.0100 |
| BaseCostBias | 0.0000 |
| LoopingCostBias | -0.0050 |
| ContinuingInteractionCostBias | 0.0000 |
| KDTreeQueryNumNeighbors | 200 |
| NumberOfPrincipalComponents | 4 |
| KDTreeMaxLeafSize | 16 |
| PosePruningSimilarityThreshold | 0.0000 |
| PCAValuesPruningSimilarityThreshold | 0.0000 |
| ExcludeFromDatabaseParameters | [0.000, -0.300] |
| AdditionalExtrapolationTime | [-100.000, 100.000] |

## Tags (1)

- `TurnInPlace`

