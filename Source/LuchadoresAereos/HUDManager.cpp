
#include "HUDManager.h"
#include "Blueprint/UserWidget.h"
#include "TextWidgetTypes.h"
#include "TextBlock.h"


#define LOCTEXT_NAMESPACE "HUD Manager"

// Sets default values
AHUDManager::AHUDManager() 
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHUDManager::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidget) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		pHUDWidget = CreateWidget<UUserWidget>(GetGameInstance(), HUDWidget);

		// now you can use the widget directly since you have a reference for it.
		// Extra check to  make sure the pointer holds the widget.
		if (pHUDWidget.IsValid())
		{
			// let add it to the view port
			pHUDWidget->AddToViewport();

			// and retrieve the TextBlock widget within it
			pScore = (UTextBlock*)pHUDWidget->GetWidgetFromName("TextBoxScore");
			pKilledEnemies = (UTextBlock*)pHUDWidget->GetWidgetFromName("TextBoxKilledEnemies");
			
			pLives = (UTextBlock*)pHUDWidget->GetWidgetFromName("TextBoxVidas");
			pTimeInRound = (UTextBlock*)pHUDWidget->GetWidgetFromName("TextBoxSeconds");
			
		}
	}
}

// Called every frame
void AHUDManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHUDManager::UpdateSeconds(int Seconds)
{
	pTimeInRound->SetText(FText::Format(LOCTEXT("Timefmt", "{0}"), FText::AsNumber(Seconds)));
}


void AHUDManager::UpdateLives(int Lives)
{
	pLives->SetText(FText::Format(LOCTEXT("Livesfmt", "{0}"), FText::AsNumber(Lives)));
}

void AHUDManager::UpdateScore(int Score)
{
	pScore->SetText(FText::AsNumber(Score));
}


#undef LOCTEXT_NAMESPACE