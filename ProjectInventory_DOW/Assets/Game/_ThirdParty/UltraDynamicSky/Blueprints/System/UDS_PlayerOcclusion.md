# UDS_PlayerOcclusion

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion.UDS_PlayerOcclusion` |
| Asset name | `UDS_PlayerOcclusion` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ActorComponent` (`/Script/Engine.ActorComponent`, native, module `/Script/Engine`)
- Interfaces (1):
  - `/Script/Niagara.NiagaraParticleCallbackHandler`

## Variables (28)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Tick Delta Seconds` | `real<double>` | `0.000000` | `System` | — | — | InstanceEditable, Private |
| `Sample Location` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `System` | — | — | InstanceEditable, Private |
| `UDS` | `object<Actor>` | `None` | `System` | — | — | InstanceEditable, Private |
| `Trace Period Timer` | `real<double>` | `0.000000` | `Tracing Occlusion` | — | — | InstanceEditable, Private |
| `All Trace Offsets` | `TArray<struct<Vector>>` | — | `Tracing Occlusion` | — | — | InstanceEditable, Private |
| `X Axis Max` | `real<double>` | `0.000000` | `Tracing Occlusion` | — | — | InstanceEditable, Private |
| `Y Axis Max` | `real<double>` | `0.000000` | `Tracing Occlusion` | — | — | InstanceEditable, Private |
| `X Axis Min` | `real<double>` | `0.000000` | `Tracing Occlusion` | — | — | InstanceEditable, Private |
| `Y Axis Min` | `real<double>` | `0.000000` | `Tracing Occlusion` | — | — | InstanceEditable, Private |
| `Z Axis Max` | `real<double>` | `0.000000` | `Tracing Occlusion` | — | — | InstanceEditable, Private |
| `Trace Debug` | `byte<EDrawDebugTrace>` | `None` | `Tracing Occlusion` | — | — | InstanceEditable, Private |
| `Ignored Actors` | `TArray<object<Actor>>` | — | `Tracing Occlusion` | — | — | InstanceEditable, Private |
| `Target Occlusion A` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `Target Occlusion B` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `Old Occlusion A` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `Old Occlusion B` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `Default` | — | — | InstanceEditable, Private |
| `Started` | `bool` | `False` | `System` | — | — | InstanceEditable, Private |
| `Occlusion Volume Multiplier` | `real<double>` | `1.000000` | `Default` | — | — | InstanceEditable, Private |
| `Portal Components` | `TArray<object<UDS_Occlusion_Portal_C>>` | — | `Tracing Occlusion` | — | — | InstanceEditable, Private |
| `Distance Field System Active` | `bool` | `False` | `Distance Field` | — | — | InstanceEditable, Private |
| `DF Occlusion System Asset` | `softobject<NiagaraSystem>` | `/Game/_ThirdParty/UltraDynamicSky/Particles/DF_Occlusion_Test.DF_Occlusion_Test` | `Distance Field` | — | — | InstanceEditable, Private |
| `DF Occlusion System` | `object<NiagaraComponent>` | `None` | `Distance Field` | — | — | InstanceEditable, Private |
| `Waiting for DF Callback` | `bool` | `False` | `Distance Field` | — | — | InstanceEditable, Private |
| `Hard Update on Callback` | `bool` | `False` | `Distance Field` | — | — | InstanceEditable, Private |
| `Force Occluded` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Force Unoccluded` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |
| `Occlusion Update Period` | `real<double>` | `0.500000` | `Default` | — | — | InstanceEditable, Private |
| `Occlusion Trace Channel` | `byte<ETraceTypeQuery>` | `TraceTypeQuery1` | `Default` | — | — | InstanceEditable, Private |

## Functions (26)

### `Apply Force Occlusion`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 13

### `Apply Portal Components`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (3): `Current Portal`, `Portal Distance Mask`, `Portal Direction`
- Nodes: 105

### `Calculate Static Values`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (5): `Facing Direction`, `Trace Direction`, `Trace Max Distance`, `Vertical Steps`, `Horizontal Steps`
- Nodes: 97

### `Check For Portal Components`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 17
- Category: `Default`
- Description: Finds occlusion portals nearby the sample location

### `Current Directional Occlusion`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> X+, real<double> Y+, real<double> X-, real<double> Y-)`
- Local variables: _none_
- Nodes: 13

### `Current Facing Direction`

- Access: `Protected`
- Flags: —
- Inputs: `(int Step, int Horizontal Steps)`
- Outputs: `(struct<Vector> ReturnValue)`
- Local variables: _none_
- Nodes: 7
- Category: `Default`

### `Current Global Occlusion`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 10

### `Current Trace Direction`

- Access: `Protected`
- Flags: —
- Inputs: `(struct<Vector> Facing Direction, int Vertical Step, int Vertical Steps, int Horizontal Steps)`
- Outputs: `(struct<Vector> ReturnValue)`
- Local variables: _none_
- Nodes: 19
- Category: `Default`

### `Current Upward Occlusion`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 9

### `Custom Global Occlusion Sample`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Location)`
- Outputs: `(real<double> Global Occlusion, real<double> Global Occlusion)`
- Local variables (2): `Total Occlusion`, `Ray Hits`
- Nodes: 32
- Category: `Default`

### `Delayed Startup`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 20

### `Get Sample Location`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 12
- Category: `Default`
- Description: Gets the location which occlusion traces will start from

### `Hard Occlusion Update`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14

### `Player Controller Pawn Changed`

- Access: `Protected`
- Flags: —
- Inputs: `(object<Pawn> OldPawn, object<Pawn> NewPawn)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

### `Start GPU Query`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 8

### `Start Up GPU Distance Field System`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 35
- Category: `Default`

### `Target Directional Occlusion`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> X+, real<double> Y+, real<double> X-, real<double> Y-)`
- Local variables: _none_
- Nodes: 6

### `Target Global Occlusion`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 4

### `Target Upward Occlusion`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Out)`
- Local variables: _none_
- Nodes: 4

### `Test Point for Occlusion Volumes`

- Access: `Protected`
- Flags: —
- Inputs: `(struct<Vector> Location)`
- Outputs: `(real<double> Final Multiplier)`
- Local variables (1): `Multiplier`
- Nodes: 22
- Category: `Default`

### `Tick Function`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Delta Seconds)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 20

### `Trace Scenery for Target Occlusion`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (4): `Hit Vector Positive Total`, `Hit Count`, `Current Offset`, `Hit Vector Negative Total`
- Nodes: 73

### `Update Ignored Actors`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15

### `Update Occlusion Volume Multiplier`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4

### `Update Target Occlusion`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11

### `Update Targets with Just Occlusion Volumes`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `EventGraph` (40 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (10):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_Occlusion_Mode` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Enum/UDS_OcclusionSamplingLocation` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Occlusion/UDS_Occlusion_Portal` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Occlusion/UDS_Occlusion_Volume` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDS_PlayerOcclusion_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Particles/DF_Occlusion_Test` [asset]
- `/Script/Engine.ActorComponent` [native]
- `/Script/Niagara` [asset]
- `/Script/PhysicsCore` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

