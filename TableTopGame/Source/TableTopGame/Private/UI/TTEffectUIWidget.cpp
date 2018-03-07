// Fill out your copyright notice in the Description page of Project Settings.

#include "TTEffectUIWidget.h"
#include "GameplayAbilitySpec.h"
#include "GameplayEffect.h"
#include "TableTopGame.h"

void UTTEffectUIWidget::InitRefs(UAbilitySystemComponent * AbilitySystem, FActiveGameplayEffectHandle EffectHandleToDisplay)
{
	if (!AbilitySystem) {
		UE_LOG(LogTTGameAbilitySystem, Warning, TEXT("InitRefs in UTTEffectUIWidget called with invalid AbilitySystemRef! "));
		return;
	}
	this->AbilitySystemRef = AbilitySystem;
	this->EffectHandle = EffectHandleToDisplay;
	if (this->AbilitySystemRef) {

		FOnActiveGameplayEffectStackChange* stackChangeDel = this->AbilitySystemRef->OnGameplayEffectStackChangeDelegate(EffectHandle);
		if (stackChangeDel) {
			stackChangeDel->AddLambda([&](FActiveGameplayEffectHandle, int32, int32)
			{
				OnUpdateEffect();
			});
		}
		FOnActiveGameplayEffectTimeChange* timeChangeDel = this->AbilitySystemRef->OnGameplayEffectTimeChangeDelegate(EffectHandle);
		if (timeChangeDel) {
			timeChangeDel->AddLambda([&](FActiveGameplayEffectHandle, float, float)
			{
				OnUpdateEffect();
			});
		}
	}
}
void UTTEffectUIWidget::OnUpdateEffect() 
{
	ReceiveOnUpdateEffect();
}

UAbilityUIData* UTTEffectUIWidget::GetEffectUIData()
{
	const UGameplayEffect* effect = this->AbilitySystemRef->GetGameplayEffectDefForHandle(EffectHandle);
	if (effect) {
		UGameplayEffectUIData* uiData = effect->UIData;
		if (uiData) {
			return Cast<UAbilityUIData>(uiData);
		}
	}
	return nullptr;
}

TArray<FGameplayModifierInfo> UTTEffectUIWidget::GetModifierInfo() 
{
	const UGameplayEffect* effect = this->AbilitySystemRef->GetGameplayEffectDefForHandle(EffectHandle);
	if (effect) {
		return effect->Modifiers;
	}
	return TArray<FGameplayModifierInfo>();
}
