# Agent loop integration

How Claude turns a user's edit request into a clean landing through the
M24 pipeline. Read this alongside `README.md` (schema reference) —
README says **what a plan is**, this doc says **how to use a plan to
fulfill a request**.

Audience: future Claude sessions picking up a new edit ask. Goal: get
from "user wants X" to "X is on disk, tested, and signed off" without
re-deriving the M24 semantics every time.

## The 8 steps

Each step produces an artefact the next step reads. Don't skip — each
is a gate. If a gate fails, the fix is scoped to that step's scope.

**Timing expectations** (important for pacing your own workflow):

| Transport | `validate_plan` | `apply_plan` | 5-op iteration loop |
|---|---|---|---|
| Editor running (M27 bridge — preferred) | **sub-second** | **sub-second** | **~5 s total** |
| Editor closed (subprocess fallback) | 2–5 min cold start | 2–5 min cold start | 10–25 min |

Always keep the UE editor open while iterating. If you're about to
batch more than one plan, the bridge saves you 10+ minutes per pass.
The `transport` field on every response (`"bridge"` vs `"subprocess"`)
tells you which path ran; warn if you see unexpected `"subprocess"`
during an iterative session.

1. **Export** — target assets are already captured in
   `ProjectInventory_DOW/` sidecars (`.md` + `.meta.json` + `.deep.md`
   where Tier 2 applies). If the user points at a legacy-depot asset
   that isn't in the canonical tree, run `ProjectInventoryCommandlet`
   against a narrow `-Filter=/Game/...` slice first.

2. **Understand** — read the deep dumps. Write nothing. The failure
   mode here is plan-based-on-assumption. Concrete confirmations to
   make before writing a plan:
   - Every asset path you intend to reference exists in the dumps.
   - Every property / state / component name you intend to touch is
     visible in the dump tables (verbatim, not inferred).
   - The target's class inheritance covers the op you picked
     (e.g., `add_statetree_enter_condition` needs the target to be a
     `UStateTree`; `set_bp_variable_default` needs the var to appear
     in the `## Variables` section, not the `## Class Default Object`
     section — those go through different ops).

3. **Plan** — produce JSON matching `plans/README.md`. The schema is
   strict: missing fields, unknown ops, wrong-shape kwargs all fail at
   step 4. Write the plan in a file next to the target assets or in a
   scratch dir — anywhere the CLI can read.

4. **Validate** — preferred path: MCP `validate_plan` tool, which
   routes through the editor bridge (sub-second) when the editor is
   running. Headless fallback is equivalent to running
   `UnrealEditor-Cmd.exe <uproject> -run=pythonscript
    -script=".../scripts/run_plan_validator.py" -plan="<plan.json>"`
   — same validator, same report shape, just cold-started. Zero
   mutations either way. Response has `report` + `transport` fields.
   Reading the report is cheap; read it.

5. **Apply** — if validation passed, run MCP `apply_plan(confirm=True)`.
   Bridge path runs the same `run_plan.py` library code in-process
   (validate → execute → mechanical-diff → verification). Fallback
   shells to `run_plan.py` under `UnrealEditor-Cmd.exe` — identical
   semantics, just slower. Every op is atomic-per-op; if op N of M
   fails, ops 1..N-1 are already committed. Response `report.passed`
   is True iff every gate passed; `transport` tells you which path
   ran. When the bridge ran AND `report.passed` is True, a
   `reExport` block in the response lists which per-asset sidecars
   got regenerated (see step 7).

6. **Verify mechanically** — automatic, inside `run_plan`. The diff
   oracle reports:
   - `asset_changes[]` with `observed` vs `expected` kind per asset,
   - `unexpected_changes[]` — fatal; something outside the plan's
     predictions changed (non-determinism, BP compile churn, cross-
     asset cascades),
   - `expected_but_missing[]` — non-fatal; idempotent skip kept the
     asset stable although the plan predicted a mutation,
   - `verification_results[]` — each `{path, expected}` /
     `{asset_exists}` / `{asset_absent}` entry evaluated.

7. **Verify semantically** — Claude's job. Re-read post-execution
   dumps to confirm the *intended behaviour change* is what the user
   asked for. Mechanical pass ≠ semantic pass — a typo in the
   condition class name can mechanically succeed (valid asset, no
   unexpected changes) but semantically fail (the wrong class got
   wired).

   **Bridge path (M27.3):** when `apply_plan` ran through the editor
   bridge and passed, the response's `reExport.wroteFiles[]` lists
   the freshly-regenerated `.md` / `.meta.json` / `.deep.md` sidecars
   for every touched UBlueprint / StateTree asset. You can go
   straight to `get_asset_deep_dump(<touched-path>)` — no manual
   refresh step. Assets of other types (BT / DT / Chooser / EQS /
   SmartObject / DataAsset) appear in `reExport.perAsset[]` with
   `status: "unsupported"` and need a follow-up
   `refresh_inventory(path_filter=<prefix>)` before their sidecars
   reflect the post-plan state.

   **Subprocess fallback:** no auto-re-export. Run `refresh_inventory`
   or `deep_dump_asset` on the touched paths before reading.

8. **Escalate only experiential** — subjective questions ("does the
   enemy feel less cheap now?") need a PIE test the user runs in
   person. Do not promise experiential outcomes from the static
   change alone. Everything mechanical / semantic should be resolved
   before escalating.

## Worked example — "enemies should only pop out when they can see the player"

### Step 1: Export

ST_EnemyBase is in the canonical tree at
`ProjectInventory_DOW/...` (modulo legacy-depot caveats). If not, a
focused sweep:

```
UnrealEditor-Cmd.exe UE_DOW.uproject -run=ProjectInventory \
    -Filter=/Game/CombatPrototype/DrewPrototype/ \
    -OutDir=<scratch>/_los_gate_inventory/ \
    -DeepDump -nullrhi -unattended
```

### Step 2: Understand

`ST_EnemyBase.deep.md` reveals:

- A top-level `SubTrees[2]` named `CombatLoop` (probe the `Name`
  field under each subtree index via
  `unreal.BpxReflectionOps.get_property_value` if the dump does not
  surface names explicitly).
- `SubTrees[2].Children[3]` is the Peek state — the one that pops out.
- `ST_Cond_CanSeeTarget` is a Blueprint at
  `/Game/CombatPrototype/DrewPrototype/ST_Cond_CanSeeTarget` whose
  parent class is `UStateTreeConditionBlueprintBase` (readable from
  its own `.meta.json`).

The right op is `add_statetree_enter_condition` — wrap
EnterConditions on the Peek state with the CanSeeTarget condition.

### Step 3: Plan

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
    }
  ],
  "expected_side_effects": [
    "ST_EnemyBase.uasset md5 will change if the condition is not already present",
    "ST_EnemyBase will recompile without errors"
  ],
  "verification": [
    { "asset_exists": "/Game/CombatPrototype/DrewPrototype/ST_EnemyBase" }
  ]
}
```

Written to `D:/Work/_combat_ai_tuning/los_gate_plan.json`.

### Step 4: Validate

```
UnrealEditor-Cmd.exe UE_DOW_Legacy.uproject -run=pythonscript \
    -script=".../scripts/run_plan_validator.py" \
    -plan="D:/Work/_combat_ai_tuning/los_gate_plan.json" \
    -nullrhi -unattended -stdout
```

Expected log:

```
Plan validation: PASSED
Per-op:
  [0] add_statetree_enter_condition: ok
[PLAN_VALIDATOR] full report written to .../los_gate_plan.json.validation.json
```

If FAILED: see "Error classification" below.

### Step 5–6: Apply + mechanical verify

```
UnrealEditor-Cmd.exe UE_DOW_Legacy.uproject -run=pythonscript \
    -script=".../scripts/run_plan.py" \
    -plan="D:/Work/_combat_ai_tuning/los_gate_plan.json" \
    -nullrhi -unattended -stdout
```

Expected log:

```
Plan execution: PASSED (executed=1, aborted_at=None, elapsed=…)
Per-op:
  [0] add_statetree_enter_condition: ok

Mechanical diff: PASSED
```

`<plan>.run.json` will carry the full reports. The md5 shift from
before→after is the quick smoke-test: did the asset actually change?

### Step 7: Semantic verify

Re-run DeepDump on ST_EnemyBase. Confirm:

- `EnterConditions[0].Node` is `StateTreeBlueprintConditionWrapper`.
- `EnterConditions[0].Node.ConditionClass` points at
  `ST_Cond_CanSeeTarget_C`.
- `EnterConditions[0].InstanceObject` is non-null and of that class.

If any of those fail, the plan landed mechanically but wired wrong —
something to fix in the script / op, not the plan.

### Step 8: Escalate

Ask the user: "Please run a PIE test and confirm enemies only pop
when they can see you. The static change is in place." Do not claim
the feel of the gameplay was validated.

## Worked example — "BP_EnemyBase doesn't return targeting info"

The Flat Arena regression that drove M26.1: `BP_EnemyBase` in Legacy's
CombatPrototype declares `BPI_Targetable` but has no `GetTargetingInfo`
override. UE's interface-message call returns defaults
(`bIsAlive=false`, `Faction=0`) for every call, so `AssessThreat(pawn)`
never classifies anyone as hostile, `KnownTargets` stays empty,
`CombatLoop`'s `ST_Cond_HasTargets` never fires, both teams run at each
other and stand around. Minimal fix is a 3-pin passthrough.

**Understand (Step 2).** From the committed inventory:

- `BP_EnemyBase.deep.md`: `## Implemented Interfaces` lists `BPI_Targetable`
  but `## Functions` doesn't include `GetTargetingInfo` (override missing).
- `BPI_Targetable.deep.md`: `GetTargetingInfo` signature = `(out bool
  bIsAlive, out bool bIsTargetable, out int32 Faction)`.
- `BP_EnemyBase`'s `## Variables` has `bIsAlive: bool` (default false)
  and `Faction: int32` (default 0) already — the op just needs to
  passthrough.

**Plan (Step 3).**

```jsonc
{
  "intended_outcome": "Override BPI_Targetable.GetTargetingInfo on BP_EnemyBase as a passthrough so interface calls return the instance's actual bIsAlive / bIsTargetable / Faction instead of UE defaults.",
  "risk_level": "medium",
  "operations": [
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
  ],
  "expected_side_effects": [
    "BP_EnemyBase.uasset md5 will change",
    "BP_EnemyBase will recompile without errors"
  ],
  "verification": [
    { "asset_exists": "/Game/CombatPrototype/DrewPrototype/BP_EnemyBase" }
  ]
}
```

**Validate / Apply (Steps 4-6).** Same as the LOS-gate example above.

**Semantic verify (Step 7).** Re-run DeepDump on `BP_EnemyBase` and
confirm:

- `## Functions` now includes `GetTargetingInfo` under the `BPI_Targetable`
  interface heading.
- Its body shows three wires: `self.bIsAlive -> Return.bIsAlive`,
  literal `true` on `Return.bIsTargetable`, `self.Faction -> Return.Faction`.
- `Return.execute` is fed by `Entry.then`.

**Escalate (Step 8).** "Reopen UE on Legacy, right-click `BP_EnemyBase`
→ Reload, verify the `GetTargetingInfo` override in the BP editor's
Interfaces panel, start `Combat_FlatArena` 5v5, observe engagement
between the two teams." Do not claim Flat Arena plays correctly from
the static change alone.

## Worked example — "squad director with an OnOrderReceived callback"

Exercises the M28.2 structural-edit chain end-to-end: add a member
variable, attach an interface, add a function graph, then wire the body
with M26.1 ops. Uses design.md's squad-coordination surface as the
motivating case — the concrete target is a `BP_SquadDirector` actor
that listens for `AI.Order.*` broadcasts and flips an internal
`bActiveOrder` flag when an order arrives.

This is a single plan, not four. The four structural ops are idempotent
on their identifiers (var name / interface path / function name /
component name), so running the plan twice is a no-op on the second
pass. The body-authoring ops at the end chain off the function graph's
Entry / Return GUIDs that `add_bp_function` returns.

### Step 2: Understand

From the project inventory (assumes `BPI_OrderListener` already exists
with a `ReceiveOrder` event signature, `BP_SquadDirector` is a plain
Actor BP parented to `AActor`):

- `BP_SquadDirector.deep.md`: `## Variables` empty — needs
  `bActiveOrder`. `## Implemented Interfaces` empty — needs
  `BPI_OrderListener`. `## Functions` empty — the plan will add
  `OnOrderReceived` as a callback helper.
- `BPI_OrderListener.deep.md`: declares `ReceiveOrder(FGameplayTag
  OrderTag)` as an event-shape interface function (no out-params), so
  `add_bp_interface` attaches cleanly but generates zero override
  graphs — the seeding loop is inert and `OnOrderReceived` is a
  separate BP-local helper, not an override.

### Step 3: Plan

```jsonc
{
  "intended_outcome": "Seed BP_SquadDirector with the minimum surface to listen for AI.Order.* broadcasts: an InstanceEditable bActiveOrder flag, BPI_OrderListener attached, and an OnOrderReceived helper function whose body sets bActiveOrder=true.",
  "risk_level": "medium",
  "operations": [
    {
      "op":                "add_bp_variable",
      "bp_path":           "/Game/Squad/BP_SquadDirector",
      "var_name":          "bActiveOrder",
      "var_type_spec":     "bool",
      "default_value":     "false",
      "instance_editable": true
    },
    {
      "op":                    "add_bp_interface",
      "bp_path":               "/Game/Squad/BP_SquadDirector",
      "interface_class_path":  "/Game/Squad/BPI_OrderListener.BPI_OrderListener_C"
    },
    {
      "op":            "add_bp_function",
      "bp_path":       "/Game/Squad/BP_SquadDirector",
      "function_name": "OnOrderReceived",
      "is_pure":       false
    }
  ],
  "expected_side_effects": [
    "BP_SquadDirector.uasset md5 will change",
    "BP_SquadDirector will recompile without errors"
  ],
  "verification": [
    { "asset_exists": "/Game/Squad/BP_SquadDirector" }
  ]
}
```

The plan stops at **structure** — the three ops above leave
`OnOrderReceived` with just Entry → Return wired by UE's default graph
creation. The body (one Set node writing `bActiveOrder=true`) is a
separate, follow-up plan that reads
`add_bp_function`'s returned `entry_guid` / `return_guid` out of the
first plan's run report and chains
`set_bp_variable_default` + `connect_graph_pins` by GUID. Keeping
structural and body-level work in separate plans matches the
per-phase verification gates: M28.2 structural changes trip different
diff patterns than M26.1 / M28.3-narrow graph wires.

### Step 4–6: Validate / Apply / Mechanical verify

Same commands as the LOS-gate / interface-passthrough examples above.
Expected run-report highlights:

- `operations[0].after.added = true` (first run) or
  `operations[0].skipped = "variable already exists"` (replay).
- `operations[1].after.added = true` or
  `operations[1].skipped = "interface already implemented"` (replay).
- `operations[2].after.entry_guid` + `.return_guid` populated with
  hex strings (non-empty on both fresh-add and replay) — these feed the
  follow-up body-authoring plan.
- `mechanical_diff.asset_changes[0]` = `{"asset":
  "/Game/Squad/BP_SquadDirector", "observed": "mutated",
  "expected": "mutated"}` on a fresh run, or `"stable"` on a replay.

### Step 7: Semantic verify

Re-run DeepDump on `BP_SquadDirector` (or read the bridge-auto-refreshed
sidecar per the M27.3 loop). Confirm:

- `## Variables` lists `bActiveOrder: bool` with `DefaultValue=false` and
  `bInstanceEditable=true`.
- `## Implemented Interfaces` lists `BPI_OrderListener`.
- `## Functions` lists `OnOrderReceived` with a **stub (no authored
  body)** suffix — M26.1.1 surfaces this so the follow-up plan knows
  the body still needs to be wired.

### Step 8: Escalate (to the follow-up plan, not the user)

The first plan lands structural scaffolding; no user action. The
follow-up body-authoring plan uses the Entry / Return GUIDs captured in
step 5's run report:

```jsonc
{
  "intended_outcome": "Wire OnOrderReceived body so it sets bActiveOrder=true on the self context.",
  "risk_level": "low",
  "operations": [
    // Use M26.1 / M28.3-narrow helpers — add a VariableSet node,
    // connect Entry.then → Set.execute → Return.execute, and pin
    // the input literal true. Full op sequence is op-catalog-specific;
    // see CATALOG.md for `connect_graph_pins`, `add_self_member_set_node`
    // (planned), etc.
  ],
  "expected_side_effects": [
    "BP_SquadDirector.uasset md5 will change"
  ]
}
```

Only escalate to the user once both plans have landed + compiled +
been semantically verified.

## Worked example — "wire OnOrderReceived body via M28.3 node spawns"

The promised follow-up to the squad-director scaffolding example above.
Exercises the M28.3 graph-authoring catalog end-to-end: spawn a
`VariableSet` targeting `self.bActiveOrder`, pin its `Value` input to the
literal `true`, then wire `Entry.then → Set.execute → Return.execute`.
Single plan, one asset touched, ~4 ops.

This demonstrates the node-level authoring pattern for every design.md
body-wiring case — utility-scorer score-calc, callout broadcasts, hit-
reaction state flips, etc. The pattern generalises: each body is a
short chain of `add_*_node` spawns + `set_graph_pin_default` literals +
`connect_graph_pins` wires.

### Step 2: Understand

From the prior plan's run report (or a re-exported sidecar):

- `BP_SquadDirector.deep.md`: `## Functions` lists `OnOrderReceived` with
  a **stub (no authored body)** suffix. Entry + Return NodeGuids are on
  `operations[2].after` in the prior run's JSON report.
- `bActiveOrder` is declared with `bInstanceEditable=true`. A `VariableSet`
  spawn needs the variable to already exist on the BP — which the prior
  plan ensured.

Grab the Entry / Return GUIDs out of the prior run report (pseudocode):

```python
prior = json.load(open("/.../ue-plan-run.json"))
entry_guid = prior["operations"][2]["after"]["entry_guid"]   # UK2Node_FunctionEntry.NodeGuid
return_guid = prior["operations"][2]["after"]["return_guid"] # UK2Node_FunctionResult.NodeGuid
```

### Step 3: Plan

```jsonc
{
  "intended_outcome": "Wire OnOrderReceived body: spawn a VariableSet targeting self.bActiveOrder, default its Value input to true, then wire Entry.then → Set.execute → Return.execute. After this plan, calling BPI_OrderListener.ReceiveOrder on a BP_SquadDirector instance will flip bActiveOrder on the instance.",
  "risk_level": "low",
  "operations": [
    {
      "op":                 "add_variable_set_node",
      "bp_path":            "/Game/Squad/BP_SquadDirector",
      "graph_name":         "OnOrderReceived",
      "variable_name":      "bActiveOrder",
      "target_class_path":  "",
      "position":           [256, 0]
    },
    {
      "op":           "set_graph_pin_default",
      "bp_path":      "/Game/Squad/BP_SquadDirector",
      "graph_name":   "OnOrderReceived",
      "node_guid":    "<VariableSet node_guid from prior op result>",
      "pin_name":     "bActiveOrder",
      "literal_text": "true"
    },
    {
      "op":             "connect_graph_pins",
      "bp_path":        "/Game/Squad/BP_SquadDirector",
      "graph_name":     "OnOrderReceived",
      "from_node_guid": "<entry_guid from prior plan's run report>",
      "from_pin":       "then",
      "to_node_guid":   "<VariableSet node_guid from op 1 result>",
      "to_pin":         "execute"
    },
    {
      "op":             "connect_graph_pins",
      "bp_path":        "/Game/Squad/BP_SquadDirector",
      "graph_name":     "OnOrderReceived",
      "from_node_guid": "<VariableSet node_guid>",
      "from_pin":       "then",
      "to_node_guid":   "<return_guid from prior plan's run report>",
      "to_pin":         "execute"
    }
  ],
  "expected_side_effects": [
    "BP_SquadDirector.uasset md5 will change",
    "BP_SquadDirector will recompile cleanly (no unconnected exec pins)"
  ],
  "verification": [
    { "asset_exists": "/Game/Squad/BP_SquadDirector" }
  ]
}
```

**GUID cross-referencing.** The `<VariableSet node_guid>` placeholder is
substituted from `operations[0].after.node_guid` in the same plan's
run report (`add_variable_set_node` is deterministic — the GUID is
`md5(<bp>:graph:OnOrderReceived:varset:bActiveOrder:self:256,0)` so the
agent can compute it client-side, or read it from op-1's result before
authoring ops 2-4 as a single dispatch). The determinism seeding means
this plan is byte-identical round-to-round (M28.pre.3 soak invariant).

### Step 4–6: Validate / Apply / Mechanical verify

Same pattern as the prior examples. Expected run-report highlights:

- `operations[0].after.spawned = true` (first run) or
  `operations[0].skipped = "VariableSet node already exists at this position"`
  (replay — position is part of the seed key).
- `operations[1].before = ""` then `.after = "true"` on fresh run, or
  `operations[1].skipped = "value unchanged"` on replay.
- `operations[2].skipped` / `operations[3].skipped` = `"pins already linked"`
  on replay.
- `mechanical_diff.asset_changes[0]` = `{observed: "mutated", expected:
  "mutated"}` on fresh run, `stable` on replay.

### Step 7: Semantic verify

Re-export `BP_SquadDirector` (bridge-auto via M27.3 or `refresh_inventory`)
and confirm via `.deep.md`:

- `## Functions` — `OnOrderReceived`'s **stub (no authored body)** suffix
  is gone. M26.1.1 only emits that tag when the function body has
  <=1 node (just Entry); after this plan it has 3 nodes
  (Entry + VariableSet + Return).
- The body section lists three wires in graph order:
  `Entry.then → Set.execute`, `Set.then → Return.execute`,
  `(literal) true → Set.bActiveOrder`.
- No `[BROKEN]` or `(unresolved)` markers on any pin.

### Step 8: Escalate (to the user)

"Open BP_SquadDirector in the editor, inspect `OnOrderReceived`, place a
`BP_SquadDirector` in a level, raise an `AI.Order.*` gameplay event via
test script; verify `bActiveOrder` flips to `true` on the placed
instance when the event fires." Do not claim end-to-end runtime behavior
from the static change — the plan proves the body compiles, not that
the gameplay event bus is hooked up correctly upstream.

### Chaining M28.3 ops beyond this pattern

Every design.md body-wiring case follows the same shape:
1. Spawn input-side nodes (`add_variable_get_node` for reads,
   `add_call_function_node` for helper calls, `add_dynamic_cast_node`
   for type-narrowing).
2. Spawn output-side / control-flow nodes (`add_variable_set_node`,
   `add_branch_node`, `add_execution_sequence_node`,
   `add_custom_event_node`).
3. Optionally declare function-local state via `add_local_variable`
   before spawning any read/write nodes against it (different shape:
   extends `UK2Node_FunctionEntry::LocalVariables` rather than spawning
   a K2Node — per M28.3.4).
4. Set literal defaults on typed input pins via `set_graph_pin_default`.
5. Connect exec + data pins via `connect_graph_pins`.

Each spawn op returns its runtime `NodeGuid` as a hex string; callers
feed those hex strings back into `connect_graph_pins` / `set_graph_pin_default`
verbatim (no FGuid parsing needed in plan JSON). All ops are idempotent
on their determinism seed keys so replay is byte-identical (M28.pre.3
soak invariant holds across the full chain).

## Error classification + retry heuristics

### Validator-step errors (step 4)

| Error text | Cause | Fix |
|---|---|---|
| `intended_outcome must be a non-empty string` | Missing or blank field. | Add a one-sentence rationale. |
| `risk_level must be one of …` | Missing or typo (`Medium` ≠ `medium`). | Lowercase, exact match. |
| `operations must be a non-empty list` | Empty or wrong type. | Plans with zero ops are never useful; delete the plan or add at least one op. |
| `unknown op: 'X'` | Typo, or op not yet shipped. | Check the CATALOG + plans/README per-op table. If the op really doesn't exist, file a milestone — do not fake it. |
| `missing required fields: [...]` | Op kwargs incomplete. | Fill per plans/README. |
| `unknown fields: [...]` | Op kwargs include something the library doesn't accept. | Remove the extra fields — UE's kwargs dispatch is strict, and the validator mirrors it. |
| ``asset does not exist: /Game/...`` | Typo, stale tree, or target was deleted. | Grep the inventory for the correct path. If the asset legitimately isn't there, the op target is wrong. |
| ``state_path [...] does not resolve to a UObject`` | Wrong index or wrong asset. | Probe with `get_property_value(ed, path + ["Name"])` first; confirm indices before writing the plan. |

Retry heuristic: validator errors are cheap to fix. Iterate the plan
JSON until it passes validation before spending the 10 s UE-startup
on `run_plan`.

### Executor-step errors (step 5)

The executor aborts on first op failure. Per-op result dicts carry
library-level error messages. Common shapes:

- `TypeError: ... unexpected keyword argument 'foo'` — library API
  drift. Plan field the validator didn't gate. Remove / rename.
- ``get_editor_property('X') raised …`` — typo on a variable /
  component name. The library op lists available names in the error;
  read them and correct.
- ``compile_and_save_package returned False`` — post-edit compile
  failed. Read the UE log for the specific BP compile error; fix the
  plan so it doesn't wire mismatched types / missing classes.
- `load_asset returned None for /Game/...` — asset at a `value`
  field is missing or unloadable. Validate earlier.

Retry heuristic: an executor failure means SOME ops may have already
committed. Before retrying, check the diff report — if an earlier op
landed, the plan may now be partially done. Either:
- Add an `idempotency_key` marker + retry (shipped ops are all
  natively idempotent, so typically this just replays cleanly), or
- Fix the failing op and re-run — the earlier ops will hit idempotent
  skip.

### Diff-step errors (step 6)

- `unexpected_changes[]` non-empty, FATAL — a file changed that the
  plan didn't predict. Usually one of:
  - **BP compile churn** (touching BP A cascaded to BP B that depends
    on A). The plan's op set is correct; add the cascaded asset to
    `expected_side_effects` for the human, or split the plan if the
    cascade is surprising to you too.
  - **Cross-asset reference** (e.g., renaming an asset that something
    else references — the referrer gets resaved with the new path).
    The op is doing more than expected; narrow it.
  - **Non-determinism** (UE recompile + save produces different bytes
    even for logically identical state). Re-run once; if persistent,
    the asset has a non-deterministic serializer, file a bug against
    the exporter / engine.
- `expected_but_missing[]` non-empty, NON-fatal — plan predicted a
  mutation but the asset stayed stable. Reason is almost always
  idempotent skip (plan already applied in a prior run). If the user
  WANTED a re-save, the plan was idempotent for a reason the user
  didn't expect — walk back through step 2.

### Verification-step errors (step 6)

- `value mismatch: got 'X', expected 'Y'` on a `path+expected` entry
  — the op ran but the resulting value isn't what the plan expected.
  This is the most likely indicator that the op was wired to the
  wrong property. Read the op's result dict — the `after` field is
  what actually got set.
- `class mismatch: got X, expected Y` on a `path+expected_class`
  entry — the op set an object reference to the wrong class. Usually
  a typo in `condition_bp_path` / equivalent.
- `asset does not exist` / `asset still exists` — topology check
  failed. Typically a rename / create / delete didn't happen. Pair
  with the asset_changes entry for the same path to debug.

## Anti-patterns

- **Skipping step 2.** Writing a plan from memory of what the dump
  "probably says" is the biggest source of validator errors. Always
  open the actual dump before declaring the path.
- **Guessing state_path indices.** Never hand-type
  `["SubTrees", "[2]", "Children", "[3]"]` without having confirmed
  it by reading `Name` fields at each step. A shifted index silently
  wires the condition to the wrong state.
- **Listing only the primary asset in `expected_side_effects`**
  when the plan cascades. A create-child-bp + set-variable-on-child
  plan changes both assets — list both.
- **Using `expected_side_effects` for mechanical matching.** That
  field is prose for human review. The oracle does not grep strings.
  Use `verification[]` for assertions.
- **Claiming `passed=True` without semantic check.** Mechanical pass
  proves the edit didn't thrash the asset — not that it did the right
  thing. A wrong condition class passes mechanically.

## Relationship to M22

When the M22 BugHunt fixture loop lands, every op will have a
per-op fixture + a DeepDump-diff assertion in
`BugHunt/TestProject/Content/PythonOps/<op>/`. M22 answers:

> "Does `add_statetree_enter_condition` do what it claims, on a
>  minimal fixture, today?"

M24 answers:

> "Does *this user-requested edit*, composed from ops that M22 has
>  already blessed, land safely on a real asset?"

If M22 is green but M24 fails mechanically, the plan is wrong — not
the op. If M22 is red, file against the op before blaming M24.

## Cheat sheet

- Schema reference: `plans/README.md`.
- Op catalog: `../CATALOG.md`.
- End-to-end CLI: `scripts/run_plan.py`.
- Validate only (no mutation): `scripts/run_plan_validator.py`.
- Execute + diff (full pipeline): `scripts/run_plan.py` — this is
  what you want 99% of the time.
