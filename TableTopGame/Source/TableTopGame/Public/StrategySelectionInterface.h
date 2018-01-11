#pragma once
#include "CoreMinimal.h"
#include "TableTopGame.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Blueprint/UserWidget.h"
#include "StrategySelectionInterface.generated.h"

class SUserWidget;
/** Interface for actors which receive notifies about their selected state */
UINTERFACE(BlueprintType)
class TABLETOPGAME_API UStrategySelectionInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class TABLETOPGAME_API IStrategySelectionInterface
{
	GENERATED_IINTERFACE_BODY()

	/** tries to select actor */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Selection")
	bool OnSelectionGained();

	/** tries to deselect actor */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Selection")
	bool OnSelectionLost();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Selection")
	FString GetName();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Selection")
	UUserWidget* GetUIWidget();
		

};