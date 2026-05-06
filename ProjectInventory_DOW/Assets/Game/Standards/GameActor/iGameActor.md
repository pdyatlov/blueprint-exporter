# iGameActor

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Standards/GameActor/iGameActor.iGameActor` |
| Asset name | `iGameActor` |
| Subclass | `Blueprint` |
| Blueprint type | `Interface` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Interface` (`/Script/CoreUObject.Interface`, native, module `/Script/CoreUObject`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (8)

### `GetLocallyOwned`

- Access: `Public`
- Flags: —
- Inputs: `()`
- Outputs: `(bool IsLocallyOwned)`
- Local variables: _none_
- Nodes: 2

### `OnKeyframesChanged`

- Access: `Public`
- Flags: —
- Inputs: `(struct<sFourBytes> Keyframes)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1

### `OnSimulationLODChange`

- Access: `Public`
- Flags: —
- Inputs: `(int LOD)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1

### `OnUpscaleLODChange`

- Access: `Public`
- Flags: —
- Inputs: `(int LOD)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1

### `RECALL`

- Access: `Public`
- Flags: —
- Inputs: `(TArray<struct<sFourBytes>>& StorageData [ref], int DataIndex, int DataCount)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1

### `SimaltionTick`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Delta, int LOD)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1

### `STORE`

- Access: `Public`
- Flags: —
- Inputs: `(TArray<struct<sFourInts>> StorageData)`
- Outputs: `(byte NumberOfDataAdded)`
- Local variables: _none_
- Nodes: 2
- Description: Up to 255 additonal datas supported

### `UpscaleTick`

- Access: `Public`
- Flags: —
- Inputs: `(real<double> Delta, int LOD)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 1

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (0)

_No authored overrides on inherited properties._

## Graphs

- Event graph: `` (0 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (3):
- `/Game/Standards/GameActor/Data/sFourBytes` [asset]
- `/Game/Standards/GameActor/Data/sFourInts` [asset]
- `/Script/CoreUObject.Interface` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Interface`
- Subclass: `Blueprint`
- Custom metadata: _none_

