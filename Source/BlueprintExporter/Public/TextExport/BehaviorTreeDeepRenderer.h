// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UObject;

/**
 * Tier 2 deep dump for `UBehaviorTree`.
 *
 * Where Tier 1 (`EmitBehaviorTreeAsset` in `ProjectInventoryCommandlet`)
 * captures tree shape — composite / task nesting, attached decorators and
 * services with their class + instance name — Tier 2 walks every node in
 * that tree and renders its **full UPROPERTY table**. That's what records
 * the authored values: `AcceptableRadius` on a `BTTask_MoveTo`, `Interval`
 * on a `BTService_DefaultFocus`, `FlowAbortMode` on a `BTDecorator_Blackboard`,
 * `BlackboardKey` selectors, and so on — the actual configuration that
 * determines behavior, not just the class names.
 *
 * AIModule (which owns `UBTNode` / `UBTCompositeNode` / `UBTTaskNode` /
 * `UBTDecorator` / `UBTService`) ships with the engine and is already a
 * non-optional dep of this plugin, so no `WITH_BEHAVIORTREE_SUPPORT` gate is
 * needed — unlike SmartObjects / Chooser / PoseSearch this renderer can link
 * unconditionally.
 *
 * The public API takes `UObject*` so callers don't need to include the
 * AIModule headers; the implementation casts internally and falls back to
 * `RenderOutOfScopeNotice` on type mismatch.
 */
namespace BlueprintExporter::DeepDump
{
	/** Render Tier 2 deep dump for a `UBehaviorTree`. */
	BLUEPRINTEXPORTER_API FString RenderBehaviorTreeMarkdown(UObject* BehaviorTreeObject);
}
