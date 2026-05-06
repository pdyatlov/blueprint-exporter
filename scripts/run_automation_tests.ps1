#requires -Version 5
<#
.SYNOPSIS
    Pre-push automation gate for BlueprintExporter plugin tests.

.DESCRIPTION
    Runs the `BlueprintExporter.*` ATF suite headless against a BugHunt or DOW
    project and asserts every matched test passed. Exit 0 iff every test the
    run observed passed. Exit 1 on test failure, invocation error, OR the
    M28.pre.1 regression signature: `LogAutomationTest: Skipping unit tests
    for the cooked build and commandlet`.

    That signature means at least one test is missing
    `EAutomationTestFlags::CommandletContext` in its flag mask. If we hit it
    the matrix silently no-ops and reports a false green, which is exactly
    the bug M28.pre.1 set out to close. Every IMPLEMENT_SIMPLE_AUTOMATION_TEST
    in the plugin MUST include `CommandletContext` — this script enforces
    that at the matrix level.

.PARAMETER Project
    Which project hosts the tests. "BugHunt" (default, committed fixtures at
    blueprint-exporter/BugHunt/TestProject) or "DOW" (studio project at
    D:\Work\UE_DOW\game).

.PARAMETER Filter
    Test filter passed to `Automation RunTests`. Defaults to `BlueprintExporter.`
    which matches every test in the plugin. Narrow with `BlueprintExporter.Schema.`,
    `.StateTree.`, or `.TextExport.` when only one area is in scope.

.PARAMETER Engine
    Override the UnrealEditor-Cmd.exe path. Defaults to the custom UE_DOW
    engine. For BugHunt you typically want stock 5.7 — pass it explicitly.

.PARAMETER ProjectFile
    Override the .uproject path. Default is project-specific:
    BugHunt -> blueprint-exporter/BugHunt/TestProject/BugHunt.uproject
    DOW     -> D:\Work\UE_DOW\game\UE_DOW.uproject

.PARAMETER LogPath
    Where to write the UE log. Default is a timestamped file under
    %TEMP%\bpx_automation\. Always written even on success so post-hoc
    diagnostics stay possible.

.EXAMPLE
    .\scripts\run_automation_tests.ps1 -Project BugHunt -Engine 'C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe'

    Full BlueprintExporter.* suite against BugHunt on stock UE 5.7.

.EXAMPLE
    .\scripts\run_automation_tests.ps1 -Project BugHunt -Filter BlueprintExporter.Schema.

    Only the schema tests.

.NOTES
    M28.pre.1 (2026-04-23) — replaces the raw commandlet invocation that
    silently skipped every test before the CommandletContext flag fix.
    Canonical flag mask for any new test:
        EAutomationTestFlags::EditorContext |
        EAutomationTestFlags::CommandletContext |
        EAutomationTestFlags::EngineFilter
#>

[CmdletBinding()]
param(
    [ValidateSet('BugHunt', 'DOW')]
    [string]$Project = 'BugHunt',

    [string]$Filter = 'BlueprintExporter.',

    [string]$Engine = 'D:\Work\UE_DOW\engine\Binaries\Win64\UnrealEditor-Cmd.exe',

    [string]$ProjectFile,

    [string]$LogPath
)

$ErrorActionPreference = 'Stop'
$RepoRoot = Split-Path -Parent $PSScriptRoot  # .../blueprint-exporter

if (-not $ProjectFile) {
    $ProjectFile = switch ($Project) {
        'BugHunt' { Join-Path $RepoRoot 'BugHunt\TestProject\BugHunt.uproject' }
        'DOW'     { 'D:\Work\UE_DOW\game\UE_DOW.uproject' }
    }
}

if (-not $LogPath) {
    $stamp = Get-Date -Format 'yyyyMMdd_HHmmss'
    $tempDir = Join-Path $env:TEMP 'bpx_automation'
    if (-not (Test-Path -LiteralPath $tempDir)) {
        New-Item -ItemType Directory -Path $tempDir | Out-Null
    }
    $LogPath = Join-Path $tempDir "run_${Project}_${stamp}.log"
}

if (-not (Test-Path -LiteralPath $Engine -PathType Leaf)) {
    Write-Error "Engine exe not found: $Engine"
    exit 2
}
if (-not (Test-Path -LiteralPath $ProjectFile -PathType Leaf)) {
    Write-Error "Project file not found: $ProjectFile"
    exit 2
}

$ExtraArgs = switch ($Project) {
    'BugHunt' { @() }
    'DOW'     { @('-EnablePlugins=BlueprintExporter') }
}

# Quoting discipline: `-ExecCmds` and `-testexit` values both contain spaces,
# so each must be wrapped in double quotes in the actual command line. With
# Start-Process -ArgumentList, PowerShell joins the array with spaces and
# passes the resulting string to the child. We pre-embed literal `"` in each
# element so the child's argv parser sees the intended quoting.
#
# Do NOT append `; Quit` to -ExecCmds. `Quit` fires immediately after
# `Automation RunTests` returns (the command queues asynchronously and
# returns instantly), so the editor exits before any test runs. `-testexit`
# with the log-line trigger is the correct exit gate: ATF emits
# `LogAutomationCommandLine: Display: ...Automation Test Queue Empty...`
# when the queue drains, and `-testexit` matches against that substring.
$argsList = @(
    "`"$ProjectFile`""
    "-ExecCmds=`"Automation RunTests $Filter`""
    "-testexit=`"Automation Test Queue Empty`""
) + $ExtraArgs + @(
    '-unattended'
    '-nopause'
    '-nullrhi'
    '-nosplash'
    '-nosound'
    '-log'
)

Write-Host "[automation] Project=$Project Filter=$Filter"
Write-Host "[automation] Engine=$Engine"
Write-Host "[automation] Log=$LogPath"
Write-Host "[automation] Running..."

$start = Get-Date
$proc = Start-Process -FilePath $Engine -ArgumentList $argsList `
    -NoNewWindow -Wait -PassThru `
    -RedirectStandardOutput $LogPath -RedirectStandardError "$LogPath.err"
$elapsed = (Get-Date) - $start

Write-Host ("[automation] UE exited after {0:N1}s, exit code = {1}." -f $elapsed.TotalSeconds, $proc.ExitCode)

# UE's stdout capture on Windows is unreliable AND can be partial (see
# M27.2 pipe-deadlock arc): the log file may be non-empty but still missing
# the lines that carry the per-test Pass/Fail markers. Prefer
# Saved/Logs/<Project>.log when available -- it's the full engine log and
# is authoritative.
$projectDir  = Split-Path -Parent $ProjectFile
$projectName = [IO.Path]::GetFileNameWithoutExtension($ProjectFile)
$fallback    = Join-Path $projectDir "Saved\Logs\${projectName}.log"
$logContent  = ''
if (Test-Path -LiteralPath $fallback) {
    Write-Host "[automation] reading authoritative log at $fallback"
    $logContent = Get-Content -LiteralPath $fallback -Raw
    Copy-Item -LiteralPath $fallback -Destination $LogPath -Force
} elseif ((Test-Path -LiteralPath $LogPath) -and ((Get-Item -LiteralPath $LogPath).Length -gt 0)) {
    $logContent = Get-Content -LiteralPath $LogPath -Raw
}

if (-not $logContent) {
    Write-Host "[automation] FAIL -- no log content captured (neither stdout nor Saved/Logs)." -ForegroundColor Red
    exit 1
}

# Regression signature: CommandletContext flag missing. If we ever see this,
# at least one test silently no-oped and the matrix lied green. The fix is
# ALWAYS to add `EAutomationTestFlags::CommandletContext` to the test's flag
# mask -- NEVER to swallow the signal here.
if ($logContent -match 'Skipping unit tests for the cooked build and commandlet') {
    Write-Host ""
    Write-Host "[automation] FAIL -- ATF reported `"Skipping unit tests for the cooked build and commandlet`"." -ForegroundColor Red
    Write-Host "             At least one test is missing EAutomationTestFlags::CommandletContext in its flag mask."
    Write-Host "             Fix: add `EAutomationTestFlags::CommandletContext` to every IMPLEMENT_SIMPLE_AUTOMATION_TEST."
    Write-Host "             Canonical mask: EditorContext | CommandletContext | EngineFilter."
    Write-Host "             Full log: $LogPath"
    exit 1
}

# Parse per-test outcomes. UE's ATF emits one `Test Started` /
# `Test Complete` pair per test under LogAutomationController. On
# failure, `LogAutomationController: Error:` lines precede the Complete
# marker. Final summary is `LogAutomationController: ...Passed: X / Failed: Y`.
$started   = [regex]::Matches($logContent, 'LogAutomationController.*BeginningTest|Test Started:').Count
$failed    = [regex]::Matches($logContent, 'LogAutomationController:\s*Error:|Test Failed:|Automation Test Failed').Count
$succeeded = [regex]::Matches($logContent, 'Test Completed\. Result=\{Success\}|Automation Test Succeeded').Count

# Match the summary line if UE emitted one. Format varies across engine
# revisions; pattern is resilient.
$summaryMatch = [regex]::Match(
    $logContent,
    'LogAutomation(?:Controller)?:\s*Display:\s*.*?(?:Passed|Succeeded):\s*(?<pass>\d+)\s*.*?(?:Failed):\s*(?<fail>\d+)',
    'Singleline'
)

Write-Host ""
Write-Host "[automation] Started:   $started"
Write-Host "[automation] Succeeded: $succeeded"
Write-Host "[automation] Failed:    $failed"
if ($summaryMatch.Success) {
    Write-Host ("[automation] ATF summary: Pass={0} Fail={1}" -f $summaryMatch.Groups['pass'].Value, $summaryMatch.Groups['fail'].Value)
}

# No tests observed at all? Something is wrong with discovery even though the
# CommandletContext flag is set. Could be a bad filter, missing plugin, or
# plugin loaded but tests not registered. Flag loudly.
if ($started -eq 0 -and $succeeded -eq 0) {
    Write-Host ""
    Write-Host "[automation] FAIL -- zero tests observed in the run." -ForegroundColor Red
    Write-Host "             Filter=$Filter matched nothing. Check plugin load and test registration."
    Write-Host "             Full log: $LogPath"
    exit 1
}

if ($failed -gt 0) {
    Write-Host ""
    Write-Host "[automation] FAIL -- $failed test(s) reported failure." -ForegroundColor Red
    Write-Host "             Grep the log for 'LogAutomationController:\s*Error:' / 'Test Failed:' lines."
    Write-Host "             Full log: $LogPath"
    exit 1
}

Write-Host ""
Write-Host "[automation] PASS -- $succeeded test(s) passed, 0 failed." -ForegroundColor Green
exit 0
