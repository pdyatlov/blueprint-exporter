# BPI_MissionScripting

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Prototype/Mission/BlueprintInterface/BPI_MissionScripting.BPI_MissionScripting` |
| Asset name | `BPI_MissionScripting` |
| Subclass | `Blueprint` |
| Blueprint type | `Interface` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Interface` (`/Script/CoreUObject.Interface`, native, module `/Script/CoreUObject`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (4)

### `ActorActivate`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Delay)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1

### `ActorDeactivate`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Delay)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1

### `SendActivationMessage`

- Access: `Public`
- Flags: —
- Inputs: `(struct<S_ActivationType> ActivationInfo)`
- Outputs: `(struct<S_ActivationType> PassedActivationType)`
- Local variables: _none_
- Nodes: 2

### `SetScriptedActorTarget`

- Access: `Public`
- Flags: —
- Inputs: `(TMap<object<E_ActivationType>>, byte> TargetActors)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1

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
- `/Game/Prototype/Mission/Enums/E_ActivationType` [asset]
- `/Game/Prototype/Mission/Structs/S_ActivationType` [asset]
- `/Script/CoreUObject.Interface` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Interface`
- Subclass: `Blueprint`
- Custom metadata: _none_

