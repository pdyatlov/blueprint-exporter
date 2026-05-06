"""Cross-session drift probe.

Single-shot apply of `implement_interface_function(force_rebind=True)` against a
freshly duplicated scratch asset. Dumps the resulting .uasset bytes + md5 to
the file path passed via -out=<path>. Intended to be invoked twice in two
independent UnrealEditor-Cmd.exe shells so the driver can diff the two
captures.

Each invocation is self-contained: pre-delete scratch, duplicate baseline,
apply op, dump. Both shells start from byte-identical state on disk, so any
diff in the captured bytes is cross-session drift attributable to op + save
path (not input-state drift).

Invoke:

    UnrealEditor-Cmd.exe <BugHunt.uproject> \\
        -run=pythonscript \\
        -script="scripts/probe_cross_session_drift.py" \\
        -out="C:/path/to/shellA.bin" \\
        -nullrhi -unattended -nopause -nosplash -nosound
"""

import hashlib
import os
import sys

import unreal

_THIS_DIR = os.path.dirname(os.path.abspath(__file__))
if _THIS_DIR not in sys.path:
    sys.path.insert(0, _THIS_DIR)

from python_ops import implement_interface_function  # noqa: E402


BASELINE_PATH = "/Game/TestBlueprints/BP_BpxTestImplementsInterface"
SCRATCH_PATH  = "/Game/TestBlueprints/BP_BpxTest_CrossSessionDrift"
INTERFACE_PATH = "/Game/TestBlueprints/BPI_BpxTestInterface"
FUNCTION_NAME = "GetTargetingInfo"

BINDINGS = {
    "bIsAlive":      "self.bIsAlive",
    "bIsTargetable": "true",
    "Faction":       "self.Faction",
}

TAG = "[cross-session-probe]"


def _log(msg):
    unreal.log(f"{TAG} {msg}")


def _fail(msg):
    unreal.log_error(f"{TAG} FAIL: {msg}")
    raise SystemExit(1)


def _parse_cmd_arg(name):
    cmdline = unreal.SystemLibrary.get_command_line()
    for prefix in (f"-{name}=", f"-{name.capitalize()}="):
        idx = cmdline.find(prefix)
        if idx >= 0:
            rest = cmdline[idx + len(prefix):]
            if rest.startswith('"'):
                end = rest.find('"', 1)
                if end > 0:
                    return rest[1:end]
            return rest.split()[0] if rest.strip() else ""
    return ""


def _package_to_disk_path(package_path):
    rel = package_path[len("/Game/"):]
    return os.path.join(unreal.Paths.project_content_dir(), rel + ".uasset")


def _file_level_delete(package_path):
    direct = _package_to_disk_path(package_path)
    if direct and os.path.isfile(direct):
        try:
            os.remove(direct)
            _log(f"pre-clean: removed {direct}")
        except OSError as exc:
            _log(f"pre-clean failed (non-fatal): {exc!r}")


def main():
    out_path = _parse_cmd_arg("out")
    if not out_path:
        _fail("-out=<path to bytes capture> required")

    asset_lib = unreal.EditorAssetLibrary

    if not asset_lib.does_asset_exist(BASELINE_PATH):
        _fail(f"baseline {BASELINE_PATH} missing")
    if not asset_lib.does_asset_exist(INTERFACE_PATH):
        _fail(f"interface {INTERFACE_PATH} missing")

    _file_level_delete(SCRATCH_PATH)

    duplicated = asset_lib.duplicate_asset(BASELINE_PATH, SCRATCH_PATH)
    if duplicated is None:
        _fail(f"duplicate_asset({BASELINE_PATH} -> {SCRATCH_PATH}) returned None")
    if not asset_lib.save_asset(SCRATCH_PATH):
        _fail(f"save_asset({SCRATCH_PATH}) returned False after duplicate")
    _log(f"duplicated baseline -> {SCRATCH_PATH}")

    result = implement_interface_function(
        bp_path=SCRATCH_PATH,
        interface_bp_path=INTERFACE_PATH,
        function_name=FUNCTION_NAME,
        output_bindings=BINDINGS,
        force_rebind=True,
    )
    if not result.get("success"):
        _fail(f"implement_interface_function returned success=False. errors={result.get('errors')}")

    after = result.get("after", {})
    _log(f"after: {after}")

    filename = unreal.SystemLibrary.get_system_path(asset_lib.load_asset(SCRATCH_PATH))
    if not filename or not os.path.isfile(filename):
        _fail(f"could not resolve saved .uasset filename for {SCRATCH_PATH}")
    with open(filename, "rb") as fp:
        payload = fp.read()

    md5 = hashlib.md5(payload).hexdigest()
    _log(f"captured {len(payload)} bytes, md5={md5}")
    _log(f"entry_guid={after.get('entry_guid')}")

    out_dir = os.path.dirname(out_path)
    if out_dir and not os.path.isdir(out_dir):
        os.makedirs(out_dir, exist_ok=True)
    with open(out_path, "wb") as fp:
        fp.write(payload)
    with open(out_path + ".meta.txt", "w", encoding="utf-8") as fp:
        fp.write(f"md5={md5}\n")
        fp.write(f"bytes={len(payload)}\n")
        fp.write(f"entry_guid={after.get('entry_guid')}\n")
    _log(f"wrote capture -> {out_path}")

    _file_level_delete(SCRATCH_PATH)
    _log("PROBE DONE")


main()
