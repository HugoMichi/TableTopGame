// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TableTopGameState.generated.h"

/**
*
*/
UCLASS()
class TABLETOPGAME_API ATableTopGameState : public AGameState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
	uint8 CurrentTurn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
	uint8 MaxTurns;

	UFUNCTION()
	void EndTurn();



};
