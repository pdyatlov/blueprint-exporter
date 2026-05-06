// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Tests/TestUFunctionFixtures.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeTestUFunctionFixtures() {}

// ********** Begin Cross Module References ********************************************************
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UBpxTestUFunctionFixture();
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UBpxTestUFunctionFixture_NoRegister();
BLUEPRINTEXPORTER_API UEnum* Z_Construct_UEnum_BlueprintExporter_EBpxTestFixtureEnum();
BLUEPRINTEXPORTER_API UScriptStruct* Z_Construct_UScriptStruct_FBpxTestFixtureStruct();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
UPackage* Z_Construct_UPackage__Script_BlueprintExporter();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FBpxTestFixtureStruct *********************************************
struct Z_Construct_UScriptStruct_FBpxTestFixtureStruct_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FBpxTestFixtureStruct); }
	static inline consteval int16 GetStructAlignment() { return alignof(FBpxTestFixtureStruct); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Private/Tests/TestUFunctionFixtures.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IntField_MetaData[] = {
		{ "Category", "Test" },
		{ "ModuleRelativePath", "Private/Tests/TestUFunctionFixtures.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StringField_MetaData[] = {
		{ "Category", "Test" },
		{ "ModuleRelativePath", "Private/Tests/TestUFunctionFixtures.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FloatField_MetaData[] = {
		{ "Category", "Test" },
		{ "ModuleRelativePath", "Private/Tests/TestUFunctionFixtures.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FBpxTestFixtureStruct constinit property declarations *************
	static const UECodeGen_Private::FIntPropertyParams NewProp_IntField;
	static const UECodeGen_Private::FStrPropertyParams NewProp_StringField;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FloatField;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FBpxTestFixtureStruct constinit property declarations ***************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBpxTestFixtureStruct>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FBpxTestFixtureStruct_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBpxTestFixtureStruct;
class UScriptStruct* FBpxTestFixtureStruct::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBpxTestFixtureStruct.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBpxTestFixtureStruct.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBpxTestFixtureStruct, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("BpxTestFixtureStruct"));
	}
	return Z_Registration_Info_UScriptStruct_FBpxTestFixtureStruct.OuterSingleton;
	}

// ********** Begin ScriptStruct FBpxTestFixtureStruct Property Definitions ************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBpxTestFixtureStruct_Statics::NewProp_IntField = { "IntField", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBpxTestFixtureStruct, IntField), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IntField_MetaData), NewProp_IntField_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBpxTestFixtureStruct_Statics::NewProp_StringField = { "StringField", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBpxTestFixtureStruct, StringField), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StringField_MetaData), NewProp_StringField_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FBpxTestFixtureStruct_Statics::NewProp_FloatField = { "FloatField", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBpxTestFixtureStruct, FloatField), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FloatField_MetaData), NewProp_FloatField_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBpxTestFixtureStruct_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBpxTestFixtureStruct_Statics::NewProp_IntField,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBpxTestFixtureStruct_Statics::NewProp_StringField,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBpxTestFixtureStruct_Statics::NewProp_FloatField,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBpxTestFixtureStruct_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FBpxTestFixtureStruct Property Definitions **************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBpxTestFixtureStruct_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	&NewStructOps,
	"BpxTestFixtureStruct",
	Z_Construct_UScriptStruct_FBpxTestFixtureStruct_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBpxTestFixtureStruct_Statics::PropPointers),
	sizeof(FBpxTestFixtureStruct),
	alignof(FBpxTestFixtureStruct),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBpxTestFixtureStruct_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBpxTestFixtureStruct_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBpxTestFixtureStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBpxTestFixtureStruct.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBpxTestFixtureStruct.InnerSingleton, Z_Construct_UScriptStruct_FBpxTestFixtureStruct_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FBpxTestFixtureStruct.InnerSingleton);
}
// ********** End ScriptStruct FBpxTestFixtureStruct ***********************************************

// ********** Begin Enum EBpxTestFixtureEnum *******************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EBpxTestFixtureEnum;
static UEnum* EBpxTestFixtureEnum_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EBpxTestFixtureEnum.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EBpxTestFixtureEnum.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_BlueprintExporter_EBpxTestFixtureEnum, (UObject*)Z_Construct_UPackage__Script_BlueprintExporter(), TEXT("EBpxTestFixtureEnum"));
	}
	return Z_Registration_Info_UEnum_EBpxTestFixtureEnum.OuterSingleton;
}
template<> BLUEPRINTEXPORTER_NON_ATTRIBUTED_API UEnum* StaticEnum<EBpxTestFixtureEnum>()
{
	return EBpxTestFixtureEnum_StaticEnum();
}
struct Z_Construct_UEnum_BlueprintExporter_EBpxTestFixtureEnum_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Alpha.Name", "EBpxTestFixtureEnum::Alpha" },
		{ "Beta.Name", "EBpxTestFixtureEnum::Beta" },
		{ "BlueprintType", "true" },
		{ "Gamma.Name", "EBpxTestFixtureEnum::Gamma" },
		{ "ModuleRelativePath", "Private/Tests/TestUFunctionFixtures.h" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EBpxTestFixtureEnum::Alpha", (int64)EBpxTestFixtureEnum::Alpha },
		{ "EBpxTestFixtureEnum::Beta", (int64)EBpxTestFixtureEnum::Beta },
		{ "EBpxTestFixtureEnum::Gamma", (int64)EBpxTestFixtureEnum::Gamma },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_BlueprintExporter_EBpxTestFixtureEnum_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_BlueprintExporter_EBpxTestFixtureEnum_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_BlueprintExporter,
	nullptr,
	"EBpxTestFixtureEnum",
	"EBpxTestFixtureEnum",
	Z_Construct_UEnum_BlueprintExporter_EBpxTestFixtureEnum_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_BlueprintExporter_EBpxTestFixtureEnum_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_BlueprintExporter_EBpxTestFixtureEnum_Statics::Enum_MetaDataParams), Z_Construct_UEnum_BlueprintExporter_EBpxTestFixtureEnum_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_BlueprintExporter_EBpxTestFixtureEnum()
{
	if (!Z_Registration_Info_UEnum_EBpxTestFixtureEnum.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EBpxTestFixtureEnum.InnerSingleton, Z_Construct_UEnum_BlueprintExporter_EBpxTestFixtureEnum_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EBpxTestFixtureEnum.InnerSingleton;
}
// ********** End Enum EBpxTestFixtureEnum *********************************************************

// ********** Begin Class UBpxTestUFunctionFixture Function AddFloats ******************************
struct Z_Construct_UFunction_UBpxTestUFunctionFixture_AddFloats_Statics
{
	struct BpxTestUFunctionFixture_eventAddFloats_Parms
	{
		float A;
		float B;
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Test" },
		{ "ModuleRelativePath", "Private/Tests/TestUFunctionFixtures.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function AddFloats constinit property declarations *****************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_A;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_B;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddFloats constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddFloats Property Definitions ****************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBpxTestUFunctionFixture_AddFloats_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxTestUFunctionFixture_eventAddFloats_Parms, A), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBpxTestUFunctionFixture_AddFloats_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxTestUFunctionFixture_eventAddFloats_Parms, B), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBpxTestUFunctionFixture_AddFloats_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxTestUFunctionFixture_eventAddFloats_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxTestUFunctionFixture_AddFloats_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxTestUFunctionFixture_AddFloats_Statics::NewProp_A,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxTestUFunctionFixture_AddFloats_Statics::NewProp_B,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxTestUFunctionFixture_AddFloats_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_AddFloats_Statics::PropPointers) < 2048);
// ********** End Function AddFloats Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxTestUFunctionFixture_AddFloats_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxTestUFunctionFixture, nullptr, "AddFloats", 	Z_Construct_UFunction_UBpxTestUFunctionFixture_AddFloats_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_AddFloats_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_AddFloats_Statics::BpxTestUFunctionFixture_eventAddFloats_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_AddFloats_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxTestUFunctionFixture_AddFloats_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_AddFloats_Statics::BpxTestUFunctionFixture_eventAddFloats_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxTestUFunctionFixture_AddFloats()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxTestUFunctionFixture_AddFloats_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxTestUFunctionFixture::execAddFloats)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_A);
	P_GET_PROPERTY(FFloatProperty,Z_Param_B);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->AddFloats(Z_Param_A,Z_Param_B);
	P_NATIVE_END;
}
// ********** End Class UBpxTestUFunctionFixture Function AddFloats ********************************

// ********** Begin Class UBpxTestUFunctionFixture Function ConcatStrings **************************
struct Z_Construct_UFunction_UBpxTestUFunctionFixture_ConcatStrings_Statics
{
	struct BpxTestUFunctionFixture_eventConcatStrings_Parms
	{
		FString A;
		FString B;
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Test" },
		{ "ModuleRelativePath", "Private/Tests/TestUFunctionFixtures.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_A_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_B_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ConcatStrings constinit property declarations *************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_A;
	static const UECodeGen_Private::FStrPropertyParams NewProp_B;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ConcatStrings constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ConcatStrings Property Definitions ************************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxTestUFunctionFixture_ConcatStrings_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxTestUFunctionFixture_eventConcatStrings_Parms, A), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_A_MetaData), NewProp_A_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxTestUFunctionFixture_ConcatStrings_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxTestUFunctionFixture_eventConcatStrings_Parms, B), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_B_MetaData), NewProp_B_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxTestUFunctionFixture_ConcatStrings_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxTestUFunctionFixture_eventConcatStrings_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxTestUFunctionFixture_ConcatStrings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxTestUFunctionFixture_ConcatStrings_Statics::NewProp_A,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxTestUFunctionFixture_ConcatStrings_Statics::NewProp_B,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxTestUFunctionFixture_ConcatStrings_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_ConcatStrings_Statics::PropPointers) < 2048);
// ********** End Function ConcatStrings Property Definitions **************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxTestUFunctionFixture_ConcatStrings_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxTestUFunctionFixture, nullptr, "ConcatStrings", 	Z_Construct_UFunction_UBpxTestUFunctionFixture_ConcatStrings_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_ConcatStrings_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_ConcatStrings_Statics::BpxTestUFunctionFixture_eventConcatStrings_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_ConcatStrings_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxTestUFunctionFixture_ConcatStrings_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_ConcatStrings_Statics::BpxTestUFunctionFixture_eventConcatStrings_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxTestUFunctionFixture_ConcatStrings()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxTestUFunctionFixture_ConcatStrings_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxTestUFunctionFixture::execConcatStrings)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_A);
	P_GET_PROPERTY(FStrProperty,Z_Param_B);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=P_THIS->ConcatStrings(Z_Param_A,Z_Param_B);
	P_NATIVE_END;
}
// ********** End Class UBpxTestUFunctionFixture Function ConcatStrings ****************************

// ********** Begin Class UBpxTestUFunctionFixture Function EchoInt ********************************
struct Z_Construct_UFunction_UBpxTestUFunctionFixture_EchoInt_Statics
{
	struct BpxTestUFunctionFixture_eventEchoInt_Parms
	{
		int32 Value;
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Test" },
		{ "ModuleRelativePath", "Private/Tests/TestUFunctionFixtures.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function EchoInt constinit property declarations *******************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_Value;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function EchoInt constinit property declarations *********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function EchoInt Property Definitions ******************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBpxTestUFunctionFixture_EchoInt_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxTestUFunctionFixture_eventEchoInt_Parms, Value), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBpxTestUFunctionFixture_EchoInt_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxTestUFunctionFixture_eventEchoInt_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxTestUFunctionFixture_EchoInt_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxTestUFunctionFixture_EchoInt_Statics::NewProp_Value,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxTestUFunctionFixture_EchoInt_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_EchoInt_Statics::PropPointers) < 2048);
// ********** End Function EchoInt Property Definitions ********************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxTestUFunctionFixture_EchoInt_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxTestUFunctionFixture, nullptr, "EchoInt", 	Z_Construct_UFunction_UBpxTestUFunctionFixture_EchoInt_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_EchoInt_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_EchoInt_Statics::BpxTestUFunctionFixture_eventEchoInt_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_EchoInt_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxTestUFunctionFixture_EchoInt_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_EchoInt_Statics::BpxTestUFunctionFixture_eventEchoInt_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxTestUFunctionFixture_EchoInt()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxTestUFunctionFixture_EchoInt_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxTestUFunctionFixture::execEchoInt)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_Value);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->EchoInt(Z_Param_Value);
	P_NATIVE_END;
}
// ********** End Class UBpxTestUFunctionFixture Function EchoInt **********************************

// ********** Begin Class UBpxTestUFunctionFixture Function GetBoolValue ***************************
struct Z_Construct_UFunction_UBpxTestUFunctionFixture_GetBoolValue_Statics
{
	struct BpxTestUFunctionFixture_eventGetBoolValue_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Test" },
		{ "ModuleRelativePath", "Private/Tests/TestUFunctionFixtures.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetBoolValue constinit property declarations **************************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetBoolValue constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetBoolValue Property Definitions *************************************
void Z_Construct_UFunction_UBpxTestUFunctionFixture_GetBoolValue_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((BpxTestUFunctionFixture_eventGetBoolValue_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBpxTestUFunctionFixture_GetBoolValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(BpxTestUFunctionFixture_eventGetBoolValue_Parms), &Z_Construct_UFunction_UBpxTestUFunctionFixture_GetBoolValue_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxTestUFunctionFixture_GetBoolValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxTestUFunctionFixture_GetBoolValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetBoolValue_Statics::PropPointers) < 2048);
// ********** End Function GetBoolValue Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxTestUFunctionFixture_GetBoolValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxTestUFunctionFixture, nullptr, "GetBoolValue", 	Z_Construct_UFunction_UBpxTestUFunctionFixture_GetBoolValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetBoolValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetBoolValue_Statics::BpxTestUFunctionFixture_eventGetBoolValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetBoolValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxTestUFunctionFixture_GetBoolValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetBoolValue_Statics::BpxTestUFunctionFixture_eventGetBoolValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxTestUFunctionFixture_GetBoolValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxTestUFunctionFixture_GetBoolValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxTestUFunctionFixture::execGetBoolValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetBoolValue();
	P_NATIVE_END;
}
// ********** End Class UBpxTestUFunctionFixture Function GetBoolValue *****************************

// ********** Begin Class UBpxTestUFunctionFixture Function GetEnumValue ***************************
struct Z_Construct_UFunction_UBpxTestUFunctionFixture_GetEnumValue_Statics
{
	struct BpxTestUFunctionFixture_eventGetEnumValue_Parms
	{
		EBpxTestFixtureEnum ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Test" },
		{ "ModuleRelativePath", "Private/Tests/TestUFunctionFixtures.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetEnumValue constinit property declarations **************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetEnumValue constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetEnumValue Property Definitions *************************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UBpxTestUFunctionFixture_GetEnumValue_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UBpxTestUFunctionFixture_GetEnumValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxTestUFunctionFixture_eventGetEnumValue_Parms, ReturnValue), Z_Construct_UEnum_BlueprintExporter_EBpxTestFixtureEnum, METADATA_PARAMS(0, nullptr) }; // 3603385499
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxTestUFunctionFixture_GetEnumValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxTestUFunctionFixture_GetEnumValue_Statics::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxTestUFunctionFixture_GetEnumValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetEnumValue_Statics::PropPointers) < 2048);
// ********** End Function GetEnumValue Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxTestUFunctionFixture_GetEnumValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxTestUFunctionFixture, nullptr, "GetEnumValue", 	Z_Construct_UFunction_UBpxTestUFunctionFixture_GetEnumValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetEnumValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetEnumValue_Statics::BpxTestUFunctionFixture_eventGetEnumValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetEnumValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxTestUFunctionFixture_GetEnumValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetEnumValue_Statics::BpxTestUFunctionFixture_eventGetEnumValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxTestUFunctionFixture_GetEnumValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxTestUFunctionFixture_GetEnumValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxTestUFunctionFixture::execGetEnumValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(EBpxTestFixtureEnum*)Z_Param__Result=P_THIS->GetEnumValue();
	P_NATIVE_END;
}
// ********** End Class UBpxTestUFunctionFixture Function GetEnumValue *****************************

// ********** Begin Class UBpxTestUFunctionFixture Function GetFloatValue **************************
struct Z_Construct_UFunction_UBpxTestUFunctionFixture_GetFloatValue_Statics
{
	struct BpxTestUFunctionFixture_eventGetFloatValue_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Test" },
		{ "ModuleRelativePath", "Private/Tests/TestUFunctionFixtures.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetFloatValue constinit property declarations *************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetFloatValue constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetFloatValue Property Definitions ************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBpxTestUFunctionFixture_GetFloatValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxTestUFunctionFixture_eventGetFloatValue_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxTestUFunctionFixture_GetFloatValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxTestUFunctionFixture_GetFloatValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetFloatValue_Statics::PropPointers) < 2048);
// ********** End Function GetFloatValue Property Definitions **************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxTestUFunctionFixture_GetFloatValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxTestUFunctionFixture, nullptr, "GetFloatValue", 	Z_Construct_UFunction_UBpxTestUFunctionFixture_GetFloatValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetFloatValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetFloatValue_Statics::BpxTestUFunctionFixture_eventGetFloatValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetFloatValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxTestUFunctionFixture_GetFloatValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetFloatValue_Statics::BpxTestUFunctionFixture_eventGetFloatValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxTestUFunctionFixture_GetFloatValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxTestUFunctionFixture_GetFloatValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxTestUFunctionFixture::execGetFloatValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetFloatValue();
	P_NATIVE_END;
}
// ********** End Class UBpxTestUFunctionFixture Function GetFloatValue ****************************

// ********** Begin Class UBpxTestUFunctionFixture Function GetIntValue ****************************
struct Z_Construct_UFunction_UBpxTestUFunctionFixture_GetIntValue_Statics
{
	struct BpxTestUFunctionFixture_eventGetIntValue_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Test" },
		{ "ModuleRelativePath", "Private/Tests/TestUFunctionFixtures.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetIntValue constinit property declarations ***************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetIntValue constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetIntValue Property Definitions **************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBpxTestUFunctionFixture_GetIntValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxTestUFunctionFixture_eventGetIntValue_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxTestUFunctionFixture_GetIntValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxTestUFunctionFixture_GetIntValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetIntValue_Statics::PropPointers) < 2048);
// ********** End Function GetIntValue Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxTestUFunctionFixture_GetIntValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxTestUFunctionFixture, nullptr, "GetIntValue", 	Z_Construct_UFunction_UBpxTestUFunctionFixture_GetIntValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetIntValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetIntValue_Statics::BpxTestUFunctionFixture_eventGetIntValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetIntValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxTestUFunctionFixture_GetIntValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetIntValue_Statics::BpxTestUFunctionFixture_eventGetIntValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxTestUFunctionFixture_GetIntValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxTestUFunctionFixture_GetIntValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxTestUFunctionFixture::execGetIntValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetIntValue();
	P_NATIVE_END;
}
// ********** End Class UBpxTestUFunctionFixture Function GetIntValue ******************************

// ********** Begin Class UBpxTestUFunctionFixture Function GetNameValue ***************************
struct Z_Construct_UFunction_UBpxTestUFunctionFixture_GetNameValue_Statics
{
	struct BpxTestUFunctionFixture_eventGetNameValue_Parms
	{
		FName ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Test" },
		{ "ModuleRelativePath", "Private/Tests/TestUFunctionFixtures.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetNameValue constinit property declarations **************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetNameValue constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetNameValue Property Definitions *************************************
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBpxTestUFunctionFixture_GetNameValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxTestUFunctionFixture_eventGetNameValue_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxTestUFunctionFixture_GetNameValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxTestUFunctionFixture_GetNameValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetNameValue_Statics::PropPointers) < 2048);
// ********** End Function GetNameValue Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxTestUFunctionFixture_GetNameValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxTestUFunctionFixture, nullptr, "GetNameValue", 	Z_Construct_UFunction_UBpxTestUFunctionFixture_GetNameValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetNameValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetNameValue_Statics::BpxTestUFunctionFixture_eventGetNameValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetNameValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxTestUFunctionFixture_GetNameValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetNameValue_Statics::BpxTestUFunctionFixture_eventGetNameValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxTestUFunctionFixture_GetNameValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxTestUFunctionFixture_GetNameValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxTestUFunctionFixture::execGetNameValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FName*)Z_Param__Result=P_THIS->GetNameValue();
	P_NATIVE_END;
}
// ********** End Class UBpxTestUFunctionFixture Function GetNameValue *****************************

// ********** Begin Class UBpxTestUFunctionFixture Function GetObjectValue *************************
struct Z_Construct_UFunction_UBpxTestUFunctionFixture_GetObjectValue_Statics
{
	struct BpxTestUFunctionFixture_eventGetObjectValue_Parms
	{
		UObject* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Test" },
		{ "ModuleRelativePath", "Private/Tests/TestUFunctionFixtures.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetObjectValue constinit property declarations ************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetObjectValue constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetObjectValue Property Definitions ***********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBpxTestUFunctionFixture_GetObjectValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxTestUFunctionFixture_eventGetObjectValue_Parms, ReturnValue), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxTestUFunctionFixture_GetObjectValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxTestUFunctionFixture_GetObjectValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetObjectValue_Statics::PropPointers) < 2048);
// ********** End Function GetObjectValue Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxTestUFunctionFixture_GetObjectValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxTestUFunctionFixture, nullptr, "GetObjectValue", 	Z_Construct_UFunction_UBpxTestUFunctionFixture_GetObjectValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetObjectValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetObjectValue_Statics::BpxTestUFunctionFixture_eventGetObjectValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetObjectValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxTestUFunctionFixture_GetObjectValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetObjectValue_Statics::BpxTestUFunctionFixture_eventGetObjectValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxTestUFunctionFixture_GetObjectValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxTestUFunctionFixture_GetObjectValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxTestUFunctionFixture::execGetObjectValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UObject**)Z_Param__Result=P_THIS->GetObjectValue();
	P_NATIVE_END;
}
// ********** End Class UBpxTestUFunctionFixture Function GetObjectValue ***************************

// ********** Begin Class UBpxTestUFunctionFixture Function GetStringValue *************************
struct Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStringValue_Statics
{
	struct BpxTestUFunctionFixture_eventGetStringValue_Parms
	{
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Test" },
		{ "ModuleRelativePath", "Private/Tests/TestUFunctionFixtures.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetStringValue constinit property declarations ************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetStringValue constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetStringValue Property Definitions ***********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStringValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxTestUFunctionFixture_eventGetStringValue_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStringValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStringValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStringValue_Statics::PropPointers) < 2048);
// ********** End Function GetStringValue Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStringValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxTestUFunctionFixture, nullptr, "GetStringValue", 	Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStringValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStringValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStringValue_Statics::BpxTestUFunctionFixture_eventGetStringValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStringValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStringValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStringValue_Statics::BpxTestUFunctionFixture_eventGetStringValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStringValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStringValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxTestUFunctionFixture::execGetStringValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=P_THIS->GetStringValue();
	P_NATIVE_END;
}
// ********** End Class UBpxTestUFunctionFixture Function GetStringValue ***************************

// ********** Begin Class UBpxTestUFunctionFixture Function GetStructValue *************************
struct Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStructValue_Statics
{
	struct BpxTestUFunctionFixture_eventGetStructValue_Parms
	{
		FBpxTestFixtureStruct ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Test" },
		{ "ModuleRelativePath", "Private/Tests/TestUFunctionFixtures.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetStructValue constinit property declarations ************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetStructValue constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetStructValue Property Definitions ***********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStructValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BpxTestUFunctionFixture_eventGetStructValue_Parms, ReturnValue), Z_Construct_UScriptStruct_FBpxTestFixtureStruct, METADATA_PARAMS(0, nullptr) }; // 3736981115
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStructValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStructValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStructValue_Statics::PropPointers) < 2048);
// ********** End Function GetStructValue Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStructValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxTestUFunctionFixture, nullptr, "GetStructValue", 	Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStructValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStructValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStructValue_Statics::BpxTestUFunctionFixture_eventGetStructValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStructValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStructValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStructValue_Statics::BpxTestUFunctionFixture_eventGetStructValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStructValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStructValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxTestUFunctionFixture::execGetStructValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBpxTestFixtureStruct*)Z_Param__Result=P_THIS->GetStructValue();
	P_NATIVE_END;
}
// ********** End Class UBpxTestUFunctionFixture Function GetStructValue ***************************

// ********** Begin Class UBpxTestUFunctionFixture Function VoidFunction ***************************
struct Z_Construct_UFunction_UBpxTestUFunctionFixture_VoidFunction_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Test" },
		{ "ModuleRelativePath", "Private/Tests/TestUFunctionFixtures.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function VoidFunction constinit property declarations **************************
// ********** End Function VoidFunction constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBpxTestUFunctionFixture_VoidFunction_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBpxTestUFunctionFixture, nullptr, "VoidFunction", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x44020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBpxTestUFunctionFixture_VoidFunction_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBpxTestUFunctionFixture_VoidFunction_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UBpxTestUFunctionFixture_VoidFunction()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBpxTestUFunctionFixture_VoidFunction_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBpxTestUFunctionFixture::execVoidFunction)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->VoidFunction();
	P_NATIVE_END;
}
// ********** End Class UBpxTestUFunctionFixture Function VoidFunction *****************************

// ********** Begin Class UBpxTestUFunctionFixture *************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UBpxTestUFunctionFixture;
UClass* UBpxTestUFunctionFixture::GetPrivateStaticClass()
{
	using TClass = UBpxTestUFunctionFixture;
	if (!Z_Registration_Info_UClass_UBpxTestUFunctionFixture.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("BpxTestUFunctionFixture"),
			Z_Registration_Info_UClass_UBpxTestUFunctionFixture.InnerSingleton,
			StaticRegisterNativesUBpxTestUFunctionFixture,
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
	return Z_Registration_Info_UClass_UBpxTestUFunctionFixture.InnerSingleton;
}
UClass* Z_Construct_UClass_UBpxTestUFunctionFixture_NoRegister()
{
	return UBpxTestUFunctionFixture::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBpxTestUFunctionFixture_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Tests/TestUFunctionFixtures.h" },
		{ "ModuleRelativePath", "Private/Tests/TestUFunctionFixtures.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UBpxTestUFunctionFixture constinit property declarations *****************
// ********** End Class UBpxTestUFunctionFixture constinit property declarations *******************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("AddFloats"), .Pointer = &UBpxTestUFunctionFixture::execAddFloats },
		{ .NameUTF8 = UTF8TEXT("ConcatStrings"), .Pointer = &UBpxTestUFunctionFixture::execConcatStrings },
		{ .NameUTF8 = UTF8TEXT("EchoInt"), .Pointer = &UBpxTestUFunctionFixture::execEchoInt },
		{ .NameUTF8 = UTF8TEXT("GetBoolValue"), .Pointer = &UBpxTestUFunctionFixture::execGetBoolValue },
		{ .NameUTF8 = UTF8TEXT("GetEnumValue"), .Pointer = &UBpxTestUFunctionFixture::execGetEnumValue },
		{ .NameUTF8 = UTF8TEXT("GetFloatValue"), .Pointer = &UBpxTestUFunctionFixture::execGetFloatValue },
		{ .NameUTF8 = UTF8TEXT("GetIntValue"), .Pointer = &UBpxTestUFunctionFixture::execGetIntValue },
		{ .NameUTF8 = UTF8TEXT("GetNameValue"), .Pointer = &UBpxTestUFunctionFixture::execGetNameValue },
		{ .NameUTF8 = UTF8TEXT("GetObjectValue"), .Pointer = &UBpxTestUFunctionFixture::execGetObjectValue },
		{ .NameUTF8 = UTF8TEXT("GetStringValue"), .Pointer = &UBpxTestUFunctionFixture::execGetStringValue },
		{ .NameUTF8 = UTF8TEXT("GetStructValue"), .Pointer = &UBpxTestUFunctionFixture::execGetStructValue },
		{ .NameUTF8 = UTF8TEXT("VoidFunction"), .Pointer = &UBpxTestUFunctionFixture::execVoidFunction },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UBpxTestUFunctionFixture_AddFloats, "AddFloats" }, // 2537772608
		{ &Z_Construct_UFunction_UBpxTestUFunctionFixture_ConcatStrings, "ConcatStrings" }, // 732053975
		{ &Z_Construct_UFunction_UBpxTestUFunctionFixture_EchoInt, "EchoInt" }, // 1698994303
		{ &Z_Construct_UFunction_UBpxTestUFunctionFixture_GetBoolValue, "GetBoolValue" }, // 647489803
		{ &Z_Construct_UFunction_UBpxTestUFunctionFixture_GetEnumValue, "GetEnumValue" }, // 2624878246
		{ &Z_Construct_UFunction_UBpxTestUFunctionFixture_GetFloatValue, "GetFloatValue" }, // 864765523
		{ &Z_Construct_UFunction_UBpxTestUFunctionFixture_GetIntValue, "GetIntValue" }, // 706985755
		{ &Z_Construct_UFunction_UBpxTestUFunctionFixture_GetNameValue, "GetNameValue" }, // 2955076678
		{ &Z_Construct_UFunction_UBpxTestUFunctionFixture_GetObjectValue, "GetObjectValue" }, // 872797076
		{ &Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStringValue, "GetStringValue" }, // 66795981
		{ &Z_Construct_UFunction_UBpxTestUFunctionFixture_GetStructValue, "GetStructValue" }, // 2834366272
		{ &Z_Construct_UFunction_UBpxTestUFunctionFixture_VoidFunction, "VoidFunction" }, // 2212702709
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBpxTestUFunctionFixture>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UBpxTestUFunctionFixture_Statics
UObject* (*const Z_Construct_UClass_UBpxTestUFunctionFixture_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBpxTestUFunctionFixture_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBpxTestUFunctionFixture_Statics::ClassParams = {
	&UBpxTestUFunctionFixture::StaticClass,
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
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBpxTestUFunctionFixture_Statics::Class_MetaDataParams), Z_Construct_UClass_UBpxTestUFunctionFixture_Statics::Class_MetaDataParams)
};
void UBpxTestUFunctionFixture::StaticRegisterNativesUBpxTestUFunctionFixture()
{
	UClass* Class = UBpxTestUFunctionFixture::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UBpxTestUFunctionFixture_Statics::Funcs));
}
UClass* Z_Construct_UClass_UBpxTestUFunctionFixture()
{
	if (!Z_Registration_Info_UClass_UBpxTestUFunctionFixture.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBpxTestUFunctionFixture.OuterSingleton, Z_Construct_UClass_UBpxTestUFunctionFixture_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBpxTestUFunctionFixture.OuterSingleton;
}
UBpxTestUFunctionFixture::UBpxTestUFunctionFixture(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UBpxTestUFunctionFixture);
UBpxTestUFunctionFixture::~UBpxTestUFunctionFixture() {}
// ********** End Class UBpxTestUFunctionFixture ***************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Private_Tests_TestUFunctionFixtures_h__Script_BlueprintExporter_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EBpxTestFixtureEnum_StaticEnum, TEXT("EBpxTestFixtureEnum"), &Z_Registration_Info_UEnum_EBpxTestFixtureEnum, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3603385499U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FBpxTestFixtureStruct::StaticStruct, Z_Construct_UScriptStruct_FBpxTestFixtureStruct_Statics::NewStructOps, TEXT("BpxTestFixtureStruct"),&Z_Registration_Info_UScriptStruct_FBpxTestFixtureStruct, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBpxTestFixtureStruct), 3736981115U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBpxTestUFunctionFixture, UBpxTestUFunctionFixture::StaticClass, TEXT("UBpxTestUFunctionFixture"), &Z_Registration_Info_UClass_UBpxTestUFunctionFixture, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBpxTestUFunctionFixture), 1041407333U) },
	};
}; // Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Private_Tests_TestUFunctionFixtures_h__Script_BlueprintExporter_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Private_Tests_TestUFunctionFixtures_h__Script_BlueprintExporter_3013010894{
	TEXT("/Script/BlueprintExporter"),
	Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Private_Tests_TestUFunctionFixtures_h__Script_BlueprintExporter_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Private_Tests_TestUFunctionFixtures_h__Script_BlueprintExporter_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Private_Tests_TestUFunctionFixtures_h__Script_BlueprintExporter_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Private_Tests_TestUFunctionFixtures_h__Script_BlueprintExporter_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Private_Tests_TestUFunctionFixtures_h__Script_BlueprintExporter_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Private_Tests_TestUFunctionFixtures_h__Script_BlueprintExporter_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
