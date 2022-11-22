// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GiltInteractableTargetInterface.h"
#include "GameFramework/Actor.h"
#include "GiltWorldInteractable.generated.h"

UCLASS(Abstract, Blueprintable)
class PROJECTTITAN_API AGiltWorldInteractable : public AActor, public IGiltInteractableTargetInterface
{
	GENERATED_BODY()

public:

	AGiltWorldInteractable();

	virtual void GatherInteractionOptions(const FGiltInteractionQuery& InteractQuery, FInteractionOptionBuilder& OptionBuilder) override;

protected:
	UPROPERTY(EditAnywhere)
	FGiltInteractionOption Option;
};
