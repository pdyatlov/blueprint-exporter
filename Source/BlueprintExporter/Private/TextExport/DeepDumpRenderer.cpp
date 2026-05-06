// Copyright 10 Chambers. All Rights Reserved.

#include "TextExport/DeepDumpRenderer.h"
#include "TextExport/DeepRenderShared.h"
#include "Schema/BlueprintExportTypes.h"
#include "Schema/StateTreeExportTypes.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"

namespace
{
	using BlueprintExporter::DeepRender::EscTbl;

	FString StripScriptPrefix(const FString& ClassPath)
	{
		int32 DotIdx = INDEX_NONE;
		if (ClassPath.FindLastChar(TEXT('.'), DotIdx))
		{
			return ClassPath.Mid(DotIdx + 1);
		}
		return ClassPath;
	}

	FString ShortClassName(const FString& ClassPath)
	{
		return StripScriptPrefix(ClassPath);
	}

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

	// ------- Component tree: property values are load-bearing in Tier 2 -------

	void RenderComponentPropertyRow(FString& Md, const FExportedComponentProperty& P)
	{
		const FString Name = EscTbl(P.PropertyName);
		const FString Type = EscTbl(P.PropertyType);
		const FString InstancedMark = P.bIsInstancedSubobject ? TEXT(" [instanced]") : TEXT("");
		const FString Value = P.Value.IsEmpty()
			? FString(TEXT("—"))
			: FString::Printf(TEXT("`%s`"), *EscTbl(P.Value));
		Md += FString::Printf(TEXT("| `%s` | `%s`%s | %s |\n"),
			*Name, *Type, *InstancedMark, *Value);
	}

	// ------- Instanced subobject tree (recursive) -------
	//
	// Renders the structured property tree captured by the serializer for
	// Instanced / EditInlineNew references (e.g. UAIPerceptionComponent::SensesConfig,
	// GAS attribute sets, anim layer overrides). Without this, .deep.md only carries
	// the flat ExportTextItem_Direct blob — sight radius / hearing range / peripheral
	// angle defaults would only be visible in .meta.json's `subobjects` JSON tree.
	//
	// Honors the schema markers per the "Never guess values" principle:
	//   bHasBrokenReference → "**Broken reference**" line + brokenReferenceInfo
	//   bCycleDetected      → "**Cycle detected**" notice, no further descent
	//   bTruncated          → "**Truncated**" notice (depth cap = 8 in serializer)

	void RenderInstancedSubobjectTree(
		FString& Md,
		const TArray<TSharedPtr<FJsonValue>>& SubobjectValues,
		int32 HeadingLevel);

	// One subobject element from a SubobjectJsonValues array. Inside a property's
	// `subobjects` field, each element is a JsonObject with the shape documented
	// on FExportedComponentProperty.
	void RenderInstancedSubobjectEntry(
		FString& Md,
		const TSharedPtr<FJsonObject>& Obj,
		int32 HeadingLevel)
	{
		if (!Obj.IsValid())
		{
			return;
		}

		const int32 ClampedLevel = FMath::Clamp(HeadingLevel, 1, 6);
		const FString Hashes = FString::ChrN(ClampedLevel, TEXT('#'));

		FString ClassPath, ObjectName;
		Obj->TryGetStringField(TEXT("classPath"), ClassPath);
		Obj->TryGetStringField(TEXT("objectName"), ObjectName);

		// Container-context label — `[N]` for arrays, `["K"]` for maps.
		double ArrayIndexD = 0;
		const bool bHasArrayIndex = Obj->TryGetNumberField(TEXT("arrayIndex"), ArrayIndexD);
		FString MapKey;
		const bool bHasMapKey = Obj->TryGetStringField(TEXT("mapKey"), MapKey);

		FString IndexLabel;
		if (bHasArrayIndex)
		{
			IndexLabel = FString::Printf(TEXT("`[%d]` "), static_cast<int32>(ArrayIndexD));
		}
		else if (bHasMapKey)
		{
			IndexLabel = FString::Printf(TEXT("`[\"%s\"]` "), *EscTbl(MapKey));
		}

		FString TitleSuffix;
		if (!ObjectName.IsEmpty())
		{
			TitleSuffix = FString::Printf(TEXT("`%s`"), *EscTbl(ObjectName));
		}
		if (!ClassPath.IsEmpty())
		{
			const FString ClassShort = ShortClassName(ClassPath);
			TitleSuffix = TitleSuffix.IsEmpty()
				? FString::Printf(TEXT("`%s`"), *EscTbl(ClassShort))
				: FString::Printf(TEXT("%s — `%s`"), *TitleSuffix, *EscTbl(ClassShort));
		}
		if (TitleSuffix.IsEmpty())
		{
			TitleSuffix = TEXT("(unresolved subobject)");
		}

		Md += FString::Printf(TEXT("%s %s%s\n\n"), *Hashes, *IndexLabel, *TitleSuffix);

		bool bBroken = false;
		Obj->TryGetBoolField(TEXT("bHasBrokenReference"), bBroken);
		if (bBroken)
		{
			FString Info;
			Obj->TryGetStringField(TEXT("brokenReferenceInfo"), Info);
			Md += FString::Printf(TEXT("- **Broken reference**: %s\n\n"),
				Info.IsEmpty() ? TEXT("(no info)") : *EscTbl(Info));
			return;
		}

		bool bCycle = false;
		Obj->TryGetBoolField(TEXT("bCycleDetected"), bCycle);
		if (bCycle)
		{
			Md += TEXT("- **Cycle detected** — already-visited subobject; tree truncated here.\n\n");
			return;
		}

		bool bTruncated = false;
		Obj->TryGetBoolField(TEXT("bTruncated"), bTruncated);
		if (bTruncated)
		{
			Md += TEXT("- **Truncated** — serializer recursion-depth cap reached (MAX_SUBOBJECT_RECURSION_DEPTH=8).\n\n");
			return;
		}

		// Property tree — split scalar properties (rendered as one table) from
		// instanced sub-properties (each recurses into its own block).
		const TArray<TSharedPtr<FJsonValue>>* PropsArrayPtr = nullptr;
		if (!Obj->TryGetArrayField(TEXT("properties"), PropsArrayPtr) || !PropsArrayPtr || PropsArrayPtr->Num() == 0)
		{
			Md += TEXT("- _No non-default properties._\n\n");
			return;
		}

		struct FParsedProp
		{
			FString Name;
			FString Type;
			FString Value;
			bool bInstanced = false;
			TSharedPtr<FJsonObject> Source;
		};

		TArray<FParsedProp> ScalarProps;
		TArray<FParsedProp> InstancedProps;

		for (const TSharedPtr<FJsonValue>& PVal : *PropsArrayPtr)
		{
			if (!PVal.IsValid()) continue;
			const TSharedPtr<FJsonObject>* PObjPtr = nullptr;
			if (!PVal->TryGetObject(PObjPtr) || !PObjPtr || !PObjPtr->IsValid()) continue;

			FParsedProp PP;
			PP.Source = *PObjPtr;
			PP.Source->TryGetStringField(TEXT("propertyName"), PP.Name);
			PP.Source->TryGetStringField(TEXT("propertyType"), PP.Type);
			PP.Source->TryGetStringField(TEXT("value"), PP.Value);
			PP.Source->TryGetBoolField(TEXT("bIsInstancedSubobject"), PP.bInstanced);

			if (PP.bInstanced)
			{
				InstancedProps.Add(MoveTemp(PP));
			}
			else
			{
				ScalarProps.Add(MoveTemp(PP));
			}
		}

		// Determinism: alpha sort by property name within each bucket. Source
		// JSON arrays preserve UE property iteration order, but rendering should
		// match the M5.2 RenderSTPropertiesTable convention.
		auto SortByName = [](TArray<FParsedProp>& V)
		{
			V.Sort([](const FParsedProp& A, const FParsedProp& B)
			{
				return A.Name.Compare(B.Name, ESearchCase::IgnoreCase) < 0;
			});
		};
		SortByName(ScalarProps);
		SortByName(InstancedProps);

		if (ScalarProps.Num() > 0)
		{
			Md += TEXT("| Property | Type | Value |\n");
			Md += TEXT("|---|---|---|\n");
			for (const FParsedProp& PP : ScalarProps)
			{
				const FString ValueCell = PP.Value.IsEmpty()
					? FString(TEXT("—"))
					: FString::Printf(TEXT("`%s`"), *EscTbl(PP.Value));
				Md += FString::Printf(TEXT("| `%s` | `%s` | %s |\n"),
					*EscTbl(PP.Name), *EscTbl(PP.Type), *ValueCell);
			}
			Md += TEXT("\n");
		}
		else if (InstancedProps.Num() == 0)
		{
			Md += TEXT("- _No properties._\n\n");
		}

		// Recurse into nested instanced sub-properties. Each gets its own
		// `[instanced]` heading one level deeper than the enclosing subobject.
		for (const FParsedProp& PP : InstancedProps)
		{
			const int32 NestedHeading = FMath::Min(ClampedLevel + 1, 6);
			const FString NestedHashes = FString::ChrN(NestedHeading, TEXT('#'));
			Md += FString::Printf(TEXT("%s `%s` (`%s`) [instanced]\n\n"),
				*NestedHashes, *EscTbl(PP.Name), *EscTbl(PP.Type));

			const TArray<TSharedPtr<FJsonValue>>* NestedArrayPtr = nullptr;
			if (PP.Source.IsValid()
				&& PP.Source->TryGetArrayField(TEXT("subobjects"), NestedArrayPtr)
				&& NestedArrayPtr
				&& NestedArrayPtr->Num() > 0)
			{
				RenderInstancedSubobjectTree(Md, *NestedArrayPtr,
					FMath::Min(NestedHeading + 1, 6));
			}
			else
			{
				Md += TEXT("- _No subobjects (slot empty or instanced object not captured)._\n\n");
			}
		}
	}

	void RenderInstancedSubobjectTree(
		FString& Md,
		const TArray<TSharedPtr<FJsonValue>>& SubobjectValues,
		int32 HeadingLevel)
	{
		for (const TSharedPtr<FJsonValue>& Val : SubobjectValues)
		{
			if (!Val.IsValid()) continue;
			const TSharedPtr<FJsonObject>* ObjPtr = nullptr;
			if (!Val->TryGetObject(ObjPtr) || !ObjPtr || !ObjPtr->IsValid()) continue;
			RenderInstancedSubobjectEntry(Md, *ObjPtr, HeadingLevel);
		}
	}

	// Walk the SCS tree in authored order (brief §8) and emit each component as
	// a flush-left H3 block. Markdown tables must stay unindented (CommonMark
	// allows 0–3 leading spaces; deeper nesting breaks the table renderer),
	// so hierarchy is carried via a `Parent` line rather than list indentation.
	void RenderComponentBlock(FString& Md, const FExportedComponent& Comp)
	{
		const FString ClassShort = StripScriptPrefix(Comp.ComponentClass);
		Md += FString::Printf(TEXT("### `%s` — `%s`\n\n"),
			*EscTbl(Comp.ComponentName),
			*EscTbl(ClassShort));

		if (Comp.bIsRootComponent)
		{
			Md += TEXT("- Root: yes\n");
		}
		if (!Comp.ParentComponentName.IsEmpty())
		{
			Md += FString::Printf(TEXT("- Parent: `%s`\n"), *EscTbl(Comp.ParentComponentName));
		}
		if (!Comp.AttachSocketName.IsEmpty())
		{
			Md += FString::Printf(TEXT("- Socket: `%s`\n"), *EscTbl(Comp.AttachSocketName));
		}
		Md += FString::Printf(TEXT("- Properties: %d\n\n"), Comp.Properties.Num());

		if (Comp.Properties.Num() > 0)
		{
			TArray<FExportedComponentProperty> Sorted = Comp.Properties;
			Sorted.Sort([](const FExportedComponentProperty& A, const FExportedComponentProperty& B)
			{
				return A.PropertyName.Compare(B.PropertyName, ESearchCase::IgnoreCase) < 0;
			});
			Md += TEXT("| Property | Type | Value |\n");
			Md += TEXT("|---|---|---|\n");
			for (const FExportedComponentProperty& P : Sorted)
			{
				RenderComponentPropertyRow(Md, P);
			}
			Md += TEXT("\n");

			// For instanced subobject properties (UAIPerceptionComponent::SensesConfig,
			// GAS attribute sets, anim layer overrides, etc.), follow the table with the
			// structured `subobjects` JSON tree so AI consumers can read sight radius /
			// hearing range / GA-tag defaults directly from .deep.md instead of
			// dropping into .meta.json. Without this, the property cell only carries
			// the flat ExportTextItem_Direct path blob.
			for (const FExportedComponentProperty& P : Sorted)
			{
				if (!P.bIsInstancedSubobject || P.SubobjectJsonValues.Num() == 0)
				{
					continue;
				}
				Md += FString::Printf(TEXT("#### `%s` (`%s`) — instanced subobjects (%d)\n\n"),
					*EscTbl(P.PropertyName),
					*EscTbl(P.PropertyType),
					P.SubobjectJsonValues.Num());
				RenderInstancedSubobjectTree(Md, P.SubobjectJsonValues, /*HeadingLevel=*/5);
			}
		}
	}

	void RenderComponentTree(FString& Md, const FExportedComponent& Comp)
	{
		RenderComponentBlock(Md, Comp);
		for (const FExportedComponent& Child : Comp.ChildComponents)
		{
			RenderComponentTree(Md, Child);
		}
	}

	// ------- Standard identity/inheritance/variables/refs/metadata -------

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
		// Declaration order per brief §8 — do NOT sort.
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

	void RenderComponents(FString& Md, const FExportedBlueprint& Data)
	{
		Md += FString::Printf(TEXT("## Components (%d)\n\n"), Data.Components.Num());
		if (Data.Components.Num() == 0)
		{
			Md += TEXT("_None (not an Actor Blueprint, or no SCS root)._\n\n");
			return;
		}
		// Components rendered in SCS tree-traversal order (brief §8) — each as a
		// flush-left H3 block. Hierarchy conveyed via `Parent`/`Root` metadata lines.
		for (const FExportedComponent& Root : Data.Components)
		{
			RenderComponentTree(Md, Root);
		}
	}

	// Tier 2 CDO overrides — full property table with the same nested
	// instanced-subobject tree pattern as components. Mirrors
	// `RenderComponentBlock`'s layout so consumers already trained on the
	// component section can parse CDO the same way.
	void RenderCDOSection(FString& Md, const FExportedBlueprint& Data)
	{
		const int32 N = Data.CDOProperties.Num();
		const FString KindLabel = Data.DataCarrierKind.IsEmpty()
			? FString()
			: FString::Printf(TEXT(" — %s"), *Data.DataCarrierKind);
		Md += FString::Printf(TEXT("## Class Default Object (%d)%s\n\n"), N, *KindLabel);

		if (N == 0)
		{
			if (!Data.DataCarrierKind.IsEmpty())
			{
				Md += FString::Printf(TEXT("_No authored CDO overrides. A `%s` Blueprint normally carries its payload here; absence of overrides is a coverage signal, not a renderer bug._\n\n"),
					*Data.DataCarrierKind);
			}
			else
			{
				Md += TEXT("_No authored overrides on inherited properties._\n\n");
			}
			return;
		}

		// Already sorted by PropertyName in the serializer; sort defensively
		// (mirrors RenderComponentBlock's belt-and-suspenders).
		TArray<FExportedComponentProperty> Sorted = Data.CDOProperties;
		Sorted.Sort([](const FExportedComponentProperty& A, const FExportedComponentProperty& B)
		{
			return A.PropertyName.Compare(B.PropertyName, ESearchCase::IgnoreCase) < 0;
		});

		Md += TEXT("| Property | Type | Value |\n");
		Md += TEXT("|---|---|---|\n");
		for (const FExportedComponentProperty& P : Sorted)
		{
			RenderComponentPropertyRow(Md, P);
		}
		Md += TEXT("\n");

		// Full recursive walk of any Instanced / EditInlineNew subobjects —
		// exact same pattern as component rendering so GE components / AbilitySystem
		// attribute sets / anim layer overrides surface with nested property tables.
		for (const FExportedComponentProperty& P : Sorted)
		{
			if (!P.bIsInstancedSubobject || P.SubobjectJsonValues.Num() == 0)
			{
				continue;
			}
			Md += FString::Printf(TEXT("### `%s` (`%s`) — instanced subobjects (%d)\n\n"),
				*EscTbl(P.PropertyName),
				*EscTbl(P.PropertyType),
				P.SubobjectJsonValues.Num());
			RenderInstancedSubobjectTree(Md, P.SubobjectJsonValues, /*HeadingLevel=*/4);
		}
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

	// ------- Widget tree (deep keeps tree identical to Tier 1) -------

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

	// ------- NEW: deep per-node pin dump -------

	using FNodeTitleMap = TMap<FString, FString>;

	// Forward-decl so the recursive state-machine walker can reach it.
	void AddStateMachineTitlesRecursive(const TArray<FExportedStateMachine>& SMs, FNodeTitleMap& Out);

	void AddGraphNodeTitles(const FExportedGraph& G, FNodeTitleMap& Out)
	{
		for (const FExportedNode& N : G.Nodes)
		{
			Out.Add(N.NodeId, N.NodeTitle);
		}
	}

	void AddStateMachineTitlesRecursive(const TArray<FExportedStateMachine>& SMs, FNodeTitleMap& Out)
	{
		for (const FExportedStateMachine& SM : SMs)
		{
			for (const FExportedAnimState& S : SM.States)
			{
				AddGraphNodeTitles(S.AnimGraph, Out);
				AddStateMachineTitlesRecursive(S.NestedStateMachines, Out);
			}
			for (const FExportedAnimTransition& T : SM.Transitions)
			{
				AddGraphNodeTitles(T.RuleGraph, Out);
			}
		}
	}

	// Build a project-wide node-title lookup table once per blueprint so that pin
	// connections referencing nodes in *other* graphs (common in AnimBPs where
	// pose pins cross AnimGraph + function graphs + state graphs) can still
	// resolve the target's title. Per-graph maps leave those lookups as `(?)`.
	void BuildProjectNodeTitleMap(const FExportedBlueprint& Data, FNodeTitleMap& Out)
	{
		AddGraphNodeTitles(Data.EventGraph, Out);
		AddGraphNodeTitles(Data.ConstructionScript, Out);
		for (const FExportedGraph& G : Data.AdditionalGraphs)
		{
			AddGraphNodeTitles(G, Out);
		}
		for (const FExportedFunction& F : Data.Functions)
		{
			AddGraphNodeTitles(F.Graph, Out);
		}
		for (const FExportedFunction& M : Data.Macros)
		{
			AddGraphNodeTitles(M.Graph, Out);
		}
		AddStateMachineTitlesRecursive(Data.StateMachines, Out);
	}

	FString FormatPinConnection(const FExportedPinConnection& C, const FNodeTitleMap& TitleMap)
	{
		const FString* Title = TitleMap.Find(C.NodeId);
		const FString TitleSafe = (Title && !Title->IsEmpty()) ? *Title : FString(TEXT("?"));
		return FString::Printf(TEXT("`%s`:`%s` (%s)"),
			*EscTbl(C.NodeId),
			*EscTbl(C.PinId),
			*EscTbl(TitleSafe));
	}

	void RenderNodeDeep(FString& Md, const FExportedNode& N, const FNodeTitleMap& TitleMap, int32 HeadingLevel)
	{
		const FString Hashes = FString::ChrN(FMath::Clamp(HeadingLevel, 1, 6), TEXT('#'));
		Md += FString::Printf(TEXT("%s `%s` — `%s` (`%s`)\n\n"),
			*Hashes,
			N.NodeTitle.IsEmpty() ? TEXT("(unnamed)") : *EscTbl(N.NodeTitle),
			*StripScriptPrefix(N.NodeClass),
			*EscTbl(N.NodeId));

		Md += FString::Printf(TEXT("- Position: (%d, %d)\n"), N.PositionX, N.PositionY);
		if (!N.NodeType.IsEmpty())
		{
			Md += FString::Printf(TEXT("- Node type: `%s`\n"), *EscTbl(N.NodeType));
		}
		if (!N.Comment.IsEmpty())
		{
			Md += FString::Printf(TEXT("- Comment: %s\n"), *EscTbl(N.Comment));
		}

		if (N.Pins.Num() == 0)
		{
			Md += TEXT("- Pins: _none_\n\n");
			return;
		}

		Md += FString::Printf(TEXT("- Pins (%d):\n\n"), N.Pins.Num());
		Md += TEXT("| Dir | Name | Type | Default | Flags | Connections |\n");
		Md += TEXT("|---|---|---|---|---|---|\n");

		// Pins preserve index order per brief §8.
		for (const FExportedPin& P : N.Pins)
		{
			const TCHAR* DirStr = (P.Direction == EExportPinDirection::Output) ? TEXT("Out") : TEXT("In");
			const FString Type = EscTbl(FormatPinType(P.PinType));
			const FString PinName = P.PinName.IsEmpty()
				? (P.PinFriendlyName.IsEmpty() ? FString(TEXT("(unnamed)")) : P.PinFriendlyName)
				: P.PinName;

			FString Default;
			if (!P.DefaultValue.IsEmpty())
			{
				Default = FString::Printf(TEXT("`%s`"), *EscTbl(P.DefaultValue));
			}
			else if (!P.AutogeneratedDefaultValue.IsEmpty())
			{
				Default = FString::Printf(TEXT("`%s` _(auto)_"), *EscTbl(P.AutogeneratedDefaultValue));
			}
			else
			{
				Default = TEXT("—");
			}

			TArray<FString> FlagBits;
			if (P.bHidden)         FlagBits.Add(TEXT("Hidden"));
			if (P.bNotConnectable) FlagBits.Add(TEXT("NotConnectable"));
			if (P.bAdvancedView)   FlagBits.Add(TEXT("Advanced"));
			if (P.bHasError)       FlagBits.Add(TEXT("Error"));
			const FString Flags = FlagBits.Num() == 0 ? TEXT("—") : FString::Join(FlagBits, TEXT(", "));

			// Connections sorted by (target NodeId, PinId) — brief §8 prescription
			// (GUIDs are not in Markdown; NodeId is the stable text equivalent).
			TArray<FExportedPinConnection> Conns = P.Connections;
			Conns.Sort([](const FExportedPinConnection& A, const FExportedPinConnection& B)
			{
				const int32 Cmp = A.NodeId.Compare(B.NodeId, ESearchCase::IgnoreCase);
				if (Cmp != 0) return Cmp < 0;
				return A.PinId.Compare(B.PinId, ESearchCase::IgnoreCase) < 0;
			});

			FString ConnStr;
			if (Conns.Num() == 0)
			{
				ConnStr = TEXT("—");
			}
			else
			{
				TArray<FString> Parts;
				Parts.Reserve(Conns.Num());
				for (const FExportedPinConnection& C : Conns)
				{
					Parts.Add(FormatPinConnection(C, TitleMap));
				}
				ConnStr = FString::Join(Parts, TEXT("; "));
			}

			Md += FString::Printf(TEXT("| %s | `%s` | `%s` | %s | %s | %s |\n"),
				DirStr,
				*EscTbl(PinName),
				*Type,
				*Default,
				*EscTbl(Flags),
				*ConnStr);
		}
		Md += TEXT("\n");
	}

	void RenderGraphDeep(FString& Md, const FExportedGraph& G, const TCHAR* Label,
		const FNodeTitleMap& TitleMap, int32 HeadingLevel = 3)
	{
		const int32 ClampedGraphLevel = FMath::Clamp(HeadingLevel, 1, 6);
		const FString GraphHashes = FString::ChrN(ClampedGraphLevel, TEXT('#'));
		const FString Name = G.GraphName.IsEmpty() ? FString(TEXT("(unnamed)")) : G.GraphName;
		const FString Type = G.GraphType.IsEmpty() ? FString() : FString::Printf(TEXT(" [%s]"), *G.GraphType);

		Md += FString::Printf(TEXT("%s %s: `%s`%s (%d nodes)\n\n"),
			*GraphHashes,
			Label,
			*EscTbl(Name),
			*Type,
			G.Nodes.Num());

		if (!G.SchemaClass.IsEmpty())
		{
			Md += FString::Printf(TEXT("- Schema: `%s`\n\n"), *EscTbl(G.SchemaClass));
		}

		if (G.Nodes.Num() == 0)
		{
			Md += TEXT("_Empty graph._\n\n");
			return;
		}

		// Nodes sorted by NodeId for determinism. The NodeId is the stable
		// content-hash-derived ID (M6.1); stable across repeat runs as long as
		// the Blueprint itself hasn't changed.
		TArray<FExportedNode> Sorted = G.Nodes;
		Sorted.Sort([](const FExportedNode& A, const FExportedNode& B)
		{
			return A.NodeId.Compare(B.NodeId, ESearchCase::IgnoreCase) < 0;
		});

		// Node headings sit one level deeper than their enclosing graph so
		// Markdown readers render them as children, not siblings. Markdown
		// supports at most H6; clamp to prevent overflow when a deeply-nested
		// state machine pushes us past that.
		const int32 NodeHeading = FMath::Min(ClampedGraphLevel + 1, 6);

		for (const FExportedNode& N : Sorted)
		{
			RenderNodeDeep(Md, N, TitleMap, NodeHeading);
		}
	}

	void RenderGraphsDeep(FString& Md, const FExportedBlueprint& Data, const FNodeTitleMap& TitleMap)
	{
		Md += TEXT("## Graphs (deep)\n\n");
		RenderGraphDeep(Md, Data.EventGraph,         TEXT("Event graph"),         TitleMap, /*HeadingLevel=*/3);
		RenderGraphDeep(Md, Data.ConstructionScript, TEXT("Construction script"), TitleMap, /*HeadingLevel=*/3);

		if (Data.AdditionalGraphs.Num() == 0)
		{
			Md += TEXT("### Additional graphs\n\n_None._\n\n");
			return;
		}
		Md += FString::Printf(TEXT("### Additional graphs (%d)\n\n"), Data.AdditionalGraphs.Num());
		TArray<FExportedGraph> Sorted = Data.AdditionalGraphs;
		Sorted.Sort([](const FExportedGraph& A, const FExportedGraph& B)
		{
			return A.GraphName.Compare(B.GraphName, ESearchCase::IgnoreCase) < 0;
		});
		for (const FExportedGraph& G : Sorted)
		{
			RenderGraphDeep(Md, G, TEXT("Graph"), TitleMap, /*HeadingLevel=*/4);
		}
	}

	void RenderFunctionsDeep(FString& Md, const TCHAR* Heading, const TArray<FExportedFunction>& Source,
		const FNodeTitleMap& TitleMap)
	{
		Md += FString::Printf(TEXT("## %s (%d) — deep\n\n"), Heading, Source.Num());
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

			if (!F.Category.IsEmpty())
			{
				Md += FString::Printf(TEXT("- Category: `%s`\n"), *F.Category);
			}
			if (!F.Description.IsEmpty())
			{
				Md += FString::Printf(TEXT("- Description: %s\n"), *EscTbl(F.Description));
			}
			Md += TEXT("\n");

			RenderGraphDeep(Md, F.Graph, TEXT("Graph"), TitleMap, /*HeadingLevel=*/4);
		}
	}

	// ------- State machines: Tier 2 inlines each state's AnimGraph + each transition's RuleGraph -------

	void RenderStateMachineDeep(FString& Md, const FExportedStateMachine& SM,
		const FNodeTitleMap& TitleMap, int32 HeadingLevel);

	void RenderStateMachineListDeep(FString& Md, const TArray<FExportedStateMachine>& Machines,
		const FNodeTitleMap& TitleMap, int32 HeadingLevel)
	{
		TArray<FExportedStateMachine> Sorted = Machines;
		Sorted.Sort([](const FExportedStateMachine& A, const FExportedStateMachine& B)
		{
			return A.MachineName.Compare(B.MachineName, ESearchCase::IgnoreCase) < 0;
		});
		for (const FExportedStateMachine& SM : Sorted)
		{
			RenderStateMachineDeep(Md, SM, TitleMap, HeadingLevel);
		}
	}

	void RenderStateMachineDeep(FString& Md, const FExportedStateMachine& SM,
		const FNodeTitleMap& TitleMap, int32 HeadingLevel)
	{
		const FString Hashes = FString::ChrN(HeadingLevel, TEXT('#'));
		Md += FString::Printf(TEXT("%s Machine: `%s` (%d states, %d transitions)\n\n"),
			*Hashes,
			SM.MachineName.IsEmpty() ? TEXT("(unnamed)") : *EscTbl(SM.MachineName),
			SM.States.Num(),
			SM.Transitions.Num());

		// States — alpha-sorted; each state embeds its full AnimGraph dump.
		TArray<FExportedAnimState> SortedStates = SM.States;
		SortedStates.Sort([](const FExportedAnimState& A, const FExportedAnimState& B)
		{
			return A.StateName.Compare(B.StateName, ESearchCase::IgnoreCase) < 0;
		});

		const int32 StateHeading = FMath::Min(HeadingLevel + 1, 6);
		const FString StateHashes = FString::ChrN(StateHeading, TEXT('#'));
		for (const FExportedAnimState& S : SortedStates)
		{
			const FString TypeLabel = S.StateType.IsEmpty()
				? FString()
				: FString::Printf(TEXT(" [%s]"), *S.StateType);
			Md += FString::Printf(TEXT("%s State: `%s`%s\n\n"),
				*StateHashes,
				S.StateName.IsEmpty() ? TEXT("(unnamed)") : *EscTbl(S.StateName),
				*TypeLabel);

			RenderGraphDeep(Md, S.AnimGraph, TEXT("AnimGraph"),
				TitleMap, /*HeadingLevel=*/FMath::Min(StateHeading + 1, 6));

			if (S.NestedStateMachines.Num() > 0)
			{
				Md += FString::Printf(TEXT("%s# Nested state machines (%d)\n\n"),
					*StateHashes, S.NestedStateMachines.Num());
				RenderStateMachineListDeep(Md, S.NestedStateMachines,
					TitleMap, FMath::Min(StateHeading + 2, 6));
			}
		}

		// Transitions — source → target, alpha-sorted by source then target.
		TArray<FExportedAnimTransition> SortedTrans = SM.Transitions;
		SortedTrans.Sort([](const FExportedAnimTransition& A, const FExportedAnimTransition& B)
		{
			const int32 Cmp = A.SourceState.Compare(B.SourceState, ESearchCase::IgnoreCase);
			if (Cmp != 0) return Cmp < 0;
			return A.TargetState.Compare(B.TargetState, ESearchCase::IgnoreCase) < 0;
		});

		for (const FExportedAnimTransition& T : SortedTrans)
		{
			Md += FString::Printf(TEXT("%s Transition: `%s` → `%s`\n\n"),
				*StateHashes,
				T.SourceState.IsEmpty() ? TEXT("(entry)") : *EscTbl(T.SourceState),
				T.TargetState.IsEmpty() ? TEXT("(none)") : *EscTbl(T.TargetState));

			Md += FString::Printf(TEXT("- Logic: `%s`\n"),
				T.BlendSettings.LogicType.IsEmpty()
					? TEXT("—")
					: *EscTbl(T.BlendSettings.LogicType));
			if (T.BlendSettings.CrossfadeDuration > 0.0f)
			{
				Md += FString::Printf(TEXT("- Crossfade: %.3fs (%s, %s)\n"),
					T.BlendSettings.CrossfadeDuration,
					T.BlendSettings.BlendMode.IsEmpty() ? TEXT("—") : *EscTbl(T.BlendSettings.BlendMode),
					T.BlendSettings.CrossfadeMode.IsEmpty() ? TEXT("—") : *EscTbl(T.BlendSettings.CrossfadeMode));
			}
			Md += FString::Printf(TEXT("- Priority: %d\n"), T.BlendSettings.PriorityOrder);
			if (T.BlendSettings.bAutomaticRuleBasedOnSequencePlayer)
			{
				Md += TEXT("- Automatic rule based on sequence player: yes\n");
			}
			Md += TEXT("\n");

			RenderGraphDeep(Md, T.RuleGraph, TEXT("Rule graph"),
				TitleMap, /*HeadingLevel=*/FMath::Min(StateHeading + 1, 6));
		}
	}

	void RenderStateMachinesDeep(FString& Md, const FExportedBlueprint& Data, const FNodeTitleMap& TitleMap)
	{
		if (Data.BlueprintSubclass != TEXT("AnimBlueprint"))
		{
			return;
		}
		Md += TEXT("## State Machines (deep)\n\n");
		if (Data.StateMachines.Num() == 0)
		{
			Md += TEXT("_No authored state machines (single-graph anim blueprint)._\n\n");
			return;
		}
		RenderStateMachineListDeep(Md, Data.StateMachines, TitleMap, /*HeadingLevel=*/3);
	}

	// ===================================================================
	// StateTree Tier 2
	// ===================================================================

	FString FormatStateType(EExportedStateTreeStateType T)
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

	FString FormatSelectionBehavior(EExportedStateTreeSelectionBehavior B)
	{
		switch (B)
		{
			case EExportedStateTreeSelectionBehavior::None:                     return TEXT("None");
			case EExportedStateTreeSelectionBehavior::TryEnterState:            return TEXT("TryEnterState");
			case EExportedStateTreeSelectionBehavior::TrySelectChildrenInOrder: return TEXT("TrySelectChildrenInOrder");
			case EExportedStateTreeSelectionBehavior::TryFollowTransitions:    return TEXT("TryFollowTransitions");
			default:                                                            return TEXT("Unknown");
		}
	}

	FString FormatTransitionTrigger(EExportedStateTreeTransitionTrigger T)
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

	// Drop UE plumbing properties that leak through TFieldIterator on
	// BP-backed instance objects (UStateTreeTaskBlueprintBase subclasses).
	bool IsUObjectPlumbingProperty(const FString& Name)
	{
		return Name == TEXT("UberGraphFrame")
			|| Name == TEXT("CachedFrameStateTree");
	}

	void RenderSTPropertiesTable(FString& Md, const TCHAR* Label,
		const TArray<FExportedStateTreeProperty>& Props,
		bool bStripUObjectPlumbing = false)
	{
		TArray<FExportedStateTreeProperty> Filtered;
		Filtered.Reserve(Props.Num());
		for (const FExportedStateTreeProperty& P : Props)
		{
			if (bStripUObjectPlumbing && IsUObjectPlumbingProperty(P.Name))
			{
				continue;
			}
			Filtered.Add(P);
		}

		if (Filtered.Num() == 0)
		{
			Md += FString::Printf(TEXT("- %s: _none_\n\n"), Label);
			return;
		}
		Md += FString::Printf(TEXT("- %s (%d):\n\n"), Label, Filtered.Num());
		Md += TEXT("| Name | Type | Value |\n");
		Md += TEXT("|---|---|---|\n");
		Filtered.Sort([](const FExportedStateTreeProperty& A, const FExportedStateTreeProperty& B)
		{
			return A.Name.Compare(B.Name, ESearchCase::IgnoreCase) < 0;
		});
		for (const FExportedStateTreeProperty& P : Filtered)
		{
			const FString Value = P.Value.IsEmpty()
				? FString(TEXT("—"))
				: FString::Printf(TEXT("`%s`"), *EscTbl(P.Value));
			Md += FString::Printf(TEXT("| `%s` | `%s` | %s |\n"),
				*EscTbl(P.Name),
				*EscTbl(P.Type),
				*Value);
		}
		Md += TEXT("\n");
	}

	void RenderSTEditorNodeDeep(FString& Md, const FExportedStateTreeEditorNode& N, int32 HeadingLevel)
	{
		const FString Hashes = FString::ChrN(FMath::Clamp(HeadingLevel, 1, 6), TEXT('#'));

		FString Title = N.Name.IsEmpty() ? FString(TEXT("(unnamed)")) : N.Name;
		if (!N.InstanceObjectClass.IsEmpty())
		{
			Title = FString::Printf(TEXT("%s — `%s`"),
				*Title,
				*ShortClassName(N.InstanceObjectClass));
		}
		Md += FString::Printf(TEXT("%s %s\n\n"), *Hashes, *EscTbl(Title));

		Md += FString::Printf(TEXT("- Category: `%s`\n"),
			N.Category.IsEmpty() ? TEXT("—") : *EscTbl(N.Category));
		if (!N.StructType.IsEmpty())
		{
			Md += FString::Printf(TEXT("- Node struct: `%s`\n"), *EscTbl(N.StructType));
		}
		if (!N.InstanceObjectClass.IsEmpty())
		{
			Md += FString::Printf(TEXT("- Instance class: `%s`\n"), *EscTbl(N.InstanceObjectClass));
		}
		if (!N.InstanceId.IsEmpty())
		{
			Md += FString::Printf(TEXT("- Instance ID: `%s`\n"), *EscTbl(N.InstanceId));
		}
		Md += TEXT("\n");

		RenderSTPropertiesTable(Md, TEXT("Node struct properties"), N.Properties);
		RenderSTPropertiesTable(Md, TEXT("Instance data properties"), N.InstanceProperties);
		RenderSTPropertiesTable(Md, TEXT("Instance object properties"),
			N.InstanceObjectProperties, /*bStripUObjectPlumbing=*/true);
	}

	void RenderSTTransitionDeep(FString& Md, const FExportedStateTreeTransition& T, int32 HeadingLevel)
	{
		const FString Hashes = FString::ChrN(FMath::Clamp(HeadingLevel, 1, 6), TEXT('#'));
		const FString Trigger = FormatTransitionTrigger(T.Trigger);
		const FString Target = T.TargetStateName.IsEmpty() ? FString(TEXT("(unset)")) : T.TargetStateName;

		Md += FString::Printf(TEXT("%s Transition: `%s` → `%s`\n\n"),
			*Hashes, *EscTbl(Trigger), *EscTbl(Target));

		if (!T.EventTag.IsEmpty())
		{
			Md += FString::Printf(TEXT("- Event tag: `%s`\n"), *EscTbl(T.EventTag));
		}
		if (!T.TargetStateGuid.IsEmpty())
		{
			Md += FString::Printf(TEXT("- Target GUID: `%s`\n"), *EscTbl(T.TargetStateGuid));
		}
		// LinkType carries the semantic distinction that target-name alone can't.
		// Only emit for non-GotoState — a plain state-named target implies GotoState.
		if (!T.LinkType.IsEmpty() && T.LinkType != TEXT("GotoState"))
		{
			Md += FString::Printf(TEXT("- Link type: `%s`\n"), *EscTbl(T.LinkType));
		}
		if (!T.Priority.IsEmpty())
		{
			Md += FString::Printf(TEXT("- Priority: `%s`\n"), *EscTbl(T.Priority));
		}
		if (T.DelaySeconds > 0.0f)
		{
			const FString RandPart = T.bDelayIsRandom
				? FString::Printf(TEXT(" ± %.3fs"), T.DelayRandomDeviationSeconds)
				: FString();
			Md += FString::Printf(TEXT("- Delay: %.3fs%s\n"), T.DelaySeconds, *RandPart);
		}
		Md += FString::Printf(TEXT("- Transition ID: `%s`\n\n"), *EscTbl(T.TransitionId));

		if (T.Conditions.Num() == 0)
		{
			Md += TEXT("Conditions: _none_ (fires unconditionally on trigger)\n\n");
			return;
		}
		const int32 CondHeading = FMath::Min(HeadingLevel + 1, 6);
		Md += FString::Printf(TEXT("Conditions (%d):\n\n"), T.Conditions.Num());
		for (const FExportedStateTreeEditorNode& C : T.Conditions)
		{
			RenderSTEditorNodeDeep(Md, C, CondHeading);
		}
	}

	void RenderSTStateDeep(FString& Md, const FExportedStateTreeState& State, int32 HeadingLevel)
	{
		const int32 ClampedHeading = FMath::Clamp(HeadingLevel, 1, 6);
		const FString Hashes = FString::ChrN(ClampedHeading, TEXT('#'));

		Md += FString::Printf(TEXT("%s `%s` [%s]\n\n"),
			*Hashes,
			State.Name.IsEmpty() ? TEXT("(unnamed)") : *EscTbl(State.Name),
			*FormatStateType(State.Type));

		if (!State.StateGuid.IsEmpty())
		{
			Md += FString::Printf(TEXT("- State GUID: `%s`\n"), *EscTbl(State.StateGuid));
		}
		Md += FString::Printf(TEXT("- Selection: `%s`\n"),
			*FormatSelectionBehavior(State.SelectionBehavior));
		if (!State.Tag.IsEmpty())
		{
			Md += FString::Printf(TEXT("- Tag: `%s`\n"), *EscTbl(State.Tag));
		}
		if (!State.LinkedAsset.IsEmpty())
		{
			Md += FString::Printf(TEXT("- Linked subtree: `%s`\n"), *EscTbl(State.LinkedAsset));
		}
		if (!State.LinkedAssetPath.IsEmpty())
		{
			Md += FString::Printf(TEXT("- Linked tree asset: `%s`\n"), *EscTbl(State.LinkedAssetPath));
		}
		Md += TEXT("\n");

		const int32 ChildHeading = FMath::Min(ClampedHeading + 1, 6);

		if (State.EnterConditions.Num() > 0)
		{
			Md += FString::Printf(TEXT("%s Enter conditions (%d)\n\n"),
				*FString::ChrN(ChildHeading, TEXT('#')),
				State.EnterConditions.Num());
			const int32 NodeHeading = FMath::Min(ChildHeading + 1, 6);
			for (const FExportedStateTreeEditorNode& C : State.EnterConditions)
			{
				RenderSTEditorNodeDeep(Md, C, NodeHeading);
			}
		}

		if (State.Tasks.Num() > 0)
		{
			Md += FString::Printf(TEXT("%s Tasks (%d)\n\n"),
				*FString::ChrN(ChildHeading, TEXT('#')),
				State.Tasks.Num());
			const int32 NodeHeading = FMath::Min(ChildHeading + 1, 6);
			for (const FExportedStateTreeEditorNode& T : State.Tasks)
			{
				RenderSTEditorNodeDeep(Md, T, NodeHeading);
			}
		}

		if (State.Transitions.Num() > 0)
		{
			Md += FString::Printf(TEXT("%s Transitions (%d)\n\n"),
				*FString::ChrN(ChildHeading, TEXT('#')),
				State.Transitions.Num());
			TArray<FExportedStateTreeTransition> Sorted = State.Transitions;
			Sorted.Sort([](const FExportedStateTreeTransition& A, const FExportedStateTreeTransition& B)
			{
				return A.TransitionId.Compare(B.TransitionId, ESearchCase::IgnoreCase) < 0;
			});
			const int32 TransHeading = FMath::Min(ChildHeading + 1, 6);
			for (const FExportedStateTreeTransition& T : Sorted)
			{
				RenderSTTransitionDeep(Md, T, TransHeading);
			}
		}

		if (State.Children.Num() > 0)
		{
			Md += FString::Printf(TEXT("%s Children (%d)\n\n"),
				*FString::ChrN(ChildHeading, TEXT('#')),
				State.Children.Num());
			// Children preserve author order — sibling execution order is
			// semantically load-bearing for selection behaviour.
			for (const FExportedStateTreeState& Child : State.Children)
			{
				RenderSTStateDeep(Md, Child, FMath::Min(ChildHeading + 1, 6));
			}
		}
	}

	void RenderSTIdentity(FString& Md, const FExportedStateTree& Data)
	{
		Md += TEXT("## Identity\n\n");
		Md += TEXT("| Field | Value |\n");
		Md += TEXT("|---|---|\n");
		Md += FString::Printf(TEXT("| Asset path | `%s` |\n"), *EscTbl(Data.AssetPath));
		Md += FString::Printf(TEXT("| Asset name | `%s` |\n"), *EscTbl(Data.AssetName));
		Md += FString::Printf(TEXT("| Asset type | `StateTree` |\n"));
		Md += FString::Printf(TEXT("| Schema | `%s` |\n"),
			Data.Schema.IsEmpty() ? TEXT("—") : *EscTbl(Data.Schema));
		Md += FString::Printf(TEXT("| Engine version | `%s` |\n"),
			*EscTbl(Data.ExportInfo.EngineVersion));
		Md += FString::Printf(TEXT("| Plugin version | `%s` |\n"),
			*EscTbl(Data.ExportInfo.PluginVersion));
		Md += TEXT("\n");
	}

	int32 CountStatesRecursive(const FExportedStateTreeState& S)
	{
		int32 N = 1;
		for (const FExportedStateTreeState& C : S.Children)
		{
			N += CountStatesRecursive(C);
		}
		return N;
	}

	void RenderSTSummary(FString& Md, const FExportedStateTree& Data)
	{
		int32 TotalStates = 0;
		for (const FExportedStateTreeState& R : Data.RootStates)
		{
			TotalStates += CountStatesRecursive(R);
		}
		Md += TEXT("## Summary\n\n");
		Md += FString::Printf(TEXT("- Root states: **%d**\n"), Data.RootStates.Num());
		Md += FString::Printf(TEXT("- Total states (incl. nested): **%d**\n"), TotalStates);
		Md += FString::Printf(TEXT("- Global evaluators: **%d**\n"), Data.Evaluators.Num());
		Md += FString::Printf(TEXT("- Global tasks: **%d**\n"), Data.GlobalTasks.Num());
		Md += FString::Printf(TEXT("- Property bindings: **%d**\n"), Data.Bindings.Num());
		Md += TEXT("\n");
	}

	void RenderSTBindings(FString& Md, const FExportedStateTree& Data)
	{
		Md += FString::Printf(TEXT("## Property Bindings (%d)\n\n"), Data.Bindings.Num());
		if (Data.Bindings.Num() == 0)
		{
			Md += TEXT("_No bindings (tasks rely on default / parameter-bag inputs only)._\n\n");
			return;
		}
		Md += TEXT("| Source | Target |\n");
		Md += TEXT("|---|---|\n");
		TArray<FExportedStateTreeBinding> Sorted = Data.Bindings;
		Sorted.Sort([](const FExportedStateTreeBinding& A, const FExportedStateTreeBinding& B)
		{
			if (A.TargetPath != B.TargetPath) return A.TargetPath < B.TargetPath;
			return A.SourcePath < B.SourcePath;
		});
		for (const FExportedStateTreeBinding& B : Sorted)
		{
			const FString Src = B.SourcePath.IsEmpty()
				? FString(TEXT("_(default / parent scope)_"))
				: FString::Printf(TEXT("`%s`"), *EscTbl(B.SourcePath));
			Md += FString::Printf(TEXT("| %s | `%s` |\n"), *Src, *EscTbl(B.TargetPath));
		}
		Md += TEXT("\n");
	}

	void RenderSTGlobalNodes(FString& Md, const TCHAR* Heading,
		const TArray<FExportedStateTreeEditorNode>& Nodes)
	{
		Md += FString::Printf(TEXT("## %s (%d)\n\n"), Heading, Nodes.Num());
		if (Nodes.Num() == 0)
		{
			Md += TEXT("_None._\n\n");
			return;
		}
		for (const FExportedStateTreeEditorNode& N : Nodes)
		{
			RenderSTEditorNodeDeep(Md, N, /*HeadingLevel=*/3);
		}
	}

	void RenderSTStates(FString& Md, const FExportedStateTree& Data)
	{
		Md += FString::Printf(TEXT("## States (%d root)\n\n"), Data.RootStates.Num());
		if (Data.RootStates.Num() == 0)
		{
			Md += TEXT("_Empty state tree._\n\n");
			return;
		}
		// Root states preserve author order.
		for (const FExportedStateTreeState& R : Data.RootStates)
		{
			RenderSTStateDeep(Md, R, /*HeadingLevel=*/3);
		}
	}

	void RenderSTReferences(FString& Md, const FExportedStateTree& Data)
	{
		Md += TEXT("## References\n\n");
		if (Data.Dependencies.Num() == 0)
		{
			Md += TEXT("_None._\n\n");
			return;
		}
		TArray<FExportedDependency> Sorted = Data.Dependencies;
		Sorted.Sort([](const FExportedDependency& A, const FExportedDependency& B)
		{
			return A.AssetPath.Compare(B.AssetPath, ESearchCase::IgnoreCase) < 0;
		});
		for (const FExportedDependency& D : Sorted)
		{
			const FString Kind = D.bIsBlueprint ? TEXT("Blueprint")
				: (D.bIsNativeClass ? TEXT("native") : TEXT("asset"));
			Md += FString::Printf(TEXT("- `%s` [%s]\n"), *D.AssetPath, *Kind);
		}
		Md += TEXT("\n");
	}
}

namespace BlueprintExporter::DeepDump
{
	FString RenderBlueprintMarkdown(const FExportedBlueprint& Data)
	{
		FString Md;
		Md.Reserve(64 * 1024);
		Md += FString::Printf(TEXT("# %s — Deep Dump (Tier 2)\n\n"), *Data.AssetName);
		Md += TEXT("> Generated by `DeepDump` commandlet. Complementary to the Tier 1 `.md` summary ");
		Md += TEXT("written by `ProjectInventory`; this file adds per-graph, per-node, per-pin detail.\n\n");

		// Build the project-wide node title lookup once so pin connections can
		// resolve target titles even when they cross graph boundaries (M5.1 fix).
		FNodeTitleMap TitleMap;
		BuildProjectNodeTitleMap(Data, TitleMap);

		RenderIdentity(Md, Data);
		RenderInheritance(Md, Data);
		RenderVariables(Md, Data);
		RenderComponents(Md, Data);
		RenderCDOSection(Md, Data);
		RenderFunctionsDeep(Md, TEXT("Functions"), Data.Functions, TitleMap);
		RenderFunctionsDeep(Md, TEXT("Macros"), Data.Macros, TitleMap);
		RenderGraphsDeep(Md, Data, TitleMap);
		RenderStateMachinesDeep(Md, Data, TitleMap);
		RenderWidgetTree(Md, Data);
		RenderReferences(Md, Data);
		RenderMetadata(Md, Data);
		return Md;
	}

	FString RenderStateTreeMarkdown(const FExportedStateTree& Data)
	{
		FString Md;
		Md.Reserve(32 * 1024);
		Md += FString::Printf(TEXT("# %s — Deep Dump (Tier 2)\n\n"), *Data.AssetName);
		Md += TEXT("> Generated by `DeepDump` commandlet for a StateTree asset. ");
		Md += TEXT("Complementary to the Tier 1 summary; adds full per-node property ");
		Md += TEXT("detail (node struct + instance data + instance object) and the ");
		Md += TEXT("complete property-bindings table.\n\n");

		RenderSTIdentity(Md, Data);
		RenderSTSummary(Md, Data);
		RenderSTBindings(Md, Data);
		RenderSTGlobalNodes(Md, TEXT("Global Evaluators"), Data.Evaluators);
		RenderSTGlobalNodes(Md, TEXT("Global Tasks"), Data.GlobalTasks);
		RenderSTStates(Md, Data);
		RenderSTReferences(Md, Data);
		return Md;
	}

	FString RenderOutOfScopeNotice(
		const FString& AssetName,
		const FString& PackagePath,
		const FString& ClassName)
	{
		FString Notice;
		Notice.Reserve(1024);
		Notice += FString::Printf(TEXT("# %s — Deep Dump (Tier 2)\n\n"), *AssetName);
		Notice += FString::Printf(TEXT("Class `%s` is out of scope for the current DeepDump set.\n\n"),
			*ClassName);
		Notice += TEXT("Supported classes: UBlueprint-family (`Blueprint`, `AnimBlueprint`, ");
		Notice += TEXT("`WidgetBlueprint`, `ControlRigBlueprint`), `StateTree`, `SmartObjectDefinition`, ");
		Notice += TEXT("`BehaviorTree`, `DataTable`, `ChooserTable`, `EnvQuery`, and `DataAsset` instances. For other logic-");
		Notice += TEXT("bearing classes, the Tier 1 `.md` + `.meta.json` already carry the typed handler's full authored shape.\n\n");
		Notice += FString::Printf(TEXT("- Asset path: `%s`\n"), *PackagePath);
		Notice += FString::Printf(TEXT("- Class: `%s`\n"), *ClassName);
		return Notice;
	}

	FString RenderDataAssetInstanceMarkdown(UObject* Asset)
	{
		FString Md;
		Md.Reserve(16 * 1024);

		if (!Asset)
		{
			Md += TEXT("# (null) — DataAsset Instance Deep Dump (Tier 2)\n\n");
			Md += TEXT("_Asset pointer was null at render time._\n");
			return Md;
		}

		UClass* AssetClass = Asset->GetClass();
		UObject* ClassCDO = AssetClass ? AssetClass->GetDefaultObject() : nullptr;

		Md += FString::Printf(TEXT("# %s — DataAsset Instance Deep Dump (Tier 2)\n\n"), *Asset->GetName());
		Md += TEXT("> Tier 2 dump of a saved `.uasset` instance. Values are diffed against the ");
		Md += TEXT("instance's own class CDO, so only authored overrides appear. Complements the ");
		Md += TEXT("class-shape `.md` / `.meta.json` at the BP definition's path.\n\n");

		Md += TEXT("## Identity\n\n");
		Md += TEXT("| Field | Value |\n");
		Md += TEXT("|---|---|\n");
		Md += FString::Printf(TEXT("| Asset path | `%s` |\n"), *EscTbl(Asset->GetPathName()));
		Md += FString::Printf(TEXT("| Asset name | `%s` |\n"), *EscTbl(Asset->GetName()));
		if (AssetClass)
		{
			Md += FString::Printf(TEXT("| Asset class | `%s` |\n"), *EscTbl(AssetClass->GetPathName()));
			UClass* ParentClass = AssetClass->GetSuperClass();
			if (ParentClass)
			{
				Md += FString::Printf(TEXT("| Parent class | `%s` |\n"), *EscTbl(ParentClass->GetPathName()));
			}
		}
		Md += TEXT("\n");

		// Collect non-default properties. Matches the M19.1 SerializeCDOProperties
		// pattern, but with "class CDO" as the reference instead of "parent class CDO" —
		// this is the instance-vs-class diff, not the class-vs-parent diff.
		static const TSet<FName> PlumbingNames = {
			FName(TEXT("UberGraphFrame")),
			FName(TEXT("CachedFrameStateTree")),
		};

		struct FPropEntry
		{
			FString Name;
			FString Type;
			FString Value;
		};
		TArray<FPropEntry> Entries;

		if (AssetClass)
		{
			for (TFieldIterator<FProperty> PropIt(AssetClass); PropIt; ++PropIt)
			{
				FProperty* Property = *PropIt;
				if (!Property) continue;
				if (Property->HasAnyPropertyFlags(CPF_Transient | CPF_DuplicateTransient)) continue;
				if (PlumbingNames.Contains(Property->GetFName())) continue;

				const void* CurrentValue = Property->ContainerPtrToValuePtr<void>(Asset);
				const void* DefaultValue = ClassCDO ? Property->ContainerPtrToValuePtr<void>(ClassCDO) : nullptr;

				// If the class CDO is null we over-report rather than silently drop
				// (brief §8 / "never guess values").
				if (DefaultValue && Property->Identical(CurrentValue, DefaultValue)) continue;

				FString ValueStr;
				Property->ExportTextItem_Direct(ValueStr, CurrentValue, DefaultValue, Asset, PPF_None);

				Entries.Add({ Property->GetName(), Property->GetCPPType(), MoveTemp(ValueStr) });
			}
		}

		Entries.Sort([](const FPropEntry& A, const FPropEntry& B) { return A.Name < B.Name; });

		Md += FString::Printf(TEXT("## Instance Overrides (%d)\n\n"), Entries.Num());
		if (Entries.Num() == 0)
		{
			Md += TEXT("_This instance's UPROPERTY values are identical to its class CDO. The class-authored defaults ARE the instance — no per-asset overrides were made after saving._\n");
			return Md;
		}
		Md += TEXT("| Property | Type | Value |\n");
		Md += TEXT("|---|---|---|\n");
		for (const FPropEntry& E : Entries)
		{
			Md += FString::Printf(TEXT("| `%s` | `%s` | `%s` |\n"),
				*EscTbl(E.Name),
				*EscTbl(E.Type),
				*EscTbl(E.Value));
		}
		Md += TEXT("\n");

		return Md;
	}
}
