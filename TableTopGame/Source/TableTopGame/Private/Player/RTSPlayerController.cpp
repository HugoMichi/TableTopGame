// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Player/RTSPlayerController.h"
#include "TableTopGame.h"

#include "AI/Navigation/NavigationSystem.h"
#include "Public/Player/TableTopPlayerState.h"

ARTSPlayerController::ARTSPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ARTSPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);


	/*TArray<TSharedRef<SWindow>> widgetsUnderMouse;
	FSlateApplication::Get().LocateWindowUnderMouse(GetScreenMousePosition(), widgetsUnderMouse);
	if (widgetsUnderMouse.Num() > 0) {
		FInputModeCustom GameMode;
		GameMode.SetWidgetToFocus(widgetsUnderMouse[0]);
		SetInputMode(GameMode);
	}*/
	// keep updating the destination every tick while desired
	/*	if (bMoveToMouseCursor)
	{
	MoveToMouseCursor();
	}*/
}

void ARTSPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
	InputComponent->BindAction("Select", IE_Pressed, this, &ARTSPlayerController::StartSelectionUnderCursor);
	InputComponent->BindAction("Select", IE_Released, this, &ARTSPlayerController::EndSelectionUnderCursor);

	InputComponent->BindAction("TestPlayerState", EInputEvent::IE_Pressed, this, &ARTSPlayerController::OnTest);
	/*reference needed !!!!!
	set ConsumeInput = false Because MouseInput is needed in the Pawn*/
	FInputAxisBinding& mouseMoveX = InputComponent->BindAxis("MouseMoveX", this, &ARTSPlayerController::OnMouseMove);
	mouseMoveX.bConsumeInput = false;
	FInputAxisBinding& mouseMoveY = InputComponent->BindAxis("MouseMoveY", this, &ARTSPlayerController::OnMouseMove);
	mouseMoveY.bConsumeInput = false;
	FInputModeGameAndUI GameMode;
	GameMode.SetHideCursorDuringCapture(false);
	GameMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(GameMode);	//Not Allowed during Construction 
	InputComponent->BindAction("OpenMenu", EInputEvent::IE_Pressed, this, &ARTSPlayerController::OnOpenMenu);
	//MainMenu

	
	//InputComponent->BindAction("SetDestination", IE_Pressed, this, &ARTSPlayerController::OnSetDestinationPressed);
	//InputComponent->BindAction("SetDestination", IE_Released, this, &ARTSPlayerController::OnSetDestinationReleased);
	//Super::GetPawn();
	//InputComponent->BindAxis("MoveForward", this, &ARTSPlayerPawn::MoveCameraForward);
	//InputComponent->BindAxis("MoveRight", this, &ARTSPlayerPawn::MoveCameraRight);
	// support touch devices 
	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ARTSPlayerController::MoveToTouchLocation);
	//InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ARTSPlayerController::MoveToTouchLocation);
}

void ARTSPlayerController::OnOpenMenu() {
	/*UserInterface = CreateWidget<UMyMenuWidget>(this, UMyMenuWidget::StaticClass());
	FInputModeGameAndUI Mode;
	Mode.SetLockMouseToViewport(true);
	Mode.SetHideCursorDuringCapture(false);
	SetInputMode(Mode);
	UserInterface->AddToViewport(9999);*/
	//TODO::
}

void ARTSPlayerController::OnTest() 
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Test Function Called"));
	ATableTopPlayerState* ATTPlayerState = Cast<ATableTopPlayerState>(this->PlayerState);
	if (ATTPlayerState)
		ATTPlayerState->EndCurrentPhase();
}

void ARTSPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void ARTSPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ARTSPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const APawn = GetPawn();
	if (APawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, APawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}
void ARTSPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ARTSPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}


/*SELECTION FUNCTIONS*/
void ARTSPlayerController::StartSelectionUnderCursor()
{
	//TODO:: ERROR Handling what happens if 000 is returned ...
	SelectionBoxStartPoint = GetScreenMousePosition();
	FVector2D MousePos;
	if(GetScreenMousePosition(MousePos))
	{
		SelectionBoxStartPoint = MousePos;
		bBoundingBoxStarted = true;
	}
	

}

void ARTSPlayerController::EndSelectionUnderCursor()
{

	TArray<AActor*> outActors;
	if (!GetActorsInSelectionRect(outActors))
	{
		bBoundingBoxStarted = false;
		return;
	}

	if (!bAddToCurrentSelection) {
		NotifyAndEmptySelectedObjects();
	}
	for (AActor * actor : outActors) {
		check(actor);
		IStrategySelectionInterface* selectable = Cast<IStrategySelectionInterface>(actor);
		if (selectable) {
			SelectedObjects.Add(actor);
			selectable->Execute_OnSelectionGained(actor);
		}
	}
	bBoundingBoxStarted = false;
	OnSelectionChanged.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("EndSelected!!!!!"));

}

bool ARTSPlayerController::GetSelectionRect(FIntRect& OutSelectionRect)
{
	if (!bBoundingBoxStarted)
	{
		return false;
	}

	// Get mouse input.
	FVector2D MousePos;// = FVector2D(EForceInit::ForceInitToZero);
	if (!GetScreenMousePosition(MousePos))
	{
		return false;
	}

	OutSelectionRect = FIntRect(
		FIntPoint(SelectionBoxStartPoint.X, SelectionBoxStartPoint.Y),
		FIntPoint(MousePos.X, MousePos.Y));

	return true;
}
bool ARTSPlayerController::GetActorsInSelectionRect(TArray<AActor*>& OutActors)
{
	FIntRect OutSelectionRect;
	if (GetSelectionRect(OutSelectionRect)) {
		//TODO get a simpler Linetrace to work for small bounding box because its more efficient
		/*if (OutSelectionRect.Area() < 10)
		{
			GetActorsUnderCursor(APawn::StaticClass(), OutActors);
		}
		else {*/
			GetActorsInRectangle(APawn::StaticClass(), OutSelectionRect.Min, OutSelectionRect.Max, OutActors, false, false);
		//}
		if (OutActors.Num() > 0) {
			return true;
		}
	}	
	return false;
}
void ARTSPlayerController::GetActorsInRectangle(TSubclassOf<class AActor> ClassFilter, const FVector2D& FirstPoint, const FVector2D& SecondPoint, TArray<AActor*>& OutActors, bool bIncludeNonCollidingComponents, bool bActorMustBeFullyEnclosed)
{
	UE_LOG(LogTemp, Warning, TEXT("StartGetActor!!!!"));
	// Because this is a HUD function it is likely to get called each tick,
	// so make sure any previous contents of the out actor array have been cleared!
	OutActors.Empty();

	//Create Selection Rectangle from Points
	FBox2D SelectionRectangle(EForceInit::ForceInitToZero);

	//This method ensures that an appropriate rectangle is generated, 
	//		no matter what the coordinates of first and second point actually are.
	SelectionRectangle += FirstPoint;
	SelectionRectangle += SecondPoint;
	//The Actor Bounds Point Mapping
	const FVector BoundsPointMapping[8] =
	{
		FVector(1, 1, 1),
		FVector(1, 1, -1),
		FVector(1, -1, 1),
		FVector(1, -1, -1),
		FVector(-1, 1, 1),
		FVector(-1, 1, -1),
		FVector(-1, -1, 1),
		FVector(-1, -1, -1)
	};

	//~~~

	//For Each Actor of the Class Filter Type
	for (TActorIterator<AActor> Itr(GetWorld(), ClassFilter); Itr; ++Itr)
	{
		AActor* EachActor = *Itr;
		//Get Actor Bounds				//casting to base class, checked by template in the .h
		const FBox EachActorBounds = Cast<AActor>(EachActor)->GetComponentsBoundingBox(bIncludeNonCollidingComponents); /* All Components? */																								//Center
		const FVector BoxCenter = EachActorBounds.GetCenter();

		//Extents
		const FVector BoxExtents = EachActorBounds.GetExtent();

		// Build 2D bounding box of actor in screen space
		FBox2D ActorBox2D(EForceInit::ForceInitToZero);
		for (uint8 BoundsPointItr = 0; BoundsPointItr < 8; BoundsPointItr++)
		{
			// Project vert into screen space.
			FVector2D ProjectedWorldLocation;
			ProjectWorldLocationToScreen(BoxCenter + (BoundsPointMapping[BoundsPointItr] * BoxExtents), ProjectedWorldLocation);
			// Add to 2D bounding box
			ActorBox2D += FVector2D(ProjectedWorldLocation.X, ProjectedWorldLocation.Y);
		}

		//Selection Box must fully enclose the Projected Actor Bounds
		if (bActorMustBeFullyEnclosed)
		{
			if (SelectionRectangle.IsInside(ActorBox2D))
			{
				OutActors.Add(Cast<AActor>(EachActor));
			}
		}
		//Partial Intersection with Projected Actor Bounds
		else
		{
			if (SelectionRectangle.Intersect(ActorBox2D))
			{
				OutActors.Add(Cast<AActor>(EachActor));
			}
		}
	}UE_LOG(LogTemp, Warning, TEXT("EndGetActor!!!!"));
}
void ARTSPlayerController::GetActorsUnderCursor(TSubclassOf<class AActor> ClassFilter, TArray<AActor*>& OutActors)
{//TODO:: Expand with class Filters etc so that an overlapping environment is not blocking the selection 
	FHitResult Hit;
	if (GetHitResultUnderCursor(ECC_Visibility, false, Hit)) {
		if (Hit.bBlockingHit) {
			OutActors.Add(Hit.GetActor());
		}
	}
}
void ARTSPlayerController::NotifyAndEmptySelectedObjects()
{
	for (AActor * actor : SelectedObjects) 
	{
		check(actor);
		IStrategySelectionInterface* selectable = Cast<IStrategySelectionInterface>(actor);
		if (selectable)
			selectable->Execute_OnSelectionLost(actor);
	}
	SelectedObjects.Empty();
}

void ARTSPlayerController::StartAddToCurrentSelection()
{
	bAddToCurrentSelection = true;
}
void ARTSPlayerController::EndAddToCurrentSelection()
{
	bAddToCurrentSelection = false;
}

void ARTSPlayerController::ImitateAxisValue()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OnMouseMove: ! %f"), axisValue));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OnMouseMove: ! x: %f y: %f"), axisValues.X, axisValues.Y));

	FVector2D mousePosition;
	GetScreenMousePosition(mousePosition);
	axisValues = LastPosition - mousePosition;
	LastPosition = mousePosition;

}
void ARTSPlayerController::OnMouseMove(float axisValue)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OnMouseMove: ! %f"), axisValue));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OnMouseMove: ! x: %f y: %f"), axisValues.X, axisValues.Y));

	//UE_LOG(LogTemp, Warning, TEXT("OnMouseMove: ! %f"), axisValue);
	//UE_LOG(LogTemp, Warning, TEXT("OnMouseMove: ! x: %f y: %f"), axisValues.X, axisValues.Y);
	/*if (bBoundingBoxStarted)
	{//
		FVector2D secondPoint = GetScreenMousePosition();
		if (SelectionBoxStartPoint != secondPoint) {
			ATableTopHUD* hud = GetHUD();
			if (hud)
				hud->SelectionRect = FBox2D(SelectionBoxStartPoint, secondPoint);
		}
	}*/
}


bool ARTSPlayerController::GetScreenMousePosition(FVector2D& MousePosition)
{
#if PLATFORM_DESKTOP
	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (LocalPlayer && LocalPlayer->ViewportClient)
	{
		if(LocalPlayer->ViewportClient->GetMousePosition(MousePosition))
			return true;
	}
#endif

	return false;
}


FVector2D ARTSPlayerController::GetScreenMousePosition()
{	
	FVector2D mousePosition;
	//Get mouse position and screen size
	UGameViewportClient* gameViewport = GEngine->GameViewport;
	//Make sure viewport exists
	check(gameViewport);
	//Make sure the viewport has focus(contains the mouse)
	if (gameViewport->IsFocused(gameViewport->Viewport))
		gameViewport->GetMousePosition(mousePosition);
	return mousePosition;
}


ATableTopHUD * ARTSPlayerController::GetHUD()
{
	return Cast<ATableTopHUD>(MyHUD);
}



/*Easy Solution: Use a Mouseclick for all functions needed to use MouseMove 
this is not working !!!!!!!!! BUG in UE4 not going to be fixed*/
void FInputModeCustom::ApplyInputMode(FReply & SlateOperations, UGameViewportClient & GameViewportClient) const
{
	TSharedPtr<SViewport> ViewportWidget = GameViewportClient.GetGameViewportWidget();
	if (ViewportWidget.IsValid())
	{
		GameViewportClient.SetIgnoreInput(false);

		//GameViewportClient.SetMouseLockMode(MouseLockMode);
		//GameViewportClient.SetMouseLockMode(EMouseLockMode::LockAlways);

		SlateOperations.ReleaseMouseCapture();
		//GameViewportClient.SetCaptureMouseOnClick(EMouseCaptureMode::CaptureDuringMouseDown);
		//sets the viewport to caputre MouseInput after it is clicked
		//GameViewportClient.SetCaptureMouseOnClick(bConsumeCaptureMouseDown ? EMouseCaptureMode::CapturePermanently : EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown);
		
		GameViewportClient.SetHideCursorDuringCapture(false);//if true hides MouseCursor during click 
	
		TSharedRef<SViewport> ViewportWidgetRef = ViewportWidget.ToSharedRef();
		SlateOperations.UseHighPrecisionMouseMovement(ViewportWidgetRef);
		//SlateOperations.SetUserFocus(WidgetToFocus.ToSharedRef()); only use if WidgetRef is valid
		//SlateOperations.SetUserFocus(ViewportWidgetRef);// not needed
		SlateOperations.LockMouseToWidget(ViewportWidgetRef);//mouse cannot leave Viewport
		//SlateOperations.ReleaseMouseLock();// opposite to LockMouseToWidget
		if (this->WidgetToFocus.IsValid()) 
		{
			SlateOperations.CaptureMouse(this->WidgetToFocus.ToSharedRef());
		} else {
			SlateOperations.CaptureMouse(ViewportWidgetRef);//can be used instead of GameViewportClient.SetCaptureMouseOnClick
		}
		//SlateOperations.ReleaseMouseCapture();//no mouse movement capture in viewport

		}

}
