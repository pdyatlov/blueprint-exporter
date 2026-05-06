// Copyright 10 Chambers. All Rights Reserved.

#include "Commandlets/ProjectPluginsCommandlet.h"
#include "BlueprintExporterModule.h"
#include "Util/AtomicFileWriter.h"
#include "Util/CommandletLog.h"
#include "InventoryEmit/PerAssetEmit.h"
#include "Schema/PluginExportTypes.h"

// `IPlugin` is declared alongside `IPluginManager` in IPluginManager.h —
// there is no separate `Interfaces/IPlugin.h` in UE 5.7.
#include "Interfaces/IPluginManager.h"
#include "ProjectDescriptor.h"
#include "ModuleDescriptor.h"
#include "PluginDescriptor.h"
#include "Misc/App.h"
#include "Misc/Paths.h"
#include "Misc/PackageName.h"
#include "HAL/FileManager.h"
#include "Internationalization/Regex.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "UObject/Class.h"
#include "UObject/Package.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/UObjectHash.h"
#include "UObject/UnrealType.h"

#define LOCTEXT_NAMESPACE "BlueprintExporter.ProjectPlugins"

namespace
{
	// Log line surface lives in `BlueprintExporter::Util::LogLine` (shared
	// helper in Util/CommandletLog.h). Kept out of this anon namespace so
	// unity (jumbo) builds don't collide with the identical-body copy that
	// ProjectManifestCommandlet.cpp used to carry.
	using BlueprintExporter::Util::LogLine;
	// Shared markdown-cell escaper. Hoisted to avoid unity-build ODR
	// collision with AggregateInventoryCommandlet.cpp's identical-body copy.
	using BlueprintExporter::InventoryEmit::EscTbl;

	const TCHAR* PluginTypeToString(EPluginType Type)
	{
		switch (Type)
		{
			case EPluginType::Engine:     return TEXT("Engine");
			case EPluginType::Enterprise: return TEXT("Enterprise");
			case EPluginType::Project:    return TEXT("Project");
			case EPluginType::External:   return TEXT("External");
			case EPluginType::Mod:        return TEXT("Mod");
			default:                      return TEXT("Unknown");
		}
	}

	// Normalise to absolute + forward slashes + trailing slash so prefix-stripping
	// is robust regardless of whether the input came in relative (e.g. UE's
	// usual `../../../game/Plugins/X`) or absolute form.
	FString NormaliseToAbsDir(const FString& Path)
	{
		FString Abs = FPaths::ConvertRelativePathToFull(Path);
		Abs.ReplaceInline(TEXT("\\"), TEXT("/"));
		if (!Abs.EndsWith(TEXT("/")))
		{
			Abs.AppendChar(TEXT('/'));
		}
		return Abs;
	}

	// Make a plugin base dir project-relative when possible. Brief §8: no
	// absolute paths in output. `Plugin->GetBaseDir()` + `FPaths::ProjectDir()`
	// often differ in form (one may be absolute, the other relative with
	// `..` chains), so both go through `ConvertRelativePathToFull` first.
	// Fallback for plugins outside the project root: engine-relative form
	// (same treatment); final fallback strips drive letter to avoid leaking
	// the workstation's disk layout.
	FString ProjectRelativePath(const FString& InPath)
	{
		if (InPath.IsEmpty())
		{
			return FString();
		}

		const FString AbsPath = NormaliseToAbsDir(InPath);
		const FString AbsProjectDir = NormaliseToAbsDir(FPaths::ProjectDir());

		if (AbsPath.StartsWith(AbsProjectDir, ESearchCase::IgnoreCase))
		{
			FString Rel = AbsPath.Mid(AbsProjectDir.Len());
			Rel.RemoveFromEnd(TEXT("/"));
			return Rel;
		}

		const FString AbsEngineDir = NormaliseToAbsDir(FPaths::EngineDir());
		if (AbsPath.StartsWith(AbsEngineDir, ESearchCase::IgnoreCase))
		{
			FString Rel = AbsPath.Mid(AbsEngineDir.Len());
			Rel.RemoveFromEnd(TEXT("/"));
			return TEXT("Engine/") + Rel;
		}

		// Outside both project and engine roots — strip drive letter so the
		// path stays relative-looking and stable across workstations.
		FString Fallback = AbsPath;
		if (Fallback.Len() >= 2 && Fallback[1] == TEXT(':'))
		{
			Fallback = Fallback.Mid(2);
		}
		Fallback.RemoveFromEnd(TEXT("/"));
		return Fallback;
	}

	// ---------------------------------------------------------------------
	// Native-type reflection walk (M7 P1).
	//
	// For each entry in the curated base-class allowlist, `GetDerivedClasses`
	// gives us every UClass currently loaded that derives from it. We then
	// filter by plugin ownership (candidate's UPackage FName must be
	// `/Script/<ModuleName>` for some module in this plugin's Modules[]) and
	// emit an `FExportedPluginNativeType` per match.
	//
	// Base classes are resolved at runtime via `StaticFindObject` — no
	// compile-time include / Build.cs dep needed. Missing modules (plugin not
	// loaded in this editor session) silently skip their bases.
	//
	// Struct-typed bases (e.g. FStateTreeTaskBase) are deferred to M7 P1.1
	// (trivial additive slice; needs a parallel `TObjectIterator<UScriptStruct>`
	// walk with `IsChildOf` check).
	// ---------------------------------------------------------------------

	struct FNativeBaseClass
	{
		const TCHAR* Path;      // e.g. "/Script/AIModule.EnvQueryTest"
		const TCHAR* Subsystem; // e.g. "EQS" — grouping label in the output
	};

	static const TArray<FNativeBaseClass>& GetNativeBaseClassAllowlist()
	{
		static const TArray<FNativeBaseClass> Allowlist = {
			// EQS — custom tests/generators/contexts (CoverEQS is the canary).
			{ TEXT("/Script/AIModule.EnvQueryTest"),                             TEXT("EQS") },
			{ TEXT("/Script/AIModule.EnvQueryGenerator"),                        TEXT("EQS") },
			{ TEXT("/Script/AIModule.EnvQueryContext_BlueprintBase"),            TEXT("EQS") },
			// StateTree — BP-extensible bases (F-prefixed native struct bases
			// are handled in a follow-up slice; see header comment above).
			{ TEXT("/Script/StateTreeModule.StateTreeTaskBlueprintBase"),        TEXT("StateTree") },
			{ TEXT("/Script/StateTreeModule.StateTreeConditionBlueprintBase"),   TEXT("StateTree") },
			{ TEXT("/Script/StateTreeModule.StateTreeEvaluatorBlueprintBase"),   TEXT("StateTree") },
			// BehaviorTree — native bases catch plugin-authored services /
			// decorators / tasks regardless of whether they subclass the
			// BlueprintBase intermediary.
			{ TEXT("/Script/AIModule.BTService"),                                TEXT("BehaviorTree") },
			{ TEXT("/Script/AIModule.BTDecorator"),                              TEXT("BehaviorTree") },
			{ TEXT("/Script/AIModule.BTTaskNode"),                               TEXT("BehaviorTree") },
			// Anim.
			{ TEXT("/Script/Engine.AnimNotify"),                                 TEXT("Anim") },
			{ TEXT("/Script/Engine.AnimNotifyState"),                            TEXT("Anim") },
			// GAS — runtime lookup so GameplayAbilities doesn't need a Build.cs
			// dep. Skipped silently if GAS isn't loaded.
			{ TEXT("/Script/GameplayAbilities.GameplayAbility"),                 TEXT("GAS") },
			{ TEXT("/Script/GameplayAbilities.GameplayEffect"),                  TEXT("GAS") },
			{ TEXT("/Script/GameplayAbilities.AttributeSet"),                    TEXT("GAS") },
			// SmartObject.
			{ TEXT("/Script/SmartObjectsModule.SmartObjectBehaviorDefinition"),  TEXT("SmartObject") },
			{ TEXT("/Script/SmartObjectsModule.SmartObjectSlotValidationFilter"),TEXT("SmartObject") },
			// Chooser.
			{ TEXT("/Script/Chooser.ChooserColumnBase"),                         TEXT("Chooser") },
			// Mass — MassProcessor is in MassEntity; DOW loads it transitively
			// via MassAI/MassCrowd/MassGameplay. Runtime skip if missing.
			{ TEXT("/Script/MassEntity.MassProcessor"),                          TEXT("Mass") },
		};
		return Allowlist;
	}

	// Walk `Class` (declared-only — inherited UPROPERTYs on the base are
	// redundant context) and emit one FExportedReflectedProperty per field.
	// Values come from the CDO; abstract / uninstantiatable classes get an
	// empty property list.
	TArray<FExportedReflectedProperty> BuildReflectedProperties(const UClass* Class)
	{
		TArray<FExportedReflectedProperty> Out;
		if (!Class)
		{
			return Out;
		}
		const UObject* CDO = Class->GetDefaultObject(/*bCreateIfNeeded=*/false);

		for (TFieldIterator<FProperty> It(Class, EFieldIteratorFlags::ExcludeSuper); It; ++It)
		{
			const FProperty* Property = *It;
			if (!Property)
			{
				continue;
			}

			FExportedReflectedProperty Prop;
			Prop.Name = Property->GetName();
			Prop.Type = Property->GetCPPType();
			if (Property->HasMetaData(TEXT("Category")))
			{
				Prop.Category = Property->GetMetaData(TEXT("Category"));
			}
			if (CDO)
			{
				FString ValueStr;
				const void* ValuePtr = Property->ContainerPtrToValuePtr<void>(CDO);
				Property->ExportTextItem_Direct(ValueStr, ValuePtr, nullptr, nullptr, PPF_None);
				Prop.Value = ValueStr;
			}
			Out.Add(MoveTemp(Prop));
		}
		return Out;
	}

	TArray<FExportedPluginNativeType> GatherNativeTypesForPlugin(const TSharedRef<IPlugin>& Plugin)
	{
		TArray<FExportedPluginNativeType> Out;

		// Build the set of /Script/<ModuleName> package FNames this plugin
		// contributes. Used to filter candidates to plugin-owned classes only.
		TSet<FName> PluginScriptPackages;
		for (const FModuleDescriptor& Module : Plugin->GetDescriptor().Modules)
		{
			const FString PackageName = FString::Printf(TEXT("/Script/%s"), *Module.Name.ToString());
			PluginScriptPackages.Add(FName(*PackageName));
		}
		if (PluginScriptPackages.Num() == 0)
		{
			return Out;
		}

		// Dedupe by ClassPath — a class could derive from multiple allowlist
		// bases (rare, but possible); keep the first-seen subsystem label for
		// determinism.
		TSet<FString> SeenClassPaths;

		for (const FNativeBaseClass& Base : GetNativeBaseClassAllowlist())
		{
			UClass* BaseClass = Cast<UClass>(
				StaticFindObject(UClass::StaticClass(), nullptr, Base.Path));
			if (!BaseClass)
			{
				// Base's module not loaded → plugin can't register against
				// it in this session. Silent skip — determinism depends on
				// which plugins are enabled, not on which we tried to probe.
				continue;
			}

			TArray<UClass*> Derived;
			GetDerivedClasses(BaseClass, Derived, /*bRecursive=*/true);

			for (UClass* Candidate : Derived)
			{
				if (!Candidate)
				{
					continue;
				}
				const UPackage* Package = Candidate->GetPackage();
				if (!Package || !PluginScriptPackages.Contains(Package->GetFName()))
				{
					continue;
				}

				const FString ClassPath = Candidate->GetPathName();
				if (SeenClassPaths.Contains(ClassPath))
				{
					continue;
				}
				SeenClassPaths.Add(ClassPath);

				FExportedPluginNativeType Type;
				Type.ClassPath = ClassPath;
				if (const UClass* Super = Candidate->GetSuperClass())
				{
					Type.ParentClassPath = Super->GetPathName();
				}
				// ModuleName = short form of the /Script/<Name> package.
				{
					const FString PkgName = Package->GetName();
					int32 LastSlash = INDEX_NONE;
					Type.ModuleName = PkgName.FindLastChar(TEXT('/'), LastSlash)
						? PkgName.Mid(LastSlash + 1)
						: PkgName;
				}
				Type.Subsystem = Base.Subsystem;
				Type.Properties = BuildReflectedProperties(Candidate);

				Out.Add(MoveTemp(Type));
			}
		}

		return Out;
	}

	FExportedPlugin BuildExportedPlugin(const TSharedRef<IPlugin>& Plugin)
	{
		const FPluginDescriptor& Desc = Plugin->GetDescriptor();

		FExportedPlugin Out;
		Out.ExportInfo.SchemaVersion = BLUEPRINT_EXPORT_SCHEMA_VERSION;
		Out.ExportInfo.EngineVersion = FEngineVersion::Current().ToString();
		Out.ExportInfo.PluginVersion = TEXT("1.28.6");
		// Brief §8 — timestamp is blanked for determinism (content hash is
		// computed with it already blanked).
		Out.ExportInfo.ExportTimestamp = TEXT("");

		Out.Name = Plugin->GetName();
		Out.PluginType = PluginTypeToString(Plugin->GetType());
		Out.BaseDir = ProjectRelativePath(Plugin->GetBaseDir());
		Out.bEnabled = Plugin->IsEnabled();

		Out.Version = Desc.Version;
		Out.VersionName = Desc.VersionName;
		Out.FriendlyName = Desc.FriendlyName;
		Out.Description = Desc.Description;
		Out.Category = Desc.Category;
		Out.CreatedBy = Desc.CreatedBy;
		Out.CreatedByURL = Desc.CreatedByURL;
		Out.DocsURL = Desc.DocsURL;
		Out.SupportURL = Desc.SupportURL;
		Out.EngineVersion = Desc.EngineVersion;
		Out.bCanContainContent = Desc.bCanContainContent;
		Out.bIsBetaVersion = Desc.bIsBetaVersion;
		Out.bInstalled = Desc.bInstalled;

		for (const FModuleDescriptor& Module : Desc.Modules)
		{
			FExportedPluginModule M;
			M.Name = Module.Name.ToString();
			M.HostType = EHostType::ToString(Module.Type);
			M.LoadingPhase = ELoadingPhase::ToString(Module.LoadingPhase);
			Out.Modules.Add(MoveTemp(M));
		}

		for (const FPluginReferenceDescriptor& Ref : Desc.Plugins)
		{
			FExportedPluginDependency D;
			D.Name = Ref.Name;
			D.bEnabled = Ref.bEnabled;
			D.bOptional = Ref.bOptional;
			Out.PluginDependencies.Add(MoveTemp(D));
		}

		// M7 P1 — reflection walk for native UClasses the plugin registers.
		// Only meaningful for enabled plugins (modules must be loaded for
		// GetDerivedClasses to see the types); silently empty otherwise.
		Out.NativeTypes = GatherNativeTypesForPlugin(Plugin);

		Out.ExportInfo.ContentHash = Out.ComputeContentHash();
		return Out;
	}

	FString RenderPluginMarkdown(const FExportedPlugin& P)
	{
		FString Md;
		Md.Reserve(8 * 1024);
		Md += FString::Printf(TEXT("# %s\n\n"), *P.Name);

		Md += TEXT("## Identity\n\n");
		Md += TEXT("| Field | Value |\n");
		Md += TEXT("|---|---|\n");
		Md += FString::Printf(TEXT("| Plugin name | `%s` |\n"), *EscTbl(P.Name));
		if (!P.FriendlyName.IsEmpty())
		{
			Md += FString::Printf(TEXT("| Friendly name | %s |\n"), *EscTbl(P.FriendlyName));
		}
		Md += FString::Printf(TEXT("| Plugin type | `%s` |\n"), *EscTbl(P.PluginType));
		Md += FString::Printf(TEXT("| Base dir | `%s` |\n"),
			P.BaseDir.IsEmpty() ? TEXT("—") : *EscTbl(P.BaseDir));
		Md += FString::Printf(TEXT("| Enabled | %s |\n"), P.bEnabled ? TEXT("yes") : TEXT("no"));
		Md += FString::Printf(TEXT("| Version | `%d` (`%s`) |\n"),
			P.Version, P.VersionName.IsEmpty() ? TEXT("—") : *EscTbl(P.VersionName));
		if (!P.Category.IsEmpty())
		{
			Md += FString::Printf(TEXT("| Category | `%s` |\n"), *EscTbl(P.Category));
		}
		if (!P.EngineVersion.IsEmpty())
		{
			Md += FString::Printf(TEXT("| Engine version | `%s` |\n"), *EscTbl(P.EngineVersion));
		}
		Md += FString::Printf(TEXT("| Can contain content | %s |\n"),
			P.bCanContainContent ? TEXT("yes") : TEXT("no"));
		if (P.bIsBetaVersion)
		{
			Md += TEXT("| Beta | yes |\n");
		}
		if (P.bInstalled)
		{
			Md += TEXT("| Installed | yes |\n");
		}
		Md += FString::Printf(TEXT("| Engine version (export) | `%s` |\n"),
			*EscTbl(P.ExportInfo.EngineVersion));
		Md += FString::Printf(TEXT("| Plugin version (tool) | `%s` |\n"),
			*EscTbl(P.ExportInfo.PluginVersion));
		Md += TEXT("\n");

		if (!P.Description.IsEmpty())
		{
			Md += TEXT("## Description\n\n");
			Md += P.Description + TEXT("\n\n");
		}

		if (!P.CreatedBy.IsEmpty() || !P.CreatedByURL.IsEmpty() ||
			!P.DocsURL.IsEmpty() || !P.SupportURL.IsEmpty())
		{
			Md += TEXT("## Authorship & Links\n\n");
			if (!P.CreatedBy.IsEmpty())
			{
				Md += FString::Printf(TEXT("- Created by: `%s`\n"), *EscTbl(P.CreatedBy));
			}
			if (!P.CreatedByURL.IsEmpty())
			{
				Md += FString::Printf(TEXT("- Author URL: `%s`\n"), *EscTbl(P.CreatedByURL));
			}
			if (!P.DocsURL.IsEmpty())
			{
				Md += FString::Printf(TEXT("- Docs: `%s`\n"), *EscTbl(P.DocsURL));
			}
			if (!P.SupportURL.IsEmpty())
			{
				Md += FString::Printf(TEXT("- Support: `%s`\n"), *EscTbl(P.SupportURL));
			}
			Md += TEXT("\n");
		}

		// Modules
		Md += FString::Printf(TEXT("## Modules (%d)\n\n"), P.Modules.Num());
		if (P.Modules.Num() == 0)
		{
			Md += TEXT("_None._\n\n");
		}
		else
		{
			TArray<FExportedPluginModule> Sorted = P.Modules;
			Sorted.Sort([](const FExportedPluginModule& A, const FExportedPluginModule& B)
			{
				return A.Name.Compare(B.Name, ESearchCase::IgnoreCase) < 0;
			});
			Md += TEXT("| Name | Host type | Loading phase |\n");
			Md += TEXT("|---|---|---|\n");
			for (const FExportedPluginModule& M : Sorted)
			{
				Md += FString::Printf(TEXT("| `%s` | `%s` | `%s` |\n"),
					*EscTbl(M.Name),
					*EscTbl(M.HostType),
					*EscTbl(M.LoadingPhase));
			}
			Md += TEXT("\n");
		}

		// Plugin dependencies
		Md += FString::Printf(TEXT("## Plugin dependencies (%d)\n\n"), P.PluginDependencies.Num());
		if (P.PluginDependencies.Num() == 0)
		{
			Md += TEXT("_None._\n\n");
		}
		else
		{
			TArray<FExportedPluginDependency> Sorted = P.PluginDependencies;
			Sorted.Sort([](const FExportedPluginDependency& A, const FExportedPluginDependency& B)
			{
				return A.Name.Compare(B.Name, ESearchCase::IgnoreCase) < 0;
			});
			Md += TEXT("| Plugin | Enabled | Optional |\n");
			Md += TEXT("|---|---|---|\n");
			for (const FExportedPluginDependency& D : Sorted)
			{
				Md += FString::Printf(TEXT("| `%s` | %s | %s |\n"),
					*EscTbl(D.Name),
					D.bEnabled  ? TEXT("yes") : TEXT("no"),
					D.bOptional ? TEXT("yes") : TEXT("no"));
			}
			Md += TEXT("\n");
		}

		// Native types — M7 P1 populates via GetDerivedClasses() reflection
		// walk over the curated base-class allowlist. If the plugin is
		// disabled (modules not loaded) the array is empty and we say so.
		Md += FString::Printf(TEXT("## Registered native types (%d)\n\n"),
			P.NativeTypes.Num());
		if (P.NativeTypes.Num() == 0)
		{
			if (P.bEnabled)
			{
				Md += TEXT("_None — this plugin's modules register no UClass ")
				      TEXT("subclasses of any allowlist base (EQS / StateTree / ")
				      TEXT("BT / Anim / GAS / SmartObject / Chooser / Mass)._\n\n");
			}
			else
			{
				Md += TEXT("_Plugin is disabled in the uproject; its modules ")
				      TEXT("are not loaded so no native types are visible to ")
				      TEXT("`GetDerivedClasses`. Enable the plugin and re-run ")
				      TEXT("to populate._\n\n");
			}
		}
		else
		{
			TArray<FExportedPluginNativeType> Sorted = P.NativeTypes;
			Sorted.Sort([](const FExportedPluginNativeType& A, const FExportedPluginNativeType& B)
			{
				return A.ClassPath.Compare(B.ClassPath, ESearchCase::IgnoreCase) < 0;
			});

			// Summary table — high-level view so readers can scan without
			// wading through every per-class property block below.
			Md += TEXT("| Class | Parent | Module | Subsystem | Props |\n");
			Md += TEXT("|---|---|---|---|---:|\n");
			for (const FExportedPluginNativeType& T : Sorted)
			{
				Md += FString::Printf(TEXT("| `%s` | `%s` | `%s` | `%s` | %d |\n"),
					*EscTbl(T.ClassPath),
					*EscTbl(T.ParentClassPath),
					*EscTbl(T.ModuleName),
					*EscTbl(T.Subsystem),
					T.Properties.Num());
			}
			Md += TEXT("\n");

			// Per-class property breakdown.
			for (const FExportedPluginNativeType& T : Sorted)
			{
				Md += FString::Printf(TEXT("### `%s` — `%s` [%s]\n\n"),
					*EscTbl(T.ClassPath),
					*EscTbl(T.ModuleName),
					*EscTbl(T.Subsystem));
				Md += FString::Printf(TEXT("- Parent: `%s`\n"), *EscTbl(T.ParentClassPath));
				Md += FString::Printf(TEXT("- Declared properties: %d\n\n"),
					T.Properties.Num());

				if (T.Properties.Num() == 0)
				{
					Md += TEXT("_No UPROPERTYs declared directly on this class._\n\n");
					continue;
				}

				TArray<FExportedReflectedProperty> SortedProps = T.Properties;
				SortedProps.Sort([](const FExportedReflectedProperty& A, const FExportedReflectedProperty& B)
				{
					return A.Name.Compare(B.Name, ESearchCase::IgnoreCase) < 0;
				});

				Md += TEXT("| Name | Type | Default | Category |\n");
				Md += TEXT("|---|---|---|---|\n");
				for (const FExportedReflectedProperty& Prop : SortedProps)
				{
					const FString Default = Prop.Value.IsEmpty()
						? FString(TEXT("—"))
						: FString::Printf(TEXT("`%s`"), *EscTbl(Prop.Value));
					const FString Category = Prop.Category.IsEmpty()
						? FString(TEXT("—"))
						: FString::Printf(TEXT("`%s`"), *EscTbl(Prop.Category));
					Md += FString::Printf(TEXT("| `%s` | `%s` | %s | %s |\n"),
						*EscTbl(Prop.Name),
						*EscTbl(Prop.Type),
						*Default,
						*Category);
				}
				Md += TEXT("\n");
			}
		}

		return Md;
	}

	FString RenderMetaJson(const FExportedPlugin& P)
	{
		const TSharedPtr<FJsonObject> Json = P.ToJson();
		FString Out;
		const TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> Writer =
			TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&Out);
		FJsonSerializer::Serialize(Json.ToSharedRef(), Writer);
		return Out;
	}

	FString RenderRollupMarkdown(const TArray<FExportedPlugin>& Plugins)
	{
		FString Md;
		Md.Reserve(16 * 1024);
		Md += TEXT("# PLUGINS\n\n");
		Md += FString::Printf(
			TEXT("Rollup of project plugins produced by `-run=ProjectPlugins`. ")
			TEXT("Each row links to a per-plugin sidecar under `PluginInventory/`. ")
			TEXT("Engine plugins are deliberately out of scope.\n\n"));

		Md += FString::Printf(TEXT("## Summary\n\n- Total plugins: **%d**\n"),
			Plugins.Num());
		int32 EnabledCount = 0;
		int32 ContentCount = 0;
		int32 NativeTypesTotal = 0;
		int32 PluginsWithNativeTypes = 0;
		for (const FExportedPlugin& P : Plugins)
		{
			if (P.bEnabled)                                  { ++EnabledCount; }
			if (P.bCanContainContent)                         { ++ContentCount; }
			NativeTypesTotal += P.NativeTypes.Num();
			if (P.NativeTypes.Num() > 0)                      { ++PluginsWithNativeTypes; }
		}
		Md += FString::Printf(TEXT("- Enabled: **%d**\n"), EnabledCount);
		Md += FString::Printf(TEXT("- Declares `bCanContainContent`: **%d**\n"),
			ContentCount);
		Md += FString::Printf(TEXT("- Registers native types (EQS/ST/BT/Anim/GAS/SmartObj/Chooser/Mass bases): **%d plugin(s), %d class(es) total**\n\n"),
			PluginsWithNativeTypes, NativeTypesTotal);

		Md += TEXT("## Plugins\n\n");
		Md += TEXT("| Plugin | Version | Category | Enabled | Modules | Deps | Native | Content | Base dir |\n");
		Md += TEXT("|---|---|---|---|---:|---:|---:|---|---|\n");
		TArray<FExportedPlugin> Sorted = Plugins;
		Sorted.Sort([](const FExportedPlugin& A, const FExportedPlugin& B)
		{
			return A.Name.Compare(B.Name, ESearchCase::IgnoreCase) < 0;
		});
		for (const FExportedPlugin& P : Sorted)
		{
			const FString Link = FString::Printf(TEXT("[`%s`](PluginInventory/%s.md)"),
				*EscTbl(P.Name), *P.Name);
			Md += FString::Printf(
				TEXT("| %s | `%s` | %s | %s | %d | %d | %d | %s | `%s` |\n"),
				*Link,
				P.VersionName.IsEmpty() ? TEXT("—") : *EscTbl(P.VersionName),
				P.Category.IsEmpty() ? TEXT("—") : *EscTbl(P.Category),
				P.bEnabled ? TEXT("yes") : TEXT("no"),
				P.Modules.Num(),
				P.PluginDependencies.Num(),
				P.NativeTypes.Num(),
				P.bCanContainContent ? TEXT("yes") : TEXT("no"),
				P.BaseDir.IsEmpty() ? TEXT("—") : *EscTbl(P.BaseDir));
		}
		Md += TEXT("\n");

		return Md;
	}

	bool RegexMatches(const FRegexPattern& Pattern, const FString& Target)
	{
		FRegexMatcher Matcher(Pattern, Target);
		return Matcher.FindNext();
	}
}

UProjectPluginsCommandlet::UProjectPluginsCommandlet()
{
	IsClient = false;
	IsEditor = true;
	IsServer = false;
	LogToConsole = true;
}

int32 UProjectPluginsCommandlet::Main(const FString& Params)
{
	LogLine(TEXT("INFO"), TEXT("Project Plugins Commandlet starting"));

	FString OutDir;
	if (!FParse::Value(*Params, TEXT("OutDir="), OutDir))
	{
		LogLine(TEXT("ERROR"),
			TEXT("Missing -OutDir=<dir>. `PLUGINS.md` + `PluginInventory/<name>.{md,meta.json}` are written under this directory."),
			/*bIsError=*/true);
		return 2;
	}
	OutDir.TrimQuotesInline();

	FString IncludeRegexStr;
	FString ExcludeRegexStr;
	FParse::Value(*Params, TEXT("Include="), IncludeRegexStr);
	FParse::Value(*Params, TEXT("Exclude="), ExcludeRegexStr);
	const bool bHasInclude = !IncludeRegexStr.IsEmpty();
	const bool bHasExclude = !ExcludeRegexStr.IsEmpty();
	FRegexPattern IncludePattern(IncludeRegexStr);
	FRegexPattern ExcludePattern(ExcludeRegexStr);

	LogLine(TEXT("INFO"), FString::Printf(TEXT("OutDir=%s Include=%s Exclude=%s"),
		*OutDir,
		IncludeRegexStr.IsEmpty() ? TEXT("(none)") : *IncludeRegexStr,
		ExcludeRegexStr.IsEmpty() ? TEXT("(none)") : *ExcludeRegexStr));

	const FString PluginInventoryDir = FPaths::Combine(OutDir, TEXT("PluginInventory"));
	if (!IFileManager::Get().DirectoryExists(*PluginInventoryDir))
	{
		IFileManager::Get().MakeDirectory(*PluginInventoryDir, /*Tree=*/true);
	}

	IPluginManager& PluginManager = IPluginManager::Get();
	const TArray<TSharedRef<IPlugin>> AllPlugins = PluginManager.GetDiscoveredPlugins();

	TArray<FExportedPlugin> Exported;
	Exported.Reserve(AllPlugins.Num());

	int32 ProjectPluginCount = 0;
	int32 FilteredOutCount = 0;

	for (const TSharedRef<IPlugin>& Plugin : AllPlugins)
	{
		// M7 P0 scope: project plugins only. Engine/Enterprise/Mod plugins are
		// intentionally skipped (Epic documents engine plugins; mods are
		// user-content and out of scope for a game-project static-analysis tool).
		if (Plugin->GetType() != EPluginType::Project)
		{
			continue;
		}
		++ProjectPluginCount;

		const FString Name = Plugin->GetName();
		if (bHasInclude && !RegexMatches(IncludePattern, Name))
		{
			++FilteredOutCount;
			continue;
		}
		if (bHasExclude && RegexMatches(ExcludePattern, Name))
		{
			++FilteredOutCount;
			continue;
		}

		FExportedPlugin P = BuildExportedPlugin(Plugin);
		Exported.Add(MoveTemp(P));
	}

	// Determinism: sort by name before writing anything.
	Exported.Sort([](const FExportedPlugin& A, const FExportedPlugin& B)
	{
		return A.Name.Compare(B.Name, ESearchCase::IgnoreCase) < 0;
	});

	LogLine(TEXT("INFO"), FString::Printf(
		TEXT("Discovered %d total plugin(s), %d project-typed, %d filtered out, %d to write"),
		AllPlugins.Num(), ProjectPluginCount, FilteredOutCount, Exported.Num()));

	// Per-plugin sidecars.
	for (const FExportedPlugin& P : Exported)
	{
		const FString MdPath   = FPaths::Combine(PluginInventoryDir, P.Name + TEXT(".md"));
		const FString JsonPath = FPaths::Combine(PluginInventoryDir, P.Name + TEXT(".meta.json"));

		const FString MdContent   = RenderPluginMarkdown(P);
		const FString JsonContent = RenderMetaJson(P);

		if (!BlueprintExporterUtil::SaveStringAtomic(MdContent, MdPath))
		{
			LogLine(TEXT("ERROR"),
				FString::Printf(TEXT("Failed to write %s"), *MdPath), /*bIsError=*/true);
			return 2;
		}
		if (!BlueprintExporterUtil::SaveStringAtomic(JsonContent, JsonPath))
		{
			LogLine(TEXT("ERROR"),
				FString::Printf(TEXT("Failed to write %s"), *JsonPath), /*bIsError=*/true);
			return 2;
		}
	}

	// Top-level rollup.
	const FString RollupMd = RenderRollupMarkdown(Exported);
	const FString RollupPath = FPaths::Combine(OutDir, TEXT("PLUGINS.md"));
	if (!BlueprintExporterUtil::SaveStringAtomic(RollupMd, RollupPath))
	{
		LogLine(TEXT("ERROR"),
			FString::Printf(TEXT("Failed to write %s"), *RollupPath), /*bIsError=*/true);
		return 2;
	}

	LogLine(TEXT("RESULT"), FString::Printf(
		TEXT("Plugins=%d (project-typed=%d, filtered-out=%d) Rollup=%s SidecarDir=%s"),
		Exported.Num(), ProjectPluginCount, FilteredOutCount,
		*RollupPath, *PluginInventoryDir));
	LogLine(TEXT("STATUS"), TEXT("SUCCESS"));
	return 0;
}

#undef LOCTEXT_NAMESPACE

