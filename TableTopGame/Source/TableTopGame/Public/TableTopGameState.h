// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "TableTopGameState.generated.h"

/**
*
*/
UCLASS()
class TABLETOPGAME_API ATableTopGameState : public AGameState
{
	GENERATED_BODY()

private:
	uint8 CurrentTurn;

	uint8 MaxTurns;

	void EndTurn();



};
