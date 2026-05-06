# Actor_Weather_Status

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Actor_Weather_Status.Actor_Weather_Status` |
| Asset name | `Actor_Weather_Status` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ActorComponent` (`/Script/Engine.ActorComponent`, native, module `/Script/Engine`)
- Interfaces (1):
  - `/Script/Niagara.NiagaraParticleCallbackHandler`

## Variables (57)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `UDW` | `object<Ultra_Dynamic_Weather_C>` | `None` | `System` | — | — | InstanceEditable, Private |
| `Temperature (C)` | `real<double>` | `0.000000` | `Status` | — | — | InstanceEditable, Private |
| `Temperature (F)` | `real<double>` | `0.000000` | `Status` | — | — | InstanceEditable, Private |
| `Exposure Test Bounds` | `byte<UDS_ActorWeatherBoundsMode>` | `NewEnumerator0` | `Settings` | — | — | InstanceEditable |
| `Weather Exposure Collision Channel` | `byte<ECollisionChannel>` | `ECC_Visibility` | `Settings` | — | — | InstanceEditable |
| `Max Trace Distance` | `real<double>` | `4000.000000` | `Settings` | — | — | InstanceEditable |
| `Temperature Change Speed` | `real<double>` | `25.000000` | `Settings` | — | — | InstanceEditable |
| `Status Query Period` | `real<double>` | `1.250000` | `Settings` | — | — | InstanceEditable |
| `Update Values Period` | `real<double>` | `0.050000` | `Settings` | — | — | InstanceEditable |
| `Max Wet Value` | `real<double>` | `1.000000` | `Settings` | — | — | InstanceEditable |
| `Wet` | `real<double>` | `0.000000` | `Status` | — | — | InstanceEditable, Private |
| `Snowy` | `real<double>` | `0.000000` | `Status` | — | — | InstanceEditable, Private |
| `Dusty` | `real<double>` | `0.000000` | `Status` | — | — | InstanceEditable, Private |
| `Target Temp (F)` | `real<double>` | `0.000000` | `System` | — | — | InstanceEditable, Private |
| `Dynamic Material Instances` | `TArray<object<MaterialInstanceDynamic>>` | — | `Material Effects` | — | — | InstanceEditable, Private |
| `Max Snowy Value` | `real<double>` | `1.000000` | `Settings` | — | — | InstanceEditable |
| `Max Dusty Value` | `real<double>` | `0.500000` | `Settings` | — | — | InstanceEditable |
| `Wet Increase Speed` | `real<double>` | `1.000000` | `Settings` | — | — | InstanceEditable |
| `Wet Decrease Speed` | `real<double>` | `-0.015000` | `Settings` | — | — | InstanceEditable |
| `Snowy Increase Speed` | `real<double>` | `0.030000` | `Settings` | — | — | InstanceEditable |
| `Snowy Decrease Speed` | `real<double>` | `-0.015000` | `Settings` | — | — | InstanceEditable |
| `Dusty Increase Speed` | `real<double>` | `0.100000` | `Settings` | — | — | InstanceEditable |
| `Dusty Decrease Speed` | `real<double>` | `-0.015000` | `Settings` | — | — | InstanceEditable |
| `Wind` | `real<double>` | `0.000000` | `Status` | — | — | InstanceEditable, Private |
| `Hit by Rain` | `real<double>` | `0.000000` | `Status` | — | — | InstanceEditable, Private |
| `Hit by Snow` | `real<double>` | `0.000000` | `Status` | — | — | InstanceEditable, Private |
| `Hit by Dust` | `real<double>` | `0.000000` | `Status` | — | — | InstanceEditable, Private |
| `Exposed to Rain` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Not Exposed to Rain` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Exposed to Snow` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Not Exposed to Snow` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Exposed to Dust` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Not Exposed to Dust` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Temperature Cold` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Temperature Neutral` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Temperature Hot` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `ED_Rain Exposed` | `bool` | `False` | `Event Dispatchers` | — | — | InstanceEditable, Private |
| `ED_Snow Exposed` | `bool` | `False` | `Event Dispatchers` | — | — | InstanceEditable, Private |
| `ED_Dust Exposed` | `bool` | `False` | `Event Dispatchers` | — | — | InstanceEditable, Private |
| `ED_Wind Exposed` | `bool` | `False` | `Event Dispatchers` | — | — | InstanceEditable, Private |
| `Exposed to Wind` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Not Exposed to Wind` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `ED_Temperature State` | `int` | `-1` | `Event Dispatchers` | — | — | InstanceEditable, Private |
| `Rain Event Dispatcher Threshold` | `real<double>` | `0.100000` | `Settings` | — | — | InstanceEditable |
| `Snow Event Dispatcher Threshold` | `real<double>` | `0.100000` | `Settings` | — | — | InstanceEditable |
| `Dust Event Dispatcher Threshold` | `real<double>` | `0.100000` | `Settings` | — | — | InstanceEditable |
| `Wind Event Dispatcher Threshold` | `real<double>` | `0.500000` | `Settings` | — | — | InstanceEditable |
| `Cold Temperature Threshold` | `real<double>` | `25.000000` | `Settings` | — | — | InstanceEditable |
| `Hot Temperature Threshold` | `real<double>` | `95.000000` | `Settings` | — | — | InstanceEditable |
| `Drip Systems` | `TArray<object<NiagaraComponent>>` | — | `Drips` | — | — | InstanceEditable, Private |
| `Controlling Drip Systems` | `bool` | `False` | `Drips` | — | — | InstanceEditable, Private |
| `Local Temperature Offset (F)` | `real<double>` | `0.000000` | `Settings` | — | — | InstanceEditable |
| `Tester System` | `object<NiagaraComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Max Active DIstance` | `real<double>` | `5000.000000` | `Settings` | — | — | InstanceEditable |
| `Composite Exposure` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `System` | — | — | InstanceEditable, Private |
| `Tick Delta Seconds` | `real<float>` | `0.000000` | `System` | — | — | InstanceEditable, Private |
| `Temperature Local to Actor Location` | `bool` | `False` | `Settings` | — | — | InstanceEditable |

## Functions (11)

### `Activated`

- Access: `Protected`
- Flags: —
- Inputs: `(object<ActorComponent> Component, bool bReset)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `Bind to UDW`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

### `Check for Drip Particles`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 16

### `Deactivated`

- Access: `Protected`
- Flags: —
- Inputs: `(object<ActorComponent> Component)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `Get Target Temperature`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

### `Increment Surface State`

- Access: `Protected`
- Flags: —
- Inputs: `(real<double> Exposure, real<double> Increase Speed, real<double> Decrease Speed, real<double> Max Value, real<double> Current Value, real<double> Delta)`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 15

### `Instant Update`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

### `Make Tester System`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Only Colliding Components`
- Nodes: 47

### `Second Phase Status Updates`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4

### `Trigger Event Dispatchers`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 68

### `Update Current Status`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 68
- Description: Updates the status variables for temperature, wet, snowy, etc. Also applies these changes to the parameters on the materials in the Dynamic Material Instances array.

## Macros (1)

### `Get UDW Reference`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (2)

- `bAutoActivate` (`uint8`) = `True`
- `PrimaryComponentTick` (`FActorComponentTickFunction`) = `(bCanEverTick=True,bStartWithTickEnabled=False,TickInterval=0.050000)`

## Graphs

- Event graph: `EventGraph` (50 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (8):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_ActorWeatherBoundsMode` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Temperature_Sample_Location` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_TemperatureType` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Particles/Actor_Exposure_Test` [asset]
- `/Script/Engine.ActorComponent` [native]
- `/Script/Niagara` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

