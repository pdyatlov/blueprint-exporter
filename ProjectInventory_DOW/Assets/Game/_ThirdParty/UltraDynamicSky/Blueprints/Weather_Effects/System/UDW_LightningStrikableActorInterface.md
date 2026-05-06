# UDW_LightningStrikableActorInterface

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_LightningStrikableActorInterface.UDW_LightningStrikableActorInterface` |
| Asset name | `UDW_LightningStrikableActorInterface` |
| Subclass | `Blueprint` |
| Blueprint type | `Interface` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Interface` (`/Script/CoreUObject.Interface`, native, module `/Script/CoreUObject`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (2)

### `Struck By Lightning`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1
- Description: Called by UDW when this actor is struck by lightning.

### `Test for Potential Lightning Strike`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Can Be Struck By Lightning, struct<Vector> Lightning Strike World Location)`
- Local variables: _none_
- Nodes: 2
- Description: Used by UDW to test if an actor with this interface can be struck by lightning, and where in world space the lightning strike should hit the actor.

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

Hard refs out (1):
- `/Script/CoreUObject.Interface` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Interface`
- Subclass: `Blueprint`
- Custom metadata: _none_

