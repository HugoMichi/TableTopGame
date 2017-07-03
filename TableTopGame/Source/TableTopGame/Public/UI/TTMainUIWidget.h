// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player/TableTopPlayerState.h"
#include "TTMainUIWidget.generated.h"


/**
 * 
 */
UCLASS()
class TABLETOPGAME_API UTTMainUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	/*Ref to the CurrentPhase of the Player owning the UI*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)		
	EPlayerPhase CurrentPhase;
	
	
	
};
