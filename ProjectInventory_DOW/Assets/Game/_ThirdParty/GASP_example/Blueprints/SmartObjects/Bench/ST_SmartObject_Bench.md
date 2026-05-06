# ST_SmartObject_Bench

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/SmartObjects/Bench/ST_SmartObject_Bench.ST_SmartObject_Bench` |
| Asset name | `ST_SmartObject_Bench` |
| Asset type | `StateTree` |
| Schema | `GameplayInteractionStateTreeSchema` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Summary

- Root states: **1**
- Total states (incl. nested): **6**
- Global evaluators: **1**
- Global tasks: **0**
- Property bindings: **20**
- Unique FInstancedStruct node types: **4**

## Global Evaluators (1)

- `StateTreeBlueprintEvaluatorWrapper` (`StateTreeBlueprintEvaluatorWrapper`)

## States (1 root, 6 total)

- **Root** [State]
  - **Find Slot Location** [State]
    - Tasks (1): `StateTreeTask_FindSlotEntranceLocation` (`StateTreeTask_FindSlotEntranceLocation`)
    - **Move To Slot And Play Entry** [State]
      - Tasks (4): `StateTreeMoveToTask` (`StateTreeMoveToTask`), `StateTreeBlueprintTaskWrapper` (`StateTreeBlueprintTaskWrapper`), `StateTreeBlueprintTaskWrapper` (`StateTreeBlueprintTaskWrapper`), `StateTreeBlueprintTaskWrapper` (`StateTreeBlueprintTaskWrapper`)
      - Transitions (2):
        - OnStateSucceeded → `(next state)`
        - OnStateFailed → `ReleaseSlot`
    - **Play Loop** [State]
      - Tasks (1): `StateTreeBlueprintTaskWrapper` (`StateTreeBlueprintTaskWrapper`)
      - Transitions (1):
        - OnStateCompleted → `(next state)`
    - **Play Exit** [State]
      - Tasks (1): `StateTreeBlueprintTaskWrapper` (`StateTreeBlueprintTaskWrapper`)
      - Transitions (1):
        - OnStateCompleted → `(next state)`
    - **ReleaseSlot** [State]
      - Tasks (3): `StateTreeBlueprintTaskWrapper` (`StateTreeBlueprintTaskWrapper`), `StateTreeBlueprintTaskWrapper` (`StateTreeBlueprintTaskWrapper`), `StateTreeBlueprintTaskWrapper` (`StateTreeBlueprintTaskWrapper`)
      - Transitions (1):
        - OnStateCompleted → `(tree succeeded)`

## FInstancedStruct Node Types (4)

- `/Script/GameplayInteractionsModule.StateTreeTask_FindSlotEntranceLocation`
- `/Script/GameplayStateTreeModule.StateTreeMoveToTask`
- `/Script/StateTreeModule.StateTreeBlueprintEvaluatorWrapper`
- `/Script/StateTreeModule.StateTreeBlueprintTaskWrapper`

