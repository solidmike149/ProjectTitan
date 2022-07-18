// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/TiAnimInstance.h"

#include "AbilitySystemGlobals.h"

void UTiAnimInstance::InitializeWithAbilitySystem(UAbilitySystemComponent* ASC)
{
	check(ASC);

	GameplayTagPropertyMap.Initialize(this, ASC);
}

void UTiAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningActor = GetOwningActor();
	
	if (OwningActor)
	{
		if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor))
		{
			
			InitializeWithAbilitySystem(ASC);
		}
	}
}

void UTiAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
