# PSD_Sparse_Stand_Sprint_Starts

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Sparse/PSD_Sparse_Stand_Sprint_Starts.PSD_Sparse_Stand_Sprint_Starts` |
| Asset name | `PSD_Sparse_Stand_Sprint_Starts` |
| Asset type | `PoseSearchDatabase` |
| Parent class | `/Script/Engine.DataAsset` |
| Search mode | `PCAKDTree` |
| Schema | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Schemas/PSS_Default.PSS_Default` |
| Animation assets | **6** |
| Channels | **2** |
| Tags | 0 |
| Engine version | `5.7.4-573521+++UE_DOW+main` |

## Schema

| Field | Value |
|---|---|
| Path | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Schemas/PSS_Default.PSS_Default` |
| SampleRate | 30 |
| Cardinality | 30 |

### Skeleton roles (1)

| # | Role | Skeleton |
|---:|---|---|
| 0 | `(none)` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Meshes/SK_UEFN_Mannequin.SK_UEFN_Mannequin` |

### Channels (2)

| # | Class |
|---:|---|
| 0 | `/Script/PoseSearch.PoseSearchFeatureChannel_Trajectory` |
| 1 | `/Script/PoseSearch.PoseSearchFeatureChannel_Group` |

## Animation Assets (6)

| # | Asset class | Asset path | Sampling range | Mirror | Enabled |
|---:|---|---|---|---|:---:|
| 0 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Sprint/M_Neutral_Sprint_Start_F_Lfoot.M_Neutral_Sprint_Start_F_Lfoot` | _full_ | `UnmirroredOnly` | yes |
| 1 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Sprint/M_Neutral_Sprint_Start_F_Rfoot.M_Neutral_Sprint_Start_F_Rfoot` | _full_ | `UnmirroredOnly` | yes |
| 2 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Sprint/M_Neutral_Sprint_Reface_Start_F_L_090.M_Neutral_Sprint_Reface_Start_F_L_090` | _full_ | `UnmirroredOnly` | yes |
| 3 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Sprint/M_Neutral_Sprint_Reface_Start_F_L_180.M_Neutral_Sprint_Reface_Start_F_L_180` | _full_ | `UnmirroredOnly` | yes |
| 4 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Sprint/M_Neutral_Sprint_Reface_Start_F_R_090.M_Neutral_Sprint_Reface_Start_F_R_090` | _full_ | `UnmirroredOnly` | yes |
| 5 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Sprint/M_Neutral_Sprint_Reface_Start_F_R_180.M_Neutral_Sprint_Reface_Start_F_R_180` | _full_ | `UnmirroredOnly` | yes |

## Normalization

- NormalizationSet: `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Normalization_Sets/PSN_Sparse_All.PSN_Sparse_All`

## Performance & Bias

| Field | Value |
|---|---|
| PoseSearchMode | `PCAKDTree` |
| ContinuingPoseCostBias | -0.0500 |
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

