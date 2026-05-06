// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UObject;

/**
 * Tier 2 deep dump for `USmartObjectDefinition`.
 *
 * Where Tier 1 (`EmitSmartObjectDefinitionAsset` in `ProjectInventoryCommandlet`)
 * captures structural shape — slot count, behavior-definition paths, definition-
 * data type names, precondition-set bool, parameter-bag count — Tier 2 walks
 * each behavior definition's UPROPERTYs and each slot's `FInstancedStruct`
 * `DefinitionData` fields and renders their **configured values**. The single
 * most load-bearing thing this exposes is the `StateTreeReference` on
 * `UGameplayInteractionSmartObjectBehaviorDefinition`, which is the link from
 * the SO definition to the StateTree that runs the interaction (e.g., the path
 * from `SO_BenchDefinition` to `ST_SmartObject_Bench`).
 *
 * Lives in its own translation unit (rather than `DeepDumpRenderer.cpp`) so
 * the SmartObjects module dependency stays gated by `WITH_SMARTOBJECTS_SUPPORT`
 * without polluting the UBP/ST renderer file.
 *
 * The public API takes `UObject*` so callers don't need to include the
 * SmartObjects module headers; the implementation casts internally and falls
 * back to `RenderOutOfScopeNotice` on type mismatch or build-without-SO.
 */
namespace BlueprintExporter::DeepDump
{
	/** Render Tier 2 deep dump for a `USmartObjectDefinition`. */
	BLUEPRINTEXPORTER_API FString RenderSmartObjectDefinitionMarkdown(UObject* Def);
}
