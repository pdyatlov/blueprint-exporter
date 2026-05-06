# BP_ScriptableButton

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Prototype/Mission/BP_ScriptableButton.BP_ScriptableButton` |
| Asset name | `BP_ScriptableButton` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `BP_MissionScriptable_C` (`/Game/Prototype/Mission/Core/BP_MissionScriptable.BP_MissionScriptable_C`, blueprint)
- Interfaces (1):
  - `/Game/Standards/iDamagable.iDamagable_C`

## Variables (1)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `NewVar_0` | `TMap<object<S_ActivationType>>, struct:/Game/Prototype/Mission/Structs/S_ActivationType.S_ActivationType>` | `()` | `Default` | — | — | InstanceEditable |

## Functions (0)

_None._

## Macros (0)

_None._

## Components (2)

- `SM_Cube` — `StaticMeshComponent` @ socket `None`
  - `Sphere` — `SphereComponent` @ socket `None`
- `PointLight` — `PointLightComponent` @ socket `None`

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (11 nodes)
- Construction script: `UserConstructionScript` (2 nodes)
- Additional graphs: _none_

## References

Hard refs out (9):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Engine/EditorResources/LightIcons/S_LightError` [asset]
- `/Game/Art/Discovery/LevelPrototyping/SM_Cube` [asset]
- `/Game/Prototype/Mission/BlueprintInterface/BPI_MissionScripting` [asset]
- `/Game/Prototype/Mission/Core/BP_MissionScriptable` [asset]
- `/Game/Prototype/Mission/Core/BP_MissionScriptable.BP_MissionScriptable_C` [Blueprint]
- `/Game/Prototype/Mission/Structs/S_ActivationType` [asset]
- `/Game/Standards/iDamagable` [asset]
- `/Script/NavigationSystem` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

