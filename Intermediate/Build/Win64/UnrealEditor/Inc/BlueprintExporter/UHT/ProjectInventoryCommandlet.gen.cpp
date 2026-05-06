// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Commandlets/ProjectInventoryCommandlet.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeProjectInventoryCommandlet() {}

// ********** Begin Cross Module References ********************************************************
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UProjectInventoryCommandlet();
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UProjectInventoryCommandlet_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCommandlet();
UPackage* Z_Construct_UPackage__Script_BlueprintExporter();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UProjectInventoryCommandlet **********************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UProjectInventoryCommandlet;
UClass* UProjectInventoryCommandlet::GetPrivateStaticClass()
{
	using TClass = UProjectInventoryCommandlet;
	if (!Z_Registration_Info_UClass_UProjectInventoryCommandlet.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("ProjectInventoryCommandlet"),
			Z_Registration_Info_UClass_UProjectInventoryCommandlet.InnerSingleton,
			StaticRegisterNativesUProjectInventoryCommandlet,
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
	return Z_Registration_Info_UClass_UProjectInventoryCommandlet.InnerSingleton;
}
UClass* Z_Construct_UClass_UProjectInventoryCommandlet_NoRegister()
{
	return UProjectInventoryCommandlet::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UProjectInventoryCommandlet_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Phase 1 of the project-inventory pipeline (see PROJECT_INVENTORY_BRIEF.md \xc2\xa7""4).\n *\n * Streams through every logic-bearing asset under the mount point, loads each\n * one, introspects it via the existing `FBlueprintSerializer`, and emits a\n * per-asset Markdown summary plus a structured `.meta.json` sidecar. Memory\n * is released between assets via `CollectGarbage` (brief \xc2\xa7""11A Option A).\n *\n * First slice scope: UBlueprint-family assets only (`UBlueprint`,\n * `UAnimBlueprint`, `UWidgetBlueprint`, `UControlRigBlueprint`). Specialized\n * sections (AnimBP state-machine detail, WidgetBP widget tree, BT/ST/GAS etc.)\n * and non-UBlueprint logic-bearing types (BehaviorTree, StateTree,\n * UserDefinedStruct, UserDefinedEnum, DataTable, SmartObject, Chooser,\n * PoseSearch) land in follow-on M3 slices.\n *\n * Usage:\n *   UnrealEditor-Cmd.exe <project> -run=ProjectInventory -OutDir=<dir>\n *                                  [-MountPoint=/Game]\n *                                  [-Filter=/Game/<subpath>]\n *                                  [-Resume]\n *                                  [-DeepDump]\n *                                  [-GcEvery=<N>]\n *\n * Output layout (brief \xc2\xa7""4):\n *   <OutDir>/Assets/Game/<SubPath>/<AssetName>.md\n *   <OutDir>/Assets/Game/<SubPath>/<AssetName>.meta.json\n *   <OutDir>/Assets/Game/<SubPath>/<AssetName>.deep.md   (with -DeepDump)\n *   <OutDir>/FAILED_LOADS.md        (only if any failed)\n *   <OutDir>/PARTIAL_LOADS.md       (only if any produced without full coverage)\n *\n * `-DeepDump`: enable Tier 2 sweep. Every processed asset emits a `.deep.md`\n * sibling \xe2\x80\x94 UBlueprint-family and UStateTree get the full per-node / per-task\n * detail via the shared `TextExport/DeepDumpRenderer`; other in-scope classes\n * get a short \"out-of-scope, see Tier 1\" notice so the sibling pattern holds\n * across the sweep.\n *\n * Resume semantics: `.meta.json` is written **after** `.md`, so its presence\n * is the \"asset fully emitted\" marker. `-Resume` skips any asset whose\n * `.meta.json` already exists and is non-empty.\n *\n * Exit codes:\n *   0 = success (framework completed; individual asset failures do not fail\n *       the run by default \xe2\x80\x94 they're aggregated into FAILED_LOADS.md)\n *   2 = runtime error (bad args, registry failure, or write failure)\n */" },
#endif
		{ "IncludePath", "Commandlets/ProjectInventoryCommandlet.h" },
		{ "ModuleRelativePath", "Public/Commandlets/ProjectInventoryCommandlet.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Phase 1 of the project-inventory pipeline (see PROJECT_INVENTORY_BRIEF.md \xc2\xa7""4).\n\nStreams through every logic-bearing asset under the mount point, loads each\none, introspects it via the existing `FBlueprintSerializer`, and emits a\nper-asset Markdown summary plus a structured `.meta.json` sidecar. Memory\nis released between assets via `CollectGarbage` (brief \xc2\xa7""11A Option A).\n\nFirst slice scope: UBlueprint-family assets only (`UBlueprint`,\n`UAnimBlueprint`, `UWidgetBlueprint`, `UControlRigBlueprint`). Specialized\nsections (AnimBP state-machine detail, WidgetBP widget tree, BT/ST/GAS etc.)\nand non-UBlueprint logic-bearing types (BehaviorTree, StateTree,\nUserDefinedStruct, UserDefinedEnum, DataTable, SmartObject, Chooser,\nPoseSearch) land in follow-on M3 slices.\n\nUsage:\n  UnrealEditor-Cmd.exe <project> -run=ProjectInventory -OutDir=<dir>\n                                 [-MountPoint=/Game]\n                                 [-Filter=/Game/<subpath>]\n                                 [-Resume]\n                                 [-DeepDump]\n                                 [-GcEvery=<N>]\n\nOutput layout (brief \xc2\xa7""4):\n  <OutDir>/Assets/Game/<SubPath>/<AssetName>.md\n  <OutDir>/Assets/Game/<SubPath>/<AssetName>.meta.json\n  <OutDir>/Assets/Game/<SubPath>/<AssetName>.deep.md   (with -DeepDump)\n  <OutDir>/FAILED_LOADS.md        (only if any failed)\n  <OutDir>/PARTIAL_LOADS.md       (only if any produced without full coverage)\n\n`-DeepDump`: enable Tier 2 sweep. Every processed asset emits a `.deep.md`\nsibling \xe2\x80\x94 UBlueprint-family and UStateTree get the full per-node / per-task\ndetail via the shared `TextExport/DeepDumpRenderer`; other in-scope classes\nget a short \"out-of-scope, see Tier 1\" notice so the sibling pattern holds\nacross the sweep.\n\nResume semantics: `.meta.json` is written **after** `.md`, so its presence\nis the \"asset fully emitted\" marker. `-Resume` skips any asset whose\n`.meta.json` already exists and is non-empty.\n\nExit codes:\n  0 = success (framework completed; individual asset failures do not fail\n      the run by default \xe2\x80\x94 they're aggregated into FAILED_LOADS.md)\n  2 = runtime error (bad args, registry failure, or write failure)" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UProjectInventoryCommandlet constinit property declarations **************
// ********** End Class UProjectInventoryCommandlet constinit property declarations ****************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UProjectInventoryCommandlet>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UProjectInventoryCommandlet_Statics
UObject* (*const Z_Construct_UClass_UProjectInventoryCommandlet_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UCommandlet,
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UProjectInventoryCommandlet_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UProjectInventoryCommandlet_Statics::ClassParams = {
	&UProjectInventoryCommandlet::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UProjectInventoryCommandlet_Statics::Class_MetaDataParams), Z_Construct_UClass_UProjectInventoryCommandlet_Statics::Class_MetaDataParams)
};
void UProjectInventoryCommandlet::StaticRegisterNativesUProjectInventoryCommandlet()
{
}
UClass* Z_Construct_UClass_UProjectInventoryCommandlet()
{
	if (!Z_Registration_Info_UClass_UProjectInventoryCommandlet.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UProjectInventoryCommandlet.OuterSingleton, Z_Construct_UClass_UProjectInventoryCommandlet_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UProjectInventoryCommandlet.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UProjectInventoryCommandlet);
UProjectInventoryCommandlet::~UProjectInventoryCommandlet() {}
// ********** End Class UProjectInventoryCommandlet ************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectInventoryCommandlet_h__Script_BlueprintExporter_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UProjectInventoryCommandlet, UProjectInventoryCommandlet::StaticClass, TEXT("UProjectInventoryCommandlet"), &Z_Registration_Info_UClass_UProjectInventoryCommandlet, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UProjectInventoryCommandlet), 2590988886U) },
	};
}; // Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectInventoryCommandlet_h__Script_BlueprintExporter_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectInventoryCommandlet_h__Script_BlueprintExporter_1640315027{
	TEXT("/Script/BlueprintExporter"),
	Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectInventoryCommandlet_h__Script_BlueprintExporter_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_ProjectInventoryCommandlet_h__Script_BlueprintExporter_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
