// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

DECLARE_LOG_CATEGORY_EXTERN(LogBasicPlugin, Log, All);
DEFINE_LOG_CATEGORY(LogBasicPlugin);

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FBasicPluginModuleOne : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	static inline void ModuleOnePrint(FString text)
	{
		UE_LOG(LogBasicPlugin, Warning, TEXT("%s"), *text);
	}

	static void SpawnActor(FVector Coordinates);

private:
	void SetupToolBarItem();
	void AddToolBarButton(FToolBarBuilder& ToolbarBuilder);
	
	void SetupMenuItem();
	void AddMenuEntry(FMenuBuilder& MenuBuilder);
	void FillSubMenu(FMenuBuilder& MenuBuilder);
	
	void AddToolBarComboButton(FToolBarBuilder& ToolbarBuilder);
	TSharedRef<SWidget> FillToolBarComboButton(TSharedPtr<class FUICommandList> Commands);

	void PluginButtonClicked();
	void LoadActor();
	void OnActorLoaded(FAssetData ActorData);

	void LoadAsset();
	void onAssetLoaded(FAssetData AssetData);

	void CreateWindow();

	TSharedPtr<class FUICommandList> PluginCommands;
};
