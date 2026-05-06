# DefaultGeometrySurfacePropertiesTable

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/WwiseAudio/DefaultGeometrySurfacePropertiesTable.DefaultGeometrySurfacePropertiesTable` |
| Asset name | `DefaultGeometrySurfacePropertiesTable` |
| Asset type | `DataTable` |
| Row struct | `/Script/AkAudio.WwiseGeometrySurfacePropertiesRow` |
| Row count | **11** |
| Engine version | `5.7.4-573521+++UE_DOW+main` |

## Columns (2)

| Name | Type | Category | ToolTip |
|---|---|---|---|
| `AcousticTexture` | `TSoftObjectPtr<UAkAcousticTexture>` | `Geometry Surface Properties` | The Acoustic Texture associated with this row's Physical Material. A sound reflected on a surface is filtered according to the acoustic texture's absorption values. When estimating the Reverb of an environment, acoustic textures applied to the surfaces are used to estimate the environment's Decay and HF Damping. The default value is set to None. A surface with no acoustic texture is considered completely reflective. |
| `TransmissionLoss` | `float` | `Geometry Surface Properties` | The Transmission Loss value associated with this row's Physical Material. A sound going through a surface is filtered according to the amount of transmission loss. A surface with a transmission loss value of 0 is considered transparent and lets sound pass through without any filtering. Sound cannot reflect on such surfaces. The default value is set to 1, which is also the maximum possible value. |

## Row Names (11)

- `/Engine/EngineMaterials/DefaultDestructiblePhysicalMaterial.DefaultDestructiblePhysicalMaterial`
- `/Engine/EngineMaterials/DefaultPhysicalMaterial.DefaultPhysicalMaterial`
- `/Engine/EngineMaterials/LandscapeHolePhysicalMaterial.LandscapeHolePhysicalMaterial`
- `/Engine/EngineMaterials/PhysMat_Carboard.PhysMat_Carboard`
- `/Engine/EngineMaterials/PhysMat_Ice.PhysMat_Ice`
- `/Engine/EngineMaterials/PhysMat_Metal.PhysMat_Metal`
- `/Engine/EngineMaterials/PhysMat_Rubber.PhysMat_Rubber`
- `/Engine/EngineMaterials/PhysMat_Vehicle.PhysMat_Vehicle`
- `/Engine/EngineMaterials/PhysMat_VehicleRagdoll.PhysMat_VehicleRagdoll`
- `/Game/_ThirdParty/GASP_example/MetaHumans/Common/Materials/RigidBody_PhysicsMaterial.RigidBody_PhysicsMaterial`
- `/Water/DefaultPhysMat.DefaultPhysMat`

