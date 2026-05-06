# WB_SimpleController

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Widgets/WidgetData/WB_SimpleController.WB_SimpleController` |
| Asset name | `WB_SimpleController` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces: _none_

## Variables (3)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `PlayerController` | `object<PlayerController>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `WSAD` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `MOUSE` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |

## Functions (3)

### `GetKeysTotalAnalogState`

- Access: `Public`
- Flags: —
- Inputs: `(TArray<struct<Key>> Keys)`
- Outputs: `(real<float> ReturnValue)`
- Local variables (1): `AnalogValue`
- Nodes: 9

### `SetMouseValues`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11

### `SetWSADValues`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `bHasScriptImplementedPaint` (`uint8`) = `False`

## Graphs

- Event graph: `EventGraph` (117 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_0` (`CanvasPanel`)
  - `ScaleBox_0` (`ScaleBox`) via CanvasPanelSlot
    - `Overlay_46` (`Overlay`) via ScaleBoxSlot
      - `Controller` (`Image`) via OverlaySlot
      - `ControllerDetail` (`Image`) via OverlaySlot
      - `A_Off` (`Image`) via OverlaySlot
      - `B_Off` (`Image`) via OverlaySlot
      - `X_Off` (`Image`) via OverlaySlot
      - `Y_Off` (`Image`) via OverlaySlot
      - `LB_Off` (`Image`) via OverlaySlot
      - `LT_Off` (`Image`) via OverlaySlot
      - `RB_Off` (`Image`) via OverlaySlot
      - `RT_Off` (`Image`) via OverlaySlot
      - `DPad_Off` (`Image`) via OverlaySlot
      - `Select_Off` (`Image`) via OverlaySlot
      - `Start_Off` (`Image`) via OverlaySlot
      - `Center_Button_Off` (`Image`) via OverlaySlot
      - `A_On` (`Image`) [variable] via OverlaySlot
      - `B_On` (`Image`) [variable] via OverlaySlot
      - `X_On` (`Image`) [variable] via OverlaySlot
      - `Y_On` (`Image`) [variable] via OverlaySlot
      - `LB_On` (`Image`) [variable] via OverlaySlot
      - `LT_On` (`Image`) [variable] via OverlaySlot
      - `RB_On` (`Image`) [variable] via OverlaySlot
      - `RT_On` (`Image`) [variable] via OverlaySlot
      - `DU` (`Image`) [variable] via OverlaySlot
      - `DD` (`Image`) [variable] via OverlaySlot
      - `DL` (`Image`) [variable] via OverlaySlot
      - `DR` (`Image`) [variable] via OverlaySlot
      - `Select_On` (`Image`) [variable] via OverlaySlot
      - `Start_On` (`Image`) [variable] via OverlaySlot
      - `LS_Position` (`CanvasPanel`) [variable] via OverlaySlot
        - `LS_Off` (`Image`) via CanvasPanelSlot
        - `LS_On` (`Image`) [variable] via CanvasPanelSlot
        - `LS_Down` (`Image`) [variable] via CanvasPanelSlot
      - `RS_Position` (`CanvasPanel`) [variable] via OverlaySlot
        - `RS_Off` (`Image`) via CanvasPanelSlot
        - `RS_On` (`Image`) [variable] via CanvasPanelSlot
        - `RS_Down` (`Image`) [variable] via CanvasPanelSlot

## References

Hard refs out (28):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/A` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/B` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/Center_Button` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/Controller` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/Controller_Detail` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/D_Down` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/D_Left` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/D_Pad` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/D_Right` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/D_Up` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/LB` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/LS` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/LS_Down` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/LT` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/RB` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/RS` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/RS_Down` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/RT` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/Select` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/Start` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/X` [asset]
- `/Game/_ThirdParty/GASP_example/Widgets/Images/Y` [asset]
- `/Script/InputCore` [asset]
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

