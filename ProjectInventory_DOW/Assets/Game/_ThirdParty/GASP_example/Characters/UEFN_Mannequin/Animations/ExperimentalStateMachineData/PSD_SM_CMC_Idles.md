# PSD_SM_CMC_Idles

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/ExperimentalStateMachineData/PSD_SM_CMC_Idles.PSD_SM_CMC_Idles` |
| Asset name | `PSD_SM_CMC_Idles` |
| Asset type | `PoseSearchDatabase` |
| Parent class | `/Script/Engine.DataAsset` |
| Search mode | `BruteForce` |
| Schema | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/ExperimentalStateMachineData/PSS_SM_CMC_Idles.PSS_SM_CMC_Idles` |
| Animation assets | **6** |
| Channels | **1** |
| Tags | 0 |
| Engine version | `5.7.4-573521+++UE_DOW+main` |

## Schema

| Field | Value |
|---|---|
| Path | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/ExperimentalStateMachineData/PSS_SM_CMC_Idles.PSS_SM_CMC_Idles` |
| SampleRate | 30 |
| Cardinality | 18 |

### Skeleton roles (1)

| # | Role | Skeleton |
|---:|---|---|
| 0 | `(none)` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Meshes/SK_UEFN_Mannequin.SK_UEFN_Mannequin` |

### Channels (1)

| # | Class |
|---:|---|
| 0 | `/Script/PoseSearch.PoseSearchFeatureChannel_Pose` |

## Animation Assets (6)

| # | Asset class | Asset path | Sampling range | Mirror | Enabled |
|---:|---|---|---|---|:---:|
| 0 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Idle/M_Neutral_Crouch_Idle_Loop.M_Neutral_Crouch_Idle_Loop` | [0.000, 0.488] | `UnmirroredOnly` | yes |
| 1 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Crouch/M_Relaxed_Transition_Stand_to_Crouch.M_Relaxed_Transition_Stand_to_Crouch` | [0.000, 0.177] | `UnmirroredOnly` | yes |
| 2 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Crouch/M_Relaxed_Transition_Crouch_to_Stand.M_Relaxed_Transition_Crouch_to_Stand` | [0.000, 0.177] | `UnmirroredOnly` | yes |
| 3 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Crouch/M_Neutral_Transition_Stand_to_Crouch.M_Neutral_Transition_Stand_to_Crouch` | [0.000, 0.177] | `UnmirroredOnly` | yes |
| 4 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Crouch/M_Neutral_Transition_Crouch_to_Stand.M_Neutral_Transition_Crouch_to_Stand` | [0.000, 0.177] | `UnmirroredOnly` | yes |
| 5 | `AnimSequence` | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Idle/M_Neutral_Stand_Idle_Loop.M_Neutral_Stand_Idle_Loop` | [0.000, 0.514] | `UnmirroredOnly` | yes |

## Normalization

_No NormalizationSet assigned._

## Performance & Bias

| Field | Value |
|---|---|
| PoseSearchMode | `BruteForce` |
| ContinuingPoseCostBias | -0.0100 |
| BaseCostBias | 0.0000 |
| LoopingCostBias | 0.0000 |
| ContinuingInteractionCostBias | 0.0000 |
| KDTreeQueryNumNeighbors | 200 |
| NumberOfPrincipalComponents | 4 |
| KDTreeMaxLeafSize | 16 |
| PosePruningSimilarityThreshold | 0.0000 |
| PCAValuesPruningSimilarityThreshold | 0.0000 |
| ExcludeFromDatabaseParameters | [0.000, -0.300] |
| AdditionalExtrapolationTime | [-100.000, 100.000] |

