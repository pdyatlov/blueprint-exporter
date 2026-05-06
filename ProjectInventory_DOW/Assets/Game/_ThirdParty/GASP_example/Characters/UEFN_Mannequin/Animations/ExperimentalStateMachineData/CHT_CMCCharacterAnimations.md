# CHT_CMCCharacterAnimations

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/ExperimentalStateMachineData/CHT_CMCCharacterAnimations.CHT_CMCCharacterAnimations` |
| Asset name | `CHT_CMCCharacterAnimations` |
| Asset type | `ChooserTable` |
| Parent class | `/Script/Chooser.ChooserSignature` |
| Result type | `ObjectResult` |
| Output class | `/Script/Engine.AnimationAsset` |
| Role | Root chooser |
| Columns | **3** |
| Rows | **7** |
| Nested choosers | 0 |
| Engine version | `5.7.4-573521+++UE_DOW+main` |

## Context Data (2)

| # | Struct type |
|---:|---|
| 0 | `/Script/Chooser.ContextObjectTypeClass` |
| 1 | `/Script/Chooser.ContextObjectTypeStruct` |

## Columns (3)

| # | Struct type | Filter | Output | Cost | Input type | Disabled |
|---:|---|:---:|:---:|:---:|---|:---:|
| 0 | `/Script/Chooser.MultiEnumColumn` | yes | — | — | `/Script/Chooser.EnumContextProperty` | — |
| 1 | `/Script/Chooser.EnumColumn` | yes | — | — | `/Script/Chooser.EnumContextProperty` | — |
| 2 | `/Script/Chooser.EnumColumn` | yes | — | — | `/Script/Chooser.EnumContextProperty` | — |

## Rows (7)

_Each row's struct type names the concrete `FObjectChooserBase` variant (e.g., `FEvaluateChooser` for a chooser-ref, `FAssetChooser` for a direct asset). Per-cell filter values are not rendered in this slice._

| # | Output struct | Disabled |
|---:|---|:---:|
| 0 | `/Script/Chooser.NestedChooser` | — |
| 1 | `/Script/Chooser.NestedChooser` | — |
| 2 | `/Script/Chooser.NestedChooser` | — |
| 3 | `/Script/Chooser.NestedChooser` | — |
| 4 | `/Script/Chooser.NestedChooser` | — |
| 5 | `/Script/Chooser.NestedChooser` | — |
| 6 | `/Script/Chooser.NestedChooser` | — |

## Fallback

_Unset — the chooser returns null when no row matches._

