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

	// Value to associate an ability with an slot without tying it to an automatically activated input.
	// Passive abilities won't be tied to an input so we need a way to generically associate abilities with slots.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	ETiAbilityInputID AbilityID = ETiAbilityInputID::None;
};
