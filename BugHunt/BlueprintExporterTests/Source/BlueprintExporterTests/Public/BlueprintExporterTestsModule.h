// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBlueprintExporterTests, Log, All);

/**
 * Editor-only test module for the BlueprintExporter plugin.
 *
 * Currently owns:
 *   - UGenerateTestBlueprintsCommandlet      (-run=GenerateTestBlueprints)
 *     Regenerates the committed fixtures under BugHunt/TestProject/Content/TestBlueprints/.
 *
 * Never part of a shipping build — lives under BugHunt/ and is only enabled by
 * BugHunt/TestProject.uproject.
 */
class FBlueprintExporterTestsModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
