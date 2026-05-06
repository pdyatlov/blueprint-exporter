# UDS_Occlusion_Portal

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Occlusion/UDS_Occlusion_Portal.UDS_Occlusion_Portal` |
| Asset name | `UDS_Occlusion_Portal` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `StaticMeshComponent` (`/Script/Engine.StaticMeshComponent`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (4)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Sample Range` | `real<double>` | `2000.000000` | `Settings` | — | — | InstanceEditable |
| `Distance Falloff Exponent` | `real<double>` | `2.000000` | `Settings` | — | — | InstanceEditable |
| `Directional Occlusion` | `real<double>` | `0.550000` | `Settings` | — | — | InstanceEditable |
| `Global Occlusion` | `real<double>` | `0.000000` | `Settings` | — | — | InstanceEditable |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (18)

- `bAutoActivate` (`uint8`) = `True`
- `bBoundsChangeTriggersStreamingDataRebuild` (`uint8`) = `False`
- `bCanEverAffectNavigation` (`uint8`) = `False`
- `bEnableAutoLODGeneration` (`uint8`) = `False`
- `bGenerateOverlapEvents` (`uint8`) = `False`
- `bHiddenInGame` (`uint8`) = `True`
- `BodyInstance` (`FBodyInstance`) = `(ObjectType=ECC_PhysicsBody,CollisionProfileName="Custom")`
- `bReceivesDecals` (`uint8`) = `False`
- `bRenderInDepthPass` (`uint8`) = `False`
- `bUseAsOccluder` (`uint8`) = `False`
- `bUseDefaultCollision` (`uint8`) = `True`
- `bVisibleInRayTracing` (`uint8`) = `False`
- `bVisibleInRealTimeSkyCaptures` (`uint8`) = `False`
- `bVisibleInReflectionCaptures` (`uint8`) = `False`
- `CastShadow` (`uint8`) = `False`
- `OverrideMaterials` (`TArray`) = `("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'")`
- `PrimaryComponentTick` (`FActorComponentTickFunction`) = `(bStartWithTickEnabled=False,bAllowTickOnDedicatedServer=False)`
- `StaticMesh` (`TObjectPtr<UStaticMesh>`) = `/Script/Engine.StaticMesh'/Game/_ThirdParty/UltraDynamicSky/Meshes/Portal_Arrow.Portal_Arrow'`

## Graphs

- Event graph: `EventGraph` (7 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (3):
- `/Engine/BasicShapes/BasicShapeMaterial` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Meshes/Portal_Arrow` [asset]
- `/Script/Engine.StaticMeshComponent` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

