# W_LightRow

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Developers/rickunderhill/EditorUtility/W_LightRow.W_LightRow` |
| Asset name | `W_LightRow` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UserWidget` (`/Script/UMG.UserWidget`, native, module `/Script/UMG`)
- Interfaces (1):
  - `/Script/UMG.UserObjectListEntry`

## Variables (2)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `OwningWidget` | `object<LightingEditor_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Actor` | `object<Actor>` | `None` | `Default` | — | — | InstanceEditable, Private |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (2)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`

## Graphs

- Event graph: `EventGraph` (32 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `GridPanel_0` (`GridPanel`)
  - `SizeBox_0` (`SizeBox`) via GridSlot
    - `Button_Light` (`Button`) [variable] via SizeBoxSlot
      - `LightType` (`TextBlock`) [variable] via ButtonSlot
  - `SizeBox_1` (`SizeBox`) via GridSlot
    - `Image_69` (`Image`) [variable] via SizeBoxSlot
  - `SizeBox_2` (`SizeBox`) via GridSlot
    - `Intensity` (`TextBlock`) [variable] via SizeBoxSlot
  - `SizeBox_3` (`SizeBox`) via GridSlot
    - `CheckBox_50` (`CheckBox`) [variable] via SizeBoxSlot

## References

Hard refs out (8):
- `/Engine/MobileResources/HUD/MobileHUDDirectionStick` [asset]
- `/Game/Developers/rickunderhill/EditorUtility/BPI_LightingEditor` [asset]
- `/Game/Developers/rickunderhill/EditorUtility/LightCompItem` [asset]
- `/Game/Developers/rickunderhill/EditorUtility/LightingEditor` [asset]
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

