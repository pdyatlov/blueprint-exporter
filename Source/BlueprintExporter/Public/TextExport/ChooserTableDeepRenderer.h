// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UObject;

/**
 * Tier 2 deep dump for `UChooserTable`.
 *
 * Where Tier 1 (`EmitChooserTableAsset` in `ProjectInventoryCommandlet`)
 * captures shape — per-column concrete struct type + has-filter/output/cost
 * flags, per-row concrete struct type, fallback type, context data types,
 * nested chooser paths — Tier 2 walks every `FInstancedStruct` (column, row,
 * fallback, context entry) and renders its full UPROPERTY table. That's what
 * exposes the authored values: which enum each `FEnumColumn` reads, the
 * per-row values that select each row, the asset each `FAssetChooser` row
 * produces, the range each `FFloatRangeColumn` accepts per row.
 *
 * Gated on `WITH_CHOOSER_SUPPORT` — Chooser ships as an optional plugin, same
 * pattern as the Tier 1 handler.
 *
 * The public API takes `UObject*` so callers don't need to include the
 * Chooser module headers; the implementation casts internally and falls back
 * to `RenderOutOfScopeNotice` on type mismatch or build-without-Chooser.
 */
namespace BlueprintExporter::DeepDump
{
	/** Render Tier 2 deep dump for a `UChooserTable`. */
	BLUEPRINTEXPORTER_API FString RenderChooserTableMarkdown(UObject* ChooserTableObject);
}
