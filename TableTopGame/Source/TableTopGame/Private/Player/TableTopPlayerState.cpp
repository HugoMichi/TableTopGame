// Fill out your copyright notice in the Description page of Project Settings.

#include "TableTopGame.h"
#include "CoreMinimal.h"
#include "Public/Player/TableTopPlayerState.h"
#include "Public/Utility_BP.h"


/*EPlayerPhase::operator++(EPlayerPhase& phase) {

}*/
ATableTopPlayerState::ATableTopPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) 
{
	this->CurrentPhase = EPlayerPhase::PP_DeploymentPhase;
}

void ATableTopPlayerState::EndCurrentPhase() {
	FString EnumPhaseString = "EPlayerPhase";
	FString LastPhase = UUtility_BP::GetEnumElementToString<EPlayerPhase>(EnumPhaseString,this->CurrentPhase);
	this->CurrentPhase = UUtility_BP::GetNextEnumElement<EPlayerPhase>(EnumPhaseString, this->CurrentPhase);
	OnCurrentPhaseChanged.Broadcast();
	FString NewPhase = UUtility_BP::GetEnumElementToString<EPlayerPhase>(EnumPhaseString, this->CurrentPhase);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Last Player Phase: "+ LastPhase + 
																"Switched to Phase: " + NewPhase));
}