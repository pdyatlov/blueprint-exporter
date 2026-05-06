# iInteractable

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Standards/Interactables/iInteractable.iInteractable` |
| Asset name | `iInteractable` |
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

### `Interact`

- Access: `Public`
- Flags: —
- Inputs: `(struct<sInteractionData> InteractionData)`
- Outputs: `(bool WasBlocked)`
- Local variables: _none_
- Nodes: 2

### `ManageNotifiersRegistry`

- Access: `Public`
- Flags: —
- Inputs: `(byte Action = NewEnumerator0)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Description: Manages if the interaction should be registered for user detection in the world.

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
- `/Game/Standards/Interactables/eInteractionRegisterAction` [asset]
- `/Game/Standards/Interactables/sInteractionData` [asset]
- `/Script/CoreUObject.Interface` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Interface`
- Subclass: `Blueprint`
- Custom metadata: _none_

