// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Interaction/GiltInteractableTargetInterface.h"
#include "AbilityTask_WaitForInteractableTargets.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGiltInteractableObjectsChanged, const TArray<FGiltInteractionOption>&, InteractableOptions);
/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UAbilityTask_WaitForInteractableTargets : public UAbilityTask
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintAssignable)
	FGiltInteractableObjectsChanged InteractableObjectsChanged;

protected:

	static void LineTrace(FHitResult& OutHitResult, const UWorld* World, const FVector& Start, const FVector& End, FName ProfileName, const FCollisionQueryParams Params);

	void AimWithAvatarActor(const AActor* InSourceActor, FCollisionQueryParams Params, const FVector& TraceStart, float MaxRange, FVector& OutTraceEnd, bool bIgnorePitch = false) const;

	void UpdateInteractableOptions(const FGiltInteractionQuery& InteractQuery, const TArray<TScriptInterface<IGiltInteractableTargetInterface>>& InteractableTargets);

	FCollisionProfileName TraceProfile;

	// Does the trace affect the aiming pitch
	bool bTraceAffectsAimPitch = true;

	TArray<FGiltInteractionOption> CurrentOptions;
};
