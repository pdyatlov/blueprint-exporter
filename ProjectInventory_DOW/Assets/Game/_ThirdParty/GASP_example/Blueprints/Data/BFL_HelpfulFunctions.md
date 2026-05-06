# BFL_HelpfulFunctions

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/Data/BFL_HelpfulFunctions.BFL_HelpfulFunctions` |
| Asset name | `BFL_HelpfulFunctions` |
| Subclass | `Blueprint` |
| Blueprint type | `FunctionLibrary` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `BlueprintFunctionLibrary` (`/Script/Engine.BlueprintFunctionLibrary`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (0)

_None._

## Functions (10)

### `AddToStringHistoryArray`

- Access: `Public`
- Flags: —
- Inputs: `(TArray<string>& InOutValues [ref], string NewValue, int MaxHistoryCount, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 5

### `DebugDraw_BoolStates`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector>& Location [ref], struct<Rotator>& Rotation [ref], struct<Vector> Offset, TArray<string> BoolNames, TArray<bool> BoolValues, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables (5): `TextLoc`, `TextRot`, `Name`, `State`, `LineLoc`
- Nodes: 43
- Category: `Helpful Debug Draws`

### `DebugDraw_MultiLineGraph`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector>& Location [ref], struct<Rotator>& Rotation [ref], struct<Vector> Offset, real<float> X Length, real<float> Y Length, struct<Vector2D> GraphSize, struct<Vector2D> MinValue, struct<Vector2D> MaxValue, string Xaxis Label, string Yaxis Label, TArray<struct<S_DebugGraphLineProperties>> Lines, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables (5): `GraphLoc`, `GraphRot`, `LineColors`, `LineNames`, `Drawer`
- Nodes: 68
- Category: `Helpful Debug Draws`

### `DebugDraw_ObjectNameArray`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Location, struct<Rotator> Rotation, struct<Vector> Offset, string ArrayLabel, TArray<object<Object>> Objects, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables (3): `TextLoc`, `TextRot`, `String`
- Nodes: 25
- Category: `Helpful Debug Draws`

### `DebugDraw_StringArray`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Location, struct<Rotator> Rotation, struct<Vector> Offset, string Label, string Prefix, TArray<string> Strings, string Highlighted String, string Highlight, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables (5): `TextLoc`, `TextRot`, `String`, `HighlightedIndex`, `HasLabel`
- Nodes: 39
- Category: `Helpful Debug Draws`

### `DrawDebugAngleThresholds`

- Access: `Public`
- Flags: —
- Inputs: `(struct<Vector> Center, struct<Vector> Offset, struct<Rotator> InRotation, TArray<real<double>> YawAngles, real<double> StartRadius, real<double> EndRadius, struct<LinearColor> Color, real<float> Duration, real<float> Thickness = 1.000000, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables (1): `Origin`
- Nodes: 18
- Category: `Helpful Debug Draws`

### `DrawDebugArrowWithCircle`

- Access: `Public`
- Flags: —
- Inputs: `(bool DrawCircle, bool DrawAxis, bool DrawArrow, bool DrawString, string String, struct<Vector> StringOffset, struct<Vector> Center, struct<Vector> Direction, struct<Vector> Offset, real<double> Radius = 0.000000, real<double> Length = 50.000000, real<double> Size = 50.000000, int Segments = 100, struct<LinearColor> Color, real<double> Duration, real<double> Thickness = 1.000000, object<Object> __WorldContext)`
- Outputs: `()`
- Local variables (2): `Origin`, `ArrowEnd`
- Nodes: 47
- Category: `HelpfulDebugDraws`

### `GetObjectNames`

- Access: `Public`
- Flags: —
- Inputs: `(TArray<object<Object>> Objects, object<Object> __WorldContext)`
- Outputs: `(TArray<string> ReturnValue)`
- Local variables (1): `Names`
- Nodes: 7

### `GetPawnClassWithCVAR`

- Access: `Public`
- Flags: —
- Inputs: `(TArray<class<Class>> PawnClasses, class<Class> DefaultPawnClass, object<Object> __WorldContext)`
- Outputs: `(class<Class> ReturnValue, class<Class> ReturnValue)`
- Local variables: _none_
- Nodes: 14

### `GetVisualOverrideWithCVAR`

- Access: `Public`
- Flags: —
- Inputs: `(TArray<class<Class>> VisualOverrides, object<Object> __WorldContext)`
- Outputs: `(class<Class> ReturnValue, class<Class> ReturnValue)`
- Local variables: _none_
- Nodes: 10

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

Hard refs out (4):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/GASP_example/Blueprints/Data/S_DebugGraphLineProperties` [asset]
- `/Script/DrawDebugLibrary` [asset]
- `/Script/Engine.BlueprintFunctionLibrary` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `FunctionLibrary`
- Subclass: `Blueprint`
- Custom metadata: _none_

