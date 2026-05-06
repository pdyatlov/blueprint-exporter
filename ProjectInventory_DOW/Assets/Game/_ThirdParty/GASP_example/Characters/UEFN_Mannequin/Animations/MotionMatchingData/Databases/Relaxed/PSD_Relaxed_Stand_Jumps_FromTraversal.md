# PSD_Relaxed_Stand_Jumps_FromTraversal

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Databases/Relaxed/PSD_Relaxed_Stand_Jumps_FromTraversal.PSD_Relaxed_Stand_Jumps_FromTraversal` |
| Asset name | `PSD_Relaxed_Stand_Jumps_FromTraversal` |
| Asset type | `PoseSearchDatabase` |
| Parent class | `/Script/Engine.DataAsset` |
| Search mode | `PCAKDTree` |
| Schema | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Schemas/PSS_Default_Mover.PSS_Default_Mover` |
| Animation assets | **2** |
| Channels | **2** |
| Tags | 0 |
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

## Animation Assets (2)

| # | Asset class | Asset path | Sampling range | Mirror | Enabled |
|---:|---|---|---|---|:---:|
| 0 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Traversal/Vault/M_Neutral_Traversal_Vault_1_0_run_F_Lfoot.M_Neutral_Traversal_Vault_1_0_run_F_Lfoot` | _full_ | `UnmirroredOnly` | yes |
| 1 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Traversal/Vault/M_Neutral_Traversal_Vault_1_0_stand_F_Lfoot.M_Neutral_Traversal_Vault_1_0_stand_F_Lfoot` | _full_ | `UnmirroredOnly` | yes |

## Normalization

- NormalizationSet: `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/Normalization_Sets/PSN_Relaxed_All.PSN_Relaxed_All`

## Performance & Bias

| Field | Value |
|---|---|
| PoseSearchMode | `PCAKDTree` |
| ContinuingPoseCostBias | -0.5000 |
| BaseCostBias | -0.1000 |
| LoopingCostBias | -0.0050 |
| ContinuingInteractionCostBias | 0.0000 |
| KDTreeQueryNumNeighbors | 200 |
| NumberOfPrincipalComponents | 4 |
| KDTreeMaxLeafSize | 16 |
| PosePruningSimilarityThreshold | 0.0000 |
| PCAValuesPruningSimilarityThreshold | 0.0000 |
| ExcludeFromDatabaseParameters | [0.000, -0.300] |
| AdditionalExtrapolationTime | [-100.000, 100.000] |

