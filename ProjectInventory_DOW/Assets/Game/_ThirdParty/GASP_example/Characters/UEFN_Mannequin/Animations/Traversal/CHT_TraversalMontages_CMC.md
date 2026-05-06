# CHT_TraversalMontages_CMC

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Traversal/CHT_TraversalMontages_CMC.CHT_TraversalMontages_CMC` |
| Asset name | `CHT_TraversalMontages_CMC` |
| Asset type | `ChooserTable` |
| Parent class | `/Script/Chooser.ChooserSignature` |
| Result type | `ObjectResult` |
| Output class | `/Script/Engine.AnimMontage` |
| Role | Root chooser |
| Columns | **6** |
| Rows | **4** |
| Nested choosers | 0 |
| Engine version | `5.7.4-573521+++UE_DOW+main` |

## Context Data (3)

| # | Struct type |
|---:|---|
| 0 | `/Script/Chooser.ContextObjectTypeClass` |
| 1 | `/Script/Chooser.ContextObjectTypeStruct` |
| 2 | `/Script/Chooser.ContextObjectTypeStruct` |

## Columns (6)

| # | Struct type | Filter | Output | Cost | Input type | Disabled |
|---:|---|:---:|:---:|:---:|---|:---:|
| 0 | `/Script/Chooser.BoolColumn` | yes | — | — | `/Script/Chooser.BoolContextProperty` | — |
| 1 | `/Script/Chooser.BoolColumn` | yes | — | — | `/Script/Chooser.BoolContextProperty` | — |
| 2 | `/Script/Chooser.BoolColumn` | yes | — | — | `/Script/Chooser.BoolContextProperty` | — |
| 3 | `/Script/Chooser.FloatRangeColumn` | yes | — | — | `/Script/Chooser.FloatContextProperty` | — |
| 4 | `/Script/Chooser.FloatRangeColumn` | yes | — | — | `/Script/Chooser.FloatContextProperty` | — |
| 5 | `/Script/Chooser.OutputEnumColumn` | — | yes | — | `/Script/Chooser.EnumContextProperty` | — |

## Rows (4)

_Each row's struct type names the concrete `FObjectChooserBase` variant (e.g., `FEvaluateChooser` for a chooser-ref, `FAssetChooser` for a direct asset). Per-cell filter values are not rendered in this slice._

| # | Output struct | Disabled |
|---:|---|:---:|
| 0 | `/Script/Chooser.NestedChooser` | — |
| 1 | `/Script/Chooser.NestedChooser` | — |
| 2 | `/Script/Chooser.NestedChooser` | — |
| 3 | `/Script/Chooser.NestedChooser` | — |

## Fallback

_Unset — the chooser returns null when no row matches._

