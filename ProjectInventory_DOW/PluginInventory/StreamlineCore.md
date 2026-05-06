# StreamlineCore

## Identity

| Field | Value |
|---|---|
| Plugin name | `StreamlineCore` |
| Friendly name | NVIDIA Streamline Core (hidden, implementation detail) |
| Plugin type | `Project` |
| Base dir | `Plugins/Marketplace/StreamlineCore` |
| Enabled | yes |
| Version | `129` (`8.5.0-SL2.10.3`) |
| Category | `Rendering` |
| Can contain content | no |
| Installed | yes |
| Engine version (export) | `5.7.4-573521+++UE_DOW+main` |
| Plugin version (tool) | `1.28.6` |

## Description

Please use the specific NVIDIA Streamline feature plugins for DLSS-FG etc

## Authorship & Links

- Created by: `NVIDIA`
- Author URL: `https://developer.nvidia.com/rtx/streamline`
- Support: `mailto:DLSS-Support@nvidia.com`

## Modules (6)

| Name | Host type | Loading phase |
|---|---|---|
| `StreamlineBlueprint` | `Runtime` | `PostEngineInit` |
| `StreamlineCore` | `Runtime` | `PostEngineInit` |
| `StreamlineD3D11RHI` | `Runtime` | `None` |
| `StreamlineD3D12RHI` | `Runtime` | `None` |
| `StreamlineRHI` | `Runtime` | `PostSplashScreen` |
| `StreamlineShaders` | `Runtime` | `PostConfigInit` |

## Plugin dependencies (1)

| Plugin | Enabled | Optional |
|---|---|---|
| `StreamlineNGXCommon` | yes | no |

## Registered native types (0)

_None — this plugin's modules register no UClass subclasses of any allowlist base (EQS / StateTree / BT / Anim / GAS / SmartObject / Chooser / Mass)._

