// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "ProjectPluginsCommandlet.generated.h"

/**
 * M7 P0 of the project-inventory pipeline — see PROJECT_INVENTORY_BRIEF.md
 * and WIP_INVENTORY.md for the full scope.
 *
 * Complements ProjectManifest / ProjectInventory / AggregateInventory (which
 * all operate on `/Game` content) by covering the *project plugins* shipped
 * alongside the game. Without this, native features that plugins register —
 * e.g. `CoverEQS` shipping a `UEnvQueryTest_TraceDistance` — are invisible
 * to static analysis of the output tree.
 *
 * P0 captures uplugin metadata only:
 *   - `PLUGINS.md`                       — top-level rollup table.
 *   - `PluginInventory/<Name>.md`        — per-plugin human doc.
 *   - `PluginInventory/<Name>.meta.json` — per-plugin structured sidecar.
 *
 * P1 extends the commandlet to walk `GetDerivedClasses()` against a curated
 * set of AI/gameplay base classes and populate `NativeTypes[]` per plugin.
 * Schema is pre-shaped for P1 so the sidecar format stays stable.
 *
 * Plugin scope: `EPluginType::Project` only. Engine plugins are out of scope
 * (Epic ships documentation for those). Disabled plugins are included with
 * empty `NativeTypes[]`; their uplugin metadata is read off disk.
 *
 * Usage:
 *   UnrealEditor-Cmd.exe <project> -run=ProjectPlugins -OutDir=<dir>
 *                                  [-Include=<regex>] [-Exclude=<regex>]
 *
 * Exit codes:
 *   0 = success (all plugins written, or filter matched zero plugins)
 *   2 = runtime error (bad args, plugin manager not available, or write failure)
 */
UCLASS()
class BLUEPRINTEXPORTER_API UProjectPluginsCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	UProjectPluginsCommandlet();

	//~ Begin UCommandlet Interface
	virtual int32 Main(const FString& Params) override;
	//~ End UCommandlet Interface
};
