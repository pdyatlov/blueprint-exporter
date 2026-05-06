# UDS_DLWE_Interaction_Settings

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_DLWE_Interaction_Settings.UDS_DLWE_Interaction_Settings` |
| Asset name | `UDS_DLWE_Interaction_Settings` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `PrimaryDataAsset` (`/Script/Engine.PrimaryDataAsset`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (17)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Affects DLWE Snow/Dust` | `bool` | `True` | `Basic Controls` | — | — | InstanceEditable |
| `Affects DLWE Puddles` | `bool` | `True` | `Basic Controls` | — | — | InstanceEditable |
| `Affect Puddle Fluid Volumes` | `bool` | `True` | `Basic Controls` | — | — | InstanceEditable |
| `Active Distance` | `real<double>` | `5000.000000` | `Basic Controls` | — | — | InstanceEditable |
| `Enable Puddle Sound Effects` | `bool` | `True` | `Sounds` | — | — | InstanceEditable |
| `Enable Snow Sound Effects` | `bool` | `True` | `Sounds` | — | — | InstanceEditable |
| `Enable Dust Sound Effects` | `bool` | `True` | `Sounds` | — | — | InstanceEditable |
| `Enable Puddle Splash Particles` | `bool` | `True` | `Particles` | — | — | InstanceEditable |
| `Enable Snow Particles` | `bool` | `True` | `Particles` | — | — | InstanceEditable |
| `Snow Sound Volume` | `real<double>` | `1.000000` | `Sounds` | — | — | InstanceEditable |
| `Puddle Sound Volume` | `real<double>` | `1.000000` | `Sounds` | — | — | InstanceEditable |
| `Dust Sound Volume` | `real<double>` | `1.000000` | `Sounds` | — | — | InstanceEditable |
| `Puddle Ripple Size` | `real<double>` | `15.000000` | `Interactions` | — | — | InstanceEditable, Private |
| `Physical Materials which enable DLWE Interactions on non-Landscapes` | `TArray<object<PhysicalMaterial>>` | — | `Interactions` | — | — | InstanceEditable |
| `Landscape Collision Object Types` | `TArray<byte<EObjectTypeQuery>>` | `(ObjectTypeQuery1)` | `Interactions` | — | — | InstanceEditable |
| `General Surface Impact Sounds` | `TMap<object<SoundBase>>, object:/Script/Engine.SoundBase>` | `()` | `General Surface Response` | — | — | InstanceEditable |
| `Max Sample Rate` | `real<double>` | `15.000000` | `Basic Controls` | — | — | InstanceEditable |

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

Hard refs out (2):
- `/Script/Engine.PrimaryDataAsset` [native]
- `/Script/PhysicsCore` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

