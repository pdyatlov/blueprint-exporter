# SandboxCharacter_CMC

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/SandboxCharacter_CMC.SandboxCharacter_CMC` |
| Asset name | `SandboxCharacter_CMC` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Character` (`/Script/Engine.Character`, native, module `/Script/Engine`)
- Interfaces (1):
  - `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_Pawn.BPI_SandboxCharacter_Pawn_C`

## Variables (21)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `MovementStickMode` | `byte<E_AnalogStickBehavior>` | `NewEnumerator0` | `Input` | — | — | InstanceEditable, Private |
| `CameraStyle` | `byte<E_CameraStyle>` | `NewEnumerator1` | `Camera` | — | — | InstanceEditable |
| `AnalogWalk/RunThreshold` | `real<float>` | `0.700000` | `Input` | — | — | InstanceEditable, Private |
| `StrafeSpeedMapCurve` | `object<CurveFloat>` | `/Script/Engine.CurveFloat'/Game/_ThirdParty/GASP_example/Blueprints/Data/Curve_StrafeSpeedMap.Curve_StrafeSpeedMap'` | `Movement` | — | — | InstanceEditable, Private |
| `Gait` | `byte<E_Gait>` | `NewEnumerator1` | `Movement` | — | — | InstanceEditable, Private |
| `WalkSpeeds` | `struct<Vector>` | `(X=200.000000,Y=180.000000,Z=150.000000)` | `Movement` | — | — | InstanceEditable |
| `RunSpeeds` | `struct<Vector>` | `(X=500.000000,Y=350.000000,Z=300.000000)` | `Movement` | — | — | InstanceEditable |
| `SprintSpeeds` | `struct<Vector>` | `(X=700.000000,Y=700.000000,Z=700.000000)` | `Movement` | — | — | InstanceEditable |
| `WalkSpeeds_Demo` | `struct<Vector>` | `(X=165.000000,Y=165.000000,Z=165.000000)` | `Movement` | — | — | InstanceEditable |
| `RunSpeeds_Demo` | `struct<Vector>` | `(X=375.000000,Y=375.000000,Z=375.000000)` | `Movement` | — | — | InstanceEditable |
| `SprintSpeeds_Demo` | `struct<Vector>` | `(X=600.000000,Y=600.000000,Z=600.000000)` | `Movement` | — | — | InstanceEditable |
| `CrouchSpeeds` | `struct<Vector>` | `(X=225.000000,Y=200.000000,Z=180.000000)` | `Movement` | — | — | InstanceEditable |
| `JustLanded` | `bool` | `False` | `Movement` | — | — | InstanceEditable, Private |
| `LandVelocity` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Movement` | — | — | InstanceEditable, Private |
| `CharacterInputState` | `struct<S_PlayerInputState>` | `(WantsToStrafe_5_64E842184F7691CD179DFCBA7158A4D9=True)` | `Input` | Replicated (COND_SkipOwner) | — | InstanceEditable |
| `WasMovingOnGroundLastFrame_Simulated` | `bool` | `True` | `Movement \| Simulated` | — | — | InstanceEditable, Private |
| `LastUpdateVelocity` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Movement \| Simulated` | — | — | InstanceEditable, Private |
| `UsingAttributeBasedRootMotion` | `bool` | `False` | `Movement` | — | — | InstanceEditable, Private |
| `IsRagdolling` | `bool` | `False` | `Physics` | — | — | InstanceEditable, Private |
| `On Request Interact` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `PatrolRoute` | `object<Object>` | `None` | `AI` | — | — | InstanceEditable |

## Functions (21)

### `CalculateBrakingDeceleration`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables (1): `StrafeSpeedMap`
- Nodes: 4
- Category: `Movement`

### `CalculateBrakingFriction`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables (1): `StrafeSpeedMap`
- Nodes: 6
- Category: `Movement`

### `CalculateGroundFriction`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables (1): `StrafeSpeedMap`
- Nodes: 8
- Category: `Movement`

### `CalculateMaxAcceleration`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables (1): `StrafeSpeedMap`
- Nodes: 8
- Category: `Movement`

### `CalculateMaxCrouchSpeed`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables (1): `StrafeSpeedMap`
- Nodes: 21
- Category: `Movement`

### `CalculateMaxSpeed`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables (1): `StrafeSpeedMap`
- Nodes: 25
- Category: `Movement`

### `CanSprint`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 18
- Category: `Movement`

### `Get_PropertiesForAnimation`

- Interface override of `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_Pawn.BPI_SandboxCharacter_Pawn_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<S_CharacterPropertiesForAnimation> ReturnValue)`
- Local variables: _none_
- Nodes: 32

### `Get_PropertiesForCamera`

- Interface override of `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_Pawn.BPI_SandboxCharacter_Pawn_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<S_CharacterPropertiesForCamera> ReturnValue)`
- Local variables: _none_
- Nodes: 12

### `Get_PropertiesForTraversal`

- Interface override of `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_Pawn.BPI_SandboxCharacter_Pawn_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<S_CharacterPropertiesForTraversal> ReturnValue, object ReturnValue_Capsule_21_D1F3797D47A5FB49C3DFAE8FAB15AFCC, object ReturnValue_Mesh_15_D47797BD4F40417B966E3BB7E0AC62D3, object ReturnValue_MotionWarping_18_C9F4AD1440C92128F649A7BA8B49094B, byte ReturnValue_MovementMode_22_F39395024EEBA400FBE9FB8AE0EF7350, byte ReturnValue_Gait_12_9093F6E14192D37D2F0223B94E64FF71, real<double> ReturnValue_Speed_26_C6C3500C4C3030A343948F80DFD60AEE)`
- Local variables: _none_
- Nodes: 12

### `GetDesiredGait`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte ReturnValue, byte ReturnValue, byte ReturnValue, byte ReturnValue, byte ReturnValue)`
- Local variables (1): `FullMovementInput`
- Nodes: 28
- Category: `Movement`

### `GetMovementInputScaleValue`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector2D> Input)`
- Outputs: `(struct<Vector2D> ReturnValue)`
- Local variables: _none_
- Nodes: 8
- Category: `Input`

### `GetTraversalCheckInputs`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<S_TraversalCheckInputs> ReturnValue, struct ReturnValue_TraceForwardDirection_5_84E06003419F502C44036B9424B39047, real<double> ReturnValue_TraceForwardDistance_2_07F489F3465D510BFC123689985564DC, struct ReturnValue_TraceOriginOffset_7_2757E2FF43A7611D7F46EE9AAA15F8C0, struct ReturnValue_TraceEndOffset_15_35E488F2478DA8D4D7E69FB93494661B, real<double> ReturnValue_TraceRadius_10_FF044CA546FFD12BAA4D4E93460A273A, real<double> ReturnValue_TraceHalfHeight_12_019A16DE47BB8535C3C0CF8AA6E355EB, struct<S_TraversalCheckInputs> ReturnValue, struct ReturnValue_TraceForwardDirection_5_84E06003419F502C44036B9424B39047, real<double> ReturnValue_TraceForwardDistance_2_07F489F3465D510BFC123689985564DC, struct ReturnValue_TraceOriginOffset_7_2757E2FF43A7611D7F46EE9AAA15F8C0, struct ReturnValue_TraceEndOffset_15_35E488F2478DA8D4D7E69FB93494661B, real<double> ReturnValue_TraceRadius_10_FF044CA546FFD12BAA4D4E93460A273A, real<double> ReturnValue_TraceHalfHeight_12_019A16DE47BB8535C3C0CF8AA6E355EB)`
- Local variables (1): `Direction`
- Nodes: 16
- Category: `Traversal`

### `HasMovementInputVector`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 4
- Category: `Movement`

### `Ragdoll_End`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15
- Category: `Physics`

### `Ragdoll_Start`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14
- Category: `Physics`

### `SetupCamera`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `PlayerController`
- Nodes: 14
- Category: `Camera`

### `SetupInput`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8
- Category: `Input`

### `UpdatedMovementSimulated`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> OldVelocity)`
- Outputs: `()`
- Local variables (1): `IsMovingOnGround`
- Nodes: 19
- Category: `Movement`

### `UpdateMovement_PreCMC`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 22
- Category: `Movement`

### `UpdateRotation_PreCMC`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 22
- Category: `Movement`

## Macros (0)

_None._

## Components (11)

- `MotionWarping` — `MotionWarpingComponent` @ socket `None`
- `AC_PreCMCTick` — `AC_PreCMCTick_C` @ socket `None`
- `SpringArm` — `SpringArmComponent` @ socket `None`
  - `Camera(NotUsedByDefault)` — `CameraComponent` @ socket `None`
- `VisualOverride` — `ChildActorComponent` @ socket `None`
- `AC_TraversalLogic` — `AC_TraversalLogic_C` @ socket `None`
- `AC_FoleyEvents` — `AC_FoleyEvents_C` @ socket `None`
- `GameplayCamera` — `GameplayCameraComponent` @ socket `None`
- `BP_VisualOverrideManager` — `AC_VisualOverrideManager_C` @ socket `None`
- `AC_SmartObjectAnimation` — `AC_SmartObjectAnimation_C` @ socket `None`
- `StateTree` — `StateTreeComponent` @ socket `None`
- `AIPerception` — `AIPerceptionComponent` @ socket `None`

## Class Default Object (10)

- `ActorLabel` (`FString`) = `SandboxCharacter_CMC_ABP`
- `AIControllerClass` (`TSubclassOf<AController>`) = `None`
- `ArrowComponent` (`TObjectPtr<UArrowComponent>`) [instanced] = `/Script/Engine.ArrowComponent'/Game/_ThirdParty/GASP_example/Blueprints/SandboxCharacter_CMC.Default__SandboxCharacte...`
- `BaseEyeHeight` (`float`) = `100.000000`
- `bUseControllerRotationYaw` (`uint8`) = `False`
- `CapsuleComponent` (`TObjectPtr<UCapsuleComponent>`) [instanced] = `/Script/Engine.CapsuleComponent'/Game/_ThirdParty/GASP_example/Blueprints/SandboxCharacter_CMC.Default__SandboxCharac...`
- `CharacterMovement` (`TObjectPtr<UCharacterMovementComponent>`) [instanced] = `/Script/Engine.CharacterMovementComponent'/Game/_ThirdParty/GASP_example/Blueprints/SandboxCharacter_CMC.Default__San...`
- `Mesh` (`TObjectPtr<USkeletalMeshComponent>`) [instanced] = `/Script/Engine.SkeletalMeshComponent'/Game/_ThirdParty/GASP_example/Blueprints/SandboxCharacter_CMC.Default__SandboxC...`
- `RootComponent` (`TObjectPtr<USceneComponent>`) [instanced] = `/Script/Engine.CapsuleComponent'/Game/_ThirdParty/GASP_example/Blueprints/SandboxCharacter_CMC.Default__SandboxCharac...`
- `Tags` (`TArray`) = `("SandboxCharacter","Legacy")`

## Graphs

- Event graph: `EventGraph` (166 nodes)
- Construction script: `UserConstructionScript` (1 nodes)
- Additional graphs: _none_

## References

Hard refs out (49):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Engine/VREditor/Sounds/UI/Object_Snaps_To_Another_Actor` [asset]
- `/Game/_ThirdParty/GASP_example/Audio/Foley/AC_FoleyEvents` [asset]
- `/Game/_ThirdParty/GASP_example/Audio/Foley/S_FoleyEventParams` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/AC_PreCMCTick` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/AC_TraversalLogic` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/AC_VisualOverrideManager` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_Pawn` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Cameras/CameraAsset_SandboxCharacter` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Cameras/E_CameraMode` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Cameras/E_CameraStyle` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/Curve_StrafeSpeedMap` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_AnalogStickBehavior` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_Gait` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_MovementMode` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_RotationMode` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_Stance` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_CharacterPropertiesForAnimation` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_CharacterPropertiesForCamera` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_CharacterPropertiesForTraversal` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_PlayerInputState` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_TraversalCheckInputs` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/SandboxCharacter_CMC_ABP` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/AC_SmartObjectAnimation` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Materials/MI_UEFN_Mannequin_CMC` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Meshes/SKM_UEFN_Mannequin` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_Aim` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_Crouch` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_Jump` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_Look` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_Look_Gamepad` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_Move` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_Move_WorldSpace` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_Sprint` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_Strafe` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_Walk` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IMC_Sandbox` [asset]
- `/Script/AIModule` [asset]
- `/Script/AnimGraphRuntime` [asset]
- `/Script/Engine.Character` [native]
- `/Script/EnhancedInput` [asset]
- `/Script/GameplayCameras` [asset]
- `/Script/GameplayStateTreeModule` [asset]
- `/Script/GameplayTags` [asset]
- `/Script/InputBlueprintNodes` [asset]
- `/Script/InputCore` [asset]
- `/Script/MotionWarping` [asset]
- `/Script/NavigationSystem` [asset]
- `/Script/PhysicsCore` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

