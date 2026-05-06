// Copyright Ten Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Templates/SharedPointer.h"
#include "Templates/UniquePtr.h"

/** Plugin-wide log category. Use instead of LogTemp. */
DECLARE_LOG_CATEGORY_EXTERN(LogBlueprintExporter, Log, All);

class FToolBarBuilder;
class FMenuBuilder;

namespace BlueprintExporter::Bridge
{
	class FBridgeServer;
	class FHandlerRegistry;
}

/**
 * Main module for the Blueprint Exporter plugin.
 * Provides export/import functionality for Blueprint assets in portable JSON format.
 */
class FBlueprintExporterModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** Get the module instance */
	static FBlueprintExporterModule& Get();

	/** Check if the module is loaded */
	static bool IsAvailable();

private:
	/** Register the toolbar extension */
	void RegisterToolbarExtension();

	/** Register content browser hooks */
	void RegisterContentBrowserHooks();

	/** Register menu extensions */
	void RegisterMenuExtensions();

	/** Toolbar extension callback */
	void AddToolbarExtension(FToolBarBuilder& Builder);

	/** Unregister all extensions */
	void UnregisterExtensions();

	/** Handle for the toolbar extender delegate */
	FDelegateHandle ToolbarExtenderHandle;

	/** Handle for content browser asset extender */
	FDelegateHandle ContentBrowserExtenderHandle;

	/** Handle for content browser path/folder extender */
	FDelegateHandle ContentBrowserPathExtenderHandle;

#if WITH_BPXBRIDGE_SUPPORT
	/** JSON-RPC 2.0 editor bridge server (M27). Loopback-only; tick-driven on game thread. */
	TSharedPtr<BlueprintExporter::Bridge::FBridgeServer, ESPMode::ThreadSafe> BridgeServer;

	/** Method registry owned by the module; populated before the server starts accepting. */
	TUniquePtr<BlueprintExporter::Bridge::FHandlerRegistry> BridgeRegistry;

	void StartBridge();
	void StopBridge();
#endif
};
