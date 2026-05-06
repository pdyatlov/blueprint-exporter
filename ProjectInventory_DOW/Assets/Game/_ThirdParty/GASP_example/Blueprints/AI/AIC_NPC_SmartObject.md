# AIC_NPC_SmartObject

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/AI/AIC_NPC_SmartObject.AIC_NPC_SmartObject` |
| Asset name | `AIC_NPC_SmartObject` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `AIController` (`/Script/AIModule.AIController`, native, module `/Script/AIModule`)
- Interfaces: _none_

## Variables (1)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Cooldowns` | `TMap<string, ?>` | `()` | `Default` | — | — | InstanceEditable, Private |

## Functions (1)

### `Debug`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9

## Macros (0)

_None._

## Components (1)

- `StateTreeAI` — `StateTreeAIComponent` @ socket `None`

## Class Default Object (3)

- `PathFollowingComponent` (`TObjectPtr<UPathFollowingComponent>`) [instanced] = `/Script/AIModule.PathFollowingComponent'/Game/_ThirdParty/GASP_example/Blueprints/AI/AIC_NPC_SmartObject.Default__AIC...`
- `RootComponent` (`TObjectPtr<USceneComponent>`) [instanced] = `/Script/Engine.SceneComponent'/Game/_ThirdParty/GASP_example/Blueprints/AI/AIC_NPC_SmartObject.Default__AIC_NPC_Smart...`
- `TransformComponent` (`TObjectPtr<USceneComponent>`) [instanced] = `/Script/Engine.SceneComponent'/Game/_ThirdParty/GASP_example/Blueprints/AI/AIC_NPC_SmartObject.Default__AIC_NPC_Smart...`

## Graphs

- Event graph: `EventGraph` (7 nodes)
- Construction script: `UserConstructionScript` (1 nodes)
- Additional graphs: _none_

## References

Hard refs out (5):
- `/Game/_ThirdParty/GASP_example/Blueprints/AI/StateTree/ST_NPC_SandboxCharacter_SmartObject` [asset]
- `/Script/AIModule` [asset]
- `/Script/AIModule.AIController` [native]
- `/Script/DrawDebugLibrary` [asset]
- `/Script/GameplayStateTreeModule` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

