// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Commandlets/DeepDumpCommandlet.h"

#ifdef BLUEPRINTEXPORTER_DeepDumpCommandlet_generated_h
#error "DeepDumpCommandlet.generated.h already included, missing '#pragma once' in DeepDumpCommandlet.h"
#endif
#define BLUEPRINTEXPORTER_DeepDumpCommandlet_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UDeepDumpCommandlet ******************************************************
struct Z_Construct_UClass_UDeepDumpCommandlet_Statics;
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UDeepDumpCommandlet_NoRegister();

#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_DeepDumpCommandlet_h_39_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUDeepDumpCommandlet(); \
	friend struct ::Z_Construct_UClass_UDeepDumpCommandlet_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend BLUEPRINTEXPORTER_API UClass* ::Z_Construct_UClass_UDeepDumpCommandlet_NoRegister(); \
public: \
	DECLARE_CLASS2(UDeepDumpCommandlet, UCommandlet, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/BlueprintExporter"), Z_Construct_UClass_UDeepDumpCommandlet_NoRegister) \
	DECLARE_SERIALIZER(UDeepDumpCommandlet)


#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_DeepDumpCommandlet_h_39_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UDeepDumpCommandlet(UDeepDumpCommandlet&&) = delete; \
	UDeepDumpCommandlet(const UDeepDumpCommandlet&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDeepDumpCommandlet); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDeepDumpCommandlet); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UDeepDumpCommandlet) \
	NO_API virtual ~UDeepDumpCommandlet();


#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_DeepDumpCommandlet_h_36_PROLOG
#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_DeepDumpCommandlet_h_39_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_DeepDumpCommandlet_h_39_INCLASS_NO_PURE_DECLS \
	FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_DeepDumpCommandlet_h_39_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UDeepDumpCommandlet;

// ********** End Class UDeepDumpCommandlet ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_DeepDumpCommandlet_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
