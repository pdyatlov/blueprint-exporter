// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "ProjectManifestCommandlet.generated.h"

/**
 * Phase 0 of the project-inventory pipeline (see PROJECT_INVENTORY_BRIEF.md §3).
 *
 * Performs an FAssetRegistry-only scan of the target mount point and writes a
 * single MANIFEST.md summarizing what the project contains. No assets are
 * loaded; no UObject graphs are constructed. This is the cheap pre-flight
 * before the heavier ProjectInventory pass.
 *
 * Usage:
 *   UnrealEditor-Cmd.exe <project> -run=ProjectManifest -OutDir=<dir>
 *                                  [-MountPoint=/Game] [-TopN=50]
 *
 * Exit codes:
 *   0 = success
 *   2 = runtime error (bad args, scan failure, or write failure)
 */
UCLASS()
class BLUEPRINTEXPORTER_API UProjectManifestCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	UProjectManifestCommandlet();

	//~ Begin UCommandlet Interface
	virtual int32 Main(const FString& Params) override;
	//~ End UCommandlet Interface
};
