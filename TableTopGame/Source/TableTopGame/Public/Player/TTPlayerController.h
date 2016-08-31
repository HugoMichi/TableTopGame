// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Player/RTSPlayerController.h"
#include "TTPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TABLETOPGAME_API ATTPlayerController : public ARTSPlayerController
{
	GENERATED_BODY()
	
	UPROPERTY()
	AActor* SelectedUnit;

	UPROPERTY()
	AActor* EnemyTargetUnit;

	UFUNCTION()
	bool MoveUnitTo(const FVector Location);
	
	
};
