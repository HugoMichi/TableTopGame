// Fill out your copyright notice in the Description page of Project Settings.


#include "TableTopGame.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Blueprint/UserWidget.h"
#include "UI/TTMainUIWidget.h"
#include "Public/UI/TableTopHUD.h"


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
		MainUIWidget->AddToViewport();
	}
}


void ATableTopHUD::DrawHUD()
{
	Super::DrawHUD();
	if (bDrawSelectionRect) {
		DrawRect(FLinearColor::Blue,
			SelectionRect.Min.X, SelectionRect.Min.Y,
			SelectionRect.GetSize().X, SelectionRect.GetSize().Y);
	}

}

void ATableTopHUD::SetSelectionRect(FVector2D startPoint, FVector2D endPoint)
{
	SelectionRect = FBox2D(startPoint, endPoint);
}





