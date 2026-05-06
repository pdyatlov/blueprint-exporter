// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Reflection/ReflectionOps.h"

#ifdef BLUEPRINTEXPORTER_ReflectionOps_generated_h
#error "ReflectionOps.generated.h already included, missing '#pragma once' in ReflectionOps.h"
#endif
#define BLUEPRINTEXPORTER_ReflectionOps_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UBlueprint;
class UClass;
class UCurveFloat;
class UEdGraph;
class UEnvQuery;
class UObject;
class UScriptStruct;
class UUserDefinedStruct;
struct FBpxGraphEndpoints;
struct FBpxNodeResult;
struct FBpxReflectionResult;
struct FEdGraphPinType;
struct FGuid;
struct FRichCurveKey;

// ********** Begin Class UBpxReflectionOps ********************************************************
#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Reflection_ReflectionOps_h_61_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execCreateBlueprintClassDeterministic); \
	DECLARE_FUNCTION(execAddGameplayTag); \
	DECLARE_FUNCTION(execSetUserDefinedStructMemberDefault); \
	DECLARE_FUNCTION(execRemoveUserDefinedStructMember); \
	DECLARE_FUNCTION(execAddUserDefinedStructMember); \
	DECLARE_FUNCTION(execCreateUserDefinedStructDeterministic); \
	DECLARE_FUNCTION(execCreateDataAssetInstanceDeterministic); \
	DECLARE_FUNCTION(execSetCurveFloatKeys); \
	DECLARE_FUNCTION(execCreateCurveFloatDeterministic); \
	DECLARE_FUNCTION(execRemoveEnvQueryTest); \
	DECLARE_FUNCTION(execAddEnvQueryTest); \
	DECLARE_FUNCTION(execAddEnvQueryOption); \
	DECLARE_FUNCTION(execAddSetFieldsInStructNode); \
	DECLARE_FUNCTION(execAddBreakStructNode); \
	DECLARE_FUNCTION(execAddMakeStructNode); \
	DECLARE_FUNCTION(execAddMacroInstanceNode); \
	DECLARE_FUNCTION(execAddFunctionOverrideDeterministic); \
	DECLARE_FUNCTION(execAddFunctionUserDefinedPin); \
	DECLARE_FUNCTION(execAddLocalVariableDeterministic); \
	DECLARE_FUNCTION(execAddDynamicCastNode); \
	DECLARE_FUNCTION(execAddExecutionSequenceNode); \
	DECLARE_FUNCTION(execAddCustomEventNode); \
	DECLARE_FUNCTION(execAddVariableSetNode); \
	DECLARE_FUNCTION(execAddVariableGetNode); \
	DECLARE_FUNCTION(execAddCallFunctionNode); \
	DECLARE_FUNCTION(execSetGraphPinLiteralDefault); \
	DECLARE_FUNCTION(execAddBranchNode); \
	DECLARE_FUNCTION(execAddInterfaceByPath); \
	DECLARE_FUNCTION(execAddComponentToSCSDeterministic); \
	DECLARE_FUNCTION(execAddFunctionGraphDeterministic); \
	DECLARE_FUNCTION(execAddMemberVariableDeterministic); \
	DECLARE_FUNCTION(execConnectGraphPinsByGuidString); \
	DECLARE_FUNCTION(execWipeFunctionGraphBody); \
	DECLARE_FUNCTION(execSetNodePinLiteralDefault); \
	DECLARE_FUNCTION(execConnectPinsByName); \
	DECLARE_FUNCTION(execAddSelfMemberGetNode); \
	DECLARE_FUNCTION(execFindGraphEndpoints); \
	DECLARE_FUNCTION(execOverrideInterfaceFunction); \
	DECLARE_FUNCTION(execGetObjectPropertyValue); \
	DECLARE_FUNCTION(execSetObjectPropertyValue); \
	DECLARE_FUNCTION(execNewSubobject); \
	DECLARE_FUNCTION(execSetInstancedStructType); \
	DECLARE_FUNCTION(execArrayRemoveAt); \
	DECLARE_FUNCTION(execArrayAppendNewElement); \
	DECLARE_FUNCTION(execCompileAndSavePackage); \
	DECLARE_FUNCTION(execGetArrayLength); \
	DECLARE_FUNCTION(execFindSubobject); \
	DECLARE_FUNCTION(execSetPropertyValue); \
	DECLARE_FUNCTION(execGetPropertyValue);


struct Z_Construct_UClass_UBpxReflectionOps_Statics;
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UBpxReflectionOps_NoRegister();

#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Reflection_ReflectionOps_h_61_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBpxReflectionOps(); \
	friend struct ::Z_Construct_UClass_UBpxReflectionOps_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend BLUEPRINTEXPORTER_API UClass* ::Z_Construct_UClass_UBpxReflectionOps_NoRegister(); \
public: \
	DECLARE_CLASS2(UBpxReflectionOps, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/BlueprintExporter"), Z_Construct_UClass_UBpxReflectionOps_NoRegister) \
	DECLARE_SERIALIZER(UBpxReflectionOps)


#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Reflection_ReflectionOps_h_61_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBpxReflectionOps(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UBpxReflectionOps(UBpxReflectionOps&&) = delete; \
	UBpxReflectionOps(const UBpxReflectionOps&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBpxReflectionOps); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBpxReflectionOps); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBpxReflectionOps) \
	NO_API virtual ~UBpxReflectionOps();


#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Reflection_ReflectionOps_h_58_PROLOG
#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Reflection_ReflectionOps_h_61_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Reflection_ReflectionOps_h_61_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Reflection_ReflectionOps_h_61_INCLASS_NO_PURE_DECLS \
	FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Reflection_ReflectionOps_h_61_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UBpxReflectionOps;

// ********** End Class UBpxReflectionOps **********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Reflection_ReflectionOps_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
