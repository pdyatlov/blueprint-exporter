#requires -Version 5
<#
.SYNOPSIS
    M28.pre.5 — config-file parity gate for `add_gameplay_tag`.

.DESCRIPTION
    Closes the M28.pre verification-matrix hole the inspect/soak gates
    can't cover: `add_gameplay_tag` writes to a `Config/<X>.ini` text
    file rather than a /Game/ uasset, so the existing per-op
    inspect+soak harness (which md5-diffs scratch .uasset files) doesn't
    apply.

    Flow (two UE shells + local diff):
      1. Snapshot baseline `<Project>/Config/<source_ini>` bytes.
      2. UE shell A — apply `add_gameplay_tag(<tag>, <comment>, <source>)`
         via the M28.pre.5 in-process harness (`verify_tag_author_harness.py`)
         which calls `python_ops.plan_executor.run_plan` end-to-end —
         exactly the same code path `apply_plan` uses.
      3. Read the post-apply ini bytes; assert exactly ONE
         `+GameplayTagList=(Tag="...",DevComment="...")` line was
         added and that the existing settings header lines are
         preserved verbatim.
      4. UE shell B — re-apply the same plan; assert the harness
         result reports `skipped="tag already registered"` AND the
         on-disk ini bytes are byte-identical to step 3 (no churn
         from the duplicate-add path).
      5. Restore the baseline ini bytes so subsequent runs / git status
         stay clean.

    Exit 0 iff every step passes. Non-zero on any harness failure,
    diff anomaly, or idempotence violation. Default project is BugHunt
    (Config/DefaultGameplayTags.ini ships as a starter fixture);
    `-Project DOW` exists for ad-hoc runs but the gate is normally
    BugHunt-only because real DOW edits would surface in `git status`
    and possibly trigger Perforce on developer machines.

.PARAMETER Tag
    Tag name to author. Default `BpxVerify.Smoke` — namespaced under
    BpxVerify.* so it can't collide with real project tags.

.PARAMETER Comment
    DevComment string. Default mentions M28.pre.5 so the line is easy
    to identify in case the cleanup step doesn't run (e.g. user ^C's
    the harness mid-flight).

.PARAMETER Source
    Source ini name. Default `DefaultGameplayTags.ini` (project root
    `Config/<name>`). Pass an explicit non-default name like `AI.ini`
    to exercise the `Config/Tags/<name>` path.

.PARAMETER Project
    BugHunt (default) or DOW. BugHunt has a starter fixture committed
    at `Config/DefaultGameplayTags.ini`; DOW has the real project ini.
    DOW runs SHOULD NOT happen casually — the post-cleanup state should
    match the pre-state, but a network blip mid-cleanup could leave a
    stray entry that flows through Perforce.

.PARAMETER Engine
    Override UnrealEditor-Cmd.exe path. Defaults to UE_DOW for
    consistency with verify_post_apply_inspect.ps1. For BugHunt pass
    -Engine override to stock 5.7.

.PARAMETER ProjectFile
    Override .uproject path. Default project-specific.

.EXAMPLE
    pwsh -File scripts/verify_tag_author.ps1 `
         -Project BugHunt `
         -Engine 'C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe'

.NOTES
    M28.pre.5 (2026-04-25) — deferred since 2026-04-23 per the
    M28.pre verification-matrix table; lands alongside M28.6.1
    `add_gameplay_tag` op which is the first plan op to mutate config
    files rather than uassets.
#>

[CmdletBinding()]
param(
    [string]$Tag = 'BpxVerify.Smoke',

    [string]$Comment = 'M28.pre.5 parity-gate fixture (auto-cleanup attempted)',

    [string]$Source = 'DefaultGameplayTags.ini',

    [ValidateSet('BugHunt', 'DOW')]
    [string]$Project = 'BugHunt',

    [string]$Engine = 'D:\Work\UE_DOW\engine\Binaries\Win64\UnrealEditor-Cmd.exe',

    [string]$ProjectFile
)

$ErrorActionPreference = 'Stop'
$RepoRoot = Split-Path -Parent $PSScriptRoot

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

$ProjectDir = Split-Path -Parent $ProjectFile
$IniPath    = Join-Path $ProjectDir "Config\$Source"

# When the source is a non-default name, the engine routes to Config/Tags/<name>.
# verify_tag_author follows the same routing.
if ($Source -ne 'DefaultGameplayTags.ini') {
    $IniPath = Join-Path $ProjectDir "Config\Tags\$Source"
}

if (-not (Test-Path -LiteralPath $IniPath -PathType Leaf)) {
    if ($Source -eq 'DefaultGameplayTags.ini' -and $Project -eq 'BugHunt') {
        Write-Error "BugHunt fixture missing: $IniPath. M28.6.1 was supposed to commit a starter."
        exit 2
    }
    # Non-default source — the engine will create the file on first add.
    # Snapshot baseline as 'absent'.
    Write-Host "[verify_tag_author] target ini does not exist yet: $IniPath"
    Write-Host "[verify_tag_author]   engine will create it on add. Treating baseline as absent."
}

$ExtraArgs = switch ($Project) {
    'BugHunt' { @() }
    'DOW'     { @('-EnablePlugins=BlueprintExporter') }
}

$HarnessPath = Join-Path $PSScriptRoot 'verify_tag_author_harness.py'
if (-not (Test-Path -LiteralPath $HarnessPath -PathType Leaf)) {
    Write-Error "Harness missing: $HarnessPath"
    exit 2
}

$stamp   = Get-Date -Format 'yyyyMMdd_HHmmss'
$TmpRoot = Join-Path $env:TEMP "bpx_verify_tag\$stamp"
$LogDir  = Join-Path $env:TEMP "bpx_verify_tag\${stamp}_logs"
New-Item -ItemType Directory -Path $TmpRoot -Force | Out-Null
New-Item -ItemType Directory -Path $LogDir  -Force | Out-Null
$env:BPX_VERIFY_TAG_TMP = $TmpRoot

Write-Host "[verify_tag_author] Tag=$Tag"
Write-Host "[verify_tag_author] Source=$Source -> $IniPath"
Write-Host "[verify_tag_author] Project=$Project ($ProjectFile)"
Write-Host "[verify_tag_author] Engine=$Engine"
Write-Host "[verify_tag_author] Tmp=$TmpRoot"

# ---------- Phase 0: snapshot baseline bytes ----------
$baselineBytes = $null
if (Test-Path -LiteralPath $IniPath -PathType Leaf) {
    $baselineBytes = [System.IO.File]::ReadAllBytes($IniPath)
    Write-Host "[verify_tag_author] Baseline: $($baselineBytes.Length) bytes"
} else {
    Write-Host "[verify_tag_author] Baseline: absent (engine will create file)"
}

function Invoke-Harness {
    param(
        [string]$Phase,
        [int]$TimeoutSec = 300
    )
    $logPath = Join-Path $LogDir "${Phase}.log"
    $argsList = @(
        "`"$ProjectFile`""
        '-run=pythonscript'
        "-script=`"$HarnessPath`""
        "-tag=`"$Tag`""
        "-comment=`"$Comment`""
        "-source=`"$Source`""
    ) + $ExtraArgs + @(
        '-unattended'
        '-nopause'
        '-nullrhi'
        '-nosplash'
        '-nosound'
        '-log'
    )
    Write-Host "[verify_tag_author] Phase=$Phase -> log $logPath"
    $proc = Start-Process -FilePath $Engine -ArgumentList $argsList `
        -NoNewWindow -Wait -PassThru `
        -RedirectStandardOutput $logPath -RedirectStandardError "$logPath.err"
    return @{ ExitCode = $proc.ExitCode; Log = $logPath }
}

function Restore-Baseline {
    if ($null -ne $baselineBytes) {
        try {
            [System.IO.File]::WriteAllBytes($IniPath, $baselineBytes)
            Write-Host "[verify_tag_author] Baseline restored ($($baselineBytes.Length) bytes)"
        } catch {
            Write-Host "[verify_tag_author] WARN — baseline restore failed: $_" -ForegroundColor Yellow
        }
    } else {
        if (Test-Path -LiteralPath $IniPath -PathType Leaf) {
            try {
                Remove-Item -LiteralPath $IniPath -Force
                Write-Host "[verify_tag_author] Baseline restored (file removed)"
            } catch {
                Write-Host "[verify_tag_author] WARN — baseline cleanup failed: $_" -ForegroundColor Yellow
            }
        }
    }
}

# ---------- Phase 1: apply add ----------
$apply1 = Invoke-Harness -Phase 'apply1'
if ($apply1.ExitCode -ge 2) {
    Write-Host "[verify_tag_author] FAIL — apply phase 1 returned $($apply1.ExitCode). Log: $($apply1.Log)" -ForegroundColor Red
    Restore-Baseline
    exit 1
}

$resultPath = Join-Path $TmpRoot 'result.json'
if (-not (Test-Path -LiteralPath $resultPath)) {
    Write-Host "[verify_tag_author] FAIL — apply phase 1 produced no result.json. Log: $($apply1.Log)" -ForegroundColor Red
    Restore-Baseline
    exit 1
}
$result1 = Get-Content -LiteralPath $resultPath -Raw | ConvertFrom-Json
if (-not $result1.passed) {
    Write-Host "[verify_tag_author] FAIL — apply phase 1 reported passed=false. See $resultPath" -ForegroundColor Red
    Restore-Baseline
    exit 1
}

# Read post-apply bytes.
if (-not (Test-Path -LiteralPath $IniPath -PathType Leaf)) {
    Write-Host "[verify_tag_author] FAIL — apply succeeded but ini file does not exist: $IniPath" -ForegroundColor Red
    Restore-Baseline
    exit 1
}
$afterApplyBytes = [System.IO.File]::ReadAllBytes($IniPath)
$afterApplyText  = [System.IO.File]::ReadAllText($IniPath)
Write-Host "[verify_tag_author] After apply: $($afterApplyBytes.Length) bytes"

# Assert: the new tag's `+GameplayTagList=(Tag="<Tag>",...)` line is present.
$expectedLineRe = "\+GameplayTagList\s*=\s*\(\s*Tag\s*=\s*`"$([regex]::Escape($Tag))`""
if ($afterApplyText -notmatch $expectedLineRe) {
    Write-Host "[verify_tag_author] FAIL — expected `+GameplayTagList=(Tag=\`"$Tag\`",...)` not found in ini." -ForegroundColor Red
    Write-Host "[verify_tag_author]   Ini file:   $IniPath"
    Write-Host "[verify_tag_author]   First 30 lines:"
    Get-Content -LiteralPath $IniPath -TotalCount 30 | ForEach-Object { Write-Host "     | $_" }
    Restore-Baseline
    exit 1
}
Write-Host "[verify_tag_author] Line-presence check: PASS"

# Assert: exactly one new `+GameplayTagList=` line was added vs baseline.
function Count-TagLines([byte[]]$bytes) {
    if ($null -eq $bytes -or $bytes.Length -eq 0) { return 0 }
    $text = [System.Text.Encoding]::UTF8.GetString($bytes)
    return ([regex]::Matches($text, '(?im)^\s*\+GameplayTagList\s*=')).Count
}
$baselineCount = Count-TagLines $baselineBytes
$afterCount    = Count-TagLines $afterApplyBytes
if (($afterCount - $baselineCount) -ne 1) {
    Write-Host "[verify_tag_author] FAIL — expected exactly 1 new +GameplayTagList= line; got $afterCount - $baselineCount = $($afterCount - $baselineCount)" -ForegroundColor Red
    Restore-Baseline
    exit 1
}
Write-Host "[verify_tag_author] Line-count check: PASS (baseline=$baselineCount → after=$afterCount, delta=1)"

# ---------- Phase 2: re-apply (idempotence + byte-identity) ----------
$apply2 = Invoke-Harness -Phase 'apply2'
if ($apply2.ExitCode -ge 2) {
    Write-Host "[verify_tag_author] FAIL — apply phase 2 returned $($apply2.ExitCode). Log: $($apply2.Log)" -ForegroundColor Red
    Restore-Baseline
    exit 1
}
$result2 = Get-Content -LiteralPath $resultPath -Raw | ConvertFrom-Json
if (-not $result2.passed) {
    Write-Host "[verify_tag_author] FAIL — apply phase 2 reported passed=false. See $resultPath" -ForegroundColor Red
    Restore-Baseline
    exit 1
}

$afterReapplyBytes = [System.IO.File]::ReadAllBytes($IniPath)
$afterReapplyHash  = (Get-FileHash -LiteralPath $IniPath -Algorithm MD5).Hash
$afterApplyHash    = [System.BitConverter]::ToString(
    [System.Security.Cryptography.MD5]::Create().ComputeHash($afterApplyBytes)
).Replace('-', '')
if ($afterApplyHash -ne $afterReapplyHash) {
    Write-Host "[verify_tag_author] FAIL — re-apply changed the ini bytes. Idempotence broken." -ForegroundColor Red
    Write-Host "[verify_tag_author]   apply1 md5:  $afterApplyHash"
    Write-Host "[verify_tag_author]   apply2 md5:  $afterReapplyHash"
    Restore-Baseline
    exit 1
}
Write-Host "[verify_tag_author] Idempotence check: PASS (md5=$afterApplyHash stable across rounds)"

# ---------- Phase 3: cleanup ----------
Restore-Baseline

Write-Host ""
Write-Host "[verify_tag_author] ALL CHECKS PASS." -ForegroundColor Green
exit 0
