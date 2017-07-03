// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Public/Units/ModelCharacter.h"
#include "TTCharacterUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class TABLETOPGAME_API UTTCharacterUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void SetCharacter(AModelCharacter* Character);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Model")
	AModelCharacter* Character;

};
