<#
.SYNOPSIS
  Force UE to rebuild the BlueprintExporter plugin on next launch.

.DESCRIPTION
  UE decides whether to rebuild a plugin at editor startup based on a
  BuildId file next to the .dll, NOT on whether source changed. Edit a
  .cpp and relaunch the editor and you'll get the PREVIOUS .dll — UE
  only rebuilds when:
    - the .dll is missing, or
    - the .dll's BuildId doesn't match the engine's BuildId (e.g. you
      switched engine versions).

  This script forces a rebuild by killing any running editor and
  deleting the .dll + .modules from a plugin install. Next launch sees
  the missing .dll and runs UBT. Typical rebuild is ~30 s on a warm
  compile cache (per M27.x empirical measurements).

  Defaults to operating on the BugHunt TestProject's plugin install,
  which is the hot path we iterate against. Pass -Install to point at
  a different downstream install.

.PARAMETER Install
  Absolute path to the plugin install whose Binaries/Win64 should be
  cleared. Defaults to the repo's BugHunt/TestProject/Plugins/BlueprintExporter.

.PARAMETER KillEditors
  Whether to kill running UnrealEditor.exe processes first. Default true.
  Set false if you're already certain no editor is running (avoids the
  2-second post-kill pause).

.EXAMPLE
  pwsh -File scripts/force_plugin_rebuild.ps1

  Kill running editors; clear BugHunt's plugin .dll + .modules; next
  BugHunt launch will rebuild.

.EXAMPLE
  pwsh -File scripts/force_plugin_rebuild.ps1 -Install "D:/Work/UE_DOW_Legacy/Plugins/BlueprintExporter"

  Same for a different downstream install (e.g. the legacy DOW depot).

.NOTES
  M27.5 — closes the recurring M27.1/2/3/4 gotcha where a source-only
  change didn't reach the editor because UE loaded the pre-change DLL.
#>

[CmdletBinding()]
param(
    [string]$Install,
    [bool]$KillEditors = $true
)

$ErrorActionPreference = 'Stop'

# Default Install to BugHunt's plugin dir resolved from this script's location.
if (-not $Install) {
    $RepoRoot = Resolve-Path (Join-Path $PSScriptRoot '..')
    $Install = Join-Path $RepoRoot 'BugHunt/TestProject/Plugins/BlueprintExporter'
}

if (-not (Test-Path $Install -PathType Container)) {
    Write-Error "Install directory not found: $Install"
    exit 2
}

$BinariesDir = Join-Path $Install 'Binaries/Win64'
if (-not (Test-Path $BinariesDir -PathType Container)) {
    Write-Host "[info] No Binaries/Win64 under $Install — nothing to clean."
    exit 0
}

if ($KillEditors) {
    $Running = Get-Process -Name UnrealEditor -ErrorAction SilentlyContinue
    if ($Running) {
        Write-Host "[kill] Stopping $($Running.Count) UnrealEditor process(es)..."
        $Running | Stop-Process -Force
        # Windows holds DLL locks briefly after process exit.
        Start-Sleep -Seconds 2
    }
    else {
        Write-Host "[kill] No UnrealEditor processes to stop."
    }
}

$Targets = @(
    'UnrealEditor-BlueprintExporter.dll'
    'UnrealEditor.modules'
)
$Removed = 0
foreach ($name in $Targets) {
    $path = Join-Path $BinariesDir $name
    if (Test-Path $path) {
        Remove-Item -Force $path
        Write-Host "[rm] $path"
        $Removed++
    }
}

if ($Removed -eq 0) {
    Write-Host "[done] No DLL/modules files present — rebuild will already fire on next launch."
}
else {
    Write-Host "[done] Cleared $Removed file(s). Next UE launch will rebuild the plugin (~30 s warm)."
}
