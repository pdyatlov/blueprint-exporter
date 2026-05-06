# BP_LightFixture

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Art/EnvKits/Micro/Lighting/Blueprints/BP_LightFixture.BP_LightFixture` |
| Asset name | `BP_LightFixture` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (18)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `bOverrideLightSettings` | `bool` | `False` | `Light` | — | — | InstanceEditable |
| `Intensity` | `real<double>` | `8.000000` | `Light` | — | — | InstanceEditable |
| `AttenuationRadius` | `real<double>` | `800.000000` | `Light` | — | — | InstanceEditable |
| `Color` | `struct<LinearColor>` | `(R=1.000000,G=0.000000,B=0.750000,A=1.000000)` | `Light` | — | — | InstanceEditable |
| `bUseTemperature` | `bool` | `True` | `Light` | — | — | InstanceEditable |
| `ColorTemperature` | `real<double>` | `6500.000000` | `Light` | — | — | InstanceEditable |
| `IES_Profile` | `object<TextureLightProfile>` | `None` | `Light` | — | — | InstanceEditable |
| `DefaultState` | `int` | `1` | `Light` | — | — | InstanceEditable, Private |
| `bCastShadows` | `bool` | `True` | `Light` | — | — | InstanceEditable |
| `bOverrideEmissiveColor` | `bool` | `False` | `Light` | — | — | InstanceEditable |
| `EmissiveColor` | `struct<LinearColor>` | `(R=1.000000,G=0.000000,B=0.750000,A=1.000000)` | `Light` | — | — | InstanceEditable |
| `EmissiveIntensity` | `real<double>` | `1.000000` | `Light` | — | — | InstanceEditable |
| `bSwitchEmissiveSlot` | `bool` | `False` | `Light` | — | — | InstanceEditable |
| `EmissiveMaterial` | `object<MaterialInstanceDynamic>` | `None` | `Light` | — | — | InstanceEditable |
| `LightComponents` | `TArray<object<LightComponent>>` | — | `Private` | — | — | InstanceEditable, Private |
| `EmissiveMaterials` | `TArray<object<MaterialInstanceConstant>>` | — | `Private` | — | — | InstanceEditable, Private |
| `RectSourceWidth` | `real<float>` | `-1.000000` | `Private` | — | — | InstanceEditable, Private |
| `RectSourceHeight` | `real<float>` | `-1.000000` | `Private` | — | — | InstanceEditable, Private |

## Functions (5)

### `GatherLightComponents`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11

### `Overrides`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1

### `SetLightParameters`

- Access: `Public`
- Flags: —
- Inputs: `(struct<LinearColor> Color, object<LightComponent> Light, real<float> SetIntensity, real<float> SetTemperature, object<TextureLightProfile> SetIESTexture, bool SetCastShadows, bool Temperature)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 25

### `UpdateEmissive`

- Access: `Public`
- Flags: —
- Inputs: `(object<LightComponentBase> Light)`
- Outputs: `()`
- Local variables (2): `CurrentMaterialIndex`, `CurrentIndex`
- Nodes: 35

### `UpdateRectLightSourceScale`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 22

## Macros (0)

_None._

## Components (1)

- `Scene` — `SceneComponent` @ socket `None`
  - `StaticMesh` — `StaticMeshComponent` @ socket `None`

## Class Default Object (1)

- `PrimaryActorTick` (`FActorTickFunction`) = `(bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (0 nodes)
- Construction script: `UserConstructionScript` (16 nodes)
- Additional graphs: _none_

## References

Hard refs out (4):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Art/Shaders/Environment/RapidShaders/R_E1` [asset]
- `/Game/Art/Shaders/Environment/RapidShaders/R_E2` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

