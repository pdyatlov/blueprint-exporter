// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Schema/StateTreeExportTypes.h"

class UStateTree;
struct FStateTreeEditorNode;
struct FStateTreeTransition;
struct FInstancedStruct;

/**
 * Serializes UStateTree assets to portable FExportedStateTree format.
 * Accesses editor data via UStateTreeEditorData for full state hierarchy extraction.
 */
class BLUEPRINTEXPORTER_API FStateTreeSerializer
{
public:
	FStateTreeSerializer();
	~FStateTreeSerializer();

	/**
	 * Serialize a State Tree to exportable format.
	 * @param StateTree The State Tree asset to serialize
	 * @param OutExported The output exported data
	 * @param OutError Error message if serialization fails
	 * @return True if successful
	 */
	bool SerializeStateTree(const UStateTree* StateTree, FExportedStateTree& OutExported, FString& OutError);

	/**
	 * Check if the StateTree module is available at runtime.
	 * @return True if the StateTree plugin is loaded and available
	 */
	static bool IsStateTreeModuleAvailable();

private:
	/** Maximum recursion depth to prevent infinite loops */
	static constexpr int32 MaxStateDepth = 50;

	/** Serialize a single state recursively */
	FExportedStateTreeState SerializeState(const class UStateTreeState* State, int32 Depth);

	/** Serialize an editor node (task/condition/evaluator) */
	FExportedStateTreeEditorNode SerializeEditorNode(const FStateTreeEditorNode& EditorNode, const FString& Category);

	/** Serialize properties from an FInstancedStruct via FProperty reflection */
	TArray<FExportedStateTreeProperty> SerializeInstancedStructProperties(const FInstancedStruct& InstancedStruct);

	/** Serialize UPROPERTY fields of a UObject (class + instance) via FProperty reflection. Used for BP-backed node instances. */
	TArray<FExportedStateTreeProperty> SerializeUObjectProperties(const UObject* Instance);

	/** Serialize transitions from a state */
	TArray<FExportedStateTreeTransition> SerializeTransitions(const TArray<FStateTreeTransition>& Transitions);

	/** Serialize property bindings from editor data */
	TArray<FExportedStateTreeBinding> SerializePropertyBindings(const class UStateTreeEditorData* EditorData);

	/** Serialize asset dependencies */
	TArray<FExportedDependency> SerializeDependencies(const UStateTree* StateTree);

	/** Set of processed state GUIDs for cycle detection */
	TSet<FGuid> ProcessedStateGuids;
};
