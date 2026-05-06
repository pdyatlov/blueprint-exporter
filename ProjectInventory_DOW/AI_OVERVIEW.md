# AI Overview

Every BehaviorTree, StateTree, and AIController-derived Blueprint in the Phase-1 scope. Cross-references the NPCs that hard-reference each AI asset.

## BehaviorTrees (0)

_None in scope._

## StateTrees (4)

| Asset | Schema | States | Evaluators | Global tasks | Referenced by |
|---|---|---:|---:|---:|---|
| `/Game/_ThirdParty/GASP_example/Blueprints/AI/StateTree/ST_NPC_SandboxCharacter_Patrol_Subtree` | `StateTreeAIComponentSchema` | 3 | 0 | 0 | 1: /Game/_ThirdParty/GASP_example/Blueprints/AI/StateTree/ST_NPC_SandboxCharacter_SmartObject |
| `/Game/_ThirdParty/GASP_example/Blueprints/AI/StateTree/ST_NPC_SandboxCharacter_SmartObject` | `StateTreeAIComponentSchema` | 8 | 0 | 0 | 1: /Game/_ThirdParty/GASP_example/Blueprints/AI/AIC_NPC_SmartObject |
| `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/Bench/ST_SmartObject_Bench` | `GameplayInteractionStateTreeSchema` | 6 | 1 | 0 | 1: /Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/Bench/SO_BenchDefinition |
| `/Game/Blueprints/AI/MassAI/ST_MassAI` | `MassStateTreeSchema` | 2 | 0 | 0 | _none_ |

## AIController-derived Blueprints (1)

| Asset | Parent | BT / ST referenced |
|---|---|---|
| `/Game/_ThirdParty/GASP_example/Blueprints/AI/AIC_NPC_SmartObject` | `/Script/AIModule.AIController` | /Game/_ThirdParty/GASP_example/Blueprints/AI/StateTree/ST_NPC_SandboxCharacter_SmartObject |

_EQS queries (`EnvQuery` assets) land in Phase 1 as of M3.2 — see individual `.md` pages for option/test detail. SmartObjectDefinition, BehaviorTree, and EnvQuery assets each ship full Tier 2 deep dumps (see their `.deep.md` pages) as of M11–M15; a dedicated rollup would duplicate that content without adding cross-asset signal._
