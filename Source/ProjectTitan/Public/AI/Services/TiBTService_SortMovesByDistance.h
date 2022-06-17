// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "TiBTService_SortMovesByDistance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UTiBTService_SortMovesByDistance : public UBTService
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector AttackIndex;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	bool ActivateDebug;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	
	UTiBTService_SortMovesByDistance();
};
