"""In-process entry points for the M27 editor bridge (M27.2).

Called by `BpxBridgeServer`/`BpxPlanHandlers` through
`FPythonScriptPlugin::ExecPythonCommandEx`. Unlike the subprocess-style
`run_plan.py` / `run_plan_validator.py` harnesses that read CLI args
from UE's command line and write sidecar JSON files, these functions
take explicit file paths as Python arguments and write the structured
report to `result_file` so the C++ caller can read it back.

Same library calls as the subprocess path (`python_ops.plan_validator.validate_plan`
and `python_ops.plan_executor.run_plan`) — only the glue changes, so there
is no fidelity risk between bridge and subprocess transports.
"""

import importlib
import json
import os
import sys

_THIS_DIR = os.path.dirname(os.path.abspath(__file__))
if _THIS_DIR not in sys.path:
    sys.path.insert(0, _THIS_DIR)


def _fresh_python_ops():
    """Reload the python_ops package + every submodule so mid-session edits
    to ``scripts/python_ops/**`` take effect on the next bridge call without
    restarting the editor.

    Rationale: ``IPythonScriptPlugin::ExecPythonCommandEx`` with
    ``EPythonFileExecutionScope::Private`` isolates locals/globals per call
    but ``sys.modules`` is shared across the editor's Python interpreter
    lifetime. Without explicit reload, an import of ``python_ops`` on the
    second bridge call returns the first call's cached module objects —
    stale against any on-disk edit. The cost is a handful of importlib.reload
    calls (~milliseconds) on each plan — trivial compared to UE-side work.

    Returns: (run_plan, validate_plan) — the two entry points the glue
    wrapper below needs, freshly bound to the on-disk source.
    """
    stale = [name for name in sys.modules if name.startswith("python_ops")]
    for name in stale:
        try:
            importlib.reload(sys.modules[name])
        except Exception:
            del sys.modules[name]

    from python_ops.plan_executor import run_plan as _run_plan
    from python_ops.plan_validator import validate_plan as _validate_plan
    return _run_plan, _validate_plan


def _load_plan(plan_file: str) -> dict:
    with open(plan_file, "r", encoding="utf-8") as fp:
        return json.load(fp)


def _write_report(result_file: str, report: dict) -> None:
    with open(result_file, "w", encoding="utf-8") as fp:
        json.dump(report, fp, indent=2, default=str)


def run_validate(plan_file: str, result_file: str) -> None:
    """Load plan, run M24.1 validator, write structured report to result_file."""
    _, validate_plan = _fresh_python_ops()
    _write_report(result_file, validate_plan(_load_plan(plan_file)))


def run_apply(plan_file: str, result_file: str) -> None:
    """Load plan, run full M24 pipeline (validate -> execute -> diff), write run-report."""
    run_plan, _ = _fresh_python_ops()
    _write_report(result_file, run_plan(_load_plan(plan_file)))
