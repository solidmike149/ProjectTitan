// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AttributeSets/TiAttributeSet.h"
#include "TiPlayerSet.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UTiPlayerSet : public UTiAttributeSet
{
	GENERATED_BODY()


public:
	
	ATTRIBUTE_ACCESSORS(UTiPlayerSet, Stamina);
	ATTRIBUTE_ACCESSORS(UTiPlayerSet, MaxStamina);
	ATTRIBUTE_ACCESSORS(UTiPlayerSet, Ammo);
	ATTRIBUTE_ACCESSORS(UTiPlayerSet, MaxAmmo);
	ATTRIBUTE_ACCESSORS(UTiPlayerSet, Speed);
	
	// AttributeSet Overrides
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Stamina")
	FGameplayAttributeData Stamina;


	UPROPERTY(BlueprintReadOnly, Category = "Stamina")
	FGameplayAttributeData MaxStamina;


	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
	FGameplayAttributeData Ammo;


	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
	FGameplayAttributeData MaxAmmo;


	UPROPERTY(BlueprintReadOnly, Category = "Speed")
	FGameplayAttributeData Speed;

};
