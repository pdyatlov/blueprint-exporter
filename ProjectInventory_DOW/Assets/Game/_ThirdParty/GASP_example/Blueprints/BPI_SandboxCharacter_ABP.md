# BPI_SandboxCharacter_ABP

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_ABP.BPI_SandboxCharacter_ABP` |
| Asset name | `BPI_SandboxCharacter_ABP` |
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

### `Get_Gait`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte ReturnValue)`
- Local variables: _none_
- Nodes: 2
- Category: `Getters`

### `Get_InteractionTransform`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Transform> ReturnValue)`
- Local variables: _none_
- Nodes: 2
- Category: `Getters`

### `Get_PoseHistory`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<PoseHistoryReference> ReturnValue)`
- Local variables: _none_
- Nodes: 2
- Category: `Getters`

### `Set_InteractionTransform`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Transform> InteractionTransform)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1
- Category: `Setters`

### `Set_NotifyTransition_ReTransition`

- Access: `Public`
- Flags: —
- Inputs: `(bool ReTransition)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1
- Category: `Setters`

### `Set_NotifyTransition_ToLoop`

- Access: `Public`
- Flags: —
- Inputs: `(bool ToLoop)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1
- Category: `Setters`

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
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_Gait` [asset]
- `/Script/CoreUObject.Interface` [native]
- `/Script/PoseSearch` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Interface`
- Subclass: `Blueprint`
- Custom metadata: _none_

