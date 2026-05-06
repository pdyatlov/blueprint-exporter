# STT_FindRandomLocation

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/AI/StateTree/TasksAndConditions/STT_FindRandomLocation.STT_FindRandomLocation` |
| Asset name | `STT_FindRandomLocation` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `StateTreeTaskBlueprintBase` (`/Script/StateTreeModule.StateTreeTaskBlueprintBase`, native, module `/Script/StateTreeModule`)
- Interfaces: _none_

## Variables (3)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `AIReference` | `object<AIController>` | `None` | `Context` | — | — | InstanceEditable |
| `SearchRadius` | `real<float>` | `0.000000` | `Default` | — | — | InstanceEditable |
| `Random Location` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Output` | — | — | InstanceEditable, Private |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (2)

- `IconColor` (`FColor`) = `(B=74,G=194,R=139,A=255)`
- `IconName` (`FName`) = `EditorStyle|ShowFlagsMenu.Navigation`

## Graphs

- Event graph: `EventGraph` (10 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (4):
- `/Script/AIModule` [asset]
- `/Script/NavigationSystem` [asset]
- `/Script/StateTreeModule` [asset]
- `/Script/StateTreeModule.StateTreeTaskBlueprintBase` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

