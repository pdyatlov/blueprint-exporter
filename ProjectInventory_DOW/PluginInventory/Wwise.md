# Wwise

## Identity

| Field | Value |
|---|---|
| Plugin name | `Wwise` |
| Friendly name | Wwise Unreal Engine Integration |
| Plugin type | `Project` |
| Base dir | `Plugins/Wwise` |
| Enabled | yes |
| Version | `202514199` (`2025.1.5.9095.4199`) |
| Category | `Audio` |
| Can contain content | yes |
| Engine version (export) | `5.7.4-573521+++UE_DOW+main` |
| Plugin version (tool) | `1.28.6` |

## Description

Wwise integration for Unreal Engine

## Authorship & Links

- Created by: `Audiokinetic, Inc.`
- Author URL: `http://audiokinetic.com`

## Modules (21)

| Name | Host type | Loading phase |
|---|---|---|
| `AkAudio` | `Runtime` | `None` |
| `AudiokineticTools` | `Editor` | `Default` |
| `Wwise` | `Runtime` | `PreLoadingScreen` |
| `WwiseAudioLinkEditor` | `Editor` | `None` |
| `WwiseAudioLinkRuntime` | `Runtime` | `None` |
| `WwiseConcurrency` | `Runtime` | `None` |
| `WwiseEditorUtils` | `Editor` | `None` |
| `WwiseEngineUtils` | `Runtime` | `None` |
| `WwiseFileHandler` | `Runtime` | `None` |
| `WwiseObjectUtils` | `Runtime` | `None` |
| `WwiseObstructionOcclusion` | `Runtime` | `None` |
| `WwisePackaging` | `Runtime` | `None` |
| `WwisePackagingEditor` | `Editor` | `None` |
| `WwisePackagingRuntime` | `Runtime` | `None` |
| `WwiseProcessing` | `Runtime` | `None` |
| `WwiseProjectDatabase` | `UncookedOnly` | `None` |
| `WwiseReconcile` | `Editor` | `Default` |
| `WwiseResourceCooker` | `UncookedOnly` | `None` |
| `WwiseResourceLoader` | `Runtime` | `None` |
| `WwiseSimpleExternalSource` | `Runtime` | `None` |
| `WwiseUtils` | `Runtime` | `None` |

## Plugin dependencies (2)

| Plugin | Enabled | Optional |
|---|---|---|
| `GeometryMode` | yes | no |
| `WwiseSoundEngine` | yes | no |

## Registered native types (1)

| Class | Parent | Module | Subsystem | Props |
|---|---|---|---|---:|
| `/Script/AkAudio.AkEventAnimNotify` | `/Script/Engine.AnimNotify` | `AkAudio` | `Anim` | 3 |

### `/Script/AkAudio.AkEventAnimNotify` — `AkAudio` [Anim]

- Parent: `/Script/Engine.AnimNotify`
- Declared properties: 3

| Name | Type | Default | Category |
|---|---|---|---|
| `AttachName` | `FString` | — | `Default` |
| `Event` | `TObjectPtr<UAkAudioEvent>` | `None` | `Default` |
| `Follow` | `bool` | `True` | `Default` |

