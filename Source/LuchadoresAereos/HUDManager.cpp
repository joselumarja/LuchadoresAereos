
#include "HUDManager.h"
#include "Blueprint/UserWidget.h"
#include "TextWidgetTypes.h"
#include "TextBlock.h"

#define LOCTEXT_NAMESPACE "HUD Manager"

// Sets default values
AHUDManager::AHUDManager() :AccumulatedDeltaTime(.0f), Seconds(200),  Lives(3)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
/*
	PrepareArray.Emplace(FText::FromString("PREPARATE!!"));
	PrepareArray.Emplace(FText::FromString("3"));
	PrepareArray.Emplace(FText::FromString("2"));
	PrepareArray.Emplace(FText::FromString("1"));

	PrepareColor.Emplace(FSlateColor(FLinearColor(FColor::Red)));
	PrepareColor.Emplace(FSlateColor(FLinearColor(FColor::Blue)));
	PrepareColor.Emplace(FSlateColor(FLinearColor(FColor::Green)));
	PrepareColor.Emplace(FSlateColor(FLinearColor(FColor::Yellow)));*/
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
			//pPrepareText = (UTextBlock*)pHUDWidget->GetWidgetFromName("Prepare");
			pLives = (UTextBlock*)pHUDWidget->GetWidgetFromName("TextBoxVidas");
			pTimeInRound = (UTextBlock*)pHUDWidget->GetWidgetFromName("TextBoxSeconds");

		}
	}

	//pTimeInRound->SetVisibility(ESlateVisibility::Hidden);
	//pRoundText->SetText(LOCTEXT("Roundfmt", "RONDA:  "));
	//pNumFails->SetText(LOCTEXT("Failsfmt", "Num Fails: 0"));
	//pScore->SetText(LOCTEXT("Scorefmt", "0"));


}

// Called every frame
void AHUDManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AccumulatedDeltaTime += DeltaTime;

	UpdateSeconds();
	AccumulatedDeltaTime = .0f;
	

}

//QUEDA PENDIENTE DE HACER EL CONTADOR REGRESIVO
void AHUDManager::UpdateSeconds()
{
	Seconds--;

	pTimeInRound->SetText(FText::Format(LOCTEXT("Timefmt", "{0}"), FText::AsNumber(Seconds)));
}

void AHUDManager::UpdateLives()
{
	pLives->SetText(FText::Format(LOCTEXT("Failsfmt", "{0}"), FText::AsNumber(--Lives)));
}

void AHUDManager::UpdateScore(int Score)
{
	pScore->SetText(FText::AsNumber(Score));
}


#undef LOCTEXT_NAMESPACE