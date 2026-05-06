# NIS

## Identity

| Field | Value |
|---|---|
| Plugin name | `NIS` |
| Friendly name | NVIDIA Image Scaling (NIS) |
| Plugin type | `Project` |
| Base dir | `Plugins/Marketplace/NIS` |
| Enabled | yes |
| Version | `14` (`8.5.0`) |
| Category | `Rendering` |
| Can contain content | no |
| Installed | yes |
| Engine version (export) | `5.7.4-573521+++UE_DOW+main` |
| Plugin version (tool) | `1.28.6` |

## Description

NVIDIA Image Scaling boosts frame rates using GPU scaling and sharpening.

## Authorship & Links

- Created by: `NVIDIA`
- Author URL: `https://developer.nvidia.com/image-scaling`
- Support: `mailto:DLSS-Support@nvidia.com`

## Modules (3)

| Name | Host type | Loading phase |
|---|---|---|
| `NISBlueprint` | `Runtime` | `PostConfigInit` |
| `NISCore` | `Runtime` | `PostEngineInit` |
| `NISShaders` | `Runtime` | `PostConfigInit` |

## Plugin dependencies (0)

_None._

## Registered native types (0)

_None — this plugin's modules register no UClass subclasses of any allowlist base (EQS / StateTree / BT / Anim / GAS / SmartObject / Chooser / Mass)._

