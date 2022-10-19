// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "TiAttackSortingComponent.generated.h"

USTRUCT(BlueprintType)
struct FCombo
{
	GENERATED_BODY()

	FCombo()
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
struct FAttack
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
	FCombo ComboData;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, DisplayName="Attack Sorting Component"))
class PROJECTTITAN_API UTiAttackSortingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTiAttackSortingComponent();

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (TitleProperty = "AttackName"), Category = "Attacks")
	TArray<FAttack> AttackData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attacks")
	float ComboWindow;

	UPROPERTY(BlueprintReadWrite, Category = "Attacks")
	bool bIsInCombo;

	UFUNCTION(BlueprintCallable)
	void IncrementScoreByCurve(int32 AttackIndex ,float Distance, FAttack& OutAttack);

	UFUNCTION(BlueprintCallable)
	void ResetAttackScore(int32 AttackIndex);

	UFUNCTION(BlueprintCallable)
	FGameplayTag ConvertIndexToTag(int32 AttackIndex);
};
