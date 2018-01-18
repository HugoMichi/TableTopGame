// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/UI/TableTopHUD.h"
#include "TableTopGame.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Blueprint/UserWidget.h"
#include "UI/TTMainUIWidget.h"

#include "Public/Player/RTSPlayerController.h"



ATableTopHUD::ATableTopHUD(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer) 
{
	// notice that at this point we can't guarantee that the playerController is actually constructed yet, so we can't get a reference to it
	static ConstructorHelpers::FClassFinder<UTTMainUIWidget> MainUIWidgetObj(TEXT("/Game/UI/TTMainUIWidget_UMG"));
	if (MainUIWidgetObj.Succeeded()) {
		MainUIWidgetBP = MainUIWidgetObj.Class;
	}
	else {
		// hudWidgetObj not found
		MainUIWidgetBP = nullptr;
	}
}

void ATableTopHUD::BeginPlay() {
	Super::BeginPlay();
	if (MainUIWidgetBP) {
		// the player controller should be constructed by now so we can get a reference to it
		MainUIWidget = CreateWidget<UTTMainUIWidget>(this->GetOwningPlayerController(), this->MainUIWidgetBP);
		MainUIWidget->AddToPlayerScreen();
		//this->GetOwningPlayerController()->PushInputComponent(InputComponent);
		//GetOwner().Pthis->InputComponent
	}
	
}


void ATableTopHUD::DrawHUD()
{
	Super::DrawHUD();


	DrawSelectionFrame();
	
	//if (bDrawSelectionRect) {
	//	/*DrawRect(FLinearColor::Blue,
	//		SelectionRect.Min.X, SelectionRect.Min.Y,
	//		SelectionRect.GetSize().X, SelectionRect.GetSize().Y);*/
	//	if (SelectionRect) {
	//		DrawRect(SelectionRect);
	//	}
	//}

}

void ATableTopHUD::DrawSelectionFrame()
{
	// Get selection frame.
	ARTSPlayerController* PlayerController = Cast<ARTSPlayerController>(PlayerOwner);

	if (!PlayerController)
	{
		return;
	}

	FIntRect SelectionFrame;
	if (!PlayerController->GetSelectionRect(SelectionFrame))
	{
		return;
	}

	// Draw selection frame.
	NotifyDrawSelectionFrame(
		SelectionFrame.Min.X,
		SelectionFrame.Min.Y,
		SelectionFrame.Width(),
		SelectionFrame.Height());
}
void ATableTopHUD::NotifyDrawSelectionFrame(float ScreenX, float ScreenY, float Width, float Height)
{
	ReceiveDrawSelectionFrame(ScreenX, ScreenY, Width, Height);

}
void ATableTopHUD::ReceiveDrawSelectionFrame_Implementation(float ScreenX, float ScreenY, float Width, float Height)
{
	DrawRect(SelectionRectColor, ScreenX, ScreenY, Width, Height);
	DrawLine(ScreenX, ScreenY, ScreenX + Width, ScreenY, SelectionRectLineColor);//Bottom Line
	DrawLine(ScreenX, ScreenY, ScreenX, ScreenY + Height, SelectionRectLineColor);//Left Line
	DrawLine(ScreenX, ScreenY + Height, ScreenX + Width, ScreenY + Height, SelectionRectLineColor);//Top Line
	DrawLine(ScreenX + Width, ScreenY, ScreenX + Width, ScreenY + Height, SelectionRectLineColor);//Right Line
}






template<typename T>
T* ATableTopHUD::openWidget(FString widget_name) {
	FStringClassReference big_inventory_widget_ref(widget_name);
	if (UClass* w = big_inventory_widget_ref.TryLoadClass<T>()) {
		T* widget = CreateWidget<T>(GetWorld(), w);
		widget->AddToViewport();
		return widget;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("widget %s is not found"), *widget_name);
		return NULL;
	}
}





