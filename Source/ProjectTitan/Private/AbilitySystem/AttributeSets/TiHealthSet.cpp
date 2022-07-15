// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/TiHealthSet.h"
#include "GameplayEffectExtension.h"


UTiHealthSet::UTiHealthSet()
	: Health(1.0f)
	, MaxHealth(1.0f)
{
	
}

void UTiHealthSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		if ((GetHealth() <= 0.0f))
		{
			if (OnOutOfHealth.IsBound())
			{
				const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
				AActor* Instigator = EffectContext.GetOriginalInstigator();
				AActor* Causer = EffectContext.GetEffectCauser();

				OnOutOfHealth.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude);
			}
		}
	}
}
