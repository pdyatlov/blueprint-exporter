"""M28.pre.3 per-op determinism soak.

Generalised descendant of soak_m26_1_1_force_rebind.py — parameterised on
the same assertions JSON that scripts/inspect_harness.py consumes, so one
fixture file feeds both gates.

Applies the op N times against a duplicated scratch asset (default N=2),
asserts every round produces byte-identical .uasset md5, and asserts any
fields listed in soak.stable_keys agree across rounds. Catches the exact
class of bug M26.1.2 surfaced (pin-GUID FGuid::NewGuid(), linker-index
monotonic counter, MakeUniqueObjectName suffix drift). Every M28 write op
that calls NewObject<> / CreatePin / RemoveNode should ship with a soak
instance before merge.

Assertions JSON shape (additive to the post-apply-inspect shape):

    {
      ... (op / source_fixture / scratch_path / plan_kwargs as usual) ...
      "soak": {
        "rounds": 2,
        "stable_keys": ["entry_guid"],
        "round2_min_wiped_nodes": 1
      }
    }

    soak.rounds                 -- count of apply rounds (default 2).
    soak.stable_keys            -- list of keys in result.after that MUST
                                   agree across rounds. Dotted paths not
                                   supported yet; keys are top-level only.
    soak.round2_min_wiped_nodes -- if set and result.after carries a
                                   'wiped_nodes' count, round 2 must have
                                   wiped >= this many (catches idempotency
                                   skips in a rebind-style op).

Exit 0 iff every round landed successfully AND md5 identical across every
pair (r1==r2==...==rN) AND every stable_key agreed AND the optional
round2_min_wiped_nodes lower bound held.

Invocation:

    UnrealEditor-Cmd.exe <uproject> -run=pythonscript \\
        -script="scripts/soak_template.py" \\
        -nullrhi -unattended -nopause -nosplash -nosound \\
        -assertions="path/to/assertions.json"
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


TAG = "[m28.pre.3-soak]"


def _log(msg: str) -> None:
    unreal.log(f"{TAG} {msg}")


def _fail(msg: str) -> None:
    unreal.log_error(f"{TAG} FAIL: {msg}")
    raise SystemExit(1)


def _parse_cmd_arg(name: str) -> str:
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
    AssetRegistry to know about it. Used when a stale .uasset exists from
    a prior interrupted run but AR doesn't yet see it (fresh shell, no
    registry scan for the scratch path yet) -- load_asset would return
    None, but duplicate_asset into the same slot still fails because the
    physical file blocks it."""
    if not package_path.startswith("/Game/"):
        return ""
    rel = package_path[len("/Game/"):]
    return os.path.join(unreal.Paths.project_content_dir(), rel + ".uasset")


def _file_level_delete(package_path: str, evict_in_memory: bool = False) -> None:
    """Remove the .uasset at the package's canonical disk location, optionally
    also evicting any in-memory copy.

    Default behavior (file-level only): compute disk path from /Game/ mapping
    and `os.remove`. Catches stale .uasset files from prior interrupted runs
    even when AssetRegistry doesn't see them. Safe across all op types
    including those whose loaded UObjects trigger UE assertions on
    `EditorAssetLibrary.delete_asset` (TypedElementRegistry crashes on some
    BP types that the M28.pre.2 inspect harness exercises).

    With evict_in_memory=True: prepend an `EditorAssetLibrary.delete_asset`
    call to evict the loaded UObject too. Required for the M28.10.1
    `recreate_between_rounds` soak path (otherwise the in-memory UObject
    from round N-1 hits StaticLoadObject in round N's idempotence check
    and the op skips the create path it was supposed to exercise). Caller
    opts in only when the asset's class is known safe (UBlueprint creates
    don't trigger the TypedElementRegistry assertion).
    """
    asset_lib = unreal.EditorAssetLibrary
    if evict_in_memory and asset_lib.does_asset_exist(package_path):
        try:
            if asset_lib.delete_asset(package_path):
                _log(f"cleanup: delete_asset({package_path}) succeeded (mem+disk)")
                return
        except Exception as exc:
            _log(f"cleanup: delete_asset({package_path!r}) raised (non-fatal): {exc!r}")
    direct = _package_to_disk_path(package_path)
    if direct and os.path.isfile(direct):
        try:
            os.remove(direct)
            _log(f"cleanup: removed (direct) {direct}")
            return
        except OSError as exc:
            _log(f"cleanup: os.remove({direct!r}) failed (non-fatal): {exc!r}")
    asset = asset_lib.load_asset(package_path)
    if not asset:
        return
    filename = unreal.SystemLibrary.get_system_path(asset)
    if filename and os.path.isfile(filename):
        try:
            os.remove(filename)
            _log(f"cleanup: removed (via load) {filename}")
        except OSError as exc:
            _log(f"cleanup: os.remove({filename!r}) failed (non-fatal): {exc!r}")


def _first_op_after(report: dict) -> dict:
    """Pull the `after` dict from the first op's result. run_plan's shape is
    {passed, execution, diff}; execution has per_op[] each of shape
    {op_idx, op, result, error} where result is the library call's
    {success, op, target, field, before, after, errors} dict."""
    exec_report = report.get("execution", {})
    per_op = exec_report.get("per_op") or []
    if not per_op:
        return {}
    first = per_op[0]
    if not isinstance(first, dict):
        return {}
    op_result = first.get("result") or {}
    if not isinstance(op_result, dict):
        return {}
    return op_result.get("after", {}) or {}


def main() -> None:
    assertions_path = _parse_cmd_arg("assertions")
    if not assertions_path:
        _fail("-assertions=<path to assertions JSON> required")
    if not os.path.isfile(assertions_path):
        _fail(f"assertions file not found: {assertions_path}")

    with open(assertions_path, "r", encoding="utf-8") as fp:
        cfg = json.load(fp)

    soak_cfg = cfg.get("soak", {})
    rounds = int(soak_cfg.get("rounds", 2))
    if rounds < 2:
        _fail(f"soak.rounds must be >= 2 (got {rounds}); otherwise there's nothing to compare")
    stable_keys = list(soak_cfg.get("stable_keys", []))
    r2_min_wiped = soak_cfg.get("round2_min_wiped_nodes")
    # M28.10.1 — recreate_between_rounds: true tells the harness to delete the
    # scratch asset BEFORE each round so the op exercises the actual create
    # path on every round, not the idempotence-skip path. This is the only
    # way to surface FGuid::NewGuid() trapdoors on create ops (BlueprintGuid,
    # auto-spawned event NodeGuids, UCS entry NodeGuid). Without this flag,
    # the existing duplicate-then-apply pattern hits idempotence skip on
    # rounds 1..N and only verifies that the duplicate's bytes are stable.
    # When true, source_fixture is optional (no baseline duplicate occurs).
    recreate_between_rounds = bool(soak_cfg.get("recreate_between_rounds", False))

    required_keys = ("op", "scratch_path", "plan_kwargs")
    for key in required_keys:
        if key not in cfg:
            _fail(f"assertions JSON missing required key: {key}")
    if not recreate_between_rounds and "source_fixture" not in cfg:
        _fail("assertions JSON missing required key: source_fixture "
              "(required unless soak.recreate_between_rounds=true)")

    source_fixture = cfg.get("source_fixture")
    scratch_path   = cfg["scratch_path"]
    asset_lib = unreal.EditorAssetLibrary

    if not recreate_between_rounds:
        if not asset_lib.does_asset_exist(source_fixture):
            _fail(f"source fixture missing: {source_fixture}")

        # Unconditional pre-delete -- catches stale .uasset files from prior
        # interrupted runs even when AssetRegistry doesn't see them.
        _file_level_delete(scratch_path)

        duplicated = asset_lib.duplicate_asset(source_fixture, scratch_path)
        if duplicated is None:
            _fail(f"duplicate_asset({source_fixture} -> {scratch_path}) returned None")
        if not asset_lib.save_asset(scratch_path):
            _fail(f"save_asset({scratch_path}) returned False after duplicate")
        _log(f"duplicated {source_fixture} -> {scratch_path} (round 0 baseline)")
    else:
        # Real create-path soak — no baseline duplicate. Each round starts
        # with scratch_path absent so the op actually creates the asset.
        _file_level_delete(scratch_path, evict_in_memory=True)
        _log(f"recreate_between_rounds=true: scratch {scratch_path} pre-deleted "
             "(no baseline duplicate)")

    plan = {
        "intended_outcome": f"M28.pre.3 soak: {cfg['op']}",
        "risk_level": "low",
        "operations": [
            {
                "op": cfg["op"],
                **cfg["plan_kwargs"],
            }
        ],
        "expected_side_effects": cfg.get("expected_side_effects", [scratch_path]),
        "verification": cfg.get("verification", []),
    }

    round_md5s: list[str] = []
    round_afters: list[dict] = []

    for r in range(1, rounds + 1):
        # When recreate_between_rounds=true, wipe the scratch asset before
        # rounds 2..N so each round genuinely exercises the create path.
        # Round 1 already starts clean from the pre-delete above.
        # evict_in_memory=True flushes the UObject from memory so round N's
        # idempotence check actually sees the asset as absent.
        if recreate_between_rounds and r > 1:
            _file_level_delete(scratch_path, evict_in_memory=True)
            _log(f"round {r}: pre-deleted {scratch_path} (recreate_between_rounds)")

        _log(f"round {r}: applying plan (op={cfg['op']})")
        report = run_plan(plan)
        if not report.get("passed"):
            exec_msg = report.get("execution", {}).get("aborted_at") or "see report"
            _fail(f"round {r} reported passed=False (aborted_at={exec_msg!r}). "
                  "Full report in run_plan's normal output.")

        after = _first_op_after(report)
        md5 = _md5_of(scratch_path)
        round_md5s.append(md5)
        round_afters.append(after)
        _log(f"round {r} md5: {md5}")
        _log(f"round {r} after: {after}")

    # --- md5 stability across rounds ---
    misses: list[str] = []
    for r in range(2, rounds + 1):
        if round_md5s[r - 1] != round_md5s[0]:
            misses.append(
                f"md5 drift round{r}={round_md5s[r-1]} vs round1={round_md5s[0]}"
            )

    # --- stable_keys agree across rounds ---
    for key in stable_keys:
        v1 = round_afters[0].get(key)
        for r in range(2, rounds + 1):
            vr = round_afters[r - 1].get(key)
            if v1 != vr:
                misses.append(
                    f"soak.stable_keys[{key}] drift round{r}={vr!r} vs round1={v1!r}"
                )

    # --- round 2 wiped lower bound ---
    if r2_min_wiped is not None and rounds >= 2:
        r2_wiped = round_afters[1].get("wiped_nodes")
        if r2_wiped is None:
            misses.append(
                f"soak.round2_min_wiped_nodes={r2_min_wiped} but result.after "
                "has no 'wiped_nodes' key. Op may not be a rebind-style op; "
                "drop the constraint in assertions JSON or update result shape."
            )
        elif r2_wiped < r2_min_wiped:
            misses.append(
                f"round2 wiped_nodes={r2_wiped} < min={r2_min_wiped} -- "
                "op skipped the rebind path instead of exercising it."
            )

    # --- cleanup ---
    _file_level_delete(scratch_path)
    _log(f"cleanup: removed scratch {scratch_path}")

    if misses:
        for miss in misses:
            unreal.log_error(f"{TAG} FAIL: {miss}")
        _fail(f"soak failed with {len(misses)} assertion miss(es)")

    _log("SOAK PASS")
    _log(f"  rounds       = {rounds}")
    _log(f"  md5 (stable) = {round_md5s[0]}")
    if stable_keys:
        _log(f"  stable_keys  = {stable_keys}")
    if r2_min_wiped is not None:
        _log(f"  r2 wiped     = {round_afters[1].get('wiped_nodes')} (>= {r2_min_wiped})")


main()
