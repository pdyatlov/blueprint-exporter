# BP_DynamicCover_Security

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Prototype/Mission/BP_DynamicCover_Security.BP_DynamicCover_Security` |
| Asset name | `BP_DynamicCover_Security` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `BP_MissionScriptable_C` (`/Game/Prototype/Mission/Core/BP_MissionScriptable.BP_MissionScriptable_C`, blueprint)
- Interfaces: _none_

## Variables (7)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `AnimationEndLocation` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=200.000000)` | `Default` | — | — | InstanceEditable, Private |
| `AnimationDuration` | `real<double>` | `2.000000` | `Default` | — | — | InstanceEditable, Private |
| `Charge` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `IsActive` | `bool` | `True` | `Default` | — | — | InstanceEditable, Private |
| `IsUp` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `ChargeTimer` | `struct<TimerHandle>` | `()` | `Default` | — | — | InstanceEditable, Private |
| `InitialActivation` | `bool` | `True` | `Default` | — | — | InstanceEditable, Private |

## Functions (2)

### `ResetTimer`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4

### `SendActivationMessage`

- Access: `Public`
- Flags: —
- Inputs: `(struct<S_ActivationType> ActivationInfo)`
- Outputs: `(struct<S_ActivationType> PassedActivationType)`
- Local variables: _none_
- Nodes: 3

## Macros (0)

_None._

## Components (6)

- `MoveBarrier` — `SceneComponent` @ socket `None`
  - `SM_DisplayCase_A_15x20x20_01` — `StaticMeshComponent` @ socket `None`
    - `SM_SecurityBarrier_A_Interact_Base` — `StaticMeshComponent` @ socket `None`
      - `SM_SecurityBarrier_A_Interact_Handle` — `StaticMeshComponent` @ socket `None`
- `Sphere` — `SphereComponent` @ socket `None`
  - `PointLight` — `PointLightComponent` @ socket `None`
- `MoveCover` — `SceneComponent` @ socket `None`
  - `SM_SecurityBarrier_A_15x30_01_Cover` — `StaticMeshComponent` @ socket `None`
- `SM_SecurityBarrier_A_15x30_01_Base` — `StaticMeshComponent` @ socket `None`
- `NS_Prototype_SteamJet_01` — `NiagaraComponent` @ socket `None`
- `NS_Prototype_SteamJet_02` — `NiagaraComponent` @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (62 nodes)
- Construction script: `UserConstructionScript` (7 nodes)
- Additional graphs: _none_

## References

Hard refs out (13):
- `/Engine/EditorResources/LightIcons/S_LightError` [asset]
- `/Game/Prototype/Mission/BlueprintInterface/BPI_MissionScripting` [asset]
- `/Game/Prototype/Mission/Core/BP_MissionScriptable` [asset]
- `/Game/Prototype/Mission/Core/BP_MissionScriptable.BP_MissionScriptable_C` [Blueprint]
- `/Game/Prototype/Mission/Structs/S_ActivationType` [asset]
- `/Game/Prototype/TheBank/SecurityBarrier/NS_Prototype_SteamJet_01` [asset]
- `/Game/Prototype/TheBank/SecurityBarrier/SM_SecurityBarrier_A_15x30_01` [asset]
- `/Game/Prototype/TheBank/SecurityBarrier/SM_SecurityBarrier_A_15x30_01_Base` [asset]
- `/Game/Prototype/TheBank/SecurityBarrier/SM_SecurityBarrier_A_15x30_01_Cover` [asset]
- `/Game/Prototype/TheBank/SecurityBarrier/SM_SecurityBarrier_A_Interact_Base` [asset]
- `/Game/Prototype/TheBank/SecurityBarrier/SM_SecurityBarrier_A_Interact_Handle` [asset]
- `/Script/NavigationSystem` [asset]
- `/Script/Niagara` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

