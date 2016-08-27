// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Public/Units/TTAttribute.h"
#include "ModelCharacter.generated.h"

class TTWeapon;

UCLASS()
class TABLETOPGAME_API AModelCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AModelCharacter(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
	FAttribute WeoponsSkill;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
	FAttribute BallisticSkill;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
	FAttribute Streangth;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
	FAttribute Toughness;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
	FAttribute Wounds;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
	FAttribute Initiative;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
	FAttribute Attacks;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
	FAttribute Leadership;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
	FAttribute ArmourSave;

	TArray<TTWeapon*> Weapons;
	TTWeapon* CurrentWeapon;

	

	
};
