# UDS_Climate_Preset

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Climate_Preset.UDS_Climate_Preset` |
| Asset name | `UDS_Climate_Preset` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `PrimaryDataAsset` (`/Script/Engine.PrimaryDataAsset`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (22)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Winter Average High Temp (C)` | `real<double>` | `0.000000` | `Temperature` | — | — | InstanceEditable, Private |
| `Winter Average Low Temp (C)` | `real<double>` | `0.000000` | `Temperature` | — | — | InstanceEditable, Private |
| `Spring Average High Temp (C)` | `real<double>` | `0.000000` | `Temperature` | — | — | InstanceEditable, Private |
| `Spring Average Low Temp (C)` | `real<double>` | `0.000000` | `Temperature` | — | — | InstanceEditable, Private |
| `Summer Average High Temp (C)` | `real<double>` | `0.000000` | `Temperature` | — | — | InstanceEditable, Private |
| `Summer Average Low Temp (C)` | `real<double>` | `0.000000` | `Temperature` | — | — | InstanceEditable, Private |
| `Autumn Average High Temp (C)` | `real<double>` | `0.000000` | `Temperature` | — | — | InstanceEditable, Private |
| `Autumn Average Low Temp (C)` | `real<double>` | `0.000000` | `Temperature` | — | — | InstanceEditable, Private |
| `Winter Cloudy Percentage` | `real<double>` | `0.000000` | `Cloudiness` | — | — | InstanceEditable, Private |
| `Spring Cloudy Percentage` | `real<double>` | `0.000000` | `Cloudiness` | — | — | InstanceEditable, Private |
| `Summer Cloudy Percentage` | `real<double>` | `0.000000` | `Cloudiness` | — | — | InstanceEditable, Private |
| `Autumn Cloudy Percentage` | `real<double>` | `0.000000` | `Cloudiness` | — | — | InstanceEditable, Private |
| `Winter Rainfall (mm)` | `real<double>` | `0.000000` | `Rainfall (Monthly Average)` | — | — | InstanceEditable, Private |
| `Spring Rainfall (mm)` | `real<double>` | `0.000000` | `Rainfall (Monthly Average)` | — | — | InstanceEditable, Private |
| `Summer Rainfall (mm)` | `real<double>` | `0.000000` | `Rainfall (Monthly Average)` | — | — | InstanceEditable, Private |
| `Autumn Rainfall (mm)` | `real<double>` | `0.000000` | `Rainfall (Monthly Average)` | — | — | InstanceEditable, Private |
| `Winter Snowfall (mm)` | `real<double>` | `0.000000` | `Snowfall (Monthly Average)` | — | — | InstanceEditable, Private |
| `Spring Snowfall (mm)` | `real<double>` | `0.000000` | `Snowfall (Monthly Average)` | — | — | InstanceEditable, Private |
| `Summer Snowfall (mm)` | `real<double>` | `0.000000` | `Snowfall (Monthly Average)` | — | — | InstanceEditable, Private |
| `Autumn Snowfall (mm)` | `real<double>` | `0.000000` | `Snowfall (Monthly Average)` | — | — | InstanceEditable, Private |
| `Dust/Sand Present` | `real<double>` | `0.000000` | `Dust` | — | — | InstanceEditable, Private |
| `Data Source` | `text` | — | `Default` | — | — | InstanceEditable, Private |

## Functions (1)

### `Return Temperature Range in Scale`

- Access: `Public`
- Flags: —
- Inputs: `(byte Scale = NewEnumerator0, int Season)`
- Outputs: `(real<double> Low, real<double> High)`
- Local variables: _none_
- Nodes: 24

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

Hard refs out (2):
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_TemperatureType` [asset]
- `/Script/Engine.PrimaryDataAsset` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

