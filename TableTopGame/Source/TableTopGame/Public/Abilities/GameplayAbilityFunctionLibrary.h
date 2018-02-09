// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/EngineTypes.h"
#include "UObject/ScriptInterface.h"
#include "GameplayTagContainer.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "GameplayCueInterface.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayAbilitySpec.h"
#include "GameplayAbility.h"
#include "AbilitySystemGlobals.h"
//#include "GameplayAbilityTypes.h"
#include "AbilitySystemComponent.h"

#include "GameplayAbilityFunctionLibrary.generated.h"

struct FGameplayAbilityActorInfo;
/**
 * 
 */
UCLASS()
class TABLETOPGAME_API UGameplayAbilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		//-----------------------------------------------------------------------
		//		GameplayAbilitySpec
		//-----------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "Ability|GameplayAbility")
	static UGameplayAbility* GetAbilityFromSpecHandle(AActor * OwningActor, FGameplayAbilitySpecHandle AbilityHandle);
	UFUNCTION(BlueprintCallable, Category = "Ability|GameplayAbility")
	static bool GetAbilitySpecFromHandle(AActor * OwningActor, FGameplayAbilitySpecHandle AbilityHandle,FGameplayAbilitySpec& OutSpec);

	/** Return remaining Cooldown and Total Duration of the Cooldown of this ability */
	UFUNCTION(BlueprintCallable, Category = "Ability|GameplayAbility")
	static float GetCooldownTimeRemainingFromActor(AActor * OwningActor, FGameplayAbilitySpecHandle CallingAbilityHandle, float& TotalDuration);



	/** Returns the start time (time which the GE was added) for a given GameplayEffect */
	UFUNCTION(BlueprintCallable, Category = "Ability|GameplayAbility")
	static void GetCooldownTimeRemainingFromTagsAndComponent(UObject* WorldContextObject, UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag CooldownTag, float& OutCooldown, float& OutDuration);


	UFUNCTION(BlueprintCallable, Category = "Ability|GameplayAbility")
	static TArray<FGameplayAbilitySpec> GetActivatableAbilitiesFromComponent( UAbilitySystemComponent* AbilitySystemComponent);

	UFUNCTION(BlueprintCallable, Category = "Ability|GameplayAbility")
	static FGameplayAbilityActorInfo GetAbilityActorInfoFromComponent(UAbilitySystemComponent* AbilitySystemComponent);

	UFUNCTION(BlueprintCallable, Category = "Ability|GameplayAbility")
	static bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const struct FGameplayAbilityActorInfo& ActorInfo, const  FGameplayTagContainer& SourceTags, const FGameplayTagContainer& TargetTags, FGameplayTagContainer& OutOptionalRelevantTags);



	/** Returns the expected end time (when we think the GE will expire) for a given GameplayEffect (note someone could remove or change it before that happens!) */
	//UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")
	//	static float GetActiveGameplayEffectExpectedEndTime(FActiveGameplayEffectHandle ActiveHandle);

	//UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")
	//	static float GetActiveGameplayEffectTotalDuration(FActiveGameplayEffectHandle ActiveHandle);

	//UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect", meta = (WorldContext = "WorldContextObject"))
	//	static float GetActiveGameplayEffectRemainingDuration(UObject* WorldContextObject, FActiveGameplayEffectHandle ActiveHandle);

	//UFUNCTION(BlueprintPure, Category = "Ability|GameplayEffect", Meta = (DisplayName = "Get Active GameplayEffect Debug String "))
	//	static FString GetActiveGameplayEffectDebugString(FActiveGameplayEffectHandle ActiveHandle);
	//
	//
	
};
