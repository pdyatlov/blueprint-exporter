// Copyright Ten Chambers. All Rights Reserved.

#include "BpxPlanHandlers.h"

#if WITH_BPXBRIDGE_SUPPORT && WITH_BPXPYTHON_SUPPORT

#include "BlueprintExporterModule.h"
#include "BpxHandlerRegistry.h"
#include "BpxJsonRpcErrors.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "HAL/FileManager.h"
#include "IPythonScriptPlugin.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "PythonScriptTypes.h"
#include "ReExport/AssetReExporter.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

namespace BlueprintExporter::Bridge
{
	namespace
	{
		// JSON-RPC custom server-error range is -32000..-32099.
		// Spec-defined codes (ErrInvalidParams / ErrInternal etc.) live in
		// BpxJsonRpcErrors.h so the unity build doesn't collide them across
		// BpxBridgeServer.cpp + BpxPlanHandlers.cpp.
		constexpr int32 ErrPythonUnavailable = -32001;
		constexpr int32 ErrPythonExecFailed = -32002;
		constexpr int32 ErrTempFile = -32003;
		constexpr int32 ErrResultParse = -32004;

		struct FPlanParams
		{
			FString PlanJson;
			FString ScriptsRoot;
			// M27.3 — inventory root for scoped re-export after apply_plan.
			// Optional for validate_plan (which is read-only). For apply_plan
			// it must be set, or re-export is skipped with a note in the
			// response. The MCP-side tool plumbs `config.inventory_root` here.
			FString InventoryRoot;
			// M27.3 — caller opts out of re-export (debugging / benchmarking).
			bool bNoReExport = false;
		};

		bool ExtractPlanParams(const TSharedPtr<FJsonObject>& Params, FPlanParams& Out, FString& OutError)
		{
			if (!Params.IsValid())
			{
				OutError = TEXT("missing params object");
				return false;
			}
			if (!Params->TryGetStringField(TEXT("planJson"), Out.PlanJson) || Out.PlanJson.IsEmpty())
			{
				OutError = TEXT("'planJson' is required and must be a non-empty string");
				return false;
			}
			if (!Params->TryGetStringField(TEXT("scriptsRoot"), Out.ScriptsRoot) || Out.ScriptsRoot.IsEmpty())
			{
				OutError = TEXT("'scriptsRoot' is required and must be a non-empty string (the directory containing bridge_entry.py and python_ops/)");
				return false;
			}
			// Optional — fine to be missing. When absent, apply_plan skips
			// re-export and notes it in the response.
			Params->TryGetStringField(TEXT("inventoryRoot"), Out.InventoryRoot);
			Params->TryGetBoolField(TEXT("noReexport"), Out.bNoReExport);
			return true;
		}

		FString MakeTempPath(const TCHAR* Prefix, const TCHAR* Extension)
		{
			return FPaths::CreateTempFilename(*FPaths::ProjectIntermediateDir(), Prefix, Extension);
		}

		// Escapes a filesystem path for embedding inside a Python raw string literal.
		// Raw strings already ignore backslashes, but the path itself must not contain
		// a double quote. UE paths shouldn't, but normalize defensively.
		FString EscapeForPythonRawString(const FString& Path)
		{
			FString Safe = Path;
			Safe.ReplaceInline(TEXT("\""), TEXT(""));
			return Safe;
		}

		// Walk the Python-produced run-report and collect every asset path
		// that either observed a change or was expected to change. Scope:
		//  - entries in `diff.asset_changes[]` where `observed != "stable"`
		//  - entries where the plan expected mutation even if the run was a
		//    no-op (so the agent still gets a fresh sidecar on replays).
		// No-ops and purely stable assets are skipped; re-exporting them
		// would just redo the byte-identical work the commandlet would have
		// done at the last full sweep.
		TArray<FString> CollectReExportTargets(const TSharedPtr<FJsonObject>& Report)
		{
			TSet<FString> Seen;
			TArray<FString> Targets;
			if (!Report.IsValid())
			{
				return Targets;
			}
			const TSharedPtr<FJsonObject>* Diff = nullptr;
			if (!Report->TryGetObjectField(TEXT("diff"), Diff) || Diff == nullptr || !Diff->IsValid())
			{
				return Targets;
			}
			const TArray<TSharedPtr<FJsonValue>>* Changes = nullptr;
			if (!(*Diff)->TryGetArrayField(TEXT("asset_changes"), Changes) || Changes == nullptr)
			{
				return Targets;
			}
			for (const TSharedPtr<FJsonValue>& Entry : *Changes)
			{
				if (!Entry.IsValid()) continue;
				const TSharedPtr<FJsonObject>* Obj = nullptr;
				if (!Entry->TryGetObject(Obj) || Obj == nullptr) continue;

				FString AssetPath;
				if (!(*Obj)->TryGetStringField(TEXT("asset"), AssetPath) || AssetPath.IsEmpty())
				{
					continue;
				}
				FString Observed;
				(*Obj)->TryGetStringField(TEXT("observed"), Observed);
				FString Expected;
				(*Obj)->TryGetStringField(TEXT("expected"), Expected);

				// Skip deleted assets — nothing to re-export. Sidecars for
				// deleted assets remain stale until `refresh_inventory` runs;
				// the agent can detect via `get_asset_meta` returning an
				// entry that no longer exists in the project.
				if (Observed == TEXT("deleted"))
				{
					continue;
				}
				if (Observed != TEXT("stable") || !Expected.IsEmpty())
				{
					bool bAlreadySeen = false;
					Seen.Add(AssetPath, &bAlreadySeen);
					if (!bAlreadySeen)
					{
						Targets.Add(AssetPath);
					}
				}
			}
			// Stable ordering — callers embed this list in the JSON response.
			Targets.Sort([](const FString& A, const FString& B) { return A < B; });
			return Targets;
		}

		// Run re-export for each touched asset. Produces a JSON object
		// suitable for embedding under the handler's `reExport` field.
		TSharedPtr<FJsonObject> RunReExport(
			const TSharedPtr<FJsonObject>& Report,
			const FString& InventoryRoot)
		{
			TSharedPtr<FJsonObject> ReExport = MakeShared<FJsonObject>();
			TArray<TSharedPtr<FJsonValue>> ScopedPathsJson;
			TArray<TSharedPtr<FJsonValue>> WroteFilesJson;
			TArray<TSharedPtr<FJsonValue>> PerAssetJson;
			int32 ErrorCount = 0;

			const TArray<FString> Targets = CollectReExportTargets(Report);
			for (const FString& PackageName : Targets)
			{
				ScopedPathsJson.Add(MakeShared<FJsonValueString>(PackageName));
				const BlueprintExporter::ReExport::FReExportResult R =
					BlueprintExporter::ReExport::ReExportAsset(PackageName, InventoryRoot);

				TSharedPtr<FJsonObject> Entry = MakeShared<FJsonObject>();
				Entry->SetStringField(TEXT("asset"), PackageName);
				Entry->SetStringField(TEXT("status"),
					BlueprintExporter::ReExport::ToString(R.Status));
				if (!R.ClassName.IsEmpty())
				{
					Entry->SetStringField(TEXT("class"), R.ClassName);
				}
				TArray<TSharedPtr<FJsonValue>> FilesJson;
				for (const FString& F : R.WrittenFiles)
				{
					FilesJson.Add(MakeShared<FJsonValueString>(F));
					WroteFilesJson.Add(MakeShared<FJsonValueString>(F));
				}
				Entry->SetArrayField(TEXT("wroteFiles"), FilesJson);
				if (!R.Error.IsEmpty())
				{
					Entry->SetStringField(TEXT("error"), R.Error);
				}
				if (R.Status != BlueprintExporter::ReExport::EReExportStatus::Ok)
				{
					++ErrorCount;
				}
				PerAssetJson.Add(MakeShared<FJsonValueObject>(Entry));
			}

			// `Targets` was pre-sorted by CollectReExportTargets; the three
			// arrays above are built by iterating that, so they're already
			// deterministic. No extra sort needed.
			ReExport->SetArrayField(TEXT("scopedPaths"), ScopedPathsJson);
			ReExport->SetArrayField(TEXT("wroteFiles"), WroteFilesJson);
			ReExport->SetNumberField(TEXT("errorCount"), ErrorCount);
			ReExport->SetArrayField(TEXT("perAsset"), PerAssetJson);
			return ReExport;
		}

		FHandlerResult RunBridgeEntry(
			const FString& PythonEntryFunction,
			const FPlanParams& Params,
			bool bRunReExport)
		{
			IPythonScriptPlugin* Py = IPythonScriptPlugin::Get();
			if (!Py || !Py->IsPythonAvailable())
			{
				return FHandlerResult::Error(ErrPythonUnavailable,
					TEXT("Python is not available in this editor session (PythonScriptPlugin missing or uninitialized)."));
			}

			const FString PlanFile = MakeTempPath(TEXT("bpx_bridge_plan_"), TEXT(".json"));
			const FString ResultFile = MakeTempPath(TEXT("bpx_bridge_result_"), TEXT(".json"));

			if (!FFileHelper::SaveStringToFile(Params.PlanJson, *PlanFile, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
			{
				return FHandlerResult::Error(ErrTempFile,
					FString::Printf(TEXT("Failed to write plan JSON to temp file: %s"), *PlanFile));
			}

			const FString ScriptsRootSafe = EscapeForPythonRawString(Params.ScriptsRoot);
			const FString PlanFileSafe = EscapeForPythonRawString(PlanFile);
			const FString ResultFileSafe = EscapeForPythonRawString(ResultFile);

			FPythonCommandEx Cmd;
			Cmd.ExecutionMode = EPythonCommandExecutionMode::ExecuteStatement;
			Cmd.FileExecutionScope = EPythonFileExecutionScope::Private;
			Cmd.Flags = EPythonCommandFlags::Unattended;
			Cmd.Command = FString::Printf(TEXT(
				"import sys; "
				"_bpx_root = r\"%s\"; "
				"sys.path.insert(0, _bpx_root) if _bpx_root not in sys.path else None; "
				"import bridge_entry; "
				"bridge_entry.%s(r\"%s\", r\"%s\")"),
				*ScriptsRootSafe,
				*PythonEntryFunction,
				*PlanFileSafe,
				*ResultFileSafe);

			const bool bOk = Py->ExecPythonCommandEx(Cmd);

			// Always clean up the plan temp regardless of outcome.
			IFileManager::Get().Delete(*PlanFile, /*bRequireExists*/ false, /*bEvenReadOnly*/ true, /*bQuiet*/ true);

			if (!bOk)
			{
				// Capture the last few log lines for diagnostic surface.
				FString LogTail;
				for (const FPythonLogOutputEntry& Entry : Cmd.LogOutput)
				{
					LogTail += FString::Printf(TEXT("[%s] %s\n"), LexToString(Entry.Type), *Entry.Output);
				}
				IFileManager::Get().Delete(*ResultFile, false, true, true);
				return FHandlerResult::Error(ErrPythonExecFailed,
					FString::Printf(TEXT("Python %s failed. CommandResult: %s\nLogTail:\n%s"),
						*PythonEntryFunction, *Cmd.CommandResult, *LogTail));
			}

			FString ResultText;
			if (!FFileHelper::LoadFileToString(ResultText, *ResultFile))
			{
				return FHandlerResult::Error(ErrResultParse,
					FString::Printf(TEXT("Python %s succeeded but did not produce a result file at %s. CommandResult: %s"),
						*PythonEntryFunction, *ResultFile, *Cmd.CommandResult));
			}

			IFileManager::Get().Delete(*ResultFile, false, true, true);

			TSharedPtr<FJsonValue> ReportValue;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResultText);
			if (!FJsonSerializer::Deserialize(Reader, ReportValue) || !ReportValue.IsValid())
			{
				return FHandlerResult::Error(ErrResultParse,
					FString::Printf(TEXT("Python %s produced a result file but it was not valid JSON (%s)."),
						*PythonEntryFunction, *Reader->GetErrorMessage()));
			}

			TSharedPtr<FJsonObject> Wrapper = MakeShared<FJsonObject>();
			Wrapper->SetField(TEXT("report"), ReportValue);
			Wrapper->SetStringField(TEXT("transport"), TEXT("bridge"));

			// M27.3 — scoped re-export after a successful apply_plan. Only
			// when the caller asked for it AND the run actually passed (a
			// failed run leaves uncommitted state the mechanical-diff may
			// not have reconciled; re-exporting on top would be misleading).
			if (bRunReExport)
			{
				TSharedPtr<FJsonObject> ReportObj;
				const TSharedPtr<FJsonObject>* ReportObjPtr = nullptr;
				const bool bReportIsObject =
					ReportValue->TryGetObject(ReportObjPtr)
					&& ReportObjPtr != nullptr && ReportObjPtr->IsValid();
				if (bReportIsObject)
				{
					ReportObj = *ReportObjPtr;
				}

				if (Params.bNoReExport)
				{
					TSharedPtr<FJsonObject> Skip = MakeShared<FJsonObject>();
					Skip->SetBoolField(TEXT("skipped"), true);
					Skip->SetStringField(TEXT("reason"), TEXT("noReexport=true in params"));
					Wrapper->SetObjectField(TEXT("reExport"), Skip);
				}
				else if (Params.InventoryRoot.IsEmpty())
				{
					TSharedPtr<FJsonObject> Skip = MakeShared<FJsonObject>();
					Skip->SetBoolField(TEXT("skipped"), true);
					Skip->SetStringField(TEXT("reason"),
						TEXT("inventoryRoot not provided by MCP (BPX_INVENTORY_ROOT likely unset)"));
					Wrapper->SetObjectField(TEXT("reExport"), Skip);
				}
				else if (!ReportObj.IsValid())
				{
					TSharedPtr<FJsonObject> Skip = MakeShared<FJsonObject>();
					Skip->SetBoolField(TEXT("skipped"), true);
					Skip->SetStringField(TEXT("reason"),
						TEXT("report is not a JSON object; cannot extract touched assets"));
					Wrapper->SetObjectField(TEXT("reExport"), Skip);
				}
				else
				{
					bool bRunPassed = false;
					ReportObj->TryGetBoolField(TEXT("passed"), bRunPassed);
					if (!bRunPassed)
					{
						TSharedPtr<FJsonObject> Skip = MakeShared<FJsonObject>();
						Skip->SetBoolField(TEXT("skipped"), true);
						Skip->SetStringField(TEXT("reason"),
							TEXT("plan did not pass (execution or diff failed); re-export would be misleading"));
						Wrapper->SetObjectField(TEXT("reExport"), Skip);
					}
					else
					{
						UE_LOG(LogBlueprintExporter, Log,
							TEXT("Bridge: apply_plan passed — scoping re-export across touched assets"));
						Wrapper->SetObjectField(TEXT("reExport"),
							RunReExport(ReportObj, Params.InventoryRoot));
					}
				}
			}

			return FHandlerResult::Success(MakeShared<FJsonValueObject>(Wrapper));
		}
	}

	void RegisterPlanHandlers(FHandlerRegistry& Registry)
	{
		Registry.Register(TEXT("validate_plan"),
			[](const TSharedPtr<FJsonObject>& Params) -> FHandlerResult
			{
				FPlanParams Parsed;
				FString Err;
				if (!ExtractPlanParams(Params, Parsed, Err))
				{
					return FHandlerResult::Error(ErrInvalidParams, Err);
				}
				UE_LOG(LogBlueprintExporter, Log, TEXT("Bridge: validate_plan dispatching to in-process Python"));
				// validate_plan is read-only; no re-export step.
				return RunBridgeEntry(TEXT("run_validate"), Parsed, /*bRunReExport=*/false);
			},
			TEXT("M24.1 validator, in-process. Params: {planJson: string, scriptsRoot: string}. "
			     "Read-only — no mutations, no saves. Returns {report, transport: \"bridge\"}."));

		Registry.Register(TEXT("apply_plan"),
			[](const TSharedPtr<FJsonObject>& Params) -> FHandlerResult
			{
				FPlanParams Parsed;
				FString Err;
				if (!ExtractPlanParams(Params, Parsed, Err))
				{
					return FHandlerResult::Error(ErrInvalidParams, Err);
				}
				UE_LOG(LogBlueprintExporter, Log, TEXT("Bridge: apply_plan dispatching to in-process Python"));
				return RunBridgeEntry(TEXT("run_apply"), Parsed, /*bRunReExport=*/true);
			},
			TEXT("M24 full loop (validate -> execute -> mechanical diff), in-process. "
			     "Params: {planJson: string, scriptsRoot: string, inventoryRoot?: string, noReexport?: bool}. "
			     "MUTATES project assets. On success + inventoryRoot set + !noReexport, re-exports "
			     ".md / .meta.json / .deep.md for touched UBlueprint + StateTree assets. "
			     "Returns {report, transport: \"bridge\", reExport: ...}."));
	}
}

#endif // WITH_BPXBRIDGE_SUPPORT && WITH_BPXPYTHON_SUPPORT
