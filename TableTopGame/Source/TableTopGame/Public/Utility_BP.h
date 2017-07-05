// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Utility_BP.generated.h"

/**
 * 
 */
UCLASS()
class TABLETOPGAME_API UUtility_BP : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	//NO Templated Functions in the cpp file they dont work. implement in .h file !!!!!!!!!!

	/*// Example usage:
	UUtility_BP::GetEnumValueAsString<EPlayerPhase>("EPlayerPhase", EPlayerPhase::PP_DeploymentPhase)));		*/		
	template<typename TEnum>
	UFUNCTION(BlueprintCallable, Category = "Utility")
	static FORCEINLINE FString GetEnumElementToString(const FString& Name, TEnum Value) 
	{
		const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		if (!enumPtr)
			return FString("Invalid");
		return enumPtr->GetNameByValue((uint8)Value).ToString();
	}
	/*Get the Index of a Enum Element given by its name as string 
	Index is the ordering of the Elements, Value is the given Value that can be additionaly added to an Element,
	value can be sparse,Index is not Sparse
	*/
	template <typename EnumType>
	UFUNCTION(BlueprintCallable, Category = "Utility")
	static FORCEINLINE EnumType GetEnumIndexFromString(const FString& EnumName, const FString& String)
	{
		UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
		if (!Enum)
			return EnumType(0);
		return (EnumType)Enum->GetIndexByName(FName(*String));
	}

	/*Get the Value of a Enum Element given by its name as string
	Index is the ordering of the Elements, Value is the given Value that can be additionaly added to an Element,
	value can be sparse, Index is not Sparse
	*/
	template <typename EnumType>
	UFUNCTION(BlueprintCallable, Category = "Utility")
		static FORCEINLINE EnumType GetEnumValueFromString(const FString& EnumName, const FString& String)
	{
		UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
		if (!Enum)
			return EnumType(0);
		return (EnumType)Enum->GetValueByName(FName(*String));
	}

	/*
	Gets the next Element of the Enum, ordering is specified by the index.
	*/
	template <typename TEnum>
	UFUNCTION(BlueprintCallable, Category = "Utility")
	static FORCEINLINE TEnum GetNextEnumElement(const FString& Name, TEnum Value)
	{
		const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		int numElements = enumPtr->NumEnums() - 1;//because of MAX EnumValue
		if (!enumPtr)
			return Value; // if Error return given Value back
		int nextIdx = enumPtr->GetIndexByValue((uint8)Value) + 1;
		if (nextIdx >= numElements)
			nextIdx = 0;
		return (TEnum)enumPtr->GetValueByIndex(nextIdx);
	}






		
		UFUNCTION(BlueprintCallable, Category = "Utility")
		static void Test();
	
	
};
