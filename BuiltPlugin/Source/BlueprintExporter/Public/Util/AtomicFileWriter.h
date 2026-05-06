// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

namespace BlueprintExporterUtil
{
	/**
	 * Write `Content` to `FinalPath` via a sibling `.tmp` file followed by a rename.
	 * Guarantees the final file either doesn't exist (fresh) or is fully written —
	 * a mid-write crash never leaves a half-file that a resume scan would treat as
	 * done.
	 *
	 * Implementation: write to `<FinalPath>.tmp`, delete `<FinalPath>` if present
	 * (UE's IPlatformFile::MoveFile fails if destination exists on Windows), then
	 * MoveFile `.tmp -> FinalPath`. The delete/move gap is small; if the process
	 * dies there, the final path is absent and the caller's resume logic re-runs
	 * the write.
	 *
	 * Encoding is always ForceUTF8WithoutBOM — downstream tools (ripgrep, git, jq,
	 * Claude Code) all expect BOM-free UTF-8.
	 *
	 * Returns true on success, false if any step fails.
	 */
	BLUEPRINTEXPORTER_API bool SaveStringAtomic(const FString& Content, const FString& FinalPath);
}
