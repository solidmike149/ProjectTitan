// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TiInteractionInterface.generated.h"

UENUM(BlueprintType)
enum class EInteractionState : uint8
{
	None,
	Hint,
	Prompt,
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTiInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTTITAN_API ITiInteractionInterface
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EInteractionState GetInteractionState() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetInteractionState(EInteractionState NewState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FName Interact();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FName GetId();
};
