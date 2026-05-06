# GM_Sandbox

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/GM_Sandbox.GM_Sandbox` |
| Asset name | `GM_Sandbox` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `GameModeBase` (`/Script/Engine.GameModeBase`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (2)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `PawnClasses` | `TArray<class<Class>>` | `("/Script/Engine.BlueprintGeneratedClass'/Game/_ThirdParty/GASP_example/Blueprints/SandboxCharacter_CMC.SandboxCharacter_CMC_C'","/Script/Engine.BlueprintGeneratedClass'/Game/_ThirdParty/GASP_example/Blueprints/PlayerPawn/SandboxCharacter_Mover.SandboxCharacter_Mover_C'")` | `Classes` | — | — | InstanceEditable |
| `VisualOverrides` | `TArray<class<Class>>` | `("/Script/Engine.BlueprintGeneratedClass'/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/BP_Player_Fix.BP_Player_Fix_C'","/Script/Engine.BlueprintGeneratedClass'/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/BP_Straz_Fix.BP_Straz_Fix_C'",None,"/Script/Engine.BlueprintGeneratedClass'/Game/_ThirdParty/GASP_example/Blueprints/RetargetedCharacters/BP_Manny.BP_Manny_C'","/Script/Engine.BlueprintGeneratedClass'/Game/_ThirdParty/GASP_example/Blueprints/RetargetedCharacters/BP_Quinn.BP_Quinn_C'","/Script/Engine.BlueprintGeneratedClass'/Game/_ThirdParty/GASP_example/Blueprints/RetargetedCharacters/BP_UE4_Mannequin.BP_UE4_Mannequin_C'")` | `Classes` | — | — | InstanceEditable, Private |

## Functions (4)

### `CyclePawn`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `PreviousIndex`, `NewIndex`
- Nodes: 16

### `CycleVisualOverride`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `PreviousIndex`, `NewIndex`
- Nodes: 16

### `GetDefaultPawnClassForController`

- Access: `Public`
- Flags: —
- Inputs: `(object<Controller> InController)`
- Outputs: `(class<Class> ReturnValue)`
- Local variables: _none_
- Nodes: 6

### `ResetAllPlayers`

- Access: `Public`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `CachedControlRotation`, `ActorTransform`
- Nodes: 18
- Category: `Default`

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`

## Class Default Object (2)

- `DefaultPawnClass` (`TSubclassOf<APawn>`) = `/Script/Engine.BlueprintGeneratedClass'/Game/_ThirdParty/GASP_example/Blueprints/PlayerPawn/SandboxCharacter_Mover.Sa...`
- `PlayerControllerClass` (`TSubclassOf<APlayerController>`) = `/Script/Engine.BlueprintGeneratedClass'/Game/_ThirdParty/GASP_example/Blueprints/PC_Sandbox.PC_Sandbox_C'`

## Graphs

- Event graph: `EventGraph` (6 nodes)
- Construction script: `UserConstructionScript` (1 nodes)
- Additional graphs: _none_

## References

Hard refs out (11):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/BFL_HelpfulFunctions` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/PC_Sandbox` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/PlayerPawn/SandboxCharacter_Mover` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/RetargetedCharacters/BP_Manny` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/RetargetedCharacters/BP_Quinn` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/RetargetedCharacters/BP_UE4_Mannequin` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/SandboxCharacter_CMC` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/BP_Player_Fix` [asset]
- `/Game/_ThirdParty/GASP_example/MetaHumans/Kellan/BP_Straz_Fix` [asset]
- `/Script/Engine.GameModeBase` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

