// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Commandlets/ProjectManifestCommandlet.h"

#ifdef BLUEPRINTEXPORTER_ProjectManifestCommandlet_generated_h
#error "ProjectManifestCommandlet.generated.h already included, missing '#pragma once' in ProjectManifestCommandlet.h"
#endif
#define BLUEPRINTEXPORTER_ProjectManifestCommandlet_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UProjectManifestCommandlet ***********************************************
struct Z_Construct_UClass_UProjectManifestCommandlet_Statics;
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UProjectManifestCommandlet_NoRegister();

#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectManifestCommandlet_h_28_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUProjectManifestCommandlet(); \
	friend struct ::Z_Construct_UClass_UProjectManifestCommandlet_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend BLUEPRINTEXPORTER_API UClass* ::Z_Construct_UClass_UProjectManifestCommandlet_NoRegister(); \
public: \
	DECLARE_CLASS2(UProjectManifestCommandlet, UCommandlet, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/BlueprintExporter"), Z_Construct_UClass_UProjectManifestCommandlet_NoRegister) \
	DECLARE_SERIALIZER(UProjectManifestCommandlet)


#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectManifestCommandlet_h_28_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UProjectManifestCommandlet(UProjectManifestCommandlet&&) = delete; \
	UProjectManifestCommandlet(const UProjectManifestCommandlet&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UProjectManifestCommandlet); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UProjectManifestCommandlet); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UProjectManifestCommandlet) \
	NO_API virtual ~UProjectManifestCommandlet();


#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectManifestCommandlet_h_25_PROLOG
#define FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectManifestCommandlet_h_28_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectManifestCommandlet_h_28_INCLASS_NO_PURE_DECLS \
	FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectManifestCommandlet_h_28_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UProjectManifestCommandlet;

// ********** End Class UProjectManifestCommandlet *************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectManifestCommandlet_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
