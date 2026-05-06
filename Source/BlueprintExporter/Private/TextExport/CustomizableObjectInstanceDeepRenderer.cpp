// Copyright 10 Chambers. All Rights Reserved.

#include "TextExport/CustomizableObjectInstanceDeepRenderer.h"
#include "TextExport/DeepDumpRenderer.h"
#include "TextExport/DeepRenderShared.h"

#include "UObject/Object.h"
#include "UObject/UnrealType.h"
#include "UObject/Class.h"

// M29.6.2 — zero compile-time dep on the Mutable module. Dispatch is by
// class-name match; every field read goes through reflection on
// `InstanceObject->GetClass()` (the runtime-resolved UClass) and the
// Descriptor's runtime-resolved UScriptStruct; the one direct-UE_API call
// the M29.1 implementation used (GetCurrentState) is replaced by a
// ProcessEvent call to UCO::GetStateName via the shared UFunctionCall
// helpers landed in M29.6.1. One BuiltPlugin DLL handles UCOI assets in
// any Mutable-capable project regardless of whether Mutable was present
// when the DLL was built.

namespace
{
	using BlueprintExporter::DeepRender::EscTbl;
	using BlueprintExporter::DeepRender::RenderStructFieldsTable;
	using BlueprintExporter::DeepRender::UFunctionCall::CallBool;
	using BlueprintExporter::DeepRender::UFunctionCall::CallObject;
	using BlueprintExporter::DeepRender::UFunctionCall::CallString;

	// Locate the `Descriptor` UPROPERTY on the UCOI via reflection against
	// the instance's own class. Returns true + (OutProp, OutData) on success.
	// Distinct helper because the Descriptor is the anchor for every
	// parameter-array walk and the state/UCO reads — resolving it once up
	// front keeps the render flow linear.
	bool ResolveDescriptor(const UObject* Instance, FStructProperty*& OutProp, const void*& OutData)
	{
		OutProp = nullptr;
		OutData = nullptr;
		if (!Instance)
		{
			return false;
		}
		FStructProperty* DescProp = FindFProperty<FStructProperty>(
			Instance->GetClass(), TEXT("Descriptor"));
		if (!DescProp || !DescProp->Struct)
		{
			return false;
		}
		OutProp = DescProp;
		OutData = DescProp->ContainerPtrToValuePtr<void>(Instance);
		return true;
	}

	// Dump one typed parameter-array field from the Descriptor as a nested
	// Markdown section. The field is always a `TArray<FCustomizableObject*ParameterValue>`;
	// each element is a UStruct whose fields we render with the shared struct-table helper.
	// Returns the number of elements rendered (0 when the array is empty — we
	// still emit the heading so downstream diff tooling sees every array type
	// unconditionally, mirroring the M11/M12 pattern).
	int32 RenderParameterArray(
		FString& Md,
		const UScriptStruct* DescStruct,
		const void* DescData,
		const TCHAR* FieldName,
		const TCHAR* Heading)
	{
		FArrayProperty* ArrProp = DescStruct ? FindFProperty<FArrayProperty>(DescStruct, FieldName) : nullptr;
		if (!ArrProp || !DescData)
		{
			Md += FString::Printf(TEXT("### %s (0)\n\n"), Heading);
			Md += TEXT("_No overrides._\n\n");
			return 0;
		}

		FScriptArrayHelper Helper(ArrProp, ArrProp->ContainerPtrToValuePtr<void>(DescData));
		const int32 Count = Helper.Num();

		Md += FString::Printf(TEXT("### %s (%d)\n\n"), Heading, Count);

		if (Count == 0)
		{
			Md += TEXT("_No overrides._\n\n");
			return 0;
		}

		FStructProperty* InnerStructProp = CastField<FStructProperty>(ArrProp->Inner);
		if (!InnerStructProp || !InnerStructProp->Struct)
		{
			Md += TEXT("_Unable to resolve element struct type._\n\n");
			return 0;
		}

		const UScriptStruct* ElemType = InnerStructProp->Struct;

		for (int32 i = 0; i < Count; ++i)
		{
			Md += FString::Printf(TEXT("#### Element %d\n\n"), i);
			const int32 N = RenderStructFieldsTable(Md, ElemType, Helper.GetRawPtr(i));
			if (N == 0)
			{
				Md += TEXT("_(no fields at non-default values, or struct declares no exposed fields)_\n\n");
			}
		}
		return Count;
	}

	// Read the parent UCO from the UCOI, preferring the UFUNCTION path so
	// that byte-identity with the pre-M29.6.2 direct-call output is preserved
	// on every project where `UCustomizableObjectInstance::GetCustomizableObject()`
	// exists as a BlueprintCallable getter. Falls back to reflecting the
	// `CustomizableObject` UPROPERTY on the Descriptor — UPROPERTY-stored
	// per M29.6.0 Q5 research.
	// TOptional-set with a null inner pointer means "function reachable, UCO
	// reference broken" (same case the M29.1 code rendered as "Broken reference"),
	// TOptional-empty means "neither path resolved" (unchanged: still
	// "Broken reference" in output).
	UObject* ResolveParentUCO(UObject* Instance, const UScriptStruct* DescStruct, const void* DescData)
	{
		TOptional<UObject*> ViaUFunc = CallObject(Instance, TEXT("GetCustomizableObject"));
		if (ViaUFunc.IsSet())
		{
			return ViaUFunc.GetValue();
		}
		if (DescStruct && DescData)
		{
			if (FObjectProperty* UcoProp = FindFProperty<FObjectProperty>(DescStruct, TEXT("CustomizableObject")))
			{
				return UcoProp->GetObjectPropertyValue_InContainer(DescData);
			}
		}
		return nullptr;
	}

	// Read the Descriptor's State integer via UPROPERTY reflection. Bool
	// signals "field found" — distinguishes a true zero from a missing field
	// so the renderer can decide whether to attempt the UCO GetStateName call.
	int32 ReadDescriptorState(const UScriptStruct* DescStruct, const void* DescData, bool& bOutFound)
	{
		bOutFound = false;
		if (!DescStruct || !DescData)
		{
			return 0;
		}
		if (FIntProperty* StateProp = FindFProperty<FIntProperty>(DescStruct, TEXT("State")))
		{
			bOutFound = true;
			return StateProp->GetPropertyValue_InContainer(DescData);
		}
		return 0;
	}

	// Resolve the "build parameter relevancy" flag. Try the UFUNCTION first
	// (byte-identity with the pre-M29.6.2 direct-call output when it exists
	// as a BlueprintCallable getter), then reflect a few candidate UPROPERTY
	// names on the Descriptor. TOptional-empty result signals "_not reachable_"
	// — honouring "Never guess values".
	TOptional<bool> ResolveBuildParameterRelevancy(UObject* Instance, const UScriptStruct* DescStruct, const void* DescData)
	{
		TOptional<bool> ViaUFunc = CallBool(Instance, TEXT("GetBuildParameterRelevancy"));
		if (ViaUFunc.IsSet())
		{
			return ViaUFunc;
		}
		if (DescStruct && DescData)
		{
			const TCHAR* Candidates[] = { TEXT("bBuildParameterRelevancy"), TEXT("BuildParameterRelevancy") };
			for (const TCHAR* Name : Candidates)
			{
				if (FBoolProperty* BoolProp = FindFProperty<FBoolProperty>(DescStruct, Name))
				{
					return BoolProp->GetPropertyValue_InContainer(DescData);
				}
			}
		}
		return TOptional<bool>();
	}

	FString DoRenderUCOI(UObject* Instance)
	{
		FString Md;
		Md.Reserve(8 * 1024);

		Md += FString::Printf(TEXT("# %s — Deep Dump (Tier 2)\n\n"), *Instance->GetName());
		Md += TEXT("> Generated by `DeepDump` for a Mutable `UCustomizableObjectInstance`. Surfaces the parent `UCustomizableObject` link and every non-transient parameter override inside the instance's `FCustomizableObjectInstanceDescriptor` — the full authoring surface an AI consumer needs to understand what this saved customization overrides vs. the UCO defaults. Runtime-generated meshes / materials are out of scope (live objects, non-deterministic across runs); UCO graph / parameter schema / node graph is in the parent UCO's own `.deep.md` (M29.2).\n\n");

		// Resolve the Descriptor up front — anchor for everything below.
		FStructProperty* DescProp = nullptr;
		const void* Desc = nullptr;
		const bool bHaveDesc = ResolveDescriptor(Instance, DescProp, Desc);
		const UScriptStruct* DescStruct = DescProp ? DescProp->Struct : nullptr;

		UObject* UcoObj = ResolveParentUCO(Instance, DescStruct, Desc);

		// ---- Identity ----
		Md += TEXT("## Identity\n\n");
		Md += TEXT("| Field | Value |\n|---|---|\n");
		Md += FString::Printf(TEXT("| Asset path | `%s` |\n"), *EscTbl(Instance->GetPathName()));
		Md += FString::Printf(TEXT("| Asset name | `%s` |\n"), *EscTbl(Instance->GetName()));
		Md += TEXT("| Asset type | `CustomizableObjectInstance` |\n");
		UClass* Cls = Instance->GetClass();
		UClass* ParentCls = Cls ? Cls->GetSuperClass() : nullptr;
		if (ParentCls)
		{
			Md += FString::Printf(TEXT("| Parent class | `%s` |\n"), *EscTbl(ParentCls->GetPathName()));
		}
		if (UcoObj)
		{
			Md += FString::Printf(TEXT("| Customizable Object | `%s` |\n"), *EscTbl(UcoObj->GetPathName()));
		}
		else
		{
			Md += TEXT("| Customizable Object | **Broken reference** — instance references a null UCO at export time |\n");
		}
		Md += TEXT("\n");

		if (!bHaveDesc)
		{
			Md += TEXT("## Parameters\n\n");
			Md += TEXT("_Unable to resolve `Descriptor` UPROPERTY via reflection — the Mutable plugin's internal layout may have changed. No parameter values rendered (honouring \"Never guess values\")._\n\n");
			return Md;
		}

		// ---- State ----
		Md += TEXT("## State\n\n");
		Md += TEXT("| Field | Value |\n|---|---|\n");

		bool bStateFound = false;
		const int32 StateIdx = ReadDescriptorState(DescStruct, Desc, bStateFound);
		FString CurrentStateName;
		if (bStateFound && UcoObj)
		{
			TArray<FString> Args;
			Args.Add(FString::Printf(TEXT("%d"), StateIdx));
			TOptional<FString> Resp = CallString(UcoObj, TEXT("GetStateName"), Args);
			if (Resp.IsSet())
			{
				CurrentStateName = Resp.GetValue();
			}
		}
		Md += FString::Printf(TEXT("| Current state | `%s` |\n"), *EscTbl(CurrentStateName));
		Md += FString::Printf(TEXT("| State index | `%d` |\n"), StateIdx);

		TOptional<bool> Relevancy = ResolveBuildParameterRelevancy(Instance, DescStruct, Desc);
		FString RelevancyText = Relevancy.IsSet()
			? (Relevancy.GetValue() ? TEXT("yes") : TEXT("no"))
			: FString(TEXT("_not reachable_"));
		Md += FString::Printf(TEXT("| Build parameter relevancy | %s |\n"), *RelevancyText);
		Md += TEXT("\n");

		// ---- Parameter arrays (9 typed arrays per M29.0 Q5) ----
		Md += TEXT("## Parameter Overrides\n\n");
		Md += TEXT("Each array below lists the authored overrides for one parameter type. Empty arrays are kept as explicit sections — tools diffing Mutable instances across versions want to see the \"this used to have overrides, now it doesn't\" transition without guessing.\n\n");

		int32 Total = 0;
		Total += RenderParameterArray(Md, DescStruct, Desc, TEXT("BoolParameters"),         TEXT("Bool"));
		Total += RenderParameterArray(Md, DescStruct, Desc, TEXT("IntParameters"),          TEXT("Int (enum)"));
		Total += RenderParameterArray(Md, DescStruct, Desc, TEXT("FloatParameters"),        TEXT("Float"));
		Total += RenderParameterArray(Md, DescStruct, Desc, TEXT("TextureParameters"),      TEXT("Texture"));
		Total += RenderParameterArray(Md, DescStruct, Desc, TEXT("SkeletalMeshParameters"), TEXT("SkeletalMesh"));
		Total += RenderParameterArray(Md, DescStruct, Desc, TEXT("MaterialParameters"),     TEXT("Material"));
		Total += RenderParameterArray(Md, DescStruct, Desc, TEXT("VectorParameters"),       TEXT("Vector (LinearColor)"));
		Total += RenderParameterArray(Md, DescStruct, Desc, TEXT("ProjectorParameters"),    TEXT("Projector"));
		Total += RenderParameterArray(Md, DescStruct, Desc, TEXT("TransformParameters"),    TEXT("Transform"));

		Md += FString::Printf(TEXT("_Total parameter overrides across all types: **%d**._\n\n"), Total);

		// ---- Runtime/derived data skip notice ----
		Md += TEXT("## Not rendered\n\n");
		Md += TEXT("- **Generated skeletal meshes and materials** — live runtime-produced objects; not part of the saved asset content. Inspect at runtime or via the baking workflow instead.\n");
		Md += TEXT("- **Multilayer projector layers** — not serialized through the `SaveDescriptor` path per Mutable's own documentation; would require a separate pass if a driver surfaces.\n");
		Md += TEXT("- **Deprecated inline parameter arrays** on the UCOI itself (`BoolParameters_DEPRECATED` etc.) — legacy storage superseded by `Descriptor`; skipped to avoid double-counting.\n");

		return Md;
	}
}

namespace BlueprintExporter::DeepDump
{
	FString RenderCustomizableObjectInstanceMarkdown(UObject* InstanceObject)
	{
		if (!InstanceObject)
		{
			return RenderOutOfScopeNotice(FString(TEXT("(null)")), FString(), TEXT("not UCustomizableObjectInstance"));
		}

		// Class-name-match dispatch — no compile-time dep on the Mutable
		// UClass. Any project that doesn't have Mutable loaded will never
		// enter this branch (no UObject with that class name exists), so the
		// renderer degrades gracefully to the out-of-scope notice without
		// needing a `#if WITH_MUTABLE_SUPPORT` gate.
		const UClass* Cls = InstanceObject->GetClass();
		const bool bIsUCOI = Cls && Cls->GetFName() == FName(TEXT("CustomizableObjectInstance"));
		if (!bIsUCOI)
		{
			return RenderOutOfScopeNotice(
				InstanceObject->GetName(),
				InstanceObject->GetPathName(),
				TEXT("not UCustomizableObjectInstance"));
		}

		return DoRenderUCOI(InstanceObject);
	}
}
