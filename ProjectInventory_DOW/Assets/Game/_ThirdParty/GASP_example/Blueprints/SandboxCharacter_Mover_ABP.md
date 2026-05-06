# SandboxCharacter_Mover_ABP

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/SandboxCharacter_Mover_ABP.SandboxCharacter_Mover_ABP` |
| Asset name | `SandboxCharacter_Mover_ABP` |
| Subclass | `AnimBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `AnimInstance` (`/Script/Engine.AnimInstance`, native, module `/Script/Engine`)
- Interfaces (1):
  - `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_ABP.BPI_SandboxCharacter_ABP_C`

## Variables (120)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `MovementMode` | `byte<E_MovementMode>` | `NewEnumerator4` | `States` | — | — | InstanceEditable, Private |
| `MovementMode_LastFrame` | `byte<E_MovementMode>` | `NewEnumerator4` | `States` | — | — | InstanceEditable, Private |
| `MovementMode_Recent` | `byte<E_MovementMode>` | `NewEnumerator4` | `States` | — | — | InstanceEditable, Private |
| `MovementMode_Time` | `real<double>` | `0.000000` | `States` | — | — | InstanceEditable, Private |
| `MovementMode_LastStateTime` | `real<double>` | `0.000000` | `States` | — | — | InstanceEditable, Private |
| `RotationMode` | `byte<E_RotationMode>` | `NewEnumerator0` | `States` | — | — | InstanceEditable, Private |
| `RotationMode_LastFrame` | `byte<E_RotationMode>` | `NewEnumerator0` | `States` | — | — | InstanceEditable, Private |
| `RotationMode_Recent` | `byte<E_RotationMode>` | `NewEnumerator0` | `States` | — | — | InstanceEditable, Private |
| `RotationMode_Time` | `real<double>` | `0.000000` | `States` | — | — | InstanceEditable, Private |
| `RotationMode_LastStateTime` | `real<double>` | `0.000000` | `States` | — | — | InstanceEditable, Private |
| `MovementState` | `byte<E_MovementState>` | `NewEnumerator4` | `States` | — | — | InstanceEditable, Private |
| `MovementState_LastFrame` | `byte<E_MovementState>` | `NewEnumerator0` | `States` | — | — | InstanceEditable, Private |
| `MovementState_Recent` | `byte<E_MovementState>` | `NewEnumerator0` | `States` | — | — | InstanceEditable, Private |
| `MovementState_Time` | `real<double>` | `0.000000` | `States` | — | — | InstanceEditable, Private |
| `MovementState_LastStateTime` | `real<double>` | `0.000000` | `States` | — | — | InstanceEditable, Private |
| `Gait` | `byte<E_Gait>` | `NewEnumerator0` | `States` | — | — | InstanceEditable, Private |
| `Gait_LastFrame` | `byte<E_Gait>` | `NewEnumerator0` | `States` | — | — | InstanceEditable, Private |
| `Gait_Recent` | `byte<E_Gait>` | `NewEnumerator0` | `States` | — | — | InstanceEditable, Private |
| `Gait_Time` | `real<double>` | `0.000000` | `States` | — | — | InstanceEditable, Private |
| `Gait_LastStateTime` | `real<double>` | `0.000000` | `States` | — | — | InstanceEditable, Private |
| `Stance` | `byte<E_Stance>` | `NewEnumerator0` | `States` | — | — | InstanceEditable, Private |
| `Stance_LastFrame` | `byte<E_Stance>` | `NewEnumerator0` | `States` | — | — | InstanceEditable, Private |
| `CharacterProperties` | `struct<S_CharacterPropertiesForAnimation>` | `(InputState_32_04D997924898849E2B907292D8F9311E=(),ActorTransform_16_F865FEEB42A03F0C9D1B7F8D29ACD19F=(Rotation=(X=0.000000,Y=-0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000)),Velocity_19_E4BA1C9D46E4A6BAC5DD63A4A1A93BE0=(X=0.000000,Y=0.000000,Z=0.000000),InputAcceleration_21_5C93A8BB46763C31AC835FA9A3C9FE88=(X=0.000000,Y=0.000000,Z=0.000000),OrientationIntent_49_38FB872B46ADBB0ED766758157174BB1=(Pitch=0.000000,Yaw=0.000000,Roll=0.000000),AimingRotation_29_9817B3384AC40E67F1E5E39238ADEEEA=(Pitch=0.000000,Yaw=0.000000,Roll=0.000000),LandVelocity_40_AD6ED73D49EE6F5998ECD7ACB2D5D7EB=(X=0.000000,Y=0.000000,Z=0.000000),GroundNormal_58_F7B6873B4C61B0EC85BAA2B8F1340DDA=(X=0.000000,Y=0.000000,Z=0.000000),GroundLocation_62_08A0EA404C60B46793D1378218DC1180=(X=0.000000,Y=0.000000,Z=0.000000),AimPosition_67_AE9F7073431FDA6A11EAD98AA4150F2A=(X=0.000000,Y=0.000000,Z=0.000000),WeaponIKPosition_70_7CE8BA0341DCBAD32512679270EE816E=(X=0.000000,Y=0.000000,Z=0.000000),WeaponIKDirection_73_983C55274AEA3592F70FA1859ACC85CC=(X=0.000000,Y=0.000000,Z=0.000000))` | `Essential Values` | — | — | InstanceEditable, Private |
| `CharacterTransform` | `struct<Transform>` | `(Rotation=(X=0.000000,Y=0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000))` | `Essential Values` | — | — | InstanceEditable, Private |
| `CharacterTransform_LastFrame` | `struct<Transform>` | `(Rotation=(X=0.000000,Y=0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000))` | `Essential Values` | — | — | InstanceEditable, Private |
| `RootTransform` | `struct<Transform>` | `(Rotation=(X=0.000000,Y=0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000))` | `Essential Values` | — | — | InstanceEditable, Private |
| `HasAcceleration` | `bool` | `False` | `Essential Values` | — | — | InstanceEditable, Private |
| `Acceleration` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Essential Values` | — | — | InstanceEditable, Private |
| `Acceleration_LastFrame` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Essential Values` | — | — | InstanceEditable, Private |
| `AccelerationAmount` | `real<double>` | `0.000000` | `Essential Values` | — | — | InstanceEditable, Private |
| `HasVelocity` | `bool` | `False` | `Essential Values` | — | — | InstanceEditable, Private |
| `Velocity` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Essential Values` | — | — | InstanceEditable, Private |
| `Velocity_LastFrame` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Essential Values` | — | — | InstanceEditable, Private |
| `RelativeAcceleration` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Essential Values` | — | — | InstanceEditable, Private |
| `VelocityAcceleration` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Essential Values` | — | — | InstanceEditable, Private |
| `LastNonZeroVelocity` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Essential Values` | — | — | InstanceEditable, Private |
| `Speed2D` | `real<double>` | `0.000000` | `Essential Values` | — | — | InstanceEditable, Private |
| `Predictor` | `object<MoverTrajectoryPredictor>` | `None` | `Trajectory` | — | — | InstanceEditable, Private |
| `Trajectory` | `struct<TransformTrajectory>` | `()` | `Trajectory` | — | — | InstanceEditable, Private |
| `TrajectoryCollision` | `struct<PoseSearchTrajectory_WorldCollisionResults>` | `()` | `Trajectory` | — | — | InstanceEditable, Private |
| `PreviousDesiredControllerYaw` | `real<float>` | `0.000000` | `Trajectory` | — | — | InstanceEditable, Private |
| `SmoothedAimTarget` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `Aim Offset` | — | — | InstanceEditable, Private |
| `MMDatabaseLOD` | `int` | `0` | `Motion Matching` | — | — | InstanceEditable, Private |
| `ValidDatabases` | `TArray<object<PoseSearchDatabase>>` | — | `Motion Matching` | — | — | InstanceEditable, Private |
| `CurrentSelectedDatabase` | `object<PoseSearchDatabase>` | `None` | `Motion Matching` | — | — | InstanceEditable, Private |
| `CurrentSelectedAnim` | `object<Object>` | `None` | `Motion Matching` | — | — | InstanceEditable, Private |
| `CurrentDatabaseTags` | `TArray<name>` | — | `Motion Matching` | — | — | InstanceEditable, Private |
| `HeavyLandSpeedThreshold` | `real<double>` | `-500.000000` | `Essential Values` | — | — | InstanceEditable, Private |
| `InteractionTransform` | `struct<Transform>` | `(Rotation=(X=0.000000,Y=0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000))` | `Essential Values` | — | — | InstanceEditable, Private |
| `Trj_PastVelocity` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Trajectory` | — | — | InstanceEditable, Private |
| `Trj_NearFutureVelocity` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Trajectory` | — | — | InstanceEditable, Private |
| `Trj_FutureVelocity` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Trajectory` | — | — | InstanceEditable, Private |
| `OffsetRootBoneEnabled` | `bool` | `False` | `Root Offset` | — | — | InstanceEditable, Private |
| `ValidAnims` | `TArray<object<AnimationAsset>>` | — | `State Machine (Experimental)` | — | — | InstanceEditable, Private |
| `BlendStackInputs` | `struct<S_BlendStackInputs>` | `()` | `State Machine (Experimental)` | — | — | InstanceEditable, Private |
| `Previous_BlendStackInputs` | `struct<S_BlendStackInputs>` | `()` | `State Machine (Experimental)` | — | — | InstanceEditable, Private |
| `StateMachineState` | `byte<E_ExperimentalStateMachineState>` | `NewEnumerator0` | `State Machine (Experimental)` | — | — | InstanceEditable, Private |
| `NoValidAnim` | `bool` | `True` | `State Machine (Experimental)` | — | — | InstanceEditable, Private |
| `NotifyTransition_Re-Transition` | `bool` | `False` | `State Machine (Experimental)` | — | — | InstanceEditable, Private |
| `NotifyTransition_ToLoop` | `bool` | `False` | `State Machine (Experimental)` | — | — | InstanceEditable, Private |
| `DebugTransitions` | `bool` | `False` | `Debug` | — | — | InstanceEditable, Private |
| `PlantSettings_Default` | `struct<FootPlacementPlantSettings>` | `(SpeedThreshold=60.000000,DistanceToGround=10.000000,LockType=PivotAroundBall,UnplantRadius=20.000000,ReplantRadiusRatio=0.200000,UnplantAngle=60.000000,ReplantAngleRatio=0.200000,MaxExtensionRatio=0.500000,MinExtensionRatio=0.200000,UnalignmentSpeedThreshold=200.000000,AnkleTwistReduction=0.750000)` | `Foot Placement` | — | — | InstanceEditable, Private |
| `PlantSettings_Stops` | `struct<FootPlacementPlantSettings>` | `(SpeedThreshold=20.000000,DistanceToGround=10.000000,LockType=PivotAroundBall,UnplantRadius=40.000000,ReplantRadiusRatio=0.750000,UnplantAngle=60.000000,ReplantAngleRatio=0.200000,MaxExtensionRatio=0.500000,MinExtensionRatio=0.200000,UnalignmentSpeedThreshold=200.000000,AnkleTwistReduction=0.750000)` | `Foot Placement` | — | — | InstanceEditable, Private |
| `InterpolationSettings_Default` | `struct<FootPlacementInterpolationSettings>` | `(UnplantLinearStiffness=100.000000,UnplantLinearDamping=1.000000,UnplantAngularStiffness=450.000000,UnplantAngularDamping=1.000000,SeparationStiffness=1000.000000,SeparationDamping=1.000000,FloorLinearStiffness=1000.000000,FloorLinearDamping=1.000000,FloorAngularStiffness=450.000000,FloorAngularDamping=1.000000,bEnableFloorInterpolation=True,bEnableSeparationInterpolation=True)` | `Foot Placement` | — | — | InstanceEditable, Private |
| `InterpolationSettings_Stops` | `struct<FootPlacementInterpolationSettings>` | `(UnplantLinearStiffness=250.000000,UnplantLinearDamping=1.000000,UnplantAngularStiffness=450.000000,UnplantAngularDamping=1.000000,SeparationStiffness=1000.000000,SeparationDamping=1.000000,FloorLinearStiffness=1000.000000,FloorLinearDamping=1.000000,FloorAngularStiffness=450.000000,FloorAngularDamping=1.000000,bEnableFloorInterpolation=True,bEnableSeparationInterpolation=True)` | `Foot Placement` | — | — | InstanceEditable, Private |
| `Stance_Recent` | `byte<E_Stance>` | `NewEnumerator0` | `States` | — | — | InstanceEditable, Private |
| `Stance_Time` | `real<double>` | `0.000000` | `States` | — | — | InstanceEditable, Private |
| `Stance_LastStateTime` | `real<double>` | `0.000000` | `States` | — | — | InstanceEditable, Private |
| `MovementDirection` | `byte<E_MovementDirection>` | `NewEnumerator0` | `States` | — | — | InstanceEditable, Private |
| `MovementDirection_LastFrame` | `byte<E_MovementDirection>` | `NewEnumerator0` | `States` | — | — | InstanceEditable, Private |
| `OffsetRootTranslationRadius` | `real<double>` | `0.000000` | `Root Offset` | — | — | InstanceEditable, Private |
| `HasOwningActor` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `HasMover` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `UseThreadSafeUpdateAnimation` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Search Cost` | `real<float>` | `0.000000` | `State Machine (Experimental)` | — | — | InstanceEditable, Private |
| `Trj_PreviousFutureVelocity` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Trajectory` | — | — | InstanceEditable, Private |
| `Trj_FutureFacing` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `Trajectory` | — | — | InstanceEditable, Private |
| `Trj_TurnAngle` | `real<double>` | `0.000000` | `Trajectory` | — | — | InstanceEditable, Private |
| `Trj_PastAngularVelocity` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Trajectory` | — | — | InstanceEditable, Private |
| `Trj_CurrentAngularVelocity` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Trajectory` | — | — | InstanceEditable, Private |
| `Trj_IsCircling` | `bool` | `False` | `Trajectory` | — | — | InstanceEditable, Private |
| `Trj_CirclingTime` | `real<double>` | `0.000000` | `Trajectory` | — | — | InstanceEditable, Private |
| `FutureFacingDelta` | `real<double>` | `0.000000` | `Trajectory` | — | — | InstanceEditable, Private |
| `LocomotionSetup` | `int` | `1` | `Default` | — | — | InstanceEditable, Private |
| `Mover` | `object<MoverComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `FootPlacement_Enable` | `bool` | `False` | `Foot Placement` | — | — | InstanceEditable, Private |
| `FootPlacement_Debug` | `bool` | `False` | `Foot Placement` | — | — | InstanceEditable, Private |
| `FootPlacementMode` | `int` | `0` | `Foot Placement` | — | — | InstanceEditable, Private |
| `FutureFacingOnTransitionStart` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `State Machine (Experimental)` | — | — | InstanceEditable, Private |
| `AO` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Aim Offset` | — | — | InstanceEditable, Private |
| `Previous_AO` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Aim Offset` | — | — | InstanceEditable, Private |
| `TransitionHistory` | `TArray<string>` | `("None")` | `Debug` | — | — | InstanceEditable, Private |
| `PawnSpeedHistory` | `TArray<real<float>>` | — | `Debug` | — | — | InstanceEditable, Private |
| `MoveData_Speed_History` | `TArray<real<float>>` | — | `Debug` | — | — | InstanceEditable, Private |
| `Phase_History` | `TArray<real<float>>` | — | `Debug` | — | — | InstanceEditable, Private |
| `Contact_L_History` | `TArray<real<float>>` | — | `Debug` | — | — | InstanceEditable, Private |
| `Contact_R_History` | `TArray<real<float>>` | — | `Debug` | — | — | InstanceEditable, Private |
| `Enable_Warping_History` | `TArray<real<float>>` | — | `Debug` | — | — | InstanceEditable, Private |
| `MM Search Cost` | `real<float>` | `0.000000` | `Motion Matching` | — | — | InstanceEditable, Private |
| `MovementDirection_Recent` | `byte<E_MovementDirection>` | `NewEnumerator0` | `States` | — | — | InstanceEditable, Private |
| `MovementDirection_Time` | `real<double>` | `0.000000` | `States` | — | — | InstanceEditable, Private |
| `EnableAO` | `bool` | `False` | `Aim Offset` | — | — | InstanceEditable, Private |
| `In Out Angular Velocity` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Aim Offset` | — | — | InstanceEditable, Private |
| `TeleportThreshold` | `real<double>` | `50.000000` | `Foot Placement` | — | — | InstanceEditable, Private |
| `FutureFacingDelta_LastFrame` | `real<double>` | `0.000000` | `Trajectory` | — | — | InstanceEditable, Private |
| `SmoothedGroundNormal` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Essential Values` | — | — | InstanceEditable, Private |
| `ForceFootPlacementReset` | `bool` | `False` | `Procedural` | — | — | InstanceEditable, Private |
| `LeanAmount` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Additive Lean` | — | — | InstanceEditable, Private |
| `MovementDirection_LastStateTime` | `real<double>` | `0.000000` | `States` | — | — | InstanceEditable, Private |
| `UpperBodyPitch` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `LeftArmBlend` | `real<double>` | `1.000000` | `Default` | — | — | InstanceEditable, Private |
| `RightArmBlend` | `real<double>` | `1.000000` | `Default` | — | — | InstanceEditable, Private |
| `BodyIKBlend` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `AimPosition` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `SharpAO` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `SharpAO_Last` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `LeftHandIK_Position` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `LeftHandIK_Rotation` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `LeftHandIK_ElbowPosition` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `LeftHandIK_Transformation` | `struct<Transform>` | `(Rotation=(X=0.000000,Y=0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000))` | `Default` | — | — | InstanceEditable, Private |

## Functions (70)

### `AdditiveLeans`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 24

### `AimOffset`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7

### `AllowFootPinning`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 6
- Category: `Procedural`

### `AllowSlopeWarping`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 4
- Category: `Procedural`

### `AnimGraph`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 73

### `Biped_FootPlacement_OnBecomeRelevant`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Procedural`

### `BlueprintThreadSafeUpdateAnimation`

- Access: `Public`
- Flags: —
- Inputs: `(real<float> DeltaTime = 0.0)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7

### `ConditionalIncrement`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> ValueIn, real<double> Delta, real<double> UpScale = 1.000000, real<double> DownScale = 1.000000, bool Direction = true)`
- Outputs: `(real<double> ValueOut, real<double> ValueOut)`
- Local variables: _none_
- Nodes: 12

### `DebugDraws`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `DrawRotation`, `DrawOrigin`
- Nodes: 131
- Category: `Debug`

### `EnableSteering`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimNodeReference>& Node [ref])`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 14
- Category: `Steering`

### `Get_DesiredFacing`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimNodeReference>& Node [ref])`
- Outputs: `(struct<Quat> ReturnValue)`
- Local variables: _none_
- Nodes: 11
- Category: `Steering`

### `Get_DynamicPlayRate`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimNodeReference>& BlendStackInput [ref])`
- Outputs: `(real<double> ReturnValue, real<double> ReturnValue, real<double> ReturnValue, real<double> ReturnValue)`
- Local variables (6): `AnimSequence`, `AnimTime`, `SpeedCurve`, `AlphaCurve`, `MaxDynamicPlayRate`, `MinDynamicPlayRate`
- Nodes: 60
- Category: `State Machine (Experimental)`

### `Get_Gait`

- Interface override of `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_ABP.BPI_SandboxCharacter_ABP_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte ReturnValue)`
- Local variables: _none_
- Nodes: 3

### `Get_InteractionTransform`

- Interface override of `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_ABP.BPI_SandboxCharacter_ABP_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Transform> ReturnValue)`
- Local variables: _none_
- Nodes: 3

### `Get_LandVelocity`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 4
- Category: `Movement Analysis`

### `Get_MMBlendTime`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue, real<double> ReturnValue, real<double> ReturnValue, real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 15
- Category: `Motion Matching`

### `Get_MMInterruptMode`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte ReturnValue)`
- Local variables: _none_
- Nodes: 30
- Category: `Motion Matching`

### `Get_MMNotifyRecencyTimeOut`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 9
- Category: `Motion Matching`

### `Get_OffsetRootRotationMode`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte ReturnValue, byte ReturnValue)`
- Local variables: _none_
- Nodes: 6
- Category: `Root Offset`

### `Get_OffsetRootTranslationHalfLife`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue, real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 6
- Category: `Root Offset`

### `Get_OffsetRootTranslationMode`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte ReturnValue, byte ReturnValue, byte ReturnValue, byte ReturnValue, byte ReturnValue)`
- Local variables: _none_
- Nodes: 13
- Category: `Root Offset`

### `Get_OffsetRootTranslationRadius`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 4
- Category: `Root Offset`

### `Get_OrientationWarpingWarpingSpace`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte ReturnValue, byte ReturnValue)`
- Local variables: _none_
- Nodes: 6
- Category: `Root Offset`

### `Get_PoseHistory`

- Interface override of `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_ABP.BPI_SandboxCharacter_ABP_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<PoseHistoryReference> ReturnValue)`
- Local variables: _none_
- Nodes: 5

### `Get_PoseHistoryReference`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<PoseHistoryReference> ReturnValue)`
- Local variables: _none_
- Nodes: 5
- Category: `Motion Matching`

### `Get_ProceduralTargetTime`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimNodeReference> Node)`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 7
- Category: `Steering`

### `Get_SlideSlopeOffset`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> ReturnValue)`
- Local variables: _none_
- Nodes: 8
- Category: `Procedural`

### `Get_SlideSlopeRotation`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Rotator> ReturnValue)`
- Local variables: _none_
- Nodes: 12
- Category: `Procedural`

### `Get_StrafeWarpAlpha`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimNodeReference>& Node [ref])`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 9
- Category: `Procedural`

### `Get_StrafeWarpDirection`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> ReturnValue)`
- Local variables: _none_
- Nodes: 8
- Category: `State Machine (Experimental)`

### `Get_StrideWarpAlpha`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimNodeReference>& Node [ref])`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 9
- Category: `Procedural`

### `Get_TotalFacingDelta`

- Access: `Public`
- Flags: —
- Inputs: `(TArray<real<float>> Times)`
- Outputs: `(real<float> ReturnValue)`
- Local variables (3): `Facings`, `Rotations`, `Angle`
- Nodes: 32
- Category: `Trajectory`

### `Get_TrajectoryTurnAngle`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 7
- Category: `Trajectory`

### `InitializeMoverPredictor`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14
- Category: `Event Graph`

### `IsAnimationAlmostComplete`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 10
- Category: `State Machine (Experimental)`

### `IsMoving`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 8
- Category: `Movement Analysis`

### `IsPivoting`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 10
- Category: `Movement Analysis`

### `IsStarting`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 17
- Category: `Movement Analysis`

### `JustLanded_Heavy`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 11
- Category: `Movement Analysis`

### `JustLanded_Light`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 11
- Category: `Movement Analysis`

### `JustTeleported`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Teleported)`
- Local variables: _none_
- Nodes: 10

### `JustTraversed`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 11
- Category: `Movement Analysis`

### `OnStateEntry_IdleBreak`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `State Machine (Experimental)`

### `OnStateEntry_IdleLoop`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `State Machine (Experimental)`

### `OnStateEntry_InAirLoop`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `State Machine (Experimental)`

### `OnStateEntry_LocomotionLoop`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `State Machine (Experimental)`

### `OnStateEntry_SlideLoop`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `State Machine (Experimental)`

### `OnStateEntry_TransitionToIdle`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `State Machine (Experimental)`

### `OnStateEntry_TransitionToInAir`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `State Machine (Experimental)`

### `OnStateEntry_TransitionToLocomotion`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `State Machine (Experimental)`

### `OnStateEntry_TransitionToSlide`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `State Machine (Experimental)`

### `OnUpdate_TransitionToLocomotion`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `State Machine (Experimental)`

### `Procedural`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 26

### `Procedural_PreLayering`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

### `Set_InteractionTransform`

- Interface override of `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_ABP.BPI_SandboxCharacter_ABP_C`
- Access: `Public`
- Flags: —
- Inputs: `(struct<Transform> InteractionTransform)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

### `Set_NotifyTransition_ReTransition`

- Interface override of `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_ABP.BPI_SandboxCharacter_ABP_C`
- Access: `Public`
- Flags: —
- Inputs: `(bool ReTransition = false)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

### `Set_NotifyTransition_ToLoop`

- Interface override of `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_ABP.BPI_SandboxCharacter_ABP_C`
- Access: `Public`
- Flags: —
- Inputs: `(bool ToLoop = false)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

### `SetBlendStackAnimFromChooser`

- Access: `Public`
- Flags: —
- Inputs: `(byte StateMachineState = NewEnumerator0, bool ForceBlend = true)`
- Outputs: `()`
- Local variables (3): `ValidAnimsFromChooser`, `ChooserOutputs`, `ChooserResult`
- Nodes: 65
- Category: `State Machine (Experimental)`

### `ShouldSpinTransition`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 12
- Category: `Movement Analysis`

### `ShouldTurnInPlace`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 11
- Category: `Movement Analysis`

### `Update_AdditiveLean`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `AimTarget`, `LateralAccelecrationAmount`
- Nodes: 24
- Category: `Event Graph`

### `Update_AimOffset`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `AimTarget`
- Nodes: 56
- Category: `Event Graph`

### `Update_CVarDrivenVariables`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 29
- Category: `Event Graph`

### `Update_EssentialValues`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 60
- Category: `Event Graph`

### `Update_Logic`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6
- Category: `Event Graph`

### `Update_MotionMatching`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8
- Category: `Motion Matching`

### `Update_MotionMatching_PostSelection`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14
- Category: `Motion Matching`

### `Update_PropertiesFromCharacter`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Event Graph`

### `Update_States`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 63
- Category: `Event Graph`

### `Update_Trajectory`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `NewLocalVar`
- Nodes: 77
- Category: `Event Graph`

## Macros (2)

### `NewMacro`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

### `UpdateStateValues`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (53 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## State Machines

- **State Controller** (10 states, 29 transitions)
  - State `Conduit` [Conduit] (1 nodes)
  - State `Idle Break` [State] (1 nodes)
  - State `Idle Loop` [State] (1 nodes)
  - State `In Air Loop` [State] (1 nodes)
  - State `Locomotion Loop` [State] (1 nodes)
  - State `Slide Loop` [State] (1 nodes)
  - State `Transition to Idle` [State] (1 nodes)
  - State `Transition to In Air` [State] (1 nodes)
  - State `Transition to Locomotion` [State] (1 nodes)
  - State `Transition to Slide` [State] (1 nodes)
  - Transition `-> Grounded` → `Conduit` [StandardBlend] crossfade=0.20s
  - Transition `-> In Air` → `Transition to In Air` [StandardBlend] crossfade=0.20s
  - Transition `-> Slide` → `Transition to Slide` [StandardBlend] crossfade=0.20s
  - Transition `Conduit` → `Transition to Idle` [StandardBlend] crossfade=0.20s
  - Transition `Conduit` → `Transition to Locomotion` [StandardBlend] crossfade=0.20s
  - Transition `Idle -> Locomotion` → `Transition to Locomotion` [StandardBlend] crossfade=0.20s
  - Transition `Idle Break` → `Idle Loop` [StandardBlend] crossfade=0.20s
  - Transition `Idle Break` → `Idle Loop` [StandardBlend] crossfade=0.20s
  - Transition `Idle Loop` → `Idle Break` [StandardBlend] crossfade=0.20s
  - Transition `Locomotion -> Idle` → `Transition to Idle` [StandardBlend] crossfade=0.20s
  - Transition `Re-Enter` → `Transition to Locomotion` [StandardBlend] crossfade=0.20s
  - Transition `Re-Enter` → `Transition to Locomotion` [StandardBlend] crossfade=0.20s
  - Transition `Re-Enter` → `Transition to Locomotion` [StandardBlend] crossfade=0.20s
  - Transition `Re-Enter` → `Transition to Locomotion` [StandardBlend] crossfade=0.20s
  - Transition `Re-Enter` → `Transition to Locomotion` [StandardBlend] crossfade=0.20s
  - Transition `Re-Enter ` → `Transition to Idle` [StandardBlend] crossfade=0.20s
  - Transition `Re-Enter ` → `Transition to Idle` [StandardBlend] crossfade=0.20s
  - Transition `Re-Enter  ` → `Transition to Slide` [StandardBlend] crossfade=0.20s
  - Transition `Re-Enter   ` → `Transition to In Air` [StandardBlend] crossfade=0.20s
  - Transition `Transition to Idle` → `Idle Loop` [StandardBlend] crossfade=0.20s
  - Transition `Transition to Idle` → `Idle Loop` [StandardBlend] crossfade=0.20s
  - Transition `Transition to In Air` → `In Air Loop` [StandardBlend] crossfade=0.20s
  - Transition `Transition to In Air` → `In Air Loop` [StandardBlend] crossfade=0.20s
  - Transition `Transition to Locomotion` → `Locomotion Loop` [Custom] crossfade=0.20s
  - Transition `Transition to Locomotion` → `Locomotion Loop` [StandardBlend] crossfade=0.20s
  - Transition `Transition to Locomotion` → `Locomotion Loop` [StandardBlend] crossfade=0.20s
  - Transition `Transition to Locomotion` → `Locomotion Loop` [StandardBlend] crossfade=0.20s
  - Transition `Transition to Slide` → `Slide Loop` [StandardBlend] crossfade=0.20s
  - Transition `Transition to Slide` → `Slide Loop` [StandardBlend] crossfade=0.20s

## References

Hard refs out (44):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_ABP` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_Pawn` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/ControlRigs/CR_Biped_FootPlacement` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/BFL_HelpfulFunctions` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_ExperimentalStateMachineState` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_Gait` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_MovementDirection` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_MovementMode` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_MovementState` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_RotationMode` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_Stance` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_BlendStackInputs` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_CharacterPropertiesForAnimation` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_ChooserOutputs` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_DebugGraphLineProperties` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_PlayerInputState` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/PlayerPawn/SandboxCharacter_Mover` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/AimOffset/AO_Blend_Curve` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/AimOffset/BS_Neutral_AO_Stand_NoSmoothing` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/ExperimentalStateMachineData/CHT_MoverCharacterAnimations` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/CHT_PoseSearchDatabases_Relaxed` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Poses/BS_Relaxed_Lean_Head` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Poses/BS_Relaxed_Run_Leans` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Poses/BS_Relaxed_Walk_Leans` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Meshes/SK_UEFN_Mannequin` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Rigs/MDT_UEFN_Mannequin` [asset]
- `/Game/_ThirdParty/GASP_example/Overlays/RifleAim_4` [asset]
- `/Script/AnimationWarpingEditor` [asset]
- `/Script/AnimationWarpingRuntime` [asset]
- `/Script/AnimGraph` [asset]
- `/Script/AnimGraphRuntime` [asset]
- `/Script/BlendStack` [asset]
- `/Script/BlendStackEditor` [asset]
- `/Script/Chooser` [asset]
- `/Script/ChooserUncooked` [asset]
- `/Script/ControlRig` [asset]
- `/Script/ControlRigDeveloper` [asset]
- `/Script/DrawDebugLibrary` [asset]
- `/Script/Engine.AnimInstance` [native]
- `/Script/Mover` [asset]
- `/Script/PoseSearch` [asset]
- `/Script/PoseSearchEditor` [asset]
- `/Script/PropertyAccessNode` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `AnimBlueprint`
- Custom metadata: _none_

