// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/TeAnimInstance.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

void UTeAnimInstance::InitializeWithAbilitySystem(UAbilitySystemComponent* ASC)
{
	check(ASC);

	GameplayTagPropertyMap.Initialize(this, ASC);
}

void UTeAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningPawn = TryGetPawnOwner();
	
	if (AActor* OwningActor = GetOwningActor())
	{
		if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor))
		{
			AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor);
			InitializeWithAbilitySystem(ASC);
		}
	}
}

void UTeAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
