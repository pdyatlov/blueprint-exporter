// Copyright 10 Chambers. All Rights Reserved.

#include "Commandlets/BlueprintAssetEnumeration.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "AssetRegistry/ARFilter.h"
#include "Engine/Blueprint.h"
#include "Modules/ModuleManager.h"

bool ResolveBlueprintTargets(const FString& Path, TArray<FString>& OutObjectPaths, FString& OutError)
{
	OutObjectPaths.Reset();
	OutError.Reset();

	if (!Path.StartsWith(TEXT("/Game/")))
	{
		OutError = TEXT("path must start with /Game/");
		return false;
	}

	FAssetRegistryModule& ARM = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AR = ARM.Get();

	// If the argument ends with "/" or contains no "." segment, it's a directory —
	// enumerate UBlueprint recursively. Otherwise treat it as a single object path.
	const bool bLooksLikeDirectory = Path.EndsWith(TEXT("/")) || !Path.Contains(TEXT("."));
	if (bLooksLikeDirectory)
	{
		// Strip trailing slash for FName-based path filter.
		FString PackagePath = Path;
		if (PackagePath.EndsWith(TEXT("/")) && PackagePath.Len() > 1)
		{
			PackagePath.LeftChopInline(1);
		}

		FARFilter Filter;
		Filter.bRecursivePaths = true;
		Filter.bRecursiveClasses = true; // include UWidgetBlueprint, UAnimBlueprint, etc.
		Filter.PackagePaths.Add(FName(*PackagePath));
		Filter.ClassPaths.Add(UBlueprint::StaticClass()->GetClassPathName());

		TArray<FAssetData> Assets;
		AR.GetAssets(Filter, Assets);

		if (Assets.Num() == 0)
		{
			// Fall back to treating the argument as a single package path (no trailing /).
			OutObjectPaths.Add(Path);
		}
		else
		{
			OutObjectPaths.Reserve(Assets.Num());
			for (const FAssetData& A : Assets)
			{
				OutObjectPaths.Add(A.GetObjectPathString());
			}
			// Deterministic order across runs — required for resume + report stability.
			OutObjectPaths.Sort();
		}
	}
	else
	{
		OutObjectPaths.Add(Path);
	}

	return true;
}
