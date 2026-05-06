# UDS_Weather_Settings

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings` |
| Asset name | `UDS_Weather_Settings` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `PrimaryDataAsset` (`/Script/Engine.PrimaryDataAsset`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (19)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Cloud Coverage` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable |
| `Rain` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable |
| `Snow` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable |
| `Thunder/Lightning` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable |
| `Wind Intensity` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable |
| `Fog` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable |
| `Dust` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable |
| `Material Wetness` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable |
| `Material Snow Coverage` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable |
| `Material Dust Coverage` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable |
| `Sky Modifier` | `object<UDS_Modifier_C>` | `None` | `Default` | — | — | InstanceEditable |
| `Icon Texture` | `softobject<Texture2D>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Weather_Icon_BG.Weather_Icon_BG` | `Default` | — | — | InstanceEditable |
| `User Friendly Name` | `text` | `NSLOCTEXT("", "AA3CADF74F883E82CB495798FBE0938B", "None")` | `Default` | — | — | InstanceEditable, Private |
| `State Sources` | `TMap<object<UDS_Weather_Settings_C,>>, real>` | `()` | `Managed Variables` | — | — | InstanceEditable, Private |
| `Symbol Texture` | `softobject<Texture2D>` | `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Symbols/Unknown.Unknown` | `Default` | — | — | InstanceEditable |
| `Changing` | `bool` | `False` | `Managed Variables` | — | — | InstanceEditable, Private |
| `Temperature` | `real<double>` | `0.000000` | `Managed Variables` | — | — | InstanceEditable, Private |
| `Wind Direction` | `real<double>` | `0.000000` | `Managed Variables` | — | — | InstanceEditable, Private |
| `Is Local Weather` | `bool` | `False` | `Managed Variables` | — | — | InstanceEditable, Private |

## Functions (10)

### `Are Material Values Identical`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Weather_Settings_C> State Object to Compare)`
- Outputs: `(bool Yes)`
- Local variables: _none_
- Nodes: 12
- Description: Just compares material state values, not weather

### `Are Weather Values Identical`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Weather_Settings_C> State Object to Compare)`
- Outputs: `(bool Yes)`
- Local variables: _none_
- Nodes: 24
- Description: Just compares weather values, not material state

### `Copy Weather State`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Weather_Settings_C> Source, bool Set Material Effects = true, bool Copy Sources)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 39
- Description: Copies another Weather Settings object's values into this object

### `Copy Weather State Structure to Object`

- Access: `Public`
- Flags: —
- Inputs: `(struct<UDW_WeatherState_Structure> Struct)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 3
- Category: `Default`

### `Custom Weather Behavior`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Alpha, object<Actor> UDS, object<Actor> UDW)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Description: Called by UDW whenever weather state changes in a way which involves this preset. Can be overridden by a child of the UDS Weather Settings class to add additional logic for custom weather presets. See the Custom Weather Behavior entry in the readme for more info.

### `Get State Sources`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(TMap<object<UDS_Weather_Settings_C,>>, real> Sources, TMap<object<UDS_Weather_Settings_C,>>, real> Sources)`
- Local variables: _none_
- Nodes: 9
- Description: Gets a map which represents the weather obejcts which comprise this object, if it is a composite of multiple. If not, it outputs a single entry map referencing itself as the only source.

### `Lerp Between Weather States`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Weather_Settings_C> A, object<UDS_Weather_Settings_C> B, real<double> Alpha, real<double> Material Alpha = -1.000000, bool Set Material Effects, bool Use Bias for Material Effects = true, bool Lerp Sources)`
- Outputs: `()`
- Local variables (2): `Biased Alpha`, `Material State Alpha`
- Nodes: 130
- Category: `Default`
- Description: Sets the values on this object by interpolating the values from an A and B object

### `Lerp State Source Maps`

- Access: `Public`
- Flags: —
- Inputs: `(object<UDS_Weather_Settings_C> A, object<UDS_Weather_Settings_C> B, real<double> Alpha)`
- Outputs: `()`
- Local variables (3): `Keys Buffer`, `State Sources A`, `State Sources B`
- Nodes: 26
- Category: `Default`

### `Populate Weather State`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Cloud Coverage, real<double> Rain, real<double> Snow, real<double> Thunder/Lightning, real<double> Wind Intensity, real<double> Fog, real<double> Dust, real<double> Material Wetness, real<double> Material Snow, real<double> Material Dust)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11
- Category: `Default`
- Description: Copies separate input values into a weather state object

### `Weather State Object to Structure`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(struct<UDW_WeatherState_Structure> Structure)`
- Local variables: _none_
- Nodes: 13
- Category: `Default`

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0) — DataAsset

_No authored overrides found on the CDO. `DataAsset` Blueprints typically author their payload here — if this BP is meant to differ from its parent class, this is a coverage gap._

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (7):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Modifier` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Modifier_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDW_WeatherState_Structure` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Symbols/Unknown` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Weather/Weather_Icon_BG` [asset]
- `/Script/Engine.PrimaryDataAsset` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

