// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Commandlets/DeepDumpCommandlet.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeDeepDumpCommandlet() {}

// ********** Begin Cross Module References ********************************************************
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UDeepDumpCommandlet();
BLUEPRINTEXPORTER_API UClass* Z_Construct_UClass_UDeepDumpCommandlet_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCommandlet();
UPackage* Z_Construct_UPackage__Script_BlueprintExporter();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UDeepDumpCommandlet ******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UDeepDumpCommandlet;
UClass* UDeepDumpCommandlet::GetPrivateStaticClass()
{
	using TClass = UDeepDumpCommandlet;
	if (!Z_Registration_Info_UClass_UDeepDumpCommandlet.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("DeepDumpCommandlet"),
			Z_Registration_Info_UClass_UDeepDumpCommandlet.InnerSingleton,
			StaticRegisterNativesUDeepDumpCommandlet,
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
	return Z_Registration_Info_UClass_UDeepDumpCommandlet.InnerSingleton;
}
UClass* Z_Construct_UClass_UDeepDumpCommandlet_NoRegister()
{
	return UDeepDumpCommandlet::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UDeepDumpCommandlet_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Tier 2 of the project-inventory pipeline (see PROJECT_INVENTORY_BRIEF.md \xc2\xa7""6).\n *\n * On-demand single-asset deep dump. Where Phase 1 (ProjectInventory) emits a\n * Tier 1 summary per asset \xe2\x80\x94 variable list, function signatures, graph node\n * counts \xe2\x80\x94 Tier 2 emits the full graph detail: every node in every graph with\n * class / title / pin layout / default values / link list, per-state AnimGraph\n * node dumps for AnimBP state machines, and per-transition rule graph dumps.\n *\n * First slice scope: UBlueprint-family assets only (`UBlueprint`,\n * `UAnimBlueprint`, `UWidgetBlueprint`, `UControlRigBlueprint`). Other\n * logic-bearing classes (BT / ST / DT / UDS / UDE / SmartObject / Chooser /\n * PoseSearch / EnvQuery) already render near-complete detail in their typed\n * Tier 1 handlers (M3.1 \xe2\x86\x92 M3.3), so they print an explanatory notice pointing\n * at the Tier 1 `.md` + `.meta.json` and exit 0.\n *\n * Usage:\n *   UnrealEditor-Cmd.exe <project> -run=DeepDump\n *                                  -Asset=/Game/Path/To/AssetName\n *                                  -OutDir=<dir>\n *\n * Output: `<OutDir>/<AssetName>.deep.md` written via atomic `.tmp` + rename.\n *\n * Exit codes:\n *   0 = success (file written, or asset class is out-of-scope and notice emitted)\n *   2 = runtime error (bad args, asset not found, serializer failure, or write failure)\n */" },
#endif
		{ "IncludePath", "Commandlets/DeepDumpCommandlet.h" },
		{ "ModuleRelativePath", "Public/Commandlets/DeepDumpCommandlet.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Tier 2 of the project-inventory pipeline (see PROJECT_INVENTORY_BRIEF.md \xc2\xa7""6).\n\nOn-demand single-asset deep dump. Where Phase 1 (ProjectInventory) emits a\nTier 1 summary per asset \xe2\x80\x94 variable list, function signatures, graph node\ncounts \xe2\x80\x94 Tier 2 emits the full graph detail: every node in every graph with\nclass / title / pin layout / default values / link list, per-state AnimGraph\nnode dumps for AnimBP state machines, and per-transition rule graph dumps.\n\nFirst slice scope: UBlueprint-family assets only (`UBlueprint`,\n`UAnimBlueprint`, `UWidgetBlueprint`, `UControlRigBlueprint`). Other\nlogic-bearing classes (BT / ST / DT / UDS / UDE / SmartObject / Chooser /\nPoseSearch / EnvQuery) already render near-complete detail in their typed\nTier 1 handlers (M3.1 \xe2\x86\x92 M3.3), so they print an explanatory notice pointing\nat the Tier 1 `.md` + `.meta.json` and exit 0.\n\nUsage:\n  UnrealEditor-Cmd.exe <project> -run=DeepDump\n                                 -Asset=/Game/Path/To/AssetName\n                                 -OutDir=<dir>\n\nOutput: `<OutDir>/<AssetName>.deep.md` written via atomic `.tmp` + rename.\n\nExit codes:\n  0 = success (file written, or asset class is out-of-scope and notice emitted)\n  2 = runtime error (bad args, asset not found, serializer failure, or write failure)" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UDeepDumpCommandlet constinit property declarations **********************
// ********** End Class UDeepDumpCommandlet constinit property declarations ************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDeepDumpCommandlet>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UDeepDumpCommandlet_Statics
UObject* (*const Z_Construct_UClass_UDeepDumpCommandlet_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UCommandlet,
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintExporter,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDeepDumpCommandlet_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UDeepDumpCommandlet_Statics::ClassParams = {
	&UDeepDumpCommandlet::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UDeepDumpCommandlet_Statics::Class_MetaDataParams), Z_Construct_UClass_UDeepDumpCommandlet_Statics::Class_MetaDataParams)
};
void UDeepDumpCommandlet::StaticRegisterNativesUDeepDumpCommandlet()
{
}
UClass* Z_Construct_UClass_UDeepDumpCommandlet()
{
	if (!Z_Registration_Info_UClass_UDeepDumpCommandlet.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDeepDumpCommandlet.OuterSingleton, Z_Construct_UClass_UDeepDumpCommandlet_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UDeepDumpCommandlet.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDeepDumpCommandlet);
UDeepDumpCommandlet::~UDeepDumpCommandlet() {}
// ********** End Class UDeepDumpCommandlet ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_DeepDumpCommandlet_h__Script_BlueprintExporter_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDeepDumpCommandlet, UDeepDumpCommandlet::StaticClass, TEXT("UDeepDumpCommandlet"), &Z_Registration_Info_UClass_UDeepDumpCommandlet, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDeepDumpCommandlet), 3425185816U) },
	};
}; // Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_DeepDumpCommandlet_h__Script_BlueprintExporter_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_DeepDumpCommandlet_h__Script_BlueprintExporter_997155561{
	TEXT("/Script/BlueprintExporter"),
	Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_DeepDumpCommandlet_h__Script_BlueprintExporter_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_game_Plugins_blueprint_exporter_Source_BlueprintExporter_Public_Commandlets_DeepDumpCommandlet_h__Script_BlueprintExporter_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
