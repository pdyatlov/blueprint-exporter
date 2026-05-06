// Copyright Epic Games, Inc. All Rights Reserved.

#include "Commandlets/BlueprintExportCommandlet.h"
#include "BlueprintExporterModule.h"
#include "Export/BlueprintExportManager.h"
#include "Serialization/StateTreeSerializer.h"
#include "Schema/BlueprintExportTypes.h"
#include "Schema/StateTreeExportTypes.h"
#include "Engine/Blueprint.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFileManager.h"

UBlueprintExportCommandlet::UBlueprintExportCommandlet()
{
	IsClient = false;
	IsEditor = true;
	IsServer = false;
	LogToConsole = true;
}

int32 UBlueprintExportCommandlet::Main(const FString& Params)
{
	LogStructured(TEXT("INFO"), TEXT("Blueprint Export Commandlet starting..."));

	// Parse arguments
	FString PathsArg, OutputDir;
	if (!ParseArgs(Params, PathsArg, OutputDir))
	{
		LogStructured(TEXT("ERROR"), TEXT("Usage: -run=BlueprintExport -Paths=\"/Game/...\" -Out=\"OutputDir\""), true);
		return EBlueprintExportExitCode::RuntimeError;
	}

	// Create output directory
	if (!IFileManager::Get().DirectoryExists(*OutputDir))
	{
		IFileManager::Get().MakeDirectory(*OutputDir, true);
	}

	// Parse optional flags
	bool bIncludeDeps = FParse::Param(*Params, TEXT("IncludeDeps"));
	int32 Depth = 1;
	FParse::Value(*Params, TEXT("Depth="), Depth);
	bool bNoText = FParse::Param(*Params, TEXT("NoText"));
	bool bNoDigest = FParse::Param(*Params, TEXT("NoDigest"));
	bool bCompact = FParse::Param(*Params, TEXT("Compact"));
	bool bIncludeStateTrees = FParse::Param(*Params, TEXT("IncludeStateTrees"));

	// Configure export
	FBlueprintExportConfig Config;
	Config.OutputDirectory = OutputDir;
	Config.bIncludeDependencies = bIncludeDeps;
	Config.DependencyDepth = Depth;
	Config.bExportHumanReadable = !bNoText;
	Config.bExportDigest = !bNoDigest;
	Config.bPrettyPrint = !bCompact;
	Config.bExportStateTrees = bIncludeStateTrees;

	LogStructured(TEXT("INFO"), FString::Printf(TEXT("Export configuration:")));
	LogStructured(TEXT("INFO"), FString::Printf(TEXT("  Paths: %s"), *PathsArg));
	LogStructured(TEXT("INFO"), FString::Printf(TEXT("  Output: %s"), *OutputDir));
	LogStructured(TEXT("INFO"), FString::Printf(TEXT("  Include dependencies: %s"), bIncludeDeps ? TEXT("Yes") : TEXT("No")));
	LogStructured(TEXT("INFO"), FString::Printf(TEXT("  Dependency depth: %d"), Depth));
	LogStructured(TEXT("INFO"), FString::Printf(TEXT("  Include State Trees: %s"), bIncludeStateTrees ? TEXT("Yes") : TEXT("No")));

	// Execute export. The manager writes .json + .txt + .digest.json per
	// Blueprint inline, honouring Config.bExportHumanReadable / bExportDigest.
	FBlueprintExportManager ExportManager;
	FBlueprintBatchExportResult Result = ExportManager.ExportBlueprintsByPath(PathsArg, Config);

	// State Tree export
	int32 StateTreeSuccessCount = 0;
	int32 StateTreeTotalCount = 0;
	TArray<FExportManifestEntry> StateTreeManifestEntries;

	if (bIncludeStateTrees)
	{
		LogStructured(TEXT("INFO"), TEXT("Discovering and exporting State Trees..."));

		TArray<FStateTreeExportResult> StateTreeResults;
		ExportManager.ExportStateTreesByPath(PathsArg, Config, StateTreeResults, StateTreeManifestEntries);

		StateTreeTotalCount = StateTreeResults.Num();
		for (const FStateTreeExportResult& STResult : StateTreeResults)
		{
			if (STResult.bSuccess)
			{
				StateTreeSuccessCount++;
			}
			else
			{
				LogStructured(TEXT("ERROR"), FString::Printf(TEXT("State Tree failed: %s - %s"), *STResult.AssetPath, *STResult.Error), true);
			}
		}

		LogStructured(TEXT("INFO"), FString::Printf(TEXT("State Trees: %d of %d exported successfully"), StateTreeSuccessCount, StateTreeTotalCount));
	}

	// Merge State Tree entries into manifest
	if (StateTreeManifestEntries.Num() > 0 && !Result.ManifestPath.IsEmpty())
	{
		FExportManifest Manifest;
		if (FExportManifest::LoadFromFile(Result.ManifestPath, Manifest))
		{
			for (const FExportManifestEntry& STEntry : StateTreeManifestEntries)
			{
				Manifest.Entries.Add(STEntry);
			}
			Manifest.ExportConfig.Add(TEXT("includeStateTrees"), TEXT("true"));
			Manifest.SaveToFile(Result.ManifestPath);
			LogStructured(TEXT("INFO"), FString::Printf(TEXT("Manifest updated with %d State Tree entries"), StateTreeManifestEntries.Num()));
		}
		else
		{
			LogStructured(TEXT("ERROR"), FString::Printf(TEXT("Failed to reload manifest for State Tree merge: %s"), *Result.ManifestPath), true);
		}
	}

	// Output results
	LogStructured(TEXT("RESULT"), TEXT("====================================="));
	LogStructured(TEXT("RESULT"), FString::Printf(TEXT("Total Blueprints: %d"), Result.Results.Num()));
	LogStructured(TEXT("RESULT"), FString::Printf(TEXT("Successful: %d"), Result.GetSuccessCount()));
	LogStructured(TEXT("RESULT"), FString::Printf(TEXT("Failed: %d"), Result.GetFailureCount()));
	if (bIncludeStateTrees)
	{
		LogStructured(TEXT("RESULT"), FString::Printf(TEXT("State Trees: %d of %d"), StateTreeSuccessCount, StateTreeTotalCount));
	}
	LogStructured(TEXT("RESULT"), FString::Printf(TEXT("Export time: %.2f seconds"), Result.Metrics.TotalExportTimeSeconds));

	// Log failures
	for (const FBlueprintExportResult& ExportResult : Result.Results)
	{
		if (!ExportResult.bSuccess)
		{
			LogStructured(TEXT("ERROR"), FString::Printf(TEXT("Failed: %s - %s"), *ExportResult.AssetPath, *ExportResult.Error), true);
		}
	}

	// Determine overall success
	bool bOverallSuccess = Result.bSuccess && (StateTreeTotalCount == 0 || StateTreeSuccessCount == StateTreeTotalCount);

	// Output success/failure marker for CI
	if (bOverallSuccess)
	{
		LogStructured(TEXT("STATUS"), TEXT("SUCCESS"));
		return EBlueprintExportExitCode::Success;
	}
	else
	{
		LogStructured(TEXT("STATUS"), TEXT("FAILURE"));
		int32 TotalFailures = Result.GetFailureCount() + (StateTreeTotalCount - StateTreeSuccessCount);
		return TotalFailures > 0 ? EBlueprintExportExitCode::ValidationFailed : EBlueprintExportExitCode::RuntimeError;
	}
}

bool UBlueprintExportCommandlet::ParseArgs(const FString& Params, FString& OutPaths, FString& OutOutputDir)
{
	if (!FParse::Value(*Params, TEXT("Paths="), OutPaths))
	{
		return false;
	}

	if (!FParse::Value(*Params, TEXT("Out="), OutOutputDir))
	{
		return false;
	}

	// Clean up paths
	OutPaths.TrimQuotesInline();
	OutOutputDir.TrimQuotesInline();

	return true;
}

void UBlueprintExportCommandlet::LogStructured(const FString& Category, const FString& Message, bool bIsError)
{
	FString Output = FString::Printf(TEXT("[%s] %s"), *Category, *Message);

	if (bIsError)
	{
		UE_LOG(LogBlueprintExporter, Error, TEXT("%s"), *Output);
	}
	else
	{
		UE_LOG(LogBlueprintExporter, Log, TEXT("%s"), *Output);
	}
}
