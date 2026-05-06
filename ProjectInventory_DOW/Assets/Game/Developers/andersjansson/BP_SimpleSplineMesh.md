# BP_SimpleSplineMesh

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Developers/andersjansson/BP_SimpleSplineMesh.BP_SimpleSplineMesh` |
| Asset name | `BP_SimpleSplineMesh` |
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
| `SplineMesh` | `object<StaticMesh>` | `/Script/Engine.StaticMesh'/Game/Art/Discovery/Noodles/SM_FloorCurb_A_Spline_01.SM_FloorCurb_A_Spline_01'` | `Default` | — | — | InstanceEditable |
| `SegmentLength` | `real<double>` | `400.000000` | `Default` | — | — | InstanceEditable |
| `DistStart` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `DistEnd` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `NumOfParts` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `Remainder` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |

## Functions (1)

### `DistanceCheck`

- Access: `Public`
- Flags: —
- Inputs: `(int A)`
- Outputs: `(struct<Vector> ReturnValue, struct<Vector> ReturnValue2)`
- Local variables: _none_
- Nodes: 9

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`
  - `Spline` — `SplineComponent` @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (3 nodes)
- Construction script: `UserConstructionScript` (27 nodes)
- Additional graphs: _none_

## References

Hard refs out (3):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Art/Discovery/Noodles/SM_FloorCurb_A_Spline_01` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

