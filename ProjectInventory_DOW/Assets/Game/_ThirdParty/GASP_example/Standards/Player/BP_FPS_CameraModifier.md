# BP_FPS_CameraModifier

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Standards/Player/BP_FPS_CameraModifier.BP_FPS_CameraModifier` |
| Asset name | `BP_FPS_CameraModifier` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `CameraModifier` (`/Script/Engine.CameraModifier`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (1)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Owner_AC_WeaponController` | `object<AC_WeaponController_C>` | `None` | `Default` | — | — | InstanceEditable, Private |

## Functions (1)

### `BlueprintModifyCamera`

- Access: `Public`
- Flags: —
- Net exec: BlueprintCosmetic
- Inputs: `(real<float> DeltaTime = 0.0, struct<Vector> ViewLocation = 0, 0, 0, struct<Rotator> ViewRotation = 0, 0, 0, real<float> FOV = 0.0)`
- Outputs: `(struct<Vector> NewViewLocation, struct<Rotator> NewViewRotation, real<float> NewFOV)`
- Local variables: _none_
- Nodes: 15

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (2):
- `/Game/_ThirdParty/GASP_example/Loadout/AC_WeaponController` [asset]
- `/Script/Engine.CameraModifier` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

