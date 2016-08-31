// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpectatorPawn.h"
#include "RTSPlayerPawn.generated.h"

/**
*
*/
UCLASS()
class TABLETOPGAME_API ARTSPlayerPawn : public ASpectatorPawn
{
	GENERATED_BODY()
		
		/** Camera Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
public:
	ARTSPlayerPawn(const FObjectInitializer& ObjectInitializer);

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	virtual void BeginPlay() override;
	void ChangeCameraArmLength(float changeValue);
	void RotateCameraArm(FRotator rotation);
	void MoveCharacterForward(float changeValue);
	void MoveCharacterRight(float changeValue);
	void OnZoomAction(float direction);
	void OnLookAroundStart();
	void OnLookAroundStop();
	/**/
	void OnMouseVertical(float axisValue);
	void OnMouseHorizontal(float axisValue);
	void DoEdgeMovement();

	/*If true the MaxSpeed of the Movement Changes according to the Zoomfactor of the Pawn*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StrategyGameMovement)
		bool bRelativeMaxSpeedEnabled = true;

	/** Base lookup rate, in deg/sec. Other scaling may affect final lookup rate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StrategyGameMovement)
		float ZoomRate = 100.0;
	/** EdgeMovement Boundary */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float EdgeMovementBoundary = 30.0;
	/** Enable EdgeMovement*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		bool bEdgeMovementEnabled = true;



	/** Tick Function, Called Every Frame */
	UFUNCTION()
		virtual void Tick(float deltaSeconds) override;
private:
	/** Sets up player inputs
	*    @param InputComponent - Input Component
	*/
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

private:
	bool lookAroundEnabled = false;
	int32 mouseLockPositionX;
	int32 mouseLockPositionY;
	/*relation between Zoom and MaxSpeed if bRelativeMaxSpeedEnabled = true
	MaxSpeed = CameraBoom->Armlength/relativeMaxSpeed
	set in Constructor */
	float relativeMaxSpeed;
	/*recalculates the USpectatorPawnMovement-> MaxSpeed*/
	void recalculateMaxSpeed();

};
