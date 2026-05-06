# Teleporter_Level

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Teleporter_Level.Teleporter_Level` |
| Asset name | `Teleporter_Level` |
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
| `Destination` | `text` | `NSLOCTEXT("", "91109E8C47779D2E420C578DD717C8F2", "None")` | `Default` | — | — | InstanceEditable |

## Functions (1)

### `UpdateName`

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
  - `DestinationName` — `TextRenderComponent` @ socket `None`
  - `Pointer` — `StaticMeshComponent` @ socket `None`
  - `Trigger` — `BoxComponent` @ socket `None`

## Class Default Object (1)

- `SpriteScale` (`float`) = `0.000000`

## Graphs

- Event graph: `EventGraph` (9 nodes)
- Construction script: `UserConstructionScript` (2 nodes)
- Additional graphs: _none_

## References

Hard refs out (4):
- `/ControlRig/Controls/ControlRig_Arrow_solid` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Materials/MI_Solid_Blue` [asset]
- `/Script/Engine.Actor` [native]
- `/Script/NavigationSystem` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

