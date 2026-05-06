# PSD_Relaxed_Crouch_Idles

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Relaxed/PSD_Relaxed_Crouch_Idles.PSD_Relaxed_Crouch_Idles` |
| Asset name | `PSD_Relaxed_Crouch_Idles` |
| Asset type | `PoseSearchDatabase` |
| Parent class | `/Script/Engine.DataAsset` |
| Search mode | `PCAKDTree` |
| Schema | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Schemas/PSS_Relaxed_Idle.PSS_Relaxed_Idle` |
| Animation assets | **2** |
| Channels | **2** |
| Tags | 0 |
| Engine version | `5.7.4-573521+++UE_DOW+main` |

## Schema

| Field | Value |
|---|---|
| Path | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Schemas/PSS_Relaxed_Idle.PSS_Relaxed_Idle` |
| SampleRate | 30 |
| Cardinality | 34 |

### Skeleton roles (1)

| # | Role | Skeleton |
|---:|---|---|
| 0 | `(none)` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Meshes/SK_UEFN_Mannequin.SK_UEFN_Mannequin` |

### Channels (2)

| # | Class |
|---:|---|
| 0 | `/Script/PoseSearch.PoseSearchFeatureChannel_Pose` |
| 1 | `/Script/PoseSearch.PoseSearchFeatureChannel_Trajectory` |

## Animation Assets (2)

| # | Asset class | Asset path | Sampling range | Mirror | Enabled |
|---:|---|---|---|---|:---:|
| 0 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Idle/M_Neutral_Crouch_Idle_Loop.M_Neutral_Crouch_Idle_Loop` | _full_ | `UnmirroredOnly` | yes |
| 1 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Crouch/M_Relaxed_Transition_Stand_to_Crouch.M_Relaxed_Transition_Stand_to_Crouch` | _full_ | `UnmirroredOnly` | yes |

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

