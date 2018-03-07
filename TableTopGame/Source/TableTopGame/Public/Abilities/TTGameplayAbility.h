// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "GameplayAbilitySpec.h"
#include "Abilities/GameplayAbility.h"
#include "TTGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class TABLETOPGAME_API UTTGameplayAbility : public UGameplayAbility
{
	GENERATED_UCLASS_BODY()
public:
	
	/** Get default priority for running a task */
	virtual uint8 GetGameplayTaskDefaultPriority() const { return FGameplayTasks::DefaultPriority; }
	
	/** Data for the UI representation of this Ability. This should include things like text, icons, etc. Not available in server-only builds. */
	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly, Category = Display)
	class UAbilityUIData* UIData;
};
