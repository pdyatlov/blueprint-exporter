# Teleporter_Sender

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Teleporter_Sender.Teleporter_Sender` |
| Asset name | `Teleporter_Sender` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (1)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Destination` | `object<Teleporter_Destination_C>` | `None` | `Default` | — | — | InstanceEditable |

## Functions (4)

### `UpdateColor`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

### `UpdateName`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

### `UpdateRotation`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

### `UpdateScale`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`
  - `Plate` — `StaticMeshComponent` @ socket `None`
    - `Pointer` — `StaticMeshComponent` @ socket `None`
  - `Trigger` — `CapsuleComponent` @ socket `None`
  - `DestinationName` — `TextRenderComponent` @ socket `None`

## Class Default Object (1)

- `SpriteScale` (`float`) = `0.000000`

## Graphs

- Event graph: `EventGraph` (6 nodes)
- Construction script: `UserConstructionScript` (5 nodes)
- Additional graphs: _none_

## References

Hard refs out (6):
- `/Engine/BasicShapes/Cube` [asset]
- `/Engine/BasicShapes/Cylinder` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Materials/MI_Solid_Blue` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Teleporter_Destination` [asset]
- `/Script/Engine.Actor` [native]
- `/Script/NavigationSystem` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

