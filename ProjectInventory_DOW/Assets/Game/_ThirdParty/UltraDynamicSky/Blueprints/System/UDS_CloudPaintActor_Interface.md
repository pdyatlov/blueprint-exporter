# UDS_CloudPaintActor_Interface

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_CloudPaintActor_Interface.UDS_CloudPaintActor_Interface` |
| Asset name | `UDS_CloudPaintActor_Interface` |
| Subclass | `Blueprint` |
| Blueprint type | `Interface` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Interface` (`/Script/CoreUObject.Interface`, native, module `/Script/CoreUObject`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (2)

### `Apply Effect to Cloud Coverage Value`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Sample Location, real<double>& Cloud Coverage [ref], real<double> Painted Opacity)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2

### `Draw to Cloud Paint Target`

- Access: `Public`
- Flags: —
- Inputs: `(object<Canvas> Canvas, object<MaterialInstanceDynamic> Radial Storm Draw MID, struct<Vector> Target Mapping, int Target Res, bool& Can Add Coverage [ref], bool& Can Subtract Coverage [ref], bool Cloud Painting Active)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (1):
- `/Script/CoreUObject.Interface` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Interface`
- Subclass: `Blueprint`
- Custom metadata: _none_

