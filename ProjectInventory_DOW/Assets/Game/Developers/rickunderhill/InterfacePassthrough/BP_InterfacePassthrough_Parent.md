# BP_InterfacePassthrough_Parent

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Developers/rickunderhill/InterfacePassthrough/BP_InterfacePassthrough_Parent.BP_InterfacePassthrough_Parent` |
| Asset name | `BP_InterfacePassthrough_Parent` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces (1):
  - `/Game/Developers/rickunderhill/InterfacePassthrough/BPI_PassthroughDebug.BPI_PassthroughDebug_C`

## Variables (1)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Target` | `TMap<object<SInterfacePassthrough>>, struct:/Game/Developers/rickunderhill/InterfacePassthrough/SInterfacePassthrough.SInterfacePassthrough>` | `()` | `Default` | — | — | InstanceEditable |

## Functions (1)

### `ADelayedActivation`

- Interface override of `/Game/Developers/rickunderhill/InterfacePassthrough/BPI_PassthroughDebug.BPI_PassthroughDebug_C`
- Access: `Public`
- Flags: —
- Inputs: `(struct<SInterfacePassthrough> Info)`
- Outputs: `(real<double> DelayOut)`
- Local variables: _none_
- Nodes: 13

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`
  - `Cube` — `StaticMeshComponent` @ socket `None`
  - `TextRender` — `TextRenderComponent` @ socket `None`
  - `Box` — `BoxComponent` @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (25 nodes)
- Construction script: `UserConstructionScript` (1 nodes)
- Additional graphs: _none_

## References

Hard refs out (9):
- `/Engine/BasicShapes/BasicShapeMaterial` [asset]
- `/Engine/BasicShapes/Cube` [asset]
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Engine/EditorMeshes/EditorSphere` [asset]
- `/Game/Developers/rickunderhill/InterfacePassthrough/BPI_PassthroughDebug` [asset]
- `/Game/Developers/rickunderhill/InterfacePassthrough/EInterfacePassthrough` [asset]
- `/Game/Developers/rickunderhill/InterfacePassthrough/SInterfacePassthrough` [asset]
- `/Script/Engine.Actor` [native]
- `/Script/NavigationSystem` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

