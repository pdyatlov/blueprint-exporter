"""M28.pre.2 post-apply content-inspection harness.

Two-mode Python script driven by scripts/verify_post_apply_inspect.ps1.
Reads a single assertions JSON, parameterised per op:

    {
      "op": "implement_interface_function",
      "source_fixture": "/Game/TestBlueprints/BP_BpxTestImplementsInterface",
      "scratch_path":   "/Game/TestBlueprints/BP_BpxTest_InspectScratch",
      "inspect_path":   "/Game/TestBlueprints/BP_BpxTest_InspectScratch",
      "plan_kwargs": {
        "bp_path":           "/Game/TestBlueprints/BP_BpxTest_InspectScratch",
        "interface_bp_path": "/Game/TestBlueprints/BPI_BpxTestInterface",
        "function_name":     "GetTargetingInfo",
        "output_bindings": {
          "bIsAlive":      "self.bIsAlive",
          "bIsTargetable": "true",
          "Faction":       "self.Faction"
        },
        "force_rebind": true
      },
      "expected_md":        ["Interface override of .*BPI_BpxTestInterface"],
      "not_expected_md":    ["stub \\(no authored body\\)"],
      "expected_deep":      ["bIsAlive", "bIsTargetable", "Faction"],
      "not_expected_deep":  []
    }

Modes:

  prepare -- duplicates source_fixture -> scratch_path, invokes the op via
             run_plan on a single-op synthetic plan, writes
             <assertions>.prepare.json with plan outcome + md5.

  cleanup -- file-level removes scratch_path's .uasset so the next run
             has a clean slate. Pattern lifted from soak_m26_1_1_force_rebind.py
             -- EditorAssetLibrary.delete_asset hits a TypedElementRegistry
             assertion in commandlet mode. File-level unlink sidesteps it.

Exit codes:
  0 on success; 1 on failure with an error written via unreal.log_error.
  Non-zero commandlet exit is what the PowerShell driver watches for.

Invocation:

    UnrealEditor-Cmd.exe <uproject> -run=pythonscript \\
        -script="scripts/inspect_harness.py" \\
        -nullrhi -unattended -nopause -nosplash -nosound \\
        -mode=prepare -assertions="path/to/assertions.json"
"""

import hashlib
import json
import os
import sys

import unreal

_THIS_DIR = os.path.dirname(os.path.abspath(__file__))
if _THIS_DIR not in sys.path:
    sys.path.insert(0, _THIS_DIR)

from python_ops.plan_executor import run_plan  # noqa: E402


TAG = "[m28.pre.2-inspect]"


def _log(msg: str) -> None:
    unreal.log(f"{TAG} {msg}")


def _fail(msg: str) -> None:
    unreal.log_error(f"{TAG} FAIL: {msg}")
    raise SystemExit(1)


def _parse_cmd_arg(name: str) -> str:
    """Pull `-name=<value>` out of UE's engine command line. UE's pythonscript
    harness strips `-flag=value` from sys.argv; `get_command_line()` keeps them."""
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


def _md5_of(package_path: str) -> str:
    asset = unreal.EditorAssetLibrary.load_asset(package_path)
    if not asset:
        return ""
    filename = unreal.SystemLibrary.get_system_path(asset)
    if not filename or not os.path.isfile(filename):
        return ""
    with open(filename, "rb") as fp:
        return hashlib.md5(fp.read()).hexdigest()


def _package_to_disk_path(package_path: str) -> str:
    """Map /Game/X/Y to <ProjectContentDir>/X/Y.uasset without needing
    AssetRegistry to know about it. Needed when a stale .uasset from a
    prior interrupted run is still on disk but AR hasn't scanned it
    yet -- duplicate_asset would fail on the physical file block."""
    if not package_path.startswith("/Game/"):
        return ""
    rel = package_path[len("/Game/"):]
    return os.path.join(unreal.Paths.project_content_dir(), rel + ".uasset")


def _file_level_delete(package_path: str) -> None:
    """Matches soak_m26_1_1_force_rebind.py cleanup. Avoids
    EditorAssetLibrary.delete_asset's TypedElementRegistry assertion in
    commandlet mode. Two-prong: direct /Game/ -> disk path first
    (works when AR doesn't see the asset), load_asset fallback second."""
    direct = _package_to_disk_path(package_path)
    if direct and os.path.isfile(direct):
        try:
            os.remove(direct)
            _log(f"cleanup: removed (direct) {direct}")
            return
        except OSError as exc:
            _log(f"cleanup: os.remove({direct!r}) failed (non-fatal): {exc!r}")
    asset = unreal.EditorAssetLibrary.load_asset(package_path)
    if not asset:
        return
    filename = unreal.SystemLibrary.get_system_path(asset)
    if filename and os.path.isfile(filename):
        try:
            os.remove(filename)
            _log(f"cleanup: removed (via load) {filename}")
        except OSError as exc:
            _log(f"cleanup: os.remove({filename!r}) failed (non-fatal): {exc!r}")


def _mode_prepare(cfg: dict, assertions_path: str) -> None:
    asset_lib = unreal.EditorAssetLibrary

    source_fixture = cfg["source_fixture"]
    scratch_path   = cfg["scratch_path"]

    if not asset_lib.does_asset_exist(source_fixture):
        _fail(f"source fixture missing: {source_fixture} "
              "(run GenerateTestBlueprintsCommandlet first if this is a BugHunt fixture)")

    # Unconditional pre-delete -- catches stale .uasset files from prior
    # interrupted runs even when AssetRegistry doesn't see them.
    _file_level_delete(scratch_path)

    duplicated = asset_lib.duplicate_asset(source_fixture, scratch_path)
    if duplicated is None:
        _fail(f"duplicate_asset({source_fixture} -> {scratch_path}) returned None")
    if not asset_lib.save_asset(scratch_path):
        _fail(f"save_asset({scratch_path}) returned False after duplicate")
    _log(f"duplicated {source_fixture} -> {scratch_path}")

    plan = {
        "intended_outcome": cfg.get("intended_outcome",
                                    f"M28.pre.2 content inspection: {cfg['op']}"),
        "risk_level": cfg.get("risk_level", "low"),
        "operations": [
            {
                "op": cfg["op"],
                **cfg["plan_kwargs"],
            }
        ],
        "expected_side_effects": cfg.get("expected_side_effects",
                                         [scratch_path]),
        "verification": cfg.get("verification", []),
    }

    _log(f"applying plan: op={cfg['op']}")
    report = run_plan(plan)

    md5 = _md5_of(scratch_path)

    prepare_out = {
        "passed":         bool(report.get("passed")),
        "op":             cfg["op"],
        "scratch_path":   scratch_path,
        "scratch_md5":    md5,
        "execution":     report.get("execution", {}),
        "diff":           report.get("diff"),
    }

    # Write the prepare report next to the UE log rather than next to the
    # assertions JSON -- otherwise it pollutes the fixtures dir and the
    # verify_all.ps1 fan-out would try to treat it as a new assertions
    # file. Use a deterministic path inside the system temp tree so the
    # driver (verify_post_apply_inspect.ps1) can find it.
    temp_root = os.environ.get("BPX_INSPECT_TMP") or os.path.join(
        os.environ.get("TEMP", "/tmp"), "bpx_inspect"
    )
    os.makedirs(temp_root, exist_ok=True)
    out_path = os.path.join(
        temp_root,
        os.path.basename(assertions_path) + ".prepare.json",
    )
    with open(out_path, "w", encoding="utf-8") as fp:
        json.dump(prepare_out, fp, indent=2, default=str)
    _log(f"prepare report written to {out_path}")

    if not prepare_out["passed"]:
        _fail(f"run_plan reported passed=False. See {out_path} for the execution report.")

    _log(f"scratch md5: {md5}")
    _log("PREPARE OK")


def _mode_cleanup(cfg: dict, assertions_path: str) -> None:
    scratch_path = cfg["scratch_path"]
    _file_level_delete(scratch_path)
    _log("CLEANUP OK")


def main() -> None:
    mode = _parse_cmd_arg("mode")
    assertions_path = _parse_cmd_arg("assertions")

    if mode not in ("prepare", "cleanup"):
        _fail(f"-mode=<prepare|cleanup> required, got {mode!r}")
    if not assertions_path:
        _fail("-assertions=<path to assertions JSON> required")
    if not os.path.isfile(assertions_path):
        _fail(f"assertions file not found: {assertions_path}")

    with open(assertions_path, "r", encoding="utf-8") as fp:
        cfg = json.load(fp)

    for key in ("op", "source_fixture", "scratch_path", "plan_kwargs"):
        if key not in cfg:
            _fail(f"assertions JSON missing required key: {key}")

    if mode == "prepare":
        _mode_prepare(cfg, assertions_path)
    else:
        _mode_cleanup(cfg, assertions_path)


main()
