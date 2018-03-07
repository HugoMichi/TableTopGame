// Fill out your copyright notice in the Description page of Project Settings.

#include "TTCharacterUIWidget.h"
#include "TableTopGame.h"
#include "Public/Units/ModelCharacter.h"





void UTTCharacterUIWidget::SetCharacter(AModelCharacter* ACharacter)
{
	this->Character = ACharacter;
	//TODO:: put this into function that gets called after Character is set maybe Construct or something like that 
	if (this->Character) {
		UAbilitySystemComponent* AbilityComp = Cast<IAbilitySystemInterface>(this->Character) ? Cast<IAbilitySystemInterface>(this->Character)->GetAbilitySystemComponent() : nullptr;
		if (AbilityComp)
		{
			if (UIAbilityComponentWidgetBP)
			{
				AbilityComponentUI = CreateWidget<UTTAbilityComponentUIWidget>(GetWorld(), UIAbilityComponentWidgetBP);
				AbilityComponentUI->SetAbilityComponent(AbilityComp);
				//Set AbilityComponent in UI Component
			}
		}
	}
}
void UTTCharacterUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/*if (this->Character) {
		UAbilitySystemComponent* AbilityComp = Cast<IAbilitySystemInterface>(this->Character) ? Cast<IAbilitySystemInterface>(this->Character)->GetAbilitySystemComponent() : nullptr;
		if (AbilityComp)
		{
			if (UIAbilityComponentWidgetBP)
			{
				AbilityComponentUI = CreateWidget<UTTAbilityComponentUIWidget>(GetWorld(), UIAbilityComponentWidgetBP);
				AbilityComponentUI->SetAbilityComponent(AbilityComp);
				//TODO:: in Blueprint Construct add AbilityComponentUI to UMG Elment of this Widget
			}
		}
	}*/
	// Character Delegates would be Bound here 
	//Dont forget to remove them in Destruct()
	//AMyPlayerController* PC = CAST_TO_MY_PC(GetOwningPlayer());
	//if (PC)
	//{
	//	// Calls CallPlayerPickupItem() that in turn calls the "BlueprintImplementableEvent" on OnPlayerPickedItem()
	//	PC->OnPlayerPickupItem.RemoveDynamic(this, &UInventoryUserWidget::CallPlayerPickupItem); // Remove the delegate before binding it. (Its always safe to unbind a delegate.)
	//	PC->OnPlayerPickupItem.AddDynamic(this, &UInventoryUserWidget::CallPlayerPickupItem); // Bind the delegate from the PC that calls the BlueprintImplementableEvent.
	//}
}