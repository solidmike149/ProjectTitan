// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GiltWorldSettings.generated.h"


class UGiltExperienceDefinition;
/**
 * The default world settings object, used primarily to set the default gameplay experience to use when playing on this map
 */
UCLASS()
class PROJECTTITAN_API AGiltWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:

	AGiltWorldSettings(const FObjectInitializer& ObjectInitializer);
	
	// Returns the default experience to use when a server opens this map if it is not overridden by the user-facing experience
	FPrimaryAssetId GetDefaultGameplayExperience() const;

protected:
	// The default experience to use when a server opens this map if it is not overridden by the user-facing experience
	UPROPERTY(EditDefaultsOnly, Category=GameMode)
	TSoftClassPtr<UGiltExperienceDefinition> DefaultGameplayExperience;
	
};
