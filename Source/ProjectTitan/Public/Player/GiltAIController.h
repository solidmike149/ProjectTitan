// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularAIController.h"
#include "GiltAIController.generated.h"

/**
 * AGiltAIController
 *
 *	The controller class used by bots in this project.
 */
UCLASS(Blueprintable)
class AGiltAIController : public AModularAIController
{
	GENERATED_BODY()

public:
	
	AGiltAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void OnUnPossess() override;
};
