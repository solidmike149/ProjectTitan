// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/GiltPlayerSet.h"

#include "GameplayEffectExtension.h"

UGiltPlayerSet::UGiltPlayerSet()
{
	MaxStamina = 100;
	Stamina = 100;
	MaxAmmo = 3;
	Ammo = 3;
}

void UGiltPlayerSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
	}

	else if (Data.EvaluatedData.Attribute == GetAmmoAttribute())
	{
		SetAmmo(FMath::Clamp(GetAmmo(), 0.0f, GetMaxAmmo()));
	}
}
