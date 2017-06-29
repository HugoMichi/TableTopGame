// Fill out your copyright notice in the Description page of Project Settings.

#include "TableTopGame.h"
#include "Utility_BP.h"



void UUtility_BP::Test() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BLUUUUB"));
}

//NO Templated Functions in the cpp file they dont work. implement in .h file !!!!!!!!!!
