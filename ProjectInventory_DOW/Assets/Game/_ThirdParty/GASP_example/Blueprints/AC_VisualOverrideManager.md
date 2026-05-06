# AC_VisualOverrideManager

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/AC_VisualOverrideManager.AC_VisualOverrideManager` |
| Asset name | `AC_VisualOverrideManager` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ActorComponent` (`/Script/Engine.ActorComponent`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (1)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `VisualOverride` | `class<Class>` | `None` | `Default` | Replicated | `OnRep_VisualOverride` | InstanceEditable |

## Functions (4)

### `ApplyVisualOverride`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `VisualOverridesList`
- Nodes: 12
- Category: `Default`

### `FindAndApplyVisualOverride`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `VisualOverridesList`
- Nodes: 8

### `ForceVisualOverride`

- Access: `Public`
- Flags: —
- Inputs: `(class<Class> Class)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14

### `OnRep_VisualOverride`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (11 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (5):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/BFL_HelpfulFunctions` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/GM_Sandbox` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/PlayerPawn/SandboxCharacter_Mover` [asset]
- `/Script/Engine.ActorComponent` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

