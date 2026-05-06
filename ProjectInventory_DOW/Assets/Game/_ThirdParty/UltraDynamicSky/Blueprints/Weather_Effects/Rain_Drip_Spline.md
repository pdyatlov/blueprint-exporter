# Rain_Drip_Spline

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Rain_Drip_Spline.Rain_Drip_Spline` |
| Asset name | `Rain_Drip_Spline` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (29)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Render Rain Drips` | `bool` | `True` | `Settings\|Rain Drips` | — | — | InstanceEditable |
| `Spawn Rate Per Meter` | `real<double>` | `250.000000` | `Settings\|Rain Drips` | — | — | InstanceEditable |
| `Extra Spawn Rate` | `real<double>` | `0.000000` | `Settings\|Rain Drips` | — | — | InstanceEditable |
| `Drip with Material Wetness` | `real<double>` | `0.010000` | `Settings\|Rain Drips` | — | — | InstanceEditable |
| `Drip Sprite Scale` | `real<double>` | `1.500000` | `Settings\|Rain Drips` | — | — | InstanceEditable |
| `Splash Particle Scale` | `real<double>` | `1.000000` | `Settings\|Rain Drips` | — | — | InstanceEditable |
| `Splash Frequency` | `real<double>` | `1.000000` | `Settings\|Rain Drips` | — | — | InstanceEditable |
| `Collision Line Trace Head Start` | `real<double>` | `25.000000` | `Settings\|Rain Drips` | — | — | InstanceEditable |
| `Curl Noise Force` | `real<double>` | `1.000000` | `Settings\|Rain Drips` | — | — | InstanceEditable, ReadOnly |
| `Closed Spline Loop` | `bool` | `False` | `Settings` | — | — | InstanceEditable |
| `Ignore Weather State` | `bool` | `False` | `Settings` | — | — | InstanceEditable |
| `Point Conversion Spacing` | `real<double>` | `10.000000` | `Settings\|Rain Drips` | — | — | InstanceEditable |
| `Drip_System` | `object<NiagaraComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Render Icicles` | `bool` | `False` | `Settings\|Icicles` | — | — | InstanceEditable |
| `Icicle Spacing` | `real<double>` | `0.750000` | `Settings\|Icicles` | — | — | InstanceEditable |
| `Icicle Location Jitter` | `real<double>` | `0.000000` | `Settings\|Icicles` | — | — | InstanceEditable |
| `Icicle Min Scale` | `real<double>` | `0.200000` | `Settings\|Icicles` | — | — | InstanceEditable |
| `Icicle Max Scale` | `real<double>` | `0.600000` | `Settings\|Icicles` | — | — | InstanceEditable |
| `Icicle Perlin Noise Variation` | `real<double>` | `0.550000` | `Settings\|Icicles` | — | — | InstanceEditable |
| `Icicle Thickness` | `real<double>` | `1.000000` | `Settings\|Icicles` | — | — | InstanceEditable |
| `Icicle Seed` | `int` | `-1` | `Settings\|Icicles` | — | — | InstanceEditable |
| `Icicle Color` | `struct<LinearColor>` | `(R=1.000000,G=1.000000,B=1.000000,A=1.000000)` | `Settings\|Icicles` | — | — | InstanceEditable |
| `Icicle Mesh Deform` | `real<double>` | `2.000000` | `Settings\|Icicles` | — | — | InstanceEditable |
| `Icicle Static Mesh` | `object<StaticMesh>` | `/Script/Engine.StaticMesh'/Game/_ThirdParty/UltraDynamicSky/Meshes/Icicle.Icicle'` | `Settings\|Icicles` | — | — | InstanceEditable |
| `Icicles Render Opaque` | `bool` | `False` | `Settings\|Icicles` | — | — | InstanceEditable |
| `Icicles Cast Shadows` | `bool` | `False` | `Settings\|Icicles` | — | — | InstanceEditable |
| `Icicle Cull Distance` | `real<double>` | `7000.000000` | `Settings\|Icicles` | — | — | InstanceEditable |
| `Rain Drips Cull Distance` | `real<double>` | `3000.000000` | `Settings\|Rain Drips` | — | — | InstanceEditable |
| `UDW Dispatch Tunnel` | `object<UDW_Dispatcher_Tunnel_C>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Dispatcher_Tunnel.UDW_Dispatcher_Tunnel_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_DispatcherTunnelAsset.UDW_DispatcherTunnelAsset'` | `Default` | — | — | InstanceEditable, Private |

## Functions (7)

### `Apply Icicle Primitive Data`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15
- Category: `System`

### `Create Curve Data`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (11): `Number of Segments`, `Current Emitter`, `Segment Index`, `Segment Bounds Min`, `Segment Bounds Max`, `Spline Length`, `Current Spline Distance`, `Spline Points`, `Bounds Min`, `Bounds Max`, `Current Spline Point`
- Nodes: 77
- Category: `System`

### `Create Icicle Meshes`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (5): `Spline Length`, `Current Spline Distance`, `Stream`, `Noise Offset`, `Noise Sample`
- Nodes: 98
- Category: `System`

### `Spawn Rate`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 9
- Category: `System`

### `UDS and UDW Dependent Updates`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10
- Category: `System`

### `Update Static Niagara Parameters`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13
- Category: `System`

### `📘 Rain Drip Spline`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Settings`

## Macros (0)

_None._

## Components (2)

- `Root` — `BillboardComponent` @ socket `None`
  - `Spline` — `SplineComponent` @ socket `None`
  - `Dripping Curve` — `NiagaraComponent` @ socket `None`
  - `InstancedStaticMesh` — `InstancedStaticMeshComponent` @ socket `None`
- `UDS_Utility_Opener` — `UDS_Utility_Opener_C` @ socket `None`

## Class Default Object (3)

- `ActorLabel` (`FString`) = `Dripping_Rain_Line-1`
- `bEnableAutoLODGeneration` (`uint8`) = `False`
- `PrimaryActorTick` (`FActorTickFunction`) = `(bStartWithTickEnabled=False,bAllowTickOnDedicatedServer=False,TickInterval=3.000000)`

## Graphs

- Event graph: `EventGraph` (17 nodes)
- Construction script: `UserConstructionScript` (11 nodes)
- Additional graphs: _none_

## References

Hard refs out (15):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_Dispatcher_Tunnel` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_DispatcherTunnelAsset` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Icicle_Ice_Mat` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Icicle_Ice_Mat_Opaque` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Splash_ParticleMat` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/Splash_ParticleMat_Translucent` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/UltraDynamicWeather_Parameters` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/Icicle` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Particles/Dripping_Curve` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Rain_Drip_Spline` [asset]
- `/Script/Engine.Actor` [native]
- `/Script/Niagara` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

