# Teleporter_Destination

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Teleporter_Destination.Teleporter_Destination` |
| Asset name | `Teleporter_Destination` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (3)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `DestinationName` | `text` | `NSLOCTEXT("[2B678387CEC31C4050FEC35E260C41E5]", "DC18D31148ECABA2EFCE4A877434FE36", "Destination")` | `Default` | — | — | InstanceEditable |
| `Color` | `struct<LinearColor>` | `(R=0.002428,G=0.138432,B=0.577581,A=1.000000)` | `Default` | — | — | InstanceEditable |
| `PlateScale` | `real<double>` | `1.000000` | `Default` | — | — | InstanceEditable |

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
- Nodes: 4

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
  - `Plate` — `StaticMeshComponent` @ socket `None`
  - `Name` — `TextRenderComponent` @ socket `None`
  - `TeleportPoint` — `SceneComponent` @ socket `None`

## Class Default Object (1)

- `SpriteScale` (`float`) = `0.000000`

## Graphs

- Event graph: `EventGraph` (3 nodes)
- Construction script: `UserConstructionScript` (5 nodes)
- Additional graphs: _none_

## References

Hard refs out (5):
- `/Engine/BasicShapes/Cylinder` [asset]
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Materials/MI_Solid_Blue` [asset]
- `/Game/_ThirdParty/GASP_example/Levels/LevelPrototyping/Teleporter_Sender` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

