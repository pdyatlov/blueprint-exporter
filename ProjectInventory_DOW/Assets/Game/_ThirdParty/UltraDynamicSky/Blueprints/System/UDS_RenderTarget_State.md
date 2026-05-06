# UDS_RenderTarget_State

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_RenderTarget_State.UDS_RenderTarget_State` |
| Asset name | `UDS_RenderTarget_State` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `PrimaryDataAsset` (`/Script/Engine.PrimaryDataAsset`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (11)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Is Active` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Center Location` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `Size` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Render Target` | `object<TextureRenderTarget2D>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Buffer Target` | `object<TextureRenderTarget2D>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Resolution` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `Half Size` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Size to Res Ratio` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Top Corner` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `Center 2D` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `Top Corner 2D` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Default` | — | — | InstanceEditable, Private |

## Functions (7)

### `Canvas Brush Location`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector2D> In)`
- Outputs: `(struct<Vector2D> Out)`
- Local variables: _none_
- Nodes: 6

### `Canvas Brush Size`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector2D> In)`
- Outputs: `(struct<Vector2D> Out)`
- Local variables: _none_
- Nodes: 4

### `Set Location`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Center Location)`
- Outputs: `(struct<LinearColor> Mapping Vector4)`
- Local variables: _none_
- Nodes: 18

### `Set Render Target`

- Access: `Public`
- Flags: —
- Inputs: `(object<TextureRenderTarget2D> Render Target, object<TextureRenderTarget2D> Buffer Target)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

### `Set Size`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Size)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9

### `Target Extent 2D`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector2D> Extent)`
- Local variables: _none_
- Nodes: 5

### `Target Needs Recenter`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Control Location, struct<Vector> Axis Mask)`
- Outputs: `(bool Yes)`
- Local variables: _none_
- Nodes: 10

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0) — DataAsset

_No authored overrides found on the CDO. `DataAsset` Blueprints typically author their payload here — if this BP is meant to differ from its parent class, this is a coverage gap._

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (1):
- `/Script/Engine.PrimaryDataAsset` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

