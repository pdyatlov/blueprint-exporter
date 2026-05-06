# DefaultReverbAssignmentTable

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/WwiseAudio/DefaultReverbAssignmentTable.DefaultReverbAssignmentTable` |
| Asset name | `DefaultReverbAssignmentTable` |
| Asset type | `DataTable` |
| Row struct | `/Script/AkAudio.WwiseDecayAuxBusRow` |
| Row count | **3** |
| Engine version | `5.7.4-573521+++UE_DOW+main` |

## Columns (2)

| Name | Type | Category | ToolTip |
|---|---|---|---|
| `Decay` | `float` | `Reverb Assignment` | The number of seconds it takes for the sound reverberation in an environment to decay by 60 dB. |
| `AuxBus` | `TSoftObjectPtr<UAkAuxBus>` | `Reverb Assignment` | The Auxiliary Bus with a reverb effect to use for a chosen Decay value. |

## Row Names (3)

- `Aux_Area_Int_Large`
- `Aux_Area_Int_Medium`
- `Aux_Area_Int_Small`

