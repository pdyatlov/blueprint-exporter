// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "BlueprintExportCommandlet.generated.h"

/**
 * Commandlet for exporting Blueprints in headless/CI mode.
 *
 * Usage:
 *   UE5Editor.exe <project> -run=BlueprintExport -Paths="/Game/..." -Out="OutputDir" [options]
 *
 * Options:
 *   -Paths=<path>       Asset path filter (supports wildcards)
 *   -Out=<dir>          Output directory for exported files
 *   -IncludeDeps        Include Blueprint dependencies
 *   -Depth=<n>          Dependency resolution depth (default: 1)
 *   -NoText             Skip human-readable text export
 *   -NoDigest           Skip digest/metrics JSON export
 *   -Compact            Use compact JSON (no pretty printing)
 *   -IncludeStateTrees  Also export State Tree assets found in the search paths
 *
 * Exit Codes:
 *   0 = Success
 *   1 = Validation failed
 *   2 = Runtime error
 */
UCLASS()
class BLUEPRINTEXPORTER_API UBlueprintExportCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	UBlueprintExportCommandlet();

	//~ Begin UCommandlet Interface
	virtual int32 Main(const FString& Params) override;
	//~ End UCommandlet Interface

private:
	/** Parse command line arguments */
	bool ParseArgs(const FString& Params, FString& OutPaths, FString& OutOutputDir);

	/** Log structured output for CI parsing */
	void LogStructured(const FString& Category, const FString& Message, bool bIsError = false);
};
