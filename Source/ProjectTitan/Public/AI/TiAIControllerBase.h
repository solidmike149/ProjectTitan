// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TiAIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTITAN_API ATiAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	bool bIsInComboCpp;
};
