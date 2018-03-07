// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemComponent.h"
#include "Public/UI/TTAttributeUIWidget.h"
#include "Public/UI/TTAbilityUIWidget.h"
#include "Public/UI/TTEffectUIWidget.h"
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






	//Delegate Binding Functions
	void AbilityEnded(const FAbilityEndedData& Data);
	void AbilityChanged(UGameplayAbility* Ability);
	void AbilityFailed(const UGameplayAbility * Ability, const FGameplayTagContainer & Explaination);
	UFUNCTION(BlueprintCallable)
	void EffectDataChanged(UAbilitySystemComponent* AbilityComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle);
	void AttributeChanged(const FOnAttributeChangeData & Data);



	//Attributes
	//UPROPERTY(BlueprintReadOnly, BlueprintReadOnly, Category = "UI")
	//TArray<UTTAttributeUIWidget*> AttributeUIWidgets;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UTTAttributeUIWidget> UIAttributeWidgetBP;
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnAddAttribute"))
	void ReceiveOnAddAttribute(UTTAttributeUIWidget* WidgetToAdd);

	//Effects add and remove
	void OnAddEffect( FActiveGameplayEffectHandle Effect);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnAddEffect"))
	void ReceiveOnAddEffect(UTTEffectUIWidget* WidgetToAdd);

	void OnRemoveEffect(FActiveGameplayEffectHandle Effect);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnRemoveEffect"))
	void ReceiveOnRemoveEffect(UTTEffectUIWidget* WidgetToRemove);
	UPROPERTY(BlueprintReadOnly, BlueprintReadOnly, Category = "UI")
	TArray<UTTEffectUIWidget*> EffectUIWidgets;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UTTEffectUIWidget> UIEffectWidgetBP;


	//Abilities add and remove
	void OnAddAbility(FGameplayAbilitySpecHandle Ability);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnAddAbility"))
	void ReceiveOnAddAbility(UTTAbilityUIWidget* WidgetToAdd);

	void OnRemoveAbility(FGameplayAbilitySpecHandle AbilitySpecHandle);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnRemoveAbility"))
	void ReceiveOnRemoveAbility(UTTAbilityUIWidget* WidgetToRemove);
	//array of widgets should not be needed widget placement and reference must be implemented in blueprints in ReceiveOnAdd/Remove Ability
	//UPROPERTY(BlueprintReadOnly, BlueprintReadOnly, Category = "UI")
	//TArray<UTTAbilityUIWidget*> AbilityUIWidgets;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UTTAbilityUIWidget> UIAbilityWidgetBP;
};
