// Copyright Ten Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UStateTree;
struct FAssetData;
struct FExportedBlueprint;

// Shared per-asset inventory-emission surface — factored out of
// `ProjectInventoryCommandlet.cpp` (M27.3.1) so the bridge re-export
// (`AssetReExporter`) and the full-sweep commandlet use the exact same
// code paths. Before M27.3.1 the bridge re-export wrote a placeholder
// `.md` + stub coverage block; now both callers produce byte-identical
// output for UBlueprint + StateTree.
//
// Anything in this namespace is the single source of truth for the
// inventory's per-asset file format. Don't duplicate logic into the
// commandlet or the re-exporter — extend here instead.
namespace BlueprintExporter::InventoryEmit
{
	// ---- shared class-name sets ----

	// UBlueprint-family class names the inventory pipeline processes through
	// the `UBlueprint` / `FBlueprintSerializer` path. Matched on short class
	// FName (via `FAssetData::AssetClassPath.GetAssetName()`) so detection
	// survives engine/plugin module reshuffles.
	const TSet<FName>& GetUBlueprintFamilyClassNames();

	// ---- small shared helpers ----

	// Map `/Game/TestBlueprints/BP_Foo` -> `<OutDir>/Assets/Game/TestBlueprints/BP_Foo`
	// (extensionless — caller appends `.md` / `.meta.json` / `.deep.md`).
	FString BuildAssetOutputBase(const FString& OutDir, const FString& PackageName);

	// Markdown table-cell escaping: `|` breaks column boundaries, embedded
	// newlines break the row. Collapse to inline-safe form.
	FString EscTbl(const FString& In);

	// `/Script/Module.Class` -> `Class`. Defensive — returns the input
	// unchanged if no `.` is present.
	FString StripScriptPrefix(const FString& ClassPath);

	// Pretty-print JSON via UE's default policy + write atomically. Returns
	// true iff the serialization AND the disk write succeeded.
	bool WriteJsonToFile(const TSharedPtr<FJsonObject>& Root, const FString& OutPath);

	// Integer-clamped percent; empty buckets are 100% by convention so an
	// empty asset doesn't drag an aggregate score down.
	int32 ComputeCoveragePercent(int32 Total, int32 Documented);

	// Build the non-UBP shape of the `.meta.json` `coverage` block — a
	// single primary bucket plus a `specialized` section listing
	// applicable vs documented named sub-sections. Suppresses the
	// `applicable` list entirely when the primary bucket is empty
	// (so `PrimaryTotal == 0` scores 100% and keeps HEALTH_REPORT clean).
	TSharedPtr<FJsonObject> BuildNonUBPCoverageJson(
		const TCHAR* PrimaryBucketName,
		int32 PrimaryTotal,
		int32 PrimaryDocumented,
		const TArray<FString>& SpecializedApplicable,
		const TArray<FString>& SpecializedDocumented,
		int32& OutOverallPct);

	// ---- big entry points ----

	// Full Tier 1 Markdown for a UBlueprint-family asset. Matches the
	// `<Path>.md` content that the commandlet's Phase 1 sweep emits
	// byte-for-byte.
	FString RenderBlueprintMarkdown(const FExportedBlueprint& Data);

	// Write the full `.meta.json` for a UBlueprint-family asset. Returns
	// true on success, false if ToJson() returned null or the disk write
	// failed. `OutOverallPct` receives the coverage-block percentage.
	bool WriteMetaJson(
		const FExportedBlueprint& Data,
		const FString& OutPath,
		int32& OutOverallPct);

#if WITH_STATETREE_SUPPORT
	// Full `.md` + `.meta.json` (+ optional `.deep.md`) emission for a
	// UStateTree asset. Mirrors the commandlet's `EmitStateTreeAsset`
	// signature exactly so the commandlet can call it with a one-line
	// delegation. When `bEmitDeepDump` is true, also writes the Tier 2
	// file via `DeepDump::RenderStateTreeMarkdown`.
	bool EmitStateTreeAsset(
		const FAssetData& AssetData,
		UStateTree* ST,
		const FString& MdPath,
		const FString& MetaPath,
		int32& OutOverallPct,
		FString& OutError,
		bool bEmitDeepDump,
		const FString& DeepPath);
#endif
}
