// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GiltGameData.generated.h"

class UGameplayEffect;
/**
 * UGiltGameData
 *
 *	Non-mutable data asset that contains global game data.
 */
UCLASS(BlueprintType, Const, Meta = (DisplayName = "Gilt Game Data", ShortTooltip = "Data asset containing global game data."))
class UGiltGameData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UGiltGameData();

	// Returns the loaded game data.
	static const UGiltGameData& Get();

	// Gameplay effect used to apply damage.
	UPROPERTY(EditDefaultsOnly, Category = "Default Gameplay Effects", meta = (DisplayName = "Damage Gameplay Effect"))
	TSoftClassPtr<UGameplayEffect> DamageGameplayEffect;

	// Gameplay effect used to add and remove dynamic tags.
	UPROPERTY(EditDefaultsOnly, Category = "Default Gameplay Effects")
	TSoftClassPtr<UGameplayEffect> DynamicTagGameplayEffect;
};
