// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "ShowDebugComponent.h"
#include "DebugData.h"
#include "ShowDebugWidget.generated.h"

/**
 * 
 */
UCLASS()
class TABLETOPGAME_API UShowDebugWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//* Function called when variables are updated. Returning list of updated variables */
	UFUNCTION(BlueprintNativeEvent, Category = "Variables")
	void OnVariablesUpdated(const TArray<FDebugVariable>& VariablesList); //this is actual Event in Blueprint	
	void OnVariablesUpdated_Implementation(const TArray<FDebugVariable>& VariablesList);  // this is function that can be used in C++ (not visible in Blueprints)
};