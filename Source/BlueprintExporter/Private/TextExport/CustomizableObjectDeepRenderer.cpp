// Copyright 10 Chambers. All Rights Reserved.

#include "TextExport/CustomizableObjectDeepRenderer.h"
#include "TextExport/DeepDumpRenderer.h"
#include "TextExport/DeepRenderShared.h"

#include "UObject/Object.h"
#include "UObject/UnrealType.h"
#include "UObject/Class.h"
#include "UObject/EnumProperty.h"
#include "EdGraph/EdGraph.h"
#include "Math/Color.h"
#include "Math/Transform.h"

// M29.6.3 — zero compile-time dep on the Mutable module. Dispatch is by
// class-name match (`InObject->GetClass()->GetFName() == "CustomizableObject"`);
// every direct call to a UCustomizableObject BlueprintCallable getter goes
// through the ProcessEvent-based `UFunctionCall` helpers landed in M29.6.1.
// All `FindFProperty` sites key off the runtime-resolved UClass rather than
// `UCustomizableObject::StaticClass()`. FLinearColor / FTransform returns are
// copied into stack locals via `CopyScriptStruct` (those types are
// engine-core, available unconditionally); the Mutable-only structs
// (`FMutableParamUIMetadata`, `FMutableStateUIMetadata`,
// `FCustomizableObjectProjector`) are read field-by-name via UScriptStruct
// reflection. M29.6.4 stripped the `WITH_MUTABLE_SUPPORT` gate project-wide;
// one BuiltPlugin DLL now handles CO assets on every engine.

namespace
{
	using BlueprintExporter::DeepRender::EscTbl;
	using BlueprintExporter::DeepRender::RenderUObjectPropertiesTable;
	using BlueprintExporter::DeepRender::UFunctionCall::CallBool;
	using BlueprintExporter::DeepRender::UFunctionCall::CallFloat;
	using BlueprintExporter::DeepRender::UFunctionCall::CallFName;
	using BlueprintExporter::DeepRender::UFunctionCall::CallInt;
	using BlueprintExporter::DeepRender::UFunctionCall::CallObject;
	using BlueprintExporter::DeepRender::UFunctionCall::CallString;
	using BlueprintExporter::DeepRender::UFunctionCall::CallUFunctionRaw;

	// Resolve the private `Source: TObjectPtr<UEdGraph>` UPROPERTY via
	// reflection against the instance's own class. M29.6.3 change: no more
	// `UCustomizableObject::StaticClass()` — key off the runtime UClass so
	// the file compiles without the Mutable module being linked.
	UEdGraph* ResolveSourceGraph(UObject* CO)
	{
#if WITH_EDITORONLY_DATA
		if (!CO)
		{
			return nullptr;
		}
		FObjectProperty* Prop = FindFProperty<FObjectProperty>(CO->GetClass(), TEXT("Source"));
		if (!Prop)
		{
			return nullptr;
		}
		UObject* Obj = Prop->GetObjectPropertyValue_InContainer(CO);
		return Cast<UEdGraph>(Obj);
#else
		return nullptr;
#endif
	}

	// Read an enum UFUNCTION return as its short name (e.g. "Bool",
	// "COGT_TOGGLE"). Walks the return property to pull the attached UEnum
	// without needing a compile-time include of the enum type. Empty result
	// means the function wasn't found, returned a non-enum type, or had no
	// UEnum attached — caller renders the fallback display string.
	FString ReadEnumShortName(UObject* CO, FName FuncName, const TArray<FString>& Args)
	{
		FString Result;
		CallUFunctionRaw(CO, FuncName, Args,
			[&Result](FProperty* ReturnProp, const void* ReturnValuePtr)
			{
				if (FEnumProperty* EP = CastField<FEnumProperty>(ReturnProp))
				{
					if (UEnum* Enum = EP->GetEnum())
					{
						const int64 Val = EP->GetUnderlyingProperty()->GetSignedIntPropertyValue(ReturnValuePtr);
						Result = Enum->GetNameStringByValue(Val);
					}
				}
				else if (FByteProperty* BP = CastField<FByteProperty>(ReturnProp))
				{
					if (UEnum* Enum = BP->Enum)
					{
						const uint8 Val = BP->GetPropertyValue(ReturnValuePtr);
						Result = Enum->GetNameStringByValue(Val);
					}
				}
			});
		return Result;
	}

	// EMutableParameterType short-name → stable display string. Short names
	// match the engine-declared `enum class` identifiers exactly; keeping
	// the display strings keyed to them (rather than to the UMETA DisplayName
	// which differs: `Bool` vs `Boolean`, `Int` vs `Integer`) preserves
	// byte-identity with the pre-M29.6.3 output.
	const TCHAR* ParamTypeDisplay(const FString& ShortName)
	{
		if (ShortName == TEXT("Bool"))         return TEXT("Bool");
		if (ShortName == TEXT("Int"))          return TEXT("Int (enum)");
		if (ShortName == TEXT("Float"))        return TEXT("Float");
		if (ShortName == TEXT("Color"))        return TEXT("Color");
		if (ShortName == TEXT("Projector"))    return TEXT("Projector");
		if (ShortName == TEXT("Texture"))      return TEXT("Texture");
		if (ShortName == TEXT("Transform"))    return TEXT("Transform");
		if (ShortName == TEXT("SkeletalMesh")) return TEXT("SkeletalMesh");
		if (ShortName == TEXT("Material"))     return TEXT("Material");
		return TEXT("(unknown)");
	}

	// ECustomizableObjectGroupType short-name → display string (same policy
	// as ParamTypeDisplay — the short names carry the `COGT_` prefix).
	const TCHAR* GroupTypeDisplay(const FString& ShortName)
	{
		if (ShortName == TEXT("COGT_TOGGLE"))      return TEXT("Toggle");
		if (ShortName == TEXT("COGT_ALL"))         return TEXT("All Options");
		if (ShortName == TEXT("COGT_ONE"))         return TEXT("At least one Option");
		if (ShortName == TEXT("COGT_ONE_OR_NONE")) return TEXT("One or None");
		return TEXT("(unknown)");
	}

	// Extract a FVector3f `(X, Y, Z)` triple from a named UStruct field. Used
	// to reach into `FCustomizableObjectProjector` without a compile-time
	// include of the struct definition. `FVector3f` is UE5 core (float X/Y/Z)
	// so FFloatProperty probes are sufficient; we keep a FDoubleProperty
	// fallback for safety if Epic ever flips the underlying storage to FVector.
	void ReadVec3FromField(const UScriptStruct* OwnerStruct, const void* OwnerMem,
		const TCHAR* FieldName, float& OutX, float& OutY, float& OutZ)
	{
		FStructProperty* VecProp = FindFProperty<FStructProperty>(OwnerStruct, FieldName);
		if (!VecProp || !VecProp->Struct)
		{
			return;
		}
		const void* VecMem = VecProp->ContainerPtrToValuePtr<void>(OwnerMem);
		auto Read = [VecMem](const UScriptStruct* Type, const TCHAR* Axis, float& Out)
		{
			if (FFloatProperty* FP = FindFProperty<FFloatProperty>(Type, Axis))
			{
				Out = FP->GetPropertyValue_InContainer(VecMem);
			}
			else if (FDoubleProperty* DP = FindFProperty<FDoubleProperty>(Type, Axis))
			{
				Out = static_cast<float>(DP->GetPropertyValue_InContainer(VecMem));
			}
		};
		Read(VecProp->Struct, TEXT("X"), OutX);
		Read(VecProp->Struct, TEXT("Y"), OutY);
		Read(VecProp->Struct, TEXT("Z"), OutZ);
	}

	// Snapshot of the UI-metadata fields the renderer wants to surface.
	// `FMutableStateUIMetadata` and `FMutableParamUIMetadata` both inherit
	// `ObjectFriendlyName` / `UISectionName` / `UIOrder` from `FMutableUIMetadata`;
	// `FindFProperty` walks the super-struct chain so the same reflection
	// works for either return type. Param-only fields (Minimum/MaximumValue)
	// are probed optionally via `bIncludeRange`.
	struct FUIMetaSnapshot
	{
		FString ObjectFriendlyName;
		FString UISectionName;
		int32 UIOrder = 0;
		float MinimumValue = 0.0f;
		float MaximumValue = 1.0f;
		bool bFound = false;
	};

	FUIMetaSnapshot ReadUIMetadata(UObject* CO, FName FuncName, const TArray<FString>& Args, bool bIncludeRange)
	{
		FUIMetaSnapshot Snap;
		CallUFunctionRaw(CO, FuncName, Args,
			[&Snap, bIncludeRange](FProperty* ReturnProp, const void* ReturnValuePtr)
			{
				FStructProperty* SP = CastField<FStructProperty>(ReturnProp);
				if (!SP || !SP->Struct)
				{
					return;
				}
				Snap.bFound = true;
				if (FStrProperty* P = FindFProperty<FStrProperty>(SP->Struct, TEXT("ObjectFriendlyName")))
				{
					Snap.ObjectFriendlyName = P->GetPropertyValue_InContainer(ReturnValuePtr);
				}
				if (FStrProperty* P = FindFProperty<FStrProperty>(SP->Struct, TEXT("UISectionName")))
				{
					Snap.UISectionName = P->GetPropertyValue_InContainer(ReturnValuePtr);
				}
				if (FIntProperty* P = FindFProperty<FIntProperty>(SP->Struct, TEXT("UIOrder")))
				{
					Snap.UIOrder = P->GetPropertyValue_InContainer(ReturnValuePtr);
				}
				if (bIncludeRange)
				{
					if (FFloatProperty* P = FindFProperty<FFloatProperty>(SP->Struct, TEXT("MinimumValue")))
					{
						Snap.MinimumValue = P->GetPropertyValue_InContainer(ReturnValuePtr);
					}
					if (FFloatProperty* P = FindFProperty<FFloatProperty>(SP->Struct, TEXT("MaximumValue")))
					{
						Snap.MaximumValue = P->GetPropertyValue_InContainer(ReturnValuePtr);
					}
				}
			});
		return Snap;
	}

	// Format the default value for a parameter of the given type via the
	// matching UCO accessor. Returns an empty string when the accessor
	// can't produce a stable value (function missing, asset not compiled,
	// non-Color/Transform/Projector struct shape). Keeps the "Never guess
	// values" contract: we call the real accessor (via reflection), we
	// don't synthesize a placeholder.
	FString FormatParamDefault(UObject* CO, const FString& ParamName, const FString& ShortName)
	{
		TArray<FString> Args;
		Args.Add(ParamName);

		if (ShortName == TEXT("Bool"))
		{
			TOptional<bool> V = CallBool(CO, TEXT("GetBoolParameterDefaultValue"), Args);
			return V.IsSet() ? (V.GetValue() ? TEXT("true") : TEXT("false")) : FString();
		}
		if (ShortName == TEXT("Int"))
		{
			TOptional<int32> V = CallInt(CO, TEXT("GetEnumParameterDefaultValue"), Args);
			return V.IsSet() ? FString::Printf(TEXT("%d"), V.GetValue()) : FString();
		}
		if (ShortName == TEXT("Float"))
		{
			TOptional<float> V = CallFloat(CO, TEXT("GetFloatParameterDefaultValue"), Args);
			return V.IsSet() ? FString::Printf(TEXT("%f"), V.GetValue()) : FString();
		}
		if (ShortName == TEXT("Color"))
		{
			FLinearColor C;
			bool bGot = false;
			CallUFunctionRaw(CO, TEXT("GetColorParameterDefaultValue"), Args,
				[&C, &bGot](FProperty* RP, const void* RV)
				{
					FStructProperty* SP = CastField<FStructProperty>(RP);
					if (SP && SP->Struct && SP->Struct->GetFName() == FName(TEXT("LinearColor")))
					{
						SP->Struct->CopyScriptStruct(&C, RV);
						bGot = true;
					}
				});
			return bGot
				? FString::Printf(TEXT("(R=%f, G=%f, B=%f, A=%f)"), C.R, C.G, C.B, C.A)
				: FString();
		}
		if (ShortName == TEXT("Transform"))
		{
			FTransform T = FTransform::Identity;
			bool bGot = false;
			CallUFunctionRaw(CO, TEXT("GetTransformParameterDefaultValue"), Args,
				[&T, &bGot](FProperty* RP, const void* RV)
				{
					FStructProperty* SP = CastField<FStructProperty>(RP);
					if (SP && SP->Struct && SP->Struct->GetFName() == FName(TEXT("Transform")))
					{
						SP->Struct->CopyScriptStruct(&T, RV);
						bGot = true;
					}
				});
			return bGot ? T.ToString() : FString();
		}
		if (ShortName == TEXT("Texture"))
		{
			TOptional<UObject*> V = CallObject(CO, TEXT("GetTextureParameterDefaultValue"), Args);
			if (!V.IsSet()) return FString();
			const UObject* Tex = V.GetValue();
			return Tex ? Tex->GetPathName() : FString(TEXT("None"));
		}
		if (ShortName == TEXT("SkeletalMesh"))
		{
			TOptional<UObject*> V = CallObject(CO, TEXT("GetSkeletalMeshParameterDefaultValue"), Args);
			if (!V.IsSet()) return FString();
			const UObject* SK = V.GetValue();
			return SK ? SK->GetPathName() : FString(TEXT("None"));
		}
		if (ShortName == TEXT("Material"))
		{
			TOptional<UObject*> V = CallObject(CO, TEXT("GetMaterialParameterDefaultValue"), Args);
			if (!V.IsSet()) return FString();
			const UObject* Mat = V.GetValue();
			return Mat ? Mat->GetPathName() : FString(TEXT("None"));
		}
		if (ShortName == TEXT("Projector"))
		{
			float PosX = 0.0f, PosY = 0.0f, PosZ = 0.0f;
			float SclX = 0.0f, SclY = 0.0f, SclZ = 0.0f;
			bool bGot = false;
			CallUFunctionRaw(CO, TEXT("GetProjectorParameterDefaultValue"), Args,
				[&](FProperty* RP, const void* RV)
				{
					FStructProperty* SP = CastField<FStructProperty>(RP);
					if (!SP || !SP->Struct)
					{
						return;
					}
					bGot = true;
					ReadVec3FromField(SP->Struct, RV, TEXT("Position"), PosX, PosY, PosZ);
					ReadVec3FromField(SP->Struct, RV, TEXT("Scale"), SclX, SclY, SclZ);
				});
			return bGot
				? FString::Printf(TEXT("Pos=(%f, %f, %f), Scale=(%f, %f, %f)"),
					PosX, PosY, PosZ, SclX, SclY, SclZ)
				: FString();
		}
		// EMutableParameterType::None or unknown short name
		return FString();
	}

	// ---- Parameters section ----
	//
	// Walks the authored parameter schema via the public BlueprintCallable
	// accessors (`GetParameterCount` / `GetParameterName` / `GetParameterTypeByName`
	// / `GetEnumParameterNumValues` / `GetEnumParameterValue` / the per-type
	// default-value getters), all routed through the M29.6.1 `UFunctionCall`
	// helpers so the file compiles without linking against the Mutable module.
	// Parameters are alpha-sorted by name for determinism — the runtime
	// positional order is implementation-detail, not authoring signal.
	void RenderParameterSection(FString& Md, UObject* CO)
	{
		TOptional<int32> CountOpt = CallInt(CO, TEXT("GetParameterCount"));
		if (!CountOpt.IsSet())
		{
			Md += TEXT("## Parameters\n\n");
			Md += TEXT("_Unable to read parameter count — `GetParameterCount` UFUNCTION not found on this object._\n\n");
			return;
		}
		const int32 Count = CountOpt.GetValue();
		if (Count == 0)
		{
			Md += TEXT("## Parameters\n\n");
			Md += TEXT("_No parameters exposed (the asset may not be compiled, or it has no Group / Parameter nodes in the graph)._\n\n");
			return;
		}

		TArray<FString> Names;
		Names.Reserve(Count);
		for (int32 i = 0; i < Count; ++i)
		{
			TArray<FString> Args;
			Args.Add(FString::Printf(TEXT("%d"), i));
			TOptional<FString> N = CallString(CO, TEXT("GetParameterName"), Args);
			Names.Add(N.IsSet() ? N.GetValue() : FString());
		}
		Names.Sort([](const FString& A, const FString& B)
		{
			return A.Compare(B, ESearchCase::IgnoreCase) < 0;
		});

		Md += FString::Printf(TEXT("## Parameters (%d)\n\n"), Count);
		Md += TEXT("Alpha-sorted by parameter name. Runtime parameter indices are implementation-detail and may shift between compiles; name is the stable identifier.\n\n");
		Md += TEXT("| Name | Type | Multidim | Default |\n|---|---|---|---|\n");

		for (const FString& Name : Names)
		{
			TArray<FString> NameArgs;
			NameArgs.Add(Name);
			const FString ShortName = ReadEnumShortName(CO, TEXT("GetParameterTypeByName"), NameArgs);
			TOptional<bool> MultiOpt = CallBool(CO, TEXT("IsParameterMultidimensional"), NameArgs);
			const bool bMulti = MultiOpt.IsSet() && MultiOpt.GetValue();
			const FString Default = FormatParamDefault(CO, Name, ShortName);

			Md += FString::Printf(TEXT("| `%s` | `%s` | %s | %s |\n"),
				*EscTbl(Name),
				ParamTypeDisplay(ShortName),
				bMulti ? TEXT("yes") : TEXT("no"),
				Default.IsEmpty() ? TEXT("—") : *FString::Printf(TEXT("`%s`"), *EscTbl(Default)));
		}
		Md += TEXT("\n");

		// Per-parameter UI metadata + (for Int enums) the option list.
		Md += TEXT("### Parameter details\n\n");
		for (const FString& Name : Names)
		{
			TArray<FString> NameArgs;
			NameArgs.Add(Name);
			const FString ShortName = ReadEnumShortName(CO, TEXT("GetParameterTypeByName"), NameArgs);
			Md += FString::Printf(TEXT("#### `%s` — `%s`\n\n"), *Name, ParamTypeDisplay(ShortName));

			const FUIMetaSnapshot UI = ReadUIMetadata(CO, TEXT("GetParameterUIMetadata"), NameArgs, /*bIncludeRange=*/true);
			const bool bHasFriendly = !UI.ObjectFriendlyName.IsEmpty();
			const bool bHasSection  = !UI.UISectionName.IsEmpty();
			const bool bHasRange    = (ShortName == TEXT("Float")) && (UI.MinimumValue != 0.0f || UI.MaximumValue != 1.0f);
			if (bHasFriendly || bHasSection || UI.UIOrder != 0 || bHasRange)
			{
				Md += TEXT("| UI field | Value |\n|---|---|\n");
				if (bHasFriendly)
				{
					Md += FString::Printf(TEXT("| ObjectFriendlyName | `%s` |\n"), *EscTbl(UI.ObjectFriendlyName));
				}
				if (bHasSection)
				{
					Md += FString::Printf(TEXT("| UISectionName | `%s` |\n"), *EscTbl(UI.UISectionName));
				}
				if (UI.UIOrder != 0)
				{
					Md += FString::Printf(TEXT("| UIOrder | `%d` |\n"), UI.UIOrder);
				}
				if (bHasRange)
				{
					Md += FString::Printf(TEXT("| Range | `%f ... %f` |\n"), UI.MinimumValue, UI.MaximumValue);
				}
				Md += TEXT("\n");
			}
			else
			{
				Md += TEXT("_(no authored UI metadata)_\n\n");
			}

			if (ShortName == TEXT("Int"))
			{
				TOptional<int32> NumValsOpt = CallInt(CO, TEXT("GetEnumParameterNumValues"), NameArgs);
				const int32 NumValues = NumValsOpt.IsSet() ? NumValsOpt.GetValue() : 0;
				if (NumValues > 0)
				{
					Md += FString::Printf(TEXT("**Enum values (%d):**\n\n"), NumValues);
					Md += TEXT("| Index | Option |\n|---|---|\n");
					for (int32 v = 0; v < NumValues; ++v)
					{
						TArray<FString> ValueArgs;
						ValueArgs.Add(Name);
						ValueArgs.Add(FString::Printf(TEXT("%d"), v));
						TOptional<FString> ValOpt = CallString(CO, TEXT("GetEnumParameterValue"), ValueArgs);
						const FString Value = ValOpt.IsSet() ? ValOpt.GetValue() : FString();
						Md += FString::Printf(TEXT("| %d | `%s` |\n"), v, *EscTbl(Value));
					}
					Md += TEXT("\n");

					const FString GroupShort = ReadEnumShortName(CO, TEXT("GetEnumParameterGroupType"), NameArgs);
					Md += FString::Printf(TEXT("_Group type: `%s`_\n\n"), GroupTypeDisplay(GroupShort));
				}
			}
		}
	}

	// ---- States section ----
	//
	// A Mutable "state" lists the subset of parameters that remain live-
	// editable at runtime (e.g. you might author a state where only face
	// morph floats are editable, or one where the full wardrobe toggles
	// are editable). Tier 2 surface: state name + runtime-parameter list
	// + UI metadata. Alpha-sorted for determinism.
	void RenderStateSection(FString& Md, UObject* CO)
	{
		TOptional<int32> CountOpt = CallInt(CO, TEXT("GetStateCount"));
		if (!CountOpt.IsSet())
		{
			Md += TEXT("## States\n\n");
			Md += TEXT("_Unable to read state count — `GetStateCount` UFUNCTION not found on this object._\n\n");
			return;
		}
		const int32 Count = CountOpt.GetValue();
		if (Count == 0)
		{
			Md += TEXT("## States\n\n");
			Md += TEXT("_No states defined._\n\n");
			return;
		}

		TArray<FString> StateNames;
		StateNames.Reserve(Count);
		for (int32 i = 0; i < Count; ++i)
		{
			TArray<FString> Args;
			Args.Add(FString::Printf(TEXT("%d"), i));
			TOptional<FString> N = CallString(CO, TEXT("GetStateName"), Args);
			StateNames.Add(N.IsSet() ? N.GetValue() : FString());
		}
		StateNames.Sort([](const FString& A, const FString& B)
		{
			return A.Compare(B, ESearchCase::IgnoreCase) < 0;
		});

		Md += FString::Printf(TEXT("## States (%d)\n\n"), Count);
		Md += TEXT("Alpha-sorted. States define which parameters remain editable at runtime (per-state subset of the full parameter schema above).\n\n");

		for (const FString& StateName : StateNames)
		{
			Md += FString::Printf(TEXT("### `%s`\n\n"), *StateName);

			TArray<FString> NameArgs;
			NameArgs.Add(StateName);
			const FUIMetaSnapshot UI = ReadUIMetadata(CO, TEXT("GetStateUIMetadata"), NameArgs, /*bIncludeRange=*/false);
			const bool bHasFriendly = !UI.ObjectFriendlyName.IsEmpty();
			const bool bHasSection  = !UI.UISectionName.IsEmpty();
			if (bHasFriendly || bHasSection || UI.UIOrder != 0)
			{
				Md += TEXT("| UI field | Value |\n|---|---|\n");
				if (bHasFriendly)
				{
					Md += FString::Printf(TEXT("| ObjectFriendlyName | `%s` |\n"), *EscTbl(UI.ObjectFriendlyName));
				}
				if (bHasSection)
				{
					Md += FString::Printf(TEXT("| UISectionName | `%s` |\n"), *EscTbl(UI.UISectionName));
				}
				if (UI.UIOrder != 0)
				{
					Md += FString::Printf(TEXT("| UIOrder | `%d` |\n"), UI.UIOrder);
				}
				Md += TEXT("\n");
			}

			TOptional<int32> RTCountOpt = CallInt(CO, TEXT("GetStateParameterCount"), NameArgs);
			const int32 RTCount = RTCountOpt.IsSet() ? RTCountOpt.GetValue() : 0;
			if (RTCount == 0)
			{
				Md += TEXT("_No runtime-editable parameters for this state._\n\n");
				continue;
			}

			TArray<FString> RTNames;
			RTNames.Reserve(RTCount);
			for (int32 p = 0; p < RTCount; ++p)
			{
				TArray<FString> Args;
				Args.Add(StateName);
				Args.Add(FString::Printf(TEXT("%d"), p));
				TOptional<FString> N = CallString(CO, TEXT("GetStateParameterName"), Args);
				RTNames.Add(N.IsSet() ? N.GetValue() : FString());
			}
			RTNames.Sort([](const FString& A, const FString& B)
			{
				return A.Compare(B, ESearchCase::IgnoreCase) < 0;
			});

			Md += FString::Printf(TEXT("**Runtime-editable parameters (%d):**\n\n"), RTCount);
			for (const FString& RTName : RTNames)
			{
				Md += FString::Printf(TEXT("- `%s`\n"), *EscTbl(RTName));
			}
			Md += TEXT("\n");
		}
	}

	// ---- Components section ----
	//
	// `GetComponentCount()` + `GetComponentName(i)` expose the authored
	// mesh-component set. Each component corresponds to a Mesh Component
	// node in the graph (post-5.6 — LODSettings moved from the UCO root
	// to those nodes). `GetSkeletalMeshComponentReferenceSkeletalMesh`
	// takes a FName key — ImportText on a FNameProperty arg accepts the
	// bare string form, so we pass the name round-trip.
	void RenderComponentSection(FString& Md, UObject* CO)
	{
		TOptional<int32> CountOpt = CallInt(CO, TEXT("GetComponentCount"));
		if (!CountOpt.IsSet())
		{
			Md += TEXT("## Components\n\n");
			Md += TEXT("_Unable to read component count — `GetComponentCount` UFUNCTION not found on this object._\n\n");
			return;
		}
		const int32 Count = CountOpt.GetValue();
		Md += FString::Printf(TEXT("## Components (%d)\n\n"), Count);

		if (Count == 0)
		{
			Md += TEXT("_No mesh components declared (the asset may lack Mesh Component nodes, or may not be compiled)._\n\n");
			return;
		}

		TArray<FString> Names;
		Names.Reserve(Count);
		for (int32 i = 0; i < Count; ++i)
		{
			TArray<FString> Args;
			Args.Add(FString::Printf(TEXT("%d"), i));
			TOptional<FName> N = CallFName(CO, TEXT("GetComponentName"), Args);
			Names.Add(N.IsSet() ? N.GetValue().ToString() : FString());
		}
		Names.Sort([](const FString& A, const FString& B)
		{
			return A.Compare(B, ESearchCase::IgnoreCase) < 0;
		});

		Md += TEXT("| Name | Reference skeletal mesh |\n|---|---|\n");
		for (const FString& Name : Names)
		{
			TArray<FString> NameArgs;
			NameArgs.Add(Name);
			TOptional<UObject*> RefOpt = CallObject(CO, TEXT("GetSkeletalMeshComponentReferenceSkeletalMesh"), NameArgs);
			const UObject* Ref = RefOpt.IsSet() ? RefOpt.GetValue() : nullptr;
			Md += FString::Printf(TEXT("| `%s` | %s |\n"),
				*EscTbl(Name),
				Ref ? *FString::Printf(TEXT("`%s`"), *EscTbl(Ref->GetPathName())) : TEXT("—"));
		}
		Md += TEXT("\n");
	}

	// Node graph rendered via the shared `RenderEdGraphNodes` helper in
	// DeepRenderShared — same walker is reused by the M29.3 macro library
	// renderer. Caller emits its own section heading above the walker.
	void RenderNodeGraph(FString& Md, UEdGraph* Graph)
	{
		Md += TEXT("## Node Graph\n\n");
		BlueprintExporter::DeepRender::RenderEdGraphNodes(Md, Graph);
	}

	// Stable yes/no/not-reachable rendering for the two bool-returning
	// identity flags. "_not reachable_" when the UFUNCTION doesn't exist on
	// this class (the Mutable module is absent or was stripped) — honors
	// "Never guess values".
	FString RenderBoolFlag(TOptional<bool> V)
	{
		if (!V.IsSet())
		{
			return FString(TEXT("_not reachable_"));
		}
		return V.GetValue() ? FString(TEXT("yes")) : FString(TEXT("no"));
	}

	FString DoRenderUCO(UObject* CO)
	{
		FString Md;
		Md.Reserve(64 * 1024);

		Md += FString::Printf(TEXT("# %s — Deep Dump (Tier 2)\n\n"), *CO->GetName());
		Md += TEXT("> Generated by `DeepDump` for a Mutable `UCustomizableObject`. Exposes the full authoring surface — parameter schema, states, components, compile options, and the editor node graph — via a combination of the UCO's public BlueprintCallable accessors (parameters / states / components) and live `UEdGraph` reflection (node graph). The compiled-model blob (`Private` companion + `BulkData` + `VersionId`) is deliberately skipped: it regenerates on save and carries build-context-dependent fields that would destroy twin-run byte-identity. See `## Not rendered` at the bottom for the full exclusion list.\n\n");

		// ---- Identity ----
		Md += TEXT("## Identity\n\n");
		Md += TEXT("| Field | Value |\n|---|---|\n");
		Md += FString::Printf(TEXT("| Asset path | `%s` |\n"), *EscTbl(CO->GetPathName()));
		Md += FString::Printf(TEXT("| Asset name | `%s` |\n"), *EscTbl(CO->GetName()));
		Md += TEXT("| Asset type | `CustomizableObject` |\n");
		UClass* Cls = CO->GetClass();
		UClass* ParentCls = Cls ? Cls->GetSuperClass() : nullptr;
		if (ParentCls)
		{
			Md += FString::Printf(TEXT("| Parent class | `%s` |\n"), *EscTbl(ParentCls->GetPathName()));
		}
		{
			TOptional<bool> IsCompiledOpt = CallBool(CO, TEXT("IsCompiled"));
			Md += FString::Printf(TEXT("| IsCompiled | %s |\n"), *RenderBoolFlag(IsCompiledOpt));
		}
#if WITH_EDITOR
		{
			TOptional<bool> IsChildOpt = CallBool(CO, TEXT("IsChildObject"));
			Md += FString::Printf(TEXT("| IsChildObject | %s |\n"), *RenderBoolFlag(IsChildOpt));
		}
#endif
		Md += TEXT("\n");

		// ---- Runtime-facing options (always visible UPROPERTYs) ----
		//
		// Rendered via the shared helper so alpha order + table shape match
		// every other Tier 2 section — filter out the editor-only fields
		// (we dump those explicitly below) and the CO-specific plumbing.
		Md += TEXT("## Runtime Options\n\n");
		{
			TSet<FName> Plumbing;
			// Editor-only fields that the renderer handles in its own section.
			Plumbing.Add(FName(TEXT("VersionBridge")));
			Plumbing.Add(FName(TEXT("VersionStruct")));
			Plumbing.Add(FName(TEXT("WorkingSet")));
			Plumbing.Add(FName(TEXT("Source")));
			Plumbing.Add(FName(TEXT("VersionId")));
			Plumbing.Add(FName(TEXT("InstancePropertiesProfiles")));
			// Private / bulk / deprecated inline fields we explicitly skip.
			Plumbing.Add(FName(TEXT("Private")));
			Plumbing.Add(FName(TEXT("BulkData")));
			Plumbing.Add(FName(TEXT("LODSettings")));
			Plumbing.Add(FName(TEXT("ReferenceSkeletalMesh_DEPRECATED")));
			Plumbing.Add(FName(TEXT("ReferenceSkeletalMeshes_DEPRECATED")));
			Plumbing.Add(FName(TEXT("CompileOptions_DEPRECATED")));
			// Compile-option flags rendered separately below.
			Plumbing.Add(FName(TEXT("bEnableRealTimeMorphTargets")));
			Plumbing.Add(FName(TEXT("bEnableClothing")));
			Plumbing.Add(FName(TEXT("bEnable16BitBoneWeights")));
			Plumbing.Add(FName(TEXT("bEnableAltSkinWeightProfiles")));
			Plumbing.Add(FName(TEXT("bEnablePhysicsAssetMerge")));
			Plumbing.Add(FName(TEXT("bEnableAnimBpPhysicsAssetsManipulation")));
			Plumbing.Add(FName(TEXT("bEnableAssetUserDataMerge")));
			Plumbing.Add(FName(TEXT("bDisableTableMaterialsParentCheck")));
			Plumbing.Add(FName(TEXT("MeshCompileType")));
			// Tags tracked separately (internal to Mutable Population system).
			Plumbing.Add(FName(TEXT("CustomizableObjectClassTags")));
			Plumbing.Add(FName(TEXT("PopulationClassTags")));
			Plumbing.Add(FName(TEXT("CustomizableObjectParametersTags")));
			Plumbing.Add(FName(TEXT("LowPriorityTextures")));
			Plumbing.Add(FName(TEXT("bIsChildObject")));

			const int32 N = RenderUObjectPropertiesTable(Md, CO, Plumbing);
			if (N == 0)
			{
				Md += TEXT("_(no runtime options at non-default values)_\n\n");
			}
		}

		// ---- Compile options (editor-only) ----
#if WITH_EDITORONLY_DATA
		Md += TEXT("## Compile Options (editor-only)\n\n");
		{
			// Reflect the specific compile-option subset as its own table so
			// a reader can see them together without scanning a 40-row dump.
			struct FPropField { const TCHAR* Name; };
			static const FPropField Fields[] = {
				{ TEXT("MeshCompileType") },
				{ TEXT("bEnableRealTimeMorphTargets") },
				{ TEXT("bEnableClothing") },
				{ TEXT("bEnable16BitBoneWeights") },
				{ TEXT("bEnableAltSkinWeightProfiles") },
				{ TEXT("bEnablePhysicsAssetMerge") },
				{ TEXT("bEnableAnimBpPhysicsAssetsManipulation") },
				{ TEXT("bEnableAssetUserDataMerge") },
				{ TEXT("bDisableTableMaterialsParentCheck") },
			};

			struct FRow { FString Name; FString Type; FString Value; };
			TArray<FRow> Rows;
			UClass* COClass = CO->GetClass();
			for (const FPropField& F : Fields)
			{
				FProperty* P = FindFProperty<FProperty>(COClass, F.Name);
				if (!P) continue;
				FRow R;
				R.Name = P->GetName();
				R.Type = P->GetCPPType();
				const void* ValuePtr = P->ContainerPtrToValuePtr<void>(CO);
				P->ExportTextItem_Direct(R.Value, ValuePtr, nullptr, nullptr, PPF_None);
				Rows.Add(MoveTemp(R));
			}
			Rows.Sort([](const FRow& A, const FRow& B){ return A.Name.Compare(B.Name, ESearchCase::IgnoreCase) < 0; });
			if (Rows.Num() > 0)
			{
				Md += TEXT("| Property | Type | Value |\n|---|---|---|\n");
				for (const FRow& R : Rows)
				{
					const FString ValueCell = R.Value.IsEmpty() ? FString(TEXT("—")) : FString::Printf(TEXT("`%s`"), *EscTbl(R.Value));
					Md += FString::Printf(TEXT("| `%s` | `%s` | %s |\n"), *EscTbl(R.Name), *EscTbl(R.Type), *ValueCell);
				}
				Md += TEXT("\n");
			}
			else
			{
				Md += TEXT("_(compile-option UPROPERTYs not reachable — Mutable module layout may have changed)_\n\n");
			}

			// VersionBridge + VersionStruct as a separate mini-section — low
			// hit rate in authored assets but load-bearing when used (cook
			// filtering).
			FObjectProperty* BridgeProp = FindFProperty<FObjectProperty>(COClass, TEXT("VersionBridge"));
			UObject* Bridge = BridgeProp ? BridgeProp->GetObjectPropertyValue_InContainer(CO) : nullptr;
			Md += FString::Printf(TEXT("_VersionBridge:_ %s\n\n"),
				Bridge ? *FString::Printf(TEXT("`%s`"), *EscTbl(Bridge->GetPathName())) : TEXT("—"));

			// WorkingSet (TArray<TSoftObjectPtr<UCustomizableObject>>).
			FArrayProperty* WsProp = FindFProperty<FArrayProperty>(COClass, TEXT("WorkingSet"));
			if (WsProp)
			{
				FScriptArrayHelper WsHelper(WsProp, WsProp->ContainerPtrToValuePtr<void>(CO));
				const int32 WsNum = WsHelper.Num();
				Md += FString::Printf(TEXT("**Working Set (%d):**\n\n"), WsNum);
				if (WsNum == 0)
				{
					Md += TEXT("_(none)_\n\n");
				}
				else
				{
					for (int32 w = 0; w < WsNum; ++w)
					{
						FString Entry;
						WsProp->Inner->ExportTextItem_Direct(Entry, WsHelper.GetRawPtr(w), nullptr, nullptr, PPF_None);
						Md += FString::Printf(TEXT("- `%s`\n"), *EscTbl(Entry));
					}
					Md += TEXT("\n");
				}
			}
		}
#else
		Md += TEXT("## Compile Options (editor-only)\n\n_Not available — this build has `WITH_EDITORONLY_DATA=0`._\n\n");
#endif

		// ---- Components ----
		RenderComponentSection(Md, CO);

		// ---- Parameters ----
		RenderParameterSection(Md, CO);

		// ---- States ----
		RenderStateSection(Md, CO);

		// ---- Node graph ----
		UEdGraph* Graph = ResolveSourceGraph(CO);
		RenderNodeGraph(Md, Graph);

		// ---- Exclusion notice ----
		Md += TEXT("## Not rendered\n\n");
		Md += TEXT("The following surfaces are intentionally excluded:\n\n");
		Md += TEXT("- **Compiled model / private data** (`Private` companion object + `BulkData` + `VersionId`) — the compiled representation is derived data, regenerated on save; `VersionId` is explicitly rewritten per the Mutable header comment. Including it would destroy twin-run byte-identity. See the M29.0 policy note in `WIP_INVENTORY.md`.\n");
		Md += TEXT("- **Cooked-platform caches** — built via `BeginCacheForCookedPlatformData` at cook time, not part of the authoring surface.\n");
		Md += TEXT("- **Population tags / parameter tags** (`CustomizableObjectClassTags`, `PopulationClassTags`, `CustomizableObjectParametersTags`) — Mutable Population system internals, surfaced in a future slice if a driver appears.\n");
		Md += TEXT("- **`LowPriorityTextures`** — texture-streaming hint, not authoring signal for parameter / state / graph analysis.\n");
		Md += TEXT("- **Deprecated inline fields** (`LODSettings`, `ReferenceSkeletalMesh_DEPRECATED`, `ReferenceSkeletalMeshes_DEPRECATED`, `CompileOptions_DEPRECATED`) — superseded storage; skipped to avoid double-counting.\n");

		return Md;
	}
}

namespace BlueprintExporter::DeepDump
{
	FString RenderCustomizableObjectMarkdown(UObject* InObject)
	{
		if (!InObject)
		{
			return RenderOutOfScopeNotice(FString(TEXT("(null)")), FString(), TEXT("not UCustomizableObject"));
		}

		// Class-name-match dispatch — no compile-time dep on the Mutable
		// UClass. Any project that doesn't have Mutable loaded will never
		// enter this branch (no UObject with that class name exists), so the
		// renderer degrades gracefully to the out-of-scope notice without
		// needing a `#if WITH_MUTABLE_SUPPORT` gate.
		const UClass* Cls = InObject->GetClass();
		const bool bIsUCO = Cls && Cls->GetFName() == FName(TEXT("CustomizableObject"));
		if (!bIsUCO)
		{
			return RenderOutOfScopeNotice(
				InObject->GetName(),
				InObject->GetPathName(),
				TEXT("not UCustomizableObject"));
		}

		return DoRenderUCO(InObject);
	}
}
