// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TiPlayerState.generated.h"

class UTiSaveGame;
/**
 * 
 */
UCLASS()
class PROJECTTITAN_API ATiPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent)
	void SavePlayerState(UTiSaveGame* SaveObject);

	UFUNCTION(BlueprintNativeEvent)
	void LoadPlayerState(UTiSaveGame* SaveObject);
};
