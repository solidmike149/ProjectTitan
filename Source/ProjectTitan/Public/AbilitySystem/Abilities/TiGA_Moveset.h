// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TiGameplayAbility.h"
#include "TiGA_Moveset.generated.h"

USTRUCT(BlueprintType)
struct FComboData
{
	GENERATED_BODY()

	FComboData()
	{
		Index = -1;

		IncrementScore = 0;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Index = -1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float IncrementScore;
};

USTRUCT(BlueprintType)
struct FAttackData
{
	GENERATED_BODY()

	//TODO Constructor

	bool IsInThreshold() const
	{
		if (Score <= ScoreThreshold)
		{
			return true;
		}
		return false;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName AttackName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRuntimeFloatCurve DistanceCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ScoreThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DecrementScoreBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DecrementScoreExecuted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FComboData ComboData;
};

/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UTiGA_Moveset : public UTiGameplayAbility
{
	GENERATED_BODY()


public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (TitleProperty = "AttackName"), Category = "Attacks")
	TArray<FAttackData> AttackDatas;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attacks")
	float ComboWindow;

	UPROPERTY(BlueprintReadWrite, Category = "Attacks")
	bool bIsInCombo;

	UFUNCTION(BlueprintCallable)
	void IncrementScoreByCurve(int32 AttackIndex ,float Distance, FAttackData& OutAttack);

	UFUNCTION(BlueprintCallable)
	void ResetAttackScore(int32 AttackIndex, bool InCombo);

	UTiGA_Moveset();
};
