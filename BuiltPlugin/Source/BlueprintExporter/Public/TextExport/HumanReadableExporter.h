// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Schema/BlueprintExportTypes.h"
#include "Schema/StateTreeExportTypes.h"

/**
 * Generates human-readable text summaries of Blueprints.
 * Output is designed for documentation, code review, and AI analysis.
 */
class BLUEPRINTEXPORTER_API FHumanReadableExporter
{
public:
	FHumanReadableExporter();
	~FHumanReadableExporter();

	/**
	 * Export Blueprint to human-readable text format.
	 * @param ExportedData The exported Blueprint data
	 * @return Human-readable text representation
	 */
	FString ExportToText(const FExportedBlueprint& ExportedData);

	/**
	 * Export a single graph to text.
	 * @param Graph The graph to export
	 * @param GraphName Name of the graph
	 * @return Text representation of the graph
	 */
	FString ExportGraphToText(const FExportedGraph& Graph, const FString& GraphName);

	/**
	 * Export execution flow for a graph.
	 * Traces from events through execution chains.
	 * @param Graph The graph to analyze
	 * @return Text representation of execution flow
	 */
	FString ExportExecutionFlow(const FExportedGraph& Graph);

	/**
	 * Save human-readable export to file.
	 * @param ExportedData The exported Blueprint data
	 * @param OutputPath Path to save the file
	 * @return True if successful
	 */
	bool SaveToFile(const FExportedBlueprint& ExportedData, const FString& OutputPath);

	/**
	 * Generate a Blueprint digest with key metrics.
	 * @param ExportedData The exported Blueprint data
	 * @return JSON object with digest information
	 */
	TSharedPtr<FJsonObject> GenerateDigest(const FExportedBlueprint& ExportedData);

	/**
	 * Save digest to file.
	 * @param ExportedData The exported Blueprint data
	 * @param OutputPath Path to save the digest
	 * @return True if successful
	 */
	bool SaveDigestToFile(const FExportedBlueprint& ExportedData, const FString& OutputPath);

	// ---- State Tree Export ----

	/**
	 * Export State Tree to human-readable text format.
	 * @param ExportedData The exported State Tree data
	 * @return Human-readable text representation
	 */
	FString ExportStateTreeToText(const FExportedStateTree& ExportedData);

	/**
	 * Save State Tree human-readable export to file.
	 * @param ExportedData The exported State Tree data
	 * @param OutputPath Path to save the file
	 * @return True if successful
	 */
	bool SaveStateTreeToFile(const FExportedStateTree& ExportedData, const FString& OutputPath);

	/**
	 * Save State Tree digest to file.
	 * @param ExportedData The exported State Tree data
	 * @param OutputPath Path to save the digest
	 * @return True if successful
	 */
	bool SaveStateTreeDigestToFile(const FExportedStateTree& ExportedData, const FString& OutputPath);

	/**
	 * Generate a State Tree digest with key metrics.
	 * @param ExportedData The exported State Tree data
	 * @return JSON object with digest information
	 */
	TSharedPtr<FJsonObject> GenerateStateTreeDigest(const FExportedStateTree& ExportedData);

private:
	/** Format variable declaration */
	FString FormatVariable(const FExportedVariable& Variable);

	/** Format function signature */
	FString FormatFunctionSignature(const FExportedFunction& Function);

	/** Format component hierarchy */
	FString FormatComponentHierarchy(const TArray<FExportedComponent>& Components, int32 Indent = 0);

	/** Format a single component with indentation */
	FString FormatComponent(const FExportedComponent& Component, int32 Indent);

	/** Format a single component property (flat or instanced-subobject) under a component. */
	FString FormatComponentProperty(const FExportedComponentProperty& Property, const FString& IndentStr);

	/** Format one entry of FExportedComponentProperty::SubobjectJsonValues as an indented block.
	 *  `Depth` is the mutual-recursion counter shared with FormatNestedInstancedProperty;
	 *  guarded by MAX_RENDER_RECURSION_DEPTH to protect against externally-constructed
	 *  cyclic FJsonValue graphs. */
	FString FormatInstancedSubobject(const TSharedPtr<FJsonValue>& SubobjectValue, const FString& IndentStr, int32 Depth = 0);

	/** Format a property inside an instanced-subobject tree (JSON shape from the subobject's "properties" array). */
	FString FormatNestedInstancedProperty(const TSharedPtr<FJsonValue>& PropertyValue, const FString& IndentStr, int32 Depth = 0);

	/** Format pin type to readable string */
	FString FormatPinType(const FExportedPinType& PinType);

	/** Trace execution flow from a starting event node */
	FString TraceExecutionFlow(const FExportedGraph& Graph, const FExportedNode& StartNode, int32 Indent);

	/** Find node by ID in graph */
	const FExportedNode* FindNodeById(const FExportedGraph& Graph, const FString& NodeId);

	/** Get connected node via exec pin */
	const FExportedNode* GetNextExecNode(const FExportedGraph& Graph, const FExportedNode& Node);

	/** An exec-pin connection: which pin name led to which node */
	struct FExecConnection
	{
		FString PinName;
		const FExportedNode* ConnectedNode;
	};

	/** Get execution connections from a node, paired with their source pin names */
	TArray<FExecConnection> GetExecConnections(const FExportedGraph& Graph, const FExportedNode& Node);

	/** Format node for inline display */
	FString FormatNodeInline(const FExportedNode& Node);

	/** Format node with expanded input values */
	FString FormatNodeWithInputs(const FExportedGraph& Graph, const FExportedNode& Node);

	/** Check if a node is a pure node (no exec pins) */
	bool IsPureNode(const FExportedNode& Node) const;

	/** Get input pin value with recursive pure node expansion */
	FString GetInputPinValue(const FExportedGraph& Graph, const FExportedPin& Pin, TSet<FString>& VisitedNodes, int32 Depth = 0);

	/** Format pure node chain recursively with ↳ notation */
	FString FormatPureNodeChain(const FExportedGraph& Graph, const FExportedNode& Node, TSet<FString>& VisitedNodes, int32 IndentLevel);

	/** Format pure node chain starting from depth 1 (skip inline-expanded nodes) */
	FString FormatPureNodeChainFromDepth1(const FExportedGraph& Graph, const FExportedNode& Node, TSet<FString>& VisitedNodes, int32 IndentLevel);

	/** Get the output pin name used in a connection */
	FString GetOutputPinName(const FExportedNode& Node, const FString& PinId) const;

	/** Check if a pin should be skipped (self, exec, hidden) */
	bool ShouldSkipPin(const FExportedPin& Pin) const;

	/** Format a pin's value for display */
	FString FormatPinValue(const FExportedPin& Pin) const;

	/** Indent text by number of levels */
	FString Indent(int32 Level);

	/** Count nodes by type */
	TMap<FString, int32> CountNodesByType(const FExportedBlueprint& ExportedData);

	/** Calculate complexity metrics */
	void CalculateComplexityMetrics(const FExportedBlueprint& ExportedData, int32& OutCyclomaticComplexity, int32& OutNestingDepth);

	// ---- State Tree Private Helpers ----

	/** Format state hierarchy recursively */
	FString FormatStateHierarchy(const TArray<FExportedStateTreeState>& States, int32 IndentLevel);

	/** Format a single state */
	FString FormatState(const FExportedStateTreeState& State, int32 IndentLevel);

	/** Format an editor node (task/condition/evaluator) */
	FString FormatEditorNode(const FExportedStateTreeEditorNode& Node);

	/** Format a transition */
	FString FormatTransition(const FExportedStateTreeTransition& Transition);

	/** Count states recursively */
	int32 CountStatesRecursive(const TArray<FExportedStateTreeState>& States);
};
