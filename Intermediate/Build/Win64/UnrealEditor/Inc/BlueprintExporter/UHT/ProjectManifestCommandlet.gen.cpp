// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Commandlets/ProjectManifestCommandlet.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeProjectManifestCommandlet() {}

// ********** Begin Cross Module References ********************************************************
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UProjectManifestCommandlet();
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UProjectManifestCommandlet_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCommandlet();
UPackage* Z_Construct_UPackage__Script_BlueprintExporter();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UProjectManifestCommandlet ***********************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UProjectManifestCommandlet;
UClass* UProjectManifestCommandlet::GetPrivateStaticClass()
{
	using TClass = UProjectManifestCommandlet;
	if (!Z_Registration_Info_UClass_UProjectManifestCommandlet.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("ProjectManifestCommandlet"),
			Z_Registration_Info_UClass_UProjectManifestCommandlet.InnerSingleton,
			StaticRegisterNativesUProjectManifestCommandlet,
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
	return Z_Registration_Info_UClass_UProjectManifestCommandlet.InnerSingleton;
}
UClass* Z_Construct_UClass_UProjectManifestCommandlet_NoRegister()
{
	return UProjectManifestCommandlet::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UProjectManifestCommandlet_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Phase 0 of the project-inventory pipeline (see PROJECT_INVENTORY_BRIEF.md \xc2\xa7""3).\n *\n * Performs an FAssetRegistry-only scan of the target mount point and writes a\n * single MANIFEST.md summarizing what the project contains. No assets are\n * loaded; no UObject graphs are constructed. This is the cheap pre-flight\n * before the heavier ProjectInventory pass.\n *\n * Usage:\n *   UnrealEditor-Cmd.exe <project> -run=ProjectManifest -OutDir=<dir>\n *                                  [-MountPoint=/Game] [-TopN=50]\n *\n * Exit codes:\n *   0 = success\n *   2 = runtime error (bad args, scan failure, or write failure)\n */" },
#endif
		{ "IncludePath", "Commandlets/ProjectManifestCommandlet.h" },
		{ "ModuleRelativePath", "Public/Commandlets/ProjectManifestCommandlet.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Phase 0 of the project-inventory pipeline (see PROJECT_INVENTORY_BRIEF.md \xc2\xa7""3).\n\nPerforms an FAssetRegistry-only scan of the target mount point and writes a\nsingle MANIFEST.md summarizing what the project contains. No assets are\nloaded; no UObject graphs are constructed. This is the cheap pre-flight\nbefore the heavier ProjectInventory pass.\n\nUsage:\n  UnrealEditor-Cmd.exe <project> -run=ProjectManifest -OutDir=<dir>\n                                 [-MountPoint=/Game] [-TopN=50]\n\nExit codes:\n  0 = success\n  2 = runtime error (bad args, scan failure, or write failure)" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UProjectManifestCommandlet constinit property declarations ***************
// ********** End Class UProjectManifestCommandlet constinit property declarations *****************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UProjectManifestCommandlet>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UProjectManifestCommandlet_Statics
UObject* (*const Z_Construct_UClass_UProjectManifestCommandlet_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UCommandlet,
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UProjectManifestCommandlet_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UProjectManifestCommandlet_Statics::ClassParams = {
	&UProjectManifestCommandlet::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UProjectManifestCommandlet_Statics::Class_MetaDataParams), Z_Construct_UClass_UProjectManifestCommandlet_Statics::Class_MetaDataParams)
};
void UProjectManifestCommandlet::StaticRegisterNativesUProjectManifestCommandlet()
{
}
UClass* Z_Construct_UClass_UProjectManifestCommandlet()
{
	if (!Z_Registration_Info_UClass_UProjectManifestCommandlet.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UProjectManifestCommandlet.OuterSingleton, Z_Construct_UClass_UProjectManifestCommandlet_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UProjectManifestCommandlet.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UProjectManifestCommandlet);
UProjectManifestCommandlet::~UProjectManifestCommandlet() {}
// ********** End Class UProjectManifestCommandlet *************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectManifestCommandlet_h__Script_BlueprintExporter_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UProjectManifestCommandlet, UProjectManifestCommandlet::StaticClass, TEXT("UProjectManifestCommandlet"), &Z_Registration_Info_UClass_UProjectManifestCommandlet, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UProjectManifestCommandlet), 1091246530U) },
	};
}; // Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectManifestCommandlet_h__Script_BlueprintExporter_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectManifestCommandlet_h__Script_BlueprintExporter_4164086910{
	TEXT("/Script/BlueprintExporter"),
	Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectManifestCommandlet_h__Script_BlueprintExporter_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectManifestCommandlet_h__Script_BlueprintExporter_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
