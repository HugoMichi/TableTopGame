// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/*
 
UENUM(BlueprintType)
enum class EPlayerPhase : uint8
{
	PP_DeploymentPhase  UMETA(DisplayName = "Deployment Phase"),
	PP_MovementPhase 	UMETA(DisplayName = "Movement Phase"),
	PP_PsychicPhase UMETA(DisplayName = "Psychic Phase"),
	PP_ShootingPhase 	UMETA(DisplayName = "Shooting Phase"),
	PP_AssaultPhase  UMETA(DisplayName = "Assault Phase")
};
	
	EPlayerPhase operator++(EPlayerPhase cur) {
		switch (cur)
		{
		case EPlayerPhase::PP_AssaultPhase:
			return cur = EPlayerPhase::PP_MovementPhase;
		default:
			return cur = EPlayerPhase::PP_PsychicPhase;
			break;
		}
	}*/

