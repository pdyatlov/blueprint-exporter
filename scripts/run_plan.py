"""End-to-end CLI harness for the M24 Supervised Edit Loop.

One entry point that runs the full `run_plan` pipeline:
validate → execute → mechanical-diff → verification. Writes
`<plan>.run.json` next to the input plan. Exit codes:

  0 — validator passed, executor passed, diff + verification passed
  1 — any step reported failure (execution log at <plan>.run.json)
  2 — CLI misuse (missing -plan, file not found, malformed JSON)

Invocation:

    UnrealEditor-Cmd.exe <uproject> -run=pythonscript \\
        -script="<repo>/blueprint-exporter/scripts/run_plan.py" \\
        -nullrhi -unattended -nopause -nosplash -nosound -stdout \\
        -plan="<path-to-plan.json>"
"""

import json
import os
import sys

import unreal

_THIS_DIR = os.path.dirname(os.path.abspath(__file__))
if _THIS_DIR not in sys.path:
    sys.path.insert(0, _THIS_DIR)

from python_ops.mechanical_diff import format_diff_report
from python_ops.plan_executor import format_execution_report, run_plan


def _parse_plan_arg():
    """Extract `-plan=<path>` from UE's engine command line. UE's
    pythonscript harness strips `-flag=value` from sys.argv so we read
    it from `unreal.SystemLibrary.get_command_line()` instead."""
    cmdline = unreal.SystemLibrary.get_command_line()

    for prefix in ("-plan=", "-Plan="):
        idx = cmdline.find(prefix)
        if idx >= 0:
            rest = cmdline[idx + len(prefix) :]
            if rest.startswith('"'):
                end = rest.find('"', 1)
                if end > 0:
                    return rest[1:end]
            return rest.split()[0] if rest.strip() else None

    tokens = cmdline.split()
    for token, next_token in zip(tokens, tokens[1:]):
        if token.lower() == "-plan":
            return next_token.strip('"')
    return None


def main():
    plan_path = _parse_plan_arg()
    if not plan_path:
        unreal.log_error("run_plan: -plan=<path> argument is required")
        return 2

    if not os.path.isfile(plan_path):
        unreal.log_error(f"run_plan: plan file not found: {plan_path}")
        return 2

    try:
        with open(plan_path, "r", encoding="utf-8") as fp:
            plan = json.load(fp)
    except json.JSONDecodeError as exc:
        unreal.log_error(f"run_plan: plan JSON is malformed ({exc}): {plan_path}")
        return 2

    report = run_plan(plan)

    out_path = plan_path + ".run.json"
    try:
        with open(out_path, "w", encoding="utf-8") as fp:
            json.dump(report, fp, indent=2, default=str)
    except OSError as exc:
        unreal.log_error(f"run_plan: failed to write report to {out_path}: {exc}")
        return 2

    for line in format_execution_report(report["execution"]).splitlines():
        unreal.log(line)

    if report["diff"] is not None:
        unreal.log("")
        for line in format_diff_report(report["diff"]).splitlines():
            unreal.log(line)

    unreal.log(f"[RUN_PLAN] full report written to {out_path}")
    return 0 if report["passed"] else 1


_exit_code = main()
RUN_PLAN_EXIT_CODE = _exit_code
