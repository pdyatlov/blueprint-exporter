# PC_Sandbox

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/PC_Sandbox.PC_Sandbox` |
| Asset name | `PC_Sandbox` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `PlayerController` (`/Script/Engine.PlayerController`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (6)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Characters` | `TArray<class<Class>>` | — | `Default` | — | — | InstanceEditable, Private |
| `Current Character Index` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `CachedControlRotation` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `TeleportMaxDistance` | `real<float>` | `10000.000000` | `Default` | — | — | InstanceEditable, Private |
| `LobbyUI` | `object<Object>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `In Visibility` | `byte<ESlateVisibility>` | `Hidden` | `Default` | — | — | InstanceEditable, Private |

## Functions (1)

### `TeleportToTarget`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (3): `TraceStart`, `TraceEnd`, `HitResult`
- Nodes: 23

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (3)

- `PlayerCameraManagerClass` (`TSubclassOf<APlayerCameraManager>`) = `/Script/CoreUObject.Class'/Script/Engine.PlayerCameraManager'`
- `RootComponent` (`TObjectPtr<USceneComponent>`) [instanced] = `/Script/Engine.SceneComponent'/Game/_ThirdParty/GASP_example/Blueprints/PC_Sandbox.Default__PC_Sandbox_C:TransformCom...`
- `TransformComponent` (`TObjectPtr<USceneComponent>`) [instanced] = `/Script/Engine.SceneComponent'/Game/_ThirdParty/GASP_example/Blueprints/PC_Sandbox.Default__PC_Sandbox_C:TransformCom...`

## Graphs

- Event graph: `EventGraph` (31 nodes)
- Construction script: `UserConstructionScript` (1 nodes)
- Additional graphs: _none_

## References

Hard refs out (11):
- `/Game/_ThirdParty/GASP_example/Blueprints/GM_Sandbox` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/SandboxCharacter_CMC` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_NextPawn` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_NextVisualOverride` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_TeleportToTarget` [asset]
- `/Script/Engine.PlayerController` [native]
- `/Script/EnhancedInput` [asset]
- `/Script/InputBlueprintNodes` [asset]
- `/Script/PhysicsCore` [asset]
- `/Script/UE_DOW` [asset]
- `/Script/UMG` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

