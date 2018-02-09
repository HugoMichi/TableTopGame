// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "GameplayEffectUIData.h"
#include "Engine/Texture2D.h"
#include "AbilityUIData.generated.h"

/**
 * 
 */
UCLASS()
class TABLETOPGAME_API UAbilityUIData : public UGameplayEffectUIData
{
	GENERATED_UCLASS_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Data, meta = (MultiLine = "true"))
	FText Description;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Data)
	FText Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Data)
	UTexture2D* Icon;
};
