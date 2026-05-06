# STT_PlayAnimFromBestCost

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/TasksAndConditions/STT_PlayAnimFromBestCost.STT_PlayAnimFromBestCost` |
| Asset name | `STT_PlayAnimFromBestCost` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `StateTreeTaskBlueprintBase` (`/Script/StateTreeModule.StateTreeTaskBlueprintBase`, native, module `/Script/StateTreeModule`)
- Interfaces: _none_

## Variables (10)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Actor` | `object<Actor>` | `None` | `Context` | — | — | InstanceEditable, Private |
| `Animation Proxy Table` | `object<ProxyTable>` | `None` | `Default` | — | — | InstanceEditable |
| `CostThreshold` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable |
| `Claimed Handle` | `struct<SmartObjectClaimHandle>` | `()` | `Input` | — | — | InstanceEditable |
| `Destination` | `struct<Transform>` | `(Rotation=(X=0.000000,Y=0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000))` | `Input` | — | — | InstanceEditable, Private |
| `MaximumDistanceThreshold` | `real<double>` | `300.000000` | `Default` | — | — | InstanceEditable |
| `Smart Object Animation Component` | `object<AC_SmartObjectAnimation_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Minimum Velocity Check` | `real<double>` | `100.000000` | `Default` | — | — | InstanceEditable |
| `Needs Evaluation` | `bool` | `True` | `Default` | — | — | InstanceEditable, Private |
| `PossibleOwnerMoverComponent` | `object<MoverComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |

## Functions (3)

### `Get Actor Velocity`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> Velocity, struct<Vector> Velocity)`
- Local variables: _none_
- Nodes: 9

### `NPC Approach Angle and Pathed Distance`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Distance, real<double> Distance)`
- Local variables (1): `Slot Transform`
- Nodes: 15

### `Setup Task`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 17

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (57 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (10):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/AC_SmartObjectAnimation` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/SmartObjectAnimationPayload` [asset]
- `/Script/AIModule` [asset]
- `/Script/Mover` [asset]
- `/Script/NavigationSystem` [asset]
- `/Script/ProxyTable` [asset]
- `/Script/SmartObjectsModule` [asset]
- `/Script/StateTreeModule` [asset]
- `/Script/StateTreeModule.StateTreeTaskBlueprintBase` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

