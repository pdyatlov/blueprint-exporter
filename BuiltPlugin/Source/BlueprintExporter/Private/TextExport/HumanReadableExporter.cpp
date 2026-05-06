// Copyright Epic Games, Inc. All Rights Reserved.

#include "TextExport/HumanReadableExporter.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace
{
	/** Defense-in-depth cap on the renderer's own recursion. The serializer caps
	 *  its tree construction at MAX_SUBOBJECT_RECURSION_DEPTH=8 (BlueprintSerializer.cpp),
	 *  so in-plugin JSON is always safe; this cap protects against externally-
	 *  constructed FJsonValue graphs that somehow evade bCycleDetected. Kept higher
	 *  than the serializer's cap so we don't accidentally truncate legitimate output. */
	constexpr int32 MAX_RENDER_RECURSION_DEPTH = 16;

	/** Leaf name of an asset / class path. FPackageName::GetShortName strips up to the
	 *  last '/' only, so "/Script/AIModule.AIPerceptionComponent" comes back as
	 *  "AIModule.AIPerceptionComponent"; readers (and LLM consumers) want
	 *  "AIPerceptionComponent". Stripping after the last '.' handles both
	 *  "/Script/Module.Class" paths and bare "Module.Class" forms. */
	FString GetClassLeafName(const FString& Path)
	{
		FString ShortName = FPackageName::GetShortName(Path);
		int32 DotIndex = INDEX_NONE;
		if (ShortName.FindLastChar(TEXT('.'), DotIndex))
		{
			return ShortName.Mid(DotIndex + 1);
		}
		return ShortName;
	}

	/** Aggregate counts for the "export coverage" block at the top of .txt and in
	 *  the digest. Lets a developer see at a glance whether the export captured the
	 *  structured data they need before pasting it into a chat. */
	struct FExportCoverageStats
	{
		int32 ComponentCount = 0;
		int32 ComponentPropertyCount = 0;
		int32 InstancedProperties = 0;
		int32 SubobjectInstancesParsed = 0;
		int32 SubobjectInstancesBroken = 0;
		int32 SubobjectInstancesTruncated = 0;
		int32 SubobjectInstancesCycles = 0;
	};

	void AccumulateSubobjectStats(const TSharedPtr<FJsonValue>& Value, FExportCoverageStats& Stats);

	void AccumulateNestedPropertyStats(const TSharedPtr<FJsonValue>& PropValue, FExportCoverageStats& Stats)
	{
		if (!PropValue.IsValid()) return;
		TSharedPtr<FJsonObject> PropObj = PropValue->AsObject();
		if (!PropObj.IsValid()) return;

		bool bIsInstanced = false;
		PropObj->TryGetBoolField(TEXT("bIsInstancedSubobject"), bIsInstanced);
		if (!bIsInstanced) return;

		Stats.InstancedProperties++;
		const TArray<TSharedPtr<FJsonValue>>* Nested = nullptr;
		if (PropObj->TryGetArrayField(TEXT("subobjects"), Nested) && Nested)
		{
			for (const TSharedPtr<FJsonValue>& SubValue : *Nested)
			{
				AccumulateSubobjectStats(SubValue, Stats);
			}
		}
	}

	void AccumulateSubobjectStats(const TSharedPtr<FJsonValue>& Value, FExportCoverageStats& Stats)
	{
		if (!Value.IsValid())
		{
			Stats.SubobjectInstancesBroken++;
			return;
		}
		TSharedPtr<FJsonObject> Obj = Value->AsObject();
		if (!Obj.IsValid())
		{
			// JSON null element — serializer emits these for null slots in arrays.
			Stats.SubobjectInstancesBroken++;
			return;
		}

		// Flags are mutually exclusive by construction in BlueprintSerializer
		// (early-return per branch at line ~1557-1564). Check in the same order.
		bool bBroken = false;
		Obj->TryGetBoolField(TEXT("bHasBrokenReference"), bBroken);
		bool bTruncated = false;
		Obj->TryGetBoolField(TEXT("bTruncated"), bTruncated);
		bool bCycle = false;
		Obj->TryGetBoolField(TEXT("bCycleDetected"), bCycle);

		if (bBroken)         Stats.SubobjectInstancesBroken++;
		else if (bTruncated) Stats.SubobjectInstancesTruncated++;
		else if (bCycle)     Stats.SubobjectInstancesCycles++;
		else                 Stats.SubobjectInstancesParsed++;

		// Recurse through the subobject's own property list so nested instanced
		// properties contribute to the tally too.
		const TArray<TSharedPtr<FJsonValue>>* Props = nullptr;
		if (Obj->TryGetArrayField(TEXT("properties"), Props) && Props)
		{
			for (const TSharedPtr<FJsonValue>& PropValue : *Props)
			{
				AccumulateNestedPropertyStats(PropValue, Stats);
			}
		}
	}

	void AccumulateComponentStats(const FExportedComponent& Component, FExportCoverageStats& Stats)
	{
		Stats.ComponentCount++;
		for (const FExportedComponentProperty& Property : Component.Properties)
		{
			Stats.ComponentPropertyCount++;
			if (Property.bIsInstancedSubobject)
			{
				Stats.InstancedProperties++;
				for (const TSharedPtr<FJsonValue>& SubValue : Property.SubobjectJsonValues)
				{
					AccumulateSubobjectStats(SubValue, Stats);
				}
			}
		}
		for (const FExportedComponent& Child : Component.ChildComponents)
		{
			AccumulateComponentStats(Child, Stats);
		}
	}

	FExportCoverageStats ComputeCoverage(const FExportedBlueprint& Data)
	{
		FExportCoverageStats Stats;
		for (const FExportedComponent& Component : Data.Components)
		{
			AccumulateComponentStats(Component, Stats);
		}
		return Stats;
	}

	FString FormatCoverageBlock(const FExportCoverageStats& Stats)
	{
		if (Stats.ComponentCount == 0)
		{
			return FString();
		}

		FString Output = TEXT("COVERAGE:\n");
		Output += FString::Printf(TEXT("  %d component%s, %d propert%s\n"),
			Stats.ComponentCount, Stats.ComponentCount == 1 ? TEXT("") : TEXT("s"),
			Stats.ComponentPropertyCount, Stats.ComponentPropertyCount == 1 ? TEXT("y") : TEXT("ies"));

		if (Stats.InstancedProperties > 0)
		{
			const int32 TotalInstances =
				Stats.SubobjectInstancesParsed +
				Stats.SubobjectInstancesBroken +
				Stats.SubobjectInstancesTruncated +
				Stats.SubobjectInstancesCycles;

			FString Detail = FString::Printf(TEXT("%d parsed"), Stats.SubobjectInstancesParsed);
			if (Stats.SubobjectInstancesBroken > 0)
			{
				Detail += FString::Printf(TEXT(", %d broken"), Stats.SubobjectInstancesBroken);
			}
			if (Stats.SubobjectInstancesTruncated > 0)
			{
				Detail += FString::Printf(TEXT(", %d truncated"), Stats.SubobjectInstancesTruncated);
			}
			if (Stats.SubobjectInstancesCycles > 0)
			{
				Detail += FString::Printf(TEXT(", %d cycle%s"), Stats.SubobjectInstancesCycles,
					Stats.SubobjectInstancesCycles == 1 ? TEXT("") : TEXT("s"));
			}

			Output += FString::Printf(TEXT("  %d instanced-subobject propert%s, %d subobject instance%s (%s)\n"),
				Stats.InstancedProperties, Stats.InstancedProperties == 1 ? TEXT("y") : TEXT("ies"),
				TotalInstances, TotalInstances == 1 ? TEXT("") : TEXT("s"),
				*Detail);
		}

		Output += TEXT("\n");
		return Output;
	}
}

FHumanReadableExporter::FHumanReadableExporter()
{
}

FHumanReadableExporter::~FHumanReadableExporter()
{
}

FString FHumanReadableExporter::ExportToText(const FExportedBlueprint& ExportedData)
{
	FString Output;

	// Header
	Output += TEXT("================================================================================\n");
	Output += FString::Printf(TEXT("BLUEPRINT: %s\n"), *ExportedData.AssetName);
	Output += FString::Printf(TEXT("Path: %s\n"), *ExportedData.AssetPath);
	Output += FString::Printf(TEXT("Parent: %s%s\n"),
		*ExportedData.ParentClass.ClassName,
		ExportedData.ParentClass.bIsNative ? TEXT(" (C++)") : TEXT(" (Blueprint)"));

	if (!ExportedData.BlueprintSubclass.IsEmpty() && ExportedData.BlueprintSubclass != TEXT("Blueprint"))
	{
		Output += FString::Printf(TEXT("Type: %s\n"), *ExportedData.BlueprintSubclass);
	}

	if (ExportedData.ImplementedInterfaces.Num() > 0)
	{
		Output += TEXT("Interfaces: ");
		for (int32 i = 0; i < ExportedData.ImplementedInterfaces.Num(); ++i)
		{
			if (i > 0) Output += TEXT(", ");
			Output += GetClassLeafName(ExportedData.ImplementedInterfaces[i]);
		}
		Output += TEXT("\n");
	}

	Output += TEXT("================================================================================\n\n");

	// Coverage header — gives the reader a one-glance confidence signal about
	// whether the export captured the structured data they'll need. Gated on
	// presence of components so Blueprints with no components stay unchanged.
	Output += FormatCoverageBlock(ComputeCoverage(ExportedData));

	// Variables
	if (ExportedData.Variables.Num() > 0)
	{
		Output += TEXT("VARIABLES:\n");
		for (const FExportedVariable& Var : ExportedData.Variables)
		{
			Output += TEXT("  ") + FormatVariable(Var) + TEXT("\n");
		}
		Output += TEXT("\n");
	}

	// Components
	if (ExportedData.Components.Num() > 0)
	{
		Output += TEXT("COMPONENTS:\n");
		Output += FormatComponentHierarchy(ExportedData.Components, 1);
		Output += TEXT("\n");
	}

	// Functions
	if (ExportedData.Functions.Num() > 0)
	{
		Output += TEXT("FUNCTIONS:\n");
		for (const FExportedFunction& Func : ExportedData.Functions)
		{
			Output += TEXT("  ") + FormatFunctionSignature(Func) + TEXT("\n");
		}
		Output += TEXT("\n");
	}

	// Macros
	if (ExportedData.Macros.Num() > 0)
	{
		Output += TEXT("MACROS:\n");
		for (const FExportedFunction& Macro : ExportedData.Macros)
		{
			Output += FString::Printf(TEXT("  # %s\n"), *Macro.FunctionName);
		}
		Output += TEXT("\n");
	}

	// Event Graph Execution Flow
	if (ExportedData.EventGraph.Nodes.Num() > 0)
	{
		Output += TEXT("EVENT GRAPH:\n");
		Output += ExportExecutionFlow(ExportedData.EventGraph);
		Output += TEXT("\n");
	}

	// Function Graphs
	for (const FExportedFunction& Func : ExportedData.Functions)
	{
		if (Func.Graph.Nodes.Num() > 0)
		{
			Output += FString::Printf(TEXT("FUNCTION: %s\n"), *Func.FunctionName);
			Output += ExportExecutionFlow(Func.Graph);
			Output += TEXT("\n");
		}
	}

	// Construction Script
	if (ExportedData.ConstructionScript.Nodes.Num() > 0)
	{
		Output += TEXT("CONSTRUCTION SCRIPT:\n");
		Output += ExportExecutionFlow(ExportedData.ConstructionScript);
		Output += TEXT("\n");
	}

	// Dependencies summary
	if (ExportedData.Dependencies.Num() > 0)
	{
		Output += TEXT("DEPENDENCIES:\n");
		for (const FExportedDependency& Dep : ExportedData.Dependencies)
		{
			FString TypeStr = Dep.bIsNativeClass ? TEXT("Native") : (Dep.bIsBlueprint ? TEXT("Blueprint") : TEXT("Asset"));
			Output += FString::Printf(TEXT("  - [%s] %s\n"), *TypeStr, *Dep.AssetPath);
		}
	}

	return Output;
}

FString FHumanReadableExporter::ExportGraphToText(const FExportedGraph& Graph, const FString& GraphName)
{
	FString Output;
	Output += FString::Printf(TEXT("Graph: %s\n"), *GraphName);
	Output += FString::Printf(TEXT("Nodes: %d\n"), Graph.Nodes.Num());
	Output += TEXT("---\n");

	for (const FExportedNode& Node : Graph.Nodes)
	{
		Output += FString::Printf(TEXT("[%s] %s at (%d, %d)\n"),
			*Node.NodeType, *Node.NodeTitle, Node.PositionX, Node.PositionY);

		if (!Node.Comment.IsEmpty())
		{
			Output += FString::Printf(TEXT("  Comment: %s\n"), *Node.Comment);
		}

		// Show connections
		for (const FExportedPin& Pin : Node.Pins)
		{
			if (Pin.Direction == EExportPinDirection::Output && Pin.Connections.Num() > 0)
			{
				for (const FExportedPinConnection& Conn : Pin.Connections)
				{
					Output += FString::Printf(TEXT("  %s -> %s.%s\n"),
						*Pin.PinName, *Conn.NodeId, *Conn.PinId);
				}
			}
		}
	}

	return Output;
}

FString FHumanReadableExporter::ExportExecutionFlow(const FExportedGraph& Graph)
{
	FString Output;

	// Find all event/entry nodes
	TArray<int32> EntryNodeIndices;
	for (int32 i = 0; i < Graph.Nodes.Num(); ++i)
	{
		const FExportedNode& Node = Graph.Nodes[i];
		if (Node.NodeType == TEXT("Event") ||
			Node.NodeType == TEXT("FunctionEntry") ||
			Node.NodeTitle.StartsWith(TEXT("Event ")))
		{
			EntryNodeIndices.Add(i);
		}
	}

	// Sort by position for consistent output
	EntryNodeIndices.Sort([&Graph](int32 A, int32 B) -> bool {
		const FExportedNode& NodeA = Graph.Nodes[A];
		const FExportedNode& NodeB = Graph.Nodes[B];
		if (NodeA.PositionY != NodeB.PositionY) return NodeA.PositionY < NodeB.PositionY;
		return NodeA.PositionX < NodeB.PositionX;
	});

	for (int32 Index : EntryNodeIndices)
	{
		Output += TraceExecutionFlow(Graph, Graph.Nodes[Index], 1);
		Output += TEXT("\n");
	}

	return Output;
}

FString FHumanReadableExporter::TraceExecutionFlow(const FExportedGraph& Graph, const FExportedNode& StartNode, int32 IndentLevel)
{
	FString Output;
	TSet<FString> VisitedExecNodes;
	TSet<FString> VisitedPureNodes;

	// Format the entry node
	FString NodeDisplay = FormatNodeInline(StartNode);

	// Check for input parameters (for events)
	TArray<FString> Inputs;
	for (const FExportedPin& Pin : StartNode.Pins)
	{
		if (Pin.Direction == EExportPinDirection::Output &&
			Pin.PinType.Category != TEXT("exec") &&
			!Pin.PinName.IsEmpty() &&
			Pin.PinName != TEXT("self"))
		{
			FString ParamStr = Pin.PinName;
			if (!Pin.PinType.Category.IsEmpty())
			{
				ParamStr += TEXT(": ") + FormatPinType(Pin.PinType);
			}
			Inputs.Add(ParamStr);
		}
	}

	if (Inputs.Num() > 0)
	{
		NodeDisplay += TEXT(" (") + FString::Join(Inputs, TEXT(", ")) + TEXT(")");
	}

	Output += Indent(IndentLevel - 1) + NodeDisplay + TEXT("\n");

	// Track branching for proper indentation
	const FExportedNode* CurrentNode = &StartNode;
	VisitedExecNodes.Add(CurrentNode->NodeId);

	while (CurrentNode)
	{
		// Get all exec connections paired with their source pin names
		TArray<FExecConnection> ExecConnections = GetExecConnections(Graph, *CurrentNode);

		if (ExecConnections.Num() == 0)
		{
			// End of chain - show termination
			Output += Indent(IndentLevel) + TEXT("\u2514\u2500 then \u2192\n");
			Output += Indent(IndentLevel + 1) + TEXT("(not connected)\n");
			break;
		}
		else if (ExecConnections.Num() == 1)
		{
			// Linear flow
			const FExportedNode* NextNode = ExecConnections[0].ConnectedNode;

			if (VisitedExecNodes.Contains(NextNode->NodeId))
			{
				Output += Indent(IndentLevel) + TEXT("\u2514\u2500 then \u2192 [Loop back to ") + NextNode->NodeTitle + TEXT("]\n");
				break;
			}

			VisitedExecNodes.Add(NextNode->NodeId);

			// Format with full input expansion
			VisitedPureNodes.Reset();
			FString NodeStr = FormatNodeWithInputs(Graph, *NextNode);
			Output += Indent(IndentLevel) + TEXT("\u2514\u2500 then \u2192\n");
			Output += Indent(IndentLevel + 1) + NodeStr + TEXT("\n");

			// Show pure node chain - skip first level (already shown inline) and show their children
			VisitedPureNodes.Add(NextNode->NodeId);
			FString PureChain = FormatPureNodeChainFromDepth1(Graph, *NextNode, VisitedPureNodes, IndentLevel + 2);
			if (!PureChain.IsEmpty())
			{
				Output += PureChain;
			}

			// Check for comments
			if (!NextNode->Comment.IsEmpty())
			{
				Output += Indent(IndentLevel + 1) + TEXT("// ") + NextNode->Comment + TEXT("\n");
			}

			CurrentNode = NextNode;
		}
		else
		{
			// Branching (if/switch/latent action with multiple exec outputs)
			VisitedPureNodes.Reset();
			VisitedPureNodes.Add(CurrentNode->NodeId);
			FString BranchNodeStr = FormatNodeWithInputs(Graph, *CurrentNode);

			// Show the branch node with its condition expanded inline
			Output += Indent(IndentLevel) + TEXT("\u2514\u2500 then \u2192\n");
			Output += Indent(IndentLevel + 1) + BranchNodeStr + TEXT("\n");

			// Show pure node chain for the branch condition (skip depth-0, show depth-1+)
			FString PureChain = FormatPureNodeChainFromDepth1(Graph, *CurrentNode, VisitedPureNodes, IndentLevel + 2);
			if (!PureChain.IsEmpty())
			{
				Output += PureChain;
			}

			for (int32 i = 0; i < ExecConnections.Num(); ++i)
			{
				const FExecConnection& Connection = ExecConnections[i];
				const FExportedNode* BranchNode = Connection.ConnectedNode;
				const FString& BranchLabel = Connection.PinName;

				if (VisitedExecNodes.Contains(BranchNode->NodeId))
				{
					Output += Indent(IndentLevel) + TEXT("\u251C\u2500 [") + BranchLabel + TEXT("] \u2192 [Loop]\n");
					continue;
				}

				// Use different tree characters for last item
				FString TreeChar = (i == ExecConnections.Num() - 1) ? TEXT("\u2514\u2500") : TEXT("\u251C\u2500");
				Output += Indent(IndentLevel) + TreeChar + TEXT(" [") + BranchLabel + TEXT("] \u2192\n");

				// Format the branch target node
				VisitedPureNodes.Reset();
				VisitedPureNodes.Add(BranchNode->NodeId);
				FString BranchTargetStr = FormatNodeWithInputs(Graph, *BranchNode);
				Output += Indent(IndentLevel + 1) + BranchTargetStr + TEXT("\n");

				// Show pure chain for this branch (skip depth-0, show depth-1+)
				FString BranchPureChain = FormatPureNodeChainFromDepth1(Graph, *BranchNode, VisitedPureNodes, IndentLevel + 2);
				if (!BranchPureChain.IsEmpty())
				{
					Output += BranchPureChain;
				}
			}

			break; // Stop after branch for now (could recurse for full tree)
		}
	}

	return Output;
}

const FExportedNode* FHumanReadableExporter::FindNodeById(const FExportedGraph& Graph, const FString& NodeId)
{
	for (const FExportedNode& Node : Graph.Nodes)
	{
		if (Node.NodeId == NodeId)
		{
			return &Node;
		}
	}
	return nullptr;
}

const FExportedNode* FHumanReadableExporter::GetNextExecNode(const FExportedGraph& Graph, const FExportedNode& Node)
{
	for (const FExportedPin& Pin : Node.Pins)
	{
		if (Pin.Direction == EExportPinDirection::Output &&
			Pin.PinType.Category == TEXT("exec") &&
			Pin.Connections.Num() > 0)
		{
			return FindNodeById(Graph, Pin.Connections[0].NodeId);
		}
	}
	return nullptr;
}

TArray<FHumanReadableExporter::FExecConnection> FHumanReadableExporter::GetExecConnections(const FExportedGraph& Graph, const FExportedNode& Node)
{
	TArray<FExecConnection> Result;

	for (const FExportedPin& Pin : Node.Pins)
	{
		if (Pin.Direction == EExportPinDirection::Output &&
			Pin.PinType.Category == TEXT("exec"))
		{
			for (const FExportedPinConnection& Conn : Pin.Connections)
			{
				const FExportedNode* ConnectedNode = FindNodeById(Graph, Conn.NodeId);
				if (ConnectedNode)
				{
					FExecConnection Connection;
					Connection.PinName = Pin.PinName;
					Connection.ConnectedNode = ConnectedNode;
					Result.Add(Connection);
				}
			}
		}
	}

	return Result;
}

FString FHumanReadableExporter::FormatNodeInline(const FExportedNode& Node)
{
	// Format based on node type
	if (Node.NodeType == TEXT("Event"))
	{
		return TEXT("Event ") + Node.NodeTitle.Replace(TEXT("Event "), TEXT(""));
	}
	else if (Node.NodeType == TEXT("FunctionEntry"))
	{
		return TEXT("Entry");
	}
	else if (Node.NodeType == TEXT("FunctionResult"))
	{
		return TEXT("Return");
	}
	else if (Node.NodeType == TEXT("CallFunction"))
	{
		// Try to extract function name from title
		FString FuncName = Node.NodeTitle;
		FuncName.RemoveFromStart(TEXT("Call "));
		return FuncName;
	}
	else if (Node.NodeType == TEXT("VariableGet"))
	{
		FString VarName = Node.NodeTitle;
		VarName.RemoveFromStart(TEXT("Get "));
		return TEXT("Get ") + VarName;
	}
	else if (Node.NodeType == TEXT("VariableSet"))
	{
		FString VarName = Node.NodeTitle;
		VarName.RemoveFromStart(TEXT("Set "));
		return TEXT("Set ") + VarName;
	}
	else if (Node.NodeType == TEXT("Branch"))
	{
		return TEXT("Branch");
	}
	else if (Node.NodeType == TEXT("Cast"))
	{
		return Node.NodeTitle;
	}

	return Node.NodeTitle;
}

bool FHumanReadableExporter::IsPureNode(const FExportedNode& Node) const
{
	// Pure nodes have no exec pins
	for (const FExportedPin& Pin : Node.Pins)
	{
		if (Pin.PinType.Category == TEXT("exec"))
		{
			return false;
		}
	}

	// Also check node type - some nodes are known pure types
	if (Node.NodeType == TEXT("VariableGet") ||
		Node.NodeType == TEXT("MakeStruct") ||
		Node.NodeType == TEXT("BreakStruct") ||
		Node.NodeType == TEXT("MakeArray") ||
		Node.NodeType == TEXT("GetArrayItem") ||
		Node.NodeTitle.Contains(TEXT("Make ")) ||
		Node.NodeTitle.Contains(TEXT("Break ")))
	{
		return true;
	}

	// Math and conversion nodes are typically pure
	if (Node.NodeClass.Contains(TEXT("K2Node_CallFunction")))
	{
		// Check if it's a pure function (no exec pins means pure)
		bool bHasExec = false;
		for (const FExportedPin& Pin : Node.Pins)
		{
			if (Pin.PinType.Category == TEXT("exec"))
			{
				bHasExec = true;
				break;
			}
		}
		return !bHasExec;
	}

	return false;
}

bool FHumanReadableExporter::ShouldSkipPin(const FExportedPin& Pin) const
{
	// Skip exec pins
	if (Pin.PinType.Category == TEXT("exec"))
	{
		return true;
	}

	// Skip self pins
	if (Pin.PinName.Equals(TEXT("self"), ESearchCase::IgnoreCase) ||
		Pin.PinName.Equals(TEXT("WorldContextObject"), ESearchCase::IgnoreCase))
	{
		return true;
	}

	// Skip hidden pins
	if (Pin.bHidden)
	{
		return true;
	}

	return false;
}

FString FHumanReadableExporter::FormatPinValue(const FExportedPin& Pin) const
{
	if (!Pin.DefaultValue.IsEmpty())
	{
		return Pin.DefaultValue;
	}
	if (!Pin.AutogeneratedDefaultValue.IsEmpty())
	{
		return Pin.AutogeneratedDefaultValue;
	}
	return TEXT("");
}

FString FHumanReadableExporter::GetOutputPinName(const FExportedNode& Node, const FString& PinId) const
{
	for (const FExportedPin& Pin : Node.Pins)
	{
		if (Pin.PinId == PinId && Pin.Direction == EExportPinDirection::Output)
		{
			// Common output names that should be shown
			if (Pin.PinName == TEXT("ReturnValue") || Pin.PinName == TEXT("Result"))
			{
				return TEXT(""); // Don't show these common names
			}
			// Show specific outputs like X, Y, Z, R, G, B, etc.
			if (Pin.PinName.Len() <= 3 ||
				Pin.PinName == TEXT("Location") ||
				Pin.PinName == TEXT("Rotation") ||
				Pin.PinName == TEXT("Scale") ||
				Pin.PinName == TEXT("Forward") ||
				Pin.PinName == TEXT("Right") ||
				Pin.PinName == TEXT("Up"))
			{
				return TEXT(".") + Pin.PinName;
			}
			// For longer names, still show them
			if (!Pin.PinName.IsEmpty() && Pin.PinName != TEXT("Output"))
			{
				return TEXT(".") + Pin.PinName;
			}
		}
	}
	return TEXT("");
}

FString FHumanReadableExporter::GetInputPinValue(const FExportedGraph& Graph, const FExportedPin& Pin, TSet<FString>& VisitedNodes, int32 Depth)
{
	// Limit depth for inline expansion - deeper levels shown in chain
	// Depth 0: Main node's inputs - expand pure nodes with their inputs as names
	// Depth 1+: Just show names/values, don't recurse further inline
	const int32 MaxInlineDepth = 1;

	// Check for connections first
	if (Pin.Connections.Num() > 0)
	{
		const FExportedPinConnection& Conn = Pin.Connections[0];
		const FExportedNode* ConnectedNode = FindNodeById(Graph, Conn.NodeId);

		if (ConnectedNode)
		{
			// Get the output pin name being used
			FString OutputSuffix = GetOutputPinName(*ConnectedNode, Conn.PinId);

			// If it's a pure node, expand it inline (but limit depth)
			if (IsPureNode(*ConnectedNode) && !VisitedNodes.Contains(ConnectedNode->NodeId))
			{
				VisitedNodes.Add(ConnectedNode->NodeId);

				// Get the node name
				FString NodeName = FormatNodeInline(*ConnectedNode);

				// Only expand inputs if we haven't exceeded depth limit
				if (Depth < MaxInlineDepth)
				{
					// Collect input values for this pure node
					TArray<FString> InputValues;
					for (const FExportedPin& InputPin : ConnectedNode->Pins)
					{
						if (InputPin.Direction == EExportPinDirection::Input && !ShouldSkipPin(InputPin))
						{
							FString InputVal = GetInputPinValue(Graph, InputPin, VisitedNodes, Depth + 1);
							if (!InputVal.IsEmpty())
							{
								InputValues.Add(InputPin.PinName + TEXT(" = ") + InputVal);
							}
						}
					}

					// Format as inline expansion
					if (InputValues.Num() > 0)
					{
						return NodeName + OutputSuffix + TEXT(" (") + FString::Join(InputValues, TEXT(", ")) + TEXT(")");
					}
				}

				return NodeName + OutputSuffix;
			}
			else
			{
				// Non-pure node or already visited - just show the reference
				return FormatNodeInline(*ConnectedNode) + OutputSuffix;
			}
		}
	}

	// No connection - return default/literal value
	return FormatPinValue(Pin);
}

FString FHumanReadableExporter::FormatNodeWithInputs(const FExportedGraph& Graph, const FExportedNode& Node)
{
	// Use local tracking just for inline expansion
	TSet<FString> LocalVisitedNodes;
	LocalVisitedNodes.Add(Node.NodeId);

	FString NodeName = FormatNodeInline(Node);

	// Collect all input values
	TArray<FString> InputValues;
	for (const FExportedPin& Pin : Node.Pins)
	{
		if (Pin.Direction == EExportPinDirection::Input && !ShouldSkipPin(Pin))
		{
			FString InputVal = GetInputPinValue(Graph, Pin, LocalVisitedNodes, 0);
			if (!InputVal.IsEmpty())
			{
				InputValues.Add(Pin.PinName + TEXT(" = ") + InputVal);
			}
		}
	}

	// Format the node with inputs
	if (InputValues.Num() > 0)
	{
		return NodeName + TEXT(" (") + FString::Join(InputValues, TEXT(", ")) + TEXT(")");
	}

	return NodeName;
}

FString FHumanReadableExporter::FormatPureNodeChain(const FExportedGraph& Graph, const FExportedNode& Node, TSet<FString>& VisitedNodes, int32 IndentLevel)
{
	FString Output;

	// Recursively find and format pure nodes feeding into this node
	// This shows the "chain" of data flow for pure nodes
	for (const FExportedPin& Pin : Node.Pins)
	{
		if (Pin.Direction == EExportPinDirection::Input && !ShouldSkipPin(Pin) && Pin.Connections.Num() > 0)
		{
			const FExportedPinConnection& Conn = Pin.Connections[0];
			const FExportedNode* ConnectedNode = FindNodeById(Graph, Conn.NodeId);

			if (ConnectedNode && IsPureNode(*ConnectedNode) && !VisitedNodes.Contains(ConnectedNode->NodeId))
			{
				VisitedNodes.Add(ConnectedNode->NodeId);

				// Format this pure node with its own inputs expanded
				FString PureNodeStr = FormatNodeWithInputs(Graph, *ConnectedNode);
				FString OutputSuffix = GetOutputPinName(*ConnectedNode, Conn.PinId);

				// Use ↳ (U+21B3) for the chain indicator
				Output += Indent(IndentLevel) + TEXT("\u21B3 ") + PureNodeStr + OutputSuffix + TEXT("\n");

				// Recursively show pure nodes feeding into this one
				Output += FormatPureNodeChain(Graph, *ConnectedNode, VisitedNodes, IndentLevel + 1);
			}
		}
	}

	return Output;
}

FString FHumanReadableExporter::FormatPureNodeChainFromDepth1(const FExportedGraph& Graph, const FExportedNode& Node, TSet<FString>& VisitedNodes, int32 IndentLevel)
{
	FString Output;

	// First, find all depth-0 pure nodes (direct inputs to this exec node)
	// Mark them as visited but don't show them (they're already inline)
	// Then show THEIR inputs (depth-1 pure nodes) in the chain
	for (const FExportedPin& Pin : Node.Pins)
	{
		if (Pin.Direction == EExportPinDirection::Input && !ShouldSkipPin(Pin) && Pin.Connections.Num() > 0)
		{
			const FExportedPinConnection& Conn = Pin.Connections[0];
			const FExportedNode* Depth0Node = FindNodeById(Graph, Conn.NodeId);

			if (Depth0Node && IsPureNode(*Depth0Node))
			{
				// Mark depth-0 node as visited (it's already shown inline)
				VisitedNodes.Add(Depth0Node->NodeId);

				// Now show the chain starting from depth-0's inputs (depth-1 nodes)
				Output += FormatPureNodeChain(Graph, *Depth0Node, VisitedNodes, IndentLevel);
			}
		}
	}

	return Output;
}

FString FHumanReadableExporter::FormatVariable(const FExportedVariable& Variable)
{
	FString Output = TEXT("- ") + Variable.VariableName + TEXT(": ");
	Output += FormatPinType(Variable.VariableType);

	if (!Variable.DefaultValue.IsEmpty())
	{
		Output += TEXT(" = ") + Variable.DefaultValue;
	}

	// Flags
	TArray<FString> Flags;
	if (Variable.Flags.bInstanceEditable) Flags.Add(TEXT("Instance Editable"));
	if (Variable.Flags.bBlueprintReadOnly) Flags.Add(TEXT("Read Only"));
	if (Variable.Flags.bReplicated) Flags.Add(TEXT("Replicated"));
	if (Variable.Flags.bExposeOnSpawn) Flags.Add(TEXT("Expose on Spawn"));

	if (Flags.Num() > 0)
	{
		Output += TEXT(" [") + FString::Join(Flags, TEXT(", ")) + TEXT("]");
	}

	return Output;
}

FString FHumanReadableExporter::FormatFunctionSignature(const FExportedFunction& Function)
{
	FString Output;

	// Function indicator
	if (Function.Flags.bPure)
	{
		Output += TEXT("* "); // Pure function
	}
	else
	{
		Output += TEXT("@ "); // Impure function
	}

	Output += Function.FunctionName;

	// Parameters
	Output += TEXT("(");
	for (int32 i = 0; i < Function.Inputs.Num(); ++i)
	{
		if (i > 0) Output += TEXT(", ");
		Output += Function.Inputs[i].ParamName + TEXT(": ") + FormatPinType(Function.Inputs[i].ParamType);
	}
	Output += TEXT(")");

	// Return type
	if (Function.Outputs.Num() > 0)
	{
		Output += TEXT(" -> ");
		if (Function.Outputs.Num() == 1)
		{
			Output += FormatPinType(Function.Outputs[0].ParamType);
		}
		else
		{
			Output += TEXT("(");
			for (int32 i = 0; i < Function.Outputs.Num(); ++i)
			{
				if (i > 0) Output += TEXT(", ");
				Output += Function.Outputs[i].ParamName + TEXT(": ") + FormatPinType(Function.Outputs[i].ParamType);
			}
			Output += TEXT(")");
		}
	}

	if (Function.Flags.bPure)
	{
		Output += TEXT(" [Pure]");
	}

	return Output;
}

FString FHumanReadableExporter::FormatComponentHierarchy(const TArray<FExportedComponent>& Components, int32 IndentLevel)
{
	FString Output;

	for (const FExportedComponent& Component : Components)
	{
		Output += FormatComponent(Component, IndentLevel);

		if (Component.ChildComponents.Num() > 0)
		{
			Output += FormatComponentHierarchy(Component.ChildComponents, IndentLevel + 1);
		}
	}

	return Output;
}

FString FHumanReadableExporter::FormatComponent(const FExportedComponent& Component, int32 IndentLevel)
{
	FString Output;

	// Tree characters
	FString TreePrefix;
	for (int32 i = 0; i < IndentLevel; ++i)
	{
		TreePrefix += (i == IndentLevel - 1) ? TEXT("+-- ") : TEXT("|   ");
	}

	// Component name and class
	FString ClassName = GetClassLeafName(Component.ComponentClass);
	Output += TreePrefix + Component.ComponentName + TEXT(" (") + ClassName + TEXT(")\n");

	// Non-default component properties. Instanced-subobject properties (e.g.
	// AIPerceptionComponent::SenseConfigs) surface their parsed nested values here
	// instead of the opaque ExportTextItem_Direct blob — the .txt is the de facto
	// LLM-consumption surface, so T1's structured data must be legible here, not just
	// in the .json.
	if (Component.Properties.Num() > 0)
	{
		FString PropIndent;
		for (int32 i = 0; i < IndentLevel; ++i)
		{
			PropIndent += TEXT("    ");
		}
		PropIndent += TEXT("  ");

		for (const FExportedComponentProperty& Property : Component.Properties)
		{
			Output += FormatComponentProperty(Property, PropIndent);
		}
	}

	return Output;
}

FString FHumanReadableExporter::FormatComponentProperty(const FExportedComponentProperty& Property, const FString& IndentStr)
{
	const FString TypeStr = Property.PropertyType.IsEmpty() ? FString(TEXT("?")) : Property.PropertyType;
	FString Output = IndentStr + TEXT("- ") + Property.PropertyName + TEXT(": ") + TypeStr;

	if (Property.bIsInstancedSubobject)
	{
		Output += TEXT(" [instanced]");
		if (Property.SubobjectJsonValues.Num() == 0)
		{
			Output += TEXT(" (none)\n");
			return Output;
		}
		Output += TEXT("\n");
		const FString SubIndent = IndentStr + TEXT("    ");
		for (const TSharedPtr<FJsonValue>& SubobjectValue : Property.SubobjectJsonValues)
		{
			Output += FormatInstancedSubobject(SubobjectValue, SubIndent);
		}
		return Output;
	}

	if (!Property.Value.IsEmpty())
	{
		Output += TEXT(" = ") + Property.Value;
	}
	Output += TEXT("\n");
	return Output;
}

FString FHumanReadableExporter::FormatInstancedSubobject(const TSharedPtr<FJsonValue>& SubobjectValue, const FString& IndentStr, int32 Depth)
{
	if (Depth >= MAX_RENDER_RECURSION_DEPTH)
	{
		return IndentStr + TEXT("<render-cap reached>\n");
	}

	if (!SubobjectValue.IsValid())
	{
		return IndentStr + TEXT("<null subobject>\n");
	}

	TSharedPtr<FJsonObject> SubobjectObj = SubobjectValue->AsObject();
	if (!SubobjectObj.IsValid())
	{
		// JSON null element — serializer emits these for null array slots.
		return IndentStr + TEXT("<null subobject>\n");
	}

	FString Header;

	// Index prefix: arrayIndex (numeric) or mapKey (string); at most one applies.
	double ArrayIndex = -1.0;
	if (SubobjectObj->TryGetNumberField(TEXT("arrayIndex"), ArrayIndex))
	{
		Header += FString::Printf(TEXT("[%d] "), static_cast<int32>(ArrayIndex));
	}
	else
	{
		FString MapKey;
		if (SubobjectObj->TryGetStringField(TEXT("mapKey"), MapKey))
		{
			Header += TEXT("[\"") + MapKey + TEXT("\"] ");
		}
	}

	FString ClassPath;
	SubobjectObj->TryGetStringField(TEXT("classPath"), ClassPath);
	const FString ClassName = ClassPath.IsEmpty() ? FString(TEXT("?")) : GetClassLeafName(ClassPath);
	Header += ClassName;

	FString ObjectName;
	if (SubobjectObj->TryGetStringField(TEXT("objectName"), ObjectName) && !ObjectName.IsEmpty())
	{
		Header += TEXT(" (") + ObjectName + TEXT(")");
	}

	// Diagnostic markers — preserved verbatim so readers don't mistake a
	// truncated / cycle-broken subobject for a fully captured one.
	bool bTruncated = false;
	if (SubobjectObj->TryGetBoolField(TEXT("bTruncated"), bTruncated) && bTruncated)
	{
		Header += TEXT(" [truncated]");
	}

	bool bCycleDetected = false;
	if (SubobjectObj->TryGetBoolField(TEXT("bCycleDetected"), bCycleDetected) && bCycleDetected)
	{
		Header += TEXT(" [cycle]");
	}

	bool bHasBrokenReference = false;
	if (SubobjectObj->TryGetBoolField(TEXT("bHasBrokenReference"), bHasBrokenReference) && bHasBrokenReference)
	{
		FString BrokenInfo;
		SubobjectObj->TryGetStringField(TEXT("brokenReferenceInfo"), BrokenInfo);
		Header += BrokenInfo.IsEmpty()
			? FString(TEXT(" [broken]"))
			: (TEXT(" [broken: ") + BrokenInfo + TEXT("]"));
	}

	FString Output = IndentStr + Header + TEXT("\n");

	const TArray<TSharedPtr<FJsonValue>>* PropsArray = nullptr;
	if (SubobjectObj->TryGetArrayField(TEXT("properties"), PropsArray) && PropsArray)
	{
		const FString NestedIndent = IndentStr + TEXT("    ");
		for (const TSharedPtr<FJsonValue>& PropValue : *PropsArray)
		{
			Output += FormatNestedInstancedProperty(PropValue, NestedIndent, Depth + 1);
		}
	}

	return Output;
}

FString FHumanReadableExporter::FormatNestedInstancedProperty(const TSharedPtr<FJsonValue>& PropertyValue, const FString& IndentStr, int32 Depth)
{
	if (Depth >= MAX_RENDER_RECURSION_DEPTH)
	{
		return IndentStr + TEXT("<render-cap reached>\n");
	}

	if (!PropertyValue.IsValid())
	{
		return IndentStr + TEXT("<invalid property>\n");
	}

	TSharedPtr<FJsonObject> PropObj = PropertyValue->AsObject();
	if (!PropObj.IsValid())
	{
		return IndentStr + TEXT("<invalid property>\n");
	}

	FString PropName;
	PropObj->TryGetStringField(TEXT("propertyName"), PropName);
	if (PropName.IsEmpty())
	{
		PropName = TEXT("?");
	}

	FString PropType;
	PropObj->TryGetStringField(TEXT("propertyType"), PropType);
	const FString TypeStr = PropType.IsEmpty() ? FString(TEXT("?")) : PropType;

	bool bIsInstanced = false;
	PropObj->TryGetBoolField(TEXT("bIsInstancedSubobject"), bIsInstanced);

	FString Output = IndentStr + TEXT("- ") + PropName + TEXT(": ") + TypeStr;

	if (bIsInstanced)
	{
		Output += TEXT(" [instanced]");
		const TArray<TSharedPtr<FJsonValue>>* Nested = nullptr;
		if (PropObj->TryGetArrayField(TEXT("subobjects"), Nested) && Nested && Nested->Num() > 0)
		{
			Output += TEXT("\n");
			const FString NestedIndent = IndentStr + TEXT("    ");
			for (const TSharedPtr<FJsonValue>& SubValue : *Nested)
			{
				Output += FormatInstancedSubobject(SubValue, NestedIndent, Depth + 1);
			}
			return Output;
		}
		Output += TEXT(" (none)\n");
		return Output;
	}

	FString PropValueStr;
	PropObj->TryGetStringField(TEXT("value"), PropValueStr);
	if (!PropValueStr.IsEmpty())
	{
		Output += TEXT(" = ") + PropValueStr;
	}
	Output += TEXT("\n");
	return Output;
}

FString FHumanReadableExporter::FormatPinType(const FExportedPinType& PinType)
{
	FString TypeStr = PinType.Category;

	// Handle common types
	if (TypeStr == TEXT("bool"))
	{
		TypeStr = TEXT("Boolean");
	}
	else if (TypeStr == TEXT("float"))
	{
		TypeStr = TEXT("Float");
	}
	else if (TypeStr == TEXT("int"))
	{
		TypeStr = TEXT("Integer");
	}
	else if (TypeStr == TEXT("string"))
	{
		TypeStr = TEXT("String");
	}
	else if (TypeStr == TEXT("object") && !PinType.SubCategoryObject.IsEmpty())
	{
		TypeStr = GetClassLeafName(PinType.SubCategoryObject);
	}
	else if (TypeStr == TEXT("struct") && !PinType.SubCategoryObject.IsEmpty())
	{
		TypeStr = GetClassLeafName(PinType.SubCategoryObject);
	}

	// Container types
	if (PinType.bIsArray)
	{
		TypeStr = TEXT("Array<") + TypeStr + TEXT(">");
	}
	else if (PinType.bIsSet)
	{
		TypeStr = TEXT("Set<") + TypeStr + TEXT(">");
	}
	else if (PinType.bIsMap)
	{
		FString ValueType = PinType.ValueTerminalType.IsEmpty() ? TEXT("?") : PinType.ValueTerminalType;
		TypeStr = TEXT("Map<") + TypeStr + TEXT(", ") + ValueType + TEXT(">");
	}

	if (PinType.bIsReference)
	{
		TypeStr += TEXT("&");
	}

	return TypeStr;
}

FString FHumanReadableExporter::Indent(int32 Level)
{
	FString Result;
	for (int32 i = 0; i < Level; ++i)
	{
		Result += TEXT("    ");
	}
	return Result;
}

bool FHumanReadableExporter::SaveToFile(const FExportedBlueprint& ExportedData, const FString& OutputPath)
{
	FString TextContent = ExportToText(ExportedData);
	return FFileHelper::SaveStringToFile(TextContent, *OutputPath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
}

TSharedPtr<FJsonObject> FHumanReadableExporter::GenerateDigest(const FExportedBlueprint& ExportedData)
{
	TSharedPtr<FJsonObject> Digest = MakeShareable(new FJsonObject());

	// Basic info
	Digest->SetStringField(TEXT("assetPath"), ExportedData.AssetPath);
	Digest->SetStringField(TEXT("assetName"), ExportedData.AssetName);
	Digest->SetStringField(TEXT("parentClass"), ExportedData.ParentClass.ClassPath);

	if (!ExportedData.BlueprintSubclass.IsEmpty())
	{
		Digest->SetStringField(TEXT("blueprintSubclass"), ExportedData.BlueprintSubclass);
	}

	// Counts
	int32 TotalNodes = 0;
	TotalNodes += ExportedData.EventGraph.Nodes.Num();
	TotalNodes += ExportedData.ConstructionScript.Nodes.Num();
	for (const FExportedFunction& Func : ExportedData.Functions)
	{
		TotalNodes += Func.Graph.Nodes.Num();
	}
	for (const FExportedFunction& Macro : ExportedData.Macros)
	{
		TotalNodes += Macro.Graph.Nodes.Num();
	}

	Digest->SetNumberField(TEXT("totalNodes"), TotalNodes);
	Digest->SetNumberField(TEXT("variableCount"), ExportedData.Variables.Num());
	Digest->SetNumberField(TEXT("functionCount"), ExportedData.Functions.Num());
	Digest->SetNumberField(TEXT("macroCount"), ExportedData.Macros.Num());
	Digest->SetNumberField(TEXT("componentCount"), ExportedData.Components.Num());
	Digest->SetNumberField(TEXT("dependencyCount"), ExportedData.Dependencies.Num());

	// Node type breakdown
	TMap<FString, int32> NodeCounts = CountNodesByType(ExportedData);
	TSharedPtr<FJsonObject> NodeTypesObj = MakeShareable(new FJsonObject());
	for (const auto& Pair : NodeCounts)
	{
		NodeTypesObj->SetNumberField(Pair.Key, Pair.Value);
	}
	Digest->SetObjectField(TEXT("nodesByType"), NodeTypesObj);

	// Complexity metrics
	int32 CyclomaticComplexity, NestingDepth;
	CalculateComplexityMetrics(ExportedData, CyclomaticComplexity, NestingDepth);
	Digest->SetNumberField(TEXT("cyclomaticComplexity"), CyclomaticComplexity);
	Digest->SetNumberField(TEXT("maxNestingDepth"), NestingDepth);

	// Function summaries
	TArray<TSharedPtr<FJsonValue>> FunctionSummaries;
	for (const FExportedFunction& Func : ExportedData.Functions)
	{
		TSharedPtr<FJsonObject> FuncObj = MakeShareable(new FJsonObject());
		FuncObj->SetStringField(TEXT("name"), Func.FunctionName);
		FuncObj->SetNumberField(TEXT("inputCount"), Func.Inputs.Num());
		FuncObj->SetNumberField(TEXT("outputCount"), Func.Outputs.Num());
		FuncObj->SetNumberField(TEXT("nodeCount"), Func.Graph.Nodes.Num());
		FuncObj->SetBoolField(TEXT("isPure"), Func.Flags.bPure);
		FunctionSummaries.Add(MakeShareable(new FJsonValueObject(FuncObj)));
	}
	Digest->SetArrayField(TEXT("functions"), FunctionSummaries);

	// Variable summaries
	TArray<TSharedPtr<FJsonValue>> VariableSummaries;
	for (const FExportedVariable& Var : ExportedData.Variables)
	{
		TSharedPtr<FJsonObject> VarObj = MakeShareable(new FJsonObject());
		VarObj->SetStringField(TEXT("name"), Var.VariableName);
		VarObj->SetStringField(TEXT("type"), FormatPinType(Var.VariableType));
		VarObj->SetBoolField(TEXT("instanceEditable"), Var.Flags.bInstanceEditable);
		VarObj->SetBoolField(TEXT("replicated"), Var.Flags.bReplicated);
		VariableSummaries.Add(MakeShareable(new FJsonValueObject(VarObj)));
	}
	Digest->SetArrayField(TEXT("variables"), VariableSummaries);

	// Coverage counts — matches the .txt "COVERAGE:" header so automated consumers
	// can gate decisions on whether an export is trustworthy.
	const FExportCoverageStats Stats = ComputeCoverage(ExportedData);
	TSharedPtr<FJsonObject> Coverage = MakeShareable(new FJsonObject());
	Coverage->SetNumberField(TEXT("componentCount"), Stats.ComponentCount);
	Coverage->SetNumberField(TEXT("componentPropertyCount"), Stats.ComponentPropertyCount);
	Coverage->SetNumberField(TEXT("instancedSubobjectProperties"), Stats.InstancedProperties);
	Coverage->SetNumberField(TEXT("subobjectInstancesParsed"), Stats.SubobjectInstancesParsed);
	Coverage->SetNumberField(TEXT("subobjectInstancesBroken"), Stats.SubobjectInstancesBroken);
	Coverage->SetNumberField(TEXT("subobjectInstancesTruncated"), Stats.SubobjectInstancesTruncated);
	Coverage->SetNumberField(TEXT("subobjectInstancesCycles"), Stats.SubobjectInstancesCycles);
	Digest->SetObjectField(TEXT("coverage"), Coverage);

	return Digest;
}

bool FHumanReadableExporter::SaveDigestToFile(const FExportedBlueprint& ExportedData, const FString& OutputPath)
{
	TSharedPtr<FJsonObject> Digest = GenerateDigest(ExportedData);

	FString JsonString;
	TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> Writer =
		TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&JsonString);

	if (!FJsonSerializer::Serialize(Digest.ToSharedRef(), Writer))
	{
		return false;
	}

	return FFileHelper::SaveStringToFile(JsonString, *OutputPath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
}

TMap<FString, int32> FHumanReadableExporter::CountNodesByType(const FExportedBlueprint& ExportedData)
{
	TMap<FString, int32> Counts;

	auto CountInGraph = [&Counts](const FExportedGraph& Graph)
	{
		for (const FExportedNode& Node : Graph.Nodes)
		{
			int32& Count = Counts.FindOrAdd(Node.NodeType);
			Count++;
		}
	};

	CountInGraph(ExportedData.EventGraph);
	CountInGraph(ExportedData.ConstructionScript);

	for (const FExportedFunction& Func : ExportedData.Functions)
	{
		CountInGraph(Func.Graph);
	}

	for (const FExportedFunction& Macro : ExportedData.Macros)
	{
		CountInGraph(Macro.Graph);
	}

	return Counts;
}

void FHumanReadableExporter::CalculateComplexityMetrics(const FExportedBlueprint& ExportedData, int32& OutCyclomaticComplexity, int32& OutNestingDepth)
{
	// Cyclomatic complexity = number of decision points + 1
	OutCyclomaticComplexity = 1;
	OutNestingDepth = 0;

	auto AnalyzeGraph = [&OutCyclomaticComplexity](const FExportedGraph& Graph)
	{
		for (const FExportedNode& Node : Graph.Nodes)
		{
			// Count branch points
			if (Node.NodeType == TEXT("Branch") ||
				Node.NodeTitle.Contains(TEXT("Switch")) ||
				Node.NodeTitle.Contains(TEXT("Select")))
			{
				// Count output exec pins for decision nodes
				int32 ExecOutputs = 0;
				for (const FExportedPin& Pin : Node.Pins)
				{
					if (Pin.Direction == EExportPinDirection::Output &&
						Pin.PinType.Category == TEXT("exec"))
					{
						ExecOutputs++;
					}
				}
				OutCyclomaticComplexity += FMath::Max(0, ExecOutputs - 1);
			}
		}
	};

	AnalyzeGraph(ExportedData.EventGraph);
	AnalyzeGraph(ExportedData.ConstructionScript);

	for (const FExportedFunction& Func : ExportedData.Functions)
	{
		AnalyzeGraph(Func.Graph);
	}

	// Nesting depth would require full graph traversal - simplified for now
	OutNestingDepth = 0;
}

// ============================================================================
// State Tree Export
// ============================================================================

FString FHumanReadableExporter::ExportStateTreeToText(const FExportedStateTree& ExportedData)
{
	FString Output;

	// Header
	Output += FString::Printf(TEXT("STATE TREE: %s\n"), *ExportedData.AssetName);
	Output += FString::Printf(TEXT("Path: %s\n"), *ExportedData.AssetPath);
	if (!ExportedData.Schema.IsEmpty())
	{
		Output += FString::Printf(TEXT("Schema: %s\n"), *ExportedData.Schema);
	}
	Output += TEXT("\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\n");

	// Evaluators
	if (ExportedData.Evaluators.Num() > 0)
	{
		Output += TEXT("\nEVALUATORS:\n");
		for (const FExportedStateTreeEditorNode& Eval : ExportedData.Evaluators)
		{
			Output += Indent(1) + FormatEditorNode(Eval) + TEXT("\n");
		}
	}

	// Global tasks
	if (ExportedData.GlobalTasks.Num() > 0)
	{
		Output += TEXT("\nGLOBAL TASKS:\n");
		for (const FExportedStateTreeEditorNode& Task : ExportedData.GlobalTasks)
		{
			Output += Indent(1) + FormatEditorNode(Task) + TEXT("\n");
		}
	}

	// States
	if (ExportedData.RootStates.Num() > 0)
	{
		Output += TEXT("\nSTATES:\n");
		Output += FormatStateHierarchy(ExportedData.RootStates, 1);
	}

	// Bindings
	if (ExportedData.Bindings.Num() > 0)
	{
		Output += TEXT("\nBINDINGS:\n");
		for (const FExportedStateTreeBinding& Binding : ExportedData.Bindings)
		{
			Output += Indent(1) + Binding.SourcePath + TEXT(" -> ") + Binding.TargetPath + TEXT("\n");
		}
	}

	// Dependencies
	if (ExportedData.Dependencies.Num() > 0)
	{
		Output += TEXT("\nDEPENDENCIES:\n");
		for (const FExportedDependency& Dep : ExportedData.Dependencies)
		{
			FString TypeStr = Dep.bIsNativeClass ? TEXT("Native") : (Dep.bIsBlueprint ? TEXT("Blueprint") : TEXT("Asset"));
			Output += FString::Printf(TEXT("    - [%s] %s\n"), *TypeStr, *Dep.AssetPath);
		}
	}

	return Output;
}

FString FHumanReadableExporter::FormatStateHierarchy(const TArray<FExportedStateTreeState>& States, int32 IndentLevel)
{
	FString Output;

	for (const FExportedStateTreeState& State : States)
	{
		Output += FormatState(State, IndentLevel);
	}

	return Output;
}

FString FHumanReadableExporter::FormatState(const FExportedStateTreeState& State, int32 IndentLevel)
{
	FString Output;
	FString Prefix = Indent(IndentLevel);

	// State name and type
	FString TypeStr;
	switch (State.Type)
	{
	case EExportedStateTreeStateType::State: TypeStr = TEXT("State"); break;
	case EExportedStateTreeStateType::Group: TypeStr = TEXT("Group"); break;
	case EExportedStateTreeStateType::Linked: TypeStr = TEXT("Linked"); break;
	case EExportedStateTreeStateType::Subtree: TypeStr = TEXT("Subtree"); break;
	default: TypeStr = TEXT("Unknown"); break;
	}

	Output += Prefix + State.Name + TEXT(" [") + TypeStr + TEXT("]");

	// Tag
	if (!State.Tag.IsEmpty())
	{
		Output += TEXT(" Tag=") + State.Tag;
	}

	// Linked asset
	if (!State.LinkedAsset.IsEmpty())
	{
		Output += TEXT(" -> ") + State.LinkedAsset;
	}

	Output += TEXT("\n");

	// Enter conditions
	if (State.EnterConditions.Num() > 0)
	{
		Output += Prefix + TEXT("  Enter Conditions:\n");
		for (const FExportedStateTreeEditorNode& Condition : State.EnterConditions)
		{
			Output += Prefix + TEXT("    ") + FormatEditorNode(Condition) + TEXT("\n");
		}
	}

	// Tasks
	if (State.Tasks.Num() > 0)
	{
		Output += Prefix + TEXT("  Tasks:\n");
		for (const FExportedStateTreeEditorNode& Task : State.Tasks)
		{
			Output += Prefix + TEXT("    ") + FormatEditorNode(Task) + TEXT("\n");
		}
	}

	// Transitions
	if (State.Transitions.Num() > 0)
	{
		Output += Prefix + TEXT("  Transitions:\n");
		for (const FExportedStateTreeTransition& Transition : State.Transitions)
		{
			Output += Prefix + TEXT("    ") + FormatTransition(Transition) + TEXT("\n");
		}
	}

	// Children (recursive)
	if (State.Children.Num() > 0)
	{
		Output += Prefix + TEXT("  Children:\n");
		Output += FormatStateHierarchy(State.Children, IndentLevel + 1);
	}

	return Output;
}

FString FHumanReadableExporter::FormatEditorNode(const FExportedStateTreeEditorNode& Node)
{
	FString Output = TEXT("[") + Node.Name + TEXT("]");

	// Show key properties inline (skip very long values)
	TArray<FString> PropStrings;
	for (const FExportedStateTreeProperty& Prop : Node.Properties)
	{
		if (Prop.Value.IsEmpty() || Prop.Value == TEXT("None") || Prop.Value == TEXT("()"))
		{
			continue;
		}
		// Skip overly long values for readability
		if (Prop.Value.Len() > 80)
		{
			PropStrings.Add(Prop.Name + TEXT("=<...>"));
		}
		else
		{
			PropStrings.Add(Prop.Name + TEXT("=") + Prop.Value);
		}
	}

	if (PropStrings.Num() > 0)
	{
		Output += TEXT(" ") + FString::Join(PropStrings, TEXT(", "));
	}

	return Output;
}

FString FHumanReadableExporter::FormatTransition(const FExportedStateTreeTransition& Transition)
{
	FString Output = TEXT("\u2192 ") + Transition.TargetStateName;

	// Trigger
	FString TriggerStr;
	switch (Transition.Trigger)
	{
	case EExportedStateTreeTransitionTrigger::OnStateCompleted: TriggerStr = TEXT("OnStateCompleted"); break;
	case EExportedStateTreeTransitionTrigger::OnStateSucceeded: TriggerStr = TEXT("OnStateSucceeded"); break;
	case EExportedStateTreeTransitionTrigger::OnStateFailed: TriggerStr = TEXT("OnStateFailed"); break;
	case EExportedStateTreeTransitionTrigger::OnTick: TriggerStr = TEXT("OnTick"); break;
	case EExportedStateTreeTransitionTrigger::OnEvent: TriggerStr = TEXT("OnEvent"); break;
	default: TriggerStr = TEXT("Unknown"); break;
	}

	Output += TEXT(" [") + TriggerStr + TEXT("]");

	// Event tag
	if (!Transition.EventTag.IsEmpty())
	{
		Output += TEXT(" Event=") + Transition.EventTag;
	}

	// Delay
	if (Transition.DelaySeconds > 0.0f)
	{
		Output += FString::Printf(TEXT(" Delay=%.1fs"), Transition.DelaySeconds);
	}

	// Conditions count
	if (Transition.Conditions.Num() > 0)
	{
		Output += FString::Printf(TEXT(" (%d conditions)"), Transition.Conditions.Num());
	}

	return Output;
}

bool FHumanReadableExporter::SaveStateTreeToFile(const FExportedStateTree& ExportedData, const FString& OutputPath)
{
	FString TextContent = ExportStateTreeToText(ExportedData);
	return FFileHelper::SaveStringToFile(TextContent, *OutputPath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
}

TSharedPtr<FJsonObject> FHumanReadableExporter::GenerateStateTreeDigest(const FExportedStateTree& ExportedData)
{
	TSharedPtr<FJsonObject> Digest = MakeShareable(new FJsonObject());

	// Basic info
	Digest->SetStringField(TEXT("assetPath"), ExportedData.AssetPath);
	Digest->SetStringField(TEXT("assetName"), ExportedData.AssetName);
	Digest->SetStringField(TEXT("schema"), ExportedData.Schema);
	Digest->SetStringField(TEXT("assetType"), TEXT("StateTree"));

	// Counts
	int32 TotalStates = CountStatesRecursive(ExportedData.RootStates);
	Digest->SetNumberField(TEXT("totalStates"), TotalStates);
	Digest->SetNumberField(TEXT("evaluatorCount"), ExportedData.Evaluators.Num());
	Digest->SetNumberField(TEXT("globalTaskCount"), ExportedData.GlobalTasks.Num());
	Digest->SetNumberField(TEXT("rootStateCount"), ExportedData.RootStates.Num());
	Digest->SetNumberField(TEXT("bindingCount"), ExportedData.Bindings.Num());
	Digest->SetNumberField(TEXT("dependencyCount"), ExportedData.Dependencies.Num());

	// Root state summaries
	TArray<TSharedPtr<FJsonValue>> StateSummaries;
	for (const FExportedStateTreeState& State : ExportedData.RootStates)
	{
		TSharedPtr<FJsonObject> StateObj = MakeShareable(new FJsonObject());
		StateObj->SetStringField(TEXT("name"), State.Name);
		StateObj->SetNumberField(TEXT("taskCount"), State.Tasks.Num());
		StateObj->SetNumberField(TEXT("transitionCount"), State.Transitions.Num());
		StateObj->SetNumberField(TEXT("childCount"), State.Children.Num());
		if (!State.Tag.IsEmpty())
		{
			StateObj->SetStringField(TEXT("tag"), State.Tag);
		}
		StateSummaries.Add(MakeShareable(new FJsonValueObject(StateObj)));
	}
	Digest->SetArrayField(TEXT("rootStates"), StateSummaries);

	return Digest;
}

bool FHumanReadableExporter::SaveStateTreeDigestToFile(const FExportedStateTree& ExportedData, const FString& OutputPath)
{
	TSharedPtr<FJsonObject> Digest = GenerateStateTreeDigest(ExportedData);

	FString JsonString;
	TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> Writer =
		TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&JsonString);

	if (!FJsonSerializer::Serialize(Digest.ToSharedRef(), Writer))
	{
		return false;
	}

	return FFileHelper::SaveStringToFile(JsonString, *OutputPath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
}

int32 FHumanReadableExporter::CountStatesRecursive(const TArray<FExportedStateTreeState>& States)
{
	int32 Count = States.Num();
	for (const FExportedStateTreeState& State : States)
	{
		Count += CountStatesRecursive(State.Children);
	}
	return Count;
}
