// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

PROJECTTITAN_API DECLARE_LOG_CATEGORY_EXTERN(LogGilt, Log, All);
PROJECTTITAN_API DECLARE_LOG_CATEGORY_EXTERN(LogGiltExperience, Log, All);
PROJECTTITAN_API DECLARE_LOG_CATEGORY_EXTERN(LogGiltAbilitySystem, Log, All);
PROJECTTITAN_API DECLARE_LOG_CATEGORY_EXTERN(LogGiltUI, Log, All);

PROJECTTITAN_API FString GetClientServerContextString(UObject* ContextObject = nullptr);

