// Copyright 10 Chambers. All Rights Reserved.

#include "Reflection/ReflectionOps.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Curves/CurveFloat.h"
#include "Engine/DataAsset.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryOption.h"
#include "EnvironmentQuery/EnvQueryGenerator.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "Components/ActorComponent.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraphSchema_K2.h"
#include "Engine/Blueprint.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/MemberReference.h"
#include "Engine/SCS_Node.h"
#include "Engine/SimpleConstructionScript.h"
#include "K2Node_AddPinInterface.h"
#include "K2Node_CallFunction.h"
#include "K2Node_CustomEvent.h"
#include "K2Node_DynamicCast.h"
#include "K2Node_EditablePinBase.h"
#include "K2Node_ExecutionSequence.h"
#include "BlueprintEditorSettings.h"
#include "K2Node_Event.h"
#include "K2Node_FunctionEntry.h"
#include "K2Node_FunctionResult.h"
#include "K2Node_IfThenElse.h"
#include "K2Node_BreakStruct.h"
#include "K2Node_MacroInstance.h"
#include "K2Node_MakeStruct.h"
#include "K2Node_SetFieldsInStruct.h"
#include "K2Node_VariableGet.h"
#include "K2Node_VariableSet.h"
#include "StructUtils/InstancedStruct.h"
#include "StructUtils/UserDefinedStruct.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/Kismet2NameValidators.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Kismet2/StructureEditorUtils.h"
#include "UserDefinedStructure/UserDefinedStructEditorData.h"  // FStructVariableDescription
#include "Misc/PackageName.h"
#include "Misc/SecureHash.h"
#include "UObject/Package.h"
#include "UObject/SavePackage.h"
#include "UObject/UnrealType.h"
#include "UObject/UObjectGlobals.h"  // CollectGarbage

// M28.6.1 — GameplayTags author API. Editor-side `AddNewGameplayTagToINI`
// lives on `IGameplayTagsEditorModule` (editor plugin), runtime-side
// `IsDictionaryTag` lives on `UGameplayTagsManager` (runtime module).
#if WITH_GAMEPLAYTAGSEDITOR_SUPPORT
#include "GameplayTagsEditorModule.h"
#include "GameplayTagsManager.h"
#endif

DEFINE_LOG_CATEGORY_STATIC(LogBpxReflection, Log, All);

namespace BpxReflection
{
	/** Try to parse a path step as an array index. "[3]" -> 3, otherwise -1. */
	static int32 ParseArrayIndex(const FString& Step)
	{
		if (Step.Len() < 3 || Step[0] != TEXT('[') || Step[Step.Len() - 1] != TEXT(']'))
		{
			// Allow bare integers too
			int32 Parsed = INDEX_NONE;
			if (Step.IsNumeric() && LexTryParseString(Parsed, *Step))
			{
				return Parsed;
			}
			return INDEX_NONE;
		}
		const FString Inner = Step.Mid(1, Step.Len() - 2);
		int32 Parsed = INDEX_NONE;
		if (LexTryParseString(Parsed, *Inner))
		{
			return Parsed;
		}
		return INDEX_NONE;
	}

	/**
	 * Walk a path, stopping at the penultimate step. Returns the container
	 * pointer + final FProperty so callers can read or write. Also tracks the
	 * innermost UObject ancestor of the leaf, the UPROPERTY chain within
	 * that owner, and the array indices encountered along that chain —
	 * needed to fire PostEditChangeChainProperty after mutations of Instanced
	 * subobjects (M23.1.1 — mirrors UE's property-handle infrastructure in
	 * StateTreeEditorNodeDetails::OnNodePicked). StateTreePropertyHelpers.cpp
	 * asserts array indices are set on the event when the chain descends past
	 * an array property.
	 *
	 * Returns false on any navigation error and populates OutError.
	 */
	static bool ResolvePath(
		UObject* Root,
		const TArray<FString>& Path,
		void*& OutContainerPtr,
		FProperty*& OutFinalProperty,
		UObject*& OutInnermostOwner,
		TArray<FProperty*>& OutOwnerChain,
		TMap<FString, int32>& OutArrayIndices,
		FString& OutError)
	{
		OutContainerPtr = nullptr;
		OutFinalProperty = nullptr;
		OutInnermostOwner = nullptr;
		OutOwnerChain.Reset();
		OutArrayIndices.Reset();

		if (!Root)
		{
			OutError = TEXT("Root object is null");
			return false;
		}
		if (Path.Num() == 0)
		{
			OutError = TEXT("Path is empty");
			return false;
		}

		// CurrentContainer: the object whose class we'll look up properties on.
		// For UObject containers this is the UObject*; for nested struct-
		// property containers it's the raw pointer to the struct instance.
		// We track both Current (UObject* for outer-class lookups) and
		// CurrentMemory (void* for ContainerPtrToValuePtr).
		UObject* CurrentObject = Root;
		void* CurrentMemory = Root;
		UStruct* CurrentStruct = Root->GetClass();

		// Owner tracking: InnermostOwner is the last UObject the walker was
		// inside; OwnerChain is the list of FProperties from that owner's
		// top-level UPROPERTY down to the current step; ArrayIndices maps
		// each array property name to the index that was traversed. Reset
		// whenever we cross a UObject boundary (FObjectProperty resolve to
		// non-null).
		UObject* InnermostOwner = Root;
		TArray<FProperty*> OwnerChain;
		TMap<FString, int32> ArrayIndices;

		for (int32 StepIndex = 0; StepIndex < Path.Num(); ++StepIndex)
		{
			const FString& Step = Path[StepIndex];
			const bool bIsLeaf = (StepIndex == Path.Num() - 1);

			// Array index step — only valid when CurrentStruct/Memory is
			// *not* in play; it always follows a prior FArrayProperty resolve,
			// which is handled inside the non-index branch below.
			const int32 ParsedIndex = ParseArrayIndex(Step);
			if (ParsedIndex != INDEX_NONE)
			{
				OutError = FString::Printf(TEXT("Unexpected array index %d at path step %d — must follow an array property"),
					ParsedIndex, StepIndex);
				return false;
			}

			// Lookup property on current struct.
			FProperty* Prop = CurrentStruct
				? CurrentStruct->FindPropertyByName(FName(*Step))
				: nullptr;
			if (!Prop)
			{
				OutError = FString::Printf(TEXT("Property '%s' not found on %s (step %d)"),
					*Step, CurrentStruct ? *CurrentStruct->GetName() : TEXT("<null>"), StepIndex);
				return false;
			}

			// Track this property in the owner chain. If we later cross a
			// UObject boundary below, the chain resets — so transient entries
			// that belong to an intermediate UObject are correctly discarded.
			OwnerChain.Add(Prop);

			void* ValuePtr = Prop->ContainerPtrToValuePtr<void>(CurrentMemory);

			// Array support: if the NEXT step is an "[N]" index, descend
			// into FArrayProperty's Inner here.
			const bool bNextIsIndex =
				(StepIndex + 1 < Path.Num()) && ParseArrayIndex(Path[StepIndex + 1]) != INDEX_NONE;

			if (bNextIsIndex)
			{
				FArrayProperty* ArrProp = CastField<FArrayProperty>(Prop);
				if (!ArrProp)
				{
					OutError = FString::Printf(TEXT("Property '%s' at step %d is not an array but next step is an index"),
						*Step, StepIndex);
					return false;
				}
				FScriptArrayHelper ArrayHelper(ArrProp, ValuePtr);
				const int32 Index = ParseArrayIndex(Path[StepIndex + 1]);
				if (!ArrayHelper.IsValidIndex(Index))
				{
					OutError = FString::Printf(TEXT("Array index %d out of range for '%s' (size %d)"),
						Index, *Step, ArrayHelper.Num());
					return false;
				}
				uint8* ElemPtr = ArrayHelper.GetRawPtr(Index);
				FProperty* InnerProp = ArrProp->Inner;

				// Record array index under the array property's name so
				// DispatchPostEditToNodes can descend into the element.
				ArrayIndices.Add(Step, Index);

				// Did we land on the leaf?
				if (StepIndex + 1 == Path.Num() - 1)
				{
					// Leaf is the array element itself — Path like ["Foo", "[N]"]
					OutContainerPtr = ElemPtr;
					OutFinalProperty = InnerProp;
					OutInnermostOwner = InnermostOwner;
					OutOwnerChain = MoveTemp(OwnerChain);
					OutArrayIndices = MoveTemp(ArrayIndices);
					return true;
				}

				// Otherwise advance past both the array name AND the index.
				// Continue walking into whatever the inner is.
				if (FObjectProperty* InnerObjProp = CastField<FObjectProperty>(InnerProp))
				{
					CurrentObject = InnerObjProp->GetObjectPropertyValue(ElemPtr);
					if (!CurrentObject)
					{
						OutError = FString::Printf(TEXT("Array element '%s[%d]' is null (step %d)"),
							*Step, Index, StepIndex);
						return false;
					}
					CurrentMemory = CurrentObject;
					CurrentStruct = CurrentObject->GetClass();
					// Crossing UObject boundary: reset owner tracking.
					InnermostOwner = CurrentObject;
					OwnerChain.Reset();
					ArrayIndices.Reset();
				}
				else if (FStructProperty* InnerStructProp = CastField<FStructProperty>(InnerProp))
				{
					CurrentMemory = ElemPtr;
					CurrentStruct = InnerStructProp->Struct;
					CurrentObject = nullptr; // structs don't have an owner UObject for further navigation
					// No reset — struct-in-array stays within the current owner.
				}
				else
				{
					OutError = FString::Printf(TEXT("Can't navigate past array element — inner type '%s' is neither Object nor Struct"),
						*InnerProp->GetClass()->GetName());
					return false;
				}

				++StepIndex; // consume the index step too
				continue;
			}

			// Non-array navigation.
			if (bIsLeaf)
			{
				OutContainerPtr = CurrentMemory;
				OutFinalProperty = Prop;
				OutInnermostOwner = InnermostOwner;
				OutOwnerChain = MoveTemp(OwnerChain);
				OutArrayIndices = MoveTemp(ArrayIndices);
				return true;
			}

			// Intermediate step — chase object / struct pointers.
			if (FObjectProperty* ObjProp = CastField<FObjectProperty>(Prop))
			{
				UObject* Next = ObjProp->GetObjectPropertyValue(ValuePtr);
				if (!Next)
				{
					OutError = FString::Printf(TEXT("Object property '%s' is null at step %d"), *Step, StepIndex);
					return false;
				}
				CurrentObject = Next;
				CurrentMemory = Next;
				CurrentStruct = Next->GetClass();
				// Crossing UObject boundary: reset owner tracking.
				InnermostOwner = Next;
				OwnerChain.Reset();
				ArrayIndices.Reset();
			}
			else if (FStructProperty* StructProp = CastField<FStructProperty>(Prop))
			{
				// FInstancedStruct is a struct wrapper whose real payload is a
				// dynamic USCRIPTSTRUCT instance at runtime. To step INTO its
				// fields (e.g. `Node.ConditionClass` on a wrapper), read the
				// InstancedStruct's actual script struct + memory and continue
				// with those as the new container.
				if (StructProp->Struct == FInstancedStruct::StaticStruct())
				{
					FInstancedStruct* InstancedPtr = reinterpret_cast<FInstancedStruct*>(ValuePtr);
					const UScriptStruct* WrappedType = InstancedPtr->GetScriptStruct();
					if (!WrappedType)
					{
						OutError = FString::Printf(TEXT("FInstancedStruct '%s' has no script struct — call SetInstancedStructType first (step %d)"),
							*Step, StepIndex);
						return false;
					}
					CurrentMemory = InstancedPtr->GetMutableMemory();
					CurrentStruct = const_cast<UScriptStruct*>(WrappedType);
					CurrentObject = nullptr;
					// No UObject crossing; chain stays with current owner.
				}
				else
				{
					CurrentMemory = ValuePtr;
					CurrentStruct = StructProp->Struct;
					CurrentObject = nullptr;
					// No reset — nested struct stays within the current owner.
				}
			}
			else
			{
				OutError = FString::Printf(TEXT("Can't navigate past '%s' — type '%s' is neither Object nor Struct"),
					*Step, *Prop->GetClass()->GetName());
				return false;
			}
		}

		OutError = TEXT("Unreachable: walk ended without leaf");
		return false;
	}

	/**
	 * Fire PreEditChange + PostEditChangeChainProperty on Owner with a chain
	 * built from OwnerChain (outermost UPROPERTY first, leaf last). ArrayIndices
	 * maps each array-property name on the chain to the traversed element index,
	 * which StateTreePropertyHelpers.cpp:125 asserts on. Matches the UE editor's
	 * drag-drop BP-condition pattern (StateTreeEditorNodeDetails.cpp:2374-2385) —
	 * load-bearing for Instanced-subobject properties whose referenced UObjects
	 * would otherwise fail to persist through SavePackage (M23.1.1).
	 */
	static void NotifyPropertyChanged(
		UObject* Owner,
		const TArray<FProperty*>& OwnerChain,
		const TMap<FString, int32>& ArrayIndices,
		EPropertyChangeType::Type ChangeType)
	{
		if (!Owner || OwnerChain.Num() == 0)
		{
			return;
		}

		Owner->Modify();

		FEditPropertyChain PropertyChain;
		for (FProperty* Prop : OwnerChain)
		{
			PropertyChain.AddTail(Prop);
		}

		FProperty* MemberProperty = OwnerChain[0];    // outermost UPROPERTY on Owner's class
		FProperty* ActiveProperty = OwnerChain.Last(); // leaf being mutated

		PropertyChain.SetActiveMemberPropertyNode(MemberProperty);
		PropertyChain.SetActivePropertyNode(ActiveProperty);

		FPropertyChangedEvent BaseEvent(ActiveProperty, ChangeType);
		BaseEvent.SetActiveMemberProperty(MemberProperty);

		// SetArrayIndexPerObject takes a view over array-of-maps (one entry per
		// object being edited). Single-object edit → 1-element array, and
		// ObjectIteratorIndex must be 0 for GetArrayIndex to find it (default
		// is INDEX_NONE which makes the map lookup fail).
		TArray<TMap<FString, int32>> PerObject;
		PerObject.Add(ArrayIndices);
		BaseEvent.SetArrayIndexPerObject(PerObject);
		BaseEvent.ObjectIteratorIndex = 0;

		FPropertyChangedChainEvent ChainEvent(PropertyChain, BaseEvent);
		Owner->PostEditChangeChainProperty(ChainEvent);
	}

	/**
	 * Deterministic FGuid from an arbitrary string. Matches the Python
	 * `_deterministic_guid(*parts)` helper in `scripts/python_ops/statetree.py`
	 * bit-for-bit when called with `":".join(parts)` as the input — MD5 of
	 * UTF-8 bytes, first 4 bytes → A (big-endian), next 4 → B, etc.
	 *
	 * Used by M26.1 graph-authoring ops to seed Entry / Return / Get node
	 * GUIDs so the post-op asset bytes are reproducible across re-runs.
	 * Without this, UE's AddFunctionGraph uses FGuid::NewGuid(), breaking
	 * golden-fixture determinism.
	 */
	static FGuid SeedGuidFromJoined(const FString& Joined)
	{
		const FTCHARToUTF8 Utf8(*Joined);
		FMD5 Hasher;
		Hasher.Update(reinterpret_cast<const uint8*>(Utf8.Get()), Utf8.Length());
		uint8 Digest[16];
		Hasher.Final(Digest);
		auto Pack4BE = [](const uint8* B) -> uint32
		{
			return (uint32(B[0]) << 24) | (uint32(B[1]) << 16) | (uint32(B[2]) << 8) | uint32(B[3]);
		};
		return FGuid(Pack4BE(Digest + 0), Pack4BE(Digest + 4), Pack4BE(Digest + 8), Pack4BE(Digest + 12));
	}

	/** Seed `UEdGraphPin::PinId` on every pin of a node with deterministic
	 *  FGuids. UE's pin creation path (`AllocateDefaultPins` -> `CreatePin`)
	 *  assigns each `PinId` via `FGuid::NewGuid()`, which leaks through to
	 *  the serialized `.uasset` and breaks byte-determinism across
	 *  wipe+rebind cycles — M26.1.1's `force_rebind=True` soak surfaced
	 *  this: NodeGuids were stable but md5 still drifted because the
	 *  freshly-created VariableGet nodes carried random PinIds.
	 *
	 *  `JoinedPrefix` is the same string the caller used to seed the
	 *  node's NodeGuid; we append `":pin:<PinName>:<dir>"` per pin so
	 *  input/output pins with the same name don't collide. */
	static void SeedPinGuidsForNode(UEdGraphNode* Node, const FString& JoinedPrefix)
	{
		if (!Node)
		{
			return;
		}
		for (UEdGraphPin* Pin : Node->Pins)
		{
			if (!Pin)
			{
				continue;
			}
			const TCHAR* DirStr = (Pin->Direction == EGPD_Input) ? TEXT("in") : TEXT("out");
			Pin->PinId = SeedGuidFromJoined(
				JoinedPrefix + TEXT(":pin:") + Pin->PinName.ToString()
				+ TEXT(":") + DirStr);
		}
	}

	/** Find a graph on `Blueprint` by name, walking the three sources where
	 *  authorable K2 graphs live:
	 *    1. `FunctionGraphs` — regular member functions + user-created libs.
	 *    2. `ImplementedInterfaces[].Graphs` — interface-override graphs
	 *       (M26.1: `FBlueprintEditorUtils::AddFunctionGraph(..., InterfaceClass)`
	 *       stores them here, NOT on FunctionGraphs).
	 *    3. `UbergraphPages` — the event graph(s) ("EventGraph" by default).
	 *       M28.2 adds this walk so `ConnectPinsByName` / `FindGraphEndpoints`
	 *       / etc. can operate on nodes that live on the ubergraph — the
	 *       use case is authoring missing wires on existing event-graph
	 *       Branch / CallFunction nodes (driver: BP_Task_Peek Branch.else
	 *       dead-end in the Combat_FlatArena diagnosis).
	 *
	 *  Name kept as `FindFunctionGraphByName` for minimum-churn diff — the
	 *  argument is semantically a graph name now, not a function name. */
	static UEdGraph* FindFunctionGraphByName(UBlueprint* Blueprint, FName FunctionName)
	{
		if (!Blueprint || FunctionName.IsNone())
		{
			return nullptr;
		}
		for (UEdGraph* Graph : Blueprint->FunctionGraphs)
		{
			if (Graph && Graph->GetFName() == FunctionName)
			{
				return Graph;
			}
		}
		for (const FBPInterfaceDescription& IfaceDesc : Blueprint->ImplementedInterfaces)
		{
			for (UEdGraph* Graph : IfaceDesc.Graphs)
			{
				if (Graph && Graph->GetFName() == FunctionName)
				{
					return Graph;
				}
			}
		}
		for (UEdGraph* Graph : Blueprint->UbergraphPages)
		{
			if (Graph && Graph->GetFName() == FunctionName)
			{
				return Graph;
			}
		}
		return nullptr;
	}
} // namespace BpxReflection

FBpxReflectionResult UBpxReflectionOps::GetPropertyValue(UObject* Root, const TArray<FString>& Path)
{
	FBpxReflectionResult Result;

	void* ContainerPtr = nullptr;
	FProperty* FinalProp = nullptr;
	UObject* InnermostOwner = nullptr;
	TArray<FProperty*> OwnerChain;
	TMap<FString, int32> ArrayIndices;
	FString Err;
	if (!BpxReflection::ResolvePath(Root, Path, ContainerPtr, FinalProp, InnermostOwner, OwnerChain, ArrayIndices, Err))
	{
		Result.ErrorMessage = Err;
		return Result;
	}

	FString Out;
	const void* ValuePtr = FinalProp->ContainerPtrToValuePtr<void>(ContainerPtr);
	FinalProp->ExportTextItem_Direct(Out, ValuePtr, nullptr, nullptr, PPF_None);
	Result.BeforeText = Out;
	Result.AfterText = Out;
	Result.bSuccess = true;
	return Result;
}

FBpxReflectionResult UBpxReflectionOps::SetPropertyValue(UObject* Root, const TArray<FString>& Path, const FString& ImportTextValue)
{
	FBpxReflectionResult Result;

	void* ContainerPtr = nullptr;
	FProperty* FinalProp = nullptr;
	UObject* InnermostOwner = nullptr;
	TArray<FProperty*> OwnerChain;
	TMap<FString, int32> ArrayIndices;
	FString Err;
	if (!BpxReflection::ResolvePath(Root, Path, ContainerPtr, FinalProp, InnermostOwner, OwnerChain, ArrayIndices, Err))
	{
		Result.ErrorMessage = Err;
		return Result;
	}

	void* ValuePtr = FinalProp->ContainerPtrToValuePtr<void>(ContainerPtr);

	// Capture before-value for reporting + idempotence.
	FString BeforeText;
	FinalProp->ExportTextItem_Direct(BeforeText, ValuePtr, nullptr, nullptr, PPF_None);
	Result.BeforeText = BeforeText;

	if (BeforeText == ImportTextValue)
	{
		Result.AfterText = BeforeText;
		Result.bSuccess = true;
		Result.bSkipped = true;
		return Result;
	}

	const TCHAR* ImportCursor = *ImportTextValue;
	if (FinalProp->ImportText_Direct(ImportCursor, ValuePtr, InnermostOwner, PPF_None) == nullptr)
	{
		Result.ErrorMessage = FString::Printf(TEXT("ImportText_Direct failed for value '%s' (property type '%s')"),
			*ImportTextValue, *FinalProp->GetClass()->GetName());
		return Result;
	}

	FString AfterText;
	FinalProp->ExportTextItem_Direct(AfterText, ValuePtr, nullptr, nullptr, PPF_None);
	Result.AfterText = AfterText;
	Result.bSuccess = true;

	// Mark the package dirty so SavePackage later will write. Note: we do NOT
	// fire PostEditChangeChainProperty here — it is only load-bearing for
	// Instanced-flagged FObjectProperty writes (handled in SetObjectPropertyValue),
	// and firing it on intermediate state (e.g. a half-initialized node wrapper)
	// trips StateTreePropertyHelpers.cpp:125 with a partially-constructed chain.
	if (UObject* OwnerObject = Cast<UObject>(Root))
	{
		if (UPackage* Pkg = OwnerObject->GetPackage())
		{
			Pkg->SetDirtyFlag(true);
		}
	}

	return Result;
}

UObject* UBpxReflectionOps::FindSubobject(UObject* Root, FName SubobjectName)
{
	if (!Root || SubobjectName.IsNone())
	{
		return nullptr;
	}

	// First: direct outer-chain check (cheapest).
	for (UObject* Cur = Root->GetOuter(); Cur; Cur = Cur->GetOuter())
	{
		if (Cur->GetFName() == SubobjectName)
		{
			return Cur;
		}
	}

	// Then: walk subobjects of Root's package.
	UPackage* Pkg = Root->GetPackage();
	if (!Pkg)
	{
		return nullptr;
	}

	TArray<UObject*> Inner;
	GetObjectsWithOuter(Pkg, Inner, /*bIncludeNestedObjects=*/true);
	for (UObject* Obj : Inner)
	{
		if (Obj && Obj->GetFName() == SubobjectName)
		{
			return Obj;
		}
	}

	// Last resort: match by partial name (e.g., "StateTreeEditorData_0" matching
	// an Obj whose name starts with "StateTreeEditorData").
	const FString Wanted = SubobjectName.ToString();
	for (UObject* Obj : Inner)
	{
		if (Obj && Obj->GetName().StartsWith(Wanted))
		{
			return Obj;
		}
	}

	return nullptr;
}

int32 UBpxReflectionOps::GetArrayLength(UObject* Root, const TArray<FString>& Path)
{
	void* ContainerPtr = nullptr;
	FProperty* FinalProp = nullptr;
	UObject* InnermostOwner = nullptr;
	TArray<FProperty*> OwnerChain;
	TMap<FString, int32> ArrayIndices;
	FString Err;
	if (!BpxReflection::ResolvePath(Root, Path, ContainerPtr, FinalProp, InnermostOwner, OwnerChain, ArrayIndices, Err))
	{
		UE_LOG(LogBpxReflection, Warning, TEXT("GetArrayLength path resolve failed: %s"), *Err);
		return -1;
	}
	FArrayProperty* ArrProp = CastField<FArrayProperty>(FinalProp);
	if (!ArrProp)
	{
		UE_LOG(LogBpxReflection, Warning, TEXT("GetArrayLength: leaf property is not an array (got %s)"),
			*FinalProp->GetClass()->GetName());
		return -1;
	}
	void* ValuePtr = ArrProp->ContainerPtrToValuePtr<void>(ContainerPtr);
	FScriptArrayHelper ArrayHelper(ArrProp, ValuePtr);
	return ArrayHelper.Num();
}

int32 UBpxReflectionOps::ArrayAppendNewElement(UObject* Root, const TArray<FString>& Path)
{
	void* ContainerPtr = nullptr;
	FProperty* FinalProp = nullptr;
	UObject* InnermostOwner = nullptr;
	TArray<FProperty*> OwnerChain;
	TMap<FString, int32> ArrayIndices;
	FString Err;
	if (!BpxReflection::ResolvePath(Root, Path, ContainerPtr, FinalProp, InnermostOwner, OwnerChain, ArrayIndices, Err))
	{
		UE_LOG(LogBpxReflection, Warning, TEXT("ArrayAppendNewElement path resolve failed: %s"), *Err);
		return -1;
	}
	FArrayProperty* ArrProp = CastField<FArrayProperty>(FinalProp);
	if (!ArrProp)
	{
		UE_LOG(LogBpxReflection, Warning, TEXT("ArrayAppendNewElement: leaf is not an array (got %s)"),
			*FinalProp->GetClass()->GetName());
		return -1;
	}
	void* ArrayPtr = ArrProp->ContainerPtrToValuePtr<void>(ContainerPtr);
	FScriptArrayHelper ArrayHelper(ArrProp, ArrayPtr);
	const int32 NewIndex = ArrayHelper.AddValue();
	// AddValue default-constructs a single element; FArrayProperty::Inner
	// initializes the memory to zero + calls any struct ctor. No PostEditChange
	// fire — intermediate state.
	if (UObject* OwnerObj = Cast<UObject>(Root))
	{
		if (UPackage* Pkg = OwnerObj->GetPackage())
		{
			Pkg->SetDirtyFlag(true);
		}
	}
	return NewIndex;
}

FBpxReflectionResult UBpxReflectionOps::ArrayRemoveAt(UObject* Root, const TArray<FString>& Path, int32 Index)
{
	FBpxReflectionResult Result;

	void* ContainerPtr = nullptr;
	FProperty* FinalProp = nullptr;
	UObject* InnermostOwner = nullptr;
	TArray<FProperty*> OwnerChain;
	TMap<FString, int32> ArrayIndices;
	FString Err;
	if (!BpxReflection::ResolvePath(Root, Path, ContainerPtr, FinalProp, InnermostOwner, OwnerChain, ArrayIndices, Err))
	{
		Result.ErrorMessage = Err;
		return Result;
	}
	FArrayProperty* ArrProp = CastField<FArrayProperty>(FinalProp);
	if (!ArrProp)
	{
		Result.ErrorMessage = FString::Printf(TEXT("leaf is not an array (got %s)"),
			*FinalProp->GetClass()->GetName());
		return Result;
	}
	void* ArrayPtr = ArrProp->ContainerPtrToValuePtr<void>(ContainerPtr);
	FScriptArrayHelper ArrayHelper(ArrProp, ArrayPtr);
	const int32 Before = ArrayHelper.Num();
	if (!ArrayHelper.IsValidIndex(Index))
	{
		Result.ErrorMessage = FString::Printf(TEXT("index %d out of range for array of size %d"),
			Index, Before);
		return Result;
	}
	ArrayHelper.RemoveValues(Index, 1);
	const int32 After = ArrayHelper.Num();
	Result.BeforeText = FString::FromInt(Before);
	Result.AfterText = FString::FromInt(After);
	Result.bSuccess = true;
	if (UObject* OwnerObj = Cast<UObject>(Root))
	{
		if (UPackage* Pkg = OwnerObj->GetPackage())
		{
			Pkg->SetDirtyFlag(true);
		}
	}
	return Result;
}

FBpxReflectionResult UBpxReflectionOps::SetInstancedStructType(UObject* Root, const TArray<FString>& Path, UScriptStruct* NewType)
{
	FBpxReflectionResult Result;

	if (!NewType)
	{
		Result.ErrorMessage = TEXT("NewType is null");
		return Result;
	}

	void* ContainerPtr = nullptr;
	FProperty* FinalProp = nullptr;
	UObject* InnermostOwner = nullptr;
	TArray<FProperty*> OwnerChain;
	TMap<FString, int32> ArrayIndices;
	FString Err;
	if (!BpxReflection::ResolvePath(Root, Path, ContainerPtr, FinalProp, InnermostOwner, OwnerChain, ArrayIndices, Err))
	{
		Result.ErrorMessage = Err;
		return Result;
	}
	FStructProperty* StructProp = CastField<FStructProperty>(FinalProp);
	if (!StructProp)
	{
		Result.ErrorMessage = FString::Printf(TEXT("leaf is not a struct (got %s)"),
			*FinalProp->GetClass()->GetName());
		return Result;
	}
	// Is it actually an FInstancedStruct?
	if (StructProp->Struct != FInstancedStruct::StaticStruct())
	{
		Result.ErrorMessage = FString::Printf(TEXT("leaf struct is '%s', not FInstancedStruct"),
			*StructProp->Struct->GetName());
		return Result;
	}
	void* ValuePtr = StructProp->ContainerPtrToValuePtr<void>(ContainerPtr);
	FInstancedStruct* InstancedPtr = reinterpret_cast<FInstancedStruct*>(ValuePtr);

	const UScriptStruct* BeforeType = InstancedPtr->GetScriptStruct();
	Result.BeforeText = BeforeType ? BeforeType->GetPathName() : TEXT("<none>");

	InstancedPtr->InitializeAs(NewType);

	const UScriptStruct* AfterType = InstancedPtr->GetScriptStruct();
	Result.AfterText = AfterType ? AfterType->GetPathName() : TEXT("<none>");
	Result.bSuccess = true;

	// No PostEditChange fire — the wrapper struct has its class field set but
	// no InstanceObject pointer yet, so UE's state-node post-edit handlers
	// would see a half-constructed node.
	if (UObject* OwnerObj = Cast<UObject>(Root))
	{
		if (UPackage* Pkg = OwnerObj->GetPackage())
		{
			Pkg->SetDirtyFlag(true);
		}
	}
	return Result;
}

UObject* UBpxReflectionOps::NewSubobject(UObject* Outer, UClass* Class, FName BaseName)
{
	if (!Outer || !Class)
	{
		UE_LOG(LogBpxReflection, Error, TEXT("NewSubobject: Outer or Class is null"));
		return nullptr;
	}
	EObjectFlags Flags = RF_Public | RF_Transactional;
	UObject* Instance = NewObject<UObject>(Outer, Class, BaseName, Flags);
	if (!Instance)
	{
		UE_LOG(LogBpxReflection, Error, TEXT("NewSubobject: NewObject returned null for class '%s'"),
			*Class->GetPathName());
		return nullptr;
	}
	if (UPackage* Pkg = Outer->GetPackage())
	{
		Pkg->SetDirtyFlag(true);
	}
	return Instance;
}

FBpxReflectionResult UBpxReflectionOps::SetObjectPropertyValue(UObject* Root, const TArray<FString>& Path, UObject* NewValue)
{
	FBpxReflectionResult Result;

	void* ContainerPtr = nullptr;
	FProperty* FinalProp = nullptr;
	UObject* InnermostOwner = nullptr;
	TArray<FProperty*> OwnerChain;
	TMap<FString, int32> ArrayIndices;
	FString Err;
	if (!BpxReflection::ResolvePath(Root, Path, ContainerPtr, FinalProp, InnermostOwner, OwnerChain, ArrayIndices, Err))
	{
		Result.ErrorMessage = Err;
		return Result;
	}
	FObjectPropertyBase* ObjProp = CastField<FObjectPropertyBase>(FinalProp);
	if (!ObjProp)
	{
		Result.ErrorMessage = FString::Printf(TEXT("leaf is not an object property (got %s)"),
			*FinalProp->GetClass()->GetName());
		return Result;
	}
	void* ValuePtr = ObjProp->ContainerPtrToValuePtr<void>(ContainerPtr);

	UObject* Before = ObjProp->GetObjectPropertyValue(ValuePtr);
	Result.BeforeText = Before ? Before->GetPathName() : TEXT("None");

	if (NewValue && ObjProp->PropertyClass && !NewValue->IsA(ObjProp->PropertyClass))
	{
		Result.ErrorMessage = FString::Printf(TEXT("NewValue class '%s' is not a %s"),
			*NewValue->GetClass()->GetPathName(),
			*ObjProp->PropertyClass->GetPathName());
		return Result;
	}

	ObjProp->SetObjectPropertyValue(ValuePtr, NewValue);

	UObject* After = ObjProp->GetObjectPropertyValue(ValuePtr);
	Result.AfterText = After ? After->GetPathName() : TEXT("None");
	Result.bSuccess = true;

	// Fire PostEditChangeChainProperty on the innermost owner. Load-bearing
	// for Instanced-flagged FObjectProperty (e.g. FStateTreeEditorNode::InstanceObject):
	// without this notification UE's serializer does not re-sync the subobject's
	// outer relationship, so SavePackage returns true but the referenced subobject
	// is not persisted and reads back as null on the next load (M23.1.1).
	// This is the terminal op in a compound "add BP condition" flow — state is
	// consistent by this point, so StateTree's DispatchPostEditToNodes can walk
	// cleanly as long as ArrayIndices are populated.
	BpxReflection::NotifyPropertyChanged(InnermostOwner, OwnerChain, ArrayIndices, EPropertyChangeType::ValueSet);

	if (UObject* OwnerObj = Cast<UObject>(Root))
	{
		if (UPackage* Pkg = OwnerObj->GetPackage())
		{
			Pkg->SetDirtyFlag(true);
		}
	}
	return Result;
}

UObject* UBpxReflectionOps::GetObjectPropertyValue(UObject* Root, const TArray<FString>& Path)
{
	void* ContainerPtr = nullptr;
	FProperty* FinalProp = nullptr;
	UObject* InnermostOwner = nullptr;
	TArray<FProperty*> OwnerChain;
	TMap<FString, int32> ArrayIndices;
	FString Err;
	if (!BpxReflection::ResolvePath(Root, Path, ContainerPtr, FinalProp, InnermostOwner, OwnerChain, ArrayIndices, Err))
	{
		UE_LOG(LogBpxReflection, Warning, TEXT("GetObjectPropertyValue path resolve failed: %s"), *Err);
		return nullptr;
	}
	FObjectPropertyBase* ObjProp = CastField<FObjectPropertyBase>(FinalProp);
	if (!ObjProp)
	{
		UE_LOG(LogBpxReflection, Warning, TEXT("GetObjectPropertyValue: leaf is not an object property (got %s)"),
			*FinalProp->GetClass()->GetName());
		return nullptr;
	}
	void* ValuePtr = ObjProp->ContainerPtrToValuePtr<void>(ContainerPtr);
	return ObjProp->GetObjectPropertyValue(ValuePtr);
}

bool UBpxReflectionOps::CompileAndSavePackage(UObject* Target)
{
	if (!Target)
	{
		UE_LOG(LogBpxReflection, Error, TEXT("CompileAndSavePackage: Target is null"));
		return false;
	}

	// Resolve the Blueprint being edited. Target may be:
	//   - a UBlueprint directly
	//   - a component template / CDO / subobject whose outer-chain contains a UBlueprint
	//   - a StateTree editor data subobject owned by a UStateTree (no UBlueprint path)
	UBlueprint* Blueprint = Cast<UBlueprint>(Target);
	if (!Blueprint)
	{
		for (UObject* Cur = Target->GetOuter(); Cur; Cur = Cur->GetOuter())
		{
			Blueprint = Cast<UBlueprint>(Cur);
			if (Blueprint)
			{
				break;
			}
		}
	}

	if (Blueprint)
	{
		FKismetEditorUtilities::CompileBlueprint(Blueprint);
		if (Blueprint->Status == BS_Error)
		{
			UE_LOG(LogBpxReflection, Error, TEXT("CompileAndSavePackage: Blueprint '%s' compiled with errors — refusing to save"),
				*Blueprint->GetPathName());
			return false;
		}
	}

	UPackage* Pkg = Target->GetPackage();
	if (!Pkg)
	{
		UE_LOG(LogBpxReflection, Error, TEXT("CompileAndSavePackage: Target '%s' has no package"), *Target->GetPathName());
		return false;
	}

	Pkg->SetDirtyFlag(true);

	FString Filename;
	if (!FPackageName::TryConvertLongPackageNameToFilename(
			Pkg->GetName(),
			Filename,
			FPackageName::GetAssetPackageExtension()))
	{
		UE_LOG(LogBpxReflection, Error, TEXT("CompileAndSavePackage: can't resolve filename for package '%s'"), *Pkg->GetName());
		return false;
	}

	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
	SaveArgs.SaveFlags = SAVE_NoError;
	SaveArgs.Error = GWarn;

	const bool bSaved = UPackage::SavePackage(Pkg, Blueprint ? Cast<UObject>(Blueprint) : Target, *Filename, SaveArgs);
	if (!bSaved)
	{
		UE_LOG(LogBpxReflection, Error, TEXT("CompileAndSavePackage: SavePackage returned false for '%s'"), *Pkg->GetName());
		return false;
	}

	return true;
}

// --- M26.1 graph-authoring primitives (interface-override passthrough) ---

FBpxReflectionResult UBpxReflectionOps::OverrideInterfaceFunction(
	UBlueprint* Blueprint, UClass* InterfaceClass, FName FunctionName)
{
	FBpxReflectionResult Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (!InterfaceClass)
	{
		Result.ErrorMessage = TEXT("InterfaceClass is null");
		return Result;
	}
	if (FunctionName.IsNone())
	{
		Result.ErrorMessage = TEXT("FunctionName is empty");
		return Result;
	}

	// Verify the interface is listed on Blueprint->ImplementedInterfaces.
	// Op is scoped to interface OVERRIDE — adding an interface to a BP is
	// out of scope (defer to a future op if it's ever needed).
	bool bFoundInterface = false;
	for (const FBPInterfaceDescription& IfaceDesc : Blueprint->ImplementedInterfaces)
	{
		if (IfaceDesc.Interface == InterfaceClass)
		{
			bFoundInterface = true;
			break;
		}
	}
	if (!bFoundInterface)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Blueprint '%s' does not implement interface '%s' — add the interface in the BP editor first"),
			*Blueprint->GetPathName(), *InterfaceClass->GetPathName());
		return Result;
	}

	// Verify the interface actually has a function with this name.
	UFunction* InterfaceFn = InterfaceClass->FindFunctionByName(FunctionName);
	if (!InterfaceFn)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Interface '%s' has no function named '%s'"),
			*InterfaceClass->GetPathName(), *FunctionName.ToString());
		return Result;
	}

	// Idempotent: if an override graph with this name already exists, skip.
	if (BpxReflection::FindFunctionGraphByName(Blueprint, FunctionName))
	{
		Result.bSuccess = true;
		Result.bSkipped = true;
		Result.BeforeText = FString::Printf(TEXT("override-exists:%s"), *FunctionName.ToString());
		Result.AfterText = Result.BeforeText;
		return Result;
	}

	// Create the new graph and wire it as an interface-function override.
	UEdGraph* NewGraph = FBlueprintEditorUtils::CreateNewGraph(
		Blueprint, FunctionName, UEdGraph::StaticClass(),
		UEdGraphSchema_K2::StaticClass());
	if (!NewGraph)
	{
		Result.ErrorMessage = TEXT("CreateNewGraph returned null");
		return Result;
	}

	FBlueprintEditorUtils::AddFunctionGraph<UClass>(
		Blueprint, NewGraph, /*bIsUserCreated*/ false, InterfaceClass);

	// Interface-function overrides only get a UK2Node_FunctionEntry; UE
	// does NOT auto-add a UK2Node_FunctionResult even when the interface
	// function has output parameters. Entry's pins end up as EGPD_Output,
	// which the K2 connection schema rejects as "both OUTPUT" when a Get-
	// node tries to feed them. We force-create a Result node so callers
	// can wire Get.<var>.OUT → Return.<pin>.IN cleanly, matching the
	// regular non-interface function convention.
	UK2Node_FunctionEntry* EntryNode = nullptr;
	bool bHasReturnNode = false;
	for (UEdGraphNode* Node : NewGraph->Nodes)
	{
		if (!EntryNode)
		{
			EntryNode = Cast<UK2Node_FunctionEntry>(Node);
		}
		if (Node && Node->IsA<UK2Node_FunctionResult>())
		{
			bHasReturnNode = true;
		}
	}
	if (!EntryNode)
	{
		Result.ErrorMessage = TEXT("AddFunctionGraph produced no UK2Node_FunctionEntry");
		return Result;
	}
	if (!bHasReturnNode)
	{
		bool bHasAnyOutParam = false;
		for (TFieldIterator<FProperty> It(InterfaceFn); It; ++It)
		{
			if (It->HasAnyPropertyFlags(CPF_OutParm) || It->HasAnyPropertyFlags(CPF_ReturnParm))
			{
				bHasAnyOutParam = true;
				break;
			}
		}
		if (bHasAnyOutParam)
		{
			// Deterministic object name — see the AddSelfMemberGetNode
			// comment for why MakeUniqueObjectName's monotonic counter
			// breaks byte-determinism across create/destroy cycles.
			const FName ReturnNodeName(*FString::Printf(
				TEXT("BpxFuncResult_%s"), *FunctionName.ToString()));
			UK2Node_FunctionResult* NewReturn = NewObject<UK2Node_FunctionResult>(NewGraph, ReturnNodeName);
			NewReturn->NodePosX = EntryNode->NodePosX + 400;
			NewReturn->NodePosY = EntryNode->NodePosY;
			NewGraph->AddNode(NewReturn, /*bUserAction*/ false, /*bSelectNewNode*/ false);
			NewReturn->CreateNewGuid();
			NewReturn->PostPlacedNewNode();
			// AllocateDefaultPins walks the graph's Outer chain to find
			// the owning UFunction, then builds Return pins from its
			// CPF_OutParm / CPF_ReturnParm properties.
			NewReturn->AllocateDefaultPins();
		}
	}

	// Overwrite UE's random NodeGuids AND random PinIds with md5-seeded
	// values so the .uasset is byte-deterministic across re-generation.
	// M26.1 seeded NodeGuids; M26.1.2 extended the determinism to PinIds
	// after the force_rebind soak surfaced wipe+rebind md5 drift driven
	// by pin-GUID randomness on freshly-authored nodes.
	const FString EntryPrefix = Blueprint->GetPathName() + TEXT(":") + FunctionName.ToString() + TEXT(":entry");
	const FString ReturnPrefix = Blueprint->GetPathName() + TEXT(":") + FunctionName.ToString() + TEXT(":return");
	const FGuid EntrySeed = BpxReflection::SeedGuidFromJoined(EntryPrefix);
	const FGuid ReturnSeed = BpxReflection::SeedGuidFromJoined(ReturnPrefix);
	for (UEdGraphNode* Node : NewGraph->Nodes)
	{
		if (!Node)
		{
			continue;
		}
		if (Node->IsA<UK2Node_FunctionEntry>())
		{
			Node->NodeGuid = EntrySeed;
			BpxReflection::SeedPinGuidsForNode(Node, EntryPrefix);
		}
		else if (Node->IsA<UK2Node_FunctionResult>())
		{
			Node->NodeGuid = ReturnSeed;
			BpxReflection::SeedPinGuidsForNode(Node, ReturnPrefix);
		}
	}

	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);

	Result.bSuccess = true;
	Result.BeforeText = TEXT("no-override");
	Result.AfterText = FString::Printf(TEXT("override-added:%s"), *FunctionName.ToString());
	return Result;
}

FBpxGraphEndpoints UBpxReflectionOps::FindGraphEndpoints(
	UBlueprint* Blueprint, FName FunctionName)
{
	FBpxGraphEndpoints Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (FunctionName.IsNone())
	{
		Result.ErrorMessage = TEXT("FunctionName is empty");
		return Result;
	}

	UEdGraph* Graph = BpxReflection::FindFunctionGraphByName(Blueprint, FunctionName);
	if (!Graph)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("No function graph named '%s' on '%s'"),
			*FunctionName.ToString(), *Blueprint->GetPathName());
		return Result;
	}

	for (UEdGraphNode* Node : Graph->Nodes)
	{
		if (!Node)
		{
			continue;
		}
		if (Node->IsA<UK2Node_FunctionEntry>())
		{
			Result.EntryGuid = Node->NodeGuid;
		}
		else if (Node->IsA<UK2Node_FunctionResult>())
		{
			Result.ReturnGuid = Node->NodeGuid;
		}
	}

	if (!Result.EntryGuid.IsValid())
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("No UK2Node_FunctionEntry in graph '%s'"), *FunctionName.ToString());
		return Result;
	}
	// ReturnGuid may legitimately be zero for void / no-return signatures.

	Result.bSuccess = true;
	return Result;
}

FBpxNodeResult UBpxReflectionOps::AddSelfMemberGetNode(
	UBlueprint* Blueprint, FName FunctionName, FName MemberName, FVector2D Position)
{
	FBpxNodeResult Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (FunctionName.IsNone())
	{
		Result.ErrorMessage = TEXT("FunctionName is empty");
		return Result;
	}
	if (MemberName.IsNone())
	{
		Result.ErrorMessage = TEXT("MemberName is empty");
		return Result;
	}
	if (!Blueprint->GeneratedClass)
	{
		Result.ErrorMessage = TEXT("Blueprint has no GeneratedClass (unsaved / corrupt BP?)");
		return Result;
	}

	UEdGraph* Graph = BpxReflection::FindFunctionGraphByName(Blueprint, FunctionName);
	if (!Graph)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("No function graph named '%s' on '%s' — call OverrideInterfaceFunction first"),
			*FunctionName.ToString(), *Blueprint->GetPathName());
		return Result;
	}

	const FGuid SeededGuid = BpxReflection::SeedGuidFromJoined(
		Blueprint->GetPathName() + TEXT(":") + FunctionName.ToString()
		+ TEXT(":get:") + MemberName.ToString());

	// Idempotent on the seeded GUID.
	for (UEdGraphNode* ExistingNode : Graph->Nodes)
	{
		if (ExistingNode && ExistingNode->NodeGuid == SeededGuid)
		{
			Result.bSuccess = true;
			Result.bSkipped = true;
			Result.NodeGuid = SeededGuid;
			return Result;
		}
	}

	// Deterministic object name. Default NewObject<>(Outer) with no FName
	// delegates to MakeUniqueObjectName which uses a per-Outer monotonic
	// counter (K2Node_VariableGet_0, _1, _2, ...). The counter does NOT
	// reset when prior objects are GC'd, so force_rebind wipe-then-create
	// produces nodes with higher suffix indices than a fresh create — and
	// those suffixes get serialized into the package FNameMap, drifting
	// the .uasset bytes. Using a deterministic, input-seeded name is what
	// keeps round N and round N+1 byte-identical. M26.1.2 soak surfaced
	// this as the third-order determinism source after pin-GUID seeding
	// and GC-after-wipe.
	const FName NewNodeName(*FString::Printf(
		TEXT("BpxVarGet_%s"), *MemberName.ToString()));
	UK2Node_VariableGet* NewNode = NewObject<UK2Node_VariableGet>(Graph, NewNodeName);
	NewNode->VariableReference.SetSelfMember(MemberName);
	Graph->AddNode(NewNode, /*bUserAction*/ false, /*bSelectNewNode*/ false);
	NewNode->NodeGuid = SeededGuid;
	NewNode->NodePosX = static_cast<int32>(Position.X);
	NewNode->NodePosY = static_cast<int32>(Position.Y);
	NewNode->PostPlacedNewNode();
	NewNode->AllocateDefaultPins();

	const FString JoinedPrefix =
		Blueprint->GetPathName() + TEXT(":") + FunctionName.ToString()
		+ TEXT(":get:") + MemberName.ToString();
	BpxReflection::SeedPinGuidsForNode(NewNode, JoinedPrefix);

	Result.bSuccess = true;
	Result.NodeGuid = SeededGuid;
	return Result;
}

FBpxReflectionResult UBpxReflectionOps::ConnectPinsByName(
	UBlueprint* Blueprint, FName FunctionName,
	FGuid FromNodeGuid, FName FromPinName,
	FGuid ToNodeGuid,   FName ToPinName)
{
	FBpxReflectionResult Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}

	UEdGraph* Graph = BpxReflection::FindFunctionGraphByName(Blueprint, FunctionName);
	if (!Graph)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("No function graph named '%s'"), *FunctionName.ToString());
		return Result;
	}

	UEdGraphNode* FromNode = nullptr;
	UEdGraphNode* ToNode = nullptr;
	for (UEdGraphNode* Node : Graph->Nodes)
	{
		if (!Node)
		{
			continue;
		}
		if (Node->NodeGuid == FromNodeGuid)
		{
			FromNode = Node;
		}
		if (Node->NodeGuid == ToNodeGuid)
		{
			ToNode = Node;
		}
	}
	if (!FromNode)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("From-node %s not found in graph '%s'"),
			*FromNodeGuid.ToString(), *FunctionName.ToString());
		return Result;
	}
	if (!ToNode)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("To-node %s not found in graph '%s'"),
			*ToNodeGuid.ToString(), *FunctionName.ToString());
		return Result;
	}

	UEdGraphPin* FromPin = FromNode->FindPin(FromPinName);
	UEdGraphPin* ToPin = ToNode->FindPin(ToPinName);
	if (!FromPin)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("From-pin '%s' not found on node %s"),
			*FromPinName.ToString(), *FromNode->GetName());
		return Result;
	}
	if (!ToPin)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("To-pin '%s' not found on node %s"),
			*ToPinName.ToString(), *ToNode->GetName());
		return Result;
	}

	// Idempotent: already-linked pins.
	if (FromPin->LinkedTo.Contains(ToPin))
	{
		Result.bSuccess = true;
		Result.bSkipped = true;
		Result.BeforeText = TEXT("already-linked");
		Result.AfterText = TEXT("already-linked");
		return Result;
	}

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	if (!K2Schema)
	{
		Result.ErrorMessage = TEXT("UEdGraphSchema_K2 CDO unavailable");
		return Result;
	}

	// Probe CanCreateConnection first so we can surface UE's specific
	// refusal reason (type mismatch, pin-direction conflict, disallowed
	// by schema rules, etc.) instead of an opaque "TryCreateConnection
	// returned false".
	const FPinConnectionResponse ConnResponse = K2Schema->CanCreateConnection(FromPin, ToPin);
	const bool bCanConnect = (ConnResponse.Response != CONNECT_RESPONSE_DISALLOW);

	const bool bConnected = bCanConnect && K2Schema->TryCreateConnection(FromPin, ToPin);
	if (!bConnected)
	{
		const TCHAR* FromDirStr = (FromPin->Direction == EGPD_Output) ? TEXT("OUT") : TEXT("IN");
		const TCHAR* ToDirStr   = (ToPin->Direction == EGPD_Output)   ? TEXT("OUT") : TEXT("IN");
		Result.ErrorMessage = FString::Printf(
			TEXT("connection refused: %s.%s[%s:%s] -> %s.%s[%s:%s] :: %s"),
			*FromNode->GetName(), *FromPinName.ToString(),
			FromDirStr, *FromPin->PinType.PinCategory.ToString(),
			*ToNode->GetName(),   *ToPinName.ToString(),
			ToDirStr,   *ToPin->PinType.PinCategory.ToString(),
			*ConnResponse.Message.ToString());
		return Result;
	}

	// NOTE: the BP is NOT marked structurally modified here. Doing so
	// would break M26.1.2's byte-identity invariant on
	// `implement_interface_function` — each wire the op authors (Faction,
	// bIsAlive) routes through this function, and each extra
	// Modify()/BroadcastChanged() pair mutates the BP's change counter
	// and triggers listeners that in turn create UObjects via
	// MakeUniqueObjectName's monotonic-counter path. M28.pre.3's force_rebind
	// soak caught the drift. The mark-modified call has been hoisted out
	// to the M28.3 Python-facing entry point `ConnectGraphPinsByGuidString`
	// — standalone `connect_graph_pins` wires still flush correctly, and
	// function-graph authoring (M26.1) is unaffected because
	// `OverrideInterfaceFunction` already marked the BP earlier in the
	// plan.

	Result.bSuccess = true;
	Result.BeforeText = TEXT("unlinked");
	Result.AfterText = TEXT("linked");
	return Result;
}

FBpxReflectionResult UBpxReflectionOps::SetNodePinLiteralDefault(
	UBlueprint* Blueprint, FName FunctionName,
	FGuid NodeGuid, FName PinName, const FString& LiteralText)
{
	FBpxReflectionResult Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}

	UEdGraph* Graph = BpxReflection::FindFunctionGraphByName(Blueprint, FunctionName);
	if (!Graph)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("No function graph named '%s'"), *FunctionName.ToString());
		return Result;
	}

	UEdGraphNode* Node = nullptr;
	for (UEdGraphNode* N : Graph->Nodes)
	{
		if (N && N->NodeGuid == NodeGuid)
		{
			Node = N;
			break;
		}
	}
	if (!Node)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Node %s not found in graph '%s'"),
			*NodeGuid.ToString(), *FunctionName.ToString());
		return Result;
	}

	UEdGraphPin* Pin = Node->FindPin(PinName);
	if (!Pin)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Pin '%s' not found on node %s"),
			*PinName.ToString(), *Node->GetName());
		return Result;
	}

	Result.BeforeText = Pin->DefaultValue;

	if (Pin->DefaultValue == LiteralText)
	{
		Result.bSuccess = true;
		Result.bSkipped = true;
		Result.AfterText = LiteralText;
		return Result;
	}

	if (const UEdGraphSchema* Schema = Pin->GetSchema())
	{
		Schema->TrySetDefaultValue(*Pin, LiteralText);
	}
	else
	{
		Pin->DefaultValue = LiteralText;
	}

	Result.bSuccess = true;
	Result.AfterText = Pin->DefaultValue;
	return Result;
}

FBpxReflectionResult UBpxReflectionOps::WipeFunctionGraphBody(
	UBlueprint* Blueprint, FName FunctionName)
{
	FBpxReflectionResult Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (FunctionName.IsNone())
	{
		Result.ErrorMessage = TEXT("FunctionName is empty");
		return Result;
	}

	UEdGraph* Graph = BpxReflection::FindFunctionGraphByName(Blueprint, FunctionName);
	if (!Graph)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("No function graph named '%s' on '%s'"),
			*FunctionName.ToString(), *Blueprint->GetPathName());
		return Result;
	}

	// Reseed Entry/Return NodeGuid + pin GUIDs deterministically BEFORE any
	// short-circuit. On the force_rebind path, `OverrideInterfaceFunction`
	// early-returns (override already exists) so it never ran its seeding
	// loop — meaning Entry carries whatever random FGuid `duplicate_asset`
	// handed it for THIS session. Without reseeding here, Entry's runtime
	// NodeGuid + pin GUIDs vary across sessions even though inputs are
	// identical (M28.pre.3 cross-session soak surfaced this after the
	// within-session fix landed). Must run on EVERY force_rebind call,
	// including ones where ToRemove ends up empty (round 1 of a soak where
	// the original stub had no authored body), which is why the reseed
	// pass comes before the "nothing to wipe" early-return below.
	const FString EntryPrefix = Blueprint->GetPathName() + TEXT(":") + FunctionName.ToString() + TEXT(":entry");
	const FString ReturnPrefix = Blueprint->GetPathName() + TEXT(":") + FunctionName.ToString() + TEXT(":return");
	const FGuid EntrySeed = BpxReflection::SeedGuidFromJoined(EntryPrefix);
	const FGuid ReturnSeed = BpxReflection::SeedGuidFromJoined(ReturnPrefix);
	for (UEdGraphNode* Node : Graph->Nodes)
	{
		if (!Node)
		{
			continue;
		}
		if (Node->IsA<UK2Node_FunctionEntry>())
		{
			Node->NodeGuid = EntrySeed;
			BpxReflection::SeedPinGuidsForNode(Node, EntryPrefix);
		}
		else if (Node->IsA<UK2Node_FunctionResult>())
		{
			Node->NodeGuid = ReturnSeed;
			BpxReflection::SeedPinGuidsForNode(Node, ReturnPrefix);
		}
	}

	// Collect non-Entry / non-Return nodes up front; mutating Graph->Nodes
	// during iteration with RemoveNode is safe in UE but clearer to stage
	// the victims first.
	TArray<UEdGraphNode*> ToRemove;
	for (UEdGraphNode* Node : Graph->Nodes)
	{
		if (!Node)
		{
			continue;
		}
		if (Node->IsA<UK2Node_FunctionEntry>() || Node->IsA<UK2Node_FunctionResult>())
		{
			continue;
		}
		ToRemove.Add(Node);
	}

	if (ToRemove.Num() == 0)
	{
		// Nothing to wipe, but we DID reseed above — report success (not
		// skipped) so the caller treats the reseed as the state change.
		Result.bSuccess = true;
		Result.BeforeText = TEXT("0");
		Result.AfterText = TEXT("0");
		return Result;
	}

	for (UEdGraphNode* Node : ToRemove)
	{
		// UEdGraph::RemoveNode handles breaking all pin links + detaching the
		// node from the graph; we don't need to call BreakAllPinLinks first.
		Graph->RemoveNode(Node, /*bBreakAllLinks*/ true);
	}

	// Entry node's Then pin may still point at a now-removed node; defensively
	// clear any dangling links on Entry / Return pins so the compiler doesn't
	// trip over stale LinkedTo entries. RemoveNode(bBreakAllLinks=true) already
	// handles the victim side; this handles the Entry / Return survivors.
	for (UEdGraphNode* Node : Graph->Nodes)
	{
		if (!Node)
		{
			continue;
		}
		if (!Node->IsA<UK2Node_FunctionEntry>() && !Node->IsA<UK2Node_FunctionResult>())
		{
			continue;
		}
		for (UEdGraphPin* Pin : Node->Pins)
		{
			if (Pin && Pin->LinkedTo.Num() > 0)
			{
				Pin->BreakAllPinLinks();
			}
		}
	}

	// Force GC so the wiped nodes stop occupying package-export linker
	// indices. Without this, subsequent node creations (the rebind pass)
	// get indices monotonically past the wiped ones, so wipe+rebind vs
	// a fresh-bind produce different linker-index byte patterns at save
	// time — same shape, different bytes. M26.1.2 soak surfaced this
	// as the second-order drift after pin-GUID seeding.
	CollectGarbage(RF_NoFlags, /*bFullPurge*/ true);

	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);

	Result.bSuccess = true;
	Result.BeforeText = FString::FromInt(ToRemove.Num());
	Result.AfterText = FString::FromInt(ToRemove.Num());
	return Result;
}

FBpxReflectionResult UBpxReflectionOps::ConnectGraphPinsByGuidString(
	UBlueprint* Blueprint, FName GraphName,
	const FString& FromNodeGuidStr, FName FromPinName,
	const FString& ToNodeGuidStr,   FName ToPinName)
{
	FBpxReflectionResult Result;

	if (FromNodeGuidStr.IsEmpty())
	{
		Result.ErrorMessage = TEXT("FromNodeGuidStr is empty");
		return Result;
	}
	if (ToNodeGuidStr.IsEmpty())
	{
		Result.ErrorMessage = TEXT("ToNodeGuidStr is empty");
		return Result;
	}

	FGuid FromGuid;
	if (!FGuid::Parse(FromNodeGuidStr, FromGuid))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("FGuid::Parse failed on FromNodeGuidStr='%s' — expected 32-char hex or {8-4-4-4-12}"),
			*FromNodeGuidStr);
		return Result;
	}
	FGuid ToGuid;
	if (!FGuid::Parse(ToNodeGuidStr, ToGuid))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("FGuid::Parse failed on ToNodeGuidStr='%s' — expected 32-char hex or {8-4-4-4-12}"),
			*ToNodeGuidStr);
		return Result;
	}

	Result = ConnectPinsByName(Blueprint, GraphName, FromGuid, FromPinName, ToGuid, ToPinName);

	// Mark structurally modified only from the M28.3 Python-facing entry
	// point, not from `ConnectPinsByName` itself. Rationale: M26.1's
	// `implement_interface_function` drives `ConnectPinsByName` directly
	// twice per call (Faction + bIsAlive wires), and each
	// MarkBlueprintAsStructurallyModified fires listeners whose UObject
	// creation goes through MakeUniqueObjectName's monotonic counter —
	// byte-drift per session. The standalone `connect_graph_pins` flow
	// (e.g. BP_Task_Peek Branch.else → FinishTask) still needs the flush
	// for a subsequent `compile_and_save_package` to pick up the wire,
	// so we do it here at the boundary Python calls into.
	if (Result.bSuccess && Blueprint)
	{
		FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);
	}
	return Result;
}

// --- M28.2.1 structural BP edits — variable add ---

FBpxReflectionResult UBpxReflectionOps::AddMemberVariableDeterministic(
	UBlueprint* Blueprint, FName VarName,
	const FEdGraphPinType& VarType, const FString& DefaultValue)
{
	FBpxReflectionResult Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (VarName.IsNone())
	{
		Result.ErrorMessage = TEXT("VarName is empty");
		return Result;
	}

	// Idempotence — match by name on Blueprint->NewVariables (the BP-declared
	// member-variable list, separate from inherited / SCS-component vars).
	// `FBlueprintEditorUtils::AddMemberVariable` rejects duplicates against
	// the broader `GetClassVariableList` set (inherited included), but we
	// short-circuit on NewVariables specifically so the skip semantics are
	// crisp: same call twice on the same plan returns success+skipped, not a
	// generic "AddMemberVariable returned false" error.
	for (const FBPVariableDescription& Var : Blueprint->NewVariables)
	{
		if (Var.VarName == VarName)
		{
			Result.bSuccess = true;
			Result.bSkipped = true;
			Result.BeforeText = FString::Printf(TEXT("var-exists:%s"), *VarName.ToString());
			Result.AfterText = Result.BeforeText;
			return Result;
		}
	}

	// Engine call. Returns false on inherited-name collision OR when VarName
	// is NAME_None (we already gated NAME_None above, so a false here means
	// inherited collision — surface it cleanly so the plan author knows to
	// rename rather than chasing a generic engine warning in the log).
	const bool bAdded = FBlueprintEditorUtils::AddMemberVariable(
		Blueprint, VarName, VarType, DefaultValue);
	if (!bAdded)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("FBlueprintEditorUtils::AddMemberVariable('%s') returned false — most likely a name collision with an inherited variable on '%s'"),
			*VarName.ToString(), *Blueprint->GetPathName());
		return Result;
	}

	// Find the just-added entry by name and overwrite VarGuid with a
	// deterministic md5-seeded value. Without this, every run produces a
	// different .uasset md5 (engine assigns FGuid::NewGuid() at line 4667
	// of BlueprintEditorUtils.cpp), tripping M28.pre.3 soak round-2 compare.
	FBPVariableDescription* NewEntry = nullptr;
	for (FBPVariableDescription& Var : Blueprint->NewVariables)
	{
		if (Var.VarName == VarName)
		{
			NewEntry = &Var;
			break;
		}
	}
	if (!NewEntry)
	{
		// Defensive — AddMemberVariable returned true but the var didn't land.
		Result.ErrorMessage = FString::Printf(
			TEXT("AddMemberVariable returned true but '%s' is not on Blueprint->NewVariables"),
			*VarName.ToString());
		return Result;
	}

	const FString SeedKey = Blueprint->GetPathName() + TEXT(":var:") + VarName.ToString();
	NewEntry->VarGuid = BpxReflection::SeedGuidFromJoined(SeedKey);

	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);

	Result.bSuccess = true;
	Result.BeforeText = TEXT("no-var");
	Result.AfterText = FString::Printf(TEXT("var-added:%s"), *VarName.ToString());
	return Result;
}

// --- M28.2.2 structural BP edits — function graph add ---

FBpxGraphEndpoints UBpxReflectionOps::AddFunctionGraphDeterministic(
	UBlueprint* Blueprint, FName FunctionName, bool bIsPure)
{
	FBpxGraphEndpoints Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (FunctionName.IsNone())
	{
		Result.ErrorMessage = TEXT("FunctionName is empty");
		return Result;
	}

	// Idempotent: if a graph with this name exists (on function graphs,
	// interface overrides, OR ubergraphs), return its Entry/Return GUIDs
	// without creating a second graph. Matches the AddMemberVariableDeterministic
	// skip semantics — plan replay is cheap and always safe.
	if (UEdGraph* Existing = BpxReflection::FindFunctionGraphByName(Blueprint, FunctionName))
	{
		for (UEdGraphNode* Node : Existing->Nodes)
		{
			if (!Node)
			{
				continue;
			}
			if (Node->IsA<UK2Node_FunctionEntry>())
			{
				Result.EntryGuid = Node->NodeGuid;
			}
			else if (Node->IsA<UK2Node_FunctionResult>())
			{
				Result.ReturnGuid = Node->NodeGuid;
			}
		}
		Result.bSuccess = true;
		Result.bSkipped = true;
		return Result;
	}

	// Name validation mirrors UBlueprintEditorLibrary::AddFunctionGraph —
	// reject reserved / duplicate names up-front rather than letting the
	// engine silently rename to "NewFunction".
	if (FKismetNameValidator(Blueprint).IsValid(FunctionName.ToString()) != EValidatorResult::Ok)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("FunctionName '%s' failed FKismetNameValidator on '%s' — reserved or collides with an existing member"),
			*FunctionName.ToString(), *Blueprint->GetPathName());
		return Result;
	}

	Blueprint->Modify();

	UEdGraph* NewGraph = FBlueprintEditorUtils::CreateNewGraph(
		Blueprint, FunctionName, UEdGraph::StaticClass(),
		UEdGraphSchema_K2::StaticClass());
	if (!NewGraph)
	{
		Result.ErrorMessage = TEXT("CreateNewGraph returned null");
		return Result;
	}

	// Blank non-interface function — pass nullptr signature so UE auto-
	// generates Entry + Return nodes matching a void/void signature. The
	// `bIsUserCreated=true` flag wires it onto Blueprint->FunctionGraphs
	// and registers it in the BP's category list.
	FBlueprintEditorUtils::AddFunctionGraph<UFunction>(
		Blueprint, NewGraph, /*bIsUserCreated*/ true, /*SignatureFromObject*/ nullptr);

	// Walk the auto-created nodes. AddFunctionGraph<UFunction, nullptr>
	// produces Entry + Return for the standard blank function shape.
	UK2Node_FunctionEntry* EntryNode = nullptr;
	UK2Node_FunctionResult* ReturnNode = nullptr;
	for (UEdGraphNode* Node : NewGraph->Nodes)
	{
		if (!EntryNode)
		{
			EntryNode = Cast<UK2Node_FunctionEntry>(Node);
		}
		if (!ReturnNode)
		{
			ReturnNode = Cast<UK2Node_FunctionResult>(Node);
		}
	}
	if (!EntryNode)
	{
		Result.ErrorMessage = TEXT("AddFunctionGraph produced no UK2Node_FunctionEntry");
		return Result;
	}

	// Seed GraphGuid — UEdGraph::PostInitProperties defaults to FGuid::NewGuid().
	const FString GraphPrefix = Blueprint->GetPathName() + TEXT(":func:") + FunctionName.ToString();
	NewGraph->GraphGuid = BpxReflection::SeedGuidFromJoined(GraphPrefix + TEXT(":graph"));

	// Seed Entry + Return NodeGuids + pin GUIDs — mirror the M26.1 /
	// M26.1.2 recipe exactly so the soak gate stays byte-stable round
	// to round. Without this, round N+1 drifts because UE reseeded via
	// CreateNewGuid() + CreatePin().
	const FString EntryPrefix = GraphPrefix + TEXT(":entry");
	EntryNode->NodeGuid = BpxReflection::SeedGuidFromJoined(EntryPrefix);
	BpxReflection::SeedPinGuidsForNode(EntryNode, EntryPrefix);

	if (ReturnNode)
	{
		const FString ReturnPrefix = GraphPrefix + TEXT(":return");
		ReturnNode->NodeGuid = BpxReflection::SeedGuidFromJoined(ReturnPrefix);
		BpxReflection::SeedPinGuidsForNode(ReturnNode, ReturnPrefix);
		Result.ReturnGuid = ReturnNode->NodeGuid;
	}

	// Pure flag lives on the Entry node's ExtraFlags (mirrored into the
	// generated UFunction on compile). See BlueprintDetailsCustomization
	// .cpp:6320 for the engine's own pure-toggle path. Applies only if
	// caller opted in — pair with a subsequent output-param add before
	// compiling, or the compile gate refuses (pure func with no return
	// is a no-op).
	if (bIsPure)
	{
		EntryNode->AddExtraFlags(FUNC_BlueprintPure);
	}

	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);

	Result.bSuccess = true;
	Result.EntryGuid = EntryNode->NodeGuid;
	return Result;
}

// --- M28.2.3 structural BP edits — SCS component add ---

FBpxReflectionResult UBpxReflectionOps::AddComponentToSCSDeterministic(
	UBlueprint* Blueprint, UClass* ComponentClass,
	FName ComponentName, FName ParentComponentName)
{
	FBpxReflectionResult Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (!ComponentClass)
	{
		Result.ErrorMessage = TEXT("ComponentClass is null");
		return Result;
	}
	if (!ComponentClass->IsChildOf(UActorComponent::StaticClass()))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("ComponentClass '%s' is not a UActorComponent subclass"),
			*ComponentClass->GetPathName());
		return Result;
	}
	if (ComponentName.IsNone())
	{
		Result.ErrorMessage = TEXT("ComponentName is empty");
		return Result;
	}

	USimpleConstructionScript* SCS = Blueprint->SimpleConstructionScript;
	if (!SCS)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Blueprint '%s' has no SimpleConstructionScript — is it a non-Actor BP?"),
			*Blueprint->GetPathName());
		return Result;
	}

	// Idempotence — if the name already lands on an SCS node, treat replay
	// as a no-op when the class matches, or a structured error when it
	// doesn't. Different-class same-name is never safe to silently rewrite.
	if (USCS_Node* Existing = SCS->FindSCSNode(ComponentName))
	{
		if (Existing->ComponentClass == ComponentClass)
		{
			Result.bSuccess = true;
			Result.bSkipped = true;
			Result.BeforeText = FString::Printf(TEXT("scs-node-exists:%s"), *ComponentName.ToString());
			Result.AfterText = Result.BeforeText;
			return Result;
		}
		Result.ErrorMessage = FString::Printf(
			TEXT("Component '%s' already exists on '%s' with class '%s' (requested '%s') — pick a different ComponentName"),
			*ComponentName.ToString(), *Blueprint->GetPathName(),
			Existing->ComponentClass ? *Existing->ComponentClass->GetPathName() : TEXT("<null>"),
			*ComponentClass->GetPathName());
		return Result;
	}

	// Parent lookup. NAME_None / empty → attach at SCS root via AddNode.
	// Parenting onto a native (inherited-CDO) component isn't supported
	// because the SCS doesn't track those as USCS_Node instances; the op's
	// scope is SCS-to-SCS parenting only.
	USCS_Node* ParentNode = nullptr;
	const bool bExplicitParent = !ParentComponentName.IsNone()
		&& !ParentComponentName.ToString().IsEmpty()
		&& ParentComponentName != FName(TEXT("None"));
	if (bExplicitParent)
	{
		ParentNode = SCS->FindSCSNode(ParentComponentName);
		if (!ParentNode)
		{
			Result.ErrorMessage = FString::Printf(
				TEXT("ParentComponentName '%s' not found as an SCS node on '%s' (native-inherited parents aren't supported — only SCS-declared components)"),
				*ParentComponentName.ToString(), *Blueprint->GetPathName());
			return Result;
		}
	}

	Blueprint->Modify();
	SCS->Modify();

	USCS_Node* NewNode = SCS->CreateNode(ComponentClass, ComponentName);
	if (!NewNode)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("SimpleConstructionScript::CreateNode returned null for class '%s'"),
			*ComponentClass->GetPathName());
		return Result;
	}

	// Post-rename detection — `GenerateNewComponentName` silently appends a
	// counter when the desired name collides with any existing SCS node or
	// inherited-class component name. Replay after a rename would fail
	// idempotence (FindSCSNode looks for the requested name, misses the
	// renamed one, then adds a second "same-named" node on the next round).
	// Reject up-front instead; the node is not yet on AllNodes so it'll GC.
	if (NewNode->GetVariableName() != ComponentName)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("ComponentName '%s' collides with a native-inherited component on '%s' (engine would rename to '%s'). Rename in your plan."),
			*ComponentName.ToString(), *Blueprint->GetPathName(),
			*NewNode->GetVariableName().ToString());
		return Result;
	}

	// Attach to root or parent. AddChildNode updates both ChildNodes and
	// AllNodes; AddNode updates both RootNodes and AllNodes.
	if (ParentNode)
	{
		ParentNode->AddChildNode(NewNode);
	}
	else
	{
		SCS->AddNode(NewNode);
	}

	// Seed VarGuid deterministically. Without this, every run produces a
	// different .uasset md5 (CreateNodeImpl at SimpleConstructionScript.cpp
	// :1375 assigns FGuid::NewGuid()), tripping the M28.pre.3 soak gate.
	const FString SeedKey = Blueprint->GetPathName() + TEXT(":scs:") + ComponentName.ToString();
	NewNode->VariableGuid = BpxReflection::SeedGuidFromJoined(SeedKey);

	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);

	Result.bSuccess = true;
	Result.BeforeText = TEXT("no-scs-node");
	Result.AfterText = FString::Printf(TEXT("scs-node-added:%s"), *ComponentName.ToString());
	return Result;
}

FBpxReflectionResult UBpxReflectionOps::AddInterfaceByPath(
	UBlueprint* Blueprint, UClass* InterfaceClass)
{
	FBpxReflectionResult Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (!InterfaceClass)
	{
		Result.ErrorMessage = TEXT("InterfaceClass is null");
		return Result;
	}
	if (!InterfaceClass->HasAnyClassFlags(CLASS_Interface))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("InterfaceClass '%s' is not an interface class (CLASS_Interface not set)"),
			*InterfaceClass->GetPathName());
		return Result;
	}

	// Idempotent: skip before touching the engine path so plan replay stays
	// quiet (engine's `ImplementNewInterface` would pop a UI notification on
	// already-implemented, which is noise in headless commandlet runs).
	for (const FBPInterfaceDescription& IfaceDesc : Blueprint->ImplementedInterfaces)
	{
		if (IfaceDesc.Interface == InterfaceClass)
		{
			Result.bSuccess = true;
			Result.bSkipped = true;
			Result.BeforeText = FString::Printf(
				TEXT("interface-already-implemented:%s"), *InterfaceClass->GetPathName());
			Result.AfterText = Result.BeforeText;
			return Result;
		}
	}

	Blueprint->Modify();

	const bool bAdded = FBlueprintEditorUtils::ImplementNewInterface(
		Blueprint, FTopLevelAssetPath(InterfaceClass));
	if (!bAdded)
	{
		// Engine returns false on (a) already-implemented (pre-screened above,
		// shouldn't reach here) or (b) anim-function-on-non-AnimBP conflict or
		// (c) a function-name conflict with an existing graph. Surface as a
		// structured error so the plan author sees the concrete reason in the
		// log, not just "add failed".
		Result.ErrorMessage = FString::Printf(
			TEXT("FBlueprintEditorUtils::ImplementNewInterface returned false for '%s' on '%s' — likely a function-name conflict or anim-function-on-non-AnimBP mismatch (check Saved/Logs)"),
			*InterfaceClass->GetPathName(), *Blueprint->GetPathName());
		return Result;
	}

	// Find the freshly-added description. `ImplementNewInterface` appends, so
	// scan by Interface pointer rather than assuming Last() — safer if a
	// future engine tweak reorders.
	FBPInterfaceDescription* AddedDesc = nullptr;
	for (FBPInterfaceDescription& IfaceDesc : Blueprint->ImplementedInterfaces)
	{
		if (IfaceDesc.Interface == InterfaceClass)
		{
			AddedDesc = &IfaceDesc;
			break;
		}
	}
	if (!AddedDesc)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("ImplementNewInterface reported success but '%s' is not on ImplementedInterfaces[] — engine state inconsistent"),
			*InterfaceClass->GetPathName());
		return Result;
	}

	// Seed GraphGuid + Entry/Return NodeGuids + pin IDs on every generated
	// override graph. Recipe identical to M28.2.2 AddFunctionGraphDeterministic,
	// keyed on (BP path, interface path, function name) so two BPs implementing
	// the same interface get distinct seeds and replay is stable.
	const FString InterfacePath = InterfaceClass->GetPathName();
	int32 GraphsSeeded = 0;
	for (UEdGraph* Graph : AddedDesc->Graphs)
	{
		if (!Graph)
		{
			continue;
		}
		const FString GraphName = Graph->GetName();
		const FString GraphPrefix = Blueprint->GetPathName()
			+ TEXT(":iface_graph:") + InterfacePath
			+ TEXT(":") + GraphName;
		Graph->GraphGuid = BpxReflection::SeedGuidFromJoined(GraphPrefix + TEXT(":graph"));

		const FString EntryPrefix = GraphPrefix + TEXT(":entry");
		const FString ReturnPrefix = GraphPrefix + TEXT(":return");
		const FGuid EntrySeed = BpxReflection::SeedGuidFromJoined(EntryPrefix);
		const FGuid ReturnSeed = BpxReflection::SeedGuidFromJoined(ReturnPrefix);
		for (UEdGraphNode* Node : Graph->Nodes)
		{
			if (!Node)
			{
				continue;
			}
			if (Node->IsA<UK2Node_FunctionEntry>())
			{
				Node->NodeGuid = EntrySeed;
				BpxReflection::SeedPinGuidsForNode(Node, EntryPrefix);
			}
			else if (Node->IsA<UK2Node_FunctionResult>())
			{
				Node->NodeGuid = ReturnSeed;
				BpxReflection::SeedPinGuidsForNode(Node, ReturnPrefix);
			}
		}
		++GraphsSeeded;
	}

	// ImplementNewInterface already calls MarkBlueprintAsStructurallyModified
	// on the success path (BlueprintEditorUtils.cpp:6507). Don't double-mark —
	// the M26.1.2 regression-chase established that re-entering structural-
	// modified listeners can invalidate freshly-seeded GUIDs.

	Result.bSuccess = true;
	Result.BeforeText = TEXT("no-interface-impl");
	Result.AfterText = FString::Printf(
		TEXT("interface-added:%s:graphs=%d"), *InterfacePath, GraphsSeeded);
	return Result;
}

// --- M28.3.1 node-level graph authoring — Branch + graph-level pin default ---

FBpxNodeResult UBpxReflectionOps::AddBranchNode(
	UBlueprint* Blueprint, FName GraphName, FVector2D Position)
{
	FBpxNodeResult Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (GraphName.IsNone())
	{
		Result.ErrorMessage = TEXT("GraphName is empty");
		return Result;
	}

	UEdGraph* Graph = BpxReflection::FindFunctionGraphByName(Blueprint, GraphName);
	if (!Graph)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("No graph named '%s' on '%s' (checked FunctionGraphs / ImplementedInterfaces / UbergraphPages)"),
			*GraphName.ToString(), *Blueprint->GetPathName());
		return Result;
	}

	// Seed key includes (x,y) so distinct Branches at different positions in the
	// same graph get distinct GUIDs. Moving a Branch post-apply will break
	// byte-identity — acceptable, plan authors set position explicitly.
	const int32 PosX = static_cast<int32>(Position.X);
	const int32 PosY = static_cast<int32>(Position.Y);
	const FString JoinedPrefix = Blueprint->GetPathName()
		+ TEXT(":graph:") + GraphName.ToString()
		+ TEXT(":branch:") + FString::FromInt(PosX)
		+ TEXT(",") + FString::FromInt(PosY);
	const FGuid SeededGuid = BpxReflection::SeedGuidFromJoined(JoinedPrefix);

	// Idempotent on the seeded GUID.
	for (UEdGraphNode* ExistingNode : Graph->Nodes)
	{
		if (ExistingNode && ExistingNode->NodeGuid == SeededGuid)
		{
			Result.bSuccess = true;
			Result.bSkipped = true;
			Result.NodeGuid = SeededGuid;
			return Result;
		}
	}

	// Deterministic object name — same rationale as AddSelfMemberGetNode:
	// default NewObject<>(Outer) delegates to MakeUniqueObjectName's monotonic
	// counter, which leaks session-state into the package FNameMap.
	// BpxBranch_<x>_<y> keeps replay byte-identical round-to-round.
	const FName NewNodeName(*FString::Printf(
		TEXT("BpxBranch_%d_%d"), PosX, PosY));
	UK2Node_IfThenElse* NewNode = NewObject<UK2Node_IfThenElse>(Graph, NewNodeName);
	Graph->AddNode(NewNode, /*bUserAction*/ false, /*bSelectNewNode*/ false);
	NewNode->NodeGuid = SeededGuid;
	NewNode->NodePosX = PosX;
	NewNode->NodePosY = PosY;
	NewNode->PostPlacedNewNode();
	NewNode->AllocateDefaultPins();

	BpxReflection::SeedPinGuidsForNode(NewNode, JoinedPrefix);

	Result.bSuccess = true;
	Result.NodeGuid = SeededGuid;
	return Result;
}

FBpxReflectionResult UBpxReflectionOps::SetGraphPinLiteralDefault(
	UBlueprint* Blueprint, FName GraphName,
	const FString& NodeGuidStr, FName PinName, const FString& LiteralText)
{
	FBpxReflectionResult Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (GraphName.IsNone())
	{
		Result.ErrorMessage = TEXT("GraphName is empty");
		return Result;
	}
	if (NodeGuidStr.IsEmpty())
	{
		Result.ErrorMessage = TEXT("NodeGuidStr is empty");
		return Result;
	}

	FGuid NodeGuid;
	if (!FGuid::Parse(NodeGuidStr, NodeGuid))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("FGuid::Parse failed on NodeGuidStr='%s' — expected 32-char hex or {8-4-4-4-12}"),
			*NodeGuidStr);
		return Result;
	}

	UEdGraph* Graph = BpxReflection::FindFunctionGraphByName(Blueprint, GraphName);
	if (!Graph)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("No graph named '%s' on '%s' (checked FunctionGraphs / ImplementedInterfaces / UbergraphPages)"),
			*GraphName.ToString(), *Blueprint->GetPathName());
		return Result;
	}

	UEdGraphNode* Node = nullptr;
	for (UEdGraphNode* N : Graph->Nodes)
	{
		if (N && N->NodeGuid == NodeGuid)
		{
			Node = N;
			break;
		}
	}
	if (!Node)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Node %s not found in graph '%s'"),
			*NodeGuid.ToString(), *GraphName.ToString());
		return Result;
	}

	UEdGraphPin* Pin = Node->FindPin(PinName);
	if (!Pin)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Pin '%s' not found on node %s"),
			*PinName.ToString(), *Node->GetName());
		return Result;
	}

	Result.BeforeText = Pin->DefaultValue;

	if (Pin->DefaultValue == LiteralText)
	{
		Result.bSuccess = true;
		Result.bSkipped = true;
		Result.AfterText = LiteralText;
		return Result;
	}

	if (const UEdGraphSchema* Schema = Pin->GetSchema())
	{
		Schema->TrySetDefaultValue(*Pin, LiteralText);
	}
	else
	{
		Pin->DefaultValue = LiteralText;
	}

	Result.bSuccess = true;
	Result.AfterText = Pin->DefaultValue;
	return Result;
}

// --- M28.3.2 — FunctionReference / VariableReference node spawns ---

namespace BpxReflection
{
	/**
	 * Compose the determinism-seed prefix for an M28.3.2 spawn op. Includes the
	 * node "kind" discriminator (`call` / `varget` / `varset`), the resolved
	 * member, and the target-class context (`self` or the external class's
	 * full path) so two different external targets with the same member FName
	 * get distinct seeds. Position included so distinct spawns at different
	 * positions in the same graph are distinct.
	 */
	static FString MakeMemberRefSeedPrefix(
		UBlueprint* Blueprint, FName GraphName, const TCHAR* Kind,
		FName MemberName, UClass* TargetClass, int32 PosX, int32 PosY)
	{
		const FString Ctx = TargetClass ? TargetClass->GetPathName() : FString(TEXT("self"));
		return Blueprint->GetPathName()
			+ TEXT(":graph:") + GraphName.ToString()
			+ TEXT(":") + Kind + TEXT(":") + MemberName.ToString()
			+ TEXT(":") + Ctx
			+ TEXT(":") + FString::FromInt(PosX) + TEXT(",") + FString::FromInt(PosY);
	}
}

FBpxNodeResult UBpxReflectionOps::AddCallFunctionNode(
	UBlueprint* Blueprint, FName GraphName,
	FName MemberName, UClass* TargetClass, FVector2D Position)
{
	FBpxNodeResult Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (GraphName.IsNone())
	{
		Result.ErrorMessage = TEXT("GraphName is empty");
		return Result;
	}
	if (MemberName.IsNone())
	{
		Result.ErrorMessage = TEXT("MemberName is empty");
		return Result;
	}

	UEdGraph* Graph = BpxReflection::FindFunctionGraphByName(Blueprint, GraphName);
	if (!Graph)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("No graph named '%s' on '%s' (checked FunctionGraphs / ImplementedInterfaces / UbergraphPages)"),
			*GraphName.ToString(), *Blueprint->GetPathName());
		return Result;
	}

	const int32 PosX = static_cast<int32>(Position.X);
	const int32 PosY = static_cast<int32>(Position.Y);
	const FString JoinedPrefix = BpxReflection::MakeMemberRefSeedPrefix(
		Blueprint, GraphName, TEXT("call"), MemberName, TargetClass, PosX, PosY);
	const FGuid SeededGuid = BpxReflection::SeedGuidFromJoined(JoinedPrefix);

	for (UEdGraphNode* ExistingNode : Graph->Nodes)
	{
		if (ExistingNode && ExistingNode->NodeGuid == SeededGuid)
		{
			Result.bSuccess = true;
			Result.bSkipped = true;
			Result.NodeGuid = SeededGuid;
			return Result;
		}
	}

	const FName NewNodeName(*FString::Printf(
		TEXT("BpxCall_%s_%d_%d"), *MemberName.ToString(), PosX, PosY));
	UK2Node_CallFunction* NewNode = NewObject<UK2Node_CallFunction>(Graph, NewNodeName);
	// FunctionReference must be set BEFORE AllocateDefaultPins — pin set is
	// signature-derived; without the reference the node allocates only the
	// bare execute/then exec pair with no typed params and no ReturnValue.
	if (TargetClass)
	{
		NewNode->FunctionReference.SetExternalMember(MemberName, TargetClass);
	}
	else
	{
		NewNode->FunctionReference.SetSelfMember(MemberName);
	}
	Graph->AddNode(NewNode, /*bUserAction*/ false, /*bSelectNewNode*/ false);
	NewNode->NodeGuid = SeededGuid;
	NewNode->NodePosX = PosX;
	NewNode->NodePosY = PosY;
	NewNode->PostPlacedNewNode();
	NewNode->AllocateDefaultPins();

	BpxReflection::SeedPinGuidsForNode(NewNode, JoinedPrefix);

	Result.bSuccess = true;
	Result.NodeGuid = SeededGuid;
	return Result;
}

FBpxNodeResult UBpxReflectionOps::AddVariableGetNode(
	UBlueprint* Blueprint, FName GraphName,
	FName MemberName, UClass* TargetClass, FVector2D Position)
{
	FBpxNodeResult Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (GraphName.IsNone())
	{
		Result.ErrorMessage = TEXT("GraphName is empty");
		return Result;
	}
	if (MemberName.IsNone())
	{
		Result.ErrorMessage = TEXT("MemberName is empty");
		return Result;
	}

	UEdGraph* Graph = BpxReflection::FindFunctionGraphByName(Blueprint, GraphName);
	if (!Graph)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("No graph named '%s' on '%s' (checked FunctionGraphs / ImplementedInterfaces / UbergraphPages)"),
			*GraphName.ToString(), *Blueprint->GetPathName());
		return Result;
	}

	const int32 PosX = static_cast<int32>(Position.X);
	const int32 PosY = static_cast<int32>(Position.Y);
	const FString JoinedPrefix = BpxReflection::MakeMemberRefSeedPrefix(
		Blueprint, GraphName, TEXT("varget"), MemberName, TargetClass, PosX, PosY);
	const FGuid SeededGuid = BpxReflection::SeedGuidFromJoined(JoinedPrefix);

	for (UEdGraphNode* ExistingNode : Graph->Nodes)
	{
		if (ExistingNode && ExistingNode->NodeGuid == SeededGuid)
		{
			Result.bSuccess = true;
			Result.bSkipped = true;
			Result.NodeGuid = SeededGuid;
			return Result;
		}
	}

	const FName NewNodeName(*FString::Printf(
		TEXT("BpxVarGet_%s_%d_%d"), *MemberName.ToString(), PosX, PosY));
	UK2Node_VariableGet* NewNode = NewObject<UK2Node_VariableGet>(Graph, NewNodeName);
	if (TargetClass)
	{
		NewNode->VariableReference.SetExternalMember(MemberName, TargetClass);
	}
	else
	{
		NewNode->VariableReference.SetSelfMember(MemberName);
	}
	Graph->AddNode(NewNode, /*bUserAction*/ false, /*bSelectNewNode*/ false);
	NewNode->NodeGuid = SeededGuid;
	NewNode->NodePosX = PosX;
	NewNode->NodePosY = PosY;
	NewNode->PostPlacedNewNode();
	NewNode->AllocateDefaultPins();

	BpxReflection::SeedPinGuidsForNode(NewNode, JoinedPrefix);

	Result.bSuccess = true;
	Result.NodeGuid = SeededGuid;
	return Result;
}

FBpxNodeResult UBpxReflectionOps::AddVariableSetNode(
	UBlueprint* Blueprint, FName GraphName,
	FName MemberName, UClass* TargetClass, FVector2D Position)
{
	FBpxNodeResult Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (GraphName.IsNone())
	{
		Result.ErrorMessage = TEXT("GraphName is empty");
		return Result;
	}
	if (MemberName.IsNone())
	{
		Result.ErrorMessage = TEXT("MemberName is empty");
		return Result;
	}

	UEdGraph* Graph = BpxReflection::FindFunctionGraphByName(Blueprint, GraphName);
	if (!Graph)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("No graph named '%s' on '%s' (checked FunctionGraphs / ImplementedInterfaces / UbergraphPages)"),
			*GraphName.ToString(), *Blueprint->GetPathName());
		return Result;
	}

	const int32 PosX = static_cast<int32>(Position.X);
	const int32 PosY = static_cast<int32>(Position.Y);
	const FString JoinedPrefix = BpxReflection::MakeMemberRefSeedPrefix(
		Blueprint, GraphName, TEXT("varset"), MemberName, TargetClass, PosX, PosY);
	const FGuid SeededGuid = BpxReflection::SeedGuidFromJoined(JoinedPrefix);

	for (UEdGraphNode* ExistingNode : Graph->Nodes)
	{
		if (ExistingNode && ExistingNode->NodeGuid == SeededGuid)
		{
			Result.bSuccess = true;
			Result.bSkipped = true;
			Result.NodeGuid = SeededGuid;
			return Result;
		}
	}

	const FName NewNodeName(*FString::Printf(
		TEXT("BpxVarSet_%s_%d_%d"), *MemberName.ToString(), PosX, PosY));
	UK2Node_VariableSet* NewNode = NewObject<UK2Node_VariableSet>(Graph, NewNodeName);
	if (TargetClass)
	{
		NewNode->VariableReference.SetExternalMember(MemberName, TargetClass);
	}
	else
	{
		NewNode->VariableReference.SetSelfMember(MemberName);
	}
	Graph->AddNode(NewNode, /*bUserAction*/ false, /*bSelectNewNode*/ false);
	NewNode->NodeGuid = SeededGuid;
	NewNode->NodePosX = PosX;
	NewNode->NodePosY = PosY;
	NewNode->PostPlacedNewNode();
	NewNode->AllocateDefaultPins();

	BpxReflection::SeedPinGuidsForNode(NewNode, JoinedPrefix);

	Result.bSuccess = true;
	Result.NodeGuid = SeededGuid;
	return Result;
}

// --- M28.3.3 — CustomEvent / ExecutionSequence / DynamicCast ---

FBpxNodeResult UBpxReflectionOps::AddCustomEventNode(
	UBlueprint* Blueprint, FName GraphName, FName EventName, FVector2D Position)
{
	FBpxNodeResult Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (GraphName.IsNone())
	{
		Result.ErrorMessage = TEXT("GraphName is empty");
		return Result;
	}
	if (EventName.IsNone())
	{
		Result.ErrorMessage = TEXT("EventName is empty");
		return Result;
	}

	UEdGraph* Graph = BpxReflection::FindFunctionGraphByName(Blueprint, GraphName);
	if (!Graph)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("No graph named '%s' on '%s' (checked FunctionGraphs / ImplementedInterfaces / UbergraphPages)"),
			*GraphName.ToString(), *Blueprint->GetPathName());
		return Result;
	}

	// CustomEvent must live in an ubergraph — K2Node_Event::IsCompatibleWithGraph
	// rejects every other graph type at compile time. Surface the check early
	// so plan authors see a structured error instead of a compile-time failure.
	const UEdGraphSchema* Schema = Graph->GetSchema();
	if (!Schema || Schema->GetGraphType(Graph) != GT_Ubergraph)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Graph '%s' is not an ubergraph — CustomEvent only authors into ubergraphs (EventGraph). Use add_call_function_node for function / interface-override graphs."),
			*GraphName.ToString());
		return Result;
	}

	const int32 PosX = static_cast<int32>(Position.X);
	const int32 PosY = static_cast<int32>(Position.Y);
	const FString JoinedPrefix = Blueprint->GetPathName()
		+ TEXT(":graph:") + GraphName.ToString()
		+ TEXT(":custom_event:") + EventName.ToString()
		+ TEXT(":") + FString::FromInt(PosX) + TEXT(",") + FString::FromInt(PosY);
	const FGuid SeededGuid = BpxReflection::SeedGuidFromJoined(JoinedPrefix);

	for (UEdGraphNode* ExistingNode : Graph->Nodes)
	{
		if (ExistingNode && ExistingNode->NodeGuid == SeededGuid)
		{
			Result.bSuccess = true;
			Result.bSkipped = true;
			Result.NodeGuid = SeededGuid;
			return Result;
		}
	}

	const FName NewNodeName(*FString::Printf(
		TEXT("BpxCustomEvent_%s_%d_%d"), *EventName.ToString(), PosX, PosY));
	UK2Node_CustomEvent* NewNode = NewObject<UK2Node_CustomEvent>(Graph, NewNodeName);
	// CustomFunctionName (inherited from UK2Node_Event) must be set before
	// AllocateDefaultPins — the delegate pin name + auto-generated signature
	// read from it inside CreatePinsForFunctionEntryExit.
	NewNode->CustomFunctionName = EventName;
	Graph->AddNode(NewNode, /*bUserAction*/ false, /*bSelectNewNode*/ false);
	NewNode->NodeGuid = SeededGuid;
	NewNode->NodePosX = PosX;
	NewNode->NodePosY = PosY;
	NewNode->PostPlacedNewNode();
	NewNode->AllocateDefaultPins();

	BpxReflection::SeedPinGuidsForNode(NewNode, JoinedPrefix);

	Result.bSuccess = true;
	Result.NodeGuid = SeededGuid;
	return Result;
}

FBpxNodeResult UBpxReflectionOps::AddExecutionSequenceNode(
	UBlueprint* Blueprint, FName GraphName, int32 NumOutputs, FVector2D Position)
{
	FBpxNodeResult Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (GraphName.IsNone())
	{
		Result.ErrorMessage = TEXT("GraphName is empty");
		return Result;
	}
	if (NumOutputs < 2)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("NumOutputs=%d — ExecutionSequence requires at least 2 outputs; one-output sequences should be authored as direct wires"),
			NumOutputs);
		return Result;
	}
	if (NumOutputs > 16)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("NumOutputs=%d exceeds sanity cap of 16 — raise the cap if a concrete driver needs more"),
			NumOutputs);
		return Result;
	}

	UEdGraph* Graph = BpxReflection::FindFunctionGraphByName(Blueprint, GraphName);
	if (!Graph)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("No graph named '%s' on '%s' (checked FunctionGraphs / ImplementedInterfaces / UbergraphPages)"),
			*GraphName.ToString(), *Blueprint->GetPathName());
		return Result;
	}

	const int32 PosX = static_cast<int32>(Position.X);
	const int32 PosY = static_cast<int32>(Position.Y);
	const FString JoinedPrefix = Blueprint->GetPathName()
		+ TEXT(":graph:") + GraphName.ToString()
		+ TEXT(":execseq:") + FString::FromInt(NumOutputs)
		+ TEXT(":") + FString::FromInt(PosX) + TEXT(",") + FString::FromInt(PosY);
	const FGuid SeededGuid = BpxReflection::SeedGuidFromJoined(JoinedPrefix);

	for (UEdGraphNode* ExistingNode : Graph->Nodes)
	{
		if (ExistingNode && ExistingNode->NodeGuid == SeededGuid)
		{
			Result.bSuccess = true;
			Result.bSkipped = true;
			Result.NodeGuid = SeededGuid;
			return Result;
		}
	}

	const FName NewNodeName(*FString::Printf(
		TEXT("BpxExecSeq_%d_%d_%d"), NumOutputs, PosX, PosY));
	UK2Node_ExecutionSequence* NewNode = NewObject<UK2Node_ExecutionSequence>(Graph, NewNodeName);
	Graph->AddNode(NewNode, /*bUserAction*/ false, /*bSelectNewNode*/ false);
	NewNode->NodeGuid = SeededGuid;
	NewNode->NodePosX = PosX;
	NewNode->NodePosY = PosY;
	NewNode->PostPlacedNewNode();
	NewNode->AllocateDefaultPins();

	// Default alloc produces Then_0 + Then_1. Add additional outputs via
	// IK2Node_AddPinInterface::AddInputPin (misleading name — it adds a new
	// THEN-OUT pin, not an input; that's UE's API wart, not ours).
	for (int32 Extra = 0; Extra < NumOutputs - 2; ++Extra)
	{
		NewNode->AddInputPin();
	}

	// Seed pin GUIDs AFTER AddInputPin so the extended Then_N+ pins get
	// deterministic PinIds too.
	BpxReflection::SeedPinGuidsForNode(NewNode, JoinedPrefix);

	Result.bSuccess = true;
	Result.NodeGuid = SeededGuid;
	return Result;
}

FBpxNodeResult UBpxReflectionOps::AddDynamicCastNode(
	UBlueprint* Blueprint, FName GraphName, UClass* TargetClass, FVector2D Position)
{
	FBpxNodeResult Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (GraphName.IsNone())
	{
		Result.ErrorMessage = TEXT("GraphName is empty");
		return Result;
	}
	if (!TargetClass)
	{
		Result.ErrorMessage = TEXT("TargetClass is null — DynamicCast requires a concrete UClass to type its As<X> output");
		return Result;
	}

	UEdGraph* Graph = BpxReflection::FindFunctionGraphByName(Blueprint, GraphName);
	if (!Graph)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("No graph named '%s' on '%s' (checked FunctionGraphs / ImplementedInterfaces / UbergraphPages)"),
			*GraphName.ToString(), *Blueprint->GetPathName());
		return Result;
	}

	const int32 PosX = static_cast<int32>(Position.X);
	const int32 PosY = static_cast<int32>(Position.Y);
	const FString JoinedPrefix = Blueprint->GetPathName()
		+ TEXT(":graph:") + GraphName.ToString()
		+ TEXT(":cast:") + TargetClass->GetPathName()
		+ TEXT(":") + FString::FromInt(PosX) + TEXT(",") + FString::FromInt(PosY);
	const FGuid SeededGuid = BpxReflection::SeedGuidFromJoined(JoinedPrefix);

	for (UEdGraphNode* ExistingNode : Graph->Nodes)
	{
		if (ExistingNode && ExistingNode->NodeGuid == SeededGuid)
		{
			Result.bSuccess = true;
			Result.bSkipped = true;
			Result.NodeGuid = SeededGuid;
			return Result;
		}
	}

	const FName NewNodeName(*FString::Printf(
		TEXT("BpxCast_%s_%d_%d"), *TargetClass->GetName(), PosX, PosY));
	UK2Node_DynamicCast* NewNode = NewObject<UK2Node_DynamicCast>(Graph, NewNodeName);
	// TargetType must be set before AllocateDefaultPins — the As<X> output pin
	// derives its PinCategory / PinSubCategoryObject from TargetType inside
	// UK2Node_DynamicCast::CreatePinsForCastNode. Post-alloc assignment leaves
	// As<X> as a wildcard.
	NewNode->TargetType = TargetClass;
	Graph->AddNode(NewNode, /*bUserAction*/ false, /*bSelectNewNode*/ false);
	NewNode->NodeGuid = SeededGuid;
	NewNode->NodePosX = PosX;
	NewNode->NodePosY = PosY;
	NewNode->PostPlacedNewNode();
	NewNode->AllocateDefaultPins();

	BpxReflection::SeedPinGuidsForNode(NewNode, JoinedPrefix);

	Result.bSuccess = true;
	Result.NodeGuid = SeededGuid;
	return Result;
}

// --- M28.3.4 — LocalVariable add ---

FBpxReflectionResult UBpxReflectionOps::AddLocalVariableDeterministic(
	UBlueprint* Blueprint, FName FunctionName, FName VarName,
	const FEdGraphPinType& VarType, const FString& DefaultValue)
{
	FBpxReflectionResult Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (FunctionName.IsNone())
	{
		Result.ErrorMessage = TEXT("FunctionName is empty");
		return Result;
	}
	if (VarName.IsNone())
	{
		Result.ErrorMessage = TEXT("VarName is empty");
		return Result;
	}

	UEdGraph* Graph = BpxReflection::FindFunctionGraphByName(Blueprint, FunctionName);
	if (!Graph)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("No function graph named '%s' on '%s' (checked FunctionGraphs / ImplementedInterfaces / UbergraphPages)"),
			*FunctionName.ToString(), *Blueprint->GetPathName());
		return Result;
	}

	// Find the graph's UK2Node_FunctionEntry. Ubergraphs don't have one; this
	// check also rejects interface-override graphs that haven't been populated
	// yet (edge case — an interface attach via M28.2.4 always authors an entry).
	UK2Node_FunctionEntry* FunctionEntry = nullptr;
	for (UEdGraphNode* Node : Graph->Nodes)
	{
		if (UK2Node_FunctionEntry* Entry = Cast<UK2Node_FunctionEntry>(Node))
		{
			FunctionEntry = Entry;
			break;
		}
	}
	if (!FunctionEntry)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Graph '%s' has no UK2Node_FunctionEntry — local variables only author into function / interface-override graphs, not ubergraphs"),
			*FunctionName.ToString());
		return Result;
	}

	// Idempotency pre-check. Walk LocalVariables[] by name. Match short-
	// circuits with bSkipped=true. Semantic equivalent of M28.2.1's
	// NewVariables[] pre-check; FBlueprintEditorUtils::FindLocalVariable
	// does the same walk but with a broader return contract — we need the
	// skip signal specifically, so inline the name compare.
	for (const FBPVariableDescription& Var : FunctionEntry->LocalVariables)
	{
		if (Var.VarName == VarName)
		{
			Result.bSuccess = true;
			Result.bSkipped = true;
			Result.BeforeText = FString::Printf(
				TEXT("localvar-exists:%s::%s"),
				*FunctionName.ToString(), *VarName.ToString());
			Result.AfterText = Result.BeforeText;
			return Result;
		}
	}

	// Engine call. Returns false if the variable couldn't be added — usually
	// because the graph doesn't support local vars (we already gated on
	// FunctionEntry above, so a false here is unexpected and worth surfacing
	// clearly).
	const bool bAdded = FBlueprintEditorUtils::AddLocalVariable(
		Blueprint, Graph, VarName, VarType, DefaultValue);
	if (!bAdded)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("FBlueprintEditorUtils::AddLocalVariable('%s' in '%s') returned false"),
			*VarName.ToString(), *FunctionName.ToString());
		return Result;
	}

	// Find the just-added entry and overwrite VarGuid with a deterministic
	// md5-seeded value. Without this, every run produces a different .uasset
	// md5 (engine assigns FGuid::NewGuid() at BlueprintEditorUtils.cpp:5433),
	// tripping M28.pre.3 soak round-2 compare. Seed key includes FunctionName
	// because local vars with the same VarName can legitimately coexist in
	// different functions — unlike M28.2.1's member-var case.
	FBPVariableDescription* NewEntry = nullptr;
	for (FBPVariableDescription& Var : FunctionEntry->LocalVariables)
	{
		if (Var.VarName == VarName)
		{
			NewEntry = &Var;
			break;
		}
	}
	if (!NewEntry)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("AddLocalVariable returned true but '%s' is not on FunctionEntry->LocalVariables for '%s'"),
			*VarName.ToString(), *FunctionName.ToString());
		return Result;
	}

	const FString SeedKey = Blueprint->GetPathName()
		+ TEXT(":func:") + FunctionName.ToString()
		+ TEXT(":localvar:") + VarName.ToString();
	NewEntry->VarGuid = BpxReflection::SeedGuidFromJoined(SeedKey);

	// AddLocalVariable already called MarkBlueprintAsStructurallyModified
	// (BlueprintEditorUtils.cpp:5445) on the success path — don't double-mark.
	// Per the M26.1.2 regression-chase block: re-entering structurally-
	// modified listeners can invalidate freshly-seeded GUIDs.

	Result.bSuccess = true;
	Result.BeforeText = TEXT("no-localvar");
	Result.AfterText = FString::Printf(
		TEXT("localvar-added:%s::%s"),
		*FunctionName.ToString(), *VarName.ToString());
	return Result;
}

// --- M28.11 — function / custom-event typed-parameter authoring ---

FBpxReflectionResult UBpxReflectionOps::AddFunctionUserDefinedPin(
	UBlueprint* Blueprint, FName FunctionName, FName PinName,
	const FEdGraphPinType& PinType, bool bDirectionIsOutput,
	const FString& DefaultValue)
{
	FBpxReflectionResult Result;
	const EEdGraphPinDirection Direction = bDirectionIsOutput ? EGPD_Output : EGPD_Input;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (FunctionName.IsNone())
	{
		Result.ErrorMessage = TEXT("FunctionName is empty");
		return Result;
	}
	if (PinName.IsNone())
	{
		Result.ErrorMessage = TEXT("PinName is empty");
		return Result;
	}

	UK2Node_EditablePinBase* TargetNode = nullptr;
	const TCHAR* SeedScope = nullptr;

	// Path 1: function graph (function or interface-override).
	UEdGraph* Graph = BpxReflection::FindFunctionGraphByName(Blueprint, FunctionName);
	if (Graph)
	{
		// Reject ubergraphs at this layer — ubergraphs don't carry an Entry
		// node we can hang user pins off; the CustomEvent path handles event
		// parameters separately. (FindFunctionGraphByName intentionally
		// returns ubergraphs for the M28.3.x graph-walk family; we filter
		// them back out here.)
		const UEdGraphSchema* Schema = Graph->GetSchema();
		if (Schema && Schema->GetGraphType(Graph) == GT_Ubergraph)
		{
			// Fall through to the CustomEvent search — a function and an
			// ubergraph can't share a name, but a CustomEvent in the
			// ubergraph can have the same FName.
			Graph = nullptr;
		}
	}

	if (Graph)
	{
		UK2Node_FunctionEntry* EntryNode = nullptr;
		UK2Node_FunctionResult* ResultNode = nullptr;
		for (UEdGraphNode* Node : Graph->Nodes)
		{
			if (!EntryNode)
			{
				EntryNode = Cast<UK2Node_FunctionEntry>(Node);
			}
			if (!ResultNode)
			{
				ResultNode = Cast<UK2Node_FunctionResult>(Node);
			}
		}

		if (Direction == EGPD_Output)
		{
			// Function input → Entry node's outputs.
			if (!EntryNode)
			{
				Result.ErrorMessage = FString::Printf(
					TEXT("Graph '%s' has no UK2Node_FunctionEntry — was the function created via add_bp_function?"),
					*FunctionName.ToString());
				return Result;
			}
			TargetNode = EntryNode;
			SeedScope = TEXT("entry");
		}
		else // EGPD_Input
		{
			// Function output → Result node's inputs. Auto-spawn Result if
			// missing (pure functions skip the engine's auto-Result on
			// create; retroactive output adds need to materialize one).
			if (!ResultNode)
			{
				if (!EntryNode)
				{
					Result.ErrorMessage = FString::Printf(
						TEXT("Graph '%s' has neither Entry nor Result node — refusing to author into a malformed function graph"),
						*FunctionName.ToString());
					return Result;
				}

				// NewObject pattern matches MovieSceneDirectorBlueprintUtils.cpp:211
				// (the engine's own retroactive Result-spawn site). NodeGuid +
				// pin IDs seeded with the same `<bp>:func:<fn>:result` key
				// `AddFunctionGraphDeterministic` uses, so a function created
				// non-pure (Result auto-spawned by engine) and a function created
				// pure-then-promoted (Result auto-spawned here) end up with
				// byte-identical Result NodeGuids.
				const FName ResultNodeName(*FString::Printf(
					TEXT("BpxFuncResult_%s"), *FunctionName.ToString()));
				ResultNode = NewObject<UK2Node_FunctionResult>(
					Graph, ResultNodeName, RF_Transactional);
				ResultNode->FunctionReference.SetSelfMember(FunctionName);
				ResultNode->bIsEditable = true;
				// Position offset from Entry to mirror the BP-editor's auto-
				// spawn placement; the value isn't saved as part of asset
				// byte-identity (NodePosX/Y land in the .uasset but the
				// position constants here are deterministic so byte-identity
				// is preserved across replays).
				ResultNode->NodePosX = EntryNode->NodePosX + 400;
				ResultNode->NodePosY = EntryNode->NodePosY;
				Graph->AddNode(ResultNode, /*bUserAction*/ false, /*bSelectNewNode*/ false);
				ResultNode->PostPlacedNewNode();
				ResultNode->AllocateDefaultPins();

				const FString ResultPrefix = Blueprint->GetPathName()
					+ TEXT(":func:") + FunctionName.ToString()
					+ TEXT(":result");
				ResultNode->NodeGuid = BpxReflection::SeedGuidFromJoined(ResultPrefix);
				BpxReflection::SeedPinGuidsForNode(ResultNode, ResultPrefix);
			}
			TargetNode = ResultNode;
			SeedScope = TEXT("result");
		}
	}
	else
	{
		// Path 2: custom event — walk all ubergraphs for a UK2Node_CustomEvent
		// whose CustomFunctionName matches.
		if (Direction != EGPD_Output)
		{
			Result.ErrorMessage = FString::Printf(
				TEXT("CustomEvent '%s' only supports Direction=EGPD_Output (event input pins). EGPD_Input is rejected — events have no user-authorable outputs."),
				*FunctionName.ToString());
			return Result;
		}

		for (UEdGraph* Ubergraph : Blueprint->UbergraphPages)
		{
			if (!Ubergraph)
			{
				continue;
			}
			for (UEdGraphNode* Node : Ubergraph->Nodes)
			{
				if (UK2Node_CustomEvent* Event = Cast<UK2Node_CustomEvent>(Node))
				{
					if (Event->CustomFunctionName == FunctionName)
					{
						TargetNode = Event;
						break;
					}
				}
			}
			if (TargetNode)
			{
				break;
			}
		}

		if (!TargetNode)
		{
			Result.ErrorMessage = FString::Printf(
				TEXT("No function graph or custom event named '%s' on '%s' (checked FunctionGraphs / ImplementedInterfaces / UbergraphPages.CustomEvent)"),
				*FunctionName.ToString(), *Blueprint->GetPathName());
			return Result;
		}
		SeedScope = TEXT("custom_event");
	}

	check(TargetNode);
	check(SeedScope);

	// Idempotence — short-circuit if a user pin with this name already exists
	// on this node. Skip path returns success without modifying the asset.
	// Inlined by hand (vs. K2Node_EditablePinBase::UserDefinedPinExists) because
	// the engine helper isn't exported with BLUEPRINTGRAPH_API and would
	// produce LNK2019 across the module boundary.
	for (const TSharedPtr<FUserPinInfo>& ExistingPin : TargetNode->UserDefinedPins)
	{
		if (ExistingPin.IsValid() && ExistingPin->PinName == PinName)
		{
			Result.bSuccess = true;
			Result.bSkipped = true;
			Result.BeforeText = FString::Printf(
				TEXT("user-pin-exists:%s::%s"),
				*FunctionName.ToString(), *PinName.ToString());
			Result.AfterText = Result.BeforeText;
			return Result;
		}
	}

	// Validate the node accepts user pins of this type + direction. The
	// engine's CanCreateUserDefinedPin defaults to false on the abstract
	// base; FunctionEntry / FunctionResult / CustomEvent each override to
	// allow input or output pins per their role.
	FText ErrorText;
	if (!TargetNode->CanCreateUserDefinedPin(PinType, Direction, ErrorText))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Node refused user pin '%s' (Direction=%s): %s"),
			*PinName.ToString(),
			(Direction == EGPD_Output) ? TEXT("Output") : TEXT("Input"),
			*ErrorText.ToString());
		return Result;
	}

	// Create the pin. bUseUniqueName=false so we author the exact requested
	// name (the idempotence pre-check + the engine's compile-time
	// duplicate-name guard are sufficient).
	UEdGraphPin* NewPin = TargetNode->CreateUserDefinedPin(
		PinName, PinType, Direction, /*bUseUniqueName*/ false);
	if (!NewPin)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("CreateUserDefinedPin returned null for '%s' on node '%s'"),
			*PinName.ToString(), *TargetNode->GetName());
		return Result;
	}

	// Apply DefaultValue if non-empty, via the engine's helper. Result-node
	// inputs (function outputs) don't carry a default at runtime — UE's
	// engine UI suppresses the Default Value field on Result-node pins —
	// but the helper accepts the assignment harmlessly. Skipping the call
	// for Result targets would diverge from the simpler "always apply"
	// shape; leave the assignment for API symmetry.
	if (!DefaultValue.IsEmpty())
	{
		for (TSharedPtr<FUserPinInfo>& UserPin : TargetNode->UserDefinedPins)
		{
			if (UserPin.IsValid() && UserPin->PinName == PinName)
			{
				TargetNode->ModifyUserDefinedPinDefaultValue(UserPin, DefaultValue);
				break;
			}
		}
	}

	// Seed PinId. Without this, every replay would assign a fresh
	// FGuid::NewGuid() at UEdGraphPin::CreatePin and the .uasset md5 would
	// drift (M28.pre.3 soak round 2 catches it). Direction encoded so an
	// input + output with the same name on the same node (rare but legal
	// for some node types) get distinct PinIds.
	const FString DirStr = (Direction == EGPD_Output) ? TEXT("out") : TEXT("in");
	const FString SeedKey = Blueprint->GetPathName()
		+ TEXT(":") + FString(SeedScope)
		+ TEXT(":") + FunctionName.ToString()
		+ TEXT(":userpin:") + PinName.ToString()
		+ TEXT(":") + DirStr;
	NewPin->PinId = BpxReflection::SeedGuidFromJoined(SeedKey);

	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);

	Result.bSuccess = true;
	Result.BeforeText = TEXT("no-user-pin");
	Result.AfterText = FString::Printf(
		TEXT("user-pin-added:%s::%s::%s"),
		*FunctionName.ToString(), *PinName.ToString(), *DirStr);
	return Result;
}

// --- M28.12 — native virtual override authoring ---

FBpxGraphEndpoints UBpxReflectionOps::AddFunctionOverrideDeterministic(
	UBlueprint* Blueprint, FName FunctionName)
{
	FBpxGraphEndpoints Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (FunctionName.IsNone())
	{
		Result.ErrorMessage = TEXT("FunctionName is empty");
		return Result;
	}
	if (!Blueprint->ParentClass)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Blueprint '%s' has no ParentClass — refusing to author an override"),
			*Blueprint->GetPathName());
		return Result;
	}

	// Resolve the parent UFUNCTION via FindFunctionByName, which walks the
	// entire ancestor chain (parent → grandparent → ...). This matches the
	// BP editor's "Override Function" menu — overridable virtuals from any
	// ancestor are allowed.
	UFunction* ParentFn = Blueprint->ParentClass->FindFunctionByName(FunctionName);
	if (!ParentFn)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Parent class '%s' (or any ancestor) has no UFUNCTION named '%s' — function not overridable"),
			*Blueprint->ParentClass->GetPathName(), *FunctionName.ToString());
		return Result;
	}

	// Reject non-user-overridable functions. FUNC_BlueprintEvent is set by
	// UHT for `BlueprintImplementableEvent` and `BlueprintNativeEvent` UFUNCTIONs
	// — exactly the set the BP editor's "Override Function" menu surfaces.
	// A regular `BlueprintCallable` virtual without the BlueprintEvent flag
	// isn't BP-overridable; the engine compile would refuse downstream, so
	// we reject here for a crisp error.
	if (!ParentFn->HasAnyFunctionFlags(FUNC_BlueprintEvent))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Parent UFUNCTION '%s' on '%s' is not overridable from BP (missing FUNC_BlueprintEvent — needs BlueprintImplementableEvent or BlueprintNativeEvent)"),
			*FunctionName.ToString(), *Blueprint->ParentClass->GetPathName());
		return Result;
	}

	// Idempotent: if a graph with this name exists (function / interface /
	// ubergraph), return its Entry/Return GUIDs without authoring a second
	// graph. Mirrors AddFunctionGraphDeterministic's skip semantics.
	if (UEdGraph* Existing = BpxReflection::FindFunctionGraphByName(Blueprint, FunctionName))
	{
		for (UEdGraphNode* Node : Existing->Nodes)
		{
			if (!Node)
			{
				continue;
			}
			if (Node->IsA<UK2Node_FunctionEntry>())
			{
				Result.EntryGuid = Node->NodeGuid;
			}
			else if (Node->IsA<UK2Node_FunctionResult>())
			{
				Result.ReturnGuid = Node->NodeGuid;
			}
		}
		Result.bSuccess = true;
		Result.bSkipped = true;
		return Result;
	}

	Blueprint->Modify();

	UEdGraph* NewGraph = FBlueprintEditorUtils::CreateNewGraph(
		Blueprint, FunctionName, UEdGraph::StaticClass(),
		UEdGraphSchema_K2::StaticClass());
	if (!NewGraph)
	{
		Result.ErrorMessage = TEXT("CreateNewGraph returned null");
		return Result;
	}

	// AddFunctionGraph<UClass>(..., ParentClass) walks ParentClass for a
	// matching-name UFUNCTION and uses its signature to build the Entry
	// node's pins. bIsUserCreated=false flags this as an override so the
	// editor's function-list panel groups it under "Override Functions".
	// Same template variant OverrideInterfaceFunction uses for interfaces.
	FBlueprintEditorUtils::AddFunctionGraph<UClass>(
		Blueprint, NewGraph, /*bIsUserCreated*/ false, Blueprint->ParentClass);

	// AddFunctionGraph<UClass> only spawns Entry by default; if the parent
	// UFUNCTION has any output / return parameter, spawn a Result node so
	// callers can wire Get.<var>.OUT → Return.<pin>.IN cleanly. Same logic
	// as OverrideInterfaceFunction — kept inline here rather than refactored
	// because the seed-prefix string differs (`override_func` vs interface
	// override's `<bp>:<fn>:<slot>` pre-M28.12 convention).
	UK2Node_FunctionEntry* EntryNode = nullptr;
	UK2Node_FunctionResult* ReturnNode = nullptr;
	for (UEdGraphNode* Node : NewGraph->Nodes)
	{
		if (!EntryNode)
		{
			EntryNode = Cast<UK2Node_FunctionEntry>(Node);
		}
		if (!ReturnNode)
		{
			ReturnNode = Cast<UK2Node_FunctionResult>(Node);
		}
	}
	if (!EntryNode)
	{
		Result.ErrorMessage = TEXT("AddFunctionGraph produced no UK2Node_FunctionEntry");
		return Result;
	}
	if (!ReturnNode)
	{
		bool bHasAnyOutParam = false;
		for (TFieldIterator<FProperty> It(ParentFn); It; ++It)
		{
			if (It->HasAnyPropertyFlags(CPF_OutParm) || It->HasAnyPropertyFlags(CPF_ReturnParm))
			{
				bHasAnyOutParam = true;
				break;
			}
		}
		if (bHasAnyOutParam)
		{
			const FName ReturnNodeName(*FString::Printf(
				TEXT("BpxFuncResult_%s"), *FunctionName.ToString()));
			ReturnNode = NewObject<UK2Node_FunctionResult>(NewGraph, ReturnNodeName);
			ReturnNode->NodePosX = EntryNode->NodePosX + 400;
			ReturnNode->NodePosY = EntryNode->NodePosY;
			NewGraph->AddNode(ReturnNode, /*bUserAction*/ false, /*bSelectNewNode*/ false);
			ReturnNode->CreateNewGuid();
			ReturnNode->PostPlacedNewNode();
			ReturnNode->AllocateDefaultPins();
		}
	}

	// Seed GraphGuid + Entry/Result NodeGuids + pin IDs deterministically.
	// Distinct prefix `override_func` (vs `func` for fresh functions) so
	// a fresh function and an override on the same BP with the same name
	// (illegal at compile time but possible mid-authoring) get distinct
	// seeds and replay is byte-stable.
	const FString OverridePrefix = Blueprint->GetPathName()
		+ TEXT(":override_func:") + FunctionName.ToString();
	NewGraph->GraphGuid = BpxReflection::SeedGuidFromJoined(OverridePrefix + TEXT(":graph"));

	const FString EntryPrefix = OverridePrefix + TEXT(":entry");
	EntryNode->NodeGuid = BpxReflection::SeedGuidFromJoined(EntryPrefix);
	BpxReflection::SeedPinGuidsForNode(EntryNode, EntryPrefix);

	if (ReturnNode)
	{
		const FString ReturnPrefix = OverridePrefix + TEXT(":return");
		ReturnNode->NodeGuid = BpxReflection::SeedGuidFromJoined(ReturnPrefix);
		BpxReflection::SeedPinGuidsForNode(ReturnNode, ReturnPrefix);
		Result.ReturnGuid = ReturnNode->NodeGuid;
	}

	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);

	Result.bSuccess = true;
	Result.EntryGuid = EntryNode->NodeGuid;
	return Result;
}

// --- M28.13 — K2Node_MacroInstance authoring (loop unblocker) ---

FBpxNodeResult UBpxReflectionOps::AddMacroInstanceNode(
	UBlueprint* Blueprint, FName GraphName, UEdGraph* MacroGraph, FVector2D Position)
{
	FBpxNodeResult Result;

	if (!Blueprint)
	{
		Result.ErrorMessage = TEXT("Blueprint is null");
		return Result;
	}
	if (GraphName.IsNone())
	{
		Result.ErrorMessage = TEXT("GraphName is empty");
		return Result;
	}
	if (!MacroGraph)
	{
		Result.ErrorMessage = TEXT("MacroGraph is null");
		return Result;
	}

	// Defensive GT_Macro check — Python op should have rejected non-macro
	// graphs already, but the macro-instance pin walk relies on the macro's
	// own Tunnel/Result nodes; pointing at a function or ubergraph would
	// produce a node with no mirrored pins and silently break compile.
	if (const UEdGraphSchema* MacroSchema = MacroGraph->GetSchema())
	{
		if (MacroSchema->GetGraphType(MacroGraph) != GT_Macro)
		{
			Result.ErrorMessage = FString::Printf(
				TEXT("MacroGraph '%s' is not a GT_Macro graph — UK2Node_MacroInstance only mirrors macro graphs"),
				*MacroGraph->GetPathName());
			return Result;
		}
	}

	UEdGraph* Graph = BpxReflection::FindFunctionGraphByName(Blueprint, GraphName);
	if (!Graph)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("No graph named '%s' on '%s' (checked FunctionGraphs / ImplementedInterfaces / UbergraphPages)"),
			*GraphName.ToString(), *Blueprint->GetPathName());
		return Result;
	}

	const int32 PosX = static_cast<int32>(Position.X);
	const int32 PosY = static_cast<int32>(Position.Y);

	// Seed key includes the macro's full path so two different ForEachLoop
	// variants from different libraries don't collide; (x,y) so distinct
	// instances of the same macro in the same graph are distinct.
	const FString JoinedPrefix = Blueprint->GetPathName()
		+ TEXT(":graph:") + GraphName.ToString()
		+ TEXT(":macro:") + MacroGraph->GetPathName()
		+ TEXT(":") + FString::FromInt(PosX) + TEXT(",") + FString::FromInt(PosY);
	const FGuid SeededGuid = BpxReflection::SeedGuidFromJoined(JoinedPrefix);

	for (UEdGraphNode* ExistingNode : Graph->Nodes)
	{
		if (ExistingNode && ExistingNode->NodeGuid == SeededGuid)
		{
			Result.bSuccess = true;
			Result.bSkipped = true;
			Result.NodeGuid = SeededGuid;
			return Result;
		}
	}

	// Deterministic object name — matches the M28.3.x family. MacroGraph's
	// short name (e.g. "ForEachLoop") in the slot rather than the full path
	// to keep FName lengths reasonable; full path is in the seed.
	const FName NewNodeName(*FString::Printf(
		TEXT("BpxMacro_%s_%d_%d"), *MacroGraph->GetName(), PosX, PosY));
	UK2Node_MacroInstance* NewNode = NewObject<UK2Node_MacroInstance>(Graph, NewNodeName);

	// MacroGraphReference must be set BEFORE AllocateDefaultPins — the
	// inherited UK2Node_Tunnel pin walk reads the macro's Tunnel/Result
	// nodes from MacroGraphReference to mirror them onto the instance.
	// Post-alloc set leaves the node with zero pins.
	NewNode->SetMacroGraph(MacroGraph);

	Graph->AddNode(NewNode, /*bUserAction*/ false, /*bSelectNewNode*/ false);
	NewNode->NodeGuid = SeededGuid;
	NewNode->NodePosX = PosX;
	NewNode->NodePosY = PosY;
	NewNode->PostPlacedNewNode();
	NewNode->AllocateDefaultPins();

	// Seed pin GUIDs AFTER AllocateDefaultPins so the mirrored Tunnel/Result
	// pins (whose count + names depend on the macro's signature) get
	// deterministic PinIds.
	BpxReflection::SeedPinGuidsForNode(NewNode, JoinedPrefix);

	Result.bSuccess = true;
	Result.NodeGuid = SeededGuid;
	return Result;
}

// --- M28.14 — struct-mutation node catalog (Make / Break / SetFields) ---

namespace BpxReflection
{
	// Shared scaffold for the M28.14 trio. Validates inputs, resolves the
	// target graph, and computes the seeded NodeGuid + idempotence walk.
	// Returns the resolved graph + seed prefix; on early-return paths the
	// out-Result already carries the appropriate error / skip state.
	template <typename TNodeClass>
	static TNodeClass* PrepStructNodeSpawn(
		UBlueprint* Blueprint,
		FName GraphName,
		UScriptStruct* StructType,
		const FString& SeedKindToken, // e.g. "make_struct"
		const FString& ExtraSeedSuffix, // sorted-fields blob for SetFields, "" for Make/Break
		const FString& ObjectNamePrefix, // e.g. "BpxMake"
		FVector2D Position,
		FBpxNodeResult& Result,
		FString& OutJoinedPrefix,
		FGuid& OutSeededGuid,
		bool& bOutSkipped)
	{
		bOutSkipped = false;

		if (!Blueprint)
		{
			Result.ErrorMessage = TEXT("Blueprint is null");
			return nullptr;
		}
		if (GraphName.IsNone())
		{
			Result.ErrorMessage = TEXT("GraphName is empty");
			return nullptr;
		}
		if (!StructType)
		{
			Result.ErrorMessage = TEXT("StructType is null — Make/Break/SetFields requires a concrete UScriptStruct");
			return nullptr;
		}

		UEdGraph* Graph = BpxReflection::FindFunctionGraphByName(Blueprint, GraphName);
		if (!Graph)
		{
			Result.ErrorMessage = FString::Printf(
				TEXT("No graph named '%s' on '%s' (checked FunctionGraphs / ImplementedInterfaces / UbergraphPages)"),
				*GraphName.ToString(), *Blueprint->GetPathName());
			return nullptr;
		}

		const int32 PosX = static_cast<int32>(Position.X);
		const int32 PosY = static_cast<int32>(Position.Y);

		OutJoinedPrefix = Blueprint->GetPathName()
			+ TEXT(":graph:") + GraphName.ToString()
			+ TEXT(":") + SeedKindToken + TEXT(":") + StructType->GetPathName()
			+ ExtraSeedSuffix
			+ TEXT(":") + FString::FromInt(PosX) + TEXT(",") + FString::FromInt(PosY);
		OutSeededGuid = BpxReflection::SeedGuidFromJoined(OutJoinedPrefix);

		for (UEdGraphNode* ExistingNode : Graph->Nodes)
		{
			if (ExistingNode && ExistingNode->NodeGuid == OutSeededGuid)
			{
				Result.bSuccess = true;
				Result.bSkipped = true;
				Result.NodeGuid = OutSeededGuid;
				bOutSkipped = true;
				return nullptr;
			}
		}

		const FName NewNodeName(*FString::Printf(
			TEXT("%s_%s_%d_%d"), *ObjectNamePrefix, *StructType->GetName(), PosX, PosY));
		TNodeClass* NewNode = NewObject<TNodeClass>(Graph, NewNodeName);
		NewNode->StructType = StructType;
		NewNode->bMadeAfterOverridePinRemoval = true;

		Graph->AddNode(NewNode, /*bUserAction*/ false, /*bSelectNewNode*/ false);
		NewNode->NodeGuid = OutSeededGuid;
		NewNode->NodePosX = PosX;
		NewNode->NodePosY = PosY;
		NewNode->PostPlacedNewNode();
		NewNode->AllocateDefaultPins();

		return NewNode;
	}
}

FBpxNodeResult UBpxReflectionOps::AddMakeStructNode(
	UBlueprint* Blueprint, FName GraphName, UScriptStruct* StructType, FVector2D Position)
{
	FBpxNodeResult Result;

	FString JoinedPrefix;
	FGuid SeededGuid;
	bool bSkipped = false;
	UK2Node_MakeStruct* NewNode = BpxReflection::PrepStructNodeSpawn<UK2Node_MakeStruct>(
		Blueprint, GraphName, StructType,
		TEXT("make_struct"), TEXT(""), TEXT("BpxMake"),
		Position, Result, JoinedPrefix, SeededGuid, bSkipped);

	if (!NewNode)
	{
		// Either error or idempotent skip — Result is already populated.
		return Result;
	}

	BpxReflection::SeedPinGuidsForNode(NewNode, JoinedPrefix);

	Result.bSuccess = true;
	Result.NodeGuid = SeededGuid;
	return Result;
}

FBpxNodeResult UBpxReflectionOps::AddBreakStructNode(
	UBlueprint* Blueprint, FName GraphName, UScriptStruct* StructType, FVector2D Position)
{
	FBpxNodeResult Result;

	FString JoinedPrefix;
	FGuid SeededGuid;
	bool bSkipped = false;
	UK2Node_BreakStruct* NewNode = BpxReflection::PrepStructNodeSpawn<UK2Node_BreakStruct>(
		Blueprint, GraphName, StructType,
		TEXT("break_struct"), TEXT(""), TEXT("BpxBreak"),
		Position, Result, JoinedPrefix, SeededGuid, bSkipped);

	if (!NewNode)
	{
		return Result;
	}

	BpxReflection::SeedPinGuidsForNode(NewNode, JoinedPrefix);

	Result.bSuccess = true;
	Result.NodeGuid = SeededGuid;
	return Result;
}

FBpxNodeResult UBpxReflectionOps::AddSetFieldsInStructNode(
	UBlueprint* Blueprint, FName GraphName, UScriptStruct* StructType,
	const TArray<FName>& FieldsToShow, FVector2D Position)
{
	FBpxNodeResult Result;

	if (FieldsToShow.Num() == 0)
	{
		Result.ErrorMessage = TEXT(
			"FieldsToShow is empty — UK2Node_SetFieldsInStruct defaults bShowPin=false "
			"for every field, so an empty list produces a node with no usable input pins. "
			"Pass at least one field name from the struct.");
		return Result;
	}

	// Pre-validate every name resolves to a property on StructType. Silent
	// no-op on a typo would be a foot-gun (the user expects a settable pin
	// and gets a no-op compile).
	if (StructType)
	{
		TSet<FName> StructFieldNames;
		for (TFieldIterator<FProperty> PropIt(StructType, EFieldIteratorFlags::IncludeSuper); PropIt; ++PropIt)
		{
			StructFieldNames.Add(PropIt->GetFName());
		}
		TArray<FName> Unknown;
		for (const FName& Field : FieldsToShow)
		{
			if (!StructFieldNames.Contains(Field))
			{
				Unknown.Add(Field);
			}
		}
		if (Unknown.Num() > 0)
		{
			TArray<FString> UnknownStrs;
			for (const FName& U : Unknown) { UnknownStrs.Add(U.ToString()); }
			Result.ErrorMessage = FString::Printf(
				TEXT("FieldsToShow contains names not present on struct '%s': [%s]. "
					 "Check spelling — UScriptStruct UPROPERTY names are case-sensitive."),
				*StructType->GetPathName(), *FString::Join(UnknownStrs, TEXT(", ")));
			return Result;
		}
	}

	// Sort-and-join the field set for the seed key so caller-side ordering
	// doesn't drift the NodeGuid across replays. Use a copy to keep the
	// caller's TArray untouched.
	TArray<FName> SortedFields = FieldsToShow;
	SortedFields.Sort(FNameLexicalLess());
	TArray<FString> SortedFieldStrs;
	for (const FName& F : SortedFields) { SortedFieldStrs.Add(F.ToString()); }
	const FString FieldsSuffix = TEXT(":fields:") + FString::Join(SortedFieldStrs, TEXT(","));

	FString JoinedPrefix;
	FGuid SeededGuid;
	bool bSkipped = false;
	UK2Node_SetFieldsInStruct* NewNode = BpxReflection::PrepStructNodeSpawn<UK2Node_SetFieldsInStruct>(
		Blueprint, GraphName, StructType,
		TEXT("set_fields_in_struct"), FieldsSuffix, TEXT("BpxSetFields"),
		Position, Result, JoinedPrefix, SeededGuid, bSkipped);

	if (!NewNode)
	{
		return Result;
	}

	// SetFieldsInStruct's pin manager defaults bShowPin=false for every
	// field (K2Node_SetFieldsInStruct.cpp:400). Walk ShowPinForProperties,
	// flip bShowPin=true for entries the caller asked for, then ReconstructNode
	// to re-run AllocateDefaultPins. RebuildPropertyList preserves bShowPin
	// overrides via its old-settings cache (K2Node.cpp:1722-1817), so the
	// reconstruct emits the requested per-field input pins.
	TSet<FName> RequestedFields(FieldsToShow);
	for (FOptionalPinFromProperty& Entry : NewNode->ShowPinForProperties)
	{
		Entry.bShowPin = RequestedFields.Contains(Entry.PropertyName);
	}
	NewNode->ReconstructNode();

	// Seed pin GUIDs AFTER ReconstructNode so the final pin set (struct in,
	// struct out, exec in/out, plus the requested per-field inputs) all get
	// deterministic PinIds.
	BpxReflection::SeedPinGuidsForNode(NewNode, JoinedPrefix);

	Result.bSuccess = true;
	Result.NodeGuid = SeededGuid;
	return Result;
}

// --- M28.5.1 — EQS option add ---

FBpxReflectionResult UBpxReflectionOps::AddEnvQueryOption(
	UEnvQuery* Query, UClass* GeneratorClass)
{
	FBpxReflectionResult Result;

	if (!Query)
	{
		Result.ErrorMessage = TEXT("Query is null");
		return Result;
	}
	if (!GeneratorClass)
	{
		Result.ErrorMessage = TEXT("GeneratorClass is null");
		return Result;
	}
	if (!GeneratorClass->IsChildOf(UEnvQueryGenerator::StaticClass()))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("GeneratorClass '%s' is not a subclass of UEnvQueryGenerator"),
			*GeneratorClass->GetPathName());
		return Result;
	}
	if (GeneratorClass->HasAnyClassFlags(CLASS_Abstract))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("GeneratorClass '%s' is abstract — pass a concrete subclass "
				"(e.g. EnvQueryGenerator_ActorsOfClass)"),
			*GeneratorClass->GetPathName());
		return Result;
	}

	TArray<TObjectPtr<UEnvQueryOption>>& Options = Query->GetOptionsMutable();
	const int32 PreCount = Options.Num();

	// Idempotency pre-check — walk existing options and match by generator
	// class. M28.5.0 research notes the canonical editor pattern is a single
	// generator per option; duplicate-class detection here is the
	// "`add_eqs_option` replay is a no-op" contract. Plan authors still tune
	// per-UPROPERTY values via `SetPropertyValue` on a path like
	// `["Options", "[N]", "Generator", "..."]` without re-triggering create.
	for (int32 i = 0; i < Options.Num(); ++i)
	{
		const UEnvQueryOption* Opt = Options[i];
		if (Opt && Opt->Generator && Opt->Generator->GetClass() == GeneratorClass)
		{
			Result.bSuccess = true;
			Result.bSkipped = true;
			Result.BeforeText = FString::Printf(TEXT("options=%d"), PreCount);
			Result.AfterText = FString::Printf(TEXT("%d"), i);
			return Result;
		}
	}

	// Determinism: explicit FName on each NewObject. Zero FGuid usage across
	// EQS classes (grep-confirmed M28.5.0) so NewObject default-name counter-
	// suffixing is the only drift source. Pattern:
	//   BpxEqsOption_<pre_count>
	//   BpxEqsGen_<pre_count>_<GeneratorClassShortName>
	// Generator name includes the class short-name so soak round 2 with the
	// same generator class but a different option index stays distinct in the
	// package's FName table (future M28.5.2 where two options can carry the
	// same generator class).
	const FName OptionName(*FString::Printf(TEXT("BpxEqsOption_%d"), PreCount));
	UEnvQueryOption* NewOption = NewObject<UEnvQueryOption>(
		Query, OptionName, RF_Transactional);
	if (!NewOption)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("NewObject<UEnvQueryOption>(Query='%s', Name='%s') returned null"),
			*Query->GetPathName(), *OptionName.ToString());
		return Result;
	}

	const FName GeneratorName(*FString::Printf(
		TEXT("BpxEqsGen_%d_%s"), PreCount, *GeneratorClass->GetName()));
	UEnvQueryGenerator* NewGenerator = NewObject<UEnvQueryGenerator>(
		NewOption, GeneratorClass, GeneratorName, RF_Transactional);
	if (!NewGenerator)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("NewObject<UEnvQueryGenerator>(Class='%s', Name='%s') returned null"),
			*GeneratorClass->GetPathName(), *GeneratorName.ToString());
		return Result;
	}

	NewOption->Generator = NewGenerator;
	Options.Add(NewOption);

	// Mark package dirty so CompileAndSavePackage picks up the mutation.
	// EnvQuery is not a Blueprint; CompileAndSavePackage will skip the compile
	// step and go straight to SavePackage, which needs the dirty flag.
	if (UPackage* Pkg = Query->GetPackage())
	{
		Pkg->SetDirtyFlag(true);
	}

	Result.bSuccess = true;
	Result.BeforeText = FString::Printf(TEXT("options=%d"), PreCount);
	Result.AfterText = FString::Printf(TEXT("%d"), PreCount);
	return Result;
}

// --- M28.5.2 — EQS test add / remove ---

FBpxReflectionResult UBpxReflectionOps::AddEnvQueryTest(
	UEnvQuery* Query, int32 OptionIndex, UClass* TestClass)
{
	FBpxReflectionResult Result;

	if (!Query)
	{
		Result.ErrorMessage = TEXT("Query is null");
		return Result;
	}
	if (!TestClass)
	{
		Result.ErrorMessage = TEXT("TestClass is null");
		return Result;
	}
	if (!TestClass->IsChildOf(UEnvQueryTest::StaticClass()))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("TestClass '%s' is not a subclass of UEnvQueryTest"),
			*TestClass->GetPathName());
		return Result;
	}
	if (TestClass->HasAnyClassFlags(CLASS_Abstract))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("TestClass '%s' is abstract — pass a concrete subclass "
				"(e.g. EnvQueryTest_Random)"),
			*TestClass->GetPathName());
		return Result;
	}

	TArray<TObjectPtr<UEnvQueryOption>>& Options = Query->GetOptionsMutable();
	if (!Options.IsValidIndex(OptionIndex))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("OptionIndex %d is out of range [0, %d)"),
			OptionIndex, Options.Num());
		return Result;
	}

	UEnvQueryOption* Option = Options[OptionIndex];
	if (!Option)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Options[%d] is null"), OptionIndex);
		return Result;
	}

	const int32 PreCount = Option->Tests.Num();

	// Idempotency pre-check — exact-class match in existing Tests[]. Per-
	// UPROPERTY tuning stays on SetPropertyValue against a
	// ["Options", "[N]", "Tests", "[M]", ...] path without re-triggering
	// create.
	for (int32 i = 0; i < Option->Tests.Num(); ++i)
	{
		const UEnvQueryTest* Existing = Option->Tests[i];
		if (Existing && Existing->GetClass() == TestClass)
		{
			Result.bSuccess = true;
			Result.bSkipped = true;
			Result.BeforeText = FString::Printf(TEXT("tests=%d"), PreCount);
			Result.AfterText = FString::Printf(TEXT("%d"), i);
			return Result;
		}
	}

	// Determinism: explicit FName on NewObject. Name includes both option
	// index and pre-insert test count so two options carrying the same
	// test class don't collide in the package's FName table.
	const FName TestName(*FString::Printf(
		TEXT("BpxEqsTest_%d_%d_%s"),
		OptionIndex, PreCount, *TestClass->GetName()));

	UEnvQueryTest* NewTest = NewObject<UEnvQueryTest>(
		Option, TestClass, TestName, RF_Transactional);
	if (!NewTest)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("NewObject<UEnvQueryTest>(Class='%s', Name='%s') returned null"),
			*TestClass->GetPathName(), *TestName.ToString());
		return Result;
	}

	// TestOrder invariant: EnvQueryManager.cpp:874 runtime repair only fires
	// on zero; editor must assign sequentially. RemoveEnvQueryTest preserves
	// the 0..N-1 invariant by reseating the tail.
	NewTest->TestOrder = PreCount;
	Option->Tests.Add(NewTest);

	if (UPackage* Pkg = Query->GetPackage())
	{
		Pkg->SetDirtyFlag(true);
	}

	Result.bSuccess = true;
	Result.BeforeText = FString::Printf(TEXT("tests=%d"), PreCount);
	Result.AfterText = FString::Printf(TEXT("%d"), PreCount);
	return Result;
}

FBpxReflectionResult UBpxReflectionOps::RemoveEnvQueryTest(
	UEnvQuery* Query, int32 OptionIndex, int32 TestIndex)
{
	FBpxReflectionResult Result;

	if (!Query)
	{
		Result.ErrorMessage = TEXT("Query is null");
		return Result;
	}

	TArray<TObjectPtr<UEnvQueryOption>>& Options = Query->GetOptionsMutable();
	if (!Options.IsValidIndex(OptionIndex))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("OptionIndex %d is out of range [0, %d)"),
			OptionIndex, Options.Num());
		return Result;
	}

	UEnvQueryOption* Option = Options[OptionIndex];
	if (!Option)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Options[%d] is null"), OptionIndex);
		return Result;
	}

	const int32 PreCount = Option->Tests.Num();

	// Idempotency: out-of-range TestIndex is treated as "already removed"
	// rather than an error. Supports soak-harness replay where round 1
	// succeeds and round 2 sees the post-mutation state. Also guards
	// against a re-apply of a successful plan without the caller having
	// to re-resolve indices. Negative indices are still hard errors —
	// the Python wrapper rejects those up-front.
	if (!Option->Tests.IsValidIndex(TestIndex))
	{
		Result.bSuccess = true;
		Result.bSkipped = true;
		Result.BeforeText = FString::Printf(TEXT("tests=%d"), PreCount);
		Result.AfterText = FString::Printf(TEXT("already-removed:%d"), TestIndex);
		return Result;
	}

	Option->Tests.RemoveAt(TestIndex);

	// Reseat TestOrder on every subsequent test. The array index IS the
	// post-remove order; the runtime doesn't repair non-zero values so the
	// editor must keep the 0..N-1 invariant explicitly.
	for (int32 i = TestIndex; i < Option->Tests.Num(); ++i)
	{
		if (UEnvQueryTest* T = Option->Tests[i])
		{
			T->TestOrder = i;
		}
	}

	if (UPackage* Pkg = Query->GetPackage())
	{
		Pkg->SetDirtyFlag(true);
	}

	Result.bSuccess = true;
	Result.BeforeText = FString::Printf(TEXT("tests=%d"), PreCount);
	Result.AfterText = FString::Printf(TEXT("removed-index:%d"), TestIndex);
	return Result;
}

// --- M28.4.1 — CurveFloat authoring ---

FBpxReflectionResult UBpxReflectionOps::CreateCurveFloatDeterministic(
	const FString& PackagePath)
{
	FBpxReflectionResult Result;

	if (PackagePath.IsEmpty() || !PackagePath.StartsWith(TEXT("/Game/")))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("PackagePath must start with /Game/ (got '%s')"), *PackagePath);
		return Result;
	}

	// Idempotence — if a UCurveFloat already exists at this path, skip.
	// StaticLoadObject finds both on-disk and in-memory-only objects; LOAD_NoWarn
	// + LOAD_Quiet suppress the "failed to load" noise on the negative path
	// (which is the expected case for a fresh create).
	UObject* Existing = StaticLoadObject(
		UCurveFloat::StaticClass(), nullptr, *PackagePath, nullptr,
		LOAD_NoWarn | LOAD_Quiet);
	if (Existing)
	{
		Result.bSuccess = true;
		Result.bSkipped = true;
		Result.BeforeText = TEXT("curve-exists");
		Result.AfterText = PackagePath;
		return Result;
	}

	// Different-class collision — a non-curve asset occupies the path.
	// Surface as a structured error rather than silently creating the curve
	// alongside or skipping, since the plan author has a target mismatch.
	if (FPackageName::DoesPackageExist(PackagePath))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Package exists at '%s' but is not a UCurveFloat"), *PackagePath);
		return Result;
	}

	UPackage* Pkg = CreatePackage(*PackagePath);
	if (!Pkg)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("CreatePackage returned null for '%s'"), *PackagePath);
		return Result;
	}
	Pkg->FullyLoad();

	// Short name is the last segment of the /Game/ path — same as the
	// fixture-gen pattern in GenerateTestBlueprintsCommandlet's
	// ShortNameFromPath helper. Explicit FName on NewObject keeps the
	// asset's FName stable across replays; UCurveFloat has no FGuid fields
	// so this is the only determinism lever.
	const FString ShortName = FPackageName::GetShortName(PackagePath);
	UCurveFloat* Curve = NewObject<UCurveFloat>(
		Pkg, FName(*ShortName), RF_Public | RF_Standalone);
	if (!Curve)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("NewObject<UCurveFloat>(Pkg='%s', Name='%s') returned null"),
			*PackagePath, *ShortName);
		return Result;
	}

	FAssetRegistryModule::AssetCreated(Curve);
	Pkg->SetDirtyFlag(true);

	Result.bSuccess = true;
	Result.BeforeText = TEXT("no-curve");
	Result.AfterText = PackagePath;
	return Result;
}

FBpxReflectionResult UBpxReflectionOps::SetCurveFloatKeys(
	UCurveFloat* Curve, const TArray<FRichCurveKey>& NewKeys)
{
	FBpxReflectionResult Result;

	if (!Curve)
	{
		Result.ErrorMessage = TEXT("Curve is null");
		return Result;
	}

	// Monotonic (non-strict) Time ordering is a FRichCurve::Evaluate
	// invariant. UE's API has a separate Sort() call but SetKeys does NOT
	// re-sort — unsorted input would silently break runtime sampling.
	// Reject up-front with a structured error so plan replay is crisp.
	for (int32 i = 1; i < NewKeys.Num(); ++i)
	{
		if (NewKeys[i].Time < NewKeys[i - 1].Time)
		{
			Result.ErrorMessage = FString::Printf(
				TEXT("Keys must be sorted by Time ascending; "
					 "NewKeys[%d].Time=%f < NewKeys[%d].Time=%f"),
				i, NewKeys[i].Time, i - 1, NewKeys[i - 1].Time);
			return Result;
		}
	}

	// Idempotence — element-wise compare Time / Value / InterpMode against
	// the existing key array. Tangent fields excluded from the compare
	// because the M28.4.1 Python surface only accepts Time + Value, so any
	// tangent drift between rounds would be engine-computed rather than
	// plan-driven.
	const TArray<FRichCurveKey> Existing = Curve->FloatCurve.GetCopyOfKeys();
	const int32 PreCount = Existing.Num();
	bool bIdentical = (Existing.Num() == NewKeys.Num());
	if (bIdentical)
	{
		for (int32 i = 0; i < NewKeys.Num(); ++i)
		{
			if (Existing[i].Time != NewKeys[i].Time
				|| Existing[i].Value != NewKeys[i].Value
				|| Existing[i].InterpMode != NewKeys[i].InterpMode)
			{
				bIdentical = false;
				break;
			}
		}
	}
	if (bIdentical)
	{
		Result.bSuccess = true;
		Result.bSkipped = true;
		Result.BeforeText = FString::Printf(TEXT("keys=%d"), PreCount);
		Result.AfterText = FString::Printf(TEXT("keys=%d"), NewKeys.Num());
		return Result;
	}

	Curve->FloatCurve.SetKeys(NewKeys);

	if (UPackage* Pkg = Curve->GetPackage())
	{
		Pkg->SetDirtyFlag(true);
	}

	Result.bSuccess = true;
	Result.BeforeText = FString::Printf(TEXT("keys=%d"), PreCount);
	Result.AfterText = FString::Printf(TEXT("keys=%d"), NewKeys.Num());
	return Result;
}

FBpxReflectionResult UBpxReflectionOps::CreateDataAssetInstanceDeterministic(
	const FString& PackagePath, UClass* DAClass)
{
	FBpxReflectionResult Result;

	if (PackagePath.IsEmpty() || !PackagePath.StartsWith(TEXT("/Game/")))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("PackagePath must start with /Game/ (got '%s')"), *PackagePath);
		return Result;
	}
	if (!DAClass)
	{
		Result.ErrorMessage = TEXT("DAClass is null");
		return Result;
	}
	if (!DAClass->IsChildOf(UDataAsset::StaticClass()))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("DAClass '%s' is not a subclass of UDataAsset"),
			*DAClass->GetPathName());
		return Result;
	}
	if (DAClass->HasAnyClassFlags(CLASS_Abstract))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("DAClass '%s' is abstract — pass a concrete subclass "
				"(or a BP-derived DA class's GeneratedClass)"),
			*DAClass->GetPathName());
		return Result;
	}

	// Idempotence — StaticLoadObject with the concrete UDataAsset base finds
	// both on-disk and in-memory objects. LOAD_NoWarn + LOAD_Quiet suppress
	// the "failed to load" noise on the negative path (expected for a fresh
	// create). Class-match check handles the wrong-class-at-this-path case.
	UObject* Existing = StaticLoadObject(
		UDataAsset::StaticClass(), nullptr, *PackagePath, nullptr,
		LOAD_NoWarn | LOAD_Quiet);
	if (Existing)
	{
		if (Existing->GetClass() == DAClass)
		{
			Result.bSuccess = true;
			Result.bSkipped = true;
			Result.BeforeText = TEXT("asset-exists");
			Result.AfterText = PackagePath;
			return Result;
		}
		Result.ErrorMessage = FString::Printf(
			TEXT("Asset exists at '%s' but is class '%s', expected '%s'"),
			*PackagePath, *Existing->GetClass()->GetPathName(),
			*DAClass->GetPathName());
		return Result;
	}

	// Different-class collision — a non-DataAsset asset occupies the path.
	// Surface as a structured error rather than silently stacking.
	if (FPackageName::DoesPackageExist(PackagePath))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Package exists at '%s' but is not a UDataAsset"), *PackagePath);
		return Result;
	}

	UPackage* Pkg = CreatePackage(*PackagePath);
	if (!Pkg)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("CreatePackage returned null for '%s'"), *PackagePath);
		return Result;
	}
	Pkg->FullyLoad();

	// Explicit FName on NewObject keeps the asset's FName stable across
	// replays. UDataAsset has no FGuid fields per M28.4.0 research, so this
	// is the only determinism lever. Flags mirror UDataAssetFactory's
	// FactoryCreateNew (EditorFactories.cpp:7288) to match what the
	// interactive editor path would produce.
	const FString ShortName = FPackageName::GetShortName(PackagePath);
	UDataAsset* Asset = NewObject<UDataAsset>(
		Pkg, DAClass, FName(*ShortName),
		RF_Public | RF_Standalone | RF_Transactional);
	if (!Asset)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("NewObject<UDataAsset>(Pkg='%s', Class='%s', Name='%s') returned null"),
			*PackagePath, *DAClass->GetPathName(), *ShortName);
		return Result;
	}

	FAssetRegistryModule::AssetCreated(Asset);
	Pkg->SetDirtyFlag(true);

	Result.bSuccess = true;
	Result.BeforeText = TEXT("no-asset");
	Result.AfterText = PackagePath;
	return Result;
}

// --- M28.4.3 — UserDefinedStruct authoring ---

namespace BpxReflection
{
	/** Resolve a FriendlyName → matching FStructVariableDescription* on a UDS.
	 *  Returns nullptr if no match. Walks the FStructureEditorUtils-exposed
	 *  VariablesDescriptions array on the UUserDefinedStructEditorData inner
	 *  subobject.
	 *
	 *  Friendly-name matching is case-sensitive and exact. `FName` on the
	 *  Python-side always serializes case-insensitively (UE's FName collapsing),
	 *  but `FriendlyName` is an FString stored verbatim — matches the authored
	 *  spelling in the struct editor UI. Plan authors should use the canonical
	 *  casing they saw in the UDS. */
	static FStructVariableDescription* FindUdsVarDescByFriendlyName(
		UUserDefinedStruct* Struct, const FString& FriendlyName)
	{
		if (!Struct || FriendlyName.IsEmpty())
		{
			return nullptr;
		}
		TArray<FStructVariableDescription>& VarDescs =
			FStructureEditorUtils::GetVarDesc(Struct);
		for (FStructVariableDescription& Desc : VarDescs)
		{
			if (Desc.FriendlyName == FriendlyName)
			{
				return &Desc;
			}
		}
		return nullptr;
	}
} // namespace BpxReflection

FBpxReflectionResult UBpxReflectionOps::CreateUserDefinedStructDeterministic(
	const FString& PackagePath)
{
	FBpxReflectionResult Result;

	if (PackagePath.IsEmpty() || !PackagePath.StartsWith(TEXT("/Game/")))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("PackagePath must start with /Game/ (got '%s')"), *PackagePath);
		return Result;
	}

	// Idempotence — StaticLoadObject on UUserDefinedStruct finds both on-disk
	// and in-memory-only objects. Class-exact skip: matches the M28.4.1 /
	// M28.4.2 idempotence shape; plan authors chain AddUserDefinedStructMember
	// ops to grow the struct rather than re-running create.
	UObject* Existing = StaticLoadObject(
		UUserDefinedStruct::StaticClass(), nullptr, *PackagePath, nullptr,
		LOAD_NoWarn | LOAD_Quiet);
	if (Existing)
	{
		Result.bSuccess = true;
		Result.bSkipped = true;
		Result.BeforeText = TEXT("uds-exists");
		Result.AfterText = PackagePath;
		return Result;
	}

	// Different-class collision — structured error; silent stacking alongside
	// would break determinism + confuse the plan author.
	if (FPackageName::DoesPackageExist(PackagePath))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Package exists at '%s' but is not a UUserDefinedStruct"), *PackagePath);
		return Result;
	}

	UPackage* Pkg = CreatePackage(*PackagePath);
	if (!Pkg)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("CreatePackage returned null for '%s'"), *PackagePath);
		return Result;
	}
	Pkg->FullyLoad();

	// CreateUserDefinedStruct does:
	//   1. NewObject<UUserDefinedStruct>(Pkg, Name, Flags)
	//   2. NewObject<UUserDefinedStructEditorData>(Struct, ...)
	//   3. Struct->Guid = FGuid::NewGuid()           <-- determinism trap #1
	//   4. AddVariable(Struct, FEdGraphPinType(Boolean))
	//       -> VarGuid = FGuid::NewGuid()            <-- determinism trap #2
	//       -> VarName derived from VarGuid via FMemberVariableNameHelper
	const FString ShortName = FPackageName::GetShortName(PackagePath);
	UUserDefinedStruct* UDS = FStructureEditorUtils::CreateUserDefinedStruct(
		Pkg, FName(*ShortName), RF_Public | RF_Standalone | RF_Transactional);
	if (!UDS)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("FStructureEditorUtils::CreateUserDefinedStruct(Pkg='%s', Name='%s') returned null"),
			*PackagePath, *ShortName);
		return Result;
	}

	// Close trap #1 — overwrite the random Struct->Guid with a deterministic
	// md5 seed. Struct->Guid is serialized into the .uasset; drift here would
	// trip M28.pre.3 soak round 2 immediately.
	UDS->Guid = BpxReflection::SeedGuidFromJoined(PackagePath + TEXT(":uds"));

	// Close trap #2 — rename the auto-bool to "BpxAutoBool" with a seeded
	// VarGuid. RenameVariable regenerates VarName from (seeded Guid +
	// new friendly name) via FMemberVariableNameHelper::Generate and triggers
	// OnStructureChanged(RenamedVariable) which rebuilds the FProperty chain.
	// The auto-bool stays in the struct because RemoveVariable refuses to
	// empty it (bAllowToMakeEmpty=false, StructureEditorUtils.cpp:327); plan
	// authors remove it later via RemoveUserDefinedStructMember once at least
	// one real member is added.
	TArray<FStructVariableDescription>& VarDescs =
		FStructureEditorUtils::GetVarDesc(UDS);
	if (VarDescs.Num() == 1)
	{
		const FString NewFriendly = TEXT("BpxAutoBool");
		const FGuid SeededVarGuid = BpxReflection::SeedGuidFromJoined(
			PackagePath + TEXT(":uds_var:") + NewFriendly);
		VarDescs[0].VarGuid = SeededVarGuid;
		// RenameVariable takes the seeded VarGuid + the new friendly name,
		// regenerates VarName, and fires OnStructureChanged.
		FStructureEditorUtils::RenameVariable(UDS, SeededVarGuid, NewFriendly);
	}

	FAssetRegistryModule::AssetCreated(UDS);
	Pkg->SetDirtyFlag(true);

	Result.bSuccess = true;
	Result.BeforeText = TEXT("no-uds");
	Result.AfterText = PackagePath;
	return Result;
}

FBpxReflectionResult UBpxReflectionOps::AddUserDefinedStructMember(
	UUserDefinedStruct* Struct, FName FriendlyName,
	const FEdGraphPinType& VarType, const FString& DefaultValue)
{
	FBpxReflectionResult Result;

	if (!Struct)
	{
		Result.ErrorMessage = TEXT("Struct is null");
		return Result;
	}
	if (FriendlyName.IsNone())
	{
		Result.ErrorMessage = TEXT("FriendlyName is empty");
		return Result;
	}

	const FString FriendlyStr = FriendlyName.ToString();

	// Idempotence — match by friendly name on VarDescriptions. VarGuid stays
	// untouched on skip so the seed recipe remains deterministic across replays.
	if (BpxReflection::FindUdsVarDescByFriendlyName(Struct, FriendlyStr))
	{
		Result.bSuccess = true;
		Result.bSkipped = true;
		Result.BeforeText = FString::Printf(TEXT("member-exists:%s"), *FriendlyStr);
		Result.AfterText = Result.BeforeText;
		return Result;
	}

	// Capture the pre-add count so we can locate the tail entry deterministically.
	// AddVariable appends; no other caller runs concurrently on the game thread.
	TArray<FStructVariableDescription>& VarDescs =
		FStructureEditorUtils::GetVarDesc(Struct);
	const int32 PreCount = VarDescs.Num();

	const bool bAdded = FStructureEditorUtils::AddVariable(Struct, VarType);
	if (!bAdded)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("FStructureEditorUtils::AddVariable returned false on '%s' for friendly='%s' "
				 "(typically means the VarType is invalid for a UDS member — check pin category)"),
			*Struct->GetPathName(), *FriendlyStr);
		return Result;
	}

	// VarDescs is a live reference, so Num() is now PreCount+1. The new entry
	// is at index PreCount. Defensive: verify the shape AddVariable landed.
	if (VarDescs.Num() != PreCount + 1)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("AddVariable returned true but VarDescriptions.Num() is %d (expected %d) on '%s'"),
			VarDescs.Num(), PreCount + 1, *Struct->GetPathName());
		return Result;
	}

	FStructVariableDescription& NewEntry = VarDescs[PreCount];
	const FString SeedKey = Struct->GetPathName() + TEXT(":uds_var:") + FriendlyStr;
	const FGuid SeededVarGuid = BpxReflection::SeedGuidFromJoined(SeedKey);
	NewEntry.VarGuid = SeededVarGuid;

	// RenameVariable regenerates VarName from (SeededVarGuid + FriendlyStr) via
	// FMemberVariableNameHelper::Generate, sets FriendlyName = FriendlyStr, and
	// fires OnStructureChanged(RenamedVariable) which triggers CompileStruct.
	// Without this pass, VarName would still reflect the random pre-seed Guid
	// and drift M28.pre.3 soak round 2.
	if (!FStructureEditorUtils::RenameVariable(Struct, SeededVarGuid, FriendlyStr))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("FStructureEditorUtils::RenameVariable failed for friendly='%s' on '%s'"),
			*FriendlyStr, *Struct->GetPathName());
		return Result;
	}

	// Optional default value. ChangeVariableDefaultValue writes VarDesc.DefaultValue,
	// fires OnStructureChanged(DefaultValueChanged), and triggers
	// RecreateDefaultInstanceInEditorData so the DefaultInstance memory stays
	// in sync with the serialized string.
	if (!DefaultValue.IsEmpty())
	{
		if (!FStructureEditorUtils::ChangeVariableDefaultValue(
				Struct, SeededVarGuid, DefaultValue))
		{
			Result.ErrorMessage = FString::Printf(
				TEXT("ChangeVariableDefaultValue failed for friendly='%s' value='%s' on '%s'"),
				*FriendlyStr, *DefaultValue, *Struct->GetPathName());
			return Result;
		}
	}

	if (UPackage* Pkg = Struct->GetPackage())
	{
		Pkg->SetDirtyFlag(true);
	}

	Result.bSuccess = true;
	Result.BeforeText = TEXT("no-member");
	Result.AfterText = FString::Printf(TEXT("member-added:%s"), *FriendlyStr);
	return Result;
}

FBpxReflectionResult UBpxReflectionOps::RemoveUserDefinedStructMember(
	UUserDefinedStruct* Struct, FName FriendlyName)
{
	FBpxReflectionResult Result;

	if (!Struct)
	{
		Result.ErrorMessage = TEXT("Struct is null");
		return Result;
	}
	if (FriendlyName.IsNone())
	{
		Result.ErrorMessage = TEXT("FriendlyName is empty");
		return Result;
	}

	const FString FriendlyStr = FriendlyName.ToString();

	// Resolve FriendlyName → VarGuid via the friendly-name walk. Capture the
	// guid before calling RemoveVariable because the reference will be stale
	// after the array mutation.
	FStructVariableDescription* ExistingDesc =
		BpxReflection::FindUdsVarDescByFriendlyName(Struct, FriendlyStr);
	if (!ExistingDesc)
	{
		Result.bSuccess = true;
		Result.bSkipped = true;
		Result.BeforeText = FString::Printf(TEXT("no-member:%s"), *FriendlyStr);
		Result.AfterText = FString::Printf(TEXT("already-removed:%s"), *FriendlyStr);
		return Result;
	}

	const FGuid VarGuid = ExistingDesc->VarGuid;

	// Refuse to empty the struct — matches the engine's bAllowToMakeEmpty=false
	// invariant (StructureEditorUtils.cpp:327). `FStructureEditorUtils::
	// RemoveVariable` would return false silently in that case; we surface it
	// up-front with a clear structured error so plan authors know to add the
	// replacement member BEFORE removing the last existing one.
	TArray<FStructVariableDescription>& VarDescs =
		FStructureEditorUtils::GetVarDesc(Struct);
	const int32 PreCount = VarDescs.Num();
	if (PreCount <= 1)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Cannot remove last member '%s' from '%s' — UUserDefinedStruct must retain at least one variable (engine invariant: bAllowToMakeEmpty=false). Add the replacement member before removing this one."),
			*FriendlyStr, *Struct->GetPathName());
		return Result;
	}

	if (!FStructureEditorUtils::RemoveVariable(Struct, VarGuid))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("FStructureEditorUtils::RemoveVariable failed for friendly='%s' on '%s'"),
			*FriendlyStr, *Struct->GetPathName());
		return Result;
	}

	if (UPackage* Pkg = Struct->GetPackage())
	{
		Pkg->SetDirtyFlag(true);
	}

	Result.bSuccess = true;
	Result.BeforeText = FString::Printf(TEXT("members=%d"), PreCount);
	Result.AfterText = FString::Printf(TEXT("member-removed:%s"), *FriendlyStr);
	return Result;
}

FBpxReflectionResult UBpxReflectionOps::SetUserDefinedStructMemberDefault(
	UUserDefinedStruct* Struct, FName FriendlyName, const FString& DefaultValueStr)
{
	FBpxReflectionResult Result;

	if (!Struct)
	{
		Result.ErrorMessage = TEXT("Struct is null");
		return Result;
	}
	if (FriendlyName.IsNone())
	{
		Result.ErrorMessage = TEXT("FriendlyName is empty");
		return Result;
	}

	const FString FriendlyStr = FriendlyName.ToString();

	FStructVariableDescription* ExistingDesc =
		BpxReflection::FindUdsVarDescByFriendlyName(Struct, FriendlyStr);
	if (!ExistingDesc)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("No member named '%s' on '%s' — cannot set default value on a missing member (use add_uds_member first)"),
			*FriendlyStr, *Struct->GetPathName());
		return Result;
	}

	// Idempotent — compare existing DefaultValue string directly. Same value →
	// skip without firing listener events (which would dirty the asset
	// needlessly and churn the md5 on otherwise-stable replays).
	const FString PreDefault = ExistingDesc->DefaultValue;
	if (PreDefault == DefaultValueStr)
	{
		Result.bSuccess = true;
		Result.bSkipped = true;
		Result.BeforeText = PreDefault;
		Result.AfterText = PreDefault;
		return Result;
	}

	const FGuid VarGuid = ExistingDesc->VarGuid;
	if (!FStructureEditorUtils::ChangeVariableDefaultValue(
			Struct, VarGuid, DefaultValueStr))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("FStructureEditorUtils::ChangeVariableDefaultValue failed for friendly='%s' value='%s' on '%s' (most likely a pin-type / value-format mismatch — check the VarType of the target member)"),
			*FriendlyStr, *DefaultValueStr, *Struct->GetPathName());
		return Result;
	}

	if (UPackage* Pkg = Struct->GetPackage())
	{
		Pkg->SetDirtyFlag(true);
	}

	Result.bSuccess = true;
	Result.BeforeText = PreDefault;
	Result.AfterText = DefaultValueStr;
	return Result;
}

// =============================================================================
// M28.6.1 — GameplayTag config authoring
// =============================================================================

FBpxReflectionResult UBpxReflectionOps::AddGameplayTag(
	const FString& TagName,
	const FString& DevComment,
	FName SourceIni,
	bool bIsRestrictedTag)
{
	FBpxReflectionResult Result;

#if !WITH_GAMEPLAYTAGSEDITOR_SUPPORT
	Result.ErrorMessage = TEXT(
		"AddGameplayTag is unavailable: WITH_GAMEPLAYTAGSEDITOR_SUPPORT=0. "
		"The GameplayTagsEditor plugin is not enabled in this build. Enable "
		"the engine plugin and rebuild, or run from an editor build that "
		"includes it.");
	return Result;
#else
	if (TagName.IsEmpty())
	{
		Result.ErrorMessage = TEXT("TagName is empty");
		return Result;
	}

	// Engine API requires the editor module to be loaded. `IsAvailable` is
	// non-throwing; `Get` would force-load via FModuleManager and throw if
	// absent. Belt-and-braces — Build.cs gates the dep, but if the user
	// disables the plugin at runtime via the project settings the load can
	// still fail.
	if (!IGameplayTagsEditorModule::IsAvailable())
	{
		Result.ErrorMessage = TEXT(
			"IGameplayTagsEditorModule is not loaded. Ensure the "
			"GameplayTagsEditor plugin is enabled in the project's .uproject.");
		return Result;
	}

	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();

	// Idempotence pre-check. The engine's AddNewGameplayTagToINI returns
	// false on duplicate-add (with a "Failed to add gameplay tag X, already
	// exists!" toast — not visible to MCP callers). For soak round-2
	// byte-identity we need a real skip signal. Use IsDictionaryTag, which
	// returns true for any explicitly-registered tag in the in-memory tree.
	const FName TagFName(*TagName);
	if (Manager.IsDictionaryTag(TagFName))
	{
		// Resolve the source the existing tag lives in so the caller
		// learns where it landed (handy when SourceIni was NAME_None and
		// the developer-config diversion may have steered to a per-machine
		// ini on a prior run). GetTagEditorData populates source on the
		// editor side.
		FString ExistingComment;
		FName ExistingSource;
		bool bExistingExplicit = false;
		bool bExistingRestricted = false;
		bool bExistingAllowsNonRestrictedChildren = false;
		Manager.GetTagEditorData(
			TagFName, ExistingComment, ExistingSource, bExistingExplicit,
			bExistingRestricted, bExistingAllowsNonRestrictedChildren);

		Result.bSuccess = true;
		Result.bSkipped = true;
		Result.BeforeText = FString::Printf(
			TEXT("existing-in:%s"),
			ExistingSource.IsNone() ? TEXT("<unknown>") : *ExistingSource.ToString());
		// AfterText reports the resolved source ini even on skip, so the
		// caller can correlate "tag was already there" with the same source
		// it would have written to.
		Result.AfterText = ExistingSource.IsNone()
			? FString(TEXT("<unknown>"))
			: ExistingSource.ToString();
		return Result;
	}

	// Engine call. Hardcoded bAllowNonRestrictedChildren=true — the M28.6.1
	// op surface deliberately does not expose that knob (always true means
	// non-restricted descendants of a restricted tag are permitted, which
	// is the engine's sensible default). If a real driver surfaces, expose
	// in a follow-up M28.6.x.
	const bool bAdded = IGameplayTagsEditorModule::Get().AddNewGameplayTagToINI(
		TagName,
		DevComment,
		SourceIni,
		bIsRestrictedTag,
		/*bAllowNonRestrictedChildren=*/true);

	if (!bAdded)
	{
		// The engine API surfaces the actual failure reason (invalid string,
		// restricted-tag rule violation, etc.) via Slate notifications which
		// MCP callers can't see. Best we can do is point at the editor log.
		// Validate up-front via IsValidGameplayTagString to give a structured
		// error for the most common case (forbidden characters / structure).
		FText ValidationError;
		FString FixedString;
		if (!Manager.IsValidGameplayTagString(TagName, &ValidationError, &FixedString))
		{
			Result.ErrorMessage = FString::Printf(
				TEXT("AddNewGameplayTagToINI rejected tag '%s': %s. Try '%s' instead."),
				*TagName,
				*ValidationError.ToString(),
				*FixedString);
			return Result;
		}
		Result.ErrorMessage = FString::Printf(
			TEXT("AddNewGameplayTagToINI returned false for tag '%s' (source '%s', restricted=%s). "
				"Check the editor log for the engine-side reason — common causes are "
				"`ImportTagsFromConfig=False` on UGameplayTagsSettings or restricted-tag "
				"parent-chain violations."),
			*TagName,
			SourceIni.IsNone() ? TEXT("<default>") : *SourceIni.ToString(),
			bIsRestrictedTag ? TEXT("true") : TEXT("false"));
		return Result;
	}

	// Resolve the source the tag actually landed in. SourceIni may have been
	// NAME_None (engine substituted the default) or may have been diverted
	// to UGameplayTagsDeveloperSettings::DeveloperConfigName when a
	// per-machine override is set. Walk the post-write editor data to
	// surface the truth.
	FString PostComment;
	FName PostSource;
	bool bPostExplicit = false;
	bool bPostRestricted = false;
	bool bPostAllowsNonRestrictedChildren = false;
	Manager.GetTagEditorData(
		TagFName, PostComment, PostSource, bPostExplicit,
		bPostRestricted, bPostAllowsNonRestrictedChildren);

	Result.bSuccess = true;
	Result.BeforeText = TEXT("absent");
	Result.AfterText = PostSource.IsNone()
		? FString(TEXT("<unknown>"))
		: PostSource.ToString();
	return Result;
#endif
}

// --- M28.10.1 — Blueprint class authoring (native or BP parent) ---

FBpxReflectionResult UBpxReflectionOps::CreateBlueprintClassDeterministic(
	const FString& PackagePath, UClass* ParentClass)
{
	FBpxReflectionResult Result;

	if (PackagePath.IsEmpty() || !PackagePath.StartsWith(TEXT("/Game/")))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("PackagePath must start with /Game/ (got '%s')"), *PackagePath);
		return Result;
	}
	if (!ParentClass)
	{
		Result.ErrorMessage = TEXT("ParentClass is null");
		return Result;
	}
	if (!FKismetEditorUtilities::CanCreateBlueprintOfClass(ParentClass))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("ParentClass '%s' is not blueprintable "
				"(FKismetEditorUtilities::CanCreateBlueprintOfClass=false). "
				"Common causes: UInterface, classes with BlueprintType=NotBlueprintable, "
				"or engine-internal classes excluded from the New Blueprint picker."),
			*ParentClass->GetPathName());
		return Result;
	}

	// Idempotence — StaticLoadObject finds both on-disk and in-memory UBlueprints.
	// Class match is via ParentClass pointer equality: post-load both sides
	// resolve to the same UClass singleton. Stricter than create_child_bp's
	// existence-only check (CATALOG.md:1431 caveat).
	UObject* Existing = StaticLoadObject(
		UBlueprint::StaticClass(), nullptr, *PackagePath, nullptr,
		LOAD_NoWarn | LOAD_Quiet);
	if (Existing)
	{
		UBlueprint* ExistingBP = Cast<UBlueprint>(Existing);
		if (ExistingBP && ExistingBP->ParentClass == ParentClass)
		{
			Result.bSuccess = true;
			Result.bSkipped = true;
			Result.BeforeText = TEXT("bp-exists");
			Result.AfterText = PackagePath;
			return Result;
		}
		if (ExistingBP)
		{
			Result.ErrorMessage = FString::Printf(
				TEXT("Blueprint exists at '%s' with parent '%s', expected '%s'"),
				*PackagePath,
				ExistingBP->ParentClass ? *ExistingBP->ParentClass->GetPathName() : TEXT("<null>"),
				*ParentClass->GetPathName());
			return Result;
		}
		Result.ErrorMessage = FString::Printf(
			TEXT("Asset exists at '%s' but is class '%s', expected UBlueprint"),
			*PackagePath, *Existing->GetClass()->GetPathName());
		return Result;
	}

	// Different-class collision at the path — structured error.
	if (FPackageName::DoesPackageExist(PackagePath))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("Package exists at '%s' but is not a UBlueprint"), *PackagePath);
		return Result;
	}

	UPackage* Pkg = CreatePackage(*PackagePath);
	if (!Pkg)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("CreatePackage returned null for '%s'"), *PackagePath);
		return Result;
	}
	Pkg->FullyLoad();

	// Close trapdoor #4: UPackage::PersistentGuid (Package.cpp:138,
	// `PersistentGuid = FGuid::NewGuid()` in UPackage::PostInitProperties).
	// Persists into the .uasset's FPackageFileSummary
	// (SavePackage2.cpp:1286), so a random value here drifts the very first
	// 16-byte block of every fresh save. Closed by overwriting with a seed
	// derived from the package path before SavePackage runs. Only relevant
	// on the create path; existing packages keep their on-disk PersistentGuid.
	Pkg->SetPersistentGuid(BpxReflection::SeedGuidFromJoined(
		PackagePath + TEXT(":pkg")));

	// Suppress auto-spawned default event nodes (BeginPlay / Tick / etc. for
	// AActor-family parents) for the duration of the create call. With them
	// out of the way, the only FGuid trapdoors are BlueprintGuid (#1) and the
	// UCS K2Node_FunctionEntry NodeGuid (#2a) — no per-event-node state to
	// chase. M28.10.0 research established that even with sorted-array +
	// seeded NodeGuids/PinIds, the spawned UK2Node_Events carry additional
	// random state that surfaces as ~177 bytes of body drift per node — most
	// likely FUniqueObjectGuid annotations or UFunction-related GUIDs that
	// the engine generates as side-effects. Authoring events explicitly via
	// `add_custom_event_node` (M28.3.3) post-create is the correct pattern;
	// design.md's drivers (BP_EncounterDirector, UAIActionScorer) author
	// their events that way anyway.
	UBlueprintEditorSettings* MutableSettings = GetMutableDefault<UBlueprintEditorSettings>();
	const bool bPrevSpawnDefaults = MutableSettings ? MutableSettings->bSpawnDefaultBlueprintNodes : true;
	if (MutableSettings)
	{
		MutableSettings->bSpawnDefaultBlueprintNodes = false;
	}

	// Engine call. Mirrors UBlueprintFactory::FactoryCreateNew's path
	// (EditorFactories.cpp:6820) without the modal class-picker — we resolve
	// ParentClass up-front. Synchronous compile runs at the tail of
	// CreateBlueprint (Kismet2.cpp:525-527).
	const FString ShortName = FPackageName::GetShortName(PackagePath);
	UBlueprint* NewBP = FKismetEditorUtilities::CreateBlueprint(
		ParentClass, Pkg, FName(*ShortName),
		BPTYPE_Normal,
		UBlueprint::StaticClass(),
		UBlueprintGeneratedClass::StaticClass(),
		NAME_None);

	// Restore the setting before any error-return paths so the editor's UI
	// behaviour for interactive New Blueprint creation isn't affected.
	if (MutableSettings)
	{
		MutableSettings->bSpawnDefaultBlueprintNodes = bPrevSpawnDefaults;
	}

	if (!NewBP)
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("FKismetEditorUtilities::CreateBlueprint(Parent='%s', Pkg='%s', Name='%s') returned null"),
			*ParentClass->GetPathName(), *PackagePath, *ShortName);
		return Result;
	}

	// Helper: walk every UPROPERTY FGuid field on Obj's class chain and seed
	// it from `<PackagePath>:<Tag>:<FieldName>`. Catches both documented
	// trapdoors (UBlueprintCore::BlueprintGuid, UEdGraph::GraphGuid /
	// InterfaceGuid) and any future engine additions that introduce a new
	// FGuid::NewGuid() in object construction. Reflection sees private
	// UPROPERTYs just fine — the C++ visibility modifier doesn't apply at
	// the FProperty layer.
	auto SeedAllFGuidProperties = [&](UObject* Obj, const FString& Tag)
	{
		if (!Obj) { return; }
		for (TFieldIterator<FStructProperty> It(Obj->GetClass()); It; ++It)
		{
			FStructProperty* Prop = *It;
			if (!Prop || Prop->Struct != TBaseStructure<FGuid>::Get()) { continue; }
			if (FGuid* GuidPtr = Prop->ContainerPtrToValuePtr<FGuid>(Obj))
			{
				*GuidPtr = BpxReflection::SeedGuidFromJoined(
					PackagePath + TEXT(":") + Tag + TEXT(":") + Prop->GetName());
			}
		}
	};

	auto SeedGraphGuid = [&](UEdGraph* Graph, const FString& Tag)
	{
		if (!Graph) { return; }
		SeedAllFGuidProperties(Graph, FString(TEXT("graph:")) + Tag);
	};

	// Close trapdoors #1 (BlueprintGuid) and any FGuid drift on the
	// freshly-compiled generated class / skeleton class / SCS. The recursive
	// `ForEachObjectWithOuter` walk we tried at first crashed SavePackage —
	// it touched FGuid fields on objects whose state SavePackage assumed
	// stable (likely UFunction inner scripts or class metadata). Targeted
	// seeding on the well-understood object set is the safe path; the
	// generated class / skeleton class / SCS each carry zero FGuid
	// UPROPERTYs in stock UE 5.7, so the calls are no-ops there but keep
	// us covered against future engine additions.
	SeedAllFGuidProperties(NewBP, TEXT("bp"));
	if (NewBP->GeneratedClass)
	{
		SeedAllFGuidProperties(NewBP->GeneratedClass, TEXT("genclass"));
	}
	if (NewBP->SkeletonGeneratedClass)
	{
		SeedAllFGuidProperties(NewBP->SkeletonGeneratedClass, TEXT("skelclass"));
	}
	if (NewBP->SimpleConstructionScript)
	{
		SeedAllFGuidProperties(NewBP->SimpleConstructionScript, TEXT("scs"));
	}

	// Per-graph seeds: UEdGraph::GraphGuid + UEdGraph::InterfaceGuid.

	for (UEdGraph* Graph : NewBP->FunctionGraphs)
	{
		if (!Graph) { continue; }
		if (Graph->GetFName() != UEdGraphSchema_K2::FN_UserConstructionScript) { continue; }
		SeedGraphGuid(Graph, TEXT("ucs"));
		for (UEdGraphNode* Node : Graph->Nodes)
		{
			if (UK2Node_FunctionEntry* Entry = Cast<UK2Node_FunctionEntry>(Node))
			{
				const FString Joined = PackagePath + TEXT(":ucs:entry");
				Entry->NodeGuid = BpxReflection::SeedGuidFromJoined(Joined);
				BpxReflection::SeedPinGuidsForNode(Entry, Joined);
			}
		}
	}

	// Seed the EventGraph ubergraph page's GraphGuid (trapdoor #5 cont.).
	// With bSpawnDefaultBlueprintNodes=false the page is empty (no default
	// events spawned). Plan authors add events explicitly via
	// `add_custom_event_node` (M28.3.3), which seeds NodeGuid + pin ids from
	// its own deterministic recipe. Defensive walk: if a future engine adds a
	// non-default node here (e.g. via OnBlueprintCreatedCallbacks for AnimBP
	// — not relevant for the AActor / UActorComponent design.md targets),
	// seed it the same way.
	for (int32 PageIdx = 0; PageIdx < NewBP->UbergraphPages.Num(); ++PageIdx)
	{
		UEdGraph* Page = NewBP->UbergraphPages[PageIdx];
		if (!Page) { continue; }
		SeedGraphGuid(Page, FString::Printf(TEXT("ubergraph:%d"), PageIdx));
		for (UEdGraphNode* Node : Page->Nodes)
		{
			if (!Node) { continue; }
			const FString Key = Node->GetClass()->GetName();
			const FString Joined = PackagePath + TEXT(":ubergraph_extra:") + Key;
			Node->NodeGuid = BpxReflection::SeedGuidFromJoined(Joined);
			BpxReflection::SeedPinGuidsForNode(Node, Joined);
		}
	}

	// Notify AssetRegistry + dirty the package, but DO NOT call
	// MarkBlueprintAsStructurallyModified — that triggers a recompile via the
	// Python-side compile_and_save_package, and the recompile path's
	// `ReconstructNode` calls regenerate NodeGuids/PinIds on certain K2Nodes,
	// clobbering our just-seeded GUIDs. The engine's CreateBlueprint already
	// compiled once with random GUIDs (Kismet2.cpp:525); the seeded GUIDs are
	// authoritative on the SOURCE graph, and the BPGC's compiled artefacts
	// don't reference NodeGuids by value, so saving without a second recompile
	// is correct. Save directly here so the seed pass is the last write
	// before SavePackage rolls the bytes to disk.
	FAssetRegistryModule::AssetCreated(NewBP);
	Pkg->SetDirtyFlag(true);

	FString Filename;
	if (!FPackageName::TryConvertLongPackageNameToFilename(
			Pkg->GetName(), Filename, FPackageName::GetAssetPackageExtension()))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("CreateBlueprintClassDeterministic: can't resolve filename for package '%s'"),
			*Pkg->GetName());
		return Result;
	}

	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
	SaveArgs.SaveFlags = SAVE_NoError;
	SaveArgs.Error = GWarn;
	if (!UPackage::SavePackage(Pkg, NewBP, *Filename, SaveArgs))
	{
		Result.ErrorMessage = FString::Printf(
			TEXT("SavePackage returned false for '%s'"), *Pkg->GetName());
		return Result;
	}

	Result.bSuccess = true;
	Result.BeforeText = TEXT("no-bp");
	Result.AfterText = PackagePath;
	return Result;
}
