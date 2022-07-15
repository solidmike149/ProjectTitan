// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Animation/AnimInstance.h"
#include "TeAnimInstance.generated.h"

class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UTeAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void InitializeWithAbilitySystem(UAbilitySystemComponent* ASC);
	
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	APawn* OwningPawn;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	float Speed;

	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	bool bIsSprinting;

	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	bool bIsAiming;

protected:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// Gameplay tags that can be mapped to blueprint variables. The variables will automatically update as the tags are added or removed.
	// These should be used instead of manually querying for the gameplay tags.
	UPROPERTY(EditDefaultsOnly, Category = "GameplayTags")
	FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;

};
