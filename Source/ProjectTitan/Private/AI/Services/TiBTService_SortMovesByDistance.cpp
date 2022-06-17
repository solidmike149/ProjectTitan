// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/TiBTService_SortMovesByDistance.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AbilitySystem/Abilities/TiGA_Moveset.h"


UTiBTService_SortMovesByDistance::UTiBTService_SortMovesByDistance()
{
	ActivateDebug = false;
}


void UTiBTService_SortMovesByDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComp))
	{
		AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject("Player"));
		if (TargetActor)
		{
			AAIController* MyController = OwnerComp.GetAIOwner();
			if (ensure(MyController))
			{
				APawn* AIPawn = MyController->GetPawn();
				if (ensure(AIPawn))
				{
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

					if (ActivateDebug)
					{
						FString DistanceDebug = FString::Printf(TEXT("Distance: %f"), DistanceTo);
						GEngine->AddOnScreenDebugMessage(-1, Interval, FColor::Green, DistanceDebug);
					}

					bool IsAttacking = BlackboardComp->GetValueAsBool("IsAttacking");
					
					if (IsAttacking)
					{
						UTiGA_Moveset* Moveset = Cast<UTiGA_Moveset>(BlackboardComp->GetValueAsObject("Moveset"));
						
						TArray<FAttackData> AttackDatas;
						
						AttackDatas = Moveset->AttackDatas;

						int32 Index = 0;

						TArray<int32> SortedAttackIndexes;
						
						for (FAttackData AttackData : AttackDatas)
						{
							FAttackData OutAttack;
							Moveset->IncrementScoreByCurve(Index, DistanceTo, OutAttack);

							if(OutAttack.IsInThreshold())
							{
								SortedAttackIndexes.Add(Index);
							}
						}

						if (SortedAttackIndexes.Num() > 0)
						{
							int32 IndexToExecute;
							if(SortedAttackIndexes.Last() == 0)
							{
								IndexToExecute = 0;
							}
							else
							{
								IndexToExecute = FMath::RandRange(0 ,SortedAttackIndexes.Last());
							}

							BlackboardComp->SetValueAsInt(AttackIndex.SelectedKeyName, IndexToExecute);
						}
					}
				}
			}
		}
	}
}
