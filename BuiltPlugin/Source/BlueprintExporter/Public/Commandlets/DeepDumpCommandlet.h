// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "DeepDumpCommandlet.generated.h"

/**
 * Tier 2 of the project-inventory pipeline (see PROJECT_INVENTORY_BRIEF.md §6).
 *
 * On-demand single-asset deep dump. Where Phase 1 (ProjectInventory) emits a
 * Tier 1 summary per asset — variable list, function signatures, graph node
 * counts — Tier 2 emits the full graph detail: every node in every graph with
 * class / title / pin layout / default values / link list, per-state AnimGraph
 * node dumps for AnimBP state machines, and per-transition rule graph dumps.
 *
 * First slice scope: UBlueprint-family assets only (`UBlueprint`,
 * `UAnimBlueprint`, `UWidgetBlueprint`, `UControlRigBlueprint`). Other
 * logic-bearing classes (BT / ST / DT / UDS / UDE / SmartObject / Chooser /
 * PoseSearch / EnvQuery) already render near-complete detail in their typed
 * Tier 1 handlers (M3.1 → M3.3), so they print an explanatory notice pointing
 * at the Tier 1 `.md` + `.meta.json` and exit 0.
 *
 * Usage:
 *   UnrealEditor-Cmd.exe <project> -run=DeepDump
 *                                  -Asset=/Game/Path/To/AssetName
 *                                  -OutDir=<dir>
 *
 * Output: `<OutDir>/<AssetName>.deep.md` written via atomic `.tmp` + rename.
 *
 * Exit codes:
 *   0 = success (file written, or asset class is out-of-scope and notice emitted)
 *   2 = runtime error (bad args, asset not found, serializer failure, or write failure)
 */
UCLASS()
class BLUEPRINTEXPORTER_API UDeepDumpCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	UDeepDumpCommandlet();

	//~ Begin UCommandlet Interface
	virtual int32 Main(const FString& Params) override;
	//~ End UCommandlet Interface
};
