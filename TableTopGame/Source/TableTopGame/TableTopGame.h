// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//General Log
DECLARE_LOG_CATEGORY_EXTERN(LogTTGame, Log, All);

//Logging during game startup
DECLARE_LOG_CATEGORY_EXTERN(LogTTGameInit, Log, All);

//Logging for your Ability system
DECLARE_LOG_CATEGORY_EXTERN(LogTTGameAbilitySystem, Log, All);

//Logging for Critical Errors that must always be addressed
DECLARE_LOG_CATEGORY_EXTERN(LogTTGameCriticalErrors, Log, All);