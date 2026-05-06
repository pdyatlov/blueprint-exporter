// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlueprintExporterModule.h"
#include "Export/BlueprintExportManager.h"
#include "TextExport/HumanReadableExporter.h"
#include "Schema/BlueprintExportTypes.h"
#include "Schema/StateTreeExportTypes.h"
#include "Serialization/StateTreeSerializer.h"
#if WITH_STATETREE_SUPPORT
#include "StateTree.h"
#endif

#if WITH_BPXBRIDGE_SUPPORT
#include "Bridge/BpxBridgeServer.h"
#include "Bridge/BpxHandlerRegistry.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#if WITH_BPXPYTHON_SUPPORT
#include "Bridge/BpxPlanHandlers.h"
#endif
#endif

#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "ContentBrowserDelegates.h"
#include "Serialization/BlueprintSerializer.h"
#include "ToolMenus.h"
#include "LevelEditor.h"
#include "Engine/Blueprint.h"
#include "AssetRegistry/AssetData.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Misc/MessageDialog.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Interfaces/IMainFrameModule.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/SWindow.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Input/SButton.h"

DEFINE_LOG_CATEGORY(LogBlueprintExporter);

#define LOCTEXT_NAMESPACE "BlueprintExporter"

// Helper function to select output folder with option to create new
static bool SelectOrCreateOutputFolder(FString& OutFolder)
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (!DesktopPlatform)
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("PlatformError", "Could not access file system."));
		return false;
	}

	// Create a clear choice dialog
	TSharedRef<SWindow> ChoiceWindow = SNew(SWindow)
		.Title(LOCTEXT("ExportLocationTitle", "Choose Export Location"))
		.ClientSize(FVector2D(450, 180))
		.SupportsMinimize(false)
		.SupportsMaximize(false)
		.SizingRule(ESizingRule::FixedSize);

	enum class EChoice { None, CreateNew, SelectExisting, Cancel };
	EChoice UserChoice = EChoice::None;

	ChoiceWindow->SetContent(
		SNew(SBorder)
		.Padding(20)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0, 0, 0, 20)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("ChooseExportMethod", "Where would you like to export the Blueprint(s)?"))
				.Font(FCoreStyle::GetDefaultFontStyle("Bold", 12))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0, 0, 0, 10)
			[
				SNew(SButton)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.OnClicked_Lambda([&ChoiceWindow, &UserChoice]() {
					UserChoice = EChoice::CreateNew;
					ChoiceWindow->RequestDestroyWindow();
					return FReply::Handled();
				})
				[
					SNew(STextBlock)
					.Text(LOCTEXT("CreateNewFolderBtn", "Create New Folder..."))
					.Justification(ETextJustify::Center)
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0, 0, 0, 10)
			[
				SNew(SButton)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.OnClicked_Lambda([&ChoiceWindow, &UserChoice]() {
					UserChoice = EChoice::SelectExisting;
					ChoiceWindow->RequestDestroyWindow();
					return FReply::Handled();
				})
				[
					SNew(STextBlock)
					.Text(LOCTEXT("SelectExistingBtn", "Select Existing Folder..."))
					.Justification(ETextJustify::Center)
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Right)
			[
				SNew(SButton)
				.OnClicked_Lambda([&ChoiceWindow, &UserChoice]() {
					UserChoice = EChoice::Cancel;
					ChoiceWindow->RequestDestroyWindow();
					return FReply::Handled();
				})
				[
					SNew(STextBlock)
					.Text(LOCTEXT("CancelBtn", "Cancel"))
				]
			]
		]
	);

	GEditor->EditorAddModalWindow(ChoiceWindow);

	if (UserChoice == EChoice::Cancel || UserChoice == EChoice::None)
	{
		return false;
	}

	if (UserChoice == EChoice::CreateNew)
	{
		// First ask for folder name
		TSharedRef<SWindow> NameWindow = SNew(SWindow)
			.Title(LOCTEXT("NewFolderNameTitle", "New Folder Name"))
			.ClientSize(FVector2D(400, 130))
			.SupportsMinimize(false)
			.SupportsMaximize(false)
			.SizingRule(ESizingRule::FixedSize);

		FString FolderName = TEXT("BlueprintExport");
		bool bNameConfirmed = false;

		TSharedRef<SEditableTextBox> TextBox = SNew(SEditableTextBox)
			.Text(FText::FromString(FolderName))
			.OnTextChanged_Lambda([&FolderName](const FText& NewText) { FolderName = NewText.ToString(); });

		NameWindow->SetContent(
			SNew(SBorder)
			.Padding(15)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0, 0, 0, 10)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("EnterNewFolderName", "Enter a name for the new folder:"))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0, 0, 0, 15)
				[
					TextBox
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Right)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(0, 0, 10, 0)
					[
						SNew(SButton)
						.Text(LOCTEXT("NextBtn", "Next"))
						.OnClicked_Lambda([&NameWindow, &bNameConfirmed]() {
							bNameConfirmed = true;
							NameWindow->RequestDestroyWindow();
							return FReply::Handled();
						})
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SButton)
						.Text(LOCTEXT("CancelBtn2", "Cancel"))
						.OnClicked_Lambda([&NameWindow]() {
							NameWindow->RequestDestroyWindow();
							return FReply::Handled();
						})
					]
				]
			]
		);

		GEditor->EditorAddModalWindow(NameWindow);

		if (!bNameConfirmed)
		{
			return false;
		}

		// Validate folder name
		FolderName = FolderName.TrimStartAndEnd();
		if (FolderName.IsEmpty())
		{
			FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("EmptyFolderName", "Folder name cannot be empty."));
			return false;
		}

		// Remove invalid characters
		FolderName = FPaths::MakeValidFileName(FolderName);

		// Now select parent directory
		FString ParentDir;
		if (!DesktopPlatform->OpenDirectoryDialog(
			FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr),
			FText::Format(LOCTEXT("SelectParentForNew", "Select where to create '{0}'"), FText::FromString(FolderName)).ToString(),
			FPaths::ProjectSavedDir(),
			ParentDir))
		{
			return false;
		}

		if (ParentDir.IsEmpty())
		{
			FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("NoParentSelected", "No parent folder selected."));
			return false;
		}

		// Create the folder
		OutFolder = FPaths::Combine(ParentDir, FolderName);

		if (IFileManager::Get().DirectoryExists(*OutFolder))
		{
			// Folder already exists, ask if they want to use it
			EAppReturnType::Type UseExisting = FMessageDialog::Open(EAppMsgType::YesNo,
				FText::Format(LOCTEXT("FolderExists", "Folder '{0}' already exists.\n\nDo you want to export to this folder?"), FText::FromString(FolderName)));

			if (UseExisting != EAppReturnType::Yes)
			{
				return false;
			}
		}
		else
		{
			if (!IFileManager::Get().MakeDirectory(*OutFolder, true))
			{
				FMessageDialog::Open(EAppMsgType::Ok,
					FText::Format(LOCTEXT("FailedToCreate", "Failed to create folder '{0}'."), FText::FromString(OutFolder)));
				return false;
			}
		}

		return true;
	}
	else // SelectExisting
	{
		if (!DesktopPlatform->OpenDirectoryDialog(
			FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr),
			LOCTEXT("SelectExistingFolder", "Select Existing Folder").ToString(),
			FPaths::ProjectSavedDir(),
			OutFolder))
		{
			return false;
		}

		if (OutFolder.IsEmpty())
		{
			return false;
		}

		return true;
	}
}

IMPLEMENT_MODULE(FBlueprintExporterModule, BlueprintExporter)

static const FName BlueprintExporterTabName("BlueprintExporter");

void FBlueprintExporterModule::StartupModule()
{
	// Register toolbar extension
	RegisterToolbarExtension();

	// Register content browser hooks
	RegisterContentBrowserHooks();

	// Register menu extensions
	RegisterMenuExtensions();

#if WITH_BPXBRIDGE_SUPPORT
	StartBridge();
#endif

	UE_LOG(LogBlueprintExporter, Log, TEXT("TenChambers Blueprint Exporter v1.28.6 loaded"));
}

void FBlueprintExporterModule::ShutdownModule()
{
#if WITH_BPXBRIDGE_SUPPORT
	StopBridge();
#endif

	UnregisterExtensions();

	UE_LOG(LogBlueprintExporter, Log, TEXT("Blueprint Exporter module unloaded"));
}

#if WITH_BPXBRIDGE_SUPPORT
void FBlueprintExporterModule::StartBridge()
{
	using namespace BlueprintExporter::Bridge;

	BridgeRegistry = MakeUnique<FHandlerRegistry>();

	BridgeRegistry->Register(TEXT("ping"),
		[](const TSharedPtr<FJsonObject>& /*Params*/) -> FHandlerResult
		{
			TSharedPtr<FJsonObject> Result = MakeShared<FJsonObject>();
			Result->SetBoolField(TEXT("pong"), true);
			Result->SetStringField(TEXT("pluginVersion"), TEXT("1.28.6"));
			return FHandlerResult::Success(MakeShared<FJsonValueObject>(Result));
		},
		TEXT("Health check. No params. Returns {pong: bool, pluginVersion: string}."));

#if WITH_BPXPYTHON_SUPPORT
	RegisterPlanHandlers(*BridgeRegistry);
#endif

	// M27.4 — `list_methods` registered last so it sees every peer + itself.
	// Captures the registry by raw pointer; the registry lives for the entire
	// module lifetime (StopBridge resets it only in ShutdownModule), and the
	// bridge server is torn down before the registry, so the pointer can't
	// dangle while handlers are being dispatched.
	FHandlerRegistry* RegistryPtr = BridgeRegistry.Get();
	BridgeRegistry->Register(TEXT("list_methods"),
		[RegistryPtr](const TSharedPtr<FJsonObject>& /*Params*/) -> FHandlerResult
		{
			TSharedPtr<FJsonObject> Result = MakeShared<FJsonObject>();
			TArray<TSharedPtr<FJsonValue>> MethodsJson;
			if (RegistryPtr)
			{
				for (const FString& Name : RegistryPtr->GetMethodNames())
				{
					TSharedPtr<FJsonObject> Entry = MakeShared<FJsonObject>();
					Entry->SetStringField(TEXT("name"), Name);
					Entry->SetStringField(TEXT("description"), RegistryPtr->GetDescription(Name));
					MethodsJson.Add(MakeShared<FJsonValueObject>(Entry));
				}
			}
			Result->SetArrayField(TEXT("methods"), MethodsJson);
			Result->SetStringField(TEXT("pluginVersion"), TEXT("1.28.6"));
			return FHandlerResult::Success(MakeShared<FJsonValueObject>(Result));
		},
		TEXT("Introspection. No params. Returns {methods: [{name, description}], pluginVersion}."));

	// Port resolution: BPX_BRIDGE_PORT env var overrides the default 1337.
	uint16 Port = 1337;
	const FString PortEnv = FPlatformMisc::GetEnvironmentVariable(TEXT("BPX_BRIDGE_PORT"));
	if (!PortEnv.IsEmpty())
	{
		const int32 Parsed = FCString::Atoi(*PortEnv);
		if (Parsed > 0 && Parsed <= 65535)
		{
			Port = static_cast<uint16>(Parsed);
		}
		else
		{
			UE_LOG(LogBlueprintExporter, Warning, TEXT("Bridge: ignored invalid BPX_BRIDGE_PORT='%s'; using default %u."), *PortEnv, Port);
		}
	}

	BridgeServer = MakeShared<FBridgeServer, ESPMode::ThreadSafe>();
	if (!BridgeServer->Start(Port, BridgeRegistry.Get()))
	{
		BridgeServer.Reset();
		UE_LOG(LogBlueprintExporter, Warning, TEXT("Bridge: disabled (server failed to start)."));
	}
}

void FBlueprintExporterModule::StopBridge()
{
	if (BridgeServer.IsValid())
	{
		BridgeServer->Stop();
		BridgeServer.Reset();
	}
	BridgeRegistry.Reset();
}
#endif // WITH_BPXBRIDGE_SUPPORT

FBlueprintExporterModule& FBlueprintExporterModule::Get()
{
	return FModuleManager::LoadModuleChecked<FBlueprintExporterModule>("BlueprintExporter");
}

bool FBlueprintExporterModule::IsAvailable()
{
	return FModuleManager::Get().IsModuleLoaded("BlueprintExporter");
}

void FBlueprintExporterModule::RegisterToolbarExtension()
{
	// Register with Tool Menus - add to Tools menu for UE 5.x compatibility
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateLambda([]()
	{
		UToolMenu* ToolsMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");
		if (ToolsMenu)
		{
			FToolMenuSection& Section = ToolsMenu->FindOrAddSection("BlueprintExporter");
			Section.Label = LOCTEXT("BlueprintExporterSection", "Blueprint Exporter");

			// Export Blueprints
			Section.AddMenuEntry(
				"ExportBlueprints",
				LOCTEXT("ExportBlueprints", "Export Blueprints..."),
				LOCTEXT("ExportBlueprintsTooltip", "Export selected Blueprints to JSON format"),
				FSlateIcon(),
				FUIAction(FExecuteAction::CreateLambda([]()
				{
					FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
					TArray<FAssetData> SelectedAssets;
					ContentBrowserModule.Get().GetSelectedAssets(SelectedAssets);

					TArray<UBlueprint*> Blueprints;
					for (const FAssetData& AssetData : SelectedAssets)
					{
						if (UBlueprint* BP = Cast<UBlueprint>(AssetData.GetAsset()))
						{
							Blueprints.Add(BP);
						}
					}

					if (Blueprints.Num() == 0)
					{
						FMessageDialog::Open(EAppMsgType::Ok,
							LOCTEXT("NoBlueprintsSelected", "No Blueprints selected. Please select Blueprints in the Content Browser."));
						return;
					}

					FString OutputDir;
					if (SelectOrCreateOutputFolder(OutputDir))
					{
						FBlueprintExportConfig Config;
						Config.OutputDirectory = OutputDir;
						Config.bPrettyPrint = true;
						Config.bExportHumanReadable = true;
						Config.bExportDigest = true;

						FBlueprintExportManager ExportManager;
						FBlueprintBatchExportResult Result = ExportManager.ExportBlueprints(Blueprints, Config);

						FString Message = FString::Printf(TEXT("Exported %d of %d Blueprints to:\n%s"),
							Result.GetSuccessCount(), Result.Results.Num(), *OutputDir);
						FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message));
					}
				}))
			);

		}
	}));
}

void FBlueprintExporterModule::RegisterContentBrowserHooks()
{
	// Add right-click context menu to content browser
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

	TArray<FContentBrowserMenuExtender_SelectedAssets>& Extenders = ContentBrowserModule.GetAllAssetViewContextMenuExtenders();

	ContentBrowserExtenderHandle = Extenders.Add_GetRef(
		FContentBrowserMenuExtender_SelectedAssets::CreateLambda([](const TArray<FAssetData>& SelectedAssets)
		{
			TSharedRef<FExtender> Extender = MakeShareable(new FExtender);

			// Check if any Blueprints or State Trees are selected
			bool bHasBlueprints = false;
			bool bHasStateTrees = false;

			// Dynamically find UStateTree class for graceful degradation
			UClass* StateTreeClass = FindObject<UClass>(nullptr, TEXT("/Script/StateTreeModule.StateTree"));

			for (const FAssetData& Asset : SelectedAssets)
			{
				if (Asset.AssetClassPath == UBlueprint::StaticClass()->GetClassPathName())
				{
					bHasBlueprints = true;
				}
				else if (StateTreeClass && Asset.AssetClassPath == StateTreeClass->GetClassPathName())
				{
					bHasStateTrees = true;
				}
			}

			if (bHasBlueprints || bHasStateTrees)
			{
				Extender->AddMenuExtension(
					"GetAssetActions",
					EExtensionHook::After,
					nullptr,
					FMenuExtensionDelegate::CreateLambda([SelectedAssets](FMenuBuilder& MenuBuilder)
					{
						MenuBuilder.AddMenuSeparator();
						MenuBuilder.AddSubMenu(
							LOCTEXT("BlueprintExporterSubmenu", "Blueprint Exporter"),
							LOCTEXT("BlueprintExporterSubmenuTooltip", "Export Blueprints and State Trees to portable format"),
							FNewMenuDelegate::CreateLambda([SelectedAssets](FMenuBuilder& SubMenuBuilder)
							{
								SubMenuBuilder.AddMenuEntry(
									LOCTEXT("ExportSelected", "Export to JSON..."),
									LOCTEXT("ExportSelectedTooltip", "Export selected Blueprints and State Trees to JSON"),
									FSlateIcon(),
									FUIAction(FExecuteAction::CreateLambda([SelectedAssets]()
									{
										// Filter to Blueprints and State Trees
										TArray<UBlueprint*> Blueprints;
#if WITH_STATETREE_SUPPORT
										TArray<UObject*> StateTrees;
										UClass* STClass = FindObject<UClass>(nullptr, TEXT("/Script/StateTreeModule.StateTree"));
#endif

										for (const FAssetData& AssetData : SelectedAssets)
										{
											UObject* Asset = AssetData.GetAsset();
											if (UBlueprint* BP = Cast<UBlueprint>(Asset))
											{
												Blueprints.Add(BP);
											}
#if WITH_STATETREE_SUPPORT
											else if (STClass && Asset && Asset->IsA(STClass))
											{
												StateTrees.Add(Asset);
											}
#endif
										}

#if WITH_STATETREE_SUPPORT
										if (Blueprints.Num() == 0 && StateTrees.Num() == 0) return;
#else
										if (Blueprints.Num() == 0) return;
#endif

										FString OutputDir;
										if (SelectOrCreateOutputFolder(OutputDir))
										{
											FBlueprintExportConfig Config;
											Config.OutputDirectory = OutputDir;
											Config.bPrettyPrint = true;
											Config.bExportHumanReadable = true;
											Config.bExportDigest = true;

											FBlueprintExportManager ExportManager;
											int32 BPCount = 0;

											if (Blueprints.Num() > 0)
											{
												FBlueprintBatchExportResult Result = ExportManager.ExportBlueprints(Blueprints, Config);
												BPCount = Result.GetSuccessCount();
											}

#if WITH_STATETREE_SUPPORT
											int32 STCount = 0;
											for (UObject* ST : StateTrees)
											{
												FStateTreeExportResult STResult = ExportManager.ExportStateTree(CastChecked<UStateTree>(ST), Config);
												if (STResult.bSuccess) STCount++;
											}

											FString Msg = FString::Printf(TEXT("Exported %d Blueprints, %d State Trees"), BPCount, STCount);
#else
											FString Msg = FString::Printf(TEXT("Exported %d Blueprints"), BPCount);
#endif
											FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Msg));
										}
									}))
								);

								SubMenuBuilder.AddMenuEntry(
									LOCTEXT("ExportWithDeps", "Export with Dependencies..."),
									LOCTEXT("ExportWithDepsTooltip", "Export with Blueprint dependencies"),
									FSlateIcon(),
									FUIAction(FExecuteAction::CreateLambda([SelectedAssets]()
									{
										TArray<UBlueprint*> Blueprints;
										for (const FAssetData& AssetData : SelectedAssets)
										{
											if (UBlueprint* BP = Cast<UBlueprint>(AssetData.GetAsset()))
											{
												Blueprints.Add(BP);
											}
										}

										if (Blueprints.Num() == 0) return;

										FString OutputDir;
										if (SelectOrCreateOutputFolder(OutputDir))
										{
											FBlueprintExportConfig Config;
											Config.OutputDirectory = OutputDir;
											Config.bIncludeDependencies = true;
											Config.DependencyDepth = 2;
											Config.bPrettyPrint = true;
											Config.bExportHumanReadable = true;
											Config.bExportDigest = true;

											FBlueprintExportManager ExportManager;
											FBlueprintBatchExportResult Result = ExportManager.ExportBlueprints(Blueprints, Config);

											FMessageDialog::Open(EAppMsgType::Ok,
												FText::Format(LOCTEXT("ExportDepsComplete", "Exported {0} Blueprints (including dependencies)"),
													FText::AsNumber(Result.GetSuccessCount())));
										}
									}))
								);

							})
						);
					})
				);
			}

			return Extender;
		})
	).GetHandle();

	// Add right-click context menu for folders in content browser
	TArray<FContentBrowserMenuExtender_SelectedPaths>& PathExtenders = ContentBrowserModule.GetAllPathViewContextMenuExtenders();

	ContentBrowserPathExtenderHandle = PathExtenders.Add_GetRef(
		FContentBrowserMenuExtender_SelectedPaths::CreateLambda([](const TArray<FString>& SelectedPaths)
		{
			TSharedRef<FExtender> Extender = MakeShareable(new FExtender);

			if (SelectedPaths.Num() > 0)
			{
				Extender->AddMenuExtension(
					"PathViewFolderOptions",
					EExtensionHook::After,
					nullptr,
					FMenuExtensionDelegate::CreateLambda([SelectedPaths](FMenuBuilder& MenuBuilder)
					{
						MenuBuilder.AddMenuSeparator();
						MenuBuilder.AddSubMenu(
							LOCTEXT("BlueprintExporterFolderSubmenu", "Blueprint Exporter"),
							LOCTEXT("BlueprintExporterFolderSubmenuTooltip", "Export all Blueprints and State Trees in this folder"),
							FNewMenuDelegate::CreateLambda([SelectedPaths](FMenuBuilder& SubMenuBuilder)
							{
								SubMenuBuilder.AddMenuEntry(
									LOCTEXT("ExportFolderBlueprints", "Export All in Folder..."),
									LOCTEXT("ExportFolderBlueprintsTooltip", "Export all Blueprints and State Trees found recursively in the selected folder(s)"),
									FSlateIcon(),
									FUIAction(FExecuteAction::CreateLambda([SelectedPaths]()
									{
										FString OutputDir;
										if (!SelectOrCreateOutputFolder(OutputDir))
										{
											return;
										}

										FBlueprintExportConfig Config;
										Config.OutputDirectory = OutputDir;
										Config.bPrettyPrint = true;
										Config.bExportHumanReadable = true;
										Config.bExportDigest = true;

										FBlueprintExportManager ExportManager;
										int32 TotalSuccess = 0;
										int32 TotalCount = 0;

										for (const FString& Path : SelectedPaths)
										{
											FBlueprintBatchExportResult Result = ExportManager.ExportBlueprintsByPath(Path, Config);
											TotalSuccess += Result.GetSuccessCount();
											TotalCount += Result.Results.Num();
										}

										// Also export State Trees
#if WITH_STATETREE_SUPPORT
										int32 STSuccess = 0, STTotal = 0;
										if (FStateTreeSerializer::IsStateTreeModuleAvailable())
										{
											for (const FString& Path : SelectedPaths)
											{
												TArray<FStateTreeExportResult> STResults;
												TArray<FExportManifestEntry> STEntries;
												ExportManager.ExportStateTreesByPath(Path, Config, STResults, STEntries);
												STTotal += STResults.Num();
												for (const auto& R : STResults) { if (R.bSuccess) STSuccess++; }
											}
										}

										if (TotalCount == 0 && STTotal == 0)
										{
											FMessageDialog::Open(EAppMsgType::Ok,
												LOCTEXT("NoFolderAssets", "No Blueprints or State Trees found in the selected folder(s)."));
										}
										else
										{
											FString Message = FString::Printf(TEXT("Exported %d/%d Blueprints, %d/%d State Trees to:\n%s"),
												TotalSuccess, TotalCount, STSuccess, STTotal, *OutputDir);
											FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message));
										}
#else
										if (TotalCount == 0)
										{
											FMessageDialog::Open(EAppMsgType::Ok,
												LOCTEXT("NoFolderAssets", "No Blueprints found in the selected folder(s)."));
										}
										else
										{
											FString Message = FString::Printf(TEXT("Exported %d/%d Blueprints to:\n%s"),
												TotalSuccess, TotalCount, *OutputDir);
											FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message));
										}
#endif
									}))
								);

								SubMenuBuilder.AddMenuEntry(
									LOCTEXT("ExportFolderWithDeps", "Export All with Dependencies..."),
									LOCTEXT("ExportFolderWithDepsTooltip", "Export all Blueprints in the selected folder(s) including their dependencies"),
									FSlateIcon(),
									FUIAction(FExecuteAction::CreateLambda([SelectedPaths]()
									{
										FString OutputDir;
										if (!SelectOrCreateOutputFolder(OutputDir))
										{
											return;
										}

										FBlueprintExportConfig Config;
										Config.OutputDirectory = OutputDir;
										Config.bIncludeDependencies = true;
										Config.DependencyDepth = 2;
										Config.bPrettyPrint = true;
										Config.bExportHumanReadable = true;
										Config.bExportDigest = true;

										FBlueprintExportManager ExportManager;
										int32 TotalSuccess = 0;
										int32 TotalCount = 0;

										for (const FString& Path : SelectedPaths)
										{
											FBlueprintBatchExportResult Result = ExportManager.ExportBlueprintsByPath(Path, Config);
											TotalSuccess += Result.GetSuccessCount();
											TotalCount += Result.Results.Num();
										}

										if (TotalCount == 0)
										{
											FMessageDialog::Open(EAppMsgType::Ok,
												LOCTEXT("NoFolderBlueprintsDeps", "No Blueprints found in the selected folder(s)."));
										}
										else
										{
											FString Message = FString::Printf(TEXT("Exported %d of %d Blueprints (including dependencies) to:\n%s"),
												TotalSuccess, TotalCount, *OutputDir);
											FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message));
										}
									}))
								);
							})
						);
					})
				);
			}

			return Extender;
		})
	).GetHandle();
}

void FBlueprintExporterModule::RegisterMenuExtensions()
{
	// Already handled via ToolMenus in RegisterToolbarExtension
}

void FBlueprintExporterModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	// Implemented via ToolMenus
}

void FBlueprintExporterModule::UnregisterExtensions()
{
	if (ContentBrowserExtenderHandle.IsValid() || ContentBrowserPathExtenderHandle.IsValid())
	{
		FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

		if (ContentBrowserExtenderHandle.IsValid())
		{
			TArray<FContentBrowserMenuExtender_SelectedAssets>& Extenders = ContentBrowserModule.GetAllAssetViewContextMenuExtenders();
			Extenders.RemoveAll([this](const FContentBrowserMenuExtender_SelectedAssets& Extender)
			{
				return Extender.GetHandle() == ContentBrowserExtenderHandle;
			});
		}

		if (ContentBrowserPathExtenderHandle.IsValid())
		{
			TArray<FContentBrowserMenuExtender_SelectedPaths>& PathExtenders = ContentBrowserModule.GetAllPathViewContextMenuExtenders();
			PathExtenders.RemoveAll([this](const FContentBrowserMenuExtender_SelectedPaths& Extender)
			{
				return Extender.GetHandle() == ContentBrowserPathExtenderHandle;
			});
		}
	}

	UToolMenus::UnregisterOwner(this);
}

#undef LOCTEXT_NAMESPACE

