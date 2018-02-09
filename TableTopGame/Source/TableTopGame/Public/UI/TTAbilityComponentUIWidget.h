// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemComponent.h"
#include "TTAbilityComponentUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class TABLETOPGAME_API UTTAbilityComponentUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void SetAbilityComponent(UAbilitySystemComponent* AbilitySystem);
	virtual void NativeConstruct() override;
protected:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"), Category = "Model")
	UAbilitySystemComponent* AbilitySystemRef;

	UFUNCTION(BlueprintCallable)
	void DataChanged();
	void AbilityEnded(const FAbilityEndedData& Data);
	void AbilityChanged(UGameplayAbility* Ability);
	void AbilityFailed(const UGameplayAbility * Ability, const FGameplayTagContainer & Explaination);
	UFUNCTION(BlueprintCallable)
	void EffectDataChanged(UAbilitySystemComponent* AbilityComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle);
};
