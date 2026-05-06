# BP_CityMapStreaming

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/LevelStreaming/CityMap/BP_CityMapStreaming.BP_CityMapStreaming` |
| Asset name | `BP_CityMapStreaming` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (6)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `City District Data Asset` | `object<DA_CityMapDistrictList_C>` | `None` | `Default` | — | — | InstanceEditable |
| `City District Index` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `City District Loading Finished` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `City District Level Streams` | `TArray<object<LevelStreamingDynamic>>` | — | `Default` | — | — | InstanceEditable, Private |
| `Check City Districts States` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `City District Loading Timer` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`

## Class Default Object (1)

- `PrimaryActorTick` (`FActorTickFunction`) = `(bCanEverTick=True)`

## Graphs

- Event graph: `EventGraph` (54 nodes)
- Construction script: `UserConstructionScript` (1 nodes)
- Additional graphs: _none_

## References

Hard refs out (3):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Blueprints/LevelStreaming/CityMap/DA_CityMapDistrictList` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

