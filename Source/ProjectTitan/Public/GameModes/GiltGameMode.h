// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularGameMode.h"
#include "GiltGameMode.generated.h"

class UGiltExperienceDefinition;

/**
 * AGiltGameMode
 *
 *	The base game mode class used by this project.
 */
UCLASS(Config = Game, Meta = (ShortTooltip = "The base game mode class used by this project."))
class PROJECTTITAN_API AGiltGameMode : public AModularGameModeBase
{
	GENERATED_BODY()

public:

	AGiltGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

protected:
	
	bool IsExperienceLoaded() const;

	void OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId, const FString& ExperienceIdSource);

	void HandleMatchAssignmentIfNotExpectingOne();
};
