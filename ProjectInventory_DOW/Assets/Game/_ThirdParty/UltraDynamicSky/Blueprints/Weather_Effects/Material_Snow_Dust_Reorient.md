# Material_Snow_Dust_Reorient

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Material_Snow_Dust_Reorient.Material_Snow_Dust_Reorient` |
| Asset name | `Material_Snow_Dust_Reorient` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `SceneComponent` (`/Script/Engine.SceneComponent`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (7)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Dynamic Material Instances` | `TArray<object<MaterialInstanceDynamic>>` | — | `Material Effects` | — | — | InstanceEditable, Private |
| `Snow/Dust Reorient Speed` | `real<float>` | `4.000000` | `Settings` | — | — | InstanceEditable |
| `Snow/Dust Reorient Update Period` | `real<double>` | `0.100000` | `Settings` | — | — | InstanceEditable |
| `Snow/Dust Reorient Check Period` | `real<double>` | `2.000000` | `Settings` | — | — | InstanceEditable |
| `Snow Up Vector` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=1.000000)` | `System` | — | — | InstanceEditable, Private |
| `Reorienting Snow` | `bool` | `False` | `System` | — | — | InstanceEditable, Private |
| `Reorientation Needed Threshold` | `real<double>` | `6.000000` | `Settings` | — | — | InstanceEditable |

## Functions (3)

### `Check for Snow Reorient`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13

### `Reorient Snow`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 35

### `Startup`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (3 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (1):
- `/Script/Engine.SceneComponent` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

