// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GiltInteractionOption.h"
#include "UObject/Interface.h"
#include "GiltInteractableTargetInterface.generated.h"

struct FGiltInteractionQuery;
class IGiltInteractableTargetInterface;

class FInteractionOptionBuilder
{
public:
	FInteractionOptionBuilder(TScriptInterface<IGiltInteractableTargetInterface> InterfaceTargetScope, TArray<FGiltInteractionOption>& InteractOptions)
		: Scope(InterfaceTargetScope)
		, Options(InteractOptions)
	{
	}

	void AddInteractionOption(const FGiltInteractionOption& Option)
	{
		FGiltInteractionOption& OptionEntry = Options.Add_GetRef(Option);
		OptionEntry.InteractableTarget = Scope;
	}

private:
	TScriptInterface<IGiltInteractableTargetInterface> Scope;
	TArray<FGiltInteractionOption>& Options;
};


UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UGiltInteractableTargetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IGiltInteractableTargetInterface
{
	GENERATED_BODY()

public:
	
	/**  */
	virtual void GatherInteractionOptions(const FGiltInteractionQuery& InteractQuery, FInteractionOptionBuilder& OptionBuilder) = 0;

	/**  */
	virtual void CustomizeInteractionEventData(const FGameplayTag& InteractionEventTag, FGameplayEventData& InOutEventData) { }
};
