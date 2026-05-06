# BP_SplineCylinder

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Developers/andersjansson/BP_SplineCylinder.BP_SplineCylinder` |
| Asset name | `BP_SplineCylinder` |
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
| `NumberOfSegments` | `int` | `4` | `Default` | — | — | InstanceEditable |
| `NumberOfCoils` | `int` | `1` | `Default` | — | — | InstanceEditable |
| `CoilRadius` | `real<double>` | `800.000000` | `Default` | — | — | InstanceEditable |
| `CoilHeight` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable |
| `DefaultSplineMesh` | `object<StaticMesh>` | `/Script/Engine.StaticMesh'/Game/Art/Discovery/Noodles/SM_CylindricalBuilding_A_01.SM_CylindricalBuilding_A_01'` | `Default` | — | — | InstanceEditable |
| `SplineMeshes` | `TArray<object<SplineMeshComponent>>` | — | `Default` | — | — | InstanceEditable, Private |
| `OverrideMesh` | `TArray<object<StaticMesh>>` | — | `Default` | — | — | InstanceEditable |
| `In Closed Loop` | `bool` | `True` | `Default` | — | — | InstanceEditable |
| `Degrees` | `int` | `360` | `Default` | — | — | InstanceEditable |

## Functions (1)

### `AddSplineMeshes`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 29

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`
  - `Spline` — `SplineComponent` @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (3 nodes)
- Construction script: `UserConstructionScript` (31 nodes)
- Additional graphs: _none_

## References

Hard refs out (3):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Art/Discovery/Noodles/SM_CylindricalBuilding_A_01` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

