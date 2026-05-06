# CoverEQS

## Identity

| Field | Value |
|---|---|
| Plugin name | `CoverEQS` |
| Friendly name | Cover EQS - Trace Distance Test |
| Plugin type | `Project` |
| Base dir | `Plugins/CoverEQS` |
| Enabled | yes |
| Version | `1` (`1.0.0`) |
| Category | `AI` |
| Can contain content | no |
| Engine version (export) | `5.7.4-573521+++UE_DOW+main` |
| Plugin version (tool) | `1.28.6` |

## Description

Custom EQS test that scores items by distance to first blocking hit along a trace. Fills the gap between the engine's boolean Trace test and continuous cover quality scoring.

## Modules (1)

| Name | Host type | Loading phase |
|---|---|---|
| `CoverEQS` | `Runtime` | `Default` |

## Plugin dependencies (0)

_None._

## Registered native types (1)

| Class | Parent | Module | Subsystem | Props |
|---|---|---|---|---:|
| `/Script/CoverEQS.EnvQueryTest_TraceDistance` | `/Script/AIModule.EnvQueryTest` | `CoverEQS` | `EQS` | 9 |

### `/Script/CoverEQS.EnvQueryTest_TraceDistance` — `CoverEQS` [EQS]

- Parent: `/Script/AIModule.EnvQueryTest`
- Declared properties: 9

| Name | Type | Default | Category |
|---|---|---|---|
| `bScoreMissAsMaxDistance` | `bool` | `False` | `Trace` |
| `bTraceFromContext` | `FAIDataProviderBoolValue` | `()` | `Trace` |
| `ContextHeightOffset` | `FAIDataProviderFloatValue` | `()` | `Trace` |
| `IgnoreActorsContext` | `TSubclassOf<UEnvQueryContext>` | `/Script/CoreUObject.Class'/Script/AIModule.EnvQueryContext_Querier'` | `Trace` |
| `ItemHeightOffset` | `FAIDataProviderFloatValue` | `()` | `Trace` |
| `MaxTraceDistance` | `FAIDataProviderFloatValue` | `(DefaultValue=3000.000000)` | `Trace` |
| `ScoreMode` | `ECoverEQSTraceDistanceScoreMode` | `InvertedDistanceToHit` | `Trace` |
| `TraceData` | `FEnvTraceData` | `(ProjectDown=1024.000000,ProjectUp=1024.000000,ExtentX=10.000000,ExtentY=10.000000,ExtentZ=10.000000,TraceMode=GeometryByChannel,bOnlyBlockingHits=True,bCanTraceOnGeometry=True)` | `Trace` |
| `TraceTo` | `TSubclassOf<UEnvQueryContext>` | `/Script/CoreUObject.Class'/Script/AIModule.EnvQueryContext_Querier'` | `Trace` |

