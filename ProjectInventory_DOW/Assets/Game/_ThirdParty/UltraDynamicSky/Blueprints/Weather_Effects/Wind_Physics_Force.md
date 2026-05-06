# Wind_Physics_Force

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Wind_Physics_Force.Wind_Physics_Force` |
| Asset name | `Wind_Physics_Force` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `SceneComponent` (`/Script/Engine.SceneComponent`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (13)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Physics Component` | `object<PrimitiveComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Max Wind Force` | `real<double>` | `10000.000000` | `Force Settings` | — | — | InstanceEditable |
| `Apply Force at Component Location` | `bool` | `False` | `Force Settings` | — | — | InstanceEditable |
| `Wind Intensity to Force Exponent` | `real<double>` | `4.000000` | `Force Settings` | — | — | InstanceEditable |
| `Update Force Period` | `real<double>` | `1.300000` | `Force Settings` | — | — | InstanceEditable |
| `Randomize Wind Angle Each Update` | `real<double>` | `35.000000` | `Force Settings` | — | — | InstanceEditable |
| `Wind Force Vector` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `System` | — | — | InstanceEditable, Private |
| `Bone Name` | `name` | `None` | `Force Settings` | — | — | InstanceEditable |
| `Test for Collision Blocking Wind` | `bool` | `True` | `Force Settings` | — | — | InstanceEditable |
| `Wind Exposure Test Trace Channel` | `byte<ETraceTypeQuery>` | `TraceTypeQuery1` | `Force Settings` | — | — | InstanceEditable |
| `Max Trace Distance` | `real<double>` | `4000.000000` | `Force Settings` | — | — | InstanceEditable |
| `Update Timer` | `struct<TimerHandle>` | `()` | `System` | — | — | InstanceEditable, Private |
| `Apply Timer` | `struct<TimerHandle>` | `()` | `System` | — | — | InstanceEditable, Private |

## Functions (5)

### `Activated`

- Access: `Protected`
- Flags: —
- Inputs: `(object<ActorComponent> Component, bool bReset)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

### `Apply Force`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 18

### `Deactivated`

- Access: `Protected`
- Flags: —
- Inputs: `(object<ActorComponent> Component)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

### `Startup Timers`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9

### `Update Force Vector`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (3): `Wind Direction`, `Wind Intensity`, `Wind Exposure`
- Nodes: 56

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (2)

- `bAutoActivate` (`uint8`) = `True`
- `PrimaryComponentTick` (`FActorComponentTickFunction`) = `(bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (12 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (2):
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/UltraDynamicWeather_Parameters` [asset]
- `/Script/Engine.SceneComponent` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

