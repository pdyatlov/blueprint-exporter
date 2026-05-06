// Copyright Epic Games, Inc. All Rights Reserved.

#include "Serialization/StateTreeSerializer.h"
#include "Modules/ModuleManager.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/Package.h"

#if WITH_STATETREE_SUPPORT
#include "StateTree.h"
#include "StateTreeEditorData.h"
#include "StateTreeState.h"
#include "StateTreeTaskBase.h"
#include "StateTreeConditionBase.h"
#include "StateTreeEvaluatorBase.h"
#include "StateTreePropertyBindings.h"
#include "StructUtils/InstancedStruct.h"
#include "UObject/UnrealType.h"
#include "UObject/TextProperty.h"
#include "GameplayTagContainer.h"
#endif

FStateTreeSerializer::FStateTreeSerializer()
{
}

FStateTreeSerializer::~FStateTreeSerializer()
{
}

bool FStateTreeSerializer::IsStateTreeModuleAvailable()
{
	return FModuleManager::Get().IsModuleLoaded(TEXT("StateTreeModule"));
}

bool FStateTreeSerializer::SerializeStateTree(const UStateTree* StateTree, FExportedStateTree& OutExported, FString& OutError)
{
	if (!StateTree)
	{
		OutError = TEXT("StateTree is null");
		return false;
	}

#if WITH_STATETREE_SUPPORT
	// Reset cycle detection
	ProcessedStateGuids.Reset();

	// Fill export info
	OutExported.ExportInfo.SchemaVersion = BLUEPRINT_EXPORT_SCHEMA_VERSION;
	OutExported.ExportInfo.EngineVersion = FEngineVersion::Current().ToString();
	OutExported.ExportInfo.PluginVersion = TEXT("1.28.6");
	OutExported.ExportInfo.ExportTimestamp = FDateTime::UtcNow().ToIso8601();

	// Basic info
	OutExported.AssetPath = StateTree->GetPathName();
	OutExported.AssetName = StateTree->GetName();

	// Access editor data
	const UStateTreeEditorData* EditorData = Cast<UStateTreeEditorData>(StateTree->EditorData);
	if (!EditorData)
	{
		OutError = TEXT("StateTree has no editor data (may be a cooked/runtime-only asset)");
		return false;
	}

	// Schema
	if (EditorData->Schema)
	{
		OutExported.Schema = EditorData->Schema->GetClass()->GetName();
	}

	// Evaluators
	for (const FStateTreeEditorNode& EvalNode : EditorData->Evaluators)
	{
		OutExported.Evaluators.Add(SerializeEditorNode(EvalNode, TEXT("Evaluator")));
	}

	// Global tasks (UE 5.3+)
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 3
	for (const FStateTreeEditorNode& TaskNode : EditorData->GlobalTasks)
	{
		OutExported.GlobalTasks.Add(SerializeEditorNode(TaskNode, TEXT("GlobalTask")));
	}
#endif

	// Root states (SubTrees)
	for (const TObjectPtr<UStateTreeState>& RootState : EditorData->SubTrees)
	{
		if (RootState)
		{
			OutExported.RootStates.Add(SerializeState(RootState, 0));
		}
	}

	// Property bindings
	OutExported.Bindings = SerializePropertyBindings(EditorData);

	// Dependencies
	OutExported.Dependencies = SerializeDependencies(StateTree);

	// Compute content hash
	OutExported.ExportInfo.ContentHash = OutExported.ComputeContentHash();

	return true;
#else
	OutError = TEXT("StateTree support is not available in this build");
	return false;
#endif
}

FExportedStateTreeState FStateTreeSerializer::SerializeState(const UStateTreeState* State, int32 Depth)
{
	FExportedStateTreeState ExportedState;

#if WITH_STATETREE_SUPPORT
	if (!State || Depth > MaxStateDepth)
	{
		ExportedState.Name = TEXT("[depth limit exceeded]");
		return ExportedState;
	}

	// Cycle detection
	if (ProcessedStateGuids.Contains(State->ID))
	{
		ExportedState.Name = FString::Printf(TEXT("[cycle: %s]"), *State->Name.ToString());
		ExportedState.StateGuid = State->ID.ToString();
		return ExportedState;
	}
	ProcessedStateGuids.Add(State->ID);

	// Basic info
	ExportedState.Name = State->Name.ToString();
	ExportedState.StateGuid = State->ID.ToString();

	// Map state type. UE 5.5+ distinguishes `Linked` (in-tree) from
	// `LinkedAsset` (external tree asset) — both used to fall through to
	// Unknown pre-M5.3 since the switch was missing `LinkedAsset`.
	switch (State->Type)
	{
	case EStateTreeStateType::State:
		ExportedState.Type = EExportedStateTreeStateType::State;
		break;
	case EStateTreeStateType::Group:
		ExportedState.Type = EExportedStateTreeStateType::Group;
		break;
	case EStateTreeStateType::Linked:
		ExportedState.Type = EExportedStateTreeStateType::Linked;
		break;
	case EStateTreeStateType::LinkedAsset:
		ExportedState.Type = EExportedStateTreeStateType::LinkedAsset;
		break;
	case EStateTreeStateType::Subtree:
		ExportedState.Type = EExportedStateTreeStateType::Subtree;
		break;
	default:
		ExportedState.Type = EExportedStateTreeStateType::Unknown;
		break;
	}

	// Tag
	if (State->Tag.IsValid())
	{
		ExportedState.Tag = State->Tag.ToString();
	}

	// Selection behavior
	switch (State->SelectionBehavior)
	{
	case EStateTreeStateSelectionBehavior::None:
		ExportedState.SelectionBehavior = EExportedStateTreeSelectionBehavior::None;
		break;
	case EStateTreeStateSelectionBehavior::TryEnterState:
		ExportedState.SelectionBehavior = EExportedStateTreeSelectionBehavior::TryEnterState;
		break;
	case EStateTreeStateSelectionBehavior::TrySelectChildrenInOrder:
		ExportedState.SelectionBehavior = EExportedStateTreeSelectionBehavior::TrySelectChildrenInOrder;
		break;
	case EStateTreeStateSelectionBehavior::TryFollowTransitions:
		ExportedState.SelectionBehavior = EExportedStateTreeSelectionBehavior::TryFollowTransitions;
		break;
	default:
		ExportedState.SelectionBehavior = EExportedStateTreeSelectionBehavior::Unknown;
		break;
	}

	// Linked target — two distinct cases on UStateTreeState:
	//   `Linked`       → `LinkedSubtree` (FStateTreeStateLink pointing inside the same tree).
	//   `LinkedAsset`  → `LinkedAsset` (TObjectPtr<UStateTree> pointing at an external asset).
	if (State->Type == EStateTreeStateType::Linked && State->LinkedSubtree.ID.IsValid())
	{
		ExportedState.LinkedAsset = State->LinkedSubtree.Name.ToString();
	}
	else if (State->Type == EStateTreeStateType::LinkedAsset && State->LinkedAsset)
	{
		ExportedState.LinkedAssetPath = State->LinkedAsset->GetPathName();
	}

	// Enter conditions
	for (const FStateTreeEditorNode& ConditionNode : State->EnterConditions)
	{
		ExportedState.EnterConditions.Add(SerializeEditorNode(ConditionNode, TEXT("EnterCondition")));
	}

	// Tasks
	for (const FStateTreeEditorNode& TaskNode : State->Tasks)
	{
		ExportedState.Tasks.Add(SerializeEditorNode(TaskNode, TEXT("Task")));
	}

	// Transitions
	ExportedState.Transitions = SerializeTransitions(State->Transitions);

	// Children (recursive)
	for (const TObjectPtr<UStateTreeState>& ChildState : State->Children)
	{
		if (ChildState)
		{
			ExportedState.Children.Add(SerializeState(ChildState, Depth + 1));
		}
	}
#else
	ExportedState.Name = TEXT("[StateTree support not available]");
#endif

	return ExportedState;
}

FExportedStateTreeEditorNode FStateTreeSerializer::SerializeEditorNode(const FStateTreeEditorNode& EditorNode, const FString& Category)
{
	FExportedStateTreeEditorNode ExportedNode;

#if WITH_STATETREE_SUPPORT
	ExportedNode.Category = Category;
	ExportedNode.InstanceId = EditorNode.ID.ToString();

	// (1) Node struct — the scheduler-plumbing template (also holds wrapper
	// fields like `TaskClass` for BP-backed wrappers).
	const FInstancedStruct& NodeStruct = EditorNode.Node;
	if (NodeStruct.IsValid())
	{
		const UScriptStruct* ScriptStruct = NodeStruct.GetScriptStruct();
		if (ScriptStruct)
		{
			ExportedNode.Name = ScriptStruct->GetName();
			ExportedNode.StructType = ScriptStruct->GetPathName();
		}

		ExportedNode.Properties = SerializeInstancedStructProperties(NodeStruct);
	}
	else
	{
		ExportedNode.Name = TEXT("[invalid]");
		ExportedNode.StructType = TEXT("");
	}

	// (2) Instance data — `FStateTreeEditorNode::Instance` is a sibling
	// FInstancedStruct holding where a native task's authored configuration
	// lives (e.g. `FStateTreeMoveToTaskInstanceData::AcceptanceRadius`).
	// Left empty for BP-backed wrappers, where the authored values live on
	// the UObject below.
	if (EditorNode.Instance.IsValid())
	{
		ExportedNode.InstanceProperties = SerializeInstancedStructProperties(EditorNode.Instance);
	}

	// (3) Instance object — `FStateTreeEditorNode::InstanceObject` is set
	// when the wrapped type is a `UStateTreeTaskBlueprintBase` /
	// `UStateTreeConditionBlueprintBase` / `UStateTreeEvaluatorBlueprintBase`
	// subclass (BP-authored tasks etc.). The UObject holds the authored BP
	// property values.
	if (UObject* InstanceObject = EditorNode.InstanceObject)
	{
		if (const UClass* InstanceClass = InstanceObject->GetClass())
		{
			ExportedNode.InstanceObjectClass = InstanceClass->GetPathName();
		}
		ExportedNode.InstanceObjectProperties = SerializeUObjectProperties(InstanceObject);
	}
#else
	ExportedNode.Name = TEXT("[StateTree support not available]");
#endif

	return ExportedNode;
}

TArray<FExportedStateTreeProperty> FStateTreeSerializer::SerializeInstancedStructProperties(const FInstancedStruct& InstancedStruct)
{
	TArray<FExportedStateTreeProperty> Properties;

#if WITH_STATETREE_SUPPORT
	if (!InstancedStruct.IsValid())
	{
		return Properties;
	}

	const UScriptStruct* ScriptStruct = InstancedStruct.GetScriptStruct();
	const uint8* StructMemory = InstancedStruct.GetMemory();

	if (!ScriptStruct || !StructMemory)
	{
		return Properties;
	}

	// Iterate all properties via FProperty reflection
	for (TFieldIterator<FProperty> PropIt(ScriptStruct); PropIt; ++PropIt)
	{
		const FProperty* Property = *PropIt;
		if (!Property)
		{
			continue;
		}

		// Skip properties that are editor-only metadata or internal
		FString PropertyName = Property->GetName();
		if (PropertyName.StartsWith(TEXT("b")) && PropertyName.Len() > 1 && FChar::IsUpper(PropertyName[1]))
		{
			// Include bool properties
		}

		FExportedStateTreeProperty ExportedProp;
		ExportedProp.Name = PropertyName;

		// Determine type string
		ExportedProp.Type = Property->GetCPPType();

		// Get category from metadata
		if (Property->HasMetaData(TEXT("Category")))
		{
			ExportedProp.Category = Property->GetMetaData(TEXT("Category"));
		}

		// Export value as string
		FString ValueStr;
		const void* ValuePtr = Property->ContainerPtrToValuePtr<void>(StructMemory);
		Property->ExportTextItem_Direct(ValueStr, ValuePtr, nullptr, nullptr, PPF_None);

		ExportedProp.Value = ValueStr;
		Properties.Add(ExportedProp);
	}
#endif

	return Properties;
}

namespace
{
	// Same plumbing filter as the M11–M15 Tier 2 deep renderers
	// (SmartObjectDefinition / BehaviorTree / EnvQuery). Runtime back-
	// references that leak into UPROPERTY walks on BP-backed instance
	// classes; no authoring meaning.
	bool IsStateTreeUEPlumbingProperty(FName Name)
	{
		static const TSet<FName> Plumbing = {
			FName(TEXT("UberGraphFrame")),
			FName(TEXT("CachedFrameStateTree")),
		};
		return Plumbing.Contains(Name);
	}
}

TArray<FExportedStateTreeProperty> FStateTreeSerializer::SerializeUObjectProperties(const UObject* Instance)
{
	TArray<FExportedStateTreeProperty> Properties;

#if WITH_STATETREE_SUPPORT
	if (!Instance)
	{
		return Properties;
	}

	const UClass* InstanceClass = Instance->GetClass();
	if (!InstanceClass)
	{
		return Properties;
	}

	// Walk every UPROPERTY on the class (including inherited). TFieldIterator's
	// default traversal returns base-class properties first, then derived — the
	// consumer-side sort in ToJson() normalises ordering, so iteration order
	// doesn't leak into output.
	for (TFieldIterator<FProperty> PropIt(InstanceClass); PropIt; ++PropIt)
	{
		const FProperty* Property = *PropIt;
		if (!Property || IsStateTreeUEPlumbingProperty(Property->GetFName()))
		{
			continue;
		}

		FExportedStateTreeProperty ExportedProp;
		ExportedProp.Name = Property->GetName();
		ExportedProp.Type = Property->GetCPPType();
		if (Property->HasMetaData(TEXT("Category")))
		{
			ExportedProp.Category = Property->GetMetaData(TEXT("Category"));
		}

		FString ValueStr;
		const void* ValuePtr = Property->ContainerPtrToValuePtr<void>(Instance);
		Property->ExportTextItem_Direct(ValueStr, ValuePtr, nullptr, nullptr, PPF_None);
		ExportedProp.Value = ValueStr;

		Properties.Add(ExportedProp);
	}
#endif

	return Properties;
}

TArray<FExportedStateTreeTransition> FStateTreeSerializer::SerializeTransitions(const TArray<FStateTreeTransition>& Transitions)
{
	TArray<FExportedStateTreeTransition> ExportedTransitions;

#if WITH_STATETREE_SUPPORT
	for (const FStateTreeTransition& Transition : Transitions)
	{
		FExportedStateTreeTransition ExportedTransition;
		ExportedTransition.TransitionId = Transition.ID.ToString();

		// Map trigger type
		switch (Transition.Trigger)
		{
		case EStateTreeTransitionTrigger::OnStateCompleted:
			ExportedTransition.Trigger = EExportedStateTreeTransitionTrigger::OnStateCompleted;
			break;
		case EStateTreeTransitionTrigger::OnStateSucceeded:
			ExportedTransition.Trigger = EExportedStateTreeTransitionTrigger::OnStateSucceeded;
			break;
		case EStateTreeTransitionTrigger::OnStateFailed:
			ExportedTransition.Trigger = EExportedStateTreeTransitionTrigger::OnStateFailed;
			break;
		case EStateTreeTransitionTrigger::OnTick:
			ExportedTransition.Trigger = EExportedStateTreeTransitionTrigger::OnTick;
			break;
		case EStateTreeTransitionTrigger::OnEvent:
			ExportedTransition.Trigger = EExportedStateTreeTransitionTrigger::OnEvent;
			break;
		default:
			ExportedTransition.Trigger = EExportedStateTreeTransitionTrigger::Unknown;
			break;
		}

		// Event tag
		if (Transition.RequiredEvent.IsValid() && Transition.RequiredEvent.Tag.IsValid())
		{
			ExportedTransition.EventTag = Transition.RequiredEvent.Tag.ToString();
		}

		// Resolve target from FStateTreeStateLink. `LinkType` is authoritative —
		// `GotoState` is the only case where Name/ID actually identify a state.
		// Other values encode tree-level semantics (`Succeeded` / `Failed` exit
		// the subtree; `NextState` / `NextSelectableState` go to a sibling);
		// Name/ID on those links are typically empty. Pre-M5.3 we didn't read
		// LinkType and rendered those as `(unresolved)`, masquerading as bugs.
		if (Transition.State.ID.IsValid())
		{
			ExportedTransition.TargetStateGuid = Transition.State.ID.ToString();
		}
		switch (Transition.State.LinkType)
		{
		case EStateTreeTransitionType::None:                ExportedTransition.LinkType = TEXT("None"); break;
		case EStateTreeTransitionType::Succeeded:           ExportedTransition.LinkType = TEXT("Succeeded"); break;
		case EStateTreeTransitionType::Failed:              ExportedTransition.LinkType = TEXT("Failed"); break;
		case EStateTreeTransitionType::GotoState:           ExportedTransition.LinkType = TEXT("GotoState"); break;
		case EStateTreeTransitionType::NextState:           ExportedTransition.LinkType = TEXT("NextState"); break;
		case EStateTreeTransitionType::NextSelectableState: ExportedTransition.LinkType = TEXT("NextSelectableState"); break;
		default:                                            ExportedTransition.LinkType = TEXT("Unknown"); break;
		}

		const FString ResolvedName = Transition.State.Name.ToString();
		if (Transition.State.LinkType == EStateTreeTransitionType::GotoState)
		{
			// Only GotoState points at a named state. Resolve name → GUID → unresolved.
			if (!ResolvedName.IsEmpty() && ResolvedName != TEXT("None"))
			{
				ExportedTransition.TargetStateName = ResolvedName;
			}
			else if (Transition.State.ID.IsValid())
			{
				ExportedTransition.TargetStateName = FString::Printf(TEXT("(state:%s)"), *ExportedTransition.TargetStateGuid);
			}
			else
			{
				ExportedTransition.TargetStateName = TEXT("(unresolved)");
			}
		}
		else
		{
			// Semantic label for non-GotoState links — matches UE's editor vocabulary.
			switch (Transition.State.LinkType)
			{
			case EStateTreeTransitionType::Succeeded:           ExportedTransition.TargetStateName = TEXT("(tree succeeded)"); break;
			case EStateTreeTransitionType::Failed:              ExportedTransition.TargetStateName = TEXT("(tree failed)"); break;
			case EStateTreeTransitionType::NextState:           ExportedTransition.TargetStateName = TEXT("(next state)"); break;
			case EStateTreeTransitionType::NextSelectableState: ExportedTransition.TargetStateName = TEXT("(next selectable state)"); break;
			case EStateTreeTransitionType::None:                ExportedTransition.TargetStateName = TEXT("(no target)"); break;
			default:                                            ExportedTransition.TargetStateName = TEXT("(unknown link type)"); break;
			}
		}

		// Delay
		ExportedTransition.DelaySeconds = Transition.DelayDuration;
		ExportedTransition.bDelayIsRandom = Transition.DelayRandomVariance > 0.0f;
		ExportedTransition.DelayRandomDeviationSeconds = Transition.DelayRandomVariance;

		// Priority
		switch (Transition.Priority)
		{
		case EStateTreeTransitionPriority::Critical:
			ExportedTransition.Priority = TEXT("Critical");
			break;
		case EStateTreeTransitionPriority::High:
			ExportedTransition.Priority = TEXT("High");
			break;
		case EStateTreeTransitionPriority::Normal:
			ExportedTransition.Priority = TEXT("Normal");
			break;
		case EStateTreeTransitionPriority::Low:
			ExportedTransition.Priority = TEXT("Low");
			break;
		default:
			ExportedTransition.Priority = TEXT("Normal");
			break;
		}

		// Transition conditions
		for (const FStateTreeEditorNode& ConditionNode : Transition.Conditions)
		{
			ExportedTransition.Conditions.Add(SerializeEditorNode(ConditionNode, TEXT("Condition")));
		}

		ExportedTransitions.Add(ExportedTransition);
	}
#endif

	return ExportedTransitions;
}

TArray<FExportedStateTreeBinding> FStateTreeSerializer::SerializePropertyBindings(const UStateTreeEditorData* EditorData)
{
	TArray<FExportedStateTreeBinding> ExportedBindings;

#if WITH_STATETREE_SUPPORT
	if (!EditorData)
	{
		return ExportedBindings;
	}

	// Access the property binding data from editor data
	// UStateTreeEditorData stores bindings as FStateTreeEditorPropertyBindings
	const FStateTreeEditorPropertyBindings* EditorBindings = EditorData->GetPropertyEditorBindings();
	if (!EditorBindings) return ExportedBindings;

	for (const FStateTreePropertyPathBinding& PathBinding : EditorBindings->GetBindings())
	{
		FExportedStateTreeBinding ExportedBinding;
		ExportedBinding.SourcePath = PathBinding.GetSourcePath().ToString();
		ExportedBinding.TargetPath = PathBinding.GetTargetPath().ToString();
		ExportedBindings.Add(ExportedBinding);
	}
#endif

	return ExportedBindings;
}

TArray<FExportedDependency> FStateTreeSerializer::SerializeDependencies(const UStateTree* StateTree)
{
	TArray<FExportedDependency> Dependencies;

#if WITH_STATETREE_SUPPORT
	if (!StateTree)
	{
		return Dependencies;
	}

	// Get dependencies via asset registry
	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

	TArray<FAssetIdentifier> ReferencedAssets;
	FAssetIdentifier StateTreeIdentifier(StateTree->GetOutermost()->GetFName());
	AssetRegistry.GetDependencies(StateTreeIdentifier, ReferencedAssets);

	TSet<FString> ProcessedPaths;

	for (const FAssetIdentifier& AssetId : ReferencedAssets)
	{
		FString AssetPath = AssetId.PackageName.ToString();

		if (AssetPath.IsEmpty() || ProcessedPaths.Contains(AssetPath))
		{
			continue;
		}
		ProcessedPaths.Add(AssetPath);

		FExportedDependency Dep;
		Dep.AssetPath = AssetPath;
		Dep.AssetName = FPackageName::GetShortName(AssetPath);
		Dep.DependencyType = EExportDependencyType::Hard;
		Dep.bIsNativeClass = AssetPath.StartsWith(TEXT("/Script/"));
		Dep.bIsBlueprint = false;

		// Check if it's a Blueprint
		FAssetData AssetData = AssetRegistry.GetAssetByObjectPath(FSoftObjectPath(AssetPath));
		if (AssetData.IsValid())
		{
			if (AssetData.AssetClassPath == UBlueprint::StaticClass()->GetClassPathName())
			{
				Dep.bIsBlueprint = true;
			}
		}

		Dependencies.Add(Dep);
	}
#endif

	return Dependencies;
}

