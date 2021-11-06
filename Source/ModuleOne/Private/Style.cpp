#include "Style.h"
#include "ModuleOne.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"
#include "Framework/Application/SlateApplication.h"

TUniquePtr<FSlateStyleSet> FBasicPluginStyle::StyleInstance = NULL;

void FBasicPluginStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FBasicPluginStyle::ShutDown()
{
	if (StyleInstance.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
		StyleInstance.Reset();
	}
}

FName FBasicPluginStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("BasicPluginStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )

const FVector2D Icon40x40(40.0f, 40.0f);

TUniquePtr<FSlateStyleSet> FBasicPluginStyle::Create()
{
	TUniquePtr<FSlateStyleSet> Style = MakeUnique<FSlateStyleSet>(GetStyleSetName());

	Style->SetContentRoot(IPluginManager::Get().FindPlugin("BasicPlugin")->GetBaseDir() / TEXT("Resources"));
	Style->Set("BasicPlugin.Logo", new IMAGE_BRUSH(TEXT("Icon40x40"), Icon40x40));

	return Style;
}

#undef IMAGE_BRUSH

void FBasicPluginStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FBasicPluginStyle::Get()
{
	check(StyleInstance);
	return *StyleInstance;
}