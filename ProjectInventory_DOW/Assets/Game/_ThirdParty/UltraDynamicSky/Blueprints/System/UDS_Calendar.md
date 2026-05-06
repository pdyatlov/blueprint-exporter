# UDS_Calendar

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Calendar.UDS_Calendar` |
| Asset name | `UDS_Calendar` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `PrimaryDataAsset` (`/Script/Engine.PrimaryDataAsset`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (12)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Months` | `TMap<string, ?>` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Uses Leap Year` | `bool` | `True` | `Default` | — | — | InstanceEditable, Private |
| `Leap Year Month` | `int` | `2` | `Default` | — | — | InstanceEditable, Private |
| `Winter Solstice Offset` | `int` | `-11` | `Default` | — | — | InstanceEditable, Private |
| `Days of the Week` | `TArray<string>` | `("Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday")` | `Default` | — | — | InstanceEditable, Private |
| `Day of the Week Offset` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `Month Lengths` | `TArray<int>` | — | `Derived Data` | — | — | InstanceEditable, Private |
| `Day Count At Start of Each Month` | `TArray<int>` | — | `Derived Data` | — | — | InstanceEditable, Private |
| `Day Count At Start of Each Month (Leap Year)` | `TArray<int>` | — | `Derived Data` | — | — | InstanceEditable, Private |
| `Month Lengths (Leap Year)` | `TArray<int>` | — | `Derived Data` | — | — | InstanceEditable, Private |
| `Number of Days in Year` | `int` | `0` | `Derived Data` | — | — | InstanceEditable, Private |
| `Calendar Data Saved` | `bool` | `False` | `Derived Data` | — | — | InstanceEditable, Private |

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

Hard refs out (1):
- `/Script/Engine.PrimaryDataAsset` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

