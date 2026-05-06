// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Schema/BlueprintExportTypes.h"

class UBlueprint;
class UEdGraph;
class UEdGraphNode;
class UEdGraphPin;
class USCS_Node;
class UK2Node;
class UAnimGraphNode_StateMachine;
class UWidget;

/**
 * Serializes UBlueprint objects to portable FExportedBlueprint format.
 * Handles all supported Blueprint elements including graphs, nodes, variables, etc.
 */
class BLUEPRINTEXPORTER_API FBlueprintSerializer
{
public:
	FBlueprintSerializer();
	~FBlueprintSerializer();

	/**
	 * Serialize a Blueprint to exportable format.
	 * @param Blueprint The Blueprint to serialize
	 * @param OutExported The output exported data
	 * @param OutError Error message if serialization fails
	 * @return True if successful
	 */
	bool SerializeBlueprint(const UBlueprint* Blueprint, FExportedBlueprint& OutExported, FString& OutError);

	/**
	 * Serialize a single graph.
	 * @param Graph The graph to serialize
	 * @return The serialized graph data
	 */
	FExportedGraph SerializeGraph(const UEdGraph* Graph);

	/**
	 * Serialize a single node.
	 * @param Node The node to serialize
	 * @return The serialized node data
	 */
	FExportedNode SerializeNode(const UEdGraphNode* Node);

	/**
	 * Serialize a pin.
	 * @param Pin The pin to serialize
	 * @return The serialized pin data
	 */
	FExportedPin SerializePin(const UEdGraphPin* Pin);

	/**
	 * Serialize pin type information.
	 * @param PinType The pin type to serialize
	 * @return The serialized pin type
	 */
	FExportedPinType SerializePinType(const FEdGraphPinType& PinType);

	/**
	 * Get node-specific data for special node types.
	 * @param Node The node to get specific data from
	 * @return JSON string with node-specific data
	 */
	FString GetNodeSpecificData(const UK2Node* Node);

	/** Detect native subclass name via UE reflection.
	 *  Returns short class name with U prefix stripped (e.g., "AnimBlueprint").
	 *  Returns "Blueprint" for standard UBlueprint assets. */
	static FString DetectBlueprintSubclass(const UBlueprint* Blueprint);

private:
	/** Serialize Blueprint variables */
	TArray<FExportedVariable> SerializeVariables(const UBlueprint* Blueprint);

	/** Serialize Blueprint functions */
	TArray<FExportedFunction> SerializeFunctions(const UBlueprint* Blueprint);

	/** Serialize Blueprint macros */
	TArray<FExportedFunction> SerializeMacros(const UBlueprint* Blueprint);

	/** Serialize component hierarchy for Actor blueprints */
	TArray<FExportedComponent> SerializeComponents(const UBlueprint* Blueprint);

	/** Recursively serialize SCS nodes */
	FExportedComponent SerializeSCSNode(const USCS_Node* SCSNode);

	/** Walk the generated class's CDO and emit inherited UPROPERTY overrides — values
	 *  that differ from the parent class CDO. Captures Details-panel authoring that
	 *  `SerializeVariables` misses (which handles BP-declared fields, not inherited
	 *  overrides). Reuses the M9 instanced-subobject walker for `CPF_InstancedReference`
	 *  / `CPF_PersistentInstance` fields so nested trees (GE modifier lists, GAS
	 *  attribute sets, AIPerception sense configs) land as structured JSON rather than
	 *  flat text blobs. Output is sorted alphabetically by property name for
	 *  determinism (brief §8). */
	TArray<FExportedComponentProperty> SerializeCDOProperties(const UBlueprint* Blueprint);

	/** Classify a Blueprint as a data-carrier subtype via `IsChildOf` against lazily-
	 *  loaded `UGameplayEffect` / `UGameplayAbility` / `UDataAsset` base classes.
	 *  Returns "GameplayEffect" / "GameplayAbility" / "DataAsset" or empty. The three
	 *  bases are found via `StaticFindObject` (same pattern as M7 `ProjectPluginsCommandlet`)
	 *  so the serializer doesn't gain new Build.cs module deps — absent modules just
	 *  produce an empty discriminator. */
	FString DetectDataCarrierKind(const UBlueprint* Blueprint);

	/** Serialize Blueprint dependencies */
	TArray<FExportedDependency> SerializeDependencies(const UBlueprint* Blueprint);

	/** Serialize all state machines found in AnimBP graphs.
	 *  Walks FunctionGraphs and UbergraphPages looking for AnimGraphNode_StateMachine nodes. */
	TArray<FExportedStateMachine> SerializeStateMachines(const UBlueprint* Blueprint);

	/** Serialize a single state machine from its AnimGraphNode.
	 *  Walks the internal UAnimationStateMachineGraph to extract states, transitions, and blend settings.
	 *  Recursively serializes nested state machines found in state BoundGraphs. */
	FExportedStateMachine SerializeStateMachine(const UAnimGraphNode_StateMachine* SMNode);

	/** Serialize a WidgetBlueprint's widget tree. Returns empty array for non-Widget BPs or when
	 *  the root widget is null. Root node lands at index 0; descendants are recursive via
	 *  UPanelWidget::GetChildAt, preserving authored slot order. */
	TArray<FExportedWidgetNode> SerializeWidgetTree(const UBlueprint* Blueprint);

	/** Serialize a single UWidget into FExportedWidgetNode plus its children. */
	FExportedWidgetNode SerializeWidgetNode(const UWidget* Widget);

	/** Get parent class information */
	FExportedParentClass SerializeParentClass(const UBlueprint* Blueprint);

	/** Get implemented interfaces */
	TArray<FString> SerializeImplementedInterfaces(const UBlueprint* Blueprint);

	/** Convert Blueprint type enum */
	EBlueprintExportType ConvertBlueprintType(const UBlueprint* Blueprint);

	/** Generate stable node ID */
	FString GenerateStableNodeId(const UEdGraphNode* Node);

	/** Generate stable pin ID */
	FString GenerateStablePinId(const UEdGraphPin* Pin);

	/** Serialize function parameters from entry/result nodes */
	void SerializeFunctionSignature(const UEdGraph* FunctionGraph, TArray<FExportedFunctionParam>& OutInputs, TArray<FExportedFunctionParam>& OutOutputs);

	/** Safely serialize pin type with extra validation to prevent crashes from orphaned object references */
	FExportedPinType SerializePinTypeSafe(const UEdGraphPin* Pin);

	/** Safely serialize pin type from FEdGraphPinType directly (used for variables) */
	FExportedPinType SerializePinTypeSafeFromType(const FEdGraphPinType& PinType);

	/** Build mapping of node GUIDs to stable IDs for connections */
	TMap<FGuid, FString> NodeGuidToStableId;

	/** Build mapping of pin addresses to stable IDs */
	TMap<const UEdGraphPin*, FString> PinToStableId;

};
