// Fill out your copyright notice in the Description page of Project Settings.

#include "TTAbilityComponentUIWidget.h"
#include "Abilities/TTGameplayAbility.h"
#include "GameplayAbilitySpec.h"
#include "GameplayEffect.h"


void UTTAbilityComponentUIWidget::NativeConstruct() {
	Super::NativeConstruct();
	//if (AbilitySystemRef) {
	//	//AbilitySystemRef->OnAbilityEnded.Add()
	//	//Effect Bindings
	//	/** Called on server whenever a GE is applied to self. This includes instant and duration based GEs. */
	//	AbilitySystemRef->OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UTTAbilityComponentUIWidget::EffectDataChanged );
	//	/** Called on both client and server whenever a duraton based GE is added (E.g., instant GEs do not trigger this). */
	//	AbilitySystemRef->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this, &UTTAbilityComponentUIWidget::EffectDataChanged);	
	//	/** Called on server whenever a periodic GE executes on self */
	//	AbilitySystemRef->OnPeriodicGameplayEffectExecuteDelegateOnSelf.AddUObject(this, &UTTAbilityComponentUIWidget::EffectDataChanged);

	//	FGameplayEffectQuery Query = FGameplayEffectQuery();
	//	TArray<FActiveGameplayEffectHandle> effects = AbilitySystemRef->GetActiveEffects(Query);
	//	for (auto effectHandle : effects) {
	//		FGameplayEffectContextHandle effectContextHandle = AbilitySystemRef->GetEffectContextFromActiveGEHandle(effectHandle);
	//		const UGameplayEffect* effect = AbilitySystemRef->GetGameplayEffectDefForHandle(effectHandle);
	//		UGameplayEffectUIData* uiData = effect->UIData;
	//		const FActiveGameplayEffect* activeEffect = AbilitySystemRef->GetActiveGameplayEffect(effectHandle);

	//		TArray<FGameplayModifierInfo> modifiers = effect->Modifiers;
	//		for (FGameplayModifierInfo mod : modifiers) {
	//			mod.Attribute;
	//			mod.Magnitude;
	//			mod.ModifierMagnitude;
	//			mod.ModifierOp;
	//		}
	//	}
	//	TArray<FGameplayEffectSpec> effectSpecs;
	//	AbilitySystemRef->GetAllActiveGameplayEffectSpecs(effectSpecs);
	//	for (FGameplayEffectSpec effectSpec : effectSpecs) {
	//		const UGameplayEffect* effect = effectSpec.Def;
	//		const FGameplayEffectContextHandle effectContextHandle = effectSpec.GetEffectContext();
	//		TArray<FGameplayEffectModifiedAttribute> modAttributes = effectSpec.ModifiedAttributes;
	//	}
	//	//TODO Bind AbilitySystem Delegeates 
	//	AbilitySystemRef->AbilityActivatedCallbacks.AddUObject(this, &UTTAbilityComponentUIWidget::AbilityChanged);
	//	AbilitySystemRef->AbilityEndedCallbacks.AddUObject(this, &UTTAbilityComponentUIWidget::AbilityChanged);
	//	AbilitySystemRef->AbilityFailedCallbacks.AddUObject(this, &UTTAbilityComponentUIWidget::AbilityFailed);
	//	AbilitySystemRef->AbilityCommittedCallbacks.AddUObject(this, &UTTAbilityComponentUIWidget::AbilityChanged);

	//	AbilitySystemRef->OnAbilityEnded.AddUObject(this, &UTTAbilityComponentUIWidget::AbilityEnded);


	//	TArray<FGameplayAbilitySpec> abilities = AbilitySystemRef->GetActivatableAbilities();
	//	//AbilitySystemRef->TryActivateAbility()

	//	for (FGameplayAbilitySpec abilitySpec : abilities) {
	//		AbilitySystemRef->TryActivateAbility(abilitySpec.Handle);
	//		UTTGameplayAbility* ttAbility = Cast<UTTGameplayAbility>(abilitySpec.Ability);
	//		if (ttAbility) {
	//			ttAbility->UIData;
	//		}
	//		float TimeRemaining, Duration;
	//		abilitySpec.Ability->GetCooldownTimeRemainingAndDuration(abilitySpec.Handle, AbilitySystemRef->AbilityActorInfo.Get(), TimeRemaining, Duration);
	//		FGameplayTagContainer OwnedTags;
	//		AbilitySystemRef->GetOwnedGameplayTags(OwnedTags);
	//		FGameplayTagContainer OptionalRelevantTags;
	//		bool canActivate = abilitySpec.Ability->CanActivateAbility(abilitySpec.Handle, AbilitySystemRef->AbilityActorInfo.Get(), &OwnedTags, &OwnedTags,&OptionalRelevantTags);
	//		bool isActive = abilitySpec.Ability->IsActive();
	//		AbilitySystemRef->FindAbilitySpecFromHandle(abilitySpec.Handle);
	//	}


	//	TArray<FGameplayAttribute> attributes;
	//	AbilitySystemRef->GetAllAttributes(attributes);
	//	for (auto attribute : attributes) {
	//		FString attrName = attribute.GetName();
	//		FOnGameplayAttributeValueChange attributeChangeDelegate = AbilitySystemRef->GetGameplayAttributeValueChangeDelegate(attribute);
	//		attributeChangeDelegate.AddUObject(this, &UTTAbilityComponentUIWidget::AttributeChanged);
	//		float value = AbilitySystemRef->GetNumericAttribute(attribute);
	//		float baseValue = AbilitySystemRef->GetNumericAttributeBase(attribute);
	//		
	//		for (UAttributeSet* attrSet : AbilitySystemRef->SpawnedAttributes) {

	//			FGameplayAttributeData* attrData = attribute.GetGameplayAttributeData(attrSet);
	//			
	//			//AbilitySystemRef.GetEffect
	//		}

	//		for (auto effectHandle : effects) {
	//			float effectAttrributeMagnitude = AbilitySystemRef->GetGameplayEffectMagnitude(effectHandle, attribute);
	//		}

	//		for (FGameplayEffectSpec effectSpec : effectSpecs) {
	//			FGameplayEffectModifiedAttribute* modAttribute = effectSpec.GetModifiedAttribute(attribute);
	//			modAttribute->Attribute;
	//			modAttribute->TotalMagnitude;
	//		}
	//	}
	//	


	//	TArray<UAttributeSet*> attributeSets = AbilitySystemRef->SpawnedAttributes;
	//	
	//	//attributes[1].GetGameplayAttributeDataChecked()

	//	//TODO Get Abilities 
	//	//TODO Get Active Effects
	//	//TODO Get Attributes
	//	
	//}
}



void UTTAbilityComponentUIWidget::SetAbilityComponent(UAbilitySystemComponent* AbilitySystem) {
	if (AbilitySystem) {
		this->AbilitySystemRef = AbilitySystem;
		//Setup AbilityDelegates
		AbilitySystemRef->AbilityActivatedCallbacks.AddUObject(this, &UTTAbilityComponentUIWidget::AbilityChanged);
		AbilitySystemRef->AbilityEndedCallbacks.AddUObject(this, &UTTAbilityComponentUIWidget::AbilityChanged);
		AbilitySystemRef->AbilityFailedCallbacks.AddUObject(this, &UTTAbilityComponentUIWidget::AbilityFailed);
		AbilitySystemRef->AbilityCommittedCallbacks.AddUObject(this, &UTTAbilityComponentUIWidget::AbilityChanged);
		AbilitySystemRef->OnAbilityEnded.AddUObject(this, &UTTAbilityComponentUIWidget::AbilityEnded);
		//AbilitySystemRef->GiveAbility()
		//Create AbilityWidgets
		if (UIAbilityWidgetBP)
		{
			TArray<FGameplayAbilitySpec> abilities = AbilitySystemRef->GetActivatableAbilities();
			for (FGameplayAbilitySpec abilitySpec : abilities)
			{
				OnAddAbility(abilitySpec.Handle);
			}
		}
		//Create EffectWidgets
		if (UIEffectWidgetBP)
		{
			FGameplayEffectQuery Query = FGameplayEffectQuery();
			TArray<FActiveGameplayEffectHandle> effects = AbilitySystemRef->GetActiveEffects(Query);
			for (FActiveGameplayEffectHandle effectHandle : effects)
			{
				OnAddEffect(effectHandle);
			}
			// Lambda to bind Delegates to functions with not matching arguments
			/** Called on server whenever a GE is applied to self. This includes instant and duration based GEs. */
			AbilitySystemRef->OnGameplayEffectAppliedDelegateToSelf.AddLambda([&] //& captures this by ref
				(UAbilitySystemComponent* AbilityComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle) //Delegate Signature
					{
						OnAddEffect(EffectHandle);
					}
				);
			
			
			//AbilitySystemRef->OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UTTAbilityComponentUIWidget::EffectDataChanged);
			/** Called on both client and server whenever a duraton based GE is added (E.g., instant GEs do not trigger this). */
			//AbilitySystemRef->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this, &UTTAbilityComponentUIWidget::EffectDataChanged);
			/** Called on server whenever a periodic GE executes on self */
			//AbilitySystemRef->OnPeriodicGameplayEffectExecuteDelegateOnSelf.AddUObject(this, &UTTAbilityComponentUIWidget::EffectDataChanged);
			

		}
		
		//Create AttributeWidgets
		if (UIAttributeWidgetBP)
		{
			TArray<FGameplayAttribute> attributes;
			AbilitySystemRef->GetAllAttributes(attributes);		
			for (FGameplayAttribute attribute : attributes)
			{	//create AttributeWidgets, delegates are handled by AttributeWidget
				UTTAttributeUIWidget* abilityUI = CreateWidget<UTTAttributeUIWidget>(GetWorld(), UIAttributeWidgetBP);
				abilityUI->InitRefs(AbilitySystemRef, attribute);
				ReceiveOnAddAttribute(abilityUI);
			}
		}


	}
}
void UTTAbilityComponentUIWidget::AbilityEnded(const FAbilityEndedData& Data) 
{
	if (Data.AbilityThatEnded) {
		AbilityChanged(Data.AbilityThatEnded);
	}	
}

void UTTAbilityComponentUIWidget::AbilityChanged(UGameplayAbility* Ability)
{

	/*for (UTTAbilityUIWidget* abilityUIWidget : AbilityUIWidgets) 
	{
		if (Ability->GetCurrentAbilitySpecHandle() == abilityUIWidget->GetAbilityHandle()) 
		{
			abilityUIWidget->OnUpdateAbility(Ability);
		}

	}*/
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
void UTTAbilityComponentUIWidget::AttributeChanged(const FOnAttributeChangeData& Data)
{
	
}

void UTTAbilityComponentUIWidget::OnAddEffect(FActiveGameplayEffectHandle  Effect)
{
	UTTEffectUIWidget* effectUI = CreateWidget<UTTEffectUIWidget>(GetWorld(), UIEffectWidgetBP);
	effectUI->InitRefs(AbilitySystemRef, Effect);
	FOnActiveGameplayEffectRemoved_Info * removeDel = AbilitySystemRef->OnGameplayEffectRemoved_InfoDelegate(Effect);
	if (removeDel) {
		removeDel->AddLambda([&,Effect](const FGameplayEffectRemovalInfo& Info) 
		{	
			if (Info.StackCount <= 0) {
				OnRemoveEffect(Effect);
			}
		});
	}
	//TODO:: set Remove delegate in Effect UI ?? can it remove itself?? or use removeEffectDelegate_Info and use info to remove the correct effect
	//FOnActiveGameplayEffectRemoved* removeDelegate = AbilitySystemRef->OnGameplayEffectRemovedDelegate(Effect);
	//removeDelegate->AddUObject(this, &UTTAbilityComponentUIWidget::OnRemoveEffect);
	//TODO:: hook effects up to turn events, update after each phase
	ReceiveOnAddEffect(effectUI);


}

void UTTAbilityComponentUIWidget::OnRemoveEffect(FActiveGameplayEffectHandle Effect)
{
}

void UTTAbilityComponentUIWidget::OnAddAbility(FGameplayAbilitySpecHandle AbilitySpecHandle)
{
	UTTAbilityUIWidget* abilityUI = CreateWidget<UTTAbilityUIWidget>(GetWorld(), UIAbilityWidgetBP);
	abilityUI->InitRefs(AbilitySystemRef, AbilitySpecHandle);
	ReceiveOnAddAbility(abilityUI);
}

void UTTAbilityComponentUIWidget::OnRemoveAbility(FGameplayAbilitySpecHandle  Ability)
{
}
