// Fill out your copyright notice in the Description page of Project Settings.

#include "TableTopGame.h"
#include "Public/Units/ModelCharacter.h"


// Sets default values
AModelCharacter::AModelCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void AModelCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AModelCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AModelCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

