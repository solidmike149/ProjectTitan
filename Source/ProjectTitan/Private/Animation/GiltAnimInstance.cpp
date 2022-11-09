// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/GiltAnimInstance.h"

#include "AbilitySystemGlobals.h"


void UGiltAnimInstance::InitializeWithAbilitySystem(UAbilitySystemComponent* ASC)
{
	check(ASC);

	GameplayTagPropertyMap.Initialize(this, ASC);
}

void UGiltAnimInstance::NativeInitializeAnimation()
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