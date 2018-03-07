// Fill out your copyright notice in the Description page of Project Settings.


#include "TTAbilityUIWidget.h"
#include "AbilitySystemComponent.h"
#include "Public/Abilities/TTGameplayAbility.h"



void UTTAbilityUIWidget::InitRefs(UAbilitySystemComponent* AbilitySystem, FGameplayAbilitySpecHandle AbilityToShow) 
{
	this->AbilityHandle = AbilityToShow;
	if (AbilitySystem) {
		this->AbilitySystemRef = AbilitySystem;
		FGameplayAbilitySpec* abilitySpec = AbilitySystemRef->FindAbilitySpecFromHandle(AbilityHandle);
		if (abilitySpec)
		{
			//abilitySpec->Ability.On
		}
	}
}


void UTTAbilityUIWidget::OnUpdateAbility(UGameplayAbility* Ability)
{
	if (Ability->GetCurrentAbilitySpecHandle() == AbilityHandle)
	{
		ReceiveOnUpdateAbility();
	}
}
FGameplayAbilitySpecHandle UTTAbilityUIWidget::GetAbilityHandle() 
{
	return AbilityHandle;
}
UAbilityUIData * UTTAbilityUIWidget::GetAbilityUIData()
{
	if (AbilitySystemRef)
	{
		FGameplayAbilitySpec* abilitySpec = AbilitySystemRef->FindAbilitySpecFromHandle(AbilityHandle);
		if (abilitySpec)
		{
			UTTGameplayAbility* ttAbility = Cast<UTTGameplayAbility>(abilitySpec->Ability);
			if (ttAbility)
			{
				return ttAbility->UIData;
			}
		}
	}
	return nullptr;
}

bool UTTAbilityUIWidget::CanActivate(OUT FGameplayTagContainer & OutReasonToFailTags)
{
	if (AbilitySystemRef)
	{
		FGameplayAbilitySpec* abilitySpec = AbilitySystemRef->FindAbilitySpecFromHandle(AbilityHandle);
		if (abilitySpec && abilitySpec->Ability) 
		{
			FGameplayTagContainer OwnedTags, OptionalRelevantTags;
			AbilitySystemRef->GetOwnedGameplayTags(OwnedTags);
			return abilitySpec->Ability->CanActivateAbility(abilitySpec->Handle, AbilitySystemRef->AbilityActorInfo.Get(),
				&OwnedTags, &OwnedTags, &OptionalRelevantTags);
		}
	}
	return false;
}

bool UTTAbilityUIWidget::IsActive()
{
	if (AbilitySystemRef)
	{
		FGameplayAbilitySpec* abilitySpec = AbilitySystemRef->FindAbilitySpecFromHandle(AbilityHandle);
		if (abilitySpec && abilitySpec->Ability)
		{
			return abilitySpec->Ability->IsActive();
		}
	}
	return false;
}

bool UTTAbilityUIWidget::ActivateAbility()
{
	if (AbilitySystemRef)
	{	
		return AbilitySystemRef->TryActivateAbility(AbilityHandle);		
	}
	return false;
}
