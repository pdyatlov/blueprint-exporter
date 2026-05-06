// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
 * Resolve a -Path=/Game/... or -TargetBP=/Game/... argument into a sorted list
 * of Blueprint object paths via the AssetRegistry. Accepts either:
 *   - a directory path ("/Game/Foo" or "/Game/Foo/") — recursively enumerates
 *     every UBlueprint under it.
 *   - a single asset reference ("/Game/Foo/BP_Thing" or "/Game/Foo/BP_Thing.BP_Thing")
 *     — returned as-is (after directory expansion yields zero matches).
 *
 * Caller is responsible for `SearchAllAssets(true)` if a prior scan hasn't
 * completed; this function does not force-trigger a new scan.
 *
 * Returns false if Path does not start with "/Game/"; populates OutError.
 */
bool ResolveBlueprintTargets(const FString& Path, TArray<FString>& OutObjectPaths, FString& OutError);
