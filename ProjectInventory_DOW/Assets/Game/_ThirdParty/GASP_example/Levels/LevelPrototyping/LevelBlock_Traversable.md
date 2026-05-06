# LevelBlock_Traversable

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/LevelBlock_Traversable.LevelBlock_Traversable` |
| Asset name | `LevelBlock_Traversable` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `LevelBlock_C` (`/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/LevelBlock.LevelBlock_C`, blueprint)
- Interfaces: _none_

## Variables (3)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Ledges` | `TArray<object<SplineComponent>>` | — | `Default` | — | — | InstanceEditable, Private |
| `OppositeLedges` | `TMap<object<SplineComponent>>, object:/Script/Engine.SplineComponent>` | `()` | `Default` | — | — | InstanceEditable, Private |
| `MinLedgeWidth` | `real<double>` | `60.000000` | `Default` | — | — | InstanceEditable, Private |

## Functions (2)

### `FindLedgeClosestToActor`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector>& ActorLocation [ref])`
- Outputs: `(object<SplineComponent> ReturnValue, object<SplineComponent> ReturnValue)`
- Local variables (2): `ClosestDistance`, `ClosestIndex`
- Nodes: 29
- Category: `Default`

### `GetLedgeTransforms`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> HitLocation, struct<Vector> ActorLocation, struct<S_TraversalCheckResult>& TraversalTraceResultInOut [ref])`
- Outputs: `()`
- Local variables (2): `ClosestLedge`, `OppositeLedge`
- Nodes: 48
- Category: `Default`

## Macros (0)

_None._

## Components (4)

- `Ledge_1` — `SplineComponent` @ socket `None`
- `Ledge_2` — `SplineComponent` @ socket `None`
- `Ledge_3` — `SplineComponent` @ socket `None`
- `Ledge_4` — `SplineComponent` @ socket `None`

## Class Default Object (2)

- `AutoNameFromHeight` (`bool`) = `True`
- `ColorGroup` (`FName`) = `Blocks_Traversable`

## Graphs

- Event graph: `EventGraph` (3 nodes)
- Construction script: `UserConstructionScript` (18 nodes)
- Additional graphs: _none_

## References

Hard refs out (4):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_TraversalCheckResult` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/LevelBlock` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/LevelBlock.LevelBlock_C` [Blueprint]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

