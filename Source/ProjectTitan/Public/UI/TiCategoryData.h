// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TiCategoryData.generated.h"

enum class EEntryCategory : uint8;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FCategoryData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<UObject> Parent;

	UPROPERTY(BlueprintReadWrite)
	EEntryCategory Category;
	
};
UCLASS(Blueprintable)
class PROJECTTITAN_API UTiCategoryData : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	FCategoryData Data;
};
