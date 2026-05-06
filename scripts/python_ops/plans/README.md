# EditPlan schema

A plan is a JSON document describing a batch of asset edits to execute
through the `python_ops` library, verify mechanically, and (for an LLM
caller) confirm semantically afterwards. Plans exist so that an edit
request and the resulting on-disk diff can be audited independently.

This file defines the JSON schema. For **how to use the schema** when
picking up a user edit request — the 8-step loop, error-handling per
step, retry heuristics, anti-patterns — see `AGENT_LOOP.md`.

The M24 loop built on top of this schema:

1. **Export** — deep-dump the target assets. *Already done via the
   BlueprintExporter plugin.*
2. **Understand** — Claude reads the dumps.
3. **Plan** — Claude writes an `EditPlan` JSON. *This document describes
   the format.*
4. **Validate** — `plan_validator.py` reads the plan, resolves every
   target + path via the M23 reflection bridge without mutating anything,
   confirms types + refs exist, rejects before any bytes move.
   *Ships in M24.1.*
5. **Apply** — `plan_executor.py` runs each op in order, snapshotting
   before / after state. *Ships in M24.2.*
6. **Verify mechanically** — `mechanical_diff.py` re-exports each
   touched asset, diffs against the pre-run snapshot, asserts
   `changed_fields ⊆ plan.expected_fields`. *Ships in M24.3.*
7. **Verify semantically** — Claude re-reads post-export dumps.
8. **Escalate only experiential** — "does it feel right?" → user PIE
   test. Everything else loops automatically.

Steps 4–6 are what this schema is designed to feed. Claude writes the
plan once; the tooling does the rest.

## Canonical shape

```jsonc
{
  "intended_outcome": "One-sentence prose. Why this plan exists.",
  "risk_level": "low" | "medium" | "high",
  "operations": [
    {
      "op": "<op-name>",
      // op-specific parameters — see "Op vocabulary" below
    }
  ],
  "expected_side_effects": [
    "<asset path>.uasset md5 will change",
    "<asset path> will be created",
    "<asset path> will recompile"
  ],
  "verification": [
    { "path": ["/Game/.../Asset", "Field"], "expected": <value> },
    { "asset_exists": "/Game/.../NewAsset" },
    { "asset_absent":  "/Game/.../OldAsset" }
  ]
}
```

Top-level fields are **all required** except `verification`
(recommended; empty list is fine for no-verify plans). Validator
rejects any plan missing `intended_outcome`, `risk_level`, or
`operations`.

## Op vocabulary

Every `op` name in `operations[]` must match a function re-exported from
`python_ops.__init__`. As of M23.2 that is:

| op name | kwargs |
|---|---|
| `set_bp_variable_default` | `bp_path`, `var_name`, `value` |
| `set_component_property` | `bp_path`, `component_name`, `property_name`, `value` |
| `set_instanced_subobject_property` | `bp_path`, `path`, `property_name`, `value` |
| `create_child_bp` | `parent_bp_path`, `new_bp_path` |
| `rename_asset` | `old_path`, `new_path` |
| `add_statetree_enter_condition` | `st_path`, `state_path`, `condition_bp_path` |
| `remove_statetree_enter_condition` | `st_path`, `state_path`, `condition_bp_path` |
| `verify_state_enter_conditions` | `st_path`, `state_path` |
| `add_statetree_transition` | `st_path`, `state_path`, `trigger`, `target_state_path`, *opt:* `priority`, `event_tag` |
| `remove_statetree_transition` | `st_path`, `state_path`, `trigger`, `target_state_path` |
| `verify_state_transitions` | `st_path`, `state_path` |
| `implement_interface_function` | `bp_path`, `interface_bp_path`, `function_name`, `output_bindings`, *opt:* `force_rebind` |
| `add_statetree_task_to_state` | `st_path`, `state_path`, `task_bp_path` |
| `remove_statetree_task_from_state` | `st_path`, `state_path`, `task_bp_path` |
| `verify_state_tasks` | `st_path`, `state_path` |
| `connect_graph_pins` | `bp_path`, `graph_name`, `from_node_guid`, `from_pin`, `to_node_guid`, `to_pin` |
| `set_level_actor_property` | `level_path`, `actor_label`, `property_path`, `value` |
| `add_bp_variable` | `bp_path`, `var_name`, `var_type_spec`, *opt:* `default_value`, `instance_editable` |
| `add_bp_function` | `bp_path`, `function_name`, *opt:* `is_pure` |
| `add_component_to_scs` | `bp_path`, `component_class_path`, `component_name`, *opt:* `parent_component_name` |
| `add_bp_interface` | `bp_path`, `interface_class_path` |
| `add_branch_node` | `bp_path`, `graph_name`, `position` |
| `set_graph_pin_default` | `bp_path`, `graph_name`, `node_guid`, `pin_name`, `literal_text` |
| `add_call_function_node` | `bp_path`, `graph_name`, `function_name`, `position`, *opt:* `target_class_path` |
| `add_variable_get_node` | `bp_path`, `graph_name`, `variable_name`, `position`, *opt:* `target_class_path` |
| `add_variable_set_node` | `bp_path`, `graph_name`, `variable_name`, `position`, *opt:* `target_class_path` |
| `add_custom_event_node` | `bp_path`, `graph_name`, `event_name`, `position` |
| `add_execution_sequence_node` | `bp_path`, `graph_name`, `num_outputs`, `position` |
| `add_dynamic_cast_node` | `bp_path`, `graph_name`, `target_class_path`, `position` |
| `add_local_variable` | `bp_path`, `function_name`, `var_name`, `var_type_spec`, *opt:* `default_value` |
| `add_eqs_option` | `eqs_path`, `generator_class_path` |
| `add_eqs_test` | `eqs_path`, `option_index`, `test_class_path` |
| `remove_eqs_test` | `eqs_path`, `option_index`, `test_index` |
| `set_eqs_generator_property` | `eqs_path`, `option_index`, `property_path`, `value` |
| `set_eqs_test_property` | `eqs_path`, `option_index`, `test_index`, `property_path`, `value` |
| `create_curve_float` | `curve_path` |
| `set_curve_float_keys` | `curve_path`, `keys` |
| `create_data_asset_instance` | `asset_path`, `parent_class_path` |
| `set_data_asset_property` | `asset_path`, `property_path`, `value` |
| `create_user_defined_struct` | `uds_path` |
| `add_uds_member` | `uds_path`, `member_name`, `var_type_spec`, *opt:* `default_value` |
| `remove_uds_member` | `uds_path`, `member_name` |
| `set_uds_member_default` | `uds_path`, `member_name`, `value` |
| `add_gameplay_tag` | `tag_name`, *opt:* `dev_comment`, `source_ini`, `is_restricted` |

The JSON shape for each op is **the op's `kwargs` flattened into the
operation object**, alongside `"op": "<name>"`. No wrapper object, no
positional args. Extra fields are a validator error.

### Examples per op

```jsonc
// Variable default on the generated class's CDO
{
  "op": "set_bp_variable_default",
  "bp_path": "/Game/CombatPrototype/DrewPrototype/ActorComponents/AC_AIWeaponController",
  "var_name": "Damage",
  "value": 12.0
}

// Flat UPROPERTY on an SCS component template
{
  "op": "set_component_property",
  "bp_path": "/Game/CombatPrototype/DrewPrototype/BP_EnemyBase_AIController",
  "component_name": "AIPerception",
  "property_name": "bAutoActivate",
  "value": true
}

// Nested property on an instanced subobject
{
  "op": "set_instanced_subobject_property",
  "bp_path": "/Game/CombatPrototype/DrewPrototype/BP_EnemyBase_AIController",
  "path": ["AIPerception", "SensesConfig", 0],
  "property_name": "SightRadius",
  "value": 1500.0
}

// New BP subclass
{
  "op": "create_child_bp",
  "parent_bp_path": "/Game/CombatPrototype/DrewPrototype/BP_EnemyBase",
  "new_bp_path":    "/Game/Runtime/AI/BP_EnemyBase_Team1"
}

// Rename / move
{
  "op": "rename_asset",
  "old_path": "/Game/Loadout/BP_Rifle",
  "new_path": "/Game/Weapons/BP_Rifle_AR1"
}

// Add a BP-backed condition to a StateTree state's EnterConditions
{
  "op": "add_statetree_enter_condition",
  "st_path":            "/Game/CombatPrototype/DrewPrototype/ST_EnemyBase",
  "state_path":         ["SubTrees", "[2]", "Children", "[3]"],
  "condition_bp_path":  "/Game/CombatPrototype/DrewPrototype/ST_Cond_CanSeeTarget"
}

// Symmetric remove
{
  "op": "remove_statetree_enter_condition",
  "st_path":            "/Game/CombatPrototype/DrewPrototype/ST_EnemyBase",
  "state_path":         ["SubTrees", "[2]", "Children", "[3]"],
  "condition_bp_path":  "/Game/CombatPrototype/DrewPrototype/ST_Cond_CanSeeTarget"
}

// Read-only: record the current EnterConditions list in the run report.
// Works uniformly for root states (SubTrees[N]) and nested states
// (SubTrees[N].Children[M]) — see "Verifying EnterConditions" below.
{
  "op": "verify_state_enter_conditions",
  "st_path":    "/Game/CombatPrototype/DrewPrototype/ST_EnemyBase",
  "state_path": ["SubTrees", "[2]"]
}

// Create an interface-function override with passthrough bindings.
// `output_bindings` maps each Return-pin name to either "self.<VarName>"
// (VariableGet passthrough) or a literal the schema coerces per pin type.
// Idempotent: if the override graph already exists on `bp_path`, the
// op returns `skipped=<reason>` without touching bindings.
{
  "op": "implement_interface_function",
  "bp_path":            "/Game/CombatPrototype/DrewPrototype/BP_EnemyBase",
  "interface_bp_path":  "/Game/CombatPrototype/DrewPrototype/BPI_Targetable",
  "function_name":      "GetTargetingInfo",
  "output_bindings": {
    "bIsAlive":      "self.bIsAlive",
    "bIsTargetable": "true",
    "Faction":       "self.Faction"
  }
}

// Same override, but this time force-rebind over an existing stub
// (M26.1.1). Use when the inventory `.md` shows the function marked
// `Interface override ... — stub (no authored body)` — i.e. someone
// clicked "add function" on the interface in the editor UI but didn't
// wire anything. The op wipes every non-Entry/non-Return node, then
// re-runs the binding logic. Entry/Return NodeGuids stay stable.
{
  "op": "implement_interface_function",
  "bp_path":            "/Game/CombatPrototype/DrewPrototype/BP_EnemyBase",
  "interface_bp_path":  "/Game/CombatPrototype/DrewPrototype/BPI_Targetable",
  "function_name":      "GetTargetingInfo",
  "output_bindings": {
    "bIsAlive":      "self.bIsAlive",
    "bIsTargetable": "true",
    "Faction":       "self.Faction"
  },
  "force_rebind": true
}

// M28.1 — append a BP-backed task to a state's Tasks array. Mirrors
// add_statetree_enter_condition but targets Tasks (via the
// FStateTreeBlueprintTaskWrapper.TaskClass field). Idempotent on the
// task BP's generated class.
{
  "op":           "add_statetree_task_to_state",
  "st_path":      "/Game/CombatPrototype/DrewPrototype/ST_EnemyBase",
  "state_path":   ["SubTrees", "[2]", "Children", "[1]"],
  "task_bp_path": "/Game/CombatPrototype/DrewPrototype/BP_Task_OpenFireLoop"
}

// M28.2 — wire two existing pins in a graph. Graph name accepts
// FunctionGraphs / ImplementedInterfaces.Graphs / UbergraphPages.
// Node GUIDs are read from .deep.md (32-char hex, no dashes).
{
  "op":             "connect_graph_pins",
  "bp_path":        "/Game/CombatPrototype/DrewPrototype/BP_Task_Peek",
  "graph_name":     "EventGraph",
  "from_node_guid": "2304ABCD00000000055E0E7F00000000",
  "from_pin":       "else",
  "to_node_guid":   "39040112055E0E7F0000000000000000",
  "to_pin":         "execute"
}

// M28.3 — set a UPROPERTY on one placed actor in a level. value is
// ExportText (plain scalars also accepted; bool/int/float auto-coerced).
{
  "op":            "set_level_actor_property",
  "level_path":    "/Game/CombatPrototype/DrewPrototype/Combat_FlatArena",
  "actor_label":   "BP_EnemyBase_TeamA",
  "property_path": ["Faction"],
  "value":         "1"
}

// M28.2.1 — add a member variable to a Blueprint. var_type_spec uses
// the compact string form documented on `_resolve_pin_type` in
// blueprint_structural.py. default_value is the literal string
// FBPVariableDescription::DefaultValue accepts (the executor bypasses
// type-coercion on this kwarg).
{
  "op":                 "add_bp_variable",
  "bp_path":            "/Game/Squad/BP_SquadDirector",
  "var_name":           "bActiveOrder",
  "var_type_spec":      "bool",
  "default_value":      "false",
  "instance_editable":  true
}

// M28.2.2 — add a blank function graph. Returned entry_guid/return_guid
// feed the M26.1 body-authoring ops in a follow-up plan.
{
  "op":            "add_bp_function",
  "bp_path":       "/Game/Squad/BP_SquadDirector",
  "function_name": "OnOrderReceived",
  "is_pure":       false
}

// M28.2.3 — add a component to an Actor BP's SCS. Empty
// parent_component_name attaches at SCS root. SCS-to-SCS parenting only.
{
  "op":                    "add_component_to_scs",
  "bp_path":               "/Game/Squad/BP_SquadDirector",
  "component_class_path":  "/Script/AIModule.AIPerceptionComponent",
  "component_name":        "SquadPerception",
  "parent_component_name": ""
}

// M28.2.4 — attach an interface to a Blueprint. The engine auto-creates
// override graphs for non-event interface functions (functions with
// output parameters); pair with implement_interface_function for the
// passthrough body.
{
  "op":                    "add_bp_interface",
  "bp_path":               "/Game/Squad/BP_SquadDirector",
  "interface_class_path":  "/Game/Squad/BPI_OrderListener.BPI_OrderListener_C"
}

// M28.3.3 — spawn a UK2Node_CustomEvent into an ubergraph. Ubergraph-
// only; function / interface-override graphs are rejected with a
// structured error. Default pins: OutputDelegate + then. For events
// with parameters, a subsequent user-defined-pin op is required.
{
  "op":         "add_custom_event_node",
  "bp_path":    "/Game/Squad/BP_SquadDirector",
  "graph_name": "EventGraph",
  "event_name": "OnOrderReceived",
  "position":   [256, 128]
}

// M28.3.3 — spawn a UK2Node_ExecutionSequence with N then_N outputs.
// num_outputs must be in [2, 16]. The engine's AddInputPin API is
// misleadingly named; it adds a THEN-OUT pin per call. The op exposes
// the clean num_outputs parameter so callers don't deal with it.
{
  "op":          "add_execution_sequence_node",
  "bp_path":     "/Game/AI/BP_TaskCallout",
  "graph_name":  "EventGraph",
  "num_outputs": 3,
  "position":    [128, 256]
}

// M28.3.3 — spawn a UK2Node_DynamicCast typed against a UClass.
// target_class_path is required (non-empty). TargetType is set before
// AllocateDefaultPins so the As<TargetClass> output pin is correctly
// typed. Default is an impure cast (three exec outs + bSuccess).
{
  "op":                 "add_dynamic_cast_node",
  "bp_path":            "/Game/AI/BP_UtilityScorer",
  "graph_name":         "ScoreTarget",
  "target_class_path":  "/Game/Enemies/BP_EnemyBase.BP_EnemyBase_C",
  "position":           [384, 0]
}

// M28.3.4 — append a local variable to a function's Entry node. Different
// shape from the spawn ops: no K2Node created, just appends to the
// existing UK2Node_FunctionEntry's LocalVariables array. var_type_spec
// uses the same compact string form add_bp_variable accepts.
// function_name must be a function / interface-override graph
// (ubergraphs don't carry local vars).
{
  "op":            "add_local_variable",
  "bp_path":       "/Game/AI/BP_UtilityScorer",
  "function_name": "ScoreTarget",
  "var_name":      "BestScore",
  "var_type_spec": "real",
  "default_value": "0.0"
}

// M28.5.1 — append an option to a UEnvQuery with a fresh generator.
// First op of the M28.5 EQS write-side catalog. Idempotent on
// (eqs_path, generator_class_path): a second call with the same generator
// class returns success with skipped="option with this generator already
// exists" and option_index pointing at the matching slot. Determinism is
// via explicit FName on each NewObject — EQS classes have zero
// FGuid::NewGuid() usage so name drift is the only risk.
// Follow with set_property_value on ["Options", "[N]", "Generator", ...]
// to tune the generator's per-UPROPERTY defaults.
{
  "op":                   "add_eqs_option",
  "eqs_path":             "/Game/AI/EQS_FindCover",
  "generator_class_path": "/Script/AIModule.EnvQueryGenerator_ActorsOfClass"
}

// M28.5.2 — append a test to an existing EQS option's Tests[] array.
// Second op of the M28.5 EQS write-side catalog. Idempotent on
// (eqs_path, option_index, test_class_path): a second call with the same
// test class on the same option returns success with skipped="test with
// this class already exists on option" and test_index pointing at the
// matching slot. TestOrder is assigned to the post-append index so the
// 0..N-1 runtime invariant holds (EnvQueryManager.cpp:874 only repairs
// zero). Determinism via explicit FName on NewObject.
{
  "op":              "add_eqs_test",
  "eqs_path":        "/Game/AI/EQS_FindCover",
  "option_index":    0,
  "test_class_path": "/Script/AIModule.EnvQueryTest_Distance"
}

// M28.5.2 — remove a test from an existing EQS option's Tests[] array by
// index. Symmetric counterpart of add_eqs_test. Reseats TestOrder on every
// subsequent test so the 0..N-1 invariant is preserved on delete.
// Idempotent on (eqs_path, option_index, test_index): an out-of-range
// test_index returns success with skipped="test already removed" — supports
// soak replay where round 1 removes and round 2 sees the post-state.
// option_index still has a strict bounds check.
{
  "op":           "remove_eqs_test",
  "eqs_path":     "/Game/AI/EQS_FindCover",
  "option_index": 0,
  "test_index":   1
}

// M28.5.3 — set a scalar UPROPERTY on an EQS option's Generator. Python-only
// wrapper around the existing M23.1 SetPropertyValue reflection bridge —
// no new UFUNCTION. property_path is leaf-relative: a single name
// (["OptionName"]) hits a plain UPROPERTY on the generator; nested paths
// descend into FStructProperty fields like FAIDataProviderFloatValue's
// DefaultValue leaf. Array elements use "[N]" notation. Idempotent: the
// bridge short-circuits when before == value as a string. value may be a
// plain int/float/bool/str — the op coerces to ExportText form before
// handing to ImportText_Direct. DataBinding swaps are out of scope — use
// the struct's DefaultValue leaf for scalar tuning.
{
  "op":            "set_eqs_generator_property",
  "eqs_path":      "/Game/AI/EQS_FindCover",
  "option_index":  0,
  "property_path": ["SearchRadius", "DefaultValue"],
  "value":         500.0
}

// M28.5.3 — set a scalar UPROPERTY on one of an EQS option's Tests. Sibling
// of set_eqs_generator_property; targets Options[i].Tests[j] instead of
// Options[i].Generator. Same reflection-bridge reuse + same idempotent
// short-circuit. Typical property_paths: ["TestComment"] for an FString
// annotation, ["TestPurpose"] for the EEnvTestPurpose enum, or
// ["ScoringFactor", "DefaultValue"] for a float scoring weight.
{
  "op":            "set_eqs_test_property",
  "eqs_path":      "/Game/AI/EQS_FindCover",
  "option_index":  0,
  "test_index":    1,
  "property_path": ["TestPurpose"],
  "value":         "Score"
}

// M28.4.1 — create a UCurveFloat asset at curve_path. First op of the M28.4
// non-BP asset-factory catalog. The created curve starts empty; populate
// keys via set_curve_float_keys in a follow-up op. Idempotent on curve_path
// (skipped if a UCurveFloat already occupies the path; structured error on
// different-class collision). No GUID seeding — UCurveFloat has zero FGuid
// fields; explicit FName on NewObject (derived from the /Game/ path tail)
// is the only determinism lever.
{
  "op":         "create_curve_float",
  "curve_path": "/Game/AI/Curve_IntensityRamp"
}

// M28.4.1 — wholesale-replace the key array on a UCurveFloat's FloatCurve.
// keys is a list of {time, value [, interp_mode]} dicts sorted by time
// ascending (unsorted input is rejected up-front; FRichCurve::Evaluate
// assumes sorted storage). interp_mode is optional (default "linear");
// valid values: "linear" / "constant" / "cubic". Idempotent on
// element-wise (time, value, interp_mode) equality. Per-key ops are
// deferred — this wholesale shape matches the "re-author as a unit"
// authoring style the design.md intensity-curve driver uses.
{
  "op":         "set_curve_float_keys",
  "curve_path": "/Game/AI/Curve_IntensityRamp",
  "keys": [
    { "time": 0.0, "value": 0.2 },
    { "time": 1.0, "value": 0.6, "interp_mode": "cubic" },
    { "time": 2.0, "value": 1.0 },
    { "time": 4.0, "value": 0.4 }
  ]
}

// M28.4.2 — create a UDataAsset-subclass instance at asset_path using
// parent_class_path as the concrete type. Third op of the M28.4 catalog.
// parent_class_path covers native DA classes (/Script/<Module>.<ClassName>)
// and BP-derived DA classes (/Game/<path>/<Name>.<Name>_C — the generated
// class, not the BP asset path). Must be a non-abstract subclass of
// UDataAsset; UPrimaryDataAsset and every BP-derived DA class satisfy that.
// Flags match UDataAssetFactory::FactoryCreateNew (RF_Public | RF_Standalone
// | RF_Transactional). Idempotent on (asset_path, parent_class_path); class
// mismatch at the same path is a structured error. UDataAsset has zero
// FGuid fields; explicit FName on NewObject is the only determinism lever.
{
  "op":                "create_data_asset_instance",
  "asset_path":        "/Game/AI/Archetypes/DA_Rusher",
  "parent_class_path": "/Game/AI/Archetypes/DA_ArchetypeBase.DA_ArchetypeBase_C"
}

// M28.4.2 — mutate a UPROPERTY on a UDataAsset instance. Fourth op of the
// M28.4 catalog; Python-only wrapper over the existing M23.1 SetPropertyValue
// reflection bridge (zero new UFUNCTION). property_path is a list of nav
// steps (["AggroRadius"] or ["Tuning", "MeleeRange"] or etc.; array indices
// use "[N]"). value accepts strings, ints, floats, bools — coerced to the
// bridge's ExportText form. Works for natively-declared UPROPERTYs on C++
// parent DAs AND for BP-added member variables on BP-derived DA classes
// (FindFProperty resolves BP-added vars by their friendly FName). Idempotent
// via before-equals-after short-circuit. For Instanced / EditInlineNew
// refs, use set_instanced_subobject_property (M26.1) instead.
{
  "op":            "set_data_asset_property",
  "asset_path":    "/Game/AI/Archetypes/DA_Rusher",
  "property_path": ["AggroRadius"],
  "value":         1200.0
}

// M28.4.3 — create a new UUserDefinedStruct at uds_path. Fifth op of the
// M28.4 catalog; first of the M28.4.3 UDS quartet. The engine's
// CreateUserDefinedStruct auto-adds a default bool member per its
// bAllowToMakeEmpty=false invariant; the bridge UFUNCTION renames that
// auto-member to BpxAutoBool with a deterministic VarGuid seeded via
// SeedGuidFromJoined(uds_path + ':uds_var:BpxAutoBool') so replay is
// byte-stable. Struct->Guid is also seeded (uds_path + ':uds'). Plan
// authors drop BpxAutoBool via remove_uds_member once at least one
// real member is present (engine's bAllowToMakeEmpty=false refuses to
// delete the last member). Idempotent on uds_path.
{
  "op":       "create_user_defined_struct",
  "uds_path": "/Game/AI/Structs/S_TargetInfo"
}

// M28.4.3 — append a member variable to an existing UUserDefinedStruct.
// Sixth op of the M28.4 catalog. Wraps FStructureEditorUtils::AddVariable
// and post-seeds the new VarDesc's VarGuid via
// SeedGuidFromJoined(uds_path + ':uds_var:' + member_name), then routes
// through RenameVariable so VarName regenerates from the seeded VarGuid
// + friendly name. Reuses blueprint_structural._resolve_pin_type (same
// catalog as add_bp_variable / add_local_variable). default_value is
// the literal FStructVariableDescription::DefaultValue string — "true"
// for bool, "42" for int, "(X=1.0,Y=2.0,Z=0.0)" for vectors, "" for
// type-default. Idempotent on member_name.
{
  "op":             "add_uds_member",
  "uds_path":       "/Game/AI/Structs/S_TargetInfo",
  "member_name":    "LastSeenTime",
  "var_type_spec":  "real",
  "default_value":  "0.0"
}

// M28.4.3 — remove a member variable from a UUserDefinedStruct by
// friendly name. Seventh op of the M28.4 catalog. Idempotent:
// missing member returns skipped="member already absent". Refuses
// to empty the struct (engine invariant bAllowToMakeEmpty=false) —
// if the target is the last member, returns a structured error.
// Plan authors add the replacement BEFORE removing the placeholder:
// the canonical "thicken S_TargetInfo" chain is create → add × N →
// remove(BpxAutoBool), not the reverse.
{
  "op":          "remove_uds_member",
  "uds_path":    "/Game/AI/Structs/S_TargetInfo",
  "member_name": "BpxAutoBool"
}

// M28.4.3 — set a member variable's default value on a UUserDefinedStruct.
// Eighth op of the M28.4 catalog; closes the UDS quartet. Routes through
// FStructureEditorUtils::ChangeVariableDefaultValue (NOT the generic
// SetPropertyValue bridge) so VarDesc.DefaultValue (authoritative
// string) and DefaultInstance memory stay in sync via the engine's
// RecreateDefaultInstanceInEditorData listener. M28.4.0 research
// Open Question #1 selected this path. value accepts strings (verbatim
// for composite literals) and scalars (coerced to ExportText form).
// Idempotent via before-equals-after string compare; missing member
// is a structured error (not a silent skip).
{
  "op":          "set_uds_member_default",
  "uds_path":    "/Game/AI/Structs/S_TargetInfo",
  "member_name": "ExposureScore",
  "value":       0.5
}

// M28.6.1 — register a new gameplay tag in the project's ini config.
// Engine handles the file write (Config/DefaultGameplayTags.ini), alpha-
// sorts the on-disk list, and refreshes the in-memory tag tree. No
// /Game/ asset is mutated — this is a Config/.ini text-file edit. The
// op is idempotent on (tag_name, source_ini); a re-apply against an
// already-registered tag returns success=True with skipped="tag already
// registered" without re-writing the file.
//
// Source ini caveat: when the developer has set DeveloperConfigName in
// project settings, source_ini="DefaultGameplayTags.ini" gets diverted
// to a per-machine ini. To force a deterministic per-source ini across
// machines, pass an explicit non-default name (e.g. "AI.ini" → routes
// to <Project>/Config/Tags/AI.ini, creating both file and source on
// first add).
//
// Perforce: AddNewGameplayTagToINI auto-checks-out the .ini via
// ISourceControlModule. The apply_plan confirm=True gate is the user's
// checkpoint for that side effect.
{
  "op":          "add_gameplay_tag",
  "tag_name":    "AI.Order.Flank",
  "dev_comment": "Squad-director command: hold position and call shots",
  "source_ini":  "DefaultGameplayTags.ini"
}
```

### Verifying EnterConditions — use the op, not a raw path

Raw `verification[]` `path` entries that try to read
`EnterConditions[N].InstanceObject` via a colon-qualified step (e.g.
`"StateTreeEditorData:SubTrees"`) resolve to `None` regardless of
whether the target is a root or nested state. The colon notation was
only ever a doc convention — `BpxReflectionOps::ResolvePath`
(`Source/BlueprintExporter/Private/Reflection/ReflectionOps.cpp`)
walks one UPROPERTY per step and has no parse rule for `:`. Do not
use these paths in new plans:

```jsonc
// BROKEN — returns null for both root and nested
["<st>", "StateTreeEditorData:SubTrees", "[2]", "EnterConditions",
 "[0]", "InstanceObject"]
```

**Use `verify_state_enter_conditions` inside `operations[]` instead.**
It takes the same `state_path` nav list as `add_` / `remove_`, walks
from the asset via the bridge's `find_subobject` + op-side helpers,
and records the live EC list in the execution report. Resolves
reliably for both root states (`["SubTrees", "[2]"]`) and nested
states (`["SubTrees", "[2]", "Children", "[3]"]`). Its
`after.entries[]` carries `{idx, class_path, instance_path}` per EC,
which a human reviewer compares against the plan's `intended_outcome`.

Structural recipe: add a `verify_state_enter_conditions` op
immediately after the mutating `add_` / `remove_` op. Keep
`verification[]` focused on what it's good at — `asset_exists` /
`asset_absent` topology checks, and path reads on asset-level scalar
UPROPERTYs that the walker does model (e.g. BP variable defaults on
the CDO).

## Value conventions

`value` fields carry the target value for a property set. JSON-native
types map to UE types per the table in `CATALOG.md`. Summary:

- scalar int / float / bool / string — plain JSON
- `Vector2D` / `Vector` / `Rotator` / `LinearColor` — JSON object with
  the component keys UE expects, e.g. `{"x": 0.7, "y": 3.0}` or
  `{"pitch": 0, "yaw": 90, "roll": 0}`. Executor converts via
  `unreal.Vector2D(...)` etc. before calling the op.
- Enum — JSON string matching the enum value name, e.g.
  `"ECC_PAWN"`; the executor resolves via
  `getattr(unreal.ECollisionChannel, value)`.
- Object / asset reference — `"/Game/...Path"` string; executor calls
  `unreal.load_asset`.
- Array — JSON array of the above (UE coerces on set).

When a value can't be represented in JSON-native form (e.g. a specific
`FInstancedStruct` configuration), use an ImportText string and document
the intent in a `"_comment"` sibling field on the op. Validator strips
`_comment` before dispatch.

## `expected_side_effects`

Free-form prose lines the executor logs alongside each run. The diff
oracle (M24.3) does **not** match these strings against actual diffs —
they exist for human review of the plan, and for Claude to confirm that
its intended outcome matches what the ops literally do. Typical forms:

- `"<path>.uasset md5 will change"`
- `"<path> will be created"`
- `"<path> will be deleted"`
- `"<path> will recompile without errors"`

List every asset that will change. An edit is "surprising" (and the
diff oracle will flag it) if a file's md5 changed and the plan did not
list it here.

## `verification`

Post-execution checks the diff oracle runs against the live editor state.
Each entry is one of:

```jsonc
// Scalar read-back via the bridge
{ "path": ["/Game/.../Asset", "FieldOrNestedPath"], "expected": <value> }

// Asset presence
{ "asset_exists": "/Game/.../Path" }
{ "asset_absent":  "/Game/.../Path" }
```

The `path` form's first element is the asset path; subsequent elements
are the same `ResolvePath`-compatible navigation steps the bridge
accepts (property names + `"[N]"` indices). Expected value must match
the post-execution bridge read for the check to pass. For plans that
only add / remove / rename assets, prefer `asset_exists` / `asset_absent`
over path reads.

Verification entries are additive — they can overlap with what the diff
oracle catches automatically via mechanical diff. Use them to pin
specific values (e.g. "Damage = 12") that matter beyond "some bytes
changed."

## Idempotency keys

Every shipped op is idempotent: running the same plan twice is safe
and on the second run every op returns `skipped` or a no-op. This is
load-bearing for the plan-executor retry loop (M24.2): if a plan fails
mid-way and the caller retries, already-applied ops are automatically
no-ops.

For ops that already ship idempotence (all seven): no plan-level action
needed. For future ops that do not ship idempotence natively, add an
`"idempotency_key": "<stable string>"` field to the op and the executor
will record it in a ledger so replays skip completed entries by key.
No op needs this today.

## Op ordering

Operations run in JSON array order. The executor does not reorder. Write
plans with the dependency structure in mind:

- `create_child_bp` before any op targeting the newly-created BP.
- `rename_asset` before any op targeting the new path.
- For StateTree condition adds, put them after any `set_bp_variable_default`
  on the condition BP — otherwise the instance starts with stale defaults.
- For array-index-sensitive ops (`set_instanced_subobject_property` with
  `path=[..., 0]` and friends) that operate on arrays modified earlier
  in the plan, use the index as it stands **after** the prior op.

## Risk levels

`risk_level` is Claude's self-assessment, surfaced in logs and used by
the executor's abort-on-first-failure threshold:

- `low` — single scalar value tweaks on a single asset
  (`set_bp_variable_default` on a float, `set_component_property` on a
  bool). No topology change, no compile failure modes beyond
  hand-typed typos.
- `medium` — SCS / instanced / StateTree edits that change asset
  topology. Compile failures possible if wrong classes wired; M17
  `BS_Error` guard holds any bad state off-disk.
- `high` — asset creation, renames, deletions, anything that changes
  the set of files on disk. Roll back by hand if mechanical diff flags
  an unexpected change — no automatic rollback (see WIP §9 "Out of
  scope").

## Worked example — "LOS-gate Peek state firing"

```jsonc
{
  "intended_outcome": "Gate Peek state entry on ST_Cond_CanSeeTarget so enemies only pop out when they have line of sight on the player.",
  "risk_level": "medium",
  "operations": [
    {
      "op": "add_statetree_enter_condition",
      "st_path": "/Game/CombatPrototype/DrewPrototype/ST_EnemyBase",
      "state_path": ["SubTrees", "[2]", "Children", "[3]"],
      "condition_bp_path": "/Game/CombatPrototype/DrewPrototype/ST_Cond_CanSeeTarget"
    },
    {
      "op": "verify_state_enter_conditions",
      "st_path": "/Game/CombatPrototype/DrewPrototype/ST_EnemyBase",
      "state_path": ["SubTrees", "[2]", "Children", "[3]"]
    }
  ],
  "expected_side_effects": [
    "ST_EnemyBase.uasset md5 will change",
    "ST_EnemyBase will recompile without errors"
  ],
  "verification": [
    { "asset_exists": "/Game/CombatPrototype/DrewPrototype/ST_EnemyBase" }
  ]
}
```

The `verify_state_enter_conditions` op's `after.entries[0].class_path`
should end with `ST_Cond_CanSeeTarget_C` after the add op lands —
confirm by reading the run report, not by adding a raw
`{path, expected_class}` verification entry (see "Verifying
EnterConditions" above).

## Common mistakes

- **Hardcoding array indices that shift.** A plan that does
  `array_remove_at` followed by `set_instanced_subobject_property` on
  the same array must account for index shift after the remove.
  Prefer class-match idempotent ops (like
  `add_statetree_enter_condition`) over positional ones when a choice
  exists.
- **Missing `expected_side_effects` entries.** Every asset that will
  change on disk must appear. The diff oracle flags unlisted changes,
  so omitting entries turns a benign change into a validation failure.
- **Using raw UE type names in `expected_type` fields.** The validator
  understands the Python names (`int`, `float`, `Vector2D`, etc.) per
  CATALOG.md's mapping table, not UE's C++ names (`FVector2D`,
  `UObject*`).
- **Mixing `value` types for the same property across plans.** UE's
  `set_editor_property` silently coerces some types; this masks bugs
  where a plan reads a field expecting `float` but the prior plan
  wrote it as an `int` literal. Stick to the Python type the property
  genuinely wants.
- **Assuming `state_path` is discoverable by name.** UE 5.7 does not
  expose `UStateTreeState` lookup by name from Python. Either probe
  the tree once (`probe_peek_path.py`-style) and hardcode the path,
  or extend the StateTree ops with a name-resolver when repeated
  edits on the same state become routine.

## Non-goals

- **Rollback.** Apply is atomic per op, not per plan. If op 5 of 10
  fails, ops 1–4 already committed. Document as a caller constraint
  and retry.
- **Multi-user edit coordination.** Plans are local; the user decides
  whether to `p4 submit`.
- **Dynamic ops.** The op vocabulary is a closed set. A plan cannot
  reference an op that isn't in `python_ops.__init__` — validator
  rejects unknowns. Adding a new op is a code change, not a plan
  change.
