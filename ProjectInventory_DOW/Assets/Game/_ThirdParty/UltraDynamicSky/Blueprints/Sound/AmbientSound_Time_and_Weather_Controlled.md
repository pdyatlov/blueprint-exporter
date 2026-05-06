# AmbientSound_Time_and_Weather_Controlled

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Sound/AmbientSound_Time_and_Weather_Controlled.AmbientSound_Time_and_Weather_Controlled` |
| Asset name | `AmbientSound_Time_and_Weather_Controlled` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `AmbientSound` (`/Script/Engine.AmbientSound`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (17)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `UDS` | `object<Ultra_Dynamic_Sky_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `UDW` | `object<Ultra_Dynamic_Weather_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Daytime Volume Multiplier` | `real<double>` | `1.000000` | `Sound` | — | — | InstanceEditable |
| `Day` | `bool` | `False` | `System` | — | — | InstanceEditable |
| `Nighttime Volume Multiplier` | `real<double>` | `1.000000` | `Sound` | — | — | InstanceEditable |
| `Snowy Volume Multiplier` | `real<double>` | `1.000000` | `Sound` | — | — | InstanceEditable |
| `Rainy Volume Multiplier` | `real<double>` | `1.000000` | `Sound` | — | — | InstanceEditable |
| `Dusty Volume Multiplier` | `real<double>` | `1.000000` | `Sound` | — | — | InstanceEditable |
| `No Weather Volume Multiplier` | `real<double>` | `1.000000` | `Sound` | — | — | InstanceEditable |
| `Volume Multiplier Transition Time` | `real<double>` | `30.000000` | `Sound` | — | — | InstanceEditable |
| `Snowing` | `bool` | `False` | `System` | — | — | InstanceEditable |
| `Raining` | `bool` | `False` | `System` | — | — | InstanceEditable |
| `Runtime` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Target Volume Multiplier` | `real<double>` | `0.000000` | `System` | — | — | InstanceEditable |
| `Dusty` | `bool` | `False` | `System` | — | — | InstanceEditable |
| `UDS Dispatch Tunnel` | `object<UDS_DispatcherTunnel_C>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_DispatcherTunnel.UDS_DispatcherTunnel_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_DispatcherTunnelObject.UDS_DispatcherTunnelObject'` | `Default` | — | — | InstanceEditable, Private |
| `UDW Dispatch Tunnel` | `object<UDW_Dispatcher_Tunnel_C>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Dispatcher_Tunnel.UDW_Dispatcher_Tunnel_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_DispatcherTunnelAsset.UDW_DispatcherTunnelAsset'` | `Default` | — | — | InstanceEditable, Private |

## Functions (16)

### `Bind to Dispatchers`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 36

### `Finished Dust`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `Finished Raining`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `Finished Snowing`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `Get Starting Dispatchers State`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 26

### `Get UDS and UDW Reference`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

### `Instant Update`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

### `Start Up Sound`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 17
- Category: `Default`

### `Started Dust`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `Started Raining`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `Started Snowing`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `Sunrise`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `Sunset`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `UDW End Play`

- Access: `Protected`
- Flags: —
- Inputs: `(object<Actor> Actor, byte EndPlayReason = Destroyed)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `Update Volume Multiplier`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 34

### `📘 Ambient Sounds Controlled by Time and Weather`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Sound`

## Macros (0)

_None._

## Components (1)

- `UDS_Utility_Opener` — `UDS_Utility_Opener_C` @ socket `None`

## Class Default Object (4)

- `ActorLabel` (`FString`) = `Time_and_Weather_Specific_AmbientSound-1`
- `AudioComponent` (`TObjectPtr<UAudioComponent>`) [instanced] = `/Script/Engine.AudioComponent'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Sound/AmbientSound_Time_and_Weather_Contro...`
- `PrimaryActorTick` (`FActorTickFunction`) = `(bCanEverTick=True,bStartWithTickEnabled=False)`
- `RootComponent` (`TObjectPtr<USceneComponent>`) [instanced] = `/Script/Engine.AudioComponent'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Sound/AmbientSound_Time_and_Weather_Contro...`

## Graphs

- Event graph: `EventGraph` (25 nodes)
- Construction script: `UserConstructionScript` (5 nodes)
- Additional graphs: _none_

## References

Hard refs out (12):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Engine/EditorResources/AudioIcons/S_AudioComponent` [asset]
- `/Engine/EditorResources/AudioIcons/S_AudioComponent_AutoActivate` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_DispatcherTunnel` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_DispatcherTunnelObject` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Sky` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Dispatcher_Tunnel` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_DispatcherTunnelAsset` [asset]
- `/Script/Engine.AmbientSound` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

