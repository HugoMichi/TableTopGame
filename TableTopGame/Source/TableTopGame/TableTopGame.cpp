// Fill out your copyright notice in the Description page of Project Settings.

#include "TableTopGame.h"
#include "Modules/ModuleManager.h"
IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, TableTopGame, "TableTopGame" );

//General Log
DEFINE_LOG_CATEGORY(LogTTGame);

//Logging during game startup
DEFINE_LOG_CATEGORY(LogTTGameInit);

//Logging for your Ability system
DEFINE_LOG_CATEGORY(LogTTGameAbilitySystem);

//Logging for Critical Errors that must always be addressed
DEFINE_LOG_CATEGORY(LogTTGameCriticalErrors);