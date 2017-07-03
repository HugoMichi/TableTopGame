// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "Public/Units/ModelCharacter.h"
//#include "Public/Player/EPlayerEnums.h"
#include "TableTopPlayerState.generated.h"

/**
*
*/
class ModelCharacter;

UENUM(BlueprintType)
enum class  EPlayerPhase : uint8
{
	PP_DeploymentPhase = 1 UMETA(DisplayName = "Deployment Phase"),
	PP_MovementPhase = 2	UMETA(DisplayName = "Movement Phase"),
	PP_PsychicPhase	= 4	UMETA(DisplayName = "Psychic Phase"),
	PP_ShootingPhase = 7	UMETA(DisplayName = "Shooting Phase"),
	PP_AssaultPhase	 = 9 	UMETA(DisplayName = "Assault Phase")
	
};
/*

EPlayerPhase& operator++(EPlayerPhase& cur) {
	switch (cur)
	{
	case EPlayerPhase::PP_AssaultPhase:
		return cur = EPlayerPhase::PP_MovementPhase;
	default:
		return cur =  EPlayerPhase::PP_PsychicPhase;
		break;
	}
};*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCurrentPhaseChanged);

UCLASS()
class TABLETOPGAME_API ATableTopPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ATableTopPlayerState(const FObjectInitializer& ObjectInitializer);
	UFUNCTION()
	void EndCurrentPhase();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
	EPlayerPhase CurrentPhase;
	//TEnumAsByte<EPlayerPhase> CurrentPhase;
	UPROPERTY(BlueprintAssignable, Category = "Phase")
	FCurrentPhaseChanged OnCurrentPhaseChanged;

	//UPROPERTY()
	TArray<ModelCharacter*> UnitList;

};
