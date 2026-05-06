# PSD_Relaxed_Slide_FeetOut

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Relaxed/PSD_Relaxed_Slide_FeetOut.PSD_Relaxed_Slide_FeetOut` |
| Asset name | `PSD_Relaxed_Slide_FeetOut` |
| Asset type | `PoseSearchDatabase` |
| Parent class | `/Script/Engine.DataAsset` |
| Search mode | `PCAKDTree` |
| Schema | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Schemas/PSS_Relaxed_Slide.PSS_Relaxed_Slide` |
| Animation assets | **4** |
| Channels | **3** |
| Tags | 0 |
| Engine version | `5.7.4-573521+++UE_DOW+main` |

## Schema

| Field | Value |
|---|---|
| Path | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Schemas/PSS_Relaxed_Slide.PSS_Relaxed_Slide` |
| SampleRate | 30 |
| Cardinality | 20 |

### Skeleton roles (1)

| # | Role | Skeleton |
|---:|---|---|
| 0 | `(none)` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Meshes/SK_UEFN_Mannequin.SK_UEFN_Mannequin` |

### Channels (3)

| # | Class |
|---:|---|
| 0 | `/Script/PoseSearch.PoseSearchFeatureChannel_Trajectory` |
| 1 | `/Script/PoseSearch.PoseSearchFeatureChannel_Group` |
| 2 | `/Script/PoseSearch.PoseSearchFeatureChannel_Position` |

## Animation Assets (4)

| # | Asset class | Asset path | Sampling range | Mirror | Enabled |
|---:|---|---|---|---|:---:|
| 0 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Slide/M_Relaxed_Slide_FootOut_Loop.M_Relaxed_Slide_FootOut_Loop` | _full_ | `UnmirroredOnly` | yes |
| 1 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Slide/M_Relaxed_Slide_FootOut_Into_Sprint_Rfoot.M_Relaxed_Slide_FootOut_Into_Sprint_Rfoot` | _full_ | `UnmirroredOnly` | yes |
| 2 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Slide/M_Relaxed_Slide_FootOut_Into_Sprint_Lfoot.M_Relaxed_Slide_FootOut_Into_Sprint_Lfoot` | _full_ | `UnmirroredOnly` | yes |
| 3 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Slide/M_Relaxed_Slide_KneesOut_trans_FootOut.M_Relaxed_Slide_KneesOut_trans_FootOut` | _full_ | `UnmirroredOnly` | yes |

## Normalization

- NormalizationSet: `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Normalization_Sets/PSN_Relaxed_All.PSN_Relaxed_All`

## Performance & Bias

| Field | Value |
|---|---|
| PoseSearchMode | `PCAKDTree` |
| ContinuingPoseCostBias | -0.0200 |
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

