# CHT_RotationOffsetCurve

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/Data/CHT_RotationOffsetCurve.CHT_RotationOffsetCurve` |
| Asset name | `CHT_RotationOffsetCurve` |
| Asset type | `ChooserTable` |
| Parent class | `/Script/Chooser.ChooserSignature` |
| Result type | `ObjectResult` |
| Output class | `/Script/Engine.CurveFloat` |
| Role | Root chooser |
| Columns | **2** |
| Rows | **8** |
| Nested choosers | 0 |
| Engine version | `5.7.4-573521+++UE_DOW+main` |

## Context Data (1)

| # | Struct type |
|---:|---|
| 0 | `/Script/Chooser.ContextObjectTypeStruct` |

## Columns (2)

| # | Struct type | Filter | Output | Cost | Input type | Disabled |
|---:|---|:---:|:---:|:---:|---|:---:|
| 0 | `/Script/Chooser.EnumColumn` | yes | — | — | `/Script/Chooser.EnumContextProperty` | — |
| 1 | `/Script/Chooser.EnumColumn` | yes | — | — | `/Script/Chooser.EnumContextProperty` | — |

## Rows (8)

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

## Fallback

_Unset — the chooser returns null when no row matches._

