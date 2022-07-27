// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AttributeSets/TiAttributeSet.h"
#include "TiHealthSet.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UTiHealthSet : public UTiAttributeSet
{
	GENERATED_BODY()

public:

	UTiHealthSet();

	ATTRIBUTE_ACCESSORS(UTiHealthSet, Health);
	ATTRIBUTE_ACCESSORS(UTiHealthSet, MaxHealth);

	// Delegate to broadcast when the health attribute reaches zero.
	FTiAttributeEvent OnOutOfHealth;

protected:
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	// The current health attribute. The health will be capped by the max health attribute.
	UPROPERTY(BlueprintReadOnly,  Category = "Health")
	FGameplayAttributeData Health;

	// The current max health attribute. Max health is an attribute since gameplay effects can modify it.
	UPROPERTY(BlueprintReadOnly, Category = "Lyra|Health")
	FGameplayAttributeData MaxHealth;
};
