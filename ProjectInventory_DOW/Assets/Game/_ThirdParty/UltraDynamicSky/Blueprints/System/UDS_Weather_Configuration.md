# UDS_Weather_Configuration

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Weather_Configuration.UDS_Weather_Configuration` |
| Asset name | `UDS_Weather_Configuration` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UDS_SharedConfig_C` (`/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_SharedConfig.UDS_SharedConfig_C`, blueprint)
- Interfaces: _none_

## Variables (11)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Weather Probability (Summer)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `()` | `Weather Properties` | — | — | InstanceEditable, Private |
| `Weather Probability (Autumn)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `()` | `Weather Properties` | — | — | InstanceEditable, Private |
| `Weather Probability (Winter)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `()` | `Weather Properties` | — | — | InstanceEditable, Private |
| `Weather Probability (Spring)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `()` | `Weather Properties` | — | — | InstanceEditable, Private |
| `Weather Specific Interval Multipliers` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `()` | `Weather Properties` | — | — | InstanceEditable, Private |
| `PhysMats_Disable Snow` | `TArray<object<PhysicalMaterial>>` | — | `Weather Properties` | — | — | InstanceEditable, Private |
| `PhysMats_Disable Puddles` | `TArray<object<PhysicalMaterial>>` | — | `Weather Properties` | — | — | InstanceEditable, Private |
| `Radial Storm Probabilities (Spring)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `()` | `Weather Properties` | — | — | InstanceEditable, Private |
| `Radial Storm Probabilities (Summer)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `()` | `Weather Properties` | — | — | InstanceEditable, Private |
| `Radial Storm Probabilities (Autumn)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `()` | `Weather Properties` | — | — | InstanceEditable, Private |
| `Radial Storm Probabilities (Winter)` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `()` | `Weather Properties` | — | — | InstanceEditable, Private |

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

Hard refs out (4):
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_SharedConfig` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_SharedConfig.UDS_SharedConfig_C` [Blueprint]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings` [asset]
- `/Script/PhysicsCore` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

