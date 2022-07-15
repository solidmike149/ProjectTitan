// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AI/TiAiCharacter.h"
#include "TiGuardian.generated.h"



class UTiTraceComponent;
class ATiShield;
/**
 * 
 */
UCLASS()
class PROJECTTITAN_API ATiGuardian : public ATiAiCharacter
{
	GENERATED_BODY()

protected:



public:

	UPROPERTY(BlueprintReadWrite)
	ATiShield* Shield;

	UFUNCTION(BlueprintImplementableEvent)
	void GetShield();

	ATiGuardian();
};
