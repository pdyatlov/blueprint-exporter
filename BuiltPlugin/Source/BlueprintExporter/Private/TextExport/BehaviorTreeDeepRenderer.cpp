// Copyright 10 Chambers. All Rights Reserved.

#include "TextExport/BehaviorTreeDeepRenderer.h"
#include "TextExport/DeepDumpRenderer.h"
#include "TextExport/DeepRenderShared.h"

#include "UObject/Object.h"
#include "UObject/UnrealType.h"
#include "UObject/Class.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BTService.h"

namespace
{
	using BlueprintExporter::DeepRender::EscTbl;

	// BT-specific back-references that UBTNode populates at load time.
	// TreeAsset points back at the owning UBehaviorTree, ParentNode at the
	// owning composite, TemplateNode at the class-default template. Passed
	// to the shared RenderUObjectPropertiesTable as AdditionalPlumbing so
	// Tier 2 stays focused on authored configuration.
	const TSet<FName>& BTExtraPlumbing()
	{
		static const TSet<FName> Set = {
			FName(TEXT("TreeAsset")),
			FName(TEXT("ParentNode")),
			FName(TEXT("TemplateNode")),
		};
		return Set;
	}

	FString NodeLabel(const UBTNode* Node)
	{
		if (!Node)
		{
			return FString(TEXT("?"));
		}
		return Node->NodeName.IsEmpty() ? Node->GetName() : Node->NodeName;
	}

	// Render an aux list (decorators attached to a slot, or services attached
	// to a composite) as a titled sub-section with per-entry property tables.
	// Heading is passed in so callers can place it at the right nesting
	// level relative to the node that owns the list.
	template <typename TAuxArray>
	void RenderAuxList(FString& Md, const TAuxArray& List, const TCHAR* Kind, const TCHAR* Heading)
	{
		if (List.Num() == 0)
		{
			return;
		}
		Md += FString::Printf(TEXT("%s %s (%d)\n\n"), Heading, Kind, List.Num());
		for (int32 i = 0; i < List.Num(); ++i)
		{
			const UBTNode* Entry = List[i].Get();
			const FString Label = Entry ? NodeLabel(Entry) : FString(TEXT("?"));
			const FString Cls = Entry ? Entry->GetClass()->GetName() : FString(TEXT("?"));
			Md += FString::Printf(TEXT("**%s %d — `%s` — `%s`**\n\n"), Kind, i, *Label, *Cls);
			if (Entry)
			{
				const int32 N = BlueprintExporter::DeepRender::RenderUObjectPropertiesTable(Md, Entry, BTExtraPlumbing());
				if (N == 0)
				{
					Md += TEXT("_(no authored properties)_\n\n");
				}
			}
			else
			{
				Md += TEXT("_(null reference at export time)_\n\n");
			}
		}
	}

	// Render one node (composite or task) with its property table + attached
	// decorators (from its parent slot) + services (composites only). The
	// `NodeIndex` + `Depth` + `Path` fields in the heading block give each
	// node a stable identity without needing deep heading nesting (max H6
	// in Markdown would clamp fast on real trees).
	void RenderNodeBlock(
		FString& Md,
		const UBTNode* Node,
		int32 NodeIndex,
		int32 Depth,
		const FString& PathLabel,
		bool bIsComposite,
		const FBTCompositeChild* SlotDecorators)
	{
		const FString Kind = bIsComposite ? FString(TEXT("Composite")) : FString(TEXT("Task"));
		const FString Label = NodeLabel(Node);
		const FString Cls = Node ? Node->GetClass()->GetName() : FString(TEXT("?"));

		Md += FString::Printf(TEXT("### Node %d — %s — `%s`\n\n"), NodeIndex, *Kind, *Label);
		Md += TEXT("| Field | Value |\n|---|---|\n");
		Md += FString::Printf(TEXT("| Node class | `%s` |\n"), *EscTbl(Cls));
		Md += FString::Printf(TEXT("| Depth | %d |\n"), Depth);
		Md += FString::Printf(TEXT("| Path | %s |\n"), *EscTbl(PathLabel));
		Md += TEXT("\n");

		if (Node)
		{
			Md += TEXT("**Properties:**\n\n");
			const int32 N = BlueprintExporter::DeepRender::RenderUObjectPropertiesTable(Md, Node, BTExtraPlumbing());
			if (N == 0)
			{
				Md += TEXT("_(no authored properties)_\n\n");
			}
		}
		else
		{
			Md += TEXT("_(null node reference at export time)_\n\n");
			return;
		}

		// Decorators live on the parent composite's slot for this child — so
		// a task's decorators come from its parent slot, and a sub-composite
		// has decorators-from-slot PLUS its own services.
		if (SlotDecorators)
		{
			RenderAuxList(Md, SlotDecorators->Decorators, TEXT("Decorator"), TEXT("####"));
		}

		if (bIsComposite)
		{
			if (const UBTCompositeNode* Composite = Cast<UBTCompositeNode>(Node))
			{
				RenderAuxList(Md, Composite->Services, TEXT("Service"), TEXT("####"));
			}
		}
	}

	// Walk the tree, emitting one heading block per composite + task.
	// `SlotDecorators` is the parent composite's `FBTCompositeChild` for
	// this child (nullptr at the root). `NodeIndex` is a running counter so
	// consumers get a stable "Node 0 / Node 1 / …" numbering across the
	// whole dump, matching the order of traversal.
	void WalkTree(
		FString& Md,
		const UBTCompositeNode* Composite,
		int32 Depth,
		const FString& ParentPath,
		const FBTCompositeChild* SlotDecorators,
		int32& NodeIndex)
	{
		if (!Composite)
		{
			return;
		}

		const FString MyLabel = NodeLabel(Composite);
		const FString MyPath = ParentPath.IsEmpty()
			? MyLabel
			: FString::Printf(TEXT("%s → %s"), *ParentPath, *MyLabel);

		RenderNodeBlock(Md, Composite, NodeIndex++, Depth, MyPath, /*bIsComposite=*/true, SlotDecorators);

		for (const FBTCompositeChild& Child : Composite->Children)
		{
			if (Child.ChildComposite)
			{
				WalkTree(Md, Child.ChildComposite, Depth + 1, MyPath, &Child, NodeIndex);
			}
			else if (Child.ChildTask)
			{
				const UBTNode* TaskNode = Child.ChildTask;
				const FString TaskLabel = NodeLabel(TaskNode);
				const FString TaskPath = FString::Printf(TEXT("%s → %s"), *MyPath, *TaskLabel);
				RenderNodeBlock(Md, TaskNode, NodeIndex++, Depth + 1, TaskPath, /*bIsComposite=*/false, &Child);
			}
		}
	}

	FString DoRenderBehaviorTree(UBehaviorTree* BT)
	{
		FString Md;
		Md.Reserve(8 * 1024);

		Md += FString::Printf(TEXT("# %s — Deep Dump (Tier 2)\n\n"), *BT->GetName());
		Md += TEXT("> Generated by `DeepDump` for a BehaviorTree asset. Adds full UPROPERTY tables for every composite / task / decorator / service in the tree — Tier 1 records shape (class + instance name + nesting + attached-aux class names) but not the authored values like `AcceptableRadius` on a `BTTask_MoveTo`, `FlowAbortMode` on a `BTDecorator_Blackboard`, or `Interval` on a `BTService_DefaultFocus`. This is the Tier 2 complement.\n\n");

		// ---- Identity ----
		Md += TEXT("## Identity\n\n");
		Md += TEXT("| Field | Value |\n|---|---|\n");
		Md += FString::Printf(TEXT("| Asset path | `%s` |\n"), *EscTbl(BT->GetPathName()));
		Md += FString::Printf(TEXT("| Asset name | `%s` |\n"), *EscTbl(BT->GetName()));
		Md += TEXT("| Asset type | `BehaviorTree` |\n");
		UClass* Cls = BT->GetClass();
		UClass* ParentCls = Cls ? Cls->GetSuperClass() : nullptr;
		if (ParentCls)
		{
			Md += FString::Printf(TEXT("| Parent class | `%s` |\n"), *EscTbl(ParentCls->GetPathName()));
		}

		FString BlackboardPath;
		int32 BlackboardKeyCount = 0;
		if (const UBlackboardData* BB = BT->BlackboardAsset)
		{
			BlackboardPath = BB->GetPathName();
			BlackboardKeyCount = BB->Keys.Num();
		}
		Md += FString::Printf(TEXT("| Blackboard | %s |\n"),
			BlackboardPath.IsEmpty() ? TEXT("_none_") : *FString::Printf(TEXT("`%s`"), *EscTbl(BlackboardPath)));
		if (!BlackboardPath.IsEmpty())
		{
			Md += FString::Printf(TEXT("| Blackboard keys | **%d** |\n"), BlackboardKeyCount);
		}
		Md += TEXT("\n");

		// ---- Blackboard keys (full entry list — Tier 1 reports them but
		// only with name + key-class; here they're in the same section as
		// everything else so a consumer doesn't need both files open).
		if (BlackboardPath.IsEmpty())
		{
			Md += TEXT("## Blackboard Keys\n\n_No blackboard asset assigned._\n\n");
		}
		else if (BlackboardKeyCount == 0)
		{
			Md += TEXT("## Blackboard Keys\n\n_Blackboard has no keys._\n\n");
		}
		else
		{
			Md += FString::Printf(TEXT("## Blackboard Keys (%d)\n\n"), BlackboardKeyCount);
			// Keys keep their declaration order on the Blackboard asset —
			// changing order would shift blackboard indices at runtime.
			Md += TEXT("| Name | Key type | Instance synced |\n|---|---|---|\n");
			for (const FBlackboardEntry& Key : BT->BlackboardAsset->Keys)
			{
				const FString KeyName = Key.EntryName.ToString();
				const FString KeyType = Key.KeyType ? Key.KeyType->GetClass()->GetName() : FString(TEXT("?"));
				const FString Synced = Key.bInstanceSynced ? TEXT("yes") : TEXT("no");
				Md += FString::Printf(TEXT("| `%s` | `%s` | %s |\n"),
					*EscTbl(KeyName), *EscTbl(KeyType), *Synced);
			}
			Md += TEXT("\n");
		}

		// ---- Tree ----
		int32 NodeCount = 0;
		if (UBTCompositeNode* Root = BT->RootNode)
		{
			// Walk once first to get a node count for the header, then again
			// to render — cheap (no loads) and avoids back-patching the header.
			// Two separate walks keep traversal + render logic un-entangled.
			TFunction<void(const UBTCompositeNode*)> Count = [&](const UBTCompositeNode* C)
			{
				if (!C) return;
				++NodeCount;
				for (const FBTCompositeChild& Ch : C->Children)
				{
					if (Ch.ChildComposite)
					{
						Count(Ch.ChildComposite);
					}
					else if (Ch.ChildTask)
					{
						++NodeCount;
					}
				}
			};
			Count(Root);
		}

		if (NodeCount == 0)
		{
			Md += TEXT("## Tree\n\n_Empty tree (no root node)._\n\n");
			return Md;
		}

		// Root decorators: `UBehaviorTree::RootDecorators` holds decorators
		// that sit above the root composite (outside its `Children` slots).
		// These don't belong to any parent-slot so they're rendered as a
		// top-level sub-section above the tree walk.
		Md += FString::Printf(TEXT("## Tree (%d nodes)\n\n"), NodeCount);

		if (BT->RootDecorators.Num() > 0)
		{
			RenderAuxList(Md, BT->RootDecorators, TEXT("Root Decorator"), TEXT("###"));
		}

		int32 NodeIndex = 0;
		WalkTree(Md, BT->RootNode, /*Depth=*/0, /*ParentPath=*/FString(), /*SlotDecorators=*/nullptr, NodeIndex);

		return Md;
	}
}

namespace BlueprintExporter::DeepDump
{
	FString RenderBehaviorTreeMarkdown(UObject* BTObject)
	{
		UBehaviorTree* BT = Cast<UBehaviorTree>(BTObject);
		if (!BT)
		{
			// Fall through to the standard out-of-scope notice — preserves the
			// sibling-pattern uniformity for callers that always emit a
			// `<Asset>.deep.md` regardless of whether BT Tier 2 succeeded.
			return RenderOutOfScopeNotice(
				BTObject ? BTObject->GetName() : FString(TEXT("(null)")),
				BTObject ? BTObject->GetPathName() : FString(),
				TEXT("not UBehaviorTree"));
		}
		return DoRenderBehaviorTree(BT);
	}
}
