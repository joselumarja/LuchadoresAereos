
#include "HUDManager.h"
#include "Blueprint/UserWidget.h"
#include "TextWidgetTypes.h"
#include "TextBlock.h"

#define LOCTEXT_NAMESPACE "HUD Manager"

// Sets default values
AHUDManager::AHUDManager() :AccumulatedDeltaTime(.0f), SecondsInRound(0), MinutesInRound(0), Fails(0)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrepareArray.Emplace(FText::FromString("PREPARATE!!"));
	PrepareArray.Emplace(FText::FromString("3"));
	PrepareArray.Emplace(FText::FromString("2"));
	PrepareArray.Emplace(FText::FromString("1"));

	PrepareColor.Emplace(FSlateColor(FLinearColor(FColor::Red)));
	PrepareColor.Emplace(FSlateColor(FLinearColor(FColor::Blue)));
	PrepareColor.Emplace(FSlateColor(FLinearColor(FColor::Green)));
	PrepareColor.Emplace(FSlateColor(FLinearColor(FColor::Yellow)));
}

// Called when the game starts or when spawned
void AHUDManager::BeginPlay()
{
	Super::BeginPlay();

	if (ArchievementWidget) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		pHUDWidget = CreateWidget<UUserWidget>(GetGameInstance(), ArchievementWidget);

		// now you can use the widget directly since you have a reference for it.
		// Extra check to  make sure the pointer holds the widget.
		if (pHUDWidget.IsValid())
		{
			// let add it to the view port
			pHUDWidget->AddToViewport();

			// and retrieve the TextBlock widget within it
			pScore = (UTextBlock*)pHUDWidget->GetWidgetFromName("Score");
			pRoundText = (UTextBlock*)pHUDWidget->GetWidgetFromName("RoundText");
			pPrepareText = (UTextBlock*)pHUDWidget->GetWidgetFromName("Prepare");
			pNumFails = (UTextBlock*)pHUDWidget->GetWidgetFromName("NumFails");
			pTimeInRound = (UTextBlock*)pHUDWidget->GetWidgetFromName("TimeInRound");

		}
	}

	pTimeInRound->SetVisibility(ESlateVisibility::Hidden);
	pRoundText->SetText(LOCTEXT("Roundfmt", "RONDA:  "));
	pNumFails->SetText(LOCTEXT("Failsfmt", "Num Fails: 0"));
	pScore->SetText(LOCTEXT("Scorefmt", "0"));


}

// Called every frame
void AHUDManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AccumulatedDeltaTime += DeltaTime;

	if (InInterRound)
	{
		InInterRoundBehaviour();
	}
	else if (AccumulatedDeltaTime >= 1.0f)
	{
		UpdateSeconds();
		AccumulatedDeltaTime = .0f;
	}

}

void AHUDManager::InInterRoundBehaviour()
{
	if (AccumulatedDeltaTime >= 1.0f) {
		if (PositionPrepare == PrepareArray.Num())
		{
			InInterRound = false;
			pTimeInRound->SetText(FText::Format(LOCTEXT("Timefmt", "Time In Round: {0}:{1}"), FText::AsNumber(0), FText::AsNumber(0)));
			pPrepareText->SetVisibility(ESlateVisibility::Hidden);
			pTimeInRound->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			pPrepareText->SetColorAndOpacity(PrepareColor[PositionPrepare]);
			pPrepareText->SetText(PrepareArray[PositionPrepare]);
			AccumulatedDeltaTime = .0f;
		}
		PositionPrepare++;
	}


}

void AHUDManager::NewRound(int Round)
{
	InInterRound = true;
	PositionPrepare = 0;
	pRoundText->SetText(FText::Format(LOCTEXT("Roundfmt", "RONDA: {0}"), FText::AsNumber(Round)));
	AccumulatedDeltaTime = 0.0f;
	SecondsInRound = .0f;
	MinutesInRound = .0f;
	pPrepareText->SetText(LOCTEXT("Preparefmt", ""));
	pPrepareText->SetVisibility(ESlateVisibility::Visible);
	pTimeInRound->SetVisibility(ESlateVisibility::Hidden);

}

void AHUDManager::UpdateSeconds()
{

	if (SecondsInRound == 60) {
		MinutesInRound++;
		SecondsInRound = 0;
	}

	pTimeInRound->SetText(FText::Format(LOCTEXT("Timefmt", "Time In Round: {0}:{1}"), FText::AsNumber(MinutesInRound), FText::AsNumber(SecondsInRound++)));
}

void AHUDManager::UpdateFails()
{
	pNumFails->SetText(FText::Format(LOCTEXT("Failsfmt", "Num Fails: {0}"), FText::AsNumber(++Fails)));
}

void AHUDManager::UpdateScore(int Score)
{
	pScore->SetText(FText::AsNumber(Score));
}


#undef LOCTEXT_NAMESPACE