# ST_NPC_SandboxCharacter_Patrol_Subtree

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/AI/StateTree/ST_NPC_SandboxCharacter_Patrol_Subtree.ST_NPC_SandboxCharacter_Patrol_Subtree` |
| Asset name | `ST_NPC_SandboxCharacter_Patrol_Subtree` |
| Asset type | `StateTree` |
| Schema | `StateTreeAIComponentSchema` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Summary

- Root states: **1**
- Total states (incl. nested): **3**
- Global evaluators: **0**
- Global tasks: **0**
- Property bindings: **4**
- Unique FInstancedStruct node types: **3**

## States (1 root, 3 total)

- **FindRandomLocation** [State]
  - Tasks (2): `StateTreeBlueprintTaskWrapper` (`StateTreeBlueprintTaskWrapper`), `StateTreeBlueprintTaskWrapper` (`StateTreeBlueprintTaskWrapper`)
  - **MoveToRandomLocation** [State]
    - Tasks (1): `StateTreeMoveToTask` (`StateTreeMoveToTask`)
    - Transitions (1):
      - OnStateCompleted → `(next state)`
  - **Wait** [State]
    - Tasks (1): `StateTreeDelayTask` (`StateTreeDelayTask`)
    - Transitions (1):
      - OnStateSucceeded → `(tree succeeded)`

## FInstancedStruct Node Types (3)

- `/Script/GameplayStateTreeModule.StateTreeMoveToTask`
- `/Script/StateTreeModule.StateTreeBlueprintTaskWrapper`
- `/Script/StateTreeModule.StateTreeDelayTask`

