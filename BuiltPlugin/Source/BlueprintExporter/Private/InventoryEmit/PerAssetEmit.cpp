// Copyright Ten Chambers. All Rights Reserved.

#include "PerAssetEmit.h"

#include "AssetRegistry/AssetData.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Misc/Paths.h"
#include "Schema/BlueprintExportTypes.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "TextExport/DeepDumpRenderer.h"
#include "Util/AtomicFileWriter.h"

#if WITH_STATETREE_SUPPORT
#include "Schema/StateTreeExportTypes.h"
#include "Serialization/StateTreeSerializer.h"
#include "StateTree.h"
#endif

namespace BlueprintExporter::InventoryEmit
{
	// ---- shared class-name sets (public) ----

	const TSet<FName>& GetUBlueprintFamilyClassNames()
	{
		static const TSet<FName> Classes = {
			FName(TEXT("Blueprint")),
			FName(TEXT("AnimBlueprint")),
			FName(TEXT("WidgetBlueprint")),
			FName(TEXT("ControlRigBlueprint")),
		};
		return Classes;
	}

	// ---- small shared helpers (public) ----

	FString BuildAssetOutputBase(const FString& OutDir, const FString& PackageName)
	{
		FString Relative = PackageName;
		Relative.RemoveFromStart(TEXT("/"));
		return FPaths::Combine(OutDir, TEXT("Assets"), Relative);
	}

	FString EscTbl(const FString& In)
	{
		FString Out = In;
		Out.ReplaceInline(TEXT("|"), TEXT("\\|"));
		Out.ReplaceInline(TEXT("\r\n"), TEXT(" "));
		Out.ReplaceInline(TEXT("\n"), TEXT(" "));
		Out.ReplaceInline(TEXT("\r"), TEXT(""));
		return Out;
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

	bool WriteJsonToFile(const TSharedPtr<FJsonObject>& Root, const FString& OutPath)
	{
		if (!Root.IsValid()) return false;
		FString JsonString;
		TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> Writer =
			TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&JsonString);
		if (!FJsonSerializer::Serialize(Root.ToSharedRef(), Writer)) return false;
		return BlueprintExporterUtil::SaveStringAtomic(JsonString, OutPath);
	}

	int32 ComputeCoveragePercent(int32 Total, int32 Documented)
	{
		return Total > 0 ? (100 * Documented) / Total : 100;
	}

	TSharedPtr<FJsonObject> BuildNonUBPCoverageJson(
		const TCHAR* PrimaryBucketName,
		int32 PrimaryTotal,
		int32 PrimaryDocumented,
		const TArray<FString>& SpecializedApplicable,
		const TArray<FString>& SpecializedDocumented,
		int32& OutOverallPct)
	{
		auto MakeBucket = [](int32 Total, int32 Doc)
		{
			TSharedPtr<FJsonObject> O = MakeShared<FJsonObject>();
			O->SetNumberField(TEXT("total"), Total);
			O->SetNumberField(TEXT("documented"), Doc);
			return O;
		};
		TSharedPtr<FJsonObject> Coverage = MakeShared<FJsonObject>();
		Coverage->SetObjectField(PrimaryBucketName,
			MakeBucket(PrimaryTotal, PrimaryDocumented));

		const bool bPrimaryEmpty = (PrimaryTotal == 0);
		const TArray<FString> EffectiveApplicable = bPrimaryEmpty ? TArray<FString>{} : SpecializedApplicable;
		const TArray<FString> EffectiveDocumented = bPrimaryEmpty ? TArray<FString>{} : SpecializedDocumented;

		TSharedPtr<FJsonObject> Specialized = MakeShared<FJsonObject>();
		TArray<TSharedPtr<FJsonValue>> ApplicableJson;
		TArray<TSharedPtr<FJsonValue>> DocumentedJson;
		for (const FString& S : EffectiveApplicable) ApplicableJson.Add(MakeShared<FJsonValueString>(S));
		for (const FString& S : EffectiveDocumented) DocumentedJson.Add(MakeShared<FJsonValueString>(S));
		Specialized->SetArrayField(TEXT("applicable"), ApplicableJson);
		Specialized->SetArrayField(TEXT("documented"), DocumentedJson);
		Coverage->SetObjectField(TEXT("specialized"), Specialized);

		const int32 TrackedTotal = PrimaryTotal + EffectiveApplicable.Num();
		const int32 TrackedDoc   = PrimaryDocumented + EffectiveDocumented.Num();
		OutOverallPct = ComputeCoveragePercent(TrackedTotal, TrackedDoc);
		Coverage->SetNumberField(TEXT("overallPct"), OutOverallPct);
		return Coverage;
	}

	// ---- private UBP render helpers (anon namespace) ----

	namespace
	{
		FString FormatPinType(const FExportedPinType& T)
		{
			FString Base = T.Category;
			if (Base.IsEmpty())
			{
				Base = TEXT("unknown");
			}

			FString Inner;
			if (!T.SubCategoryObject.IsEmpty())
			{
				Inner = StripScriptPrefix(T.SubCategoryObject);
			}
			else if (!T.PinSubCategory.IsEmpty() && T.PinSubCategory != TEXT("none"))
			{
				Inner = T.PinSubCategory;
			}

			FString Rendered = Inner.IsEmpty() ? Base : FString::Printf(TEXT("%s<%s>"), *Base, *Inner);

			if (T.bIsArray)
			{
				Rendered = FString::Printf(TEXT("TArray<%s>"), *Rendered);
			}
			else if (T.bIsSet)
			{
				Rendered = FString::Printf(TEXT("TSet<%s>"), *Rendered);
			}
			else if (T.bIsMap)
			{
				const FString Value = T.ValueTerminalType.IsEmpty() ? TEXT("?") : T.ValueTerminalType;
				Rendered = FString::Printf(TEXT("TMap<%s, %s>"), *Rendered, *Value);
			}

			if (T.bIsReference)
			{
				Rendered += TEXT("&");
			}
			if (T.bHasBrokenReference)
			{
				Rendered += TEXT(" [BROKEN]");
			}
			return Rendered;
		}

		FString FormatAccess(const FExportedFunctionFlags& F)
		{
			return F.AccessSpecifier.IsEmpty() ? TEXT("public") : F.AccessSpecifier;
		}

		FString FormatBlueprintType(EBlueprintExportType T)
		{
			switch (T)
			{
				case EBlueprintExportType::Normal:           return TEXT("Normal");
				case EBlueprintExportType::Const:            return TEXT("Const");
				case EBlueprintExportType::MacroLibrary:     return TEXT("MacroLibrary");
				case EBlueprintExportType::Interface:        return TEXT("Interface");
				case EBlueprintExportType::LevelScript:      return TEXT("LevelScript");
				case EBlueprintExportType::FunctionLibrary:  return TEXT("FunctionLibrary");
				default:                                     return TEXT("Unknown");
			}
		}

		void RenderComponentTree(FString& Md, const FExportedComponent& Comp, int32 Depth)
		{
			const FString Indent = FString::ChrN(Depth * 2, TEXT(' '));
			const FString RootMark = Comp.bIsRootComponent ? TEXT(" [root]") : TEXT("");
			const FString Socket = Comp.AttachSocketName.IsEmpty()
				? FString()
				: FString::Printf(TEXT(" @ socket `%s`"), *Comp.AttachSocketName);
			Md += FString::Printf(TEXT("%s- `%s` — `%s`%s%s\n"),
				*Indent,
				*Comp.ComponentName,
				*StripScriptPrefix(Comp.ComponentClass),
				*RootMark,
				*Socket);
			for (const FExportedComponent& Child : Comp.ChildComponents)
			{
				RenderComponentTree(Md, Child, Depth + 1);
			}
		}

		void RenderIdentity(FString& Md, const FExportedBlueprint& Data)
		{
			Md += TEXT("## Identity\n\n");
			Md += TEXT("| Field | Value |\n");
			Md += TEXT("|---|---|\n");
			Md += FString::Printf(TEXT("| Asset path | `%s` |\n"), *EscTbl(Data.AssetPath));
			Md += FString::Printf(TEXT("| Asset name | `%s` |\n"), *EscTbl(Data.AssetName));
			Md += FString::Printf(TEXT("| Subclass | `%s` |\n"), *EscTbl(Data.BlueprintSubclass));
			Md += FString::Printf(TEXT("| Blueprint type | `%s` |\n"),
				*FormatBlueprintType(Data.BlueprintType));
			Md += FString::Printf(TEXT("| Engine version | `%s` |\n"),
				*EscTbl(Data.ExportInfo.EngineVersion));
			Md += FString::Printf(TEXT("| Plugin version | `%s` |\n"),
				*EscTbl(Data.ExportInfo.PluginVersion));
			Md += TEXT("\n");
		}

		void RenderInheritance(FString& Md, const FExportedBlueprint& Data)
		{
			Md += TEXT("## Inheritance\n\n");
			const FString NativeMark = Data.ParentClass.bIsNative ? TEXT("native") : TEXT("blueprint");
			const FString Module = Data.ParentClass.ModuleName.IsEmpty()
				? FString()
				: FString::Printf(TEXT(", module `%s`"), *Data.ParentClass.ModuleName);
			Md += FString::Printf(TEXT("- Parent class: `%s` (`%s`, %s%s)\n"),
				*Data.ParentClass.ClassName,
				*Data.ParentClass.ClassPath,
				*NativeMark,
				*Module);

			if (Data.ImplementedInterfaces.Num() == 0)
			{
				Md += TEXT("- Interfaces: _none_\n");
			}
			else
			{
				TArray<FString> Sorted = Data.ImplementedInterfaces;
				Sorted.Sort([](const FString& A, const FString& B)
				{
					return A.Compare(B, ESearchCase::IgnoreCase) < 0;
				});
				Md += FString::Printf(TEXT("- Interfaces (%d):\n"), Sorted.Num());
				for (const FString& Iface : Sorted)
				{
					Md += FString::Printf(TEXT("  - `%s`\n"), *Iface);
				}
			}
			Md += TEXT("\n");
		}

		void RenderVariables(FString& Md, const FExportedBlueprint& Data)
		{
			Md += FString::Printf(TEXT("## Variables (%d)\n\n"), Data.Variables.Num());
			if (Data.Variables.Num() == 0)
			{
				Md += TEXT("_None._\n\n");
				return;
			}
			Md += TEXT("| Name | Type | Default | Category | Replication | RepNotify | Flags |\n");
			Md += TEXT("|---|---|---|---|---|---|---|\n");
			for (const FExportedVariable& V : Data.Variables)
			{
				FString Repl;
				if (V.Flags.bReplicated)
				{
					Repl = V.Flags.ReplicationCondition.IsEmpty()
						? TEXT("Replicated")
						: FString::Printf(TEXT("Replicated (%s)"), *V.Flags.ReplicationCondition);
				}
				else
				{
					Repl = TEXT("—");
				}

				const FString RepNotify = V.Flags.bRepNotify
					? (V.Flags.RepNotifyFunc.IsEmpty()
						? TEXT("yes")
						: FString::Printf(TEXT("`%s`"), *V.Flags.RepNotifyFunc))
					: TEXT("—");

				TArray<FString> FlagBits;
				if (V.Flags.bInstanceEditable)     FlagBits.Add(TEXT("InstanceEditable"));
				if (V.Flags.bBlueprintReadOnly)    FlagBits.Add(TEXT("ReadOnly"));
				if (V.Flags.bExposeOnSpawn)        FlagBits.Add(TEXT("ExposeOnSpawn"));
				if (V.Flags.bPrivate)              FlagBits.Add(TEXT("Private"));
				if (V.Flags.bExposeToCinematics)   FlagBits.Add(TEXT("ExposeToCinematics"));
				const FString Flags = FlagBits.Num() == 0 ? TEXT("—") : FString::Join(FlagBits, TEXT(", "));

				const FString Default = V.DefaultValue.IsEmpty() ? TEXT("—") : FString::Printf(TEXT("`%s`"), *EscTbl(V.DefaultValue));
				const FString Category = V.Category.IsEmpty() ? TEXT("—") : FString::Printf(TEXT("`%s`"), *EscTbl(V.Category));

				Md += FString::Printf(TEXT("| `%s` | `%s` | %s | %s | %s | %s | %s |\n"),
					*EscTbl(V.VariableName),
					*EscTbl(FormatPinType(V.VariableType)),
					*Default,
					*Category,
					*Repl,
					*RepNotify,
					*EscTbl(Flags));
			}
			Md += TEXT("\n");
		}

		FString FormatParamList(const TArray<FExportedFunctionParam>& Params)
		{
			TArray<FString> Parts;
			Parts.Reserve(Params.Num());
			for (const FExportedFunctionParam& P : Params)
			{
				FString Piece = FString::Printf(TEXT("%s %s"),
					*FormatPinType(P.ParamType), *P.ParamName);
				if (!P.DefaultValue.IsEmpty())
				{
					Piece += FString::Printf(TEXT(" = %s"), *P.DefaultValue);
				}
				if (P.bPassByReference)
				{
					Piece += TEXT(" [ref]");
				}
				Parts.Add(Piece);
			}
			return FString::Printf(TEXT("(%s)"), *FString::Join(Parts, TEXT(", ")));
		}

		void RenderFunctionSection(FString& Md, const TCHAR* Heading, const TArray<FExportedFunction>& Source)
		{
			Md += FString::Printf(TEXT("## %s (%d)\n\n"), Heading, Source.Num());
			if (Source.Num() == 0)
			{
				Md += TEXT("_None._\n\n");
				return;
			}

			TArray<FExportedFunction> Sorted = Source;
			Sorted.Sort([](const FExportedFunction& A, const FExportedFunction& B)
			{
				return A.FunctionName.Compare(B.FunctionName, ESearchCase::IgnoreCase) < 0;
			});

			for (const FExportedFunction& F : Sorted)
			{
				Md += FString::Printf(TEXT("### `%s`\n\n"), *F.FunctionName);

				// M26.1.1 — surface interface-override provenance. Stubs
				// (Nodes==1, just the Entry node) are called out explicitly
				// so readers can tell "add-function-from-interface UI stub"
				// from an authored override.
				if (F.bIsInterfaceOverride)
				{
					const FString OwnerNote = F.InterfaceClassPath.IsEmpty()
						? FString()
						: FString::Printf(TEXT(" of `%s`"), *EscTbl(F.InterfaceClassPath));
					const bool bIsStub = F.Graph.Nodes.Num() <= 1;
					const FString StubNote = bIsStub ? TEXT(" — **stub (no authored body)**") : FString();
					Md += FString::Printf(TEXT("- Interface override%s%s\n"), *OwnerNote, *StubNote);
				}

				TArray<FString> FlagBits;
				if (F.Flags.bPure)         FlagBits.Add(TEXT("Pure"));
				if (F.Flags.bConst)        FlagBits.Add(TEXT("Const"));
				if (F.Flags.bStatic)       FlagBits.Add(TEXT("Static"));
				if (F.Flags.bCallInEditor) FlagBits.Add(TEXT("CallInEditor"));
				if (F.Flags.bOverride)     FlagBits.Add(TEXT("Override"));
				if (F.Flags.bEvent)        FlagBits.Add(TEXT("Event"));
				const FString FlagStr = FlagBits.Num() == 0 ? TEXT("—") : FString::Join(FlagBits, TEXT(", "));

				TArray<FString> NetBits;
				if (F.Flags.bServer)                 NetBits.Add(TEXT("Server"));
				if (F.Flags.bClient)                 NetBits.Add(TEXT("Client"));
				if (F.Flags.bNetMulticast)           NetBits.Add(TEXT("NetMulticast"));
				if (F.Flags.bReliable)               NetBits.Add(TEXT("Reliable"));
				if (F.Flags.bBlueprintAuthorityOnly) NetBits.Add(TEXT("BlueprintAuthorityOnly"));
				if (F.Flags.bBlueprintCosmetic)      NetBits.Add(TEXT("BlueprintCosmetic"));

				Md += FString::Printf(TEXT("- Access: `%s`\n"), *FormatAccess(F.Flags));
				Md += FString::Printf(TEXT("- Flags: %s\n"), *FlagStr);
				if (NetBits.Num() > 0)
				{
					Md += FString::Printf(TEXT("- Net exec: %s\n"), *FString::Join(NetBits, TEXT(", ")));
				}
				Md += FString::Printf(TEXT("- Inputs: `%s`\n"), *FormatParamList(F.Inputs));
				Md += FString::Printf(TEXT("- Outputs: `%s`\n"), *FormatParamList(F.Outputs));

				if (F.LocalVariables.Num() > 0)
				{
					TArray<FString> Names;
					for (const FExportedVariable& V : F.LocalVariables)
					{
						Names.Add(FString::Printf(TEXT("`%s`"), *V.VariableName));
					}
					Md += FString::Printf(TEXT("- Local variables (%d): %s\n"),
						Names.Num(), *FString::Join(Names, TEXT(", ")));
				}
				else
				{
					Md += TEXT("- Local variables: _none_\n");
				}

				Md += FString::Printf(TEXT("- Nodes: %d\n"), F.Graph.Nodes.Num());

				if (!F.Category.IsEmpty())
				{
					Md += FString::Printf(TEXT("- Category: `%s`\n"), *F.Category);
				}
				if (!F.Description.IsEmpty())
				{
					Md += FString::Printf(TEXT("- Description: %s\n"), *EscTbl(F.Description));
				}
				Md += TEXT("\n");
			}
		}

		void RenderComponents(FString& Md, const FExportedBlueprint& Data)
		{
			Md += FString::Printf(TEXT("## Components (%d)\n\n"), Data.Components.Num());
			if (Data.Components.Num() == 0)
			{
				Md += TEXT("_None (not an Actor Blueprint, or no SCS root)._\n\n");
				return;
			}
			for (const FExportedComponent& Root : Data.Components)
			{
				RenderComponentTree(Md, Root, 0);
			}
			Md += TEXT("\n");
		}

		void RenderCDOProperties(FString& Md, const FExportedBlueprint& Data)
		{
			const int32 N = Data.CDOProperties.Num();
			const FString Kind = Data.DataCarrierKind.IsEmpty()
				? FString()
				: FString::Printf(TEXT(" — %s"), *Data.DataCarrierKind);
			Md += FString::Printf(TEXT("## Class Default Object (%d)%s\n\n"), N, *Kind);
			if (N == 0)
			{
				if (!Data.DataCarrierKind.IsEmpty())
				{
					Md += FString::Printf(TEXT("_No authored overrides found on the CDO. `%s` Blueprints typically author their payload here — if this BP is meant to differ from its parent class, this is a coverage gap._\n\n"),
						*Data.DataCarrierKind);
				}
				else
				{
					Md += TEXT("_No authored overrides on inherited properties._\n\n");
				}
				return;
			}
			for (const FExportedComponentProperty& P : Data.CDOProperties)
			{
				const FString InstancedMark = P.bIsInstancedSubobject ? TEXT(" [instanced]") : TEXT("");
				FString Preview = P.Value;
				Preview.ReplaceInline(TEXT("\r\n"), TEXT(" "));
				Preview.ReplaceInline(TEXT("\n"), TEXT(" "));
				if (Preview.Len() > 120)
				{
					Preview = Preview.Left(117) + TEXT("...");
				}
				Md += FString::Printf(TEXT("- `%s` (`%s`)%s = `%s`\n"),
					*P.PropertyName,
					*P.PropertyType,
					*InstancedMark,
					*Preview);
			}
			Md += TEXT("\n");
		}

		FString ShortClassName(const FString& ClassPath)
		{
			int32 Idx = INDEX_NONE;
			ClassPath.FindLastChar(TEXT('.'), Idx);
			return Idx != INDEX_NONE ? ClassPath.Mid(Idx + 1) : ClassPath;
		}

		void RenderStateMachineList(FString& Md, const TArray<FExportedStateMachine>& Machines, int32 Depth);

		void RenderStateMachine(FString& Md, const FExportedStateMachine& SM, int32 Depth)
		{
			const FString Indent = FString::ChrN(Depth * 2, TEXT(' '));
			Md += FString::Printf(TEXT("%s- **%s** (%d states, %d transitions)\n"),
				*Indent,
				SM.MachineName.IsEmpty() ? TEXT("(unnamed)") : *SM.MachineName,
				SM.States.Num(),
				SM.Transitions.Num());

			TArray<FExportedAnimState> SortedStates = SM.States;
			SortedStates.Sort([](const FExportedAnimState& A, const FExportedAnimState& B)
			{
				return A.StateName.Compare(B.StateName, ESearchCase::IgnoreCase) < 0;
			});
			for (const FExportedAnimState& S : SortedStates)
			{
				const FString Type = S.StateType.IsEmpty() ? FString() : FString::Printf(TEXT(" [%s]"), *S.StateType);
				Md += FString::Printf(TEXT("%s  - State `%s`%s (%d nodes)\n"),
					*Indent,
					S.StateName.IsEmpty() ? TEXT("(unnamed)") : *S.StateName,
					*Type,
					S.AnimGraph.Nodes.Num());

				if (S.NestedStateMachines.Num() > 0)
				{
					RenderStateMachineList(Md, S.NestedStateMachines, Depth + 2);
				}
			}

			TArray<FExportedAnimTransition> SortedTrans = SM.Transitions;
			SortedTrans.Sort([](const FExportedAnimTransition& A, const FExportedAnimTransition& B)
			{
				int32 Cmp = A.SourceState.Compare(B.SourceState, ESearchCase::IgnoreCase);
				if (Cmp != 0) return Cmp < 0;
				return A.TargetState.Compare(B.TargetState, ESearchCase::IgnoreCase) < 0;
			});
			for (const FExportedAnimTransition& T : SortedTrans)
			{
				const FString LogicLabel = T.BlendSettings.LogicType.IsEmpty()
					? FString()
					: FString::Printf(TEXT(" [%s]"), *T.BlendSettings.LogicType);
				const FString CrossfadeLabel = T.BlendSettings.CrossfadeDuration > 0.0f
					? FString::Printf(TEXT(" crossfade=%.2fs"), T.BlendSettings.CrossfadeDuration)
					: FString();
				Md += FString::Printf(TEXT("%s  - Transition `%s` → `%s`%s%s\n"),
					*Indent,
					T.SourceState.IsEmpty() ? TEXT("(entry)") : *T.SourceState,
					T.TargetState.IsEmpty() ? TEXT("(none)") : *T.TargetState,
					*LogicLabel,
					*CrossfadeLabel);
			}
		}

		void RenderStateMachineList(FString& Md, const TArray<FExportedStateMachine>& Machines, int32 Depth)
		{
			TArray<FExportedStateMachine> Sorted = Machines;
			Sorted.Sort([](const FExportedStateMachine& A, const FExportedStateMachine& B)
			{
				return A.MachineName.Compare(B.MachineName, ESearchCase::IgnoreCase) < 0;
			});
			for (const FExportedStateMachine& SM : Sorted)
			{
				RenderStateMachine(Md, SM, Depth);
			}
		}

		void RenderStateMachines(FString& Md, const FExportedBlueprint& Data)
		{
			if (Data.BlueprintSubclass != TEXT("AnimBlueprint"))
			{
				return;
			}
			Md += TEXT("## State Machines\n\n");
			if (Data.StateMachines.Num() == 0)
			{
				Md += TEXT("_No authored state machines (single-graph anim blueprint)._\n\n");
				return;
			}
			RenderStateMachineList(Md, Data.StateMachines, 0);
			Md += TEXT("\n");
		}

		void RenderWidgetNode(FString& Md, const FExportedWidgetNode& Node, int32 Depth)
		{
			const FString Indent = FString::ChrN(Depth * 2, TEXT(' '));
			const FString ClassShort = ShortClassName(Node.WidgetClass);
			const FString VarLabel = Node.bIsVariable ? TEXT(" [variable]") : TEXT("");
			const FString SlotLabel = Node.SlotClass.IsEmpty()
				? FString()
				: FString::Printf(TEXT(" via %s"), *ShortClassName(Node.SlotClass));

			Md += FString::Printf(TEXT("%s- `%s` (`%s`)%s%s\n"),
				*Indent,
				Node.WidgetName.IsEmpty() ? TEXT("(unnamed)") : *Node.WidgetName,
				*ClassShort,
				*VarLabel,
				*SlotLabel);

			for (const FExportedWidgetNode& Child : Node.Children)
			{
				RenderWidgetNode(Md, Child, Depth + 1);
			}
		}

		void RenderWidgetTree(FString& Md, const FExportedBlueprint& Data)
		{
			if (Data.BlueprintSubclass != TEXT("WidgetBlueprint"))
			{
				return;
			}
			Md += TEXT("## Widget Tree\n\n");
			if (Data.WidgetTree.Num() == 0)
			{
				Md += TEXT("_No widget tree (empty root)._\n\n");
				return;
			}
			for (const FExportedWidgetNode& Root : Data.WidgetTree)
			{
				RenderWidgetNode(Md, Root, 0);
			}
			Md += TEXT("\n");
		}

		void RenderGraphs(FString& Md, const FExportedBlueprint& Data)
		{
			Md += TEXT("## Graphs\n\n");
			Md += FString::Printf(TEXT("- Event graph: `%s` (%d nodes)\n"),
				*Data.EventGraph.GraphName, Data.EventGraph.Nodes.Num());
			Md += FString::Printf(TEXT("- Construction script: `%s` (%d nodes)\n"),
				*Data.ConstructionScript.GraphName, Data.ConstructionScript.Nodes.Num());

			if (Data.AdditionalGraphs.Num() == 0)
			{
				Md += TEXT("- Additional graphs: _none_\n");
			}
			else
			{
				TArray<FExportedGraph> Sorted = Data.AdditionalGraphs;
				Sorted.Sort([](const FExportedGraph& A, const FExportedGraph& B)
				{
					return A.GraphName.Compare(B.GraphName, ESearchCase::IgnoreCase) < 0;
				});
				Md += FString::Printf(TEXT("- Additional graphs (%d):\n"), Sorted.Num());
				for (const FExportedGraph& G : Sorted)
				{
					const FString Type = G.GraphType.IsEmpty() ? FString() : FString::Printf(TEXT(" [%s]"), *G.GraphType);
					Md += FString::Printf(TEXT("  - `%s`%s (%d nodes)\n"),
						*G.GraphName, *Type, G.Nodes.Num());
				}
			}
			Md += TEXT("\n");
		}

		void RenderReferences(FString& Md, const FExportedBlueprint& Data)
		{
			Md += TEXT("## References\n\n");

			TArray<FExportedDependency> Hard;
			TArray<FExportedDependency> Soft;
			for (const FExportedDependency& D : Data.Dependencies)
			{
				(D.DependencyType == EExportDependencyType::Hard ? Hard : Soft).Add(D);
			}
			auto SortDeps = [](TArray<FExportedDependency>& V)
			{
				V.Sort([](const FExportedDependency& A, const FExportedDependency& B)
				{
					return A.AssetPath.Compare(B.AssetPath, ESearchCase::IgnoreCase) < 0;
				});
			};
			SortDeps(Hard);
			SortDeps(Soft);

			auto EmitSection = [&Md](const TCHAR* Label, const TArray<FExportedDependency>& Deps)
			{
				Md += FString::Printf(TEXT("%s (%d):\n"), Label, Deps.Num());
				if (Deps.Num() == 0)
				{
					Md += TEXT("- _none_\n");
					return;
				}
				for (const FExportedDependency& D : Deps)
				{
					const FString Kind = D.bIsBlueprint ? TEXT("Blueprint")
						: (D.bIsNativeClass ? TEXT("native") : TEXT("asset"));
					Md += FString::Printf(TEXT("- `%s` [%s]\n"), *D.AssetPath, *Kind);
				}
			};
			EmitSection(TEXT("Hard refs out"), Hard);
			Md += TEXT("\n");
			EmitSection(TEXT("Soft refs out"), Soft);
			Md += TEXT("\n");
		}

		void RenderMetadata(FString& Md, const FExportedBlueprint& Data)
		{
			Md += TEXT("## Metadata & Flags\n\n");
			Md += FString::Printf(TEXT("- Blueprint type: `%s`\n"),
				*FormatBlueprintType(Data.BlueprintType));
			Md += FString::Printf(TEXT("- Subclass: `%s`\n"), *Data.BlueprintSubclass);

			if (Data.MetaData.Num() == 0)
			{
				Md += TEXT("- Custom metadata: _none_\n\n");
				return;
			}
			TArray<FString> Keys;
			Data.MetaData.GetKeys(Keys);
			Keys.Sort([](const FString& A, const FString& B)
			{
				return A.Compare(B, ESearchCase::IgnoreCase) < 0;
			});
			Md += FString::Printf(TEXT("- Custom metadata (%d):\n"), Keys.Num());
			for (const FString& K : Keys)
			{
				Md += FString::Printf(TEXT("  - `%s` = `%s`\n"), *K, *EscTbl(Data.MetaData[K]));
			}
			Md += TEXT("\n");
		}

		// ---- UBP coverage helpers (private) ----

		TArray<FString> ComputeSpecializedApplicable(const FExportedBlueprint& Data)
		{
			TArray<FString> Out;
			const FString& Sub = Data.BlueprintSubclass;
			if (Sub == TEXT("AnimBlueprint"))   Out.Add(TEXT("AnimBP.StateMachines"));
			if (Sub == TEXT("WidgetBlueprint")) Out.Add(TEXT("WidgetBP.WidgetTree"));
			if (Data.DataCarrierKind == TEXT("GameplayEffect"))  Out.Add(TEXT("GameplayEffect.CDO"));
			if (Data.DataCarrierKind == TEXT("GameplayAbility")) Out.Add(TEXT("GameplayAbility.CDO"));
			if (Data.DataCarrierKind == TEXT("DataAsset"))       Out.Add(TEXT("DataAsset.CDO"));
			return Out;
		}

		TArray<FString> ComputeSpecializedDocumented(const FExportedBlueprint& Data)
		{
			TArray<FString> Out;
			const FString& Sub = Data.BlueprintSubclass;
			if (Sub == TEXT("AnimBlueprint"))   Out.Add(TEXT("AnimBP.StateMachines"));
			if (Sub == TEXT("WidgetBlueprint")) Out.Add(TEXT("WidgetBP.WidgetTree"));

			const bool bHasCDO = Data.CDOProperties.Num() > 0;
			const bool bHasVars = Data.Variables.Num() > 0;

			if (bHasCDO && Data.DataCarrierKind == TEXT("GameplayEffect"))  Out.Add(TEXT("GameplayEffect.CDO"));
			if (bHasCDO && Data.DataCarrierKind == TEXT("GameplayAbility")) Out.Add(TEXT("GameplayAbility.CDO"));
			if ((bHasCDO || bHasVars) && Data.DataCarrierKind == TEXT("DataAsset")) Out.Add(TEXT("DataAsset.CDO"));

			return Out;
		}

		TSharedPtr<FJsonObject> BuildCoverageJson(
			const FExportedBlueprint& Data,
			int32& OutOverallPct)
		{
			const int32 VarTotal   = Data.Variables.Num();
			const int32 FnTotal    = Data.Functions.Num() + Data.Macros.Num();
			const int32 ComponentTotal = Data.Components.Num();
			const int32 GraphTotal = 2 + Data.AdditionalGraphs.Num();
			const int32 CDOPropTotal = Data.CDOProperties.Num();

			const int32 VarDoc   = VarTotal;
			const int32 FnDoc    = FnTotal;
			const int32 CompDoc  = ComponentTotal;
			const int32 GraphDoc = GraphTotal;
			const int32 CDOPropDoc = CDOPropTotal;

			const TArray<FString> Applicable = ComputeSpecializedApplicable(Data);
			const TArray<FString> Documented = ComputeSpecializedDocumented(Data);

			auto MakeBucket = [](int32 Total, int32 Doc)
			{
				TSharedPtr<FJsonObject> O = MakeShared<FJsonObject>();
				O->SetNumberField(TEXT("total"), Total);
				O->SetNumberField(TEXT("documented"), Doc);
				return O;
			};

			TSharedPtr<FJsonObject> Coverage = MakeShared<FJsonObject>();
			Coverage->SetObjectField(TEXT("variables"),     MakeBucket(VarTotal,       VarDoc));
			Coverage->SetObjectField(TEXT("functions"),     MakeBucket(FnTotal,        FnDoc));
			Coverage->SetObjectField(TEXT("components"),    MakeBucket(ComponentTotal, CompDoc));
			Coverage->SetObjectField(TEXT("graphs"),        MakeBucket(GraphTotal,     GraphDoc));
			Coverage->SetObjectField(TEXT("cdoProperties"), MakeBucket(CDOPropTotal,   CDOPropDoc));

			TSharedPtr<FJsonObject> Specialized = MakeShared<FJsonObject>();
			TArray<TSharedPtr<FJsonValue>> ApplicableJson;
			TArray<TSharedPtr<FJsonValue>> DocumentedJson;
			for (const FString& S : Applicable)  ApplicableJson.Add(MakeShared<FJsonValueString>(S));
			for (const FString& S : Documented)  DocumentedJson.Add(MakeShared<FJsonValueString>(S));
			Specialized->SetArrayField(TEXT("applicable"), ApplicableJson);
			Specialized->SetArrayField(TEXT("documented"), DocumentedJson);
			Coverage->SetObjectField(TEXT("specialized"), Specialized);

			const int32 TrackedTotal = VarTotal + FnTotal + ComponentTotal + GraphTotal + CDOPropTotal + Applicable.Num();
			const int32 TrackedDoc   = VarDoc  + FnDoc    + CompDoc        + GraphDoc   + CDOPropDoc   + Documented.Num();
			OutOverallPct = ComputeCoveragePercent(TrackedTotal, TrackedDoc);
			Coverage->SetNumberField(TEXT("overallPct"), OutOverallPct);

			return Coverage;
		}

#if WITH_STATETREE_SUPPORT
		// ---- StateTree render helpers (private) ----

		int32 CountStateTreeStates(const TArray<FExportedStateTreeState>& States)
		{
			int32 N = 0;
			for (const FExportedStateTreeState& S : States)
			{
				++N;
				N += CountStateTreeStates(S.Children);
			}
			return N;
		}

		const TCHAR* StateTypeLabel(EExportedStateTreeStateType T)
		{
			switch (T)
			{
				case EExportedStateTreeStateType::State:       return TEXT("State");
				case EExportedStateTreeStateType::Group:       return TEXT("Group");
				case EExportedStateTreeStateType::Linked:      return TEXT("Linked");
				case EExportedStateTreeStateType::LinkedAsset: return TEXT("LinkedAsset");
				case EExportedStateTreeStateType::Subtree:     return TEXT("Subtree");
				default:                                        return TEXT("Unknown");
			}
		}

		const TCHAR* TransitionTriggerLabel(EExportedStateTreeTransitionTrigger T)
		{
			switch (T)
			{
				case EExportedStateTreeTransitionTrigger::OnStateCompleted: return TEXT("OnStateCompleted");
				case EExportedStateTreeTransitionTrigger::OnStateSucceeded: return TEXT("OnStateSucceeded");
				case EExportedStateTreeTransitionTrigger::OnStateFailed:    return TEXT("OnStateFailed");
				case EExportedStateTreeTransitionTrigger::OnTick:           return TEXT("OnTick");
				case EExportedStateTreeTransitionTrigger::OnEvent:          return TEXT("OnEvent");
				default:                                                     return TEXT("Unknown");
			}
		}

		FString FormatEditorNode(const FExportedStateTreeEditorNode& N)
		{
			const FString Short = StripScriptPrefix(N.StructType);
			if (N.Name.IsEmpty()) return FString::Printf(TEXT("`%s`"), *Short);
			return FString::Printf(TEXT("`%s` (`%s`)"), *N.Name, *Short);
		}

		void RenderStateTreeState(FString& Md, const FExportedStateTreeState& State, int32 Depth)
		{
			const FString Indent = FString::ChrN(Depth * 2, TEXT(' '));

			const FString Tag = State.Tag.IsEmpty()
				? FString()
				: FString::Printf(TEXT(" tag=`%s`"), *State.Tag);
			const FString Linked = State.LinkedAsset.IsEmpty()
				? FString()
				: FString::Printf(TEXT(" linked=`%s`"), *State.LinkedAsset);
			Md += FString::Printf(TEXT("%s- **%s** [%s]%s%s\n"),
				*Indent,
				State.Name.IsEmpty() ? TEXT("(unnamed)") : *State.Name,
				StateTypeLabel(State.Type),
				*Tag,
				*Linked);

			auto EmitList = [&](const TCHAR* Label, const TArray<FExportedStateTreeEditorNode>& Nodes)
			{
				if (Nodes.Num() == 0) return;
				Md += FString::Printf(TEXT("%s  - %s (%d): "), *Indent, Label, Nodes.Num());
				TArray<FString> Parts;
				for (const FExportedStateTreeEditorNode& EN : Nodes) Parts.Add(FormatEditorNode(EN));
				Md += FString::Join(Parts, TEXT(", "));
				Md += TEXT("\n");
			};
			EmitList(TEXT("Enter conditions"), State.EnterConditions);
			EmitList(TEXT("Tasks"), State.Tasks);

			if (State.Transitions.Num() > 0)
			{
				Md += FString::Printf(TEXT("%s  - Transitions (%d):\n"), *Indent, State.Transitions.Num());
				for (const FExportedStateTreeTransition& T : State.Transitions)
				{
					const FString EventPart = T.EventTag.IsEmpty()
						? FString()
						: FString::Printf(TEXT(" event=`%s`"), *T.EventTag);
					const FString DelayPart = T.DelaySeconds > 0.0f
						? FString::Printf(TEXT(" delay=%.2fs%s"),
							T.DelaySeconds,
							T.bDelayIsRandom ? TEXT(" [random]") : TEXT(""))
						: FString();
					const FString CondPart = T.Conditions.Num() > 0
						? FString::Printf(TEXT(" conditions=%d"), T.Conditions.Num())
						: FString();
					const FString Target = T.TargetStateName.IsEmpty() ? TEXT("(none)") : T.TargetStateName;
					Md += FString::Printf(TEXT("%s    - %s → `%s`%s%s%s\n"),
						*Indent,
						TransitionTriggerLabel(T.Trigger),
						*Target,
						*EventPart,
						*DelayPart,
						*CondPart);
				}
			}

			for (const FExportedStateTreeState& Child : State.Children)
			{
				RenderStateTreeState(Md, Child, Depth + 1);
			}
		}

		void CollectStateTreeStructTypes(
			const TArray<FExportedStateTreeEditorNode>& Nodes,
			TSet<FString>& OutTypes)
		{
			for (const FExportedStateTreeEditorNode& N : Nodes)
			{
				if (!N.StructType.IsEmpty()) OutTypes.Add(N.StructType);
			}
		}

		void CollectStateTreeStructTypesRecursive(
			const TArray<FExportedStateTreeState>& States,
			TSet<FString>& OutTypes)
		{
			for (const FExportedStateTreeState& S : States)
			{
				CollectStateTreeStructTypes(S.EnterConditions, OutTypes);
				CollectStateTreeStructTypes(S.Tasks, OutTypes);
				for (const FExportedStateTreeTransition& T : S.Transitions)
				{
					CollectStateTreeStructTypes(T.Conditions, OutTypes);
				}
				CollectStateTreeStructTypesRecursive(S.Children, OutTypes);
			}
		}
#endif // WITH_STATETREE_SUPPORT
	}

	// ---- big entry points (public) ----

	FString RenderBlueprintMarkdown(const FExportedBlueprint& Data)
	{
		FString Md;
		Md.Reserve(16 * 1024);
		Md += FString::Printf(TEXT("# %s\n\n"), *Data.AssetName);
		RenderIdentity(Md, Data);
		RenderInheritance(Md, Data);
		RenderVariables(Md, Data);
		RenderFunctionSection(Md, TEXT("Functions"), Data.Functions);
		RenderFunctionSection(Md, TEXT("Macros"), Data.Macros);
		RenderComponents(Md, Data);
		RenderCDOProperties(Md, Data);
		RenderGraphs(Md, Data);
		RenderStateMachines(Md, Data);
		RenderWidgetTree(Md, Data);
		RenderReferences(Md, Data);
		RenderMetadata(Md, Data);
		return Md;
	}

	bool WriteMetaJson(
		const FExportedBlueprint& Data,
		const FString& OutPath,
		int32& OutOverallPct)
	{
		TSharedPtr<FJsonObject> Root = Data.ToJson();
		if (!Root.IsValid())
		{
			return false;
		}
		Root->SetStringField(TEXT("assetType"),
			Data.BlueprintSubclass.IsEmpty() ? TEXT("Blueprint") : Data.BlueprintSubclass);
		Root->SetObjectField(TEXT("coverage"), BuildCoverageJson(Data, OutOverallPct));
		return WriteJsonToFile(Root, OutPath);
	}

#if WITH_STATETREE_SUPPORT
	bool EmitStateTreeAsset(
		const FAssetData& AssetData,
		UStateTree* ST,
		const FString& MdPath,
		const FString& MetaPath,
		int32& OutOverallPct,
		FString& OutError,
		bool bEmitDeepDump,
		const FString& DeepPath)
	{
		if (!ST)
		{
			OutError = TEXT("null UStateTree");
			return false;
		}

		FStateTreeSerializer Serializer;
		FExportedStateTree ExportedData;
		FString SerializeError;
		if (!Serializer.SerializeStateTree(ST, ExportedData, SerializeError))
		{
			OutError = SerializeError.IsEmpty() ? TEXT("SerializeStateTree returned false") : SerializeError;
			return false;
		}
		ExportedData.ExportInfo.ExportTimestamp.Reset();

		const int32 TotalStates = CountStateTreeStates(ExportedData.RootStates);

		FString Md;
		Md.Reserve(4 * 1024);
		Md += FString::Printf(TEXT("# %s\n\n"), *ExportedData.AssetName);
		Md += TEXT("## Identity\n\n");
		Md += TEXT("| Field | Value |\n|---|---|\n");
		Md += FString::Printf(TEXT("| Asset path | `%s` |\n"), *EscTbl(ExportedData.AssetPath));
		Md += FString::Printf(TEXT("| Asset name | `%s` |\n"), *EscTbl(ExportedData.AssetName));
		Md += TEXT("| Asset type | `StateTree` |\n");
		Md += FString::Printf(TEXT("| Schema | `%s` |\n"),
			ExportedData.Schema.IsEmpty() ? TEXT("—") : *EscTbl(ExportedData.Schema));
		Md += FString::Printf(TEXT("| Engine version | `%s` |\n"),
			*EscTbl(ExportedData.ExportInfo.EngineVersion));
		Md += FString::Printf(TEXT("| Plugin version | `%s` |\n"),
			*EscTbl(ExportedData.ExportInfo.PluginVersion));
		Md += TEXT("\n");

		TSet<FString> StructTypeSet;
		CollectStateTreeStructTypes(ExportedData.Evaluators, StructTypeSet);
		CollectStateTreeStructTypes(ExportedData.GlobalTasks, StructTypeSet);
		CollectStateTreeStructTypesRecursive(ExportedData.RootStates, StructTypeSet);

		Md += TEXT("## Summary\n\n");
		Md += FString::Printf(TEXT("- Root states: **%d**\n"), ExportedData.RootStates.Num());
		Md += FString::Printf(TEXT("- Total states (incl. nested): **%d**\n"), TotalStates);
		Md += FString::Printf(TEXT("- Global evaluators: **%d**\n"), ExportedData.Evaluators.Num());
		Md += FString::Printf(TEXT("- Global tasks: **%d**\n"), ExportedData.GlobalTasks.Num());
		Md += FString::Printf(TEXT("- Property bindings: **%d**\n"), ExportedData.Bindings.Num());
		Md += FString::Printf(TEXT("- Unique FInstancedStruct node types: **%d**\n"), StructTypeSet.Num());
		Md += TEXT("\n");

		if (ExportedData.Evaluators.Num() > 0)
		{
			Md += FString::Printf(TEXT("## Global Evaluators (%d)\n\n"), ExportedData.Evaluators.Num());
			for (const FExportedStateTreeEditorNode& EN : ExportedData.Evaluators)
			{
				Md += FString::Printf(TEXT("- %s\n"), *FormatEditorNode(EN));
			}
			Md += TEXT("\n");
		}
		if (ExportedData.GlobalTasks.Num() > 0)
		{
			Md += FString::Printf(TEXT("## Global Tasks (%d)\n\n"), ExportedData.GlobalTasks.Num());
			for (const FExportedStateTreeEditorNode& EN : ExportedData.GlobalTasks)
			{
				Md += FString::Printf(TEXT("- %s\n"), *FormatEditorNode(EN));
			}
			Md += TEXT("\n");
		}

		Md += FString::Printf(TEXT("## States (%d root, %d total)\n\n"),
			ExportedData.RootStates.Num(), TotalStates);
		if (ExportedData.RootStates.Num() == 0)
		{
			Md += TEXT("_No root states._\n\n");
		}
		else
		{
			for (const FExportedStateTreeState& Root2 : ExportedData.RootStates)
			{
				RenderStateTreeState(Md, Root2, 0);
			}
			Md += TEXT("\n");
		}

		if (StructTypeSet.Num() > 0)
		{
			TArray<FString> StructTypes = StructTypeSet.Array();
			StructTypes.Sort([](const FString& A, const FString& B)
			{
				return A.Compare(B, ESearchCase::IgnoreCase) < 0;
			});
			Md += FString::Printf(TEXT("## FInstancedStruct Node Types (%d)\n\n"), StructTypes.Num());
			for (const FString& S : StructTypes)
			{
				Md += FString::Printf(TEXT("- `%s`\n"), *S);
			}
			Md += TEXT("\n");
		}

		if (!BlueprintExporterUtil::SaveStringAtomic(Md, MdPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MdPath);
			return false;
		}

		TSharedPtr<FJsonObject> Root = ExportedData.ToJson();
		if (!Root.IsValid())
		{
			OutError = TEXT("FExportedStateTree::ToJson returned null");
			return false;
		}
		Root->SetStringField(TEXT("assetType"), TEXT("StateTree"));

		static const TArray<FString> STSpecialized = {
			TEXT("ST.TasksPerState"),
			TEXT("ST.Transitions"),
			TEXT("ST.Conditions"),
			TEXT("ST.InstancedStructTypes"),
		};
		int32 Pct = 100;
		Root->SetObjectField(TEXT("coverage"),
			BuildNonUBPCoverageJson(TEXT("states"), TotalStates, TotalStates,
				STSpecialized, STSpecialized, Pct));
		OutOverallPct = Pct;

		if (!WriteJsonToFile(Root, MetaPath))
		{
			OutError = FString::Printf(TEXT("failed to write %s"), *MetaPath);
			return false;
		}

		if (bEmitDeepDump && !DeepPath.IsEmpty())
		{
			const FString DeepMd =
				BlueprintExporter::DeepDump::RenderStateTreeMarkdown(ExportedData);
			if (!BlueprintExporterUtil::SaveStringAtomic(DeepMd, DeepPath))
			{
				OutError = FString::Printf(TEXT("failed to write %s"), *DeepPath);
				return false;
			}
		}
		return true;
	}
#endif // WITH_STATETREE_SUPPORT
}
