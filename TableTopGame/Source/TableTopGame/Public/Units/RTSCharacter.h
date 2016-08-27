// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Public/StrategySelectionInterface.h"
#include "RTSCharacter.generated.h"


UCLASS()
class TABLETOPGAME_API ARTSCharacter : public ACharacter, public IStrategySelectionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARTSCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//SELECTION INTERFACE
	/** tries to select actor */
	UFUNCTION(BlueprintNativeEvent)
		bool OnSelectionGained();

	/** tries to deselect actor */
	UFUNCTION(BlueprintNativeEvent)
		bool OnSelectionLost();

	UFUNCTION(BlueprintNativeEvent, Category = "Selection")
		FString GetName();


};
