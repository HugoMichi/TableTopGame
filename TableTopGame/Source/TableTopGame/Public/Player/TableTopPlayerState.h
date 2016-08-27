// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
//#include "Public/Units/ModelCharacter.h"
#include "TableTopPlayerState.generated.h"

/**
*
*/
class ModelCharacter;

UENUM(BlueprintType)
enum class  EPlayerPhase: uint8
{
PP_DeploymentPhase  UMETA(DisplayName = "Deployment Phase"),
PP_MovementPhase 	UMETA(DisplayName = "Movement Phase"),
PP_PsychicPhase UMETA(DisplayName = "Psychic Phase"),
PP_ShootingPhase 	UMETA(DisplayName = "Shooting Phase"),
PP_AssaultPhase  UMETA(DisplayName = "Assault Phase")
};

UCLASS()
class TABLETOPGAME_API ATableTopPlayerState : public APlayerState
{
	GENERATED_BODY()

		TEnumAsByte<EPlayerPhase> CurrentPhase;
		TArray<ModelCharacter*> UnitList;

};
