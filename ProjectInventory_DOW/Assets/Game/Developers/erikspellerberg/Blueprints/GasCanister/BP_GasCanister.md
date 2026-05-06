# BP_GasCanister

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Developers/erikspellerberg/Blueprints/GasCanister/BP_GasCanister.BP_GasCanister` |
| Asset name | `BP_GasCanister` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces (1):
  - `/Game/Standards/iDamagable.iDamagable_C`

## Variables (27)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Gas Current` | `real<double>` | `500.000000` | `Physics Update` | — | — | InstanceEditable, Private |
| `Gas %` | `real<double>` | `0.000000` | `Physics Update` | — | — | InstanceEditable, Private |
| `Gas Flow Rate` | `real<double>` | `0.000000` | `Physics Update` | — | — | InstanceEditable, Private |
| `Gas Mass` | `real<double>` | `500.000000` | `Physics Update` | — | — | InstanceEditable, Private |
| `PSI` | `real<double>` | `200.000000` | `Physics Update` | — | — | InstanceEditable, Private |
| `Thrust` | `real<double>` | `430.000000` | `Physics Update` | — | — | InstanceEditable, Private |
| `Gas Weight` | `real<double>` | `0.800000` | `User Setup` | — | — | InstanceEditable |
| `Canister Weight` | `real<double>` | `0.000000` | `User Setup` | — | — | InstanceEditable |
| `Canister Pressure` | `real<double>` | `200.000000` | `User Setup` | — | — | InstanceEditable |
| `Thrust Multiplier` | `real<double>` | `50.000000` | `User Setup` | — | — | InstanceEditable |
| `Gas Flow Max` | `real<double>` | `430.000000` | `Setup` | — | — | InstanceEditable, Private |
| `Gas Capacity` | `real<double>` | `500.000000` | `Setup` | — | — | InstanceEditable, Private |
| `Gas Mass Initial` | `real<double>` | `500.000000` | `Setup` | — | — | InstanceEditable, Private |
| `Calculate Volume` | `bool` | `True` | `User Setup` | — | — | InstanceEditable |
| `Volume` | `real<double>` | `10000.000000` | `User Setup` | — | — | InstanceEditable |
| `Scale Force With Size` | `bool` | `False` | `User Setup` | — | — | InstanceEditable |
| `Initial Setup` | `bool` | `False` | `Setup` | — | — | InstanceEditable, Private |
| `Print Stats` | `bool` | `False` | `Debug` | — | — | InstanceEditable |
| `Print Stats 3D` | `bool` | `False` | `Debug` | — | — | InstanceEditable |
| `DebugSeconds` | `real<double>` | `0.250000` | `Debug` | — | — | InstanceEditable |
| `PSI Curve` | `object<CurveFloat>` | `None` | `User Setup` | — | — | InstanceEditable |
| `Hits to Explode` | `real<double>` | `100.000000` | `User Setup` | — | — | InstanceEditable |
| `Explode when Spent` | `bool` | `True` | `User Setup` | — | — | InstanceEditable |
| `Timer` | `real<double>` | `0.250000` | `Debug` | — | — | InstanceEditable, Private |
| `Pressure Drop` | `real<double>` | `0.000000` | `Physics Update` | — | — | InstanceEditable, Private |
| `Attached Jets` | `TArray<object<BP_Propulsion_C>>` | — | `Setup` | — | — | InstanceEditable, Private |
| `PrintID` | `name` | `None` | `Debug` | — | — | InstanceEditable |

## Functions (8)

### `Attach Jet`

- Access: `Public`
- Flags: —
- Inputs: `(struct<HitResult>& Hit [ref], real<double> Damage, struct<Vector> Direction, struct<Vector> Location)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 45

### `Debug Print`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 58

### `Debug Print 3D`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 88

### `Explode`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7

### `First Time Setup`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 46

### `Get Gas Weight`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 12

### `OLD: Calculate Thrust`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14

### `Release Pressure`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Gas %)`
- Local variables: _none_
- Nodes: 54

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`
  - `SM_Canister` — `StaticMeshComponent` @ socket `None`

## Class Default Object (2)

- `ActorLabel` (`FString`) = `BP_GasCanister`
- `PrimaryActorTick` (`FActorTickFunction`) = `(bCanEverTick=True,bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (40 nodes)
- Construction script: `UserConstructionScript` (8 nodes)
- Additional graphs: _none_

## References

Hard refs out (7):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Engine/EngineMaterials/PhysMat_Metal` [asset]
- `/Game/Blueprints/Dynamics/Shared/BP_Propulsion` [asset]
- `/Game/Blueprints/Dynamics/Utils/BP_Dynamics_Library` [asset]
- `/Game/Standards/iDamagable` [asset]
- `/Script/DrawDebugLibrary` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

