// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Reflection/ReflectionTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeReflectionTypes() {}

// ********** Begin Cross Module References ********************************************************
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FBpxGraphEndpoints();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FBpxNodeResult();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FBpxReflectionResult();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid();
UPackage* Z_Construct_UPackage__Script_BlueprintExporter();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FBpxReflectionResult **********************************************
struct Z_Construct_UScriptStruct_FBpxReflectionResult_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FBpxReflectionResult); }
	static inline consteval int16 GetStructAlignment() { return alignof(FBpxReflectionResult); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Result of a reflection-bridge op. Returned by UBpxReflectionOps methods\n * so Python callers get uniform before / after / error data without needing\n * to parse log output.\n */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Result of a reflection-bridge op. Returned by UBpxReflectionOps methods\nso Python callers get uniform before / after / error data without needing\nto parse log output." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSuccess_MetaData[] = {
		{ "Category", "Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** True iff the op completed successfully. */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "True iff the op completed successfully." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ErrorMessage_MetaData[] = {
		{ "Category", "Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Human-readable error message. Empty on success. */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Human-readable error message. Empty on success." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BeforeText_MetaData[] = {
		{ "Category", "Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** ExportText of the property value before the op. Empty for pure-read ops. */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "ExportText of the property value before the op. Empty for pure-read ops." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AfterText_MetaData[] = {
		{ "Category", "Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** ExportText of the property value after the op. Populated on success. */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "ExportText of the property value after the op. Populated on success." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSkipped_MetaData[] = {
		{ "Category", "Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** True when the op was a no-op because BeforeText already matched the target. */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "True when the op was a no-op because BeforeText already matched the target." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FBpxReflectionResult constinit property declarations **************
	static void NewProp_bSuccess_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSuccess;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ErrorMessage;
	static const UECodeGen_Private::FStrPropertyParams NewProp_BeforeText;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AfterText;
	static void NewProp_bSkipped_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSkipped;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FBpxReflectionResult constinit property declarations ****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBpxReflectionResult>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FBpxReflectionResult_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBpxReflectionResult;
class UScriptStruct* FBpxReflectionResult::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBpxReflectionResult.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBpxReflectionResult.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBpxReflectionResult, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("BpxReflectionResult"));
	}
	return Z_Registration_Info_UScriptStruct_FBpxReflectionResult.OuterSingleton;
	}

// ********** Begin ScriptStruct FBpxReflectionResult Property Definitions *************************
void Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::NewProp_bSuccess_SetBit(void* Obj)
{
	((FBpxReflectionResult*)Obj)->bSuccess = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::NewProp_bSuccess = { "bSuccess", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FBpxReflectionResult), &Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::NewProp_bSuccess_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSuccess_MetaData), NewProp_bSuccess_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::NewProp_ErrorMessage = { "ErrorMessage", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBpxReflectionResult, ErrorMessage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ErrorMessage_MetaData), NewProp_ErrorMessage_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::NewProp_BeforeText = { "BeforeText", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBpxReflectionResult, BeforeText), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BeforeText_MetaData), NewProp_BeforeText_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::NewProp_AfterText = { "AfterText", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBpxReflectionResult, AfterText), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AfterText_MetaData), NewProp_AfterText_MetaData) };
void Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::NewProp_bSkipped_SetBit(void* Obj)
{
	((FBpxReflectionResult*)Obj)->bSkipped = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::NewProp_bSkipped = { "bSkipped", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FBpxReflectionResult), &Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::NewProp_bSkipped_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSkipped_MetaData), NewProp_bSkipped_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::NewProp_bSuccess,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::NewProp_ErrorMessage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::NewProp_BeforeText,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::NewProp_AfterText,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::NewProp_bSkipped,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FBpxReflectionResult Property Definitions ***************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"BpxReflectionResult",
	Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::PropPointers),
	sizeof(FBpxReflectionResult),
	alignof(FBpxReflectionResult),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBpxReflectionResult()
{
	if (!Z_Registration_Info_UScriptStruct_FBpxReflectionResult.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBpxReflectionResult.InnerSingleton, Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FBpxReflectionResult.InnerSingleton);
}
// ********** End ScriptStruct FBpxReflectionResult ************************************************

// ********** Begin ScriptStruct FBpxGraphEndpoints ************************************************
struct Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FBpxGraphEndpoints); }
	static inline consteval int16 GetStructAlignment() { return alignof(FBpxGraphEndpoints); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Entry / Return node GUIDs for a Blueprint function graph. M26.1 \xe2\x80\x94 callers\n * use these to reference Entry and Return by stable GUID in subsequent ops\n * (AddSelfMemberGetNode targets the graph by function name; pins are wired\n * by referencing these GUIDs).\n *\n * GUIDs are deterministic: OverrideInterfaceFunction seeds Entry / Return\n * NodeGuids from md5(bp_path + \":\" + function_name + \":entry|return\"),\n * overriding UE's internal `FGuid::NewGuid()` so the golden post-op BugHunt\n * fixture stays byte-identical across re-generation.\n */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Entry / Return node GUIDs for a Blueprint function graph. M26.1 \xe2\x80\x94 callers\nuse these to reference Entry and Return by stable GUID in subsequent ops\n(AddSelfMemberGetNode targets the graph by function name; pins are wired\nby referencing these GUIDs).\n\nGUIDs are deterministic: OverrideInterfaceFunction seeds Entry / Return\nNodeGuids from md5(bp_path + \":\" + function_name + \":entry|return\"),\noverriding UE's internal `FGuid::NewGuid()` so the golden post-op BugHunt\nfixture stays byte-identical across re-generation." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSuccess_MetaData[] = {
		{ "Category", "Reflection" },
		{ "ModuleRelativePath", "Public/Reflection/ReflectionTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ErrorMessage_MetaData[] = {
		{ "Category", "Reflection" },
		{ "ModuleRelativePath", "Public/Reflection/ReflectionTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EntryGuid_MetaData[] = {
		{ "Category", "Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** GUID of the UK2Node_FunctionEntry node in the target function graph. Zero on error. */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "GUID of the UK2Node_FunctionEntry node in the target function graph. Zero on error." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnGuid_MetaData[] = {
		{ "Category", "Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** GUID of the UK2Node_FunctionResult node in the target function graph.\n\x09 *  Zero if the function has no return (void / latent FUNC_Event signatures). */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "GUID of the UK2Node_FunctionResult node in the target function graph.\nZero if the function has no return (void / latent FUNC_Event signatures)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSkipped_MetaData[] = {
		{ "Category", "Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** True when the op was a no-op because an equivalent function graph\n\x09 *  already existed (M28.2.2 AddFunctionGraphDeterministic idempotent skip). */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "True when the op was a no-op because an equivalent function graph\nalready existed (M28.2.2 AddFunctionGraphDeterministic idempotent skip)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FBpxGraphEndpoints constinit property declarations ****************
	static void NewProp_bSuccess_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSuccess;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ErrorMessage;
	static const UECodeGen_Private::FStructPropertyParams NewProp_EntryGuid;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnGuid;
	static void NewProp_bSkipped_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSkipped;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FBpxGraphEndpoints constinit property declarations ******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBpxGraphEndpoints>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBpxGraphEndpoints;
class UScriptStruct* FBpxGraphEndpoints::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBpxGraphEndpoints.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBpxGraphEndpoints.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBpxGraphEndpoints, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("BpxGraphEndpoints"));
	}
	return Z_Registration_Info_UScriptStruct_FBpxGraphEndpoints.OuterSingleton;
	}

// ********** Begin ScriptStruct FBpxGraphEndpoints Property Definitions ***************************
void Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::NewProp_bSuccess_SetBit(void* Obj)
{
	((FBpxGraphEndpoints*)Obj)->bSuccess = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::NewProp_bSuccess = { "bSuccess", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FBpxGraphEndpoints), &Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::NewProp_bSuccess_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSuccess_MetaData), NewProp_bSuccess_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::NewProp_ErrorMessage = { "ErrorMessage", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBpxGraphEndpoints, ErrorMessage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ErrorMessage_MetaData), NewProp_ErrorMessage_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::NewProp_EntryGuid = { "EntryGuid", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBpxGraphEndpoints, EntryGuid), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EntryGuid_MetaData), NewProp_EntryGuid_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::NewProp_ReturnGuid = { "ReturnGuid", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBpxGraphEndpoints, ReturnGuid), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnGuid_MetaData), NewProp_ReturnGuid_MetaData) };
void Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::NewProp_bSkipped_SetBit(void* Obj)
{
	((FBpxGraphEndpoints*)Obj)->bSkipped = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::NewProp_bSkipped = { "bSkipped", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FBpxGraphEndpoints), &Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::NewProp_bSkipped_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSkipped_MetaData), NewProp_bSkipped_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::NewProp_bSuccess,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::NewProp_ErrorMessage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::NewProp_EntryGuid,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::NewProp_ReturnGuid,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::NewProp_bSkipped,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FBpxGraphEndpoints Property Definitions *****************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"BpxGraphEndpoints",
	Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::PropPointers),
	sizeof(FBpxGraphEndpoints),
	alignof(FBpxGraphEndpoints),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBpxGraphEndpoints()
{
	if (!Z_Registration_Info_UScriptStruct_FBpxGraphEndpoints.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBpxGraphEndpoints.InnerSingleton, Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FBpxGraphEndpoints.InnerSingleton);
}
// ********** End ScriptStruct FBpxGraphEndpoints **************************************************

// ********** Begin ScriptStruct FBpxNodeResult ****************************************************
struct Z_Construct_UScriptStruct_FBpxNodeResult_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FBpxNodeResult); }
	static inline consteval int16 GetStructAlignment() { return alignof(FBpxNodeResult); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Result of a node-creation op. M26.1 \xe2\x80\x94 AddSelfMemberGetNode (and future node-\n * creation ops) return the newly-created node's GUID so callers can chain\n * subsequent ConnectPinsByName / SetNodePinLiteralDefault calls by GUID\n * rather than by walking the graph.\n */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Result of a node-creation op. M26.1 \xe2\x80\x94 AddSelfMemberGetNode (and future node-\ncreation ops) return the newly-created node's GUID so callers can chain\nsubsequent ConnectPinsByName / SetNodePinLiteralDefault calls by GUID\nrather than by walking the graph." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSuccess_MetaData[] = {
		{ "Category", "Reflection" },
		{ "ModuleRelativePath", "Public/Reflection/ReflectionTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ErrorMessage_MetaData[] = {
		{ "Category", "Reflection" },
		{ "ModuleRelativePath", "Public/Reflection/ReflectionTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NodeGuid_MetaData[] = {
		{ "Category", "Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Deterministic GUID of the newly-created (or re-found, on idempotent skip) node. */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Deterministic GUID of the newly-created (or re-found, on idempotent skip) node." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSkipped_MetaData[] = {
		{ "Category", "Reflection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** True when the op was a no-op because an equivalent node already existed. */" },
#endif
		{ "ModuleRelativePath", "Public/Reflection/ReflectionTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "True when the op was a no-op because an equivalent node already existed." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FBpxNodeResult constinit property declarations ********************
	static void NewProp_bSuccess_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSuccess;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ErrorMessage;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NodeGuid;
	static void NewProp_bSkipped_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSkipped;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FBpxNodeResult constinit property declarations **********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBpxNodeResult>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FBpxNodeResult_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBpxNodeResult;
class UScriptStruct* FBpxNodeResult::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBpxNodeResult.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBpxNodeResult.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBpxNodeResult, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("BpxNodeResult"));
	}
	return Z_Registration_Info_UScriptStruct_FBpxNodeResult.OuterSingleton;
	}

// ********** Begin ScriptStruct FBpxNodeResult Property Definitions *******************************
void Z_Construct_UScriptStruct_FBpxNodeResult_Statics::NewProp_bSuccess_SetBit(void* Obj)
{
	((FBpxNodeResult*)Obj)->bSuccess = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FBpxNodeResult_Statics::NewProp_bSuccess = { "bSuccess", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FBpxNodeResult), &Z_Construct_UScriptStruct_FBpxNodeResult_Statics::NewProp_bSuccess_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSuccess_MetaData), NewProp_bSuccess_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBpxNodeResult_Statics::NewProp_ErrorMessage = { "ErrorMessage", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBpxNodeResult, ErrorMessage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ErrorMessage_MetaData), NewProp_ErrorMessage_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FBpxNodeResult_Statics::NewProp_NodeGuid = { "NodeGuid", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBpxNodeResult, NodeGuid), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NodeGuid_MetaData), NewProp_NodeGuid_MetaData) };
void Z_Construct_UScriptStruct_FBpxNodeResult_Statics::NewProp_bSkipped_SetBit(void* Obj)
{
	((FBpxNodeResult*)Obj)->bSkipped = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FBpxNodeResult_Statics::NewProp_bSkipped = { "bSkipped", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FBpxNodeResult), &Z_Construct_UScriptStruct_FBpxNodeResult_Statics::NewProp_bSkipped_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSkipped_MetaData), NewProp_bSkipped_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBpxNodeResult_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBpxNodeResult_Statics::NewProp_bSuccess,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBpxNodeResult_Statics::NewProp_ErrorMessage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBpxNodeResult_Statics::NewProp_NodeGuid,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBpxNodeResult_Statics::NewProp_bSkipped,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBpxNodeResult_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FBpxNodeResult Property Definitions *********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBpxNodeResult_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"BpxNodeResult",
	Z_Construct_UScriptStruct_FBpxNodeResult_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBpxNodeResult_Statics::PropPointers),
	sizeof(FBpxNodeResult),
	alignof(FBpxNodeResult),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBpxNodeResult_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBpxNodeResult_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBpxNodeResult()
{
	if (!Z_Registration_Info_UScriptStruct_FBpxNodeResult.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBpxNodeResult.InnerSingleton, Z_Construct_UScriptStruct_FBpxNodeResult_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FBpxNodeResult.InnerSingleton);
}
// ********** End ScriptStruct FBpxNodeResult ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Reflection_ReflectionTypes_h__Script_BlueprintExporter_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FBpxReflectionResult::StaticStruct, Z_Construct_UScriptStruct_FBpxReflectionResult_Statics::NewStructOps, TEXT("BpxReflectionResult"),&Z_Registration_Info_UScriptStruct_FBpxReflectionResult, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBpxReflectionResult), 375724417U) },
		{ FBpxGraphEndpoints::StaticStruct, Z_Construct_UScriptStruct_FBpxGraphEndpoints_Statics::NewStructOps, TEXT("BpxGraphEndpoints"),&Z_Registration_Info_UScriptStruct_FBpxGraphEndpoints, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBpxGraphEndpoints), 39012202U) },
		{ FBpxNodeResult::StaticStruct, Z_Construct_UScriptStruct_FBpxNodeResult_Statics::NewStructOps, TEXT("BpxNodeResult"),&Z_Registration_Info_UScriptStruct_FBpxNodeResult, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBpxNodeResult), 685492501U) },
	};
}; // Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Reflection_ReflectionTypes_h__Script_BlueprintExporter_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Reflection_ReflectionTypes_h__Script_BlueprintExporter_281850060{
	TEXT("/Script/BlueprintExporter"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Reflection_ReflectionTypes_h__Script_BlueprintExporter_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Reflection_ReflectionTypes_h__Script_BlueprintExporter_Statics::ScriptStructInfo),
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
