"""M26.1.1 live force_rebind soak against the BugHunt fixture.

Closes the 'Live force_rebind=True soak' follow-up item from WIP_INVENTORY's
M26.1.1 block. The JSON-surface regression test (FInterfaceOverrideSerializationTest)
covers the serializer; the prior M26.1 golden test exercises
implement_interface_function against a no-override baseline. Neither exercises
the force_rebind=True path end-to-end against an actual pre-existing override
stub - which is the exact scenario M26.1.1 set out to unblock.

The BugHunt baseline BP_BpxTestImplementsInterface turns out to carry an
auto-created stub override (UE adds one when an interface is added to a BP),
which pre-M26.1.1 was invisible to the serializer and caused
implement_interface_function to bail with 'skipped: override graph already
exists'. Post-M26.1.1 the stub is visible in .md and the op can recover via
force_rebind=True. That's exactly what this soak exercises.

Flow:

  1. Duplicate BP_BpxTestImplementsInterface -> BP_BpxTest_ForceRebindSoak
     (scratch, deleted at end). Round 1 below asserts the duplicate carries
     the expected stub.
  2. Round 1: implement_interface_function(force_rebind=True) against the
     scratch asset. Asserts success + bindings_applied (the M26.1.1 unblock
     path). wiped_nodes count is recorded but not asserted - a pure stub
     with only Entry has nothing to wipe.
  3. Round 2: implement_interface_function(force_rebind=True) again. Now
     the scratch has 2 VariableGet nodes from round 1; force_rebind must
     wipe them (wiped_nodes > 0) and re-bind. Asserts md5 identical to
     round 1 (the op's md5-seeded NodeGuids make wipe+rebind byte-
     deterministic against a fresh bind over the same inputs).
  4. Cleanup: delete scratch.

Exit 0 iff every assertion passes.

Invoke headless:

    UnrealEditor-Cmd.exe <BugHunt.uproject> \\
        -run=pythonscript \\
        -script="D:/Work/blueprintexporter/blueprint-exporter/scripts/soak_m26_1_1_force_rebind.py" \\
        -nullrhi -unattended -nopause -nosplash -nosound
"""

import hashlib
import sys

import unreal

sys.path.insert(
    0,
    r"D:/Work/blueprintexporter/blueprint-exporter/scripts",
)

from python_ops import implement_interface_function  # noqa: E402


BASELINE_PATH = "/Game/TestBlueprints/BP_BpxTestImplementsInterface"
SCRATCH_PATH  = "/Game/TestBlueprints/BP_BpxTest_ForceRebindSoak"
INTERFACE_PATH = "/Game/TestBlueprints/BPI_BpxTestInterface"
FUNCTION_NAME = "GetTargetingInfo"

BINDINGS = {
    "bIsAlive":      "self.bIsAlive",
    "bIsTargetable": "true",
    "Faction":       "self.Faction",
}

TAG = "[m26.1.1-soak]"


def _log(msg: str) -> None:
    unreal.log(f"{TAG} {msg}")


def _fail(msg: str) -> None:
    unreal.log_error(f"{TAG} FAIL: {msg}")
    raise SystemExit(1)


def _md5_of(package_path: str) -> str:
    filename = unreal.SystemLibrary.get_system_path(
        unreal.EditorAssetLibrary.load_asset(package_path)
    )
    if not filename:
        _fail(f"could not resolve uasset filename for {package_path}")
    with open(filename, "rb") as f:
        return hashlib.md5(f.read()).hexdigest()


def _run(force_rebind: bool) -> dict:
    result = implement_interface_function(
        bp_path=SCRATCH_PATH,
        interface_bp_path=INTERFACE_PATH,
        function_name=FUNCTION_NAME,
        output_bindings=BINDINGS,
        force_rebind=force_rebind,
    )
    if not result.get("success"):
        _fail(
            f"implement_interface_function(force_rebind={force_rebind}) "
            f"returned success=False. errors={result.get('errors')}"
        )
    return result


def main() -> None:
    asset_lib = unreal.EditorAssetLibrary

    if not asset_lib.does_asset_exist(BASELINE_PATH):
        _fail(f"baseline {BASELINE_PATH} missing - run GenerateTestBlueprintsCommandlet first")
    if not asset_lib.does_asset_exist(INTERFACE_PATH):
        _fail(f"interface {INTERFACE_PATH} missing - run GenerateTestBlueprintsCommandlet first")

    if asset_lib.does_asset_exist(SCRATCH_PATH):
        _log(f"removing stale scratch {SCRATCH_PATH}")
        if not asset_lib.delete_asset(SCRATCH_PATH):
            _fail(f"delete_asset({SCRATCH_PATH}) returned False")

    duplicated = asset_lib.duplicate_asset(BASELINE_PATH, SCRATCH_PATH)
    if duplicated is None:
        _fail(f"duplicate_asset({BASELINE_PATH} -> {SCRATCH_PATH}) returned None")
    if not asset_lib.save_asset(SCRATCH_PATH):
        _fail(f"save_asset({SCRATCH_PATH}) returned False after duplicate")
    _log(f"duplicated baseline -> {SCRATCH_PATH}")

    # Round 1 - force_rebind=True against the duplicate. M26.1.1 unblock
    # path: UE auto-created a stub override when the interface was added to
    # the baseline, and pre-M26.1.1 this would bail the op with 'skipped'.
    # Post-M26.1.1, force_rebind=True clears the stub and authors bindings.
    _log("round 1: implement_interface_function(force_rebind=True)")
    r1 = _run(force_rebind=True)
    r1_before = r1.get("before", {})
    r1_after = r1.get("after", {})
    _log(f"round 1 before: {r1_before}")
    _log(f"round 1 after:  {r1_after}")

    if not r1_before.get("override_exists"):
        _fail(
            "round 1 expected baseline to have a pre-existing stub override "
            "(UE auto-creates one when an interface is added to a BP). Got "
            f"override_exists=False. Either the fixture changed shape or the "
            f"duplicate path stripped the stub."
        )
    if not r1_after.get("bindings_applied"):
        _fail(
            f"round 1 did not apply bindings despite force_rebind=True. "
            f"after={r1_after}"
        )
    if len(r1_after.get("bindings", [])) != 3:
        _fail(f"round 1 expected 3 bindings, got {r1_after.get('bindings')}")

    r1_wiped = r1_after.get("wiped_nodes", -1)
    md5_r1 = _md5_of(SCRATCH_PATH)
    _log(f"round 1 md5:         {md5_r1}")
    _log(f"round 1 wiped_nodes: {r1_wiped}")

    # Round 2 - force_rebind=True on the already-bound scratch. Now there
    # are 2 VariableGet nodes (self.bIsAlive + self.Faction; bIsTargetable
    # is a literal default on Entry, not a node) plus Entry. force_rebind
    # must wipe the VariableGets (wiped_nodes > 0) and re-bind identically.
    _log("round 2: implement_interface_function(force_rebind=True)")
    r2 = _run(force_rebind=True)
    r2_after = r2.get("after", {})
    _log(f"round 2 after: {r2_after}")

    if not r2_after.get("bindings_applied"):
        _fail(f"round 2 did not apply bindings. after={r2_after}")
    if len(r2_after.get("bindings", [])) != 3:
        _fail(f"round 2 expected 3 bindings, got {r2_after.get('bindings')}")

    r2_wiped = r2_after.get("wiped_nodes", -1)
    if r2_wiped <= 0:
        _fail(
            f"round 2 expected wiped_nodes>0 (the 2 VariableGet nodes from "
            f"round 1 should have been wiped), got {r2_wiped}"
        )

    md5_r2 = _md5_of(SCRATCH_PATH)
    _log(f"round 2 md5:         {md5_r2}")
    _log(f"round 2 wiped_nodes: {r2_wiped}")

    if md5_r1 != md5_r2:
        _fail(
            f"md5 drift between rounds: r1={md5_r1} r2={md5_r2} - "
            "force_rebind is not deterministic across runs with identical "
            "inputs"
        )

    if r1_after.get("entry_guid") != r2_after.get("entry_guid"):
        _fail(
            f"Entry NodeGuid changed across wipe: "
            f"r1={r1_after.get('entry_guid')} r2={r2_after.get('entry_guid')}"
        )

    # Cleanup via file-level delete. EditorAssetLibrary.delete_asset
    # hits a `TypedElementRegistry::RegisteredElementType '0' has not
    # been registered` assertion in commandlet mode (the typed-element
    # registry is an editor-UI-side subsystem that doesn't fully init
    # headless), which crashes the commandlet AFTER the soak's
    # assertions have already passed. Unreferencing via file delete
    # sidesteps that path.
    import os
    scratch_filename = unreal.SystemLibrary.get_system_path(
        asset_lib.load_asset(SCRATCH_PATH)
    )
    _log(f"cleanup: removing scratch file {scratch_filename}")
    if scratch_filename and os.path.isfile(scratch_filename):
        try:
            os.remove(scratch_filename)
        except OSError as exc:
            _log(f"warning: os.remove({scratch_filename!r}) failed: {exc!r}")

    _log("SOAK PASS")
    _log(f"  round 1 wiped_nodes: {r1_wiped}  (cleared the baseline stub)")
    _log(f"  round 2 wiped_nodes: {r2_wiped}  (cleared round 1's bindings)")
    _log(f"  md5 (both rounds):   {md5_r1}")
    _log(f"  Entry NodeGuid:      {r1_after.get('entry_guid')}")


main()
