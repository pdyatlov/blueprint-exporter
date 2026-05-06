# TestGameActor

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Standards/GameActor/Tests/TestGameActor.TestGameActor` |
| Asset name | `TestGameActor` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces (2):
  - `/Game/Standards/GameActor/iGameActor.iGameActor_C`
  - `/Game/Standards/iDamagable.iDamagable_C`

## Variables (2)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `SimulationLOD` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `UpscaleLOD` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |

## Functions (2)

### `GetLocallyOwned`

- Interface override of `/Game/Standards/GameActor/iGameActor.iGameActor_C`
- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool IsLocallyOwned)`
- Local variables: _none_
- Nodes: 2

### `STORE`

- Interface override of `/Game/Standards/GameActor/iGameActor.iGameActor_C`
- Access: `Public`
- Flags: —
- Inputs: `(TArray<struct<sFourInts>>& StorageData [ref])`
- Outputs: `(byte NumberOfDataAdded)`
- Local variables: _none_
- Nodes: 2

## Macros (1)

### `DebugPrint`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13

## Components (2)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`
  - `Sphere` — `StaticMeshComponent` @ socket `None`
- `GameComponent` — `GameComponent_C` @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (18 nodes)
- Construction script: `UserConstructionScript` (4 nodes)
- Additional graphs: _none_

## References

Hard refs out (8):
- `/Engine/BasicShapes/BasicShapeMaterial` [asset]
- `/Engine/BasicShapes/Sphere` [asset]
- `/Game/Standards/GameActor/Data/sFourBytes` [asset]
- `/Game/Standards/GameActor/Data/sFourInts` [asset]
- `/Game/Standards/GameActor/GameComponent` [asset]
- `/Game/Standards/GameActor/iGameActor` [asset]
- `/Game/Standards/iDamagable` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

