// Copyright Epic Games, Inc. All Rights Reserved.

#include "ModuleTwo.h"
#include "ModuleOne.h"

#define LOCTEXT_NAMESPACE "FBasicPluginModuleTwo"

void FBasicPluginModuleTwo::StartupModule()
{
	UE_LOG(LogBasicPlugin, Warning, TEXT("ModuleTwo Loaded Successfully"));
	auto* mOne = FModuleManager::GetModulePtr<FBasicPluginModuleOne>("ModuleOne");
	mOne->ModuleOnePrint("ModuleOne Print Called From Module Two");
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FBasicPluginModuleTwo::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

MODULETWO_API void FBasicPluginModuleTwo::ModuleTwoPrint(FString text)
{
	UE_LOG(LogBasicPlugin, Warning, TEXT("%s"), *text);
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBasicPluginModuleTwo, ModuleTwo)