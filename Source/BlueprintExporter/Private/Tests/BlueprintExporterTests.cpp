// Copyright Epic Games, Inc. All Rights Reserved.

#include "Misc/AutomationTest.h"
#include "Schema/BlueprintExportTypes.h"
#include "Serialization/BlueprintSerializer.h"
#include "TextExport/HumanReadableExporter.h"
#include "TextExport/DeepRenderShared.h"
#include "Tests/TestUFunctionFixtures.h"
#include "Engine/Blueprint.h"
#include "Serialization/JsonSerializer.h"
#include "Schema/StateTreeExportTypes.h"
#include "UObject/UnrealType.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBlueprintExportSchemaTest, "BlueprintExporter.Schema.JsonSerialization",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FBlueprintExportSchemaTest::RunTest(const FString& Parameters)
{
	// Test that exported data can be serialized and deserialized correctly

	// Create test exported Blueprint
	FExportedBlueprint TestBP;
	TestBP.AssetPath = TEXT("/Game/Test/BP_TestActor");
	TestBP.AssetName = TEXT("BP_TestActor");
	TestBP.BlueprintGuid = FGuid::NewGuid().ToString();
	TestBP.BlueprintType = EBlueprintExportType::Normal;

	TestBP.ParentClass.ClassName = TEXT("Actor");
	TestBP.ParentClass.ClassPath = TEXT("/Script/Engine.Actor");
	TestBP.ParentClass.bIsNative = true;

	// Add a test variable
	FExportedVariable TestVar;
	TestVar.VariableName = TEXT("Health");
	TestVar.VariableGuid = FGuid::NewGuid().ToString();
	TestVar.VariableType.Category = TEXT("float");
	TestVar.DefaultValue = TEXT("100.0");
	TestVar.Flags.bInstanceEditable = true;
	TestBP.Variables.Add(TestVar);

	// Add a test function
	FExportedFunction TestFunc;
	TestFunc.FunctionName = TEXT("TakeDamage");
	TestFunc.FunctionGuid = FGuid::NewGuid().ToString();
	TestFunc.Flags.bPure = false;

	FExportedFunctionParam DamageParam;
	DamageParam.ParamName = TEXT("DamageAmount");
	DamageParam.ParamType.Category = TEXT("float");
	TestFunc.Inputs.Add(DamageParam);

	TestBP.Functions.Add(TestFunc);

	// Add test node to event graph
	FExportedNode TestNode;
	TestNode.NodeId = TEXT("Event_BeginPlay_0_0_1");
	TestNode.NodeGuid = FGuid::NewGuid().ToString();
	TestNode.NodeClass = TEXT("/Script/BlueprintGraph.K2Node_Event");
	TestNode.NodeTitle = TEXT("Event BeginPlay");
	TestNode.NodeType = TEXT("Event");
	TestNode.PositionX = 100;
	TestNode.PositionY = 200;

	FExportedPin ExecPin;
	ExecPin.PinId = TEXT("Out_execute");
	ExecPin.PinName = TEXT("execute");
	ExecPin.Direction = EExportPinDirection::Output;
	ExecPin.PinType.Category = TEXT("exec");
	TestNode.Pins.Add(ExecPin);

	TestBP.EventGraph.GraphName = TEXT("EventGraph");
	TestBP.EventGraph.GraphGuid = FGuid::NewGuid().ToString();
	TestBP.EventGraph.Nodes.Add(TestNode);

	// Set export info
	TestBP.ExportInfo.SchemaVersion = BLUEPRINT_EXPORT_SCHEMA_VERSION;
	TestBP.ExportInfo.EngineVersion = TEXT("5.3.0");
	TestBP.ExportInfo.PluginVersion = TEXT("1.0.0");
	TestBP.ExportInfo.ExportTimestamp = FDateTime::UtcNow().ToIso8601();
	TestBP.ExportInfo.ContentHash = TestBP.ComputeContentHash();

	// Serialize to JSON
	TSharedPtr<FJsonObject> JsonObject = TestBP.ToJson();
	TestTrue(TEXT("JSON object is valid"), JsonObject.IsValid());

	// Convert to string
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	bool bSerializeSuccess = FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	TestTrue(TEXT("JSON serialization successful"), bSerializeSuccess);
	TestTrue(TEXT("JSON string is not empty"), !JsonString.IsEmpty());

	// Parse back
	TSharedPtr<FJsonObject> ParsedJson;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	bool bParseSuccess = FJsonSerializer::Deserialize(Reader, ParsedJson);
	TestTrue(TEXT("JSON parsing successful"), bParseSuccess);
	TestTrue(TEXT("Parsed JSON is valid"), ParsedJson.IsValid());

	// Deserialize back to struct
	FExportedBlueprint DeserializedBP = FExportedBlueprint::FromJson(ParsedJson);

	// Verify data
	TestEqual(TEXT("Asset path matches"), DeserializedBP.AssetPath, TestBP.AssetPath);
	TestEqual(TEXT("Asset name matches"), DeserializedBP.AssetName, TestBP.AssetName);
	TestEqual(TEXT("Blueprint type matches"), (int32)DeserializedBP.BlueprintType, (int32)TestBP.BlueprintType);
	TestEqual(TEXT("Parent class matches"), DeserializedBP.ParentClass.ClassPath, TestBP.ParentClass.ClassPath);
	TestEqual(TEXT("Variable count matches"), DeserializedBP.Variables.Num(), TestBP.Variables.Num());
	TestEqual(TEXT("Function count matches"), DeserializedBP.Functions.Num(), TestBP.Functions.Num());
	TestEqual(TEXT("Event graph node count matches"), DeserializedBP.EventGraph.Nodes.Num(), TestBP.EventGraph.Nodes.Num());

	// Verify variable details
	if (DeserializedBP.Variables.Num() > 0)
	{
		TestEqual(TEXT("Variable name matches"), DeserializedBP.Variables[0].VariableName, TestBP.Variables[0].VariableName);
		TestEqual(TEXT("Variable type matches"), DeserializedBP.Variables[0].VariableType.Category, TestBP.Variables[0].VariableType.Category);
		TestEqual(TEXT("Variable default matches"), DeserializedBP.Variables[0].DefaultValue, TestBP.Variables[0].DefaultValue);
	}

	// Verify function details
	if (DeserializedBP.Functions.Num() > 0)
	{
		TestEqual(TEXT("Function name matches"), DeserializedBP.Functions[0].FunctionName, TestBP.Functions[0].FunctionName);
		TestEqual(TEXT("Function input count matches"), DeserializedBP.Functions[0].Inputs.Num(), TestBP.Functions[0].Inputs.Num());
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBlueprintExportHumanReadableTest, "BlueprintExporter.TextExport.HumanReadable",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FBlueprintExportHumanReadableTest::RunTest(const FString& Parameters)
{
	// Test human-readable export generation

	FExportedBlueprint TestBP;
	TestBP.AssetPath = TEXT("/Game/Test/BP_TestActor");
	TestBP.AssetName = TEXT("BP_TestActor");
	TestBP.BlueprintType = EBlueprintExportType::Normal;

	TestBP.ParentClass.ClassName = TEXT("Actor");
	TestBP.ParentClass.bIsNative = true;

	// Add variable
	FExportedVariable Var;
	Var.VariableName = TEXT("PlayerHealth");
	Var.VariableType.Category = TEXT("float");
	Var.DefaultValue = TEXT("100.0");
	Var.Flags.bInstanceEditable = true;
	TestBP.Variables.Add(Var);

	// Add function
	FExportedFunction Func;
	Func.FunctionName = TEXT("GetHealthPercent");
	Func.Flags.bPure = true;

	FExportedFunctionParam ReturnParam;
	ReturnParam.ParamName = TEXT("ReturnValue");
	ReturnParam.ParamType.Category = TEXT("float");
	ReturnParam.bIsOutput = true;
	Func.Outputs.Add(ReturnParam);

	TestBP.Functions.Add(Func);

	// Generate text export
	FHumanReadableExporter TextExporter;
	FString TextOutput = TextExporter.ExportToText(TestBP);

	// Verify output
	TestTrue(TEXT("Text output is not empty"), !TextOutput.IsEmpty());
	TestTrue(TEXT("Contains Blueprint name"), TextOutput.Contains(TEXT("BP_TestActor")));
	TestTrue(TEXT("Contains VARIABLES section"), TextOutput.Contains(TEXT("VARIABLES")));
	TestTrue(TEXT("Contains variable name"), TextOutput.Contains(TEXT("PlayerHealth")));
	TestTrue(TEXT("Contains FUNCTIONS section"), TextOutput.Contains(TEXT("FUNCTIONS")));
	TestTrue(TEXT("Contains function name"), TextOutput.Contains(TEXT("GetHealthPercent")));
	TestTrue(TEXT("Contains Pure marker"), TextOutput.Contains(TEXT("Pure")));

	// Test digest generation
	TSharedPtr<FJsonObject> Digest = TextExporter.GenerateDigest(TestBP);
	TestTrue(TEXT("Digest is valid"), Digest.IsValid());
	TestTrue(TEXT("Digest has variableCount"), Digest->HasField(TEXT("variableCount")));
	TestTrue(TEXT("Digest has functionCount"), Digest->HasField(TEXT("functionCount")));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBlueprintExportManifestTest, "BlueprintExporter.Schema.ManifestSerialization",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FBlueprintExportManifestTest::RunTest(const FString& Parameters)
{
	// Test manifest serialization

	FExportManifest Manifest;
	Manifest.SchemaVersion = BLUEPRINT_EXPORT_SCHEMA_VERSION;
	Manifest.EngineVersion = TEXT("5.3.0");
	Manifest.PluginVersion = TEXT("1.0.0");
	Manifest.ExportTimestamp = FDateTime::UtcNow().ToIso8601();

	// Add entries
	FExportManifestEntry Entry1;
	Entry1.AssetPath = TEXT("/Game/Test/BP_Actor1");
	Entry1.AssetName = TEXT("BP_Actor1");
	Entry1.ExportFileName = TEXT("BP_Actor1.json");
	Entry1.ContentHash = TEXT("abc123");
	Entry1.NodeCount = 50;
	Entry1.FunctionCount = 5;
	Entry1.ComplexityScore = 75.5f;
	Manifest.Entries.Add(Entry1);

	FExportManifestEntry Entry2;
	Entry2.AssetPath = TEXT("/Game/Test/BP_Actor2");
	Entry2.AssetName = TEXT("BP_Actor2");
	Entry2.ExportFileName = TEXT("BP_Actor2.json");
	Entry2.ContentHash = TEXT("def456");
	Entry2.NodeCount = 100;
	Entry2.FunctionCount = 10;
	Entry2.ComplexityScore = 150.0f;
	Manifest.Entries.Add(Entry2);

	// Config
	Manifest.ExportConfig.Add(TEXT("includeDependencies"), TEXT("true"));
	Manifest.ExportConfig.Add(TEXT("depth"), TEXT("2"));

	// Serialize
	TSharedPtr<FJsonObject> JsonObject = Manifest.ToJson();
	TestTrue(TEXT("Manifest JSON is valid"), JsonObject.IsValid());

	// Convert to string and back
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	TSharedPtr<FJsonObject> ParsedJson;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	FJsonSerializer::Deserialize(Reader, ParsedJson);

	// Deserialize
	FExportManifest LoadedManifest = FExportManifest::FromJson(ParsedJson);

	// Verify
	TestEqual(TEXT("Schema version matches"), LoadedManifest.SchemaVersion, Manifest.SchemaVersion);
	TestEqual(TEXT("Entry count matches"), LoadedManifest.Entries.Num(), Manifest.Entries.Num());
	TestEqual(TEXT("Config preserved"), LoadedManifest.ExportConfig[TEXT("includeDependencies")], TEXT("true"));

	if (LoadedManifest.Entries.Num() >= 2)
	{
		// Entries should be sorted by path
		TestTrue(TEXT("First entry has lower path"), LoadedManifest.Entries[0].AssetPath < LoadedManifest.Entries[1].AssetPath);
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FStateTreeExportHierarchyTest, "BlueprintExporter.StateTree.HierarchyExport",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FStateTreeExportHierarchyTest::RunTest(const FString& Parameters)
{
	// TEST-01: Verify ToJson() produces correct JSON for a 3-level state hierarchy
	// with State, Group, Linked, and Subtree types

	// Build leaf state (level 3)
	FExportedStateTreeState LeafState;
	LeafState.Name = TEXT("LeafState");
	LeafState.StateGuid = FGuid::NewGuid().ToString();
	LeafState.Type = EExportedStateTreeStateType::State;
	LeafState.SelectionBehavior = EExportedStateTreeSelectionBehavior::TryEnterState;
	LeafState.Tag = TEXT("AI.Combat.Idle");

	// Build child group (level 2) containing leaf
	FExportedStateTreeState ChildGroup;
	ChildGroup.Name = TEXT("ChildGroup");
	ChildGroup.StateGuid = FGuid::NewGuid().ToString();
	ChildGroup.Type = EExportedStateTreeStateType::Group;
	ChildGroup.SelectionBehavior = EExportedStateTreeSelectionBehavior::TrySelectChildrenInOrder;
	ChildGroup.Children.Add(LeafState);

	// Build linked child (level 2)
	FExportedStateTreeState LinkedChild;
	LinkedChild.Name = TEXT("LinkedChild");
	LinkedChild.StateGuid = FGuid::NewGuid().ToString();
	LinkedChild.Type = EExportedStateTreeStateType::Linked;
	LinkedChild.LinkedAsset = TEXT("/Game/AI/ST_LinkedBehavior");

	// Build root state (level 1) containing ChildGroup and LinkedChild
	FExportedStateTreeState RootState;
	RootState.Name = TEXT("Root");
	RootState.StateGuid = FGuid::NewGuid().ToString();
	RootState.Type = EExportedStateTreeStateType::Subtree;
	RootState.Children.Add(ChildGroup);
	RootState.Children.Add(LinkedChild);

	// Wrap in FExportedStateTree
	FExportedStateTree TestTree;
	TestTree.AssetPath = TEXT("/Game/AI/ST_TestTree");
	TestTree.AssetName = TEXT("ST_TestTree");
	TestTree.Schema = TEXT("StateTreeComponentSchema");
	TestTree.ExportInfo.SchemaVersion = BLUEPRINT_EXPORT_SCHEMA_VERSION;
	TestTree.ExportInfo.EngineVersion = TEXT("5.3.0");
	TestTree.ExportInfo.PluginVersion = TEXT("1.0.0");
	TestTree.ExportInfo.ExportTimestamp = FDateTime::UtcNow().ToIso8601();
	TestTree.ExportInfo.ContentHash = TEXT("testhash");
	TestTree.RootStates.Add(RootState);

	// Serialize to JSON
	TSharedPtr<FJsonObject> JsonObject = TestTree.ToJson();
	TestTrue(TEXT("JSON object is valid"), JsonObject.IsValid());

	// Verify top-level fields
	TestEqual(TEXT("assetName matches"), JsonObject->GetStringField(TEXT("assetName")), FString(TEXT("ST_TestTree")));
	TestEqual(TEXT("schema matches"), JsonObject->GetStringField(TEXT("schema")), FString(TEXT("StateTreeComponentSchema")));

	// Verify rootStates array
	const TArray<TSharedPtr<FJsonValue>>* RootStatesArray;
	TestTrue(TEXT("rootStates array exists"), JsonObject->TryGetArrayField(TEXT("rootStates"), RootStatesArray));
	TestEqual(TEXT("rootStates has 1 entry"), RootStatesArray->Num(), 1);

	// Verify root state
	TSharedPtr<FJsonObject> RootJson = (*RootStatesArray)[0]->AsObject();
	TestEqual(TEXT("Root name"), RootJson->GetStringField(TEXT("name")), FString(TEXT("Root")));
	TestEqual(TEXT("Root type"), RootJson->GetStringField(TEXT("type")), FString(TEXT("Subtree")));

	const TArray<TSharedPtr<FJsonValue>>* RootChildren;
	TestTrue(TEXT("Root children array exists"), RootJson->TryGetArrayField(TEXT("children"), RootChildren));
	TestEqual(TEXT("Root has 2 children"), RootChildren->Num(), 2);

	// Verify ChildGroup (first child, preserves author order)
	TSharedPtr<FJsonObject> ChildGroupJson = (*RootChildren)[0]->AsObject();
	TestEqual(TEXT("ChildGroup name"), ChildGroupJson->GetStringField(TEXT("name")), FString(TEXT("ChildGroup")));
	TestEqual(TEXT("ChildGroup type"), ChildGroupJson->GetStringField(TEXT("type")), FString(TEXT("Group")));

	const TArray<TSharedPtr<FJsonValue>>* GroupChildren;
	TestTrue(TEXT("ChildGroup children array exists"), ChildGroupJson->TryGetArrayField(TEXT("children"), GroupChildren));
	TestEqual(TEXT("ChildGroup has 1 child"), GroupChildren->Num(), 1);

	// Verify LeafState (nested inside ChildGroup)
	TSharedPtr<FJsonObject> LeafJson = (*GroupChildren)[0]->AsObject();
	TestEqual(TEXT("LeafState name"), LeafJson->GetStringField(TEXT("name")), FString(TEXT("LeafState")));
	TestEqual(TEXT("LeafState type"), LeafJson->GetStringField(TEXT("type")), FString(TEXT("State")));
	TestTrue(TEXT("LeafState has tag field"), LeafJson->HasField(TEXT("tag")));
	TestEqual(TEXT("LeafState tag value"), LeafJson->GetStringField(TEXT("tag")), FString(TEXT("AI.Combat.Idle")));

	// Verify LinkedChild (second child of root)
	TSharedPtr<FJsonObject> LinkedJson = (*RootChildren)[1]->AsObject();
	TestEqual(TEXT("LinkedChild type"), LinkedJson->GetStringField(TEXT("type")), FString(TEXT("Linked")));
	TestTrue(TEXT("LinkedChild has linkedAsset field"), LinkedJson->HasField(TEXT("linkedAsset")));
	TestEqual(TEXT("LinkedChild linkedAsset path"), LinkedJson->GetStringField(TEXT("linkedAsset")), FString(TEXT("/Game/AI/ST_LinkedBehavior")));

	// Round-trip: serialize to string, parse back, FromJson, verify
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	bool bSerializeSuccess = FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	TestTrue(TEXT("JSON serialization successful"), bSerializeSuccess);

	TSharedPtr<FJsonObject> ParsedJson;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	bool bParseSuccess = FJsonSerializer::Deserialize(Reader, ParsedJson);
	TestTrue(TEXT("JSON parsing successful"), bParseSuccess);

	FExportedStateTree Deserialized = FExportedStateTree::FromJson(ParsedJson);
	TestEqual(TEXT("Round-trip AssetName"), Deserialized.AssetName, TestTree.AssetName);
	TestEqual(TEXT("Round-trip RootStates count"), Deserialized.RootStates.Num(), TestTree.RootStates.Num());
	TestEqual(TEXT("Round-trip Root children count"), Deserialized.RootStates[0].Children.Num(), TestTree.RootStates[0].Children.Num());
	TestEqual(TEXT("Round-trip ChildGroup children count"), Deserialized.RootStates[0].Children[0].Children.Num(), TestTree.RootStates[0].Children[0].Children.Num());

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FStateTreeTransitionTest, "BlueprintExporter.StateTree.TransitionSerialization",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FStateTreeTransitionTest::RunTest(const FString& Parameters)
{
	// TEST-02: Verify ToJson() produces correct JSON for transitions with
	// multiple trigger types, conditions, priority, eventTag, and delay fields

	// Create a state to hold transitions
	FExportedStateTreeState TestState;
	TestState.Name = TEXT("CombatState");
	TestState.StateGuid = FGuid::NewGuid().ToString();
	TestState.Type = EExportedStateTreeStateType::State;

	// Transition1: OnStateCompleted, basic case with priority
	// TransitionId prefix "A_" ensures it sorts first
	FExportedStateTreeTransition Transition1;
	Transition1.TransitionId = TEXT("A_Trans_Completed");
	Transition1.Trigger = EExportedStateTreeTransitionTrigger::OnStateCompleted;
	Transition1.TargetStateName = TEXT("NextState");
	Transition1.TargetStateGuid = TEXT("11111111-1111-1111-1111-111111111111");
	Transition1.Priority = TEXT("Normal");

	// Transition2: OnEvent with eventTag, delay, conditions
	// TransitionId prefix "B_" ensures it sorts second
	FExportedStateTreeTransition Transition2;
	Transition2.TransitionId = TEXT("B_Trans_Event");
	Transition2.Trigger = EExportedStateTreeTransitionTrigger::OnEvent;
	Transition2.EventTag = TEXT("AI.Combat.Engaged");
	Transition2.TargetStateName = TEXT("EngageState");
	Transition2.TargetStateGuid = TEXT("22222222-2222-2222-2222-222222222222");
	Transition2.Priority = TEXT("Critical");
	Transition2.DelaySeconds = 1.5f;
	Transition2.bDelayIsRandom = true;
	Transition2.DelayRandomDeviationSeconds = 0.5f;

	FExportedStateTreeEditorNode Condition;
	Condition.Name = TEXT("StateTreeCompareIntCondition");
	Condition.StructType = TEXT("/Script/StateTreeModule.StateTreeCompareIntCondition");
	Condition.Category = TEXT("Condition");
	Transition2.Conditions.Add(Condition);

	// Transition3: OnTick, Low priority
	// TransitionId prefix "C_" ensures it sorts third
	FExportedStateTreeTransition Transition3;
	Transition3.TransitionId = TEXT("C_Trans_Tick");
	Transition3.Trigger = EExportedStateTreeTransitionTrigger::OnTick;
	Transition3.TargetStateName = TEXT("PatrolState");
	Transition3.TargetStateGuid = TEXT("33333333-3333-3333-3333-333333333333");
	Transition3.Priority = TEXT("Low");

	// Attach all 3 transitions to the state
	TestState.Transitions.Add(Transition1);
	TestState.Transitions.Add(Transition2);
	TestState.Transitions.Add(Transition3);

	// Serialize the state to JSON
	TSharedPtr<FJsonObject> StateJson = TestState.ToJson();
	TestTrue(TEXT("State JSON is valid"), StateJson.IsValid());

	// Verify transitions array
	const TArray<TSharedPtr<FJsonValue>>* TransitionsArray;
	TestTrue(TEXT("transitions array exists"), StateJson->TryGetArrayField(TEXT("transitions"), TransitionsArray));
	TestEqual(TEXT("transitions has 3 entries"), TransitionsArray->Num(), 3);

	// Transitions are sorted by TransitionId: A_ < B_ < C_
	// Transition1 (A_Trans_Completed) should be first
	TSharedPtr<FJsonObject> T1Json = (*TransitionsArray)[0]->AsObject();
	TestEqual(TEXT("T1 trigger"), T1Json->GetStringField(TEXT("trigger")), FString(TEXT("OnStateCompleted")));
	TestEqual(TEXT("T1 priority"), T1Json->GetStringField(TEXT("priority")), FString(TEXT("Normal")));
	TestEqual(TEXT("T1 targetStateName"), T1Json->GetStringField(TEXT("targetStateName")), FString(TEXT("NextState")));
	TestEqual(TEXT("T1 targetStateGuid"), T1Json->GetStringField(TEXT("targetStateGuid")), FString(TEXT("11111111-1111-1111-1111-111111111111")));
	TestFalse(TEXT("T1 no eventTag"), T1Json->HasField(TEXT("eventTag")));
	TestFalse(TEXT("T1 no delaySeconds"), T1Json->HasField(TEXT("delaySeconds")));

	// Transition2 (B_Trans_Event) should be second
	TSharedPtr<FJsonObject> T2Json = (*TransitionsArray)[1]->AsObject();
	TestEqual(TEXT("T2 trigger"), T2Json->GetStringField(TEXT("trigger")), FString(TEXT("OnEvent")));
	TestEqual(TEXT("T2 eventTag"), T2Json->GetStringField(TEXT("eventTag")), FString(TEXT("AI.Combat.Engaged")));
	TestEqual(TEXT("T2 priority"), T2Json->GetStringField(TEXT("priority")), FString(TEXT("Critical")));
	TestEqual(TEXT("T2 targetStateGuid"), T2Json->GetStringField(TEXT("targetStateGuid")), FString(TEXT("22222222-2222-2222-2222-222222222222")));
	TestTrue(TEXT("T2 has delaySeconds"), T2Json->HasField(TEXT("delaySeconds")));
	TestTrue(TEXT("T2 delaySeconds approx 1.5"), FMath::IsNearlyEqual(T2Json->GetNumberField(TEXT("delaySeconds")), 1.5, 0.01));
	TestEqual(TEXT("T2 delayIsRandom"), T2Json->GetBoolField(TEXT("delayIsRandom")), true);
	TestTrue(TEXT("T2 has delayRandomDeviationSeconds"), T2Json->HasField(TEXT("delayRandomDeviationSeconds")));
	TestTrue(TEXT("T2 delayRandomDeviation approx 0.5"), FMath::IsNearlyEqual(T2Json->GetNumberField(TEXT("delayRandomDeviationSeconds")), 0.5, 0.01));

	const TArray<TSharedPtr<FJsonValue>>* T2Conditions;
	TestTrue(TEXT("T2 conditions array exists"), T2Json->TryGetArrayField(TEXT("conditions"), T2Conditions));
	TestEqual(TEXT("T2 conditions has 1 entry"), T2Conditions->Num(), 1);
	TestEqual(TEXT("T2 condition name"), (*T2Conditions)[0]->AsObject()->GetStringField(TEXT("name")), FString(TEXT("StateTreeCompareIntCondition")));

	// Transition3 (C_Trans_Tick) should be third
	TSharedPtr<FJsonObject> T3Json = (*TransitionsArray)[2]->AsObject();
	TestEqual(TEXT("T3 trigger"), T3Json->GetStringField(TEXT("trigger")), FString(TEXT("OnTick")));
	TestEqual(TEXT("T3 priority"), T3Json->GetStringField(TEXT("priority")), FString(TEXT("Low")));
	TestEqual(TEXT("T3 targetStateGuid"), T3Json->GetStringField(TEXT("targetStateGuid")), FString(TEXT("33333333-3333-3333-3333-333333333333")));

	// Round-trip: serialize state to JSON string, parse, FromJson, verify
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	bool bSerializeSuccess = FJsonSerializer::Serialize(StateJson.ToSharedRef(), Writer);
	TestTrue(TEXT("JSON serialization successful"), bSerializeSuccess);

	TSharedPtr<FJsonObject> ParsedJson;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	bool bParseSuccess = FJsonSerializer::Deserialize(Reader, ParsedJson);
	TestTrue(TEXT("JSON parsing successful"), bParseSuccess);

	FExportedStateTreeState Deserialized = FExportedStateTreeState::FromJson(ParsedJson);
	TestEqual(TEXT("Round-trip transition count"), Deserialized.Transitions.Num(), 3);

	// Verify trigger types survived round-trip (transitions may be in any order after FromJson
	// since FromJson preserves JSON array order which was already sorted)
	TestEqual(TEXT("Round-trip T1 trigger"), Deserialized.Transitions[0].Trigger, EExportedStateTreeTransitionTrigger::OnStateCompleted);
	TestEqual(TEXT("Round-trip T1 priority"), Deserialized.Transitions[0].Priority, FString(TEXT("Normal")));
	TestEqual(TEXT("Round-trip T2 trigger"), Deserialized.Transitions[1].Trigger, EExportedStateTreeTransitionTrigger::OnEvent);
	TestEqual(TEXT("Round-trip T2 priority"), Deserialized.Transitions[1].Priority, FString(TEXT("Critical")));
	TestEqual(TEXT("Round-trip T3 trigger"), Deserialized.Transitions[2].Trigger, EExportedStateTreeTransitionTrigger::OnTick);
	TestEqual(TEXT("Round-trip T3 priority"), Deserialized.Transitions[2].Priority, FString(TEXT("Low")));

	// Verify targetStateGuid round-trip
	TestEqual(TEXT("Round-trip T1 targetStateGuid"), Deserialized.Transitions[0].TargetStateGuid, FString(TEXT("11111111-1111-1111-1111-111111111111")));
	TestEqual(TEXT("Round-trip T2 targetStateGuid"), Deserialized.Transitions[1].TargetStateGuid, FString(TEXT("22222222-2222-2222-2222-222222222222")));
	TestEqual(TEXT("Round-trip T3 targetStateGuid"), Deserialized.Transitions[2].TargetStateGuid, FString(TEXT("33333333-3333-3333-3333-333333333333")));

	// Backward compatibility: empty TargetStateGuid should NOT emit targetStateGuid field
	{
		FExportedStateTreeTransition BackCompatTransition;
		BackCompatTransition.TransitionId = TEXT("BackCompat_Trans");
		BackCompatTransition.Trigger = EExportedStateTreeTransitionTrigger::OnStateCompleted;
		BackCompatTransition.TargetStateName = TEXT("SomeState");
		// TargetStateGuid intentionally left empty

		TSharedPtr<FJsonObject> BackCompatJson = BackCompatTransition.ToJson();
		TestFalse(TEXT("BackCompat no targetStateGuid field"), BackCompatJson->HasField(TEXT("targetStateGuid")));

		// Deserialize old-format JSON (no targetStateGuid) and verify empty string
		FExportedStateTreeTransition BackCompatDeserialized = FExportedStateTreeTransition::FromJson(BackCompatJson);
		TestTrue(TEXT("BackCompat deserialized targetStateGuid is empty"), BackCompatDeserialized.TargetStateGuid.IsEmpty());
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FStateTreeTaskNodeTest, "BlueprintExporter.StateTree.TaskAndNodeSerialization",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FStateTreeTaskNodeTest::RunTest(const FString& Parameters)
{
	// TEST-03: Verify ToJson() produces correct JSON for editor nodes with
	// name, structType, category, and sorted properties

	// Create a state to hold tasks and enter conditions
	FExportedStateTreeState TestState;
	TestState.Name = TEXT("TaskTestState");
	TestState.StateGuid = FGuid::NewGuid().ToString();
	TestState.Type = EExportedStateTreeStateType::State;

	// Create a task node with properties in reverse alphabetical order
	FExportedStateTreeEditorNode TaskNode;
	TaskNode.Name = TEXT("StateTreeRunParallelTask");
	TaskNode.StructType = TEXT("/Script/StateTreeModule.StateTreeRunParallelTask");
	TaskNode.Category = TEXT("Task");
	TaskNode.InstanceId = FGuid::NewGuid().ToString();

	// Add properties in reverse alphabetical order to test sorting
	FExportedStateTreeProperty Prop1;
	Prop1.Name = TEXT("ZOrder");
	Prop1.Type = TEXT("int32");
	Prop1.Value = TEXT("5");
	Prop1.Category = TEXT("Config");
	TaskNode.Properties.Add(Prop1);

	FExportedStateTreeProperty Prop2;
	Prop2.Name = TEXT("AlphaParam");
	Prop2.Type = TEXT("float");
	Prop2.Value = TEXT("0.75");
	Prop2.Category = TEXT("Config");
	TaskNode.Properties.Add(Prop2);

	// Create an enter condition node
	FExportedStateTreeEditorNode ConditionNode;
	ConditionNode.Name = TEXT("StateTreeCompareIntCondition");
	ConditionNode.StructType = TEXT("/Script/StateTreeModule.StateTreeCompareIntCondition");
	ConditionNode.Category = TEXT("EnterCondition");

	// Property without Category to test conditional category field
	FExportedStateTreeProperty CondProp;
	CondProp.Name = TEXT("Threshold");
	CondProp.Type = TEXT("int32");
	CondProp.Value = TEXT("10");
	// No Category set - should be empty string by default
	ConditionNode.Properties.Add(CondProp);

	// Attach to state
	TestState.Tasks.Add(TaskNode);
	TestState.EnterConditions.Add(ConditionNode);

	// Serialize the state to JSON
	TSharedPtr<FJsonObject> StateJson = TestState.ToJson();
	TestTrue(TEXT("State JSON is valid"), StateJson.IsValid());

	// Verify tasks array
	const TArray<TSharedPtr<FJsonValue>>* TasksArray;
	TestTrue(TEXT("tasks array exists"), StateJson->TryGetArrayField(TEXT("tasks"), TasksArray));
	TestEqual(TEXT("tasks has 1 entry"), TasksArray->Num(), 1);

	TSharedPtr<FJsonObject> TaskJson = (*TasksArray)[0]->AsObject();
	TestEqual(TEXT("Task name"), TaskJson->GetStringField(TEXT("name")), FString(TEXT("StateTreeRunParallelTask")));
	TestEqual(TEXT("Task structType"), TaskJson->GetStringField(TEXT("structType")), FString(TEXT("/Script/StateTreeModule.StateTreeRunParallelTask")));
	TestEqual(TEXT("Task category"), TaskJson->GetStringField(TEXT("category")), FString(TEXT("Task")));
	TestTrue(TEXT("Task has instanceId"), TaskJson->HasField(TEXT("instanceId")));
	TestFalse(TEXT("Task instanceId is not empty"), TaskJson->GetStringField(TEXT("instanceId")).IsEmpty());

	// Verify properties are sorted alphabetically: AlphaParam before ZOrder
	const TArray<TSharedPtr<FJsonValue>>* PropsArray;
	TestTrue(TEXT("properties array exists"), TaskJson->TryGetArrayField(TEXT("properties"), PropsArray));
	TestEqual(TEXT("properties has 2 entries"), PropsArray->Num(), 2);

	TSharedPtr<FJsonObject> FirstProp = (*PropsArray)[0]->AsObject();
	TestEqual(TEXT("First property name is AlphaParam"), FirstProp->GetStringField(TEXT("name")), FString(TEXT("AlphaParam")));
	TestEqual(TEXT("AlphaParam type"), FirstProp->GetStringField(TEXT("type")), FString(TEXT("float")));
	TestEqual(TEXT("AlphaParam value"), FirstProp->GetStringField(TEXT("value")), FString(TEXT("0.75")));
	TestTrue(TEXT("AlphaParam has category field"), FirstProp->HasField(TEXT("category")));
	TestEqual(TEXT("AlphaParam category"), FirstProp->GetStringField(TEXT("category")), FString(TEXT("Config")));

	TSharedPtr<FJsonObject> SecondProp = (*PropsArray)[1]->AsObject();
	TestEqual(TEXT("Second property name is ZOrder"), SecondProp->GetStringField(TEXT("name")), FString(TEXT("ZOrder")));
	TestEqual(TEXT("ZOrder type"), SecondProp->GetStringField(TEXT("type")), FString(TEXT("int32")));
	TestEqual(TEXT("ZOrder value"), SecondProp->GetStringField(TEXT("value")), FString(TEXT("5")));

	// Verify enter conditions array
	const TArray<TSharedPtr<FJsonValue>>* EnterConditionsArray;
	TestTrue(TEXT("enterConditions array exists"), StateJson->TryGetArrayField(TEXT("enterConditions"), EnterConditionsArray));
	TestEqual(TEXT("enterConditions has 1 entry"), EnterConditionsArray->Num(), 1);

	TSharedPtr<FJsonObject> CondJson = (*EnterConditionsArray)[0]->AsObject();
	TestEqual(TEXT("Condition name"), CondJson->GetStringField(TEXT("name")), FString(TEXT("StateTreeCompareIntCondition")));
	TestEqual(TEXT("Condition category"), CondJson->GetStringField(TEXT("category")), FString(TEXT("EnterCondition")));

	// Verify condition property without Category does NOT have category field
	const TArray<TSharedPtr<FJsonValue>>* CondPropsArray;
	TestTrue(TEXT("condition properties array exists"), CondJson->TryGetArrayField(TEXT("properties"), CondPropsArray));
	TestEqual(TEXT("condition properties has 1 entry"), CondPropsArray->Num(), 1);

	TSharedPtr<FJsonObject> ThresholdProp = (*CondPropsArray)[0]->AsObject();
	TestEqual(TEXT("Threshold name"), ThresholdProp->GetStringField(TEXT("name")), FString(TEXT("Threshold")));
	TestFalse(TEXT("Threshold has no category field"), ThresholdProp->HasField(TEXT("category")));

	// Round-trip: serialize state to JSON string, parse, FromJson, verify
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	bool bSerializeSuccess = FJsonSerializer::Serialize(StateJson.ToSharedRef(), Writer);
	TestTrue(TEXT("JSON serialization successful"), bSerializeSuccess);

	TSharedPtr<FJsonObject> ParsedJson;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	bool bParseSuccess = FJsonSerializer::Deserialize(Reader, ParsedJson);
	TestTrue(TEXT("JSON parsing successful"), bParseSuccess);

	FExportedStateTreeState Deserialized = FExportedStateTreeState::FromJson(ParsedJson);
	TestEqual(TEXT("Round-trip task count"), Deserialized.Tasks.Num(), 1);
	TestEqual(TEXT("Round-trip enter condition count"), Deserialized.EnterConditions.Num(), 1);
	TestEqual(TEXT("Round-trip task name"), Deserialized.Tasks[0].Name, FString(TEXT("StateTreeRunParallelTask")));
	TestEqual(TEXT("Round-trip task property count"), Deserialized.Tasks[0].Properties.Num(), 2);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FStateTreeBindingsTest, "BlueprintExporter.StateTree.PropertyBindings",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FStateTreeBindingsTest::RunTest(const FString& Parameters)
{
	// TEST-04: Verify ToJson() produces correct JSON for property bindings
	// with sourcePath and targetPath, sorted by targetPath

	// Create FExportedStateTree with bindings in non-alphabetical targetPath order
	FExportedStateTree TestTree;
	TestTree.AssetPath = TEXT("/Game/AI/ST_BindingsTest");
	TestTree.AssetName = TEXT("ST_BindingsTest");
	TestTree.Schema = TEXT("StateTreeComponentSchema");
	TestTree.ExportInfo.SchemaVersion = BLUEPRINT_EXPORT_SCHEMA_VERSION;
	TestTree.ExportInfo.EngineVersion = TEXT("5.3.0");
	TestTree.ExportInfo.PluginVersion = TEXT("1.0.0");
	TestTree.ExportInfo.ExportTimestamp = FDateTime::UtcNow().ToIso8601();
	TestTree.ExportInfo.ContentHash = TEXT("bindingtesthash");

	// Add bindings in non-alphabetical targetPath order to test sorting
	FExportedStateTreeBinding Binding1;
	Binding1.SourcePath = TEXT("Context.Actor.Location");
	Binding1.TargetPath = TEXT("Task.MoveToTarget.TargetLocation");

	FExportedStateTreeBinding Binding3;
	Binding3.SourcePath = TEXT("Context.Actor.Rotation");
	Binding3.TargetPath = TEXT("Task.MoveToTarget.TargetRotation");

	FExportedStateTreeBinding Binding2;
	Binding2.SourcePath = TEXT("Evaluator.DistanceCheck.Distance");
	Binding2.TargetPath = TEXT("Condition.RangeCheck.Value");

	// Add in order: Binding1, Binding3, Binding2 (to test sorting)
	TestTree.Bindings.Add(Binding1);
	TestTree.Bindings.Add(Binding3);
	TestTree.Bindings.Add(Binding2);

	// Serialize to JSON
	TSharedPtr<FJsonObject> JsonObject = TestTree.ToJson();
	TestTrue(TEXT("JSON object is valid"), JsonObject.IsValid());

	// Verify bindings array
	const TArray<TSharedPtr<FJsonValue>>* BindingsArray;
	TestTrue(TEXT("bindings array exists"), JsonObject->TryGetArrayField(TEXT("bindings"), BindingsArray));
	TestEqual(TEXT("bindings has 3 entries"), BindingsArray->Num(), 3);

	// Verify bindings are sorted by targetPath alphabetically:
	// 1. "Condition.RangeCheck.Value" (Binding2)
	// 2. "Task.MoveToTarget.TargetLocation" (Binding1)
	// 3. "Task.MoveToTarget.TargetRotation" (Binding3)

	TSharedPtr<FJsonObject> B1Json = (*BindingsArray)[0]->AsObject();
	TestEqual(TEXT("First binding targetPath"), B1Json->GetStringField(TEXT("targetPath")), FString(TEXT("Condition.RangeCheck.Value")));
	TestEqual(TEXT("First binding sourcePath"), B1Json->GetStringField(TEXT("sourcePath")), FString(TEXT("Evaluator.DistanceCheck.Distance")));

	TSharedPtr<FJsonObject> B2Json = (*BindingsArray)[1]->AsObject();
	TestEqual(TEXT("Second binding targetPath"), B2Json->GetStringField(TEXT("targetPath")), FString(TEXT("Task.MoveToTarget.TargetLocation")));
	TestEqual(TEXT("Second binding sourcePath"), B2Json->GetStringField(TEXT("sourcePath")), FString(TEXT("Context.Actor.Location")));

	TSharedPtr<FJsonObject> B3Json = (*BindingsArray)[2]->AsObject();
	TestEqual(TEXT("Third binding targetPath"), B3Json->GetStringField(TEXT("targetPath")), FString(TEXT("Task.MoveToTarget.TargetRotation")));
	TestEqual(TEXT("Third binding sourcePath"), B3Json->GetStringField(TEXT("sourcePath")), FString(TEXT("Context.Actor.Rotation")));

	// Round-trip: serialize to string, parse, FromJson, verify
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	bool bSerializeSuccess = FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	TestTrue(TEXT("JSON serialization successful"), bSerializeSuccess);

	TSharedPtr<FJsonObject> ParsedJson;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	bool bParseSuccess = FJsonSerializer::Deserialize(Reader, ParsedJson);
	TestTrue(TEXT("JSON parsing successful"), bParseSuccess);

	FExportedStateTree Deserialized = FExportedStateTree::FromJson(ParsedJson);
	TestEqual(TEXT("Round-trip binding count"), Deserialized.Bindings.Num(), 3);
	// Verify paths survived round-trip (order in FromJson matches JSON array order)
	TestEqual(TEXT("Round-trip first binding targetPath"), Deserialized.Bindings[0].TargetPath, FString(TEXT("Condition.RangeCheck.Value")));
	TestEqual(TEXT("Round-trip second binding targetPath"), Deserialized.Bindings[1].TargetPath, FString(TEXT("Task.MoveToTarget.TargetLocation")));
	TestEqual(TEXT("Round-trip third binding targetPath"), Deserialized.Bindings[2].TargetPath, FString(TEXT("Task.MoveToTarget.TargetRotation")));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBlueprintSubclassTest, "BlueprintExporter.Schema.BlueprintSubclassSerialization",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FBlueprintSubclassTest::RunTest(const FString& Parameters)
{
	// Test 1: BlueprintSubclass round-trips through FExportedBlueprint ToJson/FromJson
	{
		FExportedBlueprint Original;
		Original.AssetPath = TEXT("/Game/Test/BP_TestAnim");
		Original.AssetName = TEXT("BP_TestAnim");
		Original.BlueprintType = EBlueprintExportType::Normal;
		Original.BlueprintSubclass = TEXT("AnimBlueprint");

		TSharedPtr<FJsonObject> Json = Original.ToJson();

		// Verify JSON has the field
		TestTrue(TEXT("JSON has blueprintSubclass field"), Json->HasField(TEXT("blueprintSubclass")));
		TestEqual(TEXT("blueprintSubclass value in JSON"), Json->GetStringField(TEXT("blueprintSubclass")), TEXT("AnimBlueprint"));

		// Verify existing blueprintType is still present and unchanged
		TestTrue(TEXT("JSON still has blueprintType field"), Json->HasField(TEXT("blueprintType")));
		TestEqual(TEXT("blueprintType value in JSON"), Json->GetStringField(TEXT("blueprintType")), TEXT("Normal"));

		// Round-trip through FromJson
		FExportedBlueprint Restored = FExportedBlueprint::FromJson(Json);
		TestEqual(TEXT("BlueprintSubclass round-trips"), Restored.BlueprintSubclass, TEXT("AnimBlueprint"));
		TestEqual(TEXT("BlueprintType preserved"), (int32)Restored.BlueprintType, (int32)EBlueprintExportType::Normal);
	}

	// Test 2: Different subclass values
	{
		FExportedBlueprint WidgetBP;
		WidgetBP.BlueprintSubclass = TEXT("WidgetBlueprint");
		TSharedPtr<FJsonObject> Json = WidgetBP.ToJson();
		FExportedBlueprint Restored = FExportedBlueprint::FromJson(Json);
		TestEqual(TEXT("WidgetBlueprint round-trips"), Restored.BlueprintSubclass, TEXT("WidgetBlueprint"));
	}

	{
		FExportedBlueprint ControlRigBP;
		ControlRigBP.BlueprintSubclass = TEXT("ControlRigBlueprint");
		TSharedPtr<FJsonObject> Json = ControlRigBP.ToJson();
		FExportedBlueprint Restored = FExportedBlueprint::FromJson(Json);
		TestEqual(TEXT("ControlRigBlueprint round-trips"), Restored.BlueprintSubclass, TEXT("ControlRigBlueprint"));
	}

	{
		FExportedBlueprint VanillaBP;
		VanillaBP.BlueprintSubclass = TEXT("Blueprint");
		TSharedPtr<FJsonObject> Json = VanillaBP.ToJson();
		FExportedBlueprint Restored = FExportedBlueprint::FromJson(Json);
		TestEqual(TEXT("Standard Blueprint round-trips"), Restored.BlueprintSubclass, TEXT("Blueprint"));
	}

	// Test 3: Backward compatibility -- JSON without blueprintSubclass field
	{
		TSharedPtr<FJsonObject> OldJson = MakeShareable(new FJsonObject());
		OldJson->SetStringField(TEXT("assetPath"), TEXT("/Game/Test/BP_Old"));
		OldJson->SetStringField(TEXT("assetName"), TEXT("BP_Old"));
		OldJson->SetStringField(TEXT("blueprintType"), TEXT("Normal"));
		// No blueprintSubclass field -- simulating pre-v1.8 export

		FExportedBlueprint Restored = FExportedBlueprint::FromJson(OldJson);
		TestTrue(TEXT("Missing field gives empty string"), Restored.BlueprintSubclass.IsEmpty());
	}

	// Test 4: BlueprintSubclass in FExportManifestEntry
	{
		FExportManifestEntry Entry;
		Entry.AssetPath = TEXT("/Game/Test/BP_TestWidget");
		Entry.AssetName = TEXT("BP_TestWidget");
		Entry.ExportFileName = TEXT("BP_TestWidget.json");
		Entry.ContentHash = TEXT("abc123");
		Entry.AssetType = TEXT("Blueprint");
		Entry.BlueprintSubclass = TEXT("WidgetBlueprint");
		Entry.NodeCount = 10;
		Entry.FunctionCount = 2;
		Entry.ComplexityScore = 5.0f;

		TSharedPtr<FJsonObject> Json = Entry.ToJson();
		TestTrue(TEXT("Manifest has blueprintSubclass"), Json->HasField(TEXT("blueprintSubclass")));
		TestEqual(TEXT("Manifest blueprintSubclass value"), Json->GetStringField(TEXT("blueprintSubclass")), TEXT("WidgetBlueprint"));

		FExportManifestEntry Restored = FExportManifestEntry::FromJson(Json);
		TestEqual(TEXT("Manifest BlueprintSubclass round-trips"), Restored.BlueprintSubclass, TEXT("WidgetBlueprint"));
	}

	// Test 5: Manifest entry with empty BlueprintSubclass (non-Blueprint asset) omits field
	{
		FExportManifestEntry StateTreeEntry;
		StateTreeEntry.AssetPath = TEXT("/Game/AI/ST_Test");
		StateTreeEntry.AssetName = TEXT("ST_Test");
		StateTreeEntry.ExportFileName = TEXT("ST_Test.statetree.json");
		StateTreeEntry.ContentHash = TEXT("def456");
		StateTreeEntry.AssetType = TEXT("StateTree");
		// BlueprintSubclass is empty for non-Blueprint assets

		TSharedPtr<FJsonObject> Json = StateTreeEntry.ToJson();
		TestFalse(TEXT("StateTree manifest omits blueprintSubclass"), Json->HasField(TEXT("blueprintSubclass")));
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInterfaceOverrideSerializationTest,
	"BlueprintExporter.Schema.InterfaceOverrideSerialization",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FInterfaceOverrideSerializationTest::RunTest(const FString& Parameters)
{
	// M26.1.1 — `FExportedFunction` gained `bIsInterfaceOverride` +
	// `InterfaceClassPath` so the serializer can surface override graphs
	// stored on `Blueprint->ImplementedInterfaces[].Graphs`. This test
	// pins the JSON shape: (a) round-trips both fields when the function
	// is an override, (b) confirms both fields are omitted from the JSON
	// for regular member functions so non-override assets stay
	// byte-identical to pre-M26.1.1, (c) confirms `FromJson` tolerates
	// absence defensively.

	// Override case — both fields populated, both round-trip.
	{
		FExportedFunction Func;
		Func.FunctionName = TEXT("GetTargetingInfo");
		Func.FunctionGuid = FGuid::NewGuid().ToString();
		Func.Category = TEXT("Interface");
		Func.bIsInterfaceOverride = true;
		Func.InterfaceClassPath = TEXT("/Game/CombatPrototype/DrewPrototype/BPI_Targetable.BPI_Targetable");

		TSharedPtr<FJsonObject> Json = Func.ToJson();
		TestTrue(TEXT("Override JSON has isInterfaceOverride"), Json->HasField(TEXT("isInterfaceOverride")));
		TestTrue(TEXT("Override isInterfaceOverride is true"), Json->GetBoolField(TEXT("isInterfaceOverride")));
		TestTrue(TEXT("Override JSON has interfaceClassPath"), Json->HasField(TEXT("interfaceClassPath")));
		TestEqual(TEXT("interfaceClassPath value"),
			Json->GetStringField(TEXT("interfaceClassPath")),
			Func.InterfaceClassPath);

		FExportedFunction Restored = FExportedFunction::FromJson(Json);
		TestTrue(TEXT("bIsInterfaceOverride round-trips"), Restored.bIsInterfaceOverride);
		TestEqual(TEXT("InterfaceClassPath round-trips"), Restored.InterfaceClassPath, Func.InterfaceClassPath);
		TestEqual(TEXT("FunctionName preserved"), Restored.FunctionName, Func.FunctionName);
	}

	// Regular-function case — both fields omitted from JSON to keep
	// non-override exports byte-identical to pre-M26.1.1.
	{
		FExportedFunction Func;
		Func.FunctionName = TEXT("TakeDamage");
		Func.FunctionGuid = FGuid::NewGuid().ToString();
		Func.Category = TEXT("Combat");
		// bIsInterfaceOverride stays default-false; InterfaceClassPath stays empty.

		TSharedPtr<FJsonObject> Json = Func.ToJson();
		TestFalse(TEXT("Regular function omits isInterfaceOverride"), Json->HasField(TEXT("isInterfaceOverride")));
		TestFalse(TEXT("Regular function omits interfaceClassPath"), Json->HasField(TEXT("interfaceClassPath")));

		FExportedFunction Restored = FExportedFunction::FromJson(Json);
		TestFalse(TEXT("bIsInterfaceOverride default round-trips as false"), Restored.bIsInterfaceOverride);
		TestTrue(TEXT("InterfaceClassPath default round-trips as empty"), Restored.InterfaceClassPath.IsEmpty());
	}

	// Backwards compatibility — pre-M26.1.1 JSON (no isInterfaceOverride
	// / interfaceClassPath) must still deserialize without errors.
	{
		TSharedPtr<FJsonObject> OldJson = MakeShareable(new FJsonObject());
		OldJson->SetStringField(TEXT("functionName"), TEXT("LegacyFunc"));
		OldJson->SetStringField(TEXT("functionGuid"), FGuid::NewGuid().ToString());
		OldJson->SetStringField(TEXT("category"), TEXT("Default"));
		// No isInterfaceOverride / interfaceClassPath — simulating pre-1.19.6 export.

		FExportedFunction Restored = FExportedFunction::FromJson(OldJson);
		TestEqual(TEXT("Legacy JSON preserves FunctionName"), Restored.FunctionName, FString(TEXT("LegacyFunc")));
		TestFalse(TEXT("Legacy JSON gives bIsInterfaceOverride=false"), Restored.bIsInterfaceOverride);
		TestTrue(TEXT("Legacy JSON gives empty InterfaceClassPath"), Restored.InterfaceClassPath.IsEmpty());
	}

	// Edge case — bIsInterfaceOverride=true with an empty class path
	// (interface object was unresolvable at serialize time). Emits the
	// bool but not the path.
	{
		FExportedFunction Func;
		Func.FunctionName = TEXT("OrphanedOverride");
		Func.bIsInterfaceOverride = true;
		// InterfaceClassPath intentionally empty.

		TSharedPtr<FJsonObject> Json = Func.ToJson();
		TestTrue(TEXT("Empty-path override still emits isInterfaceOverride"), Json->HasField(TEXT("isInterfaceOverride")));
		TestFalse(TEXT("Empty-path override omits interfaceClassPath"), Json->HasField(TEXT("interfaceClassPath")));

		FExportedFunction Restored = FExportedFunction::FromJson(Json);
		TestTrue(TEXT("Orphan override bIsInterfaceOverride round-trips"), Restored.bIsInterfaceOverride);
		TestTrue(TEXT("Orphan override InterfaceClassPath stays empty"), Restored.InterfaceClassPath.IsEmpty());
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FStateTreeManifestTest, "BlueprintExporter.StateTree.ManifestIntegration",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FStateTreeManifestTest::RunTest(const FString& Parameters)
{
	// Create a manifest with both Blueprint and StateTree entries
	FExportManifest Manifest;
	Manifest.SchemaVersion = BLUEPRINT_EXPORT_SCHEMA_VERSION;
	Manifest.EngineVersion = TEXT("5.3.0");
	Manifest.PluginVersion = TEXT("1.28.6");
	Manifest.ExportTimestamp = TEXT("2026-03-04T00:00:00Z");

	// Blueprint entry
	FExportManifestEntry BPEntry;
	BPEntry.AssetPath = TEXT("/Game/Blueprints/BP_TestActor");
	BPEntry.AssetName = TEXT("BP_TestActor");
	BPEntry.ExportFileName = TEXT("BP_TestActor.json");
	BPEntry.AssetType = TEXT("Blueprint");
	BPEntry.BlueprintSubclass = TEXT("Blueprint");
	BPEntry.NodeCount = 10;
	Manifest.Entries.Add(BPEntry);

	// StateTree entry
	FExportManifestEntry STEntry;
	STEntry.AssetPath = TEXT("/Game/AI/ST_PatrolTree");
	STEntry.AssetName = TEXT("ST_PatrolTree");
	STEntry.ExportFileName = TEXT("ST_PatrolTree.statetree.json");
	STEntry.AssetType = TEXT("StateTree");
	STEntry.NodeCount = 5;
	Manifest.Entries.Add(STEntry);

	// Config with includeStateTrees
	Manifest.ExportConfig.Add(TEXT("includeStateTrees"), TEXT("true"));

	// Serialize to JSON
	TSharedPtr<FJsonObject> ManifestJson = Manifest.ToJson();
	TestTrue(TEXT("Manifest JSON valid"), ManifestJson.IsValid());

	// Verify entries array
	const TArray<TSharedPtr<FJsonValue>>* EntriesArray;
	TestTrue(TEXT("entries array exists"), ManifestJson->TryGetArrayField(TEXT("entries"), EntriesArray));
	TestEqual(TEXT("2 entries"), EntriesArray->Num(), 2);

	// FExportManifest::ToJson sorts entries by AssetPath for determinism, so the
	// serialized order is lexicographic on path — not insertion order. With paths
	// /Game/AI/ST_PatrolTree and /Game/Blueprints/BP_TestActor, "AI" < "Blueprints"
	// so the StateTree entry lands at index 0 and the Blueprint at index 1.
	TSharedPtr<FJsonObject> Entry0 = (*EntriesArray)[0]->AsObject();
	TestEqual(TEXT("Entry0 assetType (sorted: StateTree first)"), Entry0->GetStringField(TEXT("assetType")), FString(TEXT("StateTree")));
	TestEqual(TEXT("Entry0 assetName"), Entry0->GetStringField(TEXT("assetName")), FString(TEXT("ST_PatrolTree")));

	TSharedPtr<FJsonObject> Entry1 = (*EntriesArray)[1]->AsObject();
	TestEqual(TEXT("Entry1 assetType (sorted: Blueprint second)"), Entry1->GetStringField(TEXT("assetType")), FString(TEXT("Blueprint")));
	TestEqual(TEXT("Entry1 assetName"), Entry1->GetStringField(TEXT("assetName")), FString(TEXT("BP_TestActor")));

	// Verify config includes includeStateTrees
	const TSharedPtr<FJsonObject>* ConfigObj;
	TestTrue(TEXT("exportConfig exists"), ManifestJson->TryGetObjectField(TEXT("exportConfig"), ConfigObj));

	// Round-trip: serialize to string, parse, FromJson
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	bool bSerializeSuccess = FJsonSerializer::Serialize(ManifestJson.ToSharedRef(), Writer);
	TestTrue(TEXT("JSON serialization successful"), bSerializeSuccess);

	TSharedPtr<FJsonObject> ParsedJson;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	bool bParseSuccess = FJsonSerializer::Deserialize(Reader, ParsedJson);
	TestTrue(TEXT("JSON parsing successful"), bParseSuccess);

	// Same sort order survives the round-trip: StateTree at index 0, Blueprint at 1.
	FExportManifest Deserialized = FExportManifest::FromJson(ParsedJson);
	TestEqual(TEXT("Round-trip entry count"), Deserialized.Entries.Num(), 2);
	TestEqual(TEXT("Round-trip Entry0 assetType"), Deserialized.Entries[0].AssetType, FString(TEXT("StateTree")));
	TestEqual(TEXT("Round-trip Entry0 assetName"), Deserialized.Entries[0].AssetName, FString(TEXT("ST_PatrolTree")));
	TestEqual(TEXT("Round-trip Entry1 assetType"), Deserialized.Entries[1].AssetType, FString(TEXT("Blueprint")));
	TestEqual(TEXT("Round-trip Entry1 assetName"), Deserialized.Entries[1].AssetName, FString(TEXT("BP_TestActor")));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FStateMachineSchemaTest, "BlueprintExporter.Schema.StateMachineRoundTrip",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FStateMachineSchemaTest::RunTest(const FString& Parameters)
{
	// Test 1: FExportedTransitionBlendSettings round-trip
	{
		FExportedTransitionBlendSettings Original;
		Original.CrossfadeDuration = 0.25f;
		Original.BlendMode = TEXT("Linear");
		Original.CrossfadeMode = TEXT("BlendDuration");
		Original.LogicType = TEXT("StandardBlend");
		Original.PriorityOrder = 2;
		Original.bAutomaticRuleBasedOnSequencePlayer = true;

		TSharedPtr<FJsonObject> Json = Original.ToJson();

		FString JsonString;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
		bool bSerializeSuccess = FJsonSerializer::Serialize(Json.ToSharedRef(), Writer);
		TestTrue(TEXT("BlendSettings JSON serialization successful"), bSerializeSuccess);

		TSharedPtr<FJsonObject> ParsedJson;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
		bool bParseSuccess = FJsonSerializer::Deserialize(Reader, ParsedJson);
		TestTrue(TEXT("BlendSettings JSON parsing successful"), bParseSuccess);

		FExportedTransitionBlendSettings Restored = FExportedTransitionBlendSettings::FromJson(ParsedJson);
		TestEqual(TEXT("CrossfadeDuration round-trips"), Restored.CrossfadeDuration, 0.25f);
		TestEqual(TEXT("BlendMode round-trips"), Restored.BlendMode, FString(TEXT("Linear")));
		TestEqual(TEXT("CrossfadeMode round-trips"), Restored.CrossfadeMode, FString(TEXT("BlendDuration")));
		TestEqual(TEXT("LogicType round-trips"), Restored.LogicType, FString(TEXT("StandardBlend")));
		TestEqual(TEXT("PriorityOrder round-trips"), Restored.PriorityOrder, 2);
		TestTrue(TEXT("AutomaticRule round-trips"), Restored.bAutomaticRuleBasedOnSequencePlayer);
	}

	// Test 2: Full state machine round-trip with states and transitions
	{
		FExportedStateMachine Original;
		Original.MachineName = TEXT("State Controller");
		Original.MachineGuid = TEXT("TEST-GUID-SM");

		// State 1: IdleLoop with an AnimGraph containing one test node
		FExportedAnimState IdleState;
		IdleState.StateName = TEXT("IdleLoop");
		IdleState.StateGuid = TEXT("TEST-GUID-IDLE");
		IdleState.StateType = TEXT("State");
		IdleState.AnimGraph.GraphName = TEXT("AnimGraph");
		IdleState.AnimGraph.GraphType = TEXT("AnimGraph");
		FExportedNode TestNode;
		TestNode.NodeId = TEXT("Node_0");
		TestNode.NodeClass = TEXT("AnimGraphNode_SequencePlayer");
		TestNode.NodeTitle = TEXT("Play Idle_Anim");
		IdleState.AnimGraph.Nodes.Add(TestNode);
		Original.States.Add(IdleState);

		// State 2: LocomotionLoop
		FExportedAnimState LocoState;
		LocoState.StateName = TEXT("LocomotionLoop");
		LocoState.StateGuid = TEXT("TEST-GUID-LOCO");
		LocoState.StateType = TEXT("State");
		Original.States.Add(LocoState);

		// Transition: Idle -> Locomotion
		FExportedAnimTransition Trans;
		Trans.TransitionName = TEXT("IdleToLoco");
		Trans.TransitionGuid = TEXT("TEST-GUID-TRANS");
		Trans.SourceState = TEXT("IdleLoop");
		Trans.TargetState = TEXT("LocomotionLoop");
		Trans.BlendSettings.CrossfadeDuration = 0.2f;
		Trans.BlendSettings.BlendMode = TEXT("Linear");
		FExportedNode RuleNode;
		RuleNode.NodeId = TEXT("Rule_0");
		RuleNode.NodeClass = TEXT("AnimGraphNode_TransitionResult");
		Trans.RuleGraph.Nodes.Add(RuleNode);
		Original.Transitions.Add(Trans);

		TSharedPtr<FJsonObject> Json = Original.ToJson();

		FString JsonString;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
		bool bSerializeSuccess = FJsonSerializer::Serialize(Json.ToSharedRef(), Writer);
		TestTrue(TEXT("StateMachine JSON serialization successful"), bSerializeSuccess);

		TSharedPtr<FJsonObject> ParsedJson;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
		bool bParseSuccess = FJsonSerializer::Deserialize(Reader, ParsedJson);
		TestTrue(TEXT("StateMachine JSON parsing successful"), bParseSuccess);

		FExportedStateMachine Restored = FExportedStateMachine::FromJson(ParsedJson);
		TestEqual(TEXT("MachineName round-trips"), Restored.MachineName, FString(TEXT("State Controller")));
		TestEqual(TEXT("State count"), Restored.States.Num(), 2);
		// States are sorted by name: IdleLoop, LocomotionLoop
		TestEqual(TEXT("First state name"), Restored.States[0].StateName, FString(TEXT("IdleLoop")));
		TestEqual(TEXT("First state type"), Restored.States[0].StateType, FString(TEXT("State")));
		TestEqual(TEXT("Second state name"), Restored.States[1].StateName, FString(TEXT("LocomotionLoop")));
		TestEqual(TEXT("Transition count"), Restored.Transitions.Num(), 1);
		TestEqual(TEXT("Transition source"), Restored.Transitions[0].SourceState, FString(TEXT("IdleLoop")));
		TestEqual(TEXT("Transition target"), Restored.Transitions[0].TargetState, FString(TEXT("LocomotionLoop")));
		TestEqual(TEXT("Blend duration"), Restored.Transitions[0].BlendSettings.CrossfadeDuration, 0.2f);
		TestEqual(TEXT("AnimGraph node count"), Restored.States[0].AnimGraph.Nodes.Num(), 1);
	}

	// Test 3: Nested state machine round-trip (ANIM-06 requirement)
	{
		FExportedStateMachine Outer;
		Outer.MachineName = TEXT("OuterMachine");
		Outer.MachineGuid = TEXT("TEST-GUID-OUTER");

		// Outer state with a nested sub-state machine
		FExportedAnimState OuterState;
		OuterState.StateName = TEXT("ComplexState");
		OuterState.StateGuid = TEXT("TEST-GUID-COMPLEX");
		OuterState.StateType = TEXT("State");

		FExportedStateMachine SubMachine;
		SubMachine.MachineName = TEXT("SubStateMachine");
		SubMachine.MachineGuid = TEXT("TEST-GUID-SUB");
		FExportedAnimState SubState;
		SubState.StateName = TEXT("SubIdle");
		SubState.StateGuid = TEXT("TEST-GUID-SUB-IDLE");
		SubState.StateType = TEXT("State");
		SubMachine.States.Add(SubState);

		OuterState.NestedStateMachines.Add(SubMachine);
		Outer.States.Add(OuterState);

		TSharedPtr<FJsonObject> Json = Outer.ToJson();

		FString JsonString;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
		bool bSerializeSuccess = FJsonSerializer::Serialize(Json.ToSharedRef(), Writer);
		TestTrue(TEXT("Nested SM JSON serialization successful"), bSerializeSuccess);

		TSharedPtr<FJsonObject> ParsedJson;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
		bool bParseSuccess = FJsonSerializer::Deserialize(Reader, ParsedJson);
		TestTrue(TEXT("Nested SM JSON parsing successful"), bParseSuccess);

		FExportedStateMachine Restored = FExportedStateMachine::FromJson(ParsedJson);
		TestEqual(TEXT("Outer state count"), Restored.States.Num(), 1);
		TestEqual(TEXT("Nested SM count"), Restored.States[0].NestedStateMachines.Num(), 1);
		TestEqual(TEXT("Nested machine name"), Restored.States[0].NestedStateMachines[0].MachineName, FString(TEXT("SubStateMachine")));
		TestEqual(TEXT("Nested machine state count"), Restored.States[0].NestedStateMachines[0].States.Num(), 1);
		TestEqual(TEXT("Nested machine state name"), Restored.States[0].NestedStateMachines[0].States[0].StateName, FString(TEXT("SubIdle")));
	}

	// Test 4: FExportedBlueprint integration with StateMachines
	{
		FExportedBlueprint Original;
		Original.AssetPath = TEXT("/Game/Test/ABP_TestChar");
		Original.AssetName = TEXT("ABP_TestChar");
		Original.BlueprintType = EBlueprintExportType::Normal;
		Original.BlueprintSubclass = TEXT("AnimBlueprint");

		FExportedStateMachine Machine;
		Machine.MachineName = TEXT("Locomotion");
		Machine.MachineGuid = TEXT("TEST-GUID-LOCO-SM");
		FExportedAnimState State;
		State.StateName = TEXT("Idle");
		State.StateType = TEXT("State");
		Machine.States.Add(State);
		Original.StateMachines.Add(Machine);

		TSharedPtr<FJsonObject> Json = Original.ToJson();

		// Verify "stateMachines" field exists in JSON
		const TArray<TSharedPtr<FJsonValue>>* SMArray;
		TestTrue(TEXT("stateMachines array exists in Blueprint JSON"), Json->TryGetArrayField(TEXT("stateMachines"), SMArray));
		TestEqual(TEXT("stateMachines array has 1 entry"), SMArray->Num(), 1);

		FString JsonString;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
		bool bSerializeSuccess = FJsonSerializer::Serialize(Json.ToSharedRef(), Writer);
		TestTrue(TEXT("Blueprint+SM JSON serialization successful"), bSerializeSuccess);

		TSharedPtr<FJsonObject> ParsedJson;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
		bool bParseSuccess = FJsonSerializer::Deserialize(Reader, ParsedJson);
		TestTrue(TEXT("Blueprint+SM JSON parsing successful"), bParseSuccess);

		FExportedBlueprint Restored = FExportedBlueprint::FromJson(ParsedJson);
		TestEqual(TEXT("StateMachines count"), Restored.StateMachines.Num(), 1);
		TestEqual(TEXT("First machine name"), Restored.StateMachines[0].MachineName, FString(TEXT("Locomotion")));
		TestEqual(TEXT("First machine state count"), Restored.StateMachines[0].States.Num(), 1);
	}

	// Test 5: Backward compatibility -- missing "stateMachines" key
	{
		TSharedPtr<FJsonObject> OldJson = MakeShareable(new FJsonObject());
		OldJson->SetStringField(TEXT("assetPath"), TEXT("/Game/Test/BP_OldFormat"));
		OldJson->SetStringField(TEXT("assetName"), TEXT("BP_OldFormat"));
		OldJson->SetStringField(TEXT("blueprintType"), TEXT("Normal"));
		// No "stateMachines" key -- simulating pre-v1.8 export

		FExportedBlueprint Restored = FExportedBlueprint::FromJson(OldJson);
		TestEqual(TEXT("Missing stateMachines gives empty array"), Restored.StateMachines.Num(), 0);
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBlueprintExportInstancedSubobjectRoundTripTest,
	"BlueprintExporter.Schema.InstancedSubobjectRoundTrip",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

// Covers the T1 fix: structured instanced-subobject data attached to component
// properties must survive the ToJson / FromJson cycle intact so AI consumers see
// nested sense-config / attribute-set / anim-layer property values rather than the
// opaque ExportTextItem_Direct blob.
bool FBlueprintExportInstancedSubobjectRoundTripTest::RunTest(const FString& Parameters)
{
	// Build a fixture that mimics AIPerceptionComponent::SenseConfigs — an instanced
	// subobject array with two entries (sight + hearing), each carrying a nested
	// property list. The JSON shape matches what the serializer's runtime reflection
	// path emits for real UObjects.
	TSharedPtr<FJsonObject> SightObj = MakeShareable(new FJsonObject());
	SightObj->SetStringField(TEXT("classPath"), TEXT("/Script/AIModule.AISenseConfig_Sight"));
	SightObj->SetStringField(TEXT("objectName"), TEXT("AISenseConfig_Sight_0"));
	SightObj->SetNumberField(TEXT("arrayIndex"), 0);
	{
		TArray<TSharedPtr<FJsonValue>> SightProps;
		TSharedPtr<FJsonObject> Radius = MakeShareable(new FJsonObject());
		Radius->SetStringField(TEXT("propertyName"), TEXT("SightRadius"));
		Radius->SetStringField(TEXT("propertyType"), TEXT("float"));
		Radius->SetStringField(TEXT("value"), TEXT("3000.0"));
		SightProps.Add(MakeShareable(new FJsonValueObject(Radius)));
		SightObj->SetArrayField(TEXT("properties"), SightProps);
	}

	TSharedPtr<FJsonObject> HearingObj = MakeShareable(new FJsonObject());
	HearingObj->SetStringField(TEXT("classPath"), TEXT("/Script/AIModule.AISenseConfig_Hearing"));
	HearingObj->SetStringField(TEXT("objectName"), TEXT("AISenseConfig_Hearing_0"));
	HearingObj->SetNumberField(TEXT("arrayIndex"), 1);
	{
		TArray<TSharedPtr<FJsonValue>> HearingProps;
		TSharedPtr<FJsonObject> Range = MakeShareable(new FJsonObject());
		Range->SetStringField(TEXT("propertyName"), TEXT("HearingRange"));
		Range->SetStringField(TEXT("propertyType"), TEXT("float"));
		Range->SetStringField(TEXT("value"), TEXT("1500.0"));
		HearingProps.Add(MakeShareable(new FJsonValueObject(Range)));
		HearingObj->SetArrayField(TEXT("properties"), HearingProps);
	}

	FExportedComponentProperty Prop;
	Prop.PropertyName = TEXT("SenseConfigs");
	Prop.PropertyType = TEXT("TArray<UAISenseConfig*>");
	Prop.Value = TEXT("(Config[0]=/Script/AIModule.AISenseConfig_Sight'...',Config[1]=/Script/AIModule.AISenseConfig_Hearing'...')");
	Prop.bIsInstancedSubobject = true;
	Prop.SubobjectJsonValues.Add(MakeShareable(new FJsonValueObject(SightObj)));
	Prop.SubobjectJsonValues.Add(MakeShareable(new FJsonValueObject(HearingObj)));

	// Round-trip through JSON text so we exercise the tokenizer path, not just the
	// in-memory FJsonValue handoff — otherwise we'd miss escape / quoting bugs.
	TSharedPtr<FJsonObject> Json = Prop.ToJson();
	TestTrue(TEXT("ToJson returned a valid object"), Json.IsValid());
	TestTrue(TEXT("bIsInstancedSubobject flag is emitted"), Json->GetBoolField(TEXT("bIsInstancedSubobject")));
	const TArray<TSharedPtr<FJsonValue>>* SubArr = nullptr;
	TestTrue(TEXT("subobjects array is present"), Json->TryGetArrayField(TEXT("subobjects"), SubArr));
	TestEqual(TEXT("two subobject entries emitted"), SubArr->Num(), 2);

	FString JsonText;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonText);
	TestTrue(TEXT("Serialize to text"), FJsonSerializer::Serialize(Json.ToSharedRef(), Writer));

	TSharedPtr<FJsonObject> Parsed;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonText);
	TestTrue(TEXT("Parse back from text"), FJsonSerializer::Deserialize(Reader, Parsed));

	FExportedComponentProperty Restored = FExportedComponentProperty::FromJson(Parsed);
	TestEqual(TEXT("PropertyName round-trips"), Restored.PropertyName, Prop.PropertyName);
	TestEqual(TEXT("PropertyType round-trips"), Restored.PropertyType, Prop.PropertyType);
	TestEqual(TEXT("Value round-trips"), Restored.Value, Prop.Value);
	TestTrue(TEXT("bIsInstancedSubobject round-trips"), Restored.bIsInstancedSubobject);
	TestEqual(TEXT("SubobjectJsonValues preserves count"), Restored.SubobjectJsonValues.Num(), 2);

	// Inspect the first subobject's nested properties to confirm nested JSON survived.
	TSharedPtr<FJsonObject> RestoredSight = Restored.SubobjectJsonValues[0]->AsObject();
	TestTrue(TEXT("Restored sight subobject is a JSON object"), RestoredSight.IsValid());
	TestEqual(TEXT("Restored sight classPath"),
		RestoredSight->GetStringField(TEXT("classPath")),
		FString(TEXT("/Script/AIModule.AISenseConfig_Sight")));
	const TArray<TSharedPtr<FJsonValue>>* RestoredSightProps = nullptr;
	TestTrue(TEXT("Sight properties array present"),
		RestoredSight->TryGetArrayField(TEXT("properties"), RestoredSightProps));
	TestEqual(TEXT("Sight has one nested property"), RestoredSightProps->Num(), 1);
	TSharedPtr<FJsonObject> Radius = (*RestoredSightProps)[0]->AsObject();
	TestEqual(TEXT("Sight radius propertyName"),
		Radius->GetStringField(TEXT("propertyName")), FString(TEXT("SightRadius")));
	TestEqual(TEXT("Sight radius value"),
		Radius->GetStringField(TEXT("value")), FString(TEXT("3000.0")));

	// Ordinary (non-instanced) properties must stay byte-identical to pre-1.10 JSON:
	// no bIsInstancedSubobject field, no subobjects field.
	FExportedComponentProperty Plain;
	Plain.PropertyName = TEXT("ComponentTags");
	Plain.PropertyType = TEXT("TArray<FName>");
	Plain.Value = TEXT("(\"Tag1\",\"Tag2\")");
	TSharedPtr<FJsonObject> PlainJson = Plain.ToJson();
	TestFalse(TEXT("Plain property omits bIsInstancedSubobject"),
		PlainJson->HasField(TEXT("bIsInstancedSubobject")));
	TestFalse(TEXT("Plain property omits subobjects array"),
		PlainJson->HasField(TEXT("subobjects")));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBlueprintExportPinTypeResolvedFlagTest,
	"BlueprintExporter.Schema.PinTypeResolvedFlag",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

// Covers B3: pin types must carry an explicit resolved/unresolved marker so AI
// consumers can distinguish "this pin has no subtype" from "we couldn't safely
// read the subtype and blanked it defensively".
bool FBlueprintExportPinTypeResolvedFlagTest::RunTest(const FString& Parameters)
{
	// Resolved case: omit the field from JSON entirely (bytes-identical to pre-1.10).
	FExportedPinType Resolved;
	Resolved.Category = TEXT("object");
	Resolved.SubCategoryObject = TEXT("/Script/Engine.Actor");
	TSharedPtr<FJsonObject> ResolvedJson = Resolved.ToJson();
	TestFalse(TEXT("Resolved pin omits subCategoryObjectResolved (defaults true)"),
		ResolvedJson->HasField(TEXT("subCategoryObjectResolved")));

	// Unresolved case: emit the field as false so AI readers can see it.
	FExportedPinType Unresolved;
	Unresolved.Category = TEXT("object");
	Unresolved.SubCategoryObject = TEXT("");
	Unresolved.bSubCategoryObjectResolved = false;
	TSharedPtr<FJsonObject> UnresolvedJson = Unresolved.ToJson();
	TestTrue(TEXT("Unresolved pin includes subCategoryObjectResolved"),
		UnresolvedJson->HasField(TEXT("subCategoryObjectResolved")));
	TestFalse(TEXT("Unresolved pin value is false"),
		UnresolvedJson->GetBoolField(TEXT("subCategoryObjectResolved")));

	// Old JSON without the field must deserialize as resolved (backwards compat).
	TSharedPtr<FJsonObject> LegacyJson = MakeShareable(new FJsonObject());
	LegacyJson->SetStringField(TEXT("category"), TEXT("object"));
	LegacyJson->SetStringField(TEXT("subCategoryObject"), TEXT("/Script/Engine.Actor"));
	LegacyJson->SetStringField(TEXT("pinSubCategory"), TEXT(""));
	LegacyJson->SetBoolField(TEXT("isArray"), false);
	LegacyJson->SetBoolField(TEXT("isSet"), false);
	LegacyJson->SetBoolField(TEXT("isMap"), false);
	LegacyJson->SetBoolField(TEXT("isReference"), false);
	LegacyJson->SetBoolField(TEXT("isConst"), false);
	LegacyJson->SetBoolField(TEXT("isWeakPointer"), false);
	FExportedPinType Legacy = FExportedPinType::FromJson(LegacyJson);
	TestTrue(TEXT("Legacy JSON defaults bSubCategoryObjectResolved to true"),
		Legacy.bSubCategoryObjectResolved);

	// Full round-trip of the unresolved case preserves the flag.
	FString Text;
	TSharedRef<TJsonWriter<>> W = TJsonWriterFactory<>::Create(&Text);
	FJsonSerializer::Serialize(UnresolvedJson.ToSharedRef(), W);
	TSharedPtr<FJsonObject> Reparsed;
	TSharedRef<TJsonReader<>> R = TJsonReaderFactory<>::Create(Text);
	FJsonSerializer::Deserialize(R, Reparsed);
	FExportedPinType RoundTripped = FExportedPinType::FromJson(Reparsed);
	TestFalse(TEXT("Unresolved flag survives round-trip"),
		RoundTripped.bSubCategoryObjectResolved);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBlueprintExportInstancedSubobjectRenderingTest,
	"BlueprintExporter.TextExport.InstancedSubobjectRendering",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

// Covers the T1 UX slice: the .txt renderer — de facto primary LLM-consumption surface
// per BRF-011 because .json is too heavy to paste into a chat — must surface parsed
// nested values from instanced subobjects (sight radius, hearing range, affiliation)
// rather than the opaque ExportTextItem_Direct blob. Without this, Tier 1's structured
// data lives only in .json and is invisible in the actual paste-into-AI workflow.
bool FBlueprintExportInstancedSubobjectRenderingTest::RunTest(const FString& Parameters)
{
	// Fixture mirrors InstancedSubobjectRoundTrip: an AIPerceptionComponent-shaped
	// component with a plain property plus SenseConfigs holding two instanced senses
	// (sight + hearing). Sight additionally carries a nested instanced property so we
	// exercise the recursive rendering path, and Hearing carries a [truncated] marker
	// so we confirm diagnostic markers survive rendering.
	FExportedBlueprint TestBP;
	TestBP.AssetPath = TEXT("/Game/Test/BP_TestAIActor");
	TestBP.AssetName = TEXT("BP_TestAIActor");
	TestBP.BlueprintType = EBlueprintExportType::Normal;
	TestBP.ParentClass.ClassName = TEXT("Actor");
	TestBP.ParentClass.bIsNative = true;

	FExportedComponent Perception;
	Perception.ComponentName = TEXT("AIPerception");
	Perception.ComponentClass = TEXT("/Script/AIModule.AIPerceptionComponent");

	// Plain property — must render as "- Name: Type = Value".
	FExportedComponentProperty Tags;
	Tags.PropertyName = TEXT("ComponentTags");
	Tags.PropertyType = TEXT("TArray<FName>");
	Tags.Value = TEXT("(\"Enemy\",\"Ranged\")");
	Perception.Properties.Add(Tags);

	// Nested instanced property inside the sight config — exercises the recursive
	// FormatNestedInstancedProperty path.
	TSharedPtr<FJsonObject> AffiliationInner = MakeShareable(new FJsonObject());
	AffiliationInner->SetStringField(TEXT("classPath"), TEXT("/Script/AIModule.AISenseAffiliationFilter"));
	AffiliationInner->SetStringField(TEXT("objectName"), TEXT("AISenseAffiliationFilter_0"));
	{
		TArray<TSharedPtr<FJsonValue>> InnerProps;
		TSharedPtr<FJsonObject> DetectEnemies = MakeShareable(new FJsonObject());
		DetectEnemies->SetStringField(TEXT("propertyName"), TEXT("bDetectEnemies"));
		DetectEnemies->SetStringField(TEXT("propertyType"), TEXT("bool"));
		DetectEnemies->SetStringField(TEXT("value"), TEXT("true"));
		InnerProps.Add(MakeShareable(new FJsonValueObject(DetectEnemies)));
		AffiliationInner->SetArrayField(TEXT("properties"), InnerProps);
	}

	TSharedPtr<FJsonObject> SightObj = MakeShareable(new FJsonObject());
	SightObj->SetStringField(TEXT("classPath"), TEXT("/Script/AIModule.AISenseConfig_Sight"));
	SightObj->SetStringField(TEXT("objectName"), TEXT("AISenseConfig_Sight_0"));
	SightObj->SetNumberField(TEXT("arrayIndex"), 0);
	{
		TArray<TSharedPtr<FJsonValue>> SightProps;

		TSharedPtr<FJsonObject> Radius = MakeShareable(new FJsonObject());
		Radius->SetStringField(TEXT("propertyName"), TEXT("SightRadius"));
		Radius->SetStringField(TEXT("propertyType"), TEXT("float"));
		Radius->SetStringField(TEXT("value"), TEXT("3000.0"));
		SightProps.Add(MakeShareable(new FJsonValueObject(Radius)));

		TSharedPtr<FJsonObject> LoseRadius = MakeShareable(new FJsonObject());
		LoseRadius->SetStringField(TEXT("propertyName"), TEXT("LoseSightRadius"));
		LoseRadius->SetStringField(TEXT("propertyType"), TEXT("float"));
		LoseRadius->SetStringField(TEXT("value"), TEXT("3500.0"));
		SightProps.Add(MakeShareable(new FJsonValueObject(LoseRadius)));

		// Nested instanced property — recursive stress.
		TSharedPtr<FJsonObject> Affiliation = MakeShareable(new FJsonObject());
		Affiliation->SetStringField(TEXT("propertyName"), TEXT("DetectionByAffiliation"));
		Affiliation->SetStringField(TEXT("propertyType"), TEXT("FAISenseAffiliationFilter"));
		Affiliation->SetBoolField(TEXT("bIsInstancedSubobject"), true);
		{
			TArray<TSharedPtr<FJsonValue>> AffiliationSubs;
			AffiliationSubs.Add(MakeShareable(new FJsonValueObject(AffiliationInner)));
			Affiliation->SetArrayField(TEXT("subobjects"), AffiliationSubs);
		}
		SightProps.Add(MakeShareable(new FJsonValueObject(Affiliation)));

		SightObj->SetArrayField(TEXT("properties"), SightProps);
	}

	TSharedPtr<FJsonObject> HearingObj = MakeShareable(new FJsonObject());
	HearingObj->SetStringField(TEXT("classPath"), TEXT("/Script/AIModule.AISenseConfig_Hearing"));
	HearingObj->SetStringField(TEXT("objectName"), TEXT("AISenseConfig_Hearing_0"));
	HearingObj->SetNumberField(TEXT("arrayIndex"), 1);
	HearingObj->SetBoolField(TEXT("bTruncated"), true); // marker must reach .txt
	{
		TArray<TSharedPtr<FJsonValue>> HearingProps;
		TSharedPtr<FJsonObject> Range = MakeShareable(new FJsonObject());
		Range->SetStringField(TEXT("propertyName"), TEXT("HearingRange"));
		Range->SetStringField(TEXT("propertyType"), TEXT("float"));
		Range->SetStringField(TEXT("value"), TEXT("1500.0"));
		HearingProps.Add(MakeShareable(new FJsonValueObject(Range)));
		HearingObj->SetArrayField(TEXT("properties"), HearingProps);
	}

	FExportedComponentProperty SenseConfigs;
	SenseConfigs.PropertyName = TEXT("SenseConfigs");
	SenseConfigs.PropertyType = TEXT("TArray<UAISenseConfig*>");
	// Flat value is kept in the schema for 1.9.1-consumer compat, but the .txt
	// must NOT render it — the whole point of this slice is replacing this blob.
	SenseConfigs.Value = TEXT("(Config[0]=/Script/AIModule.AISenseConfig_Sight'\"...\"')");
	SenseConfigs.bIsInstancedSubobject = true;
	SenseConfigs.SubobjectJsonValues.Add(MakeShareable(new FJsonValueObject(SightObj)));
	SenseConfigs.SubobjectJsonValues.Add(MakeShareable(new FJsonValueObject(HearingObj)));
	Perception.Properties.Add(SenseConfigs);

	TestBP.Components.Add(Perception);

	FHumanReadableExporter TextExporter;
	const FString TextOutput = TextExporter.ExportToText(TestBP);

	// Component still present. Class rendering strips the module-prefix leaf so
	// "/Script/AIModule.AIPerceptionComponent" comes out as "AIPerceptionComponent".
	TestTrue(TEXT("Component header rendered with stripped class name"),
		TextOutput.Contains(TEXT("AIPerception (AIPerceptionComponent)")));

	// Plain property: name, type, value.
	TestTrue(TEXT("Plain property name rendered"), TextOutput.Contains(TEXT("ComponentTags")));
	TestTrue(TEXT("Plain property type rendered"), TextOutput.Contains(TEXT("TArray<FName>")));
	TestTrue(TEXT("Plain property value rendered"),
		TextOutput.Contains(TEXT("(\"Enemy\",\"Ranged\")")));

	// Instanced header with [instanced] marker + leaf class name + arrayIndex prefix.
	TestTrue(TEXT("SenseConfigs marked [instanced]"),
		TextOutput.Contains(TEXT("SenseConfigs: TArray<UAISenseConfig*> [instanced]")));
	TestTrue(TEXT("Sight arrayIndex prefix"),
		TextOutput.Contains(TEXT("[0] AISenseConfig_Sight")));
	TestTrue(TEXT("Hearing arrayIndex prefix"),
		TextOutput.Contains(TEXT("[1] AISenseConfig_Hearing")));
	TestTrue(TEXT("Sight objectName rendered"),
		TextOutput.Contains(TEXT("(AISenseConfig_Sight_0)")));

	// The module prefix ("AIModule.") must not leak into .txt — leaf-only rendering
	// is what makes the class names useful for LLM readers.
	TestFalse(TEXT("Module prefix stripped from class names"),
		TextOutput.Contains(TEXT("AIModule.")));

	// Parsed nested values — the whole point of the slice.
	TestTrue(TEXT("SightRadius name rendered"), TextOutput.Contains(TEXT("SightRadius")));
	TestTrue(TEXT("SightRadius value rendered"), TextOutput.Contains(TEXT("3000.0")));
	TestTrue(TEXT("LoseSightRadius value rendered"), TextOutput.Contains(TEXT("3500.0")));
	TestTrue(TEXT("HearingRange value rendered"), TextOutput.Contains(TEXT("1500.0")));

	// Recursive nesting: inner instanced property + its leaf value.
	TestTrue(TEXT("Nested instanced property marker"),
		TextOutput.Contains(TEXT("DetectionByAffiliation: FAISenseAffiliationFilter [instanced]")));
	TestTrue(TEXT("Nested inner class name"),
		TextOutput.Contains(TEXT("AISenseAffiliationFilter")));
	TestTrue(TEXT("Nested inner property name"),
		TextOutput.Contains(TEXT("bDetectEnemies")));

	// Diagnostic markers preserved.
	TestTrue(TEXT("Truncation marker rendered on Hearing"),
		TextOutput.Contains(TEXT("[truncated]")));

	// The opaque ExportTextItem_Direct blob MUST NOT leak into .txt — that's exactly
	// the behaviour this slice is meant to replace.
	TestFalse(TEXT("Opaque Value blob must not appear in .txt"),
		TextOutput.Contains(TEXT("(Config[0]=/Script/AIModule.AISenseConfig_Sight")));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBlueprintExportCoverageHeaderTest,
	"BlueprintExporter.TextExport.CoverageHeader",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

// UX slice #2 of BRF-011: the .txt output and .digest.json must include an
// "export coverage" summary so a developer can tell at a glance whether the
// export captured what they need before pasting it into a chat.
bool FBlueprintExportCoverageHeaderTest::RunTest(const FString& Parameters)
{
	// Fixture: 1 component, 1 plain prop + 1 instanced prop with 2 subobjects.
	// Sight is clean and carries a nested instanced property (AffiliationFilter,
	// 1 clean subobject). Hearing carries a bTruncated marker.
	// Expected coverage:
	//   componentCount = 1, componentPropertyCount = 2,
	//   instancedSubobjectProperties = 2 (top-level + nested),
	//   parsed = 2 (Sight + AffiliationFilter), broken = 0,
	//   truncated = 1 (Hearing), cycles = 0.
	FExportedBlueprint TestBP;
	TestBP.AssetPath = TEXT("/Game/Test/BP_Coverage");
	TestBP.AssetName = TEXT("BP_Coverage");
	TestBP.BlueprintType = EBlueprintExportType::Normal;
	TestBP.ParentClass.ClassName = TEXT("Actor");
	TestBP.ParentClass.bIsNative = true;

	FExportedComponent Perception;
	Perception.ComponentName = TEXT("AIPerception");
	Perception.ComponentClass = TEXT("/Script/AIModule.AIPerceptionComponent");

	FExportedComponentProperty Tags;
	Tags.PropertyName = TEXT("ComponentTags");
	Tags.PropertyType = TEXT("TArray<FName>");
	Tags.Value = TEXT("(\"Enemy\")");
	Perception.Properties.Add(Tags);

	// Nested instanced subobject for the affiliation filter.
	TSharedPtr<FJsonObject> AffiliationInner = MakeShareable(new FJsonObject());
	AffiliationInner->SetStringField(TEXT("classPath"), TEXT("/Script/AIModule.AISenseAffiliationFilter"));
	{
		TArray<TSharedPtr<FJsonValue>> InnerProps;
		TSharedPtr<FJsonObject> DetectEnemies = MakeShareable(new FJsonObject());
		DetectEnemies->SetStringField(TEXT("propertyName"), TEXT("bDetectEnemies"));
		DetectEnemies->SetStringField(TEXT("propertyType"), TEXT("bool"));
		DetectEnemies->SetStringField(TEXT("value"), TEXT("true"));
		InnerProps.Add(MakeShareable(new FJsonValueObject(DetectEnemies)));
		AffiliationInner->SetArrayField(TEXT("properties"), InnerProps);
	}

	TSharedPtr<FJsonObject> SightObj = MakeShareable(new FJsonObject());
	SightObj->SetStringField(TEXT("classPath"), TEXT("/Script/AIModule.AISenseConfig_Sight"));
	{
		TArray<TSharedPtr<FJsonValue>> SightProps;
		TSharedPtr<FJsonObject> Affiliation = MakeShareable(new FJsonObject());
		Affiliation->SetStringField(TEXT("propertyName"), TEXT("DetectionByAffiliation"));
		Affiliation->SetStringField(TEXT("propertyType"), TEXT("FAISenseAffiliationFilter"));
		Affiliation->SetBoolField(TEXT("bIsInstancedSubobject"), true);
		{
			TArray<TSharedPtr<FJsonValue>> AffSubs;
			AffSubs.Add(MakeShareable(new FJsonValueObject(AffiliationInner)));
			Affiliation->SetArrayField(TEXT("subobjects"), AffSubs);
		}
		SightProps.Add(MakeShareable(new FJsonValueObject(Affiliation)));
		SightObj->SetArrayField(TEXT("properties"), SightProps);
	}

	TSharedPtr<FJsonObject> HearingObj = MakeShareable(new FJsonObject());
	HearingObj->SetStringField(TEXT("classPath"), TEXT("/Script/AIModule.AISenseConfig_Hearing"));
	HearingObj->SetBoolField(TEXT("bTruncated"), true);

	FExportedComponentProperty SenseConfigs;
	SenseConfigs.PropertyName = TEXT("SenseConfigs");
	SenseConfigs.PropertyType = TEXT("TArray<UAISenseConfig*>");
	SenseConfigs.bIsInstancedSubobject = true;
	SenseConfigs.SubobjectJsonValues.Add(MakeShareable(new FJsonValueObject(SightObj)));
	SenseConfigs.SubobjectJsonValues.Add(MakeShareable(new FJsonValueObject(HearingObj)));
	Perception.Properties.Add(SenseConfigs);

	TestBP.Components.Add(Perception);

	FHumanReadableExporter TextExporter;
	const FString TextOutput = TextExporter.ExportToText(TestBP);

	// .txt coverage block
	TestTrue(TEXT("COVERAGE: section present"), TextOutput.Contains(TEXT("COVERAGE:")));
	TestTrue(TEXT("Component count rendered"), TextOutput.Contains(TEXT("1 component, 2 properties")));
	TestTrue(TEXT("Instanced prop + instance totals rendered"),
		TextOutput.Contains(TEXT("2 instanced-subobject properties, 3 subobject instances")));
	TestTrue(TEXT("Parsed count rendered"), TextOutput.Contains(TEXT("2 parsed")));
	TestTrue(TEXT("Truncated count rendered"), TextOutput.Contains(TEXT("1 truncated")));
	// Zero-count categories must NOT clutter the output (broken / cycles are zero here).
	TestFalse(TEXT("Zero-count 'broken' not rendered"), TextOutput.Contains(TEXT("0 broken")));
	TestFalse(TEXT("Zero-count 'cycles' not rendered"), TextOutput.Contains(TEXT("0 cycle")));

	// .digest.json coverage object
	TSharedPtr<FJsonObject> Digest = TextExporter.GenerateDigest(TestBP);
	TestTrue(TEXT("Digest is valid"), Digest.IsValid());
	const TSharedPtr<FJsonObject>* CoverageObj = nullptr;
	TestTrue(TEXT("digest.coverage present"),
		Digest->TryGetObjectField(TEXT("coverage"), CoverageObj));
	if (CoverageObj && CoverageObj->IsValid())
	{
		TestEqual(TEXT("coverage.componentCount"),
			(int32)(*CoverageObj)->GetIntegerField(TEXT("componentCount")), 1);
		TestEqual(TEXT("coverage.componentPropertyCount"),
			(int32)(*CoverageObj)->GetIntegerField(TEXT("componentPropertyCount")), 2);
		TestEqual(TEXT("coverage.instancedSubobjectProperties"),
			(int32)(*CoverageObj)->GetIntegerField(TEXT("instancedSubobjectProperties")), 2);
		TestEqual(TEXT("coverage.subobjectInstancesParsed"),
			(int32)(*CoverageObj)->GetIntegerField(TEXT("subobjectInstancesParsed")), 2);
		TestEqual(TEXT("coverage.subobjectInstancesBroken"),
			(int32)(*CoverageObj)->GetIntegerField(TEXT("subobjectInstancesBroken")), 0);
		TestEqual(TEXT("coverage.subobjectInstancesTruncated"),
			(int32)(*CoverageObj)->GetIntegerField(TEXT("subobjectInstancesTruncated")), 1);
		TestEqual(TEXT("coverage.subobjectInstancesCycles"),
			(int32)(*CoverageObj)->GetIntegerField(TEXT("subobjectInstancesCycles")), 0);
	}

	// Component-less Blueprints should get no COVERAGE: block (otherwise we'd
	// clutter every non-actor export with "0 components, 0 properties").
	FExportedBlueprint EmptyBP;
	EmptyBP.AssetPath = TEXT("/Game/Test/BP_NoComponents");
	EmptyBP.AssetName = TEXT("BP_NoComponents");
	EmptyBP.ParentClass.ClassName = TEXT("Object");
	EmptyBP.ParentClass.bIsNative = true;
	const FString EmptyOutput = TextExporter.ExportToText(EmptyBP);
	TestFalse(TEXT("COVERAGE omitted when no components"),
		EmptyOutput.Contains(TEXT("COVERAGE:")));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBlueprintExportInstancedSubobjectEdgeCasesTest,
	"BlueprintExporter.TextExport.InstancedSubobjectEdgeCases",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

// Bug-hunt coverage for subobject-rendering edge cases surfaced during the
// BRF-011 pre-push review: null FJsonValue entries, empty SubobjectJsonValues,
// cycle-detected markers, broken-reference info strings, and map-key subobjects.
// Each sub-case builds its own small fixture and exercises one rendering path.
bool FBlueprintExportInstancedSubobjectEdgeCasesTest::RunTest(const FString& Parameters)
{
	FHumanReadableExporter TextExporter;

	auto MakeComponentWithSenseConfigs = [](TArray<TSharedPtr<FJsonValue>> Subs) -> FExportedComponent
	{
		FExportedComponent Comp;
		Comp.ComponentName = TEXT("AIPerception");
		Comp.ComponentClass = TEXT("/Script/AIModule.AIPerceptionComponent");

		FExportedComponentProperty Prop;
		Prop.PropertyName = TEXT("SenseConfigs");
		Prop.PropertyType = TEXT("TArray<UAISenseConfig*>");
		Prop.bIsInstancedSubobject = true;
		Prop.SubobjectJsonValues = MoveTemp(Subs);
		Comp.Properties.Add(MoveTemp(Prop));
		return Comp;
	};

	auto BuildBP = [](const FExportedComponent& Comp) -> FExportedBlueprint
	{
		FExportedBlueprint BP;
		BP.AssetPath = TEXT("/Game/Test/BP_Edge");
		BP.AssetName = TEXT("BP_Edge");
		BP.BlueprintType = EBlueprintExportType::Normal;
		BP.ParentClass.ClassName = TEXT("Actor");
		BP.ParentClass.bIsNative = true;
		BP.Components.Add(Comp);
		return BP;
	};

	// ----- Case A: null TSharedPtr<FJsonValue> entry -----
	{
		TArray<TSharedPtr<FJsonValue>> Subs;
		Subs.Add(TSharedPtr<FJsonValue>());  // explicit null
		FExportedBlueprint BP = BuildBP(MakeComponentWithSenseConfigs(Subs));
		const FString Out = TextExporter.ExportToText(BP);
		TestTrue(TEXT("Null TSharedPtr entry renders as <null subobject>"),
			Out.Contains(TEXT("<null subobject>")));
	}

	// ----- Case B: empty SubobjectJsonValues with bIsInstancedSubobject=true -----
	{
		FExportedBlueprint BP = BuildBP(MakeComponentWithSenseConfigs({}));
		const FString Out = TextExporter.ExportToText(BP);
		TestTrue(TEXT("Empty array renders as [instanced] (none)"),
			Out.Contains(TEXT("[instanced] (none)")));
	}

	// ----- Case C: bCycleDetected=true marker -----
	{
		TSharedPtr<FJsonObject> Obj = MakeShareable(new FJsonObject());
		Obj->SetStringField(TEXT("classPath"), TEXT("/Script/AIModule.AISenseConfig_Sight"));
		Obj->SetBoolField(TEXT("bCycleDetected"), true);

		TArray<TSharedPtr<FJsonValue>> Subs;
		Subs.Add(MakeShareable(new FJsonValueObject(Obj)));
		FExportedBlueprint BP = BuildBP(MakeComponentWithSenseConfigs(Subs));
		const FString Out = TextExporter.ExportToText(BP);
		TestTrue(TEXT("Cycle marker rendered"), Out.Contains(TEXT("[cycle]")));
		TestTrue(TEXT("Cycle counted in coverage"), Out.Contains(TEXT("1 cycle")));
	}

	// ----- Case D: bHasBrokenReference=true with brokenReferenceInfo string -----
	{
		TSharedPtr<FJsonObject> Obj = MakeShareable(new FJsonObject());
		Obj->SetStringField(TEXT("classPath"), TEXT("/Script/AIModule.AISenseConfig_Sight"));
		Obj->SetBoolField(TEXT("bHasBrokenReference"), true);
		Obj->SetStringField(TEXT("brokenReferenceInfo"), TEXT("deleted asset /Game/Old.Old"));

		TArray<TSharedPtr<FJsonValue>> Subs;
		Subs.Add(MakeShareable(new FJsonValueObject(Obj)));
		FExportedBlueprint BP = BuildBP(MakeComponentWithSenseConfigs(Subs));
		const FString Out = TextExporter.ExportToText(BP);
		TestTrue(TEXT("Broken marker with info string rendered"),
			Out.Contains(TEXT("[broken: deleted asset /Game/Old.Old]")));
		TestTrue(TEXT("Broken counted in coverage"), Out.Contains(TEXT("1 broken")));
	}

	// ----- Case E: mapKey subobject (vs the usual arrayIndex) -----
	{
		TSharedPtr<FJsonObject> Obj = MakeShareable(new FJsonObject());
		Obj->SetStringField(TEXT("classPath"), TEXT("/Script/Engine.InstancedValue"));
		Obj->SetStringField(TEXT("mapKey"), TEXT("MyKey"));

		TArray<TSharedPtr<FJsonValue>> Subs;
		Subs.Add(MakeShareable(new FJsonValueObject(Obj)));
		FExportedBlueprint BP = BuildBP(MakeComponentWithSenseConfigs(Subs));
		const FString Out = TextExporter.ExportToText(BP);
		TestTrue(TEXT("Map-key prefix rendered"),
			Out.Contains(TEXT("[\"MyKey\"] InstancedValue")));
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBlueprintExportCoverageHierarchyTest,
	"BlueprintExporter.TextExport.CoverageHierarchy",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

// The coverage walker recurses into FExportedComponent::ChildComponents. Earlier
// tests only covered flat (no-children) component arrays; this one ensures
// nested child components and their properties are tallied.
bool FBlueprintExportCoverageHierarchyTest::RunTest(const FString& Parameters)
{
	// Three-level hierarchy: Root -> Middle -> Leaf. Each level contributes one
	// plain property. Middle also carries an instanced property with one clean
	// subobject to prove the instanced counter traverses the child path.
	FExportedComponent Leaf;
	Leaf.ComponentName = TEXT("Leaf");
	Leaf.ComponentClass = TEXT("/Script/Engine.SceneComponent");
	{
		FExportedComponentProperty P;
		P.PropertyName = TEXT("bVisible");
		P.PropertyType = TEXT("bool");
		P.Value = TEXT("true");
		Leaf.Properties.Add(P);
	}

	FExportedComponent Middle;
	Middle.ComponentName = TEXT("Middle");
	Middle.ComponentClass = TEXT("/Script/Engine.SceneComponent");
	{
		FExportedComponentProperty P;
		P.PropertyName = TEXT("bHidden");
		P.PropertyType = TEXT("bool");
		P.Value = TEXT("false");
		Middle.Properties.Add(P);
	}
	{
		TSharedPtr<FJsonObject> InnerObj = MakeShareable(new FJsonObject());
		InnerObj->SetStringField(TEXT("classPath"), TEXT("/Script/Engine.AttachmentData"));

		FExportedComponentProperty P;
		P.PropertyName = TEXT("AttachmentRule");
		P.PropertyType = TEXT("FAttachmentData");
		P.bIsInstancedSubobject = true;
		P.SubobjectJsonValues.Add(MakeShareable(new FJsonValueObject(InnerObj)));
		Middle.Properties.Add(P);
	}
	Middle.ChildComponents.Add(Leaf);

	FExportedComponent Root;
	Root.ComponentName = TEXT("Root");
	Root.ComponentClass = TEXT("/Script/Engine.SceneComponent");
	{
		FExportedComponentProperty P;
		P.PropertyName = TEXT("RelativeLocation");
		P.PropertyType = TEXT("FVector");
		P.Value = TEXT("(X=0,Y=0,Z=0)");
		Root.Properties.Add(P);
	}
	Root.ChildComponents.Add(Middle);

	FExportedBlueprint BP;
	BP.AssetPath = TEXT("/Game/Test/BP_Hierarchy");
	BP.AssetName = TEXT("BP_Hierarchy");
	BP.BlueprintType = EBlueprintExportType::Normal;
	BP.ParentClass.ClassName = TEXT("Actor");
	BP.ParentClass.bIsNative = true;
	BP.Components.Add(Root);

	FHumanReadableExporter TextExporter;

	// Digest coverage must tally all three components and all four properties.
	TSharedPtr<FJsonObject> Digest = TextExporter.GenerateDigest(BP);
	const TSharedPtr<FJsonObject>* CoverageObj = nullptr;
	TestTrue(TEXT("digest.coverage present"),
		Digest->TryGetObjectField(TEXT("coverage"), CoverageObj));
	if (CoverageObj && CoverageObj->IsValid())
	{
		TestEqual(TEXT("componentCount across hierarchy"),
			(int32)(*CoverageObj)->GetIntegerField(TEXT("componentCount")), 3);
		TestEqual(TEXT("componentPropertyCount across hierarchy"),
			(int32)(*CoverageObj)->GetIntegerField(TEXT("componentPropertyCount")), 4);
		TestEqual(TEXT("instancedSubobjectProperties includes nested component"),
			(int32)(*CoverageObj)->GetIntegerField(TEXT("instancedSubobjectProperties")), 1);
		TestEqual(TEXT("subobjectInstancesParsed across hierarchy"),
			(int32)(*CoverageObj)->GetIntegerField(TEXT("subobjectInstancesParsed")), 1);
	}

	// Text output must also include the nested child in the COMPONENTS section.
	const FString Out = TextExporter.ExportToText(BP);
	TestTrue(TEXT("Root rendered"), Out.Contains(TEXT("Root (SceneComponent)")));
	TestTrue(TEXT("Middle rendered"), Out.Contains(TEXT("Middle (SceneComponent)")));
	TestTrue(TEXT("Leaf rendered"), Out.Contains(TEXT("Leaf (SceneComponent)")));
	TestTrue(TEXT("Coverage line reports 3 components, 4 properties"),
		Out.Contains(TEXT("3 components, 4 properties")));

	return true;
}

// ---------------------------------------------------------------------------
// M29.6.1 — UFUNCTION call-through helpers in DeepRenderShared
//
// Validates the ProcessEvent-based zero-include reflection path that M29.6.2
// and M29.6.3 will use to invoke Mutable UFUNCTIONs without a compile-time
// dep on the Mutable module. Uses a local fixture UCLASS (no Mutable present)
// so these tests run on any project — CI doesn't need MutableSample set up.
// ---------------------------------------------------------------------------

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBpxUFunctionCallScalarReturnsTest,
	"BlueprintExporter.UFunctionCall.ScalarReturns",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FBpxUFunctionCallScalarReturnsTest::RunTest(const FString& Parameters)
{
	using namespace BlueprintExporter::DeepRender::UFunctionCall;

	UBpxTestUFunctionFixture* Fixture = NewObject<UBpxTestUFunctionFixture>();
	TestNotNull(TEXT("fixture constructed"), Fixture);
	if (!Fixture)
	{
		return false;
	}

	// Nullary scalar returns.
	TOptional<bool> BoolResult = CallBool(Fixture, TEXT("GetBoolValue"));
	TestTrue(TEXT("CallBool hit"), BoolResult.IsSet());
	TestTrue(TEXT("CallBool value"), BoolResult.IsSet() && BoolResult.GetValue() == true);

	TOptional<int32> IntResult = CallInt(Fixture, TEXT("GetIntValue"));
	TestTrue(TEXT("CallInt hit"), IntResult.IsSet());
	TestEqual(TEXT("CallInt value"), IntResult.Get(0), 42);

	TOptional<float> FloatResult = CallFloat(Fixture, TEXT("GetFloatValue"));
	TestTrue(TEXT("CallFloat hit"), FloatResult.IsSet());
	TestEqual(TEXT("CallFloat value"), FloatResult.Get(0.0f), 3.25f);

	TOptional<FString> StringResult = CallString(Fixture, TEXT("GetStringValue"));
	TestTrue(TEXT("CallString hit"), StringResult.IsSet());
	TestEqual(TEXT("CallString value"), StringResult.Get(FString()), FString(TEXT("hello")));

	TOptional<FName> NameResult = CallFName(Fixture, TEXT("GetNameValue"));
	TestTrue(TEXT("CallFName hit"), NameResult.IsSet());
	TestEqual(TEXT("CallFName value"), NameResult.Get(NAME_None).ToString(), FString(TEXT("world")));

	TOptional<UObject*> ObjectResult = CallObject(Fixture, TEXT("GetObjectValue"));
	TestTrue(TEXT("CallObject hit"), ObjectResult.IsSet());
	TestEqual(TEXT("CallObject returns self"), ObjectResult.Get(nullptr), (UObject*)Fixture);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBpxUFunctionCallInputArgsTest,
	"BlueprintExporter.UFunctionCall.InputArgs",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FBpxUFunctionCallInputArgsTest::RunTest(const FString& Parameters)
{
	using namespace BlueprintExporter::DeepRender::UFunctionCall;

	UBpxTestUFunctionFixture* Fixture = NewObject<UBpxTestUFunctionFixture>();
	if (!Fixture) { return false; }

	// Single int arg — ImportText parses "17" → int32 17.
	TArray<FString> EchoArgs; EchoArgs.Add(TEXT("17"));
	TOptional<int32> EchoResult = CallInt(Fixture, TEXT("EchoInt"), EchoArgs);
	TestTrue(TEXT("EchoInt hit"), EchoResult.IsSet());
	TestEqual(TEXT("EchoInt value"), EchoResult.Get(0), 17);

	// Two float args — "2.5" + "1.25" → 3.75f.
	TArray<FString> AddArgs; AddArgs.Add(TEXT("2.5")); AddArgs.Add(TEXT("1.25"));
	TOptional<float> AddResult = CallFloat(Fixture, TEXT("AddFloats"), AddArgs);
	TestTrue(TEXT("AddFloats hit"), AddResult.IsSet());
	TestEqual(TEXT("AddFloats value"), AddResult.Get(0.0f), 3.75f);

	// Two FString args — "foo" + "bar" → "foobar". Exercises InitializeValue
	// on non-POD param types (FString) to make sure we don't double-free.
	TArray<FString> ConcatArgs; ConcatArgs.Add(TEXT("foo")); ConcatArgs.Add(TEXT("bar"));
	TOptional<FString> ConcatResult = CallString(Fixture, TEXT("ConcatStrings"), ConcatArgs);
	TestTrue(TEXT("ConcatStrings hit"), ConcatResult.IsSet());
	TestEqual(TEXT("ConcatStrings value"), ConcatResult.Get(FString()), FString(TEXT("foobar")));

	// Arg-count mismatch — EchoInt wants 1, we pass 0 → should return empty.
	TOptional<int32> MismatchResult = CallInt(Fixture, TEXT("EchoInt"));
	TestFalse(TEXT("EchoInt with zero args returns empty"), MismatchResult.IsSet());

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBpxUFunctionCallEnumReturnTest,
	"BlueprintExporter.UFunctionCall.EnumReturn",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FBpxUFunctionCallEnumReturnTest::RunTest(const FString& Parameters)
{
	using namespace BlueprintExporter::DeepRender::UFunctionCall;

	UBpxTestUFunctionFixture* Fixture = NewObject<UBpxTestUFunctionFixture>();
	if (!Fixture) { return false; }

	TOptional<int64> EnumResult = CallEnumInt64(Fixture, TEXT("GetEnumValue"));
	TestTrue(TEXT("CallEnumInt64 hit"), EnumResult.IsSet());
	TestEqual(TEXT("CallEnumInt64 value matches EBpxTestFixtureEnum::Beta"),
		EnumResult.Get(-1), (int64)EBpxTestFixtureEnum::Beta);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBpxUFunctionCallStructReturnTest,
	"BlueprintExporter.UFunctionCall.StructReturn",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FBpxUFunctionCallStructReturnTest::RunTest(const FString& Parameters)
{
	using namespace BlueprintExporter::DeepRender::UFunctionCall;

	UBpxTestUFunctionFixture* Fixture = NewObject<UBpxTestUFunctionFixture>();
	if (!Fixture) { return false; }

	// Struct returns go through CallUFunctionRaw — the callback receives the
	// return FStructProperty + the raw memory. Caller reflects into the
	// UScriptStruct fields. This is the pattern M29.6.3 will use for
	// FMutableParamUIMetadata / FMutableStateUIMetadata / FCustomizableObjectProjector.
	FBpxTestFixtureStruct Extracted;
	bool bCalled = false;

	const bool bFnPresent = CallUFunctionRaw(Fixture, TEXT("GetStructValue"),
		TArray<FString>(),
		[&Extracted, &bCalled, this](FProperty* ReturnProp, const void* ReturnValuePtr)
		{
			bCalled = true;
			FStructProperty* StructProp = CastField<FStructProperty>(ReturnProp);
			TestNotNull(TEXT("return prop is FStructProperty"), StructProp);
			if (!StructProp) { return; }
			TestEqual(TEXT("struct type matches"),
				StructProp->Struct->GetFName(),
				FBpxTestFixtureStruct::StaticStruct()->GetFName());
			StructProp->Struct->CopyScriptStruct(&Extracted, ReturnValuePtr);
		});

	TestTrue(TEXT("CallUFunctionRaw returned true"), bFnPresent);
	TestTrue(TEXT("callback invoked"), bCalled);
	TestEqual(TEXT("struct int field"), Extracted.IntField, 7);
	TestEqual(TEXT("struct string field"), Extracted.StringField, FString(TEXT("struct")));
	TestEqual(TEXT("struct float field"), Extracted.FloatField, 2.5f);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBpxUFunctionCallVoidReturnTest,
	"BlueprintExporter.UFunctionCall.VoidReturn",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FBpxUFunctionCallVoidReturnTest::RunTest(const FString& Parameters)
{
	using namespace BlueprintExporter::DeepRender::UFunctionCall;

	UBpxTestUFunctionFixture* Fixture = NewObject<UBpxTestUFunctionFixture>();
	if (!Fixture) { return false; }

	// Void-return UFUNCTION — raw primitive returns true (call succeeded) but
	// the callback is never invoked (there's no return property to hand out).
	bool bCallbackFired = false;
	const bool bCallOK = CallUFunctionRaw(Fixture, TEXT("VoidFunction"),
		TArray<FString>(),
		[&bCallbackFired](FProperty*, const void*) { bCallbackFired = true; });

	TestTrue(TEXT("void-return call succeeds"), bCallOK);
	TestFalse(TEXT("void-return does not trigger callback"), bCallbackFired);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBpxUFunctionCallMissingFunctionTest,
	"BlueprintExporter.UFunctionCall.MissingFunction",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FBpxUFunctionCallMissingFunctionTest::RunTest(const FString& Parameters)
{
	using namespace BlueprintExporter::DeepRender::UFunctionCall;

	UBpxTestUFunctionFixture* Fixture = NewObject<UBpxTestUFunctionFixture>();
	if (!Fixture) { return false; }

	// This is the load-bearing case for the M29.6 refactor: a UFUNCTION that
	// doesn't exist on the target class (because its owning module isn't
	// loaded) must degrade gracefully to empty TOptional — never crash, never
	// log-spam. Simulates a Mutable-less build encountering a
	// UCustomizableObject asset somehow.
	TOptional<int32> MissingResult = CallInt(Fixture, TEXT("ThisFunctionDoesNotExist"));
	TestFalse(TEXT("missing function returns empty TOptional"), MissingResult.IsSet());

	bool bCallbackFired = false;
	const bool bCallOK = CallUFunctionRaw(Fixture, TEXT("StillDoesNotExist"),
		TArray<FString>(),
		[&bCallbackFired](FProperty*, const void*) { bCallbackFired = true; });
	TestFalse(TEXT("missing function returns false"), bCallOK);
	TestFalse(TEXT("missing function does not trigger callback"), bCallbackFired);

	// Null object input — also must degrade gracefully.
	TOptional<int32> NullResult = CallInt(nullptr, TEXT("GetIntValue"));
	TestFalse(TEXT("null obj returns empty TOptional"), NullResult.IsSet());

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBpxUFunctionCallReturnTypeMismatchTest,
	"BlueprintExporter.UFunctionCall.ReturnTypeMismatch",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FBpxUFunctionCallReturnTypeMismatchTest::RunTest(const FString& Parameters)
{
	using namespace BlueprintExporter::DeepRender::UFunctionCall;

	UBpxTestUFunctionFixture* Fixture = NewObject<UBpxTestUFunctionFixture>();
	if (!Fixture) { return false; }

	// GetIntValue returns int32 — if the caller asks for a bool, the typed
	// wrapper should return empty rather than misread the int bytes as bool.
	// Important for the engine-agnostic principle: type-signature drift between
	// Mutable versions shouldn't crash the renderer; it should degrade to
	// "_not reachable_".
	TOptional<bool> WrongType = CallBool(Fixture, TEXT("GetIntValue"));
	TestFalse(TEXT("type-mismatched return returns empty TOptional"), WrongType.IsSet());

	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS

