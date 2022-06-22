// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TiAbilitySystemComponent.generated.h"


class UTiGameplayAbility;
/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UTiAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
	
	bool IsAbilityActive(const FGameplayTagContainer* WithTags, const FGameplayTagContainer* WithoutTags, UGameplayAbility* Ignore);
	
	bool IsAbilityActive(const FGameplayAbilitySpecHandle& InHandle);
};
