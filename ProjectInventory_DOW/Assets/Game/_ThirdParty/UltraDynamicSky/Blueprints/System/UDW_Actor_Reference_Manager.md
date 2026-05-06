# UDW_Actor_Reference_Manager

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDW_Actor_Reference_Manager.UDW_Actor_Reference_Manager` |
| Asset name | `UDW_Actor_Reference_Manager` |
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
| `UDW` | `object<Ultra_Dynamic_Weather_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Dispatch Tunnel` | `object<UDW_Dispatcher_Tunnel_C>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Dispatcher_Tunnel.UDW_Dispatcher_Tunnel_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_DispatcherTunnelAsset.UDW_DispatcherTunnelAsset'` | `Default` | — | — | InstanceEditable, Private |
| `Got New UDW Reference` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |
| `UDW Reference Ended Play` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |

## Functions (2)

### `UDW End Play`

- Access: `Public`
- Flags: —
- Inputs: `(object<Actor> Actor, byte EndPlayReason = Destroyed)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `UDW Starting Up`

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
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Dispatcher_Tunnel` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_DispatcherTunnelAsset` [asset]
- `/Script/Engine.ActorComponent` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

