"""M28.pre.5 in-process harness — apply add_gameplay_tag via run_plan.

Single-purpose UE pythonscript invoked by scripts/verify_tag_author.ps1.
Reads ``-tag=<name>`` and ``-comment=<text>`` and ``-source=<ini_name>`` from
the engine command line, then runs a 1-op plan through the standard
plan_executor.run_plan path so the harness exercises exactly the same
code path the MCP apply_plan tool would. Writes a result JSON back to
``$env:BPX_VERIFY_TAG_TMP`` for the PowerShell driver to inspect.

Exit 0 on success; 1 on plan-pipeline failure (the driver checks both
exit code and the result JSON's ``passed`` field).

Invocation:
    UnrealEditor-Cmd.exe BugHunt.uproject -run=pythonscript \\
        -script="scripts/verify_tag_author_harness.py" \\
        -nullrhi -unattended -nopause -nosplash -nosound \\
        -tag="BpxVerify.Smoke" \\
        -comment="M28.pre.5 parity-gate fixture" \\
        -source="DefaultGameplayTags.ini"
"""

import json
import os
import sys

import unreal


_THIS_DIR = os.path.dirname(os.path.abspath(__file__))
if _THIS_DIR not in sys.path:
    sys.path.insert(0, _THIS_DIR)

from python_ops.plan_executor import run_plan  # noqa: E402

TAG = "[m28.pre.5-tag-author]"


def _log(msg: str) -> None:
    unreal.log(f"{TAG} {msg}")


def _fail(msg: str) -> None:
    unreal.log_error(f"{TAG} FAIL: {msg}")
    raise SystemExit(1)


def _parse_cmd_arg(name: str) -> str:
    """Pull `-name=<value>` from UE's full command line. Mirrors
    inspect_harness._parse_cmd_arg — UE strips `-flag=val` from sys.argv
    in pythonscript mode, so we have to read from `get_command_line()`."""
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


def main() -> None:
    tag_name = _parse_cmd_arg("tag")
    dev_comment = _parse_cmd_arg("comment")
    source_ini = _parse_cmd_arg("source") or "DefaultGameplayTags.ini"

    if not tag_name:
        _fail("-tag=<name> required")

    plan = {
        "intended_outcome": f"M28.pre.5 verify_tag_author add: {tag_name}",
        "risk_level": "low",
        "operations": [
            {
                "op": "add_gameplay_tag",
                "tag_name": tag_name,
                "dev_comment": dev_comment,
                "source_ini": source_ini,
                "is_restricted": False,
            }
        ],
        "expected_side_effects": [],
        "verification": [],
    }

    _log(f"applying plan: tag={tag_name!r} source={source_ini!r}")
    report = run_plan(plan)

    out_root = os.environ.get("BPX_VERIFY_TAG_TMP") or os.path.join(
        os.environ.get("TEMP", "/tmp"), "bpx_verify_tag"
    )
    os.makedirs(out_root, exist_ok=True)
    out_path = os.path.join(out_root, "result.json")
    with open(out_path, "w", encoding="utf-8") as fp:
        json.dump(
            {
                "passed": bool(report.get("passed")),
                "tag_name": tag_name,
                "source_ini": source_ini,
                "execution": report.get("execution", {}),
            },
            fp,
            indent=2,
            default=str,
        )
    _log(f"result written to {out_path}")

    if not bool(report.get("passed")):
        _fail(f"run_plan reported passed=False. See {out_path}.")
    _log("HARNESS OK")


main()
