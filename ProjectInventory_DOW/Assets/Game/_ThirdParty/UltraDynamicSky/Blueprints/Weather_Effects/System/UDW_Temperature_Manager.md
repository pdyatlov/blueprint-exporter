# UDW_Temperature_Manager

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Temperature_Manager.UDW_Temperature_Manager` |
| Asset name | `UDW_Temperature_Manager` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ActorComponent` (`/Script/Engine.ActorComponent`, native, module `/Script/Engine`)
- Interfaces (1):
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Temperature_Manager_Interface.UDW_Temperature_Manager_Interface_C`

## Variables (8)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `UDW` | `object<Actor>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Weather State` | `object<UDS_Weather_Settings_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Temperature Range` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `Update Period` | `real<double>` | `1.000000` | `Default` | — | — | InstanceEditable, Private |
| `Last Temperature Update Time` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Last Temperature` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Target Temperature` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Update Timer` | `struct<TimerHandle>` | `()` | `Default` | — | — | InstanceEditable, Private |

## Functions (6)

### `Calculate Temperature`

- Access: `Protected`
- Flags: —
- Inputs: `(object<UDS_Weather_Settings_C> Settings)`
- Outputs: `(real<double> Temperature)`
- Local variables (11): `Bias Value`, `Unconverted Temperature`, `Night Bias`, `Day Bias`, `Overcast Bias`, `Rain Bias`, `Snow Bias`, `Fog Bias`, `Dust Bias`, `Morning/Evening Bias`, `UDS`
- Nodes: 97
- Category: `Default`

### `Get Current Min and Max Temperature`

- Access: `Protected`
- Flags: —
- Inputs: `(struct<Vector2D> Spring Min and Max, struct<Vector2D> Summer Min and Max, struct<Vector2D> Autumn Min and Max, struct<Vector2D> Winter Min and Max)`
- Outputs: `(struct<Vector2D> Range)`
- Local variables (4): `Seasons Min and Max Values`, `Min Temperature`, `Max Temperature`, `Individual Seasons`
- Nodes: 23
- Category: `Default`

### `Get Current Value`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Temperature_Manager_Interface.UDW_Temperature_Manager_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 11

### `Instant Update Temperature`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4

### `Update Target Temperature`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

### `Update Temperature Range`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `PrimaryComponentTick` (`FActorComponentTickFunction`) = `(bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (19 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (7):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_and_Weather_Override_Volume_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Temperature_Manager_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface` [asset]
- `/Script/Engine.ActorComponent` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

