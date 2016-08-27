// Fill out your copyright notice in the Description page of Project Settings.

#include "TableTopGame.h"
#include "Public/Player/RTSPlayerPawn.h"

ARTSPlayerPawn::ARTSPlayerPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for player capsule
	//GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction, except for the yaw axis
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Disable Jump and Crouch actions
	bAddDefaultMovementBindings = false;

	EnableInput(Cast<APlayerController>(GetController()));


	// Configure character movement
	/*GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;*/

	// Create a camera boom...
	CameraBoom = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this,TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = false; // Rotate arm relative to character
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
										  // Move camera boom with character only on yaw rotation
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = true;

	// Enables camera lag - matter of taste
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bEnableCameraRotationLag = true;

	// Disable collisions
	GetCollisionComponent()->bGenerateOverlapEvents = false;
	GetCollisionComponent()->SetCollisionProfileName("NoCollision");

	// Create a camera...
	TopDownCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this,TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	USpectatorPawnMovement* spectatorMovement = Cast<USpectatorPawnMovement>(GetMovementComponent());
	if (spectatorMovement) {
		relativeMaxSpeed = CameraBoom->TargetArmLength / spectatorMovement->GetMaxSpeed();
	}
}

void ARTSPlayerPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	check(InputComponent);

	//Bind Mouse Wheel Zooming Actions
	InputComponent->BindAxis("CameraZoom", this, &ARTSPlayerPawn::OnZoomAction);

	//Bind WASD Movement
	InputComponent->BindAxis("MoveForward", this, &ARTSPlayerPawn::MoveCharacterForward);
	InputComponent->BindAxis("MoveRight", this, &ARTSPlayerPawn::MoveCharacterRight);
	InputComponent->BindAction("RotateCamera", EInputEvent::IE_Pressed, this, &ARTSPlayerPawn::OnLookAroundStart);
	InputComponent->BindAction("RotateCamera", EInputEvent::IE_Released, this, &ARTSPlayerPawn::OnLookAroundStop);
	InputComponent->BindAxis("MouseMoveX", this, &ARTSPlayerPawn::OnMouseHorizontal);
	InputComponent->BindAxis("MouseMoveY", this, &ARTSPlayerPawn::OnMouseVertical);



	//Cast<APlayerController>(GetController())->PushInputComponent(InputComponent);
}

void ARTSPlayerPawn::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	DoEdgeMovement();
}

void ARTSPlayerPawn::recalculateMaxSpeed() {
	if (bRelativeMaxSpeedEnabled) {
		USpectatorPawnMovement* spectatorMovement = Cast<USpectatorPawnMovement>(GetMovementComponent());
		if (spectatorMovement)
			spectatorMovement->MaxSpeed = CameraBoom->TargetArmLength / relativeMaxSpeed;
	}
}
void ARTSPlayerPawn::OnZoomAction(float direction)
{
	ChangeCameraArmLength(-direction);
	recalculateMaxSpeed();
}

void ARTSPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	EnableInput(Cast<APlayerController>(GetController()));
}
void ARTSPlayerPawn::ChangeCameraArmLength(float changeValue)
{
	CameraBoom->TargetArmLength += changeValue * ZoomRate; // Change 100.0f with zoom speed property
}

void ARTSPlayerPawn::RotateCameraArm(FRotator rotation)
{
	rotation = (CameraBoom->RelativeRotation + rotation);
	rotation.Roll = 0;
	rotation.Pitch = FMath::ClampAngle(rotation.Pitch, -85.0f, -5.0f);
	//CameraBoom->AddRelativeRotation(rotation);
	CameraBoom->SetRelativeRotation(rotation);

}

void ARTSPlayerPawn::MoveCharacterForward(float changeValue)
{
	//Gets the ForwardVector of the CameraBoom ignoring Pitch and Roll
	AddMovementInput(FRotator(0.0f, CameraBoom->ComponentToWorld.Rotator().Yaw, 0.0f).Vector(), changeValue);

	//MoveForward(changeValue);
}

void ARTSPlayerPawn::MoveCharacterRight(float changeValue)
{					//Gets the RightHandVector of the CameraBoom ignoring Pitch and Roll
	AddMovementInput(FRotator(0.0f, CameraBoom->ComponentToWorld.Rotator().Yaw + 90.0f, 0.0f).Vector(), changeValue);
	//MoveRight(changeValue);
}

void ARTSPlayerPawn::OnMouseHorizontal(float axisValue)
{
	if (lookAroundEnabled)
	{
		//AddControllerYawInput(axisValue);

		RotateCameraArm(FRotator(0.0f, axisValue, 0.0f));
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController) {
			Cast<ULocalPlayer>(PlayerController->Player)->ViewportClient->Viewport->SetMouse(mouseLockPositionX, mouseLockPositionY);
		}
	}
}

void ARTSPlayerPawn::OnMouseVertical(float axisValue)
{

	if (lookAroundEnabled)
	{
		RotateCameraArm(FRotator(axisValue, 0.0f, 0.0f));
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController) {
			Cast<ULocalPlayer>(PlayerController->Player)->ViewportClient->Viewport->SetMouse(mouseLockPositionX, mouseLockPositionY);
		}
	}
}

void ARTSPlayerPawn::OnLookAroundStart()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	//Lock mouse cursor
	lookAroundEnabled = true;
	if (PlayerController) {
		PlayerController->bShowMouseCursor = false;
		ULocalPlayer* localPlayer = Cast<ULocalPlayer>(PlayerController->Player);
		if (localPlayer) {
			mouseLockPositionX = localPlayer->ViewportClient->Viewport->GetMouseX();
			mouseLockPositionY = localPlayer->ViewportClient->Viewport->GetMouseY();
		}
	}
}
void ARTSPlayerPawn::OnLookAroundStop()
{
	//Unlock mouse cursor
	lookAroundEnabled = false;
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	//Lock mouse cursor
	if (PlayerController) {
		PlayerController->bShowMouseCursor = true;
	}
}
void ARTSPlayerPawn::DoEdgeMovement()
{
	if (!bEdgeMovementEnabled)
		return;
	//Create variables to hold mouse position and screen size
	FVector2D mousePosition;
	FVector2D viewportSize;

	//Get mouse position and screen size
	UGameViewportClient* gameViewport = GEngine->GameViewport;

	//Make sure viewport exists
	check(gameViewport);
	gameViewport->GetViewportSize(viewportSize);

	//Make sure the viewport has focus(contains the mouse)
	if (gameViewport->IsFocused(gameViewport->Viewport) && gameViewport->GetMousePosition(mousePosition))
	{	/*the closer the mouse is to the boundary the faster the movement*/
		float movementFactor = 0;
		//Check if the mouse is at the left or right edge of the screen and move accordingly
		if (mousePosition.X < EdgeMovementBoundary)
		{
			movementFactor = (EdgeMovementBoundary - mousePosition.X) / (0.5*EdgeMovementBoundary);
			MoveCharacterRight(-1.0f * movementFactor);
		}
		else if (viewportSize.X - mousePosition.X < EdgeMovementBoundary)
		{
			movementFactor = (EdgeMovementBoundary - (viewportSize.X - mousePosition.X)) / (0.5*EdgeMovementBoundary);
			MoveCharacterRight(1.0f * movementFactor);
		}

		//Check if the mouse is at the top or bottom edge of the screen and move accordingly
		if (mousePosition.Y < EdgeMovementBoundary)
		{
			movementFactor = (EdgeMovementBoundary - mousePosition.Y) / (0.5*EdgeMovementBoundary);
			MoveCharacterForward(1.0f * movementFactor);
		}
		else if (viewportSize.Y - mousePosition.Y < EdgeMovementBoundary)
		{
			movementFactor = (EdgeMovementBoundary - (viewportSize.Y - mousePosition.Y)) / (0.5*EdgeMovementBoundary);
			MoveCharacterForward(-1.0f * movementFactor);
		}
	}
}