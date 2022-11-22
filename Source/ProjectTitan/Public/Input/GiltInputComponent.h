// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GiltInputAction.h"
#include "GiltInputConfig.h"
#include "GiltMappableConfigPair.h"
#include "InputTriggers.h"
#include "GiltInputComponent.generated.h"


class UEnhancedInputLocalPlayerSubsystem;

/**
 * UGiltInputComponent
 *
 *	Component used to manage input mappings and bindings using an input config data asset.
 */
UCLASS(Config = Input)
class UGiltInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	UGiltInputComponent(const FObjectInitializer& ObjectInitializer);

	void AddInputMappings(const UGiltInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const;
	void RemoveInputMappings(const UGiltInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const;

	template<class UserClass, typename FuncType>
	void BindNativeAction(const UGiltInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound);

	template<class UserClass, typename PressedFuncType>
	void BindAbilityActions(const UGiltInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, TArray<uint32>& BindHandles);

	void RemoveBinds(TArray<uint32>& BindHandles);

	void AddInputConfig(const FLoadedMappableConfigPair& ConfigPair, UEnhancedInputLocalPlayerSubsystem* InputSubsystem);
	void RemoveInputConfig(const FLoadedMappableConfigPair& ConfigPair, UEnhancedInputLocalPlayerSubsystem* InputSubsystem);
};


template<class UserClass, typename FuncType>
void UGiltInputComponent::BindNativeAction(const UGiltInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound)
{
	check(InputConfig);
	if (const UInputAction* IA = InputConfig->FindNativeInputActionForTag(InputTag, bLogIfNotFound))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}
}

template<class UserClass, typename PressedFuncType>
void UGiltInputComponent::BindAbilityActions(const UGiltInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, TArray<uint32>& BindHandles)
{
	check(InputConfig);

	for (const UGiltInputAction* Action : InputConfig->AbilityInputActions)
	{
		if (Action && Action->InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindHandles.Add(BindAction(Action, ETriggerEvent::Triggered, Object, PressedFunc).GetHandle());
			}
		}
	}
}

