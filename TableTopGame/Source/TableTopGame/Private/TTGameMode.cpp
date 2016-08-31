// Fill out your copyright notice in the Description page of Project Settings.

#include "TableTopGame.h"
#include "Public/Player/TTPlayerController.h"
#include "TTGameMode.h"


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
