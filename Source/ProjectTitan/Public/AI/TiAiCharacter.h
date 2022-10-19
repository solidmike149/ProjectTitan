// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/TiCharacter.h"
#include "Interfaces/TiTargetInterface.h"
#include "TiAiCharacter.generated.h"

class UTiHealthSet;
class UGameplayEffect;
class UTiGameplayAbility;
class UTiAbilitySystemComponent;

UCLASS()
class PROJECTTITAN_API ATiAiCharacter : public ATiCharacter, public ITiTargetInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite)
	AActor* Player;
	
public:

	void Tracking(float InterpSpeed);

	ATiAiCharacter(const FObjectInitializer& ObjectInitializer);
	
};
