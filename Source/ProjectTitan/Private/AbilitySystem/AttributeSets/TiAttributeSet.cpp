// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/TiAttributeSet.h"

#include "AbilitySystem/TiAbilitySystemComponent.h"

UTiAttributeSet::UTiAttributeSet()
{
}

UWorld* UTiAttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);

	return Outer->GetWorld();
}

UTiAbilitySystemComponent* UTiAttributeSet::GetTiAbilitySystemComponent() const
{
	return Cast<UTiAbilitySystemComponent>(GetOwningAbilitySystemComponent());
}
