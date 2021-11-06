#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class FBasicPluginStyle
{
public:
	static void Initialize();

	static void ShutDown();

	static FName GetStyleSetName();

	static void ReloadTextures();

	static const ISlateStyle& Get();

private:
	static TUniquePtr<class FSlateStyleSet> Create();

	static TUniquePtr<class FSlateStyleSet> StyleInstance;
};