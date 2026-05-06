# Temperature_Volume

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/Temperature_Volume.Temperature_Volume` |
| Asset name | `Temperature_Volume` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `UDS_Volume_Actor_C` (`/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Volume_Actor.UDS_Volume_Actor_C`, blueprint)
- Interfaces (1):
  - `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Temperature_Volume_Interface.Temperature_Volume_Interface_C`

## Variables (6)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Temperature Offset` | `real<double>` | `0.000000` | `Temperature Effects` | — | — | InstanceEditable |
| `Replace Temperature` | `bool` | `False` | `Temperature Effects` | — | — | InstanceEditable |
| `Replacement Temperature` | `real<double>` | `0.000000` | `Temperature Effects` | — | — | InstanceEditable |
| `Apply Local Interior Temperature` | `bool` | `False` | `Temperature Effects` | — | — | InstanceEditable |
| `Local Interior Temperature` | `real<double>` | `72.000000` | `Temperature Effects` | — | — | InstanceEditable |
| `Overall Effect Multiplier` | `real<double>` | `1.000000` | `Temperature Effects` | — | — | InstanceEditable |

## Functions (2)

### `Query Temperature Volume`

- Interface override of `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Temperature_Volume_Interface.Temperature_Volume_Interface_C`
- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Sample Location = 0, 0, 0)`
- Outputs: `(real<double> Offset, real<double> Interior Temp, real<double> Interior Alpha, real<double> Manual Temp, real<double> Manual Alpha)`
- Local variables (1): `Multiplier`
- Nodes: 17

### `📘 Temperature`

- Access: `Private`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4
- Category: `Shape`

## Macros (0)

_None._

## Components (1)

- `UDS_Utility_Opener_Component` — `UDS_Utility_Opener_C` @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (2 nodes)
- Construction script: `UserConstructionScript` (2 nodes)
- Additional graphs: _none_

## References

Hard refs out (7):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/Editor_UI/UDS_Utility_Opener_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Volume_Actor` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_Volume_Actor.UDS_Volume_Actor_C` [Blueprint]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Temperature_Volume_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Textures/Icons/Temperature_Volume` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

