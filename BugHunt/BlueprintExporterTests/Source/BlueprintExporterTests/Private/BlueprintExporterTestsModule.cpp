// Copyright 10 Chambers. All Rights Reserved.

#include "BlueprintExporterTestsModule.h"

DEFINE_LOG_CATEGORY(LogBlueprintExporterTests);

void FBlueprintExporterTestsModule::StartupModule()
{
	UE_LOG(LogBlueprintExporterTests, Log, TEXT("BlueprintExporterTests module started."));
}

void FBlueprintExporterTestsModule::ShutdownModule()
{
	UE_LOG(LogBlueprintExporterTests, Log, TEXT("BlueprintExporterTests module shut down."));
}

IMPLEMENT_MODULE(FBlueprintExporterTestsModule, BlueprintExporterTests)
