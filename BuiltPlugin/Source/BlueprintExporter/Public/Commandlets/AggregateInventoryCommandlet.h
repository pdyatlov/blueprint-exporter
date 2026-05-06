// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "AggregateInventoryCommandlet.generated.h"

/**
 * Phase 2 of the project-inventory pipeline (see PROJECT_INVENTORY_BRIEF.md §5).
 *
 * Reads `.meta.json` sidecars emitted by `ProjectInventoryCommandlet`, builds
 * project-wide rollups, and writes them as deterministic Markdown (plus a
 * Graphviz `.dot` for the dependency graph). No assets are loaded.
 *
 * First M4 slice emits:
 *   - INDEX.md              — class/folder counts + Run Scoreboard (brief §11A)
 *                             + pointers to the other reports
 *   - CLASS_TREE.md         — BPs grouped under native parent + BP→BP chains
 *   - DEPENDENCY_GRAPH.md   — per-asset hard/soft refs (in and out)
 *   - dependency_graph.dot  — same graph in Graphviz form
 *   - REPLICATION_MATRIX.md — every replicated variable across the project
 *                             (RPCs pending the M3.1 serializer widening)
 *   - HEALTH_REPORT.md      — coverage gaps, failed/partial loads
 *   - SCOREBOARD_BASELINE.json — persisted baseline for §11A scoreboard
 *
 * Domain overviews (AI / ANIM / UI / GAS / STRUCTS_ENUMS) depend on
 * non-UBlueprint `.meta.json` from a future `ProjectInventory` slice and are
 * deliberately out of this first commit.
 *
 * Usage:
 *   UnrealEditor-Cmd.exe <project> -run=AggregateInventory -OutDir=<dir>
 *                                  [-InDir=<dir>] [-ResetBaseline]
 *
 * If `-InDir` is omitted it defaults to `<OutDir>/Assets` (the exact tree
 * `ProjectInventory` writes under).
 *
 * Exit codes:
 *   0 = success
 *   2 = runtime error (bad args, no .meta.json found, or write failure)
 */
UCLASS()
class BLUEPRINTEXPORTER_API UAggregateInventoryCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	UAggregateInventoryCommandlet();

	//~ Begin UCommandlet Interface
	virtual int32 Main(const FString& Params) override;
	//~ End UCommandlet Interface
};
