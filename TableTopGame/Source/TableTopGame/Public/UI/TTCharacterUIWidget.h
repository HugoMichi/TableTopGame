// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Public/Units/ModelCharacter.h"
#include "TTAbilityComponentUIWidget.h"
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
	virtual void NativeConstruct() override;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Meta = (ExposeOnSpawn = "true"), Category = "Model")
	AModelCharacter* Character;

	UPROPERTY()
	UTTAbilityComponentUIWidget* AbilityComponentUI;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UTTAbilityComponentUIWidget> UIAbilityComponentWidgetBP;

};
