# ST_NPC_SandboxCharacter_SmartObject

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/GASP_example/Blueprints/AI/StateTree/ST_NPC_SandboxCharacter_SmartObject.ST_NPC_SandboxCharacter_SmartObject` |
| Asset name | `ST_NPC_SandboxCharacter_SmartObject` |
| Asset type | `StateTree` |
| Schema | `StateTreeAIComponentSchema` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Summary

- Root states: **1**
- Total states (incl. nested): **8**
- Global evaluators: **0**
- Global tasks: **0**
- Property bindings: **7**
- Unique FInstancedStruct node types: **2**

## States (1 root, 8 total)

- **Root** [State]
  - **Smart Object State** [State]
    - Transitions (1):
      - OnStateCompleted → `Patrol State`
    - **UsingSmartObj** [State]
      - Enter conditions (1): `StateTreeBlueprintConditionWrapper` (`StateTreeBlueprintConditionWrapper`)
      - **FindSmartObject** [State]
        - Tasks (2): `StateTreeBlueprintTaskWrapper` (`StateTreeBlueprintTaskWrapper`), `StateTreeBlueprintTaskWrapper` (`StateTreeBlueprintTaskWrapper`)
        - **ClaimSlot** [State]
          - Tasks (1): `StateTreeBlueprintTaskWrapper` (`StateTreeBlueprintTaskWrapper`)
          - **UseSmartObject** [State]
            - Tasks (1): `StateTreeBlueprintTaskWrapper` (`StateTreeBlueprintTaskWrapper`)
    - **Patrol State** [Group]
      - Transitions (1):
        - OnStateCompleted → `Smart Object State`
      - **Patrol** [LinkedAsset]
        - Transitions (1):
          - OnStateCompleted → `Smart Object State`

## FInstancedStruct Node Types (2)

- `/Script/StateTreeModule.StateTreeBlueprintConditionWrapper`
- `/Script/StateTreeModule.StateTreeBlueprintTaskWrapper`

