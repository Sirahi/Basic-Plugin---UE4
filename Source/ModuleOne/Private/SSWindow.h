#pragma once

#include "CoreMinimal.h"
#include "SpawnSettings.h"

class IMainFrameModule;

class SpawnSettingsWindow
{
public:
	static void OpenSettingsWindow(const IMainFrameModule& MainFrameModule);
};