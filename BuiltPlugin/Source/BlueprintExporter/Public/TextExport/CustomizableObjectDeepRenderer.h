// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UObject;

/**
 * Tier 2 deep dump for `UCustomizableObject` (Mutable authoring root).
 *
 * A `UCustomizableObject` is the authoring-side asset that describes how a
 * customizable character / item is assembled from parameterised source
 * components, materials, textures, and layout / modifier / table / group /
 * variation nodes. The asset stores two distinct layers:
 *
 *   - The **authoring surface** — the parameter schema (name, type,
 *     multidim flag, default value, UI metadata), the state list (each
 *     state enumerates a subset of parameters that remain editable at
 *     runtime), and the editor node graph (`Source: TObjectPtr<UEdGraph>`,
 *     private, `WITH_EDITORONLY_DATA`). Deterministic across saves and
 *     the primary signal an AI consumer needs to understand "how this
 *     Mutable asset works".
 *
 *   - The **compiled model** — a derived-data blob held on the private
 *     companion object and the `UCustomizableObjectBulk` BulkData. Carries
 *     a `FGuid VersionId` explicitly regenerated on save (per the header
 *     comment "Used to verify the derived data matches this version"),
 *     and `PreSave` / `PostSaveRoot` / `BeginCacheForCookedPlatformData`
 *     overrides suggest build-context-dependent work. Skipped by policy
 *     (M29.0 Q3) — honoring the "Never guess values" principle; a visible
 *     skip marker goes in the rendered output.
 *
 * Tier 1 (`ProjectInventoryCommandlet` Phase 1) treats UCO as "other" and
 * emits schema-only metadata. Tier 2 exposes the full authoring surface —
 * enough for static analysis to reason about which parameter options exist,
 * which node a projector or table references, which state exposes which
 * parameters to runtime.
 *
 * Lives in its own TU (not `DeepDumpRenderer.cpp`) so the Mutable-specific
 * rendering stays out of the UBP / ST renderer file. **M29.6.3 ported this
 * implementation to zero compile-time Mutable dependency** — the file
 * compiles on any engine; dispatch is by class-name match
 * (`CO->GetClass()->GetFName() == "CustomizableObject"`); every UFUNCTION
 * call goes through the shared `UFunctionCall` helpers (ProcessEvent-based
 * reflection) from M29.6.1; `FindFProperty` keys off the runtime-resolved
 * UClass rather than `UCustomizableObject::StaticClass()`. No `MuCO/*`
 * includes and no `CustomizableObject` dep in Build.cs. **M29.6.4 removed
 * the `WITH_MUTABLE_SUPPORT` gate project-wide** — one BuiltPlugin DLL
 * handles CO assets in any Mutable-capable project.
 *
 * The public API takes `UObject*` so callers don't need to include
 * Mutable's public headers; the implementation class-name-matches
 * internally and falls back to `RenderOutOfScopeNotice` on type mismatch.
 */
namespace BlueprintExporter::DeepDump
{
	/** Render Tier 2 deep dump for a `UCustomizableObject`. */
	BLUEPRINTEXPORTER_API FString RenderCustomizableObjectMarkdown(UObject* CustomizableObject);
}
