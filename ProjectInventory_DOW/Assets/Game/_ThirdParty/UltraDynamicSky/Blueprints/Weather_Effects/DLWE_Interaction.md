# DLWE_Interaction

## Identity

| Field | Value |
|---|---|
| Asset path | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/DLWE_Interaction.DLWE_Interaction` |
| Asset name | `DLWE_Interaction` |
| Subclass | `Blueprint` |
| Blueprint type | `Normal` |
| Engine version | `5.7.4-573521+++UE_DOW+main` |
| Plugin version | `1.28.6` |

## Inheritance

- Parent class: `NiagaraComponent` (`/Script/Niagara.NiagaraComponent`, native, module `/Script/Niagara`)
- Interfaces (1):
  - `/Script/Niagara.NiagaraParticleCallbackHandler`

## Variables (22)

| Name | Type | Default | Category | Replication | RepNotify | Flags |
|---|---|---|---|---|---|---|
| `Size` | `real<double>` | `24.000000` | `Settings` | — | — | InstanceEditable |
| `Interaction Settings` | `object<UDS_DLWE_Interaction_Settings_C>` | `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_DLWE_Interaction_Settings.UDS_DLWE_Interaction_Settings_C'/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Interaction_Settings/Standard_DLWE_Interaction_Settings.Standard_DLWE_Interaction_Settings'` | `Settings` | — | — | InstanceEditable |
| `Material Puddles` | `bool` | `False` | `System` | — | — | InstanceEditable, Private |
| `Snow Depth` | `real<double>` | `0.000000` | `System` | — | — | InstanceEditable, Private |
| `Dust Depth` | `real<double>` | `0.000000` | `System` | — | — | InstanceEditable, Private |
| `System Velocity` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `System` | — | — | InstanceEditable, Private |
| `Interaction Sound` | `object<AudioComponent>` | `None` | `System` | — | — | InstanceEditable, Private |
| `Puddle Fluid Depth` | `real<double>` | `0.000000` | `System` | — | — | InstanceEditable, Private |
| `Last Trace Location` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `System` | — | — | InstanceEditable, Private |
| `Hit Puddle Fluid Volume` | `bool` | `False` | `System` | — | — | InstanceEditable, Private |
| `Impacted Ground` | `mcdelegate` | `()` | `System` | — | — | InstanceEditable, Private |
| `Landscape Hit` | `struct<HitResult>` | `(Time=1.000000,Location=(X=0.000000,Y=0.000000,Z=0.000000),ImpactPoint=(X=0.000000,Y=0.000000,Z=0.000000),Normal=(X=0.000000,Y=0.000000,Z=0.000000),ImpactNormal=(X=0.000000,Y=0.000000,Z=0.000000),TraceStart=(X=0.000000,Y=0.000000,Z=0.000000),TraceEnd=(X=0.000000,Y=0.000000,Z=0.000000),MyItem=-1,HitObjectHandle=())` | `System` | — | — | InstanceEditable, Private |
| `Last Update Hit Landscape` | `bool` | `False` | `System` | — | — | InstanceEditable, Private |
| `Ground Location` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `System` | — | — | InstanceEditable, Private |
| `Ground Normal` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `System` | — | — | InstanceEditable, Private |
| `Run General Surface Impacts` | `bool` | `False` | `System` | — | — | InstanceEditable, Private |
| `Last Trace Velocity` | `struct<Vector>` | `(X=0.000000,Y=0.000000,Z=0.000000)` | `System` | — | — | InstanceEditable, Private |
| `Average Speed` | `real<double>` | `0.000000` | `System` | — | — | InstanceEditable, Private |
| `Sound Enabled` | `bool` | `False` | `System` | — | — | InstanceEditable, Private |
| `Asleep` | `bool` | `False` | `System` | — | — | InstanceEditable, Private |
| `UDW Ref Manager` | `object<UDW_Actor_Reference_Manager_C>` | `None` | `System` | — | — | InstanceEditable, Private |
| `DLWE System` | `softobject<NiagaraSystem>` | `/Game/_ThirdParty/UltraDynamicSky/Particles/DLWE_Interaction_System.DLWE_Interaction_System` | `System` | — | — | InstanceEditable, Private |

## Functions (18)

### `Check for Disable Phys Mats`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 26

### `Collision Trace Length`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> ReturnValue)`
- Local variables: _none_
- Nodes: 8

### `Draw Snow/Dust Trails`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (1): `Depth Fraction`
- Nodes: 46

### `General Surface Impact`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 11
- Category: `Default`

### `Impact Surface`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 22

### `Make Sound Component`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 33
- Category: `Default`

### `Play Puddle Splash Sound`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 14
- Category: `Default`

### `Puddle Impact`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 18
- Category: `Default`

### `Query Puddle Volume`

- Access: `Protected`
- Flags: —
- Inputs: `(TArray<struct<HitResult>> Hits)`
- Outputs: `()`
- Local variables (3): `Puddle Hit`, `Ground Height`, `Impacting Puddle`
- Nodes: 37
- Category: `Default`

### `Ripple Size`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `(real<double> Size)`
- Local variables: _none_
- Nodes: 9
- Category: `Default`

### `Self Activate`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

### `Self Deactivate`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 2

### `Sleep`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 9

### `Snow/Dust Impact`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 26
- Category: `Default`

### `Spawn Ripple`

- Access: `Protected`
- Flags: —
- Inputs: `(struct<Vector> Location, struct<Vector> Normal, real<double> Size)`
- Outputs: `()`
- Local variables: _none_
- Nodes: 7
- Category: `Default`

### `Trace for DLWE Surface`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables (4): `Hit`, `Hit Landscape`, `Hit Index`, `Hits`
- Nodes: 76
- Category: `Default`

### `Update Snow Trail Particles`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 10

### `Update Sound`

- Access: `Protected`
- Flags: —
- Inputs: `()`
- Outputs: `()`
- Local variables: _none_
- Nodes: 23

## Macros (0)

_None._

## Components (0)

_None (not an Actor Blueprint, or no SCS root)._

## Class Default Object (7)

- `bAffectDistanceFieldLighting` (`uint8`) = `False`
- `bAffectDynamicIndirectLighting` (`uint8`) = `False`
- `bAutoActivate` (`uint8`) = `False`
- `bEnableAutoLODGeneration` (`uint8`) = `False`
- `LightingChannels` (`FLightingChannels`) = `(bChannel0=False)`
- `OverrideParameters` (`FNiagaraUserRedirectionParameterStore`) = `()`
- `TickBehavior` (`ENiagaraTickBehavior`) = `ForceTickLast`

## Graphs

- Event graph: `EventGraph` (67 nodes)
- Construction script: `` (0 nodes)
- Additional graphs: _none_

## References

Hard refs out (15):
- `/Engine/EditorBlueprintResources/StandardMacros` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/System/UDW_Actor_Reference_Manager` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Ultra_Dynamic_Weather` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Interaction_Settings/Standard_DLWE_Interaction_Settings` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/Puddle_Fluid_Volume_Interface` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_DLWE_Interaction_Settings` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Particles/DLWE_Interaction_System` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Particles/Puddle_Ripple` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Particles/Puddle_Splash` [asset]
- `/Game/_ThirdParty/UltraDynamicSky/Sound/MetaSounds/UDS_DLWE_Interaction_Sounds` [asset]
- `/Script/AudioExtensions` [asset]
- `/Script/Landscape` [asset]
- `/Script/Niagara` [asset]
- `/Script/Niagara.NiagaraComponent` [native]
- `/Script/PhysicsCore` [asset]

Soft refs out (0):
- _none_

## Metadata & Flags

- Blueprint type: `Normal`
- Subclass: `Blueprint`
- Custom metadata: _none_

