// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/TiBTService_PredictPlayerLoc.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "DrawDebugHelpers.h"

UTiBTService_PredictPlayerLoc::UTiBTService_PredictPlayerLoc()
{
	
}


void UTiBTService_PredictPlayerLoc::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
					FVector x = AIPawn->GetActorLocation() - TargetActor->GetActorLocation();

					x = x.GetSafeNormal2D();

					float DotProduct = FVector::DotProduct(x, TargetActor->GetActorForwardVector());

					float Degrees = (180.f)/PI * FMath::Acos(DotProduct);
					
					if (DegreesCurve.GetRichCurveConst() && DegreesCurve.GetRichCurveConst()->GetNumKeys() > 0)
					{
						float Offset = DegreesCurve.GetRichCurveConst()->Eval(Degrees);
						
						if (DistanceCurve.GetRichCurveConst() && DistanceCurve.GetRichCurveConst()->GetNumKeys() > 0)
						{
							float Distance = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());
							
							float DistanceMultiplier = DistanceCurve.GetRichCurveConst()->Eval(Distance);

							FVector FinalLocation = TargetActor->GetActorLocation() + TargetActor->GetActorForwardVector() * Offset * DistanceMultiplier;
							
							BlackboardComp->SetValueAsVector(TargetLocation.SelectedKeyName, FinalLocation);
							if (ActivateDebug)
							{
								FString DegreesDebug = FString::Printf(TEXT("Degrees: %f"), Degrees);
								GEngine->AddOnScreenDebugMessage(-1, Interval, FColor::Green, DegreesDebug);
							
								FString OffsetDebug = FString::Printf(TEXT("Offset: %f"), Offset);
								GEngine->AddOnScreenDebugMessage(-1, Interval, FColor::Red, OffsetDebug);
								DrawDebugSphere(GetWorld(), FinalLocation, 50, 8, FColor::Red, false, Interval);
								DrawDebugLine(GetWorld(), TargetActor->GetActorLocation(), FinalLocation, FColor::Magenta, false, Interval);
							}
						}
					}
				}
			}
		}
	}
}
