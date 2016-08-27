// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TTWeapon.generated.h"


UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	WT_Melee	UMETA(DisplayName = "Melee"),
	WT_Heavy  	UMETA(DisplayName = "Heavy"),
	WT_RapidFire 	UMETA(DisplayName = "Rapid Fire"),
	WT_Assault	UMETA(DisplayName = "Assault"),
	WT_Ordnance 	UMETA(DisplayName = "Ordnance"),
	WT_Pistol 	UMETA(DisplayName = "Pistol"),
	WT_Salvo    UMETA(DisplayName = "Salvo")
};

USTRUCT(BlueprintType)
struct TABLETOPGAME_API FWeaponSheet
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
	TEnumAsByte<EWeaponType> WeoponType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
	uint8 Streangth;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
	uint8 ArmorPiercing;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
	uint8 MinRange;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
	uint8 MaxRange;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
	uint8 NumberOfShots;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
	FName SheetName;

};

UCLASS()
class TABLETOPGAME_API ATTWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATTWeapon(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
	UStaticMeshComponent* MeshComponent;

	TArray<FWeaponSheet> WeaponCharSheets;
	FWeaponSheet* CurrentWeaponSheet;
	
	
	
};
