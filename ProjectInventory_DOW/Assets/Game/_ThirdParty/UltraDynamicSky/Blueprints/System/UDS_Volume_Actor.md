# UDS_Volume_Actor

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Volume_Actor.UDS_Volume_Actor` |
| Asset name | `UDS_Volume_Actor` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (7)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Collision Shape` | `byte<UDS_OcclusionShape>` | `NewEnumerator0` | `Shape` | — | — | InstanceEditable |
| `Box Extent` | `struct<Vector>` | `(X=100.000000,Y=100.000000,Z=100.000000)` | `Shape` | — | — | InstanceEditable |
| `Sphere Radius` | `real<double>` | `100.000000` | `Shape` | — | — | InstanceEditable |
| `Capsule Half Height` | `real<float>` | `200.000000` | `Shape` | — | — | InstanceEditable |
| `Blend Radius` | `real<double>` | `0.000000` | `Shape` | — | — | InstanceEditable |
| `Collision Component` | `object<PrimitiveComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Collision Object Type` | `byte<ECollisionChannel>` | `ECC_PhysicsBody` | `System` | — | — | InstanceEditable, Private |

## Functions (3)

### `Disable Volume`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Default`
- Description: Call at runtime to disable the occlusion volume

### `Enable Volume`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Default`
- Description: Call at runtime to enable the occlusion volume

### `Query Blend Radius`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Location)`
- Outputs: `(real<double> Multiplier, real<double> Multiplier, real<double> Multiplier, real<double> Multiplier)`
- Local variables (1): `Local Location`
- Nodes: 49

## Macros (0)

_None._

## Components (1)

- `Billboard` — `BillboardComponent` @ socket `None`

## Class Default Object (1)

- `PrimaryActorTick` (`FActorTickFunction`) = `(bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (1 nodes)
- Construction script: `UserConstructionScript` (31 nodes)
- Additional graphs: _none_

## References

Hard refs out (3):
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_OcclusionShape` [asset]
- `/Script/Engine.Actor` [native]
- `/Script/NavigationSystem` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

