// Copyright Epic Games, Inc. All Rights Reserved.

#include "Schema/StateTreeExportTypes.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Misc/SecureHash.h"

// Enum string conversion helpers
namespace
{
	FString StateTypeToString(EExportedStateTreeStateType Type)
	{
		switch (Type)
		{
		case EExportedStateTreeStateType::State: return TEXT("State");
		case EExportedStateTreeStateType::Group: return TEXT("Group");
		case EExportedStateTreeStateType::Linked: return TEXT("Linked");
		case EExportedStateTreeStateType::LinkedAsset: return TEXT("LinkedAsset");
		case EExportedStateTreeStateType::Subtree: return TEXT("Subtree");
		default: return TEXT("Unknown");
		}
	}

	EExportedStateTreeStateType StringToStateType(const FString& Str)
	{
		if (Str == TEXT("State")) return EExportedStateTreeStateType::State;
		if (Str == TEXT("Group")) return EExportedStateTreeStateType::Group;
		if (Str == TEXT("Linked")) return EExportedStateTreeStateType::Linked;
		if (Str == TEXT("LinkedAsset")) return EExportedStateTreeStateType::LinkedAsset;
		if (Str == TEXT("Subtree")) return EExportedStateTreeStateType::Subtree;
		return EExportedStateTreeStateType::Unknown;
	}

	FString TransitionTriggerToString(EExportedStateTreeTransitionTrigger Trigger)
	{
		switch (Trigger)
		{
		case EExportedStateTreeTransitionTrigger::OnStateCompleted: return TEXT("OnStateCompleted");
		case EExportedStateTreeTransitionTrigger::OnStateSucceeded: return TEXT("OnStateSucceeded");
		case EExportedStateTreeTransitionTrigger::OnStateFailed: return TEXT("OnStateFailed");
		case EExportedStateTreeTransitionTrigger::OnTick: return TEXT("OnTick");
		case EExportedStateTreeTransitionTrigger::OnEvent: return TEXT("OnEvent");
		default: return TEXT("Unknown");
		}
	}

	EExportedStateTreeTransitionTrigger StringToTransitionTrigger(const FString& Str)
	{
		if (Str == TEXT("OnStateCompleted")) return EExportedStateTreeTransitionTrigger::OnStateCompleted;
		if (Str == TEXT("OnStateSucceeded")) return EExportedStateTreeTransitionTrigger::OnStateSucceeded;
		if (Str == TEXT("OnStateFailed")) return EExportedStateTreeTransitionTrigger::OnStateFailed;
		if (Str == TEXT("OnTick")) return EExportedStateTreeTransitionTrigger::OnTick;
		if (Str == TEXT("OnEvent")) return EExportedStateTreeTransitionTrigger::OnEvent;
		return EExportedStateTreeTransitionTrigger::Unknown;
	}

	FString SelectionBehaviorToString(EExportedStateTreeSelectionBehavior Behavior)
	{
		switch (Behavior)
		{
		case EExportedStateTreeSelectionBehavior::None: return TEXT("None");
		case EExportedStateTreeSelectionBehavior::TryEnterState: return TEXT("TryEnterState");
		case EExportedStateTreeSelectionBehavior::TrySelectChildrenInOrder: return TEXT("TrySelectChildrenInOrder");
		case EExportedStateTreeSelectionBehavior::TryFollowTransitions: return TEXT("TryFollowTransitions");
		default: return TEXT("Unknown");
		}
	}

	EExportedStateTreeSelectionBehavior StringToSelectionBehavior(const FString& Str)
	{
		if (Str == TEXT("None")) return EExportedStateTreeSelectionBehavior::None;
		if (Str == TEXT("TryEnterState")) return EExportedStateTreeSelectionBehavior::TryEnterState;
		if (Str == TEXT("TrySelectChildrenInOrder")) return EExportedStateTreeSelectionBehavior::TrySelectChildrenInOrder;
		if (Str == TEXT("TryFollowTransitions")) return EExportedStateTreeSelectionBehavior::TryFollowTransitions;
		return EExportedStateTreeSelectionBehavior::Unknown;
	}
}

// FExportedStateTreeProperty
TSharedPtr<FJsonObject> FExportedStateTreeProperty::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("name"), Name);
	JsonObject->SetStringField(TEXT("type"), Type);
	JsonObject->SetStringField(TEXT("value"), Value);
	if (!Category.IsEmpty())
	{
		JsonObject->SetStringField(TEXT("category"), Category);
	}
	return JsonObject;
}

FExportedStateTreeProperty FExportedStateTreeProperty::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedStateTreeProperty Property;
	if (JsonObject.IsValid())
	{
		Property.Name = JsonObject->GetStringField(TEXT("name"));
		Property.Type = JsonObject->GetStringField(TEXT("type"));
		Property.Value = JsonObject->GetStringField(TEXT("value"));
		JsonObject->TryGetStringField(TEXT("category"), Property.Category);
	}
	return Property;
}

// FExportedStateTreeEditorNode
namespace
{
	// Emit a name-sorted property array into a JSON object under `FieldName`.
	// Only writes the field when the property list is non-empty, so pre-DeepDump
	// sidecars round-trip to byte-identical output for nodes that have no
	// instance data (keeps the canonical ProjectInventory_DOW diff minimal).
	void WriteSortedPropertiesField(
		const TSharedPtr<FJsonObject>& JsonObject,
		const TCHAR* FieldName,
		const TArray<FExportedStateTreeProperty>& Props)
	{
		if (Props.Num() == 0)
		{
			return;
		}
		TArray<FExportedStateTreeProperty> Sorted = Props;
		Sorted.Sort([](const FExportedStateTreeProperty& A, const FExportedStateTreeProperty& B)
		{
			return A.Name < B.Name;
		});
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const FExportedStateTreeProperty& Prop : Sorted)
		{
			Array.Add(MakeShareable(new FJsonValueObject(Prop.ToJson())));
		}
		JsonObject->SetArrayField(FieldName, Array);
	}

	void ReadPropertiesField(
		const TSharedPtr<FJsonObject>& JsonObject,
		const TCHAR* FieldName,
		TArray<FExportedStateTreeProperty>& OutProps)
	{
		const TArray<TSharedPtr<FJsonValue>>* Array = nullptr;
		if (JsonObject->TryGetArrayField(FieldName, Array))
		{
			for (const TSharedPtr<FJsonValue>& Value : *Array)
			{
				OutProps.Add(FExportedStateTreeProperty::FromJson(Value->AsObject()));
			}
		}
	}
}

TSharedPtr<FJsonObject> FExportedStateTreeEditorNode::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("name"), Name);
	JsonObject->SetStringField(TEXT("structType"), StructType);
	JsonObject->SetStringField(TEXT("category"), Category);
	if (!InstanceId.IsEmpty())
	{
		JsonObject->SetStringField(TEXT("instanceId"), InstanceId);
	}

	// Node struct properties (always written — keeps pre-DeepDump schema stable).
	TArray<FExportedStateTreeProperty> SortedProperties = Properties;
	SortedProperties.Sort([](const FExportedStateTreeProperty& A, const FExportedStateTreeProperty& B)
	{
		return A.Name < B.Name;
	});

	TArray<TSharedPtr<FJsonValue>> PropertiesArray;
	for (const FExportedStateTreeProperty& Prop : SortedProperties)
	{
		PropertiesArray.Add(MakeShareable(new FJsonValueObject(Prop.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("properties"), PropertiesArray);

	// Instance data (present for native task/condition/evaluator nodes with
	// struct-typed instance data) and instance object (present for BP-backed
	// nodes). Only written when non-empty so older callers / snapshots that
	// didn't capture this detail don't gain empty arrays.
	WriteSortedPropertiesField(JsonObject, TEXT("instanceProperties"), InstanceProperties);
	if (!InstanceObjectClass.IsEmpty())
	{
		JsonObject->SetStringField(TEXT("instanceObjectClass"), InstanceObjectClass);
	}
	WriteSortedPropertiesField(JsonObject, TEXT("instanceObjectProperties"), InstanceObjectProperties);

	return JsonObject;
}

FExportedStateTreeEditorNode FExportedStateTreeEditorNode::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedStateTreeEditorNode Node;
	if (JsonObject.IsValid())
	{
		Node.Name = JsonObject->GetStringField(TEXT("name"));
		Node.StructType = JsonObject->GetStringField(TEXT("structType"));
		Node.Category = JsonObject->GetStringField(TEXT("category"));
		JsonObject->TryGetStringField(TEXT("instanceId"), Node.InstanceId);

		ReadPropertiesField(JsonObject, TEXT("properties"), Node.Properties);
		ReadPropertiesField(JsonObject, TEXT("instanceProperties"), Node.InstanceProperties);
		JsonObject->TryGetStringField(TEXT("instanceObjectClass"), Node.InstanceObjectClass);
		ReadPropertiesField(JsonObject, TEXT("instanceObjectProperties"), Node.InstanceObjectProperties);
	}
	return Node;
}

// FExportedStateTreeBinding
TSharedPtr<FJsonObject> FExportedStateTreeBinding::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("sourcePath"), SourcePath);
	JsonObject->SetStringField(TEXT("targetPath"), TargetPath);
	return JsonObject;
}

FExportedStateTreeBinding FExportedStateTreeBinding::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedStateTreeBinding Binding;
	if (JsonObject.IsValid())
	{
		Binding.SourcePath = JsonObject->GetStringField(TEXT("sourcePath"));
		Binding.TargetPath = JsonObject->GetStringField(TEXT("targetPath"));
	}
	return Binding;
}

// FExportedStateTreeTransition
TSharedPtr<FJsonObject> FExportedStateTreeTransition::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("transitionId"), TransitionId);
	JsonObject->SetStringField(TEXT("trigger"), TransitionTriggerToString(Trigger));
	if (!EventTag.IsEmpty())
	{
		JsonObject->SetStringField(TEXT("eventTag"), EventTag);
	}
	JsonObject->SetStringField(TEXT("targetStateName"), TargetStateName);
	if (!TargetStateGuid.IsEmpty())
	{
		JsonObject->SetStringField(TEXT("targetStateGuid"), TargetStateGuid);
	}
	if (!LinkType.IsEmpty())
	{
		JsonObject->SetStringField(TEXT("linkType"), LinkType);
	}
	if (!Priority.IsEmpty())
	{
		JsonObject->SetStringField(TEXT("priority"), Priority);
	}
	if (DelaySeconds > 0.0f)
	{
		JsonObject->SetNumberField(TEXT("delaySeconds"), DelaySeconds);
		JsonObject->SetBoolField(TEXT("delayIsRandom"), bDelayIsRandom);
		if (bDelayIsRandom)
		{
			JsonObject->SetNumberField(TEXT("delayRandomDeviationSeconds"), DelayRandomDeviationSeconds);
		}
	}

	TArray<TSharedPtr<FJsonValue>> ConditionsArray;
	for (const FExportedStateTreeEditorNode& Condition : Conditions)
	{
		ConditionsArray.Add(MakeShareable(new FJsonValueObject(Condition.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("conditions"), ConditionsArray);

	return JsonObject;
}

FExportedStateTreeTransition FExportedStateTreeTransition::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedStateTreeTransition Transition;
	if (JsonObject.IsValid())
	{
		Transition.TransitionId = JsonObject->GetStringField(TEXT("transitionId"));
		Transition.Trigger = StringToTransitionTrigger(JsonObject->GetStringField(TEXT("trigger")));
		JsonObject->TryGetStringField(TEXT("eventTag"), Transition.EventTag);
		Transition.TargetStateName = JsonObject->GetStringField(TEXT("targetStateName"));
		JsonObject->TryGetStringField(TEXT("targetStateGuid"), Transition.TargetStateGuid);
		JsonObject->TryGetStringField(TEXT("linkType"), Transition.LinkType);
		JsonObject->TryGetStringField(TEXT("priority"), Transition.Priority);
		JsonObject->TryGetNumberField(TEXT("delaySeconds"), Transition.DelaySeconds);
		JsonObject->TryGetBoolField(TEXT("delayIsRandom"), Transition.bDelayIsRandom);
		JsonObject->TryGetNumberField(TEXT("delayRandomDeviationSeconds"), Transition.DelayRandomDeviationSeconds);

		const TArray<TSharedPtr<FJsonValue>>* ConditionsArray;
		if (JsonObject->TryGetArrayField(TEXT("conditions"), ConditionsArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *ConditionsArray)
			{
				Transition.Conditions.Add(FExportedStateTreeEditorNode::FromJson(Value->AsObject()));
			}
		}
	}
	return Transition;
}

// FExportedStateTreeState
TSharedPtr<FJsonObject> FExportedStateTreeState::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("name"), Name);
	JsonObject->SetStringField(TEXT("stateGuid"), StateGuid);
	JsonObject->SetStringField(TEXT("type"), StateTypeToString(Type));
	if (!Tag.IsEmpty())
	{
		JsonObject->SetStringField(TEXT("tag"), Tag);
	}
	JsonObject->SetStringField(TEXT("selectionBehavior"), SelectionBehaviorToString(SelectionBehavior));
	if (!LinkedAsset.IsEmpty())
	{
		JsonObject->SetStringField(TEXT("linkedAsset"), LinkedAsset);
	}
	if (!LinkedAssetPath.IsEmpty())
	{
		JsonObject->SetStringField(TEXT("linkedAssetPath"), LinkedAssetPath);
	}

	// Enter conditions
	TArray<TSharedPtr<FJsonValue>> EnterConditionsArray;
	for (const FExportedStateTreeEditorNode& Condition : EnterConditions)
	{
		EnterConditionsArray.Add(MakeShareable(new FJsonValueObject(Condition.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("enterConditions"), EnterConditionsArray);

	// Tasks
	TArray<TSharedPtr<FJsonValue>> TasksArray;
	for (const FExportedStateTreeEditorNode& Task : Tasks)
	{
		TasksArray.Add(MakeShareable(new FJsonValueObject(Task.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("tasks"), TasksArray);

	// Transitions - sort by ID for determinism
	TArray<FExportedStateTreeTransition> SortedTransitions = Transitions;
	SortedTransitions.Sort([](const FExportedStateTreeTransition& A, const FExportedStateTreeTransition& B)
	{
		return A.TransitionId < B.TransitionId;
	});

	TArray<TSharedPtr<FJsonValue>> TransitionsArray;
	for (const FExportedStateTreeTransition& Transition : SortedTransitions)
	{
		TransitionsArray.Add(MakeShareable(new FJsonValueObject(Transition.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("transitions"), TransitionsArray);

	// Children (recursive) - preserve author order (by index)
	TArray<TSharedPtr<FJsonValue>> ChildrenArray;
	for (const FExportedStateTreeState& Child : Children)
	{
		ChildrenArray.Add(MakeShareable(new FJsonValueObject(Child.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("children"), ChildrenArray);

	return JsonObject;
}

FExportedStateTreeState FExportedStateTreeState::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedStateTreeState State;
	if (JsonObject.IsValid())
	{
		State.Name = JsonObject->GetStringField(TEXT("name"));
		State.StateGuid = JsonObject->GetStringField(TEXT("stateGuid"));
		State.Type = StringToStateType(JsonObject->GetStringField(TEXT("type")));
		JsonObject->TryGetStringField(TEXT("tag"), State.Tag);
		State.SelectionBehavior = StringToSelectionBehavior(JsonObject->GetStringField(TEXT("selectionBehavior")));
		JsonObject->TryGetStringField(TEXT("linkedAsset"), State.LinkedAsset);
		JsonObject->TryGetStringField(TEXT("linkedAssetPath"), State.LinkedAssetPath);

		const TArray<TSharedPtr<FJsonValue>>* EnterConditionsArray;
		if (JsonObject->TryGetArrayField(TEXT("enterConditions"), EnterConditionsArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *EnterConditionsArray)
			{
				State.EnterConditions.Add(FExportedStateTreeEditorNode::FromJson(Value->AsObject()));
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* TasksArray;
		if (JsonObject->TryGetArrayField(TEXT("tasks"), TasksArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *TasksArray)
			{
				State.Tasks.Add(FExportedStateTreeEditorNode::FromJson(Value->AsObject()));
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* TransitionsArray;
		if (JsonObject->TryGetArrayField(TEXT("transitions"), TransitionsArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *TransitionsArray)
			{
				State.Transitions.Add(FExportedStateTreeTransition::FromJson(Value->AsObject()));
			}
		}

		// Recursive children
		const TArray<TSharedPtr<FJsonValue>>* ChildrenArray;
		if (JsonObject->TryGetArrayField(TEXT("children"), ChildrenArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *ChildrenArray)
			{
				State.Children.Add(FExportedStateTreeState::FromJson(Value->AsObject()));
			}
		}
	}
	return State;
}

// FExportedStateTree
TSharedPtr<FJsonObject> FExportedStateTree::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetObjectField(TEXT("exportInfo"), ExportInfo.ToJson());
	JsonObject->SetStringField(TEXT("assetPath"), AssetPath);
	JsonObject->SetStringField(TEXT("assetName"), AssetName);
	JsonObject->SetStringField(TEXT("schema"), Schema);

	// Evaluators
	TArray<TSharedPtr<FJsonValue>> EvaluatorsArray;
	for (const FExportedStateTreeEditorNode& Evaluator : Evaluators)
	{
		EvaluatorsArray.Add(MakeShareable(new FJsonValueObject(Evaluator.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("evaluators"), EvaluatorsArray);

	// Global tasks
	TArray<TSharedPtr<FJsonValue>> GlobalTasksArray;
	for (const FExportedStateTreeEditorNode& Task : GlobalTasks)
	{
		GlobalTasksArray.Add(MakeShareable(new FJsonValueObject(Task.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("globalTasks"), GlobalTasksArray);

	// Root states - preserve author order
	TArray<TSharedPtr<FJsonValue>> RootStatesArray;
	for (const FExportedStateTreeState& State : RootStates)
	{
		RootStatesArray.Add(MakeShareable(new FJsonValueObject(State.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("rootStates"), RootStatesArray);

	// Bindings - sort by target path for determinism
	TArray<FExportedStateTreeBinding> SortedBindings = Bindings;
	SortedBindings.Sort([](const FExportedStateTreeBinding& A, const FExportedStateTreeBinding& B)
	{
		if (A.TargetPath != B.TargetPath) return A.TargetPath < B.TargetPath;
		return A.SourcePath < B.SourcePath;
	});

	TArray<TSharedPtr<FJsonValue>> BindingsArray;
	for (const FExportedStateTreeBinding& Binding : SortedBindings)
	{
		BindingsArray.Add(MakeShareable(new FJsonValueObject(Binding.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("bindings"), BindingsArray);

	// Dependencies - sort by path
	TArray<FExportedDependency> SortedDeps = Dependencies;
	SortedDeps.Sort([](const FExportedDependency& A, const FExportedDependency& B)
	{
		return A.AssetPath < B.AssetPath;
	});

	TArray<TSharedPtr<FJsonValue>> DepsArray;
	for (const FExportedDependency& Dep : SortedDeps)
	{
		DepsArray.Add(MakeShareable(new FJsonValueObject(Dep.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("dependencies"), DepsArray);

	return JsonObject;
}

FExportedStateTree FExportedStateTree::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedStateTree StateTree;
	if (JsonObject.IsValid())
	{
		StateTree.ExportInfo = FExportInfo::FromJson(JsonObject->GetObjectField(TEXT("exportInfo")));
		StateTree.AssetPath = JsonObject->GetStringField(TEXT("assetPath"));
		StateTree.AssetName = JsonObject->GetStringField(TEXT("assetName"));
		StateTree.Schema = JsonObject->GetStringField(TEXT("schema"));

		const TArray<TSharedPtr<FJsonValue>>* EvaluatorsArray;
		if (JsonObject->TryGetArrayField(TEXT("evaluators"), EvaluatorsArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *EvaluatorsArray)
			{
				StateTree.Evaluators.Add(FExportedStateTreeEditorNode::FromJson(Value->AsObject()));
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* GlobalTasksArray;
		if (JsonObject->TryGetArrayField(TEXT("globalTasks"), GlobalTasksArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *GlobalTasksArray)
			{
				StateTree.GlobalTasks.Add(FExportedStateTreeEditorNode::FromJson(Value->AsObject()));
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* RootStatesArray;
		if (JsonObject->TryGetArrayField(TEXT("rootStates"), RootStatesArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *RootStatesArray)
			{
				StateTree.RootStates.Add(FExportedStateTreeState::FromJson(Value->AsObject()));
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* BindingsArray;
		if (JsonObject->TryGetArrayField(TEXT("bindings"), BindingsArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *BindingsArray)
			{
				StateTree.Bindings.Add(FExportedStateTreeBinding::FromJson(Value->AsObject()));
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* DepsArray;
		if (JsonObject->TryGetArrayField(TEXT("dependencies"), DepsArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *DepsArray)
			{
				StateTree.Dependencies.Add(FExportedDependency::FromJson(Value->AsObject()));
			}
		}
	}
	return StateTree;
}

FString FExportedStateTree::ComputeContentHash() const
{
	FExportedStateTree HashCopy = *this;
	HashCopy.ExportInfo.ExportTimestamp = TEXT("");
	HashCopy.ExportInfo.ContentHash = TEXT("");

	TSharedPtr<FJsonObject> JsonObject = HashCopy.ToJson();
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	return FMD5::HashAnsiString(*JsonString);
}
