// Fill out your copyright notice in the Description page of Project Settings.


#include "TiCharacterMovementComponent.h"

#include "TiCharacter.h"

UTiCharacterMovementComponent::UTiCharacterMovementComponent()
{
	SprintSpeedMultiplier = 2.0f;
}

float UTiCharacterMovementComponent::GetMaxSpeed() const
{
	ATiCharacter* Owner = Cast<ATiCharacter>(GetOwner());
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() No Owner"), *FString(__FUNCTION__));
		return Super::GetMaxSpeed();
	}

	if (!Owner->IsAlive())
	{
		return 0.0f;
	}

	if (RequestToStartSprinting)
	{
		return Owner->GetMoveSpeed() * SprintSpeedMultiplier;
	}
	
	return Owner->GetMoveSpeed();
}

void UTiCharacterMovementComponent::StartSprinting()
{
	RequestToStartSprinting = true;
}

void UTiCharacterMovementComponent::StopSprinting()
{
	RequestToStartSprinting = false;
}
