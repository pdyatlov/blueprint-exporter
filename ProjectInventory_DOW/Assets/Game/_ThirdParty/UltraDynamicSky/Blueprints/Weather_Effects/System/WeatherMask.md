# WeatherMask

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/WeatherMask.WeatherMask` |
| Asset name | `WeatherMask` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `StaticMeshComponent` (`/Script/Engine.StaticMeshComponent`, native, module `/Script/Engine`)
- Interfaces (1):
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/WeatherMaskComponentInterface.WeatherMaskComponentInterface_C`

## Variables (19)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `UDW` | `object<Ultra_Dynamic_Weather_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Mask Snow/Dust` | `real<double>` | `1.000000` | `Settings` | — | — | InstanceEditable |
| `Mask Wetness` | `real<double>` | `1.000000` | `Settings` | — | — | InstanceEditable |
| `Brush Location` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Weather Mask` | — | — | InstanceEditable, Private |
| `Brush Scale` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Weather Mask` | — | — | InstanceEditable, Private |
| `Brush Yaw` | `real<double>` | `0.000000` | `Weather Mask` | — | — | InstanceEditable, Private |
| `Center Location` | `struct<Vector2D>` | `(X=0.000000,Y=0.000000)` | `Weather Mask` | — | — | InstanceEditable, Private |
| `Max Distance` | `real<double>` | `0.000000` | `Weather Mask` | — | — | InstanceEditable, Private |
| `Ready for Drawing` | `bool` | `False` | `Weather Mask` | — | — | InstanceEditable, Private |
| `Spawned At Runtime` | `bool` | `False` | `Weather Mask` | — | — | InstanceEditable, Private |
| `Fade Timer` | `real<double>` | `0.000000` | `Fade` | — | — | InstanceEditable, Private |
| `Fade Duration` | `real<double>` | `0.000000` | `Fade` | — | — | InstanceEditable, Private |
| `Target Mask Snow/Dust` | `real<double>` | `0.000000` | `Fade` | — | — | InstanceEditable, Private |
| `Target Mask Wetness` | `real<double>` | `0.000000` | `Fade` | — | — | InstanceEditable, Private |
| `Last Mask Snow/Dust` | `real<double>` | `0.000000` | `Fade` | — | — | InstanceEditable, Private |
| `Last Mask Wetness` | `real<double>` | `0.000000` | `Fade` | — | — | InstanceEditable, Private |
| `Fade Ticking` | `bool` | `False` | `Fade` | — | — | InstanceEditable, Private |
| `Fade Tick Period` | `real<double>` | `0.030000` | `Fade` | — | — | InstanceEditable, Private |
| `Tick Fade Timer` | `struct<TimerHandle>` | `()` | `Fade` | — | — | InstanceEditable, Private |

## Functions (18)

### `Calculate Masking At Location`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Location = 0, 0, 0)`
- Outputs: `(struct<Vector2D> Mask, bool Cancel All Masks)`
- Local variables: _none_
- Nodes: 2

### `Component Generally In Range`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(bool ReturnValue)`
- Local variables: _none_
- Nodes: 10

### `Configure Collision`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

### `Disable`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

### `Draw to Height Canvas`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/WeatherMaskComponentInterface.WeatherMaskComponentInterface_C`
- Access: `Public`
- Flags: —
- Inputs: `(object<Canvas> Height Canvas, object<UDS_RenderTarget_State_C> Target State, object<MaterialInstanceDynamic> Draw MID)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2

### `Draw to Mask Canvas`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/WeatherMaskComponentInterface.WeatherMaskComponentInterface_C`
- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_RenderTarget_State_C> Target State, object<Canvas> Mask Canvas, object<Ultra_Dynamic_Weather_C> UDW)`
- Outputs: `(bool Success)`
- Local variables: _none_
- Nodes: 2

### `Editor Update`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 16

### `Enable`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

### `Fade Mask Over Time`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Fade Duration = 5.000000, real<double> New Mask Snow/Dust, real<double> New Mask Wetness)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 18
- Description: Call to start the weather mask to fade to new mask values over time, updating the UDW weather mask target as it does.

### `Force Update`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

### `Get Brush Location`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector2D> Out)`
- Local variables: _none_
- Nodes: 6

### `Get Brush Scale`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector2D> Out)`
- Local variables: _none_
- Nodes: 5

### `Get Brush Yaw`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 4

### `Get Center Location`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<Vector2D> Out)`
- Local variables: _none_
- Nodes: 4

### `Get Max Distance`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 6

### `Prepare for Drawing`

- Access: `Public`
- Flags: —
- Inputs: `(object<Ultra_Dynamic_Weather_C> UDW)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11

### `Tick Fade`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Alpha`
- Nodes: 29

### `Update Mask Values`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (19)

- `bAffectDistanceFieldLighting` (`uint8`) = `False`
- `bApplyImpulseOnDamage` (`uint8`) = `False`
- `bCanEverAffectNavigation` (`uint8`) = `False`
- `bEnableAutoLODGeneration` (`uint8`) = `False`
- `bGenerateOverlapEvents` (`uint8`) = `False`
- `bHiddenInGame` (`uint8`) = `True`
- `BodyInstance` (`FBodyInstance`) = `(ObjectType=ECC_PhysicsBody,CollisionEnabled=QueryOnly,CollisionProfileName="Custom",CollisionResponses=(ResponseArra...`
- `bReceivesDecals` (`uint8`) = `False`
- `bRenderInDepthPass` (`uint8`) = `False`
- `bReplicatePhysicsToAutonomousProxy` (`uint8`) = `False`
- `bUseAsOccluder` (`uint8`) = `False`
- `bVisibleInRayTracing` (`uint8`) = `False`
- `bVisibleInRealTimeSkyCaptures` (`uint8`) = `False`
- `bVisibleInReflectionCaptures` (`uint8`) = `False`
- `CastShadow` (`uint8`) = `False`
- `CustomPrimitiveData` (`FCustomPrimitiveData`) = `(Data=(0.817708,0.270698,0.039227,0.000000))`
- `LightingChannels` (`FLightingChannels`) = `(bChannel0=False)`
- `PrimaryComponentTick` (`FActorComponentTickFunction`) = `(bStartWithTickEnabled=False,bAllowTickOnDedicatedServer=False,TickInterval=0.030000)`
- `StaticMesh` (`TObjectPtr<UStaticMesh>`) = `/Script/Engine.StaticMesh'/Game/_ThirdParty/UltraDynamicSky/Meshes/Brush_Cube.Brush_Cube'`

## Graphs

- Event graph: `EventGraph` (34 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (8):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_RunContext` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Functions/UltraDynamicWeather_Functions` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_RenderTarget_State` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/WeatherMaskComponentInterface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/Brush_Cube` [asset]
- `/Script/Engine.StaticMeshComponent` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

