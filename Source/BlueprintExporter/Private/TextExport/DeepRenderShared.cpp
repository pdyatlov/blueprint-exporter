// Copyright 10 Chambers. All Rights Reserved.

#include "TextExport/DeepRenderShared.h"

#include "UObject/Object.h"
#include "UObject/UnrealType.h"
#include "UObject/Class.h"
#include "UObject/EnumProperty.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraph/EdGraphPin.h"
#include "HAL/UnrealMemory.h"

namespace BlueprintExporter::DeepRender
{
	FString EscTbl(const FString& In)
	{
		FString Out = In;
		Out.ReplaceInline(TEXT("|"), TEXT("\\|"));
		Out.ReplaceInline(TEXT("\r\n"), TEXT(" "));
		Out.ReplaceInline(TEXT("\n"), TEXT(" "));
		Out.ReplaceInline(TEXT("\r"), TEXT(""));
		return Out;
	}

	bool IsCommonPlumbingProperty(FName Name)
	{
		static const TSet<FName> Plumbing = {
			FName(TEXT("UberGraphFrame")),
			FName(TEXT("CachedFrameStateTree")),
		};
		return Plumbing.Contains(Name);
	}

	int32 RenderUObjectPropertiesTable(FString& Md, const UObject* Obj, const TSet<FName>& AdditionalPlumbing)
	{
		if (!Obj)
		{
			return 0;
		}

		struct FRow { FString Name; FString Type; FString Value; };
		TArray<FRow> Rows;

		for (TFieldIterator<FProperty> It(Obj->GetClass()); It; ++It)
		{
			FProperty* P = *It;
			if (!P)
			{
				continue;
			}
			const FName PropName = P->GetFName();
			if (IsCommonPlumbingProperty(PropName) || AdditionalPlumbing.Contains(PropName))
			{
				continue;
			}
			FRow R;
			R.Name = P->GetName();
			R.Type = P->GetCPPType();
			const void* ValuePtr = P->ContainerPtrToValuePtr<void>(Obj);
			P->ExportTextItem_Direct(R.Value, ValuePtr, nullptr, nullptr, PPF_None);
			Rows.Add(MoveTemp(R));
		}

		if (Rows.Num() == 0)
		{
			return 0;
		}

		Rows.Sort([](const FRow& A, const FRow& B)
		{
			return A.Name.Compare(B.Name, ESearchCase::IgnoreCase) < 0;
		});

		Md += TEXT("| Property | Type | Value |\n");
		Md += TEXT("|---|---|---|\n");
		for (const FRow& R : Rows)
		{
			const FString ValueCell = R.Value.IsEmpty()
				? FString(TEXT("—"))
				: FString::Printf(TEXT("`%s`"), *EscTbl(R.Value));
			Md += FString::Printf(TEXT("| `%s` | `%s` | %s |\n"),
				*EscTbl(R.Name), *EscTbl(R.Type), *ValueCell);
		}
		Md += TEXT("\n");
		return Rows.Num();
	}

	int32 RenderStructFieldsTable(FString& Md, const UScriptStruct* Type, const void* Memory)
	{
		if (!Type || !Memory)
		{
			return 0;
		}

		struct FRow { FString Name; FString Type; FString Value; };
		TArray<FRow> Rows;

		for (TFieldIterator<FProperty> It(Type); It; ++It)
		{
			FProperty* P = *It;
			if (!P || IsCommonPlumbingProperty(P->GetFName()))
			{
				continue;
			}
			FRow R;
			R.Name = P->GetName();
			R.Type = P->GetCPPType();
			const void* ValuePtr = P->ContainerPtrToValuePtr<void>(Memory);
			P->ExportTextItem_Direct(R.Value, ValuePtr, nullptr, nullptr, PPF_None);
			Rows.Add(MoveTemp(R));
		}

		if (Rows.Num() == 0)
		{
			return 0;
		}

		Rows.Sort([](const FRow& A, const FRow& B)
		{
			return A.Name.Compare(B.Name, ESearchCase::IgnoreCase) < 0;
		});

		Md += TEXT("| Field | Type | Value |\n");
		Md += TEXT("|---|---|---|\n");
		for (const FRow& R : Rows)
		{
			const FString ValueCell = R.Value.IsEmpty()
				? FString(TEXT("—"))
				: FString::Printf(TEXT("`%s`"), *EscTbl(R.Value));
			Md += FString::Printf(TEXT("| `%s` | `%s` | %s |\n"),
				*EscTbl(R.Name), *EscTbl(R.Type), *ValueCell);
		}
		Md += TEXT("\n");
		return Rows.Num();
	}

	const TSet<FName>& EdGraphNodePlumbing()
	{
		static const TSet<FName> Set = {
			FName(TEXT("NodePosX")),
			FName(TEXT("NodePosY")),
			FName(TEXT("NodeWidth")),
			FName(TEXT("NodeHeight")),
			FName(TEXT("NodeGuid")),
			FName(TEXT("NodeComment")),
			FName(TEXT("bCommentBubblePinned")),
			FName(TEXT("bCommentBubbleVisible")),
			FName(TEXT("bCommentBubbleMakeVisible")),
			FName(TEXT("bCanRenameNode")),
			FName(TEXT("bIsBoundBy")),
			FName(TEXT("EnabledState")),
			FName(TEXT("bDisabled")),
			FName(TEXT("bUserSetEnabledState")),
			FName(TEXT("bHasCompilerMessage")),
			FName(TEXT("ErrorType")),
			FName(TEXT("ErrorMsg")),
			FName(TEXT("CompilerMessage")),
			FName(TEXT("CompilerMessageCount")),
			FName(TEXT("AdvancedPinDisplay")),
			FName(TEXT("DeprecationResponse")),
			FName(TEXT("Pins")),
			FName(TEXT("DeprecatedPins")),
		};
		return Set;
	}

	void MaskPinGuids(FString& InOutText, int32 StartOffset)
	{
		int32 SearchFrom = StartOffset;
		const FString Needle(TEXT("PinId="));
		while (true)
		{
			const int32 Idx = InOutText.Find(Needle, ESearchCase::CaseSensitive, ESearchDir::FromStart, SearchFrom);
			if (Idx == INDEX_NONE)
			{
				return;
			}
			const int32 HexStart = Idx + Needle.Len();
			int32 HexEnd = HexStart;
			while (HexEnd < InOutText.Len() && HexEnd - HexStart < 32)
			{
				const TCHAR C = InOutText[HexEnd];
				const bool bHex = (C >= TEXT('0') && C <= TEXT('9'))
					|| (C >= TEXT('A') && C <= TEXT('F'))
					|| (C >= TEXT('a') && C <= TEXT('f'));
				if (!bHex) break;
				++HexEnd;
			}
			if (HexEnd - HexStart == 32)
			{
				const FString Replacement(TEXT("<unstable>"));
				InOutText.RemoveAt(HexStart, 32, EAllowShrinking::No);
				InOutText.InsertAt(HexStart, Replacement);
				SearchFrom = HexStart + Replacement.Len();
			}
			else
			{
				SearchFrom = HexEnd;
			}
		}
	}

	void RenderEdGraphNodes(FString& Md, const UEdGraph* Graph)
	{
		if (!Graph)
		{
			Md += TEXT("_Graph not reachable — either the asset was loaded without editor-only data, or the graph-holding UPROPERTY could not be resolved via reflection. No node walk performed (honoring \"Never guess values\")._\n\n");
			return;
		}

		const int32 NodeCount = Graph->Nodes.Num();
		if (NodeCount == 0)
		{
			Md += TEXT("_Graph has no nodes._\n\n");
			return;
		}

		Md += FString::Printf(TEXT("Graph has **%d** nodes. Listed in authored order (matches editor linear node list). Outgoing connections list output-pin edges only; input-pin edges are the inverse of some other node's output edges and are intentionally not duplicated.\n\n"), NodeCount);

		const int32 NodeSectionStart = Md.Len();
		const TSet<FName>& Plumbing = EdGraphNodePlumbing();

		for (int32 i = 0; i < NodeCount; ++i)
		{
			UEdGraphNode* Node = Graph->Nodes[i];
			if (!Node)
			{
				Md += FString::Printf(TEXT("### Node %d — `(null reference)`\n\n_(null node slot in graph at export time)_\n\n"), i);
				continue;
			}

			const FString ClassName = Node->GetClass()->GetName();
			const FString NodeName = Node->GetName();
			const FText NodeTitle = Node->GetNodeTitle(ENodeTitleType::ListView);

			Md += FString::Printf(TEXT("### Node %d — `%s`\n\n"), i, *NodeName);
			Md += TEXT("| Field | Value |\n|---|---|\n");
			Md += FString::Printf(TEXT("| Node class | `%s` |\n"), *EscTbl(ClassName));
			Md += FString::Printf(TEXT("| Title | `%s` |\n"), *EscTbl(NodeTitle.ToString()));
			Md += TEXT("\n");

			Md += TEXT("**Properties:**\n\n");
			const int32 N = RenderUObjectPropertiesTable(Md, Node, Plumbing);
			if (N == 0)
			{
				Md += TEXT("_(no authored properties)_\n\n");
			}

			int32 OutCount = 0;
			for (const UEdGraphPin* P : Node->Pins)
			{
				if (P && P->Direction == EGPD_Output && P->LinkedTo.Num() > 0)
				{
					OutCount += P->LinkedTo.Num();
				}
			}
			if (OutCount > 0)
			{
				Md += FString::Printf(TEXT("**Outgoing connections (%d):**\n\n"), OutCount);
				Md += TEXT("| Out pin | Target node | Target class | Target pin |\n|---|---|---|---|\n");
				for (UEdGraphPin* P : Node->Pins)
				{
					if (!P || P->Direction != EGPD_Output)
					{
						continue;
					}
					for (UEdGraphPin* L : P->LinkedTo)
					{
						if (!L)
						{
							continue;
						}
						UEdGraphNode* Owner = L->GetOwningNode();
						const FString OwnerName = Owner ? Owner->GetName() : FString(TEXT("?"));
						const FString OwnerClass = Owner ? Owner->GetClass()->GetName() : FString(TEXT("?"));
						Md += FString::Printf(TEXT("| `%s` | `%s` | `%s` | `%s` |\n"),
							*EscTbl(P->PinName.ToString()),
							*EscTbl(OwnerName),
							*EscTbl(OwnerClass),
							*EscTbl(L->PinName.ToString()));
					}
				}
				Md += TEXT("\n");
			}
		}

		MaskPinGuids(Md, NodeSectionStart);
	}

	namespace UFunctionCall
	{
		namespace
		{
			// Walk the param list of a UFUNCTION once, separating input params
			// from the return-parm property. Both are marked with CPF_Parm; the
			// return adds CPF_ReturnParm. Order is the declaration order that
			// ProcessEvent expects.
			void GatherParams(UFunction* Fn, TArray<FProperty*, TInlineAllocator<8>>& OutInputs, FProperty*& OutReturn)
			{
				OutReturn = nullptr;
				for (TFieldIterator<FProperty> It(Fn); It && (It->PropertyFlags & CPF_Parm); ++It)
				{
					FProperty* Prop = *It;
					if (Prop->PropertyFlags & CPF_ReturnParm)
					{
						OutReturn = Prop;
					}
					else
					{
						OutInputs.Add(Prop);
					}
				}
			}

			void DestroyAllParams(UFunction* Fn, void* ParamsBuffer)
			{
				for (TFieldIterator<FProperty> It(Fn); It && (It->PropertyFlags & CPF_Parm); ++It)
				{
					It->DestroyValue_InContainer(ParamsBuffer);
				}
			}
		}

		bool CallUFunctionRaw(
			UObject* Obj,
			FName FunctionName,
			const TArray<FString>& Args,
			TFunctionRef<void(FProperty*, const void*)> ReturnCallback)
		{
			if (!Obj)
			{
				return false;
			}

			UClass* Cls = Obj->GetClass();
			if (!Cls)
			{
				return false;
			}

			UFunction* Fn = Cls->FindFunctionByName(FunctionName);
			if (!Fn)
			{
				// Graceful miss — caller's render path prints the "not reachable"
				// marker. No log spam; a missing optional-module UFUNCTION is an
				// expected runtime state, not an error.
				return false;
			}

			// FMemory_Alloca is aliased to platform `alloca` — memory auto-frees
			// at function return; no leak path even on the early-out branches.
			uint8* Params = (uint8*)FMemory_Alloca(Fn->ParmsSize);
			FMemory::Memzero(Params, Fn->ParmsSize);

			TArray<FProperty*, TInlineAllocator<8>> InputParams;
			FProperty* ReturnProp = nullptr;
			GatherParams(Fn, InputParams, ReturnProp);

			for (TFieldIterator<FProperty> It(Fn); It && (It->PropertyFlags & CPF_Parm); ++It)
			{
				It->InitializeValue_InContainer(Params);
			}

			if (InputParams.Num() != Args.Num())
			{
				DestroyAllParams(Fn, Params);
				return false;
			}

			for (int32 i = 0; i < InputParams.Num(); ++i)
			{
				FProperty* Prop = InputParams[i];
				void* ValuePtr = Prop->ContainerPtrToValuePtr<void>(Params);
				const TCHAR* Consumed = Prop->ImportText_Direct(*Args[i], ValuePtr, nullptr, PPF_None);
				if (!Consumed)
				{
					DestroyAllParams(Fn, Params);
					return false;
				}
			}

			Obj->ProcessEvent(Fn, Params);

			if (ReturnProp)
			{
				const void* ReturnPtr = ReturnProp->ContainerPtrToValuePtr<void>(Params);
				ReturnCallback(ReturnProp, ReturnPtr);
			}

			DestroyAllParams(Fn, Params);
			return true;
		}

		TOptional<bool> CallBool(UObject* Obj, FName FuncName, const TArray<FString>& Args)
		{
			TOptional<bool> Result;
			CallUFunctionRaw(Obj, FuncName, Args, [&Result](FProperty* ReturnProp, const void* ReturnValuePtr)
			{
				if (FBoolProperty* BoolProp = CastField<FBoolProperty>(ReturnProp))
				{
					Result = BoolProp->GetPropertyValue(ReturnValuePtr);
				}
			});
			return Result;
		}

		TOptional<int32> CallInt(UObject* Obj, FName FuncName, const TArray<FString>& Args)
		{
			TOptional<int32> Result;
			CallUFunctionRaw(Obj, FuncName, Args, [&Result](FProperty* ReturnProp, const void* ReturnValuePtr)
			{
				if (FIntProperty* IntProp = CastField<FIntProperty>(ReturnProp))
				{
					Result = IntProp->GetPropertyValue(ReturnValuePtr);
				}
			});
			return Result;
		}

		TOptional<int64> CallEnumInt64(UObject* Obj, FName FuncName, const TArray<FString>& Args)
		{
			TOptional<int64> Result;
			CallUFunctionRaw(Obj, FuncName, Args, [&Result](FProperty* ReturnProp, const void* ReturnValuePtr)
			{
				if (FEnumProperty* EnumProp = CastField<FEnumProperty>(ReturnProp))
				{
					Result = EnumProp->GetUnderlyingProperty()->GetSignedIntPropertyValue(ReturnValuePtr);
				}
				else if (FByteProperty* ByteProp = CastField<FByteProperty>(ReturnProp))
				{
					if (ByteProp->Enum)
					{
						Result = (int64)ByteProp->GetPropertyValue(ReturnValuePtr);
					}
				}
			});
			return Result;
		}

		TOptional<float> CallFloat(UObject* Obj, FName FuncName, const TArray<FString>& Args)
		{
			TOptional<float> Result;
			CallUFunctionRaw(Obj, FuncName, Args, [&Result](FProperty* ReturnProp, const void* ReturnValuePtr)
			{
				if (FFloatProperty* FloatProp = CastField<FFloatProperty>(ReturnProp))
				{
					Result = FloatProp->GetPropertyValue(ReturnValuePtr);
				}
				else if (FDoubleProperty* DoubleProp = CastField<FDoubleProperty>(ReturnProp))
				{
					Result = (float)DoubleProp->GetPropertyValue(ReturnValuePtr);
				}
			});
			return Result;
		}

		TOptional<FString> CallString(UObject* Obj, FName FuncName, const TArray<FString>& Args)
		{
			TOptional<FString> Result;
			CallUFunctionRaw(Obj, FuncName, Args, [&Result](FProperty* ReturnProp, const void* ReturnValuePtr)
			{
				if (FStrProperty* StrProp = CastField<FStrProperty>(ReturnProp))
				{
					Result = StrProp->GetPropertyValue(ReturnValuePtr);
				}
			});
			return Result;
		}

		TOptional<FName> CallFName(UObject* Obj, FName FuncName, const TArray<FString>& Args)
		{
			TOptional<FName> Result;
			CallUFunctionRaw(Obj, FuncName, Args, [&Result](FProperty* ReturnProp, const void* ReturnValuePtr)
			{
				if (FNameProperty* NameProp = CastField<FNameProperty>(ReturnProp))
				{
					Result = NameProp->GetPropertyValue(ReturnValuePtr);
				}
			});
			return Result;
		}

		TOptional<UObject*> CallObject(UObject* Obj, FName FuncName, const TArray<FString>& Args)
		{
			TOptional<UObject*> Result;
			CallUFunctionRaw(Obj, FuncName, Args, [&Result](FProperty* ReturnProp, const void* ReturnValuePtr)
			{
				if (FObjectProperty* ObjProp = CastField<FObjectProperty>(ReturnProp))
				{
					Result = ObjProp->GetObjectPropertyValue(ReturnValuePtr);
				}
			});
			return Result;
		}
	}
}
