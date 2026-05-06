// Copyright 10 Chambers. All Rights Reserved.

#include "Commandlets/DeepDumpCommandlet.h"
#include "BlueprintExporterModule.h"
#include "Util/AtomicFileWriter.h"
#include "Util/CommandletLog.h"
#include "InventoryEmit/PerAssetEmit.h"
#include "TextExport/DeepDumpRenderer.h"
#include "TextExport/SmartObjectDefinitionDeepRenderer.h"
#include "TextExport/BehaviorTreeDeepRenderer.h"
#include "TextExport/DataTableDeepRenderer.h"
#include "TextExport/ChooserTableDeepRenderer.h"
#include "TextExport/EnvQueryDeepRenderer.h"
#include "TextExport/CustomizableObjectInstanceDeepRenderer.h"
#include "TextExport/CustomizableObjectDeepRenderer.h"
#include "TextExport/CustomizableObjectMacroLibraryDeepRenderer.h"
#include "Schema/BlueprintExportTypes.h"
#include "Schema/StateTreeExportTypes.h"
#include "Serialization/BlueprintSerializer.h"
#include "Serialization/StateTreeSerializer.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "AssetRegistry/AssetData.h"
#include "Engine/Blueprint.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"

#if WITH_STATETREE_SUPPORT
#include "StateTree.h"
#endif

#if WITH_SMARTOBJECTS_SUPPORT
#include "SmartObjectDefinition.h"
#endif

#if WITH_CHOOSER_SUPPORT
#include "Chooser.h"
#endif

#include "BehaviorTree/BehaviorTree.h"
#include "EnvironmentQuery/EnvQuery.h"

namespace
{
	// UBlueprint-family class name set lives in `InventoryEmit::
	// GetUBlueprintFamilyClassNames()` (single source of truth, hoisted to
	// avoid unity-build ODR collision with ProjectInventoryCommandlet.cpp's
	// identical anon-namespace copy).
	using BlueprintExporter::InventoryEmit::GetUBlueprintFamilyClassNames;

	bool IsStateTreeAssetClass(FName ClassName)
	{
		return ClassName == FName(TEXT("StateTree"));
	}

	bool IsSmartObjectDefinitionClass(FName ClassName)
	{
		return ClassName == FName(TEXT("SmartObjectDefinition"));
	}

	bool IsBehaviorTreeClass(FName ClassName)
	{
		return ClassName == FName(TEXT("BehaviorTree"));
	}

	bool IsDataTableClass(FName ClassName)
	{
		return ClassName == FName(TEXT("DataTable"));
	}

	bool IsChooserTableClass(FName ClassName)
	{
		return ClassName == FName(TEXT("ChooserTable"));
	}

	bool IsEnvQueryClass(FName ClassName)
	{
		return ClassName == FName(TEXT("EnvQuery"));
	}

	bool IsCustomizableObjectInstanceClass(FName ClassName)
	{
		return ClassName == FName(TEXT("CustomizableObjectInstance"));
	}

	bool IsCustomizableObjectClass(FName ClassName)
	{
		return ClassName == FName(TEXT("CustomizableObject"));
	}

	bool IsCustomizableObjectMacroLibraryClass(FName ClassName)
	{
		return ClassName == FName(TEXT("CustomizableObjectMacroLibrary"));
	}

	using BlueprintExporter::Util::LogLine;

	// Parse `-Asset=/Game/Path/Foo` or `-Asset=/Game/Path/Foo.Foo` down to a
	// package path (`/Game/Path/Foo`). Handles both "package path" and
	// "object path" inputs — users often paste either form.
	FString NormaliseAssetArg(const FString& Raw)
	{
		FString Trimmed = Raw;
		Trimmed.TrimQuotesInline();
		Trimmed.TrimStartAndEndInline();

		int32 DotIdx = INDEX_NONE;
		if (Trimmed.FindChar(TEXT('.'), DotIdx))
		{
			Trimmed = Trimmed.Left(DotIdx);
		}
		return Trimmed;
	}
}

UDeepDumpCommandlet::UDeepDumpCommandlet()
{
	IsClient = false;
	IsEditor = true;
	IsServer = false;
	LogToConsole = true;
}

int32 UDeepDumpCommandlet::Main(const FString& Params)
{
	LogLine(TEXT("INFO"), TEXT("Deep Dump Commandlet starting"));

	FString AssetArg;
	if (!FParse::Value(*Params, TEXT("Asset="), AssetArg))
	{
		LogLine(TEXT("ERROR"),
			TEXT("Usage: -run=DeepDump -Asset=/Game/Path/To/Asset -OutDir=<dir>"),
			/*bIsError=*/true);
		return 2;
	}
	const FString PackagePath = NormaliseAssetArg(AssetArg);
	if (PackagePath.IsEmpty() || !PackagePath.StartsWith(TEXT("/")))
	{
		LogLine(TEXT("ERROR"),
			FString::Printf(TEXT("Invalid -Asset value '%s' — expected a package path starting with `/` (e.g. `/Game/Path/Foo`)."),
				*AssetArg),
			/*bIsError=*/true);
		return 2;
	}

	FString OutDir;
	if (!FParse::Value(*Params, TEXT("OutDir="), OutDir))
	{
		LogLine(TEXT("ERROR"),
			TEXT("Missing -OutDir=<dir>. File is written as <OutDir>/<AssetName>.deep.md."),
			/*bIsError=*/true);
		return 2;
	}
	OutDir.TrimQuotesInline();

	LogLine(TEXT("INFO"),
		FString::Printf(TEXT("Asset=%s OutDir=%s"), *PackagePath, *OutDir));

	if (!IFileManager::Get().DirectoryExists(*OutDir))
	{
		IFileManager::Get().MakeDirectory(*OutDir, /*Tree=*/true);
	}

	FAssetRegistryModule& AssetRegistryModule =
		FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	LogLine(TEXT("INFO"), TEXT("Scanning asset registry (synchronous)..."));
	const double ScanStart = FPlatformTime::Seconds();
	AssetRegistry.SearchAllAssets(/*bSynchronousSearch=*/true);
	LogLine(TEXT("INFO"),
		FString::Printf(TEXT("Scan complete in %.2fs"), FPlatformTime::Seconds() - ScanStart));

	const FName PackageFName(*PackagePath);
	TArray<FAssetData> PackageAssets;
	AssetRegistry.GetAssetsByPackageName(PackageFName, PackageAssets);

	FAssetData PrimaryAsset;
	for (const FAssetData& AD : PackageAssets)
	{
		const FName ClassName = AD.AssetClassPath.GetAssetName();
		if (GetUBlueprintFamilyClassNames().Contains(ClassName)
			|| IsStateTreeAssetClass(ClassName)
			|| IsSmartObjectDefinitionClass(ClassName)
			|| IsBehaviorTreeClass(ClassName)
			|| IsDataTableClass(ClassName)
			|| IsChooserTableClass(ClassName)
			|| IsEnvQueryClass(ClassName)
			|| IsCustomizableObjectInstanceClass(ClassName)
			|| IsCustomizableObjectClass(ClassName)
			|| IsCustomizableObjectMacroLibraryClass(ClassName))
		{
			PrimaryAsset = AD;
			break;
		}
	}
	if (!PrimaryAsset.IsValid() && PackageAssets.Num() > 0)
	{
		PrimaryAsset = PackageAssets[0];
	}

	if (!PrimaryAsset.IsValid())
	{
		LogLine(TEXT("ERROR"),
			FString::Printf(TEXT("Asset not found: %s (registry has no entries in that package)"), *PackagePath),
			/*bIsError=*/true);
		return 2;
	}

	const FString AssetName = PrimaryAsset.AssetName.ToString();
	const FString OutPath = FPaths::Combine(OutDir, AssetName + TEXT(".deep.md"));
	const FName ClassName = PrimaryAsset.AssetClassPath.GetAssetName();

	const bool bIsUBP = GetUBlueprintFamilyClassNames().Contains(ClassName);
	const bool bIsST  = IsStateTreeAssetClass(ClassName);
	const bool bIsSO  = IsSmartObjectDefinitionClass(ClassName);
	const bool bIsBT  = IsBehaviorTreeClass(ClassName);
	const bool bIsDT  = IsDataTableClass(ClassName);
	const bool bIsCHT = IsChooserTableClass(ClassName);
	const bool bIsEQS = IsEnvQueryClass(ClassName);
	const bool bIsCOI  = IsCustomizableObjectInstanceClass(ClassName);
	const bool bIsCO   = IsCustomizableObjectClass(ClassName);
	const bool bIsCOML = IsCustomizableObjectMacroLibraryClass(ClassName);

	// If none of the typed dispatches match, we might still have a UDataAsset-derived
	// instance (e.g. `BP_CrowdCharacterDataAsset_C` — a BP-generated class that
	// extends UPrimaryDataAsset). These don't have a unique short class name the
	// registry can pre-filter on, so the check happens AFTER the asset is loaded.
	// Route is: typed dispatches first → DataAsset fallthrough → out-of-scope notice.
	UObject* AssetObject = PrimaryAsset.GetAsset();
	if (AssetObject == nullptr)
	{
		LogLine(TEXT("ERROR"),
			FString::Printf(TEXT("Asset load returned null for %s"), *PackagePath),
			/*bIsError=*/true);
		return 2;
	}

	const bool bIsDataAssetInstance =
		!bIsUBP && !bIsST && !bIsSO && !bIsBT && !bIsDT && !bIsCHT && !bIsEQS && !bIsCOI && !bIsCO && !bIsCOML
		&& AssetObject->IsA<UDataAsset>();

	if (!bIsUBP && !bIsST && !bIsSO && !bIsBT && !bIsDT && !bIsCHT && !bIsEQS && !bIsCOI && !bIsCO && !bIsCOML && !bIsDataAssetInstance)
	{
		const FString Notice = BlueprintExporter::DeepDump::RenderOutOfScopeNotice(
			AssetName, PackagePath, ClassName.ToString());
		if (!BlueprintExporterUtil::SaveStringAtomic(Notice, OutPath))
		{
			LogLine(TEXT("ERROR"),
				FString::Printf(TEXT("Failed to write notice to %s"), *OutPath),
				/*bIsError=*/true);
			return 2;
		}
		LogLine(TEXT("RESULT"),
			FString::Printf(TEXT("Out-of-scope class; notice written to %s"), *OutPath));
		LogLine(TEXT("STATUS"), TEXT("SUCCESS"));
		return 0;
	}

	FString Md;
	if (bIsUBP)
	{
		UBlueprint* Blueprint = Cast<UBlueprint>(AssetObject);
		if (Blueprint == nullptr)
		{
			LogLine(TEXT("ERROR"),
				FString::Printf(TEXT("Asset %s did not cast to UBlueprint (class %s)"),
					*PackagePath, *ClassName.ToString()),
				/*bIsError=*/true);
			return 2;
		}

		FBlueprintSerializer BPSerializer;
		FExportedBlueprint Exported;
		FString SerializeError;
		if (!BPSerializer.SerializeBlueprint(Blueprint, Exported, SerializeError))
		{
			LogLine(TEXT("ERROR"),
				FString::Printf(TEXT("SerializeBlueprint failed for %s: %s"),
					*PackagePath,
					SerializeError.IsEmpty() ? TEXT("(no error message)") : *SerializeError),
				/*bIsError=*/true);
			return 2;
		}
		// Brief §8: blank the timestamp the base serializer stamps — it drifts run-to-run.
		Exported.ExportInfo.ExportTimestamp.Reset();

		Md = BlueprintExporter::DeepDump::RenderBlueprintMarkdown(Exported);
	}
	else if (bIsST)
	{
#if WITH_STATETREE_SUPPORT
		UStateTree* StateTree = Cast<UStateTree>(AssetObject);
		if (StateTree == nullptr)
		{
			LogLine(TEXT("ERROR"),
				FString::Printf(TEXT("Asset %s did not cast to UStateTree (class %s)"),
					*PackagePath, *ClassName.ToString()),
				/*bIsError=*/true);
			return 2;
		}

		FStateTreeSerializer STSerializer;
		FExportedStateTree Exported;
		FString SerializeError;
		if (!STSerializer.SerializeStateTree(StateTree, Exported, SerializeError))
		{
			LogLine(TEXT("ERROR"),
				FString::Printf(TEXT("SerializeStateTree failed for %s: %s"),
					*PackagePath,
					SerializeError.IsEmpty() ? TEXT("(no error message)") : *SerializeError),
				/*bIsError=*/true);
			return 2;
		}
		Exported.ExportInfo.ExportTimestamp.Reset();

		Md = BlueprintExporter::DeepDump::RenderStateTreeMarkdown(Exported);
#else
		LogLine(TEXT("ERROR"),
			TEXT("StateTree support was not compiled into this plugin build."),
			/*bIsError=*/true);
		return 2;
#endif
	}
	else if (bIsSO)
	{
#if WITH_SMARTOBJECTS_SUPPORT
		// Renderer takes UObject* and casts internally; falls back to the
		// out-of-scope notice on type mismatch (defensive — shouldn't fire
		// here because we already checked the class name).
		Md = BlueprintExporter::DeepDump::RenderSmartObjectDefinitionMarkdown(AssetObject);
#else
		LogLine(TEXT("ERROR"),
			TEXT("SmartObjects support was not compiled into this plugin build."),
			/*bIsError=*/true);
		return 2;
#endif
	}
	else if (bIsBT)
	{
		// AIModule is a non-optional dep; renderer links unconditionally.
		// Same pattern as SO: cast happens inside, falls back to the
		// out-of-scope notice on type mismatch.
		Md = BlueprintExporter::DeepDump::RenderBehaviorTreeMarkdown(AssetObject);
	}
	else if (bIsDT)
	{
		// UDataTable lives in the Engine module — always linked.
		Md = BlueprintExporter::DeepDump::RenderDataTableMarkdown(AssetObject);
	}
	else if (bIsCHT)
	{
#if WITH_CHOOSER_SUPPORT
		Md = BlueprintExporter::DeepDump::RenderChooserTableMarkdown(AssetObject);
#else
		LogLine(TEXT("ERROR"),
			TEXT("Chooser support was not compiled into this plugin build."),
			/*bIsError=*/true);
		return 2;
#endif
	}
	else if (bIsEQS)
	{
		// AIModule is always linked — same as BT. Renderer casts inside.
		Md = BlueprintExporter::DeepDump::RenderEnvQueryMarkdown(AssetObject);
	}
	else if (bIsCOI)
	{
		// M29.1 — UCustomizableObjectInstance. Renderer dispatches by class-
		// name match (M29.6.2) and reads parameter overrides via reflection
		// on the runtime-resolved UClass + UScriptStruct; works on every
		// engine regardless of whether Mutable was linked at build time.
		Md = BlueprintExporter::DeepDump::RenderCustomizableObjectInstanceMarkdown(AssetObject);
	}
	else if (bIsCO)
	{
		// M29.2 — UCustomizableObject. Authoring-side Mutable asset: parameter
		// schema, states, components, compile options, and node graph. M29.6.3
		// ported this renderer to class-name dispatch + ProcessEvent-based
		// UFUNCTION reads so the CustomizableObject module no longer has to
		// be linked. Compiled-model / VersionId / BulkData are skipped per
		// the M29.0 policy (they regenerate on save and would destroy twin-
		// run byte-identity).
		Md = BlueprintExporter::DeepDump::RenderCustomizableObjectMarkdown(AssetObject);
	}
	else if (bIsCOML)
	{
		// M29.3 — UCustomizableObjectMacroLibrary. Reusable-macro asset:
		// walked via pure UE reflection (no Private Mutable header include).
		// Each macro gets its own section with Name / Description / I/O
		// variables / node-graph walk via the shared RenderEdGraphNodes.
		Md = BlueprintExporter::DeepDump::RenderCustomizableObjectMacroLibraryMarkdown(AssetObject);
	}
	else // bIsDataAssetInstance
	{
		// Load-time fallthrough: any UDataAsset-derived UObject gets its
		// instance-vs-class-CDO override table rendered. Values are flat
		// ExportTextItem_Direct blobs; a future slice can add recursive
		// instanced-subobject rendering if DOW hits a DA with heavy
		// Instanced / EditInlineNew nesting.
		Md = BlueprintExporter::DeepDump::RenderDataAssetInstanceMarkdown(AssetObject);
	}

	if (!BlueprintExporterUtil::SaveStringAtomic(Md, OutPath))
	{
		LogLine(TEXT("ERROR"),
			FString::Printf(TEXT("Failed to write deep dump to %s"), *OutPath),
			/*bIsError=*/true);
		return 2;
	}

	LogLine(TEXT("RESULT"),
		FString::Printf(TEXT("Wrote %s (%d bytes)"), *OutPath, Md.Len()));
	LogLine(TEXT("STATUS"), TEXT("SUCCESS"));
	return 0;
}
