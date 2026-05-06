# sGameActorHeader

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Standards/GameActor/Data/sGameActorHeader.sGameActorHeader` |
| Asset name | `sGameActorHeader` |
| Asset type | `UserDefinedStruct` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |

## Fields (8)

| Name | Type | Category | ToolTip |
|---|---|---|---|
| `GameActorID_2_4B8A74844ABC114F1FA4B5AB426A9673` | `int32` | — | Either baked into map or created dynamically, this ID is used to STORE/RECALL data. |
| `Dynamicallycreated_9_8F5AE0FF48E38B894351DA845EA53D61` | `bool` | — | Does this need to spawn before we feed the recall data to it. |
| `GameActorPrefabIndex_22_5B4501E24C00D66AE136B693D0C8D97D` | `UClass*` | — | The is the class reffefnce to the Blueprint to spawn to recreate the GameActor |
| `AdditionalDataCount_35_072CC1FF4A4607005D668D931569DB0B` | `uint8` | — | How many packets of data did we store for recall. |
| `StorageDataIndex_15_2988401A4273E62BFA634A99A1B7513E` | `int32` | — | At what index is the RECALL data kept for this GameActor |
| `Position_26_D2EC07A04CDB090FF25C539C1CD573FA` | `FVector` | — | — |
| `Rotation_30_0EB78416460781DDA3070A9AE1885193` | `FRotator` | — | — |
| `Keyframes_33_9E19B41E412FEB4A28F48C8709BB92B2` | `FsFourBytes` | — | — |

