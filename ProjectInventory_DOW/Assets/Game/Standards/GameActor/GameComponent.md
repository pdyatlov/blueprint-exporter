# GameComponent

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Standards/GameActor/GameComponent.GameComponent` |
| Asset name | `GameComponent` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `ActorComponent` (`/Script/Engine.ActorComponent`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (24)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Owner` | `object<Actor>` | `None` | `CONSTRUCTION` | — | — | InstanceEditable, Private |
| `OwnerInterface` | `interface<iGameActor_C>` | `None` | `CONSTRUCTION` | — | — | InstanceEditable, Private |
| `R_Keyframes` | `struct<sFourBytes>` | `()` | `KEYFRAMES` | Replicated | `OnRep_R_Keyframes` | InstanceEditable, Private |
| `UpdateInterval_Sim` | `real<double>` | `0.000000` | `LOD` | — | — | InstanceEditable, Private |
| `UpdateInterval_Upscale` | `real<double>` | `0.000000` | `LOD` | — | — | InstanceEditable, Private |
| `UpdateBuildup_Sim` | `real<double>` | `0.000000` | `LOD` | — | — | InstanceEditable, Private |
| `UpdateBuildup_Upscale` | `real<double>` | `0.000000` | `LOD` | — | — | InstanceEditable, Private |
| `CurrentLOD_Sim` | `int` | `0` | `LOD` | — | — | InstanceEditable, Private |
| `CurrentLOD_Upscale` | `int` | `0` | `LOD` | — | — | InstanceEditable, Private |
| `GameActorType` | `byte<eGameActorType>` | `NewEnumerator1` | `SETUP` | — | — | InstanceEditable |
| `UpdateIntervals_SimNet` | `TArray<struct<Vector2D>>` | `((X=0.000000,Y=30.000000),(X=0.250000,Y=20.000000),(X=0.500000,Y=5.000000),(X=0.250000,Y=20.000000),(X=0.500000,Y=15.000000),(X=1.000000,Y=2.000000),(X=0.500000,Y=10.000000),(X=1.500000,Y=5.000000),(X=4.000000,Y=1.000000))` | `LOD` | — | — | InstanceEditable, ReadOnly, Private |
| `UpdateIntervals_Upscale` | `TArray<real<double>>` | `(0.000000,0.250000,1.000000,0.100000,0.500000,1.500000,0.150000,1.000000,2.000000)` | `LOD` | — | — | InstanceEditable, ReadOnly, Private |
| `LODThresholds` | `TArray<struct<Vector2D>>` | `((X=1000.000000,Y=2500.000000),(X=500.000000,Y=3000.000000),(X=1000.000000,Y=2500.000000))` | `LOD` | — | — | InstanceEditable, ReadOnly, Private |
| `LODDistance_Sim` | `real<double>` | `0.000000` | `LOD` | — | — | InstanceEditable, Private |
| `LODDistance_Upscale` | `real<double>` | `0.000000` | `LOD` | — | — | InstanceEditable, Private |
| `DistanceRef_Sim` | `int` | `0` | `LOD` | — | — | InstanceEditable, Private |
| `DistanceRef_Upscale` | `int` | `0` | `LOD` | — | — | InstanceEditable, Private |
| `CanBePlayerControlled` | `bool` | `False` | `SETUP` | — | — | InstanceEditable |
| `GameActorID` | `int` | `0` | `GAD` | — | — | InstanceEditable, Private |
| `IsDynamicallyCreated` | `bool` | `False` | `GAD` | — | — | InstanceEditable, Private |
| `TempFloat` | `real<double>` | `0.000000` | `TEMP` | — | — | InstanceEditable, Private |
| `UpdateBuildup_LOD` | `real<double>` | `0.000000` | `LOD` | — | — | InstanceEditable, Private |
| `DoUpdate_LOD` | `bool` | `False` | `LOD` | — | — | InstanceEditable, Private |
| `IsConstructed` | `bool` | `False` | `Default` | — | — | InstanceEditable, Private |

## Functions (6)

### `ComputeLOD_Sim`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool LODChange, bool LODChange)`
- Local variables: _none_
- Nodes: 34
- Category: `Default`

### `ComputeLOD_Upscale`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool LODChange, bool LODChange)`
- Local variables: _none_
- Nodes: 27
- Category: `Default`

### `OnRep_R_Keyframes`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 4

### `RECALL`

- Access: `Public`
- Flags: —
- Inputs: `(TArray<struct<sFourBytes>> StorageArray, int& DataIndex [ref], int& DataPacketCount [ref])`
- Outputs: `()`
- Local variables: _none_
- Nodes: 15
- Category: `Default`

### `SetGamaActorData`

- Access: `Public`
- Flags: —
- Inputs: `(int GameActorID, bool DynamicallyCreated)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5
- Category: `Default`

### `STORE`

- Access: `Public`
- Flags: —
- Inputs: `(TArray<struct<sGameActorHeader>> StorageHeaders, TArray<struct<sFourInts>> AdditonalStorageDatas, int CurrentStorageDataOffset)`
- Outputs: `(int NewStorageDataOffset)`
- Local variables: _none_
- Nodes: 27
- Category: `Default`

## Macros (4)

### `BuildupTimer`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9

### `ComputeNewLOD`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 36

### `DebugFloat`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

### `GetLodDataIndex`

- Access: `public`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 6

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (1)

- `PrimaryComponentTick` (`FActorComponentTickFunction`) = `(bCanEverTick=True)`

## Graphs

- Event graph: `EventGraph` (89 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (8):
- `/Engine/EditorBlueprintResources/ActorComponentMacros` [asset]
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/Standards/GameActor/Data/eGameActorType` [asset]
- `/Game/Standards/GameActor/Data/sFourBytes` [asset]
- `/Game/Standards/GameActor/Data/sFourInts` [asset]
- `/Game/Standards/GameActor/Data/sGameActorHeader` [asset]
- `/Game/Standards/GameActor/iGameActor` [asset]
- `/Script/Engine.ActorComponent` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

