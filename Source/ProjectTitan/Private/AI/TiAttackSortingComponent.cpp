// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TiAttackSortingComponent.h"

#include "AI/TiAIControllerBase.h"

// Sets default values for this component's properties
UTiAttackSortingComponent::UTiAttackSortingComponent()
{
	ComboWindow = 0.5;
}

void UTiAttackSortingComponent::IncrementScoreByCurve(int32 AttackIndex, float Distance, FAttack& OutAttack)
{
	FAttack& Attack = AttackData[AttackIndex];
	
	FRuntimeFloatCurve Curve = Attack.DistanceCurve;

	if (Curve.GetRichCurveConst() && Curve.GetRichCurveConst()->GetNumKeys() > 0)
	{
		float AddingScore = Curve.GetRichCurveConst()->Eval(Distance);

		Attack.Score += AddingScore;
		
		Attack.Score = FMath::Clamp(Attack.Score, 0.0f, 1.0f);
		
		OutAttack = Attack;
	}
}

void UTiAttackSortingComponent::ResetAttackScore(int32 AttackIndex)
{
	FCombo ActiveCombo = AttackData[AttackIndex].ComboData;

	ATiAIControllerBase* AIController = Cast<ATiAIControllerBase>(GetOwner());

	if(AIController)
	{
		if (AIController->bIsInComboCpp)
		{
			int32 Index = 0;
			for (FAttack& Attack : AttackData)
			{
				if (Index == AttackIndex)
				{
					Attack.Score -= Attack.DecrementScoreExecuted;
				}
			
				else if (Index == ActiveCombo.Index)
				{
					Attack.Score += ActiveCombo.IncrementScore;
				}
			
				else
				{
					Attack.Score -= Attack.DecrementScoreBase;
				}

				Attack.Score = FMath::Clamp(Attack.Score, 0.0f, 1.0f);
				Index ++;
			}	
		}
	
		else
		{
			int32 Index = 0;
		
			for (FAttack& Attack : AttackData)
			{
				if (Index == AttackIndex)
				{
					Attack.Score -= Attack.DecrementScoreExecuted;
				}
			
				else if(Index == ActiveCombo.Index)
				{
					Attack.Score += ActiveCombo.IncrementScore;
				}
			
				Attack.Score = FMath::Clamp(Attack.Score, 0.0f, 1.0f);
				Index ++;
			}
		}	
	}
}

FGameplayTag UTiAttackSortingComponent::ConvertIndexToTag(int32 AttackIndex)
{
	FString BaseString = "Ability.Melee.Attack";

	FString IndexString = FString::FromInt(AttackIndex);

	FString Result = BaseString + IndexString;

	FName OutName = FName(*Result);

	return FGameplayTag::RequestGameplayTag(OutName);
}

