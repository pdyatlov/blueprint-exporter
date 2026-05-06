// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Commandlets/AggregateInventoryCommandlet.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeAggregateInventoryCommandlet() {}

// ********** Begin Cross Module References ********************************************************
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UAggregateInventoryCommandlet();
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UAggregateInventoryCommandlet_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCommandlet();
UPackage* Z_Construct_UPackage__Script_BlueprintExporter();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UAggregateInventoryCommandlet ********************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UAggregateInventoryCommandlet;
UClass* UAggregateInventoryCommandlet::GetPrivateStaticClass()
{
	using TClass = UAggregateInventoryCommandlet;
	if (!Z_Registration_Info_UClass_UAggregateInventoryCommandlet.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("AggregateInventoryCommandlet"),
			Z_Registration_Info_UClass_UAggregateInventoryCommandlet.InnerSingleton,
			StaticRegisterNativesUAggregateInventoryCommandlet,
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
	return Z_Registration_Info_UClass_UAggregateInventoryCommandlet.InnerSingleton;
}
UClass* Z_Construct_UClass_UAggregateInventoryCommandlet_NoRegister()
{
	return UAggregateInventoryCommandlet::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UAggregateInventoryCommandlet_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Phase 2 of the project-inventory pipeline (see PROJECT_INVENTORY_BRIEF.md \xc2\xa7""5).\n *\n * Reads `.meta.json` sidecars emitted by `ProjectInventoryCommandlet`, builds\n * project-wide rollups, and writes them as deterministic Markdown (plus a\n * Graphviz `.dot` for the dependency graph). No assets are loaded.\n *\n * First M4 slice emits:\n *   - INDEX.md              \xe2\x80\x94 class/folder counts + Run Scoreboard (brief \xc2\xa7""11A)\n *                             + pointers to the other reports\n *   - CLASS_TREE.md         \xe2\x80\x94 BPs grouped under native parent + BP\xe2\x86\x92""BP chains\n *   - DEPENDENCY_GRAPH.md   \xe2\x80\x94 per-asset hard/soft refs (in and out)\n *   - dependency_graph.dot  \xe2\x80\x94 same graph in Graphviz form\n *   - REPLICATION_MATRIX.md \xe2\x80\x94 every replicated variable across the project\n *                             (RPCs pending the M3.1 serializer widening)\n *   - HEALTH_REPORT.md      \xe2\x80\x94 coverage gaps, failed/partial loads\n *   - SCOREBOARD_BASELINE.json \xe2\x80\x94 persisted baseline for \xc2\xa7""11A scoreboard\n *\n * Domain overviews (AI / ANIM / UI / GAS / STRUCTS_ENUMS) depend on\n * non-UBlueprint `.meta.json` from a future `ProjectInventory` slice and are\n * deliberately out of this first commit.\n *\n * Usage:\n *   UnrealEditor-Cmd.exe <project> -run=AggregateInventory -OutDir=<dir>\n *                                  [-InDir=<dir>] [-ResetBaseline]\n *\n * If `-InDir` is omitted it defaults to `<OutDir>/Assets` (the exact tree\n * `ProjectInventory` writes under).\n *\n * Exit codes:\n *   0 = success\n *   2 = runtime error (bad args, no .meta.json found, or write failure)\n */" },
#endif
		{ "IncludePath", "Commandlets/AggregateInventoryCommandlet.h" },
		{ "ModuleRelativePath", "Public/Commandlets/AggregateInventoryCommandlet.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Phase 2 of the project-inventory pipeline (see PROJECT_INVENTORY_BRIEF.md \xc2\xa7""5).\n\nReads `.meta.json` sidecars emitted by `ProjectInventoryCommandlet`, builds\nproject-wide rollups, and writes them as deterministic Markdown (plus a\nGraphviz `.dot` for the dependency graph). No assets are loaded.\n\nFirst M4 slice emits:\n  - INDEX.md              \xe2\x80\x94 class/folder counts + Run Scoreboard (brief \xc2\xa7""11A)\n                            + pointers to the other reports\n  - CLASS_TREE.md         \xe2\x80\x94 BPs grouped under native parent + BP\xe2\x86\x92""BP chains\n  - DEPENDENCY_GRAPH.md   \xe2\x80\x94 per-asset hard/soft refs (in and out)\n  - dependency_graph.dot  \xe2\x80\x94 same graph in Graphviz form\n  - REPLICATION_MATRIX.md \xe2\x80\x94 every replicated variable across the project\n                            (RPCs pending the M3.1 serializer widening)\n  - HEALTH_REPORT.md      \xe2\x80\x94 coverage gaps, failed/partial loads\n  - SCOREBOARD_BASELINE.json \xe2\x80\x94 persisted baseline for \xc2\xa7""11A scoreboard\n\nDomain overviews (AI / ANIM / UI / GAS / STRUCTS_ENUMS) depend on\nnon-UBlueprint `.meta.json` from a future `ProjectInventory` slice and are\ndeliberately out of this first commit.\n\nUsage:\n  UnrealEditor-Cmd.exe <project> -run=AggregateInventory -OutDir=<dir>\n                                 [-InDir=<dir>] [-ResetBaseline]\n\nIf `-InDir` is omitted it defaults to `<OutDir>/Assets` (the exact tree\n`ProjectInventory` writes under).\n\nExit codes:\n  0 = success\n  2 = runtime error (bad args, no .meta.json found, or write failure)" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UAggregateInventoryCommandlet constinit property declarations ************
// ********** End Class UAggregateInventoryCommandlet constinit property declarations **************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAggregateInventoryCommandlet>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UAggregateInventoryCommandlet_Statics
UObject* (*const Z_Construct_UClass_UAggregateInventoryCommandlet_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UCommandlet,
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAggregateInventoryCommandlet_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAggregateInventoryCommandlet_Statics::ClassParams = {
	&UAggregateInventoryCommandlet::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAggregateInventoryCommandlet_Statics::Class_MetaDataParams), Z_Construct_UClass_UAggregateInventoryCommandlet_Statics::Class_MetaDataParams)
};
void UAggregateInventoryCommandlet::StaticRegisterNativesUAggregateInventoryCommandlet()
{
}
UClass* Z_Construct_UClass_UAggregateInventoryCommandlet()
{
	if (!Z_Registration_Info_UClass_UAggregateInventoryCommandlet.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAggregateInventoryCommandlet.OuterSingleton, Z_Construct_UClass_UAggregateInventoryCommandlet_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAggregateInventoryCommandlet.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UAggregateInventoryCommandlet);
UAggregateInventoryCommandlet::~UAggregateInventoryCommandlet() {}
// ********** End Class UAggregateInventoryCommandlet **********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_AggregateInventoryCommandlet_h__Script_BlueprintExporter_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAggregateInventoryCommandlet, UAggregateInventoryCommandlet::StaticClass, TEXT("UAggregateInventoryCommandlet"), &Z_Registration_Info_UClass_UAggregateInventoryCommandlet, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAggregateInventoryCommandlet), 141114198U) },
	};
}; // Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_AggregateInventoryCommandlet_h__Script_BlueprintExporter_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_AggregateInventoryCommandlet_h__Script_BlueprintExporter_487865990{
	TEXT("/Script/BlueprintExporter"),
	Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_AggregateInventoryCommandlet_h__Script_BlueprintExporter_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_AggregateInventoryCommandlet_h__Script_BlueprintExporter_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
