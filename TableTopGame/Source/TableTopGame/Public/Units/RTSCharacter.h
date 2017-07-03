// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Public/StrategySelectionInterface.h"
#include "Blueprint/UserWidget.h"
#include "RTSCharacter.generated.h"


UCLASS()
class TABLETOPGAME_API ARTSCharacter : public ACharacter, public IStrategySelectionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARTSCharacter(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* AInputComponent) override;

	//SELECTION INTERFACE
	/** tries to select actor */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Selection")
	bool OnSelectionGained();

	/** tries to deselect actor */
	UFUNCTION(BlueprintNativeEvent,Category = "Selection")
	bool OnSelectionLost();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable,Category = "Selection")
	FString GetName();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Selection")
	UUserWidget*  GetUIWidget();
protected:
	//*Used for displaying Information of the unit in the ui */
	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> UIWidgetBP;

	UUserWidget* UIWidget;*/



};
