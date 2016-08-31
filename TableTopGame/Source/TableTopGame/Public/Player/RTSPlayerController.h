// Fill out your copyright notice in the Description page of Project Settings.
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Public/StrategySelectionInterface.h"
#include "Public/UI/TableTopHUD.h"
#include "RTSPlayerController.generated.h"

/**
*
*/
UCLASS()
class TABLETOPGAME_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARTSPlayerController(const FObjectInitializer& ObjectInitializer);

	
protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	void OnSetSelectedUnderCursorPressed();
	void OnSetSelectedUnderCursorReleased();

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	void OnMouseMove(float axisValue);
protected:
	/*Selection Properties and function*/
	TArray<AActor*> SelectedObjects;
	/*helper function to Empty Array and Notify the Actors of lostSelection */
	void NotifyAndEmptySelectedObjects();
	/*if true current Selection is not discardet at a new Selection*/
	bool bAddToCurrentSelection = false;

	bool bBoundingBoxStarted = false;
	/*Copy of Hud->GetActorsInSelectionRectangle() to be able to call it outside Hud->DrawHUD()*/
	void GetActorsInSelectionRectangle(TSubclassOf<class AActor> ClassFilter,
		const FVector2D& FirstPoint, const FVector2D& SecondPoint, TArray<AActor*>& OutActors,
		bool bIncludeNonCollidingComponents, bool bActorMustBeFullyEnclosed);


	/* upper left Corner of the selection Box */
	FVector2D SelectionBoxStartPoint;

	AActor* GetSelectableActorUnderCursor();
	FVector2D GetScreenMousePosition();
	ATableTopHUD* GetHUD();




};
