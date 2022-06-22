// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TiGameplayAbility.h"

UTiGameplayAbility::UTiGameplayAbility()
{
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateNo;

	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}
