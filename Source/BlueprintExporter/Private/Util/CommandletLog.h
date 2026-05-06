// Copyright 10 Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlueprintExporterModule.h"

namespace BlueprintExporter::Util
{
	/** Commandlet log line: `[Category] Message` on LogBlueprintExporter, Error channel if bIsError. */
	inline void LogLine(const FString& Category, const FString& Message, bool bIsError = false)
	{
		const FString Line = FString::Printf(TEXT("[%s] %s"), *Category, *Message);
		if (bIsError)
		{
			UE_LOG(LogBlueprintExporter, Error, TEXT("%s"), *Line);
		}
		else
		{
			UE_LOG(LogBlueprintExporter, Display, TEXT("%s"), *Line);
		}
	}
}
