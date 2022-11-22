// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GiltTargetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UGiltTargetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTTITAN_API IGiltTargetInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void NotifyTargeting();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetTargetLocation() const;
};
