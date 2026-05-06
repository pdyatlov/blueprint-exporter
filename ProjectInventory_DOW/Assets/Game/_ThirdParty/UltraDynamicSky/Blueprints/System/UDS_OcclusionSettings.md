# UDS_OcclusionSettings

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_OcclusionSettings.UDS_OcclusionSettings` |
| Asset name | `UDS_OcclusionSettings` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `PrimaryDataAsset` (`/Script/Engine.PrimaryDataAsset`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (13)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Occlusion Mode` | `byte<UDS_Occlusion_Mode>` | `NewEnumerator2` | `Default` | — | — | InstanceEditable, Private |
| `Use GPU Distance Field Collision` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Max Trace Distance` | `real<double>` | `4500.000000` | `Default` | — | — | InstanceEditable, Private |
| `Horizontal Trace Steps` | `int` | `12` | `Default` | — | — | InstanceEditable, Private |
| `Vertical Trace Steps` | `int` | `5` | `Default` | — | — | InstanceEditable, Private |
| `Trace Channel` | `byte<ETraceTypeQuery>` | `TraceTypeQuery1` | `Default` | — | — | InstanceEditable, Private |
| `Update Period` | `real<double>` | `0.350000` | `Default` | — | — | InstanceEditable, Private |
| `Global Occlusion Min Fraction` | `real<double>` | `0.200000` | `Default` | — | — | InstanceEditable, Private |
| `Global Occlusion Max Fraction` | `real<double>` | `0.900000` | `Default` | — | — | InstanceEditable, Private |
| `Query Occlusion Portals` | `bool` | `True` | `Default` | — | — | InstanceEditable, Private |
| `GPU Distance Field Sample Count` | `int` | `1000` | `Default` | — | — | InstanceEditable, Private |
| `Show Trace Debugs` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Occlusion Behavior Under Water` | `byte<UDS_Occlusion_Water_Behavior>` | `NewEnumerator0` | `Default` | — | — | InstanceEditable, Private |

## Functions (0)

_None._

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

Hard refs out (3):
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Occlusion_Mode` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Occlusion_Water_Behavior` [asset]
- `/Script/Engine.PrimaryDataAsset` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

