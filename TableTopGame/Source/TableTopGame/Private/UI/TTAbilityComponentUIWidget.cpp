// Fill out your copyright notice in the Description page of Project Settings.

#include "TTAbilityComponentUIWidget.h"
#include "GameplayEffect.h"


void UTTAbilityComponentUIWidget::NativeConstruct() {
	Super::NativeConstruct();
	if (AbilitySystemRef) {
		//AbilitySystemRef->OnAbilityEnded.Add()
		//Effect Bindings
		/** Called on server whenever a GE is applied to self. This includes instant and duration based GEs. */
		AbilitySystemRef->OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UTTAbilityComponentUIWidget::EffectDataChanged );
		/** Called on both client and server whenever a duraton based GE is added (E.g., instant GEs do not trigger this). */
		AbilitySystemRef->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this, &UTTAbilityComponentUIWidget::EffectDataChanged);	
		/** Called on server whenever a periodic GE executes on self */
		AbilitySystemRef->OnPeriodicGameplayEffectExecuteDelegateOnSelf.AddUObject(this, &UTTAbilityComponentUIWidget::EffectDataChanged);

		FGameplayEffectQuery Query = FGameplayEffectQuery();
		TArray<FActiveGameplayEffectHandle> effects = AbilitySystemRef->GetActiveEffects(Query);
		//TODO Bind AbilitySystem Delegeates 
		AbilitySystemRef->AbilityActivatedCallbacks.AddUObject(this, &UTTAbilityComponentUIWidget::AbilityChanged);
		AbilitySystemRef->AbilityEndedCallbacks.AddUObject(this, &UTTAbilityComponentUIWidget::AbilityChanged);
		AbilitySystemRef->AbilityFailedCallbacks.AddUObject(this, &UTTAbilityComponentUIWidget::AbilityFailed);
		AbilitySystemRef->AbilityCommittedCallbacks.AddUObject(this, &UTTAbilityComponentUIWidget::AbilityChanged);

		AbilitySystemRef->OnAbilityEnded.AddUObject(this, &UTTAbilityComponentUIWidget::AbilityEnded);


		TArray<FGameplayAbilitySpec> abilities = AbilitySystemRef->GetActivatableAbilities();
		TArray<FGameplayAttribute> attributes;
		AbilitySystemRef->GetAllAttributes(attributes);
		

		//TODO Get Abilities 
		//TODO Get Active Effects
		//TODO Get Attributes
		
	}
}

void UTTAbilityComponentUIWidget::SetAbilityComponent(UAbilitySystemComponent* AbilitySystem) {
	this->AbilitySystemRef = AbilitySystem;
}
void UTTAbilityComponentUIWidget::AbilityEnded(const FAbilityEndedData& Data) {

}
void UTTAbilityComponentUIWidget::AbilityChanged(UGameplayAbility* Ability)
{

}
void UTTAbilityComponentUIWidget::AbilityFailed(const UGameplayAbility* Ability,const FGameplayTagContainer& Explaination)
{

}
void UTTAbilityComponentUIWidget::DataChanged() 
{
}
void UTTAbilityComponentUIWidget::EffectDataChanged(UAbilitySystemComponent* AbilityComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle) 
{
}