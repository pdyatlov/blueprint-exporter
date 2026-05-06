# UDS_Actor_Reference_Manager

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Actor_Reference_Manager.UDS_Actor_Reference_Manager` |
| Asset name | `UDS_Actor_Reference_Manager` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ActorComponent` (`/Script/Engine.ActorComponent`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (4)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `UDS` | `object<Ultra_Dynamic_Sky_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Dispatch Tunnel` | `object<UDS_DispatcherTunnel_C>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_DispatcherTunnel.UDS_DispatcherTunnel_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_DispatcherTunnelObject.UDS_DispatcherTunnelObject'` | `Default` | — | — | InstanceEditable, Private |
| `Got New UDS Reference` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `UDS Reference Ended Play` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |

## Functions (2)

### `UDS End Play`

- Access: `Public`
- Flags: —
- Inputs: `(object<Actor> Actor, byte EndPlayReason = Destroyed)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `UDS Starting Up`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `PrimaryComponentTick` (`FActorComponentTickFunction`) = `(bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (15 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (5):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_DispatcherTunnel` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_DispatcherTunnelObject` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` [asset]
- `/Script/Engine.ActorComponent` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

