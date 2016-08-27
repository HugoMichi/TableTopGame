// Fill out your copyright notice in the Description page of Project Settings.

#include "TableTopGame.h"
#include "Public/UI/TableTopHUD.h"


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





