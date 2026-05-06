// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Reflection/ReflectionOps.h"
#include "Curves/RichCurve.h"
#include "EdGraph/EdGraphPin.h"
#include "Reflection/ReflectionTypes.h"
#include "UObject/Class.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeReflectionOps() {}

// ********** Begin Cross Module References ********************************************************
AIMODULE_API UClass* Z_Construct_UClass_UEnvQuery_NoRegister();
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UBpxReflectionOps();
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UBpxReflectionOps_NoRegister();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FBpxGraphEndpoints();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FBpxNodeResult();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FBpxReflectionResult();
COREUOBJECT_API UClass* Z_Construct_UClass_UClass_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UScriptStruct_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UUserDefinedStruct_NoRegister();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
ENGINE_API UClass* Z_Construct_UClass_UBlueprint_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
ENGINE_API UClass* Z_Construct_UClass_UCurveFloat_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UEdGraph_NoRegister();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FEdGraphPinType();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FRichCurveKey();
UPackage* Z_Construct_UPackage__Script_BlueprintExporter();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UBpxReflectionOps Function AddBranchNode *********************************
struct Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode_Statics
{
	struct BpxReflectionOps_eventAddBranchNode_Parms
	{
		UBlueprint* Blueprint;
		FName GraphName;
		FVector2D Position;
		FBpxNodeResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Spawn a `UK2Node_IfThenElse` (Branch node) into a named K2 graph with a\n\x09 * deterministic NodeGuid + pin IDs.\n\x09 *\n\x09 * Simplest of the M28.3 node-spawn family \xe2\x80\x94 Branch has zero configuration\n\x09 * surface (default pins handle exec/condition/then/else), so the op focuses\n\x09 * on the shared machinery: walk all three graph families via\n\x09 * `FindFunctionGraphByName`, bypass `FGraphNodeCreator` for a deterministic\n\x09 * `FName` on `NewObject`, overwrite `NodeGuid` with\n\x09 * `SeedGuidFromJoined(<bp>:graph:<g>:branch:<x>,<y>)`, seed pin IDs via the\n\x09 * M26.1.2 `SeedPinGuidsForNode` recipe.\n\x09 *\n\x09 * `GraphName` may refer to any of: a function graph\n\x09 * (`Blueprint->FunctionGraphs`), an interface override graph\n\x09 * (`ImplementedInterfaces[].Graphs`), or an ubergraph\n\x09 * (`UbergraphPages` \xe2\x80\x94 typically \"EventGraph\"). Same resolution order as\n\x09 * `ConnectGraphPinsByGuidString` (M28.3-narrow).\n\x09 *\n\x09 * Idempotent on the seeded NodeGuid: if a node with the seeded GUID already\n\x09 * exists in the graph (i.e. `AddBranchNode` was called with identical\n\x09 * GraphName + Position), returns `bSuccess=true, bSkipped=true`. Position is\n\x09 * included in the seed so two distinct Branches in the same graph get\n\x09 * distinct GUIDs.\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.\n\x09 *\n\x09 * Thread: game-thread only.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spawn a `UK2Node_IfThenElse` (Branch node) into a named K2 graph with a\ndeterministic NodeGuid + pin IDs.\n\nSimplest of the M28.3 node-spawn family \xe2\x80\x94 Branch has zero configuration\nsurface (default pins handle exec/condition/then/else), so the op focuses\non the shared machinery: walk all three graph families via\n`FindFunctionGraphByName`, bypass `FGraphNodeCreator` for a deterministic\n`FName` on `NewObject`, overwrite `NodeGuid` with\n`SeedGuidFromJoined(<bp>:graph:<g>:branch:<x>,<y>)`, seed pin IDs via the\nM26.1.2 `SeedPinGuidsForNode` recipe.\n\n`GraphName` may refer to any of: a function graph\n(`Blueprint->FunctionGraphs`), an interface override graph\n(`ImplementedInterfaces[].Graphs`), or an ubergraph\n(`UbergraphPages` \xe2\x80\x94 typically \"EventGraph\"). Same resolution order as\n`ConnectGraphPinsByGuidString` (M28.3-narrow).\n\nIdempotent on the seeded NodeGuid: if a node with the seeded GUID already\nexists in the graph (i.e. `AddBranchNode` was called with identical\nGraphName + Position), returns `bSuccess=true, bSkipped=true`. Position is\nincluded in the seed so two distinct Branches in the same graph get\ndistinct GUIDs.\n\nCaller is responsible for `CompileAndSavePackage(BP)` after the add.\n\nThread: game-thread only." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AddBranchNode constinit property declarations *************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_GraphName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddBranchNode constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddBranchNode Property Definitions ************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddBranchNode_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode_Statics::NewProp_GraphName = { "GraphName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddBranchNode_Parms, GraphName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddBranchNode_Parms, Position), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddBranchNode_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxNodeResult, METADATA_PARAMS(0, nullptr) }; // 685492501
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode_Statics::NewProp_GraphName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode_Statics::PropPointers) < 2048);
// ********** End Function AddBranchNode Property Definitions **************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddBranchNode", 	Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode_Statics::BpxReflectionOps_eventAddBranchNode_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04822401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode_Statics::BpxReflectionOps_eventAddBranchNode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddBranchNode)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_GraphName);
	P_GET_STRUCT(FVector2D,Z_Param_Position);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxNodeResult*)Z_Param__Result=UBpxReflectionOps::AddBranchNode(Z_Param_Blueprint,Z_Param_GraphName,Z_Param_Position);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddBranchNode ***********************************

// ********** Begin Class UBpxReflectionOps Function AddBreakStructNode ****************************
struct Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics
{
	struct BpxReflectionOps_eventAddBreakStructNode_Parms
	{
		UBlueprint* Blueprint;
		FName GraphName;
		UScriptStruct* StructType;
		FVector2D Position;
		FBpxNodeResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Spawn a `UK2Node_BreakStruct` node \xe2\x80\x94 pure node that splits a struct\n\x09 * input into per-field output pins. Sibling of `AddMakeStructNode`.\n\x09 *\n\x09 * Same driver as Make: the read half of read-modify-write inside loop\n\x09 * bodies. `StructType` MUST be set before `AllocateDefaultPins` for the\n\x09 * same reason \xe2\x80\x94 the inherited `K2Node_StructMemberGet::AllocateDefaultPins`\n\x09 * walks the struct via `FOptionalPinManager::RebuildPropertyList` to\n\x09 * spawn the per-field output pins. `bMadeAfterOverridePinRemoval = true`\n\x09 * matches the engine's spawn path (`EdGraphSchema_K2.cpp:7350`).\n\x09 *\n\x09 * `StructType == nullptr` is a structured error. `UK2Node_BreakStruct::CanBeBroken`\n\x09 * returns true if the struct has any `BlueprintVisible` property \xe2\x80\x94 the\n\x09 * BlueprintReadOnly check is omitted vs Make (you can break a read-only\n\x09 * field even if you can't construct one). Bridge does not pre-check\n\x09 * CanBeBroken \xe2\x80\x94 the engine's own validation surfaces clearly at compile\n\x09 * time and pre-checking would duplicate `BLUEPRINTGRAPH_API` surface.\n\x09 *\n\x09 * Determinism: seed key\n\x09 * `md5(<bp>:graph:<g>:break_struct:<struct_path>:<x,y>)`. Idempotent.\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.\n\x09 *\n\x09 * Thread: game-thread only.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spawn a `UK2Node_BreakStruct` node \xe2\x80\x94 pure node that splits a struct\ninput into per-field output pins. Sibling of `AddMakeStructNode`.\n\nSame driver as Make: the read half of read-modify-write inside loop\nbodies. `StructType` MUST be set before `AllocateDefaultPins` for the\nsame reason \xe2\x80\x94 the inherited `K2Node_StructMemberGet::AllocateDefaultPins`\nwalks the struct via `FOptionalPinManager::RebuildPropertyList` to\nspawn the per-field output pins. `bMadeAfterOverridePinRemoval = true`\nmatches the engine's spawn path (`EdGraphSchema_K2.cpp:7350`).\n\n`StructType == nullptr` is a structured error. `UK2Node_BreakStruct::CanBeBroken`\nreturns true if the struct has any `BlueprintVisible` property \xe2\x80\x94 the\nBlueprintReadOnly check is omitted vs Make (you can break a read-only\nfield even if you can't construct one). Bridge does not pre-check\nCanBeBroken \xe2\x80\x94 the engine's own validation surfaces clearly at compile\ntime and pre-checking would duplicate `BLUEPRINTGRAPH_API` surface.\n\nDeterminism: seed key\n`md5(<bp>:graph:<g>:break_struct:<struct_path>:<x,y>)`. Idempotent.\n\nCaller is responsible for `CompileAndSavePackage(BP)` after the add.\n\nThread: game-thread only." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AddBreakStructNode constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_GraphName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StructType;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddBreakStructNode constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddBreakStructNode Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddBreakStructNode_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::NewProp_GraphName = { "GraphName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddBreakStructNode_Parms, GraphName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::NewProp_StructType = { "StructType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddBreakStructNode_Parms, StructType), Z_Construct_UClass_UScriptStruct_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddBreakStructNode_Parms, Position), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddBreakStructNode_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxNodeResult, METADATA_PARAMS(0, nullptr) }; // 685492501
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::NewProp_GraphName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::NewProp_StructType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::PropPointers) < 2048);
// ********** End Function AddBreakStructNode Property Definitions *********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddBreakStructNode", 	Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::BpxReflectionOps_eventAddBreakStructNode_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04822401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::BpxReflectionOps_eventAddBreakStructNode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddBreakStructNode)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_GraphName);
	P_GET_OBJECT(UScriptStruct,Z_Param_StructType);
	P_GET_STRUCT(FVector2D,Z_Param_Position);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxNodeResult*)Z_Param__Result=UBpxReflectionOps::AddBreakStructNode(Z_Param_Blueprint,Z_Param_GraphName,Z_Param_StructType,Z_Param_Position);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddBreakStructNode ******************************

// ********** Begin Class UBpxReflectionOps Function AddCallFunctionNode ***************************
struct Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics
{
	struct BpxReflectionOps_eventAddCallFunctionNode_Parms
	{
		UBlueprint* Blueprint;
		FName GraphName;
		FName MemberName;
		UClass* TargetClass;
		FVector2D Position;
		FBpxNodeResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Spawn a `UK2Node_CallFunction` node into a named K2 graph with deterministic\n\x09 * NodeGuid + pin IDs. Sibling of `AddBranchNode` shape; the delta is the\n\x09 * `FMemberReference` configuration step before `AllocateDefaultPins` \xe2\x80\x94 the\n\x09 * CallFunction's pins are signature-derived, so the reference MUST be set\n\x09 * prior to default-pin allocation for the correct pin set to materialise.\n\x09 *\n\x09 * `TargetClass == nullptr` routes to `FunctionReference.SetSelfMember(MemberName)`\n\x09 * \xe2\x80\x94 the member must resolve on the Blueprint's `GeneratedClass` (or an ancestor)\n\x09 * at compile time. `TargetClass != nullptr` routes to\n\x09 * `FunctionReference.SetExternalMember(MemberName, TargetClass)` \xe2\x80\x94 the member\n\x09 * must resolve on `TargetClass` (native `/Script/...` or BP-generated `*_C`).\n\x09 *\n\x09 * Idempotent on seeded NodeGuid (seed key includes member name + position so\n\x09 * two calls to the same function at different positions get distinct GUIDs).\n\x09 *\n\x09 * Thread: game-thread only.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spawn a `UK2Node_CallFunction` node into a named K2 graph with deterministic\nNodeGuid + pin IDs. Sibling of `AddBranchNode` shape; the delta is the\n`FMemberReference` configuration step before `AllocateDefaultPins` \xe2\x80\x94 the\nCallFunction's pins are signature-derived, so the reference MUST be set\nprior to default-pin allocation for the correct pin set to materialise.\n\n`TargetClass == nullptr` routes to `FunctionReference.SetSelfMember(MemberName)`\n\xe2\x80\x94 the member must resolve on the Blueprint's `GeneratedClass` (or an ancestor)\nat compile time. `TargetClass != nullptr` routes to\n`FunctionReference.SetExternalMember(MemberName, TargetClass)` \xe2\x80\x94 the member\nmust resolve on `TargetClass` (native `/Script/...` or BP-generated `*_C`).\n\nIdempotent on seeded NodeGuid (seed key includes member name + position so\ntwo calls to the same function at different positions get distinct GUIDs).\n\nThread: game-thread only." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AddCallFunctionNode constinit property declarations *******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_GraphName;
	static const UECodeGen_Private::FNamePropertyParams NewProp_MemberName;
	static const UECodeGen_Private::FClassPropertyParams NewProp_TargetClass;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddCallFunctionNode constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddCallFunctionNode Property Definitions ******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddCallFunctionNode_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::NewProp_GraphName = { "GraphName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddCallFunctionNode_Parms, GraphName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::NewProp_MemberName = { "MemberName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddCallFunctionNode_Parms, MemberName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::NewProp_TargetClass = { "TargetClass", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddCallFunctionNode_Parms, TargetClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddCallFunctionNode_Parms, Position), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddCallFunctionNode_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxNodeResult, METADATA_PARAMS(0, nullptr) }; // 685492501
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::NewProp_GraphName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::NewProp_MemberName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::NewProp_TargetClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::PropPointers) < 2048);
// ********** End Function AddCallFunctionNode Property Definitions ********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddCallFunctionNode", 	Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::BpxReflectionOps_eventAddCallFunctionNode_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04822401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::BpxReflectionOps_eventAddCallFunctionNode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddCallFunctionNode)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_GraphName);
	P_GET_PROPERTY(FNameProperty,Z_Param_MemberName);
	P_GET_OBJECT(UClass,Z_Param_TargetClass);
	P_GET_STRUCT(FVector2D,Z_Param_Position);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxNodeResult*)Z_Param__Result=UBpxReflectionOps::AddCallFunctionNode(Z_Param_Blueprint,Z_Param_GraphName,Z_Param_MemberName,Z_Param_TargetClass,Z_Param_Position);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddCallFunctionNode *****************************

// ********** Begin Class UBpxReflectionOps Function AddComponentToSCSDeterministic ****************
struct Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics
{
	struct BpxReflectionOps_eventAddComponentToSCSDeterministic_Parms
	{
		UBlueprint* Blueprint;
		UClass* ComponentClass;
		FName ComponentName;
		FName ParentComponentName;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Add a new component to a Blueprint's SimpleConstructionScript with a\n\x09 * deterministic USCS_Node::VariableGuid.\n\x09 *\n\x09 * Wraps `USimpleConstructionScript::CreateNode` (Engine module, already\n\x09 * linked \xe2\x80\x94 no new module dep) to close a silent determinism trap:\n\x09 * `CreateNodeImpl` (SimpleConstructionScript.cpp:1375) assigns\n\x09 * `NewNode->VariableGuid = FGuid::NewGuid()`. `USCS_Node::ValidateGuid`\n\x09 * only fires its name-hash seed path when `!VariableGuid.IsValid()` \xe2\x80\x94\n\x09 * since `CreateNodeImpl` just assigned a fresh GUID, that path is never\n\x09 * taken for freshly-created nodes. Every `add_component_to_scs` call\n\x09 * drifts the .uasset bytes without this override. Post-create we\n\x09 * overwrite `VariableGuid` with\n\x09 * `SeedGuidFromJoined(BlueprintPath + \":scs:\" + ComponentName)`,\n\x09 * mirroring the M28.2.1 VarGuid / M28.2.2 GraphGuid determinism recipe.\n\x09 *\n\x09 * Attachment: pass NAME_None (or an empty FName) for `ParentComponentName`\n\x09 * to add at SCS root. Otherwise we look up `ParentComponentName` via\n\x09 * `SCS->FindSCSNode` and attach via `USCS_Node::AddChildNode`. Parenting\n\x09 * to native (inherited-class-CDO) components isn't supported \xe2\x80\x94 the SCS\n\x09 * only tracks authored nodes, so a non-SCS parent returns a structured\n\x09 * error. This mirrors the editor's \"Add Child Component\" UX for SCS-only\n\x09 * parenting and keeps the op scope narrow.\n\x09 *\n\x09 * Idempotent: if `SCS->FindSCSNode(ComponentName)` finds an existing node\n\x09 * with the same `ComponentClass`, returns `bSuccess=true, bSkipped=true`\n\x09 * without touching the asset. Name-with-different-class collision is a\n\x09 * structured error. Requested-name-collides-with-inherited is also a\n\x09 * structured error (engine's `GenerateNewComponentName` would silently\n\x09 * append a counter suffix; rejecting up-front keeps plan replay crisp).\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.\n\x09 *\n\x09 * Thread: game-thread only. `FBlueprintEditorUtils::Mark\xe2\x80\xa6StructurallyModified`\n\x09 * and `USimpleConstructionScript::CreateNode` are editor-only and not\n\x09 * thread-safe.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Add a new component to a Blueprint's SimpleConstructionScript with a\ndeterministic USCS_Node::VariableGuid.\n\nWraps `USimpleConstructionScript::CreateNode` (Engine module, already\nlinked \xe2\x80\x94 no new module dep) to close a silent determinism trap:\n`CreateNodeImpl` (SimpleConstructionScript.cpp:1375) assigns\n`NewNode->VariableGuid = FGuid::NewGuid()`. `USCS_Node::ValidateGuid`\nonly fires its name-hash seed path when `!VariableGuid.IsValid()` \xe2\x80\x94\nsince `CreateNodeImpl` just assigned a fresh GUID, that path is never\ntaken for freshly-created nodes. Every `add_component_to_scs` call\ndrifts the .uasset bytes without this override. Post-create we\noverwrite `VariableGuid` with\n`SeedGuidFromJoined(BlueprintPath + \":scs:\" + ComponentName)`,\nmirroring the M28.2.1 VarGuid / M28.2.2 GraphGuid determinism recipe.\n\nAttachment: pass NAME_None (or an empty FName) for `ParentComponentName`\nto add at SCS root. Otherwise we look up `ParentComponentName` via\n`SCS->FindSCSNode` and attach via `USCS_Node::AddChildNode`. Parenting\nto native (inherited-class-CDO) components isn't supported \xe2\x80\x94 the SCS\nonly tracks authored nodes, so a non-SCS parent returns a structured\nerror. This mirrors the editor's \"Add Child Component\" UX for SCS-only\nparenting and keeps the op scope narrow.\n\nIdempotent: if `SCS->FindSCSNode(ComponentName)` finds an existing node\nwith the same `ComponentClass`, returns `bSuccess=true, bSkipped=true`\nwithout touching the asset. Name-with-different-class collision is a\nstructured error. Requested-name-collides-with-inherited is also a\nstructured error (engine's `GenerateNewComponentName` would silently\nappend a counter suffix; rejecting up-front keeps plan replay crisp).\n\nCaller is responsible for `CompileAndSavePackage(BP)` after the add.\n\nThread: game-thread only. `FBlueprintEditorUtils::Mark\xe2\x80\xa6StructurallyModified`\nand `USimpleConstructionScript::CreateNode` are editor-only and not\nthread-safe." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AddComponentToSCSDeterministic constinit property declarations ********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FClassPropertyParams NewProp_ComponentClass;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ComponentName;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ParentComponentName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddComponentToSCSDeterministic constinit property declarations **********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddComponentToSCSDeterministic Property Definitions *******************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddComponentToSCSDeterministic_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::NewProp_ComponentClass = { "ComponentClass", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddComponentToSCSDeterministic_Parms, ComponentClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::NewProp_ComponentName = { "ComponentName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddComponentToSCSDeterministic_Parms, ComponentName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::NewProp_ParentComponentName = { "ParentComponentName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddComponentToSCSDeterministic_Parms, ParentComponentName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddComponentToSCSDeterministic_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::NewProp_ComponentClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::NewProp_ComponentName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::NewProp_ParentComponentName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::PropPointers) < 2048);
// ********** End Function AddComponentToSCSDeterministic Property Definitions *********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddComponentToSCSDeterministic", 	Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::BpxReflectionOps_eventAddComponentToSCSDeterministic_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::BpxReflectionOps_eventAddComponentToSCSDeterministic_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddComponentToSCSDeterministic)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_OBJECT(UClass,Z_Param_ComponentClass);
	P_GET_PROPERTY(FNameProperty,Z_Param_ComponentName);
	P_GET_PROPERTY(FNameProperty,Z_Param_ParentComponentName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::AddComponentToSCSDeterministic(Z_Param_Blueprint,Z_Param_ComponentClass,Z_Param_ComponentName,Z_Param_ParentComponentName);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddComponentToSCSDeterministic ******************

// ********** Begin Class UBpxReflectionOps Function AddCustomEventNode ****************************
struct Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics
{
	struct BpxReflectionOps_eventAddCustomEventNode_Parms
	{
		UBlueprint* Blueprint;
		FName GraphName;
		FName EventName;
		FVector2D Position;
		FBpxNodeResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Spawn a `UK2Node_CustomEvent` node into an ubergraph with a deterministic\n\x09 * NodeGuid + pin IDs. CustomEvent is the event-channel entry point that\n\x09 * design.md's squad-director `AI.Order.*` channel rests on (item #1 + #4).\n\x09 *\n\x09 * Graph-type validation runs at op entry \xe2\x80\x94 `UEdGraphSchema::GetGraphType(G)\n\x09 * == GT_Ubergraph`. Any other graph family (function / interface override /\n\x09 * macro) returns a structured error rather than silently producing a node\n\x09 * that would fail at compile time. Mirrors the engine's own\n\x09 * `K2Node_Event::IsCompatibleWithGraph` check but surfaces it explicitly to\n\x09 * the plan author.\n\x09 *\n\x09 * `CustomFunctionName` (inherited from `UK2Node_Event`) is set BEFORE\n\x09 * `AllocateDefaultPins` so the generated delegate name + signature pins\n\x09 * resolve correctly. Seed key includes the event name + position so two\n\x09 * CustomEvents with the same name at different positions get distinct\n\x09 * GUIDs (useful during incremental authoring before a redundant second is\n\x09 * deleted).\n\x09 *\n\x09 * Default pins (from `UK2Node_Event::AllocateDefaultPins`): `OutputDelegate`\n\x09 * (delegate out, used by `Bind Event`), `then` (exec out). CustomEvents\n\x09 * that need parameters get them via subsequent UserDefinedPin-Add ops \xe2\x80\x94\n\x09 * out of M28.3.3 scope, deferred with the rest of M28.3.\n\x09 *\n\x09 * Idempotent on the seeded NodeGuid.\n\x09 *\n\x09 * Thread: game-thread only.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spawn a `UK2Node_CustomEvent` node into an ubergraph with a deterministic\nNodeGuid + pin IDs. CustomEvent is the event-channel entry point that\ndesign.md's squad-director `AI.Order.*` channel rests on (item #1 + #4).\n\nGraph-type validation runs at op entry \xe2\x80\x94 `UEdGraphSchema::GetGraphType(G)\n== GT_Ubergraph`. Any other graph family (function / interface override /\nmacro) returns a structured error rather than silently producing a node\nthat would fail at compile time. Mirrors the engine's own\n`K2Node_Event::IsCompatibleWithGraph` check but surfaces it explicitly to\nthe plan author.\n\n`CustomFunctionName` (inherited from `UK2Node_Event`) is set BEFORE\n`AllocateDefaultPins` so the generated delegate name + signature pins\nresolve correctly. Seed key includes the event name + position so two\nCustomEvents with the same name at different positions get distinct\nGUIDs (useful during incremental authoring before a redundant second is\ndeleted).\n\nDefault pins (from `UK2Node_Event::AllocateDefaultPins`): `OutputDelegate`\n(delegate out, used by `Bind Event`), `then` (exec out). CustomEvents\nthat need parameters get them via subsequent UserDefinedPin-Add ops \xe2\x80\x94\nout of M28.3.3 scope, deferred with the rest of M28.3.\n\nIdempotent on the seeded NodeGuid.\n\nThread: game-thread only." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AddCustomEventNode constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_GraphName;
	static const UECodeGen_Private::FNamePropertyParams NewProp_EventName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddCustomEventNode constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddCustomEventNode Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddCustomEventNode_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::NewProp_GraphName = { "GraphName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddCustomEventNode_Parms, GraphName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::NewProp_EventName = { "EventName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddCustomEventNode_Parms, EventName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddCustomEventNode_Parms, Position), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddCustomEventNode_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxNodeResult, METADATA_PARAMS(0, nullptr) }; // 685492501
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::NewProp_GraphName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::NewProp_EventName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::PropPointers) < 2048);
// ********** End Function AddCustomEventNode Property Definitions *********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddCustomEventNode", 	Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::BpxReflectionOps_eventAddCustomEventNode_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04822401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::BpxReflectionOps_eventAddCustomEventNode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddCustomEventNode)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_GraphName);
	P_GET_PROPERTY(FNameProperty,Z_Param_EventName);
	P_GET_STRUCT(FVector2D,Z_Param_Position);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxNodeResult*)Z_Param__Result=UBpxReflectionOps::AddCustomEventNode(Z_Param_Blueprint,Z_Param_GraphName,Z_Param_EventName,Z_Param_Position);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddCustomEventNode ******************************

// ********** Begin Class UBpxReflectionOps Function AddDynamicCastNode ****************************
struct Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics
{
	struct BpxReflectionOps_eventAddDynamicCastNode_Parms
	{
		UBlueprint* Blueprint;
		FName GraphName;
		UClass* TargetClass;
		FVector2D Position;
		FBpxNodeResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Spawn a `UK2Node_DynamicCast` node into a K2 graph with a deterministic\n\x09 * NodeGuid + pin IDs. DynamicCast routes `ObjectToCast` input through the\n\x09 * `CastSucceeded` / `CastFailed` exec outputs based on an IsA check\n\x09 * against `TargetClass`, exposing the cast object as the typed `As<X>`\n\x09 * pin. Design.md driver: utility scorer action resolution (item #2 \xe2\x80\x94\n\x09 * cast from generic `AActor*` target to specific archetype classes for\n\x09 * per-archetype scoring hooks) and callouts (item #4 \xe2\x80\x94 cast ally ref to\n\x09 * `BP_EnemyBase` to test faction before broadcasting the callout).\n\x09 *\n\x09 * `TargetType` (UPROPERTY `TSubclassOf<UObject>`) MUST be set before\n\x09 * `AllocateDefaultPins` \xe2\x80\x94 the typed `As<TargetClass>` output pin's\n\x09 * `PinCategory` / `PinSubCategoryObject` are derived from `TargetType`\n\x09 * inside `UK2Node_DynamicCast::CreatePinsForCastNode`. Post-alloc sets\n\x09 * would leave the output pin as a wildcard and break downstream wiring.\n\x09 *\n\x09 * `TargetClass == nullptr` is a structured error (impossible node shape).\n\x09 * `PureState` stays at its `UseDefault` resolution (impure by default \xe2\x80\x94\n\x09 * three exec pins + bSuccess output). A `bIsPureCast` param could expose\n\x09 * `UK2Node_DynamicCast::SetPurity`; deferred until a driver surfaces.\n\x09 *\n\x09 * Idempotent on seeded NodeGuid (seed includes `TargetClass` path +\n\x09 * position so two casts to different classes at the same spot get distinct\n\x09 * GUIDs).\n\x09 *\n\x09 * Thread: game-thread only.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spawn a `UK2Node_DynamicCast` node into a K2 graph with a deterministic\nNodeGuid + pin IDs. DynamicCast routes `ObjectToCast` input through the\n`CastSucceeded` / `CastFailed` exec outputs based on an IsA check\nagainst `TargetClass`, exposing the cast object as the typed `As<X>`\npin. Design.md driver: utility scorer action resolution (item #2 \xe2\x80\x94\ncast from generic `AActor*` target to specific archetype classes for\nper-archetype scoring hooks) and callouts (item #4 \xe2\x80\x94 cast ally ref to\n`BP_EnemyBase` to test faction before broadcasting the callout).\n\n`TargetType` (UPROPERTY `TSubclassOf<UObject>`) MUST be set before\n`AllocateDefaultPins` \xe2\x80\x94 the typed `As<TargetClass>` output pin's\n`PinCategory` / `PinSubCategoryObject` are derived from `TargetType`\ninside `UK2Node_DynamicCast::CreatePinsForCastNode`. Post-alloc sets\nwould leave the output pin as a wildcard and break downstream wiring.\n\n`TargetClass == nullptr` is a structured error (impossible node shape).\n`PureState` stays at its `UseDefault` resolution (impure by default \xe2\x80\x94\nthree exec pins + bSuccess output). A `bIsPureCast` param could expose\n`UK2Node_DynamicCast::SetPurity`; deferred until a driver surfaces.\n\nIdempotent on seeded NodeGuid (seed includes `TargetClass` path +\nposition so two casts to different classes at the same spot get distinct\nGUIDs).\n\nThread: game-thread only." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AddDynamicCastNode constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_GraphName;
	static const UECodeGen_Private::FClassPropertyParams NewProp_TargetClass;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddDynamicCastNode constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddDynamicCastNode Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddDynamicCastNode_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::NewProp_GraphName = { "GraphName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddDynamicCastNode_Parms, GraphName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::NewProp_TargetClass = { "TargetClass", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddDynamicCastNode_Parms, TargetClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddDynamicCastNode_Parms, Position), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddDynamicCastNode_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxNodeResult, METADATA_PARAMS(0, nullptr) }; // 685492501
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::NewProp_GraphName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::NewProp_TargetClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::PropPointers) < 2048);
// ********** End Function AddDynamicCastNode Property Definitions *********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddDynamicCastNode", 	Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::BpxReflectionOps_eventAddDynamicCastNode_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04822401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::BpxReflectionOps_eventAddDynamicCastNode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddDynamicCastNode)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_GraphName);
	P_GET_OBJECT(UClass,Z_Param_TargetClass);
	P_GET_STRUCT(FVector2D,Z_Param_Position);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxNodeResult*)Z_Param__Result=UBpxReflectionOps::AddDynamicCastNode(Z_Param_Blueprint,Z_Param_GraphName,Z_Param_TargetClass,Z_Param_Position);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddDynamicCastNode ******************************

// ********** Begin Class UBpxReflectionOps Function AddEnvQueryOption *****************************
struct Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryOption_Statics
{
	struct BpxReflectionOps_eventAddEnvQueryOption_Parms
	{
		UEnvQuery* Query;
		UClass* GeneratorClass;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Append a new `UEnvQueryOption` to a `UEnvQuery`'s Options array with its\n\x09 * generator set to a fresh `NewObject<UEnvQueryGenerator>(GeneratorClass)`\n\x09 * owned by the option. First op of the M28.5 EQS write-side catalog.\n\x09 *\n\x09 * Scope: creates the option + the generator in one call. M28.5.2 will\n\x09 * extend with per-test add/remove via a sibling op; scalar property edits\n\x09 * on a generator or test reuse the existing `SetPropertyValue` bridge\n\x09 * against a path like `[\"Options\", \"[N]\", \"Generator\", \"UPROPERTYName\"]`.\n\x09 *\n\x09 * `GeneratorClass` must be a concrete, non-abstract subclass of\n\x09 * `UEnvQueryGenerator`. Abstract classes (including the base itself) are\n\x09 * rejected with a structured error \xe2\x80\x94 `NewObject` on an abstract class\n\x09 * throws an uncatchable check() at runtime, so the pre-validation keeps\n\x09 * plan replay crisp.\n\x09 *\n\x09 * Determinism: EQS classes have zero `FGuid::NewGuid()` usage (grep-\n\x09 * confirmed during M28.5.0 research), so the only drift source is\n\x09 * `NewObject`'s default name generation \xe2\x80\x94 a counter-suffixed\n\x09 * `EnvQueryOption_0` / `EnvQueryOption_1` / etc. that depends on whatever\n\x09 * else has been allocated in the current editor session. Each `NewObject`\n\x09 * gets an explicit `FName` in `BpxEqsOption_<idx>` / `BpxEqsGen_<idx>`\n\x09 * form so replays across fresh editor shells produce byte-identical\n\x09 * output. `idx` is the pre-insert `Options.Num()` value so sequential\n\x09 * calls get monotonically-increasing names.\n\x09 *\n\x09 * Idempotent on `(Query, GeneratorClass)`: walks existing options and\n\x09 * returns `bSuccess=true, bSkipped=true` with the matching index in\n\x09 * `AfterText` if any option's `Generator->GetClass() == GeneratorClass`.\n\x09 * Option author can tune the generator's per-UPROPERTY values via\n\x09 * `SetPropertyValue` on `[\"Options\", \"[N]\", \"Generator\", ...]` without\n\x09 * re-triggering the creation path.\n\x09 *\n\x09 * Result shape:\n\x09 *   BeforeText: `\"options=<N>\"` (pre-add count)\n\x09 *   AfterText:  `\"<new_option_index>\"` (0-based) \xe2\x80\x94 both on create and skip\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(Query)` after the add.\n\x09 *\n\x09 * Thread: game-thread only. `NewObject` + `UPackage::SetDirtyFlag` are\n\x09 * editor-safe on the game thread and not thread-safe off it.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Append a new `UEnvQueryOption` to a `UEnvQuery`'s Options array with its\ngenerator set to a fresh `NewObject<UEnvQueryGenerator>(GeneratorClass)`\nowned by the option. First op of the M28.5 EQS write-side catalog.\n\nScope: creates the option + the generator in one call. M28.5.2 will\nextend with per-test add/remove via a sibling op; scalar property edits\non a generator or test reuse the existing `SetPropertyValue` bridge\nagainst a path like `[\"Options\", \"[N]\", \"Generator\", \"UPROPERTYName\"]`.\n\n`GeneratorClass` must be a concrete, non-abstract subclass of\n`UEnvQueryGenerator`. Abstract classes (including the base itself) are\nrejected with a structured error \xe2\x80\x94 `NewObject` on an abstract class\nthrows an uncatchable check() at runtime, so the pre-validation keeps\nplan replay crisp.\n\nDeterminism: EQS classes have zero `FGuid::NewGuid()` usage (grep-\nconfirmed during M28.5.0 research), so the only drift source is\n`NewObject`'s default name generation \xe2\x80\x94 a counter-suffixed\n`EnvQueryOption_0` / `EnvQueryOption_1` / etc. that depends on whatever\nelse has been allocated in the current editor session. Each `NewObject`\ngets an explicit `FName` in `BpxEqsOption_<idx>` / `BpxEqsGen_<idx>`\nform so replays across fresh editor shells produce byte-identical\noutput. `idx` is the pre-insert `Options.Num()` value so sequential\ncalls get monotonically-increasing names.\n\nIdempotent on `(Query, GeneratorClass)`: walks existing options and\nreturns `bSuccess=true, bSkipped=true` with the matching index in\n`AfterText` if any option's `Generator->GetClass() == GeneratorClass`.\nOption author can tune the generator's per-UPROPERTY values via\n`SetPropertyValue` on `[\"Options\", \"[N]\", \"Generator\", ...]` without\nre-triggering the creation path.\n\nResult shape:\n  BeforeText: `\"options=<N>\"` (pre-add count)\n  AfterText:  `\"<new_option_index>\"` (0-based) \xe2\x80\x94 both on create and skip\n\nCaller is responsible for `CompileAndSavePackage(Query)` after the add.\n\nThread: game-thread only. `NewObject` + `UPackage::SetDirtyFlag` are\neditor-safe on the game thread and not thread-safe off it." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AddEnvQueryOption constinit property declarations *********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Query;
	static const UECodeGen_Private::FClassPropertyParams NewProp_GeneratorClass;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddEnvQueryOption constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddEnvQueryOption Property Definitions ********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryOption_Statics::NewProp_Query = { "Query", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddEnvQueryOption_Parms, Query), Z_Construct_UClass_UEnvQuery_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryOption_Statics::NewProp_GeneratorClass = { "GeneratorClass", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddEnvQueryOption_Parms, GeneratorClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryOption_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddEnvQueryOption_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryOption_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryOption_Statics::NewProp_Query,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryOption_Statics::NewProp_GeneratorClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryOption_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryOption_Statics::PropPointers) < 2048);
// ********** End Function AddEnvQueryOption Property Definitions **********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryOption_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddEnvQueryOption", 	Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryOption_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryOption_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryOption_Statics::BpxReflectionOps_eventAddEnvQueryOption_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryOption_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryOption_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryOption_Statics::BpxReflectionOps_eventAddEnvQueryOption_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryOption()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryOption_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddEnvQueryOption)
{
	P_GET_OBJECT(UEnvQuery,Z_Param_Query);
	P_GET_OBJECT(UClass,Z_Param_GeneratorClass);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::AddEnvQueryOption(Z_Param_Query,Z_Param_GeneratorClass);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddEnvQueryOption *******************************

// ********** Begin Class UBpxReflectionOps Function AddEnvQueryTest *******************************
struct Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest_Statics
{
	struct BpxReflectionOps_eventAddEnvQueryTest_Parms
	{
		UEnvQuery* Query;
		int32 OptionIndex;
		UClass* TestClass;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Append a new `UEnvQueryTest` subclass instance to the `Tests[]` array on\n\x09 * `UEnvQuery::Options[OptionIndex]`. Second op of the M28.5 EQS write-side\n\x09 * catalog; builds on M28.5.1's option-level shape.\n\x09 *\n\x09 * `TestClass` must be a concrete, non-abstract subclass of `UEnvQueryTest`.\n\x09 * The base `UEnvQueryTest` is `UCLASS(Abstract)` so the abstract check\n\x09 * rejects the base itself in addition to any abstract intermediates.\n\x09 *\n\x09 * Determinism: like M28.5.1, explicit `FName` on `NewObject` \xe2\x80\x94 pattern\n\x09 * `BpxEqsTest_<option_index>_<pre_test_count>_<TestClassShortName>`. Option\n\x09 * index is part of the name so two options carrying the same test class\n\x09 * don't collide in the package's FName table. EQS classes have zero\n\x09 * `FGuid::NewGuid()` usage per M28.5.0 research so the counter-suffix is\n\x09 * the only drift source.\n\x09 *\n\x09 * `TestOrder` invariant: `EnvQueryManager.cpp:874` only repairs the order\n\x09 * at runtime when it is zero; the editor must assign it sequentially as\n\x09 * tests are added. Post-append assigns `NewTest->TestOrder = PreCount`\n\x09 * so the `0..N-1` ordering holds. `RemoveEnvQueryTest` reseats the tail\n\x09 * to preserve the same invariant on delete.\n\x09 *\n\x09 * Idempotent on `(Query, OptionIndex, TestClass)`: walks `Option->Tests[]`\n\x09 * and returns `bSuccess=true, bSkipped=true` with the matching index in\n\x09 * `AfterText` if any test is an exact-class match. Plan authors tune\n\x09 * per-UPROPERTY values via `SetPropertyValue` on\n\x09 * `[\"Options\", \"[N]\", \"Tests\", \"[M]\", \"...\"]`.\n\x09 *\n\x09 * Result shape:\n\x09 *   BeforeText: `\"tests=<N>\"` (pre-add count on the target option)\n\x09 *   AfterText:  `\"<new_test_index>\"` \xe2\x80\x94 both on create and skip\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(Query)` after the add.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Append a new `UEnvQueryTest` subclass instance to the `Tests[]` array on\n`UEnvQuery::Options[OptionIndex]`. Second op of the M28.5 EQS write-side\ncatalog; builds on M28.5.1's option-level shape.\n\n`TestClass` must be a concrete, non-abstract subclass of `UEnvQueryTest`.\nThe base `UEnvQueryTest` is `UCLASS(Abstract)` so the abstract check\nrejects the base itself in addition to any abstract intermediates.\n\nDeterminism: like M28.5.1, explicit `FName` on `NewObject` \xe2\x80\x94 pattern\n`BpxEqsTest_<option_index>_<pre_test_count>_<TestClassShortName>`. Option\nindex is part of the name so two options carrying the same test class\ndon't collide in the package's FName table. EQS classes have zero\n`FGuid::NewGuid()` usage per M28.5.0 research so the counter-suffix is\nthe only drift source.\n\n`TestOrder` invariant: `EnvQueryManager.cpp:874` only repairs the order\nat runtime when it is zero; the editor must assign it sequentially as\ntests are added. Post-append assigns `NewTest->TestOrder = PreCount`\nso the `0..N-1` ordering holds. `RemoveEnvQueryTest` reseats the tail\nto preserve the same invariant on delete.\n\nIdempotent on `(Query, OptionIndex, TestClass)`: walks `Option->Tests[]`\nand returns `bSuccess=true, bSkipped=true` with the matching index in\n`AfterText` if any test is an exact-class match. Plan authors tune\nper-UPROPERTY values via `SetPropertyValue` on\n`[\"Options\", \"[N]\", \"Tests\", \"[M]\", \"...\"]`.\n\nResult shape:\n  BeforeText: `\"tests=<N>\"` (pre-add count on the target option)\n  AfterText:  `\"<new_test_index>\"` \xe2\x80\x94 both on create and skip\n\nCaller is responsible for `CompileAndSavePackage(Query)` after the add." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AddEnvQueryTest constinit property declarations ***********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Query;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OptionIndex;
	static const UECodeGen_Private::FClassPropertyParams NewProp_TestClass;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddEnvQueryTest constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddEnvQueryTest Property Definitions **********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest_Statics::NewProp_Query = { "Query", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddEnvQueryTest_Parms, Query), Z_Construct_UClass_UEnvQuery_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest_Statics::NewProp_OptionIndex = { "OptionIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddEnvQueryTest_Parms, OptionIndex), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest_Statics::NewProp_TestClass = { "TestClass", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddEnvQueryTest_Parms, TestClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddEnvQueryTest_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest_Statics::NewProp_Query,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest_Statics::NewProp_OptionIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest_Statics::NewProp_TestClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest_Statics::PropPointers) < 2048);
// ********** End Function AddEnvQueryTest Property Definitions ************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddEnvQueryTest", 	Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest_Statics::BpxReflectionOps_eventAddEnvQueryTest_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest_Statics::BpxReflectionOps_eventAddEnvQueryTest_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddEnvQueryTest)
{
	P_GET_OBJECT(UEnvQuery,Z_Param_Query);
	P_GET_PROPERTY(FIntProperty,Z_Param_OptionIndex);
	P_GET_OBJECT(UClass,Z_Param_TestClass);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::AddEnvQueryTest(Z_Param_Query,Z_Param_OptionIndex,Z_Param_TestClass);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddEnvQueryTest *********************************

// ********** Begin Class UBpxReflectionOps Function AddExecutionSequenceNode **********************
struct Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics
{
	struct BpxReflectionOps_eventAddExecutionSequenceNode_Parms
	{
		UBlueprint* Blueprint;
		FName GraphName;
		int32 NumOutputs;
		FVector2D Position;
		FBpxNodeResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Spawn a `UK2Node_ExecutionSequence` node into a K2 graph with a\n\x09 * deterministic NodeGuid + pin IDs. ExecutionSequence chains N `Then_N`\n\x09 * exec outputs off a single `execute` input, firing them in order.\n\x09 * Design.md driver: polish-pass sequencing (item #8 \xe2\x80\x94 hit reactions\n\x09 * followed by ally-down reactions) and callout broadcasts (item #4).\n\x09 *\n\x09 * `NumOutputs` controls the final output-pin count. The engine's default\n\x09 * `AllocateDefaultPins` produces `Then_0` + `Then_1`; we call\n\x09 * `IK2Node_AddPinInterface::AddInputPin` (misleading name \xe2\x80\x94 it adds a new\n\x09 * Then_N **output** pin, not an input) `NumOutputs - 2` times so the node\n\x09 * lands with the requested shape. `NumOutputs < 2` is a structured error\n\x09 * (UE's ExecutionSequence requires at least two outputs to justify its\n\x09 * existence; one-output sequences should be authored as direct wires).\n\x09 * `NumOutputs > 16` is also rejected as a sanity cap; expand if a real\n\x09 * driver appears.\n\x09 *\n\x09 * `SeedPinGuidsForNode` fires AFTER the AddInputPin loop so every final\n\x09 * pin (including the extended Then_2+) gets a deterministic PinId.\n\x09 *\n\x09 * Idempotent on seeded NodeGuid (seed includes NumOutputs + position so\n\x09 * two calls with different output counts at the same position get distinct\n\x09 * GUIDs).\n\x09 *\n\x09 * Thread: game-thread only.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spawn a `UK2Node_ExecutionSequence` node into a K2 graph with a\ndeterministic NodeGuid + pin IDs. ExecutionSequence chains N `Then_N`\nexec outputs off a single `execute` input, firing them in order.\nDesign.md driver: polish-pass sequencing (item #8 \xe2\x80\x94 hit reactions\nfollowed by ally-down reactions) and callout broadcasts (item #4).\n\n`NumOutputs` controls the final output-pin count. The engine's default\n`AllocateDefaultPins` produces `Then_0` + `Then_1`; we call\n`IK2Node_AddPinInterface::AddInputPin` (misleading name \xe2\x80\x94 it adds a new\nThen_N **output** pin, not an input) `NumOutputs - 2` times so the node\nlands with the requested shape. `NumOutputs < 2` is a structured error\n(UE's ExecutionSequence requires at least two outputs to justify its\nexistence; one-output sequences should be authored as direct wires).\n`NumOutputs > 16` is also rejected as a sanity cap; expand if a real\ndriver appears.\n\n`SeedPinGuidsForNode` fires AFTER the AddInputPin loop so every final\npin (including the extended Then_2+) gets a deterministic PinId.\n\nIdempotent on seeded NodeGuid (seed includes NumOutputs + position so\ntwo calls with different output counts at the same position get distinct\nGUIDs).\n\nThread: game-thread only." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AddExecutionSequenceNode constinit property declarations **************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_GraphName;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NumOutputs;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddExecutionSequenceNode constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddExecutionSequenceNode Property Definitions *************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddExecutionSequenceNode_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::NewProp_GraphName = { "GraphName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddExecutionSequenceNode_Parms, GraphName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::NewProp_NumOutputs = { "NumOutputs", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddExecutionSequenceNode_Parms, NumOutputs), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddExecutionSequenceNode_Parms, Position), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddExecutionSequenceNode_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxNodeResult, METADATA_PARAMS(0, nullptr) }; // 685492501
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::NewProp_GraphName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::NewProp_NumOutputs,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::PropPointers) < 2048);
// ********** End Function AddExecutionSequenceNode Property Definitions ***************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddExecutionSequenceNode", 	Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::BpxReflectionOps_eventAddExecutionSequenceNode_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04822401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::BpxReflectionOps_eventAddExecutionSequenceNode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddExecutionSequenceNode)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_GraphName);
	P_GET_PROPERTY(FIntProperty,Z_Param_NumOutputs);
	P_GET_STRUCT(FVector2D,Z_Param_Position);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxNodeResult*)Z_Param__Result=UBpxReflectionOps::AddExecutionSequenceNode(Z_Param_Blueprint,Z_Param_GraphName,Z_Param_NumOutputs,Z_Param_Position);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddExecutionSequenceNode ************************

// ********** Begin Class UBpxReflectionOps Function AddFunctionGraphDeterministic *****************
struct Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics
{
	struct BpxReflectionOps_eventAddFunctionGraphDeterministic_Parms
	{
		UBlueprint* Blueprint;
		FName FunctionName;
		bool bIsPure;
		FBpxGraphEndpoints ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Add a new (blank) function graph to a Blueprint with deterministic\n\x09 * GraphGuid + Entry/Return NodeGuids + pin IDs.\n\x09 *\n\x09 * Mirrors `UBlueprintEditorLibrary::AddFunctionGraph` but closes three\n\x09 * silent determinism traps the engine path leaves open:\n\x09 *   1. `UEdGraph::PostInitProperties` (EdGraph.cpp:147) assigns\n\x09 *      `GraphGuid = FGuid::NewGuid()` \xe2\x80\x94 every call drifts the .uasset\n\x09 *      bytes. Overwritten via\n\x09 *      `SeedGuidFromJoined(BlueprintPath + \":func:\" + FunctionName + \":graph\")`.\n\x09 *   2. `UK2Node_FunctionEntry::CreateNewGuid` + `UK2Node_FunctionResult\n\x09 *      ::CreateNewGuid` each produce random NodeGuids. Overwritten via\n\x09 *      the same seeding pattern used by M26.1 `OverrideInterfaceFunction`\n\x09 *      so the Entry/Return pair is byte-stable across re-runs.\n\x09 *   3. Pin IDs on Entry + Return default-created pins are\n\x09 *      `FGuid::NewGuid()`-randomized. `SeedPinGuidsForNode` replays the\n\x09 *      M26.1.2 recipe per pin so the package FNameMap / export table\n\x09 *      lands identically round-to-round.\n\x09 *\n\x09 * Returns `FBpxGraphEndpoints` populated with Entry / Return NodeGuids so\n\x09 * callers immediately chain M26.1 body-authoring ops (AddSelfMemberGetNode,\n\x09 * ConnectPinsByName, SetNodePinLiteralDefault) by GUID. ReturnGuid is\n\x09 * valid \xe2\x80\x94 a blank non-pure function always gets both nodes.\n\x09 *\n\x09 * `bIsPure` flips `UK2Node_FunctionEntry::MetaData.bIsPureFunc` after the\n\x09 * graph is authored. Note: a pure function with no outputs WILL NOT\n\x09 * compile cleanly; pair pure=true with a subsequent variable add / Return\n\x09 * wire-up before calling CompileAndSavePackage.\n\x09 *\n\x09 * Idempotent: if a function graph named `FunctionName` already exists on\n\x09 * `Blueprint->FunctionGraphs` / `ImplementedInterfaces[].Graphs` /\n\x09 * `UbergraphPages`, returns `bSuccess=true, bSkipped=true` with the\n\x09 * existing graph's Entry/Return GUIDs so chained ops still work.\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.\n\x09 *\n\x09 * Thread: game-thread only. `FBlueprintEditorUtils::CreateNewGraph` +\n\x09 * `AddFunctionGraph` are editor-only and not thread-safe.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Add a new (blank) function graph to a Blueprint with deterministic\nGraphGuid + Entry/Return NodeGuids + pin IDs.\n\nMirrors `UBlueprintEditorLibrary::AddFunctionGraph` but closes three\nsilent determinism traps the engine path leaves open:\n  1. `UEdGraph::PostInitProperties` (EdGraph.cpp:147) assigns\n     `GraphGuid = FGuid::NewGuid()` \xe2\x80\x94 every call drifts the .uasset\n     bytes. Overwritten via\n     `SeedGuidFromJoined(BlueprintPath + \":func:\" + FunctionName + \":graph\")`.\n  2. `UK2Node_FunctionEntry::CreateNewGuid` + `UK2Node_FunctionResult\n     ::CreateNewGuid` each produce random NodeGuids. Overwritten via\n     the same seeding pattern used by M26.1 `OverrideInterfaceFunction`\n     so the Entry/Return pair is byte-stable across re-runs.\n  3. Pin IDs on Entry + Return default-created pins are\n     `FGuid::NewGuid()`-randomized. `SeedPinGuidsForNode` replays the\n     M26.1.2 recipe per pin so the package FNameMap / export table\n     lands identically round-to-round.\n\nReturns `FBpxGraphEndpoints` populated with Entry / Return NodeGuids so\ncallers immediately chain M26.1 body-authoring ops (AddSelfMemberGetNode,\nConnectPinsByName, SetNodePinLiteralDefault) by GUID. ReturnGuid is\nvalid \xe2\x80\x94 a blank non-pure function always gets both nodes.\n\n`bIsPure` flips `UK2Node_FunctionEntry::MetaData.bIsPureFunc` after the\ngraph is authored. Note: a pure function with no outputs WILL NOT\ncompile cleanly; pair pure=true with a subsequent variable add / Return\nwire-up before calling CompileAndSavePackage.\n\nIdempotent: if a function graph named `FunctionName` already exists on\n`Blueprint->FunctionGraphs` / `ImplementedInterfaces[].Graphs` /\n`UbergraphPages`, returns `bSuccess=true, bSkipped=true` with the\nexisting graph's Entry/Return GUIDs so chained ops still work.\n\nCaller is responsible for `CompileAndSavePackage(BP)` after the add.\n\nThread: game-thread only. `FBlueprintEditorUtils::CreateNewGraph` +\n`AddFunctionGraph` are editor-only and not thread-safe." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AddFunctionGraphDeterministic constinit property declarations *********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_FunctionName;
	static void NewProp_bIsPure_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsPure;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddFunctionGraphDeterministic constinit property declarations ***********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddFunctionGraphDeterministic Property Definitions ********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddFunctionGraphDeterministic_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::NewProp_FunctionName = { "FunctionName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddFunctionGraphDeterministic_Parms, FunctionName), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::NewProp_bIsPure_SetBit(void* Obj)
{
	((BpxReflectionOps_eventAddFunctionGraphDeterministic_Parms*)Obj)->bIsPure = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::NewProp_bIsPure = { "bIsPure", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(BpxReflectionOps_eventAddFunctionGraphDeterministic_Parms), &Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::NewProp_bIsPure_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddFunctionGraphDeterministic_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxGraphEndpoints, METADATA_PARAMS(0, nullptr) }; // 39012202
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::NewProp_FunctionName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::NewProp_bIsPure,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::PropPointers) < 2048);
// ********** End Function AddFunctionGraphDeterministic Property Definitions **********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddFunctionGraphDeterministic", 	Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::BpxReflectionOps_eventAddFunctionGraphDeterministic_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::BpxReflectionOps_eventAddFunctionGraphDeterministic_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddFunctionGraphDeterministic)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_FunctionName);
	P_GET_UBOOL(Z_Param_bIsPure);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxGraphEndpoints*)Z_Param__Result=UBpxReflectionOps::AddFunctionGraphDeterministic(Z_Param_Blueprint,Z_Param_FunctionName,Z_Param_bIsPure);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddFunctionGraphDeterministic *******************

// ********** Begin Class UBpxReflectionOps Function AddFunctionOverrideDeterministic **************
struct Z_Construct_UFunction_UBpxReflectionOps_AddFunctionOverrideDeterministic_Statics
{
	struct BpxReflectionOps_eventAddFunctionOverrideDeterministic_Parms
	{
		UBlueprint* Blueprint;
		FName FunctionName;
		FBpxGraphEndpoints ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Author a function-graph override of a native virtual UFUNCTION inherited\n\x09 * from `Blueprint->ParentClass` (or any ancestor in the parent chain).\n\x09 * Different code path from `AddFunctionGraphDeterministic` (fresh void/void\n\x09 * function) and `OverrideInterfaceFunction` (interface override) \xe2\x80\x94 this\n\x09 * one targets `BlueprintImplementableEvent` / `BlueprintNativeEvent`\n\x09 * UFUNCTIONs declared on the parent native class hierarchy.\n\x09 *\n\x09 * Driver: design.md MCP-only test against UE_DOW_Legacy\n\x09 * (`UEnvQueryTest_BlueprintBase::ReceiveTestCondition` override). Pre-M28.12\n\x09 * the only authoring surface was `add_bp_function`, which always created a\n\x09 * fresh void/void function \xe2\x80\x94 wrong shape when the user wanted to override\n\x09 * an inherited virtual.\n\x09 *\n\x09 * Resolution: `Blueprint->ParentClass->FindFunctionByName(FunctionName)`\n\x09 * walks the inheritance chain (engine helper handles \"this class or any\n\x09 * ancestor\"). The resolved `UFunction` must have the `FUNC_BlueprintEvent`\n\x09 * flag (else the function isn't user-overridable from a BP \xe2\x80\x94 refusing\n\x09 * here matches the BP editor's \"Override Function\" menu visibility).\n\x09 *\n\x09 * Engine call: `FBlueprintEditorUtils::AddFunctionGraph<UClass>(BP, NewGraph,\n\x09 * bIsUserCreated=false, ParentClass)` \xe2\x80\x94 same template variant as\n\x09 * `OverrideInterfaceFunction`, with `ParentClass` standing in for the\n\x09 * interface class. UE walks the class for a matching-name UFUNCTION and\n\x09 * uses its signature to build the Entry node's pins. `bIsUserCreated=false`\n\x09 * because this is an override, not a new user function \xe2\x80\x94 the editor's\n\x09 * function-list panel groups it under \"Override Functions\" via that flag.\n\x09 *\n\x09 * Result-node spawn: same logic as `OverrideInterfaceFunction` \xe2\x80\x94\n\x09 * `AddFunctionGraph<UClass>` only spawns Entry by default; if the parent\n\x09 * UFUNCTION has any output / return parameter, we spawn a Result node\n\x09 * inline (named deterministically as `BpxFuncResult_<FunctionName>`) so\n\x09 * `Get.<var>.OUT \xe2\x86\x92 Return.<pin>.IN` wiring works without a separate\n\x09 * \"spawn Result\" step.\n\x09 *\n\x09 * Idempotence: short-circuits on `FindFunctionGraphByName` match. Mirrors\n\x09 * `AddFunctionGraphDeterministic` \xe2\x80\x94 silent skip on existing graph; the\n\x09 * caller's body-authoring ops chain off the returned `EntryGuid` /\n\x09 * `ReturnGuid`.\n\x09 *\n\x09 * Determinism: `GraphGuid` + Entry/Result `NodeGuid` + pin IDs seeded via\n\x09 * `SeedGuidFromJoined(<bp>:override_func:<fn>:<slot>)`. Distinct prefix\n\x09 * (`override_func` vs fresh-function `func`) so a name collision between\n\x09 * a fresh function and an override on the same BP \xe2\x80\x94 illegal at compile\n\x09 * time, but possible mid-authoring \xe2\x80\x94 produces distinct seeds.\n\x09 *\n\x09 * Calls `MarkBlueprintAsStructurallyModified` on the success path.\n\x09 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.\n\x09 *\n\x09 * Thread: game-thread only.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Author a function-graph override of a native virtual UFUNCTION inherited\nfrom `Blueprint->ParentClass` (or any ancestor in the parent chain).\nDifferent code path from `AddFunctionGraphDeterministic` (fresh void/void\nfunction) and `OverrideInterfaceFunction` (interface override) \xe2\x80\x94 this\none targets `BlueprintImplementableEvent` / `BlueprintNativeEvent`\nUFUNCTIONs declared on the parent native class hierarchy.\n\nDriver: design.md MCP-only test against UE_DOW_Legacy\n(`UEnvQueryTest_BlueprintBase::ReceiveTestCondition` override). Pre-M28.12\nthe only authoring surface was `add_bp_function`, which always created a\nfresh void/void function \xe2\x80\x94 wrong shape when the user wanted to override\nan inherited virtual.\n\nResolution: `Blueprint->ParentClass->FindFunctionByName(FunctionName)`\nwalks the inheritance chain (engine helper handles \"this class or any\nancestor\"). The resolved `UFunction` must have the `FUNC_BlueprintEvent`\nflag (else the function isn't user-overridable from a BP \xe2\x80\x94 refusing\nhere matches the BP editor's \"Override Function\" menu visibility).\n\nEngine call: `FBlueprintEditorUtils::AddFunctionGraph<UClass>(BP, NewGraph,\nbIsUserCreated=false, ParentClass)` \xe2\x80\x94 same template variant as\n`OverrideInterfaceFunction`, with `ParentClass` standing in for the\ninterface class. UE walks the class for a matching-name UFUNCTION and\nuses its signature to build the Entry node's pins. `bIsUserCreated=false`\nbecause this is an override, not a new user function \xe2\x80\x94 the editor's\nfunction-list panel groups it under \"Override Functions\" via that flag.\n\nResult-node spawn: same logic as `OverrideInterfaceFunction` \xe2\x80\x94\n`AddFunctionGraph<UClass>` only spawns Entry by default; if the parent\nUFUNCTION has any output / return parameter, we spawn a Result node\ninline (named deterministically as `BpxFuncResult_<FunctionName>`) so\n`Get.<var>.OUT \xe2\x86\x92 Return.<pin>.IN` wiring works without a separate\n\"spawn Result\" step.\n\nIdempotence: short-circuits on `FindFunctionGraphByName` match. Mirrors\n`AddFunctionGraphDeterministic` \xe2\x80\x94 silent skip on existing graph; the\ncaller's body-authoring ops chain off the returned `EntryGuid` /\n`ReturnGuid`.\n\nDeterminism: `GraphGuid` + Entry/Result `NodeGuid` + pin IDs seeded via\n`SeedGuidFromJoined(<bp>:override_func:<fn>:<slot>)`. Distinct prefix\n(`override_func` vs fresh-function `func`) so a name collision between\na fresh function and an override on the same BP \xe2\x80\x94 illegal at compile\ntime, but possible mid-authoring \xe2\x80\x94 produces distinct seeds.\n\nCalls `MarkBlueprintAsStructurallyModified` on the success path.\nCaller is responsible for `CompileAndSavePackage(BP)` after the add.\n\nThread: game-thread only." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AddFunctionOverrideDeterministic constinit property declarations ******
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_FunctionName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddFunctionOverrideDeterministic constinit property declarations ********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddFunctionOverrideDeterministic Property Definitions *****************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddFunctionOverrideDeterministic_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddFunctionOverrideDeterministic_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddFunctionOverrideDeterministic_Statics::NewProp_FunctionName = { "FunctionName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddFunctionOverrideDeterministic_Parms, FunctionName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddFunctionOverrideDeterministic_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddFunctionOverrideDeterministic_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxGraphEndpoints, METADATA_PARAMS(0, nullptr) }; // 39012202
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddFunctionOverrideDeterministic_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddFunctionOverrideDeterministic_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddFunctionOverrideDeterministic_Statics::NewProp_FunctionName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddFunctionOverrideDeterministic_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddFunctionOverrideDeterministic_Statics::PropPointers) < 2048);
// ********** End Function AddFunctionOverrideDeterministic Property Definitions *******************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddFunctionOverrideDeterministic_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddFunctionOverrideDeterministic", 	Z_Construct_UFunction_UBpxReflectionOps_AddFunctionOverrideDeterministic_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddFunctionOverrideDeterministic_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddFunctionOverrideDeterministic_Statics::BpxReflectionOps_eventAddFunctionOverrideDeterministic_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddFunctionOverrideDeterministic_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddFunctionOverrideDeterministic_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddFunctionOverrideDeterministic_Statics::BpxReflectionOps_eventAddFunctionOverrideDeterministic_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddFunctionOverrideDeterministic()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddFunctionOverrideDeterministic_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddFunctionOverrideDeterministic)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_FunctionName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxGraphEndpoints*)Z_Param__Result=UBpxReflectionOps::AddFunctionOverrideDeterministic(Z_Param_Blueprint,Z_Param_FunctionName);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddFunctionOverrideDeterministic ****************

// ********** Begin Class UBpxReflectionOps Function AddFunctionUserDefinedPin *********************
struct Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics
{
	struct BpxReflectionOps_eventAddFunctionUserDefinedPin_Parms
	{
		UBlueprint* Blueprint;
		FName FunctionName;
		FName PinName;
		FEdGraphPinType PinType;
		bool bDirectionIsOutput;
		FString DefaultValue;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Append a user-defined pin to a Blueprint function's `K2Node_FunctionEntry`,\n\x09 * `K2Node_FunctionResult`, or to a `K2Node_CustomEvent` in an ubergraph,\n\x09 * with a deterministic PinId. Wraps `K2Node_EditablePinBase::CreateUserDefinedPin`.\n\x09 *\n\x09 * Dispatch (`bDirectionIsOutput=true` means the pin's UE direction is\n\x09 * EGPD_Output; `false` means EGPD_Input):\n\x09 *   - If `FunctionName` resolves to a function graph (function graph or\n\x09 *     interface-override graph) \xe2\x86\x92 operate on Entry / Result:\n\x09 *       - `bDirectionIsOutput=true`  \xe2\x86\x92 target Entry node (Entry's outputs\n\x09 *         are the function's inputs). Entry must already exist (auto-spawned\n\x09 *         by `add_bp_function` / `add_bp_interface`).\n\x09 *       - `bDirectionIsOutput=false` \xe2\x86\x92 target Result node (Result's inputs\n\x09 *         are the function's outputs). Result auto-spawned with deterministic\n\x09 *         NodeGuid + pin IDs if missing \xe2\x80\x94 pure-function authors who add an\n\x09 *         output pin retroactively don't need a separate \"spawn Result\"\n\x09 *         step. The auto-spawn seeds via\n\x09 *         `<bp>:func:<fn>:result` (matches `AddFunctionGraphDeterministic`'s\n\x09 *         seed key so byte-identity is preserved across the fresh-create-\n\x09 *         then-add-output vs `add_bp_function(is_pure=False)` paths).\n\x09 *   - Else \xe2\x86\x92 walk every `Blueprint->UbergraphPages` for a `K2Node_CustomEvent`\n\x09 *     whose `CustomFunctionName == FunctionName`. CustomEvents only support\n\x09 *     `bDirectionIsOutput=true` (event's outputs are the event-handler's\n\x09 *     inputs); `bDirectionIsOutput=false` is a structured error.\n\x09 *   - If neither path resolves the function/event \xe2\x86\x92 structured error.\n\x09 *\n\x09 * Idempotence: short-circuits on `target->UserDefinedPinExists(PinName)`\n\x09 * (returns `bSuccess=true, bSkipped=true` without touching the existing\n\x09 * pin's type or default). Type compatibility is NOT verified on the skip\n\x09 * path \xe2\x80\x94 same semantics as `AddMemberVariableDeterministic`.\n\x09 *\n\x09 * Determinism: the new pin's `PinId` is reseeded post-create via\n\x09 * `SeedGuidFromJoined(<bp>:<scope>:<fname>:userpin:<pname>:<dir>)` where\n\x09 * `<scope>` is `entry` / `result` / `custom_event`. Without this, the\n\x09 * fresh `FGuid::NewGuid()` from `UEdGraphPin::CreatePin` would drift the\n\x09 * `.uasset` md5 every replay and trip M28.pre.3 soak round 2.\n\x09 *\n\x09 * `DefaultValue` (ImportText format \xe2\x80\x94 `\"true\"` for bool, `\"42\"` for int,\n\x09 * `\"(X=1.0,Y=2.0)\"` for vectors) is applied via\n\x09 * `target->ModifyUserDefinedPinDefaultValue` after the pin is created.\n\x09 * Empty string = no default. Output pins on Result nodes don't accept\n\x09 * defaults at the BP layer (Result outputs are wired-only at compile);\n\x09 * the bridge silently ignores `DefaultValue` for Result-targeted calls\n\x09 * to keep the Python op signature uniform.\n\x09 *\n\x09 * Calls `MarkBlueprintAsStructurallyModified` on the success path.\n\x09 * `CreateUserDefinedPin` does NOT mark internally (verified against\n\x09 * `K2Node_EditablePinBase.cpp:162-178` \xe2\x80\x94 engine UI callers mark via the\n\x09 * BlueprintEditor panel, not the node itself), so we do it here.\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.\n\x09 *\n\x09 * Thread: game-thread only.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Append a user-defined pin to a Blueprint function's `K2Node_FunctionEntry`,\n`K2Node_FunctionResult`, or to a `K2Node_CustomEvent` in an ubergraph,\nwith a deterministic PinId. Wraps `K2Node_EditablePinBase::CreateUserDefinedPin`.\n\nDispatch (`bDirectionIsOutput=true` means the pin's UE direction is\nEGPD_Output; `false` means EGPD_Input):\n  - If `FunctionName` resolves to a function graph (function graph or\n    interface-override graph) \xe2\x86\x92 operate on Entry / Result:\n      - `bDirectionIsOutput=true`  \xe2\x86\x92 target Entry node (Entry's outputs\n        are the function's inputs). Entry must already exist (auto-spawned\n        by `add_bp_function` / `add_bp_interface`).\n      - `bDirectionIsOutput=false` \xe2\x86\x92 target Result node (Result's inputs\n        are the function's outputs). Result auto-spawned with deterministic\n        NodeGuid + pin IDs if missing \xe2\x80\x94 pure-function authors who add an\n        output pin retroactively don't need a separate \"spawn Result\"\n        step. The auto-spawn seeds via\n        `<bp>:func:<fn>:result` (matches `AddFunctionGraphDeterministic`'s\n        seed key so byte-identity is preserved across the fresh-create-\n        then-add-output vs `add_bp_function(is_pure=False)` paths).\n  - Else \xe2\x86\x92 walk every `Blueprint->UbergraphPages` for a `K2Node_CustomEvent`\n    whose `CustomFunctionName == FunctionName`. CustomEvents only support\n    `bDirectionIsOutput=true` (event's outputs are the event-handler's\n    inputs); `bDirectionIsOutput=false` is a structured error.\n  - If neither path resolves the function/event \xe2\x86\x92 structured error.\n\nIdempotence: short-circuits on `target->UserDefinedPinExists(PinName)`\n(returns `bSuccess=true, bSkipped=true` without touching the existing\npin's type or default). Type compatibility is NOT verified on the skip\npath \xe2\x80\x94 same semantics as `AddMemberVariableDeterministic`.\n\nDeterminism: the new pin's `PinId` is reseeded post-create via\n`SeedGuidFromJoined(<bp>:<scope>:<fname>:userpin:<pname>:<dir>)` where\n`<scope>` is `entry` / `result` / `custom_event`. Without this, the\nfresh `FGuid::NewGuid()` from `UEdGraphPin::CreatePin` would drift the\n`.uasset` md5 every replay and trip M28.pre.3 soak round 2.\n\n`DefaultValue` (ImportText format \xe2\x80\x94 `\"true\"` for bool, `\"42\"` for int,\n`\"(X=1.0,Y=2.0)\"` for vectors) is applied via\n`target->ModifyUserDefinedPinDefaultValue` after the pin is created.\nEmpty string = no default. Output pins on Result nodes don't accept\ndefaults at the BP layer (Result outputs are wired-only at compile);\nthe bridge silently ignores `DefaultValue` for Result-targeted calls\nto keep the Python op signature uniform.\n\nCalls `MarkBlueprintAsStructurallyModified` on the success path.\n`CreateUserDefinedPin` does NOT mark internally (verified against\n`K2Node_EditablePinBase.cpp:162-178` \xe2\x80\x94 engine UI callers mark via the\nBlueprintEditor panel, not the node itself), so we do it here.\n\nCaller is responsible for `CompileAndSavePackage(BP)` after the add.\n\nThread: game-thread only." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PinType_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function AddFunctionUserDefinedPin constinit property declarations *************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_FunctionName;
	static const UECodeGen_Private::FNamePropertyParams NewProp_PinName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PinType;
	static void NewProp_bDirectionIsOutput_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDirectionIsOutput;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DefaultValue;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddFunctionUserDefinedPin constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddFunctionUserDefinedPin Property Definitions ************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddFunctionUserDefinedPin_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::NewProp_FunctionName = { "FunctionName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddFunctionUserDefinedPin_Parms, FunctionName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::NewProp_PinName = { "PinName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddFunctionUserDefinedPin_Parms, PinName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::NewProp_PinType = { "PinType", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddFunctionUserDefinedPin_Parms, PinType), Z_Construct_UScriptStruct_FEdGraphPinType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PinType_MetaData), NewProp_PinType_MetaData) }; // 3132758275
void Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::NewProp_bDirectionIsOutput_SetBit(void* Obj)
{
	((BpxReflectionOps_eventAddFunctionUserDefinedPin_Parms*)Obj)->bDirectionIsOutput = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::NewProp_bDirectionIsOutput = { "bDirectionIsOutput", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(BpxReflectionOps_eventAddFunctionUserDefinedPin_Parms), &Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::NewProp_bDirectionIsOutput_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::NewProp_DefaultValue = { "DefaultValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddFunctionUserDefinedPin_Parms, DefaultValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultValue_MetaData), NewProp_DefaultValue_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddFunctionUserDefinedPin_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::NewProp_FunctionName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::NewProp_PinName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::NewProp_PinType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::NewProp_bDirectionIsOutput,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::NewProp_DefaultValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::PropPointers) < 2048);
// ********** End Function AddFunctionUserDefinedPin Property Definitions **************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddFunctionUserDefinedPin", 	Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::BpxReflectionOps_eventAddFunctionUserDefinedPin_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::BpxReflectionOps_eventAddFunctionUserDefinedPin_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddFunctionUserDefinedPin)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_FunctionName);
	P_GET_PROPERTY(FNameProperty,Z_Param_PinName);
	P_GET_STRUCT_REF(FEdGraphPinType,Z_Param_Out_PinType);
	P_GET_UBOOL(Z_Param_bDirectionIsOutput);
	P_GET_PROPERTY(FStrProperty,Z_Param_DefaultValue);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::AddFunctionUserDefinedPin(Z_Param_Blueprint,Z_Param_FunctionName,Z_Param_PinName,Z_Param_Out_PinType,Z_Param_bDirectionIsOutput,Z_Param_DefaultValue);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddFunctionUserDefinedPin ***********************

// ********** Begin Class UBpxReflectionOps Function AddGameplayTag ********************************
struct Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics
{
	struct BpxReflectionOps_eventAddGameplayTag_Parms
	{
		FString TagName;
		FString DevComment;
		FName SourceIni;
		bool bIsRestrictedTag;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Append a new gameplay tag to a project ini source via UE's editor-side\n\x09 * tag-config API. Bridge wrapper around\n\x09 * `IGameplayTagsEditorModule::AddNewGameplayTagToINI`, which sorts the\n\x09 * resulting ini list, preserves the leading `;METADATA=` editor marker\n\x09 * comment, and refreshes the in-memory tag tree post-write.\n\x09 *\n\x09 * Module location: the engine API lives in the editor-only\n\x09 * `GameplayTagsEditor` plugin, NOT on the runtime `UGameplayTagsManager`\n\x09 * (the M28 phase table assumed the latter \xe2\x80\x94 M28.6.0 research corrected\n\x09 * this). Compiles out unless `WITH_GAMEPLAYTAGSEDITOR_SUPPORT=1` per the\n\x09 * Build.cs gate; in non-editor builds the call returns `bSuccess=false`\n\x09 * with a structured error.\n\x09 *\n\x09 * Idempotent on `(TagName, SourceIni)`: pre-checks via\n\x09 * `UGameplayTagsManager::IsDictionaryTag(TagName)` so a re-apply against\n\x09 * an already-registered tag returns `bSuccess=true, bSkipped=true`\n\x09 * without firing the engine's \"already exists\" toast or touching the\n\x09 * .ini file. Critical for M28.pre.3 soak round-2 byte-identity \xe2\x80\x94 the\n\x09 * engine API itself returns `false` on duplicate-add, but the Python op\n\x09 * and verify_tag_author.py gate need a real skip signal.\n\x09 *\n\x09 * Source ini resolution (per `GameplayTagsEditorModule.cpp:500-518`):\n\x09 *   - `SourceIni == NAME_None` \xe2\x86\x92 engine substitutes the default name\n\x09 *     `\"DefaultGameplayTags.ini\"` (= `FGameplayTagSource::GetDefaultName()`)\n\x09 *     UNLESS `UGameplayTagsDeveloperSettings::DeveloperConfigName` is\n\x09 *     non-empty, in which case the source is diverted to the per-machine\n\x09 *     developer ini. Plan authors should pass an explicit\n\x09 *     `\"DefaultGameplayTags.ini\"` to make the intent clear, but cannot\n\x09 *     bypass the developer-override (it's user-machine config \xe2\x80\x94 analogous\n\x09 *     to how Perforce settings divert .uasset saves).\n\x09 *   - `SourceIni == \"DefaultGameplayTags.ini\"` \xe2\x86\x92 routes to\n\x09 *     `<Project>/Config/DefaultGameplayTags.ini` (mapped to\n\x09 *     `UGameplayTagsSettings`'s pre-registered source).\n\x09 *   - any other name \xe2\x86\x92 routes to `<Project>/Config/Tags/<name>` (mapped\n\x09 *     to a `UGameplayTagsList` source created on first write).\n\x09 *\n\x09 * Validation: relies on the engine's internal `IsValidGameplayTagString`\n\x09 * pre-check (called inside `AddNewGameplayTagToINI`). On invalid tag\n\x09 * strings (forbidden characters per `UGameplayTagsSettings::InvalidTagCharacters`,\n\x09 * leading/trailing dot, double-dot) the engine call returns `false` and\n\x09 * surfaces the error via an editor toast; this UFUNCTION reports\n\x09 * `bSuccess=false` with a generic message pointing the user at the\n\x09 * editor log. A future M28.6.x could expose `IsValidGameplayTagString`\n\x09 * as a separate validator UFUNCTION for plan-validate-time pre-checks\n\x09 * if a real driver wants typed feedback.\n\x09 *\n\x09 * Save behaviour: `AddNewGameplayTagToINI` writes via\n\x09 * `TagListObj->TryUpdateDefaultConfigFile(ConfigFileName)` and routes\n\x09 * through `ISourceControlModule` \xe2\x80\x94 if Perforce is configured, the .ini\n\x09 * gets checked out as part of the save. The existing `confirm=True`\n\x09 * gate on `apply_plan` is the mitigation for that side effect; document\n\x09 * loudly in the AGENT_LOOP worked example.\n\x09 *\n\x09 * Result shape:\n\x09 *   BeforeText: `\"absent\"` on add, `\"existing-in:<source>\"` on idempotent skip.\n\x09 *   AfterText:  the source ini name (FName.ToString()) the tag landed in.\n\x09 *               Useful when `SourceIni == NAME_None` and the engine\n\x09 *               substituted the default \xe2\x80\x94 the caller learns where the\n\x09 *               tag actually went.\n\x09 *\n\x09 * @param TagName            Dotted tag path (e.g. `\"AI.Order.Flank\"`).\n\x09 *                           Empty input returns a structured error.\n\x09 * @param DevComment         Author-visible comment string. Stored as\n\x09 *                           `+GameplayTagList=(Tag=\"...\",DevComment=\"...\")`.\n\x09 *                           Empty is fine and matches the most common\n\x09 *                           DOW pattern.\n\x09 * @param SourceIni          Target source ini name (`NAME_None` for\n\x09 *                           engine default, `\"DefaultGameplayTags.ini\"`\n\x09 *                           for explicit project default, or any\n\x09 *                           per-source ini name like `\"AI.ini\"` to land\n\x09 *                           the tag under `Config/Tags/AI.ini`).\n\x09 * @param bIsRestrictedTag   Authors a `+RestrictedGameplayTagList=` entry\n\x09 *                           instead. Restricted-tag children rules are\n\x09 *                           enforced by the engine; out of scope for\n\x09 *                           the M28.6.1 soak coverage (always `false`\n\x09 *                           in fixtures), exposed for forward-compat.\n\x09 *\n\x09 * Thread: game-thread only. Engine call refreshes the in-memory tag\n\x09 * tree via `EditorRefreshGameplayTagTree`, which is editor-only and not\n\x09 * thread-safe.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Append a new gameplay tag to a project ini source via UE's editor-side\ntag-config API. Bridge wrapper around\n`IGameplayTagsEditorModule::AddNewGameplayTagToINI`, which sorts the\nresulting ini list, preserves the leading `;METADATA=` editor marker\ncomment, and refreshes the in-memory tag tree post-write.\n\nModule location: the engine API lives in the editor-only\n`GameplayTagsEditor` plugin, NOT on the runtime `UGameplayTagsManager`\n(the M28 phase table assumed the latter \xe2\x80\x94 M28.6.0 research corrected\nthis). Compiles out unless `WITH_GAMEPLAYTAGSEDITOR_SUPPORT=1` per the\nBuild.cs gate; in non-editor builds the call returns `bSuccess=false`\nwith a structured error.\n\nIdempotent on `(TagName, SourceIni)`: pre-checks via\n`UGameplayTagsManager::IsDictionaryTag(TagName)` so a re-apply against\nan already-registered tag returns `bSuccess=true, bSkipped=true`\nwithout firing the engine's \"already exists\" toast or touching the\n.ini file. Critical for M28.pre.3 soak round-2 byte-identity \xe2\x80\x94 the\nengine API itself returns `false` on duplicate-add, but the Python op\nand verify_tag_author.py gate need a real skip signal.\n\nSource ini resolution (per `GameplayTagsEditorModule.cpp:500-518`):\n  - `SourceIni == NAME_None` \xe2\x86\x92 engine substitutes the default name\n    `\"DefaultGameplayTags.ini\"` (= `FGameplayTagSource::GetDefaultName()`)\n    UNLESS `UGameplayTagsDeveloperSettings::DeveloperConfigName` is\n    non-empty, in which case the source is diverted to the per-machine\n    developer ini. Plan authors should pass an explicit\n    `\"DefaultGameplayTags.ini\"` to make the intent clear, but cannot\n    bypass the developer-override (it's user-machine config \xe2\x80\x94 analogous\n    to how Perforce settings divert .uasset saves).\n  - `SourceIni == \"DefaultGameplayTags.ini\"` \xe2\x86\x92 routes to\n    `<Project>/Config/DefaultGameplayTags.ini` (mapped to\n    `UGameplayTagsSettings`'s pre-registered source).\n  - any other name \xe2\x86\x92 routes to `<Project>/Config/Tags/<name>` (mapped\n    to a `UGameplayTagsList` source created on first write).\n\nValidation: relies on the engine's internal `IsValidGameplayTagString`\npre-check (called inside `AddNewGameplayTagToINI`). On invalid tag\nstrings (forbidden characters per `UGameplayTagsSettings::InvalidTagCharacters`,\nleading/trailing dot, double-dot) the engine call returns `false` and\nsurfaces the error via an editor toast; this UFUNCTION reports\n`bSuccess=false` with a generic message pointing the user at the\neditor log. A future M28.6.x could expose `IsValidGameplayTagString`\nas a separate validator UFUNCTION for plan-validate-time pre-checks\nif a real driver wants typed feedback.\n\nSave behaviour: `AddNewGameplayTagToINI` writes via\n`TagListObj->TryUpdateDefaultConfigFile(ConfigFileName)` and routes\nthrough `ISourceControlModule` \xe2\x80\x94 if Perforce is configured, the .ini\ngets checked out as part of the save. The existing `confirm=True`\ngate on `apply_plan` is the mitigation for that side effect; document\nloudly in the AGENT_LOOP worked example.\n\nResult shape:\n  BeforeText: `\"absent\"` on add, `\"existing-in:<source>\"` on idempotent skip.\n  AfterText:  the source ini name (FName.ToString()) the tag landed in.\n              Useful when `SourceIni == NAME_None` and the engine\n              substituted the default \xe2\x80\x94 the caller learns where the\n              tag actually went.\n\n@param TagName            Dotted tag path (e.g. `\"AI.Order.Flank\"`).\n                          Empty input returns a structured error.\n@param DevComment         Author-visible comment string. Stored as\n                          `+GameplayTagList=(Tag=\"...\",DevComment=\"...\")`.\n                          Empty is fine and matches the most common\n                          DOW pattern.\n@param SourceIni          Target source ini name (`NAME_None` for\n                          engine default, `\"DefaultGameplayTags.ini\"`\n                          for explicit project default, or any\n                          per-source ini name like `\"AI.ini\"` to land\n                          the tag under `Config/Tags/AI.ini`).\n@param bIsRestrictedTag   Authors a `+RestrictedGameplayTagList=` entry\n                          instead. Restricted-tag children rules are\n                          enforced by the engine; out of scope for\n                          the M28.6.1 soak coverage (always `false`\n                          in fixtures), exposed for forward-compat.\n\nThread: game-thread only. Engine call refreshes the in-memory tag\ntree via `EditorRefreshGameplayTagTree`, which is editor-only and not\nthread-safe." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TagName_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DevComment_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function AddGameplayTag constinit property declarations ************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_TagName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DevComment;
	static const UECodeGen_Private::FNamePropertyParams NewProp_SourceIni;
	static void NewProp_bIsRestrictedTag_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsRestrictedTag;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddGameplayTag constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddGameplayTag Property Definitions ***********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::NewProp_TagName = { "TagName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddGameplayTag_Parms, TagName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TagName_MetaData), NewProp_TagName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::NewProp_DevComment = { "DevComment", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddGameplayTag_Parms, DevComment), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DevComment_MetaData), NewProp_DevComment_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::NewProp_SourceIni = { "SourceIni", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddGameplayTag_Parms, SourceIni), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::NewProp_bIsRestrictedTag_SetBit(void* Obj)
{
	((BpxReflectionOps_eventAddGameplayTag_Parms*)Obj)->bIsRestrictedTag = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::NewProp_bIsRestrictedTag = { "bIsRestrictedTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(BpxReflectionOps_eventAddGameplayTag_Parms), &Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::NewProp_bIsRestrictedTag_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddGameplayTag_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::NewProp_TagName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::NewProp_DevComment,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::NewProp_SourceIni,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::NewProp_bIsRestrictedTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::PropPointers) < 2048);
// ********** End Function AddGameplayTag Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddGameplayTag", 	Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::BpxReflectionOps_eventAddGameplayTag_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::BpxReflectionOps_eventAddGameplayTag_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddGameplayTag)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_TagName);
	P_GET_PROPERTY(FStrProperty,Z_Param_DevComment);
	P_GET_PROPERTY(FNameProperty,Z_Param_SourceIni);
	P_GET_UBOOL(Z_Param_bIsRestrictedTag);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::AddGameplayTag(Z_Param_TagName,Z_Param_DevComment,Z_Param_SourceIni,Z_Param_bIsRestrictedTag);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddGameplayTag **********************************

// ********** Begin Class UBpxReflectionOps Function AddInterfaceByPath ****************************
struct Z_Construct_UFunction_UBpxReflectionOps_AddInterfaceByPath_Statics
{
	struct BpxReflectionOps_eventAddInterfaceByPath_Parms
	{
		UBlueprint* Blueprint;
		UClass* InterfaceClass;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Attach an interface implementation to a Blueprint, seeding GraphGuid +\n\x09 * Entry/Return NodeGuids + pin IDs on every generated override graph so\n\x09 * the post-op .uasset bytes are byte-stable round-to-round.\n\x09 *\n\x09 * Wraps `FBlueprintEditorUtils::ImplementNewInterface` (Kismet2 module,\n\x09 * already linked) to close three silent determinism traps identical to\n\x09 * M28.2.2's function-graph add \xe2\x80\x94 `CreateNewGraph` allocates each override\n\x09 * graph via `NewObject<UEdGraph>` so `UEdGraph::PostInitProperties`\n\x09 * (EdGraph.cpp:147) assigns `GraphGuid = FGuid::NewGuid()`; the Entry\n\x09 * (and Return, when the signature has out-params) K2Node_* nodes added\n\x09 * by `CreateFunctionGraphTerminators` get random NodeGuids; their\n\x09 * default-created pins get random PinIds. Without overriding all three,\n\x09 * M28.pre.3 soak tripsround 2. Post-attach we overwrite each graph's\n\x09 * `GraphGuid` via `SeedGuidFromJoined(<bp>:iface_graph:<iface_path>:<fn>)`\n\x09 * and each Entry/Return node's NodeGuid + pin IDs via the M26.1.2 recipe.\n\x09 * `NewGraph->InterfaceGuid` (distinct from GraphGuid \xe2\x80\x94 comes from\n\x09 * `FindInterfaceFunctionGuid` against the source interface) is already\n\x09 * deterministic; no override needed.\n\x09 *\n\x09 * Idempotent: if `Blueprint->ImplementedInterfaces[]` already lists\n\x09 * `InterfaceClass`, returns `bSuccess=true, bSkipped=true` without\n\x09 * touching the asset. The engine's `ImplementNewInterface` does its own\n\x09 * \"already implemented\" check with a UI toast; we short-circuit earlier\n\x09 * so plan replay doesn't surface a spurious notification.\n\x09 *\n\x09 * Does NOT call `MarkBlueprintAsStructurallyModified` a second time \xe2\x80\x94\n\x09 * `ImplementNewInterface` marks it internally on the success path. Per\n\x09 * the M26.1.2 lesson, double-marking can re-enter structural-modified\n\x09 * listeners and invalidate our just-seeded GUIDs before the subsequent\n\x09 * compile + save.\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.\n\x09 *\n\x09 * Thread: game-thread only. `FBlueprintEditorUtils::ImplementNewInterface`\n\x09 * is editor-only and not thread-safe.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Attach an interface implementation to a Blueprint, seeding GraphGuid +\nEntry/Return NodeGuids + pin IDs on every generated override graph so\nthe post-op .uasset bytes are byte-stable round-to-round.\n\nWraps `FBlueprintEditorUtils::ImplementNewInterface` (Kismet2 module,\nalready linked) to close three silent determinism traps identical to\nM28.2.2's function-graph add \xe2\x80\x94 `CreateNewGraph` allocates each override\ngraph via `NewObject<UEdGraph>` so `UEdGraph::PostInitProperties`\n(EdGraph.cpp:147) assigns `GraphGuid = FGuid::NewGuid()`; the Entry\n(and Return, when the signature has out-params) K2Node_* nodes added\nby `CreateFunctionGraphTerminators` get random NodeGuids; their\ndefault-created pins get random PinIds. Without overriding all three,\nM28.pre.3 soak tripsround 2. Post-attach we overwrite each graph's\n`GraphGuid` via `SeedGuidFromJoined(<bp>:iface_graph:<iface_path>:<fn>)`\nand each Entry/Return node's NodeGuid + pin IDs via the M26.1.2 recipe.\n`NewGraph->InterfaceGuid` (distinct from GraphGuid \xe2\x80\x94 comes from\n`FindInterfaceFunctionGuid` against the source interface) is already\ndeterministic; no override needed.\n\nIdempotent: if `Blueprint->ImplementedInterfaces[]` already lists\n`InterfaceClass`, returns `bSuccess=true, bSkipped=true` without\ntouching the asset. The engine's `ImplementNewInterface` does its own\n\"already implemented\" check with a UI toast; we short-circuit earlier\nso plan replay doesn't surface a spurious notification.\n\nDoes NOT call `MarkBlueprintAsStructurallyModified` a second time \xe2\x80\x94\n`ImplementNewInterface` marks it internally on the success path. Per\nthe M26.1.2 lesson, double-marking can re-enter structural-modified\nlisteners and invalidate our just-seeded GUIDs before the subsequent\ncompile + save.\n\nCaller is responsible for `CompileAndSavePackage(BP)` after the add.\n\nThread: game-thread only. `FBlueprintEditorUtils::ImplementNewInterface`\nis editor-only and not thread-safe." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AddInterfaceByPath constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FClassPropertyParams NewProp_InterfaceClass;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddInterfaceByPath constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddInterfaceByPath Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddInterfaceByPath_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddInterfaceByPath_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddInterfaceByPath_Statics::NewProp_InterfaceClass = { "InterfaceClass", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddInterfaceByPath_Parms, InterfaceClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddInterfaceByPath_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddInterfaceByPath_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddInterfaceByPath_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddInterfaceByPath_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddInterfaceByPath_Statics::NewProp_InterfaceClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddInterfaceByPath_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddInterfaceByPath_Statics::PropPointers) < 2048);
// ********** End Function AddInterfaceByPath Property Definitions *********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddInterfaceByPath_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddInterfaceByPath", 	Z_Construct_UFunction_UBpxReflectionOps_AddInterfaceByPath_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddInterfaceByPath_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddInterfaceByPath_Statics::BpxReflectionOps_eventAddInterfaceByPath_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddInterfaceByPath_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddInterfaceByPath_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddInterfaceByPath_Statics::BpxReflectionOps_eventAddInterfaceByPath_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddInterfaceByPath()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddInterfaceByPath_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddInterfaceByPath)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_OBJECT(UClass,Z_Param_InterfaceClass);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::AddInterfaceByPath(Z_Param_Blueprint,Z_Param_InterfaceClass);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddInterfaceByPath ******************************

// ********** Begin Class UBpxReflectionOps Function AddLocalVariableDeterministic *****************
struct Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics
{
	struct BpxReflectionOps_eventAddLocalVariableDeterministic_Parms
	{
		UBlueprint* Blueprint;
		FName FunctionName;
		FName VarName;
		FEdGraphPinType VarType;
		FString DefaultValue;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Append a local variable to a Blueprint function's K2Node_FunctionEntry\n\x09 * `LocalVariables` array with a deterministic VarGuid.\n\x09 *\n\x09 * Different shape from the M28.3.1\xe2\x80\x93.3 K2Node-spawn ops \xe2\x80\x94 this op does NOT\n\x09 * create a new K2Node; it extends the `LocalVariables: TArray<FBPVariableDescription>`\n\x09 * UPROPERTY already present on the function graph's existing\n\x09 * `UK2Node_FunctionEntry`. Final planned slice of the M28.3 catalog, ships\n\x09 * last (per M28.3.0 research) so the Entry-node machinery is fully\n\x09 * exercised by the prior K2Node-spawn phases.\n\x09 *\n\x09 * Wraps `FBlueprintEditorUtils::AddLocalVariable` (UnrealEd module, already\n\x09 * linked via M26.1). The engine helper seeds `FBPVariableDescription::VarGuid`\n\x09 * via `FGuid::NewGuid()` at `BlueprintEditorUtils.cpp:5433`, so every call\n\x09 * drifts the .uasset bytes and trips M28.pre.3 soak round 2 without the\n\x09 * post-add override. We overwrite VarGuid via\n\x09 * `SeedGuidFromJoined(BlueprintPath + \":func:\" + FunctionName + \":localvar:\" + VarName)`\n\x09 * \xe2\x80\x94 function name included in the seed key (unlike M28.2.1's member-var\n\x09 * seed) because local vars of the same name can legitimately coexist in\n\x09 * different functions.\n\x09 *\n\x09 * `GraphName` may refer to a function graph (`Blueprint->FunctionGraphs`)\n\x09 * or an interface-override graph (`ImplementedInterfaces[].Graphs`) \xe2\x80\x94\n\x09 * resolved via `FindFunctionGraphByName`. Ubergraphs do not have local\n\x09 * variables (no `K2Node_FunctionEntry`); op returns a structured error if\n\x09 * targeted at one.\n\x09 *\n\x09 * Idempotent: if a local variable with `VarName` already exists on the\n\x09 * target function's `LocalVariables[]`, returns `bSuccess=true, bSkipped=true`\n\x09 * without modifying the asset. Type compatibility is NOT verified on the\n\x09 * skip path \xe2\x80\x94 same semantics as `AddMemberVariableDeterministic`.\n\x09 *\n\x09 * Does NOT call `MarkBlueprintAsStructurallyModified` a second time \xe2\x80\x94\n\x09 * `AddLocalVariable` marks internally on the success path. Per the M26.1.2\n\x09 * lesson, double-marking re-enters structural-modified listeners and\n\x09 * invalidates freshly-seeded GUIDs before the subsequent compile + save.\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.\n\x09 *\n\x09 * Thread: game-thread only. `FBlueprintEditorUtils::AddLocalVariable` is\n\x09 * editor-only and not thread-safe.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Append a local variable to a Blueprint function's K2Node_FunctionEntry\n`LocalVariables` array with a deterministic VarGuid.\n\nDifferent shape from the M28.3.1\xe2\x80\x93.3 K2Node-spawn ops \xe2\x80\x94 this op does NOT\ncreate a new K2Node; it extends the `LocalVariables: TArray<FBPVariableDescription>`\nUPROPERTY already present on the function graph's existing\n`UK2Node_FunctionEntry`. Final planned slice of the M28.3 catalog, ships\nlast (per M28.3.0 research) so the Entry-node machinery is fully\nexercised by the prior K2Node-spawn phases.\n\nWraps `FBlueprintEditorUtils::AddLocalVariable` (UnrealEd module, already\nlinked via M26.1). The engine helper seeds `FBPVariableDescription::VarGuid`\nvia `FGuid::NewGuid()` at `BlueprintEditorUtils.cpp:5433`, so every call\ndrifts the .uasset bytes and trips M28.pre.3 soak round 2 without the\npost-add override. We overwrite VarGuid via\n`SeedGuidFromJoined(BlueprintPath + \":func:\" + FunctionName + \":localvar:\" + VarName)`\n\xe2\x80\x94 function name included in the seed key (unlike M28.2.1's member-var\nseed) because local vars of the same name can legitimately coexist in\ndifferent functions.\n\n`GraphName` may refer to a function graph (`Blueprint->FunctionGraphs`)\nor an interface-override graph (`ImplementedInterfaces[].Graphs`) \xe2\x80\x94\nresolved via `FindFunctionGraphByName`. Ubergraphs do not have local\nvariables (no `K2Node_FunctionEntry`); op returns a structured error if\ntargeted at one.\n\nIdempotent: if a local variable with `VarName` already exists on the\ntarget function's `LocalVariables[]`, returns `bSuccess=true, bSkipped=true`\nwithout modifying the asset. Type compatibility is NOT verified on the\nskip path \xe2\x80\x94 same semantics as `AddMemberVariableDeterministic`.\n\nDoes NOT call `MarkBlueprintAsStructurallyModified` a second time \xe2\x80\x94\n`AddLocalVariable` marks internally on the success path. Per the M26.1.2\nlesson, double-marking re-enters structural-modified listeners and\ninvalidates freshly-seeded GUIDs before the subsequent compile + save.\n\nCaller is responsible for `CompileAndSavePackage(BP)` after the add.\n\nThread: game-thread only. `FBlueprintEditorUtils::AddLocalVariable` is\neditor-only and not thread-safe." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VarType_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function AddLocalVariableDeterministic constinit property declarations *********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_FunctionName;
	static const UECodeGen_Private::FNamePropertyParams NewProp_VarName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_VarType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DefaultValue;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddLocalVariableDeterministic constinit property declarations ***********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddLocalVariableDeterministic Property Definitions ********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddLocalVariableDeterministic_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::NewProp_FunctionName = { "FunctionName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddLocalVariableDeterministic_Parms, FunctionName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::NewProp_VarName = { "VarName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddLocalVariableDeterministic_Parms, VarName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::NewProp_VarType = { "VarType", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddLocalVariableDeterministic_Parms, VarType), Z_Construct_UScriptStruct_FEdGraphPinType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VarType_MetaData), NewProp_VarType_MetaData) }; // 3132758275
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::NewProp_DefaultValue = { "DefaultValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddLocalVariableDeterministic_Parms, DefaultValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultValue_MetaData), NewProp_DefaultValue_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddLocalVariableDeterministic_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::NewProp_FunctionName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::NewProp_VarName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::NewProp_VarType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::NewProp_DefaultValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::PropPointers) < 2048);
// ********** End Function AddLocalVariableDeterministic Property Definitions **********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddLocalVariableDeterministic", 	Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::BpxReflectionOps_eventAddLocalVariableDeterministic_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::BpxReflectionOps_eventAddLocalVariableDeterministic_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddLocalVariableDeterministic)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_FunctionName);
	P_GET_PROPERTY(FNameProperty,Z_Param_VarName);
	P_GET_STRUCT_REF(FEdGraphPinType,Z_Param_Out_VarType);
	P_GET_PROPERTY(FStrProperty,Z_Param_DefaultValue);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::AddLocalVariableDeterministic(Z_Param_Blueprint,Z_Param_FunctionName,Z_Param_VarName,Z_Param_Out_VarType,Z_Param_DefaultValue);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddLocalVariableDeterministic *******************

// ********** Begin Class UBpxReflectionOps Function AddMacroInstanceNode **************************
struct Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics
{
	struct BpxReflectionOps_eventAddMacroInstanceNode_Parms
	{
		UBlueprint* Blueprint;
		FName GraphName;
		UEdGraph* MacroGraph;
		FVector2D Position;
		FBpxNodeResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Spawn a `UK2Node_MacroInstance` into a named K2 graph, pointed at an\n\x09 * external macro graph (e.g. ForEachLoop / WhileLoop / Reverse for Each\n\x09 * Loop in `/Engine/EditorBlueprintResources/StandardMacros`), with a\n\x09 * deterministic NodeGuid + pin IDs.\n\x09 *\n\x09 * Driver: design.md feasibility table \xe2\x80\x94 five sections (BroadcastOrder /\n\x09 * AssignRole iteration, ScorerScoringLoop, ConfidenceDecay,\n\x09 * ConfidenceDecay+SharedPerception) were stuck on \"iterates X \xe2\x86\x92 blocked\"\n\x09 * because ForEachLoop is a macro instance, not an atomic K2Node, so the\n\x09 * M28.3.x catalog couldn't author it.\n\x09 *\n\x09 * `MacroGraph` MUST be a `EGraphType::GT_Macro` graph. Caller resolves it\n\x09 * Python-side via `unreal.load_object(None, \"<lib_path>\")` + walking the\n\x09 * resulting UBlueprint's `MacroGraphs` array \xe2\x80\x94 bridge enforces the\n\x09 * GT_Macro check defensively but the typical wrong-shape case is caught\n\x09 * earlier with a better error.\n\x09 *\n\x09 * Pin set: K2Node_MacroInstance mirrors the macro's own Tunnel/Result\n\x09 * pins onto the instance via the inherited `UK2Node_Tunnel::AllocateDefaultPins`.\n\x09 * `MacroGraphReference.SetGraph(MacroGraph)` MUST be called BEFORE\n\x09 * `AllocateDefaultPins` so the pin walk has the macro to iterate; without\n\x09 * the pre-alloc set, the node lands with zero pins.\n\x09 *\n\x09 * Determinism: `NodeGuid` is seeded as\n\x09 * `md5(<bp>:graph:<g>:macro:<macro_lib_path>:<macro_name>:<x,y>)`;\n\x09 * `SeedPinGuidsForNode` runs AFTER `AllocateDefaultPins` so the mirrored\n\x09 * pins (whose count + names depend on the macro's signature) get\n\x09 * deterministic PinIds. Library path is included in the seed so two\n\x09 * different ForEachLoop variants from different libraries don't collide.\n\x09 *\n\x09 * Idempotent on the seeded NodeGuid: a second call with identical\n\x09 * (GraphName, MacroGraph, Position) returns `bSuccess=true, bSkipped=true`.\n\x09 * Distinct positions in the same graph are distinct nodes (matching the\n\x09 * rest of the M28.3.x family).\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.\n\x09 *\n\x09 * Thread: game-thread only.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spawn a `UK2Node_MacroInstance` into a named K2 graph, pointed at an\nexternal macro graph (e.g. ForEachLoop / WhileLoop / Reverse for Each\nLoop in `/Engine/EditorBlueprintResources/StandardMacros`), with a\ndeterministic NodeGuid + pin IDs.\n\nDriver: design.md feasibility table \xe2\x80\x94 five sections (BroadcastOrder /\nAssignRole iteration, ScorerScoringLoop, ConfidenceDecay,\nConfidenceDecay+SharedPerception) were stuck on \"iterates X \xe2\x86\x92 blocked\"\nbecause ForEachLoop is a macro instance, not an atomic K2Node, so the\nM28.3.x catalog couldn't author it.\n\n`MacroGraph` MUST be a `EGraphType::GT_Macro` graph. Caller resolves it\nPython-side via `unreal.load_object(None, \"<lib_path>\")` + walking the\nresulting UBlueprint's `MacroGraphs` array \xe2\x80\x94 bridge enforces the\nGT_Macro check defensively but the typical wrong-shape case is caught\nearlier with a better error.\n\nPin set: K2Node_MacroInstance mirrors the macro's own Tunnel/Result\npins onto the instance via the inherited `UK2Node_Tunnel::AllocateDefaultPins`.\n`MacroGraphReference.SetGraph(MacroGraph)` MUST be called BEFORE\n`AllocateDefaultPins` so the pin walk has the macro to iterate; without\nthe pre-alloc set, the node lands with zero pins.\n\nDeterminism: `NodeGuid` is seeded as\n`md5(<bp>:graph:<g>:macro:<macro_lib_path>:<macro_name>:<x,y>)`;\n`SeedPinGuidsForNode` runs AFTER `AllocateDefaultPins` so the mirrored\npins (whose count + names depend on the macro's signature) get\ndeterministic PinIds. Library path is included in the seed so two\ndifferent ForEachLoop variants from different libraries don't collide.\n\nIdempotent on the seeded NodeGuid: a second call with identical\n(GraphName, MacroGraph, Position) returns `bSuccess=true, bSkipped=true`.\nDistinct positions in the same graph are distinct nodes (matching the\nrest of the M28.3.x family).\n\nCaller is responsible for `CompileAndSavePackage(BP)` after the add.\n\nThread: game-thread only." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AddMacroInstanceNode constinit property declarations ******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_GraphName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MacroGraph;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddMacroInstanceNode constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddMacroInstanceNode Property Definitions *****************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddMacroInstanceNode_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::NewProp_GraphName = { "GraphName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddMacroInstanceNode_Parms, GraphName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::NewProp_MacroGraph = { "MacroGraph", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddMacroInstanceNode_Parms, MacroGraph), Z_Construct_UClass_UEdGraph_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddMacroInstanceNode_Parms, Position), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddMacroInstanceNode_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxNodeResult, METADATA_PARAMS(0, nullptr) }; // 685492501
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::NewProp_GraphName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::NewProp_MacroGraph,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::PropPointers) < 2048);
// ********** End Function AddMacroInstanceNode Property Definitions *******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddMacroInstanceNode", 	Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::BpxReflectionOps_eventAddMacroInstanceNode_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04822401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::BpxReflectionOps_eventAddMacroInstanceNode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddMacroInstanceNode)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_GraphName);
	P_GET_OBJECT(UEdGraph,Z_Param_MacroGraph);
	P_GET_STRUCT(FVector2D,Z_Param_Position);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxNodeResult*)Z_Param__Result=UBpxReflectionOps::AddMacroInstanceNode(Z_Param_Blueprint,Z_Param_GraphName,Z_Param_MacroGraph,Z_Param_Position);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddMacroInstanceNode ****************************

// ********** Begin Class UBpxReflectionOps Function AddMakeStructNode *****************************
struct Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics
{
	struct BpxReflectionOps_eventAddMakeStructNode_Parms
	{
		UBlueprint* Blueprint;
		FName GraphName;
		UScriptStruct* StructType;
		FVector2D Position;
		FBpxNodeResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Spawn a `UK2Node_MakeStruct` node \xe2\x80\x94 pure node that constructs a struct\n\x09 * value from per-field input pins. First op of the M28.14 catalog.\n\x09 *\n\x09 * Driver: read-modify-write inside the M28.13 ForEachLoop body for\n\x09 * design.md's UAIActionScorer per-element score updates and\n\x09 * confidence-decay over `S_TargetInfo` arrays \xe2\x80\x94 without struct authoring\n\x09 * the loops can iterate but cannot author the body.\n\x09 *\n\x09 * `StructType` MUST be set before `AllocateDefaultPins` \xe2\x80\x94 the engine\n\x09 * walks the struct's properties via `FStructOnScope` + `FMakeStructPinManager`\n\x09 * inside `AllocateDefaultPins` to populate `ShowPinForProperties` and\n\x09 * spawn the per-field input pins. Post-alloc set leaves the node with no\n\x09 * field pins. `bMadeAfterOverridePinRemoval = true` matches the engine's\n\x09 * editor spawn path (`EdGraphSchema_K2.cpp:7286`); without it the node is\n\x09 * treated as legacy and shows phantom override-toggle pins.\n\x09 *\n\x09 * `StructType == nullptr` is a structured error. Native-make-method-only\n\x09 * structs (e.g. `FVector` on platforms with a native `UKismetMathLibrary::MakeVector`\n\x09 * that the editor prefers) still work \xe2\x80\x94 `UK2Node_MakeStruct::CanBeMade`\n\x09 * returns true if the struct has any `BlueprintVisible` non-`BlueprintReadOnly`\n\x09 * property; the BP editor surfaces both Make node + native-make alternative\n\x09 * separately.\n\x09 *\n\x09 * Determinism: `NodeGuid` seeded as\n\x09 * `md5(<bp>:graph:<g>:make_struct:<struct_path>:<x,y>)`;\n\x09 * `SeedPinGuidsForNode` runs AFTER `AllocateDefaultPins` so the per-field\n\x09 * pins (whose count + names depend on the struct's UPROPERTY layout) get\n\x09 * deterministic PinIds. Idempotent on the seeded NodeGuid.\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.\n\x09 *\n\x09 * Thread: game-thread only.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spawn a `UK2Node_MakeStruct` node \xe2\x80\x94 pure node that constructs a struct\nvalue from per-field input pins. First op of the M28.14 catalog.\n\nDriver: read-modify-write inside the M28.13 ForEachLoop body for\ndesign.md's UAIActionScorer per-element score updates and\nconfidence-decay over `S_TargetInfo` arrays \xe2\x80\x94 without struct authoring\nthe loops can iterate but cannot author the body.\n\n`StructType` MUST be set before `AllocateDefaultPins` \xe2\x80\x94 the engine\nwalks the struct's properties via `FStructOnScope` + `FMakeStructPinManager`\ninside `AllocateDefaultPins` to populate `ShowPinForProperties` and\nspawn the per-field input pins. Post-alloc set leaves the node with no\nfield pins. `bMadeAfterOverridePinRemoval = true` matches the engine's\neditor spawn path (`EdGraphSchema_K2.cpp:7286`); without it the node is\ntreated as legacy and shows phantom override-toggle pins.\n\n`StructType == nullptr` is a structured error. Native-make-method-only\nstructs (e.g. `FVector` on platforms with a native `UKismetMathLibrary::MakeVector`\nthat the editor prefers) still work \xe2\x80\x94 `UK2Node_MakeStruct::CanBeMade`\nreturns true if the struct has any `BlueprintVisible` non-`BlueprintReadOnly`\nproperty; the BP editor surfaces both Make node + native-make alternative\nseparately.\n\nDeterminism: `NodeGuid` seeded as\n`md5(<bp>:graph:<g>:make_struct:<struct_path>:<x,y>)`;\n`SeedPinGuidsForNode` runs AFTER `AllocateDefaultPins` so the per-field\npins (whose count + names depend on the struct's UPROPERTY layout) get\ndeterministic PinIds. Idempotent on the seeded NodeGuid.\n\nCaller is responsible for `CompileAndSavePackage(BP)` after the add.\n\nThread: game-thread only." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AddMakeStructNode constinit property declarations *********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_GraphName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StructType;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddMakeStructNode constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddMakeStructNode Property Definitions ********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddMakeStructNode_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::NewProp_GraphName = { "GraphName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddMakeStructNode_Parms, GraphName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::NewProp_StructType = { "StructType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddMakeStructNode_Parms, StructType), Z_Construct_UClass_UScriptStruct_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddMakeStructNode_Parms, Position), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddMakeStructNode_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxNodeResult, METADATA_PARAMS(0, nullptr) }; // 685492501
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::NewProp_GraphName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::NewProp_StructType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::PropPointers) < 2048);
// ********** End Function AddMakeStructNode Property Definitions **********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddMakeStructNode", 	Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::BpxReflectionOps_eventAddMakeStructNode_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04822401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::BpxReflectionOps_eventAddMakeStructNode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddMakeStructNode)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_GraphName);
	P_GET_OBJECT(UScriptStruct,Z_Param_StructType);
	P_GET_STRUCT(FVector2D,Z_Param_Position);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxNodeResult*)Z_Param__Result=UBpxReflectionOps::AddMakeStructNode(Z_Param_Blueprint,Z_Param_GraphName,Z_Param_StructType,Z_Param_Position);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddMakeStructNode *******************************

// ********** Begin Class UBpxReflectionOps Function AddMemberVariableDeterministic ****************
struct Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics
{
	struct BpxReflectionOps_eventAddMemberVariableDeterministic_Parms
	{
		UBlueprint* Blueprint;
		FName VarName;
		FEdGraphPinType VarType;
		FString DefaultValue;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Add a new member variable to a Blueprint with a deterministic VarGuid.\n\x09 *\n\x09 * Wraps `FBlueprintEditorUtils::AddMemberVariable` (which is exposed via\n\x09 * `unreal.BlueprintEditorLibrary.add_member_variable` already) to fix a\n\x09 * silent determinism trap: the engine call seeds `FBPVariableDescription\n\x09 * ::VarGuid` via `FGuid::NewGuid()`, so every `add_bp_variable` call\n\x09 * drifts the .uasset bytes \xe2\x80\x94 would trip M28.pre.3 soak gate immediately\n\x09 * on the first round-2 comparison. This op overwrites VarGuid with\n\x09 * `SeedGuidFromJoined(BlueprintPath + \":var:\" + VarName)` post-add,\n\x09 * mirroring the M26.1 NodeGuid / M26.1.2 PinId determinism pattern.\n\x09 *\n\x09 * `DefaultValue` is the literal default in the same string format\n\x09 * `FBPVariableDescription::DefaultValue` accepts (e.g. \"true\" for bool,\n\x09 * \"42\" for int, \"(X=1.0,Y=2.0)\" for vectors). Pass empty string for\n\x09 * type-default (UE handles the rest).\n\x09 *\n\x09 * Idempotent: if a variable with `VarName` already exists on\n\x09 * `Blueprint->NewVariables[]`, returns `bSuccess=true, bSkipped=true`\n\x09 * without modifying the BP. Type compatibility is NOT verified on the\n\x09 * skip path \xe2\x80\x94 callers can detect \"wrong type already exists\" by reading\n\x09 * `BeforeText` (\"var-exists:<VarName>\") and inspecting the existing\n\x09 * variable's type via the standard `unreal.*` reflection.\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(BP)` after the add\n\x09 * (and after any chained metadata setters like\n\x09 * `unreal.BlueprintEditorLibrary.set_blueprint_variable_instance_editable`).\n\x09 *\n\x09 * Thread: game-thread only. The implementation calls into\n\x09 * `FBlueprintEditorUtils` which is editor-only and not thread-safe.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Add a new member variable to a Blueprint with a deterministic VarGuid.\n\nWraps `FBlueprintEditorUtils::AddMemberVariable` (which is exposed via\n`unreal.BlueprintEditorLibrary.add_member_variable` already) to fix a\nsilent determinism trap: the engine call seeds `FBPVariableDescription\n::VarGuid` via `FGuid::NewGuid()`, so every `add_bp_variable` call\ndrifts the .uasset bytes \xe2\x80\x94 would trip M28.pre.3 soak gate immediately\non the first round-2 comparison. This op overwrites VarGuid with\n`SeedGuidFromJoined(BlueprintPath + \":var:\" + VarName)` post-add,\nmirroring the M26.1 NodeGuid / M26.1.2 PinId determinism pattern.\n\n`DefaultValue` is the literal default in the same string format\n`FBPVariableDescription::DefaultValue` accepts (e.g. \"true\" for bool,\n\"42\" for int, \"(X=1.0,Y=2.0)\" for vectors). Pass empty string for\ntype-default (UE handles the rest).\n\nIdempotent: if a variable with `VarName` already exists on\n`Blueprint->NewVariables[]`, returns `bSuccess=true, bSkipped=true`\nwithout modifying the BP. Type compatibility is NOT verified on the\nskip path \xe2\x80\x94 callers can detect \"wrong type already exists\" by reading\n`BeforeText` (\"var-exists:<VarName>\") and inspecting the existing\nvariable's type via the standard `unreal.*` reflection.\n\nCaller is responsible for `CompileAndSavePackage(BP)` after the add\n(and after any chained metadata setters like\n`unreal.BlueprintEditorLibrary.set_blueprint_variable_instance_editable`).\n\nThread: game-thread only. The implementation calls into\n`FBlueprintEditorUtils` which is editor-only and not thread-safe." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VarType_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function AddMemberVariableDeterministic constinit property declarations ********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_VarName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_VarType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DefaultValue;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddMemberVariableDeterministic constinit property declarations **********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddMemberVariableDeterministic Property Definitions *******************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddMemberVariableDeterministic_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::NewProp_VarName = { "VarName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddMemberVariableDeterministic_Parms, VarName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::NewProp_VarType = { "VarType", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddMemberVariableDeterministic_Parms, VarType), Z_Construct_UScriptStruct_FEdGraphPinType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VarType_MetaData), NewProp_VarType_MetaData) }; // 3132758275
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::NewProp_DefaultValue = { "DefaultValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddMemberVariableDeterministic_Parms, DefaultValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultValue_MetaData), NewProp_DefaultValue_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddMemberVariableDeterministic_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::NewProp_VarName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::NewProp_VarType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::NewProp_DefaultValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::PropPointers) < 2048);
// ********** End Function AddMemberVariableDeterministic Property Definitions *********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddMemberVariableDeterministic", 	Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::BpxReflectionOps_eventAddMemberVariableDeterministic_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::BpxReflectionOps_eventAddMemberVariableDeterministic_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddMemberVariableDeterministic)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_VarName);
	P_GET_STRUCT_REF(FEdGraphPinType,Z_Param_Out_VarType);
	P_GET_PROPERTY(FStrProperty,Z_Param_DefaultValue);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::AddMemberVariableDeterministic(Z_Param_Blueprint,Z_Param_VarName,Z_Param_Out_VarType,Z_Param_DefaultValue);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddMemberVariableDeterministic ******************

// ********** Begin Class UBpxReflectionOps Function AddSelfMemberGetNode **************************
struct Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics
{
	struct BpxReflectionOps_eventAddSelfMemberGetNode_Parms
	{
		UBlueprint* Blueprint;
		FName FunctionName;
		FName MemberName;
		FVector2D Position;
		FBpxNodeResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Create a UK2Node_VariableGet bound to MemberName on the Blueprint's\n\x09 * generated class (self context). Self-only by design for the M26.1\n\x09 * passthrough case.\n\x09 *\n\x09 * Deterministic NodeGuid seeded from md5(bp_path + \":\" + function_name\n\x09 * + \":get:\" + member_name). Idempotent on that seed: if a node with\n\x09 * the same GUID already exists in the graph, returns it with\n\x09 * bSkipped=true.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Create a UK2Node_VariableGet bound to MemberName on the Blueprint's\ngenerated class (self context). Self-only by design for the M26.1\npassthrough case.\n\nDeterministic NodeGuid seeded from md5(bp_path + \":\" + function_name\n+ \":get:\" + member_name). Idempotent on that seed: if a node with\nthe same GUID already exists in the graph, returns it with\nbSkipped=true." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AddSelfMemberGetNode constinit property declarations ******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_FunctionName;
	static const UECodeGen_Private::FNamePropertyParams NewProp_MemberName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddSelfMemberGetNode constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddSelfMemberGetNode Property Definitions *****************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddSelfMemberGetNode_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::NewProp_FunctionName = { "FunctionName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddSelfMemberGetNode_Parms, FunctionName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::NewProp_MemberName = { "MemberName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddSelfMemberGetNode_Parms, MemberName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddSelfMemberGetNode_Parms, Position), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddSelfMemberGetNode_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxNodeResult, METADATA_PARAMS(0, nullptr) }; // 685492501
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::NewProp_FunctionName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::NewProp_MemberName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::PropPointers) < 2048);
// ********** End Function AddSelfMemberGetNode Property Definitions *******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddSelfMemberGetNode", 	Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::BpxReflectionOps_eventAddSelfMemberGetNode_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04822401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::BpxReflectionOps_eventAddSelfMemberGetNode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddSelfMemberGetNode)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_FunctionName);
	P_GET_PROPERTY(FNameProperty,Z_Param_MemberName);
	P_GET_STRUCT(FVector2D,Z_Param_Position);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxNodeResult*)Z_Param__Result=UBpxReflectionOps::AddSelfMemberGetNode(Z_Param_Blueprint,Z_Param_FunctionName,Z_Param_MemberName,Z_Param_Position);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddSelfMemberGetNode ****************************

// ********** Begin Class UBpxReflectionOps Function AddSetFieldsInStructNode **********************
struct Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics
{
	struct BpxReflectionOps_eventAddSetFieldsInStructNode_Parms
	{
		UBlueprint* Blueprint;
		FName GraphName;
		UScriptStruct* StructType;
		TArray<FName> FieldsToShow;
		FVector2D Position;
		FBpxNodeResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Spawn a `UK2Node_SetFieldsInStruct` node \xe2\x80\x94 imperative node that takes\n\x09 * a struct input, sets a configurable subset of its fields from input\n\x09 * pins, and emits the modified struct as an output. The \"modify\" half of\n\x09 * read-modify-write inside loop bodies (vs Make = construct, Break = read).\n\x09 *\n\x09 * `FieldsToShow` is the configurable subset: only field names listed\n\x09 * here are exposed as input pins on the node. SetFieldsInStruct's\n\x09 * `FSetFieldsInStructPinManager::GetRecordDefaults` initializes\n\x09 * `bShowPin = false` for every field (vs Make/Break which default to\n\x09 * true), so the caller MUST pass at least one field name to get a usable\n\x09 * node. Pre-validation: any name in `FieldsToShow` that doesn't match a\n\x09 * property on `StructType` is a structured error (silent no-op would be\n\x09 * a typo foot-gun).\n\x09 *\n\x09 * Implementation: NewObject + StructType + AllocateDefaultPins \xe2\x86\x92 engine\n\x09 * populates `ShowPinForProperties` via `RebuildPropertyList` with all\n\x09 * `bShowPin=false`. We then walk `ShowPinForProperties`, set `bShowPin=true`\n\x09 * for entries matching `FieldsToShow`, and call `ReconstructNode()` to\n\x09 * re-run AllocateDefaultPins (which preserves bShowPin overrides through\n\x09 * `RebuildPropertyList`'s old-settings cache). `SeedPinGuidsForNode` runs\n\x09 * AFTER ReconstructNode so all final pins get deterministic PinIds.\n\x09 *\n\x09 * Determinism: seed key\n\x09 * `md5(<bp>:graph:<g>:set_fields_in_struct:<struct_path>:<sorted_fields>:<x,y>)`.\n\x09 * Sorted FieldsToShow in the seed so caller-side ordering doesn't drift\n\x09 * the GUID. Idempotent on the seeded NodeGuid.\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(BP)` after the add.\n\x09 *\n\x09 * Thread: game-thread only.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spawn a `UK2Node_SetFieldsInStruct` node \xe2\x80\x94 imperative node that takes\na struct input, sets a configurable subset of its fields from input\npins, and emits the modified struct as an output. The \"modify\" half of\nread-modify-write inside loop bodies (vs Make = construct, Break = read).\n\n`FieldsToShow` is the configurable subset: only field names listed\nhere are exposed as input pins on the node. SetFieldsInStruct's\n`FSetFieldsInStructPinManager::GetRecordDefaults` initializes\n`bShowPin = false` for every field (vs Make/Break which default to\ntrue), so the caller MUST pass at least one field name to get a usable\nnode. Pre-validation: any name in `FieldsToShow` that doesn't match a\nproperty on `StructType` is a structured error (silent no-op would be\na typo foot-gun).\n\nImplementation: NewObject + StructType + AllocateDefaultPins \xe2\x86\x92 engine\npopulates `ShowPinForProperties` via `RebuildPropertyList` with all\n`bShowPin=false`. We then walk `ShowPinForProperties`, set `bShowPin=true`\nfor entries matching `FieldsToShow`, and call `ReconstructNode()` to\nre-run AllocateDefaultPins (which preserves bShowPin overrides through\n`RebuildPropertyList`'s old-settings cache). `SeedPinGuidsForNode` runs\nAFTER ReconstructNode so all final pins get deterministic PinIds.\n\nDeterminism: seed key\n`md5(<bp>:graph:<g>:set_fields_in_struct:<struct_path>:<sorted_fields>:<x,y>)`.\nSorted FieldsToShow in the seed so caller-side ordering doesn't drift\nthe GUID. Idempotent on the seeded NodeGuid.\n\nCaller is responsible for `CompileAndSavePackage(BP)` after the add.\n\nThread: game-thread only." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FieldsToShow_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function AddSetFieldsInStructNode constinit property declarations **************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_GraphName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StructType;
	static const UECodeGen_Private::FNamePropertyParams NewProp_FieldsToShow_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_FieldsToShow;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddSetFieldsInStructNode constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddSetFieldsInStructNode Property Definitions *************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddSetFieldsInStructNode_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::NewProp_GraphName = { "GraphName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddSetFieldsInStructNode_Parms, GraphName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::NewProp_StructType = { "StructType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddSetFieldsInStructNode_Parms, StructType), Z_Construct_UClass_UScriptStruct_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::NewProp_FieldsToShow_Inner = { "FieldsToShow", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::NewProp_FieldsToShow = { "FieldsToShow", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddSetFieldsInStructNode_Parms, FieldsToShow), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FieldsToShow_MetaData), NewProp_FieldsToShow_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddSetFieldsInStructNode_Parms, Position), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddSetFieldsInStructNode_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxNodeResult, METADATA_PARAMS(0, nullptr) }; // 685492501
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::NewProp_GraphName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::NewProp_StructType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::NewProp_FieldsToShow_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::NewProp_FieldsToShow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::PropPointers) < 2048);
// ********** End Function AddSetFieldsInStructNode Property Definitions ***************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddSetFieldsInStructNode", 	Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::BpxReflectionOps_eventAddSetFieldsInStructNode_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::BpxReflectionOps_eventAddSetFieldsInStructNode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddSetFieldsInStructNode)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_GraphName);
	P_GET_OBJECT(UScriptStruct,Z_Param_StructType);
	P_GET_TARRAY_REF(FName,Z_Param_Out_FieldsToShow);
	P_GET_STRUCT(FVector2D,Z_Param_Position);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxNodeResult*)Z_Param__Result=UBpxReflectionOps::AddSetFieldsInStructNode(Z_Param_Blueprint,Z_Param_GraphName,Z_Param_StructType,Z_Param_Out_FieldsToShow,Z_Param_Position);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddSetFieldsInStructNode ************************

// ********** Begin Class UBpxReflectionOps Function AddUserDefinedStructMember ********************
struct Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics
{
	struct BpxReflectionOps_eventAddUserDefinedStructMember_Parms
	{
		UUserDefinedStruct* Struct;
		FName FriendlyName;
		FEdGraphPinType VarType;
		FString DefaultValue;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Append a new member variable to a `UUserDefinedStruct` with a\n\x09 * deterministic VarGuid. Wraps `FStructureEditorUtils::AddVariable` +\n\x09 * post-seed of the new VarDesc's VarGuid + rename pass so VarName\n\x09 * regenerates from the seeded Guid + the requested friendly name.\n\x09 *\n\x09 * `VarType` is the full `FEdGraphPinType` the member should take \xe2\x80\x94\n\x09 * built Python-side via `blueprint_structural._resolve_pin_type` from\n\x09 * a terse string spec (`\"int\"` / `\"struct:/Script/Game.S_Foo\"` /\n\x09 * `\"array:real\"` / etc.).\n\x09 *\n\x09 * `DefaultValue` is the literal default value as a string in the same\n\x09 * format `FStructVariableDescription::DefaultValue` accepts. Empty\n\x09 * string = type default (engine handles). On non-empty input, after\n\x09 * the add + rename we call `ChangeVariableDefaultValue(Struct,\n\x09 * SeededGuid, DefaultValue)` so the value lands on VarDesc +\n\x09 * DefaultInstance in one shot.\n\x09 *\n\x09 * Idempotent on `FriendlyName`: walks existing VarDescriptions for a\n\x09 * matching `FriendlyName` and returns `bSuccess=true, bSkipped=true`\n\x09 * without touching the asset. Type compatibility is NOT verified on\n\x09 * the skip path \xe2\x80\x94 same semantics as `AddMemberVariableDeterministic`.\n\x09 * The existing VarGuid is left untouched on skip so the seed recipe\n\x09 * stays deterministic across replays.\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(UDS)` after the add.\n\x09 *\n\x09 * Result shape:\n\x09 *   BeforeText: `\"no-member\"` on add, `\"member-exists:<FriendlyName>\"` on skip.\n\x09 *   AfterText:  `\"member-added:<FriendlyName>\"` / `\"member-exists:<FriendlyName>\"`.\n\x09 *\n\x09 * Thread: game-thread only.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Append a new member variable to a `UUserDefinedStruct` with a\ndeterministic VarGuid. Wraps `FStructureEditorUtils::AddVariable` +\npost-seed of the new VarDesc's VarGuid + rename pass so VarName\nregenerates from the seeded Guid + the requested friendly name.\n\n`VarType` is the full `FEdGraphPinType` the member should take \xe2\x80\x94\nbuilt Python-side via `blueprint_structural._resolve_pin_type` from\na terse string spec (`\"int\"` / `\"struct:/Script/Game.S_Foo\"` /\n`\"array:real\"` / etc.).\n\n`DefaultValue` is the literal default value as a string in the same\nformat `FStructVariableDescription::DefaultValue` accepts. Empty\nstring = type default (engine handles). On non-empty input, after\nthe add + rename we call `ChangeVariableDefaultValue(Struct,\nSeededGuid, DefaultValue)` so the value lands on VarDesc +\nDefaultInstance in one shot.\n\nIdempotent on `FriendlyName`: walks existing VarDescriptions for a\nmatching `FriendlyName` and returns `bSuccess=true, bSkipped=true`\nwithout touching the asset. Type compatibility is NOT verified on\nthe skip path \xe2\x80\x94 same semantics as `AddMemberVariableDeterministic`.\nThe existing VarGuid is left untouched on skip so the seed recipe\nstays deterministic across replays.\n\nCaller is responsible for `CompileAndSavePackage(UDS)` after the add.\n\nResult shape:\n  BeforeText: `\"no-member\"` on add, `\"member-exists:<FriendlyName>\"` on skip.\n  AfterText:  `\"member-added:<FriendlyName>\"` / `\"member-exists:<FriendlyName>\"`.\n\nThread: game-thread only." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VarType_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function AddUserDefinedStructMember constinit property declarations ************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Struct;
	static const UECodeGen_Private::FNamePropertyParams NewProp_FriendlyName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_VarType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DefaultValue;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddUserDefinedStructMember constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddUserDefinedStructMember Property Definitions ***********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::NewProp_Struct = { "Struct", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddUserDefinedStructMember_Parms, Struct), Z_Construct_UClass_UUserDefinedStruct_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::NewProp_FriendlyName = { "FriendlyName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddUserDefinedStructMember_Parms, FriendlyName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::NewProp_VarType = { "VarType", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddUserDefinedStructMember_Parms, VarType), Z_Construct_UScriptStruct_FEdGraphPinType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VarType_MetaData), NewProp_VarType_MetaData) }; // 3132758275
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::NewProp_DefaultValue = { "DefaultValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddUserDefinedStructMember_Parms, DefaultValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultValue_MetaData), NewProp_DefaultValue_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddUserDefinedStructMember_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::NewProp_Struct,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::NewProp_FriendlyName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::NewProp_VarType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::NewProp_DefaultValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::PropPointers) < 2048);
// ********** End Function AddUserDefinedStructMember Property Definitions *************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddUserDefinedStructMember", 	Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::BpxReflectionOps_eventAddUserDefinedStructMember_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::BpxReflectionOps_eventAddUserDefinedStructMember_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddUserDefinedStructMember)
{
	P_GET_OBJECT(UUserDefinedStruct,Z_Param_Struct);
	P_GET_PROPERTY(FNameProperty,Z_Param_FriendlyName);
	P_GET_STRUCT_REF(FEdGraphPinType,Z_Param_Out_VarType);
	P_GET_PROPERTY(FStrProperty,Z_Param_DefaultValue);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::AddUserDefinedStructMember(Z_Param_Struct,Z_Param_FriendlyName,Z_Param_Out_VarType,Z_Param_DefaultValue);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddUserDefinedStructMember **********************

// ********** Begin Class UBpxReflectionOps Function AddVariableGetNode ****************************
struct Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics
{
	struct BpxReflectionOps_eventAddVariableGetNode_Parms
	{
		UBlueprint* Blueprint;
		FName GraphName;
		FName MemberName;
		UClass* TargetClass;
		FVector2D Position;
		FBpxNodeResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Spawn a `UK2Node_VariableGet` node into a named K2 graph with deterministic\n\x09 * NodeGuid + pin IDs. Generalises M26.1's `AddSelfMemberGetNode` to any\n\x09 * graph family (function / interface override / ubergraph) and any\n\x09 * variable context (self or external class).\n\x09 *\n\x09 * `TargetClass == nullptr` routes to `VariableReference.SetSelfMember(MemberName)`;\n\x09 * non-null routes to `SetExternalMember(MemberName, TargetClass)`. Reference\n\x09 * is set before `AllocateDefaultPins` so the typed \"value\" output pin\n\x09 * materialises with the correct PinType.\n\x09 *\n\x09 * Idempotent on seeded NodeGuid.\n\x09 *\n\x09 * Thread: game-thread only.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spawn a `UK2Node_VariableGet` node into a named K2 graph with deterministic\nNodeGuid + pin IDs. Generalises M26.1's `AddSelfMemberGetNode` to any\ngraph family (function / interface override / ubergraph) and any\nvariable context (self or external class).\n\n`TargetClass == nullptr` routes to `VariableReference.SetSelfMember(MemberName)`;\nnon-null routes to `SetExternalMember(MemberName, TargetClass)`. Reference\nis set before `AllocateDefaultPins` so the typed \"value\" output pin\nmaterialises with the correct PinType.\n\nIdempotent on seeded NodeGuid.\n\nThread: game-thread only." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AddVariableGetNode constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_GraphName;
	static const UECodeGen_Private::FNamePropertyParams NewProp_MemberName;
	static const UECodeGen_Private::FClassPropertyParams NewProp_TargetClass;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddVariableGetNode constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddVariableGetNode Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddVariableGetNode_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::NewProp_GraphName = { "GraphName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddVariableGetNode_Parms, GraphName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::NewProp_MemberName = { "MemberName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddVariableGetNode_Parms, MemberName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::NewProp_TargetClass = { "TargetClass", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddVariableGetNode_Parms, TargetClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddVariableGetNode_Parms, Position), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddVariableGetNode_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxNodeResult, METADATA_PARAMS(0, nullptr) }; // 685492501
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::NewProp_GraphName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::NewProp_MemberName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::NewProp_TargetClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::PropPointers) < 2048);
// ********** End Function AddVariableGetNode Property Definitions *********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddVariableGetNode", 	Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::BpxReflectionOps_eventAddVariableGetNode_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04822401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::BpxReflectionOps_eventAddVariableGetNode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddVariableGetNode)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_GraphName);
	P_GET_PROPERTY(FNameProperty,Z_Param_MemberName);
	P_GET_OBJECT(UClass,Z_Param_TargetClass);
	P_GET_STRUCT(FVector2D,Z_Param_Position);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxNodeResult*)Z_Param__Result=UBpxReflectionOps::AddVariableGetNode(Z_Param_Blueprint,Z_Param_GraphName,Z_Param_MemberName,Z_Param_TargetClass,Z_Param_Position);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddVariableGetNode ******************************

// ********** Begin Class UBpxReflectionOps Function AddVariableSetNode ****************************
struct Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics
{
	struct BpxReflectionOps_eventAddVariableSetNode_Parms
	{
		UBlueprint* Blueprint;
		FName GraphName;
		FName MemberName;
		UClass* TargetClass;
		FVector2D Position;
		FBpxNodeResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Spawn a `UK2Node_VariableSet` node into a named K2 graph with deterministic\n\x09 * NodeGuid + pin IDs. Sibling of `AddVariableGetNode`; same self-vs-external\n\x09 * resolution via `VariableReference.SetSelfMember` / `SetExternalMember`\n\x09 * before `AllocateDefaultPins`. For Set the default pins are the `execute`\n\x09 * input/output exec pair and a typed value input pin.\n\x09 *\n\x09 * Idempotent on seeded NodeGuid.\n\x09 *\n\x09 * Thread: game-thread only.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spawn a `UK2Node_VariableSet` node into a named K2 graph with deterministic\nNodeGuid + pin IDs. Sibling of `AddVariableGetNode`; same self-vs-external\nresolution via `VariableReference.SetSelfMember` / `SetExternalMember`\nbefore `AllocateDefaultPins`. For Set the default pins are the `execute`\ninput/output exec pair and a typed value input pin.\n\nIdempotent on seeded NodeGuid.\n\nThread: game-thread only." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AddVariableSetNode constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_GraphName;
	static const UECodeGen_Private::FNamePropertyParams NewProp_MemberName;
	static const UECodeGen_Private::FClassPropertyParams NewProp_TargetClass;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddVariableSetNode constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddVariableSetNode Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddVariableSetNode_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::NewProp_GraphName = { "GraphName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddVariableSetNode_Parms, GraphName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::NewProp_MemberName = { "MemberName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddVariableSetNode_Parms, MemberName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::NewProp_TargetClass = { "TargetClass", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddVariableSetNode_Parms, TargetClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddVariableSetNode_Parms, Position), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventAddVariableSetNode_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxNodeResult, METADATA_PARAMS(0, nullptr) }; // 685492501
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::NewProp_GraphName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::NewProp_MemberName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::NewProp_TargetClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::PropPointers) < 2048);
// ********** End Function AddVariableSetNode Property Definitions *********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "AddVariableSetNode", 	Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::BpxReflectionOps_eventAddVariableSetNode_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04822401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::BpxReflectionOps_eventAddVariableSetNode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execAddVariableSetNode)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_GraphName);
	P_GET_PROPERTY(FNameProperty,Z_Param_MemberName);
	P_GET_OBJECT(UClass,Z_Param_TargetClass);
	P_GET_STRUCT(FVector2D,Z_Param_Position);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxNodeResult*)Z_Param__Result=UBpxReflectionOps::AddVariableSetNode(Z_Param_Blueprint,Z_Param_GraphName,Z_Param_MemberName,Z_Param_TargetClass,Z_Param_Position);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function AddVariableSetNode ******************************

// ********** Begin Class UBpxReflectionOps Function ArrayAppendNewElement *************************
struct Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement_Statics
{
	struct BpxReflectionOps_eventArrayAppendNewElement_Parms
	{
		UObject* Root;
		TArray<FString> Path;
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Append a default-constructed element to an array property.\n\x09 * Works for any array type (struct, object-ref, int, etc.).\n\x09 * Caller then uses SetPropertyValue / SetObjectPropertyValue /\n\x09 * SetInstancedStructType etc. on path + \"[new_index]\" + sub-fields\n\x09 * to populate the element.\n\x09 *\n\x09 * @return Index of the newly-added element, or -1 on error.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Append a default-constructed element to an array property.\nWorks for any array type (struct, object-ref, int, etc.).\nCaller then uses SetPropertyValue / SetObjectPropertyValue /\nSetInstancedStructType etc. on path + \"[new_index]\" + sub-fields\nto populate the element.\n\n@return Index of the newly-added element, or -1 on error." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Path_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ArrayAppendNewElement constinit property declarations *****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Path_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Path;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ArrayAppendNewElement constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ArrayAppendNewElement Property Definitions ****************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement_Statics::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventArrayAppendNewElement_Parms, Root), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement_Statics::NewProp_Path_Inner = { "Path", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement_Statics::NewProp_Path = { "Path", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventArrayAppendNewElement_Parms, Path), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Path_MetaData), NewProp_Path_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventArrayAppendNewElement_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement_Statics::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement_Statics::NewProp_Path_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement_Statics::NewProp_Path,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement_Statics::PropPointers) < 2048);
// ********** End Function ArrayAppendNewElement Property Definitions ******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "ArrayAppendNewElement", 	Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement_Statics::BpxReflectionOps_eventArrayAppendNewElement_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement_Statics::BpxReflectionOps_eventArrayAppendNewElement_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execArrayAppendNewElement)
{
	P_GET_OBJECT(UObject,Z_Param_Root);
	P_GET_TARRAY_REF(FString,Z_Param_Out_Path);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=UBpxReflectionOps::ArrayAppendNewElement(Z_Param_Root,Z_Param_Out_Path);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function ArrayAppendNewElement ***************************

// ********** Begin Class UBpxReflectionOps Function ArrayRemoveAt *********************************
struct Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics
{
	struct BpxReflectionOps_eventArrayRemoveAt_Parms
	{
		UObject* Root;
		TArray<FString> Path;
		int32 Index;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Remove the element at `Index` from an array property. Shifts subsequent\n\x09 * elements down (does not swap-remove).\n\x09 *\n\x09 * Returns a result with BeforeText = previous array length, AfterText =\n\x09 * new array length. bSuccess=false with an error on OOB or wrong type.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Remove the element at `Index` from an array property. Shifts subsequent\nelements down (does not swap-remove).\n\nReturns a result with BeforeText = previous array length, AfterText =\nnew array length. bSuccess=false with an error on OOB or wrong type." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Path_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ArrayRemoveAt constinit property declarations *************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Path_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Path;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Index;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ArrayRemoveAt constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ArrayRemoveAt Property Definitions ************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventArrayRemoveAt_Parms, Root), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::NewProp_Path_Inner = { "Path", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::NewProp_Path = { "Path", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventArrayRemoveAt_Parms, Path), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Path_MetaData), NewProp_Path_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventArrayRemoveAt_Parms, Index), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventArrayRemoveAt_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::NewProp_Path_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::NewProp_Path,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::NewProp_Index,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::PropPointers) < 2048);
// ********** End Function ArrayRemoveAt Property Definitions **************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "ArrayRemoveAt", 	Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::BpxReflectionOps_eventArrayRemoveAt_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::BpxReflectionOps_eventArrayRemoveAt_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execArrayRemoveAt)
{
	P_GET_OBJECT(UObject,Z_Param_Root);
	P_GET_TARRAY_REF(FString,Z_Param_Out_Path);
	P_GET_PROPERTY(FIntProperty,Z_Param_Index);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::ArrayRemoveAt(Z_Param_Root,Z_Param_Out_Path,Z_Param_Index);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function ArrayRemoveAt ***********************************

// ********** Begin Class UBpxReflectionOps Function CompileAndSavePackage *************************
struct Z_Construct_UFunction_UBpxReflectionOps_CompileAndSavePackage_Statics
{
	struct BpxReflectionOps_eventCompileAndSavePackage_Parms
	{
		UObject* Target;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Compile a Blueprint (if Target is one) and save its package.\n\x09 * Refuses to save on BS_Error \xe2\x80\x94 if the compile fails, the on-disk\n\x09 * asset is left untouched rather than written in a broken state.\n\x09 *\n\x09 * @return True only if compile succeeded AND package saved. False means\n\x09 *         the on-disk asset is unchanged and an error was logged.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Compile a Blueprint (if Target is one) and save its package.\nRefuses to save on BS_Error \xe2\x80\x94 if the compile fails, the on-disk\nasset is left untouched rather than written in a broken state.\n\n@return True only if compile succeeded AND package saved. False means\n        the on-disk asset is unchanged and an error was logged." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function CompileAndSavePackage constinit property declarations *****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Target;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function CompileAndSavePackage constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function CompileAndSavePackage Property Definitions ****************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_CompileAndSavePackage_Statics::NewProp_Target = { "Target", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventCompileAndSavePackage_Parms, Target), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UBpxReflectionOps_CompileAndSavePackage_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((BpxReflectionOps_eventCompileAndSavePackage_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBpxReflectionOps_CompileAndSavePackage_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(BpxReflectionOps_eventCompileAndSavePackage_Parms), &Z_Construct_UFunction_UBpxReflectionOps_CompileAndSavePackage_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_CompileAndSavePackage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_CompileAndSavePackage_Statics::NewProp_Target,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_CompileAndSavePackage_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_CompileAndSavePackage_Statics::PropPointers) < 2048);
// ********** End Function CompileAndSavePackage Property Definitions ******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_CompileAndSavePackage_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "CompileAndSavePackage", 	Z_Construct_UFunction_UBpxReflectionOps_CompileAndSavePackage_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_CompileAndSavePackage_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_CompileAndSavePackage_Statics::BpxReflectionOps_eventCompileAndSavePackage_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_CompileAndSavePackage_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_CompileAndSavePackage_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_CompileAndSavePackage_Statics::BpxReflectionOps_eventCompileAndSavePackage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_CompileAndSavePackage()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_CompileAndSavePackage_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execCompileAndSavePackage)
{
	P_GET_OBJECT(UObject,Z_Param_Target);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UBpxReflectionOps::CompileAndSavePackage(Z_Param_Target);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function CompileAndSavePackage ***************************

// ********** Begin Class UBpxReflectionOps Function ConnectGraphPinsByGuidString ******************
struct Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics
{
	struct BpxReflectionOps_eventConnectGraphPinsByGuidString_Parms
	{
		UBlueprint* Blueprint;
		FName GraphName;
		FString FromNodeGuidStr;
		FName FromPinName;
		FString ToNodeGuidStr;
		FName ToPinName;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * M28.2 \xe2\x80\x94 string-GUID form of ConnectPinsByName.\n\x09 *\n\x09 * Accepts FGuid values as hex strings (32-char uppercase, no dashes \xe2\x80\x94 the\n\x09 * format DeepDumpRenderer emits for NodeGuids) so Python callers can wire\n\x09 * nodes referenced out of `.deep.md` without constructing `unreal.Guid`\n\x09 * instances. Internally parses both strings via `FGuid::Parse` and\n\x09 * delegates to `ConnectPinsByName`.\n\x09 *\n\x09 * Motivating case: BP_Task_Peek's EventGraph has a `UK2Node_IfThenElse`\n\x09 * Branch whose `else` pin is unconnected. The deep dump exposes both\n\x09 * that Branch's NodeGuid and the existing `FinishTask` node's NodeGuid;\n\x09 * this op lets the plan author wire them without round-tripping FGuids\n\x09 * through the `unreal.*` surface.\n\x09 *\n\x09 * GraphName may refer to any of: a function graph\n\x09 * (`Blueprint->FunctionGraphs`), an interface override graph\n\x09 * (`ImplementedInterfaces[].Graphs`), OR an ubergraph\n\x09 * (`UbergraphPages` \xe2\x80\x94 typically \"EventGraph\"). M28.2 extended\n\x09 * `FindFunctionGraphByName` to walk all three so this op reaches each\n\x09 * of them.\n\x09 *\n\x09 * Idempotent: already-linked pins return bSkipped=true.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "M28.2 \xe2\x80\x94 string-GUID form of ConnectPinsByName.\n\nAccepts FGuid values as hex strings (32-char uppercase, no dashes \xe2\x80\x94 the\nformat DeepDumpRenderer emits for NodeGuids) so Python callers can wire\nnodes referenced out of `.deep.md` without constructing `unreal.Guid`\ninstances. Internally parses both strings via `FGuid::Parse` and\ndelegates to `ConnectPinsByName`.\n\nMotivating case: BP_Task_Peek's EventGraph has a `UK2Node_IfThenElse`\nBranch whose `else` pin is unconnected. The deep dump exposes both\nthat Branch's NodeGuid and the existing `FinishTask` node's NodeGuid;\nthis op lets the plan author wire them without round-tripping FGuids\nthrough the `unreal.*` surface.\n\nGraphName may refer to any of: a function graph\n(`Blueprint->FunctionGraphs`), an interface override graph\n(`ImplementedInterfaces[].Graphs`), OR an ubergraph\n(`UbergraphPages` \xe2\x80\x94 typically \"EventGraph\"). M28.2 extended\n`FindFunctionGraphByName` to walk all three so this op reaches each\nof them.\n\nIdempotent: already-linked pins return bSkipped=true." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FromNodeGuidStr_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ToNodeGuidStr_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ConnectGraphPinsByGuidString constinit property declarations **********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_GraphName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_FromNodeGuidStr;
	static const UECodeGen_Private::FNamePropertyParams NewProp_FromPinName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ToNodeGuidStr;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ToPinName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ConnectGraphPinsByGuidString constinit property declarations ************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ConnectGraphPinsByGuidString Property Definitions *********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventConnectGraphPinsByGuidString_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::NewProp_GraphName = { "GraphName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventConnectGraphPinsByGuidString_Parms, GraphName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::NewProp_FromNodeGuidStr = { "FromNodeGuidStr", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventConnectGraphPinsByGuidString_Parms, FromNodeGuidStr), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FromNodeGuidStr_MetaData), NewProp_FromNodeGuidStr_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::NewProp_FromPinName = { "FromPinName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventConnectGraphPinsByGuidString_Parms, FromPinName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::NewProp_ToNodeGuidStr = { "ToNodeGuidStr", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventConnectGraphPinsByGuidString_Parms, ToNodeGuidStr), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ToNodeGuidStr_MetaData), NewProp_ToNodeGuidStr_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::NewProp_ToPinName = { "ToPinName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventConnectGraphPinsByGuidString_Parms, ToPinName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventConnectGraphPinsByGuidString_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::NewProp_GraphName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::NewProp_FromNodeGuidStr,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::NewProp_FromPinName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::NewProp_ToNodeGuidStr,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::NewProp_ToPinName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::PropPointers) < 2048);
// ********** End Function ConnectGraphPinsByGuidString Property Definitions ***********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "ConnectGraphPinsByGuidString", 	Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::BpxReflectionOps_eventConnectGraphPinsByGuidString_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::BpxReflectionOps_eventConnectGraphPinsByGuidString_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execConnectGraphPinsByGuidString)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_GraphName);
	P_GET_PROPERTY(FStrProperty,Z_Param_FromNodeGuidStr);
	P_GET_PROPERTY(FNameProperty,Z_Param_FromPinName);
	P_GET_PROPERTY(FStrProperty,Z_Param_ToNodeGuidStr);
	P_GET_PROPERTY(FNameProperty,Z_Param_ToPinName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::ConnectGraphPinsByGuidString(Z_Param_Blueprint,Z_Param_GraphName,Z_Param_FromNodeGuidStr,Z_Param_FromPinName,Z_Param_ToNodeGuidStr,Z_Param_ToPinName);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function ConnectGraphPinsByGuidString ********************

// ********** Begin Class UBpxReflectionOps Function ConnectPinsByName *****************************
struct Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics
{
	struct BpxReflectionOps_eventConnectPinsByName_Parms
	{
		UBlueprint* Blueprint;
		FName FunctionName;
		FGuid FromNodeGuid;
		FName FromPinName;
		FGuid ToNodeGuid;
		FName ToPinName;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Connect two pins by name. Looks up each pin's owning node by GUID\n\x09 * in the named function graph, then invokes\n\x09 * UEdGraphSchema_K2::TryCreateConnection. Idempotent: already-linked\n\x09 * pins return bSkipped=true.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Connect two pins by name. Looks up each pin's owning node by GUID\nin the named function graph, then invokes\nUEdGraphSchema_K2::TryCreateConnection. Idempotent: already-linked\npins return bSkipped=true." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ConnectPinsByName constinit property declarations *********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_FunctionName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FromNodeGuid;
	static const UECodeGen_Private::FNamePropertyParams NewProp_FromPinName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ToNodeGuid;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ToPinName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ConnectPinsByName constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ConnectPinsByName Property Definitions ********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventConnectPinsByName_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::NewProp_FunctionName = { "FunctionName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventConnectPinsByName_Parms, FunctionName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::NewProp_FromNodeGuid = { "FromNodeGuid", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventConnectPinsByName_Parms, FromNodeGuid), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::NewProp_FromPinName = { "FromPinName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventConnectPinsByName_Parms, FromPinName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::NewProp_ToNodeGuid = { "ToNodeGuid", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventConnectPinsByName_Parms, ToNodeGuid), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::NewProp_ToPinName = { "ToPinName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventConnectPinsByName_Parms, ToPinName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventConnectPinsByName_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::NewProp_FunctionName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::NewProp_FromNodeGuid,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::NewProp_FromPinName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::NewProp_ToNodeGuid,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::NewProp_ToPinName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::PropPointers) < 2048);
// ********** End Function ConnectPinsByName Property Definitions **********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "ConnectPinsByName", 	Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::BpxReflectionOps_eventConnectPinsByName_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04822401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::BpxReflectionOps_eventConnectPinsByName_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execConnectPinsByName)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_FunctionName);
	P_GET_STRUCT(FGuid,Z_Param_FromNodeGuid);
	P_GET_PROPERTY(FNameProperty,Z_Param_FromPinName);
	P_GET_STRUCT(FGuid,Z_Param_ToNodeGuid);
	P_GET_PROPERTY(FNameProperty,Z_Param_ToPinName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::ConnectPinsByName(Z_Param_Blueprint,Z_Param_FunctionName,Z_Param_FromNodeGuid,Z_Param_FromPinName,Z_Param_ToNodeGuid,Z_Param_ToPinName);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function ConnectPinsByName *******************************

// ********** Begin Class UBpxReflectionOps Function CreateBlueprintClassDeterministic *************
struct Z_Construct_UFunction_UBpxReflectionOps_CreateBlueprintClassDeterministic_Statics
{
	struct BpxReflectionOps_eventCreateBlueprintClassDeterministic_Parms
	{
		FString PackagePath;
		UClass* ParentClass;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Create a new `UBlueprint` asset at the supplied `/Game/...` package path,\n\x09 * using `ParentClass` as the parent (native `/Script/<Module>.<Class>` or\n\x09 * BP-derived generated class `/Game/.../<Name>.<Name>_C`). Closes the\n\x09 * design.md gap surfaced by the M28.10.0 research outcome: existing\n\x09 * `create_child_bp` (`scripts/python_ops/assets.py:84`) only handles\n\x09 * BP-parented children, so design.md's `BP_EncounterDirector` (parent\n\x09 * `AActor`) and `UAIActionScorer` (parent `UActorComponent`) couldn't be\n\x09 * authored end-to-end via MCP.\n\x09 *\n\x09 * Wraps `FKismetEditorUtilities::CreateBlueprint(ParentClass, Pkg,\n\x09 * FName(ShortName), BPTYPE_Normal, UBlueprint::StaticClass(),\n\x09 * UBlueprintGeneratedClass::StaticClass(), NAME_None)`. The engine helper\n\x09 * (`Kismet2.cpp:432`):\n\x09 *   1. `NewObject<UBlueprint>(...)` with deterministic FName tail of `PackagePath`.\n\x09 *   2. `NewBP->BlueprintGuid = FGuid::NewGuid()`            <-- determinism trap #1\n\x09 *   3. Allocates SCS + UCS function graph + EventGraph ubergraph page.\n\x09 *      The UCS `K2Node_FunctionEntry` gets a fresh NodeGuid.   <-- trap #2a\n\x09 *   4. If `bSpawnDefaultBlueprintNodes=true` (editor default):\n\x09 *      walks `AutoGeneratedDefaultEventsMap` and spawns one\n\x09 *      `UK2Node_Event` per registered event matching the parent class\n\x09 *      hierarchy (e.g. BeginPlay / Tick / EndPlay for `AActor`-family;\n\x09 *      module-registered events for other parents). Each spawned node\n\x09 *      gets a fresh NodeGuid + per-pin random PinIds.          <-- trap #2b\n\x09 *      Iteration over a `TMultiMap` is hash-bucket-ordered and not\n\x09 *      stable across editor invocations \xe2\x80\x94 must sort post-hoc.\n\x09 *   5. Synchronous compile (already runs inside CreateBlueprint).\n\x09 *\n\x09 * Post-create we close all three traps:\n\x09 *   - Overwrite `NewBP->BlueprintGuid` with\n\x09 *     `SeedGuidFromJoined(PackagePath + \":bp\")`.\n\x09 *   - For the UCS function graph's `K2Node_FunctionEntry` (if present),\n\x09 *     reseed `NodeGuid` + every pin's `PinId` via\n\x09 *     `SeedGuidFromJoined(PackagePath + \":ucs:entry\")`.\n\x09 *   - For each node in `UbergraphPages[0]->Nodes`, sort by\n\x09 *     `(NodeClass.Name, K2Node_Event->EventReference.GetMemberName())` for\n\x09 *     stable order, then reseed `NodeGuid` + pins via\n\x09 *     `SeedGuidFromJoined(PackagePath + \":evt:\" + EventName)`.\n\x09 *\n\x09 * `USCS_Node::VariableGuid` is **already deterministic** (md5 of\n\x09 * `InternalVariableName`, `SCS_Node.cpp:645`) \xe2\x80\x94 no trapdoor.\n\x09 *\n\x09 * `ParentClass` must be:\n\x09 *   - non-null,\n\x09 *   - blueprintable per `FKismetEditorUtilities::CanCreateBlueprintOfClass`\n\x09 *     (rejects e.g. `UInterface`, classes with `BlueprintType=NotBlueprintable`,\n\x09 *     and a few engine internals \xe2\x80\x94 same gate the editor's New Blueprint\n\x09 *     dialog uses, and the gate `BlueprintFactory::FactoryCreateNew`\n\x09 *     (`EditorFactories.cpp:6805`) would otherwise raise as a modal\n\x09 *     `FMessageDialog` \xe2\x80\x94 must intercept before that path in commandlet /\n\x09 *     Python contexts).\n\x09 *\n\x09 * Idempotent on `(PackagePath, ParentClass)`: if a `UBlueprint` already\n\x09 * exists at the path AND its `ParentClass` pointer matches `ParentClass`,\n\x09 * returns `bSuccess=true, bSkipped=true` with `AfterText=PackagePath`.\n\x09 * Class mismatch at the same path returns a structured error \xe2\x80\x94 silent\n\x09 * stacking would be a plan-level mistake. This is **stricter than\n\x09 * `create_child_bp`**, which only verified existence (\"parent class not\n\x09 * verified\" caveat at `scripts/python_ops/CATALOG.md:1431`); the C++\n\x09 * bridge has direct access to `Existing->ParentClass` without going\n\x09 * through the partially-exposed Python `BlueprintGeneratedClass.get_super_class`.\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(NewBP)` after create.\n\x09 *\n\x09 * Result shape:\n\x09 *   BeforeText: `\"no-bp\"` on create, `\"bp-exists\"` on skip.\n\x09 *   AfterText:  the created/existing BP's `/Game/...` path.\n\x09 *\n\x09 * Thread: game-thread only. `FKismetEditorUtilities::CreateBlueprint`\n\x09 * runs a synchronous compile and is editor-only.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Create a new `UBlueprint` asset at the supplied `/Game/...` package path,\nusing `ParentClass` as the parent (native `/Script/<Module>.<Class>` or\nBP-derived generated class `/Game/.../<Name>.<Name>_C`). Closes the\ndesign.md gap surfaced by the M28.10.0 research outcome: existing\n`create_child_bp` (`scripts/python_ops/assets.py:84`) only handles\nBP-parented children, so design.md's `BP_EncounterDirector` (parent\n`AActor`) and `UAIActionScorer` (parent `UActorComponent`) couldn't be\nauthored end-to-end via MCP.\n\nWraps `FKismetEditorUtilities::CreateBlueprint(ParentClass, Pkg,\nFName(ShortName), BPTYPE_Normal, UBlueprint::StaticClass(),\nUBlueprintGeneratedClass::StaticClass(), NAME_None)`. The engine helper\n(`Kismet2.cpp:432`):\n  1. `NewObject<UBlueprint>(...)` with deterministic FName tail of `PackagePath`.\n  2. `NewBP->BlueprintGuid = FGuid::NewGuid()`            <-- determinism trap #1\n  3. Allocates SCS + UCS function graph + EventGraph ubergraph page.\n     The UCS `K2Node_FunctionEntry` gets a fresh NodeGuid.   <-- trap #2a\n  4. If `bSpawnDefaultBlueprintNodes=true` (editor default):\n     walks `AutoGeneratedDefaultEventsMap` and spawns one\n     `UK2Node_Event` per registered event matching the parent class\n     hierarchy (e.g. BeginPlay / Tick / EndPlay for `AActor`-family;\n     module-registered events for other parents). Each spawned node\n     gets a fresh NodeGuid + per-pin random PinIds.          <-- trap #2b\n     Iteration over a `TMultiMap` is hash-bucket-ordered and not\n     stable across editor invocations \xe2\x80\x94 must sort post-hoc.\n  5. Synchronous compile (already runs inside CreateBlueprint).\n\nPost-create we close all three traps:\n  - Overwrite `NewBP->BlueprintGuid` with\n    `SeedGuidFromJoined(PackagePath + \":bp\")`.\n  - For the UCS function graph's `K2Node_FunctionEntry` (if present),\n    reseed `NodeGuid` + every pin's `PinId` via\n    `SeedGuidFromJoined(PackagePath + \":ucs:entry\")`.\n  - For each node in `UbergraphPages[0]->Nodes`, sort by\n    `(NodeClass.Name, K2Node_Event->EventReference.GetMemberName())` for\n    stable order, then reseed `NodeGuid` + pins via\n    `SeedGuidFromJoined(PackagePath + \":evt:\" + EventName)`.\n\n`USCS_Node::VariableGuid` is **already deterministic** (md5 of\n`InternalVariableName`, `SCS_Node.cpp:645`) \xe2\x80\x94 no trapdoor.\n\n`ParentClass` must be:\n  - non-null,\n  - blueprintable per `FKismetEditorUtilities::CanCreateBlueprintOfClass`\n    (rejects e.g. `UInterface`, classes with `BlueprintType=NotBlueprintable`,\n    and a few engine internals \xe2\x80\x94 same gate the editor's New Blueprint\n    dialog uses, and the gate `BlueprintFactory::FactoryCreateNew`\n    (`EditorFactories.cpp:6805`) would otherwise raise as a modal\n    `FMessageDialog` \xe2\x80\x94 must intercept before that path in commandlet /\n    Python contexts).\n\nIdempotent on `(PackagePath, ParentClass)`: if a `UBlueprint` already\nexists at the path AND its `ParentClass` pointer matches `ParentClass`,\nreturns `bSuccess=true, bSkipped=true` with `AfterText=PackagePath`.\nClass mismatch at the same path returns a structured error \xe2\x80\x94 silent\nstacking would be a plan-level mistake. This is **stricter than\n`create_child_bp`**, which only verified existence (\"parent class not\nverified\" caveat at `scripts/python_ops/CATALOG.md:1431`); the C++\nbridge has direct access to `Existing->ParentClass` without going\nthrough the partially-exposed Python `BlueprintGeneratedClass.get_super_class`.\n\nCaller is responsible for `CompileAndSavePackage(NewBP)` after create.\n\nResult shape:\n  BeforeText: `\"no-bp\"` on create, `\"bp-exists\"` on skip.\n  AfterText:  the created/existing BP's `/Game/...` path.\n\nThread: game-thread only. `FKismetEditorUtilities::CreateBlueprint`\nruns a synchronous compile and is editor-only." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PackagePath_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function CreateBlueprintClassDeterministic constinit property declarations *****
	static const UECodeGen_Private::FStrPropertyParams NewProp_PackagePath;
	static const UECodeGen_Private::FClassPropertyParams NewProp_ParentClass;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function CreateBlueprintClassDeterministic constinit property declarations *******
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function CreateBlueprintClassDeterministic Property Definitions ****************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_CreateBlueprintClassDeterministic_Statics::NewProp_PackagePath = { "PackagePath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventCreateBlueprintClassDeterministic_Parms, PackagePath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PackagePath_MetaData), NewProp_PackagePath_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UFunction_UBpxReflectionOps_CreateBlueprintClassDeterministic_Statics::NewProp_ParentClass = { "ParentClass", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventCreateBlueprintClassDeterministic_Parms, ParentClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_CreateBlueprintClassDeterministic_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventCreateBlueprintClassDeterministic_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_CreateBlueprintClassDeterministic_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_CreateBlueprintClassDeterministic_Statics::NewProp_PackagePath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_CreateBlueprintClassDeterministic_Statics::NewProp_ParentClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_CreateBlueprintClassDeterministic_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_CreateBlueprintClassDeterministic_Statics::PropPointers) < 2048);
// ********** End Function CreateBlueprintClassDeterministic Property Definitions ******************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_CreateBlueprintClassDeterministic_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "CreateBlueprintClassDeterministic", 	Z_Construct_UFunction_UBpxReflectionOps_CreateBlueprintClassDeterministic_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_CreateBlueprintClassDeterministic_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_CreateBlueprintClassDeterministic_Statics::BpxReflectionOps_eventCreateBlueprintClassDeterministic_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_CreateBlueprintClassDeterministic_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_CreateBlueprintClassDeterministic_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_CreateBlueprintClassDeterministic_Statics::BpxReflectionOps_eventCreateBlueprintClassDeterministic_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_CreateBlueprintClassDeterministic()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_CreateBlueprintClassDeterministic_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execCreateBlueprintClassDeterministic)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_PackagePath);
	P_GET_OBJECT(UClass,Z_Param_ParentClass);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::CreateBlueprintClassDeterministic(Z_Param_PackagePath,Z_Param_ParentClass);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function CreateBlueprintClassDeterministic ***************

// ********** Begin Class UBpxReflectionOps Function CreateCurveFloatDeterministic *****************
struct Z_Construct_UFunction_UBpxReflectionOps_CreateCurveFloatDeterministic_Statics
{
	struct BpxReflectionOps_eventCreateCurveFloatDeterministic_Parms
	{
		FString PackagePath;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Create a new `UCurveFloat` asset at the supplied `/Game/...` package\n\x09 * path. First op of the M28.4 non-BP asset-factory catalog.\n\x09 *\n\x09 * Wraps `NewObject<UCurveFloat>(Pkg, Name, RF_Public | RF_Standalone)`.\n\x09 * Notifies the AssetRegistry + marks the package dirty; the caller is\n\x09 * responsible for `CompileAndSavePackage(curve)` to persist \xe2\x80\x94 same\n\x09 * pattern as `AddEnvQueryOption`. Compile is a no-op for non-Blueprint\n\x09 * assets; `CompileAndSavePackage` shorts the compile branch and writes\n\x09 * via `UPackage::SavePackage` directly.\n\x09 *\n\x09 * Determinism: `UCurveFloat` / `UCurveBase` / `FRichCurveKey` have\n\x09 * zero `FGuid::NewGuid()` usage (grep-confirmed M28.4.0 research). No\n\x09 * seeding is required \xe2\x80\x94 the explicit `FName` on `NewObject` (derived\n\x09 * from the short name of `PackagePath`) is already enough.\n\x09 *\n\x09 * Idempotent on `PackagePath`: if a `UCurveFloat` already exists at\n\x09 * the path, returns `bSuccess=true, bSkipped=true` with\n\x09 * `AfterText=PackagePath`. If a non-curve asset occupies the path, a\n\x09 * structured error is returned (different class collisions should not\n\x09 * silently no-op \xe2\x80\x94 the caller has a plan-level mistake to fix).\n\x09 *\n\x09 * Result shape:\n\x09 *   BeforeText: `\"no-curve\"` on create, `\"curve-exists\"` on skip.\n\x09 *   AfterText:  the created/existing curve's `/Game/...` path.\n\x09 *\n\x09 * Thread: game-thread only. `NewObject` + `CreatePackage` +\n\x09 * `AssetRegistry::AssetCreated` are editor-safe on the game thread.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Create a new `UCurveFloat` asset at the supplied `/Game/...` package\npath. First op of the M28.4 non-BP asset-factory catalog.\n\nWraps `NewObject<UCurveFloat>(Pkg, Name, RF_Public | RF_Standalone)`.\nNotifies the AssetRegistry + marks the package dirty; the caller is\nresponsible for `CompileAndSavePackage(curve)` to persist \xe2\x80\x94 same\npattern as `AddEnvQueryOption`. Compile is a no-op for non-Blueprint\nassets; `CompileAndSavePackage` shorts the compile branch and writes\nvia `UPackage::SavePackage` directly.\n\nDeterminism: `UCurveFloat` / `UCurveBase` / `FRichCurveKey` have\nzero `FGuid::NewGuid()` usage (grep-confirmed M28.4.0 research). No\nseeding is required \xe2\x80\x94 the explicit `FName` on `NewObject` (derived\nfrom the short name of `PackagePath`) is already enough.\n\nIdempotent on `PackagePath`: if a `UCurveFloat` already exists at\nthe path, returns `bSuccess=true, bSkipped=true` with\n`AfterText=PackagePath`. If a non-curve asset occupies the path, a\nstructured error is returned (different class collisions should not\nsilently no-op \xe2\x80\x94 the caller has a plan-level mistake to fix).\n\nResult shape:\n  BeforeText: `\"no-curve\"` on create, `\"curve-exists\"` on skip.\n  AfterText:  the created/existing curve's `/Game/...` path.\n\nThread: game-thread only. `NewObject` + `CreatePackage` +\n`AssetRegistry::AssetCreated` are editor-safe on the game thread." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PackagePath_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function CreateCurveFloatDeterministic constinit property declarations *********
	static const UECodeGen_Private::FStrPropertyParams NewProp_PackagePath;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function CreateCurveFloatDeterministic constinit property declarations ***********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function CreateCurveFloatDeterministic Property Definitions ********************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_CreateCurveFloatDeterministic_Statics::NewProp_PackagePath = { "PackagePath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventCreateCurveFloatDeterministic_Parms, PackagePath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PackagePath_MetaData), NewProp_PackagePath_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_CreateCurveFloatDeterministic_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventCreateCurveFloatDeterministic_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_CreateCurveFloatDeterministic_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_CreateCurveFloatDeterministic_Statics::NewProp_PackagePath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_CreateCurveFloatDeterministic_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_CreateCurveFloatDeterministic_Statics::PropPointers) < 2048);
// ********** End Function CreateCurveFloatDeterministic Property Definitions **********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_CreateCurveFloatDeterministic_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "CreateCurveFloatDeterministic", 	Z_Construct_UFunction_UBpxReflectionOps_CreateCurveFloatDeterministic_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_CreateCurveFloatDeterministic_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_CreateCurveFloatDeterministic_Statics::BpxReflectionOps_eventCreateCurveFloatDeterministic_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_CreateCurveFloatDeterministic_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_CreateCurveFloatDeterministic_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_CreateCurveFloatDeterministic_Statics::BpxReflectionOps_eventCreateCurveFloatDeterministic_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_CreateCurveFloatDeterministic()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_CreateCurveFloatDeterministic_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execCreateCurveFloatDeterministic)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_PackagePath);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::CreateCurveFloatDeterministic(Z_Param_PackagePath);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function CreateCurveFloatDeterministic *******************

// ********** Begin Class UBpxReflectionOps Function CreateDataAssetInstanceDeterministic **********
struct Z_Construct_UFunction_UBpxReflectionOps_CreateDataAssetInstanceDeterministic_Statics
{
	struct BpxReflectionOps_eventCreateDataAssetInstanceDeterministic_Parms
	{
		FString PackagePath;
		UClass* DAClass;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Create a new `UDataAsset`-subclass instance at the supplied `/Game/...`\n\x09 * package path, using `DAClass` as the concrete type to instantiate.\n\x09 * Third op of the M28.4 non-BP asset-factory catalog.\n\x09 *\n\x09 * Wraps `NewObject<UDataAsset>(Pkg, DAClass, FName(ShortName),\n\x09 * RF_Public | RF_Standalone | RF_Transactional)` \xe2\x80\x94 matching\n\x09 * `UDataAssetFactory::FactoryCreateNew`'s flag set\n\x09 * (EditorFactories.cpp:7288-7300). Notifies the AssetRegistry + marks the\n\x09 * package dirty; caller is responsible for `CompileAndSavePackage(Asset)`\n\x09 * to persist \xe2\x80\x94 same pattern as `CreateCurveFloatDeterministic`. Compile\n\x09 * is a no-op for non-Blueprint assets; `CompileAndSavePackage` shorts\n\x09 * the compile branch and writes via `UPackage::SavePackage` directly.\n\x09 *\n\x09 * `DAClass` must be:\n\x09 *   - non-null,\n\x09 *   - a subclass of `UDataAsset` (covers UDataAsset / UPrimaryDataAsset /\n\x09 *     BP-derived DA classes whose GeneratedClass inherits from either),\n\x09 *   - concrete (CLASS_Abstract flag rejected up-front).\n\x09 *\n\x09 * Determinism: `UDataAsset` / `UPrimaryDataAsset` have zero\n\x09 * `FGuid::NewGuid()` usage (M28.4.0 research \xe2\x80\x94 walks the Engine/DataAsset.h\n\x09 * + UPrimaryDataAsset.cpp surface). The only drift source is `NewObject`'s\n\x09 * default-name generation, closed by passing an explicit `FName` derived\n\x09 * from the short-name tail of `PackagePath`.\n\x09 *\n\x09 * Idempotent on `PackagePath`: if a `UDataAsset` already exists at the\n\x09 * path AND is an instance of `DAClass`, returns `bSuccess=true,\n\x09 * bSkipped=true` with `AfterText=PackagePath`. A wrong-class collision\n\x09 * (either non-DA asset at the path, or DA whose class doesn't match\n\x09 * `DAClass`) returns a structured error rather than silently creating\n\x09 * alongside \xe2\x80\x94 the plan author has a target mismatch to fix.\n\x09 *\n\x09 * Result shape:\n\x09 *   BeforeText: `\"no-asset\"` on create, `\"asset-exists\"` on skip.\n\x09 *   AfterText:  the created/existing asset's `/Game/...` path.\n\x09 *\n\x09 * Thread: game-thread only. `NewObject` + `CreatePackage` +\n\x09 * `AssetRegistry::AssetCreated` are editor-safe on the game thread.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Create a new `UDataAsset`-subclass instance at the supplied `/Game/...`\npackage path, using `DAClass` as the concrete type to instantiate.\nThird op of the M28.4 non-BP asset-factory catalog.\n\nWraps `NewObject<UDataAsset>(Pkg, DAClass, FName(ShortName),\nRF_Public | RF_Standalone | RF_Transactional)` \xe2\x80\x94 matching\n`UDataAssetFactory::FactoryCreateNew`'s flag set\n(EditorFactories.cpp:7288-7300). Notifies the AssetRegistry + marks the\npackage dirty; caller is responsible for `CompileAndSavePackage(Asset)`\nto persist \xe2\x80\x94 same pattern as `CreateCurveFloatDeterministic`. Compile\nis a no-op for non-Blueprint assets; `CompileAndSavePackage` shorts\nthe compile branch and writes via `UPackage::SavePackage` directly.\n\n`DAClass` must be:\n  - non-null,\n  - a subclass of `UDataAsset` (covers UDataAsset / UPrimaryDataAsset /\n    BP-derived DA classes whose GeneratedClass inherits from either),\n  - concrete (CLASS_Abstract flag rejected up-front).\n\nDeterminism: `UDataAsset` / `UPrimaryDataAsset` have zero\n`FGuid::NewGuid()` usage (M28.4.0 research \xe2\x80\x94 walks the Engine/DataAsset.h\n+ UPrimaryDataAsset.cpp surface). The only drift source is `NewObject`'s\ndefault-name generation, closed by passing an explicit `FName` derived\nfrom the short-name tail of `PackagePath`.\n\nIdempotent on `PackagePath`: if a `UDataAsset` already exists at the\npath AND is an instance of `DAClass`, returns `bSuccess=true,\nbSkipped=true` with `AfterText=PackagePath`. A wrong-class collision\n(either non-DA asset at the path, or DA whose class doesn't match\n`DAClass`) returns a structured error rather than silently creating\nalongside \xe2\x80\x94 the plan author has a target mismatch to fix.\n\nResult shape:\n  BeforeText: `\"no-asset\"` on create, `\"asset-exists\"` on skip.\n  AfterText:  the created/existing asset's `/Game/...` path.\n\nThread: game-thread only. `NewObject` + `CreatePackage` +\n`AssetRegistry::AssetCreated` are editor-safe on the game thread." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PackagePath_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function CreateDataAssetInstanceDeterministic constinit property declarations **
	static const UECodeGen_Private::FStrPropertyParams NewProp_PackagePath;
	static const UECodeGen_Private::FClassPropertyParams NewProp_DAClass;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function CreateDataAssetInstanceDeterministic constinit property declarations ****
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function CreateDataAssetInstanceDeterministic Property Definitions *************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_CreateDataAssetInstanceDeterministic_Statics::NewProp_PackagePath = { "PackagePath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventCreateDataAssetInstanceDeterministic_Parms, PackagePath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PackagePath_MetaData), NewProp_PackagePath_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UFunction_UBpxReflectionOps_CreateDataAssetInstanceDeterministic_Statics::NewProp_DAClass = { "DAClass", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventCreateDataAssetInstanceDeterministic_Parms, DAClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_CreateDataAssetInstanceDeterministic_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventCreateDataAssetInstanceDeterministic_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_CreateDataAssetInstanceDeterministic_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_CreateDataAssetInstanceDeterministic_Statics::NewProp_PackagePath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_CreateDataAssetInstanceDeterministic_Statics::NewProp_DAClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_CreateDataAssetInstanceDeterministic_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_CreateDataAssetInstanceDeterministic_Statics::PropPointers) < 2048);
// ********** End Function CreateDataAssetInstanceDeterministic Property Definitions ***************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_CreateDataAssetInstanceDeterministic_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "CreateDataAssetInstanceDeterministic", 	Z_Construct_UFunction_UBpxReflectionOps_CreateDataAssetInstanceDeterministic_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_CreateDataAssetInstanceDeterministic_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_CreateDataAssetInstanceDeterministic_Statics::BpxReflectionOps_eventCreateDataAssetInstanceDeterministic_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_CreateDataAssetInstanceDeterministic_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_CreateDataAssetInstanceDeterministic_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_CreateDataAssetInstanceDeterministic_Statics::BpxReflectionOps_eventCreateDataAssetInstanceDeterministic_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_CreateDataAssetInstanceDeterministic()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_CreateDataAssetInstanceDeterministic_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execCreateDataAssetInstanceDeterministic)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_PackagePath);
	P_GET_OBJECT(UClass,Z_Param_DAClass);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::CreateDataAssetInstanceDeterministic(Z_Param_PackagePath,Z_Param_DAClass);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function CreateDataAssetInstanceDeterministic ************

// ********** Begin Class UBpxReflectionOps Function CreateUserDefinedStructDeterministic **********
struct Z_Construct_UFunction_UBpxReflectionOps_CreateUserDefinedStructDeterministic_Statics
{
	struct BpxReflectionOps_eventCreateUserDefinedStructDeterministic_Parms
	{
		FString PackagePath;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Create a new `UUserDefinedStruct` asset at the supplied `/Game/...`\n\x09 * package path. Fourth (and most complex) slice of the M28.4 non-BP\n\x09 * asset-factory catalog.\n\x09 *\n\x09 * Wraps `FStructureEditorUtils::CreateUserDefinedStruct(Pkg, FName(ShortName),\n\x09 * RF_Public | RF_Standalone | RF_Transactional)`. The engine helper:\n\x09 *   1. Allocates the UUserDefinedStruct + its inner\n\x09 *      UUserDefinedStructEditorData via `NewObject`.\n\x09 *   2. Assigns `Struct->Guid = FGuid::NewGuid()` (StructureEditorUtils.cpp:53)\n\x09 *      \xe2\x80\x94 first determinism trap.\n\x09 *   3. Auto-adds a default `bool` member via `AddVariable(Struct, FEdGraphPinType(PC_Boolean, ...))`\n\x09 *      (StructureEditorUtils.cpp:60), which itself assigns\n\x09 *      `VarGuid = FGuid::NewGuid()` (:303) \xe2\x80\x94 second determinism trap.\n\x09 *   4. Routes the auto-member's VarName through\n\x09 *      `FMemberVariableNameHelper::Generate(Struct, DisplayName, Guid)`\n\x09 *      so VarName is derived from the random VarGuid.\n\x09 *\n\x09 * Post-create we close both traps:\n\x09 *   - Overwrite `Struct->Guid` with\n\x09 *     `SeedGuidFromJoined(PackagePath + \":uds\")`.\n\x09 *   - Rename the auto-bool to friendly name `BpxAutoBool`, seed its\n\x09 *     VarGuid with `SeedGuidFromJoined(PackagePath + \":uds_var:BpxAutoBool\")`,\n\x09 *     then call `FStructureEditorUtils::RenameVariable(Struct, SeededGuid,\n\x09 *     \"BpxAutoBool\")` so `VarName` regenerates from seed + friendly and the\n\x09 *     UScriptStruct's FProperty chain recompiles with the seeded shape.\n\x09 *\n\x09 * The auto-bool is intentionally left in place (renamed, not removed):\n\x09 * `RemoveVariable` refuses to empty the struct (`bAllowToMakeEmpty=false`,\n\x09 * StructureEditorUtils.cpp:327), and chaining add \xe2\x86\x92 remove would double the\n\x09 * op count for the same end state. Plan authors drive further structure via\n\x09 * `AddUserDefinedStructMember` and optionally `RemoveUserDefinedStructMember`\n\x09 * to drop the auto-bool once at least one real member is present.\n\x09 *\n\x09 * Idempotent on `PackagePath`: if a `UUserDefinedStruct` already exists at\n\x09 * the path, returns `bSuccess=true, bSkipped=true` with `AfterText=PackagePath`.\n\x09 * Wrong-class collision at the path \xe2\x86\x92 structured error (silent stacking\n\x09 * would be a plan-level mistake).\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(UDS)` after create.\n\x09 *\n\x09 * Result shape:\n\x09 *   BeforeText: `\"no-uds\"` on create, `\"uds-exists\"` on skip.\n\x09 *   AfterText:  the created/existing UDS's `/Game/...` path.\n\x09 *\n\x09 * Thread: game-thread only. `FStructureEditorUtils::CreateUserDefinedStruct`\n\x09 * is editor-only and not thread-safe.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Create a new `UUserDefinedStruct` asset at the supplied `/Game/...`\npackage path. Fourth (and most complex) slice of the M28.4 non-BP\nasset-factory catalog.\n\nWraps `FStructureEditorUtils::CreateUserDefinedStruct(Pkg, FName(ShortName),\nRF_Public | RF_Standalone | RF_Transactional)`. The engine helper:\n  1. Allocates the UUserDefinedStruct + its inner\n     UUserDefinedStructEditorData via `NewObject`.\n  2. Assigns `Struct->Guid = FGuid::NewGuid()` (StructureEditorUtils.cpp:53)\n     \xe2\x80\x94 first determinism trap.\n  3. Auto-adds a default `bool` member via `AddVariable(Struct, FEdGraphPinType(PC_Boolean, ...))`\n     (StructureEditorUtils.cpp:60), which itself assigns\n     `VarGuid = FGuid::NewGuid()` (:303) \xe2\x80\x94 second determinism trap.\n  4. Routes the auto-member's VarName through\n     `FMemberVariableNameHelper::Generate(Struct, DisplayName, Guid)`\n     so VarName is derived from the random VarGuid.\n\nPost-create we close both traps:\n  - Overwrite `Struct->Guid` with\n    `SeedGuidFromJoined(PackagePath + \":uds\")`.\n  - Rename the auto-bool to friendly name `BpxAutoBool`, seed its\n    VarGuid with `SeedGuidFromJoined(PackagePath + \":uds_var:BpxAutoBool\")`,\n    then call `FStructureEditorUtils::RenameVariable(Struct, SeededGuid,\n    \"BpxAutoBool\")` so `VarName` regenerates from seed + friendly and the\n    UScriptStruct's FProperty chain recompiles with the seeded shape.\n\nThe auto-bool is intentionally left in place (renamed, not removed):\n`RemoveVariable` refuses to empty the struct (`bAllowToMakeEmpty=false`,\nStructureEditorUtils.cpp:327), and chaining add \xe2\x86\x92 remove would double the\nop count for the same end state. Plan authors drive further structure via\n`AddUserDefinedStructMember` and optionally `RemoveUserDefinedStructMember`\nto drop the auto-bool once at least one real member is present.\n\nIdempotent on `PackagePath`: if a `UUserDefinedStruct` already exists at\nthe path, returns `bSuccess=true, bSkipped=true` with `AfterText=PackagePath`.\nWrong-class collision at the path \xe2\x86\x92 structured error (silent stacking\nwould be a plan-level mistake).\n\nCaller is responsible for `CompileAndSavePackage(UDS)` after create.\n\nResult shape:\n  BeforeText: `\"no-uds\"` on create, `\"uds-exists\"` on skip.\n  AfterText:  the created/existing UDS's `/Game/...` path.\n\nThread: game-thread only. `FStructureEditorUtils::CreateUserDefinedStruct`\nis editor-only and not thread-safe." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PackagePath_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function CreateUserDefinedStructDeterministic constinit property declarations **
	static const UECodeGen_Private::FStrPropertyParams NewProp_PackagePath;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function CreateUserDefinedStructDeterministic constinit property declarations ****
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function CreateUserDefinedStructDeterministic Property Definitions *************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_CreateUserDefinedStructDeterministic_Statics::NewProp_PackagePath = { "PackagePath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventCreateUserDefinedStructDeterministic_Parms, PackagePath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PackagePath_MetaData), NewProp_PackagePath_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_CreateUserDefinedStructDeterministic_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventCreateUserDefinedStructDeterministic_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_CreateUserDefinedStructDeterministic_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_CreateUserDefinedStructDeterministic_Statics::NewProp_PackagePath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_CreateUserDefinedStructDeterministic_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_CreateUserDefinedStructDeterministic_Statics::PropPointers) < 2048);
// ********** End Function CreateUserDefinedStructDeterministic Property Definitions ***************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_CreateUserDefinedStructDeterministic_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "CreateUserDefinedStructDeterministic", 	Z_Construct_UFunction_UBpxReflectionOps_CreateUserDefinedStructDeterministic_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_CreateUserDefinedStructDeterministic_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_CreateUserDefinedStructDeterministic_Statics::BpxReflectionOps_eventCreateUserDefinedStructDeterministic_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_CreateUserDefinedStructDeterministic_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_CreateUserDefinedStructDeterministic_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_CreateUserDefinedStructDeterministic_Statics::BpxReflectionOps_eventCreateUserDefinedStructDeterministic_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_CreateUserDefinedStructDeterministic()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_CreateUserDefinedStructDeterministic_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execCreateUserDefinedStructDeterministic)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_PackagePath);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::CreateUserDefinedStructDeterministic(Z_Param_PackagePath);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function CreateUserDefinedStructDeterministic ************

// ********** Begin Class UBpxReflectionOps Function FindGraphEndpoints ****************************
struct Z_Construct_UFunction_UBpxReflectionOps_FindGraphEndpoints_Statics
{
	struct BpxReflectionOps_eventFindGraphEndpoints_Parms
	{
		UBlueprint* Blueprint;
		FName FunctionName;
		FBpxGraphEndpoints ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Resolve UK2Node_FunctionEntry + UK2Node_FunctionResult for a function\n\x09 * graph on Blueprint by name. Returns their NodeGuids so callers can\n\x09 * reference Entry / Return by GUID in subsequent ConnectPinsByName\n\x09 * calls. ReturnGuid is intentionally zero for void / no-return\n\x09 * signatures \xe2\x80\x94 not an error.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Resolve UK2Node_FunctionEntry + UK2Node_FunctionResult for a function\ngraph on Blueprint by name. Returns their NodeGuids so callers can\nreference Entry / Return by GUID in subsequent ConnectPinsByName\ncalls. ReturnGuid is intentionally zero for void / no-return\nsignatures \xe2\x80\x94 not an error." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function FindGraphEndpoints constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_FunctionName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function FindGraphEndpoints constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function FindGraphEndpoints Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_FindGraphEndpoints_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventFindGraphEndpoints_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_FindGraphEndpoints_Statics::NewProp_FunctionName = { "FunctionName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventFindGraphEndpoints_Parms, FunctionName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_FindGraphEndpoints_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventFindGraphEndpoints_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxGraphEndpoints, METADATA_PARAMS(0, nullptr) }; // 39012202
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_FindGraphEndpoints_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_FindGraphEndpoints_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_FindGraphEndpoints_Statics::NewProp_FunctionName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_FindGraphEndpoints_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_FindGraphEndpoints_Statics::PropPointers) < 2048);
// ********** End Function FindGraphEndpoints Property Definitions *********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_FindGraphEndpoints_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "FindGraphEndpoints", 	Z_Construct_UFunction_UBpxReflectionOps_FindGraphEndpoints_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_FindGraphEndpoints_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_FindGraphEndpoints_Statics::BpxReflectionOps_eventFindGraphEndpoints_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_FindGraphEndpoints_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_FindGraphEndpoints_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_FindGraphEndpoints_Statics::BpxReflectionOps_eventFindGraphEndpoints_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_FindGraphEndpoints()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_FindGraphEndpoints_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execFindGraphEndpoints)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_FunctionName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxGraphEndpoints*)Z_Param__Result=UBpxReflectionOps::FindGraphEndpoints(Z_Param_Blueprint,Z_Param_FunctionName);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function FindGraphEndpoints ******************************

// ********** Begin Class UBpxReflectionOps Function FindSubobject *********************************
struct Z_Construct_UFunction_UBpxReflectionOps_FindSubobject_Statics
{
	struct BpxReflectionOps_eventFindSubobject_Parms
	{
		UObject* Root;
		FName SubobjectName;
		UObject* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Walk Outer chain or named subobjects to find a UObject by short name.\n\x09 * Useful for reaching editor-only subobjects Python can't load directly\n\x09 * (e.g., UStateTreeEditorData owned by a UStateTree).\n\x09 *\n\x09 * Resolution order: outer-walk (Outer / GetTypedOuter) then recursive\n\x09 * subobject traversal via GetObjectsWithOuter.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Walk Outer chain or named subobjects to find a UObject by short name.\nUseful for reaching editor-only subobjects Python can't load directly\n(e.g., UStateTreeEditorData owned by a UStateTree).\n\nResolution order: outer-walk (Outer / GetTypedOuter) then recursive\nsubobject traversal via GetObjectsWithOuter." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function FindSubobject constinit property declarations *************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FNamePropertyParams NewProp_SubobjectName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function FindSubobject constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function FindSubobject Property Definitions ************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_FindSubobject_Statics::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventFindSubobject_Parms, Root), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_FindSubobject_Statics::NewProp_SubobjectName = { "SubobjectName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventFindSubobject_Parms, SubobjectName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_FindSubobject_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventFindSubobject_Parms, ReturnValue), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_FindSubobject_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_FindSubobject_Statics::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_FindSubobject_Statics::NewProp_SubobjectName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_FindSubobject_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_FindSubobject_Statics::PropPointers) < 2048);
// ********** End Function FindSubobject Property Definitions **************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_FindSubobject_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "FindSubobject", 	Z_Construct_UFunction_UBpxReflectionOps_FindSubobject_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_FindSubobject_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_FindSubobject_Statics::BpxReflectionOps_eventFindSubobject_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_FindSubobject_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_FindSubobject_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_FindSubobject_Statics::BpxReflectionOps_eventFindSubobject_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_FindSubobject()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_FindSubobject_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execFindSubobject)
{
	P_GET_OBJECT(UObject,Z_Param_Root);
	P_GET_PROPERTY(FNameProperty,Z_Param_SubobjectName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UObject**)Z_Param__Result=UBpxReflectionOps::FindSubobject(Z_Param_Root,Z_Param_SubobjectName);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function FindSubobject ***********************************

// ********** Begin Class UBpxReflectionOps Function GetArrayLength ********************************
struct Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength_Statics
{
	struct BpxReflectionOps_eventGetArrayLength_Parms
	{
		UObject* Root;
		TArray<FString> Path;
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Get length of an array property addressed by Path. Returns -1 on error\n\x09 * (which is also a valid FBpxReflectionResult::ErrorMessage condition);\n\x09 * callers should prefer the variant below that returns a full result.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get length of an array property addressed by Path. Returns -1 on error\n(which is also a valid FBpxReflectionResult::ErrorMessage condition);\ncallers should prefer the variant below that returns a full result." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Path_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetArrayLength constinit property declarations ************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Path_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Path;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetArrayLength constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetArrayLength Property Definitions ***********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength_Statics::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventGetArrayLength_Parms, Root), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength_Statics::NewProp_Path_Inner = { "Path", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength_Statics::NewProp_Path = { "Path", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventGetArrayLength_Parms, Path), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Path_MetaData), NewProp_Path_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventGetArrayLength_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength_Statics::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength_Statics::NewProp_Path_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength_Statics::NewProp_Path,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength_Statics::PropPointers) < 2048);
// ********** End Function GetArrayLength Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "GetArrayLength", 	Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength_Statics::BpxReflectionOps_eventGetArrayLength_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength_Statics::BpxReflectionOps_eventGetArrayLength_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execGetArrayLength)
{
	P_GET_OBJECT(UObject,Z_Param_Root);
	P_GET_TARRAY_REF(FString,Z_Param_Out_Path);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=UBpxReflectionOps::GetArrayLength(Z_Param_Root,Z_Param_Out_Path);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function GetArrayLength **********************************

// ********** Begin Class UBpxReflectionOps Function GetObjectPropertyValue ************************
struct Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue_Statics
{
	struct BpxReflectionOps_eventGetObjectPropertyValue_Parms
	{
		UObject* Root;
		TArray<FString> Path;
		UObject* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Read a UObject property's value directly (no ExportText parsing).\n\x09 * Returns nullptr both on error and on \"property holds null\" \xe2\x80\x94 check\n\x09 * a GetPropertyValue result if you need to distinguish.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Read a UObject property's value directly (no ExportText parsing).\nReturns nullptr both on error and on \"property holds null\" \xe2\x80\x94 check\na GetPropertyValue result if you need to distinguish." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Path_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetObjectPropertyValue constinit property declarations ****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Path_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Path;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetObjectPropertyValue constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetObjectPropertyValue Property Definitions ***************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue_Statics::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventGetObjectPropertyValue_Parms, Root), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue_Statics::NewProp_Path_Inner = { "Path", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue_Statics::NewProp_Path = { "Path", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventGetObjectPropertyValue_Parms, Path), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Path_MetaData), NewProp_Path_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventGetObjectPropertyValue_Parms, ReturnValue), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue_Statics::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue_Statics::NewProp_Path_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue_Statics::NewProp_Path,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue_Statics::PropPointers) < 2048);
// ********** End Function GetObjectPropertyValue Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "GetObjectPropertyValue", 	Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue_Statics::BpxReflectionOps_eventGetObjectPropertyValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue_Statics::BpxReflectionOps_eventGetObjectPropertyValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execGetObjectPropertyValue)
{
	P_GET_OBJECT(UObject,Z_Param_Root);
	P_GET_TARRAY_REF(FString,Z_Param_Out_Path);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UObject**)Z_Param__Result=UBpxReflectionOps::GetObjectPropertyValue(Z_Param_Root,Z_Param_Out_Path);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function GetObjectPropertyValue **************************

// ********** Begin Class UBpxReflectionOps Function GetPropertyValue ******************************
struct Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue_Statics
{
	struct BpxReflectionOps_eventGetPropertyValue_Parms
	{
		UObject* Root;
		TArray<FString> Path;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Read a property value by path. Returns the value as ExportText\n\x09 * (same format as FProperty::ExportTextItem_Direct produces).\n\x09 *\n\x09 * @param Root The starting UObject.\n\x09 * @param Path Sequence of property names. Array elements are addressed\n\x09 *             with \"[N]\" notation, e.g. `[\"SensesConfig\", \"[0]\", \"SightRadius\"]`.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Read a property value by path. Returns the value as ExportText\n(same format as FProperty::ExportTextItem_Direct produces).\n\n@param Root The starting UObject.\n@param Path Sequence of property names. Array elements are addressed\n            with \"[N]\" notation, e.g. `[\"SensesConfig\", \"[0]\", \"SightRadius\"]`." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Path_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetPropertyValue constinit property declarations **********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Path_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Path;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetPropertyValue constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetPropertyValue Property Definitions *********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue_Statics::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventGetPropertyValue_Parms, Root), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue_Statics::NewProp_Path_Inner = { "Path", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue_Statics::NewProp_Path = { "Path", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventGetPropertyValue_Parms, Path), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Path_MetaData), NewProp_Path_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventGetPropertyValue_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue_Statics::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue_Statics::NewProp_Path_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue_Statics::NewProp_Path,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue_Statics::PropPointers) < 2048);
// ********** End Function GetPropertyValue Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "GetPropertyValue", 	Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue_Statics::BpxReflectionOps_eventGetPropertyValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue_Statics::BpxReflectionOps_eventGetPropertyValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execGetPropertyValue)
{
	P_GET_OBJECT(UObject,Z_Param_Root);
	P_GET_TARRAY_REF(FString,Z_Param_Out_Path);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::GetPropertyValue(Z_Param_Root,Z_Param_Out_Path);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function GetPropertyValue ********************************

// ********** Begin Class UBpxReflectionOps Function NewSubobject **********************************
struct Z_Construct_UFunction_UBpxReflectionOps_NewSubobject_Statics
{
	struct BpxReflectionOps_eventNewSubobject_Parms
	{
		UObject* Outer;
		UClass* Class;
		FName BaseName;
		UObject* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Create a new UObject of `Class` with `Outer` as its owner. Used for\n\x09 * constructing editor-only subobject instances (e.g. a BP-wrapped\n\x09 * StateTree condition instance that will be pointed-to by\n\x09 * FStateTreeEditorNode::InstanceObject).\n\x09 *\n\x09 * BaseName optional \xe2\x80\x94 NAME_None auto-generates a unique name.\n\x09 * Always created with RF_Public | RF_Transactional so the editor\n\x09 * treats it as undoable.\n\x09 *\n\x09 * @return The newly-created UObject, or nullptr on error.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Create a new UObject of `Class` with `Outer` as its owner. Used for\nconstructing editor-only subobject instances (e.g. a BP-wrapped\nStateTree condition instance that will be pointed-to by\nFStateTreeEditorNode::InstanceObject).\n\nBaseName optional \xe2\x80\x94 NAME_None auto-generates a unique name.\nAlways created with RF_Public | RF_Transactional so the editor\ntreats it as undoable.\n\n@return The newly-created UObject, or nullptr on error." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function NewSubobject constinit property declarations **************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Outer;
	static const UECodeGen_Private::FClassPropertyParams NewProp_Class;
	static const UECodeGen_Private::FNamePropertyParams NewProp_BaseName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function NewSubobject constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function NewSubobject Property Definitions *************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_NewSubobject_Statics::NewProp_Outer = { "Outer", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventNewSubobject_Parms, Outer), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UFunction_UBpxReflectionOps_NewSubobject_Statics::NewProp_Class = { "Class", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventNewSubobject_Parms, Class), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_NewSubobject_Statics::NewProp_BaseName = { "BaseName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventNewSubobject_Parms, BaseName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_NewSubobject_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventNewSubobject_Parms, ReturnValue), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_NewSubobject_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_NewSubobject_Statics::NewProp_Outer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_NewSubobject_Statics::NewProp_Class,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_NewSubobject_Statics::NewProp_BaseName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_NewSubobject_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_NewSubobject_Statics::PropPointers) < 2048);
// ********** End Function NewSubobject Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_NewSubobject_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "NewSubobject", 	Z_Construct_UFunction_UBpxReflectionOps_NewSubobject_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_NewSubobject_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_NewSubobject_Statics::BpxReflectionOps_eventNewSubobject_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_NewSubobject_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_NewSubobject_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_NewSubobject_Statics::BpxReflectionOps_eventNewSubobject_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_NewSubobject()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_NewSubobject_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execNewSubobject)
{
	P_GET_OBJECT(UObject,Z_Param_Outer);
	P_GET_OBJECT(UClass,Z_Param_Class);
	P_GET_PROPERTY(FNameProperty,Z_Param_BaseName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UObject**)Z_Param__Result=UBpxReflectionOps::NewSubobject(Z_Param_Outer,Z_Param_Class,Z_Param_BaseName);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function NewSubobject ************************************

// ********** Begin Class UBpxReflectionOps Function OverrideInterfaceFunction *********************
struct Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction_Statics
{
	struct BpxReflectionOps_eventOverrideInterfaceFunction_Parms
	{
		UBlueprint* Blueprint;
		UClass* InterfaceClass;
		FName FunctionName;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Create an override function graph for an interface function on the\n\x09 * target Blueprint. Scoped to the interface-override case \xe2\x80\x94 caller\n\x09 * passes the resolved UInterface's generated class so we don't walk\n\x09 * the parent hierarchy. The new graph is populated with default\n\x09 * UK2Node_FunctionEntry + UK2Node_FunctionResult by\n\x09 * FBlueprintEditorUtils::AddFunctionGraph; we then overwrite those\n\x09 * two nodes' NodeGuids with md5-seeded values so the post-op asset is\n\x09 * byte-deterministic across re-generation \xe2\x80\x94 the golden BugHunt fixture\n\x09 * strategy depends on this.\n\x09 *\n\x09 * Idempotent: returns bSuccess=true, bSkipped=true if a graph with\n\x09 * FunctionName already exists on Blueprint->FunctionGraphs (leaves\n\x09 * the existing graph unchanged).\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Create an override function graph for an interface function on the\ntarget Blueprint. Scoped to the interface-override case \xe2\x80\x94 caller\npasses the resolved UInterface's generated class so we don't walk\nthe parent hierarchy. The new graph is populated with default\nUK2Node_FunctionEntry + UK2Node_FunctionResult by\nFBlueprintEditorUtils::AddFunctionGraph; we then overwrite those\ntwo nodes' NodeGuids with md5-seeded values so the post-op asset is\nbyte-deterministic across re-generation \xe2\x80\x94 the golden BugHunt fixture\nstrategy depends on this.\n\nIdempotent: returns bSuccess=true, bSkipped=true if a graph with\nFunctionName already exists on Blueprint->FunctionGraphs (leaves\nthe existing graph unchanged)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function OverrideInterfaceFunction constinit property declarations *************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FClassPropertyParams NewProp_InterfaceClass;
	static const UECodeGen_Private::FNamePropertyParams NewProp_FunctionName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function OverrideInterfaceFunction constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function OverrideInterfaceFunction Property Definitions ************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventOverrideInterfaceFunction_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction_Statics::NewProp_InterfaceClass = { "InterfaceClass", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventOverrideInterfaceFunction_Parms, InterfaceClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction_Statics::NewProp_FunctionName = { "FunctionName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventOverrideInterfaceFunction_Parms, FunctionName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventOverrideInterfaceFunction_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction_Statics::NewProp_InterfaceClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction_Statics::NewProp_FunctionName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction_Statics::PropPointers) < 2048);
// ********** End Function OverrideInterfaceFunction Property Definitions **************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "OverrideInterfaceFunction", 	Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction_Statics::BpxReflectionOps_eventOverrideInterfaceFunction_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction_Statics::BpxReflectionOps_eventOverrideInterfaceFunction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execOverrideInterfaceFunction)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_OBJECT(UClass,Z_Param_InterfaceClass);
	P_GET_PROPERTY(FNameProperty,Z_Param_FunctionName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::OverrideInterfaceFunction(Z_Param_Blueprint,Z_Param_InterfaceClass,Z_Param_FunctionName);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function OverrideInterfaceFunction ***********************

// ********** Begin Class UBpxReflectionOps Function RemoveEnvQueryTest ****************************
struct Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest_Statics
{
	struct BpxReflectionOps_eventRemoveEnvQueryTest_Parms
	{
		UEnvQuery* Query;
		int32 OptionIndex;
		int32 TestIndex;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Remove the test at `Options[OptionIndex].Tests[TestIndex]` and reseat\n\x09 * `TestOrder` on every subsequent test so the `0..N-1` invariant holds.\n\x09 * Symmetric counterpart of `AddEnvQueryTest`.\n\x09 *\n\x09 * Idempotent on `(Query, OptionIndex, TestIndex)`: an out-of-range\n\x09 * `TestIndex` (e.g. a re-apply after a successful prior run removed\n\x09 * the same test) returns `bSuccess=true, bSkipped=true` with\n\x09 * `AfterText=\"already-removed:<test_index>\"`. OptionIndex still has a\n\x09 * hard bounds check \xe2\x80\x94 option identity is stable across test removals,\n\x09 * so an out-of-range option indicates a plan-level misunderstanding.\n\x09 *\n\x09 * Result shape:\n\x09 *   BeforeText: `\"tests=<N>\"` (pre-remove count on the target option)\n\x09 *   AfterText:  `\"removed-index:<test_index>\"` on actual removal,\n\x09 *               `\"already-removed:<test_index>\"` on the idempotent\n\x09 *               skip path.\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(Query)` after the\n\x09 * remove.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Remove the test at `Options[OptionIndex].Tests[TestIndex]` and reseat\n`TestOrder` on every subsequent test so the `0..N-1` invariant holds.\nSymmetric counterpart of `AddEnvQueryTest`.\n\nIdempotent on `(Query, OptionIndex, TestIndex)`: an out-of-range\n`TestIndex` (e.g. a re-apply after a successful prior run removed\nthe same test) returns `bSuccess=true, bSkipped=true` with\n`AfterText=\"already-removed:<test_index>\"`. OptionIndex still has a\nhard bounds check \xe2\x80\x94 option identity is stable across test removals,\nso an out-of-range option indicates a plan-level misunderstanding.\n\nResult shape:\n  BeforeText: `\"tests=<N>\"` (pre-remove count on the target option)\n  AfterText:  `\"removed-index:<test_index>\"` on actual removal,\n              `\"already-removed:<test_index>\"` on the idempotent\n              skip path.\n\nCaller is responsible for `CompileAndSavePackage(Query)` after the\nremove." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function RemoveEnvQueryTest constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Query;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OptionIndex;
	static const UECodeGen_Private::FIntPropertyParams NewProp_TestIndex;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RemoveEnvQueryTest constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RemoveEnvQueryTest Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest_Statics::NewProp_Query = { "Query", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventRemoveEnvQueryTest_Parms, Query), Z_Construct_UClass_UEnvQuery_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest_Statics::NewProp_OptionIndex = { "OptionIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventRemoveEnvQueryTest_Parms, OptionIndex), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest_Statics::NewProp_TestIndex = { "TestIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventRemoveEnvQueryTest_Parms, TestIndex), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventRemoveEnvQueryTest_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest_Statics::NewProp_Query,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest_Statics::NewProp_OptionIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest_Statics::NewProp_TestIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest_Statics::PropPointers) < 2048);
// ********** End Function RemoveEnvQueryTest Property Definitions *********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "RemoveEnvQueryTest", 	Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest_Statics::BpxReflectionOps_eventRemoveEnvQueryTest_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest_Statics::BpxReflectionOps_eventRemoveEnvQueryTest_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execRemoveEnvQueryTest)
{
	P_GET_OBJECT(UEnvQuery,Z_Param_Query);
	P_GET_PROPERTY(FIntProperty,Z_Param_OptionIndex);
	P_GET_PROPERTY(FIntProperty,Z_Param_TestIndex);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::RemoveEnvQueryTest(Z_Param_Query,Z_Param_OptionIndex,Z_Param_TestIndex);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function RemoveEnvQueryTest ******************************

// ********** Begin Class UBpxReflectionOps Function RemoveUserDefinedStructMember *****************
struct Z_Construct_UFunction_UBpxReflectionOps_RemoveUserDefinedStructMember_Statics
{
	struct BpxReflectionOps_eventRemoveUserDefinedStructMember_Parms
	{
		UUserDefinedStruct* Struct;
		FName FriendlyName;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Remove a member variable by friendly name from a `UUserDefinedStruct`.\n\x09 * Wraps `FStructureEditorUtils::RemoveVariable` after resolving the\n\x09 * friendly name \xe2\x86\x92 VarGuid on the target struct's VarDescriptions array.\n\x09 *\n\x09 * Idempotent on `FriendlyName`: if no member with that friendly name\n\x09 * exists, returns `bSuccess=true, bSkipped=true` with\n\x09 * `AfterText=\"already-removed:<FriendlyName>\"`.\n\x09 *\n\x09 * Refuses to empty the struct: if the target member is the last one\n\x09 * (pre-remove count == 1), returns a structured error matching the\n\x09 * engine's `bAllowToMakeEmpty=false` invariant\n\x09 * (StructureEditorUtils.cpp:327). Plan authors who want an \"empty\"\n\x09 * logical struct should add the replacement member BEFORE removing\n\x09 * the placeholder, not after.\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(UDS)` after the remove.\n\x09 *\n\x09 * Result shape:\n\x09 *   BeforeText: `\"members=<pre_count>\"` on remove, `\"no-member:<FriendlyName>\"` on skip.\n\x09 *   AfterText:  `\"member-removed:<FriendlyName>\"` /\n\x09 *               `\"already-removed:<FriendlyName>\"`.\n\x09 *\n\x09 * Thread: game-thread only.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Remove a member variable by friendly name from a `UUserDefinedStruct`.\nWraps `FStructureEditorUtils::RemoveVariable` after resolving the\nfriendly name \xe2\x86\x92 VarGuid on the target struct's VarDescriptions array.\n\nIdempotent on `FriendlyName`: if no member with that friendly name\nexists, returns `bSuccess=true, bSkipped=true` with\n`AfterText=\"already-removed:<FriendlyName>\"`.\n\nRefuses to empty the struct: if the target member is the last one\n(pre-remove count == 1), returns a structured error matching the\nengine's `bAllowToMakeEmpty=false` invariant\n(StructureEditorUtils.cpp:327). Plan authors who want an \"empty\"\nlogical struct should add the replacement member BEFORE removing\nthe placeholder, not after.\n\nCaller is responsible for `CompileAndSavePackage(UDS)` after the remove.\n\nResult shape:\n  BeforeText: `\"members=<pre_count>\"` on remove, `\"no-member:<FriendlyName>\"` on skip.\n  AfterText:  `\"member-removed:<FriendlyName>\"` /\n              `\"already-removed:<FriendlyName>\"`.\n\nThread: game-thread only." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function RemoveUserDefinedStructMember constinit property declarations *********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Struct;
	static const UECodeGen_Private::FNamePropertyParams NewProp_FriendlyName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RemoveUserDefinedStructMember constinit property declarations ***********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RemoveUserDefinedStructMember Property Definitions ********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_RemoveUserDefinedStructMember_Statics::NewProp_Struct = { "Struct", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventRemoveUserDefinedStructMember_Parms, Struct), Z_Construct_UClass_UUserDefinedStruct_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_RemoveUserDefinedStructMember_Statics::NewProp_FriendlyName = { "FriendlyName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventRemoveUserDefinedStructMember_Parms, FriendlyName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_RemoveUserDefinedStructMember_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventRemoveUserDefinedStructMember_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_RemoveUserDefinedStructMember_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_RemoveUserDefinedStructMember_Statics::NewProp_Struct,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_RemoveUserDefinedStructMember_Statics::NewProp_FriendlyName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_RemoveUserDefinedStructMember_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_RemoveUserDefinedStructMember_Statics::PropPointers) < 2048);
// ********** End Function RemoveUserDefinedStructMember Property Definitions **********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_RemoveUserDefinedStructMember_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "RemoveUserDefinedStructMember", 	Z_Construct_UFunction_UBpxReflectionOps_RemoveUserDefinedStructMember_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_RemoveUserDefinedStructMember_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_RemoveUserDefinedStructMember_Statics::BpxReflectionOps_eventRemoveUserDefinedStructMember_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_RemoveUserDefinedStructMember_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_RemoveUserDefinedStructMember_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_RemoveUserDefinedStructMember_Statics::BpxReflectionOps_eventRemoveUserDefinedStructMember_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_RemoveUserDefinedStructMember()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_RemoveUserDefinedStructMember_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execRemoveUserDefinedStructMember)
{
	P_GET_OBJECT(UUserDefinedStruct,Z_Param_Struct);
	P_GET_PROPERTY(FNameProperty,Z_Param_FriendlyName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::RemoveUserDefinedStructMember(Z_Param_Struct,Z_Param_FriendlyName);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function RemoveUserDefinedStructMember *******************

// ********** Begin Class UBpxReflectionOps Function SetCurveFloatKeys *****************************
struct Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys_Statics
{
	struct BpxReflectionOps_eventSetCurveFloatKeys_Parms
	{
		UCurveFloat* Curve;
		TArray<FRichCurveKey> NewKeys;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Wholesale-replace the `FRichCurveKey` array on a `UCurveFloat`'s\n\x09 * `FloatCurve` with `NewKeys`. Second op of the M28.4 catalog.\n\x09 *\n\x09 * Mirrors the `FRichCurve::SetKeys` API \xe2\x80\x94 caller pre-sorts the keys\n\x09 * by Time ascending. Unsorted input is rejected up-front with a\n\x09 * structured error because UE's `FRichCurve::Evaluate` assumes sorted\n\x09 * storage and would silently sample incorrectly otherwise.\n\x09 *\n\x09 * Scope is deliberately wholesale-replace (not per-key add/remove)\n\x09 * per the M28.4.0 research \xe2\x80\x94 matches the authoring style for the\n\x09 * design.md intensity-curve use case (re-author a 4-point curve when\n\x09 * tuning, rather than incrementally patching one point). Per-key ops\n\x09 * (`AddCurveFloatKey` / `SetCurveFloatKey` / `RemoveCurveFloatKey`)\n\x09 * are deferred until a concrete driver surfaces the need.\n\x09 *\n\x09 * Idempotent on element-wise `(Time, Value, InterpMode)` equality: if\n\x09 * the existing key array already matches `NewKeys` on those fields in\n\x09 * order, returns `bSuccess=true, bSkipped=true` without touching the\n\x09 * asset. Tangent fields are excluded from the compare because the\n\x09 * M28.4.1 Python surface only accepts Time+Value (tangent defaults\n\x09 * roll through `FRichCurveKey`'s zero-initialiser, which the engine\n\x09 * normalises on load).\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(Curve)` after the\n\x09 * mutation \xe2\x80\x94 same pattern as the EQS write-side ops.\n\x09 *\n\x09 * Result shape:\n\x09 *   BeforeText: `\"keys=<pre_count>\"`.\n\x09 *   AfterText:  `\"keys=<new_count>\"` \xe2\x80\x94 decimal so the soak harness\n\x09 *               can cross-check via the standard `after_text` read.\n\x09 *\n\x09 * Thread: game-thread only. `FRichCurve::SetKeys` + `SetDirtyFlag`\n\x09 * are not thread-safe.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Wholesale-replace the `FRichCurveKey` array on a `UCurveFloat`'s\n`FloatCurve` with `NewKeys`. Second op of the M28.4 catalog.\n\nMirrors the `FRichCurve::SetKeys` API \xe2\x80\x94 caller pre-sorts the keys\nby Time ascending. Unsorted input is rejected up-front with a\nstructured error because UE's `FRichCurve::Evaluate` assumes sorted\nstorage and would silently sample incorrectly otherwise.\n\nScope is deliberately wholesale-replace (not per-key add/remove)\nper the M28.4.0 research \xe2\x80\x94 matches the authoring style for the\ndesign.md intensity-curve use case (re-author a 4-point curve when\ntuning, rather than incrementally patching one point). Per-key ops\n(`AddCurveFloatKey` / `SetCurveFloatKey` / `RemoveCurveFloatKey`)\nare deferred until a concrete driver surfaces the need.\n\nIdempotent on element-wise `(Time, Value, InterpMode)` equality: if\nthe existing key array already matches `NewKeys` on those fields in\norder, returns `bSuccess=true, bSkipped=true` without touching the\nasset. Tangent fields are excluded from the compare because the\nM28.4.1 Python surface only accepts Time+Value (tangent defaults\nroll through `FRichCurveKey`'s zero-initialiser, which the engine\nnormalises on load).\n\nCaller is responsible for `CompileAndSavePackage(Curve)` after the\nmutation \xe2\x80\x94 same pattern as the EQS write-side ops.\n\nResult shape:\n  BeforeText: `\"keys=<pre_count>\"`.\n  AfterText:  `\"keys=<new_count>\"` \xe2\x80\x94 decimal so the soak harness\n              can cross-check via the standard `after_text` read.\n\nThread: game-thread only. `FRichCurve::SetKeys` + `SetDirtyFlag`\nare not thread-safe." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewKeys_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetCurveFloatKeys constinit property declarations *********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Curve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewKeys_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_NewKeys;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetCurveFloatKeys constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetCurveFloatKeys Property Definitions ********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys_Statics::NewProp_Curve = { "Curve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetCurveFloatKeys_Parms, Curve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys_Statics::NewProp_NewKeys_Inner = { "NewKeys", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FRichCurveKey, METADATA_PARAMS(0, nullptr) }; // 363054195
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys_Statics::NewProp_NewKeys = { "NewKeys", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetCurveFloatKeys_Parms, NewKeys), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewKeys_MetaData), NewProp_NewKeys_MetaData) }; // 363054195
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetCurveFloatKeys_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys_Statics::NewProp_Curve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys_Statics::NewProp_NewKeys_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys_Statics::NewProp_NewKeys,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys_Statics::PropPointers) < 2048);
// ********** End Function SetCurveFloatKeys Property Definitions **********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "SetCurveFloatKeys", 	Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys_Statics::BpxReflectionOps_eventSetCurveFloatKeys_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys_Statics::BpxReflectionOps_eventSetCurveFloatKeys_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execSetCurveFloatKeys)
{
	P_GET_OBJECT(UCurveFloat,Z_Param_Curve);
	P_GET_TARRAY_REF(FRichCurveKey,Z_Param_Out_NewKeys);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::SetCurveFloatKeys(Z_Param_Curve,Z_Param_Out_NewKeys);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function SetCurveFloatKeys *******************************

// ********** Begin Class UBpxReflectionOps Function SetGraphPinLiteralDefault *********************
struct Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics
{
	struct BpxReflectionOps_eventSetGraphPinLiteralDefault_Parms
	{
		UBlueprint* Blueprint;
		FName GraphName;
		FString NodeGuidStr;
		FName PinName;
		FString LiteralText;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Set a pin's literal `DefaultValue` on any node in any K2 graph\n\x09 * (function / interface-override / ubergraph). Sibling of M26.1's\n\x09 * `SetNodePinLiteralDefault` but keyed by `GraphName` (routes through\n\x09 * `FindFunctionGraphByName` to reach all three graph families) and accepts\n\x09 * `NodeGuid` as a string (32-char hex or `{8-4-4-4-12}`), matching the\n\x09 * shape of `ConnectGraphPinsByGuidString`.\n\x09 *\n\x09 * Motivating case: newly-spawned nodes from M28.3.1+ return their runtime\n\x09 * `NodeGuid` as a hex string in the op result; plan authors chain\n\x09 * `set_graph_pin_default` using that string without round-tripping through\n\x09 * the `unreal.Guid` surface.\n\x09 *\n\x09 * Kept separate from M26.1 `SetNodePinLiteralDefault` (which is keyed by\n\x09 * function name + FGuid) to preserve M26.1 callers' semantics unchanged \xe2\x80\x94\n\x09 * same coexistence pattern as `ConnectPinsByName` (M26.1) +\n\x09 * `ConnectGraphPinsByGuidString` (M28.3-narrow).\n\x09 *\n\x09 * Uses `UEdGraphSchema::TrySetDefaultValue` so pin-type coercion +\n\x09 * autogenerated-default updates follow UE's own rules. Idempotent: setting\n\x09 * to the current value returns `bSkipped=true`.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set a pin's literal `DefaultValue` on any node in any K2 graph\n(function / interface-override / ubergraph). Sibling of M26.1's\n`SetNodePinLiteralDefault` but keyed by `GraphName` (routes through\n`FindFunctionGraphByName` to reach all three graph families) and accepts\n`NodeGuid` as a string (32-char hex or `{8-4-4-4-12}`), matching the\nshape of `ConnectGraphPinsByGuidString`.\n\nMotivating case: newly-spawned nodes from M28.3.1+ return their runtime\n`NodeGuid` as a hex string in the op result; plan authors chain\n`set_graph_pin_default` using that string without round-tripping through\nthe `unreal.Guid` surface.\n\nKept separate from M26.1 `SetNodePinLiteralDefault` (which is keyed by\nfunction name + FGuid) to preserve M26.1 callers' semantics unchanged \xe2\x80\x94\nsame coexistence pattern as `ConnectPinsByName` (M26.1) +\n`ConnectGraphPinsByGuidString` (M28.3-narrow).\n\nUses `UEdGraphSchema::TrySetDefaultValue` so pin-type coercion +\nautogenerated-default updates follow UE's own rules. Idempotent: setting\nto the current value returns `bSkipped=true`." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NodeGuidStr_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LiteralText_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetGraphPinLiteralDefault constinit property declarations *************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_GraphName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_NodeGuidStr;
	static const UECodeGen_Private::FNamePropertyParams NewProp_PinName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_LiteralText;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetGraphPinLiteralDefault constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetGraphPinLiteralDefault Property Definitions ************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetGraphPinLiteralDefault_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::NewProp_GraphName = { "GraphName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetGraphPinLiteralDefault_Parms, GraphName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::NewProp_NodeGuidStr = { "NodeGuidStr", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetGraphPinLiteralDefault_Parms, NodeGuidStr), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NodeGuidStr_MetaData), NewProp_NodeGuidStr_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::NewProp_PinName = { "PinName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetGraphPinLiteralDefault_Parms, PinName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::NewProp_LiteralText = { "LiteralText", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetGraphPinLiteralDefault_Parms, LiteralText), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LiteralText_MetaData), NewProp_LiteralText_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetGraphPinLiteralDefault_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::NewProp_GraphName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::NewProp_NodeGuidStr,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::NewProp_PinName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::NewProp_LiteralText,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::PropPointers) < 2048);
// ********** End Function SetGraphPinLiteralDefault Property Definitions **************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "SetGraphPinLiteralDefault", 	Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::BpxReflectionOps_eventSetGraphPinLiteralDefault_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::BpxReflectionOps_eventSetGraphPinLiteralDefault_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execSetGraphPinLiteralDefault)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_GraphName);
	P_GET_PROPERTY(FStrProperty,Z_Param_NodeGuidStr);
	P_GET_PROPERTY(FNameProperty,Z_Param_PinName);
	P_GET_PROPERTY(FStrProperty,Z_Param_LiteralText);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::SetGraphPinLiteralDefault(Z_Param_Blueprint,Z_Param_GraphName,Z_Param_NodeGuidStr,Z_Param_PinName,Z_Param_LiteralText);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function SetGraphPinLiteralDefault ***********************

// ********** Begin Class UBpxReflectionOps Function SetInstancedStructType ************************
struct Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics
{
	struct BpxReflectionOps_eventSetInstancedStructType_Parms
	{
		UObject* Root;
		TArray<FString> Path;
		UScriptStruct* NewType;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Set the type of an FInstancedStruct property, reallocating its backing\n\x09 * storage to hold a default-constructed instance of NewType.\n\x09 *\n\x09 * @return bSuccess=true iff path resolves to an FInstancedStruct property\n\x09 *         and InitializeAs(NewType) completes.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set the type of an FInstancedStruct property, reallocating its backing\nstorage to hold a default-constructed instance of NewType.\n\n@return bSuccess=true iff path resolves to an FInstancedStruct property\n        and InitializeAs(NewType) completes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Path_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetInstancedStructType constinit property declarations ****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Path_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Path;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NewType;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetInstancedStructType constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetInstancedStructType Property Definitions ***************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetInstancedStructType_Parms, Root), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::NewProp_Path_Inner = { "Path", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::NewProp_Path = { "Path", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetInstancedStructType_Parms, Path), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Path_MetaData), NewProp_Path_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::NewProp_NewType = { "NewType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetInstancedStructType_Parms, NewType), Z_Construct_UClass_UScriptStruct_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetInstancedStructType_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::NewProp_Path_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::NewProp_Path,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::NewProp_NewType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::PropPointers) < 2048);
// ********** End Function SetInstancedStructType Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "SetInstancedStructType", 	Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::BpxReflectionOps_eventSetInstancedStructType_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::BpxReflectionOps_eventSetInstancedStructType_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execSetInstancedStructType)
{
	P_GET_OBJECT(UObject,Z_Param_Root);
	P_GET_TARRAY_REF(FString,Z_Param_Out_Path);
	P_GET_OBJECT(UScriptStruct,Z_Param_NewType);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::SetInstancedStructType(Z_Param_Root,Z_Param_Out_Path,Z_Param_NewType);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function SetInstancedStructType **************************

// ********** Begin Class UBpxReflectionOps Function SetNodePinLiteralDefault **********************
struct Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics
{
	struct BpxReflectionOps_eventSetNodePinLiteralDefault_Parms
	{
		UBlueprint* Blueprint;
		FName FunctionName;
		FGuid NodeGuid;
		FName PinName;
		FString LiteralText;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Set a pin's literal DefaultValue. Uses UEdGraphSchema::TrySetDefaultValue\n\x09 * so pin-type coercion + autogenerated-default updates happen per UE's\n\x09 * own rules. Idempotent: setting to the current value returns\n\x09 * bSkipped=true.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set a pin's literal DefaultValue. Uses UEdGraphSchema::TrySetDefaultValue\nso pin-type coercion + autogenerated-default updates happen per UE's\nown rules. Idempotent: setting to the current value returns\nbSkipped=true." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LiteralText_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetNodePinLiteralDefault constinit property declarations **************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_FunctionName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NodeGuid;
	static const UECodeGen_Private::FNamePropertyParams NewProp_PinName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_LiteralText;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetNodePinLiteralDefault constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetNodePinLiteralDefault Property Definitions *************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetNodePinLiteralDefault_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::NewProp_FunctionName = { "FunctionName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetNodePinLiteralDefault_Parms, FunctionName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::NewProp_NodeGuid = { "NodeGuid", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetNodePinLiteralDefault_Parms, NodeGuid), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::NewProp_PinName = { "PinName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetNodePinLiteralDefault_Parms, PinName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::NewProp_LiteralText = { "LiteralText", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetNodePinLiteralDefault_Parms, LiteralText), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LiteralText_MetaData), NewProp_LiteralText_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetNodePinLiteralDefault_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::NewProp_FunctionName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::NewProp_NodeGuid,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::NewProp_PinName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::NewProp_LiteralText,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::PropPointers) < 2048);
// ********** End Function SetNodePinLiteralDefault Property Definitions ***************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "SetNodePinLiteralDefault", 	Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::BpxReflectionOps_eventSetNodePinLiteralDefault_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04822401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::BpxReflectionOps_eventSetNodePinLiteralDefault_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execSetNodePinLiteralDefault)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_FunctionName);
	P_GET_STRUCT(FGuid,Z_Param_NodeGuid);
	P_GET_PROPERTY(FNameProperty,Z_Param_PinName);
	P_GET_PROPERTY(FStrProperty,Z_Param_LiteralText);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::SetNodePinLiteralDefault(Z_Param_Blueprint,Z_Param_FunctionName,Z_Param_NodeGuid,Z_Param_PinName,Z_Param_LiteralText);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function SetNodePinLiteralDefault ************************

// ********** Begin Class UBpxReflectionOps Function SetObjectPropertyValue ************************
struct Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics
{
	struct BpxReflectionOps_eventSetObjectPropertyValue_Parms
	{
		UObject* Root;
		TArray<FString> Path;
		UObject* NewValue;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Set a UObject property's value directly (no ImportText round-trip).\n\x09 * Correct choice for setting object references that point at other\n\x09 * objects you've just created via NewSubobject.\n\x09 *\n\x09 * @return bSuccess=true iff path resolves to an FObjectProperty and\n\x09 *         NewValue (or null) is compatible with the property's expected\n\x09 *         class.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set a UObject property's value directly (no ImportText round-trip).\nCorrect choice for setting object references that point at other\nobjects you've just created via NewSubobject.\n\n@return bSuccess=true iff path resolves to an FObjectProperty and\n        NewValue (or null) is compatible with the property's expected\n        class." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Path_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetObjectPropertyValue constinit property declarations ****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Path_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Path;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NewValue;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetObjectPropertyValue constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetObjectPropertyValue Property Definitions ***************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetObjectPropertyValue_Parms, Root), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::NewProp_Path_Inner = { "Path", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::NewProp_Path = { "Path", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetObjectPropertyValue_Parms, Path), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Path_MetaData), NewProp_Path_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::NewProp_NewValue = { "NewValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetObjectPropertyValue_Parms, NewValue), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetObjectPropertyValue_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::NewProp_Path_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::NewProp_Path,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::NewProp_NewValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::PropPointers) < 2048);
// ********** End Function SetObjectPropertyValue Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "SetObjectPropertyValue", 	Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::BpxReflectionOps_eventSetObjectPropertyValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::BpxReflectionOps_eventSetObjectPropertyValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execSetObjectPropertyValue)
{
	P_GET_OBJECT(UObject,Z_Param_Root);
	P_GET_TARRAY_REF(FString,Z_Param_Out_Path);
	P_GET_OBJECT(UObject,Z_Param_NewValue);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::SetObjectPropertyValue(Z_Param_Root,Z_Param_Out_Path,Z_Param_NewValue);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function SetObjectPropertyValue **************************

// ********** Begin Class UBpxReflectionOps Function SetPropertyValue ******************************
struct Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics
{
	struct BpxReflectionOps_eventSetPropertyValue_Parms
	{
		UObject* Root;
		TArray<FString> Path;
		FString ImportTextValue;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Write a property value by path. Uses FProperty::ImportText_Direct to\n\x09 * coerce ImportTextValue into the property's native type.\n\x09 *\n\x09 * Idempotent: if the before-value already matches ImportTextValue via\n\x09 * string equality, bSkipped is true and no write happens.\n\x09 *\n\x09 * Does NOT call SavePackage \xe2\x80\x94 caller must invoke CompileAndSavePackage\n\x09 * after a batch of edits to persist.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Write a property value by path. Uses FProperty::ImportText_Direct to\ncoerce ImportTextValue into the property's native type.\n\nIdempotent: if the before-value already matches ImportTextValue via\nstring equality, bSkipped is true and no write happens.\n\nDoes NOT call SavePackage \xe2\x80\x94 caller must invoke CompileAndSavePackage\nafter a batch of edits to persist." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Path_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ImportTextValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetPropertyValue constinit property declarations **********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Path_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Path;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ImportTextValue;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetPropertyValue constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetPropertyValue Property Definitions *********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetPropertyValue_Parms, Root), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::NewProp_Path_Inner = { "Path", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::NewProp_Path = { "Path", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetPropertyValue_Parms, Path), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Path_MetaData), NewProp_Path_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::NewProp_ImportTextValue = { "ImportTextValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetPropertyValue_Parms, ImportTextValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ImportTextValue_MetaData), NewProp_ImportTextValue_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetPropertyValue_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::NewProp_Path_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::NewProp_Path,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::NewProp_ImportTextValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::PropPointers) < 2048);
// ********** End Function SetPropertyValue Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "SetPropertyValue", 	Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::BpxReflectionOps_eventSetPropertyValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::BpxReflectionOps_eventSetPropertyValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execSetPropertyValue)
{
	P_GET_OBJECT(UObject,Z_Param_Root);
	P_GET_TARRAY_REF(FString,Z_Param_Out_Path);
	P_GET_PROPERTY(FStrProperty,Z_Param_ImportTextValue);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::SetPropertyValue(Z_Param_Root,Z_Param_Out_Path,Z_Param_ImportTextValue);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function SetPropertyValue ********************************

// ********** Begin Class UBpxReflectionOps Function SetUserDefinedStructMemberDefault *************
struct Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault_Statics
{
	struct BpxReflectionOps_eventSetUserDefinedStructMemberDefault_Parms
	{
		UUserDefinedStruct* Struct;
		FName FriendlyName;
		FString DefaultValueStr;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Set a member variable's default-value string on a `UUserDefinedStruct`.\n\x09 * Wraps `FStructureEditorUtils::ChangeVariableDefaultValue` after\n\x09 * resolving the friendly name \xe2\x86\x92 VarGuid.\n\x09 *\n\x09 * `DefaultValueStr` is the literal default value in the same string\n\x09 * format `FStructVariableDescription::DefaultValue` accepts \xe2\x80\x94 e.g.\n\x09 * `\"true\"` for bool, `\"42\"` for int, `\"(X=1.0,Y=2.0,Z=0.0)\"` for vectors,\n\x09 * `\"/Game/MyDT.MyDT\"` for soft object paths. Callers converting from\n\x09 * Python scalars should use the same ExportText normalization pattern\n\x09 * `data_assets._normalize_scalar_value` uses.\n\x09 *\n\x09 * Why not reuse `SetPropertyValue` on the struct's DefaultInstance:\n\x09 * `ChangeVariableDefaultValue` writes `VarDesc.DefaultValue` (the\n\x09 * authoritative string that regenerates `DefaultInstance` memory via\n\x09 * `RecreateDefaultInstanceInEditorData`); a direct write to\n\x09 * `DefaultInstance` via `SetPropertyValue` leaves `VarDesc.DefaultValue`\n\x09 * stale and the UDS in a torn state where the serialized string says X\n\x09 * but memory says Y. M28.4.0 research Open Question #1 selected this\n\x09 * path.\n\x09 *\n\x09 * Idempotent: compares existing `VarDesc.DefaultValue` against\n\x09 * `DefaultValueStr` up-front; match \xe2\x86\x92 `bSuccess=true, bSkipped=true`\n\x09 * without invoking the engine call (which would fire listener events\n\x09 * and churn the asset). Missing member name returns a structured\n\x09 * error \xe2\x80\x94 silent no-op on a plan-level typo would hide a real\n\x09 * authoring mistake.\n\x09 *\n\x09 * Caller is responsible for `CompileAndSavePackage(UDS)` after the set.\n\x09 *\n\x09 * Result shape:\n\x09 *   BeforeText: the pre-op default value string.\n\x09 *   AfterText:  the post-op default value string (== DefaultValueStr).\n\x09 *\n\x09 * Thread: game-thread only.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set a member variable's default-value string on a `UUserDefinedStruct`.\nWraps `FStructureEditorUtils::ChangeVariableDefaultValue` after\nresolving the friendly name \xe2\x86\x92 VarGuid.\n\n`DefaultValueStr` is the literal default value in the same string\nformat `FStructVariableDescription::DefaultValue` accepts \xe2\x80\x94 e.g.\n`\"true\"` for bool, `\"42\"` for int, `\"(X=1.0,Y=2.0,Z=0.0)\"` for vectors,\n`\"/Game/MyDT.MyDT\"` for soft object paths. Callers converting from\nPython scalars should use the same ExportText normalization pattern\n`data_assets._normalize_scalar_value` uses.\n\nWhy not reuse `SetPropertyValue` on the struct's DefaultInstance:\n`ChangeVariableDefaultValue` writes `VarDesc.DefaultValue` (the\nauthoritative string that regenerates `DefaultInstance` memory via\n`RecreateDefaultInstanceInEditorData`); a direct write to\n`DefaultInstance` via `SetPropertyValue` leaves `VarDesc.DefaultValue`\nstale and the UDS in a torn state where the serialized string says X\nbut memory says Y. M28.4.0 research Open Question #1 selected this\npath.\n\nIdempotent: compares existing `VarDesc.DefaultValue` against\n`DefaultValueStr` up-front; match \xe2\x86\x92 `bSuccess=true, bSkipped=true`\nwithout invoking the engine call (which would fire listener events\nand churn the asset). Missing member name returns a structured\nerror \xe2\x80\x94 silent no-op on a plan-level typo would hide a real\nauthoring mistake.\n\nCaller is responsible for `CompileAndSavePackage(UDS)` after the set.\n\nResult shape:\n  BeforeText: the pre-op default value string.\n  AfterText:  the post-op default value string (== DefaultValueStr).\n\nThread: game-thread only." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultValueStr_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetUserDefinedStructMemberDefault constinit property declarations *****
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Struct;
	static const UECodeGen_Private::FNamePropertyParams NewProp_FriendlyName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DefaultValueStr;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetUserDefinedStructMemberDefault constinit property declarations *******
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetUserDefinedStructMemberDefault Property Definitions ****************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault_Statics::NewProp_Struct = { "Struct", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetUserDefinedStructMemberDefault_Parms, Struct), Z_Construct_UClass_UUserDefinedStruct_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault_Statics::NewProp_FriendlyName = { "FriendlyName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetUserDefinedStructMemberDefault_Parms, FriendlyName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault_Statics::NewProp_DefaultValueStr = { "DefaultValueStr", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetUserDefinedStructMemberDefault_Parms, DefaultValueStr), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultValueStr_MetaData), NewProp_DefaultValueStr_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventSetUserDefinedStructMemberDefault_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault_Statics::NewProp_Struct,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault_Statics::NewProp_FriendlyName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault_Statics::NewProp_DefaultValueStr,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault_Statics::PropPointers) < 2048);
// ********** End Function SetUserDefinedStructMemberDefault Property Definitions ******************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "SetUserDefinedStructMemberDefault", 	Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault_Statics::BpxReflectionOps_eventSetUserDefinedStructMemberDefault_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault_Statics::BpxReflectionOps_eventSetUserDefinedStructMemberDefault_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execSetUserDefinedStructMemberDefault)
{
	P_GET_OBJECT(UUserDefinedStruct,Z_Param_Struct);
	P_GET_PROPERTY(FNameProperty,Z_Param_FriendlyName);
	P_GET_PROPERTY(FStrProperty,Z_Param_DefaultValueStr);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::SetUserDefinedStructMemberDefault(Z_Param_Struct,Z_Param_FriendlyName,Z_Param_DefaultValueStr);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function SetUserDefinedStructMemberDefault ***************

// ********** Begin Class UBpxReflectionOps Function WipeFunctionGraphBody *************************
struct Z_Construct_UFunction_UBpxReflectionOps_WipeFunctionGraphBody_Statics
{
	struct BpxReflectionOps_eventWipeFunctionGraphBody_Parms
	{
		UBlueprint* Blueprint;
		FName FunctionName;
		FBpxReflectionResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "BlueprintExporter|Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Remove every node from a function graph except UK2Node_FunctionEntry\n\x09 * and UK2Node_FunctionResult (plus their pin connections). Used by the\n\x09 * M26.1.1 `implement_interface_function(force_rebind=True)` path to\n\x09 * clear a pre-existing interface-override stub (or a prior authoring\n\x09 * pass) before re-running the binding logic on the same graph.\n\x09 *\n\x09 * Entry / Return nodes are preserved so the caller can keep referring\n\x09 * to them by their seeded GUIDs without having to re-create the graph.\n\x09 *\n\x09 * Idempotent: if the graph exists and already contains only Entry /\n\x09 * Return, returns bSuccess=true with bSkipped=true and a zero removal\n\x09 * count. Marks the blueprint structurally modified only when the graph\n\x09 * actually changed. Caller is responsible for CompileAndSavePackage.\n\x09 *\n\x09 * AfterText reports the removed-node count as a decimal string for\n\x09 * observability in op-result dicts.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Remove every node from a function graph except UK2Node_FunctionEntry\nand UK2Node_FunctionResult (plus their pin connections). Used by the\nM26.1.1 `implement_interface_function(force_rebind=True)` path to\nclear a pre-existing interface-override stub (or a prior authoring\npass) before re-running the binding logic on the same graph.\n\nEntry / Return nodes are preserved so the caller can keep referring\nto them by their seeded GUIDs without having to re-create the graph.\n\nIdempotent: if the graph exists and already contains only Entry /\nReturn, returns bSuccess=true with bSkipped=true and a zero removal\ncount. Marks the blueprint structurally modified only when the graph\nactually changed. Caller is responsible for CompileAndSavePackage.\n\nAfterText reports the removed-node count as a decimal string for\nobservability in op-result dicts." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function WipeFunctionGraphBody constinit property declarations *****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Blueprint;
	static const UECodeGen_Private::FNamePropertyParams NewProp_FunctionName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function WipeFunctionGraphBody constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function WipeFunctionGraphBody Property Definitions ****************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxReflectionOps_WipeFunctionGraphBody_Statics::NewProp_Blueprint = { "Blueprint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventWipeFunctionGraphBody_Parms, Blueprint), Z_Construct_UClass_UBlueprint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxReflectionOps_WipeFunctionGraphBody_Statics::NewProp_FunctionName = { "FunctionName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventWipeFunctionGraphBody_Parms, FunctionName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxReflectionOps_WipeFunctionGraphBody_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxReflectionOps_eventWipeFunctionGraphBody_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxReflectionResult, METADATA_PARAMS(0, nullptr) }; // 375724417
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxReflectionOps_WipeFunctionGraphBody_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_WipeFunctionGraphBody_Statics::NewProp_Blueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_WipeFunctionGraphBody_Statics::NewProp_FunctionName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxReflectionOps_WipeFunctionGraphBody_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_WipeFunctionGraphBody_Statics::PropPointers) < 2048);
// ********** End Function WipeFunctionGraphBody Property Definitions ******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxReflectionOps_WipeFunctionGraphBody_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxReflectionOps, nullptr, "WipeFunctionGraphBody", 	Z_Construct_UFunction_UBpxReflectionOps_WipeFunctionGraphBody_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_WipeFunctionGraphBody_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxReflectionOps_WipeFunctionGraphBody_Statics::BpxReflectionOps_eventWipeFunctionGraphBody_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxReflectionOps_WipeFunctionGraphBody_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxReflectionOps_WipeFunctionGraphBody_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxReflectionOps_WipeFunctionGraphBody_Statics::BpxReflectionOps_eventWipeFunctionGraphBody_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxReflectionOps_WipeFunctionGraphBody()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxReflectionOps_WipeFunctionGraphBody_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxReflectionOps::execWipeFunctionGraphBody)
{
	P_GET_OBJECT(UBlueprint,Z_Param_Blueprint);
	P_GET_PROPERTY(FNameProperty,Z_Param_FunctionName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxReflectionResult*)Z_Param__Result=UBpxReflectionOps::WipeFunctionGraphBody(Z_Param_Blueprint,Z_Param_FunctionName);
	P_NATIVE_END;
}
// ********** End Class UBpxReflectionOps Function WipeFunctionGraphBody ***************************

// ********** Begin Class UBpxReflectionOps ********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UBpxReflectionOps;
UClass* UBpxReflectionOps::GetPrivateStaticClass()
{
	using TClass = UBpxReflectionOps;
	if (!Z_Registration_Info_UClass_UBpxReflectionOps.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("BpxReflectionOps"),
			Z_Registration_Info_UClass_UBpxReflectionOps.InnerSingleton,
			StaticRegisterNativesUBpxReflectionOps,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UBpxReflectionOps.InnerSingleton;
}
UClass* Z_Construct_UClass_UBpxReflectionOps_NoRegister()
{
	return UBpxReflectionOps::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBpxReflectionOps_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Static UFUNCTION library exposing native FProperty walks to Python.\n *\n * Rationale: UE's Python binding generator enforces CPF_Protected and other\n * access flags at the Python layer, which blocks otherwise-legitimate\n * editor automation (StateTree.EditorData, Blueprint.ParentClass, etc.).\n * This library operates on FProperty / UObject directly in native C++ land\n * so those Python-specific flags don't apply, then surfaces each op as a\n * BlueprintCallable UFUNCTION that Python can invoke as\n * `unreal.BpxReflectionOps.get_property_value(...)`.\n *\n * Designed to be small and stable. Every write op returns an\n * `FBpxReflectionResult` with before / after / error data so Python callers\n * don't need to parse log output.\n */" },
#endif
		{ "IncludePath", "Reflection/ReflectionOps.h" },
		{ "ModuleRelativePath", "Public/Reflection/ReflectionOps.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Static UFUNCTION library exposing native FProperty walks to Python.\n\nRationale: UE's Python binding generator enforces CPF_Protected and other\naccess flags at the Python layer, which blocks otherwise-legitimate\neditor automation (StateTree.EditorData, Blueprint.ParentClass, etc.).\nThis library operates on FProperty / UObject directly in native C++ land\nso those Python-specific flags don't apply, then surfaces each op as a\nBlueprintCallable UFUNCTION that Python can invoke as\n`unreal.BpxReflectionOps.get_property_value(...)`.\n\nDesigned to be small and stable. Every write op returns an\n`FBpxReflectionResult` with before / after / error data so Python callers\ndon't need to parse log output." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UBpxReflectionOps constinit property declarations ************************
// ********** End Class UBpxReflectionOps constinit property declarations **************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("AddBranchNode"), .Pointer = &UBpxReflectionOps::execAddBranchNode },
		{ .NameUTF8 = UTF8TEXT("AddBreakStructNode"), .Pointer = &UBpxReflectionOps::execAddBreakStructNode },
		{ .NameUTF8 = UTF8TEXT("AddCallFunctionNode"), .Pointer = &UBpxReflectionOps::execAddCallFunctionNode },
		{ .NameUTF8 = UTF8TEXT("AddComponentToSCSDeterministic"), .Pointer = &UBpxReflectionOps::execAddComponentToSCSDeterministic },
		{ .NameUTF8 = UTF8TEXT("AddCustomEventNode"), .Pointer = &UBpxReflectionOps::execAddCustomEventNode },
		{ .NameUTF8 = UTF8TEXT("AddDynamicCastNode"), .Pointer = &UBpxReflectionOps::execAddDynamicCastNode },
		{ .NameUTF8 = UTF8TEXT("AddEnvQueryOption"), .Pointer = &UBpxReflectionOps::execAddEnvQueryOption },
		{ .NameUTF8 = UTF8TEXT("AddEnvQueryTest"), .Pointer = &UBpxReflectionOps::execAddEnvQueryTest },
		{ .NameUTF8 = UTF8TEXT("AddExecutionSequenceNode"), .Pointer = &UBpxReflectionOps::execAddExecutionSequenceNode },
		{ .NameUTF8 = UTF8TEXT("AddFunctionGraphDeterministic"), .Pointer = &UBpxReflectionOps::execAddFunctionGraphDeterministic },
		{ .NameUTF8 = UTF8TEXT("AddFunctionOverrideDeterministic"), .Pointer = &UBpxReflectionOps::execAddFunctionOverrideDeterministic },
		{ .NameUTF8 = UTF8TEXT("AddFunctionUserDefinedPin"), .Pointer = &UBpxReflectionOps::execAddFunctionUserDefinedPin },
		{ .NameUTF8 = UTF8TEXT("AddGameplayTag"), .Pointer = &UBpxReflectionOps::execAddGameplayTag },
		{ .NameUTF8 = UTF8TEXT("AddInterfaceByPath"), .Pointer = &UBpxReflectionOps::execAddInterfaceByPath },
		{ .NameUTF8 = UTF8TEXT("AddLocalVariableDeterministic"), .Pointer = &UBpxReflectionOps::execAddLocalVariableDeterministic },
		{ .NameUTF8 = UTF8TEXT("AddMacroInstanceNode"), .Pointer = &UBpxReflectionOps::execAddMacroInstanceNode },
		{ .NameUTF8 = UTF8TEXT("AddMakeStructNode"), .Pointer = &UBpxReflectionOps::execAddMakeStructNode },
		{ .NameUTF8 = UTF8TEXT("AddMemberVariableDeterministic"), .Pointer = &UBpxReflectionOps::execAddMemberVariableDeterministic },
		{ .NameUTF8 = UTF8TEXT("AddSelfMemberGetNode"), .Pointer = &UBpxReflectionOps::execAddSelfMemberGetNode },
		{ .NameUTF8 = UTF8TEXT("AddSetFieldsInStructNode"), .Pointer = &UBpxReflectionOps::execAddSetFieldsInStructNode },
		{ .NameUTF8 = UTF8TEXT("AddUserDefinedStructMember"), .Pointer = &UBpxReflectionOps::execAddUserDefinedStructMember },
		{ .NameUTF8 = UTF8TEXT("AddVariableGetNode"), .Pointer = &UBpxReflectionOps::execAddVariableGetNode },
		{ .NameUTF8 = UTF8TEXT("AddVariableSetNode"), .Pointer = &UBpxReflectionOps::execAddVariableSetNode },
		{ .NameUTF8 = UTF8TEXT("ArrayAppendNewElement"), .Pointer = &UBpxReflectionOps::execArrayAppendNewElement },
		{ .NameUTF8 = UTF8TEXT("ArrayRemoveAt"), .Pointer = &UBpxReflectionOps::execArrayRemoveAt },
		{ .NameUTF8 = UTF8TEXT("CompileAndSavePackage"), .Pointer = &UBpxReflectionOps::execCompileAndSavePackage },
		{ .NameUTF8 = UTF8TEXT("ConnectGraphPinsByGuidString"), .Pointer = &UBpxReflectionOps::execConnectGraphPinsByGuidString },
		{ .NameUTF8 = UTF8TEXT("ConnectPinsByName"), .Pointer = &UBpxReflectionOps::execConnectPinsByName },
		{ .NameUTF8 = UTF8TEXT("CreateBlueprintClassDeterministic"), .Pointer = &UBpxReflectionOps::execCreateBlueprintClassDeterministic },
		{ .NameUTF8 = UTF8TEXT("CreateCurveFloatDeterministic"), .Pointer = &UBpxReflectionOps::execCreateCurveFloatDeterministic },
		{ .NameUTF8 = UTF8TEXT("CreateDataAssetInstanceDeterministic"), .Pointer = &UBpxReflectionOps::execCreateDataAssetInstanceDeterministic },
		{ .NameUTF8 = UTF8TEXT("CreateUserDefinedStructDeterministic"), .Pointer = &UBpxReflectionOps::execCreateUserDefinedStructDeterministic },
		{ .NameUTF8 = UTF8TEXT("FindGraphEndpoints"), .Pointer = &UBpxReflectionOps::execFindGraphEndpoints },
		{ .NameUTF8 = UTF8TEXT("FindSubobject"), .Pointer = &UBpxReflectionOps::execFindSubobject },
		{ .NameUTF8 = UTF8TEXT("GetArrayLength"), .Pointer = &UBpxReflectionOps::execGetArrayLength },
		{ .NameUTF8 = UTF8TEXT("GetObjectPropertyValue"), .Pointer = &UBpxReflectionOps::execGetObjectPropertyValue },
		{ .NameUTF8 = UTF8TEXT("GetPropertyValue"), .Pointer = &UBpxReflectionOps::execGetPropertyValue },
		{ .NameUTF8 = UTF8TEXT("NewSubobject"), .Pointer = &UBpxReflectionOps::execNewSubobject },
		{ .NameUTF8 = UTF8TEXT("OverrideInterfaceFunction"), .Pointer = &UBpxReflectionOps::execOverrideInterfaceFunction },
		{ .NameUTF8 = UTF8TEXT("RemoveEnvQueryTest"), .Pointer = &UBpxReflectionOps::execRemoveEnvQueryTest },
		{ .NameUTF8 = UTF8TEXT("RemoveUserDefinedStructMember"), .Pointer = &UBpxReflectionOps::execRemoveUserDefinedStructMember },
		{ .NameUTF8 = UTF8TEXT("SetCurveFloatKeys"), .Pointer = &UBpxReflectionOps::execSetCurveFloatKeys },
		{ .NameUTF8 = UTF8TEXT("SetGraphPinLiteralDefault"), .Pointer = &UBpxReflectionOps::execSetGraphPinLiteralDefault },
		{ .NameUTF8 = UTF8TEXT("SetInstancedStructType"), .Pointer = &UBpxReflectionOps::execSetInstancedStructType },
		{ .NameUTF8 = UTF8TEXT("SetNodePinLiteralDefault"), .Pointer = &UBpxReflectionOps::execSetNodePinLiteralDefault },
		{ .NameUTF8 = UTF8TEXT("SetObjectPropertyValue"), .Pointer = &UBpxReflectionOps::execSetObjectPropertyValue },
		{ .NameUTF8 = UTF8TEXT("SetPropertyValue"), .Pointer = &UBpxReflectionOps::execSetPropertyValue },
		{ .NameUTF8 = UTF8TEXT("SetUserDefinedStructMemberDefault"), .Pointer = &UBpxReflectionOps::execSetUserDefinedStructMemberDefault },
		{ .NameUTF8 = UTF8TEXT("WipeFunctionGraphBody"), .Pointer = &UBpxReflectionOps::execWipeFunctionGraphBody },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddBranchNode, "AddBranchNode" }, // 3907492114
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddBreakStructNode, "AddBreakStructNode" }, // 300704806
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddCallFunctionNode, "AddCallFunctionNode" }, // 2644009142
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddComponentToSCSDeterministic, "AddComponentToSCSDeterministic" }, // 1726171117
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddCustomEventNode, "AddCustomEventNode" }, // 954529270
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddDynamicCastNode, "AddDynamicCastNode" }, // 1360895649
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryOption, "AddEnvQueryOption" }, // 3541674077
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddEnvQueryTest, "AddEnvQueryTest" }, // 2666964188
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddExecutionSequenceNode, "AddExecutionSequenceNode" }, // 1208853056
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddFunctionGraphDeterministic, "AddFunctionGraphDeterministic" }, // 1866504756
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddFunctionOverrideDeterministic, "AddFunctionOverrideDeterministic" }, // 1374501838
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddFunctionUserDefinedPin, "AddFunctionUserDefinedPin" }, // 2174582585
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddGameplayTag, "AddGameplayTag" }, // 2490897308
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddInterfaceByPath, "AddInterfaceByPath" }, // 2200552595
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddLocalVariableDeterministic, "AddLocalVariableDeterministic" }, // 1387833527
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddMacroInstanceNode, "AddMacroInstanceNode" }, // 3448776372
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddMakeStructNode, "AddMakeStructNode" }, // 2211877178
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddMemberVariableDeterministic, "AddMemberVariableDeterministic" }, // 2846574344
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddSelfMemberGetNode, "AddSelfMemberGetNode" }, // 408759128
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddSetFieldsInStructNode, "AddSetFieldsInStructNode" }, // 100506544
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddUserDefinedStructMember, "AddUserDefinedStructMember" }, // 2768968181
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddVariableGetNode, "AddVariableGetNode" }, // 494314577
		{ &Z_Construct_UFunction_UBpxReflectionOps_AddVariableSetNode, "AddVariableSetNode" }, // 994074832
		{ &Z_Construct_UFunction_UBpxReflectionOps_ArrayAppendNewElement, "ArrayAppendNewElement" }, // 3379394120
		{ &Z_Construct_UFunction_UBpxReflectionOps_ArrayRemoveAt, "ArrayRemoveAt" }, // 3631612645
		{ &Z_Construct_UFunction_UBpxReflectionOps_CompileAndSavePackage, "CompileAndSavePackage" }, // 1002986512
		{ &Z_Construct_UFunction_UBpxReflectionOps_ConnectGraphPinsByGuidString, "ConnectGraphPinsByGuidString" }, // 3793061055
		{ &Z_Construct_UFunction_UBpxReflectionOps_ConnectPinsByName, "ConnectPinsByName" }, // 4206576806
		{ &Z_Construct_UFunction_UBpxReflectionOps_CreateBlueprintClassDeterministic, "CreateBlueprintClassDeterministic" }, // 252503351
		{ &Z_Construct_UFunction_UBpxReflectionOps_CreateCurveFloatDeterministic, "CreateCurveFloatDeterministic" }, // 361147588
		{ &Z_Construct_UFunction_UBpxReflectionOps_CreateDataAssetInstanceDeterministic, "CreateDataAssetInstanceDeterministic" }, // 4175624701
		{ &Z_Construct_UFunction_UBpxReflectionOps_CreateUserDefinedStructDeterministic, "CreateUserDefinedStructDeterministic" }, // 2142136892
		{ &Z_Construct_UFunction_UBpxReflectionOps_FindGraphEndpoints, "FindGraphEndpoints" }, // 2239118062
		{ &Z_Construct_UFunction_UBpxReflectionOps_FindSubobject, "FindSubobject" }, // 3483047926
		{ &Z_Construct_UFunction_UBpxReflectionOps_GetArrayLength, "GetArrayLength" }, // 3870456597
		{ &Z_Construct_UFunction_UBpxReflectionOps_GetObjectPropertyValue, "GetObjectPropertyValue" }, // 3145673875
		{ &Z_Construct_UFunction_UBpxReflectionOps_GetPropertyValue, "GetPropertyValue" }, // 470349833
		{ &Z_Construct_UFunction_UBpxReflectionOps_NewSubobject, "NewSubobject" }, // 1543697121
		{ &Z_Construct_UFunction_UBpxReflectionOps_OverrideInterfaceFunction, "OverrideInterfaceFunction" }, // 3127481884
		{ &Z_Construct_UFunction_UBpxReflectionOps_RemoveEnvQueryTest, "RemoveEnvQueryTest" }, // 751422648
		{ &Z_Construct_UFunction_UBpxReflectionOps_RemoveUserDefinedStructMember, "RemoveUserDefinedStructMember" }, // 4075763487
		{ &Z_Construct_UFunction_UBpxReflectionOps_SetCurveFloatKeys, "SetCurveFloatKeys" }, // 2447870277
		{ &Z_Construct_UFunction_UBpxReflectionOps_SetGraphPinLiteralDefault, "SetGraphPinLiteralDefault" }, // 673516415
		{ &Z_Construct_UFunction_UBpxReflectionOps_SetInstancedStructType, "SetInstancedStructType" }, // 3918731655
		{ &Z_Construct_UFunction_UBpxReflectionOps_SetNodePinLiteralDefault, "SetNodePinLiteralDefault" }, // 3968966843
		{ &Z_Construct_UFunction_UBpxReflectionOps_SetObjectPropertyValue, "SetObjectPropertyValue" }, // 3930920261
		{ &Z_Construct_UFunction_UBpxReflectionOps_SetPropertyValue, "SetPropertyValue" }, // 3438553069
		{ &Z_Construct_UFunction_UBpxReflectionOps_SetUserDefinedStructMemberDefault, "SetUserDefinedStructMemberDefault" }, // 1693934044
		{ &Z_Construct_UFunction_UBpxReflectionOps_WipeFunctionGraphBody, "WipeFunctionGraphBody" }, // 3869863295
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBpxReflectionOps>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UBpxReflectionOps_Statics
UObject* (*const Z_Construct_UClass_UBpxReflectionOps_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBpxReflectionOps_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBpxReflectionOps_Statics::ClassParams = {
	&UBpxReflectionOps::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBpxReflectionOps_Statics::Class_MetaDataParams), Z_Construct_UClass_UBpxReflectionOps_Statics::Class_MetaDataParams)
};
void UBpxReflectionOps::StaticRegisterNativesUBpxReflectionOps()
{
	UClass* Class = UBpxReflectionOps::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UBpxReflectionOps_Statics::Funcs));
}
UClass* Z_Construct_UClass_UBpxReflectionOps()
{
	if (!Z_Registration_Info_UClass_UBpxReflectionOps.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBpxReflectionOps.OuterSingleton, Z_Construct_UClass_UBpxReflectionOps_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBpxReflectionOps.OuterSingleton;
}
UBpxReflectionOps::UBpxReflectionOps(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UBpxReflectionOps);
UBpxReflectionOps::~UBpxReflectionOps() {}
// ********** End Class UBpxReflectionOps **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Reflection_ReflectionOps_h__Script_BlueprintExporter_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBpxReflectionOps, UBpxReflectionOps::StaticClass, TEXT("UBpxReflectionOps"), &Z_Registration_Info_UClass_UBpxReflectionOps, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBpxReflectionOps), 4018586453U) },
	};
}; // Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Reflection_ReflectionOps_h__Script_BlueprintExporter_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Reflection_ReflectionOps_h__Script_BlueprintExporter_2989614083{
	TEXT("/Script/BlueprintExporter"),
	Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Reflection_ReflectionOps_h__Script_BlueprintExporter_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Reflection_ReflectionOps_h__Script_BlueprintExporter_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
