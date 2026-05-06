# BP_WP

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Developers/andersjansson/Mission/BP_WP.BP_WP` |
| Asset name | `BP_WP` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (9)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Widget` | `object<WBP_WP_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `NextWP` | `object<BP_WP_C>` | `None` | `Default` | — | — | InstanceEditable |
| `First` | `bool` | `False` | `Default` | — | — | InstanceEditable |
| `ActivationText` | `text` | `NSLOCTEXT("[BF7A86A432EBAA02CBA0D98E898BD67B]", "A58D7FBA4B80FA3DA772E2B35D31CE51", "Reach Objective")` | `Default` | — | — | InstanceEditable |
| `ReachedText` | `text` | `NSLOCTEXT("[BF7A86A432EBAA02CBA0D98E898BD67B]", "07EC76FD4833FF8D622B659764F31F5B", "Objective Reached")` | `Default` | — | — | InstanceEditable |
| `NextObjectiveDelay` | `real<float>` | `6.000000` | `Default` | — | — | InstanceEditable |
| `ActivateDelay` | `real<float>` | `0.200000` | `Default` | — | — | InstanceEditable |
| `IsActive` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `MissionID` | `string` | — | `Default` | — | — | InstanceEditable |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`
  - `Sphere` — `SphereComponent` @ socket `None`

## Class Default Object (1)

- `PrimaryActorTick` (`FActorTickFunction`) = `(bCanEverTick=True,bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (78 nodes)
- Construction script: `UserConstructionScript` (1 nodes)
- Additional graphs: _none_

## References

Hard refs out (7):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Developers/andersjansson/Mission/WBP_ObjText` [asset]
- `/Game/Developers/andersjansson/Mission/WBP_WP` [asset]
- `/Script/Engine.Actor` [native]
- `/Script/NavigationSystem` [asset]
- `/Script/UMG` [asset]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

