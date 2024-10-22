// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Player/RTSPlayerController.h"
#include "TTPlayerController.generated.h"
class AModelCharacter;
class ATTPlayerState;
/**
 * 
 */
UCLASS()
class TABLETOPGAME_API ATTPlayerController : public ARTSPlayerController
{
	GENERATED_BODY()
	

public:
	/*Movement Phase*/
	/*Moves Selected Unit to the postion
	 * @param Location to move to 
	*/
	UFUNCTION()
	bool MoveUnitTo(const FVector Location);
	UFUNCTION()
	void ShowSelectedModelMovementRange();
	UFUNCTION()
	void ShowSelectedModelHoloUnderMouseCursor();


	/*Shooting Phase*/
	UFUNCTION()
	void ShowSelectedModelShootingRange();
	UFUNCTION()
	void ShootAtTarget();
	UFUNCTION()
	void ShowDiceRollInHud(FName ActionName,TArray<uint8> diceRolls, uint8 ValueNeeded, bool smallerIsBetter);
	UFUNCTION()
	ATableTopPlayerState* GetPlayerState();
protected:	
	UPROPERTY()
	AModelCharacter* SelectedUnit;

	
	UPROPERTY()
	AModelCharacter* EnemyTargetUnit;
	
};
