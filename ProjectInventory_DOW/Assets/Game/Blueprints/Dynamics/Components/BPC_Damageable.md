# BPC_Damageable

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/Dynamics/Components/BPC_Damageable.BPC_Damageable` |
| Asset name | `BPC_Damageable` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `SceneComponent` (`/Script/Engine.SceneComponent`, native, module `/Script/Engine`)
- Interfaces (1):
  - `/Game/Standards/iDamagable.iDamagable_C`

## Variables (10)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Alive` | `bool` | `True` | `Setup` | — | — | InstanceEditable, Private |
| `Destructible` | `bool` | `False` | `Setup` | — | — | InstanceEditable |
| `Custom Destroy Event` | `bool` | `False` | `Setup` | — | — | InstanceEditable |
| `DestructionDelay` | `real<double>` | `0.000000` | `Setup` | — | — | InstanceEditable |
| `Health` | `real<double>` | `100.000000` | `Setup` | — | — | InstanceEditable |
| `DamageTaken` | `real<double>` | `0.000000` | `Private` | — | — | InstanceEditable, Private |
| `DestroyedTime` | `real<double>` | `5.000000` | `Private` | — | — | InstanceEditable, Private |
| `Current Health` | `real<double>` | `0.000000` | `Private` | — | — | InstanceEditable |
| `AfterDamage` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `Custom Destroyed` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |

## Functions (1)

### `OnDestroyed_Event`

- Access: `Public`
- Flags: —
- Inputs: `(object<Actor> DestroyedActor1)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `PrimaryComponentTick` (`FActorComponentTickFunction`) = `(bCanEverTick=True,bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (68 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (2):
- `/Game/Standards/iDamagable` [asset]
- `/Script/Engine.SceneComponent` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

