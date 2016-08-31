// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine/UserDefinedStruct.h"
#include "TableTopGame.h"
#include "TTAttribute.generated.h"

/** */

UENUM(BlueprintType)
enum class EAttributeModifierType : uint8
{
	AMT_Multiply 	UMETA(DisplayName = "*"),
	AMT_Add  	UMETA(DisplayName = "+"),
	AMT_Override 	UMETA(DisplayName = "override")
};

USTRUCT(BlueprintType)
struct TABLETOPGAME_API FAttributeModifier
{
	GENERATED_BODY()


		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
		EAttributeModifierType ModifierType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
		uint8 BaseValue;

	FName ModifierName;
	bool operator<(const FAttributeModifier &B) {
		return ModifierType < B.ModifierType;
	}

	bool operator==(const FAttributeModifier &B) {
		return ModifierType == B.ModifierType &&
			BaseValue == B.BaseValue	&&
			ModifierName == B.ModifierName;
	}

};

/** Broadcasts whenever the layer changes */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttributeChangedEvent);

USTRUCT(BlueprintType)
struct TABLETOPGAME_API FAttribute
{
	GENERATED_BODY()

		FAttribute() {
		ClampValueMax = 10;
		ClampValueMin = 0;
		BaseValue = 0;
		CalculateFinalValue();
	}
	FAttribute(uint8 baseValue) {
		ClampValueMax = 10;
		ClampValueMin = 0;
		this->BaseValue = baseValue;
		CalculateFinalValue();
	}
	FAttribute(uint8 baseValue, TArray<FAttributeModifier> modifiers) {
		this->Modifiers = modifiers;
		FAttribute(BaseValue);
	}



/** Broadcasts whenever the layer changes */
	UPROPERTY(BlueprintAssignable,Category = ModelCharacteristics)
	FAttributeChangedEvent ChangedEvent;
	FAttributeChangedEvent& OnChanged() { return ChangedEvent; }
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
		uint8 BaseValue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
		uint8 ClampValueMax;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
		uint8 ClampValueMin;
	UPROPERTY()
		uint8 FinalValue;

	/* Defines if a larger Value of an attribute ist better or a smaller  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ModelCharacteristics)
		bool bLargeValueIsBetter = true;
	/*Array used to store all active Modifiers*/
	TArray<FAttributeModifier> Modifiers;

	void CalculateFinalValue() {
		if (Modifiers.Num() == 0) {
			FinalValue = BaseValue;
			return;
		}
		Modifiers.Sort([](const FAttributeModifier& A, const FAttributeModifier& B) {
			return A.ModifierType < B.ModifierType;
		});
		/*If there are Values with Overrides take them first */
		TArray<FAttributeModifier> Overrides = Modifiers.FilterByPredicate([](const FAttributeModifier& A) {
			return A.ModifierType == EAttributeModifierType::AMT_Override ? true : false;
		});
		if (Overrides.Num() != 0) {
			FinalValue = Overrides[0].BaseValue;
			for (FAttributeModifier item : Overrides) {
				if (FinalValue < item.BaseValue)
					FinalValue = item.BaseValue;
			}
			FinalValue = FMath::Clamp(FinalValue, ClampValueMin, ClampValueMax);
			return;
		}
		/*The Rest of the Value Application depends on the Order of the EAttributeModifierType Enum*/

		for (FAttributeModifier item : Modifiers) {
			switch (item.ModifierType)
			{
			case EAttributeModifierType::AMT_Multiply:
				FinalValue *= item.BaseValue;
				break;
			case EAttributeModifierType::AMT_Add:
				FinalValue += item.BaseValue;
				break;

			default:
				//UE_LOG(LogTemp, Warning, TEXT("SelectedName: %s"),item.ModifierName);
				break;
			}

		}
		FinalValue = FMath::Clamp(FinalValue, ClampValueMin, ClampValueMax);

	}

	void AddModifier(FAttributeModifier mod) {
		Modifiers.Add(mod);
		CalculateFinalValue();
		ChangedEvent.Broadcast();
	}

	int32 RemoveModifier(FAttributeModifier mod) {
		int32 res = Modifiers.Remove(mod);
		CalculateFinalValue();
		ChangedEvent.Broadcast();
		return res;
	}

	uint8 GetBaseValue() {
		return BaseValue;
	}
	uint8 GetFinalValue() {
		return BaseValue;
	}
};
/*Class is used to expose structs special functions to Blueprint*/
UCLASS()
class TABLETOPGAME_API UTTAttribute : public UObject
{
	GENERATED_BODY()
UFUNCTION(BlueprintCallable, Category = "Attribute")
static void AddModifier(FAttribute AttributeStruct,FAttributeModifier mod);

UFUNCTION(BlueprintCallable, Category = "Attribute")
static int32 RemoveModifier(FAttribute AttributeStruct,FAttributeModifier mod);

};