// Copyright 10 Chambers. All Rights Reserved.

#include "Commandlets/AggregateInventoryCommandlet.h"
#include "BlueprintExporterModule.h"
#include "Util/AtomicFileWriter.h"
#include "Util/CommandletLog.h"
#include "InventoryEmit/PerAssetEmit.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"

namespace
{
	using BlueprintExporter::Util::LogLine;
	// Shared markdown-cell escaper. Hoisted to avoid unity-build ODR
	// collision with ProjectPluginsCommandlet.cpp's identical-body copy.
	using BlueprintExporter::InventoryEmit::EscTbl;

	// --------------------------------------------------------------------
	// Aggregate data model: parsed from each .meta.json
	// --------------------------------------------------------------------

	struct FReplicatedVar
	{
		FString Name;
		FString Type;            // pretty-formatted from `variableType` JSON sub-obj
		FString Condition;       // e.g., "COND_Autonomy", empty if default
		FString RepNotifyFunc;   // empty if `repNotify` was false
	};

	struct FRpcFunc
	{
		FString Name;
		FString Direction;       // "Server" | "Client" | "NetMulticast"
		bool    bReliable = false;
		bool    bAuthorityOnly = false;
		bool    bCosmetic = false;
		FString Signature;       // compact "(float InAmount, bool bLog)"
	};

	struct FAggregateDepRef
	{
		FString AssetPath;
		bool    bIsBlueprint   = false;
		bool    bIsNativeClass = false;
	};

	struct FAggregateAsset
	{
		// Identity
		FString PackageName;          // "/Game/TestBlueprints/BP_NetRep"  (derived)
		FString AssetPath;            // "/Game/TestBlueprints/BP_NetRep.BP_NetRep"
		FString AssetName;
		FString Subclass;             // "Blueprint", "WidgetBlueprint", etc.
		FString ParentClassName;
		FString ParentClassPath;
		bool    bParentIsNative = false;
		TArray<FString> Interfaces;

		// Replication surface (brief §5 REPLICATION_MATRIX)
		TArray<FReplicatedVar> ReplicatedVars;
		TArray<FRpcFunc>       RpcFunctions;

		// Dependency surface (brief §5 DEPENDENCY_GRAPH)
		TArray<FAggregateDepRef> HardRefsOut;
		TArray<FAggregateDepRef> SoftRefsOut;

		// Coverage (brief §4 / §11A HEALTH_REPORT inputs)
		int32 OverallCoveragePct = 100;
		int32 VarsTotal = 0, VarsDoc = 0;
		int32 FnsTotal = 0, FnsDoc = 0;
		int32 CompsTotal = 0, CompsDoc = 0;
		int32 GraphsTotal = 0, GraphsDoc = 0;
		TArray<FString> SpecializedApplicable;
		TArray<FString> SpecializedDocumented;

		// M4.1 domain-overview metrics (populated per assetType).
		// BehaviorTree:
		FString BlackboardPath;       // /Game/.../BB_Foo or empty
		int32 BTNodeCount = 0;
		int32 BBKeyCount = 0;
		// StateTree:
		FString STSchema;             // e.g., "StateTreeComponentSchema"
		int32 STStateCount = 0;       // recursive count including nested children
		int32 STEvaluatorCount = 0;
		int32 STGlobalTaskCount = 0;
		// UserDefinedStruct:
		int32 UDSFieldCount = 0;
		// UserDefinedEnum:
		int32 UDEValueCount = 0;
		// UBlueprint specialized metrics:
		int32 BPComponentCount = 0;   // SCS root count
		int32 BPFunctionCount = 0;
		int32 BPVariableCount = 0;
	};

	// --------------------------------------------------------------------
	// Safe JSON field access helpers
	// --------------------------------------------------------------------

	FString JsonStr(const TSharedPtr<FJsonObject>& Obj, const TCHAR* Field)
	{
		if (!Obj.IsValid()) return FString();
		FString Out;
		Obj->TryGetStringField(Field, Out);
		return Out;
	}

	bool JsonBool(const TSharedPtr<FJsonObject>& Obj, const TCHAR* Field, bool Default = false)
	{
		if (!Obj.IsValid()) return Default;
		bool Out = Default;
		Obj->TryGetBoolField(Field, Out);
		return Out;
	}

	int32 JsonInt(const TSharedPtr<FJsonObject>& Obj, const TCHAR* Field, int32 Default = 0)
	{
		if (!Obj.IsValid()) return Default;
		int32 Out = Default;
		Obj->TryGetNumberField(Field, Out);
		return Out;
	}

	TSharedPtr<FJsonObject> JsonObj(const TSharedPtr<FJsonObject>& Obj, const TCHAR* Field)
	{
		if (!Obj.IsValid()) return nullptr;
		const TSharedPtr<FJsonObject>* Inner = nullptr;
		if (Obj->TryGetObjectField(Field, Inner) && Inner)
		{
			return *Inner;
		}
		return nullptr;
	}

	const TArray<TSharedPtr<FJsonValue>>* JsonArr(const TSharedPtr<FJsonObject>& Obj, const TCHAR* Field)
	{
		if (!Obj.IsValid()) return nullptr;
		const TArray<TSharedPtr<FJsonValue>>* Out = nullptr;
		Obj->TryGetArrayField(Field, Out);
		return Out;
	}

	// --------------------------------------------------------------------
	// Derive package name from full asset path "/Game/Foo/Bar.Bar" -> "/Game/Foo/Bar"
	// --------------------------------------------------------------------
	FString PackageNameFromAssetPath(const FString& AssetPath)
	{
		int32 DotIdx = INDEX_NONE;
		if (AssetPath.FindLastChar(TEXT('.'), DotIdx))
		{
			return AssetPath.Left(DotIdx);
		}
		return AssetPath;
	}

	// Mount-relative top-level folder for counts-by-folder rollup.
	// "/Game/TestBlueprints/Sub/BP_Foo" -> "/Game/TestBlueprints"
	FString TopLevelFolderOf(const FString& PackageName)
	{
		if (!PackageName.StartsWith(TEXT("/")))
		{
			return PackageName;
		}
		// Find first "/" after the leading "/Game/"
		int32 Second = PackageName.Find(TEXT("/"), ESearchCase::CaseSensitive, ESearchDir::FromStart, 1);
		if (Second == INDEX_NONE)
		{
			return PackageName;
		}
		int32 Third = PackageName.Find(TEXT("/"), ESearchCase::CaseSensitive, ESearchDir::FromStart, Second + 1);
		if (Third == INDEX_NONE)
		{
			return PackageName;
		}
		return PackageName.Left(Third);
	}

	FString StripScriptPrefix(const FString& ClassPath)
	{
		int32 DotIdx = INDEX_NONE;
		if (ClassPath.FindLastChar(TEXT('.'), DotIdx))
		{
			return ClassPath.Mid(DotIdx + 1);
		}
		return ClassPath;
	}

	FString FormatPinTypeFromJson(const TSharedPtr<FJsonObject>& TypeObj)
	{
		if (!TypeObj.IsValid()) return TEXT("unknown");
		FString Base = JsonStr(TypeObj, TEXT("category"));
		if (Base.IsEmpty()) Base = TEXT("unknown");

		FString Inner;
		const FString Sub = JsonStr(TypeObj, TEXT("subCategoryObject"));
		if (!Sub.IsEmpty())
		{
			Inner = StripScriptPrefix(Sub);
		}
		else
		{
			const FString PinSub = JsonStr(TypeObj, TEXT("pinSubCategory"));
			if (!PinSub.IsEmpty() && !PinSub.Equals(TEXT("None"), ESearchCase::IgnoreCase))
			{
				Inner = PinSub;
			}
		}

		FString Rendered = Inner.IsEmpty() ? Base : FString::Printf(TEXT("%s<%s>"), *Base, *Inner);
		if (JsonBool(TypeObj, TEXT("isArray")))
		{
			Rendered = FString::Printf(TEXT("TArray<%s>"), *Rendered);
		}
		else if (JsonBool(TypeObj, TEXT("isSet")))
		{
			Rendered = FString::Printf(TEXT("TSet<%s>"), *Rendered);
		}
		else if (JsonBool(TypeObj, TEXT("isMap")))
		{
			const FString Value = JsonStr(TypeObj, TEXT("valueTerminalType"));
			Rendered = FString::Printf(TEXT("TMap<%s, %s>"),
				*Rendered, Value.IsEmpty() ? TEXT("?") : *Value);
		}
		if (JsonBool(TypeObj, TEXT("isReference"))) Rendered += TEXT("&");
		return Rendered;
	}

	bool ParseMetaJsonFile(const FString& Path, FAggregateAsset& Out)
	{
		FString JsonString;
		if (!FFileHelper::LoadFileToString(JsonString, *Path))
		{
			return false;
		}
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
		TSharedPtr<FJsonObject> Root;
		if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
		{
			return false;
		}

		Out.AssetPath   = JsonStr(Root, TEXT("assetPath"));
		Out.AssetName   = JsonStr(Root, TEXT("assetName"));
		// Prefer `assetType` (universal across UBP + non-UBP) over
		// `blueprintSubclass` (UBP-only). M3.1 sets `assetType` everywhere;
		// older `.meta.json` from pre-M3.1 runs still populate
		// `blueprintSubclass` — fall back to that for back-compat.
		Out.Subclass = JsonStr(Root, TEXT("assetType"));
		if (Out.Subclass.IsEmpty())
		{
			Out.Subclass = JsonStr(Root, TEXT("blueprintSubclass"));
		}
		Out.PackageName = PackageNameFromAssetPath(Out.AssetPath);

		TSharedPtr<FJsonObject> Parent = JsonObj(Root, TEXT("parentClass"));
		if (Parent.IsValid())
		{
			Out.ParentClassName = JsonStr(Parent, TEXT("className"));
			Out.ParentClassPath = JsonStr(Parent, TEXT("classPath"));
			Out.bParentIsNative = JsonBool(Parent, TEXT("isNative"));
		}

		if (const auto* Ifaces = JsonArr(Root, TEXT("implementedInterfaces")))
		{
			for (const TSharedPtr<FJsonValue>& V : *Ifaces)
			{
				FString S;
				if (V.IsValid() && V->TryGetString(S))
				{
					Out.Interfaces.Add(S);
				}
			}
		}

		// Replicated variables
		if (const auto* Vars = JsonArr(Root, TEXT("variables")))
		{
			for (const TSharedPtr<FJsonValue>& V : *Vars)
			{
				const TSharedPtr<FJsonObject>* VarObjPtr = nullptr;
				if (!V.IsValid() || !V->TryGetObject(VarObjPtr) || !VarObjPtr) continue;
				const TSharedPtr<FJsonObject> VarObj = *VarObjPtr;

				TSharedPtr<FJsonObject> Flags = JsonObj(VarObj, TEXT("flags"));
				if (!JsonBool(Flags, TEXT("replicated"))) continue;

				FReplicatedVar Rep;
				Rep.Name = JsonStr(VarObj, TEXT("variableName"));
				Rep.Type = FormatPinTypeFromJson(JsonObj(VarObj, TEXT("variableType")));
				Rep.Condition = JsonStr(Flags, TEXT("replicationCondition"));
				if (JsonBool(Flags, TEXT("repNotify")))
				{
					Rep.RepNotifyFunc = JsonStr(Flags, TEXT("repNotifyFunc"));
					if (Rep.RepNotifyFunc.IsEmpty())
					{
						Rep.RepNotifyFunc = TEXT("(unnamed)");
					}
				}
				Out.ReplicatedVars.Add(MoveTemp(Rep));
			}
		}

		// RPC functions — functions whose flags carry Server/Client/NetMulticast.
		// M3.2 extends FExportedFunctionFlags with these bits; older `.meta.json`
		// from pre-M3.2 runs will simply have them default-false, so the loop
		// produces zero RPC rows for those assets.
		auto FormatParamListJson = [](const TArray<TSharedPtr<FJsonValue>>* Arr) -> FString
		{
			if (!Arr) return FString();
			TArray<FString> Parts;
			for (const TSharedPtr<FJsonValue>& V : *Arr)
			{
				const TSharedPtr<FJsonObject>* PObjPtr = nullptr;
				if (!V.IsValid() || !V->TryGetObject(PObjPtr) || !PObjPtr) continue;
				const TSharedPtr<FJsonObject> PObj = *PObjPtr;
				const FString PName = JsonStr(PObj, TEXT("paramName"));
				const FString PType = FormatPinTypeFromJson(JsonObj(PObj, TEXT("paramType")));
				Parts.Add(FString::Printf(TEXT("%s %s"), *PType, *PName));
			}
			return FString::Printf(TEXT("(%s)"), *FString::Join(Parts, TEXT(", ")));
		};
		if (const auto* Fns = JsonArr(Root, TEXT("functions")))
		{
			for (const TSharedPtr<FJsonValue>& V : *Fns)
			{
				const TSharedPtr<FJsonObject>* FnObjPtr = nullptr;
				if (!V.IsValid() || !V->TryGetObject(FnObjPtr) || !FnObjPtr) continue;
				const TSharedPtr<FJsonObject> FnObj = *FnObjPtr;

				TSharedPtr<FJsonObject> Flags = JsonObj(FnObj, TEXT("flags"));
				const bool bServer    = JsonBool(Flags, TEXT("server"));
				const bool bClient    = JsonBool(Flags, TEXT("client"));
				const bool bMulticast = JsonBool(Flags, TEXT("netMulticast"));
				if (!bServer && !bClient && !bMulticast) continue;

				FRpcFunc Rpc;
				Rpc.Name = JsonStr(FnObj, TEXT("functionName"));
				// Direction priority: Multicast > Server > Client is arbitrary
				// but exclusive in UE (the engine rejects multiple directions
				// at compile time) so any ordering works.
				Rpc.Direction = bMulticast ? TEXT("NetMulticast")
							   : bServer   ? TEXT("Server")
							   : TEXT("Client");
				Rpc.bReliable       = JsonBool(Flags, TEXT("reliable"));
				Rpc.bAuthorityOnly  = JsonBool(Flags, TEXT("blueprintAuthorityOnly"));
				Rpc.bCosmetic       = JsonBool(Flags, TEXT("blueprintCosmetic"));
				Rpc.Signature       = FormatParamListJson(JsonArr(FnObj, TEXT("inputs")));
				Out.RpcFunctions.Add(MoveTemp(Rpc));
			}
		}

		// Dependencies
		if (const auto* Deps = JsonArr(Root, TEXT("dependencies")))
		{
			for (const TSharedPtr<FJsonValue>& V : *Deps)
			{
				const TSharedPtr<FJsonObject>* DepObjPtr = nullptr;
				if (!V.IsValid() || !V->TryGetObject(DepObjPtr) || !DepObjPtr) continue;
				const TSharedPtr<FJsonObject> DepObj = *DepObjPtr;

				FAggregateDepRef Ref;
				Ref.AssetPath      = JsonStr(DepObj, TEXT("assetPath"));
				Ref.bIsBlueprint   = JsonBool(DepObj, TEXT("isBlueprint"));
				Ref.bIsNativeClass = JsonBool(DepObj, TEXT("isNativeClass"));
				const FString Kind = JsonStr(DepObj, TEXT("dependencyType"));
				if (Kind.Equals(TEXT("Soft"), ESearchCase::IgnoreCase))
				{
					Out.SoftRefsOut.Add(MoveTemp(Ref));
				}
				else
				{
					Out.HardRefsOut.Add(MoveTemp(Ref));
				}
			}
		}

		// Coverage
		TSharedPtr<FJsonObject> Cov = JsonObj(Root, TEXT("coverage"));
		if (Cov.IsValid())
		{
			Out.OverallCoveragePct = JsonInt(Cov, TEXT("overallPct"), 100);
			auto ReadBucket = [&](const TCHAR* Field, int32& Total, int32& Doc)
			{
				if (TSharedPtr<FJsonObject> B = JsonObj(Cov, Field))
				{
					Total = JsonInt(B, TEXT("total"));
					Doc   = JsonInt(B, TEXT("documented"));
				}
			};
			ReadBucket(TEXT("variables"),  Out.VarsTotal,   Out.VarsDoc);
			ReadBucket(TEXT("functions"),  Out.FnsTotal,    Out.FnsDoc);
			ReadBucket(TEXT("components"), Out.CompsTotal,  Out.CompsDoc);
			ReadBucket(TEXT("graphs"),     Out.GraphsTotal, Out.GraphsDoc);

			TSharedPtr<FJsonObject> Spec = JsonObj(Cov, TEXT("specialized"));
			if (Spec.IsValid())
			{
				auto ReadList = [&](const TCHAR* Field, TArray<FString>& Out2)
				{
					if (const auto* Arr = JsonArr(Spec, Field))
					{
						for (const TSharedPtr<FJsonValue>& X : *Arr)
						{
							FString S;
							if (X.IsValid() && X->TryGetString(S)) Out2.Add(S);
						}
					}
				};
				ReadList(TEXT("applicable"), Out.SpecializedApplicable);
				ReadList(TEXT("documented"), Out.SpecializedDocumented);
			}
		}

		// Per-type metrics for domain overviews (M4.1). Reads type-specific
		// top-level fields from the `.meta.json`; absent fields leave
		// counts at zero, which is fine for UBPs (no BT/ST metrics) or
		// non-UBP types (no UBP metrics).
		if (Out.Subclass == TEXT("BehaviorTree"))
		{
			Out.BlackboardPath = JsonStr(Root, TEXT("blackboardPath"));
			if (const auto* Nodes = JsonArr(Root, TEXT("nodes")))
			{
				Out.BTNodeCount = Nodes->Num();
			}
			if (const auto* Keys = JsonArr(Root, TEXT("blackboardKeys")))
			{
				Out.BBKeyCount = Keys->Num();
			}
		}
		else if (Out.Subclass == TEXT("StateTree"))
		{
			Out.STSchema = JsonStr(Root, TEXT("schema"));
			if (const auto* Evals = JsonArr(Root, TEXT("evaluators")))
			{
				Out.STEvaluatorCount = Evals->Num();
			}
			if (const auto* GTs = JsonArr(Root, TEXT("globalTasks")))
			{
				Out.STGlobalTaskCount = GTs->Num();
			}
			// Recursive state count: walk `rootStates` + nested `children`.
			if (const auto* Roots = JsonArr(Root, TEXT("rootStates")))
			{
				TFunction<int32(const TArray<TSharedPtr<FJsonValue>>&)> Count;
				Count = [&Count](const TArray<TSharedPtr<FJsonValue>>& Arr) -> int32
				{
					int32 N = 0;
					for (const TSharedPtr<FJsonValue>& V : Arr)
					{
						const TSharedPtr<FJsonObject>* Obj = nullptr;
						if (V.IsValid() && V->TryGetObject(Obj) && Obj)
						{
							++N;
							const TArray<TSharedPtr<FJsonValue>>* Kids = nullptr;
							if ((*Obj)->TryGetArrayField(TEXT("children"), Kids) && Kids)
							{
								N += Count(*Kids);
							}
						}
					}
					return N;
				};
				Out.STStateCount = Count(*Roots);
			}
		}
		else if (Out.Subclass == TEXT("UserDefinedStruct"))
		{
			if (const auto* Fields = JsonArr(Root, TEXT("fields")))
			{
				Out.UDSFieldCount = Fields->Num();
			}
		}
		else if (Out.Subclass == TEXT("UserDefinedEnum"))
		{
			if (const auto* Values = JsonArr(Root, TEXT("values")))
			{
				Out.UDEValueCount = Values->Num();
			}
		}
		else
		{
			// UBP family — reuse the coverage-bucket totals (authoritative;
			// already parsed above) for the domain-overview complexity columns.
			Out.BPVariableCount = Out.VarsTotal;
			Out.BPFunctionCount = Out.FnsTotal;
			Out.BPComponentCount = Out.CompsTotal;
		}

		return true;
	}

	TArray<FString> FindMetaJsonFiles(const FString& InDir)
	{
		TArray<FString> Out;
		// FindFilesRecursive: path + root + wildcard + bFiles + bDirectories
		TArray<FString> FoundFiles;
		IFileManager::Get().FindFilesRecursive(FoundFiles, *InDir, TEXT("*.meta.json"),
			/*Files=*/true, /*Directories=*/false, /*bClearFileNames=*/true);
		return FoundFiles;
	}

	// --------------------------------------------------------------------
	// Scoreboard (brief §11A)
	// --------------------------------------------------------------------

	struct FScoreboardMetrics
	{
		int32 AssetsIntrospected = 0;
		int32 FailedLoads = 0;
		int32 PartialLoads = 0;
		int32 CoverageUnder100 = 0;
		int32 HealthWarnings = 0;

		TSharedPtr<FJsonObject> ToJson() const
		{
			TSharedPtr<FJsonObject> O = MakeShared<FJsonObject>();
			O->SetNumberField(TEXT("assetsIntrospected"), AssetsIntrospected);
			O->SetNumberField(TEXT("failedLoads"), FailedLoads);
			O->SetNumberField(TEXT("partialLoads"), PartialLoads);
			O->SetNumberField(TEXT("coverageUnder100"), CoverageUnder100);
			O->SetNumberField(TEXT("healthWarnings"), HealthWarnings);
			return O;
		}

		static FScoreboardMetrics FromJson(const TSharedPtr<FJsonObject>& O)
		{
			FScoreboardMetrics M;
			if (!O.IsValid()) return M;
			M.AssetsIntrospected = JsonInt(O, TEXT("assetsIntrospected"));
			M.FailedLoads        = JsonInt(O, TEXT("failedLoads"));
			M.PartialLoads       = JsonInt(O, TEXT("partialLoads"));
			M.CoverageUnder100   = JsonInt(O, TEXT("coverageUnder100"));
			M.HealthWarnings     = JsonInt(O, TEXT("healthWarnings"));
			return M;
		}
	};

	int32 CountTableRows(const FString& Path)
	{
		// Rough count of data rows in a `FAILED_LOADS.md` / `PARTIAL_LOADS.md`.
		// Format is "# Title\nTotal: N\n\n| ... |\n|---|---|\n| ... row ... |\n"
		FString Contents;
		if (!FFileHelper::LoadFileToString(Contents, *Path))
		{
			return 0;
		}
		// Parse the "Total: N" line which ProjectInventoryCommandlet writes — it's
		// authoritative and robust to table formatting changes.
		int32 TotalIdx = Contents.Find(TEXT("Total: "));
		if (TotalIdx == INDEX_NONE)
		{
			return 0;
		}
		FString Rest = Contents.Mid(TotalIdx + 7);
		int32 Newline = INDEX_NONE;
		if (Rest.FindChar(TEXT('\n'), Newline))
		{
			Rest = Rest.Left(Newline);
		}
		return FCString::Atoi(*Rest.TrimStartAndEnd());
	}

	// --------------------------------------------------------------------
	// Renderers
	// --------------------------------------------------------------------

	FString RenderINDEX(
		const TArray<FAggregateAsset>& Assets,
		const TMap<FString, int32>& SubclassCounts,
		const TMap<FString, int32>& FolderCounts,
		const TMap<FString, int32>& HubRefsOut,
		const TMap<FString, int32>& HubRefsIn,
		const FScoreboardMetrics& Baseline,
		const FScoreboardMetrics& LastRun,
		bool bBaselineExistedBeforeRun)
	{
		FString Md;
		Md.Reserve(8 * 1024);
		Md += TEXT("# Project Inventory Index\n\n");
		Md += TEXT("First file to read. Rollup of `.meta.json` sidecars produced by `-run=ProjectInventory` (Phase 1 / brief §4).\n\n");

		// ---- Run Scoreboard (brief §11A) ----
		Md += TEXT("## Run Scoreboard\n\n");
		if (!bBaselineExistedBeforeRun)
		{
			Md += TEXT("_First run against this output directory — baseline seeded from this run, so all deltas are `0`. Subsequent runs will diff against this baseline. Pass `-ResetBaseline` to reseed explicitly._\n\n");
		}
		Md += TEXT("| Metric | Baseline | Last Run | Delta |\n");
		Md += TEXT("|---|---:|---:|---:|\n");

		auto Row = [&Md](const TCHAR* Metric, int32 B, int32 L)
		{
			const int32 Delta = L - B;
			const FString DeltaStr = Delta > 0 ? FString::Printf(TEXT("+%d"), Delta)
				: FString::Printf(TEXT("%d"), Delta);
			Md += FString::Printf(TEXT("| %s | %d | %d | %s |\n"),
				Metric, B, L, *DeltaStr);
		};
		Row(TEXT("Assets introspected"), Baseline.AssetsIntrospected, LastRun.AssetsIntrospected);
		Row(TEXT("Failed loads"),        Baseline.FailedLoads,        LastRun.FailedLoads);
		Row(TEXT("Partial loads"),       Baseline.PartialLoads,       LastRun.PartialLoads);
		Row(TEXT("Coverage <100%"),      Baseline.CoverageUnder100,   LastRun.CoverageUnder100);
		Row(TEXT("HEALTH warnings"),     Baseline.HealthWarnings,     LastRun.HealthWarnings);
		Md += TEXT("\n");

		// ---- Counts by subclass ----
		Md += TEXT("## Counts by Blueprint subclass\n\n");
		if (SubclassCounts.Num() == 0)
		{
			Md += TEXT("_No assets._\n\n");
		}
		else
		{
			TArray<FString> Keys;
			SubclassCounts.GetKeys(Keys);
			Keys.Sort([](const FString& A, const FString& B){ return A.Compare(B, ESearchCase::IgnoreCase) < 0; });
			Md += TEXT("| Subclass | Count |\n|---|---:|\n");
			for (const FString& K : Keys)
			{
				Md += FString::Printf(TEXT("| `%s` | %d |\n"), *K, SubclassCounts[K]);
			}
			Md += TEXT("\n");
		}

		// ---- Counts by folder ----
		Md += TEXT("## Counts by top-level folder\n\n");
		if (FolderCounts.Num() == 0)
		{
			Md += TEXT("_No assets._\n\n");
		}
		else
		{
			TArray<FString> Keys;
			FolderCounts.GetKeys(Keys);
			Keys.Sort([](const FString& A, const FString& B){ return A.Compare(B, ESearchCase::IgnoreCase) < 0; });
			Md += TEXT("| Folder | Assets |\n|---|---:|\n");
			for (const FString& K : Keys)
			{
				Md += FString::Printf(TEXT("| `%s` | %d |\n"), *K, FolderCounts[K]);
			}
			Md += TEXT("\n");
		}

		// ---- Hubs (top 10 by refs_in + refs_out combined) ----
		Md += TEXT("## Largest connection hubs\n\n");
		struct FHub { FString Path; int32 In; int32 Out; };
		TArray<FHub> Hubs;
		TSet<FString> SeenPaths;
		for (const auto& Kv : HubRefsOut) { SeenPaths.Add(Kv.Key); }
		for (const auto& Kv : HubRefsIn)  { SeenPaths.Add(Kv.Key); }
		Hubs.Reserve(SeenPaths.Num());
		for (const FString& P : SeenPaths)
		{
			Hubs.Add({ P, HubRefsIn.FindRef(P), HubRefsOut.FindRef(P) });
		}
		Hubs.Sort([](const FHub& A, const FHub& B)
		{
			const int32 Sa = A.In + A.Out;
			const int32 Sb = B.In + B.Out;
			if (Sa != Sb) return Sa > Sb;
			return A.Path.Compare(B.Path, ESearchCase::IgnoreCase) < 0;
		});
		const int32 Top = FMath::Min(10, Hubs.Num());
		if (Top == 0)
		{
			Md += TEXT("_No references recorded._\n\n");
		}
		else
		{
			Md += TEXT("| Asset | Refs in | Refs out |\n|---|---:|---:|\n");
			for (int32 i = 0; i < Top; ++i)
			{
				Md += FString::Printf(TEXT("| `%s` | %d | %d |\n"),
					*Hubs[i].Path, Hubs[i].In, Hubs[i].Out);
			}
			Md += TEXT("\n");
		}

		// ---- Where to start: routing table from "I want to know X" → rollup ----
		Md += TEXT("## Where to start\n\n");
		Md += TEXT("Pick a question, jump to the right rollup. All rollups are deterministic text files; everything is link-and-read.\n\n");
		Md += TEXT("| Looking for... | Read |\n");
		Md += TEXT("|---|---|\n");
		Md += TEXT("| NPC behavior / AIControllers / BehaviorTrees / StateTrees | [AI_OVERVIEW.md](AI_OVERVIEW.md) |\n");
		Md += TEXT("| Animation Blueprints + state machines + transitions | [ANIM_OVERVIEW.md](ANIM_OVERVIEW.md) |\n");
		Md += TEXT("| UI widget trees (UMG) | [UI_OVERVIEW.md](UI_OVERVIEW.md) |\n");
		Md += TEXT("| GameplayAbility / GAS-derived blueprints | [GAS_OVERVIEW.md](GAS_OVERVIEW.md) |\n");
		Md += TEXT("| UserDefinedStruct / UserDefinedEnum schemas | [STRUCTS_ENUMS.md](STRUCTS_ENUMS.md) |\n");
		Md += TEXT("| Replicated variables + Server/Client/NetMulticast RPCs | [REPLICATION_MATRIX.md](REPLICATION_MATRIX.md) |\n");
		Md += TEXT("| Class inheritance chains (native + BP→BP) | [CLASS_TREE.md](CLASS_TREE.md) |\n");
		Md += TEXT("| Refs in / refs out per asset (+ Graphviz `.dot`) | [DEPENDENCY_GRAPH.md](DEPENDENCY_GRAPH.md) |\n");
		Md += TEXT("| Project plugins + their registered native types | [PLUGINS.md](PLUGINS.md) |\n");
		Md += TEXT("| Coverage gaps + failed loads + partial loads | [HEALTH_REPORT.md](HEALTH_REPORT.md) |\n");
		Md += TEXT("| Full registry scan (incl. non-logic-bearing assets) | [MANIFEST.md](MANIFEST.md) |\n");
		Md += TEXT("\n");
		Md += TEXT("Some rollups are conditional on the source data:\n");
		Md += TEXT("- `GAS_OVERVIEW.md` is written only when GAS-derived assets are detected.\n");
		Md += TEXT("- `PLUGINS.md` + `PluginInventory/` are written by the separate `-run=ProjectPlugins` step.\n");
		Md += TEXT("- `MANIFEST.md` is written by the separate `-run=ProjectManifest` step (Phase 0).\n\n");

		// ---- Per-asset deep dumps: explain the .md / .meta.json / .deep.md trio ----
		Md += TEXT("## Per-asset deep dumps\n\n");
		Md += TEXT("Each Phase-1 asset writes siblings under `Assets/<package>`:\n\n");
		Md += TEXT("| File | What |\n");
		Md += TEXT("|---|---|\n");
		Md += TEXT("| `<Asset>.md` | Tier 1 human-readable summary (variables, function signatures, graph node counts, references). |\n");
		Md += TEXT("| `<Asset>.meta.json` | Tier 1 structured form (full export + coverage block). This rollup reads the JSON, not the `.md`. |\n");
		Md += TEXT("| `<Asset>.deep.md` | Tier 2 full per-node / per-pin / per-task dump _(only when `-DeepDump` was passed)_. |\n");
		Md += TEXT("\n");
		Md += TEXT("Tier 2 coverage:\n\n");
		Md += TEXT("- **UBlueprint family** (`Blueprint`, `AnimBlueprint`, `WidgetBlueprint`, `ControlRigBlueprint`) and **StateTree** get the full `.deep.md`: every node with its pin table, every state with per-task instance data + instance object properties, full property bindings, and **nested instanced-subobject trees** for Instanced / EditInlineNew references (`AIPerception` sense configs, GAS attribute sets, anim layer overrides, etc.).\n");
		Md += TEXT("- **SmartObjectDefinition** gets full per-behavior-definition UPROPERTY tables and per-slot `FInstancedStruct` `DefinitionData` field values — exposes the `StateTreeReference` link from the SO definition to the StateTree that runs the interaction (e.g., `SO_BenchDefinition` → `ST_SmartObject_Bench`), plus entrance annotations (`Offset`, `bIsEntry`, `TrajectorySlotHeightOffset`, `TransitionCheckRadius`, etc.).\n");
		Md += TEXT("- **BehaviorTree** gets a per-node property-table dump — every composite / task / decorator / service in the tree renders its full UPROPERTY values, so the authored configuration (`AcceptableRadius` on a `BTTask_MoveTo`, `FlowAbortMode` on a `BTDecorator_Blackboard`, `Interval` on a `BTService_DefaultFocus`, Blackboard key selectors) is readable without opening the asset.\n");
		Md += TEXT("- **DataTable** gets per-row property tables — Tier 1 captures schema only (row struct, column list, row names), Tier 2 walks every row's `UScriptStruct` fields via `ExportTextItem_Direct` so the actual data (`Damage=15`, `Icon=/Game/UI/…`, `Tier=Common` on a row named `Sword_Iron`) is inline. Rows are alpha-sorted to match the Tier 1 name list positionally.\n");
		Md += TEXT("- **ChooserTable** gets full `FInstancedStruct` field tables per column + row + fallback + context entry — the authored values for each column (which enum a `FEnumColumn` reads, the per-row RowValues arrays, the range on each `FFloatRangeColumn`) and the asset paths / sub-choosers each row points at become inline instead of just type names.\n");
		Md += TEXT("- **EnvQuery** gets per-option generator + per-test UPROPERTY tables — Tier 1 records class + option order, Tier 2 adds the authored values (`Radius` on an `EnvQueryGenerator_SimpleGrid`, `TestPurpose` / `ScoringEquation` / `ClampMin` / `Weight` per test, trace config, tag filters, etc.).\n");
		Md += TEXT("- Other types (`PoseSearchDatabase`, `UserDefinedStruct`, `UserDefinedEnum`) get an out-of-scope `.deep.md` notice pointing back at the Tier 1 typed handler — those handlers already render near-complete shape in `.md`.\n\n");

		// ---- Trust signals: explicit markers, "never guess values" rule ----
		Md += TEXT("## Trust signals\n\n");
		Md += TEXT("Output follows a strict \"never guess values\" rule. When something can't be determined, it's marked, not substituted. Any value not bracketed by these markers is the actual authored value:\n\n");
		Md += TEXT("| Marker | Meaning |\n");
		Md += TEXT("|---|---|\n");
		Md += TEXT("| `[BROKEN]` on a pin type | Serializer couldn't resolve the pin's `SubCategoryObject` weak pointer (typically third-party PostLoad failures). The pin existed but its type is degraded; do not infer it. |\n");
		Md += TEXT("| `[instanced]` on a property type | Property points at one or more Instanced / EditInlineNew subobjects. Their full property tree is rendered as nested sub-sections immediately below the property table. |\n");
		Md += TEXT("| `**Truncated**` in an instanced subtree | Recursion-depth cap reached (`MAX_SUBOBJECT_RECURSION_DEPTH=8`); deeper subobjects exist but weren't walked. |\n");
		Md += TEXT("| `**Cycle detected**` in an instanced subtree | Subobject reference cycle; tree truncated to avoid infinite recursion. |\n");
		Md += TEXT("| `**Broken reference**` in an instanced subtree | Instanced slot existed but the referenced object was null at export time. |\n");
		Md += TEXT("| `(unresolved)` on a transition | StateTree transition target couldn't be resolved (rare; should not appear for any standard `Succeeded`/`Failed`/`NextState`/`GotoState` transition). |\n");
		Md += TEXT("| `(?)` in a pin connection | Cross-graph node title couldn't be resolved (cosmetic; observed only on identical sub-graph hash collisions in third-party rigs). |\n");
		Md += TEXT("| `_None_` / `_Empty graph._` | Genuinely empty container — not a serialization failure. |\n");
		Md += TEXT("\n");

		return Md;
	}

	FString RenderCLASS_TREE(const TArray<FAggregateAsset>& Assets)
	{
		FString Md;
		Md.Reserve(8 * 1024);
		Md += TEXT("# Class Tree\n\n");
		Md += TEXT("Inheritance rollup across every Phase-1 Blueprint. Native parents group their direct Blueprint children; BP→BP chains are listed separately.\n\n");

		// Group assets by *native* parent class path.
		TMap<FString, TArray<const FAggregateAsset*>> NativeParentToKids;
		TArray<const FAggregateAsset*> BPParentedAssets;
		TMap<FString, const FAggregateAsset*> AssetByPackage;
		for (const FAggregateAsset& A : Assets)
		{
			AssetByPackage.Add(A.PackageName, &A);
		}
		for (const FAggregateAsset& A : Assets)
		{
			if (A.bParentIsNative)
			{
				NativeParentToKids.FindOrAdd(A.ParentClassPath).Add(&A);
			}
			else
			{
				BPParentedAssets.Add(&A);
			}
		}

		Md += TEXT("## By native parent\n\n");
		if (NativeParentToKids.Num() == 0)
		{
			Md += TEXT("_No native-parented Blueprints recorded._\n\n");
		}
		else
		{
			TArray<FString> NativeKeys;
			NativeParentToKids.GetKeys(NativeKeys);
			NativeKeys.Sort([](const FString& A, const FString& B){ return A.Compare(B, ESearchCase::IgnoreCase) < 0; });
			for (const FString& NativeKey : NativeKeys)
			{
				TArray<const FAggregateAsset*>& Kids = NativeParentToKids[NativeKey];
				Kids.Sort([](const FAggregateAsset& A, const FAggregateAsset& B)
				{
					return A.PackageName.Compare(B.PackageName, ESearchCase::IgnoreCase) < 0;
				});
				Md += FString::Printf(TEXT("- `%s` [%d]\n"), *NativeKey, Kids.Num());
				for (const FAggregateAsset* K : Kids)
				{
					Md += FString::Printf(TEXT("  - `%s`\n"), *K->PackageName);
				}
			}
			Md += TEXT("\n");
		}

		Md += TEXT("## Blueprint → Blueprint chains\n\n");
		if (BPParentedAssets.Num() == 0)
		{
			Md += TEXT("_No BP-to-BP inheritance recorded._\n\n");
		}
		else
		{
			// Render each BP-parented asset as `Child < Parent` for a flat, line-per-
			// chain summary. Full trees are easier to reason about once DOW is mapped.
			TArray<const FAggregateAsset*> Sorted = BPParentedAssets;
			Sorted.Sort([](const FAggregateAsset& A, const FAggregateAsset& B)
			{
				return A.PackageName.Compare(B.PackageName, ESearchCase::IgnoreCase) < 0;
			});
			for (const FAggregateAsset* A : Sorted)
			{
				Md += FString::Printf(TEXT("- `%s` < `%s`\n"), *A->PackageName, *A->ParentClassPath);
			}
			Md += TEXT("\n");
		}

		return Md;
	}

	struct FDependencyGraphResult { FString Md; FString Dot; };

	FDependencyGraphResult RenderDEPENDENCY_GRAPH(
		const TArray<FAggregateAsset>& Assets,
		const TMap<FString, TArray<FString>>& RefsInByPath)
	{
		FDependencyGraphResult R;
		R.Md.Reserve(16 * 1024);
		R.Dot.Reserve(8 * 1024);

		R.Md += TEXT("# Dependency Graph\n\n");
		R.Md += TEXT("Per-asset hard/soft references out, plus reverse-index refs in. See `dependency_graph.dot` for the Graphviz version.\n\n");

		TArray<FAggregateAsset> Sorted = Assets;
		Sorted.Sort([](const FAggregateAsset& A, const FAggregateAsset& B)
		{
			return A.PackageName.Compare(B.PackageName, ESearchCase::IgnoreCase) < 0;
		});

		for (const FAggregateAsset& A : Sorted)
		{
			R.Md += FString::Printf(TEXT("## `%s`\n\n"), *A.PackageName);

			auto EmitRefs = [&R](const TCHAR* Label, TArray<FAggregateDepRef> Refs)
			{
				Refs.Sort([](const FAggregateDepRef& X, const FAggregateDepRef& Y)
				{
					return X.AssetPath.Compare(Y.AssetPath, ESearchCase::IgnoreCase) < 0;
				});
				R.Md += FString::Printf(TEXT("- %s (%d):\n"), Label, Refs.Num());
				if (Refs.Num() == 0)
				{
					R.Md += TEXT("  - _none_\n");
					return;
				}
				for (const FAggregateDepRef& D : Refs)
				{
					const FString Kind = D.bIsBlueprint ? TEXT("Blueprint")
						: (D.bIsNativeClass ? TEXT("native") : TEXT("asset"));
					R.Md += FString::Printf(TEXT("  - `%s` [%s]\n"), *D.AssetPath, *Kind);
				}
			};
			EmitRefs(TEXT("Hard refs out"), A.HardRefsOut);
			EmitRefs(TEXT("Soft refs out"), A.SoftRefsOut);

			// Hard refs in (reverse index)
			TArray<FString> In = RefsInByPath.FindRef(A.PackageName);
			// Also consider refs whose target is the full AssetPath form
			for (const FString& AltKey : TArray<FString>{ A.AssetPath })
			{
				if (const TArray<FString>* More = RefsInByPath.Find(AltKey))
				{
					for (const FString& P : *More) In.AddUnique(P);
				}
			}
			In.Sort([](const FString& X, const FString& Y){ return X.Compare(Y, ESearchCase::IgnoreCase) < 0; });
			R.Md += FString::Printf(TEXT("- Hard refs in (%d):\n"), In.Num());
			if (In.Num() == 0)
			{
				R.Md += TEXT("  - _none_\n");
			}
			else
			{
				for (const FString& P : In)
				{
					R.Md += FString::Printf(TEXT("  - `%s`\n"), *P);
				}
			}
			R.Md += TEXT("\n");
		}

		// DOT graph
		R.Dot += TEXT("// Generated by AggregateInventoryCommandlet (M4). Hard edges only.\n");
		R.Dot += TEXT("digraph ProjectInventory {\n");
		R.Dot += TEXT("  rankdir=LR;\n");
		R.Dot += TEXT("  node [shape=box, fontname=\"Helvetica\", fontsize=10];\n");
		R.Dot += TEXT("  edge [arrowsize=0.6];\n");
		for (const FAggregateAsset& A : Sorted)
		{
			TArray<FAggregateDepRef> H = A.HardRefsOut;
			H.Sort([](const FAggregateDepRef& X, const FAggregateDepRef& Y)
			{
				return X.AssetPath.Compare(Y.AssetPath, ESearchCase::IgnoreCase) < 0;
			});
			for (const FAggregateDepRef& D : H)
			{
				R.Dot += FString::Printf(TEXT("  \"%s\" -> \"%s\";\n"),
					*A.PackageName, *D.AssetPath);
			}
		}
		R.Dot += TEXT("}\n");

		return R;
	}

	FString RenderREPLICATION_MATRIX(const TArray<FAggregateAsset>& Assets)
	{
		FString Md;
		Md.Reserve(4 * 1024);
		Md += TEXT("# Replication Matrix\n\n");
		Md += TEXT("Every replicated member across the Phase-1 scope. The single most valuable document for the Steam Relay playtest workstream (brief §5).\n\n");
		Md += TEXT("Kinds: `Var` (UPROPERTY(Replicated)/RepNotify), `RPC` (functions with Server/Client/NetMulticast + optional Reliable flags). RPC rows are sourced from M3.2's net-exec flag extension on `FExportedFunctionFlags`.\n\n");

		struct FRow { FString Asset; FString Member; FString Kind; FString Repl; FString Cond; FString Notes; };
		TArray<FRow> Rows;
		int32 VarCount = 0;
		int32 RpcCount = 0;
		for (const FAggregateAsset& A : Assets)
		{
			for (const FReplicatedVar& R : A.ReplicatedVars)
			{
				FRow Row;
				Row.Asset  = A.PackageName;
				Row.Member = R.Name;
				Row.Kind   = TEXT("Var");
				Row.Repl   = FString::Printf(TEXT("Replicated (%s)"), *R.Type);
				Row.Cond   = R.Condition.IsEmpty() ? TEXT("—") : R.Condition;
				Row.Notes  = R.RepNotifyFunc.IsEmpty()
					? FString(TEXT("—"))
					: FString::Printf(TEXT("RepNotify: `%s`"), *R.RepNotifyFunc);
				Rows.Add(MoveTemp(Row));
				++VarCount;
			}
			for (const FRpcFunc& Rpc : A.RpcFunctions)
			{
				FRow Row;
				Row.Asset  = A.PackageName;
				Row.Member = Rpc.Signature.IsEmpty()
					? Rpc.Name
					: FString::Printf(TEXT("%s%s"), *Rpc.Name, *Rpc.Signature);
				Row.Kind   = TEXT("RPC");
				Row.Repl   = Rpc.Direction;
				Row.Cond   = Rpc.bReliable ? TEXT("Reliable") : TEXT("Unreliable");
				TArray<FString> NoteBits;
				if (Rpc.bAuthorityOnly) NoteBits.Add(TEXT("BlueprintAuthorityOnly"));
				if (Rpc.bCosmetic)      NoteBits.Add(TEXT("BlueprintCosmetic"));
				Row.Notes = NoteBits.Num() == 0 ? FString(TEXT("—")) : FString::Join(NoteBits, TEXT(", "));
				Rows.Add(MoveTemp(Row));
				++RpcCount;
			}
		}
		Rows.Sort([](const FRow& A, const FRow& B)
		{
			const int32 AssetCmp = A.Asset.Compare(B.Asset, ESearchCase::IgnoreCase);
			if (AssetCmp != 0) return AssetCmp < 0;
			// Group Vars before RPCs within each asset for readability.
			if (A.Kind != B.Kind) return A.Kind.Compare(B.Kind, ESearchCase::IgnoreCase) < 0;
			return A.Member.Compare(B.Member, ESearchCase::IgnoreCase) < 0;
		});

		Md += FString::Printf(TEXT("Total rows: **%d** (vars: %d, RPCs: %d)\n\n"),
			Rows.Num(), VarCount, RpcCount);
		if (Rows.Num() == 0)
		{
			Md += TEXT("_No replicated members or RPCs found in the Phase-1 scope._\n");
			return Md;
		}
		Md += TEXT("| Asset | Member | Kind | Replication | Condition | Notes |\n");
		Md += TEXT("|---|---|---|---|---|---|\n");
		for (const FRow& R : Rows)
		{
			Md += FString::Printf(TEXT("| `%s` | `%s` | %s | %s | %s | %s |\n"),
				*EscTbl(R.Asset), *EscTbl(R.Member),
				*R.Kind, *EscTbl(R.Repl), *EscTbl(R.Cond), *EscTbl(R.Notes));
		}
		Md += TEXT("\n");
		return Md;
	}

	FString RenderHEALTH_REPORT(
		const TArray<FAggregateAsset>& Assets,
		int32 FailedLoads,
		int32 PartialLoads)
	{
		FString Md;
		Md.Reserve(4 * 1024);
		Md += TEXT("# Health Report\n\n");
		Md += TEXT("Coverage gaps and load failures across the Phase-1 scope.\n\n");

		Md += TEXT("## Totals\n\n");
		Md += FString::Printf(TEXT("- Failed loads: **%d** (see `FAILED_LOADS.md` if non-zero)\n"), FailedLoads);
		Md += FString::Printf(TEXT("- Partial loads: **%d** (see `PARTIAL_LOADS.md` if non-zero)\n"), PartialLoads);

		TArray<const FAggregateAsset*> Under100;
		for (const FAggregateAsset& A : Assets)
		{
			if (A.OverallCoveragePct < 100)
			{
				Under100.Add(&A);
			}
		}
		Md += FString::Printf(TEXT("- Assets with coverage < 100%%: **%d**\n\n"), Under100.Num());

		if (Under100.Num() == 0)
		{
			Md += TEXT("_All introspected assets are at 100%% coverage for the first-slice render set._\n");
			return Md;
		}
		Under100.Sort([](const FAggregateAsset& A, const FAggregateAsset& B)
		{
			if (A.OverallCoveragePct != B.OverallCoveragePct)
			{
				return A.OverallCoveragePct < B.OverallCoveragePct;
			}
			return A.PackageName.Compare(B.PackageName, ESearchCase::IgnoreCase) < 0;
		});

		Md += TEXT("## Coverage < 100%\n\n");
		Md += TEXT("| Asset | Subclass | Overall | Missing |\n");
		Md += TEXT("|---|---|---:|---|\n");
		for (const FAggregateAsset* A : Under100)
		{
			TArray<FString> Missing;
			if (A->VarsTotal > A->VarsDoc)       Missing.Add(FString::Printf(TEXT("variables %d/%d"), A->VarsDoc, A->VarsTotal));
			if (A->FnsTotal > A->FnsDoc)         Missing.Add(FString::Printf(TEXT("functions %d/%d"), A->FnsDoc, A->FnsTotal));
			if (A->CompsTotal > A->CompsDoc)     Missing.Add(FString::Printf(TEXT("components %d/%d"), A->CompsDoc, A->CompsTotal));
			if (A->GraphsTotal > A->GraphsDoc)   Missing.Add(FString::Printf(TEXT("graphs %d/%d"), A->GraphsDoc, A->GraphsTotal));
			TArray<FString> UndocumentedSpec;
			for (const FString& S : A->SpecializedApplicable)
			{
				if (!A->SpecializedDocumented.Contains(S)) UndocumentedSpec.Add(S);
			}
			for (const FString& S : UndocumentedSpec)
			{
				Missing.Add(FString::Printf(TEXT("specialized `%s`"), *S));
			}
			const FString MissingStr = Missing.Num() == 0 ? TEXT("—") : FString::Join(Missing, TEXT("; "));
			Md += FString::Printf(TEXT("| `%s` | `%s` | %d%% | %s |\n"),
				*EscTbl(A->PackageName), *A->Subclass, A->OverallCoveragePct, *EscTbl(MissingStr));
		}
		Md += TEXT("\n");
		return Md;
	}

	// ====================================================================
	// M4.1 domain overviews. All pure text-over-JSON; deterministic by
	// construction (same sort rules as other renderers). Each overview is
	// written unconditionally except GAS (conditional on detection).
	// ====================================================================

	// Find assets whose HardRefsOut targets include `TargetPackage` or `TargetAssetPath`.
	// Uses the reverse index already built in Main to avoid O(N²) rescans.
	TArray<FString> FindRefsIn(
		const TMap<FString, TArray<FString>>& RefsInByPath,
		const FString& TargetPackage,
		const FString& TargetAssetPath)
	{
		TArray<FString> Out;
		if (const TArray<FString>* A = RefsInByPath.Find(TargetPackage)) Out.Append(*A);
		if (TargetAssetPath != TargetPackage)
		{
			if (const TArray<FString>* B = RefsInByPath.Find(TargetAssetPath))
			{
				for (const FString& P : *B) Out.AddUnique(P);
			}
		}
		Out.Sort([](const FString& A, const FString& B){ return A.Compare(B, ESearchCase::IgnoreCase) < 0; });
		return Out;
	}

	bool IsAIControllerParent(const FString& ParentClassPath)
	{
		// Direct-parent detection only; BP-to-BP inheritance chains to an
		// AIController ancestor get picked up separately by CLASS_TREE.
		return ParentClassPath == TEXT("/Script/AIModule.AIController")
			|| ParentClassPath.StartsWith(TEXT("/Script/AIModule.AIController"));
	}

	bool IsGameplayAbilityParent(const FString& ParentClassPath)
	{
		return ParentClassPath.StartsWith(TEXT("/Script/GameplayAbilities.GameplayAbility"));
	}

	bool IsGameplayEffectParent(const FString& ParentClassPath)
	{
		return ParentClassPath.StartsWith(TEXT("/Script/GameplayAbilities.GameplayEffect"));
	}

	bool IsAttributeSetParent(const FString& ParentClassPath)
	{
		return ParentClassPath.StartsWith(TEXT("/Script/GameplayAbilities.AttributeSet"));
	}

	FString RenderAI_OVERVIEW(
		const TArray<FAggregateAsset>& Assets,
		const TMap<FString, TArray<FString>>& RefsInByPath)
	{
		TArray<const FAggregateAsset*> BTs, STs, AIControllers;
		for (const FAggregateAsset& A : Assets)
		{
			if (A.Subclass == TEXT("BehaviorTree"))      BTs.Add(&A);
			else if (A.Subclass == TEXT("StateTree"))    STs.Add(&A);
			else if (IsAIControllerParent(A.ParentClassPath)) AIControllers.Add(&A);
		}
		auto SortByPkg = [](const FAggregateAsset& A, const FAggregateAsset& B)
		{
			return A.PackageName.Compare(B.PackageName, ESearchCase::IgnoreCase) < 0;
		};
		BTs.Sort(SortByPkg);
		STs.Sort(SortByPkg);
		AIControllers.Sort(SortByPkg);

		FString Md;
		Md.Reserve(4 * 1024);
		Md += TEXT("# AI Overview\n\n");
		Md += TEXT("Every BehaviorTree, StateTree, and AIController-derived Blueprint in the Phase-1 scope. Cross-references the NPCs that hard-reference each AI asset.\n\n");

		// ---- BehaviorTrees ----
		Md += FString::Printf(TEXT("## BehaviorTrees (%d)\n\n"), BTs.Num());
		if (BTs.Num() == 0)
		{
			Md += TEXT("_None in scope._\n\n");
		}
		else
		{
			Md += TEXT("| Asset | Nodes | Blackboard | Keys | Referenced by |\n|---|---:|---|---:|---|\n");
			for (const FAggregateAsset* A : BTs)
			{
				TArray<FString> RefsIn = FindRefsIn(RefsInByPath, A->PackageName, A->AssetPath);
				const FString RefsInStr = RefsIn.Num() == 0
					? FString(TEXT("_none_"))
					: FString::Printf(TEXT("%d: %s"), RefsIn.Num(), *FString::Join(RefsIn, TEXT(", ")));
				const FString BBStr = A->BlackboardPath.IsEmpty()
					? FString(TEXT("—"))
					: FString::Printf(TEXT("`%s`"), *EscTbl(A->BlackboardPath));
				Md += FString::Printf(TEXT("| `%s` | %d | %s | %d | %s |\n"),
					*EscTbl(A->PackageName), A->BTNodeCount, *BBStr, A->BBKeyCount,
					*EscTbl(RefsInStr));
			}
			Md += TEXT("\n");
		}

		// ---- StateTrees ----
		Md += FString::Printf(TEXT("## StateTrees (%d)\n\n"), STs.Num());
		if (STs.Num() == 0)
		{
			Md += TEXT("_None successfully introspected in scope._\n\n");
		}
		else
		{
			Md += TEXT("| Asset | Schema | States | Evaluators | Global tasks | Referenced by |\n|---|---|---:|---:|---:|---|\n");
			for (const FAggregateAsset* A : STs)
			{
				TArray<FString> RefsIn = FindRefsIn(RefsInByPath, A->PackageName, A->AssetPath);
				const FString RefsInStr = RefsIn.Num() == 0
					? FString(TEXT("_none_"))
					: FString::Printf(TEXT("%d: %s"), RefsIn.Num(), *FString::Join(RefsIn, TEXT(", ")));
				Md += FString::Printf(TEXT("| `%s` | `%s` | %d | %d | %d | %s |\n"),
					*EscTbl(A->PackageName),
					A->STSchema.IsEmpty() ? TEXT("—") : *EscTbl(A->STSchema),
					A->STStateCount, A->STEvaluatorCount, A->STGlobalTaskCount,
					*EscTbl(RefsInStr));
			}
			Md += TEXT("\n");
		}

		// ---- AIController-derived BPs ----
		Md += FString::Printf(TEXT("## AIController-derived Blueprints (%d)\n\n"), AIControllers.Num());
		if (AIControllers.Num() == 0)
		{
			Md += TEXT("_None in scope._\n\n");
		}
		else
		{
			Md += TEXT("| Asset | Parent | BT / ST referenced |\n|---|---|---|\n");
			for (const FAggregateAsset* A : AIControllers)
			{
				// Look for hard refs to any BT or ST we know about.
				TSet<FString> AIPkgs;
				for (const FAggregateAsset* B : BTs) AIPkgs.Add(B->PackageName);
				for (const FAggregateAsset* S : STs) AIPkgs.Add(S->PackageName);
				TArray<FString> Matched;
				for (const FAggregateDepRef& D : A->HardRefsOut)
				{
					const FString DepPkg = PackageNameFromAssetPath(D.AssetPath);
					if (AIPkgs.Contains(DepPkg)) Matched.AddUnique(DepPkg);
				}
				Matched.Sort([](const FString& X, const FString& Y){ return X.Compare(Y, ESearchCase::IgnoreCase) < 0; });
				const FString MatchedStr = Matched.Num() == 0 ? FString(TEXT("—")) : FString::Join(Matched, TEXT(", "));
				Md += FString::Printf(TEXT("| `%s` | `%s` | %s |\n"),
					*EscTbl(A->PackageName), *EscTbl(A->ParentClassPath), *EscTbl(MatchedStr));
			}
			Md += TEXT("\n");
		}

		Md += TEXT("_EQS queries (`EnvQuery` assets) land in Phase 1 as of M3.2 — see individual `.md` pages for option/test detail. SmartObjectDefinition, BehaviorTree, and EnvQuery assets each ship full Tier 2 deep dumps (see their `.deep.md` pages) as of M11–M15; a dedicated rollup would duplicate that content without adding cross-asset signal._\n");
		return Md;
	}

	FString RenderANIM_OVERVIEW(const TArray<FAggregateAsset>& Assets)
	{
		TArray<const FAggregateAsset*> AnimBPs;
		for (const FAggregateAsset& A : Assets)
		{
			if (A.Subclass == TEXT("AnimBlueprint")) AnimBPs.Add(&A);
		}
		AnimBPs.Sort([](const FAggregateAsset& A, const FAggregateAsset& B)
		{
			return A.PackageName.Compare(B.PackageName, ESearchCase::IgnoreCase) < 0;
		});

		FString Md;
		Md.Reserve(2 * 1024);
		Md += TEXT("# Animation Overview\n\n");
		Md += TEXT("Every AnimBlueprint in the Phase-1 scope. Motion Matching / Chooser Table / state-machine-complexity detail depends on the M3.2 serializer widening and is not yet surfaced.\n\n");

		Md += FString::Printf(TEXT("## AnimBlueprints (%d)\n\n"), AnimBPs.Num());
		if (AnimBPs.Num() == 0)
		{
			Md += TEXT("_None in scope (BugHunt fixture corpus has no AnimBPs; DOW will populate this overview)._\n");
			return Md;
		}
		Md += TEXT("| Asset | Parent | Variables | Functions | Components |\n|---|---|---:|---:|---:|\n");
		for (const FAggregateAsset* A : AnimBPs)
		{
			Md += FString::Printf(TEXT("| `%s` | `%s` | %d | %d | %d |\n"),
				*EscTbl(A->PackageName), *EscTbl(A->ParentClassPath),
				A->BPVariableCount, A->BPFunctionCount, A->BPComponentCount);
		}
		Md += TEXT("\n");
		return Md;
	}

	FString RenderUI_OVERVIEW(
		const TArray<FAggregateAsset>& Assets,
		const TMap<FString, TArray<FString>>& RefsInByPath)
	{
		TArray<const FAggregateAsset*> Widgets;
		for (const FAggregateAsset& A : Assets)
		{
			if (A.Subclass == TEXT("WidgetBlueprint")) Widgets.Add(&A);
		}
		Widgets.Sort([](const FAggregateAsset& A, const FAggregateAsset& B)
		{
			return A.PackageName.Compare(B.PackageName, ESearchCase::IgnoreCase) < 0;
		});

		FString Md;
		Md.Reserve(2 * 1024);
		Md += TEXT("# UI Overview\n\n");
		Md += TEXT("Every WidgetBlueprint in the Phase-1 scope. Widget-tree structure + binding density depend on the M3.2 widget-tree serializer and are not yet surfaced.\n\n");

		Md += FString::Printf(TEXT("## WidgetBlueprints (%d)\n\n"), Widgets.Num());
		if (Widgets.Num() == 0)
		{
			Md += TEXT("_None in scope._\n");
			return Md;
		}
		Md += TEXT("| Asset | Parent | Variables | Functions | Nested refs in |\n|---|---|---:|---:|---:|\n");
		for (const FAggregateAsset* A : Widgets)
		{
			TArray<FString> RefsIn = FindRefsIn(RefsInByPath, A->PackageName, A->AssetPath);
			Md += FString::Printf(TEXT("| `%s` | `%s` | %d | %d | %d |\n"),
				*EscTbl(A->PackageName), *EscTbl(A->ParentClassPath),
				A->BPVariableCount, A->BPFunctionCount, RefsIn.Num());
		}
		Md += TEXT("\n");
		return Md;
	}

	// Returns empty string when no GAS assets are detected — caller treats
	// empty as "skip write" so the overview doesn't spam projects without GAS.
	FString RenderGAS_OVERVIEW(const TArray<FAggregateAsset>& Assets)
	{
		TArray<const FAggregateAsset*> Abilities, Effects, AttrSets;
		for (const FAggregateAsset& A : Assets)
		{
			if (IsGameplayAbilityParent(A.ParentClassPath)) Abilities.Add(&A);
			else if (IsGameplayEffectParent(A.ParentClassPath)) Effects.Add(&A);
			else if (IsAttributeSetParent(A.ParentClassPath)) AttrSets.Add(&A);
		}
		if (Abilities.Num() + Effects.Num() + AttrSets.Num() == 0)
		{
			return FString();  // no GAS detected → caller skips write
		}
		auto SortByPkg = [](const FAggregateAsset& A, const FAggregateAsset& B)
		{
			return A.PackageName.Compare(B.PackageName, ESearchCase::IgnoreCase) < 0;
		};
		Abilities.Sort(SortByPkg);
		Effects.Sort(SortByPkg);
		AttrSets.Sort(SortByPkg);

		FString Md;
		Md.Reserve(2 * 1024);
		Md += TEXT("# GAS Overview\n\n");
		Md += TEXT("GameplayAbility / GameplayEffect / AttributeSet-derived Blueprints in the Phase-1 scope. Generated only when at least one such asset is detected.\n\n");

		auto EmitSection = [&Md](const TCHAR* Title, const TArray<const FAggregateAsset*>& Set)
		{
			Md += FString::Printf(TEXT("## %s (%d)\n\n"), Title, Set.Num());
			if (Set.Num() == 0)
			{
				Md += TEXT("_None in scope._\n\n");
				return;
			}
			Md += TEXT("| Asset | Parent | Variables | Functions |\n|---|---|---:|---:|\n");
			for (const FAggregateAsset* A : Set)
			{
				Md += FString::Printf(TEXT("| `%s` | `%s` | %d | %d |\n"),
					*EscTbl(A->PackageName), *EscTbl(A->ParentClassPath),
					A->BPVariableCount, A->BPFunctionCount);
			}
			Md += TEXT("\n");
		};
		EmitSection(TEXT("GameplayAbility-derived"), Abilities);
		EmitSection(TEXT("GameplayEffect-derived"), Effects);
		EmitSection(TEXT("AttributeSet-derived"), AttrSets);

		Md += TEXT("_Granted / blocked / required tag containers, cost / cooldown refs, and per-ability net-exec policy land after the M3.2 serializer widening._\n");
		return Md;
	}

	FString RenderSTRUCTS_ENUMS(
		const TArray<FAggregateAsset>& Assets,
		const TMap<FString, TArray<FString>>& RefsInByPath)
	{
		TArray<const FAggregateAsset*> Structs, Enums;
		for (const FAggregateAsset& A : Assets)
		{
			if (A.Subclass == TEXT("UserDefinedStruct")) Structs.Add(&A);
			else if (A.Subclass == TEXT("UserDefinedEnum")) Enums.Add(&A);
		}
		auto SortByPkg = [](const FAggregateAsset& A, const FAggregateAsset& B)
		{
			return A.PackageName.Compare(B.PackageName, ESearchCase::IgnoreCase) < 0;
		};
		Structs.Sort(SortByPkg);
		Enums.Sort(SortByPkg);

		FString Md;
		Md.Reserve(2 * 1024);
		Md += TEXT("# User-Defined Structs & Enums\n\n");
		Md += TEXT("Every project-authored struct and enum, with reference-in counts so you can see what relies on each.\n\n");

		Md += FString::Printf(TEXT("## Structs (%d)\n\n"), Structs.Num());
		if (Structs.Num() == 0)
		{
			Md += TEXT("_None in scope._\n\n");
		}
		else
		{
			Md += TEXT("| Asset | Fields | Referenced by |\n|---|---:|---:|\n");
			for (const FAggregateAsset* A : Structs)
			{
				TArray<FString> RefsIn = FindRefsIn(RefsInByPath, A->PackageName, A->AssetPath);
				Md += FString::Printf(TEXT("| `%s` | %d | %d |\n"),
					*EscTbl(A->PackageName), A->UDSFieldCount, RefsIn.Num());
			}
			Md += TEXT("\n");
		}

		Md += FString::Printf(TEXT("## Enums (%d)\n\n"), Enums.Num());
		if (Enums.Num() == 0)
		{
			Md += TEXT("_None in scope._\n\n");
		}
		else
		{
			Md += TEXT("| Asset | Values | Referenced by |\n|---|---:|---:|\n");
			for (const FAggregateAsset* A : Enums)
			{
				TArray<FString> RefsIn = FindRefsIn(RefsInByPath, A->PackageName, A->AssetPath);
				Md += FString::Printf(TEXT("| `%s` | %d | %d |\n"),
					*EscTbl(A->PackageName), A->UDEValueCount, RefsIn.Num());
			}
			Md += TEXT("\n");
		}

		Md += TEXT("_Per-struct field types and per-enum values are in the Tier 1 `.md` / `.meta.json` sidecars for each asset._\n");
		return Md;
	}
}

UAggregateInventoryCommandlet::UAggregateInventoryCommandlet()
{
	IsClient = false;
	IsEditor = true;
	IsServer = false;
	LogToConsole = true;
}

int32 UAggregateInventoryCommandlet::Main(const FString& Params)
{
	LogLine(TEXT("INFO"), TEXT("Aggregate Inventory Commandlet starting"));

	FString OutDir;
	if (!FParse::Value(*Params, TEXT("OutDir="), OutDir))
	{
		LogLine(TEXT("ERROR"),
			TEXT("Usage: -run=AggregateInventory -OutDir=<dir> [-InDir=<dir>] [-ResetBaseline]"),
			/*bIsError=*/true);
		return 2;
	}
	OutDir.TrimQuotesInline();

	FString InDir;
	FParse::Value(*Params, TEXT("InDir="), InDir);
	InDir.TrimQuotesInline();
	if (InDir.IsEmpty())
	{
		InDir = FPaths::Combine(OutDir, TEXT("Assets"));
	}

	const bool bResetBaseline = FParse::Param(*Params, TEXT("ResetBaseline"));

	LogLine(TEXT("INFO"),
		FString::Printf(TEXT("OutDir=%s InDir=%s ResetBaseline=%s"),
			*OutDir, *InDir, bResetBaseline ? TEXT("yes") : TEXT("no")));

	if (!IFileManager::Get().DirectoryExists(*InDir))
	{
		LogLine(TEXT("ERROR"), FString::Printf(TEXT("InDir does not exist: %s"), *InDir), /*bIsError=*/true);
		return 2;
	}
	if (!IFileManager::Get().DirectoryExists(*OutDir))
	{
		IFileManager::Get().MakeDirectory(*OutDir, /*Tree=*/true);
	}

	// ---- Discover .meta.json files ----
	const TArray<FString> MetaFiles = FindMetaJsonFiles(InDir);
	LogLine(TEXT("INFO"), FString::Printf(TEXT("Found %d .meta.json files under %s"), MetaFiles.Num(), *InDir));
	if (MetaFiles.Num() == 0)
	{
		LogLine(TEXT("ERROR"),
			TEXT("No .meta.json files found — run ProjectInventoryCommandlet first."),
			/*bIsError=*/true);
		return 2;
	}

	// ---- Parse each .meta.json ----
	TArray<FAggregateAsset> Assets;
	Assets.Reserve(MetaFiles.Num());
	int32 ParseFailures = 0;
	for (const FString& Path : MetaFiles)
	{
		FAggregateAsset Asset;
		if (ParseMetaJsonFile(Path, Asset))
		{
			Assets.Add(MoveTemp(Asset));
		}
		else
		{
			++ParseFailures;
			LogLine(TEXT("PARTIAL"),
				FString::Printf(TEXT("Failed to parse .meta.json: %s"), *Path),
				/*bIsError=*/true);
		}
	}
	LogLine(TEXT("INFO"),
		FString::Printf(TEXT("Parsed %d assets (%d parse failures)"), Assets.Num(), ParseFailures));

	// ---- Build aggregate indexes ----
	TMap<FString, int32> SubclassCounts;
	TMap<FString, int32> FolderCounts;
	TMap<FString, TArray<FString>> RefsInByTargetPath;  // target asset path -> [referring package names]
	TMap<FString, int32> HubRefsOut;  // package -> count
	TMap<FString, int32> HubRefsIn;   // package -> count (keyed by PackageName where possible)
	int32 CoverageUnder100 = 0;

	for (const FAggregateAsset& A : Assets)
	{
		if (!A.Subclass.IsEmpty()) ++SubclassCounts.FindOrAdd(A.Subclass);
		const FString Folder = TopLevelFolderOf(A.PackageName);
		++FolderCounts.FindOrAdd(Folder);
		if (A.OverallCoveragePct < 100) ++CoverageUnder100;

		const int32 HardOutCount = A.HardRefsOut.Num();
		if (HardOutCount > 0) HubRefsOut.Add(A.PackageName, HardOutCount);

		for (const FAggregateDepRef& D : A.HardRefsOut)
		{
			RefsInByTargetPath.FindOrAdd(D.AssetPath).AddUnique(A.PackageName);
			// Also add package-name form in case downstream consumers key by it.
			const FString DepPkg = PackageNameFromAssetPath(D.AssetPath);
			if (DepPkg != D.AssetPath)
			{
				RefsInByTargetPath.FindOrAdd(DepPkg).AddUnique(A.PackageName);
			}
		}
	}
	// Back-fill HubRefsIn from RefsInByTargetPath restricted to known assets.
	for (const FAggregateAsset& A : Assets)
	{
		if (const TArray<FString>* R = RefsInByTargetPath.Find(A.PackageName))
		{
			HubRefsIn.Add(A.PackageName, R->Num());
		}
	}

	// ---- Scoreboard metrics ----
	FScoreboardMetrics LastRun;
	LastRun.AssetsIntrospected = Assets.Num();
	LastRun.FailedLoads  = CountTableRows(FPaths::Combine(OutDir, TEXT("FAILED_LOADS.md")));
	LastRun.PartialLoads = CountTableRows(FPaths::Combine(OutDir, TEXT("PARTIAL_LOADS.md")));
	LastRun.CoverageUnder100 = CoverageUnder100;
	LastRun.HealthWarnings = CoverageUnder100 + LastRun.FailedLoads + LastRun.PartialLoads;

	// ---- Baseline load / seed ----
	const FString BaselinePath = FPaths::Combine(OutDir, TEXT("SCOREBOARD_BASELINE.json"));
	FScoreboardMetrics Baseline = LastRun;  // default: baseline == this run (first run or reset)
	bool bBaselineExistedBeforeRun = false;

	if (!bResetBaseline && IFileManager::Get().FileExists(*BaselinePath))
	{
		FString BaselineJson;
		if (FFileHelper::LoadFileToString(BaselineJson, *BaselinePath))
		{
			TSharedRef<TJsonReader<>> R = TJsonReaderFactory<>::Create(BaselineJson);
			TSharedPtr<FJsonObject> BaselineObj;
			if (FJsonSerializer::Deserialize(R, BaselineObj) && BaselineObj.IsValid())
			{
				Baseline = FScoreboardMetrics::FromJson(BaselineObj);
				bBaselineExistedBeforeRun = true;
				LogLine(TEXT("INFO"), TEXT("Loaded SCOREBOARD_BASELINE.json"));
			}
		}
	}
	if (!bBaselineExistedBeforeRun || bResetBaseline)
	{
		// Seed / reseed baseline from this run.
		FString BaselineJson;
		TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> Writer =
			TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&BaselineJson);
		FJsonSerializer::Serialize(LastRun.ToJson().ToSharedRef(), Writer);
		if (!BlueprintExporterUtil::SaveStringAtomic(BaselineJson, BaselinePath))
		{
			LogLine(TEXT("ERROR"), FString::Printf(TEXT("Failed to write %s"), *BaselinePath), /*bIsError=*/true);
			return 2;
		}
		LogLine(TEXT("INFO"),
			bResetBaseline ? TEXT("Reseeded SCOREBOARD_BASELINE.json (-ResetBaseline)")
			               : TEXT("Seeded SCOREBOARD_BASELINE.json (first run)"));
		Baseline = LastRun;
	}

	// ---- Render all outputs ----
	auto WriteOut = [&OutDir](const TCHAR* Name, const FString& Content) -> bool
	{
		const FString Path = FPaths::Combine(OutDir, Name);
		if (!BlueprintExporterUtil::SaveStringAtomic(Content, Path))
		{
			LogLine(TEXT("ERROR"), FString::Printf(TEXT("Failed to write %s"), *Path), /*bIsError=*/true);
			return false;
		}
		LogLine(TEXT("OK"), FString::Printf(TEXT("Wrote %s"), Name));
		return true;
	};

	bool bAllOk = true;
	bAllOk &= WriteOut(TEXT("INDEX.md"),
		RenderINDEX(Assets, SubclassCounts, FolderCounts, HubRefsOut, HubRefsIn,
			Baseline, LastRun, bBaselineExistedBeforeRun));
	bAllOk &= WriteOut(TEXT("CLASS_TREE.md"), RenderCLASS_TREE(Assets));

	FDependencyGraphResult DepGraph = RenderDEPENDENCY_GRAPH(Assets, RefsInByTargetPath);
	bAllOk &= WriteOut(TEXT("DEPENDENCY_GRAPH.md"), DepGraph.Md);
	bAllOk &= WriteOut(TEXT("dependency_graph.dot"), DepGraph.Dot);

	bAllOk &= WriteOut(TEXT("REPLICATION_MATRIX.md"), RenderREPLICATION_MATRIX(Assets));
	bAllOk &= WriteOut(TEXT("HEALTH_REPORT.md"),
		RenderHEALTH_REPORT(Assets, LastRun.FailedLoads, LastRun.PartialLoads));

	// M4.1 domain overviews — same atomic-write path, deterministic outputs.
	bAllOk &= WriteOut(TEXT("AI_OVERVIEW.md"),
		RenderAI_OVERVIEW(Assets, RefsInByTargetPath));
	bAllOk &= WriteOut(TEXT("ANIM_OVERVIEW.md"),
		RenderANIM_OVERVIEW(Assets));
	bAllOk &= WriteOut(TEXT("UI_OVERVIEW.md"),
		RenderUI_OVERVIEW(Assets, RefsInByTargetPath));
	bAllOk &= WriteOut(TEXT("STRUCTS_ENUMS.md"),
		RenderSTRUCTS_ENUMS(Assets, RefsInByTargetPath));
	// GAS overview is conditional: renderer returns empty string when no
	// GAS-derived assets are detected, in which case we don't emit the file.
	const FString GasOverview = RenderGAS_OVERVIEW(Assets);
	if (!GasOverview.IsEmpty())
	{
		bAllOk &= WriteOut(TEXT("GAS_OVERVIEW.md"), GasOverview);
	}
	else
	{
		// If a previous run created GAS_OVERVIEW.md but current scope has none,
		// leave the stale file in place — aggregate is not a destructive
		// operation. Resetting baseline + re-running is the explicit mechanism
		// for clean slate. Log so users notice the stale-file possibility.
		LogLine(TEXT("INFO"), TEXT("No GAS-derived assets detected — GAS_OVERVIEW.md not emitted."));
	}

	if (!bAllOk)
	{
		return 2;
	}

	LogLine(TEXT("RESULT"),
		FString::Printf(TEXT("Assets=%d Subclasses=%d Folders=%d CoverageUnder100=%d Repl=%d"),
			Assets.Num(), SubclassCounts.Num(), FolderCounts.Num(),
			CoverageUnder100,
			[&]{ int32 N = 0; for (const auto& A : Assets) N += A.ReplicatedVars.Num(); return N; }()));
	LogLine(TEXT("STATUS"), TEXT("SUCCESS"));
	return 0;
}
