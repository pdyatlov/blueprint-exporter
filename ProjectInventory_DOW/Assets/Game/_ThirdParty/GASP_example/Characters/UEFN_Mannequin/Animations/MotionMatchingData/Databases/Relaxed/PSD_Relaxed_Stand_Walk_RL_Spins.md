# PSD_Relaxed_Stand_Walk_RL_Spins

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Relaxed/PSD_Relaxed_Stand_Walk_RL_Spins.PSD_Relaxed_Stand_Walk_RL_Spins` |
| Asset name | `PSD_Relaxed_Stand_Walk_RL_Spins` |
| Asset type | `PoseSearchDatabase` |
| Parent class | `/Script/Engine.DataAsset` |
| Search mode | `PCAKDTree` |
| Schema | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Schemas/PSS_Relaxed_WalkSpins.PSS_Relaxed_WalkSpins` |
| Animation assets | **8** |
| Channels | **2** |
| Tags | 0 |
| Engine version | `5.7.4-573521+++UE_DOW+main` |

## Schema

| Field | Value |
|---|---|
| Path | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Schemas/PSS_Relaxed_WalkSpins.PSS_Relaxed_WalkSpins` |
| SampleRate | 30 |
| Cardinality | 28 |

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
| 0 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Walk/M_Relaxed_Walk_Spin_B_RL_Lfoot.M_Relaxed_Walk_Spin_B_RL_Lfoot` | _full_ | `UnmirroredOnly` | yes |
| 1 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Walk/M_Relaxed_Walk_Spin_B_RL_Rfoot.M_Relaxed_Walk_Spin_B_RL_Rfoot` | _full_ | `UnmirroredOnly` | yes |
| 2 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Walk/M_Relaxed_Walk_Spin_F_360_L_Lfoot.M_Relaxed_Walk_Spin_F_360_L_Lfoot` | _full_ | `UnmirroredOnly` | yes |
| 3 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Walk/M_Relaxed_Walk_Spin_F_360_L_Rfoot.M_Relaxed_Walk_Spin_F_360_L_Rfoot` | _full_ | `UnmirroredOnly` | yes |
| 4 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Walk/M_Relaxed_Walk_Spin_F_360_R_Lfoot.M_Relaxed_Walk_Spin_F_360_R_Lfoot` | _full_ | `UnmirroredOnly` | yes |
| 5 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Walk/M_Relaxed_Walk_Spin_F_360_R_Rfoot.M_Relaxed_Walk_Spin_F_360_R_Rfoot` | _full_ | `UnmirroredOnly` | yes |
| 6 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Walk/M_Relaxed_Walk_Spin_F_RL_Lfoot.M_Relaxed_Walk_Spin_F_RL_Lfoot` | _full_ | `UnmirroredOnly` | yes |
| 7 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Walk/M_Relaxed_Walk_Spin_F_RL_Rfoot.M_Relaxed_Walk_Spin_F_RL_Rfoot` | _full_ | `UnmirroredOnly` | yes |

## Normalization

- NormalizationSet: `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Normalization_Sets/PSN_Relaxed_All.PSN_Relaxed_All`

## Performance & Bias

| Field | Value |
|---|---|
| PoseSearchMode | `PCAKDTree` |
| ContinuingPoseCostBias | -0.3000 |
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

