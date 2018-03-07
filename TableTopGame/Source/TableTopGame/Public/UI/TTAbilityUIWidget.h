// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemComponent.h"
#include "Abilities/AbilityUIData.h"
#include "TTAbilityUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class TABLETOPGAME_API UTTAbilityUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitRefs(class UAbilitySystemComponent* AbilitySystemRef, struct FGameplayAbilitySpecHandle AbilityHandle);

	//Function used for binding to AbilityDelegates calls ReceiveOnUpdateAbility
	void OnUpdateAbility(class UGameplayAbility* Ability);
	//Uses the getters to set Variables in the UI is called when data is updated
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnUpdateAbility"))
	void ReceiveOnUpdateAbility();
	UFUNCTION(Blueprintcallable, Category = Attribute)
	FGameplayAbilitySpecHandle GetAbilityHandle();
protected:
	FGameplayAbilitySpecHandle AbilityHandle;
	UAbilitySystemComponent* AbilitySystemRef;
	UFUNCTION(Blueprintcallable, Category = Attribute)
	UAbilityUIData* GetAbilityUIData();
	UFUNCTION(Blueprintcallable, Category = Attribute)
	bool CanActivate(struct FGameplayTagContainer& OutReasonToFailTags);
	UFUNCTION(Blueprintcallable, Category = Attribute)
	bool IsActive();
	UFUNCTION(Blueprintcallable, Category = Attribute)
	bool ActivateAbility();
	
	
};
