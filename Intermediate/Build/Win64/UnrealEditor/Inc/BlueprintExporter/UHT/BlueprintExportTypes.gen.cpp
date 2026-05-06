// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Schema/BlueprintExportTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeBlueprintExportTypes() {}

// ********** Begin Cross Module References ********************************************************
BLUEPRINTEXPORTER_API UEnum* Z_Construct_UEnum_BlueprintExporter_EBlueprintDiffChangeType();
BLUEPRINTEXPORTER_API UEnum* Z_Construct_UEnum_BlueprintExporter_EBlueprintExportType();
BLUEPRINTEXPORTER_API UEnum* Z_Construct_UEnum_BlueprintExporter_EExportDependencyType();
BLUEPRINTEXPORTER_API UEnum* Z_Construct_UEnum_BlueprintExporter_EExportPinDirection();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FBlueprintDiffChange();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FBlueprintDiffResult();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FBlueprintExportConfig();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FBlueprintExportMetrics();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedAnimState();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedAnimTransition();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedBlueprint();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedComponent();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedComponentProperty();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedDependency();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedFunction();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedFunctionFlags();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedFunctionParam();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedGraph();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedNode();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedParentClass();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedPin();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedPinConnection();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedPinType();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedStateMachine();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedTransitionBlendSettings();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedVariable();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedVariableFlags();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportedWidgetNode();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportInfo();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportManifest();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FExportManifestEntry();
UPackage* Z_Construct_UPackage__Script_BlueprintExporter();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EBlueprintExportType ******************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EBlueprintExportType;
static UEnum* EBlueprintExportType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EBlueprintExportType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EBlueprintExportType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_BlueprintExporter_EBlueprintExportType, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("EBlueprintExportType"));
	}
	return Z_Registration_Info_UEnum_EBlueprintExportType.OuterSingleton;
}
template<> BLUEPRINTEXPORTER_NON_ATTRIBUTED_API UEnum* StaticEnum<EBlueprintExportType>()
{
	return EBlueprintExportType_StaticEnum();
}
struct Z_Construct_UEnum_BlueprintExporter_EBlueprintExportType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Blueprint type enumeration\n */" },
#endif
		{ "Const.Name", "EBlueprintExportType::Const" },
		{ "FunctionLibrary.Name", "EBlueprintExportType::FunctionLibrary" },
		{ "Interface.Name", "EBlueprintExportType::Interface" },
		{ "LevelScript.Name", "EBlueprintExportType::LevelScript" },
		{ "MacroLibrary.Name", "EBlueprintExportType::MacroLibrary" },
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
		{ "Normal.Name", "EBlueprintExportType::Normal" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint type enumeration" },
#endif
		{ "Unknown.Name", "EBlueprintExportType::Unknown" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EBlueprintExportType::Normal", (int64)EBlueprintExportType::Normal },
		{ "EBlueprintExportType::Const", (int64)EBlueprintExportType::Const },
		{ "EBlueprintExportType::MacroLibrary", (int64)EBlueprintExportType::MacroLibrary },
		{ "EBlueprintExportType::Interface", (int64)EBlueprintExportType::Interface },
		{ "EBlueprintExportType::LevelScript", (int64)EBlueprintExportType::LevelScript },
		{ "EBlueprintExportType::FunctionLibrary", (int64)EBlueprintExportType::FunctionLibrary },
		{ "EBlueprintExportType::Unknown", (int64)EBlueprintExportType::Unknown },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_BlueprintExporter_EBlueprintExportType_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_BlueprintExporter_EBlueprintExportType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	"EBlueprintExportType",
	"EBlueprintExportType",
	Z_Construct_UEnum_BlueprintExporter_EBlueprintExportType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_BlueprintExporter_EBlueprintExportType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_BlueprintExporter_EBlueprintExportType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_BlueprintExporter_EBlueprintExportType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_BlueprintExporter_EBlueprintExportType()
{
	if (!Z_Registration_Info_UEnum_EBlueprintExportType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EBlueprintExportType.InnerSingleton, Z_Construct_UEnum_BlueprintExporter_EBlueprintExportType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EBlueprintExportType.InnerSingleton;
}
// ********** End Enum EBlueprintExportType ********************************************************

// ********** Begin Enum EExportPinDirection *******************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EExportPinDirection;
static UEnum* EExportPinDirection_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EExportPinDirection.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EExportPinDirection.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_BlueprintExporter_EExportPinDirection, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("EExportPinDirection"));
	}
	return Z_Registration_Info_UEnum_EExportPinDirection.OuterSingleton;
}
template<> BLUEPRINTEXPORTER_NON_ATTRIBUTED_API UEnum* StaticEnum<EExportPinDirection>()
{
	return EExportPinDirection_StaticEnum();
}
struct Z_Construct_UEnum_BlueprintExporter_EExportPinDirection_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Pin direction\n */" },
#endif
		{ "Input.Name", "EExportPinDirection::Input" },
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
		{ "Output.Name", "EExportPinDirection::Output" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pin direction" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EExportPinDirection::Input", (int64)EExportPinDirection::Input },
		{ "EExportPinDirection::Output", (int64)EExportPinDirection::Output },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_BlueprintExporter_EExportPinDirection_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_BlueprintExporter_EExportPinDirection_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	"EExportPinDirection",
	"EExportPinDirection",
	Z_Construct_UEnum_BlueprintExporter_EExportPinDirection_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_BlueprintExporter_EExportPinDirection_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_BlueprintExporter_EExportPinDirection_Statics::Enum_MetaDataParams), Z_Construct_UEnum_BlueprintExporter_EExportPinDirection_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_BlueprintExporter_EExportPinDirection()
{
	if (!Z_Registration_Info_UEnum_EExportPinDirection.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EExportPinDirection.InnerSingleton, Z_Construct_UEnum_BlueprintExporter_EExportPinDirection_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EExportPinDirection.InnerSingleton;
}
// ********** End Enum EExportPinDirection *********************************************************

// ********** Begin Enum EExportDependencyType *****************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EExportDependencyType;
static UEnum* EExportDependencyType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EExportDependencyType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EExportDependencyType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_BlueprintExporter_EExportDependencyType, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("EExportDependencyType"));
	}
	return Z_Registration_Info_UEnum_EExportDependencyType.OuterSingleton;
}
template<> BLUEPRINTEXPORTER_NON_ATTRIBUTED_API UEnum* StaticEnum<EExportDependencyType>()
{
	return EExportDependencyType_StaticEnum();
}
struct Z_Construct_UEnum_BlueprintExporter_EExportDependencyType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Dependency type\n */" },
#endif
		{ "Hard.Name", "EExportDependencyType::Hard" },
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
		{ "Soft.Name", "EExportDependencyType::Soft" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Dependency type" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EExportDependencyType::Hard", (int64)EExportDependencyType::Hard },
		{ "EExportDependencyType::Soft", (int64)EExportDependencyType::Soft },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_BlueprintExporter_EExportDependencyType_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_BlueprintExporter_EExportDependencyType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	"EExportDependencyType",
	"EExportDependencyType",
	Z_Construct_UEnum_BlueprintExporter_EExportDependencyType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_BlueprintExporter_EExportDependencyType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_BlueprintExporter_EExportDependencyType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_BlueprintExporter_EExportDependencyType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_BlueprintExporter_EExportDependencyType()
{
	if (!Z_Registration_Info_UEnum_EExportDependencyType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EExportDependencyType.InnerSingleton, Z_Construct_UEnum_BlueprintExporter_EExportDependencyType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EExportDependencyType.InnerSingleton;
}
// ********** End Enum EExportDependencyType *******************************************************

// ********** Begin Enum EBlueprintDiffChangeType **************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EBlueprintDiffChangeType;
static UEnum* EBlueprintDiffChangeType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EBlueprintDiffChangeType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EBlueprintDiffChangeType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_BlueprintExporter_EBlueprintDiffChangeType, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("EBlueprintDiffChangeType"));
	}
	return Z_Registration_Info_UEnum_EBlueprintDiffChangeType.OuterSingleton;
}
template<> BLUEPRINTEXPORTER_NON_ATTRIBUTED_API UEnum* StaticEnum<EBlueprintDiffChangeType>()
{
	return EBlueprintDiffChangeType_StaticEnum();
}
struct Z_Construct_UEnum_BlueprintExporter_EBlueprintDiffChangeType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Added.Name", "EBlueprintDiffChangeType::Added" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Diff change type\n */" },
#endif
		{ "ConnectionChanged.Name", "EBlueprintDiffChangeType::ConnectionChanged" },
		{ "Modified.Name", "EBlueprintDiffChangeType::Modified" },
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
		{ "Moved.Name", "EBlueprintDiffChangeType::Moved" },
		{ "Removed.Name", "EBlueprintDiffChangeType::Removed" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Diff change type" },
#endif
		{ "TypeChanged.Name", "EBlueprintDiffChangeType::TypeChanged" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EBlueprintDiffChangeType::Added", (int64)EBlueprintDiffChangeType::Added },
		{ "EBlueprintDiffChangeType::Removed", (int64)EBlueprintDiffChangeType::Removed },
		{ "EBlueprintDiffChangeType::Modified", (int64)EBlueprintDiffChangeType::Modified },
		{ "EBlueprintDiffChangeType::Moved", (int64)EBlueprintDiffChangeType::Moved },
		{ "EBlueprintDiffChangeType::TypeChanged", (int64)EBlueprintDiffChangeType::TypeChanged },
		{ "EBlueprintDiffChangeType::ConnectionChanged", (int64)EBlueprintDiffChangeType::ConnectionChanged },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_BlueprintExporter_EBlueprintDiffChangeType_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_BlueprintExporter_EBlueprintDiffChangeType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	"EBlueprintDiffChangeType",
	"EBlueprintDiffChangeType",
	Z_Construct_UEnum_BlueprintExporter_EBlueprintDiffChangeType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_BlueprintExporter_EBlueprintDiffChangeType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_BlueprintExporter_EBlueprintDiffChangeType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_BlueprintExporter_EBlueprintDiffChangeType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_BlueprintExporter_EBlueprintDiffChangeType()
{
	if (!Z_Registration_Info_UEnum_EBlueprintDiffChangeType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EBlueprintDiffChangeType.InnerSingleton, Z_Construct_UEnum_BlueprintExporter_EBlueprintDiffChangeType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EBlueprintDiffChangeType.InnerSingleton;
}
// ********** End Enum EBlueprintDiffChangeType ****************************************************

// ********** Begin ScriptStruct FBlueprintExportConfig ********************************************
struct Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FBlueprintExportConfig); }
	static inline consteval int16 GetStructAlignment() { return alignof(FBlueprintExportConfig); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Export configuration options\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Export configuration options" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OutputDirectory_MetaData[] = {
		{ "Category", "Export" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Output directory for exported files */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Output directory for exported files" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIncludeDependencies_MetaData[] = {
		{ "Category", "Export" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Include Blueprint dependencies */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Include Blueprint dependencies" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DependencyDepth_MetaData[] = {
		{ "Category", "Export" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Maximum dependency depth (0 = unlimited) */" },
#endif
		{ "EditCondition", "bIncludeDependencies" },
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum dependency depth (0 = unlimited)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bExportHumanReadable_MetaData[] = {
		{ "Category", "Export" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Export human-readable text summary */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Export human-readable text summary" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bExportDigest_MetaData[] = {
		{ "Category", "Export" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Export digest/metrics JSON */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Export digest/metrics JSON" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bPrettyPrint_MetaData[] = {
		{ "Category", "Format" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Pretty print JSON output */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pretty print JSON output" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bExportStateTrees_MetaData[] = {
		{ "Category", "Export" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Also export State Tree assets found in the search paths */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Also export State Tree assets found in the search paths" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FBlueprintExportConfig constinit property declarations ************
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutputDirectory;
	static void NewProp_bIncludeDependencies_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIncludeDependencies;
	static const UECodeGen_Private::FIntPropertyParams NewProp_DependencyDepth;
	static void NewProp_bExportHumanReadable_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bExportHumanReadable;
	static void NewProp_bExportDigest_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bExportDigest;
	static void NewProp_bPrettyPrint_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bPrettyPrint;
	static void NewProp_bExportStateTrees_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bExportStateTrees;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FBlueprintExportConfig constinit property declarations **************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBlueprintExportConfig>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBlueprintExportConfig;
class UScriptStruct* FBlueprintExportConfig::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBlueprintExportConfig.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBlueprintExportConfig.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBlueprintExportConfig, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("BlueprintExportConfig"));
	}
	return Z_Registration_Info_UScriptStruct_FBlueprintExportConfig.OuterSingleton;
	}

// ********** Begin ScriptStruct FBlueprintExportConfig Property Definitions ***********************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_OutputDirectory = { "OutputDirectory", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintExportConfig, OutputDirectory), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OutputDirectory_MetaData), NewProp_OutputDirectory_MetaData) };
void Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bIncludeDependencies_SetBit(void* Obj)
{
	((FBlueprintExportConfig*)Obj)->bIncludeDependencies = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bIncludeDependencies = { "bIncludeDependencies", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FBlueprintExportConfig), &Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bIncludeDependencies_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIncludeDependencies_MetaData), NewProp_bIncludeDependencies_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_DependencyDepth = { "DependencyDepth", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintExportConfig, DependencyDepth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DependencyDepth_MetaData), NewProp_DependencyDepth_MetaData) };
void Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bExportHumanReadable_SetBit(void* Obj)
{
	((FBlueprintExportConfig*)Obj)->bExportHumanReadable = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bExportHumanReadable = { "bExportHumanReadable", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FBlueprintExportConfig), &Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bExportHumanReadable_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bExportHumanReadable_MetaData), NewProp_bExportHumanReadable_MetaData) };
void Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bExportDigest_SetBit(void* Obj)
{
	((FBlueprintExportConfig*)Obj)->bExportDigest = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bExportDigest = { "bExportDigest", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FBlueprintExportConfig), &Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bExportDigest_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bExportDigest_MetaData), NewProp_bExportDigest_MetaData) };
void Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bPrettyPrint_SetBit(void* Obj)
{
	((FBlueprintExportConfig*)Obj)->bPrettyPrint = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bPrettyPrint = { "bPrettyPrint", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FBlueprintExportConfig), &Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bPrettyPrint_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bPrettyPrint_MetaData), NewProp_bPrettyPrint_MetaData) };
void Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bExportStateTrees_SetBit(void* Obj)
{
	((FBlueprintExportConfig*)Obj)->bExportStateTrees = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bExportStateTrees = { "bExportStateTrees", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FBlueprintExportConfig), &Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bExportStateTrees_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bExportStateTrees_MetaData), NewProp_bExportStateTrees_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_OutputDirectory,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bIncludeDependencies,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_DependencyDepth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bExportHumanReadable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bExportDigest,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bPrettyPrint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewProp_bExportStateTrees,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FBlueprintExportConfig Property Definitions *************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"BlueprintExportConfig",
	Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::PropPointers),
	sizeof(FBlueprintExportConfig),
	alignof(FBlueprintExportConfig),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBlueprintExportConfig()
{
	if (!Z_Registration_Info_UScriptStruct_FBlueprintExportConfig.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBlueprintExportConfig.InnerSingleton, Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FBlueprintExportConfig.InnerSingleton);
}
// ********** End ScriptStruct FBlueprintExportConfig **********************************************

// ********** Begin ScriptStruct FExportedPinType **************************************************
struct Z_Construct_UScriptStruct_FExportedPinType_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedPinType); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedPinType); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Pin type information for serialization\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pin type information for serialization" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Category_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SubCategoryObject_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PinSubCategory_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsArray_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsSet_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsMap_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsReference_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsConst_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsWeakPointer_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ValueTerminalType_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bHasBrokenReference_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** True if this pin type has a broken/orphaned object reference */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "True if this pin type has a broken/orphaned object reference" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BrokenReferenceInfo_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Description of what reference is broken (e.g., deleted class, missing asset) */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Description of what reference is broken (e.g., deleted class, missing asset)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSubCategoryObjectResolved_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** True if SubCategoryObject was resolved from a trustworthy source (property reflection or node context).\n\x09 *  False if the serializer left SubCategoryObject blank because the PinSubCategoryObject weak pointer\n\x09 *  was not safe to access and no fallback was available. Lets AI consumers distinguish \"no subtype\"\n\x09 *  from \"subtype unknown\". Defaults to true so older JSON (where this field is absent) is treated\n\x09 *  as resolved \xe2\x80\x94 only the defensive-blanking path sets this to false. */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "True if SubCategoryObject was resolved from a trustworthy source (property reflection or node context).\nFalse if the serializer left SubCategoryObject blank because the PinSubCategoryObject weak pointer\nwas not safe to access and no fallback was available. Lets AI consumers distinguish \"no subtype\"\nfrom \"subtype unknown\". Defaults to true so older JSON (where this field is absent) is treated\nas resolved \xe2\x80\x94 only the defensive-blanking path sets this to false." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedPinType constinit property declarations ******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Category;
	static const UECodeGen_Private::FStrPropertyParams NewProp_SubCategoryObject;
	static const UECodeGen_Private::FStrPropertyParams NewProp_PinSubCategory;
	static void NewProp_bIsArray_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsArray;
	static void NewProp_bIsSet_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsSet;
	static void NewProp_bIsMap_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsMap;
	static void NewProp_bIsReference_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsReference;
	static void NewProp_bIsConst_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsConst;
	static void NewProp_bIsWeakPointer_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsWeakPointer;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ValueTerminalType;
	static void NewProp_bHasBrokenReference_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bHasBrokenReference;
	static const UECodeGen_Private::FStrPropertyParams NewProp_BrokenReferenceInfo;
	static void NewProp_bSubCategoryObjectResolved_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSubCategoryObjectResolved;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedPinType constinit property declarations ********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedPinType>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedPinType_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedPinType;
class UScriptStruct* FExportedPinType::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedPinType.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedPinType.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedPinType, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedPinType"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedPinType.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedPinType Property Definitions *****************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedPinType, Category), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Category_MetaData), NewProp_Category_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_SubCategoryObject = { "SubCategoryObject", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedPinType, SubCategoryObject), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SubCategoryObject_MetaData), NewProp_SubCategoryObject_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_PinSubCategory = { "PinSubCategory", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedPinType, PinSubCategory), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PinSubCategory_MetaData), NewProp_PinSubCategory_MetaData) };
void Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsArray_SetBit(void* Obj)
{
	((FExportedPinType*)Obj)->bIsArray = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsArray = { "bIsArray", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedPinType), &Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsArray_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsArray_MetaData), NewProp_bIsArray_MetaData) };
void Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsSet_SetBit(void* Obj)
{
	((FExportedPinType*)Obj)->bIsSet = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsSet = { "bIsSet", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedPinType), &Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsSet_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsSet_MetaData), NewProp_bIsSet_MetaData) };
void Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsMap_SetBit(void* Obj)
{
	((FExportedPinType*)Obj)->bIsMap = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsMap = { "bIsMap", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedPinType), &Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsMap_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsMap_MetaData), NewProp_bIsMap_MetaData) };
void Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsReference_SetBit(void* Obj)
{
	((FExportedPinType*)Obj)->bIsReference = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsReference = { "bIsReference", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedPinType), &Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsReference_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsReference_MetaData), NewProp_bIsReference_MetaData) };
void Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsConst_SetBit(void* Obj)
{
	((FExportedPinType*)Obj)->bIsConst = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsConst = { "bIsConst", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedPinType), &Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsConst_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsConst_MetaData), NewProp_bIsConst_MetaData) };
void Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsWeakPointer_SetBit(void* Obj)
{
	((FExportedPinType*)Obj)->bIsWeakPointer = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsWeakPointer = { "bIsWeakPointer", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedPinType), &Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsWeakPointer_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsWeakPointer_MetaData), NewProp_bIsWeakPointer_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_ValueTerminalType = { "ValueTerminalType", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedPinType, ValueTerminalType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ValueTerminalType_MetaData), NewProp_ValueTerminalType_MetaData) };
void Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bHasBrokenReference_SetBit(void* Obj)
{
	((FExportedPinType*)Obj)->bHasBrokenReference = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bHasBrokenReference = { "bHasBrokenReference", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedPinType), &Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bHasBrokenReference_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bHasBrokenReference_MetaData), NewProp_bHasBrokenReference_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_BrokenReferenceInfo = { "BrokenReferenceInfo", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedPinType, BrokenReferenceInfo), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BrokenReferenceInfo_MetaData), NewProp_BrokenReferenceInfo_MetaData) };
void Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bSubCategoryObjectResolved_SetBit(void* Obj)
{
	((FExportedPinType*)Obj)->bSubCategoryObjectResolved = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bSubCategoryObjectResolved = { "bSubCategoryObjectResolved", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedPinType), &Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bSubCategoryObjectResolved_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSubCategoryObjectResolved_MetaData), NewProp_bSubCategoryObjectResolved_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedPinType_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_Category,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_SubCategoryObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_PinSubCategory,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsArray,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsSet,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsMap,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsReference,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsConst,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bIsWeakPointer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_ValueTerminalType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bHasBrokenReference,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_BrokenReferenceInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPinType_Statics::NewProp_bSubCategoryObjectResolved,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedPinType_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedPinType Property Definitions *******************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedPinType_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedPinType",
	Z_Construct_UScriptStruct_FExportedPinType_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedPinType_Statics::PropPointers),
	sizeof(FExportedPinType),
	alignof(FExportedPinType),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedPinType_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedPinType_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedPinType()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedPinType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedPinType.InnerSingleton, Z_Construct_UScriptStruct_FExportedPinType_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedPinType.InnerSingleton);
}
// ********** End ScriptStruct FExportedPinType ****************************************************

// ********** Begin ScriptStruct FExportedPinConnection ********************************************
struct Z_Construct_UScriptStruct_FExportedPinConnection_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedPinConnection); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedPinConnection); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Pin connection reference\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pin connection reference" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NodeId_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PinId_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedPinConnection constinit property declarations ************
	static const UECodeGen_Private::FStrPropertyParams NewProp_NodeId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_PinId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedPinConnection constinit property declarations **************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedPinConnection>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedPinConnection_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedPinConnection;
class UScriptStruct* FExportedPinConnection::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedPinConnection.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedPinConnection.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedPinConnection, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedPinConnection"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedPinConnection.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedPinConnection Property Definitions ***********************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedPinConnection_Statics::NewProp_NodeId = { "NodeId", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedPinConnection, NodeId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NodeId_MetaData), NewProp_NodeId_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedPinConnection_Statics::NewProp_PinId = { "PinId", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedPinConnection, PinId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PinId_MetaData), NewProp_PinId_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedPinConnection_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPinConnection_Statics::NewProp_NodeId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPinConnection_Statics::NewProp_PinId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedPinConnection_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedPinConnection Property Definitions *************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedPinConnection_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedPinConnection",
	Z_Construct_UScriptStruct_FExportedPinConnection_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedPinConnection_Statics::PropPointers),
	sizeof(FExportedPinConnection),
	alignof(FExportedPinConnection),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedPinConnection_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedPinConnection_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedPinConnection()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedPinConnection.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedPinConnection.InnerSingleton, Z_Construct_UScriptStruct_FExportedPinConnection_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedPinConnection.InnerSingleton);
}
// ********** End ScriptStruct FExportedPinConnection **********************************************

// ********** Begin ScriptStruct FExportedPin ******************************************************
struct Z_Construct_UScriptStruct_FExportedPin_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedPin); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedPin); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Exported pin data\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Exported pin data" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PinId_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PinName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PinFriendlyName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Direction_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PinType_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultValue_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AutogeneratedDefaultValue_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bHidden_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bNotConnectable_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAdvancedView_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Connections_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bHasError_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** True if this pin has an error (orphaned node, invalid state, etc.) */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "True if this pin has an error (orphaned node, invalid state, etc.)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ErrorMessage_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Error message describing what's wrong with this pin */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Error message describing what's wrong with this pin" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedPin constinit property declarations **********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_PinId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_PinName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_PinFriendlyName;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Direction_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Direction;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PinType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DefaultValue;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AutogeneratedDefaultValue;
	static void NewProp_bHidden_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bHidden;
	static void NewProp_bNotConnectable_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bNotConnectable;
	static void NewProp_bAdvancedView_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAdvancedView;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Connections_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Connections;
	static void NewProp_bHasError_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bHasError;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ErrorMessage;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedPin constinit property declarations ************************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedPin>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedPin_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedPin;
class UScriptStruct* FExportedPin::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedPin.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedPin.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedPin, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedPin"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedPin.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedPin Property Definitions *********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_PinId = { "PinId", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedPin, PinId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PinId_MetaData), NewProp_PinId_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_PinName = { "PinName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedPin, PinName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PinName_MetaData), NewProp_PinName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_PinFriendlyName = { "PinFriendlyName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedPin, PinFriendlyName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PinFriendlyName_MetaData), NewProp_PinFriendlyName_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_Direction_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_Direction = { "Direction", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedPin, Direction), Z_Construct_UEnum_BlueprintExporter_EExportPinDirection, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Direction_MetaData), NewProp_Direction_MetaData) }; // 4217096699
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_PinType = { "PinType", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedPin, PinType), Z_Construct_UScriptStruct_FExportedPinType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PinType_MetaData), NewProp_PinType_MetaData) }; // 3244080351
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_DefaultValue = { "DefaultValue", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedPin, DefaultValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultValue_MetaData), NewProp_DefaultValue_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_AutogeneratedDefaultValue = { "AutogeneratedDefaultValue", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedPin, AutogeneratedDefaultValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AutogeneratedDefaultValue_MetaData), NewProp_AutogeneratedDefaultValue_MetaData) };
void Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_bHidden_SetBit(void* Obj)
{
	((FExportedPin*)Obj)->bHidden = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_bHidden = { "bHidden", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedPin), &Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_bHidden_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bHidden_MetaData), NewProp_bHidden_MetaData) };
void Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_bNotConnectable_SetBit(void* Obj)
{
	((FExportedPin*)Obj)->bNotConnectable = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_bNotConnectable = { "bNotConnectable", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedPin), &Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_bNotConnectable_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bNotConnectable_MetaData), NewProp_bNotConnectable_MetaData) };
void Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_bAdvancedView_SetBit(void* Obj)
{
	((FExportedPin*)Obj)->bAdvancedView = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_bAdvancedView = { "bAdvancedView", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedPin), &Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_bAdvancedView_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAdvancedView_MetaData), NewProp_bAdvancedView_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_Connections_Inner = { "Connections", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FExportedPinConnection, METADATA_PARAMS(0, nullptr) }; // 417709420
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_Connections = { "Connections", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedPin, Connections), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Connections_MetaData), NewProp_Connections_MetaData) }; // 417709420
void Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_bHasError_SetBit(void* Obj)
{
	((FExportedPin*)Obj)->bHasError = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_bHasError = { "bHasError", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedPin), &Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_bHasError_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bHasError_MetaData), NewProp_bHasError_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_ErrorMessage = { "ErrorMessage", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedPin, ErrorMessage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ErrorMessage_MetaData), NewProp_ErrorMessage_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedPin_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_PinId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_PinName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_PinFriendlyName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_Direction_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_Direction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_PinType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_DefaultValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_AutogeneratedDefaultValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_bHidden,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_bNotConnectable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_bAdvancedView,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_Connections_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_Connections,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_bHasError,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedPin_Statics::NewProp_ErrorMessage,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedPin_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedPin Property Definitions ***********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedPin_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedPin",
	Z_Construct_UScriptStruct_FExportedPin_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedPin_Statics::PropPointers),
	sizeof(FExportedPin),
	alignof(FExportedPin),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedPin_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedPin_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedPin()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedPin.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedPin.InnerSingleton, Z_Construct_UScriptStruct_FExportedPin_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedPin.InnerSingleton);
}
// ********** End ScriptStruct FExportedPin ********************************************************

// ********** Begin ScriptStruct FExportedNode *****************************************************
struct Z_Construct_UScriptStruct_FExportedNode_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedNode); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedNode); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Exported node data\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Exported node data" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NodeId_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NodeGuid_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NodeClass_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NodeTitle_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NodeType_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PositionX_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PositionY_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Comment_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bCommentBubbleVisible_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bCommentBubblePinned_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NodeColor_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Pins_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NodeSpecificData_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Node-specific data stored as JSON string for extensibility */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Node-specific data stored as JSON string for extensibility" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedNode constinit property declarations *********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_NodeId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_NodeGuid;
	static const UECodeGen_Private::FStrPropertyParams NewProp_NodeClass;
	static const UECodeGen_Private::FStrPropertyParams NewProp_NodeTitle;
	static const UECodeGen_Private::FStrPropertyParams NewProp_NodeType;
	static const UECodeGen_Private::FIntPropertyParams NewProp_PositionX;
	static const UECodeGen_Private::FIntPropertyParams NewProp_PositionY;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Comment;
	static void NewProp_bCommentBubbleVisible_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bCommentBubbleVisible;
	static void NewProp_bCommentBubblePinned_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bCommentBubblePinned;
	static const UECodeGen_Private::FStrPropertyParams NewProp_NodeColor;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Pins_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Pins;
	static const UECodeGen_Private::FStrPropertyParams NewProp_NodeSpecificData;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedNode constinit property declarations ***********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedNode>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedNode_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedNode;
class UScriptStruct* FExportedNode::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedNode.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedNode.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedNode, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedNode"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedNode.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedNode Property Definitions ********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_NodeId = { "NodeId", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedNode, NodeId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NodeId_MetaData), NewProp_NodeId_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_NodeGuid = { "NodeGuid", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedNode, NodeGuid), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NodeGuid_MetaData), NewProp_NodeGuid_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_NodeClass = { "NodeClass", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedNode, NodeClass), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NodeClass_MetaData), NewProp_NodeClass_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_NodeTitle = { "NodeTitle", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedNode, NodeTitle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NodeTitle_MetaData), NewProp_NodeTitle_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_NodeType = { "NodeType", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedNode, NodeType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NodeType_MetaData), NewProp_NodeType_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_PositionX = { "PositionX", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedNode, PositionX), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PositionX_MetaData), NewProp_PositionX_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_PositionY = { "PositionY", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedNode, PositionY), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PositionY_MetaData), NewProp_PositionY_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_Comment = { "Comment", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedNode, Comment), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Comment_MetaData), NewProp_Comment_MetaData) };
void Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_bCommentBubbleVisible_SetBit(void* Obj)
{
	((FExportedNode*)Obj)->bCommentBubbleVisible = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_bCommentBubbleVisible = { "bCommentBubbleVisible", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedNode), &Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_bCommentBubbleVisible_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bCommentBubbleVisible_MetaData), NewProp_bCommentBubbleVisible_MetaData) };
void Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_bCommentBubblePinned_SetBit(void* Obj)
{
	((FExportedNode*)Obj)->bCommentBubblePinned = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_bCommentBubblePinned = { "bCommentBubblePinned", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedNode), &Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_bCommentBubblePinned_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bCommentBubblePinned_MetaData), NewProp_bCommentBubblePinned_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_NodeColor = { "NodeColor", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedNode, NodeColor), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NodeColor_MetaData), NewProp_NodeColor_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_Pins_Inner = { "Pins", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FExportedPin, METADATA_PARAMS(0, nullptr) }; // 3667484744
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_Pins = { "Pins", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedNode, Pins), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Pins_MetaData), NewProp_Pins_MetaData) }; // 3667484744
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_NodeSpecificData = { "NodeSpecificData", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedNode, NodeSpecificData), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NodeSpecificData_MetaData), NewProp_NodeSpecificData_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedNode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_NodeId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_NodeGuid,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_NodeClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_NodeTitle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_NodeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_PositionX,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_PositionY,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_Comment,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_bCommentBubbleVisible,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_bCommentBubblePinned,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_NodeColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_Pins_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_Pins,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedNode_Statics::NewProp_NodeSpecificData,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedNode_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedNode Property Definitions **********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedNode_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedNode",
	Z_Construct_UScriptStruct_FExportedNode_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedNode_Statics::PropPointers),
	sizeof(FExportedNode),
	alignof(FExportedNode),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedNode_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedNode_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedNode()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedNode.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedNode.InnerSingleton, Z_Construct_UScriptStruct_FExportedNode_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedNode.InnerSingleton);
}
// ********** End ScriptStruct FExportedNode *******************************************************

// ********** Begin ScriptStruct FExportedGraph ****************************************************
struct Z_Construct_UScriptStruct_FExportedGraph_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedGraph); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedGraph); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Exported graph data\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Exported graph data" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GraphName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GraphGuid_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GraphType_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SchemaClass_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Nodes_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedGraph constinit property declarations ********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_GraphName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_GraphGuid;
	static const UECodeGen_Private::FStrPropertyParams NewProp_GraphType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_SchemaClass;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Nodes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Nodes;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedGraph constinit property declarations **********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedGraph>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedGraph_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedGraph;
class UScriptStruct* FExportedGraph::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedGraph.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedGraph.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedGraph, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedGraph"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedGraph.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedGraph Property Definitions *******************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedGraph_Statics::NewProp_GraphName = { "GraphName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedGraph, GraphName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GraphName_MetaData), NewProp_GraphName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedGraph_Statics::NewProp_GraphGuid = { "GraphGuid", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedGraph, GraphGuid), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GraphGuid_MetaData), NewProp_GraphGuid_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedGraph_Statics::NewProp_GraphType = { "GraphType", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedGraph, GraphType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GraphType_MetaData), NewProp_GraphType_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedGraph_Statics::NewProp_SchemaClass = { "SchemaClass", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedGraph, SchemaClass), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SchemaClass_MetaData), NewProp_SchemaClass_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedGraph_Statics::NewProp_Nodes_Inner = { "Nodes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FExportedNode, METADATA_PARAMS(0, nullptr) }; // 2727321664
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FExportedGraph_Statics::NewProp_Nodes = { "Nodes", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedGraph, Nodes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Nodes_MetaData), NewProp_Nodes_MetaData) }; // 2727321664
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedGraph_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedGraph_Statics::NewProp_GraphName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedGraph_Statics::NewProp_GraphGuid,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedGraph_Statics::NewProp_GraphType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedGraph_Statics::NewProp_SchemaClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedGraph_Statics::NewProp_Nodes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedGraph_Statics::NewProp_Nodes,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedGraph_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedGraph Property Definitions *********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedGraph_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedGraph",
	Z_Construct_UScriptStruct_FExportedGraph_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedGraph_Statics::PropPointers),
	sizeof(FExportedGraph),
	alignof(FExportedGraph),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedGraph_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedGraph_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedGraph()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedGraph.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedGraph.InnerSingleton, Z_Construct_UScriptStruct_FExportedGraph_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedGraph.InnerSingleton);
}
// ********** End ScriptStruct FExportedGraph ******************************************************

// ********** Begin ScriptStruct FExportedVariableFlags ********************************************
struct Z_Construct_UScriptStruct_FExportedVariableFlags_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedVariableFlags); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedVariableFlags); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Variable flags\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Variable flags" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bInstanceEditable_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bBlueprintReadOnly_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bExposeOnSpawn_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bPrivate_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bExposeToCinematics_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bReplicated_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReplicationCondition_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRepNotify_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** CPF_RepNotify: variable triggers an OnRep_<Name> callback on replication. */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "CPF_RepNotify: variable triggers an OnRep_<Name> callback on replication." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RepNotifyFunc_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Name of the OnRep function when bRepNotify is true; empty string otherwise. */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Name of the OnRep function when bRepNotify is true; empty string otherwise." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedVariableFlags constinit property declarations ************
	static void NewProp_bInstanceEditable_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bInstanceEditable;
	static void NewProp_bBlueprintReadOnly_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bBlueprintReadOnly;
	static void NewProp_bExposeOnSpawn_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bExposeOnSpawn;
	static void NewProp_bPrivate_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bPrivate;
	static void NewProp_bExposeToCinematics_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bExposeToCinematics;
	static void NewProp_bReplicated_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bReplicated;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReplicationCondition;
	static void NewProp_bRepNotify_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRepNotify;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RepNotifyFunc;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedVariableFlags constinit property declarations **************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedVariableFlags>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedVariableFlags_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedVariableFlags;
class UScriptStruct* FExportedVariableFlags::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedVariableFlags.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedVariableFlags.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedVariableFlags, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedVariableFlags"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedVariableFlags.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedVariableFlags Property Definitions ***********************
void Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bInstanceEditable_SetBit(void* Obj)
{
	((FExportedVariableFlags*)Obj)->bInstanceEditable = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bInstanceEditable = { "bInstanceEditable", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedVariableFlags), &Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bInstanceEditable_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bInstanceEditable_MetaData), NewProp_bInstanceEditable_MetaData) };
void Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bBlueprintReadOnly_SetBit(void* Obj)
{
	((FExportedVariableFlags*)Obj)->bBlueprintReadOnly = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bBlueprintReadOnly = { "bBlueprintReadOnly", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedVariableFlags), &Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bBlueprintReadOnly_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bBlueprintReadOnly_MetaData), NewProp_bBlueprintReadOnly_MetaData) };
void Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bExposeOnSpawn_SetBit(void* Obj)
{
	((FExportedVariableFlags*)Obj)->bExposeOnSpawn = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bExposeOnSpawn = { "bExposeOnSpawn", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedVariableFlags), &Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bExposeOnSpawn_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bExposeOnSpawn_MetaData), NewProp_bExposeOnSpawn_MetaData) };
void Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bPrivate_SetBit(void* Obj)
{
	((FExportedVariableFlags*)Obj)->bPrivate = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bPrivate = { "bPrivate", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedVariableFlags), &Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bPrivate_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bPrivate_MetaData), NewProp_bPrivate_MetaData) };
void Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bExposeToCinematics_SetBit(void* Obj)
{
	((FExportedVariableFlags*)Obj)->bExposeToCinematics = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bExposeToCinematics = { "bExposeToCinematics", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedVariableFlags), &Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bExposeToCinematics_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bExposeToCinematics_MetaData), NewProp_bExposeToCinematics_MetaData) };
void Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bReplicated_SetBit(void* Obj)
{
	((FExportedVariableFlags*)Obj)->bReplicated = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bReplicated = { "bReplicated", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedVariableFlags), &Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bReplicated_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bReplicated_MetaData), NewProp_bReplicated_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_ReplicationCondition = { "ReplicationCondition", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedVariableFlags, ReplicationCondition), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReplicationCondition_MetaData), NewProp_ReplicationCondition_MetaData) };
void Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bRepNotify_SetBit(void* Obj)
{
	((FExportedVariableFlags*)Obj)->bRepNotify = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bRepNotify = { "bRepNotify", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedVariableFlags), &Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bRepNotify_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRepNotify_MetaData), NewProp_bRepNotify_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_RepNotifyFunc = { "RepNotifyFunc", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedVariableFlags, RepNotifyFunc), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RepNotifyFunc_MetaData), NewProp_RepNotifyFunc_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bInstanceEditable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bBlueprintReadOnly,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bExposeOnSpawn,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bPrivate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bExposeToCinematics,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bReplicated,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_ReplicationCondition,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_bRepNotify,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewProp_RepNotifyFunc,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedVariableFlags Property Definitions *************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedVariableFlags",
	Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::PropPointers),
	sizeof(FExportedVariableFlags),
	alignof(FExportedVariableFlags),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedVariableFlags()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedVariableFlags.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedVariableFlags.InnerSingleton, Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedVariableFlags.InnerSingleton);
}
// ********** End ScriptStruct FExportedVariableFlags **********************************************

// ********** Begin ScriptStruct FExportedVariable *************************************************
struct Z_Construct_UScriptStruct_FExportedVariable_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedVariable); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedVariable); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Exported variable data\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Exported variable data" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VariableName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VariableGuid_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VariableType_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultValue_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Category_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Flags_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ToolTip_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MetaData_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedVariable constinit property declarations *****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_VariableName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_VariableGuid;
	static const UECodeGen_Private::FStructPropertyParams NewProp_VariableType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DefaultValue;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Category;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Flags;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ToolTip;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MetaData_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MetaData_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_MetaData;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedVariable constinit property declarations *******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedVariable>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedVariable_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedVariable;
class UScriptStruct* FExportedVariable::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedVariable.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedVariable.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedVariable, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedVariable"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedVariable.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedVariable Property Definitions ****************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_VariableName = { "VariableName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedVariable, VariableName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VariableName_MetaData), NewProp_VariableName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_VariableGuid = { "VariableGuid", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedVariable, VariableGuid), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VariableGuid_MetaData), NewProp_VariableGuid_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_VariableType = { "VariableType", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedVariable, VariableType), Z_Construct_UScriptStruct_FExportedPinType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VariableType_MetaData), NewProp_VariableType_MetaData) }; // 3244080351
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_DefaultValue = { "DefaultValue", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedVariable, DefaultValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultValue_MetaData), NewProp_DefaultValue_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedVariable, Category), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Category_MetaData), NewProp_Category_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_Flags = { "Flags", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedVariable, Flags), Z_Construct_UScriptStruct_FExportedVariableFlags, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Flags_MetaData), NewProp_Flags_MetaData) }; // 2431683992
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_ToolTip = { "ToolTip", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedVariable, ToolTip), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ToolTip_MetaData), NewProp_ToolTip_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_MetaData_ValueProp = { "MetaData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_MetaData_Key_KeyProp = { "MetaData_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_MetaData = { "MetaData", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedVariable, MetaData), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MetaData_MetaData), NewProp_MetaData_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedVariable_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_VariableName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_VariableGuid,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_VariableType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_DefaultValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_Category,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_Flags,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_ToolTip,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_MetaData_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_MetaData_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedVariable_Statics::NewProp_MetaData,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedVariable_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedVariable Property Definitions ******************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedVariable_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedVariable",
	Z_Construct_UScriptStruct_FExportedVariable_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedVariable_Statics::PropPointers),
	sizeof(FExportedVariable),
	alignof(FExportedVariable),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedVariable_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedVariable_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedVariable()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedVariable.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedVariable.InnerSingleton, Z_Construct_UScriptStruct_FExportedVariable_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedVariable.InnerSingleton);
}
// ********** End ScriptStruct FExportedVariable ***************************************************

// ********** Begin ScriptStruct FExportedFunctionParam ********************************************
struct Z_Construct_UScriptStruct_FExportedFunctionParam_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedFunctionParam); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedFunctionParam); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Function parameter data\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Function parameter data" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParamName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParamType_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultValue_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsOutput_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bPassByReference_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedFunctionParam constinit property declarations ************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ParamName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ParamType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DefaultValue;
	static void NewProp_bIsOutput_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsOutput;
	static void NewProp_bPassByReference_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bPassByReference;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedFunctionParam constinit property declarations **************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedFunctionParam>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedFunctionParam_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedFunctionParam;
class UScriptStruct* FExportedFunctionParam::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedFunctionParam.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedFunctionParam.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedFunctionParam, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedFunctionParam"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedFunctionParam.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedFunctionParam Property Definitions ***********************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::NewProp_ParamName = { "ParamName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedFunctionParam, ParamName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParamName_MetaData), NewProp_ParamName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::NewProp_ParamType = { "ParamType", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedFunctionParam, ParamType), Z_Construct_UScriptStruct_FExportedPinType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParamType_MetaData), NewProp_ParamType_MetaData) }; // 3244080351
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::NewProp_DefaultValue = { "DefaultValue", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedFunctionParam, DefaultValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultValue_MetaData), NewProp_DefaultValue_MetaData) };
void Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::NewProp_bIsOutput_SetBit(void* Obj)
{
	((FExportedFunctionParam*)Obj)->bIsOutput = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::NewProp_bIsOutput = { "bIsOutput", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedFunctionParam), &Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::NewProp_bIsOutput_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsOutput_MetaData), NewProp_bIsOutput_MetaData) };
void Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::NewProp_bPassByReference_SetBit(void* Obj)
{
	((FExportedFunctionParam*)Obj)->bPassByReference = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::NewProp_bPassByReference = { "bPassByReference", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedFunctionParam), &Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::NewProp_bPassByReference_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bPassByReference_MetaData), NewProp_bPassByReference_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::NewProp_ParamName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::NewProp_ParamType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::NewProp_DefaultValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::NewProp_bIsOutput,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::NewProp_bPassByReference,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedFunctionParam Property Definitions *************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedFunctionParam",
	Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::PropPointers),
	sizeof(FExportedFunctionParam),
	alignof(FExportedFunctionParam),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedFunctionParam()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedFunctionParam.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedFunctionParam.InnerSingleton, Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedFunctionParam.InnerSingleton);
}
// ********** End ScriptStruct FExportedFunctionParam **********************************************

// ********** Begin ScriptStruct FExportedFunctionFlags ********************************************
struct Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedFunctionFlags); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedFunctionFlags); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Function flags\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Function flags" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bPure_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bConst_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bStatic_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bCallInEditor_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bOverride_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEvent_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AccessSpecifier_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bServer_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** RPC net-exec flags (set from UK2Node_FunctionEntry::GetFunctionFlags()). */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "RPC net-exec flags (set from UK2Node_FunctionEntry::GetFunctionFlags())." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bClient_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bNetMulticast_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bReliable_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bBlueprintAuthorityOnly_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bBlueprintCosmetic_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedFunctionFlags constinit property declarations ************
	static void NewProp_bPure_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bPure;
	static void NewProp_bConst_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bConst;
	static void NewProp_bStatic_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bStatic;
	static void NewProp_bCallInEditor_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bCallInEditor;
	static void NewProp_bOverride_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOverride;
	static void NewProp_bEvent_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEvent;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AccessSpecifier;
	static void NewProp_bServer_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bServer;
	static void NewProp_bClient_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bClient;
	static void NewProp_bNetMulticast_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bNetMulticast;
	static void NewProp_bReliable_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bReliable;
	static void NewProp_bBlueprintAuthorityOnly_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bBlueprintAuthorityOnly;
	static void NewProp_bBlueprintCosmetic_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bBlueprintCosmetic;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedFunctionFlags constinit property declarations **************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedFunctionFlags>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedFunctionFlags;
class UScriptStruct* FExportedFunctionFlags::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedFunctionFlags.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedFunctionFlags.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedFunctionFlags, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedFunctionFlags"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedFunctionFlags.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedFunctionFlags Property Definitions ***********************
void Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bPure_SetBit(void* Obj)
{
	((FExportedFunctionFlags*)Obj)->bPure = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bPure = { "bPure", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedFunctionFlags), &Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bPure_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bPure_MetaData), NewProp_bPure_MetaData) };
void Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bConst_SetBit(void* Obj)
{
	((FExportedFunctionFlags*)Obj)->bConst = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bConst = { "bConst", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedFunctionFlags), &Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bConst_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bConst_MetaData), NewProp_bConst_MetaData) };
void Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bStatic_SetBit(void* Obj)
{
	((FExportedFunctionFlags*)Obj)->bStatic = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bStatic = { "bStatic", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedFunctionFlags), &Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bStatic_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bStatic_MetaData), NewProp_bStatic_MetaData) };
void Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bCallInEditor_SetBit(void* Obj)
{
	((FExportedFunctionFlags*)Obj)->bCallInEditor = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bCallInEditor = { "bCallInEditor", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedFunctionFlags), &Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bCallInEditor_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bCallInEditor_MetaData), NewProp_bCallInEditor_MetaData) };
void Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bOverride_SetBit(void* Obj)
{
	((FExportedFunctionFlags*)Obj)->bOverride = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bOverride = { "bOverride", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedFunctionFlags), &Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bOverride_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bOverride_MetaData), NewProp_bOverride_MetaData) };
void Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bEvent_SetBit(void* Obj)
{
	((FExportedFunctionFlags*)Obj)->bEvent = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bEvent = { "bEvent", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedFunctionFlags), &Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bEvent_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEvent_MetaData), NewProp_bEvent_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_AccessSpecifier = { "AccessSpecifier", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedFunctionFlags, AccessSpecifier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AccessSpecifier_MetaData), NewProp_AccessSpecifier_MetaData) };
void Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bServer_SetBit(void* Obj)
{
	((FExportedFunctionFlags*)Obj)->bServer = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bServer = { "bServer", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedFunctionFlags), &Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bServer_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bServer_MetaData), NewProp_bServer_MetaData) };
void Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bClient_SetBit(void* Obj)
{
	((FExportedFunctionFlags*)Obj)->bClient = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bClient = { "bClient", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedFunctionFlags), &Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bClient_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bClient_MetaData), NewProp_bClient_MetaData) };
void Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bNetMulticast_SetBit(void* Obj)
{
	((FExportedFunctionFlags*)Obj)->bNetMulticast = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bNetMulticast = { "bNetMulticast", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedFunctionFlags), &Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bNetMulticast_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bNetMulticast_MetaData), NewProp_bNetMulticast_MetaData) };
void Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bReliable_SetBit(void* Obj)
{
	((FExportedFunctionFlags*)Obj)->bReliable = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bReliable = { "bReliable", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedFunctionFlags), &Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bReliable_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bReliable_MetaData), NewProp_bReliable_MetaData) };
void Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bBlueprintAuthorityOnly_SetBit(void* Obj)
{
	((FExportedFunctionFlags*)Obj)->bBlueprintAuthorityOnly = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bBlueprintAuthorityOnly = { "bBlueprintAuthorityOnly", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedFunctionFlags), &Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bBlueprintAuthorityOnly_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bBlueprintAuthorityOnly_MetaData), NewProp_bBlueprintAuthorityOnly_MetaData) };
void Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bBlueprintCosmetic_SetBit(void* Obj)
{
	((FExportedFunctionFlags*)Obj)->bBlueprintCosmetic = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bBlueprintCosmetic = { "bBlueprintCosmetic", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedFunctionFlags), &Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bBlueprintCosmetic_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bBlueprintCosmetic_MetaData), NewProp_bBlueprintCosmetic_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bPure,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bConst,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bStatic,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bCallInEditor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bOverride,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bEvent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_AccessSpecifier,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bServer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bClient,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bNetMulticast,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bReliable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bBlueprintAuthorityOnly,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewProp_bBlueprintCosmetic,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedFunctionFlags Property Definitions *************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedFunctionFlags",
	Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::PropPointers),
	sizeof(FExportedFunctionFlags),
	alignof(FExportedFunctionFlags),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedFunctionFlags()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedFunctionFlags.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedFunctionFlags.InnerSingleton, Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedFunctionFlags.InnerSingleton);
}
// ********** End ScriptStruct FExportedFunctionFlags **********************************************

// ********** Begin ScriptStruct FExportedFunction *************************************************
struct Z_Construct_UScriptStruct_FExportedFunction_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedFunction); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedFunction); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Exported function data\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Exported function data" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FunctionName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FunctionGuid_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Flags_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Inputs_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Outputs_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LocalVariables_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Keywords_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Category_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Graph_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsInterfaceOverride_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** True iff this function is an override of an interface function \xe2\x80\x94\n\x09 *  i.e. the UEdGraph* lives on `Blueprint->ImplementedInterfaces[].Graphs`\n\x09 *  rather than `Blueprint->FunctionGraphs`. Surfaces interface-stub\n\x09 *  overrides that `implement_interface_function` detects but the old\n\x09 *  exporter missed (the \"invisible stub\" bug closed in M26.1.1). */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "True iff this function is an override of an interface function \xe2\x80\x94\ni.e. the UEdGraph* lives on `Blueprint->ImplementedInterfaces[].Graphs`\nrather than `Blueprint->FunctionGraphs`. Surfaces interface-stub\noverrides that `implement_interface_function` detects but the old\nexporter missed (the \"invisible stub\" bug closed in M26.1.1)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InterfaceClassPath_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** When `bIsInterfaceOverride` is true, the `/Game/...` class path of\n\x09 *  the interface Blueprint this override belongs to (the one listed on\n\x09 *  `Blueprint->ImplementedInterfaces`). Empty otherwise. */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "When `bIsInterfaceOverride` is true, the `/Game/...` class path of\nthe interface Blueprint this override belongs to (the one listed on\n`Blueprint->ImplementedInterfaces`). Empty otherwise." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedFunction constinit property declarations *****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_FunctionName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_FunctionGuid;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Flags;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Inputs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Inputs;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Outputs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Outputs;
	static const UECodeGen_Private::FStructPropertyParams NewProp_LocalVariables_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_LocalVariables;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Description;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Keywords_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Keywords;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Category;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Graph;
	static void NewProp_bIsInterfaceOverride_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsInterfaceOverride;
	static const UECodeGen_Private::FStrPropertyParams NewProp_InterfaceClassPath;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedFunction constinit property declarations *******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedFunction>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedFunction_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedFunction;
class UScriptStruct* FExportedFunction::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedFunction.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedFunction.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedFunction, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedFunction"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedFunction.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedFunction Property Definitions ****************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_FunctionName = { "FunctionName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedFunction, FunctionName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FunctionName_MetaData), NewProp_FunctionName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_FunctionGuid = { "FunctionGuid", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedFunction, FunctionGuid), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FunctionGuid_MetaData), NewProp_FunctionGuid_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Flags = { "Flags", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedFunction, Flags), Z_Construct_UScriptStruct_FExportedFunctionFlags, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Flags_MetaData), NewProp_Flags_MetaData) }; // 409630351
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Inputs_Inner = { "Inputs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FExportedFunctionParam, METADATA_PARAMS(0, nullptr) }; // 1365006374
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Inputs = { "Inputs", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedFunction, Inputs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Inputs_MetaData), NewProp_Inputs_MetaData) }; // 1365006374
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Outputs_Inner = { "Outputs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FExportedFunctionParam, METADATA_PARAMS(0, nullptr) }; // 1365006374
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Outputs = { "Outputs", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedFunction, Outputs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Outputs_MetaData), NewProp_Outputs_MetaData) }; // 1365006374
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_LocalVariables_Inner = { "LocalVariables", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FExportedVariable, METADATA_PARAMS(0, nullptr) }; // 1626092749
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_LocalVariables = { "LocalVariables", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedFunction, LocalVariables), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LocalVariables_MetaData), NewProp_LocalVariables_MetaData) }; // 1626092749
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedFunction, Description), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Description_MetaData), NewProp_Description_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Keywords_Inner = { "Keywords", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Keywords = { "Keywords", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedFunction, Keywords), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Keywords_MetaData), NewProp_Keywords_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedFunction, Category), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Category_MetaData), NewProp_Category_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Graph = { "Graph", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedFunction, Graph), Z_Construct_UScriptStruct_FExportedGraph, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Graph_MetaData), NewProp_Graph_MetaData) }; // 193825846
void Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_bIsInterfaceOverride_SetBit(void* Obj)
{
	((FExportedFunction*)Obj)->bIsInterfaceOverride = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_bIsInterfaceOverride = { "bIsInterfaceOverride", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedFunction), &Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_bIsInterfaceOverride_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsInterfaceOverride_MetaData), NewProp_bIsInterfaceOverride_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_InterfaceClassPath = { "InterfaceClassPath", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedFunction, InterfaceClassPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InterfaceClassPath_MetaData), NewProp_InterfaceClassPath_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedFunction_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_FunctionName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_FunctionGuid,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Flags,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Inputs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Inputs,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Outputs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Outputs,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_LocalVariables_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_LocalVariables,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Description,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Keywords_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Keywords,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Category,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_Graph,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_bIsInterfaceOverride,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedFunction_Statics::NewProp_InterfaceClassPath,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedFunction_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedFunction Property Definitions ******************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedFunction_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedFunction",
	Z_Construct_UScriptStruct_FExportedFunction_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedFunction_Statics::PropPointers),
	sizeof(FExportedFunction),
	alignof(FExportedFunction),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedFunction_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedFunction_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedFunction()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedFunction.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedFunction.InnerSingleton, Z_Construct_UScriptStruct_FExportedFunction_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedFunction.InnerSingleton);
}
// ********** End ScriptStruct FExportedFunction ***************************************************

// ********** Begin ScriptStruct FExportedComponentProperty ****************************************
struct Z_Construct_UScriptStruct_FExportedComponentProperty_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedComponentProperty); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedComponentProperty); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Component property\n *\n * For ordinary properties, `Value` carries the flat `ExportTextItem_Direct` string and\n * `bIsInstancedSubobject` is false.\n *\n * For Instanced / EditInlineNew subobject references (e.g. `UAIPerceptionComponent::SenseConfigs`,\n * GAS `AbilitySystemComponent` attribute sets, anim instance layers), the serializer\n * additionally populates `SubobjectJsonValues` with a structured JSON description of each\n * referenced subobject so AI consumers can read nested property values (sight radius,\n * hearing range, affiliation, etc.) instead of parsing the opaque `Value` blob.\n *\n * Each element of `SubobjectJsonValues` is an FJsonObject with shape:\n *   { \"classPath\": \"/Script/AIModule.AISenseConfig_Sight\",\n *     \"objectName\": \"AISenseConfig_Sight_0\",\n *     \"arrayIndex\": 0,             // optional, present for array/map contexts\n *     \"mapKey\": \"...\",             // optional, present for map contexts\n *     \"properties\": [ { \"propertyName\", \"propertyType\", \"value\",\n *                       \"bIsInstancedSubobject\"?, \"subobjects\"? } ],\n *     \"bTruncated\": true,          // optional, emitted only when true\n *     \"bCycleDetected\": true,      // optional, emitted only when true\n *     \"bHasBrokenReference\": true, // optional, emitted only when true\n *     \"brokenReferenceInfo\": \"...\" // optional\n *   }\n *\n * `SubobjectJsonValues` is NOT a UPROPERTY: the nested \"properties\" array inside each\n * subobject is itself an array of FExportedComponentProperty-shaped JSON, which would\n * create an A->B->A USTRUCT cycle that UHT does not support. The tree is emitted and\n * parsed as opaque JSON by `ToJson`/`FromJson`; no typed C++ consumer needs to walk it.\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Component property\n\nFor ordinary properties, `Value` carries the flat `ExportTextItem_Direct` string and\n`bIsInstancedSubobject` is false.\n\nFor Instanced / EditInlineNew subobject references (e.g. `UAIPerceptionComponent::SenseConfigs`,\nGAS `AbilitySystemComponent` attribute sets, anim instance layers), the serializer\nadditionally populates `SubobjectJsonValues` with a structured JSON description of each\nreferenced subobject so AI consumers can read nested property values (sight radius,\nhearing range, affiliation, etc.) instead of parsing the opaque `Value` blob.\n\nEach element of `SubobjectJsonValues` is an FJsonObject with shape:\n  { \"classPath\": \"/Script/AIModule.AISenseConfig_Sight\",\n    \"objectName\": \"AISenseConfig_Sight_0\",\n    \"arrayIndex\": 0,             // optional, present for array/map contexts\n    \"mapKey\": \"...\",             // optional, present for map contexts\n    \"properties\": [ { \"propertyName\", \"propertyType\", \"value\",\n                      \"bIsInstancedSubobject\"?, \"subobjects\"? } ],\n    \"bTruncated\": true,          // optional, emitted only when true\n    \"bCycleDetected\": true,      // optional, emitted only when true\n    \"bHasBrokenReference\": true, // optional, emitted only when true\n    \"brokenReferenceInfo\": \"...\" // optional\n  }\n\n`SubobjectJsonValues` is NOT a UPROPERTY: the nested \"properties\" array inside each\nsubobject is itself an array of FExportedComponentProperty-shaped JSON, which would\ncreate an A->B->A USTRUCT cycle that UHT does not support. The tree is emitted and\nparsed as opaque JSON by `ToJson`/`FromJson`; no typed C++ consumer needs to walk it." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PropertyName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PropertyType_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsInstancedSubobject_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** True when this property points to one or more Instanced / EditInlineNew subobjects\n\x09 *  and `SubobjectJsonValues` has been populated with their structured property trees. */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "True when this property points to one or more Instanced / EditInlineNew subobjects\nand `SubobjectJsonValues` has been populated with their structured property trees." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedComponentProperty constinit property declarations ********
	static const UECodeGen_Private::FStrPropertyParams NewProp_PropertyName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_PropertyType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Value;
	static void NewProp_bIsInstancedSubobject_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsInstancedSubobject;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedComponentProperty constinit property declarations **********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedComponentProperty>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedComponentProperty_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedComponentProperty;
class UScriptStruct* FExportedComponentProperty::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedComponentProperty.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedComponentProperty.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedComponentProperty, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedComponentProperty"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedComponentProperty.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedComponentProperty Property Definitions *******************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedComponentProperty_Statics::NewProp_PropertyName = { "PropertyName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedComponentProperty, PropertyName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PropertyName_MetaData), NewProp_PropertyName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedComponentProperty_Statics::NewProp_PropertyType = { "PropertyType", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedComponentProperty, PropertyType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PropertyType_MetaData), NewProp_PropertyType_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedComponentProperty_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedComponentProperty, Value), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Value_MetaData), NewProp_Value_MetaData) };
void Z_Construct_UScriptStruct_FExportedComponentProperty_Statics::NewProp_bIsInstancedSubobject_SetBit(void* Obj)
{
	((FExportedComponentProperty*)Obj)->bIsInstancedSubobject = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedComponentProperty_Statics::NewProp_bIsInstancedSubobject = { "bIsInstancedSubobject", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedComponentProperty), &Z_Construct_UScriptStruct_FExportedComponentProperty_Statics::NewProp_bIsInstancedSubobject_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsInstancedSubobject_MetaData), NewProp_bIsInstancedSubobject_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedComponentProperty_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedComponentProperty_Statics::NewProp_PropertyName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedComponentProperty_Statics::NewProp_PropertyType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedComponentProperty_Statics::NewProp_Value,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedComponentProperty_Statics::NewProp_bIsInstancedSubobject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedComponentProperty_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedComponentProperty Property Definitions *********************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedComponentProperty_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedComponentProperty",
	Z_Construct_UScriptStruct_FExportedComponentProperty_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedComponentProperty_Statics::PropPointers),
	sizeof(FExportedComponentProperty),
	alignof(FExportedComponentProperty),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedComponentProperty_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedComponentProperty_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedComponentProperty()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedComponentProperty.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedComponentProperty.InnerSingleton, Z_Construct_UScriptStruct_FExportedComponentProperty_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedComponentProperty.InnerSingleton);
}
// ********** End ScriptStruct FExportedComponentProperty ******************************************

// ********** Begin ScriptStruct FExportedComponent ************************************************
struct Z_Construct_UScriptStruct_FExportedComponent_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedComponent); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedComponent); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Exported component data (for Actor blueprints)\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Exported component data (for Actor blueprints)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComponentName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComponentClass_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParentComponentName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsRootComponent_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttachSocketName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Properties_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedComponent constinit property declarations ****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ComponentName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ComponentClass;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ParentComponentName;
	static void NewProp_bIsRootComponent_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsRootComponent;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AttachSocketName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Properties_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Properties;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedComponent constinit property declarations ******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedComponent>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedComponent_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedComponent;
class UScriptStruct* FExportedComponent::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedComponent.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedComponent.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedComponent, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedComponent"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedComponent.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedComponent Property Definitions ***************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedComponent_Statics::NewProp_ComponentName = { "ComponentName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedComponent, ComponentName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComponentName_MetaData), NewProp_ComponentName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedComponent_Statics::NewProp_ComponentClass = { "ComponentClass", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedComponent, ComponentClass), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComponentClass_MetaData), NewProp_ComponentClass_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedComponent_Statics::NewProp_ParentComponentName = { "ParentComponentName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedComponent, ParentComponentName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParentComponentName_MetaData), NewProp_ParentComponentName_MetaData) };
void Z_Construct_UScriptStruct_FExportedComponent_Statics::NewProp_bIsRootComponent_SetBit(void* Obj)
{
	((FExportedComponent*)Obj)->bIsRootComponent = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedComponent_Statics::NewProp_bIsRootComponent = { "bIsRootComponent", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedComponent), &Z_Construct_UScriptStruct_FExportedComponent_Statics::NewProp_bIsRootComponent_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsRootComponent_MetaData), NewProp_bIsRootComponent_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedComponent_Statics::NewProp_AttachSocketName = { "AttachSocketName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedComponent, AttachSocketName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttachSocketName_MetaData), NewProp_AttachSocketName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedComponent_Statics::NewProp_Properties_Inner = { "Properties", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FExportedComponentProperty, METADATA_PARAMS(0, nullptr) }; // 3006916080
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FExportedComponent_Statics::NewProp_Properties = { "Properties", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedComponent, Properties), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Properties_MetaData), NewProp_Properties_MetaData) }; // 3006916080
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedComponent_Statics::NewProp_ComponentName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedComponent_Statics::NewProp_ComponentClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedComponent_Statics::NewProp_ParentComponentName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedComponent_Statics::NewProp_bIsRootComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedComponent_Statics::NewProp_AttachSocketName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedComponent_Statics::NewProp_Properties_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedComponent_Statics::NewProp_Properties,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedComponent_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedComponent Property Definitions *****************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedComponent_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedComponent",
	Z_Construct_UScriptStruct_FExportedComponent_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedComponent_Statics::PropPointers),
	sizeof(FExportedComponent),
	alignof(FExportedComponent),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedComponent_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedComponent_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedComponent()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedComponent.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedComponent.InnerSingleton, Z_Construct_UScriptStruct_FExportedComponent_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedComponent.InnerSingleton);
}
// ********** End ScriptStruct FExportedComponent **************************************************

// ********** Begin ScriptStruct FExportedDependency ***********************************************
struct Z_Construct_UScriptStruct_FExportedDependency_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedDependency); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedDependency); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Blueprint dependency reference\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint dependency reference" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AssetPath_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AssetName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DependencyType_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsBlueprint_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsNativeClass_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedDependency constinit property declarations ***************
	static const UECodeGen_Private::FStrPropertyParams NewProp_AssetPath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AssetName;
	static const UECodeGen_Private::FBytePropertyParams NewProp_DependencyType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_DependencyType;
	static void NewProp_bIsBlueprint_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsBlueprint;
	static void NewProp_bIsNativeClass_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsNativeClass;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Description;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedDependency constinit property declarations *****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedDependency>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedDependency_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedDependency;
class UScriptStruct* FExportedDependency::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedDependency.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedDependency.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedDependency, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedDependency"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedDependency.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedDependency Property Definitions **************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedDependency_Statics::NewProp_AssetPath = { "AssetPath", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedDependency, AssetPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AssetPath_MetaData), NewProp_AssetPath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedDependency_Statics::NewProp_AssetName = { "AssetName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedDependency, AssetName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AssetName_MetaData), NewProp_AssetName_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FExportedDependency_Statics::NewProp_DependencyType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FExportedDependency_Statics::NewProp_DependencyType = { "DependencyType", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedDependency, DependencyType), Z_Construct_UEnum_BlueprintExporter_EExportDependencyType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DependencyType_MetaData), NewProp_DependencyType_MetaData) }; // 3110129056
void Z_Construct_UScriptStruct_FExportedDependency_Statics::NewProp_bIsBlueprint_SetBit(void* Obj)
{
	((FExportedDependency*)Obj)->bIsBlueprint = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedDependency_Statics::NewProp_bIsBlueprint = { "bIsBlueprint", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedDependency), &Z_Construct_UScriptStruct_FExportedDependency_Statics::NewProp_bIsBlueprint_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsBlueprint_MetaData), NewProp_bIsBlueprint_MetaData) };
void Z_Construct_UScriptStruct_FExportedDependency_Statics::NewProp_bIsNativeClass_SetBit(void* Obj)
{
	((FExportedDependency*)Obj)->bIsNativeClass = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedDependency_Statics::NewProp_bIsNativeClass = { "bIsNativeClass", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedDependency), &Z_Construct_UScriptStruct_FExportedDependency_Statics::NewProp_bIsNativeClass_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsNativeClass_MetaData), NewProp_bIsNativeClass_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedDependency_Statics::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedDependency, Description), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Description_MetaData), NewProp_Description_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedDependency_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedDependency_Statics::NewProp_AssetPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedDependency_Statics::NewProp_AssetName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedDependency_Statics::NewProp_DependencyType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedDependency_Statics::NewProp_DependencyType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedDependency_Statics::NewProp_bIsBlueprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedDependency_Statics::NewProp_bIsNativeClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedDependency_Statics::NewProp_Description,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedDependency_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedDependency Property Definitions ****************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedDependency_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedDependency",
	Z_Construct_UScriptStruct_FExportedDependency_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedDependency_Statics::PropPointers),
	sizeof(FExportedDependency),
	alignof(FExportedDependency),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedDependency_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedDependency_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedDependency()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedDependency.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedDependency.InnerSingleton, Z_Construct_UScriptStruct_FExportedDependency_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedDependency.InnerSingleton);
}
// ********** End ScriptStruct FExportedDependency *************************************************

// ********** Begin ScriptStruct FExportedParentClass **********************************************
struct Z_Construct_UScriptStruct_FExportedParentClass_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedParentClass); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedParentClass); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Parent class information\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Parent class information" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClassName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClassPath_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsNative_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ModuleName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedParentClass constinit property declarations **************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ClassName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ClassPath;
	static void NewProp_bIsNative_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsNative;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ModuleName;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedParentClass constinit property declarations ****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedParentClass>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedParentClass_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedParentClass;
class UScriptStruct* FExportedParentClass::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedParentClass.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedParentClass.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedParentClass, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedParentClass"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedParentClass.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedParentClass Property Definitions *************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedParentClass_Statics::NewProp_ClassName = { "ClassName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedParentClass, ClassName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClassName_MetaData), NewProp_ClassName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedParentClass_Statics::NewProp_ClassPath = { "ClassPath", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedParentClass, ClassPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClassPath_MetaData), NewProp_ClassPath_MetaData) };
void Z_Construct_UScriptStruct_FExportedParentClass_Statics::NewProp_bIsNative_SetBit(void* Obj)
{
	((FExportedParentClass*)Obj)->bIsNative = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedParentClass_Statics::NewProp_bIsNative = { "bIsNative", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedParentClass), &Z_Construct_UScriptStruct_FExportedParentClass_Statics::NewProp_bIsNative_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsNative_MetaData), NewProp_bIsNative_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedParentClass_Statics::NewProp_ModuleName = { "ModuleName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedParentClass, ModuleName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ModuleName_MetaData), NewProp_ModuleName_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedParentClass_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedParentClass_Statics::NewProp_ClassName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedParentClass_Statics::NewProp_ClassPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedParentClass_Statics::NewProp_bIsNative,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedParentClass_Statics::NewProp_ModuleName,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedParentClass_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedParentClass Property Definitions ***************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedParentClass_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedParentClass",
	Z_Construct_UScriptStruct_FExportedParentClass_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedParentClass_Statics::PropPointers),
	sizeof(FExportedParentClass),
	alignof(FExportedParentClass),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedParentClass_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedParentClass_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedParentClass()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedParentClass.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedParentClass.InnerSingleton, Z_Construct_UScriptStruct_FExportedParentClass_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedParentClass.InnerSingleton);
}
// ********** End ScriptStruct FExportedParentClass ************************************************

// ********** Begin ScriptStruct FExportInfo *******************************************************
struct Z_Construct_UScriptStruct_FExportInfo_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportInfo); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportInfo); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Export metadata/info\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Export metadata/info" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SchemaVersion_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EngineVersion_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PluginVersion_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExportTimestamp_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ContentHash_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportInfo constinit property declarations ***********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_SchemaVersion;
	static const UECodeGen_Private::FStrPropertyParams NewProp_EngineVersion;
	static const UECodeGen_Private::FStrPropertyParams NewProp_PluginVersion;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ExportTimestamp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ContentHash;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportInfo constinit property declarations *************************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportInfo>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportInfo_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportInfo;
class UScriptStruct* FExportInfo::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportInfo.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportInfo.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportInfo, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportInfo"));
	}
	return Z_Registration_Info_UScriptStruct_FExportInfo.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportInfo Property Definitions **********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportInfo_Statics::NewProp_SchemaVersion = { "SchemaVersion", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportInfo, SchemaVersion), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SchemaVersion_MetaData), NewProp_SchemaVersion_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportInfo_Statics::NewProp_EngineVersion = { "EngineVersion", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportInfo, EngineVersion), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EngineVersion_MetaData), NewProp_EngineVersion_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportInfo_Statics::NewProp_PluginVersion = { "PluginVersion", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportInfo, PluginVersion), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PluginVersion_MetaData), NewProp_PluginVersion_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportInfo_Statics::NewProp_ExportTimestamp = { "ExportTimestamp", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportInfo, ExportTimestamp), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExportTimestamp_MetaData), NewProp_ExportTimestamp_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportInfo_Statics::NewProp_ContentHash = { "ContentHash", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportInfo, ContentHash), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ContentHash_MetaData), NewProp_ContentHash_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportInfo_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportInfo_Statics::NewProp_SchemaVersion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportInfo_Statics::NewProp_EngineVersion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportInfo_Statics::NewProp_PluginVersion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportInfo_Statics::NewProp_ExportTimestamp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportInfo_Statics::NewProp_ContentHash,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportInfo_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportInfo Property Definitions ************************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportInfo_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportInfo",
	Z_Construct_UScriptStruct_FExportInfo_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportInfo_Statics::PropPointers),
	sizeof(FExportInfo),
	alignof(FExportInfo),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportInfo_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportInfo_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportInfo()
{
	if (!Z_Registration_Info_UScriptStruct_FExportInfo.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportInfo.InnerSingleton, Z_Construct_UScriptStruct_FExportInfo_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportInfo.InnerSingleton);
}
// ********** End ScriptStruct FExportInfo *********************************************************

// ********** Begin ScriptStruct FExportedTransitionBlendSettings **********************************
struct Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedTransitionBlendSettings); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedTransitionBlendSettings); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Transition blend settings for AnimBP state machine transitions\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Transition blend settings for AnimBP state machine transitions" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CrossfadeDuration_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Crossfade duration in seconds */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Crossfade duration in seconds" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BlendMode_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blend mode (EAlphaBlendOption as string, e.g., \"Linear\", \"Cubic\", \"HermiteCubic\") */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blend mode (EAlphaBlendOption as string, e.g., \"Linear\", \"Cubic\", \"HermiteCubic\")" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CrossfadeMode_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Crossfade mode (ETransitionBlendMode as string, e.g., \"BlendDuration\", \"Proportional\") */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Crossfade mode (ETransitionBlendMode as string, e.g., \"BlendDuration\", \"Proportional\")" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LogicType_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Logic type (ETransitionLogicType as string, e.g., \"StandardBlend\", \"Inertialization\", \"Custom\") */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Logic type (ETransitionLogicType as string, e.g., \"StandardBlend\", \"Inertialization\", \"Custom\")" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PriorityOrder_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Priority order for multiple transitions from same state */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Priority order for multiple transitions from same state" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAutomaticRuleBasedOnSequencePlayer_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether transition uses automatic rule based on sequence player */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether transition uses automatic rule based on sequence player" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedTransitionBlendSettings constinit property declarations **
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CrossfadeDuration;
	static const UECodeGen_Private::FStrPropertyParams NewProp_BlendMode;
	static const UECodeGen_Private::FStrPropertyParams NewProp_CrossfadeMode;
	static const UECodeGen_Private::FStrPropertyParams NewProp_LogicType;
	static const UECodeGen_Private::FIntPropertyParams NewProp_PriorityOrder;
	static void NewProp_bAutomaticRuleBasedOnSequencePlayer_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutomaticRuleBasedOnSequencePlayer;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedTransitionBlendSettings constinit property declarations ****
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedTransitionBlendSettings>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedTransitionBlendSettings;
class UScriptStruct* FExportedTransitionBlendSettings::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedTransitionBlendSettings.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedTransitionBlendSettings.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedTransitionBlendSettings, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedTransitionBlendSettings"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedTransitionBlendSettings.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedTransitionBlendSettings Property Definitions *************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::NewProp_CrossfadeDuration = { "CrossfadeDuration", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedTransitionBlendSettings, CrossfadeDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CrossfadeDuration_MetaData), NewProp_CrossfadeDuration_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::NewProp_BlendMode = { "BlendMode", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedTransitionBlendSettings, BlendMode), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BlendMode_MetaData), NewProp_BlendMode_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::NewProp_CrossfadeMode = { "CrossfadeMode", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedTransitionBlendSettings, CrossfadeMode), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CrossfadeMode_MetaData), NewProp_CrossfadeMode_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::NewProp_LogicType = { "LogicType", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedTransitionBlendSettings, LogicType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LogicType_MetaData), NewProp_LogicType_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::NewProp_PriorityOrder = { "PriorityOrder", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedTransitionBlendSettings, PriorityOrder), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PriorityOrder_MetaData), NewProp_PriorityOrder_MetaData) };
void Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::NewProp_bAutomaticRuleBasedOnSequencePlayer_SetBit(void* Obj)
{
	((FExportedTransitionBlendSettings*)Obj)->bAutomaticRuleBasedOnSequencePlayer = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::NewProp_bAutomaticRuleBasedOnSequencePlayer = { "bAutomaticRuleBasedOnSequencePlayer", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedTransitionBlendSettings), &Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::NewProp_bAutomaticRuleBasedOnSequencePlayer_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAutomaticRuleBasedOnSequencePlayer_MetaData), NewProp_bAutomaticRuleBasedOnSequencePlayer_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::NewProp_CrossfadeDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::NewProp_BlendMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::NewProp_CrossfadeMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::NewProp_LogicType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::NewProp_PriorityOrder,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::NewProp_bAutomaticRuleBasedOnSequencePlayer,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedTransitionBlendSettings Property Definitions ***************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedTransitionBlendSettings",
	Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::PropPointers),
	sizeof(FExportedTransitionBlendSettings),
	alignof(FExportedTransitionBlendSettings),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedTransitionBlendSettings()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedTransitionBlendSettings.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedTransitionBlendSettings.InnerSingleton, Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedTransitionBlendSettings.InnerSingleton);
}
// ********** End ScriptStruct FExportedTransitionBlendSettings ************************************

// ********** Begin ScriptStruct FExportedAnimState ************************************************
struct Z_Construct_UScriptStruct_FExportedAnimState_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedAnimState); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedAnimState); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Exported animation state within an AnimBP state machine\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Exported animation state within an AnimBP state machine" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StateName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StateGuid_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StateType_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** State type: \"State\", \"Conduit\", or \"Entry\" */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "State type: \"State\", \"Conduit\", or \"Entry\"" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AnimGraph_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedAnimState constinit property declarations ****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_StateName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_StateGuid;
	static const UECodeGen_Private::FStrPropertyParams NewProp_StateType;
	static const UECodeGen_Private::FStructPropertyParams NewProp_AnimGraph;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedAnimState constinit property declarations ******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedAnimState>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedAnimState_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedAnimState;
class UScriptStruct* FExportedAnimState::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedAnimState.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedAnimState.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedAnimState, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedAnimState"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedAnimState.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedAnimState Property Definitions ***************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedAnimState_Statics::NewProp_StateName = { "StateName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedAnimState, StateName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StateName_MetaData), NewProp_StateName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedAnimState_Statics::NewProp_StateGuid = { "StateGuid", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedAnimState, StateGuid), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StateGuid_MetaData), NewProp_StateGuid_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedAnimState_Statics::NewProp_StateType = { "StateType", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedAnimState, StateType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StateType_MetaData), NewProp_StateType_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedAnimState_Statics::NewProp_AnimGraph = { "AnimGraph", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedAnimState, AnimGraph), Z_Construct_UScriptStruct_FExportedGraph, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AnimGraph_MetaData), NewProp_AnimGraph_MetaData) }; // 193825846
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedAnimState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedAnimState_Statics::NewProp_StateName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedAnimState_Statics::NewProp_StateGuid,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedAnimState_Statics::NewProp_StateType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedAnimState_Statics::NewProp_AnimGraph,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedAnimState_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedAnimState Property Definitions *****************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedAnimState_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedAnimState",
	Z_Construct_UScriptStruct_FExportedAnimState_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedAnimState_Statics::PropPointers),
	sizeof(FExportedAnimState),
	alignof(FExportedAnimState),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedAnimState_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedAnimState_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedAnimState()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedAnimState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedAnimState.InnerSingleton, Z_Construct_UScriptStruct_FExportedAnimState_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedAnimState.InnerSingleton);
}
// ********** End ScriptStruct FExportedAnimState **************************************************

// ********** Begin ScriptStruct FExportedAnimTransition *******************************************
struct Z_Construct_UScriptStruct_FExportedAnimTransition_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedAnimTransition); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedAnimTransition); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Exported animation transition within an AnimBP state machine\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Exported animation transition within an AnimBP state machine" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TransitionName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TransitionGuid_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceState_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetState_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RuleGraph_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BlendSettings_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedAnimTransition constinit property declarations ***********
	static const UECodeGen_Private::FStrPropertyParams NewProp_TransitionName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_TransitionGuid;
	static const UECodeGen_Private::FStrPropertyParams NewProp_SourceState;
	static const UECodeGen_Private::FStrPropertyParams NewProp_TargetState;
	static const UECodeGen_Private::FStructPropertyParams NewProp_RuleGraph;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BlendSettings;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedAnimTransition constinit property declarations *************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedAnimTransition>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedAnimTransition_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedAnimTransition;
class UScriptStruct* FExportedAnimTransition::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedAnimTransition.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedAnimTransition.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedAnimTransition, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedAnimTransition"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedAnimTransition.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedAnimTransition Property Definitions **********************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::NewProp_TransitionName = { "TransitionName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedAnimTransition, TransitionName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TransitionName_MetaData), NewProp_TransitionName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::NewProp_TransitionGuid = { "TransitionGuid", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedAnimTransition, TransitionGuid), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TransitionGuid_MetaData), NewProp_TransitionGuid_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::NewProp_SourceState = { "SourceState", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedAnimTransition, SourceState), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceState_MetaData), NewProp_SourceState_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::NewProp_TargetState = { "TargetState", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedAnimTransition, TargetState), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetState_MetaData), NewProp_TargetState_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::NewProp_RuleGraph = { "RuleGraph", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedAnimTransition, RuleGraph), Z_Construct_UScriptStruct_FExportedGraph, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RuleGraph_MetaData), NewProp_RuleGraph_MetaData) }; // 193825846
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::NewProp_BlendSettings = { "BlendSettings", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedAnimTransition, BlendSettings), Z_Construct_UScriptStruct_FExportedTransitionBlendSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BlendSettings_MetaData), NewProp_BlendSettings_MetaData) }; // 2024514486
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::NewProp_TransitionName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::NewProp_TransitionGuid,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::NewProp_SourceState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::NewProp_TargetState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::NewProp_RuleGraph,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::NewProp_BlendSettings,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedAnimTransition Property Definitions ************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedAnimTransition",
	Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::PropPointers),
	sizeof(FExportedAnimTransition),
	alignof(FExportedAnimTransition),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedAnimTransition()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedAnimTransition.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedAnimTransition.InnerSingleton, Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedAnimTransition.InnerSingleton);
}
// ********** End ScriptStruct FExportedAnimTransition *********************************************

// ********** Begin ScriptStruct FExportedStateMachine *********************************************
struct Z_Construct_UScriptStruct_FExportedStateMachine_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedStateMachine); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedStateMachine); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Exported AnimBP state machine (contains states and transitions)\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Exported AnimBP state machine (contains states and transitions)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MachineName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MachineGuid_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedStateMachine constinit property declarations *************
	static const UECodeGen_Private::FStrPropertyParams NewProp_MachineName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MachineGuid;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedStateMachine constinit property declarations ***************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedStateMachine>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedStateMachine_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedStateMachine;
class UScriptStruct* FExportedStateMachine::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedStateMachine.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedStateMachine.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedStateMachine, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedStateMachine"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedStateMachine.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedStateMachine Property Definitions ************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedStateMachine_Statics::NewProp_MachineName = { "MachineName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedStateMachine, MachineName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MachineName_MetaData), NewProp_MachineName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedStateMachine_Statics::NewProp_MachineGuid = { "MachineGuid", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedStateMachine, MachineGuid), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MachineGuid_MetaData), NewProp_MachineGuid_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedStateMachine_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedStateMachine_Statics::NewProp_MachineName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedStateMachine_Statics::NewProp_MachineGuid,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedStateMachine_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedStateMachine Property Definitions **************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedStateMachine_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedStateMachine",
	Z_Construct_UScriptStruct_FExportedStateMachine_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedStateMachine_Statics::PropPointers),
	sizeof(FExportedStateMachine),
	alignof(FExportedStateMachine),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedStateMachine_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedStateMachine_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedStateMachine()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedStateMachine.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedStateMachine.InnerSingleton, Z_Construct_UScriptStruct_FExportedStateMachine_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedStateMachine.InnerSingleton);
}
// ********** End ScriptStruct FExportedStateMachine ***********************************************

// ********** Begin ScriptStruct FExportedWidgetNode ***********************************************
struct Z_Construct_UScriptStruct_FExportedWidgetNode_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedWidgetNode); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedWidgetNode); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Exported UMG widget tree node.\n *\n * Captures a single node in a WidgetBlueprint's widget hierarchy \xe2\x80\x94 the\n * root UWidget of `UBaseWidgetBlueprint::WidgetTree` and each recursive\n * descendant via `UPanelWidget::GetChildAt`. Authored child order is\n * preserved (slot order is semantically load-bearing in UMG layout).\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Exported UMG widget tree node.\n\nCaptures a single node in a WidgetBlueprint's widget hierarchy \xe2\x80\x94 the\nroot UWidget of `UBaseWidgetBlueprint::WidgetTree` and each recursive\ndescendant via `UPanelWidget::GetChildAt`. Authored child order is\npreserved (slot order is semantically load-bearing in UMG layout)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WidgetName_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Widget's UObject name (matches the variable name when promoted). */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Widget's UObject name (matches the variable name when promoted)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WidgetClass_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Full class path of the UWidget subclass (e.g., \"/Script/UMG.HorizontalBox\"). */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Full class path of the UWidget subclass (e.g., \"/Script/UMG.HorizontalBox\")." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsVariable_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** True when the widget is exposed as a Blueprint variable (bIsVariable / BindWidget). */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "True when the widget is exposed as a Blueprint variable (bIsVariable / BindWidget)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SlotClass_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Slot struct class path (e.g., \"/Script/UMG.HorizontalBoxSlot\"). Empty for the root. */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Slot struct class path (e.g., \"/Script/UMG.HorizontalBoxSlot\"). Empty for the root." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedWidgetNode constinit property declarations ***************
	static const UECodeGen_Private::FStrPropertyParams NewProp_WidgetName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_WidgetClass;
	static void NewProp_bIsVariable_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsVariable;
	static const UECodeGen_Private::FStrPropertyParams NewProp_SlotClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedWidgetNode constinit property declarations *****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedWidgetNode>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedWidgetNode_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedWidgetNode;
class UScriptStruct* FExportedWidgetNode::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedWidgetNode.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedWidgetNode.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedWidgetNode, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedWidgetNode"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedWidgetNode.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedWidgetNode Property Definitions **************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedWidgetNode_Statics::NewProp_WidgetName = { "WidgetName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedWidgetNode, WidgetName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WidgetName_MetaData), NewProp_WidgetName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedWidgetNode_Statics::NewProp_WidgetClass = { "WidgetClass", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedWidgetNode, WidgetClass), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WidgetClass_MetaData), NewProp_WidgetClass_MetaData) };
void Z_Construct_UScriptStruct_FExportedWidgetNode_Statics::NewProp_bIsVariable_SetBit(void* Obj)
{
	((FExportedWidgetNode*)Obj)->bIsVariable = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FExportedWidgetNode_Statics::NewProp_bIsVariable = { "bIsVariable", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FExportedWidgetNode), &Z_Construct_UScriptStruct_FExportedWidgetNode_Statics::NewProp_bIsVariable_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsVariable_MetaData), NewProp_bIsVariable_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedWidgetNode_Statics::NewProp_SlotClass = { "SlotClass", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedWidgetNode, SlotClass), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SlotClass_MetaData), NewProp_SlotClass_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedWidgetNode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedWidgetNode_Statics::NewProp_WidgetName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedWidgetNode_Statics::NewProp_WidgetClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedWidgetNode_Statics::NewProp_bIsVariable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedWidgetNode_Statics::NewProp_SlotClass,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedWidgetNode_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedWidgetNode Property Definitions ****************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedWidgetNode_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedWidgetNode",
	Z_Construct_UScriptStruct_FExportedWidgetNode_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedWidgetNode_Statics::PropPointers),
	sizeof(FExportedWidgetNode),
	alignof(FExportedWidgetNode),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedWidgetNode_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedWidgetNode_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedWidgetNode()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedWidgetNode.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedWidgetNode.InnerSingleton, Z_Construct_UScriptStruct_FExportedWidgetNode_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedWidgetNode.InnerSingleton);
}
// ********** End ScriptStruct FExportedWidgetNode *************************************************

// ********** Begin ScriptStruct FExportedBlueprint ************************************************
struct Z_Construct_UScriptStruct_FExportedBlueprint_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportedBlueprint); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportedBlueprint); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Complete exported Blueprint data\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Complete exported Blueprint data" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExportInfo_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AssetPath_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AssetName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BlueprintGuid_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BlueprintType_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BlueprintSubclass_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Native UObject subclass name (e.g., \"AnimBlueprint\", \"WidgetBlueprint\", \"Blueprint\").\n\x09 *  Detected via UE reflection, always populated, never empty. */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Native UObject subclass name (e.g., \"AnimBlueprint\", \"WidgetBlueprint\", \"Blueprint\").\nDetected via UE reflection, always populated, never empty." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParentClass_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ImplementedInterfaces_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Variables_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Functions_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Macros_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EventGraph_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ConstructionScript_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Components_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CDOProperties_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Class Default Object properties \xe2\x80\x94 authored Details-panel values on the generated\n\x09 *  class's CDO that aren't captured by Variables (which serializes the declared\n\x09 *  fields) or Components (SCS hierarchy). Populated only for properties inherited\n\x09 *  from the parent class chain and diffed against the parent CDO, so entries are\n\x09 *  strictly authored overrides on top of parent defaults.\n\x09 *\n\x09 *  Critical for data-carrier Blueprints: `GameplayEffect` subclasses store their\n\x09 *  `Modifiers` / `DurationPolicy` / GameplayCue list here; `GameplayAbility` subclasses\n\x09 *  store `AbilityTags` / `CostGameplayEffectClass`; `DataAsset` subclasses store the\n\x09 *  authored payload properties. Regular BPs use this for Actor-level overrides like\n\x09 *  `bReplicates` / `NetUpdateFrequency` that live on the CDO.\n\x09 *\n\x09 *  Instanced / EditInlineNew subobject fields (e.g. GE modifier components,\n\x09 *  AbilitySystemComponent attribute sets) surface through the same M9\n\x09 *  `bIsInstancedSubobject` + `SubobjectJsonValues` recursive tree the component\n\x09 *  walker uses. */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Class Default Object properties \xe2\x80\x94 authored Details-panel values on the generated\nclass's CDO that aren't captured by Variables (which serializes the declared\nfields) or Components (SCS hierarchy). Populated only for properties inherited\nfrom the parent class chain and diffed against the parent CDO, so entries are\nstrictly authored overrides on top of parent defaults.\n\nCritical for data-carrier Blueprints: `GameplayEffect` subclasses store their\n`Modifiers` / `DurationPolicy` / GameplayCue list here; `GameplayAbility` subclasses\nstore `AbilityTags` / `CostGameplayEffectClass`; `DataAsset` subclasses store the\nauthored payload properties. Regular BPs use this for Actor-level overrides like\n`bReplicates` / `NetUpdateFrequency` that live on the CDO.\n\nInstanced / EditInlineNew subobject fields (e.g. GE modifier components,\nAbilitySystemComponent attribute sets) surface through the same M9\n`bIsInstancedSubobject` + `SubobjectJsonValues` recursive tree the component\nwalker uses." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DataCarrierKind_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Data-carrier kind discriminator \xe2\x80\x94 `GameplayEffect` / `GameplayAbility` / `DataAsset`\n\x09 *  when `GeneratedClass->IsChildOf` the corresponding base; empty otherwise. Computed\n\x09 *  at serialize time because `FExportedBlueprint` consumers (inventory commandlet,\n\x09 *  HEALTH_REPORT) don't carry live UClass handles. Used to emit specialized-section\n\x09 *  applicable markers (`GameplayEffect.CDO` etc.) so HEALTH_REPORT can flag a\n\x09 *  data-carrier BP whose CDO walk produced no authored overrides. */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Data-carrier kind discriminator \xe2\x80\x94 `GameplayEffect` / `GameplayAbility` / `DataAsset`\nwhen `GeneratedClass->IsChildOf` the corresponding base; empty otherwise. Computed\nat serialize time because `FExportedBlueprint` consumers (inventory commandlet,\nHEALTH_REPORT) don't carry live UClass handles. Used to emit specialized-section\napplicable markers (`GameplayEffect.CDO` etc.) so HEALTH_REPORT can flag a\ndata-carrier BP whose CDO walk produced no authored overrides." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AdditionalGraphs_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Dependencies_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MetaData_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportedBlueprint constinit property declarations ****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ExportInfo;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AssetPath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AssetName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_BlueprintGuid;
	static const UECodeGen_Private::FBytePropertyParams NewProp_BlueprintType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_BlueprintType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_BlueprintSubclass;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ParentClass;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ImplementedInterfaces_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ImplementedInterfaces;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Variables_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Variables;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Functions_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Functions;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Macros_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Macros;
	static const UECodeGen_Private::FStructPropertyParams NewProp_EventGraph;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ConstructionScript;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Components_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Components;
	static const UECodeGen_Private::FStructPropertyParams NewProp_CDOProperties_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_CDOProperties;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DataCarrierKind;
	static const UECodeGen_Private::FStructPropertyParams NewProp_AdditionalGraphs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_AdditionalGraphs;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Dependencies_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Dependencies;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MetaData_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MetaData_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_MetaData;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportedBlueprint constinit property declarations ******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportedBlueprint>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportedBlueprint_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportedBlueprint;
class UScriptStruct* FExportedBlueprint::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedBlueprint.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportedBlueprint.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportedBlueprint, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportedBlueprint"));
	}
	return Z_Registration_Info_UScriptStruct_FExportedBlueprint.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportedBlueprint Property Definitions ***************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_ExportInfo = { "ExportInfo", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedBlueprint, ExportInfo), Z_Construct_UScriptStruct_FExportInfo, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExportInfo_MetaData), NewProp_ExportInfo_MetaData) }; // 2393131268
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_AssetPath = { "AssetPath", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedBlueprint, AssetPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AssetPath_MetaData), NewProp_AssetPath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_AssetName = { "AssetName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedBlueprint, AssetName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AssetName_MetaData), NewProp_AssetName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_BlueprintGuid = { "BlueprintGuid", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedBlueprint, BlueprintGuid), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BlueprintGuid_MetaData), NewProp_BlueprintGuid_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_BlueprintType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_BlueprintType = { "BlueprintType", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedBlueprint, BlueprintType), Z_Construct_UEnum_BlueprintExporter_EBlueprintExportType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BlueprintType_MetaData), NewProp_BlueprintType_MetaData) }; // 130912469
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_BlueprintSubclass = { "BlueprintSubclass", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedBlueprint, BlueprintSubclass), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BlueprintSubclass_MetaData), NewProp_BlueprintSubclass_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_ParentClass = { "ParentClass", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedBlueprint, ParentClass), Z_Construct_UScriptStruct_FExportedParentClass, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParentClass_MetaData), NewProp_ParentClass_MetaData) }; // 413471149
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_ImplementedInterfaces_Inner = { "ImplementedInterfaces", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_ImplementedInterfaces = { "ImplementedInterfaces", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedBlueprint, ImplementedInterfaces), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ImplementedInterfaces_MetaData), NewProp_ImplementedInterfaces_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Variables_Inner = { "Variables", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FExportedVariable, METADATA_PARAMS(0, nullptr) }; // 1626092749
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Variables = { "Variables", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedBlueprint, Variables), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Variables_MetaData), NewProp_Variables_MetaData) }; // 1626092749
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Functions_Inner = { "Functions", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FExportedFunction, METADATA_PARAMS(0, nullptr) }; // 4096331461
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Functions = { "Functions", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedBlueprint, Functions), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Functions_MetaData), NewProp_Functions_MetaData) }; // 4096331461
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Macros_Inner = { "Macros", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FExportedFunction, METADATA_PARAMS(0, nullptr) }; // 4096331461
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Macros = { "Macros", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedBlueprint, Macros), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Macros_MetaData), NewProp_Macros_MetaData) }; // 4096331461
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_EventGraph = { "EventGraph", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedBlueprint, EventGraph), Z_Construct_UScriptStruct_FExportedGraph, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EventGraph_MetaData), NewProp_EventGraph_MetaData) }; // 193825846
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_ConstructionScript = { "ConstructionScript", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedBlueprint, ConstructionScript), Z_Construct_UScriptStruct_FExportedGraph, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ConstructionScript_MetaData), NewProp_ConstructionScript_MetaData) }; // 193825846
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Components_Inner = { "Components", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FExportedComponent, METADATA_PARAMS(0, nullptr) }; // 817091047
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Components = { "Components", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedBlueprint, Components), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Components_MetaData), NewProp_Components_MetaData) }; // 817091047
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_CDOProperties_Inner = { "CDOProperties", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FExportedComponentProperty, METADATA_PARAMS(0, nullptr) }; // 3006916080
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_CDOProperties = { "CDOProperties", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedBlueprint, CDOProperties), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CDOProperties_MetaData), NewProp_CDOProperties_MetaData) }; // 3006916080
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_DataCarrierKind = { "DataCarrierKind", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedBlueprint, DataCarrierKind), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DataCarrierKind_MetaData), NewProp_DataCarrierKind_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_AdditionalGraphs_Inner = { "AdditionalGraphs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FExportedGraph, METADATA_PARAMS(0, nullptr) }; // 193825846
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_AdditionalGraphs = { "AdditionalGraphs", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedBlueprint, AdditionalGraphs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AdditionalGraphs_MetaData), NewProp_AdditionalGraphs_MetaData) }; // 193825846
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Dependencies_Inner = { "Dependencies", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FExportedDependency, METADATA_PARAMS(0, nullptr) }; // 2115202204
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Dependencies = { "Dependencies", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedBlueprint, Dependencies), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Dependencies_MetaData), NewProp_Dependencies_MetaData) }; // 2115202204
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_MetaData_ValueProp = { "MetaData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_MetaData_Key_KeyProp = { "MetaData_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_MetaData = { "MetaData", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportedBlueprint, MetaData), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MetaData_MetaData), NewProp_MetaData_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportedBlueprint_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_ExportInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_AssetPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_AssetName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_BlueprintGuid,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_BlueprintType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_BlueprintType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_BlueprintSubclass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_ParentClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_ImplementedInterfaces_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_ImplementedInterfaces,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Variables_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Variables,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Functions_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Functions,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Macros_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Macros,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_EventGraph,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_ConstructionScript,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Components_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Components,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_CDOProperties_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_CDOProperties,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_DataCarrierKind,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_AdditionalGraphs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_AdditionalGraphs,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Dependencies_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_Dependencies,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_MetaData_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_MetaData_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewProp_MetaData,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedBlueprint_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportedBlueprint Property Definitions *****************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportedBlueprint_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportedBlueprint",
	Z_Construct_UScriptStruct_FExportedBlueprint_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedBlueprint_Statics::PropPointers),
	sizeof(FExportedBlueprint),
	alignof(FExportedBlueprint),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportedBlueprint_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportedBlueprint_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportedBlueprint()
{
	if (!Z_Registration_Info_UScriptStruct_FExportedBlueprint.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportedBlueprint.InnerSingleton, Z_Construct_UScriptStruct_FExportedBlueprint_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportedBlueprint.InnerSingleton);
}
// ********** End ScriptStruct FExportedBlueprint **************************************************

// ********** Begin ScriptStruct FExportManifestEntry **********************************************
struct Z_Construct_UScriptStruct_FExportManifestEntry_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportManifestEntry); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportManifestEntry); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Manifest entry for a single exported Blueprint\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Manifest entry for a single exported Blueprint" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AssetPath_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AssetName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExportFileName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ContentHash_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AssetType_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Asset type discriminator: \"Blueprint\" or \"StateTree\" */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Asset type discriminator: \"Blueprint\" or \"StateTree\"" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BlueprintSubclass_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Native Blueprint subclass for filtering (e.g., \"AnimBlueprint\"). Empty for non-Blueprint assets. */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Native Blueprint subclass for filtering (e.g., \"AnimBlueprint\"). Empty for non-Blueprint assets." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NodeCount_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FunctionCount_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComplexityScore_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportManifestEntry constinit property declarations **************
	static const UECodeGen_Private::FStrPropertyParams NewProp_AssetPath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AssetName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ExportFileName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ContentHash;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AssetType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_BlueprintSubclass;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NodeCount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_FunctionCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ComplexityScore;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportManifestEntry constinit property declarations ****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportManifestEntry>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportManifestEntry_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportManifestEntry;
class UScriptStruct* FExportManifestEntry::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportManifestEntry.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportManifestEntry.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportManifestEntry, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportManifestEntry"));
	}
	return Z_Registration_Info_UScriptStruct_FExportManifestEntry.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportManifestEntry Property Definitions *************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportManifestEntry_Statics::NewProp_AssetPath = { "AssetPath", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportManifestEntry, AssetPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AssetPath_MetaData), NewProp_AssetPath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportManifestEntry_Statics::NewProp_AssetName = { "AssetName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportManifestEntry, AssetName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AssetName_MetaData), NewProp_AssetName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportManifestEntry_Statics::NewProp_ExportFileName = { "ExportFileName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportManifestEntry, ExportFileName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExportFileName_MetaData), NewProp_ExportFileName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportManifestEntry_Statics::NewProp_ContentHash = { "ContentHash", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportManifestEntry, ContentHash), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ContentHash_MetaData), NewProp_ContentHash_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportManifestEntry_Statics::NewProp_AssetType = { "AssetType", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportManifestEntry, AssetType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AssetType_MetaData), NewProp_AssetType_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportManifestEntry_Statics::NewProp_BlueprintSubclass = { "BlueprintSubclass", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportManifestEntry, BlueprintSubclass), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BlueprintSubclass_MetaData), NewProp_BlueprintSubclass_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FExportManifestEntry_Statics::NewProp_NodeCount = { "NodeCount", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportManifestEntry, NodeCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NodeCount_MetaData), NewProp_NodeCount_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FExportManifestEntry_Statics::NewProp_FunctionCount = { "FunctionCount", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportManifestEntry, FunctionCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FunctionCount_MetaData), NewProp_FunctionCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FExportManifestEntry_Statics::NewProp_ComplexityScore = { "ComplexityScore", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportManifestEntry, ComplexityScore), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComplexityScore_MetaData), NewProp_ComplexityScore_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportManifestEntry_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportManifestEntry_Statics::NewProp_AssetPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportManifestEntry_Statics::NewProp_AssetName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportManifestEntry_Statics::NewProp_ExportFileName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportManifestEntry_Statics::NewProp_ContentHash,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportManifestEntry_Statics::NewProp_AssetType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportManifestEntry_Statics::NewProp_BlueprintSubclass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportManifestEntry_Statics::NewProp_NodeCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportManifestEntry_Statics::NewProp_FunctionCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportManifestEntry_Statics::NewProp_ComplexityScore,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportManifestEntry_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportManifestEntry Property Definitions ***************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportManifestEntry_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportManifestEntry",
	Z_Construct_UScriptStruct_FExportManifestEntry_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportManifestEntry_Statics::PropPointers),
	sizeof(FExportManifestEntry),
	alignof(FExportManifestEntry),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportManifestEntry_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportManifestEntry_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportManifestEntry()
{
	if (!Z_Registration_Info_UScriptStruct_FExportManifestEntry.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportManifestEntry.InnerSingleton, Z_Construct_UScriptStruct_FExportManifestEntry_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportManifestEntry.InnerSingleton);
}
// ********** End ScriptStruct FExportManifestEntry ************************************************

// ********** Begin ScriptStruct FExportManifest ***************************************************
struct Z_Construct_UScriptStruct_FExportManifest_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExportManifest); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExportManifest); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Export manifest containing all exported Blueprints\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Export manifest containing all exported Blueprints" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SchemaVersion_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EngineVersion_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PluginVersion_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExportTimestamp_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Entries_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExportConfig_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExportManifest constinit property declarations *******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_SchemaVersion;
	static const UECodeGen_Private::FStrPropertyParams NewProp_EngineVersion;
	static const UECodeGen_Private::FStrPropertyParams NewProp_PluginVersion;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ExportTimestamp;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Entries_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Entries;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ExportConfig_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ExportConfig_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_ExportConfig;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExportManifest constinit property declarations *********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExportManifest>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExportManifest_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExportManifest;
class UScriptStruct* FExportManifest::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExportManifest.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExportManifest.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExportManifest, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("ExportManifest"));
	}
	return Z_Registration_Info_UScriptStruct_FExportManifest.OuterSingleton;
	}

// ********** Begin ScriptStruct FExportManifest Property Definitions ******************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportManifest_Statics::NewProp_SchemaVersion = { "SchemaVersion", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportManifest, SchemaVersion), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SchemaVersion_MetaData), NewProp_SchemaVersion_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportManifest_Statics::NewProp_EngineVersion = { "EngineVersion", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportManifest, EngineVersion), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EngineVersion_MetaData), NewProp_EngineVersion_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportManifest_Statics::NewProp_PluginVersion = { "PluginVersion", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportManifest, PluginVersion), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PluginVersion_MetaData), NewProp_PluginVersion_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportManifest_Statics::NewProp_ExportTimestamp = { "ExportTimestamp", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportManifest, ExportTimestamp), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExportTimestamp_MetaData), NewProp_ExportTimestamp_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FExportManifest_Statics::NewProp_Entries_Inner = { "Entries", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FExportManifestEntry, METADATA_PARAMS(0, nullptr) }; // 2800868016
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FExportManifest_Statics::NewProp_Entries = { "Entries", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportManifest, Entries), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Entries_MetaData), NewProp_Entries_MetaData) }; // 2800868016
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportManifest_Statics::NewProp_ExportConfig_ValueProp = { "ExportConfig", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExportManifest_Statics::NewProp_ExportConfig_Key_KeyProp = { "ExportConfig_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FExportManifest_Statics::NewProp_ExportConfig = { "ExportConfig", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExportManifest, ExportConfig), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExportConfig_MetaData), NewProp_ExportConfig_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExportManifest_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportManifest_Statics::NewProp_SchemaVersion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportManifest_Statics::NewProp_EngineVersion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportManifest_Statics::NewProp_PluginVersion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportManifest_Statics::NewProp_ExportTimestamp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportManifest_Statics::NewProp_Entries_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportManifest_Statics::NewProp_Entries,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportManifest_Statics::NewProp_ExportConfig_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportManifest_Statics::NewProp_ExportConfig_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExportManifest_Statics::NewProp_ExportConfig,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportManifest_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExportManifest Property Definitions ********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExportManifest_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"ExportManifest",
	Z_Construct_UScriptStruct_FExportManifest_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportManifest_Statics::PropPointers),
	sizeof(FExportManifest),
	alignof(FExportManifest),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExportManifest_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExportManifest_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExportManifest()
{
	if (!Z_Registration_Info_UScriptStruct_FExportManifest.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExportManifest.InnerSingleton, Z_Construct_UScriptStruct_FExportManifest_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExportManifest.InnerSingleton);
}
// ********** End ScriptStruct FExportManifest *****************************************************

// ********** Begin ScriptStruct FBlueprintDiffChange **********************************************
struct Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FBlueprintDiffChange); }
	static inline consteval int16 GetStructAlignment() { return alignof(FBlueprintDiffChange); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Diff change entry\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Diff change entry" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChangeType_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Category_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ElementPath_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ElementName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OldValue_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewValue_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FBlueprintDiffChange constinit property declarations **************
	static const UECodeGen_Private::FBytePropertyParams NewProp_ChangeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ChangeType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Category;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ElementPath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ElementName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OldValue;
	static const UECodeGen_Private::FStrPropertyParams NewProp_NewValue;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Description;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FBlueprintDiffChange constinit property declarations ****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBlueprintDiffChange>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBlueprintDiffChange;
class UScriptStruct* FBlueprintDiffChange::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBlueprintDiffChange.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBlueprintDiffChange.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBlueprintDiffChange, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("BlueprintDiffChange"));
	}
	return Z_Registration_Info_UScriptStruct_FBlueprintDiffChange.OuterSingleton;
	}

// ********** Begin ScriptStruct FBlueprintDiffChange Property Definitions *************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::NewProp_ChangeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::NewProp_ChangeType = { "ChangeType", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintDiffChange, ChangeType), Z_Construct_UEnum_BlueprintExporter_EBlueprintDiffChangeType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChangeType_MetaData), NewProp_ChangeType_MetaData) }; // 1858970996
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintDiffChange, Category), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Category_MetaData), NewProp_Category_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::NewProp_ElementPath = { "ElementPath", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintDiffChange, ElementPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ElementPath_MetaData), NewProp_ElementPath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::NewProp_ElementName = { "ElementName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintDiffChange, ElementName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ElementName_MetaData), NewProp_ElementName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::NewProp_OldValue = { "OldValue", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintDiffChange, OldValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OldValue_MetaData), NewProp_OldValue_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::NewProp_NewValue = { "NewValue", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintDiffChange, NewValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewValue_MetaData), NewProp_NewValue_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintDiffChange, Description), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Description_MetaData), NewProp_Description_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::NewProp_ChangeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::NewProp_ChangeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::NewProp_Category,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::NewProp_ElementPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::NewProp_ElementName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::NewProp_OldValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::NewProp_NewValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::NewProp_Description,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FBlueprintDiffChange Property Definitions ***************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"BlueprintDiffChange",
	Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::PropPointers),
	sizeof(FBlueprintDiffChange),
	alignof(FBlueprintDiffChange),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBlueprintDiffChange()
{
	if (!Z_Registration_Info_UScriptStruct_FBlueprintDiffChange.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBlueprintDiffChange.InnerSingleton, Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FBlueprintDiffChange.InnerSingleton);
}
// ********** End ScriptStruct FBlueprintDiffChange ************************************************

// ********** Begin ScriptStruct FBlueprintDiffResult **********************************************
struct Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FBlueprintDiffResult); }
	static inline consteval int16 GetStructAlignment() { return alignof(FBlueprintDiffResult); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Complete diff result between two Blueprints\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Complete diff result between two Blueprints" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourcePath_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetPath_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bHasChanges_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NodesAdded_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NodesRemoved_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NodesModified_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ConnectionsChanged_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VariablesChanged_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FunctionsChanged_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LayoutChanges_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Changes_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FBlueprintDiffResult constinit property declarations **************
	static const UECodeGen_Private::FStrPropertyParams NewProp_SourcePath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_TargetPath;
	static void NewProp_bHasChanges_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bHasChanges;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NodesAdded;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NodesRemoved;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NodesModified;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ConnectionsChanged;
	static const UECodeGen_Private::FIntPropertyParams NewProp_VariablesChanged;
	static const UECodeGen_Private::FIntPropertyParams NewProp_FunctionsChanged;
	static const UECodeGen_Private::FIntPropertyParams NewProp_LayoutChanges;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Changes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Changes;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FBlueprintDiffResult constinit property declarations ****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBlueprintDiffResult>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBlueprintDiffResult;
class UScriptStruct* FBlueprintDiffResult::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBlueprintDiffResult.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBlueprintDiffResult.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBlueprintDiffResult, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("BlueprintDiffResult"));
	}
	return Z_Registration_Info_UScriptStruct_FBlueprintDiffResult.OuterSingleton;
	}

// ********** Begin ScriptStruct FBlueprintDiffResult Property Definitions *************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_SourcePath = { "SourcePath", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintDiffResult, SourcePath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourcePath_MetaData), NewProp_SourcePath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_TargetPath = { "TargetPath", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintDiffResult, TargetPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetPath_MetaData), NewProp_TargetPath_MetaData) };
void Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_bHasChanges_SetBit(void* Obj)
{
	((FBlueprintDiffResult*)Obj)->bHasChanges = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_bHasChanges = { "bHasChanges", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FBlueprintDiffResult), &Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_bHasChanges_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bHasChanges_MetaData), NewProp_bHasChanges_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_NodesAdded = { "NodesAdded", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintDiffResult, NodesAdded), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NodesAdded_MetaData), NewProp_NodesAdded_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_NodesRemoved = { "NodesRemoved", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintDiffResult, NodesRemoved), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NodesRemoved_MetaData), NewProp_NodesRemoved_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_NodesModified = { "NodesModified", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintDiffResult, NodesModified), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NodesModified_MetaData), NewProp_NodesModified_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_ConnectionsChanged = { "ConnectionsChanged", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintDiffResult, ConnectionsChanged), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ConnectionsChanged_MetaData), NewProp_ConnectionsChanged_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_VariablesChanged = { "VariablesChanged", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintDiffResult, VariablesChanged), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VariablesChanged_MetaData), NewProp_VariablesChanged_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_FunctionsChanged = { "FunctionsChanged", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintDiffResult, FunctionsChanged), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FunctionsChanged_MetaData), NewProp_FunctionsChanged_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_LayoutChanges = { "LayoutChanges", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintDiffResult, LayoutChanges), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LayoutChanges_MetaData), NewProp_LayoutChanges_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_Changes_Inner = { "Changes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FBlueprintDiffChange, METADATA_PARAMS(0, nullptr) }; // 3585319695
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_Changes = { "Changes", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintDiffResult, Changes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Changes_MetaData), NewProp_Changes_MetaData) }; // 3585319695
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_SourcePath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_TargetPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_bHasChanges,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_NodesAdded,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_NodesRemoved,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_NodesModified,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_ConnectionsChanged,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_VariablesChanged,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_FunctionsChanged,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_LayoutChanges,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_Changes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewProp_Changes,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FBlueprintDiffResult Property Definitions ***************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"BlueprintDiffResult",
	Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::PropPointers),
	sizeof(FBlueprintDiffResult),
	alignof(FBlueprintDiffResult),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBlueprintDiffResult()
{
	if (!Z_Registration_Info_UScriptStruct_FBlueprintDiffResult.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBlueprintDiffResult.InnerSingleton, Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FBlueprintDiffResult.InnerSingleton);
}
// ********** End ScriptStruct FBlueprintDiffResult ************************************************

// ********** Begin ScriptStruct FBlueprintExportMetrics *******************************************
struct Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FBlueprintExportMetrics); }
	static inline consteval int16 GetStructAlignment() { return alignof(FBlueprintExportMetrics); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Export metrics for CI reporting\n */" },
#endif
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Export metrics for CI reporting" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Timestamp_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TotalBlueprints_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SuccessCount_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FailureCount_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TotalExportTimeSeconds_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FailedAssets_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PerBlueprintMetrics_MetaData[] = {
		{ "ModuleRelativePath", "Public/Schema/BlueprintExportTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FBlueprintExportMetrics constinit property declarations ***********
	static const UECodeGen_Private::FStrPropertyParams NewProp_Timestamp;
	static const UECodeGen_Private::FIntPropertyParams NewProp_TotalBlueprints;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SuccessCount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_FailureCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TotalExportTimeSeconds;
	static const UECodeGen_Private::FStrPropertyParams NewProp_FailedAssets_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_FailedAssets;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PerBlueprintMetrics_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_PerBlueprintMetrics_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_PerBlueprintMetrics;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FBlueprintExportMetrics constinit property declarations *************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBlueprintExportMetrics>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBlueprintExportMetrics;
class UScriptStruct* FBlueprintExportMetrics::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBlueprintExportMetrics.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBlueprintExportMetrics.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBlueprintExportMetrics, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("BlueprintExportMetrics"));
	}
	return Z_Registration_Info_UScriptStruct_FBlueprintExportMetrics.OuterSingleton;
	}

// ********** Begin ScriptStruct FBlueprintExportMetrics Property Definitions **********************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_Timestamp = { "Timestamp", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintExportMetrics, Timestamp), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Timestamp_MetaData), NewProp_Timestamp_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_TotalBlueprints = { "TotalBlueprints", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintExportMetrics, TotalBlueprints), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TotalBlueprints_MetaData), NewProp_TotalBlueprints_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_SuccessCount = { "SuccessCount", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintExportMetrics, SuccessCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SuccessCount_MetaData), NewProp_SuccessCount_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_FailureCount = { "FailureCount", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintExportMetrics, FailureCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FailureCount_MetaData), NewProp_FailureCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_TotalExportTimeSeconds = { "TotalExportTimeSeconds", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintExportMetrics, TotalExportTimeSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TotalExportTimeSeconds_MetaData), NewProp_TotalExportTimeSeconds_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_FailedAssets_Inner = { "FailedAssets", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_FailedAssets = { "FailedAssets", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintExportMetrics, FailedAssets), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FailedAssets_MetaData), NewProp_FailedAssets_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_PerBlueprintMetrics_ValueProp = { "PerBlueprintMetrics", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_PerBlueprintMetrics_Key_KeyProp = { "PerBlueprintMetrics_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_PerBlueprintMetrics = { "PerBlueprintMetrics", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBlueprintExportMetrics, PerBlueprintMetrics), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PerBlueprintMetrics_MetaData), NewProp_PerBlueprintMetrics_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_Timestamp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_TotalBlueprints,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_SuccessCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_FailureCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_TotalExportTimeSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_FailedAssets_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_FailedAssets,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_PerBlueprintMetrics_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_PerBlueprintMetrics_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewProp_PerBlueprintMetrics,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FBlueprintExportMetrics Property Definitions ************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"BlueprintExportMetrics",
	Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::PropPointers),
	sizeof(FBlueprintExportMetrics),
	alignof(FBlueprintExportMetrics),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBlueprintExportMetrics()
{
	if (!Z_Registration_Info_UScriptStruct_FBlueprintExportMetrics.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBlueprintExportMetrics.InnerSingleton, Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FBlueprintExportMetrics.InnerSingleton);
}
// ********** End ScriptStruct FBlueprintExportMetrics *********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Schema_BlueprintExportTypes_h__Script_BlueprintExporter_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EBlueprintExportType_StaticEnum, TEXT("EBlueprintExportType"), &Z_Registration_Info_UEnum_EBlueprintExportType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 130912469U) },
		{ EExportPinDirection_StaticEnum, TEXT("EExportPinDirection"), &Z_Registration_Info_UEnum_EExportPinDirection, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 4217096699U) },
		{ EExportDependencyType_StaticEnum, TEXT("EExportDependencyType"), &Z_Registration_Info_UEnum_EExportDependencyType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3110129056U) },
		{ EBlueprintDiffChangeType_StaticEnum, TEXT("EBlueprintDiffChangeType"), &Z_Registration_Info_UEnum_EBlueprintDiffChangeType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1858970996U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FBlueprintExportConfig::StaticStruct, Z_Construct_UScriptStruct_FBlueprintExportConfig_Statics::NewStructOps, TEXT("BlueprintExportConfig"),&Z_Registration_Info_UScriptStruct_FBlueprintExportConfig, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBlueprintExportConfig), 83341232U) },
		{ FExportedPinType::StaticStruct, Z_Construct_UScriptStruct_FExportedPinType_Statics::NewStructOps, TEXT("ExportedPinType"),&Z_Registration_Info_UScriptStruct_FExportedPinType, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedPinType), 3244080351U) },
		{ FExportedPinConnection::StaticStruct, Z_Construct_UScriptStruct_FExportedPinConnection_Statics::NewStructOps, TEXT("ExportedPinConnection"),&Z_Registration_Info_UScriptStruct_FExportedPinConnection, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedPinConnection), 417709420U) },
		{ FExportedPin::StaticStruct, Z_Construct_UScriptStruct_FExportedPin_Statics::NewStructOps, TEXT("ExportedPin"),&Z_Registration_Info_UScriptStruct_FExportedPin, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedPin), 3667484744U) },
		{ FExportedNode::StaticStruct, Z_Construct_UScriptStruct_FExportedNode_Statics::NewStructOps, TEXT("ExportedNode"),&Z_Registration_Info_UScriptStruct_FExportedNode, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedNode), 2727321664U) },
		{ FExportedGraph::StaticStruct, Z_Construct_UScriptStruct_FExportedGraph_Statics::NewStructOps, TEXT("ExportedGraph"),&Z_Registration_Info_UScriptStruct_FExportedGraph, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedGraph), 193825846U) },
		{ FExportedVariableFlags::StaticStruct, Z_Construct_UScriptStruct_FExportedVariableFlags_Statics::NewStructOps, TEXT("ExportedVariableFlags"),&Z_Registration_Info_UScriptStruct_FExportedVariableFlags, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedVariableFlags), 2431683992U) },
		{ FExportedVariable::StaticStruct, Z_Construct_UScriptStruct_FExportedVariable_Statics::NewStructOps, TEXT("ExportedVariable"),&Z_Registration_Info_UScriptStruct_FExportedVariable, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedVariable), 1626092749U) },
		{ FExportedFunctionParam::StaticStruct, Z_Construct_UScriptStruct_FExportedFunctionParam_Statics::NewStructOps, TEXT("ExportedFunctionParam"),&Z_Registration_Info_UScriptStruct_FExportedFunctionParam, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedFunctionParam), 1365006374U) },
		{ FExportedFunctionFlags::StaticStruct, Z_Construct_UScriptStruct_FExportedFunctionFlags_Statics::NewStructOps, TEXT("ExportedFunctionFlags"),&Z_Registration_Info_UScriptStruct_FExportedFunctionFlags, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedFunctionFlags), 409630351U) },
		{ FExportedFunction::StaticStruct, Z_Construct_UScriptStruct_FExportedFunction_Statics::NewStructOps, TEXT("ExportedFunction"),&Z_Registration_Info_UScriptStruct_FExportedFunction, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedFunction), 4096331461U) },
		{ FExportedComponentProperty::StaticStruct, Z_Construct_UScriptStruct_FExportedComponentProperty_Statics::NewStructOps, TEXT("ExportedComponentProperty"),&Z_Registration_Info_UScriptStruct_FExportedComponentProperty, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedComponentProperty), 3006916080U) },
		{ FExportedComponent::StaticStruct, Z_Construct_UScriptStruct_FExportedComponent_Statics::NewStructOps, TEXT("ExportedComponent"),&Z_Registration_Info_UScriptStruct_FExportedComponent, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedComponent), 817091047U) },
		{ FExportedDependency::StaticStruct, Z_Construct_UScriptStruct_FExportedDependency_Statics::NewStructOps, TEXT("ExportedDependency"),&Z_Registration_Info_UScriptStruct_FExportedDependency, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedDependency), 2115202204U) },
		{ FExportedParentClass::StaticStruct, Z_Construct_UScriptStruct_FExportedParentClass_Statics::NewStructOps, TEXT("ExportedParentClass"),&Z_Registration_Info_UScriptStruct_FExportedParentClass, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedParentClass), 413471149U) },
		{ FExportInfo::StaticStruct, Z_Construct_UScriptStruct_FExportInfo_Statics::NewStructOps, TEXT("ExportInfo"),&Z_Registration_Info_UScriptStruct_FExportInfo, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportInfo), 2393131268U) },
		{ FExportedTransitionBlendSettings::StaticStruct, Z_Construct_UScriptStruct_FExportedTransitionBlendSettings_Statics::NewStructOps, TEXT("ExportedTransitionBlendSettings"),&Z_Registration_Info_UScriptStruct_FExportedTransitionBlendSettings, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedTransitionBlendSettings), 2024514486U) },
		{ FExportedAnimState::StaticStruct, Z_Construct_UScriptStruct_FExportedAnimState_Statics::NewStructOps, TEXT("ExportedAnimState"),&Z_Registration_Info_UScriptStruct_FExportedAnimState, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedAnimState), 1438610023U) },
		{ FExportedAnimTransition::StaticStruct, Z_Construct_UScriptStruct_FExportedAnimTransition_Statics::NewStructOps, TEXT("ExportedAnimTransition"),&Z_Registration_Info_UScriptStruct_FExportedAnimTransition, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedAnimTransition), 1886809071U) },
		{ FExportedStateMachine::StaticStruct, Z_Construct_UScriptStruct_FExportedStateMachine_Statics::NewStructOps, TEXT("ExportedStateMachine"),&Z_Registration_Info_UScriptStruct_FExportedStateMachine, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedStateMachine), 3677686335U) },
		{ FExportedWidgetNode::StaticStruct, Z_Construct_UScriptStruct_FExportedWidgetNode_Statics::NewStructOps, TEXT("ExportedWidgetNode"),&Z_Registration_Info_UScriptStruct_FExportedWidgetNode, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedWidgetNode), 2859759423U) },
		{ FExportedBlueprint::StaticStruct, Z_Construct_UScriptStruct_FExportedBlueprint_Statics::NewStructOps, TEXT("ExportedBlueprint"),&Z_Registration_Info_UScriptStruct_FExportedBlueprint, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportedBlueprint), 1580580613U) },
		{ FExportManifestEntry::StaticStruct, Z_Construct_UScriptStruct_FExportManifestEntry_Statics::NewStructOps, TEXT("ExportManifestEntry"),&Z_Registration_Info_UScriptStruct_FExportManifestEntry, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportManifestEntry), 2800868016U) },
		{ FExportManifest::StaticStruct, Z_Construct_UScriptStruct_FExportManifest_Statics::NewStructOps, TEXT("ExportManifest"),&Z_Registration_Info_UScriptStruct_FExportManifest, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExportManifest), 2305226352U) },
		{ FBlueprintDiffChange::StaticStruct, Z_Construct_UScriptStruct_FBlueprintDiffChange_Statics::NewStructOps, TEXT("BlueprintDiffChange"),&Z_Registration_Info_UScriptStruct_FBlueprintDiffChange, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBlueprintDiffChange), 3585319695U) },
		{ FBlueprintDiffResult::StaticStruct, Z_Construct_UScriptStruct_FBlueprintDiffResult_Statics::NewStructOps, TEXT("BlueprintDiffResult"),&Z_Registration_Info_UScriptStruct_FBlueprintDiffResult, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBlueprintDiffResult), 2532158023U) },
		{ FBlueprintExportMetrics::StaticStruct, Z_Construct_UScriptStruct_FBlueprintExportMetrics_Statics::NewStructOps, TEXT("BlueprintExportMetrics"),&Z_Registration_Info_UScriptStruct_FBlueprintExportMetrics, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBlueprintExportMetrics), 993822037U) },
	};
}; // Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Schema_BlueprintExportTypes_h__Script_BlueprintExporter_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Schema_BlueprintExportTypes_h__Script_BlueprintExporter_3627219418{
	TEXT("/Script/BlueprintExporter"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Schema_BlueprintExportTypes_h__Script_BlueprintExporter_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Schema_BlueprintExportTypes_h__Script_BlueprintExporter_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Schema_BlueprintExportTypes_h__Script_BlueprintExporter_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Schema_BlueprintExportTypes_h__Script_BlueprintExporter_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
