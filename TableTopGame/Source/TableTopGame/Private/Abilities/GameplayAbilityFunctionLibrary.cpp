// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Abilities/GameplayAbilityFunctionLibrary.h"
//#include "AbilitySystemGlobals.h"
//#include "GameplayEffect.h"
//#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilityTypes.h"
#include "TableTopGame.h"
#include "Kismet/GameplayStatics.h"
//#include "GameplayTagContainer.h"


UGameplayAbility* UGameplayAbilityFunctionLibrary::GetAbilityFromSpecHandle(AActor * OwningActor, FGameplayAbilitySpecHandle AbilityHandle) {

	//UAbilitySystemComponent* AbilityComp = Cast<IAbilitySystemInterface>(OwningActor) ? Cast<IAbilitySystemInterface>(OwningActor)->GetAbilitySystemComponent() : nullptr;

	//if (!AbilityComp) {
	//	UE_LOG(LogTTGameAbilitySystem,Warning, TEXT("UGameplayAbilityFunctionLibrary::GetAbilityFromSpecHandle: OwningActor* invalid or does not have valid AbilitySystemComponent! "));
	//	return nullptr;
	//}
	//FGameplayAbilitySpec* spec = AbilityComp->FindAbilitySpecFromHandle(AbilityHandle);
	//if (!spec) {
	//	UE_LOG(LogTTGameAbilitySystem,Warning, TEXT("UGameplayAbilityFunctionLibrary::GetAbilityFromSpecHandle: AbilityHandle* invalid or not found!"));
	//	return nullptr;
	//}
	FGameplayAbilitySpec spec;
	if (GetAbilitySpecFromHandle(OwningActor, AbilityHandle, spec))
	{
		return spec.Ability;
	}
	return nullptr;	
}

bool UGameplayAbilityFunctionLibrary::GetAbilitySpecFromHandle(AActor * OwningActor, FGameplayAbilitySpecHandle AbilityHandle,OUT FGameplayAbilitySpec& OutSpec) {

	UAbilitySystemComponent* AbilityComp = Cast<IAbilitySystemInterface>(OwningActor) ? Cast<IAbilitySystemInterface>(OwningActor)->GetAbilitySystemComponent() : nullptr;

	if (!AbilityComp) {
		UE_LOG(LogTTGameAbilitySystem,Warning, TEXT("UGameplayAbilityFunctionLibrary::GetAbilityFromSpecHandle: OwningActor* invalid or does not have valid AbilitySystemComponent! "));
		return false;
	}
	FGameplayAbilitySpec* spec = AbilityComp->FindAbilitySpecFromHandle(AbilityHandle);
	if (!spec) {
		UE_LOG(LogTTGameAbilitySystem,Warning, TEXT("UGameplayAbilityFunctionLibrary::GetAbilityFromSpecHandle: AbilityHandle* invalid or not found!"));

		return false;
	}
	OutSpec = *spec;
	return true;
}
float UGameplayAbilityFunctionLibrary::GetCooldownTimeRemainingFromActor(AActor * OwningActor, FGameplayAbilitySpecHandle CallingAbilityHandle, float& TotalDuration)
{
	/*UGameplayAbility* AbilityToCheck = GetAbilityFromSpecHandle(OwningActor, CallingAbilityHandle);
	UAbilitySystemComponent* AbilityComp = Cast<IAbilitySystemInterface>(OwningActor) ? Cast<IAbilitySystemInterface>(OwningActor)->GetAbilitySystemComponent() : nullptr;

	if (AbilityToCheck && AbilityComp)
	{
		float CurrentDuration;
		AbilityToCheck->GetCooldownTimeRemainingAndDuration(CallingAbilityHandle, AbilityComp->AbilityActorInfo.Get(), CurrentDuration, TotalDuration);
		return CurrentDuration;
	}
	else
	{*/
		return 0.f;
	//}
}


void UGameplayAbilityFunctionLibrary::GetCooldownTimeRemainingFromTagsAndComponent(UObject* WorldContextObject, UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag CooldownTag, float& OutCooldown, float& OutDuration)
{
	if (AbilitySystemComponent == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("ASC Null, returning"));
		return;
	}

	FGameplayTagContainer Tags;
	Tags.AddTagFast(CooldownTag);

	FGameplayEffectQuery Query = FGameplayEffectQuery::MakeQuery_MatchAllOwningTags(Tags);

	TArray<FActiveGameplayEffectHandle> Effects = AbilitySystemComponent->GetActiveEffects(Query);

	if (Effects.Num() > 0)
	{
		const FActiveGameplayEffect* Effect = AbilitySystemComponent->GetActiveGameplayEffect(Effects[0]);
		OutDuration = Effect->GetDuration();
		OutCooldown = Effect->GetTimeRemaining(UGameplayStatics::GetTimeSeconds(WorldContextObject));
	}
}

TArray<FGameplayAbilitySpec> UGameplayAbilityFunctionLibrary::GetActivatableAbilitiesFromComponent( UAbilitySystemComponent * AbilitySystemComponent)
{
	if (AbilitySystemComponent == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("ASC Null, returning"));
		
		return TArray<FGameplayAbilitySpec>();
	}
	TArray<FGameplayAbilitySpec> abilities = AbilitySystemComponent->GetActivatableAbilities();
	for (auto abilitySpec : abilities) 
	{
		FGameplayAbilitySpecHandle handle = abilitySpec.Handle;
		UGameplayAbility* ability = abilitySpec.Ability;
		FGameplayAbilityActorInfo actorInfo = ability->GetActorInfo();
		FGameplayAbilitySpec* specFromHandle = AbilitySystemComponent->FindAbilitySpecFromHandle(handle);
			//ability->CanActivateAbility(handle)
		//abilitySpec.
	}				
	TArray<FGameplayAbilitySpec*> matchingAbilities;
	FGameplayTagContainer tags;
	AbilitySystemComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(tags, matchingAbilities, false);
	//matchingAbilities;

	return abilities;
}

FGameplayAbilityActorInfo UGameplayAbilityFunctionLibrary::GetAbilityActorInfoFromComponent(UAbilitySystemComponent * AbilitySystemComponent)
{
	if (AbilitySystemComponent->AbilityActorInfo.IsValid())
	{
		return *AbilitySystemComponent->AbilityActorInfo.Get();
	}
	else 
	{
		return FGameplayAbilityActorInfo();
	}
}

bool UGameplayAbilityFunctionLibrary::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo& ActorInfo, const FGameplayTagContainer& SourceTags, const FGameplayTagContainer& TargetTags, FGameplayTagContainer & OutOptionalRelevantTags)
{
	//const FGameplayAbilityActorInfo* ActorInfo = ActorInfo;
	
	FGameplayAbilitySpec spec;
	if (!(ActorInfo.OwnerActor.IsValid() && ActorInfo.AvatarActor.IsValid())) 
	{
		UE_LOG(LogTTGameAbilitySystem, Warning, TEXT("UGameplayAbilityFunctionLibrary::CanActivateAbility: ActorInfo.OwnerActor invalid or ActorInfo.AvatarActor invalid! "));
		return false;
	}

	if(GetAbilitySpecFromHandle(ActorInfo.OwnerActor.Get(), Handle, spec))
	{
		UGameplayAbility * ability = spec.Ability;
		if (ability) {
			return ability->CanActivateAbility(Handle, &ActorInfo, &SourceTags, &TargetTags, &OutOptionalRelevantTags);
		}
		UE_LOG(LogTTGameAbilitySystem, Warning, TEXT("UGameplayAbilityFunctionLibrary::CanActivateAbility: Invalid Ability* from Spec! "));

	}
	return false;
}


