# StreamlineDLSSG

## Identity

| Field | Value |
|---|---|
| Plugin name | `StreamlineDLSSG` |
| Friendly name | NVIDIA DLSS Frame Generation and DLSS Multi Frame Generation |
| Plugin type | `Project` |
| Base dir | `Plugins/Marketplace/StreamlineDLSSG` |
| Enabled | yes |
| Version | `129` (`8.5.0-SL2.10.3`) |
| Category | `Rendering` |
| Can contain content | no |
| Installed | yes |
| Engine version (export) | `5.7.4-573521+++UE_DOW+main` |
| Plugin version (tool) | `1.28.6` |

## Description

NVIDIA DLSS Frame Generation and DLSS Multi Frame Generation use AI to boost frame rates by generating additional high-quality frames, all while optimizing responsiveness with NVIDIA Reflex.

## Authorship & Links

- Created by: `NVIDIA`
- Author URL: `https://developer.nvidia.com/rtx/streamline`
- Support: `mailto:DLSS-Support@nvidia.com`

## Modules (1)

| Name | Host type | Loading phase |
|---|---|---|
| `StreamlineDLSSGBlueprint` | `Runtime` | `PostEngineInit` |

## Plugin dependencies (2)

| Plugin | Enabled | Optional |
|---|---|---|
| `StreamlineCore` | yes | no |
| `StreamlineReflex` | yes | no |

## Registered native types (0)

_None — this plugin's modules register no UClass subclasses of any allowlist base (EQS / StateTree / BT / Anim / GAS / SmartObject / Chooser / Mass)._

