// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UObject;

/**
 * Tier 2 deep dump for `UCustomizableObjectMacroLibrary` (Mutable's
 * reusable-macro asset type).
 *
 * A macro library holds N `UCustomizableObjectMacro` entries. Each macro
 * has a name, a description, an authored set of input / output variables
 * (name + pin category + unique id), and its own `UEdGraph` that a
 * `UCustomizableObjectNodeMacroInstance` can reference from a parent UCO
 * graph. Tier 1 treats a COML as "other"; Tier 2 exposes the full
 * authoring surface per macro — the same level of detail M29.2 renders
 * for a UCustomizableObject asset's own graph, just repeated once per
 * macro.
 *
 * Implementation uses total UE reflection — walks the library asset's
 * UPROPERTYs by name (Macros → array of UCustomizableObjectMacro), then
 * walks each macro's UPROPERTYs by name (Name, Description, InputOutputs,
 * Graph). No include of the Private-only `CustomizableObjectMacroLibrary.h`
 * header; mirrors M11 / M29.1 / M29.2's zero-new-module-dep pattern.
 *
 * The node-graph walk reuses `BlueprintExporter::DeepRender::RenderEdGraphNodes`
 * (M29.3 refactor) so the per-node rendering shape matches M29.2 exactly,
 * including the `PinId=<32-hex>` → `PinId=<unstable>` masking applied to
 * every `FEdGraphPinReference`-typed UPROPERTY emitted by the walker.
 *
 * Lives in its own TU (not `DeepDumpRenderer.cpp`) so the Mutable-specific
 * rendering stays out of the UBP / ST renderer file. Was always written
 * zero-include (no `MuCO/*` headers, no typed `Cast<>`) via class-name
 * dispatch + UPROPERTY-by-name reflection; **M29.6.4 removed the
 * `WITH_MUTABLE_SUPPORT` gate project-wide** so the same implementation
 * now compiles on any engine.
 *
 * The public API takes `UObject*`; the implementation checks by class
 * name internally and falls back to `RenderOutOfScopeNotice` on type
 * mismatch.
 */
namespace BlueprintExporter::DeepDump
{
	/** Render Tier 2 deep dump for a `UCustomizableObjectMacroLibrary`. */
	BLUEPRINTEXPORTER_API FString RenderCustomizableObjectMacroLibraryMarkdown(UObject* MacroLibraryObject);
}
