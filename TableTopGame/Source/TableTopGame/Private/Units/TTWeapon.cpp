// Fill out your copyright notice in the Description page of Project Settings.

#include "TableTopGame.h"
#include "TTWeapon.h"


// Sets default values
ATTWeapon::ATTWeapon(const FObjectInitializer& ObjectInitializer)
{
	USceneComponent* SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComp"));
	RootComponent = SceneComponent;

	MeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("MeshComp"));
	MeshComponent->SetupAttachment(RootComponent);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATTWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATTWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

