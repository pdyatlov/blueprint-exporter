# BPW_DLSSSR_UpscalingAA

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/NVIDIA_DEV/BPW_DLSSSR_UpscalingAA.BPW_DLSSSR_UpscalingAA` |
| Asset name | `BPW_DLSSSR_UpscalingAA` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (4)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `s_sharpness` | `object<BPW_Graphics_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `DLSSMode` | `byte<UDLSSMode>` | `Off` | `Default` | — | — | InstanceEditable, Private |
| `Widgets` | `TArray<object<Widget>>` | — | `Default` | — | — | InstanceEditable |
| `Resolutions` | `object<DataTable>` | `None` | `Default` | — | — | InstanceEditable, Private |

## Functions (7)

### `GetSupportedUpscalers`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(TArray<string> OutOptions)`
- Local variables (1): `Options`
- Nodes: 22

### `InitBPW_UpscalingAA`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 85

### `InitSharpness`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

### `SetAntiAliasingCVar`

- Access: `Public`
- Flags: —
- Inputs: `(byte AAMode = NewEnumerator0)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Default`

### `SetUpscaleBuiltIn`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 25
- Category: `Default`

### `SetUpscaleDLSS`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 26
- Category: `Default`

### `SetUpscaleNIS`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 19
- Category: `Default`

## Macros (3)

### `Enable DLAA`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `Set DLSS Mode`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

### `SetScreenResolution`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (4)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Custom`
- `DesignTimeSize` (`FVector2D`) = `(X=354.000000,Y=1130.000000)`

## Graphs

- Event graph: `EventGraph` (131 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `brd_upscalingAA` (`Border`) [variable]
  - `vb_upscalingaa` (`VerticalBox`) via BorderSlot
    - `upscalingaa` (`VerticalBox`) via VerticalBoxSlot
      - `t_upscaling_aa` (`BPWC_Title_C`) via VerticalBoxSlot
      - `BPW_WindowMode` (`BPW_WindowMode_C`) [variable] via VerticalBoxSlot
      - `BPW_ResolutionMenu` (`BPW_ResolutionMenu_C`) [variable] via VerticalBoxSlot
      - `l_upscaling` (`BPW_List_C`) [variable] via VerticalBoxSlot
      - `l_antialiasing` (`BPW_List_C`) [variable] via VerticalBoxSlot
      - `s_resolution_scale` (`BPW_Slider_C`) [variable] via VerticalBoxSlot
    - `BPW_Graphics` (`BPW_Graphics_C`) [variable] via VerticalBoxSlot
    - `vb_dlsssr` (`VerticalBox`) via VerticalBoxSlot
      - `dlss` (`VerticalBox`) via VerticalBoxSlot
        - `t_dlss` (`BPWC_Title_C`) via VerticalBoxSlot
        - `t_dlss_supported` (`BPW_Stat_C`) [variable] via VerticalBoxSlot
        - `l_dlss` (`BPW_List_C`) [variable] via VerticalBoxSlot
        - `s_dlss_sharpness` (`BPW_Slider_C`) [variable] via VerticalBoxSlot
        - `b_dlssrr` (`BPW_Checkbox_C`) [variable] via VerticalBoxSlot
        - `b_dlss_showstats` (`BPW_Checkbox_C`) [variable] via VerticalBoxSlot
        - `BPW_DevStat_DLSSSR` (`BPW_DevStats_DLSSSR_C`) [variable] via VerticalBoxSlot
      - `vbNIS` (`VerticalBox`) [variable] via VerticalBoxSlot
        - `t_nis` (`BPWC_Title_C`) via VerticalBoxSlot
        - `l_imagescaling` (`BPW_List_C`) [variable] via VerticalBoxSlot
        - `s_custom_res` (`BPW_Slider_C`) [variable] via VerticalBoxSlot
        - `s_nis_sharpness` (`BPW_Slider_C`) [variable] via VerticalBoxSlot

## References

Hard refs out (20):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Blueprints/NVIDIA_DEV/BPW_Graphics` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CommonControls/BPW_ResolutionMenu` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CommonControls/BPW_WindowMode` [asset]
- `/Game/Blueprints/NVIDIA_DEV/Core/BPWC_Title` [asset]
- `/Game/Blueprints/NVIDIA_DEV/Core/E_AntiAliasingMode` [asset]
- `/Game/Blueprints/NVIDIA_DEV/Core/E_BuiltInAAModes` [asset]
- `/Game/Blueprints/NVIDIA_DEV/Core/E_UpscaleMode` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_Checkbox` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_List` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_Slider` [asset]
- `/Game/Blueprints/NVIDIA_DEV/CoreControls/BPW_Stat` [asset]
- `/Game/Blueprints/NVIDIA_DEV/DevStats/BPW_DevStats_DLSSSR` [asset]
- `/Game/Blueprints/NVIDIA_DEV/DLSSMacros` [asset]
- `/Script/DLSSBlueprint` [asset]
- `/Script/NISBlueprint` [asset]
- `/Script/SlateCore` [asset]
- `/Script/UMG` [asset]
- `/Script/UMG.UserWidget` [native]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

