# Light_Day-Night_Toggle

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Utilities/Light_Day-Night_Toggle.Light_Day-Night_Toggle` |
| Asset name | `Light_Day-Night_Toggle` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `SceneComponent` (`/Script/Engine.SceneComponent`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (19)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Light On At Night` | `bool` | `True` | `Settings` | — | — | InstanceEditable |
| `Random Delay` | `real<double>` | `1.000000` | `Settings` | — | — | InstanceEditable |
| `Dynamic Material Instances` | `TArray<object<MaterialInstanceDynamic>>` | — | `Settings` | — | — | InstanceEditable, Private |
| `Animate Light Turning On` | `bool` | `True` | `Settings` | — | — | InstanceEditable |
| `Turn On Animation Length` | `real<double>` | `1.500000` | `Settings` | — | — | InstanceEditable |
| `Animation Intensity Curve Exponent` | `real<double>` | `0.600000` | `Settings` | — | — | InstanceEditable |
| `Turn On Animation Flicker` | `real<double>` | `0.200000` | `Settings` | — | — | InstanceEditable |
| `Light Component` | `object<LightComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Light Max Intensity` | `real<float>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Light Animation Timer` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Animation Alpha` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Random Value` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `0-1 Intensity` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Light Turn On` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Light Turn Off` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `UDS Ref Manager` | `object<UDS_Actor_Reference_Manager_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Enabled Sunset State` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `Latent On/Off Timer` | `struct<TimerHandle>` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Tick Timer` | `struct<TimerHandle>` | `()` | `Default` | — | — | InstanceEditable, Private |

## Functions (7)

### `Bind to UDS`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14

### `Instant Update`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 23

### `Latent On/Off`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 25

### `Sunset/Sunrise Function`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

### `Tick Light Animation`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 45

### `Turn Off Light`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

### `Turn On Light`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `PrimaryComponentTick` (`FActorComponentTickFunction`) = `(bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (17 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (3):
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Actor_Reference_Manager` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` [asset]
- `/Script/Engine.SceneComponent` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

