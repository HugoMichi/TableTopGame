// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TTAttribute.h"
#include "UnitsEnums.h"
#include "TTItem.generated.h"

//#include "ModelCharacter.h"
//#include "TTItemManager.h"
//enum class EAttributes :uint8;
//enum class EAttributeModifierType : uint8;
struct FSocketInfo;


USTRUCT(BlueprintType)
struct TABLETOPGAME_API FModifierInfo
{
	GENERATED_BODY()
		FModifierInfo() {
	}
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemManager")
		EAttributes Attribute;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemManager")
		FAttributeModifier Modifier;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemManager")
		ATTItem* ItemRef;
};


UCLASS()
class TABLETOPGAME_API ATTItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATTItem(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/*The Points this Item can be Attached to*/
	TArray<EAttachPointType> PossibleAttachPoints;
	FSocketInfo* CurrentAttachPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TArray<FModifierInfo> Modifiers;
	/*Picture Used by Ui to Represent Item*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	UTexture2D* IconTexture;
	/*Text Used by Ui to give detaild Infromation about Item*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FString Description;

};
