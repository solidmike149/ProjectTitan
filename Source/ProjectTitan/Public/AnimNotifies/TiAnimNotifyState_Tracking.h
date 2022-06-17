// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "TiAnimNotifyState_Tracking.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UTiAnimNotifyState_Tracking : public UAnimNotifyState
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Tracking")
	float InterpSpeed;

	UPROPERTY(EditAnywhere, Category = "Tracking", AdvancedDisplay)
	FRuntimeFloatCurve InterpSpeedCurve;
	
	float Time;

protected:

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
};
