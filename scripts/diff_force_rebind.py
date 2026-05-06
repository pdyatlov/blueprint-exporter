"""Diagnostic: find what bytes differ between round 1 and round 2 of the
M26.1 force_rebind path so we can identify the remaining non-determinism
source.

Mirrors the soak but copies the .uasset bytes to memory between rounds
and diffs the two byte strings, printing the differing offsets + a
surrounding context window.
"""

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

TAG = "[force-rebind-diff]"


def _log(msg):
    unreal.log(f"{TAG} {msg}")


def _read_uasset() -> bytes:
    filename = unreal.SystemLibrary.get_system_path(
        unreal.EditorAssetLibrary.load_asset(SCRATCH_PATH)
    )
    with open(filename, "rb") as f:
        return f.read()


def _run():
    return implement_interface_function(
        bp_path=SCRATCH_PATH,
        interface_bp_path=INTERFACE_PATH,
        function_name=FUNCTION_NAME,
        output_bindings=BINDINGS,
        force_rebind=True,
    )


def main():
    asset_lib = unreal.EditorAssetLibrary
    if asset_lib.does_asset_exist(SCRATCH_PATH):
        asset_lib.delete_asset(SCRATCH_PATH)
    asset_lib.duplicate_asset(BASELINE_PATH, SCRATCH_PATH)
    asset_lib.save_asset(SCRATCH_PATH)

    r1 = _run()
    bytes_r1 = _read_uasset()
    _log(f"round 1: success={r1.get('success')} size={len(bytes_r1)} "
         f"wiped={r1.get('after', {}).get('wiped_nodes')}")

    r2 = _run()
    bytes_r2 = _read_uasset()
    _log(f"round 2: success={r2.get('success')} size={len(bytes_r2)} "
         f"wiped={r2.get('after', {}).get('wiped_nodes')}")

    if bytes_r1 == bytes_r2:
        _log("BYTES IDENTICAL - drift fixed")
        return

    n = min(len(bytes_r1), len(bytes_r2))
    diffs = []
    for i in range(n):
        if bytes_r1[i] != bytes_r2[i]:
            diffs.append(i)

    _log(f"DRIFT: {len(diffs)} differing bytes (size r1={len(bytes_r1)} r2={len(bytes_r2)})")

    # Coalesce adjacent diffs into runs.
    if diffs:
        runs = []
        start = diffs[0]
        prev = diffs[0]
        for i in diffs[1:]:
            if i - prev <= 4:
                prev = i
            else:
                runs.append((start, prev))
                start = i
                prev = i
        runs.append((start, prev))
        _log(f"coalesced into {len(runs)} runs (gap<=4 bytes)")
        for idx, (s, e) in enumerate(runs[:20]):
            ctx_s = max(0, s - 8)
            ctx_e = min(n, e + 8 + 1)
            r1_slice = bytes_r1[ctx_s:ctx_e].hex()
            r2_slice = bytes_r2[ctx_s:ctx_e].hex()
            _log(f"  run {idx}: bytes [{s}..{e}] ({e - s + 1} bytes)")
            _log(f"    r1 @[{ctx_s}..{ctx_e}]: {r1_slice}")
            _log(f"    r2 @[{ctx_s}..{ctx_e}]: {r2_slice}")


main()
