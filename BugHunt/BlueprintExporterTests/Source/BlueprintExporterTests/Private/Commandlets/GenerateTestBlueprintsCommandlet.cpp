// Copyright 10 Chambers. All Rights Reserved.

#include "Commandlets/GenerateTestBlueprintsCommandlet.h"

#include "BlueprintExporterTestsModule.h"

#include "Engine/Blueprint.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/DataAsset.h"
#include "Engine/SCS_Node.h"
#include "Engine/SimpleConstructionScript.h"
#include "Engine/Level.h"
#include "Engine/UserDefinedEnum.h"
#include "Engine/UserDefinedStruct.h"
#include "Engine/World.h"

#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Kismet2/StructureEditorUtils.h"
#include "Kismet2/EnumEditorUtils.h"
#include "Schema/BlueprintExportTypes.h"
#include "UserDefinedStructure/UserDefinedStructEditorData.h"  // FStructVariableDescription full definition (M28.4.3 UDS fixture)

#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "AssetRegistry/IAssetRegistry.h"

#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraphSchema_K2.h"
#include "EdGraphUtilities.h"

#include "K2Node_CallFunction.h"
#include "K2Node_Event.h"
#include "K2Node_CustomEvent.h"
#include "K2Node_VariableGet.h"
#include "K2Node_VariableSet.h"
#include "K2Node_IfThenElse.h"
#include "K2Node_ExecutionSequence.h"
#include "K2Node_MakeArray.h"
#include "K2Node_MakeStruct.h"
#include "K2Node_BreakStruct.h"
#include "K2Node_Knot.h"
#include "K2Node_MathExpression.h"
#include "K2Node_Self.h"
#include "K2Node_MacroInstance.h"
#include "K2Node_FunctionEntry.h"
#include "K2Node_FunctionResult.h"
#include "K2Node_Composite.h"
#include "K2Node_ConstructObjectFromClass.h"
#include "K2Node_SpawnActorFromClass.h"
#include "K2Node_Timeline.h"

#include "UObject/Interface.h"
#include "UObject/Package.h"
#include "UObject/SavePackage.h"
#include "UObject/TopLevelAssetPath.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/MetaData.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "PackageTools.h"

#include "Blueprint/UserWidget.h"
#include "WidgetBlueprint.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Blueprint/WidgetTree.h"

#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Curves/CurveFloat.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryOption.h"
#include "EnvironmentQuery/EnvQueryGenerator.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_ActorsOfClass.h"
#include "EnvironmentQuery/Tests/EnvQueryTest_Random.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Team.h"
#include "Perception/AISenseConfig.h"

#if WITH_STATETREE_SUPPORT
#include "StateTree.h"
#endif

namespace BugHuntGen
{
	const TCHAR* const kFixturePackageRoot = TEXT("/Game/TestBlueprints");
	const TCHAR* const kAuxPackageRoot = TEXT("/Game/Fixtures");

	/** Set by Main() from the -Force CLI flag. Without it, existing fixtures are treated as up-to-date. */
	static bool GForceRegenerate = false;

	struct FResult
	{
		FString Name;
		bool bCreated = false;
		bool bSkipped = false;
		FString Message;
	};

	/** True if the given /Game/... package path is already committed to disk. */
	bool FixtureOnDisk(const FString& PackagePath)
	{
		FString FilePath;
		if (!FPackageName::TryConvertLongPackageNameToFilename(PackagePath, FilePath, FPackageName::GetAssetPackageExtension())) return false;
		return FPaths::FileExists(FilePath);
	}

	FString ShortNameFromPath(const FString& PackagePath)
	{
		return FPackageName::GetShortName(PackagePath);
	}

	bool SavePackageForAsset(UObject* Asset, FString& OutError)
	{
		if (!Asset) { OutError = TEXT("null asset"); return false; }
		UPackage* Pkg = Asset->GetPackage();
		if (!Pkg) { OutError = TEXT("no package"); return false; }

		Pkg->SetDirtyFlag(true);

		const FString Filename = FPackageName::LongPackageNameToFilename(Pkg->GetName(), FPackageName::GetAssetPackageExtension());

		FSavePackageArgs Args;
		Args.TopLevelFlags = RF_Public | RF_Standalone;
		Args.SaveFlags = SAVE_NoError;
		Args.Error = GWarn;

		const bool bSaved = UPackage::SavePackage(Pkg, Asset, *Filename, Args);
		if (!bSaved)
		{
			OutError = FString::Printf(TEXT("UPackage::SavePackage failed for %s"), *Filename);
			return false;
		}
		return true;
	}

	/** Create an empty Blueprint at the given package path, parented to ParentClass. */
	UBlueprint* CreateBlueprint(const FString& PackagePath, UClass* ParentClass, EBlueprintType Type = BPTYPE_Normal)
	{
		const FString ShortName = ShortNameFromPath(PackagePath);

		// If it already exists, use it (generator is idempotent unless -Force).
		if (UBlueprint* Existing = LoadObject<UBlueprint>(nullptr, *(PackagePath + TEXT(".") + ShortName)))
		{
			return Existing;
		}

		UPackage* Pkg = CreatePackage(*PackagePath);
		if (!Pkg) return nullptr;
		Pkg->FullyLoad();

		UBlueprint* BP = FKismetEditorUtilities::CreateBlueprint(
			ParentClass,
			Pkg,
			FName(*ShortName),
			Type,
			UBlueprint::StaticClass(),
			UBlueprintGeneratedClass::StaticClass(),
			FName(TEXT("BlueprintExporterTests")));

		if (BP)
		{
			FAssetRegistryModule::AssetCreated(BP);
			BP->MarkPackageDirty();
		}
		return BP;
	}

	/** Helper: add a boolean variable. Returns FBPVariableDescription index. */
	/** Set CPF_Net on a member variable so it is marked replicated. */
	void MarkReplicated(UBlueprint* BP, FName VarName)
	{
		if (uint64* Flags = FBlueprintEditorUtils::GetBlueprintVariablePropertyFlags(BP, VarName))
		{
			*Flags |= CPF_Net;
		}
	}

	void MarkRepNotify(UBlueprint* BP, FName VarName, FName NotifyFunc)
	{
		if (uint64* Flags = FBlueprintEditorUtils::GetBlueprintVariablePropertyFlags(BP, VarName))
		{
			*Flags |= CPF_Net | CPF_RepNotify;
		}
		FBlueprintEditorUtils::SetBlueprintVariableRepNotifyFunc(BP, VarName, NotifyFunc);
	}

	void AddBoolVariable(UBlueprint* BP, FName VarName, bool bReplicated = false)
	{
		FEdGraphPinType Type;
		Type.PinCategory = UEdGraphSchema_K2::PC_Boolean;
		FBlueprintEditorUtils::AddMemberVariable(BP, VarName, Type, TEXT("false"));
		if (bReplicated)
		{
			MarkReplicated(BP, VarName);
		}
	}

	void AddIntVariable(UBlueprint* BP, FName VarName)
	{
		FEdGraphPinType Type;
		Type.PinCategory = UEdGraphSchema_K2::PC_Int;
		FBlueprintEditorUtils::AddMemberVariable(BP, VarName, Type);
	}

	void AddFloatVariable(UBlueprint* BP, FName VarName)
	{
		FEdGraphPinType Type;
		Type.PinCategory = UEdGraphSchema_K2::PC_Real;
		Type.PinSubCategory = UEdGraphSchema_K2::PC_Float;
		FBlueprintEditorUtils::AddMemberVariable(BP, VarName, Type);
	}

	void AddStringVariable(UBlueprint* BP, FName VarName)
	{
		FEdGraphPinType Type;
		Type.PinCategory = UEdGraphSchema_K2::PC_String;
		FBlueprintEditorUtils::AddMemberVariable(BP, VarName, Type);
	}

	void AddNameVariable(UBlueprint* BP, FName VarName)
	{
		FEdGraphPinType Type;
		Type.PinCategory = UEdGraphSchema_K2::PC_Name;
		FBlueprintEditorUtils::AddMemberVariable(BP, VarName, Type);
	}

	void AddVectorVariable(UBlueprint* BP, FName VarName)
	{
		FEdGraphPinType Type;
		Type.PinCategory = UEdGraphSchema_K2::PC_Struct;
		Type.PinSubCategoryObject = TBaseStructure<FVector>::Get();
		FBlueprintEditorUtils::AddMemberVariable(BP, VarName, Type);
	}

	void AddObjectVariable(UBlueprint* BP, FName VarName, UClass* Cls)
	{
		FEdGraphPinType Type;
		Type.PinCategory = UEdGraphSchema_K2::PC_Object;
		Type.PinSubCategoryObject = Cls;
		FBlueprintEditorUtils::AddMemberVariable(BP, VarName, Type);
	}

	void AddArrayIntVariable(UBlueprint* BP, FName VarName)
	{
		FEdGraphPinType Type;
		Type.PinCategory = UEdGraphSchema_K2::PC_Int;
		Type.ContainerType = EPinContainerType::Array;
		FBlueprintEditorUtils::AddMemberVariable(BP, VarName, Type);
	}

	void AddSetStringVariable(UBlueprint* BP, FName VarName)
	{
		FEdGraphPinType Type;
		Type.PinCategory = UEdGraphSchema_K2::PC_String;
		Type.ContainerType = EPinContainerType::Set;
		FBlueprintEditorUtils::AddMemberVariable(BP, VarName, Type);
	}

	void AddMapNameFloatVariable(UBlueprint* BP, FName VarName)
	{
		FEdGraphPinType Type;
		Type.PinCategory = UEdGraphSchema_K2::PC_Name;
		Type.ContainerType = EPinContainerType::Map;
		Type.PinValueType.TerminalCategory = UEdGraphSchema_K2::PC_Real;
		Type.PinValueType.TerminalSubCategory = UEdGraphSchema_K2::PC_Float;
		FBlueprintEditorUtils::AddMemberVariable(BP, VarName, Type);
	}

	void AddRepNotifyBoolVariable(UBlueprint* BP, FName VarName, FName NotifyFunction)
	{
		FEdGraphPinType Type;
		Type.PinCategory = UEdGraphSchema_K2::PC_Boolean;
		FBlueprintEditorUtils::AddMemberVariable(BP, VarName, Type, TEXT("false"));
		MarkRepNotify(BP, VarName, NotifyFunction);
	}

	/** Compile the blueprint and return true if it ended BS_UpToDate. */
	bool Compile(UBlueprint* BP)
	{
		if (!BP) return false;
		FKismetEditorUtilities::CompileBlueprint(BP);
		return BP->Status == BS_UpToDate || BP->Status == BS_UpToDateWithWarnings;
	}

	// =========================================================================
	// Fixture generators — each is isolated; failures don't cascade.
	// =========================================================================

	/** BP_NodeZoo — Actor BP exercising a selection of common K2Node subclasses. */
	FResult GenBP_NodeZoo()
	{
		FResult R; R.Name = TEXT("BP_NodeZoo");
		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate)
		{
			R.bSkipped = true; R.Message = TEXT("already on disk (use -Force to regenerate)");
			return R;
		}
		UBlueprint* BP = CreateBlueprint(Path, AActor::StaticClass());
		if (!BP) { R.Message = TEXT("CreateBlueprint failed"); return R; }

		AddBoolVariable(BP, TEXT("bEnabled"));
		AddIntVariable(BP, TEXT("Count"));
		AddFloatVariable(BP, TEXT("Speed"));
		AddStringVariable(BP, TEXT("Label"));
		AddVectorVariable(BP, TEXT("Origin"));

		// Add a custom event to give the graph a named entry point the exporter can find.
		if (UEdGraph* EventGraph = FBlueprintEditorUtils::FindEventGraph(BP))
		{
			UK2Node_CustomEvent* CE = NewObject<UK2Node_CustomEvent>(EventGraph);
			CE->CustomFunctionName = TEXT("Ping");
			EventGraph->AddNode(CE, /*bFromUI=*/false, /*bSelectNewNode=*/false);
			CE->CreateNewGuid();
			CE->PostPlacedNewNode();
			CE->AllocateDefaultPins();
			CE->NodePosX = 200; CE->NodePosY = 200;

			// A plain sequence node — common structural element.
			UK2Node_ExecutionSequence* Seq = NewObject<UK2Node_ExecutionSequence>(EventGraph);
			EventGraph->AddNode(Seq, false, false);
			Seq->CreateNewGuid();
			Seq->PostPlacedNewNode();
			Seq->AllocateDefaultPins();
			Seq->NodePosX = 500; Seq->NodePosY = 200;

			// Connect CE exec to Seq exec.
			UEdGraphPin* CEExec = CE->FindPin(UEdGraphSchema_K2::PN_Then);
			UEdGraphPin* SeqExec = Seq->GetExecPin();
			if (CEExec && SeqExec) CEExec->MakeLinkTo(SeqExec);
		}

		FBlueprintEditorUtils::MarkBlueprintAsModified(BP);
		if (!Compile(BP)) { R.Message = TEXT("compile failed"); return R; }

		FString Err;
		if (!SavePackageForAsset(BP, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** BP_PinHell — variables exercising wildcard / arrays / sets / maps / delegate types. */
	FResult GenBP_PinHell()
	{
		FResult R; R.Name = TEXT("BP_PinHell");
		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }
		UBlueprint* BP = CreateBlueprint(Path, AActor::StaticClass());
		if (!BP) { R.Message = TEXT("CreateBlueprint failed"); return R; }

		AddIntVariable(BP, TEXT("Scalar"));
		AddArrayIntVariable(BP, TEXT("IntArray"));
		AddSetStringVariable(BP, TEXT("StringSet"));
		AddMapNameFloatVariable(BP, TEXT("NameToFloat"));
		AddObjectVariable(BP, TEXT("ActorRef"), AActor::StaticClass());
		AddVectorVariable(BP, TEXT("Position"));

		FBlueprintEditorUtils::MarkBlueprintAsModified(BP);
		if (!Compile(BP)) { R.Message = TEXT("compile failed"); return R; }

		FString Err;
		if (!SavePackageForAsset(BP, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** BP_InheritanceChain — 3-deep BP parent chain with overrides. */
	FResult GenBP_InheritanceChain()
	{
		FResult R; R.Name = TEXT("BP_InheritanceChain");

		const FString P1 = FString::Printf(TEXT("%s/%s_Grandparent"), kFixturePackageRoot, *R.Name);
		const FString P2 = FString::Printf(TEXT("%s/%s_Parent"), kFixturePackageRoot, *R.Name);
		const FString P3 = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(P3) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }

		UBlueprint* Grand = CreateBlueprint(P1, AActor::StaticClass());
		if (!Grand) { R.Message = TEXT("grandparent create failed"); return R; }
		AddBoolVariable(Grand, TEXT("bGrand"));
		AddIntVariable(Grand, TEXT("GrandInt"));
		FBlueprintEditorUtils::MarkBlueprintAsModified(Grand);
		if (!Compile(Grand)) { R.Message = TEXT("grandparent compile failed"); return R; }
		FString SaveErr;
		if (!SavePackageForAsset(Grand, SaveErr)) { R.Message = SaveErr; return R; }

		UBlueprint* Parent = CreateBlueprint(P2, Grand->GeneratedClass);
		if (!Parent) { R.Message = TEXT("parent create failed"); return R; }
		AddStringVariable(Parent, TEXT("ParentString"));
		FBlueprintEditorUtils::MarkBlueprintAsModified(Parent);
		if (!Compile(Parent)) { R.Message = TEXT("parent compile failed"); return R; }
		if (!SavePackageForAsset(Parent, SaveErr)) { R.Message = SaveErr; return R; }

		UBlueprint* Child = CreateBlueprint(P3, Parent->GeneratedClass);
		if (!Child) { R.Message = TEXT("child create failed"); return R; }
		AddFloatVariable(Child, TEXT("ChildFloat"));
		FBlueprintEditorUtils::MarkBlueprintAsModified(Child);
		if (!Compile(Child)) { R.Message = TEXT("child compile failed"); return R; }
		if (!SavePackageForAsset(Child, SaveErr)) { R.Message = SaveErr; return R; }

		R.bCreated = true;
		return R;
	}

	/** BP_SCSMonster — Actor BP with multiple components in an attachment hierarchy. */
	FResult GenBP_SCSMonster()
	{
		FResult R; R.Name = TEXT("BP_SCSMonster");
		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }
		UBlueprint* BP = CreateBlueprint(Path, AActor::StaticClass());
		if (!BP) { R.Message = TEXT("CreateBlueprint failed"); return R; }

		USimpleConstructionScript* SCS = BP->SimpleConstructionScript;
		if (!SCS) { R.Message = TEXT("no SCS"); return R; }

		// Root: SceneComponent (default on Actor-derived BPs).
		USCS_Node* Root = SCS->GetRootNodes().Num() > 0 ? SCS->GetRootNodes()[0] : nullptr;
		if (!Root)
		{
			Root = SCS->CreateNode(USceneComponent::StaticClass(), TEXT("DefaultSceneRoot"));
			SCS->AddNode(Root);
		}

		// Add a StaticMesh child.
		USCS_Node* MeshNode = SCS->CreateNode(UStaticMeshComponent::StaticClass(), TEXT("Mesh"));
		Root->AddChildNode(MeshNode);

		// Add a Box under the mesh.
		USCS_Node* BoxNode = SCS->CreateNode(UBoxComponent::StaticClass(), TEXT("Box"));
		MeshNode->AddChildNode(BoxNode);

		// And a Sphere under root.
		USCS_Node* SphereNode = SCS->CreateNode(USphereComponent::StaticClass(), TEXT("Sphere"));
		Root->AddChildNode(SphereNode);

		FBlueprintEditorUtils::MarkBlueprintAsModified(BP);
		if (!Compile(BP)) { R.Message = TEXT("compile failed"); return R; }

		FString Err;
		if (!SavePackageForAsset(BP, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** BP_MacroMania — macro library BP + macro instance usage. */
	FResult GenBP_MacroMania()
	{
		FResult R; R.Name = TEXT("BP_MacroMania");

		const FString LibPath = FString::Printf(TEXT("%s/%s_Lib"), kFixturePackageRoot, *R.Name);
		const FString ConsumerPathPre = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(LibPath) && FixtureOnDisk(ConsumerPathPre) && !GForceRegenerate)
		{
			R.bSkipped = true; R.Message = TEXT("already on disk"); return R;
		}
		UBlueprint* Lib = CreateBlueprint(LibPath, AActor::StaticClass(), BPTYPE_MacroLibrary);
		if (!Lib) { R.Message = TEXT("macro library create failed"); return R; }

		// Add one macro graph so the library is non-empty.
		UEdGraph* MacroGraph = FBlueprintEditorUtils::CreateNewGraph(
			Lib, TEXT("MyMacro"),
			UEdGraph::StaticClass(),
			UEdGraphSchema_K2::StaticClass());
		FBlueprintEditorUtils::AddMacroGraph(Lib, MacroGraph, /*bIsUserCreated=*/true, AActor::StaticClass());

		FBlueprintEditorUtils::MarkBlueprintAsModified(Lib);
		if (!Compile(Lib)) { R.Message = TEXT("macro lib compile failed"); return R; }

		FString Err;
		if (!SavePackageForAsset(Lib, Err)) { R.Message = Err; return R; }

		// Consumer BP that references the library (simplest: just parent to Actor, add a variable).
		const FString ConsumerPath = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		UBlueprint* Consumer = CreateBlueprint(ConsumerPath, AActor::StaticClass());
		if (!Consumer) { R.Message = TEXT("consumer create failed"); return R; }
		AddIntVariable(Consumer, TEXT("Count"));
		FBlueprintEditorUtils::MarkBlueprintAsModified(Consumer);
		if (!Compile(Consumer)) { R.Message = TEXT("consumer compile failed"); return R; }
		if (!SavePackageForAsset(Consumer, Err)) { R.Message = Err; return R; }

		R.bCreated = true;
		return R;
	}

	/** BP_NetRep — replicated variables + RepNotify. */
	FResult GenBP_NetRep()
	{
		FResult R; R.Name = TEXT("BP_NetRep");
		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }
		UBlueprint* BP = CreateBlueprint(Path, AActor::StaticClass());
		if (!BP) { R.Message = TEXT("CreateBlueprint failed"); return R; }

		AddBoolVariable(BP, TEXT("bSimpleReplicated"), /*bReplicated=*/true);
		AddIntVariable(BP, TEXT("Score"));
		MarkReplicated(BP, TEXT("Score"));

		AddRepNotifyBoolVariable(BP, TEXT("bHealthLow"), TEXT("OnRep_HealthLow"));

		// Create the OnRep function graph so compile succeeds.
		UEdGraph* RepFn = FBlueprintEditorUtils::CreateNewGraph(
			BP, TEXT("OnRep_HealthLow"),
			UEdGraph::StaticClass(),
			UEdGraphSchema_K2::StaticClass());
		FBlueprintEditorUtils::AddFunctionGraph<UClass>(BP, RepFn, /*bIsUserCreated=*/true, nullptr);

		FBlueprintEditorUtils::MarkBlueprintAsModified(BP);
		if (!Compile(BP)) { R.Message = TEXT("compile failed"); return R; }

		FString Err;
		if (!SavePackageForAsset(BP, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** BP_StructEnumZoo — user-defined struct + enum + BP that uses them. */
	FResult GenBP_StructEnumZoo()
	{
		FResult R; R.Name = TEXT("BP_StructEnumZoo");

		const FString BPPathPre = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(BPPathPre) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }

		// User enum.
		const FString EnumPath = FString::Printf(TEXT("%s/E_BugHuntEnum"), kAuxPackageRoot);
		UUserDefinedEnum* BugHuntEnum = LoadObject<UUserDefinedEnum>(nullptr, *(EnumPath + TEXT(".E_BugHuntEnum")));
		if (!BugHuntEnum)
		{
			UPackage* EnumPkg = CreatePackage(*EnumPath);
			EnumPkg->FullyLoad();
			UEnum* AsEnum = FEnumEditorUtils::CreateUserDefinedEnum(EnumPkg, TEXT("E_BugHuntEnum"), RF_Public | RF_Standalone);
			BugHuntEnum = Cast<UUserDefinedEnum>(AsEnum);
			if (BugHuntEnum)
			{
				FEnumEditorUtils::AddNewEnumeratorForUserDefinedEnum(BugHuntEnum);
				FEnumEditorUtils::AddNewEnumeratorForUserDefinedEnum(BugHuntEnum);
				FEnumEditorUtils::AddNewEnumeratorForUserDefinedEnum(BugHuntEnum);
				FAssetRegistryModule::AssetCreated(BugHuntEnum);
			}
		}
		if (BugHuntEnum)
		{
			FString Err;
			SavePackageForAsset(BugHuntEnum, Err);
		}

		// User struct.
		const FString StructPath = FString::Printf(TEXT("%s/S_BugHuntStruct"), kAuxPackageRoot);
		UUserDefinedStruct* UStructObj = LoadObject<UUserDefinedStruct>(nullptr, *(StructPath + TEXT(".S_BugHuntStruct")));
		if (!UStructObj)
		{
			UPackage* StructPkg = CreatePackage(*StructPath);
			StructPkg->FullyLoad();
			UStructObj = FStructureEditorUtils::CreateUserDefinedStruct(StructPkg, TEXT("S_BugHuntStruct"), RF_Public | RF_Standalone);
			if (UStructObj)
			{
				FAssetRegistryModule::AssetCreated(UStructObj);
			}
		}
		if (UStructObj)
		{
			FString Err;
			SavePackageForAsset(UStructObj, Err);
		}

		// Consumer BP.
		const FString BPPath = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		UBlueprint* BP = CreateBlueprint(BPPath, AActor::StaticClass());
		if (!BP) { R.Message = TEXT("consumer create failed"); return R; }

		if (BugHuntEnum)
		{
			FEdGraphPinType EnumType;
			EnumType.PinCategory = UEdGraphSchema_K2::PC_Byte;
			EnumType.PinSubCategoryObject = BugHuntEnum;
			FBlueprintEditorUtils::AddMemberVariable(BP, TEXT("EnumValue"), EnumType);
		}
		if (UStructObj)
		{
			FEdGraphPinType StructType;
			StructType.PinCategory = UEdGraphSchema_K2::PC_Struct;
			StructType.PinSubCategoryObject = UStructObj;
			FBlueprintEditorUtils::AddMemberVariable(BP, TEXT("StructValue"), StructType);
		}

		FBlueprintEditorUtils::MarkBlueprintAsModified(BP);
		if (!Compile(BP)) { R.Message = TEXT("compile failed"); return R; }

		FString Err;
		if (!SavePackageForAsset(BP, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** BP_WidgetTree — UserWidget BP with a simple widget hierarchy. */
	FResult GenBP_WidgetTree()
	{
		FResult R; R.Name = TEXT("BP_WidgetTree");

		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }
		const FString Short = ShortNameFromPath(Path);

		UWidgetBlueprint* Existing = LoadObject<UWidgetBlueprint>(nullptr, *(Path + TEXT(".") + Short));
		if (!Existing)
		{
			UPackage* Pkg = CreatePackage(*Path);
			Pkg->FullyLoad();
			// NOTE: Arg 5 is BlueprintClassType (UWidgetBlueprint), arg 6 is
			// BlueprintGeneratedClassType (UWidgetBlueprintGeneratedClass).
			// Reversing these produces a "plain" UBlueprint that crashes when
			// its WidgetTree is accessed.
			Existing = Cast<UWidgetBlueprint>(FKismetEditorUtilities::CreateBlueprint(
				UUserWidget::StaticClass(),
				Pkg,
				FName(*Short),
				BPTYPE_Normal,
				UWidgetBlueprint::StaticClass(),
				UWidgetBlueprintGeneratedClass::StaticClass(),
				FName(TEXT("BlueprintExporterTests"))));
			if (Existing) FAssetRegistryModule::AssetCreated(Existing);
		}
		if (!Existing) { R.Message = TEXT("widget BP create failed"); return R; }

		// FKismetEditorUtilities::CreateBlueprint for UWidgetBlueprint does NOT
		// auto-create a WidgetTree. Construct one on demand.
		if (!Existing->WidgetTree)
		{
			Existing->WidgetTree = NewObject<UWidgetTree>(Existing, TEXT("WidgetTree"), RF_Transactional);
		}

		// Build a trivial widget tree: CanvasPanel root with a TextBlock child.
		if (Existing->WidgetTree && !Existing->WidgetTree->RootWidget)
		{
			UCanvasPanel* Root = Existing->WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootCanvas"));
			if (Root)
			{
				Existing->WidgetTree->RootWidget = Root;
				UTextBlock* Text = Existing->WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("HelloText"));
				if (Text) Root->AddChild(Text);
			}
		}

		FBlueprintEditorUtils::MarkBlueprintAsModified(Existing);
		if (!Compile(Existing)) { R.Message = TEXT("widget compile failed"); return R; }

		FString Err;
		if (!SavePackageForAsset(Existing, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** BP_NPC_BehaviorTree — BT + BB asset + AIController BP that uses them. */
	FResult GenBP_NPC_BehaviorTree()
	{
		FResult R; R.Name = TEXT("BP_NPC_BehaviorTree");

		const FString BPPathPre = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(BPPathPre) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }

		// Blackboard.
		const FString BBPath = FString::Printf(TEXT("%s/BB_BugHunt"), kAuxPackageRoot);
		UBlackboardData* BB = LoadObject<UBlackboardData>(nullptr, *(BBPath + TEXT(".BB_BugHunt")));
		if (!BB)
		{
			UPackage* Pkg = CreatePackage(*BBPath);
			Pkg->FullyLoad();
			BB = NewObject<UBlackboardData>(Pkg, TEXT("BB_BugHunt"), RF_Public | RF_Standalone);
			FAssetRegistryModule::AssetCreated(BB);

			auto AddKey = [BB](FName Name, UClass* KeyCls)
			{
				FBlackboardEntry Entry;
				Entry.EntryName = Name;
				Entry.KeyType = NewObject<UBlackboardKeyType>(BB, KeyCls);
				BB->Keys.Add(Entry);
			};
			AddKey(TEXT("bAlert"),    UBlackboardKeyType_Bool::StaticClass());
			AddKey(TEXT("Count"),     UBlackboardKeyType_Int::StaticClass());
			AddKey(TEXT("Speed"),     UBlackboardKeyType_Float::StaticClass());
			AddKey(TEXT("LastSeen"),  UBlackboardKeyType_Vector::StaticClass());
			AddKey(TEXT("Tag"),       UBlackboardKeyType_String::StaticClass());

			FString Err;
			SavePackageForAsset(BB, Err);
		}

		// Behavior tree.
		const FString BTPath = FString::Printf(TEXT("%s/BT_BugHunt"), kAuxPackageRoot);
		UBehaviorTree* BT = LoadObject<UBehaviorTree>(nullptr, *(BTPath + TEXT(".BT_BugHunt")));
		if (!BT)
		{
			UPackage* Pkg = CreatePackage(*BTPath);
			Pkg->FullyLoad();
			BT = NewObject<UBehaviorTree>(Pkg, TEXT("BT_BugHunt"), RF_Public | RF_Standalone);
			BT->BlackboardAsset = BB;
			FAssetRegistryModule::AssetCreated(BT);
			FString Err;
			SavePackageForAsset(BT, Err);
		}

		// AIController BP that references the BT.
		const FString BPPath = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		UBlueprint* BP = CreateBlueprint(BPPath, AAIController::StaticClass());
		if (!BP) { R.Message = TEXT("AIController BP create failed"); return R; }

		// Add a soft ref variable to the BT so the export has something to chew on.
		FEdGraphPinType BTType;
		BTType.PinCategory = UEdGraphSchema_K2::PC_SoftObject;
		BTType.PinSubCategoryObject = UBehaviorTree::StaticClass();
		FBlueprintEditorUtils::AddMemberVariable(BP, TEXT("BT"), BTType);

		FBlueprintEditorUtils::MarkBlueprintAsModified(BP);
		if (!Compile(BP)) { R.Message = TEXT("compile failed"); return R; }

		FString Err;
		if (!SavePackageForAsset(BP, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** BP_NPC_Perception — AIController BP with AIPerceptionComponent and sense configs. */
	FResult GenBP_NPC_Perception()
	{
		FResult R; R.Name = TEXT("BP_NPC_Perception");

		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }
		UBlueprint* BP = CreateBlueprint(Path, AAIController::StaticClass());
		if (!BP) { R.Message = TEXT("create failed"); return R; }

		// Add a perception component via SCS.
		USimpleConstructionScript* SCS = BP->SimpleConstructionScript;
		if (!SCS) { R.Message = TEXT("no SCS"); return R; }

		USCS_Node* PerceptionNode = SCS->CreateNode(UAIPerceptionComponent::StaticClass(), TEXT("Perception"));
		SCS->AddNode(PerceptionNode);

		// Configure with sight + hearing sense configs on the template.
		if (UAIPerceptionComponent* Template = Cast<UAIPerceptionComponent>(PerceptionNode->ComponentTemplate))
		{
			UAISenseConfig_Sight* Sight = NewObject<UAISenseConfig_Sight>(Template, TEXT("Sight"));
			Sight->SightRadius = 1500.0f;
			Sight->LoseSightRadius = 2000.0f;
			Sight->PeripheralVisionAngleDegrees = 90.0f;
			Sight->SetMaxAge(5.0f);

			UAISenseConfig_Hearing* Hearing = NewObject<UAISenseConfig_Hearing>(Template, TEXT("Hearing"));
			Hearing->HearingRange = 3000.0f;
			Hearing->SetMaxAge(3.0f);

			Template->ConfigureSense(*Sight);
			Template->ConfigureSense(*Hearing);
			Template->SetDominantSense(UAISenseConfig_Sight::StaticClass());
		}

		FBlueprintEditorUtils::MarkBlueprintAsModified(BP);
		if (!Compile(BP)) { R.Message = TEXT("compile failed"); return R; }

		FString Err;
		if (!SavePackageForAsset(BP, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/**
	 * BP_NPC_StateTree — only generated if State Tree support is compiled in. Otherwise
	 * we skip gracefully (coverage gap is captured in the report).
	 */
	FResult GenBP_NPC_StateTree()
	{
		FResult R; R.Name = TEXT("BP_NPC_StateTree");
#if WITH_STATETREE_SUPPORT
		const FString BPPathPre = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(BPPathPre) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }

		// Create an empty StateTree asset next to an AIController BP that references it.
		const FString STPath = FString::Printf(TEXT("%s/ST_BugHunt"), kAuxPackageRoot);
		UStateTree* ST = LoadObject<UStateTree>(nullptr, *(STPath + TEXT(".ST_BugHunt")));
		if (!ST)
		{
			UPackage* Pkg = CreatePackage(*STPath);
			Pkg->FullyLoad();
			ST = NewObject<UStateTree>(Pkg, TEXT("ST_BugHunt"), RF_Public | RF_Standalone);
			FAssetRegistryModule::AssetCreated(ST);
			FString Err;
			SavePackageForAsset(ST, Err);
		}

		const FString BPPath = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		UBlueprint* BP = CreateBlueprint(BPPath, AAIController::StaticClass());
		if (!BP) { R.Message = TEXT("create failed"); return R; }

		FEdGraphPinType STType;
		STType.PinCategory = UEdGraphSchema_K2::PC_SoftObject;
		STType.PinSubCategoryObject = UStateTree::StaticClass();
		FBlueprintEditorUtils::AddMemberVariable(BP, TEXT("StateTree"), STType);

		FBlueprintEditorUtils::MarkBlueprintAsModified(BP);
		if (!Compile(BP)) { R.Message = TEXT("compile failed"); return R; }
		FString Err;
		if (!SavePackageForAsset(BP, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
#else
		R.bSkipped = true;
		R.Message = TEXT("WITH_STATETREE_SUPPORT=0 — skipped");
#endif
		return R;
	}

	/**
	 * BP_NPC_SmartObject — SmartObjects module isn't in our dep list and isn't guaranteed
	 * available in a vanilla UE 5.7 install. Mark as skipped so the report records the gap.
	 */
	FResult GenBP_NPC_SmartObject()
	{
		FResult R; R.Name = TEXT("BP_NPC_SmartObject");
		R.bSkipped = true;
		R.Message = TEXT("SmartObjects module not enabled in plugin deps — skipped");
		return R;
	}

	/** BP_GASP_AnimBP — very simplified AnimBP (no GASP / Motion Matching / Control Rig). */
	FResult GenBP_GASP_AnimBP()
	{
		FResult R; R.Name = TEXT("BP_GASP_AnimBP");
		// We don't have an actual skeleton in the test project — creating a real AnimBP
		// requires a USkeleton asset. Without one, the AnimBP is essentially inert.
		// Rather than produce a junk fixture we mark it as skipped with an explicit reason.
		R.bSkipped = true;
		R.Message = TEXT("No USkeleton available in TestProject without imports — skipped");
		return R;
	}

	/** BP_GAS_Ability — requires GameplayAbilities module. Skipped if absent. */
	FResult GenBP_GAS_Ability()
	{
		FResult R; R.Name = TEXT("BP_GAS_Ability");
#if WITH_GAS_SUPPORT
		const FString PathPre = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(PathPre) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }

		// Create a UGameplayAbility BP if GAS is available.
		UClass* AbilityBase = FindObject<UClass>(nullptr, TEXT("/Script/GameplayAbilities.GameplayAbility"));
		if (!AbilityBase) { R.bSkipped = true; R.Message = TEXT("UGameplayAbility class not found"); return R; }

		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		UBlueprint* BP = CreateBlueprint(Path, AbilityBase);
		if (!BP) { R.Message = TEXT("create failed"); return R; }

		AddFloatVariable(BP, TEXT("Cooldown"));
		AddIntVariable(BP, TEXT("Charges"));

		FBlueprintEditorUtils::MarkBlueprintAsModified(BP);
		if (!Compile(BP)) { R.Message = TEXT("compile failed"); return R; }
		FString Err;
		if (!SavePackageForAsset(BP, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
#else
		R.bSkipped = true;
		R.Message = TEXT("WITH_GAS_SUPPORT=0 — skipped");
#endif
		return R;
	}

	/** BPI_BpxTestInterface — M26.1 regression fixture.
	 *  Declares a single function `GetTargetingInfo` with three outputs
	 *  (bIsAlive:bool, bIsTargetable:bool, Faction:int32) matching the
	 *  Flat Arena motivating case that drove M26.1. Used as the interface
	 *  target by `implement_interface_function` tests (the op's output is
	 *  the BP_BpxTestImplementsInterface_Expected golden fixture). */
	FResult GenBPI_BpxTestInterface()
	{
		FResult R; R.Name = TEXT("BPI_BpxTestInterface");

		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }

		UBlueprint* IBP = CreateBlueprint(Path, UInterface::StaticClass(), BPTYPE_Interface);
		if (!IBP) { R.Message = TEXT("CreateBlueprint returned null for interface"); return R; }

		// UE compiles interface-function outputs from the RETURN node's
		// EGPD_Input user-defined pins, not from Entry's EGPD_Input pins
		// (which, perhaps counter-intuitively, don't produce CPF_OutParm
		// properties on the UFunction). AddFunctionGraph doesn't auto-add
		// a Return node, so we create one explicitly and declare the
		// three outputs there — matching UE editor's own "Add Output to
		// Function" behaviour.
		UEdGraph* FnGraph = FBlueprintEditorUtils::CreateNewGraph(
			IBP, FName(TEXT("GetTargetingInfo")),
			UEdGraph::StaticClass(),
			UEdGraphSchema_K2::StaticClass());
		FBlueprintEditorUtils::AddFunctionGraph<UClass>(
			IBP, FnGraph, /*bIsUserCreated=*/true, /*SignatureFromObject=*/(UClass*)nullptr);

		UK2Node_FunctionEntry* EntryNode = nullptr;
		for (UEdGraphNode* Node : FnGraph->Nodes)
		{
			if (UK2Node_FunctionEntry* EN = Cast<UK2Node_FunctionEntry>(Node))
			{
				EntryNode = EN;
				break;
			}
		}
		if (!EntryNode)
		{
			R.Message = TEXT("UK2Node_FunctionEntry node missing from generated graph");
			return R;
		}

		UK2Node_FunctionResult* ReturnNode = NewObject<UK2Node_FunctionResult>(FnGraph);
		ReturnNode->NodePosX = EntryNode->NodePosX + 400;
		ReturnNode->NodePosY = EntryNode->NodePosY;
		FnGraph->AddNode(ReturnNode, /*bUserAction=*/false, /*bSelectNewNode=*/false);
		ReturnNode->CreateNewGuid();
		ReturnNode->PostPlacedNewNode();
		ReturnNode->AllocateDefaultPins();

		FEdGraphPinType BoolType;
		BoolType.PinCategory = UEdGraphSchema_K2::PC_Boolean;
		FEdGraphPinType IntType;
		IntType.PinCategory = UEdGraphSchema_K2::PC_Int;

		ReturnNode->CreateUserDefinedPin(FName(TEXT("bIsAlive")),      BoolType, EGPD_Input, /*bUseUniqueName=*/false);
		ReturnNode->CreateUserDefinedPin(FName(TEXT("bIsTargetable")), BoolType, EGPD_Input, /*bUseUniqueName=*/false);
		ReturnNode->CreateUserDefinedPin(FName(TEXT("Faction")),       IntType,  EGPD_Input, /*bUseUniqueName=*/false);

		FBlueprintEditorUtils::MarkBlueprintAsModified(IBP);
		if (!Compile(IBP)) { R.Message = TEXT("compile failed"); return R; }

		FString Err;
		if (!SavePackageForAsset(IBP, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** BP_BpxTestImplementsInterface — M26.1 regression fixture baseline.
	 *  Actor BP with three member variables (bIsAlive, bIsTargetable,
	 *  Faction) matching the BPI_BpxTestInterface.GetTargetingInfo
	 *  signature. Declares the interface on ImplementedInterfaces but
	 *  provides NO override — running `implement_interface_function` on
	 *  a copy of this BP is what produces the committed _Expected golden
	 *  fixture (via scripts/regenerate_m26_1_golden.py). Depends on
	 *  BPI_BpxTestInterface existing — the Gens array orders them so
	 *  the interface generates first. */
	FResult GenBP_BpxTestImplementsInterface()
	{
		FResult R; R.Name = TEXT("BP_BpxTestImplementsInterface");

		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }

		const FString InterfaceClassPath = FString::Printf(
			TEXT("%s/BPI_BpxTestInterface.BPI_BpxTestInterface_C"), kFixturePackageRoot);
		UClass* InterfaceClass = LoadObject<UClass>(nullptr, *InterfaceClassPath);
		if (!InterfaceClass)
		{
			R.Message = FString::Printf(
				TEXT("interface class %s not found — BPI_BpxTestInterface must generate first"),
				*InterfaceClassPath);
			return R;
		}

		UBlueprint* BP = CreateBlueprint(Path, AActor::StaticClass());
		if (!BP) { R.Message = TEXT("CreateBlueprint returned null"); return R; }

		AddBoolVariable(BP, TEXT("bIsAlive"));
		AddBoolVariable(BP, TEXT("bIsTargetable"));
		AddIntVariable(BP, TEXT("Faction"));

		// ImplementNewInterface registers the interface on the BP's
		// ImplementedInterfaces list. No override function is added here —
		// that's the job of the op under test.
		FBlueprintEditorUtils::ImplementNewInterface(BP, FTopLevelAssetPath(InterfaceClass));

		FBlueprintEditorUtils::MarkBlueprintAsModified(BP);
		if (!Compile(BP)) { R.Message = TEXT("compile failed"); return R; }

		FString Err;
		if (!SavePackageForAsset(BP, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** BP_BpxTestStructuralVariables — M28.2.1 regression fixture baseline.
	 *  Empty Actor BP with no declared member variables. The inspect/soak
	 *  gates duplicate this into a scratch path and run `add_bp_variable`
	 *  against it; the post-op asset must be byte-deterministic across
	 *  rounds (M28.pre.3 soak gate) and the rendered .md must surface the
	 *  newly-added variable (M28.pre.2 inspect gate).
	 *
	 *  Kept deliberately empty — adding any baseline variables would muddle
	 *  the determinism story (existing variables already have stable VarGuids
	 *  from the original Generate run, so we'd only be testing the seeding
	 *  via the absence of drift, not the seeding itself). With zero baseline
	 *  variables, EVERY VarGuid in the post-op asset comes from the new
	 *  SeedGuidFromJoined path — clear blast radius. */
	FResult GenBP_BpxTestStructuralVariables()
	{
		FResult R; R.Name = TEXT("BP_BpxTestStructuralVariables");

		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }

		UBlueprint* BP = CreateBlueprint(Path, AActor::StaticClass());
		if (!BP) { R.Message = TEXT("CreateBlueprint returned null"); return R; }

		FBlueprintEditorUtils::MarkBlueprintAsModified(BP);
		if (!Compile(BP)) { R.Message = TEXT("compile failed"); return R; }

		FString Err;
		if (!SavePackageForAsset(BP, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** BP_BpxTestStructuralFunctions — M28.2.2 regression fixture baseline.
	 *  Empty Actor BP with no declared member functions (only whatever UE
	 *  auto-creates for a fresh AActor child — construction script + event
	 *  graph, never user-declared functions). The inspect / soak gates
	 *  duplicate this into a scratch path and run `add_bp_function`
	 *  against it; the post-op asset must be byte-deterministic across
	 *  rounds (M28.pre.3 soak, exercising the GraphGuid + Entry/Return
	 *  NodeGuid + pin-GUID seed triad) and the rendered .md / .deep.md
	 *  must surface the new function (M28.pre.2 inspect).
	 *
	 *  Same rationale as the variable fixture: kept deliberately empty so
	 *  every seeded GUID in the post-op asset comes from the new
	 *  SeedGuidFromJoined(":func:", ":entry", ":return", per-pin) paths,
	 *  not from pre-existing on-disk content. */
	FResult GenBP_BpxTestStructuralFunctions()
	{
		FResult R; R.Name = TEXT("BP_BpxTestStructuralFunctions");

		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }

		UBlueprint* BP = CreateBlueprint(Path, AActor::StaticClass());
		if (!BP) { R.Message = TEXT("CreateBlueprint returned null"); return R; }

		FBlueprintEditorUtils::MarkBlueprintAsModified(BP);
		if (!Compile(BP)) { R.Message = TEXT("compile failed"); return R; }

		FString Err;
		if (!SavePackageForAsset(BP, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** BP_BpxTestStructuralComponents — M28.2.3 regression fixture baseline.
	 *  Empty Actor BP with no SCS-declared components (only the inherited
	 *  AActor DefaultSceneRoot slot that the engine materialises lazily
	 *  when the first authored child is attached). The inspect / soak gates
	 *  duplicate this into a scratch path and run `add_component_to_scs`
	 *  against it; the post-op asset must be byte-deterministic across
	 *  rounds (M28.pre.3 soak, exercising the `SeedGuidFromJoined(":scs:")`
	 *  path on `USCS_Node::VariableGuid`) and the rendered `.md` /
	 *  `.deep.md` must surface the new component (M28.pre.2 inspect).
	 *
	 *  Kept deliberately empty for the same reason as the other M28.2
	 *  fixtures: every seeded VariableGuid in the post-op asset comes from
	 *  the new SCS seeding path, not from pre-existing on-disk content. */
	FResult GenBP_BpxTestStructuralComponents()
	{
		FResult R; R.Name = TEXT("BP_BpxTestStructuralComponents");

		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }

		UBlueprint* BP = CreateBlueprint(Path, AActor::StaticClass());
		if (!BP) { R.Message = TEXT("CreateBlueprint returned null"); return R; }

		FBlueprintEditorUtils::MarkBlueprintAsModified(BP);
		if (!Compile(BP)) { R.Message = TEXT("compile failed"); return R; }

		FString Err;
		if (!SavePackageForAsset(BP, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** BP_BpxTestGraphNodes — M28.3.1 regression fixture baseline.
	 *  Empty Actor BP whose default EventGraph provides the target graph for
	 *  `add_branch_node`. The inspect / soak gates duplicate this to scratch
	 *  and spawn a Branch at a fixed position; the post-op asset must be
	 *  byte-deterministic across rounds (M28.pre.3 soak, exercising the
	 *  SeedGuidFromJoined(":branch:x,y") NodeGuid seed + the M26.1.2 pin-GUID
	 *  seeding on the fresh UK2Node_IfThenElse) and the rendered .md /
	 *  .deep.md must surface the new Branch (M28.pre.2 inspect).
	 *
	 *  Same rationale as the M28.2 structural fixtures: kept deliberately empty
	 *  so every seeded GUID in the post-op asset comes from the new
	 *  SeedGuidFromJoined(":branch:x,y") path, not from pre-existing on-disk
	 *  content. */
	FResult GenBP_BpxTestGraphNodes()
	{
		FResult R; R.Name = TEXT("BP_BpxTestGraphNodes");

		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }

		UBlueprint* BP = CreateBlueprint(Path, AActor::StaticClass());
		if (!BP) { R.Message = TEXT("CreateBlueprint returned null"); return R; }

		FBlueprintEditorUtils::MarkBlueprintAsModified(BP);
		if (!Compile(BP)) { R.Message = TEXT("compile failed"); return R; }

		FString Err;
		if (!SavePackageForAsset(BP, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** BP_BpxTestGraphNodesCalls — M28.3.2 regression fixture baseline.
	 *  Actor BP with one declared int member variable `TestCount` and one
	 *  declared void/void member function `DoTheThing`. Targets for the
	 *  self-context variants of `add_call_function_node` /
	 *  `add_variable_get_node` / `add_variable_set_node`.
	 *
	 *  Unlike the empty M28.2.x / M28.3.1 fixtures, this one declares a
	 *  variable + function at fixture-generation time. Rationale: the three
	 *  new M28.3.2 ops each require a resolvable self-member target to
	 *  materialise their signature-derived pin set; authoring these via the
	 *  commandlet at fixture-gen lets the inspect / soak gates target the
	 *  same names across replays without chaining ops in the plan (single-op
	 *  plan shape is hard-coded in inspect_harness / soak_template).
	 *
	 *  Determinism rationale: the pre-existing `TestCount` VarGuid and
	 *  `DoTheThing` GraphGuid + Entry NodeGuid are committed into the
	 *  .uasset at fixture-gen time. They DO NOT drift on CI runs because the
	 *  fixture is a committed binary asset — only `-Force` regen would
	 *  reassign them (and we don't run `-Force` in CI). The NEW seeded GUIDs
	 *  introduced by M28.3.2 ops come only from the SeedGuidFromJoined paths
	 *  these gates exercise, so the blast radius remains focused on the new
	 *  determinism machinery. */
	FResult GenBP_BpxTestGraphNodesCalls()
	{
		FResult R; R.Name = TEXT("BP_BpxTestGraphNodesCalls");

		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }

		UBlueprint* BP = CreateBlueprint(Path, AActor::StaticClass());
		if (!BP) { R.Message = TEXT("CreateBlueprint returned null"); return R; }

		AddIntVariable(BP, TEXT("TestCount"));

		// Blank void/void function named `DoTheThing`. Same pattern as the
		// M26.1 interface fixture's `GetTargetingInfo` creation, but with no
		// return node / user-defined pins — the default UK2Node_FunctionEntry
		// is sufficient for a void/void signature.
		UEdGraph* FnGraph = FBlueprintEditorUtils::CreateNewGraph(
			BP, FName(TEXT("DoTheThing")),
			UEdGraph::StaticClass(),
			UEdGraphSchema_K2::StaticClass());
		FBlueprintEditorUtils::AddFunctionGraph<UClass>(
			BP, FnGraph, /*bIsUserCreated=*/true, /*SignatureFromObject=*/(UClass*)nullptr);

		FBlueprintEditorUtils::MarkBlueprintAsModified(BP);
		if (!Compile(BP)) { R.Message = TEXT("compile failed"); return R; }

		FString Err;
		if (!SavePackageForAsset(BP, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** EQS_BpxTestBasic — M28.5.1 regression fixture baseline.
	 *  Empty `UEnvQuery` asset with zero options. The inspect / soak gates
	 *  duplicate this into a scratch path and run `add_eqs_option` against it,
	 *  targeting `/Script/AIModule.EnvQueryGenerator_ActorsOfClass` as the
	 *  concrete generator class. Post-op asset must be byte-deterministic
	 *  across rounds (M28.pre.3 soak, exercising the explicit `FName` on each
	 *  `NewObject<UEnvQueryOption>` / `NewObject<UEnvQueryGenerator>` that the
	 *  EQS bridge relies on instead of `FGuid::NewGuid()` — zero `FGuid` usage
	 *  across EQS classes per the M28.5.0 research) and the rendered `.deep.md`
	 *  must surface the new generator class via the M15 EnvQueryDeepRenderer.
	 *
	 *  Kept deliberately empty (zero options) so every authored option in the
	 *  post-op asset comes from the new bridge path, not from pre-existing
	 *  on-disk content.
	 *
	 *  BugHunt has zero EQS content shipped prior to this fixture — the M15
	 *  read-side ships "speculative" per that milestone's closure note; this
	 *  is the first EQS asset the project has to exercise against. */
	FResult GenEQS_BpxTestBasic()
	{
		FResult R; R.Name = TEXT("EQS_BpxTestBasic");

		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }

		const FString ShortName = ShortNameFromPath(Path);
		UPackage* Pkg = CreatePackage(*Path);
		if (!Pkg) { R.Message = TEXT("CreatePackage returned null"); return R; }
		Pkg->FullyLoad();

		UEnvQuery* EQS = NewObject<UEnvQuery>(Pkg, FName(*ShortName), RF_Public | RF_Standalone);
		if (!EQS) { R.Message = TEXT("NewObject<UEnvQuery> returned null"); return R; }

		FAssetRegistryModule::AssetCreated(EQS);
		EQS->MarkPackageDirty();

		FString Err;
		if (!SavePackageForAsset(EQS, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** EQS_BpxTestWithOption — M28.5.2 regression fixture.
	 *  Pre-seeded `UEnvQuery` with one option that already contains:
	 *    - generator: `EnvQueryGenerator_ActorsOfClass`
	 *    - tests[0]:  `EnvQueryTest_Random`
	 *  Enables inspect+soak for both new M28.5.2 ops from a single fixture:
	 *    - `add_eqs_test(option_index=0, test_class=EnvQueryTest_Distance)` →
	 *      idempotency key differs from pre-seeded Random, so the op runs.
	 *    - `remove_eqs_test(option_index=0, test_index=0)` → removes the
	 *      pre-seeded Random test.
	 *  Explicit `FName` on every `NewObject` call mirrors the M28.5.1 /
	 *  M28.5.2 bridge recipe so the fixture itself is byte-deterministic on
	 *  `-Force` regeneration (EQS classes have zero `FGuid::NewGuid()` usage;
	 *  counter-suffixed default names are the only drift source). */
	FResult GenEQS_BpxTestWithOption()
	{
		FResult R; R.Name = TEXT("EQS_BpxTestWithOption");

		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }

		const FString ShortName = ShortNameFromPath(Path);
		UPackage* Pkg = CreatePackage(*Path);
		if (!Pkg) { R.Message = TEXT("CreatePackage returned null"); return R; }
		Pkg->FullyLoad();

		UEnvQuery* EQS = NewObject<UEnvQuery>(Pkg, FName(*ShortName), RF_Public | RF_Standalone);
		if (!EQS) { R.Message = TEXT("NewObject<UEnvQuery> returned null"); return R; }

		// Pre-seed one option at index 0 with an ActorsOfClass generator and
		// one Random test. Explicit FName per M28.5.x determinism recipe.
		UEnvQueryOption* Option = NewObject<UEnvQueryOption>(
			EQS, TEXT("BpxEqsFixtureOption_0"), RF_Transactional);
		if (!Option) { R.Message = TEXT("NewObject<UEnvQueryOption> returned null"); return R; }

		UEnvQueryGenerator* Generator = NewObject<UEnvQueryGenerator>(
			Option, UEnvQueryGenerator_ActorsOfClass::StaticClass(),
			TEXT("BpxEqsFixtureGen_0_EnvQueryGenerator_ActorsOfClass"),
			RF_Transactional);
		if (!Generator) { R.Message = TEXT("NewObject<UEnvQueryGenerator> returned null"); return R; }
		Option->Generator = Generator;

		UEnvQueryTest* Test = NewObject<UEnvQueryTest>(
			Option, UEnvQueryTest_Random::StaticClass(),
			TEXT("BpxEqsFixtureTest_0_0_EnvQueryTest_Random"),
			RF_Transactional);
		if (!Test) { R.Message = TEXT("NewObject<UEnvQueryTest> returned null"); return R; }
		Test->TestOrder = 0;
		Option->Tests.Add(Test);

		EQS->GetOptionsMutable().Add(Option);

		FAssetRegistryModule::AssetCreated(EQS);
		EQS->MarkPackageDirty();

		FString Err;
		if (!SavePackageForAsset(EQS, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** Curve_BpxTestEmpty — M28.4.1 regression fixture baseline.
	 *  Empty `UCurveFloat` asset with zero keys. The set_curve_float_keys
	 *  inspect / soak gates duplicate this into a scratch path and populate
	 *  it with a 2-point curve; post-op asset must be byte-deterministic
	 *  across rounds (M28.pre.3 soak) and the rendered `.deep.md` must
	 *  surface the new keys via the Tier 1 / Tier 2 DataTable-family
	 *  rendering path (UCurveFloat falls through the generic handler
	 *  which still dumps the FRichCurve key array).
	 *
	 *  Kept deliberately empty (zero keys) so every authored key in the
	 *  post-op asset comes from the new SetCurveFloatKeys bridge path,
	 *  not from pre-existing on-disk content. Mirror of the EQS_BpxTestBasic
	 *  minimum-viable baseline recipe.
	 *
	 *  UCurveFloat / UCurveBase / FRichCurveKey have zero `FGuid::NewGuid()`
	 *  usage per the M28.4.0 research, so counter-suffixed default names
	 *  are the only drift source; explicit `FName` on `NewObject` is
	 *  sufficient (no seed-GUID recipe needed). */
	FResult GenCurve_BpxTestEmpty()
	{
		FResult R; R.Name = TEXT("Curve_BpxTestEmpty");

		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }

		const FString ShortName = ShortNameFromPath(Path);
		UPackage* Pkg = CreatePackage(*Path);
		if (!Pkg) { R.Message = TEXT("CreatePackage returned null"); return R; }
		Pkg->FullyLoad();

		UCurveFloat* Curve = NewObject<UCurveFloat>(
			Pkg, FName(*ShortName), RF_Public | RF_Standalone);
		if (!Curve) { R.Message = TEXT("NewObject<UCurveFloat> returned null"); return R; }

		FAssetRegistryModule::AssetCreated(Curve);
		Curve->MarkPackageDirty();

		FString Err;
		if (!SavePackageForAsset(Curve, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** DA_BpxTestParentClass — M28.4.2 regression fixture (parent class).
	 *  BP-derived `UPrimaryDataAsset` subclass declaring three BP-member
	 *  variables (`Intensity: int`, `Range: float`, `Label: FString`). Serves
	 *  as the GeneratedClass for DA_BpxTestInstance and as a structural
	 *  target for authoring new DA instances via `create_data_asset_instance`.
	 *
	 *  Why BP-derived rather than native C++: matches the "Data Only
	 *  Blueprints" authoring path Epic recommends (and the one real content
	 *  authors use — natively-declared DA subclasses require a module rebuild
	 *  per schema change, which is heavier than BP-authored tuning fields).
	 *  Also avoids a native fixture class in `BlueprintExporterTests` that
	 *  would need rebuild on every DLL bump.
	 *
	 *  Determinism: VarGuids are committed into the .uasset at fixture-gen
	 *  time (same as BP_BpxTestGraphNodesCalls) — only `-Force` regeneration
	 *  would reassign them, and we don't run `-Force` in CI. The authored
	 *  property names (`Intensity` / `Range` / `Label`) are the stable
	 *  targets `set_data_asset_property` resolves via FindFProperty on the
	 *  generated class. */
	FResult GenDA_BpxTestParentClass()
	{
		FResult R; R.Name = TEXT("DA_BpxTestParentClass");

		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }

		UBlueprint* BP = CreateBlueprint(Path, UPrimaryDataAsset::StaticClass());
		if (!BP) { R.Message = TEXT("CreateBlueprint returned null"); return R; }

		AddIntVariable(BP, TEXT("Intensity"));
		AddFloatVariable(BP, TEXT("Range"));
		AddStringVariable(BP, TEXT("Label"));

		FBlueprintEditorUtils::MarkBlueprintAsModified(BP);
		if (!Compile(BP)) { R.Message = TEXT("compile failed"); return R; }

		FString Err;
		if (!SavePackageForAsset(BP, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** DA_BpxTestInstance — M28.4.2 regression fixture (instance).
	 *  Empty instance of DA_BpxTestParentClass's GeneratedClass. The
	 *  inspect / soak gates duplicate this into a scratch path and mutate
	 *  the BP-declared `Intensity` variable; post-op asset must be
	 *  byte-deterministic across rounds and the rendered `.deep.md` /
	 *  `.meta.json` would surface the new value (skipped in CI because
	 *  UDataAsset isn't in the inventory pipeline's logic-bearing set per
	 *  PROJECT_INVENTORY_BRIEF.md §3).
	 *
	 *  Kept deliberately empty (no UPROPERTY overrides) so every authored
	 *  value in the post-op asset comes from the new SetPropertyValue path,
	 *  not from pre-existing on-disk content. Mirror of the Curve_BpxTestEmpty
	 *  / EQS_BpxTestBasic minimum-viable baseline recipe.
	 *
	 *  Requires DA_BpxTestParentClass to already exist on disk at generation
	 *  time — enforced by the order in the Gens array in Main() below
	 *  (parent BP appears before instance). UDataAsset / UPrimaryDataAsset
	 *  have zero `FGuid::NewGuid()` usage per the M28.4.0 research, so
	 *  counter-suffixed default names are the only drift source; explicit
	 *  `FName` on `NewObject` closes that. */
	FResult GenDA_BpxTestInstance()
	{
		FResult R; R.Name = TEXT("DA_BpxTestInstance");

		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }

		const FString ParentPath = FString::Printf(TEXT("%s/DA_BpxTestParentClass"), kFixturePackageRoot);
		const FString ParentShort = ShortNameFromPath(ParentPath);
		UBlueprint* ParentBP = LoadObject<UBlueprint>(nullptr, *(ParentPath + TEXT(".") + ParentShort));
		if (!ParentBP) { R.Message = TEXT("DA_BpxTestParentClass not loaded (must gen parent first)"); return R; }
		UClass* ParentClass = ParentBP->GeneratedClass;
		if (!ParentClass) { R.Message = TEXT("DA_BpxTestParentClass has no GeneratedClass"); return R; }

		const FString ShortName = ShortNameFromPath(Path);
		UPackage* Pkg = CreatePackage(*Path);
		if (!Pkg) { R.Message = TEXT("CreatePackage returned null"); return R; }
		Pkg->FullyLoad();

		UDataAsset* Asset = NewObject<UDataAsset>(
			Pkg, ParentClass, FName(*ShortName),
			RF_Public | RF_Standalone | RF_Transactional);
		if (!Asset) { R.Message = TEXT("NewObject<UDataAsset> returned null"); return R; }

		FAssetRegistryModule::AssetCreated(Asset);
		Asset->MarkPackageDirty();

		FString Err;
		if (!SavePackageForAsset(Asset, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** UDS_BpxTestEmpty — M28.4.3 regression fixture.
	 *  Minimal `UUserDefinedStruct` with two members:
	 *    - `BpxAutoBool : bool` — the engine's auto-added first member, renamed
	 *      for readability (CreateUserDefinedStruct assigns a `MemberVar`
	 *      placeholder; this fixture routes it through RenameVariable so the
	 *      committed .uasset reads `BpxAutoBool` in the struct editor).
	 *    - `BpxRemovalCandidate : int (default 7)` — a second member pre-seeded
	 *      so the `remove_uds_member` soak has something to delete (engine's
	 *      bAllowToMakeEmpty=false invariant refuses to leave the struct with
	 *      zero members, so the fixture must have at least 2 for remove soak
	 *      to succeed) and so `set_uds_member_default` soak has a target field
	 *      with a known pre-op value to mutate.
	 *
	 *  The `add_uds_member` soak targets a THIRD friendly name (e.g. `BpxAddCandidate`)
	 *  that is NOT pre-seeded here so round 1 genuinely adds + round 2 hits the
	 *  idempotent skip.
	 *
	 *  Determinism: VarGuids are committed into the .uasset at fixture-gen time
	 *  (same pattern as BP_BpxTestGraphNodesCalls / DA_BpxTestParentClass) —
	 *  only `-Force` regen would reassign them, and we don't run `-Force` in CI.
	 *  The authored friendly names (`BpxAutoBool` / `BpxRemovalCandidate`) are
	 *  the stable targets `remove_uds_member` / `set_uds_member_default` resolve
	 *  via `FStructureEditorUtils::GetVarDesc(Struct)` friendly-name walk on
	 *  the generated `UUserDefinedStructEditorData::VariablesDescriptions`
	 *  array.
	 *
	 *  Authoring path mirrors `CreateUserDefinedStructDeterministic` + two
	 *  `AddUserDefinedStructMember` calls (for BpxRemovalCandidate only — the
	 *  auto-bool is auto-added by the engine's CreateUserDefinedStruct). Does
	 *  NOT apply the bridge's determinism-seeding logic because committed
	 *  fixture bytes are frozen on disk; random GUIDs at commit time are fine
	 *  as long as the soak gate runs the bridge op (which DOES seed). */
	FResult GenUDS_BpxTestEmpty()
	{
		FResult R; R.Name = TEXT("UDS_BpxTestEmpty");

		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }

		const FString ShortName = ShortNameFromPath(Path);
		UPackage* Pkg = CreatePackage(*Path);
		if (!Pkg) { R.Message = TEXT("CreatePackage returned null"); return R; }
		Pkg->FullyLoad();

		// CreateUserDefinedStruct auto-adds a first bool member per engine
		// invariant (StructureEditorUtils.cpp:60). Rename it to a readable
		// friendly name so the struct editor / inventory dump isn't cluttered
		// with the engine's `MemberVar` placeholder.
		UUserDefinedStruct* UDS = FStructureEditorUtils::CreateUserDefinedStruct(
			Pkg, FName(*ShortName), RF_Public | RF_Standalone | RF_Transactional);
		if (!UDS) { R.Message = TEXT("CreateUserDefinedStruct returned null"); return R; }

		{
			TArray<FStructVariableDescription>& VarDescs = FStructureEditorUtils::GetVarDesc(UDS);
			if (VarDescs.Num() == 1)
			{
				FStructureEditorUtils::RenameVariable(UDS, VarDescs[0].VarGuid, TEXT("BpxAutoBool"));
			}
		}

		// Add BpxRemovalCandidate : int (default=7). AddVariable auto-generates
		// the VarGuid; we locate the new entry at the tail and route through
		// RenameVariable so the friendly name lands cleanly, then set the
		// default value via ChangeVariableDefaultValue.
		{
			FEdGraphPinType IntType;
			IntType.PinCategory = UEdGraphSchema_K2::PC_Int;

			TArray<FStructVariableDescription>& PreDescs = FStructureEditorUtils::GetVarDesc(UDS);
			const int32 PreCount = PreDescs.Num();
			if (FStructureEditorUtils::AddVariable(UDS, IntType))
			{
				TArray<FStructVariableDescription>& PostDescs = FStructureEditorUtils::GetVarDesc(UDS);
				if (PostDescs.Num() == PreCount + 1)
				{
					const FGuid NewVarGuid = PostDescs[PreCount].VarGuid;
					FStructureEditorUtils::RenameVariable(UDS, NewVarGuid, TEXT("BpxRemovalCandidate"));
					FStructureEditorUtils::ChangeVariableDefaultValue(UDS, NewVarGuid, TEXT("7"));
				}
			}
		}

		FAssetRegistryModule::AssetCreated(UDS);
		UDS->MarkPackageDirty();

		FString Err;
		if (!SavePackageForAsset(UDS, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}

	/** BP_BpxTestStructuralInterfaces — M28.2.4 regression fixture baseline.
	 *  Empty Actor BP with no implemented interfaces. The inspect / soak
	 *  gates duplicate this into a scratch path and run `add_bp_interface`
	 *  against it, targeting the existing `BPI_BpxTestInterface` (shared with
	 *  the M26.1 fixtures). Post-op asset must be byte-deterministic across
	 *  rounds (M28.pre.3 soak, exercising the GraphGuid + Entry/Return
	 *  NodeGuid + pin-GUID seed triad on the generated override graph) and
	 *  the rendered .md / .deep.md must surface the interface + the stub
	 *  override graph (M28.pre.2 inspect).
	 *
	 *  Same rationale as the other M28.2 fixtures: kept deliberately empty
	 *  so every seeded GUID in the post-op asset comes from the new
	 *  SeedGuidFromJoined(":iface_graph:", ":entry", ":return", per-pin)
	 *  paths, not from pre-existing on-disk content. */
	FResult GenBP_BpxTestStructuralInterfaces()
	{
		FResult R; R.Name = TEXT("BP_BpxTestStructuralInterfaces");

		const FString Path = FString::Printf(TEXT("%s/%s"), kFixturePackageRoot, *R.Name);
		if (FixtureOnDisk(Path) && !GForceRegenerate) { R.bSkipped = true; R.Message = TEXT("already on disk"); return R; }

		UBlueprint* BP = CreateBlueprint(Path, AActor::StaticClass());
		if (!BP) { R.Message = TEXT("CreateBlueprint returned null"); return R; }

		FBlueprintEditorUtils::MarkBlueprintAsModified(BP);
		if (!Compile(BP)) { R.Message = TEXT("compile failed"); return R; }

		FString Err;
		if (!SavePackageForAsset(BP, Err)) { R.Message = Err; return R; }
		R.bCreated = true;
		return R;
	}
}

UGenerateTestBlueprintsCommandlet::UGenerateTestBlueprintsCommandlet()
{
	IsClient = false;
	IsEditor = true;
	IsServer = false;
	LogToConsole = true;
}

int32 UGenerateTestBlueprintsCommandlet::Main(const FString& Params)
{
	using namespace BugHuntGen;

	UE_LOG(LogBlueprintExporterTests, Log, TEXT("[Gen] starting fixture generation"));

	FString OnlyFilter, TierFilter;
	FParse::Value(*Params, TEXT("Only="), OnlyFilter);
	FParse::Value(*Params, TEXT("Tier="), TierFilter);
	BugHuntGen::GForceRegenerate = FParse::Param(*Params, TEXT("Force"));

	struct FGen
	{
		TCHAR Tier;
		TFunction<FResult()> Func;
	};

	TArray<FGen> Gens = {
		{TEXT('C'), &GenBP_NodeZoo},
		{TEXT('C'), &GenBP_PinHell},
		{TEXT('C'), &GenBP_InheritanceChain},
		{TEXT('C'), &GenBP_SCSMonster},
		{TEXT('C'), &GenBP_MacroMania},
		{TEXT('C'), &GenBP_NetRep},
		{TEXT('C'), &GenBP_StructEnumZoo},
		{TEXT('C'), &GenBP_WidgetTree},
		{TEXT('A'), &GenBP_NPC_BehaviorTree},
		{TEXT('A'), &GenBP_NPC_Perception},
		{TEXT('A'), &GenBP_NPC_StateTree},
		{TEXT('A'), &GenBP_NPC_SmartObject},
		{TEXT('A'), &GenBP_GASP_AnimBP},
		{TEXT('B'), &GenBP_GAS_Ability},
		// M26.1 interface-override fixtures. BPI must generate before BP_
		// (the BP loads the interface class by path during setup).
		{TEXT('C'), &GenBPI_BpxTestInterface},
		{TEXT('C'), &GenBP_BpxTestImplementsInterface},
		// M28.2.1 structural-edit fixture. Empty baseline; the inspect/soak
		// gates author variables onto a scratch duplicate and assert
		// determinism + .md content.
		{TEXT('C'), &GenBP_BpxTestStructuralVariables},
		// M28.2.2 structural-edit fixture. Empty baseline; the inspect/soak
		// gates author a blank function graph onto a scratch duplicate and
		// assert GraphGuid + Entry/Return seeding holds byte-identity.
		{TEXT('C'), &GenBP_BpxTestStructuralFunctions},
		// M28.2.3 structural-edit fixture. Empty baseline; the inspect/soak
		// gates author an SCS component onto a scratch duplicate and assert
		// USCS_Node::VariableGuid seeding holds byte-identity.
		{TEXT('C'), &GenBP_BpxTestStructuralComponents},
		// M28.2.4 structural-edit fixture. Empty baseline; the inspect/soak
		// gates attach the existing BPI_BpxTestInterface onto a scratch
		// duplicate and assert GraphGuid + Entry/Return + pin-GUID seeding
		// on the generated override graph holds byte-identity.
		{TEXT('C'), &GenBP_BpxTestStructuralInterfaces},
		// M28.3.1 graph-authoring fixture. Empty baseline; the inspect/soak
		// gates spawn a UK2Node_IfThenElse (Branch) onto the default
		// EventGraph of a scratch duplicate and assert NodeGuid + pin-GUID
		// seeding holds byte-identity across rounds.
		{TEXT('C'), &GenBP_BpxTestGraphNodes},
		// M28.3.2 graph-authoring fixture. Actor BP with one declared int
		// variable (TestCount) + one declared void/void function (DoTheThing)
		// so the self-context CallFunction / VariableGet / VariableSet ops
		// have resolvable targets. The inspect/soak gates spawn each into
		// the default EventGraph and assert NodeGuid + pin-GUID seeding
		// holds byte-identity across rounds.
		{TEXT('C'), &GenBP_BpxTestGraphNodesCalls},
		// M28.5.1 EQS-authoring fixture. Empty UEnvQuery baseline; the
		// inspect/soak gates append a first option (generator only for
		// M28.5.1; tests ship in M28.5.2) onto a scratch duplicate and
		// assert explicit-FName determinism holds byte-identity across rounds.
		{TEXT('A'), &GenEQS_BpxTestBasic},
		// M28.5.2 EQS-authoring fixture. Pre-seeded with one option carrying
		// an ActorsOfClass generator + one Random test, so add_eqs_test and
		// remove_eqs_test inspect/soak gates both have a valid target from
		// a single fixture.
		{TEXT('A'), &GenEQS_BpxTestWithOption},
		// M28.4.1 CurveFloat-authoring fixture. Empty UCurveFloat baseline;
		// the set_curve_float_keys inspect/soak gates populate a scratch
		// duplicate with a 2-point curve and assert explicit-FName
		// determinism holds byte-identity across rounds.
		{TEXT('C'), &GenCurve_BpxTestEmpty},
		// M28.4.2 DataAsset-authoring fixtures. Parent class (BP-derived
		// UPrimaryDataAsset with three declared vars) + empty instance of
		// it. Parent MUST generate before instance — the instance's
		// NewObject needs the parent's GeneratedClass loaded. set_data_
		// asset_property soak targets the instance; create_data_asset_
		// instance soak creates a scratch instance of the parent class.
		{TEXT('C'), &GenDA_BpxTestParentClass},
		{TEXT('C'), &GenDA_BpxTestInstance},
		// M28.4.3 UserDefinedStruct-authoring fixture. UDS with two members
		// (BpxAutoBool + BpxRemovalCandidate:int=7); the inspect/soak gates
		// duplicate this into a scratch path and exercise the four UDS ops
		// (create / add_member / remove_member / set_member_default) on non-
		// overlapping identifiers. Pre-seeded second member is required because
		// remove_uds_member can't empty the struct (engine invariant).
		{TEXT('C'), &GenUDS_BpxTestEmpty},
	};

	int32 Created = 0, Skipped = 0, Failed = 0;
	TArray<FResult> Results;

	for (const FGen& G : Gens)
	{
		if (!TierFilter.IsEmpty())
		{
			const TCHAR Want = TierFilter[0];
			if (G.Tier != Want) continue;
		}
		FResult R;
		try { R = G.Func(); }
		catch (...) { R.Message = TEXT("exception"); }

		if (!OnlyFilter.IsEmpty() && !R.Name.Equals(OnlyFilter, ESearchCase::IgnoreCase)) continue;

		Results.Add(R);
		if (R.bCreated) { Created++; UE_LOG(LogBlueprintExporterTests, Display, TEXT("[Gen] OK    %s"), *R.Name); }
		else if (R.bSkipped) { Skipped++; UE_LOG(LogBlueprintExporterTests, Warning, TEXT("[Gen] SKIP  %s — %s"), *R.Name, *R.Message); }
		else { Failed++; UE_LOG(LogBlueprintExporterTests, Error, TEXT("[Gen] FAIL  %s — %s"), *R.Name, *R.Message); }

		// Collect garbage between fixtures so transient packages don't blow up memory.
		CollectGarbage(RF_NoFlags);
	}

	UE_LOG(LogBlueprintExporterTests, Display, TEXT("[Gen] done — created=%d skipped=%d failed=%d"), Created, Skipped, Failed);

	// Write a manifest of what was generated, for the report consolidator.
	TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
	TArray<TSharedPtr<FJsonValue>> Arr;
	for (const FResult& R : Results)
	{
		TSharedPtr<FJsonObject> O = MakeShared<FJsonObject>();
		O->SetStringField(TEXT("name"), R.Name);
		O->SetStringField(TEXT("status"), R.bCreated ? TEXT("created") : (R.bSkipped ? TEXT("skipped") : TEXT("failed")));
		O->SetStringField(TEXT("message"), R.Message);
		Arr.Add(MakeShared<FJsonValueObject>(O));
	}
	Root->SetArrayField(TEXT("fixtures"), Arr);
	Root->SetNumberField(TEXT("created"), Created);
	Root->SetNumberField(TEXT("skipped"), Skipped);
	Root->SetNumberField(TEXT("failed"), Failed);

	FString ReportStr;
	TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> W =
		TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&ReportStr);
	FJsonSerializer::Serialize(Root.ToSharedRef(), W);
	const FString ReportPath = FPaths::ProjectSavedDir() / TEXT("BugHunt") / TEXT("fixtures.json");
	IFileManager::Get().MakeDirectory(*FPaths::GetPath(ReportPath), true);
	FFileHelper::SaveStringToFile(ReportStr, *ReportPath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);

	return Failed == 0 ? EBlueprintExportExitCode::Success : EBlueprintExportExitCode::ValidationFailed;
}
