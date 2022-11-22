// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "GiltInputAction.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECTTITAN_API UGiltInputAction : public UInputAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action")
	FGameplayTag InputTag;
};
