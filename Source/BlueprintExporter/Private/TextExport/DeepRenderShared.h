// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/Function.h"

class UObject;
class UScriptStruct;
class UEdGraph;
class FProperty;

namespace BlueprintExporter::DeepRender
{
	/** Markdown table-cell escape: escapes `|` and collapses newlines so a value never breaks the row. */
	FString EscTbl(const FString& In);

	/** UE-internal plumbing UPROPERTYs that carry no authoring meaning (UberGraphFrame / CachedFrameStateTree). */
	bool IsCommonPlumbingProperty(FName Name);

	/**
	 * Render a Markdown property table for a UObject's UPROPERTYs (alpha-sorted).
	 * Skips IsCommonPlumbingProperty plus any names in AdditionalPlumbing (callers pass type-specific
	 * back-reference names they want stripped — e.g. BehaviorTree passes TreeAsset / ParentNode / TemplateNode).
	 * Returns row count (0 if Obj is null or no rows were emitted).
	 */
	int32 RenderUObjectPropertiesTable(FString& Md, const UObject* Obj, const TSet<FName>& AdditionalPlumbing = TSet<FName>());

	/**
	 * Render a Markdown field table for a UScriptStruct instance at Memory (alpha-sorted by field name).
	 * Column header is "Field | Type | Value". Common plumbing is filtered (no-op for most structs).
	 * Returns row count (0 if Type/Memory null or no rows).
	 */
	int32 RenderStructFieldsTable(FString& Md, const UScriptStruct* Type, const void* Memory);

	/**
	 * UEdGraphNode plumbing set — editor-state UPROPERTYs (NodePosX/Y, comment bubble,
	 * compiler messages, enabled state, Pins/DeprecatedPins) that carry no authoring
	 * signal and shift across reloads. Passed to RenderUObjectPropertiesTable as
	 * AdditionalPlumbing when rendering individual UEdGraphNode subtypes. Shared
	 * between M29.2 (UCustomizableObject) and M29.3 (UCustomizableObjectMacroLibrary)
	 * graph walkers — nothing Mutable-specific in the set.
	 */
	const TSet<FName>& EdGraphNodePlumbing();

	/**
	 * UEdGraph pin GUIDs (UEdGraphPin::PinId) are assigned at pin-creation and
	 * regenerate every load, so any FEdGraphPinReference-typed UPROPERTY serialized
	 * via ExportTextItem_Direct leaks `PinId=<32-hex>` that drifts run-to-run.
	 * Replace every such GUID in InOutText with the literal `<unstable>` while
	 * preserving the `OwningNode` reference — honors "Never guess values" by
	 * marking the GUID as unstable rather than dropping it or faking one.
	 * `StartOffset` limits the search to a suffix of the text so callers can
	 * mask only the just-appended slice. (M29.2 twin-run finding.)
	 */
	void MaskPinGuids(FString& InOutText, int32 StartOffset = 0);

	/**
	 * Walk a UEdGraph's Nodes in authored order, emitting one heading block per
	 * node with class + title + alpha-sorted UPROPERTY table (filtered by
	 * EdGraphNodePlumbing) + outgoing pin-link table (output pins only — input
	 * pins are inverse edges of some other node's output list). Applies
	 * MaskPinGuids to the rendered suffix before returning so the output is
	 * twin-run stable. Caller emits its own section heading above this.
	 *
	 * Handles null graph + null node slots defensively with visible markers.
	 */
	void RenderEdGraphNodes(FString& Md, const UEdGraph* Graph);

	/**
	 * M29.6.1 — zero-include UFUNCTION call-through helpers.
	 *
	 * Invoke a UFUNCTION by name via ProcessEvent, then extract the return
	 * value by type. Returns empty `TOptional<>` / `false` when the function
	 * is not present on the object's class (runtime-absent optional module,
	 * renamed API, signature drift, etc.) so callers render "_not reachable_"
	 * markers rather than faking a value — honors the plugin's "Never guess
	 * values" contract.
	 *
	 * Use these instead of direct typed calls whenever the target class lives
	 * in an optional / out-of-tree module that we don't want to link against.
	 * Lets a single BuiltPlugin DLL handle every project's asset types via
	 * runtime dispatch, independent of build-engine plugin availability — see
	 * the "engine-agnostic" design note (M29.6 arc).
	 *
	 * Args are positional ImportText-formatted strings, one per non-return
	 * parameter in the UFUNCTION's declared order. Empty args list is valid
	 * for nullary functions. Param-buffer lifetime is fully managed inside
	 * the call so `FString` / struct / `FTransform` returns round-trip
	 * cleanly.
	 */
	namespace UFunctionCall
	{
		/**
		 * Core primitive. Returns `false` when the function isn't found or
		 * the arg count doesn't match; otherwise invokes ProcessEvent and
		 * hands `(ReturnProp, ReturnValuePtr)` to the callback for the
		 * caller to extract. Callback is only invoked for functions with a
		 * non-void return. Void-return functions still return `true` (the
		 * call succeeded, there's just nothing to extract).
		 */
		bool CallUFunctionRaw(
			UObject* Obj,
			FName FunctionName,
			const TArray<FString>& Args,
			TFunctionRef<void(FProperty* ReturnProp, const void* ReturnValuePtr)> ReturnCallback);

		/** Thin typed wrappers over CallUFunctionRaw. Empty TOptional means
		 *  function missing OR return-type mismatch — caller can't distinguish
		 *  (and doesn't need to: both cases render the same "_not reachable_"
		 *  way). */
		TOptional<bool>     CallBool(UObject* Obj, FName FuncName, const TArray<FString>& Args = TArray<FString>());
		TOptional<int32>    CallInt(UObject* Obj, FName FuncName, const TArray<FString>& Args = TArray<FString>());
		/** Enum return — works for both `FEnumProperty` (new-style scoped) and
		 *  `FByteProperty` with attached `UEnum`. Returned as int64 so the
		 *  caller can look up the name via `UEnum::GetNameStringByValue`. */
		TOptional<int64>    CallEnumInt64(UObject* Obj, FName FuncName, const TArray<FString>& Args = TArray<FString>());
		TOptional<float>    CallFloat(UObject* Obj, FName FuncName, const TArray<FString>& Args = TArray<FString>());
		TOptional<FString>  CallString(UObject* Obj, FName FuncName, const TArray<FString>& Args = TArray<FString>());
		TOptional<FName>    CallFName(UObject* Obj, FName FuncName, const TArray<FString>& Args = TArray<FString>());
		TOptional<UObject*> CallObject(UObject* Obj, FName FuncName, const TArray<FString>& Args = TArray<FString>());
	}
}
