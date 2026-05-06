# BP_Player

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Loadout/BP_Player.BP_Player` |
| Asset name | `BP_Player` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Character` (`/Script/Engine.Character`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (7)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `SensY` | `real<double>` | `1.300000` | `Default` | — | — | InstanceEditable |
| `SensX` | `real<double>` | `1.300000` | `Default` | — | — | InstanceEditable |
| `JumpWished` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `JumpReleased` | `bool` | `True` | `Default` | — | — | InstanceEditable, Private |
| `JumpBuffer` | `real<double>` | `0.200000` | `Default` | — | — | InstanceEditable, Private |
| `ToggleCrouch` | `bool` | `True` | `Default` | — | — | InstanceEditable, Private |
| `ToggleSprint` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (2)

- `PlayerCamera` — `CameraComponent` @ socket `None`
- `AC_WeaponManager` — `AC_WeaponManager_C` @ socket `None`

## Class Default Object (5)

- `ArrowComponent` (`TObjectPtr<UArrowComponent>`) [instanced] = `/Script/Engine.ArrowComponent'/Game/_ThirdParty/GASP_example/Loadout/BP_Player.Default__BP_Player_C:Arrow'`
- `CapsuleComponent` (`TObjectPtr<UCapsuleComponent>`) [instanced] = `/Script/Engine.CapsuleComponent'/Game/_ThirdParty/GASP_example/Loadout/BP_Player.Default__BP_Player_C:CollisionCylinder'`
- `CharacterMovement` (`TObjectPtr<UCharacterMovementComponent>`) [instanced] = `/Script/Engine.CharacterMovementComponent'/Game/_ThirdParty/GASP_example/Loadout/BP_Player.Default__BP_Player_C:CharM...`
- `Mesh` (`TObjectPtr<USkeletalMeshComponent>`) [instanced] = `/Script/Engine.SkeletalMeshComponent'/Game/_ThirdParty/GASP_example/Loadout/BP_Player.Default__BP_Player_C:CharacterM...`
- `RootComponent` (`TObjectPtr<USceneComponent>`) [instanced] = `/Script/Engine.CapsuleComponent'/Game/_ThirdParty/GASP_example/Loadout/BP_Player.Default__BP_Player_C:CollisionCylinder'`

## Graphs

- Event graph: `EventGraph` (36 nodes)
- Construction script: `UserConstructionScript` (1 nodes)
- Additional graphs: _none_

## References

Hard refs out (5):
- `/Game/_ThirdParty/GASP_example/Loadout/AC_WeaponManager` [asset]
- `/Game/_ThirdParty/GASP_example/Loadout/PlaceholderMeshes/SKM_Manny_Simple` [asset]
- `/Script/Engine.Character` [native]
- `/Script/InputCore` [asset]
- `/Script/NavigationSystem` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

