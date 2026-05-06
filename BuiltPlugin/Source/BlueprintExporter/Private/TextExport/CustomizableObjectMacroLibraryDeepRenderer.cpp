// Copyright 10 Chambers. All Rights Reserved.

#include "TextExport/CustomizableObjectMacroLibraryDeepRenderer.h"
#include "TextExport/DeepDumpRenderer.h"
#include "TextExport/DeepRenderShared.h"

#include "UObject/Object.h"
#include "UObject/UnrealType.h"
#include "UObject/Class.h"
#include "EdGraph/EdGraph.h"

// M29.6.4 — no WITH_MUTABLE_SUPPORT gate. The renderer was already written
// zero-include via class-name dispatch + UPROPERTY-by-name reflection (M29.3),
// so M29.6.4 just removes the compile-time gate without changing logic.

namespace
{
	using BlueprintExporter::DeepRender::EscTbl;
	using BlueprintExporter::DeepRender::RenderUObjectPropertiesTable;
	using BlueprintExporter::DeepRender::RenderEdGraphNodes;

	// Class names we dispatch on via GetClass()->GetName() — keeps the
	// renderer compile-decoupled from the Private Mutable headers. If the
	// Mutable module ever renames these classes, the dump falls through to
	// the out-of-scope notice rather than crashing.
	const TCHAR* LibraryClassName() { return TEXT("CustomizableObjectMacroLibrary"); }

	// Property names on UCustomizableObjectMacroLibrary / UCustomizableObjectMacro /
	// UCustomizableObjectMacroInputOutput — all public UPROPERTYs, discoverable by
	// name via FindFProperty without a class-pointer dep.
	const TCHAR* PropMacros()          { return TEXT("Macros"); }
	const TCHAR* PropName()            { return TEXT("Name"); }
	const TCHAR* PropDescription()     { return TEXT("Description"); }
	const TCHAR* PropInputOutputs()    { return TEXT("InputOutputs"); }
	const TCHAR* PropGraph()           { return TEXT("Graph"); }
	const TCHAR* PropType()            { return TEXT("Type"); }
	const TCHAR* PropPinCategoryType() { return TEXT("PinCategoryType"); }
	const TCHAR* PropUniqueId()        { return TEXT("UniqueId"); }

	// Walk the library's Macros array via FArrayProperty + FObjectProperty
	// reflection. Returns the resolved UObject* per-element; skips null slots
	// defensively. Zero type dependency on the Mutable module.
	int32 GetMacroCount(const UObject* Library, FArrayProperty*& OutArrayProp)
	{
		OutArrayProp = nullptr;
		if (!Library)
		{
			return 0;
		}
		OutArrayProp = FindFProperty<FArrayProperty>(Library->GetClass(), PropMacros());
		if (!OutArrayProp)
		{
			return 0;
		}
		FScriptArrayHelper Helper(OutArrayProp, OutArrayProp->ContainerPtrToValuePtr<void>(Library));
		return Helper.Num();
	}

	UObject* GetMacroAt(UObject* Library, FArrayProperty* ArrayProp, int32 Index)
	{
		if (!Library || !ArrayProp)
		{
			return nullptr;
		}
		FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(Library));
		if (Index < 0 || Index >= Helper.Num())
		{
			return nullptr;
		}
		FObjectProperty* InnerObjProp = CastField<FObjectProperty>(ArrayProp->Inner);
		if (!InnerObjProp)
		{
			return nullptr;
		}
		return InnerObjProp->GetObjectPropertyValue(Helper.GetRawPtr(Index));
	}

	// Render the per-macro I/O variable table. Each input/output sub-object
	// has four UPROPERTYs we surface: Name (FName), Type (enum Input/Output),
	// PinCategoryType (FName), UniqueId (FGuid). UniqueId is stable across
	// loads (it's explicitly persisted per the header comment "Useful for pin
	// reconstruction and name repetitions"), unlike UEdGraphPin::PinId — no
	// masking needed.
	void RenderInputOutputsTable(FString& Md, UObject* Macro)
	{
		if (!Macro)
		{
			return;
		}
		FArrayProperty* IOProp = FindFProperty<FArrayProperty>(Macro->GetClass(), PropInputOutputs());
		if (!IOProp)
		{
			Md += TEXT("_(InputOutputs UPROPERTY not reachable — macro library layout may have changed)_\n\n");
			return;
		}
		FScriptArrayHelper Helper(IOProp, IOProp->ContainerPtrToValuePtr<void>(Macro));
		const int32 Count = Helper.Num();
		Md += FString::Printf(TEXT("**Inputs / Outputs (%d):**\n\n"), Count);
		if (Count == 0)
		{
			Md += TEXT("_(no authored I/O variables)_\n\n");
			return;
		}
		FObjectProperty* InnerObjProp = CastField<FObjectProperty>(IOProp->Inner);
		if (!InnerObjProp)
		{
			Md += TEXT("_(unable to resolve I/O element object-property)_\n\n");
			return;
		}

		Md += TEXT("| Name | Direction | Pin type | UniqueId |\n|---|---|---|---|\n");
		for (int32 i = 0; i < Count; ++i)
		{
			UObject* IO = InnerObjProp->GetObjectPropertyValue(Helper.GetRawPtr(i));
			if (!IO)
			{
				Md += TEXT("| _(null slot)_ | — | — | — |\n");
				continue;
			}

			// ExportTextItem_Direct APPENDS to the provided FString, so these
			// must start empty — fall back to `?` at cell-render time if the
			// property wasn't reachable via reflection.
			FString NameStr;
			FString DirStr;
			FString PinCatStr;
			FString UniqueIdStr;

			if (FNameProperty* NP = FindFProperty<FNameProperty>(IO->GetClass(), PropName()))
			{
				NameStr = NP->GetPropertyValue_InContainer(IO).ToString();
			}
			if (FProperty* TypeProp = FindFProperty<FProperty>(IO->GetClass(), PropType()))
			{
				TypeProp->ExportTextItem_Direct(DirStr, TypeProp->ContainerPtrToValuePtr<void>(IO), nullptr, nullptr, PPF_None);
			}
			if (FNameProperty* PCP = FindFProperty<FNameProperty>(IO->GetClass(), PropPinCategoryType()))
			{
				PinCatStr = PCP->GetPropertyValue_InContainer(IO).ToString();
			}
			if (FProperty* UIDProp = FindFProperty<FProperty>(IO->GetClass(), PropUniqueId()))
			{
				UIDProp->ExportTextItem_Direct(UniqueIdStr, UIDProp->ContainerPtrToValuePtr<void>(IO), nullptr, nullptr, PPF_None);
			}

			const FString NameCell     = NameStr.IsEmpty()     ? FString(TEXT("?")) : NameStr;
			const FString DirCell      = DirStr.IsEmpty()      ? FString(TEXT("?")) : DirStr;
			const FString PinCatCell   = PinCatStr.IsEmpty()   ? FString(TEXT("?")) : PinCatStr;
			const FString UniqueIdCell = UniqueIdStr.IsEmpty() ? FString(TEXT("?")) : UniqueIdStr;

			Md += FString::Printf(TEXT("| `%s` | `%s` | `%s` | `%s` |\n"),
				*EscTbl(NameCell),
				*EscTbl(DirCell),
				*EscTbl(PinCatCell),
				*EscTbl(UniqueIdCell));
		}
		Md += TEXT("\n");
	}

	void RenderMacroBlock(FString& Md, UObject* Macro, int32 Index)
	{
		if (!Macro)
		{
			Md += FString::Printf(TEXT("## Macro %d — `(null reference)`\n\n_(null macro slot in library at export time)_\n\n"), Index);
			return;
		}

		// Name (FName) — heading.
		FString MacroName(TEXT("?"));
		if (FNameProperty* NP = FindFProperty<FNameProperty>(Macro->GetClass(), PropName()))
		{
			MacroName = NP->GetPropertyValue_InContainer(Macro).ToString();
		}

		Md += FString::Printf(TEXT("## Macro %d — `%s`\n\n"), Index, *MacroName);

		// Identity table — UObject path + class.
		Md += TEXT("| Field | Value |\n|---|---|\n");
		Md += FString::Printf(TEXT("| Object path | `%s` |\n"), *EscTbl(Macro->GetPathName()));
		Md += FString::Printf(TEXT("| Object class | `%s` |\n"), *EscTbl(Macro->GetClass()->GetName()));
		Md += FString::Printf(TEXT("| Name | `%s` |\n"), *EscTbl(MacroName));

		// Description (FString) — rendered inline if short enough, else as a block.
		if (FStrProperty* DP = FindFProperty<FStrProperty>(Macro->GetClass(), PropDescription()))
		{
			const FString Description = DP->GetPropertyValue_InContainer(Macro);
			if (Description.IsEmpty())
			{
				Md += TEXT("| Description | _(empty)_ |\n");
			}
			else
			{
				Md += FString::Printf(TEXT("| Description | `%s` |\n"), *EscTbl(Description));
			}
		}
		Md += TEXT("\n");

		// I/O variable table.
		RenderInputOutputsTable(Md, Macro);

		// Graph walk — UEdGraph resolved via FObjectProperty reflection.
		Md += TEXT("**Graph:**\n\n");
		FObjectProperty* GraphProp = FindFProperty<FObjectProperty>(Macro->GetClass(), PropGraph());
		UEdGraph* Graph = nullptr;
		if (GraphProp)
		{
			UObject* GraphObj = GraphProp->GetObjectPropertyValue_InContainer(Macro);
			Graph = Cast<UEdGraph>(GraphObj);
		}
		RenderEdGraphNodes(Md, Graph);
	}

	FString DoRenderMacroLibrary(UObject* Library)
	{
		FString Md;
		Md.Reserve(32 * 1024);

		Md += FString::Printf(TEXT("# %s — Deep Dump (Tier 2)\n\n"), *Library->GetName());
		Md += TEXT("> Generated by `DeepDump` for a Mutable `UCustomizableObjectMacroLibrary`. A macro library stores reusable Mutable graph macros that other `UCustomizableObject` assets can instance via `UCustomizableObjectNodeMacroInstance`. Each macro is surfaced below with its name, description, input / output variable list, and full node-graph walk — same shape as M29.2's UCO node-graph section, just repeated once per macro. Implementation uses total UE reflection (no Private-header include on the Mutable module) — walks library → macros array → per-macro {Name, Description, InputOutputs, Graph} by UPROPERTY name.\n\n");

		// ---- Identity ----
		Md += TEXT("## Identity\n\n");
		Md += TEXT("| Field | Value |\n|---|---|\n");
		Md += FString::Printf(TEXT("| Asset path | `%s` |\n"), *EscTbl(Library->GetPathName()));
		Md += FString::Printf(TEXT("| Asset name | `%s` |\n"), *EscTbl(Library->GetName()));
		Md += TEXT("| Asset type | `CustomizableObjectMacroLibrary` |\n");
		UClass* Cls = Library->GetClass();
		UClass* ParentCls = Cls ? Cls->GetSuperClass() : nullptr;
		if (ParentCls)
		{
			Md += FString::Printf(TEXT("| Parent class | `%s` |\n"), *EscTbl(ParentCls->GetPathName()));
		}

		// Library-level UPROPERTY dump (everything except Macros, which we
		// render in its own section below with per-element nested detail).
		{
			TSet<FName> Plumbing;
			Plumbing.Add(FName(PropMacros()));
			const int32 N = RenderUObjectPropertiesTable(Md, Library, Plumbing);
			if (N == 0)
			{
				Md += TEXT("\n_(no library-level properties at non-default values)_\n\n");
			}
		}

		// ---- Macros ----
		FArrayProperty* MacrosArrayProp = nullptr;
		const int32 MacroCount = GetMacroCount(Library, MacrosArrayProp);
		Md += FString::Printf(TEXT("\n## Macros (%d)\n\n"), MacroCount);
		if (MacroCount == 0 || !MacrosArrayProp)
		{
			Md += TEXT("_No macros authored in this library (or the `Macros` UPROPERTY could not be resolved)._\n\n");
		}
		else
		{
			Md += TEXT("Listed in authored order. Each macro below gets its own `## Macro N` section with Name / Description / I/O variable table / node-graph walk — consumers want to see a macro's full authoring surface in one place rather than split across separate sections per attribute.\n\n");
			for (int32 i = 0; i < MacroCount; ++i)
			{
				UObject* Macro = GetMacroAt(Library, MacrosArrayProp, i);
				RenderMacroBlock(Md, Macro, i);
			}
		}

		// ---- Not rendered ----
		Md += TEXT("## Not rendered\n\n");
		Md += TEXT("- **Runtime pin GUIDs** inside `FEdGraphPinReference`-typed UPROPERTYs on macro-graph nodes — masked to `PinId=<unstable>` by the shared `MaskPinGuids` post-process (M29.2 finding). The `OwningNode` reference stays readable; the GUID itself regenerates each load and would destroy twin-run byte-identity.\n");
		Md += TEXT("- **Compiled / cooked representations** — a macro library is an authoring-only asset; Mutable's compiled model lives on the UCustomizableObject instances that reference these macros via `UCustomizableObjectNodeMacroInstance`.\n");

		return Md;
	}
}

namespace BlueprintExporter::DeepDump
{
	FString RenderCustomizableObjectMacroLibraryMarkdown(UObject* MacroLibraryObject)
	{
		if (!MacroLibraryObject)
		{
			return RenderOutOfScopeNotice(
				FString(TEXT("(null)")),
				FString(),
				TEXT("null UObject"));
		}
		// Class check by name to avoid a Private-header include on Mutable.
		if (MacroLibraryObject->GetClass()->GetName() != LibraryClassName())
		{
			return RenderOutOfScopeNotice(
				MacroLibraryObject->GetName(),
				MacroLibraryObject->GetPathName(),
				TEXT("not UCustomizableObjectMacroLibrary"));
		}
		return DoRenderMacroLibrary(MacroLibraryObject);
	}
}
