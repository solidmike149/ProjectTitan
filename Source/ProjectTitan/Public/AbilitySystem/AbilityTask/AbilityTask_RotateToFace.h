// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_RotateToFace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRotateToFaceDelegate);

/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UAbilityTask_RotateToFace : public UAbilityTask
{

	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FRotateToFaceDelegate OnTimedOut;
	
protected:
	
	UAbilityTask_RotateToFace();
	
	virtual void Activate() override;

	virtual void OnDestroy(bool bInOwnerFinished) override;

	virtual void TickTask(float DeltaTime) override;
	
private:

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_RotateToFace* RotateToFace(
													UGameplayAbility* OwningAbility,
													FName TaskInstanceName,
													AActor* ActorToFace,
													FRotator TargetRotation,
													float Duration,
													float InterpolationSpeed,
													UCurveFloat* OptionalInterpolationCurve
													);

	void Rotate(float DeltaTime);

	UPROPERTY()
	AActor* ActorToFace;
	
	FRotator TargetRotation;

	float Duration;

	float InterpolationSpeed;

	UPROPERTY()
	UCurveFloat* OptionalInterpolationCurve;
	
	bool bIsFinished;

	float Time;
};
