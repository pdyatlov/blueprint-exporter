# UDS_InterfaceActorArrayManager

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArrayManager.UDS_InterfaceActorArrayManager` |
| Asset name | `UDS_InterfaceActorArrayManager` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ActorComponent` (`/Script/Engine.ActorComponent`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (8)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Interface` | `class<Class>` | `None` | `Default` | — | — | InstanceEditable |
| `Should Filter Array` | `bool` | `True` | `Default` | — | — | InstanceEditable |
| `All Actors` | `TArray<object<Actor>>` | — | `Default` | — | — | InstanceEditable, Private |
| `Filtered and Sorted Actors` | `TArray<object<Actor>>` | — | `Default` | — | — | InstanceEditable, Private |
| `Filtered Array Changed` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Started` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Should Sort Array` | `bool` | `True` | `Default` | — | — | InstanceEditable |
| `Full Array Changed` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |

## Functions (5)

### `Actor in Array End Play`

- Access: `Public`
- Flags: —
- Inputs: `(object<Actor> Actor, byte EndPlayReason = Destroyed)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

### `Add New Actor`

- Access: `Public`
- Flags: —
- Inputs: `(object<Actor> Actor)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 18

### `Editor Acquire Arrays`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

### `Filter and Sort Array`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Changed, bool Changed)`
- Local variables (5): `Unsorted Array`, `Unsorted Priorities`, `Next Index`, `Filtering Location`, `Old Array`
- Nodes: 66

### `Start Manager`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `PrimaryComponentTick` (`FActorComponentTickFunction`) = `(bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (4):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArray_ManagedActor` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_InterfaceActorArrayOwner_Interface` [asset]
- `/Script/Engine.ActorComponent` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

