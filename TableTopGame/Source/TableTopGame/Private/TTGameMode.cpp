// Fill out your copyright notice in the Description page of Project Settings.

#include "TableTopGame.h"
#include "Public/Player/TTPlayerController.h"
#include "Public/Player/TableTopPlayerState.h"
#include "TTGameMode.h"


ATTGameMode::ATTGameMode()
{
// use our custom PlayerController class
PlayerControllerClass = ARTSPlayerController::StaticClass();

// set default pawn class to our Blueprinted character
//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/RTSPlayerPawn_BP"));
if (PlayerPawnBPClass.Class != NULL)
{
	DefaultPawnClass = PlayerPawnBPClass.Class;
}
PlayerStateClass = ATableTopPlayerState::StaticClass();
//HUDClass = AStrategyHUD::StaticClass();
}

void ATTGameMode::BroadcastDiceRoll(APlayerController * RollingPlayer, FName ActionName, TArray<uint8> DiceResults, uint8 ValueNeeded, bool smallerIsBetter)
{
	for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ATTPlayerController* PlayerController = Cast<ATTPlayerController>(*It);
		if (PlayerController != nullptr)
		{
			PlayerController->ShowDiceRollInHud(ActionName,DiceResults,ValueNeeded,smallerIsBetter);
		}
	}

}
