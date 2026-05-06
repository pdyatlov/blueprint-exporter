# UDW_Material_State_Manager

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Material_State_Manager.UDW_Material_State_Manager` |
| Asset name | `UDW_Material_State_Manager` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ActorComponent` (`/Script/Engine.ActorComponent`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (14)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `UDW` | `object<Actor>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Weather State` | `object<UDS_Weather_Settings_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Temperature Manager` | `object<UDW_Temperature_Manager_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Replicated Wetness` | `real<double>` | `-1.000000` | `Default` | Replicated | — | InstanceEditable, Private |
| `Replicated Material Snow` | `real<double>` | `-1.000000` | `Default` | Replicated | — | InstanceEditable, Private |
| `Replicated Material Dust` | `real<double>` | `-1.000000` | `Default` | Replicated | — | InstanceEditable, Private |
| `First Step` | `bool` | `True` | `Default` | — | — | InstanceEditable, Private |
| `Wetness Change Speed` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Snow Change Speed` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Dust Change Speed` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Change Speeds are Active` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Tick Delta Seconds` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Instant Updating` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `For Global State` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |

## Functions (9)

### `Apply New State`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Snow, real<double> Wetness, real<double> Dust)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

### `Current Dust Change Speed`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out, real<double> Out, real<double> Out, real<double> Out)`
- Local variables (4): `Coverage Duration`, `Clear Duration`, `Clear Speed (Windy)`, `Clear Speed (No Wind)`
- Nodes: 41

### `Current Snow Change Speed`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out, real<double> Out, real<double> Out, real<double> Out)`
- Local variables (4): `Coverage Duration`, `Melt Duration`, `Melt Speed (Above Freezing`, `Melt Speed (Below Freezing)`
- Nodes: 41

### `Current Wetness Change Speed`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out, real<double> Out, real<double> Out, real<double> Out, real<double> Out)`
- Local variables (5): `Coverage Duration`, `Dry Duration`, `Dry Speed Sunny`, `Dry Speed Cloudy`, `Snow Melt Contributes to Wetness`
- Nodes: 58

### `Increment Material State`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Tick Delta)`
- Outputs: `(bool Changed, bool Changed, bool Changed)`
- Local variables: _none_
- Nodes: 36

### `Instant Update`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

### `Start Material State Sim`

- Access: `Public`
- Flags: —
- Inputs: `(object<Actor> UDW, object<UDS_Weather_Settings_C> Weather State)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9

### `Update Change Speeds`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `New Active`
- Nodes: 26

### `Update Replicated State`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

## Macros (1)

### `Increment Material Value with Speed`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 24

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (2)

- `bReplicates` (`uint8`) = `True`
- `PrimaryComponentTick` (`FActorComponentTickFunction`) = `(bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (3 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (6):
- `/Engine/EditorBlueprintResources/ActorComponentMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Temperature_Manager` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/UltraDynamicWeather_Parameters` [asset]
- `/Script/Engine.ActorComponent` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

