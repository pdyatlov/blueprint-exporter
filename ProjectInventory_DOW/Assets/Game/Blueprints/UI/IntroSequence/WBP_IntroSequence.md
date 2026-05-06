# WBP_IntroSequence

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/UI/IntroSequence/WBP_IntroSequence.WBP_IntroSequence` |
| Asset name | `WBP_IntroSequence` |
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
| `MediaPlayer` | `object<MediaPlayer>` | `/Script/MediaAssets.MediaPlayer'/Game/Art/UI/VideoSequence/MP_LoadingSequence.MP_LoadingSequence'` | `Default` | — | — | InstanceEditable, Private |
| `CurrentStage` | `int` | `0` | `Default` | — | — | InstanceEditable, Private |
| `OnIntroComplete` | `mcdelegate` | `()` | `Default` | — | — | InstanceEditable, Private |

## Functions (4)

### `PlayVideo`

- Access: `Public`
- Flags: —
- Inputs: `(bool Looping, object<MediaSource> Video, int Stage, text ButtonText)`
- Outputs: `()`
- Local variables (1): `Media`
- Nodes: 16

### `SetButtonInteractible`

- Access: `Public`
- Flags: —
- Inputs: `(bool Value)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `SetButtonText`

- Access: `Public`
- Flags: —
- Inputs: `(text Text)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

### `SetButtonVisible`

- Access: `Public`
- Flags: —
- Inputs: `(bool Value)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (2)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bIsFocusable` (`uint8`) = `True`

## Graphs

- Event graph: `EventGraph` (25 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_23` (`CanvasPanel`)
  - `VideoImage` (`Image`) [variable] via CanvasPanelSlot
  - `Button` (`WBP_FillButton_C`) [variable] via CanvasPanelSlot

## References

Hard refs out (12):
- `/Game/Art/UI/VideoSequence/MP_LoadingSequence` [asset]
- `/Game/Art/UI/VideoSequence/MP_LoadingSequence_Material` [asset]
- `/Game/Blueprints/UI/GenericElements/WBP_FillButton` [asset]
- `/Game/Movies/Loading_Hacking` [asset]
- `/Game/Movies/Loading_Intro` [asset]
- `/Game/Movies/Loading_Map` [asset]
- `/Script/InputCore` [asset]
- `/Script/MediaAssets` [asset]
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

