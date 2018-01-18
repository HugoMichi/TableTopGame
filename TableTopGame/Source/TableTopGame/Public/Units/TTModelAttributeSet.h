// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "TTModelAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TABLETOPGAME_API UTTModelAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModelAttributes")
		FGameplayAttributeData WeoponsSkill;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModelAttributes")
		FGameplayAttributeData BallisticSkill;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModelAttributes")
		FGameplayAttributeData Strength;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModelAttributes")
		FGameplayAttributeData Toughness;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModelAttributes")
		FGameplayAttributeData Wounds;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModelAttributes")
		FGameplayAttributeData Initiative;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModelAttributes")
		FGameplayAttributeData Attacks;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModelAttributes")
		FGameplayAttributeData Leadership;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModelAttributes")
		FGameplayAttributeData ArmourSave;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModelAttributes")
		FGameplayAttributeData InvulnerableSave;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModelAttributes")
		FGameplayAttributeData CoverSave;
	
};
