# SandboxCharacter_CMC_ABP

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/SandboxCharacter_CMC_ABP.SandboxCharacter_CMC_ABP` |
| Asset name | `SandboxCharacter_CMC_ABP` |
| Subclass | `AnimBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `AnimInstance` (`/Script/Engine.AnimInstance`, native, module `/Script/Engine`)
- Interfaces (2):
  - `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_ABP.BPI_SandboxCharacter_ABP_C`
  - `/Game/_ThirdParty/GASP_example/Blueprints/Data/BPI_InteractionTransform.BPI_InteractionTransform_C`

## Variables (76)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `MovementMode` | `byte<E_MovementMode>` | `NewEnumerator4` | `States` | — | — | InstanceEditable, Private |
| `MovementMode_LastFrame` | `byte<E_MovementMode>` | `NewEnumerator4` | `States` | — | — | InstanceEditable, Private |
| `RotationMode` | `byte<E_RotationMode>` | `NewEnumerator0` | `States` | — | — | InstanceEditable, Private |
| `RotationMode_LastFrame` | `byte<E_RotationMode>` | `NewEnumerator0` | `States` | — | — | InstanceEditable, Private |
| `MovementState` | `byte<E_MovementState>` | `NewEnumerator4` | `States` | — | — | InstanceEditable, Private |
| `MovementState_LastFrame` | `byte<E_MovementState>` | `NewEnumerator0` | `States` | — | — | InstanceEditable, Private |
| `Gait` | `byte<E_Gait>` | `NewEnumerator0` | `States` | — | — | InstanceEditable, Private |
| `Gait_LastFrame` | `byte<E_Gait>` | `NewEnumerator0` | `States` | — | — | InstanceEditable, Private |
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
| `TrajectoryGenerationData_Idle` | `struct<PoseSearchTrajectoryData>` | `(MaxControllerYawRate=100.000000,SpeedRemappingCurve=(EditorCurveData=(DefaultValue=340282346638528859811704183484516925440.000000,PreInfinityExtrap=RCCE_Constant,PostInfinityExtrap=RCCE_Constant)),AccelerationRemappingCurve=(EditorCurveData=(DefaultValue=340282346638528859811704183484516925440.000000,PreInfinityExtrap=RCCE_Constant,PostInfinityExtrap=RCCE_Constant)))` | `Trajectory` | — | — | InstanceEditable, Private |
| `TrajectoryGenerationData_Moving` | `struct<PoseSearchTrajectoryData>` | `(SpeedRemappingCurve=(EditorCurveData=(DefaultValue=340282346638528859811704183484516925440.000000,PreInfinityExtrap=RCCE_Constant,PostInfinityExtrap=RCCE_Constant)),AccelerationRemappingCurve=(EditorCurveData=(DefaultValue=340282346638528859811704183484516925440.000000,PreInfinityExtrap=RCCE_Constant,PostInfinityExtrap=RCCE_Constant)))` | `Trajectory` | — | — | InstanceEditable, Private |
| `Trajectory` | `struct<TransformTrajectory>` | `()` | `Trajectory` | — | — | InstanceEditable, Private |
| `TrajectoryCollision` | `struct<PoseSearchTrajectory_WorldCollisionResults>` | `()` | `Trajectory` | — | — | InstanceEditable, Private |
| `PreviousDesiredControllerYaw` | `real<float>` | `0.000000` | `Trajectory` | — | — | InstanceEditable, Private |
| `MMDatabaseLOD` | `int` | `0` | `Motion Matching` | — | — | InstanceEditable, Private |
| `CurrentSelectedAnim` | `object<Object>` | `None` | `Motion Matching` | — | — | InstanceEditable, Private |
| `CurrentSelectedDatabase` | `object<PoseSearchDatabase>` | `None` | `Motion Matching` | — | — | InstanceEditable, Private |
| `ValidDatabases` | `TArray<object<PoseSearchDatabase>>` | — | `Motion Matching` | — | — | InstanceEditable, Private |
| `MM Search Cost` | `real<float>` | `0.000000` | `Motion Matching` | — | — | InstanceEditable, Private |
| `CurrentDatabaseTags` | `TArray<name>` | — | `Motion Matching` | — | — | InstanceEditable, Private |
| `HeavyLandSpeedThreshold` | `real<double>` | `700.000000` | `Essential Values` | — | — | InstanceEditable, Private |
| `InteractionTransform` | `struct<Transform>` | `(Rotation=(X=0.000000,Y=0.000000,Z=0.000000,W=1.000000),Translation=(X=0.000000,Y=0.000000,Z=0.000000),Scale3D=(X=1.000000,Y=1.000000,Z=1.000000))` | `Essential Values` | — | — | InstanceEditable, Private |
| `Trj_PastVelocity` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Trajectory` | — | — | InstanceEditable, Private |
| `Trj_CurrentVelocity` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Trajectory` | — | — | InstanceEditable, Private |
| `Trj_FutureVelocity` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Trajectory` | — | — | InstanceEditable, Private |
| `OffsetRootBoneEnabled` | `bool` | `False` | `Essential Values` | — | — | InstanceEditable, Private |
| `BlendStackInputs` | `struct<S_BlendStackInputs>` | `()` | `State Machine (Experimental) \| AnimGraph` | — | — | InstanceEditable, Private |
| `Previous_BlendStackInputs` | `struct<S_BlendStackInputs>` | `()` | `State Machine (Experimental) \| AnimGraph` | — | — | InstanceEditable, Private |
| `StateMachineState` | `byte<E_ExperimentalStateMachineState>` | `NewEnumerator0` | `State Machine (Experimental) \| AnimGraph` | — | — | InstanceEditable, Private |
| `NoValidAnim` | `bool` | `True` | `State Machine (Experimental) \| AnimGraph` | — | — | InstanceEditable, Private |
| `NotifyTransition_Re-Transition` | `bool` | `False` | `State Machine (Experimental) \| AnimGraph` | — | — | InstanceEditable, Private |
| `NotifyTransition_ToLoop` | `bool` | `False` | `State Machine (Experimental) \| AnimGraph` | — | — | InstanceEditable, Private |
| `DebugExperimentalStateMachine` | `bool` | `False` | `State Machine (Experimental) \| Debug` | — | — | InstanceEditable, Private |
| `UseExperimentalStateMachine` | `bool` | `False` | `State Machine (Experimental)` | — | — | InstanceEditable, Private |
| `PlantSettings_Default` | `struct<FootPlacementPlantSettings>` | `(SpeedThreshold=1.000000,DistanceToGround=10.000000,LockType=PivotAroundBall,UnplantRadius=20.000000,ReplantRadiusRatio=0.200000,UnplantAngle=60.000000,ReplantAngleRatio=0.200000,MaxExtensionRatio=0.500000,MinExtensionRatio=0.200000,UnalignmentSpeedThreshold=100.000000,AnkleTwistReduction=0.750000)` | `Foot Placement` | — | — | InstanceEditable, Private |
| `PlantSettings_Stops` | `struct<FootPlacementPlantSettings>` | `(SpeedThreshold=1.000000,DistanceToGround=10.000000,LockType=PivotAroundBall,UnplantRadius=40.000000,ReplantRadiusRatio=0.750000,UnplantAngle=60.000000,ReplantAngleRatio=0.200000,MaxExtensionRatio=0.500000,MinExtensionRatio=0.200000,UnalignmentSpeedThreshold=100.000000,AnkleTwistReduction=0.750000)` | `Foot Placement` | — | — | InstanceEditable, Private |
| `InterpolationSettings_Default` | `struct<FootPlacementInterpolationSettings>` | `(UnplantLinearStiffness=100.000000,UnplantLinearDamping=1.000000,UnplantAngularStiffness=450.000000,UnplantAngularDamping=1.000000,SeparationStiffness=1000.000000,SeparationDamping=1.000000,FloorLinearStiffness=1000.000000,FloorLinearDamping=1.000000,FloorAngularStiffness=450.000000,FloorAngularDamping=1.000000,bEnableFloorInterpolation=True,bEnableSeparationInterpolation=True)` | `Foot Placement` | — | — | InstanceEditable, Private |
| `InterpolationSettings_Stops` | `struct<FootPlacementInterpolationSettings>` | `(UnplantLinearStiffness=250.000000,UnplantLinearDamping=1.000000,UnplantAngularStiffness=450.000000,UnplantAngularDamping=1.000000,SeparationStiffness=1000.000000,SeparationDamping=1.000000,FloorLinearStiffness=1000.000000,FloorLinearDamping=1.000000,FloorAngularStiffness=450.000000,FloorAngularDamping=1.000000,bEnableFloorInterpolation=True,bEnableSeparationInterpolation=True)` | `Foot Placement` | — | — | InstanceEditable, Private |
| `MovementDirection` | `byte<E_MovementDirection>` | `NewEnumerator0` | `State Machine (Experimental) \| Movement Direction` | — | — | InstanceEditable, Private |
| `MovementDirectionLastFrame` | `byte<E_MovementDirection>` | `NewEnumerator0` | `State Machine (Experimental) \| Movement Direction` | — | — | InstanceEditable, Private |
| `MovementDirectionBias` | `byte<E_MovementDirectionBias>` | `NewEnumerator0` | `State Machine (Experimental) \| Movement Direction` | — | — | InstanceEditable, Private |
| `MovementDirectionThresholds` | `struct<S_MovementDirectionThresholds>` | `(FL_3_747C69604F939E7EFF347D97BBD8A811=-60.000000,FR_5_790F2C4742CB53A5585DBFAF660F9CF0=60.000000,BL_7_630ADC5A4B6C3AF9DA182E816EDB311B=-120.000000,BR_9_67DF35F84900050330F770A709E84CF7=120.000000)` | `State Machine (Experimental) \| Movement Direction` | — | — | InstanceEditable, Private |
| `TargetRotation` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `State Machine (Experimental) \| Target Rotation` | — | — | InstanceEditable, Private |
| `TargetRotationOnTransitionStart` | `struct<Rotator>` | `(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)` | `State Machine (Experimental) \| Target Rotation` | — | — | InstanceEditable, Private |
| `OffsetRootTranslationRadius` | `real<double>` | `0.000000` | `Root Offset` | — | — | InstanceEditable, Private |
| `HasOwningActor` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `UseThreadSafeUpdateAnimation` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Search Cost` | `real<float>` | `0.000000` | `State Machine (Experimental)\|Anim Graph` | — | — | InstanceEditable, Private |
| `TargetRotationDelta` | `real<double>` | `0.000000` | `State Machine (Experimental) \| Target Rotation` | — | — | InstanceEditable, Private |
| `LocomotionSetup` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `Mover` | `object<MoverComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `FootPlacementMode` | `int` | `0` | `Foot Placement` | — | — | InstanceEditable, Private |
| `ValidAnims` | `TArray<object<AnimationAsset>>` | — | `State Machine (Experimental)\|Anim Graph` | — | — | InstanceEditable, Private |
| `TransitionHistory` | `TArray<string>` | `("None")` | `Debug` | — | — | InstanceEditable, Private |
| `PawnSpeedHistory` | `TArray<real<float>>` | — | `Debug` | — | — | InstanceEditable, Private |
| `MoveData_Speed_History` | `TArray<real<float>>` | — | `Debug` | — | — | InstanceEditable, Private |
| `Phase_History` | `TArray<real<float>>` | — | `Debug` | — | — | InstanceEditable, Private |
| `Contact_L_History` | `TArray<real<float>>` | — | `Debug` | — | — | InstanceEditable, Private |
| `Contact_R_History` | `TArray<real<float>>` | — | `Debug` | — | — | InstanceEditable, Private |
| `Enable_Warping_History` | `TArray<real<float>>` | — | `Debug` | — | — | InstanceEditable, Private |

## Functions (68)

### `AllowFootPinning`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 6

### `AnimGraph`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 31

### `BlueprintThreadSafeUpdateAnimation`

- Access: `Public`
- Flags: —
- Inputs: `(real<float> DeltaTime = 0.0)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

### `CalculateRelativeAccelerationAmount`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> ReturnValue, struct<Vector> ReturnValue)`
- Local variables: _none_
- Nodes: 29
- Category: `Additive Lean`

### `Debug_ExperimentalStateMachine`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (3): `MeshLocation`, `DrawOrigin`, `DrawRotation`
- Nodes: 171
- Category: `State Machine (Experimental) | Debug`

### `Enable_AO`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 13
- Category: `Aim Offset`

### `EnableSteering`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimNodeReference>& Node [ref])`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 10
- Category: `Steering`

### `Get_AO_Yaw`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 6
- Category: `Aim Offset`

### `Get_AOValue`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector2D> ReturnValue, real<double> ReturnValue_X, real<double> ReturnValue_Y)`
- Local variables: _none_
- Nodes: 10
- Category: `Aim Offset`

### `Get_DesiredFacing`

- Access: `Public`
- Flags: —
- Inputs: `()`
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
- Nodes: 53
- Category: `State Machine (Experimental) | AnimGraph`

### `Get_FootPlacementInterpolationSettings`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<FootPlacementInterpolationSettings> ReturnValue)`
- Local variables: _none_
- Nodes: 13
- Category: `Foot Placement`

### `Get_FootPlacementPlantSettings`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<FootPlacementPlantSettings> ReturnValue)`
- Local variables: _none_
- Nodes: 13
- Category: `Foot Placement`

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

### `Get_LeanAmount`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector2D> ReturnValue, real<double> ReturnValue_X, real<double> ReturnValue_Y)`
- Local variables: _none_
- Nodes: 7
- Category: `Additive Lean`

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
- Nodes: 24
- Category: `Motion Matching`

### `Get_MMNotifyRecencyTimeOut`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 9
- Category: `Motion Matching`

### `Get_MovementDirectionThresholds`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<S_MovementDirectionThresholds> ReturnValue, real<double> ReturnValue_FL_3_747C69604F939E7EFF347D97BBD8A811, real<double> ReturnValue_FR_5_790F2C4742CB53A5585DBFAF660F9CF0, real<double> ReturnValue_BL_7_630ADC5A4B6C3AF9DA182E816EDB311B, real<double> ReturnValue_BR_9_67DF35F84900050330F770A709E84CF7, struct<S_MovementDirectionThresholds> ReturnValue, real<double> ReturnValue_FL_3_747C69604F939E7EFF347D97BBD8A811, real<double> ReturnValue_FR_5_790F2C4742CB53A5585DBFAF660F9CF0, real<double> ReturnValue_BL_7_630ADC5A4B6C3AF9DA182E816EDB311B, real<double> ReturnValue_BR_9_67DF35F84900050330F770A709E84CF7, struct<S_MovementDirectionThresholds> ReturnValue, real<double> ReturnValue_FL_3_747C69604F939E7EFF347D97BBD8A811, real<double> ReturnValue_FR_5_790F2C4742CB53A5585DBFAF660F9CF0, real<double> ReturnValue_BL_7_630ADC5A4B6C3AF9DA182E816EDB311B, real<double> ReturnValue_BR_9_67DF35F84900050330F770A709E84CF7)`
- Local variables: _none_
- Nodes: 17
- Category: `State Machine (Experimental) | Movement Direction`

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
- Outputs: `(byte ReturnValue, byte ReturnValue, byte ReturnValue, byte ReturnValue)`
- Local variables: _none_
- Nodes: 12
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

### `Get_PoseHistory_Old`

- Interface override of `/Game/_ThirdParty/GASP_example/Blueprints/Data/BPI_InteractionTransform.BPI_InteractionTransform_C`
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

### `Get_StrafeYawRotationOffset`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables (1): `MappedDirection`
- Nodes: 15
- Category: `State Machine (Experimental) | Target Rotation`

### `Get_TrajectoryTurnAngle`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 8
- Category: `Movement Analysis`

### `GetInteractionTransform_Old`

- Interface override of `/Game/_ThirdParty/GASP_example/Blueprints/Data/BPI_InteractionTransform.BPI_InteractionTransform_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Transform> InteractionTransform)`
- Local variables: _none_
- Nodes: 3

### `IsAnimationAlmostComplete`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 10
- Category: `State Machine (Experimental) | AnimGraph`

### `IsMoving`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 10
- Category: `Movement Analysis`

### `IsPivoting`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 9
- Category: `Movement Analysis`

### `IsStarting`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 14
- Category: `Movement Analysis`

### `JustLanded_Heavy`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 10
- Category: `Movement Analysis`

### `JustLanded_Light`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 10
- Category: `Movement Analysis`

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
- Category: `State Machine (Experimental) | AnimGraph`

### `OnStateEntry_IdleLoop`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `State Machine (Experimental) | AnimGraph`

### `OnStateEntry_InAirLoop`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `State Machine (Experimental) | AnimGraph`

### `OnStateEntry_LocomotionLoop`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `State Machine (Experimental) | AnimGraph`

### `OnStateEntry_SlideLoop`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `State Machine (Experimental) | AnimGraph`

### `OnStateEntry_TransitionToIdle`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `State Machine (Experimental) | AnimGraph`

### `OnStateEntry_TransitionToInAir`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `State Machine (Experimental) | AnimGraph`

### `OnStateEntry_TransitionToLocomotion`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `State Machine (Experimental) | AnimGraph`

### `OnStateEntry_TransitionToSlide`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `State Machine (Experimental) | AnimGraph`

### `OnUpdate_TransitionToLocomotion`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `State Machine (Experimental) | AnimGraph`

### `PlayLand`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 8
- Category: `Movement Analysis`

### `PlayMovingLand`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 11
- Category: `Movement Analysis`

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
- Local variables (2): `ChooserOutputs`, `ChooserResult`
- Nodes: 64
- Category: `State Machine (Experimental) | AnimGraph`

### `SetInteractionTransform_Old`

- Interface override of `/Game/_ThirdParty/GASP_example/Blueprints/Data/BPI_InteractionTransform.BPI_InteractionTransform_C`
- Access: `Public`
- Flags: —
- Inputs: `(struct<Transform> InteractionTransform)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

### `ShouldSpinTransition`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 14
- Category: `Movement Analysis`

### `ShouldTurnInPlace`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 16
- Category: `Movement Analysis`

### `Update_CVarDrivenVariables`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 25
- Category: `Event Graph`

### `Update_EssentialValues`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 53
- Category: `Event Graph`

### `Update_Logic`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8
- Category: `Event Graph`

### `Update_MotionMatching`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9
- Category: `Motion Matching`

### `Update_MotionMatching_PostSelection`

- Access: `Public`
- Flags: —
- Inputs: `(struct<AnimUpdateContext>& Context [ref], struct<AnimNodeReference>& Node [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13
- Category: `Motion Matching`

### `Update_MovementDirection`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `Direction`, `TargetMovementDirection`
- Nodes: 49
- Category: `State Machine (Experimental) | Movement Direction`

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
- Nodes: 30
- Category: `Event Graph`

### `Update_TargetRotation`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 25
- Category: `State Machine (Experimental) | Target Rotation`

### `Update_Trajectory`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `NewLocalVar`
- Nodes: 27
- Category: `Event Graph`

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `bUsingCopyPoseFromMesh` (`uint8`) = `True`

## Graphs

- Event graph: `EventGraph` (15 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## State Machines

- **State Controller** (8 states, 22 transitions)
  - State `Conduit` [Conduit] (1 nodes)
  - State `Idle Break` [State] (1 nodes)
  - State `Idle Loop` [State] (1 nodes)
  - State `In Air Loop` [State] (1 nodes)
  - State `Locomotion Loop` [State] (1 nodes)
  - State `Transition to Idle` [State] (1 nodes)
  - State `Transition to In Air` [State] (1 nodes)
  - State `Transition to Locomotion` [State] (1 nodes)
  - Transition `-> Grounded` → `Conduit` [StandardBlend] crossfade=0.20s
  - Transition `-> In Air` → `Transition to In Air` [StandardBlend] crossfade=0.20s
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
  - Transition `Re-Enter ` → `Transition to Idle` [StandardBlend] crossfade=0.20s
  - Transition `Re-Enter ` → `Transition to Idle` [StandardBlend] crossfade=0.20s
  - Transition `Transition to Idle` → `Idle Loop` [StandardBlend]
  - Transition `Transition to Idle` → `Idle Loop` [StandardBlend]
  - Transition `Transition to In Air` → `In Air Loop` [StandardBlend]
  - Transition `Transition to In Air` → `In Air Loop` [StandardBlend]
  - Transition `Transition to Locomotion` → `Locomotion Loop` [StandardBlend]
  - Transition `Transition to Locomotion` → `Locomotion Loop` [Custom] crossfade=0.20s
  - Transition `Transition to Locomotion` → `Locomotion Loop` [StandardBlend]

## References

Hard refs out (43):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_ABP` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_Pawn` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/BFL_HelpfulFunctions` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/BPI_InteractionTransform` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_ExperimentalStateMachineState` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_Gait` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_MovementDirection` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_MovementDirectionBias` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_MovementMode` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_MovementState` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_RotationMode` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_Stance` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_BlendStackInputs` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_CharacterPropertiesForAnimation` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_ChooserOutputs` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_DebugGraphLineProperties` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_MovementDirectionThresholds` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_PlayerInputState` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/AimOffset/AO_Blend_Curve` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/AimOffset/BS_Neutral_AO_Stand` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/ExperimentalStateMachineData/CHT_CMCCharacterAnimations` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/ExperimentalStateMachineData/StrafeOffsetCurveContainer` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/MotionMatchingData/CHT_PoseSearchDatabases` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Poses/BS1D_Additive_Lean_Run` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Meshes/SK_UEFN_Mannequin` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Rigs/MDT_UEFN_Mannequin` [asset]
- `/Script/AnimationWarpingEditor` [asset]
- `/Script/AnimationWarpingRuntime` [asset]
- `/Script/AnimGraph` [asset]
- `/Script/AnimGraphRuntime` [asset]
- `/Script/BlendStack` [asset]
- `/Script/BlendStackEditor` [asset]
- `/Script/Chooser` [asset]
- `/Script/ChooserUncooked` [asset]
- `/Script/CurveExpression` [asset]
- `/Script/CurveExpressionEditor` [asset]
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

