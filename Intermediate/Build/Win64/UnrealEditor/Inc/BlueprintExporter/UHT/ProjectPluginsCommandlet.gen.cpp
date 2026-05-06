// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Commandlets/ProjectPluginsCommandlet.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeProjectPluginsCommandlet() {}

// ********** Begin Cross Module References ********************************************************
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UProjectPluginsCommandlet();
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UProjectPluginsCommandlet_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCommandlet();
UPackage* Z_Construct_UPackage__Script_BlueprintExporter();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UProjectPluginsCommandlet ************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UProjectPluginsCommandlet;
UClass* UProjectPluginsCommandlet::GetPrivateStaticClass()
{
	using TClass = UProjectPluginsCommandlet;
	if (!Z_Registration_Info_UClass_UProjectPluginsCommandlet.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("ProjectPluginsCommandlet"),
			Z_Registration_Info_UClass_UProjectPluginsCommandlet.InnerSingleton,
			StaticRegisterNativesUProjectPluginsCommandlet,
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
	return Z_Registration_Info_UClass_UProjectPluginsCommandlet.InnerSingleton;
}
UClass* Z_Construct_UClass_UProjectPluginsCommandlet_NoRegister()
{
	return UProjectPluginsCommandlet::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UProjectPluginsCommandlet_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * M7 P0 of the project-inventory pipeline \xe2\x80\x94 see PROJECT_INVENTORY_BRIEF.md\n * and WIP_INVENTORY.md for the full scope.\n *\n * Complements ProjectManifest / ProjectInventory / AggregateInventory (which\n * all operate on `/Game` content) by covering the *project plugins* shipped\n * alongside the game. Without this, native features that plugins register \xe2\x80\x94\n * e.g. `CoverEQS` shipping a `UEnvQueryTest_TraceDistance` \xe2\x80\x94 are invisible\n * to static analysis of the output tree.\n *\n * P0 captures uplugin metadata only:\n *   - `PLUGINS.md`                       \xe2\x80\x94 top-level rollup table.\n *   - `PluginInventory/<Name>.md`        \xe2\x80\x94 per-plugin human doc.\n *   - `PluginInventory/<Name>.meta.json` \xe2\x80\x94 per-plugin structured sidecar.\n *\n * P1 extends the commandlet to walk `GetDerivedClasses()` against a curated\n * set of AI/gameplay base classes and populate `NativeTypes[]` per plugin.\n * Schema is pre-shaped for P1 so the sidecar format stays stable.\n *\n * Plugin scope: `EPluginType::Project` only. Engine plugins are out of scope\n * (Epic ships documentation for those). Disabled plugins are included with\n * empty `NativeTypes[]`; their uplugin metadata is read off disk.\n *\n * Usage:\n *   UnrealEditor-Cmd.exe <project> -run=ProjectPlugins -OutDir=<dir>\n *                                  [-Include=<regex>] [-Exclude=<regex>]\n *\n * Exit codes:\n *   0 = success (all plugins written, or filter matched zero plugins)\n *   2 = runtime error (bad args, plugin manager not available, or write failure)\n */" },
#endif
		{ "IncludePath", "Commandlets/ProjectPluginsCommandlet.h" },
		{ "ModuleRelativePath", "Public/Commandlets/ProjectPluginsCommandlet.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "M7 P0 of the project-inventory pipeline \xe2\x80\x94 see PROJECT_INVENTORY_BRIEF.md\nand WIP_INVENTORY.md for the full scope.\n\nComplements ProjectManifest / ProjectInventory / AggregateInventory (which\nall operate on `/Game` content) by covering the *project plugins* shipped\nalongside the game. Without this, native features that plugins register \xe2\x80\x94\ne.g. `CoverEQS` shipping a `UEnvQueryTest_TraceDistance` \xe2\x80\x94 are invisible\nto static analysis of the output tree.\n\nP0 captures uplugin metadata only:\n  - `PLUGINS.md`                       \xe2\x80\x94 top-level rollup table.\n  - `PluginInventory/<Name>.md`        \xe2\x80\x94 per-plugin human doc.\n  - `PluginInventory/<Name>.meta.json` \xe2\x80\x94 per-plugin structured sidecar.\n\nP1 extends the commandlet to walk `GetDerivedClasses()` against a curated\nset of AI/gameplay base classes and populate `NativeTypes[]` per plugin.\nSchema is pre-shaped for P1 so the sidecar format stays stable.\n\nPlugin scope: `EPluginType::Project` only. Engine plugins are out of scope\n(Epic ships documentation for those). Disabled plugins are included with\nempty `NativeTypes[]`; their uplugin metadata is read off disk.\n\nUsage:\n  UnrealEditor-Cmd.exe <project> -run=ProjectPlugins -OutDir=<dir>\n                                 [-Include=<regex>] [-Exclude=<regex>]\n\nExit codes:\n  0 = success (all plugins written, or filter matched zero plugins)\n  2 = runtime error (bad args, plugin manager not available, or write failure)" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UProjectPluginsCommandlet constinit property declarations ****************
// ********** End Class UProjectPluginsCommandlet constinit property declarations ******************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UProjectPluginsCommandlet>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UProjectPluginsCommandlet_Statics
UObject* (*const Z_Construct_UClass_UProjectPluginsCommandlet_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UCommandlet,
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UProjectPluginsCommandlet_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UProjectPluginsCommandlet_Statics::ClassParams = {
	&UProjectPluginsCommandlet::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x001000A8u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UProjectPluginsCommandlet_Statics::Class_MetaDataParams), Z_Construct_UClass_UProjectPluginsCommandlet_Statics::Class_MetaDataParams)
};
void UProjectPluginsCommandlet::StaticRegisterNativesUProjectPluginsCommandlet()
{
}
UClass* Z_Construct_UClass_UProjectPluginsCommandlet()
{
	if (!Z_Registration_Info_UClass_UProjectPluginsCommandlet.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UProjectPluginsCommandlet.OuterSingleton, Z_Construct_UClass_UProjectPluginsCommandlet_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UProjectPluginsCommandlet.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UProjectPluginsCommandlet);
UProjectPluginsCommandlet::~UProjectPluginsCommandlet() {}
// ********** End Class UProjectPluginsCommandlet **************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectPluginsCommandlet_h__Script_BlueprintExporter_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UProjectPluginsCommandlet, UProjectPluginsCommandlet::StaticClass, TEXT("UProjectPluginsCommandlet"), &Z_Registration_Info_UClass_UProjectPluginsCommandlet, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UProjectPluginsCommandlet), 1639496509U) },
	};
}; // Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectPluginsCommandlet_h__Script_BlueprintExporter_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectPluginsCommandlet_h__Script_BlueprintExporter_489440179{
	TEXT("/Script/BlueprintExporter"),
	Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectPluginsCommandlet_h__Script_BlueprintExporter_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectPluginsCommandlet_h__Script_BlueprintExporter_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
