// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TTMainUIWidget.h"
#include "TableTopHUD.generated.h"

/**
 * 
 */
UCLASS()
class TABLETOPGAME_API ATableTopHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATableTopHUD(const FObjectInitializer& ObjectInitializer);

	// Begin HUD interface
	virtual void DrawHUD() override;
	// End HUD interface

	//handle Selection Rectangle functionality
		
		/** Event for drawing the selection frame because the mouse is being dragged. */
		virtual void NotifyDrawSelectionFrame(float ScreenX, float ScreenY, float Width, float Height);

		/** Event for drawing the selection frame because the mouse is being dragged. */
		UFUNCTION(BlueprintNativeEvent, Category = "RTS", meta = (DisplayName = "DrawSelectionFrame"))
		void ReceiveDrawSelectionFrame(float ScreenX, float ScreenY, float Width, float Height);

	private:
		UPROPERTY(EditDefaultsOnly)
		FLinearColor SelectionRectColor;
		UPROPERTY(EditDefaultsOnly)
		FLinearColor SelectionRectLineColor;
		/** Draws the current selection frame if mouse is being dragged. */
		void DrawSelectionFrame();

private:
	/*InventoryWidget Blueprint reference*/
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTTMainUIWidget> MainUIWidgetBP;



	/*usagee.g.:  openWidget<UUserWidget>(TEXT("/Game/Sandbox/UI/W_SystemInfo.W_SystemInfo_C"));*/
	template<typename T>
	T* openWidget(FString widget_name);
public:
	UTTMainUIWidget* MainUIWidget;

	//class UClass * MainUIWidgetClass;
	//class UTTMainUIWidget * MainUIWidget;

	virtual void BeginPlay() override;
};
