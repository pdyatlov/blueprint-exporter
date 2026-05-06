// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "Schema/BlueprintExportTypes.h"

/**
 * Schema for M7 (Project Plugins scanner) — see PROJECT_INVENTORY_BRIEF.md and
 * WIP_INVENTORY.md for the full scope. Output structure mirrors the rest of
 * the inventory pipeline: one top-level rollup (`PLUGINS.md`) plus per-plugin
 * sidecars at `PluginInventory/<PluginName>.{md,meta.json}`.
 *
 * P0 captures uplugin metadata only: descriptor fields, module list,
 * plugin-reference dependencies. Native-type enumeration (`NativeTypes[]`) is
 * reserved for P1 — shaped into the P0 schema so the sidecar format stays
 * stable once P1 starts populating it.
 */

/**
 * Generic reflected-property record. Field-compatible with
 * `FExportedStateTreeProperty` — kept as a separate type to avoid pulling the
 * StateTree types into the plugins schema. If the duplication becomes costly
 * we can unify later by extracting a shared `FExportedReflectedProperty`
 * from both sites.
 */
struct BLUEPRINTEXPORTER_API FExportedReflectedProperty
{
	/** Property name */
	FString Name;

	/** Property CPP type string (e.g. "float", "FVector", "TSubclassOf<UEnvQueryContext>") */
	FString Type;

	/** String representation of the default value (from `ExportTextItem_Direct` on the CDO) */
	FString Value;

	/** UPROPERTY `Category` metadata if declared */
	FString Category;

	TSharedPtr<FJsonObject> ToJson() const;
	static FExportedReflectedProperty FromJson(const TSharedPtr<FJsonObject>& JsonObject);
};

/**
 * A single module declared by a plugin's .uplugin.
 * Mirrors `FModuleDescriptor` (Name / Type / LoadingPhase) with enum values
 * stringified for readability and stability.
 */
struct BLUEPRINTEXPORTER_API FExportedPluginModule
{
	/** Module name (matches the `.Build.cs` target name) */
	FString Name;

	/** `EHostType::Type` as string: "Runtime", "RuntimeNoCommandlet", "Editor", "EditorNoCommandlet",
	 *  "EditorAndProgram", "Program", "ServerOnly", "ClientOnly", "ClientOnlyNoCommandlet",
	 *  "CookedOnly", "UncookedOnly", "Developer", "DeveloperTool". */
	FString HostType;

	/** `ELoadingPhase::Type` as string: "Default", "PostDefault", "PreDefault", "EarliestPossible",
	 *  "PostConfigInit", "PostSplashScreen", "PreEarlyLoadingScreen", "PreLoadingScreen",
	 *  "PostEngineInit", "None". */
	FString LoadingPhase;

	TSharedPtr<FJsonObject> ToJson() const;
	static FExportedPluginModule FromJson(const TSharedPtr<FJsonObject>& JsonObject);
};

/**
 * A single plugin-reference dependency declared by a plugin's .uplugin `Plugins` array.
 */
struct BLUEPRINTEXPORTER_API FExportedPluginDependency
{
	/** Name of the depended-on plugin */
	FString Name;

	/** Whether the dependency is marked Enabled in the .uplugin entry */
	bool bEnabled = true;

	/** Whether the dependency is marked Optional (i.e. absence is tolerated) */
	bool bOptional = false;

	TSharedPtr<FJsonObject> ToJson() const;
	static FExportedPluginDependency FromJson(const TSharedPtr<FJsonObject>& JsonObject);
};

/**
 * A single native UClass registered by a plugin module. P1 populates this;
 * P0 leaves `NativeTypes[]` empty on every plugin and the JSON field is
 * written only when the array is non-empty.
 */
struct BLUEPRINTEXPORTER_API FExportedPluginNativeType
{
	/** Full class path, e.g. `/Script/CoverEQS.EnvQueryTest_TraceDistance` */
	FString ClassPath;

	/** Full parent class path, e.g. `/Script/AIModule.EnvQueryTest` */
	FString ParentClassPath;

	/** Name of the plugin module that declares this class (matches an `FExportedPluginModule::Name`) */
	FString ModuleName;

	/** Subsystem bucket for grouping (e.g. "EQS", "StateTree", "BehaviorTree", "Anim", "GAS",
	 *  "SmartObject", "Chooser", "Mass", "Other") */
	FString Subsystem;

	/** Declared UPROPERTYs on the class (excluding inherited); name-sorted */
	TArray<FExportedReflectedProperty> Properties;

	TSharedPtr<FJsonObject> ToJson() const;
	static FExportedPluginNativeType FromJson(const TSharedPtr<FJsonObject>& JsonObject);
};

/**
 * Top-level plugin record. One of these per project plugin. Also round-trips
 * as the root of each `PluginInventory/<PluginName>.meta.json` sidecar.
 */
struct BLUEPRINTEXPORTER_API FExportedPlugin
{
	/** Export metadata (reused from the Blueprint/StateTree pipelines) */
	FExportInfo ExportInfo;

	/** Plugin name (from `IPlugin::GetName()`) — matches the .uplugin filename stem */
	FString Name;

	/** `EPluginType` as string: "Engine", "Enterprise", "Project", "External", "Mod" */
	FString PluginType;

	/** Path to the plugin's root directory, relative to the project root when possible.
	 *  Absolute paths are forbidden by brief §8; if the plugin sits outside the project we
	 *  emit an engine-relative path instead. */
	FString BaseDir;

	/** Whether the plugin is currently enabled in the running editor */
	bool bEnabled = false;

	/** `FPluginDescriptor::Version` — integer */
	int32 Version = 0;

	/** `FPluginDescriptor::VersionName` — semantic version string */
	FString VersionName;

	/** `FPluginDescriptor::FriendlyName` */
	FString FriendlyName;

	/** `FPluginDescriptor::Description` */
	FString Description;

	/** `FPluginDescriptor::Category` */
	FString Category;

	/** `FPluginDescriptor::CreatedBy` */
	FString CreatedBy;

	/** `FPluginDescriptor::CreatedByURL` */
	FString CreatedByURL;

	/** `FPluginDescriptor::DocsURL` */
	FString DocsURL;

	/** `FPluginDescriptor::SupportURL` */
	FString SupportURL;

	/** `FPluginDescriptor::EngineVersion` — required engine version per the descriptor */
	FString EngineVersion;

	/** `FPluginDescriptor::bCanContainContent` */
	bool bCanContainContent = false;

	/** `FPluginDescriptor::bIsBetaVersion` */
	bool bIsBetaVersion = false;

	/** `FPluginDescriptor::bInstalled` */
	bool bInstalled = false;

	/** Modules declared by the plugin (sorted alpha by name at ToJson time) */
	TArray<FExportedPluginModule> Modules;

	/** Plugin-reference dependencies (sorted alpha by name at ToJson time) */
	TArray<FExportedPluginDependency> PluginDependencies;

	/** Native UClasses the plugin registers (empty in M7 P0; populated in P1) */
	TArray<FExportedPluginNativeType> NativeTypes;

	TSharedPtr<FJsonObject> ToJson() const;
	static FExportedPlugin FromJson(const TSharedPtr<FJsonObject>& JsonObject);

	/** Compute content hash over the sidecar content (timestamp blanked). */
	FString ComputeContentHash() const;
};
