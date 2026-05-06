# BP_SimpleRocket

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/Dynamics/Props/SimpleRocket/BP_SimpleRocket.BP_SimpleRocket` |
| Asset name | `BP_SimpleRocket` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces (1):
  - `/Game/Standards/iDamagable.iDamagable_C`

## Variables (32)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Expired` | `bool` | `False` | `Live Variables` | — | — | InstanceEditable, Private |
| `Thrust` | `real<double>` | `0.000000` | `Live Variables` | — | — | InstanceEditable, Private |
| `Expired (S)` | `real<double>` | `0.000000` | `Live Variables` | — | — | InstanceEditable, Private |
| `Max Thrust` | `real<double>` | `12000.000000` | `Rocket Settings` | — | — | InstanceEditable |
| `Visualize Jet` | `bool` | `True` | `Debugging` | — | — | InstanceEditable |
| `Print Stats` | `bool` | `True` | `Debugging` | — | — | InstanceEditable |
| `Print Stats 3D` | `bool` | `False` | `Debugging` | — | — | InstanceEditable |
| `Multiply with Scale` | `bool` | `True` | `Rocket Settings` | — | — | InstanceEditable |
| `Thrust Curve` | `object<CurveFloat>` | `/Script/Engine.CurveFloat'/Game/Blueprints/Dynamics/Props/SimpleRocket/Curve_SimpleRocket_Force_B.Curve_SimpleRocket_Force_B'` | `Rocket Settings` | — | — | InstanceEditable |
| `Override Mass` | `bool` | `False` | `Rocket Settings` | — | — | InstanceEditable |
| `Mass Override` | `real<double>` | `0.000000` | `Rocket Settings` | — | — | InstanceEditable |
| `PrintID` | `name` | `SimpleRocket` | `Debugging` | — | — | InstanceEditable |
| `Burn Time` | `real<double>` | `15.000000` | `Rocket Settings` | — | — | InstanceEditable |
| `Owner Interface` | `interface<iGameActor_C>` | `None` | `Default` | — | — | InstanceEditable, Private |
| `Max Allowed Jets` | `real<double>` | `8.000000` | `Rocket Settings` | — | — | InstanceEditable, Private |
| `Health` | `real<double>` | `120.000000` | `Destruction` | — | — | InstanceEditable |
| `Explode At %` | `real<double>` | `10.000000` | `Destruction` | — | — | InstanceEditable, Private |
| `Explode After` | `real<double>` | `6.000000` | `Destruction` | — | — | InstanceEditable |
| `Explosive` | `bool` | `True` | `Destruction` | — | — | InstanceEditable |
| `Trigger Explode` | `bool` | `False` | `Live Variables` | — | — | InstanceEditable, Private |
| `Explosion Delay Min` | `real<double>` | `0.200000` | `Destruction` | — | — | InstanceEditable |
| `Explosion Delay Max` | `real<double>` | `0.000000` | `Destruction` | — | — | InstanceEditable |
| `Debris` | `class<Class>` | `None` | `Destruction` | — | — | InstanceEditable |
| `Force Impulse Multiplier` | `real<double>` | `800.000000` | `Destruction` | — | — | InstanceEditable |
| `Explosion Radius Multiplier` | `real<double>` | `10.000000` | `Destruction` | — | — | InstanceEditable |
| `Attached JetForces` | `TArray<object<BPC_JetForce_C>>` | — | `Components` | — | — | InstanceEditable, Private |
| `Start TIme` | `real<double>` | `0.000000` | `Live Variables` | — | — | InstanceEditable, Private |
| `Shake` | `class<Class>` | `/Script/CoreUObject.Class'/Script/Engine.CameraShakeBase'` | `Default` | — | — | InstanceEditable, Private |
| `Explosion Triggered` | `bool` | `False` | `Live Variables` | — | — | InstanceEditable, Private |
| `Fuel ` | `real<double>` | `100.000000` | `Live Variables` | — | — | InstanceEditable, Private |
| `Scale Explosion by Remaing Fuel` | `bool` | `True` | `Destruction` | — | — | InstanceEditable |
| `Jet Angle Sway` | `real<double>` | `1.000000` | `Rocket Settings` | — | — | InstanceEditable |

## Functions (8)

### `Attach Jet`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Attachment Point, struct<Vector> Attachment Angle)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 66
- Category: `Default`

### `Attach Jet (OLD)`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Attachment Point, struct<Vector> Attachment Angle)`
- Outputs: `()`
- Local variables (1): `Old Attached Jets`
- Nodes: 40
- Category: `Default`

### `Debug Explosive Radius`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 22

### `Debug Print`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 57
- Category: `Default`

### `Debug Print 3D`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (2): `PrintText`, `Jet Prints`
- Nodes: 82
- Category: `Default`

### `Expire`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 19
- Category: `Default`

### `Explode`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 40
- Category: `Default`

### `Release Pressure`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool Spent)`
- Local variables: _none_
- Nodes: 49
- Category: `Default`

## Macros (0)

_None._

## Components (1)

- `SM_Canister` — `StaticMeshComponent` @ socket `None`
  - `RadialForce` — `RadialForceComponent` @ socket `None`

## Class Default Object (2)

- `ActorLabel` (`FString`) = `BP_GasCanister`
- `PrimaryActorTick` (`FActorTickFunction`) = `(TickGroup=TG_DuringPhysics,bCanEverTick=True,bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (91 nodes)
- Construction script: `UserConstructionScript` (21 nodes)
- Additional graphs: _none_

## References

Hard refs out (12):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Engine/EngineMaterials/PhysMat_Metal` [asset]
- `/Game/Blueprints/Dynamics/Components/BPC_JetForce` [asset]
- `/Game/Blueprints/Dynamics/Props/BP_Debris` [asset]
- `/Game/Blueprints/Dynamics/Props/SimpleRocket/Curve_SimpleRocket_Force_B` [asset]
- `/Game/Blueprints/Dynamics/Shared/BP_Propulsion` [asset]
- `/Game/Blueprints/Dynamics/Utils/BP_Dynamics_Library` [asset]
- `/Game/Developers/erikspellerberg/Blueprints/BPC_MultiJet` [asset]
- `/Game/Standards/GameActor/iGameActor` [asset]
- `/Game/Standards/iDamagable` [asset]
- `/Script/DrawDebugLibrary` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

