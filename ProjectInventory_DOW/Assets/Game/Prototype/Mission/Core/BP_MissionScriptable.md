# BP_MissionScriptable

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Prototype/Mission/Core/BP_MissionScriptable.BP_MissionScriptable` |
| Asset name | `BP_MissionScriptable` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces (1):
  - `/Game/Prototype/Mission/BlueprintInterface/BPI_MissionScripting.BPI_MissionScripting_C`

## Variables (10)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `e_Activated` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `e_EventOngoing` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `e_EventFinished` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `AutoActivate` | `bool` | `False` | `Default` | — | — | InstanceEditable |
| `e_Deactivated` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `OnActivatedTargets` | `TMap<object<S_ActivationType>>, struct:/Game/Prototype/Mission/Structs/S_ActivationType.S_ActivationType>` | `()` | `Default` | — | — | InstanceEditable |
| `OnDeactivatedTargets` | `TMap<object<S_ActivationType>>, struct:/Game/Prototype/Mission/Structs/S_ActivationType.S_ActivationType>` | `()` | `Default` | — | — | InstanceEditable |
| `DebugDrawLines` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Timescale` | `real<double>` | `3.000000` | `Default` | — | — | InstanceEditable, Private |
| `DebugPrint` | `string` | — | `Default` | — | — | InstanceEditable |

## Functions (1)

### `SendActivationMessage`

- Interface override of `/Game/Prototype/Mission/BlueprintInterface/BPI_MissionScripting.BPI_MissionScripting_C`
- Access: `Public`
- Flags: —
- Inputs: `(struct<S_ActivationType> ActivationInfo)`
- Outputs: `(struct<S_ActivationType> PassedActivationType)`
- Local variables: _none_
- Nodes: 8

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (21 nodes)
- Construction script: `UserConstructionScript` (23 nodes)
- Additional graphs: _none_

## References

Hard refs out (5):
- `/Game/Blueprints/EditorUtilities/EU_MacroLib` [asset]
- `/Game/Prototype/Mission/BlueprintInterface/BPI_MissionScripting` [asset]
- `/Game/Prototype/Mission/Enums/E_ActivationType` [asset]
- `/Game/Prototype/Mission/Structs/S_ActivationType` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

