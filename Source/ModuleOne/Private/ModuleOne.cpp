// Copyright Epic Games, Inc. All Rights Reserved.

#include "ModuleOne.h"
#include "ModuleTwo.h"
#include "Style.h"
#include "Commands.h"
#include "LevelEditor.h"
#include "AssetRegistryModule.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Engine/World.h"
#include "FileHelpers.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Interfaces/IMainFrameModule.h"
#include "SSWindow.h"
#include "SpawnSettings.h"

#define LOCTEXT_NAMESPACE "FBasicPluginModuleOne"

void FBasicPluginModuleOne::StartupModule()
{
	UE_LOG(LogBasicPlugin, Warning, TEXT("ModuleOne Loaded Successfully"))
	{
		auto& mTwo = FModuleManager::LoadModuleChecked<FBasicPluginModuleTwo>("ModuleTwo");
		mTwo.ModuleTwoPrint("ModuleTwo Print Called From Module One");
	}

	FBasicPluginStyle::Initialize();
	FBasicPluginStyle::ReloadTextures();

	FBasicPluginCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FBasicPluginCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FBasicPluginModuleOne::PluginButtonClicked)
	);

	PluginCommands->MapAction(
		FBasicPluginCommands::Get().LoadActor,
		FExecuteAction::CreateRaw(this, &FBasicPluginModuleOne::LoadActor)
	);

	PluginCommands->MapAction(
		FBasicPluginCommands::Get().LoadSaveAsset,
		FExecuteAction::CreateRaw(this, &FBasicPluginModuleOne::LoadAsset)
	);

	PluginCommands->MapAction(
		FBasicPluginCommands::Get().ModuleOnePrintAction,
		FExecuteAction::CreateLambda([]() {
			ModuleOnePrint("ModuleOne Print Called From Menu");
			})
		);

	PluginCommands->MapAction(
		FBasicPluginCommands::Get().ModuleTwoPrintAction,
		FExecuteAction::CreateLambda([]() {
			auto& mTwo = FModuleManager::GetModuleChecked<FBasicPluginModuleTwo>("ModuleTwo");
			mTwo.ModuleTwoPrint("ModuleTwo Print Called From Menu");
			})
	);
	
	//SetupToolBarItem();
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FBasicPluginModuleOne::SetupToolBarItem));
	SetupMenuItem();

	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FBasicPluginModuleOne::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FBasicPluginStyle::ShutDown();

	FBasicPluginCommands::Unregister();

	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FBasicPluginModuleOne::PluginButtonClicked()
{	
	CreateWindow();
}

void FBasicPluginModuleOne::CreateWindow()
{
	IMainFrameModule& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));
	SpawnSettingsWindow::OpenSettingsWindow(MainFrameModule);
}

void FBasicPluginModuleOne::LoadActor()
{
	IAssetRegistry& AssetRegistry = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();
	FString ActorPath = "/Game/Actor/TestActor.TestActor";
	FAssetData ActorData = AssetRegistry.GetAssetByObjectPath(FName(*ActorPath));

	FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();
	FSoftObjectPath ItemToStream = ActorData.ToSoftObjectPath();

	AssetLoader.RequestAsyncLoad(ItemToStream, FStreamableDelegate::CreateRaw(this, &FBasicPluginModuleOne::OnActorLoaded, ActorData));
}

void FBasicPluginModuleOne::OnActorLoaded(FAssetData ActorData)
{
	if (ActorData.IsAssetLoaded())
	{
		UE_LOG(LogBasicPlugin, Display, TEXT("Actor Loaded Successfully"));
	}
}

void FBasicPluginModuleOne::LoadAsset()
{
	IAssetRegistry& AssetRegistry = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();
	
	FString AssetPath = "/Game/Megascans/3D_Assets/Wooden_Chair_ukmlcaoaw/Wooden_Chair_LOD0_ukmlcaoaw.Wooden_Chair_LOD0_ukmlcaoaw";
	FAssetData AssetData = AssetRegistry.GetAssetByObjectPath(FName(*AssetPath));

	FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();
	FSoftObjectPath ItemToStream = AssetData.ToSoftObjectPath();

	AssetLoader.RequestAsyncLoad(ItemToStream, FStreamableDelegate::CreateRaw(this, &FBasicPluginModuleOne::onAssetLoaded, AssetData));
}

void FBasicPluginModuleOne::onAssetLoaded(FAssetData AssetData)
{
	UStaticMesh* StaticMesh = Cast<UStaticMesh>(AssetData.GetAsset());

	StaticMesh->SetLightMapResolution(256);

	FStaticMeshSourceModel& SourceModel = StaticMesh->GetSourceModel(0);
	SourceModel.BuildSettings.BuildScale3D = FVector(3.0, 3.0, 1.0);
	SourceModel.BuildSettings.bGenerateLightmapUVs = true;

	UMaterialInterface* MaterialInterface = StaticMesh->GetMaterial(0);

	UMaterialInstanceDynamic* DyMaterial = UMaterialInstanceDynamic::Create(MaterialInterface, StaticMesh);

	DyMaterial->SetVectorParameterValue(FName(TEXT("Albedo Controls")), FLinearColor(2.0, 0.7, 0.5, 1.0));

	StaticMesh->SetMaterial(0, DyMaterial);

	StaticMesh->Build(true);
	StaticMesh->MarkPackageDirty();
	TArray<UPackage*> PackagesToSave;
	PackagesToSave.Add(StaticMesh->GetPackage());
	UEditorLoadingAndSavingUtils::SavePackages(PackagesToSave, true);
}

void FBasicPluginModuleOne::SpawnActor(FVector Coordinates)
{
	IAssetRegistry& AssetRegistry = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();
	FString ActorPath = "/Game/Actor/TestActor.TestActor";
	FAssetData ActorData= AssetRegistry.GetAssetByObjectPath(FName(*ActorPath));

	if (!ActorData.IsAssetLoaded())
	{
		UE_LOG(LogBasicPlugin, Error, TEXT("Actor not loaded!"));
		return;
	}

	UBlueprint* Actor = Cast<UBlueprint>(ActorData.GetAsset());

	UWorld* World = GEngine->GetWorldContexts()[0].World();

	FRotator Rotation = FRotator::ZeroRotator;

	AActor* SpawnedActor = World->SpawnActor(Actor->GeneratedClass, &Coordinates, &Rotation);
}

void FBasicPluginModuleOne::SetupToolBarItem()
{
	//FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	//{
	//	TSharedPtr<FExtender> ToolBarExtender = MakeShareable(new FExtender);
	//	
	//	ToolBarExtender->AddToolBarExtension("Settings",
	//		EExtensionHook::After,
	//		PluginCommands,
	//		FToolBarExtensionDelegate::CreateRaw(this, &FBasicPluginModuleOne::AddToolBarButton)
	//	);

	//	ToolBarExtender->AddToolBarExtension("Settings",
	//		EExtensionHook::After,
	//		PluginCommands,
	//		FToolBarExtensionDelegate::CreateRaw(this, &FBasicPluginModuleOne::AddToolBarComboButton)
	//	);

	//	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolBarExtender);
	//}

	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* ToolBarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolBarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& ButtonEntry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(
					FBasicPluginCommands::Get().PluginAction,
					LOCTEXT("BasicPlugin_label", "BasicPlugin"),
					LOCTEXT("BasicPlugin_ToolTipOverride", "BasicPlugin"),
					FSlateIcon(FBasicPluginStyle::GetStyleSetName(), "BasicPlugin.Logo"),
					FName(TEXT("BasicPlugin"))));
				
				FUIAction TempCommand;
				
				FToolMenuEntry& ComboButtonEntry = Section.AddEntry(FToolMenuEntry::InitComboButton(
					FName(TEXT("BasicPlugin")),
					TempCommand,
					FOnGetContent::CreateRaw(this, &FBasicPluginModuleOne::FillToolBarComboButton, PluginCommands),
					LOCTEXT("BasicPlugin_label", "BasicPlugin"),
					LOCTEXT("BasicPlugin_ToolTipOverride", "BasicPlugin"),
					FSlateIcon(FBasicPluginStyle::GetStyleSetName(), "BasicPlugin.Logo")));
				
				ButtonEntry.SetCommandList(PluginCommands);
				ComboButtonEntry.SetCommandList(PluginCommands);
			}
		}
	}
}

void FBasicPluginModuleOne::AddToolBarButton(FToolBarBuilder& ToolbarBuilder)
{
	ToolbarBuilder.AddToolBarButton(
		FBasicPluginCommands::Get().PluginAction,
		FName(TEXT("BasicPlugin")),
		LOCTEXT("BasicPlugin_label", "BasicPlugin"),
		LOCTEXT("BasicPlugin_ToolTipOverride", "BasicPlugin"),
		FSlateIcon(FBasicPluginStyle::GetStyleSetName(), "BasicPlugin.Logo"),
		FName(TEXT("BasicPlugin")));
}

void FBasicPluginModuleOne::SetupMenuItem()
{
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddMenuExtension("LevelEditor",
			EExtensionHook::After,
			PluginCommands,
			FMenuExtensionDelegate::CreateRaw(this, &FBasicPluginModuleOne::AddMenuEntry)
		);
		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
}

void FBasicPluginModuleOne::AddMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.BeginSection("CustomMenu", TAttribute<FText>(FText::FromString("BasicPlugin")));

	MenuBuilder.AddMenuEntry(FBasicPluginCommands::Get().ModuleOnePrintAction,
		FName(TEXT("ModuleOnePrint")),
		LOCTEXT("ModuleOnePrint_label", "ModuleOnePrint"),
		LOCTEXT("ModuleOnePrint_ToolTipOverride", "Calls ModuleOne Print Function"),
		FSlateIcon(),
		FName(TEXT("ModuleOnePrint")));

	MenuBuilder.AddSubMenu(FText::FromString("ModuleTwoPrint"),
		FText::FromString("ModuleTwoPrint SubMenu"),
		FNewMenuDelegate::CreateRaw(this, &FBasicPluginModuleOne::FillSubMenu)
	);

	MenuBuilder.EndSection();
}

void FBasicPluginModuleOne::FillSubMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		FBasicPluginCommands::Get().ModuleTwoPrintAction,
		FName(TEXT("ModuleTwoPrint")),
		LOCTEXT("ModuleTwoPrint_label", "ModuleTwoPrint"),
		LOCTEXT("ModuleTwoPrint_ToolTipOverride", "Calls ModuleTwo Print Function"),
		FSlateIcon(),
		FName(TEXT("ModuleTwoPrint")));
}

void FBasicPluginModuleOne::AddToolBarComboButton(FToolBarBuilder& ToolbarBuilder)
{
	FUIAction TempCommand;
	ToolbarBuilder.AddComboButton(
		TempCommand,
		FOnGetContent::CreateRaw(this, &FBasicPluginModuleOne::FillToolBarComboButton, PluginCommands),
		LOCTEXT("BasicPlugin_label", "BasicPlugin"),
		LOCTEXT("BasicPlugin_ToolTipOverride", "BasicPlugin"),
		FSlateIcon(FBasicPluginStyle::GetStyleSetName(), "BasicPlugin.Logo")
	);
}

TSharedRef<SWidget> FBasicPluginModuleOne::FillToolBarComboButton(TSharedPtr<class FUICommandList> Commands)
{
	FMenuBuilder MenuBuilder(true, Commands);
	MenuBuilder.AddMenuEntry(FBasicPluginCommands::Get().ModuleOnePrintAction,
		FName(TEXT("ModuleOnePrint")),
		LOCTEXT("ModuleOnePrint_label", "ModuleOnePrint"),
		LOCTEXT("ModuleOnePrint_ToolTipOverride", "Calls ModuleOne Print Function"),
		FSlateIcon(),
		FName(TEXT("ModuleOnePrint")));
	MenuBuilder.AddMenuEntry(FBasicPluginCommands::Get().ModuleTwoPrintAction,
		FName(TEXT("ModuleTwoPrint")),
		LOCTEXT("ModuleTwoPrint_label", "ModuleTwoPrint"),
		LOCTEXT("ModuleTwoPrint_ToolTipOverride", "Calls ModuleTwo Print Function"),
		FSlateIcon(),
		FName(TEXT("ModuleTwoPrint")));
	MenuBuilder.AddMenuEntry(FBasicPluginCommands::Get().LoadActor,
		FName(TEXT("LoadActor")),
		LOCTEXT("LoadActor_label", "LoadActor"),
		LOCTEXT("LoadActor_ToolTipOverride", "Loads the Actor"),
		FSlateIcon(),
		FName(TEXT("LoadActor")));
	MenuBuilder.AddMenuEntry(FBasicPluginCommands::Get().LoadSaveAsset,
		FName(TEXT("LoadSaveAsset")),
		LOCTEXT("LoadSaveAsset_label", "LoadSaveAsset"),
		LOCTEXT("LoadSaveAsset_ToolTipOverride", "Async Loads & Saves the Asset"),
		FSlateIcon(),
		FName(TEXT("LoadActor")));

	return MenuBuilder.MakeWidget();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBasicPluginModuleOne, ModuleOne)