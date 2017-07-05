// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TTDiceRollWidget.generated.h"

/**
 * 
 */
UCLASS()
class TABLETOPGAME_API UTTDiceRollWidget : public UUserWidget
{
	GENERATED_BODY()

		//TODO:: use a DiceRollInfoStruct
public:
	UFUNCTION(BlueprintCallable)
	void SetDiceRollInfo(FName ActionName, TArray<uint8> diceRolls, uint8 ValueNeeded, bool smallerIsBetter);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dice")
	FName ActionName;
	TArray<uint8> diceRolls;
	uint8 ValueNeeded;
	bool smallerIsBetter;
	
};
