"""CLI harness for python_ops.plan_validator (M24.1).

Invocation (via the UE Python commandlet):

    UnrealEditor-Cmd.exe <uproject> -run=pythonscript \\
        -script="<repo>/blueprint-exporter/scripts/run_plan_validator.py" \\
        -nullrhi -unattended -nopause -nosplash -nosound -stdout \\
        -plan="<path-to-plan.json>"

The `-plan=<path>` argument is read from `sys.argv`. The script:

  1. Loads the plan JSON
  2. Calls `validate_plan(plan)`
  3. Prints `format_report(report)` to stdout so the caller's terminal /
     log line-parses it easily
  4. Writes the full structured report as JSON next to the plan as
     `<plan>.validation.json` so automation can read it back
  5. Exits with code 0 on passed, 1 on failed schema / semantic issues,
     2 on CLI misuse (missing -plan, file not found, malformed JSON)

Pairs with `python_ops.plan_validator.validate_plan` — this file is a
thin UE-side entry point; the library is testable from pure Python
(sans UE, with asset checks stubbed out) if that matters later.
"""

import json
import os
import sys

import unreal

# Make the sibling python_ops package importable when running from
# UE's pythonscript harness (it does not add the script's parent to
# sys.path automatically).
_THIS_DIR = os.path.dirname(os.path.abspath(__file__))
if _THIS_DIR not in sys.path:
    sys.path.insert(0, _THIS_DIR)

from python_ops.plan_validator import format_report, validate_plan


def _parse_plan_arg():
    """Extract the value of `-plan=<path>` from UE's command line.

    UE's pythonscript harness strips `-flag=value` args from the
    interpreter's `sys.argv`, so we have to read them back from the
    engine-level command line via `unreal.SystemLibrary.get_command_line`.
    Accepts `-plan=X`, `-plan="X with spaces"`, and `-plan X` (space form,
    last resort). The split handles quotes because UE preserves them."""
    cmdline = unreal.SystemLibrary.get_command_line()

    # Find the first -plan= occurrence, extract the value to the next
    # unquoted whitespace (or end of line).
    prefix = "-plan="
    idx = cmdline.find(prefix)
    if idx < 0:
        prefix = "-Plan="
        idx = cmdline.find(prefix)
    if idx >= 0:
        rest = cmdline[idx + len(prefix) :]
        if rest.startswith('"'):
            end = rest.find('"', 1)
            if end > 0:
                return rest[1:end]
        # Unquoted: value runs to next whitespace.
        return rest.split()[0] if rest.strip() else None

    # Space-separated form: `-plan <path>`
    for token, next_token in zip(cmdline.split(), cmdline.split()[1:]):
        if token.lower() == "-plan":
            return next_token.strip('"')

    return None


def main():
    plan_path = _parse_plan_arg()
    if not plan_path:
        unreal.log_error(
            "run_plan_validator: -plan=<path> argument is required"
        )
        return 2

    if not os.path.isfile(plan_path):
        unreal.log_error(f"run_plan_validator: plan file not found: {plan_path}")
        return 2

    try:
        with open(plan_path, "r", encoding="utf-8") as fp:
            plan = json.load(fp)
    except json.JSONDecodeError as exc:
        unreal.log_error(
            f"run_plan_validator: plan JSON is malformed ({exc}): {plan_path}"
        )
        return 2

    report = validate_plan(plan)

    # Write the full report next to the plan for automation.
    out_path = plan_path + ".validation.json"
    try:
        with open(out_path, "w", encoding="utf-8") as fp:
            json.dump(report, fp, indent=2, default=str)
    except OSError as exc:
        unreal.log_error(
            f"run_plan_validator: failed to write report to {out_path}: {exc}"
        )
        return 2

    # Human-readable to stdout via unreal.log so it appears in the
    # commandlet log + stdout mirror.
    for line in format_report(report).splitlines():
        unreal.log(line)

    unreal.log(f"[PLAN_VALIDATOR] full report written to {out_path}")

    return 0 if report["passed"] else 1


_exit_code = main()

# UE's pythonscript harness does not honor sys.exit cleanly; leak the
# code via a module-level global for callers that want to chain.
PLAN_VALIDATOR_EXIT_CODE = _exit_code
