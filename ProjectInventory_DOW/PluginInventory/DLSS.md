# DLSS

## Identity

| Field | Value |
|---|---|
| Plugin name | `DLSS` |
| Friendly name | NVIDIA DLSS Super Resolution/Ray Reconstruction/DLAA |
| Plugin type | `Project` |
| Base dir | `Plugins/Marketplace/DLSS` |
| Enabled | yes |
| Version | `57` (`8.5.0-NGX310.5.0`) |
| Category | `Rendering` |
| Can contain content | yes |
| Installed | yes |
| Engine version (export) | `5.7.4-573521+++UE_DOW+main` |
| Plugin version (tool) | `1.28.6` |

## Description

DLSS Super Resolution boosts frame rates by rendering fewer pixels and using AI to output high resolution frames. DLSS Ray Reconstruction enhances image quality by generating high-quality pixels between sampled rays for intensive ray traced content. DLAA is an AI-based anti-aliasing mode to improve image quality.

## Authorship & Links

- Created by: `NVIDIA`
- Author URL: `https://developer.nvidia.com/dlss`
- Support: `mailto:DLSS-Support@nvidia.com`

## Modules (9)

| Name | Host type | Loading phase |
|---|---|---|
| `DLSS` | `Runtime` | `PostEngineInit` |
| `DLSSBlueprint` | `Runtime` | `PostConfigInit` |
| `DLSSEditor` | `Editor` | `PostEngineInit` |
| `DLSSUtility` | `Runtime` | `PostConfigInit` |
| `NGXD3D11RHI` | `Runtime` | `PostEngineInit` |
| `NGXD3D12RHI` | `Runtime` | `PostEngineInit` |
| `NGXRHI` | `Runtime` | `PostEngineInit` |
| `NGXVulkanRHI` | `Runtime` | `PostEngineInit` |
| `NGXVulkanRHIPreInit` | `Runtime` | `PostConfigInit` |

## Plugin dependencies (1)

| Plugin | Enabled | Optional |
|---|---|---|
| `StreamlineNGXCommon` | yes | no |

## Registered native types (0)

_None — this plugin's modules register no UClass subclasses of any allowlist base (EQS / StateTree / BT / Anim / GAS / SmartObject / Chooser / Mass)._

