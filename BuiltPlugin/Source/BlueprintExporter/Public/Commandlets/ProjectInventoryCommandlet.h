// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "ProjectInventoryCommandlet.generated.h"

/**
 * Phase 1 of the project-inventory pipeline (see PROJECT_INVENTORY_BRIEF.md §4).
 *
 * Streams through every logic-bearing asset under the mount point, loads each
 * one, introspects it via the existing `FBlueprintSerializer`, and emits a
 * per-asset Markdown summary plus a structured `.meta.json` sidecar. Memory
 * is released between assets via `CollectGarbage` (brief §11A Option A).
 *
 * First slice scope: UBlueprint-family assets only (`UBlueprint`,
 * `UAnimBlueprint`, `UWidgetBlueprint`, `UControlRigBlueprint`). Specialized
 * sections (AnimBP state-machine detail, WidgetBP widget tree, BT/ST/GAS etc.)
 * and non-UBlueprint logic-bearing types (BehaviorTree, StateTree,
 * UserDefinedStruct, UserDefinedEnum, DataTable, SmartObject, Chooser,
 * PoseSearch) land in follow-on M3 slices.
 *
 * Usage:
 *   UnrealEditor-Cmd.exe <project> -run=ProjectInventory -OutDir=<dir>
 *                                  [-MountPoint=/Game]
 *                                  [-Filter=/Game/<subpath>]
 *                                  [-Resume]
 *                                  [-DeepDump]
 *                                  [-GcEvery=<N>]
 *
 * Output layout (brief §4):
 *   <OutDir>/Assets/Game/<SubPath>/<AssetName>.md
 *   <OutDir>/Assets/Game/<SubPath>/<AssetName>.meta.json
 *   <OutDir>/Assets/Game/<SubPath>/<AssetName>.deep.md   (with -DeepDump)
 *   <OutDir>/FAILED_LOADS.md        (only if any failed)
 *   <OutDir>/PARTIAL_LOADS.md       (only if any produced without full coverage)
 *
 * `-DeepDump`: enable Tier 2 sweep. Every processed asset emits a `.deep.md`
 * sibling — UBlueprint-family and UStateTree get the full per-node / per-task
 * detail via the shared `TextExport/DeepDumpRenderer`; other in-scope classes
 * get a short "out-of-scope, see Tier 1" notice so the sibling pattern holds
 * across the sweep.
 *
 * Resume semantics: `.meta.json` is written **after** `.md`, so its presence
 * is the "asset fully emitted" marker. `-Resume` skips any asset whose
 * `.meta.json` already exists and is non-empty.
 *
 * Exit codes:
 *   0 = success (framework completed; individual asset failures do not fail
 *       the run by default — they're aggregated into FAILED_LOADS.md)
 *   2 = runtime error (bad args, registry failure, or write failure)
 */
UCLASS()
class BLUEPRINTEXPORTER_API UProjectInventoryCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	UProjectInventoryCommandlet();

	//~ Begin UCommandlet Interface
	virtual int32 Main(const FString& Params) override;
	//~ End UCommandlet Interface
};
