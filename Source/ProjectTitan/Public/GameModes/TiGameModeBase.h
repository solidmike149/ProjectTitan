// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TiGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTITAN_API ATiGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    	
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	
};
