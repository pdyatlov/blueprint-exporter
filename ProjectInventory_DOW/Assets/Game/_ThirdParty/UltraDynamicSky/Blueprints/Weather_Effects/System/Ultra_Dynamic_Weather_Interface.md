# Ultra_Dynamic_Weather_Interface

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Ultra_Dynamic_Weather_Interface.Ultra_Dynamic_Weather_Interface` |
| Asset name | `Ultra_Dynamic_Weather_Interface` |
| Subclass | `Blueprint` |
| Blueprint type | `Interface` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Interface` (`/Script/CoreUObject.Interface`, native, module `/Script/CoreUObject`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (21)

### `Editor Return from PIE`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2
- Category: `Editor`

### `Editor Tick`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Delta Time)`
- Outputs: `(bool Completed)`
- Local variables: _none_
- Nodes: 2
- Category: `Editor`

### `Editor Update Season`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2
- Category: `Editor`

### `Force Custom Weather Behavior Update`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2
- Category: `Update`

### `Get Current Season`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Season)`
- Local variables: _none_
- Nodes: 2
- Category: `Season`

### `Get Dust Material Change Timing`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Coverage Duration, real<double> Clear Duration, real<double> Clear Speed (Windy), real<double> Clear Speed (No Wind))`
- Local variables: _none_
- Nodes: 2
- Category: `Material Effects`

### `Get Global Temp Above Freezing`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Above Freezing)`
- Local variables: _none_
- Nodes: 2
- Category: `Temperature`

### `Get Individual Seasons`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(TArray<real<double>> Seasons)`
- Local variables: _none_
- Nodes: 2
- Category: `Season`

### `Get Snow Material Change Timing`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Coverage Duration, real<double> Melt Duration, real<double> Melt Speed (Above Freezing), real<double> Melt Speed (Below Freezing))`
- Local variables: _none_
- Nodes: 2
- Category: `Material Effects`

### `Get Temperature Bias Settings`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Nighttime Bias, real<double> Daytime  Bias, real<double> Overcast Bias, real<double> Rain Bias, real<double> Snow Bias, real<double> Fog Bias, real<double> Dust Bias, real<double> Morning/Evening Bias)`
- Local variables: _none_
- Nodes: 2
- Category: `Temperature`

### `Get UDS Values Controlled by UDW`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Cloud Coverage, real<double> Fog, real<double> Dust Amount, real<double> Cloud Direction, real<double> Wind Intensity, real<double> Rain, real<double> Snow, real<double> Fog Snow Contribution)`
- Local variables: _none_
- Nodes: 2
- Category: `Weather State`
- Description: Used by UDS to get values from UDW controlled by the weather state

### `Get UDS Weather Override Bool`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Cloud Coverage, bool Fog, bool Dust)`
- Local variables: _none_
- Nodes: 2
- Category: `Weather State`

### `Get UDW Current UDS Reference`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(object<Ultra_Dynamic_Sky_C> UDS)`
- Local variables: _none_
- Nodes: 2
- Category: `System`

### `Get UDW State for Saving`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<UDS_and_UDW_State> UDW State)`
- Local variables: _none_
- Nodes: 2
- Category: `Saving/Loading`

### `Get Weather Speed`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 2
- Category: `System`

### `Get Wetness Material Change Timing`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Coverage Duration, real<double> Dry Duration, real<double> Dry Speed (Sunny), real<double> Dry Speed (Cloudy), real<double> Snow Melt Contributes to Wetness)`
- Local variables: _none_
- Nodes: 2
- Category: `Material Effects`

### `Initialize Weather`

- Access: `Public`
- Flags: —
- Inputs: `(object<Ultra_Dynamic_Sky_C> UDS)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1
- Category: `Startup`

### `Request Global Weather Binding Update`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1
- Category: `Weather State`

### `UDS Weather Variable Overrides`

- Access: `Public`
- Flags: —
- Inputs: `(bool Override Clouds, real<double> Cloud Coverage, bool Override Fog, real<double> Fog, bool Override Dust, real<double> Dust)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2
- Category: `Weather State`

### `UDW Runtime Tick`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Delta Time)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1
- Category: `Update`

### `UDW State Apply`

- Access: `Public`
- Flags: —
- Inputs: `(struct<UDS_and_UDW_State> State)`
- Outputs: `(bool Completed)`
- Local variables: _none_
- Nodes: 2
- Category: `Saving/ Loading`

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (3):
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_and_UDW_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` [asset]
- `/Script/CoreUObject.Interface` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Interface`
- Subclass: `Blueprint`
- Custom metadata: _none_

