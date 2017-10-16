// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MultiPackerStyle.h"
#include "MultiPackerCommands.h"
#include "LevelEditor.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Editor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Paths.h"

class FToolBarBuilder;
class FMenuBuilder;

class FMultiPackerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	UObject* LoadAssetFromContent(FString Path, FString Name);
	
	//Our reference variable to the widget we are loading in
	UPROPERTY() //Macro to prevent it being cleared up by GC, you can also make it visible to blueprints with specific parameters
	UUserWidget* createdWidget = nullptr; //Always set pointers to nullptr unless you're declaring and defining at the same time
private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};