// Copyright Ten Chambers. All Rights Reserved.

#include "AssetReExporter.h"

#include "AssetRegistry/AssetData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "BlueprintExporterModule.h"
#include "Engine/Blueprint.h"
#include "HAL/FileManager.h"
#include "InventoryEmit/PerAssetEmit.h"
#include "Misc/Paths.h"
#include "Schema/BlueprintExportTypes.h"
#include "Serialization/BlueprintSerializer.h"
#include "TextExport/DeepDumpRenderer.h"
#include "Util/AtomicFileWriter.h"

#if WITH_STATETREE_SUPPORT
#include "StateTree.h"
#endif

namespace BlueprintExporter::ReExport
{
	const TCHAR* ToString(EReExportStatus Status)
	{
		switch (Status)
		{
		case EReExportStatus::Ok:              return TEXT("ok");
		case EReExportStatus::Unsupported:     return TEXT("unsupported");
		case EReExportStatus::LoadFailed:      return TEXT("load_failed");
		case EReExportStatus::SerializeFailed: return TEXT("serialize_failed");
		case EReExportStatus::WriteFailed:     return TEXT("write_failed");
		}
		return TEXT("unknown");
	}

	namespace
	{
		// UBlueprint-family short class names match the inventory commandlet's
		// in-scope Tier 2 set (Blueprint, AnimBlueprint, WidgetBlueprint,
		// ControlRigBlueprint). Matching here only drives re-export routing —
		// an unknown BP subclass still falls through Cast<UBlueprint>() below
		// and gets handled.
		bool IsUBlueprintFamily(const FAssetData& AD)
		{
			const FName ClassName = AD.AssetClassPath.GetAssetName();
			return ClassName == FName(TEXT("Blueprint"))
				|| ClassName == FName(TEXT("AnimBlueprint"))
				|| ClassName == FName(TEXT("WidgetBlueprint"))
				|| ClassName == FName(TEXT("ControlRigBlueprint"));
		}

		FAssetData FindPrimaryAsset(const FString& PackageName)
		{
			FAssetRegistryModule& AssetRegistryModule =
				FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
			IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

			TArray<FAssetData> PackageAssets;
			AssetRegistry.GetAssetsByPackageName(FName(*PackageName), PackageAssets);

			// Prefer a UBP or StateTree entry when the package has siblings
			// (e.g. Blueprint + BlueprintGeneratedClass). Fall back to the
			// first asset if nothing matches.
			for (const FAssetData& AD : PackageAssets)
			{
				const FName ClassName = AD.AssetClassPath.GetAssetName();
				if (IsUBlueprintFamily(AD) || ClassName == FName(TEXT("StateTree")))
				{
					return AD;
				}
			}
			if (PackageAssets.Num() > 0)
			{
				return PackageAssets[0];
			}
			return FAssetData();
		}

		// M27.3.1 — now delegates to InventoryEmit::RenderBlueprintMarkdown +
		// InventoryEmit::WriteMetaJson. Pre-M27.3.1 the re-export wrote a
		// placeholder `.md` pointing at `get_asset_deep_dump` and a stub
		// coverage block; both are now canonical (byte-identical to the
		// commandlet's Phase 1 sweep output).
		bool ReExportBlueprint(
			UBlueprint* Blueprint,
			const FString& MdPath,
			const FString& MetaPath,
			const FString& DeepPath,
			FReExportResult& Out)
		{
			FBlueprintSerializer Serializer;
			FExportedBlueprint Exported;
			FString SerializeError;
			if (!Serializer.SerializeBlueprint(Blueprint, Exported, SerializeError))
			{
				Out.Status = EReExportStatus::SerializeFailed;
				Out.Error = SerializeError.IsEmpty()
					? FString(TEXT("SerializeBlueprint returned false"))
					: SerializeError;
				return false;
			}
			// Brief §8 determinism: no run-drifting fields in file contents.
			Exported.ExportInfo.ExportTimestamp.Reset();

			const FString Md = InventoryEmit::RenderBlueprintMarkdown(Exported);
			if (!BlueprintExporterUtil::SaveStringAtomic(Md, MdPath))
			{
				Out.Status = EReExportStatus::WriteFailed;
				Out.Error = FString::Printf(TEXT("failed to write %s"), *MdPath);
				return false;
			}
			Out.WrittenFiles.Add(MdPath);

			int32 OverallPct = 100;
			if (!InventoryEmit::WriteMetaJson(Exported, MetaPath, OverallPct))
			{
				Out.Status = EReExportStatus::WriteFailed;
				Out.Error = FString::Printf(TEXT("failed to write %s"), *MetaPath);
				return false;
			}
			Out.WrittenFiles.Add(MetaPath);

			const FString DeepMd =
				DeepDump::RenderBlueprintMarkdown(Exported);
			if (!BlueprintExporterUtil::SaveStringAtomic(DeepMd, DeepPath))
			{
				Out.Status = EReExportStatus::WriteFailed;
				Out.Error = FString::Printf(TEXT("failed to write %s"), *DeepPath);
				return false;
			}
			Out.WrittenFiles.Add(DeepPath);

			Out.Status = EReExportStatus::Ok;
			return true;
		}

#if WITH_STATETREE_SUPPORT
		// M27.3.1 — single call to the shared emitter handles all three files
		// (`.md`, `.meta.json`, `.deep.md` when requested) for a StateTree.
		bool ReExportStateTree(
			const FAssetData& AssetData,
			UStateTree* StateTree,
			const FString& MdPath,
			const FString& MetaPath,
			const FString& DeepPath,
			FReExportResult& Out)
		{
			int32 OverallPct = 100;
			FString EmitError;
			const bool bOk = InventoryEmit::EmitStateTreeAsset(
				AssetData, StateTree, MdPath, MetaPath, OverallPct, EmitError,
				/*bEmitDeepDump=*/true, DeepPath);
			if (!bOk)
			{
				// Distinguish "serialize returned false" from "write failed" when
				// possible — the shared emitter prefixes write errors with
				// `failed to write`. Crude but covers the observable cases.
				const bool bWrite = EmitError.Contains(TEXT("failed to write"));
				Out.Status = bWrite
					? EReExportStatus::WriteFailed
					: EReExportStatus::SerializeFailed;
				Out.Error = EmitError.IsEmpty()
					? FString(TEXT("EmitStateTreeAsset returned false"))
					: EmitError;
				return false;
			}
			Out.WrittenFiles.Add(MdPath);
			Out.WrittenFiles.Add(MetaPath);
			Out.WrittenFiles.Add(DeepPath);
			Out.Status = EReExportStatus::Ok;
			return true;
		}
#endif
	}

	FReExportResult ReExportAsset(
		const FString& PackageName,
		const FString& InventoryRoot)
	{
		FReExportResult Result;
		Result.PackageName = PackageName;

		if (PackageName.IsEmpty() || !PackageName.StartsWith(TEXT("/")))
		{
			Result.Status = EReExportStatus::LoadFailed;
			Result.Error = FString::Printf(
				TEXT("package name must start with `/` (got %s)"), *PackageName);
			return Result;
		}
		if (InventoryRoot.IsEmpty())
		{
			Result.Status = EReExportStatus::WriteFailed;
			Result.Error = TEXT("inventoryRoot is empty");
			return Result;
		}

		const FAssetData AssetData = FindPrimaryAsset(PackageName);
		if (!AssetData.IsValid())
		{
			Result.Status = EReExportStatus::LoadFailed;
			Result.Error = FString::Printf(
				TEXT("no asset found in package %s (AssetRegistry.GetAssetsByPackageName returned empty)"),
				*PackageName);
			return Result;
		}
		Result.ClassName = AssetData.AssetClassPath.GetAssetName().ToString();

		UObject* Asset = AssetData.GetAsset();
		if (Asset == nullptr)
		{
			Result.Status = EReExportStatus::LoadFailed;
			Result.Error = TEXT("AssetData.GetAsset() returned null");
			return Result;
		}

		// Ensure the inventory output subtree exists. BuildAssetOutputBase is
		// the shared helper from InventoryEmit — same layout the commandlet
		// sweep uses, so an MCP retrieval call walking `<InventoryRoot>/Assets/`
		// finds the refreshed sidecars.
		const FString OutBase = InventoryEmit::BuildAssetOutputBase(InventoryRoot, PackageName);
		const FString OutSubdir = FPaths::GetPath(OutBase);
		if (!IFileManager::Get().DirectoryExists(*OutSubdir))
		{
			if (!IFileManager::Get().MakeDirectory(*OutSubdir, /*Tree=*/true))
			{
				Result.Status = EReExportStatus::WriteFailed;
				Result.Error = FString::Printf(
					TEXT("failed to create output directory %s"), *OutSubdir);
				return Result;
			}
		}
		const FString MdPath   = OutBase + TEXT(".md");
		const FString MetaPath = OutBase + TEXT(".meta.json");
		const FString DeepPath = OutBase + TEXT(".deep.md");

		if (UBlueprint* Blueprint = Cast<UBlueprint>(Asset))
		{
			ReExportBlueprint(Blueprint, MdPath, MetaPath, DeepPath, Result);
			return Result;
		}

#if WITH_STATETREE_SUPPORT
		if (UStateTree* StateTree = Cast<UStateTree>(Asset))
		{
			ReExportStateTree(AssetData, StateTree, MdPath, MetaPath, DeepPath, Result);
			return Result;
		}
#endif

		Result.Status = EReExportStatus::Unsupported;
		Result.Error = FString::Printf(
			TEXT("type %s not supported by bridge re-export (M27.3/.3.1 covers UBlueprint + UStateTree only); "
			     "run refresh_inventory to update sidecars for this asset"),
			*Result.ClassName);
		return Result;
	}
}
