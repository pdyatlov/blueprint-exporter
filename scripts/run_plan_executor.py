"""CLI harness for python_ops.plan_executor (M24.2).

Invocation (via the UE Python commandlet):

    UnrealEditor-Cmd.exe <uproject> -run=pythonscript \\
        -script="<repo>/blueprint-exporter/scripts/run_plan_executor.py" \\
        -nullrhi -unattended -nopause -nosplash -nosound -stdout \\
        -plan="<path-to-plan.json>"

The `-plan=<path>` argument is read from UE's engine command line
(sys.argv does not work — UE strips `-flag=value` args). The script:

  1. Loads the plan JSON
  2. Calls `execute_plan(plan)` — which calls `validate_plan` internally
     and only proceeds if validation passes
  3. Prints `format_execution_report(report)` to stdout
  4. Writes the full structured report as JSON next to the plan as
     `<plan>.execution.json` so automation can read it back
  5. Exits 0 on passed, 1 on validation / execution failure,
     2 on CLI misuse (missing -plan, file not found, malformed JSON)

Pairs with `python_ops.plan_executor.execute_plan`. The executor aborts
on first op failure, so a failing plan may have already committed the
preceding ops to disk — inspect the execution report to decide whether
to retry (after fixing the plan) or roll back (typically via git / p4).
"""

import json
import os
import sys

import unreal

_THIS_DIR = os.path.dirname(os.path.abspath(__file__))
if _THIS_DIR not in sys.path:
    sys.path.insert(0, _THIS_DIR)

from python_ops.plan_executor import execute_plan, format_execution_report


def _parse_plan_arg():
    """Extract `-plan=<path>` from UE's engine command line.

    Mirror of `run_plan_validator._parse_plan_arg` — kept duplicated
    rather than factored out because UE's pythonscript discourages
    cross-file imports for free-standing harness scripts."""
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
        unreal.log_error(
            "run_plan_executor: -plan=<path> argument is required"
        )
        return 2

    if not os.path.isfile(plan_path):
        unreal.log_error(f"run_plan_executor: plan file not found: {plan_path}")
        return 2

    try:
        with open(plan_path, "r", encoding="utf-8") as fp:
            plan = json.load(fp)
    except json.JSONDecodeError as exc:
        unreal.log_error(
            f"run_plan_executor: plan JSON is malformed ({exc}): {plan_path}"
        )
        return 2

    report = execute_plan(plan)

    out_path = plan_path + ".execution.json"
    try:
        with open(out_path, "w", encoding="utf-8") as fp:
            json.dump(report, fp, indent=2, default=str)
    except OSError as exc:
        unreal.log_error(
            f"run_plan_executor: failed to write report to {out_path}: {exc}"
        )
        return 2

    for line in format_execution_report(report).splitlines():
        unreal.log(line)

    unreal.log(f"[PLAN_EXECUTOR] full report written to {out_path}")

    return 0 if report["passed"] else 1


_exit_code = main()

PLAN_EXECUTOR_EXIT_CODE = _exit_code
