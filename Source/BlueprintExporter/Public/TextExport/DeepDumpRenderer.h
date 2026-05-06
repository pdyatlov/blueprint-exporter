// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

struct FExportedBlueprint;
struct FExportedStateTree;

/**
 * Tier 2 "deep dump" Markdown renderers for the project-inventory pipeline.
 *
 * Shared by `DeepDumpCommandlet` (single-asset `-run=DeepDump`) and
 * `ProjectInventoryCommandlet -DeepDump` (sweep mode). Input is an already-
 * serialized `FExportedBlueprint` or `FExportedStateTree` with any run-drifting
 * fields (e.g. `ExportTimestamp`) blanked by the caller per brief §8.
 *
 * Output is deterministic: sorted / traversal order matches the single-asset
 * DeepDump byte-for-byte.
 */
namespace BlueprintExporter::DeepDump
{
	/** Full per-node pin-level dump for UBlueprint-family assets. */
	BLUEPRINTEXPORTER_API FString RenderBlueprintMarkdown(const FExportedBlueprint& Data);

	/** Full per-task/condition/evaluator property dump for UStateTree assets. */
	BLUEPRINTEXPORTER_API FString RenderStateTreeMarkdown(const FExportedStateTree& Data);

	/**
	 * Tier 2 dump for a UDataAsset-derived UObject instance — the saved `.uasset`
	 * data, not the BP class that defines its shape. Walks the instance's
	 * UPROPERTYs (inherited + BP-declared) and diffs against the instance's own
	 * class CDO, emitting only authored overrides. Complements the existing
	 * `.md` / `.meta.json` which covers the class shape (`BP_XYZ_DataAsset`)
	 * but misses the populated `/Game/.../XYZ_DataAsset.uasset` instance.
	 *
	 * Skips the M11–M16 plumbing allowlist (`UberGraphFrame` / `CachedFrameStateTree`)
	 * and `CPF_Transient | CPF_DuplicateTransient`. Values are the flat
	 * `ExportTextItem_Direct` blob — nested struct / array content is parseable
	 * but dense; instanced-subobject recursion lands in a later slice if needed.
	 */
	BLUEPRINTEXPORTER_API FString RenderDataAssetInstanceMarkdown(UObject* Asset);

	/**
	 * Short notice file for asset classes outside the supported Tier 2 set
	 * (anything that isn't UBlueprint-family or UStateTree).
	 *
	 * Written as `<Asset>.deep.md` so the sibling-to-Tier-1 symmetry holds
	 * during a sweep — consumers always know where to look for Tier 2 output
	 * and see "here is what you have at Tier 1 instead".
	 */
	BLUEPRINTEXPORTER_API FString RenderOutOfScopeNotice(
		const FString& AssetName,
		const FString& PackagePath,
		const FString& ClassName);
}
