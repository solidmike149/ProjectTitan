// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TiIndexData.generated.h"

USTRUCT(BlueprintType)
struct FIndexData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<UObject> Parent;

	UPROPERTY(BlueprintReadWrite)
	FName Id;
	
	UPROPERTY(BlueprintReadWrite)
	FText Title;

	FIndexData(){}

	FIndexData(TWeakObjectPtr<UObject> NewParent, FName NewId, FText NewTitle)
	{
		Parent = NewParent;
		Id = NewId;
		Title = NewTitle;
	}
};
/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTTITAN_API UTiIndexData : public UObject
{
	GENERATED_BODY()

public:
	
	UTiIndexData();
	
	UPROPERTY(BlueprintReadWrite)
	FIndexData Data;
};
