// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MultiPacker.h"
#include "MultiPackerStyle.h"
#include "MultiPackerCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
//#include "SlateBasics.h"


static const FName MultiPackerTabName("MultiPacker");

#define LOCTEXT_NAMESPACE "FMultiPackerModule"

void FMultiPackerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FMultiPackerStyle::Initialize();
	FMultiPackerStyle::ReloadTextures();

	FMultiPackerCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMultiPackerCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FMultiPackerModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FMultiPackerModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FMultiPackerModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MultiPackerTabName, FOnSpawnTab::CreateRaw(this, &FMultiPackerModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FMultiPackerTabTitle", "MultiPacker"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FMultiPackerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FMultiPackerStyle::Shutdown();

	FMultiPackerCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MultiPackerTabName);
}

UObject* FMultiPackerModule::LoadAssetFromContent(FString Path, FString Name)
{
	FString FullPath = Path + Name;
	FStringAssetReference* assetRef = new FStringAssetReference(FullPath);
	FStreamableManager assetLoader;
	UObject* loadedAsset = nullptr;
	loadedAsset = assetLoader.SynchronousLoad(*assetRef);
	return loadedAsset;
}

TSharedRef<SDockTab> FMultiPackerModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	
	UBlueprint* loadedWidget = Cast<UBlueprint>(LoadAssetFromContent("/MultiPacker/Widgets/", "W_Main"));


	if (loadedWidget)
	{
		UClass* tempWidget = loadedWidget->GeneratedClass;
		createdWidget = CreateWidget<UUserWidget>(GEditor->GetEditorWorldContext().World(), tempWidget);
	}
	else {
		loadedWidget = Cast<UBlueprint>(LoadAssetFromContent("/MultiPacker/Widgets/", "W_Main"));
	}

		return		SNew(SDockTab)
			.TabRole(ETabRole::NomadTab)
			[
				SNew(SBox)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Content()
				[
					createdWidget->TakeWidget()
				]
			];
}

void FMultiPackerModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(MultiPackerTabName);
}

void FMultiPackerModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FMultiPackerCommands::Get().OpenPluginWindow);
}

void FMultiPackerModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FMultiPackerCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMultiPackerModule, MultiPacker)