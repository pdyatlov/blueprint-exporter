// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Commandlets/ProjectPluginsCommandlet.h"

#ifdef BLUEPRINTEXPORTER_ProjectPluginsCommandlet_generated_h
#error "ProjectPluginsCommandlet.generated.h already included, missing '#pragma once' in ProjectPluginsCommandlet.h"
#endif
#define BLUEPRINTEXPORTER_ProjectPluginsCommandlet_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UProjectPluginsCommandlet ************************************************
struct Z_Construct_UClass_UProjectPluginsCommandlet_Statics;
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UProjectPluginsCommandlet_NoRegister();

#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectPluginsCommandlet_h_43_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUProjectPluginsCommandlet(); \
	friend struct ::Z_Construct_UClass_UProjectPluginsCommandlet_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend BLUEPRINTEXPORTER_API UClass* ::Z_Construct_UClass_UProjectPluginsCommandlet_NoRegister(); \
public: \
	DECLARE_CLASS2(UProjectPluginsCommandlet, UCommandlet, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/BlueprintExporter"), Z_Construct_UClass_UProjectPluginsCommandlet_NoRegister) \
	DECLARE_SERIALIZER(UProjectPluginsCommandlet)


#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectPluginsCommandlet_h_43_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UProjectPluginsCommandlet(UProjectPluginsCommandlet&&) = delete; \
	UProjectPluginsCommandlet(const UProjectPluginsCommandlet&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UProjectPluginsCommandlet); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UProjectPluginsCommandlet); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UProjectPluginsCommandlet) \
	NO_API virtual ~UProjectPluginsCommandlet();


#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectPluginsCommandlet_h_40_PROLOG
#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectPluginsCommandlet_h_43_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectPluginsCommandlet_h_43_INCLASS_NO_PURE_DECLS \
	FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectPluginsCommandlet_h_43_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UProjectPluginsCommandlet;

// ********** End Class UProjectPluginsCommandlet **************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectPluginsCommandlet_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
