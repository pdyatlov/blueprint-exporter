// Copyright 10 Chambers. All Rights Reserved.

#include "Commandlets/ProjectManifestCommandlet.h"
#include "BlueprintExporterModule.h"
#include "Util/AtomicFileWriter.h"
#include "Util/CommandletLog.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "AssetRegistry/ARFilter.h"
#include "AssetRegistry/AssetData.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"

namespace
{
	// Logic-bearing classes per PROJECT_INVENTORY_BRIEF.md §3. Matched on the
	// class FName only (package path deliberately ignored — class-name match
	// is stable across engine/plugin module reshuffles).
	const TSet<FName>& GetLogicBearingClassNames()
	{
		static const TSet<FName> Classes = {
			FName(TEXT("Blueprint")),
			FName(TEXT("AnimBlueprint")),
			FName(TEXT("WidgetBlueprint")),
			FName(TEXT("ControlRigBlueprint")),
			FName(TEXT("BehaviorTree")),
			FName(TEXT("StateTree")),
			FName(TEXT("EnvQuery")),
			FName(TEXT("SmartObjectDefinition")),
			FName(TEXT("ChooserTable")),
			FName(TEXT("PoseSearchDatabase")),
			FName(TEXT("UserDefinedStruct")),
			FName(TEXT("UserDefinedEnum")),
			FName(TEXT("DataTable")),
		};
		return Classes;
	}

	bool IsLogicBearing(const FAssetData& AssetData)
	{
		return GetLogicBearingClassNames().Contains(AssetData.AssetClassPath.GetAssetName());
	}

	int64 ResolvePackageSizeOnDisk(const FAssetData& AssetData)
	{
		FString PackageFilename;
		if (FPackageName::DoesPackageExist(AssetData.PackageName.ToString(), &PackageFilename))
		{
			const int64 Size = IFileManager::Get().FileSize(*PackageFilename);
			return Size >= 0 ? Size : 0;
		}
		return 0;
	}

	// "/Game/TestBlueprints/Foo" with mount "/Game" -> "/Game/TestBlueprints".
	FString TopLevelFolderUnderMount(const FString& PackagePath, const FString& MountPoint)
	{
		if (!PackagePath.StartsWith(MountPoint))
		{
			return MountPoint;
		}
		FString Remainder = PackagePath.Mid(MountPoint.Len());
		Remainder.RemoveFromStart(TEXT("/"));
		int32 SlashIdx = INDEX_NONE;
		if (Remainder.FindChar(TEXT('/'), SlashIdx))
		{
			Remainder = Remainder.Left(SlashIdx);
		}
		return Remainder.IsEmpty() ? MountPoint : (MountPoint / Remainder);
	}

	// Log line surface lives in `BlueprintExporter::Util::LogLine` (shared
	// helper in Util/CommandletLog.h). Kept out of this anon namespace so
	// unity (jumbo) builds don't collide with the identical-body copy that
	// ProjectPluginsCommandlet.cpp used to carry.
	using BlueprintExporter::Util::LogLine;

	struct FSizeEntry
	{
		FString PackageName;
		FName   ClassName;
		int64   Size;
	};
}

UProjectManifestCommandlet::UProjectManifestCommandlet()
{
	IsClient = false;
	IsEditor = true;
	IsServer = false;
	LogToConsole = true;
}

int32 UProjectManifestCommandlet::Main(const FString& Params)
{
	LogLine(TEXT("INFO"), TEXT("Project Manifest Commandlet starting..."));

	FString OutDir;
	if (!FParse::Value(*Params, TEXT("OutDir="), OutDir))
	{
		LogLine(TEXT("ERROR"),
			TEXT("Usage: -run=ProjectManifest -OutDir=<dir> [-MountPoint=/Game] [-TopN=50]"),
			/*bIsError=*/true);
		return 2;
	}
	OutDir.TrimQuotesInline();

	FString MountPoint = TEXT("/Game");
	FParse::Value(*Params, TEXT("MountPoint="), MountPoint);
	MountPoint.TrimQuotesInline();
	if (!MountPoint.StartsWith(TEXT("/")))
	{
		MountPoint = TEXT("/") + MountPoint;
	}
	while (MountPoint.EndsWith(TEXT("/")) && MountPoint.Len() > 1)
	{
		MountPoint = MountPoint.LeftChop(1);
	}

	int32 TopN = 50;
	FParse::Value(*Params, TEXT("TopN="), TopN);
	TopN = FMath::Clamp(TopN, 0, 10000);

	LogLine(TEXT("INFO"),
		FString::Printf(TEXT("MountPoint=%s OutDir=%s TopN=%d"), *MountPoint, *OutDir, TopN));

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

	FARFilter Filter;
	Filter.PackagePaths.Add(FName(*MountPoint));
	Filter.bRecursivePaths = true;

	TArray<FAssetData> AllAssets;
	AssetRegistry.GetAssets(Filter, AllAssets);

	LogLine(TEXT("INFO"),
		FString::Printf(TEXT("Found %d assets under %s"), AllAssets.Num(), *MountPoint));

	TMap<FName, int32> LogicBearingCounts;
	TMap<FName, int32> NonLogicCounts;
	TMap<FString, int32> FolderTotals;
	TMap<FString, int32> FolderLogicBearing;

	TArray<FSizeEntry> Sizes;
	Sizes.Reserve(AllAssets.Num());

	int32 LogicBearingTotal = 0;

	for (const FAssetData& AssetData : AllAssets)
	{
		const FName ClassName = AssetData.AssetClassPath.GetAssetName();
		const bool bLogic = IsLogicBearing(AssetData);
		if (bLogic)
		{
			++LogicBearingCounts.FindOrAdd(ClassName);
			++LogicBearingTotal;
		}
		else
		{
			++NonLogicCounts.FindOrAdd(ClassName);
		}

		const FString PackagePath = AssetData.PackagePath.ToString();
		const FString TopFolder = TopLevelFolderUnderMount(PackagePath, MountPoint);
		++FolderTotals.FindOrAdd(TopFolder);
		if (bLogic)
		{
			++FolderLogicBearing.FindOrAdd(TopFolder);
		}

		FSizeEntry Entry;
		Entry.PackageName = AssetData.PackageName.ToString();
		Entry.ClassName = ClassName;
		Entry.Size = ResolvePackageSizeOnDisk(AssetData);
		Sizes.Add(MoveTemp(Entry));
	}

	Sizes.Sort([](const FSizeEntry& A, const FSizeEntry& B)
	{
		if (A.Size != B.Size)
		{
			return A.Size > B.Size;
		}
		return A.PackageName.Compare(B.PackageName, ESearchCase::IgnoreCase) < 0;
	});

	FString Md;
	Md.Reserve(16 * 1024);
	Md += TEXT("# Project Manifest\n\n");
	Md += FString::Printf(TEXT("Mount point: `%s`\n\n"), *MountPoint);
	Md += FString::Printf(TEXT("- Total assets: **%d**\n"), AllAssets.Num());
	Md += FString::Printf(TEXT("- Logic-bearing assets: **%d**\n"), LogicBearingTotal);
	Md += FString::Printf(TEXT("- Non-logic assets: **%d**\n\n"),
		AllAssets.Num() - LogicBearingTotal);

	auto EmitClassTable = [&Md](const TCHAR* Title, const TMap<FName, int32>& Counts)
	{
		Md += FString::Printf(TEXT("## %s\n\n"), Title);
		if (Counts.Num() == 0)
		{
			Md += TEXT("_None._\n\n");
			return;
		}
		TArray<FName> Keys;
		Counts.GetKeys(Keys);
		Keys.Sort([](const FName& A, const FName& B)
		{
			return A.ToString().Compare(B.ToString(), ESearchCase::IgnoreCase) < 0;
		});
		Md += TEXT("| Class | Count |\n");
		Md += TEXT("|---|---|\n");
		for (const FName& Key : Keys)
		{
			Md += FString::Printf(TEXT("| `%s` | %d |\n"), *Key.ToString(), Counts[Key]);
		}
		Md += TEXT("\n");
	};

	EmitClassTable(TEXT("Counts by class (logic-bearing)"), LogicBearingCounts);
	EmitClassTable(TEXT("Counts by class (non-logic / skipped)"), NonLogicCounts);

	{
		Md += TEXT("## Counts by top-level folder\n\n");
		TArray<FString> Folders;
		FolderTotals.GetKeys(Folders);
		Folders.Sort([](const FString& A, const FString& B)
		{
			return A.Compare(B, ESearchCase::IgnoreCase) < 0;
		});
		Md += TEXT("| Folder | Total | Logic-bearing |\n");
		Md += TEXT("|---|---|---|\n");
		for (const FString& Folder : Folders)
		{
			const int32 LB = FolderLogicBearing.FindRef(Folder);
			Md += FString::Printf(TEXT("| `%s` | %d | %d |\n"),
				*Folder, FolderTotals[Folder], LB);
		}
		Md += TEXT("\n");
	}

	if (TopN > 0)
	{
		const int32 Emit = FMath::Min(TopN, Sizes.Num());
		Md += FString::Printf(TEXT("## Largest %d assets (by package size on disk)\n\n"), Emit);
		Md += TEXT("| # | Path | Class | Size (bytes) |\n");
		Md += TEXT("|---|---|---|---|\n");
		for (int32 Index = 0; Index < Emit; ++Index)
		{
			const FSizeEntry& Entry = Sizes[Index];
			Md += FString::Printf(TEXT("| %d | `%s` | `%s` | %lld |\n"),
				Index + 1, *Entry.PackageName, *Entry.ClassName.ToString(), Entry.Size);
		}
		Md += TEXT("\n");
	}

	const FString OutPath = FPaths::Combine(OutDir, TEXT("MANIFEST.md"));
	if (!BlueprintExporterUtil::SaveStringAtomic(Md, OutPath))
	{
		LogLine(TEXT("ERROR"), FString::Printf(TEXT("Failed to write %s"), *OutPath), /*bIsError=*/true);
		return 2;
	}

	LogLine(TEXT("RESULT"), FString::Printf(TEXT("Wrote %s"), *OutPath));
	LogLine(TEXT("RESULT"),
		FString::Printf(TEXT("Total=%d LogicBearing=%d NonLogic=%d"),
			AllAssets.Num(), LogicBearingTotal, AllAssets.Num() - LogicBearingTotal));
	LogLine(TEXT("STATUS"), TEXT("SUCCESS"));
	return 0;
}
