# OptimizedBP_CrowdMassAI

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/AI/MassAI/CrowdGen/OptimizationTest/OptimizedBP_CrowdMassAI.OptimizedBP_CrowdMassAI` |
| Asset name | `OptimizedBP_CrowdMassAI` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Character` (`/Script/Engine.Character`, native, module `/Script/Engine`)
- Interfaces (1):
  - `/Game/_ThirdParty/CitySampleCrowd/Blueprints/BPI_CrowdCharacter.BPI_CrowdCharacter_C`

## Variables (0)

_None._

## Functions (1)

### `GetBodyType`

- Interface override of `/Game/_ThirdParty/CitySampleCrowd/Blueprints/BPI_CrowdCharacter.BPI_CrowdCharacter_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte BodyType)`
- Local variables: _none_
- Nodes: 2

## Macros (0)

_None._

## Components (2)

- `MassAgent` — `MassAgentComponent` @ socket `None`
- `Cube` — `StaticMeshComponent` @ socket `None`

## Class Default Object (6)

- `ActorLabel` (`FString`) = `BP_Male_Med-1`
- `ArrowComponent` (`TObjectPtr<UArrowComponent>`) [instanced] = `/Script/Engine.ArrowComponent'/Game/Blueprints/AI/MassAI/CrowdGen/OptimizationTest/OptimizedBP_CrowdMassAI.Default__O...`
- `CapsuleComponent` (`TObjectPtr<UCapsuleComponent>`) [instanced] = `/Script/Engine.CapsuleComponent'/Game/Blueprints/AI/MassAI/CrowdGen/OptimizationTest/OptimizedBP_CrowdMassAI.Default_...`
- `CharacterMovement` (`TObjectPtr<UCharacterMovementComponent>`) [instanced] = `/Script/Engine.CharacterMovementComponent'/Game/Blueprints/AI/MassAI/CrowdGen/OptimizationTest/OptimizedBP_CrowdMassA...`
- `Mesh` (`TObjectPtr<USkeletalMeshComponent>`) [instanced] = `/Script/Engine.SkeletalMeshComponent'/Game/Blueprints/AI/MassAI/CrowdGen/OptimizationTest/OptimizedBP_CrowdMassAI.Def...`
- `RootComponent` (`TObjectPtr<USceneComponent>`) [instanced] = `/Script/Engine.CapsuleComponent'/Game/Blueprints/AI/MassAI/CrowdGen/OptimizationTest/OptimizedBP_CrowdMassAI.Default_...`

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `UserConstructionScript` (1 nodes)
- Additional graphs: _none_

## References

Hard refs out (8):
- `/Engine/BasicShapes/BasicShapeMaterial` [asset]
- `/Engine/BasicShapes/Cube` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Blueprints/BPI_CrowdCharacter` [asset]
- `/Game/_ThirdParty/CitySampleCrowd/Character/Shared/Enums/CrowdBodyType` [asset]
- `/Game/Blueprints/AI/MassAI/DA_NPCconfig` [asset]
- `/Script/Engine.Character` [native]
- `/Script/MassActors` [asset]
- `/Script/NavigationSystem` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

