// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RTSGameMode.h"
#include "TTGameMode.generated.h"


/**
 * 
 */
UCLASS()
class TABLETOPGAME_API ATTGameMode : public ARTSGameMode
{
	GENERATED_BODY()
public:
	ATTGameMode();
	void BroadcastDiceRoll(APlayerController* RollingPlayer,FName ActionName, TArray<uint8> DiceResults, uint8 ValueNeeded, bool smallerIsBetter);
	
	
};
