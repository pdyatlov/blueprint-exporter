// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Tests/TestUFunctionFixtures.h"

#ifdef BLUEPRINTEXPORTER_TestUFunctionFixtures_generated_h
#error "TestUFunctionFixtures.generated.h already included, missing '#pragma once' in TestUFunctionFixtures.h"
#endif
#define BLUEPRINTEXPORTER_TestUFunctionFixtures_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObject;
enum class EBpxTestFixtureEnum : uint8;
struct FBpxTestFixtureStruct;

// ********** Begin ScriptStruct FBpxTestFixtureStruct *********************************************
struct Z_Construct_UScriptStruct_FBpxTestFixtureStruct_Statics;
#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Private_Tests_TestUFunctionFixtures_h_12_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FBpxTestFixtureStruct_Statics; \
	BLUEPRINTEXPORTER_API static class UScriptStruct* StaticStruct();


struct FBpxTestFixtureStruct;
// ********** End ScriptStruct FBpxTestFixtureStruct ***********************************************

// ********** Begin Class UBpxTestUFunctionFixture *************************************************
#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Private_Tests_TestUFunctionFixtures_h_35_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execVoidFunction); \
	DECLARE_FUNCTION(execGetStructValue); \
	DECLARE_FUNCTION(execGetEnumValue); \
	DECLARE_FUNCTION(execConcatStrings); \
	DECLARE_FUNCTION(execAddFloats); \
	DECLARE_FUNCTION(execEchoInt); \
	DECLARE_FUNCTION(execGetObjectValue); \
	DECLARE_FUNCTION(execGetNameValue); \
	DECLARE_FUNCTION(execGetStringValue); \
	DECLARE_FUNCTION(execGetFloatValue); \
	DECLARE_FUNCTION(execGetIntValue); \
	DECLARE_FUNCTION(execGetBoolValue);


struct Z_Construct_UClass_UBpxTestUFunctionFixture_Statics;
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UBpxTestUFunctionFixture_NoRegister();

#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Private_Tests_TestUFunctionFixtures_h_35_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBpxTestUFunctionFixture(); \
	friend struct ::Z_Construct_UClass_UBpxTestUFunctionFixture_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend BLUEPRINTEXPORTER_API UClass* ::Z_Construct_UClass_UBpxTestUFunctionFixture_NoRegister(); \
public: \
	DECLARE_CLASS2(UBpxTestUFunctionFixture, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/BlueprintExporter"), Z_Construct_UClass_UBpxTestUFunctionFixture_NoRegister) \
	DECLARE_SERIALIZER(UBpxTestUFunctionFixture)


#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Private_Tests_TestUFunctionFixtures_h_35_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBpxTestUFunctionFixture(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UBpxTestUFunctionFixture(UBpxTestUFunctionFixture&&) = delete; \
	UBpxTestUFunctionFixture(const UBpxTestUFunctionFixture&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBpxTestUFunctionFixture); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBpxTestUFunctionFixture); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBpxTestUFunctionFixture) \
	NO_API virtual ~UBpxTestUFunctionFixture();


#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Private_Tests_TestUFunctionFixtures_h_32_PROLOG
#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Private_Tests_TestUFunctionFixtures_h_35_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Private_Tests_TestUFunctionFixtures_h_35_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Private_Tests_TestUFunctionFixtures_h_35_INCLASS_NO_PURE_DECLS \
	FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Private_Tests_TestUFunctionFixtures_h_35_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UBpxTestUFunctionFixture;

// ********** End Class UBpxTestUFunctionFixture ***************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Private_Tests_TestUFunctionFixtures_h

// ********** Begin Enum EBpxTestFixtureEnum *******************************************************
#define FOREACH_ENUM_EBPXTESTFIXTUREENUM(op) \
	op(EBpxTestFixtureEnum::Alpha) \
	op(EBpxTestFixtureEnum::Beta) \
	op(EBpxTestFixtureEnum::Gamma) 

enum class EBpxTestFixtureEnum : uint8;
template<> struct TIsUEnumClass<EBpxTestFixtureEnum> { enum { Value = true }; };
template<> BLUEPRINTEXPORTER_NON_ATTRIBUTED_API UEnum* StaticEnum<EBpxTestFixtureEnum>();
// ********** End Enum EBpxTestFixtureEnum *********************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
