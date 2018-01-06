// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/InputComponent.h"
#include "Engine/EngineTypes.h"
#include "GestureRecognizer.h"
#include "InputCoreTypes.h"
#include "KeyState.h"
#include "SettingsBlueprintLibrary.generated.h"


USTRUCT(BlueprintType)
struct FQualitySettings
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quality Settings")
		int32 AntiAliasingQuality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quality Settings")
		int32 EffectsQuality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quality Settings")
		int32 PostProcessQuality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quality Settings")
		int32 ResolutionQuality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quality Settings")
		int32 ShadowQuality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quality Settings")
		int32 TextureQuality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quality Settings")
		int32 ViewDistanceQuality;

	FQualitySettings()
	{
		//do nothing
	}
};

USTRUCT(BlueprintType)
struct FScreenSettings
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screen Settings")
		int32 ScreenSizeX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screen Settings")
		int32 ScreenSizeY;

	/** Game window fullscreen mode 0 = Fullscreen 1 = Windowed fullscreen 2 = Windowed 3 = WindowedMirror */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screen Settings")
		int32 ScreenMode;

	/** Whether to use VSync or not */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screen Settings")
		bool bUseVSync;

	FScreenSettings()
	{

	}
};



USTRUCT(BlueprintType)
struct FInputActionKey
{
	GENERATED_USTRUCT_BODY()

		/** Key to bind it to. */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		FKey Key;

	/** true if one of the Shift keys must be down when the KeyEvent is received to be acknowledged */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		uint32 bShift : 1;

	/** true if one of the Ctrl keys must be down when the KeyEvent is received to be acknowledged */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		uint32 bCtrl : 1;

	/** true if one of the Alt keys must be down when the KeyEvent is received to be acknowledged */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		uint32 bAlt : 1;

	/** true if one of the Cmd keys must be down when the KeyEvent is received to be acknowledged */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		uint32 bCmd : 1;

	bool operator==(const FInputActionKey& Other) const
	{
		return (Key == Other.Key
			&& bShift == Other.bShift
			&& bCtrl == Other.bCtrl
			&& bAlt == Other.bAlt
			&& bCmd == Other.bCmd);
	}

	bool operator<(const FInputActionKey& Other) const
	{
		bool bResult = false;
		if (Key < Other.Key)
		{
			bResult = true;
		}
		return bResult;
	}


	FInputActionKey(const FKey InKey = EKeys::Invalid, const bool bInShift = false, const bool bInCtrl = false, const bool bInAlt = false, const bool bInCmd = false)
		: Key(InKey)
		, bShift(bInShift)
		, bCtrl(bInCtrl)
		, bAlt(bInAlt)
		, bCmd(bInCmd)
	{}
	FInputActionKey(FInputActionKeyMapping mapping)
		: Key(mapping.Key)
		, bShift(mapping.bShift)
		, bCtrl(mapping.bCtrl)
		, bAlt(mapping.bAlt)
		, bCmd(mapping.bCmd)
	{
	}
};




/**
* Defines a mapping between an action and key
*
* @see https://docs.unrealengine.com/latest/INT/Gameplay/Input/index.html
*/
USTRUCT(BlueprintType)
struct FInputActionKeyMappings
{
	GENERATED_USTRUCT_BODY()

		/** Friendly name of action, e.g "jump" */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		FName ActionName;

	/** Key to bind it to. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		TArray<FInputActionKey> ActionKeys;

	bool operator==(const FInputActionKeyMappings& Other) const
	{
		return (ActionName == Other.ActionName);
	}

	bool operator<(const FInputActionKeyMappings& Other) const
	{
		bool bResult = false;
		if (ActionName < Other.ActionName)
		{
			bResult = true;
		}
		return bResult;
	}

	FInputActionKeyMappings(const FName InActionName, const FKey InKey, const bool bInShift, const bool bInCtrl, const bool bInAlt, const bool bInCmd)
		: ActionName(InActionName)
	{
		ActionKeys.Add(FInputActionKey(InKey, bInShift, bInCtrl, bInAlt, bInCmd));
	}
	FInputActionKeyMappings(const FName InActionName = NAME_None)
		: ActionName(InActionName)
	{
	}
};



/**
*
*/

/**
 * 
 */
UCLASS()
class TABLETOPGAME_API USettingsBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	//* KEY MAPPING FUNCTIONS *//	

	static FORCEINLINE TArray<FInputActionKeyMapping> MappingsToMapping(FInputActionKeyMappings map);
	static FORCEINLINE TArray<FInputActionKeyMappings> MappingToMappings(TArray<FInputActionKeyMapping> map);

	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Key Mapping")
		static FInputActionKey GetInputActionKey(const FKeyEvent & KeyEvent);

	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Key Mapping")
		static FInputAxisKeyMapping GetInputAxisMapping(const FKeyEvent & KeyEvent);
	//	Axis Mapping
	UFUNCTION(BlueprintPure, Category = "UtilityLibrary | Key Mapping")
		static void GetAllAxisKeyMapping(TArray<FInputAxisKeyMapping>& Bindings);

	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Key Mapping")
		static void RemoveAxisKeyMapping(FInputAxisKeyMapping ToRemove);
	//	Action Mapping
	UFUNCTION(BlueprintPure, Category = "UtilityLibrary | Key Mapping")
		static void GetAllActionKeyMappings(TArray<FInputActionKeyMappings>& Mapping);

	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Key Mapping")
		static void RemoveActionKeyMapping(FInputActionKeyMappings ToRemove);

	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Key Mapping")
		static void GetAllAxisAndActionMappingsForKey(FKey Key, TArray<FInputActionKeyMappings>& ActionMapping, TArray<FInputAxisKeyMapping>& AxisMapping);

	/** Returns false if the key could not be found as an existing mapping!*/
	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Key Mapping")
		static bool ReMapAxisKey(FInputAxisKeyMapping oldMapping, FInputAxisKeyMapping newMapping);
	/** Returns false if the key could not be found as an existing mapping!*/
	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Key Mapping")
		static bool ReMapActionKey(FInputActionKeyMappings oldMapping, FInputActionKeyMappings newMapping);
	//* SOUND SETTING FUNCTIONS *//	


	//* GRAFIC SETTINGS *//

	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Grafic Settings")
		static bool OptionsMenu__GetDisplayAdapterScreenResolutions(TArray<int32>& Widths, TArray<int32>& Heights, TArray<int32>& RefreshRates, bool IncludeRefreshRates);
	/** Gets the current Resolution in the engine */
	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Grafic Settings")
		static FIntPoint GetResolution();

	/** sets Resolution in the engine */
	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Grafic Settings")
		static void SetResolution(FIntPoint res);

	/** Gets the current Scalability Quality in the engine */
	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Grafic Settings")
		static FQualitySettings GetQualityLevels();

	/** Sets the introduced ScalabilityQuality Settings */
	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Grafic Settings")
		static void SetQualityLevelsByLevel(int32 QualityLevel);

	/** Sets the ScalabilityQuality by Level */
	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Grafic Settings")
		static void SetQualityLevels(FQualitySettings InSettings);

	/** Gets the current Screen settings in the engine */
	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Grafic Settings")
		static FScreenSettings GetScreenSettings();

	/** Sets the screen settings */
	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Grafic Settings")
		static void SetScreenSettings(FScreenSettings InSettings);

	/** Applies all non resolution settings */
	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Grafic Settings")
		static void ApplyNonScreenSettings();

	/** Applies the screen settings */
	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Grafic Settings")
		static void ApplyScreenSettings();

	/** Applies all the graphic settings */
	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Grafic Settings	")
		static void ApplyGraphicSettings();

	//*UTILITY*/

	/** Implementation of a Selection Marquee / Selection Box as a BP Node. AnchorPoint is the first clicked point, which user then drags from to make the box. Class filter is optional way to narrow the scope of actors that can be selected by the selection box! -Rama*/
	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Selection", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
		static void Selection_SelectionBox(UObject* WorldContextObject, TArray<AActor*>& SelectedActors, FVector2D AnchorPoint, FVector2D DraggedPoint, TSubclassOf<AActor> ClassFilter);

	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | Projection")
		static FVector2D ProjectWorldToScreenPosition(const FVector& WorldLocation);

	/** SET the Mouse Position! Returns false if the operation could not occur */
	UFUNCTION(BlueprintCallable, Category = "UtilityLibrary | ViewPort")
		static bool Viewport__SetMousePosition(const APlayerController* ThePC, const float& PosX, const float& PosY);

	/** Get the Cursor Position within the Player's Viewport. This will return a result consistent with SET Mouse Position Returns false if the operation could not occur */
	UFUNCTION(BlueprintPure, Category = "UtilityLibrary | ViewPort")
		static bool Viewport__GetMousePosition(const APlayerController* ThePC, float& PosX, float& PosY);

	/** Get the coordinates of the center of the player's screen / viewport. Returns false if the operation could not occur */
	UFUNCTION(BlueprintPure, Category = "UtilityLibrary | ViewPort")
		static bool Viewport__GetCenterOfViewport(const APlayerController* ThePC, float& PosX, float& PosY);

	
	
};
