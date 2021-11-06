#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "Style.h"
#include "ToolMenus.h"

class FBasicPluginCommands : public TCommands<FBasicPluginCommands>
{
public:

	FBasicPluginCommands()
		: TCommands<FBasicPluginCommands>(TEXT("BasicPlugin"), NSLOCTEXT("Contexts", "BasicPlugin", "BasicPlugin Plugin"), NAME_None, FBasicPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
	TSharedPtr< FUICommandInfo > LoadActor;
	TSharedPtr< FUICommandInfo > LoadSaveAsset;
	TSharedPtr< FUICommandInfo > ModuleOnePrintAction;
	TSharedPtr< FUICommandInfo > ModuleTwoPrintAction;
};