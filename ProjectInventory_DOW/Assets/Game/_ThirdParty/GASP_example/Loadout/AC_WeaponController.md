# AC_WeaponController

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Loadout/AC_WeaponController.AC_WeaponController` |
| Asset name | `AC_WeaponController` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ActorComponent` (`/Script/Engine.ActorComponent`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (51)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `bWantsToFire` | `bool` | `False` | `OLD Queue Shot Buffer` | — | — | InstanceEditable, Private |
| `BufferWindow` | `real<double>` | `0.240000` | `OLD Queue Shot Buffer` | — | — | InstanceEditable, Private |
| `bBufferedShot` | `bool` | `False` | `OLD Queue Shot Buffer` | — | — | InstanceEditable, Private |
| `bIsFiring` | `bool` | `False` | `OLD Gun States` | — | — | InstanceEditable, Private |
| `bIsReloading` | `bool` | `False` | `OLD Gun States` | — | — | InstanceEditable, Private |
| `OLD_currentAmmo` | `int` | `1` | `OLD` | — | — | InstanceEditable, Private |
| `FireTimerHandle` | `struct<TimerHandle>` | `()` | `OLD Gun States` | — | — | InstanceEditable, Private |
| `OLD_FireRate` | `real<double>` | `0.100000` | `OLD` | — | — | InstanceEditable, Private |
| `OnFireLoopStart` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `OnFireLoopStop` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `OnFireShot` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `NextAllowedFireTime` | `real<double>` | `0.000000` | `OLD Gun States` | — | — | InstanceEditable, Private |
| `BufferedShotTimerHandle` | `struct<TimerHandle>` | `()` | `OLD Queue Shot Buffer` | — | — | InstanceEditable, Private |
| `OLD_IsFullyAuto` | `bool` | `True` | `OLD` | — | — | InstanceEditable, Private |
| `Owner` | `object<Actor>` | `None` | `INIT` | — | — | InstanceEditable, Private |
| `iWeaponOwner` | `interface<iWeaponOwner_C>` | `None` | `INIT` | — | — | InstanceEditable, Private |
| `RecoilReticleWidget` | `object<WBP_WeaponReticle_C>` | `None` | `INIT` | — | — | InstanceEditable, Private |
| `CurrentReticleOffsetPx` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `OLD Recoil` | — | — | InstanceEditable, Private |
| `PixelsPerYawUnit` | `real<double>` | `1.000000` | `OLD Recoil` | — | — | InstanceEditable, Private |
| `PixelsPerPitchUnit` | `real<double>` | `1.000000` | `OLD Recoil` | — | — | InstanceEditable, Private |
| `RecoilStrYaw` | `real<double>` | `1.000000` | `OLD Recoil` | — | — | InstanceEditable, Private |
| `RecoilStrPitch` | `real<double>` | `10.000000` | `OLD Recoil` | — | — | InstanceEditable, Private |
| `RecoilVelocity` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `RECOIL` | — | — | InstanceEditable, Private |
| `RecoilPosition` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `RECOIL` | — | — | InstanceEditable, Private |
| `FinalCameraRotationQuat` | `struct<Quat>` | `(X=0.000000,Y=0.000000,Z=0.000000,W=1.000000)` | `RECOIL` | — | — | InstanceEditable, Private |
| `RecoilSimStep` | `real<double>` | `0.001000` | `RECOIL` | — | — | InstanceEditable, Private |
| `RecoilSimFrameDelta` | `real<double>` | `0.001000` | `RECOIL` | — | — | InstanceEditable, Private |
| `TriggerBuffer` | `byte` | `0` | `TRIGGER` | — | — | InstanceEditable, Private |
| `TriggerBuffer_Max` | `byte` | `1` | `TRIGGER` | — | — | InstanceEditable, Private |
| `TriggerBuffer_Latest` | `real<double>` | `0.000000` | `TRIGGER` | — | — | InstanceEditable, Private |
| `TriggerBuffer_AddReq` | `real<double>` | `-1.000000` | `TRIGGER` | — | — | InstanceEditable, Private |
| `IsReloading` | `bool` | `False` | `AMMO` | — | — | InstanceEditable, Private |
| `ClipSize` | `int` | `0` | `AMMO` | — | — | InstanceEditable, Private |
| `MaxClipSize` | `int` | `0` | `AMMO` | — | — | InstanceEditable, Private |
| `FireRateTimer` | `real<double>` | `0.100000` | `FIRE` | — | — | InstanceEditable, Private |
| `FireRate` | `real<double>` | `0.050000` | `FIRE` | — | — | InstanceEditable, Private |
| `ProjectilesToFire` | `byte` | `1` | `FIRE` | — | — | InstanceEditable, Private |
| `ProjectilesToFireBuffer` | `byte` | `0` | `FIRE` | — | — | InstanceEditable, Private |
| `ProjectilesFiredInBurst` | `int` | `0` | `FIRE` | — | — | InstanceEditable, Private |
| `IsInfiniteBurstActive` | `bool` | `False` | `FIRE` | — | — | InstanceEditable, Private |
| `FireMode` | `byte<eFireFXMode>` | `NewEnumerator3` | `FIRE` | — | — | InstanceEditable, Private |
| `AimOrigin` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `AimPosition` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `AimTargetPosition` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `FPSCameraModifier` | `object<BP_FPS_CameraModifier_C>` | `None` | `INIT` | — | — | InstanceEditable, Private |
| `RecoilWorldSpaceWeight` | `struct<Vector2D>` | `(X=0.400000,Y=0.800000)` | `RECOIL` | — | — | InstanceEditable, Private |
| `RecoilDelay` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `RecoilSpringTimer` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `RecoilSpringTimerSpeed` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `RecoilPower` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `Damage_0` | `real<double>` | `10.000000` | `Default` | — | — | InstanceEditable, Private |

## Functions (16)

### `CanFireGlobal`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Can Fire)`
- Local variables: _none_
- Nodes: 8
- Category: `Default`

### `CanFireNow`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool CanFireNow)`
- Local variables: _none_
- Nodes: 7
- Category: `Default`

### `FireOneShot`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 19

### `GetOwnerAndRefs`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `Default`

### `GetWeaponsFromManager`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1
- Category: `Default`

### `HandleFirePressed`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

### `HandleFireReleased`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `InitialiseRecoilReticle`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Default`

### `RegisterRecoil`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector2D> Power, real<double> Delay, real<double> SpringTimerLength)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14
- Category: `Default`

### `SetRecoil`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2
- Category: `Default`

### `Spring`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector2D>& Velocity [ref], struct<Vector2D>& Position [ref], real<double> Delta, real<double> Frequency, real<double> Dampening)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 37
- Category: `Default`

### `StartFireLoop`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14

### `StopFireLoop`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

### `TryBufferShot`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `TimeRemaining`
- Nodes: 13

### `TryConsumeBufferedShot`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

### `UpdateCameraOffset`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Delta, struct<Quat> CameraQuaternion, struct<Vector> CameraPosition)`
- Outputs: `(struct<Quat> ModifiedRotation)`
- Local variables: _none_
- Nodes: 38

## Macros (3)

### `AddRecoilToSpringSim`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15

### `SpringSimulation`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 43

### `TraceApplyDamageAndUpdateTargetPosition`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 49

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `PrimaryComponentTick` (`FActorComponentTickFunction`) = `(bCanEverTick=True)`

## Graphs

- Event graph: `EventGraph` (205 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (12):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/PlayerPawn/SandboxCharacter_Mover` [asset]
- `/Game/_ThirdParty/GASP_example/Loadout/Widgets/WBP_WeaponReticle` [asset]
- `/Game/_ThirdParty/GASP_example/Standards/eFireFXMode` [asset]
- `/Game/_ThirdParty/GASP_example/Standards/iWeaponOwner` [asset]
- `/Game/_ThirdParty/GASP_example/Standards/Player/BP_FPS_CameraModifier` [asset]
- `/Game/_ThirdParty/GASP_example/Standards/sFireFXData` [asset]
- `/Game/Standards/iDamagable` [asset]
- `/Script/Engine.ActorComponent` [native]
- `/Script/InputCore` [asset]
- `/Script/PhysicsCore` [asset]
- `/Script/UMG` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

