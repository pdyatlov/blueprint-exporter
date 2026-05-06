#requires -Version 5
<#
.SYNOPSIS
    M28.pre.3 -- per-op determinism soak gate.

.DESCRIPTION
    Shells UnrealEditor-Cmd.exe with scripts/soak_template.py against the
    supplied assertions JSON. Single UE shell. Soak harness applies the op
    N rounds (default 2), duplicated from a baseline fixture each time,
    asserts every round produces byte-identical .uasset md5 AND any fields
    declared in soak.stable_keys agree across rounds.

    Catches exactly the bug class M26.1.2 surfaced (pin-GUID randomness,
    GC counter drift, MakeUniqueObjectName suffix monotonicity). Every M28
    write op ships with an assertions JSON instance; this wrapper is how
    CI invokes them.

.PARAMETER Assertions
    Path to the assertions JSON. Same shape as scripts/inspect_fixtures/*.json;
    soak.rounds / soak.stable_keys / soak.round2_min_wiped_nodes are the
    soak-specific extensions.

.PARAMETER Project / Engine / ProjectFile
    Same semantics as scripts/verify_post_apply_inspect.ps1.

.EXAMPLE
    pwsh -File scripts/verify_soak.ps1 `
         -Assertions scripts/inspect_fixtures/implement_interface_function.json `
         -Project BugHunt `
         -Engine 'C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe'

.NOTES
    M28.pre.3 (2026-04-23). Same-file JSON fixtures across post-apply-inspect
    and soak gates; one fixture per op authors both checks.
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string]$Assertions,

    [ValidateSet('BugHunt', 'DOW')]
    [string]$Project = 'BugHunt',

    [string]$Engine = 'D:\Work\UE_DOW\engine\Binaries\Win64\UnrealEditor-Cmd.exe',

    [string]$ProjectFile
)

$ErrorActionPreference = 'Stop'
$RepoRoot = Split-Path -Parent $PSScriptRoot

if (-not (Test-Path -LiteralPath $Assertions -PathType Leaf)) {
    Write-Error "Assertions JSON not found: $Assertions"
    exit 2
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

$SoakScript = Join-Path $PSScriptRoot 'soak_template.py'
if (-not (Test-Path -LiteralPath $SoakScript)) {
    Write-Error "soak_template.py not found at $SoakScript"
    exit 2
}

$ExtraArgs = switch ($Project) {
    'BugHunt' { @() }
    'DOW'     { @('-EnablePlugins=BlueprintExporter') }
}

$stamp = Get-Date -Format 'yyyyMMdd_HHmmss'
$tempDir = Join-Path $env:TEMP 'bpx_soak'
if (-not (Test-Path -LiteralPath $tempDir)) {
    New-Item -ItemType Directory -Path $tempDir | Out-Null
}
$LogPath = Join-Path $tempDir "soak_${stamp}.log"
$assertionsAbs = (Resolve-Path -LiteralPath $Assertions).Path

$argsList = @(
    "`"$ProjectFile`""
    '-run=pythonscript'
    "-script=`"$SoakScript`""
    "-assertions=`"$assertionsAbs`""
) + $ExtraArgs + @(
    '-unattended'
    '-nopause'
    '-nullrhi'
    '-nosplash'
    '-nosound'
    '-log'
)

Write-Host "[soak] Assertions=$Assertions"
Write-Host "[soak] Project=$Project"
Write-Host "[soak] Log=$LogPath"
Write-Host "[soak] Running..."

$start = Get-Date
$proc = Start-Process -FilePath $Engine -ArgumentList $argsList `
    -NoNewWindow -Wait -PassThru `
    -RedirectStandardOutput $LogPath -RedirectStandardError "$LogPath.err"
$elapsed = (Get-Date) - $start

Write-Host ("[soak] UE exited after {0:N1}s, exit code = {1}." -f $elapsed.TotalSeconds, $proc.ExitCode)

# UE stdout capture on Windows is unreliable AND can be partial (see M27.2
# pipe-deadlock arc): the log file may be non-empty but still missing the
# LogPython lines that carry our SOAK PASS / FAIL markers. Prefer
# Saved/Logs/<Project>.log when available -- it's the full engine log and
# is authoritative.
$projectDir  = Split-Path -Parent $ProjectFile
$projectName = [IO.Path]::GetFileNameWithoutExtension($ProjectFile)
$fallback    = Join-Path $projectDir "Saved\Logs\${projectName}.log"
$logContent  = ''
if (Test-Path -LiteralPath $fallback) {
    $logContent = Get-Content -LiteralPath $fallback -Raw
    Copy-Item -LiteralPath $fallback -Destination $LogPath -Force
} elseif ((Test-Path -LiteralPath $LogPath) -and ((Get-Item -LiteralPath $LogPath).Length -gt 0)) {
    $logContent = Get-Content -LiteralPath $LogPath -Raw
}

# The soak harness emits `[m28.pre.3-soak] SOAK PASS` or `[m28.pre.3-soak]
# FAIL: ...` with an explicit SystemExit(1). UE commandlet translates that
# to a non-zero exit code, but we also re-check the log pattern in case
# another subsystem clobbered the exit code on shutdown.
$passMatch = [regex]::IsMatch($logContent, '\[m28\.pre\.3-soak\] SOAK PASS')
$failMatch = [regex]::IsMatch($logContent, '\[m28\.pre\.3-soak\] FAIL:')

if ($failMatch -or ($proc.ExitCode -ge 2)) {
    Write-Host ""
    Write-Host "[soak] FAIL -- soak assertion(s) tripped." -ForegroundColor Red
    Write-Host "        Tail of the log:"
    $logContent -split "`n" | Select-String -Pattern '\[m28\.pre\.3-soak\]' |
        Select-Object -Last 12 | ForEach-Object { Write-Host "          $_" }
    Write-Host "        Full log: $LogPath"
    exit 1
}

if (-not $passMatch) {
    Write-Host ""
    Write-Host "[soak] FAIL -- soak did not emit SOAK PASS and did not emit a FAIL line either." -ForegroundColor Red
    Write-Host "        Most likely the UE shell died before the harness ran. Log: $LogPath"
    exit 1
}

Write-Host ""
Write-Host "[soak] PASS -- byte-identical across all rounds." -ForegroundColor Green
# Echo the stable-md5 line so CI captures it in the build log.
$logContent -split "`n" |
    Select-String -Pattern '\[m28\.pre\.3-soak\]\s+(md5 \(stable\)|rounds|stable_keys|r2 wiped)' |
    ForEach-Object { Write-Host "        $_" }
exit 0
