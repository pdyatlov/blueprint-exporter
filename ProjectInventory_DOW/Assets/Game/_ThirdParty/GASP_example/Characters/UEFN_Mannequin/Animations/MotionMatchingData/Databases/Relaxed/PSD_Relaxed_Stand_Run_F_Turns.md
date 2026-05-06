# PSD_Relaxed_Stand_Run_F_Turns

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Relaxed/PSD_Relaxed_Stand_Run_F_Turns.PSD_Relaxed_Stand_Run_F_Turns` |
| Asset name | `PSD_Relaxed_Stand_Run_F_Turns` |
| Asset type | `PoseSearchDatabase` |
| Parent class | `/Script/Engine.DataAsset` |
| Search mode | `PCAKDTree` |
| Schema | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Schemas/PSS_Relaxed_Pivots.PSS_Relaxed_Pivots` |
| Animation assets | **8** |
| Channels | **2** |
| Tags | 1 |
| Engine version | `5.7.4-573521+++UE_DOW+main` |

## Schema

| Field | Value |
|---|---|
| Path | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Schemas/PSS_Relaxed_Pivots.PSS_Relaxed_Pivots` |
| SampleRate | 30 |
| Cardinality | 33 |

### Skeleton roles (1)

| # | Role | Skeleton |
|---:|---|---|
| 0 | `(none)` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Meshes/SK_UEFN_Mannequin.SK_UEFN_Mannequin` |

### Channels (2)

| # | Class |
|---:|---|
| 0 | `/Script/PoseSearch.PoseSearchFeatureChannel_Trajectory` |
| 1 | `/Script/PoseSearch.PoseSearchFeatureChannel_Group` |

## Animation Assets (8)

| # | Asset class | Asset path | Sampling range | Mirror | Enabled |
|---:|---|---|---|---|:---:|
| 0 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Run/M_Relaxed_Run_Turn_R_180_Rfoot.M_Relaxed_Run_Turn_R_180_Rfoot` | _full_ | `UnmirroredOnly` | yes |
| 1 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Run/M_Relaxed_Run_Turn_R_180_Lfoot.M_Relaxed_Run_Turn_R_180_Lfoot` | _full_ | `UnmirroredOnly` | yes |
| 2 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Run/M_Relaxed_Run_Turn_R_090_Rfoot.M_Relaxed_Run_Turn_R_090_Rfoot` | _full_ | `UnmirroredOnly` | yes |
| 3 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Run/M_Relaxed_Run_Turn_R_090_Lfoot.M_Relaxed_Run_Turn_R_090_Lfoot` | _full_ | `UnmirroredOnly` | yes |
| 4 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Run/M_Relaxed_Run_Turn_L_180_Rfoot.M_Relaxed_Run_Turn_L_180_Rfoot` | _full_ | `UnmirroredOnly` | yes |
| 5 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Run/M_Relaxed_Run_Turn_L_180_Lfoot.M_Relaxed_Run_Turn_L_180_Lfoot` | _full_ | `UnmirroredOnly` | yes |
| 6 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Run/M_Relaxed_Run_Turn_L_090_Rfoot.M_Relaxed_Run_Turn_L_090_Rfoot` | _full_ | `UnmirroredOnly` | yes |
| 7 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Run/M_Relaxed_Run_Turn_L_090_Lfoot.M_Relaxed_Run_Turn_L_090_Lfoot` | _full_ | `UnmirroredOnly` | yes |

## Normalization

- NormalizationSet: `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Normalization_Sets/PSN_Relaxed_All.PSN_Relaxed_All`

## Performance & Bias

| Field | Value |
|---|---|
| PoseSearchMode | `PCAKDTree` |
| ContinuingPoseCostBias | -0.3500 |
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

- `Pivots`

