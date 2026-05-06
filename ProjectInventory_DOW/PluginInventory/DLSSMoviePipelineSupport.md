# DLSSMoviePipelineSupport

## Identity

| Field | Value |
|---|---|
| Plugin name | `DLSSMoviePipelineSupport` |
| Friendly name | Movie Render Queue DLSS/DLAA Support |
| Plugin type | `Project` |
| Base dir | `Plugins/Marketplace/DLSSMoviePipelineSupport` |
| Enabled | yes |
| Version | `32` (`8.5.0`) |
| Category | `Rendering` |
| Can contain content | yes |
| Installed | yes |
| Engine version (export) | `5.7.4-573521+++UE_DOW+main` |
| Plugin version (tool) | `1.28.6` |

## Description

Plugin that adds DLSS/DLAA support to Movie Render Queue.

## Authorship & Links

- Created by: `NVIDIA`
- Author URL: `https://developer.nvidia.com/dlss`
- Support: `mailto:DLSS-Support@nvidia.com`

## Modules (1)

| Name | Host type | Loading phase |
|---|---|---|
| `DLSSMoviePipelineSupport` | `Runtime` | `PostEngineInit` |

## Plugin dependencies (2)

| Plugin | Enabled | Optional |
|---|---|---|
| `DLSS` | yes | no |
| `MovieRenderPipeline` | yes | no |

## Registered native types (0)

_None — this plugin's modules register no UClass subclasses of any allowlist base (EQS / StateTree / BT / Anim / GAS / SmartObject / Chooser / Mass)._

