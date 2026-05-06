"""GameplayTag config-authoring ops via the M28.6.1 reflection bridge.

Authors gameplay tags into project config ini files (`Config/DefaultGameplayTags.ini`
or `Config/Tags/<source>.ini`) by delegating to UE's editor-side
`IGameplayTagsEditorModule::AddNewGameplayTagToINI`. Engine handles file
write, alpha sort, in-memory tag-tree refresh, and (when the project is
under Perforce) source-control checkout. Idempotent on `(tag_name, source_ini)`
so plan replay is safe — duplicate add returns ``skipped`` instead of
re-touching the .ini.

M28.6.1 ships one op of the planned M28.6 catalog:

  - add_gameplay_tag — append a new tag entry to a project ini source.

Future M28.6.x sub-phases (not yet shipped) would cover:
  - delete_gameplay_tag / rename_gameplay_tag — wrap
    `IGameplayTagsEditorModule::DeleteTagFromINI` / `RenameTagInINI`.
  - update_tag_comment — wrap `UpdateTagInINI` for DevComment edits.
  - move_gameplay_tag_between_sources — wrap `MoveTagsBetweenINI`.

Design.md drivers (per WIP_INVENTORY M28 phase table line 2918+2921):
items #1 (squad director + `AI.Order.*` event channel) and #4 (callouts /
pre-grenade lean / committed cover-to-cover anim — `AI.Callout.*` channel).

Determinism: zero `FGuid::NewGuid()` / `MakeUniqueObjectName` on the engine
write path (verified M28.6.0 research). The editor module sorts the on-disk
tag list alphabetically before writing (`UGameplayTagsList::SortTags` called
inside `AddNewGameplayTagToINI` at GameplayTagsEditorModule.cpp:540), so on-disk
order is byte-deterministic across runs. The ONE cross-machine drift source
is `UGameplayTagsDeveloperSettings::DeveloperConfigName` — when a developer
sets that local override, calls with `source_ini="DefaultGameplayTags.ini"`
get diverted to a per-machine ini. This is engine behaviour, analogous to
how Perforce settings divert .uasset saves; document but don't bypass.

Perforce: `IGameplayTagsEditorModule::AddNewGameplayTagToINI` calls
`GameplayTagsUpdateSourceControl` before AND after the ini write. If the
project has Perforce configured (env vars / .p4config / project ini), the
target .ini gets auto-checked-out as part of the save. The MCP-side
`apply_plan` confirm gate is the user's checkpoint for that side effect.
"""

import unreal

from ._common import make_result


def _ops():
    return unreal.BpxReflectionOps


def add_gameplay_tag(
    tag_name: str,
    dev_comment: str = "",
    source_ini: str = "DefaultGameplayTags.ini",
    is_restricted: bool = False,
):
    """Append a new gameplay tag to a project ini source.

    First op of the M28.6 GameplayTag write-side catalog. Wraps the
    editor-side `IGameplayTagsEditorModule::AddNewGameplayTagToINI` engine
    API via the M28.6.1 `BpxReflectionOps::AddGameplayTag` UFUNCTION, which
    handles validation, idempotence, file write, and in-memory tag-tree
    refresh atomically.

    Args:
        tag_name: Dotted tag path. Examples:

              - ``"AI.Order.Flank"`` (squad director event channel — design.md #1)
              - ``"AI.Callout.Grenade"`` (callout channel — design.md #4)
              - ``"AI.State.Suppressed"`` (perception state)

            Validated by the engine's `IsValidGameplayTagString` —
            forbidden characters per `UGameplayTagsSettings::InvalidTagCharacters`
            (typically ``"\\"\\',"``) and structural rules (no leading/trailing
            dot, no double-dots) reject the call. The bridge surfaces a
            structured "try X instead" suggestion when the engine produces
            a fixed-string fallback.

        dev_comment: Author-visible comment string. Stored as
            ``DevComment="..."`` on the resulting
            ``+GameplayTagList=(Tag="...",DevComment="...")`` ini line. Empty
            is fine and matches the dominant DOW pattern (every tag in
            `D:/Work/UE_DOW/game/Config/DefaultGameplayTags.ini` ships with
            empty DevComment).

        source_ini: Target source ini name. Defaults to ``"DefaultGameplayTags.ini"``
            — the project's main tag config at ``<Project>/Config/<name>``.
            Any other name (e.g. ``"AI.ini"``) routes to
            ``<Project>/Config/Tags/<name>``, creating both the file and
            the source registration on first add.

            **Per-machine override caveat:** when the developer running the
            editor has set ``UGameplayTagsDeveloperSettings::DeveloperConfigName``
            in their project settings, ``"DefaultGameplayTags.ini"`` (or an
            empty string) gets diverted to ``<Project>/Config/<DeveloperConfigName>.ini``.
            This is engine behaviour for per-developer staging; the op
            documents it but cannot bypass it. To force a deterministic
            per-source ini across machines, pass an explicit non-default
            name (e.g. ``"AI.ini"``).

        is_restricted: When ``True``, authors a ``+RestrictedGameplayTagList=``
            entry instead of ``+GameplayTagList=``. Restricted tags cannot
            be children of non-restricted tags; the engine enforces this
            and the op surfaces the engine-side rejection as a structured
            error. Default ``False``; M28.6.1 has no soak coverage for the
            restricted path (no design.md driver). Exposed for forward
            compat.

    Returns:
        Standard op-result dict. ``after`` carries
        ``{tag_name, source_ini, skipped}``. ``before`` is ``"absent"`` on
        a real add or ``"existing-in:<source>"`` on idempotent skip.

        Idempotent on ``(tag_name, source_ini)``: the bridge UFUNCTION
        pre-checks via ``UGameplayTagsManager::IsDictionaryTag`` so a re-apply
        of the same tag returns ``success=True, skipped="tag already
        registered"`` without re-writing the .ini file. Enables M28.pre.3
        soak round-2 byte-identity.

    No save call needed: ``IGameplayTagsEditorModule::AddNewGameplayTagToINI``
    handles the ini write internally (via ``UObject::TryUpdateDefaultConfigFile``)
    and refreshes the in-memory tag tree (``EditorRefreshGameplayTagTree``)
    before returning. Plan authors don't call ``compile_and_save_package``
    after this op — there's no UAsset to save.

    Driver context (from M28.6.0 research): the engine API is on
    ``IGameplayTagsEditorModule`` (editor plugin), NOT ``UGameplayTagsManager``
    as the original M28 phase-table assumed. The plugin's Build.cs gates
    the dep behind ``WITH_GAMEPLAYTAGSEDITOR_SUPPORT``; in headless / cooked
    builds the bridge UFUNCTION returns a structured error pointing at the
    missing module.
    """
    target = f"{source_ini}#{tag_name}"
    result = make_result("add_gameplay_tag", target, tag_name)

    if not isinstance(tag_name, str) or not tag_name.strip():
        result["errors"].append("tag_name must be a non-empty string")
        return result
    if not isinstance(dev_comment, str):
        result["errors"].append(
            f"dev_comment must be a string; got {type(dev_comment).__name__}"
        )
        return result
    if not isinstance(source_ini, str) or not source_ini.strip():
        result["errors"].append("source_ini must be a non-empty string")
        return result
    if not isinstance(is_restricted, bool):
        result["errors"].append(
            f"is_restricted must be a bool; got {type(is_restricted).__name__}"
        )
        return result

    ops = _ops()
    # SourceIni passed to the bridge as an FName. The bridge then forwards
    # to AddNewGameplayTagToINI which compares against
    # FGameplayTagSource::GetDefaultName() (the literal FName
    # "DefaultGameplayTags.ini"); FName matching is case-sensitive in
    # storage but display-insensitive — pass the user's literal value
    # through unchanged.
    r = ops.add_gameplay_tag(tag_name, dev_comment, unreal.Name(source_ini), is_restricted)

    if not r.success:
        result["errors"].append(
            f"add_gameplay_tag bridge call failed: {r.error_message}"
        )
        return result

    resolved_source = str(r.after_text) if r.after_text else source_ini

    result["before"] = r.before_text

    if r.skipped:
        result["success"] = True
        result["skipped"] = "tag already registered"
        result["after"] = {
            "tag_name": tag_name,
            "source_ini": resolved_source,
            "spawned": False,
        }
        return result

    result["success"] = True
    result["after"] = {
        "tag_name": tag_name,
        "source_ini": resolved_source,
        "spawned": True,
    }
    return result
