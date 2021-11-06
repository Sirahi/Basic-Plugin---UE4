#include "SSWindow.h"
#include "IDetailsView.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Input/SButton.h"
#include "SpawnSettings.h"
#include "ModuleOne.h"

#define LOCTEXT_NAMESPACE "SpawnSettings"

TWeakPtr<SWindow> ActorSpawnWindow;

class SSpawnSettings : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SSpawnSettings) {}
		SLATE_ARGUMENT(USpawnSettings*, InSpawnSettings)
		SLATE_ATTRIBUTE(FText, Label)
		SLATE_EVENT(FOnClicked, TestClick)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
			FPropertyEditorModule& PropertyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
			FDetailsViewArgs SSOptionsDetailsArgs;
			SSOptionsDetailsArgs.bUpdatesFromSelection = false;
			SSOptionsDetailsArgs.bLockable = false;
			SSOptionsDetailsArgs.bAllowSearch = false;
			SSOptionsDetailsArgs.bShowOptions = false;
			SSOptionsDetailsArgs.bAllowFavoriteSystem = false;
			SSOptionsDetailsArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
			SSOptionsDetailsArgs.ViewIdentifier = "SpawnSettings";

			SSOptionsDetails = PropertyEditor.CreateDetailView(SSOptionsDetailsArgs);

			ChildSlot
			[
				SNew(SVerticalBox)

				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				[
					SNew(SScrollBox)
					+ SScrollBox::Slot()
					[
						SSOptionsDetails.ToSharedRef()
					]
					+ SScrollBox::Slot()
					.Padding(3,5)
					[
						SNew(SButton)
						.OnClicked(InArgs._TestClick)
						.ContentPadding(3)
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Center)
						.Text(InArgs._Label)
						.ToolTipText(LOCTEXT("SpawnSettings", "BasicPlugin"))
					]
				]
			];


			

			if (InArgs._InSpawnSettings)
			{
				SetSpawnSettings(InArgs._InSpawnSettings);
			}

	}

	void SetSpawnSettings(USpawnSettings* InSpawnSettings)
	{
		SpawnSettings = InSpawnSettings;

		SSOptionsDetails->SetObject(SpawnSettings);
	}

private:
	TSharedPtr<IDetailsView> SSOptionsDetails;

	USpawnSettings* SpawnSettings;
};


void SpawnSettingsWindow::OpenSettingsWindow(const IMainFrameModule& MainFrameModule)
{
	TSharedPtr<SWindow> Window = ActorSpawnWindow.Pin();

	if (Window.IsValid())
	{
		Window->BringToFront();
	}
	else
	{
		Window = SNew(SWindow)
			.Title(LOCTEXT("SpawnSettings", "Spawn Actor"))
			.ClientSize(FVector2D(200, 150))
			.SupportsMaximize(false)
			.SupportsMinimize(false);

		TSharedPtr<SWindow> RootWindow = MainFrameModule.GetParentWindow();
		if (RootWindow.IsValid())
		{
			FSlateApplication::Get().AddWindowAsNativeChild(Window.ToSharedRef(), RootWindow.ToSharedRef());
		}
		else
		{
			FSlateApplication::Get().AddWindow(Window.ToSharedRef());
		}
	}

	USpawnSettings* SpawnSettings = GetMutableDefault<USpawnSettings>();

	Window->SetContent(
		SNew(SSpawnSettings)
		.InSpawnSettings(SpawnSettings)
		.Label(FText::FromString("SPAWN"))
		.TestClick_Lambda([]() {
			USpawnSettings* SSettings = GetMutableDefault<USpawnSettings>();
			FBasicPluginModuleOne::SpawnActor(SSettings->GetCoordinates());
			return FReply::Handled(); 
		})
	);

	ActorSpawnWindow = Window;
}

#undef LOCTEXT_NAMESPACE