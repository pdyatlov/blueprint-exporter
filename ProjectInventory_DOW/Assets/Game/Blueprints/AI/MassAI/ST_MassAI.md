# ST_MassAI

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Blueprints/AI/MassAI/ST_MassAI.ST_MassAI` |
| Asset name | `ST_MassAI` |
| Asset type | `StateTree` |
| Schema | `MassStateTreeSchema` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Summary

- Root states: **1**
- Total states (incl. nested): **2**
- Global evaluators: **0**
- Global tasks: **0**
- Property bindings: **1**
- Unique FInstancedStruct node types: **2**

## States (1 root, 2 total)

- **Root** [State]
  - **Wander** [State]
    - Tasks (2): `MassZoneGraphFindWanderTarget` (`MassZoneGraphFindWanderTarget`), `MassZoneGraphPathFollowTask` (`MassZoneGraphPathFollowTask`)
    - Transitions (1):
      - OnStateCompleted → `Root`

## FInstancedStruct Node Types (2)

- `/Script/MassAIBehavior.MassZoneGraphPathFollowTask`
- `/Script/MassCrowd.MassZoneGraphFindWanderTarget`

