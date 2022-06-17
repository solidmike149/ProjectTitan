// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "TiBTService_PredictPlayerLoc.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UTiBTService_PredictPlayerLoc : public UBTService
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector Player;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetLocation;

	UPROPERTY(EditAnywhere, Category = "AI")
	bool ActivateDebug;

	UPROPERTY(EditAnywhere, Category = "Graphs")
	FRuntimeFloatCurve DegreesCurve;

	UPROPERTY(EditAnywhere, Category = "Graphs")
	FRuntimeFloatCurve DistanceCurve;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:

	UTiBTService_PredictPlayerLoc();
};
