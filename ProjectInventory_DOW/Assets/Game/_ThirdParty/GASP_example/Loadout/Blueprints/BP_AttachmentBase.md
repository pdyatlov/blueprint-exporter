# BP_AttachmentBase

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Loadout/Blueprints/BP_AttachmentBase.BP_AttachmentBase` |
| Asset name | `BP_AttachmentBase` |
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
| `AttachmentDefinition` | `object<DA_AttachmentDefinition_C>` | `None` | `Components` | — | — | InstanceEditable |

## Functions (1)

### `InitializeAttachmentFromAttachmentDefinition`

- Access: `Public`
- Flags: —
- Inputs: `(object<DA_AttachmentDefinition_C> IncomingDefinition)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`
  - `SkeletalMesh` — `SkeletalMeshComponent` @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `UserConstructionScript` (1 nodes)
- Additional graphs: _none_

## References

Hard refs out (2):
- `/Game/_ThirdParty/GASP_example/Loadout/Blueprints/DataAssets/DA_AttachmentDefinition` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

