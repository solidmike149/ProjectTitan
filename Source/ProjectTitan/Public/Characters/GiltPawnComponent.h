// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "GiltPawnComponent.generated.h"


UINTERFACE(BlueprintType)
class PROJECTTITAN_API UGiltReadyInterface : public UInterface
{
	GENERATED_BODY()
};

class IGiltReadyInterface
{
	GENERATED_BODY()

public:
	virtual bool IsPawnComponentReadyToInitialize() const = 0;
};



/**
 * UGiltPawnComponent
 *
 *	An actor component that can be used for adding custom behavior to pawns.
 */
UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent))
class PROJECTTITAN_API UGiltPawnComponent : public UPawnComponent, public IGiltReadyInterface
{
	GENERATED_BODY()
	
public:

	UGiltPawnComponent(const FObjectInitializer& ObjectInitializer);

	virtual bool IsPawnComponentReadyToInitialize() const override { return true; }
};
