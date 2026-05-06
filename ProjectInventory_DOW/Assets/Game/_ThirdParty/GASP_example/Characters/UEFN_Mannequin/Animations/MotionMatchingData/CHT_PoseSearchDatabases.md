# CHT_PoseSearchDatabases

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/CHT_PoseSearchDatabases.CHT_PoseSearchDatabases` |
| Asset name | `CHT_PoseSearchDatabases` |
| Asset type | `ChooserTable` |
| Parent class | `/Script/Chooser.ChooserSignature` |
| Result type | `ObjectResult` |
| Output class | `/Script/PoseSearch.PoseSearchDatabase` |
| Role | Root chooser |
| Columns | **1** |
| Rows | **3** |
| Nested choosers | 0 |
| Engine version | `5.7.4-573521+++UE_DOW+main` |

## Context Data (1)

| # | Struct type |
|---:|---|
| 0 | `/Script/Chooser.ContextObjectTypeClass` |

## Columns (1)

| # | Struct type | Filter | Output | Cost | Input type | Disabled |
|---:|---|:---:|:---:|:---:|---|:---:|
| 0 | `/Script/Chooser.FloatRangeColumn` | yes | — | — | `/Script/Chooser.FloatContextProperty` | — |

## Rows (3)

_Each row's struct type names the concrete `FObjectChooserBase` variant (e.g., `FEvaluateChooser` for a chooser-ref, `FAssetChooser` for a direct asset). Per-cell filter values are not rendered in this slice._

| # | Output struct | Disabled |
|---:|---|:---:|
| 0 | `/Script/Chooser.EvaluateChooser` | — |
| 1 | `/Script/Chooser.EvaluateChooser` | — |
| 2 | `/Script/Chooser.EvaluateChooser` | — |

## Fallback

- Struct type: `/Script/Chooser.EvaluateChooser`

