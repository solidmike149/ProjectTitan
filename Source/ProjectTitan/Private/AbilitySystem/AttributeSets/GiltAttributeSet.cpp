// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/GiltAttributeSet.h"

#include "AbilitySystem/GiltAbilitySystemComponent.h"

UGiltAttributeSet::UGiltAttributeSet()
{
}

UWorld* UGiltAttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);

	return Outer->GetWorld();
}

UGiltAbilitySystemComponent* UGiltAttributeSet::GetLyraAbilitySystemComponent() const
{
	return Cast<UGiltAbilitySystemComponent>(GetOwningAbilitySystemComponent());
}