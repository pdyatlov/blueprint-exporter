# UDS_Readme_Entry_Widget

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Readme_Entry_Widget.UDS_Readme_Entry_Widget` |
| Asset name | `UDS_Readme_Entry_Widget` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `EditorUtilityWidget` (`/Script/Blutility.EditorUtilityWidget`, native, module `/Script/Blutility`)
- Interfaces: _none_

## Variables (13)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Entry Text` | `TArray<text>` | `(NSLOCTEXT("[2336BF864FDDC71F5D58D1BDE1A2F814]", "D9B0ECC04FD0FF06B9948BA8A293B7E5", "^Test Title"),NSLOCTEXT("[2336BF864FDDC71F5D58D1BDE1A2F814]", "E47BB97A4545E879BB2242A99B006E21", ">Test Subtitle"),NSLOCTEXT("[2336BF864FDDC71F5D58D1BDE1A2F814]", "DF65D36F40970E2822CDCABD0A35BDD7", "Test Basic Text"))` | `Default` | — | — | InstanceEditable |
| `Entry Title` | `text` | `NSLOCTEXT("[2336BF864FDDC71F5D58D1BDE1A2F814]", "8CE09F6B4076663874096B9B1773421F", "Test Entry Title")` | `Default` | — | — | InstanceEditable |
| `Show Category Label` | `bool` | `False` | `Default` | — | — | InstanceEditable |
| `Category` | `int` | `0` | `Default` | — | — | InstanceEditable |
| `Text Widgets` | `TArray<object<TextBlock>>` | — | `Default` | — | — | InstanceEditable, Private |
| `Expand` | `bool` | `False` | `Default` | — | — | InstanceEditable |
| `Entry Number` | `int` | `0` | `Default` | — | — | InstanceEditable |
| `Entry Content Widgets` | `TArray<object<Widget>>` | — | `Default` | — | — | InstanceEditable, Private |
| `Glossary` | `string` | — | `Default` | — | — | InstanceEditable, Private |
| `Readme` | `object<README_C>` | `None` | `Default` | — | — | InstanceEditable |
| `Entry Row` | `name` | `None` | `Default` | — | — | InstanceEditable |
| `Favorited` | `bool` | `False` | `Default` | — | — | InstanceEditable |
| `Linked Entries` | `TArray<name>` | — | `Default` | — | — | InstanceEditable |

## Functions (5)

### `Check for Entry Formatting`

- Access: `Public`
- Flags: —
- Inputs: `(text Input Text)`
- Outputs: `(bool Indented, bool SubTitle, text Formatting Removed)`
- Local variables: _none_
- Nodes: 12

### `Check for Word Formatting`

- Access: `Public`
- Flags: —
- Inputs: `(string Word)`
- Outputs: `(bool Tooltip, string Displayed Word, struct<UDS_Glossary_Entry> Glossary Entry, bool Tooltip, string Displayed Word, struct<UDS_Glossary_Entry> Glossary Entry)`
- Local variables: _none_
- Nodes: 15

### `Create Entry Links`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (3): `Links Vertical Box`, `Links Area Label`, `Links Wrap Box`
- Nodes: 78

### `Create Text Boxes`

- Access: `Public`
- Flags: —
- Inputs: `(text Text)`
- Outputs: `()`
- Local variables (9): `Text Indented`, `Text Subtitle`, `Plain Text No Formatting`, `Words`, `Wrap Box`, `Font`, `Paragraphs`, `Current Word`, `Italic`
- Nodes: 112

### `Set Expanded Instant`

- Access: `Public`
- Flags: —
- Inputs: `(bool Expand)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (5)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `bHasScriptImplementedTick` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Custom`
- `DesignTimeSize` (`FVector2D`) = `(X=800.000000,Y=300.000000)`
- `PaletteCategory` (`FText`) = `NSLOCTEXT("", "835BBE1240A1F730EF48E2B1E2C8B367", "UDS_Tools")`

## Graphs

- Event graph: `EventGraph` (70 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_0` (`CanvasPanel`)
  - `CanvasPanel_54` (`CanvasPanel`) via CanvasPanelSlot
    - `Image_50` (`Image`) [variable] via CanvasPanelSlot
    - `EntrySizebox` (`SizeBox`) [variable] via CanvasPanelSlot
      - `ExpandButton` (`Button`) [variable] via SizeBoxSlot
        - `EntryBox` (`VerticalBox`) [variable] via ButtonSlot
          - `HorizontalBox_0` (`HorizontalBox`) via VerticalBoxSlot
            - `TitleText_1` (`TextBlock`) [variable] via HorizontalBoxSlot
            - `Number` (`TextBlock`) [variable] via HorizontalBoxSlot
            - `CategoryLabel` (`TextBlock`) [variable] via HorizontalBoxSlot
            - `Favorite_Checkbox` (`CheckBox`) [variable] via HorizontalBoxSlot
          - `Spacer_109` (`Spacer`) via VerticalBoxSlot
          - `Line` (`Image`) via VerticalBoxSlot
          - `Spacer_80` (`Spacer`) via VerticalBoxSlot

## References

Hard refs out (18):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Engine/EngineFonts/Roboto` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/README` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Glossary` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Glossary_Entry` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Readme_Entry_Link` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Readme_Image` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Readme_Tooltip_Word` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Star_Icon_Off` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Star_Icon_On` [asset]
- `/Script/Blutility` [asset]
- `/Script/Blutility.EditorUtilityWidget` [native]
- `/Script/MovieScene` [asset]
- `/Script/MovieSceneTracks` [asset]
- `/Script/SlateCore` [asset]
- `/Script/SlateRHIRenderer` [asset]
- `/Script/UMG` [asset]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

