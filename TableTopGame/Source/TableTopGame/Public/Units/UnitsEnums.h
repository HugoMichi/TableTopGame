// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"




UENUM(BlueprintType)
enum class EAttributes : uint8
{
	A_WeaponsSkill		UMETA(DisplayName = "WeaponsSkill"),
	A_BallisticSkill	UMETA(DisplayName = "BallisticSkill"),
	A_Strength			UMETA(DisplayName = "Strength"),
	A_Toughness			UMETA(DisplayName = "Toughness"),
	A_Wounds			UMETA(DisplayName = "Wounds"),
	A_Initiative		UMETA(DisplayName = "Initiative"),
	A_Attacks			UMETA(DisplayName = "Attacks"),
	A_Leadership		UMETA(DisplayName = "Leadership"),
	A_ArmourSave		UMETA(DisplayName = "ArmourSave")
};


UENUM(BlueprintType)
enum class EAttachPointType : uint8
{
	APT_MainWeapon	UMETA(DisplayName = "Both Hands Main Weapon"),
	APT_LeftHandWeapon  	UMETA(DisplayName = "Left Hand"),
	APT_RightHandWeapon 	UMETA(DisplayName = "Right Hand"),
	APT_Grenades	UMETA(DisplayName = "Grenade"),
	APT_Belt	UMETA(DisplayName = "Belt"),
};