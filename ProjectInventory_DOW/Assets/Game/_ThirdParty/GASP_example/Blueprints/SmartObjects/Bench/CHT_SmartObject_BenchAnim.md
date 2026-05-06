# CHT_SmartObject_BenchAnim

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/Bench/CHT_SmartObject_BenchAnim.CHT_SmartObject_BenchAnim` |
| Asset name | `CHT_SmartObject_BenchAnim` |
| Asset type | `ChooserTable` |
| Parent class | `/Script/Chooser.ChooserSignature` |
| Result type | `ObjectResult` |
| Output class | `/Script/Engine.AnimMontage` |
| Role | Root chooser |
| Columns | **2** |
| Rows | **10** |
| Nested choosers | 0 |
| Engine version | `5.7.4-573521+++UE_DOW+main` |

## Context Data (3)

| # | Struct type |
|---:|---|
| 0 | `/Script/Chooser.ContextObjectTypeClass` |
| 1 | `/Script/Chooser.ContextObjectTypeStruct` |
| 2 | `/Script/Chooser.ContextObjectTypeStruct` |

## Columns (2)

| # | Struct type | Filter | Output | Cost | Input type | Disabled |
|---:|---|:---:|:---:|:---:|---|:---:|
| 0 | `/Script/Chooser.FloatRangeColumn` | yes | — | — | `/Script/Chooser.FloatContextProperty` | — |
| 1 | `/Script/PoseSearch.PoseSearchColumn` | yes | — | yes | `/Script/PoseSearch.PoseHistoryContextProperty` | — |

## Rows (10)

_Each row's struct type names the concrete `FObjectChooserBase` variant (e.g., `FEvaluateChooser` for a chooser-ref, `FAssetChooser` for a direct asset). Per-cell filter values are not rendered in this slice._

| # | Output struct | Disabled |
|---:|---|:---:|
| 0 | `/Script/Chooser.AssetChooser` | — |
| 1 | `/Script/Chooser.AssetChooser` | — |
| 2 | `/Script/Chooser.AssetChooser` | — |
| 3 | `/Script/Chooser.AssetChooser` | — |
| 4 | `/Script/Chooser.AssetChooser` | — |
| 5 | `/Script/Chooser.AssetChooser` | — |
| 6 | `/Script/Chooser.AssetChooser` | — |
| 7 | `/Script/Chooser.AssetChooser` | — |
| 8 | `/Script/Chooser.AssetChooser` | — |
| 9 | `/Script/Chooser.AssetChooser` | — |

## Fallback

_Unset — the chooser returns null when no row matches._

