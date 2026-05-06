#requires -Version 5
<#
.SYNOPSIS
    M28.pre.4 -- fan-out pre-push gate across both engines + every gate type.

.DESCRIPTION
    Runs the full M28 verification matrix end-to-end with one invocation.
    Default mode exercises the cheap BugHunt (stock UE 5.7) leg:

      1. Automation tests (scripts/run_automation_tests.ps1)
      2. Determinism gate (scripts/verify_determinism.ps1 -SweepDeepDump)
      3. Per-op post-apply content inspection (scripts/verify_post_apply_inspect.ps1)
      4. Per-op determinism soak (scripts/verify_soak.ps1)

    With -IncludeDow, additionally runs gates 1 and 2 against the DOW
    project on the custom UE_DOW engine. Soak + inspect stay BugHunt-only
    because their assertions JSONs reference BugHunt fixtures; a future
    M28 op with DOW-side content can ship a second JSON that exercises
    DOW paths, and this wrapper will pick it up via
    scripts/inspect_fixtures/*.json iteration.

    Exits 0 iff every gate in the selected matrix returns 0. A summary
    table prints at the end with per-gate pass/fail + elapsed.

.PARAMETER IncludeDow
    Also run the DOW custom-engine legs of automation + determinism.
    DOW determinism defaults to -Filter=/Game/_ThirdParty/GASP_example/
    (363-asset slice) to keep total time bounded; override with -DowFilter.

.PARAMETER DowFilter
    Package prefix for the DOW determinism gate slice. Default
    /Game/_ThirdParty/GASP_example/.

.PARAMETER SkipSoak
    Skip all per-op soak runs. Useful when the soak template flags a
    pre-existing regression that you're investigating separately and
    want to verify the rest of the matrix independently.

.PARAMETER SkipInspect
    Skip all per-op post-apply inspection runs.

.PARAMETER StockEngine
    Override stock UE 5.7 exe path. Default:
    C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe

.PARAMETER CustomEngine
    Override custom UE_DOW exe path. Default:
    D:\Work\UE_DOW\engine\Binaries\Win64\UnrealEditor-Cmd.exe

.EXAMPLE
    pwsh -File scripts/verify_all.ps1

    Runs the BugHunt-only matrix: automation + determinism + all
    inspect/soak fixtures under scripts/inspect_fixtures/. ~3-5 min total.

.EXAMPLE
    pwsh -File scripts/verify_all.ps1 -IncludeDow

    Additionally runs automation + determinism against the DOW GASP
    slice on the custom engine. ~8-12 min total.

.NOTES
    M28.pre.4 (2026-04-23). Sibling of run_automation_tests / verify_determinism /
    verify_post_apply_inspect / verify_soak -- does not reimplement their
    logic, just fans them out across the right (Project, Engine) pairs.
#>

[CmdletBinding()]
param(
    [switch]$IncludeDow,

    [string]$DowFilter = '/Game/_ThirdParty/GASP_example/',

    [switch]$SkipSoak,
    [switch]$SkipInspect,

    [string]$StockEngine = 'C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe',
    [string]$CustomEngine = 'D:\Work\UE_DOW\engine\Binaries\Win64\UnrealEditor-Cmd.exe'
)

$ErrorActionPreference = 'Stop'

$ScriptsDir = $PSScriptRoot
$AutoScript      = Join-Path $ScriptsDir 'run_automation_tests.ps1'
$DetermScript    = Join-Path $ScriptsDir 'verify_determinism.ps1'
$InspectScript   = Join-Path $ScriptsDir 'verify_post_apply_inspect.ps1'
$SoakScript      = Join-Path $ScriptsDir 'verify_soak.ps1'
$TagAuthorScript = Join-Path $ScriptsDir 'verify_tag_author.ps1'  # M28.pre.5
$FixturesDir     = Join-Path $ScriptsDir 'inspect_fixtures'

foreach ($s in @($AutoScript, $DetermScript, $InspectScript, $SoakScript, $TagAuthorScript)) {
    if (-not (Test-Path -LiteralPath $s)) {
        Write-Error "Sibling gate script missing: $s"
        exit 2
    }
}

# ---------- gate runner ----------

$results = [System.Collections.Generic.List[object]]::new()

function Invoke-Gate {
    param(
        [string]$Name,
        [string]$Script,
        [string[]]$GateArgs,
        [bool]$Required = $true
    )
    Write-Host ""
    Write-Host ("==== [{0}] {1} {2}" -f $Name, (Split-Path -Leaf $Script), ($GateArgs -join ' ')) -ForegroundColor Cyan
    $start = Get-Date
    # Use pwsh -File so each gate runs in its own subshell -- isolates
    # $ErrorActionPreference=Stop and avoids bleed between gate state.
    $logPath = Join-Path $env:TEMP ("bpx_verify_all\" + (Get-Date -Format 'yyyyMMdd_HHmmss') + "_${Name}.log")
    $logDir = Split-Path -Parent $logPath
    if (-not (Test-Path -LiteralPath $logDir)) {
        New-Item -ItemType Directory -Path $logDir | Out-Null
    }
    # Spawn pwsh and capture its exit code. Param name is GateArgs (not Args)
    # because $Args is a reserved automatic variable — using it as a param
    # name silently fails to bind and the gate gets zero arguments.
    # Quoting: Start-Process -ArgumentList joins the array with spaces to
    # form the command line. Any element that contains a space (e.g. the
    # "C:\Program Files\..." engine path) is split into multiple args by
    # the child's argv parser unless we pre-embed double quotes. Script
    # paths always get quoted; all other elements containing whitespace or
    # `"` characters get quoted too.
    function Quote-IfNeeded([string]$s) {
        if ($null -eq $s) { return '""' }
        if ($s -match '[\s"]') {
            # Escape any embedded `"` and wrap the whole thing.
            return '"' + ($s -replace '"', '\"') + '"'
        }
        return $s
    }
    $quotedScript = Quote-IfNeeded $Script
    $quotedGateArgs = @()
    foreach ($ga in $GateArgs) { $quotedGateArgs += Quote-IfNeeded $ga }
    $allArgs = @('-NoProfile', '-File', $quotedScript) + $quotedGateArgs
    $proc = Start-Process -FilePath 'pwsh' -ArgumentList $allArgs `
        -NoNewWindow -Wait -PassThru `
        -RedirectStandardOutput $logPath -RedirectStandardError "$logPath.err"
    $elapsed = (Get-Date) - $start
    $passed = ($proc.ExitCode -eq 0)
    $results.Add([pscustomobject]@{
        Name     = $Name
        Passed   = $passed
        ExitCode = $proc.ExitCode
        Elapsed  = $elapsed
        Log      = $logPath
        Required = $Required
    })
    $verdict = if ($passed) { 'PASS' } else { 'FAIL' }
    $color = if ($passed) { 'Green' } else { 'Red' }
    Write-Host ("     {0} (exit={1}, {2:N1}s) -- log {3}" -f $verdict, $proc.ExitCode, $elapsed.TotalSeconds, $logPath) -ForegroundColor $color
    # Tail the gate's last 8 lines inline so the invoker sees something
    # useful without having to cd to the log dir.
    if (Test-Path -LiteralPath $logPath) {
        $tail = Get-Content -LiteralPath $logPath -Tail 8
        foreach ($line in $tail) {
            Write-Host ("       | $line")
        }
    }
}

$overallStart = Get-Date

# Availability-check the engines before any gate spawns pwsh. Missing
# engines get a clean warning here instead of cryptic per-gate
# "Engine exe not found" failures that look identical to real gate
# errors in the summary table.
$stockAvailable = Test-Path -LiteralPath $StockEngine -PathType Leaf
if (-not $stockAvailable) {
    Write-Host "[verify_all] WARN -- stock engine not found at:" -ForegroundColor Yellow
    Write-Host "           $StockEngine"
    Write-Host "           BugHunt legs will be skipped. Install UE 5.7 or pass -StockEngine <path>."
}
if ($IncludeDow) {
    $customAvailable = Test-Path -LiteralPath $CustomEngine -PathType Leaf
    if (-not $customAvailable) {
        Write-Host "[verify_all] WARN -- custom engine not found at:" -ForegroundColor Yellow
        Write-Host "           $CustomEngine"
        Write-Host "           DOW legs will be skipped. Install UE_DOW or pass -CustomEngine <path>."
    }
}

# ---------- BugHunt / stock 5.7 legs ----------

if ($stockAvailable) {
    Invoke-Gate -Name 'automation-bughunt' -Script $AutoScript -GateArgs @(
        '-Project', 'BugHunt'
        '-Engine',  $StockEngine
    )

    Invoke-Gate -Name 'determinism-bughunt' -Script $DetermScript -GateArgs @(
        '-Project',       'BugHunt'
        '-SweepDeepDump'
        '-Engine',        $StockEngine
    )
}

if ($stockAvailable -and -not $SkipInspect) {
    if (-not (Test-Path -LiteralPath $FixturesDir)) {
        Write-Host "[verify_all] inspect: no $FixturesDir -- skipping (no per-op fixtures authored yet)."
    } else {
        # Exclude *.prepare.json side-effect files that the inspect harness
        # writes next to each assertions JSON (<assertions>.prepare.json).
        $fixtures = Get-ChildItem -LiteralPath $FixturesDir -Filter '*.json' -File |
            Where-Object { $_.Name -notlike '*.prepare.json' }
        if (-not $fixtures) {
            Write-Host "[verify_all] inspect: $FixturesDir is empty -- skipping."
        } else {
            foreach ($fx in $fixtures) {
                # Honor per-fixture "skip_inspect": true. Introduced for M28.4.1
                # CurveFloat ops — UCurveFloat is not in the inventory pipeline's
                # logic-bearing set (PROJECT_INVENTORY_BRIEF.md §3), so the
                # re-export phase emits zero .md and inspect always fails. The
                # soak gate (byte-identity of the scratch .uasset across rounds)
                # still runs and carries the determinism signal.
                $cfg = Get-Content -LiteralPath $fx.FullName -Raw | ConvertFrom-Json
                if ($cfg.PSObject.Properties.Match('skip_inspect') -and $cfg.skip_inspect) {
                    Write-Host "[verify_all] inspect: $($fx.BaseName) has skip_inspect=true -- skipping inspect gate."
                    continue
                }
                Invoke-Gate -Name "inspect-$($fx.BaseName)" -Script $InspectScript -GateArgs @(
                    '-Assertions', $fx.FullName
                    '-Project',    'BugHunt'
                    '-Engine',     $StockEngine
                )
            }
        }
    }
} else {
    Write-Host "[verify_all] SkipInspect set -- skipping content-inspection fan-out."
}

if ($stockAvailable -and -not $SkipSoak) {
    if (Test-Path -LiteralPath $FixturesDir) {
        # Exclude *.prepare.json side-effect files that the inspect harness
        # writes next to each assertions JSON (<assertions>.prepare.json).
        $fixtures = Get-ChildItem -LiteralPath $FixturesDir -Filter '*.json' -File |
            Where-Object { $_.Name -notlike '*.prepare.json' }
        foreach ($fx in $fixtures) {
            # Only fan out to fixtures that declare a soak section. The
            # harness would exit with a missing-key FAIL otherwise, which
            # would false-red the matrix for op JSONs that legitimately
            # only care about inspect.
            $cfg = Get-Content -LiteralPath $fx.FullName -Raw | ConvertFrom-Json
            if ($cfg.PSObject.Properties.Match('soak') -and $cfg.soak) {
                Invoke-Gate -Name "soak-$($fx.BaseName)" -Script $SoakScript -GateArgs @(
                    '-Assertions', $fx.FullName
                    '-Project',    'BugHunt'
                    '-Engine',     $StockEngine
                )
            }
        }
    }
} else {
    Write-Host "[verify_all] SkipSoak set -- skipping soak fan-out."
}

# ---------- M28.pre.5 tag-author parity gate (BugHunt only) ----------
# Standalone gate for `add_gameplay_tag` since the op writes a Config/.ini
# text file rather than a /Game/ uasset, so the inspect+soak fan-out
# above can't cover it. The gate:
#   - snapshots BugHunt's Config/DefaultGameplayTags.ini bytes
#   - applies add_gameplay_tag via run_plan
#   - asserts exactly one +GameplayTagList= line was added with the new tag
#   - re-applies and asserts byte-identical (idempotence skip path)
#   - restores the baseline
# Bypassed when -SkipInspect is set (its content-correctness focus is the
# same category as inspect — when triaging a real inspect regression you
# typically want both off).

if ($stockAvailable -and -not $SkipInspect) {
    Invoke-Gate -Name 'tag-author-bughunt' -Script $TagAuthorScript -GateArgs @(
        '-Project', 'BugHunt'
        '-Engine',  $StockEngine
    )
}

# ---------- DOW / custom engine legs (opt-in) ----------

if ($IncludeDow -and $customAvailable) {
    Invoke-Gate -Name 'automation-dow' -Script $AutoScript -GateArgs @(
        '-Project', 'DOW'
        '-Engine',  $CustomEngine
    )

    Invoke-Gate -Name 'determinism-dow-slice' -Script $DetermScript -GateArgs @(
        '-Project',       'DOW'
        '-SweepDeepDump'
        '-Filter',        $DowFilter
        '-DeepAsset',     '/Game/_ThirdParty/GASP_example/Animation/PSD_SM_CMC_Idles'
        '-Engine',        $CustomEngine
    )
} else {
    Write-Host ""
    Write-Host "[verify_all] -IncludeDow not set; skipping DOW custom-engine legs."
    Write-Host "             For pre-push matrix against C++ touches on BpxReflectionOps,"
    Write-Host "             re-run with -IncludeDow."
}

# ---------- summary ----------

$overallElapsed = (Get-Date) - $overallStart

Write-Host ""
Write-Host "==== [verify_all] Summary ====" -ForegroundColor Cyan
$width = ($results | ForEach-Object { $_.Name.Length } | Measure-Object -Maximum).Maximum
foreach ($r in $results) {
    $line = "{0,-$width}  {1,4}  exit={2,-3}  {3,6:N1}s  {4}" -f `
        $r.Name,
        ($(if ($r.Passed) { 'PASS' } else { 'FAIL' })),
        $r.ExitCode,
        $r.Elapsed.TotalSeconds,
        $r.Log
    if ($r.Passed) {
        Write-Host "  $line" -ForegroundColor Green
    } else {
        Write-Host "  $line" -ForegroundColor Red
    }
}
Write-Host ""
Write-Host ("[verify_all] Total elapsed: {0:N1}s" -f $overallElapsed.TotalSeconds)

$failures = @($results | Where-Object { -not $_.Passed })
if ($failures.Count -eq 0) {
    Write-Host "[verify_all] ALL GATES PASS." -ForegroundColor Green
    exit 0
}

Write-Host "[verify_all] $($failures.Count) GATE(S) FAILED." -ForegroundColor Red
foreach ($f in $failures) {
    Write-Host "           $($f.Name)  (log $($f.Log))" -ForegroundColor Red
}
exit 1
