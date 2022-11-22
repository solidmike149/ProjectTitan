// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/GiltInputConfig.h"

#include "GiltLogChannels.h"
#include "Input/GiltInputAction.h"

UGiltInputConfig::UGiltInputConfig(const FObjectInitializer& ObjectInitializer)
{
}


const UInputAction* UGiltInputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const UGiltInputAction* Action : NativeInputActions)
	{
		if (Action && (Action->InputTag == InputTag))
		{
			return Action;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogGilt, Error, TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}

const UInputAction* UGiltInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const UGiltInputAction* Action : AbilityInputActions)
	{
		if (Action && (Action->InputTag == InputTag))
		{
			return Action;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogGilt, Error, TEXT("Can't find AbilityInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}