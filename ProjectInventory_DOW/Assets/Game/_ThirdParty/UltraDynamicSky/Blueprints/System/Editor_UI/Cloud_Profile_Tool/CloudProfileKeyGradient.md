# CloudProfileKeyGradient

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/Cloud_Profile_Tool/CloudProfileKeyGradient.CloudProfileKeyGradient` |
| Asset name | `CloudProfileKeyGradient` |
| Subclass | `WidgetBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `EditorUtilityWidget` (`/Script/Blutility.EditorUtilityWidget`, native, module `/Script/Blutility`)
- Interfaces: _none_

## Variables (7)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Gradient Label` | `string` | — | `Specific` | — | — | InstanceEditable |
| `In Tool Tip Text` | `text` | — | `Specific` | — | — | InstanceEditable |
| `Authoring Tool` | `object<Cloud_Profile_Authoring_Tool_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Setting Index` | `int` | `0` | `Specific` | — | — | InstanceEditable |
| `Selected Key Index` | `int` | `-1` | `Default` | — | — | InstanceEditable, Private |
| `Dragging Key Bar` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Gradient Target` | `object<TextureRenderTarget2D>` | `None` | `Default` | — | — | InstanceEditable, Private |

## Functions (11)

### `Get Value on Gradient`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Position, TArray<struct<Vector2D>> Sorted Array)`
- Outputs: `(real<double> Value, real<double> Value, real<double> Value, real<double> Value, real<double> Value)`
- Local variables (3): `Current Key`, `Inserted`, `Index Between`
- Nodes: 48

### `Get_KeyValueSpinCanvas_Visibility`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(byte ReturnValue)`
- Local variables: _none_
- Nodes: 8
- Category: `Bindings`

### `On_BarBorder_MouseButtonDown`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Geometry> MyGeometry, struct<PointerEvent>& MouseEvent [ref])`
- Outputs: `(struct<EventReply> ReturnValue)`
- Local variables (2): `Click Position`, `Clicked New Key`
- Nodes: 41
- Category: `Bindings`

### `On_BarBorder_MouseButtonUp`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Geometry> MyGeometry, struct<PointerEvent>& MouseEvent [ref])`
- Outputs: `(struct<EventReply> ReturnValue)`
- Local variables: _none_
- Nodes: 4
- Category: `Bindings`

### `On_BarBorder_MouseDoubleClick`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Geometry> MyGeometry, struct<PointerEvent>& MouseEvent [ref])`
- Outputs: `(struct<EventReply> ReturnValue)`
- Local variables (1): `Click Position`
- Nodes: 46
- Category: `Bindings`

### `On_BarBorder_MouseMove`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Geometry> MyGeometry, struct<PointerEvent>& MouseEvent [ref])`
- Outputs: `(struct<EventReply> ReturnValue)`
- Local variables (1): `Click Position`
- Nodes: 36
- Category: `Bindings`

### `Place Key Editor`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 24

### `Populate Gradient Keys`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (3): `Current Image`, `Index`, `Position`
- Nodes: 35

### `Sort Key Array`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(TArray<struct<Vector2D>> Sorted)`
- Local variables (3): `Current Key`, `Inserted`, `Sorted Array`
- Nodes: 31

### `Update Drag`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

### `Update Gradient Preview`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (3): `Sorted Array`, `Canvas`, `Pixel`
- Nodes: 41

## Macros (1)

### `Get Key Array`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (4)

- `bHasScriptImplementedPaint` (`uint8`) = `False`
- `DesignSizeMode` (`EDesignPreviewSizeMode`) = `Desired`
- `DesignTimeSize` (`FVector2D`) = `(X=160.000000,Y=500.000000)`
- `PaletteCategory` (`FText`) = `NSLOCTEXT("", "25F8834F4D107CBA4013C7953AA29BBB", "UDS_Tools")`

## Graphs

- Event graph: `EventGraph` (46 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## Widget Tree

- `CanvasPanel_47` (`CanvasPanel`)
  - `Spacer_177` (`Spacer`) via CanvasPanelSlot
  - `Image_51` (`Image`) [variable] via CanvasPanelSlot
  - `VerticalBox_70` (`VerticalBox`) via CanvasPanelSlot
    - `CanvasPanel_173` (`CanvasPanel`) via VerticalBoxSlot
      - `CanvasPanel_135` (`CanvasPanel`) via CanvasPanelSlot
        - `Gradient` (`Image`) [variable] via CanvasPanelSlot
      - `CanvasPanel_863` (`CanvasPanel`) via CanvasPanelSlot
        - `Image_293` (`Image`) [variable] via CanvasPanelSlot
        - `Image_290` (`Image`) [variable] via CanvasPanelSlot
        - `GradientKeyCanvas` (`CanvasPanel`) [variable] via CanvasPanelSlot
        - `BarBorder` (`Border`) [variable] via CanvasPanelSlot
          - `CanvasPanel_132` (`CanvasPanel`) via BorderSlot
            - `KeyValueSpinCanvas` (`CanvasPanel`) [variable] via CanvasPanelSlot
              - `Image_658` (`Image`) [variable] via CanvasPanelSlot
              - `Image` (`Image`) [variable] via CanvasPanelSlot
              - `Image_241` (`Image`) [variable] via CanvasPanelSlot
              - `KeyEditorSpinbox` (`SpinBox`) [variable] via CanvasPanelSlot
    - `Label` (`TextBlock`) [variable] via VerticalBoxSlot

## References

Hard refs out (11):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/Cloud_Profile_Tool/UDS_CloudProfile_Data` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/Cloud_Profile_Tool/UDS_CloudProfile_Key` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Tools/Cloud_Profile_Authoring_Tool` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Key_Handle` [asset]
- `/Script/Blutility` [asset]
- `/Script/Blutility.EditorUtilityWidget` [native]
- `/Script/Slate` [asset]
- `/Script/SlateCore` [asset]
- `/Script/UMG` [asset]
- `/Script/UMGEditor` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `WidgetBlueprint`
- Custom metadata: _none_

