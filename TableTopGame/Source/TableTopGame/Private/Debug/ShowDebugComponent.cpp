// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Debug/ShowDebugComponent.h"
#include "TableTopGame.h"
#include "WidgetComponent.h"

// Sets default values for this component's properties
UShowDebugComponent::UShowDebugComponent()
{
	//sets default values
	CustomTickInterval = 0.25f;
	isUsingCustomTickInterval = true;
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UShowDebugComponent::BeginPlay()
{
	Super::BeginPlay();
	//If want to use custom tick interval set the Tick interval
	if (isUsingCustomTickInterval)
	{
		PrimaryComponentTick.TickInterval = CustomTickInterval;
	}
	//create UWidgetComponent component object
	WidgetComponentRef = NewObject<UWidgetComponent>(this);
	//Sets UWidgetComponent User widget class to display
	WidgetComponentRef->SetWidgetClass(ShowDebugWidgetClass);
	//Set UWidgetComponent draw size
	WidgetComponentRef->SetDrawSize(FVector2D(2000, 500));
	//This will work only in 4.11 - setting widget space to screen not world
	WidgetComponentRef->SetWidgetSpace(EWidgetSpace::Screen);
	//Make sure widget don't have any collision
	WidgetComponentRef->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//Add created component to the Owner.
	GetOwner()->AddComponent(FName("ShowDebugWidgetComponent"), false, GetOwner()->GetRootComponent()->GetComponentTransform(), WidgetComponentRef);
	//Attach component to the root
	WidgetComponentRef->AttachToComponent(GetOwner()->GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
	//Register component. Without this it won't be visible
	WidgetComponentRef->RegisterComponent();
	//After registering store reference to the User Widget object (User Widget)
	ShowDebugWidgetRef = Cast<UShowDebugWidget>(WidgetComponentRef->GetUserWidgetObject());
}


// Called every frame
void UShowDebugComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//If UserWidget (UShowDebugWidget) is created call OnVariablesUpdated event so it can be managed in Blueprints to fill the data in layout.
	if (ShowDebugWidgetRef)
	{
		ShowDebugWidgetRef->OnVariablesUpdated(UpdateVariables());  // heres where we actually call our custom event
	}
}

TArray<FDebugVariable> UShowDebugComponent::UpdateVariables()
{
	//variables array that we will return 
	TArray<FDebugVariable> Variables;
	FDebugVariable TempVar;

	for (int i = 0; i < VariablesNames.Num(); i++)  // iterate all VariableNames that someone added to the array
	{
		UProperty *Prop = FindField<UProperty>(GetOwner()->GetClass(), VariablesNames[i]); // try to find the UProperty named as VariablesNames[i]
		if (Prop)
		{
			FString VariableToString;
			void *Value = Prop->ContainerPtrToValuePtr<void>(GetOwner()); //this function will create pointer to the value 
			if (Value)
			{
				Prop->ExportTextItem(VariableToString, Value, NULL, NULL, 0);  // this function will export the value to string! 

				TempVar.SetName(VariablesNames[i]);  //sets the name
				TempVar.SetValue(VariableToString); //sets the value
				Variables.Add(TempVar); //add it to the array that we will return
			}
		}
		else //wasn't able to find any variable 
		{
			FString CantFindName = FString("not found: ") + FString(VariablesNames[i].ToString());  //create simple string 
			TempVar.SetName(FName(*CantFindName));
			TempVar.SetValue(FString(""));
			Variables.Add(TempVar);
		}
	}
	return Variables;
}