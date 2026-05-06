// Copyright 10 Chambers. All Rights Reserved.

#include "Commandlets/ProjectInventoryCommandlet.h"
#include "BlueprintExporterModule.h"
#include "InventoryEmit/PerAssetEmit.h"
#include "Util/AtomicFileWriter.h"
#include "Util/CommandletLog.h"
#include "TextExport/DeepDumpRenderer.h"
#include "TextExport/SmartObjectDefinitionDeepRenderer.h"
#include "TextExport/BehaviorTreeDeepRenderer.h"
#include "TextExport/DataTableDeepRenderer.h"
#include "TextExport/ChooserTableDeepRenderer.h"
#include "TextExport/EnvQueryDeepRenderer.h"
#include "TextExport/CustomizableObjectInstanceDeepRenderer.h"
#include "TextExport/CustomizableObjectDeepRenderer.h"
#include "TextExport/CustomizableObjectMacroLibraryDeepRenderer.h"
#include "Schema/BlueprintExportTypes.h"
#include "Serialization/BlueprintSerializer.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "AssetRegistry/ARFilter.h"
#include "AssetRegistry/AssetData.h"
#include "Engine/Blueprint.h"
// UUserDefinedStruct moved to CoreUObject/StructUtils in UE 5.5. The old
// `Engine/UserDefinedStruct.h` header is now a deprecation stub that only
// forwards when `UE_ENABLE_INCLUDE_ORDER_DEPRECATED_IN_5_5` is defined.
#include "StructUtils/UserDefinedStruct.h"
#include "Engine/UserDefinedEnum.h"
#include "UObject/UnrealType.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformTime.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "UObject/GarbageCollection.h"
#include "UObject/Package.h"

// AIModule — for UBehaviorTree / UBlackboardData introspection (M3.1) and
// UEnvQuery introspection (M3.2).
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BTService.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryOption.h"
#include "EnvironmentQuery/EnvQueryGenerator.h"
#include "EnvironmentQuery/EnvQueryTest.h"

// Engine — for UDataTable schema introspection (M3.2).
#include "Engine/DataTable.h"

// StateTree — optional; WITH_STATETREE_SUPPORT is defined by Build.cs based on
// whether StateTreeModule is present in the host engine.
#if WITH_STATETREE_SUPPORT
#include "Schema/StateTreeExportTypes.h"
#include "Serialization/StateTreeSerializer.h"
#include "StateTree.h"
#endif

// Chooser — optional; WITH_CHOOSER_SUPPORT is defined by Build.cs based on
// whether the Chooser plugin module is present. `Chooser.h` is in the plugin's
// `Internal/` folder but the plugin's Build.cs exposes it via PublicIncludePaths.
#if WITH_CHOOSER_SUPPORT
#include "Chooser.h"
#include "IChooserColumn.h"
#include "IHasContext.h"
#endif

// PoseSearch — optional; WITH_POSESEARCH_SUPPORT is defined by Build.cs based
// on whether the PoseSearch plugin module is present. All headers live in the
// plugin's Public include path under `PoseSearch/`.
#if WITH_POSESEARCH_SUPPORT
#include "PoseSearch/PoseSearchDatabase.h"
#include "PoseSearch/PoseSearchSchema.h"
#include "PoseSearch/PoseSearchFeatureChannel.h"
#include "PoseSearch/PoseSearchNormalizationSet.h"
#endif

// SmartObjects — optional; WITH_SMARTOBJECTS_SUPPORT is defined by Build.cs
// based on whether the SmartObjects plugin is present.
#if WITH_SMARTOBJECTS_SUPPORT
#include "SmartObjectDefinition.h"
#include "SmartObjectTypes.h"
#include "GameplayTagContainer.h"
#include "WorldConditionQuery.h"
#endif

// Mutable — no compile-time link dep as of M29.6.4. The three renderers
// (UCOI / UCO / COML) dispatch by class-name match and read via reflection,
// so we include their public entry-point headers only; no MuCO/* includes
// and no `CustomizableObject` dep in Build.cs.

namespace
{
	// M27.3.1 — import the shared per-asset emission surface so unqualified
	// calls to EscTbl / StripScriptPrefix / WriteJsonToFile /
	// ComputeCoveragePercent / BuildNonUBPCoverageJson / BuildAssetOutputBase
	// / RenderBlueprintMarkdown / WriteMetaJson / EmitStateTreeAsset resolve
	// into BlueprintExporter::InventoryEmit. Single source of truth; any
	// divergence between the commandlet sweep and the bridge re-export is
	// impossible by construction.
	using namespace BlueprintExporter::InventoryEmit;

	// UBlueprint-family class name set now lives in
	// `InventoryEmit::GetUBlueprintFamilyClassNames()` (hoisted to avoid
	// unity-build ODR collision with DeepDumpCommandlet.cpp's identical
	// anon-namespace copy). The `using namespace ...::InventoryEmit` above
	// keeps unqualified call sites in this file compiling unchanged.

	// Non-UBP logic-bearing classes (per brief §3). The first M3 slice doesn't
	// introspect these; it just records them as "skipped, scope of later slice"
	// so the next session has a concrete surface to tackle.
	const TSet<FName>& GetNonUBPLogicBearingClassNames()
	{
		static const TSet<FName> Classes = {
			FName(TEXT("BehaviorTree")),
			FName(TEXT("StateTree")),
			FName(TEXT("EnvQuery")),
			FName(TEXT("SmartObjectDefinition")),
			FName(TEXT("ChooserTable")),
			FName(TEXT("PoseSearchDatabase")),
			FName(TEXT("UserDefinedStruct")),
			FName(TEXT("UserDefinedEnum")),
			FName(TEXT("DataTable")),
			// M29.6.4 — CO classes enter the sweep unconditionally; the
			// renderers are engine-agnostic so the entries never need a
			// WITH_MUTABLE_SUPPORT gate. Projects without Mutable content
			// simply have zero assets matching these names.
			FName(TEXT("CustomizableObjectInstance")),
			FName(TEXT("CustomizableObject")),
			FName(TEXT("CustomizableObjectMacroLibrary")),
		};
		return Classes;
	}

	// For classes that hit `EmitGenericNonUBPAsset`, declare the specialized
	// section(s) a future typed handler is expected to document. Prevents
	// silent-100% coverage when the generic schema dump says nothing about
	// the asset's authored content (DOW calibration finding 2026-04-18).
	//
	// One item per class — HEALTH_REPORT renders one row per gap, so keeping
	// this to a single descriptive marker avoids drowning the report. When
	// the typed handler lands (M3.3+ P1), it moves this marker to the
	// `documented` list and coverage returns to 100%.
	TArray<FString> GetGenericFallbackApplicableSections(const FString& ClassShortName)
	{
		// All named logic-bearing classes have typed handlers as of M3.3 P1c:
		//   - ChooserTable → M3.3 P1a
		//   - PoseSearchDatabase → M3.3 P1b
		//   - SmartObjectDefinition → M3.3 P1c
		// If a new unhandled class starts hitting the generic fallback in the
		// future, add an entry here so HEALTH_REPORT flags it honestly instead
		// of scoring silent 100%.
		(void)ClassShortName;
		return {};
	}

	using BlueprintExporter::Util::LogLine;

	// BuildAssetOutputBase, EscTbl, StripScriptPrefix, FormatPinType, FormatAccess,
	// FormatBlueprintType, RenderComponentTree, RenderIdentity, RenderInheritance,
	// RenderVariables, FormatParamList, RenderFunctionSection, RenderComponents,
	// RenderCDOProperties, ShortClassName, RenderStateMachine*, RenderWidget*,
	// RenderGraphs, RenderReferences, RenderMetadata, RenderBlueprintMarkdown,
	// ComputeSpecializedApplicable/Documented, ComputeCoveragePercent,
	// BuildCoverageJson, WriteJsonToFile, WriteMetaJson, BuildNonUBPCoverageJson,
	// CountStateTreeStates, FormatEditorNode, RenderStateTreeState,
	// CollectStateTreeStructTypes*, EmitStateTreeAsset — ALL HOISTED to
	// BlueprintExporter::InventoryEmit via the `using namespace` above.
	// Single source of truth between the commandlet sweep and the M27 bridge
	// re-export (AssetReExporter). See Private/InventoryEmit/PerAssetEmit.{h,cpp}.


	struct FFailedAsset
	{
		FString PackageName;
		FString Reason;
	};

	void WriteFailureLog(
		const FString& OutDir,
		const TCHAR* Basename,
		const TCHAR* Title,
		const TArray<FFailedAsset>& Entries)
	{
		if (Entries.Num() == 0)
		{
			return;
		}
		TArray<FFailedAsset> Sorted = Entries;
		Sorted.Sort([](const FFailedAsset& A, const FFailedAsset& B)
		{
			return A.PackageName.Compare(B.PackageName, ESearchCase::IgnoreCase) < 0;
		});

		FString Md;
		Md.Reserve(4 * 1024);
		Md += FString::Printf(TEXT("# %s\n\n"), Title);
		Md += FString::Printf(TEXT("Total: %d\n\n"), Sorted.Num());
		Md += TEXT("| Package | Reason |\n");
		Md += TEXT("|---|---|\n");
		for (const FFailedAsset& E : Sorted)
		{
			Md += FString::Printf(TEXT("| `%s` | %s |\n"),
				*EscTbl(E.PackageName), *EscTbl(E.Reason));
		}
		Md += TEXT("\n");

		const FString Path = FPaths::Combine(OutDir, Basename);
		BlueprintExporterUtil::SaveStringAtomic(Md, Path);
	}

	// ====================================================================
	// Non-UBP asset handlers (M3.1). Each handler:
	//   - Builds a Markdown summary (`.md`)
	//   - Builds a `.meta.json` with `assetType`, a type-specific payload,
	//     `dependencies` (asset-registry-derived), and `coverage`
	//   - Writes both via `SaveStringAtomic` (order: `.md` first, `.meta.json`
	//     second — `.meta.json` is the "done" sentinel for `-Resume`)
	// Failure semantics: return false + fill OutError; commandlet aggregates
	// into FAILED/PARTIAL logs the same way UBP handling does.
	// ====================================================================

	// Gather asset-registry dependencies for a given object path and
	// render them as FExportedDependency-shaped JSON so DEPENDENCY_GRAPH.md
	// (in AggregateInventory) can key them uniformly across UBP + non-UBP.
	TArray<TSharedPtr<FJsonValue>> GatherDependenciesJson(const FAssetData& AssetData)
	{
		TArray<TSharedPtr<FJsonValue>> Out;
		FAssetRegistryModule& AssetRegistryModule =
			FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
		IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

		TArray<FName> HardDeps;
		TArray<FName> SoftDeps;
		AssetRegistry.GetDependencies(AssetData.PackageName, HardDeps,
			UE::AssetRegistry::EDependencyCategory::Package,
			UE::AssetRegistry::EDependencyQuery::Hard);
		AssetRegistry.GetDependencies(AssetData.PackageName, SoftDeps,
			UE::AssetRegistry::EDependencyCategory::Package,
			UE::AssetRegistry::EDependencyQuery::Soft);

		auto EmitDeps = [&Out](const TArray<FName>& Deps, const TCHAR* Kind)
		{
			for (const FName& D : Deps)
			{
				TSharedPtr<FJsonObject> O = MakeShared<FJsonObject>();
				O->SetStringField(TEXT("assetPath"), D.ToString());
				O->SetStringField(TEXT("assetName"), FPaths::GetCleanFilename(D.ToString()));
				O->SetStringField(TEXT("dependencyType"), Kind);
				O->SetBoolField(TEXT("isBlueprint"), false);
				O->SetBoolField(TEXT("isNativeClass"), false);
				O->SetStringField(TEXT("description"), TEXT(""));
				Out.Add(MakeShared<FJsonValueObject>(O));
			}
		};
		// Deterministic order: sort each group alpha before emitting.
		TArray<FName> HardSorted = HardDeps;
		TArray<FName> SoftSorted = SoftDeps;
		HardSorted.Sort([](const FName& A, const FName& B){ return A.LexicalLess(B); });
		SoftSorted.Sort([](const FName& A, const FName& B){ return A.LexicalLess(B); });
		EmitDeps(HardSorted, TEXT("Hard"));
		EmitDeps(SoftSorted, TEXT("Soft"));
		return Out;
	}

	// -------- UserDefinedStruct --------
	bool EmitUserDefinedStructAsset(
		const FAssetData& AssetData,
		UUserDefinedStruct* UDS,
		const FString& MdPath,
		const FString& MetaPath,
		int32& OutOverallPct,
		FString& OutError)
	{
		if (!UDS)
		{
			OutError = TEXT("null UUserDefinedStruct");
			return false;
		}
		struct FFieldRow { FString Name; FString Type; FString Category; FString ToolTip; };
		TArray<FFieldRow> Fields;
		// Default iterator: own fields + inherited; UUserDefinedStruct's super is
		// UScriptStruct which has no user-visible fields so the default is fine.
		for (TFieldIterator<FProperty> It(UDS); It; ++It)
		{
			FProperty* Prop = *It;
			FFieldRow R;
			// Prop->GetName() on UUserDefinedStruct properties returns the
			// GUID-suffixed internal name (e.g., "MyVar_2_ABCDEF"). Authored
			// name extraction needs StructureEditorUtils from UnrealEd; for the
			// first slice we live with the internal name. Aggregate consumers
			// can strip the suffix if they need the authored form.
			R.Name = Prop->GetName();
			R.Type = Prop->GetCPPType();
			R.Category = Prop->GetMetaData(TEXT("Category"));
			R.ToolTip = Prop->GetToolTipText().ToString();
			Fields.Add(MoveTemp(R));
		}

		// Markdown
		FString Md;
		Md.Reserve(4 * 1024);
		Md += FString::Printf(TEXT("# %s\n\n"), *UDS->GetName());
		Md += TEXT("## Identity\n\n");
		Md += TEXT("| Field | Value |\n|---|---|\n");
		Md += FString::Printf(TEXT("| Asset path | `%s` |\n"), *EscTbl(UDS->GetPathName()));
		Md += FString::Printf(TEXT("| Asset name | `%s` |\n"), *EscTbl(UDS->GetName()));
		Md += TEXT("| Asset type | `UserDefinedStruct` |\n");
		Md += FString::Printf(TEXT("| Engine version | `%s` |\n"),
			*EscTbl(FEngineVersion::Current().ToString()));
		Md += TEXT("\n");

		Md += FString::Printf(TEXT("## Fields (%d)\n\n"), Fields.Num());
		if (Fields.Num() == 0)
		{
			Md += TEXT("_No fields._\n\n");
		}
		else
		{
			// Preserve declaration order per brief §8.
			Md += TEXT("| Name | Type | Category | ToolTip |\n|---|---|---|---|\n");
			for (const FFieldRow& F : Fields)
			{
				Md += FString::Printf(TEXT("| `%s` | `%s` | %s | %s |\n"),
					*EscTbl(F.Name), *EscTbl(F.Type),
					F.Category.IsEmpty() ? TEXT("—") : *FString::Printf(TEXT("`%s`"), *EscTbl(F.Category)),
					F.ToolTip.IsEmpty() ? TEXT("—") : *EscTbl(F.ToolTip));
			}
			Md += TEXT("\n");
		}

		if (!BlueprintExporterUtil::SaveStringAtomic(Md, MdPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MdPath);
			return false;
		}

		// .meta.json
		TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
		Root->SetStringField(TEXT("$schema"), TEXT("blueprint-exporter-v1"));
		Root->SetStringField(TEXT("assetType"), TEXT("UserDefinedStruct"));
		Root->SetStringField(TEXT("assetPath"), UDS->GetPathName());
		Root->SetStringField(TEXT("assetName"), UDS->GetName());

		TArray<TSharedPtr<FJsonValue>> FieldsJson;
		for (const FFieldRow& F : Fields)
		{
			TSharedPtr<FJsonObject> FO = MakeShared<FJsonObject>();
			FO->SetStringField(TEXT("name"), F.Name);
			FO->SetStringField(TEXT("type"), F.Type);
			FO->SetStringField(TEXT("category"), F.Category);
			FO->SetStringField(TEXT("toolTip"), F.ToolTip);
			FieldsJson.Add(MakeShared<FJsonValueObject>(FO));
		}
		Root->SetArrayField(TEXT("fields"), FieldsJson);
		Root->SetArrayField(TEXT("dependencies"), GatherDependenciesJson(AssetData));

		Root->SetObjectField(TEXT("coverage"),
			BuildNonUBPCoverageJson(TEXT("fields"), Fields.Num(), Fields.Num(),
				{}, {}, OutOverallPct));

		if (!WriteJsonToFile(Root, MetaPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MetaPath);
			return false;
		}
		return true;
	}

	// -------- UserDefinedEnum --------
	bool EmitUserDefinedEnumAsset(
		const FAssetData& AssetData,
		UUserDefinedEnum* UDE,
		const FString& MdPath,
		const FString& MetaPath,
		int32& OutOverallPct,
		FString& OutError)
	{
		if (!UDE)
		{
			OutError = TEXT("null UUserDefinedEnum");
			return false;
		}
		struct FEnumRow { FString Name; FString Display; int64 Value; };
		TArray<FEnumRow> Rows;
		// NumEnums() includes the trailing "_MAX" sentinel; skip it.
		const int32 Num = UDE->NumEnums();
		for (int32 i = 0; i < Num; ++i)
		{
			FName N = UDE->GetNameByIndex(i);
			if (UDE->ContainsExistingMax() && i == Num - 1) continue;
			FEnumRow R;
			R.Name = N.ToString();
			R.Display = UDE->GetDisplayNameTextByIndex(i).ToString();
			R.Value = UDE->GetValueByIndex(i);
			Rows.Add(MoveTemp(R));
		}

		FString Md;
		Md.Reserve(2 * 1024);
		Md += FString::Printf(TEXT("# %s\n\n"), *UDE->GetName());
		Md += TEXT("## Identity\n\n");
		Md += TEXT("| Field | Value |\n|---|---|\n");
		Md += FString::Printf(TEXT("| Asset path | `%s` |\n"), *EscTbl(UDE->GetPathName()));
		Md += FString::Printf(TEXT("| Asset name | `%s` |\n"), *EscTbl(UDE->GetName()));
		Md += TEXT("| Asset type | `UserDefinedEnum` |\n");
		Md += FString::Printf(TEXT("| Engine version | `%s` |\n"),
			*EscTbl(FEngineVersion::Current().ToString()));
		Md += TEXT("\n");

		Md += FString::Printf(TEXT("## Values (%d)\n\n"), Rows.Num());
		if (Rows.Num() == 0)
		{
			Md += TEXT("_No values._\n\n");
		}
		else
		{
			// Preserve declaration order per brief §8.
			Md += TEXT("| Name | Display Name | Value |\n|---|---|---:|\n");
			for (const FEnumRow& R : Rows)
			{
				Md += FString::Printf(TEXT("| `%s` | %s | %lld |\n"),
					*EscTbl(R.Name),
					R.Display.IsEmpty() ? TEXT("—") : *EscTbl(R.Display),
					R.Value);
			}
			Md += TEXT("\n");
		}

		if (!BlueprintExporterUtil::SaveStringAtomic(Md, MdPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MdPath);
			return false;
		}

		TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
		Root->SetStringField(TEXT("$schema"), TEXT("blueprint-exporter-v1"));
		Root->SetStringField(TEXT("assetType"), TEXT("UserDefinedEnum"));
		Root->SetStringField(TEXT("assetPath"), UDE->GetPathName());
		Root->SetStringField(TEXT("assetName"), UDE->GetName());

		TArray<TSharedPtr<FJsonValue>> ValuesJson;
		for (const FEnumRow& R : Rows)
		{
			TSharedPtr<FJsonObject> VO = MakeShared<FJsonObject>();
			VO->SetStringField(TEXT("name"), R.Name);
			VO->SetStringField(TEXT("displayName"), R.Display);
			VO->SetNumberField(TEXT("value"), static_cast<double>(R.Value));
			ValuesJson.Add(MakeShared<FJsonValueObject>(VO));
		}
		Root->SetArrayField(TEXT("values"), ValuesJson);
		Root->SetArrayField(TEXT("dependencies"), GatherDependenciesJson(AssetData));

		Root->SetObjectField(TEXT("coverage"),
			BuildNonUBPCoverageJson(TEXT("values"), Rows.Num(), Rows.Num(),
				{}, {}, OutOverallPct));

		if (!WriteJsonToFile(Root, MetaPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MetaPath);
			return false;
		}
		return true;
	}

	// -------- BehaviorTree --------
	// Per-node listing (one row per composite/task) with attached decorators
	// and services. Services live on the composite itself (UBTCompositeNode::
	// Services). Decorators live on the parent composite's `FBTCompositeChild`
	// slot — so a task's decorators come from its parent slot, and a sub-
	// composite has decorators-from-slot PLUS its own services.
	struct FBTNodeInfo
	{
		int32 Depth = 0;
		FString Class;
		FString Name;
		TArray<TPair<FString, FString>> Decorators;   // (class, name)
		TArray<TPair<FString, FString>> Services;     // (class, name)
	};

	FString BTNodeLabel(const UBTNode* Node)
	{
		if (!Node) return FString(TEXT("?"));
		return Node->NodeName.IsEmpty() ? Node->GetName() : Node->NodeName;
	}

	void CollectBTServices(const UBTCompositeNode* Composite, FBTNodeInfo& Row)
	{
		if (!Composite) return;
		for (const TObjectPtr<UBTService>& Svc : Composite->Services)
		{
			if (const UBTService* S = Svc.Get())
			{
				Row.Services.Add(MakeTuple(S->GetClass()->GetName(), BTNodeLabel(S)));
			}
		}
	}

	void CollectBTDecoratorsForSlot(const FBTCompositeChild& Slot, FBTNodeInfo& Row)
	{
		for (const TObjectPtr<UBTDecorator>& Dec : Slot.Decorators)
		{
			if (const UBTDecorator* D = Dec.Get())
			{
				Row.Decorators.Add(MakeTuple(D->GetClass()->GetName(), BTNodeLabel(D)));
			}
		}
	}

	// Fills OutRows with one row per composite + task. `SlotDecorators` is
	// optional — the root composite has no parent slot, so it's nullptr there.
	void CollectBTNodes(
		const UBTCompositeNode* Composite,
		int32 Depth,
		const FBTCompositeChild* SlotDecorators,
		TArray<FBTNodeInfo>& OutRows)
	{
		if (!Composite) return;

		FBTNodeInfo Row;
		Row.Depth = Depth;
		Row.Class = Composite->GetClass()->GetName();
		Row.Name = BTNodeLabel(Composite);
		if (SlotDecorators)
		{
			CollectBTDecoratorsForSlot(*SlotDecorators, Row);
		}
		CollectBTServices(Composite, Row);
		OutRows.Add(MoveTemp(Row));

		for (const FBTCompositeChild& Child : Composite->Children)
		{
			if (Child.ChildComposite)
			{
				CollectBTNodes(Child.ChildComposite, Depth + 1, &Child, OutRows);
			}
			else if (Child.ChildTask)
			{
				FBTNodeInfo Leaf;
				Leaf.Depth = Depth + 1;
				Leaf.Class = Child.ChildTask->GetClass()->GetName();
				Leaf.Name = BTNodeLabel(Child.ChildTask);
				CollectBTDecoratorsForSlot(Child, Leaf);
				OutRows.Add(MoveTemp(Leaf));
			}
		}
	}

	bool EmitBehaviorTreeAsset(
		const FAssetData& AssetData,
		UBehaviorTree* BT,
		const FString& MdPath,
		const FString& MetaPath,
		int32& OutOverallPct,
		FString& OutError)
	{
		if (!BT)
		{
			OutError = TEXT("null UBehaviorTree");
			return false;
		}

		TArray<FBTNodeInfo> Nodes;
		if (UBTCompositeNode* Root = BT->RootNode)
		{
			CollectBTNodes(Root, 0, /*SlotDecorators=*/nullptr, Nodes);
		}

		struct FBBKey { FString Name; FString KeyClass; };
		TArray<FBBKey> BBKeys;
		FString BlackboardPath;
		if (UBlackboardData* BB = BT->BlackboardAsset)
		{
			BlackboardPath = BB->GetPathName();
			for (const FBlackboardEntry& Key : BB->Keys)
			{
				FBBKey K;
				K.Name = Key.EntryName.ToString();
				K.KeyClass = Key.KeyType ? Key.KeyType->GetClass()->GetName() : FString(TEXT("?"));
				BBKeys.Add(MoveTemp(K));
			}
		}

		FString Md;
		Md.Reserve(4 * 1024);
		Md += FString::Printf(TEXT("# %s\n\n"), *BT->GetName());
		Md += TEXT("## Identity\n\n");
		Md += TEXT("| Field | Value |\n|---|---|\n");
		Md += FString::Printf(TEXT("| Asset path | `%s` |\n"), *EscTbl(BT->GetPathName()));
		Md += FString::Printf(TEXT("| Asset name | `%s` |\n"), *EscTbl(BT->GetName()));
		Md += TEXT("| Asset type | `BehaviorTree` |\n");
		Md += FString::Printf(TEXT("| Blackboard | %s |\n"),
			BlackboardPath.IsEmpty() ? TEXT("_none_") : *FString::Printf(TEXT("`%s`"), *EscTbl(BlackboardPath)));
		Md += FString::Printf(TEXT("| Engine version | `%s` |\n"),
			*EscTbl(FEngineVersion::Current().ToString()));
		Md += TEXT("\n");

		int32 TotalDecorators = 0;
		int32 TotalServices = 0;
		for (const FBTNodeInfo& N : Nodes)
		{
			TotalDecorators += N.Decorators.Num();
			TotalServices += N.Services.Num();
		}

		Md += FString::Printf(TEXT("## Tree (%d nodes, %d decorators, %d services)\n\n"),
			Nodes.Num(), TotalDecorators, TotalServices);
		if (Nodes.Num() == 0)
		{
			Md += TEXT("_Empty tree (no root node)._\n\n");
		}
		else
		{
			for (const FBTNodeInfo& N : Nodes)
			{
				const FString Indent = FString::ChrN(N.Depth * 2, TEXT(' '));
				Md += FString::Printf(TEXT("%s- `%s` — `%s`\n"), *Indent, *N.Name, *N.Class);
				for (const TPair<FString, FString>& D : N.Decorators)
				{
					Md += FString::Printf(TEXT("%s  - _decorator_ `%s` — `%s`\n"),
						*Indent, *D.Value, *D.Key);
				}
				for (const TPair<FString, FString>& S : N.Services)
				{
					Md += FString::Printf(TEXT("%s  - _service_ `%s` — `%s`\n"),
						*Indent, *S.Value, *S.Key);
				}
			}
			Md += TEXT("\n");
		}

		Md += FString::Printf(TEXT("## Blackboard Keys (%d)\n\n"), BBKeys.Num());
		if (BBKeys.Num() == 0)
		{
			Md += TEXT("_None or no blackboard assigned._\n\n");
		}
		else
		{
			// Keys keep their declaration order on the Blackboard asset —
			// changing order would shift blackboard indices at runtime.
			Md += TEXT("| Name | Key type |\n|---|---|\n");
			for (const FBBKey& K : BBKeys)
			{
				Md += FString::Printf(TEXT("| `%s` | `%s` |\n"), *EscTbl(K.Name), *EscTbl(K.KeyClass));
			}
			Md += TEXT("\n");
		}

		if (!BlueprintExporterUtil::SaveStringAtomic(Md, MdPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MdPath);
			return false;
		}

		TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
		Root->SetStringField(TEXT("$schema"), TEXT("blueprint-exporter-v1"));
		Root->SetStringField(TEXT("assetType"), TEXT("BehaviorTree"));
		Root->SetStringField(TEXT("assetPath"), BT->GetPathName());
		Root->SetStringField(TEXT("assetName"), BT->GetName());
		Root->SetStringField(TEXT("blackboardPath"), BlackboardPath);

		TArray<TSharedPtr<FJsonValue>> NodesJson;
		for (const FBTNodeInfo& N : Nodes)
		{
			TSharedPtr<FJsonObject> NO = MakeShared<FJsonObject>();
			NO->SetNumberField(TEXT("depth"), N.Depth);
			NO->SetStringField(TEXT("class"), N.Class);
			NO->SetStringField(TEXT("name"), N.Name);

			auto EmitAuxArray = [](const TArray<TPair<FString, FString>>& In)
			{
				TArray<TSharedPtr<FJsonValue>> Out;
				for (const TPair<FString, FString>& P : In)
				{
					TSharedPtr<FJsonObject> O = MakeShared<FJsonObject>();
					O->SetStringField(TEXT("class"), P.Key);
					O->SetStringField(TEXT("name"), P.Value);
					Out.Add(MakeShared<FJsonValueObject>(O));
				}
				return Out;
			};
			NO->SetArrayField(TEXT("decorators"), EmitAuxArray(N.Decorators));
			NO->SetArrayField(TEXT("services"), EmitAuxArray(N.Services));
			NodesJson.Add(MakeShared<FJsonValueObject>(NO));
		}
		Root->SetArrayField(TEXT("nodes"), NodesJson);

		TArray<TSharedPtr<FJsonValue>> KeysJson;
		for (const FBBKey& K : BBKeys)
		{
			TSharedPtr<FJsonObject> KO = MakeShared<FJsonObject>();
			KO->SetStringField(TEXT("name"), K.Name);
			KO->SetStringField(TEXT("keyClass"), K.KeyClass);
			KeysJson.Add(MakeShared<FJsonValueObject>(KO));
		}
		Root->SetArrayField(TEXT("blackboardKeys"), KeysJson);
		Root->SetArrayField(TEXT("dependencies"), GatherDependenciesJson(AssetData));

		// M3.2 documents per-node decorators + services, so both specialized
		// sections are now populated. They remain `applicable` (so non-empty
		// trees keep a consistent coverage surface across runs) and get moved
		// into `documented` whenever the tree contains at least one node —
		// `BuildNonUBPCoverageJson` suppresses both lists for empty trees so
		// BT_BugHunt (no root node) doesn't score 0%.
		Root->SetObjectField(TEXT("coverage"),
			BuildNonUBPCoverageJson(TEXT("nodes"), Nodes.Num(), Nodes.Num(),
				{ TEXT("BT.Decorators"), TEXT("BT.Services") },
				{ TEXT("BT.Decorators"), TEXT("BT.Services") }, OutOverallPct));

		if (!WriteJsonToFile(Root, MetaPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MetaPath);
			return false;
		}
		return true;
	}

	// -------- DataTable --------
	// Schema only (brief §4): column list derived from `RowStruct`'s fields, row
	// count + row names. Row *contents* are intentionally not written — they
	// can be arbitrary blobs and aren't logic-bearing. If DOW ends up needing
	// row-level detail for any particular DT, `DeepDumpCommandlet` is the
	// right tool for that.
	bool EmitDataTableAsset(
		const FAssetData& AssetData,
		UDataTable* DT,
		const FString& MdPath,
		const FString& MetaPath,
		int32& OutOverallPct,
		FString& OutError)
	{
		if (!DT)
		{
			OutError = TEXT("null UDataTable");
			return false;
		}

		const UScriptStruct* RowStruct = DT->GetRowStruct();
		const FString RowStructPath = RowStruct ? RowStruct->GetPathName() : FString();
		const FString RowStructName = RowStruct ? RowStruct->GetName() : FString();

		struct FColRow { FString Name; FString Type; FString Category; FString ToolTip; };
		TArray<FColRow> Columns;
		if (RowStruct)
		{
			for (TFieldIterator<FProperty> It(RowStruct); It; ++It)
			{
				FProperty* P = *It;
				FColRow C;
				C.Name = P->GetName();
				C.Type = P->GetCPPType();
				C.Category = P->GetMetaData(TEXT("Category"));
				C.ToolTip = P->GetToolTipText().ToString();
				Columns.Add(MoveTemp(C));
			}
		}

		const TArray<FName> RowNames = DT->GetRowNames();

		FString Md;
		Md.Reserve(4 * 1024);
		Md += FString::Printf(TEXT("# %s\n\n"), *DT->GetName());
		Md += TEXT("## Identity\n\n");
		Md += TEXT("| Field | Value |\n|---|---|\n");
		Md += FString::Printf(TEXT("| Asset path | `%s` |\n"), *EscTbl(DT->GetPathName()));
		Md += FString::Printf(TEXT("| Asset name | `%s` |\n"), *EscTbl(DT->GetName()));
		Md += TEXT("| Asset type | `DataTable` |\n");
		Md += FString::Printf(TEXT("| Row struct | %s |\n"),
			RowStructPath.IsEmpty() ? TEXT("_none_") : *FString::Printf(TEXT("`%s`"), *EscTbl(RowStructPath)));
		Md += FString::Printf(TEXT("| Row count | **%d** |\n"), RowNames.Num());
		Md += FString::Printf(TEXT("| Engine version | `%s` |\n"),
			*EscTbl(FEngineVersion::Current().ToString()));
		Md += TEXT("\n");

		Md += FString::Printf(TEXT("## Columns (%d)\n\n"), Columns.Num());
		if (Columns.Num() == 0)
		{
			Md += TEXT("_No columns — row struct missing or has no properties._\n\n");
		}
		else
		{
			Md += TEXT("| Name | Type | Category | ToolTip |\n|---|---|---|---|\n");
			for (const FColRow& C : Columns)
			{
				Md += FString::Printf(TEXT("| `%s` | `%s` | %s | %s |\n"),
					*EscTbl(C.Name), *EscTbl(C.Type),
					C.Category.IsEmpty() ? TEXT("—") : *FString::Printf(TEXT("`%s`"), *EscTbl(C.Category)),
					C.ToolTip.IsEmpty() ? TEXT("—") : *EscTbl(C.ToolTip));
			}
			Md += TEXT("\n");
		}

		// Row names only — no row contents (brief §4 "schema only").
		Md += FString::Printf(TEXT("## Row Names (%d)\n\n"), RowNames.Num());
		if (RowNames.Num() == 0)
		{
			Md += TEXT("_Empty table._\n\n");
		}
		else
		{
			TArray<FName> Sorted = RowNames;
			Sorted.Sort([](const FName& A, const FName& B) { return A.LexicalLess(B); });
			for (const FName& N : Sorted)
			{
				Md += FString::Printf(TEXT("- `%s`\n"), *EscTbl(N.ToString()));
			}
			Md += TEXT("\n");
		}

		if (!BlueprintExporterUtil::SaveStringAtomic(Md, MdPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MdPath);
			return false;
		}

		TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
		Root->SetStringField(TEXT("$schema"), TEXT("blueprint-exporter-v1"));
		Root->SetStringField(TEXT("assetType"), TEXT("DataTable"));
		Root->SetStringField(TEXT("assetPath"), DT->GetPathName());
		Root->SetStringField(TEXT("assetName"), DT->GetName());
		Root->SetStringField(TEXT("rowStructPath"), RowStructPath);
		Root->SetStringField(TEXT("rowStructName"), RowStructName);
		Root->SetNumberField(TEXT("rowCount"), RowNames.Num());

		TArray<TSharedPtr<FJsonValue>> ColsJson;
		for (const FColRow& C : Columns)
		{
			TSharedPtr<FJsonObject> CO = MakeShared<FJsonObject>();
			CO->SetStringField(TEXT("name"), C.Name);
			CO->SetStringField(TEXT("type"), C.Type);
			CO->SetStringField(TEXT("category"), C.Category);
			CO->SetStringField(TEXT("toolTip"), C.ToolTip);
			ColsJson.Add(MakeShared<FJsonValueObject>(CO));
		}
		Root->SetArrayField(TEXT("columns"), ColsJson);

		// Deterministic row-name list (sorted alpha) — names only, no contents.
		TArray<FName> SortedNames = RowNames;
		SortedNames.Sort([](const FName& A, const FName& B) { return A.LexicalLess(B); });
		TArray<TSharedPtr<FJsonValue>> NamesJson;
		for (const FName& N : SortedNames)
		{
			NamesJson.Add(MakeShared<FJsonValueString>(N.ToString()));
		}
		Root->SetArrayField(TEXT("rowNames"), NamesJson);

		Root->SetArrayField(TEXT("dependencies"), GatherDependenciesJson(AssetData));

		Root->SetObjectField(TEXT("coverage"),
			BuildNonUBPCoverageJson(TEXT("columns"), Columns.Num(), Columns.Num(),
				{}, {}, OutOverallPct));

		if (!WriteJsonToFile(Root, MetaPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MetaPath);
			return false;
		}
		return true;
	}

	// -------- EnvQuery --------
	// Top-level option list: each FEnvQueryOption has a Generator + Tests.
	// Rendered as a flat listing; per-test parameter detail is `DeepDump` work.
	bool EmitEnvQueryAsset(
		const FAssetData& AssetData,
		UEnvQuery* EQS,
		const FString& MdPath,
		const FString& MetaPath,
		int32& OutOverallPct,
		FString& OutError)
	{
		if (!EQS)
		{
			OutError = TEXT("null UEnvQuery");
			return false;
		}

		struct FOptRow
		{
			FString OptionName;
			FString GeneratorClass;
			TArray<FString> TestClasses;   // short class name per test
		};
		TArray<FOptRow> Options;
		int32 TotalTests = 0;
		for (const UEnvQueryOption* Opt : EQS->GetOptions())
		{
			if (!Opt) continue;
			FOptRow R;
			if (const UEnvQueryGenerator* Gen = Opt->Generator)
			{
				R.OptionName = Gen->OptionName.IsEmpty() ? Gen->GetName() : Gen->OptionName;
				R.GeneratorClass = Gen->GetClass()->GetName();
			}
			else
			{
				R.OptionName = TEXT("(no generator)");
				R.GeneratorClass = TEXT("");
			}
			for (const TObjectPtr<UEnvQueryTest>& TestPtr : Opt->Tests)
			{
				if (const UEnvQueryTest* Test = TestPtr.Get())
				{
					R.TestClasses.Add(Test->GetClass()->GetName());
					++TotalTests;
				}
			}
			Options.Add(MoveTemp(R));
		}

		FString Md;
		Md.Reserve(4 * 1024);
		Md += FString::Printf(TEXT("# %s\n\n"), *EQS->GetName());
		Md += TEXT("## Identity\n\n");
		Md += TEXT("| Field | Value |\n|---|---|\n");
		Md += FString::Printf(TEXT("| Asset path | `%s` |\n"), *EscTbl(EQS->GetPathName()));
		Md += FString::Printf(TEXT("| Asset name | `%s` |\n"), *EscTbl(EQS->GetName()));
		Md += TEXT("| Asset type | `EnvQuery` |\n");
		Md += FString::Printf(TEXT("| Engine version | `%s` |\n"),
			*EscTbl(FEngineVersion::Current().ToString()));
		Md += TEXT("\n");

		Md += FString::Printf(TEXT("## Options (%d, %d tests total)\n\n"), Options.Num(), TotalTests);
		if (Options.Num() == 0)
		{
			Md += TEXT("_No options._\n\n");
		}
		else
		{
			// Query options have authored order that determines run order —
			// preserve it rather than sorting (brief §8: authored order for
			// semantically ordered collections).
			for (const FOptRow& O : Options)
			{
				Md += FString::Printf(TEXT("- `%s` — generator `%s`, %d test(s)\n"),
					*O.OptionName, *O.GeneratorClass, O.TestClasses.Num());
				for (const FString& T : O.TestClasses)
				{
					Md += FString::Printf(TEXT("  - test `%s`\n"), *T);
				}
			}
			Md += TEXT("\n");
		}

		if (!BlueprintExporterUtil::SaveStringAtomic(Md, MdPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MdPath);
			return false;
		}

		TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
		Root->SetStringField(TEXT("$schema"), TEXT("blueprint-exporter-v1"));
		Root->SetStringField(TEXT("assetType"), TEXT("EnvQuery"));
		Root->SetStringField(TEXT("assetPath"), EQS->GetPathName());
		Root->SetStringField(TEXT("assetName"), EQS->GetName());

		TArray<TSharedPtr<FJsonValue>> OptsJson;
		for (const FOptRow& O : Options)
		{
			TSharedPtr<FJsonObject> OO = MakeShared<FJsonObject>();
			OO->SetStringField(TEXT("optionName"), O.OptionName);
			OO->SetStringField(TEXT("generatorClass"), O.GeneratorClass);
			TArray<TSharedPtr<FJsonValue>> TestsJson;
			for (const FString& T : O.TestClasses)
			{
				TestsJson.Add(MakeShared<FJsonValueString>(T));
			}
			OO->SetArrayField(TEXT("tests"), TestsJson);
			OptsJson.Add(MakeShared<FJsonValueObject>(OO));
		}
		Root->SetArrayField(TEXT("options"), OptsJson);
		Root->SetArrayField(TEXT("dependencies"), GatherDependenciesJson(AssetData));

		Root->SetObjectField(TEXT("coverage"),
			BuildNonUBPCoverageJson(TEXT("options"), Options.Num(), Options.Num(),
				{}, {}, OutOverallPct));

		if (!WriteJsonToFile(Root, MetaPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MetaPath);
			return false;
		}
		return true;
	}

#if WITH_CHOOSER_SUPPORT
	// -------- ChooserTable --------
	// Structural dump of a UChooserTable: columns (polymorphic FChooserColumnBase
	// derivatives), rows (FInstancedStruct-per-row — each typed by the concrete
	// ObjectChooser variant like FEvaluateChooser / FNestedChooser / FAssetChooser),
	// fallback row, context data. Per-column filter VALUES (the per-row cell
	// contents in a BoolColumn / FloatRangeColumn / etc.) are NOT walked in this
	// slice — they need per-column-type knowledge and are a separate slice.
	bool EmitChooserTableAsset(
		const FAssetData& AssetData,
		UChooserTable* Chooser,
		const FString& MdPath,
		const FString& MetaPath,
		int32& OutOverallPct,
		FString& OutError)
	{
		if (!Chooser)
		{
			OutError = TEXT("null UChooserTable");
			return false;
		}

		auto InstStructTypePath = [](const FInstancedStruct& S) -> FString
		{
			const UScriptStruct* T = S.GetScriptStruct();
			return T ? T->GetPathName() : FString();
		};
		auto InstStructTypeName = [](const FInstancedStruct& S) -> FString
		{
			const UScriptStruct* T = S.GetScriptStruct();
			return T ? T->GetName() : FString();
		};

		// Parent class + identity
		UClass* Cls = Chooser->GetClass();
		UClass* ParentCls = Cls ? Cls->GetSuperClass() : nullptr;
		const FString ParentName = ParentCls ? ParentCls->GetName() : FString();
		const FString ParentPath = ParentCls ? ParentCls->GetPathName() : FString();

		// Result type enum -> string (mirrors EObjectChooserResultType metadata).
		const TCHAR* ResultTypeStr = TEXT("ObjectResult");
		switch (Chooser->ResultType)
		{
		case EObjectChooserResultType::ObjectResult:    ResultTypeStr = TEXT("ObjectResult"); break;
		case EObjectChooserResultType::ClassResult:     ResultTypeStr = TEXT("ClassResult"); break;
		case EObjectChooserResultType::NoPrimaryResult: ResultTypeStr = TEXT("NoPrimaryResult"); break;
		}

		const FString OutputObjectTypePath = Chooser->OutputObjectType ? Chooser->OutputObjectType->GetPathName() : FString();

		// Nested detection: RootChooser == this (or null) means we ARE the root.
		const UChooserTable* RootChooser = Chooser->GetRootChooser();
		const bool bIsRoot = (RootChooser == Chooser) || (RootChooser == nullptr);
		const FString RootChooserPath = bIsRoot ? FString() : (RootChooser ? RootChooser->GetPathName() : FString());

		struct FColumnRow
		{
			int32 Index = 0;
			FString TypeName;
			FString TypePath;
			bool bHasFilter = false;
			bool bHasOutput = false;
			bool bHasCost = false;
			bool bDisabled = false;
			FString InputTypePath;
		};
		TArray<FColumnRow> Columns;
		Columns.Reserve(Chooser->ColumnsStructs.Num());
		for (int32 i = 0; i < Chooser->ColumnsStructs.Num(); ++i)
		{
			const FInstancedStruct& ColIS = Chooser->ColumnsStructs[i];
			FColumnRow Row;
			Row.Index = i;
			Row.TypeName = InstStructTypeName(ColIS);
			Row.TypePath = InstStructTypePath(ColIS);
			if (const FChooserColumnBase* ColBase = ColIS.GetPtr<FChooserColumnBase>())
			{
				Row.bHasFilter = ColBase->HasFilters();
				Row.bHasOutput = ColBase->HasOutputs();
				Row.bHasCost   = ColBase->HasCosts();
#if WITH_EDITORONLY_DATA
				Row.bDisabled = ColBase->bDisabled;
#endif
#if WITH_EDITOR
				// GetInputType() returns the currently-bound InputValue's struct
				// type (a FChooserParameterBase descendant). Can be null if no
				// input is wired. Non-const method — need a const_cast because
				// we hold a const pointer.
				if (const UScriptStruct* InputType = const_cast<FChooserColumnBase*>(ColBase)->GetInputType())
				{
					Row.InputTypePath = InputType->GetPathName();
				}
#endif
			}
			Columns.Add(MoveTemp(Row));
		}
		// Order preserved — columns are semantically load-bearing (they're
		// evaluated left-to-right as filters).

		// Rows: each FInstancedStruct in ResultsStructs (editor) / CookedResults
		// (cooked) carries the concrete output type (e.g., FEvaluateChooser
		// pointing at another UChooserTable, FAssetChooser pointing at a UObject,
		// FNestedChooser pointing at an embedded UChooserTable).
		struct FRowEntry
		{
			int32 Index = 0;
			FString TypeName;
			FString TypePath;
			bool bDisabled = false;
		};
		TArray<FRowEntry> Rows;
#if WITH_EDITORONLY_DATA
		const TArray<FInstancedStruct>& RowStructs = Chooser->ResultsStructs;
#else
		const TArray<FInstancedStruct>& RowStructs = Chooser->CookedResults;
#endif
		Rows.Reserve(RowStructs.Num());
		for (int32 i = 0; i < RowStructs.Num(); ++i)
		{
			FRowEntry R;
			R.Index = i;
			R.TypeName = InstStructTypeName(RowStructs[i]);
			R.TypePath = InstStructTypePath(RowStructs[i]);
#if WITH_EDITORONLY_DATA
			R.bDisabled = Chooser->DisabledRows.IsValidIndex(i) && Chooser->DisabledRows[i];
#endif
			Rows.Add(MoveTemp(R));
		}

		// Fallback: single FInstancedStruct, may be unset (no StructType).
		const bool bFallbackSet = (Chooser->FallbackResult.GetScriptStruct() != nullptr);
		const FString FallbackTypePath = InstStructTypePath(Chooser->FallbackResult);
		const FString FallbackTypeName = InstStructTypeName(Chooser->FallbackResult);

		// Context data: parameter objects/structs that columns read/write.
		TArray<FString> ContextTypePaths;
		ContextTypePaths.Reserve(Chooser->ContextData.Num());
		for (const FInstancedStruct& Ctx : Chooser->ContextData)
		{
			ContextTypePaths.Add(InstStructTypePath(Ctx));
		}

		// Nested chooser paths (editor-only). Sort alpha for determinism.
		TArray<FString> NestedChooserPaths;
#if WITH_EDITORONLY_DATA
		NestedChooserPaths.Reserve(Chooser->NestedChoosers.Num());
		for (const TObjectPtr<UChooserTable>& NC : Chooser->NestedChoosers)
		{
			if (NC)
			{
				NestedChooserPaths.Add(NC->GetPathName());
			}
		}
		NestedChooserPaths.Sort([](const FString& A, const FString& B)
		{
			return A.Compare(B, ESearchCase::IgnoreCase) < 0;
		});
		const int32 NestedObjectCount = Chooser->NestedObjects.Num();
#else
		const int32 NestedObjectCount = 0;
#endif

		// ---- Markdown ----
		FString Md;
		Md.Reserve(4 * 1024);
		Md += FString::Printf(TEXT("# %s\n\n"), *Chooser->GetName());
		Md += TEXT("## Identity\n\n");
		Md += TEXT("| Field | Value |\n|---|---|\n");
		Md += FString::Printf(TEXT("| Asset path | `%s` |\n"), *EscTbl(Chooser->GetPathName()));
		Md += FString::Printf(TEXT("| Asset name | `%s` |\n"), *EscTbl(Chooser->GetName()));
		Md += TEXT("| Asset type | `ChooserTable` |\n");
		Md += FString::Printf(TEXT("| Parent class | %s |\n"),
			ParentPath.IsEmpty() ? TEXT("_none_") : *FString::Printf(TEXT("`%s`"), *EscTbl(ParentPath)));
		Md += FString::Printf(TEXT("| Result type | `%s` |\n"), ResultTypeStr);
		Md += FString::Printf(TEXT("| Output class | %s |\n"),
			OutputObjectTypePath.IsEmpty() ? TEXT("_none_") : *FString::Printf(TEXT("`%s`"), *EscTbl(OutputObjectTypePath)));
		Md += FString::Printf(TEXT("| Role | %s |\n"),
			bIsRoot ? TEXT("Root chooser") : *FString::Printf(TEXT("Nested under `%s`"), *EscTbl(RootChooserPath)));
		Md += FString::Printf(TEXT("| Columns | **%d** |\n"), Columns.Num());
		Md += FString::Printf(TEXT("| Rows | **%d** |\n"), Rows.Num());
		Md += FString::Printf(TEXT("| Nested choosers | %d |\n"), NestedChooserPaths.Num());
		Md += FString::Printf(TEXT("| Engine version | `%s` |\n"),
			*EscTbl(FEngineVersion::Current().ToString()));
		Md += TEXT("\n");

		Md += FString::Printf(TEXT("## Context Data (%d)\n\n"), ContextTypePaths.Num());
		if (ContextTypePaths.Num() == 0)
		{
			Md += TEXT("_No context parameters declared._\n\n");
		}
		else
		{
			Md += TEXT("| # | Struct type |\n|---:|---|\n");
			for (int32 i = 0; i < ContextTypePaths.Num(); ++i)
			{
				Md += FString::Printf(TEXT("| %d | %s |\n"), i,
					ContextTypePaths[i].IsEmpty() ? TEXT("_unset_") : *FString::Printf(TEXT("`%s`"), *EscTbl(ContextTypePaths[i])));
			}
			Md += TEXT("\n");
		}

		Md += FString::Printf(TEXT("## Columns (%d)\n\n"), Columns.Num());
		if (Columns.Num() == 0)
		{
			Md += TEXT("_No columns._\n\n");
		}
		else
		{
			Md += TEXT("| # | Struct type | Filter | Output | Cost | Input type | Disabled |\n|---:|---|:---:|:---:|:---:|---|:---:|\n");
			for (const FColumnRow& C : Columns)
			{
				Md += FString::Printf(TEXT("| %d | `%s` | %s | %s | %s | %s | %s |\n"),
					C.Index,
					*EscTbl(C.TypePath.IsEmpty() ? C.TypeName : C.TypePath),
					C.bHasFilter ? TEXT("yes") : TEXT("—"),
					C.bHasOutput ? TEXT("yes") : TEXT("—"),
					C.bHasCost ? TEXT("yes") : TEXT("—"),
					C.InputTypePath.IsEmpty() ? TEXT("—") : *FString::Printf(TEXT("`%s`"), *EscTbl(C.InputTypePath)),
					C.bDisabled ? TEXT("yes") : TEXT("—"));
			}
			Md += TEXT("\n");
		}

		Md += FString::Printf(TEXT("## Rows (%d)\n\n"), Rows.Num());
		Md += TEXT("_Each row's struct type names the concrete `FObjectChooserBase` variant (e.g., `FEvaluateChooser` for a chooser-ref, `FAssetChooser` for a direct asset). Per-cell filter values are not rendered in this slice._\n\n");
		if (Rows.Num() == 0)
		{
			Md += TEXT("_No rows._\n\n");
		}
		else
		{
			Md += TEXT("| # | Output struct | Disabled |\n|---:|---|:---:|\n");
			for (const FRowEntry& R : Rows)
			{
				Md += FString::Printf(TEXT("| %d | %s | %s |\n"),
					R.Index,
					R.TypePath.IsEmpty() ? TEXT("_unset_") : *FString::Printf(TEXT("`%s`"), *EscTbl(R.TypePath)),
					R.bDisabled ? TEXT("yes") : TEXT("—"));
			}
			Md += TEXT("\n");
		}

		Md += TEXT("## Fallback\n\n");
		if (!bFallbackSet)
		{
			Md += TEXT("_Unset — the chooser returns null when no row matches._\n\n");
		}
		else
		{
			Md += FString::Printf(TEXT("- Struct type: `%s`\n\n"),
				*EscTbl(FallbackTypePath.IsEmpty() ? FallbackTypeName : FallbackTypePath));
		}

		if (NestedChooserPaths.Num() > 0)
		{
			Md += FString::Printf(TEXT("## Nested Choosers (%d)\n\n"), NestedChooserPaths.Num());
			for (const FString& P : NestedChooserPaths)
			{
				Md += FString::Printf(TEXT("- `%s`\n"), *EscTbl(P));
			}
			Md += TEXT("\n");
		}

		if (!BlueprintExporterUtil::SaveStringAtomic(Md, MdPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MdPath);
			return false;
		}

		// ---- JSON ----
		TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
		Root->SetStringField(TEXT("$schema"), TEXT("blueprint-exporter-v1"));
		Root->SetStringField(TEXT("assetType"), TEXT("ChooserTable"));
		Root->SetStringField(TEXT("assetPath"), Chooser->GetPathName());
		Root->SetStringField(TEXT("assetName"), Chooser->GetName());

		TSharedPtr<FJsonObject> ParentJson = MakeShared<FJsonObject>();
		ParentJson->SetStringField(TEXT("className"), ParentName);
		ParentJson->SetStringField(TEXT("classPath"), ParentPath);
		ParentJson->SetBoolField(TEXT("isNative"), ParentCls && ParentCls->IsNative());
		Root->SetObjectField(TEXT("parentClass"), ParentJson);

		Root->SetStringField(TEXT("resultType"), ResultTypeStr);
		Root->SetStringField(TEXT("outputObjectType"), OutputObjectTypePath);
		Root->SetBoolField(TEXT("isRootChooser"), bIsRoot);
		if (!bIsRoot)
		{
			Root->SetStringField(TEXT("rootChooserPath"), RootChooserPath);
		}

		TArray<TSharedPtr<FJsonValue>> ContextJson;
		for (const FString& P : ContextTypePaths)
		{
			TSharedPtr<FJsonObject> CtxO = MakeShared<FJsonObject>();
			CtxO->SetStringField(TEXT("structType"), P);
			ContextJson.Add(MakeShared<FJsonValueObject>(CtxO));
		}
		Root->SetArrayField(TEXT("contextData"), ContextJson);

		TArray<TSharedPtr<FJsonValue>> ColsJson;
		for (const FColumnRow& C : Columns)
		{
			TSharedPtr<FJsonObject> CO = MakeShared<FJsonObject>();
			CO->SetNumberField(TEXT("index"), C.Index);
			CO->SetStringField(TEXT("structType"), C.TypePath);
			CO->SetBoolField(TEXT("hasFilter"), C.bHasFilter);
			CO->SetBoolField(TEXT("hasOutput"), C.bHasOutput);
			CO->SetBoolField(TEXT("hasCost"), C.bHasCost);
			CO->SetBoolField(TEXT("disabled"), C.bDisabled);
			CO->SetStringField(TEXT("inputType"), C.InputTypePath);
			ColsJson.Add(MakeShared<FJsonValueObject>(CO));
		}
		Root->SetArrayField(TEXT("columns"), ColsJson);

		TArray<TSharedPtr<FJsonValue>> RowsJson;
		for (const FRowEntry& R : Rows)
		{
			TSharedPtr<FJsonObject> RO = MakeShared<FJsonObject>();
			RO->SetNumberField(TEXT("index"), R.Index);
			RO->SetStringField(TEXT("structType"), R.TypePath);
			RO->SetBoolField(TEXT("disabled"), R.bDisabled);
			RowsJson.Add(MakeShared<FJsonValueObject>(RO));
		}
		Root->SetArrayField(TEXT("rows"), RowsJson);

		TSharedPtr<FJsonObject> FallbackJson = MakeShared<FJsonObject>();
		FallbackJson->SetBoolField(TEXT("set"), bFallbackSet);
		FallbackJson->SetStringField(TEXT("structType"), FallbackTypePath);
		Root->SetObjectField(TEXT("fallback"), FallbackJson);

		TArray<TSharedPtr<FJsonValue>> NestedJson;
		for (const FString& P : NestedChooserPaths)
		{
			NestedJson.Add(MakeShared<FJsonValueString>(P));
		}
		Root->SetArrayField(TEXT("nestedChoosers"), NestedJson);
		Root->SetNumberField(TEXT("nestedObjects"), NestedObjectCount);

		Root->SetArrayField(TEXT("dependencies"), GatherDependenciesJson(AssetData));

		// Primary bucket = rows (the authored output set). Specialized empty —
		// per-cell filter values are tracked as a separate future slice, not
		// here. (If that slice ships, it adds `Chooser.CellValues` as
		// applicable-but-undocumented at that point.)
		Root->SetObjectField(TEXT("coverage"),
			BuildNonUBPCoverageJson(TEXT("rows"), Rows.Num(), Rows.Num(),
				{}, {}, OutOverallPct));

		if (!WriteJsonToFile(Root, MetaPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MetaPath);
			return false;
		}
		return true;
	}
#endif // WITH_CHOOSER_SUPPORT

#if WITH_POSESEARCH_SUPPORT
	// -------- PoseSearchDatabase --------
	// Structural dump of a UPoseSearchDatabase: Schema (channel list via deref),
	// DatabaseAnimationAssets (referenced anim asset + sampling range + mirror),
	// NormalizationSet (path only), plus top-level bias / performance config.
	// Schema channels are polymorphic UPoseSearchFeatureChannel subclasses; we
	// emit each channel's class path (not deep details — that's DeepDump
	// territory).
	const TCHAR* PoseSearchModeLabel(EPoseSearchMode M)
	{
		switch (M)
		{
		case EPoseSearchMode::BruteForce: return TEXT("BruteForce");
		case EPoseSearchMode::PCAKDTree:  return TEXT("PCAKDTree");
		case EPoseSearchMode::VPTree:     return TEXT("VPTree");
		case EPoseSearchMode::EventOnly:  return TEXT("EventOnly");
		default:                          return TEXT("Unknown");
		}
	}

	const TCHAR* PoseSearchMirrorLabel(EPoseSearchMirrorOption M)
	{
		switch (M)
		{
		case EPoseSearchMirrorOption::UnmirroredOnly:        return TEXT("UnmirroredOnly");
		case EPoseSearchMirrorOption::MirroredOnly:          return TEXT("MirroredOnly");
		case EPoseSearchMirrorOption::UnmirroredAndMirrored: return TEXT("UnmirroredAndMirrored");
		default:                                             return TEXT("Unknown");
		}
	}

	bool EmitPoseSearchDatabaseAsset(
		const FAssetData& AssetData,
		UPoseSearchDatabase* Database,
		const FString& MdPath,
		const FString& MetaPath,
		int32& OutOverallPct,
		FString& OutError)
	{
		if (!Database)
		{
			OutError = TEXT("null UPoseSearchDatabase");
			return false;
		}

		UClass* Cls = Database->GetClass();
		UClass* ParentCls = Cls ? Cls->GetSuperClass() : nullptr;
		const FString ParentName = ParentCls ? ParentCls->GetName() : FString();
		const FString ParentPath = ParentCls ? ParentCls->GetPathName() : FString();

		// ---- Schema ----
		const UPoseSearchSchema* Schema = Database->Schema;
		const FString SchemaPath = Schema ? Schema->GetPathName() : FString();
		const int32 SchemaSampleRate = Schema ? Schema->SampleRate : 0;
		const int32 SchemaCardinality = Schema ? Schema->SchemaCardinality : 0;

		// GetChannels() returns FinalizedChannels (authored + any injected debug
		// channels when bInjectAdditionalDebugChannels is set). That's what the
		// runtime actually uses, which is what an inventory consumer wants.
		struct FChannelRow
		{
			FString ClassName;
			FString ClassPath;
		};
		TArray<FChannelRow> Channels;
		if (Schema)
		{
			TConstArrayView<TObjectPtr<UPoseSearchFeatureChannel>> ChanArr = Schema->GetChannels();
			Channels.Reserve(ChanArr.Num());
			for (const TObjectPtr<UPoseSearchFeatureChannel>& Ch : ChanArr)
			{
				FChannelRow R;
				if (UClass* ChCls = Ch ? Ch->GetClass() : nullptr)
				{
					R.ClassName = ChCls->GetName();
					R.ClassPath = ChCls->GetPathName();
				}
				Channels.Add(MoveTemp(R));
			}
		}
		// Brief §8: channel order is semantically load-bearing (evaluated in
		// order), so preserve it. Determinism still holds — array order in the
		// serialized asset is stable across runs.

		// Skeleton roles (names only — authoring surface). GetRoledSkeletons()
		// is public.
		TArray<FString> SkeletonRoles;
		TArray<FString> SkeletonPaths;
		if (Schema)
		{
			for (const FPoseSearchRoledSkeleton& R : Schema->GetRoledSkeletons())
			{
				SkeletonRoles.Add(R.Role.IsNone() ? TEXT("(none)") : R.Role.ToString());
				SkeletonPaths.Add(R.Skeleton ? R.Skeleton->GetPathName() : FString());
			}
		}

		// ---- Animation assets ----
		struct FAnimRow
		{
			int32 Index = 0;
			FString AnimAssetPath;
			FString AnimAssetClass;
			float SamplingRangeMin = 0.f;
			float SamplingRangeMax = 0.f;
			bool bEnabled = true;
			bool bDisableReselection = false;
			FString MirrorOption;
		};
		TArray<FAnimRow> Anims;
		const int32 NumAnims = Database->GetNumAnimationAssets();
		Anims.Reserve(NumAnims);
		for (int32 i = 0; i < NumAnims; ++i)
		{
			FAnimRow R;
			R.Index = i;
			if (const FPoseSearchDatabaseAnimationAsset* Entry = Database->GetDatabaseAnimationAsset(i))
			{
				if (UObject* Asset = Entry->GetAnimationAsset())
				{
					R.AnimAssetPath = Asset->GetPathName();
					if (UClass* AC = Asset->GetClass())
					{
						R.AnimAssetClass = AC->GetName();
					}
				}
#if WITH_EDITORONLY_DATA
				const FFloatInterval Range = Entry->GetSamplingRange();
				R.SamplingRangeMin = Range.Min;
				R.SamplingRangeMax = Range.Max;
				R.bEnabled = Entry->IsEnabled();
				R.bDisableReselection = Entry->IsDisableReselection();
				R.MirrorOption = PoseSearchMirrorLabel(Entry->GetMirrorOption());
#endif
			}
			Anims.Add(MoveTemp(R));
		}
		// Preserve authored order — the array index matters for PoseSearch
		// (it's the SourceAssetIdx in the built search index).

		// ---- NormalizationSet ----
		FString NormalizationSetPath;
#if WITH_EDITORONLY_DATA
		if (Database->NormalizationSet)
		{
			NormalizationSetPath = Database->NormalizationSet->GetPathName();
		}
#endif

		// ---- Tags ----
		TArray<FString> Tags;
		Tags.Reserve(Database->Tags.Num());
		for (const FName& T : Database->Tags)
		{
			Tags.Add(T.ToString());
		}
		Tags.Sort([](const FString& A, const FString& B)
		{
			return A.Compare(B, ESearchCase::IgnoreCase) < 0;
		});

		// ---- Markdown ----
		FString Md;
		Md.Reserve(4 * 1024);
		Md += FString::Printf(TEXT("# %s\n\n"), *Database->GetName());
		Md += TEXT("## Identity\n\n");
		Md += TEXT("| Field | Value |\n|---|---|\n");
		Md += FString::Printf(TEXT("| Asset path | `%s` |\n"), *EscTbl(Database->GetPathName()));
		Md += FString::Printf(TEXT("| Asset name | `%s` |\n"), *EscTbl(Database->GetName()));
		Md += TEXT("| Asset type | `PoseSearchDatabase` |\n");
		Md += FString::Printf(TEXT("| Parent class | %s |\n"),
			ParentPath.IsEmpty() ? TEXT("_none_") : *FString::Printf(TEXT("`%s`"), *EscTbl(ParentPath)));
		Md += FString::Printf(TEXT("| Search mode | `%s` |\n"), PoseSearchModeLabel(Database->PoseSearchMode));
		Md += FString::Printf(TEXT("| Schema | %s |\n"),
			SchemaPath.IsEmpty() ? TEXT("_unset_") : *FString::Printf(TEXT("`%s`"), *EscTbl(SchemaPath)));
		Md += FString::Printf(TEXT("| Animation assets | **%d** |\n"), Anims.Num());
		Md += FString::Printf(TEXT("| Channels | **%d** |\n"), Channels.Num());
		Md += FString::Printf(TEXT("| Tags | %d |\n"), Tags.Num());
		Md += FString::Printf(TEXT("| Engine version | `%s` |\n"),
			*EscTbl(FEngineVersion::Current().ToString()));
		Md += TEXT("\n");

		// Schema section
		Md += TEXT("## Schema\n\n");
		if (!Schema)
		{
			Md += TEXT("_Schema is unset — the database cannot be indexed until one is assigned._\n\n");
		}
		else
		{
			Md += TEXT("| Field | Value |\n|---|---|\n");
			Md += FString::Printf(TEXT("| Path | `%s` |\n"), *EscTbl(SchemaPath));
			Md += FString::Printf(TEXT("| SampleRate | %d |\n"), SchemaSampleRate);
			Md += FString::Printf(TEXT("| Cardinality | %d |\n"), SchemaCardinality);
			Md += TEXT("\n");

			Md += FString::Printf(TEXT("### Skeleton roles (%d)\n\n"), SkeletonRoles.Num());
			if (SkeletonRoles.Num() == 0)
			{
				Md += TEXT("_No skeleton roles declared._\n\n");
			}
			else
			{
				Md += TEXT("| # | Role | Skeleton |\n|---:|---|---|\n");
				for (int32 i = 0; i < SkeletonRoles.Num(); ++i)
				{
					Md += FString::Printf(TEXT("| %d | `%s` | %s |\n"),
						i, *EscTbl(SkeletonRoles[i]),
						SkeletonPaths[i].IsEmpty() ? TEXT("_unset_") : *FString::Printf(TEXT("`%s`"), *EscTbl(SkeletonPaths[i])));
				}
				Md += TEXT("\n");
			}

			Md += FString::Printf(TEXT("### Channels (%d)\n\n"), Channels.Num());
			if (Channels.Num() == 0)
			{
				Md += TEXT("_No channels declared._\n\n");
			}
			else
			{
				Md += TEXT("| # | Class |\n|---:|---|\n");
				for (int32 i = 0; i < Channels.Num(); ++i)
				{
					Md += FString::Printf(TEXT("| %d | %s |\n"),
						i,
						Channels[i].ClassPath.IsEmpty() ? TEXT("_unset_") : *FString::Printf(TEXT("`%s`"), *EscTbl(Channels[i].ClassPath)));
				}
				Md += TEXT("\n");
			}
		}

		// Animation assets section
		Md += FString::Printf(TEXT("## Animation Assets (%d)\n\n"), Anims.Num());
		if (Anims.Num() == 0)
		{
			Md += TEXT("_No animation assets registered._\n\n");
		}
		else
		{
			Md += TEXT("| # | Asset class | Asset path | Sampling range | Mirror | Enabled |\n|---:|---|---|---|---|:---:|\n");
			for (const FAnimRow& A : Anims)
			{
				FString Range;
				if (A.SamplingRangeMin == 0.0f && A.SamplingRangeMax == 0.0f)
				{
					Range = TEXT("_full_");
				}
				else
				{
					Range = FString::Printf(TEXT("[%.3f, %.3f]"), A.SamplingRangeMin, A.SamplingRangeMax);
				}
				Md += FString::Printf(TEXT("| %d | %s | %s | %s | `%s` | %s |\n"),
					A.Index,
					A.AnimAssetClass.IsEmpty() ? TEXT("—") : *FString::Printf(TEXT("`%s`"), *EscTbl(A.AnimAssetClass)),
					A.AnimAssetPath.IsEmpty() ? TEXT("_unset_") : *FString::Printf(TEXT("`%s`"), *EscTbl(A.AnimAssetPath)),
					*Range,
					A.MirrorOption.IsEmpty() ? TEXT("—") : *EscTbl(A.MirrorOption),
					A.bEnabled ? TEXT("yes") : TEXT("no"));
			}
			Md += TEXT("\n");
		}

		// Normalization section
		Md += TEXT("## Normalization\n\n");
		if (NormalizationSetPath.IsEmpty())
		{
			Md += TEXT("_No NormalizationSet assigned._\n\n");
		}
		else
		{
			Md += FString::Printf(TEXT("- NormalizationSet: `%s`\n\n"), *EscTbl(NormalizationSetPath));
		}

		// Performance / bias section
		Md += TEXT("## Performance & Bias\n\n");
		Md += TEXT("| Field | Value |\n|---|---|\n");
		Md += FString::Printf(TEXT("| PoseSearchMode | `%s` |\n"), PoseSearchModeLabel(Database->PoseSearchMode));
		Md += FString::Printf(TEXT("| ContinuingPoseCostBias | %.4f |\n"), Database->ContinuingPoseCostBias);
		Md += FString::Printf(TEXT("| BaseCostBias | %.4f |\n"), Database->BaseCostBias);
		Md += FString::Printf(TEXT("| LoopingCostBias | %.4f |\n"), Database->LoopingCostBias);
		Md += FString::Printf(TEXT("| ContinuingInteractionCostBias | %.4f |\n"), Database->ContinuingInteractionCostBias);
		Md += FString::Printf(TEXT("| KDTreeQueryNumNeighbors | %d |\n"), Database->KDTreeQueryNumNeighbors);
#if WITH_EDITORONLY_DATA
		Md += FString::Printf(TEXT("| NumberOfPrincipalComponents | %d |\n"), Database->NumberOfPrincipalComponents);
		Md += FString::Printf(TEXT("| KDTreeMaxLeafSize | %d |\n"), Database->KDTreeMaxLeafSize);
		Md += FString::Printf(TEXT("| PosePruningSimilarityThreshold | %.4f |\n"), Database->PosePruningSimilarityThreshold);
		Md += FString::Printf(TEXT("| PCAValuesPruningSimilarityThreshold | %.4f |\n"), Database->PCAValuesPruningSimilarityThreshold);
		Md += FString::Printf(TEXT("| ExcludeFromDatabaseParameters | [%.3f, %.3f] |\n"),
			Database->ExcludeFromDatabaseParameters.Min, Database->ExcludeFromDatabaseParameters.Max);
		Md += FString::Printf(TEXT("| AdditionalExtrapolationTime | [%.3f, %.3f] |\n"),
			Database->AdditionalExtrapolationTime.Min, Database->AdditionalExtrapolationTime.Max);
#endif
		Md += TEXT("\n");

		if (Tags.Num() > 0)
		{
			Md += FString::Printf(TEXT("## Tags (%d)\n\n"), Tags.Num());
			for (const FString& T : Tags)
			{
				Md += FString::Printf(TEXT("- `%s`\n"), *EscTbl(T));
			}
			Md += TEXT("\n");
		}

		if (!BlueprintExporterUtil::SaveStringAtomic(Md, MdPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MdPath);
			return false;
		}

		// ---- JSON ----
		TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
		Root->SetStringField(TEXT("$schema"), TEXT("blueprint-exporter-v1"));
		Root->SetStringField(TEXT("assetType"), TEXT("PoseSearchDatabase"));
		Root->SetStringField(TEXT("assetPath"), Database->GetPathName());
		Root->SetStringField(TEXT("assetName"), Database->GetName());

		TSharedPtr<FJsonObject> ParentJson = MakeShared<FJsonObject>();
		ParentJson->SetStringField(TEXT("className"), ParentName);
		ParentJson->SetStringField(TEXT("classPath"), ParentPath);
		ParentJson->SetBoolField(TEXT("isNative"), ParentCls && ParentCls->IsNative());
		Root->SetObjectField(TEXT("parentClass"), ParentJson);

		// Schema sub-object
		TSharedPtr<FJsonObject> SchemaJson = MakeShared<FJsonObject>();
		SchemaJson->SetStringField(TEXT("path"), SchemaPath);
		SchemaJson->SetNumberField(TEXT("sampleRate"), SchemaSampleRate);
		SchemaJson->SetNumberField(TEXT("cardinality"), SchemaCardinality);

		TArray<TSharedPtr<FJsonValue>> ChannelsJson;
		for (const FChannelRow& C : Channels)
		{
			TSharedPtr<FJsonObject> CO = MakeShared<FJsonObject>();
			CO->SetStringField(TEXT("className"), C.ClassName);
			CO->SetStringField(TEXT("classPath"), C.ClassPath);
			ChannelsJson.Add(MakeShared<FJsonValueObject>(CO));
		}
		SchemaJson->SetArrayField(TEXT("channels"), ChannelsJson);

		TArray<TSharedPtr<FJsonValue>> RolesJson;
		for (int32 i = 0; i < SkeletonRoles.Num(); ++i)
		{
			TSharedPtr<FJsonObject> RO = MakeShared<FJsonObject>();
			RO->SetStringField(TEXT("role"), SkeletonRoles[i]);
			RO->SetStringField(TEXT("skeletonPath"), SkeletonPaths[i]);
			RolesJson.Add(MakeShared<FJsonValueObject>(RO));
		}
		SchemaJson->SetArrayField(TEXT("skeletonRoles"), RolesJson);
		Root->SetObjectField(TEXT("schema"), SchemaJson);

		// Animation assets
		TArray<TSharedPtr<FJsonValue>> AnimsJson;
		for (const FAnimRow& A : Anims)
		{
			TSharedPtr<FJsonObject> AO = MakeShared<FJsonObject>();
			AO->SetNumberField(TEXT("index"), A.Index);
			AO->SetStringField(TEXT("animAssetPath"), A.AnimAssetPath);
			AO->SetStringField(TEXT("animAssetClass"), A.AnimAssetClass);
			AO->SetNumberField(TEXT("samplingRangeMin"), A.SamplingRangeMin);
			AO->SetNumberField(TEXT("samplingRangeMax"), A.SamplingRangeMax);
			AO->SetBoolField(TEXT("enabled"), A.bEnabled);
			AO->SetBoolField(TEXT("disableReselection"), A.bDisableReselection);
			AO->SetStringField(TEXT("mirrorOption"), A.MirrorOption);
			AnimsJson.Add(MakeShared<FJsonValueObject>(AO));
		}
		Root->SetArrayField(TEXT("animationAssets"), AnimsJson);

		Root->SetStringField(TEXT("normalizationSet"), NormalizationSetPath);

		// Performance / bias
		TSharedPtr<FJsonObject> PerfJson = MakeShared<FJsonObject>();
		PerfJson->SetStringField(TEXT("poseSearchMode"), PoseSearchModeLabel(Database->PoseSearchMode));
		PerfJson->SetNumberField(TEXT("continuingPoseCostBias"), Database->ContinuingPoseCostBias);
		PerfJson->SetNumberField(TEXT("baseCostBias"), Database->BaseCostBias);
		PerfJson->SetNumberField(TEXT("loopingCostBias"), Database->LoopingCostBias);
		PerfJson->SetNumberField(TEXT("continuingInteractionCostBias"), Database->ContinuingInteractionCostBias);
		PerfJson->SetNumberField(TEXT("kdTreeQueryNumNeighbors"), Database->KDTreeQueryNumNeighbors);
#if WITH_EDITORONLY_DATA
		PerfJson->SetNumberField(TEXT("numberOfPrincipalComponents"), Database->NumberOfPrincipalComponents);
		PerfJson->SetNumberField(TEXT("kdTreeMaxLeafSize"), Database->KDTreeMaxLeafSize);
		PerfJson->SetNumberField(TEXT("posePruningSimilarityThreshold"), Database->PosePruningSimilarityThreshold);
		PerfJson->SetNumberField(TEXT("pcaValuesPruningSimilarityThreshold"), Database->PCAValuesPruningSimilarityThreshold);
		PerfJson->SetNumberField(TEXT("excludeFromDatabaseMin"), Database->ExcludeFromDatabaseParameters.Min);
		PerfJson->SetNumberField(TEXT("excludeFromDatabaseMax"), Database->ExcludeFromDatabaseParameters.Max);
		PerfJson->SetNumberField(TEXT("additionalExtrapolationMin"), Database->AdditionalExtrapolationTime.Min);
		PerfJson->SetNumberField(TEXT("additionalExtrapolationMax"), Database->AdditionalExtrapolationTime.Max);
#endif
		Root->SetObjectField(TEXT("performance"), PerfJson);

		// Tags
		TArray<TSharedPtr<FJsonValue>> TagsJson;
		for (const FString& T : Tags)
		{
			TagsJson.Add(MakeShared<FJsonValueString>(T));
		}
		Root->SetArrayField(TEXT("tags"), TagsJson);

		Root->SetArrayField(TEXT("dependencies"), GatherDependenciesJson(AssetData));

		// Primary bucket = animationAssets (the authored search corpus).
		// All documented; specialized empty — Schema / NormalizationSet /
		// performance are all emitted above and nothing about them is
		// specialized-but-undocumented.
		Root->SetObjectField(TEXT("coverage"),
			BuildNonUBPCoverageJson(TEXT("animationAssets"), Anims.Num(), Anims.Num(),
				{}, {}, OutOverallPct));

		if (!WriteJsonToFile(Root, MetaPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MetaPath);
			return false;
		}
		return true;
	}
#endif // WITH_POSESEARCH_SUPPORT

#if WITH_SMARTOBJECTS_SUPPORT
	// -------- SmartObjectDefinition --------
	// Structural dump of a USmartObjectDefinition: slot list (offset, rotation,
	// activity/runtime tags, preconditions-set, behavior-definitions list,
	// definition-data structs), default behavior definitions, object-level
	// preconditions, activity tags, user-tag filter, world-condition schema,
	// tag filtering / merging policies, parameter bag. Slot DefinitionData
	// struct types are emitted as class path per entry; per-field contents
	// stay in DeepDump territory.
	const TCHAR* SOTagFilteringPolicyLabel(ESmartObjectTagFilteringPolicy P)
	{
		switch (P)
		{
		case ESmartObjectTagFilteringPolicy::NoFilter: return TEXT("NoFilter");
		case ESmartObjectTagFilteringPolicy::Combine:  return TEXT("Combine");
		case ESmartObjectTagFilteringPolicy::Override: return TEXT("Override");
		default:                                       return TEXT("Unknown");
		}
	}

	const TCHAR* SOTagMergingPolicyLabel(ESmartObjectTagMergingPolicy P)
	{
		switch (P)
		{
		case ESmartObjectTagMergingPolicy::Combine:  return TEXT("Combine");
		case ESmartObjectTagMergingPolicy::Override: return TEXT("Override");
		default:                                     return TEXT("Unknown");
		}
	}

	// Flatten an FGameplayTagContainer into a sorted TArray<FString> of tag
	// names. Alpha-sorted for determinism; authored order in a tag container
	// isn't load-bearing (tag set semantics).
	TArray<FString> GameplayTagContainerToSortedNames(const FGameplayTagContainer& C)
	{
		TArray<FString> Out;
		TArray<FGameplayTag> Arr;
		C.GetGameplayTagArray(Arr);
		Out.Reserve(Arr.Num());
		for (const FGameplayTag& T : Arr)
		{
			Out.Add(T.ToString());
		}
		Out.Sort([](const FString& A, const FString& B)
		{
			return A.Compare(B, ESearchCase::IgnoreCase) < 0;
		});
		return Out;
	}

	// Pull TObjectPtr<USmartObjectBehaviorDefinition> elements from a private
	// TArray<TObjectPtr<>> via reflection. `DefaultBehaviorDefinitions` and the
	// per-slot `BehaviorDefinitions` array are both reachable this way; per-
	// slot is public on FSmartObjectSlotDefinition so the direct field read is
	// fine there, but `DefaultBehaviorDefinitions` is private on the class.
	TArray<FString> ReadObjectArrayPaths(const UObject* Owner, const TCHAR* PropertyName)
	{
		TArray<FString> Out;
		if (!Owner) return Out;
		FArrayProperty* ArrProp = FindFProperty<FArrayProperty>(Owner->GetClass(), PropertyName);
		if (!ArrProp) return Out;
		FObjectProperty* Inner = CastField<FObjectProperty>(ArrProp->Inner);
		if (!Inner) return Out;

		FScriptArrayHelper Helper(ArrProp, ArrProp->ContainerPtrToValuePtr<void>(Owner));
		for (int32 i = 0; i < Helper.Num(); ++i)
		{
			UObject* Obj = Inner->GetObjectPropertyValue(Helper.GetRawPtr(i));
			Out.Add(Obj ? Obj->GetPathName() : FString());
		}
		return Out;
	}

	bool EmitSmartObjectDefinitionAsset(
		const FAssetData& AssetData,
		USmartObjectDefinition* Def,
		const FString& MdPath,
		const FString& MetaPath,
		int32& OutOverallPct,
		FString& OutError)
	{
		if (!Def)
		{
			OutError = TEXT("null USmartObjectDefinition");
			return false;
		}

		UClass* Cls = Def->GetClass();
		UClass* ParentCls = Cls ? Cls->GetSuperClass() : nullptr;
		const FString ParentName = ParentCls ? ParentCls->GetName() : FString();
		const FString ParentPath = ParentCls ? ParentCls->GetPathName() : FString();

		// ---- Object-level data ----
		const TArray<FString> ObjectActivityTags = GameplayTagContainerToSortedNames(Def->GetActivityTags());
		const FGameplayTagQuery& UserTagFilter = Def->GetUserTagFilter();
		const bool bUserTagFilterEmpty = UserTagFilter.IsEmpty();
		const FString UserTagFilterDesc = bUserTagFilterEmpty ? FString() : UserTagFilter.GetDescription();

		const TSubclassOf<USmartObjectWorldConditionSchema>& SchemaClass = Def->GetWorldConditionSchemaClass();
		const FString WorldConditionSchemaPath = SchemaClass.Get() ? SchemaClass->GetPathName() : FString();

		const bool bPreconditionsValid = Def->GetPreconditions().IsValid();

		const FString TagFilteringPolicy = SOTagFilteringPolicyLabel(Def->GetUserTagsFilteringPolicy());
		const FString TagMergingPolicy   = SOTagMergingPolicyLabel(Def->GetActivityTagsMergingPolicy());

		const FInstancedPropertyBag& Parameters = Def->GetDefaultParameters();
		const int32 ParameterCount = Parameters.GetNumPropertiesInBag();

		// DefaultBehaviorDefinitions (private) via reflection.
		const TArray<FString> DefaultBehaviorPaths =
			ReadObjectArrayPaths(Def, TEXT("DefaultBehaviorDefinitions"));

		// ---- Slots ----
		struct FSlotRow
		{
			int32 Index = 0;
			FString Name;
			FVector3f Offset = FVector3f::ZeroVector;
			FRotator3f Rotation = FRotator3f::ZeroRotator;
			bool bEnabled = true;
			TArray<FString> ActivityTags;
			TArray<FString> RuntimeTags;
			bool bUserTagFilterEmpty = true;
			bool bSelectionPreconditionsValid = false;
			TArray<FString> BehaviorDefinitionPaths;
			TArray<FString> DefinitionDataStructTypes;
		};
		TArray<FSlotRow> Slots;
		TConstArrayView<FSmartObjectSlotDefinition> SlotView = Def->GetSlots();
		Slots.Reserve(SlotView.Num());
		for (int32 i = 0; i < SlotView.Num(); ++i)
		{
			const FSmartObjectSlotDefinition& S = SlotView[i];
			FSlotRow R;
			R.Index = i;
#if WITH_EDITORONLY_DATA
			R.Name = S.Name.ToString();
#endif
			R.Offset = S.Offset;
			R.Rotation = S.Rotation;
			R.bEnabled = S.bEnabled;
			R.ActivityTags = GameplayTagContainerToSortedNames(S.ActivityTags);
			R.RuntimeTags  = GameplayTagContainerToSortedNames(S.RuntimeTags);
			R.bUserTagFilterEmpty = S.UserTagFilter.IsEmpty();
			R.bSelectionPreconditionsValid = S.SelectionPreconditions.IsValid();

			R.BehaviorDefinitionPaths.Reserve(S.BehaviorDefinitions.Num());
			for (const TObjectPtr<USmartObjectBehaviorDefinition>& B : S.BehaviorDefinitions)
			{
				R.BehaviorDefinitionPaths.Add(B ? B->GetPathName() : FString());
			}

			R.DefinitionDataStructTypes.Reserve(S.DefinitionData.Num());
			for (const FSmartObjectDefinitionDataProxy& Proxy : S.DefinitionData)
			{
				const UScriptStruct* Type = Proxy.Data.GetScriptStruct();
				R.DefinitionDataStructTypes.Add(Type ? Type->GetPathName() : FString());
			}

			Slots.Add(MoveTemp(R));
		}
		// Slot order is semantically load-bearing (index is the SlotHandle key)
		// — preserve authored order.

		// Object-level DefinitionData (private TArray<FSmartObjectDefinitionDataProxy>)
		// via reflection. Each element carries a TInstancedStruct<FSmartObjectDefinitionData>.
		TArray<FString> ObjectDefinitionDataStructTypes;
		if (FArrayProperty* DdProp = FindFProperty<FArrayProperty>(Cls, TEXT("DefinitionData")))
		{
			FScriptArrayHelper Helper(DdProp, DdProp->ContainerPtrToValuePtr<void>(Def));
			FStructProperty* Inner = CastField<FStructProperty>(DdProp->Inner);
			if (Inner && Inner->Struct)
			{
				for (int32 i = 0; i < Helper.Num(); ++i)
				{
					const FSmartObjectDefinitionDataProxy* Proxy =
						reinterpret_cast<const FSmartObjectDefinitionDataProxy*>(Helper.GetRawPtr(i));
					const UScriptStruct* Type = Proxy ? Proxy->Data.GetScriptStruct() : nullptr;
					ObjectDefinitionDataStructTypes.Add(Type ? Type->GetPathName() : FString());
				}
			}
		}

		// ---- Markdown ----
		FString Md;
		Md.Reserve(4 * 1024);
		Md += FString::Printf(TEXT("# %s\n\n"), *Def->GetName());
		Md += TEXT("## Identity\n\n");
		Md += TEXT("| Field | Value |\n|---|---|\n");
		Md += FString::Printf(TEXT("| Asset path | `%s` |\n"), *EscTbl(Def->GetPathName()));
		Md += FString::Printf(TEXT("| Asset name | `%s` |\n"), *EscTbl(Def->GetName()));
		Md += TEXT("| Asset type | `SmartObjectDefinition` |\n");
		Md += FString::Printf(TEXT("| Parent class | %s |\n"),
			ParentPath.IsEmpty() ? TEXT("_none_") : *FString::Printf(TEXT("`%s`"), *EscTbl(ParentPath)));
		Md += FString::Printf(TEXT("| Slots | **%d** |\n"), Slots.Num());
		Md += FString::Printf(TEXT("| Default behaviors | %d |\n"), DefaultBehaviorPaths.Num());
		Md += FString::Printf(TEXT("| Activity tags | %d |\n"), ObjectActivityTags.Num());
		Md += FString::Printf(TEXT("| Preconditions set | %s |\n"), bPreconditionsValid ? TEXT("yes") : TEXT("no"));
		Md += FString::Printf(TEXT("| Parameters (bag) | %d |\n"), ParameterCount);
		Md += FString::Printf(TEXT("| Tag filtering policy | `%s` |\n"), *TagFilteringPolicy);
		Md += FString::Printf(TEXT("| Tag merging policy | `%s` |\n"), *TagMergingPolicy);
		Md += FString::Printf(TEXT("| World condition schema | %s |\n"),
			WorldConditionSchemaPath.IsEmpty() ? TEXT("_none_") : *FString::Printf(TEXT("`%s`"), *EscTbl(WorldConditionSchemaPath)));
		Md += FString::Printf(TEXT("| Engine version | `%s` |\n"),
			*EscTbl(FEngineVersion::Current().ToString()));
		Md += TEXT("\n");

		// Object-level activity tags / user filter
		if (ObjectActivityTags.Num() > 0 || !bUserTagFilterEmpty || ObjectDefinitionDataStructTypes.Num() > 0)
		{
			Md += TEXT("## Object-level Tags & Data\n\n");
			if (ObjectActivityTags.Num() > 0)
			{
				Md += FString::Printf(TEXT("- Activity tags (%d):\n"), ObjectActivityTags.Num());
				for (const FString& T : ObjectActivityTags)
				{
					Md += FString::Printf(TEXT("  - `%s`\n"), *EscTbl(T));
				}
			}
			if (!bUserTagFilterEmpty)
			{
				Md += FString::Printf(TEXT("- User tag filter: `%s`\n"),
					*EscTbl(UserTagFilterDesc.IsEmpty() ? TEXT("<set>") : *UserTagFilterDesc));
			}
			if (ObjectDefinitionDataStructTypes.Num() > 0)
			{
				Md += FString::Printf(TEXT("- DefinitionData (%d):\n"), ObjectDefinitionDataStructTypes.Num());
				for (const FString& T : ObjectDefinitionDataStructTypes)
				{
					Md += FString::Printf(TEXT("  - `%s`\n"),
						*EscTbl(T.IsEmpty() ? TEXT("_unset_") : *T));
				}
			}
			Md += TEXT("\n");
		}

		// Default behaviors
		Md += FString::Printf(TEXT("## Default Behavior Definitions (%d)\n\n"), DefaultBehaviorPaths.Num());
		if (DefaultBehaviorPaths.Num() == 0)
		{
			Md += TEXT("_No default behavior definitions declared — slots must supply their own._\n\n");
		}
		else
		{
			Md += TEXT("| # | Path |\n|---:|---|\n");
			for (int32 i = 0; i < DefaultBehaviorPaths.Num(); ++i)
			{
				Md += FString::Printf(TEXT("| %d | %s |\n"),
					i,
					DefaultBehaviorPaths[i].IsEmpty() ? TEXT("_unset_") : *FString::Printf(TEXT("`%s`"), *EscTbl(DefaultBehaviorPaths[i])));
			}
			Md += TEXT("\n");
		}

		// Slots
		Md += FString::Printf(TEXT("## Slots (%d)\n\n"), Slots.Num());
		if (Slots.Num() == 0)
		{
			Md += TEXT("_No slots defined._\n\n");
		}
		else
		{
			for (const FSlotRow& S : Slots)
			{
				const FString Header = S.Name.IsEmpty()
					? FString::Printf(TEXT("Slot %d"), S.Index)
					: FString::Printf(TEXT("Slot %d — `%s`"), S.Index, *S.Name);
				Md += FString::Printf(TEXT("### %s\n\n"), *Header);
				Md += TEXT("| Field | Value |\n|---|---|\n");
				Md += FString::Printf(TEXT("| Offset | (%.2f, %.2f, %.2f) |\n"),
					S.Offset.X, S.Offset.Y, S.Offset.Z);
				Md += FString::Printf(TEXT("| Rotation | (P=%.2f, Y=%.2f, R=%.2f) |\n"),
					S.Rotation.Pitch, S.Rotation.Yaw, S.Rotation.Roll);
				Md += FString::Printf(TEXT("| Enabled | %s |\n"), S.bEnabled ? TEXT("yes") : TEXT("no"));
				Md += FString::Printf(TEXT("| Activity tags | %d |\n"), S.ActivityTags.Num());
				Md += FString::Printf(TEXT("| Runtime tags | %d |\n"), S.RuntimeTags.Num());
				Md += FString::Printf(TEXT("| User tag filter | %s |\n"),
					S.bUserTagFilterEmpty ? TEXT("_empty_") : TEXT("set"));
				Md += FString::Printf(TEXT("| Selection preconditions | %s |\n"),
					S.bSelectionPreconditionsValid ? TEXT("set") : TEXT("_unset_"));
				Md += FString::Printf(TEXT("| Behavior definitions | %d |\n"), S.BehaviorDefinitionPaths.Num());
				Md += FString::Printf(TEXT("| DefinitionData entries | %d |\n"), S.DefinitionDataStructTypes.Num());
				Md += TEXT("\n");

				if (S.ActivityTags.Num() > 0)
				{
					Md += TEXT("Activity tags: ");
					TArray<FString> Bt;
					for (const FString& T : S.ActivityTags) Bt.Add(FString::Printf(TEXT("`%s`"), *EscTbl(T)));
					Md += FString::Join(Bt, TEXT(", "));
					Md += TEXT("\n\n");
				}
				if (S.BehaviorDefinitionPaths.Num() > 0)
				{
					Md += FString::Printf(TEXT("Behavior definitions (%d):\n"), S.BehaviorDefinitionPaths.Num());
					for (const FString& B : S.BehaviorDefinitionPaths)
					{
						Md += FString::Printf(TEXT("- `%s`\n"),
							*EscTbl(B.IsEmpty() ? TEXT("_unset_") : *B));
					}
					Md += TEXT("\n");
				}
				if (S.DefinitionDataStructTypes.Num() > 0)
				{
					Md += FString::Printf(TEXT("DefinitionData (%d):\n"), S.DefinitionDataStructTypes.Num());
					for (const FString& T : S.DefinitionDataStructTypes)
					{
						Md += FString::Printf(TEXT("- `%s`\n"),
							*EscTbl(T.IsEmpty() ? TEXT("_unset_") : *T));
					}
					Md += TEXT("\n");
				}
			}
		}

		if (!BlueprintExporterUtil::SaveStringAtomic(Md, MdPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MdPath);
			return false;
		}

		// ---- JSON ----
		TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
		Root->SetStringField(TEXT("$schema"), TEXT("blueprint-exporter-v1"));
		Root->SetStringField(TEXT("assetType"), TEXT("SmartObjectDefinition"));
		Root->SetStringField(TEXT("assetPath"), Def->GetPathName());
		Root->SetStringField(TEXT("assetName"), Def->GetName());

		TSharedPtr<FJsonObject> ParentJson = MakeShared<FJsonObject>();
		ParentJson->SetStringField(TEXT("className"), ParentName);
		ParentJson->SetStringField(TEXT("classPath"), ParentPath);
		ParentJson->SetBoolField(TEXT("isNative"), ParentCls && ParentCls->IsNative());
		Root->SetObjectField(TEXT("parentClass"), ParentJson);

		// Object-level metadata
		TSharedPtr<FJsonObject> ObjectJson = MakeShared<FJsonObject>();
		TArray<TSharedPtr<FJsonValue>> OActTagsJson;
		for (const FString& T : ObjectActivityTags) OActTagsJson.Add(MakeShared<FJsonValueString>(T));
		ObjectJson->SetArrayField(TEXT("activityTags"), OActTagsJson);
		ObjectJson->SetBoolField(TEXT("userTagFilterEmpty"), bUserTagFilterEmpty);
		ObjectJson->SetStringField(TEXT("userTagFilterDesc"), UserTagFilterDesc);
		ObjectJson->SetBoolField(TEXT("preconditionsSet"), bPreconditionsValid);
		ObjectJson->SetNumberField(TEXT("parameterCount"), ParameterCount);
		ObjectJson->SetStringField(TEXT("tagFilteringPolicy"), TagFilteringPolicy);
		ObjectJson->SetStringField(TEXT("tagMergingPolicy"), TagMergingPolicy);
		ObjectJson->SetStringField(TEXT("worldConditionSchema"), WorldConditionSchemaPath);

		TArray<TSharedPtr<FJsonValue>> ODefDataJson;
		for (const FString& T : ObjectDefinitionDataStructTypes) ODefDataJson.Add(MakeShared<FJsonValueString>(T));
		ObjectJson->SetArrayField(TEXT("definitionDataStructTypes"), ODefDataJson);
		Root->SetObjectField(TEXT("object"), ObjectJson);

		// Default behaviors
		TArray<TSharedPtr<FJsonValue>> DbdJson;
		for (const FString& P : DefaultBehaviorPaths) DbdJson.Add(MakeShared<FJsonValueString>(P));
		Root->SetArrayField(TEXT("defaultBehaviorDefinitions"), DbdJson);

		// Slots
		TArray<TSharedPtr<FJsonValue>> SlotsJson;
		for (const FSlotRow& S : Slots)
		{
			TSharedPtr<FJsonObject> SO = MakeShared<FJsonObject>();
			SO->SetNumberField(TEXT("index"), S.Index);
			SO->SetStringField(TEXT("name"), S.Name);
			TSharedPtr<FJsonObject> OffObj = MakeShared<FJsonObject>();
			OffObj->SetNumberField(TEXT("x"), S.Offset.X);
			OffObj->SetNumberField(TEXT("y"), S.Offset.Y);
			OffObj->SetNumberField(TEXT("z"), S.Offset.Z);
			SO->SetObjectField(TEXT("offset"), OffObj);
			TSharedPtr<FJsonObject> RotObj = MakeShared<FJsonObject>();
			RotObj->SetNumberField(TEXT("pitch"), S.Rotation.Pitch);
			RotObj->SetNumberField(TEXT("yaw"), S.Rotation.Yaw);
			RotObj->SetNumberField(TEXT("roll"), S.Rotation.Roll);
			SO->SetObjectField(TEXT("rotation"), RotObj);
			SO->SetBoolField(TEXT("enabled"), S.bEnabled);

			TArray<TSharedPtr<FJsonValue>> AT;
			for (const FString& T : S.ActivityTags) AT.Add(MakeShared<FJsonValueString>(T));
			SO->SetArrayField(TEXT("activityTags"), AT);

			TArray<TSharedPtr<FJsonValue>> RT;
			for (const FString& T : S.RuntimeTags) RT.Add(MakeShared<FJsonValueString>(T));
			SO->SetArrayField(TEXT("runtimeTags"), RT);

			SO->SetBoolField(TEXT("userTagFilterEmpty"), S.bUserTagFilterEmpty);
			SO->SetBoolField(TEXT("selectionPreconditionsSet"), S.bSelectionPreconditionsValid);

			TArray<TSharedPtr<FJsonValue>> BD;
			for (const FString& P : S.BehaviorDefinitionPaths) BD.Add(MakeShared<FJsonValueString>(P));
			SO->SetArrayField(TEXT("behaviorDefinitions"), BD);

			TArray<TSharedPtr<FJsonValue>> DD;
			for (const FString& T : S.DefinitionDataStructTypes) DD.Add(MakeShared<FJsonValueString>(T));
			SO->SetArrayField(TEXT("definitionDataStructTypes"), DD);

			SlotsJson.Add(MakeShared<FJsonValueObject>(SO));
		}
		Root->SetArrayField(TEXT("slots"), SlotsJson);

		Root->SetArrayField(TEXT("dependencies"), GatherDependenciesJson(AssetData));

		// Primary bucket = slots (the authored interaction points). All
		// documented; specialized empty. An empty-slot definition scores
		// 100% via the coverage-formula empty-primary suppression.
		Root->SetObjectField(TEXT("coverage"),
			BuildNonUBPCoverageJson(TEXT("slots"), Slots.Num(), Slots.Num(),
				{}, {}, OutOverallPct));

		if (!WriteJsonToFile(Root, MetaPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MetaPath);
			return false;
		}
		return true;
	}
#endif // WITH_SMARTOBJECTS_SUPPORT

	// -------- Generic non-UBP fallback --------
	// As of M3.3 P1c every named logic-bearing class has a typed handler
	// (ChooserTable → P1a, PoseSearchDatabase → P1b, SmartObjectDefinition →
	// P1c; BT / ST / UDS / UDE / DataTable / EnvQuery landed earlier). This
	// path is now purely defensive — if a future class joins the in-scope set
	// without its own handler, this produces a generic schema dump so the
	// aggregate still sees the asset, counts it under its `assetType`, and
	// surfaces its deps in DEPENDENCY_GRAPH.
	bool EmitGenericNonUBPAsset(
		const FAssetData& AssetData,
		UObject* Asset,
		const FString& MdPath,
		const FString& MetaPath,
		int32& OutOverallPct,
		FString& OutError)
	{
		if (!Asset)
		{
			OutError = TEXT("null UObject");
			return false;
		}

		UClass* Cls = Asset->GetClass();
		const FString AssetTypeName = Cls ? Cls->GetName() : FString(TEXT("Unknown"));
		UClass* ParentCls = Cls ? Cls->GetSuperClass() : nullptr;
		const FString ParentName = ParentCls ? ParentCls->GetName() : FString();
		const FString ParentPath = ParentCls ? ParentCls->GetPathName() : FString();

		struct FPropRow { FString Name; FString Type; FString Category; FString ToolTip; };
		TArray<FPropRow> Props;
		if (Cls)
		{
			// Walk all UPROPERTY-declared properties on the class. Inherited
			// properties are intentionally included — they're part of the
			// asset's authored schema from a content author's perspective.
			for (TFieldIterator<FProperty> It(Cls); It; ++It)
			{
				FProperty* P = *It;
				FPropRow R;
				R.Name = P->GetName();
				R.Type = P->GetCPPType();
				R.Category = P->GetMetaData(TEXT("Category"));
				R.ToolTip = P->GetToolTipText().ToString();
				Props.Add(MoveTemp(R));
			}
		}
		// Brief §8: deterministic ordering. Class fields iterate in declaration
		// order which is stable across runs, but inherited properties come
		// first and can reorder if UE reshuffles base classes between versions.
		// Sort alpha so upstream base-class reshuffles don't churn the file.
		Props.Sort([](const FPropRow& A, const FPropRow& B)
		{
			return A.Name.Compare(B.Name, ESearchCase::IgnoreCase) < 0;
		});

		FString Md;
		Md.Reserve(4 * 1024);
		Md += FString::Printf(TEXT("# %s\n\n"), *Asset->GetName());
		Md += TEXT("## Identity\n\n");
		Md += TEXT("| Field | Value |\n|---|---|\n");
		Md += FString::Printf(TEXT("| Asset path | `%s` |\n"), *EscTbl(Asset->GetPathName()));
		Md += FString::Printf(TEXT("| Asset name | `%s` |\n"), *EscTbl(Asset->GetName()));
		Md += FString::Printf(TEXT("| Asset type | `%s` |\n"), *EscTbl(AssetTypeName));
		Md += FString::Printf(TEXT("| Parent class | %s |\n"),
			ParentPath.IsEmpty() ? TEXT("_none_") : *FString::Printf(TEXT("`%s`"), *EscTbl(ParentPath)));
		Md += FString::Printf(TEXT("| Engine version | `%s` |\n"),
			*EscTbl(FEngineVersion::Current().ToString()));
		Md += TEXT("\n");

		Md += FString::Printf(TEXT("## Properties (%d)\n\n"), Props.Num());
		Md += TEXT("_Generic schema dump. A typed handler for this asset type is pending the DOW calibration slice._\n\n");
		if (Props.Num() == 0)
		{
			Md += TEXT("_No UPROPERTY-declared fields discovered on the class._\n\n");
		}
		else
		{
			Md += TEXT("| Name | Type | Category | ToolTip |\n|---|---|---|---|\n");
			for (const FPropRow& P : Props)
			{
				Md += FString::Printf(TEXT("| `%s` | `%s` | %s | %s |\n"),
					*EscTbl(P.Name), *EscTbl(P.Type),
					P.Category.IsEmpty() ? TEXT("—") : *FString::Printf(TEXT("`%s`"), *EscTbl(P.Category)),
					P.ToolTip.IsEmpty() ? TEXT("—") : *EscTbl(P.ToolTip));
			}
			Md += TEXT("\n");
		}

		if (!BlueprintExporterUtil::SaveStringAtomic(Md, MdPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MdPath);
			return false;
		}

		TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
		Root->SetStringField(TEXT("$schema"), TEXT("blueprint-exporter-v1"));
		Root->SetStringField(TEXT("assetType"), AssetTypeName);
		Root->SetStringField(TEXT("assetPath"), Asset->GetPathName());
		Root->SetStringField(TEXT("assetName"), Asset->GetName());

		TSharedPtr<FJsonObject> ParentJson = MakeShared<FJsonObject>();
		ParentJson->SetStringField(TEXT("className"), ParentName);
		ParentJson->SetStringField(TEXT("classPath"), ParentPath);
		ParentJson->SetBoolField(TEXT("isNative"), ParentCls && ParentCls->IsNative());
		Root->SetObjectField(TEXT("parentClass"), ParentJson);

		TArray<TSharedPtr<FJsonValue>> PropsJson;
		for (const FPropRow& P : Props)
		{
			TSharedPtr<FJsonObject> PO = MakeShared<FJsonObject>();
			PO->SetStringField(TEXT("name"), P.Name);
			PO->SetStringField(TEXT("type"), P.Type);
			PO->SetStringField(TEXT("category"), P.Category);
			PO->SetStringField(TEXT("toolTip"), P.ToolTip);
			PropsJson.Add(MakeShared<FJsonValueObject>(PO));
		}
		Root->SetArrayField(TEXT("properties"), PropsJson);
		Root->SetArrayField(TEXT("dependencies"), GatherDependenciesJson(AssetData));

		// Primary bucket = properties count. Specialized `applicable` comes
		// from the per-class map so authored content a typed handler will
		// eventually surface (PSD schema, Chooser columns, SmartObj slots)
		// shows up as an honest gap instead of a silent 100%. `documented`
		// stays empty — this is the fallback path, by definition not typed.
		const TArray<FString> Applicable = GetGenericFallbackApplicableSections(AssetTypeName);
		Root->SetObjectField(TEXT("coverage"),
			BuildNonUBPCoverageJson(TEXT("properties"), Props.Num(), Props.Num(),
				Applicable, /*Documented=*/{}, OutOverallPct));

		if (!WriteJsonToFile(Root, MetaPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MetaPath);
			return false;
		}
		return true;
	}

}

UProjectInventoryCommandlet::UProjectInventoryCommandlet()
{
	IsClient = false;
	IsEditor = true;
	IsServer = false;
	LogToConsole = true;
}

int32 UProjectInventoryCommandlet::Main(const FString& Params)
{
	LogLine(TEXT("INFO"), TEXT("Project Inventory Commandlet starting"));

	FString OutDir;
	if (!FParse::Value(*Params, TEXT("OutDir="), OutDir))
	{
		LogLine(TEXT("ERROR"),
			TEXT("Usage: -run=ProjectInventory -OutDir=<dir> [-MountPoint=/Game] [-Filter=/Game/<sub>] [-Resume] [-DeepDump] [-GcEvery=<N>]"),
			/*bIsError=*/true);
		return 2;
	}
	OutDir.TrimQuotesInline();

	FString MountPoint = TEXT("/Game");
	FParse::Value(*Params, TEXT("MountPoint="), MountPoint);
	MountPoint.TrimQuotesInline();
	if (!MountPoint.StartsWith(TEXT("/"))) MountPoint = TEXT("/") + MountPoint;
	while (MountPoint.EndsWith(TEXT("/")) && MountPoint.Len() > 1) MountPoint = MountPoint.LeftChop(1);

	FString FilterPrefix;
	FParse::Value(*Params, TEXT("Filter="), FilterPrefix);
	FilterPrefix.TrimQuotesInline();

	const bool bResume = FParse::Param(*Params, TEXT("Resume"));

	// Tier 2 sweep — emit `<Path>.deep.md` next to every `<Path>.md`. UBlueprint
	// family and UStateTree get the full DeepDump; other in-scope classes get a
	// short "out-of-scope, consult Tier 1" notice so the sibling pattern holds.
	const bool bEmitDeepDump = FParse::Param(*Params, TEXT("DeepDump"));

	int32 GcEvery = 50;
	FParse::Value(*Params, TEXT("GcEvery="), GcEvery);
	GcEvery = FMath::Clamp(GcEvery, 1, 10000);

	LogLine(TEXT("INFO"),
		FString::Printf(TEXT("OutDir=%s MountPoint=%s Filter=%s Resume=%s DeepDump=%s GcEvery=%d"),
			*OutDir, *MountPoint,
			FilterPrefix.IsEmpty() ? TEXT("(none)") : *FilterPrefix,
			bResume ? TEXT("yes") : TEXT("no"),
			bEmitDeepDump ? TEXT("yes") : TEXT("no"),
			GcEvery));

	if (!IFileManager::Get().DirectoryExists(*OutDir))
	{
		IFileManager::Get().MakeDirectory(*OutDir, /*Tree=*/true);
	}

	FAssetRegistryModule& AssetRegistryModule =
		FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	LogLine(TEXT("INFO"), TEXT("Scanning asset registry (synchronous)..."));
	const double ScanStart = FPlatformTime::Seconds();
	AssetRegistry.SearchAllAssets(/*bSynchronousSearch=*/true);
	LogLine(TEXT("INFO"),
		FString::Printf(TEXT("Scan complete in %.2fs"), FPlatformTime::Seconds() - ScanStart));

	FARFilter RegistryFilter;
	RegistryFilter.PackagePaths.Add(FName(*MountPoint));
	RegistryFilter.bRecursivePaths = true;

	TArray<FAssetData> AllAssets;
	AssetRegistry.GetAssets(RegistryFilter, AllAssets);

	// M3.2 processes the entire non-UBP logic-bearing set declared in
	// `GetNonUBPLogicBearingClassNames()`. Types with typed handlers (BT, ST,
	// UDS, UDE, DataTable, EnvQuery) get their full surface; the remainder
	// (SmartObjectDefinition, ChooserTable, PoseSearchDatabase) flow through
	// the generic non-UBP fallback until the DOW calibration slice replaces
	// them with typed handlers.
	TArray<FAssetData> ToProcess;
	for (const FAssetData& AD : AllAssets)
	{
		const FName ClassName = AD.AssetClassPath.GetAssetName();
		const bool bIsUBP = GetUBlueprintFamilyClassNames().Contains(ClassName);
		const bool bIsNonUBPLogic = GetNonUBPLogicBearingClassNames().Contains(ClassName);
		if (!bIsUBP && !bIsNonUBPLogic)
		{
			continue;
		}
		if (!FilterPrefix.IsEmpty())
		{
			const FString Pkg = AD.PackageName.ToString();
			if (!Pkg.StartsWith(FilterPrefix))
			{
				continue;
			}
		}
		ToProcess.Add(AD);
	}

	// Brief §8 deterministic ordering — alpha by package name before processing so
	// output and any in-progress state are reproducible.
	ToProcess.Sort([](const FAssetData& A, const FAssetData& B)
	{
		return A.PackageName.LexicalLess(B.PackageName);
	});

	LogLine(TEXT("INFO"),
		FString::Printf(TEXT("Logic-bearing assets to process (UBP + non-UBP): %d"), ToProcess.Num()));

	FBlueprintSerializer BPSerializer;
	TArray<FFailedAsset> FailedLoads;
	TArray<FFailedAsset> PartialLoads;

	const int32 Total = ToProcess.Num();
	int32 Processed = 0;
	int32 Skipped = 0;
	int32 EmittedSinceGc = 0;
	const double RunStart = FPlatformTime::Seconds();

	for (int32 Index = 0; Index < Total; ++Index)
	{
		const FAssetData& AssetData = ToProcess[Index];
		const FString PackageName = AssetData.PackageName.ToString();
		const FString OutBase = BuildAssetOutputBase(OutDir, PackageName);
		const FString MdPath = OutBase + TEXT(".md");
		const FString MetaPath = OutBase + TEXT(".meta.json");
		const FString DeepPath = OutBase + TEXT(".deep.md");

		// Resume: skip if .meta.json already written (the later of the two writes).
		if (bResume && IFileManager::Get().FileExists(*MetaPath))
		{
			++Skipped;
			LogLine(TEXT("SKIP"),
				FString::Printf(TEXT("[%d/%d] %s (resume, .meta.json exists)"),
					Index + 1, Total, *PackageName));
			continue;
		}

		// Ensure the output subtree exists for this package.
		const FString OutSubdir = FPaths::GetPath(OutBase);
		if (!IFileManager::Get().DirectoryExists(*OutSubdir))
		{
			IFileManager::Get().MakeDirectory(*OutSubdir, /*Tree=*/true);
		}

		UObject* Asset = AssetData.GetAsset();
		if (Asset == nullptr)
		{
			FailedLoads.Add({ PackageName, TEXT("AssetData.GetAsset() returned null") });
			LogLine(TEXT("FAIL"),
				FString::Printf(TEXT("[%d/%d] %s (load returned null)"), Index + 1, Total, *PackageName),
				/*bIsError=*/true);
			continue;
		}

		int32 OverallPct = 100;
		bool bOk = false;
		FString EmitError;

		// Dispatch by type. UBlueprint first because it's the common case and
		// matches every UBlueprint-derived subclass (AnimBP, WidgetBP, etc.).
		if (UBlueprint* Blueprint = Cast<UBlueprint>(Asset))
		{
			FExportedBlueprint ExportedData;
			FString SerializeError;
			if (!BPSerializer.SerializeBlueprint(Blueprint, ExportedData, SerializeError))
			{
				PartialLoads.Add({ PackageName, SerializeError.IsEmpty() ? TEXT("SerializeBlueprint returned false") : SerializeError });
				LogLine(TEXT("PARTIAL"),
					FString::Printf(TEXT("[%d/%d] %s (serializer error: %s)"),
						Index + 1, Total, *PackageName, *SerializeError),
					/*bIsError=*/true);
				continue;
			}
			// Brief §8: blank timestamp stamped by the base serializer.
			ExportedData.ExportInfo.ExportTimestamp.Reset();

			const FString Md = RenderBlueprintMarkdown(ExportedData);
			if (!BlueprintExporterUtil::SaveStringAtomic(Md, MdPath))
			{
				PartialLoads.Add({ PackageName, FString::Printf(TEXT("failed to write %s"), *MdPath) });
				LogLine(TEXT("FAIL"), FString::Printf(TEXT("write .md failed: %s"), *MdPath), /*bIsError=*/true);
				continue;
			}
			if (!WriteMetaJson(ExportedData, MetaPath, OverallPct))
			{
				PartialLoads.Add({ PackageName, FString::Printf(TEXT("failed to write %s"), *MetaPath) });
				LogLine(TEXT("FAIL"), FString::Printf(TEXT("write .meta.json failed: %s"), *MetaPath), /*bIsError=*/true);
				continue;
			}
			if (bEmitDeepDump)
			{
				const FString DeepMd =
					BlueprintExporter::DeepDump::RenderBlueprintMarkdown(ExportedData);
				if (!BlueprintExporterUtil::SaveStringAtomic(DeepMd, DeepPath))
				{
					PartialLoads.Add({ PackageName, FString::Printf(TEXT("failed to write %s"), *DeepPath) });
					LogLine(TEXT("FAIL"), FString::Printf(TEXT("write .deep.md failed: %s"), *DeepPath), /*bIsError=*/true);
					continue;
				}
			}
			bOk = true;
		}
		else if (UBehaviorTree* BT = Cast<UBehaviorTree>(Asset))
		{
			bOk = EmitBehaviorTreeAsset(AssetData, BT, MdPath, MetaPath, OverallPct, EmitError);
		}
#if WITH_STATETREE_SUPPORT
		else if (UStateTree* ST = Cast<UStateTree>(Asset))
		{
			bOk = EmitStateTreeAsset(AssetData, ST, MdPath, MetaPath, OverallPct, EmitError,
				bEmitDeepDump, DeepPath);
		}
#endif
		else if (UUserDefinedStruct* UDS = Cast<UUserDefinedStruct>(Asset))
		{
			bOk = EmitUserDefinedStructAsset(AssetData, UDS, MdPath, MetaPath, OverallPct, EmitError);
		}
		else if (UUserDefinedEnum* UDE = Cast<UUserDefinedEnum>(Asset))
		{
			bOk = EmitUserDefinedEnumAsset(AssetData, UDE, MdPath, MetaPath, OverallPct, EmitError);
		}
		else if (UDataTable* DT = Cast<UDataTable>(Asset))
		{
			bOk = EmitDataTableAsset(AssetData, DT, MdPath, MetaPath, OverallPct, EmitError);
		}
		else if (UEnvQuery* EQS = Cast<UEnvQuery>(Asset))
		{
			bOk = EmitEnvQueryAsset(AssetData, EQS, MdPath, MetaPath, OverallPct, EmitError);
		}
#if WITH_CHOOSER_SUPPORT
		else if (UChooserTable* Chooser = Cast<UChooserTable>(Asset))
		{
			bOk = EmitChooserTableAsset(AssetData, Chooser, MdPath, MetaPath, OverallPct, EmitError);
		}
#endif
#if WITH_POSESEARCH_SUPPORT
		else if (UPoseSearchDatabase* PSD = Cast<UPoseSearchDatabase>(Asset))
		{
			bOk = EmitPoseSearchDatabaseAsset(AssetData, PSD, MdPath, MetaPath, OverallPct, EmitError);
		}
#endif
#if WITH_SMARTOBJECTS_SUPPORT
		else if (USmartObjectDefinition* SOD = Cast<USmartObjectDefinition>(Asset))
		{
			bOk = EmitSmartObjectDefinitionAsset(AssetData, SOD, MdPath, MetaPath, OverallPct, EmitError);
		}
#endif
		else
		{
			// Defensive fallback for a future unhandled in-scope class —
			// every current class has its own typed handler as of M3.3 P1c.
			bOk = EmitGenericNonUBPAsset(AssetData, Asset, MdPath, MetaPath, OverallPct, EmitError);
		}

		// `.deep.md` sibling. UBP and ST already wrote theirs in their own
		// branches. SmartObjectDefinition (M11), BehaviorTree (M12),
		// DataTable (M13), and ChooserTable (M14) get full Tier 2 here via
		// their dedicated renderers. Everything else gets the out-of-scope
		// notice so the Tier 1 ↔ Tier 2 sibling pattern is uniform across
		// the sweep — downstream tooling doesn't have to second-guess why
		// some assets have a `.deep.md` and others don't.
		if (bOk && bEmitDeepDump)
		{
			const bool bAlreadyWroteDeep = Cast<UBlueprint>(Asset) != nullptr
#if WITH_STATETREE_SUPPORT
				|| Cast<UStateTree>(Asset) != nullptr
#endif
				;
			if (!bAlreadyWroteDeep)
			{
				FString DeepMd;
#if WITH_SMARTOBJECTS_SUPPORT
				if (Cast<USmartObjectDefinition>(Asset) != nullptr)
				{
					DeepMd = BlueprintExporter::DeepDump::RenderSmartObjectDefinitionMarkdown(Asset);
				}
				else
#endif
				if (Cast<UBehaviorTree>(Asset) != nullptr)
				{
					DeepMd = BlueprintExporter::DeepDump::RenderBehaviorTreeMarkdown(Asset);
				}
				else if (Cast<UDataTable>(Asset) != nullptr)
				{
					DeepMd = BlueprintExporter::DeepDump::RenderDataTableMarkdown(Asset);
				}
#if WITH_CHOOSER_SUPPORT
				else if (Cast<UChooserTable>(Asset) != nullptr)
				{
					DeepMd = BlueprintExporter::DeepDump::RenderChooserTableMarkdown(Asset);
				}
#endif
				else if (Cast<UEnvQuery>(Asset) != nullptr)
				{
					DeepMd = BlueprintExporter::DeepDump::RenderEnvQueryMarkdown(Asset);
				}
				// M29.6.4 — all three CO renderers dispatch by class-name match
				// and read through reflection, so no Cast<> or MuCO/* dep. The
				// renderers themselves handle the "not this class" fallthrough
				// via RenderOutOfScopeNotice, but we still dispatch by name here
				// so unrelated UObjects fall through to the generic path below.
				else if (Asset && Asset->GetClass()
					&& Asset->GetClass()->GetName() == TEXT("CustomizableObjectInstance"))
				{
					DeepMd = BlueprintExporter::DeepDump::RenderCustomizableObjectInstanceMarkdown(Asset);
				}
				else if (Asset && Asset->GetClass()
					&& Asset->GetClass()->GetName() == TEXT("CustomizableObject"))
				{
					DeepMd = BlueprintExporter::DeepDump::RenderCustomizableObjectMarkdown(Asset);
				}
				else if (Asset && Asset->GetClass()
					&& Asset->GetClass()->GetName() == TEXT("CustomizableObjectMacroLibrary"))
				{
					DeepMd = BlueprintExporter::DeepDump::RenderCustomizableObjectMacroLibraryMarkdown(Asset);
				}
				else
				{
					const FString ClassName = AssetData.AssetClassPath.GetAssetName().ToString();
					DeepMd = BlueprintExporter::DeepDump::RenderOutOfScopeNotice(
						AssetData.AssetName.ToString(), PackageName, ClassName);
				}
				if (!BlueprintExporterUtil::SaveStringAtomic(DeepMd, DeepPath))
				{
					bOk = false;
					EmitError = FString::Printf(TEXT("failed to write %s"), *DeepPath);
				}
			}
		}

		if (!bOk)
		{
			PartialLoads.Add({ PackageName, EmitError.IsEmpty() ? FString(TEXT("emit returned false")) : EmitError });
			LogLine(TEXT("PARTIAL"),
				FString::Printf(TEXT("[%d/%d] %s (emit error: %s)"),
					Index + 1, Total, *PackageName, *EmitError),
				/*bIsError=*/true);
			continue;
		}

		++Processed;
		++EmittedSinceGc;

		const double Elapsed = FPlatformTime::Seconds() - RunStart;
		const double AvgPerAsset = (Processed + Skipped) > 0 ? Elapsed / double(Processed + Skipped) : 0.0;
		const double ETA = AvgPerAsset * double(Total - (Index + 1));
		LogLine(TEXT("OK"),
			FString::Printf(TEXT("[%d/%d] %s (coverage=%d%%, elapsed=%.0fs, ETA=%.0fs)"),
				Index + 1, Total, *PackageName, OverallPct, Elapsed, ETA));

		if (EmittedSinceGc >= GcEvery)
		{
			CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);
			EmittedSinceGc = 0;
		}
	}

	WriteFailureLog(OutDir, TEXT("FAILED_LOADS.md"),
		TEXT("Failed loads (Phase 1)"), FailedLoads);
	WriteFailureLog(OutDir, TEXT("PARTIAL_LOADS.md"),
		TEXT("Partial loads (Phase 1 — serializer or write failure)"), PartialLoads);

	LogLine(TEXT("RESULT"),
		FString::Printf(TEXT("Processed=%d Skipped=%d Failed=%d Partial=%d (total in-scope=%d)"),
			Processed, Skipped, FailedLoads.Num(), PartialLoads.Num(), Total));
	LogLine(TEXT("STATUS"), TEXT("SUCCESS"));
	return 0;
}
