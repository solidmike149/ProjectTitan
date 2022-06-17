// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TiAnimInstance.generated.h"

class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UTiAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

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

	virtual void NativeInitializeAnimation() override;
};
