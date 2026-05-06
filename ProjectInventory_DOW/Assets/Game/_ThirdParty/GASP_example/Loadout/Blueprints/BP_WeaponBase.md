# BP_WeaponBase

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Loadout/Blueprints/BP_WeaponBase.BP_WeaponBase` |
| Asset name | `BP_WeaponBase` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (11)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `WeaponDefinition` | `object<DA_WeaponDefinition_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Damage` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `FireRate` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `RecoilStrengthMult` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `HipfireSpread` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `DamageDropOffRange` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `ReloadSpeedMult` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `ADS SpeedMult` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `EquipSpeedMult` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `MagSize` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `MagReserve` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |

## Functions (2)

### `InitializeBaseFromWeaponDefinition`

- Access: `Public`
- Flags: —
- Inputs: `(object<DA_WeaponDefinition_C> IncomingDefinition)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

### `SetWeaponVisibility`

- Access: `Public`
- Flags: —
- Inputs: `(bool bActive)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`
  - `SkeletalMesh` — `SkeletalMeshComponent` @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `UserConstructionScript` (1 nodes)
- Additional graphs: _none_

## References

Hard refs out (2):
- `/Game/_ThirdParty/GASP_example/Loadout/Blueprints/DataAssets/DA_WeaponDefinition` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

