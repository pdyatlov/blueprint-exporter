# BP_Vault

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/Art/EnvKits/Micro/Vaults/BP_Vault.BP_Vault` |
| Asset name | `BP_Vault` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `Actor` (`/Script/Engine.Actor`, native, module `/Script/Engine`)
- Interfaces: _none_

## Variables (6)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Open_Anim` | `object<AnimationAsset>` | `/Script/Engine.AnimSequence'/Game/Art/EnvKits/Micro/Vaults/Vault_Sphere_A/root_Door_Open.root_Door_Open'` | `Default` | — | — | InstanceEditable |
| `Door Skeletal Mesh` | `object<SkeletalMesh>` | `/Script/Engine.SkeletalMesh'/Game/Art/EnvKits/Micro/Vaults/Vault_Sphere_A/SKM_Vaults_Sphere_A_Door_01.SKM_Vaults_Sphere_A_Door_01'` | `Default` | — | — | InstanceEditable |
| `Frame Static Mesh` | `object<StaticMesh>` | `/Script/Engine.StaticMesh'/Game/Art/EnvKits/Micro/Vaults/Vault_Sphere_A/SM_Vaults_Sphere_A_Frame_01.SM_Vaults_Sphere_A_Frame_01'` | `Default` | — | — | InstanceEditable |
| `Interior Static Mesh Dummy` | `object<StaticMesh>` | `/Script/Engine.StaticMesh'/Game/Art/EnvKits/Micro/Vaults/Vault_Sphere_A/SM_Vaults_Sphere_A_Interior_01.SM_Vaults_Sphere_A_Interior_01'` | `Default` | — | — | InstanceEditable |
| `Vault Interior Level Instance` | `softobject<World>` | `/Game/Art/EnvKits/Micro/Vaults/Vault_Sphere_A/LI_Vault_Sphere_A_Interior_01.LI_Vault_Sphere_A_Interior_01` | `Default` | — | — | InstanceEditable |
| `Vault Props Level Instance` | `softobject<World>` | `/Game/Art/EnvKits/Micro/Vaults/Vault_Sphere_A/LI_Vault_Sphere_A_Props_01.LI_Vault_Sphere_A_Props_01` | `Default` | — | — | InstanceEditable |

## Functions (2)

### `Load Interior`

- Access: `Public`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

### `Start Open`

- Access: `Public`
- Flags: CallInEditor
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

## Macros (0)

_None._

## Components (1)

- `DefaultSceneRoot` — `SceneComponent` [root] @ socket `None`
  - `SKM_Door` — `SkeletalMeshComponent` @ socket `None`
  - `SM_Interior` — `StaticMeshComponent` @ socket `None`
  - `SM_Frame` — `StaticMeshComponent` @ socket `None`

## Class Default Object (1)

- `PrimaryActorTick` (`FActorTickFunction`) = `(bStartWithTickEnabled=False)`

## Graphs

- Event graph: `EventGraph` (14 nodes)
- Construction script: `UserConstructionScript` (10 nodes)
- Additional graphs: _none_

## References

Hard refs out (7):
- `/Game/Art/EnvKits/Micro/Vaults/Vault_Sphere_A/LI_Vault_Sphere_A_Interior_01` [asset]
- `/Game/Art/EnvKits/Micro/Vaults/Vault_Sphere_A/LI_Vault_Sphere_A_Props_01` [asset]
- `/Game/Art/EnvKits/Micro/Vaults/Vault_Sphere_A/root_Door_Open` [asset]
- `/Game/Art/EnvKits/Micro/Vaults/Vault_Sphere_A/SKM_Vaults_Sphere_A_Door_01` [asset]
- `/Game/Art/EnvKits/Micro/Vaults/Vault_Sphere_A/SM_Vaults_Sphere_A_Frame_01` [asset]
- `/Game/Art/EnvKits/Micro/Vaults/Vault_Sphere_A/SM_Vaults_Sphere_A_Interior_01` [asset]
- `/Script/Engine.Actor` [native]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

