// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemComponent.h"
#include "Public/Abilities/AbilityUIData.h"
#include "TTEffectUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class TABLETOPGAME_API UTTEffectUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitRefs(class UAbilitySystemComponent* AbilitySystemRef, struct FActiveGameplayEffectHandle EffectHandle);

	void OnUpdateEffect();
	//Uses the getters to set Variables in the UI is called when data is updated
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnUpdateEffect"))
	void ReceiveOnUpdateEffect();
	
protected:
	FActiveGameplayEffectHandle EffectHandle;
	UAbilitySystemComponent* AbilitySystemRef;
	UFUNCTION(BlueprintCallable, Category = Effect)
	UAbilityUIData* GetEffectUIData();
	UFUNCTION(BlueprintCallable, Category = Effect)
	TArray<FGameplayModifierInfo> GetModifierInfo();

};
