// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UObject;

/**
 * Tier 2 deep dump for `UEnvQuery` (Environment Query System).
 *
 * Where Tier 1 (`EmitEnvQueryAsset` in `ProjectInventoryCommandlet`)
 * captures shape — per-option generator class name + ordered list of test
 * class names — Tier 2 walks the generator UObject and every test UObject
 * and renders their full UPROPERTY tables. That's what exposes the authored
 * values: the radius / center actor / item type / data binding on a
 * generator, the `TestPurpose` (filter vs. score vs. both) / `FilterType` /
 * `ScoringEquation` / `ClampMin` / `Weight` / distance parameters / trace
 * config / gameplay-tag filter on each test.
 *
 * No build gate — AIModule (which owns `UEnvQuery` / `UEnvQueryOption` /
 * `UEnvQueryGenerator` / `UEnvQueryTest`) ships with the engine and is
 * already a non-optional dep of this plugin.
 *
 * Known limitation as of M15: DOW has **zero** EnvQuery assets in /Game
 * content, so this renderer's per-option property-table path is code-
 * reviewed but unexercised by the canonical test corpus — same coverage
 * gap M12 BT shipped with. When DOW authors its first EQS asset, the
 * next sweep will exercise this path end-to-end automatically (no further
 * code changes required).
 *
 * The public API takes `UObject*` so callers don't need to include the
 * AIModule headers at the call site; the implementation casts internally
 * and falls back to `RenderOutOfScopeNotice` on type mismatch.
 */
namespace BlueprintExporter::DeepDump
{
	/** Render Tier 2 deep dump for a `UEnvQuery`. */
	BLUEPRINTEXPORTER_API FString RenderEnvQueryMarkdown(UObject* EnvQueryObject);
}
