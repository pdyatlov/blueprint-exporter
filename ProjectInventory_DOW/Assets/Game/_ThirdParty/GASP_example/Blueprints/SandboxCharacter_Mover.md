# SandboxCharacter_Mover

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/SandboxCharacter_Mover.SandboxCharacter_Mover` |
| Asset name | `SandboxCharacter_Mover` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Pawn` (`/Script/Engine.Pawn`, native, module `/Script/Engine`)
- Interfaces (2):
  - `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_Pawn.BPI_SandboxCharacter_Pawn_C`
  - `/Script/Mover.MoverInputProducerInterface`

## Variables (18)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `MoverDefaultInputs_PreSim` | `struct<CharacterDefaultInputs>` | `(MoveInput=(X=0.000000,Y=0.000000,Z=0.000000),OrientationIntent=(X=0.000000,Y=0.000000,Z=0.000000),ControlRotation=(Pitch=0.000000,Yaw=0.000000,Roll=0.000000))` | `Mover` | — | — | InstanceEditable, Private |
| `PlayerInputState` | `struct<S_PlayerInputState>` | `(WantsToStrafe_5_64E842184F7691CD179DFCBA7158A4D9=True)` | `Input` | — | — | InstanceEditable, Private |
| `Jump_JustPressed` | `bool` | `False` | `Input` | — | — | InstanceEditable, Private |
| `MoverCustomInputs_PreSim` | `struct<S_MoverCustomInputs>` | `()` | `Mover` | — | — | InstanceEditable, Private |
| `MoverDefaultInputs_PostSim` | `struct<CharacterDefaultInputs>` | `(MoveInput=(X=0.000000,Y=0.000000,Z=0.000000),OrientationIntent=(X=0.000000,Y=0.000000,Z=0.000000),ControlRotation=(Pitch=0.000000,Yaw=0.000000,Roll=0.000000))` | `Mover` | — | — | InstanceEditable, Private |
| `MoverCustomInputs_PostSim` | `struct<S_MoverCustomInputs>` | `()` | `Mover` | — | — | InstanceEditable, Private |
| `MovementModeMap` | `TMap<name<E_MovementMode>>, :/Game/_ThirdParty/GASP_example/Blueprints/Data/E_MovementMode.E_MovementMode>` | `(("Walking", NewEnumerator4),("Falling", NewEnumerator5),("Sliding", NewEnumerator6),("Flying", NewEnumerator7))` | `Mover` | — | — | InstanceEditable, Private |
| `SpeedHistory` | `TArray<real<float>>` | — | `Debug` | — | — | InstanceEditable, Private |
| `TargetableActors` | `TArray<object<Actor>>` | — | `Default` | — | — | InstanceEditable, Private |
| `TargetedActor` | `object<Actor>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `DebugAngle` | `real<double>` | `0.000000` | `Debug` | — | — | InstanceEditable, Private |
| `SlidingAudioComponent` | `object<AudioComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `TwinStickMode` | `bool` | `False` | `Input` | — | — | InstanceEditable, Private |
| `TwinStickAimRotation` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `Input` | — | — | InstanceEditable, Private |
| `LastControlRotation` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `Input` | — | — | InstanceEditable, Private |
| `ControlRotationRate` | `real<double>` | `0.000000` | `Input` | — | — | InstanceEditable, Private |
| `FloorNormal` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Mover` | — | — | InstanceEditable, Private |
| `FloorLocation` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Mover` | — | — | InstanceEditable, Private |

## Functions (26)

### `CacheInputsFromMover`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9
- Category: `Mover`

### `DebugDraws`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (3): `DebugDrawOrigin`, `LineThickness`, `Drawer`
- Nodes: 111
- Category: `Debug`

### `Get_AimingRotation`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Rotator> ReturnValue, struct<Rotator> ReturnValue, struct<Rotator> ReturnValue, real<float> ReturnValue_Roll, real<float> ReturnValue_Pitch, real<float> ReturnValue_Yaw)`
- Local variables: _none_
- Nodes: 21
- Category: `Mover`

### `Get_CurrentMovementMode`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte ReturnValue)`
- Local variables: _none_
- Nodes: 7
- Category: `Mover`

### `Get_Gait`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte ReturnValue, byte ReturnValue, byte ReturnValue, byte ReturnValue, byte ReturnValue, byte ReturnValue, byte ReturnValue, byte ReturnValue)`
- Local variables: _none_
- Nodes: 33
- Category: `Mover`

### `Get_MoveInput`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> ReturnValue, struct<Vector> ReturnValue)`
- Local variables: _none_
- Nodes: 16
- Category: `Mover`

### `Get_MovementDirectionAndOffset`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte MovementDirection, real<double> RotationOffset, byte MovementDirection, real<double> RotationOffset, byte MovementDirection, real<double> RotationOffset)`
- Local variables (4): `DirectionOfMovement`, `MovementDirectionAngle`, `NewMovementDirection`, `MovementDirectionThresholds`
- Nodes: 57
- Category: `Mover`

### `Get_MovementDirectionFromThresholds`

- Access: `Public`
- Flags: —
- Inputs: `(struct<S_MovementDirectionThresholds>& Thresholds [ref], real<double> Direction)`
- Outputs: `(byte ReturnValue, byte ReturnValue, byte ReturnValue, byte ReturnValue)`
- Local variables: _none_
- Nodes: 13
- Category: `Mover`

### `Get_MovementDirectionThresholds`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<S_MovementDirectionThresholds> ReturnValue, real<double> ReturnValue_FL_3_747C69604F939E7EFF347D97BBD8A811, real<double> ReturnValue_FR_5_790F2C4742CB53A5585DBFAF660F9CF0, real<double> ReturnValue_BL_7_630ADC5A4B6C3AF9DA182E816EDB311B, real<double> ReturnValue_BR_9_67DF35F84900050330F770A709E84CF7, struct<S_MovementDirectionThresholds> ReturnValue, real<double> ReturnValue_FL_3_747C69604F939E7EFF347D97BBD8A811, real<double> ReturnValue_FR_5_790F2C4742CB53A5585DBFAF660F9CF0, real<double> ReturnValue_BL_7_630ADC5A4B6C3AF9DA182E816EDB311B, real<double> ReturnValue_BR_9_67DF35F84900050330F770A709E84CF7, struct<S_MovementDirectionThresholds> ReturnValue, real<double> ReturnValue_FL_3_747C69604F939E7EFF347D97BBD8A811, real<double> ReturnValue_FR_5_790F2C4742CB53A5585DBFAF660F9CF0, real<double> ReturnValue_BL_7_630ADC5A4B6C3AF9DA182E816EDB311B, real<double> ReturnValue_BR_9_67DF35F84900050330F770A709E84CF7, struct<S_MovementDirectionThresholds> ReturnValue, real<double> ReturnValue_FL_3_747C69604F939E7EFF347D97BBD8A811, real<double> ReturnValue_FR_5_790F2C4742CB53A5585DBFAF660F9CF0, real<double> ReturnValue_BL_7_630ADC5A4B6C3AF9DA182E816EDB311B, real<double> ReturnValue_BR_9_67DF35F84900050330F770A709E84CF7, struct<S_MovementDirectionThresholds> ReturnValue, real<double> ReturnValue_FL_3_747C69604F939E7EFF347D97BBD8A811, real<double> ReturnValue_FR_5_790F2C4742CB53A5585DBFAF660F9CF0, real<double> ReturnValue_BL_7_630ADC5A4B6C3AF9DA182E816EDB311B, real<double> ReturnValue_BR_9_67DF35F84900050330F770A709E84CF7)`
- Local variables: _none_
- Nodes: 25
- Category: `Mover`

### `Get_OrientationIntent`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> ReturnValue, struct<Vector> ReturnValue, struct<Vector> ReturnValue, struct<Vector> ReturnValue, struct<Vector> ReturnValue, struct<Vector> ReturnValue, struct<Vector> ReturnValue, struct<Vector> ReturnValue, struct<Vector> ReturnValue, struct<Vector> ReturnValue)`
- Local variables (1): `Direction`
- Nodes: 76
- Category: `Mover`

### `Get_PropertiesForAnimation`

- Interface override of `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_Pawn.BPI_SandboxCharacter_Pawn_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<S_CharacterPropertiesForAnimation> ReturnValue)`
- Local variables: _none_
- Nodes: 22

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

### `Get_RotationMode`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte ReturnValue, byte ReturnValue, byte ReturnValue, byte ReturnValue, byte ReturnValue, byte ReturnValue, byte ReturnValue, byte ReturnValue)`
- Local variables (2): `Direction`, `MovementDirection`
- Nodes: 32
- Category: `Mover`

### `Get_Speed`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 5
- Category: `Mover`

### `GetTraversalCheckInputs`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<S_TraversalCheckInputs> ReturnValue, struct ReturnValue_TraceForwardDirection_5_84E06003419F502C44036B9424B39047, real<double> ReturnValue_TraceForwardDistance_2_07F489F3465D510BFC123689985564DC, struct ReturnValue_TraceOriginOffset_7_2757E2FF43A7611D7F46EE9AAA15F8C0, struct ReturnValue_TraceEndOffset_15_35E488F2478DA8D4D7E69FB93494661B, real<double> ReturnValue_TraceRadius_10_FF044CA546FFD12BAA4D4E93460A273A, real<double> ReturnValue_TraceHalfHeight_12_019A16DE47BB8535C3C0CF8AA6E355EB, struct<S_TraversalCheckInputs> ReturnValue, struct ReturnValue_TraceForwardDirection_5_84E06003419F502C44036B9424B39047, real<double> ReturnValue_TraceForwardDistance_2_07F489F3465D510BFC123689985564DC, struct ReturnValue_TraceOriginOffset_7_2757E2FF43A7611D7F46EE9AAA15F8C0, struct ReturnValue_TraceEndOffset_15_35E488F2478DA8D4D7E69FB93494661B, real<double> ReturnValue_TraceRadius_10_FF044CA546FFD12BAA4D4E93460A273A, real<double> ReturnValue_TraceHalfHeight_12_019A16DE47BB8535C3C0CF8AA6E355EB)`
- Local variables (1): `Direction`
- Nodes: 25
- Category: `Traversal`

### `OnMovementModeChanged`

- Access: `Public`
- Flags: —
- Inputs: `(name& PreviousMovementModeName [ref], name& NewMovementModeName [ref])`
- Outputs: `()`
- Local variables (2): `PreviousMovementMode`, `NewMovementMode`
- Nodes: 53
- Category: `Mover`

### `OnPreSimulateTick`

- Access: `Public`
- Flags: —
- Inputs: `(struct<MoverTimeStep>& TimeStep [ref], struct<MoverInputCmdContext>& InputCmd [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10
- Category: `Mover`

### `ProduceInput`

- Interface override of `/Script/Mover.MoverInputProducerInterface`
- Access: `Public`
- Flags: —
- Inputs: `(int SimTimeMs = 0)`
- Outputs: `(struct<MoverInputCmdContext> InputCmdResult)`
- Local variables (1): `InputCollection`
- Nodes: 52

### `SetupCamera`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `PlayerController`
- Nodes: 17
- Category: `Default`

### `SetupInput`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8
- Category: `Default`

### `Update_ControlRotationRate`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

### `Update_FloorValues`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12

### `Update_SlidingAudio`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

### `Update_TargetedActor`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13

### `Update_TwinStickMode`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 20

## Macros (0)

_None._

## Components (8)

- `Capsule` — `CapsuleComponent` @ socket `None`
  - `SkeletalMesh` — `SkeletalMeshComponent` @ socket `None`
    - `VisualOverride` — `ChildActorComponent` @ socket `None`
    - `GameplayCamera` — `GameplayCameraComponent` @ socket `root`
  - `SpringArm` — `SpringArmComponent` @ socket `None`
    - `Camera` — `CameraComponent` @ socket `None`
- `CharacterMover` — `CharacterMoverComponent` @ socket `None`
- `AC_TraversalLogic` — `AC_TraversalLogic_C` @ socket `None`
- `MotionWarping` — `MotionWarpingComponent` @ socket `None`
- `AC_FoleyEvents` — `AC_FoleyEvents_C` @ socket `None`
- `AC_VisualOverrideManager` — `AC_VisualOverrideManager_C` @ socket `None`
- `AC_SmartObjectAnimation` — `AC_SmartObjectAnimation_C` @ socket `None`
- `NavMover` — `NavMoverComponent` @ socket `None`

## Class Default Object (3)

- `ActorLabel` (`FString`) = `SandboxCharacter_Mover_ABP`
- `bReplicateMovement` (`uint8`) = `False`
- `Tags` (`TArray`) = `("Experimental","New")`

## Graphs

- Event graph: `EventGraph` (142 nodes)
- Construction script: `UserConstructionScript` (1 nodes)
- Additional graphs: _none_

## References

Hard refs out (59):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Engine/VREditor/Sounds/UI/Object_Snaps_To_Another_Actor` [asset]
- `/Game/_ThirdParty/GASP_example/Audio/Foley/AC_FoleyEvents` [asset]
- `/Game/_ThirdParty/GASP_example/Audio/Foley/S_FoleyEventParams` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/AC_TraversalLogic` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/AC_VisualOverrideManager` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_Pawn` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Cameras/CameraAsset_SandboxCharacter` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Cameras/E_CameraMode` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/CHT_RotationOffsetCurve` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_Gait` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_MovementDirection` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_MovementMode` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_RotationMode` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_Stance` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_CharacterPropertiesForAnimation` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_CharacterPropertiesForCamera` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_CharacterPropertiesForTraversal` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_MovementDirectionThresholds` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_MoverCustomInputs` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_PlayerInputState` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_RotationOffsetCurveChooser_Inputs` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_TraversalCheckInputs` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/MovementModes/BP_MovementMode_Falling` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/MovementModes/BP_MovementMode_Slide` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/MovementModes/BP_MovementMode_Walking` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/MovementModes/BP_MovementTransition_FromSlide` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/MovementModes/BP_MovementTransition_ToSlide` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/SandboxCharacter_Mover_ABP` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/AC_SmartObjectAnimation` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Idle/M_Neutral_Stand_Idle_Loop` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Materials/MI_UEFN_Mannequin_Mover` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Meshes/SKM_UEFN_Mannequin` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_Aim` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_Crouch` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_Jump` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_Look` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_Look_Gamepad` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_Move` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_Sprint` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_Strafe` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_TwinStick_AimDirection` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IA_Walk` [asset]
- `/Game/_ThirdParty/GASP_example/Input/IMC_Sandbox` [asset]
- `/Script/AIModule` [asset]
- `/Script/AudioExtensions` [asset]
- `/Script/Chooser` [asset]
- `/Script/ChooserUncooked` [asset]
- `/Script/DrawDebugLibrary` [asset]
- `/Script/Engine.Pawn` [native]
- `/Script/EnhancedInput` [asset]
- `/Script/GameplayCameras` [asset]
- `/Script/GameplayTags` [asset]
- `/Script/InputBlueprintNodes` [asset]
- `/Script/InputCore` [asset]
- `/Script/MotionWarping` [asset]
- `/Script/Mover` [asset]
- `/Script/NavigationSystem` [asset]
- `/Script/PhysicsCore` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

