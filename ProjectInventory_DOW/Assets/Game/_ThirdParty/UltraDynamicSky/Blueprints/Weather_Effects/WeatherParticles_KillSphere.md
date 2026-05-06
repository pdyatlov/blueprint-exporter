# WeatherParticles_KillSphere

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/WeatherParticles_KillSphere.WeatherParticles_KillSphere` |
| Asset name | `WeatherParticles_KillSphere` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `StaticMeshComponent` (`/Script/Engine.StaticMeshComponent`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (1)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Tick Timer` | `struct<TimerHandle>` | `()` | `Default` | — | — | InstanceEditable, Private |

## Functions (1)

### `Update Parameter`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (14)

- `bAffectDistanceFieldLighting` (`uint8`) = `False`
- `bAffectDynamicIndirectLighting` (`uint8`) = `False`
- `bAutoActivate` (`uint8`) = `True`
- `bCanEverAffectNavigation` (`uint8`) = `False`
- `bEnableAutoLODGeneration` (`uint8`) = `False`
- `bGenerateOverlapEvents` (`uint8`) = `False`
- `bHiddenInGame` (`uint8`) = `True`
- `BodyInstance` (`FBodyInstance`) = `(ObjectType=ECC_PhysicsBody,CollisionProfileName="Custom")`
- `bUseDefaultCollision` (`uint8`) = `True`
- `CastShadow` (`uint8`) = `False`
- `CustomPrimitiveData` (`FCustomPrimitiveData`) = `(Data=(1.000000,0.000000,0.000000,1.000000))`
- `LightingChannels` (`FLightingChannels`) = `(bChannel0=False)`
- `PrimaryComponentTick` (`FActorComponentTickFunction`) = `(bStartWithTickEnabled=False,bAllowTickOnDedicatedServer=False)`
- `StaticMesh` (`TObjectPtr<UStaticMesh>`) = `/Script/Engine.StaticMesh'/Game/_ThirdParty/UltraDynamicSky/Meshes/Brush_Sphere.Brush_Sphere'`

## Graphs

- Event graph: `EventGraph` (17 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (3):
- `/Game/_ThirdParty/UltraDynamicSky/Materials/Weather/UltraDynamicWeather_Parameters` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/Brush_Sphere` [asset]
- `/Script/Engine.StaticMeshComponent` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

