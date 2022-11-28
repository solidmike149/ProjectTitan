// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GiltCharacterMovementComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"


UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_MovementStopped, "Gameplay.MovementStopped");
UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_RotationStopped, "Gameplay.RotationStopped");

UGiltCharacterMovementComponent::UGiltCharacterMovementComponent()
{
}

FRotator UGiltCharacterMovementComponent::GetDeltaRotation(float DeltaTime) const
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner()))
	{
		if (ASC->HasMatchingGameplayTag(TAG_Gameplay_RotationStopped))
		{
			return FRotator(0,0,0);
		}
	}

	return Super::GetDeltaRotation(DeltaTime);
}

float UGiltCharacterMovementComponent::GetMaxSpeed() const
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner()))
	{
		if (ASC->HasMatchingGameplayTag(TAG_Gameplay_MovementStopped))
		{
			return 0;
		}
	}

	return Super::GetMaxSpeed();
}
