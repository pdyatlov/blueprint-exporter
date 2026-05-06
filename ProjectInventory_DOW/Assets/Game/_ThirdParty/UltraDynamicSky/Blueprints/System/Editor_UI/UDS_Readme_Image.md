# UDS_Readme_Image

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Readme_Image.UDS_Readme_Image` |
| Asset name | `UDS_Readme_Image` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `EditorUtilityWidget` (`/Script/Blutility.EditorUtilityWidget`, native, module `/Script/Blutility`)
- Interfaces: _none_

## Variables (2)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Image URL` | `string` | — | `Default` | — | — | InstanceEditable |
| `Caption Text` | `string` | — | `Default` | — | — | InstanceEditable |

## Functions (1)

### `On_Image_MouseButtonDown`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Geometry> MyGeometry, struct<PointerEvent>& MouseEvent [ref])`
- Outputs: `(struct<EventReply> ReturnValue)`
- Local variables: _none_
- Nodes: 8

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (5)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Custom`
- `DesignTimeSize` (`FVector2D`) = `(X=701.000000,Y=501.000000)`
- `PaletteCategory` (`FText`) = `NSLOCTEXT("", "905F674146DBBF07AF9661A2BB3EC8AF", "UDS_Tools")`

## Graphs

- Event graph: `EventGraph` (11 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `MainCanvasPanel` (`CanvasPanel`) [variable]
  - `VerticalBox_101` (`VerticalBox`) via CanvasPanelSlot
    - `ScaleBox_193` (`ScaleBox`) via VerticalBoxSlot
      - `CanvasPanel_202` (`CanvasPanel`) via ScaleBoxSlot
        - `Border_0` (`Border`) [variable] via CanvasPanelSlot
          - `CanvasPanel_0` (`CanvasPanel`) via BorderSlot
            - `Image` (`Image`) [variable] via CanvasPanelSlot
    - `Caption` (`TextBlock`) [variable] via VerticalBoxSlot

## References

Hard refs out (7):
- `/Engine/EngineMaterials/DefaultDiffuse` [asset]
- `/Script/Blutility` [asset]
- `/Script/Blutility.EditorUtilityWidget` [native]
- `/Script/InputCore` [asset]
- `/Script/SlateCore` [asset]
- `/Script/UMG` [asset]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

