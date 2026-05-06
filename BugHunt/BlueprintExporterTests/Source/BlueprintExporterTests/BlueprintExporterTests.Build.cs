// Copyright 10 Chambers. All Rights Reserved.

using UnrealBuildTool;

public class BlueprintExporterTests : ModuleRules
{
	public BlueprintExporterTests(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Json",
				"JsonUtilities",
				"BlueprintExporter",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"AssetRegistry",
				"AssetTools",
				"BlueprintGraph",
				"AnimGraph",
				"AnimGraphRuntime",
				"Kismet",
				"KismetCompiler",
				"UnrealEd",
				"EditorSubsystem",
				"EditorFramework",
				"Projects",
				"ToolMenus",
				"AIModule",
				"GameplayTasks",
				"NavigationSystem",
				"GameplayTags",
				"UMG",
				"UMGEditor",
				"MovieScene",
				"MovieSceneTracks",
				"Niagara",
				"PropertyEditor",
				"InputCore",
				"Slate",
				"SlateCore",
			}
		);

		// Optional modules: match BlueprintExporter's detection for StateTree/StructUtils
		bool bHasStateTree = false;
		try
		{
			string StateTreeDir = GetModuleDirectory("StateTreeModule");
			bHasStateTree = !string.IsNullOrEmpty(StateTreeDir);
		}
		catch
		{
			bHasStateTree = false;
		}

		if (bHasStateTree)
		{
			PublicDefinitions.Add("WITH_STATETREE_SUPPORT=1");
			PrivateDependencyModuleNames.AddRange(new string[]
			{
				"StateTreeModule",
				"StateTreeEditorModule",
				"StructUtils",
			});
		}
		else
		{
			PublicDefinitions.Add("WITH_STATETREE_SUPPORT=0");
		}

		// GAS is optional for BP_GAS_Ability fixture
		bool bHasGAS = false;
		try
		{
			string GASDir = GetModuleDirectory("GameplayAbilities");
			bHasGAS = !string.IsNullOrEmpty(GASDir);
		}
		catch
		{
			bHasGAS = false;
		}

		if (bHasGAS)
		{
			PublicDefinitions.Add("WITH_GAS_SUPPORT=1");
			PrivateDependencyModuleNames.AddRange(new string[]
			{
				"GameplayAbilities",
			});
		}
		else
		{
			PublicDefinitions.Add("WITH_GAS_SUPPORT=0");
		}
	}
}
