// Fill out your copyright notice in the Description page of Project Settings.

#include "TTPlayerController.h"
#include "TableTopGame.h"
#include "ModelCharacter.h"
#include "TableTopPlayerState.h"


bool ATTPlayerController::MoveUnitTo(const FVector Location)
{
	return false;
}

void ATTPlayerController::ShowSelectedModelMovementRange()
{
}

void ATTPlayerController::ShowSelectedModelHoloUnderMouseCursor()
{
}

void ATTPlayerController::ShowSelectedModelShootingRange()
{
}

void ATTPlayerController::ShootAtTarget()
{
	if (!this->SelectedUnit||!this->EnemyTargetUnit)
		return;
	this->SelectedUnit->ShootAtTarget(this->EnemyTargetUnit);
}

void ATTPlayerController::ShowDiceRollInHud(FName ActionName,TArray<uint8> diceRolls, uint8 ValueNeeded, bool smallerIsBetter)
{

}



ATableTopPlayerState* ATTPlayerController::GetPlayerState() 
{		
	return Cast<ATableTopPlayerState>(AController::PlayerState);
}