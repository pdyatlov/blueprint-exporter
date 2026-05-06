# WBP_WeaponReticle

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Loadout/Widgets/WBP_WeaponReticle.WBP_WeaponReticle` |
| Asset name | `WBP_WeaponReticle` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (1)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `ReticleOffsetNorm` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Default` | — | — | InstanceEditable |

## Functions (3)

### `ConvertToViewSpace`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector2D> OffsetPosition)`
- Outputs: `(struct<Vector2D> OutputPin)`
- Local variables: _none_
- Nodes: 15

### `SetReticleOffsetNorm`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector2D> ScreenspacePosition)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

### `UpdateDotPosition`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `NormX`, `NormY`
- Nodes: 22

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (2)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`

## Graphs

- Event graph: `EventGraph` (3 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_63` (`CanvasPanel`)
  - `CenterDot` (`Image`) [variable] via CanvasPanelSlot
  - `RecoilBoundsBox` (`CanvasPanel`) [variable] via CanvasPanelSlot
  - `RecoilDot` (`Image`) [variable] via CanvasPanelSlot

## References

Hard refs out (4):
- `/Script/SlateCore` [asset]
- `/Script/UMG` [asset]
- `/Script/UMG.UserWidget` [native]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

