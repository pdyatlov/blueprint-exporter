// Copyright Epic Games, Inc. All Rights Reserved.

#include "Serialization/BlueprintSerializer.h"
#include "BlueprintExporterModule.h"
#include "Engine/Blueprint.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/SimpleConstructionScript.h"
#include "Engine/SCS_Node.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraphSchema_K2.h"
#include "K2Node.h"
#include "K2Node_Event.h"
#include "K2Node_FunctionEntry.h"
#include "K2Node_FunctionResult.h"
#include "K2Node_CallFunction.h"
#include "K2Node_CallDelegate.h"
#include "K2Node_VariableGet.h"
#include "K2Node_VariableSet.h"
#include "K2Node_MacroInstance.h"
#include "K2Node_Composite.h"
#include "K2Node_Tunnel.h"
#include "K2Node_IfThenElse.h"
#include "K2Node_SwitchEnum.h"
#include "K2Node_SwitchString.h"
#include "K2Node_SwitchInteger.h"
#include "K2Node_ForEachElementInEnum.h"
#include "K2Node_MakeArray.h"
#include "K2Node_MakeStruct.h"
#include "K2Node_BreakStruct.h"
#include "K2Node_SpawnActorFromClass.h"
#include "K2Node_DynamicCast.h"
#include "K2Node_Self.h"
#include "K2Node_TemporaryVariable.h"
#include "K2Node_LocalVariable.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Misc/EngineVersionComparison.h"
#include "Serialization/JsonSerializer.h"
#include "Components/ActorComponent.h"
#include "UObject/UnrealType.h"

// AnimBP state machine includes
#include "AnimGraphNode_StateMachine.h"
#include "AnimationStateMachineGraph.h"
#include "AnimStateNode.h"
#include "AnimStateTransitionNode.h"
#include "AnimStateConduitNode.h"
#include "AnimStateEntryNode.h"
#include "AnimStateNodeBase.h"

// UMG — WidgetBlueprint tree walk (Track A, M3.3 closeout). UMG ships
// with the engine; always present, no optional-detection needed.
#include "BaseWidgetBlueprint.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Widget.h"
#include "Components/PanelWidget.h"
#include "Components/PanelSlot.h"

// Content-derived stable hash for a graph node.
//
// The engine's `UEdGraphNode::NodeGuid` is not a stable identifier across
// loads for every node. Specifically, nodes that UE auto-regenerates on
// load (e.g. `K2Node_CallFunction` wrapping engine functions whose
// signatures have drifted since the asset was authored) get a fresh GUID
// each time the asset streams in. That drift propagated into our
// `.meta.json` output as `nodeGuid` and through the `nodeId` suffix,
// defeating the byte-identical-across-runs determinism contract (brief §8)
// when verified by `scripts/verify_determinism.ps1` against the full DOW
// inventory.
//
// The fix: derive a deterministic 32-hex-char identifier from the stable
// parts of the node — its class name, function / variable name if
// applicable, authored position, and the ordered pin signature (name +
// direction). Two loads of the same unmodified asset produce the same
// hash; an actual authoring change (renamed pin, moved node, swapped
// function) produces a different one, which is the correct behaviour.
static FString ComputeStableNodeHash(const UEdGraphNode* Node)
{
	if (!Node)
	{
		return FString();
	}

	TStringBuilder<512> Signature;
	Signature << Node->GetClass()->GetName() << TEXT('|');
	Signature << Node->NodePosX << TEXT(',') << Node->NodePosY << TEXT('|');

	// Subtype-specific identity so that two different CallFunction nodes at
	// the same position (pathological but possible) with different target
	// functions produce different hashes.
	if (const UK2Node_CallFunction* CallNode = Cast<UK2Node_CallFunction>(Node))
	{
		Signature << TEXT("fn=") << CallNode->FunctionReference.GetMemberName().ToString() << TEXT('|');
	}
	else if (const UK2Node_Event* EventNode = Cast<UK2Node_Event>(Node))
	{
		Signature << TEXT("ev=") << EventNode->GetFunctionName().ToString() << TEXT('|');
	}
	else if (const UK2Node_VariableGet* VarGet = Cast<UK2Node_VariableGet>(Node))
	{
		Signature << TEXT("vg=") << VarGet->GetVarName().ToString() << TEXT('|');
	}
	else if (const UK2Node_VariableSet* VarSet = Cast<UK2Node_VariableSet>(Node))
	{
		Signature << TEXT("vs=") << VarSet->GetVarName().ToString() << TEXT('|');
	}

	// Pin signature. Pin indices are stable within a single load; in the
	// face of auto-regenerated nodes we still get a consistent hash as long
	// as the regenerated pin set matches the authored pin set (which it
	// does — UE's regeneration recreates the same pins by schema).
	for (const UEdGraphPin* Pin : Node->Pins)
	{
		if (Pin)
		{
			Signature << (Pin->Direction == EGPD_Input ? TEXT('I') : TEXT('O'));
			Signature << Pin->PinName.ToString();
			Signature << TEXT(';');
		}
	}

	// SHA1 → hex, take first 32 chars (16 bytes) so the result looks like
	// an FGuid string. Callers emitting this into the `nodeGuid` JSON field
	// stay shape-compatible with pre-M6.1 readers.
	const FTCHARToUTF8 Utf8(Signature.ToString());
	FSHAHash Hash;
	FSHA1::HashBuffer((const uint8*)Utf8.Get(), Utf8.Length(), Hash.Hash);
	FString Hex;
	Hex.Reserve(32);
	for (int32 i = 0; i < 16; ++i)
	{
		Hex += FString::Printf(TEXT("%02X"), Hash.Hash[i]);
	}
	return Hex;
}

// Helper function to get the type path from an FProperty using reflection
// This is safer than accessing weak pointers in FEdGraphPinType
static FString GetTypePathFromProperty(const FProperty* Property)
{
	if (!Property)
	{
		return FString();
	}

	// Handle struct properties
	if (const FStructProperty* StructProp = CastField<FStructProperty>(Property))
	{
		if (StructProp->Struct)
		{
			return StructProp->Struct->GetPathName();
		}
	}
	// Handle object properties
	else if (const FObjectPropertyBase* ObjProp = CastField<FObjectPropertyBase>(Property))
	{
		if (ObjProp->PropertyClass)
		{
			return ObjProp->PropertyClass->GetPathName();
		}
	}
	// Handle class properties
	else if (const FClassProperty* ClassProp = CastField<FClassProperty>(Property))
	{
		if (ClassProp->MetaClass)
		{
			return ClassProp->MetaClass->GetPathName();
		}
	}
	// Handle interface properties
	else if (const FInterfaceProperty* InterfaceProp = CastField<FInterfaceProperty>(Property))
	{
		if (InterfaceProp->InterfaceClass)
		{
			return InterfaceProp->InterfaceClass->GetPathName();
		}
	}
	// Handle enum properties
	else if (const FEnumProperty* EnumProp = CastField<FEnumProperty>(Property))
	{
		if (EnumProp->GetEnum())
		{
			return EnumProp->GetEnum()->GetPathName();
		}
	}
	else if (const FByteProperty* ByteProp = CastField<FByteProperty>(Property))
	{
		if (ByteProp->Enum)
		{
			return ByteProp->Enum->GetPathName();
		}
	}
	// Handle array properties - get inner type
	else if (const FArrayProperty* ArrayProp = CastField<FArrayProperty>(Property))
	{
		return GetTypePathFromProperty(ArrayProp->Inner);
	}
	// Handle set properties - get element type
	else if (const FSetProperty* SetProp = CastField<FSetProperty>(Property))
	{
		return GetTypePathFromProperty(SetProp->ElementProp);
	}
	// Handle map properties - return key:value types
	else if (const FMapProperty* MapProp = CastField<FMapProperty>(Property))
	{
		FString KeyType = GetTypePathFromProperty(MapProp->KeyProp);
		FString ValueType = GetTypePathFromProperty(MapProp->ValueProp);
		if (!KeyType.IsEmpty() || !ValueType.IsEmpty())
		{
			return FString::Printf(TEXT("Map<%s,%s>"), *KeyType, *ValueType);
		}
	}
	// Handle soft object/class references
	else if (const FSoftObjectProperty* SoftObjProp = CastField<FSoftObjectProperty>(Property))
	{
		if (SoftObjProp->PropertyClass)
		{
			return SoftObjProp->PropertyClass->GetPathName();
		}
	}
	else if (const FSoftClassProperty* SoftClassProp = CastField<FSoftClassProperty>(Property))
	{
		if (SoftClassProp->MetaClass)
		{
			return SoftClassProp->MetaClass->GetPathName();
		}
	}

	return FString();
}

// Helper to get map value type path from FProperty
static FString GetMapValueTypePathFromProperty(const FProperty* Property)
{
	if (const FMapProperty* MapProp = CastField<FMapProperty>(Property))
	{
		return GetTypePathFromProperty(MapProp->ValueProp);
	}
	return FString();
}

// Helper to resolve pin type from the owning node context
// This uses reflection and node-specific APIs to safely get type info without accessing weak pointers
static FString GetTypePathFromPinContext(const UEdGraphPin* Pin)
{
	if (!Pin)
	{
		return FString();
	}

	UEdGraphNode* OwningNode = Pin->GetOwningNode();
	if (!OwningNode)
	{
		return FString();
	}

	// Handle Variable Get/Set nodes - look up the variable type
	if (const UK2Node_VariableGet* VarGetNode = Cast<UK2Node_VariableGet>(OwningNode))
	{
		// Get the variable's property from the class
		FProperty* VarProp = VarGetNode->GetPropertyForVariable();
		if (VarProp)
		{
			return GetTypePathFromProperty(VarProp);
		}
	}
	else if (const UK2Node_VariableSet* VarSetNode = Cast<UK2Node_VariableSet>(OwningNode))
	{
		FProperty* VarProp = VarSetNode->GetPropertyForVariable();
		if (VarProp)
		{
			return GetTypePathFromProperty(VarProp);
		}
	}
	// Handle CallFunction nodes - get parameter types from UFunction
	else if (const UK2Node_CallFunction* CallFuncNode = Cast<UK2Node_CallFunction>(OwningNode))
	{
		UFunction* Func = CallFuncNode->GetTargetFunction();
		if (Func)
		{
			// Find the property that matches this pin's name
			FName PinName = Pin->PinName;

			// Check for return value first
			if (PinName == UEdGraphSchema_K2::PN_ReturnValue)
			{
				if (FProperty* ReturnProp = Func->GetReturnProperty())
				{
					return GetTypePathFromProperty(ReturnProp);
				}
			}

			// Search through function parameters
			for (TFieldIterator<FProperty> PropIt(Func); PropIt; ++PropIt)
			{
				FProperty* Prop = *PropIt;
				if (Prop->GetFName() == PinName)
				{
					return GetTypePathFromProperty(Prop);
				}
			}
		}
	}
	// Handle DynamicCast nodes - get the target class
	else if (const UK2Node_DynamicCast* CastNode = Cast<UK2Node_DynamicCast>(OwningNode))
	{
		UClass* TargetClass = CastNode->TargetType;
		if (TargetClass)
		{
			return TargetClass->GetPathName();
		}
	}
	// Handle MakeStruct nodes
	else if (const UK2Node_MakeStruct* MakeStructNode = Cast<UK2Node_MakeStruct>(OwningNode))
	{
		if (MakeStructNode->StructType)
		{
			return MakeStructNode->StructType->GetPathName();
		}
	}
	// Handle BreakStruct nodes
	else if (const UK2Node_BreakStruct* BreakStructNode = Cast<UK2Node_BreakStruct>(OwningNode))
	{
		if (BreakStructNode->StructType)
		{
			return BreakStructNode->StructType->GetPathName();
		}
	}
	// Handle FunctionEntry nodes - get parameter types
	else if (const UK2Node_FunctionEntry* EntryNode = Cast<UK2Node_FunctionEntry>(OwningNode))
	{
		// Get the function graph
		if (UEdGraph* Graph = EntryNode->GetGraph())
		{
			// Try to find the UFunction for this graph
			if (UBlueprint* Blueprint = Cast<UBlueprint>(Graph->GetOuter()))
			{
				if (Blueprint->GeneratedClass)
				{
					UFunction* Func = Blueprint->GeneratedClass->FindFunctionByName(Graph->GetFName());
					if (Func)
					{
						FName PinName = Pin->PinName;
						for (TFieldIterator<FProperty> PropIt(Func); PropIt; ++PropIt)
						{
							FProperty* Prop = *PropIt;
							if (Prop->GetFName() == PinName)
							{
								return GetTypePathFromProperty(Prop);
							}
						}
					}
				}
			}
		}
	}
	// Handle FunctionResult nodes - get return types
	else if (const UK2Node_FunctionResult* ResultNode = Cast<UK2Node_FunctionResult>(OwningNode))
	{
		if (UEdGraph* Graph = ResultNode->GetGraph())
		{
			if (UBlueprint* Blueprint = Cast<UBlueprint>(Graph->GetOuter()))
			{
				if (Blueprint->GeneratedClass)
				{
					UFunction* Func = Blueprint->GeneratedClass->FindFunctionByName(Graph->GetFName());
					if (Func)
					{
						FName PinName = Pin->PinName;
						// Check return value
						if (PinName == UEdGraphSchema_K2::PN_ReturnValue)
						{
							if (FProperty* ReturnProp = Func->GetReturnProperty())
							{
								return GetTypePathFromProperty(ReturnProp);
							}
						}
						// Check output parameters
						for (TFieldIterator<FProperty> PropIt(Func); PropIt; ++PropIt)
						{
							FProperty* Prop = *PropIt;
							if (Prop->GetFName() == PinName && Prop->HasAnyPropertyFlags(CPF_OutParm))
							{
								return GetTypePathFromProperty(Prop);
							}
						}
					}
				}
			}
		}
	}
	// Handle SpawnActorFromClass nodes
	else if (const UK2Node_SpawnActorFromClass* SpawnNode = Cast<UK2Node_SpawnActorFromClass>(OwningNode))
	{
		// The return value pin is the spawned actor type
		if (Pin->PinName == UEdGraphSchema_K2::PN_ReturnValue)
		{
			UClass* ClassToSpawn = SpawnNode->GetClassToSpawn();
			if (ClassToSpawn)
			{
				return ClassToSpawn->GetPathName();
			}
		}
	}
	// Handle Self reference nodes
	else if (const UK2Node_Self* SelfNode = Cast<UK2Node_Self>(OwningNode))
	{
		if (UEdGraph* Graph = SelfNode->GetGraph())
		{
			if (UBlueprint* Blueprint = Cast<UBlueprint>(Graph->GetOuter()))
			{
				if (Blueprint->GeneratedClass)
				{
					return Blueprint->GeneratedClass->GetPathName();
				}
			}
		}
	}

	return FString();
}

FBlueprintSerializer::FBlueprintSerializer()
{
}

FBlueprintSerializer::~FBlueprintSerializer()
{
}

bool FBlueprintSerializer::SerializeBlueprint(const UBlueprint* Blueprint, FExportedBlueprint& OutExported, FString& OutError)
{
	if (!Blueprint)
	{
		OutError = TEXT("Blueprint is null");
		return false;
	}

	UE_LOG(LogBlueprintExporter, Log, TEXT("[BlueprintExporter] Starting export of Blueprint: %s (status=%d)"),
		*Blueprint->GetName(), (int32)Blueprint->Status);

	// Check if Blueprint is in a valid state for export
	// Blueprints with certain error states can crash when accessing their data
	if (Blueprint->Status == BS_Error)
	{
		UE_LOG(LogBlueprintExporter, Warning, TEXT("[BlueprintExporter] Blueprint has compile errors - aborting export"));
		OutError = FString::Printf(TEXT("Blueprint '%s' has compile errors. Please fix errors before exporting."), *Blueprint->GetName());
		return false;
	}

	// Check if Blueprint needs recompiling - stale Blueprints can crash
	if (Blueprint->Status == BS_Dirty || Blueprint->Status == BS_Unknown)
	{
		OutError = FString::Printf(TEXT("Blueprint '%s' needs to be recompiled. Please compile the Blueprint before exporting."), *Blueprint->GetName());
		return false;
	}

	// Check if the generated class is valid - THIS CAN CRASH if the class has broken references
	if (!Blueprint->GeneratedClass)
	{
		OutError = FString::Printf(TEXT("Blueprint '%s' has no generated class. Please compile the Blueprint before exporting."), *Blueprint->GetName());
		return false;
	}

	// Reset state
	NodeGuidToStableId.Empty();
	PinToStableId.Empty();

	// Export info
	OutExported.ExportInfo.SchemaVersion = BLUEPRINT_EXPORT_SCHEMA_VERSION;
	OutExported.ExportInfo.EngineVersion = FEngineVersion::Current().ToString();
	OutExported.ExportInfo.PluginVersion = TEXT("1.28.6");
	OutExported.ExportInfo.ExportTimestamp = FDateTime::UtcNow().ToIso8601();

	// Basic info
	OutExported.AssetPath = Blueprint->GetPathName();
	OutExported.AssetName = Blueprint->GetName();
	OutExported.BlueprintGuid = Blueprint->GetBlueprintGuid().ToString();
	OutExported.BlueprintType = ConvertBlueprintType(Blueprint);
	OutExported.BlueprintSubclass = DetectBlueprintSubclass(Blueprint);

	OutExported.ParentClass = SerializeParentClass(Blueprint);
	OutExported.ImplementedInterfaces = SerializeImplementedInterfaces(Blueprint);
	OutExported.Variables = SerializeVariables(Blueprint);
	OutExported.Functions = SerializeFunctions(Blueprint);
	OutExported.Macros = SerializeMacros(Blueprint);

	UE_LOG(LogBlueprintExporter, Verbose, TEXT("[BlueprintExporter] Building node ID mappings (UbergraphPages: %d, FunctionGraphs: %d, MacroGraphs: %d)"),
		Blueprint->UbergraphPages.Num(), Blueprint->FunctionGraphs.Num(), Blueprint->MacroGraphs.Num());

	// Sort nodes deterministically before ID assignment to ensure stable IDs across sessions
	auto SortNodes = [](TArray<UEdGraphNode*> Nodes) -> TArray<UEdGraphNode*> {
		Nodes.Sort([](const UEdGraphNode& A, const UEdGraphNode& B) {
			if (A.NodePosX != B.NodePosX) return A.NodePosX < B.NodePosX;
			if (A.NodePosY != B.NodePosY) return A.NodePosY < B.NodePosY;
			// Tiebreaker for identical-position nodes uses the stable content
			// hash rather than `A.NodeGuid` — the latter drifts for
			// UE-regenerated nodes and would flip sort order between loads.
			return ComputeStableNodeHash(&A) < ComputeStableNodeHash(&B);
		});
		return Nodes;
	};

	// Graphs - First pass: build node ID mappings (sorted for determinism)
	for (UEdGraph* Graph : Blueprint->UbergraphPages)
	{
		if (Graph)
		{
			for (UEdGraphNode* Node : SortNodes(Graph->Nodes))
			{
				if (Node)
				{
					FString StableId = GenerateStableNodeId(Node);
					NodeGuidToStableId.Add(Node->NodeGuid, StableId);
					for (UEdGraphPin* Pin : Node->Pins)
					{
						if (Pin)
						{
							FString PinStableId = GenerateStablePinId(Pin);
							PinToStableId.Add(Pin, PinStableId);
						}
					}
				}
			}
		}
	}

	for (UEdGraph* Graph : Blueprint->FunctionGraphs)
	{
		if (Graph)
		{
			for (UEdGraphNode* Node : SortNodes(Graph->Nodes))
			{
				if (Node)
				{
					FString StableId = GenerateStableNodeId(Node);
					NodeGuidToStableId.Add(Node->NodeGuid, StableId);
					for (UEdGraphPin* Pin : Node->Pins)
					{
						if (Pin)
						{
							FString PinStableId = GenerateStablePinId(Pin);
							PinToStableId.Add(Pin, PinStableId);
						}
					}
				}
			}
		}
	}

	for (UEdGraph* Graph : Blueprint->MacroGraphs)
	{
		if (Graph)
		{
			for (UEdGraphNode* Node : SortNodes(Graph->Nodes))
			{
				if (Node)
				{
					FString StableId = GenerateStableNodeId(Node);
					NodeGuidToStableId.Add(Node->NodeGuid, StableId);
					for (UEdGraphPin* Pin : Node->Pins)
					{
						if (Pin)
						{
							FString PinStableId = GenerateStablePinId(Pin);
							PinToStableId.Add(Pin, PinStableId);
						}
					}
				}
			}
		}
	}

	// Event graph (combines all ubergraph pages)
	if (Blueprint->UbergraphPages.Num() > 0)
	{
		OutExported.EventGraph.GraphName = TEXT("EventGraph");
		OutExported.EventGraph.GraphType = TEXT("EventGraph");

		for (UEdGraph* Graph : Blueprint->UbergraphPages)
		{
			if (Graph)
			{
				FExportedGraph SubGraph = SerializeGraph(Graph);
				OutExported.EventGraph.Nodes.Append(SubGraph.Nodes);
				if (OutExported.EventGraph.GraphGuid.IsEmpty())
				{
					OutExported.EventGraph.GraphGuid = SubGraph.GraphGuid;
					OutExported.EventGraph.SchemaClass = SubGraph.SchemaClass;
				}
			}
		}
	}

	// Construction script graph is located on FunctionGraphs (see loop below);
	// no further work needed here via SimpleConstructionScript.

	// For construction script graphs
	for (UEdGraph* Graph : Blueprint->FunctionGraphs)
	{
		if (Graph && Graph->GetFName() == UEdGraphSchema_K2::FN_UserConstructionScript)
		{
			OutExported.ConstructionScript = SerializeGraph(Graph);
			break;
		}
	}

	// Components (for Actor blueprints)
	OutExported.Components = SerializeComponents(Blueprint);

	// Class Default Object properties — authored Details-panel overrides on inherited
	// UPROPERTYs (GE modifiers / GA ability tags / DA payload / Actor bReplicates etc.)
	// that the graph-oriented walk above never touches.
	OutExported.CDOProperties = SerializeCDOProperties(Blueprint);
	OutExported.DataCarrierKind = DetectDataCarrierKind(Blueprint);

	// State machines (for AnimBP assets)
	OutExported.StateMachines = SerializeStateMachines(Blueprint);

	// Widget tree (for WidgetBP assets)
	OutExported.WidgetTree = SerializeWidgetTree(Blueprint);

	// Additional graphs
	for (UEdGraph* Graph : Blueprint->FunctionGraphs)
	{
		if (Graph && Graph->GetFName() != UEdGraphSchema_K2::FN_UserConstructionScript)
		{
			// These are already handled via Functions
		}
	}

	// Dependencies
	OutExported.Dependencies = SerializeDependencies(Blueprint);

	// Metadata
	// Add any Blueprint-level metadata here

	// Compute content hash
	OutExported.ExportInfo.ContentHash = OutExported.ComputeContentHash();

	UE_LOG(LogBlueprintExporter, Log, TEXT("[BlueprintExporter] Export completed successfully for: %s"), *Blueprint->GetName());
	UE_LOG(LogBlueprintExporter, Log, TEXT("[BlueprintExporter]   Nodes: %d, Variables: %d, Functions: %d"),
		OutExported.EventGraph.Nodes.Num(),
		OutExported.Variables.Num(),
		OutExported.Functions.Num());

	return true;
}

FExportedGraph FBlueprintSerializer::SerializeGraph(const UEdGraph* Graph)
{
	FExportedGraph ExportedGraph;

	if (!Graph)
	{
		return ExportedGraph;
	}

	ExportedGraph.GraphName = Graph->GetName();
	ExportedGraph.GraphGuid = Graph->GraphGuid.ToString();

	if (const UEdGraphSchema* Schema = Graph->GetSchema())
	{
		ExportedGraph.SchemaClass = Schema->GetClass()->GetPathName();
	}

	// Determine graph type
	if (Graph->GetFName() == UEdGraphSchema_K2::FN_UserConstructionScript)
	{
		ExportedGraph.GraphType = TEXT("ConstructionScript");
	}
	else if (Graph->GetSchema() && Graph->GetSchema()->GetClass()->IsChildOf(UEdGraphSchema_K2::StaticClass()))
	{
		ExportedGraph.GraphType = TEXT("K2Graph");
	}
	else
	{
		ExportedGraph.GraphType = TEXT("Unknown");
	}

	// Serialize nodes in deterministic order (sorted by position + GUID tiebreaker)
	TArray<UEdGraphNode*> SortedNodes = Graph->Nodes;
	SortedNodes.Sort([](const UEdGraphNode& A, const UEdGraphNode& B) {
		if (A.NodePosX != B.NodePosX) return A.NodePosX < B.NodePosX;
		if (A.NodePosY != B.NodePosY) return A.NodePosY < B.NodePosY;
		return A.NodeGuid < B.NodeGuid;
	});
	for (const UEdGraphNode* Node : SortedNodes)
	{
		if (Node)
		{
			ExportedGraph.Nodes.Add(SerializeNode(Node));
		}
	}

	return ExportedGraph;
}

FExportedNode FBlueprintSerializer::SerializeNode(const UEdGraphNode* Node)
{
	FExportedNode ExportedNode;

	if (!Node)
	{
		return ExportedNode;
	}

	// Log node info BEFORE doing anything else - use class name which is safe
	UE_LOG(LogBlueprintExporter, Verbose, TEXT("[BlueprintExporter] >>> Serializing node: Class=%s, Pos=(%d,%d), GUID=%s"),
		*Node->GetClass()->GetName(),
		Node->NodePosX,
		Node->NodePosY,
		*Node->NodeGuid.ToString());

	// Generate stable ID
	FString* FoundId = NodeGuidToStableId.Find(Node->NodeGuid);
	ExportedNode.NodeId = FoundId ? *FoundId : GenerateStableNodeId(Node);
	// `NodeGuid` in the exported schema is a deterministic content-hash, not
	// the raw UE-side `NodeGuid` (which drifts on auto-regenerated nodes).
	// Downstream consumers like `BlueprintTypeInference` key off this value
	// for pin-link resolution; a stable hash keeps their import/compare
	// paths working without breaking byte-for-byte determinism (brief §8).
	ExportedNode.NodeGuid = ComputeStableNodeHash(Node);
	ExportedNode.NodeClass = Node->GetClass()->GetPathName();

	// Safely get node title - some nodes with broken references can crash when getting title
	// Use a simpler title approach for potentially problematic node types
	if (const UK2Node_VariableGet* VarGetNode = Cast<UK2Node_VariableGet>(Node))
	{
		// Variable nodes can crash if the variable was deleted - use variable name directly
		ExportedNode.NodeTitle = FString::Printf(TEXT("Get %s"), *VarGetNode->GetVarName().ToString());
	}
	else if (const UK2Node_VariableSet* VarSetNode = Cast<UK2Node_VariableSet>(Node))
	{
		ExportedNode.NodeTitle = FString::Printf(TEXT("Set %s"), *VarSetNode->GetVarName().ToString());
	}
	else if (const UK2Node_CallFunction* CallNode = Cast<UK2Node_CallFunction>(Node))
	{
		// CallFunction nodes can crash if the function was deleted - use member name directly
		FName MemberName = CallNode->FunctionReference.GetMemberName();
		ExportedNode.NodeTitle = MemberName.IsNone() ? TEXT("Call Function") : MemberName.ToString();
	}
	else
	{
		ExportedNode.NodeTitle = Node->GetNodeTitle(ENodeTitleType::FullTitle).ToString();
	}

	// Determine node type for easier categorization
	if (Node->IsA<UK2Node_Event>())
	{
		ExportedNode.NodeType = TEXT("Event");
	}
	else if (Node->IsA<UK2Node_FunctionEntry>())
	{
		ExportedNode.NodeType = TEXT("FunctionEntry");
	}
	else if (Node->IsA<UK2Node_FunctionResult>())
	{
		ExportedNode.NodeType = TEXT("FunctionResult");
	}
	else if (Node->IsA<UK2Node_CallFunction>())
	{
		ExportedNode.NodeType = TEXT("CallFunction");
	}
	else if (Node->IsA<UK2Node_VariableGet>())
	{
		ExportedNode.NodeType = TEXT("VariableGet");
	}
	else if (Node->IsA<UK2Node_VariableSet>())
	{
		ExportedNode.NodeType = TEXT("VariableSet");
	}
	else if (Node->IsA<UK2Node_MacroInstance>())
	{
		ExportedNode.NodeType = TEXT("MacroInstance");
	}
	else if (Node->IsA<UK2Node_IfThenElse>())
	{
		ExportedNode.NodeType = TEXT("Branch");
	}
	else if (Node->IsA<UK2Node_DynamicCast>())
	{
		ExportedNode.NodeType = TEXT("Cast");
	}
	else if (Node->IsA<UK2Node>())
	{
		ExportedNode.NodeType = TEXT("K2Node");
	}
	else
	{
		ExportedNode.NodeType = TEXT("Generic");
	}

	// Position
	ExportedNode.PositionX = Node->NodePosX;
	ExportedNode.PositionY = Node->NodePosY;

	// Comments
	ExportedNode.Comment = Node->NodeComment;
	ExportedNode.bCommentBubbleVisible = Node->bCommentBubbleVisible;
	ExportedNode.bCommentBubblePinned = Node->bCommentBubblePinned;

	// Node color (if custom)
	if (Node->HasUserSetTheEnabledState())
	{
		// Store enabled state info if needed
	}

	// Serialize pins
	for (const UEdGraphPin* Pin : Node->Pins)
	{
		if (Pin)
		{
			ExportedNode.Pins.Add(SerializePin(Pin));
		}
	}

	// Get node-specific data
	if (const UK2Node* K2Node = Cast<UK2Node>(Node))
	{
		ExportedNode.NodeSpecificData = GetNodeSpecificData(K2Node);
	}

	return ExportedNode;
}

FExportedPin FBlueprintSerializer::SerializePin(const UEdGraphPin* Pin)
{
	FExportedPin ExportedPin;

	if (!Pin)
	{
		return ExportedPin;
	}

	// Log pin info BEFORE doing anything dangerous
	UE_LOG(LogBlueprintExporter, Verbose, TEXT("[BlueprintExporter]   >> Pin: %s (Dir: %s)"),
		*Pin->PinName.ToString(),
		Pin->Direction == EGPD_Input ? TEXT("In") : TEXT("Out"));

	// Check if the pin has a valid owning node - flag but don't skip
	const UEdGraphNode* OwningNode = Pin->GetOwningNode();
	if (!OwningNode || !IsValid(OwningNode))
	{
		// Still capture what we can, but flag the problem
		ExportedPin.PinName = Pin->PinName.ToString();
		ExportedPin.Direction = (Pin->Direction == EGPD_Input) ? EExportPinDirection::Input : EExportPinDirection::Output;
		ExportedPin.bHasError = true;
		ExportedPin.ErrorMessage = TEXT("Pin has orphaned or invalid owning node");
		UE_LOG(LogBlueprintExporter, Warning, TEXT("[BlueprintExporter] PIN ERROR - %s: %s"), *ExportedPin.PinName, *ExportedPin.ErrorMessage);
		return ExportedPin;
	}

	// Validate pin direction - flag but capture what we can
	if (Pin->Direction != EGPD_Input && Pin->Direction != EGPD_Output)
	{
		ExportedPin.PinName = Pin->PinName.ToString();
		ExportedPin.Direction = EExportPinDirection::Input;
		ExportedPin.bHasError = true;
		ExportedPin.ErrorMessage = TEXT("Pin has invalid direction value - possible memory corruption");
		UE_LOG(LogBlueprintExporter, Warning, TEXT("[BlueprintExporter] PIN ERROR - %s: %s"), *ExportedPin.PinName, *ExportedPin.ErrorMessage);
		return ExportedPin;
	}
	// (Per-pin info logging continues at Verbose throughout SerializePinTypeSafe)

	// Generate stable ID
	const FString* FoundId = PinToStableId.Find(Pin);
	ExportedPin.PinId = FoundId ? *FoundId : GenerateStablePinId(Pin);
	ExportedPin.PinName = Pin->PinName.ToString();
	ExportedPin.PinFriendlyName = Pin->PinFriendlyName.ToString();
	ExportedPin.Direction = (Pin->Direction == EGPD_Input) ? EExportPinDirection::Input : EExportPinDirection::Output;

	// Safely serialize pin type - captures errors instead of crashing
	ExportedPin.PinType = SerializePinTypeSafe(Pin);

	ExportedPin.DefaultValue = Pin->DefaultValue;
	ExportedPin.AutogeneratedDefaultValue = Pin->AutogeneratedDefaultValue;
	ExportedPin.bHidden = Pin->bHidden;
	ExportedPin.bNotConnectable = Pin->bNotConnectable;
	ExportedPin.bAdvancedView = Pin->bAdvancedView;

	// Serialize connections
	for (const UEdGraphPin* LinkedPin : Pin->LinkedTo)
	{
		if (LinkedPin && LinkedPin->GetOwningNode())
		{
			FExportedPinConnection Connection;

			// Find stable ID for connected node. Fallback calls
			// `GenerateStableNodeId` so the emitted ID matches the
			// `TypePrefix_X_Y_HASHPREFIX` format that pre-pass-mapped IDs use —
			// emitting just the raw hash (as M6.1's first cut did) meant DeepDump's
			// title-map lookups for cross-graph connection targets all missed and
			// rendered as `(?)`. The pre-pass only visits top-level graphs
			// (Ubergraph / FunctionGraphs / MacroGraphs), so pins linking into
			// nested BoundGraphs (K2Node_Composite, K2Node_MacroInstance) fall
			// through here for every nested-graph connection.
			const FString* ConnectedNodeId = NodeGuidToStableId.Find(LinkedPin->GetOwningNode()->NodeGuid);
			Connection.NodeId = ConnectedNodeId ? *ConnectedNodeId : GenerateStableNodeId(LinkedPin->GetOwningNode());

			// Find stable ID for connected pin
			const FString* ConnectedPinId = PinToStableId.Find(LinkedPin);
			Connection.PinId = ConnectedPinId ? *ConnectedPinId : LinkedPin->PinName.ToString();

			ExportedPin.Connections.Add(Connection);
		}
	}

	// Sort connections for determinism
	ExportedPin.Connections.Sort([](const FExportedPinConnection& A, const FExportedPinConnection& B) {
		if (A.NodeId != B.NodeId) return A.NodeId < B.NodeId;
		return A.PinId < B.PinId;
	});

	return ExportedPin;
}

FExportedPinType FBlueprintSerializer::SerializePinTypeSafe(const UEdGraphPin* Pin)
{
	FExportedPinType ExportedType;

	if (!Pin)
	{
		ExportedType.Category = TEXT("Unknown");
		ExportedType.bHasBrokenReference = true;
		ExportedType.BrokenReferenceInfo = TEXT("Pin is null");
		return ExportedType;
	}

	UE_LOG(LogBlueprintExporter, Verbose, TEXT("[BlueprintExporter]     Processing pin type for: %s"), *Pin->PinName.ToString());

	// Get pin type reference - accessing PinType struct should be safe
	// The dangerous part is accessing the weak object pointers inside it
	const FEdGraphPinType& PinType = Pin->PinType;

	// First check: if PinCategory is NAME_None, the pin type is likely corrupted
	if (PinType.PinCategory == NAME_None)
	{
		ExportedType.Category = TEXT("None");
		ExportedType.bHasBrokenReference = true;
		ExportedType.BrokenReferenceInfo = TEXT("Pin has no category (NAME_None) - likely corrupted");
		UE_LOG(LogBlueprintExporter, Warning, TEXT("[BlueprintExporter] PIN TYPE ERROR - %s: Category is NAME_None"), *Pin->PinName.ToString());
		return ExportedType;
	}

	// Category is an FName - safe to access
	ExportedType.Category = PinType.PinCategory.ToString();
	UE_LOG(LogBlueprintExporter, Verbose, TEXT("[BlueprintExporter]     Pin category: %s"), *ExportedType.Category);

	// Check if this is a simple type (no object references needed)
	// These types are safe and don't have weak object pointers that can crash
	static const FName SafeCategories[] = {
		TEXT("bool"),
		TEXT("byte"),
		TEXT("int"),
		TEXT("int64"),
		TEXT("float"),
		TEXT("double"),
		TEXT("real"),
		TEXT("name"),
		TEXT("string"),
		TEXT("text"),
		TEXT("exec"),
		TEXT("wildcard")
	};

	bool bIsSafeCategory = false;
	for (const FName& SafeCat : SafeCategories)
	{
		if (PinType.PinCategory == SafeCat)
		{
			bIsSafeCategory = true;
			break;
		}
	}

	// For safe categories, we don't need to access PinSubCategoryObject
	if (bIsSafeCategory)
	{
		ExportedType.PinSubCategory = PinType.PinSubCategory.ToString();
		ExportedType.bIsArray = PinType.IsArray();
		ExportedType.bIsSet = PinType.IsSet();
		ExportedType.bIsMap = PinType.IsMap();
		ExportedType.bIsReference = PinType.bIsReference;
		ExportedType.bIsConst = PinType.bIsConst;
		ExportedType.bIsWeakPointer = PinType.bIsWeakPointer;
		return ExportedType;
	}

	// For object/struct/class/interface types, we need to be very careful
	// The PinSubCategoryObject weak pointer can crash if the referenced object was deleted
	ExportedType.PinSubCategory = PinType.PinSubCategory.ToString();

	// CRITICAL: Do NOT call ANY methods on PinSubCategoryObject (IsExplicitlyNull, IsValid, IsStale, Get)
	// as they can ALL trigger assertions on corrupted weak pointers.
	// The weak pointer's internal index can be corrupted, causing ANY access to crash.

	// Instead, try to resolve the type from the owning node context using reflection
	// This is safer because it uses compiled FProperty data instead of weak pointers
	FString TypePath = GetTypePathFromPinContext(Pin);
	if (!TypePath.IsEmpty())
	{
		ExportedType.SubCategoryObject = TypePath;
		// bSubCategoryObjectResolved stays at its default (true).
		UE_LOG(LogBlueprintExporter, Verbose, TEXT("[BlueprintExporter]     Resolved type from node context: %s"), *TypePath);
	}
	else
	{
		ExportedType.SubCategoryObject = TEXT(""); // Could not resolve safely
		// Mark the blank as "unresolved" rather than "no subtype" so AI consumers
		// know a type existed but couldn't be recovered. Without this, readers
		// can't distinguish a primitive pin (genuinely no subtype) from one whose
		// weak-object-pointer pin reference was unsafe to dereference.
		ExportedType.bSubCategoryObjectResolved = false;
		UE_LOG(LogBlueprintExporter, Verbose, TEXT("[BlueprintExporter]     Could not resolve type for '%s' (node context unavailable)"), *ExportedType.Category);
	}

	ExportedType.bIsArray = PinType.IsArray();
	ExportedType.bIsSet = PinType.IsSet();
	ExportedType.bIsMap = PinType.IsMap();
	ExportedType.bIsReference = PinType.bIsReference;
	ExportedType.bIsConst = PinType.bIsConst;
	ExportedType.bIsWeakPointer = PinType.bIsWeakPointer;

	// Handle map value type - try to resolve from node context as well
	if (PinType.IsMap() && PinType.PinValueType.TerminalCategory != NAME_None)
	{
		ExportedType.ValueTerminalType = PinType.PinValueType.TerminalCategory.ToString();
		// For map value types, we'd need more complex resolution - leave as category for now
		UE_LOG(LogBlueprintExporter, Verbose, TEXT("[BlueprintExporter]     Map value type: %s"), *ExportedType.ValueTerminalType);
	}

	return ExportedType;
}

FExportedPinType FBlueprintSerializer::SerializePinType(const FEdGraphPinType& PinType)
{
	FExportedPinType ExportedType;

	ExportedType.Category = PinType.PinCategory.ToString();

	// CRITICAL: Skip PinSubCategoryObject access entirely
	// TWeakObjectPtr methods (IsValid, IsExplicitlyNull, IsStale, Get) can ALL crash
	// on corrupted weak pointers with invalid internal indices
	ExportedType.SubCategoryObject = TEXT(""); // Unsafe to access
	// Explicit marker so AI consumers can distinguish "no subtype" from
	// "subtype was blanked because we had no pin context for safe reflection".
	// Use SerializePinTypeSafe when a UEdGraphPin is in hand to resolve the type.
	ExportedType.bSubCategoryObjectResolved = false;

	ExportedType.PinSubCategory = PinType.PinSubCategory.ToString();
	ExportedType.bIsArray = PinType.IsArray();
	ExportedType.bIsSet = PinType.IsSet();
	ExportedType.bIsMap = PinType.IsMap();
	ExportedType.bIsReference = PinType.bIsReference;
	ExportedType.bIsConst = PinType.bIsConst;
	ExportedType.bIsWeakPointer = PinType.bIsWeakPointer;

	// Handle map value type - skip TerminalSubCategoryObject access for same reason
	if (PinType.IsMap() && PinType.PinValueType.TerminalCategory != NAME_None)
	{
		ExportedType.ValueTerminalType = PinType.PinValueType.TerminalCategory.ToString();
		// Skip TerminalSubCategoryObject - same weak pointer crash risk
	}

	return ExportedType;
}

FString FBlueprintSerializer::GetNodeSpecificData(const UK2Node* Node)
{
	if (!Node)
	{
		return TEXT("");
	}

	TSharedPtr<FJsonObject> SpecificData = MakeShareable(new FJsonObject());

	// Handle CallDelegate nodes (checked before CallFunction so we can emit
	// delegate-specific metadata). K2Node_CallDelegate is a separate
	// UK2Node subclass and was previously unhandled — the deserializer
	// rebuilt it as a bare node with no DelegateReference, so on compile
	// UE reported "Event Dispatcher has no property Call None". Emit the
	// authored delegate property name + its owning class so the
	// deserializer can restore DelegateReference via SetFromField.
	if (const UK2Node_CallDelegate* DelegateNode = Cast<UK2Node_CallDelegate>(Node))
	{
		const FName DelegateName = DelegateNode->DelegateReference.GetMemberName();
		SpecificData->SetStringField(TEXT("delegatePropertyName"), DelegateName.ToString());

		// Resolve delegate owner class, preferring the "Self" marker when the
		// delegate is owned by the BP we're serializing. Writing out the
		// SKEL_ class path via GetOwnerClass() directly is not reliably
		// reloadable via LoadObject on the import side — skeleton classes
		// are generated on BP compile, not package-loadable. FMemberReference::
		// IsSelfContext() returns false for delegates declared in a BP
		// because MemberParent is set to the generated class, so we have to
		// detect self-ownership by comparing against the owning BP's
		// {Skeleton,}GeneratedClass directly.
		if (const FMulticastDelegateProperty* DelegateProp = CastField<FMulticastDelegateProperty>(DelegateNode->GetProperty()))
		{
			const UClass* OwnerClass = DelegateProp->GetOwnerClass();

			UBlueprint* OwningBP = nullptr;
			if (Node->GetGraph())
			{
				OwningBP = Node->GetGraph()->GetTypedOuter<UBlueprint>();
			}

			const bool bSelf = OwningBP && OwnerClass && (
				OwnerClass == OwningBP->SkeletonGeneratedClass ||
				OwnerClass == OwningBP->GeneratedClass);

			if (bSelf)
			{
				SpecificData->SetStringField(TEXT("delegateOwnerClass"), TEXT("Self"));
			}
			else if (OwnerClass)
			{
				SpecificData->SetStringField(TEXT("delegateOwnerClass"), OwnerClass->GetPathName());
			}
		}
		else if (DelegateNode->DelegateReference.IsSelfContext())
		{
			SpecificData->SetStringField(TEXT("delegateOwnerClass"), TEXT("Self"));
		}
	}
	// Handle CallFunction nodes
	else if (const UK2Node_CallFunction* CallFunctionNode = Cast<UK2Node_CallFunction>(Node))
	{
		// Safely get target function - may crash on broken references
		FName MemberName = CallFunctionNode->FunctionReference.GetMemberName();
		SpecificData->SetStringField(TEXT("memberName"), MemberName.ToString());

		// Only try to resolve the function if the reference appears valid
		if (!MemberName.IsNone())
		{
			if (UFunction* Function = CallFunctionNode->GetTargetFunction())
			{
				SpecificData->SetStringField(TEXT("targetFunction"), Function->GetPathName());
				SpecificData->SetStringField(TEXT("functionName"), Function->GetName());

				if (UClass* OwnerClass = Function->GetOwnerClass())
				{
					SpecificData->SetStringField(TEXT("functionOwnerClass"), OwnerClass->GetPathName());
				}
			}

			// Use IsMemberParentClassValid to safely check before accessing
			if (CallFunctionNode->FunctionReference.IsSelfContext())
			{
				SpecificData->SetStringField(TEXT("memberParentClass"), TEXT("Self"));
			}
		}
	}
	// Handle Variable nodes
	else if (const UK2Node_VariableGet* VarGetNode = Cast<UK2Node_VariableGet>(Node))
	{
		SpecificData->SetStringField(TEXT("variableName"), VarGetNode->GetVarName().ToString());
		SpecificData->SetBoolField(TEXT("isPure"), VarGetNode->IsNodePure());

		// Safely check variable reference
		if (VarGetNode->VariableReference.IsSelfContext())
		{
			SpecificData->SetStringField(TEXT("variableSourceClass"), TEXT("Self"));
		}
	}
	else if (const UK2Node_VariableSet* VarSetNode = Cast<UK2Node_VariableSet>(Node))
	{
		SpecificData->SetStringField(TEXT("variableName"), VarSetNode->GetVarName().ToString());

		// Safely check variable reference
		if (VarSetNode->VariableReference.IsSelfContext())
		{
			SpecificData->SetStringField(TEXT("variableSourceClass"), TEXT("Self"));
		}
	}
	// Handle Event nodes
	else if (const UK2Node_Event* EventNode = Cast<UK2Node_Event>(Node))
	{
		SpecificData->SetStringField(TEXT("eventName"), EventNode->GetFunctionName().ToString());
		SpecificData->SetStringField(TEXT("customFunctionName"), EventNode->CustomFunctionName.ToString());
		SpecificData->SetBoolField(TEXT("isOverrideEvent"), EventNode->bOverrideFunction);
	}
	// Handle Macro nodes
	else if (const UK2Node_MacroInstance* MacroNode = Cast<UK2Node_MacroInstance>(Node))
	{
		if (UEdGraph* MacroGraph = MacroNode->GetMacroGraph())
		{
			SpecificData->SetStringField(TEXT("macroGraphName"), MacroGraph->GetName());

			if (UBlueprint* MacroBP = FBlueprintEditorUtils::FindBlueprintForGraph(MacroGraph))
			{
				SpecificData->SetStringField(TEXT("macroBlueprintPath"), MacroBP->GetPathName());
			}
		}
	}
	// Handle Dynamic Cast nodes
	else if (const UK2Node_DynamicCast* CastNode = Cast<UK2Node_DynamicCast>(Node))
	{
		if (UClass* TargetClass = CastNode->TargetType)
		{
			SpecificData->SetStringField(TEXT("targetType"), TargetClass->GetPathName());
		}
		SpecificData->SetBoolField(TEXT("isPureCast"), CastNode->IsNodePure());
	}
	// Handle SpawnActor nodes
	else if (const UK2Node_SpawnActorFromClass* SpawnNode = Cast<UK2Node_SpawnActorFromClass>(Node))
	{
		// Class is determined by pin connection, not stored directly
	}
	// Handle MakeArray nodes
	else if (const UK2Node_MakeArray* MakeArrayNode = Cast<UK2Node_MakeArray>(Node))
	{
		SpecificData->SetNumberField(TEXT("numInputs"), MakeArrayNode->NumInputs);
	}
	// Handle MakeStruct nodes
	else if (const UK2Node_MakeStruct* MakeStructNode = Cast<UK2Node_MakeStruct>(Node))
	{
		if (UScriptStruct* Struct = MakeStructNode->StructType)
		{
			SpecificData->SetStringField(TEXT("structType"), Struct->GetPathName());
		}
	}
	// Handle BreakStruct nodes
	else if (const UK2Node_BreakStruct* BreakStructNode = Cast<UK2Node_BreakStruct>(Node))
	{
		if (UScriptStruct* Struct = BreakStructNode->StructType)
		{
			SpecificData->SetStringField(TEXT("structType"), Struct->GetPathName());
		}
	}
	// Handle Switch nodes
	else if (const UK2Node_SwitchEnum* SwitchEnumNode = Cast<UK2Node_SwitchEnum>(Node))
	{
		if (UEnum* Enum = SwitchEnumNode->Enum)
		{
			SpecificData->SetStringField(TEXT("enumType"), Enum->GetPathName());
		}
	}
	else if (const UK2Node_SwitchString* SwitchStringNode = Cast<UK2Node_SwitchString>(Node))
	{
		TArray<TSharedPtr<FJsonValue>> CasesArray;
		for (const FName& PinName : SwitchStringNode->PinNames)
		{
			CasesArray.Add(MakeShareable(new FJsonValueString(PinName.ToString())));
		}
		SpecificData->SetArrayField(TEXT("cases"), CasesArray);
	}
	else if (const UK2Node_SwitchInteger* SwitchIntNode = Cast<UK2Node_SwitchInteger>(Node))
	{
		SpecificData->SetNumberField(TEXT("startIndex"), SwitchIntNode->StartIndex);
	}

	// Only return non-empty data
	if (SpecificData->Values.Num() == 0)
	{
		return TEXT("");
	}

	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(SpecificData.ToSharedRef(), Writer);
	return OutputString;
}

FExportedPinType FBlueprintSerializer::SerializePinTypeSafeFromType(const FEdGraphPinType& PinType)
{
	FExportedPinType ExportedType;

	// Category is an FName - safe to access
	ExportedType.Category = PinType.PinCategory.ToString();
	UE_LOG(LogBlueprintExporter, Verbose, TEXT("[BlueprintExporter]     SerializePinTypeSafeFromType: Category=%s"), *ExportedType.Category);

	// Check if this is a simple type (no object references needed)
	static const FName SafeCategories[] = {
		TEXT("bool"),
		TEXT("byte"),
		TEXT("int"),
		TEXT("int64"),
		TEXT("float"),
		TEXT("double"),
		TEXT("real"),
		TEXT("name"),
		TEXT("string"),
		TEXT("text"),
		TEXT("exec"),
		TEXT("wildcard")
	};

	bool bIsSafeCategory = false;
	for (const FName& SafeCat : SafeCategories)
	{
		if (PinType.PinCategory == SafeCat)
		{
			bIsSafeCategory = true;
			break;
		}
	}

	// For safe categories, we don't need to access PinSubCategoryObject
	if (bIsSafeCategory)
	{
		ExportedType.PinSubCategory = PinType.PinSubCategory.ToString();
		ExportedType.bIsArray = PinType.IsArray();
		ExportedType.bIsSet = PinType.IsSet();
		ExportedType.bIsMap = PinType.IsMap();
		ExportedType.bIsReference = PinType.bIsReference;
		ExportedType.bIsConst = PinType.bIsConst;
		ExportedType.bIsWeakPointer = PinType.bIsWeakPointer;
		return ExportedType;
	}

	ExportedType.PinSubCategory = PinType.PinSubCategory.ToString();
	UE_LOG(LogBlueprintExporter, Verbose, TEXT("[BlueprintExporter]     PinSubCategory: %s"), *ExportedType.PinSubCategory);

	// CRITICAL: Do NOT call ANY methods on PinSubCategoryObject (IsExplicitlyNull, IsValid, IsStale, Get)
	// as they can ALL trigger assertions on corrupted weak pointers.
	// For struct/object/class/interface/softobject/softclass types, the SubCategoryObject is left empty
	// here -- the caller (SerializeVariables, etc.) is responsible for resolving the type via FProperty
	// reflection on the GeneratedClass instead. Mark it as not-yet-resolved so downstream readers
	// don't confuse "no subtype" with "subtype not safely recoverable from the pin alone". The
	// caller flips this back to true once it fills SubCategoryObject via FProperty reflection.
	ExportedType.bSubCategoryObjectResolved = false;

	ExportedType.bIsArray = PinType.IsArray();
	ExportedType.bIsSet = PinType.IsSet();
	ExportedType.bIsMap = PinType.IsMap();
	ExportedType.bIsReference = PinType.bIsReference;
	ExportedType.bIsConst = PinType.bIsConst;
	ExportedType.bIsWeakPointer = PinType.bIsWeakPointer;

	// Handle map value type - also skip weak pointer access for safety
	if (PinType.IsMap() && PinType.PinValueType.TerminalCategory != NAME_None)
	{
		ExportedType.ValueTerminalType = PinType.PinValueType.TerminalCategory.ToString();
		// CRITICAL: Skip TerminalSubCategoryObject access - same weak pointer crash risk
		UE_LOG(LogBlueprintExporter, Verbose, TEXT("[BlueprintExporter]     Map value type: %s (SubCategoryObject skipped)"), *ExportedType.ValueTerminalType);
	}

	return ExportedType;
}

TArray<FExportedVariable> FBlueprintSerializer::SerializeVariables(const UBlueprint* Blueprint)
{
	TArray<FExportedVariable> Variables;

	if (!Blueprint)
	{
		return Variables;
	}

	for (const FBPVariableDescription& VarDesc : Blueprint->NewVariables)
	{
		UE_LOG(LogBlueprintExporter, Verbose, TEXT("[BlueprintExporter]   Variable: %s"), *VarDesc.VarName.ToString());

		FExportedVariable ExportedVar;
		ExportedVar.VariableName = VarDesc.VarName.ToString();
		ExportedVar.VariableGuid = VarDesc.VarGuid.ToString();
		// Use safe version to prevent crashes from orphaned object references
		ExportedVar.VariableType = SerializePinTypeSafeFromType(VarDesc.VarType);

		// Try to get the actual type path from the GeneratedClass property (safer than weak pointer)
		if (Blueprint->GeneratedClass)
		{
			if (FProperty* Prop = Blueprint->GeneratedClass->FindPropertyByName(VarDesc.VarName))
			{
				FString TypePath = GetTypePathFromProperty(Prop);
				if (!TypePath.IsEmpty())
				{
					ExportedVar.VariableType.SubCategoryObject = TypePath;
					ExportedVar.VariableType.bSubCategoryObjectResolved = true;
					UE_LOG(LogBlueprintExporter, Verbose, TEXT("[BlueprintExporter]     Found type from property: %s"), *TypePath);
				}
				// Also try to get map value type
				if (ExportedVar.VariableType.bIsMap)
				{
					FString ValueTypePath = GetMapValueTypePathFromProperty(Prop);
					if (!ValueTypePath.IsEmpty())
					{
						ExportedVar.VariableType.ValueTerminalType = ExportedVar.VariableType.ValueTerminalType + TEXT(":") + ValueTypePath;
					}
				}
			}
		}

		// Try to get default value from the CDO (Class Default Object) first
		// VarDesc.DefaultValue is often empty - actual values are stored in the CDO
		bool bGotDefaultFromCDO = false;
		if (Blueprint->GeneratedClass)
		{
			if (UObject* CDO = Blueprint->GeneratedClass->GetDefaultObject(false))
			{
				if (FProperty* Prop = Blueprint->GeneratedClass->FindPropertyByName(VarDesc.VarName))
				{
					const void* ValuePtr = Prop->ContainerPtrToValuePtr<void>(CDO);
					if (ValuePtr)
					{
						FString ValueStr;
						Prop->ExportTextItem_Direct(ValueStr, ValuePtr, nullptr, CDO, PPF_None);
						ExportedVar.DefaultValue = ValueStr;
						bGotDefaultFromCDO = true;
					}
				}
			}
		}
		// Fall back to VarDesc.DefaultValue if CDO extraction failed
		if (!bGotDefaultFromCDO)
		{
			ExportedVar.DefaultValue = VarDesc.DefaultValue;
		}

		ExportedVar.Category = VarDesc.Category.ToString();

		// Flags - these are simple property flag checks, safe to access
		ExportedVar.Flags.bInstanceEditable = (VarDesc.PropertyFlags & CPF_Edit) != 0;
		ExportedVar.Flags.bBlueprintReadOnly = (VarDesc.PropertyFlags & CPF_BlueprintReadOnly) != 0;
		ExportedVar.Flags.bExposeOnSpawn = (VarDesc.PropertyFlags & CPF_ExposeOnSpawn) != 0;
		ExportedVar.Flags.bPrivate = (VarDesc.PropertyFlags & CPF_DisableEditOnInstance) != 0;
		ExportedVar.Flags.bExposeToCinematics = (VarDesc.PropertyFlags & CPF_Interp) != 0;
		ExportedVar.Flags.bReplicated = VarDesc.RepNotifyFunc != NAME_None || (VarDesc.PropertyFlags & CPF_Net) != 0;

		if (VarDesc.ReplicationCondition != COND_None)
		{
			ExportedVar.Flags.ReplicationCondition = StaticEnum<ELifetimeCondition>()->GetNameStringByValue((int64)VarDesc.ReplicationCondition);
		}

		// RepNotify — load-bearing for the REPLICATION_MATRIX downstream document.
		// Emit both the flag and the function name. An empty string (not "None") is
		// written when the variable is not RepNotify, so downstream consumers can
		// treat "empty" as the canonical "no callback" signal.
		ExportedVar.Flags.bRepNotify = (VarDesc.PropertyFlags & CPF_RepNotify) != 0;
		if (ExportedVar.Flags.bRepNotify && VarDesc.RepNotifyFunc != NAME_None)
		{
			ExportedVar.Flags.RepNotifyFunc = VarDesc.RepNotifyFunc.ToString();
		}

		// Metadata - iterate directly over MetaDataArray instead of using GetMetaData
		// GetMetaData() can trigger EntryIndex != INDEX_NONE assertion on corrupted variables
		for (const auto& MetaPair : VarDesc.MetaDataArray)
		{
			FString Key = MetaPair.DataKey.ToString();
			ExportedVar.MetaData.Add(Key, MetaPair.DataValue);
			// Extract ToolTip from metadata array directly
			if (Key == TEXT("ToolTip"))
			{
				ExportedVar.ToolTip = MetaPair.DataValue;
			}
		}

		Variables.Add(ExportedVar);
	}

	return Variables;
}

TArray<FExportedFunction> FBlueprintSerializer::SerializeFunctions(const UBlueprint* Blueprint)
{
	TArray<FExportedFunction> Functions;

	if (!Blueprint)
	{
		return Functions;
	}

	// Build the full set of function graphs to serialize. UE stores them in
	// two disjoint places:
	//   - `Blueprint->FunctionGraphs` — regular member functions and the
	//     user-construction-script graph.
	//   - `Blueprint->ImplementedInterfaces[i].Graphs` — override graphs for
	//     each implemented interface. The editor creates a stub here the
	//     moment you click "add function" on an interface in the UI, and
	//     `implement_interface_function`'s idempotency check detects those
	//     stubs. Pre-M26.1.1 the serializer only walked FunctionGraphs, so
	//     stubs were invisible in the inventory — users saw "no such
	//     function" but the op saw the graph and refused to touch it.
	// We collect both into a single iteration with an owning-interface class
	// path (empty for regular functions) so the export can flag overrides
	// without a second pass.
	struct FGraphWithOwner
	{
		UEdGraph* Graph = nullptr;
		FString InterfaceClassPath; // empty -> regular member function
	};
	TArray<FGraphWithOwner> ToSerialize;
	for (UEdGraph* Graph : Blueprint->FunctionGraphs)
	{
		ToSerialize.Add({Graph, FString()});
	}
	for (const FBPInterfaceDescription& IfaceDesc : Blueprint->ImplementedInterfaces)
	{
		const FString IfacePath = IfaceDesc.Interface ? IfaceDesc.Interface->GetPathName() : FString();
		for (UEdGraph* Graph : IfaceDesc.Graphs)
		{
			ToSerialize.Add({Graph, IfacePath});
		}
	}

	for (const FGraphWithOwner& Entry : ToSerialize)
	{
		UEdGraph* Graph = Entry.Graph;
		if (!Graph || Graph->GetFName() == UEdGraphSchema_K2::FN_UserConstructionScript)
		{
			continue;
		}

		UE_LOG(LogBlueprintExporter, Verbose, TEXT("[BlueprintExporter]   Function: %s (%d nodes)"), *Graph->GetName(), Graph->Nodes.Num());

		FExportedFunction ExportedFunc;
		ExportedFunc.FunctionName = Graph->GetName();
		ExportedFunc.FunctionGuid = Graph->GraphGuid.ToString();
		ExportedFunc.bIsInterfaceOverride = !Entry.InterfaceClassPath.IsEmpty();
		ExportedFunc.InterfaceClassPath = Entry.InterfaceClassPath;

		// Get function entry node for signature info
		for (UEdGraphNode* Node : Graph->Nodes)
		{
			if (UK2Node_FunctionEntry* EntryNode = Cast<UK2Node_FunctionEntry>(Node))
			{
				// Extract flags from entry node
				ExportedFunc.Flags.bPure = false; // Functions with exec pins are not pure
				ExportedFunc.Flags.bCallInEditor = EntryNode->MetaData.bCallInEditor;

				const uint32 FuncFlags = static_cast<uint32>(EntryNode->GetFunctionFlags());

				// Check access specifier
				switch (FuncFlags & FUNC_AccessSpecifiers)
				{
				case FUNC_Public:
					ExportedFunc.Flags.AccessSpecifier = TEXT("Public");
					break;
				case FUNC_Protected:
					ExportedFunc.Flags.AccessSpecifier = TEXT("Protected");
					break;
				case FUNC_Private:
					ExportedFunc.Flags.AccessSpecifier = TEXT("Private");
					break;
				default:
					ExportedFunc.Flags.AccessSpecifier = TEXT("Public");
				}

				// Net-exec flags (M3.2): one RPC direction + reliability + authority/cosmetic gates.
				// Sourced from FunctionFlags which OR's the entry node's ExtraFlags with
				// GetSuperFunctionFlags(), so overridden engine-events keep their base RPC flags.
				ExportedFunc.Flags.bServer                 = (FuncFlags & FUNC_NetServer)              != 0;
				ExportedFunc.Flags.bClient                 = (FuncFlags & FUNC_NetClient)              != 0;
				ExportedFunc.Flags.bNetMulticast           = (FuncFlags & FUNC_NetMulticast)           != 0;
				ExportedFunc.Flags.bReliable               = (FuncFlags & FUNC_NetReliable)            != 0;
				ExportedFunc.Flags.bBlueprintAuthorityOnly = (FuncFlags & FUNC_BlueprintAuthorityOnly) != 0;
				ExportedFunc.Flags.bBlueprintCosmetic      = (FuncFlags & FUNC_BlueprintCosmetic)      != 0;

				ExportedFunc.Description = EntryNode->MetaData.ToolTip.ToString();
				ExportedFunc.Category = EntryNode->MetaData.Category.ToString();

				// Keywords
				FString KeywordsStr = EntryNode->MetaData.Keywords.ToString();
				if (!KeywordsStr.IsEmpty())
				{
					KeywordsStr.ParseIntoArray(ExportedFunc.Keywords, TEXT(" "));
				}

				break;
			}
		}

		// Get function signature from entry/result nodes
		SerializeFunctionSignature(Graph, ExportedFunc.Inputs, ExportedFunc.Outputs);

		// Local variables - stored in the function graph's local variables
		// In UE 5.x, local variables are accessed via the function entry node
		if (Graph)
		{
			TArray<UK2Node_FunctionEntry*> EntryNodes;
			Graph->GetNodesOfClass(EntryNodes);
			for (UK2Node_FunctionEntry* EntryNode : EntryNodes)
			{
				if (EntryNode)
				{
					for (const FBPVariableDescription& LocalVar : EntryNode->LocalVariables)
					{
						FExportedVariable ExportedLocalVar;
						ExportedLocalVar.VariableName = LocalVar.VarName.ToString();
						ExportedLocalVar.VariableGuid = LocalVar.VarGuid.ToString();
						// Use safe version to prevent crashes from orphaned object references
						ExportedLocalVar.VariableType = SerializePinTypeSafeFromType(LocalVar.VarType);
						ExportedLocalVar.DefaultValue = LocalVar.DefaultValue;
						ExportedFunc.LocalVariables.Add(ExportedLocalVar);
					}
				}
			}
		}

		// Serialize the function graph
		ExportedFunc.Graph = SerializeGraph(Graph);

		Functions.Add(ExportedFunc);
	}

	return Functions;
}

TArray<FExportedFunction> FBlueprintSerializer::SerializeMacros(const UBlueprint* Blueprint)
{
	TArray<FExportedFunction> Macros;

	if (!Blueprint)
	{
		return Macros;
	}

	for (UEdGraph* Graph : Blueprint->MacroGraphs)
	{
		if (!Graph)
		{
			continue;
		}

		FExportedFunction ExportedMacro;
		ExportedMacro.FunctionName = Graph->GetName();
		ExportedMacro.FunctionGuid = Graph->GraphGuid.ToString();

		// Macros don't have the same entry nodes, but have tunnel nodes
		for (UEdGraphNode* Node : Graph->Nodes)
		{
			if (UK2Node_Tunnel* TunnelNode = Cast<UK2Node_Tunnel>(Node))
			{
				// Process tunnel inputs/outputs
			}
		}

		ExportedMacro.Graph = SerializeGraph(Graph);
		Macros.Add(ExportedMacro);
	}

	return Macros;
}

TArray<FExportedComponent> FBlueprintSerializer::SerializeComponents(const UBlueprint* Blueprint)
{
	TArray<FExportedComponent> Components;

	if (!Blueprint || !Blueprint->SimpleConstructionScript)
	{
		return Components;
	}

	USimpleConstructionScript* SCS = Blueprint->SimpleConstructionScript;

	// GetDefaultSceneRootNode() returns a node that is already present in
	// GetRootNodes() when the Blueprint has a scene root, so we must NOT iterate
	// both — we'd emit the same component twice (visible as a duplicated
	// "DefaultSceneRoot (SceneComponent)" block in the .txt and inflated
	// componentCount in the coverage summary). Walk the root list once and flip
	// bIsRootComponent on whichever entry matches the default scene root.
	const USCS_Node* DefaultRootNode = SCS->GetDefaultSceneRootNode();
	const TArray<USCS_Node*>& RootNodes = SCS->GetRootNodes();
	for (USCS_Node* RootNode : RootNodes)
	{
		if (!RootNode)
		{
			continue;
		}
		FExportedComponent Exported = SerializeSCSNode(RootNode);
		if (RootNode == DefaultRootNode)
		{
			Exported.bIsRootComponent = true;
		}
		Components.Add(MoveTemp(Exported));
	}

	return Components;
}

namespace
{
	/** Deepest Instanced-subobject chain we're willing to walk. Guards against pathological
	 *  cycles that slip past the Visited set (e.g., two equal-but-distinct UObject instances
	 *  referring to each other) and keeps export output bounded. */
	constexpr int32 MAX_SUBOBJECT_RECURSION_DEPTH = 8;

	/** True if the property (or, for containers, its inner element property) is an
	 *  FObjectProperty carrying Instanced / EditInlineNew semantics. Covers the
	 *  "AIPerceptionComponent::SenseConfigs" shape (TArray<UAISenseConfig*> with Instanced),
	 *  as well as plain UPROPERTY(Instanced) UObject* members. Sets and maps are not
	 *  handled — Instanced is very rarely used with those containers in practice. */
	bool PropertyHoldsInstancedSubobject(const FProperty* Property)
	{
		if (!Property)
		{
			return false;
		}
		if (const FObjectProperty* ObjProp = CastField<FObjectProperty>(Property))
		{
			return ObjProp->HasAnyPropertyFlags(CPF_InstancedReference | CPF_PersistentInstance);
		}
		if (const FArrayProperty* ArrayProp = CastField<FArrayProperty>(Property))
		{
			return PropertyHoldsInstancedSubobject(ArrayProp->Inner);
		}
		return false;
	}

	// Some UPROPERTY values are regenerated on every asset load — e.g.
	// `AVolume::VolumeGuid` on `AAudioVolume` / `APostProcessVolume` subclasses
	// (UE stamps a fresh FGuid during PostLoad for runtime-unique network IDs).
	// If we emit the raw value we fail the byte-identical-across-runs contract
	// even though the authored asset didn't change. Substitute a placeholder
	// so the sidecar .meta.json stays stable while still signalling that a
	// transient value existed in that slot.
	//
	// Extend this set as new transient fields surface from real content.
	bool IsTransientValueProperty(const FProperty* Property)
	{
		if (!Property)
		{
			return false;
		}
		static const TSet<FName> TransientNames = {
			FName(TEXT("VolumeGuid")),
		};
		return TransientNames.Contains(Property->GetFName());
	}

	const TCHAR* TransientValuePlaceholder()
	{
		return TEXT("[transient]");
	}

	// Forward decls for mutual recursion between the subobject-JSON builder and the
	// property-array walker.
	TSharedPtr<FJsonObject> BuildInstancedSubobjectJson(const UObject* Subobject, TSet<const UObject*>& Visited, int32 Depth);
	TArray<TSharedPtr<FJsonValue>> BuildPropertiesJsonArrayForObject(const UObject* Container, TSet<const UObject*>& Visited, int32 Depth);

	/** Build the JSON array that populates `FExportedComponentProperty::SubobjectJsonValues`
	 *  for a single instanced property. One element for a direct object reference,
	 *  N elements for a TArray<UObject*>. Each element gets an optional `arrayIndex`
	 *  so downstream consumers can preserve ordering. */
	TArray<TSharedPtr<FJsonValue>> BuildInstancedSubobjectValuesForProperty(
		const FProperty* Property,
		const void* OwnerContainerPtr,
		TSet<const UObject*>& Visited,
		int32 Depth)
	{
		TArray<TSharedPtr<FJsonValue>> Out;
		if (!Property || !OwnerContainerPtr)
		{
			return Out;
		}

		if (const FObjectProperty* ObjProp = CastField<FObjectProperty>(Property))
		{
			const void* ValuePtr = ObjProp->ContainerPtrToValuePtr<void>(OwnerContainerPtr);
			const UObject* Sub = ObjProp->GetObjectPropertyValue(ValuePtr);
			if (TSharedPtr<FJsonObject> Obj = BuildInstancedSubobjectJson(Sub, Visited, Depth))
			{
				Out.Add(MakeShared<FJsonValueObject>(Obj));
			}
			return Out;
		}

		if (const FArrayProperty* ArrayProp = CastField<FArrayProperty>(Property))
		{
			const FObjectProperty* InnerObjProp = CastField<FObjectProperty>(ArrayProp->Inner);
			if (!InnerObjProp)
			{
				return Out;
			}
			FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(OwnerContainerPtr));
			for (int32 Index = 0; Index < Helper.Num(); ++Index)
			{
				const uint8* ElemPtr = Helper.GetRawPtr(Index);
				const UObject* Sub = InnerObjProp->GetObjectPropertyValue(ElemPtr);
				TSharedPtr<FJsonObject> Obj = BuildInstancedSubobjectJson(Sub, Visited, Depth);
				if (Obj.IsValid())
				{
					Obj->SetNumberField(TEXT("arrayIndex"), Index);
					Out.Add(MakeShared<FJsonValueObject>(Obj));
				}
			}
			return Out;
		}

		return Out;
	}

	TSharedPtr<FJsonObject> BuildInstancedSubobjectJson(
		const UObject* Subobject,
		TSet<const UObject*>& Visited,
		int32 Depth)
	{
		TSharedPtr<FJsonObject> Obj = MakeShareable(new FJsonObject());

		// "Never guess values" — preserve the fact that an instanced slot existed but
		// its reference was null, rather than silently dropping the entry.
		if (!Subobject)
		{
			Obj->SetBoolField(TEXT("bHasBrokenReference"), true);
			Obj->SetStringField(TEXT("brokenReferenceInfo"), TEXT("Instanced subobject reference was null at export time"));
			return Obj;
		}

		Obj->SetStringField(TEXT("classPath"), Subobject->GetClass()->GetPathName());
		Obj->SetStringField(TEXT("objectName"), Subobject->GetName());

		if (Depth >= MAX_SUBOBJECT_RECURSION_DEPTH)
		{
			Obj->SetBoolField(TEXT("bTruncated"), true);
			return Obj;
		}
		if (Visited.Contains(Subobject))
		{
			Obj->SetBoolField(TEXT("bCycleDetected"), true);
			return Obj;
		}
		Visited.Add(Subobject);

		const TArray<TSharedPtr<FJsonValue>> Properties = BuildPropertiesJsonArrayForObject(Subobject, Visited, Depth + 1);
		if (Properties.Num() > 0)
		{
			Obj->SetArrayField(TEXT("properties"), Properties);
		}
		return Obj;
	}

	TArray<TSharedPtr<FJsonValue>> BuildPropertiesJsonArrayForObject(
		const UObject* Container,
		TSet<const UObject*>& Visited,
		int32 Depth)
	{
		TArray<TSharedPtr<FJsonValue>> Out;
		if (!Container)
		{
			return Out;
		}

		UClass* Cls = Container->GetClass();
		UObject* CDO = Cls ? Cls->GetDefaultObject() : nullptr;

		for (TFieldIterator<FProperty> PropIt(Cls); PropIt; ++PropIt)
		{
			FProperty* Property = *PropIt;
			if (!Property || Property->HasAnyPropertyFlags(CPF_Transient | CPF_DuplicateTransient))
			{
				continue;
			}

			const void* CurrentValue = Property->ContainerPtrToValuePtr<void>(Container);
			const void* DefaultValue = CDO ? Property->ContainerPtrToValuePtr<void>(CDO) : nullptr;
			if (DefaultValue && Property->Identical(CurrentValue, DefaultValue))
			{
				continue;
			}

			TSharedPtr<FJsonObject> PropObj = MakeShareable(new FJsonObject());
			PropObj->SetStringField(TEXT("propertyName"), Property->GetName());
			PropObj->SetStringField(TEXT("propertyType"), Property->GetCPPType());

			FString FlatValue;
			if (IsTransientValueProperty(Property))
			{
				FlatValue = TransientValuePlaceholder();
			}
			else
			{
				Property->ExportTextItem_Direct(FlatValue, CurrentValue, DefaultValue, const_cast<UObject*>(Container), PPF_None);
			}
			PropObj->SetStringField(TEXT("value"), FlatValue);

			if (PropertyHoldsInstancedSubobject(Property))
			{
				PropObj->SetBoolField(TEXT("bIsInstancedSubobject"), true);
				TArray<TSharedPtr<FJsonValue>> Subs = BuildInstancedSubobjectValuesForProperty(
					Property, Container, Visited, Depth);
				if (Subs.Num() > 0)
				{
					PropObj->SetArrayField(TEXT("subobjects"), Subs);
				}
			}

			Out.Add(MakeShared<FJsonValueObject>(PropObj));
		}

		return Out;
	}
} // namespace

FExportedComponent FBlueprintSerializer::SerializeSCSNode(const USCS_Node* SCSNode)
{
	FExportedComponent ExportedComponent;

	if (!SCSNode)
	{
		return ExportedComponent;
	}

	ExportedComponent.ComponentName = SCSNode->GetVariableName().ToString();

	if (SCSNode->ComponentClass)
	{
		ExportedComponent.ComponentClass = SCSNode->ComponentClass->GetPathName();
	}
	else
	{
		ExportedComponent.ComponentClass = TEXT("Unknown");
		UE_LOG(LogBlueprintExporter, Warning, TEXT("[BlueprintExporter] SCS node '%s' has null ComponentClass - orphaned component reference"),
			*ExportedComponent.ComponentName);
	}

	if (SCSNode->ParentComponentOrVariableName != NAME_None)
	{
		ExportedComponent.ParentComponentName = SCSNode->ParentComponentOrVariableName.ToString();
	}

	ExportedComponent.AttachSocketName = SCSNode->AttachToName.ToString();

	// Get component template for property values -- guard against null
	UActorComponent* ComponentTemplate = SCSNode->ComponentTemplate;
	if (ComponentTemplate)
	{
		// Iterate through properties
		UObject* ComponentCDO = ComponentTemplate->GetClass() ? ComponentTemplate->GetClass()->GetDefaultObject() : nullptr;
		for (TFieldIterator<FProperty> PropIt(ComponentTemplate->GetClass()); PropIt; ++PropIt)
		{
			FProperty* Property = *PropIt;

			// Skip certain properties
			if (Property->HasAnyPropertyFlags(CPF_Transient | CPF_DuplicateTransient))
			{
				continue;
			}

			// Only export modified properties (non-default values). If the CDO is
			// unavailable we can't compare, so we treat the property as modified and
			// emit it — the "never guess values" principle prefers over-reporting to
			// silent omission.
			const void* DefaultValue = ComponentCDO ? Property->ContainerPtrToValuePtr<void>(ComponentCDO) : nullptr;
			const void* CurrentValue = Property->ContainerPtrToValuePtr<void>(ComponentTemplate);
			if (DefaultValue && Property->Identical(CurrentValue, DefaultValue))
			{
				continue;
			}

			FString ValueStr;
			if (IsTransientValueProperty(Property))
			{
				ValueStr = TransientValuePlaceholder();
			}
			else
			{
				Property->ExportTextItem_Direct(ValueStr, CurrentValue, DefaultValue, ComponentTemplate, PPF_None);
			}

			FExportedComponentProperty PropExport;
			PropExport.PropertyName = Property->GetName();
			PropExport.PropertyType = Property->GetCPPType();
			PropExport.Value = ValueStr;

			// Structured capture for Instanced / EditInlineNew subobject references
			// (e.g. UAIPerceptionComponent::SenseConfigs, GAS attribute sets, anim layers).
			// Without this, the flat `Value` above is the opaque ExportTextItem_Direct blob
			// that AI consumers cannot parse. We still emit the flat value for backwards
			// compatibility; the structured tree supplements it.
			if (PropertyHoldsInstancedSubobject(Property))
			{
				TSet<const UObject*> Visited;
				TArray<TSharedPtr<FJsonValue>> Subs = BuildInstancedSubobjectValuesForProperty(
					Property, ComponentTemplate, Visited, /*Depth=*/1);
				if (Subs.Num() > 0)
				{
					PropExport.bIsInstancedSubobject = true;
					PropExport.SubobjectJsonValues = MoveTemp(Subs);
				}
			}

			ExportedComponent.Properties.Add(PropExport);
		}
	}
	else
	{
		UE_LOG(LogBlueprintExporter, Warning, TEXT("[BlueprintExporter] SCS node '%s' has null ComponentTemplate - properties will be empty"),
			*ExportedComponent.ComponentName);
	}

	// Recursively serialize child nodes
	for (USCS_Node* ChildNode : SCSNode->ChildNodes)
	{
		if (ChildNode)
		{
			ExportedComponent.ChildComponents.Add(SerializeSCSNode(ChildNode));
		}
	}

	return ExportedComponent;
}

TArray<FExportedComponentProperty> FBlueprintSerializer::SerializeCDOProperties(const UBlueprint* Blueprint)
{
	TArray<FExportedComponentProperty> Out;

	if (!Blueprint || !Blueprint->GeneratedClass)
	{
		return Out;
	}

	UClass* GeneratedClass = Blueprint->GeneratedClass;
	UObject* CDO = GeneratedClass->GetDefaultObject();
	if (!CDO)
	{
		return Out;
	}

	UClass* ParentClass = GeneratedClass->GetSuperClass();
	UObject* ParentCDO = ParentClass ? ParentClass->GetDefaultObject() : nullptr;

	// Matches the M11–M16 Tier 2 renderers' + M16 StateTree serializer's plumbing
	// filter. Without it, BP-backed CDOs leak UE runtime back-references
	// (FPointerToUberGraphFrame, TObjectPtr<UStateTree>) as authored-looking props.
	static const TSet<FName> PlumbingNames = {
		FName(TEXT("UberGraphFrame")),
		FName(TEXT("CachedFrameStateTree")),
	};

	for (TFieldIterator<FProperty> PropIt(GeneratedClass); PropIt; ++PropIt)
	{
		FProperty* Property = *PropIt;
		if (!Property)
		{
			continue;
		}

		// Only walk INHERITED properties — BP-declared fields are already captured
		// by `SerializeVariables`. Inherited properties are those declared higher up
		// the parent chain; they're the only place where "authored override vs
		// parent default" makes sense.
		const UClass* OwnerClass = Property->GetOwnerClass();
		if (!OwnerClass || OwnerClass == GeneratedClass)
		{
			continue;
		}

		if (Property->HasAnyPropertyFlags(CPF_Transient | CPF_DuplicateTransient))
		{
			continue;
		}

		if (PlumbingNames.Contains(Property->GetFName()))
		{
			continue;
		}

		const void* CurrentValue = Property->ContainerPtrToValuePtr<void>(CDO);
		const void* DefaultValue = ParentCDO ? Property->ContainerPtrToValuePtr<void>(ParentCDO) : nullptr;

		// Inherited-only filter above guarantees the parent layout contains the slot;
		// no out-of-bounds risk. If the parent CDO is somehow null, emit the value
		// (over-report rather than guess equality).
		if (DefaultValue && Property->Identical(CurrentValue, DefaultValue))
		{
			continue;
		}

		FString ValueStr;
		if (IsTransientValueProperty(Property))
		{
			ValueStr = TransientValuePlaceholder();
		}
		else
		{
			Property->ExportTextItem_Direct(ValueStr, CurrentValue, DefaultValue, CDO, PPF_None);
		}

		FExportedComponentProperty PropExport;
		PropExport.PropertyName = Property->GetName();
		PropExport.PropertyType = Property->GetCPPType();
		PropExport.Value = ValueStr;

		// Reuse the M9 instanced-subobject walker — GE modifier lists
		// (TArray<FGameplayModifierInfo>) aren't Instanced, but AbilitySystemComponent
		// attribute sets, AIPerception SenseConfigs, and anim layer overrides are, and
		// a GE that inherits a base C++ class with Instanced components needs the
		// nested tree for any consumer to read actual values.
		if (PropertyHoldsInstancedSubobject(Property))
		{
			TSet<const UObject*> Visited;
			TArray<TSharedPtr<FJsonValue>> Subs = BuildInstancedSubobjectValuesForProperty(
				Property, CDO, Visited, /*Depth=*/1);
			if (Subs.Num() > 0)
			{
				PropExport.bIsInstancedSubobject = true;
				PropExport.SubobjectJsonValues = MoveTemp(Subs);
			}
		}

		Out.Add(MoveTemp(PropExport));
	}

	Out.Sort([](const FExportedComponentProperty& A, const FExportedComponentProperty& B) {
		return A.PropertyName < B.PropertyName;
	});

	return Out;
}

FString FBlueprintSerializer::DetectDataCarrierKind(const UBlueprint* Blueprint)
{
	if (!Blueprint || !Blueprint->GeneratedClass)
	{
		return FString();
	}

	UClass* GeneratedClass = Blueprint->GeneratedClass;

	// Resolve base classes lazily (same pattern as M7 ProjectPluginsCommandlet). Silent
	// skip when a module isn't loaded — data-carrier kind remains empty rather than
	// forcing a new Build.cs module dep.
	const UClass* GameplayEffectBase = FindObject<UClass>(nullptr, TEXT("/Script/GameplayAbilities.GameplayEffect"));
	const UClass* GameplayAbilityBase = FindObject<UClass>(nullptr, TEXT("/Script/GameplayAbilities.GameplayAbility"));
	const UClass* DataAssetBase = FindObject<UClass>(nullptr, TEXT("/Script/Engine.DataAsset"));

	if (GameplayEffectBase && GeneratedClass->IsChildOf(GameplayEffectBase))
	{
		return TEXT("GameplayEffect");
	}
	if (GameplayAbilityBase && GeneratedClass->IsChildOf(GameplayAbilityBase))
	{
		return TEXT("GameplayAbility");
	}
	if (DataAssetBase && GeneratedClass->IsChildOf(DataAssetBase))
	{
		return TEXT("DataAsset");
	}
	return FString();
}

TArray<FExportedDependency> FBlueprintSerializer::SerializeDependencies(const UBlueprint* Blueprint)
{
	TArray<FExportedDependency> Dependencies;

	if (!Blueprint)
	{
		return Dependencies;
	}

	TSet<FString> ProcessedPaths;

	// Get asset references via the asset registry
	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

	TArray<FAssetIdentifier> ReferencedAssets;
	FAssetIdentifier BlueprintIdentifier(Blueprint->GetOutermost()->GetFName());
	AssetRegistry.GetDependencies(BlueprintIdentifier, ReferencedAssets);

	for (const FAssetIdentifier& AssetId : ReferencedAssets)
	{
		FString AssetPath = AssetId.PackageName.ToString();

		// Skip already processed
		if (ProcessedPaths.Contains(AssetPath))
		{
			continue;
		}
		ProcessedPaths.Add(AssetPath);

		FExportedDependency Dependency;
		Dependency.AssetPath = AssetPath;
		Dependency.AssetName = FPackageName::GetShortName(AssetPath);

		// Check if it's a Blueprint
		FAssetData AssetData = AssetRegistry.GetAssetByObjectPath(FSoftObjectPath(AssetPath));
		if (AssetData.IsValid())
		{
			FString AssetClass = AssetData.AssetClassPath.ToString();
			Dependency.bIsBlueprint = AssetClass.Contains(TEXT("Blueprint"));
		}

		// Check if it's a native class
		UClass* Class = FindObject<UClass>(nullptr, *AssetPath);
		Dependency.bIsNativeClass = Class && Class->IsNative();

		Dependency.DependencyType = EExportDependencyType::Hard;

		Dependencies.Add(Dependency);
	}

	// Also track the parent class as a dependency
	if (Blueprint && Blueprint->ParentClass)
	{
		FExportedDependency ParentDep;
		ParentDep.AssetPath = Blueprint->ParentClass->GetPathName();
		ParentDep.AssetName = Blueprint->ParentClass->GetName();
		ParentDep.bIsBlueprint = !Blueprint->ParentClass->IsNative();
		ParentDep.bIsNativeClass = Blueprint->ParentClass->IsNative();
		ParentDep.DependencyType = EExportDependencyType::Hard;
		ParentDep.Description = TEXT("Parent class");

		if (!ProcessedPaths.Contains(ParentDep.AssetPath))
		{
			Dependencies.Add(ParentDep);
		}
	}

	return Dependencies;
}

FExportedParentClass FBlueprintSerializer::SerializeParentClass(const UBlueprint* Blueprint)
{
	FExportedParentClass ParentClass;

	if (!Blueprint)
	{
		UE_LOG(LogBlueprintExporter, Error, TEXT("[BlueprintExporter] SerializeParentClass called with null Blueprint"));
		return ParentClass;
	}

	if (!Blueprint->ParentClass)
	{
		ParentClass.ClassName = TEXT("Unknown");
		UE_LOG(LogBlueprintExporter, Warning, TEXT("[BlueprintExporter] Blueprint '%s' has null ParentClass - export will have incomplete parent class data"), *Blueprint->GetName());
		return ParentClass;
	}

	ParentClass.ClassName = Blueprint->ParentClass->GetName();
	ParentClass.ClassPath = Blueprint->ParentClass->GetPathName();
	ParentClass.bIsNative = Blueprint->ParentClass->IsNative();

	if (ParentClass.bIsNative)
	{
		ParentClass.ModuleName = Blueprint->ParentClass->GetOutermost()->GetName();
	}

	return ParentClass;
}

TArray<FString> FBlueprintSerializer::SerializeImplementedInterfaces(const UBlueprint* Blueprint)
{
	TArray<FString> Interfaces;

	if (Blueprint)
	{
		for (const FBPInterfaceDescription& InterfaceDesc : Blueprint->ImplementedInterfaces)
		{
			if (InterfaceDesc.Interface)
			{
				Interfaces.Add(InterfaceDesc.Interface->GetPathName());
			}
		}
	}

	return Interfaces;
}

EBlueprintExportType FBlueprintSerializer::ConvertBlueprintType(const UBlueprint* Blueprint)
{
	if (!Blueprint)
	{
		return EBlueprintExportType::Unknown;
	}

	switch (Blueprint->BlueprintType)
	{
	case BPTYPE_Normal:
		return EBlueprintExportType::Normal;
	case BPTYPE_Const:
		return EBlueprintExportType::Const;
	case BPTYPE_MacroLibrary:
		return EBlueprintExportType::MacroLibrary;
	case BPTYPE_Interface:
		return EBlueprintExportType::Interface;
	case BPTYPE_LevelScript:
		return EBlueprintExportType::LevelScript;
	case BPTYPE_FunctionLibrary:
		return EBlueprintExportType::FunctionLibrary;
	default:
		return EBlueprintExportType::Unknown;
	}
}

FString FBlueprintSerializer::DetectBlueprintSubclass(const UBlueprint* Blueprint)
{
	if (!Blueprint)
	{
		return TEXT("Blueprint");
	}

	FString ClassName = Blueprint->GetClass()->GetFName().ToString();

	// Strip the standard UE "U" prefix if present
	if (ClassName.StartsWith(TEXT("U")))
	{
		ClassName.RemoveAt(0, 1);
	}

	return ClassName;
}

FString FBlueprintSerializer::GenerateStableNodeId(const UEdGraphNode* Node)
{
	if (!Node)
	{
		return TEXT("");
	}

	// Generate a stable ID based on node type and properties
	// This helps maintain consistency across exports
	FString TypePrefix;

	if (Node->IsA<UK2Node_Event>())
	{
		const UK2Node_Event* EventNode = Cast<UK2Node_Event>(Node);
		TypePrefix = FString::Printf(TEXT("Event_%s"), *EventNode->GetFunctionName().ToString());
	}
	else if (Node->IsA<UK2Node_FunctionEntry>())
	{
		TypePrefix = TEXT("Entry");
	}
	else if (Node->IsA<UK2Node_FunctionResult>())
	{
		TypePrefix = TEXT("Result");
	}
	else if (Node->IsA<UK2Node_CallFunction>())
	{
		const UK2Node_CallFunction* CallNode = Cast<UK2Node_CallFunction>(Node);
		TypePrefix = FString::Printf(TEXT("Call_%s"), *CallNode->FunctionReference.GetMemberName().ToString());
	}
	else if (Node->IsA<UK2Node_VariableGet>())
	{
		const UK2Node_VariableGet* VarNode = Cast<UK2Node_VariableGet>(Node);
		TypePrefix = FString::Printf(TEXT("Get_%s"), *VarNode->GetVarName().ToString());
	}
	else if (Node->IsA<UK2Node_VariableSet>())
	{
		const UK2Node_VariableSet* VarNode = Cast<UK2Node_VariableSet>(Node);
		TypePrefix = FString::Printf(TEXT("Set_%s"), *VarNode->GetVarName().ToString());
	}
	else
	{
		TypePrefix = Node->GetClass()->GetName();
	}

	// Use position and a *content-derived* stable hash (not `Node->NodeGuid`,
	// which drifts for auto-regenerated nodes — see ComputeStableNodeHash).
	FString StableId = FString::Printf(TEXT("%s_%d_%d_%s"),
		*TypePrefix,
		Node->NodePosX,
		Node->NodePosY,
		*ComputeStableNodeHash(Node).Left(8));

	return StableId;
}

FString FBlueprintSerializer::GenerateStablePinId(const UEdGraphPin* Pin)
{
	if (!Pin)
	{
		return TEXT("");
	}

	// For pins, use the pin name combined with direction
	FString DirectionPrefix = (Pin->Direction == EGPD_Input) ? TEXT("In") : TEXT("Out");
	return FString::Printf(TEXT("%s_%s"), *DirectionPrefix, *Pin->PinName.ToString());
}

void FBlueprintSerializer::SerializeFunctionSignature(const UEdGraph* FunctionGraph, TArray<FExportedFunctionParam>& OutInputs, TArray<FExportedFunctionParam>& OutOutputs)
{
	if (!FunctionGraph)
	{
		return;
	}

	for (UEdGraphNode* Node : FunctionGraph->Nodes)
	{
		// Get inputs from function entry
		if (UK2Node_FunctionEntry* EntryNode = Cast<UK2Node_FunctionEntry>(Node))
		{
			for (UEdGraphPin* Pin : EntryNode->Pins)
			{
				// Skip exec pin and self pin
				if (Pin && Pin->Direction == EGPD_Output &&
					Pin->PinType.PinCategory != UEdGraphSchema_K2::PC_Exec &&
					Pin->PinName != UEdGraphSchema_K2::PN_Self)
				{
					FExportedFunctionParam Param;
					Param.ParamName = Pin->PinName.ToString();
					// Use safe version with pin context to resolve types from node
					Param.ParamType = SerializePinTypeSafe(Pin);
					Param.DefaultValue = Pin->DefaultValue;
					Param.bIsOutput = false;
					Param.bPassByReference = Pin->PinType.bIsReference;
					OutInputs.Add(Param);
				}
			}
		}
		// Get outputs from function result
		else if (UK2Node_FunctionResult* ResultNode = Cast<UK2Node_FunctionResult>(Node))
		{
			for (UEdGraphPin* Pin : ResultNode->Pins)
			{
				// Skip exec pin
				if (Pin && Pin->Direction == EGPD_Input &&
					Pin->PinType.PinCategory != UEdGraphSchema_K2::PC_Exec)
				{
					FExportedFunctionParam Param;
					Param.ParamName = Pin->PinName.ToString();
					// Use safe version with pin context to resolve types from node
					Param.ParamType = SerializePinTypeSafe(Pin);
					Param.bIsOutput = true;
					Param.bPassByReference = Pin->PinType.bIsReference;
					OutOutputs.Add(Param);
				}
			}
		}
	}
}

// =============================================================================
// State Machine Serialization (AnimBP support)
// =============================================================================

TArray<FExportedStateMachine> FBlueprintSerializer::SerializeStateMachines(const UBlueprint* Blueprint)
{
	TArray<FExportedStateMachine> Result;
	if (!Blueprint) return Result;

	// Collect all graphs to search (AnimGraph lives in FunctionGraphs)
	TArray<UEdGraph*> AllGraphs;
	AllGraphs.Append(Blueprint->FunctionGraphs);
	AllGraphs.Append(Blueprint->UbergraphPages);

	for (UEdGraph* Graph : AllGraphs)
	{
		if (!Graph) continue;
		for (UEdGraphNode* Node : Graph->Nodes)
		{
			if (UAnimGraphNode_StateMachine* SMNode = Cast<UAnimGraphNode_StateMachine>(Node))
			{
				FExportedStateMachine SM = SerializeStateMachine(SMNode);
				Result.Add(SM);
			}
		}
	}

	return Result;
}

FExportedStateMachine FBlueprintSerializer::SerializeStateMachine(const UAnimGraphNode_StateMachine* SMNode)
{
	FExportedStateMachine SM;
	if (!SMNode) return SM;

	UAnimationStateMachineGraph* SMGraph = SMNode->EditorStateMachineGraph;
	SM.MachineName = SMGraph ? SMGraph->GetName() : SMNode->GetNodeTitle(ENodeTitleType::FullTitle).ToString();
	SM.MachineGuid = SMNode->NodeGuid.ToString();

	if (!SMGraph) return SM;

	for (UEdGraphNode* Node : SMGraph->Nodes)
	{
		if (!Node) continue;

		// States (real animation states)
		if (UAnimStateNode* StateNode = Cast<UAnimStateNode>(Node))
		{
			FExportedAnimState State;
			State.StateName = StateNode->GetStateName();
			State.StateGuid = StateNode->NodeGuid.ToString();
			State.StateType = TEXT("State");

			if (StateNode->BoundGraph)
			{
				State.AnimGraph = SerializeGraph(StateNode->BoundGraph);

				// Check for nested state machines (ANIM-06)
				for (UEdGraphNode* InnerNode : StateNode->BoundGraph->Nodes)
				{
					if (UAnimGraphNode_StateMachine* NestedSM = Cast<UAnimGraphNode_StateMachine>(InnerNode))
					{
						State.NestedStateMachines.Add(SerializeStateMachine(NestedSM));
					}
				}
			}

			SM.States.Add(State);
		}
		// Conduits (pass-through routing nodes)
		else if (UAnimStateConduitNode* ConduitNode = Cast<UAnimStateConduitNode>(Node))
		{
			FExportedAnimState State;
			State.StateName = ConduitNode->GetStateName();
			State.StateGuid = ConduitNode->NodeGuid.ToString();
			State.StateType = TEXT("Conduit");

			if (ConduitNode->BoundGraph)
			{
				State.AnimGraph = SerializeGraph(ConduitNode->BoundGraph);
			}

			SM.States.Add(State);
		}
		// Transitions
		else if (UAnimStateTransitionNode* TransNode = Cast<UAnimStateTransitionNode>(Node))
		{
			FExportedAnimTransition Trans;
			Trans.TransitionGuid = TransNode->NodeGuid.ToString();

			// Source and target state names (null-safe per project principle: never guess values)
			UAnimStateNodeBase* PrevState = TransNode->GetPreviousState();
			UAnimStateNodeBase* NextState = TransNode->GetNextState();
			Trans.SourceState = PrevState ? PrevState->GetStateName() : TEXT("unknown");
			Trans.TargetState = NextState ? NextState->GetStateName() : TEXT("unknown");

			// Build transition name from source->target
			Trans.TransitionName = Trans.SourceState + TEXT("_to_") + Trans.TargetState;

			// Rule graph (ANIM-04)
			if (TransNode->BoundGraph)
			{
				Trans.RuleGraph = SerializeGraph(TransNode->BoundGraph);
			}

			// Blend settings (ANIM-05)
			Trans.BlendSettings.CrossfadeDuration = TransNode->CrossfadeDuration;
			Trans.BlendSettings.PriorityOrder = TransNode->PriorityOrder;
			Trans.BlendSettings.bAutomaticRuleBasedOnSequencePlayer = TransNode->bAutomaticRuleBasedOnSequencePlayerInState;

			// Enum-to-string conversions
			// BlendMode (EAlphaBlendOption) -- core UE enum with reflection
			UEnum* BlendModeEnum = StaticEnum<EAlphaBlendOption>();
			if (BlendModeEnum)
			{
				Trans.BlendSettings.BlendMode = BlendModeEnum->GetNameStringByValue(static_cast<int64>(TransNode->BlendMode));
			}
			else
			{
				Trans.BlendSettings.BlendMode = FString::FromInt(static_cast<int32>(TransNode->BlendMode));
			}

			// CrossfadeMode (ETransitionBlendMode) - deprecated in 5.7, use LogicType instead
			// Read from deprecated field for backward compat
			switch (TransNode->CrossfadeMode_DEPRECATED)
			{
			case ETransitionBlendMode::TBM_Linear:
				Trans.BlendSettings.CrossfadeMode = TEXT("Linear");
				break;
			case ETransitionBlendMode::TBM_Cubic:
				Trans.BlendSettings.CrossfadeMode = TEXT("Cubic");
				break;
			default:
				Trans.BlendSettings.CrossfadeMode = FString::FromInt(static_cast<int32>(TransNode->CrossfadeMode_DEPRECATED));
				break;
			}

			// LogicType (ETransitionLogicType)
			switch (TransNode->LogicType)
			{
			case ETransitionLogicType::TLT_StandardBlend:
				Trans.BlendSettings.LogicType = TEXT("StandardBlend");
				break;
			case ETransitionLogicType::TLT_Inertialization:
				Trans.BlendSettings.LogicType = TEXT("Inertialization");
				break;
			case ETransitionLogicType::TLT_Custom:
				Trans.BlendSettings.LogicType = TEXT("Custom");
				break;
			default:
				Trans.BlendSettings.LogicType = FString::FromInt(static_cast<int32>(TransNode->LogicType));
				break;
			}

			SM.Transitions.Add(Trans);
		}
		// UAnimStateEntryNode -- skip (it's a pointer to the initial state, not a state itself)
		// Per research Pitfall 3: serializing it creates a phantom state that doesn't exist
	}

	return SM;
}

// ===== WidgetBlueprint tree =====

TArray<FExportedWidgetNode> FBlueprintSerializer::SerializeWidgetTree(const UBlueprint* Blueprint)
{
	TArray<FExportedWidgetNode> Out;
	if (!Blueprint)
	{
		return Out;
	}

	const UBaseWidgetBlueprint* WidgetBP = Cast<UBaseWidgetBlueprint>(Blueprint);
	if (!WidgetBP || !WidgetBP->WidgetTree)
	{
		return Out;
	}

	const UWidget* Root = WidgetBP->WidgetTree->RootWidget;
	if (!Root)
	{
		return Out;
	}

	Out.Add(SerializeWidgetNode(Root));
	return Out;
}

FExportedWidgetNode FBlueprintSerializer::SerializeWidgetNode(const UWidget* Widget)
{
	FExportedWidgetNode Node;
	if (!Widget)
	{
		return Node;
	}

	Node.WidgetName = Widget->GetName();
	if (UClass* Cls = Widget->GetClass())
	{
		Node.WidgetClass = Cls->GetPathName();
	}
	Node.bIsVariable = Widget->bIsVariable;

	// Slot type tells consumers how this widget is laid out by its parent
	// (e.g., HorizontalBoxSlot vs VerticalBoxSlot vs CanvasPanelSlot).
	if (Widget->Slot)
	{
		if (UClass* SlotCls = Widget->Slot->GetClass())
		{
			Node.SlotClass = SlotCls->GetPathName();
		}
	}

	// Recurse into children. UPanelWidget exposes the authored child array
	// via GetChildAt(i). Authored order is preserved — slot order is
	// semantically load-bearing in UMG layout.
	if (const UPanelWidget* Panel = Cast<UPanelWidget>(Widget))
	{
		const int32 ChildCount = Panel->GetChildrenCount();
		Node.Children.Reserve(ChildCount);
		for (int32 i = 0; i < ChildCount; ++i)
		{
			if (UWidget* Child = Panel->GetChildAt(i))
			{
				Node.Children.Add(SerializeWidgetNode(Child));
			}
		}
	}
	return Node;
}

