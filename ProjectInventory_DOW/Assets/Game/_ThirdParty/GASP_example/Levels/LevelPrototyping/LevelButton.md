# LevelButton

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/LevelButton.LevelButton` |
| Asset name | `LevelButton` |
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
| `ButtonName` | `text` | `NSLOCTEXT("[0902C6E36FB3F28C313C93F225124388]", "F28886BF47D38093238C94B08C99F310", "Button")` | `Default` | — | — | InstanceEditable |
| `ExecuteConsoleCommand` | `bool` | `True` | `Default` | — | — | InstanceEditable |
| `ConsoleCommand` | `string` | — | `Default` | — | — | InstanceEditable |
| `Color` | `struct<LinearColor>` | `(R=0.002428,G=0.138432,B=0.577581,A=1.000000)` | `Default` | — | — | InstanceEditable |
| `TextColor` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `Default` | — | — | InstanceEditable |
| `PlateScale` | `real<double>` | `1.000000` | `Default` | — | — | InstanceEditable |
| `ButtonPressed` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |

## Functions (4)

### `UpdateColor`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

### `UpdateName`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

### `UpdateScale`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Default`

### `UpdateSenders`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`
  - `Name` — `TextRenderComponent` @ socket `None`
  - `Trigger` — `BoxComponent` @ socket `None`
  - `Plate` — `StaticMeshComponent` @ socket `None`

## Class Default Object (1)

- `SpriteScale` (`float`) = `0.000000`

## Graphs

- Event graph: `EventGraph` (10 nodes)
- Construction script: `UserConstructionScript` (4 nodes)
- Additional graphs: _none_

## References

Hard refs out (7):
- `/Engine/BasicShapes/Cube` [asset]
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Materials/MI_Solid_Blue` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Teleporter_Destination` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Teleporter_Sender` [asset]
- `/Script/Engine.Actor` [native]
- `/Script/NavigationSystem` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

