# UDW_Local_Weather_Actor_Interface

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Local_Weather_Actor_Interface.UDW_Local_Weather_Actor_Interface` |
| Asset name | `UDW_Local_Weather_Actor_Interface` |
| Subclass | `Blueprint` |
| Blueprint type | `Interface` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Interface` (`/Script/CoreUObject.Interface`, native, module `/Script/CoreUObject`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (6)

### `Apply WOV State`

- Access: `Public`
- Flags: —
- Inputs: `(struct<UDW_WOV_State> State)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2
- Category: `Local Weather Actor`

### `Bind Local Weather Update Function to UDW`

- Access: `Public`
- Flags: —
- Inputs: `(object<Ultra_Dynamic_Weather_C> UDW)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2
- Category: `Local Weather Actor`

### `Check to Change Temperature Scale`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2
- Category: `Local Weather Actor`

### `Full Reconstruction`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2
- Category: `Local Weather Actor`

### `Get Saved WOV State`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Has Valid State, struct<UDW_WOV_State> State)`
- Local variables: _none_
- Nodes: 2
- Category: `Local Weather Actor`

### `Get WOV Random Weather Forecast`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Player is Inside, TArray<object<UDS_Weather_Settings_C>> Array)`
- Local variables: _none_
- Nodes: 2
- Category: `Local Weather Actor`

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

Hard refs out (4):
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WOV_State` [asset]
- `/Script/CoreUObject.Interface` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Interface`
- Subclass: `Blueprint`
- Custom metadata: _none_

