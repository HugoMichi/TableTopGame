// Fill out your copyright notice in the Description page of Project Settings.

#include "TableTopGame.h"
#include "CoreMinimal.h"
#include "Public/Units/TTItem.h"
#include "Public/Units/TTAttribute.h"
#include "Public/Units/ModelCharacter.h"
#include "Public/Utility_BP.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TTItemManager.h"


// Sets default values for this component's properties
UTTItemManager::UTTItemManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTTItemManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTTItemManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UTTItemManager::AddItem(ATTItem * Item)
{
	for (auto attachType : Item->PossibleAttachPoints) 
	{
		int32 idx;
		if (GetFirstFreeSocketIndex(attachType, idx)) 
		{	
			return AddItemToSocketIndex(Item, idx);
		}
	}	
	return false;
}

bool UTTItemManager::AddItemToSocket(ATTItem * Item, FName SocketName)
{
	int32 idx;
	if (GetFreeSocketIndexBySocketName(SocketName,idx))
	{		
		return AddItemToSocketIndex(Item, idx);
	}
	return false;
}

bool UTTItemManager::AddItemToSocketIndex(ATTItem *Item, int32 Idx)
{
	if(Item->PossibleAttachPoints.Find(Sockets[Idx].AttachPointType) && 
		Item->CurrentAttachPoint == nullptr, Sockets[Idx].bInUse == false)
	{	/*SocketHandling*/
		Sockets[Idx].bInUse = true;
		Sockets[Idx].AttachedItemRef = Item;
		Item->CurrentAttachPoint = &Sockets[Idx];
		Item->AttachToComponent(SocketMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Sockets[Idx].Socket->SocketName);
		//TODO:: Physicalise Item etc ....

		/*Item ModifierHandling*/
		for (auto modifier : Item->Modifiers) 
		{
			AModelCharacter* parent = Cast<AModelCharacter>(GetOwner());
			if (parent) {
				parent->AddAttributeModifier(modifier);
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Cast Failed Owner of TTItemManager is not a AModelCharacter !!!"));
			}
		}
		return true;
	}
	return false;
}

bool UTTItemManager::RemoveItem(ATTItem * Item)
{
	/*SocketHandling*/
	FSocketInfo* info = Item->CurrentAttachPoint;
	info->AttachedItemRef = nullptr;
	info->bInUse = false;
	Item->CurrentAttachPoint = nullptr;
	Item->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	
	/*Item ModifierHandling*/
	for (auto modifier : Item->Modifiers)
	{
		AModelCharacter* parent = Cast<AModelCharacter>(GetOwner());
		if (parent) {
			parent->RemoveAttributeModifier(modifier);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Cast Failed Owner of TTItemManager is not a AModelCharacter !!!"));
		}
	}
	return false;
}

void UTTItemManager::SetSocketMesh(USkeletalMeshComponent* ASocketMesh)
{
	SocketMesh = ASocketMesh;
}

TArray<FSocketInfo>* UTTItemManager::GetSockets()
{
	return &Sockets;
}

void UTTItemManager::InitSocketInfoFromSkelMesh()
{
	if (SocketMesh)
	{
		TArray<FName> socketNames = SocketMesh->GetAllSocketNames();
		for (auto socketName : socketNames)
		{	
			const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EAttachPointType"), true);
			int numElements = enumPtr->NumEnums() - 1;//because of MAX EnumValue
			for (int idx = 0; idx<numElements; idx++ ) 
			{
				EAttachPointType enumValue = (EAttachPointType)enumPtr->GetValueByIndex(idx);
				FString enumName = enumPtr->GetNameByValue((uint8)enumValue).ToString();
				if (socketName.ToString().StartsWith(enumName)) 
				{
					const USkeletalMeshSocket* socket = SocketMesh->GetSocketByName(socketName);
					FSocketInfo socketInfo = FSocketInfo(enumValue,socket);
					Sockets.Add(socketInfo);
					break;
				}
			}

		}
	}
}
bool UTTItemManager::GetFreeSocketIndexBySocketName(FName SocketName, int32 & Idx)
{
	for (int32 Index = 0; Index != Sockets.Num(); ++Index)
	{
		if (!Sockets[Index].bInUse && Sockets[Index].Socket->SocketName == SocketName) {
			Idx = Index;
			return true;
		}
	}
	return false;
}
bool UTTItemManager::GetFirstFreeSocketIndex(EAttachPointType type, int32 & Idx)
{
	for (int32 Index = 0; Index != Sockets.Num(); ++Index)
	{
		if (!Sockets[Index].bInUse && Sockets[Index].AttachPointType == type) {
			Idx = Index;
			return true;
		}
	}
	return false;
}


