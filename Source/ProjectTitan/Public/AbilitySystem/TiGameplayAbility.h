// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ProjectTitan/ProjectTitan.h"
#include "TiGameplayAbility.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECTTITAN_API UTiGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	
	UTiGameplayAbility();

	// Abilities with this set will automatically activate when the input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	ETiAbilityInputID AbilityInputID = ETiAbilityInputID::None;
};
