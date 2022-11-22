// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GiltGameplayAbility.h"
#include "Interaction/GiltInteractionOption.h"
#include "GiltGameplayAbility_Interact.generated.h"

class UGiltIndicatorDescriptor;
/**
 * UGiltGameplayAbility_Interact
 *
 * Gameplay ability used for character interacting
 */
UCLASS(Abstract)
class PROJECTTITAN_API UGiltGameplayAbility_Interact : public UGiltGameplayAbility
{
	GENERATED_BODY()

public:

	UGiltGameplayAbility_Interact(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable)
	void UpdateInteractions(const TArray<FGiltInteractionOption>& InteractiveOptions);

	UFUNCTION(BlueprintCallable)
	void TriggerInteraction();

protected:
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FGiltInteractionOption> CurrentOptions;

	UPROPERTY()
	TArray<UGiltIndicatorDescriptor*> Indicators;

	UPROPERTY(EditDefaultsOnly)
	float InteractionScanRate = 0.1f;

	UPROPERTY(EditDefaultsOnly)
	float InteractionScanRange = 500;

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UUserWidget> DefaultInteractionWidgetClass;
};
