// Copyright Epic Games, Inc. All Rights Reserved.

#include "Export/BlueprintExportManager.h"
#include "BlueprintExporterModule.h"
#include "Serialization/BlueprintSerializer.h"
#include "Serialization/BlueprintTypeInference.h"
#include "Serialization/StateTreeSerializer.h"
#if WITH_STATETREE_SUPPORT
#include "StateTree.h"
#endif
#include "TextExport/HumanReadableExporter.h"
#include "Engine/Blueprint.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFileManager.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

FBlueprintExportManager::FBlueprintExportManager()
{
	Serializer = MakeUnique<FBlueprintSerializer>();
}

FBlueprintExportManager::~FBlueprintExportManager()
{
}

FBlueprintExportResult FBlueprintExportManager::ExportBlueprint(UBlueprint* Blueprint, const FBlueprintExportConfig& Config)
{
	FBlueprintExportResult Result;
	Result.AssetPath = Blueprint ? Blueprint->GetPathName() : TEXT("");

	double StartTime = FPlatformTime::Seconds();

	if (!Blueprint)
	{
		Result.Error = TEXT("Blueprint is null");
		return Result;
	}

	// Validate output directory
	if (Config.OutputDirectory.IsEmpty())
	{
		Result.Error = TEXT("Output directory is not specified");
		return Result;
	}

	// Serialize Blueprint
	FExportedBlueprint ExportedData;
	FString SerializeError;
	if (!Serializer->SerializeBlueprint(Blueprint, ExportedData, SerializeError))
	{
		Result.Error = SerializeError;
		return Result;
	}

	// Generate output path
	FString OutputPath = GenerateOutputPath(Config.OutputDirectory, Blueprint->GetPathName(), Blueprint->GetName());
	Result.OutputFilePath = OutputPath;

	// Create directory if needed
	FString Directory = FPaths::GetPath(OutputPath);
	if (!IFileManager::Get().DirectoryExists(*Directory))
	{
		IFileManager::Get().MakeDirectory(*Directory, true);
	}

	// Write main JSON export
	FString WriteError;
	if (!WriteExportedBlueprint(ExportedData, OutputPath, Config.bPrettyPrint, WriteError))
	{
		Result.Error = WriteError;
		return Result;
	}

	// Generate human-readable text export
	if (Config.bExportHumanReadable)
	{
		FHumanReadableExporter TextExporter;
		FString TextPath = FPaths::ChangeExtension(OutputPath, TEXT("txt"));
		TextExporter.SaveToFile(ExportedData, TextPath);
	}

	// Generate digest export
	if (Config.bExportDigest)
	{
		FHumanReadableExporter TextExporter;
		FString DigestPath = FPaths::ChangeExtension(OutputPath, TEXT("digest.json"));
		TextExporter.SaveDigestToFile(ExportedData, DigestPath);
	}

	// Calculate metrics
	Result.NodeCount = CountNodes(ExportedData);
	Result.ComplexityScore = CalculateComplexityScore(ExportedData);
	Result.ExportTimeSeconds = static_cast<float>(FPlatformTime::Seconds() - StartTime);
	Result.bSuccess = true;

	return Result;
}

FBlueprintBatchExportResult FBlueprintExportManager::ExportBlueprints(const TArray<UBlueprint*>& Blueprints, const FBlueprintExportConfig& Config)
{
	FBlueprintBatchExportResult BatchResult;
	BatchResult.bSuccess = true;

	// Validate output directory
	if (Config.OutputDirectory.IsEmpty())
	{
		BatchResult.bSuccess = false;
		return BatchResult;
	}

	double BatchStartTime = FPlatformTime::Seconds();

	// Collect all Blueprints to export (including dependencies)
	TArray<UBlueprint*> AllBlueprints;
	TSet<FString> ProcessedPaths;

	for (UBlueprint* Blueprint : Blueprints)
	{
		if (!Blueprint || ProcessedPaths.Contains(Blueprint->GetPathName()))
		{
			continue;
		}

		ProcessedPaths.Add(Blueprint->GetPathName());
		AllBlueprints.Add(Blueprint);

		// Resolve dependencies if requested
		if (Config.bIncludeDependencies)
		{
			TArray<UBlueprint*> Dependencies = ResolveDependencies(Blueprint, Config.DependencyDepth);
			for (UBlueprint* Dep : Dependencies)
			{
				if (Dep && !ProcessedPaths.Contains(Dep->GetPathName()))
				{
					ProcessedPaths.Add(Dep->GetPathName());
					AllBlueprints.Add(Dep);
				}
			}
		}
	}

	// Export each Blueprint
	FExportManifest Manifest;
	Manifest.SchemaVersion = BLUEPRINT_EXPORT_SCHEMA_VERSION;
	Manifest.EngineVersion = FEngineVersion::Current().ToString();
	Manifest.PluginVersion = TEXT("1.28.6");
	Manifest.ExportTimestamp = FDateTime::UtcNow().ToIso8601();

	// Store config in manifest
	Manifest.ExportConfig.Add(TEXT("includeDependencies"), Config.bIncludeDependencies ? TEXT("true") : TEXT("false"));
	Manifest.ExportConfig.Add(TEXT("dependencyDepth"), FString::FromInt(Config.DependencyDepth));
	Manifest.ExportConfig.Add(TEXT("outputDirectory"), Config.OutputDirectory);

	for (UBlueprint* Blueprint : AllBlueprints)
	{
		FBlueprintExportResult Result = ExportBlueprint(Blueprint, Config);
		BatchResult.Results.Add(Result);

		if (Result.bSuccess)
		{
			FExportManifestEntry Entry;
			Entry.AssetPath = Blueprint->GetPathName();
			Entry.AssetName = Blueprint->GetName();
			Entry.ExportFileName = FPaths::GetCleanFilename(Result.OutputFilePath);
			Entry.AssetType = TEXT("Blueprint");
			Entry.BlueprintSubclass = FBlueprintSerializer::DetectBlueprintSubclass(Blueprint);
			Entry.NodeCount = Result.NodeCount;
			Entry.ComplexityScore = Result.ComplexityScore;

			// Compute hash by loading the exported file
			FString JsonContent;
			if (FFileHelper::LoadFileToString(JsonContent, *Result.OutputFilePath))
			{
				Entry.ContentHash = FMD5::HashAnsiString(*JsonContent);
			}

			Manifest.Entries.Add(Entry);
		}
		else
		{
			BatchResult.bSuccess = false;
		}
	}

	// Write manifest
	FString ManifestPath = FPaths::Combine(Config.OutputDirectory, TEXT("manifest.json"));
	FString ManifestError;
	if (!WriteManifest(Manifest, ManifestPath, ManifestError))
	{
		BatchResult.bSuccess = false;
		// Surface the failure reason — FBlueprintBatchExportResult has no
		// aggregate error field, and without this log the only signal callers
		// have of a manifest write failure is the bSuccess flag flipping.
		UE_LOG(LogBlueprintExporter, Error, TEXT("[BlueprintExporter] Batch manifest write failed: %s"), *ManifestError);
	}
	BatchResult.ManifestPath = ManifestPath;

	// Build metrics
	BatchResult.Metrics.Timestamp = FDateTime::UtcNow().ToIso8601();
	BatchResult.Metrics.TotalBlueprints = AllBlueprints.Num();
	BatchResult.Metrics.SuccessCount = BatchResult.GetSuccessCount();
	BatchResult.Metrics.FailureCount = BatchResult.GetFailureCount();
	BatchResult.Metrics.TotalExportTimeSeconds = static_cast<float>(FPlatformTime::Seconds() - BatchStartTime);

	for (const FBlueprintExportResult& Result : BatchResult.Results)
	{
		if (!Result.bSuccess)
		{
			BatchResult.Metrics.FailedAssets.Add(Result.AssetPath);
		}
		else
		{
			BatchResult.Metrics.PerBlueprintMetrics.Add(Result.AssetPath, Result.ExportTimeSeconds);
		}
	}

	// Write metrics file
	FString MetricsPath = FPaths::Combine(Config.OutputDirectory, TEXT("metrics.json"));
	BatchResult.Metrics.SaveToFile(MetricsPath);

	return BatchResult;
}

FBlueprintBatchExportResult FBlueprintExportManager::ExportBlueprintsByPath(const FString& PathFilter, const FBlueprintExportConfig& Config)
{
	TArray<UBlueprint*> Blueprints;

	// Use asset registry to find Blueprints
	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

	FARFilter Filter;
	Filter.ClassPaths.Add(UBlueprint::StaticClass()->GetClassPathName());
	Filter.bRecursivePaths = true;
	Filter.bRecursiveClasses = true;

	// Parse path filter
	if (PathFilter.Contains(TEXT("*")))
	{
		// Wildcard path - search in parent directory
		FString BasePath = PathFilter;
		BasePath.ReplaceInline(TEXT("*"), TEXT(""));
		Filter.PackagePaths.Add(FName(*BasePath));
	}
	else
	{
		Filter.PackagePaths.Add(FName(*PathFilter));
	}

	TArray<FAssetData> AssetDataList;
	AssetRegistry.GetAssets(Filter, AssetDataList);

	for (const FAssetData& AssetData : AssetDataList)
	{
		// Check wildcard matching if needed
		if (PathFilter.Contains(TEXT("*")))
		{
			FString PackagePath = AssetData.PackagePath.ToString();
			// Simple wildcard matching
			FString Pattern = PathFilter;
			Pattern.ReplaceInline(TEXT("*"), TEXT(""));
			if (!PackagePath.StartsWith(Pattern))
			{
				continue;
			}
		}

		UBlueprint* Blueprint = Cast<UBlueprint>(AssetData.GetAsset());
		if (Blueprint)
		{
			Blueprints.Add(Blueprint);
		}
	}

	return ExportBlueprints(Blueprints, Config);
}

TArray<UBlueprint*> FBlueprintExportManager::ResolveDependencies(UBlueprint* Blueprint, int32 MaxDepth)
{
	TArray<UBlueprint*> Dependencies;
	TSet<FString> ProcessedPaths;

	if (Blueprint)
	{
		ProcessedPaths.Add(Blueprint->GetPathName());
		ResolveDependenciesRecursive(Blueprint, 0, MaxDepth, ProcessedPaths, Dependencies);
	}

	return Dependencies;
}

void FBlueprintExportManager::ResolveDependenciesRecursive(UBlueprint* Blueprint, int32 CurrentDepth, int32 MaxDepth, TSet<FString>& ProcessedPaths, TArray<UBlueprint*>& OutDependencies)
{
	if (!Blueprint)
	{
		return;
	}

	if (MaxDepth > 0 && CurrentDepth >= MaxDepth)
	{
		return;
	}

	// Get dependencies via asset registry
	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

	TArray<FAssetIdentifier> ReferencedAssets;
	FAssetIdentifier BlueprintIdentifier(Blueprint->GetOutermost()->GetFName());
	AssetRegistry.GetDependencies(BlueprintIdentifier, ReferencedAssets);

	for (const FAssetIdentifier& AssetId : ReferencedAssets)
	{
		FString AssetPath = AssetId.PackageName.ToString();

		if (ProcessedPaths.Contains(AssetPath))
		{
			continue;
		}

		// Try to load as Blueprint
		UBlueprint* DepBlueprint = LoadObject<UBlueprint>(nullptr, *AssetPath);
		if (!DepBlueprint)
		{
			// Try appending the Blueprint suffix
			FString BPPath = AssetPath + TEXT(".") + FPackageName::GetShortName(AssetPath);
			DepBlueprint = LoadObject<UBlueprint>(nullptr, *BPPath);
		}

		if (DepBlueprint)
		{
			ProcessedPaths.Add(DepBlueprint->GetPathName());
			OutDependencies.Add(DepBlueprint);

			// Recurse
			ResolveDependenciesRecursive(DepBlueprint, CurrentDepth + 1, MaxDepth, ProcessedPaths, OutDependencies);
		}
	}

	// Also check parent Blueprint
	if (Blueprint->ParentClass && !Blueprint->ParentClass->IsNative())
	{
		UBlueprint* ParentBP = Cast<UBlueprint>(Blueprint->ParentClass->ClassGeneratedBy);
		if (ParentBP && !ProcessedPaths.Contains(ParentBP->GetPathName()))
		{
			ProcessedPaths.Add(ParentBP->GetPathName());
			OutDependencies.Add(ParentBP);
			ResolveDependenciesRecursive(ParentBP, CurrentDepth + 1, MaxDepth, ProcessedPaths, OutDependencies);
		}
	}
}

bool FBlueprintExportManager::WriteExportedBlueprint(const FExportedBlueprint& ExportedData, const FString& OutputPath, bool bPrettyPrint, FString& OutError)
{
	TSharedPtr<FJsonObject> JsonObject = ExportedData.ToJson();

	// Run type inference post-pass to resolve missing pin types from connections
	FBlueprintTypeInference TypeInference;
	FInferenceStats InferenceStats = TypeInference.RunTypeInference(JsonObject);

	UE_LOG(LogBlueprintExporter, Log, TEXT("[BlueprintExporter] Type inference complete: %d/%d resolved (%d inferred), %d unresolved, %d conflicts"),
		InferenceStats.ResolvedPins, InferenceStats.TotalPins, InferenceStats.InferredPins,
		InferenceStats.UnresolvedPins, InferenceStats.ConflictPins);

	FString JsonString;
	TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> PrettyWriter =
		TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&JsonString);
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> CondensedWriter =
		TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonString);

	bool bSerializeSuccess;
	if (bPrettyPrint)
	{
		bSerializeSuccess = FJsonSerializer::Serialize(JsonObject.ToSharedRef(), PrettyWriter);
	}
	else
	{
		bSerializeSuccess = FJsonSerializer::Serialize(JsonObject.ToSharedRef(), CondensedWriter);
	}

	if (!bSerializeSuccess)
	{
		OutError = TEXT("Failed to serialize to JSON");
		return false;
	}

	if (!FFileHelper::SaveStringToFile(JsonString, *OutputPath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
	{
		OutError = FString::Printf(TEXT("Failed to write file: %s"), *OutputPath);
		return false;
	}

	return true;
}

bool FBlueprintExportManager::WriteManifest(const FExportManifest& Manifest, const FString& OutputPath, FString& OutError)
{
	if (!Manifest.SaveToFile(OutputPath))
	{
		// Previously dropped SaveToFile's failure on the floor: callers checked the
		// return value but always got an empty OutError, so batch-export failures
		// surfaced as a silent bSuccess=false with no diagnostic. SaveToFile itself
		// doesn't expose the underlying reason, so we report the destination path
		// — the two common causes (unwritable directory, file in use) are both
		// debuggable from the path alone.
		OutError = FString::Printf(TEXT("Failed to write manifest to '%s'"), *OutputPath);
		return false;
	}
	return true;
}

float FBlueprintExportManager::CalculateComplexityScore(const FExportedBlueprint& ExportedData)
{
	float Score = 0.0f;

	// Node count contributes to complexity
	int32 TotalNodes = CountNodes(ExportedData);
	Score += TotalNodes * 1.0f;

	// Function count
	Score += ExportedData.Functions.Num() * 5.0f;

	// Variable count
	Score += ExportedData.Variables.Num() * 2.0f;

	// Connection count (rough estimate based on pins)
	int32 ConnectionCount = 0;
	auto CountConnections = [&ConnectionCount](const FExportedGraph& Graph)
	{
		for (const FExportedNode& Node : Graph.Nodes)
		{
			for (const FExportedPin& Pin : Node.Pins)
			{
				ConnectionCount += Pin.Connections.Num();
			}
		}
	};

	CountConnections(ExportedData.EventGraph);
	CountConnections(ExportedData.ConstructionScript);
	for (const FExportedFunction& Func : ExportedData.Functions)
	{
		CountConnections(Func.Graph);
	}

	Score += ConnectionCount * 0.5f;

	// Component count
	Score += ExportedData.Components.Num() * 3.0f;

	return Score;
}

int32 FBlueprintExportManager::CountNodes(const FExportedBlueprint& ExportedData)
{
	int32 Count = 0;

	Count += ExportedData.EventGraph.Nodes.Num();
	Count += ExportedData.ConstructionScript.Nodes.Num();

	for (const FExportedFunction& Func : ExportedData.Functions)
	{
		Count += Func.Graph.Nodes.Num();
	}

	for (const FExportedFunction& Macro : ExportedData.Macros)
	{
		Count += Macro.Graph.Nodes.Num();
	}

	for (const FExportedGraph& Graph : ExportedData.AdditionalGraphs)
	{
		Count += Graph.Nodes.Num();
	}

	return Count;
}

FString FBlueprintExportManager::GenerateOutputPath(const FString& OutputDirectory, const FString& AssetPath, const FString& AssetName)
{
	// Convert asset path to a valid file path
	// /Game/Folder/MyBlueprint -> Folder/MyBlueprint/MyBlueprint.json
	FString RelativePath = AssetPath;
	RelativePath.RemoveFromStart(TEXT("/Game/"));
	RelativePath.RemoveFromStart(TEXT("/"));

	// Use asset name for the folder
	FString FolderPath = FPaths::GetPath(RelativePath);
	FString OutputPath = FPaths::Combine(OutputDirectory, FolderPath, AssetName, AssetName + TEXT(".json"));

	return OutputPath;
}

// ============================================================================
// State Tree Export Support
// ============================================================================

#if WITH_STATETREE_SUPPORT

FStateTreeSerializer& FBlueprintExportManager::GetStateTreeSerializer()
{
	if (!StateTreeSerializerPtr)
	{
		StateTreeSerializerPtr = MakeUnique<FStateTreeSerializer>();
	}
	return *StateTreeSerializerPtr;
}

FStateTreeExportResult FBlueprintExportManager::ExportStateTree(UStateTree* StateTree, const FBlueprintExportConfig& Config)
{
	FStateTreeExportResult Result;
	Result.AssetPath = StateTree ? StateTree->GetPathName() : TEXT("");

	double StartTime = FPlatformTime::Seconds();

	if (!StateTree)
	{
		Result.Error = TEXT("StateTree is null");
		return Result;
	}

	if (Config.OutputDirectory.IsEmpty())
	{
		Result.Error = TEXT("Output directory is not specified");
		return Result;
	}

	if (!FStateTreeSerializer::IsStateTreeModuleAvailable())
	{
		Result.Error = TEXT("StateTree module is not available");
		return Result;
	}

	// Serialize State Tree
	FExportedStateTree ExportedData;
	FString SerializeError;
	if (!GetStateTreeSerializer().SerializeStateTree(StateTree, ExportedData, SerializeError))
	{
		Result.Error = SerializeError;
		return Result;
	}

	// Generate output path
	FString OutputPath = GenerateStateTreeOutputPath(Config.OutputDirectory, StateTree->GetPathName(), StateTree->GetName());
	Result.OutputFilePath = OutputPath;

	// Create directory if needed
	FString Directory = FPaths::GetPath(OutputPath);
	if (!IFileManager::Get().DirectoryExists(*Directory))
	{
		IFileManager::Get().MakeDirectory(*Directory, true);
	}

	// Write main JSON export
	FString WriteError;
	if (!WriteExportedStateTree(ExportedData, OutputPath, Config.bPrettyPrint, WriteError))
	{
		Result.Error = WriteError;
		return Result;
	}

	// Generate human-readable text export
	if (Config.bExportHumanReadable)
	{
		FHumanReadableExporter TextExporter;
		FString TextPath = FPaths::ChangeExtension(OutputPath, TEXT("txt"));
		TextExporter.SaveStateTreeToFile(ExportedData, TextPath);
	}

	// Generate digest export
	if (Config.bExportDigest)
	{
		FHumanReadableExporter TextExporter;
		FString DigestPath = FPaths::ChangeExtension(OutputPath, TEXT("digest.json"));
		TextExporter.SaveStateTreeDigestToFile(ExportedData, DigestPath);
	}

	// Calculate metrics
	Result.StateCount = CountStates(ExportedData);
	Result.ExportTimeSeconds = static_cast<float>(FPlatformTime::Seconds() - StartTime);
	Result.bSuccess = true;

	return Result;
}

void FBlueprintExportManager::ExportStateTreesByPath(const FString& PathFilter, const FBlueprintExportConfig& Config,
	TArray<FStateTreeExportResult>& OutResults, TArray<FExportManifestEntry>& OutManifestEntries)
{
	if (!FStateTreeSerializer::IsStateTreeModuleAvailable())
	{
		UE_LOG(LogBlueprintExporter, Log, TEXT("[BlueprintExporter] StateTree module not available, skipping State Tree discovery"));
		return;
	}

	// Find UStateTree class dynamically
	UClass* StateTreeClass = FindObject<UClass>(nullptr, TEXT("/Script/StateTreeModule.StateTree"));
	if (!StateTreeClass)
	{
		UE_LOG(LogBlueprintExporter, Log, TEXT("[BlueprintExporter] UStateTree class not found, skipping State Tree export"));
		return;
	}

	// Use asset registry to find State Trees
	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

	FARFilter Filter;
	Filter.ClassPaths.Add(StateTreeClass->GetClassPathName());
	Filter.bRecursivePaths = true;
	Filter.bRecursiveClasses = true;

	// Parse path filter
	if (PathFilter.Contains(TEXT("*")))
	{
		FString BasePath = PathFilter;
		BasePath.ReplaceInline(TEXT("*"), TEXT(""));
		Filter.PackagePaths.Add(FName(*BasePath));
	}
	else
	{
		Filter.PackagePaths.Add(FName(*PathFilter));
	}

	TArray<FAssetData> AssetDataList;
	AssetRegistry.GetAssets(Filter, AssetDataList);

	for (const FAssetData& AssetData : AssetDataList)
	{
		// Check wildcard matching if needed
		if (PathFilter.Contains(TEXT("*")))
		{
			FString PackagePath = AssetData.PackagePath.ToString();
			FString Pattern = PathFilter;
			Pattern.ReplaceInline(TEXT("*"), TEXT(""));
			if (!PackagePath.StartsWith(Pattern))
			{
				continue;
			}
		}

		UStateTree* StateTree = Cast<UStateTree>(AssetData.GetAsset());
		if (StateTree)
		{
			FStateTreeExportResult Result = ExportStateTree(StateTree, Config);
			OutResults.Add(Result);

			if (Result.bSuccess)
			{
				FExportManifestEntry Entry;
				Entry.AssetPath = StateTree->GetPathName();
				Entry.AssetName = StateTree->GetName();
				Entry.ExportFileName = FPaths::GetCleanFilename(Result.OutputFilePath);
				Entry.AssetType = TEXT("StateTree");
				Entry.NodeCount = Result.StateCount;

				// Compute hash
				FString JsonContent;
				if (FFileHelper::LoadFileToString(JsonContent, *Result.OutputFilePath))
				{
					Entry.ContentHash = FMD5::HashAnsiString(*JsonContent);
				}

				OutManifestEntries.Add(Entry);
			}
		}
	}
}

bool FBlueprintExportManager::WriteExportedStateTree(const FExportedStateTree& ExportedData, const FString& OutputPath, bool bPrettyPrint, FString& OutError)
{
	TSharedPtr<FJsonObject> JsonObject = ExportedData.ToJson();

	FString JsonString;
	bool bSerializeSuccess;

	if (bPrettyPrint)
	{
		TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> PrettyWriter =
			TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&JsonString);
		bSerializeSuccess = FJsonSerializer::Serialize(JsonObject.ToSharedRef(), PrettyWriter);
	}
	else
	{
		TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> CondensedWriter =
			TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonString);
		bSerializeSuccess = FJsonSerializer::Serialize(JsonObject.ToSharedRef(), CondensedWriter);
	}

	if (!bSerializeSuccess)
	{
		OutError = TEXT("Failed to serialize State Tree to JSON");
		return false;
	}

	if (!FFileHelper::SaveStringToFile(JsonString, *OutputPath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
	{
		OutError = FString::Printf(TEXT("Failed to write file: %s"), *OutputPath);
		return false;
	}

	return true;
}

FString FBlueprintExportManager::GenerateStateTreeOutputPath(const FString& OutputDirectory, const FString& AssetPath, const FString& AssetName)
{
	FString RelativePath = AssetPath;
	RelativePath.RemoveFromStart(TEXT("/Game/"));
	RelativePath.RemoveFromStart(TEXT("/"));

	FString FolderPath = FPaths::GetPath(RelativePath);
	FString OutputPath = FPaths::Combine(OutputDirectory, FolderPath, AssetName, AssetName + TEXT(".statetree.json"));

	return OutputPath;
}

int32 FBlueprintExportManager::CountStates(const FExportedStateTree& ExportedData)
{
	return CountStatesRecursive(ExportedData.RootStates);
}

int32 FBlueprintExportManager::CountStatesRecursive(const TArray<FExportedStateTreeState>& States)
{
	int32 Count = States.Num();
	for (const FExportedStateTreeState& State : States)
	{
		Count += CountStatesRecursive(State.Children);
	}
	return Count;
}

#endif // WITH_STATETREE_SUPPORT

