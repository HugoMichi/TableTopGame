// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitsEnums.h"
#include "Public/Units/TTAttribute.h"
#include "TTItemManager.generated.h"

class ATTItem;




USTRUCT(BlueprintType)
struct TABLETOPGAME_API FSocketInfo
{
	GENERATED_BODY()
	FSocketInfo() {
		this->AttachPointType = EAttachPointType::APT_Belt;
		this->bInUse = false;
		this->AttachedItemRef = nullptr;
		this->Socket = nullptr;
	}
	FSocketInfo(EAttachPointType AttachPointType, const USkeletalMeshSocket* Socket) {
		this->AttachPointType = AttachPointType;
		this->bInUse = false;
		this->AttachedItemRef = nullptr;
		this->Socket = Socket;
	}
	FSocketInfo(EAttachPointType AttachPointType, bool bInUse, ATTItem* AttachedItemRef,const USkeletalMeshSocket* Socket) {
		this->AttachPointType = AttachPointType;
		this->bInUse = bInUse;
		this->AttachedItemRef = AttachedItemRef;
		this->Socket = Socket;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemManager")
		EAttachPointType AttachPointType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemManager")
		bool bInUse;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemManager")
		ATTItem* AttachedItemRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemManager")
		const USkeletalMeshSocket* Socket;
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TABLETOPGAME_API UTTItemManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTTItemManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
		/* Delegates*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FItemsChanged);
	/*OnItemsChanged is called when a item is Added or Removed*/
	UPROPERTY(BlueprintAssignable, Category = "ModelAttributes")
	FItemsChanged OnItemsChanged;

	bool AddItem(ATTItem* Item);
	bool AddItemToSocket(ATTItem* Item, FName SocketName);
	bool AddItemToSocketIndex(ATTItem* Item, int32 Idx);
	bool RemoveItem(ATTItem* Item);
	/*the Mesh used by the Class this Component is added to 
	it has to have Sockets for the System to work	
	Sockets have to be Named after the EAttachPointType Enum:
	e.g.: APT_MainWeapon_1 or  APT_Grenades_5  usw...*/
	void SetSocketMesh(USkeletalMeshComponent* SocketMesh);
	/*Only Use the Array for Displaying etc. use Add and Remove Functions for editing*/
	TArray<FSocketInfo>* GetSockets();

protected:
	TArray<ATTItem*>  EquippedItems;
	USkeletalMeshComponent* SocketMesh;
	TArray<FSocketInfo> Sockets;


private:
	void InitSocketInfoFromSkelMesh();
	bool GetFreeSocketIndexBySocketName(FName SocketName, int32 & outIdx);
	bool GetFirstFreeSocketIndex(EAttachPointType point, int32 & outIdx);





	
};
