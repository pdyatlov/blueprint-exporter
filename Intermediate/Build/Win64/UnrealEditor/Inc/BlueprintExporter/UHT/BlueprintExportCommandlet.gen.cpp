// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Commandlets/BlueprintExportCommandlet.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeBlueprintExportCommandlet() {}

// ********** Begin Cross Module References ********************************************************
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UBlueprintExportCommandlet();
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UBlueprintExportCommandlet_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCommandlet();
UPackage* Z_Construct_UPackage__Script_BlueprintExporter();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UBlueprintExportCommandlet ***********************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UBlueprintExportCommandlet;
UClass* UBlueprintExportCommandlet::GetPrivateStaticClass()
{
	using TClass = UBlueprintExportCommandlet;
	if (!Z_Registration_Info_UClass_UBlueprintExportCommandlet.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("BlueprintExportCommandlet"),
			Z_Registration_Info_UClass_UBlueprintExportCommandlet.InnerSingleton,
			StaticRegisterNativesUBlueprintExportCommandlet,
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
	return Z_Registration_Info_UClass_UBlueprintExportCommandlet.InnerSingleton;
}
UClass* Z_Construct_UClass_UBlueprintExportCommandlet_NoRegister()
{
	return UBlueprintExportCommandlet::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBlueprintExportCommandlet_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Commandlet for exporting Blueprints in headless/CI mode.\n *\n * Usage:\n *   UE5Editor.exe <project> -run=BlueprintExport -Paths=\"/Game/...\" -Out=\"OutputDir\" [options]\n *\n * Options:\n *   -Paths=<path>       Asset path filter (supports wildcards)\n *   -Out=<dir>          Output directory for exported files\n *   -IncludeDeps        Include Blueprint dependencies\n *   -Depth=<n>          Dependency resolution depth (default: 1)\n *   -NoText             Skip human-readable text export\n *   -NoDigest           Skip digest/metrics JSON export\n *   -Compact            Use compact JSON (no pretty printing)\n *   -IncludeStateTrees  Also export State Tree assets found in the search paths\n *\n * Exit Codes:\n *   0 = Success\n *   1 = Validation failed\n *   2 = Runtime error\n */" },
#endif
		{ "IncludePath", "Commandlets/BlueprintExportCommandlet.h" },
		{ "ModuleRelativePath", "Public/Commandlets/BlueprintExportCommandlet.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Commandlet for exporting Blueprints in headless/CI mode.\n\nUsage:\n  UE5Editor.exe <project> -run=BlueprintExport -Paths=\"/Game/...\" -Out=\"OutputDir\" [options]\n\nOptions:\n  -Paths=<path>       Asset path filter (supports wildcards)\n  -Out=<dir>          Output directory for exported files\n  -IncludeDeps        Include Blueprint dependencies\n  -Depth=<n>          Dependency resolution depth (default: 1)\n  -NoText             Skip human-readable text export\n  -NoDigest           Skip digest/metrics JSON export\n  -Compact            Use compact JSON (no pretty printing)\n  -IncludeStateTrees  Also export State Tree assets found in the search paths\n\nExit Codes:\n  0 = Success\n  1 = Validation failed\n  2 = Runtime error" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UBlueprintExportCommandlet constinit property declarations ***************
// ********** End Class UBlueprintExportCommandlet constinit property declarations *****************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBlueprintExportCommandlet>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UBlueprintExportCommandlet_Statics
UObject* (*const Z_Construct_UClass_UBlueprintExportCommandlet_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UCommandlet,
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBlueprintExportCommandlet_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBlueprintExportCommandlet_Statics::ClassParams = {
	&UBlueprintExportCommandlet::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBlueprintExportCommandlet_Statics::Class_MetaDataParams), Z_Construct_UClass_UBlueprintExportCommandlet_Statics::Class_MetaDataParams)
};
void UBlueprintExportCommandlet::StaticRegisterNativesUBlueprintExportCommandlet()
{
}
UClass* Z_Construct_UClass_UBlueprintExportCommandlet()
{
	if (!Z_Registration_Info_UClass_UBlueprintExportCommandlet.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBlueprintExportCommandlet.OuterSingleton, Z_Construct_UClass_UBlueprintExportCommandlet_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBlueprintExportCommandlet.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UBlueprintExportCommandlet);
UBlueprintExportCommandlet::~UBlueprintExportCommandlet() {}
// ********** End Class UBlueprintExportCommandlet *************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_BlueprintExportCommandlet_h__Script_BlueprintExporter_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBlueprintExportCommandlet, UBlueprintExportCommandlet::StaticClass, TEXT("UBlueprintExportCommandlet"), &Z_Registration_Info_UClass_UBlueprintExportCommandlet, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBlueprintExportCommandlet), 3173587205U) },
	};
}; // Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_BlueprintExportCommandlet_h__Script_BlueprintExporter_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_BlueprintExportCommandlet_h__Script_BlueprintExporter_1325634373{
	TEXT("/Script/BlueprintExporter"),
	Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_BlueprintExportCommandlet_h__Script_BlueprintExporter_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_BlueprintExportCommandlet_h__Script_BlueprintExporter_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
