"""Regenerate the M26.1 BugHunt golden fixture.

Duplicates the BP_BpxTestImplementsInterface baseline (produced by
`GenerateTestBlueprintsCommandlet`) and applies
`implement_interface_function` to the duplicate, saving the result
as BP_BpxTestImplementsInterface_Expected. The committed _Expected
.uasset is what regression tests diff against.

Run after the commandlet regenerates the baseline:

    UnrealEditor-Cmd.exe <BugHunt.uproject> \
        -run=GenerateTestBlueprints -nullrhi -unattended -nopause -nosplash -nosound
    UnrealEditor-Cmd.exe <BugHunt.uproject> \
        -run=pythonscript \
        -script="D:/Work/blueprintexporter/blueprint-exporter/scripts/regenerate_m26_1_golden.py" \
        -nullrhi -unattended -nopause -nosplash -nosound

Both passes are idempotent — re-running on a clean tree produces
byte-identical .uasset bytes thanks to the M26.1 bridge's md5-seeded
NodeGuids. A determinism twin-run on BugHunt exercises this end-to-end.
"""

import sys

import unreal

# The python_ops package lives next to this script.
sys.path.insert(
    0,
    r"D:/Work/blueprintexporter/blueprint-exporter/scripts",
)

from python_ops import implement_interface_function  # noqa: E402


BASELINE_PATH = "/Game/TestBlueprints/BP_BpxTestImplementsInterface"
EXPECTED_PATH = "/Game/TestBlueprints/BP_BpxTestImplementsInterface_Expected"
INTERFACE_PATH = "/Game/TestBlueprints/BPI_BpxTestInterface"
FUNCTION_NAME = "GetTargetingInfo"


def _fail(message: str) -> None:
    unreal.log_error(f"[m26.1-golden] {message}")
    raise SystemExit(1)


def main() -> None:
    asset_lib = unreal.EditorAssetLibrary

    if not asset_lib.does_asset_exist(BASELINE_PATH):
        _fail(
            f"baseline {BASELINE_PATH} missing — run "
            f"GenerateTestBlueprintsCommandlet first"
        )
    if not asset_lib.does_asset_exist(INTERFACE_PATH):
        _fail(
            f"interface {INTERFACE_PATH} missing — run "
            f"GenerateTestBlueprintsCommandlet first"
        )

    # Start fresh so md5-seeded determinism is unambiguous.
    if asset_lib.does_asset_exist(EXPECTED_PATH):
        unreal.log(f"[m26.1-golden] removing stale {EXPECTED_PATH}")
        if not asset_lib.delete_asset(EXPECTED_PATH):
            _fail(f"delete_asset({EXPECTED_PATH}) returned False")

    duplicated = asset_lib.duplicate_asset(BASELINE_PATH, EXPECTED_PATH)
    if duplicated is None:
        _fail(f"duplicate_asset({BASELINE_PATH} -> {EXPECTED_PATH}) returned None")
    if not asset_lib.save_asset(EXPECTED_PATH):
        _fail(f"save_asset({EXPECTED_PATH}) returned False after duplicate")
    unreal.log(f"[m26.1-golden] duplicated baseline -> {EXPECTED_PATH}")

    # force_rebind=True because the duplicated baseline carries an auto-
    # created stub override (UE adds one when an interface is added to a
    # BP). Without force_rebind the idempotency check bails with
    # 'skipped: override graph already exists' and no bindings get
    # authored. Pre-M26.1.2 the regen would still look successful at the
    # commandlet level, but the committed _Expected was actually an empty
    # stub matching the baseline. M26.1.2 pin-GUID seeding made the
    # round-trip byte-deterministic so force_rebind is safe to use here
    # unconditionally.
    result = implement_interface_function(
        bp_path=EXPECTED_PATH,
        interface_bp_path=INTERFACE_PATH,
        function_name=FUNCTION_NAME,
        output_bindings={
            "bIsAlive":      "self.bIsAlive",
            "bIsTargetable": "true",
            "Faction":       "self.Faction",
        },
        force_rebind=True,
    )

    if not result["success"]:
        _fail(f"op failed: {result.get('errors')}")

    unreal.log(
        f"[m26.1-golden] op landed: {result.get('after')}"
    )
    unreal.log("[m26.1-golden] done — _Expected fixture regenerated")


main()
