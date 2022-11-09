// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GiltCharacterMovementComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"


UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_MovementStopped, "Gameplay.MovementStopped");

UGiltCharacterMovementComponent::UGiltCharacterMovementComponent()
{
}

float UGiltCharacterMovementComponent::GetMaxSpeed() const
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner()))
	{
		if (ASC->HasAnyMatchingGameplayTags(MovementBlockingTag))
		{
			return 0;
		}
	}
	return Super::GetMaxSpeed();
}
