// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/TiGameplayAbility.h"

#include "AbilitySystem/TiAbilitySystemComponent.h"


UTiGameplayAbility::UTiGameplayAbility()
{
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateNo;

	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UTiGameplayAbility::TryActivateAbilityOnSpawn(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) const
{

	// Try to activate if activation policy is on spawn.
	if (ActorInfo && !Spec.IsActive())
	{
		UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
		const AActor* AvatarActor = ActorInfo->AvatarActor.Get();

		// If avatar actor is torn off or about to die, don't try to activate until we get the new one.
		if (ASC && AvatarActor && (AvatarActor->GetLifeSpan() <= 0.0f))
		{
			
			ASC->TryActivateAbility(Spec.Handle);
		}
	}
}

void UTiGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	K2_OnAbilityAdded();

	//TryActivateAbilityOnSpawn(ActorInfo, Spec);
}

void UTiGameplayAbility::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	K2_OnAbilityRemoved();

	Super::OnRemoveAbility(ActorInfo, Spec);
}

void UTiGameplayAbility::OnPawnAvatarSet()
{
	K2_OnPawnAvatarSet();
}
