// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TiCharacterMovementComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "TiGameplayTags.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_MovementStopped, "Gameplay.MovementStopped");

UTiCharacterMovementComponent::UTiCharacterMovementComponent()
{
	SprintSpeedMultiplier = 2.0f;
}

float UTiCharacterMovementComponent::GetMaxSpeed() const
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner()))
	{
		if (ASC->HasMatchingGameplayTag(TAG_Gameplay_MovementStopped))
		{
			return 0;
		}

		if(ASC->HasMatchingGameplayTag(FTiGameplayTags::Get().Status_Aim))
		{
			return 0;
		}
	}

	/*
	if (RequestToStartSprinting)
	{
		return Owner->GetMoveSpeed() * SprintSpeedMultiplier;
	}
	*/
	return Super::GetMaxSpeed();
}

void UTiCharacterMovementComponent::StartSprinting()
{
	RequestToStartSprinting = true;
}

void UTiCharacterMovementComponent::StopSprinting()
{
	RequestToStartSprinting = false;
}
