// Fill out your copyright notice in the Description page of Project Settings.
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Public/StrategySelectionInterface.h"
#include "Public/UI/TableTopHUD.h"
#include "RTSPlayerController.generated.h"




struct  TABLETOPGAME_API FInputModeCustom : public FInputModeDataBase
{
	/** Widget to focus */
	FInputModeCustom& SetWidgetToFocus(TSharedPtr<SWidget> InWidgetToFocus) { WidgetToFocus = InWidgetToFocus; return *this; }

	/** Whether to lock the mouse to the viewport */
	DEPRECATED(4.13, "Mouse locking behavior is now controlled by an enum. Please use SetLockMouseToViewportBehavior(...) instead.")
	FInputModeCustom& SetLockMouseToViewport(bool InLockMouseToViewport) { return SetLockMouseToViewportBehavior(InLockMouseToViewport ? EMouseLockMode::LockOnCapture : EMouseLockMode::DoNotLock); }

	/** Sets the mouse locking behavior of the viewport */
	FInputModeCustom& SetLockMouseToViewportBehavior(EMouseLockMode InMouseLockMode) { MouseLockMode = InMouseLockMode; return *this; }

	/** Whether to hide the cursor during temporary mouse capture caused by a mouse down */
	FInputModeCustom& SetHideCursorDuringCapture(bool InHideCursorDuringCapture) { bHideCursorDuringCapture = InHideCursorDuringCapture; return *this; }
	/** Whether the mouse down that causes capture should be consumed, and not passed to player input processing */
	FInputModeCustom& SetConsumeCaptureMouseDown(bool InConsumeCaptureMouseDown) { bConsumeCaptureMouseDown = InConsumeCaptureMouseDown; return *this; }

	FInputModeCustom()
		: WidgetToFocus()
		, MouseLockMode(EMouseLockMode::DoNotLock)
		, bHideCursorDuringCapture(false)
		,bConsumeCaptureMouseDown(true)
	{}

protected:

	TSharedPtr<SWidget> WidgetToFocus;
	EMouseLockMode MouseLockMode;
	bool bHideCursorDuringCapture;
	bool bConsumeCaptureMouseDown;
	virtual void ApplyInputMode(FReply& SlateOperations, class UGameViewportClient& GameViewportClient) const override;
};











/*Delegates*/
/*Broadcast whenever the selection changes*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSelectionChanged);

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

	//
	void OnOpenMenu();

	//TestFunction
	void OnTest();


	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	UPROPERTY(BlueprintAssignable, Category = Selection)
	FSelectionChanged OnSelectionChanged;

	void OnSetSelectedUnderCursorPressed();
	void OnSetSelectedUnderCursorReleased();

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	void OnMouseMove(float axisValue);

protected:
	/*imitate axisValue of MouseInput because its consumed by UI Widgets*/
	FVector2D LastPosition;
	FVector2D axisValues;
	void ImitateAxisValue();
	/*Selection Properties and function*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Selection")
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
	bool GetScreenMousePosition(FVector2D& MousePosition);
	FVector2D GetScreenMousePosition();
	ATableTopHUD* GetHUD();




};
