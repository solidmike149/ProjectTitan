// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularGameState.h"
#include "GiltGameState.generated.h"

class UGiltExperienceManagerComponent;

UCLASS()
class PROJECTTITAN_API AGiltGameState : public AModularGameStateBase
{
	GENERATED_BODY()

public:

	AGiltGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

private:
	
	UPROPERTY()
	UGiltExperienceManagerComponent* ExperienceManagerComponent;
};
