// Fill out your copyright notice in the Description page of Project Settings.

#include "TTCharacterUIWidget.h"
#include "TableTopGame.h"
#include "Public/Units/ModelCharacter.h"





void UTTCharacterUIWidget::SetCharacter(AModelCharacter* ACharacter) 
{
	this->Character = ACharacter;
}