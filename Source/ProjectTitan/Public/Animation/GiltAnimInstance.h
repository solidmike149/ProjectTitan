// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Animation/AnimInstance.h"
#include "GiltAnimInstance.generated.h"

class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UGiltAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	
	void InitializeWithAbilitySystem(UAbilitySystemComponent* ASC);

protected:

	virtual void NativeInitializeAnimation() override;

	// Gameplay tags that can be mapped to blueprint variables. The variables will automatically update as the tags are added or removed.
	// These should be used instead of manually querying for the gameplay tags.
	UPROPERTY(EditDefaultsOnly, Category = "GameplayTags")
	FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;
	
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	AActor* OwningActor;
};
