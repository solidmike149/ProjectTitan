// Fill out your copyright notice in the Description page of Project Settings.


#include "TiAnimInstance.h"

#include "AbilitySystemComponent.h"

void UTiAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningPawn = TryGetPawnOwner();
	if (OwningPawn)
	{
		AbilitySystemComponent = Cast<UAbilitySystemComponent>(OwningPawn->GetComponentByClass(UAbilitySystemComponent::StaticClass()));
	}
}
