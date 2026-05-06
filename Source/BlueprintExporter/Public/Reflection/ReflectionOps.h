// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Curves/RichCurve.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Reflection/ReflectionTypes.h"
#include "ReflectionOps.generated.h"

// Forward decl. The full type lives in EdGraph/EdGraphSchema.h; we only
// reference it as `const FEdGraphPinType&` in UFUNCTION signatures
// (M28.2.1's AddMemberVariableDeterministic), which UHT resolves
// transitively. Mirrors BlueprintEditorLibrary.h's declaration pattern.
struct FEdGraphPinType;

// M28.5.1 — AddEnvQueryOption takes a `UEnvQuery*` parameter. Full type
// lives in EnvironmentQuery/EnvQuery.h (AIModule, already a private dep via
// BlueprintExporter.Build.cs). UHT needs the forward declaration to resolve
// the UCLASS reference in the generated code; the .cpp includes the full
// header for the actual mutations.
class UEnvQuery;

// M28.4.1 — SetCurveFloatKeys takes a `UCurveFloat*` parameter plus a
// TArray<FRichCurveKey>. UCurveFloat lives in Curves/CurveFloat.h (Engine,
// already a public dep); the .cpp includes the full header. FRichCurveKey
// is a USTRUCT whose definition UHT needs to see inline to emit the TArray
// marshalling, so RichCurve.h is included at the top of this header.
class UCurveFloat;

// M28.4.2 — CreateDataAssetInstanceDeterministic takes a `UClass*` naming
// the concrete UDataAsset subclass to instantiate. UDataAsset lives in
// Engine/DataAsset.h (Engine, already a public dep); the .cpp includes the
// full header for the IsChildOf / abstract-class checks.
class UDataAsset;

// M28.4.3 — the UDS ops take `UUserDefinedStruct*` parameters. Full type
// lives in StructUtils/UserDefinedStruct.h (CoreUObject in UE 5.5+); the
// .cpp includes the full header for FStructureEditorUtils calls + the
// direct VariablesDescriptions walk on UUserDefinedStructEditorData.
class UUserDefinedStruct;

/**
 * Static UFUNCTION library exposing native FProperty walks to Python.
 *
 * Rationale: UE's Python binding generator enforces CPF_Protected and other
 * access flags at the Python layer, which blocks otherwise-legitimate
 * editor automation (StateTree.EditorData, Blueprint.ParentClass, etc.).
 * This library operates on FProperty / UObject directly in native C++ land
 * so those Python-specific flags don't apply, then surfaces each op as a
 * BlueprintCallable UFUNCTION that Python can invoke as
 * `unreal.BpxReflectionOps.get_property_value(...)`.
 *
 * Designed to be small and stable. Every write op returns an
 * `FBpxReflectionResult` with before / after / error data so Python callers
 * don't need to parse log output.
 */
UCLASS()
class BLUEPRINTEXPORTER_API UBpxReflectionOps : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Read a property value by path. Returns the value as ExportText
	 * (same format as FProperty::ExportTextItem_Direct produces).
	 *
	 * @param Root The starting UObject.
	 * @param Path Sequence of property names. Array elements are addressed
	 *             with "[N]" notation, e.g. `["SensesConfig", "[0]", "SightRadius"]`.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult GetPropertyValue(UObject* Root, const TArray<FString>& Path);

	/**
	 * Write a property value by path. Uses FProperty::ImportText_Direct to
	 * coerce ImportTextValue into the property's native type.
	 *
	 * Idempotent: if the before-value already matches ImportTextValue via
	 * string equality, bSkipped is true and no write happens.
	 *
	 * Does NOT call SavePackage — caller must invoke CompileAndSavePackage
	 * after a batch of edits to persist.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult SetPropertyValue(UObject* Root, const TArray<FString>& Path, const FString& ImportTextValue);

	/**
	 * Walk Outer chain or named subobjects to find a UObject by short name.
	 * Useful for reaching editor-only subobjects Python can't load directly
	 * (e.g., UStateTreeEditorData owned by a UStateTree).
	 *
	 * Resolution order: outer-walk (Outer / GetTypedOuter) then recursive
	 * subobject traversal via GetObjectsWithOuter.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static UObject* FindSubobject(UObject* Root, FName SubobjectName);

	/**
	 * Get length of an array property addressed by Path. Returns -1 on error
	 * (which is also a valid FBpxReflectionResult::ErrorMessage condition);
	 * callers should prefer the variant below that returns a full result.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static int32 GetArrayLength(UObject* Root, const TArray<FString>& Path);

	/**
	 * Compile a Blueprint (if Target is one) and save its package.
	 * Refuses to save on BS_Error — if the compile fails, the on-disk
	 * asset is left untouched rather than written in a broken state.
	 *
	 * @return True only if compile succeeded AND package saved. False means
	 *         the on-disk asset is unchanged and an error was logged.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static bool CompileAndSavePackage(UObject* Target);

	// --- M23.1 mutation primitives ---

	/**
	 * Append a default-constructed element to an array property.
	 * Works for any array type (struct, object-ref, int, etc.).
	 * Caller then uses SetPropertyValue / SetObjectPropertyValue /
	 * SetInstancedStructType etc. on path + "[new_index]" + sub-fields
	 * to populate the element.
	 *
	 * @return Index of the newly-added element, or -1 on error.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static int32 ArrayAppendNewElement(UObject* Root, const TArray<FString>& Path);

	/**
	 * Remove the element at `Index` from an array property. Shifts subsequent
	 * elements down (does not swap-remove).
	 *
	 * Returns a result with BeforeText = previous array length, AfterText =
	 * new array length. bSuccess=false with an error on OOB or wrong type.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult ArrayRemoveAt(UObject* Root, const TArray<FString>& Path, int32 Index);

	/**
	 * Set the type of an FInstancedStruct property, reallocating its backing
	 * storage to hold a default-constructed instance of NewType.
	 *
	 * @return bSuccess=true iff path resolves to an FInstancedStruct property
	 *         and InitializeAs(NewType) completes.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult SetInstancedStructType(UObject* Root, const TArray<FString>& Path, UScriptStruct* NewType);

	/**
	 * Create a new UObject of `Class` with `Outer` as its owner. Used for
	 * constructing editor-only subobject instances (e.g. a BP-wrapped
	 * StateTree condition instance that will be pointed-to by
	 * FStateTreeEditorNode::InstanceObject).
	 *
	 * BaseName optional — NAME_None auto-generates a unique name.
	 * Always created with RF_Public | RF_Transactional so the editor
	 * treats it as undoable.
	 *
	 * @return The newly-created UObject, or nullptr on error.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static UObject* NewSubobject(UObject* Outer, UClass* Class, FName BaseName);

	/**
	 * Set a UObject property's value directly (no ImportText round-trip).
	 * Correct choice for setting object references that point at other
	 * objects you've just created via NewSubobject.
	 *
	 * @return bSuccess=true iff path resolves to an FObjectProperty and
	 *         NewValue (or null) is compatible with the property's expected
	 *         class.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult SetObjectPropertyValue(UObject* Root, const TArray<FString>& Path, UObject* NewValue);

	/**
	 * Read a UObject property's value directly (no ExportText parsing).
	 * Returns nullptr both on error and on "property holds null" — check
	 * a GetPropertyValue result if you need to distinguish.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static UObject* GetObjectPropertyValue(UObject* Root, const TArray<FString>& Path);

	// --- M26.1 graph-authoring primitives (interface-override passthrough) ---

	/**
	 * Create an override function graph for an interface function on the
	 * target Blueprint. Scoped to the interface-override case — caller
	 * passes the resolved UInterface's generated class so we don't walk
	 * the parent hierarchy. The new graph is populated with default
	 * UK2Node_FunctionEntry + UK2Node_FunctionResult by
	 * FBlueprintEditorUtils::AddFunctionGraph; we then overwrite those
	 * two nodes' NodeGuids with md5-seeded values so the post-op asset is
	 * byte-deterministic across re-generation — the golden BugHunt fixture
	 * strategy depends on this.
	 *
	 * Idempotent: returns bSuccess=true, bSkipped=true if a graph with
	 * FunctionName already exists on Blueprint->FunctionGraphs (leaves
	 * the existing graph unchanged).
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult OverrideInterfaceFunction(
		UBlueprint* Blueprint,
		UClass* InterfaceClass,
		FName FunctionName);

	/**
	 * Resolve UK2Node_FunctionEntry + UK2Node_FunctionResult for a function
	 * graph on Blueprint by name. Returns their NodeGuids so callers can
	 * reference Entry / Return by GUID in subsequent ConnectPinsByName
	 * calls. ReturnGuid is intentionally zero for void / no-return
	 * signatures — not an error.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxGraphEndpoints FindGraphEndpoints(
		UBlueprint* Blueprint,
		FName FunctionName);

	/**
	 * Create a UK2Node_VariableGet bound to MemberName on the Blueprint's
	 * generated class (self context). Self-only by design for the M26.1
	 * passthrough case.
	 *
	 * Deterministic NodeGuid seeded from md5(bp_path + ":" + function_name
	 * + ":get:" + member_name). Idempotent on that seed: if a node with
	 * the same GUID already exists in the graph, returns it with
	 * bSkipped=true.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxNodeResult AddSelfMemberGetNode(
		UBlueprint* Blueprint,
		FName FunctionName,
		FName MemberName,
		FVector2D Position);

	/**
	 * Connect two pins by name. Looks up each pin's owning node by GUID
	 * in the named function graph, then invokes
	 * UEdGraphSchema_K2::TryCreateConnection. Idempotent: already-linked
	 * pins return bSkipped=true.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult ConnectPinsByName(
		UBlueprint* Blueprint,
		FName FunctionName,
		FGuid FromNodeGuid, FName FromPinName,
		FGuid ToNodeGuid,   FName ToPinName);

	/**
	 * Set a pin's literal DefaultValue. Uses UEdGraphSchema::TrySetDefaultValue
	 * so pin-type coercion + autogenerated-default updates happen per UE's
	 * own rules. Idempotent: setting to the current value returns
	 * bSkipped=true.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult SetNodePinLiteralDefault(
		UBlueprint* Blueprint,
		FName FunctionName,
		FGuid NodeGuid,
		FName PinName,
		const FString& LiteralText);

	/**
	 * Remove every node from a function graph except UK2Node_FunctionEntry
	 * and UK2Node_FunctionResult (plus their pin connections). Used by the
	 * M26.1.1 `implement_interface_function(force_rebind=True)` path to
	 * clear a pre-existing interface-override stub (or a prior authoring
	 * pass) before re-running the binding logic on the same graph.
	 *
	 * Entry / Return nodes are preserved so the caller can keep referring
	 * to them by their seeded GUIDs without having to re-create the graph.
	 *
	 * Idempotent: if the graph exists and already contains only Entry /
	 * Return, returns bSuccess=true with bSkipped=true and a zero removal
	 * count. Marks the blueprint structurally modified only when the graph
	 * actually changed. Caller is responsible for CompileAndSavePackage.
	 *
	 * AfterText reports the removed-node count as a decimal string for
	 * observability in op-result dicts.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult WipeFunctionGraphBody(
		UBlueprint* Blueprint,
		FName FunctionName);

	/**
	 * M28.2 — string-GUID form of ConnectPinsByName.
	 *
	 * Accepts FGuid values as hex strings (32-char uppercase, no dashes — the
	 * format DeepDumpRenderer emits for NodeGuids) so Python callers can wire
	 * nodes referenced out of `.deep.md` without constructing `unreal.Guid`
	 * instances. Internally parses both strings via `FGuid::Parse` and
	 * delegates to `ConnectPinsByName`.
	 *
	 * Motivating case: BP_Task_Peek's EventGraph has a `UK2Node_IfThenElse`
	 * Branch whose `else` pin is unconnected. The deep dump exposes both
	 * that Branch's NodeGuid and the existing `FinishTask` node's NodeGuid;
	 * this op lets the plan author wire them without round-tripping FGuids
	 * through the `unreal.*` surface.
	 *
	 * GraphName may refer to any of: a function graph
	 * (`Blueprint->FunctionGraphs`), an interface override graph
	 * (`ImplementedInterfaces[].Graphs`), OR an ubergraph
	 * (`UbergraphPages` — typically "EventGraph"). M28.2 extended
	 * `FindFunctionGraphByName` to walk all three so this op reaches each
	 * of them.
	 *
	 * Idempotent: already-linked pins return bSkipped=true.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult ConnectGraphPinsByGuidString(
		UBlueprint* Blueprint,
		FName GraphName,
		const FString& FromNodeGuidStr, FName FromPinName,
		const FString& ToNodeGuidStr,   FName ToPinName);

	// --- M28.2.1 structural BP edits — variable add ---

	/**
	 * Add a new member variable to a Blueprint with a deterministic VarGuid.
	 *
	 * Wraps `FBlueprintEditorUtils::AddMemberVariable` (which is exposed via
	 * `unreal.BlueprintEditorLibrary.add_member_variable` already) to fix a
	 * silent determinism trap: the engine call seeds `FBPVariableDescription
	 * ::VarGuid` via `FGuid::NewGuid()`, so every `add_bp_variable` call
	 * drifts the .uasset bytes — would trip M28.pre.3 soak gate immediately
	 * on the first round-2 comparison. This op overwrites VarGuid with
	 * `SeedGuidFromJoined(BlueprintPath + ":var:" + VarName)` post-add,
	 * mirroring the M26.1 NodeGuid / M26.1.2 PinId determinism pattern.
	 *
	 * `DefaultValue` is the literal default in the same string format
	 * `FBPVariableDescription::DefaultValue` accepts (e.g. "true" for bool,
	 * "42" for int, "(X=1.0,Y=2.0)" for vectors). Pass empty string for
	 * type-default (UE handles the rest).
	 *
	 * Idempotent: if a variable with `VarName` already exists on
	 * `Blueprint->NewVariables[]`, returns `bSuccess=true, bSkipped=true`
	 * without modifying the BP. Type compatibility is NOT verified on the
	 * skip path — callers can detect "wrong type already exists" by reading
	 * `BeforeText` ("var-exists:<VarName>") and inspecting the existing
	 * variable's type via the standard `unreal.*` reflection.
	 *
	 * Caller is responsible for `CompileAndSavePackage(BP)` after the add
	 * (and after any chained metadata setters like
	 * `unreal.BlueprintEditorLibrary.set_blueprint_variable_instance_editable`).
	 *
	 * Thread: game-thread only. The implementation calls into
	 * `FBlueprintEditorUtils` which is editor-only and not thread-safe.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult AddMemberVariableDeterministic(
		UBlueprint* Blueprint,
		FName VarName,
		const FEdGraphPinType& VarType,
		const FString& DefaultValue);

	// --- M28.2.2 structural BP edits — function graph add ---

	/**
	 * Add a new (blank) function graph to a Blueprint with deterministic
	 * GraphGuid + Entry/Return NodeGuids + pin IDs.
	 *
	 * Mirrors `UBlueprintEditorLibrary::AddFunctionGraph` but closes three
	 * silent determinism traps the engine path leaves open:
	 *   1. `UEdGraph::PostInitProperties` (EdGraph.cpp:147) assigns
	 *      `GraphGuid = FGuid::NewGuid()` — every call drifts the .uasset
	 *      bytes. Overwritten via
	 *      `SeedGuidFromJoined(BlueprintPath + ":func:" + FunctionName + ":graph")`.
	 *   2. `UK2Node_FunctionEntry::CreateNewGuid` + `UK2Node_FunctionResult
	 *      ::CreateNewGuid` each produce random NodeGuids. Overwritten via
	 *      the same seeding pattern used by M26.1 `OverrideInterfaceFunction`
	 *      so the Entry/Return pair is byte-stable across re-runs.
	 *   3. Pin IDs on Entry + Return default-created pins are
	 *      `FGuid::NewGuid()`-randomized. `SeedPinGuidsForNode` replays the
	 *      M26.1.2 recipe per pin so the package FNameMap / export table
	 *      lands identically round-to-round.
	 *
	 * Returns `FBpxGraphEndpoints` populated with Entry / Return NodeGuids so
	 * callers immediately chain M26.1 body-authoring ops (AddSelfMemberGetNode,
	 * ConnectPinsByName, SetNodePinLiteralDefault) by GUID. ReturnGuid is
	 * valid — a blank non-pure function always gets both nodes.
	 *
	 * `bIsPure` flips `UK2Node_FunctionEntry::MetaData.bIsPureFunc` after the
	 * graph is authored. Note: a pure function with no outputs WILL NOT
	 * compile cleanly; pair pure=true with a subsequent variable add / Return
	 * wire-up before calling CompileAndSavePackage.
	 *
	 * Idempotent: if a function graph named `FunctionName` already exists on
	 * `Blueprint->FunctionGraphs` / `ImplementedInterfaces[].Graphs` /
	 * `UbergraphPages`, returns `bSuccess=true, bSkipped=true` with the
	 * existing graph's Entry/Return GUIDs so chained ops still work.
	 *
	 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.
	 *
	 * Thread: game-thread only. `FBlueprintEditorUtils::CreateNewGraph` +
	 * `AddFunctionGraph` are editor-only and not thread-safe.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxGraphEndpoints AddFunctionGraphDeterministic(
		UBlueprint* Blueprint,
		FName FunctionName,
		bool bIsPure);

	// --- M28.2.3 structural BP edits — SCS component add ---

	/**
	 * Add a new component to a Blueprint's SimpleConstructionScript with a
	 * deterministic USCS_Node::VariableGuid.
	 *
	 * Wraps `USimpleConstructionScript::CreateNode` (Engine module, already
	 * linked — no new module dep) to close a silent determinism trap:
	 * `CreateNodeImpl` (SimpleConstructionScript.cpp:1375) assigns
	 * `NewNode->VariableGuid = FGuid::NewGuid()`. `USCS_Node::ValidateGuid`
	 * only fires its name-hash seed path when `!VariableGuid.IsValid()` —
	 * since `CreateNodeImpl` just assigned a fresh GUID, that path is never
	 * taken for freshly-created nodes. Every `add_component_to_scs` call
	 * drifts the .uasset bytes without this override. Post-create we
	 * overwrite `VariableGuid` with
	 * `SeedGuidFromJoined(BlueprintPath + ":scs:" + ComponentName)`,
	 * mirroring the M28.2.1 VarGuid / M28.2.2 GraphGuid determinism recipe.
	 *
	 * Attachment: pass NAME_None (or an empty FName) for `ParentComponentName`
	 * to add at SCS root. Otherwise we look up `ParentComponentName` via
	 * `SCS->FindSCSNode` and attach via `USCS_Node::AddChildNode`. Parenting
	 * to native (inherited-class-CDO) components isn't supported — the SCS
	 * only tracks authored nodes, so a non-SCS parent returns a structured
	 * error. This mirrors the editor's "Add Child Component" UX for SCS-only
	 * parenting and keeps the op scope narrow.
	 *
	 * Idempotent: if `SCS->FindSCSNode(ComponentName)` finds an existing node
	 * with the same `ComponentClass`, returns `bSuccess=true, bSkipped=true`
	 * without touching the asset. Name-with-different-class collision is a
	 * structured error. Requested-name-collides-with-inherited is also a
	 * structured error (engine's `GenerateNewComponentName` would silently
	 * append a counter suffix; rejecting up-front keeps plan replay crisp).
	 *
	 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.
	 *
	 * Thread: game-thread only. `FBlueprintEditorUtils::Mark…StructurallyModified`
	 * and `USimpleConstructionScript::CreateNode` are editor-only and not
	 * thread-safe.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult AddComponentToSCSDeterministic(
		UBlueprint* Blueprint,
		UClass* ComponentClass,
		FName ComponentName,
		FName ParentComponentName);

	// --- M28.2.4 structural BP edits — interface attach ---

	/**
	 * Attach an interface implementation to a Blueprint, seeding GraphGuid +
	 * Entry/Return NodeGuids + pin IDs on every generated override graph so
	 * the post-op .uasset bytes are byte-stable round-to-round.
	 *
	 * Wraps `FBlueprintEditorUtils::ImplementNewInterface` (Kismet2 module,
	 * already linked) to close three silent determinism traps identical to
	 * M28.2.2's function-graph add — `CreateNewGraph` allocates each override
	 * graph via `NewObject<UEdGraph>` so `UEdGraph::PostInitProperties`
	 * (EdGraph.cpp:147) assigns `GraphGuid = FGuid::NewGuid()`; the Entry
	 * (and Return, when the signature has out-params) K2Node_* nodes added
	 * by `CreateFunctionGraphTerminators` get random NodeGuids; their
	 * default-created pins get random PinIds. Without overriding all three,
	 * M28.pre.3 soak tripsround 2. Post-attach we overwrite each graph's
	 * `GraphGuid` via `SeedGuidFromJoined(<bp>:iface_graph:<iface_path>:<fn>)`
	 * and each Entry/Return node's NodeGuid + pin IDs via the M26.1.2 recipe.
	 * `NewGraph->InterfaceGuid` (distinct from GraphGuid — comes from
	 * `FindInterfaceFunctionGuid` against the source interface) is already
	 * deterministic; no override needed.
	 *
	 * Idempotent: if `Blueprint->ImplementedInterfaces[]` already lists
	 * `InterfaceClass`, returns `bSuccess=true, bSkipped=true` without
	 * touching the asset. The engine's `ImplementNewInterface` does its own
	 * "already implemented" check with a UI toast; we short-circuit earlier
	 * so plan replay doesn't surface a spurious notification.
	 *
	 * Does NOT call `MarkBlueprintAsStructurallyModified` a second time —
	 * `ImplementNewInterface` marks it internally on the success path. Per
	 * the M26.1.2 lesson, double-marking can re-enter structural-modified
	 * listeners and invalidate our just-seeded GUIDs before the subsequent
	 * compile + save.
	 *
	 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.
	 *
	 * Thread: game-thread only. `FBlueprintEditorUtils::ImplementNewInterface`
	 * is editor-only and not thread-safe.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult AddInterfaceByPath(
		UBlueprint* Blueprint,
		UClass* InterfaceClass);

	// --- M28.3.1 node-level graph authoring — Branch + graph-level pin default ---

	/**
	 * Spawn a `UK2Node_IfThenElse` (Branch node) into a named K2 graph with a
	 * deterministic NodeGuid + pin IDs.
	 *
	 * Simplest of the M28.3 node-spawn family — Branch has zero configuration
	 * surface (default pins handle exec/condition/then/else), so the op focuses
	 * on the shared machinery: walk all three graph families via
	 * `FindFunctionGraphByName`, bypass `FGraphNodeCreator` for a deterministic
	 * `FName` on `NewObject`, overwrite `NodeGuid` with
	 * `SeedGuidFromJoined(<bp>:graph:<g>:branch:<x>,<y>)`, seed pin IDs via the
	 * M26.1.2 `SeedPinGuidsForNode` recipe.
	 *
	 * `GraphName` may refer to any of: a function graph
	 * (`Blueprint->FunctionGraphs`), an interface override graph
	 * (`ImplementedInterfaces[].Graphs`), or an ubergraph
	 * (`UbergraphPages` — typically "EventGraph"). Same resolution order as
	 * `ConnectGraphPinsByGuidString` (M28.3-narrow).
	 *
	 * Idempotent on the seeded NodeGuid: if a node with the seeded GUID already
	 * exists in the graph (i.e. `AddBranchNode` was called with identical
	 * GraphName + Position), returns `bSuccess=true, bSkipped=true`. Position is
	 * included in the seed so two distinct Branches in the same graph get
	 * distinct GUIDs.
	 *
	 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.
	 *
	 * Thread: game-thread only.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxNodeResult AddBranchNode(
		UBlueprint* Blueprint,
		FName GraphName,
		FVector2D Position);

	/**
	 * Set a pin's literal `DefaultValue` on any node in any K2 graph
	 * (function / interface-override / ubergraph). Sibling of M26.1's
	 * `SetNodePinLiteralDefault` but keyed by `GraphName` (routes through
	 * `FindFunctionGraphByName` to reach all three graph families) and accepts
	 * `NodeGuid` as a string (32-char hex or `{8-4-4-4-12}`), matching the
	 * shape of `ConnectGraphPinsByGuidString`.
	 *
	 * Motivating case: newly-spawned nodes from M28.3.1+ return their runtime
	 * `NodeGuid` as a hex string in the op result; plan authors chain
	 * `set_graph_pin_default` using that string without round-tripping through
	 * the `unreal.Guid` surface.
	 *
	 * Kept separate from M26.1 `SetNodePinLiteralDefault` (which is keyed by
	 * function name + FGuid) to preserve M26.1 callers' semantics unchanged —
	 * same coexistence pattern as `ConnectPinsByName` (M26.1) +
	 * `ConnectGraphPinsByGuidString` (M28.3-narrow).
	 *
	 * Uses `UEdGraphSchema::TrySetDefaultValue` so pin-type coercion +
	 * autogenerated-default updates follow UE's own rules. Idempotent: setting
	 * to the current value returns `bSkipped=true`.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult SetGraphPinLiteralDefault(
		UBlueprint* Blueprint,
		FName GraphName,
		const FString& NodeGuidStr,
		FName PinName,
		const FString& LiteralText);

	// --- M28.3.2 node-level graph authoring — FunctionReference / VariableReference ---

	/**
	 * Spawn a `UK2Node_CallFunction` node into a named K2 graph with deterministic
	 * NodeGuid + pin IDs. Sibling of `AddBranchNode` shape; the delta is the
	 * `FMemberReference` configuration step before `AllocateDefaultPins` — the
	 * CallFunction's pins are signature-derived, so the reference MUST be set
	 * prior to default-pin allocation for the correct pin set to materialise.
	 *
	 * `TargetClass == nullptr` routes to `FunctionReference.SetSelfMember(MemberName)`
	 * — the member must resolve on the Blueprint's `GeneratedClass` (or an ancestor)
	 * at compile time. `TargetClass != nullptr` routes to
	 * `FunctionReference.SetExternalMember(MemberName, TargetClass)` — the member
	 * must resolve on `TargetClass` (native `/Script/...` or BP-generated `*_C`).
	 *
	 * Idempotent on seeded NodeGuid (seed key includes member name + position so
	 * two calls to the same function at different positions get distinct GUIDs).
	 *
	 * Thread: game-thread only.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxNodeResult AddCallFunctionNode(
		UBlueprint* Blueprint,
		FName GraphName,
		FName MemberName,
		UClass* TargetClass,
		FVector2D Position);

	/**
	 * Spawn a `UK2Node_VariableGet` node into a named K2 graph with deterministic
	 * NodeGuid + pin IDs. Generalises M26.1's `AddSelfMemberGetNode` to any
	 * graph family (function / interface override / ubergraph) and any
	 * variable context (self or external class).
	 *
	 * `TargetClass == nullptr` routes to `VariableReference.SetSelfMember(MemberName)`;
	 * non-null routes to `SetExternalMember(MemberName, TargetClass)`. Reference
	 * is set before `AllocateDefaultPins` so the typed "value" output pin
	 * materialises with the correct PinType.
	 *
	 * Idempotent on seeded NodeGuid.
	 *
	 * Thread: game-thread only.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxNodeResult AddVariableGetNode(
		UBlueprint* Blueprint,
		FName GraphName,
		FName MemberName,
		UClass* TargetClass,
		FVector2D Position);

	/**
	 * Spawn a `UK2Node_VariableSet` node into a named K2 graph with deterministic
	 * NodeGuid + pin IDs. Sibling of `AddVariableGetNode`; same self-vs-external
	 * resolution via `VariableReference.SetSelfMember` / `SetExternalMember`
	 * before `AllocateDefaultPins`. For Set the default pins are the `execute`
	 * input/output exec pair and a typed value input pin.
	 *
	 * Idempotent on seeded NodeGuid.
	 *
	 * Thread: game-thread only.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxNodeResult AddVariableSetNode(
		UBlueprint* Blueprint,
		FName GraphName,
		FName MemberName,
		UClass* TargetClass,
		FVector2D Position);

	// --- M28.3.3 node-level graph authoring — CustomEvent / ExecutionSequence / DynamicCast ---

	/**
	 * Spawn a `UK2Node_CustomEvent` node into an ubergraph with a deterministic
	 * NodeGuid + pin IDs. CustomEvent is the event-channel entry point that
	 * design.md's squad-director `AI.Order.*` channel rests on (item #1 + #4).
	 *
	 * Graph-type validation runs at op entry — `UEdGraphSchema::GetGraphType(G)
	 * == GT_Ubergraph`. Any other graph family (function / interface override /
	 * macro) returns a structured error rather than silently producing a node
	 * that would fail at compile time. Mirrors the engine's own
	 * `K2Node_Event::IsCompatibleWithGraph` check but surfaces it explicitly to
	 * the plan author.
	 *
	 * `CustomFunctionName` (inherited from `UK2Node_Event`) is set BEFORE
	 * `AllocateDefaultPins` so the generated delegate name + signature pins
	 * resolve correctly. Seed key includes the event name + position so two
	 * CustomEvents with the same name at different positions get distinct
	 * GUIDs (useful during incremental authoring before a redundant second is
	 * deleted).
	 *
	 * Default pins (from `UK2Node_Event::AllocateDefaultPins`): `OutputDelegate`
	 * (delegate out, used by `Bind Event`), `then` (exec out). CustomEvents
	 * that need parameters get them via subsequent UserDefinedPin-Add ops —
	 * out of M28.3.3 scope, deferred with the rest of M28.3.
	 *
	 * Idempotent on the seeded NodeGuid.
	 *
	 * Thread: game-thread only.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxNodeResult AddCustomEventNode(
		UBlueprint* Blueprint,
		FName GraphName,
		FName EventName,
		FVector2D Position);

	/**
	 * Spawn a `UK2Node_ExecutionSequence` node into a K2 graph with a
	 * deterministic NodeGuid + pin IDs. ExecutionSequence chains N `Then_N`
	 * exec outputs off a single `execute` input, firing them in order.
	 * Design.md driver: polish-pass sequencing (item #8 — hit reactions
	 * followed by ally-down reactions) and callout broadcasts (item #4).
	 *
	 * `NumOutputs` controls the final output-pin count. The engine's default
	 * `AllocateDefaultPins` produces `Then_0` + `Then_1`; we call
	 * `IK2Node_AddPinInterface::AddInputPin` (misleading name — it adds a new
	 * Then_N **output** pin, not an input) `NumOutputs - 2` times so the node
	 * lands with the requested shape. `NumOutputs < 2` is a structured error
	 * (UE's ExecutionSequence requires at least two outputs to justify its
	 * existence; one-output sequences should be authored as direct wires).
	 * `NumOutputs > 16` is also rejected as a sanity cap; expand if a real
	 * driver appears.
	 *
	 * `SeedPinGuidsForNode` fires AFTER the AddInputPin loop so every final
	 * pin (including the extended Then_2+) gets a deterministic PinId.
	 *
	 * Idempotent on seeded NodeGuid (seed includes NumOutputs + position so
	 * two calls with different output counts at the same position get distinct
	 * GUIDs).
	 *
	 * Thread: game-thread only.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxNodeResult AddExecutionSequenceNode(
		UBlueprint* Blueprint,
		FName GraphName,
		int32 NumOutputs,
		FVector2D Position);

	/**
	 * Spawn a `UK2Node_DynamicCast` node into a K2 graph with a deterministic
	 * NodeGuid + pin IDs. DynamicCast routes `ObjectToCast` input through the
	 * `CastSucceeded` / `CastFailed` exec outputs based on an IsA check
	 * against `TargetClass`, exposing the cast object as the typed `As<X>`
	 * pin. Design.md driver: utility scorer action resolution (item #2 —
	 * cast from generic `AActor*` target to specific archetype classes for
	 * per-archetype scoring hooks) and callouts (item #4 — cast ally ref to
	 * `BP_EnemyBase` to test faction before broadcasting the callout).
	 *
	 * `TargetType` (UPROPERTY `TSubclassOf<UObject>`) MUST be set before
	 * `AllocateDefaultPins` — the typed `As<TargetClass>` output pin's
	 * `PinCategory` / `PinSubCategoryObject` are derived from `TargetType`
	 * inside `UK2Node_DynamicCast::CreatePinsForCastNode`. Post-alloc sets
	 * would leave the output pin as a wildcard and break downstream wiring.
	 *
	 * `TargetClass == nullptr` is a structured error (impossible node shape).
	 * `PureState` stays at its `UseDefault` resolution (impure by default —
	 * three exec pins + bSuccess output). A `bIsPureCast` param could expose
	 * `UK2Node_DynamicCast::SetPurity`; deferred until a driver surfaces.
	 *
	 * Idempotent on seeded NodeGuid (seed includes `TargetClass` path +
	 * position so two casts to different classes at the same spot get distinct
	 * GUIDs).
	 *
	 * Thread: game-thread only.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxNodeResult AddDynamicCastNode(
		UBlueprint* Blueprint,
		FName GraphName,
		UClass* TargetClass,
		FVector2D Position);

	// --- M28.3.4 node-level graph authoring — LocalVariable add ---

	/**
	 * Append a local variable to a Blueprint function's K2Node_FunctionEntry
	 * `LocalVariables` array with a deterministic VarGuid.
	 *
	 * Different shape from the M28.3.1–.3 K2Node-spawn ops — this op does NOT
	 * create a new K2Node; it extends the `LocalVariables: TArray<FBPVariableDescription>`
	 * UPROPERTY already present on the function graph's existing
	 * `UK2Node_FunctionEntry`. Final planned slice of the M28.3 catalog, ships
	 * last (per M28.3.0 research) so the Entry-node machinery is fully
	 * exercised by the prior K2Node-spawn phases.
	 *
	 * Wraps `FBlueprintEditorUtils::AddLocalVariable` (UnrealEd module, already
	 * linked via M26.1). The engine helper seeds `FBPVariableDescription::VarGuid`
	 * via `FGuid::NewGuid()` at `BlueprintEditorUtils.cpp:5433`, so every call
	 * drifts the .uasset bytes and trips M28.pre.3 soak round 2 without the
	 * post-add override. We overwrite VarGuid via
	 * `SeedGuidFromJoined(BlueprintPath + ":func:" + FunctionName + ":localvar:" + VarName)`
	 * — function name included in the seed key (unlike M28.2.1's member-var
	 * seed) because local vars of the same name can legitimately coexist in
	 * different functions.
	 *
	 * `GraphName` may refer to a function graph (`Blueprint->FunctionGraphs`)
	 * or an interface-override graph (`ImplementedInterfaces[].Graphs`) —
	 * resolved via `FindFunctionGraphByName`. Ubergraphs do not have local
	 * variables (no `K2Node_FunctionEntry`); op returns a structured error if
	 * targeted at one.
	 *
	 * Idempotent: if a local variable with `VarName` already exists on the
	 * target function's `LocalVariables[]`, returns `bSuccess=true, bSkipped=true`
	 * without modifying the asset. Type compatibility is NOT verified on the
	 * skip path — same semantics as `AddMemberVariableDeterministic`.
	 *
	 * Does NOT call `MarkBlueprintAsStructurallyModified` a second time —
	 * `AddLocalVariable` marks internally on the success path. Per the M26.1.2
	 * lesson, double-marking re-enters structural-modified listeners and
	 * invalidates freshly-seeded GUIDs before the subsequent compile + save.
	 *
	 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.
	 *
	 * Thread: game-thread only. `FBlueprintEditorUtils::AddLocalVariable` is
	 * editor-only and not thread-safe.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult AddLocalVariableDeterministic(
		UBlueprint* Blueprint,
		FName FunctionName,
		FName VarName,
		const FEdGraphPinType& VarType,
		const FString& DefaultValue);

	// --- M28.11 typed function / custom-event parameter authoring ---

	/**
	 * Append a user-defined pin to a Blueprint function's `K2Node_FunctionEntry`,
	 * `K2Node_FunctionResult`, or to a `K2Node_CustomEvent` in an ubergraph,
	 * with a deterministic PinId. Wraps `K2Node_EditablePinBase::CreateUserDefinedPin`.
	 *
	 * Dispatch (`bDirectionIsOutput=true` means the pin's UE direction is
	 * EGPD_Output; `false` means EGPD_Input):
	 *   - If `FunctionName` resolves to a function graph (function graph or
	 *     interface-override graph) → operate on Entry / Result:
	 *       - `bDirectionIsOutput=true`  → target Entry node (Entry's outputs
	 *         are the function's inputs). Entry must already exist (auto-spawned
	 *         by `add_bp_function` / `add_bp_interface`).
	 *       - `bDirectionIsOutput=false` → target Result node (Result's inputs
	 *         are the function's outputs). Result auto-spawned with deterministic
	 *         NodeGuid + pin IDs if missing — pure-function authors who add an
	 *         output pin retroactively don't need a separate "spawn Result"
	 *         step. The auto-spawn seeds via
	 *         `<bp>:func:<fn>:result` (matches `AddFunctionGraphDeterministic`'s
	 *         seed key so byte-identity is preserved across the fresh-create-
	 *         then-add-output vs `add_bp_function(is_pure=False)` paths).
	 *   - Else → walk every `Blueprint->UbergraphPages` for a `K2Node_CustomEvent`
	 *     whose `CustomFunctionName == FunctionName`. CustomEvents only support
	 *     `bDirectionIsOutput=true` (event's outputs are the event-handler's
	 *     inputs); `bDirectionIsOutput=false` is a structured error.
	 *   - If neither path resolves the function/event → structured error.
	 *
	 * Idempotence: short-circuits on `target->UserDefinedPinExists(PinName)`
	 * (returns `bSuccess=true, bSkipped=true` without touching the existing
	 * pin's type or default). Type compatibility is NOT verified on the skip
	 * path — same semantics as `AddMemberVariableDeterministic`.
	 *
	 * Determinism: the new pin's `PinId` is reseeded post-create via
	 * `SeedGuidFromJoined(<bp>:<scope>:<fname>:userpin:<pname>:<dir>)` where
	 * `<scope>` is `entry` / `result` / `custom_event`. Without this, the
	 * fresh `FGuid::NewGuid()` from `UEdGraphPin::CreatePin` would drift the
	 * `.uasset` md5 every replay and trip M28.pre.3 soak round 2.
	 *
	 * `DefaultValue` (ImportText format — `"true"` for bool, `"42"` for int,
	 * `"(X=1.0,Y=2.0)"` for vectors) is applied via
	 * `target->ModifyUserDefinedPinDefaultValue` after the pin is created.
	 * Empty string = no default. Output pins on Result nodes don't accept
	 * defaults at the BP layer (Result outputs are wired-only at compile);
	 * the bridge silently ignores `DefaultValue` for Result-targeted calls
	 * to keep the Python op signature uniform.
	 *
	 * Calls `MarkBlueprintAsStructurallyModified` on the success path.
	 * `CreateUserDefinedPin` does NOT mark internally (verified against
	 * `K2Node_EditablePinBase.cpp:162-178` — engine UI callers mark via the
	 * BlueprintEditor panel, not the node itself), so we do it here.
	 *
	 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.
	 *
	 * Thread: game-thread only.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult AddFunctionUserDefinedPin(
		UBlueprint* Blueprint,
		FName FunctionName,
		FName PinName,
		const FEdGraphPinType& PinType,
		bool bDirectionIsOutput,
		const FString& DefaultValue);

	// --- M28.12 native virtual override authoring ---

	/**
	 * Author a function-graph override of a native virtual UFUNCTION inherited
	 * from `Blueprint->ParentClass` (or any ancestor in the parent chain).
	 * Different code path from `AddFunctionGraphDeterministic` (fresh void/void
	 * function) and `OverrideInterfaceFunction` (interface override) — this
	 * one targets `BlueprintImplementableEvent` / `BlueprintNativeEvent`
	 * UFUNCTIONs declared on the parent native class hierarchy.
	 *
	 * Driver: design.md MCP-only test against UE_DOW_Legacy
	 * (`UEnvQueryTest_BlueprintBase::ReceiveTestCondition` override). Pre-M28.12
	 * the only authoring surface was `add_bp_function`, which always created a
	 * fresh void/void function — wrong shape when the user wanted to override
	 * an inherited virtual.
	 *
	 * Resolution: `Blueprint->ParentClass->FindFunctionByName(FunctionName)`
	 * walks the inheritance chain (engine helper handles "this class or any
	 * ancestor"). The resolved `UFunction` must have the `FUNC_BlueprintEvent`
	 * flag (else the function isn't user-overridable from a BP — refusing
	 * here matches the BP editor's "Override Function" menu visibility).
	 *
	 * Engine call: `FBlueprintEditorUtils::AddFunctionGraph<UClass>(BP, NewGraph,
	 * bIsUserCreated=false, ParentClass)` — same template variant as
	 * `OverrideInterfaceFunction`, with `ParentClass` standing in for the
	 * interface class. UE walks the class for a matching-name UFUNCTION and
	 * uses its signature to build the Entry node's pins. `bIsUserCreated=false`
	 * because this is an override, not a new user function — the editor's
	 * function-list panel groups it under "Override Functions" via that flag.
	 *
	 * Result-node spawn: same logic as `OverrideInterfaceFunction` —
	 * `AddFunctionGraph<UClass>` only spawns Entry by default; if the parent
	 * UFUNCTION has any output / return parameter, we spawn a Result node
	 * inline (named deterministically as `BpxFuncResult_<FunctionName>`) so
	 * `Get.<var>.OUT → Return.<pin>.IN` wiring works without a separate
	 * "spawn Result" step.
	 *
	 * Idempotence: short-circuits on `FindFunctionGraphByName` match. Mirrors
	 * `AddFunctionGraphDeterministic` — silent skip on existing graph; the
	 * caller's body-authoring ops chain off the returned `EntryGuid` /
	 * `ReturnGuid`.
	 *
	 * Determinism: `GraphGuid` + Entry/Result `NodeGuid` + pin IDs seeded via
	 * `SeedGuidFromJoined(<bp>:override_func:<fn>:<slot>)`. Distinct prefix
	 * (`override_func` vs fresh-function `func`) so a name collision between
	 * a fresh function and an override on the same BP — illegal at compile
	 * time, but possible mid-authoring — produces distinct seeds.
	 *
	 * Calls `MarkBlueprintAsStructurallyModified` on the success path.
	 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.
	 *
	 * Thread: game-thread only.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxGraphEndpoints AddFunctionOverrideDeterministic(
		UBlueprint* Blueprint,
		FName FunctionName);

	// --- M28.13 K2Node_MacroInstance authoring (loop unblocker) ---

	/**
	 * Spawn a `UK2Node_MacroInstance` into a named K2 graph, pointed at an
	 * external macro graph (e.g. ForEachLoop / WhileLoop / Reverse for Each
	 * Loop in `/Engine/EditorBlueprintResources/StandardMacros`), with a
	 * deterministic NodeGuid + pin IDs.
	 *
	 * Driver: design.md feasibility table — five sections (BroadcastOrder /
	 * AssignRole iteration, ScorerScoringLoop, ConfidenceDecay,
	 * ConfidenceDecay+SharedPerception) were stuck on "iterates X → blocked"
	 * because ForEachLoop is a macro instance, not an atomic K2Node, so the
	 * M28.3.x catalog couldn't author it.
	 *
	 * `MacroGraph` MUST be a `EGraphType::GT_Macro` graph. Caller resolves it
	 * Python-side via `unreal.load_object(None, "<lib_path>")` + walking the
	 * resulting UBlueprint's `MacroGraphs` array — bridge enforces the
	 * GT_Macro check defensively but the typical wrong-shape case is caught
	 * earlier with a better error.
	 *
	 * Pin set: K2Node_MacroInstance mirrors the macro's own Tunnel/Result
	 * pins onto the instance via the inherited `UK2Node_Tunnel::AllocateDefaultPins`.
	 * `MacroGraphReference.SetGraph(MacroGraph)` MUST be called BEFORE
	 * `AllocateDefaultPins` so the pin walk has the macro to iterate; without
	 * the pre-alloc set, the node lands with zero pins.
	 *
	 * Determinism: `NodeGuid` is seeded as
	 * `md5(<bp>:graph:<g>:macro:<macro_lib_path>:<macro_name>:<x,y>)`;
	 * `SeedPinGuidsForNode` runs AFTER `AllocateDefaultPins` so the mirrored
	 * pins (whose count + names depend on the macro's signature) get
	 * deterministic PinIds. Library path is included in the seed so two
	 * different ForEachLoop variants from different libraries don't collide.
	 *
	 * Idempotent on the seeded NodeGuid: a second call with identical
	 * (GraphName, MacroGraph, Position) returns `bSuccess=true, bSkipped=true`.
	 * Distinct positions in the same graph are distinct nodes (matching the
	 * rest of the M28.3.x family).
	 *
	 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.
	 *
	 * Thread: game-thread only.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxNodeResult AddMacroInstanceNode(
		UBlueprint* Blueprint,
		FName GraphName,
		UEdGraph* MacroGraph,
		FVector2D Position);

	// --- M28.14 — struct-mutation node catalog (Make / Break / SetFields) ---

	/**
	 * Spawn a `UK2Node_MakeStruct` node — pure node that constructs a struct
	 * value from per-field input pins. First op of the M28.14 catalog.
	 *
	 * Driver: read-modify-write inside the M28.13 ForEachLoop body for
	 * design.md's UAIActionScorer per-element score updates and
	 * confidence-decay over `S_TargetInfo` arrays — without struct authoring
	 * the loops can iterate but cannot author the body.
	 *
	 * `StructType` MUST be set before `AllocateDefaultPins` — the engine
	 * walks the struct's properties via `FStructOnScope` + `FMakeStructPinManager`
	 * inside `AllocateDefaultPins` to populate `ShowPinForProperties` and
	 * spawn the per-field input pins. Post-alloc set leaves the node with no
	 * field pins. `bMadeAfterOverridePinRemoval = true` matches the engine's
	 * editor spawn path (`EdGraphSchema_K2.cpp:7286`); without it the node is
	 * treated as legacy and shows phantom override-toggle pins.
	 *
	 * `StructType == nullptr` is a structured error. Native-make-method-only
	 * structs (e.g. `FVector` on platforms with a native `UKismetMathLibrary::MakeVector`
	 * that the editor prefers) still work — `UK2Node_MakeStruct::CanBeMade`
	 * returns true if the struct has any `BlueprintVisible` non-`BlueprintReadOnly`
	 * property; the BP editor surfaces both Make node + native-make alternative
	 * separately.
	 *
	 * Determinism: `NodeGuid` seeded as
	 * `md5(<bp>:graph:<g>:make_struct:<struct_path>:<x,y>)`;
	 * `SeedPinGuidsForNode` runs AFTER `AllocateDefaultPins` so the per-field
	 * pins (whose count + names depend on the struct's UPROPERTY layout) get
	 * deterministic PinIds. Idempotent on the seeded NodeGuid.
	 *
	 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.
	 *
	 * Thread: game-thread only.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxNodeResult AddMakeStructNode(
		UBlueprint* Blueprint,
		FName GraphName,
		UScriptStruct* StructType,
		FVector2D Position);

	/**
	 * Spawn a `UK2Node_BreakStruct` node — pure node that splits a struct
	 * input into per-field output pins. Sibling of `AddMakeStructNode`.
	 *
	 * Same driver as Make: the read half of read-modify-write inside loop
	 * bodies. `StructType` MUST be set before `AllocateDefaultPins` for the
	 * same reason — the inherited `K2Node_StructMemberGet::AllocateDefaultPins`
	 * walks the struct via `FOptionalPinManager::RebuildPropertyList` to
	 * spawn the per-field output pins. `bMadeAfterOverridePinRemoval = true`
	 * matches the engine's spawn path (`EdGraphSchema_K2.cpp:7350`).
	 *
	 * `StructType == nullptr` is a structured error. `UK2Node_BreakStruct::CanBeBroken`
	 * returns true if the struct has any `BlueprintVisible` property — the
	 * BlueprintReadOnly check is omitted vs Make (you can break a read-only
	 * field even if you can't construct one). Bridge does not pre-check
	 * CanBeBroken — the engine's own validation surfaces clearly at compile
	 * time and pre-checking would duplicate `BLUEPRINTGRAPH_API` surface.
	 *
	 * Determinism: seed key
	 * `md5(<bp>:graph:<g>:break_struct:<struct_path>:<x,y>)`. Idempotent.
	 *
	 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.
	 *
	 * Thread: game-thread only.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxNodeResult AddBreakStructNode(
		UBlueprint* Blueprint,
		FName GraphName,
		UScriptStruct* StructType,
		FVector2D Position);

	/**
	 * Spawn a `UK2Node_SetFieldsInStruct` node — imperative node that takes
	 * a struct input, sets a configurable subset of its fields from input
	 * pins, and emits the modified struct as an output. The "modify" half of
	 * read-modify-write inside loop bodies (vs Make = construct, Break = read).
	 *
	 * `FieldsToShow` is the configurable subset: only field names listed
	 * here are exposed as input pins on the node. SetFieldsInStruct's
	 * `FSetFieldsInStructPinManager::GetRecordDefaults` initializes
	 * `bShowPin = false` for every field (vs Make/Break which default to
	 * true), so the caller MUST pass at least one field name to get a usable
	 * node. Pre-validation: any name in `FieldsToShow` that doesn't match a
	 * property on `StructType` is a structured error (silent no-op would be
	 * a typo foot-gun).
	 *
	 * Implementation: NewObject + StructType + AllocateDefaultPins → engine
	 * populates `ShowPinForProperties` via `RebuildPropertyList` with all
	 * `bShowPin=false`. We then walk `ShowPinForProperties`, set `bShowPin=true`
	 * for entries matching `FieldsToShow`, and call `ReconstructNode()` to
	 * re-run AllocateDefaultPins (which preserves bShowPin overrides through
	 * `RebuildPropertyList`'s old-settings cache). `SeedPinGuidsForNode` runs
	 * AFTER ReconstructNode so all final pins get deterministic PinIds.
	 *
	 * Determinism: seed key
	 * `md5(<bp>:graph:<g>:set_fields_in_struct:<struct_path>:<sorted_fields>:<x,y>)`.
	 * Sorted FieldsToShow in the seed so caller-side ordering doesn't drift
	 * the GUID. Idempotent on the seeded NodeGuid.
	 *
	 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.
	 *
	 * Thread: game-thread only.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxNodeResult AddSetFieldsInStructNode(
		UBlueprint* Blueprint,
		FName GraphName,
		UScriptStruct* StructType,
		const TArray<FName>& FieldsToShow,
		FVector2D Position);

	// --- M28.5.1 EQS authoring — option add ---

	/**
	 * Append a new `UEnvQueryOption` to a `UEnvQuery`'s Options array with its
	 * generator set to a fresh `NewObject<UEnvQueryGenerator>(GeneratorClass)`
	 * owned by the option. First op of the M28.5 EQS write-side catalog.
	 *
	 * Scope: creates the option + the generator in one call. M28.5.2 will
	 * extend with per-test add/remove via a sibling op; scalar property edits
	 * on a generator or test reuse the existing `SetPropertyValue` bridge
	 * against a path like `["Options", "[N]", "Generator", "UPROPERTYName"]`.
	 *
	 * `GeneratorClass` must be a concrete, non-abstract subclass of
	 * `UEnvQueryGenerator`. Abstract classes (including the base itself) are
	 * rejected with a structured error — `NewObject` on an abstract class
	 * throws an uncatchable check() at runtime, so the pre-validation keeps
	 * plan replay crisp.
	 *
	 * Determinism: EQS classes have zero `FGuid::NewGuid()` usage (grep-
	 * confirmed during M28.5.0 research), so the only drift source is
	 * `NewObject`'s default name generation — a counter-suffixed
	 * `EnvQueryOption_0` / `EnvQueryOption_1` / etc. that depends on whatever
	 * else has been allocated in the current editor session. Each `NewObject`
	 * gets an explicit `FName` in `BpxEqsOption_<idx>` / `BpxEqsGen_<idx>`
	 * form so replays across fresh editor shells produce byte-identical
	 * output. `idx` is the pre-insert `Options.Num()` value so sequential
	 * calls get monotonically-increasing names.
	 *
	 * Idempotent on `(Query, GeneratorClass)`: walks existing options and
	 * returns `bSuccess=true, bSkipped=true` with the matching index in
	 * `AfterText` if any option's `Generator->GetClass() == GeneratorClass`.
	 * Option author can tune the generator's per-UPROPERTY values via
	 * `SetPropertyValue` on `["Options", "[N]", "Generator", ...]` without
	 * re-triggering the creation path.
	 *
	 * Result shape:
	 *   BeforeText: `"options=<N>"` (pre-add count)
	 *   AfterText:  `"<new_option_index>"` (0-based) — both on create and skip
	 *
	 * Caller is responsible for `CompileAndSavePackage(Query)` after the add.
	 *
	 * Thread: game-thread only. `NewObject` + `UPackage::SetDirtyFlag` are
	 * editor-safe on the game thread and not thread-safe off it.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult AddEnvQueryOption(
		UEnvQuery* Query,
		UClass* GeneratorClass);

	// --- M28.5.2 EQS authoring — test add / remove ---

	/**
	 * Append a new `UEnvQueryTest` subclass instance to the `Tests[]` array on
	 * `UEnvQuery::Options[OptionIndex]`. Second op of the M28.5 EQS write-side
	 * catalog; builds on M28.5.1's option-level shape.
	 *
	 * `TestClass` must be a concrete, non-abstract subclass of `UEnvQueryTest`.
	 * The base `UEnvQueryTest` is `UCLASS(Abstract)` so the abstract check
	 * rejects the base itself in addition to any abstract intermediates.
	 *
	 * Determinism: like M28.5.1, explicit `FName` on `NewObject` — pattern
	 * `BpxEqsTest_<option_index>_<pre_test_count>_<TestClassShortName>`. Option
	 * index is part of the name so two options carrying the same test class
	 * don't collide in the package's FName table. EQS classes have zero
	 * `FGuid::NewGuid()` usage per M28.5.0 research so the counter-suffix is
	 * the only drift source.
	 *
	 * `TestOrder` invariant: `EnvQueryManager.cpp:874` only repairs the order
	 * at runtime when it is zero; the editor must assign it sequentially as
	 * tests are added. Post-append assigns `NewTest->TestOrder = PreCount`
	 * so the `0..N-1` ordering holds. `RemoveEnvQueryTest` reseats the tail
	 * to preserve the same invariant on delete.
	 *
	 * Idempotent on `(Query, OptionIndex, TestClass)`: walks `Option->Tests[]`
	 * and returns `bSuccess=true, bSkipped=true` with the matching index in
	 * `AfterText` if any test is an exact-class match. Plan authors tune
	 * per-UPROPERTY values via `SetPropertyValue` on
	 * `["Options", "[N]", "Tests", "[M]", "..."]`.
	 *
	 * Result shape:
	 *   BeforeText: `"tests=<N>"` (pre-add count on the target option)
	 *   AfterText:  `"<new_test_index>"` — both on create and skip
	 *
	 * Caller is responsible for `CompileAndSavePackage(Query)` after the add.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult AddEnvQueryTest(
		UEnvQuery* Query,
		int32 OptionIndex,
		UClass* TestClass);

	/**
	 * Remove the test at `Options[OptionIndex].Tests[TestIndex]` and reseat
	 * `TestOrder` on every subsequent test so the `0..N-1` invariant holds.
	 * Symmetric counterpart of `AddEnvQueryTest`.
	 *
	 * Idempotent on `(Query, OptionIndex, TestIndex)`: an out-of-range
	 * `TestIndex` (e.g. a re-apply after a successful prior run removed
	 * the same test) returns `bSuccess=true, bSkipped=true` with
	 * `AfterText="already-removed:<test_index>"`. OptionIndex still has a
	 * hard bounds check — option identity is stable across test removals,
	 * so an out-of-range option indicates a plan-level misunderstanding.
	 *
	 * Result shape:
	 *   BeforeText: `"tests=<N>"` (pre-remove count on the target option)
	 *   AfterText:  `"removed-index:<test_index>"` on actual removal,
	 *               `"already-removed:<test_index>"` on the idempotent
	 *               skip path.
	 *
	 * Caller is responsible for `CompileAndSavePackage(Query)` after the
	 * remove.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult RemoveEnvQueryTest(
		UEnvQuery* Query,
		int32 OptionIndex,
		int32 TestIndex);

	// --- M28.4.1 CurveFloat authoring — create / set keys ---

	/**
	 * Create a new `UCurveFloat` asset at the supplied `/Game/...` package
	 * path. First op of the M28.4 non-BP asset-factory catalog.
	 *
	 * Wraps `NewObject<UCurveFloat>(Pkg, Name, RF_Public | RF_Standalone)`.
	 * Notifies the AssetRegistry + marks the package dirty; the caller is
	 * responsible for `CompileAndSavePackage(curve)` to persist — same
	 * pattern as `AddEnvQueryOption`. Compile is a no-op for non-Blueprint
	 * assets; `CompileAndSavePackage` shorts the compile branch and writes
	 * via `UPackage::SavePackage` directly.
	 *
	 * Determinism: `UCurveFloat` / `UCurveBase` / `FRichCurveKey` have
	 * zero `FGuid::NewGuid()` usage (grep-confirmed M28.4.0 research). No
	 * seeding is required — the explicit `FName` on `NewObject` (derived
	 * from the short name of `PackagePath`) is already enough.
	 *
	 * Idempotent on `PackagePath`: if a `UCurveFloat` already exists at
	 * the path, returns `bSuccess=true, bSkipped=true` with
	 * `AfterText=PackagePath`. If a non-curve asset occupies the path, a
	 * structured error is returned (different class collisions should not
	 * silently no-op — the caller has a plan-level mistake to fix).
	 *
	 * Result shape:
	 *   BeforeText: `"no-curve"` on create, `"curve-exists"` on skip.
	 *   AfterText:  the created/existing curve's `/Game/...` path.
	 *
	 * Thread: game-thread only. `NewObject` + `CreatePackage` +
	 * `AssetRegistry::AssetCreated` are editor-safe on the game thread.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult CreateCurveFloatDeterministic(
		const FString& PackagePath);

	/**
	 * Wholesale-replace the `FRichCurveKey` array on a `UCurveFloat`'s
	 * `FloatCurve` with `NewKeys`. Second op of the M28.4 catalog.
	 *
	 * Mirrors the `FRichCurve::SetKeys` API — caller pre-sorts the keys
	 * by Time ascending. Unsorted input is rejected up-front with a
	 * structured error because UE's `FRichCurve::Evaluate` assumes sorted
	 * storage and would silently sample incorrectly otherwise.
	 *
	 * Scope is deliberately wholesale-replace (not per-key add/remove)
	 * per the M28.4.0 research — matches the authoring style for the
	 * design.md intensity-curve use case (re-author a 4-point curve when
	 * tuning, rather than incrementally patching one point). Per-key ops
	 * (`AddCurveFloatKey` / `SetCurveFloatKey` / `RemoveCurveFloatKey`)
	 * are deferred until a concrete driver surfaces the need.
	 *
	 * Idempotent on element-wise `(Time, Value, InterpMode)` equality: if
	 * the existing key array already matches `NewKeys` on those fields in
	 * order, returns `bSuccess=true, bSkipped=true` without touching the
	 * asset. Tangent fields are excluded from the compare because the
	 * M28.4.1 Python surface only accepts Time+Value (tangent defaults
	 * roll through `FRichCurveKey`'s zero-initialiser, which the engine
	 * normalises on load).
	 *
	 * Caller is responsible for `CompileAndSavePackage(Curve)` after the
	 * mutation — same pattern as the EQS write-side ops.
	 *
	 * Result shape:
	 *   BeforeText: `"keys=<pre_count>"`.
	 *   AfterText:  `"keys=<new_count>"` — decimal so the soak harness
	 *               can cross-check via the standard `after_text` read.
	 *
	 * Thread: game-thread only. `FRichCurve::SetKeys` + `SetDirtyFlag`
	 * are not thread-safe.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult SetCurveFloatKeys(
		UCurveFloat* Curve,
		const TArray<FRichCurveKey>& NewKeys);

	// --- M28.4.2 DataAsset authoring — create instance ---

	/**
	 * Create a new `UDataAsset`-subclass instance at the supplied `/Game/...`
	 * package path, using `DAClass` as the concrete type to instantiate.
	 * Third op of the M28.4 non-BP asset-factory catalog.
	 *
	 * Wraps `NewObject<UDataAsset>(Pkg, DAClass, FName(ShortName),
	 * RF_Public | RF_Standalone | RF_Transactional)` — matching
	 * `UDataAssetFactory::FactoryCreateNew`'s flag set
	 * (EditorFactories.cpp:7288-7300). Notifies the AssetRegistry + marks the
	 * package dirty; caller is responsible for `CompileAndSavePackage(Asset)`
	 * to persist — same pattern as `CreateCurveFloatDeterministic`. Compile
	 * is a no-op for non-Blueprint assets; `CompileAndSavePackage` shorts
	 * the compile branch and writes via `UPackage::SavePackage` directly.
	 *
	 * `DAClass` must be:
	 *   - non-null,
	 *   - a subclass of `UDataAsset` (covers UDataAsset / UPrimaryDataAsset /
	 *     BP-derived DA classes whose GeneratedClass inherits from either),
	 *   - concrete (CLASS_Abstract flag rejected up-front).
	 *
	 * Determinism: `UDataAsset` / `UPrimaryDataAsset` have zero
	 * `FGuid::NewGuid()` usage (M28.4.0 research — walks the Engine/DataAsset.h
	 * + UPrimaryDataAsset.cpp surface). The only drift source is `NewObject`'s
	 * default-name generation, closed by passing an explicit `FName` derived
	 * from the short-name tail of `PackagePath`.
	 *
	 * Idempotent on `PackagePath`: if a `UDataAsset` already exists at the
	 * path AND is an instance of `DAClass`, returns `bSuccess=true,
	 * bSkipped=true` with `AfterText=PackagePath`. A wrong-class collision
	 * (either non-DA asset at the path, or DA whose class doesn't match
	 * `DAClass`) returns a structured error rather than silently creating
	 * alongside — the plan author has a target mismatch to fix.
	 *
	 * Result shape:
	 *   BeforeText: `"no-asset"` on create, `"asset-exists"` on skip.
	 *   AfterText:  the created/existing asset's `/Game/...` path.
	 *
	 * Thread: game-thread only. `NewObject` + `CreatePackage` +
	 * `AssetRegistry::AssetCreated` are editor-safe on the game thread.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult CreateDataAssetInstanceDeterministic(
		const FString& PackagePath,
		UClass* DAClass);

	// --- M28.4.3 UserDefinedStruct authoring — create / add member / remove member / set default ---

	/**
	 * Create a new `UUserDefinedStruct` asset at the supplied `/Game/...`
	 * package path. Fourth (and most complex) slice of the M28.4 non-BP
	 * asset-factory catalog.
	 *
	 * Wraps `FStructureEditorUtils::CreateUserDefinedStruct(Pkg, FName(ShortName),
	 * RF_Public | RF_Standalone | RF_Transactional)`. The engine helper:
	 *   1. Allocates the UUserDefinedStruct + its inner
	 *      UUserDefinedStructEditorData via `NewObject`.
	 *   2. Assigns `Struct->Guid = FGuid::NewGuid()` (StructureEditorUtils.cpp:53)
	 *      — first determinism trap.
	 *   3. Auto-adds a default `bool` member via `AddVariable(Struct, FEdGraphPinType(PC_Boolean, ...))`
	 *      (StructureEditorUtils.cpp:60), which itself assigns
	 *      `VarGuid = FGuid::NewGuid()` (:303) — second determinism trap.
	 *   4. Routes the auto-member's VarName through
	 *      `FMemberVariableNameHelper::Generate(Struct, DisplayName, Guid)`
	 *      so VarName is derived from the random VarGuid.
	 *
	 * Post-create we close both traps:
	 *   - Overwrite `Struct->Guid` with
	 *     `SeedGuidFromJoined(PackagePath + ":uds")`.
	 *   - Rename the auto-bool to friendly name `BpxAutoBool`, seed its
	 *     VarGuid with `SeedGuidFromJoined(PackagePath + ":uds_var:BpxAutoBool")`,
	 *     then call `FStructureEditorUtils::RenameVariable(Struct, SeededGuid,
	 *     "BpxAutoBool")` so `VarName` regenerates from seed + friendly and the
	 *     UScriptStruct's FProperty chain recompiles with the seeded shape.
	 *
	 * The auto-bool is intentionally left in place (renamed, not removed):
	 * `RemoveVariable` refuses to empty the struct (`bAllowToMakeEmpty=false`,
	 * StructureEditorUtils.cpp:327), and chaining add → remove would double the
	 * op count for the same end state. Plan authors drive further structure via
	 * `AddUserDefinedStructMember` and optionally `RemoveUserDefinedStructMember`
	 * to drop the auto-bool once at least one real member is present.
	 *
	 * Idempotent on `PackagePath`: if a `UUserDefinedStruct` already exists at
	 * the path, returns `bSuccess=true, bSkipped=true` with `AfterText=PackagePath`.
	 * Wrong-class collision at the path → structured error (silent stacking
	 * would be a plan-level mistake).
	 *
	 * Caller is responsible for `CompileAndSavePackage(UDS)` after create.
	 *
	 * Result shape:
	 *   BeforeText: `"no-uds"` on create, `"uds-exists"` on skip.
	 *   AfterText:  the created/existing UDS's `/Game/...` path.
	 *
	 * Thread: game-thread only. `FStructureEditorUtils::CreateUserDefinedStruct`
	 * is editor-only and not thread-safe.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult CreateUserDefinedStructDeterministic(
		const FString& PackagePath);

	/**
	 * Append a new member variable to a `UUserDefinedStruct` with a
	 * deterministic VarGuid. Wraps `FStructureEditorUtils::AddVariable` +
	 * post-seed of the new VarDesc's VarGuid + rename pass so VarName
	 * regenerates from the seeded Guid + the requested friendly name.
	 *
	 * `VarType` is the full `FEdGraphPinType` the member should take —
	 * built Python-side via `blueprint_structural._resolve_pin_type` from
	 * a terse string spec (`"int"` / `"struct:/Script/Game.S_Foo"` /
	 * `"array:real"` / etc.).
	 *
	 * `DefaultValue` is the literal default value as a string in the same
	 * format `FStructVariableDescription::DefaultValue` accepts. Empty
	 * string = type default (engine handles). On non-empty input, after
	 * the add + rename we call `ChangeVariableDefaultValue(Struct,
	 * SeededGuid, DefaultValue)` so the value lands on VarDesc +
	 * DefaultInstance in one shot.
	 *
	 * Idempotent on `FriendlyName`: walks existing VarDescriptions for a
	 * matching `FriendlyName` and returns `bSuccess=true, bSkipped=true`
	 * without touching the asset. Type compatibility is NOT verified on
	 * the skip path — same semantics as `AddMemberVariableDeterministic`.
	 * The existing VarGuid is left untouched on skip so the seed recipe
	 * stays deterministic across replays.
	 *
	 * Caller is responsible for `CompileAndSavePackage(UDS)` after the add.
	 *
	 * Result shape:
	 *   BeforeText: `"no-member"` on add, `"member-exists:<FriendlyName>"` on skip.
	 *   AfterText:  `"member-added:<FriendlyName>"` / `"member-exists:<FriendlyName>"`.
	 *
	 * Thread: game-thread only.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult AddUserDefinedStructMember(
		UUserDefinedStruct* Struct,
		FName FriendlyName,
		const FEdGraphPinType& VarType,
		const FString& DefaultValue);

	/**
	 * Remove a member variable by friendly name from a `UUserDefinedStruct`.
	 * Wraps `FStructureEditorUtils::RemoveVariable` after resolving the
	 * friendly name → VarGuid on the target struct's VarDescriptions array.
	 *
	 * Idempotent on `FriendlyName`: if no member with that friendly name
	 * exists, returns `bSuccess=true, bSkipped=true` with
	 * `AfterText="already-removed:<FriendlyName>"`.
	 *
	 * Refuses to empty the struct: if the target member is the last one
	 * (pre-remove count == 1), returns a structured error matching the
	 * engine's `bAllowToMakeEmpty=false` invariant
	 * (StructureEditorUtils.cpp:327). Plan authors who want an "empty"
	 * logical struct should add the replacement member BEFORE removing
	 * the placeholder, not after.
	 *
	 * Caller is responsible for `CompileAndSavePackage(UDS)` after the remove.
	 *
	 * Result shape:
	 *   BeforeText: `"members=<pre_count>"` on remove, `"no-member:<FriendlyName>"` on skip.
	 *   AfterText:  `"member-removed:<FriendlyName>"` /
	 *               `"already-removed:<FriendlyName>"`.
	 *
	 * Thread: game-thread only.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult RemoveUserDefinedStructMember(
		UUserDefinedStruct* Struct,
		FName FriendlyName);

	/**
	 * Set a member variable's default-value string on a `UUserDefinedStruct`.
	 * Wraps `FStructureEditorUtils::ChangeVariableDefaultValue` after
	 * resolving the friendly name → VarGuid.
	 *
	 * `DefaultValueStr` is the literal default value in the same string
	 * format `FStructVariableDescription::DefaultValue` accepts — e.g.
	 * `"true"` for bool, `"42"` for int, `"(X=1.0,Y=2.0,Z=0.0)"` for vectors,
	 * `"/Game/MyDT.MyDT"` for soft object paths. Callers converting from
	 * Python scalars should use the same ExportText normalization pattern
	 * `data_assets._normalize_scalar_value` uses.
	 *
	 * Why not reuse `SetPropertyValue` on the struct's DefaultInstance:
	 * `ChangeVariableDefaultValue` writes `VarDesc.DefaultValue` (the
	 * authoritative string that regenerates `DefaultInstance` memory via
	 * `RecreateDefaultInstanceInEditorData`); a direct write to
	 * `DefaultInstance` via `SetPropertyValue` leaves `VarDesc.DefaultValue`
	 * stale and the UDS in a torn state where the serialized string says X
	 * but memory says Y. M28.4.0 research Open Question #1 selected this
	 * path.
	 *
	 * Idempotent: compares existing `VarDesc.DefaultValue` against
	 * `DefaultValueStr` up-front; match → `bSuccess=true, bSkipped=true`
	 * without invoking the engine call (which would fire listener events
	 * and churn the asset). Missing member name returns a structured
	 * error — silent no-op on a plan-level typo would hide a real
	 * authoring mistake.
	 *
	 * Caller is responsible for `CompileAndSavePackage(UDS)` after the set.
	 *
	 * Result shape:
	 *   BeforeText: the pre-op default value string.
	 *   AfterText:  the post-op default value string (== DefaultValueStr).
	 *
	 * Thread: game-thread only.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult SetUserDefinedStructMemberDefault(
		UUserDefinedStruct* Struct,
		FName FriendlyName,
		const FString& DefaultValueStr);

	// --- M28.6.1 GameplayTag config authoring ---

	/**
	 * Append a new gameplay tag to a project ini source via UE's editor-side
	 * tag-config API. Bridge wrapper around
	 * `IGameplayTagsEditorModule::AddNewGameplayTagToINI`, which sorts the
	 * resulting ini list, preserves the leading `;METADATA=` editor marker
	 * comment, and refreshes the in-memory tag tree post-write.
	 *
	 * Module location: the engine API lives in the editor-only
	 * `GameplayTagsEditor` plugin, NOT on the runtime `UGameplayTagsManager`
	 * (the M28 phase table assumed the latter — M28.6.0 research corrected
	 * this). Compiles out unless `WITH_GAMEPLAYTAGSEDITOR_SUPPORT=1` per the
	 * Build.cs gate; in non-editor builds the call returns `bSuccess=false`
	 * with a structured error.
	 *
	 * Idempotent on `(TagName, SourceIni)`: pre-checks via
	 * `UGameplayTagsManager::IsDictionaryTag(TagName)` so a re-apply against
	 * an already-registered tag returns `bSuccess=true, bSkipped=true`
	 * without firing the engine's "already exists" toast or touching the
	 * .ini file. Critical for M28.pre.3 soak round-2 byte-identity — the
	 * engine API itself returns `false` on duplicate-add, but the Python op
	 * and verify_tag_author.py gate need a real skip signal.
	 *
	 * Source ini resolution (per `GameplayTagsEditorModule.cpp:500-518`):
	 *   - `SourceIni == NAME_None` → engine substitutes the default name
	 *     `"DefaultGameplayTags.ini"` (= `FGameplayTagSource::GetDefaultName()`)
	 *     UNLESS `UGameplayTagsDeveloperSettings::DeveloperConfigName` is
	 *     non-empty, in which case the source is diverted to the per-machine
	 *     developer ini. Plan authors should pass an explicit
	 *     `"DefaultGameplayTags.ini"` to make the intent clear, but cannot
	 *     bypass the developer-override (it's user-machine config — analogous
	 *     to how Perforce settings divert .uasset saves).
	 *   - `SourceIni == "DefaultGameplayTags.ini"` → routes to
	 *     `<Project>/Config/DefaultGameplayTags.ini` (mapped to
	 *     `UGameplayTagsSettings`'s pre-registered source).
	 *   - any other name → routes to `<Project>/Config/Tags/<name>` (mapped
	 *     to a `UGameplayTagsList` source created on first write).
	 *
	 * Validation: relies on the engine's internal `IsValidGameplayTagString`
	 * pre-check (called inside `AddNewGameplayTagToINI`). On invalid tag
	 * strings (forbidden characters per `UGameplayTagsSettings::InvalidTagCharacters`,
	 * leading/trailing dot, double-dot) the engine call returns `false` and
	 * surfaces the error via an editor toast; this UFUNCTION reports
	 * `bSuccess=false` with a generic message pointing the user at the
	 * editor log. A future M28.6.x could expose `IsValidGameplayTagString`
	 * as a separate validator UFUNCTION for plan-validate-time pre-checks
	 * if a real driver wants typed feedback.
	 *
	 * Save behaviour: `AddNewGameplayTagToINI` writes via
	 * `TagListObj->TryUpdateDefaultConfigFile(ConfigFileName)` and routes
	 * through `ISourceControlModule` — if Perforce is configured, the .ini
	 * gets checked out as part of the save. The existing `confirm=True`
	 * gate on `apply_plan` is the mitigation for that side effect; document
	 * loudly in the AGENT_LOOP worked example.
	 *
	 * Result shape:
	 *   BeforeText: `"absent"` on add, `"existing-in:<source>"` on idempotent skip.
	 *   AfterText:  the source ini name (FName.ToString()) the tag landed in.
	 *               Useful when `SourceIni == NAME_None` and the engine
	 *               substituted the default — the caller learns where the
	 *               tag actually went.
	 *
	 * @param TagName            Dotted tag path (e.g. `"AI.Order.Flank"`).
	 *                           Empty input returns a structured error.
	 * @param DevComment         Author-visible comment string. Stored as
	 *                           `+GameplayTagList=(Tag="...",DevComment="...")`.
	 *                           Empty is fine and matches the most common
	 *                           DOW pattern.
	 * @param SourceIni          Target source ini name (`NAME_None` for
	 *                           engine default, `"DefaultGameplayTags.ini"`
	 *                           for explicit project default, or any
	 *                           per-source ini name like `"AI.ini"` to land
	 *                           the tag under `Config/Tags/AI.ini`).
	 * @param bIsRestrictedTag   Authors a `+RestrictedGameplayTagList=` entry
	 *                           instead. Restricted-tag children rules are
	 *                           enforced by the engine; out of scope for
	 *                           the M28.6.1 soak coverage (always `false`
	 *                           in fixtures), exposed for forward-compat.
	 *
	 * Thread: game-thread only. Engine call refreshes the in-memory tag
	 * tree via `EditorRefreshGameplayTagTree`, which is editor-only and not
	 * thread-safe.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult AddGameplayTag(
		const FString& TagName,
		const FString& DevComment,
		FName SourceIni,
		bool bIsRestrictedTag);

	// --- M28.10.1 Blueprint class authoring — create with native or BP parent ---

	/**
	 * Create a new `UBlueprint` asset at the supplied `/Game/...` package path,
	 * using `ParentClass` as the parent (native `/Script/<Module>.<Class>` or
	 * BP-derived generated class `/Game/.../<Name>.<Name>_C`). Closes the
	 * design.md gap surfaced by the M28.10.0 research outcome: existing
	 * `create_child_bp` (`scripts/python_ops/assets.py:84`) only handles
	 * BP-parented children, so design.md's `BP_EncounterDirector` (parent
	 * `AActor`) and `UAIActionScorer` (parent `UActorComponent`) couldn't be
	 * authored end-to-end via MCP.
	 *
	 * Wraps `FKismetEditorUtilities::CreateBlueprint(ParentClass, Pkg,
	 * FName(ShortName), BPTYPE_Normal, UBlueprint::StaticClass(),
	 * UBlueprintGeneratedClass::StaticClass(), NAME_None)`. The engine helper
	 * (`Kismet2.cpp:432`):
	 *   1. `NewObject<UBlueprint>(...)` with deterministic FName tail of `PackagePath`.
	 *   2. `NewBP->BlueprintGuid = FGuid::NewGuid()`            <-- determinism trap #1
	 *   3. Allocates SCS + UCS function graph + EventGraph ubergraph page.
	 *      The UCS `K2Node_FunctionEntry` gets a fresh NodeGuid.   <-- trap #2a
	 *   4. If `bSpawnDefaultBlueprintNodes=true` (editor default):
	 *      walks `AutoGeneratedDefaultEventsMap` and spawns one
	 *      `UK2Node_Event` per registered event matching the parent class
	 *      hierarchy (e.g. BeginPlay / Tick / EndPlay for `AActor`-family;
	 *      module-registered events for other parents). Each spawned node
	 *      gets a fresh NodeGuid + per-pin random PinIds.          <-- trap #2b
	 *      Iteration over a `TMultiMap` is hash-bucket-ordered and not
	 *      stable across editor invocations — must sort post-hoc.
	 *   5. Synchronous compile (already runs inside CreateBlueprint).
	 *
	 * Post-create we close all three traps:
	 *   - Overwrite `NewBP->BlueprintGuid` with
	 *     `SeedGuidFromJoined(PackagePath + ":bp")`.
	 *   - For the UCS function graph's `K2Node_FunctionEntry` (if present),
	 *     reseed `NodeGuid` + every pin's `PinId` via
	 *     `SeedGuidFromJoined(PackagePath + ":ucs:entry")`.
	 *   - For each node in `UbergraphPages[0]->Nodes`, sort by
	 *     `(NodeClass.Name, K2Node_Event->EventReference.GetMemberName())` for
	 *     stable order, then reseed `NodeGuid` + pins via
	 *     `SeedGuidFromJoined(PackagePath + ":evt:" + EventName)`.
	 *
	 * `USCS_Node::VariableGuid` is **already deterministic** (md5 of
	 * `InternalVariableName`, `SCS_Node.cpp:645`) — no trapdoor.
	 *
	 * `ParentClass` must be:
	 *   - non-null,
	 *   - blueprintable per `FKismetEditorUtilities::CanCreateBlueprintOfClass`
	 *     (rejects e.g. `UInterface`, classes with `BlueprintType=NotBlueprintable`,
	 *     and a few engine internals — same gate the editor's New Blueprint
	 *     dialog uses, and the gate `BlueprintFactory::FactoryCreateNew`
	 *     (`EditorFactories.cpp:6805`) would otherwise raise as a modal
	 *     `FMessageDialog` — must intercept before that path in commandlet /
	 *     Python contexts).
	 *
	 * Idempotent on `(PackagePath, ParentClass)`: if a `UBlueprint` already
	 * exists at the path AND its `ParentClass` pointer matches `ParentClass`,
	 * returns `bSuccess=true, bSkipped=true` with `AfterText=PackagePath`.
	 * Class mismatch at the same path returns a structured error — silent
	 * stacking would be a plan-level mistake. This is **stricter than
	 * `create_child_bp`**, which only verified existence ("parent class not
	 * verified" caveat at `scripts/python_ops/CATALOG.md:1431`); the C++
	 * bridge has direct access to `Existing->ParentClass` without going
	 * through the partially-exposed Python `BlueprintGeneratedClass.get_super_class`.
	 *
	 * Caller is responsible for `CompileAndSavePackage(NewBP)` after create.
	 *
	 * Result shape:
	 *   BeforeText: `"no-bp"` on create, `"bp-exists"` on skip.
	 *   AfterText:  the created/existing BP's `/Game/...` path.
	 *
	 * Thread: game-thread only. `FKismetEditorUtilities::CreateBlueprint`
	 * runs a synchronous compile and is editor-only.
	 */
	UFUNCTION(BlueprintCallable, Category = "BlueprintExporter|Reflection")
	static FBpxReflectionResult CreateBlueprintClassDeterministic(
		const FString& PackagePath,
		UClass* ParentClass);
};
