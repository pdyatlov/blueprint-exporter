// Copyright Ten Chambers. All Rights Reserved.

#pragma once

#if WITH_BPXBRIDGE_SUPPORT && WITH_BPXPYTHON_SUPPORT

#include "CoreMinimal.h"

namespace BlueprintExporter::Bridge
{
	class FHandlerRegistry;

	// Registers the M27.2 `validate_plan` + `apply_plan` handlers against a
	// bridge registry. Called from `FBlueprintExporterModule::StartBridge` after
	// the registry is constructed, before the server starts accepting.
	void RegisterPlanHandlers(FHandlerRegistry& Registry);
}

#endif // WITH_BPXBRIDGE_SUPPORT && WITH_BPXPYTHON_SUPPORT
