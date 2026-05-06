# ABP_Civilian_1

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/AI/MassAI/Anims/ABP_Civilian_1.ABP_Civilian_1` |
| Asset name | `ABP_Civilian_1` |
| Subclass | `AnimBlueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `AnimInstance` (`/Script/Engine.AnimInstance`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (7)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Character` | `object<Character>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `MovementComponent` | `object<CharacterMovementComponent>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Velocity` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `GroundSpeed` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `Direction` | `real<double>` | `0.000000` | `Default` | — | — | InstanceEditable, Private |
| `ShouldMove` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `IsFalling` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |

## Functions (1)

### `AnimGraph`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (42 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## State Machines

- **Locomotion** (2 states, 2 transitions)
  - State `Idle` [State] (2 nodes)
  - State `Walk / Run` [State] (4 nodes)
  - Transition `Idle` → `Walk / Run` [StandardBlend] crossfade=0.20s
  - Transition `Walk / Run` → `Idle` [StandardBlend] crossfade=0.30s
- **Main States** (4 states, 6 transitions)
  - State `Fall Loop` [State] (2 nodes)
  - State `Jump` [State] (2 nodes)
  - State `Land` [State] (2 nodes)
  - State `Locomotion` [State] (2 nodes)
  - Transition `Jump` → `Fall Loop` [StandardBlend] crossfade=0.30s
  - Transition `Land` → `Locomotion` [StandardBlend] crossfade=0.50s
  - Transition `Land` → `Locomotion` [StandardBlend] crossfade=0.40s
  - Transition `To Falling` → `Fall Loop` [StandardBlend] crossfade=0.40s
  - Transition `To Falling` → `Jump` [StandardBlend] crossfade=0.15s
  - Transition `To Land` → `Land` [StandardBlend] crossfade=0.10s

## References

Hard refs out (13):
- `/Game/Art/Characters/MetaHumans/Cha_BaseBody_WorldNpc_Male_Asian_01/Body/SKM_World_Npc_Male_Asian_BodyMesh` [asset]
- `/Game/Art/Characters/MetaHumans/Common/Female/Medium/NormalWeight/Body/metahuman_base_skel` [asset]
- `/Game/Blueprints/AI/MassAI/Anims/Unarmed/BS_Idle_Walk_Run` [asset]
- `/Game/Blueprints/AI/MassAI/Anims/Unarmed/MM_Fall_Loop` [asset]
- `/Game/Blueprints/AI/MassAI/Anims/Unarmed/MM_Idle` [asset]
- `/Game/Blueprints/AI/MassAI/Anims/Unarmed/MM_Jump` [asset]
- `/Game/Blueprints/AI/MassAI/Anims/Unarmed/MM_Land` [asset]
- `/Game/Blueprints/AI/MassAI/Rigs/CR_Metahuman_FootIK` [asset]
- `/Script/AnimGraph` [asset]
- `/Script/AnimGraphRuntime` [asset]
- `/Script/ControlRig` [asset]
- `/Script/ControlRigDeveloper` [asset]
- `/Script/Engine.AnimInstance` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `AnimBlueprint`
- Custom metadata: _none_

