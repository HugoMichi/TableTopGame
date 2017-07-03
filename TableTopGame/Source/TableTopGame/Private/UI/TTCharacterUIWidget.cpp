// Fill out your copyright notice in the Description page of Project Settings.

#include "TableTopGame.h"
#include "Public/Units/ModelCharacter.h"
#include "TTCharacterUIWidget.h"




void UTTCharacterUIWidget::SetCharacter(AModelCharacter* ACharacter) 
{
	this->Character = ACharacter;
}