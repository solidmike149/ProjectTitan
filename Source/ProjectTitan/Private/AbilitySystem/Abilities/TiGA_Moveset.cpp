// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TiGA_Moveset.h"


UTiGA_Moveset::UTiGA_Moveset()
{
	ComboWindow = 0.5;
}

void UTiGA_Moveset::IncrementScoreByCurve(int32 AttackIndex, float Distance, FAttackData& OutAttack)
{
	FAttackData& Attack = AttackDatas[AttackIndex];
	
	FRuntimeFloatCurve Curve = Attack.DistanceCurve;

	if (Curve.GetRichCurveConst() && Curve.GetRichCurveConst()->GetNumKeys() > 0)
	{
		float AddingScore = Curve.GetRichCurveConst()->Eval(Distance);

		Attack.Score += AddingScore;
		
		Attack.Score = FMath::Clamp(Attack.Score, -1.0f, 1.0f);
		
		OutAttack = Attack;
	}
}

void UTiGA_Moveset::ResetAttackScore(int32 AttackIndex, bool InCombo)
{
	FComboData ActiveCombo = AttackDatas[AttackIndex].ComboData;
	
	if (!InCombo)
	{
		int32 Index = 0;
		for (FAttackData& Attack : AttackDatas)
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

			Attack.Score = FMath::Clamp(Attack.Score, -1.0f, 1.0f);
			Index ++;
		}	
	}
	
	else
	{
		int32 Index = 0;
		
		for (FAttackData& Attack : AttackDatas)
		{
			if (Index == AttackIndex)
			{
				Attack.Score -= Attack.DecrementScoreExecuted;
			}
			
			else if(Index == ActiveCombo.Index)
			{
				Attack.Score += ActiveCombo.IncrementScore;
			}
			
			Attack.Score = FMath::Clamp(Attack.Score, -1.0f, 1.0f);
			Index ++;
		}
	}
}
