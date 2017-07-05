// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
struct FModifierInfo;
#include "GameFramework/Character.h"
#include "Public/Units/RTSCharacter.h"
#include "Public/Units/TTItem.h"
#include "Public/Units/TTAttribute.h"

//#include "Public/Units/TTItem.h"
//#include "UnitsEnums.h"
//#include "Public/UI/TTCharacterUIWidget.h"
#include "ModelCharacter.generated.h"

//struct FModifierInfo;
class ATTItem;
class UTTCharacterUIWidget;
class ATTWeapon;
//struct FAttribute;


USTRUCT(BlueprintType)
struct TABLETOPGAME_API FD6DiceResult
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DiceResult)
		int	numberOFSuccesDice;
};



UCLASS()
class TABLETOPGAME_API AModelCharacter : public ARTSCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AModelCharacter(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	FName GetUnitName() {
		return UnitName;
	}

	/*Movement Phase*/
	UFUNCTION()
	bool MoveTo(const FVector Location);


	/*Shooting Phase*/
	UFUNCTION()
	void ShowShootingRange();

	UFUNCTION()
	void ShootAtTarget(AModelCharacter* Target);
	void FireOverwatchAtTarget(AModelCharacter* Target);
	/*returns true if new weapon has been selected*/
	UFUNCTION()
	bool SelectWeapon(uint8 WeaponArrayPos);

private:
	bool HasLineOfSightTo(AModelCharacter * Target);
	bool IsInWeaponRangeTo(AModelCharacter * Target);
	uint16 RollToHit(uint16 NumberOfShots);
public:

	/*Assault Phase*/
	bool ChargeEnemyUnit(AModelCharacter * Target);
	void ChargeMoveToUnit(AModelCharacter * Target);
	void FightCloseCombat(AModelCharacter * Target);
private:
	void FightInitiativeStep(AModelCharacter * Target);
	void PileIn(AModelCharacter * Target);
	uint16 RollToHit(uint16 NumberOfAttacks, uint8 TargetWeaponSkill);
	uint16 AllocateWoundsCloseCombatFrom(AModelCharacter* Shooter, uint16 NumberOfWounds, uint8 WeaponStreangth, uint8 ArmorPiercing);
	uint8 DetermineAssaultResults();

	/*Assault Phase END*/

	/*Wound Handling*/
	uint16 RollToWound(uint16 NumberOfHits, uint8 WeaponStrength);
public:
	uint16 AllocateWoundsFrom(AModelCharacter* Shooter, uint16 NumberOfWounds, uint8 WeaponStreangth, uint8 ArmorPiercing);

private:
	uint16 TakeSaves(uint8 WeaponArmorPiercing, uint16 NumberOfWounds);
	void ModelDies();
	uint8 GetBestSave(uint8 WeaponArmorPiercing);
	TArray<uint8> GetD6DiceRoll(uint16 NumberOfDices);


public:
	/* Delegates*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttributesChanged);
	UPROPERTY(BlueprintAssignable, Category = "ModelAttributes")
	FAttributesChanged OnAttributesChanged;

	UFUNCTION(BlueprintCallable, Category = "ModelAttributes")
	void AddAttributeModifier(struct FModifierInfo& Modifier);

	UFUNCTION(BlueprintCallable, Category = "ModelAttributes")
	void RemoveAttributeModifier(struct FModifierInfo& Modifier);
protected:	
	/*Model Attributes*/
	UFUNCTION(BlueprintCallable, Category = "ModelAttributes")
	FAttribute& GetAttributeOnEnum(EAttributes type);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelAttributes)
	FName UnitName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ModelAttributes")
	FAttribute WeoponsSkill;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ModelAttributes")
	FAttribute BallisticSkill;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ModelAttributes")
	FAttribute Strength;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ModelAttributes")
	FAttribute Toughness;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ModelAttributes")
	FAttribute Wounds;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ModelAttributes")
	FAttribute Initiative;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ModelAttributes")
	FAttribute Attacks;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ModelAttributes")
	FAttribute Leadership;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ModelAttributes")
	FAttribute ArmourSave;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ModelAttributes")
	uint8 InvulnerableSave;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ModelAttributes")
	uint8 CoverSave;

	uint8 WoundsTakenThisPhase = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ModelAttributes")
	TArray<ATTWeapon*> Weapons;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ModelAttributes")
	ATTWeapon* CurrentWeapon;

	
	/*UI Representation override from RTSChar	*/
	//*Used for displaying Information of the unit in the ui */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UTTCharacterUIWidget> UIWidgetBP;

	UTTCharacterUIWidget* UIWidget;
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Selection")
	UUserWidget*  GetUIWidget();//TODO: Test if this or parent Version is called when used in interface
};
