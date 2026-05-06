#requires -Version 5
<#
.SYNOPSIS
    Determinism CI gate for the Project Inventory pipeline (brief §11A).

.DESCRIPTION
    Runs ProjectManifest, ProjectInventory, AggregateInventory, ProjectPlugins, and DeepDump
    twice against the same project state — once into $OutA, once into $OutB —
    then diffs the two trees with `git diff --no-index`. Exit 0 iff the trees
    are byte-identical.

    Invariant under test: same input CL -> byte-identical output across runs
    (brief §8, exercised by hand after every milestone). Codifying the check
    here prevents regressions and makes a failing diff immediately actionable
    (the script emits the unified diff on failure).

.PARAMETER Project
    Which project to exercise. "BugHunt" (committed fixtures in
    blueprint-exporter/BugHunt/TestProject), "DOW" (the studio project at
    D:\Work\UE_DOW\game), or "MutableSample" (M29.4 — the Mutable demo
    project at D:\Work\mutable\MutableSample, used as an ad-hoc fixture
    for the M29 Mutable / CustomizableObject Tier 2 renderer chain; NOT
    in the default regression rotation since enabling Mutable on BugHunt
    would triple its build weight).

.PARAMETER OutA
    Output dir for the first run. Defaults to a sibling of the repo root named
    `_determinism_A`. Cleaned before run unless `-KeepOnSuccess` is set AND
    the previous run succeeded.

.PARAMETER OutB
    Output dir for the second run. Defaults to `_determinism_B`.

.PARAMETER Filter
    Passed through to ProjectInventory `-Filter=`. Useful for slicing a large
    project like DOW (e.g. `/Game/_ThirdParty/GASP_example/`) rather than
    running the full 18k-asset pass under a CI gate.

.PARAMETER DeepAsset
    Package path of the asset to DeepDump. Defaults to
    `/Game/TestBlueprints/BP_NetRep` for BugHunt and is required for DOW
    (no sensible default across DOW content).

.PARAMETER SkipDeep
    Skip the DeepDump step. Useful when DOW is on a workstation without the
    M5 DLL yet, or when you only care about the Phase 0/1/2 pipeline.

.PARAMETER SweepDeepDump
    Enable the Tier 2 sweep: passes `-DeepDump` to ProjectInventory so every
    processed asset emits a `<Path>.deep.md` sibling next to its `<Path>.md`.
    The deep output is picked up by the diff automatically, catching sweep-
    path non-determinism that the single-asset DeepDump phase would miss.

    Supersedes the single-asset DeepDump phase (it's redundant when every
    asset is already deep-dumped by the sweep), so that phase is skipped
    when this switch is set.

    Opt-in because sweep output grows with project size — a full DOW sweep
    is ~5-10 MB of Tier 2 output and takes ~3-5 min. BugHunt is cheap; DOW
    slices via `-Filter` are cheap. A full-DOW `-SweepDeepDump` is slow
    enough that it should stay a manual pre-merge check, not a CI gate.

.PARAMETER KeepOnSuccess
    Do not delete $OutA and $OutB after a successful run. Default is to clean
    up so the repo doesn't accumulate gigabytes of ephemeral inventory output.
    On failure, both dirs are always kept so the diff can be re-inspected.

.PARAMETER Engine
    Override the engine exe path. Default:
    `D:\Work\UE_DOW\engine\Binaries\Win64\UnrealEditor-Cmd.exe`.

.PARAMETER ProjectFile
    Override the .uproject path. Default is project-specific:
    BugHunt       -> blueprint-exporter/BugHunt/TestProject/BugHunt.uproject
    DOW           -> D:/Work/UE_DOW/game/UE_DOW.uproject
    MutableSample -> D:/Work/mutable/MutableSample/MutableSample.uproject

.EXAMPLE
    .\scripts\verify_determinism.ps1 -Project BugHunt

    Full pipeline twin run against the BugHunt fixture set. Uses BP_NetRep
    for the DeepDump sample.

.EXAMPLE
    .\scripts\verify_determinism.ps1 -Project DOW -Filter /Game/_ThirdParty/GASP_example/ -DeepAsset /Game/_ThirdParty/GASP_example/Animation/PSD_SM_CMC_Idles -KeepOnSuccess

    Same-CL determinism check against DOW's Motion Matching slice, keeping
    both output trees on disk for inspection.

.EXAMPLE
    .\scripts\verify_determinism.ps1 -Project MutableSample -SweepDeepDump

    M29.4 — full-sweep Tier 2 twin-run across the MutableSample Mutable
    slice (CO_* + COI_* + COML_*). Requires MutableSample's game module
    rebuilt against UE_DOW (BuildId 6efc257b-...); the stock-5.7-shipped
    MutableSample.dll errors with "The game module 'MutableSample' could
    not be found". Use `Build.bat MutableSampleEditor Win64 Development
    -Project=D:\Work\mutable\MutableSample\MutableSample.uproject` once
    per UE_DOW rebuild to produce a matching BuildId (~22 s warm cache).
    Cheapest deep-dump single-asset default if you're NOT using
    -SweepDeepDump: `/Game/Weapon/CO_Weapon` (the smallest UCO in the
    project at ~42 KB `.deep.md`).

.EXAMPLE
    $LASTEXITCODE
    0   # byte-identical
    1   # at least one file differed; unified diff printed above

.NOTES
    Intended to run from a PowerShell or cmd.exe shell. Running via Git Bash
    / MSYS2 mangles `/Game/...` arguments (the `-Filter` and `-DeepAsset`
    package paths) into `C:/Program Files/Git/Game/...` unless you prefix
    the invocation with `MSYS_NO_PATHCONV=1`. The commandlets themselves have
    defensive checks for the mangled form but the simplest fix is to avoid
    the bash layer for this script.
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [ValidateSet('BugHunt', 'DOW', 'MutableSample')]
    [string]$Project,

    [string]$OutA,
    [string]$OutB,
    [string]$Filter,
    [string]$DeepAsset,
    [switch]$SkipDeep,
    [switch]$SweepDeepDump,
    [switch]$KeepOnSuccess,
    [string]$Engine = 'D:\Work\UE_DOW\engine\Binaries\Win64\UnrealEditor-Cmd.exe',
    [string]$ProjectFile
)

$ErrorActionPreference = 'Stop'
$RepoRoot = Split-Path -Parent $PSScriptRoot  # .../blueprint-exporter

# ---------- Resolve project-specific defaults ----------

if (-not $ProjectFile) {
    $ProjectFile = switch ($Project) {
        'BugHunt'       { Join-Path $RepoRoot 'BugHunt\TestProject\BugHunt.uproject' }
        'DOW'           { 'D:\Work\UE_DOW\game\UE_DOW.uproject' }
        'MutableSample' { 'D:\Work\mutable\MutableSample\MutableSample.uproject' }
    }
}

if (-not $OutA) { $OutA = Join-Path $RepoRoot "_determinism_A" }
if (-not $OutB) { $OutB = Join-Path $RepoRoot "_determinism_B" }

if (-not $DeepAsset -and -not $SkipDeep -and -not $SweepDeepDump) {
    $DeepAsset = switch ($Project) {
        'BugHunt'       { '/Game/TestBlueprints/BP_NetRep' }
        'DOW'           { $null }
        'MutableSample' { '/Game/Weapon/CO_Weapon' }
    }
    if (-not $DeepAsset) {
        throw "-DeepAsset is required when -Project=DOW (no default across DOW content). Pass -SkipDeep or -SweepDeepDump to bypass."
    }
}

# DOW's uproject pins BlueprintExporter as disabled; MutableSample's uproject
# doesn't list BlueprintExporter at all (we mount it via a junction pointing
# at BuiltPlugin/ so plugin discovery picks it up, but -EnablePlugins is
# belt-and-braces). BugHunt lists the plugin as enabled already.
$ExtraArgs = switch ($Project) {
    'BugHunt'       { @() }
    'DOW'           { @('-EnablePlugins=BlueprintExporter') }
    'MutableSample' { @('-EnablePlugins=BlueprintExporter') }
}

# ---------- Pre-flight ----------

if (-not (Test-Path -LiteralPath $Engine -PathType Leaf)) {
    throw "Engine exe not found: $Engine"
}
if (-not (Test-Path -LiteralPath $ProjectFile -PathType Leaf)) {
    throw "Project file not found: $ProjectFile"
}

function New-CleanDir([string]$Path) {
    if (Test-Path -LiteralPath $Path) {
        Remove-Item -LiteralPath $Path -Recurse -Force
    }
    New-Item -ItemType Directory -Path $Path | Out-Null
}

function Invoke-Commandlet {
    param(
        [string]$Run,
        [string[]]$AdditionalArgs,
        [string]$OutDir,
        [string]$LogPath
    )

    $argsList = @(
        "`"$ProjectFile`""
        "-run=$Run"
        "-OutDir=`"$OutDir`""
    ) + $ExtraArgs + $AdditionalArgs + @(
        '-nullrhi'
        '-unattended'
        '-nopause'
        '-nosplash'
        '-nosound'
        '-stdout'
        '-log'
    )

    Write-Host "  [verify] $Run -> $OutDir"
    $proc = Start-Process -FilePath $Engine -ArgumentList $argsList `
        -NoNewWindow -Wait -PassThru `
        -RedirectStandardOutput $LogPath -RedirectStandardError "$LogPath.err"

    # Exit 1 from UE-Cmd is benign on this codebase — the ProjectID config
    # warning lives in the Warning/Error Summary and inflates the exit code.
    # Treat 0 and 1 as "framework ran"; 2+ is an actual commandlet error.
    if ($proc.ExitCode -ge 2) {
        Write-Error "Commandlet $Run failed with exit $($proc.ExitCode). Log: $LogPath"
        throw "Commandlet failure"
    }

    # Confirm the commandlet itself reported success via [STATUS] SUCCESS.
    $statusLine = Select-String -LiteralPath $LogPath -Pattern '\[STATUS\] SUCCESS' -SimpleMatch:$false -ErrorAction SilentlyContinue
    if (-not $statusLine) {
        Write-Error "Commandlet $Run did not report [STATUS] SUCCESS. Log: $LogPath"
        throw "Commandlet status missing"
    }
}

function Invoke-Pipeline {
    param([string]$OutDir, [string]$LogDir, [string]$Label)

    Write-Host "[verify] Run ${Label}: OutDir=$OutDir LogDir=$LogDir"
    New-CleanDir $OutDir
    New-CleanDir $LogDir

    # Phase 0 -- ProjectManifest
    Invoke-Commandlet -Run 'ProjectManifest' -AdditionalArgs @() -OutDir $OutDir `
        -LogPath (Join-Path $LogDir 'manifest.log')

    # Phase 1 -- ProjectInventory (optional filter + optional deep-dump sweep)
    $inventoryArgs = @()
    if ($Filter) { $inventoryArgs += "-Filter=$Filter" }
    if ($SweepDeepDump) { $inventoryArgs += '-DeepDump' }
    Invoke-Commandlet -Run 'ProjectInventory' -AdditionalArgs $inventoryArgs -OutDir $OutDir `
        -LogPath (Join-Path $LogDir 'inventory.log')

    # Phase 2 -- AggregateInventory (reads $OutDir/Assets, writes rollups into $OutDir)
    Invoke-Commandlet -Run 'AggregateInventory' -AdditionalArgs @() -OutDir $OutDir `
        -LogPath (Join-Path $LogDir 'aggregate.log')

    # Phase Plugins (M7 P0) -- ProjectPlugins writes PLUGINS.md + PluginInventory/
    # sidecars into $OutDir. Always run; cheap (<1s), and detects plugin-graph
    # non-determinism (e.g. if `FPluginDescriptor::Modules` iteration order
    # starts drifting).
    Invoke-Commandlet -Run 'ProjectPlugins' -AdditionalArgs @() -OutDir $OutDir `
        -LogPath (Join-Path $LogDir 'plugins.log')

    # Optional DeepDump -- single asset into a Deep/ subdir so the Phase 2 tree
    # doesn't get mixed in with the deep dump sidecar files.
    # Skipped when -SweepDeepDump is set: the Phase 1 sweep already emits a
    # .deep.md per asset, so the single-asset run would be redundant.
    if ((-not $SkipDeep) -and (-not $SweepDeepDump)) {
        $deepOut = Join-Path $OutDir 'Deep'
        New-Item -ItemType Directory -Path $deepOut | Out-Null
        Invoke-Commandlet -Run 'DeepDump' `
            -AdditionalArgs @("-Asset=$DeepAsset") -OutDir $deepOut `
            -LogPath (Join-Path $LogDir 'deepdump.log')
    }
}

# ---------- Run both ----------

# Logs live in sibling directories so the diff compares pure inventory output.
# Commandlet stdout carries timestamps and would otherwise fail the check by
# design. `git diff --no-index` does not honour pathspec excludes, so
# structural separation is the reliable answer.
$LogsA = "${OutA}_logs"
$LogsB = "${OutB}_logs"

$start = Get-Date
Invoke-Pipeline -OutDir $OutA -LogDir $LogsA -Label 'A'
Invoke-Pipeline -OutDir $OutB -LogDir $LogsB -Label 'B'
$elapsed = (Get-Date) - $start

Write-Host ""
Write-Host ("[verify] Both runs complete in {0}s. Diffing..." -f [int]$elapsed.TotalSeconds)

# ---------- Diff ----------

# Bypass gitattributes CRLF rules -- we want byte-identical, not "identical
# after line-ending normalization". Without these, git emits "CRLF will be
# replaced by LF" warnings that PowerShell's Stop ErrorActionPreference
# escalates into terminating errors.
$diffArgs = @(
    '-c'; 'core.autocrlf=false'
    '-c'; 'core.safecrlf=false'
    '--no-pager'
    'diff'
    '--no-index'
    '--stat'
    '--'
    $OutA
    $OutB
)

# `git diff --no-index` returns 0 on identical, 1 on diff. Any other exit code
# is a git-side failure (e.g. path not found), which we want to surface.
# Temporarily relax ErrorActionPreference so git warnings on stderr don't
# throw; $LASTEXITCODE is the load-bearing signal here.
$prevEap = $ErrorActionPreference
$ErrorActionPreference = 'Continue'
$diffOut = & git @diffArgs 2>&1
$diffExit = $LASTEXITCODE
$ErrorActionPreference = $prevEap

if ($diffExit -eq 0) {
    Write-Host "[verify] PASS -- both output trees are byte-identical." -ForegroundColor Green
    if (-not $KeepOnSuccess) {
        Remove-Item -LiteralPath $OutA  -Recurse -Force
        Remove-Item -LiteralPath $OutB  -Recurse -Force
        Remove-Item -LiteralPath $LogsA -Recurse -Force
        Remove-Item -LiteralPath $LogsB -Recurse -Force
        Write-Host ("[verify] Cleaned up {0}, {1}, and per-run logs." -f $OutA, $OutB)
    } else {
        Write-Host ("[verify] KeepOnSuccess set; output trees at {0}, {1}; logs at {2}, {3}." `
            -f $OutA, $OutB, $LogsA, $LogsB)
    }
    exit 0
}

if ($diffExit -eq 1) {
    $diffFile = "${OutA}.diff"
    Write-Host "[verify] FAIL -- outputs differ between runs." -ForegroundColor Red
    Write-Host "        Stat summary:"
    $diffOut | ForEach-Object { Write-Host ("          " + $_) }
    Write-Host ""
    Write-Host ("        Full unified diff saved at: {0}" -f $diffFile)
    $fullDiffArgs = @(
        '-c'; 'core.autocrlf=false'
        '-c'; 'core.safecrlf=false'
        '--no-pager'
        'diff'
        '--no-index'
        '--'
        $OutA
        $OutB
    )
    $prevEap = $ErrorActionPreference
    $ErrorActionPreference = 'Continue'
    & git @fullDiffArgs > $diffFile 2>&1
    $ErrorActionPreference = $prevEap
    Write-Host ("        Output trees preserved at {0} and {1} for inspection." -f $OutA, $OutB)
    Write-Host ("        Per-run logs at {0}, {1}." -f $LogsA, $LogsB)
    exit 1
}

Write-Host ("[verify] ERROR -- git diff exited with code {0}." -f $diffExit) -ForegroundColor Red
$diffOut | ForEach-Object { Write-Host ("          " + $_) }
exit $diffExit
