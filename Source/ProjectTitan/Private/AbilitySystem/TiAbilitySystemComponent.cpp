// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TiAbilitySystemComponent.h"

#include "AbilitySystem/TiGameplayAbility.h"

bool UTiAbilitySystemComponent::IsAbilityActive(const FGameplayTagContainer* WithTags, const FGameplayTagContainer* WithoutTags, UGameplayAbility* Ignore)
{
	ABILITYLIST_SCOPE_LOCK();
 
	for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		if (!Spec.IsActive() || Spec.Ability == nullptr || Spec.Ability == Ignore)
		{
			continue;
		}
 
		const bool WithTagPass = (!WithTags || Spec.Ability->AbilityTags.HasAny(*WithTags));
		const bool WithoutTagPass = (!WithoutTags || !Spec.Ability->AbilityTags.HasAny(*WithoutTags));
 
		if (WithTagPass && WithoutTagPass)
		{
			return true;
		}
	}
	return false;
}
 
bool UTiAbilitySystemComponent::IsAbilityActive(const FGameplayAbilitySpecHandle& InHandle)
{
	ABILITYLIST_SCOPE_LOCK();
	FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(InHandle);
	return Spec ? Spec->IsActive() : false;
}
