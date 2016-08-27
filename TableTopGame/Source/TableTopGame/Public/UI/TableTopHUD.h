// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "TableTopHUD.generated.h"

/**
 * 
 */
UCLASS()
class TABLETOPGAME_API ATableTopHUD : public AHUD
{
	GENERATED_BODY()

public:
	// Begin HUD interface
	virtual void DrawHUD() override;
	// End HUD interface

	//handle Selection Rectangle functionality
	bool bDrawSelectionRect = true;
	void SetSelectionRect(FVector2D startPoint, FVector2D endPoint);
	FBox2D SelectionRect;
private:

};
