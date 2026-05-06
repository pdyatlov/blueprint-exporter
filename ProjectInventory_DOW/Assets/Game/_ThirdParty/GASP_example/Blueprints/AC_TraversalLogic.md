# AC_TraversalLogic

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/AC_TraversalLogic.AC_TraversalLogic` |
| Asset name | `AC_TraversalLogic` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ActorComponent` (`/Script/Engine.ActorComponent`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (6)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `CharacterProperties` | `struct<S_CharacterPropertiesForTraversal>` | `()` | `Default` | — | — | InstanceEditable, Private |
| `TraversalResult` | `struct<S_TraversalCheckResult>` | `(FrontLedgeLocation_50_52B8B8A84F10B0E0A9F287972F2C54D8=(X=0.000000,Y=0.000000,Z=0.000000),FrontLedgeNormal_51_3C4F46204EAF10E382D4D9A8E26ACB5A=(X=0.000000,Y=0.000000,Z=0.000000),BackLedgeLocation_55_EB7453EF477E18645DAD9F8950BCF44F=(X=0.000000,Y=0.000000,Z=0.000000),BackLedgeNormal_56_F05B9B4A4046704A49754F80A8C7BCE3=(X=0.000000,Y=0.000000,Z=0.000000),BackFloorLocation_58_0BB660F246B00F3211984E9AC5FE310D=(X=0.000000,Y=0.000000,Z=0.000000))` | `Default` | — | — | InstanceEditable, Private |
| `DoingTraversalAction` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Mesh` | `object<SkeletalMeshComponent>` | `None` | `Default` | — | — | InstanceEditable |
| `IsMoverCharacter` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Mover` | `object<CharacterMoverComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |

## Functions (4)

### `SetMovementMode`

- Access: `Public`
- Flags: —
- Inputs: `(byte NewMovementMode = MOVE_None)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14

### `SetReplicationBehavior`

- Access: `Public`
- Flags: —
- Inputs: `(bool ClientAuthoritative)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11

### `SetWarpTargets`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (3): `AnimatedDistanceFromFrontLedgeToBackLedge`, `AnimatedDistanceFromFrontLedgeToBackFloor`, `MotionWarping`
- Nodes: 78
- Category: `Default`

### `TryTraversalAction`

- Access: `Public`
- Flags: —
- Inputs: `(struct<S_TraversalCheckInputs> Inputs, byte DebugType = None)`
- Outputs: `(bool TraversalCheckFailed, bool MontageSelectionFailed, bool TraversalCheckFailed, bool MontageSelectionFailed, bool TraversalCheckFailed, bool MontageSelectionFailed, bool TraversalCheckFailed, bool MontageSelectionFailed, bool TraversalCheckFailed, bool MontageSelectionFailed)`
- Local variables (10): `TraversalCheckResult`, `ActorLocation`, `CapsuleRadius`, `CapsuleHalfHeight`, `HasRoomCheck_FrontLedgeLocation`, `HasRoomCheck_BackLedgeLocation`, `TopSweepResult`, `DrawDebugLevel`, `DrawDebugDuration`, `ValidMontages`
- Nodes: 241
- Category: `Default`

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (51 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (25):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_ABP` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/BPI_SandboxCharacter_Pawn` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_Gait` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_MovementMode` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/E_TraversalActionType` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_CharacterPropertiesForTraversal` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_TraversalCheckInputs` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_TraversalCheckResult` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_TraversalChooserInputs` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_TraversalChooserOutputs` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Traversal/CHT_TraversalMontages_CMC` [asset]
- `/Game/_ThirdParty/GASP_example/Characters/UEFN_Mannequin/Animations/Traversal/CHT_TraversalMontages_Mover` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/LevelBlock_Traversable` [asset]
- `/Script/AnimationWarpingRuntime` [asset]
- `/Script/AnimGraph` [asset]
- `/Script/AnimGraphRuntime` [asset]
- `/Script/Chooser` [asset]
- `/Script/ChooserUncooked` [asset]
- `/Script/Engine.ActorComponent` [native]
- `/Script/MotionWarping` [asset]
- `/Script/Mover` [asset]
- `/Script/MoverEditor` [asset]
- `/Script/PhysicsCore` [asset]
- `/Script/PoseSearch` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

