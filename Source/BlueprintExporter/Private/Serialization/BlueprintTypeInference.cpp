// Copyright Epic Games, Inc. All Rights Reserved.

#include "Serialization/BlueprintTypeInference.h"
#include "BlueprintExporterModule.h"
#include "Serialization/JsonSerializer.h"

// ============================================================================
// FTypeSignature Implementation
// ============================================================================

bool FTypeSignature::IsConcrete(int32 Depth) const
{
	// Guard against pathological recursion
	if (Depth > 4) return false;

	// Exclude non-types from conflict detection
	if (Kind == ETypeKind::Wildcard) return false;
	if (Kind == ETypeKind::Exec) return false;
	if (Kind == ETypeKind::Context) return false;
	if (Kind == ETypeKind::Unknown) return false;

	// Primitives are concrete (no path needed)
	// Kind::Primitive is not excluded, so it passes through

	// Missing path when required
	if (NeedsPath(Kind) && Path.IsEmpty()) return false;

	// Container completeness - incomplete containers are not concrete
	if (Container == EContainerType::Array || Container == EContainerType::Set)
	{
		if (!ElementType.IsSet() || !ElementType.GetValue().IsValid())
		{
			return false;
		}
		if (!ElementType.GetValue()->IsConcrete(Depth + 1))
		{
			return false;
		}
	}
	if (Container == EContainerType::Map)
	{
		if (!MapKeyType.IsSet() || !MapKeyType.GetValue().IsValid() || !MapKeyType.GetValue()->IsConcrete(Depth + 1))
		{
			return false;
		}
		if (!MapValueType.IsSet() || !MapValueType.GetValue().IsValid() || !MapValueType.GetValue()->IsConcrete(Depth + 1))
		{
			return false;
		}
	}

	return true;
}

bool FTypeSignature::Equals(const FTypeSignature& Other) const
{
	if (Kind != Other.Kind) return false;
	if (Container != Other.Container) return false;

	// Normalize paths before comparing
	FString NormPath = FBlueprintTypeInference::NormalizePath(Path);
	FString OtherNormPath = FBlueprintTypeInference::NormalizePath(Other.Path);
	if (NormPath != OtherNormPath) return false;

	// Container element types
	if (Container == EContainerType::Array || Container == EContainerType::Set)
	{
		if (ElementType.IsSet() != Other.ElementType.IsSet()) return false;
		if (ElementType.IsSet() && Other.ElementType.IsSet())
		{
			if (!ElementType.GetValue()->Equals(*Other.ElementType.GetValue())) return false;
		}
	}
	if (Container == EContainerType::Map)
	{
		if (MapKeyType.IsSet() != Other.MapKeyType.IsSet()) return false;
		if (MapKeyType.IsSet() && Other.MapKeyType.IsSet())
		{
			if (!MapKeyType.GetValue()->Equals(*Other.MapKeyType.GetValue())) return false;
		}
		if (MapValueType.IsSet() != Other.MapValueType.IsSet()) return false;
		if (MapValueType.IsSet() && Other.MapValueType.IsSet())
		{
			if (!MapValueType.GetValue()->Equals(*Other.MapValueType.GetValue())) return false;
		}
	}

	// Don't require ref/const match - those can differ across wire
	return true;
}

FString FTypeSignature::GetHash() const
{
	FString Hash = FString::Printf(TEXT("%s|%s|%s|%s"),
		*KindToString(Kind),
		*Category,
		*FBlueprintTypeInference::NormalizePath(Path),
		*ContainerToString(Container));

	// Include element types for containers
	if (ElementType.IsSet() && ElementType.GetValue().IsValid())
	{
		Hash += TEXT("|elem:") + ElementType.GetValue()->GetHash();
	}
	if (MapKeyType.IsSet() && MapKeyType.GetValue().IsValid())
	{
		Hash += TEXT("|key:") + MapKeyType.GetValue()->GetHash();
	}
	if (MapValueType.IsSet() && MapValueType.GetValue().IsValid())
	{
		Hash += TEXT("|val:") + MapValueType.GetValue()->GetHash();
	}

	return Hash;
}

bool FTypeSignature::NeedsPath(ETypeKind InKind)
{
	return InKind == ETypeKind::Object
		|| InKind == ETypeKind::Struct
		|| InKind == ETypeKind::Enum
		|| InKind == ETypeKind::Class
		|| InKind == ETypeKind::Interface;
}

FString FTypeSignature::KindToString(ETypeKind InKind)
{
	switch (InKind)
	{
	case ETypeKind::Object:    return TEXT("object");
	case ETypeKind::Struct:    return TEXT("struct");
	case ETypeKind::Class:     return TEXT("class");
	case ETypeKind::Enum:      return TEXT("enum");
	case ETypeKind::Interface: return TEXT("interface");
	case ETypeKind::Primitive: return TEXT("primitive");
	case ETypeKind::Exec:      return TEXT("exec");
	case ETypeKind::Wildcard:  return TEXT("wildcard");
	case ETypeKind::Context:   return TEXT("context");
	default:                   return TEXT("unknown");
	}
}

FString FTypeSignature::ContainerToString(EContainerType InContainer)
{
	switch (InContainer)
	{
	case EContainerType::Array: return TEXT("array");
	case EContainerType::Set:   return TEXT("set");
	case EContainerType::Map:   return TEXT("map");
	default:                    return TEXT("none");
	}
}

ETypeKind FTypeSignature::ParseKind(const FString& Str)
{
	if (Str == TEXT("object"))    return ETypeKind::Object;
	if (Str == TEXT("struct"))    return ETypeKind::Struct;
	if (Str == TEXT("class"))     return ETypeKind::Class;
	if (Str == TEXT("enum"))      return ETypeKind::Enum;
	if (Str == TEXT("interface")) return ETypeKind::Interface;
	if (Str == TEXT("primitive")) return ETypeKind::Primitive;
	if (Str == TEXT("exec"))      return ETypeKind::Exec;
	if (Str == TEXT("wildcard"))  return ETypeKind::Wildcard;
	if (Str == TEXT("context"))   return ETypeKind::Context;
	return ETypeKind::Unknown;
}

EContainerType FTypeSignature::ParseContainer(const FString& Str)
{
	if (Str == TEXT("array")) return EContainerType::Array;
	if (Str == TEXT("set"))   return EContainerType::Set;
	if (Str == TEXT("map"))   return EContainerType::Map;
	return EContainerType::None;
}

// ============================================================================
// FPinReference Implementation
// ============================================================================

FString FPinReference::MakeId() const
{
	return FString::Printf(TEXT("%s:%s:%s:%s"), *GraphScope, *NodeGuid, *PinName, *Direction);
}

// ============================================================================
// FInferenceStats Implementation
// ============================================================================

TSharedPtr<FJsonObject> FInferenceStats::ToJson() const
{
	TSharedPtr<FJsonObject> StatsObj = MakeShared<FJsonObject>();

	StatsObj->SetNumberField(TEXT("totalPins"), TotalPins);
	StatsObj->SetNumberField(TEXT("resolvedPins"), ResolvedPins);
	StatsObj->SetNumberField(TEXT("unresolvedPins"), UnresolvedPins);
	StatsObj->SetNumberField(TEXT("conflictPins"), ConflictPins);

	StatsObj->SetNumberField(TEXT("unrealResolvedPins"), UnrealResolvedPins);
	StatsObj->SetNumberField(TEXT("inferredPins"), InferredPins);

	StatsObj->SetNumberField(TEXT("passesRun"), PassesRun);

	if (TotalPins > 0)
	{
		StatsObj->SetNumberField(TEXT("resolvedPercent"), 100.0f * ResolvedPins / TotalPins);
	}

	// Complex pins breakdown
	TSharedPtr<FJsonObject> ComplexObj = MakeShared<FJsonObject>();
	ComplexObj->SetNumberField(TEXT("total"), TotalComplexPins);
	ComplexObj->SetNumberField(TEXT("unrealResolved"), UnrealResolvedComplexPins);
	ComplexObj->SetNumberField(TEXT("inferred"), InferredComplexPins);
	ComplexObj->SetNumberField(TEXT("unresolved"), UnresolvedComplexPins);

	if (TotalComplexPins > 0)
	{
		float UnrealResolvedPct = 100.0f * UnrealResolvedComplexPins / TotalComplexPins;
		float ResolvedPct = 100.0f * (UnrealResolvedComplexPins + InferredComplexPins) / TotalComplexPins;
		float GainPct = ResolvedPct - UnrealResolvedPct;

		ComplexObj->SetNumberField(TEXT("unrealResolvedPercent"), UnrealResolvedPct);
		ComplexObj->SetNumberField(TEXT("resolvedPercent"), ResolvedPct);
		ComplexObj->SetNumberField(TEXT("coverageGainPercentPoints"), GainPct);
	}

	StatsObj->SetObjectField(TEXT("complexPins"), ComplexObj);

	return StatsObj;
}

// ============================================================================
// FBlueprintTypeInference Implementation
// ============================================================================

FBlueprintTypeInference::FBlueprintTypeInference()
{
}

FBlueprintTypeInference::~FBlueprintTypeInference()
{
}

FString FBlueprintTypeInference::NormalizePath(const FString& Path)
{
	FString Result = Path.TrimStartAndEnd();

	// Remove surrounding quotes if present
	if (Result.StartsWith(TEXT("\"")) && Result.EndsWith(TEXT("\"")))
	{
		Result = Result.Mid(1, Result.Len() - 2);
	}

	// Strip type prefixes: ScriptStruct'/Script/...', Class'/Script/...', etc.
	static const TArray<FString> Prefixes = {
		TEXT("ScriptStruct'"),
		TEXT("Class'"),
		TEXT("BlueprintGeneratedClass'"),
		TEXT("Struct'"),
		TEXT("Enum'"),
		TEXT("Object'")
	};

	for (const FString& Prefix : Prefixes)
	{
		if (Result.StartsWith(Prefix) && Result.EndsWith(TEXT("'")))
		{
			Result = Result.Mid(Prefix.Len(), Result.Len() - Prefix.Len() - 1);
			break;
		}
	}

	// Don't strip _C suffix - BP generated class vs BP asset are semantically different
	// Don't add /Script/ prefix - could be wrong for game types

	return Result;
}

ETypeKind FBlueprintTypeInference::DetermineKind(const FString& Category, const FString& SubCategoryPath, bool& bOutPossibleInterface)
{
	bOutPossibleInterface = false;

	if (Category == TEXT("exec")) return ETypeKind::Exec;

	// Primitives
	static const TSet<FString> Primitives = {
		TEXT("bool"), TEXT("byte"), TEXT("int"), TEXT("int64"),
		TEXT("real"), TEXT("float"), TEXT("double"),
		TEXT("name"), TEXT("string"), TEXT("text")
	};
	if (Primitives.Contains(Category))
	{
		return ETypeKind::Primitive;
	}

	// Interface detection: category is "object" but path may indicate interface
	// Use weak heuristic - hint only, don't change Kind
	if (Category == TEXT("object"))
	{
		FString NormPath = NormalizePath(SubCategoryPath);
		if (!NormPath.IsEmpty() && !NormPath.EndsWith(TEXT("_C")) && NormPath.Contains(TEXT("Interface")))
		{
			bOutPossibleInterface = true;
		}
		return ETypeKind::Object;
	}

	// Standard mappings
	if (Category == TEXT("class"))     return ETypeKind::Class;
	if (Category == TEXT("struct"))    return ETypeKind::Struct;
	if (Category == TEXT("enum"))      return ETypeKind::Enum;
	if (Category == TEXT("interface")) return ETypeKind::Interface;

	// Check for wildcard-like patterns
	if (SubCategoryPath.IsEmpty() || SubCategoryPath == TEXT("None"))
	{
		// Could be wildcard if category expects a path
		if (Category == TEXT("object") || Category == TEXT("struct") || Category == TEXT("class"))
		{
			return ETypeKind::Wildcard;
		}
	}

	return ETypeKind::Unknown;
}

bool FBlueprintTypeInference::IsComplexType(const FInferencePinData& Pin)
{
	return FTypeSignature::NeedsPath(Pin.ExtractedSignature.Kind);
}

const TSet<FString>& FBlueprintTypeInference::GetTypeCarrierNodes()
{
	static TSet<FString> Carriers = {
		TEXT("K2Node_Select"),
		TEXT("K2Node_MakeArray"),
		TEXT("K2Node_GetArrayItem"),
		TEXT("K2Node_SetArrayElem"),
		TEXT("K2Node_SetArrayItem"),  // UE naming variant
		TEXT("K2Node_MapFind"),
		TEXT("K2Node_MapAdd"),
		TEXT("K2Node_Knot"),  // Reroute node
		TEXT("Reroute")
	};
	return Carriers;
}

// ============================================================================
// Case-tolerant JSON helpers
// ============================================================================

namespace
{
	// Get object field with case tolerance
	TSharedPtr<FJsonObject> GetJsonObject(const TSharedPtr<FJsonObject>& Obj, const TCHAR* KeyA, const TCHAR* KeyB = nullptr)
	{
		if (!Obj.IsValid()) return nullptr;
		if (Obj->HasField(KeyA)) return Obj->GetObjectField(KeyA);
		if (KeyB && Obj->HasField(KeyB)) return Obj->GetObjectField(KeyB);
		return nullptr;
	}

	// Get array field with case tolerance
	const TArray<TSharedPtr<FJsonValue>>* GetJsonArray(const TSharedPtr<FJsonObject>& Obj, const TCHAR* KeyA, const TCHAR* KeyB = nullptr)
	{
		if (!Obj.IsValid()) return nullptr;
		if (Obj->HasField(KeyA)) return &Obj->GetArrayField(KeyA);
		if (KeyB && Obj->HasField(KeyB)) return &Obj->GetArrayField(KeyB);
		return nullptr;
	}

	// Get string field with case tolerance
	FString GetJsonString(const TSharedPtr<FJsonObject>& Obj, const TCHAR* KeyA, const TCHAR* KeyB = nullptr)
	{
		if (!Obj.IsValid()) return FString();
		FString Result;
		if (Obj->TryGetStringField(KeyA, Result)) return Result;
		if (KeyB && Obj->TryGetStringField(KeyB, Result)) return Result;
		return FString();
	}

	// Check if object has field with case tolerance
	bool HasJsonField(const TSharedPtr<FJsonObject>& Obj, const TCHAR* KeyA, const TCHAR* KeyB = nullptr)
	{
		if (!Obj.IsValid()) return false;
		if (Obj->HasField(KeyA)) return true;
		if (KeyB && Obj->HasField(KeyB)) return true;
		return false;
	}

	// Get graph scope from graph object
	FString GetGraphScope(const TSharedPtr<FJsonObject>& GraphObj, const FString& Fallback)
	{
		if (!GraphObj.IsValid()) return Fallback;
		FString Scope = GetJsonString(GraphObj, TEXT("graphGuid"), TEXT("GraphGuid"));
		return Scope.IsEmpty() ? Fallback : Scope;
	}
}

// ============================================================================
// Main entry point
// ============================================================================

FInferenceStats FBlueprintTypeInference::RunTypeInference(TSharedPtr<FJsonObject> ExportJson, int32 MaxPasses)
{
	if (!ExportJson.IsValid())
	{
		return FInferenceStats();
	}

	// Debug: Log root keys to detect casing issues
	TArray<FString> RootKeys;
	ExportJson->Values.GetKeys(RootKeys);
	UE_LOG(LogBlueprintExporter, Log, TEXT("[TypeInference] Root JSON keys: %s"), *FString::Join(RootKeys, TEXT(", ")));

	// Get Blueprint class path for context pins
	TSharedPtr<FJsonObject> ParentObj = GetJsonObject(ExportJson, TEXT("parentClass"), TEXT("ParentClass"));
	if (ParentObj.IsValid())
	{
		BlueprintClassPath = GetJsonString(ParentObj, TEXT("classPath"), TEXT("ClassPath"));
	}

	// Step 1: Build pin lookup map
	PinLookup.Empty();
	Connections.Empty();
	ResolvedPins.Empty();
	PotentialConflicts.Empty();

	BuildPinLookup(ExportJson);
	BuildConnectionGraph(ExportJson);

	// Step 2: Mark initially resolved pins
	for (auto& Pair : PinLookup)
	{
		FInferencePinData& Pin = Pair.Value;
		if (Pin.State == EResolutionState::UnrealResolved)
		{
			ResolvedPins.Add(Pair.Key);
		}
	}

	UE_LOG(LogBlueprintExporter, Log, TEXT("[TypeInference] Starting inference: %d pins, %d initially resolved, %d connections"),
		PinLookup.Num(), ResolvedPins.Num(), Connections.Num());

	// Step 3: Iterative inference
	int32 Pass = 0;
	for (Pass = 1; Pass <= MaxPasses; Pass++)
	{
		int32 TotalResolved = 0;

		// Hard inference (direct wire connections)
		int32 HardResolved = RunHardInferencePass(Pass);
		TotalResolved += HardResolved;

		// Soft inference (type carrier nodes)
		int32 SoftResolved = RunSoftInferencePass(Pass);
		TotalResolved += SoftResolved;

		UE_LOG(LogBlueprintExporter, Log, TEXT("[TypeInference] Pass %d: %d hard + %d soft = %d new resolutions"),
			Pass, HardResolved, SoftResolved, TotalResolved);

		if (TotalResolved == 0)
		{
			break; // Converged
		}
	}

	// Step 4: Mark static function self pins
	MarkStaticFunctionSelfPins(ExportJson);

	// Step 5: Finalize conflicts (deferred until after convergence)
	for (const FString& PinId : PotentialConflicts)
	{
		if (!ResolvedPins.Contains(PinId))
		{
			if (FInferencePinData* Pin = PinLookup.Find(PinId))
			{
				if (Pin->ConflictingTypes.Num() >= 2)
				{
					SetPinState(*Pin, EResolutionState::Conflict, 0, TEXT("conflicting_linked_types"));
				}
			}
		}
	}

	// Step 6: Finalize all pin metadata
	FinalizeAllPinMetadata();

	// Step 7: Compute and write stats
	FInferenceStats Stats = ComputeStats();
	Stats.PassesRun = Pass;
	WriteInferenceStats(ExportJson, Stats);

	UE_LOG(LogBlueprintExporter, Log, TEXT("[TypeInference] Complete: %d resolved (%d inferred), %d unresolved, %d conflicts"),
		Stats.ResolvedPins, Stats.InferredPins, Stats.UnresolvedPins, Stats.ConflictPins);

	return Stats;
}

void FBlueprintTypeInference::BuildPinLookup(TSharedPtr<FJsonObject> ExportJson)
{
	int32 TotalPinsAdded = 0;

	// Event graph
	{
		TSharedPtr<FJsonObject> EventGraph = GetJsonObject(ExportJson, TEXT("eventGraph"), TEXT("EventGraph"));
		if (EventGraph.IsValid())
		{
			int32 Before = PinLookup.Num();
			ProcessGraph(EventGraph, GetGraphScope(EventGraph, TEXT("EventGraph")));
			UE_LOG(LogBlueprintExporter, Log, TEXT("[TypeInference] EventGraph: added %d pins"), PinLookup.Num() - Before);
		}
	}

	// Functions
	{
		const TArray<TSharedPtr<FJsonValue>>* Functions = GetJsonArray(ExportJson, TEXT("functions"), TEXT("Functions"));
		if (Functions)
		{
			UE_LOG(LogBlueprintExporter, Log, TEXT("[TypeInference] Processing %d functions"), Functions->Num());
			for (const auto& FuncVal : *Functions)
			{
				TSharedPtr<FJsonObject> FuncObj = FuncVal->AsObject();
				if (!FuncObj.IsValid()) continue;

				TSharedPtr<FJsonObject> GraphObj = GetJsonObject(FuncObj, TEXT("graph"), TEXT("Graph"));
				if (!GraphObj.IsValid()) continue;

				FString FuncName = GetJsonString(FuncObj, TEXT("functionName"), TEXT("FunctionName"));
				int32 Before = PinLookup.Num();
				ProcessGraph(GraphObj, GetGraphScope(GraphObj, FuncName));
				UE_LOG(LogBlueprintExporter, Log, TEXT("[TypeInference] Function '%s': added %d pins (total: %d)"),
					*FuncName, PinLookup.Num() - Before, PinLookup.Num());
			}
		}
	}

	// Macros
	{
		const TArray<TSharedPtr<FJsonValue>>* Macros = GetJsonArray(ExportJson, TEXT("macros"), TEXT("Macros"));
		if (Macros)
		{
			for (const auto& MacroVal : *Macros)
			{
				TSharedPtr<FJsonObject> MacroObj = MacroVal->AsObject();
				if (!MacroObj.IsValid()) continue;

				TSharedPtr<FJsonObject> GraphObj = GetJsonObject(MacroObj, TEXT("graph"), TEXT("Graph"));
				if (!GraphObj.IsValid()) continue;

				FString MacroName = GetJsonString(MacroObj, TEXT("functionName"), TEXT("macroName"));
				ProcessGraph(GraphObj, GetGraphScope(GraphObj, MacroName));
			}
		}
	}
}

void FBlueprintTypeInference::ProcessGraph(TSharedPtr<FJsonObject> GraphObj, const FString& GraphScope)
{
	if (!GraphObj.IsValid()) return;

	const TArray<TSharedPtr<FJsonValue>>* Nodes = GetJsonArray(GraphObj, TEXT("nodes"), TEXT("Nodes"));
	if (!Nodes) return;

	for (const auto& NodeVal : *Nodes)
	{
		TSharedPtr<FJsonObject> NodeObj = NodeVal->AsObject();
		if (!NodeObj.IsValid()) continue;

		FString NodeGuid = GetJsonString(NodeObj, TEXT("nodeGuid"), TEXT("NodeGuid"));
		FString NodeClass = GetJsonString(NodeObj, TEXT("nodeClass"), TEXT("NodeClass"));
		bool bIsReroute = NodeClass.Contains(TEXT("Knot")) || NodeClass.Contains(TEXT("Reroute"));

		const TArray<TSharedPtr<FJsonValue>>* Pins = GetJsonArray(NodeObj, TEXT("pins"), TEXT("Pins"));
		if (!Pins) continue;

		for (const auto& PinVal : *Pins)
		{
			TSharedPtr<FJsonObject> PinObj = PinVal->AsObject();
			if (!PinObj.IsValid()) continue;

			FString PinName = GetJsonString(PinObj, TEXT("pinName"), TEXT("PinName"));
			FString Direction = GetJsonString(PinObj, TEXT("direction"), TEXT("Direction"));

			// Key format: GraphScope:NodeGuid:PinName:Direction
			FString PinKey = FString::Printf(TEXT("%s:%s:%s:%s"), *GraphScope, *NodeGuid, *PinName, *Direction);

			FInferencePinData PinData;
			PinData.PinObject = PinObj;
			PinData.NodeObject = NodeObj;
			PinData.GraphScope = GraphScope;
			PinData.NodeGuid = NodeGuid;
			PinData.NodeClass = NodeClass;
			PinData.PinName = PinName;
			PinData.Direction = Direction;
			PinData.bIsReroute = bIsReroute;

			// Extract type object
			TSharedPtr<FJsonObject> TypeObj = GetJsonObject(PinObj, TEXT("type"), TEXT("Type"));
			if (TypeObj.IsValid())
			{
				PinData.TypeObject = TypeObj;
				PinData.ExtractedSignature = ExtractTypeSignature(TypeObj);

				// Determine initial resolution state
				bool bPossibleInterface = false;
				FString Category = GetJsonString(TypeObj, TEXT("category"), TEXT("Category"));
				FString SubCat = GetJsonString(TypeObj, TEXT("subCategoryObject"), TEXT("SubCategoryObject"));

				ETypeKind Kind = DetermineKind(Category, SubCat, bPossibleInterface);
				PinData.bPossibleInterface = bPossibleInterface;
				PinData.ExtractedSignature.Kind = Kind;

				// Determine if Unreal resolved this
				if (Kind == ETypeKind::Exec || Kind == ETypeKind::Primitive)
				{
					PinData.State = EResolutionState::UnrealResolved;
				}
				else if (FTypeSignature::NeedsPath(Kind))
				{
					FString NormPath = NormalizePath(SubCat);
					if (!NormPath.IsEmpty() && NormPath != TEXT("None"))
					{
						PinData.State = EResolutionState::UnrealResolved;
					}
					else
					{
						PinData.State = EResolutionState::Unresolved;
						PinData.UnresolvedReason = FString::Printf(TEXT("missing_%s_path"), *FTypeSignature::KindToString(Kind));
					}
				}
				else if (Kind == ETypeKind::Wildcard)
				{
					PinData.State = EResolutionState::Unresolved;
					PinData.UnresolvedReason = TEXT("wildcard");
				}
				else
				{
					PinData.State = EResolutionState::Unresolved;
					PinData.UnresolvedReason = TEXT("unknown_category");
				}
			}

			PinLookup.Add(PinKey, PinData);
		}
	}
}

void FBlueprintTypeInference::BuildConnectionGraph(TSharedPtr<FJsonObject> ExportJson)
{
	// Process one graph's nodes for connections
	auto ProcessGraphConnections = [this](const TSharedPtr<FJsonObject>& GraphObj, const FString& GraphScope)
	{
		if (!GraphObj.IsValid()) return;

		const TArray<TSharedPtr<FJsonValue>>* Nodes = GetJsonArray(GraphObj, TEXT("nodes"), TEXT("Nodes"));
		if (!Nodes) return;

		for (const auto& NodeVal : *Nodes)
		{
			TSharedPtr<FJsonObject> NodeObj = NodeVal->AsObject();
			if (NodeObj.IsValid())
			{
				ProcessNodeConnections(NodeObj, GraphScope);
			}
		}
	};

	// Event graph
	{
		TSharedPtr<FJsonObject> EventGraph = GetJsonObject(ExportJson, TEXT("eventGraph"), TEXT("EventGraph"));
		if (EventGraph.IsValid())
		{
			ProcessGraphConnections(EventGraph, GetGraphScope(EventGraph, TEXT("EventGraph")));
		}
	}

	// Functions
	{
		const TArray<TSharedPtr<FJsonValue>>* Functions = GetJsonArray(ExportJson, TEXT("functions"), TEXT("Functions"));
		if (Functions)
		{
			for (const auto& FuncVal : *Functions)
			{
				TSharedPtr<FJsonObject> FuncObj = FuncVal->AsObject();
				if (!FuncObj.IsValid()) continue;

				TSharedPtr<FJsonObject> GraphObj = GetJsonObject(FuncObj, TEXT("graph"), TEXT("Graph"));
				if (!GraphObj.IsValid()) continue;

				FString FuncName = GetJsonString(FuncObj, TEXT("functionName"), TEXT("FunctionName"));
				ProcessGraphConnections(GraphObj, GetGraphScope(GraphObj, FuncName));
			}
		}
	}

	// Macros
	{
		const TArray<TSharedPtr<FJsonValue>>* Macros = GetJsonArray(ExportJson, TEXT("macros"), TEXT("Macros"));
		if (Macros)
		{
			for (const auto& MacroVal : *Macros)
			{
				TSharedPtr<FJsonObject> MacroObj = MacroVal->AsObject();
				if (!MacroObj.IsValid()) continue;

				TSharedPtr<FJsonObject> GraphObj = GetJsonObject(MacroObj, TEXT("graph"), TEXT("Graph"));
				if (!GraphObj.IsValid()) continue;

				FString MacroName = GetJsonString(MacroObj, TEXT("functionName"), TEXT("macroName"));
				ProcessGraphConnections(GraphObj, GetGraphScope(GraphObj, MacroName));
			}
		}
	}
}

void FBlueprintTypeInference::ProcessNodeConnections(TSharedPtr<FJsonObject> NodeObj, const FString& GraphScope)
{
	FString NodeGuid = GetJsonString(NodeObj, TEXT("nodeGuid"), TEXT("NodeGuid"));

	const TArray<TSharedPtr<FJsonValue>>* Pins = GetJsonArray(NodeObj, TEXT("pins"), TEXT("Pins"));
	if (!Pins) return;

	for (const auto& PinVal : *Pins)
	{
		TSharedPtr<FJsonObject> PinObj = PinVal->AsObject();
		if (!PinObj.IsValid()) continue;

		FString PinName = GetJsonString(PinObj, TEXT("pinName"), TEXT("PinName"));
		FString Direction = GetJsonString(PinObj, TEXT("direction"), TEXT("Direction"));
		FString SourcePinKey = FString::Printf(TEXT("%s:%s:%s:%s"), *GraphScope, *NodeGuid, *PinName, *Direction);

		const TArray<TSharedPtr<FJsonValue>>* ConnectionsArr = GetJsonArray(PinObj, TEXT("connections"), TEXT("Connections"));
		if (!ConnectionsArr) continue;

		for (const auto& ConnVal : *ConnectionsArr)
		{
			TSharedPtr<FJsonObject> ConnObj = ConnVal->AsObject();
			if (!ConnObj.IsValid()) continue;

			// Connection format: nodeId contains NodeGuid, pinId contains PinName
			FString TargetNodeGuid = GetJsonString(ConnObj, TEXT("nodeId"), TEXT("NodeId"));
			FString TargetPinName = GetJsonString(ConnObj, TEXT("pinId"), TEXT("PinId"));

			// Target direction is opposite of source direction
			FString TargetDirection = (Direction == TEXT("Input")) ? TEXT("Output") : TEXT("Input");
			FString TargetPinKey = FString::Printf(TEXT("%s:%s:%s:%s"), *GraphScope, *TargetNodeGuid, *TargetPinName, *TargetDirection);

			// Add connection (source -> target)
			Connections.Add(SourcePinKey, TargetPinKey);
		}
	}
}

FTypeSignature FBlueprintTypeInference::ExtractTypeSignature(TSharedPtr<FJsonObject> TypeObj)
{
	FTypeSignature Sig;

	if (!TypeObj.IsValid())
	{
		return Sig;
	}

	// Safe access with case tolerance
	Sig.Category = GetJsonString(TypeObj, TEXT("category"), TEXT("Category"));
	FString SubCat = GetJsonString(TypeObj, TEXT("subCategoryObject"), TEXT("SubCategoryObject"));
	Sig.Path = NormalizePath(SubCat);

	// Container flags
	bool bIsArray = false, bIsSet = false, bIsMap = false;
	TypeObj->TryGetBoolField(TEXT("isArray"), bIsArray);
	TypeObj->TryGetBoolField(TEXT("isSet"), bIsSet);
	TypeObj->TryGetBoolField(TEXT("isMap"), bIsMap);

	Sig.Container = bIsArray ? EContainerType::Array
		: bIsSet ? EContainerType::Set
		: bIsMap ? EContainerType::Map
		: EContainerType::None;

	// Reference flags
	TypeObj->TryGetBoolField(TEXT("isReference"), Sig.bIsReference);
	TypeObj->TryGetBoolField(TEXT("isConst"), Sig.bIsConst);

	// Determine kind
	bool bPossibleInterface = false;
	Sig.Kind = DetermineKind(Sig.Category, SubCat, bPossibleInterface);

	return Sig;
}

void FBlueprintTypeInference::ApplyInferredType(FInferencePinData& Pin, const FTypeSignature& Type, int32 Pass, const TArray<FPinReference>& Sources)
{
	if (!Pin.TypeObject.IsValid())
	{
		return;
	}

	// Apply the type
	Pin.TypeObject->SetStringField(TEXT("category"), Type.Category);
	Pin.TypeObject->SetStringField(TEXT("subCategoryObject"), Type.Path);

	// Container flags
	Pin.TypeObject->SetBoolField(TEXT("isArray"), Type.Container == EContainerType::Array);
	Pin.TypeObject->SetBoolField(TEXT("isSet"), Type.Container == EContainerType::Set);
	Pin.TypeObject->SetBoolField(TEXT("isMap"), Type.Container == EContainerType::Map);

	// Mark container element types as unresolved if we don't have them
	if (Type.Container == EContainerType::Array || Type.Container == EContainerType::Set)
	{
		if (!Type.ElementType.IsSet() || !Type.ElementType.GetValue().IsValid())
		{
			Pin.TypeObject->SetBoolField(TEXT("containerElementUnresolved"), true);
		}
	}
	if (Type.Container == EContainerType::Map)
	{
		if (!Type.MapKeyType.IsSet() || !Type.MapKeyType.GetValue().IsValid() ||
			!Type.MapValueType.IsSet() || !Type.MapValueType.GetValue().IsValid())
		{
			Pin.TypeObject->SetBoolField(TEXT("containerElementUnresolved"), true);
		}
	}

	// Metadata
	Pin.TypeObject->SetBoolField(TEXT("resolved"), true);
	Pin.TypeObject->SetStringField(TEXT("resolvedBy"), TEXT("inferred"));
	Pin.TypeObject->SetNumberField(TEXT("inferredPass"), Pass);
	Pin.TypeObject->SetStringField(TEXT("inferredTypeHash"), Type.GetHash());
	Pin.TypeObject->SetBoolField(TEXT("typeWasModifiedByInference"), true);

	// Provenance - minimal identifiers
	TArray<TSharedPtr<FJsonValue>> ProvenanceArray;
	for (const FPinReference& Ref : Sources)
	{
		TSharedPtr<FJsonObject> RefObj = MakeShared<FJsonObject>();
		RefObj->SetStringField(TEXT("nodeGuid"), Ref.NodeGuid);
		RefObj->SetStringField(TEXT("pinName"), Ref.PinName);
		RefObj->SetStringField(TEXT("direction"), Ref.Direction);
		ProvenanceArray.Add(MakeShared<FJsonValueObject>(RefObj));
	}

	// Sort for deterministic output
	ProvenanceArray.Sort([](const TSharedPtr<FJsonValue>& A, const TSharedPtr<FJsonValue>& B)
	{
		FString KeyA = A->AsObject()->GetStringField(TEXT("nodeGuid")) + TEXT(":") +
			A->AsObject()->GetStringField(TEXT("pinName")) + TEXT(":") +
			A->AsObject()->GetStringField(TEXT("direction"));
		FString KeyB = B->AsObject()->GetStringField(TEXT("nodeGuid")) + TEXT(":") +
			B->AsObject()->GetStringField(TEXT("pinName")) + TEXT(":") +
			B->AsObject()->GetStringField(TEXT("direction"));
		return KeyA < KeyB;
	});

	Pin.TypeObject->SetArrayField(TEXT("inferredFrom"), ProvenanceArray);

	// Update internal state
	Pin.InferredFrom = Sources;
	Pin.InferredPass = Pass;
	Pin.ExtractedSignature = Type;
}

void FBlueprintTypeInference::MarkTypeConflict(FInferencePinData& Pin, const TArray<FTypeSignature>& ConflictingTypesArr)
{
	if (!Pin.TypeObject.IsValid())
	{
		return;
	}

	// Dedupe by hash
	TMap<FString, FTypeSignature> UniqueByHash;
	for (const FTypeSignature& Type : ConflictingTypesArr)
	{
		FString Hash = Type.GetHash();
		if (!UniqueByHash.Contains(Hash))
		{
			UniqueByHash.Add(Hash, Type);
		}
	}

	// Convert to array and sort
	TArray<FTypeSignature> Deduped;
	UniqueByHash.GenerateValueArray(Deduped);
	Deduped.Sort([](const FTypeSignature& A, const FTypeSignature& B)
	{
		return A.GetHash() < B.GetHash();
	});

	Pin.ConflictingTypes = Deduped;

	// Write to JSON
	Pin.TypeObject->SetBoolField(TEXT("resolved"), false);
	Pin.TypeObject->SetBoolField(TEXT("typeConflict"), true);
	Pin.TypeObject->SetStringField(TEXT("resolvedBy"), TEXT("unresolved"));
	Pin.TypeObject->SetStringField(TEXT("unresolvedReason"), TEXT("conflicting_linked_types"));

	// Full signatures for debugging
	TArray<TSharedPtr<FJsonValue>> ConflictArray;
	for (const FTypeSignature& Type : Deduped)
	{
		TSharedPtr<FJsonObject> TypeSig = MakeShared<FJsonObject>();
		TypeSig->SetStringField(TEXT("kind"), FTypeSignature::KindToString(Type.Kind));
		TypeSig->SetStringField(TEXT("category"), Type.Category);
		TypeSig->SetStringField(TEXT("path"), Type.Path);
		TypeSig->SetStringField(TEXT("container"), FTypeSignature::ContainerToString(Type.Container));
		ConflictArray.Add(MakeShared<FJsonValueObject>(TypeSig));
	}
	Pin.TypeObject->SetArrayField(TEXT("conflictingTypes"), ConflictArray);
}

void FBlueprintTypeInference::SetPinState(FInferencePinData& Pin, EResolutionState NewState, int32 InferPass, const FString& Reason)
{
	// Unreal truth is immutable
	if (Pin.State == EResolutionState::UnrealResolved)
	{
		ensureMsgf(NewState == EResolutionState::UnrealResolved,
			TEXT("Cannot transition from UnrealResolved"));
		return;
	}

	Pin.State = NewState;

	// Clean metadata based on new state
	switch (NewState)
	{
	case EResolutionState::UnrealResolved:
		Pin.InferredPass = 0;
		Pin.UnresolvedReason.Empty();
		Pin.InferredFrom.Empty();
		break;

	case EResolutionState::Inferred:
		Pin.InferredPass = InferPass;
		Pin.UnresolvedReason.Empty();
		break;

	case EResolutionState::Conflict:
		Pin.InferredPass = 0;
		Pin.UnresolvedReason = TEXT("conflicting_linked_types");
		Pin.InferredFrom.Empty();
		break;

	case EResolutionState::Unresolved:
		Pin.InferredPass = 0;
		Pin.UnresolvedReason = Reason.IsEmpty() ? TEXT("no_concrete_links") : Reason;
		Pin.InferredFrom.Empty();
		break;
	}
}

int32 FBlueprintTypeInference::RunHardInferencePass(int32 Pass)
{
	int32 NewlyResolved = 0;

	for (auto& Pair : PinLookup)
	{
		const FString& PinId = Pair.Key;
		FInferencePinData& Pin = Pair.Value;

		// Skip already resolved, exec, and primitive pins
		if (ResolvedPins.Contains(PinId)) continue;
		if (Pin.ExtractedSignature.Kind == ETypeKind::Exec) continue;
		if (Pin.ExtractedSignature.Kind == ETypeKind::Primitive) continue;

		// Get types from connected pins
		TArray<FTypeSignature> LinkedTypes;
		TArray<FPinReference> LinkedRefs;

		TArray<FString> ConnectedPins;
		Connections.MultiFind(PinId, ConnectedPins);

		for (const FString& LinkedPinId : ConnectedPins)
		{
			if (ResolvedPins.Contains(LinkedPinId))
			{
				if (const FInferencePinData* LinkedPin = PinLookup.Find(LinkedPinId))
				{
					// Filter out wildcards, exec, context, unknown
					const FTypeSignature& LinkedSig = LinkedPin->ExtractedSignature;
					if (LinkedSig.Kind == ETypeKind::Wildcard) continue;
					if (LinkedSig.Kind == ETypeKind::Exec) continue;
					if (LinkedSig.Kind == ETypeKind::Context) continue;
					if (LinkedSig.Kind == ETypeKind::Unknown) continue;
					if (FTypeSignature::NeedsPath(LinkedSig.Kind) && LinkedSig.Path.IsEmpty()) continue;

					LinkedTypes.Add(LinkedSig);

					FPinReference Ref;
					Ref.GraphScope = LinkedPin->GraphScope;
					Ref.NodeGuid = LinkedPin->NodeGuid;
					Ref.PinName = LinkedPin->PinName;
					Ref.Direction = LinkedPin->Direction;
					LinkedRefs.Add(Ref);
				}
			}
		}

		if (LinkedTypes.Num() == 0) continue; // No resolved links

		// Try to unify
		TOptional<FTypeSignature> Unified = TryUnify(LinkedTypes);

		if (Unified.IsSet())
		{
			// Success - apply inferred type
			ApplyInferredType(Pin, Unified.GetValue(), Pass, LinkedRefs);
			SetPinState(Pin, EResolutionState::Inferred, Pass);
			ResolvedPins.Add(PinId);
			NewlyResolved++;
		}
		else if (LinkedTypes.Num() >= 2)
		{
			// Check if we have 2+ distinct concrete types
			TSet<FString> UniqueConcreteHashes;
			TArray<FTypeSignature> ConcreteTypes;
			for (const FTypeSignature& Type : LinkedTypes)
			{
				if (Type.IsConcrete())
				{
					UniqueConcreteHashes.Add(Type.GetHash());
					ConcreteTypes.Add(Type);
				}
			}

			if (UniqueConcreteHashes.Num() >= 2)
			{
				// Mark potential conflict (finalized after convergence)
				PotentialConflicts.Add(PinId);
				Pin.ConflictingTypes = ConcreteTypes;
			}
		}
	}

	return NewlyResolved;
}

int32 FBlueprintTypeInference::RunSoftInferencePass(int32 Pass)
{
	int32 NewlyResolved = 0;

	// Type carrier nodes propagate types across their pins
	const TSet<FString>& Carriers = GetTypeCarrierNodes();

	for (auto& Pair : PinLookup)
	{
		const FString& PinId = Pair.Key;
		FInferencePinData& Pin = Pair.Value;

		// Skip already resolved
		if (ResolvedPins.Contains(PinId)) continue;
		if (Pin.ExtractedSignature.Kind == ETypeKind::Exec) continue;
		if (Pin.ExtractedSignature.Kind == ETypeKind::Primitive) continue;

		// Check if this is a type carrier node
		bool bIsCarrier = false;
		for (const FString& Carrier : Carriers)
		{
			if (Pin.NodeClass.Contains(Carrier))
			{
				bIsCarrier = true;
				break;
			}
		}

		if (!bIsCarrier) continue;

		// For reroute nodes, find any resolved pin on the same node
		// and propagate its type to unresolved pins

		// Collect all pins on this node
		TArray<FString> SameNodePins;
		for (const auto& OtherPair : PinLookup)
		{
			const FInferencePinData& OtherPin = OtherPair.Value;
			if (OtherPin.GraphScope == Pin.GraphScope && OtherPin.NodeGuid == Pin.NodeGuid)
			{
				SameNodePins.Add(OtherPair.Key);
			}
		}

		// Find resolved pins on same node (excluding exec/primitive)
		FTypeSignature ResolvedType;
		bool bFoundResolved = false;
		TArray<FPinReference> Sources;

		for (const FString& OtherPinId : SameNodePins)
		{
			if (ResolvedPins.Contains(OtherPinId))
			{
				const FInferencePinData* OtherPin = PinLookup.Find(OtherPinId);
				if (OtherPin && OtherPin->ExtractedSignature.Kind != ETypeKind::Exec &&
					OtherPin->ExtractedSignature.Kind != ETypeKind::Primitive)
				{
					if (OtherPin->ExtractedSignature.IsConcrete())
					{
						ResolvedType = OtherPin->ExtractedSignature;
						bFoundResolved = true;

						FPinReference Ref;
						Ref.GraphScope = OtherPin->GraphScope;
						Ref.NodeGuid = OtherPin->NodeGuid;
						Ref.PinName = OtherPin->PinName;
						Ref.Direction = OtherPin->Direction;
						Sources.Add(Ref);
						break;
					}
				}
			}
		}

		if (bFoundResolved)
		{
			ApplyInferredType(Pin, ResolvedType, Pass, Sources);
			SetPinState(Pin, EResolutionState::Inferred, Pass);
			ResolvedPins.Add(PinId);
			NewlyResolved++;

			// Mark as soft inference
			if (Pin.TypeObject.IsValid())
			{
				Pin.TypeObject->SetStringField(TEXT("inferConfidence"), TEXT("soft"));
			}
		}
	}

	return NewlyResolved;
}

TOptional<FTypeSignature> FBlueprintTypeInference::TryUnify(const TArray<FTypeSignature>& Types)
{
	// Filter out wildcards, exec, context, unknown, missing paths
	TArray<FTypeSignature> ConcreteTypes;
	for (const FTypeSignature& Type : Types)
	{
		if (Type.Kind == ETypeKind::Wildcard) continue;
		if (Type.Kind == ETypeKind::Exec) continue;
		if (Type.Kind == ETypeKind::Context) continue;
		if (Type.Kind == ETypeKind::Unknown) continue;
		if (FTypeSignature::NeedsPath(Type.Kind) && Type.Path.IsEmpty()) continue;

		ConcreteTypes.Add(Type);
	}

	if (ConcreteTypes.Num() == 0) return TOptional<FTypeSignature>(); // All wildcards
	if (ConcreteTypes.Num() == 1) return ConcreteTypes[0];

	// Check equality among concrete types (no inheritance unification without schema)
	const FTypeSignature& First = ConcreteTypes[0];
	for (int32 i = 1; i < ConcreteTypes.Num(); i++)
	{
		if (!First.Equals(ConcreteTypes[i]))
		{
			return TOptional<FTypeSignature>(); // Conflict
		}
	}

	return First;
}

void FBlueprintTypeInference::MarkStaticFunctionSelfPins(TSharedPtr<FJsonObject> ExportJson)
{
	// Find CallFunction nodes and mark their self pins as context
	for (auto& Pair : PinLookup)
	{
		FInferencePinData& Pin = Pair.Value;

		// Look for self pins on CallFunction nodes that are unresolved
		if (Pin.State != EResolutionState::Unresolved) continue;
		if (Pin.PinName != TEXT("self")) continue;
		if (!Pin.NodeClass.Contains(TEXT("CallFunction"))) continue;

		// Parse nodeSpecificData to get library class and function name
		FString LibraryClass;
		FString FunctionName;
		FString FunctionOwnerClass;

		if (Pin.NodeObject.IsValid())
		{
			TSharedPtr<FJsonObject> NodeSpecificData = GetJsonObject(Pin.NodeObject, TEXT("nodeSpecificData"), TEXT("NodeSpecificData"));
			if (NodeSpecificData.IsValid())
			{
				FunctionOwnerClass = GetJsonString(NodeSpecificData, TEXT("functionOwnerClass"), TEXT("FunctionOwnerClass"));
				FunctionName = GetJsonString(NodeSpecificData, TEXT("functionName"), TEXT("FunctionName"));

				// Check if it's a library function (static)
				if (FunctionOwnerClass.Contains(TEXT("Library")) ||
					FunctionOwnerClass.Contains(TEXT("Statics")) ||
					FunctionOwnerClass.Contains(TEXT("BlueprintFunctionLibrary")))
				{
					LibraryClass = FunctionOwnerClass;
				}
			}
		}

		// Mark as context pin
		if (Pin.TypeObject.IsValid())
		{
			Pin.TypeObject->SetStringField(TEXT("kind"), TEXT("context"));
			Pin.TypeObject->SetBoolField(TEXT("resolved"), false);
			Pin.TypeObject->SetStringField(TEXT("resolvedBy"), TEXT("unresolved"));
			Pin.TypeObject->SetStringField(TEXT("unresolvedReason"), TEXT("static_function_self"));
			Pin.TypeObject->SetStringField(TEXT("context"), TEXT("blueprint"));
			Pin.TypeObject->SetStringField(TEXT("contextClass"), BlueprintClassPath);

			if (!LibraryClass.IsEmpty())
			{
				Pin.TypeObject->SetStringField(TEXT("libraryClass"), LibraryClass);
			}
			if (!FunctionOwnerClass.IsEmpty())
			{
				Pin.TypeObject->SetStringField(TEXT("functionOwnerClass"), FunctionOwnerClass);
			}
			if (!FunctionName.IsEmpty())
			{
				Pin.TypeObject->SetStringField(TEXT("functionName"), FunctionName);
			}
		}

		SetPinState(Pin, EResolutionState::Unresolved, 0, TEXT("static_function_self"));
	}
}

void FBlueprintTypeInference::FinalizeAllPinMetadata()
{
	for (auto& Pair : PinLookup)
	{
		FInferencePinData& Pin = Pair.Value;

		// Invariant check: can't be both Unreal-resolved AND inferred
		if (Pin.State == EResolutionState::UnrealResolved && Pin.InferredPass > 0)
		{
			ensureMsgf(false, TEXT("Pin %s marked both Unreal-resolved and inferred"), *Pair.Key);
			Pin.InferredPass = 0;
			Pin.bInvariantViolation = true;

			// Clear inference artifacts
			if (Pin.TypeObject.IsValid())
			{
				Pin.TypeObject->RemoveField(TEXT("inferredPass"));
				Pin.TypeObject->RemoveField(TEXT("inferConfidence"));
				Pin.TypeObject->RemoveField(TEXT("inferredFrom"));
				Pin.TypeObject->RemoveField(TEXT("evidenceSummary"));
				Pin.TypeObject->RemoveField(TEXT("inferredTypeHash"));
				Pin.TypeObject->SetBoolField(TEXT("invariantViolation"), true);
			}
		}

		// Default unresolved reason
		if (Pin.State == EResolutionState::Unresolved && Pin.UnresolvedReason.IsEmpty())
		{
			Pin.UnresolvedReason = TEXT("no_concrete_links");
		}

		// Ensure all pins have resolvedBy set
		if (Pin.TypeObject.IsValid())
		{
			switch (Pin.State)
			{
			case EResolutionState::UnrealResolved:
				Pin.TypeObject->SetBoolField(TEXT("resolved"), true);
				Pin.TypeObject->SetStringField(TEXT("resolvedBy"), TEXT("unreal"));
				break;

			case EResolutionState::Inferred:
				Pin.TypeObject->SetBoolField(TEXT("resolved"), true);
				Pin.TypeObject->SetStringField(TEXT("resolvedBy"), TEXT("inferred"));
				if (!Pin.TypeObject->HasField(TEXT("inferConfidence")))
				{
					Pin.TypeObject->SetStringField(TEXT("inferConfidence"), TEXT("hard"));
				}
				break;

			case EResolutionState::Conflict:
				Pin.TypeObject->SetBoolField(TEXT("resolved"), false);
				Pin.TypeObject->SetStringField(TEXT("resolvedBy"), TEXT("unresolved"));
				Pin.TypeObject->SetStringField(TEXT("unresolvedReason"), Pin.UnresolvedReason);
				break;

			case EResolutionState::Unresolved:
				Pin.TypeObject->SetBoolField(TEXT("resolved"), false);
				Pin.TypeObject->SetStringField(TEXT("resolvedBy"), TEXT("unresolved"));
				Pin.TypeObject->SetStringField(TEXT("unresolvedReason"), Pin.UnresolvedReason);
				break;
			}

			// Possible interface hint
			if (Pin.bPossibleInterface)
			{
				Pin.TypeObject->SetBoolField(TEXT("possibleInterface"), true);
			}
		}
	}
}

FInferenceStats FBlueprintTypeInference::ComputeStats()
{
	FInferenceStats Stats;
	Stats.TotalPins = PinLookup.Num();

	for (const auto& Pair : PinLookup)
	{
		const FInferencePinData& Pin = Pair.Value;
		bool bIsComplex = IsComplexType(Pin);

		if (bIsComplex) Stats.TotalComplexPins++;

		switch (Pin.State)
		{
		case EResolutionState::UnrealResolved:
			Stats.UnrealResolvedPins++;
			if (bIsComplex) Stats.UnrealResolvedComplexPins++;
			break;

		case EResolutionState::Inferred:
			Stats.InferredPins++;
			if (bIsComplex) Stats.InferredComplexPins++;
			break;

		case EResolutionState::Conflict:
			Stats.ConflictPins++;
			break;

		case EResolutionState::Unresolved:
			// Just unresolved, no conflict
			break;
		}
	}

	// Derived - cannot drift
	Stats.ResolvedPins = Stats.UnrealResolvedPins + Stats.InferredPins;
	Stats.UnresolvedPins = Stats.TotalPins - Stats.ResolvedPins;
	Stats.UnresolvedComplexPins = Stats.TotalComplexPins - Stats.UnrealResolvedComplexPins - Stats.InferredComplexPins;

	// Invariants
	ensureMsgf(Stats.ResolvedPins + Stats.UnresolvedPins == Stats.TotalPins,
		TEXT("Stats total mismatch: %d + %d != %d"),
		Stats.ResolvedPins, Stats.UnresolvedPins, Stats.TotalPins);
	ensureMsgf(Stats.ConflictPins <= Stats.UnresolvedPins,
		TEXT("Conflict count exceeds unresolved: %d > %d"),
		Stats.ConflictPins, Stats.UnresolvedPins);

	return Stats;
}

void FBlueprintTypeInference::WriteInferenceStats(TSharedPtr<FJsonObject> ExportJson, const FInferenceStats& Stats)
{
	if (!ExportJson.IsValid())
	{
		return;
	}

	ExportJson->SetObjectField(TEXT("inferenceStats"), Stats.ToJson());
}
