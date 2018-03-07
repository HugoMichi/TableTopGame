// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "TTAttributeUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class TABLETOPGAME_API UTTAttributeUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitRefs(UAbilitySystemComponent* AbilitySystemRef, FGameplayAttribute Attribute);
	
	void OnUpdateAttribute(const FOnAttributeChangeData& Data);
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnUpdateAttribute();
protected:
	FGameplayAttribute Attribute;
	UAbilitySystemComponent* AbilitySystemRef;
	UFUNCTION( BlueprintCallable, Category = Attribute)
	float GetValue();
	UFUNCTION(BlueprintCallable, Category = Attribute)
	float GetBaseValue();
	UFUNCTION(BlueprintCallable, Category = Attribute)
	FString GetInfoText();
	UFUNCTION(BlueprintCallable, Category = Attribute)
	FString GetName();
	
};
