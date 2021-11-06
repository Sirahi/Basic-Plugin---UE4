#include "Commands.h"

#define LOCTEXT_NAMESPACE "FBasicPluginModule"

void FBasicPluginCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "BasicPlugin", "BasicPlugin", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(LoadActor, "LoadActor", "LoadActor", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(LoadSaveAsset, "LoadSaveAsset", "LoadSaveAsset", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(ModuleOnePrintAction, "ModuleOnePrint", "Calls ModuleOne Print Function", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(ModuleTwoPrintAction, "ModuleTwoPrint", "Calls ModuleTwo Print Function", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE