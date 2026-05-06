#requires -Version 5
<#
.SYNOPSIS
    M28.pre.2 -- post-apply content inspection gate.

.DESCRIPTION
    For a given write-side op, verifies that applying it via the plan
    pipeline actually produces the expected authored content in the
    re-exported .md / .deep.md sidecars. Closes the "did the mutation
    surface post-re-export" correctness gap that the determinism gate
    (byte-stability only) doesn't cover.

    Flow (three UE shells + local regex match):
      1. inspect_harness.py --mode=prepare    — duplicate fixture,
                                                apply op via run_plan,
                                                write <json>.prepare.json
      2. ProjectInventory -Filter -DeepDump   — re-export scratch asset's
                                                .md / .meta.json / .deep.md
                                                into scratch inventory dir
      3. local: regex match the sidecars against expected_md /
                not_expected_md / expected_deep / not_expected_deep
      4. inspect_harness.py --mode=cleanup    — file-level remove
                                                scratch asset

    Exit 0 iff every expected_* regex matches AND every not_expected_*
    regex misses. Non-zero on prepare failure, re-export failure, any
    assertion miss, or driver error.

.PARAMETER Assertions
    Path to the assertions JSON (see inspect_harness.py docstring for the
    full shape; scripts/inspect_fixtures/*.json are the committed examples).

.PARAMETER Project
    BugHunt (default) or DOW. Scratch path and source_fixture must be
    resolvable in whichever project is chosen; BugHunt fixtures live
    under /Game/TestBlueprints/.

.PARAMETER Engine
    Override UnrealEditor-Cmd.exe path. Default is the custom UE_DOW
    engine. For BugHunt you typically want stock 5.7 via -Engine override.

.PARAMETER ProjectFile
    Override .uproject path. Default is project-specific.

.PARAMETER KeepScratch
    Skip the cleanup shell. Useful when diagnosing a failing assertion;
    the re-exported .md / .deep.md stay on disk for manual inspection.

.EXAMPLE
    pwsh -File scripts/verify_post_apply_inspect.ps1 `
         -Assertions scripts/inspect_fixtures/implement_interface_function.json `
         -Project BugHunt `
         -Engine 'C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe'

.NOTES
    M28.pre.2 (2026-04-23) -- added as the correctness gate for every
    M28 write-side op. Each new op ships with an instance of
    scripts/inspect_fixtures/<op_name>.json and CI runs this wrapper
    against it on every push touching python_ops/ or ReflectionOps.cpp.
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string]$Assertions,

    [ValidateSet('BugHunt', 'DOW')]
    [string]$Project = 'BugHunt',

    [string]$Engine = 'D:\Work\UE_DOW\engine\Binaries\Win64\UnrealEditor-Cmd.exe',

    [string]$ProjectFile,

    [switch]$KeepScratch
)

$ErrorActionPreference = 'Stop'
$RepoRoot = Split-Path -Parent $PSScriptRoot

if (-not (Test-Path -LiteralPath $Assertions -PathType Leaf)) {
    Write-Error "Assertions JSON not found: $Assertions"
    exit 2
}

$cfg = Get-Content -LiteralPath $Assertions -Raw | ConvertFrom-Json
foreach ($key in 'op','source_fixture','scratch_path','plan_kwargs','inspect_path') {
    if (-not $cfg.PSObject.Properties.Match($key)) {
        Write-Error "Assertions JSON missing required key: $key"
        exit 2
    }
}

if (-not $ProjectFile) {
    $ProjectFile = switch ($Project) {
        'BugHunt' { Join-Path $RepoRoot 'BugHunt\TestProject\BugHunt.uproject' }
        'DOW'     { 'D:\Work\UE_DOW\game\UE_DOW.uproject' }
    }
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

$InspectScriptPath = Join-Path $PSScriptRoot 'inspect_harness.py'
if (-not (Test-Path -LiteralPath $InspectScriptPath)) {
    Write-Error "inspect_harness.py not found at $InspectScriptPath"
    exit 2
}

$stamp = Get-Date -Format 'yyyyMMdd_HHmmss'
$ScratchInvDir = Join-Path $env:TEMP "bpx_inspect\${stamp}"
$LogDir        = Join-Path $env:TEMP "bpx_inspect\${stamp}_logs"
New-Item -ItemType Directory -Path $ScratchInvDir -Force | Out-Null
New-Item -ItemType Directory -Path $LogDir        -Force | Out-Null

Write-Host "[inspect] Op=$($cfg.op)"
Write-Host "[inspect] Assertions=$Assertions"
Write-Host "[inspect] Source=$($cfg.source_fixture)"
Write-Host "[inspect] Scratch=$($cfg.scratch_path)"
Write-Host "[inspect] Inventory scratch=$ScratchInvDir"

function Invoke-UE {
    param(
        [string[]]$ExtraCliArgs,
        [string]$Phase,
        [int]$TimeoutSec = 300
    )
    $logPath = Join-Path $LogDir "${Phase}.log"
    $argsList = @(
        "`"$ProjectFile`""
    ) + $ExtraCliArgs + $ExtraArgs + @(
        '-unattended'
        '-nopause'
        '-nullrhi'
        '-nosplash'
        '-nosound'
        '-log'
    )
    Write-Host "[inspect] Phase=$Phase -> log $logPath"
    $proc = Start-Process -FilePath $Engine -ArgumentList $argsList `
        -NoNewWindow -Wait -PassThru `
        -RedirectStandardOutput $logPath -RedirectStandardError "$logPath.err"
    return @{ ExitCode = $proc.ExitCode; Log = $logPath }
}

# ---------- Phase 1: prepare (duplicate + apply) ----------
$assertionsAbs = (Resolve-Path -LiteralPath $Assertions).Path

# The harness writes its prepare report to $env:BPX_INSPECT_TMP (or the
# default under %TEMP%\bpx_inspect) using basename(assertions) +
# ".prepare.json". We pin a per-run tmp dir so the path is deterministic
# here even when the driver runs multiple gates concurrently.
$PrepareTmpRoot = Join-Path $env:TEMP "bpx_inspect\prepare_${stamp}"
New-Item -ItemType Directory -Path $PrepareTmpRoot -Force | Out-Null
$env:BPX_INSPECT_TMP = $PrepareTmpRoot

$prepare = Invoke-UE -Phase 'prepare' -ExtraCliArgs @(
    '-run=pythonscript'
    "-script=`"$InspectScriptPath`""
    '-mode=prepare'
    "-assertions=`"$assertionsAbs`""
)

if ($prepare.ExitCode -ge 2) {
    Write-Host "[inspect] FAIL -- prepare phase exited $($prepare.ExitCode). Log: $($prepare.Log)" -ForegroundColor Red
    exit 1
}

$prepareReport = Join-Path $PrepareTmpRoot ((Split-Path -Leaf $assertionsAbs) + '.prepare.json')
if (-not (Test-Path -LiteralPath $prepareReport)) {
    Write-Host "[inspect] FAIL -- prepare phase did not write $prepareReport. Log: $($prepare.Log)" -ForegroundColor Red
    exit 1
}
$prepareData = Get-Content -LiteralPath $prepareReport -Raw | ConvertFrom-Json
if (-not $prepareData.passed) {
    Write-Host "[inspect] FAIL -- run_plan returned passed=false in prepare phase." -ForegroundColor Red
    Write-Host "           Full prepare report: $prepareReport"
    Write-Host "           Plan execution log: $($prepare.Log)"
    exit 1
}
Write-Host "[inspect] Prepare OK. Scratch md5 = $($prepareData.scratch_md5)"

# ---------- Phase 2: re-export via ProjectInventory + DeepDump ----------
# Scope to the inspect_path's parent directory so the Filter matches exactly
# the one asset. ProjectInventory's -Filter takes a /Game/... prefix.
$inspectPath = $cfg.inspect_path
$filterPrefix = $inspectPath  # exact prefix is fine for a single-asset scope

$reexport = Invoke-UE -Phase 'reexport' -ExtraCliArgs @(
    '-run=ProjectInventory'
    "-OutDir=`"$ScratchInvDir`""
    "-Filter=$filterPrefix"
    '-DeepDump'
)

if ($reexport.ExitCode -ge 2) {
    Write-Host "[inspect] FAIL -- re-export phase exited $($reexport.ExitCode). Log: $($reexport.Log)" -ForegroundColor Red
    exit 1
}

# Locate the re-exported sidecars. ProjectInventory writes to
# <OutDir>/Assets/Game/<path-relative-to-/Game>/<AssetName>.(md|meta.json|deep.md).
# The scratch asset at /Game/X/Y/Z lands at <OutDir>/Assets/Game/X/Y/Z.md etc.
# (The "Game" component is preserved from the /Game/ root — ProjectInventory
# mirrors the package-path structure under Assets/ rather than flattening it.)
$relPath = $inspectPath -replace '^/Game/', 'Assets/Game/'
$mdPath   = Join-Path $ScratchInvDir ("$relPath.md")
$deepPath = Join-Path $ScratchInvDir ("$relPath.deep.md")

if (-not (Test-Path -LiteralPath $mdPath)) {
    Write-Host "[inspect] FAIL -- expected .md not found at $mdPath" -ForegroundColor Red
    Write-Host "           Tree under ${ScratchInvDir}:"
    Get-ChildItem -Path $ScratchInvDir -Recurse -ErrorAction SilentlyContinue |
        Select-Object -First 20 | ForEach-Object { Write-Host "             $($_.FullName)" }
    exit 1
}
$mdContent = Get-Content -LiteralPath $mdPath -Raw
$deepContent = if (Test-Path -LiteralPath $deepPath) {
    Get-Content -LiteralPath $deepPath -Raw
} else { '' }

# ---------- Phase 3: regex match ----------
$misses = @()
function Check-Expected {
    param([string]$Content, [string[]]$Patterns, [string]$Source, [bool]$ShouldMatch)
    foreach ($pat in $Patterns) {
        $matched = [regex]::IsMatch($Content, $pat)
        if ($ShouldMatch -and -not $matched) {
            $script:misses += "[${Source}] expected pattern MISSED: $pat"
        } elseif (-not $ShouldMatch -and $matched) {
            $script:misses += "[${Source}] not_expected pattern HIT (should not): $pat"
        }
    }
}

$expectedMd     = @($cfg.expected_md      | Where-Object { $_ })
$notExpectedMd  = @($cfg.not_expected_md  | Where-Object { $_ })
$expectedDeep   = @($cfg.expected_deep    | Where-Object { $_ })
$notExpectedDeep= @($cfg.not_expected_deep| Where-Object { $_ })

Check-Expected -Content $mdContent   -Patterns $expectedMd      -Source '.md'      -ShouldMatch $true
Check-Expected -Content $mdContent   -Patterns $notExpectedMd   -Source '.md'      -ShouldMatch $false
Check-Expected -Content $deepContent -Patterns $expectedDeep    -Source '.deep.md' -ShouldMatch $true
Check-Expected -Content $deepContent -Patterns $notExpectedDeep -Source '.deep.md' -ShouldMatch $false

Write-Host ""
Write-Host "[inspect] Sidecars:"
Write-Host "           .md      = $mdPath"
Write-Host "           .deep.md = $deepPath"
Write-Host "[inspect] Patterns:"
Write-Host "           expected_md      : $($expectedMd.Count)"
Write-Host "           not_expected_md  : $($notExpectedMd.Count)"
Write-Host "           expected_deep    : $($expectedDeep.Count)"
Write-Host "           not_expected_deep: $($notExpectedDeep.Count)"

# ---------- Phase 4: cleanup ----------
if (-not $KeepScratch) {
    $cleanup = Invoke-UE -Phase 'cleanup' -ExtraCliArgs @(
        '-run=pythonscript'
        "-script=`"$InspectScriptPath`""
        '-mode=cleanup'
        "-assertions=`"$assertionsAbs`""
    )
    if ($cleanup.ExitCode -ge 2) {
        Write-Host "[inspect] WARN -- cleanup phase exited $($cleanup.ExitCode). Scratch asset may remain." -ForegroundColor Yellow
        Write-Host "           Cleanup log: $($cleanup.Log)"
    } else {
        Write-Host "[inspect] Cleanup OK."
    }
    Remove-Item -LiteralPath $ScratchInvDir -Recurse -Force -ErrorAction SilentlyContinue
} else {
    Write-Host "[inspect] KeepScratch set; scratch asset preserved at $($cfg.scratch_path), inventory at $ScratchInvDir"
}

# ---------- Final verdict ----------
if ($misses.Count -eq 0) {
    Write-Host ""
    Write-Host "[inspect] PASS -- every expected pattern matched, every not_expected missed." -ForegroundColor Green
    exit 0
}

Write-Host ""
Write-Host "[inspect] FAIL -- $($misses.Count) assertion(s) failed:" -ForegroundColor Red
foreach ($miss in $misses) {
    Write-Host "           $miss" -ForegroundColor Red
}
Write-Host ""
Write-Host "           Sidecars at:"
Write-Host "             .md      = $mdPath"
Write-Host "             .deep.md = $deepPath"
Write-Host "           (pass -KeepScratch to preserve them across runs)"
exit 1
