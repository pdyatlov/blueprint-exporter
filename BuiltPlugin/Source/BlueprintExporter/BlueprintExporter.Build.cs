// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BlueprintExporter : ModuleRules
{
	public BlueprintExporter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
			}
		);

		PrivateIncludePaths.AddRange(
			new string[] {
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Json",
				"JsonUtilities",
			}
		);

		// Detect whether StateTreeModule is available at build time
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
				"GameplayTags",
				"PropertyBindingUtils",
			});
		}
		else
		{
			PublicDefinitions.Add("WITH_STATETREE_SUPPORT=0");
		}

		// Detect whether the Chooser plugin (UChooserTable) is available.
		// Mirrors the WITH_STATETREE_SUPPORT pattern. When absent, Choosers
		// fall through to EmitGenericNonUBPAsset.
		bool bHasChooser = false;
		try
		{
			string ChooserDir = GetModuleDirectory("Chooser");
			bHasChooser = !string.IsNullOrEmpty(ChooserDir);
		}
		catch
		{
			bHasChooser = false;
		}

		if (bHasChooser)
		{
			PublicDefinitions.Add("WITH_CHOOSER_SUPPORT=1");
			PrivateDependencyModuleNames.Add("Chooser");
		}
		else
		{
			PublicDefinitions.Add("WITH_CHOOSER_SUPPORT=0");
		}

		// Detect whether the PoseSearch plugin (UPoseSearchDatabase) is available.
		// Mirrors the WITH_CHOOSER_SUPPORT pattern. When absent, PoseSearchDatabase
		// falls through to EmitGenericNonUBPAsset.
		bool bHasPoseSearch = false;
		try
		{
			string PoseSearchDir = GetModuleDirectory("PoseSearch");
			bHasPoseSearch = !string.IsNullOrEmpty(PoseSearchDir);
		}
		catch
		{
			bHasPoseSearch = false;
		}

		if (bHasPoseSearch)
		{
			PublicDefinitions.Add("WITH_POSESEARCH_SUPPORT=1");
			PrivateDependencyModuleNames.Add("PoseSearch");
		}
		else
		{
			PublicDefinitions.Add("WITH_POSESEARCH_SUPPORT=0");
		}

		// Detect whether the SmartObjects plugin (USmartObjectDefinition) is
		// available. Mirrors the WITH_POSESEARCH_SUPPORT pattern. When absent,
		// SmartObjectDefinition falls through to EmitGenericNonUBPAsset.
		// The *plugin* is named "SmartObjects" but the *runtime module* is
		// "SmartObjectsModule" — the module name is what GetModuleDirectory
		// needs. Runtime deps pulled in transitively: GameplayTags, WorldConditions.
		bool bHasSmartObjects = false;
		try
		{
			string SmartObjectsDir = GetModuleDirectory("SmartObjectsModule");
			bHasSmartObjects = !string.IsNullOrEmpty(SmartObjectsDir);
		}
		catch
		{
			bHasSmartObjects = false;
		}

		if (bHasSmartObjects)
		{
			PublicDefinitions.Add("WITH_SMARTOBJECTS_SUPPORT=1");
			PrivateDependencyModuleNames.Add("SmartObjectsModule");
			// FWorldConditionQueryDefinition::IsValid() is dllimported from
			// WorldConditions. SmartObjectsModule declares it as a public dep
			// (which gets us the header) but link deps must be explicit in
			// the consuming module — hence this line.
			PrivateDependencyModuleNames.Add("WorldConditions");
		}
		else
		{
			PublicDefinitions.Add("WITH_SMARTOBJECTS_SUPPORT=0");
		}

		// M28.6.1 — detect GameplayTagsEditor (editor plugin shipping with stock
		// UE 5.7) so AddGameplayTag can delegate to
		// IGameplayTagsEditorModule::AddNewGameplayTagToINI. The function lives
		// on the editor module's interface, not the runtime UGameplayTagsManager
		// (the M28 phase table assumed the latter — research at M28.6.0
		// corrected this). When the editor plugin is absent, AddGameplayTag
		// compiles out and returns a structured error pointing at the missing
		// dep; the rest of the plugin builds fine.
		bool bHasGameplayTagsEditor = false;
		try
		{
			string GteDir = GetModuleDirectory("GameplayTagsEditor");
			bHasGameplayTagsEditor = !string.IsNullOrEmpty(GteDir);
		}
		catch
		{
			bHasGameplayTagsEditor = false;
		}

		if (bHasGameplayTagsEditor)
		{
			PublicDefinitions.Add("WITH_GAMEPLAYTAGSEDITOR_SUPPORT=1");
			PrivateDependencyModuleNames.AddRange(new string[]
			{
				"GameplayTagsEditor",
				"GameplayTags",  // runtime module — UGameplayTagsManager::IsDictionaryTag
				                 // (already pulled in transitively via WITH_STATETREE_SUPPORT
				                 // when StateTree is present, but list explicitly so the
				                 // M28.6.1 path holds when StateTree is absent)
			});
		}
		else
		{
			PublicDefinitions.Add("WITH_GAMEPLAYTAGSEDITOR_SUPPORT=0");
		}

		// M29.6 — Mutable renderers are engine-agnostic via runtime reflection:
		// the three renderers (UCustomizableObjectInstance / UCustomizableObject /
		// UCustomizableObjectMacroLibrary) compile on any engine, dispatch by
		// class-name match, and invoke Mutable UFUNCTIONs through ProcessEvent
		// via the shared `UFunctionCall` helpers in DeepRenderShared. One
		// BuiltPlugin DLL handles CO assets in any Mutable-capable project,
		// regardless of whether the Mutable plugin was present when this DLL
		// was built. No compile-time link dep on `CustomizableObject`.

		// M27.1 — detect WebSocketNetworking (experimental plugin shipping with stock UE 5.7).
		// When absent, the bridge compiles out entirely and the plugin behaves as pre-M27.
		bool bHasWebSocketNetworking = false;
		try
		{
			string WsnDir = GetModuleDirectory("WebSocketNetworking");
			bHasWebSocketNetworking = !string.IsNullOrEmpty(WsnDir);
		}
		catch
		{
			bHasWebSocketNetworking = false;
		}

		if (bHasWebSocketNetworking)
		{
			PublicDefinitions.Add("WITH_BPXBRIDGE_SUPPORT=1");
			PrivateDependencyModuleNames.Add("WebSocketNetworking");
		}
		else
		{
			PublicDefinitions.Add("WITH_BPXBRIDGE_SUPPORT=0");
		}

		// M27.2 — detect PythonScriptPlugin for in-process Python execution
		// via IPythonScriptPlugin::ExecPythonCommandEx. Ships with stock UE
		// but is experimental; gate so the plugin compiles cleanly without it.
		bool bHasPythonScriptPlugin = false;
		try
		{
			string PspDir = GetModuleDirectory("PythonScriptPlugin");
			bHasPythonScriptPlugin = !string.IsNullOrEmpty(PspDir);
		}
		catch
		{
			bHasPythonScriptPlugin = false;
		}

		if (bHasPythonScriptPlugin)
		{
			PublicDefinitions.Add("WITH_BPXPYTHON_SUPPORT=1");
			PrivateDependencyModuleNames.Add("PythonScriptPlugin");
		}
		else
		{
			PublicDefinitions.Add("WITH_BPXPYTHON_SUPPORT=0");
		}

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"AIModule",                // UBehaviorTree + UBlackboardData introspection (ProjectInventory M3.1)
				"AnimGraph",
				"AnimGraphRuntime",
				"AssetRegistry",
				"AssetTools",
				"BlueprintGraph",
				"UMG",                     // UWidget / UPanelWidget / UPanelSlot walk (Track A)
				"UMGEditor",               // UWidgetBlueprint (inherits UBaseWidgetBlueprint via UnrealEd) — some editor headers live here
				"ContentBrowser",
				"DeveloperSettings",
				"EditorFramework",
				"EditorStyle",
				"EditorSubsystem",
				"GraphEditor",
				"InputCore",
				"Kismet",
				"KismetCompiler",
				"Projects",
				"PropertyEditor",
				"Slate",
				"SlateCore",
				"ToolMenus",
				"ApplicationCore",
				"UnrealEd",
			}
		);

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
		);
	}
}
