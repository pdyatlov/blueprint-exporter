// Copyright Ten Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Scoped per-asset inventory refresh, called from the editor bridge after a
// successful `apply_plan` (M27.3). Not a full commandlet replacement: full
// coverage / DEPENDENCY_GRAPH / CLASS_TREE regeneration still requires
// `refresh_inventory`. This path only rewrites the three per-asset sidecars
// for the assets a plan actually touched, so the agent's next retrieval call
// (`get_asset_deep_dump` / `get_asset_meta`) sees the post-plan state without
// paying the full-project re-scan cost.
namespace BlueprintExporter::ReExport
{
	enum class EReExportStatus : uint8
	{
		Ok,
		Unsupported,   // type out of bridge-refresh scope (not UBP / not StateTree)
		LoadFailed,    // asset registry or load() returned null
		SerializeFailed,
		WriteFailed,
	};

	struct FReExportResult
	{
		FString PackageName;          // `/Game/...` path, as passed in
		EReExportStatus Status = EReExportStatus::Ok;
		FString ClassName;            // short class name of the loaded asset (diagnostics)
		TArray<FString> WrittenFiles; // absolute paths that were written
		FString Error;                // populated only on failure
	};

	// Re-emit `.md` / `.meta.json` / `.deep.md` for a single asset into the
	// inventory root's `Assets/` subtree. `PackageName` is a `/Game/...` path
	// (matching AssetRegistry). `InventoryRoot` is an absolute directory path.
	//
	// Scope for M27.3: UBlueprint family + UStateTree. Other asset types return
	// `EReExportStatus::Unsupported` and leave the existing files untouched —
	// the caller should surface this in the plan run-report so the agent knows
	// to invoke `refresh_inventory` if it cares about those sidecars.
	//
	// The `.md` written by this path is a brief placeholder that points at
	// `get_asset_deep_dump` for the full post-plan detail. Full-fidelity Tier 1
	// `.md` rendering lives in `ProjectInventoryCommandlet` and is not factored
	// out here to avoid duplicating ~300 lines of per-type rendering logic.
	// The `.deep.md` IS fully regenerated via the existing Tier 2 renderer, so
	// the agent's `get_asset_deep_dump` / `search_deep_dumps` consumers see
	// ground truth. `.meta.json` is regenerated via `FExported*::ToJson()`
	// with a stub `coverage` block marked `{refreshed_by: "bridge_reexport"}`
	// so downstream tools can tell targeted refresh apart from full sweep.
	FReExportResult ReExportAsset(
		const FString& PackageName,
		const FString& InventoryRoot);

	// Stringify a status code for logs / run reports.
	const TCHAR* ToString(EReExportStatus Status);
}
