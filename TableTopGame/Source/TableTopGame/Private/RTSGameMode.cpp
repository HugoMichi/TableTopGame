// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/RTSGameMode.h"
#include "TableTopGame.h"


ARTSGameMode::ARTSGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ARTSPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TableTopCPP/Blueprints/Units/RTSPlayerPawn"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	//DefaultPawnClass = ARTSPlayerPawn::StaticClass();
	HUDClass = ATableTopHUD::StaticClass();
}


