// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UObject;

/**
 * Tier 2 deep dump for `UCustomizableObjectInstance` (Mutable customization
 * instance).
 *
 * A `UCustomizableObjectInstance` is a saved, parameterised snapshot of a
 * `UCustomizableObject` — the authored parameter values (bool / int enum /
 * float / texture / vector / projector / transform / skeletal-mesh /
 * material) plus the active Mutable optimization state. Runtime generates a
 * skeletal mesh + material set from (UCO compiled graph × UCOI param overrides)
 * on demand; at rest the instance is just the parameter bundle.
 *
 * Tier 1 (inventory sweep) treats UCOI as "other" and emits schema-only
 * metadata. Tier 2 exposes the full authoring surface: the parent UCO link
 * and every non-transient parameter override, keyed by param name. Primary
 * use case per the M29 scope: "understand how Mutable works" without opening
 * the editor.
 *
 * Storage layout (per M29.0 Q5 finding):
 *   UCustomizableObjectInstance -> private UPROPERTY() FCustomizableObjectInstanceDescriptor Descriptor;
 *   FCustomizableObjectInstanceDescriptor has 9 typed arrays:
 *     - BoolParameters / IntParameters / FloatParameters / TextureParameters
 *     - SkeletalMeshParameters / MaterialParameters / VectorParameters
 *     - ProjectorParameters / TransformParameters
 *   plus transient int32 State.
 *   UCOI itself has inline `*_DEPRECATED` arrays (legacy) which we skip.
 *
 * Lives in its own TU (not `DeepDumpRenderer.cpp`) so the Mutable-specific
 * rendering stays out of the UBP/ST renderer file. **M29.6.2 ported this
 * implementation to zero compile-time Mutable dependency** — the file
 * compiles on any engine; dispatch is by class-name match
 * (`InstanceObject->GetClass()->GetFName() == "CustomizableObjectInstance"`);
 * every field read goes through reflection on the runtime-resolved UClass
 * / UScriptStruct; the one direct-UE_API call the M29.1 implementation
 * used (Descriptor::GetCurrentState) is replaced by a ProcessEvent call to
 * UCO::GetStateName via the shared `UFunctionCall` helpers from M29.6.1.
 * **M29.6.4 removed the `WITH_MUTABLE_SUPPORT` gate project-wide** so
 * callers no longer wrap the invocation in `#if WITH_MUTABLE_SUPPORT`.
 *
 * The public API takes `UObject*` so callers don't need to include
 * Mutable's public headers; the implementation class-name-matches
 * internally and falls back to `RenderOutOfScopeNotice` on type mismatch.
 */
namespace BlueprintExporter::DeepDump
{
	/** Render Tier 2 deep dump for a `UCustomizableObjectInstance`. */
	BLUEPRINTEXPORTER_API FString RenderCustomizableObjectInstanceMarkdown(UObject* InstanceObject);
}
