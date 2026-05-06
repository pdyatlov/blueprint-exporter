// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Schema/BlueprintExportTypes.h"
#include "Schema/StateTreeExportTypes.h"

class UBlueprint;
#if WITH_STATETREE_SUPPORT
class UStateTree;
#endif
class FBlueprintSerializer;
class FStateTreeSerializer;

/**
 * Export result for a single Blueprint
 */
struct BLUEPRINTEXPORTER_API FBlueprintExportResult
{
	bool bSuccess = false;
	FString AssetPath;
	FString OutputFilePath;
	FString Error;
	float ExportTimeSeconds = 0.0f;
	int32 NodeCount = 0;
	float ComplexityScore = 0.0f;
};

/**
 * Batch export result
 */
struct BLUEPRINTEXPORTER_API FBlueprintBatchExportResult
{
	bool bSuccess = false;
	TArray<FBlueprintExportResult> Results;
	FString ManifestPath;
	FBlueprintExportMetrics Metrics;

	int32 GetSuccessCount() const
	{
		int32 Count = 0;
		for (const auto& Result : Results)
		{
			if (Result.bSuccess) Count++;
		}
		return Count;
	}

	int32 GetFailureCount() const
	{
		return Results.Num() - GetSuccessCount();
	}
};

/**
 * Export result for a single State Tree
 */
struct BLUEPRINTEXPORTER_API FStateTreeExportResult
{
	bool bSuccess = false;
	FString AssetPath;
	FString OutputFilePath;
	FString Error;
	float ExportTimeSeconds = 0.0f;
	int32 StateCount = 0;
};

/**
 * Manages Blueprint and State Tree export operations with dependency resolution and batch processing.
 */
class BLUEPRINTEXPORTER_API FBlueprintExportManager
{
public:
	FBlueprintExportManager();
	~FBlueprintExportManager();

	/**
	 * Export a single Blueprint.
	 * @param Blueprint The Blueprint to export
	 * @param Config Export configuration
	 * @return Export result
	 */
	FBlueprintExportResult ExportBlueprint(UBlueprint* Blueprint, const FBlueprintExportConfig& Config);

	/**
	 * Export multiple Blueprints.
	 * @param Blueprints Blueprints to export
	 * @param Config Export configuration
	 * @return Batch export result with manifest
	 */
	FBlueprintBatchExportResult ExportBlueprints(const TArray<UBlueprint*>& Blueprints, const FBlueprintExportConfig& Config);

	/**
	 * Export Blueprints matching path filter.
	 * @param PathFilter Asset path filter (supports wildcards)
	 * @param Config Export configuration
	 * @return Batch export result
	 */
	FBlueprintBatchExportResult ExportBlueprintsByPath(const FString& PathFilter, const FBlueprintExportConfig& Config);

	/**
	 * Resolve Blueprint dependencies.
	 * @param Blueprint Root Blueprint
	 * @param MaxDepth Maximum dependency depth (0 = unlimited)
	 * @return List of dependent Blueprints
	 */
	TArray<UBlueprint*> ResolveDependencies(UBlueprint* Blueprint, int32 MaxDepth);

#if WITH_STATETREE_SUPPORT
	/**
	 * Export a single State Tree.
	 * @param StateTree The State Tree to export
	 * @param Config Export configuration
	 * @return Export result
	 */
	FStateTreeExportResult ExportStateTree(UStateTree* StateTree, const FBlueprintExportConfig& Config);

	/**
	 * Export State Trees matching path filter.
	 * @param PathFilter Asset path filter (supports wildcards)
	 * @param Config Export configuration
	 * @param OutResults Individual export results appended here
	 * @param OutManifestEntries Manifest entries for successful exports appended here
	 */
	void ExportStateTreesByPath(const FString& PathFilter, const FBlueprintExportConfig& Config,
		TArray<FStateTreeExportResult>& OutResults, TArray<FExportManifestEntry>& OutManifestEntries);
#endif

	/** Get the serializer instance */
	FBlueprintSerializer& GetSerializer() { return *Serializer; }

private:
	/** Write exported Blueprint to file */
	bool WriteExportedBlueprint(const FExportedBlueprint& ExportedData, const FString& OutputPath, bool bPrettyPrint, FString& OutError);

	/** Write manifest file */
	bool WriteManifest(const FExportManifest& Manifest, const FString& OutputPath, FString& OutError);

	/** Calculate complexity score for a Blueprint */
	float CalculateComplexityScore(const FExportedBlueprint& ExportedData);

	/** Count nodes in exported Blueprint */
	int32 CountNodes(const FExportedBlueprint& ExportedData);

	/** Generate output file path for Blueprint */
	FString GenerateOutputPath(const FString& OutputDirectory, const FString& AssetPath, const FString& AssetName);

	/** Resolve dependencies recursively */
	void ResolveDependenciesRecursive(UBlueprint* Blueprint, int32 CurrentDepth, int32 MaxDepth, TSet<FString>& ProcessedPaths, TArray<UBlueprint*>& OutDependencies);

#if WITH_STATETREE_SUPPORT
	/** Write exported State Tree to file */
	bool WriteExportedStateTree(const FExportedStateTree& ExportedData, const FString& OutputPath, bool bPrettyPrint, FString& OutError);

	/** Generate output file path for State Tree */
	FString GenerateStateTreeOutputPath(const FString& OutputDirectory, const FString& AssetPath, const FString& AssetName);

	/** Count states recursively */
	int32 CountStates(const FExportedStateTree& ExportedData);
	int32 CountStatesRecursive(const TArray<FExportedStateTreeState>& States);

	/** Lazily create the State Tree serializer */
	FStateTreeSerializer& GetStateTreeSerializer();

	TUniquePtr<FStateTreeSerializer> StateTreeSerializerPtr;
#endif

	TUniquePtr<FBlueprintSerializer> Serializer;
};
