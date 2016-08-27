// Fill out your copyright notice in the Description page of Project Settings.

#include "TableTopGame.h"
#include "Public/Player/RTSPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"

ARTSPlayerController::ARTSPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

}

void ARTSPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

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
	InputComponent->BindAction("Select", IE_Pressed, this, &ARTSPlayerController::OnSetSelectedUnderCursorPressed);
	InputComponent->BindAction("Select", IE_Released, this, &ARTSPlayerController::OnSetSelectedUnderCursorReleased);

	/*reference needed !!!!!
	set ConsumeInput = false Because MouseInput is needed in the Pawn*/
	FInputAxisBinding& mouseMoveX = InputComponent->BindAxis("MouseMoveX", this, &ARTSPlayerController::OnMouseMove);
	mouseMoveX.bConsumeInput = false;
	FInputAxisBinding& mouseMoveY = InputComponent->BindAxis("MouseMoveY", this, &ARTSPlayerController::OnMouseMove);
	mouseMoveY.bConsumeInput = false;

	//InputComponent->BindAction("SetDestination", IE_Pressed, this, &ARTSPlayerController::OnSetDestinationPressed);
	//InputComponent->BindAction("SetDestination", IE_Released, this, &ARTSPlayerController::OnSetDestinationReleased);
	//Super::GetPawn();
	//InputComponent->BindAxis("MoveForward", this, &ARTSPlayerPawn::MoveCameraForward);
	//InputComponent->BindAxis("MoveRight", this, &ARTSPlayerPawn::MoveCameraRight);
	// support touch devices 
	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ARTSPlayerController::MoveToTouchLocation);
	//InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ARTSPlayerController::MoveToTouchLocation);
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
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

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
AActor* ARTSPlayerController::GetSelectableActorUnderCursor()
{	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if (Hit.bBlockingHit)
	{
		IStrategySelectionInterface* selectable = Cast<IStrategySelectionInterface>(Hit.GetActor());
		if (selectable) {
			selectable->Execute_OnSelectionGained(Hit.GetActor());
			return Hit.GetActor();
		}
	}return NULL;
}
void ARTSPlayerController::OnSetSelectedUnderCursorPressed()
{
	//TODO:: ERROR Handling what happens if 000 is returned ...
	SelectionBoxStartPoint = GetScreenMousePosition();
	bBoundingBoxStarted = true;
}

void ARTSPlayerController::OnSetSelectedUnderCursorReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("StartSelected!!!!!"));
	bBoundingBoxStarted = false;
	/*setting Selection box to default*/
	ATableTopHUD* hud = GetHUD();
	TArray<AActor*> outActors;
	if (hud) {
		//TODO:: is Canvas Draw Function !!! should be called only during Hud-DrawHud()!!!!!
		GetActorsInSelectionRectangle(APawn::StaticClass(), hud->SelectionRect.Min, hud->SelectionRect.Max, outActors, false, false);
		hud->SelectionRect = FBox2D(FVector2D(), FVector2D());
	}
	if (!bAddToCurrentSelection) {
		NotifyAndEmptySelectedObjects();
		//SelectedObjects.Empty();
	}
	for (AActor * actor : outActors) {
		IStrategySelectionInterface* selectable = Cast<IStrategySelectionInterface>(actor);
		if (selectable) {
			SelectedObjects.Add(actor);
			selectable->Execute_OnSelectionGained(actor);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Selected!!!!!"));

	for (AActor * actor : SelectedObjects) {
		//UE_LOG(LogTemp, Warning, TEXT("SelectedName: %s"),*actor->GetName());
	}
	/*AActor* selected = GetSelectableActorUnderCursor();
	if (selected) {
	if (!bAddToCurrentSelection)
	SelectedObjects.Empty();
	SelectedObjects.Add(selected);
	}*/
	UE_LOG(LogTemp, Warning, TEXT("EndSelected!!!!!"));
}

void ARTSPlayerController::GetActorsInSelectionRectangle(TSubclassOf<class AActor> ClassFilter, const FVector2D& FirstPoint, const FVector2D& SecondPoint, TArray<AActor*>& OutActors, bool bIncludeNonCollidingComponents, bool bActorMustBeFullyEnclosed)
{
	UE_LOG(LogTemp, Warning, TEXT("StartGetActor!!!!"));
	// Because this is a HUD function it is likely to get called each tick,
	// so make sure any previous contents of the out actor array have been cleared!
	OutActors.Empty();

	//Create Selection Rectangle from Points
	FBox2D SelectionRectangle(0);

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
		const FBox EachActorBounds = Cast<AActor>(EachActor)->GetComponentsBoundingBox(bIncludeNonCollidingComponents); /* All Components? */

																														//Center
		const FVector BoxCenter = EachActorBounds.GetCenter();

		//Extents
		const FVector BoxExtents = EachActorBounds.GetExtent();

		// Build 2D bounding box of actor in screen space
		FBox2D ActorBox2D(0);
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

void ARTSPlayerController::OnMouseMove(float axisValue)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OnMouseMove: ! %f"), axisValue));
	if (bBoundingBoxStarted)
	{
		FVector2D secondPoint = GetScreenMousePosition();
		if (SelectionBoxStartPoint != secondPoint) {
			ATableTopHUD* hud = GetHUD();
			if (hud)
				hud->SelectionRect = FBox2D(SelectionBoxStartPoint, secondPoint);
		}
	}
}
void ARTSPlayerController::NotifyAndEmptySelectedObjects()
{
	for (AActor * actor : SelectedObjects) {
		IStrategySelectionInterface* selectable = Cast<IStrategySelectionInterface>(actor);
		if (selectable)
			selectable->Execute_OnSelectionLost(actor);
	}SelectedObjects.Empty();
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




