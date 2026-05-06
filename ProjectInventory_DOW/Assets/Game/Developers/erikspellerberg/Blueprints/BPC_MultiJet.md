# BPC_MultiJet

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Developers/erikspellerberg/Blueprints/BPC_MultiJet.BPC_MultiJet` |
| Asset name | `BPC_MultiJet` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `SceneComponent` (`/Script/Engine.SceneComponent`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (10)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Debug Draw Arrow` | `bool` | `False` | `Debug` | — | — | InstanceEditable |
| `Debug Arrow Color` | `real<double>` | `-1.000000` | `Debug` | — | — | InstanceEditable |
| `Debug Arrow Length` | `real<double>` | `-1.000000` | `Debug` | — | — | InstanceEditable |
| `Thrust` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Arrow Settings` | `struct<DrawDebugArrowSettings>` | `(ArrowHeadStartSize=5.000000,bArrowheadOnEnd=True,ArrowHeadEndSize=5.000000)` | `Default` | — | — | InstanceEditable, Private |
| `Positions and Rotations` | `TMap<struct<Rotator>>, struct:/Script/CoreUObject.Rotator>` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Divide Force` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Rocket` | `object<PrimitiveComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Positions and Vectors` | `TMap<struct<Vector>>, struct:/Script/CoreUObject.Vector>` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Rocket Rotation` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |

## Functions (1)

### `Debug Draw`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector>& Location [ref], struct<Rotator>& Rotation [ref])`
- Outputs: `()`
- Local variables (1): `NewLocalVar`
- Nodes: 18

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `PrimaryComponentTick` (`FActorComponentTickFunction`) = `(bCanEverTick=True)`

## Graphs

- Event graph: `EventGraph` (34 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (2):
- `/Script/DrawDebugLibrary` [asset]
- `/Script/Engine.SceneComponent` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

