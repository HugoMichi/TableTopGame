// Fill out your copyright notice in the Description page of Project Settings.

#include "TTAttributeUIWidget.h"
#include "Abilities/AbilityUIData.h"
#include "TableTopGame.h"



void UTTAttributeUIWidget::InitRefs(UAbilitySystemComponent* AbilitySystem, FGameplayAttribute AttributeToDisplay) {
	if (!AbilitySystem) {
		UE_LOG(LogTTGameAbilitySystem, Warning, TEXT("UpdateAttribute in TTAttributeWidget called with invalid AbilitySystemRef! "));
		return;
	}
	this->AbilitySystemRef = AbilitySystem;
	this->Attribute = AttributeToDisplay;
	if (this->AbilitySystemRef) {
		//TODO maybe use lambda
		this->AbilitySystemRef->GetGameplayAttributeValueChangeDelegate(Attribute)
				.AddUObject(this,&UTTAttributeUIWidget::OnUpdateAttribute);
	}

}


void UTTAttributeUIWidget::OnUpdateAttribute(const FOnAttributeChangeData& Data) {
	if (!AbilitySystemRef) {
		UE_LOG(LogTTGameAbilitySystem, Warning, TEXT("UpdateAttribute in TTAttributeWidget called with invalid AbilitySystemRef! "));
		return;
	}
	ReceiveOnUpdateAttribute();
}
float UTTAttributeUIWidget::GetValue() 
{
	if (!AbilitySystemRef) {
		UE_LOG(LogTTGameAbilitySystem, Warning, TEXT("UpdateAttribute in TTAttributeWidget called with invalid AbilitySystemRef! "));
		return 0.0;
	}
	return AbilitySystemRef->GetNumericAttribute(this->Attribute);
}

float UTTAttributeUIWidget::GetBaseValue() 
{
	if (!AbilitySystemRef) {
		UE_LOG(LogTTGameAbilitySystem, Warning, TEXT("UpdateAttribute in TTAttributeWidget called with invalid AbilitySystemRef! "));
		return 0.0;
	}
	return AbilitySystemRef->GetNumericAttributeBase(this->Attribute);
}

FString UTTAttributeUIWidget::GetInfoText() 
{
	if (!AbilitySystemRef) {
		UE_LOG(LogTTGameAbilitySystem, Warning, TEXT("UpdateAttribute in TTAttributeWidget called with invalid AbilitySystemRef! "));
		return FString();
	}
	//Get Attribute affecting Effects
	FGameplayEffectQuery Query = FGameplayEffectQuery();
	TArray<FActiveGameplayEffectHandle> effects = AbilitySystemRef->GetActiveEffects(Query);
	FString InfoText = FString();
	for (auto effectHandle : effects) {
		float effectAttrributeMagnitude = AbilitySystemRef->GetGameplayEffectMagnitude(effectHandle, this->Attribute);
		if (effectAttrributeMagnitude > 0) {
			const UGameplayEffect* effect = AbilitySystemRef->GetGameplayEffectDefForHandle(effectHandle);
			if (effect) {
				if (effect->UIData && Cast<UAbilityUIData>(effect->UIData)) {
					UAbilityUIData*  data = Cast<UAbilityUIData>(effect->UIData);
					//Todo:: dont build sttring here give the values to the ui built it in the widget
					InfoText.Append(FString::SanitizeFloat(effectAttrributeMagnitude) + data->Name.ToString() + LINE_TERMINATOR);
				}
			}
		}
	}
	return InfoText;
}


FString UTTAttributeUIWidget::GetName() 
{
	return Attribute.AttributeName;
}