// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UObject;

/**
 * Tier 2 deep dump for `UDataTable`.
 *
 * Where Tier 1 (`EmitDataTableAsset` in `ProjectInventoryCommandlet`)
 * captures schema only (row struct, column list with name / type / category /
 * tooltip, and the sorted row-name list) — deliberately scoped per brief §4
 * to "schema only" because rows can be arbitrary blobs — Tier 2 walks every
 * row and renders its **authored values**. For each row in `RowMap` we emit
 * a property table whose cells come from `ExportTextItem_Direct` against the
 * row struct's fields, alpha-sorted for determinism.
 *
 * This is what turns a Tier 1 "DT_ItemCatalog has 42 rows over S_ItemRow"
 * summary into a Tier 2 "row `Sword_Iron` has Damage=15 / Icon=… / Tier=Common"
 * dump — the actual data the gameplay code reads at runtime.
 *
 * No build gate needed — `UDataTable` lives in the Engine module, which is
 * always a public dep of this plugin.
 *
 * The public API takes `UObject*` so callers don't need to include Engine
 * headers at the call site; the cast happens inside the .cpp and falls back
 * to `RenderOutOfScopeNotice` on type mismatch.
 */
namespace BlueprintExporter::DeepDump
{
	/** Render Tier 2 deep dump for a `UDataTable`. */
	BLUEPRINTEXPORTER_API FString RenderDataTableMarkdown(UObject* DataTableObject);
}
