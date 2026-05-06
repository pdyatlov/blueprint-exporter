# BP_SplineFence

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Developers/andersjansson/Tools/BP_SplineFence.BP_SplineFence` |
| Asset name | `BP_SplineFence` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (7)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `PostMesh` | `object<StaticMesh>` | `/Script/Engine.StaticMesh'/Game/Art/EnvKits/Micro/Street/FenceAsianSet_A/SM_FenceAsian_Post_01.SM_FenceAsian_Post_01'` | `Default` | — | — | InstanceEditable |
| `FenceMesh` | `object<StaticMesh>` | `/Script/Engine.StaticMesh'/Game/Art/EnvKits/Micro/Street/FenceAsianSet_A/SM_FenceAsian_20_01.SM_FenceAsian_20_01'` | `Default` | — | — | InstanceEditable |
| `MeshLength` | `real<double>` | `200.000000` | `Default` | — | — | InstanceEditable, Private |
| `AmountOfSegments` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `Spacing` | `real<double>` | `200.000000` | `Default` | — | — | InstanceEditable |
| `CapEnd` | `bool` | `True` | `Default` | — | — | InstanceEditable |
| `MeshZRotation` | `real<float>` | `-90.000000` | `Default` | — | — | InstanceEditable |

## Functions (2)

### `GetLocationAtTime`

- Access: `Public`
- Flags: —
- Inputs: `(int A)`
- Outputs: `(struct<Vector> ReturnValue)`
- Local variables: _none_
- Nodes: 6

### `Populate`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 31

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`
  - `Spline` — `SplineComponent` @ socket `None`
    - `Fence` — `InstancedStaticMeshComponent` @ socket `None`
    - `FencePost` — `InstancedStaticMeshComponent` @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (3 nodes)
- Construction script: `UserConstructionScript` (11 nodes)
- Additional graphs: _none_

## References

Hard refs out (4):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Art/EnvKits/Micro/Street/FenceAsianSet_A/SM_FenceAsian_20_01` [asset]
- `/Game/Art/EnvKits/Micro/Street/FenceAsianSet_A/SM_FenceAsian_Post_01` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

