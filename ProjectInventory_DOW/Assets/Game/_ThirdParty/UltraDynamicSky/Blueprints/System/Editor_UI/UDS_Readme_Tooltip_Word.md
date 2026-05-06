# UDS_Readme_Tooltip_Word

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Readme_Tooltip_Word.UDS_Readme_Tooltip_Word` |
| Asset name | `UDS_Readme_Tooltip_Word` |
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
| `Color` | `struct<LinearColor>` | `(R=0.000000,G=0.000000,B=0.000000,A=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `Glossary Entry` | `struct<UDS_Glossary_Entry>` | `()` | `Default` | — | — | InstanceEditable, Private |

## Functions (1)

### `Get_Text_ToolTipWidget_0`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(object<Widget> ReturnValue)`
- Local variables: _none_
- Nodes: 8

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (4)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Desired`
- `PaletteCategory` (`FText`) = `NSLOCTEXT("", "EB420BCB48E5CCBB198C7883BA3A077F", "UDS_Tools")`

## Graphs

- Event graph: `EventGraph` (12 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `Button_0` (`Button`) [variable]
  - `Text` (`TextBlock`) [variable] via ButtonSlot

## References

Hard refs out (8):
- `/Engine/EngineResources/WhiteSquareTexture` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Glossary_Entry` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Glossary_Tooltip` [asset]
- `/Script/Blutility` [asset]
- `/Script/Blutility.EditorUtilityWidget` [native]
- `/Script/SlateCore` [asset]
- `/Script/UMG` [asset]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

