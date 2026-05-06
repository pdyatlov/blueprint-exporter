# AC_WeaponManager

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Loadout/AC_WeaponManager.AC_WeaponManager` |
| Asset name | `AC_WeaponManager` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ActorComponent` (`/Script/Engine.ActorComponent`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (9)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `PlayerLoadout` | `object<DA_PlayerLoadout_C>` | `/Game/_ThirdParty/GASP_example/Loadout/Blueprints/DataAssets/DA_PlayerLoadout.DA_PlayerLoadout_C'/Game/_ThirdParty/GASP_example/Loadout/Blueprints/Loadouts/DA_PlayerLoadout_Default.DA_PlayerLoadout_Default'` | `Default` | — | — | InstanceEditable |
| `CurrentSlot` | `byte<EWeaponSlot>` | `NewEnumerator0` | `Default` | — | — | InstanceEditable, Private |
| `CurrentWeapon` | `object<BP_WeaponBase_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `PrimaryWeaponInstance` | `object<BP_WeaponBase_C>` | `None` | `Default` | — | — | InstanceEditable |
| `SecondaryWeaponInstance` | `object<BP_WeaponBase_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `MeleeWeaponInstance` | `object<BP_WeaponBase_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `DefinedPrimary` | `object<DA_WeaponDefinition_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `DefinedSecondary` | `object<DA_WeaponDefinition_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `DefinedMelee` | `object<DA_WeaponDefinition_C>` | `None` | `Default` | — | — | InstanceEditable, Private |

## Functions (7)

### `AddAttachments`

- Access: `Public`
- Flags: —
- Inputs: `(object<DA_WeaponDefinition_C> DefinedWeapon, object<BP_WeaponBase_C> SpawnedWeaponInstance)`
- Outputs: `()`
- Local variables (1): `BarrelToAttach`
- Nodes: 31
- Category: `Default`

### `CalculateWeaponStats`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1
- Category: `Default`

### `GetFiringSocketLocation`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector> FiringSocketLocation)`
- Local variables: _none_
- Nodes: 5

### `GetOwnerPawn`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(object<Pawn> OwnerPawn)`
- Local variables: _none_
- Nodes: 7
- Category: `Default`

### `InitializeFromLoadout`

- Access: `Public`
- Flags: —
- Inputs: `(object<DA_PlayerLoadout_C> InLoadout)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11

### `SpawnWeaponBase`

- Access: `Public`
- Flags: —
- Inputs: `(object<DA_WeaponDefinition_C> WeaponDef, object<Pawn> OwnerPawn)`
- Outputs: `(object<BP_WeaponBase_C> SpawnedWeapon)`
- Local variables: _none_
- Nodes: 31

### `SwitchWeaponSlot`

- Access: `Public`
- Flags: —
- Inputs: `(byte NewSlot = NewEnumerator0)`
- Outputs: `()`
- Local variables (2): `NewWeapon`, `NewEquipSocketName`
- Nodes: 45

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (54 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (13):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/PlayerPawn/SandboxCharacter_Mover` [asset]
- `/Game/_ThirdParty/GASP_example/Loadout/Blueprints/BP_AttachmentBase` [asset]
- `/Game/_ThirdParty/GASP_example/Loadout/Blueprints/BP_WeaponBase` [asset]
- `/Game/_ThirdParty/GASP_example/Loadout/Blueprints/DataAssets/DA_AttachmentDefinition` [asset]
- `/Game/_ThirdParty/GASP_example/Loadout/Blueprints/DataAssets/DA_PlayerLoadout` [asset]
- `/Game/_ThirdParty/GASP_example/Loadout/Blueprints/DataAssets/DA_WeaponDefinition` [asset]
- `/Game/_ThirdParty/GASP_example/Loadout/Blueprints/Loadouts/DA_PlayerLoadout_Default` [asset]
- `/Game/_ThirdParty/GASP_example/Loadout/BP_Player` [asset]
- `/Game/_ThirdParty/GASP_example/Loadout/BPI_Weapon` [asset]
- `/Game/_ThirdParty/GASP_example/Loadout/Enums/EWeaponSlot` [asset]
- `/Script/Engine.ActorComponent` [native]
- `/Script/InputCore` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

