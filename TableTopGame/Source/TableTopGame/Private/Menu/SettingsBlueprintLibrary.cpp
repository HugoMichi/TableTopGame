// Fill out your copyright notice in the Description page of Project Settings.

#include "TableTopGame.h"
#include "SettingsBlueprintLibrary.h"



//////////////////////////////////////////////////////////////////////////////////////////////
/*KEY MAPPING FUNCTIONS*/
//////////////////////////////////////////////////////////////////////////////////////////////

TArray<FInputActionKeyMapping> USettingsBlueprintLibrary::MappingsToMapping(FInputActionKeyMappings map)
{
	TArray<FInputActionKeyMapping> out;
	for (FInputActionKey key : map.ActionKeys) {
		out.Add(FInputActionKeyMapping(map.ActionName, key.Key, key.bShift, key.bCtrl, key.bAlt, key.bCmd));
	}
	return out;
}
TArray<FInputActionKeyMappings> USettingsBlueprintLibrary::MappingToMappings(TArray<FInputActionKeyMapping> map)
{
	TArray<FInputActionKeyMappings> out;
	for (FInputActionKeyMapping element : map)
	{
		FInputActionKeyMappings emptyMap = FInputActionKeyMappings(element.ActionName);
		out.AddUnique(emptyMap);
		out[out.Find(emptyMap)].ActionKeys.Add(FInputActionKey(element));
	}
	return out;
}


FInputActionKey USettingsBlueprintLibrary::GetInputActionKey(const FKeyEvent& KeyEvent)
{
	FInputActionKey Input;

	Input.Key = KeyEvent.GetKey();
	//Input.KeyAsString = Input.Key.GetDisplayName().ToString();

	Input.bAlt = KeyEvent.IsAltDown();
	Input.bCtrl = KeyEvent.IsControlDown();
	Input.bShift = KeyEvent.IsShiftDown();
	Input.bCmd = KeyEvent.IsCommandDown();

	return Input;
}
FInputAxisKeyMapping USettingsBlueprintLibrary::GetInputAxisMapping(const FKeyEvent& KeyEvent)
{
	FInputAxisKeyMapping Input;

	Input.Key = KeyEvent.GetKey();
	//Input.KeyAsString = Input.Key.GetDisplayName().ToString();
	Input.Scale = 1;

	return Input;
}

void USettingsBlueprintLibrary::GetAllAxisKeyMapping(TArray<FInputAxisKeyMapping>& Bindings)
{
	Bindings.Empty();

	const UInputSettings* Settings = GetDefault<UInputSettings>();
	if (!Settings) return;
	Bindings = Settings->AxisMappings;
	/*const TArray<FInputAxisKeyMapping>& Axi = Settings->AxisMappings;

	for (const FInputAxisKeyMapping& Each : Axi)
	{
	Bindings.Add(FInputAxis(Each));
	}*/
}
void USettingsBlueprintLibrary::RemoveAxisKeyMapping(FInputAxisKeyMapping ToRemove)
{
	//GetMutableDefault
	UInputSettings* Settings = GetMutableDefault<UInputSettings>();
	if (!Settings) return;

	TArray<FInputAxisKeyMapping>& Axi = Settings->AxisMappings;

	bool Found = false;
	for (int32 v = 0; v < Axi.Num(); v++)
	{
		if (Axi[v].Key == ToRemove.Key)
		{
			Found = true;
			Axi.RemoveAt(v);
			v = 0;
			continue;
		}
	}

	if (Found)
	{
		//SAVES TO DISK
		Settings->SaveKeyMappings();

		//REBUILDS INPUT, creates modified config in Saved/Config/Windows/Input.ini
		for (TObjectIterator<UPlayerInput> It; It; ++It)
		{
			It->ForceRebuildingKeyMaps(true);
		}
	}
}

void USettingsBlueprintLibrary::GetAllActionKeyMappings(TArray<FInputActionKeyMappings>& Mapping)
{
	Mapping.Empty();

	const UInputSettings* Settings = GetDefault<UInputSettings>();
	if (!Settings) return;

	const TArray<FInputActionKeyMapping>& mappings = Settings->ActionMappings;
	Mapping = USettingsBlueprintLibrary::MappingToMappings(mappings);
}


void USettingsBlueprintLibrary::RemoveActionKeyMapping(FInputActionKeyMappings ToRemove)
{
	//GetMutableDefault
	UInputSettings* Settings = GetMutableDefault<UInputSettings>();
	if (!Settings) return;

	TArray<FInputActionKeyMapping>& Actions = Settings->ActionMappings;

	TArray<FInputActionKeyMapping> toRemoveMaps;
	for (FInputActionKey key : ToRemove.ActionKeys) {
		toRemoveMaps.Add(FInputActionKeyMapping(ToRemove.ActionName, key.Key, key.bShift, key.bCtrl, key.bAlt, key.bCmd));
	}
	bool Found = false;
	for (FInputActionKeyMapping removeMap : toRemoveMaps) {

		for (int32 i = 0; i < Actions.Num(); i++)
		{
			if (Actions[i].Key == removeMap.Key)
			{
				Found = true;
				Actions.RemoveAt(i);
				i = 0;
				continue;
			}
		}
	}

	if (Found)
	{
		//SAVES TO DISK
		Settings->SaveKeyMappings();

		//REBUILDS INPUT, creates modified config in Saved/Config/Windows/Input.ini
		for (TObjectIterator<UPlayerInput> It; It; ++It)
		{
			It->ForceRebuildingKeyMaps(true);
		}
	}
}

void USettingsBlueprintLibrary::GetAllAxisAndActionMappingsForKey(FKey Key, TArray<FInputActionKeyMappings>& ActionMapping, TArray<FInputAxisKeyMapping>& AxisMapping)
{
	ActionMapping.Empty();
	AxisMapping.Empty();

	const UInputSettings* Settings = GetDefault<UInputSettings>();
	if (!Settings) return;

	ActionMapping = MappingToMappings(Settings->ActionMappings);
	AxisMapping = Settings->AxisMappings;

}
bool USettingsBlueprintLibrary::ReMapAxisKey(FInputAxisKeyMapping oldMapping, FInputAxisKeyMapping newMapping)
{
	UInputSettings* Settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
	if (!Settings) return false;

	TArray<FInputAxisKeyMapping>& Axi = Settings->AxisMappings;

	//~~~

	bool Found = false;
	for (FInputAxisKeyMapping& Each : Axi)
	{
		//Search by original
		if (Each.AxisName == oldMapping.AxisName &&
			Each.Key == oldMapping.Key
			) {
			//Update to new!
			Each = newMapping;
			Found = true;
			break;
		}
	}

	if (Found)
	{
		//SAVES TO DISK
		const_cast<UInputSettings*>(Settings)->SaveKeyMappings();

		//REBUILDS INPUT, creates modified config in Saved/Config/Windows/Input.ini
		for (TObjectIterator<UPlayerInput> It; It; ++It)
		{
			It->ForceRebuildingKeyMaps(true);
		}
	}
	return Found;
}

bool USettingsBlueprintLibrary::ReMapActionKey(FInputActionKeyMappings oldMap, FInputActionKeyMappings newMap)
{
	UInputSettings* Settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
	if (!Settings) return false;

	TArray<FInputActionKeyMapping>& Actions = Settings->ActionMappings;

	TArray<FInputActionKeyMapping> oldMapping = MappingsToMapping(oldMap);
	TArray<FInputActionKeyMapping> newMapping = MappingsToMapping(newMap);

	//~~~


	//Remove Old Mappings

	bool Found = false;
	for (FInputActionKeyMapping old : oldMapping) {
		if (0 < Actions.Remove(old))
			Found = true;
	}
	for (FInputActionKeyMapping newM : newMapping) {
		Actions.AddUnique(newM);
	}


	//for (FInputActionKeyMapping& Each : Actions)
	//{
	//	//Search by original
	//	if (Each.ActionName == oldMapping.ActionName &&
	//		Each.Key == oldMapping.Key
	//		) {
	//		Each.ActionName = newMapping.ActionName;
	//		Each.Key = newMapping.Key;
	//		Each.bAlt = newMapping.bAlt;
	//		Each.bCmd = newMapping.bCmd;
	//		Each.bCtrl = newMapping.bCtrl;
	//		Each.bShift = newMapping.bShift;
	//		Found = true;
	//		break;
	//	}
	//}

	if (Found)
	{
		//SAVES TO DISK
		const_cast<UInputSettings*>(Settings)->SaveKeyMappings();

		//REBUILDS INPUT, creates modified config in Saved/Config/Windows/Input.ini
		for (TObjectIterator<UPlayerInput> It; It; ++It)
		{
			It->ForceRebuildingKeyMaps(true);
		}
	}
	return Found;
}



///////////////////////////////////////////////////////////////////////////////////////////
/*GRAFIC SETTINGS FUNCTIONS*/
///////////////////////////////////////////////////////////////////////////////////////////


bool USettingsBlueprintLibrary::OptionsMenu__GetDisplayAdapterScreenResolutions(TArray<int32>& Widths, TArray<int32>& Heights, TArray<int32>& RefreshRates, bool IncludeRefreshRates)
{
	//Clear any Previous
	Widths.Empty();
	Heights.Empty();
	RefreshRates.Empty();

	TArray<FString> Unique;

	FScreenResolutionArray Resolutions;
	if (RHIGetAvailableResolutions(Resolutions, false))
	{
		for (const FScreenResolutionRHI& EachResolution : Resolutions)
		{
			FString Str = "";
			Str += FString::FromInt(EachResolution.Width);
			Str += FString::FromInt(EachResolution.Height);

			//Include Refresh Rates?
			if (IncludeRefreshRates)
			{
				Str += FString::FromInt(EachResolution.RefreshRate);
			}

			if (Unique.Contains(Str))
			{
				//Skip! This is duplicate!
				continue;
			}
			else
			{
				//Add to Unique List!
				Unique.AddUnique(Str);
			}

			//Add to Actual Data Output!
			Widths.Add(EachResolution.Width);
			Heights.Add(EachResolution.Height);
			RefreshRates.Add(EachResolution.RefreshRate);
		}

		return true;
	}
	return false;
}

FIntPoint USettingsBlueprintLibrary::GetResolution()
{
	return GEngine->GameUserSettings->GetScreenResolution();
}
void USettingsBlueprintLibrary::SetResolution(FIntPoint res)
{
	return GEngine->GameUserSettings->SetScreenResolution(res);
}

FQualitySettings USettingsBlueprintLibrary::GetQualityLevels()
{
	FQualitySettings OutQuality;

	OutQuality.AntiAliasingQuality = GEngine->GameUserSettings->ScalabilityQuality.AntiAliasingQuality;
	OutQuality.EffectsQuality = GEngine->GameUserSettings->ScalabilityQuality.EffectsQuality;
	OutQuality.PostProcessQuality = GEngine->GameUserSettings->ScalabilityQuality.PostProcessQuality;
	OutQuality.ResolutionQuality = GEngine->GameUserSettings->ScalabilityQuality.ResolutionQuality;
	OutQuality.ShadowQuality = GEngine->GameUserSettings->ScalabilityQuality.ShadowQuality;
	OutQuality.TextureQuality = GEngine->GameUserSettings->ScalabilityQuality.TextureQuality;
	OutQuality.ViewDistanceQuality = GEngine->GameUserSettings->ScalabilityQuality.ViewDistanceQuality;

	return OutQuality;
}

void USettingsBlueprintLibrary::SetQualityLevelsByLevel(int32 QualityLevel)
{
	GEngine->GameUserSettings->ScalabilityQuality.SetFromSingleQualityLevel(QualityLevel);
}

void USettingsBlueprintLibrary::SetQualityLevels(FQualitySettings InSettings)
{
	GEngine->GameUserSettings->ScalabilityQuality.AntiAliasingQuality = InSettings.AntiAliasingQuality;
	GEngine->GameUserSettings->ScalabilityQuality.EffectsQuality = InSettings.EffectsQuality;
	GEngine->GameUserSettings->ScalabilityQuality.PostProcessQuality = InSettings.PostProcessQuality;
	GEngine->GameUserSettings->ScalabilityQuality.ResolutionQuality = InSettings.ResolutionQuality;
	GEngine->GameUserSettings->ScalabilityQuality.ShadowQuality = InSettings.ShadowQuality;
	GEngine->GameUserSettings->ScalabilityQuality.TextureQuality = InSettings.TextureQuality;
	GEngine->GameUserSettings->ScalabilityQuality.ViewDistanceQuality = InSettings.ViewDistanceQuality;
}


FScreenSettings USettingsBlueprintLibrary::GetScreenSettings()
{
	FScreenSettings OutSettings;
	FIntPoint Resolution = GEngine->GameUserSettings->GetScreenResolution();

	OutSettings.ScreenSizeX = Resolution.X;
	OutSettings.ScreenSizeY = Resolution.Y;
	OutSettings.ScreenMode = int32(GEngine->GameUserSettings->GetFullscreenMode());
	OutSettings.bUseVSync = GEngine->GameUserSettings->bUseVSync;

	return OutSettings;
}

void USettingsBlueprintLibrary::SetScreenSettings(FScreenSettings InSettings)
{
	GEngine->GameUserSettings->SetFullscreenMode(static_cast<EWindowMode::Type>(InSettings.ScreenMode));
	GEngine->GameUserSettings->SetScreenResolution(FIntPoint(InSettings.ScreenSizeX, InSettings.ScreenSizeY));
	GEngine->GameUserSettings->bUseVSync = InSettings.bUseVSync;
}

void USettingsBlueprintLibrary::ApplyNonScreenSettings()
{
	GEngine->GameUserSettings->ApplyNonResolutionSettings();
}

void USettingsBlueprintLibrary::ApplyScreenSettings()
{
	GEngine->GameUserSettings->ApplyResolutionSettings(true);
}

void USettingsBlueprintLibrary::ApplyGraphicSettings()
{
	GEngine->GameUserSettings->ApplyNonResolutionSettings();
	GEngine->GameUserSettings->ApplyResolutionSettings(true);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*UTILITY*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


void USettingsBlueprintLibrary::Selection_SelectionBox(UObject* WorldContextObject, TArray<AActor*>& SelectedActors, FVector2D AnchorPoint, FVector2D DraggedPoint, TSubclassOf<AActor> ClassFilter)
{
	if (!WorldContextObject) return;


	//using a context object to get the world!
	UWorld* const World = GEngine->GetWorldFromContextObject(WorldContextObject);
	if (!World) return;
	//~~~~~~~~~~~

	SelectedActors.Empty();

	FBox2D Box;
	Box += DraggedPoint;
	Box += AnchorPoint;
	for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
	{
		if (!Itr->IsA(ClassFilter)) continue;
		//~~~~~~~~~~~~~~~~~~

		if (Box.IsInside(USettingsBlueprintLibrary::ProjectWorldToScreenPosition(Itr->GetActorLocation())))
		{
			SelectedActors.Add(*Itr);
		}
	}
}


FVector2D USettingsBlueprintLibrary::ProjectWorldToScreenPosition(const FVector& WorldLocation)
{
	TObjectIterator<APlayerController> ThePC;
	if (!ThePC) return FVector2D::ZeroVector;

	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(ThePC->Player);
	if (LocalPlayer != NULL && LocalPlayer->ViewportClient != NULL && LocalPlayer->ViewportClient->Viewport != NULL)
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		// Create a view family for the game viewport
		FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
			LocalPlayer->ViewportClient->Viewport,
			ThePC->GetWorld()->Scene,
			LocalPlayer->ViewportClient->EngineShowFlags)
			.SetRealtimeUpdate(true));

		// Calculate a view where the player is to update the streaming from the players start location
		FVector ViewLocation;
		FRotator ViewRotation;
		FSceneView* SceneView = LocalPlayer->CalcSceneView(&ViewFamily, /*out*/ ViewLocation, /*out*/ ViewRotation, LocalPlayer->ViewportClient->Viewport);

		//Valid Scene View?
		if (SceneView)
		{
			//Return
			FVector2D ScreenLocation;
			SceneView->WorldToPixel(WorldLocation, ScreenLocation);
			return ScreenLocation;
		}
	}

	return FVector2D::ZeroVector;
}

//Most HUD stuff is in floats so I do the conversion internally
bool USettingsBlueprintLibrary::Viewport__SetMousePosition(const APlayerController* ThePC, const float& PosX, const float& PosY)
{
	if (!ThePC) return false;
	//~~~~~~~~~~~~~

	//Get Player
	const ULocalPlayer * Player = Cast<ULocalPlayer>(ThePC->Player);
	//PlayerController::Player is UPlayer

	if (!Player) return false;
	//~~~~~~~~~~~~~~~~~~~~

	//get view port ptr
	const UGameViewportClient * ViewportClient =
		Cast < UGameViewportClient >(Player->ViewportClient);

	if (!ViewportClient) return false;
	//~~~~~~~~~~~~~~~~~~~~

	FViewport * Viewport = ViewportClient->Viewport;

	if (!Viewport) return false;
	//~~~~~~~~~~~~~~~~~~~~

	//Set Mouse
	Viewport->SetMouse(int32(PosX), int32(PosY));

	return true;
}


bool USettingsBlueprintLibrary::Viewport__GetMousePosition(const APlayerController * ThePC, float & PosX, float & PosY)
{
	if (!ThePC) return false;
	//~~~~~~~~~~~~~

	//Get Player
	const ULocalPlayer * Player = Cast<ULocalPlayer>(ThePC->Player);
	//PlayerController::Player is UPlayer

	if (!Player) return false;
	//~~~~~~~~~~~~~~~~~~~~

	//get view port ptr
	const UGameViewportClient * ViewportClient =
		Cast < UGameViewportClient >(Player->ViewportClient);

	if (!ViewportClient) return false;
	//~~~~~~~~~~~~~~~~~~~~

	FViewport * Viewport = ViewportClient->Viewport;

	if (!Viewport) return false;
	//~~~~~~~~~~~~~~~~~~~~

	PosX = float(Viewport->GetMouseX());
	PosY = float(Viewport->GetMouseY());

	return true;
}


bool USettingsBlueprintLibrary::Viewport__GetCenterOfViewport(const APlayerController * ThePC, float & PosX, float & PosY)
{
	if (!ThePC) return false;
	//~~~~~~~~~~~~~

	//Get Player
	const ULocalPlayer * Player = Cast<ULocalPlayer>(ThePC->Player);
	//PlayerController::Player is UPlayer

	if (!Player) return false;
	//~~~~~~~~~~~~~~~~~~~~

	//get view port ptr
	const UGameViewportClient * ViewportClient =
		Cast < UGameViewportClient >(Player->ViewportClient);

	if (!ViewportClient) return false;
	//~~~~~~~~~~~~~~~~~~~~

	FViewport * Viewport = ViewportClient->Viewport;

	if (!Viewport) return false;
	//~~~~~~~~~~~~~~~~~~~~

	//Get Size
	FIntPoint Size = Viewport->GetSizeXY();

	//Center
	PosX = Size.X / 2;
	PosY = Size.Y / 2;

	return true;
}




