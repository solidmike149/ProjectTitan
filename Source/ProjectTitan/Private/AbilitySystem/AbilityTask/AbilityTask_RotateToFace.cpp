// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTask/AbilityTask_RotateToFace.h"

#include "AbilitySystemGlobals.h"

UAbilityTask_RotateToFace::UAbilityTask_RotateToFace()
{
	bTickingTask = true;
	ActorToFace = nullptr;
	OptionalInterpolationCurve = nullptr;
	Time = 0.0f;
}

void UAbilityTask_RotateToFace::Activate()
{
	Super::Activate();
}

UAbilityTask_RotateToFace* UAbilityTask_RotateToFace::RotateToFace
(
	UGameplayAbility* OwningAbility,
	FName TaskInstanceName,
	AActor* ActorToFace,
	FRotator TargetRotation,
	float Duration,
	float InterpolationSpeed,
	UCurveFloat* OptionalInterpolationCurve
)
{
	UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Duration(Duration);
	
	UAbilityTask_RotateToFace* MyTask = NewAbilityTask<UAbilityTask_RotateToFace>(OwningAbility, TaskInstanceName);
	
	MyTask->Duration = Duration;
	MyTask->ActorToFace = ActorToFace;
	MyTask->TargetRotation = TargetRotation;
	MyTask->InterpolationSpeed = InterpolationSpeed,
	MyTask->OptionalInterpolationCurve = OptionalInterpolationCurve;

	return MyTask;
}


void UAbilityTask_RotateToFace::TickTask(float DeltaTime)
{
	if (bIsFinished)
	{
		return;
	}
	
	Super::TickTask(DeltaTime);

	AActor* MyActor = GetAvatarActor();
	if (MyActor)
	{
		const bool bIsInfiniteDuration = Duration < 0.f;

		if (!bIsInfiniteDuration)
		{
			// Task has finished
			bIsFinished = true;
			if (!bIsSimulating)
			{
				MyActor->ForceNetUpdate();
				if (ShouldBroadcastAbilityTaskDelegates())
				{
					OnTimedOut.Broadcast();
				}
				EndTask();
			}
		}
		Rotate(DeltaTime);
	}
	else
	{
		bIsFinished = true;
		EndTask();
	}
}

void UAbilityTask_RotateToFace::Rotate(float DeltaTime)
{
	FRotator InterpRotation;

	AActor* Avatar = GetAvatarActor();
	
	if(ActorToFace)
	{
		InterpRotation = FRotationMatrix::MakeFromX(ActorToFace->GetActorLocation() - Avatar->GetActorLocation()).Rotator();

		if(OptionalInterpolationCurve)
		{
			Time += DeltaTime;
			InterpolationSpeed = OptionalInterpolationCurve->GetFloatValue(Time);
		}
	}
	
	FRotator FinalRotation = FMath::RInterpTo(Avatar->GetActorRotation(), InterpRotation,
										GetWorld()->GetDeltaSeconds(), InterpolationSpeed);
	
	Avatar->SetActorRotation(FinalRotation);
}

void UAbilityTask_RotateToFace::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}
