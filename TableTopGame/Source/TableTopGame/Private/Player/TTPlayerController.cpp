// Fill out your copyright notice in the Description page of Project Settings.

#include "TableTopGame.h"
#include "ModelCharacter.h"
#include "TTPlayerController.h"

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
