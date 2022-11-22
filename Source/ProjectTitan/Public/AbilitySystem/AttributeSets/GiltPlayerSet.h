// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AttributeSets/GiltAttributeSet.h"
#include "GiltPlayerSet.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UGiltPlayerSet : public UGiltAttributeSet
{
	GENERATED_BODY()

public:
	
	ATTRIBUTE_ACCESSORS(UGiltPlayerSet, Stamina);
	ATTRIBUTE_ACCESSORS(UGiltPlayerSet, MaxStamina);
	ATTRIBUTE_ACCESSORS(UGiltPlayerSet, Ammo);
	ATTRIBUTE_ACCESSORS(UGiltPlayerSet, MaxAmmo);

	UGiltPlayerSet();
	
	// AttributeSet Overrides
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Gilt|Stamina")
	FGameplayAttributeData Stamina;


	UPROPERTY(BlueprintReadOnly, Category = "Gilt|Stamina")
	FGameplayAttributeData MaxStamina;


	UPROPERTY(BlueprintReadOnly, Category = "Gilt|Ammo")
	FGameplayAttributeData Ammo;


	UPROPERTY(BlueprintReadOnly, Category = "Gilt|Ammo")
	FGameplayAttributeData MaxAmmo;
};
