# BP_Dynamics_Library

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/Dynamics/Utils/BP_Dynamics_Library.BP_Dynamics_Library` |
| Asset name | `BP_Dynamics_Library` |
| Subclass | `Blueprint` |
| Blueprint type | `FunctionLibrary` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `BlueprintFunctionLibrary` (`/Script/Engine.BlueprintFunctionLibrary`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (3)

### `Apply Force from UDW Wind`

- Access: `Public`
- Flags: —
- Inputs: `(object<PrimitiveComponent> Target, real<double> Force Multiplier = 100.000000, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7

### `Damage to Impulse`

- Access: `Public`
- Flags: —
- Inputs: `(object<PrimitiveComponent> Target, real<double> Damage, struct<Vector> Direction, struct<Vector> Impact, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14
- Category: `Default`

### `Mass to RadialForce`

- Access: `Public`
- Flags: —
- Inputs: `(object<RadialForceComponent>& Radial Force [ref], object<PrimitiveComponent> Target, real<double> Radius Mult = 10.000000, real<double> Impulse Strength Mult = 100.000000, object<Object> __WorldContext)`
- Outputs: `(real<double> DamageRadius)`
- Local variables: _none_
- Nodes: 14

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

Hard refs out (2):
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Functions/UltraDynamicWeather_Functions` [asset]
- `/Script/Engine.BlueprintFunctionLibrary` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `FunctionLibrary`
- Subclass: `Blueprint`
- Custom metadata: _none_

