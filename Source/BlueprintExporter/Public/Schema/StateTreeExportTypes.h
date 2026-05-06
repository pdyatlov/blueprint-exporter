// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "Schema/BlueprintExportTypes.h"

/**
 * State tree state type. Mirrors UE's `EStateTreeStateType`.
 *
 * `Linked` and `LinkedAsset` are distinct: `Linked` points at another state
 * *within the same tree* (via `UStateTreeState::LinkedSubtree`), whereas
 * `LinkedAsset` points at a *different StateTree asset* (via
 * `UStateTreeState::LinkedAsset`). Pre-M5.3 we collapsed both to `Linked`
 * and silently emitted `Unknown` when UE set the state type to
 * `LinkedAsset`; DOW's NPC patrol state hit that path.
 */
enum class EExportedStateTreeStateType : uint8
{
	State,
	Group,
	Linked,
	LinkedAsset,
	Subtree,
	Unknown
};

/**
 * State tree transition trigger
 */
enum class EExportedStateTreeTransitionTrigger : uint8
{
	OnStateCompleted,
	OnStateSucceeded,
	OnStateFailed,
	OnTick,
	OnEvent,
	Unknown
};

/**
 * State tree selection behavior
 */
enum class EExportedStateTreeSelectionBehavior : uint8
{
	None,
	TryEnterState,
	TrySelectChildrenInOrder,
	TryFollowTransitions,
	Unknown
};

/**
 * Generic property extracted from FInstancedStruct reflection.
 * Used for task/condition/evaluator parameters.
 */
struct BLUEPRINTEXPORTER_API FExportedStateTreeProperty
{
	/** Property name */
	FString Name;

	/** Property type (e.g., "float", "int32", "FVector", "UClass*") */
	FString Type;

	/** String representation of the value */
	FString Value;

	/** Category from metadata if available */
	FString Category;

	TSharedPtr<FJsonObject> ToJson() const;
	static FExportedStateTreeProperty FromJson(const TSharedPtr<FJsonObject>& JsonObject);
};

/**
 * A task, condition, evaluator, or consideration node within a state.
 *
 * StateTree editor nodes have a two-part shape:
 *   - `Node` — immutable node struct (e.g. `FStateTreeMoveToTask`). Carries
 *     scheduler plumbing (BindingsBatch, InstanceDataHandle, etc.) and, for
 *     wrapper nodes, the pointer to the wrapped class (e.g.
 *     `FStateTreeBlueprintTaskWrapper::TaskClass`).
 *   - `InstanceData` / `Instance` — the per-instance configuration. For most
 *     native tasks this is a sibling `FInstancedStruct` (e.g.
 *     `FStateTreeMoveToTaskInstanceData` with `AcceptanceRadius`, `MoveToMode`,
 *     `FilterClass`). For Blueprint-backed nodes it's a `UObject` instance of
 *     the wrapped BP class (e.g. `STT_FindRandomLocation_C` with the BP's
 *     authored properties).
 *
 * The node struct alone (captured in `Properties`) describes the role; the
 * instance data/object is where the authored behavior actually lives. Both
 * are captured here so consumers can reason about NPC behaviour without
 * loading the asset.
 */
struct BLUEPRINTEXPORTER_API FExportedStateTreeEditorNode
{
	/** Node name (usually struct type short name) */
	FString Name;

	/** Fully qualified struct type path */
	FString StructType;

	/** Category: "Task", "EnterCondition", "Condition", "Evaluator", "Consideration" */
	FString Category;

	/** Instance ID for binding references */
	FString InstanceId;

	/** Reflected properties from the `Node` FInstancedStruct (scheduler plumbing + wrapper fields) */
	TArray<FExportedStateTreeProperty> Properties;

	/** Reflected properties from `InstanceData` (for native tasks/conditions with struct-typed instance data) */
	TArray<FExportedStateTreeProperty> InstanceProperties;

	/** Class path of the `Instance` UObject, when the node is Blueprint-backed (e.g. `UStateTreeTaskBlueprintBase` subclass) */
	FString InstanceObjectClass;

	/** Reflected properties from the `Instance` UObject, when Blueprint-backed */
	TArray<FExportedStateTreeProperty> InstanceObjectProperties;

	TSharedPtr<FJsonObject> ToJson() const;
	static FExportedStateTreeEditorNode FromJson(const TSharedPtr<FJsonObject>& JsonObject);
};

/**
 * Property binding (data wiring between nodes/parameters).
 */
struct BLUEPRINTEXPORTER_API FExportedStateTreeBinding
{
	/** Source path (e.g., "Evaluator.MyEval.Value") */
	FString SourcePath;

	/** Target path (e.g., "Task.MoveToTarget.TargetLocation") */
	FString TargetPath;

	TSharedPtr<FJsonObject> ToJson() const;
	static FExportedStateTreeBinding FromJson(const TSharedPtr<FJsonObject>& JsonObject);
};

/**
 * State tree transition.
 */
struct BLUEPRINTEXPORTER_API FExportedStateTreeTransition
{
	/** Unique ID for deterministic ordering */
	FString TransitionId;

	/** Trigger type */
	EExportedStateTreeTransitionTrigger Trigger = EExportedStateTreeTransitionTrigger::Unknown;

	/** Event tag (for OnEvent triggers) */
	FString EventTag;

	/** Target state name */
	FString TargetStateName;

	/** Target state GUID for unambiguous identification */
	FString TargetStateGuid;

	/**
	 * Link type from `FStateTreeStateLink::LinkType`. One of:
	 *   `GotoState` — transition references an explicit target state (Target* fields populated);
	 *   `Succeeded` / `Failed` — exit the containing tree/subtree with success/failure;
	 *   `NextState` / `NextSelectableState` — go to next sibling (selectable skips disabled ones);
	 *   `None` — no transition target set.
	 * Pre-M5.3 this field wasn't read, so non-GotoState transitions rendered
	 * as `(unresolved)` — visually indistinguishable from bugs.
	 */
	FString LinkType;

	/** Transition priority */
	FString Priority;

	/** Delay duration in seconds (0 = immediate) */
	float DelaySeconds = 0.0f;

	/** Whether delay is random */
	bool bDelayIsRandom = false;

	/** Random delay deviation in seconds */
	float DelayRandomDeviationSeconds = 0.0f;

	/** Conditions that must be met for this transition */
	TArray<FExportedStateTreeEditorNode> Conditions;

	TSharedPtr<FJsonObject> ToJson() const;
	static FExportedStateTreeTransition FromJson(const TSharedPtr<FJsonObject>& JsonObject);
};

/**
 * A state in the state tree hierarchy (recursive, like FExportedComponent).
 */
struct BLUEPRINTEXPORTER_API FExportedStateTreeState
{
	/** State name */
	FString Name;

	/** State GUID for identity */
	FString StateGuid;

	/** State type */
	EExportedStateTreeStateType Type = EExportedStateTreeStateType::State;

	/** Gameplay tag associated with this state */
	FString Tag;

	/** Selection behavior for child states */
	EExportedStateTreeSelectionBehavior SelectionBehavior = EExportedStateTreeSelectionBehavior::None;

	/**
	 * For `Linked` states: name of the target subtree *within the same tree*
	 * (`UStateTreeState::LinkedSubtree.Name`). Unused for `LinkedAsset`
	 * states — see `LinkedAssetPath` below.
	 */
	FString LinkedAsset;

	/**
	 * For `LinkedAsset` states: object path of the external StateTree asset
	 * the state delegates execution to (`UStateTreeState::LinkedAsset`).
	 * Empty for other state types.
	 */
	FString LinkedAssetPath;

	/** Enter conditions */
	TArray<FExportedStateTreeEditorNode> EnterConditions;

	/** Tasks in this state */
	TArray<FExportedStateTreeEditorNode> Tasks;

	/** Transitions from this state */
	TArray<FExportedStateTreeTransition> Transitions;

	/** Child states (recursive) */
	TArray<FExportedStateTreeState> Children;

	TSharedPtr<FJsonObject> ToJson() const;
	static FExportedStateTreeState FromJson(const TSharedPtr<FJsonObject>& JsonObject);
};

/**
 * Top-level State Tree export container.
 */
struct BLUEPRINTEXPORTER_API FExportedStateTree
{
	/** Export metadata */
	FExportInfo ExportInfo;

	/** Asset path in Unreal */
	FString AssetPath;

	/** Asset name */
	FString AssetName;

	/** Schema class name (e.g., "StateTreeComponentSchema") */
	FString Schema;

	/** Global evaluators */
	TArray<FExportedStateTreeEditorNode> Evaluators;

	/** Global tasks */
	TArray<FExportedStateTreeEditorNode> GlobalTasks;

	/** Root states (subtrees) */
	TArray<FExportedStateTreeState> RootStates;

	/** Property bindings */
	TArray<FExportedStateTreeBinding> Bindings;

	/** Asset dependencies */
	TArray<FExportedDependency> Dependencies;

	TSharedPtr<FJsonObject> ToJson() const;
	static FExportedStateTree FromJson(const TSharedPtr<FJsonObject>& JsonObject);

	/** Compute content hash for change detection */
	FString ComputeContentHash() const;
};
