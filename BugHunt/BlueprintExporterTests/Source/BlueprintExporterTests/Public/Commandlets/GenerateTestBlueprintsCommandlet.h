// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "GenerateTestBlueprintsCommandlet.generated.h"

/**
 * Generates the BlueprintExporter bug-hunt fixture set programmatically.
 *
 * Usage:
 *   UnrealEditor-Cmd.exe TestProject/BlueprintExporterTests.uproject ^
 *     -run=GenerateTestBlueprints [-Only=<area>] [-Force] ^
 *     -nullrhi -unattended -nopause
 *
 * Options:
 *   -Only=<name>    Generate only one fixture (name matches the fixture catalog)
 *   -Tier=A|B|C     Generate only fixtures at or above a given priority tier
 *   -Force          Regenerate even if output already exists
 *
 * Output:
 *   /Game/TestBlueprints/<fixture>  .uasset
 *   /Game/Fixtures/<asset>          .uasset  (skeletons, placeholder meshes etc.)
 *
 * Exit codes:
 *   0 = All requested fixtures generated
 *   1 = Partial failure (one or more fixtures failed)
 *   2 = Runtime error
 */
UCLASS()
class UGenerateTestBlueprintsCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	UGenerateTestBlueprintsCommandlet();

	virtual int32 Main(const FString& Params) override;
};
