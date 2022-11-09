// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "GiltCheatManager.generated.h"

#ifndef USING_CHEAT_MANAGER
#define USING_CHEAT_MANAGER (1 && !UE_BUILD_SHIPPING)
#endif // #ifndef USING_CHEAT_MANAGER

DECLARE_LOG_CATEGORY_EXTERN(LogGiltCheat, Log, All);

/**
 * UGiltCheatManager
 *
 *	Base cheat manager class used by this project.
 */
UCLASS(config = Game, Within = PlayerController, MinimalAPI)
class UGiltCheatManager : public UCheatManager
{
	GENERATED_BODY()
};
