# python_ops Catalog

LLM-facing op reference. Every op runs through UE's own save / compile paths
via the `unreal` Python API — no JSON round-trip, no deserializer. Use this
as the default write mechanism for Claude-driven asset edits on UE projects.

For orchestrating multiple ops as a single reviewable edit, see the
EditPlan schema in `plans/README.md` (M24.0) — it defines the JSON shape
consumed by the validator / executor / diff-oracle triple on top of this
library.

## Invocation pattern

```python
import sys, unreal
sys.path.insert(0, r"D:/Work/blueprintexporter/blueprint-exporter/scripts")
from python_ops import set_bp_variable_default  # plus any other ops used

result = set_bp_variable_default(
    bp_path="/Game/Path/To/BP",
    var_name="SomeVariable",
    value=unreal.Vector2D(1.0, 2.0),
)
```

Run the resulting script via:

```
UnrealEditor-Cmd.exe <uproject> -run=pythonscript -script="<script.py>" \
    -nullrhi -unattended -nopause -nosplash -nosound -stdout
```

## Op result shape

Every op returns a dict:

```python
{
    "success": bool,           # True iff the op did what it promised
    "op": str,                 # op name, for logging
    "target": str,             # asset path touched
    "field": str,              # variable / property name (if applicable)
    "before": Any,             # value pre-op
    "after": Any,              # value post-op
    "errors": List[str],       # empty on success; human-readable messages on fail
    "skipped": str,            # optional; present when op was a no-op
                               # (e.g. "value already matches")
}
```

Ops are **idempotent**: calling with the same value twice is a no-op on the
second call (no save, no md5 drift). Detected by comparing `before` to the
requested value.

## Value type mapping

Most UE types map cleanly from Python:

| UE type | Python |
|---|---|
| `int` / `int32` / `int64` | plain `int` |
| `float` / `double` (real) | plain `float` |
| `bool` | plain `bool` |
| `FString` / `FName` / `FText` | plain `str` |
| `FVector2D` | `unreal.Vector2D(x, y)` |
| `FVector` | `unreal.Vector(x, y, z)` |
| `FRotator` | `unreal.Rotator(roll, pitch, yaw)` |
| `FLinearColor` | `unreal.LinearColor(r, g, b, a)` |
| Enum | `unreal.ECollisionChannel.ECC_PAWN` etc. |
| Object/asset reference | `unreal.load_asset("/Game/...")` |
| `TArray<T>` | Python list; UE coerces on set |

## Available ops (M21.0 + M23.2 + M25.2 + M26.1 + M26.1.1 + M28.x)

### `set_bp_variable_default(bp_path, var_name, value)`

Set the default of a BP-declared My-Blueprint variable on the generated
class's CDO. Recompiles + saves. Idempotent.

```python
set_bp_variable_default(
    "/Game/CombatPrototype/DrewPrototype/ActorComponents/AC_AIWeaponController",
    "Damage", 8.0,
)
```

Covers BP-authored variables. For C++-inherited component fields use
`set_component_property`. For nested instanced subobjects (e.g. individual
sense configs inside AIPerception) use `set_instanced_subobject_property`.

### `set_component_property(bp_path, component_name, property_name, value)`

Set a flat UPROPERTY on an SCS component template. Resolves the component by
its variable name (as it appears in the Components panel). Recompiles + saves.
Idempotent.

```python
set_component_property(
    "/Game/CombatPrototype/DrewPrototype/BP_EnemyBase_AIController",
    "AIPerception", "bAutoActivate", True,
)
```

For BP-added SCS components. Fails with a clear error if the component name
doesn't match. The error message lists available component names to help
diagnose typos.

### `set_instanced_subobject_property(bp_path, path, property_name, value)`

Walk a path of components / properties / array indices from an SCS component,
then set `property_name` on the leaf object. Recompiles + saves. Idempotent.

```python
# Tune AIPerception.SensesConfig[0].SightRadius
set_instanced_subobject_property(
    "/Game/CombatPrototype/DrewPrototype/BP_EnemyBase_AIController",
    path=["AIPerception", "SensesConfig", 0],
    property_name="SightRadius",
    value=1500.0,
)
```

Path elements are resolved in order: string → `get_editor_property`, int →
array index. The first element must be an SCS component name. Works because
instanced subobjects are held by-reference in UE (UObject pointers), so
Python edits propagate back to the component template that owns them.

### `create_blueprint_class(parent_path, new_bp_path)` *(M28.10.1)*

Create a new Blueprint with either a native or BP parent class. Closes the
design.md gap surfaced by the M28.10.0 research outcome: pre-M28.10.1,
`create_child_bp` only handled BP parents, so `BP_EncounterDirector`
(parent `AActor`) and `UAIActionScorer` (parent `UActorComponent`) couldn't
be authored end-to-end via MCP. Accepts:

- Native classes: `/Script/<Module>.<ClassName>`
  (e.g. `/Script/Engine.Actor`, `/Script/Engine.ActorComponent`).
- BP generated classes: `/Game/<path>/<Name>.<Name>_C`.
- BP asset shorthand: `/Game/<path>/<Name>` — auto-suffixes `.{Name}_C`.

```python
create_blueprint_class(
    parent_path="/Script/Engine.Actor",
    new_bp_path="/Game/Runtime/AI/BP_EncounterDirector",
)
create_blueprint_class(
    parent_path="/Game/CombatPrototype/DrewPrototype/BP_EnemyBase",
    new_bp_path="/Game/Runtime/AI/BP_EnemyBase_Team1",
)
```

Idempotent on `(new_bp_path, parent_path)` with **strict ParentClass match**
via the C++ bridge (pointer equality on `Existing->ParentClass`). A BP
existing at the path with a *different* parent surfaces as a structured
error rather than a silent skip.

Determinism: the bridge UFUNCTION reseeds the documented FGuid trapdoors
that fire on fresh `FKismetEditorUtilities::CreateBlueprint` —
`UBlueprint::BlueprintGuid` (private UPROPERTY on `UBlueprintCore`,
seeded via FProperty reflection), `UPackage::PersistentGuid`, every
`UEdGraph::GraphGuid` on UCS + EventGraph, and the UCS
`K2Node_FunctionEntry`'s NodeGuid + pin ids. To remove a class of
auto-generated random state we couldn't fully tame, the bridge also
suppresses `UBlueprintEditorSettings::bSpawnDefaultBlueprintNodes` for
the duration of the create call so default events (BeginPlay / Tick /
etc.) are not spawned — plan authors add events explicitly via
`add_custom_event_node` (M28.3.3) which has its own deterministic
NodeGuid + PinId seeding. See `WIP_INVENTORY.md § M28.10.0 research
outcome` for the full trapdoor catalog and seeding recipe.

**Residual drift (known limitation):** even with all documented seeds in
place, two consecutive in-process runs of the create path produce
.uasset files that differ by ~16 bytes (one FGuid) somewhere in the
post-export annotation table or asset-registry tag block — source not
yet pinpointed. Production usage is single-create per BP path so the
residual is benign; two runs of `apply_plan` against the same plan
produce nearly-identical files and the same DeepDump output. Soak
verification uses the M28.4.x idempotence-only pattern (the duplicate
pre-places the asset and the op short-circuits via the
parent-class-match skip path). The M28.10.1 soak-harness extension
`soak.recreate_between_rounds: true` is preserved in
`scripts/soak_template.py` for any future op that wants stricter
create-path soak coverage; combined with `evict_in_memory=True` in
`_file_level_delete` it lets a soak fixture run round 1..N each
genuinely creating from scratch.

### `create_child_bp(parent_bp_path, new_bp_path)`

**M28.10.1 back-compat alias** for `create_blueprint_class`. Existing plans
authored against this name continue to work unchanged. New plans should
prefer `create_blueprint_class` directly, which also accepts native
parents. The alias forwards `parent_bp_path` (expected to be a BP asset
path under `/Game/`) to `create_blueprint_class` after the same `_C`
suffix normalization.

Idempotence is now stricter than the pre-M28.10.1 behaviour: parent-class
match is verified via C++ pointer equality, so an existing BP at
`new_bp_path` with a different parent now surfaces as an error rather
than a silent skip (closes the pre-M28.10.1 caveat that had to fall back
to "asset exists and is a Blueprint" because the Python binding didn't
expose `BlueprintGeneratedClass.get_super_class` reliably).

```python
create_child_bp(
    "/Game/CombatPrototype/DrewPrototype/BP_EnemyBase",
    "/Game/Runtime/AI/BP_EnemyBase_Team1",
)
```

Use case: team variants with pre-set faction overrides — follow with
`set_bp_variable_default(new_bp_path, "Faction", 1)`.

### `rename_asset(old_path, new_path)`

Rename (move) an asset. Idempotent if already at the destination.

```python
rename_asset(
    "/Game/Loadout/BP_Rifle",
    "/Game/Weapons/BP_Rifle_AR1",
)
```

Refuses to overwrite an existing destination. For deletions (including
cleanup after renames), use `unreal.EditorAssetLibrary.delete_asset`
directly — delete is not wrapped in the op library since the risk/benefit
profile doesn't justify a library entry.

### `add_statetree_enter_condition(st_path, state_path, condition_bp_path)` *(M23.2)*

Append a Blueprint-backed condition to a state's `EnterConditions` array.
Goes through the M23 reflection bridge because UE 5.7's Python reflection
marks `SubTrees` / `EnterConditions` / `Transitions` as protected.

```python
add_statetree_enter_condition(
    st_path="/Game/CombatPrototype/DrewPrototype/ST_EnemyBase",
    state_path=["SubTrees", "[2]", "Children", "[3]"],   # Peek
    condition_bp_path="/Game/CombatPrototype/DrewPrototype/ST_Cond_CanSeeTarget",
)
```

`state_path` is the navigation list from `StateTreeEditorData` to the
target `UStateTreeState`. Use the existing
`get_property_value(ed, ["SubTrees", "[N]", "Name"])` probe idiom to map
names to paths up-front — UE 5.7 does not expose a state-by-name lookup.

Idempotent by class: if an `EnterCondition` already has an `InstanceObject`
of the condition BP's generated class, returns success with a `skipped`
reason. Safe to call from a plan executor without a pre-flight existence
check.

### `remove_statetree_enter_condition(st_path, state_path, condition_bp_path)` *(M23.2)*

Symmetric to `add_`. Removes the first entry whose `InstanceObject` is of
the condition BP's generated class. No-op with `skipped` when none match.

```python
remove_statetree_enter_condition(
    st_path="/Game/CombatPrototype/DrewPrototype/ST_EnemyBase",
    state_path=["SubTrees", "[2]", "Children", "[3]"],
    condition_bp_path="/Game/CombatPrototype/DrewPrototype/ST_Cond_CanSeeTarget",
)
```

### `verify_state_enter_conditions(st_path, state_path)` *(M25.2.0)*

Read the current `EnterConditions` list at a state. Read-only — no
compile, no save, no mutation. `after` carries:

```
{
  "ec_len": N,
  "entries": [
    {"idx": 0, "class_path": "/Game/.../Cond_C", "instance_path": "..."}
  ]
}
```

```python
verify_state_enter_conditions(
    st_path="/Game/CombatPrototype/DrewPrototype/ST_EnemyBase",
    state_path=["SubTrees", "[2]"],   # root-state CombatLoop (works too)
)
```

Canonical read-back for a state's EnterConditions. Raw
`verification[]` `path` entries of the form
`[<st>, "StateTreeEditorData:SubTrees", ..., "InstanceObject"]` do
not resolve through the bridge's path walker — the colon notation was
only ever a doc convention and `BpxReflectionOps::ResolvePath` walks
one UPROPERTY per step. Use this op inside `operations[]` instead: it
takes the same `state_path` nav list as `add_` / `remove_`, walks the
asset via `find_subobject` + op-side helpers, and captures the live EC
list in the run report. Works uniformly for root (`["SubTrees", "[2]"]`)
and nested (`["SubTrees", "[2]", "Children", "[3]"]`) states.

### `add_statetree_transition(st_path, state_path, trigger, target_state_path, priority="Normal", event_tag="")` *(M25.2.1)*

Append an `FStateTreeTransition` to a state's `Transitions` array so the
state can flow to another state on a given trigger. Same reflection-bridge
rationale as the enter-condition ops — `Transitions` is protected in UE
5.7's Python layer.

```python
add_statetree_transition(
    st_path="/Game/CombatPrototype/DrewPrototype/ST_EnemyBase",
    state_path=["SubTrees", "[1]", "Children", "[1]"],   # SearchClueLoop.MoveToClue
    trigger="OnStateSucceeded",
    target_state_path=["SubTrees", "[2]"],               # CombatLoop (root)
)
```

`target_state_path` is resolved read-only: the op reads the target state's
`ID` (FGuid) + `Name` (FName) and writes them into the new transition's
`FStateTreeStateLink` with `LinkType=GotoState`. Non-`GotoState` link types
(`Succeeded` / `Failed` / `NextState` / `NextSelectableState` / `None`) are
not yet supported — author them manually in the StateTree editor for now.

`trigger` must be one of `OnStateCompleted` / `OnStateSucceeded` /
`OnStateFailed` / `OnTick` / `OnEvent`. `priority` accepts the standard
`Critical` / `High` / `Normal` / `Low`. For `OnEvent` transitions pass the
gameplay tag name (e.g. `"AI.TargetSpotted"`) in `event_tag`; required for
`OnEvent`, must be empty otherwise.

Idempotent by `(Trigger, State.ID[, EventTag])`: if an identical transition
already exists on the source state, returns success with a `skipped`
reason. The transition's own `ID` (FGuid) is seeded deterministically from
the op inputs so repeat runs produce byte-stable output modulo UE's own
save cosmetics.

### `remove_statetree_transition(st_path, state_path, trigger, target_state_path)` *(M25.2.1)*

Symmetric to `add_`. Removes the first `Transitions[]` entry whose
`Trigger` + `State.ID` match the given pair. No-op with `skipped` when
none match.

```python
remove_statetree_transition(
    st_path="/Game/CombatPrototype/DrewPrototype/ST_EnemyBase",
    state_path=["SubTrees", "[1]", "Children", "[1]"],
    trigger="OnStateSucceeded",
    target_state_path=["SubTrees", "[2]"],
)
```

### `verify_state_transitions(st_path, state_path)` *(M25.2.1)*

Read-only dump of a state's `Transitions` list. Mirrors
`verify_state_enter_conditions`. `after` carries:

```
{
  "t_len": N,
  "entries": [
    {"idx": 0, "trigger": "OnStateSucceeded",
     "target_guid": "...", "target_name": "CombatLoop",
     "link_type": "GotoState", "priority": "Normal"}
  ]
}
```

```python
verify_state_transitions(
    st_path="/Game/CombatPrototype/DrewPrototype/ST_EnemyBase",
    state_path=["SubTrees", "[1]", "Children", "[1]"],
)
```

### `implement_interface_function(bp_path, interface_bp_path, function_name, output_bindings, force_rebind=False)` *(M26.1, `force_rebind` M26.1.1)*

Create an interface-function override on `bp_path` and wire its Return
pins to BP member variables (self-context) or literal defaults. Composes
the M26.1 bridge primitives (`OverrideInterfaceFunction` + `FindGraphEndpoints`
+ `AddSelfMemberGetNode` + `ConnectPinsByName` + `SetNodePinLiteralDefault`
+ `CompileAndSavePackage`) into a single EditPlan-driven edit.

The motivating case: `BP_EnemyBase` in Legacy's `CombatPrototype` declares
`BPI_Targetable` but has no `GetTargetingInfo` override, so UE's message-
call returns defaults (`bIsAlive=false`, `Faction=0`) for every call, and
the combat behaviour tree never classifies anyone as hostile. A 3-pin
passthrough override (`bIsAlive=self.bIsAlive`, `bIsTargetable=true`,
`Faction=self.Faction`) fixes the bug — this op performs exactly that
class of edit, idempotently.

```python
implement_interface_function(
    bp_path="/Game/CombatPrototype/DrewPrototype/BP_EnemyBase",
    interface_bp_path="/Game/CombatPrototype/DrewPrototype/BPI_Targetable",
    function_name="GetTargetingInfo",
    output_bindings={
        "bIsAlive":      "self.bIsAlive",   # VariableGet passthrough
        "bIsTargetable": "true",             # literal default on Return.bIsTargetable
        "Faction":       "self.Faction",    # VariableGet passthrough
    },
)
```

Per-binding semantics:
  - `"self.<VarName>"` — op adds a `UK2Node_VariableGet` bound to the
    named BP-member variable (self context), then wires
    `Get.<VarName>.OUT` → `Return.<pin>.IN`. Get nodes are placed
    deterministically in a left column of the graph (`-400, 100*index`).
  - any other string — op sets the Return pin's `DefaultValue` literal
    via `UEdGraphSchema_K2::TrySetDefaultValue`; UE coerces per pin type
    (`"true"` / `"false"` for bool, `"42"` for int, struct importtext
    for FVector etc.).

Idempotence: if the override graph already exists on `bp_path`, the op
returns `success=True, skipped=<reason>` without touching bindings.
To replace bindings on an existing override, pass `force_rebind=True`
(M26.1.1) — the op then wipes every non-Entry / non-Return node out of
the existing graph and re-runs the binding logic on a clean slate.
Entry / Return keep their seeded NodeGuids so downstream references by
GUID stay stable. `after.wiped_nodes` records the removed-node count.

The `force_rebind` path also unblocks the most common authoring mistake
this op surfaces in practice: the editor auto-creates a stub override
the moment you click "add function" on an interface in the UI, and the
default-False idempotency check mistakes that stub for a completed
authoring pass. Pre-M26.1.1 the only workaround was to delete the
override graph by hand in the editor; now `force_rebind=True` handles
it in the plan.

Invariants the op enforces before touching the asset:
  - `bp_path` must be a `Blueprint` under `/Game/`.
  - `interface_bp_path` must be a `Blueprint` whose generated class is the
    one named on `bp_path->ImplementedInterfaces`. Adding an interface to
    a BP is a separate concern (do it in the editor or via a future op).
  - `function_name` must exist on the interface's generated class.

Pin-name conventions (hidden from plan authors by the op, documented
here for debugging):
  - Entry's execution output pin is `"then"`.
  - Return's execution input pin is `"execute"`. The op auto-wires
    Entry.then → Return.execute on first creation.
  - `UK2Node_VariableGet` output pin is named after the variable.
  - Return's data input pin is named per the interface signature and
    must match the `output_bindings` key.

The M26.1 bridge forces creation of a `UK2Node_FunctionResult` node on
interface overrides when the interface's UFunction has any `CPF_OutParm`
or `CPF_ReturnParm` properties — UE's `AddFunctionGraph` for interface
overrides doesn't auto-add a Return node. Without the force-create,
Get-node outputs can't wire into Entry's pins (which UE renders as
EGPD_Output direction, producing a "both OUTPUT" schema rejection).

BugHunt regression fixtures (`BugHunt/TestProject/Content/TestBlueprints/`):
  - `BPI_BpxTestInterface` — interface with `GetTargetingInfo` (bool /
    bool / int outputs).
  - `BP_BpxTestImplementsInterface` — baseline actor BP with the interface
    declared but no override.
  - `BP_BpxTestImplementsInterface_Expected` — post-op golden, generated
    by `scripts/regenerate_m26_1_golden.py`. Regenerate with `-Force` if
    the fixture shape changes; UE .uasset saves aren't byte-deterministic
    at pin-GUID granularity so golden comparison is semantic (DeepDump-
    level), not byte-level.

### `add_statetree_task_to_state(st_path, state_path, task_bp_path)` *(M28.1)*

Append a Blueprint-backed task to a state's `Tasks` array. Mirrors
`add_statetree_enter_condition` — the wrapper struct is
`FStateTreeBlueprintTaskWrapper` (field `TaskClass`) instead of
`FStateTreeBlueprintConditionWrapper` (field `ConditionClass`); the
array is `Tasks` instead of `EnterConditions`. Idempotent: skips when
the state already carries a task whose `InstanceObject` is of the
requested BP's generated class.

```python
result = add_statetree_task_to_state(
    st_path="/Game/CombatPrototype/DrewPrototype/ST_EnemyBase",
    state_path=["SubTrees", "[2]", "Children", "[1]"],  # CombatLoop
    task_bp_path="/Game/CombatPrototype/DrewPrototype/BP_Task_OpenFireLoop",
)
```

Motivating case: in the Flat Arena diagnosis, `ST_EnemyBase` referenced
`BP_Task_OpenFireLoop` as an asset but never attached it to the
`CombatLoop` state — firing only happened as a side effect of
`BP_Task_Peek`, which in turn was gated on a dead-end Branch (see
`connect_graph_pins` below). Adding `OpenFireLoop` as a task on
`CombatLoop` is the "NPCs actually fire" fix.

### `remove_statetree_task_from_state(st_path, state_path, task_bp_path)` *(M28.1)*

Remove the first `Tasks[]` entry on `state_path` whose `InstanceObject`
is of `task_bp_path`'s generated class. No-op (success with `skipped`)
when no matching entry exists.

### `verify_state_tasks(st_path, state_path)` *(M28.1)*

Read-only snapshot of the current `Tasks` list at a state. Returns
`{task_len, entries: [{idx, class_path, instance_path}]}`. Use alongside
`verify_state_enter_conditions` / `verify_state_transitions` to capture
post-edit state in a plan's run report.

### `connect_graph_pins(bp_path, graph_name, from_node_guid, from_pin, to_node_guid, to_pin)` *(M28.2)*

Wire two existing pins in a Blueprint graph. Intended for the case
where a graph is mostly authored but missing a single connection — the
authoring UX that today requires opening the graph in the editor and
dragging one wire.

```python
result = connect_graph_pins(
    bp_path="/Game/CombatPrototype/DrewPrototype/BP_Task_Peek",
    graph_name="EventGraph",
    from_node_guid="AB12CD34EF567890AB12CD34EF567890",  # K2Node_IfThenElse
    from_pin="else",
    to_node_guid="1122334455667788AABBCCDDEEFF0011",  # existing FinishTask
    to_pin="execute",
)
```

`graph_name` accepts any K2 graph on the Blueprint — regular function
graphs (`FunctionGraphs`), interface-override graphs
(`ImplementedInterfaces[].Graphs`), and ubergraph pages
(`UbergraphPages`, typically `"EventGraph"`). Node GUIDs are consumed
as hex strings — the format `DeepDumpRenderer` emits in `.deep.md`.

Pin-name conventions:
  - `UK2Node_IfThenElse` (Branch) — true output is `"then"`, false is
    `"else"`, exec-in is `"execute"`, bool condition input is
    `"Condition"`.
  - `UK2Node_FunctionEntry` — exec-out is `"then"`.
  - `UK2Node_FunctionResult` — exec-in is `"execute"`.
  - `UK2Node_CallFunction` — exec-in is `"execute"`, exec-out is
    `"then"` when single-output (Latent nodes have multiple named
    exec-outs, check the node's `.deep.md` pin table).

Idempotent: `BpxReflectionOps::ConnectPinsByName` short-circuits when
the two pins are already in each other's `LinkedTo` arrays. M28.2
marks the blueprint structurally modified after a successful connect
so the following `compile_and_save_package` picks up the new wire.

### `set_level_actor_property(level_path, actor_label, property_path, value)` *(M28.3)*

Mutate a UPROPERTY on one placed actor in a level (.umap) and save
the level package. Minimum viable "level instance property edit" op —
does NOT add / remove actors and does NOT handle World Partition cell
loading.

```python
result = set_level_actor_property(
    level_path="/Game/CombatPrototype/DrewPrototype/Combat_FlatArena",
    actor_label="BP_EnemyBase_TeamA",
    property_path=["Faction"],
    value="1",
)
```

The op:
  1. Calls `unreal.EditorLoadingAndSavingUtils.load_map` to make
     `level_path` the editor's current level (side effect: the editor
     opens this level).
  2. Iterates `EditorActorSubsystem.get_all_level_actors()` to find the
     actor whose `GetActorLabel()` matches `actor_label`.
  3. Runs `BpxReflectionOps::SetPropertyValue` on `property_path`.
  4. `compile_and_save_package(world)` to persist.

`value` is ExportText — the format `FProperty::ExportTextItem_Direct`
produces (`"1"` for int, `"true"` for bool, `"EnumName::Alpha"` for
enums, `"(X=1.0,Y=2.0,Z=3.0)"` for FVector). Plain `int`/`float`/`bool`
Python scalars are also accepted and coerced to the right ExportText
form (lowercase for bools). Idempotent via `SetPropertyValue`'s
before==after skip — replays no-op.

Motivating case: in the Flat Arena diagnosis, two enemy actors had
`Faction=0` (default), so the same-faction check in `AssessThreat`
returned false for everyone and nobody engaged. Fix is two op calls,
one per team.

Out of scope (M28.3 deliberate): adding / removing actors, batched
multi-actor updates, World Partition OFPA cell-aware loading. M20
picks up the broader level-export / level-edit scope when content
drivers beyond Flat Arena surface.

### `add_bp_variable(bp_path, var_name, var_type_spec, default_value="", instance_editable=False)` *(M28.2.1)*

Add a new member variable to a Blueprint. Wraps the M28.2.1
`AddMemberVariableDeterministic` UFUNCTION which calls
`FBlueprintEditorUtils::AddMemberVariable` and then overwrites the fresh
`FBPVariableDescription::VarGuid` with a content-seeded GUID so the
post-op `.uasset` is byte-stable across re-runs (the M28.pre.3 soak gate
catches drift on round 2 otherwise).

```python
add_bp_variable(
    bp_path="/Game/Squad/BP_SquadDirector",
    var_name="bActiveOrder",
    var_type_spec="bool",
    default_value="false",
    instance_editable=True,
)
```

`var_type_spec` accepts a compact set of string forms — documented in
full on `_resolve_pin_type` in `blueprint_structural.py`. Common forms:

- basic: `"int"` / `"byte"` / `"bool"` / `"real"` / `"name"` /
  `"string"` / `"text"`. `"float"` is accepted as a friendly alias
  for `"real"` (UE's unified float/double pin type post-LWC).
- struct: `"struct:/Script/CoreUObject.Vector"` /
  `"struct:/Script/Game.S_TargetInfo"`.
- object: `"object:/Script/AIModule.AIController"` /
  `"object:/Game/MyBP.MyBP_C"`.
- class: `"class:/Script/AIModule.AIController"` (TSubclassOf).
- container: `"array:<inner>"` / `"set:<inner>"` /
  `"map:<key>=>>>:<value>"` (the `=>>>:` separator is deliberate — colons
  alone collide with asset paths inside the inner spec).

`default_value` is the literal string form `FBPVariableDescription
::DefaultValue` accepts (`"true"`, `"42"`, `"(X=1.0,Y=2.0,Z=3.0)"`,
etc.). Empty string = type default. The executor deliberately bypasses
`_convert_value` on this kwarg because the bridge needs the raw
ImportText.

`instance_editable=True` chains
`BlueprintEditorLibrary.set_blueprint_variable_instance_editable` after
the deterministic add (= "Instance Editable" checkbox in the BP editor
details panel). Default False matches UE's stricter default (hidden on
placed instances unless exposed).

Idempotent: if a variable named `var_name` already exists on
`Blueprint->NewVariables[]`, returns `skipped="variable already exists"`
without modifying type or metadata. Type compatibility is NOT verified
on skip — caller can detect "wrong type already exists" by inspecting
the existing variable via the standard `unreal.*` reflection.

### `add_bp_function(bp_path, function_name, is_pure=False)` *(M28.2.2)*

Add a blank member function graph to a Blueprint. Mirrors
`add_bp_variable`'s shape — deterministic bridge wrapper, idempotent on
the function name, compile+save at the end. The op creates a standard
void/void function with auto-generated Entry and Return nodes; the
returned `entry_guid` / `return_guid` feed the M26.1 body-authoring ops
(`AddSelfMemberGetNode`, `ConnectPinsByName`, `SetNodePinLiteralDefault`)
so a follow-up plan can populate the body by GUID reference.

```python
result = add_bp_function(
    bp_path="/Game/Squad/BP_SquadDirector",
    function_name="OnOrderReceived",
)
entry_guid  = result["after"]["entry_guid"]
return_guid = result["after"]["return_guid"]
```

`is_pure=True` sets `FUNC_BlueprintPure` on the Entry node's ExtraFlags.
Pure functions with no outputs do not compile cleanly — only pair
`is_pure=True` with a later output-wire-up in the same plan.

Idempotent: if a graph named `function_name` already exists anywhere on
the BP (function graphs, interface-override graphs, or ubergraph pages —
all three live in `FindFunctionGraphByName`), returns
`skipped="function already exists"` and populates the existing graph's
Entry / Return GUIDs so chained authoring ops still work.

Determinism: `GraphGuid` + Entry / Return `NodeGuid` + every default-
created pin's `PinId` are seeded by the
`AddFunctionGraphDeterministic` UFUNCTION from
`SeedGuidFromJoined(bp_path + ":func:" + function_name + ":<slot>")` so
the post-op `.uasset` is byte-stable round-to-round. Without this,
`UEdGraph::PostInitProperties` (EdGraph.cpp:147) +
`UK2Node_FunctionEntry::CreateNewGuid` +
`UK2Node_FunctionResult::CreateNewGuid` + default-created pin GUIDs all
re-randomize and round 2 of the soak would drift immediately.

### `add_component_to_scs(bp_path, component_class_path, component_name, parent_component_name="")` *(M28.2.3)*

Add a component to an Actor Blueprint's SimpleConstructionScript. Wraps
the M28.2.3 `AddComponentToSCSDeterministic` UFUNCTION which calls
`USimpleConstructionScript::CreateNode` and post-write seeds the new
`USCS_Node::VariableGuid` via `SeedGuidFromJoined(bp_path + ":scs:" +
component_name)` so the .uasset is byte-stable across re-runs.

The engine path looked pure-Python in M28.2.0 research — `USCS_Node
::ValidateGuid` has a name-hash seed path when `!VariableGuid.IsValid()`.
Code inspection during M28.2.3 proved that path is unreachable for
freshly-created nodes: `CreateNodeImpl` (SimpleConstructionScript.cpp
:1375) assigns `FGuid::NewGuid()` before `ValidateGuid` runs, so the
hash path is never taken. A 3rd bridge UFUNCTION closes the gap.

```python
add_component_to_scs(
    bp_path="/Game/Squad/BP_SquadDirector",
    component_class_path="/Script/AIModule.AIPerceptionComponent",
    component_name="SquadPerception",
    parent_component_name="",  # attach at SCS root
)
```

`component_class_path` resolves via `load_class` → `load_object`
fallback — covers native `/Script/<Module>.<Class>` paths and BP-
generated `/Game/<Asset>.<Asset>_C` classes uniformly. The bridge
validates that it's a `UActorComponent` subclass and that the requested
name doesn't collide with a native-inherited component (engine would
silently append a counter suffix, breaking replay idempotence —
rejecting up-front keeps plan replay crisp).

`parent_component_name` is an SCS-node name (as it appears in the
Components panel). Empty / omitted attaches at SCS root. SCS-to-SCS
parenting only — parenting onto a native (inherited-CDO) component
returns a structured error. Mirrors the editor's "Add Child Component"
UX for SCS-only parenting.

Idempotent: if a USCS node named `component_name` exists with the same
`component_class`, returns `skipped="component already exists on SCS"`.
Name-with-different-class collision is a structured error, not a silent
overwrite.

### `add_bp_interface(bp_path, interface_class_path)` *(M28.2.4)*

Attach an interface implementation to a Blueprint. Wraps the M28.2.4
`AddInterfaceByPath` UFUNCTION which calls
`FBlueprintEditorUtils::ImplementNewInterface` and post-attach seeds
`GraphGuid` + Entry / Return `NodeGuid` + pin IDs on every generated
override graph so the .uasset is byte-stable across re-runs.

```python
add_bp_interface(
    bp_path="/Game/Squad/BP_SquadDirector",
    interface_class_path="/Game/Squad/BPI_OrderListener.BPI_OrderListener_C",
)
```

`interface_class_path` resolves via `load_class` → `load_object` —
covers native `/Script/<Module>.<Interface>` interfaces and BP-generated
`/Game/<Asset>.<Asset>_C` interface classes uniformly. The bridge
validates that it's a class with `CLASS_Interface` set before calling
the engine API.

ImplementNewInterface generates an override graph only for interface
functions that aren't placeable as events (i.e. functions with output
parameters — events stay wired up through the ubergraph's event-node
path). Pure-event interfaces attach cleanly with zero generated graphs;
the seeding loop is inert on that path.

Idempotent: if the BP already lists `interface_class_path` on
`ImplementedInterfaces[]`, returns
`skipped="interface already implemented"`. Pre-screened in the Python
op so replay does not surface the engine's "already implemented" UI
toast.

Determinism: each generated graph's `GraphGuid` + Entry / Return
`NodeGuid` + pin IDs are seeded via
`SeedGuidFromJoined(bp_path + ":iface_graph:" + interface_class_path +
":" + graph_name + ":<slot>")`. Keyed on both BP and interface paths so
two BPs implementing the same interface get distinct seeds and replay
is byte-stable across re-runs.

Chain with `implement_interface_function(force_rebind=True)` to go from
a bare stub (`add_bp_interface` only authors the empty override graph)
to a wired passthrough in the same plan — see
`plans/AGENT_LOOP.md`'s squad-director worked example.

### `add_custom_event_node(bp_path, graph_name, event_name, position)` *(M28.3.3)*

Spawn a `UK2Node_CustomEvent` into an ubergraph. Event-channel entry point
for design.md's squad director (`AI.Order.*` channel, item #1) and callout
system (item #4).

```python
add_custom_event_node(
    bp_path="/Game/Squad/BP_SquadDirector",
    graph_name="EventGraph",
    event_name="OnOrderReceived",
    position=[256, 128],
)
```

`graph_name` must resolve to an ubergraph (e.g. `"EventGraph"`). Function
/ interface-override graphs are rejected at op entry with a structured
error mirroring UE's compile-time `K2Node_Event::IsCompatibleWithGraph`
check — early surfacing keeps the plan-author feedback loop tight.

`CustomFunctionName` (inherited from `UK2Node_Event`) is set before
`AllocateDefaultPins` so the delegate pin name + signature resolve
correctly. Default pin set: `OutputDelegate` (delegate out, consumed by
`Bind Event`) + `then` (exec out). CustomEvent parameters require
subsequent user-defined-pin ops (deferred from M28.3.3).

Idempotent on seeded NodeGuid (seed includes event name + position).
`after` carries `{node_guid, event_name, spawned, pins}`.

Determinism: seed key is
`md5(<bp>:graph:<g>:custom_event:<name>:<x>,<y>)`. Pin IDs via
`SeedPinGuidsForNode`.

### `add_execution_sequence_node(bp_path, graph_name, num_outputs, position)` *(M28.3.3)*

Spawn a `UK2Node_ExecutionSequence` with N `then_N` exec outputs
(lowercase per UE's `UEdGraphSchema_K2::PN_Then`).
Design.md drivers: polish-pass sequencing (item #8) and callout
broadcasts fanning out to multiple listeners (item #4).

```python
add_execution_sequence_node(
    bp_path="/Game/AI/BP_TaskCallout",
    graph_name="EventGraph",
    num_outputs=3,
    position=[128, 256],
)
```

`num_outputs` must be in `[2, 16]`. The engine's default `AllocateDefaultPins`
produces `Then_0` + `Then_1`; additional outputs are added via
`IK2Node_AddPinInterface::AddInputPin`. **Naming gotcha**: `AddInputPin`
adds a new THEN-OUT pin, not an input — UE API wart, not ours. The op
exposes this via the clean `num_outputs` parameter so callers don't have
to deal with the misleading method name.

Idempotent on seeded NodeGuid (seed includes `num_outputs` + position so
two sequences with different fan-outs at the same position get distinct
GUIDs). `after` carries `{node_guid, num_outputs, spawned, pins}`.

Determinism: seed key is
`md5(<bp>:graph:<g>:execseq:<n>:<x>,<y>)`. `SeedPinGuidsForNode` runs
AFTER the `AddInputPin` loop so extended `Then_2`+ pins are also
deterministic.

### `add_dynamic_cast_node(bp_path, graph_name, target_class_path, position)` *(M28.3.3)*

Spawn a `UK2Node_DynamicCast` typed against a specific UClass. Routes
`ObjectToCast` input through `CastSucceeded` / `CastFailed` exec outputs
based on an IsA check, exposing the cast object as the typed `As<X>`
pin. Design.md drivers: utility scorer archetype resolution (item #2)
and callout faction checks (item #4 — cast ally ref to `BP_EnemyBase`
before broadcasting).

```python
add_dynamic_cast_node(
    bp_path="/Game/AI/BP_UtilityScorer",
    graph_name="ScoreTarget",
    target_class_path="/Game/Enemies/BP_EnemyBase.BP_EnemyBase_C",
    position=[384, 0],
)
```

`target_class_path` is required and non-empty — DynamicCast with a null
TargetType is an impossible node shape. Accepts `/Script/<Module>.<Class>`
(native) or `/Game/<Asset>.<Asset>_C` (BP-generated). Resolved via
`unreal.load_class` → `load_object` fallback, mirroring
`add_component_to_scs` / `add_bp_interface`.

**`TargetType` MUST be set before `AllocateDefaultPins`** — the typed
`As<TargetClass>` output pin's `PinCategory` / `PinSubCategoryObject` are
derived from `TargetType` inside `UK2Node_DynamicCast::CreatePinsForCastNode`.
Post-alloc assignment leaves `As<X>` as a wildcard. The op enforces the
correct ordering internally; plan authors don't have to think about it.

Default pins (impure cast — the ship shape): `execute` (exec in),
`CastSucceeded` / `CastFailed` (exec out), `ObjectToCast` (object in),
`As<TargetClass>` (typed object out), `bSuccess` (bool out). A future
`is_pure` param could surface `UK2Node_DynamicCast::SetPurity`; deferred
until a concrete driver surfaces.

Idempotent on seeded NodeGuid (seed includes target class path +
position).

Determinism: seed key is
`md5(<bp>:graph:<g>:cast:<target>:<x>,<y>)`. Pin IDs via
`SeedPinGuidsForNode`.

### `add_macro_instance_node(bp_path, graph_name, macro_path, position)` *(M28.13)*

Spawn a `UK2Node_MacroInstance` into a K2 graph, pointed at an external
macro graph (e.g. `ForEachLoop` / `WhileLoop` / `ForEachLoopWithBreak`).
Single highest-ROI op of the M28 catalog: one new bridge UFUNCTION
unblocks five design.md sections that were stuck on "iterates X →
blocked" (BroadcastOrder/AssignRole iteration, ScorerScoringLoop,
ConfidenceDecay×2, SharedPerception) because ForEachLoop is a macro
instance, not an atomic K2Node.

```python
add_macro_instance_node(
    bp_path="/Game/AI/BP_EncounterDirector",
    graph_name="EventGraph",
    macro_path="/Engine/EditorBlueprintResources/StandardMacros.StandardMacros:ForEachLoop",
    position=[400, 0],
)
```

`macro_path` is required, of shape `"<lib_uobject_path>:<macro_name>"`.
The lib path resolves to a `UBlueprint` (the macro library) via
`unreal.load_object`; the suffix after `:` matches a graph in the
library's `MacroGraphs` array. Common StandardMacros macros:

- `/Engine/EditorBlueprintResources/StandardMacros.StandardMacros:ForEachLoop`
- `/Engine/EditorBlueprintResources/StandardMacros.StandardMacros:ForEachLoopWithBreak`
- `/Engine/EditorBlueprintResources/StandardMacros.StandardMacros:WhileLoop`
- `/Engine/EditorBlueprintResources/StandardMacros.StandardMacros:Reverse for Each Loop`

User-authored macro libraries on `/Game/...` paths work the same way —
pass the library's UObject path as the prefix.

**`MacroGraphReference` MUST be set before `AllocateDefaultPins`** — the
inherited `UK2Node_Tunnel::AllocateDefaultPins` reads the macro's own
Tunnel/Result pins from `MacroGraphReference` to mirror them onto the
instance. Post-alloc set leaves the node with zero pins. The op
enforces the correct ordering internally; plan authors don't have to
think about it.

`SeedPinGuidsForNode` runs AFTER `AllocateDefaultPins` so the mirrored
pins (whose count + names depend on the macro's signature) get
deterministic PinIds.

Idempotent on seeded NodeGuid (seed includes the macro's full path +
position so two different ForEachLoop variants from different libraries
don't collide).

Determinism: seed key is
`md5(<bp>:graph:<g>:macro:<macro_lib_path.lib_name:macro_name>:<x>,<y>)`.

Default pins (mirrored from the macro's Tunnel/Result):
- ForEachLoop: `execute` (exec in), `Array` (array in, wildcard until
  connected), `Array Element` (typed out), `Array Index` (int out),
  `LoopBody` (exec out), `Completed` (exec out).
- WhileLoop: `execute` (exec in), `Condition` (bool in), `LoopBody`
  (exec out), `Completed` (exec out).
- ForEachLoopWithBreak: same as ForEachLoop plus a `Break` exec in.

The bridge defensively rejects non-`GT_Macro` graphs; the Python op
catches the typical wrong-shape case (function or ubergraph mistakenly
passed as `macro_path`) earlier with a better error.

### `add_make_struct_node(bp_path, graph_name, struct_type_path, position)` *(M28.14)*

Spawn a `UK2Node_MakeStruct` — pure node that constructs a struct value
from per-field input pins. First op of the M28.14 struct-mutation catalog.

```python
add_make_struct_node(
    bp_path="/Game/AI/BP_EncounterDirector",
    graph_name="EventGraph",
    struct_type_path="/Script/CoreUObject.Vector",
    position=[400, 0],
)
```

Driver: read-modify-write inside the M28.13 ForEachLoop body for design.md's
UAIActionScorer per-element score updates and confidence-decay over
`S_TargetInfo` arrays — without struct authoring the loops can iterate
but cannot author the body.

`struct_type_path` accepts engine structs
(`/Script/CoreUObject.Vector`, `/Script/Engine.HitResult`,
`/Script/CoreUObject.Rotator`) and user-defined structs at `/Game/...`
paths. Resolved via `unreal.load_object`.

Idempotent on seeded NodeGuid (seed includes struct path + position).

Determinism: seed key
`md5(<bp>:graph:<g>:make_struct:<struct_path>:<x>,<y>)`. Pin IDs via
`SeedPinGuidsForNode` AFTER `AllocateDefaultPins` so the per-field input
pins (whose count + names depend on the struct's UPROPERTY layout) get
deterministic PinIds.

Default pins: one input pin per `BlueprintVisible` non-`BlueprintReadOnly`
UPROPERTY on the struct, plus a single output pin carrying the
constructed struct value. The bridge sets `bMadeAfterOverridePinRemoval = true`
to match the engine's editor spawn path; without it the node would be
treated as legacy and surface phantom override-toggle pins.

### `add_break_struct_node(bp_path, graph_name, struct_type_path, position)` *(M28.14)*

Spawn a `UK2Node_BreakStruct` — pure node that splits a struct input into
per-field output pins. The "read" half of read-modify-write inside loop
bodies (Make = construct, Break = read, SetFields = modify-in-place).

```python
add_break_struct_node(
    bp_path="/Game/AI/BP_EncounterDirector",
    graph_name="EventGraph",
    struct_type_path="/Game/AI/Structs/S_TargetInfo.S_TargetInfo",
    position=[400, 100],
)
```

`struct_type_path` resolution and idempotence semantics match
`add_make_struct_node`.

Determinism: seed key
`md5(<bp>:graph:<g>:break_struct:<struct_path>:<x>,<y>)`.

Default pins: one input pin (struct value) + one output pin per
`BlueprintVisible` UPROPERTY on the struct.

### `add_set_fields_in_struct_node(bp_path, graph_name, struct_type_path, fields_to_show, position)` *(M28.14)*

Spawn a `UK2Node_SetFieldsInStruct` — imperative node that takes a
struct input, sets a configurable subset of its fields from input pins,
and emits the modified struct as an output. The "modify" half of
read-modify-write inside loop bodies. UE editor surfaces this as a node
titled "Set members in <StructName>".

```python
add_set_fields_in_struct_node(
    bp_path="/Game/AI/BP_EncounterDirector",
    graph_name="EventGraph",
    struct_type_path="/Game/AI/Structs/S_TargetInfo.S_TargetInfo",
    fields_to_show=["Confidence", "LastSeenTime"],
    position=[600, 0],
)
```

`fields_to_show` is required and non-empty —
`UK2Node_SetFieldsInStruct::FSetFieldsInStructPinManager::GetRecordDefaults`
initializes `bShowPin = false` for every property (vs Make/Break which
default to true), so an empty list would produce a node with no settable
pins. The bridge rejects this up front. Field names must match struct
UPROPERTYs case-sensitively — any unknown name is a structured error to
prevent silent typo no-ops.

Internally: NewObject + StructType + AllocateDefaultPins (engine populates
`ShowPinForProperties` with all `bShowPin=false` via the SetFields-specific
pin manager). The bridge then walks `ShowPinForProperties`, sets
`bShowPin = true` for entries matching `fields_to_show`, and calls
`ReconstructNode()` to re-run AllocateDefaultPins. `RebuildPropertyList`
preserves bShowPin overrides through its old-settings cache so the
reconstruct emits the requested per-field input pins.
`SeedPinGuidsForNode` runs AFTER ReconstructNode so the final pin set
gets deterministic PinIds.

Idempotent on seeded NodeGuid.

Determinism: seed key
`md5(<bp>:graph:<g>:set_fields_in_struct:<struct_path>:fields:<sorted_fields>:<x>,<y>)`.
Sorted `fields_to_show` in the seed so caller-side ordering doesn't
drift the GUID across replays.

Default pins (with `fields_to_show=["Confidence", "LastSeenTime"]` on a
hypothetical `S_TargetInfo`): `execute` (exec in), `then` (exec out),
struct in pin (struct ref input), struct out pin (struct ref output),
`Confidence` (input), `LastSeenTime` (input).

### `add_eqs_option(eqs_path, generator_class_path)` *(M28.5.1)*

Append a new option to a `UEnvQuery` with a fresh generator of the supplied
concrete class. First op of the M28.5 EQS write-side catalog.

```python
add_eqs_option(
    eqs_path="/Game/AI/EQS_FindCover",
    generator_class_path="/Script/AIModule.EnvQueryGenerator_ActorsOfClass",
)
```

Creates a `UEnvQueryOption` owned by the target query and a fresh
`UEnvQueryGenerator` of `generator_class_path` owned by the option, then
appends the option to `UEnvQuery::Options`. Atomic: option + generator
land together or not at all. Tests are appended in subsequent sub-phases
(`add_eqs_test` ships in M28.5.2); scalar property edits on either the
generator or a test reuse the existing `SetPropertyValue` bridge against
a path like `["Options", "[N]", "Generator", "<UPROPERTY>"]`.

`generator_class_path` must be a concrete, non-abstract subclass of
`UEnvQueryGenerator`. The bridge rejects abstract classes (including the
base itself) up-front — `NewObject` on abstract throws an uncatchable
`check()` at runtime, so the pre-check keeps plan replay crisp. Typical
concrete classes:

- `/Script/AIModule.EnvQueryGenerator_ActorsOfClass`
- `/Script/AIModule.EnvQueryGenerator_SimpleGrid`
- `/Script/AIModule.EnvQueryGenerator_Donut`
- `/Script/AIModule.EnvQueryGenerator_OnCircle`
- `/Script/AIModule.EnvQueryGenerator_PathingGrid`

Idempotent on `(eqs_path, generator_class_path)`: if any existing option
already carries a generator of the requested class, returns
`skipped="option with this generator already exists"` with
`option_index` pointing at the matching slot. Plan authors tune the
generator's per-UPROPERTY values via `SetPropertyValue` on
`["Options", "[N]", "Generator", ...]` without re-triggering the create
path.

Determinism: `UEnvQuery` / `UEnvQueryOption` / `UEnvQueryGenerator`
classes have zero `FGuid::NewGuid()` usage (grep-confirmed M28.5.0
research); the only drift source is `NewObject`'s counter-suffixed
default name generation. The bridge passes explicit `FName`s
(`BpxEqsOption_<idx>` / `BpxEqsGen_<idx>_<ClassShortName>`) on each
`NewObject` so two replays against the same baseline produce
byte-identical `.uasset`. M28.pre.3 soak exercises this invariant.

Design.md drivers: the utility-scorer target picker (item #2 — cast
EQS results to archetype classes for per-archetype scoring) and squad
director cover scans (item #6 — EQS resolves candidate cover positions
for the flanking arm of a squad order). M15 landed the Tier 2 read-side
so authored EQS content is fully inspectable; M28.5 closes the loop with
a write-side so authoring stays in the plan layer.

### `add_eqs_test(eqs_path, option_index, test_class_path)` *(M28.5.2)*

Append a `UEnvQueryTest` subclass to an existing option's `Tests[]` array.
Second op of the M28.5 EQS write-side catalog; builds on the option-level
shape from `add_eqs_option`.

```python
add_eqs_test(
    eqs_path="/Game/AI/EQS_FindCover",
    option_index=0,
    test_class_path="/Script/AIModule.EnvQueryTest_Distance",
)
```

Creates a `UEnvQueryTest` subclass instance owned by
`UEnvQuery::Options[option_index]`, appends it to the option's `Tests[]`,
and assigns `TestOrder = pre_count` so the `0..N-1` runtime invariant
holds. `EnvQueryManager.cpp:874` only repairs `TestOrder=0` at runtime,
so the editor must assign sequentially — the bridge takes care of this.

`test_class_path` must be a concrete, non-abstract subclass of
`UEnvQueryTest`. The base `UEnvQueryTest` is `UCLASS(Abstract)` so the
abstract check rejects the base itself. Typical concrete classes:

- `/Script/AIModule.EnvQueryTest_Random`
- `/Script/AIModule.EnvQueryTest_Distance`
- `/Script/AIModule.EnvQueryTest_Trace`
- `/Script/AIModule.EnvQueryTest_Dot`
- `/Script/AIModule.EnvQueryTest_Pathfinding`

Idempotent on `(eqs_path, option_index, test_class_path)`: if any
existing test on the target option is an exact-class match, returns
`skipped="test with this class already exists on option"` with
`test_index` pointing at the matching slot. Per-UPROPERTY tuning stays
on `SetPropertyValue` against a
`["Options", "[N]", "Tests", "[M]", "<UPROPERTY>"]` path without
re-triggering create.

Determinism: the bridge passes an explicit `FName`
(`BpxEqsTest_<option_index>_<pre_count>_<TestClassShortName>`) on the
`NewObject` call. Option index is part of the name so two options
carrying the same test class don't collide in the package's `FName`
table. Replays across fresh editor shells produce byte-identical
`.uasset` — exercised by the M28.pre.3 soak gate.

### `remove_eqs_test(eqs_path, option_index, test_index)` *(M28.5.2)*

Remove a test from an option's `Tests[]` array by index. Symmetric
counterpart of `add_eqs_test`.

```python
remove_eqs_test(
    eqs_path="/Game/AI/EQS_FindCover",
    option_index=0,
    test_index=1,
)
```

Removes `UEnvQuery::Options[option_index].Tests[test_index]` and reseats
`TestOrder` on every subsequent test so the `0..N-1` invariant holds —
`EnvQueryManager.cpp:874` only repairs `TestOrder=0` at runtime, so
non-zero stale values would silently break evaluation order.

Idempotent on `(eqs_path, option_index, test_index)`: an out-of-range
`test_index` returns `skipped="test already removed (out-of-range
index)"`. This supports soak-style replay where round 1 mutates and
round 2 would otherwise hit the now-empty slot. `option_index` still
has a strict bounds check — option identity is stable across test
removals, so an out-of-range option indicates a plan-level mistake.

### `set_eqs_generator_property(eqs_path, option_index, property_path, value)` *(M28.5.3)*

Mutate a UPROPERTY on `UEnvQuery::Options[option_index].Generator`.
Fourth op of the M28.5 catalog — Python-only wrapper around the existing
`SetPropertyValue` reflection bridge (M23.1). No new UFUNCTION.

```python
set_eqs_generator_property(
    eqs_path="/Game/AI/EQS_FindCover",
    option_index=0,
    property_path=["SearchRadius", "DefaultValue"],
    value=500.0,
)
```

`property_path` is leaf-relative — a single name (`["OptionName"]`)
addresses a plain UPROPERTY on the generator; nested paths
(`["SearchRadius", "DefaultValue"]`) descend into `FStructProperty`
fields like `FAIDataProviderFloatValue::DefaultValue`. Array elements
use `"[N]"` notation — see `BpxReflectionOps::ResolvePath` for the
full grammar. The wrapper prepends the EQS-specific prefix
`["Options", "[option_index]", "Generator"]` so callers only supply
the subobject-local path.

`value` may be a plain string / int / float / bool — scalars are
coerced to their ExportText form before handing to
`FProperty::ImportText_Direct` (`"true"` / `"false"` / decimal repr).
Strings pass through verbatim so callers with an already-formatted
ExportText literal (enum short name, FVector tuple like
`"(X=1.0,Y=0.0,Z=0.0)"`) can use it directly.

Idempotent: the underlying `SetPropertyValue` short-circuits when
`before == value` as a string — replays are no-ops on round 2. Safe
to re-run the same plan multiple times.

Out of scope: `FAIDataProviderFloatValue::DataBinding` swaps. The
`DataBinding` is a provider UObject inside the struct that needs
`PostEditChangeProperty` revalidation per `EnvQueryNode.cpp` — plain
ImportText bypasses that. Use the struct's `DefaultValue` leaf for
scalar tuning; swap bindings from the editor when needed.

### `set_eqs_test_property(eqs_path, option_index, test_index, property_path, value)` *(M28.5.3)*

Mutate a UPROPERTY on `UEnvQuery::Options[i].Tests[j]`. Fifth op of
the M28.5 catalog; sibling of `set_eqs_generator_property` targeting
an option's `Tests[]` array instead of its `Generator` slot. Reuses
the same `SetPropertyValue` bridge — no new UFUNCTION.

```python
set_eqs_test_property(
    eqs_path="/Game/AI/EQS_FindCover",
    option_index=0,
    test_index=1,
    property_path=["TestPurpose"],
    value="Score",
)
```

`property_path` / `value` rules are identical to
`set_eqs_generator_property`. Typical targets:

- `["TestComment"]` — FString `UEnvQueryTest::TestComment`.
- `["TestPurpose"]` — enum (`"Filter"` / `"Score"` / `"FilterAndScore"`).
- `["ScoringFactor", "DefaultValue"]` — float leaf inside
  `FAIDataProviderFloatValue`.
- `["ClampMinType"]` — enum `EEnvQueryTestClamping::Type`.

The wrapper prepends the EQS-specific prefix `["Options",
"[option_index]", "Tests", "[test_index]"]` so callers only supply
the test-local property path.

Idempotent via `SetPropertyValue`'s before-equals-after short-circuit.
Same `DataBinding`-swap exclusion as the generator op — use the
`DefaultValue` leaf for scalar tuning.

### `create_curve_float(curve_path)` *(M28.4.1)*

Create a new `UCurveFloat` asset at the supplied `/Game/...` path. First
op of the M28.4 non-BP asset-factory catalog.

```python
create_curve_float(curve_path="/Game/AI/Curve_IntensityRamp")
```

Wraps `NewObject<UCurveFloat>(Pkg, Name, RF_Public | RF_Standalone)` +
`FAssetRegistryModule::AssetCreated` + `UPackage::SavePackage` via
`compile_and_save_package`. The created asset starts with zero keys;
populate via `set_curve_float_keys` in a follow-up op (or plan step).

Idempotent on `curve_path`: if a `UCurveFloat` already exists at the
target path, returns `skipped="curve already exists"` with
`spawned=False`. If a different asset class occupies the path, returns
a structured error — silently co-existing would be a plan-level
mistake.

Determinism: `UCurveFloat` / `UCurveBase` / `FRichCurveKey` have zero
`FGuid::NewGuid()` usage (grep-confirmed M28.4.0 research), so the only
drift source is `NewObject`'s counter-suffixed default name. The bridge
passes an explicit `FName` derived from the path's short-name tail
(e.g. `Curve_IntensityRamp`), so replays across fresh editor shells
produce byte-identical `.uasset`. M28.pre.3 soak exercises the
idempotent-skip branch; the actual create-from-scratch path is covered
by MCP pytest + manual editor verification (running it through the
inspect harness would leave residue outside the single-scratch-path
cleanup contract).

Design.md driver: item #6 (encounter-director intensity curve) — author
the 4-point intensity curve as a standalone `UCurveFloat` at plan-compose
time rather than requiring a manual editor pass.

### `set_curve_float_keys(curve_path, keys)` *(M28.4.1)*

Wholesale-replace the key array on a `UCurveFloat`'s `FloatCurve`.
Second op of the M28.4 catalog.

```python
set_curve_float_keys(
    curve_path="/Game/AI/Curve_IntensityRamp",
    keys=[
        {"time": 0.0, "value": 0.2},
        {"time": 1.0, "value": 0.6},
        {"time": 2.0, "value": 1.0},
        {"time": 4.0, "value": 0.4},
    ],
)
```

`keys` is an ordered list of `{time, value [, interp_mode]}` dicts.
`time` and `value` are required floats. `interp_mode` is an optional
string — one of `"linear"` (default), `"constant"`, `"cubic"`.
`RCIM_None` is deliberately omitted: UE's Python binding hides that
enum value (Python keyword clash) so we can't reach it without dropping
to ImportText, which has no realistic driver here. Entries MUST be
pre-sorted by `time` ascending — `FRichCurve::Evaluate` assumes sorted
storage, and the bridge rejects unsorted input rather than letting the
editor write a corrupted curve.

Per the M28.4.0 research outcome, wholesale replacement is the intended
scope — matches the "re-author as a unit" authoring style the
design.md intensity-curve driver uses. Per-key add/edit/remove ops are
deferred until a concrete driver materialises the "tweak one point
without re-supplying all N" use case.

Idempotent on element-wise `(time, value, interp_mode)` equality: if
the existing key array already matches `keys` on those fields in
order, returns `skipped="keys already match"`. Tangent fields are
excluded from the compare because the current surface only accepts
Time + Value — tangent drift between rounds would be engine-computed
rather than plan-driven.

Out of scope (deliberate):
- Tangent / per-key tangent-weight tuning. The Python surface only
  exposes `interp_mode` beyond the basics; `FRichCurveKey`'s zero-
  initialiser defaults cover the common case. Bespoke tangents belong
  in a per-key op.
- Non-float curves (`UCurveVector`, `UCurveLinearColor`). Narrow scope
  matches the M28.3 narrow K2Node catalog precedent.

### `create_data_asset_instance(asset_path, parent_class_path)` *(M28.4.2)*

Create a new `UDataAsset`-subclass instance at the supplied `/Game/...`
path, using `parent_class_path` as the concrete type to instantiate.
Third op of the M28.4 non-BP asset-factory catalog.

```python
create_data_asset_instance(
    asset_path="/Game/AI/Archetypes/DA_Rusher",
    parent_class_path="/Game/AI/Archetypes/DA_ArchetypeBase.DA_ArchetypeBase_C",
)
```

`parent_class_path` covers both native DA classes
(`/Script/<Module>.<ClassName>`) and BP-derived DA classes
(`/Game/<path>/<Name>.<Name>_C` — the GeneratedClass, not the BP asset
path). The bridge UFUNCTION validates that the class is a non-abstract
subclass of `UDataAsset`; `UPrimaryDataAsset` and every BP-derived DA
class satisfy that transitively.

Wraps `NewObject<UDataAsset>(Pkg, DAClass, FName(ShortName),
RF_Public | RF_Standalone | RF_Transactional)` — matches
`UDataAssetFactory::FactoryCreateNew` flag-for-flag, so a scripted
create lands with the same object header the interactive editor
produces.

Idempotent on `(asset_path, parent_class_path)`: if a DA already
exists at the path AND its class matches `parent_class_path`, returns
`skipped="asset already exists"`. Class mismatch at the same path
returns a structured error — plan author has a target mismatch.

Determinism: `UDataAsset` / `UPrimaryDataAsset` have zero
`FGuid::NewGuid()` usage (grep-confirmed M28.4.0 research). The
explicit `FName` on `NewObject` (derived from the short-name tail)
is the only determinism lever.

Design.md driver: item #7 (archetype DAs — Rusher / Marksman /
Suppresser / Flanker). Each archetype is a
`/Game/AI/Archetypes/DA_<Name>.uasset` instance of a BP-derived
`UPrimaryDataAsset` subclass carrying per-archetype tuning.

### `set_data_asset_property(asset_path, property_path, value)` *(M28.4.2)*

Mutate a UPROPERTY on a `UDataAsset`-subclass instance. Fourth op of
the M28.4 catalog. Reuses the existing M23.1 `SetPropertyValue`
reflection bridge — no new UFUNCTION.

```python
set_data_asset_property(
    asset_path="/Game/AI/Archetypes/DA_Rusher",
    property_path=["AggroRadius"],
    value=1200.0,
)
```

`property_path` is a list of navigation steps the reflection bridge
understands. A single leaf name (`["AggroRadius"]`) addresses a plain
UPROPERTY; nested paths (`["Tuning", "MeleeRange"]`) descend into
`FStructProperty` fields. Array elements use `"[N]"` notation — see
`BpxReflectionOps::ResolvePath`. `value` accepts strings (passed
verbatim), ints / floats / bools (coerced to their ExportText form).

Works for both natively-declared UPROPERTYs on a C++ parent DA class
AND for BP-added member variables on a BP-derived DA class. BP-added
vars land on the generated class with their friendly FName, so
`FindFProperty(class, FName(friendly_name))` resolves cleanly — no
mangling-resolution helper needed for the current corpus. If a real
mangled case surfaces (shadowed / renamed field), add a
`_resolve_da_property_name` helper in `data_assets.py` rather than
bloating every op's happy path.

Idempotent via `SetPropertyValue`'s before-equals-after short-circuit.

Out of scope (deliberate):
- Instanced-subobject / EditInlineNew references. Use
  `set_instanced_subobject_property` (M26.1) for those; it already
  works on any UObject root. `SetPropertyValue` only covers
  scalar + struct-scalar mutations.

### `create_user_defined_struct(uds_path)` *(M28.4.3)*

Create a new `UUserDefinedStruct` asset at a ``/Game/...`` path. Fifth
op of the M28.4 catalog; first of the M28.4.3 UDS quartet.

```python
create_user_defined_struct(
    uds_path="/Game/AI/Structs/S_TargetInfo",
)
```

Wraps the M28.4.3 `CreateUserDefinedStructDeterministic` bridge
UFUNCTION which calls `FStructureEditorUtils::CreateUserDefinedStruct`
then closes the engine's two `FGuid::NewGuid()` determinism traps:
`Struct->Guid` (seeded from `<uds_path>:uds`) and the auto-bool
member's `VarGuid` (seeded from `<uds_path>:uds_var:BpxAutoBool`).
The auto-bool is renamed to ``BpxAutoBool`` via
`FStructureEditorUtils::RenameVariable` so `VarName` regenerates
from the seeded `VarGuid` + the new friendly name.

The auto-bool stays in the fresh struct because the engine's
`bAllowToMakeEmpty=false` invariant (StructureEditorUtils.cpp:327)
refuses to remove the last member. Plan authors drive further
structure via `add_uds_member` to add real members, then optionally
`remove_uds_member` to drop `BpxAutoBool` once at least one real
member is present.

Idempotent on `uds_path`: if a UUserDefinedStruct already exists at
the target path, returns `success=True` with
`skipped="uds already exists"`. Wrong-class collision at the same
path returns a structured error — silent stacking would be a
plan-level mistake.

Design.md driver: item #3 (confidence-decaying perception — thicken
`S_TargetInfo` UDS with lifetime / last-seen-time / exposure-score
fields so the perception system can reason about stale contacts).

### `add_uds_member(uds_path, member_name, var_type_spec, default_value="")` *(M28.4.3)*

Append a new member variable to an existing `UUserDefinedStruct`.
Sixth op of the M28.4 catalog.

```python
add_uds_member(
    uds_path="/Game/AI/Structs/S_TargetInfo",
    member_name="LastSeenTime",
    var_type_spec="real",
    default_value="0.0",
)
add_uds_member(
    uds_path="/Game/AI/Structs/S_TargetInfo",
    member_name="ExposureScore",
    var_type_spec="real",
    default_value="0.0",
)
add_uds_member(
    uds_path="/Game/AI/Structs/S_TargetInfo",
    member_name="Archetype",
    var_type_spec="object:/Script/Engine.DataAsset",
)
```

Wraps the M28.4.3 `AddUserDefinedStructMember` UFUNCTION which calls
`FStructureEditorUtils::AddVariable` then post-seeds the new
`VarDesc.VarGuid` via `SeedGuidFromJoined(<uds_path>:uds_var:<friendly>)`
and reroutes through `RenameVariable` so `VarName` regenerates from the
seeded VarGuid. Reuses `blueprint_structural._resolve_pin_type` for the
type spec catalog — same terse forms as `add_bp_variable` /
`add_local_variable` (`"int"` / `"struct:/Script/..."` / `"array:real"`
/ etc.).

`default_value` is the literal default in the same string format
`FStructVariableDescription::DefaultValue` accepts — `"true"` for bool,
`"42"` for int, `"(X=1.0,Y=2.0,Z=0.0)"` for vectors, `""` for
type-default. On non-empty input, the bridge writes the default via
`ChangeVariableDefaultValue` in the same call so VarDesc +
DefaultInstance stay in sync.

Idempotent on `member_name`: if a member with the same friendly name
already exists, returns `success=True` with
`skipped="member already exists"`. Type / default-value compatibility
is NOT verified on the skip path.

### `remove_uds_member(uds_path, member_name)` *(M28.4.3)*

Remove a member variable by friendly name from a `UUserDefinedStruct`.
Seventh op of the M28.4 catalog.

```python
remove_uds_member(
    uds_path="/Game/AI/Structs/S_TargetInfo",
    member_name="BpxAutoBool",
)
```

Wraps the M28.4.3 `RemoveUserDefinedStructMember` UFUNCTION which
resolves `member_name` → VarGuid via the VarDescriptions friendly-name
walk and calls `FStructureEditorUtils::RemoveVariable`.

Idempotent on `member_name`: missing member returns `success=True`
with `skipped="member already absent"`. Supports destructive-op
soak round 2 replay.

Refuses to empty the struct: if the target is the last member
(pre-remove count == 1), returns a structured error matching the
engine's `bAllowToMakeEmpty=false` invariant
(StructureEditorUtils.cpp:327). Plan authors should add the
replacement member BEFORE removing the last existing one — the
canonical squad-director `S_TargetInfo` thicken plan chains
`create_user_defined_struct` → `add_uds_member × N` →
`remove_uds_member(BpxAutoBool)` in that order.

### `set_uds_member_default(uds_path, member_name, value)` *(M28.4.3)*

Set a member variable's default value on a `UUserDefinedStruct`.
Eighth op of the M28.4 catalog; closes the UDS quartet.

```python
set_uds_member_default(
    uds_path="/Game/AI/Structs/S_TargetInfo",
    member_name="ExposureScore",
    value=0.5,
)
```

Wraps the M28.4.3 `SetUserDefinedStructMemberDefault` UFUNCTION which
calls `FStructureEditorUtils::ChangeVariableDefaultValue` — writes
`VarDesc.DefaultValue` (the authoritative string) and fires
`OnStructureChanged(DefaultValueChanged)` which triggers
`RecreateDefaultInstanceInEditorData` so the serialized string and
`DefaultInstance` memory stay in sync. M28.4.0 research Open
Question #1 selected this path over re-routing through the generic
`SetPropertyValue` bridge (which would leave the UDS in a torn state
where the serialized string said X but memory said Y).

`value` accepts strings (passed verbatim for composite literals like
`"(X=1.0,Y=2.0,Z=0.0)"` / `"/Game/DT_Foo.DT_Foo"`) and scalars (ints /
floats / bools are coerced to their ExportText form).

Idempotent: compares existing `VarDesc.DefaultValue` against the
normalized value up-front; match → `skipped="value already match"`
without invoking the engine call. Missing member returns a
structured error (not a silent no-op) — typos should surface at
plan-execute time, not get hidden behind idempotent skip semantics.

### `add_local_variable(bp_path, function_name, var_name, var_type_spec, default_value="")` *(M28.3.4)*

Append a local variable to a Blueprint function's `K2Node_FunctionEntry`.
Final planned op of the M28.3 catalog. Different shape from the M28.3.1–.3
K2Node-spawn ops — extends the existing Entry node's
`LocalVariables: TArray<FBPVariableDescription>` rather than creating a new
K2Node. Ships last per the M28.3.0 research sequencing so the Entry-node
machinery is fully exercised by the prior phases.

```python
add_local_variable(
    bp_path="/Game/AI/BP_UtilityScorer",
    function_name="ScoreTarget",
    var_name="BestScore",
    var_type_spec="real",
    default_value="0.0",
)
```

Wraps the M28.3.4 `AddLocalVariableDeterministic` UFUNCTION which calls
`FBlueprintEditorUtils::AddLocalVariable` then overrides the engine-assigned
`VarGuid` with a md5-seeded value so replay is byte-stable. Reuses the
M28.2.1 `_resolve_pin_type` spec parser from `blueprint_structural.py` —
same compact string forms (`"int"` / `"struct:/Script/..."` /
`"array:int"` / etc.).

`function_name` must resolve to a function graph or interface-override
graph (has a `UK2Node_FunctionEntry`). Ubergraphs are rejected — they
don't carry local variables.

Idempotent: if a local variable with `var_name` already exists on the
target function's `LocalVariables[]`, returns `success=True` with
`skipped="local variable already exists"`. Local vars with the same name
in DIFFERENT functions are allowed (determinism seed includes function
name: `md5(<bp>:func:<fn>:localvar:<varname>)`).

Does NOT call `MarkBlueprintAsStructurallyModified` a second time —
`AddLocalVariable` marks internally on the success path. Per the M26.1.2
regression-chase lesson, double-marking re-enters structurally-modified
listeners and invalidates freshly-seeded GUIDs before the subsequent
compile + save.

Design.md drivers: utility-scorer per-score scratch state (item #2),
squad-director per-call vars (item #1), polish-pass state (item #8).
Any function body that needs transient state without polluting the BP's
member-variable surface.

### `add_function_override(bp_path, function_name)` *(M28.12)*

Override a native virtual UFUNCTION inherited from the Blueprint's parent
class hierarchy. Surfaced 2026-04-27 by the design.md MCP-only test against
UE_DOW_Legacy: pre-M28.12 the only function-authoring surface was
`add_bp_function`, which always created a fresh void/void function — wrong
shape when the user wanted to override an inherited virtual like
`UEnvQueryTest_BlueprintBase::ReceiveTestCondition`.

```python
add_function_override(
    bp_path="/Game/AI/BPC_Cond_HasOrder",
    function_name="ReceiveTestCondition",
)
```

Wraps the M28.12 `BpxReflectionOps::AddFunctionOverrideDeterministic`
UFUNCTION which:

1. Resolves the parent UFUNCTION via
   `Blueprint->ParentClass->FindFunctionByName(FunctionName)`. The engine
   helper walks the entire ancestor chain (parent → grandparent → ...) so
   any overridable virtual from any ancestor is reachable.
2. Validates `FUNC_BlueprintEvent` is set (the flag UHT applies to
   `BlueprintImplementableEvent` and `BlueprintNativeEvent` UFUNCTIONs).
   Plain `BlueprintCallable` virtuals without the event flag are NOT
   user-overridable from BP — the bridge rejects them with a structured
   error matching the BP editor's "Override Function" menu visibility.
3. Calls
   `FBlueprintEditorUtils::AddFunctionGraph<UClass>(BP, NewGraph,
   /*bIsUserCreated*/ false, ParentClass)` — same template variant
   `OverrideInterfaceFunction` (M26.1) uses for interface overrides. UE
   walks the class for a matching-name UFUNCTION and uses its signature
   to build the Entry node's pins. `bIsUserCreated=false` flags this as
   an override so the editor's function-list panel groups it under
   "Override Functions".
4. Auto-spawns a `K2Node_FunctionResult` with deterministic
   `BpxFuncResult_<FunctionName>` name + seeded NodeGuid + pin IDs when
   the parent UFUNCTION has output / return parameters. Mirrors
   `OverrideInterfaceFunction`'s post-spawn pass — UE only auto-creates
   Entry, not Result, when going through the `<UClass>` template variant.
5. Reseeds `GraphGuid` + Entry / Result `NodeGuid` + pin IDs via
   `SeedGuidFromJoined(<bp>:override_func:<fn>:<slot>)`. Distinct prefix
   (`override_func` vs fresh-function `func`) so a name collision between
   a fresh function and an override on the same BP — illegal at compile
   time but possible mid-authoring — produces distinct seeds.

`function_name` is an FName matching a parent-class UFUNCTION declaration.
Common drivers from design.md:

- `"ReceiveTestCondition"` on `UEnvQueryTest_BlueprintBase` (returns
  bool, the M28.12 driver case)
- `"K2_ShouldAbilityRespondToEvent"` on `UGameplayAbility` (returns bool,
  takes 2 struct params — exercises typed-pin mirror in the M28.pre.3
  soak fixture)
- `"K2_CanActivateAbility"` / `"K2_ActivateAbility"` etc. on
  `UGameplayAbility`

Idempotent: if a graph with this name already exists on the BP (whether
authored as fresh or as a prior override), returns `success=True` with
`skipped="function override already exists"` and populates the existing
graph's Entry / Return GUIDs so chained authoring ops still work.

Determinism: per the seed key above. Round 2 of the M28.pre.3 soak hits
the idempotence skip path with byte-identical bytes — surfaced by the
`add_function_override.json` fixture against `BP_GAS_Ability`.

Distinguished from siblings:

- `add_bp_function` (M28.2.2) — fresh void/void function. Use when
  authoring a NEW function.
- `OverrideInterfaceFunction` / `add_bp_interface` (M26.1 + M28.2.4) —
  interface override. Use when the function lives on a BP interface
  attached via `Blueprint->ImplementedInterfaces[]`, not on the parent
  class chain.
- `add_function_override` (this op) — native parent-class virtual
  override. Use when the function is `BlueprintImplementableEvent` /
  `BlueprintNativeEvent` declared on `Blueprint->ParentClass` or any
  ancestor.

### `add_function_input(bp_path, function_name, pin_name, var_type_spec, default_value="")` *(M28.11)*

Append a typed input parameter to a Blueprint function's `K2Node_FunctionEntry`.
Surfaced 2026-04-27 by the design.md MCP-only test against UE_DOW_Legacy:
the pre-M28.11 surface created void/void functions only and no op authored
function-signature pins. Wraps the M28.11 `BpxReflectionOps::AddFunctionUserDefinedPin`
UFUNCTION via `K2Node_EditablePinBase::CreateUserDefinedPin`.

```python
add_function_input(
    bp_path="/Game/AI/BP_EncounterDirector",
    function_name="IssueOrder",
    pin_name="OrderTag",
    var_type_spec="struct:/Script/GameplayTags.GameplayTag",
    default_value="",
)
```

The pin lives on the function's Entry node (UE pin direction `EGPD_Output` —
the entry's outputs flow INTO the function body, hence they appear as the
function's inputs in the BP editor's Details panel). `function_name` accepts
function graphs and interface-override graphs; ubergraphs are rejected
bridge-side (events use `add_custom_event_input`).

Reuses the M28.2.1 `_resolve_pin_type` spec parser — same compact string
forms (`"int"` / `"struct:/Script/..."` / `"object:/Script/..."` /
`"array:int"` / `"map:name=>>>:int"` / etc.).

Idempotent on `pin_name`: walks `K2Node_FunctionEntry::UserDefinedPins` by
name; match returns `success=True` with `skipped="user-defined pin already
exists"` without modifying the existing pin's type or default. Type
compatibility is NOT verified on the skip path — same semantics as
`add_bp_variable`.

Determinism: PinId is seeded post-create as
`md5(<bp>:entry:<fn>:userpin:<pin>:out)`. Without this, replay drifts (engine
assigns `FGuid::NewGuid()` in `UEdGraphPin::CreatePin`); M28.pre.3 soak
round 2 catches it.

Design.md driver: encounter-director ↔ AI.Order custom-event channel (item
#1) — typed function inputs replace the member-variable handshake workaround
when an existing function call is the order's surface (e.g.
`IssueOrder(OrderTag, TargetActor, Priority)`).

### `add_function_output(bp_path, function_name, pin_name, var_type_spec)` *(M28.11)*

Append a typed output parameter to a Blueprint function's `K2Node_FunctionResult`.
Sibling of `add_function_input` — the pin lives on the Result node (UE pin
direction `EGPD_Input` — the result's inputs receive FROM the function body,
appearing as the function's outputs in the editor's Details panel).

```python
add_function_output(
    bp_path="/Game/AI/BP_UtilityScorer",
    function_name="ScoreTarget",
    pin_name="Score",
    var_type_spec="real",
)
```

**Result-node auto-spawn:** if the target function has no `K2Node_FunctionResult`
(pure-flagged via `add_bp_function(..., is_pure=True)` skips the engine's
auto-Result on create), the bridge spawns one with deterministic `NodeGuid`
+ pin IDs seeded from `<bp>:func:<fn>:result` (the same key
`AddFunctionGraphDeterministic` uses for the auto-spawned Result, so byte-
identity is preserved across the create-pure-then-add-output and the
non-pure-from-create paths). Authors don't need a separate "spawn Result"
step.

No `default_value` kwarg: function output pins don't carry a runtime default
(BP editor suppresses the Default Value field on Result-node pins). The
bridge would accept the assignment harmlessly via
`ModifyUserDefinedPinDefaultValue` but the field is never read.

Idempotent on `pin_name`: walks `K2Node_FunctionResult::UserDefinedPins` by
name. Determinism: PinId seeded as
`md5(<bp>:result:<fn>:userpin:<pin>:in)`.

Design.md driver: utility scorer + tactical-AI helper functions that need
typed outputs (e.g. `EvaluateCover` returning a cover-quality score).

### `add_custom_event_input(bp_path, graph_name, event_name, pin_name, var_type_spec, default_value="")` *(M28.11)*

Append a typed input parameter to an existing `K2Node_CustomEvent` in an
ubergraph. Sibling of M28.3.3's `add_custom_event_node` for typed parameter
authoring.

```python
add_custom_event_input(
    bp_path="/Game/AI/BP_EncounterDirector",
    graph_name="EventGraph",
    event_name="OnIssueOrder",
    pin_name="OrderTag",
    var_type_spec="struct:/Script/GameplayTags.GameplayTag",
)
```

The pin lives on the CustomEvent node (UE pin direction `EGPD_Output` —
event's outputs flow INTO the event-handler body, appearing as the event's
inputs in the editor's Details panel).

`graph_name` is informational at the bridge level — the bridge walks every
`Blueprint->UbergraphPages` for a `UK2Node_CustomEvent` whose
`CustomFunctionName == event_name`. Kept in the Python signature for symmetry
with `add_custom_event_node` and so plan authors can grep their plan against
their mental model. Future scoping (multiple ubergraphs with same-named
events) can use the kwarg without breaking existing plans.

Idempotent on `pin_name`: walks the event node's `UserDefinedPins` by name.
Determinism: PinId seeded as
`md5(<bp>:custom_event:<event>:userpin:<pin>:out)`.

Design.md driver: encounter-director ↔ AI.Order custom-event channel
(item #1). With M28.11 shipped, the order channel can drop the
member-variable handshake workaround (`PendingOrderTag` /
`PendingOrderTarget`) and use typed event params throughout —
`OnIssueOrder(OrderTag, TargetActor, Priority)` becomes a single self-
documenting event signature.

### `add_gameplay_tag(tag_name, dev_comment="", source_ini="DefaultGameplayTags.ini", is_restricted=False)` *(M28.6.1)*

Append a new gameplay tag to a project ini source. First (and only planned)
op of the M28.6 GameplayTag write-side catalog. Wraps UE's editor-side
`IGameplayTagsEditorModule::AddNewGameplayTagToINI` engine API via the
M28.6.1 `BpxReflectionOps::AddGameplayTag` UFUNCTION.

```python
add_gameplay_tag(
    tag_name="AI.Order.Flank",
    dev_comment="Squad-director command: hold position and call shots",
    source_ini="DefaultGameplayTags.ini",
)
```

Engine handles the file write (via `UObject::TryUpdateDefaultConfigFile`),
alpha-sorts the resulting `+GameplayTagList=(...)` list deterministically,
and refreshes the in-memory tag tree so subsequent `IsDictionaryTag` /
`RequestAllGameplayTags` queries see the new tag immediately. No
`compile_and_save_package` call needed — there's no UAsset to save.

`source_ini` resolution (per M28.6.0 research findings):

- `"DefaultGameplayTags.ini"` (default) → `<Project>/Config/DefaultGameplayTags.ini`,
  mapped to `UGameplayTagsSettings`'s pre-registered source.
- Any other name like `"AI.ini"` → `<Project>/Config/Tags/AI.ini`,
  creating both the file and the source registration on first add.

**Per-machine override caveat:** when the developer has set
`UGameplayTagsDeveloperSettings::DeveloperConfigName` in their project
settings, `"DefaultGameplayTags.ini"` (or empty) gets diverted to
`<Project>/Config/<DeveloperConfigName>.ini`. This is engine behaviour for
per-developer staging — the op cannot bypass it. To force a deterministic
per-source ini across machines, pass an explicit non-default name.

Idempotent on `(tag_name, source_ini)`: the bridge UFUNCTION pre-checks
via `UGameplayTagsManager::IsDictionaryTag` so a re-apply against an
already-registered tag returns `success=True, skipped="tag already
registered"` without re-writing the .ini file. Critical for M28.pre.3
soak round-2 byte-identity — the engine API itself returns `false` on
duplicate-add, so the pre-check is what produces the real skip signal.

`is_restricted` defaults to `False`. When `True`, authors a
`+RestrictedGameplayTagList=` entry instead. Restricted tags have
parent-chain rules the engine enforces (cannot be children of
non-restricted tags); the bridge surfaces engine-side rejections as a
structured error. M28.6.1 has no soak coverage for the restricted path
(no design.md driver) — exposed for forward compat.

Determinism: zero `FGuid::NewGuid()` / `MakeUniqueObjectName` on the engine
write path (verified M28.6.0 research). The editor module's
`UGameplayTagsList::SortTags` runs before each write so on-disk order is
byte-deterministic across runs. The ONE machine-level drift source is the
`DeveloperConfigName` diversion described above.

Perforce: `IGameplayTagsEditorModule::AddNewGameplayTagToINI` calls
`GameplayTagsUpdateSourceControl` before AND after the ini write. If the
project has Perforce configured (env vars / .p4config / project ini), the
target .ini gets auto-checked-out as part of the save. The MCP-side
`apply_plan` `confirm=True` gate is the user's checkpoint for that side
effect — no separate mitigation in the op itself.

Validation: relies on the engine's internal `IsValidGameplayTagString`
pre-check (called inside `AddNewGameplayTagToINI`). Forbidden characters
per `UGameplayTagsSettings::InvalidTagCharacters` (typically `"\"\',"`)
and structural rules (no leading/trailing dot, no double-dots) trigger an
engine-side rejection; the bridge surfaces a structured "try X instead"
suggestion when the engine produces a fixed-string fallback.

Design.md drivers: item #1 (squad director + `AI.Order.*` event channel:
`AI.Order.Flank`, `AI.Order.Suppress`, `AI.Order.Hold`) and item #4
(callouts / pre-grenade lean / committed cover-to-cover anim: 
`AI.Callout.Grenade`, `AI.Callout.Reload`, `AI.Anim.PreGrenadeLean`).
Both unblocked by being able to author tags from a plan rather than via
manual .ini editing.

## Known caveats

- **UE .uasset saves are not byte-deterministic.** md5 can differ across
  saves even when authored state is identical. Use DeepDump diff (not md5)
  as the correctness oracle in M22 fixtures.
- **`create_child_bp` parent-class match** — the pre-M28.10.1 caveat that
  `BlueprintGeneratedClass.get_super_class` wasn't exposed uniformly
  across UE 5.x Python bindings is **closed by M28.10.1**. Both
  `create_blueprint_class` and `create_child_bp` now verify parent
  match via C++ pointer equality on `Existing->ParentClass` in the
  `CreateBlueprintClassDeterministic` bridge UFUNCTION.

## Coming next

M23.2+ StateTree (extend the shipped pair):
- `set_state_type(st_path, state_path, state_type)`

M21.2 variable / function authoring:
- `add_bp_variable` / `add_bp_function` / `add_component_to_scs` /
  `add_bp_interface` shipped in M28.2.1 – M28.2.4 — see the structural
  edits block above.
- `bind_delegate_handler(bp_path, delegate_name, handler_function_name)`
  still pending.

M28.3 node-level graph authoring — COMPLETE (2026-04-24):
- `add_branch_node` / `set_graph_pin_default` (M28.3.1)
- `add_call_function_node` / `add_variable_get_node` / `add_variable_set_node`
  (M28.3.2)
- `add_custom_event_node` / `add_execution_sequence_node` /
  `add_dynamic_cast_node` (M28.3.3)
- `add_local_variable` (M28.3.4)
- 9 ops total, all idempotent on determinism seed keys, pin names +
  NodeGuids byte-stable round-to-round per the M28.pre.3 soak invariant.
  See the `Worked example — "wire OnOrderReceived body via M28.3 node
  spawns"` block in `plans/AGENT_LOOP.md` for the full chained-authoring
  pattern used by every design.md body-wiring case.

M28.11 typed function / custom-event parameter authoring — COMPLETE (2026-04-27):
- `add_function_input` / `add_function_output` (function Entry / Result
  user-defined pins; Result auto-spawned with deterministic GUIDs if the
  function was created pure-flagged)
- `add_custom_event_input` (CustomEvent user-defined pins; ubergraph
  walker resolves the target event by `CustomFunctionName`)
- 3 ops total, all sharing one bridge UFUNCTION
  (`AddFunctionUserDefinedPin`) that wraps
  `K2Node_EditablePinBase::CreateUserDefinedPin` and reseeds the new
  `UEdGraphPin::PinId` deterministically. Idempotent on
  `UserDefinedPins` name match. With M28.11 shipped, design.md's
  encounter-director ↔ AI.Order channel can drop the
  member-variable handshake workaround and use typed event params
  throughout.

M28.12 native virtual override authoring — COMPLETE (2026-04-27):
- `add_function_override` (overrides `BlueprintImplementableEvent` /
  `BlueprintNativeEvent` UFUNCTIONs declared on the parent-class chain;
  signature auto-mirrored from parent via
  `AddFunctionGraph<UClass>(...,ParentClass)`; Result node auto-spawned
  with deterministic NodeGuid when parent has output / return params).
- 1 op total. New bridge UFUNCTION
  `AddFunctionOverrideDeterministic` parallels `OverrideInterfaceFunction`
  (M26.1) but targets `Blueprint->ParentClass` instead of an
  `ImplementedInterfaces[]` entry. With M28.12 shipped, design.md's
  driver case (`UEnvQueryTest_BlueprintBase::ReceiveTestCondition`
  override) is end-to-end authorable from a plan; agents no longer hit
  the wall where overriding inherited virtuals required a manual editor
  click.

M28.13 K2Node_MacroInstance authoring (loop unblocker) — COMPLETE (2026-04-27):
- `add_macro_instance_node` (spawns `UK2Node_MacroInstance` pointed at an
  external macro graph; mirrors the macro's Tunnel/Result pins onto the
  instance via the inherited `UK2Node_Tunnel::AllocateDefaultPins`).
- 1 op total. New bridge UFUNCTION `AddMacroInstanceNode` adjacent to
  the M28.3.x atomic K2Node spawn family — only delta is the pre-alloc
  `MacroGraphReference.SetGraph(MacroGraph)` call so the pin walk has
  the macro to iterate. With M28.13 shipped, design.md's five "iterates
  X → blocked" sections (BroadcastOrder/AssignRole iteration,
  ScorerScoringLoop, ConfidenceDecay×2, SharedPerception) become
  authorable via `add_macro_instance_node` + `connect_graph_pins`.
  Macro library resolution is Python-side via `unreal.load_object` +
  `MacroGraphs[]` walk; supports both engine-shipped
  `/Engine/EditorBlueprintResources/StandardMacros` and user-authored
  `/Game/Macros/...` libraries.

M28.14 struct-mutation node catalog — COMPLETE (2026-04-28):
- `add_make_struct_node` (spawns `UK2Node_MakeStruct` — pure node
  constructing a struct value from per-field input pins).
- `add_break_struct_node` (spawns `UK2Node_BreakStruct` — pure node
  splitting a struct input into per-field output pins).
- `add_set_fields_in_struct_node` (spawns `UK2Node_SetFieldsInStruct` —
  imperative node setting a configurable subset of struct fields and
  emitting the modified struct as output; required `fields_to_show`
  list because the SetFields pin manager defaults `bShowPin=false` for
  every field).
- 3 ops total sharing a templated `PrepStructNodeSpawn` scaffold in
  `BpxReflectionOps`. Make/Break write the standard
  `StructType + bMadeAfterOverridePinRemoval = true` pre-alloc config
  matching the engine's editor spawn path; SetFields adds a post-alloc
  `ShowPinForProperties` walk + `ReconstructNode()` to honor
  `fields_to_show`. With M28.14 shipped, design.md's read-modify-write
  patterns inside the M28.13 ForEachLoop body (UAIActionScorer per-element
  score updates, confidence-decay over `S_TargetInfo` arrays) are
  end-to-end authorable from a plan.

M28.5 EQS write-side — COMPLETE (2026-04-24):
- `add_eqs_option` (M28.5.1)
- `add_eqs_test` / `remove_eqs_test` (M28.5.2)
- `set_eqs_generator_property` / `set_eqs_test_property` (M28.5.3)
- 5 ops total. Option / test create-remove use the M28.5.x UFUNCTION
  family on `UBpxReflectionOps` with explicit-FName NewObject determinism;
  scalar property setters reuse the existing M23.1 `SetPropertyValue`
  reflection bridge via nested paths (e.g.
  `["Options", "[0]", "Tests", "[2]", "ScoringFactor", "DefaultValue"]`)
  — Python-only wrappers with no new UFUNCTION. All five ops idempotent
  on their identifier keys.

M28.4 non-BP asset factories — COMPLETE (2026-04-24):
- `create_curve_float` / `set_curve_float_keys` (M28.4.1) — shipped.
- `create_data_asset_instance` / `set_data_asset_property` (M28.4.2) —
  shipped.
- `create_user_defined_struct` / `add_uds_member` / `remove_uds_member`
  / `set_uds_member_default` (M28.4.3) — shipped.
- 8 ops total across 3 new Python modules (`curves.py` / `data_assets.py`
  / `uds.py`). 6 new UFUNCTIONs on `UBpxReflectionOps`
  (`CreateCurveFloatDeterministic` + `SetCurveFloatKeys` +
  `CreateDataAssetInstanceDeterministic` +
  `CreateUserDefinedStructDeterministic` + `AddUserDefinedStructMember`
  + `RemoveUserDefinedStructMember` + `SetUserDefinedStructMemberDefault`;
  `set_data_asset_property` reuses the existing M23.1 `SetPropertyValue`
  bridge — zero new UFUNCTION there).
- M28.4.1 ships 2 ops: `create_curve_float` wraps `NewObject<UCurveFloat>`
  + AssetRegistry notification for fresh `/Game/` curves (idempotent on
  path — hard error on different-class collision); `set_curve_float_keys`
  wholesale-replaces the `FRichCurve::SetKeys` array (idempotent on
  element-wise `(Time, Value, InterpMode)` compare). UCurveFloat has
  zero FGuid usage per the M28.4.0 research so explicit FName on
  NewObject is the only determinism lever. Per-key add/edit/remove
  deferred; wholesale matches the design.md intensity-curve authoring
  style.
- M28.4.2 ships 2 ops: `create_data_asset_instance` wraps
  `NewObject<UDataAsset>(Pkg, DAClass, RF_Public|RF_Standalone|RF_Transactional)`
  for fresh `/Game/` DA instances (idempotent on path; class-mismatch at
  the same path is a structured error); `set_data_asset_property` is a
  Python-only wrapper over the existing M23.1 `SetPropertyValue` bridge
  — zero new UFUNCTIONs. Flags mirror `UDataAssetFactory::FactoryCreateNew`
  so scripted creates match interactive-editor output. Covers native DA
  classes (`/Script/<Module>.<ClassName>`) and BP-derived DA classes
  (`/Game/<path>/<Name>.<Name>_C`). UDataAsset / UPrimaryDataAsset have
  zero FGuid usage per the M28.4.0 research so explicit FName on
  NewObject is the only determinism lever.
- M28.4.3 ships 4 ops: `create_user_defined_struct` wraps
  `FStructureEditorUtils::CreateUserDefinedStruct` and closes both of
  the engine's `FGuid::NewGuid()` determinism traps
  (`Struct->Guid` and the auto-bool's `VarGuid`) via `SeedGuidFromJoined`
  + a post-create `RenameVariable` pass that regenerates `VarName` from
  the seeded Guid. The auto-bool stays in the fresh struct (renamed to
  `BpxAutoBool`) because the engine's `bAllowToMakeEmpty=false`
  invariant refuses to remove the last member — plan authors drop it
  once at least one real member is added. `add_uds_member` /
  `remove_uds_member` follow the same seed-then-rename recipe;
  `set_uds_member_default` routes through `ChangeVariableDefaultValue`
  so `VarDesc.DefaultValue` and `DefaultInstance` memory stay in sync
  (M28.4.0 research Open Question #1 selected this path over a direct
  `SetPropertyValue` write on the DefaultInstance, which would have
  left the UDS in a torn state). All four ops idempotent on the
  `(uds_path, member_name)` identifier key; M28.pre.3 soak stable
  round-to-round.

M21.3 perception tuning helpers (deferred):
- `set_perception_sense_config(bp_path, sense_class, property_name, value)` —
  a convenience op that layers on top of `set_instanced_subobject_property`
  by resolving the sense config instance by class rather than by index.

M22: every op above lands with a BugHunt fixture + DeepDump-diff assertion.

## Deferred: retrofit M21.0 ops onto the bridge

The original M23.2 scope (WIP §9) called for porting the M21.0 CDO /
component / instanced ops onto `unreal.BpxReflectionOps`. Skipped in this
pass because the M21.0 ops work for their documented cases (via
`get_editor_property` / `set_editor_property`) and a full retrofit needs:
- a Python→ImportText converter for rich UE types (`Vector2D`, `Rotator`,
  etc.) to go through the bridge's string-based `SetPropertyValue`, **and**
- M22 fixture tests to prove the retrofit does not regress existing
  behaviour.

Neither exists today. Revisit when the first M21.0 op surfaces a case
`set_editor_property` can't handle (most likely: a natively-declared
protected property the editor path can't reach, or a StateTree-adjacent
edit where the existing M21.0 path can't find the container).
