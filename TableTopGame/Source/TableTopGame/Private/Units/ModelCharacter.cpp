// Fill out your copyright notice in the Description page of Project Settings.

#include "TableTopGame.h"
#include "TTWeapon.h"
#include "Public/Player/TTPlayerController.h"
#include "Public/TTGameMode.h"
#include "Public/Units/ModelCharacter.h"


// Sets default values
AModelCharacter::AModelCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void AModelCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AModelCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AModelCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

bool AModelCharacter::MoveTo(const FVector Location)
{
	return false;
}


/*ShootingPhase*/
void AModelCharacter::ShowShootingRange()
{
}

void AModelCharacter::ShootAtTarget(AModelCharacter * Target)
{
	if (HasLineOfSightTo(Target)&& IsInWeaponRangeTo(Target)) {
		FWeaponSheet* SelectedWeapon = CurrentWeapon->CurrentWeaponSheet;
		check(SelectedWeapon)
		if (!SelectedWeapon)
			return;
		uint16 causedWounds = Target->RollToWound(RollToHit(SelectedWeapon->NumberOfShots), SelectedWeapon->Strength);
		Target->AllocateWoundsFrom(this, causedWounds, SelectedWeapon->Strength, SelectedWeapon->ArmorPiercing);
		
	}
}

void AModelCharacter::FireOverwatchAtTarget(AModelCharacter * Target)
{
}


bool AModelCharacter::SelectWeapon(uint8 WeaponArrayPos)
{
	if (Weapons.IsValidIndex(WeaponArrayPos)) {
		CurrentWeapon = Weapons[WeaponArrayPos];
		return true;
	}
	return false;
}

bool AModelCharacter::HasLineOfSightTo(AModelCharacter * Target)
{	
	//TODO:: Do Linetrace from Head to enemy unit ....
	return false;
}

bool AModelCharacter::IsInWeaponRangeTo(AModelCharacter * Target)
{	
	//TODO:: RangeCheck 
	return false;
}

uint16 AModelCharacter::RollToHit(uint16 NumberOfShots)
{
	TArray<uint8> randomArray = GetD6DiceRoll(NumberOfShots);
	int succesfulHit = 0;
	int valueToHit = FMath::Clamp( 7 - BallisticSkill.FinalValue, 2, 7);
	for (uint8 wound : randomArray) {
		if (wound >= valueToHit)
			succesfulHit++;
	}
	return succesfulHit;
}
bool AModelCharacter::ChargeEnemyUnit(AModelCharacter * Target)
{
	return false;
}
void AModelCharacter::ChargeMoveToUnit(AModelCharacter * Target)
{
}
void AModelCharacter::FightCloseCombat(AModelCharacter * Target)
{
}
void AModelCharacter::FightInitiativeStep(AModelCharacter * Target)
{
}
void AModelCharacter::PileIn(AModelCharacter * Target)
{
}
uint16 AModelCharacter::RollToHit(uint16 NumberOfAttacks, uint8 TargetWeaponSkill)
{
	return uint16();
}
uint16 AModelCharacter::AllocateWoundsCloseCombatFrom(AModelCharacter * Shooter, uint16 NumberOfWounds, uint8 WeaponStreangth, uint8 ArmorPiercing)
{
	return uint16();
}
uint8 AModelCharacter::DetermineAssaultResults()
{
	return uint8();
}
/*ShootingPhase END */


/*Wound Handling */
uint16 AModelCharacter::RollToWound(uint16 NumberOfHits, uint8 WeaponStrength)
{
	TArray<uint8> randomArray = GetD6DiceRoll(NumberOfHits);
	int succesfulWound = 0;
	int valueToWound = FMath::Clamp(4 +Toughness.FinalValue - WeaponStrength,2,7);
	for (uint8 wound : randomArray) {
		if (wound >= valueToWound)
			succesfulWound++;
	}
	return succesfulWound;
}

uint16 AModelCharacter::AllocateWoundsFrom(AModelCharacter * Shooter, uint16 NumberOfWounds, uint8 WeaponStrength,uint8 ArmorPiercing)
{
	//GetClosestModelsInUnitWithSameSave.....
	int WoundsTaken = TakeSaves(ArmorPiercing, NumberOfWounds);
	if (WoundsTaken > 0) {
		Wounds.AddModifier(FAttributeModifier(EAttributeModifierType::AMT_Subtract, WoundsTaken, Shooter->GetUnitName()));
		WoundsTakenThisPhase += WoundsTaken;
		if (Wounds.FinalValue <= 0)
			ModelDies();
		}
	return WoundsTaken;
}

uint16 AModelCharacter::TakeSaves(uint8 WeaponArmorPiercing, uint16 NumberOfWounds)
{
	uint8 bestSave = GetBestSave(WeaponArmorPiercing);
	TArray<uint8> randomArray = GetD6DiceRoll(NumberOfWounds);
	int succesfulSaves = 0;
	for (uint8 save : randomArray) {
		if (save >= bestSave)
			succesfulSaves++;
	}
	//GetWorld()->GetAuthGameMode<ATTGameMode>()->BroadcastDiceRoll(this, TEXT("Take Saves"),randomArray, bestSave, true);
		return succesfulSaves;

}

void AModelCharacter::ModelDies()
{
}

uint8 AModelCharacter::GetBestSave(uint8 WeaponArmorPiercing)
{	uint8 bestSave = 7;
	/*ArmourSave is not pierced by AP*/
	if(ArmourSave.GetFinalValue() < WeaponArmorPiercing) {
		bestSave = ArmourSave.GetFinalValue();
	}
	if (InvulnerableSave < bestSave) {
		bestSave = InvulnerableSave;
	}
	if (CoverSave < bestSave) {
		bestSave = CoverSave;
	}
	return bestSave;
}

TArray<uint8> AModelCharacter::GetD6DiceRoll(uint16 NumberOfDices)
{
	TArray<uint8> randomArray = TArray<uint8>();
	for (int i = 0; i < NumberOfDices;i++) {
		randomArray.Add(FMath::RandRange(0, 6));
	}
	return randomArray;
}


