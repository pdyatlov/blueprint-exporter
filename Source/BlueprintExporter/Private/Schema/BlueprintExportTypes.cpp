// Copyright Epic Games, Inc. All Rights Reserved.

#include "Schema/BlueprintExportTypes.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Misc/FileHelper.h"
#include "Misc/SecureHash.h"

// Helper to convert enum to string
namespace
{
	FString PinDirectionToString(EExportPinDirection Direction)
	{
		return Direction == EExportPinDirection::Input ? TEXT("Input") : TEXT("Output");
	}

	EExportPinDirection StringToPinDirection(const FString& Str)
	{
		return Str == TEXT("Output") ? EExportPinDirection::Output : EExportPinDirection::Input;
	}

	FString DependencyTypeToString(EExportDependencyType Type)
	{
		return Type == EExportDependencyType::Soft ? TEXT("Soft") : TEXT("Hard");
	}

	EExportDependencyType StringToDependencyType(const FString& Str)
	{
		return Str == TEXT("Soft") ? EExportDependencyType::Soft : EExportDependencyType::Hard;
	}

	FString BlueprintTypeToString(EBlueprintExportType Type)
	{
		switch (Type)
		{
		case EBlueprintExportType::Normal: return TEXT("Normal");
		case EBlueprintExportType::Const: return TEXT("Const");
		case EBlueprintExportType::MacroLibrary: return TEXT("MacroLibrary");
		case EBlueprintExportType::Interface: return TEXT("Interface");
		case EBlueprintExportType::LevelScript: return TEXT("LevelScript");
		case EBlueprintExportType::FunctionLibrary: return TEXT("FunctionLibrary");
		default: return TEXT("Unknown");
		}
	}

	EBlueprintExportType StringToBlueprintType(const FString& Str)
	{
		if (Str == TEXT("Normal")) return EBlueprintExportType::Normal;
		if (Str == TEXT("Const")) return EBlueprintExportType::Const;
		if (Str == TEXT("MacroLibrary")) return EBlueprintExportType::MacroLibrary;
		if (Str == TEXT("Interface")) return EBlueprintExportType::Interface;
		if (Str == TEXT("LevelScript")) return EBlueprintExportType::LevelScript;
		if (Str == TEXT("FunctionLibrary")) return EBlueprintExportType::FunctionLibrary;
		return EBlueprintExportType::Unknown;
	}

	FString DiffChangeTypeToString(EBlueprintDiffChangeType Type)
	{
		switch (Type)
		{
		case EBlueprintDiffChangeType::Added: return TEXT("Added");
		case EBlueprintDiffChangeType::Removed: return TEXT("Removed");
		case EBlueprintDiffChangeType::Modified: return TEXT("Modified");
		case EBlueprintDiffChangeType::Moved: return TEXT("Moved");
		case EBlueprintDiffChangeType::TypeChanged: return TEXT("TypeChanged");
		case EBlueprintDiffChangeType::ConnectionChanged: return TEXT("ConnectionChanged");
		default: return TEXT("Modified");
		}
	}

	TSharedPtr<FJsonObject> MapToJson(const TMap<FString, FString>& Map)
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		TArray<FString> Keys;
		Map.GetKeys(Keys);
		Keys.Sort();
		for (const FString& Key : Keys)
		{
			JsonObject->SetStringField(Key, Map[Key]);
		}
		return JsonObject;
	}

	TMap<FString, FString> JsonToMap(const TSharedPtr<FJsonObject>& JsonObject)
	{
		TMap<FString, FString> Map;
		if (JsonObject.IsValid())
		{
			for (const auto& Pair : JsonObject->Values)
			{
				Map.Add(Pair.Key, Pair.Value->AsString());
			}
		}
		return Map;
	}
}

// FExportedPinType
TSharedPtr<FJsonObject> FExportedPinType::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("category"), Category);
	JsonObject->SetStringField(TEXT("subCategoryObject"), SubCategoryObject);
	JsonObject->SetStringField(TEXT("pinSubCategory"), PinSubCategory);
	JsonObject->SetBoolField(TEXT("isArray"), bIsArray);
	JsonObject->SetBoolField(TEXT("isSet"), bIsSet);
	JsonObject->SetBoolField(TEXT("isMap"), bIsMap);
	JsonObject->SetBoolField(TEXT("isReference"), bIsReference);
	JsonObject->SetBoolField(TEXT("isConst"), bIsConst);
	JsonObject->SetBoolField(TEXT("isWeakPointer"), bIsWeakPointer);
	if (!ValueTerminalType.IsEmpty())
	{
		JsonObject->SetStringField(TEXT("valueTerminalType"), ValueTerminalType);
	}
	// Include error information if present
	if (bHasBrokenReference)
	{
		JsonObject->SetBoolField(TEXT("hasBrokenReference"), bHasBrokenReference);
		JsonObject->SetStringField(TEXT("brokenReferenceInfo"), BrokenReferenceInfo);
	}
	// Emit subCategoryObjectResolved only when false, so AI consumers can distinguish
	// "no subtype" from "subtype blanked defensively". Absence of the field means
	// resolved (matches the default). Keeps existing exports byte-identical.
	if (!bSubCategoryObjectResolved)
	{
		JsonObject->SetBoolField(TEXT("subCategoryObjectResolved"), false);
	}
	return JsonObject;
}

FExportedPinType FExportedPinType::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedPinType PinType;
	if (JsonObject.IsValid())
	{
		PinType.Category = JsonObject->GetStringField(TEXT("category"));
		PinType.SubCategoryObject = JsonObject->GetStringField(TEXT("subCategoryObject"));
		PinType.PinSubCategory = JsonObject->GetStringField(TEXT("pinSubCategory"));
		PinType.bIsArray = JsonObject->GetBoolField(TEXT("isArray"));
		PinType.bIsSet = JsonObject->GetBoolField(TEXT("isSet"));
		PinType.bIsMap = JsonObject->GetBoolField(TEXT("isMap"));
		PinType.bIsReference = JsonObject->GetBoolField(TEXT("isReference"));
		PinType.bIsConst = JsonObject->GetBoolField(TEXT("isConst"));
		PinType.bIsWeakPointer = JsonObject->GetBoolField(TEXT("isWeakPointer"));
		JsonObject->TryGetStringField(TEXT("valueTerminalType"), PinType.ValueTerminalType);
		JsonObject->TryGetBoolField(TEXT("hasBrokenReference"), PinType.bHasBrokenReference);
		JsonObject->TryGetStringField(TEXT("brokenReferenceInfo"), PinType.BrokenReferenceInfo);
		// TryGetBoolField leaves the target untouched if the field is absent, so older
		// JSON without this field stays at the default (true = resolved).
		JsonObject->TryGetBoolField(TEXT("subCategoryObjectResolved"), PinType.bSubCategoryObjectResolved);
	}
	return PinType;
}

// FExportedPinConnection
TSharedPtr<FJsonObject> FExportedPinConnection::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("nodeId"), NodeId);
	JsonObject->SetStringField(TEXT("pinId"), PinId);
	return JsonObject;
}

FExportedPinConnection FExportedPinConnection::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedPinConnection Connection;
	if (JsonObject.IsValid())
	{
		Connection.NodeId = JsonObject->GetStringField(TEXT("nodeId"));
		Connection.PinId = JsonObject->GetStringField(TEXT("pinId"));
	}
	return Connection;
}

// FExportedPin
TSharedPtr<FJsonObject> FExportedPin::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("pinId"), PinId);
	JsonObject->SetStringField(TEXT("pinName"), PinName);
	JsonObject->SetStringField(TEXT("pinFriendlyName"), PinFriendlyName);
	JsonObject->SetStringField(TEXT("direction"), PinDirectionToString(Direction));
	JsonObject->SetObjectField(TEXT("type"), PinType.ToJson());
	JsonObject->SetStringField(TEXT("defaultValue"), DefaultValue);
	JsonObject->SetStringField(TEXT("autogeneratedDefaultValue"), AutogeneratedDefaultValue);
	JsonObject->SetBoolField(TEXT("hidden"), bHidden);
	JsonObject->SetBoolField(TEXT("notConnectable"), bNotConnectable);
	JsonObject->SetBoolField(TEXT("advancedView"), bAdvancedView);

	TArray<TSharedPtr<FJsonValue>> ConnectionsArray;
	for (const FExportedPinConnection& Connection : Connections)
	{
		ConnectionsArray.Add(MakeShareable(new FJsonValueObject(Connection.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("connections"), ConnectionsArray);

	// Include error information if present
	if (bHasError)
	{
		JsonObject->SetBoolField(TEXT("hasError"), bHasError);
		JsonObject->SetStringField(TEXT("errorMessage"), ErrorMessage);
	}

	return JsonObject;
}

FExportedPin FExportedPin::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedPin Pin;
	if (JsonObject.IsValid())
	{
		Pin.PinId = JsonObject->GetStringField(TEXT("pinId"));
		Pin.PinName = JsonObject->GetStringField(TEXT("pinName"));
		Pin.PinFriendlyName = JsonObject->GetStringField(TEXT("pinFriendlyName"));
		Pin.Direction = StringToPinDirection(JsonObject->GetStringField(TEXT("direction")));
		Pin.PinType = FExportedPinType::FromJson(JsonObject->GetObjectField(TEXT("type")));
		Pin.DefaultValue = JsonObject->GetStringField(TEXT("defaultValue"));
		Pin.AutogeneratedDefaultValue = JsonObject->GetStringField(TEXT("autogeneratedDefaultValue"));
		Pin.bHidden = JsonObject->GetBoolField(TEXT("hidden"));
		Pin.bNotConnectable = JsonObject->GetBoolField(TEXT("notConnectable"));
		Pin.bAdvancedView = JsonObject->GetBoolField(TEXT("advancedView"));

		const TArray<TSharedPtr<FJsonValue>>* ConnectionsArray;
		if (JsonObject->TryGetArrayField(TEXT("connections"), ConnectionsArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *ConnectionsArray)
			{
				Pin.Connections.Add(FExportedPinConnection::FromJson(Value->AsObject()));
			}
		}

		// Read error information if present
		JsonObject->TryGetBoolField(TEXT("hasError"), Pin.bHasError);
		JsonObject->TryGetStringField(TEXT("errorMessage"), Pin.ErrorMessage);
	}
	return Pin;
}

// FExportedNode
TSharedPtr<FJsonObject> FExportedNode::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("nodeId"), NodeId);
	JsonObject->SetStringField(TEXT("nodeGuid"), NodeGuid);
	JsonObject->SetStringField(TEXT("nodeClass"), NodeClass);
	JsonObject->SetStringField(TEXT("nodeTitle"), NodeTitle);
	JsonObject->SetStringField(TEXT("nodeType"), NodeType);
	JsonObject->SetNumberField(TEXT("positionX"), PositionX);
	JsonObject->SetNumberField(TEXT("positionY"), PositionY);
	JsonObject->SetStringField(TEXT("comment"), Comment);
	JsonObject->SetBoolField(TEXT("commentBubbleVisible"), bCommentBubbleVisible);
	JsonObject->SetBoolField(TEXT("commentBubblePinned"), bCommentBubblePinned);
	JsonObject->SetStringField(TEXT("nodeColor"), NodeColor);

	TArray<TSharedPtr<FJsonValue>> PinsArray;
	// Sort pins by name for determinism
	TArray<FExportedPin> SortedPins = Pins;
	SortedPins.Sort([](const FExportedPin& A, const FExportedPin& B) {
		if (A.Direction != B.Direction)
		{
			return A.Direction < B.Direction;
		}
		return A.PinName < B.PinName;
	});
	for (const FExportedPin& Pin : SortedPins)
	{
		PinsArray.Add(MakeShareable(new FJsonValueObject(Pin.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("pins"), PinsArray);

	if (!NodeSpecificData.IsEmpty())
	{
		TSharedPtr<FJsonObject> SpecificDataObj;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(NodeSpecificData);
		if (FJsonSerializer::Deserialize(Reader, SpecificDataObj))
		{
			JsonObject->SetObjectField(TEXT("nodeSpecificData"), SpecificDataObj);
		}
	}

	return JsonObject;
}

FExportedNode FExportedNode::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedNode Node;
	if (JsonObject.IsValid())
	{
		Node.NodeId = JsonObject->GetStringField(TEXT("nodeId"));
		Node.NodeGuid = JsonObject->GetStringField(TEXT("nodeGuid"));
		Node.NodeClass = JsonObject->GetStringField(TEXT("nodeClass"));
		Node.NodeTitle = JsonObject->GetStringField(TEXT("nodeTitle"));
		Node.NodeType = JsonObject->GetStringField(TEXT("nodeType"));
		Node.PositionX = JsonObject->GetIntegerField(TEXT("positionX"));
		Node.PositionY = JsonObject->GetIntegerField(TEXT("positionY"));
		Node.Comment = JsonObject->GetStringField(TEXT("comment"));
		Node.bCommentBubbleVisible = JsonObject->GetBoolField(TEXT("commentBubbleVisible"));
		Node.bCommentBubblePinned = JsonObject->GetBoolField(TEXT("commentBubblePinned"));
		Node.NodeColor = JsonObject->GetStringField(TEXT("nodeColor"));

		const TArray<TSharedPtr<FJsonValue>>* PinsArray;
		if (JsonObject->TryGetArrayField(TEXT("pins"), PinsArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *PinsArray)
			{
				Node.Pins.Add(FExportedPin::FromJson(Value->AsObject()));
			}
		}

		const TSharedPtr<FJsonObject>* SpecificDataObj;
		if (JsonObject->TryGetObjectField(TEXT("nodeSpecificData"), SpecificDataObj))
		{
			FString OutputString;
			TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
			FJsonSerializer::Serialize(SpecificDataObj->ToSharedRef(), Writer);
			Node.NodeSpecificData = OutputString;
		}
	}
	return Node;
}

// FExportedGraph
TSharedPtr<FJsonObject> FExportedGraph::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("graphName"), GraphName);
	JsonObject->SetStringField(TEXT("graphGuid"), GraphGuid);
	JsonObject->SetStringField(TEXT("graphType"), GraphType);
	JsonObject->SetStringField(TEXT("schemaClass"), SchemaClass);

	// Sort nodes by position for determinism (top-left to bottom-right), with NodeGuid tiebreaker
	TArray<FExportedNode> SortedNodes = Nodes;
	SortedNodes.Sort([](const FExportedNode& A, const FExportedNode& B) {
		if (A.PositionY != B.PositionY)
		{
			return A.PositionY < B.PositionY;
		}
		if (A.PositionX != B.PositionX)
		{
			return A.PositionX < B.PositionX;
		}
		return A.NodeGuid < B.NodeGuid;
	});

	TArray<TSharedPtr<FJsonValue>> NodesArray;
	for (const FExportedNode& Node : SortedNodes)
	{
		NodesArray.Add(MakeShareable(new FJsonValueObject(Node.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("nodes"), NodesArray);

	return JsonObject;
}

FExportedGraph FExportedGraph::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedGraph Graph;
	if (JsonObject.IsValid())
	{
		Graph.GraphName = JsonObject->GetStringField(TEXT("graphName"));
		Graph.GraphGuid = JsonObject->GetStringField(TEXT("graphGuid"));
		Graph.GraphType = JsonObject->GetStringField(TEXT("graphType"));
		Graph.SchemaClass = JsonObject->GetStringField(TEXT("schemaClass"));

		const TArray<TSharedPtr<FJsonValue>>* NodesArray;
		if (JsonObject->TryGetArrayField(TEXT("nodes"), NodesArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *NodesArray)
			{
				Graph.Nodes.Add(FExportedNode::FromJson(Value->AsObject()));
			}
		}
	}
	return Graph;
}

// FExportedVariableFlags
TSharedPtr<FJsonObject> FExportedVariableFlags::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetBoolField(TEXT("instanceEditable"), bInstanceEditable);
	JsonObject->SetBoolField(TEXT("blueprintReadOnly"), bBlueprintReadOnly);
	JsonObject->SetBoolField(TEXT("exposeOnSpawn"), bExposeOnSpawn);
	JsonObject->SetBoolField(TEXT("private"), bPrivate);
	JsonObject->SetBoolField(TEXT("exposeToCinematics"), bExposeToCinematics);
	JsonObject->SetBoolField(TEXT("replicated"), bReplicated);
	JsonObject->SetStringField(TEXT("replicationCondition"), ReplicationCondition);
	JsonObject->SetBoolField(TEXT("repNotify"), bRepNotify);
	JsonObject->SetStringField(TEXT("repNotifyFunc"), RepNotifyFunc);
	return JsonObject;
}

FExportedVariableFlags FExportedVariableFlags::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedVariableFlags Flags;
	if (JsonObject.IsValid())
	{
		Flags.bInstanceEditable = JsonObject->GetBoolField(TEXT("instanceEditable"));
		Flags.bBlueprintReadOnly = JsonObject->GetBoolField(TEXT("blueprintReadOnly"));
		Flags.bExposeOnSpawn = JsonObject->GetBoolField(TEXT("exposeOnSpawn"));
		Flags.bPrivate = JsonObject->GetBoolField(TEXT("private"));
		Flags.bExposeToCinematics = JsonObject->GetBoolField(TEXT("exposeToCinematics"));
		Flags.bReplicated = JsonObject->GetBoolField(TEXT("replicated"));
		JsonObject->TryGetStringField(TEXT("replicationCondition"), Flags.ReplicationCondition);
		// Optional — absent from exports produced before schema v1.12 — default false / empty.
		JsonObject->TryGetBoolField(TEXT("repNotify"), Flags.bRepNotify);
		JsonObject->TryGetStringField(TEXT("repNotifyFunc"), Flags.RepNotifyFunc);
	}
	return Flags;
}

// FExportedVariable
TSharedPtr<FJsonObject> FExportedVariable::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("variableName"), VariableName);
	JsonObject->SetStringField(TEXT("variableGuid"), VariableGuid);
	JsonObject->SetObjectField(TEXT("variableType"), VariableType.ToJson());
	JsonObject->SetStringField(TEXT("defaultValue"), DefaultValue);
	JsonObject->SetStringField(TEXT("category"), Category);
	JsonObject->SetObjectField(TEXT("flags"), Flags.ToJson());
	JsonObject->SetStringField(TEXT("toolTip"), ToolTip);
	JsonObject->SetObjectField(TEXT("metaData"), MapToJson(MetaData));
	return JsonObject;
}

FExportedVariable FExportedVariable::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedVariable Variable;
	if (JsonObject.IsValid())
	{
		Variable.VariableName = JsonObject->GetStringField(TEXT("variableName"));
		Variable.VariableGuid = JsonObject->GetStringField(TEXT("variableGuid"));
		Variable.VariableType = FExportedPinType::FromJson(JsonObject->GetObjectField(TEXT("variableType")));
		Variable.DefaultValue = JsonObject->GetStringField(TEXT("defaultValue"));
		Variable.Category = JsonObject->GetStringField(TEXT("category"));
		Variable.Flags = FExportedVariableFlags::FromJson(JsonObject->GetObjectField(TEXT("flags")));
		Variable.ToolTip = JsonObject->GetStringField(TEXT("toolTip"));

		const TSharedPtr<FJsonObject>* MetaDataObj;
		if (JsonObject->TryGetObjectField(TEXT("metaData"), MetaDataObj))
		{
			Variable.MetaData = JsonToMap(*MetaDataObj);
		}
	}
	return Variable;
}

// FExportedFunctionParam
TSharedPtr<FJsonObject> FExportedFunctionParam::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("paramName"), ParamName);
	JsonObject->SetObjectField(TEXT("paramType"), ParamType.ToJson());
	JsonObject->SetStringField(TEXT("defaultValue"), DefaultValue);
	JsonObject->SetBoolField(TEXT("isOutput"), bIsOutput);
	JsonObject->SetBoolField(TEXT("passByReference"), bPassByReference);
	return JsonObject;
}

FExportedFunctionParam FExportedFunctionParam::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedFunctionParam Param;
	if (JsonObject.IsValid())
	{
		Param.ParamName = JsonObject->GetStringField(TEXT("paramName"));
		Param.ParamType = FExportedPinType::FromJson(JsonObject->GetObjectField(TEXT("paramType")));
		Param.DefaultValue = JsonObject->GetStringField(TEXT("defaultValue"));
		Param.bIsOutput = JsonObject->GetBoolField(TEXT("isOutput"));
		Param.bPassByReference = JsonObject->GetBoolField(TEXT("passByReference"));
	}
	return Param;
}

// FExportedFunctionFlags
TSharedPtr<FJsonObject> FExportedFunctionFlags::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetBoolField(TEXT("pure"), bPure);
	JsonObject->SetBoolField(TEXT("const"), bConst);
	JsonObject->SetBoolField(TEXT("static"), bStatic);
	JsonObject->SetBoolField(TEXT("callInEditor"), bCallInEditor);
	JsonObject->SetBoolField(TEXT("override"), bOverride);
	JsonObject->SetBoolField(TEXT("event"), bEvent);
	JsonObject->SetStringField(TEXT("accessSpecifier"), AccessSpecifier);
	JsonObject->SetBoolField(TEXT("server"), bServer);
	JsonObject->SetBoolField(TEXT("client"), bClient);
	JsonObject->SetBoolField(TEXT("netMulticast"), bNetMulticast);
	JsonObject->SetBoolField(TEXT("reliable"), bReliable);
	JsonObject->SetBoolField(TEXT("blueprintAuthorityOnly"), bBlueprintAuthorityOnly);
	JsonObject->SetBoolField(TEXT("blueprintCosmetic"), bBlueprintCosmetic);
	return JsonObject;
}

FExportedFunctionFlags FExportedFunctionFlags::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedFunctionFlags Flags;
	if (JsonObject.IsValid())
	{
		Flags.bPure = JsonObject->GetBoolField(TEXT("pure"));
		Flags.bConst = JsonObject->GetBoolField(TEXT("const"));
		Flags.bStatic = JsonObject->GetBoolField(TEXT("static"));
		Flags.bCallInEditor = JsonObject->GetBoolField(TEXT("callInEditor"));
		Flags.bOverride = JsonObject->GetBoolField(TEXT("override"));
		Flags.bEvent = JsonObject->GetBoolField(TEXT("event"));
		JsonObject->TryGetStringField(TEXT("accessSpecifier"), Flags.AccessSpecifier);
		JsonObject->TryGetBoolField(TEXT("server"), Flags.bServer);
		JsonObject->TryGetBoolField(TEXT("client"), Flags.bClient);
		JsonObject->TryGetBoolField(TEXT("netMulticast"), Flags.bNetMulticast);
		JsonObject->TryGetBoolField(TEXT("reliable"), Flags.bReliable);
		JsonObject->TryGetBoolField(TEXT("blueprintAuthorityOnly"), Flags.bBlueprintAuthorityOnly);
		JsonObject->TryGetBoolField(TEXT("blueprintCosmetic"), Flags.bBlueprintCosmetic);
	}
	return Flags;
}

// FExportedFunction
TSharedPtr<FJsonObject> FExportedFunction::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("functionName"), FunctionName);
	JsonObject->SetStringField(TEXT("functionGuid"), FunctionGuid);
	JsonObject->SetObjectField(TEXT("flags"), Flags.ToJson());

	TArray<TSharedPtr<FJsonValue>> InputsArray;
	for (const FExportedFunctionParam& Input : Inputs)
	{
		InputsArray.Add(MakeShareable(new FJsonValueObject(Input.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("inputs"), InputsArray);

	TArray<TSharedPtr<FJsonValue>> OutputsArray;
	for (const FExportedFunctionParam& Output : Outputs)
	{
		OutputsArray.Add(MakeShareable(new FJsonValueObject(Output.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("outputs"), OutputsArray);

	TArray<TSharedPtr<FJsonValue>> LocalVarsArray;
	for (const FExportedVariable& LocalVar : LocalVariables)
	{
		LocalVarsArray.Add(MakeShareable(new FJsonValueObject(LocalVar.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("localVariables"), LocalVarsArray);

	JsonObject->SetStringField(TEXT("description"), Description);

	TArray<TSharedPtr<FJsonValue>> KeywordsArray;
	for (const FString& Keyword : Keywords)
	{
		KeywordsArray.Add(MakeShareable(new FJsonValueString(Keyword)));
	}
	JsonObject->SetArrayField(TEXT("keywords"), KeywordsArray);

	JsonObject->SetStringField(TEXT("category"), Category);
	JsonObject->SetObjectField(TEXT("graph"), Graph.ToJson());

	// M26.1.1 — emit interface-override flags only when true to keep the
	// common-case JSON (regular FunctionGraphs functions) byte-identical.
	// Non-default fields suppressed on the output-serialization side; the
	// FromJson path tolerates absence (see default initializers in the
	// schema).
	if (bIsInterfaceOverride)
	{
		JsonObject->SetBoolField(TEXT("isInterfaceOverride"), true);
		if (!InterfaceClassPath.IsEmpty())
		{
			JsonObject->SetStringField(TEXT("interfaceClassPath"), InterfaceClassPath);
		}
	}

	return JsonObject;
}

FExportedFunction FExportedFunction::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedFunction Function;
	if (JsonObject.IsValid())
	{
		Function.FunctionName = JsonObject->GetStringField(TEXT("functionName"));
		Function.FunctionGuid = JsonObject->GetStringField(TEXT("functionGuid"));
		Function.Flags = FExportedFunctionFlags::FromJson(JsonObject->GetObjectField(TEXT("flags")));

		const TArray<TSharedPtr<FJsonValue>>* InputsArray;
		if (JsonObject->TryGetArrayField(TEXT("inputs"), InputsArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *InputsArray)
			{
				Function.Inputs.Add(FExportedFunctionParam::FromJson(Value->AsObject()));
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* OutputsArray;
		if (JsonObject->TryGetArrayField(TEXT("outputs"), OutputsArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *OutputsArray)
			{
				Function.Outputs.Add(FExportedFunctionParam::FromJson(Value->AsObject()));
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* LocalVarsArray;
		if (JsonObject->TryGetArrayField(TEXT("localVariables"), LocalVarsArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *LocalVarsArray)
			{
				Function.LocalVariables.Add(FExportedVariable::FromJson(Value->AsObject()));
			}
		}

		Function.Description = JsonObject->GetStringField(TEXT("description"));

		const TArray<TSharedPtr<FJsonValue>>* KeywordsArray;
		if (JsonObject->TryGetArrayField(TEXT("keywords"), KeywordsArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *KeywordsArray)
			{
				Function.Keywords.Add(Value->AsString());
			}
		}

		Function.Category = JsonObject->GetStringField(TEXT("category"));
		Function.Graph = FExportedGraph::FromJson(JsonObject->GetObjectField(TEXT("graph")));

		// M26.1.1 — interface-override fields are omitted from non-override
		// exports, so read defensively.
		JsonObject->TryGetBoolField(TEXT("isInterfaceOverride"), Function.bIsInterfaceOverride);
		JsonObject->TryGetStringField(TEXT("interfaceClassPath"), Function.InterfaceClassPath);
	}
	return Function;
}

// FExportedComponentProperty
TSharedPtr<FJsonObject> FExportedComponentProperty::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("propertyName"), PropertyName);
	JsonObject->SetStringField(TEXT("propertyType"), PropertyType);
	JsonObject->SetStringField(TEXT("value"), Value);
	// Emit instanced-subobject structure only when present so ordinary properties
	// produce byte-identical JSON to pre-1.10 exports.
	if (bIsInstancedSubobject)
	{
		JsonObject->SetBoolField(TEXT("bIsInstancedSubobject"), true);
		if (SubobjectJsonValues.Num() > 0)
		{
			JsonObject->SetArrayField(TEXT("subobjects"), SubobjectJsonValues);
		}
	}
	return JsonObject;
}

FExportedComponentProperty FExportedComponentProperty::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedComponentProperty Property;
	if (JsonObject.IsValid())
	{
		Property.PropertyName = JsonObject->GetStringField(TEXT("propertyName"));
		Property.PropertyType = JsonObject->GetStringField(TEXT("propertyType"));
		Property.Value = JsonObject->GetStringField(TEXT("value"));
		JsonObject->TryGetBoolField(TEXT("bIsInstancedSubobject"), Property.bIsInstancedSubobject);
		const TArray<TSharedPtr<FJsonValue>>* SubobjectsArray = nullptr;
		if (JsonObject->TryGetArrayField(TEXT("subobjects"), SubobjectsArray) && SubobjectsArray)
		{
			Property.SubobjectJsonValues = *SubobjectsArray;
		}
	}
	return Property;
}

// FExportedComponent
TSharedPtr<FJsonObject> FExportedComponent::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("componentName"), ComponentName);
	JsonObject->SetStringField(TEXT("componentClass"), ComponentClass);
	JsonObject->SetStringField(TEXT("parentComponentName"), ParentComponentName);
	JsonObject->SetBoolField(TEXT("isRootComponent"), bIsRootComponent);
	JsonObject->SetStringField(TEXT("attachSocketName"), AttachSocketName);

	TArray<TSharedPtr<FJsonValue>> PropertiesArray;
	for (const FExportedComponentProperty& Property : Properties)
	{
		PropertiesArray.Add(MakeShareable(new FJsonValueObject(Property.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("properties"), PropertiesArray);

	TArray<TSharedPtr<FJsonValue>> ChildrenArray;
	for (const FExportedComponent& Child : ChildComponents)
	{
		ChildrenArray.Add(MakeShareable(new FJsonValueObject(Child.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("childComponents"), ChildrenArray);

	return JsonObject;
}

FExportedComponent FExportedComponent::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedComponent Component;
	if (JsonObject.IsValid())
	{
		Component.ComponentName = JsonObject->GetStringField(TEXT("componentName"));
		Component.ComponentClass = JsonObject->GetStringField(TEXT("componentClass"));
		Component.ParentComponentName = JsonObject->GetStringField(TEXT("parentComponentName"));
		Component.bIsRootComponent = JsonObject->GetBoolField(TEXT("isRootComponent"));
		Component.AttachSocketName = JsonObject->GetStringField(TEXT("attachSocketName"));

		const TArray<TSharedPtr<FJsonValue>>* PropertiesArray;
		if (JsonObject->TryGetArrayField(TEXT("properties"), PropertiesArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *PropertiesArray)
			{
				Component.Properties.Add(FExportedComponentProperty::FromJson(Value->AsObject()));
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* ChildrenArray;
		if (JsonObject->TryGetArrayField(TEXT("childComponents"), ChildrenArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *ChildrenArray)
			{
				Component.ChildComponents.Add(FExportedComponent::FromJson(Value->AsObject()));
			}
		}
	}
	return Component;
}

// FExportedDependency
TSharedPtr<FJsonObject> FExportedDependency::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("assetPath"), AssetPath);
	JsonObject->SetStringField(TEXT("assetName"), AssetName);
	JsonObject->SetStringField(TEXT("dependencyType"), DependencyTypeToString(DependencyType));
	JsonObject->SetBoolField(TEXT("isBlueprint"), bIsBlueprint);
	JsonObject->SetBoolField(TEXT("isNativeClass"), bIsNativeClass);
	JsonObject->SetStringField(TEXT("description"), Description);
	return JsonObject;
}

FExportedDependency FExportedDependency::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedDependency Dependency;
	if (JsonObject.IsValid())
	{
		Dependency.AssetPath = JsonObject->GetStringField(TEXT("assetPath"));
		Dependency.AssetName = JsonObject->GetStringField(TEXT("assetName"));
		Dependency.DependencyType = StringToDependencyType(JsonObject->GetStringField(TEXT("dependencyType")));
		Dependency.bIsBlueprint = JsonObject->GetBoolField(TEXT("isBlueprint"));
		Dependency.bIsNativeClass = JsonObject->GetBoolField(TEXT("isNativeClass"));
		Dependency.Description = JsonObject->GetStringField(TEXT("description"));
	}
	return Dependency;
}

// FExportedParentClass
TSharedPtr<FJsonObject> FExportedParentClass::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("className"), ClassName);
	JsonObject->SetStringField(TEXT("classPath"), ClassPath);
	JsonObject->SetBoolField(TEXT("isNative"), bIsNative);
	JsonObject->SetStringField(TEXT("moduleName"), ModuleName);
	return JsonObject;
}

FExportedParentClass FExportedParentClass::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedParentClass ParentClass;
	if (JsonObject.IsValid())
	{
		ParentClass.ClassName = JsonObject->GetStringField(TEXT("className"));
		ParentClass.ClassPath = JsonObject->GetStringField(TEXT("classPath"));
		ParentClass.bIsNative = JsonObject->GetBoolField(TEXT("isNative"));
		ParentClass.ModuleName = JsonObject->GetStringField(TEXT("moduleName"));
	}
	return ParentClass;
}

// FExportInfo
TSharedPtr<FJsonObject> FExportInfo::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("schemaVersion"), SchemaVersion);
	JsonObject->SetStringField(TEXT("engineVersion"), EngineVersion);
	JsonObject->SetStringField(TEXT("pluginVersion"), PluginVersion);
	JsonObject->SetStringField(TEXT("exportTimestamp"), ExportTimestamp);
	JsonObject->SetStringField(TEXT("contentHash"), ContentHash);
	return JsonObject;
}

FExportInfo FExportInfo::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportInfo Info;
	if (JsonObject.IsValid())
	{
		Info.SchemaVersion = JsonObject->GetStringField(TEXT("schemaVersion"));
		Info.EngineVersion = JsonObject->GetStringField(TEXT("engineVersion"));
		Info.PluginVersion = JsonObject->GetStringField(TEXT("pluginVersion"));
		Info.ExportTimestamp = JsonObject->GetStringField(TEXT("exportTimestamp"));
		Info.ContentHash = JsonObject->GetStringField(TEXT("contentHash"));
	}
	return Info;
}

// FExportedTransitionBlendSettings
TSharedPtr<FJsonObject> FExportedTransitionBlendSettings::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetNumberField(TEXT("crossfadeDuration"), CrossfadeDuration);
	JsonObject->SetStringField(TEXT("blendMode"), BlendMode);
	JsonObject->SetStringField(TEXT("crossfadeMode"), CrossfadeMode);
	JsonObject->SetStringField(TEXT("logicType"), LogicType);
	JsonObject->SetNumberField(TEXT("priorityOrder"), PriorityOrder);
	JsonObject->SetBoolField(TEXT("automaticRuleBasedOnSequencePlayer"), bAutomaticRuleBasedOnSequencePlayer);
	return JsonObject;
}

FExportedTransitionBlendSettings FExportedTransitionBlendSettings::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedTransitionBlendSettings Settings;
	if (JsonObject.IsValid())
	{
		Settings.CrossfadeDuration = JsonObject->GetNumberField(TEXT("crossfadeDuration"));
		JsonObject->TryGetStringField(TEXT("blendMode"), Settings.BlendMode);
		JsonObject->TryGetStringField(TEXT("crossfadeMode"), Settings.CrossfadeMode);
		JsonObject->TryGetStringField(TEXT("logicType"), Settings.LogicType);
		Settings.PriorityOrder = JsonObject->GetIntegerField(TEXT("priorityOrder"));
		Settings.bAutomaticRuleBasedOnSequencePlayer = JsonObject->GetBoolField(TEXT("automaticRuleBasedOnSequencePlayer"));
	}
	return Settings;
}

// FExportedAnimState
TSharedPtr<FJsonObject> FExportedAnimState::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("stateName"), StateName);
	JsonObject->SetStringField(TEXT("stateGuid"), StateGuid);
	JsonObject->SetStringField(TEXT("stateType"), StateType);
	JsonObject->SetObjectField(TEXT("animGraph"), AnimGraph.ToJson());

	TArray<TSharedPtr<FJsonValue>> NestedArray;
	for (const FExportedStateMachine& Nested : NestedStateMachines)
	{
		NestedArray.Add(MakeShareable(new FJsonValueObject(Nested.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("nestedStateMachines"), NestedArray);

	return JsonObject;
}

FExportedAnimState FExportedAnimState::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedAnimState State;
	if (JsonObject.IsValid())
	{
		State.StateName = JsonObject->GetStringField(TEXT("stateName"));
		State.StateGuid = JsonObject->GetStringField(TEXT("stateGuid"));
		JsonObject->TryGetStringField(TEXT("stateType"), State.StateType);

		const TSharedPtr<FJsonObject>* AnimGraphObj;
		if (JsonObject->TryGetObjectField(TEXT("animGraph"), AnimGraphObj))
		{
			State.AnimGraph = FExportedGraph::FromJson(*AnimGraphObj);
		}

		const TArray<TSharedPtr<FJsonValue>>* NestedArray;
		if (JsonObject->TryGetArrayField(TEXT("nestedStateMachines"), NestedArray))
		{
			for (const auto& Value : *NestedArray)
			{
				State.NestedStateMachines.Add(FExportedStateMachine::FromJson(Value->AsObject()));
			}
		}
	}
	return State;
}

// FExportedAnimTransition
TSharedPtr<FJsonObject> FExportedAnimTransition::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("transitionName"), TransitionName);
	JsonObject->SetStringField(TEXT("transitionGuid"), TransitionGuid);
	JsonObject->SetStringField(TEXT("sourceState"), SourceState);
	JsonObject->SetStringField(TEXT("targetState"), TargetState);
	JsonObject->SetObjectField(TEXT("ruleGraph"), RuleGraph.ToJson());
	JsonObject->SetObjectField(TEXT("blendSettings"), BlendSettings.ToJson());
	return JsonObject;
}

FExportedAnimTransition FExportedAnimTransition::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedAnimTransition Transition;
	if (JsonObject.IsValid())
	{
		Transition.TransitionName = JsonObject->GetStringField(TEXT("transitionName"));
		Transition.TransitionGuid = JsonObject->GetStringField(TEXT("transitionGuid"));
		Transition.SourceState = JsonObject->GetStringField(TEXT("sourceState"));
		Transition.TargetState = JsonObject->GetStringField(TEXT("targetState"));

		const TSharedPtr<FJsonObject>* RuleGraphObj;
		if (JsonObject->TryGetObjectField(TEXT("ruleGraph"), RuleGraphObj))
		{
			Transition.RuleGraph = FExportedGraph::FromJson(*RuleGraphObj);
		}

		const TSharedPtr<FJsonObject>* BlendObj;
		if (JsonObject->TryGetObjectField(TEXT("blendSettings"), BlendObj))
		{
			Transition.BlendSettings = FExportedTransitionBlendSettings::FromJson(*BlendObj);
		}
	}
	return Transition;
}

// FExportedStateMachine
TSharedPtr<FJsonObject> FExportedStateMachine::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("machineName"), MachineName);
	JsonObject->SetStringField(TEXT("machineGuid"), MachineGuid);

	// Sort states by name for determinism
	TArray<FExportedAnimState> SortedStates = States;
	SortedStates.Sort([](const FExportedAnimState& A, const FExportedAnimState& B) {
		return A.StateName < B.StateName;
	});
	TArray<TSharedPtr<FJsonValue>> StatesArray;
	for (const FExportedAnimState& State : SortedStates)
	{
		StatesArray.Add(MakeShareable(new FJsonValueObject(State.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("states"), StatesArray);

	// Sort transitions by name for determinism
	TArray<FExportedAnimTransition> SortedTransitions = Transitions;
	SortedTransitions.Sort([](const FExportedAnimTransition& A, const FExportedAnimTransition& B) {
		return A.TransitionName < B.TransitionName;
	});
	TArray<TSharedPtr<FJsonValue>> TransitionsArray;
	for (const FExportedAnimTransition& Transition : SortedTransitions)
	{
		TransitionsArray.Add(MakeShareable(new FJsonValueObject(Transition.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("transitions"), TransitionsArray);

	return JsonObject;
}

FExportedStateMachine FExportedStateMachine::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedStateMachine Machine;
	if (JsonObject.IsValid())
	{
		Machine.MachineName = JsonObject->GetStringField(TEXT("machineName"));
		Machine.MachineGuid = JsonObject->GetStringField(TEXT("machineGuid"));

		const TArray<TSharedPtr<FJsonValue>>* StatesArray;
		if (JsonObject->TryGetArrayField(TEXT("states"), StatesArray))
		{
			for (const auto& Value : *StatesArray)
			{
				Machine.States.Add(FExportedAnimState::FromJson(Value->AsObject()));
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* TransitionsArray;
		if (JsonObject->TryGetArrayField(TEXT("transitions"), TransitionsArray))
		{
			for (const auto& Value : *TransitionsArray)
			{
				Machine.Transitions.Add(FExportedAnimTransition::FromJson(Value->AsObject()));
			}
		}
	}
	return Machine;
}

// FExportedWidgetNode
TSharedPtr<FJsonObject> FExportedWidgetNode::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("widgetName"), WidgetName);
	JsonObject->SetStringField(TEXT("widgetClass"), WidgetClass);
	JsonObject->SetBoolField(TEXT("isVariable"), bIsVariable);
	JsonObject->SetStringField(TEXT("slotClass"), SlotClass);

	// Authored child order preserved — slot order is load-bearing in UMG.
	TArray<TSharedPtr<FJsonValue>> ChildrenArray;
	for (const FExportedWidgetNode& Child : Children)
	{
		ChildrenArray.Add(MakeShareable(new FJsonValueObject(Child.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("children"), ChildrenArray);
	return JsonObject;
}

FExportedWidgetNode FExportedWidgetNode::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedWidgetNode Node;
	if (JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("widgetName"), Node.WidgetName);
		JsonObject->TryGetStringField(TEXT("widgetClass"), Node.WidgetClass);
		JsonObject->TryGetBoolField(TEXT("isVariable"), Node.bIsVariable);
		JsonObject->TryGetStringField(TEXT("slotClass"), Node.SlotClass);

		const TArray<TSharedPtr<FJsonValue>>* ChildrenArray;
		if (JsonObject->TryGetArrayField(TEXT("children"), ChildrenArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *ChildrenArray)
			{
				Node.Children.Add(FExportedWidgetNode::FromJson(Value->AsObject()));
			}
		}
	}
	return Node;
}

// FExportedBlueprint
TSharedPtr<FJsonObject> FExportedBlueprint::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	JsonObject->SetStringField(TEXT("$schema"), TEXT("blueprint-exporter-v1"));
	JsonObject->SetObjectField(TEXT("exportInfo"), ExportInfo.ToJson());
	JsonObject->SetStringField(TEXT("assetPath"), AssetPath);
	JsonObject->SetStringField(TEXT("assetName"), AssetName);
	JsonObject->SetStringField(TEXT("blueprintGuid"), BlueprintGuid);
	JsonObject->SetStringField(TEXT("blueprintType"), BlueprintTypeToString(BlueprintType));
	JsonObject->SetStringField(TEXT("blueprintSubclass"), BlueprintSubclass);
	JsonObject->SetObjectField(TEXT("parentClass"), ParentClass.ToJson());

	TArray<TSharedPtr<FJsonValue>> InterfacesArray;
	for (const FString& Interface : ImplementedInterfaces)
	{
		InterfacesArray.Add(MakeShareable(new FJsonValueString(Interface)));
	}
	JsonObject->SetArrayField(TEXT("implementedInterfaces"), InterfacesArray);

	// Sort variables by name for determinism
	TArray<FExportedVariable> SortedVariables = Variables;
	SortedVariables.Sort([](const FExportedVariable& A, const FExportedVariable& B) {
		return A.VariableName < B.VariableName;
	});
	TArray<TSharedPtr<FJsonValue>> VariablesArray;
	for (const FExportedVariable& Variable : SortedVariables)
	{
		VariablesArray.Add(MakeShareable(new FJsonValueObject(Variable.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("variables"), VariablesArray);

	// Sort functions by name for determinism
	TArray<FExportedFunction> SortedFunctions = Functions;
	SortedFunctions.Sort([](const FExportedFunction& A, const FExportedFunction& B) {
		return A.FunctionName < B.FunctionName;
	});
	TArray<TSharedPtr<FJsonValue>> FunctionsArray;
	for (const FExportedFunction& Function : SortedFunctions)
	{
		FunctionsArray.Add(MakeShareable(new FJsonValueObject(Function.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("functions"), FunctionsArray);

	// Sort macros by name for determinism
	TArray<FExportedFunction> SortedMacros = Macros;
	SortedMacros.Sort([](const FExportedFunction& A, const FExportedFunction& B) {
		return A.FunctionName < B.FunctionName;
	});
	TArray<TSharedPtr<FJsonValue>> MacrosArray;
	for (const FExportedFunction& Macro : SortedMacros)
	{
		MacrosArray.Add(MakeShareable(new FJsonValueObject(Macro.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("macros"), MacrosArray);

	JsonObject->SetObjectField(TEXT("eventGraph"), EventGraph.ToJson());
	JsonObject->SetObjectField(TEXT("constructionScript"), ConstructionScript.ToJson());

	// Sort components by name for determinism
	TArray<FExportedComponent> SortedComponents = Components;
	SortedComponents.Sort([](const FExportedComponent& A, const FExportedComponent& B) {
		return A.ComponentName < B.ComponentName;
	});
	TArray<TSharedPtr<FJsonValue>> ComponentsArray;
	for (const FExportedComponent& Component : SortedComponents)
	{
		ComponentsArray.Add(MakeShareable(new FJsonValueObject(Component.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("components"), ComponentsArray);

	// Class Default Object property overrides — already sorted by property name in the
	// serializer (determinism, brief §8); re-sort here defensively so a consumer that
	// mutates the in-memory vector can't drift output order.
	TArray<FExportedComponentProperty> SortedCDOProps = CDOProperties;
	SortedCDOProps.Sort([](const FExportedComponentProperty& A, const FExportedComponentProperty& B) {
		return A.PropertyName < B.PropertyName;
	});
	TArray<TSharedPtr<FJsonValue>> CDOPropsArray;
	for (const FExportedComponentProperty& Prop : SortedCDOProps)
	{
		CDOPropsArray.Add(MakeShareable(new FJsonValueObject(Prop.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("cdoProperties"), CDOPropsArray);

	if (!DataCarrierKind.IsEmpty())
	{
		JsonObject->SetStringField(TEXT("dataCarrierKind"), DataCarrierKind);
	}

	TArray<TSharedPtr<FJsonValue>> AdditionalGraphsArray;
	for (const FExportedGraph& Graph : AdditionalGraphs)
	{
		AdditionalGraphsArray.Add(MakeShareable(new FJsonValueObject(Graph.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("additionalGraphs"), AdditionalGraphsArray);

	// Sort state machines by name for determinism
	TArray<FExportedStateMachine> SortedStateMachines = StateMachines;
	SortedStateMachines.Sort([](const FExportedStateMachine& A, const FExportedStateMachine& B) {
		return A.MachineName < B.MachineName;
	});
	TArray<TSharedPtr<FJsonValue>> StateMachinesArray;
	for (const FExportedStateMachine& Machine : SortedStateMachines)
	{
		StateMachinesArray.Add(MakeShareable(new FJsonValueObject(Machine.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("stateMachines"), StateMachinesArray);

	// Widget tree — authored hierarchical order preserved (slot order is
	// load-bearing in UMG layout); only non-empty for WidgetBlueprints.
	TArray<TSharedPtr<FJsonValue>> WidgetTreeArray;
	for (const FExportedWidgetNode& Node : WidgetTree)
	{
		WidgetTreeArray.Add(MakeShareable(new FJsonValueObject(Node.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("widgetTree"), WidgetTreeArray);

	// Sort dependencies by path for determinism
	TArray<FExportedDependency> SortedDeps = Dependencies;
	SortedDeps.Sort([](const FExportedDependency& A, const FExportedDependency& B) {
		return A.AssetPath < B.AssetPath;
	});
	TArray<TSharedPtr<FJsonValue>> DependenciesArray;
	for (const FExportedDependency& Dependency : SortedDeps)
	{
		DependenciesArray.Add(MakeShareable(new FJsonValueObject(Dependency.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("dependencies"), DependenciesArray);

	JsonObject->SetObjectField(TEXT("metaData"), MapToJson(MetaData));

	return JsonObject;
}

FExportedBlueprint FExportedBlueprint::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportedBlueprint Blueprint;
	if (JsonObject.IsValid())
	{
		Blueprint.ExportInfo = FExportInfo::FromJson(JsonObject->GetObjectField(TEXT("exportInfo")));
		Blueprint.AssetPath = JsonObject->GetStringField(TEXT("assetPath"));
		Blueprint.AssetName = JsonObject->GetStringField(TEXT("assetName"));
		Blueprint.BlueprintGuid = JsonObject->GetStringField(TEXT("blueprintGuid"));
		Blueprint.BlueprintType = StringToBlueprintType(JsonObject->GetStringField(TEXT("blueprintType")));
		JsonObject->TryGetStringField(TEXT("blueprintSubclass"), Blueprint.BlueprintSubclass);
		Blueprint.ParentClass = FExportedParentClass::FromJson(JsonObject->GetObjectField(TEXT("parentClass")));

		const TArray<TSharedPtr<FJsonValue>>* InterfacesArray;
		if (JsonObject->TryGetArrayField(TEXT("implementedInterfaces"), InterfacesArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *InterfacesArray)
			{
				Blueprint.ImplementedInterfaces.Add(Value->AsString());
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* VariablesArray;
		if (JsonObject->TryGetArrayField(TEXT("variables"), VariablesArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *VariablesArray)
			{
				Blueprint.Variables.Add(FExportedVariable::FromJson(Value->AsObject()));
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* FunctionsArray;
		if (JsonObject->TryGetArrayField(TEXT("functions"), FunctionsArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *FunctionsArray)
			{
				Blueprint.Functions.Add(FExportedFunction::FromJson(Value->AsObject()));
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* MacrosArray;
		if (JsonObject->TryGetArrayField(TEXT("macros"), MacrosArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *MacrosArray)
			{
				Blueprint.Macros.Add(FExportedFunction::FromJson(Value->AsObject()));
			}
		}

		Blueprint.EventGraph = FExportedGraph::FromJson(JsonObject->GetObjectField(TEXT("eventGraph")));
		Blueprint.ConstructionScript = FExportedGraph::FromJson(JsonObject->GetObjectField(TEXT("constructionScript")));

		const TArray<TSharedPtr<FJsonValue>>* ComponentsArray;
		if (JsonObject->TryGetArrayField(TEXT("components"), ComponentsArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *ComponentsArray)
			{
				Blueprint.Components.Add(FExportedComponent::FromJson(Value->AsObject()));
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* CDOPropsArray;
		if (JsonObject->TryGetArrayField(TEXT("cdoProperties"), CDOPropsArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *CDOPropsArray)
			{
				Blueprint.CDOProperties.Add(FExportedComponentProperty::FromJson(Value->AsObject()));
			}
		}

		JsonObject->TryGetStringField(TEXT("dataCarrierKind"), Blueprint.DataCarrierKind);

		const TArray<TSharedPtr<FJsonValue>>* AdditionalGraphsArray;
		if (JsonObject->TryGetArrayField(TEXT("additionalGraphs"), AdditionalGraphsArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *AdditionalGraphsArray)
			{
				Blueprint.AdditionalGraphs.Add(FExportedGraph::FromJson(Value->AsObject()));
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* StateMachinesArray;
		if (JsonObject->TryGetArrayField(TEXT("stateMachines"), StateMachinesArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *StateMachinesArray)
			{
				Blueprint.StateMachines.Add(FExportedStateMachine::FromJson(Value->AsObject()));
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* WidgetTreeArray;
		if (JsonObject->TryGetArrayField(TEXT("widgetTree"), WidgetTreeArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *WidgetTreeArray)
			{
				Blueprint.WidgetTree.Add(FExportedWidgetNode::FromJson(Value->AsObject()));
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* DependenciesArray;
		if (JsonObject->TryGetArrayField(TEXT("dependencies"), DependenciesArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *DependenciesArray)
			{
				Blueprint.Dependencies.Add(FExportedDependency::FromJson(Value->AsObject()));
			}
		}

		const TSharedPtr<FJsonObject>* MetaDataObj;
		if (JsonObject->TryGetObjectField(TEXT("metaData"), MetaDataObj))
		{
			Blueprint.MetaData = JsonToMap(*MetaDataObj);
		}
	}
	return Blueprint;
}

FString FExportedBlueprint::ComputeContentHash() const
{
	// Create a copy without volatile fields and compute hash
	FExportedBlueprint HashCopy = *this;
	HashCopy.ExportInfo.ExportTimestamp = TEXT("");
	HashCopy.ExportInfo.ContentHash = TEXT("");

	TSharedPtr<FJsonObject> JsonObject = HashCopy.ToJson();
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	return FMD5::HashAnsiString(*JsonString);
}

// FExportManifestEntry
TSharedPtr<FJsonObject> FExportManifestEntry::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("assetPath"), AssetPath);
	JsonObject->SetStringField(TEXT("assetName"), AssetName);
	JsonObject->SetStringField(TEXT("exportFileName"), ExportFileName);
	JsonObject->SetStringField(TEXT("contentHash"), ContentHash);
	if (!AssetType.IsEmpty())
	{
		JsonObject->SetStringField(TEXT("assetType"), AssetType);
	}
	if (!BlueprintSubclass.IsEmpty())
	{
		JsonObject->SetStringField(TEXT("blueprintSubclass"), BlueprintSubclass);
	}
	JsonObject->SetNumberField(TEXT("nodeCount"), NodeCount);
	JsonObject->SetNumberField(TEXT("functionCount"), FunctionCount);
	JsonObject->SetNumberField(TEXT("complexityScore"), ComplexityScore);
	return JsonObject;
}

FExportManifestEntry FExportManifestEntry::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportManifestEntry Entry;
	if (JsonObject.IsValid())
	{
		Entry.AssetPath = JsonObject->GetStringField(TEXT("assetPath"));
		Entry.AssetName = JsonObject->GetStringField(TEXT("assetName"));
		Entry.ExportFileName = JsonObject->GetStringField(TEXT("exportFileName"));
		Entry.ContentHash = JsonObject->GetStringField(TEXT("contentHash"));
		JsonObject->TryGetStringField(TEXT("assetType"), Entry.AssetType);
		JsonObject->TryGetStringField(TEXT("blueprintSubclass"), Entry.BlueprintSubclass);
		Entry.NodeCount = JsonObject->GetIntegerField(TEXT("nodeCount"));
		Entry.FunctionCount = JsonObject->GetIntegerField(TEXT("functionCount"));
		Entry.ComplexityScore = JsonObject->GetNumberField(TEXT("complexityScore"));
	}
	return Entry;
}

// FExportManifest
TSharedPtr<FJsonObject> FExportManifest::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("schemaVersion"), SchemaVersion);
	JsonObject->SetStringField(TEXT("engineVersion"), EngineVersion);
	JsonObject->SetStringField(TEXT("pluginVersion"), PluginVersion);
	JsonObject->SetStringField(TEXT("exportTimestamp"), ExportTimestamp);

	// Sort entries by path for determinism
	TArray<FExportManifestEntry> SortedEntries = Entries;
	SortedEntries.Sort([](const FExportManifestEntry& A, const FExportManifestEntry& B) {
		return A.AssetPath < B.AssetPath;
	});

	TArray<TSharedPtr<FJsonValue>> EntriesArray;
	for (const FExportManifestEntry& Entry : SortedEntries)
	{
		EntriesArray.Add(MakeShareable(new FJsonValueObject(Entry.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("entries"), EntriesArray);

	JsonObject->SetObjectField(TEXT("exportConfig"), MapToJson(ExportConfig));

	return JsonObject;
}

FExportManifest FExportManifest::FromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	FExportManifest Manifest;
	if (JsonObject.IsValid())
	{
		Manifest.SchemaVersion = JsonObject->GetStringField(TEXT("schemaVersion"));
		Manifest.EngineVersion = JsonObject->GetStringField(TEXT("engineVersion"));
		Manifest.PluginVersion = JsonObject->GetStringField(TEXT("pluginVersion"));
		Manifest.ExportTimestamp = JsonObject->GetStringField(TEXT("exportTimestamp"));

		const TArray<TSharedPtr<FJsonValue>>* EntriesArray;
		if (JsonObject->TryGetArrayField(TEXT("entries"), EntriesArray))
		{
			for (const TSharedPtr<FJsonValue>& Value : *EntriesArray)
			{
				Manifest.Entries.Add(FExportManifestEntry::FromJson(Value->AsObject()));
			}
		}

		const TSharedPtr<FJsonObject>* ConfigObj;
		if (JsonObject->TryGetObjectField(TEXT("exportConfig"), ConfigObj))
		{
			Manifest.ExportConfig = JsonToMap(*ConfigObj);
		}
	}
	return Manifest;
}

bool FExportManifest::SaveToFile(const FString& FilePath) const
{
	TSharedPtr<FJsonObject> JsonObject = ToJson();
	FString JsonString;
	TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> Writer =
		TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&JsonString);

	if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer))
	{
		return FFileHelper::SaveStringToFile(JsonString, *FilePath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
	}
	return false;
}

bool FExportManifest::LoadFromFile(const FString& FilePath, FExportManifest& OutManifest)
{
	FString JsonString;
	if (!FFileHelper::LoadFileToString(JsonString, *FilePath))
	{
		return false;
	}

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
	{
		return false;
	}

	OutManifest = FExportManifest::FromJson(JsonObject);
	return true;
}

// FBlueprintDiffChange
TSharedPtr<FJsonObject> FBlueprintDiffChange::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("changeType"), DiffChangeTypeToString(ChangeType));
	JsonObject->SetStringField(TEXT("category"), Category);
	JsonObject->SetStringField(TEXT("elementPath"), ElementPath);
	JsonObject->SetStringField(TEXT("elementName"), ElementName);
	JsonObject->SetStringField(TEXT("oldValue"), OldValue);
	JsonObject->SetStringField(TEXT("newValue"), NewValue);
	JsonObject->SetStringField(TEXT("description"), Description);
	return JsonObject;
}

// FBlueprintDiffResult
TSharedPtr<FJsonObject> FBlueprintDiffResult::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("sourcePath"), SourcePath);
	JsonObject->SetStringField(TEXT("targetPath"), TargetPath);
	JsonObject->SetBoolField(TEXT("hasChanges"), bHasChanges);
	JsonObject->SetNumberField(TEXT("nodesAdded"), NodesAdded);
	JsonObject->SetNumberField(TEXT("nodesRemoved"), NodesRemoved);
	JsonObject->SetNumberField(TEXT("nodesModified"), NodesModified);
	JsonObject->SetNumberField(TEXT("connectionsChanged"), ConnectionsChanged);
	JsonObject->SetNumberField(TEXT("variablesChanged"), VariablesChanged);
	JsonObject->SetNumberField(TEXT("functionsChanged"), FunctionsChanged);
	JsonObject->SetNumberField(TEXT("layoutChanges"), LayoutChanges);

	TArray<TSharedPtr<FJsonValue>> ChangesArray;
	for (const FBlueprintDiffChange& Change : Changes)
	{
		ChangesArray.Add(MakeShareable(new FJsonValueObject(Change.ToJson())));
	}
	JsonObject->SetArrayField(TEXT("changes"), ChangesArray);

	return JsonObject;
}

FString FBlueprintDiffResult::GetSummary() const
{
	if (!bHasChanges)
	{
		return TEXT("No changes detected.");
	}

	FString Summary = FString::Printf(
		TEXT("Changes: %d nodes added, %d removed, %d modified; %d connections changed; %d variables, %d functions changed; %d layout changes"),
		NodesAdded, NodesRemoved, NodesModified, ConnectionsChanged, VariablesChanged, FunctionsChanged, LayoutChanges
	);
	return Summary;
}

bool FBlueprintDiffResult::SaveToFile(const FString& FilePath) const
{
	TSharedPtr<FJsonObject> JsonObject = ToJson();
	FString JsonString;
	TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> Writer =
		TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&JsonString);

	if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer))
	{
		return FFileHelper::SaveStringToFile(JsonString, *FilePath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
	}
	return false;
}

// FBlueprintExportMetrics
TSharedPtr<FJsonObject> FBlueprintExportMetrics::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("timestamp"), Timestamp);
	JsonObject->SetNumberField(TEXT("totalBlueprints"), TotalBlueprints);
	JsonObject->SetNumberField(TEXT("successCount"), SuccessCount);
	JsonObject->SetNumberField(TEXT("failureCount"), FailureCount);
	JsonObject->SetNumberField(TEXT("totalExportTimeSeconds"), TotalExportTimeSeconds);

	TArray<TSharedPtr<FJsonValue>> FailedArray;
	for (const FString& Failed : FailedAssets)
	{
		FailedArray.Add(MakeShareable(new FJsonValueString(Failed)));
	}
	JsonObject->SetArrayField(TEXT("failedAssets"), FailedArray);

	TSharedPtr<FJsonObject> MetricsObj = MakeShareable(new FJsonObject());
	TArray<FString> Keys;
	PerBlueprintMetrics.GetKeys(Keys);
	Keys.Sort();
	for (const FString& Key : Keys)
	{
		MetricsObj->SetNumberField(Key, PerBlueprintMetrics[Key]);
	}
	JsonObject->SetObjectField(TEXT("perBlueprintMetrics"), MetricsObj);

	return JsonObject;
}

bool FBlueprintExportMetrics::SaveToFile(const FString& FilePath) const
{
	TSharedPtr<FJsonObject> JsonObject = ToJson();
	FString JsonString;
	TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> Writer =
		TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&JsonString);

	if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer))
	{
		return FFileHelper::SaveStringToFile(JsonString, *FilePath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
	}
	return false;
}
