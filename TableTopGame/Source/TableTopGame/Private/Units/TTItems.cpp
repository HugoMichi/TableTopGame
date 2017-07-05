// Fill out your copyright notice in the Description page of Project Settings.

#include "TableTopGame.h"
#include "TTItems.h"


// Sets default values
ATTItems::ATTItems()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATTItems::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATTItems::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

