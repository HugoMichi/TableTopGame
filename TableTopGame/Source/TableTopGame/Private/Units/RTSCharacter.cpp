// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Units/RTSCharacter.h"
#include "TableTopGame.h"
#include "Blueprint/UserWidget.h"



// Sets default values
ARTSCharacter::ARTSCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARTSCharacter::BeginPlay()
{
	Super::BeginPlay();
	/*if(UIWidgetBP) 
	{
		//UUserWidget* Widget = UIWidgetBP->GetDefaultObject<UUserWidget>();
		UIWidget = CreateWidget<UUserWidget>(GetWorld(), UIWidgetBP);

	}*/
}

// Called every frame
void ARTSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARTSCharacter::SetupPlayerInputComponent(class UInputComponent* AInputComponent)
{
	Super::SetupPlayerInputComponent(AInputComponent);

}

bool ARTSCharacter::OnSelectionGained_Implementation()
{
	return false;
}

bool ARTSCharacter::OnSelectionLost_Implementation()
{
	return false;
}

FString ARTSCharacter::GetName_Implementation()
{
	return FString();
}

UUserWidget*  ARTSCharacter::GetUIWidget_Implementation()
{
	return nullptr;
}