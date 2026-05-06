// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Commandlets/BlueprintExportCommandlet.h"

#ifdef BLUEPRINTEXPORTER_BlueprintExportCommandlet_generated_h
#error "BlueprintExportCommandlet.generated.h already included, missing '#pragma once' in BlueprintExportCommandlet.h"
#endif
#define BLUEPRINTEXPORTER_BlueprintExportCommandlet_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UBlueprintExportCommandlet ***********************************************
struct Z_Construct_UClass_UBlueprintExportCommandlet_Statics;
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UBlueprintExportCommandlet_NoRegister();

#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_BlueprintExportCommandlet_h_33_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBlueprintExportCommandlet(); \
	friend struct ::Z_Construct_UClass_UBlueprintExportCommandlet_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend BLUEPRINTEXPORTER_API UClass* ::Z_Construct_UClass_UBlueprintExportCommandlet_NoRegister(); \
public: \
	DECLARE_CLASS2(UBlueprintExportCommandlet, UCommandlet, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/BlueprintExporter"), Z_Construct_UClass_UBlueprintExportCommandlet_NoRegister) \
	DECLARE_SERIALIZER(UBlueprintExportCommandlet)


#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_BlueprintExportCommandlet_h_33_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UBlueprintExportCommandlet(UBlueprintExportCommandlet&&) = delete; \
	UBlueprintExportCommandlet(const UBlueprintExportCommandlet&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBlueprintExportCommandlet); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBlueprintExportCommandlet); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UBlueprintExportCommandlet) \
	NO_API virtual ~UBlueprintExportCommandlet();


#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_BlueprintExportCommandlet_h_30_PROLOG
#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_BlueprintExportCommandlet_h_33_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_BlueprintExportCommandlet_h_33_INCLASS_NO_PURE_DECLS \
	FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_BlueprintExportCommandlet_h_33_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UBlueprintExportCommandlet;

// ********** End Class UBlueprintExportCommandlet *************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_BlueprintExportCommandlet_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
